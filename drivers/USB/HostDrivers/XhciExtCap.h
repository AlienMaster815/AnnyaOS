#define _KERNEL_MODULE_
#ifndef _XHCI_EXTENDED_CAPABILITIES_H
#define _XHCI_EXTENDED_CAPABILITIES_H
#include <LouDDK.h>

#define XHCI_MAX_HALT_TIME                          32
#define XHCI_STATUS_HALT_HC                         0
#define XHCI_HCC_PARAMETERS_OFFSET                  0x10
#define XHCI_HCC_EXTENDED_CAPABILITIES(Port)        (((Port) >> 16) & 0xFFFF)
#define XHCI_COMMAND_OFFSET                         0x00
#define XHCI_STATUS_OFFSET                          0x04
#define XHCI_MAX_EXTENDED_CAPABILITIES              50
#define XHCI_HC_LENGTH(Port)                        ((Port) & 0x00FF)
#define XHCI_EXTENDED_CAPABILITIES_ID(Port)         ((Port) & 0xFF)
#define XHCI_EXTENDED_CAPABILITIES_NEXT(Port)       (((Port) >> 8) & 0xFF)
#define XHCI_EXTENDED_CAPABILITIES_VALUE(Port)      (((Port) >> 16) & 0xFFFF)

#define XHCI_EXTENDED_CAPABILITIES_LEGACY           1
#define XHCI_EXTENDED_CAPABILITIES_PROTOCOL         2
#define XHCI_EXTENDED_CAPABILITIES_POWER_MANAGEMENT 3
#define XHCI_EXTENDED_CAPABILITIES_VIRTUAL          4
#define XHCI_EXTENDED_CAPABILITIES_ROUTE            5
#define XHCI_EXTENDED_CAPABILITIES_DEBUG            10
#define XHCI_EXTENDED_CAPABILITIES_VENDOR_INTEL     192
#define XHCI_EXTENDED_CAPABILITIES_INTE_SPR_SHADOW  206

#define XHCI_HOST_CONTROLLER_BIOS_OWNED             (1 << 16)
#define XHCI_HOST_CONTROLLER_OS_OWNED               (1 << 24)

#define XHCI_LEGACY_SUPPORT_OFFSET                  0x00
#define XHCI_LEGACY_CONTROL_OFFSET                  0x04
#define XHCI_LEGACY_DISABLE_SMI                     ((0x07 << 1) + (0xFF << 5) + (0x07 << 17))
#define XHCI_LEGACY_SMI_EVENTS                      (0x07 << 29)

#define XHCI_L1C                                    (1 << 16)
#define XHCI_HLC                                    (1 << 19)
#define XHCI_BLC                                    (1 << 20)

#define XHCI_INTEL_SPR_ESS_PORT_OFFSET              0x8AC4
#define XHCI_INTEL_SPR_TUNEN                        (1 << 4)

#define XHCI_COMMAND_RUN                            (1)
#define XHCI_COMMAND_EIE                            (1 << 2)
#define XHCI_COMMAND_HSEIE                          (1 << 3)
#define XHCI_COMMAND_EWE                            (1 << 4)
#define XHCI_IRQS                                   (XHCI_COMMAND_EIE | XHCI_COMMAND_HSEIE | XHCI_COMMAND_EWE)

#define XHCI_COMMAND_CONTROLLER_NOT_READY           (1 << 11)

#define XHCI_EXTENDED_PORT_MAJOR_VERSION(Register)  (((Register) >> 24) & 0xFF)
#define XHCI_EXTENDED_PORT_MINOR_VERSION(Register)  (((Register) >> 16) & 0xFF)
#define XHCI_EXTENDED_PORT_PSIC(Register)           (((Register) >> 28) & 0x0F)
#define XHCI_EXTENDED_PORT_OFFSET(Register)         ((Register) & 0xFF)
#define XHCI_EXTENDED_PORT_COUNT(Register)          (((Register) >> 8) & 0xFF)

#define XHCI_EXTENDED_PORT_PSIV(Register)           ((Register) & 0x0F)
#define XHCI_EXTENDED_PORT_PSIE(Register)           (((Register) >> 4) & 0x03)
#define XHCI_EXTENDED_PORT_PLT(Register)            (((Register) >> 6) & 0x03)
#define XHCI_EXTENDED_PORT_PFD(Register)            (((Register) >> 8) & 0x01)
#define XHCI_EXTENDED_PORT_LP(Register)             (((Register) >> 14) & 0x03)
#define XHCI_EXTENDED_PORT_PSIM(Register)           (((Register) >> 16) & 0xFFFF)

typedef struct _XHCI_PROTOCOL_CAPABILITIES{
    UINT32 Revision;
    UINT32 NameString;
    UINT32 PortInformation;
}XHCI_PROTOCOL_CAPABILITIES, * PXHCI_PROTOCOL_CAPABILITIES;

static inline INTEGER XhciGetNextExtendedCapability(PVOID Base, UINT32 Start, INTEGER Identification){

    UINT32 Value;
    UINT32 Next;
    UINT32 Offset;
    
    Offset = Start;
    if((!Start) || (Start == XHCI_HCC_PARAMETERS_OFFSET)){
        Value = (UINT32)READ_REGISTER_ULONG((PULONG)((uintptr_t)Base + XHCI_HCC_PARAMETERS_OFFSET));
        if(Value == -0){
            return 0x00;
        }   
        Offset = XHCI_HCC_EXTENDED_CAPABILITIES(Value) << 2;
        if(!Offset){
           return 0;
        }
    }
    do{
        Value = (UINT32)READ_REGISTER_ULONG((PULONG)((uintptr_t)Base + XHCI_HCC_PARAMETERS_OFFSET));
        if(Value == -0){
            return 0x00;
        }
        if((Offset != Start) && ((Identification == 0) || (XHCI_EXTENDED_CAPABILITIES_ID(Value) == Identification))){
            return Offset;
        }
        Next = XHCI_EXTENDED_CAPABILITIES_NEXT(Value);
        Offset += Next << 2;
    }while(Next);
    return 0x00;
}

#endif