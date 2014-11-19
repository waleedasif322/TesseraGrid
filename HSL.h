#ifndef HSL_H
#define HSL_H

#include "Globals.h"

class HSL {
public:
	enum HueRange	{AllHues,
			 RedHues,
			 YellowHues,
			 GreenHues,
			 CyanHues,
			 BlueHues,
			 MagentaHues};
	HSL();

	void	init			();
	void	adjustHueSaturation	(const QImage &in, QImage &out);

	void	setHue			(int range, double v);
	void	setSaturation		(int range, double v);
	void	setLightness		(int range, double v);
	void	setOverlap		(double);

	double	hue			(int range);
	double	saturation		(int range);
	double	lightness		(int range);
	double	overlap			();

protected:
	double	mapHue			(int, double);
	double	mapSaturation		(int, double);
	double	mapLightness		(int, double);

private:
	double		m_hue		[7];
	double		m_saturation	[7];
	double		m_lightness	[7];
	double		m_overlap;
};

#endif	// HSL_H
