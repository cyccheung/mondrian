#ifndef PIXEL_HPP
#define PIXEL_HPP


#include "Constants.hpp"

class Pixel {
public:
    Pixel();

    void setPixel(int xIn, int yIn, Color colorIn);

    void setPixel(Color colorIn);

    int getX();

    int getY();

    Color getColor();
    
private:
    int x;
    int y;
    Color color;
};

#endif