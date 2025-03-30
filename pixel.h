/*
The header file for pixel.

A class which represents a pixel in the canvas/image which has attributes for color and transparancy.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan
Jake Heairld & Joseph Hamilton

March 30, 2025
*/

#ifndef PIXEL_H
#define PIXEL_H

class Pixel
{

public:
    /**
     * Default constructor for creating a new Pixel object with values of zero (black and fiully transparent).
     */
    Pixel();

    /**
     * Custom constructor for creating a new Pixel object with specific color and transparency.
     * @param red - red value of the pixel
     * @param green - green value of the pixel
     * @param blue - blue component of the pixel
     * @param alpha - alpha (transparency) value of the pixel
     */
    Pixel(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

    /**
     * Equal operator to compare equality of two Pixel objects.
     * @param other - Pixel to compare with
     * @return true if the two Pixels have the same red, green, blue, and alpha values, false otherwise
     */
    bool operator==(const Pixel& other) const;

    /**
     * Inequal operator to compare two Pixel objects.
     * @param other - Pixel to compare with.
     * @return true if the two Pixels have different red, green, blue, or alpha values, false otherwise.
     */
    bool operator!=(const Pixel& other) const;

    /**
     * red value of the pixel ranging from 0 to 255.
     */
    unsigned char red;

    /**
     * green value of the pixel ranging from 0 to 255.
     */
    unsigned char green;

    /**
     * blue value of the pixel ranging from 0 to 255.
     */
    unsigned char blue;

    /**
     * alpha value of the pixel ranging from (0 - fully transparent and 255 - fully opaque)
     */
    unsigned char alpha;
};

/**
 * alpha value for hovered pixels
 */
const unsigned char HOVERED_ALPHA = 128;

/**
 * Alpha value of the pixels in an unselected layer (grayed out)
 */
const unsigned char HIDDEN_ALPHA = 50;

#endif
