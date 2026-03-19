#ifndef _DRSD_FORMAT_INTERNAL_H
#define _DRSD_FORMAT_INTERNAL_H

#include "DrsdCore.h"

static inline UINT32 DrsdPixelXrgb8888ToR8Bt601(UINT32 Pixel){
    UINT32 R = (Pixel & 0x00FF0000) >> 16;
    UINT32 G = (Pixel & 0x0000FF00) >> 8;
    UINT32 B = (Pixel & 0x000000FF);

    return (77 * R + 150 * G + 29 * B) / 256;
}   

static inline UINT32 DrsdPixelXrgb8888ToRgb332(UINT32 Pixel){
    return  ((Pixel & 0x00E00000) >> 16) | 
            ((Pixel & 0x0000E000) >> 11) |
            ((Pixel & 0x000000C0) >> 6);
}

static inline UINT32 DrsdPixelXrgb8888ToRgb565(UINT32 Pixel){
    return  ((Pixel & 0x00F80000) >> 8) | 
            ((Pixel & 0x0000FC00) >> 5) | 
            ((Pixel & 0x000000F8) >> 3);
}

static inline UINT32 DrsdPixelXrgb8888ToRgb565Be(UINT32 Pixel){
    UINT32 Result;
    Pixel = DrsdPixelXrgb8888ToRgb565(Pixel);
    LouKeSwapEndianess(
        &Pixel,
        &Result,
        sizeof(UINT16)
    );
    return Result;
}

static inline UINT32 DrsdPixelXrgb8888ToRgbx5551(UINT32 Pixel){
    return  ((Pixel & 0x00F80000) >> 8) |
            ((Pixel & 0x0000F800) >> 5) |
            ((Pixel & 0x000000F8));
}

static inline UINT32 DrsdPixelXrgb8888ToRgba5551(UINT32 Pixel){
    return DrsdPixelXrgb8888ToRgbx5551(Pixel) | (1 << 0);
}

static inline UINT32 DrsdPixelXrgb8888ToXrgb1555(UINT32 Pixel){
    return  ((Pixel & 0x00F80000) >> 9) | 
            ((Pixel & 0x0000F800) >> 6) |
            ((Pixel & 0x000000F8) >> 3);
}

static inline UINT32 DrsdPixelXrgb8888ToArgb1555(UINT32 Pixel){
    return (1 << 15) | DrsdPixelXrgb8888ToXrgb1555(Pixel);
}

static inline UINT32 DrsdPixelXrgb8888ToRgb888(UINT32 Pixel){
    return Pixel & 0x00FFFFFF;
}

static inline UINT32 DrsdPixelXrgb8888ToBgr888(UINT32 Pixel){
    return  ((Pixel & 0x00FF0000) >> 16) |
	        ((Pixel & 0x0000FF00)) |
	        ((Pixel & 0x000000FF) << 16);
}

static inline UINT32 DrsdPixelXrgb8888ToArgb8888(UINT32 Pixel){
    return Pixel | 0xFF000000;
}

static inline UINT32 DrsdPixelXrgb8888ToXbgr8888(UINT32 Pixel){
	return ((Pixel & 0xFF000000)) |
	       ((Pixel & 0x00FF0000) >> 16) |
	       ((Pixel & 0x0000FF00)) |
	       ((Pixel & 0x000000FF) << 16);
}

static inline UINT32 DrsdPixelXrgb8888ToBgrx8888(UINT32 Pixel){
    return  ((Pixel & 0xFF000000) >> 24) |
	        ((Pixel & 0x00FF0000) >> 8) |
	        ((Pixel & 0x0000FF00) << 8) |
	        ((Pixel & 0x000000FF) << 24);
}
    
static inline UINT32 DrsdPixelXrgb8888ToAbgr8888(UINT32 Pixel){
    return 0xFF000000 | DrsdPixelXrgb8888ToXbgr8888(Pixel); 
}

static inline UINT32 DrsdPixelXrgb8888ToXrgb2101010(UINT32 Pixel){
	Pixel = ((Pixel & 0x000000FF) << 2) |
	      ((Pixel & 0x0000FF00) << 4) |
	      ((Pixel & 0x00FF0000) << 6);
	return  Pixel | ((Pixel >> 8) & 0x00300C03);
}

static inline UINT32 DrsdPixelXrgb8888ToArgb2101010(UINT32 Pixel){
    return (0b11 << 30) | DrsdPixelXrgb8888ToXrgb2101010(Pixel);
}

static inline UINT32 DrsdPixelXrgb8888ToXbgr2101010(UINT32 Pixel){
	Pixel = ((Pixel & 0x00FF0000) >> 14) |
	        ((Pixel & 0x0000FF00) << 4) |
	        ((Pixel & 0x000000FF) << 22);
	return  Pixel | ((Pixel >> 8) & 0x00300C03);
}

static inline UINT32 DrsdPixelXrgb8888ToAbgr2101010(UINT32 Pixel){
    return (0b11 << 30) | DrsdPixelXrgb8888ToXbgr2101010(Pixel);
}

static inline UINT32 DrsdPixelArgb8888ToArgb4444(UINT32 Pixel){
    return  ((Pixel & 0xF0000000) >> 16) |
            ((Pixel & 0x00F00000) >> 12) |
            ((Pixel & 0x0000F000) >> 8)  |
            ((Pixel & 0x000000F0) >> 4);
}

#endif