#define _KERNEL_MODULE_
#include <LouDDK.h>
// SPDX-License-Identifier: GPL-2.0-or-later
/*
 *  ahci.c - AHCI SATA support
 *
 *  Maintained by:  Tejun Heo <tj@kernel.org>
 *    		    Please ALWAYS copy linux-ide@vger.kernel.org
 *		    on emails.
 *
 *  Copyright 2004-2005 Red Hat, Inc.
 *
 * libata documentation is available via 'make {ps|pdf}docs',
 * as Documentation/driver-api/libata.rst
 *
 * AHCI hardware documentation:
 * http://www.intel.com/technology/serialata/pdf/rev1_0.pdf
 * http://www.intel.com/technology/serialata/pdf/rev1_1.pdf
 
    NOTICE:This is a derivative work for the Lousine Kernel 
 */

#define SATA_SIGNATURE_ATA      0x101
#define SATA_SIGNATURE_ATAPI    0xEB140101
#define SATA_SIGNATURE_SEMB     0xC33C0101
#define SATA_SIGNATURE_PM       0x96690101

#define HBA_PORT_IPM_ACTIVE     1
#define HBA_PORT_DET_PRESENT    3

#define AHCI_MAX_PORTS                  32
#define AHCI_MAX_SCATTER_GATHERS        168
#define AHCI_DMA_BOUNDRY                UINT32_MAX
#define AHCI_MAX_COMMANDS               32
#define AHCI_COMMAND_SIZE               32
#define AHCI_COMMAND_SLOT_SIZE          (AHCI_MAX_COMMANDS * AHCI_COMMAND_SIZE)
#define AHCI_RECIVE_FIS_SIZE            256
#define AHCI_COMMAND_TABLE_CDB          0x40
#define AHCI_COMMAND_TABLE_HEADER_SIZE  0x80
#define AHCI_COMMAND_TABLE_SIZE         (AHCI_COMMAND_TABLE_HEADER_SIZE + (AHCI_MAX_SCATTER_GATHERS * 16))
#define AHCI_COMMAND_TABLE_AR_SIZE      (AHCI_COMMAND_TABLE_SIZE * AHCI_MAX_COMMANDS)
#define AHCI_PORT_PRIVATE_DMA_SIZE      (AHCI_COMMAND_SLOT_SIZE + AHCI_COMMAND_TABLE_AR_SIZE + AHCI_RECIVE_FIS_SIZE)
#define AHCI_PORT_PRIVATE_FBS_DMA_SIZE  (AHCI_COMMAND_SLOT_SIZE + AHCI_COMMAND_TABLE_AR_SIZE + (AHCI_RECIVE_FIS_SIZE * 16))



#define AHCI_STANDARD_ABAR                  5
#define AHCI_STA2X11_ABAR                   0
#define AHCI_ENMOTUS_ABAR                   2
#define AHCI_CAVIUM_ABAR                    0
#define AHCI_GENERATION_5_CAVIUM_ABAR       4
#define AHCI_LOONGSON_ABAR                  0

typedef struct _AHCI_COMMAND_PRIVATE_DATA{
    UINT8                   CommandSlot;
    UINTPTR                 CommandHeader;
    UINTPTR                 CommandTable;
    LOUSINE_DMA_TRANSFER    PioDmaTransfer;
}AHCI_COMMAND_PRIVATE_DATA, * PAHCI_COMMAND_PRIVATE_DATA;

typedef struct _AHCI_DRIVER_PRIVATE_DATA{
    PAHCI_GENERIC_HOST_CONTROL              GenericHostController;
    PAHCI_GENERIC_PORT                      GenericPort;
    PPCI_DEVICE_OBJECT                      PDEV;
    UINT32                                  CapOveride;
    AHCI_DRIVER_BOARD_INFORMATION_TABLE     BoardInfo;
    uint64_t                                PrivateFlags;
    LOUSTATUS                               (*StartCommandEngine)(PATA_PORT_DEVICE_OBJECT AtaPort);
    LOUSTATUS                               (*StopCommandEngine)(PATA_PORT_DEVICE_OBJECT AtaPort);
    uintptr_t                               DmaData;
    uintptr_t                               DmaDataDma;
    uintptr_t                               Fis;
    uintptr_t                               FisDma;
    uintptr_t                               Command;
    uintptr_t                               CommandDma;
    uint32_t                                PortMap;
    uint8_t                                 InterruptRequestVector;
    LOUSINE_DMA_DEVICE                      DmaDevice;
    size_t                                  RemappedNvme;
    uint64_t                                EmLocation;
    uint64_t                                EmBufferSize;
    uint8_t                                 EmMessageType;
    uint32_t                                ExternalPortMask;
    BOOLEAN                                 AtapiDevice;
    BOOLEAN                                 DeviceAttached;
    UINT32                                  CommandSlot;
    KERNEL_EVENT_OBJECT                     CommandCompletion[32];
}AHCI_DRIVER_PRIVATE_DATA, * PAHCI_DRIVER_PRIVATE_DATA;



static inline unsigned int AhciRemapDcc(int i){
    return AHCI_REMAP_N_DCC + i * 0x80;
}

#define         AHCI_ENCODE_BUSDEVFUNC(Bus, Slot, Func) (PVOID)(((Bus & 0xFF) << 16) | ((Slot & 0xFF) << 8) | ((Func & 0xFF)))
static inline 
void   
AHCI_DECODE_BUSDEVFUNC(
    UINT8* Bus, 
    UINT8* Slot, 
    UINT8* Func,
    PVOID pEncoding
){
    UINT64 Encoding = (UINT64)pEncoding;
    if(Bus){
        *Bus = ((Encoding >> 16) & 0xFF);
    }
    if(Slot){
        *Slot = ((Encoding >> 8) & 0xFF);
    }
    if(Func){
        *Func = ((Encoding) & 0xFF);
    }
}


/*


//Driver Operations
LOUSTATUS AhciGenricDMAPrepCommand(
    PATA_QUEUED_COMMAND QueuedCommand
);
LOUSTATUS AhciGenricDMAIssueCommand(
    PATA_QUEUED_COMMAND QueuedCommand
);
LOUSTATUS AhciGenericHardReset(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort);
LOUSTATUS AhciVt8251HardReset(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort);
LOUSTATUS AhciP5wdhHardReset(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort);
LOUSTATUS AhciAvnHardReset(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort);
LOUSTATUS ResetAhcPciController(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost);
void AhciStartPort(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort);
void AhciStopPort(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort);
//Endof Driver Operations



//port States
#define PORT_STATE_UNDEFINED                0
#define PORT_STATE_RESET                    1
#define PORT_STATE_INIT                     2
#define PORT_STATE_NOT_RUNNING              3
#define PORT_STATE_POWER_ON                 4
#define PORT_STATE_POWER_OFF                5
#define PORT_STATE_OFFLINE                  6
#define PORT_STATE_START_COM                7
#define PORT_STATE_PHY_LISTENING            8
#define PORT_STATE_REG_FIS_POST_TO_MEM      9
#define PORT_STATE_LOW_POWER                10
#define PORT_STATE_DEVICE_SLEEP             11
#define PORT_STATE_IDLE                     12
#define PORT_STATE_NDR_ENTRY                13



void AhciSetEmMessages(
    PAHCI_DRIVER_PRIVATE_DATA HostPrivate
);

LOUSTATUS  
AhciResetEm(
    PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost
);
*/



//AHCI Device list information from linux kernel documentation

#define AHCI_BOARD_NORMAL_AHCI  0 //Ahci Device Conforms to specification
#define AHCI_BOARD_43_BIT_DMA   1 //43 bit dma only ahci device
#define AHCI_BOARD_IGN_IFFER    2 //IGN_IFFER is iffy;
#define AHCI_BOARD_NO_BOUNCE    3 //systems dont require bounce delay
#define AHCI_BOARD_NO_MSI       4 //device has broken MSI
#define AHCI_BOARD_INTEL_PCS    5 //pci quirk for old intel chips however cannot assume they are not still broken until verification withought quirk code
#define AHCI_BOARD_PCS_NO_SLEEP 6 //Device has broken sleep system
#define AHCI_BOARD_PCS_NO_SNTF  7 //HBA's SNTF System Is Broken
#define AHCI_BOARD_HAS_FBS      8 //HBA Supports Fiss based switching but doesent report it 

//the following are specifica chips that need special attention
#define AHCI_BOARD_AL_CHIP      9
#define AHCI_BOARD_AVN_CHIP     10
#define AHCI_BOARD_MCP65_CHIP   11
#define AHCI_BOARD_MCP77_CHIP   12
#define AHCI_BOARD_MCP89_CHIP   13
#define AHCI_BOARD_MV_CHIP      14
#define AHCI_BOARD_SB600_CHIP   15
#define AHCI_BOARD_SB700_CHIP   16
#define AHCI_BOARD_VT8251_CHIP  17
//the following are the systems that are familiy membors of the above mcp
#define AHCI_BOARD_LINUX_CHIP   AHCI_BOARD_MCP65_CHIP //this is a board designed with a linux firmware
#define AHCI_BOARD_MCP67_CHIP   AHCI_BOARD_MCP65_CHIP
#define AHCI_BOARD_MCP73_CHIP   AHCI_BOARD_MCP65_CHIP
#define AHCI_BOARD_MCP79_CHIP   AHCI_BOARD_MCP77_CHIP

#define AHCI_SYSTEM_MODULE_VERSION_MESSAGE "AHCI.SYS Module Version 1.01\n"

//End of Device list from Linux Kernel Documetation

typedef struct PACKED _FIS_H2D{
    UINT8   FisType;
#define FIS_H2D_PMP_PORT_BITS   0x0F
#define FIS_H2D_COMMAND_BIT     (1 << 7)
    UINT8   PmpC;
    UINT8   Command;
    UINT8   FeatureCurrent;
    UINT8   LbaLowCurrent;
    UINT8   LbaMidCurrent;
    UINT8   LbaHighCurrent;
    UINT8   Device;
    UINT8   LbaLowPrevious;
    UINT8   LbaMidPrevious;
    UINT8   LbaHighPrevious;
    UINT8   FeaturePrevious;
    UINT8   SectorCountCurrent;
    UINT8   SectorCountPrevious;
    UINT8   IsochCommandCompletion;
    UINT8   Control;
    UINT8   Reserved[4];
}FIS_H2D, * PFIS_H2D;

typedef struct PACKED _FIS_D2H{
    UINT8   FisType;
#define     FIS_D2H_PMP_PORT_BITS   0x0F
#define     FIS_D2H_INTERRUPT_BIT   (1 << 6)
    UINT8   PmpPortInterrupt;
    UINT8   Status;
    UINT8   Error;
    UINT8   LbaLowCurrent;
    UINT8   LbaMidCurrent;
    UINT8   LbaHighCurrent;
    UINT8   Device;
    UINT8   LbaLowPrevious;
    UINT8   LbaMidPrevious;
    UINT8   LbaHighPrevious;
    UINT8   Reserved1;
    UINT8   SectorCountCurrent;
    UINT8   SectorCountPrevious;
    UINT8   Resevred2[6];
}FIS_D2H, * PFIS_D2H;

typedef struct PACKED _FIS_PIO{
    UINT8   FisType;
#define     FIS_PIO_PMP_PORT_BITS   0x0F
#define     FIS_PIO_TRANSFER        (1 << 5)
#define     FIS_PIO_INTERRUPT_BIT   (1 << 6)
    UINT8   PmpPortTransferInterrupt;
    UINT8   Status;
    UINT8   Error;
    UINT8   LbaLowCurrent;
    UINT8   LbaMidCurrent;
    UINT8   LbaHighCurrent;
    UINT8   Device;
    UINT8   LbaLowPrevious;
    UINT8   LbaMidPrevious;
    UINT8   LbaHighPrevious;
    UINT8   Reserved1;
    UINT8   SectorCountCurrent;
    UINT8   SectorCountPrevious;
    UINT8   Resered2;
    UINT8   eStatus;
    UINT16  TransferCount;
    UINT8   Resered3[2];
}FIS_PIO, * PFIS_PIO;

typedef struct PACKED _COMMAND_HEADER{
    UINT8   CflAWP;
#define COMMAND_HEADER_FIS_LENGTH_BITS  0x1F
#define COMMAND_HEADER_ATAPI_BIT        (1 << 5)
#define COMMAND_HEADER_WRITE_BIT        (1 << 6)
#define COMMAND_HEADER_PREFETCH_BIT     (1 << 7)  
    UINT8   RBCPmp;
#define COMMAND_HEADER_RESET_BIT        (1 << 0)
#define COMMAND_HEADER_BIST_BIT         (1 << 1)
#define COMMAND_HEADER_CLR_ROK_BIT      (1 << 2)
#define COMMAND_HEADER_PMP_SHIFT        (4)
#define COMMAND_HEADER_PMP_BITS         0x0F
    UINT16  Prdtl;
    UINT32  Ctba;
    UINT32  Ctbau;
    UINT32  Reserved[5];
}COMMAND_HEADER, * PCOMMAND_HEADER;

typedef struct PACKED _COMMAND_TABLE_PRDT{
    UINT32  Dba;
    UINT32  Dbau;
    UINT32  Reserved;
    UINT32  DbcI;
#define COMMAND_TABLE_DBC_BITS ((1 << 22) - 1)
#define COMMAND_TABLE_INT_BIT   (1 << 31)
}COMMAND_TABLE_PRDT, * PCOMMAND_TABLE_PRDT;

typedef struct PACKED _COMMAND_TABLE{
    UINT8               CmdFis[64]; 
    UINT8               AtapiCommand[16];
    UINT8               Reserved[48];   
    COMMAND_TABLE_PRDT  Prdts[];
}COMMAND_TABLE, * PCOMMAND_TABLE;


static inline void DumpPort(PAHCI_GENERIC_PORT AhciPort){
    LouPrint("PxCLB   :%h\n", AhciPort->PxCLB);
    LouPrint("PxCLBU  :%h\n", AhciPort->PxCLBU);
    LouPrint("PxFB    :%h\n", AhciPort->PxFB);
    LouPrint("PxFBU   :%h\n", AhciPort->PxFBU);
    LouPrint("PxIS    :%h\n", AhciPort->PxIS);
    LouPrint("PxIE    :%h\n", AhciPort->PxIE);
    LouPrint("PxCMD   :%h\n", AhciPort->PxCMD);
    LouPrint("PxTFD   :%h\n", AhciPort->PxTFD);
    LouPrint("PxSIG   :%h\n", AhciPort->PxSIG);
    LouPrint("PxSSTS  :%h\n", AhciPort->PxSSTS);
    LouPrint("PxSCTL  :%h\n", AhciPort->PxSCTL);
    LouPrint("PxSERR  :%h\n", AhciPort->PxSERR);
    LouPrint("PxSACT  :%h\n", AhciPort->PxSACT);
    LouPrint("PxCI    :%h\n", AhciPort->PxCI);
    LouPrint("PxSNTF  :%h\n", AhciPort->PxSNTF);
    LouPrint("PxFBS   :%h\n", AhciPort->PxFBS);
    LouPrint("PxDEVSLP:%h\n", AhciPort->PxDEVSLP);
    LouPrint("PxVS    :%h\n", AhciPort->PxVS);
}

static inline void DumpGhc(PAHCI_GENERIC_HOST_CONTROL Ghc){
    LouPrint("CAP     :%h\n", Ghc->Capabilities);
    LouPrint("GHC     :%h\n", Ghc->GlobalHostControl);
    LouPrint("IS      :%h\n", Ghc->InterruptStatus);
    LouPrint("PI      :%h\n", Ghc->PortsImplemented);
    LouPrint("VS      :%h\n", Ghc->Version);
    LouPrint("CC_CTL  :%h\n", Ghc->CCC_Control);
    LouPrint("CC_PORTS:%h\n", Ghc->CccPorts);
    LouPrint("EM_LOC  :%h\n", Ghc->EmLocation);
    LouPrint("EM_CTL  :%h\n", Ghc->EmControl);
    LouPrint("CAP2    :%h\n", Ghc->Capabilities2);
    LouPrint("BIHC    :%h\n", Ghc->BiosHandoff);
}

static inline void DumpEverything(
    PATA_HOST_DEVICE_OBJECT AtaHost
){
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)AtaHost->HostPrivateData; 
    DumpGhc(PrivateData->GenericHostController);
    PATA_PORT_DEVICE_OBJECT TmpPort;
    SIZE i;
    ForEachAtaPort(AtaHost, TmpPort, i){
        PAHCI_DRIVER_PRIVATE_DATA PrivateAhciData2 = (PAHCI_DRIVER_PRIVATE_DATA)TmpPort->PortPrivateData;
        DumpPort(PrivateAhciData2->GenericPort);
    }    
}

static inline void DumpH2dFis(
    PFIS_H2D H2dFis
){
    LouPrint("H2dFis->FisType       :%bc\n", (UINT64)H2dFis->FisType);
    LouPrint("H2dFis->Pmpc          :%bc\n", (UINT64)H2dFis->PmpC);
    LouPrint("H2dFis->Command       :%h\n", (UINT64)H2dFis->Command);
    LouPrint("H2dFis->FeatureCurrent:%h\n", (UINT64)H2dFis->FeatureCurrent);
    LouPrint("H2dFis->LbaLowCurrent :%h\n", (UINT64)H2dFis->LbaLowCurrent);
    LouPrint("H2dFis->LbaMidCurrent :%h\n", (UINT64)H2dFis->LbaMidCurrent);
    LouPrint("H2dFis->LbaHighCurrent:%h\n", (UINT64)H2dFis->LbaHighCurrent);
    LouPrint("H2dFis->Device        :%h\n", (UINT64)H2dFis->Device);
    LouPrint("H2dFis->LbaLowPrev    :%h\n", (UINT64)H2dFis->LbaLowPrevious);
    LouPrint("H2dFis->LbaMidPrev    :%h\n", (UINT64)H2dFis->LbaMidPrevious);
    LouPrint("H2dFis->LbaHighPrev   :%h\n", (UINT64)H2dFis->LbaHighPrevious);
    LouPrint("H2dFis->FeaturePrev   :%h\n", (UINT64)H2dFis->FeaturePrevious);
    LouPrint("H2dFis->SCCurrent     :%h\n", (UINT64)H2dFis->SectorCountCurrent);
    LouPrint("H2dFis->SCPrev        :%h\n", (UINT64)H2dFis->SectorCountPrevious);
    LouPrint("H2dFis->ICC           :%h\n", (UINT64)H2dFis->IsochCommandCompletion);
    LouPrint("H2dFis->Control       :%h\n", (UINT64)H2dFis->Control);
}

static inline void DumpPrdt(PCOMMAND_TABLE_PRDT Prdt){
    LouPrint("Prdt->Dba     :%h\n", (UINT64)Prdt->Dba);
    LouPrint("Prdt->Dbau    :%h\n", (UINT64)Prdt->Dbau);
    LouPrint("Prdt->DbcI    :%h\n", (UINT64)Prdt->DbcI);
}

static inline void DumpCmdHeader(PCOMMAND_HEADER CmdHeader){
    LouPrint("CmdHeader->CflAWP :%h\n", (UINT64)CmdHeader->CflAWP);
    LouPrint("CmdHeader->RBCPmp :%h\n", (UINT64)CmdHeader->RBCPmp);
    LouPrint("CmdHeader->Prdtl  :%h\n", (UINT64)CmdHeader->Prdtl);
    LouPrint("CmdHeader->Ctba   :%h\n", (UINT64)CmdHeader->Ctba);
    LouPrint("CmdHeader->Ctbau  :%h\n", (UINT64)CmdHeader->Ctbau);
}