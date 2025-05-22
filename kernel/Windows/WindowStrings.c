#include <LouAPI.h>

#define YINC 17
#define XINC 8


void PrintWindowTitle(uint16_t StartX, uint16_t StartY, string Text){
    while(*Text != '\0'){

        Text++;
    }
}

CharMapping* GetCharecterMap(char Charecter);


void PutFloatingCharecter(
    char FloatingCharecter, 
    uint16_t x ,uint16_t y, 
    uint16_t AnchorX, uint16_t AnchorY,
    uint16_t ScalingX, uint16_t ScalingY,
    uint8_t r, uint8_t g, uint8_t b
){
    CharMapping* Map = GetCharecterMap(FloatingCharecter);

    for(uint16_t ix = 0 ; ix < ScalingX; ix++){
        for(uint16_t iy = 0 ; iy < ScalingY; iy++){
            for (uint16_t yz = 0; yz < 16; yz++) {
                wchar_t Ybyte = Map->pixels[yz];
                for (uint16_t xz = 0; xz < 16; xz++) {
                    if ((Ybyte >> (15 - xz)) & 0x01) { 
                        LouKeDrsdPutPixelMirrored((x + (xz * ScalingX) +  ix), (y + (yz * ScalingY) + iy), r, g, b);
                    }
                }
            }
        }
    }
}

void PlaceFloatingString(
    string FloatingString,
    uint16_t x, uint16_t y,
    uint16_t ScalingX, uint16_t ScalingY,
    uint8_t r, uint8_t g, uint8_t b, 
    ...
){
    int32_t AnchorX = -8;
    int32_t AnchorY = 0;

    for(size_t i = 0 ; i < strlen(FloatingString); i++){
        if(FloatingString[i] == ' '){
            x += (8 * ScalingX);
            continue;
        }
        if(FloatingString[i] == '\n'){
            y += (17 * ScalingY);
            continue;
        }
        PutFloatingCharecter(
            FloatingString[i], 
            (x - (10 * ScalingX)), y, 
            AnchorX, AnchorY,
            ScalingX, ScalingY,
            r, g, b
        );
        x += (8 * ScalingX);
    }
}