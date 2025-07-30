#include "../LouDll.h"

#define LOUDLL_API __declspec(dllexport)
LOUDLL_API
int LouPrint(char* Str, ...);

int abs(int x) {
    return (x < 0) ? -x : x;
}

LOUDLL_API
void LouDrsdPutPixel32(
    PDRSD_CLIP Clip,
    UINT32 X, UINT32 Y,
    UINT32 Color
){
    Clip->WindowBuffer[X + (Y * Clip->Width)] = Color;
}

LOUDLL_API
void LouDrsdDrawRectangle32(
    PDRSD_CLIP Clip,
    UINT32 X, UINT32 Y, 
    UINT32 Width, UINT32 Height,
    UINT32 Color
){

}

LOUDLL_API
void LouDrsdFillRectangle32(
    PDRSD_CLIP Clip,
    UINT32 X, UINT32 Y, 
    UINT32 Width, UINT32 Height,
    UINT32 Color
){
    
}


LOUDLL_API
void LouDrsdPutPixel(
    PDRSD_CLIP Clip,
    UINT32 X, UINT32 Y,
    UINT8 R, UINT8 G, UINT8 B, UINT8 A
){

}

LOUDLL_API
void LouDrsdDrawLine(
    PDRSD_CLIP Clip, 
    UINT32 X1, UINT32 Y1,
    UINT32 X2, UINT32 Y2, 
    UINT8 R, UINT8 G, UINT8 B, UINT8 A
){



}

LOUDLL_API
void LouDrsdDrawLine32(
    PDRSD_CLIP Clip, 
    UINT32 x0, UINT32 y0,
    UINT32 x1, UINT32 y1, 
    UINT32 Color
){
  int dx =  abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1; 
  int err = dx + dy, e2; /* error value e_xy */
 
  for (;;){  /* loop */
    LouDrsdPutPixel32(Clip, x0,y0,Color);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
}

LOUDLL_API
void LouDrsdDrawRectangle(
    PDRSD_CLIP Clip,
    UINT32 X, UINT32 Y, 
    UINT32 Width, UINT32 Height,
    UINT8 R, UINT8 G, UINT8 B, UINT8 A
){

}

LOUDLL_API
void LouDrsdFillRectangle(
    PDRSD_CLIP Clip,
    UINT32 X, UINT32 Y, 
    UINT32 Width, UINT32 Height,
    UINT8 R, UINT8 G, UINT8 B, UINT8 A
){

}

LOUDLL_API
void 
LouDrsdClipToClip(
    PDRSD_CLIP BackClip,
    PDRSD_CLIP FrontClip,
    UINT32 X,
    UINT32 Y
){
    if((BackClip->Width < (X + FrontClip->Width)) || (BackClip->Height < (Y + FrontClip->Height))){
        LouPrint("LouDrsdClipToClip() Bad Data\n");
        return;
    }
    for(size_t y = 0; y < FrontClip->Height; y++){
        for(size_t x = 0; x < FrontClip->Width; x++){
            BackClip->WindowBuffer[(X + x) + ((Y + y) * BackClip->Width)] = FrontClip->WindowBuffer[x + (y * FrontClip->Width)];
        }
    }
}