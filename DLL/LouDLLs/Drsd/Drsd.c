#include "Drsd.h"

static BOOLEAN UsingBootFramebuffer = false;
static PBOOTVID_FRAMEBUFFER BootFrameBuffer = 0x00;
static int gWidth = 0;
static int gHeight = 0;
static int gX = 0;
static int gY = 0;
static UINT32* Canvas = 0x00;
static UINT32* UserBuffer = 0x00;
static STRING ProcessName = {0};
static BOOLEAN WindowManager = false;
static PUSER_PROCESS_HEAP CanvasHeap = 0x00;

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
        *Height = BootFrameBuffer->Height;
        gX = 0;
        gY = 0;
        gHeight = BootFrameBuffer->Height;
        gWidth  = BootFrameBuffer->Width;
        //Canvas
        UserBuffer = BootFrameBuffer->UserBuffer ? BootFrameBuffer->UserBuffer : (UINT32*)BootFrameBuffer->RawData;
        return STATUS_SUCCESS;
    }
    *x = 0;
    *y = 0;
    *Width = 0;
    *Width = 0;
    gX = 0;
    gY = 0;
    gHeight = 0;
    gWidth  = 0;
    return STATUS_UNSUCCESSFUL;
}

DRSD_API
void 
DrsdSyncScreens(){
    if(UsingBootFramebuffer){
        LouMemCpy(UserBuffer, Canvas, BootFrameBuffer->FramebufferSize);
        return;
    }
}

DRSD_API
void
DrsdPutPixelEx(int X , int Y, UINT32 Color){
    if(
        (X < gX || X >= (gX + gWidth)) ||
        (Y < gY || Y >= (gY + gHeight)) 
    ){
        return;
    }
    X = X - gX;
    Y = Y - gY;
    Canvas[X + (Y * gWidth)] = Color;    
}

DRSD_API
BOOL DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved){

    LOUSTATUS Status = LouGetCurrentProccessName(
        &ProcessName
    );

    if((Status == STATUS_SUCCESS) && (ProcessName.Buffer)){
        if(!strcmp(ProcessName.Buffer, AWM_PROCESS_NAME)){
            WindowManager = true;
            Status = LouGetBootFrameBuffer(&BootFrameBuffer);
            if((Status == STATUS_SUCCESS) && (BootFrameBuffer)){
                LouPrint("DRSD.DLL:Using Boot Framebuffer\n");
                UsingBootFramebuffer = true;
                CanvasHeap = LouRtlCreateHeap(
                                USER_HEAP_FLAG_ZERO_MEMORY, 
                                0x00, 
                                BootFrameBuffer->FramebufferSize, 
                                BootFrameBuffer->FramebufferSize,
                                0x00, 0x00
                            );
                Canvas = (UINT32*)LouRtlAllocateHeapEx(CanvasHeap, BootFrameBuffer->FramebufferSize, MEGABYTE_PAGE, 0x00);
                if(!Canvas){
                    LouPrint("DRSD.DLL:Error Allocating Offscreen Canvas\n");
                }
            }else {
                LouPrint("DRSD.DLL:Unable To Get BootFrameBuffer\n");
            }
        }
    }

    LouPrint("DRSD.DLL Attatched To New Process\n");

    return true;
}
