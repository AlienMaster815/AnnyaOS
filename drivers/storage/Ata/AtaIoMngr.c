#include "AtaCore.h"

void AtaCorePortIoQueueManager(PVOID Params){
    PATA_PORT_DEVICE_OBJECT PortDevice = (PATA_PORT_DEVICE_OBJECT)(UINT8*)Params;
    while(1){
        MutexLockOrYield(PortDevice->ChannelLock);
        PATA_COMMAND_PACKET CommandPacket = ListItemToTypeOrNull(PortDevice->QueuedCommands.NextHeader, ATA_COMMAND_PACKET, QueuedCommands);
        if(!CommandPacket){
            MutexUnlock(PortDevice->ChannelLock);
            LouKeYieldExecution();
            continue;
        }
        LouKeListDeleteItem(&CommandPacket->QueuedCommands);
        CommandPacket->CommandStatus = PortDevice->Operations->AtaPortDeviceIssueCommand(PortDevice, CommandPacket);
        if(CommandPacket->CommandStatus != STATUS_SUCCESS){
            goto _COMMAND_FINISHED;
        }
        if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_POLL){
            SIZE Timeout = 1000;
            _KEEP_POLLING:
            CommandPacket->CommandStatus = PortDevice->Operations->AtaPortDeviceGetCommandStatus(PortDevice, CommandPacket);
            if(CommandPacket->CommandStatus != STATUS_SUCCESS){
                goto _COMMAND_FINISHED;
            }
            if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_EXT_CMD){
                if(CommandPacket->PacketEx.Status & ((1 << 5) | 1)){
                    CommandPacket->CommandStatus = STATUS_IO_DEVICE_ERROR;
                    goto _COMMAND_FINISHED;
                }
                if(CommandPacket->PacketEx.Status & 0x80){
                    if(!Timeout){
                        CommandPacket->CommandStatus = STATUS_TIMEOUT;
                        goto _COMMAND_FINISHED;
                    }
                    sleep(1);
                    Timeout--;
                    goto _KEEP_POLLING;
                }
            }else{
                if(CommandPacket->Packet.Status & ((1 << 5) | 1)){
                    CommandPacket->CommandStatus = STATUS_IO_DEVICE_ERROR;
                    goto _COMMAND_FINISHED;
                }
                if(CommandPacket->Packet.Status & 0x80){
                    if(!Timeout){
                        CommandPacket->CommandStatus = STATUS_TIMEOUT;
                        goto _COMMAND_FINISHED;
                    }
                    sleep(1);
                    Timeout--;
                    goto _KEEP_POLLING;
                }
            }
        }else{
            LouPrint("AtaCorePortIoQueueManager() Not Polling\n");
            while(1);
        }
        _COMMAND_FINISHED:
        if(PortDevice->Operations->AtaPortDeviceCleanupCommand){
            CommandPacket->CleanupStatus = PortDevice->Operations->AtaPortDeviceCleanupCommand(PortDevice, CommandPacket);
        }
        LouKeSetAtomicBoolean(&CommandPacket->CommandDone, 1);
        MutexUnlock(PortDevice->ChannelLock);
        LouKeYieldExecution();
    }
}