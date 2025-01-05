#include <LouDDK.h>
#include <Hal.h>

#define NOT_AMD_CHIPSET 0
#define AMD_CHIPSET_SB600 1
#define AMD_CHIPSET_SB700 2
#define AMD_CHIPSET_SB800 3
#define AMD_CHIPSET_HUDSON2 4
#define AMD_CHIPSET_BOLTON 5
#define AMD_CHIPSET_YANGTZE 6
#define AMD_CHIPSET_TAISHAN 7
#define AMD_CHIPSET_UNKNOWN 8

static PPCI_DEVICE_GROUP AmdChipsetDevices;

void InitializeAmdVendorChipset(PPCI_DEVICE_GROUP Chipsets){

    AmdChipsetDevices = Chipsets;

}

bool IsChipSetAmdChipSet(){   
    return AmdChipsetDevices ? 1 : 0;
}