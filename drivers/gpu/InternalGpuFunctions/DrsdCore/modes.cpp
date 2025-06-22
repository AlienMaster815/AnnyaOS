#include "DrsdCore.h"


size_t DrsdModeVfresh(PDRSD_DISPLAY_MODE Mode) {
    uint64_t num = Mode->KhzClock;
    uint64_t den;

    if (Mode->HorizontalTotal == 0 || Mode->VirticalTotal == 0) {
        return 0;
    }

    den = (uint64_t)Mode->HorizontalTotal * (uint64_t)Mode->VirticalTotal;

    if (Mode->DdmFlags & DDM_FLAG_INTERLACED)
        num *= 2;
    if (Mode->DdmFlags & DDM_FLAG_DOUBLE_SCAN)
        den *= 2;
    if (Mode->VirticalScan > 1)
        den *= Mode->VirticalScan;

    return (size_t)((num * 1000 + (den / 2)) / den);
}


PDRSD_DISPLAY_MODE DrsdForkMode(PDRSD_DEVICE Device, PDRSD_DISPLAY_MODE DispMode){
    PDRSD_DISPLAY_MODE Result = LouKeMallocType(DRSD_DISPLAY_MODE, KERNEL_GENERIC_MEMORY);
    
    memcpy(Result, DispMode, sizeof(DRSD_DISPLAY_MODE));

    //TODO: Register to device for global tracking

    return Result;
}

#define HV_FACTOR                       1000
#define CVT_MARGIN_PERCENTAGE           18
#define CVT_HORIZONTAL_GRANULARITY      8         
#define CVT_MINIMAL_VERTICAL_PORCH      3
#define CVT_MINIMAL_VERTICAL_BPORCH     6
#define CVT_KHZ_CLOCK_STEPING           250
#define CVT_MINIMAL_VSYNC_BP            550
#define CVT_HORIZONTAL_SYNC_PRECENTAGE  8
#define CVT_M_FACTOR                    600
#define CVT_C_FACTOR                    40    
#define CVT_K_FACTOR                    128    
#define CVT_J_FACTOR                    20    
#define CVT_M_PRIME                     (600 * 128 / 256)     
#define CVT_C_PRIME                     ((40 - 20) * 128 / 256 + 20)    
#define CVT_RB_MINIMAL_VBLANK           460
#define CVT_RB_HORIZONTAL_SYNC          32
#define CVT_RB_HORIZONTAL_BLANK         160
#define CVT_RB_VFPORCH                  3

KERNEL_IMPORT
int snprintf(char *buffer, size_t buffer_size, const char *format, ...);

PDRSD_DISPLAY_MODE DrsdCreateModeObject(PDRSD_DEVICE Device){   
    PDRSD_DISPLAY_MODE NewMode = LouKeMallocType(DRSD_DISPLAY_MODE, KERNEL_GENERIC_MEMORY);

    //TODO : Add a track hande to the device

    return NewMode;
}

void DrsdSetModeName(PDRSD_DISPLAY_MODE Mode){
    bool IsInterlaced = (Mode->DdmFlags & DDM_FLAG_INTERLACED);
    Mode->ModeName = (string)LouKeMallocEx(32, 1, KERNEL_GENERIC_MEMORY);
    snprintf(Mode->ModeName, 32, "%dx%d%s", Mode->HorizontalDisplay, Mode->VirticalDisplay, IsInterlaced ? "i" : "");
}

PDRSD_DISPLAY_MODE DrsdCvtMode(
    PDRSD_DEVICE Device, 
    uint32_t Width, 
    uint32_t Height, 
    uint32_t Vfresh, 
    bool Reduced, 
    bool Interlaced, 
    bool Margins
){
    PDRSD_DISPLAY_MODE NewMode;
    uint64_t VFeild;
    uint64_t HRound, VRound, HMargin, VMargin;
    size_t Interlace = 0;
    size_t VSync;
    size_t HPeriod;
    size_t Tmp;

    if((!Height) || (!Width)){
        return 0x00;
    }

    NewMode = DrsdCreateModeObject(Device);
    if(!NewMode){
        return 0x00;
    }

    Vfresh = Vfresh ? Vfresh : 60;

    VFeild = Vfresh;
    VRound = Height;

    if(Interlaced){
        Interlace = 1;
        VFeild *= 2;
        VRound /= 2;
    }

    HRound = Width - (Width % CVT_HORIZONTAL_GRANULARITY);

    HMargin = 0;
    VMargin = 0;

    if(Margins){
        HMargin = HRound * CVT_MARGIN_PERCENTAGE / 1000;
        HMargin -= HMargin % CVT_HORIZONTAL_GRANULARITY;
        VMargin = VRound * CVT_MARGIN_PERCENTAGE / 1000;
    }

    NewMode->HorizontalDisplay = HRound + 2 * HMargin;
    NewMode->VirticalDisplay = VRound + 2 * VMargin;

    if((!(Height % 3)) && ((Height * 4 / 3) == Width)){
        VSync = 4;
    }
    else if((!(Height % 9)) && ((Height * 16 / 9) == Width)){
        VSync = 5;
    }
    else if((!(Height % 10)) && ((Height * 16 / 10) == Width)){
        VSync = 6;
    }
    else if((!(Height % 4)) && ((Height * 5 / 4) == Width)){
        VSync = 7;
    }
    else if((!(Height % 9)) && ((Height * 15 / 9) == Width)){
        VSync = 7;
    }else{
        VSync = 10;
    }

    if(!Reduced){
        uint64_t Tmp1, Tmp2;
        size_t HorizontalBlankPrec;
        size_t VsbPorch, HorizontalBlank;
        UNUSED size_t VbPorch; 

        Tmp1 = HV_FACTOR * 1000000 - CVT_MINIMAL_VSYNC_BP * HV_FACTOR * VFeild;
        Tmp2 = (VRound + 2 * VMargin + CVT_MINIMAL_VERTICAL_PORCH) * 2 + Interlace;

        HPeriod = Tmp1 * 2 / (Tmp2 * VFeild);

        Tmp1 = CVT_MINIMAL_VSYNC_BP * HV_FACTOR / HPeriod + 1;

        if(Tmp1 < (VSync + CVT_MINIMAL_VERTICAL_PORCH)){
            VsbPorch = VSync + CVT_MINIMAL_VERTICAL_PORCH;
        }else{
            VsbPorch = Tmp1;
        }

        VbPorch = VsbPorch - VSync;
        NewMode->VirticalTotal = VRound + 2 * VMargin + VsbPorch + CVT_MINIMAL_VERTICAL_PORCH; 

        HorizontalBlankPrec = CVT_C_PRIME * HV_FACTOR - CVT_M_PRIME * HPeriod / 1000;

        if(HorizontalBlankPrec < 20 * HV_FACTOR){
            HorizontalBlankPrec = 20 * HV_FACTOR;
        }

        HorizontalBlank = NewMode->HorizontalDisplay * HorizontalBlankPrec / (100 * HV_FACTOR - HorizontalBlankPrec);
        HorizontalBlank -= HorizontalBlank % (2 * CVT_HORIZONTAL_GRANULARITY);

        NewMode->HorizontalTotal = NewMode->HorizontalDisplay + HorizontalBlank;
        NewMode->HorizontalSyncEnd = NewMode->HorizontalDisplay + HorizontalBlank / 2;
        NewMode->HorizontalSyncStart = NewMode->HorizontalSyncEnd - (NewMode->HorizontalTotal * CVT_HORIZONTAL_SYNC_PRECENTAGE) / 100;
        NewMode->HorizontalSyncStart += CVT_HORIZONTAL_GRANULARITY - NewMode->HorizontalSyncStart % CVT_HORIZONTAL_GRANULARITY;
        NewMode->VirticalSyncStart = NewMode->VirticalDisplay + CVT_MINIMAL_VERTICAL_PORCH;
        NewMode->VirticalSyncEnd = NewMode->VirticalSyncStart + VSync;
    }else{
        size_t VbLines, Tmp1, Tmp2;

        Tmp1 = HV_FACTOR * 1000000 - CVT_RB_MINIMAL_VBLANK * HV_FACTOR * VFeild;
        Tmp2 = VRound + 2 * VMargin;

        HPeriod = Tmp1 / (Tmp2 * VFeild);
        VbLines = CVT_RB_MINIMAL_VBLANK * HV_FACTOR / HPeriod + 1;

        if(VbLines < (CVT_RB_VFPORCH + VSync + CVT_MINIMAL_VERTICAL_BPORCH)){
            VbLines = CVT_RB_VFPORCH + VSync + CVT_MINIMAL_VERTICAL_BPORCH;
        }

        NewMode->VirticalTotal = VRound + 2 * VMargin + VbLines;
        NewMode->HorizontalTotal = NewMode->HorizontalDisplay + CVT_RB_HORIZONTAL_BLANK;
        NewMode->HorizontalSyncEnd = NewMode->HorizontalDisplay + CVT_RB_HORIZONTAL_BLANK / 2;
        NewMode->HorizontalSyncStart = NewMode->HorizontalSyncEnd - CVT_RB_HORIZONTAL_SYNC;
        NewMode->VirticalSyncStart = NewMode->VirticalDisplay + CVT_RB_VFPORCH;
        NewMode->VirticalSyncEnd = NewMode->VirticalSyncStart + VSync;
    }

    Tmp = NewMode->HorizontalTotal;
    Tmp *= HV_FACTOR * 1000;
    Tmp /= HPeriod;
    Tmp -= NewMode->KhzClock % CVT_KHZ_CLOCK_STEPING;
    NewMode->KhzClock = Tmp;   

    if(Interlaced){
        NewMode->VirticalTotal *= 2;
        NewMode->DdmFlags |= DDM_FLAG_INTERLACED;
    }

    DrsdSetModeName(NewMode);

    if(Reduced){
        NewMode->DdmFlags |= DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW;
    }else{
        NewMode->DdmFlags |= DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH;
    }

    LouPrint("DrsdCvtMode() STATUS_SUCCESS\n");
    return NewMode;
}