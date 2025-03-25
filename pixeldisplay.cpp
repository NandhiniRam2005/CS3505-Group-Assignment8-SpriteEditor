#include "pixeldisplay.h"
#include <QPoint>

PixelDisplay::PixelDisplay(QWidget *parent)
    : QWidget{parent}, pixelResolutionWidth(32), pixelResolutionHeight(32) // example 32x32 pixel resolution
{}

QPoint PixelDisplay::mapPixelCoordinateToUICoordinate(unsigned int pixelX, unsigned int pixelY) {
    unsigned int uiX = pixelX * (800 / pixelResolutionWidth); // 800 is the widget width
    unsigned int uiY = pixelY * (800 / pixelResolutionHeight); // 800 is the widget height
    return QPoint(uiX, uiY);
}


