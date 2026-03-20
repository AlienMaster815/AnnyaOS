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

DRIVER_EXPORT
void 
__DrsdCrtcCommitFree(PKERNEL_REFERENCE Kref){
    PDRSD_CRTC_COMMIT Commit = CONTAINER_OF(Kref, DRSD_CRTC_COMMIT, Reference);
    LouKeFree(Commit);
}

DRIVER_EXPORT
LOUSTATUS
DrsdCrtcCommitWait(
    PDRSD_CRTC_COMMIT Commit
){
    LOUSTATUS Status;
    if(!Commit){
        return STATUS_SUCCESS;
    }

    Status = LouKeWaitForCompletionTimeout(&Commit->HwDone, 10);
    if(Status != STATUS_SUCCESS){
        LouPrint("DRSD.SYS:Crtc:%h HwDone Timed Out\n", Commit->Crtc->Device);
        return STATUS_TIMEOUT;
    }

    Status = LouKeWaitForCompletionTimeout(&Commit->FlipDone, 10);
    if(Status != STATUS_SUCCESS){
        LouPrint("DRSD.SYS:Crtc:%h FlipDone Timed Out\n", Commit->Crtc->Device);
        return STATUS_TIMEOUT;
    }

    return STATUS_SUCCESS;
}

DRIVER_EXPORT 
void 
DrsdAtomicStateDefaultRelease(
    PDRSD_ATOMIC_STATE State
){
    LouKeFree(State->Connectors);
    LouKeFree(State->Crtcs);
    LouKeFree(State->Planes);
    LouKeFree(State->ColorOps);
    LouKeFree(State->PrivateObjects);
}

DRIVER_EXPORT
LOUSTATUS 
DrsdAtomicStateInitalize(
    PDRSD_DEVICE        Device,
    PDRSD_ATOMIC_STATE  State
){
    LouKeInitializeKernelRefence(&State->Reference);
    State->AllowModeSet = true;
    State->Crtcs = LouKeMallocArray(DRSD_CRTCS_STATE, Device->ModeConfig.CrtcCount, KERNEL_GENERIC_MEMORY);
    if(!State->Crtcs){
        goto _INIT_FAILED;
    }
    State->Planes = LouKeMallocArray(DRSD_PLANES_STATE, Device->ModeConfig.TotalPlaneCount, KERNEL_GENERIC_MEMORY);
    if(State->Planes){
        goto _INIT_FAILED;
    }
    State->ColorOps = LouKeMallocArray(DRSD_COLOR_OPS, Device->ModeConfig.ColorOpCount, KERNEL_GENERIC_MEMORY);
    if(State->ColorOps){
        goto _INIT_FAILED;
    }

    DrsdAcquireDevice(Device);
    State->Device = Device;

    LouPrint("DRSD.SYS:Allocated Device State:%h\n", State);

    return STATUS_SUCCESS;

    _INIT_FAILED:
        DrsdAtomicStateDefaultRelease(State);
        return STATUS_INSUFFICIENT_RESOURCES;

}

DRIVER_EXPORT
PDRSD_CONNECTOR 
DrsdAtomicGetConnectorForEncoder(
    PDRSD_ENCODER                   Encoder,
    PDRSD_MODESET_ACQURE_CONTEXT    Context
){


    return 0x00;
}
