#define _KERNEL_MODULE_
#include <LouDDK.h>
#include "VirtualboxDriver.h"
 #include <drivers/VBoxError.h>


/*
 * This is a clean-room reimplementation of the VirtualBox VBE/VMSVGA driver,
 * originally developed by Oracle Corporation and released under the MIT license.
 *
 * This implementation is based on independent research and observation of the
 * Linux kernel's `vboxvideo` driver and related specifications. No code was
 * directly copied or translated.
 *
 * All identifiers, register names, and behavior are derived from public
 * documentation or reverse-engineered from hardware behavior.
 *
 * Copyright (C) 2025 Tyler Grenier
 * Licensed under the GNU GPLv2
 */
 
void      
HgsmiProccessDisplayInformation(
    POOL Context, 
    uint32_t Display, 
    int32_t StartX, 
    int32_t StartY, 
    uint32_t StartOffset, 
    uint32_t Pitch, 
    uint32_t Width, 
    uint32_t Height, 
    uint16_t Bpp, 
    uint16_t Flags
){
    PVBVA_INFORMATION_SCREEN Screen = (PVBVA_INFORMATION_SCREEN)HgsmiBufferAllocate(
                                        Context, sizeof(VBVA_INFORMATION_SCREEN), 
                                        HGSMI_CH_VBVA, VBVA_INFORMATION_SCREEN_COMMAND
                                    );

    if(!Screen){
        return;
    }

    Screen->ViewIndex = Display;
    Screen->StartX = StartX;
    Screen->StartY = StartY;
    Screen->StartOffset = StartOffset;
    Screen->LineSize = Pitch;
    Screen->Width = Width;
    Screen->Height = Height;
    Screen->Bpp = Bpp;
    Screen->Flags = Flags;
    
    HgsmiBufferSubmit(Context, Screen);
    HgsmiBufferFree(Context, Screen);

}

LOUSTATUS 
HgsmiUpdateInputMappings(
    POOL Context, 
    int32_t OriginX, 
    int32_t OriginY, 
    uint32_t Width, 
    uint32_t Height
){



    return STATUS_SUCCESS;
}

LOUSTATUS HgsmiGetModeHints(
    POOL Context, 
    uint32_t Screens, 
    PVBVA_MODE_HINT Hints
){
    
    PVBVA_QUERY_MODE_HINTS  Query;
    size_t                  Size;

    if(!Hints){
        LouPrint("ERROR:VBOX_VIDEO:HgsmiGetModeHints() Hints Is NULL\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    
    Size = Screens * sizeof(VBVA_MODE_HINT);
    Query = (PVBVA_QUERY_MODE_HINTS)HgsmiBufferAllocate(
        Context, 
        sizeof(VBVA_QUERY_MODE_HINTS) + Size, 
        HGSMI_CH_VBVA, 
        VBVA_QUERY_MODE_HINTS_COMMAND
    );

    if(!Query){
        LouPrint("ERROR:VBOX_VIDEO:HgsmiGetModeHints() Query Is Null\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Query->HintsQueriedCount = Screens;
    Query->HintStructureQuestSize = sizeof(VBVA_MODE_HINT);
    Query->Rc = VERR_NOT_SUPPORTED;

    HgsmiBufferSubmit(Context, Query);

    if(Query->Rc < 0){
        LouPrint("ERROR:VBOX_VIDEO:HgsmiGetModeHints() Query Failed\n");
        return STATUS_IO_DEVICE_ERROR;
    }

    memcpy(Hints, (uint8_t*)(uint64_t)((uint8_t*)Query) + sizeof(VBVA_QUERY_MODE_HINTS), Size);
    
    HgsmiBufferFree(Context, Query);

    return STATUS_SUCCESS;
}
