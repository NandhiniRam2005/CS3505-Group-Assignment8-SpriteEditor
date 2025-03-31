/*
* Checked by Joel Rodriguez
The cpp file for pixel display.

A class which represents the pixels displayed for the frames.
It implements methods for mapping coordinates onto the canvas, setting grid size, and updating the drawn image.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan
Jake Heairld & Joseph Hamilton

March 30, 2025
*/

#include "pixeldisplay.h"

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

    const double pixelWidthF = ((double)width()) / gridSize;
    const double pixelHeightF = ((double)height()) / gridSize;

    QTransform transform;
    transform.scale(pixelWidthF, pixelHeightF);
    painter.setTransform(transform);

    // Loop through each pixel in the grid and render it
    for (unsigned int y = 0; y < gridSize; y++) {
        for (unsigned int x = 0; x < gridSize; x++) {
            const Pixel& pixel = currentImage[y * gridSize + x];
            QColor color(pixel.red, pixel.green, pixel.blue, pixel.alpha);

            painter.fillRect(
                x,
                y,
                1,
                1,
                color
                );
        }
    }
}


void PixelDisplay::updateDrawnImage(const Pixel* image) {
    for (unsigned int i = 0; i < gridSize * gridSize; i++) {
        currentImage[i] = image[i];
    }

    update();
}

void PixelDisplay::setGridSize(unsigned int newSize) {
    gridSize = newSize;
}
