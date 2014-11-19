#ifndef TESSERAPARAMETERS_H
#define TESSERAPARAMETERS_H

#include <QtGui>
#include <QtCore>

class TesseraParameters{

public:
    enum ColorMode {RGB, HSL};
    //const unsigned int RGB=1, HSL=2;

    TesseraParameters();
    TesseraParameters(const TesseraParameters &);
    TesseraParameters& operator=(const TesseraParameters &);

    void	reset	();

    void	setOriginalImage(const QImage&);
    void	setImage	(const QImage&);
    void	setBrightness	(int);
    void	setContrast	(int);
    void	setHue		(int);
    void	setSaturation	(int);
    void	setLightness	(int);
    void	setColorMode	(ColorMode);

    const QImage&	originalImage	() const;
    const QImage&	image           () const;
    int		brightness	() const;
    int		contrast	() const;
    int		hue         () const;
    int		saturation	() const;
    int		lightness	() const;
    ColorMode colorMode	() const; //change from ColorMode to int
protected:
    // input settings
    QImage		m_origImage; // original uncropped input image
    QImage		m_image;     // current cropped/color-correctd inp image

    int		m_brightness;
    int		m_contrast;
    int		m_hue;
    int		m_saturation;
    int		m_lightness;
    ColorMode	m_colorMode;

};

#endif // TESSERAPARAMETERS_H
