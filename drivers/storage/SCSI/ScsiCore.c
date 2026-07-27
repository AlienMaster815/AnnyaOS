#include "ScsiCore.h"




LOUSTATUS ScsiCoreEntry(){
    LouPrint("SCSICORE.SYS:ScsiCoreEntry()\n");

    //LouKeCreateFastObjectClass("PDEV", 256, sizeof(PCI_DEVICE_OBJECT), GET_ALIGNMENT(PCI_DEVICE_OBJECT), 0, KERNEL_GENERIC_MEMORY);


    LouPrint("SCSICORE.SYS:ScsiCoreEntry():STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS;
}