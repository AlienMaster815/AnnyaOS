#include <usb.h>
#include "Ohci.h"
#include <Hal.h>


void InitializeOhciDevice(P_PCI_DEVICE_OBJECT PDEV){
    return;
    LouPrint("Initializing Ohci Device\n");


    LouPrint("OHCI Initialization Success\n");
    while(1);
}