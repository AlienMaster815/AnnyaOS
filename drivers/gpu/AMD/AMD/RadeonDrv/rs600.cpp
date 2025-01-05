#include <LouDDK.h>
#include "Radeon.h"
#include "rs600d.h"

uint32_t RS600McReadRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register
){
    LouKIRQL Irql;
    uint32_t Result;
    LouKeAcquireSpinLock(&RDEV->McIdxLock, &Irql);
    WREG32(R_000070_MC_INDEX, S_000070_MC_ADDRESS(Register) | S_000070_MC_INDEX_CITF_ARB0(1));
    Result = RREG32(R_000074_MC_INDEX_DATA);
    LouKeReleaseSpinLock(&RDEV->McIdxLock, &Irql);
    return Result;
}

void RS600McWriteRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register,
    uint32_t Value
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&RDEV->McIdxLock, &Irql);
    WREG32(R_000070_MC_INDEX, S_000070_MC_ADDRESS(Register) | S_000070_MC_INDEX_CITF_ARB0(1) | S_000074_MC_INDEX_WR_EN(1));
    WREG32(R_000074_MC_INDEX_DATA, Value);
    LouKeReleaseSpinLock(&RDEV->McIdxLock, &Irql);
}

#define PCIE_INDEX  				0x38
#define PCIE_DATA  					0x3C

uint32_t RS600PciepReadRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register
){
    LouKIRQL Irql;
    uint32_t Result;
    LouKeAcquireSpinLock(&RDEV->McIdxLock, &Irql);
    WREG32(PCIE_INDEX, (Register) & 0xFF);
    RREG32(PCIE_INDEX);
    Result = RREG32(PCIE_DATA);
    LouKeReleaseSpinLock(&RDEV->McIdxLock, &Irql);
    return Result;
}

void RS600PciepWriteRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register,
    uint32_t Value
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&RDEV->McIdxLock, &Irql);
    WREG32(PCIE_INDEX, (Register) & 0xFF);
    RREG32(PCIE_INDEX);
    WREG32(PCIE_DATA, Value);
    RREG32(PCIE_DATA);
    LouKeReleaseSpinLock(&RDEV->McIdxLock, &Irql);
}