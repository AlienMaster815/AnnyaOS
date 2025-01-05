#include <LouDDK.h>
#include "Radeon.h"

void RadeonScratchInitialize(
    PRADEON_DEVICE RDEV
){
    uint16_t i;
    uint16_t e;

    if(RDEV->Family < CHIP_R300){
        RDEV->Scratch.RegisterCount = 5;
        e = 5;
    }else {
        RDEV->Scratch.RegisterCount = 7;
        e = 7;
    }
    RDEV->Scratch.RegisterBase = RADEON_SCRATCH_REGISTER0;
    for(i = 00; i < e; i++){
        RDEV->Scratch.Free[i] = true;
        RDEV->Scratch.Register[i] = RADEON_SCRATCH_REGISTER0 + (i * 4);
    }

}

void RadeonSurfaceInitialize(PRADEON_DEVICE RDEV) {
    if (RDEV->Family < CHIP_R600) {
        for (uint16_t i = 0; i < RADEON_GEM_MAX_SURFACES; i++) {
            RADEON_CLEAR_SURFACE_REGISTER(RDEV, i);
        }
        WREG32(RADEON_SURFACE_CONTROL, 0);
    }
}