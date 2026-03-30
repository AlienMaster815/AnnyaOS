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
#include "../DrsdCore.h"

static 
LOUSTATUS
TtmRangeManagerAlloc(
    PTTM_RESOURCE_MANAGER   Manager,
    PTTM_BUFFER_OBJECT      Bo,
    PTTM_PLACE              Place,
    PTTM_RESOURCE*          Resource
){
    LouPrint("TtmRangeManagerAlloc()\n");
    while(1);
    return STATUS_SUCCESS;
}

static
void 
TtmRangeManagerFree(
    PTTM_RESOURCE_MANAGER   Manager,
    PTTM_RESOURCE           Resource
){
    LouPrint("TtmRangeManagerFree()\n");
    while(1);
}

static 
BOOLEAN
TtmRangeManagerIntersects(
    PTTM_RESOURCE_MANAGER   Manager,
    PTTM_RESOURCE           Resource,
    PTTM_PLACE              Place,
    SIZE                    Size
){
    LouPrint("TtmRangeManagerIntersects()\n");
    while(1);
    return false;
}

static 
BOOLEAN
TtmRangeManagerCompatible(
    PTTM_RESOURCE_MANAGER   Manager,
    PTTM_RESOURCE           Resource,
    PTTM_PLACE              Place,
    SIZE                    Size
){
    LouPrint("TtmRangeManagerCompatible()\n");
    while(1);
    return false;
}

static TTM_RESOURCE_MANAGER_FUNCTION TtmRangeManagerFunctions = {
    .Alloc = TtmRangeManagerAlloc,
    .Free = TtmRangeManagerFree,
    .Intersects = TtmRangeManagerIntersects,
    .Compatible = TtmRangeManagerCompatible,
    //TODO: Debug function  
};

LOUSTATUS 
TtmRangeManagerInitializeNoCheck(
    PDRSD_TTM_DEVICE    TtmDevice,
    UINT                Type,
    BOOLEAN             UseTt,
    UINT64              Size
){
    PTTM_RESOURCE_MANAGER   Manager;
    PTTM_RANGE_MANAGER      RManager;

    RManager = LouKeMallocType(TTM_RANGE_MANAGER, KERNEL_GENERIC_MEMORY);
    if(!RManager){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Manager = &RManager->Manager;
    Manager->UseTt = UseTt;
    Manager->Functions = &TtmRangeManagerFunctions;

    TtmResourceManagerInitialize(Manager, TtmDevice, Size);
    
    DrsdMmInitialize(&RManager->Mm, 0 , Size);

    TtmSetDriverManager(TtmDevice, Type, Manager);
    TtmResourceManagerSetUsed(Manager, true);
    return STATUS_SUCCESS;
}