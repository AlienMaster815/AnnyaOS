#include "DrsdCore.h"

static 
LOUSTATUS 
DrsdVRamManagerInitialize(
    PDRSD_VRAM_MM Vmm, 
    PDRSD_DEVICE Device, 
    UINT64 VRamBase, 
    UINT64 VRamSize
){
    LOUSTATUS Status;

    Vmm->VRamBase = VRamBase;
    Vmm->VRamSize = VRamSize;

    

    //TtmRangeManagerInitializeNoCheck

    return STATUS_SUCCESS;
}

static PDRSD_VRAM_MM DrsdVRamHelperAllocateManager(
    PDRSD_DEVICE Device,
    UINT64       VRamBase,
    UINT64       VRamSize
){
    LOUSTATUS Status;
    if(Device->VramManager){
        return STATUS_SUCCESS;
    }
    Device->VramManager = LouKeMallocType(DRSD_VRAM_MM, KERNEL_GENERIC_MEMORY);
    if(!Device->VramManager){
        return (PDRSD_VRAM_MM)(UINTPTR)STATUS_INSUFFICIENT_RESOURCES;
    }
    Status = DrsdVRamManagerInitialize(Device->VramManager, Device, VRamBase, VRamSize); 
    if(Status != STATUS_SUCCESS){
        goto _ERROR_FREE;
    }
    return Device->VramManager;
_ERROR_FREE:
    LouKeFree(Device->VramManager);
    Device->VramManager = 0x00;
    return (PDRSD_VRAM_MM)(UINTPTR)Status;
}

DRIVER_EXPORT
LOUSTATUS 
DrsdGxeVRamDriverDumbCreate(
    PDRSD_FILE Dile, 
    PDRSD_DEVICE Device, 
    PDRSE_MODE_CREATE_DUMB Args
){
    LouPrint("DrsdGxeVRamDriverDumbCreate()\n");
    while(1);   
    return STATUS_SUCCESS;
}

DRIVER_EXPORT
LOUSTATUS 
DrsdVRamHelperInitialize(
    PDRSD_DEVICE    Device,
    UINT64          VRamBase,
    SIZE            VRamSize
){
    PDRSD_VRAM_MM VramManager;
    if(Device->VramManager){
        LouPrint("DRSDCORE.SYS:WARNING:VRam Manager Object Already Exists\n");
        return STATUS_SUCCESS;
    }

    VramManager = DrsdVRamHelperAllocateManager(Device, VRamBase, VRamSize);

    LouPrint("DrsdVRamHelperInitialize()\n");
    while(1);
    return STATUS_SUCCESS;
}