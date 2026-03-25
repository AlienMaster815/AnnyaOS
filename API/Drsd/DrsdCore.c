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

static BOOLEAN DrsdCoreInitCompleted = false;

static void DrsdDeviceRelease(PKERNEL_REFERENCE Reference){
    
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