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

    

    return STATUS_SUCCESS;
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


