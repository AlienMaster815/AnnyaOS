#include "BootVid.h"

static PBOOTVID_FRAMEBUFFER BootBuffer = 0;
PFB_BOOT_RENDERER BootFbRenderers = 0x00;

LOUSTATUS BootVidRegisterBootFrameBuffer(PBOOTVID_FRAMEBUFFER FrameBuffer, SIZE FbCount){
    if(BootBuffer){
        return STATUS_UNSUCCESSFUL;
    }
    BootBuffer = FrameBuffer;
    BootFbRenderers = LouKeMallocArray(FB_BOOT_RENDERER, FbCount, KERNEL_GENERIC_MEMORY);
    if(!BootFbRenderers){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    for(SIZE i = 0; i < FbCount; i++){
        BootFbRenderers[i].Canvas = LouKeMallocEx(FrameBuffer[i].FramebufferSize, KILOBYTE_PAGE, KERNEL_GENERIC_MEMORY);
        if(!BootFbRenderers[i].Canvas){
            return STATUS_INSUFFICIENT_RESOURCES;
        }
        BootFbRenderers[i].Width = FrameBuffer[i].Width;
        BootFbRenderers[i].Height = FrameBuffer[i].Height;
        BootFbRenderers[i].Pitch = FrameBuffer[i].Pitch;
        BootFbRenderers[i].Fb = &FrameBuffer[i];
    }

    return STATUS_SUCCESS;
}

UINT32 BootRenderGetPixel(
    INT32 x, INT32 y, PFB_BOOT_RENDERER Renderer
){
    if((!BootBuffer) || (x >= Renderer->Width) || (y >= Renderer->Height)){
        return 0xFFFFFFFF;
    }
    return Renderer->Canvas[x + y * (Renderer->Pitch / 4)]; 
}

void BootRenderPutPixelEx(INT32 x, INT32 y, UINT32 Rgb, PFB_BOOT_RENDERER Renderer){
    if((!BootBuffer) || (x >= Renderer->Width) || (y >= Renderer->Height)){
        return;
    }
    Renderer->Canvas[x + y * (Renderer->Pitch / 4)] = Rgb;
}

void BootRenderPutPixel(INT32 x, INT32 y, UINT8 R, UINT8 G, UINT8 B, PFB_BOOT_RENDERER Renderer){
    BootRenderPutPixelEx(x, y, SET_RGB(R, G, B), Renderer);
}

static size_t i = 0;

void BootRenderSyncScreen(PFB_BOOT_RENDERER Renderer){
    memcpy((PVOID)Renderer->Fb->RawData, (PVOID)Renderer->Canvas, Renderer->Fb->FramebufferSize);
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

void BootRenderPutPixelBrightnesEx(int x, int y, UINT32 Color, float Brightness, PFB_BOOT_RENDERER Renderer){
    Color = BootRenderGetColorBrightness(Color, Brightness);
    BootRenderPutPixelEx(x, y, Color, Renderer);
}

void BootRenderPutPixelBrightnes(int x, int y, UINT8 R, UINT8 G, UINT8 B, float Brightness, PFB_BOOT_RENDERER Renderer){
    BootRenderPutPixelBrightnesEx(x, y, SET_RGB(R, G, B), Brightness, Renderer);
}

void BootRenderDrawLineEx(int x1, int y1, int x2, int y2, UINT32 Color, PFB_BOOT_RENDERER Renderer) {
    if (x1 == x2 && y1 == y2) {
        BootRenderPutPixelEx(x1, y1, Color, Renderer);
        return;
    }
    else if(x1 == x2){
        for(int i = MIN(y1, y2); i <= MAX(y1, y2); i++){
            BootRenderPutPixelEx(x1, i, Color, Renderer);
        }
        return;
    }else if(y1 == y2){
        for(int i = MIN(x1, x2); i <= MAX(x1, x2); i++){
            BootRenderPutPixelEx(i, y1, Color, Renderer);
        }
        return;
    }

    int dx = BootRenderAbsolute(x2 - x1);
    int dy = -BootRenderAbsolute(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx + dy;

    while (1) {
        BootRenderPutPixelEx(x1, y1, Color, Renderer);
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
    UINT32  Color,
    PFB_BOOT_RENDERER Renderer
){

    if((X1 == X2) && (Y1 == Y2)){
        BootRenderPutPixelEx(X1, Y1, Color, Renderer);
        return;
    }
    else if(X1 == X2){
        for(int i = MIN(Y1, Y2); i <= MAX(Y1, Y2); i++){
            BootRenderPutPixelEx(X1, i, Color, Renderer);
        }
        return;
    }else if(Y1 == Y2){
        for(int i = MIN(X1, X2); i <= MAX(X1, X2); i++){
            BootRenderPutPixelEx(i, Y1, Color, Renderer);
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
                BootRenderRoundFloatPartOfNumber(IntersectY),
                Renderer
            );
            BootRenderPutPixelBrightnesEx(
                BootRenderIntegerPartOfNumber(IntersectY) + 1,
                x,
                Color,
                BootRenderFloatPartOfNumber(IntersectY),
                Renderer
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
                BootRenderRoundFloatPartOfNumber(IntersectY),
                Renderer
            );
            BootRenderPutPixelBrightnesEx(
                x, 
                BootRenderIntegerPartOfNumber(IntersectY) + 1,
                Color, 
                BootRenderFloatPartOfNumber(IntersectY),
                Renderer
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
    UINT8   B,
    PFB_BOOT_RENDERER Renderer
){
    BootRenderDrawLineEx(X1, Y1, X2, Y2, SET_RGB(R,G,B), Renderer);
}

void BootRenderDrawAaLine(
    int     X1, int Y1,
    int     X2, int Y2,
    UINT8   R,
    UINT8   G,
    UINT8   B,
    PFB_BOOT_RENDERER Renderer
){
    BootRenderDrawAaLineEx(X1, Y1, X2, Y2, SET_RGB(R,G,B), Renderer);
}

void BootRenderSetScreenColorEx(UINT32 Color, PFB_BOOT_RENDERER Renderer){
    for(SIZE i = 0 ; i < (Renderer->Fb->FramebufferSize / sizeof(UINT32)); i++){
        Renderer->Canvas[i] = Color;
    }
}

void BootRenderSetScreenColor(UINT8 R, UINT8 G, UINT8 B, PFB_BOOT_RENDERER Renderer){
    BootRenderSetScreenColorEx(SET_RGB(R, G, B), Renderer);
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