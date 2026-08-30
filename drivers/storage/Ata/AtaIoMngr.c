#include "AtaCore.h"

void AtaCorePortIoQueueManager(PVOID Params){
    BOOLEAN Defer;
    PATA_HOST_DEVICE_OBJECT HostDevice = (PATA_HOST_DEVICE_OBJECT)Params;
    SIZE i;
    PATA_PORT_DEVICE_OBJECT TmpPort;
    while(1){    
        ForEachAtaPort(HostDevice, TmpPort, i){
            if(MutexLockOrFalse(TmpPort->ChannelLock)){
                PATA_COMMAND_PACKET SafeEntry;
                PATA_COMMAND_PACKET TmpEntry;
                PATA_COMMAND_PACKET CommandPacket = ListItemToTypeOrNull(TmpPort->CommandList.NextHeader, ATA_COMMAND_PACKET, FifoChain);
                if(CommandPacket){
                    LouKeListDeleteItem(TmpPort->CommandList.NextHeader);
                    if(TmpPort->Operations->AtaPortDeviceIssueCommand){
                        CommandPacket->CommandStatus = TmpPort->Operations->AtaPortDeviceIssueCommand(TmpPort, CommandPacket);
                        if((TmpPort->Operations->AtaPortDeviceGetCommandStatus) && (CommandPacket->CommandStatus == STATUS_SUCCESS)){
                            if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_POLL){
                                SIZE Timeout = 1000;
                                while(CommandPacket->CommandStatus == STATUS_SUCCESS){
                                    CommandPacket->CommandStatus = TmpPort->Operations->AtaPortDeviceGetCommandStatus(TmpPort, CommandPacket);
                                    if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_EXT_CMD){
                                        if(CommandPacket->PacketEx.Status & ((1 << 5) | 1)){
                                            sleep(10);
                                            Timeout--;
                                        }
                                    }else{
                                        if(CommandPacket->Packet.Status & ((1 << 5) | 1)){
                                            CommandPacket->CommandStatus = STATUS_IO_DEVICE_ERROR;
                                            break;
                                        }
                                        if(CommandPacket->Packet.Status & 0x80){
                                            sleep(10);
                                            Timeout--;
                                        }
                                    }
                                    break;
                                }
                            }else{
                                LouPrint("AtaCorePortIoQueueManager() Not Polling\n");
                                while(1);
                            }
                            LouKeSetAtomicBoolean(&CommandPacket->CommandDone, 1);
                            if(TmpPort->Operations->AtaPortDeviceCleanupCommand){
                                CommandPacket->CleanupStatus = TmpPort->Operations->AtaPortDeviceCleanupCommand(TmpPort, CommandPacket);
                            }
                        }
                        ForEachListEntrySafe(TmpEntry, SafeEntry, &CommandPacket->MultiCmdChain, MultiCmdChain){
                            if(TmpEntry->CommandStatus == STATUS_SUCCESS){
                                if(TmpPort->Operations->AtaPortDeviceIssueCommand){
                                    TmpEntry->CommandStatus = TmpPort->Operations->AtaPortDeviceIssueCommand(TmpPort, TmpEntry);
                                    if((TmpPort->Operations->AtaPortDeviceGetCommandStatus) && (TmpEntry->CommandStatus == STATUS_SUCCESS)){
                                        if(TmpEntry->CommandFlags & ATA_COMMAND_PACKET_FLAGS_POLL){
                                            SIZE Timeout = 1000;
                                            while(TmpEntry->CommandStatus == STATUS_SUCCESS){
                                                TmpEntry->CommandStatus = TmpPort->Operations->AtaPortDeviceGetCommandStatus(TmpPort, TmpEntry);
                                                if(TmpEntry->CommandFlags & ATA_COMMAND_PACKET_FLAGS_EXT_CMD){
                                                    if(TmpEntry->PacketEx.Status & ((1 << 5) | 1)){
                                                        sleep(10);
                                                        Timeout--;
                                                    }
                                                }else{
                                                    if(TmpEntry->Packet.Status & ((1 << 5) | 1)){
                                                        TmpEntry->CommandStatus = STATUS_IO_DEVICE_ERROR;
                                                        break;
                                                    }
                                                    if(TmpEntry->Packet.Status & 0x80){
                                                        sleep(10);
                                                        Timeout--;
                                                    }
                                                }
                                                break;
                                            }
                                        }
                                    }else{
                                        LouPrint("AtaCorePortIoQueueManager() Not Polling\n");
                                        while(1);
                                    }
                                    LouKeSetAtomicBoolean(&TmpEntry->CommandDone, 1);
                                    if(TmpPort->Operations->AtaPortDeviceCleanupCommand){
                                        TmpEntry->CleanupStatus = TmpPort->Operations->AtaPortDeviceCleanupCommand(TmpPort, TmpEntry);
                                    }
                                }     
                            }
                            LouKeListDeleteItem(&TmpEntry->FifoChain);
                            LouKeListDeleteItem(&TmpEntry->MultiCmdChain);
                        }
                    }
                }
                MutexUnlock(TmpPort->ChannelLock);
            }
        }
    }
}