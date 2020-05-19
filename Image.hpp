/*
Image class contains the RGB values of each pixel
This class contains function that takes top left corner, bottom right corner, and fill color
*/

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "Constants.hpp"
#include "Pixel.hpp"

class Image {
public:
    Image();

    // Colors in rectangle defined by top left and bottom right corner
    void colorRegion(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, Color color);

private:
    Pixel image[CANVASHEIGHT][CANVASWIDTH];
};

#endif
