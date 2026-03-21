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


DRIVER_EXPORT
void DrsdAcquireDevice(
    PDRSD_DEVICE Device
);

DRIVER_EXPORT
void DrsdReleaseDevice(
    PDRSD_DEVICE Device
);

#endif