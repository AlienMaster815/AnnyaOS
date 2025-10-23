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


KERNEL_IMPORT
LOUSTATUS DrsdInitializeGenericPlane(
    PDRSD_DEVICE            Device, 
    PDRSD_PLANE             Plane,
    size_t                  CrtcLimit,
    PDRSD_PLANE_CALLBACKS   PlaneCallbacks,
    uint32_t*               PlaneFormats,
    size_t                  FormatCount,
    uint64_t*               FormatModifiers,
    DRSD_PLANE_TYPE         PlaneType,
    string                  Name,
    ...
){
    Plane->PlaneName = Name;
    Plane->Callbacks = PlaneCallbacks;
    Plane->FormatCount = FormatCount;
    Plane->FormatDefault = PlaneFormats ? false : true;
    Plane->Modifiers = FormatModifiers;
    Plane->ModifierDefault = FormatModifiers ? false : true;
    Plane->PlaneType = PlaneType;
    Plane->Device = Device;
    Plane->Formats = PlaneFormats; 

    //LouPrint("Callbacks->ResetPlane:%h\n", PlaneCallbacks->ResetPlane);

    PDRSD_PLANE Tmp = Device->Planes;
    if(!Tmp){
        Device->Planes = Plane;
    }else{
        while(Tmp->Peers.NextHeader){
            Tmp = (PDRSD_PLANE)Tmp->Peers.NextHeader;
        }
        Tmp->Peers.NextHeader = (PListHeader)Plane;
    }

    //TODO: later add support for Extra Data

    LouPrint("DrsdInitializeGenericPlane() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

void DrsdGxeDestroyShadowPlane(
    PDRSD_PLANE Plane
){

    DrsdAtomicDestroyPlaneState(Plane->PlaneState);

    LouPrint("DrsdGxeDestroyShadowPlane() STATUS_SUCCESS\n");
}
