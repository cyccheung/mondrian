/*
Image class contains the RGB values of each pixel
This class contains function that takes top left corner, bottom right corner, and fill color
*/

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <fstream>
#include <vector>
#include <cstdlib>
#include "Constants.hpp"

class Image {
public:
    // Create white canvas of correct size
    Image();

    // Turn image into BMP
    void generateBMP(const char *fileName);

    // Colors in rectangle defined by top left and bottom right corner. Note: Does not create or edit actual image, only changes private image variable
    void colorRegion(int bottomLeftX, int bottomLeftY, int topRightX, int topRightY, Color color);

    // Called recursively
    // Either split region up into four smaller regions and call function on each of the four regions
    // Or region is colored (base case)
    void splitOrColor(int bottomLeftX, int bottomLeftY, int topRightX, int topRightY, bool first);

private:
    // Used by generateImage
    void writeHeaders(std::ofstream &of);

    // Used by generateImage
    void writeData(std::ofstream &of);

    BMPFILE_HEADER fileHeader;
    BMP_DIB_V3_HEADER dibHeader;
    BMP_COLOR_HEADER colorHeader;
    std::vector<uint8_t> image;
};

#endif
