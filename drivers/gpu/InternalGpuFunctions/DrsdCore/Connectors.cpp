#include "DrsdCore.h"

// SPDX-License-Identifier: GPL-2.0-only
/*
 * AnnyaOS DRSD (Display Rendering Subsystem)
 *
 * This subsystem was inspired by the Linux DRM/KMS graphics stack architecture,
 * originally developed by contributors to the Linux kernel including:
 *
 *   - Dave Airlie          <airlied@linux.ie>
 *   - Daniel Vetter        <daniel.vetter@ffwll.ch>
 *   - Thomas Hellstrom     <thomas@vmware.com>
 *   - Alex Deucher         <alexander.deucher@amd.com>
 *   - Michel Dänzer        <michel@daenzer.net>
 *   - The X.Org / Mesa / DRM community
 *
 * This implementation is an original independent design under the DRSD architecture
 * for the Lousine Kernel. While its conceptual structure resembles Linux DRM/KMS
 * for hardware compatibility reasons (framebuffers, CRTCs, modesetting, planes,
 * scanout buffers), no Linux source code was copied or reused.
 *
 * All code was written from scratch for AnnyaOS. Behavior was based on:
 *
 *   - VESA and PCI/PCIe graphics initialization standards
 *   - AMD, Intel, and NVIDIA public GPU documentation
 *   - Linux DRM documentation (for behavioral understanding only)
 *   - Observed GPU hardware behavior during development
 *
 * Copyright (C) 2025 Tyler Grenier (AlienMaster815)
 * AnnyaOS Project — https://github.com/AlienMaster815/AnnyaOS
 *
 * Licensed under GPL-2.0-only. See COPYING for details.
 */

 
DRSD_CONNECTOR_STATUS DrsdDetectConnectorStatus(
    PDRSD_CONNECTOR         Connector, 
    PDRSD_MODE_SET_CONTEXT  Setex,
    bool                    Force
){
    if(Connector->AssistCallbacks->ConnectorDetectContext){
        return Connector->AssistCallbacks->ConnectorDetectContext(Connector, Setex, Force);
    }else if(Connector->AssistCallbacks->ConnectorDetect){
        return Connector->AssistCallbacks->ConnectorDetect(Connector, Force);
    }else if(Connector->Callbacks->DetectConnector){
        Connector->Callbacks->DetectConnector(Connector, Force);
    }
    return DRSD_CONNECTOR_CONNECTED;
}

void DrsdAddProbedDisplayModeToConnector(PDRSD_CONNECTOR Connector, PDRSD_DISPLAY_MODE Mode){

    if(!Connector->ProbedModes.NextHeader){
        Connector->ProbedModes.NextHeader = (PListHeader)Mode;
        return;
    }
    PDRSD_DISPLAY_MODE Tmp = (PDRSD_DISPLAY_MODE)Connector->ProbedModes.NextHeader;
    while(Tmp->Peers.NextHeader){
        Tmp = (PDRSD_DISPLAY_MODE)Tmp->Peers.NextHeader;
    }
    Tmp->Peers.NextHeader = (PListHeader)Mode;
}

LOUSTATUS DrsdInternalProbeSingleConnectorModes(
    PDRSD_CONNECTOR Connector,
    uint32_t        MaxX,
    uint32_t        MaxY
){
    LouPrint("DrsdInternalProbeSingleConnectorModes()\n");
    PDRSD_DEVICE Device = Connector->Device;
    PDRSD_DISPLAY_MODE DispMode;
    DRSD_CONNECTOR_STATUS OldConnectorStatus;
    DRSD_CONNECTOR_STATUS Status;
    UNUSED int ModeCount;

    DrsdModeSetWarnIfLocked(Device);

    PDRSD_MODE_SET_CONTEXT Setex = DrsdInitializeModeContext(Device);

    DrsdModeSetLockContext(Setex);

    DispMode = (PDRSD_DISPLAY_MODE)Connector->SupportedModes.NextHeader;

    while(DispMode){
        DispMode->ModeStatus = DRSD_MODE_STALE;
        DispMode = (PDRSD_DISPLAY_MODE)DispMode->Peers.NextHeader;
    }

    OldConnectorStatus = Connector->ConnectorStatus;

    if(Connector->Force){
        if(
            (Connector->Force == DRSD_FORCE_ON) ||
            (Connector->Force == DRSD_FORCE_DIGITAL)
        ){
            Connector->ConnectorStatus = DRSD_CONNECTOR_CONNECTED;   
        }else {
            Connector->ConnectorStatus = DRSD_CONNECTOR_DISCONNECTED;
        }
        if(Connector->Callbacks->ForceConnector){
            Connector->Callbacks->ForceConnector(Connector);
        }
    }else{
        Status = DrsdInternalProbeDetection(Connector, Setex, true);
        Connector->ConnectorStatus = Status;   
    }

    if(Connector->ConnectorStatus != OldConnectorStatus){
        //TODO: Notify and register change
        LouPrint("NOTICE:Device Status Changed From:%d to %d\n", OldConnectorStatus, Connector->ConnectorStatus);

    }    

    if(!Device->ModeConfiguration.UsingPolling){
        Device->ModeConfiguration.UsingPolling = true;
    }

    //TODO Get Connection Enabled if not so

    Connector->ProbeModeCount = DrsdInternalProbeModes(Connector);


    DrsdModeSetDestroyModeContext(Device, Setex);
    LouPrint("DrsdInternalProbeSingleConnectorModes() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

PDRSD_EDID_TRACKER DrsdEdidCreateObject(PINTEL_STANDARD_EDID Edid);

static void ClearEld(PDRSD_CONNECTOR Connector){
    MutexLock(&Connector->EldTex);
    memset(Connector->Eld, 0, 128);
    MutexUnlock(&Connector->EldTex);
    Connector->LatencyPresent[0] = false;
    Connector->LatencyPresent[1] = false;
    Connector->VideoLatency[0] = 0;
    Connector->VideoLatency[1] = 0;
    Connector->AudioLatency[0] = 0;
    Connector->AudioLatency[1] = 0;
}

static void DrsdResetDisplayInformation(PDRSD_CONNECTOR Connector){
    PDRSD_DISPLAY_INFORMATION Tmp = &Connector->DisplayInformation;
    Tmp->MetricWidth = 0;
    Tmp->MetricHeight = 0;
    Tmp->BitsPerChannel = 0;
    Tmp->ColorFormats = 0;
    Tmp->CEARevision = 0;
    Tmp->MaxTmdsClock = 0;
    Tmp->DualDVI = false;
    Tmp->HdmiDevice = false;
    Tmp->AudioConection = false;
    Tmp->HdmiInfoFrameProtocol = false;
    Tmp->QuantizationSelectable = false;
    memset(&Tmp->HdmiInformation, 0 , sizeof(DRSD_HDMI_INFORMATION));
    memset(&Connector->HdmiSyncInformation, 0, sizeof(HDMI_SYNCRONIZATION_INFORMATION));
    Tmp->EdidHdmiRgb444DcModes = 0;
    Tmp->EdidHdmiYcbcr444DcModes = 0;
    Tmp->NDD = 0;
    memset(&Tmp->MonitorRangeInfo, 0, sizeof(DRSD_MONITOR_RANGE_INFORMATION));
    memset(&Tmp->LuminanceInformation, 0, sizeof(DRSD_LUMINANCE_RANGE_INFORMATION));
    Tmp->MsoStreamCount = 0;
    Tmp->MsoPixelOverlap = 0;
    Tmp->MaxDscBpp = 0;
    if(Tmp->Vics){
        LouKeFree(Tmp->Vics);
    }
    Tmp->Vics = 0x00;
    Tmp->VicsCount = 0;
    Tmp->Quirks = 0;
}

size_t EdidGetQuirks(PDRSD_EDID_TRACKER Edid);

void UpdateDisplayInformation(PDRSD_CONNECTOR Connector, PDRSD_EDID_TRACKER Edid){
    UNUSED PINTEL_STANDARD_EDID IntelEdid;
    PDRSD_DISPLAY_INFORMATION Info = &Connector->DisplayInformation;

    DrsdResetDisplayInformation(Connector);
    ClearEld(Connector);

    if(!Edid){
        return;
    }    
    
    IntelEdid = Edid->EdidBase;

    Info->Quirks = EdidGetQuirks(Edid);
   
    Info->MetricWidth = IntelEdid->WidthMetric * 10;
    Info->MetricHeight = IntelEdid->HeightMetric * 10;

    //TODO: DrsdGetMonitorRange(Connector, Edid);

    //if(IntelEdid->Revision < 3){
    //    goto _FINISH;
    //}

    //TODO: if(!DrsdEdidIsDigital(DrsdEdid)){
    //    goto _FINISH;
    //}    


    //TODO:Finish this

    //_FINISH:

}

LOUSTATUS DrsdEdidConnectorUdate(PDRSD_CONNECTOR Connector, PDRSD_EDID_TRACKER Edid){
    UpdateDisplayInformation(Connector, Edid);
    //TODO: Finish this
    LouPrint("DrsdEdidConnectorUdate() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS DrsdUpdateEdidConnectorProperties(PDRSD_CONNECTOR Connector, PINTEL_STANDARD_EDID Edid){
    return DrsdEdidConnectorUdate(Connector, DrsdEdidCreateObject(Edid));
}