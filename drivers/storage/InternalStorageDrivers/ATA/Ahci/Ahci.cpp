#include <LouDDK.h>
#include <Hal.h>

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
 * - BSD Kernel documentation 
 * - Microsoft, NVIDIA, and Advanced Micro Devices (AMD) documentation
 *
 * DISCLAIMER:
 * Due to the nature of proprietary information and potential leaks, the sources 
 * of certain information will not be disclosed **nor shall it be given.** 
 * Any possibly leaked information, if present, is used **strictly for compatibility 
 * purposes and not with any malicious intent.**
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
 *
 * LICENSE:
 * This module is licensed under the GNU General Public License v2 (GPLv2).
 * You may obtain a copy of the GPLv2 at:
 * https://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 */

#include "AhciMod.h"

//ATA Module Structured Operations
UNUSED static LOUSINE_ATA_PORT_OPERATIONS AhciGenericOperations{
    .PrepCommand = AhciGenricDMAPrepCommand,
    .IssueCommand = AhciGenricDMAIssueCommand,
    .HardReset = AhciGenericHardReset,
};

UNUSED static LOUSINE_ATA_PORT_OPERATIONS AhciVt8251Operations{
    .PrepCommand = AhciGenricDMAPrepCommand,
    .IssueCommand = AhciGenricDMAIssueCommand,
    .HardReset = AhciVt8251HardReset,
};

UNUSED static LOUSINE_ATA_PORT_OPERATIONS AhciP5wdhOperations{
    .PrepCommand = AhciGenricDMAPrepCommand,
    .IssueCommand = AhciGenricDMAIssueCommand,
    .HardReset = AhciP5wdhHardReset,
};

UNUSED static LOUSINE_ATA_PORT_OPERATIONS AhciAvnOperations{
    .PrepCommand = AhciGenricDMAIssueCommand,
    .IssueCommand = AhciGenricDMAIssueCommand,
    .HardReset = AhciAvnHardReset,
};


UNUSED static LOUSINE_ATA_PORT_OPERATIONS AhciPmpRetySrStOperations{
    .PrepCommand = AhciGenricDMAIssueCommand,
    .IssueCommand = AhciGenricDMAIssueCommand,
    .HardReset = AhciGenericHardReset,
};
//endof ATA Module Structured Operations

typedef struct _AHCI_DRIVER_BOARD_INFORMATION_TABLE{
    uint32_t                        AhciFlags;
    uint32_t                        AtaFlags;
    uint32_t                        PioFlags;
    uint32_t                        DmaFlags;
    PLOUSINE_ATA_PORT_OPERATIONS    DevicesPortOperations;
}AHCI_DRIVER_BOARD_INFORMATION_TABLE, * PAHCI_DRIVER_BOARD_INFORMATION_TABLE;

UNUSED static AHCI_DRIVER_BOARD_INFORMATION_TABLE AhciBoardInfomationTable[] = {
    [AHCI_BOARD_NORMAL_AHCI] = {
        .AhciFlags              = AHCI_FLAG_COMMON,
        .PioFlags               = UNIVERSAL_ATA_PIO4,
        .DmaFlags               = UNIVERSAL_ATA_UDMA6,
        .DevicesPortOperations  = &AhciGenericOperations,
    },
    [AHCI_BOARD_43_BIT_DMA] = {
        .AhciFlags              = AHCI_FLAG_COMMON | AHCI_BOARD_43_BIT_DMA,
        .PioFlags               = UNIVERSAL_ATA_PIO4,
        .DmaFlags               = UNIVERSAL_ATA_UDMA6,
        .DevicesPortOperations  = &AhciGenericOperations,
    },
    [AHCI_BOARD_IGN_IFFER] = {
        .AhciFlags              = AHCI_FLAG_COMMON | AHCI_FLAG_IGN_IFFER,
        .PioFlags               = UNIVERSAL_ATA_PIO4,
        .DmaFlags               = UNIVERSAL_ATA_UDMA6,
        .DevicesPortOperations  = &AhciGenericOperations,
    },
    [AHCI_BOARD_NO_BOUNCE] = {
        .AhciFlags              = AHCI_FLAG_COMMON | AHCI_FLAG_NO_DEBOUNCE,
        .PioFlags               = UNIVERSAL_ATA_PIO4,
        .DmaFlags               = UNIVERSAL_ATA_UDMA6,
        .DevicesPortOperations  = &AhciGenericOperations,
    },
    [AHCI_BOARD_NO_MSI] = {
        .AhciFlags              = AHCI_FLAG_COMMON | AHCI_FLAG_NO_MSI,
        .PioFlags               = UNIVERSAL_ATA_PIO4,
        .DmaFlags               = UNIVERSAL_ATA_UDMA6,
        .DevicesPortOperations  = &AhciGenericOperations,
    },
    [AHCI_BOARD_INTEL_PCS]      = {
        .AhciFlags              = AHCI_FLAG_COMMON | AHCI_FLAG_INTEL_PCS,
        .PioFlags               = UNIVERSAL_ATA_PIO4,
        .DmaFlags               = UNIVERSAL_ATA_UDMA6,
        .DevicesPortOperations  = &AhciGenericOperations,
    },
    [AHCI_BOARD_PCS_NO_SLEEP]   = {
        .AhciFlags              = AHCI_FLAG_COMMON | AHCI_FLAG_INTEL_PCS | AHCI_FLAG_BROKEN_SLEEP,
        .PioFlags               = UNIVERSAL_ATA_PIO4,
        .DmaFlags               = UNIVERSAL_ATA_UDMA6,
        .DevicesPortOperations  = &AhciGenericOperations,
    },
    [AHCI_BOARD_PCS_NO_SNTF]   = {
        .AhciFlags              = AHCI_FLAG_COMMON | AHCI_FLAG_INTEL_PCS | AHCI_FLAG_BROKEN_SNTF,
        .PioFlags               = UNIVERSAL_ATA_PIO4,
        .DmaFlags               = UNIVERSAL_ATA_UDMA6,
        .DevicesPortOperations  = &AhciGenericOperations,
    },
    [AHCI_BOARD_HAS_FBS]   = {
        .AhciFlags              = AHCI_FLAG_COMMON | AHCI_FLAG_HAS_FBS,
        .PioFlags               = UNIVERSAL_ATA_PIO4,
        .DmaFlags               = UNIVERSAL_ATA_UDMA6,
        .DevicesPortOperations  = &AhciGenericOperations,
    },
    [AHCI_BOARD_AL_CHIP]   = {
        .AhciFlags              = AHCI_FLAG_COMMON | AHCI_FLAG_HAS_NO_PMP | AHCI_FLAG_NO_MSI,
        .PioFlags               = UNIVERSAL_ATA_PIO4,
        .DmaFlags               = UNIVERSAL_ATA_UDMA6,
        .DevicesPortOperations  = &AhciGenericOperations,
    },
    [AHCI_BOARD_AVN_CHIP]   = {
        .AhciFlags              = AHCI_FLAG_COMMON | AHCI_FLAG_INTEL_PCS,
        .PioFlags               = UNIVERSAL_ATA_PIO4,
        .DmaFlags               = UNIVERSAL_ATA_UDMA6,
        .DevicesPortOperations  = &AhciAvnOperations,
    },
    [AHCI_BOARD_MCP65_CHIP]   = {
        .AhciFlags              = AHCI_FLAG_COMMON | AHCI_FLAG_HAS_NO_PMP | AHCI_FLAG_NO_FPDMA_AA,
        .AtaFlags               = ATA_FLAG_NO_DIPM,
        .PioFlags               = UNIVERSAL_ATA_PIO4,
        .DmaFlags               = UNIVERSAL_ATA_UDMA6,
        .DevicesPortOperations  = &AhciGenericOperations,
    },
    [AHCI_BOARD_MCP77_CHIP]   = {
        .AhciFlags              = AHCI_FLAG_COMMON | AHCI_FLAG_HAS_NO_PMP | AHCI_FLAG_NO_FPDMA_AA,
        .PioFlags               = UNIVERSAL_ATA_PIO4,
        .DmaFlags               = UNIVERSAL_ATA_UDMA6,
        .DevicesPortOperations  = &AhciGenericOperations,
    },
    [AHCI_BOARD_MCP89_CHIP]   = {
        .AhciFlags              = AHCI_FLAG_COMMON | AHCI_FLAG_NO_FPDMA_AA,
        .PioFlags               = UNIVERSAL_ATA_PIO4,
        .DmaFlags               = UNIVERSAL_ATA_UDMA6,
        .DevicesPortOperations  = &AhciGenericOperations,
    },
    [AHCI_BOARD_MV_CHIP]   = {
        .AhciFlags              = AHCI_FLAG_NO_NCQ | AHCI_FLAG_NO_MSI | AHCI_FLAG_MV_PATA | AHCI_FLAG_HAS_NO_PMP,
        .AtaFlags               = ATA_FLAG_SATA | ATA_FLAG_PIO_DMA,
        .PioFlags               = UNIVERSAL_ATA_PIO4,
        .DmaFlags               = UNIVERSAL_ATA_UDMA6,
        .DevicesPortOperations  = &AhciGenericOperations,
    },
    [AHCI_BOARD_SB600_CHIP]   = {
        .AhciFlags              = AHCI_FLAG_COMMON | AHCI_FLAG_NO_MSI | AHCI_FLAG_SECTOR255 | AHCI_FLAG_32BIT_ONLY | AHCI_FLAG_IGN_INTERNAL_SERR,
        .PioFlags               = UNIVERSAL_ATA_PIO4,
        .DmaFlags               = UNIVERSAL_ATA_UDMA6,
        .DevicesPortOperations  = &AhciPmpRetySrStOperations,
    },
    [AHCI_BOARD_SB700_CHIP]   = {
        .AhciFlags              = AHCI_FLAG_COMMON | AHCI_FLAG_IGN_INTERNAL_SERR,
        .PioFlags               = UNIVERSAL_ATA_PIO4,
        .DmaFlags               = UNIVERSAL_ATA_UDMA6,
        .DevicesPortOperations  = &AhciPmpRetySrStOperations,
    },
    [AHCI_BOARD_VT8251_CHIP]   = {
        .AhciFlags              = AHCI_FLAG_COMMON | AHCI_FLAG_NO_NCQ | AHCI_FLAG_HAS_NO_PMP,
        .PioFlags               = UNIVERSAL_ATA_PIO4,
        .DmaFlags               = UNIVERSAL_ATA_UDMA6,
        .DevicesPortOperations  = &AhciVt8251Operations,
    },
};  

UNUSED static LOUSINE_PCI_DEVICE_TABLE AhciDevices[] = {
    //Intel Ahci Devices
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x06D6, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //Commet Lake PCH-H Raid
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x2652, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH6
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x2653, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH6M
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x27C1, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH7
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x27C5, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH7M
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x27C3, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH7R     
    {.VendorID = PCI_VENDOR_ID_AL,    .DeviceID = 0x5288, .BoardID = AHCI_BOARD_IGN_IFFER, .SimpleEntry = true},        //ULi M5288
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x2681, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ESB 2
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x2682, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ESB 2
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x2683, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ESB 2
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x27C6, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH7-M DH
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x2821, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH8
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x2822, .BoardID = AHCI_BOARD_PCS_NO_SNTF, .SimpleEntry = true},      //ICH8 Lewisburg Raid
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x2824, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH8
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x2829, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH8M
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x282A, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH8M
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x2922, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH9
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x2923, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH9
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x2924, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH9
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x2925, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH9
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x2927, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH9
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x2929, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH9M
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x292A, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH9M
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x292B, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH9M
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x292C, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH9M
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x292F, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH9M
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x294D, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH9
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x294E, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH9M
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x502A, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //TOLAPAI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x502B, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //TOLAPAI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x3A05, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH10
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x3A22, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH10
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x3A25, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //ICH10
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x3B22, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //PCH AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x3B23, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //PCH AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x3B24, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //PCH RAID
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x3B25, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //PCH RAID
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x3B29, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //PCHM AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x3B2B, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //PCH RAID
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x3B2C, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //PCHM RAID
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x3B2F, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //PCH AHCI

    //TODO : Finish NVIDIA NVIDIA And INTEL DOCUMENTATION for the rest of the boards

    //Amazon Labs Devices
    {.VendorID = PCI_VENDOR_ID_AMAZON_ANNAPURNA_LABS, .DeviceID = 0x0031,.BoardID = AHCI_BOARD_AL_CHIP,.SimpleEntry = true},

    //JmMicro Devices
    {.VendorID = PCI_VENDOR_ID_JMICRON, .DeviceID = ANY_PCI_ID, .SubVendorID = ANY_PCI_ID, .SubDeviceID = ANY_PCI_ID, .BoardID = AHCI_BOARD_IGN_IFFER, .AdvancedEntry = true},
    {.VendorID = PCI_VENDOR_ID_JMICRON, .DeviceID = 0x2362, .BoardID = AHCI_BOARD_IGN_IFFER, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_JMICRON, .DeviceID = 0x236F, .BoardID = AHCI_BOARD_IGN_IFFER, .SimpleEntry = true},

    //(Advanced Micro Devices) Devices
    {.VendorID = PCI_VENDOR_ID_AMD, .DeviceID = 0x7800, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_AMD, .DeviceID = 0x7801, .BoardID = AHCI_BOARD_NO_BOUNCE, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_AMD, .DeviceID = 0x7900, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_AMD, .DeviceID = 0x7901, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_AMD, .DeviceID = ANY_PCI_ID, .SubVendorID = ANY_PCI_ID, .SubDeviceID = ANY_PCI_ID, .BoardID = AHCI_BOARD_NORMAL_AHCI, .AdvancedEntry = true},
    {.VendorID = PCI_VENDOR_ID_ATI, .DeviceID = 0x4380, .BoardID = AHCI_BOARD_SB600_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_ATI, .DeviceID = 0x4390, .BoardID = AHCI_BOARD_SB700_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_ATI, .DeviceID = 0x4391, .BoardID = AHCI_BOARD_SB700_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_ATI, .DeviceID = 0x4392, .BoardID = AHCI_BOARD_SB700_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_ATI, .DeviceID = 0x4393, .BoardID = AHCI_BOARD_SB700_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_ATI, .DeviceID = 0x4394, .BoardID = AHCI_BOARD_SB700_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_ATI, .DeviceID = 0x4395, .BoardID = AHCI_BOARD_SB700_CHIP, .SimpleEntry = true},

    //Dell Specific Devices
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = ANY_PCI_ID, .SubVendorID = PCI_SUBVENDOR_ID_DELL, .SubDeviceID = ANY_PCI_ID, .BoardID = AHCI_BOARD_INTEL_PCS, .AdvancedEntry = true},

    //VIA Devices
    {.VendorID = PCI_VENDOR_ID_VIA, .DeviceID = 0x3349, .BoardID = AHCI_BOARD_VT8251_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_VIA, .DeviceID = 0x6287, .BoardID = AHCI_BOARD_VT8251_CHIP, .SimpleEntry = true},

    //SiS Devices
    {.VendorID = PCI_VENDOR_ID_SI, .DeviceID = 0x1184, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_SI, .DeviceID = 0x1185, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_SI, .DeviceID = 0x0186, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},

    //ST Mirco Devices
    {.VendorID = PCI_VENDOR_ID_STMICRO, .DeviceID = 0xCC06, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},

    //Marvel Devices
    {.VendorID = PCI_VENDOR_ID_MARVELL, .DeviceID = 0x6145, .BoardID = AHCI_BOARD_MV_CHIP, .SimpleEntry = true},                                                                            //6145
    {.VendorID = PCI_VENDOR_ID_MARVELL, .DeviceID = 0x6121, .BoardID = AHCI_BOARD_MV_CHIP, .SimpleEntry = true},                                                                            //6121
    {.VendorID = PCI_VENDOR_ID_MARVELL_EXT, .DeviceID = 0x9123, .BaseClass = 0x01, .SubClass = 0x06, .BoardID = AHCI_BOARD_HAS_FBS, .SimpleWithClass = true},                               //88SE9128
    {.VendorID = PCI_VENDOR_ID_MARVELL_EXT, .DeviceID = 0x9125, .BoardID = AHCI_BOARD_HAS_FBS, .SimpleEntry = true},                                                                        //88SE9125
    {.VendorID = PCI_VENDOR_ID_MARVELL_EXT, .DeviceID = 0x9178, .SubVendorID = PCI_VENDOR_ID_MARVELL_EXT, .SubDeviceID = 0x9170, .BoardID = AHCI_BOARD_HAS_FBS, .AdvancedEntry = true},     //88SE9170
    {.VendorID = PCI_VENDOR_ID_MARVELL_EXT, .DeviceID = 0x917A, .BoardID = AHCI_BOARD_HAS_FBS, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_MARVELL_EXT, .DeviceID = 0x9172, .BoardID = AHCI_BOARD_HAS_FBS, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_MARVELL_EXT, .DeviceID = 0x9182, .BoardID = AHCI_BOARD_HAS_FBS, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_MARVELL_EXT, .DeviceID = 0x9192, .BoardID = AHCI_BOARD_HAS_FBS, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_MARVELL_EXT, .DeviceID = 0x91A0, .BoardID = AHCI_BOARD_HAS_FBS, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_MARVELL_EXT, .DeviceID = 0x91A2, .BoardID = AHCI_BOARD_HAS_FBS, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_MARVELL_EXT, .DeviceID = 0x91A3, .BoardID = AHCI_BOARD_HAS_FBS, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_MARVELL_EXT, .DeviceID = 0x9230, .BoardID = AHCI_BOARD_HAS_FBS, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_MARVELL_EXT, .DeviceID = 0x9235, .BoardID = AHCI_BOARD_NO_BOUNCE, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_TTI, .DeviceID = 0x0642, .BoardID = AHCI_BOARD_HAS_FBS, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_TTI, .DeviceID = 0x0645, .BoardID = AHCI_BOARD_HAS_FBS, .SimpleEntry = true},

    //Promise Devices
    {.VendorID = PCI_VENDOR_ID_PROMISE, .DeviceID = 0x3F20, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true}, //PDC42819
    {.VendorID = PCI_VENDOR_ID_PROMISE, .DeviceID = 0x3781, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true}, //Fast Track TX8660 AHCI

    //ASMedia Devices
    {.VendorID = PCI_VENDOR_ID_ASMEDIA, .DeviceID = 0x0601, .BoardID = AHCI_BOARD_43_BIT_DMA, .SimpleEntry = true},     //ASM1060
    {.VendorID = PCI_VENDOR_ID_ASMEDIA, .DeviceID = 0x0602, .BoardID = AHCI_BOARD_43_BIT_DMA, .SimpleEntry = true},     //ASM1060   
    {.VendorID = PCI_VENDOR_ID_ASMEDIA, .DeviceID = 0x0611, .BoardID = AHCI_BOARD_43_BIT_DMA, .SimpleEntry = true},     //ASM1061
    {.VendorID = PCI_VENDOR_ID_ASMEDIA, .DeviceID = 0x0612, .BoardID = AHCI_BOARD_43_BIT_DMA, .SimpleEntry = true},     //ASM1061/1062
    {.VendorID = PCI_VENDOR_ID_ASMEDIA, .DeviceID = 0x0621, .BoardID = AHCI_BOARD_43_BIT_DMA, .SimpleEntry = true},     //ASM1061R
    {.VendorID = PCI_VENDOR_ID_ASMEDIA, .DeviceID = 0x0622, .BoardID = AHCI_BOARD_43_BIT_DMA, .SimpleEntry = true},     //ASM1062R
    {.VendorID = PCI_VENDOR_ID_ASMEDIA, .DeviceID = 0x0624, .BoardID = AHCI_BOARD_43_BIT_DMA, .SimpleEntry = true},     //ASM1062+JMB575
    {.VendorID = PCI_VENDOR_ID_ASMEDIA, .DeviceID = 0x1062, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},    //ASM1062A
    {.VendorID = PCI_VENDOR_ID_ASMEDIA, .DeviceID = 0x1064, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},    //ASM1064
    {.VendorID = PCI_VENDOR_ID_ASMEDIA, .DeviceID = 0x1164, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},    //ASM1164
    {.VendorID = PCI_VENDOR_ID_ASMEDIA, .DeviceID = 0x1165, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},    //ASM1165
    {.VendorID = PCI_VENDOR_ID_ASMEDIA, .DeviceID = 0x1166, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},    //ASM1166

    //Samsung Macraps Devices
    {.VendorID = PCI_VENDOR_ID_SAMSUNG, .DeviceID = 0x1600, .BoardID = AHCI_BOARD_NO_MSI, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_SAMSUNG, .DeviceID = 0xA800, .BoardID = AHCI_BOARD_NO_MSI, .SimpleEntry = true},

    //Enmotus Devices
    {.VendorID = 0x1C44, .DeviceID = 0x8000, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},

    //Loongson Devices
    {.VendorID = PCI_VENDOR_ID_LOONGSON, .DeviceID = 0x7A08, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},

    //Generic Ahci Device    
    {.BaseClass = 0x01, .SubClass = 0x06, .BoardID = AHCI_BOARD_NORMAL_AHCI, .GenericEntry = true},
    //List Termination
    {0},
};

VOID AhciUnloadDriver(PDRIVER_OBJECT){
    DbgPrint("AhciUnloadDriver()\r\n");


    DbgPrint("AhciUnloadDriver() RETURN\r\n");
}

NTSTATUS AddAhciDevice(PDRIVER_OBJECT DriverObject ,PDEVICE_OBJECT Device){
    DbgPrint("AddAhciDevice()\r\n");

    LouPrint("Ahci DeviceID:%d\r\n", Device->DeviceID);

    DbgPrint("AddAhciDevice() STATUS_SUCCESS\r\n");
    return STATUS_SUCCESS;
}


//Unique name for AhciDriver due to the driver being built into the kernels binary
//And we will be using the (LOUSINE SUBSYSTEM FOR NT DRIVERS) with Lousine function
//for streamlineing certain things 
NTSTATUS AhciDriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryEntry){
    DbgPrint("DriverEntry()\r\n");

    //tell the System where are key Nt driver functions are
    DriverObject->DriverUnload = AhciUnloadDriver;
    DriverObject->DriverExtension->AddDevice = AddAhciDevice;
    //tell the losine kernel we will be using the
    //Lousine Driver Module (LDM) alongside the
    //NT Kernel Moudle Subsystem so it fills
    //out the extra information
    DriverObject->DriverUsingLdm = true;
    //fill LDM information
    DriverObject->DeviceTable = (uintptr_t)AhciDevices;
    
    DbgPrint("DriverEntry() STATUS_SUCCESS\r\n");
    return STATUS_SUCCESS;
}