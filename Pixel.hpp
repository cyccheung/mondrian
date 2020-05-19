#ifndef PIXEL_HPP
#define PIXEL_HPP


#include "Constants.hpp"

class Pixel {
public:
    Pixel();

    void setPixel(int x, int y, Color color);

    int getX();

    int getY();

    Color getColor();
    
private:
    int x;
    int y;
    Color color;
};

#endif