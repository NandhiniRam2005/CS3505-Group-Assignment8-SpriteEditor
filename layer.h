#ifndef LAYER_H
#define LAYER_H
#include <QPoint>
#include "pixel.h"

class Layer
{
public:
    Layer();
    Layer(int size);
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
    void bucketFillDfs(int x, int y, bool* visits, const Pixel& color, const Pixel& currentColor);
    Pixel* pixels;
    int size;
    void validateCoords(int x, int y) const;
    const unsigned char VISIBLE_ALPHA = 255;
    const unsigned char HIDDEN_ALPHA = 128;
};

#endif // LAYER_H
