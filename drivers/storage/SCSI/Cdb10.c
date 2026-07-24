#include "ScsiCore.h"

void ScsiCoreEncodeCdb10Command(
    PSCSI_CDB10_COMMAND Cdb,
    UINT8               OpCode,
    UINT8               ServiceActionMci,
    UINT32              Lba,
    UINT8               Mci,
    UINT16              TpaLength,
    UINT8               Control
){
    UINT32 Tmp32;
    UINT16 Tmp16;
    SCSI_CDB10_COMMAND tCdb = {0};
    tCdb.OpCode = OpCode;
    tCdb.ServiceActionMci = ServiceActionMci;
    LouKeSwapEndianess(&Lba, &Tmp32, sizeof(UINT32));
    tCdb.Lba = Tmp32;
    tCdb.Mci = Mci;
    LouKeSwapEndianess(&TpaLength, &Tmp16, sizeof(UINT16));
    tCdb.TpaLength = Tmp16;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_CDB10_COMMAND));
}
