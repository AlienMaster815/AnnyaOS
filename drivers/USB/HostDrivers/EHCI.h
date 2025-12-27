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
#define EHCI_HCSPARAMS_DEBUG_PORT_NUMBER_SHIFT                  24
#define EHCI_HCSPARAMS_P_INDICATOR_MASK                         1
#define EHCI_HCSPARAMS_P_INDICATOR_SHIFT                        16
#define EHCI_HCSPARAMS_N_CC_MASK                                0x0F     
#define EHCI_HCSPARAMS_N_CC_SHIFT                               12
#define EHCI_HCSPARAMS_N_PCC_MASK                               0x0F
#define EHCI_HCSPARAMS_N_PCC_SHIFT                              8
#define EHCI_HCSPARAMS_PRR_MASK                                 1
#define EHCI_HCSPARAMS_PRR_SHIFT                                7
#define EHCI_HCSPARAMS_PPC_MASK                                 1
#define EHCI_HCSPARAMS_PPC_SHIFT                                7
#define EHCI_HCSPARAMS_N_PORTS_MASK                             0x0F
#define EHCI_HCSPARAMS_N_PORTS_SHIFT                            0

#define EHCI_HCSPARAMS_DEBUG_PORT_NUMBER                        (EHCI_HCSPARAMS_DEBUG_PORT_NUMBER_MASK << EHCI_HCSPARAMS_DEBUG_PORT_NUMBER_SHIFT)
#define EHCI_HCSPARAMS_P_INDICATOR                              (EHCI_HCSPARAMS_P_INDICATOR_MASK << EHCI_HCSPARAMS_P_INDICATOR_SHIFT)
#define EHCI_HCSPARAMS_N_CC                                     (EHCI_HCSPARAMS_N_CC_MASK << EHCI_HCSPARAMS_N_CC_SHIFT)
#define EHCI_HCSPARAMS_N_PCC                                    (EHCI_HCSPARAMS_N_PCC_MASK << EHCI_HCSPARAMS_N_PCC_SHIFT)
#define EHCI_HCSPARAMS_PRR                                      (EHCI_HCSPARAMS_PRR_MASK << EHCI_HCSPARAMS_PRR_SHIFT)
#define EHCI_HCSPARAMS_PPC                                      (EHCI_HCSPARAMS_PPC_MASK << EHCI_HCSPARAMS_PPC_SHIFT)
#define EHCI_HCSPARAMS_N_PORTS                                  (EHCI_HCSPARAMS_N_PORTS_MASK << EHCI_HCSPARAMS_N_PORTS_SHIFT)

#define EHCI_GET_DEBUG_PORT_NUMBER(HcsParams)                   ((HcsParams & EHCI_HCSPARAMS_DEBUG_PORT_NUMBER) >> EHCI_HCSPARAMS_DEBUG_PORT_NUMBER_SHIFT)
#define EHCI_SUPPORTS_P_INDICATOR(HcsParams)                    (HcsParams & EHCI_HCSPARAMS_P_INDICATOR)
#define EHCI_GET_N_CC(HcsParams)                                ((HcsParams & EHCI_HCSPARAMS_N_CC) >> EHCI_HCSPARAMS_N_CC_SHIFT)
#define EHCI_GET_N_PCC(HcsParams)                               ((HcsParams & EHCI_HCSPARAMS_N_PCC) >> EHCI_HCSPARAMS_N_PCC_SHIFT)
#define EHCI_PORT_ROUTING_BY_HCSPP_PORTROUTE(HcsParmas)         (HcsParmas & EHCI_HCSPARAMS_PRR)
#define EHCI_SUPPORTS_PPC(HcsParams)                            (HcsParams & EHCI_HCSPARAMS_PPC)
#define EHCI_GET_N_PORTS(HcsParams)                             ((HcsParams & EHCI_HCSPARAMS_N_PORTS) >> EHCI_HCSPARAMS_N_PORTS_SHIFT)

//Hcc Parameters Cap Reegister
#define EHCI_HCCPARAMS_EECP_MASK                                0xFF
#define EHCI_HCCPARAMS_EECP_SHIFT                               8
#define EHCI_HCCPARAMS_IST_MASK                                 0x0F
#define EHCI_HCCPARAMS_IST_SHIFT                                4
#define EHCI_HCCPARAMS_ASPC_MASK                                1
#define EHCI_HCCPARAMS_ASPC_SHIFT                               2
#define EHCI_HCCPARAMS_PFLF_MASK                                1
#define EHCI_HCCPARAMS_PFLF_SHIFT                               1
#define EHCI_HCCPARAMS_64AC_MASK                                1
#define EHCI_HCCPARAMS_64AC_SHIFT                               0                                    

#define EHCI_HCCPARAMS_EECP                                     (EHCI_HCCPARAMS_EECP_MASK << EHCI_HCCPARAMS_EECP_SHIFT)
#define EHCI_HCCPARAMS_IST                                      (EHCI_HCCPARAMS_IST_MASK << EHCI_HCCPARAMS_IST_SHIFT)
#define EHCI_HCCPARAMS_ASPC                                     (EHCI_HCCPARAMS_ASPC_MASK << EHCI_HCCPARAMS_ASPC_SHIFT)
#define EHCI_HCCPARAMS_PFLF                                     (EHCI_HCCPARAMS_PFLF_MASK << EHCI_HCCPARAMS_PFLF_SHIFT)
#define EHCI_HCCPARAMS_64AC                                     (EHCI_HCCPARAMS_64AC_MASK << EHCI_HCCPARAMS_64AC_SHIFT)

#define EHCI_GET_EECP(HccParams)                                ((HccParams & EHCI_HCCPARAMS_EECP) >> EHCI_HCCPARAMS_EECP_SHIFT)
#define EHCI_GET_IST(HccParams)                                 ((HccParams & EHCI_HCCPARAMS_IST) >> EHCI_HCCPARAMS_IST_SHIFT)
#define EHCI_SUPPORTS_HIGH_SPEED_PARK(HccParams)                (HccParams & EHCI_HCCPARAMS_ASPC)
#define EHCI_SUPPORTS_SMALL_FRAME_LISTS(HccParams)              (HccParams & EHCI_HCCPARAMS_PFLF)
#define EHCI_SUPPORTS_64BIT_DATA_STRUCTURES(HccParams)          (HccParams & EHCI_HCCPARAMS_64AC)

#define EHCI_CAP_TO_BOOLEAN(Cap)    (Cap ? true : false)

//TODO: HCSP-PORTROUTE

typedef struct PACKED _EHCI_HOST_OPERATIONAL_REGISTERS{ 
    UINT32      UsbCommand;             //USBCMD
    UINT32      UsbStatus;              //USBSTS
    UINT32      UsbInterruptEnable;     //USBINTR
    UINT32      UsbFrameIndex;          //FRINDEX
    UINT32      ControlDsSegment;       //CTRLDSSEGMENT
    UINT32      FrameListBaseAddress;   //PERIODICLISTBASE
    UINT32      NextAsyncListAddress;   //ASYNCLISTADDR
    UINT8       Reserved[0x3F - 0x1C];
    UINT32      ConfigFlag;             //CONFIGFLAG
    UINT32      PortStatusControl[];    //PORTSC      
}EHCI_HOST_OPERATIONAL_REGISTERS, * PEHCI_HOST_OPERATIONAL_REGISTERS;

#define EHCI_USBCMD_ITC_MASK                    0xFF
#define EHCI_USBCMD_ITC_SHIFT                   16
#define EHCI_USBCMD_ASPME_MASK                  1
#define EHCI_USBCMD_ASPME_SHIFT                 11
#define EHCI_USBCMD_ASPMC_MASK                  3
#define EHCI_USBCMD_ASPMC_SHIFT                 8
#define EHCI_USBCMD_LHCR_MASK                   1
#define EHCI_USBCMD_LHCR_SHIFT                  7
#define EHCI_USBCMD_IAAD_MASK                   1
#define EHCI_USBCMD_IAAD_SHIFT                  6
#define EHCI_USBCMD_ASE_MASK                    1
#define EHCI_USBCMD_ASE_SHIFT                   5
#define EHCI_USBCMD_PSE_MASK                    1
#define EHCI_USBCMD_PSE_SHIFT                   4
#define EHCI_USBCMD_FLS_MASK                    3
#define EHCI_USBCMD_FLS_SHIFT                   2
#define EHCI_USBCMD_HCRESET_MASK                1
#define EHCI_USBCMD_HCRESET_SHIFT               1
#define EHCI_USBCMD_RS_MASK                     1
#define EHCI_USBCMD_RS_SHIFT                    0                          


#define EHCI_USBCMD_ITC                         (EHCI_USBCMD_ITC_MASK << EHCI_USBCMD_ITC_SHIFT)
#define EHCI_USBCMD_ASPME                       (EHCI_USBCMD_ASPME_MASK << EHCI_USBCMD_ASPME_SHIFT)
#define EHCI_USBCMD_ASPMC                       (EHCI_USBCMD_ASPME_MASK << EHCI_USBCMD_ASPMC_SHIFT)
#define EHCI_USBCMD_LHCR                        (EHCI_USBCMD_LHCR_MASK << EHCI_USBCMD_LHCR_SHIFT)
#define EHCI_USBCMD_IAAD                        (EHCI_USBCMD_IAAD_MASK << EHCI_USBCMD_IAAD_SHIFT)
#define EHCI_USBCMD_ASE                         (EHCI_USBCMD_ASE_MASK << EHCI_USBCMD_ASE_SHIFT)
#define EHCI_USBCMD_PSE                         (EHCI_USBCMD_PSE_MASK << EHCI_USBCMD_PSE_SHIFT)
#define EHCI_USBCMD_FLS                         (EHCI_USBCMD_FLS_MASK << EHCI_USBCMD_FLS_SHIFT)
#define EHCI_USBCMD_HCRESET                     (EHCI_USBCMD_HCRESET_MASK << EHCI_USBCMD_HCRESET_SHIFT)
#define EHCI_USBCMD_RS                          (EHCI_USBCMD_RS_MASK << EHCI_USBCMD_RS_SHIFT)


#define EHCI_GET_USBCMO_ITC(UsbCmd)             ((UsbCmd & EHCI_USBCMD_ITC) >> EHCI_USBCMD_ITC_SHIFT)
#define EHCI_GET_USBCMD_ASPME(UsbCmd)           (UsbCmd & EHCI_USBCMD_ASPME)
#define EHCI_GET_USBCMD_ASPMC(UsbCmd)           ((UsbCmd & EHCI_USBCMD_ASPMC) >> EHCI_USBCMD_ASPMC_SHIFT)
#define EHCI_GET_USBCMD_LHCR(UsbCmd)            (UsbCmd & EHCI_USBCMD_LHCR)
#define EHCI_GET_USBCMD_IAAD(UsbCmd)            (UsbCmd & EHCI_USBCMD_IAAD)
#define EHCI_GET_USBCMD_ASE(UsbCmd)             (UsbCmd & EHCI_USBCMD_ASE)
#define EHCI_GET_USBCMD_PSE(UsbCmd)             (UsbCmd & EHCI_USBCMD_PSE)
#define EHCI_GET_USBCMD_FLS(UsbCmd)             ((UsbCmd & EHCI_USBCMD_FLS) >> EHCI_USBCMD_FLS_SHIFT)
#define EHCI_GET_USBCMD_HCRESET(UsbCmd)         (UsbCmd & EHCI_USBCMD_HCRESET)
#define EHCI_GET_USBCMD_RS(UsbCmd)              (UsbCmd & EHCI_USBCMD_RS)

static inline UINT32 EHCI_SET_USBCMD_ITC(UINT32 UsbCmd, UINT8 Itc){
    UsbCmd &= ~(EHCI_USBCMD_ITC);
    UsbCmd |= ((UINT32)Itc << EHCI_USBCMD_ITC_SHIFT);
    return UsbCmd;
}

static inline UINT32 EHCI_SET_USBCMD_ASPME(UINT32 UsbCmd, BOOL Aspme){
    UsbCmd &= ~(EHCI_USBCMD_ASPME);
    Aspme ? UsbCmd |= (EHCI_USBCMD_ASPME) : UsbCmd |= 0;
    return UsbCmd;
}

static inline UINT32 EHCI_SET_USBCMD_ASPMC(UINT32 UsbCmd, UINT8 Aspmc){
    UsbCmd &= ~(EHCI_USBCMD_ASPMC);
    UsbCmd |= ((Aspmc & EHCI_USBCMD_ASPMC_MASK) << EHCI_USBCMD_ASPMC_SHIFT);
    return UsbCmd;
}

static inline UINT32 EHCI_SET_USBCMD_LHCR(UINT32 UsbCmd, BOOL Lhcr){
    UsbCmd &= ~(EHCI_USBCMD_LHCR);
    Lhcr ? UsbCmd |= EHCI_USBCMD_LHCR : UsbCmd |= 0;
    return UsbCmd;
}

static inline UINT32 EHCI_SET_USBCMD_IAAD(UINT32 UsbCmd, BOOL Iaad){
    UsbCmd &= ~(EHCI_USBCMD_IAAD);
    Iaad ? UsbCmd |= EHCI_USBCMD_IAAD: UsbCmd |= 0;
    return UsbCmd;
}

static inline UINT32 EHCI_SET_USBCMD_ASE(UINT32 UsbCmd, BOOL Ase){
    UsbCmd &= ~(EHCI_USBCMD_ASE);
    Ase ? UsbCmd |= EHCI_USBCMD_ASE : UsbCmd |= 0;
    return UsbCmd;
}

static inline UINT32 EHCI_SET_USBCMD_PSE(UINT32 UsbCmd, BOOL Pse){
    UsbCmd &= ~(EHCI_USBCMD_PSE);
    Pse ? UsbCmd |= EHCI_USBCMD_PSE : UsbCmd |= 0; 
    return UsbCmd;
}

static inline UINT32 EHCI_SET_USBCMD_FLS(UINT32 UsbCmd, UINT8 Fls){
    UsbCmd &= ~(EHCI_USBCMD_FLS);
    UsbCmd |= ((UINT32)(Fls & EHCI_USBCMD_FLS_MASK) << EHCI_USBCMD_FLS_SHIFT);
    return UsbCmd;
}

static inline UINT32 EHCI_SET_USBCMD_HCRESET(UINT32 UsbCmd, BOOL Hcreset){
    UsbCmd &= ~(EHCI_USBCMD_HCRESET);
    Hcreset ? UsbCmd |= EHCI_USBCMD_HCRESET : UsbCmd |= 0;
    return UsbCmd;
}

static inline UINT32 EHCI_SET_USBCMD_RS(UINT32 UsbCmd, BOOL Rs){
    UsbCmd &= ~(EHCI_USBCMD_RS);
    Rs ? UsbCmd |= EHCI_USBCMD_RS : UsbCmd |= 0;
    return UsbCmd;
}


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

#define EHCI_GET_USBSTS_ASS(UsbSts)             (UsbSts & EHCI_USBSTS_ASS)   
#define EHCI_GET_USBSTS_PSS(UsbSts)             (UsbSts & EHCI_USBSTS_PSS)   
#define EHCI_GET_USBSTS_RECLAMATION(UsbSts)     (UsbSts & EHCI_USBSTS_RECLAMATION)   
#define EHCI_GET_USBSTS_HC_HALTED(UsbSts)       (UsbSts & EHCI_USBSTS_HC_HALTED)   
//the rest are writable
#define EHCI_GET_USBSTS_IAA(UsbSts)             (UsbSts & EHCI_USBSTS_IAA)
#define EHCI_GET_USBSTS_HSE(UsbSts)             (UsbSts & EHCI_USBSTS_HSE)
#define EHCI_GET_USBSTS_FLR(UsbSts)             (UsbSts & EHCI_USBSTS_FLR)
#define EHCI_GET_USBSTS_PCD(UsbSts)             (UsbSts & EHCI_USBSTS_PCD)
#define EHCI_GET_USBSTS_USBERRINT(UsbSts)       (UsbSts & EHCI_USBSTS_USBERRINT)
#define EHCI_GET_USBSTS_USBINT(UsbSts)          (UsbSts & EHCI_USBSTS_USBINT)



static inline UINT32 EHCI_USBSTS_SET_IAA(UINT32 UsbSts, BOOL Iaa){
    UsbSts &= ~(EHCI_USBSTS_IAA);
    Iaa ? UsbSts |= EHCI_USBSTS_IAA : UsbSts |= 0;
    return UsbSts;
}

static inline UINT32 EHCI_USBSTS_SET_HSE(UINT32 UsbSts, BOOL Hse){
    UsbSts &= ~(EHCI_USBSTS_HSE);
    Hse ? UsbSts |= EHCI_USBSTS_HSE : UsbSts |= 0;
    return UsbSts;
}

static inline UINT32 EHCI_USBSTS_SET_FLR(UINT32 UsbSts, BOOL Flr){
    UsbSts &= ~(EHCI_USBSTS_FLR);
    Flr ? UsbSts |= EHCI_USBSTS_FLR : UsbSts |= 0;
    return UsbSts;
}

static inline UINT32 EHCI_USBSTS_SET_PCD(UINT32 UsbSts, BOOL Pcd){
    UsbSts &= ~(EHCI_USBSTS_PCD);
    Pcd ? UsbSts |= EHCI_USBSTS_PCD : UsbSts |= 0;
    return UsbSts;
}

static inline UINT32 EHCI_USBSTS_SET_USBERRINT(UINT32 UsbSts, BOOL v){
    UsbSts &= ~(EHCI_USBSTS_USBERRINT);
    v ? UsbSts |= EHCI_USBSTS_USBERRINT : UsbSts |= 0;
    return UsbSts;
}

static inline UINT32 EHCI_USBSTS_SET_USBINT(UINT32 UsbSts, BOOL v){
    UsbSts &= ~(EHCI_USBSTS_USBINT);
    v ? UsbSts |= EHCI_USBSTS_USBINT : UsbSts |= 0;
    return UsbSts;
}

typedef struct _EHCI_DEVICE{
    PPCI_DEVICE_OBJECT                  PDEV;
    PEHCI_CAPABILITY_REGISTERS          Capabilities;
    PEHCI_HOST_OPERATIONAL_REGISTERS    OperationalRegisters;
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
}EHCI_DEVICE, * PEHCI_DEVICE;

void EhciGetHostCapabilities(PEHCI_DEVICE EhciDevice);
LOUSTATUS EhciStopHostController(PEHCI_DEVICE EhciDevice);

#endif