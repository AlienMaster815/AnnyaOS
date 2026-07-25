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
    *Out = ((CommandCode & 0b1111) | ((GroupCode & 0b111) << 5));
    return STATUS_SUCCESS;
}

LOUSTATUS
ScsiCoreEncodeControl(
    UINT8*  Out,
    UINT8   VendorSpecific,
    UINT8   Reserved,
    UINT8   Naca,
    UINT8   Obsolete1,
    UINT8   Obsolete0
){
    if(
        (!Out) || (VendorSpecific > 0b11) || 
        (Reserved > 0b0111) || (Naca > 0b01) || 
        ((Obsolete1 > 0b01) || (Obsolete0 > 0b01))
    ){
        return STATUS_INVALID_PARAMETER;
    }
    *Out = ((VendorSpecific << 6) | (Reserved << 3) | (Naca << 2) | (Obsolete1 << 1) | (Obsolete0 << 1));
    return STATUS_SUCCESS;
}
