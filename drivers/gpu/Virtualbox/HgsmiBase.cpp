// SPDX-License-Identifier: MIT
/* Copyright (C) 2006-2017 Oracle Corporation */

#define _KERNEL_MODULE_
#include <LouDDK.h>
#include "VirtualboxDriver.h"
#include <drivers/VBoxError.h>

LOUSTATUS 
HgsmiReportFlagsLocation(
    POOL Context, 
    uint32_t Location
){
    PHGSMI_BUFFER_LOCATION LocationBuffer; 

    LocationBuffer = (PHGSMI_BUFFER_LOCATION)HgsmiBufferAllocate(
        Context, 
        sizeof(HGSMI_BUFFER_LOCATION), 
        HGSMI_CH_HGSMI, 
        HGSMI_CC_HOST_FLAGS_LOCATION
    );

    if(!LocationBuffer){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    LocationBuffer->BufferLocation = Location;
    LocationBuffer->BufferLength = sizeof(HGSMI_HOST_FLAGS);

    HgsmiBufferSubmit(Context, LocationBuffer);
    HgsmiBufferFree(Context, LocationBuffer);

    return STATUS_SUCCESS;
}

LOUSTATUS
HgsmiSendCapabilityInfo(
    POOL Context, 
    uint32_t Capabilities
){
    PVBVA_CAPABILITIES VbvaCapabilities = (PVBVA_CAPABILITIES)HgsmiBufferAllocate(Context, sizeof(VBVA_CAPABILITIES), HGSMI_CH_VBVA, VBVA_INFORMATION_CAPS);
    if(!VbvaCapabilities){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    VbvaCapabilities->Rc = VERR_NOT_IMPLEMENTED;
    VbvaCapabilities->Capabilities = Capabilities;

    HgsmiBufferSubmit(Context, VbvaCapabilities);

    if(VbvaCapabilities->Rc < 0){
        LouPrint("VBOXGPU:ERROR:Error Sending HGSMI Capabilities Info\n");
    }

    HgsmiBufferFree(Context, VbvaCapabilities);

    return STATUS_SUCCESS;
}


LOUSTATUS 
HgsmiTestQueryConfiguration(
    POOL Context
){
    uint32_t Value = 0;
    LOUSTATUS Result;

    Result = HgsmiQueryConfiguration(
        Context,
        U32_MAX,
        &Value
    );
    if(Result != STATUS_SUCCESS){
        return Result;
    }

    return (Value == U32_MAX) ? STATUS_SUCCESS : STATUS_IO_DEVICE_ERROR;
}


LOUSTATUS 
HgsmiQueryConfiguration(
    POOL Context, 
    uint32_t Index, 
    uint32_t* Result
){
    PVBVA_CONFIGURATION32 Configuration = (PVBVA_CONFIGURATION32)HgsmiBufferAllocate(Context, sizeof(VBVA_CONFIGURATION32), HGSMI_CH_VBVA, VBVA_QUERY_CONFIGURATION32_COMMAND);
    if(!Configuration){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Configuration->Index = Index;
    Configuration->Value = U32_MAX;
    
    HgsmiBufferSubmit(Context, Configuration);

    *Result = Configuration->Value;
    
    HgsmiBufferFree(Context, Configuration);
    
    return STATUS_SUCCESS;
}

LOUSTATUS 
HgsmiUpdatePointerShape(
    POOL Context, 
    uint32_t Flags, 
    uint32_t HotX, 
    uint32_t HotY, 
    uint32_t Width, 
    uint32_t Height, 
    uint8_t* Pixels, 
    uint32_t Length
){
    PVBVA_MOUSE_POINTER_SHAPE Pointer;
    UINT32 PixelLength = 0;
    LOUSTATUS Result;
    
    if(Flags & VBOX_MOUSE_POINTER_SHAPE){
        PixelLength = ((((Width + 7) / 8) * Height + 3) & ~(3)) + Width * 4 * Height;
        if(PixelLength > Length){
            return STATUS_INVALID_PARAMETER;
        }
        Flags |= VBOX_MOUSE_POINTER_VISABLE;
    }

    Pointer = (PVBVA_MOUSE_POINTER_SHAPE)HgsmiBufferAllocate(Context, sizeof(VBVA_MOUSE_POINTER_SHAPE) + PixelLength + 4, HGSMI_CH_VBVA, VBVA_MOUSE_POINTER_SHAPE_COMMAND);
    if(!Pointer){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Pointer->Result = VINF_SUCCESS;
    Pointer->Flags = Flags;
    Pointer->HotX = HotX;
    Pointer->HotY = HotY;
    Pointer->Width = Width;
    Pointer->Height= Height;
    if(PixelLength){
        memcpy(Pointer->DataBlock, Pixels, PixelLength);
    }

    HgsmiBufferSubmit(Context, Pointer);

    switch(Pointer->Result){
        case VINF_SUCCESS:
            Result = STATUS_SUCCESS;
            break;
        case VERR_NO_MEMORY:
            Result = STATUS_INVALID_PARAMETER;
            break;
        case VERR_NOT_SUPPORTED:
            Result = STATUS_DEVICE_BUSY;
            break;    
        default:
            Result = STATUS_INVALID_PARAMETER;
    }
    
    HgsmiBufferFree(Context, Pointer);

    return Result;
}

LOUSTATUS 
HgsmiCursorPosition(
    POOL Context, 
    bool ReportPosition, 
    uint32_t X, 
    uint32_t Y, 
    uint32_t* Xhost, 
    uint32_t YHost
){

    

    return STATUS_SUCCESS;
}


