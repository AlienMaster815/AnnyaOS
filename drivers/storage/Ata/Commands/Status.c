#include "../AtaCore.h"

#define ATA_DEVICE_STATUS_OK(Status) ((!(Status & (1 << 0))) && (Status & (1 << 6)) && (!(Status & (1 << 7))))

static ATA_DEVICE_COMMAND_STATUS AtaCoreCheckUaMsMeRs(UINT8 Error){
    if(Error & (1 << 4)){
        return ATA_DEVICE_COMMAND_STATUS_USER_ACCESSABLE_ADDRESS_NOT_FOUND;
    }
    else if(Error & (1 << 2)){
        return ATA_DEVICE_COMMAND_STATUS_NOT_SUPPORTED;
    }
    else if(Error & (1 << 0)){
        return ATA_DEVICE_COMMAND_STATUS_MEDIA_ERROR;
    }
    return ATA_DEVICE_COMMAND_STATUS_NEEDS_RESET;
}

static ATA_DEVICE_COMMAND_STATUS AtaCoreCheckNsRs(UINT8 Error){
    if(Error & (1 << 2)){
        return ATA_DEVICE_COMMAND_STATUS_NOT_SUPPORTED;
    }
    return ATA_DEVICE_COMMAND_STATUS_NEEDS_RESET;
}

ATA_DEVICE_COMMAND_STATUS 
AtaCoreCheckCfaEraseSectorsStatus(
    PATA_COMMAND_CFA_ERASE_SECTORS_STRUCTURE Sts
){
    if(ATA_DEVICE_STATUS_OK(Sts->Status)){ //error bit
        return ATA_DEVICE_COMMAND_STATUS_SUCCESS;
    }
    return AtaCoreCheckUaMsMeRs(Sts->Error);
}

ATA_DEVICE_COMMAND_STATUS
AtaCoreCheckCfaRequestExtendedErrorCodeStatus(
    PATA_COMMAND_CFA_REQUEST_EXTENDED_ERROR_CODE_STRUCTURE  Sts
){
    if(ATA_DEVICE_STATUS_OK(Sts->Status)){
        return ATA_DEVICE_COMMAND_STATUS_SUCCESS; 
    }
    return AtaCoreCheckNsRs(Sts->Error);
}

ATA_DEVICE_COMMAND_STATUS
AtaCoreCheckCfaTranslateSectorStatus(
    PATA_COMMAND_CFA_TRANSLATE_SECTOR_STRUCTURE Sts
){
    if(ATA_DEVICE_STATUS_OK(Sts->Status)){
        return ATA_DEVICE_COMMAND_STATUS_SUCCESS;
    }
    return AtaCoreCheckNsRs(Sts->Error);
}

ATA_DEVICE_COMMAND_STATUS
AtaCoreCheckCfaWriteMultipleWithoughtEraseStatus(
    PATA_COMMAND_CFA_WRITE_MULTIPLE_WITHOUGHT_ERASE_STRUCTURE Sts
){  
    if(ATA_DEVICE_STATUS_OK(Sts->Status)){
        return ATA_DEVICE_COMMAND_STATUS_SUCCESS;
    }
    return AtaCoreCheckUaMsMeRs(Sts->Error);
}

ATA_DEVICE_COMMAND_STATUS
AtaCoreCheckCfaWriteSectorsWithoughtEraseStatus(
    PATA_COMMAND_CFA_WRITE_MULTIPLE_WITHOUGHT_ERASE_STRUCTURE Sts
){  
    if(ATA_DEVICE_STATUS_OK(Sts->Status)){
        return ATA_DEVICE_COMMAND_STATUS_SUCCESS;
    }
    return AtaCoreCheckUaMsMeRs(Sts->Error);
}

ATA_DEVICE_COMMAND_STATUS 
AtaCoreCheckMediaCardTypeStatus(
    PATA_COMMAND_CHECK_MEDIA_CARD_TYPE_STRUCTURE Sts
){
    if(ATA_DEVICE_STATUS_OK(Sts->Status) && (!(Sts->Status & (1 << 3)))){
        return ATA_DEVICE_COMMAND_STATUS_SUCCESS;
    }
    return AtaCoreCheckNsRs(Sts->Error);
}

ATA_DEVICE_COMMAND_STATUS 
AtaCoreCheckPowerModeStatus(
    PATA_COMMAND_CHECK_POWER_MODE_STRUCTURE Sts
){
    if(ATA_DEVICE_STATUS_OK(Sts->Status) && (!(Sts->Status & (1 << 3)))){
        return ATA_DEVICE_COMMAND_STATUS_SUCCESS;
    }
    return AtaCoreCheckNsRs(Sts->Error);
}

ATA_DEVICE_COMMAND_STATUS 
AtaCoreCheckConfigureStreamStatus(
    PATA_COMMAND_CONFIGURE_STREAM_STRUCTURE Sts
){
    if(ATA_DEVICE_STATUS_OK(Sts->Status) && (!(Sts->Status & (1 << 3)))){
        return ATA_DEVICE_COMMAND_STATUS_SUCCESS;
    }
    return AtaCoreCheckNsRs(Sts->Error);
}

ATA_DEVICE_COMMAND_STATUS
AtaCoreCheckDeviceConfigurationRestoreStatus(
    PATA_COMMAND_DEVICE_CONFIGURATION_RESTORE_STRUCTURE Sts
){
    if(ATA_DEVICE_STATUS_OK(Sts->Status) && (!(Sts->Status & (1 << 3)))){
        return ATA_DEVICE_COMMAND_STATUS_SUCCESS;
    }
    return AtaCoreCheckNsRs(Sts->Error);  
}

ATA_DEVICE_COMMAND_STATUS
AtaCoreCheckDeviceConfigurationFreezeLockStatus(
    PATA_COMMAND_DEVICE_CONFIGURATION_RESTORE_STRUCTURE Sts
){
    if(ATA_DEVICE_STATUS_OK(Sts->Status) && (!(Sts->Status & (1 << 3)))){
        return ATA_DEVICE_COMMAND_STATUS_SUCCESS;
    }
    return AtaCoreCheckNsRs(Sts->Error);  
}

ATA_DEVICE_COMMAND_STATUS
AtaCoreCheckDeviceConfigurationIdentifyStatus(
    PATA_COMMAND_DEVICE_CONFIGURATION_RESTORE_STRUCTURE Sts
){
    if(ATA_DEVICE_STATUS_OK(Sts->Status) && (!(Sts->Status & (1 << 3)))){
        return ATA_DEVICE_COMMAND_STATUS_SUCCESS;
    }
    return AtaCoreCheckNsRs(Sts->Error);  
}

ATA_DEVICE_COMMAND_STATUS
AtaCoreCheckDeviceConfigurationSetStatus(
    PATA_COMMAND_DEVICE_CONFIGURATION_RESTORE_STRUCTURE Sts
){
    if(ATA_DEVICE_STATUS_OK(Sts->Status) && (!(Sts->Status & (1 << 3)))){
        return ATA_DEVICE_COMMAND_STATUS_SUCCESS;
    }
    return AtaCoreCheckNsRs(Sts->Error);  
}

ATA_DEVICE_COMMAND_STATUS
AtaCoreCheckDownloadMicroCodeStatus(
    PATA_COMMAND_DOWNLOAD_MICROCODE_STRUCTURE Sts
){
    if(ATA_DEVICE_STATUS_OK(Sts->Status) && (!(Sts->Status & (1 << 3)))){
        return ATA_DEVICE_COMMAND_STATUS_SUCCESS;
    }
    return AtaCoreCheckNsRs(Sts->Error);  
}