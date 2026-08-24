#include "../AtaCore.h"

void AtaCoreEncodeCfaEraseSectorsCommand(
    PATA_COMMAND_CFA_ERASE_SECTORS_STRUCTURE    Cmd,
    UINT8                                       Dev,
    UINT32                                      Lba,
    UINT8                                       SectorCount
){
    ATA_COMMAND_CFA_ERASE_SECTORS_STRUCTURE tCmd = {0};
    tCmd.Features = 0x00;
    tCmd.SectorCount = SectorCount;
    tCmd.LbaLow = Lba & 0xFF;
    tCmd.LbaMid = (Lba >> 8) & 0xFF; 
    tCmd.LbaHigh = (Lba >> 16) & 0xFF;
    tCmd.Device = (1 << 6) | (Lba >> 24) & 0x0F;
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