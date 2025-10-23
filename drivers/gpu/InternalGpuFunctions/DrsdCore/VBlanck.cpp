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

PDRSD_VBLANK_CRTC GetDrsdVBlankCrtcFromCrtc(
    PDRSD_DEVICE    Device,
    PDRSD_CRTC      Crtc
){
    size_t Index = GetDrsdCrtcIndex(Crtc);
    PDRSD_VBLANK_CRTC VBlank = Device->VBlanks;
    for(size_t i = 0 ; i < Index; i++){
        VBlank = (PDRSD_VBLANK_CRTC)VBlank->Peers.NextHeader;
    }
    return VBlank;
}

void AddVBlankToCrtc(PDRSD_DEVICE Device){
    Device->VBlankCount++;
    PDRSD_VBLANK_CRTC VBlank = Device->VBlanks;
    if(!VBlank){
        Device->VBlanks = LouKeMallocType(DRSD_VBLANK_CRTC, KERNEL_GENERIC_MEMORY);
        return;
    }
    while(VBlank){
        if(!VBlank->Peers.NextHeader){
            VBlank->Peers.NextHeader = (PListHeader)LouKeMallocType(DRSD_VBLANK_CRTC, KERNEL_GENERIC_MEMORY);
            return;          
        }
        VBlank = (PDRSD_VBLANK_CRTC)VBlank->Peers.NextHeader;
    }   
}

void DrsdResetCrtcVBlank(
    PDRSD_CRTC Crtc
){
    PDRSD_DEVICE Device = Crtc->Device;
    PDRSD_VBLANK_CRTC VBlank = GetDrsdVBlankCrtcFromCrtc(Device, Crtc);
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&Device->VBlankLock, &Irql);
    if(!VBlank->InModeset){
        LouKeSetAtomic(&VBlank->Count, LouKeGetAtomic(&VBlank->Count) + 1);
        VBlank->InModeset++;
    }
    LouKeReleaseSpinLock(&Device->VBlankLock, &Irql);
}