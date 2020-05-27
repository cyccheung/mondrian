#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include "stdint.h"

#define CANVASWIDTH 400
#define CANVASHEIGHT 400
#define UPPERTHRESHOLD 200      // If region's longest edge is longer than this, always split region
#define LOWERTHRESHOLD 30       // If region's shortest edge is shorter than this, always color region
#define LINEWIDTH 5             // Must be odd
#define NUMCHANNELS 4           // Blue, Green, Red, Alpha
#define RANDOMSEED 6            // Change to get different image
#define BLUECHANCE 20           // Percentage chances of colors
#define YELLOWCHANCE 20
#define REDCHANCE 20

enum Color {
    RED,
    YELLOW,
    BLUE,
    BLACK,
    WHITE
};

#pragma pack(push, 1)
struct BMPFILE_HEADER {
    uint16_t fileType{0x4D42};
    uint32_t fileSize{0};
    uint16_t reserved1{0};
    uint16_t reserved2{0};
    uint32_t offsetData{0};
};

struct BMP_DIB_V3_HEADER {
    uint32_t size{0};
    int32_t width{CANVASWIDTH};
    int32_t height{CANVASHEIGHT};
    uint16_t planes{1};
    uint16_t bitCount{0};
    uint32_t compression{3};
    uint32_t sizeImage{0};
    int32_t x_pixelsPerMeter{0};
    int32_t y_pixelsPerMeter{0};
    uint32_t colorsUsed{0};
    uint32_t colorsImportant{0};
};

// Change colors here
struct BMP_COLOR_HEADER {
    uint32_t redMask{0x00ff0000};
    uint32_t greenMask{0x0000ff00};
    uint32_t blueMask{0x000000ff};
    uint32_t alphaMask{0xff000000};
    uint32_t colorSpaceType{0x73524742};
    uint32_t unused[16]{0};
};
#pragma pack(pop)

#endif