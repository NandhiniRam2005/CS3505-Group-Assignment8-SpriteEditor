#ifndef LAYER_H
#define LAYER_H

#include "Pixel.h"

class Layer
{
public:
    Layer(unsigned int width, unsigned int height);
    ~Layer();
    bool operator==(const Layer& other) const;

    void paintPixels(unsigned int corner1, unsigned int corner2, const Pixel& color);
    void bucketFill(unsigned int x, unsigned int y, const Pixel& color);
    Pixel getPixel(unsigned int x, unsigned int y) const;
    void selectLayer();
    void hideLayer();
    void reflectVertical();
    void reflectHorizontal();
    void rotate90();
    void resize(unsigned int newSize);

private:
    Pixel** pixels;
    unsigned int width;
    unsigned int height;
};

#endif // LAYER_H
