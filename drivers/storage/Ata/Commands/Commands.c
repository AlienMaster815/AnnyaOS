#include "../AtaCore.h"

PVOID AtaCoreAllocateAtaCommandPacket(){
    return LouKeAllocateFastObject("ATA_COMMAND_PACKET");
}

void AtaCoreFreeAtaCommandPacket(PVOID Object){
    LouKeFreeFastObject("ATA_COMMAND_PACKET", Object);
}

void 
AtaCoreCommitCommandPacketToPort(
    PATA_COMMAND_PACKET     CommandPacket, 
    PATA_PORT_DEVICE_OBJECT AtaPort
){
    MutexLock(AtaPort->ChannelLock);
    LouKeListAddTail(&CommandPacket->QueuedCommands, &AtaPort->QueuedCommands);
    LouKeUnblockThread(AtaPort->CommandWorkerThread);
    MutexUnlock(AtaPort->ChannelLock);
}
