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

void DrsdEdidCtaSadGet(
    PCEA_SAD    CtaSad, 
    UINT8*      Sad
){

    Sad[0] = CtaSad->Format << 3 | CtaSad->Channels;
    Sad[1] = CtaSad->Frequency;
    Sad[2] = CtaSad->Byte2;

}

void DrsdEdidCtaSadSet(
    PCEA_SAD    CtaSad, 
    UINT8*      Sad
){

	CtaSad->Format = (Sad[0] & 0x78) >> 3;
	CtaSad->Channels = Sad[0] & 0x07;
	CtaSad->Frequency = Sad[1] & 0x7F;
	CtaSad->Byte2 = Sad[2];

}