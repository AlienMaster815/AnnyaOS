#include "Radeon.h"
#include <LouDDK.h>

#define RS480_NB_MC_INDEX 0x168
#define RS480_NB_MC_IND_WR_EN	(1 << 8)
#define RS480_NB_MC_DATA  0x16c

uint32_t RS400McReadRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register
){
    LouKIRQL Irql;
    uint32_t Result;
    LouKeAcquireSpinLock(&RDEV->McIdxLock, &Irql);
    WREG32(RS480_NB_MC_INDEX,Register & 0xFF);
    Result = RREG32(RS480_NB_MC_DATA);   
    WREG32(RS480_NB_MC_INDEX, 0xFF);
    LouKeReleaseSpinLock(&RDEV->McIdxLock, &Irql);
    return Result;
}

void RS400McWriteRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register,
    uint32_t Value
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&RDEV->McIdxLock, &Irql);
    WREG32(RS480_NB_MC_INDEX, (((Register) & 0xFF) | RS480_NB_MC_IND_WR_EN));
    WREG32(RS480_NB_MC_DATA, (Value));
    WREG32(RS480_NB_MC_INDEX, (Register) & 0xFF);
    LouKeReleaseSpinLock(&RDEV->McIdxLock, &Irql);
}

void R100VgaRenderDisable(PRADEON_DEVICE RDEV);
void RadeonScratchInitialize(
    PRADEON_DEVICE RDEV
);
void RadeonSurfaceInitialize(PRADEON_DEVICE RDEV);
void RestoreR100RegistersToSanityValues(PRADEON_DEVICE RDEV);
bool RadeonGetBios(PRADEON_DEVICE RDEV);


LOUSTATUS RS400Initialize(PRADEON_DEVICE RDEV){
    LOUSTATUS Status = STATUS_SUCCESS;

    //Disable Vga
    LouPrint("R400 Disableing Vga Rendering\n");
    R100VgaRenderDisable(RDEV);
    LouPrint("R400 Rendering Disabled\n");
    //Initialize Scratch Registers
    LouPrint("Initializing Scratch Registers\n");
    RadeonScratchInitialize(RDEV);
    LouPrint("Finished Initializing Scratch Registers\n");
    //Initialize Surface Registers
    LouPrint("Initializing Surface Registers\n");
    RadeonSurfaceInitialize(RDEV);
    LouPrint("Finished Initializing Surface Registers\n");
    //Stet Sanity Values
    LouPrint("Setting Registers To Sane Values\n");
    RestoreR100RegistersToSanityValues(RDEV);
    LouPrint("Finished Setting Registers To Sane Values\n");
    //Get Atom Bios
    LouPrint("Geting Radeon Bios\n");
    RadeonGetBios(RDEV);
    LouPrint("Finished Geting Radeon Bios\n");


    return Status;
}

void RS400DeInitialize(PRADEON_DEVICE RDEV){

}

LOUSTATUS RS400Suspend(PRADEON_DEVICE RDEV){

    return STATUS_SUCCESS;
}

LOUSTATUS RS400Resume(PRADEON_DEVICE RDEV){


    return STATUS_SUCCESS;
}



LOUSTATUS RS400McWaitForIdle(PRADEON_DEVICE RDEV){



    return STATUS_SUCCESS;
}

void RS400TlbFlush(PRADEON_DEVICE RDEV){

}
    
uint64_t RS400GetPageEntry(uint64_t Address, uint32_t Flags){

    return 0;
}
   
void RS400SetPage(PRADEON_DEVICE RDEV, uint64_t i, uint64_t Entry){

}


