#define _KERNEL_MODULE_
#include <LouDDK.h>
#include <Hal.h>

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
 */

 
#include "AhciMod.h"


//ATA Module Structured Operations
UNUSED static LOUSINE_ATA_PORT_OPERATIONS AhciGenericOperations{
    //.PrepCommand = AhciGenricDMAPrepCommand,
    .IssueCommand = AhciGenricDMAIssueCommand,
    .HardReset = AhciGenericHardReset,
    .HostReset = ResetAhcPciController,
    .PortStart = AhciStartPort,
    .PortStop = AhciStopPort,
};

UNUSED static LOUSINE_ATA_PORT_OPERATIONS AhciVt8251Operations{
    //.PrepCommand = AhciGenricDMAPrepCommand,
    .IssueCommand = AhciGenricDMAIssueCommand,
    .HardReset = AhciVt8251HardReset,
    .HostReset = ResetAhcPciController,
    .PortStart = AhciStartPort,
    .PortStop = AhciStopPort,
};

UNUSED static LOUSINE_ATA_PORT_OPERATIONS AhciP5wdhOperations{
    //.PrepCommand = AhciGenricDMAPrepCommand,
    .IssueCommand = AhciGenricDMAIssueCommand,
    .HardReset = AhciP5wdhHardReset,
    .HostReset = ResetAhcPciController,
    .PortStart = AhciStartPort,
    .PortStop = AhciStopPort,
};

UNUSED static LOUSINE_ATA_PORT_OPERATIONS AhciAvnOperations{
    //.PrepCommand = AhciGenricDMAPrepCommand,
    .IssueCommand = AhciGenricDMAIssueCommand,
    .HardReset = AhciAvnHardReset,
    .HostReset = ResetAhcPciController,
    .PortStart = AhciStartPort,
    .PortStop = AhciStopPort,
};


UNUSED static LOUSINE_ATA_PORT_OPERATIONS AhciPmpRetySrStOperations{
    //.PrepCommand = AhciGenricDMAPrepCommand,
    .IssueCommand = AhciGenricDMAIssueCommand,
    .HardReset = AhciGenericHardReset,
    .HostReset = ResetAhcPciController, 
};

//endof ATA Module Structured Operations

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
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x19B0, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},      //DNV AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x19B1, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},      //DNV AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x19B2, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},      //DNV AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x19B3, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},      //DNV AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x19B4, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},      //DNV AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x19B5, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},      //DNV AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x19B6, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},      //DNV AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x19B7, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},      //DNV AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x19BE, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},      //DNV AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x19BF, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},      //DNV AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x19C0, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},      //DNV AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x19C1, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},      //DNV AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x19C2, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},      //DNV AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x19C3, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},      //DNV AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x19C4, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},      //DNV AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x19C5, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},      //DNV AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x19C6, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},      //DNV AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x19C7, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},      //DNV AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x19CE, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},      //DNV AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x19CF, .BoardID = AHCI_BOARD_NORMAL_AHCI, .SimpleEntry = true},      //DNV AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x1C02, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //CPT AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x1C03, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //CPT M AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x1C04, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //CPT RAID
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x1C05, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //CPT M RAID
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x1C06, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //CPT RAID
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x1C07, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //CPT RAID
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x1D02, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //PBG RAID
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x1D04, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //PBG RAID
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x1D06, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //PBG RAID
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x2323, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //DH89XXCC
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x1E02, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //Panther Point AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x1E03, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //Panther M AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x1E04, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //Panther Point AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x1E05, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //Panther Point AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x1E06, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //Panther Point AHCI
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x1E07, .BoardID = AHCI_BOARD_INTEL_PCS, .SimpleEntry = true},        //Panther M AHCI

    //TODO: Finish intell Devices At the end

    //NVIDIA Devices : MCP ARCHITECTURE
    //NVIDIA MCP 65 CHIPS
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x044C, .BoardID = AHCI_BOARD_MCP65_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x044D, .BoardID = AHCI_BOARD_MCP65_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x044E, .BoardID = AHCI_BOARD_MCP65_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x044F, .BoardID = AHCI_BOARD_MCP65_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x045C, .BoardID = AHCI_BOARD_MCP65_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x045D, .BoardID = AHCI_BOARD_MCP65_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x045E, .BoardID = AHCI_BOARD_MCP65_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x045F, .BoardID = AHCI_BOARD_MCP65_CHIP, .SimpleEntry = true},
    //NVIDIA MCP 67 CHIPS
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0550, .BoardID = AHCI_BOARD_MCP67_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0551, .BoardID = AHCI_BOARD_MCP67_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0552, .BoardID = AHCI_BOARD_MCP67_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0553, .BoardID = AHCI_BOARD_MCP67_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0554, .BoardID = AHCI_BOARD_MCP67_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0555, .BoardID = AHCI_BOARD_MCP67_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0556, .BoardID = AHCI_BOARD_MCP67_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0557, .BoardID = AHCI_BOARD_MCP67_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0558, .BoardID = AHCI_BOARD_MCP67_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0559, .BoardID = AHCI_BOARD_MCP67_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x055A, .BoardID = AHCI_BOARD_MCP67_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x055B, .BoardID = AHCI_BOARD_MCP67_CHIP, .SimpleEntry = true},
    //NVIDIA MCP 65 CHIPS With LINUX Modified Firmware
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0580, .BoardID = AHCI_BOARD_LINUX_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0581, .BoardID = AHCI_BOARD_LINUX_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0582, .BoardID = AHCI_BOARD_LINUX_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0583, .BoardID = AHCI_BOARD_LINUX_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0584, .BoardID = AHCI_BOARD_LINUX_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0585, .BoardID = AHCI_BOARD_LINUX_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0586, .BoardID = AHCI_BOARD_LINUX_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0587, .BoardID = AHCI_BOARD_LINUX_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0588, .BoardID = AHCI_BOARD_LINUX_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0589, .BoardID = AHCI_BOARD_LINUX_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x058A, .BoardID = AHCI_BOARD_LINUX_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x058B, .BoardID = AHCI_BOARD_LINUX_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x058C, .BoardID = AHCI_BOARD_LINUX_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x058D, .BoardID = AHCI_BOARD_LINUX_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x058E, .BoardID = AHCI_BOARD_LINUX_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x058F, .BoardID = AHCI_BOARD_LINUX_CHIP, .SimpleEntry = true},
    //NVIDIA MCP 73 CHIPS
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x07F0, .BoardID = AHCI_BOARD_MCP73_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x07F1, .BoardID = AHCI_BOARD_MCP73_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x07F2, .BoardID = AHCI_BOARD_MCP73_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x07F3, .BoardID = AHCI_BOARD_MCP73_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x07F4, .BoardID = AHCI_BOARD_MCP73_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x07F5, .BoardID = AHCI_BOARD_MCP73_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x07F6, .BoardID = AHCI_BOARD_MCP73_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x07F7, .BoardID = AHCI_BOARD_MCP73_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x07F8, .BoardID = AHCI_BOARD_MCP73_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x07F9, .BoardID = AHCI_BOARD_MCP73_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x07FA, .BoardID = AHCI_BOARD_MCP73_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x07FB, .BoardID = AHCI_BOARD_MCP73_CHIP, .SimpleEntry = true},
    //NVIDIA MCP 77 CHIPS
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0AD0, .BoardID = AHCI_BOARD_MCP77_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0AD1, .BoardID = AHCI_BOARD_MCP77_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0AD2, .BoardID = AHCI_BOARD_MCP77_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0AD3, .BoardID = AHCI_BOARD_MCP77_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0AD4, .BoardID = AHCI_BOARD_MCP77_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0AD5, .BoardID = AHCI_BOARD_MCP77_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0AD6, .BoardID = AHCI_BOARD_MCP77_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0AD7, .BoardID = AHCI_BOARD_MCP77_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0AD8, .BoardID = AHCI_BOARD_MCP77_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0AD9, .BoardID = AHCI_BOARD_MCP77_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0ADA, .BoardID = AHCI_BOARD_MCP77_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0ADB, .BoardID = AHCI_BOARD_MCP77_CHIP, .SimpleEntry = true},
    //NVIDIA MCP 79 CHIPS
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0AB4, .BoardID = AHCI_BOARD_MCP79_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0AB5, .BoardID = AHCI_BOARD_MCP79_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0AB6, .BoardID = AHCI_BOARD_MCP79_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0AB7, .BoardID = AHCI_BOARD_MCP79_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0AB8, .BoardID = AHCI_BOARD_MCP79_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0AB9, .BoardID = AHCI_BOARD_MCP79_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0ABA, .BoardID = AHCI_BOARD_MCP79_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0ABB, .BoardID = AHCI_BOARD_MCP79_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0ABC, .BoardID = AHCI_BOARD_MCP79_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0ABD, .BoardID = AHCI_BOARD_MCP79_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0ABE, .BoardID = AHCI_BOARD_MCP79_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0ABF, .BoardID = AHCI_BOARD_MCP79_CHIP, .SimpleEntry = true},
    //NVIDIA MCP 89 CHIPS
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0D84, .BoardID = AHCI_BOARD_MCP89_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0D85, .BoardID = AHCI_BOARD_MCP89_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0D86, .BoardID = AHCI_BOARD_MCP89_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0D87, .BoardID = AHCI_BOARD_MCP89_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0D88, .BoardID = AHCI_BOARD_MCP89_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0D89, .BoardID = AHCI_BOARD_MCP89_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0D8A, .BoardID = AHCI_BOARD_MCP89_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0D8B, .BoardID = AHCI_BOARD_MCP89_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0D8C, .BoardID = AHCI_BOARD_MCP89_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0D8D, .BoardID = AHCI_BOARD_MCP89_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0D8E, .BoardID = AHCI_BOARD_MCP89_CHIP, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_NVIDIA, .DeviceID = 0x0D8F, .BoardID = AHCI_BOARD_MCP89_CHIP, .SimpleEntry = true},

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
    {.BaseClass = 0x01, .SubClass = 0x06, .ProgIf = ANY_PCI_CLASS, .BoardID = AHCI_BOARD_NORMAL_AHCI, .GenericEntry = true},
    //List Termination
    {0},
};


VOID AhciUnloadDriver(
    PDRIVER_OBJECT DriverObject
){
    LouPrint("AHCI.SYS:AhciUnloadDriver()\n");
    //this is a dummy function due to the module
    //being built in there is nothing to unload
    LouPrint("AHCI.SYS:AhciUnloadDriver() RETURN\n");
}

static void AhciIntelPcs(PPCI_DEVICE_OBJECT PDEV, PAHCI_DRIVER_PRIVATE_DATA PrivateData){
    uint16_t Tmp;

    if(!(PrivateData->AhciFlags & AHCI_FLAG_INTEL_PCS)){
        return;
    }

    //according to linux documentation some PCS systems do not 
    //automatically or faild to enable all the ports so we can
    //try to do this now
    Tmp = LouKeReadPciUint16(PDEV, PCS6_PCI_REGISTER);
    if((Tmp & PrivateData->PortMap) != PrivateData->PortMap){
        Tmp |= PrivateData->PortMap;
        LouKeWritePciUint16(PDEV, PCS6_PCI_REGISTER, Tmp);
    }

}

static NTSTATUS ResetAhciHba(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost){
    UNUSED PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)LkdmAtaHostToPrivateData(AtaHost);
    UNUSED PAHCI_GENERIC_HOST_CONTROL Ghc = PrivateData->GenericHostController;    
    UNUSED uint32_t Tmp;
    uint32_t Poll = 0;
    LouPrint("AHCI.SYS:ResetAhciHba()\n");

    Tmp = Ghc->GlobalHostControl;
    if(!(Tmp & (1 << 31))){
        Tmp |= (1 << 31);
        Ghc->GlobalHostControl = Tmp;
        sleep(100);
        Tmp = Ghc->GlobalHostControl;
        if(!(Tmp & (1 << 31))){
            Tmp |= (1 << 31);
            for(uint8_t i = 0 ; i < 5; i = 0){
                Ghc->GlobalHostControl = Tmp;
            }
            sleep(100);
            if(!(Tmp & (1 << 31))){
                LouPrint("AHCI.SYS:ERROR Setting AE\n");
                return STATUS_IO_DEVICE_ERROR;
            }
        }
    }

    Tmp = Ghc->GlobalHostControl;
    Tmp |= 1;
    Ghc->GlobalHostControl = Tmp;

    while(Poll >= 1000){
        Tmp = Ghc->GlobalHostControl;
        if(!(Tmp & 0x01)){
            break;
        }
        Poll += 100;
        sleep(100);
    }

    if(Poll >= 1000){
        LouPrint("AHCI.SYS:Timeout HC Reset HBA Is Stuck\n");
        return STATUS_IO_DEVICE_ERROR;
    }

    Tmp = Ghc->GlobalHostControl;
    if(!(Tmp & (1 << 31))){
        Tmp |= (1 << 31);
        Ghc->GlobalHostControl = Tmp;
        sleep(100);
        Tmp = Ghc->GlobalHostControl;
        if(!(Tmp & (1 << 31))){
            Tmp |= (1 << 31);
            for(uint8_t i = 0 ; i < 5; i = 0){
                Ghc->GlobalHostControl = Tmp;
            }
            sleep(100);
            if(!(Tmp & (1 << 31))){
                LouPrint("AHCI.SYS:ERROR Setting AE\n");
                return STATUS_IO_DEVICE_ERROR;
            }
        }
    }

    LouPrint("AHCI.SYS:ResetAhciHba() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS ResetAhcPciController(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost){
    NTSTATUS Status = STATUS_SUCCESS;
    PPCI_DEVICE_OBJECT PDEV = LkdmAtaHostToPciDevice(AtaHost);
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)LkdmAtaHostToPrivateData(AtaHost);

    
    Status = ResetAhciHba(AtaHost);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    AhciIntelPcs(PDEV, PrivateData);

    return STATUS_SUCCESS;
}

static bool ChipHasAppleBios(PPCI_COMMON_CONFIG PciConfig){
    return (
        PciConfig->Header.VendorID == PCI_VENDOR_ID_NVIDIA && 
        PciConfig->Header.DeviceID == PCI_DEVICE_ID_NVIDIA_NFORCE_MCP89_SATA &&
        PciConfig->Header.u.type0.SubVendorID == PCI_VENDOR_ID_APPLE && 
        PciConfig->Header.u.type0.SubSystemID == 0xCB89
    ) ? true : false;
}

static void NvidiaMcp89AppleBiosUnlockAhciChip(PPCI_DEVICE_OBJECT PDEV){
    uint32_t Tmp;

    LouPrint("AHCI.SYS:Enableing MCP89 Ahci Mode For Macraps\n");
    
    //tell the device we are going to be accessing the controllers
    //Bios Settings
    Tmp = LouKeReadPciUint32(PDEV, 0xF8);
    Tmp |= (1 << 0x1B);
    LouKeWritePciUint32(PDEV, 0xF8, Tmp);
    //we have offically broken the terms and conditions of apples 
    //product use aggrement by modifying a device congratz everybody
    //(Hosnetly we all broke it when you deviceded to run this sofware
    //on your macbook)... just fair warning to end user;
    //now we need to Make Changes withought changing the Device ID
    //By setting Unsetting Bit 0xF0000000 and setting Bit 0x80000000
    Tmp = LouKeReadPciUint32(PDEV, 0x054C);
    Tmp |= (1 << 0x0C);
    LouKeWritePciUint32(PDEV, 0x054C, Tmp);

    //change the data
    Tmp = LouKeReadPciUint32(PDEV, 0x04A4);
    Tmp &= ~(0xFF);
    Tmp |= 0x01060100;
    LouKeWritePciUint32(PDEV, 0x04A4, Tmp);

    //cleanup the bios 
    Tmp = LouKeReadPciUint32(PDEV, 0x054C);
    Tmp &= ~(1 << 0x0C);
    LouKeWritePciUint32(PDEV, 0x054C, Tmp);

    Tmp = LouKeReadPciUint32(PDEV, 0xF8);
    Tmp &= ~(1 << 0x1B);
    LouKeWritePciUint32(PDEV, 0xF8, Tmp);
    //Ahci On Apple Bios Should Now Be Unlocked
}


LOUSTATUS AhciStopCommandEngine(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort);
void AhciStartCommandEngine(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort);
void AhciPciInitializeController(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost);

void AhciPortInterruptHandler(
    PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost,
    UINT32                          IrqMask
){  
    UINT32 Status;
    for(size_t i = 0 ; i < AtaHost->PortCount; i++){
        if(!(IrqMask & (1 << i))){
            continue;
        }
        PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort = &AtaHost->Ports[i]; 
        PAHCI_DRIVER_PRIVATE_DATA Private = (PAHCI_DRIVER_PRIVATE_DATA)AtaPort->PortPrivateData;
        PAHCI_GENERIC_PORT Port = Private->GenericPort;
        Status = Port->PxIS;
        Port->PxIS = Status;

        if(((Status & (1)) || (Status & (1 << 3))) && (!(Status & (0b00011111 << 26)))){
            for(size_t j = 0; j < 32; j++){
                if((Private->CommandsQueued & (1 << j)) && (!(Port->PxCI & (1 << j)))){
                    LouKeSignalEvent(&Private->CommandCompletion[j]);
                }
            }
        }
        //1895

    }
}

void AhciInterruptHandler(uint64_t IrqData){
    PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost = (PLOUSINE_KERNEL_DEVICE_ATA_HOST)IrqData;
    PAHCI_DRIVER_PRIVATE_DATA HostPrivateData = (PAHCI_DRIVER_PRIVATE_DATA)AtaHost->HostPrivateData;
    PAHCI_GENERIC_HOST_CONTROL Ghc = HostPrivateData->GenericHostController;
    UINT32 IrqStatus, IrqMask, Pi = Ghc->PortsImplemented;//3.1415
    LouKIRQL Irql;
    
    IrqStatus = Ghc->InterruptStatus;
    if(!IrqStatus){
        return;
    }
    IrqMask = IrqStatus & Pi;//3.1415
    //LouKeAcquireSpinLock(&AtaHost->HostLock, &Irql);

    AhciPortInterruptHandler(AtaHost, IrqMask);

    Ghc->InterruptStatus = IrqStatus;
    //LouKeReleaseSpinLock(&AtaHost->HostLock, &Irql);
    return;
}

static AhciSb600Enable64Bit(
    PPCI_DEVICE_OBJECT  PDEV
){
    UNUSED static const DMI_SYSTEM_ID SystemIds[] = {
        {
            .Identification = "ASUS M2A-VM",
            .Matches = {
				DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
				DMI_MATCH(DMI_BOARD_NAME, "M2A-VM"),            
            },
            .DriverData = (PVOID)"20071026",
        },
        {
			.Identification = "MSI K9A2 Platinum",
			.Matches = {
				DMI_MATCH(DMI_BOARD_VENDOR, "MICRO-STAR INTER"),
				DMI_MATCH(DMI_BOARD_NAME, "MS-7376"),
			},
		},
        {
			.Identification = "MSI K9AGM2",
			.Matches = {
				DMI_MATCH(DMI_BOARD_VENDOR, "MICRO-STAR INTER"),
				DMI_MATCH(DMI_BOARD_NAME, "MS-7327"),
			},    
		},
        {
			.Identification = "ASUS M3A",
			.Matches = {
				DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
				DMI_MATCH(DMI_BOARD_NAME, "M3A"),
			},
		},
        0,
    };

    PDMI_SYSTEM_ID Match;
    INTEGER Year, Month, Date;
    CHAR Buffer[9];

    Match = LouKeDmiGetFirstMatch((PDMI_SYSTEM_ID)SystemIds);
    if((PDEV->bus != 0x00) || (PDEV->func == 0x12) || (!Match)){
        return false;
    }

    if(!Match->DriverData){
        goto _ENABLE_64_BIT;
    }

    DmiGetDate(DMI_BIOS_DATE, &Year, &Month, &Date);
    snprintf(Buffer, 9, "%04d%02d%02d", Year, Month, Date);

    if(strcmp(Buffer, (string)Match->DriverData) >= 0){
        goto _ENABLE_64_BIT;
    }else{
        LouPrint("AHCI.SYS:WARNING:Device:%h Can Not Enable 64 Bit DMA BIOS Is Too Old\n", PDEV);
        return false;
    }

    _ENABLE_64_BIT:
    LouPrint("AHCI.SYS:WARNING:Device:%h Enabling 64 Bit DMA\n", PDEV);
    return true;
}

static void AhciRemapCheck(
    PPCI_DEVICE_OBJECT          PDEV,
    int                         Bar,
    PAHCI_DRIVER_PRIVATE_DATA   PrivateData
){
    int     i;
    UINT32  Capabilities;
    PPCI_COMMON_CONFIG PciConfig = (PPCI_COMMON_CONFIG)PDEV->CommonConfig;
    if(
        (PciConfig->Header.VendorID != 0x8086) || 
        (LouKeHalGetPciBaseAddressSize(PDEV, Bar) < (512 * KILOBYTE)) ||
        (Bar != AHCI_STANDARD_ABAR) ||
        (!(READ_REGISTER_ULONG((ULONG*)((UINT8*)((UINTPTR)PrivateData->GenericHostController + AHCI_VS_CAPABILITIES))) & 0x01))
    ){
        //LouPrint("AHCI.SYS:Vendor:%h\n", PciConfig->Header.VendorID);
        //LouPrint("AHCI.SYS:BarSize:%h\n", LouKeHalGetPciBaseAddressSize(PDEV, Bar));
        //LouPrint("AHCI.SYS:Capabilities:%h\n", READ_REGISTER_ULONG((ULONG*)((UINT8*)((UINTPTR)PrivateData->GenericHostController + AHCI_VS_CAPABILITIES))));
        LouPrint("AHCI.SYS:This AHCI Device Does Not Support NVME\n");
        return;
    }

    Capabilities = READ_REGISTER_ULONGLONG((ULONGLONG*)((UINT8*)((UINTPTR)PrivateData->GenericHostController + AHCI_REMAP_CAP)));
    for(i = 0; i < AHCI_MAXIMUM_REMAP; i++){
        if((Capabilities & (1 << i)) == 0){
            continue;
        } 
        if(READ_REGISTER_ULONG((ULONG*)((UINT8*)((UINTPTR)PrivateData->GenericHostController + AhciRemapDcc(i)))) != PCI_CLASS_STORAGE_EXPRESS){
            continue;
        }

        PrivateData->RemappedNvme++;
    }

    if(!PrivateData->RemappedNvme){
        LouPrint("AHCI.SYS:This AHCI Device Does Not Have Any NVME To Remap\n");
        return;
    }

    LouPrint("AHCI.SYS:This AHCI Device Has %d NVME Devices Remap\n", PrivateData->RemappedNvme);
    LouPrint("AHCI.SYS:If Your Bios Is In Raid Mode Switch To AHCI Mode To Use The NVME Device\n");

    PrivateData->AhciFlags |= AHCI_FLAG_NO_MSI;
}

static bool AhciHasBrokenSystemPowerOff(
    PPCI_DEVICE_OBJECT PDEV
){
    static const DMI_SYSTEM_ID BrokenSystems[] = {
        {
			.Identification = "HP Compaq nx6310",
			.Matches = {
				DMI_MATCH(DMI_SYSTEM_VENDOR, "Hewlett-Packard"),
				DMI_MATCH(DMI_PRODUCT_NAME, "HP Compaq nx6310"),
			},
			.DriverData = (PVOID)0x1F,
		},
		{
			.Identification = "HP Compaq 6720s",
			.Matches = {
				DMI_MATCH(DMI_SYSTEM_VENDOR, "Hewlett-Packard"),
				DMI_MATCH(DMI_PRODUCT_NAME, "HP Compaq 6720s"),
			},
			.DriverData = (PVOID)0x1F,
		},
        0,
    }; 

    PDMI_SYSTEM_ID Match = LouKeDmiGetFirstMatch((PDMI_SYSTEM_ID)BrokenSystems);

    if(Match){
        return (((UINT8)(UINTPTR)Match->DriverData) == PDEV->slot);
    }

    return false;
}

static bool AhciHasBrokenLpm(
    PPCI_DEVICE_OBJECT PDEV
){

    static DMI_SYSTEM_ID SystemIds[] = {
        {
            .Matches = {
                DMI_MATCH(DMI_SYSTEM_VENDOR, "LENOVO"),
                DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad X250"),
            },
            .DriverData = (PVOID)"20180406",
        },
        {
            .Matches = {
                DMI_MATCH(DMI_SYSTEM_VENDOR, "LENOVO"),
                DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad L450"),
            },
            .DriverData = (PVOID)"20180420",
        },
        {
            .Matches = {
                DMI_MATCH(DMI_SYSTEM_VENDOR, "LENOVO"),
                DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad T450s"),
            },
            .DriverData = (PVOID)"20180315",
        },
        {
            .Matches = {
				DMI_MATCH(DMI_SYSTEM_VENDOR, "LENOVO"),
				DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad W541"),
            },
            .DriverData = (PVOID)"20180409",
        },
        {
            .Matches = {
				DMI_MATCH(DMI_SYSTEM_VENDOR, "ASUSTeK COMPUTER INC."),
				DMI_MATCH(DMI_PRODUCT_NAME, "ASUSPRO D840MB_M840SA"),
            },
        },
        {
            .Matches = {
				DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK COMPUTER INC."),
				DMI_MATCH(DMI_BOARD_NAME, "ROG STRIX B550-F GAMING (WI-FI)"),            
            },
        },
        {},
    };

    PDMI_SYSTEM_ID Dmi = LouKeDmiGetFirstMatch(SystemIds);
    INTEGER Year, Month, Date;
    CHAR Buffer[9];

    if(!Dmi){
        return false;
    }
    if(!Dmi->DriverData){
        return true;
    }

    DmiGetDate(DMI_BIOS_DATE, &Year, &Month, &Date);
    snprintf(Buffer, 9, "%04d%02d%02d", Year, Month, Date);

    return strcmp(Buffer, (string)Dmi->DriverData) < 0;
}

static bool AhciHasBrokenSuspend(PPCI_DEVICE_OBJECT PDEV){

    UNUSED static DMI_SYSTEM_ID SystemIds[] = {
		{
			.Identification = "dv4",
			.Matches = {
				DMI_MATCH(DMI_SYSTEM_VENDOR, "Hewlett-Packard"),
				DMI_MATCH(DMI_PRODUCT_NAME,
					  "HP Pavilion dv4 Notebook PC"),
			},
			.DriverData = (PVOID)"20090105",
		},
		{
			.Identification = "dv5",
			.Matches = {
				DMI_MATCH(DMI_SYSTEM_VENDOR, "Hewlett-Packard"),
				DMI_MATCH(DMI_PRODUCT_NAME, "HP Pavilion dv5 Notebook PC"),
			},
			.DriverData = (PVOID)"20090506",
		},
		{
			.Identification = "dv6",
			.Matches = {
				DMI_MATCH(DMI_SYSTEM_VENDOR, "Hewlett-Packard"),
				DMI_MATCH(DMI_PRODUCT_NAME, "HP Pavilion dv6 Notebook PC"),
			},
			.DriverData = (PVOID)"20090423",
		},
		{
			.Identification = "HDX18",
			.Matches = {
				DMI_MATCH(DMI_SYSTEM_VENDOR, "Hewlett-Packard"),
				DMI_MATCH(DMI_PRODUCT_NAME, "HP HDX18 Notebook PC"),
			},
			.DriverData = (PVOID)"20090430",
		},
		{
			.Identification = "G725",
			.Matches = {
				DMI_MATCH(DMI_SYSTEM_VENDOR, "eMachines"),
				DMI_MATCH(DMI_PRODUCT_NAME, "eMachines G725"),
			},
			.DriverData = (PVOID)"20091216",
		},
		{ }
	};    
    PDMI_SYSTEM_ID Dmi = LouKeDmiGetFirstMatch(SystemIds);
    INTEGER Year, Month, Date;
    CHAR Buffer[9];

    if((!Dmi) || (PDEV->bus) || ((PDEV->slot != 0x1F) && (PDEV->func != 2))) {
        return false;
    }

    DmiGetDate(DMI_BIOS_DATE, &Year, &Month, &Date);
    snprintf(Buffer, 9, "%04d%02d%02d", Year, Month, Date);
    return strcmp(Buffer, (string)Dmi->DriverData) < 0;
}

static bool AhciHasBrokenOnline(
    PPCI_DEVICE_OBJECT PDEV
){
    static DMI_SYSTEM_ID SystemIds[] = {
        {
			.Identification = "EP45-DQ6",
			.Matches = {
				DMI_MATCH(DMI_BOARD_VENDOR, "Gigabyte Technology Co., Ltd."),
				DMI_MATCH(DMI_BOARD_NAME, "EP45-DQ6"),
			},
			.DriverData = AHCI_ENCODE_BUSDEVFUNC(0x0A, 0x00, 0),
		},
		{
			.Identification = "EP45-DS5",
			.Matches = {
				DMI_MATCH(DMI_BOARD_VENDOR, "Gigabyte Technology Co., Ltd."),
				DMI_MATCH(DMI_BOARD_NAME, "EP45-DS5"),
			},
			.DriverData = (PVOID)AHCI_ENCODE_BUSDEVFUNC(0x03, 0x00, 0),
		},
        {},
    };

    PDMI_SYSTEM_ID Dmi = LouKeDmiGetFirstMatch(SystemIds);
    if(!Dmi){
        return false;
    }
    UINT8 Bus, Slot, Func;
    AHCI_DECODE_BUSDEVFUNC(&Bus, &Slot, &Func, Dmi->DriverData); 

    return ((PDEV->bus == Bus) && (PDEV->slot == Slot) && (PDEV->func == Func));
}

static void AcerSa5_271WorkAround(
    PAHCI_DRIVER_PRIVATE_DATA   PrivateAhciData,
    PPCI_DEVICE_OBJECT          PDEV
){
    
    static DMI_SYSTEM_ID SystemIds[] = {
		{
			.Identification = "Acer Switch Alpha 12",
			.Matches = {
				DMI_MATCH(DMI_SYSTEM_VENDOR, "Acer"),
				DMI_MATCH(DMI_PRODUCT_NAME, "Switch SA5-271"),
			},
		},
        {},
    };

    if(LouKeCheckDmiSystem(SystemIds)){
        LouPrint("AHCI.SYS:Enableing Acer Switch Alpha 12 Workaround\n");
        if(((PrivateAhciData->GenericHostController->Capabilities) & 0xC734FF00) == 0xC734FF00){
            PrivateAhciData->PortMap = 0x07;      
            PrivateAhciData->CapOveride =  0xC734FF02;      
        }
    }

}

static void  AhciInitializeInterrupts(
    PPCI_DEVICE_OBJECT              PDEV, 
    UINT32                          PortCount,
    PAHCI_DRIVER_PRIVATE_DATA       PrivateData
){
    //1722
    UINT64 Flags = (PrivateData->AhciFlags & AHCI_FLAG_NO_MSI) ? PCI_IRQ_USE_LEGACY : (PCI_IRQ_USE_MSI | PCI_IRQ_USE_MSI_X) | (PCI_IRQ_USE_LEGACY);
    
    if(!NT_SUCCESS(LouKeHalMallocPciIrqVectors(
        PDEV, 
        PortCount,
        Flags  
    ))){
        LouPrint("AHCI.SYS:Interrupts For PCI Devices Could Not Be Allocated\n");
        return;
    }

    UINT8 Vectors = LouKeHalGetPciIrqVectorCount(PDEV);
    if(Vectors == 1){
        LouPrint("AHCI.SYS:Interrupts For Ahci Device Initialized\n");
        return;
    }

    LouPrint("AHCI.SYS:Initializing AHCI Interrupts\n");

    while(1);
}

static void AhciMarkExternalPort(PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort){
    PAHCI_DRIVER_PRIVATE_DATA PrivateAhciData = (PAHCI_DRIVER_PRIVATE_DATA)AtaPort->PortPrivateData;
    PAHCI_GENERIC_PORT GenericPort = PrivateAhciData->GenericPort;
    UINT32 Command = GenericPort->PxCMD;
    UINT32 Capabilities = PrivateAhciData->CapOveride ? PrivateAhciData->CapOveride : PrivateAhciData->GenericHostController->Capabilities;

    if(
        ((Command & AHCI_COMMAND_ESP) && (Capabilities & AHCI_SUPPORTS_SXS(Capabilities))) || 
        (Command & AHCI_COMMAND_HPCP)
    ){
        if(PrivateAhciData->ExternalPortMask & (1UL << AtaPort->PortNumber)){
            LouPrint("AHCI.SYS:Ignoring External/Hotplug Capability\n");
            return;
        }
        AtaPort->AtaPFlags |= ATA_PFLAG_EXTERNAL;
    }
}

static void AhciUpdateInitialLpmPolicy(PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort){
    
}

static LOUSTATUS AhciConfigureDmaMasks(
    PPCI_DEVICE_OBJECT          PDEV, 
    PAHCI_DRIVER_PRIVATE_DATA   AhciPrivate
){
    AhciPrivate->DmaBits = 32;
    UINT32 Capabilities = AhciPrivate->CapOveride ? AhciPrivate->CapOveride : AhciPrivate->GenericHostController->Capabilities;

    if(AHCI_SUPPORTS_S64A(Capabilities)){
        AhciPrivate->DmaBits = 64;
        LouPrint("AHCI.SYS:Ahci Controller Supports Long Mode DMA\n");
        if(AhciPrivate->AhciFlags & AHCI_FLAG_43BIT_DMA_ONLY){
            AhciPrivate->DmaBits = 43;
            LouPrint("AHCI.SYS:WARNING:Ahci Controller Only Supports 43 bit DMA\n");
        }
    }else {
        LouPrint("AHCI.SYS:Ahci Controller Only Supports 32 bit DMA\n");
    }

    return STATUS_SUCCESS;
}


static void AhciSetupInterruptHandler(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost){
    PPCI_DEVICE_OBJECT PDEV = AtaHost->PDEV;
    if(LouKeHalGetPciIrqVectorCount(PDEV) > 1){
        LouPrint("AhciSetupInterruptHandler()\n");
        while(1);
    } 
    else{
        RegisterInterruptHandler(AhciInterruptHandler, LouKeHalGetPciIrqVector(PDEV, 0), false, (uint64_t)AtaHost);
    }
}

NTSTATUS AddAhciDevice(
    PDRIVER_OBJECT DriverObject,
    struct _DEVICE_OBJECT* Device
){
    LouPrint("AHCI.SYS:AddAhciDevice()\n");
    //LouPrint("Ahci DeviceID:%d\r\n", Device->DeviceID);
    NTSTATUS Status = STATUS_SUCCESS;

    //get the device ID and Pci Device from the LKDM
    uint64_t AhciDeviceID = Device->DeviceID;
    uint8_t BoardID = AhciDevices[AhciDeviceID].BoardID;
    PPCI_DEVICE_OBJECT PDEV = LkdmDeviceObjectToPciDevice(Device);    
    UNUSED PAHCI_DRIVER_BOARD_INFORMATION BoardInformation = &AhciBoardInfomationTable[BoardID];
    int Abar = AHCI_STANDARD_ABAR;
    uint8_t PortCount;
    //Get Pci Config Handle and update the handle
    PPCI_COMMON_CONFIG PciConfig = (PPCI_COMMON_CONFIG)PDEV->CommonConfig;
    LouKeHalGetPciConfiguration(PDEV, PciConfig);

    //According to linux documentation An AHCI Driver Cannot Driver
    //Parrellel Devices such as those with MARVELL Designs due to a 
    //mix use of AHCI and Parrallel Ports on the chip therefore it is 
    //safer to use the generic ATA Driver Written for boot and initialize
    //an accelerated Driver for non boot Chips as well as the boot chip
    //once system reaches phase two device initialization with modules
    if(PciConfig->Header.VendorID == PCI_VENDOR_ID_MARVELL){
        return STATUS_NO_SUCH_DEVICE;
    }

    //According to linux dcumentation NNIDIA MCP89 CHIPS with Apple 
    //bios's has a locking mechanism for the AHCI chip and needs to
    //be unlocked before it can be used
    if(ChipHasAppleBios(PciConfig)){
        NvidiaMcp89AppleBiosUnlockAhciChip(PDEV);
    }

    //due to the nature of probing with base class 1 and sub class 6
    //the probe includes devices that posses a SAS Sata Chip and AHCI
    //is only able to drive AHCI devices so we need to tell the user
    //this to warn them if the need to uses the Drives Attached to the 
    //SAS platform chip
    if(PciConfig->Header.VendorID == PCI_VENDOR_ID_PROMISE){
        LouPrint("AHCI.SYS:WARNING:PDC42819 Detected Only Stata Devices May Be Used With This Module\n");
    }

    //acording to some proprietary information from STMicro, Cavium,
    //Enmotus, and Loongson, and a linux kernel document related to
    //a vendor with and id of 0x1C44 wich I Belive is refering to the 
    //Enmotus 8000 Storage IO Controller the Actual Standard BAR 5 used
    //for ABAR is not used on all controllers the following figures what 
    //bar should actually be use for the controller
    if((PciConfig->Header.VendorID == PCI_VENDOR_ID_STMICRO) && (PciConfig->Header.DeviceID == 0xCC06)){
        Abar = AHCI_STA2X11_ABAR; 
    }else if((PciConfig->Header.VendorID == 0x1C44) && (PciConfig->Header.DeviceID == 0x8000)){
        Abar = AHCI_ENMOTUS_ABAR;
    }else if(PciConfig->Header.VendorID == PCI_VENDOR_ID_CAVIUM){
        if(PciConfig->Header.DeviceID == 0xA01C){
            Abar = AHCI_CAVIUM_ABAR;
        }else if(PciConfig->Header.DeviceID == 0xA084){
            Abar = AHCI_GENERATION_5_CAVIUM_ABAR;
        }
    }else if((PciConfig->Header.VendorID == PCI_VENDOR_ID_LOONGSON) && (PciConfig->Header.DeviceID == 0x7A08)){
        Abar = AHCI_LOONGSON_ABAR;
    }

    //now we are finally ready to start the controller
    Status = LouKeHalEnablePciDevice(PDEV);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    //according to Linux and BSD documentation along with Several 
    //Documents By Intel documentation surrounding quirks on intel controllers
    //the ICH6 controllers ID 0x2652 and 0x2653 share ids for PIIX chips and 
    //AHCI Chips Types and if the controller while in combined mode
    //can posibly A. make the controller unstable or unsuable or B. just
    //completly damage the chip up to but not including destorying it
    if(
        (PciConfig->Header.VendorID == PCI_VENDOR_ID_INTEL && PciConfig->Header.DeviceID == 0x2652) || 
        (PciConfig->Header.VendorID == PCI_VENDOR_ID_INTEL && PciConfig->Header.DeviceID == 0x2653)
    ){
        //in order for us to ensure that the chips is not in combined mode
        //we nead to read the ICH map register in pci configuration space
        //and check if one of the first two bits, if they are we need to
        //leave this controller alone
        uint8_t ICHMap;

        ICHMap = LouKeReadPciUint8(PDEV, ICH_PCI_MAP_REGISTER);
        if(ICHMap & 0x03){
            LouPrint("AHCI.SYS:WARNING: Controller is in combined mode and connot enable AHCI Mode\n");
            return STATUS_NO_SUCH_DEVICE;
        }  
    }

    //At this point we are able to grab the host and start filling out
    //private data from the information on the controller
    PAHCI_GENERIC_HOST_CONTROL Ghc = (PAHCI_GENERIC_HOST_CONTROL)LouKePciGetIoRegion(PDEV, Abar, 0);

    PortCount = AHCI_GET_NP(Ghc->Capabilities) + 1;

    PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost = LouKeMallocAtaDevice(PDEV, PortCount);
    LouKeMallocAtaPrivateData(AtaHost, sizeof(AHCI_DRIVER_PRIVATE_DATA), GET_ALIGNMENT(AHCI_DRIVER_PRIVATE_DATA));
    PAHCI_DRIVER_PRIVATE_DATA PrivateAhciData = (PAHCI_DRIVER_PRIVATE_DATA)AtaHost->HostPrivateData;

    PrivateAhciData->PDEV = PDEV;

    PrivateAhciData->PortMap = (uint16_t)Ghc->PortsImplemented;

    PrivateAhciData->StopCommandEngine = AhciStopCommandEngine;
    PrivateAhciData->StartCommandEngine = AhciStartCommandEngine;

    //Store the host Mmio into private data
    PrivateAhciData->GenericHostController = Ghc;
    PrivateAhciData->AhciFlags |= (uint64_t)BoardInformation->AhciFlags;
    PrivateAhciData->AtaFlags  |= (uint64_t)BoardInformation->AtaFlags;
    PrivateAhciData->PioFlags  |= (uint64_t)BoardInformation->PioFlags;
    PrivateAhciData->DmaFlags  |= (uint64_t)BoardInformation->DmaFlags;

    for(size_t Slot = 0 ; Slot < 32; Slot++){
        LouKeInitializeEventTimeOut(&PrivateAhciData->CommandCompletion[Slot], 5000); //10 second timeout
    }

    //Nvidia MCP65 Chip Revisions 0xA1 and 0xA2 do not support
    //MSI so we should take note of this however the losuine
    //currently dosent support interrupts for storage devices
    //because storage devices are optimized for Poling because
    //Cpu time slicing is done as a (Virtual Process) meaning that
    //the system uses interrupt threads to manage context management
    if(
        (BoardID == AHCI_BOARD_MCP65_CHIP && PciConfig->Header.RevisionID == 0xA1) || 
        (BoardID == AHCI_BOARD_MCP65_CHIP && PciConfig->Header.RevisionID == 0xA2) 
    ){
        PrivateAhciData->AhciFlags |= AHCI_FLAG_NO_MSI;
    }

    //SB800 doesn't need to conform to the INTERNAL SERR quirk
    if(BoardID == AHCI_BOARD_SB700_CHIP && PciConfig->Header.RevisionID >= 0x40){
        PrivateAhciData->AhciFlags &= ~(AHCI_FLAG_IGN_INTERNAL_SERR);
    }

    if(AhciSb600Enable64Bit(PDEV)){
        PrivateAhciData->AhciFlags &= ~(AHCI_FLAG_32BIT_ONLY);
    }

    AhciRemapCheck(PDEV, Abar, PrivateAhciData);

    if(AHCI_SUPPORTS_SNCQ(Ghc->Capabilities)){
        PrivateAhciData->AtaFlags |= ATA_FLAG_NCQ;

        //according the the linux kernel documentation
        //auto activate optimization SHOULD be supported
        //all controller however like always some vendors
        //(NVIDIA) Cut corners and tend to have broken 
        //implementations on their chips allthough it
        //is not documented in the actual hardware manuals
        //it should be handled aproprietly
        if(!(PrivateAhciData->AhciFlags & AHCI_FLAG_NO_FPDMA_AA)){
            PrivateAhciData->AtaFlags |= ATA_FLAG_FPDMA_AA;
        }

        //Finally all systems with NCQ have a Auxil field
        PrivateAhciData->AtaFlags |= ATA_FLAG_FPDMA_AUXILERY;
    }

    if(AHCI_SUPPORTS_S64A(Ghc->Capabilities)){
        if(PrivateAhciData->AhciFlags & AHCI_FLAG_43BIT_DMA_ONLY){
            PrivateAhciData->DmaBits = 43;
        }else{
            PrivateAhciData->DmaBits = 64;
        }
    }else {
        PrivateAhciData->AhciFlags |= AHCI_FLAG_32BIT_ONLY;
        PrivateAhciData->DmaBits = 32;    
    }

    if(AHCI_SUPPORTS_PMP(Ghc->Capabilities)){
        PrivateAhciData->AtaFlags |= ATA_FLAG_PMP;   
    }

    AhciSetEmMessages(PrivateAhciData);
    
    if(AhciHasBrokenSystemPowerOff(PDEV)){
        PrivateAhciData->AhciFlags |= AHCI_FLAG_NO_POWEROFF_SPINDOWN;
        LouPrint("AHCI.SYS:AHCI Spindown Quirk Skipping Spindown On Power Off\n");
    }

    if(AhciHasBrokenLpm(PDEV)){
        PrivateAhciData->AtaFlags |= ATA_FLAG_NO_LPM;
        LouPrint("AHCI.SYS:BIOS Update Required For Link Power Management Support\n");
    }

    if(AhciHasBrokenSuspend(PDEV)){
        PrivateAhciData->AhciFlags |= AHCI_FLAG_NO_SUSPEND;
        LouPrint("AHCI.SYS:BIOS Update Required For Suspend And Resume\n");
    }

    if(AhciHasBrokenOnline(PDEV)){
        PrivateAhciData->AhciFlags |= AHCI_SRST_TOUT_IS_OFFLINE;
        LouPrint("AHCI.SYS:Online Status Unreliable Applying Workaround\n");
    }

    AcerSa5_271WorkAround(PrivateAhciData, PDEV);

    AhciInitializeInterrupts(PDEV, PortCount, PrivateAhciData);
        
    PrivateAhciData->InterruptRequestVector = LouKeHalGetPciIrqVector(PDEV, 0);

    UNUSED UINT32 TmpCap = (PrivateAhciData->CapOveride ? PrivateAhciData->CapOveride : Ghc->Capabilities);


    if(!(AHCI_SUPPORTS_SSS(TmpCap))){
        PrivateAhciData->AtaFlags |= ATA_FLAG_PARALLEL_SCAN;
    }else{
        LouPrint("AHCI.SYS:SSS Bit Set But Bus Scan Disabled\n");
    }

    if(!(AHCI_SUPPORTS_PSC(TmpCap))){
        PrivateAhciData->AtaFlags |= ATA_FLAG_NO_PART;
    }

    if(!(AHCI_SUPPORTS_SSC(TmpCap))){
        PrivateAhciData->AtaFlags |= ATA_FLAG_NO_SSC;
    }

    if(!(AHCI_SUPPORTS_SDS(Ghc->Capabilities2))){
        PrivateAhciData->AtaFlags |= ATA_FLAG_NO_DEV_SLP;
    }

    if(PrivateAhciData->AtaFlags & ATA_FLAG_EM){
        AhciResetEm(AtaHost);
    }


    LouKeForkAtaHostPrivateDataToPorts(AtaHost);
    
    ForEachAtaPort(AtaHost){
        PAHCI_DRIVER_PRIVATE_DATA PrivateAhciData2 = (PAHCI_DRIVER_PRIVATE_DATA)AtaHost->Ports[AtaPortIndex].PortPrivateData;
        PrivateAhciData2->GenericPort = (PAHCI_GENERIC_PORT)(uintptr_t)((uintptr_t)Ghc + 0x100 + AtaPortIndex * 0x80);

        AhciMarkExternalPort(&AtaHost->Ports[AtaPortIndex]);

        AhciUpdateInitialLpmPolicy(&AtaHost->Ports[AtaPortIndex]);

        if(Ghc->PortsImplemented & (1 << AtaPortIndex)){
            AtaHost->Ports[AtaPortIndex].AtaFlags = PrivateAhciData->AtaFlags;
            AtaHost->Ports[AtaPortIndex].Operations = BoardInformation[BoardID].DevicesPortOperations;
            AtaHost->Ports[AtaPortIndex].SerialDevice = true;
        }else{
            AtaHost->Ports[AtaPortIndex].Operations = 0x00;
        }
    }

    //2107
    //2110

    AhciConfigureDmaMasks(PDEV, PrivateAhciData);

    ResetAhcPciController(AtaHost);

    AhciPciInitializeController(AtaHost);
    LouKeHalPciSetMaster(PDEV);

    AhciSetupInterruptHandler(AtaHost);

    LouPrint("AHCI.SYS:Adding AHCI Device To Device Manager\n");    

    LouKeRegisterDevice(
        PDEV, 
        ATA_DEVICE_T,
        "Annya/System64/Drivers/AhciGen.sys",
        (void*)AtaHost,
        0x00
    );
    LouPrint("AHCI.SYS:AddAhciDevice() STATUS_SUCCESS\n");
    return Status;
}

LOUDDK_API_ENTRY
NTSTATUS 
DriverEntry(
    PDRIVER_OBJECT DriverObject, 
    PUNICODE_STRING RegistryEntry
){
    LouPrint(AHCI_SYSTEM_MODULE_VERSION_MESSAGE);
    LouPrint("AHCI.SYS:DriverEntry()\n");

    //tell the System where are key Nt driver functions are
    DriverObject->DriverUnload = AhciUnloadDriver;
    DriverObject->DriverExtension->AddDevice = AddAhciDevice;
    //tell the lousine kernel we will be using the
    //Lousine Kernel Driver Module (LKDM) alongside the
    //NT Kernel Moudle Subsystem so it fills
    //out the extra information relating to the LKDM
    DriverObject->DriverUsingLkdm = true;
    //fill LDM information
    DriverObject->DeviceTable = (uintptr_t)AhciDevices;
    
    LouPrint("AHCI.SYS:DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}