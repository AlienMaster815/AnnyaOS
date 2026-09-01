#include "../AtaCore.h"

PVOID AtaCoreAllocateAtaCommandPacket(){
    return LouKeAllocateFastObject("ATA_COMMAND_PACKET");
}

void AtaCoreFreeAtaCommandPacket(PVOID Object){
    LouKeFreeFastObject("ATA_COMMAND_PACKET", Object);
}

