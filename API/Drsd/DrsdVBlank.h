#ifndef _DRSD_VBLANK_INTERNAL_H
#define _DRSD_VBLANK_INTERNAL_H

DRIVER_EXPORT 
BOOLEAN
DrsdDeviceHasVBlank(
    PDRSD_DEVICE Device
);

DRIVER_EXPORT
void
DrsdCrtcVBlankReset(
    PDRSD_CRTC  Crtc
);

#endif