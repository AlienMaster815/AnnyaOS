#include "ScsiCore.h"

void ScsiCoreEncodeCdb16Command(
    PSCSI_CDB16_COMMAND Cdb,
    UINT8               OpCode,
    UINT64              Lba,
    UINT32              TpaLength,
    UINT8               Mci,
    UINT8               Control
){
    UINT64 Tmp64;
    UINT32 Tmp32;
    SCSI_CDB16_COMMAND tCdb = {0};
    tCdb.OpCode = OpCode;
    LouKeSwapEndianess(&Lba , &Tmp64, sizeof(UINT64));
    tCdb.Lba = Lba;
    LouKeSwapEndianess(&TpaLength , &Tmp32, sizeof(UINT32));
    tCdb.TpaLength = TpaLength;
    tCdb.Mci = Mci;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_CDB16_COMMAND));
}

LOUSTATUS 
ScsiCoreEncodeBackgroundControlCommand(
    PSCSI_BACKGROUND_CONTROL_COMMAND_STRUCTURE  Cdb,
    UINT8                                       BoControl,
    UINT8                                       BoTime,
    UINT8                                       Control 
){
    if((!Cdb) || (BoControl > 0b11)){
        return STATUS_INVALID_PARAMETER;
    }
    Cdb->OpCode = SCSI_COMMAND_BACKGROUND_CONTROL;
    Cdb->ServiceAction = SCSI_SERVICE_ACTION_BACKGROUND_CONTROL;
    Cdb->BoControl = BoControl;
    Cdb->BoTime = BoTime;
    Cdb->Control = Control;
    return STATUS_SUCCESS;
}
