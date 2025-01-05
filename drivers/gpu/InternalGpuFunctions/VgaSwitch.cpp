#include <LouDDK.h>

LOUSTATUS VgaSwitchClientDefer(
    P_PCI_DEVICE_OBJECT PDEV
){

    UNUSED PPCI_COMMON_CONFIG Config = (PPCI_COMMON_CONFIG)PDEV->CommonConfig;

    if(Config->Header.BaseClass == 0x03){
        //TODO: AppleGmuxPresent() && PDEV != VgaDefaultDevice()
        //then return UNSUCCESSFUL
    }

    return STATUS_SUCCESS;
}

LOUSTATUS VgaClientRegister(P_PCI_DEVICE_OBJECT PDEV, uint32_t (*Handler)(P_PCI_DEVICE_OBJECT, bool)){

    PDEV->VgaDecode = (uintptr_t)Handler;

    return STATUS_SUCCESS;
}