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
 
#ifndef _DRSD_ATOMIC_H
#define _DRSD_ATOMIC_H

#include "DrsdCrtc.h"
#include "DrsdPlane.h"
#include "DrsdCore.h"

static inline UINT DrsdConnectorIndex(PDRSD_CONNECTOR Connector){
    return Connector->Index;
}

DRIVER_EXPORT
void 
__DrsdCrtcCommitFree(PKERNEL_REFERENCE Kref);

static inline void DrsdCrtcCommitPut(
    PDRSD_CRTC_COMMIT CrtcCommit
){
    LouKeReleaseReferenceAndCall(&CrtcCommit->Reference, __DrsdCrtcCommitFree);
}

static inline PDRSD_CRTC_STATE DrsdAtomicGetNewCrtcState(
    PDRSD_ATOMIC_STATE  State,
    PDRSD_CRTC          Crtc
){
    return State->Crtcs[DrsdCrtcIndex(Crtc)].NewState;
}

static inline PDRSD_PLANE_STATE DrsdAtomicGetNewPlaneState(PDRSD_ATOMIC_STATE State, PDRSD_PLANE Plane){
    return State->Planes[DrsdPlaneIndex(Plane)].NewState;
}

static inline PDRSD_CONNECTOR_STATE DrsdAtomicGetOldConnectorState(PDRSD_ATOMIC_STATE State, PDRSD_CONNECTOR Connector){
    UINT Index = DrsdConnectorIndex(Connector);
    if(Index >= State->ConnectorCount){
        return 0x00;
    }
    return State->Connectors[Index].OldState;
}

static inline PDRSD_CONNECTOR_STATE DrsdAtomicGetNewConnectorState(PDRSD_ATOMIC_STATE State, PDRSD_CONNECTOR Connector){
    UINT Index = DrsdConnectorIndex(Connector);
    if(Index >= State->ConnectorCount){
        return 0x00;
    }
    return State->Connectors[Index].NewState;
}

static inline PDRSD_BRIDGE_STATE DrsdPrivateToBridgeState(PDRSD_PRIVATE_STATE State){
    return CONTAINER_OF(State, DRSD_BRIDGE_STATE, Base);
}

DRIVER_EXPORT
PDRSD_CONNECTOR 
DrsdAtomicGetConnectorForEncoder(
    PDRSD_ENCODER                   Encoder,
    PDRSD_MODESET_ACQUIRE_CONTEXT    Context
);

DRIVER_EXPORT 
BOOLEAN 
IsDrsdAtomicGetConnectorForEncoderError(
    PDRSD_CONNECTOR Connector
);

DRIVER_EXPORT
PDRSD_COLOR_OP_STATE 
DrsdAtomicGetNewColorOpState(
    PDRSD_ATOMIC_STATE  State,
    PDRSD_COLOR_OP      ColorOp
);

DRIVER_EXPORT
PDRSD_COLOR_OP_STATE 
DrsdAtomicGetOldColorOpState(
    PDRSD_ATOMIC_STATE  State,
    PDRSD_COLOR_OP      ColorOp
);

DRIVER_EXPORT
PDRSD_PRIVATE_STATE
DrsdAtomicGetNewPrivateObjectState(
    PDRSD_ATOMIC_STATE      State,
    PDRSD_PRIVATE_OBJECT    Object
);

#define ForEachOldConnectorInState(State, Connector, OldConnectorState, Index) \
    for((Index) = 0; (Index) < (State)->ConnectorCount; (Index)++) \
        ForEachIf((State)->Connectors[Index].Connector && ((Connector) = ((State)->Connectors[Index].Connector), (void)(Connector), (OldConnectorState) = (State)->Connectors[Index].OldState, 1))

#define ForEachNewConnectorInState(State, Connector, NewConnectorState, Index) \
    for((Index) = 0; (Index) < (State)->ConnectorCount; (Index)++) \
        ForEachIf((State)->Connectors[Index].Connector && ((Connector) = ((State)->Connectors[Index].Connector), (void)(Connector), (NewConnectorState) = (State)->Connectors[Index].NewState, 1))


#endif