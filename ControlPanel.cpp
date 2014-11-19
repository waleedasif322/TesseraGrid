#include <QtGui>
#include <QTreeWidget>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QLabel>
#include <QAction>
#include <QSizePolicy>
#include "ControlPanel.h"
#include "qsizepolicy.h"
#include <QStackedWidget>
#include <QGroupBox>
#include <QGridLayout>
#include "MainWindow.h"
#include "Globals.h"
#include <iostream>
#include <QList>
#include <HSL.h>

using namespace std;

ControlPanel::ControlPanel()
{
    populate();
    createActions_C();
    createVBox();
    createTree();
}

void ControlPanel::createActions_C()
{

    connect(Slider_brightness, SIGNAL(sliderMoved(int)), this, SLOT(s_sliderValueBrightness(int)));
    connect(Slider_contrast, SIGNAL(sliderMoved(int)), this, SLOT(s_sliderValueContrast(int)));
    connect(Slider_hue, SIGNAL(sliderMoved(int)), this, SLOT(s_sliderValueHue(int)));
    connect(Slider_saturation, SIGNAL(sliderMoved(int)), this, SLOT(s_sliderValueSaturation(int)));
    connect(Slider_Lightness, SIGNAL(sliderMoved(int)), this, SLOT(s_sliderValueBrightness(int)));
    connect(sliderDither, SIGNAL(sliderMoved(int)), this, SLOT(s_sliderValueDither(int)));

    connect(Button_resetBrightness, SIGNAL(clicked()), this, SLOT(s_resetBrightness()));
    connect(Button_resetContrast, SIGNAL(clicked()), this, SLOT(s_resetContrast()));
    connect(Button_resetHue, SIGNAL(clicked()), this, SLOT(s_resetHue()));
    connect(Button_resetSaturation, SIGNAL(clicked()), this, SLOT(s_resetSaturation()));
    connect(Button_resetLightness, SIGNAL(clicked()), this, SLOT(s_resetLightness()));
    connect(Button_revertOriginal_BC, SIGNAL(clicked()), this, SLOT(s_revertOriginalBC()));
   // connect(Button_revertOriginal_HS, SIGNAL(clicked()), this, SLOT(s_revertOriginalHS()));
}

void ControlPanel::populate()
{
    Slider_brightness       = new QSlider(Qt::Horizontal);
    Slider_brightness->     setRange(-128, 128);
    Slider_brightness->     setValue(0);
    //Slider_brightness     ->setSizePolicy(QSizePolicy::Fixed);

    Slider_contrast         = new QSlider(Qt::Horizontal);
    Slider_contrast->       setRange(-100, 100);
    Slider_contrast->       setValue(0);
    //Slider_contrast       ->setSizePolicy(QSizePolicy::Fixed);

    Slider_hue              = new QSlider(Qt::Horizontal);
    Slider_hue->            setRange(-180, 180);
    Slider_hue->            setValue(0);

    Slider_saturation =     new QSlider(Qt::Horizontal);
    Slider_saturation->     setRange(-100, 100);
    Slider_saturation->     setValue(0);

    Slider_Lightness =      new QSlider(Qt::Horizontal);
    Slider_Lightness->      setRange(-100, 100);
    Slider_Lightness->      setValue(0);

    sliderDither =          new QSlider(Qt::Horizontal);
    sliderDither->          setRange(0, 100);
    sliderDither->          setValue(0);


    spinboxStyle =          new QSpinBox();
    spinboxStyle->          setValue(0);

    RButton_brightnessContrast  = new QRadioButton("Brightness-Contrast");
    RButton_brightnessContrast  ->setChecked(true);
    RButton_hueSaturation       = new QRadioButton("Hue-Saturation");

    buttonUS                    = new QRadioButton("US");
    buttonUS->                  setChecked(true);
    buttonMetric                = new QRadioButton("Metric");
    buttonTiles                 = new QRadioButton("Tiles");

    LabelValue_brightness       = new QLabel("0");
    LabelValue_contrast         = new QLabel("0");
    LabelValue_hue              = new QLabel("0");
    LabelValue_saturation       = new QLabel("0");
    LabelValue_lightness        = new QLabel("0");
    labelValueDither                 = new QLabel("0");

    Label_brightness            = new QLabel("Brightness");
    Label_contrast              = new QLabel("Contrast");
    Label_hue                   = new QLabel("Hue");
    Label_saturation            = new QLabel("Saturation");
    Label_Lightness             = new QLabel("Lightness");

    labelDither                 = new QLabel("Dither");
    labelStyle                  = new QLabel("Style");

    labelWidth                  = new QLabel("Width");
    labelHeight                 = new QLabel("Height");
    widthInches                 = new QLabel("in");
    heightInches                = new QLabel("in");

    tfWidth                     = new QLineEdit("Default");
    tfHeight                    = new QLineEdit("Default");

    Button_resetBrightness      = new QPushButton("Reset");
    Button_resetContrast        = new QPushButton("Reset");
    Button_resetHue             = new QPushButton("Reset");
    Button_resetSaturation      = new QPushButton("Reset");
    Button_resetLightness       = new QPushButton("Reset");
    Button_revertOriginal_BC    = new QPushButton("Reset to Original");
    Button_resetBrightness      ->setFixedWidth(70);
    Button_resetContrast        ->setFixedWidth(70);
    Button_resetHue             ->setFixedWidth(70);
    Button_resetSaturation      ->setFixedWidth(70);
    Button_resetLightness       ->setFixedWidth(70);

}

void ControlPanel::createVBox()
{
    /*
//   Instead of the Qgroupbox below, use a widget, and add all to widget after code
    gridWidget = new QWidget;
    BCGrid = new QGridLayout(gridWidget);
   // BCGrid->setRowMinimumHeight(4, 1);
    //BCGrid->setColumnMinimumWidth(4, 1);
    BCGrid->setSpacing(10);
    BCGrid->addWidget(RButton_brightnessContrast, 0, 0);
    BCGrid->addWidget(RButton_hueSaturation, 0, 4);
    BCGrid->addWidget(Label_brightness, 1,0);
    BCGrid->addWidget(Slider_brightness, 1,1, 2, 10);
    //BCGrid->setHorizontalSpacing(5);
    BCGrid->addWidget(LabelValue_brightness, 1, 2);
    BCGrid->addWidget(Button_resetBrightness, 1, 3);
    //BCGrid->setColumnStretch(0,15);
    //BCGrid->setColumnStretch(1,15);
    //BCGrid->setColumnStretch(2,10);
    //BCGrid->setColumnStretch(3,10);
*/

    //Radio Buttons
    m_stackWidget           = new QStackedWidget;
    RadioGroupBox           = new QGroupBox; // use buttonbox instead
    QHBoxLayout *RHBox      = new QHBoxLayout;
    RHBox->                 addWidget(RButton_brightnessContrast);
    RHBox->                 addWidget(RButton_hueSaturation);
    RHBox->                 addStretch(1);
    RadioGroupBox->         setLayout(RHBox);

    HBox_brightness         = new QHBoxLayout();
    HBox_brightness->       addWidget(Label_brightness);
    HBox_brightness->       addWidget(Slider_brightness);
    HBox_brightness->       addWidget(LabelValue_brightness);
    HBox_brightness->       addWidget(Button_resetBrightness);
    w_brightness            = new QWidget;
    w_brightness->          setLayout(HBox_brightness);

    HBox_contrast           = new QHBoxLayout();
    HBox_contrast->         addWidget(Label_contrast);
    HBox_contrast->         addWidget(Slider_contrast);
    HBox_contrast->         addWidget(LabelValue_contrast);
    HBox_contrast->         addWidget(Button_resetContrast);
    w_contrast =            new QWidget;
    w_contrast->            setLayout(HBox_contrast);

    VBox_inputSettingsBC    = new QVBoxLayout();
    //VBox_inputSettingsBC  ->addWidget(RadioGroupBox);
    VBox_inputSettingsBC->  addWidget(w_brightness);
    VBox_inputSettingsBC->  addWidget(w_contrast);
    //VBox_inputSettingsBC  ->addWidget(Button_revertOriginal_BC);
    w_inputSettingsBC       = new QWidget;
    w_inputSettingsBC->     setLayout(VBox_inputSettingsBC);
    m_stackWidget->         addWidget(w_inputSettingsBC);
    
    //GroupBox              = new QWidget;
    //GroupBox->            setLayout(BCGrid);
    QHBoxLayout *HBox_hue   = new QHBoxLayout();
    HBox_hue->              addWidget(Label_hue);
    HBox_hue->              addWidget(Slider_hue);
    HBox_hue->              addWidget(LabelValue_hue);
    HBox_hue->              addWidget(Button_resetHue);
    QWidget *w_hue          = new QWidget;
    w_hue->                 setLayout(HBox_hue);

    QHBoxLayout *HBox_saturation    = new QHBoxLayout();
    HBox_saturation->               addWidget(Label_saturation);
    HBox_saturation->               addWidget(Slider_saturation);
    HBox_saturation->               addWidget(LabelValue_saturation);
    HBox_saturation->               addWidget(Button_resetSaturation);
    QWidget *w_saturation           = new QWidget;
    w_saturation->                  setLayout(HBox_saturation);

    QHBoxLayout *HBox_Lightness     = new QHBoxLayout();
    HBox_Lightness->                addWidget(Label_Lightness);
    HBox_Lightness->                addWidget(Slider_Lightness);
    HBox_Lightness->                addWidget(LabelValue_lightness);
    HBox_Lightness->                addWidget(Button_resetLightness);
    QWidget *w_Lightness            = new QWidget;
    w_Lightness->                   setLayout(HBox_Lightness);

    VBox_inputSettingsHS            = new QVBoxLayout();
    //VBox_inputSettingsHS->        addWidget(RadioGroupBox);
    VBox_inputSettingsHS->          addWidget(w_hue);
    VBox_inputSettingsHS->          addWidget(w_saturation);
    VBox_inputSettingsHS->          addWidget(w_Lightness);
    //VBox_inputSettingsHS->        addWidget(Button_revertOriginal_HS);
    w_inputSettingsHS               = new QWidget;
    w_inputSettingsHS->             setLayout(VBox_inputSettingsHS);

    m_stackWidget->                 addWidget(w_inputSettingsHS);
    QVBoxLayout *everything         = new QVBoxLayout;
    everything->                    addWidget(RadioGroupBox);
    everything->                    addWidget(m_stackWidget);
    everything->                    addWidget(Button_revertOriginal_BC);
    final =                         new QWidget;
    final->                         setLayout(everything);

    connect(RButton_hueSaturation, SIGNAL(clicked()), this,
            SLOT(change_stack1()));
    connect(RButton_brightnessContrast, SIGNAL(clicked()), this,
            SLOT(change_stack2()));

        boxStyle =                      new QHBoxLayout;
        boxStyle->                      addWidget(labelStyle);
        boxStyle->                      addWidget(spinboxStyle);
        styleWidget =                   new QWidget;
        styleWidget->                   setLayout(boxStyle);

        boxDither =                     new QHBoxLayout;
        boxDither->                     addWidget(labelDither);
        boxDither->                     addWidget(sliderDither);
        boxDither->                     addWidget(labelValueDither);
        ditherWidget =                  new QWidget;
        ditherWidget->                  setLayout(boxDither);

        MosaicRendering =               new QHBoxLayout;
        MosaicRendering->               addWidget(styleWidget);
        MosaicRendering->               addWidget(ditherWidget);

        MRW =                           new QWidget;
        MRW->                           setLayout(MosaicRendering);
        //-----------------------------------//

        //-----------------------------------//
        rbBox =                         new QVBoxLayout();
        rbBox->                         addWidget(buttonUS);
        rbBox->                         addWidget(buttonMetric);
        rbBox->                         addWidget(buttonTiles);
        rbWidget =                      new QWidget;
        rbWidget->                      setLayout(rbBox);

        widthBox =                      new QHBoxLayout();
        widthBox->                      addWidget(labelWidth);
        widthBox->                      addWidget(tfWidth);
        widthBox->                      addWidget(widthInches);
        widthWidget =                   new QWidget;
        widthWidget ->                  setLayout(widthBox);

        heightBox =                     new QHBoxLayout();
        heightBox->                     addWidget(labelHeight);
        heightBox->                     addWidget(tfHeight);
        heightBox->                     addWidget(heightInches);
        heightWidget =                   new QWidget;
        heightWidget ->                  setLayout(heightBox);

        dimenBox =                      new QVBoxLayout();
        dimenBox->                      addWidget(widthWidget);
        dimenBox->                      addWidget(heightWidget);
        dimenWidget =                   new QWidget;
        dimenWidget->                   setLayout(dimenBox);

        MosaicSizeBox =                 new QHBoxLayout();
        MosaicSizeBox->                 addWidget(dimenWidget);
        MosaicSizeBox->                 addWidget(rbWidget);

        MSW =                           new QWidget;
        MSW ->                          setLayout(MosaicSizeBox);
        //-----------------------------------//
}

void ControlPanel::createTree()
{
    m_tree = new QTreeWidget;
    m_tree->    setHeaderHidden(true);
    m_tree->    setMinimumWidth(375);
    m_tree->    setIndentation(10);
    m_tree->    setAnimated(true);

    //make new Tree Items with parent m_tree
    Tree_inputSettings =    new QTreeWidgetItem(m_tree);
    Tree_mosaicSize =       new QTreeWidgetItem(m_tree);
    Tree_mosaicRendering =  new QTreeWidgetItem(m_tree);
    Tree_tilePalette =      new QTreeWidgetItem(m_tree);
    Tree_grout =            new QTreeWidgetItem(m_tree);

    //make new children Tree Items with parent original tree items above
    QTreeWidgetItem *inputChild =   new QTreeWidgetItem(Tree_inputSettings);
    QTreeWidgetItem *mosaicChild =  new QTreeWidgetItem(Tree_mosaicSize);
    QTreeWidgetItem *renderChild =  new QTreeWidgetItem(Tree_mosaicRendering);
    QTreeWidgetItem *tileChild =    new QTreeWidgetItem(Tree_tilePalette);
    QTreeWidgetItem *groutChild =   new QTreeWidgetItem(Tree_grout);

    //add child to parent tree item
    Tree_inputSettings->    addChild(inputChild);
    Tree_mosaicSize->       addChild(mosaicChild);
    Tree_mosaicRendering->  addChild(renderChild);
    Tree_tilePalette->      addChild(tileChild);
    Tree_grout->            addChild(groutChild);

    //set text for all tree items
    Tree_inputSettings->    setText(0, "Input Settings");
    Tree_mosaicSize->       setText(0, "Mosaic Size");
    Tree_mosaicRendering->  setText(0, "Mosaic Rendering");
    Tree_tilePalette->      setText(0, "Tile Palette");
    Tree_grout->            setText(0, "Grout");

    m_tree->                setItemWidget(inputChild, 0, final);
    m_tree->                setItemWidget(mosaicChild, 0, MSW);
    m_tree->                setItemWidget(renderChild, 0, MRW);
    //m_tree->              setItemWidget(tileChild, 0, );
    //m_tree->              setItemWidget(groutChild, 0, );

    QVBoxLayout *vbox       = new QVBoxLayout;
    vbox->                  addWidget(m_tree);
    setLayout(vbox);
}

void ControlPanel::s_resetBrightness()
{
    s_sliderValueBrightness(0);
}
void ControlPanel::s_resetContrast()
{
    s_sliderValueContrast(0);
}
void ControlPanel::s_resetHue()
{
    s_sliderValueHue(0);
}
void ControlPanel::s_resetSaturation()
{
    s_sliderValueSaturation(0);
}
void ControlPanel::s_resetLightness()
{
    s_sliderValueLightness(0);
}
void ControlPanel::s_revertOriginalBC()
{
    TesseraParameters &params   = g_mainWindow->parameters();
    const QImage &origImage     = params.originalImage();
    const QImage &curImage      = params.image();
    if(origImage.isNull() || curImage.isNull())
        return;

    g_mainWindow->              parameters().setBrightness(0);
    g_mainWindow->              parameters().setContrast	(0);
    g_mainWindow->              parameters().setHue	(0);
    g_mainWindow->              parameters().setSaturation(0);
    g_mainWindow->              parameters().setLightness	(0);
    blockSignals(true);

    s_sliderValueBrightness(0);
    s_sliderValueContrast(0);
    s_sliderValueHue(0);
    s_sliderValueLightness(0);
    s_sliderValueSaturation(0);

    blockSignals(false);

    m_image                     = origImage;
    params.setImage(            m_image);
    g_mainWindow->              parameters().setImage(m_image);
    g_mainWindow->              updateInputFrame();
}
void ControlPanel::s_revertOriginalHS() {

}
void ControlPanel::s_sliderValueBrightness(int val)
{
    blockSignals(true); 
    Slider_brightness->     setValue(val);
    LabelValue_brightness-> setText(QString::number(val));
    g_mainWindow->          parameters().setBrightness(val);
    updateInputImage(       TesseraParameters::RGB);
    blockSignals(false);
}
void ControlPanel::s_sliderValueContrast(int val)
{
    blockSignals(true);
    Slider_contrast->       setValue(val);
    LabelValue_contrast->   setText(QString::number(val));
    g_mainWindow->          parameters().setContrast(val);
    updateInputImage(       TesseraParameters::RGB);
    blockSignals(false);

}
void ControlPanel::s_sliderValueHue(int val)
{
    blockSignals(true);
    Slider_hue->        setValue(val);
    LabelValue_hue->    setText(QString::number(val));
    g_mainWindow->      parameters().setHue(val);
    updateInputImage(   TesseraParameters::HSL);
    blockSignals(false);
}
void ControlPanel::s_sliderValueSaturation(int val)
{
    blockSignals(true);
    Slider_saturation->     setValue(val);
    LabelValue_saturation-> setText(QString::number(val));
    g_mainWindow->          parameters().setSaturation(val);
    updateInputImage(       TesseraParameters::HSL);
    blockSignals(false);
}
void ControlPanel::s_sliderValueLightness(int val)
{
    blockSignals(true);
    Slider_Lightness->      setValue(val);
    LabelValue_lightness->  setText(QString::number(val));
    g_mainWindow->          parameters().setLightness(val);
    updateInputImage(       TesseraParameters::HSL);
    blockSignals(false);
}
void ControlPanel::resetControls(){}
void ControlPanel::change_stack1()
{
    m_stackWidget->setCurrentIndex(1);
}

void ControlPanel::change_stack2()
{
    m_stackWidget->setCurrentIndex(0);
}

void ControlPanel::s_sliderValueDither(int val)
{
    sliderDither        ->setValue(val);
    labelValueDither    ->setText(QString::number(val));
}

int ControlPanel::updateInputImage(TesseraParameters::ColorMode mode)
    {
        // error checking
        TesseraParameters &params = g_mainWindow->parameters();
        const QImage &origImage = params.originalImage();
        const QImage &curImage = params.image();
        if(origImage.isNull() || curImage.isNull())
            return 0;

        if(m_image.isNull())
            m_image = origImage;

        // update colormode and current image
        if(params.colorMode() != mode)
            m_image = curImage;
        params.setColorMode(mode);

        QImage inImage = m_image;
        QImage outImage;
        if(params.colorMode() == TesseraParameters::RGB) {// brightness-contrast
            // get contrast and brightness
            int	contrast	= params.contrast();
            int	brightness	= params.brightness();

            // init slope of intensity ramp
            double	c;
            if(contrast >= 0)
                c = contrast/25. + 1.0;   // slope: 1 to 5
            else	c = 1. + (contrast/133.); // slope: 1 to 0

            // init lookup table: multiply by contrast; add brightness
            int lut[256];
            for(int v=0; v<256; v++) {
                int i = (v - 128)*c + (128 + brightness);
                lut[v] = CLIP(i, 0, 255);
            }

            // init input dimensions
            int w = inImage.width ();
            int h = inImage.height();

            // create output image
            outImage = QImage(w, h, QImage::Format_RGB32);

            // apply lookup table to source image to make input image
            for(int y=0; y<h; y++) {
                const QRgb *src = (const QRgb*) inImage.scanLine(y);
                QRgb *out  = (QRgb*) outImage.scanLine(y);
                for(int x=0; x<w; x++) {
                    // set transparent pixels to white
                    if(qAlpha(src[x]) < 128) {
                        *out++ = qRgb(255, 255, 255);
                    } else {
                        *out++ = qRgb(lut[qRed  (src[x])],
                                  lut[qGreen(src[x])],
                                  lut[qBlue (src[x])]);
                    }
                }
            }
        } else {			// hue-saturation
            double h = params.hue() / 180.0;
            double s = params.saturation() / 100.0;
            double l = params.lightness() / 100.0;
            HSL hsl;
            hsl.setHue	 (HSL::AllHues, h);
            hsl.setSaturation(HSL::AllHues, s);
            hsl.setLightness (HSL::AllHues, l);
            hsl.adjustHueSaturation(inImage, outImage);
        }
        params.setImage(outImage);
        g_mainWindow->updateInputFrame();

        return 1;
    }

