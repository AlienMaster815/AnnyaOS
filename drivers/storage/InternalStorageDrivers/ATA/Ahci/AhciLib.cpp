#include <LouDDK.h>


PHBA_COMMAND_TABLE LouKeAhciMallocCommandTable(uint16_t TableEntries){
    if(!TableEntries){
        return 0x00;
    }

    return (PHBA_COMMAND_TABLE)LouKeMallocEx(sizeof(HBA_COMMAND_TABLE) + (TableEntries * sizeof(HBA_PRDT_ENTRY)), 128, WRITEABLE_PAGE | UNCACHEABLE_PAGE | PRESENT_PAGE);
}

void LouKeAhciFreeCommandTable(PHBA_COMMAND_TABLE Table){
    LouKeFree((void*)Table);
}


LOUSTATUS AhciGenricDMAPrepCommand(
    PATA_QUEUED_COMMAND QueuedCommand
){  
    LouPrint("AhciGenricDMAPrepCommand\n");
    while(1);
    return STATUS_SUCCESS;  
}

LOUSTATUS AhciGenricDMAIssueCommand(
    PATA_QUEUED_COMMAND QueuedCommand
){
    LouPrint("AhciaGenricDMAIssueCommand\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS AhciGenericHardReset(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    LouPrint("AhciGenericHardReset");
    while(1);
    return STATUS_SUCCESS;
}
