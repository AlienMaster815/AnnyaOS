#include "ScsiCore.h"

LOUSTATUS
ScsiCoreEncodeOpCode(
    UINT8*  Out, 
    UINT8   CommandCode, 
    UINT8   GroupCode
){
    if((!Out) || (CommandCode > 0b1111) || (GroupCode > 0b111)){
        return STATUS_INVALID_PARAMETER;
    }
    *Out = CommandCode & 0b1111;
    *Out |= (GroupCode & 0b111) << 5;
    return STATUS_SUCCESS;
}



