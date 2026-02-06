/* SPDX-License-Identifier: MIT */
/* Copyright (C) 2006-2017 Oracle Corporation */
/* Port Copyright (C) 2025-2026 Tyler Grenier */

 #define _KERNEL_MODULE_
 #include <LouDDK.h>
 #include "VirtualboxDriver.h"
 #include <drivers/VBoxError.h>


UNUSED static uint32_t VbvaBufferAvailable(PVBVA_BUFFER Vbva){


    return 0;
}

UNUSED static void VbvaBufferPlaceDataAt(PVBVA_BUFFER_CONTEXT VbvaContext, void* Pointer, uint32_t Length, uint32_t Offset){

}

UNUSED static void VbvaBufferFlush(POOL Context){

}

static bool VbvaInformHost(PVBVA_BUFFER_CONTEXT VbvaContext, POOL Context, int32_t Screen, bool Enable){

    bool Result = false;
    PVBVA_ENABLE_EX EnablePacket = (PVBVA_ENABLE_EX)HgsmiBufferAllocate(Context, sizeof(VBVA_ENABLE_EX), HGSMI_CH_VBVA, VBVA_ENABLE_COMMAND);
    if(!EnablePacket){
        return false;
    }
    
    EnablePacket->Base.Flags = Enable ? VBVA_F_ENABLE : VBVA_F_DISABLE;
    EnablePacket->Base.Offset = VbvaContext->BufferOffset;
    EnablePacket->Base.Result = VERR_NOT_SUPPORTED;

    if(Screen > MAXIMUM_VIRTUALBOX_MONITORS){
        return false;
    }

    EnablePacket->Base.Flags |= VBVA_F_EXTENDED | VBVA_F_ABSOFFSET;
    EnablePacket->ScreenID = Screen;

    HgsmiBufferSubmit(Context, EnablePacket);

    if(Enable){
        Result = EnablePacket->Base.Result >= 0;
    }else{
        Result = true;
    }

    HgsmiBufferFree(Context, EnablePacket);
    
    return Result;
}

void VbvaDisable(PVBVA_BUFFER_CONTEXT VbvaContext, POOL Context, int32_t Screen){
    VbvaContext->BufferOverflow = false;
    VbvaContext->Record = 0x00;
    VbvaContext->VbvaBuffer = 0x00;
    VbvaInformHost(VbvaContext, Context, Screen, false);
}


bool VbvaEnable(PVBVA_BUFFER_CONTEXT VbvaContext, POOL Context, PVBVA_BUFFER  VbvaBuffer, int32_t Screen){
    bool Result = false;

    memset(VbvaBuffer, 0, sizeof(VBVA_BUFFER));

    VbvaBuffer->PartialWriteTresh = 256;
    VbvaBuffer->DataLength = VbvaContext->BufferLength - sizeof(VBVA_BUFFER);
    VbvaContext->VbvaBuffer = VbvaBuffer;

    Result = VbvaInformHost(VbvaContext, Context, Screen, true);
    if(!Result){
        VbvaDisable(VbvaContext, Context, Screen);
    }

    return Result;
}

bool VbvaBufferBeginUpdate(PVBVA_BUFFER_CONTEXT VbvaContext, POOL Context){

    return false;
}

void VbvaBufferEndUpdate(PVBVA_BUFFER_CONTEXT VbvaContext){

}

bool VbvaWrite(PVBVA_BUFFER_CONTEXT BufferContext, POOL Context, void* Pixels, uint32_t Length){

    return false;
}

void VbvaSetupBufferContext(
    PVBVA_BUFFER_CONTEXT VbvaContext, 
    uint32_t BufferOffset, 
    uint32_t BufferLength
){
    VbvaContext->BufferOffset = BufferOffset;
    VbvaContext->BufferLength = BufferLength;
}
