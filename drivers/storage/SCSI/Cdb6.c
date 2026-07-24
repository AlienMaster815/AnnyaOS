#include "ScsiCore.h"

void ScsiCoreEncodeCdb6Command(
    PSCSI_CDB6_COMMAND  Cdb,
    UINT8               OpCode,
    UINT8               MsbMci,
    UINT16              Lba,
    UINT8               TpaLength,
    UINT8               Control 
){
    UINT16 Tmp16;
    SCSI_CDB6_COMMAND tCdb = {0};
    tCdb.OpCode = OpCode;
    tCdb.MsbMci = MsbMci;
    tCdb.Lba = Lba;
    LouKeSwapEndianess(&TpaLength, &Tmp16, sizeof(UINT16));
    tCdb.TpaLength = Tmp16;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_CDB6_COMMAND));
}
