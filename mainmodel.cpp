#include "mainmodel.h"
#include <stdexcept>
MainModel::MainModel(QObject *parent)
    : QObject{parent}
{}

//TODO: load / save JSON methods
// send animation frames on a timer
// attach signals / slots
void MainModel::loadJSON(QString& filepath){}
void MainModel::saveJSON(QString& filepath){}

void MainModel::resize(unsigned int newSize){
    for(Frame& frame : frames){
        frame.resize(newSize);
    }
    gridSize = newSize;
    sendDisplayImage();
}

void MainModel::previousFrame(){
    selectedFrame -= 1;
    if(selectedFrame >= frames.size()){
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
    //TODO: Set timer here
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
        emit newDisplayImage(image);
        return;
    }
    for(int i = currentMouseY; i< currentMouseY + brushSize; i++){
        for(int j = currentMouseX; j< currentMouseX + brushSize; j++){
            image[i * gridSize + j].alpha = HOVERED_ALPHA;
        }
    }
    emit newDisplayImage(image);
}
