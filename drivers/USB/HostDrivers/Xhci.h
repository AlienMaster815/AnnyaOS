//Copyright GPL-2 Tyler Grenier (2025 - 2026)
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

#define XHCI_INT_REG_SET_IP_DWord           0
#define XHCI_INT_REG_SET_IP_MASK            1
#define XHCI_INT_REG_SET_IP_SHIFT           0
#define XHCI_INT_REG_SET_IP                 (XHCI_INT_REG_SET_IP_MASK << XHCI_INT_REG_SET_IP_SHIFT)
#define XHCI_INT_REG_SET_IPE_DWord          0
#define XHCI_INT_REG_SET_IE_MASK            1
#define XHCI_INT_REG_SET_IE_SHIFT           1
#define XHCI_INT_REG_SET_IE                 (XHCI_INT_REG_SET_IE_MASK << XHCI_INT_REG_SET_IE_SHIFT)
#define XHCI_INT_REG_SET_IMI_DWord          1
#define XHCI_INT_REG_SET_IMI_MASK           0xFFFF
#define XHCI_INT_REG_SET_IMI_SHIFT          0
#define XHCI_INT_REG_SET_IMI                (XHCI_INT_REG_SET_IMI_MASK << XHCI_INT_REG_SET_IMI_SHIFT)
#define XHCI_INT_REG_SET_IMC_DWord          1
#define XHCI_INT_REG_SET_IMC_MASK           0xFFFF
#define XHCI_INT_REG_SET_IMC_SHIFT          16
#define XHCI_INT_REG_SET_IMC                (XHCI_INT_REG_SET_IMC_MASK << XHCI_INT_REG_SET_IMC_SHIFT)
#define XHCI_INT_REG_SET_ERST_SIZE_DWord    2
#define XHCI_INT_REG_SET_ERST_SIZE_MASK     0xFFFF
#define XHCI_INT_REG_SET_ERST_SIZE_SHIFT    0
#define XHCI_INT_REG_SET_ERST_SIZE          (XHCI_INT_REG_SET_ERST_SIZE_MASK << XHCI_INT_REG_SET_ERST_SIZE_SHIFT)
#define XHCI_INT_REG_SET_ERSTBA_LO_DWord    4
#define XHCI_INT_REG_SET_ERSTBA_LO_MASK     0xFFFFFFC0
#define XHCI_INT_REG_SET_ERSTBA_LO_SHIFT    0
#define XHCI_INT_REG_SET_ERSTBA_LO          (XHCI_INT_REG_SET_ERSTBA_LO_MASK << XHCI_INT_REG_SET_ERSTBA_LO_SHIFT)
#define XHCI_INT_REG_SET_ERSTBA_HI_DWord    5
#define XHCI_INT_REG_SET_ERSTBA_HI_MASK     0xFFFFFFFF
#define XHCI_INT_REG_SET_ERSTBA_HI_SHIFT    0
#define XHCI_INT_REG_SET_ERSTBA_HI          (XHCI_INT_REG_SET_ERSTBA_HI_MASK << XHCI_INT_REG_SET_ERSTBA_HI_SHIFT)
#define XHCI_INT_REG_SET_DESI_DWord         6
#define XHCI_INT_REG_SET_DESI_MASK          0x07
#define XHCI_INT_REG_SET_DESI_SHIFT         0
#define XHCI_INT_REG_SET_DESI               (XHCI_INT_REG_SET_DESI_MASK << XHCI_INT_REG_SET_DESI_SHIFT)
#define XHCI_INT_REG_SET_EHB_DWord          6
#define XHCI_INT_REG_SET_EHB_MASK           1
#define XHCI_INT_REG_SET_EHB_SHIFT          3
#define XHCI_INT_REG_SET_EHB                (XHCI_INT_REG_SET_EHB_MASK << XHCI_INT_REG_SET_EHB_SHIFT)
#define XHCI_INT_REG_SET_ERDP_LO_DWord      6
#define XHCI_INT_REG_SET_ERDP_LO_MASK       0xFFFFFFF0
#define XHCI_INT_REG_SET_ERDP_LO_SHIFT      0
#define XHCI_INT_REG_SET_ERDP_LO            (XHCI_INT_REG_SET_ERDP_LO_MASK << XHCI_INT_REG_SET_ERDP_LO_SHIFT)
#define XHCI_INT_REG_SET_ERDP_HI_DWord      7
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

#define XHCI_INT_REG_ERSTBA_MASK        0xFFFFFFFFFFFFFFC0
#define XHCI_INT_REG_ERSTBA_SHIFT       0
#define XHCI_INT_REG_ERSTBA             (XHCI_INT_REG_ERSTBA_MASK << XHCI_INT_REG_ERSTBA_SHIFT)

#define XHCI_INT_REG_ERDP_DESI_MASK     0x03
#define XHCI_INT_REG_ERDP_DESI_SHIFT    0
#define XHCI_INT_REG_ERDP_DESI          (XHCI_INT_REG_ERDP_DESI_MASK << XHCI_INT_REG_ERDP_DESI_SHIFT)
#define XHCI_INT_REG_ERDP_EHB_MASK      1
#define XHCI_INT_REG_ERDP_EHB_SHIFT     3
#define XHCI_INT_REG_ERDP_MASK          0xFFFFFFFFFFFFFFF0

typedef struct PACKED _XHCI_DOORBELL_REGISTERS{
    UINT32      Doorbell[256];
}XHCI_DOORBELL_REGISTERS, * PXHCI_DOORBELL_REGISTERS;

#define XHCI_DOORBELL_REG_DB_TARGET_MASK        0xFF
#define XHCI_DOORBELL_REG_DB_TARGET_SHIFT       0
#define XHCI_DOORBELL_REG_DB_TARGET             (XHCI_DOORBELL_REG_DB_TARGET_MASK << XHCI_DOORBELL_REG_DB_TARGET_SHIFT)
#define XHCI_DOORBELL_TASK_ID_MASK              0xFFFF
#define XHCI_DOORBELL_TASK_ID_SHIFT             16
#define XHCI_DOORBELL_TASK_ID                   (XHCI_DOORBELL_REG_DB_TARGET_MASK << XHCI_DOORBELL_REG_DB_TARGET_SHIFT)

typedef struct PACKED _XHCI_RUNTIME_REGISTERS{
    UINT32                  MicroFrameIndex;
    UINT8                   ReservedZ[0x1F - 0x04];
    XHCI_INTERUPT_REGISTER  Irqx[];
}XHCI_RUNTIME_REGISTERS, * PXHCI_RUNTIME_REGISTERS;

#define XHCI_RUNTIME_REG_MAX_IRQS           1023

typedef struct PACKED _XHCI_VTIO_REGISTERS{
    UINT32      VtioCap;
    UINT32      VtioCa;
    UINT32      VtioDa[8];
    UINT8       Rsvdp[0x2F - 0x28];
    UINT32      VtioIa[32];
    UINT8       Rsvdz[0xFF - 0xB0];
    UINT32      VtioEa[255];
}XHCI_VTIO_REGISTERS, * PXHCI_VTIO_REGISTERS;

#define XHCI_VTIOCAP_PDMAID_MASK            0xFFFF
#define XHCI_VTIOCAP_PDMAID_SHIFT           0
#define XHCI_VTIOCAP_PDMAID                 (XHCI_VTIOCAP_PDMAID_MASK << XHCI_VTIOCAP_PDMAID_SHIFT)
#define XHCI_VTIOCAP_ADMAID_MASK            0xFFFF
#define XHCI_VTIOCAP_ADMAID_SHIFT           16
#define XHCI_VTIOCAP_ADMAID                 (XHCI_VTIOCAP_ADMAID_MASK << XHCI_VTIOCAP_ADMAID_SHIFT)

#define XHCI_VTIOCA_CRDIDA_MASK             1
#define XHCI_VTIOCA_CRDIDA_SHIFT            1
#define XHCI_VTIOCA_CRDIDA                  (XHCI_VTIOCA_CRDIDA_MASK << XHCI_VTIOCA_CRDIDA_SHIFT)
#define XHCI_VTIOCA_DCBAADIDA_MASK          1
#define XHCI_VTIOCA_DCBAADIDA_SHIFT         2
#define XHCI_VTIOCA_DCBAADIDA               (XHCI_VTIOCA_DCBAADIDA_MASK << XHCI_VTIOCA_DCBAADIDA_SHIFT)
#define XHCI_VTIOCA_SPBADIDA_MASK           1
#define XHCI_VTIOCA_SPBADIDA_SHIFT          3
#define XHCI_VTIOCA_SPBADIDA                (XHCI_VTIOCA_SPBADIDA_MASK << XHCI_VTIOCA_SPBADIDA_SHIFT)
#define XHCI_VTIOCA_SPBDIDA_MASK            1
#define XHCI_VTIOCA_SPBDIDA_SHIFT           4
#define XHCI_VTIOCA_SPBDIDA                 (XHCI_VTIOCA_SPBDIDA_MASK << XHCI_VTIOCA_SPBDIDA_SHIFT)
#define XHCI_VTIOCA_ICDIDA_MASK             1
#define XHCI_VTIOCA_ICDIDA_SHIFT            6
#define XHCI_VTIOCA_ICDIDA                  (XHCI_VTIOCA_ICDIDA_MASK << XHCI_VTIOCA_ICDIDA_SHIFT)
#define XHCI_VTIOCA_MSIDIDA_MASK            1
#define XHCI_VTIOCA_MSIDIDA_SHIFT           7
#define XHCI_VTIOCA_MSIDIDA                 (XHCI_VTIOCA_MSIDIDA_MASK << XHCI_VTIOCA_MSIDIDA_SHIFT)
#define XHCI_VTIOCA_PBDIDA_MASK             1
#define XHCI_VTIOCA_PBDIDA_SHIFT            8
#define XHCI_VTIOCA_PBDIDA                  (XHCI_VTIOCA_PBDIDA_MASK << XHCI_VTIOCA_PBDIDA_SHIFT)
#define XHCI_VTIOCA_DCDIDA_MASK             1
#define XHCI_VTIOCA_DCDIDA_SHIFT            9
#define XHCI_VTIOCA_DCDIDA                  (XHCI_VTIOCA_DCDIDA_MASK << XHCI_VTIOCA_DCDIDA_SHIFT)
#define XHCI_VTIOCA_EPDIDA_MASK             1
#define XHCI_VTIOCA_EPDIDA_SHIFT            10
#define XHCI_VTIOCA_EPDIDA                  (XHCI_VTIOCA_EPDIDA_MASK << XHCI_VTIOCA_EPDIDA_SHIFT)


#define XHCI_DEVICE_CONTEXT_BASE_ADDRESS_ARRAY_SIZE         2048
//#define XHCI_DEVICE_CONTEXT_BASE_ADDRESS_ARRAY_BOUNDRY    PAGESIZE
#define XHCI_DEVICE_CONTEXT_BASE_ADDRESS_ARRAY_ALIGNMENT    64
#define XHCI_DEVICE_CONTEXT_SIZE                            2048
//#define XHCI_DEVICE_CONTEXT_BOUNDRY                       PAGESIZE
#define XHCI_DEVICE_CONTEXT_ALIGNMENT                       64
#define XHCI_INPUT_CONTROLL_CONTEXT_SIZE                    64
//#define XHCI_INPUT_CONTROLL_CONTEXT_BOUNDRY               PAGESIZE
#define XHCI_INPUT_CONTROLL_CONTEXT_ALINGMENT               64
#define XHCI_SLOT_CONTEXT_SIZE                              64
//#define XHCI_SLOT_CONTEXT_BOUNDRY                         PAGESIZE
#define XHCI_SLOT_CONTEXT_ALIGNMENT                         32
#define XHCI_ENDPOINT_CONTEXT_SIZE                          64
//#define XHCI_ENDPOINT_CONTEXT_BOUNDRY                     PAGESIZE
#define XHCI_ENDPOINT_CONTEXT_ALIGNMENT                     32
#define XHCI_STREAM_CONTEXT_SIZE                            16
//#define XHCI_STREAM_CONTEXT_SIZE                          PAGESIZE
#define XHCI_STREAM_CONTEXT_ALIGNMENT                       16
#define XHCI_LINEAR_STREAM_ARRAY_SIZE                       (1 * MEGABYTE)
#define XHCI_LINEAR_STREAM_ARRAY_ALIGNMENT                  16
#define XHCI_PRIMARY_SECONDARY_STREAM_ARRAY_SIZE            (4 * KILOBYTE)                  
//#define XHCI_PRIMARY_SECONDARY_STREAM_ARRAY_BOUNDRY       PAGESIZE
#define XHCI_PRIMARY_SECONDARY_STREAM_ARRAY_ALIGNMENT       16
#define XHCI_TRANSFER_RING_SEGMENT_SIZE                     (64 * KILOBYTE)
#define XHCI_TRANSFER_RING_SEGMENT_BOUNDRY                  (64 * KILOBYTE)
#define XHCI_TRANSFER_RING_SEGMENT_ALINGMENT                16
#define XHCI_COMMAND_RING_SEGMENT_SIZE                      (64 * KILOBYTE)
#define XHCI_COMMAND_RING_SEGMENT_BOUNDRY                   (64 * KILOBYTE)
#define XHCI_COMMAND_RING_SEGMENT_ALIGNMENT                 64
#define XHCI_EVENT_RING_SEGMENT_SIZE                        (64 * KILOBYTE)
#define XHCI_EVENT_RING_SEGMENT_BOUNDRY                     (64 * KILOBYTE)
#define XHCI_EVENT_RING_SEGMENT_ALIGNMENT                   64
#define XHCI_EVENT_RING_SEGMENT_TABLE_SIZE                  (512 * KILOBYTE)
#define XHCI_EVENT_RING_SEGMENT_TABLE_ALIGNMENT             64
#define XHCI_SCRATCHPAD_BUFFER_ARRAY_SIZE                   248
//#define XHCI_SCRATCHPAD_BUFFER_ARRAY_BOUND                PAGESIZE
#define XHCI_SCRATCHPAD_BUFFER_ARRAY_ALINGMENT              64
//#define XHCI_SCRATCHPAD_BUFFERS_SIZE                      PAGESIZE
//#define XHCI_SCRATCHPAD_BUFFERS_BOUNDRY                   PAGESIZE
//#define XHCI_SCRATCHPAD_BUFFERS_ALIGNMENT                 PAGE

#define XHCI_DEVICE_CONTEXT_BASE_ADDRESS_ARRAY_ALLOCATION_SIZE(MaxSlotsEn) ((MaxSlotsEn + 1) * sizeof(UINT64))

typedef struct PACKED _XHCI_SLOT_CONTEXT{
    UINT32      DWord[8];
}XHCI_SLOT_CONTEXT, * PXHCI_SLOT_CONTEXT;

//offset 0
#define XHCI_SLOT_CONTEXT_ROUTE_STRING_MASK       0x000FFFFF
#define XHCI_SLOT_CONTEXT_ROUTE_STRING_SHIFT      0
#define XHCI_SLOT_CONTEXT_ROUTE_STRING            (XHCI_SLOT_CONTEXT_ROUTE_STRING_MASK << XHCI_SLOT_CONTEXT_ROUTE_STRING_SHIFT)
#define XHCI_SLOT_CONTEXT_SPEED_MASK              0x0F
#define XHCI_SLOT_CONTEXT_SPEED_SHIFT             20
#define XHCI_SLOT_CONTEXT_SPEED                   (XHCI_SLOT_CONTEXT_SPEED_MASK << XHCI_SLOT_CONTEXT_SPEED_SHIFT)
#define XHCI_SLOT_CONTEXT_MTT_MASK                1
#define XHCI_SLOT_CONTEXT_MTT_SHIFT               25
#define XHCI_SLOT_CONTEXT_MTT                     (XHCI_SLOT_CONTEXT_MTT_MASK << XHCI_SLOT_CONTEXT_MTT_SHIFT)
#define XHCI_SLOT_CONTEXT_HUB_MASK                1
#define XHCI_SLOT_CONTEXT_HUB_SHIFT               26
#define XHCI_SLOT_CONTEXT_HUB                     (XHCI_SLOT_CONTEXT_HUB_MASK << XHCI_SLOT_CONTEXT_HUB_SHIFT)
#define XHCI_SLOT_CONTEXT_CONTEXT_ENTRIES_MASK    0x1F
#define XHCI_SLOT_CONTEXT_CONTEXT_ENTRIES_SHIFT   27
#define XHCI_SLOT_CONTEXT_CONTEXT_ENTRIES         (XHCI_SLOT_CONTEXT_CONTEXT_ENTRIES_MASK << XHCI_SLOT_CONTEXT_CONTEXT_ENTRIES_SHIFT)

//offset 4
#define XHCI_SLOT_CONTEXT_MAX_EXIT_LATENCY_MASK     0xFFFF
#define XHCI_SLOT_CONTEXT_MAX_EXIT_LATENCY_SHIFT    0
#define XHCI_SLOT_CONTEXT_MAX_EXIT_LATENCY          (XHCI_SLOT_CONTEXT_MAX_EXIT_LATENCY_MASK << XHCI_SLOT_CONTEXT_MAX_EXIT_LATENCY_SHIFT)
#define XHCI_SLOT_CONTEXT_RHPN_MASK                 0xFF
#define XHCI_SLOT_CONTEXT_RHPN_SHIFT                16
#define XHCI_SLOT_CONTEXT_RHPN                      (XHCI_SLOT_CONTEXT_RHPN_MASK << XHCI_SLOT_CONTEXT_RHPN_SHIFT) //Root Hub Port Number
#define XHCI_SLOT_CONTEXT_NUMBER_OF_PORTS_MASK      0xFF
#define XHCI_SLOT_CONTEXT_NUMBER_OF_PORTS_SHIFT     24
#define XHCI_SLOT_CONTEXT_NUMBER_OF_PORTS           (XHCI_SLOT_CONTEXT_NUMBER_OF_PORTS_MASK << XHCI_SLOT_CONTEXT_NUMBER_OF_PORTS_SHIFT)

//offset 8
#define XHCI_SLOT_CONTEXT_PARENT_HUB_SLOT_ID_MASK   0xFF
#define XHCI_SLOT_CONTEXT_PARENT_HUB_SLOT_ID_SHIFT  0
#define XHCI_SLOT_CONTEXT_PARENT_HUB_SLOT_ID        (XHCI_SLOT_CONTEXT_PARENT_HUB_SLOT_ID_MASK << XHCI_SLOT_CONTEXT_PARENT_HUB_SLOT_ID_SHIFT)
#define XHCI_SLOT_CONTEXT_PARENT_PORT_NUMBER_MASK   0xFF
#define XHCI_SLOT_CONTEXT_PARENT_PORT_NUMBER_SHIFT  8
#define XHCI_SLOT_CONTEXT_PARENT_PORT_NUMBER        (XHCI_SLOT_CONTEXT_PARENT_PORT_NUMBER_MASK << XHCI_SLOT_CONTEXT_PARENT_PORT_NUMBER_SHIFT)
#define XHCI_SLOT_CONTEXT_TT_THINK_TIME_MASK        0b11
#define XHCI_SLOT_CONTEXT_TT_THINK_TIME_SHIFT       16
#define XHCI_SLOT_CONTEXT_TT_THINK_TIME             (XHCI_SLOT_CONTEXT_TT_THINK_TIME_MASK << XHCI_SLOT_CONTEXT_TT_THINK_TIME_SHIFT)
#define XHCI_SLOT_CONTEXT_INTERRUPT_TARGET_MASK     0x03FF
#define XHCI_SLOT_CONTEXT_INTERRUPT_TARGET_SHIFT    22
#define XHCI_SLOT_CONTEXT_INTERRUPT_TARGET          (XHCI_SLOT_CONTEXT_INTERRUPT_TARGET_MASK << XHCI_SLOT_CONTEXT_INTERRUPT_TARGET_SHIFT)

//offset 12
#define XHCI_SLOT_CONTEXT_USB_DEVICE_ADDRESS_MASK   0xFF
#define XHCI_SLOT_CONTEXT_USB_DEVICE_ADDRESS_SHIFT  0
#define XHCI_SLOT_CONTEXT_USB_DEVICE_ADDRESS        (XHCI_SLOT_CONTEXT_USB_DEVICE_ADDRESS_MASK << XHCI_SLOT_CONTEXT_USB_DEVICE_ADDRESS_SHIFT)
#define XHCI_SLOT_CONTEXT_SLOT_STATE_MASK           0x1F
#define XHCI_SLOT_CONTEXT_SLOT_STATE_SHIFT          27
#define XHCI_SLOT_CONTEXT_SLOT_STATE                (XHCI_SLOT_CONTEXT_SLOT_STATE_MASK << XHCI_SLOT_CONTEXT_SLOT_STATE_SHIFT)

typedef struct PACKED _XHCI_ENDPOINT_CONTEXT{
    UINT32      DWord[8];
}XHCI_ENDPOINT_CONTEXT, * PXHCI_ENDPOINT_CONTEXT;

//offset 0
#define XHCI_ENDPOINT_CONTEXT_EP_STATE_MASK         0b11
#define XHCI_ENDPOINT_CONTEXT_EP_STATE_SHIFT        0
#define XHCI_ENDPOINT_CONTEXT_EP_STATE              (XHCI_ENDPOINT_CONTEXT_EP_STATE_MASK << XHCI_ENDPOINT_CONTEXT_EP_STATE_SHIFT)
#define XHCI_ENDPOINT_CONTEXT_MULT_MASK             0b11
#define XHCI_ENDPOINT_CONTEXT_MULT_SHIFT            8
#define XHCI_ENDPOINT_CONTEXT_MULT                  (XHCI_ENDPOINT_CONTEXT_MULT_MASK << XHCI_ENDPOINT_CONTEXT_MULT_SHIFT)
#define XHCI_ENDPOINT_CONTEXT_MAX_PSTREAMS_MASK     0x1F
#define XHCI_ENDPOINT_CONTEXT_MAX_PSTREAMS_SHIFT    10
#define XHCI_ENDPOINT_CONTEXT_MAX_PSTREAMS          (XHCI_ENDPOINT_CONTEXT_MAX_PSTREAMS_MASK << XHCI_ENDPOINT_CONTEXT_MAX_PSTREAMS_SHIFT)
#define XHCI_ENDPOINT_CONTEXT_LSA_MASK              1
#define XHCI_ENDPOINT_CONTEXT_LSA_SHIFT             15
#define XHCI_ENDPOINT_CONTEXT_LSA                   (XHCI_ENDPOINT_CONTEXT_LSA_MASK << XHCI_ENDPOINT_CONTEXT_LSA_SHIFT)
#define XHCI_ENDPOINT_CONTEXT_INTERVAL_MASK         0xFF
#define XHCI_ENDPOINT_CONTEXT_INTERVAL_SHIFT        16
#define XHCI_ENDPOINT_CONTEXT_INTERVAL              (XHCI_ENDPOINT_CONTEXT_INTERVAL_MASK << XHCI_ENDPOINT_CONTEXT_INTERVAL_SHIFT)
#define XHCI_ENDPOINT_CONTEXT_MAX_ESIT_HI_MASK      0xFF
#define XHCI_ENDPOINT_CONTEXT_MAX_ESIT_HI_SHIFT     24

//offset 4
#define XHCI_ENDPOINT_CONTEXT_ERROR_COUNT_MASK      0b11
#define XHCI_ENDPOINT_CONTEXT_ERROR_COUNT_SHIFT     1
#define XHCI_ENDPOINT_CONTEXT_ERROR_COUNT           (XHCI_ENDPOINT_CONTEXT_ERROR_COUNT_MASK << XHCI_ENDPOINT_CONTEXT_ERROR_COUNT_SHIFT)
#define XHCI_ENDPOINT_CONTEXT_EP_TYPE_MASK          0b111
#define XHCI_ENDPOINT_CONTEXT_EP_TYPE_SHIFT         3
#define XHCI_ENDPOINT_CONTEXT_EP_TYPE               (XHCI_ENDPOINT_CONTEXT_EP_TYPE_MASK << XHCI_ENDPOINT_CONTEXT_EP_TYPE_SHIFT)
#define XHCI_ENDPOINT_CONTEXT_HID_MASK              1
#define XHCI_ENDPOINT_CONTEXT_HID_SHIFT             7
#define XHCI_ENDPOINT_CONTEXT_HID                   (XHCI_ENDPOINT_CONTEXT_HID_MASK << XHCI_ENDPOINT_CONTEXT_HID_SHIFT)
#define XHCI_ENDPOINT_CONTEXT_MAX_BURST_SIZE_MASK   0xFF
#define XHCI_ENDPOINT_CONTEXT_MAX_BURST_SIZE_SHIFT  8
#define XHCI_ENDPOINT_CONTEXT_MAX_BURST_SIZE        (XHCI_ENDPOINT_CONTEXT_MAX_BURST_SIZE_MASK << XHCI_ENDPOINT_CONTEXT_MAX_BURST_SIZE_SHIFT)
#define XHCI_ENDPOINT_CONTEXT_MAX_PACKET_SIZE_MASK  0xFFFF
#define XHCI_ENDPOINT_CONTEXT_MAX_PACKET_SIZE_SHIFT 16
#define XHCI_ENDPOINT_CONTEXT_MAX_PACKET_SIZE       (XHCI_ENDPOINT_CONTEXT_MAX_PACKET_SIZE_MASK << XHCI_ENDPOINT_CONTEXT_MAX_PACKET_SIZE_SHIFT)

//offset 8
#define XHCI_ENDPOINT_CONTEXT_DCS_MASK              1
#define XHCI_ENDPOINT_CONTEXT_DCS_SHIFT             0
#define XHCI_ENDPOINT_CONTEXT_DCS                   (XHCI_ENDPOINT_CONTEXT_DCS_MASK << XHCI_ENDPOINT_CONTEXT_DCS_SHIFT)
#define XHCI_ENDPOINT_CONTEXT_TR_DEQUEUE_PTR        0xFFFFFFFFFFFFFFF0

//offset 16
#define XHCI_ENDPOINT_CONTEXT_AVG_TRB_LEN_MASK      0xFFFF
#define XHCI_ENDPOINT_CONTEXT_AVG_TRB_LEN_SHIFT     0
#define XHCI_ENDPOINT_CONTEXT_AVG_TRB_LEN           (XHCI_ENDPOINT_CONTEXT_AVG_TRB_LEN_MASK << XHCI_ENDPOINT_CONTEXT_AVG_TRB_LEN_SHIFT)
#define XHCI_ENDPOINT_CONTEXT_MAX_ESIT_LO_MASK      0xFFFF
#define XHCI_ENDPOINT_CONTEXT_MAX_ESIT_LO_SHIFT     16
#define XHCI_ENDPOINT_CONTEXT_MAX_ESIT_LO           (XHCI_ENDPOINT_CONTEXT_MAX_ESIT_LO_MASK << XHCI_ENDPOINT_CONTEXT_MAX_ESIT_LO_SHIFT)

typedef struct PACKED _XHCI_STREAM_CONTEXT{
    UINT32  DWord[4];
}XHCI_STREAM_CONTEXT, * PXHCI_STREAM_CONTEXT;

//offset 0
#define XHCI_STREAM_CONTEXT_DCS_MASK                1
#define XHCI_STREAM_CONTEXT_DCS_SHIFT               0
#define XHCI_STREAM_CONTEXT_DCS                     (XHCI_STREAM_CONTEXT_DCS_MASK << XHCI_STREAM_CONTEXT_DCS_SHIFT)
#define XHCI_STREAM_CONTEXT_SCT_MASK                0b111
#define XHCI_STREAM_CONTEXT_SCT_SHIFT               1
#define XHCI_STREAM_CONTEXT_SCT                     (XHCI_STREAM_CONTEXT_SCT_MASK << XHCI_STREAM_CONTEXT_SCT_SHIFT)
#define XHCI_STREAM_CONTEXT_TR_DEQUEUE_PTR          0xFFFFFFFFFFFFFFF0

//offset 8
#define XHCI_STREAM_CONTEXT_STOPPED_EDTLA_MASK      0x00FFFFFF
#define XHCI_STREAM_CONTEXT_STOPPED_EDTLA_SHIFT     0
#define XHCI_STREAM_CONTEXT_STOPPED_EDTLA           (XHCI_STREAM_CONTEXT_STOPPED_EDTLA_MASK << XHCI_STREAM_CONTEXT_STOPPED_EDTLA_SHIFT)

#define XHCI_DEVICE_CONTEXT_EP_OUT                  0
#define XHCI_DEVICE_CONTEXT_EP_IN                   1

#define XHCI_DEVICE_CONTEXT_TO_EPx_IN(Ctx, x)       (&Ctx->EpX[XHCI_DEVICE_CONTEXT_EP_IN][x])
#define XHCI_DEVICE_CONTEXT_TO_EPx_OUT(Ctx, x)      (&Ctx->EpX[XHCI_DEVICE_CONTEXT_EP_OUT][x])

typedef struct PACKED _XHCI_DEVICE_CONTEXT{
    XHCI_SLOT_CONTEXT       SlotContext;
    XHCI_ENDPOINT_CONTEXT   Ep0BiDir;
    XHCI_ENDPOINT_CONTEXT   EpX[][2];
}XHCI_DEVICE_CONTEXT, * PXHCI_DEVICE_CONTEXT;

typedef struct PACKED _XHCI_INPUT_CONTROL_CONTEXT{
    UINT32      DWord[8];
}XHCI_INPUT_CONTROL_CONTEXT, * PXHCI_INPUT_CONTROL_CONTEXT;

//offset 0
#define XHCI_INPUT_CONTROL_CONTEXT_Dx_MASK                  1
#define XHCI_INPUT_CONTROL_CONTEXT_Dx_SHIFT(x)              (XHCI_INPUT_CONTEXT_Dx_MASK << x)

//offset 4
#define XHCI_INPUT_CONTROL_CONTEXT_ADD_CONTEXT_FLAGS        UINT32_MAX

//offset 28
#define XHCI_INPUT_CONTROL_CONTEXT_CONFIG_VALUE_MASK        0xFF
#define XHCI_INPUT_CONTROL_CONTEXT_CONFIG_VALUE_SHIFT       0
#define XHCI_INPUT_CONTROL_CONTEXT_CONFIG_VALUE             (XHCI_INPUT_CONTEXT_CONFIG_VALUE_MASK << XHCI_INPUT_CONTEXT_CONFIG_VALUE_SHIFT)
#define XHCI_INPUT_CONTROL_CONTEXT_INTERFACE_NUMBER_MASK    0xFF
#define XHCI_INPUT_CONTROL_CONTEXT_INTERFACE_NUMBER_SHIFT   8
#define XHCI_INPUT_CONTROL_CONTEXT_INTERFACE_NUMBER         (XHCI_INPUT_CONTEXT_INTERFACE_NUMBER_MASK << XHCI_INPUT_CONTEXT_INTERFACE_NUMBER_SHIFT)
#define XHCI_INPUT_CONTROL_CONTEXT_ALTERNATE_SETTING_MASK   0xFF
#define XHCI_INPUT_CONTROL_CONTEXT_ALTERNATE_SETTING_SHIFT  16
#define XHCI_INPUT_CONTROL_CONTEXT_ALTERNATE_SETTING        (XHCI_INPUT_CONTEXT_ALTERNATE_SETTING_MASK << XHCI_INPUT_CONTEXT_ALTERNATE_SETTING_SHIFT)

#define XHCI_INPUT_CONTEXT_EP_OUT                           0
#define XHCI_INPUT_CONTEXT_EP_IN                            1

#define XHCI_INPUT_CONTEXT_TO_EPx_IN(Ctx, x)                (&Ctx->EpX[XHCI_INPUT_CONTEXT_EP_IN][x])
#define XHCI_INPUT_CONTEXT_TO_EPx_OUT(Ctx, x)               (&Ctx->EpX[XHCI_INPUT_CONTEXT_EP_OUT][x])

typedef struct PACKED _XHCI_INPUT_CONTEXT{
    XHCI_INPUT_CONTROL_CONTEXT      InputControlContext;
    XHCI_SLOT_CONTEXT               Slot;
    XHCI_ENDPOINT_CONTEXT           Ep0;
    XHCI_ENDPOINT_CONTEXT           EpX[][2];
}XHCI_INPUT_CONTEXT, * PXHCI_INPUT_CONTEXT;

typedef UINT32 XHCI_PORT_BANDWIDTH_CONTEXT;
typedef XHCI_PORT_BANDWIDTH_CONTEXT* PXHCI_PORT_BANDWIDTH_CONTEXT;

#define XHCI_PORT_BANDWIDTH_CONTEXT_PORTx_MEMBER            (x / 4)
#define XHCI_PORT_BANDWIDTH_CONTEXT_PORTx_MASK              0xFF
#define XHCI_PORT_BANDWIDTH_CONTEXT_PORTx_SHIFT(x)          ((x % 4) * 8)
#define XHCI_PORT_BANDWIDTH_CONTEXT_PORTx(x)                (XHCI_PORT_BANDWIDTH_CONTEXT_PORTx_MASK << XHCI_PORT_BANDWIDTH_CONTEXT_PORTx_SHIFT(x))

typedef struct _XHCI_NORMAL_TRB{
    UINT32  DWord[4];
}XHCI_NORMAL_TRB, * PXHCI_NORMAL_TRB;

//offset 0
#define XHCI_NORMAL_TRB_DATA_BUFFER_PTR_LO_MASK             UINT32_MAX
#define XHCI_NORMAL_TRB_DATA_BUFFER_PTR_LO_SHIFT            0
#define XHCI_NORMAL_TRB_DATA_BUFFER_PTR_LO                  (XHCI_NORMAL_TRB_DATA_BUFFER_PTR_LO_MASK << XHCI_NORMAL_TRB_DATA_BUFFER_PTR_LO_SHIFT)

//offset 4
#define XHCI_NORMAL_TRB_DATA_BUFFER_PTR_HI_MASK             UINT32_MAX
#define XHCI_NORMAL_TRB_DATA_BUFFER_PTR_HI_SHIFT            0
#define XHCI_NORMAL_TRB_DATA_BUFFER_PTR_HI                  (XHCI_NORMAL_TRB_DATA_BUFFER_PTR_HI_MASK << XHCI_NORMAL_TRB_DATA_BUFFER_PTR_HI_SHIFT)

//offset 8
#define XHCI_NORMAL_TRB_TRB_TRANSFER_LENGTH_MASK            0x0001FFFF
#define XHCI_NORMAL_TRB_TRB_TRANSFER_LENGTH_SHIFT           0
#define XHCI_NORMAL_TRB_TRB_TRANSFER_LENGTH                 (XHCI_NORMAL_TRB_TRB_TRANSFER_LENGTH_MASK << XHCI_NORMAL_TRB_TRB_TRANSFER_LENGTH_SHIFT)
#define XHCI_NORMAL_TRB_TD_SIZE_MASK                        0x1F
#define XHCI_NORMAL_TRB_TD_SIZE_SHIFT                       17
#define XHCI_NORMAL_TRB_TD_SIZE                             (XHCI_NORMAL_TRB_TD_SIZE_MASK << XHCI_NORMAL_TRB_TD_SIZE_SHIFT)
#define XHCI_NROMAL_TRB_INTERRUPT_TARGET_MASK               0x03FF
#define XHCI_NROMAL_TRB_INTERRUPT_TARGET_SHIFT              22
#define XHCI_NROMAL_TRB_INTERRUPT_TARGET                    (XHCI_NROMAL_TRB_INTERRUPT_TARGET_MASK << XHCI_NROMAL_TRB_INTERRUPT_TARGET_SHIFT)

//offset 12
#define XHCI_NORMAL_TRB_CYCLE_BIT_MASK                      1
#define XHCI_NORMAL_TRB_CYCLE_BIT_SHIFT                     0
#define XHCI_NORMAL_TRB_CYCLE_BIT                           (XHCI_NORMAL_TRB_CYCLE_BIT_MASK << XHCI_NORMAL_TRB_CYCLE_BIT_SHIFT)
#define XHCI_NORMAL_TRB_ENT_MASK                            1
#define XHCI_NORMAL_TRB_ENT_SHIFT                           1
#define XHCI_NORMAL_TRB_ENT                                 (XHCI_NORMAL_TRB_ENT_MASK << XHCI_NORMAL_TRB_ENT_SHIFT)
#define XHCI_NORMAL_TRB_ISP_MASK                            1
#define XHCI_NORMAL_TRB_ISP_SHIFT                           2
#define XHCI_NORMAL_TRB_ISP                                 (XHCI_NORMAL_TRB_ISP_MASK << XHCI_NORMAL_TRB_ISP_SHIFT)
#define XHCI_NORMAL_TRB_NS_MASK                             1
#define XHCI_NORMAL_TRB_NS_SHIFT                            3
#define XHCI_NORMAL_TRB_NS                                  (XHCI_NORMAL_TRB_NS_MASK << XHCI_NORMAL_TRB_NS_SHIFT)
#define XHCI_NORMAL_TRB_CH_MASK                             1
#define XHCI_NORMAL_TRB_CH_SHIFT                            4
#define XHCI_NORMAL_TRB_CH                                  (XHCI_NORMAL_TRB_CH_MASK << XHCI_NORMAL_TRB_CH_SHIFT)
#define XHCI_NORMAL_TRB_IOC_MASK                            1
#define XHCI_NORMAL_TRB_IOC_SHIFT                           5
#define XHCI_NORMAL_TRB_IOC                                 (XHCI_NORMAL_TRB_IOC_MASK << XHCI_NORMAL_TRB_IOC_SHIFT)
#define XHCI_NORMAL_TRB_IDT_MASK                            1
#define XHCI_NORMAL_TRB_IDT_SHIFT                           6
#define XHCI_NORMAL_TRB_IDT                                 (XHCI_NORMAL_TRB_IDT_MASK << XHCI_NORMAL_TRB_IDT_SHIFT)
#define XHCI_NORMAL_TRB_TRB_TYPE_MASK                       0x3F
#define XHCI_NORMAL_TRB_TRB_TYPE_SHIFT                      10
#define XHCI_NORMAL_TRB_TRB_TYPE                            (XHCI_NORMAL_TRB_TRB_TYPE_MASK << XHCI_NORMAL_TRB_TRB_TYPE_SHIFT)

//control TRBs will have Setup then Data if required then Status TDs

typedef struct PACKED _XHCI_SETUP_STAGE_TRB{
    UINT32      DWord[4];
}XHCI_SETUP_STAGE_TRB, * PXHCI_SETUP_STAGE_TRB;

//offset 0
#define XHCI_SETUP_STAGE_TRB_REQUEST_TYPE_MASK              0xFF
#define XHCI_SETUP_STAGE_TRB_REQUEST_TYPE_SHIFT             0
#define XHCI_SETUP_STAGE_TRB_REQUEST_TYPE                   (XHCI_SETUP_STAGE_TRB_REQUEST_TYPE_MASK << XHCI_SETUP_STAGE_TRB_REQUEST_TYPE_SHIFT)
#define XHCI_SETUP_STAGE_TRB_REQUEST_MASK                   0xFF
#define XHCI_SETUP_STAGE_TRB_REQUEST_SHIFT                  8
#define XHCI_SETUP_STAGE_TRB_REQUEST                        (XHCI_SETUP_STAGE_TRB_REQUEST_MASK << XHCI_SETUP_STAGE_TRB_REQUEST_SHIFT)
#define XHCI_SETUP_STAGE_TRB_VALUE_MASK                     0xFFFF
#define XHCI_SETUP_STAGE_TRB_VALUE_SHIFT                    16
#define XHCI_SETUP_STAGE_TRB_VALUE                          (XHCI_SETUP_STAGE_TRB_VALUE_MASK << XHCI_SETUP_STAGE_TRB_VALUE_SHIFT)

//offset 4
#define XHCI_SETUP_STAGE_TRB_INDEX_MASK                     0xFFFF
#define XHCI_SETUP_STAGE_TRB_INDEX_SHIFT                    0
#define XHCI_SETUP_STAGE_TRB_INDEX                          (XHCI_SETUP_STAGE_TRB_INDEX_MASK << XHCI_SETUP_STAGE_TRB_INDEX_SHIFT)
#define XHCI_SETUP_STAGE_TRB_LENGTH_MASK                    0xFFFF
#define XHCI_SETUP_STAGE_TRB_LENGTH_SHIFT                   16
#define XHCI_SETUP_STAGE_TRB_LENGTH                         (XHCI_SETUP_STAGE_TRB_LENGTH_MASK << XHCI_SETUP_STAGE_TRB_LENGTH_SHIFT)

//offset 8
#define XHCI_SETUP_STAGE_TRB_TRANSFER_LENGTH_MASK           0x0001FFFF
#define XHCI_SETUP_STAGE_TRB_TRANSFER_LENGTH_SHIFT          0
#define XHCI_SETUP_STAGE_TRB_TRANSFER_LENGTH                (XHCI_SETUP_STAGE_TRB_TRANSFER_LENGTH_MASK << XHCI_SETUP_STAGE_TRB_TRANSFER_LENGTH) //always 8
#define XHCI_SETUP_STAGE_TRB_INTERRUT_TARGET_MASK           0x03FF
#define XHCI_SETUP_STAGE_TRB_INTERRUT_TARGET_SHIFT          22
#define XHCI_SETUP_STAGE_TRB_INTERRUT_TARGET                (XHCI_SETUP_STAGE_TRB_INTERRUT_TARGET_MASK << XHCI_SETUP_STAGE_TRB_INTERRUT_TARGET_SHIFT)

//offset 12
#define XHCI_SETUP_STAGE_TRB_CYCLE_BIT_MASK                 1
#define XHCI_SETUP_STAGE_TRB_CYCLE_BIT_SHIFT                0
#define XHCI_SETUP_STAGE_TRB_CYCLE_BIT                      (XHCI_SETUP_STAGE_TRB_CYCLE_BIT_MASK << XHCI_SETUP_STAGE_TRB_CYCLE_BIT_SHIFT)
#define XHCI_SETUP_STAGE_TRB_IOC_MASK                       1
#define XHCI_SETUP_STAGE_TRB_IOC_SHIFT                      5
#define XHCI_SETUP_STAGE_TRB_IOC                            (XHCI_SETUP_STAGE_TRB_IOC_MASK << XHCI_SETUP_STAGE_TRB_IOC_SHIFT)
#define XHCI_SETUP_STAGE_TRB_IDT_MASK                       1
#define XHCI_SETUP_STAGE_TRB_IDT_SHIFT                      6
#define XHCI_SETUP_STAGE_TRB_IDT                            (XHCI_SETUP_STAGE_TRB_IDT_MASK << XHCI_SETUP_STAGE_TRB_IDT_SHIFT)
#define XHCI_SETUP_STAGE_TRB_TYPE_MASK                      0x3F
#define XHCI_SETUP_STAGE_TRB_TYPE_SHIFT                     10
#define XHCI_SETUP_STAGE_TRB_TYPE                           (XHCI_SETUP_STAGE_TRB_TYPE_MASK << XHCI_SETUP_STAGE_TRB_TYPE_SHIFT)
#define XHCI_SETUP_STAGE_TRB_TRANSFER_TYPE_MASK             0x03
#define XHCI_SETUP_STAGE_TRB_TRANSFER_TYPE_SHIFT            16
#define XHCI_SETUP_STAGE_TRB_TRANSFER_TYPE                  (XHCI_SETUP_STAGE_TRB_TRANSFER_TYPE_MASK << XHCI_SETUP_STAGE_TRB_TRANSFER_TYPE_SHIFT)

typedef struct PACKED _XHCI_DATA_STAGE_TRB{
    UINT32  DWord[4];
}XHCI_DATA_STAGE_TRB, * PXHCI_DATA_STAGE_TRB;

//offset 0
#define XHCI_DATA_STAGE_TRB_DATA_BUFFER_LO_MASK             UINT32_MAX
#define XHCI_DATA_STAGE_TRB_DATA_BUFFER_LO_SHIFT            0
#define XHCI_DATA_STAGE_TRB_DATA_BUFFER_LO                  (XHCI_DATA_STAGE_TRB_DATA_BUFFER_LO_MASK << XHCI_DATA_STAGE_TRB_DATA_BUFFER_LO_SHIFT)

//offset 4
#define XHCI_DATA_STAGE_TRB_DATA_BUFFER_HI_MASK             UINT32_MAX
#define XHCI_DATA_STAGE_TRB_DATA_BUFFER_HI_SHIFT            0
#define XHCI_DATA_STAGE_TRB_DATA_BUFFER_HI                  (XHCI_DATA_STAGE_TRB_DATA_BUFFER_HI_MASK << XHCI_DATA_STAGE_TRB_DATA_BUFFER_HI_SHIFT)

//offset 8
#define XHCI_DATA_STAGE_TRB_TRANSFER_LENGTH_MASK            0x0001FFFF
#define XHCI_DATA_STAGE_TRB_TRANSFER_LENGTH_SHIFT           0
#define XHCI_DATA_STAGE_TRB_TRANSFER_LENGTH                 (XHCI_DATA_STAGE_TRB_TRANSFER_LENGTH_MASK << XHCI_DATA_STAGE_TRB_TRANSFER_LENGTH_SHIFT)
#define XHCI_DATA_STAGE_TRB_TD_SIZE_MASK                    0x1F
#define XHCI_DATA_STAGE_TRB_TD_SIZE_SHIFT                   17
#define XHCI_DATA_STAGE_TRB_TD_SIZE                         (XHCI_DATA_STAGE_TRB_TD_SIZE_MASK << XHCI_DATA_STAGE_TRB_TD_SIZE_SHIFT)
#define XHCI_DATA_STAGE_TRB_INTERRUPT_TARGET_MASK           0x03FF
#define XHCI_DATA_STAGE_TRB_INTERRUPT_TARGET_SHIFT          22
#define XHCI_DATA_STAGE_TRB_INTERRUPT_TARGET                (XHCI_DATA_STAGE_TRB_INTERRUPT_TARGET_MASK << XHCI_DATA_STAGE_TRB_INTERRUPT_TARGET_SHIFT)

//offset 12
#define XHCI_DATA_STAGE_TRB_CYCLE_BIT_MASK                  1
#define XHCI_DATA_STAGE_TRB_CYCLE_BIT_SHIFT                 0
#define XHCI_DATA_STAGE_TRB_CYCLE_BIT                       (XHCI_DATA_STAGE_TRB_CYCLE_BIT_MASK << XHCI_DATA_STAGE_TRB_CYCLE_BIT_SHIFT)
#define XHCI_DATA_STAGE_TRB_ENT_MASK                        1
#define XHCI_DATA_STAGE_TRB_ENT_SHIFT                       1
#define XHCI_DATA_STAGE_TRB_ENT                             (XHCI_DATA_STAGE_TRB_ENT_MASK << XHCI_DATA_STAGE_TRB_ENT_SHIFT)
#define XHCI_DATA_STAGE_TRB_ISP_MASK                        1
#define XHCI_DATA_STAGE_TRB_ISP_SHIFT                       2
#define XHCI_DATA_STAGE_TRB_ISP                             (XHCI_DATA_STAGE_TRB_ISP_MASK << XHCI_DATA_STAGE_TRB_ISP_SHIFT)
#define XHCI_DATA_STAGE_TRB_NS_MASK                         1
#define XHCI_DATA_STAGE_TRB_NS_SHIFT                        3
#define XHCI_DATA_STAGE_TRB_NS                              (XHCI_DATA_STAGE_TRB_NS_MASK << XHCI_DATA_STAGE_TRB_NS_SHIFT)
#define XHCI_DATA_STAGE_TRB_CH_MASK                         1
#define XHCI_DATA_STAGE_TRB_CH_SHIFT                        4
#define XHCI_DATA_STAGE_TRB_CH                              (XHCI_DATA_STAGE_TRB_CH_MASK << XHCI_DATA_STAGE_TRB_CH_SHIFT)
#define XHCI_DATA_STAGE_TRB_IOC_MASK                        1
#define XHCI_DATA_STAGE_TRB_IOC_SHIFT                       5
#define XHIC_DATA_STAGE_TRB_IOC                             (XHIC_DATA_STAGE_TRB_IOC_MASK << XHIC_DATA_STAGE_TRB_IOC_SHIFT)
#define XHCI_DATA_STAGE_TRB_IDT_MASK                        1
#define XHCI_DATA_STAGE_TRB_IDT_SHIFT                       6
#define XHCI_DATA_STAGE_TRB_IDT                             (XHCI_DATA_STAGE_TRB_IDT_MASK << XHCI_DATA_STAGE_TRB_IDT_SHIFT)
#define XHCI_DATA_STAGE_TRB_TYPE_MASK                       0x3F
#define XHCI_DATA_STAGE_TRB_TYPE_SHIFT                      10
#define XHCI_DATA_STAGE_TRB_TYPE                            (XHCI_DATA_STAGE_TRB_TRB_TYPE_MASK << XHCI_DATA_STAGE_TRB_TRB_TYPE_SHIFT)
#define XHCI_DATA_STAGE_TRB_DIR_MASK                        1
#define XHCI_DATA_STAGE_TRB_DIR_SHIFT                       16
#define XHCI_DATA_STAGE_TRB_DIR                             (XHCI_DATA_STAGE_TRB_DIR_MASK << XHCI_DATA_STAGE_TRB_DIR_SHIFT)

typedef struct PACKED _XHCI_STATUS_STAGE_TRB{
    UINT32      DWord[4];
}XHCI_STATUS_STAGE_TRB, * PXHCI_STATUS_STAGE_TRB;

//offset 8
#define XHCI_STATUS_STAGE_TRB_INTERRUPT_TARGET_MASK         0x03FF
#define XHCI_STATUS_STAGE_TRB_INTERRUPT_TARGET_SHIFT        22
#define XHCI_STATUS_STAGE_TRB_INTERRUPT_TARGET              (XHCI_STATUS_STAGE_TRB_INTERRUPT_TARGET_MASK << XHCI_STATUS_STAGE_TRB_INTERRUPT_TARGET_SHIFT)

//offset 12
#define XHCI_STATUS_STAGE_TRB_CYCLE_BIT_MASK                1
#define XHCI_STATUS_STAGE_TRB_CYCLE_BIT_SHIFT               0
#define XHCI_STATUS_STAGE_TRB_CYCLE_BIT                     (XHCI_STATUS_STAGE_TRB_CYCLE_BIT_MASK << XHCI_STATUS_STAGE_TRB_CYCLE_BIT_SHIFT)
#define XHCI_STATUS_STAGE_TRB_ENT_MASK                      1
#define XHCI_STATUS_STAGE_TRB_ENT_SHIFT                     1
#define XHCI_STATUS_STAGE_TRB_ENT                           (XHCI_STATUS_STAGE_TRB_ENT_MASK << XHCI_STATUS_STAGE_TRB_ENT_SHIFT)
#define XHCI_STATUS_STAGE_TRB_CH_MASK                       1
#define XHCI_STATUS_STAGE_TRB_CH_SHIFT                      4
#define XHCI_STATUS_STAGE_TRB_CH                            (XHCI_STATUS_STAGE_TRB_CH_MASK << XHCI_STATUS_STAGE_TRB_CH_SHIFT)                       
#define XHCI_STATUS_STAGE_TRB_IOC_MASK                      1
#define XHCI_STATUS_STAGE_TRB_IOC_SHIFT                     5
#define XHCI_STATUS_STAGE_TRB_IOC                           (XHCI_STATUS_STAGE_TRB_IOC_MASK << XHCI_STATUS_STAGE_TRB_IOC_SHIFT)
#define XHCI_STATUS_STAGE_TRB_TYPE_MASK                     0x3F
#define XHCI_STATUS_STAGE_TRB_TYPE_SHIFT                    10
#define XHCI_STATUS_STAGE_TRB_TYPE                          (XHCI_STATUS_STAGE_TRB_TYPE_MASK << XHCI_STATUS_STAGE_TRB_TYPE_SHIFT)
#define XHCI_STATUS_STAGE_TRB_DIR_MASK                      1
#define XHCI_STATUS_STAGE_TRB_DIR_SHIFT                     16
#define XHCI_STATUS_STAGE_TRB_DIR                           (XHCI_STATUS_STAGE_TRB_DIR_MASK << XHCI_STATUS_STAGE_TRB_DIR_SHIFT)

typedef struct PACKED _XHCI_ISOCH_TRB{
    UINT32      DWord[4];
}XHCI_ISOCH_TRB, * PXHCI_ISOCH_TRB;

//offset 0
#define XHCI_ISOCH_TRB_DATA_BUFFER_LO_MASK                  UINT32_MAX                  
#define XHCI_ISOCH_TRB_DATA_BUFFER_LO_SHIFT                 0
#define XHCI_ISOCH_TRB_DATA_BUFFER_LO                       (XHCI_ISOCH_TRB_DATA_BUFFER_LO_MASK << XHCI_ISOCH_TRB_DATA_BUFFER_LO_SHIFT)

//offset 4
#define XHCI_ISOCH_TRB_DATA_BUFFER_HI_MASK                  UINT32_MAX                  
#define XHCI_ISOCH_TRB_DATA_BUFFER_HI_SHIFT                 0
#define XHCI_ISOCH_TRB_DATA_BUFFER_HI                       (XHCI_ISOCH_TRB_DATA_BUFFER_HI_MASK << XHCI_ISOCH_TRB_DATA_BUFFER_HI_SHIFT)

//offset 8
#define XHCI_ISOCH_TRB_TRANSFER_LENGTH_MASK                 0x0001FFFF
#define XHCI_ISOCH_TRB_TRANSFER_LENGTH_SHIFT                0
#define XHCI_ISOCH_TRB_TRANSFER_LENGTH                      (XHCI_ISOCH_TRB_TRANSFER_LENGTH_MASK << XHCI_ISOCH_TRB_TRANSFER_LENGTH_SHIFT)
#define XHCI_ISOCH_TRB_TD_SIZE_TBC_MASK                     0x1F
#define XHCI_ISOCH_TRB_TD_SIZE_TBC_SHIFT                    17
#define XHCI_ISOCH_TRB_TD_SIZE_TBC                          (XHCI_ISOCH_TRB_TD_SIZE_TBC_MASK << XHCI_ISOCH_TRB_TD_SIZE_TBC_SHIFT)
#define XHCI_ISOCH_TRB_INTERRUPT_TARGET_MASK                0x03FF
#define XHCI_ISOCH_TRB_INTERRUPT_TARGET_SHIFT               22
#define XHCI_ISOCH_TRB_INTERRUPT_TARGET                     (XHCI_ISOCH_TRB_INTERRUPT_TARGET_MASK << XHCI_ISOCH_TRB_INTERRUPT_TARGET_SHIFT)

//offset 12
#define XHCI_ISOCH_TRB_CYCLE_BIT_MASK                       1
#define XHCI_ISOCH_TRB_CYCLE_BIT_SHIFT                      0
#define XHCI_ISOCH_TRB_CYCLE_BIT                            (XHCI_ISOCH_TRB_CYCLE_BIT_MASK << XHCI_ISOCH_TRB_CYCLE_BIT_SHIFT)
#define XHCI_ISOCH_TRB_ENT_MASK                             1
#define XHCI_ISOCH_TRB_ENT_SHIFT                            1
#define XHCI_ISOCH_TRB_ENT                                  (XHCI_ISOCH_TRB_ENT_MASK << XHCI_ISOCH_TRB_ENT_SHIFT)
#define XHCI_ISOCH_TRB_ISP_MASK                             1
#define XHCI_ISOCH_TRB_ISP_SHIFT                            2
#define XHCI_ISOCH_TRB_ISP                                  (XHCI_ISOCH_TRB_ISP_MASK << XHCI_ISOCH_TRB_ISP_SHIFT)
#define XHCI_ISOCH_TRB_NS_MASK                              1
#define XHCI_ISOCH_TRB_NS_SHIFT                             3
#define XHCI_ISOCH_TRB_NS                                   (XHCI_ISOCH_TRB_NS_MASK << XHCI_ISOCH_TRB_NS_SHIFT)
#define XHCI_ISOCH_TRB_CH_MASK                              1
#define XHCI_ISOCH_TRB_CH_SHIFT                             4
#define XHCI_ISOCH_TRB_CH                                   (XHCI_ISOCH_TRB_CH_MASK << XHCI_ISOCH_TRB_CH_SHIFT)
#define XHCI_ISOCH_TRB_IOC_MASK                             1
#define XHCI_ISOCH_TRB_IOC_SHIFT                            5
#define XHCI_ISOCH_TRB_IOC                                  (XHCI_ISOCH_TRB_IOC_MASK << XHCI_ISOCH_TRB_IOC_SHIFT)
#define XHCI_ISOCH_TRB_IDT_MASK                             1
#define XHCI_ISOCH_TRB_IDT_SHIFT                            6
#define XHCI_ISOCH_TRB_IDT                                  (XHCI_ISOCH_TRB_IDT_MASK << XHCI_ISOCH_TRB_IDT_SHIFT)
#define XHCI_ISOCH_TRB_TBC_MASK                             0b11
#define XHCI_ISOCH_TRB_TBC_SHIFT                            7
#define XHCI_ISOCH_TRB_TBC                                  (XHCI_ISOCH_TRB_TBC_MASK << XHCI_ISOCH_TRB_TBC_SHIFT)
#define XHCI_ISOCH_TRB_BEI_MASK                             1
#define XHCI_ISOCH_TRB_BEI_SHIFT                            9
#define XHCI_ISOCH_TRB_BEI                                  (XHCI_ISOCH_TRB_BEI_MASK << XHCI_ISOCH_TRB_BEI_SHIFT)
#define XHCI_ISOCH_TRB_TYPE_MASK                            0x3F
#define XHCI_ISOCH_TRB_TYPE_SHIFT                           10
#define XHCI_ISOCH_TRB_TYPE                                 (XHCI_ISOCH_TRB_TYPE_MASK << XHCI_ISOCH_TRB_TYPE_SHIFT)
#define XHCI_ISOCH_TRB_TLBPC_MASK                           0x0F
#define XHCI_ISOCH_TRB_TLBPC_SHIFT                          16
#define XHCI_ISOCH_TRB_TLBPC                                (XHCI_ISOCH_TRB_TLBPC_MASK << XHCI_ISOCH_TRB_TLBPC_SHIFT)
#define XHCI_ISOCH_TRB_FRAME_ID_MASK                        0x07FF
#define XHCI_ISOCH_TRB_FRAME_ID_SHIFT                       20
#define XHCI_ISOCH_TRB_FRAME_ID                             (XHCI_ISOCH_TRB_FRAME_ID_MASK << XHCI_ISOCH_TRB_FRAME_ID_SHIFT)
#define XHCI_ISOCH_TRB_SIA_MASK                             1
#define XHCI_ISOCH_TRB_SIA_SHIFT                            31
#define XHCI_ISOCH_TRB_SIA                                  (XHCI_ISOCH_TRB_SIA_MASK << XHCI_ISOCH_TRB_SIA_SHIFT)

typedef struct PACKED _XHCI_NO_OP_TRB{
    UINT32  DWord[4];
}XHCI_NO_OP_TRB, * PXHCI_NO_OP_TRB;

//offset 8
#define XHCI_NO_OP_TRB_INTERRUPT_TARGET_MASK                0x03FF
#define XHCI_NO_OP_TRB_INTERRUPT_TARGET_SHIFT               22
#define XHCI_NO_OP_TRB_INTERRUPT_TARGET                     (XHCI_NO_OP_TRB_INTERRUPT_TARGET_MASK << XHCI_NO_OP_TRB_INTERRUPT_TARGET_SHIFT)

//offset 12
#define XHCI_NO_OP_TRB_CYCLE_BIT_MASK                       1
#define XHCI_NO_OP_TRB_CYCLE_BIT_SHIFT                      0
#define XHCI_NO_OP_TRB_CYCLE_BIT                            (XHCI_NO_OP_TRB_CYCLE_BIT_MASK << XHCI_NO_OP_TRB_CYCLE_BIT_SHIFT)
#define XHCI_NO_OP_TRB_ENT_MASK                             1
#define XHCI_NO_OP_TRB_ENT_SHIFT                            1
#define XHCI_NO_OP_TRB_ENT                                  (XHCI_NO_OP_TRB_ENT_MASK << XHCI_NO_OP_TRB_ENT_SHIFT)
#define XHCI_NO_OP_TRB_CH_MASK                              1
#define XHCI_NO_OP_TRB_CH_SHIFT                             4      
#define XHCI_NO_OP_TRB_CH                                   (XHCI_NO_OP_TRB_CH_MASK << XHCI_NO_OP_TRB_CH_SHIFT)
#define XHCI_NO_OP_TRB_IOC_MASK                             1
#define XHCI_NO_OP_TRB_IOC_SHIFT                            5
#define XHCI_NO_OP_TRB_IOC                                  (XHCI_NO_OP_TRB_IOC_MASK << XHCI_NO_OP_TRB_IOC_SHIFT)
#define XHCI_NO_OP_TRB_TYPE_MASK                            0x3F
#define XHCI_NO_OP_TRB_TYPE_TYPE                            10
#define XHCI_NO_OP_TRB_TYPE                                 (XHCI_NO_OP_TRB_TYPE_MASK << XHCI_NO_OP_TRB_TYPE_SHIFT)

typedef struct PACKED _XHCI_TRANSFER_EVENT_TRB{
    UINT32      DWord[4];
}XHCI_TRANSFER_EVENT_TRB, * PXHCI_TRANSFER_EVENT_TRB;

//offset 0
#define XHCI_TRANSFER_EVENT_TRB_PTR_LO_MASK                 UINT32_MAX
#define XHCI_TRANSFER_EVENT_TRB_PTR_LO_SHIFT                0
#define XHCI_TRANSFER_EVENT_TRB_PTR_LO                      (XHCI_TRANSFER_EVENT_TRB_PTR_LO_MASK << XHCI_TRANSFER_EVENT_TRB_PTR_LO_SHIFT)

//offset 4
#define XHCI_TRANSFER_EVENT_TRB_PTR_HI_MASK                 UINT32_MAX
#define XHCI_TRANSFER_EVENT_TRB_PTR_HI_SHIFT                0
#define XHCI_TRANSFER_EVENT_TRB_PTR_HI                      (XHCI_TRANSFER_EVENT_TRB_PTR_HI_MASK << XHCI_TRANSFER_EVENT_TRB_PTR_HI_SHIFT)

//offset 8
#define XHCI_TRANSFER_EVENT_TRB_LENGTH_MASK                 0x00FFFFFF
#define XHCI_TRANSFER_EVENT_TRB_LENGTH_SHIFT                0
#define XHCI_TRANSFER_EVENT_TRB_LENGTH                      (XHCI_TRANSFER_EVENT_TRB_LENGTH_MASK << XHCI_TRANSFER_EVENT_TRB_LENGTH_SHIFT)
#define XHCI_TRANSFER_EVENT_TRB_COMPLETION_CODE_MASK        0xFF
#define XHCI_TRANSFER_EVENT_TRB_COMPLETION_CODE_SHIFT       24
#define XHCI_TRANSFER_EVENT_TRB_COMPLETION_CODE             (XHCI_TRANSFER_EVENT_TRB_COMPLETION_CODE_MASK << XHCI_TRANSFER_EVENT_TRB_COMPLETION_CODE_SHIFT)

//offset 12
#define XHCI_TRANSFER_EVENT_TRB_CYCLE_BIT_MASK              1
#define XHCI_TRANSFER_EVENT_TRB_CYCLE_BIT_SHIFT             0
#define XHCI_TRANSFER_EVENT_TRB_CYCLE_BIT                   (XHCI_TRANSFER_EVENT_TRB_CYCLE_BIT_MASK << XHCI_TRANSFER_EVENT_TRB_CYCLE_BIT_SHIFT)
#define XHCI_TRANSFER_EVENT_TRB_ED_MASK                     1
#define XHCI_TRANSFER_EVENT_TRB_ED_SHIFT                    2
#define XHCI_TRANSFER_EVENT_TRB_ED                          (XHCI_TRANSFER_EVENT_TRB_ED_MASK << XHCI_TRANSFER_EVENT_TRB_ED_SHIFT)
#define XHCI_TRANSFER_EVENT_TRB_TYPE_MASK                   0x3F
#define XHCI_TRANSFER_EVENT_TRB_TYPE_SHIFT                  10
#define XHCI_TRANSFER_EVENT_TRB_TYPE                        (XHCI_TRANSFER_EVENT_TRB_TYPE_MASK << XHCI_TRANSFER_EVENT_TRB_TYPE_SHIFT)
#define XHCI_TRANSFER_EVENT_TRB_ENDPOINT_ID_MASK            0x3F
#define XHCI_TRANSFER_EVENT_TRB_ENDPOINT_ID_SHIFT           16
#define XHCI_TRANSFER_EVENT_TRB_ENDPOINT_ID                 (XHCI_TRANSFER_EVENT_TRB_ENDPOINT_ID_MASK << XHCI_TRANSFER_EVENT_TRB_ENDPOINT_ID_SHIFT)
#define XHCI_TRANSFER_EVENT_TRB_SLOT_ID_MASK                0xFF
#define XHCI_TRANSFER_EVENT_TRB_SLOT_ID_SHIFT               24
#define XHCI_TRANSFER_EVENT_TRB_SLOT_ID                     (XHCI_TRANSFER_EVENT_TRB_SLOT_ID_MASK << XHCI_TRANSFER_EVENT_TRB_SLOT_ID_SHIFT)

typedef struct PACKED _XHCI_COMMAND_COMPLETION_EVENT{
    UINT32      DWord[4];
}XHCI_COMMAND_COMPLETION_EVENT, * PXHCI_COMMAND_COMPLETION_EVENT;

//offset 0
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_LO_MASK                   0x0FFFFFFF
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_LO_SHIFT                  4
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_LO                        (XHCI_COMMAND_COMPLETION_EVENT_TRB_LO_MASK << XHCI_COMMAND_COMPLETION_EVENT_TRB_LO_SHIFT)

//offset 4
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_HI_MASK                   UINT32_MAX
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_HI_SHIFT                     0
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_HI                        (XHCI_COMMAND_COMPLETION_EVENT_TRB_HI_MASK << XHCI_COMMAND_COMPLETION_EVENT_TRB_HI_SHIFT)

//offset 8
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_CCP_MASK                  0x00FFFFFF
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_CCP_SHIFT                 0
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_CCP                       (XHCI_COMMAND_COMPLETION_EVENT_TRB_CCP_MASK << XHCI_COMMAND_COMPLETION_EVENT_TRB_CCP_SHIFT)
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_COMPLETION_CODE_MASK      0xFF
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_COMPLETION_CODE_SHIFT     24
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_COMPLETION_CODE           (XHCI_COMMAND_COMPLETION_EVENT_TRB_COMPLETION_CODE_MASK << XHCI_COMMAND_COMPLETION_EVENT_TRB_COMPLETION_CODE_SHIFT)

//offset 12
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_CYCLE_BIT_MASK            1
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_CYCLE_BIT_SHIFT           0
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_CYCLE_BIT                 (XHCI_COMMAND_COMPLETION_EVENT_TRB_CYCLE_BIT_MASK << XHCI_COMMAND_COMPLETION_EVENT_TRB_CYCLE_BIT_SHIFT)
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_TYPE_MASK                 0x3F
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_TYPE_SHIFT                10
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_TYPE                      (XHCI_COMMAND_COMPLETION_EVENT_TRB_TYPE_MASK << XHCI_COMMAND_COMPLETION_EVENT_TRB_TYPE_SHIFT)
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_VF_ID_MASK                0xFF
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_VF_ID_SHIFT               16
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_VF_ID                     (XHCI_COMMAND_COMPLETION_EVENT_TRB_VF_ID_MASK << XHCI_COMMAND_COMPLETION_EVENT_TRB_VF_ID_SHIFT)
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_SLOT_ID_MASK              0xFF
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_SLOT_ID_SHIFT             24
#define XHCI_COMMAND_COMPLETION_EVENT_TRB_SLOT_ID                   (XHCI_COMMAND_COMPLETION_EVENT_TRB_SLOT_ID_MASK << XHCI_COMMAND_COMPLETION_EVENT_TRB_SLOT_ID_SHIFT)

typedef struct PACKED _XHCI_PORT_STATUS_CHANGE_EVENT_TRB{
    UINT32  DWord[4];
}XHCI_PORT_STATUS_CHANGE_EVENT_TRB, * PXHCI_PORT_STATUS_CHANGE_EVENT_TRB;

//offset 0
#define XHCI_PORT_STATUS_CHANGE_EVENT_TRB_PORT_ID_MASK              0xFF
#define XHCI_PORT_STATUS_CHANGE_EVENT_TRB_PORT_ID_SHIFT             24
#define XHCI_PORT_STATUS_CHANGE_EVENT_TRB_PORT_ID                   (XHCI_PORT_STATUS_CHANGE_EVENT_TRB_PORT_ID_MASK << XHCI_PORT_STATUS_CHANGE_EVENT_TRB_PORT_ID_SHIFT)

//offset 8
#define XHCI_PORT_STATUS_CHANGE_EVENT_TRB_COMPLETION_CODE_MASK      0xFF
#define XHCI_PORT_STATUS_CHANGE_EVENT_TRB_COMPLETION_CODE_SHIFT     24
#define XHCI_PORT_STATUS_CHANGE_EVENT_TRB_COMPLETION_CODE           (XHCI_PORT_STATUS_CHANGE_EVENT_TRB_COMPLETION_CODE_MASK << XHCI_PORT_STATUS_CHANGE_EVENT_TRB_COMPLETION_CODE_SHIFT)

//offset 12
#define XHCI_PORT_STATUS_CHANGE_EVENT_TRB_CYCLE_BIT_MASK            1
#define XHCI_PORT_STATUS_CHANGE_EVENT_TRB_CYCLE_BIT_SHIFT           0
#define XHCI_PORT_STATUS_CHANGE_EVENT_TRB_CYCLE_BIT                 (XHCI_PORT_STATUS_CHANGE_EVENT_TRB_CYCLE_BIT_MASK >> XHCI_PORT_STATUS_CHANGE_EVENT_TRB_CYCLE_BIT_SHIFT)
#define XHCI_PORT_STATUS_CHANGE_EVENT_TRB_TYPE_MASK                 0x3F
#define XHCI_PORT_STATUS_CHANGE_EVENT_TRB_TYPE_SHIFT                10
#define XHCI_PORT_STATUS_CHANGE_EVENT_TRB_TYPE                      (XHCI_PORT_STATUS_CHANGE_EVENT_TRB_TYPE_MASK << XHCI_PORT_STATUS_CHANGE_EVENT_TRB_TYPE_SHIFT)

typedef struct PACKED _XHCI_BANDWIDTH_REQUEST_TRB{
    UINT32  DWord[4];
}XHCI_BANDWIDTH_REQUEST_TRB, * PXHCI_BANDWIDTH_REQUEST_TRB;

//offset 8
#define XHCI_BANDWIDTH_REQUEST_TRB_COMPLETION_CODE_MASK             0xFF
#define XHCI_BANDWIDTH_REQUEST_TRB_COMPLETION_CODE_SHIFT            24
#define XHCI_BANDWIDTH_REQUEST_TRB_COMPLETION_CODE                  (XHCI_BANDWIDTH_REQUEST_TRB_COMPLETION_CODE_MASK << XHCI_BANDWIDTH_REQUEST_TRB_COMPLETION_CODE_SHIFT)

//offset 12
#define XHCI_BANDWIDTH_REQUEST_TRB_CYCLE_BIT_MASK                   1
#define XHCI_BANDWIDTH_REQUEST_TRB_CYCLE_BIT_SHIFT                  0
#define XHCI_BANDWIDTH_REQUEST_TRB_CYCLE_BIT                        (XHCI_BANDWIDTH_REQUEST_TRB_CYCLE_BIT_MASK << XHCI_BANDWIDTH_REQUEST_TRB_CYCLE_BIT_SHIFT)
#define XHCI_BANDWIDTH_REQUEST_TRB_TYPE_MASK                        0x3F
#define XHCI_BANDWIDTH_REQUEST_TRB_TYPE_SHIFT                       10
#define XHCI_BANDWIDTH_REQUEST_TRB_TYPE                             (XHCI_BANDWIDTH_REQUEST_TRB_TYPE_MASK << XHCI_BANDWIDTH_REQUEST_TRB_TYPE_SHIFT)
#define XHCI_BANDWIDTH_REQUEST_TRB_SLOT_ID_MASK                     0xFF
#define XHCI_BANDWIDTH_REQUEST_TRB_SLOT_ID_SHIFT                    24

typedef struct PACKED _XHCI_DOORBELL_EVENT_TRB{
    UINT32  DWord[4];
}XHCI_DOORBELL_EVENT_TRB, * PXHCI_DOORBELL_EVENT_TRB;

//offset 0
#define XHCI_DOORBELL_EVENT_TRB_DB_REASON_MASK                      0x0F
#define XHCI_DOORBELL_EVENT_TRB_DB_REASON_SHIFT                     0
#define XHCI_DOORBELL_EVENT_TRB_DB_REASON                           (XHCI_DOORBELL_EVENT_TRB_DB_REASON_MASK << XHCI_DOORBELL_EVENT_TRB_DB_REASON_SHIFT)

//offset 8
#define XHCI_DOORBELL_EVENT_TRB_COMPLETION_CODE_MASK                0xFF
#define XHCI_DOORBELL_EVENT_TRB_COMPLETION_CODE_SHIFT               24
#define XHCI_DOORBELL_EVENT_TRB_COMPLETION_CODE                     (XHCI_DOORBELL_EVENT_TRB_COMPLETION_CODE_MASK << XHCI_DOORBELL_EVENT_TRB_COMPLETION_CODE_SHIFT)

//offset 12
#define XHCI_DOORBELL_EVENT_TRB_CYCLE_BIT_MASK                      1
#define XHCI_DOORBELL_EVENT_TRB_CYCLE_BIT_SHIFT                     0
#define XHCI_DOORBELL_EVENT_TRB_CYCLE_BIT                           (XHCI_DOORBELL_EVENT_TRB_CYCLE_BIT_MASK << XHCI_DOORBELL_EVENT_TRB_CYCLE_BIT_SHIFT)
#define XHCI_DOORBELL_EVENT_TRB_TYPE_MASK                           0x3F
#define XHCI_DOORBELL_EVENT_TRB_TYPE_SHIFT                          10
#define XHCI_DOORBELL_EVENT_TRB_TYPE                                (XHCI_DOORBELL_EVENT_TRB_TYPE_MASK << XHCI_DOORBELL_EVENT_TRB_TYPE_SHIFT)
#define XHCI_DOORBELL_EVENT_TRB_VF_ID_MASK                          0xFF
#define XHCI_DOORBELL_EVENT_TRB_VF_ID_SHIFT                         16
#define XHCI_DOORBELL_EVENT_TRB_VF_ID                               (XHCI_DOORBELL_EVENT_TRB_VF_ID_MASK << XHCI_DOORBELL_EVENT_TRB_VF_ID_SHIFT)
#define XHCI_DOORBELL_EVENT_TRB_SLOT_ID_MASK                        0xFF
#define XHCI_DOORBELL_EVENT_TRB_SLOT_ID_SHIFT                       24
#define XHCI_DOORBELL_EVENT_TRB_SLOT_ID                             (XHCI_DOORBELL_EVENT_TRB_SLOT_ID_MASK << XHCI_DOORBELL_EVENT_TRB_SLOT_ID_SHIFT)

typedef struct PACKED _XHCI_HOST_CONTROLLER_EVENT_TRB{
    UINT32  DWord[4];
}XHCI_HOST_CONTROLLER_EVENT_TRB, * PXHCI_HOST_CONTROLLER_EVENT_TRB;

//offset 8
#define XHCI_HOST_CONTROLLER_EVENT_TRB_COMPLETION_CODE_MASK         0xFF
#define XHCI_HOST_CONTROLLER_EVENT_TRB_COMPLETION_CODE_SHIFT        24
#define XHCI_HOST_CONTROLLER_EVENT_TRB_COMPLETION_CODE              (XHCI_HOST_CONTROLLER_EVENT_TRB_COMPLETION_CODE_MASK << XHCI_HOST_CONTROLLER_EVENT_TRB_COMPLETION_CODE_SHIFT)

//offset 12
#define XHCI_HOST_CONTROLLER_EVENT_TRB_CYCLE_BIT_MASK               1
#define XHCI_HOST_CONTROLLER_EVENT_TRB_CYCLE_BIT_SHIFT              0
#define XHCI_HOST_CONTROLLER_EVENT_TRB_CYCLE_BIT                    (XHCI_HOST_CONTROLLER_EVENT_TRB_CYCLE_BIT_MASK << XHCI_HOST_CONTROLLER_EVENT_TRB_CYCLE_BIT_SHIFT)
#define XHCI_HOST_CONTROLLER_EVENT_TRB_TYPE_MASK                    0x3F
#define XHCI_HOST_CONTROLLER_EVENT_TRB_TYPE_SHIFT                   10
#define XHCI_HOST_CONTROLLER_EVENT_TRB_TYPE                         (XHCI_HOST_CONTROLLER_EVENT_TRB_TYPE_MASK << XHCI_HOST_CONTROLLER_EVENT_TRB_TYPE_SHIFT)

typedef struct _XHCI_DEVICE_NOTIFICATION_EVENT_TRB{
    UINT32  DWord[4];
}XHCI_DEVICE_NOTIFICATION_EVENT_TRB, * PXHCI_DEVICE_NOTIFICATION_EVENT_TRB;

#define XHCI_DEVICE_NOTIFICATION_EVENT_TRB_NOTIFICATION_TYPE_MASK   0x0F
#define XHCI_DEVICE_NOTIFICATION_EVENT_TRB_NOTIFICATION_TYPE_SHIFT  4
#define XHCI_DEVICE_NOTIFICATION_EVENT_TRB_NOTIFICATION_TYPE        (XHCI_DEVICE_NOTIFICATION_EVENT_TRB_NOTIFICATION_TYPE_MASK << XHCI_DEVICE_NOTIFICATION_EVENT_TRB_NOTIFICATION_TYPE_SHIFT)
#define XHCI_DEVICE_NOTIFICATION_EVENT_TRB_DND_LO_MASK              0x0FFFFFFF
#define XHCI_DEVICE_NOTIFICATION_EVENT_TRB_DND_LO_SHIFT             8
#define XHCI_DEVICE_NOTIFICATION_EVENT_TRB_DND_LO                   (XHCI_DEVICE_NOTIFICATION_EVENT_TRB_DND_MASK << XHCI_DEVICE_NOTIFICATION_EVENT_TRB_DND_SHIFT)

//offset 4
#define XHCI_DEVICE_NOTIFICATION_EVENT_TRB_DND_HI_MASK              UINT32_MAX
#define XHCI_DEVICE_NOTIFICATION_EVENT_TRB_DND_HI_SHIFT             0
#define XHCI_DEVICE_NOTIFICATION_EVENT_TRB_DND_HI                   (XHCI_DEVICE_NOTIFICATION_EVENT_TRB_DND_HI_MASK << XHCI_DEVICE_NOTIFICATION_EVENT_TRB_DND_HI_SHIFT)

//offset 8
#define XHCI_DEVICE_NOTIFICATION_EVENT_TRB_CYCLE_BIT_MASK           1
#define XHCI_DEVICE_NOTIFICATION_EVENT_TRB_CYCLE_BIT_SHIFT          0
#define XHCI_DEVICE_NOTIFICATION_EVENT_TRB_CYCLE_BIT                (XHCI_DEVICE_NOTIFICATION_EVENT_TRB_CYCLE_BIT_MASK << XHCI_DEVICE_NOTIFICATION_EVENT_TRB_CYCLE_BIT_SHIFT)
#define XHCI_DEVICE_NOTIFICATION_EVENT_TRB_TYPE_MASK                0x3F
#define XHCI_DEVICE_NOTIFICATION_EVENT_TRB_TYPE_SHIFT               10
#define XHCI_DEVICE_NOTIFICATION_EVENT_TRB_TYPE                     (XHCI_DEVICE_NOTIFICATION_EVENT_TRB_TYPE_MASK << XHCI_DEVICE_NOTIFICATION_EVENT_TRB_TYPE_SHIFT)
#define XHCI_DEVICE_NOTIFICATION_EVENT_TRB_SLOT_ID_MASK             0xFF
#define XHCI_DEVICE_NOTIFICATION_EVENT_TRB_SLOT_ID_SHIFT            24
#define XHCI_DEVICE_NOTIFICATION_EVENT_TRB_SLOT_ID                  (XHCI_DEVICE_NOTIFICATION_EVENT_TRB_SLOT_ID_MASK << XHCI_DEVICE_NOTIFICATION_EVENT_TRB_SLOT_ID_SHIFT)

typedef struct PACKED _XHCI_MFINDEX_WRAP_EVENT_TRB{
    UINT32  DWord;
}XHCI_MFINDEX_WRAP_EVENT_TRB, * PXHCI_MFINDEX_WRAP_EVENT_TRB;

//offset 8
#define XHCI_MFINDEX_WRAP_EVENT_TRB_COMPLETION_CODE_MASK            0xFF
#define XHCI_MFINDEX_WRAP_EVENT_TRB_COMPLETION_CODE_SHIFT           24
#define XHCI_MFINDEX_WRAP_EVENT_TRB_COMPLETION_CODE                 (XHCI_MFINDEX_WRAP_EVENT_TRB_COMPLETION_CODE_MASK << XHCI_MFINDEX_WRAP_EVENT_TRB_COMPLETION_CODE_SHIFT)

//offset 12
#define XHCI_MFINDEX_WRAP_EVENT_TRB_CYCLE_BIT_MASK                  1
#define XHCI_MFINDEX_WRAP_EVENT_TRB_CYCLE_BIT_SHIFT                 0
#define XHCI_MFINDEX_WRAP_EVENT_TRB_CYCLE_BIT                       (XHCI_MFINDEX_WRAP_EVENT_TRB_CYCLE_BIT_MASK << XHCI_MFINDEX_WRAP_EVENT_TRB_CYCLE_BIT_SHIFT)
#define XHCI_MFINDEX_WRAP_EVENT_TRB_TYPE_MASK                       0x3F
#define XHCI_MFINDEX_WRAP_EVENT_TRB_TYPE_SHIFT                      10
#define XHCI_MFINDEX_WRAP_EVENT_TRB_TYPE                            (XHCI_MFINDEX_WRAP_EVENT_TRB_TYPE_MASK << XHCI_MFINDEX_WRAP_EVENT_TRB_TYPE_SHIFT)

typedef struct PACKED _XHCI_NO_OP_COMMAND_TRB{
    UINT32 DWord[4];
}XHCI_NO_OP_COMMAND_TRB, * PXHCI_NO_OP_COMMAND_TRB;

//offset 12
#define XHCI_NO_OP_COMMAND_TRB_CYCLE_BIT_MASK                       1
#define XHCI_NO_OP_COMMAND_TRB_CYCLE_BIT_SHIFT                      0
#define XHCI_NO_OP_COMMAND_TRB_CYCLE_BIT                            (XHCI_NO_OP_COMMAND_TRB_CYCLE_BIT_MASK << XHCI_NO_OP_COMMAND_TRB_CYCLE_BIT_SHIFT)
#define XHCI_NO_OP_COMMAND_TRB_TYPE_MASK                            0x3F
#define XHCI_NO_OP_COMMAND_TRB_TYPE_SHIFT                           10
#define XHCI_NO_OP_COMMAND_TRB_TYPE                                 (XHCI_NO_OP_COMMAND_TRB_TYPE_MASK << XHCI_NO_OP_COMMAND_TRB_TYPE_SHIFT)

typedef struct PACKED _XHCI_ENABLE_SLOT_COMMAND_TRB{
    UINT32  DWord[4];
}XHCI_ENABLE_SLOT_COMMAND_TRB, * PXHCI_ENABLE_SLOT_COMMAND_TRB;

//offset 12
#define XHCI_ENABLE_SLOT_COMMAND_TRB_CYCLE_BIT_MASK                 1
#define XHCI_ENABLE_SLOT_COMMAND_TRB_CYCLE_BIT_SHIFT                0
#define XHCI_ENABLE_SLOT_COMMAND_TRB_CYCLE_BIT                      (XHCI_ENABLE_SLOT_COMMAND_TRB_CYCLE_BIT_MASK << XHCI_ENABLE_SLOT_COMMAND_TRB_CYCLE_BIT_SHIFT)
#define XHCI_ENABLE_SLOT_COMMAND_TRB_TYPE_MASK                      0x3F
#define XHCI_ENABLE_SLOT_COMMAND_TRB_TYPE_SHIFT                     10
#define XHCI_ENABLE_SLOT_COMMAND_TRB_TYPE                           (XHCI_ENABLE_SLOT_COMMAND_TRB_TYPE_MASK << XHCI_ENABLE_SLOT_COMMAND_TRB_TYPE_SHIFT)
#define XHCI_ENABLE_SLOT_COMMAND_TRB_SLOT_TYPE_MASK                 0x1F
#define XHCI_ENABLE_SLOT_COMMAND_TRB_SLOT_TYPE_SHIFT                16
#define XHCI_ENABLE_SLOT_COMMAND_TRB_SLOT_TYPE                      (XHCI_ENABLE_SLOT_COMMAND_TRB_SLOT_TYPE_MASK << XHCI_ENABLE_SLOT_COMMAND_TRB_SLOT_TYPE_SHIFT)

typedef struct PACKED _XHCI_DISABLE_SLOT_TRB{
    UINT32 DWord[4];
}XHCI_DISABLE_SLOT_TRB, * PXHCI_DISABLE_SLOT_TRB;

//offset 12
#define XHCI_DISABLE_SLOT_TRB_CYCLE_BIT_MASK                        1
#define XHCI_DISABLE_SLOT_TRB_CYCLE_BIT_SHIFT                       0
#define XHCI_DISABLE_SLOT_TRB_CYCLE_BIT                             (XHCI_DISABLE_SLOT_TRB_CYCLE_BIT_MASK << XHCI_DISABLE_SLOT_TRB_CYCLE_BIT_SHIFT)
#define XHCI_DISABLE_SLOT_TRB_TYPE_MASK                             0x3F
#define XHCI_DISABLE_SLOT_TRB_TYPE_SHIFT                            10
#define XHCI_DISABLE_SLOT_TRB_TYPE                                  (XHCI_DISABLE_SLOT_TRB_TYPE_MASK << XHCI_DISABLE_SLOT_TRB_TYPE_SHIFT)
#define XHCI_DISABLE_SLOT_TRB_SLOT_ID_MASK                          0xFF
#define XHCI_DISABLE_SLOT_TRB_SLOT_ID_SHIFT                         24
#define XHCI_DISABLE_SLOT_TRB_SLOT_ID                               (XHCI_DISABLE_SLOT_TRB_SLOT_ID_MASK << XHCI_DISABLE_SLOT_TRB_SLOT_ID_SHIFT)

typedef struct PACKED _XHCI_ADDRESS_DEVICE_COMMAND_TRB{
    UINT32  DWord[4];
}XHCI_ADDRESS_DEVICE_COMMAND_TRB, * PXHCI_ADDRESS_DEVICE_COMMAND_TRB;   

//offset 0
#define XHCI_ADDRESS_DEVICE_COMMAND_TRB_INPUT_CONTEXT_PTR_LO_MASK   0x0FFFFFFF
#define XHCI_ADDRESS_DEVICE_COMMAND_TRB_INPUT_CONTEXT_PTR_LO_SHIFT  4
#define XHCI_ADDRESS_DEVICE_COMMAND_TRB_INPUT_CONTEXT_PTR_LO        (XHCI_ADDRESS_DEVICE_COMMAND_TRB_INPUT_CONTEXT_PTR_HI_MASK << XHCI_ADDRESS_DEVICE_COMMAND_TRB_INPUT_CONTEXT_PTR_HI_SHIFT)

//offset 4
#define XHCI_ADDRESS_DEVICE_COMMAND_TRB_INPUT_CONTEXT_PTR_HI_MASK   UINT32_MAX
#define XHCI_ADDRESS_DEVICE_COMMAND_TRB_INPUT_CONTEXT_PTR_HI_SHIFT  0
#define XHCI_ADDRESS_DEVICE_COMMAND_TRB_INPUT_CONTEXT_PTR_HI        (XHCI_ADDRESS_DEVICE_COMMAND_TRB_INPUT_CONTEXT_PTR_HI_MASK << XHCI_ADDRESS_DEVICE_COMMAND_TRB_INPUT_CONTEXT_PTR_HI_SHIFT)

//offset 12
#define XHCI_ADDRESS_DEVICE_COMMAND_TRB_CYCLE_BIT_MASK              1
#define XHCI_ADDRESS_DEVICE_COMMAND_TRB_CYCLE_BIT_SHIFT             0
#define XHCI_ADDRESS_DEVICE_COMMAND_TRB_CYCLE_BIT                   (XHCI_ADDRESS_DEVICE_COMMAND_TRB_CYCLE_BIT_MASK << XHCI_ADDRESS_DEVICE_COMMAND_TRB_CYCLE_BIT_SHIFT)
#define XHCI_ADDRESS_DEVICE_COMMAND_TRB_BSR_MASK                    1
#define XHCI_ADDRESS_DEVICE_COMMAND_TRB_BSR_SHIFT                   9
#define XHCI_ADDRESS_DEVICE_COMMAND_TRB_BSR                         (XHCI_ADDRESS_DEVICE_COMMAND_TRB_BSR_MASK << XHCI_ADDRESS_DEVICE_COMMAND_TRB_BSR_SHIFT)
#define XHCI_ADDRESS_DEVICE_COMMAND_TRB_TYPE_MASK                   0x3F
#define XHCI_ADDRESS_DEVICE_COMMAND_TRB_TYPE_SHIFT                  10
#define XHCI_ADDRESS_DEVICE_COMMAND_TRB_TYPE                        (XHCI_ADDRESS_DEVICE_COMMAND_TRB_TYPE_MASK << XHCI_ADDRESS_DEVICE_COMMAND_TRB_TYPE_SHIFT)
#define XHCI_ADDRESS_DEVICE_COMMAND_TRB_SLOT_ID_MASK                0xFF
#define XHCI_ADDRESS_DEVICE_COMMAND_TRB_SLOT_ID_SHIFT               24
#define XHCI_ADDRESS_DEVICE_COMMAND_TRB_SLOT_ID                     (XHCI_ADDRESS_DEVICE_COMMAND_TRB_SLOT_ID_MASK << XHCI_ADDRESS_DEVICE_COMMAND_TRB_SLOT_ID_SHIFT)

typedef struct PACKED _XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB{
    UINT32  DWord[4];
}XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB, * PXHCI_CONFIGURE_ENDPOINT_COMMAND_TRB;

//offset 0
#define XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_LO_MASK                 0x0FFFFFFF
#define XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_LO_SHIFT                4
#define XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_LO                      (XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_LO_MASK << XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_LO_SHIFT)

//offset 4
#define XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_HI_MASK                 UINT32_MAX
#define XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_HI_SHIFT                0
#define XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_HI                      (XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_HI_MASK << XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_HI_SHIFT)

//offset 12
#define XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_CYCLE_BIT_MASK          1
#define XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_CYCLE_BIT_SHIFT         0
#define XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_CYCLE_BIT               (XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_CYCLE_BIT_MASK << XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_CYCLE_BIT_SHIFT)
#define XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_DC_MASK                 1
#define XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_DC_SHIFT                9
#define XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_DC                      (XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_DC_MASK << XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_DC_SHIFT)
#define XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_TYPE_MASK               0x3F
#define XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_TYPE_SHIFT              10
#define XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_TYPE                    (XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_TYPE_MASK << XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_TYPE_SHIFT)
#define XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_SLOT_ID_MASK            0xFF
#define XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_SLOT_ID_SHIFT           24
#define XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_SLOT_ID                 (XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_SLOT_ID_MASK << XHCI_CONFIGURE_ENDPOINT_COMMAND_TRB_SLOT_ID_SHIFT)

typedef struct PACKED _XHCI_EVALUATE_CONTEXT_COMMAND_TRB{
    UINT32  DWord[4];
}XHCI_EVALUATE_CONTEXT_COMMAND_TRB, * PXHCI_EVALUATE_CONTEXT_COMMAND_TRB;

//offset 0
#define XHCI_EVALUATE_CONTEXT_COMMAND_TRB_LO_MASK                   0x0FFFFFFF
#define XHCI_EVALUATE_CONTEXT_COMMAND_TRB_LO_SHIFT                  4
#define XHCI_EVALUATE_CONTEXT_COMMAND_TRB_LO                        (XHCI_EVALUATE_CONTEXT_COMMAND_TRB_LO_MASK << XHCI_EVALUATE_CONTEXT_COMMAND_TRB_LO_SHIFT)

//offset 8
#define XHCI_EVALUATE_CONTEXT_COMMAND_TRB_HI_MASK                   UINT32_MAX
#define XHCI_EVALUATE_CONTEXT_COMMAND_TRB_HI_SHIFT                  0
#define XHCI_EVALUATE_CONTEXT_COMMAND_TRB_HI                        (XHCI_EVALUATE_CONTEXT_COMMAND_TRB_HI_MASK << XHCI_EVALUATE_CONTEXT_COMMAND_TRB_HI_SHIFT)

//offset 12
#define XHCI_EVALUATE_CONTEXT_COMMAND_TRB_BSR_MASK                  1
#define XHCI_EVALUATE_CONTEXT_COMMAND_TRB_BSR_SHIFT                 9
#define XHCI_EVALUATE_CONTEXT_COMMAND_TRB_BSR                       (XHCI_EVALUATE_CONTEXT_COMMAND_TRB_BSR_MASK << XHCI_EVALUATE_CONTEXT_COMMAND_TRB_BSR_SHIFT)
#define XHCI_EVALUATE_CONTEXT_COMMAND_TRB_TYPE_MASK                 0x3F
#define XHCI_EVALUATE_CONTEXT_COMMAND_TRB_TYPE_SHIFT                10
#define XHCI_EVALUATE_CONTEXT_COMMAND_TRB_TYPE                      (XHCI_EVALUATE_CONTEXT_COMMAND_TRB_TYPE_MASK << XHCI_EVALUATE_CONTEXT_COMMAND_TRB_TYPE_SHIFT)
#define XHCI_EVALUATE_CONTEXT_COMMAND_TRB_SLOT_ID_MASK              0xFF
#define XHCI_EVALUATE_CONTEXT_COMMAND_TRB_SLOT_ID_SHIFT             24
#define XHCI_EVALUATE_CONTEXT_COMMAND_TRB_SLOT_ID                   (XHCI_EVALUATE_CONTEXT_COMMAND_TRB_SLOT_ID_MASK << XHCI_EVALUATE_CONTEXT_COMMAND_TRB_SLOT_ID_SHIFT)

typedef struct PACKED _XHCI_RESET_ENDPOINT_COMMAND_TRB{
    UINT32  DWord[4];
}XHCI_RESET_ENDPOINT_COMMAND_TRB, * PXHCI_RESET_ENDPOINT_COMMAND_TRB;

//offset 12
#define XHCI_RESET_ENDPOINT_COMMAND_TRB_CYCLE_BIT_MASK              1
#define XHCI_RESET_ENDPOINT_COMMAND_TRB_CYCLE_BIT_SHIFT             0
#define XHCI_RESET_ENDPOINT_COMMAND_TRB_CYCLE_BIT                   (XHCI_RESET_ENDPOINT_COMMAND_TRB_CYCLE_BIT_MASK << XHCI_RESET_ENDPOINT_COMMAND_TRB_CYCLE_BIT_SHIFT)
#define XHCI_RESET_ENDPOINT_COMMAND_TRB_TSP_MASK                    1
#define XHCI_RESET_ENDPOINT_COMMAND_TRB_TSP_SHIFT                   9
#define XHCI_RESET_ENDPOINT_COMMAND_TRB_TSP                         (XHCI_RESET_ENDPOINT_COMMAND_TRB_TSP_MASK << XHCI_RESET_ENDPOINT_COMMAND_TRB_TSP_SHIFT)
#define XHCI_RESET_ENDPOINT_COMMAND_TRB_TYPE_MASK                   0x3F
#define XHCI_RESET_ENDPOINT_COMMAND_TRB_TYPE_SHIFT                  10
#define XHCI_RESET_ENDPOINT_COMMAND_TRB_TYPE                        (XHCI_RESET_ENDPOINT_COMMAND_TRB_TYPE_MASK << XHCI_RESET_ENDPOINT_COMMAND_TRB_TYPE_SHIFT)
#define XHCI_RESET_ENDPOINT_COMMAND_TRB_ENDPOINT_ID_MASK            0x1F
#define XHCI_RESET_ENDPOINT_COMMAND_TRB_ENDPOINT_ID_SHIFT           16
#define XHCI_RESET_ENDPOINT_COMMAND_TRB_ENDPOINT_ID                 (XHCI_RESET_ENDPOINT_COMMAND_TRB_ENDPOINT_ID_MASK << XHCI_RESET_ENDPOINT_COMMAND_TRB_ENDPOINT_ID_SHIFT)
#define XHCI_RESET_ENDPOINT_COMMAND_TRB_SLOT_ID_MASK                0xFF
#define XHCI_RESET_ENDPOINT_COMMAND_TRB_SLOT_ID_SHIFT               24
#define XHCI_RESET_ENDPOINT_COMMAND_TRB_SLOT_ID                     (XHCI_RESET_ENDPOINT_COMMAND_TRB_SLOT_ID_MASK << XHCI_RESET_ENDPOINT_COMMAND_TRB_SLOT_ID_SHIFT)

typedef struct PACKED _XHCI_STOP_ENDPOINT_COMMAND_TRB{
    UINT32  DWord[4];
}XHCI_STOP_ENDPOINT_COMMAND_TRB, * PXHCI_STOP_ENDPOINT_COMMAND_TRB;

//offset 12
#define XHCI_STOP_ENDPOINT_COMMAND_TRB_CYCLE_BIT_MASK               1
#define XHCI_STOP_ENDPOINT_COMMAND_TRB_CYCLE_BIT_SHIFT              0
#define XHCI_STOP_ENDPOINT_COMMAND_TRB_CYCLE_BIT                    (XHCI_STOP_ENDPOINT_COMMAND_TRB_CYCLE_BIT_MASK << XHCI_STOP_ENDPOINT_COMMAND_TRB_CYCLE_BIT_SHIFT)
#define XHCI_STOP_ENDPOINT_COMMAND_TRB_TSP_MASK                     1
#define XHCI_STOP_ENDPOINT_COMMAND_TRB_TSP_SHIFT                    9
#define XHCI_STOP_ENDPOINT_COMMAND_TRB_TSP                          (XHCI_STOP_ENDPOINT_COMMAND_TRB_TSP_MASK << XHCI_STOP_ENDPOINT_COMMAND_TRB_TSP_SHIFT)
#define XHCI_STOP_ENDPOINT_COMMAND_TRB_TYPE_MASK                    0x3F
#define XHCI_STOP_ENDPOINT_COMMAND_TRB_TYPE_SHIFT                   10
#define XHCI_STOP_ENDPOINT_COMMAND_TRB_TYPE                         (XHCI_STOP_ENDPOINT_COMMAND_TRB_TYPE_MASK << XHCI_STOP_ENDPOINT_COMMAND_TRB_TYPE_SHIFT)
#define XHCI_STOP_ENDPOINT_COMMAND_TRB_ENDPOINT_ID_MASK             0x1F
#define XHCI_STOP_ENDPOINT_COMMAND_TRB_ENDPOINT_ID_SHIFT            16
#define XHCI_STOP_ENDPOINT_COMMAND_TRB_ENDPOINT_ID                  (XHCI_STOP_ENDPOINT_COMMAND_TRB_ENDPOINT_ID_MASK << XHCI_STOP_ENDPOINT_COMMAND_TRB_ENDPOINT_ID_SHIFT)
#define XHCI_STOP_ENDPOINT_COMMAND_TRB_SP_MASK                      1
#define XHCI_STOP_ENDPOINT_COMMAND_TRB_SP_SHIFT                     23
#define XHCI_STOP_ENDPOINT_COMMAND_TRB_SP                           (XHCI_STOP_ENDPOINT_COMMAND_TRB_SP_MASK << XHCI_STOP_ENDPOINT_COMMAND_TRB_SP_SHIFT)
#define XHCI_STOP_ENDPOINT_COMMAND_TRB_SLOT_ID_MASK                 0xFF
#define XHCI_STOP_ENDPOINT_COMMAND_TRB_SLOT_ID_SHIFT                24
#define XHCI_STOP_ENDPOINT_COMMAND_TRB_SLOT_ID                      (XHCI_STOP_ENDPOINT_COMMAND_TRB_SLOT_ID_MASK << XHCI_STOP_ENDPOINT_COMMAND_TRB_SLOT_ID_SHIFT)

typedef struct PACKED _XHCI_SET_TR_DQUEUE_PTR_COMMAND_TRB{
    UINT32 DWord[4];
}XHCI_SET_TR_DQUEUE_PTR_COMMAND_TRB, * PXHCI_SET_TR_DQUEUE_PTR_COMMAND_TRB;

//offset 0
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_DCS_MASK                1
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_DCS_SHIFT               0
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_DCS                     (XHCI_SET_TR_DQUEUE_PTR_COMMAND_TRB_DCS_MASK << XHCI_SET_TR_DQUEUE_PTR_COMMAND_TRB_DCS_SHIFT)
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_SCT_MASK                0x07
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_SCT_SHIFT               1
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_SCT                     (XHCI_SET_TR_DQUEUE_PTR_COMMAND_TRB_SCT_MASK << XHCI_SET_TR_DQUEUE_PTR_COMMAND_TRB_SCT_SHIFT)
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_LO_MASK                 0x0FFFFFFF
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_LO_SHIFT                4
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_LO                      (XHCI_SET_TR_DQUEUE_PTR_COMMAND_TRB_LO_MASK << XHCI_SET_TR_DQUEUE_PTR_COMMAND_TRB_LO_SHIFT)
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_HI_MASK                 UINT32_MAX
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_HI_SHIFT                0
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_HI                      (XHCI_SET_TR_DQUEUE_PTR_COMMAND_TRB_HI_MASK << XHCI_SET_TR_DQUEUE_PTR_COMMAND_TRB_HI_SHIFT)

//offset 8
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_STREAM_ID_MASK          0xFFFF
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_STREAM_ID_SHIFT         16
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_STREAM_ID               (XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_STREAM_ID_MASK << XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_STREAM_ID_SHIFT)

//offset 12
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_CYCLE_BIT_MASK          1
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_CYCLE_BIT_SHIFT         0
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_CYCLE_BIT               (XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_CYCLE_BIT_MASK << XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_CYCLE_BIT_SHIFT)
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_TYPE_MASK               0x3F
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_TYPE_SHIFT              10
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_TYPE                    (XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_TYPE_MASK << XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_TYPE_SHIFT)
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_ENDPOINT_ID_MASK        0x1F
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_ENDPOINT_ID_SHIFT       16
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_ENDPOINT_ID             (XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_ENDPOINT_ID_MASK << XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_ENDPOINT_ID_SHIFT)
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_SLOT_ID_MASK            0xFF
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_SLOT_ID_SHIFT           24
#define XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_SLOT_ID                 (XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_SLOT_ID_MASK << XHCI_SET_TR_DEQUEUE_PTR_COMMAND_TRB_SLOT_ID_SHIFT)

typedef struct PACKED _XHCI_RESET_DEVICE_COMMAND_TRB{
    UINT32  DWord[4];
}XHCI_RESET_DEVICE_COMMAND_TRB, * PXHCI_RESET_DEVICE_COMMAND_TRB;

#define XHCI_RESET_DEVICE_COMMAND_TRB_CYCLE_BIT_MASK                1
#define XHCI_RESET_DEVICE_COMMAND_TRB_CYCLE_BIT_SHIFT               0
#define XHCI_RESET_DEVICE_COMMAND_TRB_CYCLE_BIT                     (XHCI_RESET_DEVICE_COMMAND_TRB_CYCLE_BIT_MASK << XHCI_RESET_DEVICE_COMMAND_TRB_CYCLE_BIT_SHIFT)
#define XHCI_RESET_DEVICE_COMMAND_TRB_TYPE_MASK                     0x3F
#define XHCI_RESET_DEVICE_COMMAND_TRB_TYPE_SHIFT                    10
#define XHCI_RESET_DEVICE_COMMAND_TRB_TYPE                          (XHCI_RESET_DEVICE_COMMAND_TRB_TYPE_MASK << XHCI_RESET_DEVICE_COMMAND_TRB_TYPE_SHIFT)
#define XHCI_RESET_DEVICE_COMMAND_TRB_SLOT_ID_MASK                  0xFF
#define XHCI_RESET_DEVICE_COMMAND_TRB_SLOT_ID_SHIFT                 24
#define XHCI_RESET_DEVICE_COMMAND_TRB_SLOT_ID                       (XHCI_RESET_DEVICE_COMMAND_TRB_SLOT_ID_MASK << XHCI_RESET_DEVICE_COMMAND_TRB_SLOT_ID_SHIFT)

//496

//page 506 is the end of TRB

//page 591 is the end

#endif