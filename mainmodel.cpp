/*
The cpp file for mainmodel.

A class which represents the model for the sprite editor. It manages frames, layers,
brush size, animation speed, and pixel manipulations. The model sends updated pixel grids to
the display through signals and handles user interactions with frames and layers.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan
Jake Heairld & Joseph Hamilton

March 30, 2025
*/

#include "mainmodel.h"
#include <QJsonDocument>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>

using std::min;
using std::max;
using std::copy;
using std::runtime_error;

MainModel::MainModel(QObject *parent): QObject{parent} {
    brushSize = 4;
    gridSize = 32;
    selectedFrame = 0;
    selectedColor = Pixel(0,0,0,255);
    currentTool = Tool::Brush;
    animationTimer = new QTimer();
    animationFPS = 10;
    currentAnimationFrame = 0;

    frames.push_back(Frame(gridSize));
    animationTimer->start(1000/animationFPS);

    connect(animationTimer, &QTimer::timeout, this, &MainModel::sendAnimationFrame);
}

void MainModel::loadJSON(const QString& filepath) {
    if(!filepath.endsWith("ssp")){
        emit loadJSONStatus(false);
        return;
    }

    frames.clear();
    QFile file(filepath);

    //try to open the file on readonly mode to see if its a valid filename
    if (!file.open(QIODevice::ReadOnly)) {
        emit loadJSONStatus(false);
        return;
    }

    QByteArray fileData = file.readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(fileData);
    QJsonObject jsonSpriteCanvas = jsonDocument.object();

    //Read size
    if (jsonSpriteCanvas.contains("size")) {
        gridSize = jsonSpriteCanvas["size"].toInt();
        emit gridSizeUpdated(gridSize);
    } else {
        emit loadJSONStatus(false);
        return;
    }

    QVector<Pixel> tempImage(gridSize * gridSize);

    //Read frames
    if (jsonSpriteCanvas.contains("frames")) {
        QJsonArray jsonFrames = jsonSpriteCanvas["frames"].toArray();

        for (const auto& frameValue : jsonFrames) {
            QJsonObject jsonFrame = frameValue.toObject();
            Frame frame(gridSize);

            //Read layers
            if (jsonFrame.contains("layers")) {
                QJsonArray jsonLayers = jsonFrame["layers"].toArray();

                for (const QJsonValue& layerValue : jsonLayers) {
                    QJsonObject jsonLayer = layerValue.toObject();
                    Layer layer(gridSize);

                    //Read Pixels
                    if (jsonLayer.contains("pixels")) {
                        QJsonArray pixelArray = jsonLayer["pixels"].toArray();
                        Pixel* pixels = layer.getLayer();
                        loadPixelsFromJson(pixelArray, pixels);

                        if (frames.isEmpty() && jsonLayers.size() > 0) {
                            copy(pixels, pixels + gridSize * gridSize, tempImage.begin());
                        }

                    }
                    frame.addLayer(layer);
                }
            }

            // Needed since frames must have one layer the frame constructor adds a layer, this deletes it
            frame.deleteLayer(0);
            frames.append(frame);
        }
    } else {
        emit loadJSONStatus(false);
        return;
    }

    file.close();
    emit loadJSONStatus(true);
    emit sendNumberOfLayers(frames[selectedFrame].getLayers().size());
    emit newDisplayImage(tempImage.data());
}


void MainModel::saveJSON(const QString& filepath){
    QFile file(filepath);

    //try to open the file on writeonly mode to see if its a valid filename
    if (!file.open(QIODevice::WriteOnly)) {
        emit saveJSONStatus(false);
        return;
    }

    QJsonObject jsonSpriteCanvas;
    jsonSpriteCanvas["size"] = (int) gridSize;
    QJsonArray jsonFrames;

    // Loop through frames in the model
    for (Frame& frame : frames) {
        QJsonObject jsonFrame;
        QJsonArray jsonLayers;

        // Loop through layers
        for (auto& layer : frame.getLayers()) {
            QJsonObject jsonLayer;
            const Pixel* pixels = layer.getLayer();

            // Add layer's pixels to the pixel array
            jsonLayer["pixels"] = pixelsToJson(pixels);
            jsonLayers.append(jsonLayer);
        }
        jsonFrame["layers"] = jsonLayers;
        jsonFrames.append(jsonFrame);
    }
    jsonSpriteCanvas["frames"] = jsonFrames;

    // use jsonSpriteCanvas object to make a document used to write to the file
    QJsonDocument jsonDocument(jsonSpriteCanvas);
    file.write(jsonDocument.toJson());
    file.close();
    emit saveJSONStatus(true);
}

void MainModel::loadPixelsFromJson(const QJsonArray& pixelArray, Pixel* pixels) {
    for (unsigned int i = 0; i < pixelArray.size(); i++) {
        QJsonObject jsonPixel = pixelArray[i].toObject();
        pixels[i].red = jsonPixel["red"].toInt();
        pixels[i].green = jsonPixel["green"].toInt();
        pixels[i].blue = jsonPixel["blue"].toInt();
        pixels[i].alpha = jsonPixel["alpha"].toInt();
    }
}

QJsonArray MainModel::pixelsToJson(const Pixel* pixels) {
    QJsonArray pixelArray;

    for (unsigned int i = 0; i < gridSize * gridSize; i++) {
        QJsonObject jsonPixel;
        jsonPixel["red"] = pixels[i].red;
        jsonPixel["green"] = pixels[i].green;
        jsonPixel["blue"] = pixels[i].blue;
        jsonPixel["alpha"] = pixels[i].alpha;
        pixelArray.append(jsonPixel);
    }

    return pixelArray;
}

void MainModel::resize(unsigned int newSize){
    for(Frame& frame : frames){
        frame.resize(newSize);
    }

    gridSize = newSize;
    sendDisplayImage();
}

void MainModel::previousFrame(){
    selectedFrame -= 1;

    if(selectedFrame < 0){
        selectedFrame = frames.size()-1;
    }

    emit newSelectedFrame(selectedFrame);
    emit sendNumberOfLayers(frames[selectedFrame].getLayers().size());
    sendDisplayImage();
}

void MainModel::nextFrame(){
    selectedFrame += 1;

    if(selectedFrame == frames.size()){
        selectedFrame = 0;
    }

    emit newSelectedFrame(selectedFrame);
    emit sendNumberOfLayers(frames[selectedFrame].getLayers().size());
    sendDisplayImage();
}

void MainModel::addFrame(bool copyPrevious){
    if(copyPrevious){
        frames.append(frames[frames.size()-1]);
    }else{
        frames.append(Frame(gridSize));
    }

    selectedFrame+=1;
    emit sendNumberOfLayers(frames[selectedFrame].getLayers().size());
    emit newSelectedFrame(selectedFrame);
    sendDisplayImage();
}

void MainModel::deleteFrame(){
    if(frames.size() == 1){
        throw runtime_error("Cannot delete the only remaining frame");
    }

    frames.remove(selectedFrame);

    if(selectedFrame >= frames.size()){
        selectedFrame = frames.size()-1;
    }

    emit newSelectedFrame(selectedFrame);
    emit sendNumberOfLayers(frames[selectedFrame].getLayers().size());
    sendDisplayImage();
}

void MainModel::changeLayer(unsigned int layer){
    if(layer >= frames[selectedFrame].getLayers().size()){
        throw runtime_error("Invalid layer index");
    }

    frames[selectedFrame].selectLayer(layer);
    sendDisplayImage();
}

void MainModel::addLayer(){
    frames[selectedFrame].addLayer();
    sendDisplayImage();
}

void MainModel::deleteLayer(int layerIndex){
    frames[selectedFrame].deleteLayer(layerIndex);
    sendDisplayImage();
}

void MainModel::changeBrushSize(unsigned int newBrushSize){
    brushSize = newBrushSize;
    sendDisplayImage();
}

void MainModel::changeAnimationFPS(unsigned int newFPS){
    qDebug() << "FPS changed: " << newFPS;
    animationFPS = newFPS;

    if (animationFPS > 0 and animationFPS < 1000) {
        animationTimer->start();

        animationTimer->setInterval(1000/animationFPS);
    }
    else {
        animationTimer->stop();
    }
}

void MainModel::changeSelectedColor(Pixel newColor){
    selectedColor = newColor;
    emit newSelectedColor(selectedColor);
}

void MainModel::mouseHovered(unsigned int xCoord, unsigned int yCoord){
    currentMouseX = xCoord;
    currentMouseY = yCoord;
    sendDisplayImage();
}

void MainModel::paintPixels(unsigned int topLeftX, unsigned int topLeftY){
    // boundary checks
    if(topLeftX >= gridSize || topLeftY >= gridSize){
        return;
    }

    const unsigned int maxX = min(topLeftX + brushSize, gridSize);
    const unsigned int maxY = min(topLeftY + brushSize, gridSize);

    frames[selectedFrame].paintPixels(QPoint(topLeftX, topLeftY), QPoint(maxX-1, maxY-1), selectedColor);
    sendDisplayImage();
}

void MainModel::erasePixels(unsigned int topLeftX, unsigned int topLeftY){
    // boundary checks
    if(topLeftX >= gridSize || topLeftY >= gridSize){
        return;
    }

    const unsigned int maxX = min(topLeftX + brushSize, gridSize);
    const unsigned int maxY = min(topLeftY + brushSize, gridSize);

    frames[selectedFrame].paintPixels(QPoint(topLeftX, topLeftY), QPoint(maxX - 1, maxY - 1), Pixel(0, 0, 0, 0));
    sendDisplayImage();
}

void MainModel::bucketFill(unsigned int topLeftX, unsigned int topLeftY){
    frames[selectedFrame].bucketFill(topLeftX, topLeftY, selectedColor);
    sendDisplayImage();
}

void MainModel::reflectVertical(){
    frames[selectedFrame].reflectVertical();
    sendDisplayImage();
}

void MainModel::reflectHorizontal(){
    frames[selectedFrame].reflectHorizontal();
    sendDisplayImage();
}

void MainModel::rotate90(){
    frames[selectedFrame].rotate90();
    sendDisplayImage();
}

void MainModel::setSelectedColorToPixel(unsigned int x, unsigned int y){
    selectedColor = frames[selectedFrame].getPixel(x, y);
    emit newSelectedColor(selectedColor);
}

void MainModel::mouseLeft()
{
    currentMouseX = -1;
    currentMouseY = -1;
    sendDisplayImage();
}

void MainModel::selectTool(Tool newTool){
    currentTool = newTool;
}
void MainModel::pixelClicked(unsigned int xCoord, unsigned int yCoord){
    switch(currentTool){
    case Tool::Brush:
        paintPixels(xCoord, yCoord);
        break;
    case Tool::Eraser:
        erasePixels(xCoord, yCoord);
        break;
    case Tool::EyeDropper:
        setSelectedColorToPixel(xCoord, yCoord);
        break;
    case Tool::PaintBucket:
        bucketFill(xCoord, yCoord);
        break;
    case Tool::None:
        break;
    }
}

void MainModel::sendDisplayImage(){
    // For the frame display
    emit newFrameImage(frames[selectedFrame].getRenderedImage());

    // Get original image
    Pixel* baseImage = frames[selectedFrame].getLayeredImage();

    // Create temporary copy
    QVector<Pixel> tempImage(gridSize * gridSize);

    copy(baseImage, baseImage + gridSize * gridSize, tempImage.begin());
    unsigned int brushSizeStore = brushSize;

    if(currentTool == Tool::PaintBucket || currentTool == Tool::EyeDropper){
        brushSize = 1;
    }

    if(currentMouseX >= 0 && currentMouseY >= 0) {
        // Apply hover to copy
        const int maxX = min(currentMouseX + brushSize, static_cast<int>(gridSize));
        const int maxY = min(currentMouseY + brushSize, static_cast<int>(gridSize));

        for(int y = max(0, currentMouseY); y < maxY; ++y) {
            for(int x = max(0, currentMouseX); x < maxX; ++x) {
                tempImage[y * gridSize + x].alpha = HOVERED_ALPHA;
            }
        }
    }

    brushSize = brushSizeStore;

    // Emit temporary copy
    emit newDisplayImage(tempImage.data());
}

void MainModel::sendAnimationFrame(){
    currentAnimationFrame += 1;

    if(currentAnimationFrame >= frames.size()){
        currentAnimationFrame = 0;
    }

    emit newAnimationFrame(frames[currentAnimationFrame].getRenderedImage());
}

void MainModel::getGridSize() {
    emit gridSizeUpdated(gridSize);
}
