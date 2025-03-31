/*
* Checked by Jake Heairld and Jacob Anderson
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
    const int pixelWidth = std::floor(pixelWidthF);
    const int pixelHeight = std::floor(pixelHeightF);

    //keep track of how many extra pixels of width/height to add
    int remainderWidth = width() - (pixelWidth * gridSize);
    int remainderHeight = height() - (pixelHeight * gridSize);

    // Loop through each pixel in the grid and render it
    for (unsigned int y = 0; y < gridSize; y++) {
        for (unsigned int x = 0; x < gridSize; x++) {
            const Pixel& pixel = currentImage[y * gridSize + x];
            QColor color(pixel.red, pixel.green, pixel.blue, pixel.alpha);

            //add an extra pixel of width/height to some of the pixels to even out the canvas size
            int extraWidth = 0;
            int extraHeight = 0;

            if(x < remainderWidth){
                extraWidth = 1;
            }
            if(y < remainderHeight){
                extraHeight = 1;
            }

            int adjustedWidth = pixelWidth + extraWidth;
            int adjustedHeight = pixelHeight + extraHeight;

            //calculate the x and y positions, shift the position a bit since some of the pixels have extra width/height
            int xpos = x * pixelWidth + std::min<int>(x, remainderWidth);
            int ypos = y * pixelHeight + std::min<int>(y, remainderHeight);

            painter.fillRect(
                xpos,
                ypos,
                adjustedWidth,
                adjustedHeight,
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
