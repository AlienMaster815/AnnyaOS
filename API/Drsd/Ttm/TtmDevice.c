#include "../DrsdCore.h"


DRIVER_EXPORT
LOUSTATUS
TtmDeviceInitialize(
    PDRSD_TTM_DEVICE            Device,
    PTTM_DEVICE_FUNCTIONS       Functions,
    PPCI_DEVICE_OBJECT          PDEV,
    PDRSD_VMA_OFFSET_MANAGER    VmaManager,
    UINT64                      PageFlags
){

    Device->AllocationFlags = PageFlags;
    Device->Functions = Functions;
    
    
    Device->VmaManager = VmaManager;

    return STATUS_SUCCESS;
}