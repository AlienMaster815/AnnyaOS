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