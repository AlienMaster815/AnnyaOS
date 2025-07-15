#include "../LouDll.h"

#define LOUDLL_API __declspec(dllexport)

void LouDrsdPutPixel32(
    PDRSD_CLIP Clip,
    UINT32 X, UINT32 Y,
    UINT32 Color
){

}

void LouDrsdDrawRectangle32(
    PDRSD_CLIP Clip,
    UINT32 X, UINT32 Y, 
    UINT32 Width, UINT32 Height,
    UINT32 Color
){

}

void LouDrsdFillRectangle32(
    PDRSD_CLIP Clip,
    UINT32 X, UINT32 Y, 
    UINT32 Width, UINT32 Height,
    UINT32 Color
){
    
}

void LouDrsdPutPixel(
    PDRSD_CLIP Clip,
    UINT32 X, UINT32 Y,
    UINT8 R, UINT8 G, UINT8 B, UINT8 A
){

}

void LouDrsdDrawLine(
    PDRSD_CLIP Clip, 
    UINT32 X1, UINT32 Y1,
    UINT32 X2, UINT32 Y2, 
    UINT8 R, UINT8 G, UINT8 B, UINT8 A
){



}

void LouDrsdDrawRectangle(
    PDRSD_CLIP Clip,
    UINT32 X, UINT32 Y, 
    UINT32 Width, UINT32 Height,
    UINT8 R, UINT8 G, UINT8 B, UINT8 A
){

}

void LouDrsdFillRectangle(
    PDRSD_CLIP Clip,
    UINT32 X, UINT32 Y, 
    UINT32 Width, UINT32 Height,
    UINT8 R, UINT8 G, UINT8 B, UINT8 A
){

}