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
 
#ifndef _DRSD_BRIDGE_INTERNAL_H
#define _DRSD_BRIDGE_INTERNAL_H

#include "DrsdCore.h"

DRIVER_EXPORT
void 
DrsdBridgeRemove(
    PDRSD_BRIDGE Bridge
);

DRIVER_EXPORT
PDRSD_BRIDGE
DrsdBridgeGet(
    PDRSD_BRIDGE Bridge
);

DRIVER_EXPORT
void
DrsdBridgePut(
    PDRSD_BRIDGE Bridge
);

DEFINE_FREE(DrsdBridgePut, PDRSD_BRIDGE, if (_T) DrsdBridgePut(_T))

static inline PDRSD_BRIDGE DrsdBridgeGetNextBridge(PDRSD_BRIDGE Bridge){
    Bridge = ListItemToTypeOrNull(&Bridge->ChainNode.NextHeader, DRSD_BRIDGE, ChainNode);
    if(!Bridge){
        return Bridge;
    }
    return DrsdBridgeGet(Bridge);
}

static inline 
PDRSD_BRIDGE DrsdBridgeGetNextBridgeAndPut(PDRSD_BRIDGE Bridge){
    PDRSD_BRIDGE Next = DrsdBridgeGetNextBridge(Bridge);
    DrsdBridgePut(Bridge);
    return Next;
}

static inline 
PDRSD_BRIDGE DrsdBridgeChainGetFirstBridge(PDRSD_ENCODER Encoder){
    return DrsdBridgeGet(ListItemToTypeOrNull(Encoder->BridgeChain.NextHeader, DRSD_BRIDGE, ChainNode));
}

#define DrsdForEachBridgeInChainScoped(Encoder, Bridge) \
    for(PDRSD_BRIDGE Bridge __free(DrsdBridgePut) = DrsdBridgeChainGetFirstBridge(Encoder); Bridge; Bridge = DrsdBridgeGetNextBridgeAndPut(Bridge))

static inline PDRSD_BRIDGE DrsdPrivateToBridge(
    PDRSD_PRIVATE_OBJECT    Private
){
    return CONTAINER_OF(Private, DRSD_BRIDGE, Base);
}


#endif