#include "TesseraParameters.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TesseraParameters::TesseraParameters:
//
// Default Constructor
//
TesseraParameters::TesseraParameters()
{
    reset();
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TesseraParameters::TesseraParameters:
//
// Copy Constructor
//
TesseraParameters::TesseraParameters(const TesseraParameters &params)
    : m_origImage	(params.m_origImage),
      m_image	(params.m_image),
      m_brightness	(params.m_brightness),
      m_contrast	(params.m_contrast),
      m_hue		(params.m_hue),
      m_saturation	(params.m_saturation),
      m_lightness	(params.m_lightness),
      m_colorMode	(params.m_colorMode)
{
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TesseraParameters::operator=:
//
// Assignment operator
//
TesseraParameters&
TesseraParameters::operator=(const TesseraParameters &params)
{
    if(&params == this)
        return *this;

    // input settings
    m_origImage	= params.m_origImage;
    m_image		= params.m_image;
    m_brightness	= params.m_brightness;
    m_contrast	= params.m_contrast;
    m_hue		= params.m_hue;
    m_saturation	= params.m_saturation;
    m_lightness	= params.m_lightness;
    m_colorMode	= params.m_colorMode;

    return *this;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TesseraParameters::reset:
//
// Reset parameters to default values
//
void
TesseraParameters::reset()
{
    // input settings
    m_image		= QImage();
    m_origImage	= QImage();
    m_brightness	= 0;
    m_contrast	= 0;
    m_hue		= 0;
    m_saturation	= 0;
    m_lightness	= 0;
    m_colorMode	= RGB;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TesseraParameters::setOriginalImage:
//
// Set original input image.This image is never modified by changes
// in the brightness/contrast and hue/saturation/lightness.
//
void
TesseraParameters::setOriginalImage(const QImage &image)
{
    m_origImage = image;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TesseraParameters::
//
// Set current image, which is used to generate the mosaic. This
// image may be the cropped or color-corrected version of the "Original Image".
void
TesseraParameters::setImage(const QImage &image)
{
    m_image = image;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TesseraParameters::setBrightness:
//
// Set image brightness
//
void
TesseraParameters::setBrightness(int val)
{
    m_brightness = val;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TesseraParameters::setContrast:
//
// Set image contrast
void
TesseraParameters::setContrast(int val)
{
    m_contrast = val;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TesseraParameters::setHue:
//
// Set image hue
//
void
TesseraParameters::setHue(int val)
{
    m_hue = val;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TesseraParameters::setSaturation:
//
// Set image saturation
//
void
TesseraParameters::setSaturation(int val)
{
   m_saturation = val;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TesseraParameters::setLightness:
//
// Set image lightness
//
void
TesseraParameters::setLightness(int val)
{
   m_lightness = val;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TesseraParameters::setColorMode:
//
// Set current color mode: Brightness/Contrast vs Hue/Saturation/Lightness
//
void
TesseraParameters::setColorMode(ColorMode val)
{
   m_colorMode = val;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TesseraParameters::originalImage:
//
// Get original image
//
const QImage&
TesseraParameters::originalImage() const
{
    return m_origImage;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TesseraParameters::image:
//
// Get current image
//
const QImage&
TesseraParameters::image() const
{
   return m_image;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TesseraParameters::brightness:
//
// Get brightness
//
int
TesseraParameters::brightness() const
{
    return m_brightness;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TesseraParameters::contrast:
//
// Get contrast
//
int
TesseraParameters::contrast() const
{
    return m_contrast;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TesseraParameters::hue:
//
//! \brief	Get hue
//! \details	Get hue
//! \return	Hue
//
int
TesseraParameters::hue() const
{
    return m_hue;
}

TesseraParameters::ColorMode TesseraParameters::colorMode() const{

    return m_colorMode;
}
int TesseraParameters::saturation() const{

    return m_saturation;
}

int TesseraParameters::lightness() const{

    return m_lightness;
}

