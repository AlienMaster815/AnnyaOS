//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#define _KERNEL_MODULE_
#ifndef _EHCI_H
#define _EHCI_H

#include <LouDDK.h>
#include <Hal.h>

#define EHCI_OPERATIONAL_REGISTER_BAR   0 
#define EHCI_CAP_REGISTER_OFFSET        0

#define EHCI_PCI_SBRN_OFFSET            0x60
#define EHCI_PCI_FLADJ_OFFSET           0x61
#define EHCI_PCI_PORTWAKECAP_OFFSET     0x62

typedef struct _EHCI_PCI_EXTENTIONS{
    UINT8                               Sbrn;
    UINT8                               Fladj;
    UINT16                              Portwakecap;
}EHCI_PCI_EXTENTIONS, * PEHCI_PCI_EXTENTIONS;

typedef struct PACKED _EHCI_CAPABILITY_REGISTERS{
    UINT8       CapLength;
    UINT8       Reserved1;
    UINT16      HciVersion;
    UINT32      HcsParams;
    UINT32      HccParams;
    UINT64      HcspPortRoute;
}EHCI_CAPABILITY_REGISTERS, * PEHCI_CAPABILITY_REGISTERS;

//Hcs Parameters Cap Register
#define EHCI_HCSPARAMS_DEBUG_PORT_NUMBER_MASK                   0x0F
#define EHCI_HCSPARAMS_DEBUG_PORT_NUMBER_SHIFT                  20
#define EHCI_HCSPARAMS_DEBUG_PORT_NUMBER                        (EHCI_HCSPARAMS_DEBUG_PORT_NUMBER_MASK << EHCI_HCSPARAMS_DEBUG_PORT_NUMBER_SHIFT)

#define EHCI_HCSPARAMS_P_INDICATOR_MASK                         1
#define EHCI_HCSPARAMS_P_INDICATOR_SHIFT                        16
#define EHCI_HCSPARAMS_P_INDICATOR                              (EHCI_HCSPARAMS_P_INDICATOR_MASK << EHCI_HCSPARAMS_P_INDICATOR_SHIFT)

#define EHCI_HCSPARAMS_N_CC_MASK                                0x0F     
#define EHCI_HCSPARAMS_N_CC_SHIFT                               12
#define EHCI_HCSPARAMS_N_CC                                     (EHCI_HCSPARAMS_N_CC_MASK << EHCI_HCSPARAMS_N_CC_SHIFT)

#define EHCI_HCSPARAMS_N_PCC_MASK                               0x0F
#define EHCI_HCSPARAMS_N_PCC_SHIFT                              8
#define EHCI_HCSPARAMS_N_PCC                                    (EHCI_HCSPARAMS_N_PCC_MASK << EHCI_HCSPARAMS_N_PCC_SHIFT)

#define EHCI_HCSPARAMS_PRR_MASK                                 1
#define EHCI_HCSPARAMS_PRR_SHIFT                                7
#define EHCI_HCSPARAMS_PRR                                      (EHCI_HCSPARAMS_PRR_MASK << EHCI_HCSPARAMS_PRR_SHIFT)

#define EHCI_HCSPARAMS_PPC_MASK                                 1
#define EHCI_HCSPARAMS_PPC_SHIFT                                4
#define EHCI_HCSPARAMS_PPC                                      (EHCI_HCSPARAMS_PPC_MASK << EHCI_HCSPARAMS_PPC_SHIFT)

#define EHCI_HCSPARAMS_N_PORTS_MASK                             0x0F
#define EHCI_HCSPARAMS_N_PORTS_SHIFT                            0
#define EHCI_HCSPARAMS_N_PORTS                                  (EHCI_HCSPARAMS_N_PORTS_MASK << EHCI_HCSPARAMS_N_PORTS_SHIFT)



//Hcc Parameters Cap Reegister
#define EHCI_HCCPARAMS_EECP_MASK                                0xFF
#define EHCI_HCCPARAMS_EECP_SHIFT                               8
#define EHCI_HCCPARAMS_EECP                                     (EHCI_HCCPARAMS_EECP_MASK << EHCI_HCCPARAMS_EECP_SHIFT)


#define EHCI_HCCPARAMS_IST_MASK                                 0x0F
#define EHCI_HCCPARAMS_IST_SHIFT                                4
#define EHCI_HCCPARAMS_IST                                      (EHCI_HCCPARAMS_IST_MASK << EHCI_HCCPARAMS_IST_SHIFT)


#define EHCI_HCCPARAMS_ASPC_MASK                                1
#define EHCI_HCCPARAMS_ASPC_SHIFT                               2
#define EHCI_HCCPARAMS_ASPC                                     (EHCI_HCCPARAMS_ASPC_MASK << EHCI_HCCPARAMS_ASPC_SHIFT)


#define EHCI_HCCPARAMS_PFLF_MASK                                1
#define EHCI_HCCPARAMS_PFLF_SHIFT                               1
#define EHCI_HCCPARAMS_PFLF                                     (EHCI_HCCPARAMS_PFLF_MASK << EHCI_HCCPARAMS_PFLF_SHIFT)

#define EHCI_HCCPARAMS_64AC_MASK                                1
#define EHCI_HCCPARAMS_64AC_SHIFT                               0                                    
#define EHCI_HCCPARAMS_64AC                                     (EHCI_HCCPARAMS_64AC_MASK << EHCI_HCCPARAMS_64AC_SHIFT)

//TODO: HCSP-PORTROUTE

typedef struct PACKED _EHCI_HOST_OPERATIONAL_REGISTERS{ 
    UINT32      UsbCommand;             //USBCMD
    UINT32      UsbStatus;              //USBSTS
    UINT32      UsbInterruptEnable;     //USBINTR
    UINT32      UsbFrameIndex;          //FRINDEX
    UINT32      ControlDsSegment;       //CTRLDSSEGMENT
    UINT32      FrameListBaseAddress;   //PERIODICLISTBASE
    UINT32      NextAsyncListAddress;   //ASYNCLISTADDR
    UINT8       Reserved[36];
    UINT32      ConfigFlag;             //CONFIGFLAG
    UINT32      PortStatusControl[];    //PORTSC      
}EHCI_HOST_OPERATIONAL_REGISTERS, * PEHCI_HOST_OPERATIONAL_REGISTERS;

#define EHCI_USBCMD_ITC_MASK                    0xFF
#define EHCI_USBCMD_ITC_SHIFT                   16
#define EHCI_USBCMD_ITC                         (EHCI_USBCMD_ITC_MASK << EHCI_USBCMD_ITC_SHIFT)

#define EHCI_USBCMD_ASPME_MASK                  1
#define EHCI_USBCMD_ASPME_SHIFT                 11
#define EHCI_USBCMD_ASPME                       (EHCI_USBCMD_ASPME_MASK << EHCI_USBCMD_ASPME_SHIFT)

#define EHCI_USBCMD_ASPMC_MASK                  3
#define EHCI_USBCMD_ASPMC_SHIFT                 8
#define EHCI_USBCMD_ASPMC                       (EHCI_USBCMD_ASPME_MASK << EHCI_USBCMD_ASPMC_SHIFT)

#define EHCI_USBCMD_LHCR_MASK                   1
#define EHCI_USBCMD_LHCR_SHIFT                  7
#define EHCI_USBCMD_LHCR                        (EHCI_USBCMD_LHCR_MASK << EHCI_USBCMD_LHCR_SHIFT)

#define EHCI_USBCMD_IAAD_MASK                   1
#define EHCI_USBCMD_IAAD_SHIFT                  6
#define EHCI_USBCMD_IAAD                        (EHCI_USBCMD_IAAD_MASK << EHCI_USBCMD_IAAD_SHIFT)

#define EHCI_USBCMD_ASE_MASK                    1
#define EHCI_USBCMD_ASE_SHIFT                   5
#define EHCI_USBCMD_ASE                         (EHCI_USBCMD_ASE_MASK << EHCI_USBCMD_ASE_SHIFT)

#define EHCI_USBCMD_PSE_MASK                    1
#define EHCI_USBCMD_PSE_SHIFT                   4
#define EHCI_USBCMD_PSE                         (EHCI_USBCMD_PSE_MASK << EHCI_USBCMD_PSE_SHIFT)

#define EHCI_USBCMD_FLS_MASK                    3
#define EHCI_USBCMD_FLS_SHIFT                   2
#define EHCI_USBCMD_FLS                         (EHCI_USBCMD_FLS_MASK << EHCI_USBCMD_FLS_SHIFT)

#define EHCI_USBCMD_HCRESET_MASK                1
#define EHCI_USBCMD_HCRESET_SHIFT               1
#define EHCI_USBCMD_HCRESET                     (EHCI_USBCMD_HCRESET_MASK << EHCI_USBCMD_HCRESET_SHIFT)

#define EHCI_USBCMD_RS_MASK                     1
#define EHCI_USBCMD_RS_SHIFT                    0                          
#define EHCI_USBCMD_RS                          (EHCI_USBCMD_RS_MASK << EHCI_USBCMD_RS_SHIFT)

#define EHCI_ITC_1FRAME                         0x01
#define EHCI_ITC_2FRAME                         0x02
#define EHCI_ITC_4FRAME                         0x04
#define EHCI_ITC_8FRAME                         0x08
#define EHCI_ITC_16FRAME                        0x10
#define EHCI_ITC_32FRAME                        0x20
#define EHCI_ITC_64FRAME                        0x40

#define EHCI_FLS_1024ELEMENTS                   0b00
#define EHCI_FLS_512ELEMENTS                    0b01
#define EHCI_FLS_256ELEMENTS                    0b10

//USBSTATUS
#define EHCI_USBSTS_ASS_MASK                    1
#define EHCI_USBSTS_ASS_SHIFT                   15
#define EHCI_USBSTS_PSS_MASK                    1
#define EHCI_USBSTS_PSS_SHIFT                   14
#define EHCI_USBSTS_RECLAMATION_MASK            1
#define EHCI_USBSTS_RECLAMATION_SHIFT           13
#define EHCI_USBSTS_HC_HALTED_MASK              1
#define EHCI_USBSTS_HC_HALTED_SHIFT             12
//the rest are writable
#define EHCI_USBSTS_IAA_MASK                    1
#define EHCI_USBSTS_IAA_SHIFT                   5
#define EHCI_USBSTS_HSE_MASK                    1
#define EHCI_USBSTS_HSE_SHIFT                   4
#define EHCI_USBSTS_FLR_MASK                    1
#define EHCI_USBSTS_FLR_SHIFT                   3
#define EHCI_USBSTS_PCD_MASK                    1
#define EHCI_USBSTS_PCD_SHIFT                   2
#define EHCI_USBSTS_USBERRINT_MASK              1 
#define EHCI_USBSTS_USBERRINT_SHIFT             1 
#define EHCI_USBSTS_USBINT_MASK                 1
#define EHCI_USBSTS_USBINT_SHIFT                0

#define EHCI_USBSTS_ASS                         (EHCI_USBSTS_ASS_MASK << EHCI_USBSTS_ASS_SHIFT)
#define EHCI_USBSTS_PSS                         (EHCI_USBSTS_PSS_MASK << EHCI_USBSTS_PSS_SHIFT)
#define EHCI_USBSTS_RECLAMATION                 (EHCI_USBSTS_RECLAMATION_MASK << EHCI_USBSTS_RECLAMATION_SHIFT)
#define EHCI_USBSTS_HC_HALTED                   (EHCI_USBSTS_HC_HALTED_MASK << EHCI_USBSTS_HC_HALTED_SHIFT)
//the rest are writable
#define EHCI_USBSTS_IAA                         (EHCI_USBSTS_IAA_MASK << EHCI_USBSTS_IAA_SHIFT)
#define EHCI_USBSTS_HSE                         (EHCI_USBSTS_HSE_MASK << EHCI_USBSTS_HSE_SHIFT)
#define EHCI_USBSTS_FLR                         (EHCI_USBSTS_FLR_MASK << EHCI_USBSTS_FLR_SHIFT)
#define EHCI_USBSTS_PCD                         (EHCI_USBSTS_PCD_MASK << EHCI_USBSTS_PCD_SHIFT)
#define EHCI_USBSTS_USBERRINT                   (EHCI_USBSTS_USBERRINT_MASK << EHCI_USBSTS_USBERRINT_SHIFT)
#define EHCI_USBSTS_USBINT                      (EHCI_USBSTS_USBINT_MASK << EHCI_USBSTS_USBINT_SHIFT)

#define EHCI_PFLE_TERMINATE_BIT 1

typedef struct PACKED _EHCI_QH{
    UINT32 HLink;           
    UINT32 EpChar;          
    UINT32 EpCaps;          
    UINT32 CurrentQtd;      
    UINT32 NextQtd;         
    UINT32 AltNextQtd;      
    UINT32 Token;           
    UINT32 Buffer[5];       
    UINT32 ExtendedBuffer[4]; 
}EHCI_QH, * PEHCI_QH;

//PORTSC
#define EHCI_PORTSC_WKOC_E_MASK         1
#define EHCI_PORTSC_WKOC_E_SHIFT        22
#define EHCI_PORTSC_WKOC_E              (EHCI_PORTSC_WKOC_E_MASK << EHCI_PORTSC_WKOC_E_SHIFT) //RW

#define EHCI_PORTSC_WKDSCNNT_E_MASK     1
#define EHCI_PORTSC_WKDSCNNT_E_SHIFT    21
#define EHCI_PORTSC_WKDSCNNT_E          (EHCI_PORTSC_WKDSCNNT_E_MASK << EHCI_PORTSC_WKDSCNNT_E_SHIFT) //RW

#define EHCI_PORTSC_WKCNNT_E_MASK       1
#define EHCI_PORTSC_WKCNNT_E_SHIFT      20
#define EHCI_PORTSC_WKCNNT_E            (EHCI_PORTSC_WKCNNT_E_MASK << EHCI_PORTSC_WKCNNT_E_SHIFT) //RW

#define EHCI_PORTSC_PTC_MASK            0x0F
#define EHCI_PORTSC_PTC_SHIFT           16
#define EHCI_PORTSC_PTC                 (EHCI_PORTSC_PTC_MASK << EHCI_PORTSC_PTC_SHIFT) //RW

#define EHCI_PORTSC_PIC_MASK            3
#define EHCI_PORTSC_PIC_SHIFT           14
#define EHCI_PORTSC_PIC                 (EHCI_PORTSC_PIC_MASK << EHCI_PORTSC_PIC_SHIFT) //R


#define EHCI_PORTSC_PORT_OWNER_MASK     1
#define EHCI_PORTSC_PORT_OWNER_SHIFT    13
#define EHCI_PORTSC_PORT_OWNER          (EHCI_PORTSC_PORT_OWNER_MASK << EHCI_PORTSC_PORT_OWNER_SHIFT) //RW

#define EHCI_PORTSC_PORT_POWER_MASK     1
#define EHCI_PORTSC_PORT_POWER_SHIFT    12
#define EHCI_PORTSC_PORT_POWER          (EHCI_PORTSC_PORT_POWER_MASK << EHCI_PORTSC_PORT_POWER_SHIFT) //RW

#define EHCI_PORTSC_LINE_STATUS_MASK    3
#define EHCI_PORTSC_LINE_STATUS_SHIFT   10
#define EHCI_PORTSC_LINE_STATUS         (EHCI_PORTSC_LINE_STATUS_MASK << EHCI_PORTSC_LINE_STATUS_SHIFT) //R

#define EHCI_PORTSC_PORT_RESET_MASK     1
#define EHCI_PORTSC_PORT_RESET_SHIFT    8
#define EHCI_PORTSC_PORT_RESET          (EHCI_PORTSC_PORT_RESET_MASK << EHCI_PORTSC_PORT_RESET_SHIFT) //RW

#define EHCI_PORTSC_SUSPEND_MASK        1
#define EHCI_PORTSC_SUSPEND_SHIFT       7
#define EHCI_PORTSC_SUSPEND             (EHCI_PORTSC_SUSPEND_MASK << EHCI_PORTSC_SUSPEND_SHIFT) //RW

#define EHCI_PORTSC_FPR_MASK            1
#define EHCI_PORTSC_FPR_SHIFT           6
#define EHCI_PORTSC_FPR                 (EHCI_PORTSC_FPR_MASK << EHCI_PORTSC_FPR_SHIFT) //RW

#define EHCI_PORTSC_OCC_MASK            1
#define EHCI_PORTSC_OCC_SHIFT           5
#define EHCI_PORTSC_OCC                 (EHCI_PORTSC_OCC_MASK << EHCI_PORTSC_OCC_SHIFT) //RW

#define EHCI_PORTSC_OCA_MASK            1
#define EHCI_PORTSC_OCA_SHIFT           4
#define EHCI_PORTSC_OCA                 (EHCI_PORTSC_OCA_MASK << EHCI_PORTSC_OCA_SHIFT) //R

#define EHCI_PORTSC_PEC_MASK            1
#define EHCI_PORTSC_PEC_SHIFT           3
#define EHCI_PORTSC_PEC                 (EHCI_PORTSC_PEC_MASK << EHCI_PORTSC_PEC_SHIFT) //RW

#define EHCI_PORTSC_PORT_ENABLE_MASK    1
#define EHCI_PORTSC_PORT_ENABLE_SHIFT   2
#define EHCI_PORTSC_PORT_ENABLE         (EHCI_PORTSC_PORT_ENABLE_MASK << EHCI_PORTSC_PORT_ENABLE_SHIFT) //RW

#define EHCI_PORTSC_CSC_MASK            1
#define EHCI_PORTSC_CSC_SHIFT           1
#define EHCI_PORTSC_CSC                 (EHCI_PORTSC_CSC_MASK << EHCI_PORTSC_CSC_SHIFT) //RW

#define EHCI_PORTSC_CCS_MASK            1
#define EHCI_PORTSC_CCS_SHIFT           0
#define EHCI_PORTSC_CCS                 (EHCI_PORTSC_CCS_MASK << EHCI_PORTSC_CCS_SHIFT) //R

#define PORTSC_PTC_NOT_ENABLED          0b0000
#define PORTSC_PTC_J_STATE              0b0001
#define PORTSC_PTC_K_STATE              0b0010
#define PORTSC_PTC_SE0_NAK              0b0011
#define PORTSC_PTC_PACKET               0b0100
#define PORTSC_PTR_FORCE_ENABLE         0b0101

#define PORTSC_PIC_OFF                  0b00
#define PORTSC_PIC_AMBER                0b01
#define PORTSC_PIC_GREEN                0b10
#define PORTSC_PIC_UNDEFINED            0b11

#define EHCI_DEVICE_CAPABILITIES_MISC_FLAG_PPC                          (1 << 0)
#define EHCI_DEVICE_CAPABILITIES_MISC_FLAG_PORT_ROUTING_RULES           (1 << 1)
#define EHCI_DEVICE_CAPABILITIES_MISC_FLAG_PORT_INDICATORS              (1 << 2)
#define EHCI_DEVICE_CAPABILITIES_MISC_FLAG_64BIT_DMA                    (1 << 3)
#define EHCI_DEVICE_CAPABILITIES_MISC_FLAG_PROGRAMMABLE_FRAME_LIST      (1 << 4)
#define EHCI_DEVICE_CAPABILITIES_MISC_FLAG_ASYNC_SCHEDULE_PARK          (1 << 5)

typedef struct _EHCI_DEVICE_CAPABILITIES{
    UINT8   EhciMajorVersion;
    UINT8   EhciMinorVersion;
    UINT8   NumberOfPorts;
    UINT8   PortsPerCompanionController;
    UINT8   NumberOfCompanionControllers;
    UINT8   DebugPortNumber;
    UINT8   IsochronusSchedulingThreshold;
    UINT8   EhciExtendedCapabilitiesPointer;
    UINT64  EhciOptionalPortRoute;
    UINT8   EhciMiscFlags;   
}EHCI_DEVICE_CAPABILITIES, * PEHCI_DEVICE_CAPABILITIES;

typedef struct _EHCI_DEVICE_OBJECT{
    PPCI_DEVICE_OBJECT                  PDEV;
    PEHCI_CAPABILITY_REGISTERS          CapabilitiesRegisters;
    PEHCI_HOST_OPERATIONAL_REGISTERS    OperationalRegisters;
    EHCI_DEVICE_CAPABILITIES            EhciDeviceCapabilities;

/*
    UINTPTR                             PeriodicFrameListBase;
    UINTPTR                             AshQHAddress;
    EHCI_PCI_EXTENTIONS                 Extentions;
    BOOL                                Dma64Supported;
    BOOL                                PortIndicatorSupport;
    BOOL                                EhciRoutingThroughPORTROUTE;
    BOOL                                PortPowerControlSupport;
    BOOL                                HighSpeedParkSupport;
    BOOL                                SmallFrameSizeSupport;
    UINT8                               EhciPortCount;
    UINT8                               OhciPortMultiplier; // * this for each OHCI companion
    UINT8                               OhciCompanionCount;
    UINT8                               DebugPort;        
    UINT8                               EecpPciCapPointer;
    UINT8                               Ist;
*/
}EHCI_DEVICE_OBJECT, * PEHCI_DEVICE_OBJECT;

void EhciGetHostCapabilities(PEHCI_DEVICE_OBJECT EhciObject);

#endif

/*















LOUSTATUS EhciResetController(PEHCI_DEVICE EhciDevice);
UINTPTR EhciGetDmaAddress(PVOID VAddress);
void EhciFreeDma(PEHCI_DEVICE EhciDevice, PVOID VAddress);
LOUSTATUS EhciAllocateDma(PEHCI_DEVICE EhciDevice, SIZE size, SIZE Alignment, PVOID* Out);
LOUSTATUS EhciAllocatePeriodicFrameListBase(PEHCI_DEVICE EhciDevice);
LOUSTATUS EhciAllocateAsyncHead(PEHCI_DEVICE EhciDevice);



*/