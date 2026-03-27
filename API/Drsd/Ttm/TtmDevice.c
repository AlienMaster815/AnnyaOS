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

static UINT TtmGlobalUsageCount = 0;
static mutex_t TtmGlobalMutex = {0};
DRIVER_EXPORT TTM_GLOBAL TtmGlobal;

static 
void
TtmGlobalRelease(){
    PTTM_GLOBAL Global = &TtmGlobal;
    MutexLock(&TtmGlobalMutex);
    if(--TtmGlobalUsageCount > 0){
        goto _DONE;
    }
    TtmPoolManagerDeInitialize();
    LouKeFreePage(Global->DumbyReadVirtBase);
    memset(Global, 0, sizeof(TTM_GLOBAL));
_DONE:
    MutexUnlock(&TtmGlobalMutex);
} 

static
LOUSTATUS 
TtmGlobalInitialize(){
    PTTM_GLOBAL Global = &TtmGlobal;
    SIZE        PageCount;
    SIZE        Dma32Count;
    LOUSTATUS   Status = STATUS_SUCCESS;

    MutexLock(&TtmGlobalMutex);
    if(++TtmGlobalUsageCount > 1){
        goto _DONE;
    }

    PageCount = GetRamSize() / MEGABYTE_PAGE;
    PageCount /= 2;
    
    Dma32Count = MIN(GetRamSize(), 2 * GIGABYTE) / MEGABYTE_PAGE;

    TtmPoolManagerInitialize(PageCount);

_DONE:
    if(Status != STATUS_SUCCESS){
        --TtmGlobalUsageCount;
    }
    MutexUnlock(&TtmGlobalMutex);
    return Status;
}

DRIVER_EXPORT
LOUSTATUS
TtmDeviceInitialize(
    PDRSD_TTM_DEVICE            Device,
    PTTM_DEVICE_FUNCTIONS       Functions,
    PPCI_DEVICE_OBJECT          PDEV,
    PDRSD_VMA_OFFSET_MANAGER    VmaManager,
    UINT64                      PageFlags
){

    Device->AllocationFlags = PageFlags;
    Device->Functions = Functions;
    
    
    Device->VmaManager = VmaManager;

    LouPrint("TtmDeviceInitialize()\n");
    while(1);
    return STATUS_SUCCESS;
}