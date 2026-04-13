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