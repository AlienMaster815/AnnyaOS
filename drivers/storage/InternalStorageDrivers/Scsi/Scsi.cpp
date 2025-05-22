#include <LouDDK.h>
#include <Hal.h>
#include "Scsi.h"

LOUSTATUS InitializeScsiDevice(P_PCI_DEVICE_OBJECT PDEV){

    LouPrint("Hello Scsi Controller\n");

    PPCI_COMMON_CONFIG CommonConfig = (PPCI_COMMON_CONFIG)PDEV->CommonConfig;

    LouPrint("Device ID :%h\n", CommonConfig->Header.DeviceID);
    LouPrint("Vendor ID :%h\n", CommonConfig->Header.VendorID);
    LouPrint("BASE CLASS:%h\n", CommonConfig->Header.BaseClass);
    LouPrint("SUB CLASS :%h\n", CommonConfig->Header.SubClass);
    LouPrint("PROG IF   :%h\n", CommonConfig->Header.ProgIf);

    for(uint8_t i = 0 ; i < 6;i++){
        LouPrint("Bar %d:%h\n", i, CommonConfig->Header.u.type0.BaseAddresses[i]);    
    }

    while(1);
    return STATUS_SUCCESS;
}
