#include "Image.hpp"

// Create white canvas
Image::Image() {
    for(int i = 0; i < CANVASHEIGHT; i++) {
        for(int j = 0; j < CANVASWIDTH; j++) {
            // Default to white
            image.push_back(255);     // B
            image.push_back(255);     // G
            image.push_back(255);     // R
            image.push_back(255);     // A
        }
    }
    // std::cout << "Image Num Elements: " << image.size() << std::endl;
}

void Image::generateBMP(const char *fileName) {
    std::ofstream of{ fileName, std::ios_base::binary };
    dibHeader.width = CANVASWIDTH;
    dibHeader.height = CANVASHEIGHT;
    if(of) {
        dibHeader.size = sizeof(BMP_DIB_V3_HEADER) + sizeof(BMP_COLOR_HEADER);
        fileHeader.offsetData = sizeof(BMPFILE_HEADER) + sizeof(BMP_DIB_V3_HEADER) + sizeof(BMP_COLOR_HEADER);
        dibHeader.bitCount = 32;
        dibHeader.compression = 3;
        fileHeader.fileSize = fileHeader.offsetData + image.size();
        writeHeaders(of);
        writeData(of);
    }
    else {
        throw std::runtime_error("Unable to open output image file");
    }
}

void Image::colorRegion(int bottomLeftX, int bottomLeftY, int topRightX, int topRightY, Color color) {
    assert(bottomLeftX >= 0);
    assert(bottomLeftY >= 0);
    assert(topRightX < CANVASWIDTH);
    assert(topRightY < CANVASHEIGHT);
    assert(bottomLeftX < topRightX);
    assert(bottomLeftY < topRightY);
    for(int i = bottomLeftY; i <= topRightY; i++) {
        for(int j = bottomLeftX; j <= topRightX; j++) {
            assert(NUMCHANNELS * (i * CANVASWIDTH + j) <= NUMCHANNELS * CANVASWIDTH * CANVASHEIGHT - 4);
            image[NUMCHANNELS * (i * CANVASWIDTH + j) + 0] = color == RED ? 0        // Blue channel
                                                            :color == YELLOW ? 1
                                                            :color == BLUE ? 149
                                                            :color == WHITE ? 255
                                                            : 0;
            image[NUMCHANNELS * (i * CANVASWIDTH + j) + 1] = color == RED ? 1        // Green channel
                                                            :color == YELLOW ? 201
                                                            :color == BLUE ? 80
                                                            :color == WHITE ? 255
                                                            : 0;
            image[NUMCHANNELS * (i * CANVASWIDTH + j) + 2] = color == RED ? 221      // Red channel
                                                            :color == YELLOW ? 250
                                                            :color == BLUE ? 34
                                                            :color == WHITE ? 255
                                                            : 0;
            image[NUMCHANNELS * (i * CANVASWIDTH + j) + 3] = 255;                    // Alpha channel                                         
        }
    }
}

void Image::splitOrColor(int bottomLeftX, int bottomLeftY, int topRightX, int topRightY, bool first) {
    assert(bottomLeftX >= 0);
    assert(bottomLeftY >= 0);
    assert(topRightX < CANVASWIDTH);
    assert(topRightY < CANVASHEIGHT);
    assert(bottomLeftX < topRightX);
    assert(bottomLeftY < topRightY);
    bool split = false;     // Whether region will be split up
    int splitX, splitY;     // Coordinates of point where region will be split up
    int randomInt = 0;

    // Draw black outline, 2 pixels thick, of this region. Do not draw if called on entire canvas
    if(!first) {
        colorRegion(bottomLeftX, topRightY - 1, topRightX, topRightY, BLACK);       // Top line
        colorRegion(topRightX - 1, bottomLeftY, topRightX, topRightY, BLACK);       // Right line
        colorRegion(bottomLeftX, bottomLeftY, topRightX, bottomLeftY + 1, BLACK);   // Bottom line
        colorRegion(bottomLeftX, bottomLeftY, bottomLeftX + 1, topRightY, BLACK);   // Left line
    }

    // Decide if split or color
    // If longer edge is longer than threshold edge length, always split
    if(topRightX - bottomLeftX > UPPERTHRESHOLD || topRightY - bottomLeftY > UPPERTHRESHOLD) {
        split = true;
    }
    // If shorter edge is shorter than threshold edge length, always color
    else if(topRightX - bottomLeftX < LOWERTHRESHOLD || topRightY - bottomLeftY < LOWERTHRESHOLD) {
        split = false;
    }
    // Else randomly decide
    else {
        // Generate random number between 0 to 99, if less than region area divided by canvas area, split
        randomInt = rand() % 100;
        split = randomInt < (((topRightX - bottomLeftX) * (topRightY - bottomLeftY) * 100) / (CANVASHEIGHT * CANVASWIDTH));
    }

    // Do the splitting or coloring
    if(split) {
        // Generate random point near the middle of the region (25% to 75% of sides)
        // randomInt = (rand() % 50) + 25;
        randomInt = rand() % (int)floor((topRightX - bottomLeftX) / 2);
        // splitX = bottomLeftX + floor((randomInt * (topRightX - bottomLeftX)) / 100);
        splitX = bottomLeftX + randomInt + (int)(0.25 * (topRightX - bottomLeftX));
        // randomInt = (rand() % 50) + 25;
        randomInt = rand() % (int)floor((topRightY - bottomLeftY) / 2);
        // splitY = bottomLeftY + floor((randomInt * (topRightY - bottomLeftY)) / 100);
        splitY = bottomLeftY + randomInt + (int)(0.25 * (topRightY - bottomLeftY));

        // Recursively call function on each of the four regions
        splitOrColor(splitX, splitY, topRightX, topRightY, false);         // Top Right Region
        splitOrColor(bottomLeftX, splitY, splitX, topRightY, false);       // Top Left Region
        splitOrColor(bottomLeftX, bottomLeftY, splitX, splitY, false);     // Bottom Left Region
        splitOrColor(splitX, bottomLeftY, topRightX, splitY, false);       // Bottom Right Region
    }
    else {
        Color chosenColor;
        randomInt = rand() % 100;
        // Chances of each color
        chosenColor = (randomInt >= 0 && randomInt < 20) ? RED :
                      (randomInt >= 20 && randomInt < 40) ? YELLOW :
                      (randomInt >= 40 && randomInt < 60) ? BLUE :
                      WHITE;
        colorRegion(bottomLeftX + 2, bottomLeftY + 2, topRightX - 2, topRightY - 2, chosenColor);
    }
}

void Image::writeHeaders(std::ofstream &of) {
    of.write((const char*)&fileHeader, sizeof(fileHeader));
    of.write((const char*)&dibHeader, sizeof(dibHeader));
    of.write((const char*)&colorHeader, sizeof(colorHeader));
}

void Image::writeData(std::ofstream &of) {
    of.write((const char*)image.data(), image.size());
}