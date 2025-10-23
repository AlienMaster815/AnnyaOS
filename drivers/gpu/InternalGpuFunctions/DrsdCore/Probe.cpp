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

 
int DrsdInternalProbeModes(PDRSD_CONNECTOR Connector){

    int Count = Connector->AssistCallbacks->ConnectorGetModes(Connector);

    if(Count < 1){
        LouPrint("ERROR No Modes Available\n");
    }

    //TODO Add Edid Overide

    LouPrint("DrsdInternalProbeModes() STATUS_SUCCESS\n");
    return Count;
}

DRSD_CONNECTOR_STATUS DrsdInternalProbeDetection(
    PDRSD_CONNECTOR Connector, 
    PDRSD_MODE_SET_CONTEXT Setex, 
    bool Force
){
    DRSD_CONNECTOR_STATUS ConnectorStatus;
    
    DrsdModeSetLockContext(Setex);

    ConnectorStatus = DrsdDetectConnectorStatus(Connector, Setex, Force);

    if(ConnectorStatus != Connector->ConnectorStatus){
        Setex->EpochCounter += 1;
    }
    
    return ConnectorStatus;
}