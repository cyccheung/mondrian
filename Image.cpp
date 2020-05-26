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
}

void Image::generateImage(const char *fileName) {
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

void Image::writeHeaders(std::ofstream &of) {
    of.write((const char*)&fileHeader, sizeof(fileHeader));
    of.write((const char*)&dibHeader, sizeof(dibHeader));
    of.write((const char*)&colorHeader, sizeof(colorHeader));
}

void Image::writeData(std::ofstream &of) {
    of.write((const char*)image.data(), image.size());
}