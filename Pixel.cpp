#include "Pixel.hpp"

Pixel::Pixel() {
    x = 0;
    y = 0;
    color = white;
}

void Pixel::setPixel(int xIn, int yIn, Color colorIn) {
    x = xIn;
    y = yIn;
    color = colorIn;
}

int Pixel::getX() {
    return x;
}

int Pixel::getY() {
    return y;
}

Color Pixel::getColor() {
    return color;
}