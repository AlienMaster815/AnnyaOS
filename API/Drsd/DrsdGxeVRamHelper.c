 /*
 * Copyright (c) 2026 AnnyaOS
 *
 * This file is a derivative work based on Linux DRM,
 * Copyright (c) 1994 - current
 *   - Dave Airlie          <airlied@linux.ie>
 *   - Daniel Vetter        <daniel.vetter@ffwll.ch>
 *   - Thomas Hellstrom     <thomas@vmware.com>
 *   - Alex Deucher         <alexander.deucher@amd.com>
 *   - Michel Dänzer        <michel@daenzer.net>
 *   - The X.Org / Mesa / DRM community
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "DrsdCore.h"

static PTTM_TT BoDriverTtmTtCreate(
    PTTM_BUFFER_OBJECT  Bo, 
    UINT64              PageFlags
){
    LouPrint("BoDriverTtmTtCreate()\n");
    while(1);
    return 0x00;
}


static void BoDriverTtmTtDestroy(PDRSD_TTM_DEVICE TtmDevice, PTTM_TT Tt){
    LouPrint("BoDriverTtmTtDestroy()\n");
    while(1);
}

DRIVER_EXPORT
BOOLEAN 
TtmBoEvictionValuable(
    PTTM_BUFFER_OBJECT  Bo,
    PTTM_PLACE          Place
){
    LouPrint("TtmBoEvictionValuable()\n");
    while(1);
    return false;
}

static 
void 
BoDriverEvictFlags(
    PTTM_BUFFER_OBJECT  Bo,
    PTTM_PLACEMENT      Placement
){
    LouPrint("BoDriverEvictFlags()\n");
    while(1);
}

static 
LOUSTATUS
BoDriverMove(
    PTTM_BUFFER_OBJECT      Bo,
    BOOLEAN                 Evict,
    PTTM_OPERATION_CONTEXT  Ctx,
    PTTM_RESOURCE           NewMem,
    PTTM_PLACE              Hop
){
    LouPrint("BoDriverMove()\n");
    while(1);
    return STATUS_SUCCESS;
}

static
void 
BoDriverDeleteMemNotify(
    PTTM_BUFFER_OBJECT  Bo
){
    LouPrint("BoDriverDeleteMemNotif()\n");
    while(1);
}

static 
LOUSTATUS 
BoDriverIoMemReserve(
    PDRSD_TTM_DEVICE    Device,
    PTTM_RESOURCE       Mem
){
    LouPrint("BoDriverIoMemReserve()\n");
    while(1);
    return STATUS_SUCCESS;
}

static TTM_DEVICE_FUNCTIONS BoDriver = {
    .TtmTtCreate = BoDriverTtmTtCreate,
    .TtmTtDestroy = BoDriverTtmTtDestroy,
    .EvictionValuable = TtmBoEvictionValuable,
    .EvictFlags = BoDriverEvictFlags,
    .Move = BoDriverMove,
    .DeleteMemNotify = BoDriverDeleteMemNotify,
    .IoMemReserve = BoDriverIoMemReserve,
};

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

    Status = TtmDeviceInitialize(
        &Vmm->TtmDevice,
        &BoDriver,
        Device->PDEV,
        Device->VmaOffsetManager,
        TTM_ALLOCATION_POOL_USE_DMA32
    );

    if(Status != STATUS_SUCCESS){
        return Status;
    }

    Status = TtmRangeManagerInitialize(
        &Vmm->TtmDevice, 
        TTM_PL_VRAM,
        false,
        VRamSize / KILOBYTE_PAGE
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    LouPrint("DrsdVRamManagerInitialize()\n");
    while(1);
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