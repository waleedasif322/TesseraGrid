#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H


#include <QTreeWidget>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QSpinBox>
#include <QLabel>
#include <QAction>

#include <QStackedWidget>
#include <QGroupBox>
#include <QGridLayout>
#include "TesseraParameters.h"
#include "tileconverter.h"

class ControlPanel : public QTreeWidget
{
    Q_OBJECT

    public:
    ControlPanel();
    //~ControlPanel();
    void resetImage();

    protected:
    //void closeEvent(QCloseEvent *event);

public slots:
        void resetControls();

//private slots:
    void s_resetBrightness();
    void s_resetContrast();
    void s_resetHue();
    void s_resetSaturation();
    void s_resetLightness();
    void s_revertOriginalBC();
    void s_revertOriginalHS();
    void s_sliderValueBrightness(int);
    void s_sliderValueContrast(int);
    void s_sliderValueHue(int);
    void s_sliderValueSaturation(int);
    void s_sliderValueLightness(int);
    void s_sliderValueDither(int);
    void change_stack1();
    void change_stack2();


    private:

    void createActions_C();
    void createVBox();
    void createTree();
    void populate();

    int updateInputImage(TesseraParameters::ColorMode mode);

    //CreateTree
    QTreeWidget *m_tree;
    QTreeWidgetItem *Tree_inputSettings;
    QTreeWidgetItem *Tree_mosaicSize;
    QTreeWidgetItem *Tree_mosaicRendering;
    QTreeWidgetItem *Tree_tilePalette;
    QTreeWidgetItem *Tree_grout;

    QVBoxLayout *VBox_mosaicSize;
    QVBoxLayout *VBox_mosaicRendering;
    QVBoxLayout *VBox_tilePalette;
    QVBoxLayout *VBox_grout;


    QPushButton *Button_resetBrightness;
    QPushButton *Button_resetContrast;
    QPushButton *Button_resetHue;
    QPushButton *Button_resetSaturation;
    QPushButton *Button_resetLightness;
    QPushButton *Button_revertOriginal_BC;
    QPushButton *Button_revertOriginal_HS;

    //CreateVBox
    QWidget *w_inputSettingsBC;
    QWidget *w_inputSettingsHS;
    QHBoxLayout *HBox_brightness;
    QWidget *w_brightness;
    QHBoxLayout *HBox_contrast;
    QWidget *w_contrast;
    QVBoxLayout *VBox_inputSettingsBC;
    QVBoxLayout *VBox_inputSettingsHS;
    QWidget *final;

    QRadioButton *RButton_brightnessContrast;
    QRadioButton *RButton_hueSaturation;

    QLabel *Label_brightness;
    QLabel *Label_contrast;
    QLabel *Label_hue;
    QLabel *Label_saturation;
    QLabel *Label_Lightness;

    QSlider *Slider_brightness;
    QSlider *Slider_contrast;
    QSlider *Slider_hue;
    QSlider *Slider_saturation;
    QSlider *Slider_Lightness;

    QLabel *LabelValue_brightness;
    QLabel *LabelValue_contrast;
    QLabel *LabelValue_hue;
    QLabel *LabelValue_saturation;
    QLabel *LabelValue_lightness;


    QStackedWidget *m_stackWidget;
    QGroupBox *RadioGroupBox;
    QGridLayout *HSGrid;
    QGridLayout *BCGrid;
    QWidget *GroupBox;
    QWidget *gridWidget;

    QImage m_image;
    QImage tileImages;

    QWidget *buttonbox;
    TileConverter convertToTiles;

    QHBoxLayout *MosaicSizeBox;
      QHBoxLayout *widthBox;
      QWidget     *widthWidget;
      QHBoxLayout *heightBox;
      QWidget     *heightWidget;
      QVBoxLayout *dimenBox;
      QWidget     *dimenWidget;
      QVBoxLayout *rbBox;
      QWidget     *rbWidget;
      QRadioButton *buttonUS;
      QRadioButton *buttonMetric;
      QRadioButton *buttonTiles;
      QLabel *labelWidth;
      QLabel *widthInches;
      QLabel *heightInches;
      QLabel *labelHeight;
      QLineEdit *tfWidth;
      QLineEdit *tfHeight;
      QWidget *MSW;
      //---------------------------//

      //-----------Done----------------//
      QHBoxLayout *MosaicRendering;
      QHBoxLayout *boxStyle;
      QWidget *styleWidget;
      QHBoxLayout *boxDither;
      QWidget *ditherWidget;
      QLabel *labelStyle;
      QLabel *labelValueDither;
      QLabel *labelDither;
      QSpinBox *spinboxStyle;
      QSlider *sliderDither;
      QWidget *MRW;
};


#endif // CONTROLPANEL_H
