#include "pixel.h"

Pixel::Pixel(): red(0), green(0), blue(0), alpha(0){}

Pixel::Pixel(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
    :red(red), green(green), blue(blue), alpha(alpha){
}

bool Pixel::operator==(const Pixel& other) const{
    return (red == other.red) && (green==other.green) && (blue==other.blue) && (alpha == other.alpha);
}

bool Pixel::operator!=(const Pixel& other) const{
    return (red != other.red) || (green !=other.green) || (blue !=other.blue) || (alpha != other.alpha);
}
