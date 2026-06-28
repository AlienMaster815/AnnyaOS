#include "../BootVid.h"



void BootVidInitializeArtifactTracking(PFB_BOOT_RENDERER Renderer){
    SIZE TotalLines = Renderer->Height / TERMINAL_INCY;
    if(Renderer->LineSystem){
        LouKeFree(Renderer->LineSystem);
    }
    Renderer->LineSystem = LouKeMallocArray(SIZE, TotalLines, KERNEL_GENERIC_MEMORY);
    Renderer->TotalLines = TotalLines;
}

void BootVidModifyTracking(SIZE Y, SIZE LineWidth, PFB_BOOT_RENDERER Renderer){
    SIZE Line = (Y / TERMINAL_INCY);
    Renderer->LineSystem[Line] = LineWidth;
}

void BootVidScrollTracking(PFB_BOOT_RENDERER Renderer){
    for(SIZE i = 0; i < (Renderer->TotalLines - 1); i++){
        if(Renderer->LineSystem[i] > Renderer->LineSystem[i + 1]){
            UINT32* DeviceBase = &((UINT32*)Renderer->Fb->RawData)[(i * TERMINAL_INCY) * (Renderer->Pitch / 4)];
            UINT32* ShadowBase = &Renderer->Canvas[(i * TERMINAL_INCY) * (Renderer->Pitch / 4)];
            for(SIZE y = 0 ; y < TERMINAL_INCY; y++){
                for(SIZE x = Renderer->LineSystem[i + 1]; x < Renderer->LineSystem[i]; x++){
                    DeviceBase[x + y * (Renderer->Pitch / 4)] = 0;
                }
            } 
        }   
        Renderer->LineSystem[i] = Renderer->LineSystem[i + 1];
    }
    Renderer->LineSystem[Renderer->TotalLines - 1] = 0x00;
}

void BootVidSyncScreenWithTracking(PFB_BOOT_RENDERER Renderer){
    for(SIZE i = 0 ; i < Renderer->TotalLines; i++){
        if(!Renderer->LineSystem[i])continue;
        UINT32* DeviceBase = &((UINT32*)Renderer->Fb->RawData)[(i * TERMINAL_INCY) * (Renderer->Pitch / 4)];
        UINT32* ShadowBase = &Renderer->Canvas[(i * TERMINAL_INCY) * (Renderer->Pitch / 4)];
        for(SIZE y = 0 ; y < TERMINAL_INCY; y++){
            for(SIZE x = 0 ; x < Renderer->LineSystem[i]; x++){
                DeviceBase[x + y * (Renderer->Pitch / 4)] = ShadowBase[x + y * (Renderer->Pitch / 4)];
            }
        }
    }
}