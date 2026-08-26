#include "../AtaCore.h"

static void AtaCoreEncodeLba28Common(
    PATA_COMMAND_GENERIC    Cmd,
    UINT32                  Lba
){  
    Cmd->LbaLow = Lba & 0xFF;
    Cmd->LbaMid = (Lba >> 8) & 0xFF; 
    Cmd->LbaHigh = (Lba >> 16) & 0xFF;
}

static void AtaCoreEncodeDeviceConfiguration(
    PATA_COMMAND_DEVICE_CONFIGURATION_STRUCTURE Cmd,
    UINT8                                       Dev,
    UINT8                                       Operation //feature
){
    ATA_COMMAND_DEVICE_CONFIGURATION_STRUCTURE tCmd = {0};
    tCmd.Features = Operation;
    tCmd.Device = Dev ? (1 << 4) : 0;
    tCmd.Command = ATA_COMMAND_CODE_DEVICE_CONFIGURATION;
    memcpy(Cmd, &tCmd, sizeof(ATA_COMMAND_DEVICE_CONFIGURATION_STRUCTURE));
}

void AtaCoreEncodeCfaEraseSectorsCommand(
    PATA_COMMAND_CFA_ERASE_SECTORS_STRUCTURE    Cmd,
    UINT8                                       Dev,
    UINT32                                      Lba,
    UINT8                                       SectorCount
){
    ATA_COMMAND_CFA_ERASE_SECTORS_STRUCTURE tCmd = {0};
    tCmd.Features = 0x00;
    tCmd.SectorCount = SectorCount;
    AtaCoreEncodeLba28Common((PATA_COMMAND_GENERIC)&tCmd, Lba);
    tCmd.Device = (1 << 6) | ((Lba >> 24) & 0x0F);
    tCmd.Device |= Dev ? (1 << 4) : 0;
    tCmd.Command = ATA_COMMAND_CODE_CFA_ERASE_SECTORS;
    memcpy(Cmd, &tCmd, sizeof(ATA_COMMAND_CFA_ERASE_SECTORS_STRUCTURE));
}

void AtaCoreEncodeCfaRequesttExtendedErrorCodeCommand(
    PATA_COMMAND_CFA_REQUEST_EXTENDED_ERROR_CODE_STRUCTURE  Cmd,
    UINT8                                                   Dev
){
    ATA_COMMAND_CFA_REQUEST_EXTENDED_ERROR_CODE_STRUCTURE tCmd = {0};
    tCmd.Device = Dev ? (1 << 4) : 0;
    tCmd.Command = ATA_COMMAND_CODE_CFA_REQUEST_EXTENDED_ERROR;
    memcpy(Cmd, &tCmd, sizeof(PATA_COMMAND_CFA_REQUEST_EXTENDED_ERROR_CODE_STRUCTURE));
}

void AtaCoreEncodeCfaTranslateSectorCommand(
    PATA_COMMAND_CFA_TRANSLATE_SECTOR_STRUCTURE Cmd,
    UINT8                                       Dev,
    UINT32                                      Lba
){
    ATA_COMMAND_CFA_TRANSLATE_SECTOR_STRUCTURE tCmd = {0};
    AtaCoreEncodeLba28Common((PATA_COMMAND_GENERIC)&tCmd, Lba);
    tCmd.Device = (1 << 6) | ((Lba >> 24) & 0x0F);
    tCmd.Device |= Dev ? (1 << 4) : 0;
    tCmd.Command = ATA_COMMAND_CODE_CFA_TRANSLATE_SECTOR;
    memcpy(Cmd, &tCmd, sizeof(ATA_COMMAND_CFA_TRANSLATE_SECTOR_STRUCTURE));
}

void 
AtaCoreEncodeCfaWriteMultipleWithoutEraseCommand(
    PATA_COMMAND_CFA_WRITE_MULTIPLE_WITHOUGHT_ERASE_STRUCTURE   Cmd,
    UINT8                                                       Dev,
    UINT32                                                      Lba,
    UINT8                                                       SectorCount
){
    ATA_COMMAND_CFA_WRITE_MULTIPLE_WITHOUGHT_ERASE_STRUCTURE tCmd = {0};
    tCmd.SectorCount = SectorCount;
    AtaCoreEncodeLba28Common((PATA_COMMAND_GENERIC)&tCmd, Lba);
    tCmd.Device = (1 << 6) | ((Lba >> 24) & 0xFF);
    tCmd.Device |= Dev ? (1 << 4) : 0; 
    tCmd.Command = ATA_COMMAND_CODE_CFA_WRITE_MULTIPLE_WO_ERASE;
    memcpy(Cmd, &tCmd, sizeof(ATA_COMMAND_CFA_WRITE_MULTIPLE_WITHOUGHT_ERASE_STRUCTURE));
}

void 
AtaCoreEncodeCfaWriteSectorsWithoutEraseCommand(
    PATA_COMMAND_CFA_WRITE_SECTORS_WITHOUGHT_ERASE_STRUCTURE    Cmd,
    UINT8                                                       Dev,
    UINT32                                                      Lba,
    UINT8                                                       SectorCount
){
    ATA_COMMAND_CFA_WRITE_SECTORS_WITHOUGHT_ERASE_STRUCTURE tCmd = {0};
    tCmd.SectorCount = SectorCount;
    AtaCoreEncodeLba28Common((PATA_COMMAND_GENERIC)&tCmd, Lba);
    tCmd.Device = (1 << 6) | ((Lba >> 24) & 0xFF);
    tCmd.Device |= Dev ? (1 << 4) : 0; 
    tCmd.Command = ATA_COMMAND_CODE_CFA_WRITE_SECTORS_WOUT_ERASE;
    memcpy(Cmd, &tCmd, sizeof(ATA_COMMAND_CFA_WRITE_SECTORS_WITHOUGHT_ERASE_STRUCTURE));
}

void AtaCoreEncodeCheckMediaCardTypeCommand(
    PATA_COMMAND_CHECK_MEDIA_CARD_TYPE_STRUCTURE    Cmd,
    UINT8                                           Dev,
    UINT8                                           Enb
){
    ATA_COMMAND_CHECK_MEDIA_CARD_TYPE_STRUCTURE tCmd = {0};
    tCmd.Features = Enb ? 1 : 0;
    tCmd.Device = Dev ? (1 << 4) : 0;
    tCmd.Command = ATA_COMMAND_CODE_CHECK_MEDIA_CARD_TYPE;
    memcpy(Cmd, &tCmd, sizeof(ATA_COMMAND_CHECK_MEDIA_CARD_TYPE_STRUCTURE));
}

void AtaCoreEncodeCheckPowerModeCommand(
    PATA_COMMAND_CHECK_POWER_MODE_STRUCTURE Cmd,
    UINT8                                   Dev
){
    ATA_COMMAND_CHECK_POWER_MODE_STRUCTURE tCmd = {0};
    tCmd.Device = Dev ? (1 << 4) : 0;
    tCmd.Command = ATA_COMMAND_CODE_CHECK_POWER_MODE;
    memcpy(Cmd, &tCmd, sizeof(ATA_COMMAND_CHECK_POWER_MODE_STRUCTURE));
}

void AtaCoreEncodeConfigureStreamCommand(
    PATA_COMMAND_CONFIGURE_STREAM_STRUCTURE Cmd,
    UINT8                                   Dev,
    UINT8                                   Dcctl,
    UINT8                                   StreamID,
    UINT8                                   Rw,
    UINT8                                   Ar,
    UINT16                                  SectorCount
){
    ATA_COMMAND_CONFIGURE_STREAM_STRUCTURE tCmd = {0};
    tCmd.Features = ATA_CMDBLK_ENCODE_PREV_VALUE(Dcctl) | ATA_CMDBLK_ENCODE_CURR_VALUE(StreamID | (Rw << 6) | (Ar << 7));
    tCmd.SectorCount = ATA_CMDBLK_ENCODE_PREV_VALUE((SectorCount >> 8) & 0xF) | ATA_CMDBLK_ENCODE_CURR_VALUE(SectorCount & 0xFF); 
    tCmd.Device = (1 << 6);
    tCmd.Device |= Dev ? (1 << 4) : 0;
    tCmd.Command = ATA_COMMAND_CODE_CONFIGURE_STREAM;
    memcpy(Cmd, &tCmd, sizeof(ATA_COMMAND_CONFIGURE_STREAM_STRUCTURE));
}

void AtaCoreEncodeDeviceConfigurationRestoreCommand(
    PATA_COMMAND_DEVICE_CONFIGURATION_RESTORE_STRUCTURE Cmd,
    UINT8                                               Dev
){
    AtaCoreEncodeDeviceConfiguration(
        Cmd,
        Dev,
        0xC0 //restore
    );
}

void AtaCoreEncodeDeviceConfigurationFreezeLockCommand(
    PATA_COMMAND_DEVICE_CONFIGURATION_FREEZE_LOCK_STRUCTURE Cmd,
    UINT8                                                   Dev
){
    AtaCoreEncodeDeviceConfiguration(
        Cmd,
        Dev,
        0xC1 //freeze lock
    );
}

void AtaCoreEncodeDeviceConfigurationIdentifyCommand(
    PATA_COMMAND_DEVICE_CONFIGURATION_IDENTIFY_STRUCTURE    Cmd,
    UINT8                                                   Dev
){
    AtaCoreEncodeDeviceConfiguration(
        Cmd,
        Dev,
        0xC2 //Identify
    );
}

void AtaCoreEncodeDeviceConfigurationSetCommand(
    PATA_COMMAND_DEVICE_CONFIGURATION_SET_STRUCTURE     Cmd,
    UINT8                                               Dev
){
    AtaCoreEncodeDeviceConfiguration(
        Cmd,
        Dev,
        0xC3 //Set
    );
}

void
AtaCoreEncodeDeviceResetCommand(
    PATA_COMMAND_DEVICE_RESET_STRUCTURE Cmd,
    UINT8                               Dev    
){
    ATA_COMMAND_DEVICE_RESET_STRUCTURE tCmd = {0};
    tCmd.Device = Dev ? (1 << 4) : 0;
    tCmd.Command = ATA_COMMAND_CODE_DEVICE_RESET;
    memcpy(Cmd, &tCmd, sizeof(ATA_COMMAND_DEVICE_RESET_STRUCTURE));
}

void AtaCoreEncodeDownloadMicroCodeCommand(
    PATA_COMMAND_DOWNLOAD_MICROCODE_STRUCTURE   Cmd,
    UINT8                                       Dev,
    UINT8                                       SubCommandCode,
    UINT16                                      SectorCount
){
    ATA_COMMAND_DOWNLOAD_MICROCODE_STRUCTURE tCmd = {0};
    tCmd.Features = SubCommandCode;
    tCmd.SectorCount = SectorCount & 0xFF;
    tCmd.LbaLow = (SectorCount >> 8) & 0xFF;
    tCmd.Device = Dev ? (1 << 4) : 0;
    tCmd.Command = ATA_COMMAND_CODE_DOWNLOAD_MICROCODE;
    memcpy(Cmd, &tCmd, sizeof(ATA_COMMAND_DOWNLOAD_MICROCODE_STRUCTURE));
}

void 
AtaCoreEncodeExecuteDeviceDiagnosticsCommand(
    PATA_COMMAND_EXECUTE_DEVICE_DIAGNOSTIC  Cmd
){
    ATA_COMMAND_EXECUTE_DEVICE_DIAGNOSTIC tCmd = {0};
    tCmd.Command = ATA_COMMAND_CODE_EXECUTE_DEVICE_DIAGNOSTICS;
    memcpy(Cmd, &tCmd, sizeof(ATA_COMMAND_CODE_EXECUTE_DEVICE_DIAGNOSTICS));
}

void 
AtaCoreEncodeFlushCacheCommand(
    PATA_COMMAND_FLUSH_CACHE_STRUCTURE  Cmd,
    UINT8                               Dev
){
    ATA_COMMAND_FLUSH_CACHE_STRUCTURE tCmd = {0};
    tCmd.Device = Dev ? (1 << 4) : 0;
    tCmd.Command = ATA_COMMAND_CODE_FLUSH_CACHE;
    memcpy(Cmd, &tCmd, sizeof(ATA_COMMAND_FLUSH_CACHE_STRUCTURE));
}

void 
AtaCoreEncodeFlushCacheExCommand(
    PATA_COMMAND_FLUSH_CACHE_EX_STRUCTURE   Cmd,
    UINT8                                   Dev
){
    ATA_COMMAND_FLUSH_CACHE_EX_STRUCTURE tCmd = {0};
    tCmd.Device = Dev ? (1 << 4) : 0;
    tCmd.Command = ATA_COMMAND_CODE_FLUSH_CACHE_EXT;
    memcpy(Cmd, &tCmd, sizeof(ATA_COMMAND_FLUSH_CACHE_EX_STRUCTURE));
}

void 
AtaCoreEncodeGetMediaStatusCommand(
    PATA_COMMAND_GET_MEDIA_STATUS_STRUCTURE Cmd,
    UINT8                                   Dev
){
    ATA_COMMAND_GET_MEDIA_STATUS_STRUCTURE tCmd = {0};
    tCmd.Device = Dev ? (1 << 4) : 0;
    tCmd.Command = ATA_COMMAND_CODE_GET_MEDIA_STATUS;
    memcpy(Cmd, &tCmd, sizeof(ATA_COMMAND_GET_MEDIA_STATUS_STRUCTURE));
}

void 
AtaCoreEncodeIdentifyDeviceCommand(
    PATA_COMMAND_IDENTIFY_DEVICE_STRUCTURE Cmd,
    UINT8                                   Dev
){
    ATA_COMMAND_IDENTIFY_DEVICE_STRUCTURE tCmd = {0};
    tCmd.Device = Dev ? (1 << 4) : 0;
    tCmd.Command = ATA_COMMAND_CODE_IDENTIFY_DEVICE;
    memcpy(Cmd, &tCmd, sizeof(ATA_COMMAND_IDENTIFY_DEVICE_STRUCTURE));
}

void 
AtaCoreEncodeIdentifyPacketDeviceCommand(
    PATA_COMMAND_IDENTIFY_PACKET_DEVICE_STRUCTURE Cmd,
    UINT8                                   Dev
){
    ATA_COMMAND_IDENTIFY_PACKET_DEVICE_STRUCTURE tCmd = {0};
    tCmd.Device = Dev ? (1 << 4) : 0;
    tCmd.Command = ATA_COMMAND_CODE_IDENTIFY_PACKET_DEVICE;
    memcpy(Cmd, &tCmd, sizeof(ATA_COMMAND_IDENTIFY_PACKET_DEVICE_STRUCTURE));
}

void 
AtaCoreEncodeIdleCommand(
    PATA_COMMAND_IDLE_STRUCTURE Cmd,
    UINT8                       TimePeriod,
    UINT8                       Dev
){
    ATA_COMMAND_IDLE_STRUCTURE tCmd = {0};
    tCmd.Device = Dev ? (1 << 4) : 0;
    tCmd.SectorCount = TimePeriod;
    tCmd.Command = ATA_COMMAND_CODE_IDLE;
    memcpy(Cmd, &tCmd, sizeof(ATA_COMMAND_IDLE_STRUCTURE));
}

void 
AtaCoreEncodeIdleImmediateCommand(
    PATA_COMMAND_IDLE_IMMEDIATE_STRUCTURE   Cmd,
    UINT8                                   Dev
){
    ATA_COMMAND_IDLE_IMMEDIATE_STRUCTURE tCmd = {0}; 
    tCmd.Device = Dev ? (1 << 4) : 0;
    tCmd.Command = ATA_COMMAND_CODE_IDLE_IMMEDIATE;
    memcpy(Cmd, &tCmd, sizeof(ATA_COMMAND_IDLE_IMMEDIATE_STRUCTURE));
}

//continue 8.20