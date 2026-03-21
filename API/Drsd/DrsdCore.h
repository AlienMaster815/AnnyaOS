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
 
#define _KERNEL_MODULE_
#ifndef _DRSD_CORE_H
#define _DRSD_CORE_H

#include <LouDDK.h>

#include "DrsdCrtcInternals.h"
#include "DrsdCache.h"
#include "DrsdModes.h"
#include "DrsdModesetLock.h"
#include "DrsdAtomic.h"
#include "DrsdAtomicHelper.h"
#include "DrsdEdid.h"
#include "DrsdEld.h"
#include "DrsdDraw.h"
#include "DrsdFormat.h"
#include "DrsdModeObject.h"
#include "DrsdConnector.h"
#include "DrsdColorOp.h"
#include "DrsdCrtc.h"

typedef enum _DRSD_DRIVER_FEATURE{
    DRIVER_GXE = (1 << 0),
    DRIVER_MODESET = (1 << 1),
    DRIVER_RENDER = (1 << 3),
    DRIVER_ATOMIC = (1 << 4),
    DRIVER_SYNCOBJ = (1 << 5),
    DRIVER_SYNCOBJ_TIMELINE = (1 << 6),
    DRIVER_COMPUTE_ACCEL = (1 << 7),
    DRIVER_GXE_GPUA = (1 << 8),
    DRIVER_CURSOR_HOTSPOT = (1 << 9),
    DRIVER_USE_AGP = (1 << 25),
    DRIVER_LEGACY = (1 << 26),
    DRIVER_PCI_DMA = (1 << 27),
    DRIVER_SG = (1 << 28),
    DRIVER_HAVE_DMA = (1 << 29),
    DRIVER_HAVE_IRQ = (1 << 30),
}DRSD_DRIVER_FEATURE, * PDRSD_DRIVER_FEATURE;

static inline BOOLEAN DrsdCoreCheckAllFeatures(
    PDRSD_DEVICE    Device, 
    UINT32          Features
){
    UINT32 Support = Device->DeviceDriver->DriverFeatures & Device->DriverFeatures;
    return Features && ((Support & Features) == Features);
}

static inline BOOLEAN DrsdCoreCheckFeature(
    PDRSD_DEVICE            Device, 
    DRSD_DRIVER_FEATURE     Feature
){
    DrsdCoreCheckAllFeatures(Device, Feature);
}

DRIVER_EXPORT
void DrsdAcquireDevice(
    PDRSD_DEVICE Device
);

DRIVER_EXPORT
void DrsdReleaseDevice(
    PDRSD_DEVICE Device
);

#endif