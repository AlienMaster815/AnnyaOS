//Copyright GPL-2 Tyler Grenier (2023 - 2026)
#include <LouDDK.h>


LOUAPI uint8_t LouKeGetPciInterruptLineFromPin(PPCI_DEVICE_OBJECT PDEV);

uint8_t LouKeGetPciInterruptPin(PPCI_DEVICE_OBJECT PDEV){

    uint8_t PIN = LouKeReadPciUint8(PDEV, 0x3D);
    return PIN;
}

uint8_t LouKeGetPciInterruptLine(PPCI_DEVICE_OBJECT PDEV){
    return LouKeReadPciUint8(PDEV, 0x3C);
}

LOUAPI bool GetAPICStatus();

LOUAPI uint8_t LouKePciGetInterruptLine(PPCI_DEVICE_OBJECT PDEV){
    if(GetAPICStatus()){
        UINT8 Result = LouKeGetPciInterruptLineFromPin(PDEV);
        if(Result == 0xFF){
            return Result;
        }
        else {
            return Result + 0x20;
        }
    }
    return LouKeGetPciInterruptLine(PDEV) + 0x20;
}
