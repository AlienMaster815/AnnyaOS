#include <LouDDK.h>
#include "Radeon.h"
#include "rs600d.h"

uint32_t RS780McReadRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register
){
    LouKIRQL Irql;
    uint32_t Result;
    LouKeAcquireSpinLock(&RDEV->McIdxLock, &Irql);
    WREG32(R_0028F8_MC_INDEX, S_0028F8_MC_ADDRESS(Register));
    Result = RREG32(R_0028F8_MC_INDEX);
    WREG32(R_0028F8_MC_INDEX, ~C_0028F8_MC_ADDRESS);
    LouKeReleaseSpinLock(&RDEV->McIdxLock, &Irql);
    return Result;
}

void RS780McWriteRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register,
    uint32_t Value
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&RDEV->McIdxLock, &Irql);
    WREG32(R_0028F8_MC_INDEX, S_0028F8_MC_ADDRESS(Register) | S_0028F8_MC_INDEX_WR_EN(1));
    WREG32(R_0028FC_MC_DATA, Value);
    WREG32(R_0028F8_MC_INDEX, 0x7F);
    LouKeReleaseSpinLock(&RDEV->McIdxLock, &Irql);
}