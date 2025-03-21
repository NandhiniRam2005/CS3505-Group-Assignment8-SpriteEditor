#include "frame.h"
#include <stdexcept>
Frame::Frame(unsigned int size): size(size){
    layers.push_back(Layer(size));
    activeLayer = 0;
}

Frame::~Frame() {

}

Frame::Frame(const Frame& other) {
    layers = other.layers;
    activeLayer = other.activeLayer;
    size = other.size;
}

void Frame::operator=(Frame other) {
    std::swap(layers, other.layers);
    std::swap(activeLayer, other.activeLayer);
    std::swap(size, other.size);
}

Pixel* Frame::getLayeredImage() const {

}

Pixel* Frame::getRenderedImage() const {

}

void Frame::selectLayer(unsigned int index) {
    if(index >= layers.size()){
        throw std::runtime_error("Invalid layer index");
    }
    layers[activeLayer].hideLayer();
    activeLayer = index;
    layers[activeLayer].selectLayer();
}

void Frame::deleteLayer() {
    if(layers.size()==1){
        throw std::runtime_error("Cannot delete last layer in a frame");
    }
    layers.pop_back();
    if(activeLayer >= layers.size()){
        activeLayer = layers.size()-1;
    }
}

void Frame::addLayer() {
    layers.push_back(Layer(size));
}

void Frame::resize(unsigned int newSize) {
    for(Layer& layer : layers){
        layer.resize(newSize);
    }
    size = newSize;
}

void Frame::paintPixels(QPoint corner1, QPoint corner2, const Pixel& color) {
    layers[activeLayer].paintPixels(corner1, corner2, color);
}

void Frame::bucketFill(unsigned int x, unsigned int y, const Pixel& color) {
    layers[activeLayer].bucketFill(x, y, color);
}

Pixel Frame::getPixel(unsigned int x, unsigned int y) const {
    return layers[activeLayer].getPixel(x, y);
}

void Frame::reflectVertical() {
    layers[activeLayer].reflectVertical();
}

void Frame::reflectHorizontal() {
    layers[activeLayer].reflectHorizontal();
}

void Frame::rotate90() {
    layers[activeLayer].rotate90();
}
