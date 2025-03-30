/*
The cpp file for frame.

A class which represents a frame, implementing methods to render, get, manipulate, and slect frames.
It represents an image frame consisting of layers of pixels.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan
Jake Heairld & Joseph Hamilton

March 30, 2025
*/

#include "frame.h"

#include <stdexcept>
#include <iostream>

using std::swap;
using std::runtime_error;

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
    swap(layers, other.layers);
    swap(activeLayer, other.activeLayer);
    swap(size, other.size);
    swap(layeredImage, other.layeredImage);
    swap(renderedImage, other.renderedImage);
    swap(imageChanged, other.imageChanged);
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

     // Combines layers into the rendered and layered images
    for(Layer& layer : layers){
        const Pixel* layerPixels = layer.getLayer();
        for(unsigned int i = 0; i<size*size; i++){
            if(layerPixels[i].alpha != 0){
                layeredImage[i] = layerPixels[i];
                renderedImage[i] = layeredImage[i];

                if(renderedImage[i].alpha == HIDDEN_ALPHA){
                    renderedImage[i].alpha = 255;
                }
            }
        }
    }

    const Pixel* layerPixels = layers[activeLayer].getLayer();

    // Includes the active layer's pixels in the layered image
    for(unsigned int i = 0; i<size*size; i++){
        if(layerPixels[i].alpha != 0){
            layeredImage[i] = layerPixels[i];
        }
    }

    imageChanged = false;
}

void Frame::selectLayer(unsigned int index) {
    if(index >= layers.size()){
        throw runtime_error("Invalid layer index");
    }

    layers[activeLayer].hideLayer();
    activeLayer = index;
    layers[activeLayer].selectLayer();
    imageChanged = true;
}

void Frame::deleteLayer(int layerIndex) {
    if(layers.size()==1){
        throw runtime_error("Cannot delete last layer in a frame");
    }

    if(layerIndex >= layers.size() || layerIndex < 0){
        throw runtime_error("Invalid layer index");
    }

    layers.removeAt(layerIndex);
    activeLayer = 0;
    imageChanged = true;
}

void Frame::addLayer() {
    layers.push_back(Layer(size));
    imageChanged = true;
}

void Frame::addLayer(Layer newLayer){
    layers.push_back(newLayer);
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
