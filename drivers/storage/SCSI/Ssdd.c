#include "ScsiCore.h"

static LOUSTATUS ScsiCoreGetSksHmrError(
    PSSDD_SKS_HMR_ERROR Cdb,
    UINT16*             Arc
){
    if((!Cdb) || (!Arc)){
        return STATUS_INVALID_PARAMETER;
    }else if(!(Cdb->Sksv & (1 << 7))){
        return STATUS_INVALID_PARAMETER;
    }
    UINT16 Tmp16;
    LouKeSwapEndianess(&Cdb->Arc, &Tmp16, sizeof(UINT16));
    *Arc = Tmp16;
    return STATUS_SUCCESS;
}


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

LOUSTATUS
ScsiCoreGetSksIllegalRequest(
    PSSDD_SKS_ILLEGAL_REQUEST   Cdb,
    UINT8*                      BitPointer,
    UINT8*                      Bpv,
    UINT8*                      Reserved,
    UINT8*                      Cd,
    UINT16*                     FieldPointer
){
    if((!Cdb) || (!BitPointer) || (!Bpv) || (!Reserved) || (!Cd) || (!FieldPointer)){
        return STATUS_INVALID_PARAMETER;
    }
    if(!(Cdb->BpBpvCdSksv & (1 << 7))){
        return STATUS_INVALID_PARAMETER;
    }
    SSDD_SKS_ILLEGAL_REQUEST    tCdb;
    UINT16                      Tmp16;
    memcpy(&tCdb, Cdb, sizeof(SSDD_SKS_ILLEGAL_REQUEST));
    *BitPointer = tCdb.BpBpvCdSksv      & 0b0111;
    *Bpv = (tCdb.BpBpvCdSksv >> 3)      & 0b0001;
    *Reserved = (tCdb.BpBpvCdSksv >> 4) & 0b0011;
    *Cd = (tCdb.BpBpvCdSksv >> 6)       & 0b0001;
    LouKeSwapEndianess(&tCdb.FieldPointer, &Tmp16, sizeof(UINT16));
    *FieldPointer = Tmp16;
    return STATUS_SUCCESS;
}

LOUSTATUS ScsiCoreGetSksHardwareError(PSSDD_SKS_HARDWARE_ERROR Cdb, UINT16* Arc){
    return ScsiCoreGetSksHmrError(Cdb, Arc); 
}

LOUSTATUS ScsiCoreGetSksMediumError(PSSDD_SKS_MEDIUM_ERROR Cdb, UINT16* Arc){
    return ScsiCoreGetSksHmrError(Cdb, Arc); 
}

LOUSTATUS ScsiCoreGetSksRecoverError(PSSDD_SKS_RECOVERED_ERROR Cdb, UINT16* Arc){
    return ScsiCoreGetSksHmrError(Cdb, Arc); 
}
