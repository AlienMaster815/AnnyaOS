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

UNUSED static mutex_t ConnectorListLock = {0};
UNUSED static LIST_OBJECT ConnectorList = {0};

static mutex_t ConnectorListIterationLock = {0};

typedef struct _DRSD_CONNECTOR_PROP_ENUM_LIST{
    INTEGER     Type;
    LOUSTR      Name;
    XARRAY      Ida;
}DRSD_CONNECTOR_PROP_ENUM_LIST, * PDRSD_CONNECTOR_PROP_ENUM_LIST;
 
static  DRSD_CONNECTOR_PROP_ENUM_LIST DrsdConnectorEnumList[] = {
    {DRSD_CONNECTOR_MODE_UNKOWN, "Unkown"},
    {DRSD_CONNECTOR_MODE_VGA, "VGA"},
    {DRSD_CONNECTOR_MODE_DVII, "DVI-I"},
    {DRSD_CONNECTOR_MODE_DVID, "DVI-D"},
    {DRSD_CONNECTOR_MODE_DVIA, "DVI-A"},
    {DRSD_CONNECTOR_MODE_COMPOSITE, "Composite"},
    {DRSD_CONNECTOR_MODE_SVIDEO, "SVIDEO"},
    {DRSD_CONNECTOR_MODE_LVDS, "LVDS"},
    {DRSD_CONNECTOR_MODE_COMPONENT, "Component"},
    {DRSD_CONNECTOR_MODE_9PIN_DIN, "DIN"},
    {DRSD_CONNECTOR_MODE_DISPLAY_PORT, "DP"},
    {DRSD_CONNECTOR_MODE_HDMI_A, "HDMI-A"},
    {DRSD_CONNECTOR_MODE_HDMI_B, "HDMI-B"},
    {DRSD_CONNECTOR_MODE_TV, "TV"},
    {DRSD_CONNECTOR_MODE_EDP, "EDP"},
    {DRSD_CONNECTOR_MODE_VIRTUAL, "Virtual"},
    {DRSD_CONNECTOR_MODE_DSI, "DSI"},
    {DRSD_CONNECTOR_MODE_DPI, "DPI"},
    {DRSD_CONNECTOR_MODE_WRITEBACK, "WriteBack"},
    {DRSD_CONNECTOR_MODE_SPI, "SPI"},
    {DRSD_CONNECTOR_MODE_USB, "USB"},
};

void DrsdConnectorIdaInitialize(){
    for(int i = 0; i < (ARRAY_SIZE(DrsdConnectorEnumList)); i++){
        LouKeXaInit(&DrsdConnectorEnumList[i].Ida);
    }
}

void DrsdConnectorIdaDestroy(){
    for(int i = 0; i < (ARRAY_SIZE(DrsdConnectorEnumList)); i++){
        LouKeXaDestroy(&DrsdConnectorEnumList[i].Ida);
    }
}

DRIVER_EXPORT
LOUSTR 
DrsdGetConnectorTypeName(UINT Type){
    if(Type >= 21){
        return 0x00;
    }
    return DrsdConnectorEnumList[Type].Name;
}

static void DrsdConnectorFree(PKERNEL_REFERENCE Ref){
    PDRSD_CONNECTOR Connector = CONTAINER_OF(Ref, DRSD_CONNECTOR, Base.ReferenceCount);
    PDRSD_DEVICE Device = Connector->Device;
    DrsdUnregisterModeObject(Device, &Connector->Base);
    Connector->Callbacks->Destroy(Connector);
}

void DrsdConnectorFreeWorkFunction(PLOUQ_WORK Work){
    PDRSD_CONNECTOR Connector, N;
    PDRSD_DEVICE Device = CONTAINER_OF(Work, DRSD_DEVICE, ModeConfig.ConnectorFreeWork);
    PDRSD_MODE_CONFIGURATION ModeConfig = &Device->ModeConfig;
    LouKIRQL Irql;
    PListHeader Freed;

    LouKeAcquireSpinLock(&ModeConfig->ConnectorListLock, &Irql);
    LouKeLListDeleteAll(&ModeConfig->ConnectorFreeList);
    LouKeReleaseSpinLock(&ModeConfig->ConnectorListLock, &Irql);

    ForEachLListEntrySafe(Connector, N, Freed, FreeNode){
        DrsdUnregisterModeObject(Device, &Connector->Base);
        Connector->Functions->Destroy(Connector);
    }

}

DRIVER_EXPORT
void 
DrsdConnectorListIterationBegin(
    PDRSD_DEVICE                    Device,
    PDRSD_CONNECTOR_LIST_ITERATION  Iteration
){
    Iteration->Device = Device;
    Iteration->Connector = 0x00;
    MutexLockEx(&ConnectorListIterationLock, false);
}

static 
void
DrsdConnectorPutSafe(
    PDRSD_CONNECTOR Connector
){
    PDRSD_MODE_CONFIGURATION    Config = &Connector->Device->ModeConfig;

    if(!LouKeGetReferenceCount(&Connector->Base.ReferenceCount)){
        return;
    }

    LouKeListAddTail(&Connector->FreeNode, &Config->ConnectorFreeList);
    LouKeQueueWork(&Config->ConnectorFreeWork);
}

DRIVER_EXPORT
PDRSD_CONNECTOR
DrsdConnectorListNextIteration(
    PDRSD_CONNECTOR_LIST_ITERATION Iteration
){
    PDRSD_CONNECTOR             OldConnector = Iteration->Connector;
    PDRSD_MODE_CONFIGURATION    Config = &Iteration->Device->ModeConfig;
    PListHeader                 lHeader;
    LouKIRQL                    Irql;

    LouKeAcquireSpinLock(&Config->ConnectorListLock, &Irql);
    lHeader = OldConnector ? &OldConnector->Head : &Config->ConnectorList;

    do{
        if(lHeader->NextHeader == &Config->ConnectorList){
            Iteration->Connector = 0x00;
            break;
        }
        lHeader = lHeader->NextHeader;

        Iteration->Connector = CONTAINER_OF(lHeader, DRSD_CONNECTOR, Head);

    }while(!LouKeAcquireReferenceIfNotZero(&Iteration->Connector->Base.ReferenceCount));

    if(OldConnector){
        DrsdConnectorPutSafe(OldConnector);
    }
    LouKeReleaseSpinLock(&Config->ConnectorListLock, &Irql);
    return Iteration->Connector;
}

DRIVER_EXPORT
void 
DrsdConnectorListIterationEnd(
    PDRSD_CONNECTOR_LIST_ITERATION  Iteration
){
    PDRSD_MODE_CONFIGURATION Config = &Iteration->Device->ModeConfig;
    LouKIRQL Flags;
    Iteration->Device = 0x00;
    if(Iteration->Connector){
        LouKeAcquireSpinLock(&Config->ConnectorListLock, &Flags);
        DrsdConnectorPutSafe(Iteration->Connector);
        LouKeReleaseSpinLock(&Config->ConnectorListLock, &Flags);
    }
    MutexLockEx(&ConnectorListIterationLock, false);
}

DRIVER_EXPORT
void DrsdAddProbedDisplayModeToConnector(PDRSD_CONNECTOR Connector, PDRSD_DISPLAY_MODE Mode){
    LouPrint("DrsdAddProbedDisplayModeToConnector()\n");
    while(1);
}

DRIVER_EXPORT
LOUSTATUS DrsdInternalProbeSingleConnectorModes(
    PDRSD_CONNECTOR Connector,
    uint32_t        MaxX,
    uint32_t        MaxY
){
    LouPrint("DrsdInternalProbeSingleConnectorModes()\n");
    while(1);
    return STATUS_SUCCESS;
}

DRIVER_EXPORT
LOUSTATUS DrsdUpdateEdidConnectorProperties(PDRSD_CONNECTOR Connector, PINTEL_STANDARD_EDID Edid){
    LouPrint("DrsdUpdateEdidConnectorProperties()\n");
    while(1);
    return STATUS_SUCCESS;
}
