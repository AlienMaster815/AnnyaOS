#include <LouDDK.h>

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

 
void DrsdAtomicDestroyPlaneState(PDRSD_PLANE_STATE PlaneState);
void DrsdModeObjectObjectFree(PDRSD_MODE_OBJECT Object);
void DrsdModeSetDestroyModeContext(PDRSD_DEVICE Device, PDRSD_MODE_SET_CONTEXT Setex);
void DrsdGxeDestroyShadowPlane(PDRSD_PLANE Plane);
void DrsdModeSetLockContext(PDRSD_MODE_SET_CONTEXT Context);
void DrsdResetCrtcVBlank(PDRSD_CRTC Crtc);
PDRSD_MODE_SET_CONTEXT DrsdInitializeModeContext(PDRSD_DEVICE Device);
void AddVBlankToCrtc(PDRSD_DEVICE Device);
void DrsdModeSetWarnIfLocked(PDRSD_DEVICE Device);
size_t GetDrsdCrtcIndex(PDRSD_CRTC Crtc);
DRSD_CONNECTOR_STATUS DrsdInternalProbeDetection(
    PDRSD_CONNECTOR Connector, 
    PDRSD_MODE_SET_CONTEXT Setex, 
    bool Force
);
DRSD_CONNECTOR_STATUS DrsdDetectConnectorStatus(
    PDRSD_CONNECTOR         Connector, 
    PDRSD_MODE_SET_CONTEXT  Setex,
    bool                    Force
);
int DrsdInternalProbeModes(PDRSD_CONNECTOR Connector);

