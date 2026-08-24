#include "../AtaCore.h"

#define ATA_DEVICE_STATUS_OK(Status) ((!(Status & (1 << 0))) && (Status & (1 << 6)) && (!(Status & (1 << 7))))

ATA_DEVICE_COMMAND_STATUS 
AtaCoreCheckCfaEraseSectorsStatus(
    PATA_COMMAND_CFA_ERASE_SECTORS_STRUCTURE Sts
){
    UINT8 Status = Sts->Status;
    UINT8 Error = Sts->Error;
    if(ATA_DEVICE_STATUS_OK(Status)){ //error bit
        return ATA_DEVICE_COMMAND_STATUS_SUCCESS;
    }else{
        if(Error & (1 << 4)){
            return ATA_DEVICE_COMMAND_STATUS_USER_ACCESSABLE_ADDRESS_NOT_FOUND;
        }
        else if(Status & (1 << 2)){
            return ATA_DEVICE_COMMAND_STATUS_NOT_SUPPORTED;
        }
        else if(Error & (1 << 0)){
            return ATA_DEVICE_COMMAND_STATUS_MEDIA_ERROR;
        }
    }
    return ATA_DEVICE_COMMAND_STATUS_NEEDS_RESET;
}

ATA_DEVICE_COMMAND_STATUS
AtaCoreCheckCfaRequestExtendedErrorCode(
    PATA_COMMAND_CFA_REQUEST_EXTENDED_ERROR_CODE_STRUCTURE  Sts
){
    if(ATA_DEVICE_STATUS_OK(Sts->Status)){
        return ATA_DEVICE_COMMAND_STATUS_SUCCESS; 
    }else if(Sts->Error & (1 << 2)){
        return ATA_DEVICE_COMMAND_STATUS_NOT_SUPPORTED;
    }
    return ATA_DEVICE_COMMAND_STATUS_NEEDS_RESET;
}