#include "../DrsdCore.h"

DRIVER_EXPORT
void 
TtmResourceManagerInitialize(
    PTTM_RESOURCE_MANAGER   Manager,
    PDRSD_TTM_DEVICE        TtmDevice,
    SIZE                    Size
){
    UINT i;
    Manager->TtmDevice = TtmDevice;
    Manager->Size = Size;
    Manager->Usage = 0;

    for(i = 0 ; i < TTM_MOVE_FENCES_COUNT; i++){    
        Manager->EvictionDmaFences[i] = 0x00;
    }
}