#include "pixeldisplay.h"
#include <QPainter>
#include <QPoint>

PixelDisplay::PixelDisplay(QWidget *parent)
    : QWidget(parent),
    currentImage(nullptr),
    gridSize(32)  // Default grid size
{
    setMouseTracking(true);

    // Initialize default white background pixels
    defaultImage.resize(32 * 32, Pixel(255, 255, 255, 255));
}

void PixelDisplay::updateDrawnImage(const Pixel* image, unsigned int size)
{
    currentImage = image;
    gridSize = size;
    update(); // Trigger repaint
}

void PixelDisplay::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // Always draw white background first
    const Pixel* drawImage = currentImage ? currentImage : defaultImage.data();
    const unsigned int drawSize = currentImage ? gridSize : 32;

    const float cellW = width() / static_cast<float>(drawSize);
    const float cellH = height() / static_cast<float>(drawSize);

    // Draw all pixels (including white background)
    for (unsigned int y = 0; y < drawSize; ++y) {
        for (unsigned int x = 0; x < drawSize; ++x) {
            const Pixel& pixel = drawImage[y * drawSize + x];
            QColor color(pixel.red, pixel.green, pixel.blue, pixel.alpha);

            // Force alpha to 255 if using default image
            if (!currentImage) color.setAlpha(255);

            painter.fillRect(QRectF(x * cellW, y * cellH, cellW, cellH), color);
        }
    }
}
