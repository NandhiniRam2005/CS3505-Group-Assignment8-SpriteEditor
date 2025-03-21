#ifndef PIXEL_H
#define PIXEL_H

class Pixel
{
public:
    Pixel();
    Pixel(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
    bool operator==(const Pixel& other) const;
    bool operator!=(const Pixel& other) const;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
};

#endif // PIXEL_H
