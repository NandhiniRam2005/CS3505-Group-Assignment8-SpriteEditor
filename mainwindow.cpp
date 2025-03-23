#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(MainModel *model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    selectedTool = Brush;
    brushSize = 5;
    currentIndexOfLayerButtons = 1;
    selectedLayerButton = ui->layerOne;
    ui->layerOne->setProperty("layerNumber", 1);
    layerButtons.append(ui->layerOne);
    deleteLayerDisabled = true;

    //connections

    //Save/Load
    connect(ui->actionLoad, &QAction::triggered, model, &MainModel::loadJSON);
    connect(ui->actionSave, &QAction::triggered, model, &MainModel::saveJSON);

    //Add delete frames
    connect(ui->previousFrameButton, &QPushButton::clicked, model, &MainModel::previousFrame);
    connect(ui->nextFrameButton, &QPushButton::clicked, model, &MainModel::nextFrame);
    connect(ui->deleteFrameButton, &QPushButton::clicked, model, &MainModel::deleteFrame);
    connect(ui->addFrameButton, &QPushButton::clicked, this, &MainWindow::addFrameHelper);
    connect(this, &MainWindow::addFrame, model, &MainModel::addFrame);

    //Add delete layers
    connect(ui->addLayerButton, &QPushButton::clicked, this, &MainWindow::addLayerButton);
    connect(this, &MainWindow::addLayer, model, &MainModel::addLayer);
    connect(ui->deleteLayerButton, &QPushButton::clicked, model, &MainModel::deleteLayer);

    //Select layers they will be dynamically created and connected else where.
    connect(ui->layerOne, &QPushButton::clicked, this, [this]() {
        int layerNumber = ui->layerOne->property("layerNumber").toInt();
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
    connect(model, &MainModel::newDisplayImage, ui->mainDrawing, &PixelDisplay::updateDrawnImage);
    connect(model,
            &MainModel::newDisplayImage,
            ui->animationDisplay,
            &PixelDisplay::updateDrawnImage);
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

    //Set brush size connections - DO WE WANT A SLIDER FOR BRUSH SIZE??? (havnt added to ui cuz aint sure hehe)
    connect(ui->brushSizeSlider, &QSlider::valueChanged, this, &MainWindow::setBrushSize);

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
    colorButton.setStyleSheet(QString("background-color: rgba(%1, %2, %3, %4);").arg(pixel.red).arg(pixel.green).arg(pixel.blue).arg(pixel.alpha));
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
    selectedTool = Brush;
}

void MainWindow::setToolToBucket()
{
    selectedTool = PaintBucket;
}

void MainWindow::setToolToEraser()
{
    selectedTool = Eraser;
}

void MainWindow::setToolToEyeDropper()
{
    selectedTool = EyeDropper;
}

void MainWindow::onLayerButtonClicked(int layerNumber)
{
    // TODO: Implement onLayerButtonClicked
    emit changeLayer(layerNumber);
}

void MainWindow::updateGridSize(unsigned int gridSize) {
    currentGridSize = gridSize;
}

QPoint MainWindow::mapClickLocationToGridCoordinate(unsigned int x, unsigned int y) {
    int canvasWidthPixels = ui->mainDrawing->width();
    int canvasHeightPixels = ui->mainDrawing->height();

    int cellWidth = canvasWidthPixels / currentGridSize;
    int cellHeight = canvasHeightPixels / currentGridSize;

    int gridXCoordinate = x / cellWidth;
    int gridYCoordinate = y / cellHeight;

    return QPoint(gridXCoordinate, gridYCoordinate);
}

void MainWindow::addLayerButton(){
    currentIndexOfLayerButtons++;
    numberOfLayerButtons++;
    //renable delete button
    if(deleteLayerDisabled){
        deleteLayerDisabled = false;
        ui->deleteLayerButton->setEnabled(true);
    }
    LayerButton* button = new LayerButton(currentIndexOfLayerButtons, this);
    connect(button, &QPushButton::clicked, this, [this, button]() {selectedLayerButton = button; onLayerButtonClicked(button->getLayerNumber());});
    ui->layerButtonLayout->addWidget(button);
    layerButtons.append(button);
    emit addLayer();
}

void MainWindow::deleteLayerButton(){
    if(numberOfLayerButtons == 1) return;
    numberOfLayerButtons--;
    ui->layerButtonLayout->removeWidget(selectedLayerButton);
    layerButtons.removeOne(selectedLayerButton);
    delete selectedLayerButton;
    selectedLayerButton = layerButtons.first(); // when layer deleted it selects some button
    emit changeLayer(selectedLayerButton->getLayerNumber());

    if(numberOfLayerButtons == 1){
        deleteLayerDisabled = true;
        ui->deleteLayerButton->setEnabled(false);
    }

}
