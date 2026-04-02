//Copyright GPL-2 Tyler Grenier (2026)
#include "BootVid.h"

static struct multiboot_tag_framebuffer_common* BootGraphics = 0x00;

LOUAPI
LOUSTATUS
BootVidEntry(){
    LOUSTATUS Status;
    WORD LoadOrder;
    PVOID DefaultFontKey;
    PVOID DefaultFontFile;
    UINT32 ScalerType;

    LouPrint("BOOTVID.SYS:BootVidEntry()\n");

    Status = LouKeGetBootFrameBuffer(&BootGraphics);
    if(Status != STATUS_SUCCESS){
        LouPrint("BOOTVID.SYS:ERROR Unable To Get Boot Frame Buffer\n");
        return STATUS_SUCCESS;
    }

    if(!BootGraphics->framebuffer_addr){
        LouPrint("BOOTVID.SYS:ERROR Vesa/Gop Never Set The Frame Buffer\n");
        return STATUS_SUCCESS;
    }

    LouPrint("BOOTVID.SYS:Using Framebuffer:%h\n", BootGraphics); 
    PBOOTVID_FRAMEBUFFER NewBuffer = LouKeMallocType(BOOTVID_FRAMEBUFFER, KERNEL_GENERIC_MEMORY);
    NewBuffer->Width = BootGraphics->framebuffer_width;
	NewBuffer->Height = BootGraphics->framebuffer_height;
    NewBuffer->Bpp = BootGraphics->framebuffer_bpp;
    NewBuffer->RawData = (UINT8*)LouKePciGetVirtualBarAddress(BootGraphics->framebuffer_addr);//check PCI space for framebuffer in case device is a "NON-VGA, kernel Accelerated device" 
    NewBuffer->FramebufferSize = NewBuffer->Width * NewBuffer->Height * (NewBuffer->Bpp / 8);
    NewBuffer->DrsdDevice = false;

    if((!NewBuffer->RawData) && (BootGraphics->framebuffer_addr)){
        //Fallback for VGA emulation if the device is in VGA Emulation
        EnforceSystemMemoryMap(BootGraphics->framebuffer_addr, ROUND_UP64(NewBuffer->FramebufferSize, KILOBYTE_PAGE));
		LouKeMapContinuousMemoryBlock(BootGraphics->framebuffer_addr, BootGraphics->framebuffer_addr, ROUND_UP64(NewBuffer->FramebufferSize, KILOBYTE_PAGE), KERNEL_DMA_MEMORY);
		LouKeCreateDeviceSection((PVOID)BootGraphics->framebuffer_addr, (PVOID)BootGraphics->framebuffer_addr, ROUND_UP64(NewBuffer->FramebufferSize, KILOBYTE_PAGE), PAGE_READWRITE | SEC_NOCACHE);
		NewBuffer->RawData = (UINT8*)BootGraphics->framebuffer_addr;
    }

    //UINT32* Tmp = (UINT32*)NewBuffer->RawData;

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

    ScalerType = TtfReadUint32(DefaultFontFile);

    LouPrint("BOOTVID.SYS:Default Font File:%h\n", ScalerType);

    switch(ScalerType){
    case 0x00010000:
    case 0x74727565:
        Status = TtfInitializeFile(DefaultFontFile);
        break;
    default:
        LouPrint("BOOTVID.SYS:ERROR:File Type Is Not Supported By BOOTVID.SYS\n");
    }

    LouPrint("BOOTVID.SYS:BootVidEntry():STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS;
}