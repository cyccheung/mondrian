#include "Image.hpp"

// Create white canvas
Image::Image() {
    for(int i = 0; i < CANVASHEIGHT; i++) {
        for(int j = 0; j < CANVASWIDTH; j++) {
            image[i][j].setPixel(j, i, white);
        }
    }
    
}

Image::~Image() {
}