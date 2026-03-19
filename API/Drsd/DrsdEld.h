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

#ifndef _DRSD_ELD_H
#define _DRSD_ELD_H

#include "DrsdCore.h"

#define DRSD_ELD_SAD_COUNT          5
#define DRSD_ELD_SAD_COUNT_SHIFT    4
#define DRSD_ELD_SAD_COUNT_MASK     (0x0F << DRSD_ELD_SAD_COUNT_SHIFT)

#define DRSD_ELD_CEA_SAD(Mnl, Sad)  (20 + (Mnl) + 3 * (Sad))

#define DRSD_ELD_CEA_EDID_VER_MNL   4
#define DRSD_ELD_MNL_SHIFT          0
#define DRSD_ELD_MNL_MASK           (0x1F << DRSD_ELD_MNL_SHIFT)

static inline int DrsdEldMnl(UINT8* Eld){
    return (Eld[DRSD_ELD_CEA_EDID_VER_MNL] & DRSD_ELD_MNL_MASK) >> DRSD_ELD_MNL_SHIFT;
}

static inline int DrsdEldSadCount(UINT8* Eld){
    return (Eld[DRSD_ELD_SAD_COUNT] & DRSD_ELD_SAD_COUNT_MASK) >> DRSD_ELD_SAD_COUNT_SHIFT;
}

#endif