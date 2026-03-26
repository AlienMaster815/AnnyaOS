#include "DrsdCore.h"

LOUSTATUS 
DrsdGxeInitialize(
    PDRSD_DEVICE Device
){
    PDRSD_VMA_OFFSET_MANAGER VmaOffsetManager = LouKeMallocType(DRSD_VMA_OFFSET_MANAGER, KERNEL_GENERIC_MEMORY);
    if(!VmaOffsetManager){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Device->VmaOffsetManager = VmaOffsetManager;

    return STATUS_SUCCESS;
}