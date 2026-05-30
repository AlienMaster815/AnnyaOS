#include "../BootVid.h"

static SIZE* LineWidths = 0x00;
static SIZE TotalLines = 0;

extern PBOOTVID_FRAMEBUFFER BootBuffer;
extern UINT32* Canvas;
extern INT32 Width;
extern INT32 Height;


void BootVidInitializeArtifactTracking(){
    TotalLines = Height / TERMINAL_INCY;
    if(LineWidths){
        LouKeFree(LineWidths);
    }
    LineWidths = LouKeMallocArray(SIZE, TotalLines, KERNEL_GENERIC_MEMORY);
}

void BootVidModifyTracking(SIZE Y, SIZE LineWidth){
    SIZE Line = (Y / TERMINAL_INCY);
    LineWidths[Line] = LineWidth;
}

void BootVidScrollTracking(){
    for(SIZE i = 0; i < (TotalLines - 1); i++){
        if(LineWidths[i] > LineWidths[i + 1]){
            UINT32* DeviceBase = &((UINT32*)BootBuffer->RawData)[(i * TERMINAL_INCY) * Width];
            UINT32* ShadowBase = &Canvas[(i * TERMINAL_INCY) * Width];
            for(SIZE y = 0 ; y < TERMINAL_INCY; y++){
                for(SIZE x = LineWidths[i + 1]; x < LineWidths[i]; x++){
                    DeviceBase[x + y * Width] = 0;
                }
            } 
        }   
        LineWidths[i] = LineWidths[i + 1];
    }
    LineWidths[TotalLines - 1] = 0x00;
}

void BootVidSyncScreenWithTracking(){
    for(SIZE i = 0 ; i < TotalLines; i++){
        if(!LineWidths[i])continue;
        UINT32* DeviceBase = &((UINT32*)BootBuffer->RawData)[(i * TERMINAL_INCY) * Width];
        UINT32* ShadowBase = &Canvas[(i * TERMINAL_INCY) * Width];
        for(SIZE y = 0 ; y < TERMINAL_INCY; y++){
            for(SIZE x = 0 ; x < LineWidths[i]; x++){
                DeviceBase[x + y * Width] = ShadowBase[x + y * Width];
            }
        }
    }
}