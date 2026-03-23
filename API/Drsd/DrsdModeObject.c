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

LOUSTATUS 
DrsdModeObjectAddEx(
    PDRSD_DEVICE            Device,
    PDRSD_MODE_OBJECT       Object,
    UINT32                  ObjectType,
    BOOLEAN                 RegisterObject,
    void                  (*ObjectFreeCb)(PKERNEL_REFERENCE)
){
    LOUSTATUS Result;
    MutexLock(&Device->ModeConfig.IdrMutex);
    int Out = 1;
    Result = LouKeXaIdrAllocate(&Device->ModeConfig.ObjectIdr, RegisterObject ? Object : 0x00, &Out, 0, KERNEL_GENERIC_MEMORY);    
    if(Result == STATUS_SUCCESS){
        Object->Identification = Out;
        Object->ModeType = ObjectType;
        if(ObjectFreeCb){
            Object->FreeCb = ObjectFreeCb;
            LouKeInitializeKernelRefence(&Object->ReferenceCount);   
        }
    }
    MutexUnlock(&Device->ModeConfig.IdrMutex);
    return Result; 
}

LOUSTATUS 
DrsdModeObjectAdd(
    PDRSD_DEVICE            Device,
    PDRSD_MODE_OBJECT       Object,
    UINT32                  ObjectType
){
    return DrsdModeObjectAddEx(Device, Object, ObjectType, true, 0x00);
}


BOOLEAN DrsdModeObjectLeaseRequires(UINT32 Type){
    switch(Type){
        case DRSD_MODE_OBJECT_CRTC:
        case DRSD_MODE_OBJECT_CONNECTOR:
        case DRSD_MODE_OBJECT_PLANE:
            return true;
        default:
            return false;
    }
}

DRIVER_EXPORT
void 
DrsdModeObjectPut(
    PDRSD_MODE_OBJECT ModeObject
){

    if(ModeObject->FreeCb){
        LouPrint("DRSDCORE.SYS:DrsdModeObjectPut():Object ID:%d", ModeObject->Identification);
        LouKeReleaseReferenceAndCall(&ModeObject->ReferenceCount, ModeObject->FreeCb);
    }
}

DRIVER_EXPORT
void 
DrsdModeObjectGet(
    PDRSD_MODE_OBJECT ModeObject
){
    if(ModeObject->FreeCb){
        LouPrint("DRSDCORE.SYS:DrsdModeObjectGet():Object ID:%d", ModeObject->Identification);
        LouKeAcquireReference(&ModeObject->ReferenceCount);
    }
}


void DrsdUnregisterModeObject(
    PDRSD_DEVICE Device, 
    PDRSD_MODE_OBJECT Object
){

    

}