#include <LouDDK.h>
#include "Radeon.h"

bool RadeonAtrmGetBios(PRADEON_DEVICE RDEV){

    return true;
}

bool RadeonVfctBios(PRADEON_DEVICE RDEV){

    return true;
}



bool RadeonCardPosted(PRADEON_DEVICE RDEV){

    return true;
}

bool IgpReadBiosFromVram(PRADEON_DEVICE RDEV){



    return true;
}

bool RadeonReadBios(PRADEON_DEVICE RDEV){

    return true;
}

bool RadeonReadDisabledBios(PRADEON_DEVICE RDEV){

    return true;
}

bool RadeonReadPlatformBios(PRADEON_DEVICE RDEV){

    return true;
}

bool RadeonGetBios(PRADEON_DEVICE RDEV){
    UNUSED bool Result = true;
    UNUSED uint16_t Tmp;

    Result = RadeonAtrmGetBios(RDEV);
    if(!Result){
        Result = RadeonVfctBios(RDEV);
    }
    if(!Result){
        Result = IgpReadBiosFromVram(RDEV);
    }
    if(!Result){
        Result = RadeonReadBios(RDEV);
    }
    if(!Result){
        Result = RadeonReadDisabledBios(RDEV);
    }
    if(!Result){
        Result = RadeonReadPlatformBios(RDEV);
    }

    return Result;
}