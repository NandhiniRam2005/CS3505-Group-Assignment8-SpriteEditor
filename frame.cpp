#include "frame.h"

Frame::Frame(unsigned int width, unsigned int height): width(width), height(height) {}

Frame::~Frame() {

}

Frame::Frame(const Frame& other) {

}

void Frame::operator=(Frame other) {

}

Pixel** Frame::getLayeredImage() const {

}

Pixel** Frame::getRenderedImage() const {

}

void Frame::selectLayer(unsigned int index) {
    activeLayer = index;
}

void Frame::deleteLayer() {
    layers.remove(activeLayer);
    if (layers.size() == 0) {
        activeLayer = 0;
    } else {
        activeLayer = layers.size() - 1;
    }
}

void Frame::addLayer() {
    Layer newLayer(width, height);
    layers.append(newLayer);
    activeLayer = layers.size() - 1;
}

void Frame::resize(unsigned int newSize) {
    width = newSize;
    height = newSize;
    for (int i = 0; i < layers.size(); i++) {
        layers[i].resize(newSize);
    }
}

void Frame::paintPixels(unsigned int corner1, unsigned int corner2, const Pixel& color) {

}

void Frame::bucketFill(unsigned int x, unsigned int y, const Pixel& color) {

}

Pixel Frame::getPixel(unsigned int x, unsigned int y) const {

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

void Frame::rerenderImage() {

}

void Frame::deSelectCurrentLayer() {

}
