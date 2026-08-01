#include "ScsiCore.h"

static LOUSTATUS ScsiCoreGetSksHmrError(
    PSSDD_SKS_HMR_ERROR SenseData,
    UINT16*             Arc
){
    if((!SenseData) || (!Arc)){
        return STATUS_INVALID_PARAMETER;
    }else if(!(SenseData->Sksv & (1 << 7))){
        return STATUS_INVALID_PARAMETER;
    }
    LouKeSwapEndianess(&SenseData->Arc, Arc, sizeof(UINT16));
    return STATUS_SUCCESS;
}

static
LOUSTATUS 
ScsiCoreGetSksNoSr(
    PSSDD_SKS_NO_SR SenseData,
    UINT16*         ProgressIndication
){
    if((!SenseData) || (!ProgressIndication)){
        return STATUS_INVALID_PARAMETER;
    }else if(!(SenseData->Sksv & (1 << 7))){
        return STATUS_INVALID_PARAMETER;
    }
    LouKeSwapEndianess(&SenseData->ProgressIndication, ProgressIndication, sizeof(UINT16));
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
    }else if((SenceData->DescriptorType != SSDD_TYPE_SENCE_KEY_SPECIFIC) || (SenceData->AdditionalLength != SSDD_TYPE_KEY_SPECIFIC_SIZE)){
        return STATUS_INVALID_PARAMETER;
    }else if((SenceData->SenceKeySpecific[0] & (1 << 7))){
        return STATUS_INVALID_PARAMETER;
    }
    memcpy(Out, SenceData->SenceKeySpecific, 3);
    return STATUS_SUCCESS;
}

LOUSTATUS
ScsiCoreGetSksIllegalRequest(
    PSSDD_SKS_ILLEGAL_REQUEST   SenseData,
    UINT8*                      BitPointer,
    UINT8*                      Bpv,
    UINT8*                      Reserved,
    UINT8*                      Cd,
    UINT16*                     FieldPointer
){
    if((!SenseData) || (!BitPointer) || (!Bpv) || (!Reserved) || (!Cd) || (!FieldPointer)){
        return STATUS_INVALID_PARAMETER;
    }
    if(!(SenseData->BpBpvCdSksv & (1 << 7))){
        return STATUS_INVALID_PARAMETER;
    }
    SSDD_SKS_ILLEGAL_REQUEST    tSenseData;
    UINT16                      Tmp16;
    memcpy(&tSenseData, SenseData, sizeof(SSDD_SKS_ILLEGAL_REQUEST));
    *BitPointer = tSenseData.BpBpvCdSksv      & 0b0111;
    *Bpv = (tSenseData.BpBpvCdSksv >> 3)      & 0b0001;
    *Reserved = (tSenseData.BpBpvCdSksv >> 4) & 0b0011;
    *Cd = (tSenseData.BpBpvCdSksv >> 6)       & 0b0001;
    LouKeSwapEndianess(&tSenseData.FieldPointer, FieldPointer, sizeof(UINT16));
    return STATUS_SUCCESS;
}

LOUSTATUS ScsiCoreGetSksHardwareError(PSSDD_SKS_HARDWARE_ERROR SenseData, UINT16* Arc){
    return ScsiCoreGetSksHmrError(SenseData, Arc); 
}

LOUSTATUS ScsiCoreGetSksMediumError(PSSDD_SKS_MEDIUM_ERROR SenseData, UINT16* Arc){
    return ScsiCoreGetSksHmrError(SenseData, Arc); 
}

LOUSTATUS ScsiCoreGetSksRecoverError(PSSDD_SKS_RECOVERED_ERROR SenseData, UINT16* Arc){
    return ScsiCoreGetSksHmrError(SenseData, Arc); 
}

LOUSTATUS ScsiCoreGetSksNoSense(PSSDD_SKS_NO_SENSE SenseData, UINT16* ProgressIndication){
    return ScsiCoreGetSksNoSr(SenseData, ProgressIndication);
}

LOUSTATUS ScsiCoreGetSksNotReady(PSSDD_SKS_NOT_READY SenseData, UINT16* ProgressIndication){
    return ScsiCoreGetSksNoSr(SenseData, ProgressIndication);
}

LOUSTATUS ScsiCoreGetSksCopyAborted(
    PSCSI_SKS_COPY_ABORTED  SenseData,
    UINT8*                  BitPointer,
    UINT8*                  Bpv,
    UINT8*                  Sd,
    UINT16*                 FieldPointer
){
    if((!SenseData) || (!BitPointer) || (!Bpv) || (!Sd) || (!FieldPointer)){
        return STATUS_INVALID_PARAMETER;
    }else if(!(SenseData->SksvSdBpvBitPointer & (1 << 7))){
        return STATUS_INVALID_PARAMETER;
    }
    SCSI_SKS_COPY_ABORTED tSenseData;
    memcpy(&tSenseData, SenseData, sizeof(SCSI_SKS_COPY_ABORTED));
    *BitPointer = tSenseData.SksvSdBpvBitPointer & 0b111;
    *Bpv = (tSenseData.SksvSdBpvBitPointer >> 3) & 0b1; 
    *Sd = (tSenseData.SksvSdBpvBitPointer >> 5) & 0b1;
    LouKeSwapEndianess(&tSenseData.FieldPointer, FieldPointer, sizeof(UINT16));
    return STATUS_SUCCESS;
}

LOUSTATUS ScsiCoreGetSksUnitAttention(
    PSCSI_SKS_UNIT_ATTENTION    SenseData,
    UINT8*                      Overflow
){
    if((!SenseData) || (!Overflow)){
        return STATUS_INVALID_PARAMETER;
    }
    if(!(SenseData->SksvOverflow & (1 << 7))){
        return STATUS_INVALID_PARAMETER;
    }
    *Overflow = SenseData->SksvOverflow & 0b01;
    return STATUS_SUCCESS;
}

LOUSTATUS 
ScsiCoreGetFieldReplaceableUnitSenceData(
    PSSDD_FIELD_REPLACEABLE_UNIT_STRUCTURE  SenceData,
    UINT8*                                  Fruc
){
    if((!SenceData) || (!Fruc)){
        return STATUS_INVALID_PARAMETER;
    }else if(SenceData->DescriptorType != SSDD_TYPE_FIELD_REPLACEABLE_UNIT){
        return STATUS_INVALID_PARAMETER;
    }
    *Fruc = SenceData->Fruc;
    return STATUS_SUCCESS;
}

LOUSTATUS
ScsiCoreGetProgressIndicationsData(
    PSSDD_PROGRESS_INDICATIONS_SENSE_DATA_STRUCTURE SenseData,
    UINT8*                                          SenseKey,
    UINT8*                                          Asc,
    UINT8*                                          AscQualifier,
    UINT16*                                         ProgressIndication
){
    if((!SenseData) || (!SenseKey) || (!Asc) || (!AscQualifier) || (!ProgressIndication)){
        return STATUS_INVALID_PARAMETER;
    }else if((SenseData->DescriptorType != 0x0A) || (SenseData->AdditionalLength != 0x06)){
        return STATUS_INVALID_PARAMETER;
    }
    *SenseKey = SenseData->SenseKey;
    *Asc = SenseData->Asc;
    *AscQualifier = SenseData->AscQualifier;
    LouKeSwapEndianess(&SenseData->ProgressIndication, ProgressIndication, sizeof(UINT16));
    return STATUS_SUCCESS;
}

LOUSTATUS 
ScsiCoreGetVendorSpecificSenseData(
    PSSDD_VENDOR_SPECIFIC_SENSE_DATA_DESCRIPTOR_FORMAT_STRUCTURE    SenseData,
    UINT8*                                                          OutData,
    SIZE                                                            OutLength
){
    if((!SenseData) || (!OutData)){
        return STATUS_INVALID_PARAMETER;
    }else if(SenseData->DescriptorType <= 0x80){
        return STATUS_INVALID_PARAMETER;
    }
    LouKeSwapEndianess(SenseData->Data, OutData, OutLength);
    return STATUS_SUCCESS;
}