#include "AtaCore.h"



void AtaCorePortIoQueueManager(PVOID Params){
    PATA_PORT_DEVICE_OBJECT PortDevice = (PATA_PORT_DEVICE_OBJECT)(UINT8*)Params;
    PTHREAD Thread = LouKeGetCurrentThreadHandle();
    while(1){
        MutexLock(PortDevice->ChannelLock);
        PATA_COMMAND_PACKET CommandPacket = ListItemToTypeOrNull(PortDevice->QueuedCommands.NextHeader, ATA_COMMAND_PACKET, QueuedCommands);
        if(!CommandPacket){
            MutexUnlock(PortDevice->ChannelLock);
            LouKeBlockThread(Thread);
            continue;
        }
        LouKeListDeleteItem(&CommandPacket->QueuedCommands);
        CommandPacket->CommandStatus = PortDevice->Operations->AtaPortDeviceIssueCommand(PortDevice, CommandPacket);
        LOUSTATUS tStatus = STATUS_SUCCESS;
        if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_POLL){
            tStatus = PortDevice->Operations->AtaPortDeviceGetCommandStatus(PortDevice, CommandPacket);
        }else{
            LouPrint("AtaCorePortIoQueueManager() Not Polling\n");
            while(1);
        }
        if(CommandPacket->CommandStatus == STATUS_SUCCESS){
            CommandPacket->CommandStatus = tStatus;
        }
        LouPrint("Port:%d:Error :%h\n", PortDevice->PortNumber, CommandPacket->Packet.Error);
        LouPrint("Port:%d:Status:%h\n", PortDevice->PortNumber, CommandPacket->Packet.Status);
        LouPrint("Port:%d:CmdSTS:%h\n", PortDevice->PortNumber, CommandPacket->CommandStatus);
        if(PortDevice->Operations->AtaPortDeviceCleanupCommand){
            CommandPacket->CleanupStatus = PortDevice->Operations->AtaPortDeviceCleanupCommand(PortDevice, CommandPacket);
        }
        MutexUnlock(PortDevice->ChannelLock);
        LouKeSetAtomicBoolean(&CommandPacket->CommandDone, 1);
    }
}