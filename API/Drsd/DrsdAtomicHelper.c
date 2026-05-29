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

static 
void
DrsdAtomicHelperPlaneChanged(
    PDRSD_ATOMIC_STATE  State,
    PDRSD_PLANE_STATE   OldPlaneState,
    PDRSD_PLANE_STATE   PlaneState,
    PDRSD_PLANE         Plane
){
    PDRSD_CRTC_STATE CrtcState;
    if(OldPlaneState->Crtc){
        CrtcState = DrsdAtomicGetNewCrtcState(State, OldPlaneState->Crtc);
        if(!CrtcState){
            LouPrint("DRSD.SYS:WARNING:DrsdAtomicHelperPlaneChanged() OldPlaneState CrtcState Null\n");
            return;
        }
        CrtcState->PlanesChanged = true;
    }

    if(PlaneState->Crtc){
        CrtcState = DrsdAtomicGetNewCrtcState(State, PlaneState->Crtc);
        if(!CrtcState){
            LouPrint("DRSD.SYS:WARNING:DrsdAtomicHelperPlaneChanged() PlaneState CrtcState Null\n");
            return;
        }
        CrtcState->PlanesChanged = true;
    }
}

static
LOUSTATUS
HandleConflictingEncoders(
    PDRSD_ATOMIC_STATE  State,
    BOOLEAN             DisableConflictingEncoders
){
    PDRSD_CONNECTOR_STATE           NewConnectorState;
    PDRSD_CONNECTOR                 Connector;
    DRSD_CONNECTOR_LIST_ITERATION   ConnectorIteration;
    PDRSD_ENCODER                   Encoder;
    UINT                            EncoderMask;
    LOUSTATUS                       Status;
    int                             i;

    ForEachNewConnectorInState(State, Connector, NewConnectorState, i){
        PDRSD_CONNECTOR_HELPER_FUNCTIONS Functions = Connector->AssistFunctions;
        PDRSD_ENCODER NewEncdoder;

        if(!NewConnectorState->Crtc){
            continue;
        }

        if(Functions->AtomicBestEncoder){
            NewEncdoder = Functions->AtomicBestEncoder(Connector, State);
        }else if(Functions->BestEncoder){
            NewEncdoder = Functions->BestEncoder(Connector);
        }
        else{
            NewEncdoder = DrsdConnectorGetSingleEncoder(Connector);
        }

        if(NewEncdoder){
            if(EncoderMask & DrsdEncoderMask(NewEncdoder)){
                LouPrint("New Enocder:%h Is Invalid\n", NewEncdoder);
                return STATUS_INVALID_PARAMETER;
            }
            EncoderMask |= DrsdEncoderMask(NewEncdoder);
        }
    }

    if(!EncoderMask){
        return 0x00;
    }

    DrsdConnectorListIterationBegin(State->Device, &ConnectorIteration);
    DrsdForEachConnectorIteration(Connector, &ConnectorIteration){

        PDRSD_CRTC_STATE CrtcState;
        if(DrsdAtomicGetNewConnectorState(State, Connector)){
            continue;
        }
        
        Encoder = Connector->State->BestEncoder;
        if((!Encoder)  || (!(EncoderMask & DrsdEncoderMask(Encoder)))){
            continue;
        } 

        if(!DisableConflictingEncoders){
        LouPrint("DEVICE:%s Encoder:%d:%s In Use CRTC:%d:%s By Connector:%d:%s\n", Connector->Device, Encoder->Base.Identification, Encoder->Name, NewConnectorState->Crtc->Base.Identification, NewConnectorState->Crtc->Name, Connector->Base.Identification, Connector->Name);
            Status = STATUS_INVALID_PARAMETER;
            goto _OUT;
        }
        
        NewConnectorState = DrsdAtomicGetConnectorState(State, Connector);
        if(IS_LOU_KE_PTR_ERROR(NewConnectorState)){
            Status = LOU_KE_PTR_ERROR(NewConnectorState);
            goto _OUT;
        }   
        LouPrint("DEVICE:%s Encoder:%d:%s On CRTC:%d:%s Disabling Connector:%d:%s\n", Connector->Device, Encoder->Base.Identification, Encoder->Name, NewConnectorState->Crtc->Base.Identification, NewConnectorState->Crtc->Name, Connector->Base.Identification, Connector->Name);

        CrtcState = DrsdAtomicGetNewCrtcState(State, NewConnectorState->Crtc);

        Status = DrsdAtomicSetCrtcForConnector(NewConnectorState, 0x00);
        if(Status != STATUS_SUCCESS){
            goto _OUT;
        }

        if(!CrtcState->ConnectorMask){
            Status = DrsdAtomicSetModePropForCrtc(CrtcState, 0x00);
            if(Status != STATUS_SUCCESS){
                goto _OUT;
            }
            CrtcState->Active = false;
        }
    }
_OUT:
    DrsdConnectorListIterationEnd(&ConnectorIteration);    
    return Status;
}



static 
LOUSTATUS
PageFlipCommon(
    PDRSD_ATOMIC_STATE          State,
    PDRSD_CRTC                  Crtc,
    PDRSD_FRAME_BUFFER          FrameBuffer,
    PDRSD_PENDING_VBLANK_EVENT  VBlankEvent,
    UINT32                      Flags
){
    
    PDRSD_PLANE             Plane = Crtc->Primary;
    PDRSD_PLANE_STATE       PlaneState;
    PDRSD_CRTC_STATE        CrtcState;
    LOUSTATUS               Status = STATUS_SUCCESS;

    CrtcState = DrsdAtomicGetCrtcState(State, Crtc);
    if(IS_LOU_KE_PTR_ERROR(CrtcState)){
        return LOU_KE_PTR_ERROR(CrtcState);
    }

    CrtcState->Event = VBlankEvent;
    CrtcState->AsyncFlip = Flags & DRSD_MODE_PAGE_FLIP_ASYNC;

    PlaneState = DrsdAtomicGetPlaneState(State, Plane);
    if(IS_LOU_KE_PTR_ERROR(PlaneState)){
        return LOU_KE_PTR_ERROR(PlaneState);
    }

    Status = DrsdAtomicSetCrtcForPlane(PlaneState, Crtc);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    DrsdAtomicSetFbForPlane(PlaneState, FrameBuffer);

    State->AllowModeSet = false;
    if(!CrtcState->Active){
        LouPrint("DEVICE:%h CRTC:%d:%h Disabled Rejecting Legacy Flip\n");
        return STATUS_INVALID_PARAMETER;
    }

    return Status;
}

static 
void 
SetBestEncoder(
    PDRSD_ATOMIC_STATE      State,
    PDRSD_CONNECTOR_STATE   ConnectorState,
    PDRSD_ENCODER           Encoder
){
    PDRSD_CRTC_STATE    CrtcState;
    PDRSD_CRTC          Crtc;
    if(ConnectorState->BestEncoder){
        Crtc = ConnectorState->Connector->State->Crtc;
        if(!Crtc && Encoder != ConnectorState->BestEncoder){
            LouPrint("DRSD.SYS:WARNING:SetBestEncoder():Crtc Is Null In AN NON Duplicate Atomic State Restoration\n");
        }
        if(Crtc){
           CrtcState = DrsdAtomicGetNewCrtcState(State, Crtc);
           CrtcState->EncoderMask &= ~DrsdEncoderMask(ConnectorState->BestEncoder); 
        }
    }
    if(Encoder){
        Crtc = ConnectorState->Crtc;
        if(Crtc){
            CrtcState = DrsdAtomicGetCrtcState(State, Crtc);
            CrtcState->EncoderMask |= DrsdEncoderMask(Encoder); 
        }else{
            LouPrint("DRSD.SYS:WARNING:SetBestEncoder():Crtc Is Null\n");                        
        }
    }   
    ConnectorState->BestEncoder = Encoder;
}

static 
void
StealEncoder(
    PDRSD_ATOMIC_STATE  State,
    PDRSD_ENCODER       Encoder
){
    PDRSD_CRTC_STATE        CrtcState;
    PDRSD_CONNECTOR         Connector;
    PDRSD_CONNECTOR_STATE   OldConnectorState;
    PDRSD_CONNECTOR_STATE   NewConnectorState;
    int Index;

    ForEachOldNewConnectorInState(State, Connector, OldConnectorState, NewConnectorState, Index){
        PDRSD_CRTC EncoderCrtc;
        if(NewConnectorState->BestEncoder != Encoder){
            continue;
        }

        EncoderCrtc = NewConnectorState->Crtc;
        LouPrint("DRSD.SYS:StealEncoder():Device:%h [ENCODER:%d:%s] In Use On [CRTC:%d:%s], Stealing It\n", Encoder->Device , Encoder->Base.Identification, Encoder->Name, EncoderCrtc->Base.Identification, EncoderCrtc->Name);
        
        SetBestEncoder(State, NewConnectorState, 0x00);

        CrtcState = DrsdAtomicGetNewCrtcState(State, EncoderCrtc);
        CrtcState->ConnectorsChanged = true;
        return;
    }
}

static 
LOUSTATUS
UpdateConnectorRouting(
    PDRSD_ATOMIC_STATE      State,
    PDRSD_CONNECTOR         Connector,
    PDRSD_CONNECTOR_STATE   OldConnectorState,
    PDRSD_CONNECTOR_STATE   NewConnectorState,
    BOOLEAN                 AddedByUser
){
    PDRSD_CONNECTOR_HELPER_FUNCTIONS    Functions;
    PDRSD_ENCODER                       Encoder;
    PDRSD_CRTC_STATE                    CrtcState;

    LouPrint("DRSD.SYS:Device:%h Updating Routing For [CONNECTOR:%d:%s]\n", Connector->Device, Connector->Base.Identification, Connector->Name);

    if(OldConnectorState->Crtc != NewConnectorState->Crtc){
        if(!OldConnectorState->Crtc){
            CrtcState = DrsdAtomicGetNewCrtcState(State, OldConnectorState->Crtc);
            CrtcState->ConnectorsChanged = true;
        }
        if(NewConnectorState->Crtc){
            CrtcState = DrsdAtomicGetNewCrtcState(State, NewConnectorState->Crtc);
            CrtcState->ConnectorsChanged = true;
        }
    }

    if(!NewConnectorState->Crtc){
        LouPrint("DRSD.SYS:Device:%h [CONNECTOR:%d:%s]\n", Connector->Device, Connector->Base.Identification, Connector->Name);
        SetBestEncoder(State, NewConnectorState, 0x00);
        return STATUS_SUCCESS;
    }

    CrtcState = DrsdAtomicGetNewCrtcState(State, NewConnectorState->Crtc);

    if(State->Duplicated && DrsdConnectorIsUnRegistered(Connector) && AddedByUser && CrtcState->Active){
        //LouPrint("DRSD.SYS:Device");
        return STATUS_INVALID_PARAMETER;
    }

}

DRIVER_EXPORT
LOUSTATUS 
DrsdAtomicCommit(
    PDRSD_ATOMIC_STATE State  
){
    LOUSTATUS Status;
    PDRSD_MODE_CONFIGURATION ModeConfig = &State->Device->ModeConfig;

    Status = DrsdAtomicCheckOnly(State);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    return ModeConfig->Functions->AtomicCommit(State->Device, State, false);

}

DRIVER_EXPORT
LOUSTATUS 
DrsdAtomicHelperResetCrtc(
    PDRSD_CRTC                       Crtc,
    PDRSD_MODESET_ACQUIRE_CONTEXT    Context
){


    return STATUS_SUCCESS;
}



DRIVER_EXPORT
LOUSTATUS 
DrsdAtomicHelperCrtcSetConfiguration(
    PDRSD_MODE_SET                  Mode,
    PDRSD_MODESET_ACQUIRE_CONTEXT   ModeSetAquireContext
){
    PDRSD_ATOMIC_STATE  State;
    PDRSD_CRTC          Crtc = Mode->Crtc;
    LOUSTATUS Status;

    State = DrsdAtomicStateAllocate(Crtc->Device);
    if(!State){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    State->AcquireContext = ModeSetAquireContext;
    Status = __DrsdAtomicHelperSetConfig(Mode, State);
    if(Status != STATUS_SUCCESS){
        goto _SET_CONFIG_FAILED;
    }

    Status =  HandleConflictingEncoders(State, true);
    if(Status != STATUS_SUCCESS){
        goto _SET_CONFIG_FAILED;
    }

    Status = DrsdAtomicCommit(State);

_SET_CONFIG_FAILED:
    DrsdAtomicStatePut(State);
    return Status;
}


DRIVER_EXPORT
LOUSTATUS 
DrsdAtomicHelperPageFlip(
    PDRSD_CRTC                      Crtc,
    PDRSD_FRAME_BUFFER              FrameBuffer,
    PDRSD_PENDING_VBLANK_EVENT      VBlankEvent,
    uint32_t                        Flags,
    PDRSD_MODESET_ACQUIRE_CONTEXT   ModeSetAquireContext
){
    PDRSD_PLANE         Plane = Crtc->Primary;
    PDRSD_ATOMIC_STATE  State;
    LOUSTATUS           Status = STATUS_SUCCESS;

    State = DrsdAtomicStateAllocate(Plane->Device);
    if(!State){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    State->AcquireContext = ModeSetAquireContext;

    Status = PageFlipCommon(State, Crtc, FrameBuffer, VBlankEvent, Flags);
    if(Status != STATUS_SUCCESS){
        goto _FAIL;
    }

    Status = DrsdAtomicNonBlockingCommit(State);

_FAIL:
    DrsdAtomicStatePut(State);
    return Status;
}

DRIVER_EXPORT
LOUSTATUS
DrsdAtomicHelperCheckPlaneState(
    PDRSD_PLANE_STATE   PlaneState,
    PDRSD_CRTC_STATE    CrtcState,
    int                 MinScale,
    int                 MaxScale,
    BOOLEAN             CanPosition,
    BOOLEAN             CanUpdateDisabled
){  
    PDRSD_FRAME_BUFFER  FrameBuffer = PlaneState->FrameBuffer;
    PDRSD_RECT          Source = &PlaneState->Source; 
    PDRSD_RECT          Destination = &PlaneState->Destination; 
    UINT                Rotation = PlaneState->Rotation;
    DRSD_RECT           Clip = {0};
    int                 HScale;
    int                 VScale;

    *Source = DrsdPlaneStateSource(PlaneState);
    *Destination = DrsdPlaneStateSource(PlaneState);

    if(!FrameBuffer){
        PlaneState->Visable = false;
        return STATUS_SUCCESS;
    }

    if(!PlaneState->Crtc){
        PlaneState->Visable = false;
        return STATUS_SUCCESS;
    }

    if((!CrtcState->Enable) && (!CanUpdateDisabled)){
        //TODO: Debug print
        return STATUS_INVALID_PARAMETER;
    }
    
    DrsdRectRotate(Source, FrameBuffer->Width << 16, FrameBuffer->Height << 16, Rotation);

    LOUSTATUS Status = DrsdRectCalcHScale(Source, Destination, MinScale, MaxScale, &HScale);
    if(Status != STATUS_SUCCESS){
        LouPrint("DRSDCORE.SYS:DrsdAtomicHelperCheckPlaneState():ERROR Calculating HScale\n");
        return Status;
    }
    Status = DrsdRectCalcHScale(Source, Destination, MinScale, MaxScale, &VScale);
    if(Status != STATUS_SUCCESS){
        LouPrint("DRSDCORE.SYS:DrsdAtomicHelperCheckPlaneState():ERROR Calculating VScale\n");
        return Status;
    }

    if((HScale < 0) || (VScale < 0)){
        LouPrint("DRSDCORE.SYS:DrsdAtomicHelperCheckPlaneState():ERROR Invalid PlaneState\n");
        return STATUS_INTEGER_OVERFLOW;
    }

    if(CrtcState->Enable){
        DrsdModeGetHvTiming(&CrtcState->Mode, &Clip.X2, &Clip.Y2);
    }

    Status = DrsdRectClipScaled(Source, Destination, &Clip, &PlaneState->Visable);
    if(Status != STATUS_SUCCESS){
        LouPrint("DRSDCORE.SYS:DrsdAtomicHelperCheckPlaneState():ERROR Unable To Set Visability\n");
        return Status;
    }

    DrsdRectRotateInv(Source, FrameBuffer->Width << 16, FrameBuffer->Height << 16, Rotation);

    if(!PlaneState->Visable){
        return STATUS_SUCCESS;
    }

    if((!CanPosition) && (DrsdRectEquals(Destination, &Clip))){
        LouPrint("DRSDCORE.SYS:DrsdAtomicHelperCheckPlaneState():ERROR Plane Must Cover Entire CRTC\n");
        return STATUS_INVALID_PARAMETER;
    } 
    return STATUS_SUCCESS;
}


DRIVER_EXPORT
LOUSTATUS 
DrsdAtomicHelperUpdatePlane(
    PDRSD_PLANE                     Plane,
    PDRSD_CRTC                      Crtc,
    PDRSD_FRAME_BUFFER              FrameBuffer,
    int                             CrtcX, 
    int                             CrtcY, 
    int                             CrtcWidth, 
    int                             CrtcHeight,
    uint32_t                        SourceX, 
    uint32_t                        SourceY, 
    uint32_t                        SourceWidth, 
    uint32_t                        SourceHeight,
    PDRSD_MODESET_ACQUIRE_CONTEXT   Context
){
    PDRSD_ATOMIC_STATE  State;
    PDRSD_PLANE_STATE   PlaneState;
    LOUSTATUS Status =  STATUS_SUCCESS; 
 
    State = DrsdAtomicStateAllocate(Plane->Device);
    if(!State){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    State->AcquireContext = Context;
    PlaneState = DrsdAtomicGetPlaneState(State, Plane);
    if(IS_LOU_KE_PTR_ERROR(PlaneState)){
        Status = LOU_KE_PTR_ERROR(PlaneState);
        goto _FAIL;
    }

    Status = DrsdAtomicSetCrtcForPlane(PlaneState, Crtc);
    if(Status != STATUS_SUCCESS){
        goto _FAIL;
    }

    DrsdAtomicSetFbForPlane(PlaneState, FrameBuffer);
    PlaneState->CrtcX = CrtcX;
    PlaneState->CrtcY = CrtcY;
    PlaneState->CrtcWidth = CrtcWidth;
    PlaneState->CrtcHeight = CrtcHeight;
    PlaneState->SourceX = SourceX;
    PlaneState->SourceY = SourceY;
    PlaneState->SourceWidth = SourceWidth;
    PlaneState->SourceHeight = SourceHeight;

    if(Plane == Crtc->Cursor){
        State->LegacyCursorUpdate = true;
    }

    Status = DrsdAtomicCommit(State);

_FAIL:
    DrsdAtomicStatePut(State);
    return Status;
}

DRIVER_EXPORT 
LOUSTATUS
__DrsdAtomicHelperDisablePlane(
    PDRSD_PLANE             Plane,
    PDRSD_PLANE_STATE       PlaneState
){
    LOUSTATUS Status = DrsdAtomicSetCrtcForPlane(PlaneState, 0x00);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    DrsdAtomicSetFbForPlane(PlaneState, 0x00);
    PlaneState->CrtcX = 0;
    PlaneState->CrtcY = 0;
    PlaneState->CrtcWidth = 0;
    PlaneState->CrtcHeight = 0;
    PlaneState->SourceX = 0;
    PlaneState->SourceY = 0;
    PlaneState->SourceWidth = 0;
    PlaneState->SourceHeight = 0;

    return STATUS_SUCCESS;
}

DRIVER_EXPORT
LOUSTATUS 
DrsdAtomicHelperDisablePlane(
    PDRSD_PLANE                     Plane,
    PDRSD_MODESET_ACQUIRE_CONTEXT   Context            
){
    PDRSD_ATOMIC_STATE  State;
    PDRSD_PLANE_STATE   PlaneState;
    LOUSTATUS           Status = STATUS_SUCCESS;

    State = DrsdAtomicStateAllocate(Plane->Device);
    if(!State){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    State->AcquireContext = Context;
    PlaneState = DrsdAtomicGetPlaneState(State, Plane);
    if(IS_LOU_KE_PTR_ERROR(PlaneState)){
        Status = LOU_KE_PTR_ERROR(PlaneState);
        goto _FAIL;
    }

    if(PlaneState->Crtc && PlaneState->Crtc->Cursor == Plane){
        State->LegacyCursorUpdate = true;
    }

    Status = __DrsdAtomicHelperDisablePlane(Plane, PlaneState);
    if(Status != STATUS_SUCCESS){
        goto _FAIL;
    }

    Status = DrsdAtomicCommit(State);

_FAIL:
    DrsdAtomicStatePut(State);
    return Status;
}