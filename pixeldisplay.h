/*
 * Checked by Nandhini Ramanathan
The header file for pixel display.

A class which represents the pixels displayed for the frames.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan
Jake Heairld & Joseph Hamilton

March 30, 2025
*/

#ifndef PIXELDISPLAY_H
#define PIXELDISPLAY_H

#include "pixel.h"
#include <QWidget>
#include <QPainter>

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
    /**
     * Maps the pixel coordinates to the correlated UI coordinate
     * @param pixelX - The pixel's x coordinate
     * @param pixelY - The pixel's y coordinate
     * @return A QPoint tuple with the UI coordinate conversion of the pixel coordinates
     */
    QPoint mapPixelCoordinateToUICoordinate(unsigned int pixelX, unsigned int pixelY);

    /**
     * Stores the grid size used to render pixels
     */
    unsigned int gridSize;

    /**
     * Stores the current image as a collection of pixels
     */
    QVector<Pixel> currentImage;

protected:
    /**
     * Handles the painting of pixels onto the widget.
     */
    void paintEvent(QPaintEvent* event) override;

public slots:
    /**
     * Updates the pixel image displayed.
     * @param image - The image to be displayed
     */
    void updateDrawnImage(const Pixel* image);

    /**
     * Sets the grid size for the display.
     * @param GridSize - new grid size value.
     */
    void setGridSize(unsigned int GridSize);
};

#endif
