#include <LouDDK.h>
#include "Radeon.h"
#include "r100.h"

static inline 
void R100PllErrataAfterIndex(
    PRADEON_DEVICE RDEV
){

    if(RDEV->PllErrAta & CHIP_ERRATA_PLL_DUMMYREADS){
        RREG32(RADEON_CLOCK_CONTROL_DATA);
        RREG32(RADEON_CRTC_GEN_CONTROL);        
    }

}

static inline
void R100PplErrataAfterData(
    PRADEON_DEVICE RDEV
){

    if(RDEV->PllErrAta & CHIP_ERRATA_PLL_DELAY){
        sleep(5);
    }

    if(RDEV->PllErrAta & CHIP_ERRATA_R300_CG){
        uint32_t Save;
        uint32_t Tmp;

        Save = RREG32(RADEON_CLOCK_CONTROL_INDEX);
        Tmp = Save & ~(0x3F | RADEON_PLL_WR_EN);
        WREG32(RADEON_CLOCK_CONTROL_INDEX, Tmp);
        Tmp = RREG32(RADEON_CLOCK_CONTROL_DATA);
        WREG32(RADEON_CLOCK_CONTROL_INDEX, Save);
    }

}

uint32_t R100PllReadRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register
){
    LouKIRQL Irql;
    uint32_t Data;
    LouKeAcquireSpinLock(&RDEV->PllIdxLock, &Irql);
    WREG8(RADEON_CLOCK_CONTROL_INDEX, Register & 0x3F);
    R100PllErrataAfterIndex(RDEV);
    Data = RREG32(RADEON_CLOCK_CONTROL_DATA);
    R100PplErrataAfterData(RDEV);
    LouKeReleaseSpinLock(&RDEV->PllIdxLock, &Irql);
    return Data;
}

void R100PllWriteRegister(
    PRADEON_DEVICE RDEV,
    uint32_t Register,
    uint32_t Value
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&RDEV->PllIdxLock, &Irql);
    WREG8(RADEON_CLOCK_CONTROL_INDEX, ((Register & 0x3F) | RADEON_PLL_WR_EN));
    R100PllErrataAfterIndex(RDEV);
    WREG32(RADEON_CLOCK_CONTROL_DATA, Value);
    R100PplErrataAfterData(RDEV);
    LouKeReleaseSpinLock(&RDEV->PllIdxLock, &Irql);
}

LOUSTATUS R100Initialize(PRADEON_DEVICE RDEV){



    return STATUS_SUCCESS;
}

void R100DeInitialize(PRADEON_DEVICE RDEV){

}

LOUSTATUS R100Suspend(PRADEON_DEVICE RDEV){

    return STATUS_SUCCESS;
}

LOUSTATUS R100Resume(PRADEON_DEVICE RDEV){


    return STATUS_SUCCESS;
}

void R100VgaSetState(PRADEON_DEVICE RDEV, bool State){

}

LOUSTATUS R100AsicReset(PRADEON_DEVICE RDEV, bool HardReset){


    return STATUS_SUCCESS;
}

bool R100GuiIdle(PRADEON_DEVICE RDEV){

    return true;
}

LOUSTATUS R100McWaitForIdle(PRADEON_DEVICE RDEV){



    return STATUS_SUCCESS;
}


LOUSTATUS R100IrqSet(PRADEON_DEVICE RDEV){

    return STATUS_SUCCESS;
}

LOUSTATUS R100IrqProcess(PRADEON_DEVICE RDEV){

    return STATUS_SUCCESS;
}



void R100WaitForVblank(PDrsdDevice Dev){

}


void R100BandwithUpdate(PRADEON_DEVICE RDEV){

}

uint32_t R100GetVblankCounter(PDrsdCrtc Crtc){
    return 0;
}

PRADEON_FENCE R100CopyBlit(
    PRADEON_DEVICE RDEV, 
    uint64_t Src,
    uint64_t Dst,
    uint64_t NumberOfGpuPages
){


    return 0;
}

void RadeonLegacySetBackLightLevel(PRADEON_ENCODER Encoder, uint8_t Level){

}

uint8_t RadeonLegacyGetBackLightLevel(PRADEON_ENCODER Encoder){
    return 0;
}


LOUSTATUS R100SetRegister(PRADEON_DEVICE RDEV, int Register, uint32_t TillingFlags, uint32_t Pitch, uint32_t Offset, uint32_t ObjSize){

    return STATUS_SUCCESS;
}
    
void R100ClearRegister(PRADEON_DEVICE RDEV, int Register){

}

void R100InitializationHahdler(PRADEON_DEVICE RDEV){

}

void R100DeInitializationHandler(PRADEON_DEVICE RDEV){

}

bool R100SenceHandler(PRADEON_DEVICE RDEV, RADEON_HPD_ID ID){

    return true;
}

void R100SetPolarity(PRADEON_DEVICE RDEV, RADEON_HPD_ID ID){

}

void R100Miscilanious(PRADEON_DEVICE RDEV){

}

void R100Prepare(PRADEON_DEVICE RDEV){

}
    
void R100PmDeInitialize(PRADEON_DEVICE RDEV){

}
    
void R100InitializeProfile(PRADEON_DEVICE RDEV){

}

void R100GetDynamicPowerManagementState(PRADEON_DEVICE RDEV){

}
    
uint32_t RadeonLegacyGetEngineClock(PRADEON_DEVICE RDEV){
    return 0;
}
    
void RadeonLegacySetEngineClock(struct _RADEON_DEVICE* RDEV, uint32_t Clock){

}
    
uint32_t RadeonLegacyGetMemoryClock(struct _RADEON_DEVICE* RDEV){
    return 0;
}
 
  
void RadeonLegacySetClockGating(struct _RADEON_DEVICE* RDEV, int Enable){

}

void R100PageFlip(struct _RADEON_DEVICE* RDEV, int Crtc, uint64_t CrtcBase, bool ASYNC){

}
    
void R100PageFlipPending(struct _RADEON_DEVICE* RDEV, int Crtc){

}

void R100VgaRenderDisable(PRADEON_DEVICE RDEV){
    uint32_t Temp = RRE8(R_0003C2_GEN_MO_WT);
    WREG8(R_0003C2_GEN_MO_WT, C_0003C2_VGA_RAM_ENABLE & Temp);
}

void RestoreR100RegistersToSanityValues(PRADEON_DEVICE RDEV){

    uint32_t Tmp;

    Tmp = RREG32(RADEON_CP_CSQ_CONTROL);
    if(Tmp){
        WREG32(RADEON_CP_CSQ_CONTROL, 0);
    }
    Tmp = RREG32(RADEON_CP_RB_CONTROL);
    if(Tmp){
        WREG32(RADEON_CP_RB_CONTROL, 0);
    }
    Tmp = RREG32(RADEON_SCRATCH_UMSK);
    if(Tmp){
        WREG32(RADEON_SCRATCH_UMSK, 0);
    }

}