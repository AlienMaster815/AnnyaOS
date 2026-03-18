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
LOUSTATUS 
DrsdBridgeHelperResetCrtc(
    PDRSD_BRIDGE Bridge,
    PDRSD_MODESET_ACQURE_CONTEXT Context
){
    UNUSED PDRSD_CONNECTOR Connector;
    UNUSED PDRSD_ENCODER Encoder = Bridge->Encoder;
    UNUSED PDRSD_DEVICE Device = Encoder->Device; 
    UNUSED PDRSD_CRTC Crtc;
    LOUSTATUS Status;

    Status = DrsdModesetLock(&Device->ModeConfig.ConnectionMutex, Context);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    Connector = DrsdAtomicGetConnectorForEncoder(Encoder, Context);
    if(LOU_KE_ALLOC_PTR_ERROR(Connector)){
        Status = LOUPTR_ERROR(Connector);
        goto _HELPER_IS_DONE;
    }

    if(!Connector->State){
        Status = STATUS_INVALID_PARAMETER;
        goto _HELPER_IS_DONE;
    }

    Crtc = Connector->State->Crtc;
    Status = DrsdAtomicHelperResetCrtc(Crtc, Context);
    if(Status != STATUS_SUCCESS){
        goto _HELPER_IS_DONE;
    }
    
    _HELPER_IS_DONE:
    DrsdModesetUnlock(&Device->ModeConfig.ConnectionMutex);
    return Status;
}