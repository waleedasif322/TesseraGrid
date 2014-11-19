#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBox>
#include <QToolBar>
#include <QTabWidget>
#include <QHBoxLayout>
#include "TesseraParameters.h"
#include "ControlPanel.h"
#include "ImageWindow.h"
#include "tileconverter.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
    MainWindow();
    TesseraParameters& parameters();
    TileConverter& TilesMaker();
    void updateInputFrame();
    void updateOutputFrame();

    protected:
    //void closeEvent(QCloseEvent *event);

    private slots:

    //THE FOLLOWING IS FUNCTIONALITY PROVIDED BY THE FILE BUTTON
    void newProject();
    void openExamples();
    void loadProject();
    void save();
    void saveAs();
    void savePalette();
    void loadPalette();
    void Export();
    void quit();

    //THE FOLLOWING IS FUNCTIONALITY PROVIDED BY THE EDIT BUTTON
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void fillSelection();
    void blendTool();
    void copyCurrentlayer();
    void resetAllparameters();
    void cropInput();
    void cropOutput();

    //THE FOLLOWING IS THE FUNCTIONALITY PROVIDED BY THE VIEW BUTTON
    void zoomIn();
    void zoomOut();
    void fitWindow();
    void fullScreen();
    void toggleSections();
    void showLayermanager();
    void input();
    void output();
    void palette();
    void info();

    private:

    void createActions();
    void createMenus();
    void createToolbars();
    void createWidgets();

    QTabWidget *MainTabWidget;
    ImageWindow *TabInput;
    ImageWindow *TabOutput;
    QWidget *TabPalette;
    QWidget *TabInfo;

    QHBoxLayout *mainHBox;


    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;

    QToolBar *fileToolBar;
    //QToolBar *editToolBar;
    QToolBar *viewToolBar;

    //QACTIONS FOR FILE MENU
    QAction *ActionNewProject;
    QAction *ActionOpenExamples;
    QAction *ActionLoadProject;
    QAction *ActionSave;
    QAction *ActionSaveAs;
    QAction *ActionSavePalette;
    QAction *ActionLoadPalette;
    QAction *ActionExport;
    QAction *ActionQuit;

    //QACTIONS FOR EDIT MENU
    QAction *ActionUndo;
    QAction *ActionRedo;
    QAction *ActionCut;
    QAction *ActionCopy;
    QAction *ActionPaste;
    QAction *ActionFillSelection;
    QAction *ActionBlendTool;
    QAction *ActionCopyCurrentLayer;
    QAction *ActionResetAllParameters;
    QAction *ActionCropInput;
    QAction *ActionCropOutput;

    //QACTIONS FOR VIEW MENU
    QAction *ActionZoomIn;
    QAction *ActionZoomOut;
    QAction *ActionFitWindow;
    QAction *ActionFullScreen;
    QAction *ActionToggleSelections;
    QAction *ActionShowLayerManager;
    QAction *ActionInput;
    QAction *ActionOutput;
    QAction *ActionPalette;
    QAction *ActionInfo;

    ControlPanel *control_panel;
   // ImageWindow *m_frameInput;
    QString     m_currentInDir;
    TesseraParameters   m_params;
    TileConverter m_tiles;
    int m_count;
    QList<QImage> zoomDB;
    QImage temp;


};

#endif // MAINWINDOW_H
