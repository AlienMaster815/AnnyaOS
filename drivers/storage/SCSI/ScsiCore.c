#include "ScsiCore.h"

/*==================================================================
// [ Device Registered & Probe Initialized]
//                     |
//         [ Send INQUIRY Command ]
//                     |
//         --------------------------
//         |                        |
//  (STATUS_SUCCESS)     (STATUS_IO_DEVICE_ERROR)
//         |                        |
//[ Device Is Ready ]   [Send REQUEST_SENSE Command]
//                                  |
//                         [Inspect Sense Key]
//                                  |
//                     ------------------------------
//                     |                            |
//              (NOT_READY Key)           (UNIT_ATTENTION Key)
//                     |                            |
//          [ Senc START_STOP_UNIT ]    [ Clear Conditon Retry ]
===================================================================*/

DRIVER_EXPORT LOUSTATUS ScsiCoreEncodeLunAddressingLevel(
    PLONG_MODE_LUN_STRUCTURE    Lun, 
    UINT16                      FirstLevel,
    UINT16                      SecondLevel,
    UINT16                      ThirdLevel,
    UINT16                      FourthLevel
){
    Lun->AddressingLevels[0] = ScsiCoreEncodeUint16(FirstLevel);
    Lun->AddressingLevels[1] = ScsiCoreEncodeUint16(SecondLevel);
    Lun->AddressingLevels[2] = ScsiCoreEncodeUint16(ThirdLevel);
    Lun->AddressingLevels[3] = ScsiCoreEncodeUint16(FourthLevel);
}


static BOOLEAN ScsiCoreDebugOn = false;

void ScsiCoreDbgPrint(char* format, ...){
    if(ScsiCoreDebugOn){
        va_list args;
        va_start(args, format);
        LouPrintEx(format, args);
        va_end(args);
    }
}


LOUSTATUS ScsiCoreEntry(){
    HANDLE ScsiDebugKey = LouKeOpenRegistryHandle(L"KERNEL_DEFAULT_CONFIG\\DEBUG\\SCSI_CORE_DEBUG", 0x00);
    BYTE DbgValue = 0;
    LouKeReadRegistryByteValue(ScsiDebugKey, &DbgValue);
    ScsiCoreDebugOn = DbgValue ? true : false;
    
    ScsiCoreDbgPrint("SCSICORE.SYS:ScsiCoreEntry()\n");



    ScsiCoreDbgPrint("SCSICORE.SYS:ScsiCoreEntry():STATUS_SUCCESS\n");
    //while(1);
    return STATUS_SUCCESS;
}