#include "ScsiCore.h"

LOUSTATUS
ScsiCoreGetInfoSenceDataInformation(
    PSSDD_INFO_STRUCTURE    SenceData,
    UINT64*                 Out
){
    if((!SenceData) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }else if((SenceData->DescriptorType != SSDD_TYPE_INFO) || (SenceData->AdditionalLength != SSDD_TYPE_INFO_SIZE)){
        return STATUS_INVALID_PARAMETER;
    }else if(!(SenceData->ReservedValid & (1 << 7))){
        return STATUS_INVALID_PARAMETER;
    }
    LouKeSwapEndianess(&SenceData->Information, Out, sizeof(UINT64));
    return STATUS_SUCCESS;
}

LOUSTATUS
ScsiCoreGetCommandSpecificInfoSenceDataInformation(
    PSSDD_COMMAND_SPECIFIC_INFO_STRUCTURE   SenceData,
    UINT64*                                 Out
){
    if((!SenceData) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }else if((SenceData->DescriptorType != SSDD_TYPE_COMMAND_SPECIFIC_INFO) || (SenceData->AdditionalLength != SSDD_TYPE_COMMAND_SPECIFIC_INFO_SIZE)){
        return STATUS_INVALID_PARAMETER;
    }
    LouKeSwapEndianess(&SenceData->Information, Out, sizeof(UINT64));
    return STATUS_SUCCESS;
}

LOUSTATUS
ScsiCoreGetSenceKeySpecificSenceData(
    PSSDD_SENCE_KEY_SPECIFIC_STRUCTURE      SenceData,
    UINT8*                                  Out
){
    if((!SenceData) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }else if((SenceData->DescriptorType != SSDD_SENCE_KEY_SPECIFIC) || (SenceData->AdditionalLength != SSDD_TYPE_KEY_SPECIFIC_SIZE)){
        return STATUS_INVALID_PARAMETER;
    }else if((SenceData->SenceKeySpecific[0] & (1 << 7))){
        return STATUS_INVALID_PARAMETER;
    }
    memcpy(Out, SenceData->SenceKeySpecific, 3);
    return STATUS_SUCCESS;
}