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

#include "AhciMod.h"

LOUSTATUS AhciGenericPortDevicePrepCommand(
    PATA_PORT_DEVICE_OBJECT PortDevice,
    PATA_COMMAND_PACKET     CommandPacket
){

    LouPrint("AhciGenericPortDevicePrepCommand()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS AhciGenericPortDeviceIssueCommand(
    PATA_PORT_DEVICE_OBJECT PortDevice,
    PATA_COMMAND_PACKET     CommandPacket
){

    LouPrint("AhciGenericPortDeviceIssueCommand()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS AhciGenericPortDeviceCleanupCommand(
    PATA_PORT_DEVICE_OBJECT PortDevice,
    PATA_COMMAND_PACKET     CommandPacket
){

    LouPrint("AhciGenericPortDeviceCleanupCommand()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS AhciGenericPortDeviceStartPort(PATA_PORT_DEVICE_OBJECT PortDevice){

    LouPrint("AhciGenericPortDeviceStartPort()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS AhciGenericPortDeviceStopPort(PATA_PORT_DEVICE_OBJECT PortDevice){

    LouPrint("AhciGenericPortDeviceStopPort()\n");
    while(1);
    return STATUS_SUCCESS;
}


LOUSTATUS AhciGenericHostReset(PATA_HOST_DEVICE_OBJECT PortDevice){

    LouPrint("AhciGenericPortDeviceStopPort()\n");
    while(1);
    return STATUS_SUCCESS;
}


static ATA_HOST_OPERATIONS AhciGenericHostOperations = {
    .AtaHostDeviceReset = AhciGenericHostReset,
//    .AtaHostDeviceStart = AtaGenericHostDeviceStart,
//    .AtaHostDeviceStop = AtaGenericHostDeviceStop,
//    .AtaHostDeviceWake = AtaGenericHostDeviceWake,
//    .AtaHostDeviceSleep = AtaGenericHostDeviceSleep,
//    .AtaHostDevicePowerUp = AtaGenericHostDevicePowerUp,
//    .AtaHostDevicePowerDown = AtaGenericHostDevicePowerDown,
};

//static ATA_HOST_OPERATIONS AhciVt8251HostOperations = {
//    .AtaHostDeviceReset = AhciGenericHostReset,
//    .AtaHostDeviceStart = AtaGenericHostDeviceStart,
//    .AtaHostDeviceStop = AtaGenericHostDeviceStop,
//    .AtaHostDeviceWake = AtaGenericHostDeviceWake,
//    .AtaHostDeviceSleep = AtaGenericHostDeviceSleep,
//    .AtaHostDevicePowerUp = AtaGenericHostDevicePowerUp,
//    .AtaHostDevicePowerDown = AtaGenericHostDevicePowerDown,
//};

//static ATA_HOST_OPERATIONS AhciP5wdhHostOperations = {
//    .AtaHostDeviceReset = AhciGenericHostReset,
//    .AtaHostDeviceStart = AtaGenericHostDeviceStart,
//    .AtaHostDeviceStop = AtaGenericHostDeviceStop,
//    .AtaHostDeviceWake = AtaGenericHostDeviceWake,
//    .AtaHostDeviceSleep = AtaGenericHostDeviceSleep,
//    .AtaHostDevicePowerUp = AtaGenericHostDevicePowerUp,
//    .AtaHostDevicePowerDown = AtaGenericHostDevicePowerDown,
//};


//static ATA_HOST_OPERATIONS AhciAvnHostOperations = {
//    .AtaHostDeviceReset = AhciGenericHostReset,
//    .AtaHostDeviceStart = AtaGenericHostDeviceStart,
//    .AtaHostDeviceStop = AtaGenericHostDeviceStop,
//    .AtaHostDeviceWake = AtaGenericHostDeviceWake,
//    .AtaHostDeviceSleep = AtaGenericHostDeviceSleep,
//    .AtaHostDevicePowerUp = AtaGenericHostDevicePowerUp,
//    .AtaHostDevicePowerDown = AtaGenericHostDevicePowerDown,
//};

//static ATA_HOST_OPERATIONS AhciPmpRetySrStHostOperations = {
//    .AtaHostDeviceReset = AhciGenericHostReset,
//    .AtaHostDeviceStart = AtaGenericHostDeviceStart,
//    .AtaHostDeviceStop = AtaGenericHostDeviceStop,
//    .AtaHostDeviceWake = AtaGenericHostDeviceWake,
//    .AtaHostDeviceSleep = AtaGenericHostDeviceSleep,
//    .AtaHostDevicePowerUp = AtaGenericHostDevicePowerUp,
//    .AtaHostDevicePowerDown = AtaGenericHostDevicePowerDown,
//};


//ATA Module Structured Operations
UNUSED static ATA_PORT_OPERATIONS AhciGenericPortOperations{
    .AtaPortDevicePrepCommand = AhciGenericPortDevicePrepCommand,
    .AtaPortDeviceIssueCommand = AhciGenericPortDeviceIssueCommand,
    .AtaPortDeviceCleanupCommand = AhciGenericPortDeviceCleanupCommand,
    .AtaPortDeviceStart = AhciGenericPortDeviceStartPort,
    .AtaPortDeviceStop = AhciGenericPortDeviceStopPort,
//    .AtaPortDeviceWake = AtaGenericPortDeviceWake,
//    .AtaPortDeviceSleep = AtaGenericPortDeviceSleep,
//    .AtaPortDevicePowerUp = AtaGenericPortDevicePowerUp,
//    .AtaPortDevicePowerDown = AtaGenericPortDevicePowerDown,
};

UNUSED static ATA_PORT_OPERATIONS AhciVt8251Operations{
    .AtaPortDevicePrepCommand = AhciGenericPortDevicePrepCommand,
    .AtaPortDeviceIssueCommand = AhciGenericPortDeviceIssueCommand,
    .AtaPortDeviceCleanupCommand = AhciGenericPortDeviceCleanupCommand,
    .AtaPortDeviceStart = AhciGenericPortDeviceStartPort,
    .AtaPortDeviceStop = AhciGenericPortDeviceStopPort,
//    .AtaPortDeviceWake = AtaGenericPortDeviceWake,
//    .AtaPortDeviceSleep = AtaGenericPortDeviceSleep,
//    .AtaPortDevicePowerUp = AtaGenericPortDevicePowerUp,
//    .AtaPortDevicePowerDown = AtaGenericPortDevicePowerDown,
};

UNUSED static ATA_PORT_OPERATIONS AhciP5wdhOperations{
    .AtaPortDevicePrepCommand = AhciGenericPortDevicePrepCommand,
    .AtaPortDeviceIssueCommand = AhciGenericPortDeviceIssueCommand,
    .AtaPortDeviceCleanupCommand = AhciGenericPortDeviceCleanupCommand,
    .AtaPortDeviceStart = AhciGenericPortDeviceStartPort,
    .AtaPortDeviceStop = AhciGenericPortDeviceStopPort,
//    .AtaPortDeviceWake = AtaGenericPortDeviceWake,
//    .AtaPortDeviceSleep = AtaGenericPortDeviceSleep,
//    .AtaPortDevicePowerUp = AtaGenericPortDevicePowerUp,
//    .AtaPortDevicePowerDown = AtaGenericPortDevicePowerDown,
};

UNUSED static ATA_PORT_OPERATIONS AhciAvnOperations{
    .AtaPortDevicePrepCommand = AhciGenericPortDevicePrepCommand,
    .AtaPortDeviceIssueCommand = AhciGenericPortDeviceIssueCommand,
    .AtaPortDeviceCleanupCommand = AhciGenericPortDeviceCleanupCommand,
    .AtaPortDeviceStart = AhciGenericPortDeviceStartPort,
    .AtaPortDeviceStop = AhciGenericPortDeviceStopPort,
//    .AtaPortDeviceWake = AtaGenericPortDeviceWake,
//    .AtaPortDeviceSleep = AtaGenericPortDeviceSleep,
//    .AtaPortDevicePowerUp = AtaGenericPortDevicePowerUp,
//    .AtaPortDevicePowerDown = AtaGenericPortDevicePowerDown,
};


UNUSED static ATA_PORT_OPERATIONS AhciPmpRetySrStOperations{
    .AtaPortDevicePrepCommand = AhciGenericPortDevicePrepCommand,
    .AtaPortDeviceIssueCommand = AhciGenericPortDeviceIssueCommand,
    .AtaPortDeviceCleanupCommand = AhciGenericPortDeviceCleanupCommand,
//    .AtaPortDeviceStart = AtaGenericPortDeviceStartPort,
//    .AtaPortDeviceStop = AtaGenericPortDeviceStopPort,
//    .AtaPortDeviceWake = AtaGenericPortDeviceWake,
//    .AtaPortDeviceSleep = AtaGenericPortDeviceSleep,
//    .AtaPortDevicePowerUp = AtaGenericPortDevicePowerUp,
//    .AtaPortDevicePowerDown = AtaGenericPortDevicePowerDown,
};



//endof ATA Module Structured Operations

static LOUSINE_PCI_DEVICE_TABLE AhciDevices[] = {
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


LOUSTATUS AddAhciDevice(
    PDRIVER_OBJECT DriverObject,
    struct _DEVICE_OBJECT* Device
){
    LouPrint("AHCI.SYS:AddAhciDevice()\n");
    PPCI_DEVICE_OBJECT PDEV = PciHalGetPciDeviceObjectFromLdmDeviceObject(Device);

    
    
    LouPrint("AHCI.SYS:AddAhciDevice() STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS; //Status;
}
VOID AhciUnloadDriver(
    PDRIVER_OBJECT DriverObject
){
    LouPrint("AHCI.SYS:AhciUnloadDriver()\n");
    //this is a dummy function due to the module
    //being built in there is nothing to unload
    LouPrint("AHCI.SYS:AhciUnloadDriver() RETURN\n");
}

LOUAPI
LOUSTATUS 
DriverEntry(
    PDRIVER_OBJECT  DriverObject, 
    PUNICODE_STRING RegistryEntry
){
    LouPrint("AHCI.SYS:DriverEntry()\n");

    //tell the System where are key Nt driver functions are
    DriverObject->DriverUnload = AhciUnloadDriver;
    DriverObject->DriverExtension->AddDevice = AddAhciDevice;

    LOUSTATUS Status = PciHalRegisterLousinePciDeviceTable(DriverObject, AhciDevices);
    if(Status != STATUS_SUCCESS){
        LouPrint("AHCI.SYS::DriverEntry():ERROR Unable To Register Pci Device Table\n");
    }
    
    LouPrint("AHCI.SYS:DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}