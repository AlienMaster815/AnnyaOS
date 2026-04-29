#include "Drsd.h"

static BOOLEAN UsingBootFramebuffer = false;
static PBOOTVID_FRAMEBUFFER BootFrameBuffer = 0x00;

DRSD_API
LOUSTATUS  
DrsdGetCurrentScreenArea(
    int* x,
    int* y,
    int* Width,
    int* Height
){
    if(!x || !y || !Width || !Height){
        return STATUS_INVALID_PARAMETER;
    }

    if(UsingBootFramebuffer){
        *x = 0;
        *y = 0;
        *Width = BootFrameBuffer->Width;
        *Width = BootFrameBuffer->Height;
        return STATUS_SUCCESS;
    }

    *x = 0;
    *y = 0;
    *Width = 0;
    *Width = 0;

    return STATUS_UNSUCCESSFUL;
}


DRSD_API
BOOL DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved){

    LOUSTATUS Status = LouGetBootFrameBuffer(&BootFrameBuffer);
    if(Status == STATUS_SUCCESS){
        LouPrint("Using Boot Framebuffer\n");
        UsingBootFramebuffer = true;
    }else {
        LouPrint("Unable To Get BootFrameBuffer\n");
    }


    return true;
}
