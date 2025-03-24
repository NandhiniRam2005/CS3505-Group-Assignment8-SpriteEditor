/*
The header file for pixel display.

A class which represents the pixels displayed for the frames.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan
Jake Heairld & Joseph Hamilton

March 21, 2025
*/
#ifndef PIXELDISPLAY_H
#define PIXELDISPLAY_H

#include <QWidget>
#include "pixel.h"

class PixelDisplay : public QWidget
{
    Q_OBJECT

public:
    /**
     * Creates a new pixel display object
     * @param parent - the parent of the model
     */
    explicit PixelDisplay(QWidget *parent = nullptr);

private:
    unsigned int pixelResolutionWidth;
    unsigned int pixelResolutionHeight;

    /**
     * Maps the pixel coordinates to the correlated UI coordinate
     * @param pixelX - The pixel's x coordinate
     * @param pixelY - The pixel's y coordinate
     * @return A QPoint tuple with the UI coordinate conversion of the pixel coordinates
     */
    QPoint mapPixelCoordinateToUICoordinate(unsigned int pixelX, unsigned int pixelY);

    /**
     * Helper method for updating drawn image.Draws a pixel at a specific location
     * @param pixelX - The pixel's x coordinate
     * @param pixelY - The pixel's y coordinate
     * @param currentPixel - The pixel to be drawn
     */
   // void drawPixel(unsigned int pixelX, unsigned int pixelY, Pixel currentPixel);

public slots:
    /**
     * Updates the pixel image displayed
     * @param image - The image to be displayed
     */
   // void updateDrawnImage(const QVector<QVector<Pixel>> &image);

signals:
};

#endif // PIXELDISPLAY_H
