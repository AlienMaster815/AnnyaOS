#include "Radeon.h"
#include <LouDDK.h>

uint32_t R515McReadRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register
){
    LouKIRQL Irql;
    uint32_t Result;
    LouKeAcquireSpinLock(&RDEV->McIdxLock, &Irql);
    WREG32(MC_INDEX, 0x7F0000 | (Register & 0xFFFF));
    Result = RREG32(MC_INDEX_DATA);
    WREG32(MC_INDEX, 0);
    LouKeReleaseSpinLock(&RDEV->McIdxLock, &Irql);
    return Result;
}

void R515McWriteRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register,
    uint32_t Value
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&RDEV->McIdxLock, &Irql);
    WREG32(MC_INDEX, 0xFF0000 | ((Register) & 0xFFFF));
    WREG32(MC_INDEX_DATA, (Value));
    WREG32(MC_INDEX, 0);
    LouKeReleaseSpinLock(&RDEV->McIdxLock, &Irql);
}