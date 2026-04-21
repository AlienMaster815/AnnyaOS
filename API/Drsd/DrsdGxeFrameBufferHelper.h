#ifndef _DRSD_GXE_FRAMEBUFFER_HELPER_H
#define _DRSD_GXE_FRAMEBUFFER_HELPER_H

#include "DrsdCore.h"

DRIVER_EXPORT 
LOUSTATUS
DrsdGxeFbVMap(
    PDRSD_FRAME_BUFFER  FrameBuffer,
    PIO_MAP_OBJECT      Map,
    PIO_MAP_OBJECT      Data
);

#endif