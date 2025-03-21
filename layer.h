#ifndef LAYER_H
#define LAYER_H
#include <QVector>
#include <QPoint>
#include "pixel.h"

class Layer
{
public:
    Layer(int width, int height);
    ~Layer();
    Layer(const Layer& other);
    void operator=(Layer other);

    void paintPixels(QPoint corner1, QPoint corner2, const Pixel& color);
    void bucketFill(int x, int y, const Pixel& color);
    Pixel getPixel(int x, int y) const;
    void selectLayer();
    void hideLayer();
    void reflectVertical();
    void reflectHorizontal();
    void rotate90();
    void resize(int newSize);

private:
    QVector<QVector<Pixel>> pixels;
    int width;
    int height;
    void validateCoords(int x, int y) const;
    const unsigned char VISIBLE_ALPHA = 255;
    const unsigned char HIDDEN_ALPHA = 128;
};

#endif // LAYER_H
