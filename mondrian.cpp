#include <cstdio>
#include <iostream>
#include "Image.hpp"
#include "Constants.hpp"

int main() {
    srand(RANDOMSEED);
    Image mondrianImage;
    std::cout << "Drawing...\n";
    mondrianImage.splitOrColor(0, 0, CANVASWIDTH - 1, CANVASHEIGHT - 1, true);
    std::cout << "Generating Image...\n";
    mondrianImage.generateBMP("file.bmp");
    std::cout << "Image Generated" << std::endl;
    return 0;
}