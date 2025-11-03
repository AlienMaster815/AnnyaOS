#ifndef _AHCI_H
#define _AHCI_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C"{
#else 
#include <LouAPI.h>
#endif

#include "SerialAta.h"

typedef struct _AHCI_GENERIC_HOST_CONTROL{
    volatile uint32_t Capabilities;
    volatile uint32_t GlobalHostControl;
    volatile uint32_t InterruptStatus;
    volatile uint32_t PortsImplemented;
    volatile uint32_t Version;
    volatile uint32_t CCC_Control;
    volatile uint32_t CccPorts;
    volatile uint32_t EmLocation;
    volatile uint32_t EmControl;
    volatile uint32_t Capabilities2;
    volatile uint32_t BiosHandoff;
}AHCI_GENERIC_HOST_CONTROL, * PAHCI_GENERIC_HOST_CONTROL;

#define AHCI_SUPPORTS_S64A(Capabilities)    ((Capabilities & (1 << 31)) ? 1 : 0)
#define AHCI_SUPPORTS_SNCQ(Capabilities)    ((Capabilities & (1 << 30)) ? 1 : 0)
#define AHCI_SUPPORTS_SSNTF(Capabilities)   ((Capabilities & (1 << 29)) ? 1 : 0)
#define AHCI_SUPPORTS_SMPS(Capabilities)    ((Capabilities & (1 << 28)) ? 1 : 0)
#define AHCI_SUPPORTS_SSS(Capabilities)     ((Capabilities & (1 << 27)) ? 1 : 0)
#define AHCI_SUPPORTS_SALP(Capabilities)    ((Capabilities & (1 << 26)) ? 1 : 0)
#define AHCI_SUPPORTS_SAL(Capabilities)     ((Capabilities & (1 << 25)) ? 1 : 0)
#define AHCI_SUPPORTS_SCLO(Capabilities)    ((Capabilities & (1 << 24)) ? 1 : 0)
#define AHCI_GET_ISS(Capabilities)          ((Capabilities >> 19) & 0xF)
#define AHCI_SUPPORTS_SAM(Capabilities)     ((Capabilities & (1 << 18)) ? 1 : 0)
#define AHCI_SUPPORTS_SPM(Capabilities)     ((Capabilities & (1 << 17)) ? 1 : 0)
#define AHCI_SUPPORTS_FBSS(Capabilities)    ((Capabilities & (1 << 16)) ? 1 : 0)
#define AHCI_SUPPORTS_PMP(Capabilities)     ((Capabilities & (1 << 15)) ? 1 : 0)
#define AHCI_SUPPORTS_SSC(Capabilities)     ((Capabilities & (1 << 14)) ? 1 : 0)
#define AHCI_SUPPORTS_PSC(Capabilities)     ((Capabilities & (1 << 13)) ? 1 : 0)
#define AHCI_GET_NCS(Capabilities)          ((Capabilities >> 8) & 0x1F)
#define AHCI_SUPPORTS_CCCS(Capabilities)    ((Capabilities & (1 << 7))  ? 1 : 0)
#define AHCI_SUPPORTS_EMS(Capabilities)     ((Capabilities & (1 << 6))  ? 1 : 0)
#define AHCI_SUPPORTS_SXS(Capabilities)     ((Capabilities & (1 << 4))  ? 1 : 0)
#define AHCI_GET_NP(Capabilities)           (Capabilities & 0x1F)

typedef struct _AHCI_PRIVATE_DATA_TEMPLATE_HEADER{
    uint8_t Supports64BitAddressing                 :   1;
    uint8_t SupportsNativeCommandQueueing           :   1;
    uint8_t SupportsSNotificationRegister           :   1;
    uint8_t SupportsMechanicalPresenceSwitch        :   1;
    uint8_t SupportsStaggeredSpinup                 :   1;
    uint8_t SupportsAggresiveLinkPowerManagement    :   1;
    uint8_t SupportsActivityLED                     :   1;
    uint8_t SupportsCommandListOveride              :   1;
    uint8_t MaximumInterfaceSpeedSupport            :   4;
    uint8_t IsAnAhciOnlyDevice                      :   1;
    uint8_t SupportsPortMultiplier                  :   1;
    uint8_t SupportsFisBasedSwitching               :   1;
    uint8_t SupportsMultiplePioDRQBlock             :   1;
    uint8_t SupportsSlumberState                    :   1;
    uint8_t SupportsPartialState                    :   1;
    uint8_t NumberOfCommandSlots                    :   5;
    uint8_t SupportsCommandCoalesing                :   1;
    uint8_t SupportsEnclosureManagement             :   1;
    uint8_t SupportsExternalSata                    :   1;
    uint8_t ImplementedPorts                        :   5;
}AHCI_PRIVATE_DATA_TEMPLATE_HEADER, * PAHCI_PRIVATE_DATA_TEMPLATE_HEADER;

typedef struct _AHCI_GENERIC_PORT{
    volatile uint32_t PxCLB;
    volatile uint32_t PxCLBU;
    volatile uint32_t PxFB;
    volatile uint32_t PxFBU;
    volatile uint32_t PxIS;
    volatile uint32_t PxIE;
    volatile uint32_t PxCMD;
    volatile uint32_t Reserved0;
    volatile uint32_t PxTFD;
    volatile uint32_t PxSIG;
    volatile uint32_t PxSSTS;
    volatile uint32_t PxSCTL;
    volatile uint32_t PxSERR;
    volatile uint32_t PxSACT;
    volatile uint32_t PxCI;
    volatile uint32_t PxSNTF;
    volatile uint32_t PxFBS;
    volatile uint32_t PxDEVSLP;
    volatile uint32_t Reserved1;
    volatile uint32_t PxVS;
}AHCI_GENERIC_PORT, * PAHCI_GENERIC_PORT;

#define GET_PxCLB_ADDRESS(PxCLB)    ((PxCLB) & ~(0b111111111))
#define GET_PxFB_ADDRESS(PxFB)      ((PxFB) & ~(0b1111111))
#define IS_INTERRUPT_CPDS(PxIS)     ((PxIS) & (1 << 31))
#define IS_INTERRUPT_TFES(PxIS)     ((PxIS) & (1 << 30))
#define IS_INTERRUPT_HBFS(PxIS)     ((PxIS) & (1 << 29))
#define IS_INTERRUPT_HBDS(PxIS)     ((PxIS) & (1 << 28))
#define IS_INTERRUPT_IFS(PxIS)      ((PxIS) & (1 << 27))
#define IS_INTERRUPT_INFS(PxIS)     ((PxIS) & (1 << 26))
#define IS_INTERRUPT_OFS(PxIS)      ((PxIS) & (1 << 24))
#define IS_INTERRUPT_IPMS(PxIS)     ((PxIS) & (1 << 23))
#define IS_INTERRUPT_PRCS(PxIS)     ((PxIS) & (1 << 22))
#define IS_INTERRUPT_DMPS(PxIS)     ((PxIS) & (1 << 7))
#define IS_INTERRUPT_PCS(PxIS)      ((PxIS) & (1 << 6))
#define IS_INTERRUPT_DPS(PxIS)      ((PxIS) & (1 << 5))
#define IS_INTERRUPT_UFS(PxIS)      ((PxIS) & (1 << 4))
#define IS_INTERRUPT_SDBS(PxIS)     ((PxIS) & (1 << 3))
#define IS_INTERRUPT_DSS(PxIS)      ((PxIS) & (1 << 2))
#define IS_INTERRUPT_PSS(PxIS)      ((PxIS) & (1 << 1))
#define IS_INTERRUPT_DHRS(PxIS)     ((PxIS) & 1)

//ST, CR, FRE, FR
#define AHCI_PxCMD_CR   (1 << 15)
#define AHCI_PxCMD_FR   (1 << 14)
#define AHCI_PxCMD_FRE  (1 << 4)
#define AHCI_PxCMD_ST   1




#define AHCI_FLAG_COMMON                1
#define AHCI_FLAG_43BIT_DMA_ONLY        1 << 1
#define AHCI_FLAG_IGN_IFFER             1 << 2
#define AHCI_FLAG_NO_DEBOUNCE           1 << 3
#define AHCI_FLAG_NO_MSI                1 << 4
#define AHCI_FLAG_INTEL_PCS             1 << 5
#define AHCI_FLAG_BROKEN_SLEEP          1 << 6
#define AHCI_FLAG_BROKEN_SNTF           1 << 7
#define AHCI_FLAG_HAS_FBS               1 << 8
#define AHCI_FLAG_HAS_NO_PMP            1 << 9
#define AHCI_FLAG_NO_FPDMA_AA           1 << 10
#define AHCI_FLAG_HAS_NCQ               1 << 11
#define AHCI_FLAG_NO_NCQ                1 << 12
#define AHCI_FLAG_MV_PATA               1 << 13
#define AHCI_FLAG_IGN_INTERNAL_SERR     1 << 14
#define AHCI_FLAG_32BIT_ONLY            1 << 15
#define AHCI_FLAG_SECTOR255             1 << 16
#define AHCI_FLAG_NO_POWEROFF_SPINDOWN  1 << 17

typedef struct _AHCI_DRIVER_BOARD_INFORMATION_TABLE{
    uint32_t                        AhciFlags;
    uint32_t                        AtaFlags;
    uint32_t                        PioFlags;
    uint32_t                        DmaFlags;
    PLOUSINE_ATA_PORT_OPERATIONS    DevicesPortOperations;
    uint64_t                        Padding[4];
}AHCI_DRIVER_BOARD_INFORMATION_TABLE, * PAHCI_DRIVER_BOARD_INFORMATION_TABLE,
 AHCI_DRIVER_BOARD_INFORMATION ,* PAHCI_DRIVER_BOARD_INFORMATION;



#define ICH_PCI_MAP_REGISTER 0x90
#define PCS6_PCI_REGISTER    0x92

#define AHCI_COMMAND_TABLE_HEADER_SIZE 0x80

#define AHCI_COMMAND_TABLE_CDB_OFFSET 0x40

#define AHCI_COMMAND_WRITE 1 << 5
#define AHCI_COMMAND_ATAPI 1 << 9


#ifdef __cplusplus
}
#endif
#endif //_AHCI_H