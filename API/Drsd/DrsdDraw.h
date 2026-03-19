#ifndef _DRSD_DRAW_H
#define _DRSD_DRAW_H 

#include "DrsdCore.h"

static inline BOOLEAN DrsdDrawIsPixelFg(
    UINT8* SBuf8, 
    UINT SPitch, 
    int X, 
    int Y 
){
    return (SBuf8[(Y * SPitch) + X / 8] & (0x80 >> (X % 8))) != 0;
}

DRIVER_EXPORT 
BOOLEAN
DrsdDrawCanConvertFromXrgb8888(
    UINT32 Format
);

DRIVER_EXPORT
UINT32 
DrsdDrawColorFromXrgb8888(
    UINT32 Color,
    UINT32 Format
);

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
);

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
);

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
);

DRIVER_EXPORT
void 
DrsdDrawFill16(
    PIO_MAP_OBJECT  IoMap,
    UINT            DPitch,
    UINT            Height,
    UINT            Width,
    UINT16          Color
);

DRIVER_EXPORT
void 
DrsdDrawFill24(
    PIO_MAP_OBJECT  IoMap,
    UINT            DPitch,
    UINT            Height,
    UINT            Width,
    UINT32          Color
);

DRIVER_EXPORT
void 
DrsdDrawFill32(
    PIO_MAP_OBJECT  IoMap,
    UINT            DPitch,
    UINT            Height,
    UINT            Width,
    UINT32          Color
);

#endif