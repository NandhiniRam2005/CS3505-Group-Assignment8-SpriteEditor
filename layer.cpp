#include "layer.h"
#include "pixel.h"
#include <QPoint>
#include <stdexcept>

Layer::Layer():pixels(nullptr), size(0) {}

Layer::Layer(int size): size(size){
    pixels = new Pixel[size * size];
    for(int i = 0; i<size * size; i++){
        pixels[i] = Pixel(0,0,0,0);
    }
}

Layer::~Layer(){
    delete[] pixels;
}

Layer::Layer(const Layer& other){
    size = other.size;
    pixels = new Pixel[size * size];
    for(int i = 0; i<size * size; i++){
        pixels[i] = other.pixels[i];
    }
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
            pixels[i*size + j] = color;
        }
    }
}

void Layer::bucketFill(int x, int y, const Pixel& color){
    validateCoords(x, y);
    bool* visits = new bool[size * size]{};
    Pixel& currentColor = pixels[y * size + x];
    bucketFillDfs(x, y, visits, color, currentColor);
    delete[] visits;
}

void Layer::bucketFillDfs(int x, int y, bool* visits, const Pixel& color, const Pixel& currentColor){
    if(x < 0 || y < 0 || x >= size || y >= size || visits[y*size + x] || pixels[y*size + x] != currentColor){
        return;
    }
    visits[y*size + x] = true;
    pixels[y*size + x] = color;
    bucketFillDfs(x-1, y, visits, color, currentColor);
    bucketFillDfs(x+1, y, visits, color, currentColor);
    bucketFillDfs(x, y-1, visits, color, currentColor);
    bucketFillDfs(x, y+1, visits, color, currentColor);
}

Pixel Layer::getPixel(int x, int y) const{
    validateCoords(x, y);
    return pixels[y* size + x];
}

void Layer::selectLayer(){
    for(int i = 0; i< size * size; i++){
        pixels[i].alpha = VISIBLE_ALPHA;
    }
}

void Layer::hideLayer(){
    for(int i = 0; i< size * size; i++){
        pixels[i].alpha = HIDDEN_ALPHA;
    }
}

void Layer::reflectVertical(){
    for (int i = 0; i < size / 2; i++) {
        for (int j = 0; j < size; j++) {
            std::swap(pixels[i * size + j], pixels[(size - 1 - i) * size + j]);
        }
    }
}

void Layer::reflectHorizontal(){
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size / 2; j++) {
            std::swap(pixels[i * size + j], pixels[i * size + (size - 1 - j)]);
        }
    }
}

void Layer::rotate90(){
    Pixel* rotated = new Pixel[size * size];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            rotated[j * size + (size - 1 - i)] = pixels[i * size + j];
        }
    }
    std::swap(pixels, rotated);
    delete[] rotated;
}

void Layer::resize(int newSize){
    if(newSize < 0){
        throw std::runtime_error("Invalid size");
    }
    if(newSize == size){
        return;
    }
    Pixel* newPixels = new Pixel[newSize * newSize]{};

    int smaller = std::min(newSize, size);
    for(int i = 0; i<smaller; i++){
        for(int j = 0; j<smaller; j++){
            newPixels[i * newSize + j] = pixels[i * size + j];
        }
    }
    size = newSize;
    std::swap(pixels, newPixels);
    delete[] newPixels;
}

void Layer::validateCoords(int x, int y) const{
    if(x < 0 || y < 0 || x >= size || y >= size){
        throw std::runtime_error("Invalid coordinates");
    }
}
