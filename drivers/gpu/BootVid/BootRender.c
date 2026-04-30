#include "BootVid.h"

PBOOTVID_FRAMEBUFFER BootBuffer = 0;

UINT32* Canvas = 0;
INT32 Width = 0;
INT32 Height = 0;

LOUSTATUS BootVidRegisterBootFrameBuffer(PBOOTVID_FRAMEBUFFER FrameBuffer){
    if(BootBuffer){
        return STATUS_UNSUCCESSFUL;
    }
    BootBuffer = FrameBuffer;
    Canvas = (UINT32*)LouKeMallocEx(BootBuffer->FramebufferSize, 512, KERNEL_GENERIC_MEMORY);
    Width = BootBuffer->Width;
    Height = BootBuffer->Height;
    return STATUS_SUCCESS;
}

UINT32 BootRenderGetPixel(
    INT32 x, INT32 y
){
    if((!BootBuffer) || (x >= Width) || (y >= Height)){
        return 0xFFFFFFFF;
    }
    return Canvas[x + y * Width]; 
}

void BootRenderPutPixelEx(INT32 x, INT32 y, UINT32 Rgb){
    if((!BootBuffer) || (x >= Width) || (y >= Height)){
        return;
    }
    Canvas[x + y * Width] = Rgb;
}

void BootRenderPutPixel(INT32 x, INT32 y, UINT8 R, UINT8 G, UINT8 B){
    BootRenderPutPixelEx(x, y, SET_RGB(R, G, B));
}

void BootRenderSyncScreen(){
    memcpy((PVOID)BootBuffer->RawData, (PVOID)Canvas, BootBuffer->FramebufferSize);
}

void BootRenderSwap(int* A, int* B){
    int Temp = *A;
    *A = *B;
    *B = Temp; 
}

float BootRenderAbsolute(float x){
    return (x < 0) ? -x : x;
}

int BootRenderIntegerPartOfNumber(float x){
    return (int)x;
}

int BootRenderRoundNumber(float x){
    return BootRenderIntegerPartOfNumber(x + 0.5);
}

float BootRenderFloatPartOfNumber(float x){
    float fraction = x - (float)((int)x);
    if (fraction < 0) fraction += 1.0f; 
    return fraction;
}


float BootRenderRoundFloatPartOfNumber(float x){
    return 1.0f - BootRenderFloatPartOfNumber(x);
}

UINT32 BootRenderGetColorBrightness(UINT32 Color, float Brightness) {
    UINT8 R = GET_RED(Color);
    UINT8 G = GET_GREEN(Color);
    UINT8 B = GET_BLUE(Color);

    float NewR = (float)R * Brightness;
    float NewG = (float)G * Brightness;
    float NewB = (float)B * Brightness;

    float MaxVal = MAX(NewR, MAX(NewG, NewB));
    if (MaxVal > 255.0f) {
        float Scale = 255.0f / MaxVal;
        NewR *= Scale;
        NewG *= Scale;
        NewB *= Scale;
    }
    return SET_RGB((UINT8)NewR, (UINT8)NewG, (UINT8)NewB);
}

void BootRenderPutPixelBrightnesEx(int x, int y, UINT32 Color, float Brightness){
    Color = BootRenderGetColorBrightness(Color, Brightness);
    BootRenderPutPixelEx(x, y, Color);
}

void BootRenderPutPixelBrightnes(int x, int y, UINT8 R, UINT8 G, UINT8 B, float Brightness){
    BootRenderPutPixelBrightnesEx(x, y, SET_RGB(R, G, B), Brightness);
}

void BootRenderDrawLineEx(int x1, int y1, int x2, int y2, UINT32 Color) {
    if (x1 == x2 && y1 == y2) {
        BootRenderPutPixelEx(x1, y1, Color);
        return;
    }
    else if(x1 == x2){
        for(int i = MIN(y1, y2); i <= MAX(y1, y2); i++){
            BootRenderPutPixelEx(x1, i, Color);
        }
        return;
    }else if(y1 == y2){
        for(int i = MIN(x1, x2); i <= MAX(x1, x2); i++){
            BootRenderPutPixelEx(i, y1, Color);
        }
        return;
    }

    int dx = BootRenderAbsolute(x2 - x1);
    int dy = -BootRenderAbsolute(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx + dy;

    while (1) {
        BootRenderPutPixelEx(x1, y1, Color);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 >= dy) { 
            err += dy; 
            x1 += sx; 
        }
        if (e2 <= dx) { 
            err += dx; 
            y1 += sy; 
        }
    }
}

void BootRenderDrawAaLineEx(
    int     X1, int Y1,
    int     X2, int Y2,
    UINT32  Color
){

    if((X1 == X2) && (Y1 == Y2)){
        BootRenderPutPixelEx(X1, Y1, Color);
        return;
    }
    else if(X1 == X2){
        for(int i = MIN(Y1, Y2); i <= MAX(Y1, Y2); i++){
            BootRenderPutPixelEx(X1, i, Color);
        }
        return;
    }else if(Y1 == Y2){
        for(int i = MIN(X1, X2); i <= MAX(X1, X2); i++){
            BootRenderPutPixelEx(i, Y1, Color);
        }
        return;
    }


    int Steep = BootRenderAbsolute(Y2 - Y1) > BootRenderAbsolute(X2 - X1);

    if(Steep){
        BootRenderSwap(&X1, &Y1);
        BootRenderSwap(&X2, &Y2);
    }
    if(X1 > X2){
        BootRenderSwap(&X1, &X2);
        BootRenderSwap(&Y1, &Y2);
    }

    float Dx = X2 - X1;
    float Dy = Y2 - Y1;
    float Gradient = (Dx == 0) ? 1.0f : Dy / Dx; 

    int     XPxl1 = X1;
    int     XPxl2 = X2;
    float   IntersectY = Y1;

    if(Steep){
        int x;
        for(x = XPxl1; x <= XPxl2; x++){
            BootRenderPutPixelBrightnesEx(
                BootRenderIntegerPartOfNumber(IntersectY),
                x,
                Color,
                BootRenderRoundFloatPartOfNumber(IntersectY)
            );
            BootRenderPutPixelBrightnesEx(
                BootRenderIntegerPartOfNumber(IntersectY) + 1,
                x,
                Color,
                BootRenderFloatPartOfNumber(IntersectY)
            );
            IntersectY += Gradient;
        }
    }else{
        int x;
        for(x = XPxl1; x <= XPxl2; x++){
            BootRenderPutPixelBrightnesEx(
                x, 
                BootRenderIntegerPartOfNumber(IntersectY), 
                Color, 
                BootRenderRoundFloatPartOfNumber(IntersectY)
            );
            BootRenderPutPixelBrightnesEx(
                x, 
                BootRenderIntegerPartOfNumber(IntersectY) + 1,
                Color, 
                BootRenderFloatPartOfNumber(IntersectY)
            );
            IntersectY += Gradient;
        }
    }
}

void BootRenderDrawLine(
    int     X1, int Y1,
    int     X2, int Y2,
    UINT8   R,
    UINT8   G,
    UINT8   B
){
    BootRenderDrawLineEx(X1, Y1, X2, Y2, SET_RGB(R,G,B));
}

void BootRenderDrawAaLine(
    int     X1, int Y1,
    int     X2, int Y2,
    UINT8   R,
    UINT8   G,
    UINT8   B
){
    BootRenderDrawAaLineEx(X1, Y1, X2, Y2, SET_RGB(R,G,B));
}

void BootRenderSetScreenColorEx(UINT32 Color){
    for(SIZE i = 0 ; i < (BootBuffer->FramebufferSize / sizeof(UINT32)); i++){
        Canvas[i] = Color;
    }
}

void BootRenderSetScreenColor(UINT8 R, UINT8 G, UINT8 B){
    BootRenderSetScreenColorEx(SET_RGB(R, G, B));
}

DRIVER_EXPORT
LOUSTATUS
GetBootVidFrameBuffer(
    UINT64* KulaPacket
){
    if(!KulaPacket){
        return STATUS_INVALID_PARAMETER;
    }
    *KulaPacket = (UINT64)BootBuffer;
    return STATUS_SUCCESS;
}