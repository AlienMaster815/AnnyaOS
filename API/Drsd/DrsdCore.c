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

//TODO: Put this in DrsdGxe.h
LOUSTATUS 
DrsdGxeInitialize(
    PDRSD_DEVICE Device
);

static BOOLEAN DrsdCoreInitCompleted = false;

static XARRAY DrsdMinorsXa;
static XARRAY AccelMinorsXa;

static void DrsdDeviceRelease(PKERNEL_REFERENCE Reference){
    
}

static PDRSD_MINOR* DrsdMinorGetSlot(
    PDRSD_DEVICE    Device, 
    DRSD_MINOR_TYPE Type
){
    switch(Type){
        case DRSD_MINOR_PRIMARY:
            &Device->Primary;
        case DRSD_MINOR_RENDER:
            return &Device->Render;
        case DRSD_MINOR_ACCEL:
            return &Device->Accel;
        default:
            LouPrint("DRSDCORE.SYS:BUGBUG:DrsdMinorGetSlot()\n");
            while(1);
    }
}

static PXARRAY DrsdMinorGetXa(DRSD_MINOR_TYPE Type){
    if((Type == DRSD_MINOR_PRIMARY) || (Type == DRSD_MINOR_RENDER)){
        return &DrsdMinorsXa;
    }else if(Type == DRSD_MINOR_ACCEL){
        return &AccelMinorsXa;
    }
    return 0x00;
}

static inline LOUSTATUS DrsdMinorAllocate(
    PDRSD_DEVICE    Device, 
    DRSD_MINOR_TYPE Type
){
    PDRSD_MINOR Minor;
    LOUSTATUS   Status;
    Minor = LouKeMallocType(DRSD_MINOR, KERNEL_GENERIC_MEMORY);
    if(!Minor){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Minor->Type = Type;
    Minor->Device = Device;

    Status = LouKeXarrayAllocateInt(
        DrsdMinorGetXa(Type),
        &Minor->Index,
        0x00,
        191,
        KERNEL_GENERIC_MEMORY
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    *DrsdMinorGetSlot(Device, Type) = Minor;
    return STATUS_SUCCESS;
}

static LOUSTATUS DrsdInitializeDevice(
    PPCI_DEVICE_OBJECT  Pdev,
    PDRSD_DEVICE        Device,
    PDRSD_DRIVER        Driver
){
    LOUSTATUS Status;
    if(!DrsdCoreInitCompleted){
        return STATUS_NO_SUCH_DEVICE;
    }

    if(!Pdev){
        LouPrint("DRSDCOR.SYS:ERROR:No Parent");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    LouKeInitializeKernelRefence(&Device->Reference);

    Device->PDEV = Pdev;
    Device->DeviceDriver = Driver;
    Device->DriverFeatures = ~0u;

    if(DrsdCoreCheckFeature(Device, DRIVER_COMPUTE_ACCEL) && (DrsdCoreCheckFeature(Device, DRIVER_RENDER) || DrsdCoreCheckFeature(Device, DRIVER_MODESET))){
        LouPrint("DRSDCORE.SYS:ERROR:Drsd Driver Cannot Be Both A Compute Acceleration And Graphics Driver\n");
        return STATUS_INVALID_PARAMETER;
    }

    if(DrsdCoreCheckFeature(Device, DRIVER_COMPUTE_ACCEL)){
        LouPrint("DRSDCORE.SYS:DrsdInitializeDevice():DRIVER_COMPUTE_ACCEL\n");
        while(1);
    }else{
        if(DrsdCoreCheckFeature(Device, DRIVER_RENDER)){
            Status = DrsdMinorAllocate(Device, DRSD_MINOR_RENDER);
            if(Status != STATUS_SUCCESS){
                return Status;
            }
        }
        
        Status = DrsdMinorAllocate(Device, DRSD_MINOR_PRIMARY);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
    }

    if(DrsdCoreCheckFeature(Device, DRIVER_GXE)){
        Status = DrsdGxeInitialize(Device);
        if(Status){
            LouPrint("DRSD.SYS:ERROR:Could Not Initialize Graphecis EXecution Ststem\n");
            return Status;
        }
    }

    //TODO Add Device Unique Name
    
    return STATUS_SUCCESS;
}

static LOUSTATUS DrsdDeviceManagerInitializeDevice(
    PPCI_DEVICE_OBJECT  Pdev,
    PDRSD_DEVICE        Device,
    PDRSD_DRIVER        Driver
){
    LOUSTATUS Status = DrsdInitializeDevice(Pdev, Device, Driver);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    //TODO: track the manager
    return STATUS_SUCCESS;
}

DRIVER_EXPORT
PVOID
DrsdDeviceManagerAllocateDeviceEx(
    PPCI_DEVICE_OBJECT  Pdev, 
    PDRSD_DRIVER        Driver, 
    SIZE                Size, 
    SIZE                Offset
){
    PVOID           Container;
    PDRSD_DEVICE    Device;
    LOUSTATUS       Status;

    Container = LouKeMalloc(Size, KERNEL_GENERIC_MEMORY);
    if(!Container){
        return (PVOID)(UINTPTR)STATUS_INSUFFICIENT_RESOURCES;
    }

    Device = Container + Offset;
    Status = DrsdDeviceManagerInitializeDevice(Pdev, Device, Driver);
    if(Status != STATUS_SUCCESS){
        LouKeFree(Container);
        return (PVOID)(UINTPTR)Status;
    }
    Device->Managed.FinalFree = Container;
    return Container;
}

DRIVER_EXPORT
void LouKeDrsdHandleConflictingDevices(PPCI_DEVICE_OBJECT PDEV){
    LouPrint("LouKeDrsdHandleConflictingDevices()\n");
    while(1);
}

KERNEL_EXPORT
LOUSTATUS
LouKeDrsdInitializeDevice(
    PDRSD_DEVICE Device
){
    LouPrint("LouKeDrsdInitializeDevice()\n");
    while(1);
    return STATUS_SUCCESS;
}

DRIVER_EXPORT
void DrsdAcquireDevice(
    PDRSD_DEVICE Device
){
    if(Device){
        LouKeAcquireReference(&Device->Reference);
    }
}

DRIVER_EXPORT
void DrsdReleaseDevice(
    PDRSD_DEVICE Device
){
    if(Device){
        LouKeReleaseReferenceAndCall(&Device->Reference, DrsdDeviceRelease);
    }
}

KERNEL_ENTRY LOUSTATUS DrsdCoreSubsystemEntry(){
    LouPrint("DrsdCoreSubsystemEntry()\n");

    LOUSTATUS Result = STATUS_SUCCESS;

    DrsdConnectorIdaInitialize();
    DrsdMemcpyEarlyInit();

    //TODO:Finish this
    
    LouPrint("DrsdCoreSubsystemEntry() STATUS_SUCCESS\n");
    //while(1);
    
    DrsdCoreInitCompleted = true;

    return Result;
}

//EDID

DRIVER_EXPORT
size_t DrsdAddModesNoEDID(
    PDRSD_CONNECTOR Connector, 
    int32_t Width, 
    int32_t Height
){
    LouPrint("DrsdAddModesNoEDID()\n");
    while(1);
    return 0x00;
}

//GXE
DRIVER_EXPORT
LOUSTATUS 
LouKePassVramToDrsdMemoryManager(
    PDRSD_DEVICE Device, 
    void* VramBase, 
    size_t size, 
    void* PAddress
){
    LouPrint("LouKePassVramToDrsdMemoryManager()\n");
    while(1);
    return STATUS_SUCCESS;
}

DRIVER_EXPORT
PDRSD_FRAME_BUFFER DrsdGxeCreateAsyncFramebuffer(
    PDRSD_DEVICE                Device,
    PDRSD_FILE                  FilePrivate,
    PDRSD_FORMAT_INFORMATION    Info,
    PDRSD_MODE_FB_COMMAND2      ModeCommand
){
    LouPrint("DrsdGxeCreateAsyncFramebuffer()\n");
    while(1);
    return 0x00;
}