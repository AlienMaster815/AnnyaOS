#include <LouDDK.h>
#include <Hal.h>

//PPCI_DEVICE_OBJECT LouKeGetPDEV(uint8_t Bus, uint8_t Slot, uint8_t Function);

//PPCI_DEVICE_GROUP LouKeHalOpenPciCompanions(
//    PPCI_DEVICE_OBJECT PDEV
//){

//    PPCI_DEVICE_GROUP DevGroup = LouKeMallocArray(PCI_DEVICE_GROUP,  8, KERNEL_GENERIC_MEMORY);

//    for(uint8_t i = 0 ; i < 8;i++){
//        DevGroup[i].PDEV = LouKeGetPDEV(PDEV->bus, PDEV->slot, i);
//    }

//    return DevGroup;
//}