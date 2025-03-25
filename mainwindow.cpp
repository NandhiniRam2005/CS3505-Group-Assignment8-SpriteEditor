#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QScrollBar>
#include <iostream>


MainWindow::MainWindow(MainModel* model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    selectedTool = Tool::Brush;
    brushSize = 1;
    currentIndexOfLayerButtons = 1;
    numberOfLayerButtons = 1;
    selectedLayerButton = ui->layerOneButton;
    selectedLayerButton->setStyleSheet("border: 2px solid blue; border-radius: 5px; padding: 5px;");
    previouslySelected = nullptr;
    ui->layerOneButton->setLayerNumber(1);
    layerButtons.push_back(ui->layerOneButton);
    deleteLayerDisabled = true;

    //connections

    //Save/Load
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::openFileChooserLoad);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::openFileChooserSave);

    //Add delete frames
    connect(ui->previousFrameButton, &QPushButton::clicked, model, &MainModel::previousFrame);
    connect(ui->nextFrameButton, &QPushButton::clicked, model, &MainModel::nextFrame);
    connect(ui->deleteFrameButton, &QPushButton::clicked, model, &MainModel::deleteFrame);
    connect(ui->addFrameButton, &QPushButton::clicked, this, &MainWindow::addFrameHelper);
    connect(this, &MainWindow::addFrame, model, &MainModel::addFrame);

    //Add delete layers
    connect(ui->addLayerButton, &QPushButton::clicked, this, &MainWindow::addLayerButton);
    // connect(this, &MainWindow::selectedLayerChanged, this, &MainWindow::displayLayerButtonSelection);
    // connect(this, &MainWindow::addLayer, model, &MainModel::addLayer);
    connect(ui->deleteLayerButton, &QPushButton::clicked, this, &MainWindow::deleteLayerButton);
    // connect(this, &MainWindow::deleteLayer, model, &MainModel::deleteLayer);

    //Select layers they will be dynamically created and connected else where.
    connect(ui->layerOneButton, &QPushButton::clicked, this, [this]() {
        selectedLayerButton->setStyleSheet("");
        selectedLayerButton = ui->layerOneButton;
        selectedLayerButton->setStyleSheet("border: 2px solid blue; border-radius: 5px; padding: 5px;");
        int layerNumber = ui->layerOneButton->getLayerNumber();
        onLayerButtonClicked(layerNumber);
    });

    connect(ui->addLayerButton, &QPushButton::clicked, this, &MainWindow::addLayer);

    //Change fps
    connect(ui->fpsSlider, &QSlider::sliderMoved, model, &MainModel::changeAnimationFPS);

    //Transformations
    connect(ui->reflectHorizontalButto, &QPushButton::clicked, model, &MainModel::reflectHorizontal);
    connect(ui->reflectVerticalButton, &QPushButton::clicked, model, &MainModel::reflectVertical);
    connect(ui->rotateButton, &QPushButton::clicked, model, &MainModel::rotate90);

    //Update displays
    // connect(model, &MainModel::newDisplayImage, ui->mainDrawing, &PixelDisplay::updateDrawnImage);
    // connect(model, &MainModel::newAnimationFrame, ui->animationDisplay, &PixelDisplay::updateDrawnImage);
    // connect(model, &MainModel::newDisplayImage, ui->frameDisplay, &PixelDisplay::updateDrawnImage);

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
    connect(ui->mouseListener, &MouseListener::mouseClicked, this, &MainWindow::mapClickLocationToGridCoordinate);
    //Set brush size connections - DO WE WANT A SLIDER FOR BRUSH SIZE??? (havnt added to ui cuz aint sure hehe)
    //connect(ui->brushSizeSlider, &QSlider::valueChanged, this, &MainWindow::setBrushSize);

    // Grid size connection between model and window (cuz i was jus gonna add a getter for it
    // in model but doe sthat break MVC? so jus added signal/slot) (for mapClickLocationToGridCoordinate method) !!!
    connect(this, &MainWindow::askGridSize, model, &MainModel::getGridSize);
    connect(model, &MainModel::gridSizeUpdated, this, &MainWindow::updateGridSize);

    emit askGridSize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayColorChange(Pixel pixel)
{
    ui->colorButton->setStyleSheet(QString("background-color: rgba(%1, %2, %3, %4); border-style: outset; border-width: 2px; border-color: beige;").arg(pixel.red).arg(pixel.green).arg(pixel.blue).arg(pixel.alpha));
}

void MainWindow::displayLoadStatus(bool status)
{
    // TODO: Implement displayLoadStatus
}

void MainWindow::displaySaveStatus(bool status)
{
    // TODO: Implement displaySaveStatus
}

void MainWindow::openColorDialogue()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Select a Color", QColorDialog::ShowAlphaChannel);
    if (color.isValid()) {
        emit changeColor(Pixel(color.red(), color.green(), color.blue(), color.alpha()));
    }
}

void MainWindow::setFrameCopyVariable()
{
    frameBeingCopied = !frameBeingCopied;
}

void MainWindow::setBrushSize(int size)
{
    brushSize = size;
    emit changeBrushSize(brushSize);
}

void MainWindow::addFrameHelper()
{
    emit addFrame(frameBeingCopied);
}

void MainWindow::setToolToBrush()
{
    ui->brushButton->setStyleSheet("border: 2px solid blue; border-radius: 5px; padding: 5px;");
    ui->eraserButton->setStyleSheet("");
    ui->paintBucketButton->setStyleSheet("");
    ui->eyeDropperButton->setStyleSheet("");
    selectedTool = Tool::Brush;
}

void MainWindow::setToolToBucket()
{
    ui->brushButton->setStyleSheet("");
    ui->eraserButton->setStyleSheet("");
    ui->paintBucketButton->setStyleSheet("border: 2px solid blue; border-radius: 5px; padding: 5px;");
    ui->eyeDropperButton->setStyleSheet("");
    selectedTool = Tool::PaintBucket;
}

void MainWindow::setToolToEraser()
{
    ui->brushButton->setStyleSheet("");
    ui->eraserButton->setStyleSheet("border: 2px solid blue; border-radius: 5px; padding: 5px;");
    ui->paintBucketButton->setStyleSheet("");
    ui->eyeDropperButton->setStyleSheet("");
    selectedTool = Tool::Eraser;
}

void MainWindow::setToolToEyeDropper()
{
    ui->brushButton->setStyleSheet("");
    ui->eraserButton->setStyleSheet("");
    ui->paintBucketButton->setStyleSheet("");
    ui->eyeDropperButton->setStyleSheet("border: 2px solid blue; border-radius: 5px; padding: 5px;");
    selectedTool = Tool::EyeDropper;
}

void MainWindow::onLayerButtonClicked(int layerNumber)
{   
    emit changeLayer(layerNumber);
}

void MainWindow::updateGridSize(unsigned int gridSize) {
    currentGridSize = gridSize;
}

void MainWindow::mapClickLocationToGridCoordinate(QPoint screenPoint) {
    int canvasWidthPixels = ui->mainDrawing->width();
    int canvasHeightPixels = ui->mainDrawing->height();

    int cellWidth = canvasWidthPixels / currentGridSize;
    int cellHeight = canvasHeightPixels / currentGridSize;

    int gridXCoordinate = screenPoint.x() / cellWidth;
    int gridYCoordinate = screenPoint.y() / cellHeight;

}

void MainWindow::addLayerButton(){
    numberOfLayerButtons++;
    //renable delete button
    if(deleteLayerDisabled){
        deleteLayerDisabled = false;
        ui->deleteLayerButton->setEnabled(true);
    }
    LayerButton* button = new LayerButton(numberOfLayerButtons, this);
    button->setMinimumHeight(32);
    button->setMinimumWidth(99);
    connect(button, &QPushButton::clicked, this, [this, button]() { selectedLayerButton->setStyleSheet(""); selectedLayerButton = button;  selectedLayerButton->setStyleSheet("border: 2px solid blue; border-radius: 5px; padding: 5px;"); onLayerButtonClicked(button->getLayerNumber());});
    ui->layerButtonLayout->addWidget(button);
    selectedLayerButton->setStyleSheet("");
    selectedLayerButton = button;
    selectedLayerButton->setStyleSheet("border: 2px solid blue; border-radius: 5px; padding: 5px;");
    emit changeLayer(selectedLayerButton->getLayerNumber() - 1);
    if (numberOfLayerButtons == 4) {
        int currentHeight = ui->scrollArea->widget()->minimumHeight();
        ui->scrollArea->widget()->setMinimumHeight(currentHeight + 150);

    } else if (numberOfLayerButtons > 4) {
        int currentHeight = ui->scrollArea->widget()->minimumHeight();
        ui->scrollArea->widget()->setMinimumHeight(currentHeight + 38);
    }

    QScrollBar* verticalScrollBar = ui->scrollArea->verticalScrollBar();
    verticalScrollBar->setValue(verticalScrollBar->maximum());

    layerButtons.push_back(button);
    emit addLayer();
}

void MainWindow::deleteLayerButton(){
    if(numberOfLayerButtons == 1) return;
    numberOfLayerButtons--;
    ui->layerButtonLayout->removeWidget(selectedLayerButton);
    layerButtons.removeOne(selectedLayerButton);
    emit deleteLayer(); // Hey dont we need to delete a specific layer not just any layer
    selectedLayerButton->setStyleSheet("");
    delete selectedLayerButton;
    for(int i = 0; i < numberOfLayerButtons; i++){
        QString buttonText = "Layer " + QString::number(i + 1);
        layerButtons.at(i)->setLayerNumber(i);
        layerButtons.at(i)->setText(buttonText);
    }
    selectedLayerButton = layerButtons.last(); // when layer deleted it selects some button & layer
    selectedLayerButton->setStyleSheet("border: 2px solid blue; border-radius: 5px; padding: 5px;");
    emit changeLayer(selectedLayerButton->getLayerNumber() - 1);
    if (numberOfLayerButtons == 3) {
        ui->scrollArea->widget()->setMinimumHeight(0);

    } else if (numberOfLayerButtons > 3) {
        int currentHeight = ui->scrollArea->widget()->minimumHeight();
        ui->scrollArea->widget()->setMinimumHeight(currentHeight - 38);
    }

    QScrollBar* verticalScrollBar = ui->scrollArea->verticalScrollBar();
    verticalScrollBar->setValue(verticalScrollBar->maximum());

    if(numberOfLayerButtons == 1){
        deleteLayerDisabled = true;
        ui->deleteLayerButton->setEnabled(false);
    }

}

void MainWindow::openFileChooserLoad(){
    QString filename = QFileDialog::getOpenFileName(nullptr, "Open File", "", "ssp", nullptr);

    emit loadFile(filename);
}
void MainWindow::openFileChooserSave(){
    QString filename = QFileDialog::getOpenFileName(nullptr, "Open File", "", "ssp", nullptr);

    emit saveFile(filename);
}
