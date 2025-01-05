#include <LouDDK.h>
#include "Radeon.h"

#define R_000078_MC_INDEX   0x000078
#define S_000078_MC_IND_ADDR(x) (((x) & 0x1FF) << 0)
#define G_000078_MC_IND_ADDR(x) (((x) >> 0) & 0x1FF)
#define C_000078_MC_IND_ADDR    0xFFFFFE00
#define C_000078MC_INDEX_ADDRESS 0xFFFFFE00
#define R_00007C_MC_DATA    0x00007C
#define S_000078_MC_IND_ADDR(x) (((x) & 0x1FF) << 0)
#define S_000078_MC_INDEX(x) (((x) & 0x1FF) << 0)
#define S_000078_MC_IND_WR_EN(x)                     (((x) & 0x1) << 9)

uint32_t RS690McReadRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register
){
    LouKIRQL Irql;
    uint32_t Result;
    LouKeAcquireSpinLock(&RDEV->McIdxLock, &Irql);
    WREG32(R_000078_MC_INDEX, S_000078_MC_INDEX(Register));
    Result = RREG32(R_00007C_MC_DATA);
    WREG32(R_000078_MC_INDEX, ~C_000078MC_INDEX_ADDRESS);
    LouKeReleaseSpinLock(&RDEV->McIdxLock, &Irql);
    return Result;
}

void RS690McWriteRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register,
    uint32_t Value
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&RDEV->McIdxLock, &Irql);
    WREG32(R_000078_MC_INDEX, S_000078_MC_INDEX(Register) | S_000078_MC_IND_WR_EN(1));
	WREG32(R_00007C_MC_DATA, Value);
	WREG32(R_000078_MC_INDEX, 0x7F);
    LouKeReleaseSpinLock(&RDEV->McIdxLock, &Irql);
}