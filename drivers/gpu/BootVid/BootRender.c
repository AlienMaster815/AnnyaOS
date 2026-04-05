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