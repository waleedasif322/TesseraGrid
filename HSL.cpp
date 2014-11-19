// The code for HSL computation and adjustments has been taken from GIMP

#include "HSL.h"

HSL::HSL()
{
	init();
}


void
HSL::init()
{
	m_overlap = 0.0;
	for(int i=0; i<7; i++){
		m_hue	    [i] = 0.0;
		m_lightness [i] = 0.0;
		m_saturation[i] = 0.0;
	}
}



void
HSL::setHue(int range, double v)
{
	if(range < AllHues || range > MagentaHues)
		return;

	m_hue[range] = v;
}



void
HSL::setSaturation(int range, double v)
{
	if(range < AllHues || range > MagentaHues)
		return;

	m_saturation[range] = v;
}



void
HSL::setLightness(int range, double v)
{
	if(range < AllHues || range > MagentaHues)
		return;

	m_lightness[range] = v;
}



void
HSL::setOverlap(double v)
{
	m_overlap = v;
}



double
HSL::hue(int range)
{
	if(range < AllHues || range > MagentaHues)
		return -1;
	return m_hue[range];
}



double
HSL::saturation(int range)
{
	if(range < AllHues || range > MagentaHues)
		return -1;
	return m_saturation[range];
}



double
HSL::lightness(int range)
{
	if(range < AllHues || range > MagentaHues)
		return -1;
	return m_lightness[range];
}



double
HSL::overlap()
{
	return m_overlap;
}



inline double
hslValue(double n1, double n2, double hue)
{
	double	val;

	if (hue > 6.0)
		hue -= 6.0;
	else if (hue < 0.0)
		hue += 6.0;

	if (hue < 1.0)
		val = n1 + (n2 - n1) * hue;
	else if (hue < 3.0)
		val = n2;
	else if (hue < 4.0)
		val = n1 + (n2 - n1) * (4.0 - hue);
	else
		val = n1;

	return val;
}



inline void
RGBToHSL(const QRgb &rgb, double &h, double &s, double &l)
{
	double	max, min, delta;
	double	r = qRed  (rgb) / 255.0;
	double	g = qGreen(rgb) / 255.0;
	double	b = qBlue (rgb) / 255.0;

	max = MAX( MAX(r, g), b);
	min = MIN( MIN(r, g), b);
	l = (max + min) / 2.0;

	if(max == min) {
		s = 0.0;
		h = -1;
	} else {
		if(l <= 0.5)
			s = (max - min) / (max + min);
		else	s = (max - min) / (2.0 - max - min);
		delta = max - min;
		if (delta == 0.0)
			delta = 1.0;

		if(r == max)
			h = (g - b) / delta;
		else if(g == max)
			h = 2.0 + (b - r) / delta;
		else if(b == max)
			h = 4.0 + (r - g) / delta;
		h /= 6.0;
		if (h < 0.0)
			h += 1.0;
	}
}



inline void
HSLToRGB(double h, double s, double l, QRgb &rgb)
{
	double	r, g, b;

	if(s == 0) {
		/*  achromatic case  */
		r = l;
		g = l;
		b = l;
	}
	else {
		double m1, m2;

		if (l <= 0.5)
			m2 = l * (1.0 + s);
		else	m2 = l + s - l * s;
		m1 = 2.0 * l - m2;
		r = hslValue (m1, m2, h * 6.0 + 2.0);
		g = hslValue (m1, m2, h * 6.0);
		b = hslValue (m1, m2, h * 6.0 - 2.0);
	}
	rgb = qRgb((int) (r*255), (int) (g*255), (int) (b*255));
}



double
HSL::mapHue(int range, double value)
{
	value += (m_hue[AllHues] + m_hue[range]) / 2.0;

	if (value < 0)
		return value + 1.0;
	else if (value > 1.0)
		return value - 1.0;
	else	return value;
}



double
HSL::mapSaturation(int range, double value)
{
	double v = m_saturation[AllHues] + m_saturation[range];

	/* This change affects the way saturation is computed. With the old
	 * code (different code for value < 0), increasing the saturation
	 * affected muted colors very much, and bright colors less. With the
	 * new code, it affects muted colors and bright colors more or less
	 * evenly. For enhancing the color in photos, the new behavior is
	 * exactly what you want. It's hard for me to imagine a case in
	 * which the old behavior is better.
	 */
	value *= (v + 1.0);

	return CLIP(value, 0.0, 1.0);
}



double
HSL::mapLightness(int range, double value)
{
	double v = (m_lightness[AllHues] + m_lightness[range]) / 2.0;

	if (v < 0)
		return value * (v + 1.0);
	else	return value + (v * (1.0 - value));
}



void
HSL::adjustHueSaturation(const QImage &in, QImage &out)
{
	// error checking
	if(in.isNull())
		return;

	int	W = in.width();
	int	H = in.height();
	double	h = 0, s = 0, l = 0;
	float	overlap;

	overlap = m_overlap / 2.0;

	// error checking: in image must be same size as the out image
	if(out.width() != W || out.height() != H)
		out = QImage(W, H, QImage::Format_RGB32);

	// apply lookup table to source image to make input image
	for(int y=0; y<H; y++) {
		const QRgb *src = (const QRgb*) in.scanLine(y);
		QRgb *trg  = (QRgb*) out.scanLine(y);
		for(int x=0; x<W; x++) {
			double	hh;
			int     hue_counter;
			int     hue                 = 0;
			int     secondary_hue       = 0;
			bool	use_secondary_hue   = false;
			float   primary_intensity   = 0.0;
			float   secondary_intensity = 0.0;

			RGBToHSL(src[x], h, s, l);

			hh = h * 6.0;
			for (hue_counter=0; hue_counter<7; hue_counter++) {
				double hue_threshold = (double) hue_counter +
					0.5;
				if (hh < ((double) hue_threshold + overlap)) {
					hue = hue_counter;
					if (overlap > 0.0 &&
					    h > ((double) hue_threshold -
						 overlap)) {
						use_secondary_hue = true;
						secondary_hue = hue_counter + 1;
						secondary_intensity =
							(hh - (double)
							 hue_threshold +
							 overlap) /
							(2.0 * overlap);
						primary_intensity = 1.0 -
							secondary_intensity;
					}else {
						use_secondary_hue = false;
					}
					break;
				}
			}
			if (hue >= 6) {
				hue = 0;
				use_secondary_hue = false;
			}
			if (secondary_hue >= 6) {
				secondary_hue = 0;
			}
			/*  transform into GimpHueRange values  */
			hue++;
			secondary_hue++;
			if (use_secondary_hue) {
				double mapped_primary_hue;
				double mapped_secondary_hue;
				double diff;

				mapped_primary_hue   = mapHue (hue, h);
				mapped_secondary_hue = mapHue (secondary_hue,
							       h);

				/* Find nearest hue on the circle
				 * between primary and secondary hue
				 */
				diff = mapped_primary_hue -
					mapped_secondary_hue;
				if (diff < -0.5) {
					mapped_secondary_hue -= 1.0;
				} else if (diff >= 0.5) {
					mapped_secondary_hue += 1.0;
				}

				h = (mapped_primary_hue * primary_intensity +
				     mapped_secondary_hue*secondary_intensity);
				s = (mapSaturation (hue, s) *
				     primary_intensity +
				     mapSaturation (secondary_hue, s) *
				     secondary_intensity);

				l = (mapLightness (hue, l) *
				     primary_intensity +
				     mapLightness (secondary_hue, l) *
				     secondary_intensity);
			} else {
				h = mapHue        (hue, h);
				s = mapSaturation (hue, s);
				l = mapLightness  (hue, l);
			}

			HSLToRGB(h, s, l, trg[x]);
		}
	}
}
