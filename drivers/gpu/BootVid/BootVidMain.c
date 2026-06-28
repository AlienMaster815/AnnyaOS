//Copyright GPL-2 Tyler Grenier (2026)
#include "BootVid.h"

SIZE gFbCount = 0;
static PLOADER_FB_MEMORY_MAP BootGraphics = 0x00;
static BOOLEAN BootVidInitialized = false;

KERNEL_EXPORT UINT64 LouKeGetKSpaceBase();

LOUAPI
LOUSTATUS
BootVidEntry(){
    LOUSTATUS Status;
    WORD LoadOrder;
    PVOID DefaultFontKey;
    PVOID DefaultFontFile;
    UINT32 ScalerType;
    LouPrint("BOOTVID.SYS:BootVidEntry()\n");

    Status = LouKeGetBootFrameBuffer(&BootGraphics, &gFbCount);
    if(Status != STATUS_SUCCESS){
        LouPrint("BOOTVID.SYS:ERROR Unable To Get Boot Frame Buffer\n");
        return STATUS_SUCCESS;
    }

    LouPrint("BootGraphics:%h\n", (UINT64)BootGraphics);

    PBOOTVID_FRAMEBUFFER NewBuffer = LouKeMallocArray(BOOTVID_FRAMEBUFFER, gFbCount, USER_GENERIC_MEMORY);
    for(SIZE i = 0 ; i < gFbCount; i++){
        NewBuffer[i].Width = BootGraphics[i].Tracker.Width;
	    NewBuffer[i].Height = BootGraphics[i].Tracker.Height;
        NewBuffer[i].Bpp = BootGraphics[i].Tracker.Bpp;
        NewBuffer[i].Pitch = BootGraphics[i].Tracker.Pitch;
        NewBuffer[i].FramebufferSize = BootGraphics[i].Tracker.Pitch * BootGraphics[i].Tracker.Height;
        NewBuffer[i].DrsdDevice = false;
        SIZE Offset = BootGraphics[i].Tracker.Base & (KILOBYTE_PAGE - 1);


        NewBuffer->UserBuffer = LouVMallocEx(ROUND_UP64(NewBuffer[i].FramebufferSize + Offset, KILOBYTE_PAGE), KILOBYTE_PAGE);
        LouKeMapContinuousMemoryBlock(BootGraphics[i].Tracker.Base - Offset, (UINT64)NewBuffer[i].UserBuffer, ROUND_UP64(NewBuffer[i].FramebufferSize + Offset, KILOBYTE_PAGE), USER_WRITE_COMBINE_MEMORY);
        NewBuffer[i].UserBuffer = (UINT32*)((UINTPTR)NewBuffer[i].UserBuffer + Offset);
        NewBuffer[i].RawData = (UINT8*)NewBuffer[i].UserBuffer;
        
    }

    Status = BootVidRegisterBootFrameBuffer(NewBuffer, gFbCount);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    DefaultFontKey = LouKeOpenRegistryHandle(L"KERNEL_DEFAULT_CONFIG\\BootDev\\DefaultFont\\LoadOrder", 0x00);    
    if(!DefaultFontKey){
        LouPrint("BOOTVID.SYS:ERROR:Unable To Open Default Font Key\n");
        while(1);
    }
    Status = LouKeReadRegistryWordValue(DefaultFontKey, &LoadOrder);
    if(Status != STATUS_SUCCESS){
        LouPrint("BOOTVID.SYS:ERROR:Unable To Open Default Font LoadOrder\n");
        while(1);
    }
    
    DefaultFontFile = LouKeGetBootDevice(LoadOrder);

    if(!DefaultFontFile){
        LouPrint("BOOTVID.SYS:ERROR:Default Font File Location Is NULL\n");
        while(1);
    }

    ScalerType = TtfReadUint32(*(UINT32*)DefaultFontFile);

    LouPrint("BOOTVID.SYS:Default Font File:%h\n", ScalerType);

    switch(ScalerType){
    case 0x00010000:
    case 0x74727565:
        Status = TtfInitializeFile(DefaultFontFile);
        break;
    default:
        LouPrint("BOOTVID.SYS:ERROR:File Type Is Not Supported By BOOTVID.SYS\n");
    }

    BootVidInitializeTerminalDriver();

    BootVidInitialized = true;

    LouPrint("BOOTVID.SYS:BootVidEntry():STATUS_SUCCESS\n");
    while(1);

    return STATUS_SUCCESS;
}

DRIVER_EXPORT 
void 
LouKeExitDosMode(){
    if(!BootVidInitialized){
        return;
    }
    BootVidDeInitializeTerminalDriver();
}
