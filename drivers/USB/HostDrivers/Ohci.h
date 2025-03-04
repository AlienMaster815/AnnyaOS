#ifndef _OHCI_H
#define _OHCI_H
#include "usb.h"

typedef struct _OPEN_HOST_CONTROLLER_INTERFACE{
    uint32_t HcRevision;
    uint32_t HcControl;
    uint32_t HcCommandStatus;
    uint32_t HcInterruptStatus;
    uint32_t HcInterruptEnable;
    uint32_t HcInterruptDisable;
    uint32_t HcHCCA;
    uint32_t HcPeriodicCurrentED;
    uint32_t HcControlHeadED;
    uint32_t HcControlCurrentED;
    uint32_t HcBulkHeadED;
    uint32_t HcBulkCurrentED;
    uint32_t HcDoneHead;
    uint32_t HcFmInternal;
    uint32_t HcFmRemaining;
    uint32_t HcFmNumber;
    uint32_t HcPeriodicStart;
    uint32_t HcLSThreshold;
    uint32_t HcRhDescriptorA;
    uint32_t HcRhDescriptorB;
    uint32_t HcRhStatus;
    uint32_t HcRhPortStatus[]; //Depends on the port count
}OPEN_HOST_CONTROLLER_INTERFACE, * POPEN_HOST_CONTROLLER_INTERFACE;


//Register Manipulation Offset
#define GET_OHCI_REGISTER_BITS(Register, BitOffset, BitCount) ((Register >> BitOffset) & ((1 << BitCount) - 1)) 
#define SET_OHCI_REGISTER_BITS(Register, Value, BitOffset, BitCount) (Register = ((Value & (1 << BitCount) - 1) << BitOffset))

//Revision Register Helpers
#define GET_OHCI_REVISION(OHCI)         GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRevision, 0 , 8)

//Control Register Helpers
#define GET_OHCI_CONTROL_CBSR(OHCI)                 GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcControl, 0, 2)
#define GET_OHCI_CONTROL_PLE(OHCI)                  GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcControl, 2, 1)
#define GET_OHCI_CONTROL_IE(OHCI)                   GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcControl, 3, 1)
#define GET_OHCI_CONTROL_CLE(OHCI)                  GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcControl, 4, 1)
#define GET_OHCI_CONTROL_BLE(OHCI)                  GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcControl, 5, 1)
#define GET_OHCI_CONTROL_HCFS(OHCI)                 GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcControl, 6, 2)
#define GET_OHCI_CONTROL_IR(OHCI)                   GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcControl, 8, 1)
#define GET_OHCI_CONTROL_RWC(OHCI)                  GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcControl, 9, 1)
#define GET_OHCI_CONTROL_RWE(OHCI)                  GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcControl, 10, 1)

#define GET_OHCI_CS_HCR(OHCI)                       GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcCommandStatus, 0, 1)
#define GET_OHCI_CS_CLF(OHCI)                       GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcCommandStatus, 1, 1)
#define GET_OHCI_CS_BLF(OHCI)                       GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcCommandStatus, 2, 1)
#define GET_OHCI_CS_OCR(OHCI)                       GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcCommandStatus, 3, 1)
#define GET_OHCI_CS_SOC(OHCI)                       GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcCommandStatus, 6, 2)

#define GET_OHCI_IS_SO(OHCI)                        GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcInterruptStatus, 0, 1)
#define GET_OHCI_IS_WDH(OHCI)                       GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcInterruptStatus, 1, 1)
#define GET_OHCI_IS_SF(OHCI)                        GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcInterruptStatus, 2, 1)
#define GET_OHCI_IS_RD(OHCI)                        GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcInterruptStatus, 3, 1)
#define GET_OHCI_IS_UE(OHCI)                        GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcInterruptStatus, 4, 1)
#define GET_OHCI_IS_FNO(OHCI)                       GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcInterruptStatus, 5, 1)
#define GET_OHCI_IS_RHSC(OHCI)                      GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcInterruptStatus, 6, 1)
#define GET_OHCI_IS_OC(OHCI)                        GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcInterruptStatus, 30, 1)

#define GET_OHCI_IE_SO(OHCI)                        GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcInterruptEnable, 0, 1)
#define GET_OHCI_IE_WDH(OHCI)                       GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcInterruptEnable, 1, 1)
#define GET_OHCI_IE_SF(OHCI)                        GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcInterruptEnable, 2, 1)
#define GET_OHCI_IE_RD(OHCI)                        GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcInterruptEnable, 3, 1)
#define GET_OHCI_IE_UE(OHCI)                        GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcInterruptEnable, 4, 1)
#define GET_OHCI_IE_FNO(OHCI)                       GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcInterruptEnable, 5, 1)
#define GET_OHCI_IE_RHSC(OHCI)                      GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcInterruptEnable, 6, 1)
#define GET_OHCI_IE_OC(OHCI)                        GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcInterruptEnable, 30, 1)
#define GET_OHCI_IE_MIE(OHCI)                       GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcInterruptEnable, 31, 1)

#define GET_OHCI_HCCA(OHCI)                         GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcHCCA, 8, 32 - 8)
#define GET_OHCI_PERIOD_CURRENT_ED(OHCI)            GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcPeriodicCurrentED, 4, 32 - 4)
#define GET_OHCI_CONTROL_HEAD_ED(OHCI)              GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcControlHeadED, 4, 32 - 4)
#define GET_OHCI_CONTROL_CURRENT_ED(OHCI)           GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcControlCurrentED, 4, 32 - 4)
#define GET_OHCI_BULK_HEAD_ED(OHCI)                 GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcBulkCurrentED, 4, 32 - 4)
#define GET_OHCI_DONE_HEAD(OHCI)                    GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcDoneHead, 4, 32 - 4)

#define GET_OHCI_FI_FI(OHCI)                        GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcFmInternal, 0, 14)
#define GET_OHCI_FI_FSMPS(OHCI)                     GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcFmInternal, 16, 15)
#define GET_OHCI_FI_FIT(OCHI)                       GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcFmInternal, 31, 1)

#define GET_OHCI_FR_FR(OHCI)                        GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcFmRemaining, 0, 14)
#define GET_OHCI_FR_FRT(OHCI)                       GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcFmRemaining, 31, 1)

#define GET_OHCI_FN(OHCI)                           GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcFmNumber, 0, 16)
#define GET_OHCI_PERIODIC_START(OHCI)               GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcPeriodicStart, 0, 14)
#define GET_OHCI_LS_THRESH_HOLD(OHCI)               GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcLSThreshold, 0, 12)

#define GET_OHCI_RDA_NDP(OHCI)                      GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhDescriptorA, 0, 8)
#define GET_OHCI_RDA_PSM(OHCI)                      GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhDescriptorA,  8, 1)
#define GET_OHCI_RDA_NPS(OHCI)                      GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhDescriptorA,  9, 1)
#define GET_OHCI_RDA_DT(OHCI)                       GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhDescriptorA,  10, 1)
#define GET_OHCI_RDA_OCPM(OHCI)                     GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhDescriptorA,  11, 1)
#define GET_OHCI_RDA_NOCP(OHCI)                     GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhDescriptorA,  12, 1)
#define GET_OHCI_RDA_POTPGT(OHCI)                   GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhDescriptorA,  24, 8)

#define GET_OHCI_RDB_DR(OHCI)                       GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhDescriptorB, 0, 16)
#define GET_OHCI_RDB_PPCM(OHCI)                     GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhDescriptorB, 16, 16)

#define GET_OHCI_RHS_LPS(OHCI)                      GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhStatus, 0, 1)
#define GET_OHCI_RHS_OCI(OHCI)                      GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhStatus, 1, 1)
#define GET_OHCI_RHS_DRWE(OHCI)                     GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhStatus, 15, 1)
#define GET_OHCI_RHS_LPSC(OHCI)                     GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhStatus, 16, 1)
#define GET_OHCI_RHS_OCIC(OHCI)                     GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhStatus, 17, 1)
#define GET_OHCI_RHS_CRWE(OHCI)                     GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhStatus, 31, 1)

#define GET_OHCI_RHPS_CCS(OHCI, PN)                 GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhPortStatus[PN], 0, 1)
#define GET_OHCI_RHPS_PES(OHCI, PN)                 GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhPortStatus[PN], 1, 1)
#define GET_OHCI_RHPS_PSS(OHCI, PN)                 GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhPortStatus[PN], 2, 1)
#define GET_OHCI_RHPS_POCI(OHCI, PN)                GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhPortStatus[PN], 3, 1)
#define GET_OHCI_RHPS_PRS(OHCI, PN)                 GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhPortStatus[PN], 4, 1)
#define GET_OHCI_RHPS_PPS(OHCI, PN)                 GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhPortStatus[PN], 8, 1)
#define GET_OHCI_RHPS_LSDA(OHCI, PN)                GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhPortStatus[PN], 9, 1)
#define GET_OHCI_RHPS_CSC(OHCI, PN)                 GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhPortStatus[PN], 16, 1)
#define GET_OHCI_PHPS_PESC(OHCI, PN)                GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhPortStatus[PN], 17, 1)
#define GET_OHCI_PHPS_PSSC(OHCI, PN)                GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhPortStatus[PN], 18, 1)
#define GET_OHCI_PHPS_OCIC(OHCI, PN)                GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhPortStatus[PN], 19, 1)
#define GET_OHCI_PHPS_PRSC(OHCI, PN)                GET_OHCI_REGISTER_BITS(((POPEN_HOST_CONTROLLER_INTERFACE)OHCI)->HcRhPortStatus[PN], 20, 1)

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

typedef struct __attribute__((packed)) _OHCI_ISOCHRONOUS_TRANSFER_DESCRIPTOR{
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

#define OHCI_NO_ERROR               0
#define OHCI_CRC_ERROR              1
#define OHCI_BIT_STUFFING_ERROR     2
#define OHCI_DTM_ERROR              3
#define OHCI_STALL_ERROR            4
#define OHCI_DNR_ERROR              5
#define OHCI_PID_CHECK_FAILED_ERROR 6
#define OHCI_UNEXPECTED_PID_ERROR   7
#define OHCI_DATA_OVERRUN_ERROR     8
#define OHCI_DATA_UNDERRUN_ERROR    9
#define OHCI_BUFFER_OVERRUN_ERROR   12
#define OHCI_BUFFER_UNDERRUN_ERROR  13
#define OHCI_NOT_ACCESSED_ERROR     14

typedef struct __attribute__((packed)) _HCCA_PARTITION{
    uint32_t HccaIDT[128/sizeof(uint32_t)];
    uint16_t HccaFrameNumber;
    uint16_t HccaPad1;
    uint32_t HccaDoneHead;
}HCCA_PARTITION, * PHCCA_PARTITION;

typedef struct _OHCI_HCD_PRIVATE_DATA{
    POPEN_HOST_CONTROLLER_INTERFACE Ohci;
    uint32_t                        DeviceSpecificFlags;
    uint32_t                        CDeviceSpecificFlags;
    OPEN_HOST_CONTROLLER_INTERFACE  OhciContext; //not a full context but this is usefull for operations if needed
}OHCI_HCD_PRIVATE_DATA, * POHCI_HCD_PRIVATE_DATA;

#define LousbHcdPrivToOhciPriv(Hcd) (POHCI_HCD_PRIVATE_DATA)((PLOUSB_HCD)Hcd)->PrivateData

#endif //_OHCI_H