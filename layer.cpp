#include "layer.h"
#include "pixel.h"
#include <QVector>
#include <QPoint>
#include <stdexcept>

Layer::Layer(int width, int height): width(width), height(height){
    pixels = QVector<QVector<Pixel>>();
    for(int i = 0; i<height; i++){
        pixels.push_back(QVector<Pixel>());
        for(int j = 0; j<width; j++){
            pixels[i].push_back(Pixel(0,0,0,0));
        }
    }
}
Layer::~Layer(){

}
Layer::Layer(const Layer& other){
    size = other.size;
    pixels = other.pixels;
}
void Layer::operator=(Layer other){
    std::swap(size, other.size);
    std::swap(pixels, other.pixels);
}

void Layer::paintPixels(QPoint corner1, QPoint corner2, const Pixel& color){
    validateCoords(corner1.x(), corner1.y());
    validateCoords(corner2.x(), corner2.y());
    for(int i = corner1.y(); i<= corner2.y(); i++){
        for(int j = corner1.x(); i<=corner2.x(); i++){
            pixels[i][j] = color;
        }
    }
}
void Layer::bucketFill(int x, int y, const Pixel& color){
    validateCoords(x, y);

}
Pixel Layer::getPixel(int x, int y) const{
    validateCoords(x, y);
    return pixels[y][x];
}
void Layer::selectLayer(){
    for(QVector<Pixel>& vector : pixels){
        for(Pixel& p: vector){
            p.alpha = VISIBLE_ALPHA;
        }
    }
}
void Layer::hideLayer(){
    for(QVector<Pixel>& vector : pixels){
        for(Pixel& p: vector){
            p.alpha = HIDDEN_ALPHA;
        }
    }
}
void Layer::reflectVertical(){

}
void Layer::reflectHorizontal(){

}
void Layer::rotate90(){

}
void Layer::resize(int newSize){
    if(newSize < 0){
        throw std::runtime_error("Invalid size");
    }
    int diff = newSize - size;
    if(diff < 0){
        for(int i = 0; i<diff; i++){
            pixels.pop_back();
        }
        for(QVector<Pixel>& vector : pixels){
            for(int i = 0; i<diff; i++){
                vector.pop_back();
            }
        }
    }else if(diff > 0){
        QVector<Pixel> newColumn;
        for(int i = 0; i<newSize; i++){
            newColumn.push_back(Pixel(0,0,0,0));
        }
        for(int i = 0; i<diff; i++){
            pixels.push_back(newColumn);
        }
    }
    size = newSize;
}
void Layer::validateCoords(int x, int y) const{
    if(x < 0 || y < 0 || x >= size || y >= size){
        throw std::runtime_error("Invalid coordinates");
    }
}
