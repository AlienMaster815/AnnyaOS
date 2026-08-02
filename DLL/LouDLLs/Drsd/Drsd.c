#include "Drsd.h"

static BOOLEAN UsingBootFramebuffer = false;
static PBOOTVID_FRAMEBUFFER BootFrameBuffer = 0x00;
static int gWidth = 0;
static int gHeight = 0;
static int gX = 0;
static int gY = 0;
static UINT32* UserBuffer = 0x00;
static STRING ProcessName = {0};
static BOOLEAN WindowManager = false;
//static BOOLEAN Overide32Bpp = false;

static PUSER_PROCESS_HEAP DrsdRuntimeHeap = 0x00;
static ListHeader ContextTree = {0};

typedef void (*FOR_EACH_CONTEX_IN_AREA_CALLBACK)(PDRSD_FB_CONTEXT Context, PVOID Data);

static PListHeader InternalDrsdGetFbContext(
    PListHeader          TreeEntry,
    int  XLocation, int  YLocation, 
    int* XOut,      int* YOut,
    int* WidthOut,  int* HeightOut
){
    PDRSD_FB_CONTEXT TmpContext;
    PListHeader Result = 0x00;
    PListHeader TmpResult;

    ForEachListEntryBackwards(TmpContext, TreeEntry, Peers){
        if(
            ((TmpContext->XLocation <= XLocation) && ((TmpContext->XLocation + TmpContext->Width) > XLocation)) &&
            ((TmpContext->YLocation <= YLocation) && ((TmpContext->YLocation + TmpContext->Height) > YLocation))
        ){
            Result = &TmpContext->Peers;
            if(XOut)*XOut = TmpContext->XLocation;
            if(YOut)*YOut = TmpContext->YLocation;
            if(WidthOut)*WidthOut = TmpContext->Width;
            if(HeightOut)*HeightOut = TmpContext->Height;
            TmpResult = InternalDrsdGetFbContext(
                &TmpContext->Subordinates,
                XLocation,  YLocation,
                XOut,       YOut,
                WidthOut,   HeightOut
            );
            Result = TmpResult ? TmpResult : Result;
            goto _DONE;
        }
    }
_DONE:
    return Result;
}

static 
void
InternalDrsdForEachContextInArea(
    PListHeader                         TreeEntry,
    int                                 XLocation,  
    int                                 YLocation, 
    int                                 Width,      
    int                                 Height, 
    FOR_EACH_CONTEX_IN_AREA_CALLBACK    Callback, 
    PVOID                               Data
){
    PDRSD_FB_CONTEXT TmpContext;

    ForEachListEntry(TmpContext, TreeEntry, Peers){
        if(!(
            (((TmpContext->XLocation + TmpContext->Width) < XLocation) || (TmpContext->XLocation > (XLocation + Width))) ||
            (((TmpContext->YLocation + TmpContext->Height) < YLocation) || (TmpContext->YLocation > (YLocation + Height)))
        )){
            Callback(TmpContext, Data);
        }
        InternalDrsdForEachContextInArea(
            &TmpContext->Subordinates,
            XLocation,
            YLocation,
            Width,
            Height,
            Callback,
            Data
        );
    }
}

DRSD_API
LOUSTATUS  
InternalDrsdGetCurrentScreenArea(
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
InternalDrsdDeployContext(
    HANDLE tContext
){
    PDRSD_FB_CONTEXT Context = (PDRSD_FB_CONTEXT)tContext;
    int ContextX = Context->XLocation;
    int ContextY = Context->YLocation;
    int ContextWidth = Context->Width;
    int ContextHeight = Context->Height;
    UINT32* Data = Context->Data;    
    for(int Y = 0; Y < ContextHeight; Y++){
        for(int X = 0; X < ContextWidth; X++){
            UserBuffer[(X + ContextX) + ((Y + ContextY) * gWidth)] = Data[X + (Y * ContextWidth)];
        }
    }
}

DRSD_API
void 
InternalDrsdFillColorEx(
    HANDLE  tContext,
    int     x,
    int     y,
    int     Width,
    int     Height,
    UINT32  Color
){
    PDRSD_FB_CONTEXT Context = (PDRSD_FB_CONTEXT)tContext;
    int ContextX = Context->XLocation;
    int ContextY = Context->YLocation;
    int ContextWidth = Context->Width;
    int ContextHeight = Context->Height;
    UINT32* Data = Context->Data;
    if((!x) && (!y) && (!Width) && (!Height)){
        for(int Y = 0 ; Y < ContextHeight; Y++){
            for(int X = 0; X < ContextWidth; X++){
                Data[X + (Y * ContextWidth)] = Color;
            }
        }
        return;
    }
    for(int Y = 0; Y < Height; Y++){
        for(int X = 0; X < Width; X++){
            Data[((x - ContextX) + X) + (((y - ContextY) + Y) * ContextWidth)] = Color;
        }
    }
}

DRSD_API
void
InternalDrsdPutPixelEx(int X , int Y, UINT32 Color){
    if(
        (X < gX || X >= (gX + gWidth)) ||
        (Y < gY || Y >= (gY + gHeight)) 
    ){
        return;
    }
    X = X - gX;
    Y = Y - gY;
    UserBuffer[X + (Y * gWidth)] = Color;    
}

//DRSD_API 
//void InternalDrsdDrawLineEx(
//    int X1, int Y1, 
//    int X2, int Y2, 
//    UINT32 Color
//){



//}

DRSD_API
HANDLE
InternalDrsdCreateFbContext(
    int                         XLocation,
    int                         YLocation,
    int                         Width,
    int                         Height
){
    SIZE DataSize = Width * Height;
    PDRSD_FB_CONTEXT NewContext = LouRtlAllocateHeapEx(
        DrsdRuntimeHeap, 
        GetStructureSize(DRSD_FB_CONTEXT, Data, (DataSize / sizeof(UINT32))),
        GET_ALIGNMENT(DRSD_FB_CONTEXT),
        0x00
    );
    NewContext->XLocation = XLocation;
    NewContext->YLocation = YLocation;
    NewContext->Width = Width;
    NewContext->Height = Height;
    LouMemSet(NewContext->Data, 0, DataSize);

    PListHeader ContextList = InternalDrsdGetFbContext(
        &ContextTree,
        XLocation,  YLocation,
        0x00,       0x00,
        0x00,       0x00
    );
    if(ContextList){
        LouKeListAddTail(&NewContext->Peers, ContextList);
    }else{
        LouKeListAddTail(&NewContext->Peers, &ContextTree);
    }
    return (HANDLE)NewContext;
}

DRSD_API
void 
InternalDrsdRedrawArea(
    int x,      int y,
    int Width,  int Height
){



}

DRSD_API
BOOL DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved){

    LOUSTATUS Status = LouGetCurrentProccessName(
        &ProcessName
    );

    if((Status == STATUS_SUCCESS) && (ProcessName.Buffer)){
        if(!strcmp(ProcessName.Buffer, AWM_PROCESS_NAME)){
            WindowManager = true;
            LouGetGlobalObject(L"DrsdRuntimeHeap", (PVOID)(UINT8*)&DrsdRuntimeHeap);
            Status = LouGetBootFrameBuffer(&BootFrameBuffer);
            if((Status == STATUS_SUCCESS) && (BootFrameBuffer)){
                LouPrint("DRSD.DLL:Using Boot Framebuffer\n");
                UsingBootFramebuffer = true;
            }else {
                LouPrint("DRSD.DLL:Unable To Get BootFrameBuffer\n");
            }
        }
    }

    LouPrint("DRSD.DLL:Attatched To New Process\n");

    return true;
}
