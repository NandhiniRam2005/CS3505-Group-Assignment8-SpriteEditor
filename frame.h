/*
 * Checked by Nandhini Ramanathan
The header file for frame.

A class which represents a frame.
It represents an image frame consisting of layers of pixels.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan
Jake Heairld & Joseph Hamilton

March 30, 2025
*/

#ifndef FRAME_H
#define FRAME_H

#include "layer.h"
#include "pixel.h"
#include <QVector>

class Frame
{
public:
    /**
     * custom contrcutor thart creates a new Frame object with the given size.
     * @param size - size of the frame (square).
     */
    Frame(unsigned int size);

    /**
     * Destructor for the frame class.
     */
    ~Frame();


    /**
     * Copy constructor for creating a copy of the Frame.
     * @param other - Frame object to copy.
     */
    Frame(const Frame& other);

    /**
     * Assignment operator for the Frame class.
     * @param other - Frame object to assign.
     */
    void operator=(Frame other);

    /**
     * Returns the image with all layers applied, updated only if image has changed.
     * @return A pointer to the layered image.
     */
    Pixel* getLayeredImage();

    /**
     * Returns the final rendered image with all layers combined.
     * @return A pointer to the rendered image.
     */
    Pixel* getRenderedImage();

    /**
     * Selects the specified layer by index and sets it as the active layer.
     * Hides the current active layer and makes the new one active.
     * @param index - index of the layer to select.
     * @throws run time error if the index is out of bounds.
     */
    void selectLayer(unsigned int index);

    /**
     * Deletes the current layer.
     * @throws run time error if the layer is the last one in the frame.
     */
    void deleteLayer(int layerIndex);

    /**
     * Adds a new layer to the frame.
     */
    void addLayer();

    /**
     * add layer methiod overloaded to take a Layer parameter to be added to the sprite editor.
     * @param newLayer - the layer to be added
     */
    void addLayer(Layer newLayer);

    /**
     * Resizes the frame and all its layers to the new size.
     * @param newSize - new size for the frame and layers.
     */
    void resize(unsigned int newSize);

    /**
     * Paints pixels within the specified rectangular region on the active layer with the given color.
     * @param corner1 - top-left corner of the region to paint.
     * @param corner2 - bottom-right corner of the region to paint.
     * @param color - color to paint the region with.
     */
    void paintPixels(QPoint corner1, QPoint corner2, const Pixel& color);

    /**
     * Bucket fill starting from the specified coordinate position, filling all connected
     * pixels with the specified color.
     * @param x - x-coordinate of the starting position.
     * @param y - y-coordinate of the starting position.
     * @param color - color to fill the region with.
     */
    void bucketFill(unsigned int x, unsigned int y, const Pixel& color);

    /**
     * Gets the pixel at the specified coordinates in the active layer.
     * @param x - x-coordinate of the pixel to get.
     * @param y - y-coordinate of the pixel to get.
     * @return pixel at the given coordinates.
     */
    Pixel getPixel(unsigned int x, unsigned int y) const;

    /**
     * Reflects the active layer vertically.
     */
    void reflectVertical();

    /**
     * Reflects the active layer horizontally.
     */
    void reflectHorizontal();


    /**
     * Rotates the active layer by 90 degrees clockwise.
     */
    void rotate90();

    /**
     * Gets the layers in this frame.
     * @return a vector of layers containe din this frame.
     */
    QVector<Layer> getLayers();

private:
    /**
     * Renders the layered image and final rendered image based on the current state.
     */
    void renderImages();

    /**
     * vector of layers in the frame.
     */
    QVector<Layer> layers;

    /**
     * index of the currently active layer in teh farme.
     */
    unsigned int activeLayer;

    /**
     * size of the frame.
     */
    unsigned int size;

    /**
     * The image (array of pixels) with all the layers applied.
     */
    Pixel* layeredImage;

    /**
     * final rendered image as an array of pixels
     */
    Pixel* renderedImage;

    /**
     * Flag to indicate if the image has changed and needs to be rerendered.
     */
    bool imageChanged;
};

#endif
