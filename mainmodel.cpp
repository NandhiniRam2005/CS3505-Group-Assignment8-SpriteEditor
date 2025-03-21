#include "mainmodel.h"
#include <stdexcept>
MainModel::MainModel(QObject *parent)
    : QObject{parent}
{}

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

void MainModel::changeBrushSize(unsigned int newBrushSize){}
void MainModel::changeAnimationFPS(unsigned int newFPS){}
void MainModel::changeSelectedColor(Pixel newColor){}
void MainModel::mouseHovered(unsigned int xCoord, unsigned int yCoord){}

void MainModel::paintPixels(unsigned int topLeftX, unsigned int topLeftY){}
void MainModel::erasePixels(unsigned int topLeftX, unsigned int topLeftY){}
void MainModel::bucketFill(unsigned int topLeftX, unsigned int topLeftY){}
void MainModel::reflectVertical(){}
void MainModel::reflectHorizontal(){}
void MainModel::rotate90(){}
void MainModel::setSelectedColorToPixel(unsigned int x, unsigned int y){}
