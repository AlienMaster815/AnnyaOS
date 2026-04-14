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
        PDRSD_CONNECTOR_ASSIST_FUNCTIONS Functions = Connector->AssistFunctions;
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

    if(!Encoder){
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
        if(LOU_KE_PTR_ERROR(NewConnectorState)){
            Status = (LOUSTATUS)(UINTPTR)NewConnectorState;
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