#include <LouACPI.h>
#include "acpi.h"

int _EfiCapsuleSetupInfo(
    PEFI_CAPSULE_INFORMATION CapsuleInfo
){
    LouPrint("_EfiCapsuleSetupInfo()\n");
    while(1);
    return 0x00;
}

int EfiCapsuleSetupInfo(
    PEFI_CAPSULE_INFORMATION    CapsuleInfo, 
    void*                       KernelBuffer,
    size_t                      HeaderBytes
){
    LouPrint("EfiCapsuleSetupInfo()\n");
    while(1);
    return 0x00;
}

