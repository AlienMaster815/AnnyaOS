#include <LouDDK.h>
#include "Radeon.h"
#include "../AmdGpuBasic.h"

uint32_t RadeonInvalidRR(PRADEON_DEVICE RDEV, uint32_t Register){

    return 0;
}

void RadeonInvalidWR(PRADEON_DEVICE RDEV, uint32_t Register, uint32_t Value){

}

void R420McWriteRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register,
    uint32_t Value
);

uint32_t R420McReadRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register
);

uint32_t R100PllReadRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register
);

void R100PllWriteRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register,
    uint32_t Value
);

uint32_t R515McReadRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register
);

void R515McWriteRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register,
    uint32_t Value
);

void RS400McWriteRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register,
    uint32_t Value
);

uint32_t RS400McReadRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register
);

uint32_t RS690McReadRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register
);

void RS690McWriteRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register,
    uint32_t Value
);

uint32_t RS600McReadRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register
);

void RS600McWriteRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register,
    uint32_t Value
);

void RS600McWriteRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register,
    uint32_t Value
);

uint32_t RS600McReadRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register
);

uint32_t RS780McReadRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register
);

void RS780McWriteRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register,
    uint32_t Value
);

uint32_t RS600PciepReadRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register
);

void RS600PciepWriteRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register,
    uint32_t Value
);

void CikPciepWriteRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register,
    uint32_t Value
);

uint32_t CikPciepReadRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register
);

void RadeonRegisterAccessorInitialize(
    PRADEON_DEVICE RDEV
){
    RDEV->McReadRegister = RadeonInvalidRR;
    RDEV->McWriteRegister = RadeonInvalidWR;
    RDEV->PllReadRegister = RadeonInvalidRR;
    RDEV->PllWriteRegister = RadeonInvalidWR;
    RDEV->PciepReadRegister = RadeonInvalidRR;
    RDEV->PciepWriteRegister = RadeonInvalidWR;

    if(RDEV->Family < CHIP_RV515){
        RDEV->PcieRegisterMask = 0xFF;
    }else {
        RDEV->PcieRegisterMask = 0x7FF;
    }

    if(RDEV->Family <= CHIP_R580){
        RDEV->PllReadRegister = R100PllReadRegister;
        RDEV->PllWriteRegister = R100PllWriteRegister;
        LouPrint("CHIP_R580\n");
    }
    if(RDEV->Family >= CHIP_R420){
        RDEV->McReadRegister = R420McReadRegister;
        RDEV->McWriteRegister = R420McWriteRegister;
        LouPrint("CHIP_R420\n");
    }
    if(RDEV->Family >= CHIP_RV515){
        RDEV->McReadRegister = R515McReadRegister;
        RDEV->McWriteRegister = R515McWriteRegister;
        LouPrint("CHIP_RV515\n");
    }
    if((RDEV->Family == CHIP_RS400) || (RDEV->Family == CHIP_RS480)){
        RDEV->McReadRegister = RS400McReadRegister;
        RDEV->McWriteRegister = RS400McWriteRegister;
        LouPrint("CHIP_RS400 || CHIP_RS480\n");
    }
    if((RDEV->Family == CHIP_RS690) || (RDEV->Family == CHIP_RS740)){
        RDEV->McReadRegister = RS690McReadRegister;
        RDEV->McWriteRegister = RS690McWriteRegister;
        LouPrint("CHIP_RS690 || CHIP_RS740\n");
    }
    if(RDEV->Family == CHIP_RS600){
        RDEV->McReadRegister = RS600McReadRegister;
        RDEV->McWriteRegister = RS600McWriteRegister;
        LouPrint("CHIP_RS600\n");
    }
    if((RDEV->Family == CHIP_RS780) || (RDEV->Family == CHIP_RS880)){
        RDEV->McReadRegister = RS780McReadRegister;
        RDEV->McWriteRegister = RS780McWriteRegister;
        LouPrint("CHIP_RS780 || CHIP_RS880\n");
    }

    if(RDEV->Family >= CHIP_BONAIRE){

        LouPrint("CHIP_BONAIRE\n");
    }
    else if(RDEV->Family >= CHIP_RS600){

        LouPrint("CHIP_RS600\n");
    }

}


//R100 Specific
void R100DeInitialize(PRADEON_DEVICE RDEV);
LOUSTATUS R100Initialize(PRADEON_DEVICE RDEV);
LOUSTATUS R100Suspend(PRADEON_DEVICE RDEV);
LOUSTATUS R100Resume(PRADEON_DEVICE RDEV);
void R100VgaSetState(PRADEON_DEVICE RDEV, bool State);
LOUSTATUS R100AsicReset(PRADEON_DEVICE RDEV, bool HardReset);
bool R100GuiIdle(PRADEON_DEVICE RDEV);
LOUSTATUS R100McWaitForIdle(PRADEON_DEVICE RDEV);

void RS400DeInitialize(PRADEON_DEVICE RDEV);
LOUSTATUS RS400Initialize(PRADEON_DEVICE RDEV);
LOUSTATUS RS400Suspend(PRADEON_DEVICE RDEV);
LOUSTATUS RS400Resume(PRADEON_DEVICE RDEV);
void RS400VgaSetState(PRADEON_DEVICE RDEV, bool State);
LOUSTATUS R300AsicReset(PRADEON_DEVICE RDEV, bool HardReset);
bool RS400GuiIdle(PRADEON_DEVICE RDEV);
LOUSTATUS RS400McWaitForIdle(PRADEON_DEVICE RDEV);
void RS400TlbFlush(PRADEON_DEVICE RDEV);
uint64_t RS400GetPageEntry(uint64_t Address, uint32_t Flags);
void RS400SetPage(PRADEON_DEVICE RDEV, uint64_t i, uint64_t Entry);
LOUSTATUS R100IrqProcess(PRADEON_DEVICE RDEV);
LOUSTATUS R100IrqSet(PRADEON_DEVICE RDEV);
void R100BandwithUpdate(PRADEON_DEVICE RDEV);
uint32_t R100GetVblankCounter(PDrsdCrtc Crtc);
void R100WaitForVblank(PDrsdDevice Dev);
void RadeonLegacySetBackLightLevel(PRADEON_ENCODER Encoder, uint8_t Level);
uint8_t RadeonLegacyGetBackLightLevel(PRADEON_ENCODER Encoder);
PRADEON_FENCE R100CopyBlit(
    PRADEON_DEVICE RDEV, 
    uint64_t Src,
    uint64_t Dst,
    uint64_t NumberOfGpuPages
);
PRADEON_FENCE R200CopyDma(
    PRADEON_DEVICE RDEV, 
    uint64_t Src,
    uint64_t Dst,
    uint64_t NumberOfGpuPages
);
LOUSTATUS R100SetRegister(
    PRADEON_DEVICE RDEV, 
    int Register, 
    uint32_t TillingFlags, 
    uint32_t Pitch, 
    uint32_t Offset, 
    uint32_t ObjSize
);
void R100ClearRegister(PRADEON_DEVICE RDEV, int Register);

void R100Miscilanious(PRADEON_DEVICE RDEV);
void R100Prepare(PRADEON_DEVICE RDEV);
void R100PmDeInitialize(PRADEON_DEVICE RDEV);
void R100InitializeProfile(PRADEON_DEVICE RDEV);
void R100GetDynamicPowerManagementState(PRADEON_DEVICE RDEV);
uint32_t RadeonLegacyGetEngineClock(PRADEON_DEVICE RDEV);
void RadeonLegacySetEngineClock(struct _RADEON_DEVICE* RDEV, uint32_t Clock);
uint32_t RadeonLegacyGetMemoryClock(struct _RADEON_DEVICE* RDEV);
void R100PageFlip(struct _RADEON_DEVICE* RDEV, int Crtc, uint64_t CrtcBase, bool ASYNC);
void R100PageFlipPending(struct _RADEON_DEVICE* RDEV, int Crtc);
void RadeonLegacySetClockGating(struct _RADEON_DEVICE* RDEV, int Enable);

void RegisterR100AsicDriverHandlers(
    PRADEON_ASIC_DRIVER_HANDLER Asic
){

    Asic->InitializationHandler = R100Initialize;
    Asic->DeInitializationHandler = R100DeInitialize;
    Asic->SuspendHandler = R100Suspend;
    Asic->ResumeHandler = R100Resume;
    Asic->VgaSetStateHandler = R100VgaSetState;
    Asic->AsicResetHandler = R100AsicReset;
    Asic->McWaitForIdle = R100McWaitForIdle;

}

//ENDOF R100 Specific

void RegisterRS400AsicDriverHandlers(
    PRADEON_ASIC_DRIVER_HANDLER Asic
){
    
    Asic->InitializationHandler = RS400Initialize;
    Asic->DeInitializationHandler = RS400DeInitialize;
    Asic->SuspendHandler = RS400Suspend;
    Asic->ResumeHandler = RS400Resume;
    Asic->VgaSetStateHandler = R100VgaSetState;
    Asic->AsicResetHandler = R300AsicReset;
    Asic->GuiIdleHandler = R100GuiIdle;
    Asic->McWaitForIdle = RS400McWaitForIdle;

    Asic->GartHandler.TlbFlush = RS400TlbFlush;
    Asic->GartHandler.GetPageEntry = RS400GetPageEntry;
    Asic->GartHandler.SetPage = RS400SetPage;

    //Asic->RingsHandler.Ring[RADEON_RING_TYPE_GFX_INDEX] = 

    Asic->InterruptStructure.Set = R100IrqSet;
    Asic->InterruptStructure.Process = R100IrqProcess;

    Asic->DisplayHandlers.BandwithUpdate = R100BandwithUpdate;
    Asic->DisplayHandlers.GetVblankCounter = R100GetVblankCounter;
    Asic->DisplayHandlers.SetBackLightLevel = RadeonLegacySetBackLightLevel;
    Asic->DisplayHandlers.GetBackLightLevel = RadeonLegacyGetBackLightLevel;

    Asic->CopyHandlers.Blit = R100CopyBlit;
    Asic->CopyHandlers.BlitIndex = RADEON_RING_TYPE_GFX_INDEX;
    Asic->CopyHandlers.Dma = R200CopyDma;
    Asic->CopyHandlers.DmaIndex = RADEON_RING_TYPE_GFX_INDEX;
    Asic->CopyHandlers.Copy = R100CopyBlit;
    Asic->CopyHandlers.CopyIndex = RADEON_RING_TYPE_GFX_INDEX;

    Asic->Surface.SetRegister = R100SetRegister;
    Asic->Surface.ClearRegister = R100ClearRegister;

    Asic->PowerManagement.Miscilanious = R100Miscilanious;
    Asic->PowerManagement.Prepare = R100Prepare;
    Asic->PowerManagement.DeInitialize = R100PmDeInitialize;
    Asic->PowerManagement.InitializeProfile = R100InitializeProfile;
    Asic->PowerManagement.GetDynamicPowerManagementState = R100GetDynamicPowerManagementState;
    Asic->PowerManagement.GetEngineClock = RadeonLegacyGetEngineClock;
    Asic->PowerManagement.SetEngineClock = RadeonLegacySetEngineClock;
    Asic->PowerManagement.GetMemoryClock = RadeonLegacyGetMemoryClock;
    Asic->PowerManagement.SetClockGating = RadeonLegacySetClockGating;

    Asic->FlipHandlers.PageFlip = R100PageFlip;
    Asic->FlipHandlers.PageFlipPending = R100PageFlipPending;

}


LOUSTATUS RadeonInitializeAsic(
    PRADEON_DEVICE RDEV
){
    LOUSTATUS Status = STATUS_SUCCESS;
    RadeonRegisterAccessorInitialize(RDEV);

    if(RDEV->RadeonFlags & RADEON_SINGLE_CRTC){
        RDEV->NumberOfCrts = 1;
        LouPrint("Single CRTC Device\n");
    }else {
        RDEV->NumberOfCrts = 2;
        LouPrint("Multi CRTC Device\n");
    }

    RDEV->HasUvd = false;
    RDEV->HasVce = false; 

    switch(RDEV->Family){
        case CHIP_R100:
        case CHIP_RV100:
        case CHIP_RS100:
        case CHIP_RV200:
        case CHIP_RS200:
            LouPrint("Using R100Asic Driver\n");
            RegisterR100AsicDriverHandlers(&RDEV->AsicHandlers);
            break;
        case CHIP_RS400:
        case CHIP_RS480:
            LouPrint("Using RS400 Asic Driver\n");
            RegisterRS400AsicDriverHandlers(&RDEV->AsicHandlers);
            break;
        default:
            break;
    }

    if(RDEV->RadeonFlags & RADEON_IS_IGP){
        RDEV->AsicHandlers.PowerManagement.GetMemoryClock = 0x00;
        RDEV->AsicHandlers.PowerManagement.SetMemoryClock = 0x00;
    }

    return Status;
}