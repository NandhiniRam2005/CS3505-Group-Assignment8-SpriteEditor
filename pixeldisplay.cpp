#include "pixeldisplay.h"
#include <QPainter>
#include <QPoint>
#include <QRect>

PixelDisplay::PixelDisplay(QWidget *parent) : QWidget(parent), gridSize(32), painter(this) {}

QPoint PixelDisplay::mapPixelCoordinateToUICoordinate(unsigned int pixelX, unsigned int pixelY) {
    // Calculate the size of each pixel based on the widget's size
    int pixelWidth = width() / gridSize;
    int pixelHeight = height() / gridSize;

    // Calculate the UI coordinates for the top-left corner of the pixel
    int uiX = pixelX * pixelWidth;
    int uiY = pixelY * pixelHeight;

    return QPoint(uiX, uiY);
}

void PixelDisplay::drawPixel(unsigned int pixelX, unsigned int pixelY, Pixel currentPixel) {
    // Calculate the size of each pixel based on the widget's size
    int pixelWidth = width() / gridSize;
    int pixelHeight = height() / gridSize;

    // Set the brush color based on the pixel's color
    QColor pixelColor(currentPixel.red, currentPixel.green, currentPixel.blue);
    painter.setBrush(pixelColor);
    painter.setPen(pixelColor);

    // Calculate the rectangle for the pixel
    QRect pixelRect(
        pixelX * pixelWidth,  // x
        pixelY * pixelHeight, // y
        pixelWidth,
        pixelHeight
        );

    // Draw the pixel
    painter.drawRect(pixelRect);
}

void PixelDisplay::updateDrawnImage(const Pixel* image) {
    // Iterate through the entire image array and draw each pixel
    for (unsigned int y = 0; y < gridSize; ++y) {
        for (unsigned int x = 0; x < gridSize; ++x) {
            // Calculate the index in the 1D array
            unsigned int index = y * gridSize + x;

            // Draw the pixel at its corresponding location
            drawPixel(x, y, image[index]);
        }
    }

    // Force a repaint of the widget
    update();
}

void PixelDisplay::paintEvent(QPaintEvent* event) {


    QWidget::paintEvent(event);



    update();
}
