#include "pixeldisplay.h"

#include <QPainter>
#include <QPoint>
#include <QRect>

PixelDisplay::PixelDisplay(QWidget *parent) : QWidget(parent), gridSize(32), currentImage(64 * 64) {
}

QPoint PixelDisplay::mapPixelCoordinateToUICoordinate(unsigned int pixelX, unsigned int pixelY) {
    // Calculate the size of each pixel based on the widget's size
    int pixelWidth = width() / gridSize;
    int pixelHeight = height() / gridSize;

    // Calculate the UI coordinates for the top-left corner of the pixel
    int uiX = pixelX * pixelWidth;
    int uiY = pixelY * pixelHeight;

    return QPoint(uiX, uiY);
}

void PixelDisplay::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);

    QPainter painter(this);
    const int pixelWidth = width() / gridSize;
    const int pixelHeight = height() / gridSize;

    for (unsigned int y = 0; y < gridSize; ++y) {
        for (unsigned int x = 0; x < gridSize; ++x) {
            const Pixel& pixel = currentImage[y * gridSize + x];
            QColor color(pixel.red, pixel.green, pixel.blue, pixel.alpha);

            painter.fillRect(
                x * pixelWidth,
                y * pixelHeight,
                pixelWidth,
                pixelHeight,
                color
                );
        }
    }
}

void PixelDisplay::updateDrawnImage(const Pixel* image) {
    // Iterate through the entire image array and draw each pixel
    for (unsigned int i = 0; i < gridSize * gridSize; i++) {
        currentImage[i] = image[i];
    }
    update(); // Schedule a repaint
}

void PixelDisplay::setGridSize(unsigned int newSize) {
    gridSize = newSize;
}
