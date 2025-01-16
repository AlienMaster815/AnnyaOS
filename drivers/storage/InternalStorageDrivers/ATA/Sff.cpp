#include <LouDDK.h>

KERNEL_IMPORT
int AtaBmdaPortStart(PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort){
    if((AtaPort->MwDmaBits) || (AtaPort->UDmaBits)){
        //TODO: Allocate Coherent Memory For Controller

    }

    LouPrint("AtaBmdaPortStart()\n");
    while(1);
    return 0;
}