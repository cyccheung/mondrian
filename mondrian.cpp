#include <cstdio>
#include <iostream>
#include "Image.hpp"
#include "Constants.hpp"

int main() {
    Image mondrianImage;
    // mondrianImage.colorRegion(0, 0, CANVASWIDTH, CANVASHEIGHT, BLUE);
    mondrianImage.generateBMP("file.bmp");
    return 0;
}