#include "DrsdCore.h"

// SPDX-License-Identifier: GPL-2.0-only
/*
 * AnnyaOS DRSD (Display Rendering Subsystem)
 *
 * This subsystem was inspired by the Linux DRM/KMS graphics stack architecture,
 * originally developed by contributors to the Linux kernel including:
 *
 *   - Dave Airlie          <airlied@linux.ie>
 *   - Daniel Vetter        <daniel.vetter@ffwll.ch>
 *   - Thomas Hellstrom     <thomas@vmware.com>
 *   - Alex Deucher         <alexander.deucher@amd.com>
 *   - Michel Dänzer        <michel@daenzer.net>
 *   - The X.Org / Mesa / DRM community
 *
 * This implementation is an original independent design under the DRSD architecture
 * for the Lousine Kernel. While its conceptual structure resembles Linux DRM/KMS
 * for hardware compatibility reasons (framebuffers, CRTCs, modesetting, planes,
 * scanout buffers), no Linux source code was copied or reused.
 *
 * All code was written from scratch for AnnyaOS. Behavior was based on:
 *
 *   - VESA and PCI/PCIe graphics initialization standards
 *   - AMD, Intel, and NVIDIA public GPU documentation
 *   - Linux DRM documentation (for behavioral understanding only)
 *   - Observed GPU hardware behavior during development
 *
 * Copyright (C) 2025 Tyler Grenier (AlienMaster815)
 * AnnyaOS Project — https://github.com/AlienMaster815/AnnyaOS
 *
 * Licensed under GPL-2.0-only. See COPYING for details.
 */

 
static DRSD_MODE_SET_CONTEXT ModeSetManagerContextList;
static mutex_t ModeSetManagerLock;

PDRSD_MODE_SET_CONTEXT DrsdInitializeModeContext(PDRSD_DEVICE Device){
    MutexLock(&Device->ModeConfiguration.ConfigLock);
    MutexLockEx(&ModeSetManagerLock, true);
    
    PDRSD_MODE_SET_CONTEXT TmpContextList = &ModeSetManagerContextList;

    while(TmpContextList->Peers.NextHeader){
        TmpContextList = (PDRSD_MODE_SET_CONTEXT)TmpContextList->Peers.NextHeader;
    }

    TmpContextList->Peers.NextHeader = (PListHeader)LouKeMallocType(DRSD_MODE_SET_CONTEXT, KERNEL_GENERIC_MEMORY);
    TmpContextList = (PDRSD_MODE_SET_CONTEXT)TmpContextList->Peers.NextHeader;

    TmpContextList->Device = Device;
    MutexUnlock(&ModeSetManagerLock);
    return TmpContextList;
}

//returns true if device is being used
void DrsdModeSetLockContext(PDRSD_MODE_SET_CONTEXT Context){
    MutexLockEx(&ModeSetManagerLock, true);
    MutexLockEx(&Context->ModeSetLock, false);
    MutexUnlock(&ModeSetManagerLock);

}

void DrsdModeSetWarnIfLocked(PDRSD_DEVICE Device){
    MutexLockEx(&ModeSetManagerLock, true);
    if(MutexIsLocked(&Device->ModeConfiguration.ConnectionMutex)){
        LouPrint("WARNING:DrsdModeSetWarnIfLocked() CONFIG IS LOCKED\n");
    }    
    MutexUnlock(&ModeSetManagerLock);
}

void DrsdModeSetUnlockContext(PDRSD_MODE_SET_CONTEXT Setex){
    MutexLockEx(&ModeSetManagerLock, true);
    MutexUnlock(&Setex->ModeSetLock);
    MutexUnlock(&ModeSetManagerLock);
}

void DrsdModeSetDestroyModeContext(PDRSD_DEVICE Device, PDRSD_MODE_SET_CONTEXT Setex){
    MutexLockEx(&ModeSetManagerLock, true);
    PDRSD_MODE_SET_CONTEXT TmpContextList = &ModeSetManagerContextList;
    while(TmpContextList->Peers.NextHeader){
        if((uintptr_t)TmpContextList->Peers.NextHeader == (uintptr_t)Setex){
            TmpContextList->Peers.NextHeader = ((PDRSD_MODE_SET_CONTEXT)TmpContextList->Peers.NextHeader)->Peers.NextHeader;
            LouKeFree(Setex);
            break;
        }
        TmpContextList = (PDRSD_MODE_SET_CONTEXT)TmpContextList->Peers.NextHeader;
    }
    MutexUnlock(&ModeSetManagerLock);
    MutexUnlock(&Device->ModeConfiguration.ConfigLock);
}