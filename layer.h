/*
The header file for layer.

A class which represents a single layer in an image/canvas, which contains a grid of pixels.
It has methods for modifying, reflecting, rotating, and resizing the layer.
The class also contains tools to fill regions, selecting or hiding the layer,
and getting individual pixels.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan
Jake Heairld & Joseph Hamilton

March 30, 2025
*/

#ifndef LAYER_H
#define LAYER_H

#include "pixel.h"
#include <QPoint>

class Layer
{
public:
    /**
     * Default constructor for creating a new Layer object.
     * Initializes an empty layer with no pixels.
     */
    Layer();

    /**
     * Custom constructor for creating a new Layer object with a specific size.
     * @param size - width and height of the square layer (in pixels).
     */
    Layer(int size);

    /**
     * Destructor for the Layer class.
     */
    ~Layer();

    /**
     * Copy constructor for creating a new Layer object from another existing Layer, duplicating it.
     * @param other - Layer to copy.
     */
    Layer(const Layer& other);

    /**
     * Assignment operator for assigning one Layer to another.
     * @param other - Layer to assign to the current one to
     */
    void operator=(Layer other);

    /**
     * Paints a region of pixels with a given color.
     * @param corner1 - top-left corner coordinate of the rectangle
     * @param corner2 - bottom-right corner coordinate of the rectangle
     * @param color - color to paint the pixels with.
     */
    void paintPixels(QPoint corner1, QPoint corner2, const Pixel& color);

    /**
     * Fills a region using the given starting pixel with a new color using a depth-first search.
     * @param x - x-coordinate of the starting pixel.
     * @param y - y-coordinate of the starting pixel.
     * @param color - color to fill the region with.
     */
    void bucketFill(int x, int y, const Pixel& color);

    /**
     * Gets the pixel at a specific position in the layer.
     * @param x - x-coordinate of the pixel.
     * @param y - y-coordinate of the pixel.
     * @return The pixel at the specified coordinates.
     */
    Pixel getPixel(int x, int y) const;

    /**
     * Selects the layer by making all non-transparent pixels fully opaque to be selected
     */
    void selectLayer();

    /**
     * Hides the layer by making all non-transparent pixels look grayed out (changing its alpha)
     */
    void hideLayer();

    /**
     * Reflects the layer vertically.
     */
    void reflectVertical();

    /**
     * Reflects the layer horizontally.
     */
    void reflectHorizontal();

    /**
     * Rotates the layer by 90 degrees clockwise.
     */
    void rotate90();

    /**
     * Resizes the layer to a new size, preserving pixel content within bounds.
     * @param newSize - new size of the layer
     * @throws run time error if the new size is invalid (negative).
     */
    void resize(int newSize);

    /**
     * Gets a pointer to the array of pixels in this layer
     * @return a pointer to the pixels.
     */
    Pixel* getLayer() const;

private:
    /**
     * Helper function for doing depth-first search in the bucket fill method
     * @param x - current x-coordinate.
     * @param y - current y-coordinate.
     * @param visits - array tracking visited pixels.
     * @param color - color to fill with.
     * @param currentColor - color currently at the coordinate position.
     */
    void bucketFillDfs(int x, int y, bool* visits, const Pixel& color, const Pixel& currentColor);

    /**
     * Validates if the given coordinates are within the bounds of the layer.
     * @param x - x-coordinate to validate.
     * @param y - y-coordinate to validate.
     * @throws run time error if the coordinates are out of bounds.
     */
    void validateCoords(int x, int y) const;

    /**
     * Pointer (array) of pixels in this layer
     */
    Pixel* pixels;

    /**
     * Size of the layer (width and height - sqaure)
     */
    int size;
};

#endif
