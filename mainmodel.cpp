#include "mainmodel.h"
#include <stdexcept>
#include <QJsonDocument>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>

MainModel::MainModel(QObject *parent)
    : QObject{parent}
{
    brushSize = 1;
    gridSize = 32;
    animationFPS = 12;
    frames.push_back(Frame(gridSize));
    selectedFrame = 0;
    selectedColor = Pixel(0,0,0,255);

    animationTimer = new QTimer();

    connect(animationTimer, &QTimer::timeout, this, &MainModel::sendAnimationFrame);

    animationTimer->start(33);
    currentAnimationFrame = 0;
    }
/*
//TODO: load / save JSON methods --- DONE MAYBE? : look at saveJson tho! :(
// send animation frames on a timer
// attach signals / slots
void MainModel::loadJSON(QString& filepath){
    QFile file(filepath);

    //try to open the file on readonly mode to see if its a valid filename
    if (!file.open(QIODevice::ReadOnly)) {
        emit loadJSONStatus(false);
        return;
    }

    QByteArray fileData = file.readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(fileData);

    if (jsonDocument.isNull()) {
        emit loadJSONStatus(false);
        return;
    }

    QJsonObject jsonSpriteCanvas = jsonDocument.object();

    //Read size
    if (jsonSpriteCanvas.contains("size")) {
        gridSize = jsonSpriteCanvas["size"].toInt();
    } else {
        emit loadJSONStatus(false);
        return;
    }

    //Read frames
    if (jsonSpriteCanvas.contains("frames")) {
        QJsonArray jsonFrames = jsonSpriteCanvas["frames"].toArray();

        for (const QJsonValue& frameValue : jsonFrames) {
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

                        for (unsigned int i = 0; i < pixelArray.size(); i++) {
                            QJsonObject jsonPixel = pixelArray[i].toObject();
                            pixels[i].red = jsonPixel["red"].toInt();
                            pixels[i].green = jsonPixel["green"].toInt();
                            pixels[i].blue = jsonPixel["blue"].toInt();
                            pixels[i].alpha = jsonPixel["alpha"].toInt();
                        }
                    }
                    frame.addLayer();
                }
            }
            frames.append(frame);
        }
    } else {
        emit loadJSONStatus(false);
        return;
    }

    file.close();
    emit loadJSONStatus(true);
}


void MainModel::saveJSON(QString& filepath){
    QFile file(filepath);

    //try to open the file on writeonly mode to see if its a valid filename
    if (!file.open(QIODevice::WriteOnly)) {
        emit saveJSONStatus(false);
        return;
    }

    QJsonObject jsonSpriteCanvas;
    jsonSpriteCanvas["size"] = (int) gridSize;

    // Loop through frames in the model
    QJsonArray jsonFrames;
    for (Frame& frame : frames) {
        QJsonObject jsonFrame;
        QJsonArray jsonLayers;

        // Loop through each frame's layers
        // HOW DO I LOOP THRU the frame's layers without liek having a getlayers method in frame (but doenst that break MVC? idk
        for (const Layer& layer : frame.getLayers()) {
            QJsonObject jsonLayer;
            QJsonArray pixelArray;

            const Pixel* pixels = layer.getLayer();

            // Add layer's pixels to the pixel array
            for (unsigned int i = 0; i < gridSize * gridSize; i++) {
                QJsonObject jsonPixel;
                jsonPixel["red"] = pixels[i].red;
                jsonPixel["green"] = pixels[i].green;
                jsonPixel["blue"] = pixels[i].blue;
                jsonPixel["alpha"] = pixels[i].alpha;
                pixelArray.append(jsonPixel);
            }
            jsonLayer["pixels"] = pixelArray;
            jsonLayer["size"] = (int) gridSize;
            jsonLayers.append(jsonLayer);
        }
        jsonFrame["layers"] = jsonLayers;
        jsonFrame["size"] = (int) gridSize;
        jsonFrames.append(jsonFrame);
    }
    jsonSpriteCanvas["frames"] = jsonFrames;

    // use jsonSpriteCanvas obj to make a document used to write to the file
    QJsonDocument jsonDocument(jsonSpriteCanvas);
    file.write(jsonDocument.toJson());
    file.close();
    emit saveJSONStatus(true);
}
*/
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
    sendDisplayImage();
}

void MainModel::nextFrame(){
    selectedFrame += 1;
    if(selectedFrame == frames.size()){
        selectedFrame = 0;
    }
    sendDisplayImage();
}

void MainModel::addFrame(bool copyPrevious){
    if(copyPrevious){
        frames.append(frames[frames.size()-1]);
    }else{
        frames.append(Frame(gridSize));
    }
}

void MainModel::deleteFrame(){
    if(frames.size() == 1){
        throw std::runtime_error("Cannot delete the only remaining frame");
    }

    frames.remove(frames.size()-1);
    if(selectedFrame <= frames.size()){
        selectedFrame = frames.size()-1;
    }
}

void MainModel::changeLayer(unsigned int layer){
    if(layer >= frames.size()){
        throw std::runtime_error("Invalid layer index");
    }
    frames[selectedFrame].selectLayer(layer);
    selectedFrame = layer;
    sendDisplayImage();
}

void MainModel::addLayer(){
    frames[selectedFrame].addLayer();
}

void MainModel::deleteLayer(){
    frames[selectedFrame].deleteLayer();
}

void MainModel::changeBrushSize(unsigned int newBrushSize){
    brushSize = newBrushSize;
    sendDisplayImage();
}

void MainModel::changeAnimationFPS(unsigned int newFPS){
    animationFPS = newFPS;
    if (newFPS > 0 and newFPS > 1000)
        animationTimer->setInterval(1000/newFPS);
    else
        animationTimer->stop();
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
    frames[selectedFrame].paintPixels(QPoint(topLeftX, topLeftY), QPoint(topLeftX + brushSize - 1, topLeftX + brushSize - 1), selectedColor);
    sendDisplayImage();
}

void MainModel::erasePixels(unsigned int topLeftX, unsigned int topLeftY){
    frames[selectedFrame].paintPixels(QPoint(topLeftX, topLeftY), QPoint(topLeftX + brushSize - 1, topLeftX + brushSize - 1), Pixel(0,0,0,0));
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

void MainModel::sendDisplayImage(){
    Pixel* image = frames[selectedFrame].getLayeredImage();
    if(currentMouseX < 0 || currentMouseY < 0){
        emit newDisplayImage(image, gridSize);
        return;
    }
    for(int i = currentMouseY; i< currentMouseY + brushSize; i++){
        for(int j = currentMouseX; j< currentMouseX + brushSize; j++){
            image[i * gridSize + j].alpha = HOVERED_ALPHA;
        }
    }
    emit newDisplayImage(image, gridSize);
}

void MainModel::sendAnimationFrame(){
    currentAnimationFrame += 1;
    if(currentAnimationFrame == frames.size()){
        currentAnimationFrame = 0;
    }
    emit newAnimationFrame(frames[currentAnimationFrame].getLayeredImage());
}


void MainModel::getGridSize() {
    emit gridSizeUpdated(gridSize);
}
