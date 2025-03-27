#include "frame.h"
#include <stdexcept>
Frame::Frame(unsigned int size): size(size){
    layers.push_back(Layer(size));
    activeLayer = 0;
    layeredImage = new Pixel[size * size]();
    renderedImage = new Pixel[size * size]();
    imageChanged = false;
}

Frame::~Frame() {
    delete[] layeredImage;
    delete[] renderedImage;
}

Frame::Frame(const Frame& other) {
    layers = other.layers;
    size = other.size;
    activeLayer = other.activeLayer;
    renderedImage = new Pixel[size* size];
    layeredImage = new Pixel[size * size];
    imageChanged = true;
    renderImages();
}

void Frame::operator=(Frame other) {
    std::swap(layers, other.layers);
    std::swap(activeLayer, other.activeLayer);
    std::swap(size, other.size);
    std::swap(layeredImage, other.layeredImage);
    std::swap(renderedImage, other.renderedImage);
    std::swap(imageChanged, other.imageChanged);
}

Pixel* Frame::getLayeredImage() {
    if(!imageChanged){
        return layeredImage;
    }
    renderImages();
    return layeredImage;
}

Pixel* Frame::getRenderedImage() {
    if(!imageChanged){
        return renderedImage;
    }
    renderImages();
    return renderedImage;
}

void Frame::renderImages(){
    delete[] layeredImage;
    delete[] renderedImage;

    layeredImage = new Pixel[size * size]();
    renderedImage = new Pixel[size * size]();
    for(Layer& layer : layers){
        const Pixel* layerPixels = layer.getLayer();
        for(unsigned int i = 0; i<size*size; i++){
            if(layerPixels[i].alpha != 0){
                layeredImage[i] = layerPixels[i];
                renderedImage[i] = layeredImage[i];
            }
        }
    }
    imageChanged = false;
}

void Frame::selectLayer(unsigned int index) {
    if(index >= layers.size()){
        throw std::runtime_error("Invalid layer index");
    }
    layers[activeLayer].hideLayer();
    activeLayer = index;
    layers[activeLayer].selectLayer();
    imageChanged = true;
}

void Frame::deleteLayer() {
    if(layers.size()==1){
        throw std::runtime_error("Cannot delete last layer in a frame");
    }
    layers.pop_back();
    if(activeLayer >= layers.size()){
        activeLayer = layers.size()-1;
    }
    imageChanged = true;
}

void Frame::addLayer() {
    layers.push_back(Layer(size));
    imageChanged = true;
}

void Frame::resize(unsigned int newSize) {
    for(Layer& layer : layers){
        layer.resize(newSize);
    }
    size = newSize;
    imageChanged = true;
}

void Frame::paintPixels(QPoint corner1, QPoint corner2, const Pixel& color) {
    layers[activeLayer].paintPixels(corner1, corner2, color);
    imageChanged = true;
}

void Frame::bucketFill(unsigned int x, unsigned int y, const Pixel& color) {
    layers[activeLayer].bucketFill(x, y, color);
    imageChanged = true;
}

Pixel Frame::getPixel(unsigned int x, unsigned int y) const {
    return layers[activeLayer].getPixel(x, y);
}

void Frame::reflectVertical() {
    layers[activeLayer].reflectVertical();
    imageChanged = true;
}

void Frame::reflectHorizontal() {
    layers[activeLayer].reflectHorizontal();
    imageChanged = true;
}

void Frame::rotate90() {
    layers[activeLayer].rotate90();
    imageChanged = true;
}

QVector<Layer> Frame::getLayers() {
    return layers;
}
