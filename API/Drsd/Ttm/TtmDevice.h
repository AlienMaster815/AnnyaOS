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
 
#ifndef _TTM_DEVICE_H
#define _TTM_DEVICE_H

#include "../DrsdCore.h"

static inline void TtmSetDriverManager(
    PDRSD_TTM_DEVICE        Device,
    int                     Type,
    PTTM_RESOURCE_MANAGER   Manager
){
    if(TTM_MEM_TYPES_COUNT > Type){
        Device->ManagerDriver[Type] = Manager;
    }else{
        LouPrint("DRSDCORE.SYS:TtmSetDriverManager():BUGBUG\n");
        while(1); //TODO:SysExit 
    } 
}

DRIVER_EXPORT
LOUSTATUS
TtmDeviceInitialize(
    PDRSD_TTM_DEVICE            Device,
    PTTM_DEVICE_FUNCTIONS       Functions,
    PPCI_DEVICE_OBJECT          PDEV,
    PDRSD_VMA_OFFSET_MANAGER    VmaManager,
    UINT64                      PageFlags
);

#endif