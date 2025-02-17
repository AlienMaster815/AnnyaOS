
#include <LouDDK.h>
/*
 * This software is provided under the GNU General Public License (GPL) v2.
 * Copyright (C) 2025 Tyler Grenier.
 *
 * The following kernel module is based on a combination of publicly available 
 * specifications, OS development resources, and various vendor documentation, 
 * including but not limited to:
 * - AHCI Specification
 * - OSDev.org materials
 * - Linux kernel documentation
 * - BSD kernel documentation
 * - Microsoft, NVIDIA, and Advanced Micro Devices (AMD) documentation
 *
 * DISCLAIMER:
 * Due to the nature of proprietary information and potential leaks, the sources 
 * of certain information will not be disclosed **nor shall they be provided.** 
 * Any possibly leaked information, if present, is used **strictly for compatibility 
 * purposes and not with any malicious intent.** If you require additional information 
 * regarding this driver, please obtain it from the **respective hardware or documentation owner.**
 *
 * This software is provided "as is," without any warranty of any kind, express or 
 * implied, including but not limited to the implied warranties of merchantability, 
 * fitness for a particular purpose, and non-infringement. In no event shall the author
 * be liable for any direct, indirect, incidental, special, exemplary, or consequential 
 * damages arising from the use of this software.
 *
 * MODULE FILES:
 * - AhciMod.h
 * - Ahci.cpp
 * - Ahci-Vt8251.cpp
 * - AhciLib.cpp
 * - Ahci-P5wdh.cpp
 * - Ahci-Avn.cpp
 * - AhciPowerManagement.cpp
 * - AhciPhyLayer.cpp
 *
 * LICENSE:
 * This module is licensed under the GNU General Public License v2 (GPLv2).
 * You may obtain a copy of the GPLv2 at:
 * https://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 */
#define SATA_SIGNATURE_ATA      0x101
#define SATA_SIGNATURE_ATAPI    0xEB140101
#define SATA_SIGNATURE_SEMB     0xC33C0101
#define SATA_SIGNATURE_PM       0x96690101

#define HBA_PORT_IPM_ACTIVE     1
#define HBA_PORT_DET_PRESENT    3

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

//End of Device list from Linux Kernel Documetation

#define AHCI_STANDARD_ABAR                  5
#define AHCI_STA2X11_ABAR                   0
#define AHCI_ENMOTUS_ABAR                   2
#define AHCI_CAVIUM_ABAR                    0
#define AHCI_GENERATION_5_CAVIUM_ABAR       4
#define AHCI_LOONGSON_ABAR                  0

#pragma pack(push, 1)
typedef struct _AHCI_DRIVER_PRIVATE_DATA{
    PAHCI_GENERIC_HOST_CONTROL  GenericHostController;
    PAHCI_GENERIC_PORT          GenericPort;
    P_PCI_DEVICE_OBJECT         PDEV;
    uint64_t                    AhciFlags;
    uint64_t                    AtaFlags;
    uint64_t                    PioFlags;
    uint64_t                    DmaFlags;
    uint64_t                    PrivateFlags;
    uint8_t                     InterruptRequestVector;
    uint8_t                     DmaBits;
    uint16_t                    PortMap;
    void                        (*StartCommandEngine)(PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort);
    LOUSTATUS                   (*StopCommandEngine)(PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort);\
    uintptr_t                   FisDma;
    uintptr_t                   CommandDma;
    bool                        PortNeedsSanatized[32];
}AHCI_DRIVER_PRIVATE_DATA, * PAHCI_DRIVER_PRIVATE_DATA;
#pragma pack(pop)

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
