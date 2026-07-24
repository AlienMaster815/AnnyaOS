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

