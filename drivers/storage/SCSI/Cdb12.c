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
    SCSI_CDB12_COMMAND tCdb = {0};
    tCdb.OpCode = OpCode;
    tCdb.ServiceActionMci = ServiceActionMci;
    tCdb.Lba = ScsiCoreEncodeUint32(Lba);
    tCdb.TpaLength = ScsiCoreEncodeUint32(TpaLength);
    tCdb.Mci = Mci;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_CDB12_COMMAND));
}

void ScsiCoreEncodeRead12Command(
    PSCSI_READ12_COMMAND_STRUCTURE  Cdb,
    UINT8                           Rarc,
    UINT8                           Fua,
    UINT16                          Dpo,
    UINT8                           RdProtect,
    UINT32                          Lba,
    UINT32                          TransferLength,
    UINT8                           GroupNumber,
    UINT8                           Control
){
    SCSI_READ12_COMMAND_STRUCTURE tCdb = {0};
    tCdb.RarcFuaDpoRdprotect = ((Rarc << 2) | (Fua << 3) | (Dpo << 4) | (RdProtect << 5));
    tCdb.Lba = ScsiCoreEncodeUint32(Lba);
    tCdb.TransferLength = ScsiCoreEncodeUint32(TransferLength); 
    tCdb.GroupNumberMmc6 = GroupNumber;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_READ12_COMMAND_STRUCTURE));
}

