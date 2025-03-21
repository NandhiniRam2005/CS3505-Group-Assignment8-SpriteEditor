#ifndef FRAME_H
#define FRAME_H

#include "layer.h"
#include <vector>

using std::vector;

class Frame
{
public:
    Frame(unsigned int width, unsigned int height);
    ~Frame();
    Frame(const Frame& other);
    void operator=(Frame other);

    Pixel** getLayeredImage() const;
    Pixel** getRenderedImage() const;

    void selectLayer(unsigned int index);
    void deleteLayer();
    void addLayer();
    void resize(unsigned int newSize);

    void paintPixels(unsigned int corner1, unsigned int corner2, const Pixel& color);
    void bucketFill(unsigned int x, unsigned int y, const Pixel& color);
    Pixel getPixel(unsigned int x, unsigned int y) const;
    void reflectVertical();
    void reflectHorizontal();
    void rotate90();

private:
    std::vector<Layer> layers;
    unsigned int activeLayer;
    Pixel** layeredImage;
    unsigned int width;
    unsigned int height;

    void rerenderImage();
    void deSelectCurrentLayer();
};

#endif // FRAME_H
