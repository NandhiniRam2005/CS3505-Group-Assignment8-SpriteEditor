#ifndef FRAME_H
#define FRAME_H

#include "layer.h"
#include "pixel.h"
#include <QVector>

using std::vector;

class Frame
{
public:
    Frame(unsigned int size);
    ~Frame();
    Frame(const Frame& other);
    void operator=(Frame other);

    Pixel* getLayeredImage() const;
    Pixel* getRenderedImage() const;

    void selectLayer(unsigned int index);
    void deleteLayer();
    void addLayer();
    void resize(unsigned int newSize);

    void paintPixels(QPoint corner1, QPoint corner2, const Pixel& color);
    void bucketFill(unsigned int x, unsigned int y, const Pixel& color);
    Pixel getPixel(unsigned int x, unsigned int y) const;
    void reflectVertical();
    void reflectHorizontal();
    void rotate90();

private:
    QVector<Layer> layers;
    unsigned int activeLayer;
    unsigned int size;
};

#endif // FRAME_H
