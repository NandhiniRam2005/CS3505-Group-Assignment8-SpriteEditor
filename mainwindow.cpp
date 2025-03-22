#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(MainModel* model,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    selectedTool = Brush;
    ui->layerOne->setProperty("layerNumber", 1);

    //connections

    //Save/Load
    connect(ui->actionLoad, &QAction::triggered, model, &MainModel::loadJSON);
    connect(ui->actionSave, &QAction::triggered, model, &MainModel::saveJSON);

    //Add delete frames
    connect(ui->previousFrameButton, &QPushButton::clicked, model, &MainModel::previousFrame);
    connect(ui->nextFrameButton, &QPushButton::clicked, model, &MainModel::nextFrame);
    connect(ui->deleteFrameButton, &QPushButton::clicked, model, &MainModel::deleteFrame);
    connect(ui->addFrameButton, &QPushButton::clicked, this, &MainWindow::addFrameHelper);

    //Add delete layers
    connect(ui->addLayerButton, &QPushButton::clicked, model, &MainModel::addLayer);
    connect(this, &MainWindow::addFrame, model, &MainModel::addFrame);
    connect(ui->deleteLayerButton, &QPushButton::clicked, model, &MainModel::deleteLayer);

    //Select layers they will be dynamically created and connected else where.
    connect(ui->layerOne, &QPushButton::clicked, this, [this]() {
        int layerNumber = ui->layerOne->property("layerNumber").toInt();
        onLayerButtonClicked(layerNumber);
    });

    //Change fps
    connect(ui->fpsSlider, &QSlider::sliderMoved, model, &MainModel::changeAnimationFPS);

    //Transformations
    connect(ui->reflectHorizontalButto, &QPushButton::clicked, model, &MainModel::reflectHorizontal);
    connect(ui->reflectVerticalButton, &QPushButton::clicked, model, &MainModel::reflectVertical);
    connect(ui->rotateButton, &QPushButton::clicked, model, &MainModel::rotate90);

    //Update displays
    connect(model, &MainModel::newDisplayImage, ui->mainDrawing, &PixelDisplay::updateDrawnImage);
    connect(model, &MainModel::newDisplayImage, ui->animationDisplay, &PixelDisplay::updateDrawnImage);
    connect(model, &MainModel::newDisplayImage, ui->frameDisplay, &PixelDisplay::updateDrawnImage);

    //Update color
    connect(ui->colorButton, &QPushButton::clicked, this, &MainWindow::openColorDialogue);
    connect(this, &MainWindow::changeColor, this, &MainWindow::displayColorChange);
    connect(this, &MainWindow::changeColor, model, &MainModel::changeSelectedColor);

    //Frame being copied?
    connect(ui->copyFrameButton, &QRadioButton::clicked, this, &MainWindow::setFrameCopyVariable);

    //Set tools
    connect(ui->brushButton, &QPushButton::clicked, this, &MainWindow::setToolToBrush);
    connect(ui->eyeDropperButton, &QPushButton::clicked, this, &MainWindow::setToolToEyeDropper);
    connect(ui->paintBucketButton, &QPushButton::clicked, this, &MainWindow::setToolToBucket);
    connect(ui->eraserButton, &QPushButton::clicked, this, &MainWindow::setToolToEraser);

    //Drawing connections NOT DONE

    //Set brush size connections NOT DONE:
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayColorChange(Pixel pixel) {
    // TODO: Implement displayColorChange
}

void MainWindow::displayLoadStatus(bool status) {
    // TODO: Implement displayLoadStatus
}

void MainWindow::displaySaveStatus(bool status) {
    // TODO: Implement displaySaveStatus
}

void MainWindow::openColorDialogue() {
    // TODO: Implement openColorDialogue
}

void MainWindow::setFrameCopyVariable() {
    // TODO: Implement setFrameCopyVariable
}

void MainWindow::addFrameHelper() {
    // TODO: Implement addFrameHelper
}

void MainWindow::setToolToBrush() {
    // TODO: Implement setToolToBrush
}

void MainWindow::setToolToBucket() {
    // TODO: Implement setToolToBucket
}

void MainWindow::setToolToEraser() {
    // TODO: Implement setToolToEraser
}

void MainWindow::setToolToEyeDropper() {
    // TODO: Implement setToolToEyeDropper
}

void MainWindow::onLayerButtonClicked(int layerNumber) {
    // TODO: Implement onLayerButtonClicked
}

QPoint MainWindow::mapClickLocationToGridCoordinate(unsigned int x, unsigned int y){

}

// WE NEED TO ADD A SLOT for adding buttons dynamically for layers

