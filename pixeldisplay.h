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

    QPoint mapPixelCoordinateToUICoordinate(unsigned int pixelX, unsigned int pixelY);

    void drawPixel(unsigned int pixelX, unsigned int pixelY, Pixel currentPixel);

public slots:
    void updateDrawnImage(Pixel[][]);

signals:
};

#endif // PIXELDISPLAY_H
