#include "mainmodel.h"
#include <stdexcept>
MainModel::MainModel(QObject *parent)
    : QObject{parent}
{}

//TODO: load / save JSON methods
// mouseHovered / make grid transparent where mouse is hovering
// send animation frames on a timer
// attach signals / slots
void MainModel::loadJSON(QString& filepath){}
void MainModel::saveJSON(QString& filepath){}

void MainModel::resize(unsigned int newSize){
    for(Frame& frame : frames){
        frame.resize(newSize);
    }
    gridSize = newSize;
}

void MainModel::previousFrame(){
    selectedFrame -= 1;
    if(selectedFrame >= frames.size()){
        selectedFrame = frames.size()-1;
    }
}
void MainModel::nextFrame(){
    selectedFrame += 1;
    if(selectedFrame == frames.size()){
        selectedFrame = 0;
    }
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
}

void MainModel::addLayer(){
    frames[selectedFrame].addLayer();
}

void MainModel::deleteLayer(){
    frames[selectedFrame].deleteLayer();
}

void MainModel::changeBrushSize(unsigned int newBrushSize){
    brushSize = newBrushSize;
}

void MainModel::changeAnimationFPS(unsigned int newFPS){
    animationFPS = newFPS;
}

void MainModel::changeSelectedColor(Pixel newColor){
    selectedColor = newColor;
}

void MainModel::mouseHovered(unsigned int xCoord, unsigned int yCoord){
    currentMouseX = xCoord;
    currentMouseY = yCoord;
}

void MainModel::paintPixels(unsigned int topLeftX, unsigned int topLeftY){
    frames[selectedFrame].paintPixels(topLeftX, topLeftY, selectedColor);
}
void MainModel::erasePixels(unsigned int topLeftX, unsigned int topLeftY){
    frames[selectedFrame].paintPixels(topLeftX, topLeftY, Pixel(0,0,0,0));
}
void MainModel::bucketFill(unsigned int topLeftX, unsigned int topLeftY){
    frames[selectedFrame].bucketFill(topLeftX, topLeftY, selectedColor);
}
void MainModel::reflectVertical(){
    frames[selectedFrame].reflectVertical();
}
void MainModel::reflectHorizontal(){
    frames[selectedFrame].reflectHorizontal();
}
void MainModel::rotate90(){
    frames[selectedFrame].rotate90();
}
void MainModel::setSelectedColorToPixel(unsigned int x, unsigned int y){
    selectedColor = frames[selectedFrame].getPixel(x, y);
}
