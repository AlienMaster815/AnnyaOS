#ifndef _OHCI_H
#define _OHCI_H
#include <LouDDK.h>

#pragma pack(push, 1)
typedef struct _OPEN_HOST_CONTROLLER{
    uint32_t Revision;
    uint32_t Control;
    uint32_t CommandStatus;
    uint32_t InterruptStatus;
    uint32_t InterruptEnable;
    uint32_t HCCA;
    uint32_t PeriodCurrentED;
    uint32_t ControlHeadED;
    uint32_t ControlCurrentED;
    uint32_t BulkHeadED;
    uint32_t BulkCurrentED;
    uint32_t DoneHead;
    uint32_t FmInterval;
    uint32_t FmRemaining;
    uint32_t FmNumber;
    uint32_t PeriodicStart;
    uint32_t LSThreashold;
    uint32_t RhDescriptorA;
    uint32_t RhDescriptorB;
    uint32_t RhStatus;
}OPEN_HOST_CONTROLLER, * POPEN_HOST_CONTROLLER;

typedef struct _OHCI_ENDPOINT_DESCRIPTOR{
    uint32_t FA_EN_D_S_K_F_MPS;
    uint32_t TDQueuedTailPointer;
    uint32_t H_C_TDQueuedHeadPointer;
    uint32_t NextEndpointDescriptor;
}OHCI_ENDPOINT_DESCRIPTOR, * POHCI_ENDPOINT_DESCRIPTOR; 

typedef struct _OHCI_TRANSFER_DESCRIPTOR{
    uint32_t R_DP_DI_T_EC_CC;
    uint32_t CurrentBufferPointer;
    uint32_t NextTransferDescriptor;
    uint32_t BufferEnd;
}OHCI_TRANSFER_DESCRIPTOR, * POHCI_TRANSFER_DESCRIPTOR;

typedef struct _OHCI_ISOCHRONOUS_TRANSFER_DESCRIPTOR{
    uint32_t SF_DI_FC_CC;
    uint32_t BuferPage0;
    uint32_t NextTransferDescriptor;
    uint32_t BufferEnd;
    uint16_t PSW[8];
}OHCI_ISOCHRONOUS_TRANSFER_DESCRIPTOR, * POHCI_ISOCHRONOUS_TRANSFER_DESCRIPTOR;

static inline LOUSTATUS InitializeGeneralEndpointDescriptor(
    POHCI_ENDPOINT_DESCRIPTOR EndpointDescriptor,
    uint8_t FunctionAddress,
    uint8_t EndpointNumber,
    uint8_t Direction,
    bool Speed,
    bool Skip,
    bool Format,
    uint16_t MaximumPacketSize,
    uint32_t TDQueuedTailPointer,
    bool Halted,
    bool ToggleCarry,
    uint32_t TDQueuedHeadPointer,
    uint32_t NextEndpointDescriptor
){
    if(
        (EndpointNumber & 0xF0) || (FunctionAddress & (1 << 7)) ||
        (Direction > 0x03) || (MaximumPacketSize > 0x3FF) || 
        (TDQueuedTailPointer & 0x0F) || (TDQueuedHeadPointer & 0x0F) ||
        (NextEndpointDescriptor & 0x0F) || (!EndpointDescriptor)
    ){
        return STATUS_INVALID_PARAMETER;
    }
    //DWORD 0
    EndpointDescriptor->FA_EN_D_S_K_F_MPS  = (uint32_t)FunctionAddress;
    EndpointDescriptor->FA_EN_D_S_K_F_MPS |= (uint32_t)EndpointNumber  << 7;
    EndpointDescriptor->FA_EN_D_S_K_F_MPS |= (uint32_t)Direction  << 11;//0
    EndpointDescriptor->FA_EN_D_S_K_F_MPS |= (uint32_t)Speed  ? 1 << 13 : 0;
    EndpointDescriptor->FA_EN_D_S_K_F_MPS |= (uint32_t)Skip   ? 1 << 14 : 0;
    EndpointDescriptor->FA_EN_D_S_K_F_MPS |= (uint32_t)Format ? 1 << 15 : 0;
    EndpointDescriptor->FA_EN_D_S_K_F_MPS |= (uint32_t)MaximumPacketSize << 16;
    //DWORD 1
    EndpointDescriptor->TDQueuedTailPointer = (uint32_t)TDQueuedTailPointer;
    //DWORD 2
    EndpointDescriptor->H_C_TDQueuedHeadPointer  = 0;
    EndpointDescriptor->H_C_TDQueuedHeadPointer |= Halted ? 1 : 0;
    EndpointDescriptor->H_C_TDQueuedHeadPointer |= ToggleCarry ? (1 << 1) : 0;
    EndpointDescriptor->H_C_TDQueuedHeadPointer |= TDQueuedHeadPointer;
    //DWORD 3
    EndpointDescriptor->NextEndpointDescriptor = NextEndpointDescriptor;

    return STATUS_SUCCESS;
}

#define OHCI_ENDPOINT_DIRECTION_GET_FROM_TD  0b00
#define OHCI_ENDPOINT_DIRECTION_OUT          0b01
#define OHCI_ENDPOINT_DIRECTION_IN           0b10
#define OHCI_ENDPOINT_DIRECTION_GET_FROM_TD2 0b11

#define OHCI_ENDPOINT_SPEED_FAST false
#define OHCI_ENDPOINT_SPEED_SLOW true

#define OHCI_ENDPOINT_FORMAT_GENERAL        false
#define OHCI_ENDPOINT_FORMAT_ISOCHRONOUS    true

#pragma pack(pop)

#endif //_OHCO_H