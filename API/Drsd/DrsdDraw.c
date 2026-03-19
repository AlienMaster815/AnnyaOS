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
BOOLEAN
DrsdDrawCanConvertFromXrgb8888(
    UINT32 Format
){

    switch(Format){

        case DRSD_COLOR_FORMAT_RGB565:
        case DRSD_COLOR_FORMAT_RGBA5551:
        case DRSD_COLOR_FORMAT_XRGB1555:
        case DRSD_COLOR_FORMAT_ARGB1555:
        case DRSD_COLOR_FORMAT_RGB888:
        case DRSD_COLOR_FORMAT_XRGB8888:
        case DRSD_COLOR_FORMAT_ARGB8888:
        case DRSD_COLOR_FORMAT_XBGR8888:
        case DRSD_COLOR_FORMAT_ABGR8888:
        case DRSD_COLOR_FORMAT_XRGB2101010:
        case DRSD_COLOR_FORMAT_ARGB2101010:
        case DRSD_COLOR_FORMAT_ABGR2101010:
            return true;

        default:
            return false;
    }  
}

DRIVER_EXPORT
UINT32 
DrsdDrawColorFromXrgb8888(
    UINT32 Color,
    UINT32 Format
){
    switch(Format){
        case DRSD_COLOR_FORMAT_RGB565:  
            return DrsdPixelXrgb8888ToRgb565(Color);
        case DRSD_COLOR_FORMAT_RGBA5551:
            return DrsdPixelXrgb8888ToRgba5551(Color);
        case DRSD_COLOR_FORMAT_XRGB1555:
            return DrsdPixelXrgb8888ToXrgb1555(Color);
        case DRSD_COLOR_FORMAT_ARGB1555:
            return DrsdPixelXrgb8888ToArgb1555(Color);
        case DRSD_COLOR_FORMAT_RGB888:
        case DRSD_COLOR_FORMAT_XRGB8888:
            return Color;
        case DRSD_COLOR_FORMAT_ARGB8888:
            return DrsdPixelXrgb8888ToArgb8888(Color);
        case DRSD_COLOR_FORMAT_XBGR8888:
            return DrsdPixelXrgb8888ToXbgr8888(Color);
        case DRSD_COLOR_FORMAT_ABGR8888:
            return DrsdPixelXrgb8888ToAbgr8888(Color);
        case DRSD_COLOR_FORMAT_XRGB2101010:
            return DrsdPixelXrgb8888ToXrgb2101010(Color);
        case DRSD_COLOR_FORMAT_ARGB2101010:
            return DrsdPixelXrgb8888ToArgb2101010(Color);
        case DRSD_COLOR_FORMAT_ABGR2101010:
            return DrsdPixelXrgb8888ToAbgr2101010(Color);
        default:
            return 0x00;
    }
}

DRIVER_EXPORT 
void 
DrsdDrawBlit16(
    PIO_MAP_OBJECT  IoMap,
    UINT            DPitch,
    UINT8*          SBuf8,
    UINT            SPitch,
    UINT            Height,
    UINT            Width,
    UINT            Scale,
    UINT16          Fg16
){
    for(UINT Y = 0; Y < Height; Y++){
        for(UINT X = 0; X < Width; X++){
            if(DrsdDrawIsPixelFg(SBuf8, SPitch, X / Scale, Y / Scale)){
                LouKeIoObjectWriteIo(IoMap, Y * DPitch + Y * sizeof(UINT16), UINT16, Fg16);
            }
        }
    }
}

DRIVER_EXPORT
void 
DrsdDrawBlit24(
    PIO_MAP_OBJECT  IoMap,
    UINT            DPitch,
    UINT8*          SBuf8,
    UINT            SPitch,
    UINT            Height,
    UINT            Width,
    UINT            Scale, 
    UINT32          Fg32
){
    for(UINT Y = 0; Y < Height; Y++){
        for(UINT X = 0; X < Width; X++){
            SIZE Offset = Y * DPitch + X * 3;
            if(DrsdDrawIsPixelFg(SBuf8, SPitch, X / Scale, Y / Scale)){
                LouKeIoObjectWriteIo(IoMap, Offset, UINT8,      (Fg32 & 0x000000FF));
                LouKeIoObjectWriteIo(IoMap, Offset + 1, UINT8,  (Fg32 & 0x0000FF00) >> 8);
                LouKeIoObjectWriteIo(IoMap, Offset + 2, UINT8,  (Fg32 & 0x00FF0000) >> 16);
            }
        }
    }
}

DRIVER_EXPORT
void 
DrsdDrawBlit32(
    PIO_MAP_OBJECT  IoMap,
    UINT            DPitch,
    UINT8*          SBuf8,
    UINT            SPitch,
    UINT            Height,
    UINT            Width,
    UINT            Scale,
    UINT32          Fg32
){
    for(UINT Y = 0; Y < Height; Y++){
        for(UINT X = 0; X < Width; X++){
            if(DrsdDrawIsPixelFg(SBuf8, SPitch, X / Scale, Y / Scale)){
                LouKeIoObjectWriteIo(IoMap, Y * DPitch + Y * sizeof(UINT32), UINT32, Fg32);
            }
        }
    }
}

DRIVER_EXPORT
void 
DrsdDrawFill16(
    PIO_MAP_OBJECT  IoMap,
    UINT            DPitch,
    UINT            Height,
    UINT            Width,
    UINT16          Color
){  
    for(UINT Y = 0; Y < Height; Y++){
        for(UINT X = 0; X < Width; X++){
            LouKeIoObjectWriteIo(IoMap, Y * DPitch + X * sizeof(UINT16), UINT16, Color);
        }
    }
}

DRIVER_EXPORT
void 
DrsdDrawFill24(
    PIO_MAP_OBJECT  IoMap,
    UINT            DPitch,
    UINT            Height,
    UINT            Width,
    UINT32          Color
){  
    for(UINT Y = 0; Y < Height; Y++){
        for(UINT X = 0; X < Width; X++){
            UINT Offset = Y * DPitch + X * 3;
            LouKeIoObjectWriteIo(IoMap, Offset, UINT8,      (Color & 0x000000FF));
            LouKeIoObjectWriteIo(IoMap, Offset + 1, UINT8,  (Color & 0x0000FF00) >> 0);
            LouKeIoObjectWriteIo(IoMap, Offset + 2, UINT8,  (Color & 0x00FF0000) >> 0);
        }
    }
}

DRIVER_EXPORT
void 
DrsdDrawFill32(
    PIO_MAP_OBJECT  IoMap,
    UINT            DPitch,
    UINT            Height,
    UINT            Width,
    UINT32          Color
){ 
    for(UINT Y = 0; Y < Height; Y++){
        for(UINT X = 0; X < Width; X++){
            LouKeIoObjectWriteIo(IoMap, Y * DPitch + X * sizeof(UINT32), UINT32, Color);
        }
    }
}
