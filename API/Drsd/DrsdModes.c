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
DRSD_MODE_STATUS
DrsdModeValidateBasic(
    PDRSD_DISPLAY_MODE Mode
){
    if(Mode->Type & ~(DRSD_MODE_TYPE_ALL)){
        return DRSD_MODE_BAD;
    }
    if(Mode->Type & ~(DRSD_MODE_FLAG_ALL)){
        return DRSD_MODE_BAD;
    }
    if((Mode->Flags & DRSD_MODE_FLAG_3D_MASK) > DRSD_MODE_FLAG_3D_MAX){
        return DRSD_MODE_BAD;
    }

    if(!Mode->KhzClock){
        return DRSD_MODE_CLOCK_TOO_LOW;
    }

    if(
        (Mode->HorizontalDisplay == 0) ||
        (Mode->HorizontalSyncStart < Mode->HorizontalDisplay) ||
        (Mode->HorizontalSyncStart < Mode->HorizontalSyncStart) ||
        (Mode->HorizontalTotal < Mode->HorizontalSyncEnd)
    ){
        return DRSD_MODE_H_ILLEGAL;
    }
    
    if(
        (Mode->VerticalDisplay == 0) ||
        (Mode->VerticalSyncStart < Mode->VerticalDisplay) ||
        (Mode->VerticalSyncStart < Mode->VerticalSyncStart) ||
        (Mode->VerticalTotal < Mode->VerticalSyncEnd)
    ){
        return DRSD_MODE_V_ILLEGAL;
    }

    return DRSD_MODE_OK;
} 

DRIVER_EXPORT 
DRSD_MODE_STATUS 
DrsdModeValidateDriver(
    PDRSD_DEVICE        Device,
    PDRSD_DISPLAY_MODE  Mode
){
    DRSD_MODE_STATUS Status = DrsdModeValidateBasic(Mode);
    if(Status != DRSD_MODE_OK){
        return Status;
    }

    if(Device->ModeConfig.Functions->ModeValid){
        return Device->ModeConfig.Functions->ModeValid(Device, Mode);
    }

    return DRSD_MODE_OK;
}

DRIVER_EXPORT
void
DrsdModeSetCrtcInfo(
    PDRSD_DISPLAY_MODE  Mode,
    int                 AdjustFlags
){
    if(!Mode){
        return;
    }

    Mode->CrtcClock = Mode->KhzClock;
    Mode->CrtcHorizontalDisplay = Mode->HorizontalDisplay;
    Mode->CrtcHorizontalSyncStart = Mode->HorizontalSyncStart;
    Mode->CrtcHorizontalSyncEnd = Mode->HorizontalSyncEnd;
    Mode->CrtcHorizontalTotal = Mode->HorizontalTotal;
    Mode->CrtcHorizontalSkew = Mode->HorizontalSkew;
    Mode->CrtcVerticalDisplay = Mode->VerticalDisplay;
    Mode->CrtcVerticalSyncStart = Mode->VerticalSyncStart;
    Mode->CrtcVerticalSyncEnd = Mode->VerticalSyncEnd;
    Mode->CrtcVerticalTotal = Mode->VerticalTotal;

    if(Mode->Flags & DRSD_MODE_FLAG_INTERLACE){
        if(AdjustFlags & CRTC_INTERLACE_HALVE_V){
            Mode->CrtcVerticalDisplay /= 2;
            Mode->CrtcVerticalSyncStart /= 2;
            Mode->CrtcVerticalSyncEnd /= 2;
            Mode->CrtcVerticalTotal /= 2;
        }
    }
    
    if(!(AdjustFlags & CRTC_NO_DBLSCAN)){
        if(Mode->Flags & DRSD_MODE_FLAG_DBLSCAN){
            Mode->CrtcVerticalDisplay *= 2;
            Mode->CrtcVerticalSyncStart *= 2;
            Mode->CrtcVerticalSyncEnd *= 2;
            Mode->CrtcVerticalTotal *= 2;
        }
    }
        
    if(!(AdjustFlags & CRTC_NO_VSCAN)){
        if(Mode->VerticalScan > 1){
            Mode->CrtcVerticalDisplay *= Mode->VerticalScan;
            Mode->CrtcVerticalSyncStart *= Mode->VerticalScan;
            Mode->CrtcVerticalSyncEnd *= Mode->VerticalScan;
            Mode->CrtcVerticalTotal *= Mode->VerticalScan;
        }
    }

    if(AdjustFlags & CRTC_STEREO_DOUBLE){
        UINT Layout = Mode->Flags & DRSD_MODE_FLAG_3D_MASK;
        switch(Layout){
            case DRSD_MODE_FLAG_3D_FRAME_PACKING:
                Mode->CrtcClock *= 2;
                Mode->CrtcVerticalDisplay += Mode->VerticalTotal;
                Mode->CrtcVerticalSyncStart += Mode->VerticalTotal;
                Mode->CrtcVerticalSyncEnd += Mode->VerticalTotal;
                Mode->CrtcVerticalTotal += Mode->VerticalTotal;
                break;
        }
    }    

    Mode->CrtcVBlankStart = MIN(Mode->CrtcVerticalSyncStart, Mode->CrtcVerticalDisplay);
    Mode->CrtcVBlankEnd = MAX(Mode->CrtcVerticalSyncEnd, Mode->CrtcVerticalTotal);
    Mode->CrtcHBlankStart = MIN(Mode->CrtcHorizontalSyncStart, Mode->CrtcHorizontalDisplay);
    Mode->CrtcHBlankEnd = MAX(Mode->CrtcHorizontalSyncEnd, Mode->CrtcHorizontalTotal);
}

DRIVER_EXPORT
BOOL DrsdModeParseCommandLineForConnector(
    LOUSTR              ModeOption,
    PDRSD_CONNECTOR     Connector,
    PDRSD_CMDLINE_MODE  Mode
){

    return false;
}

DRIVER_EXPORT
void DrsdModeCopy(
    PDRSD_DISPLAY_MODE Destination, 
    PDRSD_DISPLAY_MODE Source
){
    ListHeader Head = Destination->Head;
    *Destination = *Source;
    Destination->Head = Head;
}

DRIVER_EXPORT 
int 
DrsdModeVRefresh(
    PDRSD_DISPLAY_MODE Mode
){
    UINT Num = 1, Den = 1;

    if((!Mode->HorizontalTotal) || (!Mode->VerticalTotal)){
        return 0;
    }

    if(Mode->Flags & DRSD_MODE_FLAG_INTERLACE){
        Num *= 2;
    }

    if(Mode->Flags & DRSD_MODE_FLAG_DBLSCAN){
        Den *= 2;
    }

    if(Mode->VerticalScan > 1){
        Den *= Mode->VerticalScan;
    }

    if(LouKeRtlUIntMult(Mode->KhzClock, Num, &Num) != STATUS_SUCCESS){
        return 0;
    }

    if(LouKeRtlUIntMult(Mode->HorizontalTotal * Mode->VerticalTotal, Den, &Den) != STATUS_SUCCESS){
        return 0;
    }    
    if(LouKeRtlUIntMult(Num, 1000, &Num) != STATUS_SUCCESS){
        return 0;
    }

    if(!Den){
        return 0;
    }

    return DIVIDE_ROUND_CLOSEST_ULL(Num, Den);

}

void 
DrsdModeConvertToUMode(
    PDRSD_MODE_MODEINFO Out, 
    PDRSD_DISPLAY_MODE  In
){

	Out->Clock = In->KhzClock;
	Out->HorizontalDisplay = In->HorizontalDisplay;
	Out->HSyncStart = In->HorizontalSyncStart;
	Out->HSyncEnd = In->HorizontalSyncEnd;
	Out->HTotal = In->HorizontalTotal;
	Out->HSkew = In->HorizontalSkew;
	Out->VerticalDisplay = In->VerticalDisplay;
	Out->VSyncStart = In->VerticalSyncStart;
	Out->VSyncEnd = In->VerticalSyncEnd;
	Out->VTotal = In->VerticalTotal;
	Out->VScan = In->VerticalScan;
	Out->VRefresh = DrsdModeVRefresh(In);
	Out->Flags = In->Flags;
	Out->Type = In->Type;

	switch (In->AspectRatio) {
	case HDMI_PICTURE_ASPECT_4_3:
		Out->Flags |= DRSD_MODE_FLAG_PIC_AR_4_3;
		break;
	case HDMI_PICTURE_ASPECT_16_9:
		Out->Flags |= DRSD_MODE_FLAG_PIC_AR_16_9;
		break;
	case HDMI_PICTURE_ASPECT_64_27:
		Out->Flags |= DRSD_MODE_FLAG_PIC_AR_64_27;
		break;
	case HDMI_PICTURE_ASPECT_256_135:
		Out->Flags |= DRSD_MODE_FLAG_PIC_AR_256_135;
		break;
	default:
	case HDMI_PICTURE_ASPECT_NONE:
		Out->Flags |= DRSD_MODE_FLAG_PIC_AR_NONE;
		break;
	}
	strncpy(Out->Name, In->Name, sizeof(DRSD_DISPLAY_MODE_LENGTH));
}

DRIVER_EXPORT
LOUSTATUS
DrsdModeConvertUMode(
    PDRSD_DEVICE        Device,
    PDRSD_DISPLAY_MODE  Out,
    PDRSD_MODE_MODEINFO In
){
    if((In->Clock > INT32_MAX) || (In->VRefresh > INT32_MAX)){
        return STATUS_INTEGER_OVERFLOW;
    }

    Out->KhzClock = In->Clock;
    Out->HorizontalDisplay = In->HorizontalDisplay;
    Out->HorizontalSyncStart = In->HSyncStart;
    Out->HorizontalSyncEnd = In->HSyncEnd;
    Out->HorizontalTotal = In->HTotal;
    Out->HorizontalSkew = In->HSkew;
    Out->VerticalDisplay = In->VerticalDisplay;
    Out->VerticalSyncStart = In->VSyncStart;
    Out->VerticalSyncEnd = In->VSyncEnd;
    Out->VerticalTotal = In->VTotal;
    Out->VerticalScan = In->VScan;
    Out->Flags = In->Flags;

    Out->Type = In->Type & DRSD_MODE_TYPE_ALL;
    strncpy(Out->Name, In->Name, sizeof(Out->Name));

    Out->Flags &= ~(DRSD_MODE_FLAG_PIC_AR_MASK); 

	switch (In->Flags & DRSD_MODE_FLAG_PIC_AR_MASK) {
	case DRSD_MODE_FLAG_PIC_AR_4_3:
		Out->Flags |= HDMI_PICTURE_ASPECT_4_3;
		break;
	case DRSD_MODE_FLAG_PIC_AR_16_9:
		Out->Flags |= HDMI_PICTURE_ASPECT_16_9;
		break;
	case DRSD_MODE_FLAG_PIC_AR_64_27:
		Out->Flags |= HDMI_PICTURE_ASPECT_64_27;
		break;
	case DRSD_MODE_FLAG_PIC_AR_256_135:
		Out->Flags |= HDMI_PICTURE_ASPECT_256_135;
		break;
	default:
	case DRSD_MODE_FLAG_PIC_AR_NONE:
		Out->Flags |= HDMI_PICTURE_ASPECT_NONE;
		break;
	}

    Out->ModeStatus = DrsdModeValidateDriver(Device, Out);
    if(Out->ModeStatus != DRSD_MODE_OK){
        return STATUS_INVALID_PARAMETER;
    }

    DrsdModeSetCrtcInfo(Out, CRTC_INTERLACE_HALVE_V);

    return STATUS_SUCCESS;
}

DRIVER_EXPORT
void
DrsdModeInitialize(
    PDRSD_DISPLAY_MODE  Destination,
    PDRSD_DISPLAY_MODE  Source
){  
    memset(Destination, 0, sizeof(DRSD_DISPLAY_MODE));
    DrsdModeCopy(Destination, Source);
}

DRIVER_EXPORT
void 
DrsdModeGetHvTiming(
    PDRSD_DISPLAY_MODE  Mode,
    int*                HDisplay,
    int*                VDisplay
){
    DRSD_DISPLAY_MODE Adjusted;
    DrsdModeInitialize(&Adjusted, Mode);
    DrsdModeSetCrtcInfo(&Adjusted, CRTC_STEREO_DOUBLE_ONLY);
    *HDisplay = Adjusted.CrtcHorizontalDisplay;
    *VDisplay = Adjusted.CrtcVerticalDisplay;
}