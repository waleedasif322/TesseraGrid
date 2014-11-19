#include <QtGui>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QWidget>
#include <QTabWidget>
#include "MainWindow.h"
#include "qtabwidget.h"
#include "ControlPanel.h"
#include <QIcon>
#include "Globals.h"
#include "tileconverter.h"

using namespace std;

MainWindow *g_mainWindow = NULL;

MainWindow::MainWindow()
{
    setWindowTitle("TesseraGrid by Ahmed Yahya & Waleed Asif. All rights reserved.");
    setWindowIcon(QIcon(":/tools/tool-pencil-22.png"));
    createActions();
    createMenus();
    createToolbars();
    createWidgets();
    setMinimumSize(800, 600);
    setSizePolicy(QSizePolicy::Expanding,
                  QSizePolicy::Expanding);
    resize(900,800);
    //Set Size Policies and Add Fillers
    //Set Tab Widget as central widget
    g_mainWindow = this;
}

void MainWindow::createActions()
{
    //Create all Buttons and Menu Items
    //File Button Beginning
    ActionNewProject                    = new QAction(("&New Project"), this);
    ActionNewProject->                  setShortcut(QKeySequence::New);
    ActionNewProject->                  setIcon(QIcon(":/tools/new.png"));
    ActionNewProject->                  setIconVisibleInMenu(true);
    connect(ActionNewProject, SIGNAL(triggered()),
            this, SLOT(newProject()));

    ActionOpenExamples                  = new QAction(("&Open Examples"), this);
    ActionOpenExamples->                setShortcut(QKeySequence::Open);
    ActionOpenExamples->                setIcon(QIcon(":/tools/file-load.png"));
    connect(ActionOpenExamples, SIGNAL(triggered()),
            this, SLOT(openExamples()));

    ActionLoadProject                   = new QAction(("&Load Project"), this);
    ActionLoadProject->                 setShortcut(tr("Ctrl+L"));
    connect(ActionLoadProject, SIGNAL(triggered()),
            this, SLOT(loadProject()));

    ActionSave = new QAction(("&Save"), this);
    ActionSave->setShortcut(tr("Ctrl+S"));
    ActionSave->setIcon(QIcon(":/tools/file-save.png"));
    connect(ActionSave, SIGNAL(triggered()), this, SLOT(save()));

    ActionSaveAs = new QAction(("Save As..."), this);
    ActionSaveAs->setShortcut(tr("Ctrl+Shift+S"));
    connect(ActionSaveAs, SIGNAL(triggered()), this, SLOT(saveAs()));

    ActionSavePalette = new QAction(("Save Palette"), this);
    ActionSavePalette->setShortcut(tr("Ctrl+P"));
    connect(ActionSavePalette, SIGNAL(triggered()), this, SLOT(savePalette()));

    ActionLoadPalette = new QAction(("Load Palette"), this);
    ActionLoadPalette->setShortcut(tr("Ctrl+G"));
    connect(ActionLoadPalette, SIGNAL(triggered()), this, SLOT(loadPalette()));

    ActionExport = new QAction (("&Export"), this);
    ActionExport->setShortcut(tr("Ctrl+E"));
    connect(ActionExport, SIGNAL(triggered()), this, SLOT(Export()));

    ActionQuit = new QAction (("&Quit"), this);
    ActionQuit->setShortcut(QKeySequence::Quit);
    connect(ActionQuit, SIGNAL(triggered()), this, SLOT(quit()));
    //File Button...end

    //Edit Button...beginning
    ActionUndo = new QAction(("Undo"), this);
    ActionUndo->setShortcut(tr("Ctrl+Z"));
    connect(ActionUndo, SIGNAL(triggered()), this, SLOT(undo()));

    ActionRedo = new QAction(("&Redo"), this);
    ActionRedo->setShortcut(tr("Ctrl+Y"));
    connect(ActionRedo, SIGNAL(triggered()), this, SLOT(redo()));

    ActionCut = new QAction(("Cut"), this);
    ActionCut->setShortcut(tr("Ctrl+X"));
    connect(ActionCut, SIGNAL(triggered()), this, SLOT(cut()));

    ActionCopy = new QAction(("&Copy"), this);
    ActionCopy->setShortcut(tr("Ctrl+C"));
    connect(ActionCopy, SIGNAL(triggered()), this, SLOT(copy()));

    ActionPaste = new QAction (("Paste"), this);
    ActionPaste->setShortcut(tr("Ctrl+V"));
    connect(ActionPaste, SIGNAL(triggered()), this, SLOT(paste()));

    ActionFillSelection = new QAction(("Fill Selection"), this);
    ActionFillSelection->setShortcut(tr("Ctrl+I"));
    connect(ActionFillSelection, SIGNAL(triggered()), this, SLOT(fillSelection()));

    ActionBlendTool = new QAction(("Blend Tool"), this);
    ActionBlendTool->setShortcut(tr("Ctrl+D"));
    connect(ActionBlendTool, SIGNAL(triggered()), this, SLOT(blendTool()));

    ActionCopyCurrentLayer = new QAction(("Copy Current Layer"), this);
    ActionCopyCurrentLayer->setShortcut(tr("Ctrl+Shift+C"));
    connect(ActionCopyCurrentLayer, SIGNAL(triggered()), this, SLOT(copyCurrentlayer()));

    ActionResetAllParameters = new QAction(("Reset All Parameters"), this);
    ActionResetAllParameters->setShortcut(tr("Ctrl+A"));
    connect(ActionResetAllParameters, SIGNAL(triggered()), this, SLOT(resetAllparameters()));

    ActionCropInput = new QAction(("Crop Input"), this);
    ActionCropInput->setShortcut(tr("Ctrl+R"));
    connect(ActionCropInput, SIGNAL(triggered()), this, SLOT(cropInput()));

    ActionCropOutput = new QAction(("Crop Output"), this);
    ActionCropOutput->setShortcut(tr("Ctrl+T"));
    connect(ActionCropOutput, SIGNAL(triggered()), this, SLOT(cropOutput()));
    //Edit Button...end

    //View Button...beginning
    ActionZoomIn = new QAction(("Zoom In"), this);
    ActionZoomIn->setShortcut(tr("Ctrl+="));
    ActionZoomIn->setIcon(QIcon(":/tools/zoomin.png"));
    connect(ActionZoomIn, SIGNAL(triggered()), this, SLOT(zoomIn()));

    ActionZoomOut = new QAction(("Zoom Out"), this);
    ActionZoomOut->setShortcut(tr("Ctrl+-"));
    ActionZoomOut->setIcon(QIcon(":/tools/zoomout.png"));
    connect(ActionZoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()));

    ActionFitWindow = new QAction(("Fit Window"), this);
    ActionFitWindow->setShortcut(tr("Ctrl+W"));
    connect(ActionFitWindow, SIGNAL(triggered()), this, SLOT(fitWindow()));

    ActionFullScreen = new QAction(("FullScreen"), this);
    ActionFullScreen->setShortcut(tr("Ctrl+F"));
    connect(ActionFullScreen, SIGNAL(triggered()), this, SLOT(fullScreen()));

    ActionToggleSelections = new QAction(("Toggle Selections"), this);
    ActionToggleSelections->setShortcut(tr("Ctrl+B"));
    connect(ActionToggleSelections, SIGNAL(triggered()), this, SLOT(toggleSections()));

    ActionShowLayerManager = new QAction(("Show Layer Manager"), this);
    ActionShowLayerManager->setShortcut(tr("Ctrl+M"));
    ActionShowLayerManager->setIcon(QIcon(":/tools/view-layer-manager.png"));
    connect(ActionShowLayerManager, SIGNAL(triggered()), this, SLOT(showLayermanager()));

    ActionInput = new QAction(("Input"), this);
    ActionInput->setShortcut(tr("1"));
    connect(ActionInput, SIGNAL(triggered()), this, SLOT(input()));

    ActionOutput = new QAction(("Output"), this);
    ActionOutput->setShortcut(tr("2"));
    connect(ActionOutput, SIGNAL(triggered()), this, SLOT(output()));

    ActionPalette = new QAction(("Palette"), this);
    ActionPalette->setShortcut(tr("3"));
    connect(ActionPalette, SIGNAL(triggered()), this, SLOT(palette()));

    ActionInfo = new QAction(("Info"), this);
    ActionInfo->setShortcut(tr("4"));
    connect(ActionInfo, SIGNAL(triggered()), this, SLOT(info()));
    //View Button...end

}

void MainWindow::createMenus()
{
    //CREATE FILE MENU IN MENU BAR
    fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(ActionNewProject);
    fileMenu->addAction(ActionOpenExamples);
    fileMenu->addAction(ActionLoadProject);
    fileMenu->addSeparator();
    fileMenu->addAction(ActionSave);
    fileMenu->addAction(ActionSaveAs);
    fileMenu->addSeparator();
    fileMenu->addAction(ActionSavePalette);
    fileMenu->addAction(ActionLoadPalette);
    fileMenu->addSeparator();
    fileMenu->addAction(ActionExport);
    fileMenu->addSeparator();
    fileMenu->addAction(ActionQuit);

    //CREATE EDIT MENU IN MENU BAR
    editMenu = menuBar()->addMenu("Edit");
    editMenu->addAction(ActionUndo);
    editMenu->addAction(ActionRedo);
    editMenu->addSeparator();
    editMenu->addAction(ActionCut);
    editMenu->addAction(ActionCopy);
    editMenu->addAction(ActionPaste);
    editMenu->addAction(ActionFillSelection);
    editMenu->addAction(ActionBlendTool);
    editMenu->addAction(ActionCopyCurrentLayer);
    editMenu->addSeparator();
    editMenu->addAction(ActionResetAllParameters);
    editMenu->addSeparator();
    editMenu->addAction(ActionCropInput);
    editMenu->addAction(ActionCropOutput);

    //CREATE VIEW MENU IN MENU BAR
    viewMenu = menuBar()->addMenu("View");
    viewMenu->addAction(ActionZoomIn);
    viewMenu->addAction(ActionZoomOut);
    viewMenu->addAction(ActionFitWindow);
    viewMenu->addAction(ActionFullScreen);
    viewMenu->addSeparator();
    viewMenu->addAction(ActionToggleSelections);
    viewMenu->addAction(ActionShowLayerManager);
    viewMenu->addSeparator();
    viewMenu->addAction(ActionInput);
    viewMenu->addAction(ActionOutput);
    viewMenu->addAction(ActionPalette);
    viewMenu->addAction(ActionInfo);

}

void MainWindow::createToolbars() // toolbars for common actions
{
    fileToolBar = addToolBar("File");
    fileToolBar->addAction(ActionNewProject);
    fileToolBar->addAction(ActionOpenExamples);
    fileToolBar->addAction(ActionSave);


    viewToolBar = addToolBar("View");
    viewToolBar->addAction(ActionZoomIn);
    viewToolBar->addAction(ActionZoomOut);
    viewToolBar->addAction(ActionShowLayerManager);
}

void MainWindow::createWidgets() //Create Main tabs and control panel
{

    QHBoxLayout *main_HBox  = new QHBoxLayout();
    control_panel           = new ControlPanel();
    control_panel->         setHeaderHidden(true);  //to remove the bar that appears on control panel
    control_panel->         setMinimumWidth(400);
    control_panel->         setSizePolicy(QSizePolicy::Expanding,
                                          QSizePolicy::Expanding);
    MainTabWidget           = new QTabWidget();
    TabInput                = new ImageWindow();
    TabOutput               = new ImageWindow();
    TabPalette              = new QWidget();
    TabInfo                 = new QWidget();
    MainTabWidget->         setMinimumSize(400, 400);
    MainTabWidget->         addTab(TabInput, "Input");
    MainTabWidget->         addTab(TabOutput, "Output");
    MainTabWidget->         addTab(TabPalette, "Palette");
    MainTabWidget->         addTab(TabInfo, "Info");
    main_HBox->             addWidget(MainTabWidget);
    main_HBox->             addWidget(control_panel);
    QWidget *w              = new QWidget;
    w->                     setLayout(main_HBox);
    QSplitter *splitter     = new QSplitter(this);
    splitter->              addWidget(MainTabWidget);
    splitter->              addWidget(control_panel);
    setCentralWidget(splitter);
}

void MainWindow::updateInputFrame()
{
    TabInput->setImage(m_params.image());
}

void MainWindow::updateOutputFrame()
{
    TabOutput->setImage(m_tiles.tiledImage()); //should return final mosaic
}

TesseraParameters& MainWindow::parameters()
{
    return m_params;
}
TileConverter& MainWindow::TilesMaker()
{
    return m_tiles;
}

//File Functionality
void MainWindow::newProject(){

    QFileDialog dialog(this);

        // open the last known working directory
        if(!m_currentInDir.isEmpty())
            dialog.setDirectory("/Desktop");

        // display existing files and directories
        dialog.setFileMode(QFileDialog::ExistingFile);

        // invoke native file browser to select file
        QString sel("Images");
        QString file =  dialog.getOpenFileName(this,
                     "Open File", m_currentInDir,
                     "Images (*.jpg *.jpeg *.png *.bmp *.tiff *.tif);;"
                      "All files (*)", &sel);

        // no file selected.. return
        if(file.isNull())
            return;

        // update location of current directory
        m_currentInDir = QFileInfo(file).dir().absolutePath();

        // load input image
        QImage image = QImage(file);

        // check whether image could be read
        if(image.isNull()) {
          //  QMessageBox::critical( , "Error", "False!");
            return;
        }
        m_params.reset();
        m_params.setOriginalImage(image);
        m_params.setImage(image);
        control_panel->resetControls();
        updateInputFrame();
        m_tiles.reset();
        m_tiles.setOriginalImage(image);
        m_tiles.drawImage();
        updateOutputFrame();
}
void MainWindow::openExamples(){}
void MainWindow::loadProject(){}
void MainWindow::save(){

   /* QFileDialog dialog(this);
    dialog.setDirectory("/Desktop");
    dialog.setFileMode(QFileDialog::AnyFile);
    */
    QImage save;
    save = m_tiles.m_outImage;
    save.save("final.jpg");

}
void MainWindow::saveAs(){}
void MainWindow::savePalette(){}
void MainWindow::loadPalette(){}
void MainWindow::Export(){}
void MainWindow::quit()
{
    exit(1);
}

//Edit Functionality
void MainWindow::undo(){}
void MainWindow::redo(){}
void MainWindow::cut(){}
void MainWindow::copy(){}
void MainWindow::paste(){}
void MainWindow::fillSelection(){}
void MainWindow::blendTool(){}
void MainWindow::copyCurrentlayer(){}
void MainWindow::resetAllparameters(){}
void MainWindow::cropInput(){}
void MainWindow::cropOutput(){}

//View Functionality
void MainWindow::zoomIn()
{
    temp = m_tiles.tiledImage();
    TileConverter &params = g_mainWindow->TilesMaker();
    const QImage &image = params.tiledImage();
    QImage ZoomedImage = image;
    if(ZoomedImage == temp)
    {

        m_count = 0;
        zoomDB << temp;
        m_count++;
    }
    int factor = 2;
    int width = ZoomedImage.width();
    int height = ZoomedImage.height();
    int zoomedW = width/factor;
    int zoomedH = height/factor;
    int x = (width-zoomedW)/2;
    int y = (height-zoomedH)/2;
    ZoomedImage = ZoomedImage.copy(x, y, zoomedW, zoomedH);
    zoomDB << ZoomedImage;
    m_count++;

    params.setImage(ZoomedImage);
    g_mainWindow->updateOutputFrame();
    //TabOutput->H->setVisible(true);
    //TabOutput->H->setValue(int(factor*TabOutput->H->value() + (factor-1) * TabOutput->H->pageStep()/2));


}

void MainWindow::zoomOut()
{
    QImage zoomOutImage;
    if(m_count > 0){
        zoomOutImage = zoomDB[m_count - 1];
        m_count--;
    }
    TileConverter &params = g_mainWindow->TilesMaker();
    params.setImage(zoomOutImage);
    g_mainWindow->updateOutputFrame();
}
void MainWindow::fitWindow(){}
void MainWindow::fullScreen(){}
void MainWindow::toggleSections(){}
void MainWindow::showLayermanager(){}
void MainWindow::input(){}
void MainWindow::output(){}
void MainWindow::palette(){}
void MainWindow::info(){}



