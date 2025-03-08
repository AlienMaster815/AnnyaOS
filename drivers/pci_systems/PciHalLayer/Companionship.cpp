#include <LouDDK.h>
#include <Hal.h>

P_PCI_DEVICE_OBJECT LouKeGetPDEV(uint8_t Bus, uint8_t Slot, uint8_t Function);

PPCI_DEVICE_GROUP LouKeHalOpenPciCompanions(
    uint8_t Bus,
    uint8_t Slot
){

    PPCI_DEVICE_GROUP DevGroup = (PPCI_DEVICE_GROUP)LouKeMallocEx(sizeof(PCI_DEVICE_GROUP) * 8, GET_ALIGNMENT(PCI_DEVICE_GROUP), WRITEABLE_PAGE | PRESENT_PAGE);

    for(uint8_t i = 0 ; i < 8;i++){
        DevGroup[i].PDEV = LouKeGetPDEV(Bus, Slot, i);
    }

    return DevGroup;
}