#ifndef ATA_CORE_INTERNALS_H
#define ATA_CORE_INTERNALS_H

#define _KERNEL_MODULE_

#include <LouDDK.h>

void AtaCoreDbgPrint(char* format, ...);

void AtaCoreEncodeCfaEraseSectorsCommand(PATA_COMMAND_CFA_ERASE_SECTORS_STRUCTURE Cmd, UINT8 Dev, UINT32 Lba, UINT8 SectorCount);
void AtaCoreEncodeCfaRequesttExtendedErrorCodeCommand(PATA_COMMAND_CFA_REQUEST_EXTENDED_ERROR_CODE_STRUCTURE  Cmd, UINT8 Dev);
void AtaCoreEncodeCfaTranslateSectorCommand(PATA_COMMAND_CFA_TRANSLATE_SECTOR_STRUCTURE Cmd, UINT8 Dev, UINT32 Lba);
void AtaCoreEncodeCfaWriteMultipleWithoutEraseCommand(PATA_COMMAND_CFA_WRITE_MULTIPLE_WITHOUGHT_ERASE_STRUCTURE Cmd, UINT8 Dev, UINT32 Lba, UINT8 SectorCount);
void AtaCoreEncodeCfaWriteSectorsWithoutEraseCommand(PATA_COMMAND_CFA_WRITE_SECTORS_WITHOUGHT_ERASE_STRUCTURE Cmd, UINT8 Dev, UINT32 Lba, UINT8 SectorCount);
void AtaCoreEncodeCheckMediaCardTypeCommand(PATA_COMMAND_CHECK_MEDIA_CARD_TYPE_STRUCTURE Cmd, UINT8 Dev, UINT8 Enb);
void AtaCoreEncodeCheckPowerModeCommand(PATA_COMMAND_CHECK_POWER_MODE_STRUCTURE Cmd, UINT8 Dev);
void AtaCoreEncodeConfigureStreamCommand(PATA_COMMAND_CONFIGURE_STREAM_STRUCTURE Cmd, UINT8 Dev, UINT8 Dcctl, UINT8 StreamID, UINT8 Rw, UINT8 Ar, UINT16 SectorCount);
void AtaCoreEncodeDeviceConfigurationRestoreCommand(PATA_COMMAND_DEVICE_CONFIGURATION_RESTORE_STRUCTURE Cmd, UINT8 Dev);
void AtaCoreEncodeDeviceConfigurationFreezeLockCommand(PATA_COMMAND_DEVICE_CONFIGURATION_FREEZE_LOCK_STRUCTURE Cmd, UINT8 Dev);
void AtaCoreEncodeDeviceConfigurationIdentifyCommand(PATA_COMMAND_DEVICE_CONFIGURATION_IDENTIFY_STRUCTURE Cmd, UINT8 Dev);
void AtaCoreEncodeDeviceConfigurationSetCommand(PATA_COMMAND_DEVICE_CONFIGURATION_SET_STRUCTURE Cmd, UINT8 Dev);
void AtaCoreEncodeDeviceResetCommand(PATA_COMMAND_DEVICE_RESET_STRUCTURE Cmd, UINT8 Dev);
void AtaCoreEncodeDownloadMicroCodeCommand( PATA_COMMAND_DOWNLOAD_MICROCODE_STRUCTURE Cmd, UINT8 Dev, UINT8 SubCommandCode, UINT16 SectorCount);
void AtaCoreEncodeExecuteDeviceDiagnosticsCommand(PATA_COMMAND_EXECUTE_DEVICE_DIAGNOSTIC Cmd);
void AtaCoreEncodeFlushCacheCommand(PATA_COMMAND_FLUSH_CACHE_STRUCTURE Cmd, UINT8 Dev);
void AtaCoreEncodeFlushCacheExCommand(PATA_COMMAND_FLUSH_CACHE_EX_STRUCTURE Cmd, UINT8 Dev);
void AtaCoreEncodeGetMediaStatusCommand(PATA_COMMAND_GET_MEDIA_STATUS_STRUCTURE Cmd, UINT8 Dev);
void AtaCoreEncodeIdentifyDeviceCommand(PATA_COMMAND_IDENTIFY_DEVICE_STRUCTURE Cmd, UINT8 Dev);
void AtaCoreEncodeIdentifyPacketDeviceCommand(PATA_COMMAND_IDENTIFY_PACKET_DEVICE_STRUCTURE Cmd, UINT8 Dev);
void AtaCoreEncodeIdleCommand(PATA_COMMAND_IDLE_STRUCTURE Cmd, UINT8 TimePeriod, UINT8 Dev);
void AtaCoreEncodeIdleImmediateCommand(PATA_COMMAND_IDLE_IMMEDIATE_STRUCTURE Cmd, UINT8 Dev);
void AtaCoreEncodeMediaEjectCommand(PATA_COMMAND_MEDIA_EJECT_STRUCTURE Cmd, UINT8 Dev);
void AtaCoreEncodeMediaLockCommand(PATA_COMMAND_MEDIA_LOCK_STRUCTURE Cmd, UINT8 Dev);
void AtaCoreEncodeMediaUnlockCommand(PATA_COMMAND_MEDIA_UNLOCK_STRUCTURE Cmd, UINT8 Dev);
void AtaCoreEncodeNopCommand(PATA_COMMAND_NOP_STRUCTURE Cmd, UINT8 Dev, UINT8 SubCommand);
void AtaCoreEncodePacketCommand(PATA_COMMAND_PACKET_STRUCTURE Cmd, UINT8 Dev, UINT16 ByteCountLimit, UINT8 Dma, UINT8 Ovl, UINT8 Tag);

LOUSTATUS AtaCoreRegisterAtaPorts(PATA_HOST_DEVICE_OBJECT HostDevice);

void AtaCorePortIoQueueManager(PVOID Params);

PVOID AtaCoreAllocateAtaCommandPacket();
void AtaCoreFreeAtaCommandPacket(PVOID Object);

LOUSTATUS AtaCoreGetEndpointCapacity(PATA_ENDPOINT_DEVICE_OBJECT EndpointDevice, UINT32* OutLba, UINT32* OutSectorSize);
LOUSTATUS AtaCoreReadSectorsFromEndpointDevice(PATA_ENDPOINT_DEVICE_OBJECT EndpointDevice, UINT32 Lba, UINT32 SectorCount, PVOID OutBuffer);

#endif