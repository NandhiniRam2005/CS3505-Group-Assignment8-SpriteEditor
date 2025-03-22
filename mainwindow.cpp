#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(MainModel* model,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    selectedTool = Brush;
    //connections
    connect(ui->actionLoad, &QAction::triggered, model, &MainModel::loadJSON);
    connect(ui->actionSave, &QAction::triggered, model, &MainModel::saveJSON);
    connect(ui->previousFrameButton, &QPushButton::clicked, model, &MainModel::previousFrame);
    connect(ui->nextFrameButton, &QPushButton::clicked, model, &MainModel::nextFrame);
    connect(ui->deleteFrameButton, &QPushButton::clicked, model, &MainModel::deleteFrame);
    connect(ui->addFrameButton, &QPushButton::clicked, this, &MainWindow::addFrameHelper);
    connect(ui->addLayerButton, &QPushButton::clicked, model, &MainModel::addLayer);
    connect(this, &MainWindow::addFrame, model, &MainModel::addFrame);
    connect(ui->deleteLayerButton, &QPushButton::clicked, model, &MainModel::deleteLayer);
    connect(ui->fpsSlider, &QSlider::sliderMoved, model, &MainModel::changeAnimationFPS);
    connect(ui->reflectHorizontalButto, &QPushButton::clicked, model, &MainModel::reflectHorizontal);
    connect(ui->reflectVerticalButton, &QPushButton::clicked, model, &MainModel::reflectVertical);
    connect(ui->rotateButton, &QPushButton::clicked, model, &MainModel::rotate90);
    connect(model, &MainModel::newDisplayImage, ui->mainDrawing, &PixelDisplay::updateDrawnImage);
    connect(model, &MainModel::newDisplayImage, ui->animationDisplay, &PixelDisplay::updateDrawnImage);
    connect(model, &MainModel::newDisplayImage, ui->frameDisplay, &PixelDisplay::updateDrawnImage);
    connect(ui->colorButton, &QPushButton::clicked, this, &MainWindow::openColorDialogue);
    connect(this, &MainWindow::changeColor, this, &MainWindow::displayColorChange);
    connect(this, &MainWindow::changeColor, model, &MainModel::changeSelectedColor);
    connect(ui->copyFrameButton, &QRadioButton::clicked, this, &MainWindow::setFrameCopyVariable);
    connect(ui->brushButton, &QPushButton::clicked, this, &MainWindow::setToolToBrush);
    connect(ui->eyeDropperButton, &QPushButton::clicked, this, &MainWindow::setToolToEyeDropper);
    connect(ui->paintBucketButton, &QPushButton::clicked, this, &MainWindow::setToolToBucket);
    connect(ui->eraserButton, &QPushButton::clicked, this, &MainWindow::setToolToEraser);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void displayColorChange(Pixel pixel);

void displayLoadStatus(bool status);

void displaySaveStatus(bool status);

void openColorDialogue();

void updateColorDisplay(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha);

void setFrameCopyVariable();

void addFrameHelper();

void setToolToBrush();

void setToolToBucket();

void setToolToEraser();

void setToolToEyeDropper();
