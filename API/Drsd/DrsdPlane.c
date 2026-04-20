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
BOOLEAN
DrsdPlaneHasFormat(
    PDRSD_PLANE Plane,
    UINT32      Format,
    UINT64      Modifier
){


    return false;
}

DRIVER_EXPORT
UINT
DrsdPlaneGetDamageClipsCount(PDRSD_PLANE_STATE State){
    return (State && State->FbDamageClips) ? State->FbDamageClips->Length / sizeof(DRSD_MODE_RECT) : 0;
}

PDRSD_MODE_RECT
__DrsdPlaneGetDamageClips(
    PDRSD_PLANE_STATE State
){
    return (PDRSD_MODE_RECT)((State && State->FbDamageClips) ? State->FbDamageClips->Data : 0x00);
}

DRIVER_EXPORT
PDRSD_MODE_RECT
DrsdPlaneGetDamageClips(
    PDRSD_PLANE_STATE State
){
    PDRSD_DEVICE Device = State->Plane->Device;
    PDRSD_MODE_CONFIGURATION Config = &Device->ModeConfig;

    if(!DrsdModeObjectFindPropertyId(&State->Plane->Base, Config->PropFbDamageClips->Base.Identification)){
        LouPrint("DRSDCORE.SYS:DrsdPlaneEnableFbDamageClips() Not Called\n");
    }

    return __DrsdPlaneGetDamageClips(State);
}