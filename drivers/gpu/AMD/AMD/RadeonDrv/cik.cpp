#include <LouDDK.h>
#include "Radeon.h"

#define PCIE_INDEX  				0x38
#define PCIE_DATA  					0x3C

uint32_t CikPciepReadRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register
){
    LouKIRQL Irql;
    uint32_t Result;
    LouKeAcquireSpinLock(&RDEV->PciepIdxLock, &Irql);
    WREG32(PCIE_INDEX, Register);
    RREG32(PCIE_INDEX);
    Result = RREG32(PCIE_DATA);
    LouKeReleaseSpinLock(&RDEV->PciepIdxLock, &Irql);
    return Result;
}

void CikPciepWriteRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register,
    uint32_t Value
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&RDEV->PciepIdxLock, &Irql);
    WREG32(PCIE_INDEX, Register);
    RREG32(PCIE_INDEX);
    WREG32(PCIE_DATA, Value);
    RREG32(PCIE_DATA);
    LouKeReleaseSpinLock(&RDEV->PciepIdxLock, &Irql);
}