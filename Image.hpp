/*
Image class contains the RGB values of each pixel
This class contains function that takes top left corner, bottom right corner, and fill color
*/

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <fstream>
#include <vector>
#include "Constants.hpp"
// #include "Pixel.hpp"

class Image {
public:
    Image();

    // Maybe not needed
    // ~Image();

    // Turn image into BMP
    void generateImage(const char *fileName);

    // Colors in rectangle defined by top left and bottom right corner. Note: Does not create image, only changes image variable
    void colorRegion(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, Color color);

private:
    void writeHeaders(std::ofstream &of);

    void writeData(std::ofstream &of);

    BMPFILE_HEADER fileHeader;
    BMP_DIB_V3_HEADER dibHeader;
    BMP_COLOR_HEADER colorHeader;
    std::vector<uint8_t> image;
};

#endif
