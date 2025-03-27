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
    brushSize = 3;
    currentIndexOfLayerButtons = 1;
    numberOfLayerButtons = 1;
    selectedLayerButton = ui->layerOneButton;
    selectedLayerButton->setStyleSheet("border: 2px solid blue; border-radius: 5px; padding: 5px;");
    previouslySelected = nullptr;
    ui->layerOneButton->setLayerNumber(1);
    layerButtons.push_back(ui->layerOneButton);
    deleteLayerDisabled = true;
    ui->resizeBox->addItem("8 x 8");
    ui->resizeBox->addItem("16 x 16");
    ui->resizeBox->addItem("32 x 32");
    ui->resizeBox->addItem("64 x 64");


    //connections

    //For Hover
    connect(ui->mouseListener, &MouseListener::mouseLeft, model, &MainModel::mouseLeft);
    connect(ui->mouseListener, &MouseListener::mouseMoved,
            this, [this, model](QPoint point) {
                const int canvasWidth = ui->mainDrawing->width();
                const int canvasHeight = ui->mainDrawing->height();

                if (canvasWidth == 0 || canvasHeight == 0) return;

                const int cellWidth = canvasWidth / currentGridSize;
                const int cellHeight = canvasHeight / currentGridSize;

                const int gridX = point.x() / cellWidth;
                const int gridY = point.y() / cellHeight;

                if (gridX >= 0 && gridY >= 0 &&
                    gridX < static_cast<int>(currentGridSize) &&
                    gridY < static_cast<int>(currentGridSize)) {
                    model->mouseHovered(gridX, gridY);
                }
            });

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
    connect(this, &MainWindow::addLayer, model, &MainModel::addLayer);
    connect(ui->deleteLayerButton, &QPushButton::clicked, this, &MainWindow::deleteLayerButton);
    connect(this, &MainWindow::deleteLayer, model, &MainModel::deleteLayer);
    connect(this, &MainWindow::changeLayer, model, &MainModel::changeLayer);

    //Select layers they will be dynamically created and connected else where.
    connect(ui->layerOneButton, &QPushButton::clicked, this, [this]() {
        selectedLayerButton->setStyleSheet("");
        selectedLayerButton = ui->layerOneButton;
        selectedLayerButton->setStyleSheet("border: 2px solid blue; border-radius: 5px; padding: 5px;");
        int layerNumber = ui->layerOneButton->getLayerNumber();
        onLayerButtonClicked(layerNumber - 1);
    });

    connect(ui->addLayerButton, &QPushButton::clicked, this, &MainWindow::addLayer);

    //Change fps
    connect(ui->fpsSlider, &QSlider::sliderMoved, model, &MainModel::changeAnimationFPS);

    //Transformations
    connect(ui->reflectHorizontalButton, &QPushButton::clicked, model, &MainModel::reflectHorizontal);
    connect(ui->reflectVerticalButton, &QPushButton::clicked, model, &MainModel::reflectVertical);
    connect(ui->rotateButton, &QPushButton::clicked, model, &MainModel::rotate90);

    // Resize
    connect(ui->resizeBox, &QComboBox::currentIndexChanged, this, &MainWindow::changeGridSize);
    connect(this, &MainWindow::resize, ui->mainDrawing, &PixelDisplay::setGridSize);
    connect(this, &MainWindow::resize, ui->animationDisplay, &PixelDisplay::setGridSize);
    connect(this, &MainWindow::resize, ui->frameDisplay, &PixelDisplay::setGridSize);
    connect(this, &MainWindow::resize, model, &MainModel::resize);

    // Toolbar connection
    connect(this, &MainWindow::pixelClicked, model, &MainModel::pixelClicked);
    connect(this, &MainWindow::toolSelected, model, &MainModel::selectTool);

    //Update displays
    connect(model, &MainModel::newDisplayImage, ui->mainDrawing, &PixelDisplay::updateDrawnImage);
    connect(model, &MainModel::newAnimationFrame, ui->animationDisplay, &PixelDisplay::updateDrawnImage);
    connect(model, &MainModel::newDisplayImage, ui->frameDisplay, &PixelDisplay::updateDrawnImage);

    //Update color
    connect(ui->colorButton, &QPushButton::clicked, this, &MainWindow::openColorDialogue);
    connect(this, &MainWindow::changeColor, this, &MainWindow::displayColorChange);
    connect(this, &MainWindow::changeColor, model, &MainModel::changeSelectedColor);
    connect(model, &MainModel::newSelectedColor, this, &MainWindow::displayColorChange);

    //Frame being copied?
    connect(ui->copyFrameButton, &QRadioButton::clicked, this, &MainWindow::setFrameCopyVariable);

    //Set tools
    connect(ui->brushButton, &QPushButton::clicked, this, &MainWindow::setToolToBrush);
    connect(ui->eyeDropperButton, &QPushButton::clicked, this, &MainWindow::setToolToEyeDropper);
    connect(ui->paintBucketButton, &QPushButton::clicked, this, &MainWindow::setToolToBucket);
    connect(ui->eraserButton, &QPushButton::clicked, this, &MainWindow::setToolToEraser);

    //Drawing connections NOT DONE
    connect(ui->mouseListener, &MouseListener::mouseClicked, this, &MainWindow::mapClickLocationToGridCoordinate);
    connect(ui->mouseListener, &MouseListener::mouseMoved, this, &MainWindow::handleMouseDrag);
    //Set brush size connections - DO WE WANT A SLIDER FOR BRUSH SIZE??? (havnt added to ui cuz aint sure hehe)
    //connect(ui->brushSizeSlider, &QSlider::valueChanged, this, &MainWindow::setBrushSize);

    // Grid size connection between model and window (cuz i was jus gonna add a getter for it
    // in model but doe sthat break MVC? so jus added signal/slot) (for mapClickLocationToGridCoordinate method) !!!
    connect(this, &MainWindow::askGridSize, model, &MainModel::getGridSize);
    connect(model, &MainModel::gridSizeUpdated, this, &MainWindow::updateGridSize);

    //Connect MouseListener
    connect(ui->mouseListener, &MouseListener::mouseClicked, this, &MainWindow::mapClickLocationToGridCoordinate);

    //Load and save
    connect(this, &MainWindow::saveFile, model, &MainModel::saveJSON);
    connect(this, &MainWindow::loadFile, model, &MainModel::loadJSON);


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
    emit toolSelected(Tool::Brush);
}

void MainWindow::setToolToBucket()
{
    ui->brushButton->setStyleSheet("");
    ui->eraserButton->setStyleSheet("");
    ui->paintBucketButton->setStyleSheet("border: 2px solid blue; border-radius: 5px; padding: 5px;");
    ui->eyeDropperButton->setStyleSheet("");
    emit toolSelected(Tool::PaintBucket);
}

void MainWindow::setToolToEraser()
{
    ui->brushButton->setStyleSheet("");
    ui->eraserButton->setStyleSheet("border: 2px solid blue; border-radius: 5px; padding: 5px;");
    ui->paintBucketButton->setStyleSheet("");
    ui->eyeDropperButton->setStyleSheet("");
    emit toolSelected(Tool::Eraser);
}

void MainWindow::setToolToEyeDropper()
{
    ui->brushButton->setStyleSheet("");
    ui->eraserButton->setStyleSheet("");
    ui->paintBucketButton->setStyleSheet("");
    ui->eyeDropperButton->setStyleSheet("border: 2px solid blue; border-radius: 5px; padding: 5px;");
    emit toolSelected(Tool::EyeDropper);
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

    unsigned int gridXCoordinate = screenPoint.x() / cellWidth;
    unsigned int gridYCoordinate = screenPoint.y() / cellHeight;

    if(gridXCoordinate < 0 || gridYCoordinate < 0 || gridXCoordinate >= currentGridSize ||gridYCoordinate >= currentGridSize){
        return; //clicked / dragged outside of the canvas
    }
    emit pixelClicked(gridXCoordinate, gridYCoordinate);
}

void MainWindow::handleMouseDrag(QPoint screenPoint) {
    if(QApplication::mouseButtons() & Qt::LeftButton) {
        mapClickLocationToGridCoordinate(screenPoint);
    }
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
    connect(button, &QPushButton::clicked, this, [this, button]() { selectedLayerButton->setStyleSheet(""); selectedLayerButton = button;  selectedLayerButton->setStyleSheet("border: 2px solid blue; border-radius: 5px; padding: 5px;"); onLayerButtonClicked(button->getLayerNumber() - 1);});
    ui->layerButtonLayout->addWidget(button);
    selectedLayerButton->setStyleSheet("");
    selectedLayerButton = button;
    selectedLayerButton->setStyleSheet("border: 2px solid blue; border-radius: 5px; padding: 5px;");
    emit addLayer();
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
}

void MainWindow::deleteLayerButton(){
    if(numberOfLayerButtons == 1) return;
    numberOfLayerButtons--;
    ui->layerButtonLayout->removeWidget(selectedLayerButton);
    layerButtons.removeOne(selectedLayerButton);
    emit deleteLayer(selectedLayerButton->getLayerNumber() - 1); // Hey dont we need to delete a specific layer not just any layer
    selectedLayerButton->setStyleSheet("");
    delete selectedLayerButton;
    for(int i = 0; i < numberOfLayerButtons; i++){
        QString buttonText = "Layer " + QString::number(i + 1);
        layerButtons.at(i)->setLayerNumber(i+1);
        layerButtons.at(i)->setText(buttonText);
    }
    std::cout << layerButtons.size() << std::endl;

    std::cout << layerButtons.first()->getLayerNumber() << std::endl;
    selectedLayerButton = layerButtons.first(); // when layer deleted it selects some button & layer
    std::cout << selectedLayerButton->getLayerNumber() - 1 << std::endl;
    selectedLayerButton->setStyleSheet("border: 2px solid blue; border-radius: 5px; padding: 5px;");
    std::cout << selectedLayerButton->getLayerNumber() - 1 << std::endl;
    emit changeLayer(selectedLayerButton->getLayerNumber());
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
    QString filename = QFileDialog::getOpenFileName(nullptr, "Open File", "", "", nullptr);

    emit loadFile(filename);

    ui->mainDrawing->update();
    ui->animationDisplay->update();
    ui->frameDisplay->update();
}
void MainWindow::openFileChooserSave(){
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save File", "", "ssp", nullptr);
    // QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "Sprite Project (*.ssp);;All Files (*)");

    if (!fileName.isEmpty()) {
        if (!fileName.endsWith(".ssp")) {
            fileName += ".ssp";
        }
        emit saveFile(fileName);
    }
}

void MainWindow::changeGridSize(int sizeOption) {
    switch (sizeOption) {
    case 0:
        currentGridSize = 8;
        emit resize(8);
        break;
    case 1:
        currentGridSize = 16;
        emit resize(16);
        break;
    case 2:
        currentGridSize = 32;
        emit resize(32);
        break;
    case 3:
        currentGridSize = 64;
        emit resize(64);
        break;
    }
}

