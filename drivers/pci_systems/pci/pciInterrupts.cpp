#include <LouDDK.h>
#include <NtAPI.h>

KERNEL_IMPORT uint8_t LouKeGetPciInterruptLineFromPin(P_PCI_DEVICE_OBJECT PDEV);

uint8_t LouKeGetPciInterruptPin(P_PCI_DEVICE_OBJECT PDEV){

    uint8_t PIN = LouKeReadPciUint8(PDEV, 0x3D);
    return PIN;
}

uint8_t LouKeGetPciInterruptLine(P_PCI_DEVICE_OBJECT PDEV){
    return LouKeReadPciUint8(PDEV, 0x3C);
}

LOUDDK_API_ENTRY bool GetAPICStatus();

KERNEL_IMPORT uint8_t LouKePciGetInterruptLine(P_PCI_DEVICE_OBJECT PDEV){
    if(GetAPICStatus()){
        return LouKeGetPciInterruptLineFromPin(PDEV) + 0x20;
    }
    return LouKeGetPciInterruptLine(PDEV) + 0x20;
}
