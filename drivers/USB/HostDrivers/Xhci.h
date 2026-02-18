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

//VTIOSOFF
#define XHCI_VTIOSOFF_MASK                          0x0FFFFF
#define XHCI_VTIOSOFF_SHIFT                         12
#define XHCI_VTIOSOFF                               (XHCI_VTIOSOFF_MASK << XHCI_VTIOSOFF_SHIFT)
#define GET_XHCI_VTIOSOFF(Base)                     ((*(UINT32*)((UINT64)Base + 0x20)) & XHCI_VTIOSOFF)

//HC Operational Registers

typedef struct PACKED _XHCI_USB_PORT_REGISTER_SET{
    UINT32                          PortStatusControl;
    UINT32                          PortPMSC;
    UINT32                          PortLI;
    UINT32                          PortHLPMC;
}XHCI_USB_PORT_REGISTER_SET, * PXHCI_USB_PORT_REGISTER_SET;

typedef struct PACKED _XHCI_OPERATIONAL_REGISTERS{
    UINT32                          UsbCommand;
    UINT32                          UsbStatus;                      
    UINT32                          PageSize;                       
    UINT8                           ReservedZ1[0x13 - 0x0C];        
    UINT32                          DncCtrl;
    UINT64                          Crcr;
    UINT8                           ReservedZ2[0x2F - 0x20];
    UINT64                          Dcbaap;
    UINT32                          Config;
    UINT8                           ReservedZ3[0x03FF - 0x003C];
    XHCI_USB_PORT_REGISTER_SET      Ports[];
}XHCI_OPERATIONAL_REGISTERS, * PXHCI_OPERATIONAL_REGISTERS;


#define GET_XHCI_OPERATIONAL_REGISTERS(Cap)         ((PXHCI_OPERATIONAL_REGISTERS)((UINT64)((PXHCI_CAPABILITIES_REGISTER)Cap)->CapLength + (UINT64)Cap))

//393

#define XHCI_USBCMD_RUN_STOP_MASK           1
#define XHCI_USBCMD_RUN_STOP_SHIFT          0
#define XHCI_USBCMD_RUN_STOP                (XHCI_USBCMD_RUN_STOP_MASK << XHCI_USBCMD_RUN_STOP_SHIFT)
#define XHCI_USBCMD_HCRST_MASK              1
#define XHCI_USBCMD_HCRST_SHIFT             1
#define XHCI_USBCMD_HCRST                   (XHCI_USBCMD_HCRST_MASK << XHCI_USBCMD_HCRST_SHIFT) //this will reset downstream USB3 ports and roots
#define XHCI_USBCMD_INTE_MASK               1
#define XHCI_USBCMD_INTE_SHIFT              2
#define XHCI_USBCMD_INTE                    (XHCI_USBCMD_INTE_MASK << XHCI_USBCMD_INTE_SHIFT)
#define XHCI_USBCMD_HSEE_MASK               1
#define XHCI_USBCMD_HSEE_SHIFT              3
#define XHCI_USBCMD_HSEE                    (XHCI_USBCMD_HSEE_MASK << XHCI_USBCMD_HSEE_SHIFT)
#define XHCI_USBCMD_LHCRST_MASK             1
#define XHCI_USBCMD_LHCRST_SHIFT            7
#define XHCI_USBCMD_LHCRST                  (XHCI_USBCMD_LHCRST_MASK << XHCI_USBCMD_LHCRST_SHIFT)
#define XHCI_USBCMD_CSS_MASK                1
#define XHCI_USBCMD_CSS_SHIFT               8
#define XHCI_USBCMD_CSS                     (XHCI_USBCMD_CSS_MASK << XHCI_USBCMD_CSS_SHIFT)
#define XHCI_USBCMD_CRS_MASK                1
#define XHCI_USBCMD_CRS_SHIFT               9
#define XHCI_USBCMD_CRS                     (XHCI_USBCMD_CRS_MASK << XHCI_USBCMD_CRS_SHIFT)
#define XHCI_USBCMD_EWE_MASK                1
#define XHCI_USBCMD_EWE_SHIFT               10
#define XHCI_USBCMD_EWE                     (XHCI_USBCMD_EWE_MASK << XHCI_USBCMD_EWE_SHIFT)
#define XHCI_USBCMD_EU3S_MASK               1
#define XHCI_USBCMD_EU3S_SHIFT              11
#define XHCI_USBCMD_EU3S                    (XHCI_USBCMD_EU3S_MASK << XHCI_USBCMD_EU3S_SHIFT)
#define XHCI_USBCMD_CME_MASK                1
#define XHCI_USBCMD_CME_SHIFT               13
#define XHCI_USBCMD_CME                     (XHCI_USBCMD_CME_MASK << XHCI_USBCMD_CME_SHIFT)
#define XHCI_USBCMD_ETE_MASK                1
#define XHCI_USBCMD_ETE_SHIFT               14
#define XHCI_USBCMD_TSC_EN_MASK             1
#define XHCI_USBCMD_TSC_EN_SHIFT            15
#define XHCI_USBCMD_TSC_EN                  (XHCI_USBCMD_TSC_EN_MASK << XHCI_USBCMD_TSC_EN_SHIFT)
#define XHCI_USBCMD_VTIOE_MASK              1
#define XHCI_USBCMD_VTIOE_SHIFT             16
#define XHCI_USBCMD_VTIOE                   (XHCI_USBCMD_VTIOE_MASK << XHCI_USBCMD_VTIOE_SHIFT)

#define XHCI_USBSTS_HCH_MASK                1
#define XHCI_USBSTS_HCH_SHIFT               0
#define XHCI_USBSTS_HCH                     (XHCI_USBSTS_HCH_MASK << XHCI_USBSTS_HCH_SHIFT)
#define XHCI_USBSTS_HSE_MASK                1
#define XHCI_USBSTS_HSE_SHIFT               2
#define XHCI_USBSTS_HSE                     (XHCI_USBSTS_HSE_MASK << XHCI_USBSTS_HSE_SHIFT)
#define XHCI_USBSTS_EINT_MASK               1
#define XHCI_USBSTS_EINT_SHIFT              3
#define XHCI_USBSTS_EINT                    (XHCI_USBSTS_EINT_MASK << XHCI_USBSTS_EINT_SHIFT)
#define XHCI_USBSTS_PCD_MASK                1
#define XHCI_USBSTS_PCD_SHIFT               4
#define XHCI_USBSTS_PCD                     (XHCI_USBSTS_PCD_MASK << XHCI_USBSTS_PCD_SHIFT)
#define XHCI_USBSTS_SSS_MASK                1
#define XHCI_USBSTS_SSS_SHIFT               8
#define XHCI_USBSTS_SSS                     (XHCI_USBSTS_SSS_MASK << XHCI_USBSTS_SSS_SHIFT)
#define XHCI_USBSTS_RSS_MASK                1
#define XHCI_USBSTS_RSS_SHIFT               9
#define XHCI_USBSTS_RSS                     (XHCI_USBSTS_RSS_MASK << XHCI_USBSTS_RSS_SHIFT)
#define XHCI_USBSTS_SRE_MASK                1
#define XHCI_USBSTS_SRE_SHIFT               10
#define XHCI_USBSTS_SRE                     (XHCI_USBSTS_SRE_MASK << XHCI_USBSTS_SRE_SHIFT)
#define XHCI_USBSTS_CNR_MASK                1
#define XHCI_USBSTS_CNR_SHIFT               11
#define XHCI_USBSTS_CNR                     (XHCI_USBSTS_CNR_MASK << XHCI_USBSTS_CNR_SHIFT)
#define XHCI_USBSTS_HCE_MASK                1
#define XHCI_USBSTS_HCE_SHIFT               12
#define XHCI_USBSTS_HCE                     (XHCI_USBSTS_HCE_MASK << XHCI_USBSTS_HCE_SHIFT)

#define XHCI_PAGE_SIZE_MASK                 0xFFFF
#define XHCI_PAGE_SIZE_SHIFT                0
#define XHCI_PAGE_SIZE                      (XHCI_PAGE_SIZE_MASK << XHCI_PAGE_SIZE_SHIFT)

#define XHCI_DNCTRL_NEx(x)                  (1 << x)

#define XHCI_CRCR_RCS_MASK                  1
#define XHCI_CRCR_RCS_SHIFT                 0
#define XHCI_CRCR_RCS                       (XHCI_CRCR_RCS_MASK << XHCI_CRCR_RCS_SHIFT)
#define XHCI_CRCR_CS_MASK                   1
#define XHCI_CRCR_CS_SHIFT                  1
#define XHCI_CRCR_CS                        (XHCI_CRCR_CS_MASK << XHCI_CRCR_CS_SHIFT)
#define XHCI_CRCR_CA_MASK                   1
#define XHCI_CRCR_CA_SHIFT                  2
#define XHCI_CRCR_CA                        (XHCI_CRCR_CA_MASK << XHCI_CRCR_CA_SHIFT)
#define XHCI_CRCR_CRR_MASK                  1
#define XHCI_CRCR_CRR_SHIFT                 3
#define XHCI_CRCR_CRR                       (XHCI_CRCR_CRR_MASK << XHCI_CRCR_CRR_SHIFT)
#define XHCI_CRCR_CRP                       0xFFFFFFFFFFFFFFC0

#define XHCI_DCBAAP                         0xFFFFFFFFFFFFFFC0

#define XHCI_CONFIG_MAX_SLOTS_EN_MASK       0xFF
#define XHCI_CONFIG_MAX_SLOTS_EN_SHIFT      0
#define XHCI_CONFIG_MAX_SLOTS_EN            (XHCI_CONFIG_MAX_SLOTS_EN_MASK << XHCI_CONFIG_MAX_SLOTS_EN_SHIFT)
#define XHCI_CONFIG_U3_ENTRY_ENABLE_MASK    1
#define XHCI_CONFIG_U3_ENTRY_ENABLE_SHIFT   8
#define XHCI_CONFIG_U3_ENTRY_ENABLE         (XHCI_CONFIG_U3_ENTRY_ENABLE_MASK << XHCI_CONFIG_U3_ENTRY_ENABLE_SHIFT)
#define XHCI_CONFIG_CIE_MASK                1
#define XHCI_CONFIG_CIE_SHFIT               9
#define XHCI_CONFIG_CIE                     (XHCI_CONFIG_CIE_MASK << XHCI_CONFIG_CIE_SHFIT)

#define XHCI_PORTSC_CSS_MASK                1
#define XHCI_PORTSC_CSS_SHIFT               0
#define XHCI_PORTSC_CSS                     (XHCI_PORTSC_CSS_MASK << XHCI_PORTSC_CSS_SHIFT)
#define XHCI_PORTSC_PED_MASK                1
#define XHCI_PORTSC_PED_SHIFT               1
#define XHCI_PORTSC_PED                     (XHCI_PORTSC_PED_MASK << XHCI_PORTSC_PED_SHIFT)
#define XHCI_PORTSC_OCA_MASK                1
#define XHCI_PORTSC_OCA_SHIFT               3
#define XHCI_PORTSC_OCA                     (XHCI_PORTSC_OCA_MASK << XHCI_PORTSC_OCA_SHIFT)
#define XHCI_PORTSC_PR_MASK                 1
#define XHCI_PORTSC_PR_SHIFT                4
#define XHCI_PORTSC_PR                      (XHCI_PORTSC_PR_MASK << XHCI_PORTSC_PR_SHIFT)
#define XHCI_PORTSC_PLS_MASK                0x0F
#define XHCI_PORTSC_PLS_SHIFT               5
#define XHCI_PORTSC_PLS                     (XHCI_PORTSC_PLS_MASK << XHCI_PORTSC_PLS_SHIFT)
#define     XHCI_PLS_U0_STATE               0
#define     XHCI_PLS_U1_STATE               1
#define     XHCI_PLS_U2_STATE               2
#define     XHCI_PLS_U3_STATE               3
#define     XHCI_PLS_DISABLE                4
#define     XHCI_PLS_RXDETECT               5
#define     XHCI_PLS_INACTIVE               6
#define     XHCI_PLS_POLLING                7
#define     XHCI_PLS_RECOVERY               8
#define     XHCI_PLS_HOST_RESET             9
#define     XHCI_PLS_COMPLIANCE_MODE        10
#define     XHCI_PLS_RESUME                 15
#define XHCI_PORTSC_PP_MASK                 1
#define XHCI_PORTSC_PP_SHIFT                9
#define XHCI_PORTSC_PP                      (XHCI_PORTSC_PP_MASK << XHCI_PORTSC_PP_SHIFT)
#define XHCI_PORTSC_PORT_SPEED_MASK         0x0F
#define XHCI_PORTSC_PORT_SPEED_SHIFT        10
#define XHCI_PORTSC_PORT_SPEED              (XHCI_PORTSC_PORT_SPEED_MASK << XHCI_PORTSC_PORT_SPEED_SHIFT)
#define XHCI_PORTSC_PIC_MASK                0x03
#define XHCI_PORTSC_PIC_SHIFT               14
#define XHCI_PORTSC_PIC                     (XHCI_PORTSC_PIC_MASK << XHCI_PORTSC_PIC_SHIFT)
#define XHCI_PORTSC_LWS_MASK                1
#define XHCI_PORTSC_LWS_SHIFT               16
#define XHCO_PORTSC_LWS                     (XHCI_PORTSC_LWS_MASK << XHCI_PORTSC_LWS_SHIFT)
#define XHCI_PORTSC_CSC_MASK                1
#define XHCI_PORTSC_CSC_SHIFT               17
#define XHCI_PORTSC_CSC                     (XHCI_PORTSC_CSC_MASK << XHCI_PORTSC_CSC_SHIFT)
#define XHCI_PORTSC_PEC_MASK                1
#define XHCI_PORTSC_PEC_SHIFT               18
#define XHCI_PORTSC_PEC                     (XHCI_PORTSC_PEC_MASK << XHCI_PORTSC_PEC_SHIFT)
#define XHCI_PORTSC_WRC_MASK                1
#define XHCI_PORTSC_WRC_SHIFT               19
#define XHCI_PORTSC_WRC                     (XHCI_PORTSC_WRC_MASK << XHCI_PORTSC_WRC_SHIFT)
#define XHCI_PORTSC_OCC_MASK                1
#define XHCI_PORTSC_OCC_SHIFT               20
#define XHCI_PORTSC_OCC                     (XHCI_PORTSC_OCC_MASK << XHCI_PORTSC_OCC_SHIFT)
#define XHCI_PORTSC_PRC_MASK                1
#define XHCI_PORTSC_PRC_SHIFT               21
#define XHCI_PORTSC_PRC                     (XHCI_PORTSC_PRC_MASK << XHCI_PORTSC_PRC_SHIFT)
#define XHCI_PORTSC_PLC_MASK                1
#define XHCI_PORTSC_PLC_SHIFT               22
#define XHCI_PORTSC_PLC                     (XHCI_PORTSC_PLC_MASK << XHCI_PORTSC_PLC_SHIFT)
#define XHCI_PORTSC_CEC_MASK                1
#define XHCI_PORTSC_CEC_SHIFT               23
#define XHCI_PORTSC_CEC                     (XHCI_PORTSC_CEC_MASK << XHCI_PORTSC_CEC_SHIFT)
#define XHCI_PORTSC_CAS_MASK                1
#define XHCI_PORTSC_CAS_SHIFT               24
#define XHCI_PORTSC_CAS                     (XHCI_PORTSC_CAS_MASK << XHCI_PORTSC_CAS_SHIFT)
#define XHCI_PORTSC_WCE_MASK                1
#define XHCI_PORTSC_WCE_SHIFT               25
#define XHCI_PORTSC_WCE                     (XHCI_PORTSC_WCE_MASK << XHCI_PORTSC_WCE_SHIFT)
#define XHCI_PORTSC_WDE_MASK                1
#define XHCI_PORTSC_WDE_SHIFT               26
#define XHCI_PORTSC_WDE                     (XHCI_PORTSC_WDE_MASK << XHCI_PORTSC_WDE_SHIFT)
#define XHCI_PORTSC_WOE_MASK                1
#define XHCI_PORTSC_WOE_SHIFT               27
#define XHCI_PORTSC_WOE                     (XHCI_PORTSC_WOE_MASK << XHCI_PORTSC_WOE_SHIFT)
#define XHCI_PORTSC_DR_MASK                 1
#define XHCI_PORTSC_DR_SHIFT                30
#define XHCI_PORTSC_DR                      (XHCI_PORTSC_DR_MASK << XHCI_PORTSC_DR_SHIFT)
#define XHCI_PORTSC_WPR_MASK                1
#define XHCI_PORTSC_WPR_SHIFT               31
#define XHCI_PORTSC_WPR                     (XHCI_PORTSC_WPR_MASK << XHCI_PORTSC_WPR_SHIFT)

#define XHCI_PORTPMSC3_U1_TIMEOUT_MASK      0x0F
#define XHCI_PORTPMSC3_U1_TIMEOUT_SHIFT     0
#define XHCI_PORTPMSC3_U1_TIMEOUT           (XHCI_PORTPMSC3_U1_TIMEOUT_MASK << XHCI_PORTPMSC3_U1_TIMEOUT_SHIFT)
#define XHCI_PORTPMSC3_U2_TIMEOUT_MASK      0x0F
#define XHCI_PORTPMSC3_U2_TIMEOUT_SHIFT     8
#define XHCI_PORTPMSC3_U2_TIMEOUT           (XHCI_PORTPMSC3_U2_TIMEOUT_MASK << XHCI_PORTPMSC3_U2_TIMEOUT_SHIFT)
#define XHCI_PORTPMSC3_FLA_MASK             1
#define XHCI_PORTPMSC3_FLA_SHIFT            16
#define XHCI_PORTPMSC3_FLA                  (XHCI_PORTPMSC3_FLA_MASK << XHCI_PORTPMSC3_FLA_SHIFT)

#define XHCI_PORTPMSC2_L1S_MASK             0x03
#define XHCI_PORTPMSC2_L1S_SHIFT            0
#define XHCI_PORTPMSC2_L1S                  (XHCI_PORTPMSC2_L1S_MASK << XHCI_PORTPMSC2_L1S_SHIFT)
#define XHCI_PORTPMSC2_RWE_MASK             1
#define XHCI_PORTPMSC2_RWE_SHIFT            3
#define XHCI_POrTPMSC2_RWE                  (XHCI_PORTPMSC2_RWE_MASK << XHCI_PORTPMSC2_RWE_SHIFT)
#define XHCI_PORTPMSC2_BESL_MASK            0x0F
#define XHCI_PORTPMSC2_BESL_SHIFT           4
#define XHCI_PORTPMSC2_BESL                 (XHCI_PORTPMSC2_BESL_MASK << XHCI_PORTPMSC2_BESL_SHIFT)
#define XHCI_PORTPMSC2_L1_DEV_SLOT_MASK     0xFF
#define XHCI_PORTPMSC2_L1_DEV_SLOT_SHIFT    8
#define XHCI_PORTPMSC2_L1_DEV_SLOT          (XHCI_PORTPMSC2_L1_DEV_SLOT_MASK << XHCI_PORTPMSC2_L1_DEV_SLOT_SHIFT)
#define XHCI_PORTPMSC2_HLE_MASK             1
#define XHCI_PORTPMSC2_HLE_SHIFT            16
#define XHCI_PORTPMSC2_HLE                  (XHCI_PORTPMSC2_HLE_MASK << XHCI_PORTPMSC2_HLE_SHIFT)
#define XHCI_PORTPMSC2_TEST_MODE_MASK       0x0F
#define XHCI_PORTPMSC2_TEST_MODE_SHIFT      28
#define XHCI_PORTPMSC2_TEST_MODE            (XHCI_PORTPMSC2_TEST_MODE_MASK << XHCI_PORTPMSC2_TEST_MODE_SHIFT)
#define XHCI_PORTLI_LEC_MASK                0xFFFF
#define XHCI_PORTLI_LEC_SHIFT               0
#define XHCI_PORTLI_LEC                     (XHCI_PORTLI_LEC_MASK << XHCI_PORTLI_LEC_SHIFT)
#define XHCI_PORTLI_RLC_MASK                0x0F
#define XHCI_PORTLI_RLC_SHIFT               0x16
#define XHCI_PORTLI_RLC                     (XHCI_PORTLI_RLC_MASK << XHCI_PORTLI_RLC_SHIFT)
#define XHCI_PORTLI_TLC_MASK                0x0F
#define XHCI_PORTLI_TLC_SHIFT               0x20
#define XHCI_PORTLI_TLC                     (XHCI_PORTLI_TLC_MASK << XHCI_PORTLI_TLC_SHIFT)

#define XHCI_PORTEXSC3_LSEC_MASK             0xFFFF
#define XHCI_PORTEXSC3_LSEC_SHIFT            0
#define XHCI_PORTEXSC3_LSEC                  (XHCI_PORTEXSC_LSEC_MASK << XHCI_PORTEXSC_LSEC_SHIFT)

#define XHCI_PORTEXSC2_HIRDM_MASK           0x03
#define XHCI_PORTEXSC2_HIRDM_SHIFT          0
#define XHCI_PORTEXSC2_HIRDM                (XHCI_PORTEXSC2_HIRDM_MASK << XHCI_PORTEXSC2_HIRDM_SHIFT)
#define XHCI_PORTEXSC2_L1_TIMEOUT_MASK      0xFF
#define XHCI_PORTEXSC2_L1_TIMEOUT_SHIFT     2
#define XHCI_PORTEXSC2_L1_TIMEOUT           (XHCI_PORTEXSC2_L1_TIMEOUT_MASK << XHCI_PORTEXSC2_L1_TIMEOUT_SHIFT)
#define XHCI_PORTEXSC2_BESLD_MASK           0x0F
#define XHCI_PORTEXSC2_BESLD_SHIFT          10
#define XHCI_PORTEXSC2_BESLD                (XHCI_PORTEXSC2_BESLD_MASK << XHCI_PORTEXSC2_BESLD_SHIFT)

#define XHCI_PORTEXSC_L1_TIMEOUT_NsTx(Ns)  (MIN(Ns, 64280) / 256)
#define XHCI_PORTEXSC_L1_TIMEOUT_xTNs(x)   (MIN(x, 0xFF) ? (MIN(x, 0xFF) * 256) : 128)

typedef struct PACKED _XHCI_INTERUPT_REGISTER_SET{
    UINT32  DWord[8];
}XHCI_INTERUPT_REGISTER_SET, * PXHCI_INTERUPT_REGISTER_SET;

#define XHCI_INT_REG_SET_IP_DWORD           0
#define XHCI_INT_REG_SET_IP_MASK            1
#define XHCI_INT_REG_SET_IP_SHIFT           0
#define XHCI_INT_REG_SET_IP                 (XHCI_INT_REG_SET_IP_MASK << XHCI_INT_REG_SET_IP_SHIFT)
#define XHCI_INT_REG_SET_IPE_DWORD          0
#define XHCI_INT_REG_SET_IE_MASK            1
#define XHCI_INT_REG_SET_IE_SHIFT           1
#define XHCI_INT_REG_SET_IE                 (XHCI_INT_REG_SET_IE_MASK << XHCI_INT_REG_SET_IE_SHIFT)
#define XHCI_INT_REG_SET_IMI_DWORD          1
#define XHCI_INT_REG_SET_IMI_MASK           0xFFFF
#define XHCI_INT_REG_SET_IMI_SHIFT          0
#define XHCI_INT_REG_SET_IMI                (XHCI_INT_REG_SET_IMI_MASK << XHCI_INT_REG_SET_IMI_SHIFT)
#define XHCI_INT_REG_SET_IMC_DWORD          1
#define XHCI_INT_REG_SET_IMC_MASK           0xFFFF
#define XHCI_INT_REG_SET_IMC_SHIFT          16
#define XHCI_INT_REG_SET_IMC                (XHCI_INT_REG_SET_IMC_MASK << XHCI_INT_REG_SET_IMC_SHIFT)
#define XHCI_INT_REG_SET_ERST_SIZE_DWORD    2
#define XHCI_INT_REG_SET_ERST_SIZE_MASK     0xFFFF
#define XHCI_INT_REG_SET_ERST_SIZE_SHIFT    0
#define XHCI_INT_REG_SET_ERST_SIZE          (XHCI_INT_REG_SET_ERST_SIZE_MASK << XHCI_INT_REG_SET_ERST_SIZE_SHIFT)
#define XHCI_INT_REG_SET_ERSTBA_LO_DWORD    4
#define XHCI_INT_REG_SET_ERSTBA_LO_MASK     0xFFFFFFC0
#define XHCI_INT_REG_SET_ERSTBA_LO_SHIFT    0
#define XHCI_INT_REG_SET_ERSTBA_LO          (XHCI_INT_REG_SET_ERSTBA_LO_MASK << XHCI_INT_REG_SET_ERSTBA_LO_SHIFT)
#define XHCI_INT_REG_SET_ERSTBA_HI_DWORD    5
#define XHCI_INT_REG_SET_ERSTBA_HI_MASK     0xFFFFFFFF
#define XHCI_INT_REG_SET_ERSTBA_HI_SHIFT    0
#define XHCI_INT_REG_SET_ERSTBA_HI          (XHCI_INT_REG_SET_ERSTBA_HI_MASK << XHCI_INT_REG_SET_ERSTBA_HI_SHIFT)
#define XHCI_INT_REG_SET_DESI_DWORD         6
#define XHCI_INT_REG_SET_DESI_MASK          0x07
#define XHCI_INT_REG_SET_DESI_SHIFT         0
#define XHCI_INT_REG_SET_DESI               (XHCI_INT_REG_SET_DESI_MASK << XHCI_INT_REG_SET_DESI_SHIFT)
#define XHCI_INT_REG_SET_EHB_DWORD          6
#define XHCI_INT_REG_SET_EHB_MASK           1
#define XHCI_INT_REG_SET_EHB_SHIFT          3
#define XHCI_INT_REG_SET_EHB                (XHCI_INT_REG_SET_EHB_MASK << XHCI_INT_REG_SET_EHB_SHIFT)
#define XHCI_INT_REG_SET_ERDP_LO_DWORD      6
#define XHCI_INT_REG_SET_ERDP_LO_MASK       0xFFFFFFF0
#define XHCI_INT_REG_SET_ERDP_LO_SHIFT      0
#define XHCI_INT_REG_SET_ERDP_LO            (XHCI_INT_REG_SET_ERDP_LO_MASK << XHCI_INT_REG_SET_ERDP_LO_SHIFT)
#define XHCI_INT_REG_SET_ERDP_HI_DWORD      7
#define XHCI_INT_REG_SET_ERDP_HI_MASK       0xFFFFFFFF
#define XHCI_INT_REG_SET_ERDP_HI_SHIFT      0
#define XHCI_INT_REG_SET_ERDP_HI            (XHCI_INT_REG_SET_ERDP_HI_MASK << XHCI_INT_REG_SET_ERDP_HI_SHIFT)

typedef struct PACKED _XHCI_INTERUPT_REGISTER{
    UINT32      Iman;
    UINT32      Imod;
    UINT32      Erstsz;
    UINT32      Rsvdp;
    UINT64      Erstba;
    UINT64      Erdp;
}XHCI_INTERUPT_REGISTER, * PXHCI_INTERUPT_REGISTER;

#define XHCI_INT_REG_IMAN_IP_MASK       1
#define XHCI_INT_REG_IMAN_IP_SHIFT      0
#define XHCI_INT_REG_IMAN_IP            (XHCI_INT_REG_IMAN_IP_MASK << XHCI_INT_REG_IMAN_IP_SHIFT)
#define XHCI_INT_REG_IMAN_IE_MASK       1
#define XHCI_INT_REG_IMAN_IE_SHIFT      1
#define XHCI_INT_REG_IMAN_IE            (XHCI_INT_REG_IMAN_IE_MASK << XHCI_INT_REG_IMAN_IE_SHIFT)

#define XHCI_INT_REG_IMOD_IMODI_MASK    0xFFFF
#define XHCI_INT_REG_IMOD_IMODI_SHIFT   0
#define XHCI_INT_REG_IMOD_IMODI         (XHCI_INT_REG_IMOD_IMODI_MASK << XHCI_INT_REG_IMOD_IMODI_SHIFT)
#define XHCI_INT_REG_IMOD_IMODC_MASK    0xFFFF
#define XHCI_INT_REG_IMOD_IMODC_SHIFT   16
#define XHCI_INT_REG_IMOD_IMODC         (XHCI_INT_REG_IMOD_IMODC_MASK << XHCI_INT_REG_IMOD_IMODC_SHIFT)



typedef struct PACKED _XHCI_RUNTIME_REGISTERS{
    UINT32                  MicroFrameIndex;
    UINT8                   ReservedZ[0x1F - 0x04];
    XHCI_INTERUPT_REGISTER  Irqx[];
}XHCI_RUNTIME_REGISTERS, * PXHCI_RUNTIME_REGISTERS;

#define XHCI_RUNTIME_REG_MAX_IRQS           1023



#endif