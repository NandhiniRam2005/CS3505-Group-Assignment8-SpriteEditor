#include "pixeldisplay.h"
#include <QPainter>
#include <QPoint>

PixelDisplay::PixelDisplay(QWidget *parent)
    : QWidget{parent}, pixelResolutionWidth(32), pixelResolutionHeight(32)
{}

QPoint PixelDisplay::mapPixelCoordinateToUICoordinate(unsigned int pixelX, unsigned int pixelY) {
    const float cellW = width() / static_cast<float>(pixelResolutionWidth);
    const float cellH = height() / static_cast<float>(pixelResolutionHeight);
    return QPoint(pixelX * cellW, pixelY * cellH);
}

void PixelDisplay::drawPixel(unsigned int pixelX, unsigned int pixelY, Pixel currentPixel) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);

    const QPoint pos = mapPixelCoordinateToUICoordinate(pixelX, pixelY);
    const float cellW = width() / pixelResolutionWidth;
    const float cellH = height() / pixelResolutionHeight;

    painter.fillRect(pos.x(), pos.y(), cellW, cellH,
                     QColor(currentPixel.red, currentPixel.green,
                            currentPixel.blue, currentPixel.alpha));
}

void PixelDisplay::updateDrawnImage(const QVector<QVector<Pixel>> &image) {
    // Clear previous content
    QPainter cleaner(this);
    cleaner.eraseRect(rect());

    // Draw all pixels immediately
    for (int x = 0; x < image.size(); x++) {
        for (int y = 0; y < image[x].size(); y++) {
            drawPixel(x, y, image[x][y]);
        }
    }

    update(); // Force UI refresh
}
