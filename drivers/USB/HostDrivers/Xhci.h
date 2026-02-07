#ifndef _XHCI_H
#define _XHCI_H
#define _KERNEL_MODULE_
#include <LouDDK.h>

//ASYNC for controll and bulk
//ISOCH for Interrupt and periodic

//BAR points to Cap Register and following is the operational regs
//XHCI Extended Cap register as well as runtime and doorbell is pointed from Cap and 

typedef struct PACKED _XHCI_CAPABILITIES_REGISTER{
    UINT8       CapLength;
    UINT8       Reserved1;
    UINT16      HciVersion;
    UINT32      HcsParams1;
    UINT32      HcsParams2;
    UINT32      HcsParams3;
    UINT32      HccParams1;
    UINT32      DoorbellOffset;
    UINT32      RuntimeRegOfffset;
    UINT32      HccParams2;
}XHCI_CAPABILITIES_REGISTER, * PXHCI_CAPABILITIES_REGISTER;

//HCSPARAMS1
#define XHCI_CAP_MAX_PORTS_MASK                     0xFF
#define XHCI_CAP_MAX_PORTS_SHIFT                    24
#define XHCI_CAP_MAX_PORTS                          (XHCI_CAP_MAX_PORTS_MASK << XHCI_CAP_MAX_PORTS_SHIFT) 
#define GET_XHCI_CAP_MAX_PORTS(x)                   ((((PXHCI_CAPABILITIES_REGISTER)x)->HcsParams1 & XHCI_CAP_MAX_PORTS) >> XHCI_CAP_MAX_PORTS_SHIFT)
#define XHCI_CAP_MAX_INTERRUPTS_MASK                0x07FF
#define XHCI_CAP_MAX_INTERRUPTS_SHIFT               8
#define XHCI_CAP_MAX_INTERRUPTS                     (XHCI_CAP_MAX_INTERRUPTS_MASK << XHCI_CAP_MAX_INTERRUPTS_SHIFT)
#define GET_XHCI_CAP_MAX_INTERRUPTS(x)              ((((PXHCI_CAPABILITIES_REGISTER)x)->HcsParams1 & XHCI_CAP_MAX_INTERRUPTS) >> XHCI_CAP_MAX_INTERRUPTS_SHIFT)
#define XHCI_CAP_MAX_DEVICE_SLOTS_MASK              0xFF
#define XHCI_CAP_MAX_DEVICE_SLOTS_SHIFT             0
#define XHCI_CAP_MAX_DEVICE_SLOTS                   (XHCI_CAP_MAX_DEVICE_SLOTS_MASK << XHCI_CAP_MAX_DEVICE_SLOTS_SHIFT)
#define GET_XHCI_CAP_MAX_DEVICE_SLOTS(x)            ((((PXHCI_CAPABILITIES_REGISTER)x)->HcsParams1 & XHCI_CAP_MAX_PORTS_MASK) >> XHCI_CAP_MAX_INTERRUPTS_SHIFT)

//HCSPARAMS2
#define XHCI_CAP_MAX_SCRATCHPAD_BUFFERSLO_MASK      0xF8
#define XHCI_CAP_MAX_SCRATCHPAD_BUFFERSLO_SHIFT     27
#define XHCI_CAP_MAX_SCRATCHPAD_BUFFERSLO           (XHCI_CAP_SCRATCHPAD_BUFFERS_MASK << XHCI_CAP_SCRATCHPAD_BUFFERS_SHIFT)
#define GET_XHCI_CAP_MAX_SCRATCHPAD_BUFFERSLO(x)    ((((PXHCI_CAPABILITIES_REGISTER)x)->HcsParams2 & XHCI_CAP_SCRATCHPAD_BUFFERS) >> XHCI_CAP_SCRATCHPAD_BUFFERS_SHIFT)
#define XHCI_CAP_SCRATCHPAD_RESTORE_MASK            1
#define XHCI_CAP_SCRATCHPAD_RESTORE_SHIFT           26
#define XHCI_CAP_SCRATCHPAD_RESTORE                 (XHCI_CAP_SCRATCHPAD_RESTORE_MASK << XHCI_CAP_SCRATCHPAD_RESTORE_SHIFT)
#define GET_XHCI_CAP_SCRATCHPAD_RESTORE(x)          ((((PXHCI_CAPABILITIES_REGISTER)x)->HcsParams2 & XHCI_CAP_SCRATCHPAD_RESTORE) >> XHCI_CAP_SCRATCHPAD_RESTORE_SHIFT)
#define XHCI_CAP_MAX_SCRATCHPAD_BUFFERSHI_MASK      0x3E
#define XHCI_CAP_MAX_SCRATCHPAD_BUFFERSHI_SHIFT     21
#define XHCI_CAP_MAX_SCRATCHPAD_BUFFERSHI           (XHCI_CAP_MAX_SCRATCHPAD_BUFFERSHI_MASK << XHCI_CAP_MAX_SCRATCHPAD_BUFFERSHI_SHIFT)
#define GET_XHCI_CAP_MAX_SCRATCHPAD_BUFFERSHI(x)    ((((PXHCI_CAPABILITIES_REGISTER)x)->HcsParams2 & XHCI_CAP_MAX_SCRATCHPAD_BUFFERSHI) >> XHCI_CAP_MAX_SCRATCHPAD_BUFFERSHI_SHIFT)
#define XHCI_CAP_MAX_ERST_MASK                      0x0F
#define XHCI_CAP_MAX_ERST_SHIFT                     4
#define XHCI_CAP_MAX_ERST                           (XHCI_CAP_MAX_ERST_MASK << XHCI_CAP_MAX_ERST_SHIFT)
#define GET_XHCI_CAP_MAX_ERST(x)                    ((((PXHCI_CAPABILITIES_REGISTER)x)->HcsParams2 & XHCI_CAP_MAX_ERST) >> XHCI_CAP_MAX_ERST_SHIFT)
#define XHCI_CAP_IST_MASK                           4
#define XHCI_CAP_IST_SHIFT                          0x0F
#define XHCI_CAP_IST                                (XHCI_CAP_IST_MASK << XHCI_CAP_IST_SHIFT)
#define GET_XHCI_CAP_IST(x)                         ((((PXHCI_CAPABILITIES_REGISTER)x)->HcsParams2 & XHCI_CAP_IST) >> XHCI_CAP_IST_SHIFT)

//HCSPARAMS3
#define XHCI_CAP_U2_DEV_EXIT_LATENCY_MASK           0xFF
#define XHCI_CAP_U2_DEV_EXIT_LATENCY_SHIFT          8
#define XHCI_CAP_U2_DEV_EXIT_LATENCY                (XHCI_CAP_U2_DEV_EXIT_LATENCY_MASK << XHCI_CAP_U2_DEV_EXIT_LATENCY_SHIFT)
#define GET_XHCI_CAP_U2_DEV_EXIT_LATENCY(x)         ((((PXHCI_CAPABILITIES_REGISTER)x)->HcsParams3 & XHCI_CAP_U2_DEV_EXIT_LATENCY) >> XHCI_CAP_U2_DEV_EXIT_LATENCY_SHIFT)
#define XHCI_CAP_U1_DEV_EXIT_LATENCY_MASK           0xFF
#define XHCI_CAP_U1_DEV_EXIT_LATENCY_SHIFT          0
#define XHCI_CAP_U1_DEV_EXIT_LATENCY                (XHCI_CAP_U2_DEV_EXIT_LATENCY_MASK << XHCI_CAP_U1_DEV_EXIT_LATENCY_SHIFT)
#define GET_XHCI_CAP_U1_DEV_EXIT_LATENCY(x)         ((((PXHCI_CAPABILITIES_REGISTER)x)->HcsParams3 & XHCI_CAP_U1_DEV_EXIT_LATENCY) >> XHCI_CAP_U1_DEV_EXIT_LATENCY_SHIFT)

//HCCPARAMS1
#define XHCI_CAP_AC64_MASK                          1
#define XHCI_CAP_AC64_SHIFT                         0
#define XHCI_CAP_AC64                               (XHCI_CAP_AC64_MASK << XHCI_CAP_AC64_SHIFT)
#define XHCI_CAP_BNC_MASK                           1
#define XHCI_CAP_BNC_SHIFT                          1
#define XHCI_CAP_BNC                                (XHCI_CAP_BNC_MASK << XHCI_CAP_BNC_SHIFT)
#define XHCI_CAP_CZS_MASK                           1
#define XHCI_CAP_CZS_SHIFT                          2
#define XHCI_CAP_CZS                                (XHCI_CAP_CZS_MASK << XHCI_CAP_CZS_SHIFT)
#define XHCI_CAP_PPC_MASK                           1
#define XHCI_CAP_PPC_SHIFT                          3
#define XHCI_CAP_PPC                                (XHCI_CAP_PPC_MASK << XHCI_CAP_PPC_SHIFT)
#define XHCI_CAP_PIND_MASK                          1
#define XHCI_CAP_PIND_SHIFT                         4
#define XHCI_CAP_PIND                               (XHCI_CAP_PIND_MASK << XHCI_CAP_PIND_SHIFT)
#define XHCI_CAP_LHRC_MASK                          1
#define XHCI_CAP_LHRC_SHIFT                         5
#define XHCI_CAP_LHRC                               (XHCI_CAP_LHRC_MASK << XHCI_CAP_LHRC_SHIFT)
#define XHCI_CAP_LTC_MASK                           1
#define XHCI_CAP_LTC_SHIFT                          6
#define XHCI_CAP_LTC                                (XHCI_CAP_LTC_MASK << XHCI_CAP_LTC_SHIFT)
#define XHCI_CAP_NSS_MASK                           1
#define XHCI_CAP_NSS_SHIFT                          7
#define XHCI_CAP_NSS                                (XHCI_CAP_NSS_MASK << XHCI_CAP_NSS_SHIFT)
#define XHCI_CAP_PAE_MASK                           1
#define XHCI_CAP_PAE_SHIFT                          8
#define XHCI_CAP_PAE                                (XHCI_CAP_PAE_MASK << XHCI_CAP_PAE_SHIFT)
#define XHCI_CAP_SPC_MASK                           1
#define XHCI_CAP_SPC_SHIFT                          9
#define XHCI_CAP_SPC                                (XHCI_CAP_SPC_MASK << XHCI_CAP_SPC_SHIFT)
#define XHCI_CAP_SEC_MASK                           1
#define XHCI_CAP_SEC_SHIFT                          10
#define XHCI_CAP_SEC                                (XHCI_CAP_SEC_MASK << XHCI_CAP_SEC_SHIFT)
#define XHCI_CAP_CFC_MASK                           1
#define XHCI_CAP_CFC_SHIFT                          11
#define XHCI_CAP_CFC                                (XHCI_CAP_CFC_MASK << XHCI_CAP_CFC_SHIFT)
#define XHCI_CAP_MAX_PSA_SIZE_MASK                  0x0F
#define XHCI_CAP_MAX_PSA_SIZE_SHIFT                 12
#define XHCI_CAP_MAX_PSA_SIZE                       (XHCI_CAP_MAX_PSA_SIZE_MASK << XHCI_CAP_CFC_SHIFT)
#define XHCI_CAP_XECP_MASK                          0xFFFF
#define XHCI_CAP_XECP_SHIFT                         16
#define XHCI_CAP_XECP                               (XHCI_CAP_XECP_MASK << XHCI_CAP_XECP_SHIFT)
#define GET_XHCI_CAP_XECP                           (((((PXHCI_CAPABILITIES_REGISTER)x)->HccParams1 & XHCI_CAP_XECP) >> XHCI_CAP_XECP_SHIFT) << 2)

//DBOFF
#define XHCI_CAP_DBOFF_MASK                         0xFFFFFFFC
#define XHCI_CAP_DBOFF_SHIFT                        0
#define XHCI_CAP_DBOFF                              (XHCI_CAP_DBOFF_MASK << XHCI_CAP_DBOFF_SHIFT)
#define GET_XHCI_CAP_DBOFF(x)                       ((((PXHCI_CAPABILITIES_REGISTER)x)->DoorbellOffset & XHCI_CAP_DBOFF) >> XHCI_CAP_DBOFF_SHIFT)

//RTSOFF
#define XHCI_CAP_RTSOFF_MASK                        0xFFFFFFF0
#define XHCI_CAP_RTSOFF_SHIFT                       0
#define XHCI_CAP_RTSOFF                             (XHCI_CAP_RTSOFF_MASK << XHCI_CAP_RTSOFF_SHIFT)
#define GET_XHCI_CAP_RTSOFF(x)                      ((((PXHCI_CAPABILITIES_REGISTER)x)->RuntimeRegOfffset & XHCI_CAP_RTSOFF) >> XHCI_CAP_RTSOFF_SHIFT)

//HCCPARAMS2
#define XHCI_CAP_U3C_MASK                           1
#define XHCI_CAP_U3C_SHIFT                          0
#define XHCI_CAP_U3C                                (XHCI_CAP_U3C_MASK << XHCI_CAP_U3C_SHIFT)
#define XHCI_CAP_CMC_MASK                           1
#define XHCI_CAP_CMC_SHIFT                          1
#define XHCI_CAP_CMC                                (XHCI_CAP_CMC_MASK << XHCI_CAP_CMC_SHIFT)
#define XHCI_CAP_FSC_MASK                           1
#define XHCI_CAP_FSC_SHIFT                          2
#define XHCI_CAP_FSC                                (XHCI_CAP_FSC_MASK << XHCI_CAP_FSC_SHIFT)
#define XHCI_CAP_CTC_MASK                           1
#define XHCI_CAP_CTC_SHIFT                          3
#define XHCI_CAP_CTC                                (XHCI_CAP_CTC_MASK << XHCI_CAP_CTC_SHIFT)
#define XHCI_CAP_LEC_MASK                           1
#define XHCI_CAP_LEC_SHIFT                          4
#define XHCI_CAP_LEC                                (XHCI_CAP_LEC_MASK << XHCI_CAP_LEC_SHIFT)
#define XHCI_CAP_CIC_MASK                           1
#define XHCI_CAP_CIC_SHIFT                          5
#define XHCI_CAP_CIC                                (XHCI_CAP_CIC_MASK << XHCI_CAP_CIC_SHIFT)
#define XHCI_CAP_ETC_MASK                           1
#define XHCI_CAP_ETC_SHIFT                          6
#define XHCI_CAP_ETC                                (XHCI_CAP_ETC_MASK << XHCI_CAP_ETC_SHIFT)
#define XHCI_CAP_ETC_TSC_MASK                       1
#define XHCI_CAP_ETC_TSC_SHIFT                      7
#define XHCI_CAP_ETC_TSC                            (XHCI_CAP_ETC_TSC_MASK << XHCI_CAP_ETC_TSC_SHIFT)
#define XHCI_CAP_GSC_MASK                           1
#define XHCI_CAP_GSC_SHIFT                          8
#define XHCI_CAP_GSC                                (XHCI_CAP_GSC_MASK << XHCI_CAP_GSC_SHIFT)
#define XHCI_CAP_VTC_MASK                           1
#define XHCI_CAP_VTC_SHIFT                          9
#define XHCI_CAP_VTC                                (XHCI_CAP_VTC_MASK << XHCI_CAP_VTC_SHIFT)



#endif