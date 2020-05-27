#include <cstdio>
#include <iostream>
#include "Image.hpp"
#include "Constants.hpp"

int main() {
    srand(RANDOMSEED);
    Image mondrianImage;
    // mondrianImage.colorRegion(200, 200, 500, 500, BLUE);
    // mondrianImage.colorRegion(0, CANVASHEIGHT - 1, CANVASWIDTH, CANVASHEIGHT, BLACK);       // Top line
    // mondrianImage.colorRegion(CANVASWIDTH - 1, CANVASHEIGHT, CANVASWIDTH, 0, BLACK);       // Right line
    // mondrianImage.colorRegion(0, 0, CANVASWIDTH, 0 + 1, BLACK);   // Bottom line
    // mondrianImage.colorRegion(0, 0, 0 + 1, CANVASHEIGHT, BLACK);   // Left line
    // mondrianImage.colorRegion(400, 400, 800, 402, BLACK);       // Top line
    std::cout << "Drawing...\n";
    mondrianImage.splitOrColor(0, 0, CANVASWIDTH - 1, CANVASHEIGHT - 1, true);
    std::cout << "Generating Image...\n";
    mondrianImage.generateBMP("file.bmp");
    std::cout << "Image Generated" << std::endl;
    return 0;
}