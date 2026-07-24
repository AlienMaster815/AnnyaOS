#include "ScsiCore.h"

void ScsiCoreEncodeCdb12Command(
    PSCSI_CDB12_COMMAND Cdb,
    UINT8               OpCode,
    UINT8               ServiceActionMci,
    UINT32              Lba,
    UINT32              TpaLength,
    UINT8               Mci,
    UINT8               Control
){
    UINT32 Tmp32;
    SCSI_CDB12_COMMAND tCdb = {0};
    tCdb.OpCode = OpCode;
    tCdb.ServiceActionMci = ServiceActionMci;
    LouKeSwapEndianess(&Lba, &Tmp32, sizeof(UINT32));
    tCdb.Lba = Tmp32;
    LouKeSwapEndianess(&TpaLength, &Tmp32, sizeof(UINT32));
    tCdb.TpaLength = Tmp32;
    tCdb.Mci = Mci;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_CDB12_COMMAND));
}