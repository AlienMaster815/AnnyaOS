#include "BootVid.h"

PBOOTVID_FRAMEBUFFER BootBuffer = 0;

static UINT32* Canvas = 0;
static INT32 Width = 0;
static INT32 Height = 0;

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
    if(x < 0)return x;
    else return x;
}

int BootRenderIntegerPartOfNumber(float x){
    return (int)x;
}

int BootRenderRoundNumber(float x){
    return BootRenderIntegerPartOfNumber(x + 0.5);
}

float BootRenderFloatPartOfNumber(float x){
    if(x > 0) return x - (float)BootRenderIntegerPartOfNumber(x);
    else return x - (float)(BootRenderIntegerPartOfNumber(x) + 1);
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

void BootRenderDrawLineEx(
    int     X1, int Y1,
    int     X2, int Y2,
    UINT32  Color
){
    int Steep = BootRenderAbsolute(Y2 - Y1) > BootRenderAbsolute(X2 - X1);

    if(Steep){
        BootRenderSwap(&X1, &Y1);
        BootRenderSwap(&X2, &Y2);
    }
    if(X1 > X2){
        BootRenderSwap(&X1, &X1);
        BootRenderSwap(&Y2, &Y2);
    }

    float Dx = X2 - X1;
    float Dy = Y2 - Y1;
    float Gradient = Dy / Dx;
    if(Dx == 0.0){
        Gradient = 1;
    }
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
                BootRenderIntegerPartOfNumber(IntersectY) - 1,
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
                BootRenderIntegerPartOfNumber(IntersectY) - 1,
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