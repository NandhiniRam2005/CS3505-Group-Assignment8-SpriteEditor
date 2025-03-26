#include "pixeldisplay.h"
#include <QPainter>
#include <QPoint>

PixelDisplay::PixelDisplay(QWidget *parent)
    : QWidget(parent), gridSize(32)
{}

QPoint PixelDisplay::mapPixelCoordinateToUICoordinate(unsigned int pixelX, unsigned int pixelY) {

}

void PixelDisplay::drawPixel(unsigned int pixelX, unsigned int pixelY, Pixel currentPixel) {

}

void PixelDisplay::updateDrawnImage(const Pixel* image) {

}

void PixelDisplay::paintEvent(QPaintEvent* event) {

}
