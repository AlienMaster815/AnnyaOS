#include <LouDDK.h>
#include "Radeon.h"
#include "r420.h"

uint32_t R420McReadRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register
){
    LouKIRQL Irql;
    uint32_t Result;
    LouKeAcquireSpinLock(&RDEV->McIdxLock, &Irql);
    WREG32(R_000lF8_MC_INDEX, S_0001F8_MC_INDEX_ADDRESS(Register));
    Result = RREG32(R_0001FC_MC_INDEX_DATA);
    LouKeReleaseSpinLock(&RDEV->McIdxLock, &Irql);
    return Result;
}

void R420McWriteRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register,
    uint32_t Value
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&RDEV->McIdxLock, &Irql);
    WREG32(R_000lF8_MC_INDEX, S_0001F8_MC_INDEX_ADDRESS(Register) | S_0001F8_MC_INDEX_WR_ENNABLE(1));
    WREG32(R_0001FC_MC_INDEX_DATA, Value);
    LouKeReleaseSpinLock(&RDEV->McIdxLock, &Irql);
}