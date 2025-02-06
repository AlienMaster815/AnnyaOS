#include <LouDDK.h>
#include "AhciMod.h"

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
 *
 * LICENSE:
 * This module is licensed under the GNU General Public License v2 (GPLv2).
 * You may obtain a copy of the GPLv2 at:
 * https://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 */

SECTIONED_CODE(".Ahci.Code")
PHBA_COMMAND_TABLE LouKeAhciMallocCommandTable(uint16_t TableEntries){
    if(!TableEntries){
        return 0x00;
    }

    return (PHBA_COMMAND_TABLE)LouKeMallocEx(sizeof(HBA_COMMAND_TABLE) + (TableEntries * sizeof(HBA_PRDT_ENTRY)), 128, WRITEABLE_PAGE | UNCACHEABLE_PAGE | PRESENT_PAGE);
}

SECTIONED_CODE(".Ahci.Code")
void LouKeAhciFreeCommandTable(PHBA_COMMAND_TABLE Table){
    LouKeFree((void*)Table);
}

SECTIONED_CODE(".Ahci.Code")
int8_t AhciPortGetFreeCommandSlot(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)AhciPort->PortPrivateData;
    PAHCI_GENERIC_PORT Port = PrivateData->GenericPort;
    PAHCI_GENERIC_HOST_CONTROL Ghc = PrivateData->GenericHostController;
    uint32_t CommandSlots = AHCI_GET_NCS(Ghc->Capabilities);
    uint32_t Slots = (Port->PxSACT | Port->PxCI);
 
    for(int8_t i = 0 ; i < (int8_t)(CommandSlots & 0x1F); i++){
        if(!(Slots & (1 << i))){
            return i;
        }
    }
    return -1;
}


typedef struct __attribute__((packed)) _AHCI_PRDT_ENTRY{
	uint32_t	    AddressLow;
	uint32_t        AddressHigh;
	uint32_t        Reserved;
	uint32_t		FlagsAndSize;
}AHCI_PRDT_ENTRY, * PAHCI_PRDT_ENTRY;

typedef struct __attribute__((packed)) _AHCI_COMMAND_LIST_ENTRY{
    uint16_t        Flags;
    uint16_t        PrdtLength;
    uint32_t        TotalTransfer;
    uint32_t        CommandTableBaseLow;
    uint32_t        CommandTableBaseHigh;
    uint32_t        Reserved[4];
}AHCI_COMMAND_LIST_ENTRY, * PAHCI_COMMAND_LIST_ENTRY;

#define CALCULATE_DMA_ADDRESS (DmaAddress + (i * (4 * MEGABYTE)))

SECTIONED_CODE(".Ahci.Code")
LOUSTATUS AhciGenricDMAPrepCommand(
    PATA_QUEUED_COMMAND QueuedCommand
){  
    LouPrint("AhciGenricDMAPrepCommand\n");
    UNUSED PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort = QueuedCommand->Port;
    UNUSED PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)AhciPort->PortPrivateData;

    PAHCI_GENERIC_PORT Port = PrivateData->GenericPort;
    Port->PxSERR = 0xFFFFFFFF;  // Clear all errors
    while(Port->PxSERR){
        sleep(10);
    }

    bool IsAtapi = QueuedCommand->PacketCommand;
    uint16_t CommandTableEntries;
    if(QueuedCommand->DataSize > (4 * MEGABYTE)){
        CommandTableEntries = ((QueuedCommand->DataSize / (4 * MEGABYTE))) + 1;
    }else{
        CommandTableEntries = 1;
    }
    uint64_t Crums;
    void* CommandTable = LouKeAhciMallocCommandTable(CommandTableEntries);
    uint32_t Options = (CommandTableEntries & 0x1F) | (1 << 6); 
    uint8_t Slot = AhciPortGetFreeCommandSlot(AhciPort);

    DbgPrint("Using Command Slot:%d For Command\n", Slot);

    QueuedCommandToFis(QueuedCommand, 0, 1, (uint8_t*)CommandTable);

    if(IsAtapi){
        memset((void*)((uintptr_t)CommandTable + AHCI_COMMAND_TABLE_CDB_OFFSET), 0, 32);
        memcpy((void*)((uintptr_t)CommandTable + AHCI_COMMAND_TABLE_CDB_OFFSET), QueuedCommand->ScsiCommand, QueuedCommand->ScsiCommandLength);
    }

    PAHCI_PRDT_ENTRY Prdt = (PAHCI_PRDT_ENTRY)((uintptr_t)CommandTable + AHCI_COMMAND_TABLE_HEADER_SIZE); 

    uint64_t DmaAddress;
    RequestPhysicalAddress(QueuedCommand->DataAddress ,&DmaAddress);

    if(CommandTableEntries > 1){
        Crums = QueuedCommand->DataSize % ((CommandTableEntries - 1) * (4 * MEGABYTE));
    }else {
        Crums = QueuedCommand->DataSize;
    }

    DbgPrint("Setting Up Prdt Entries\n");
    for(uint8_t i = 0; i < CommandTableEntries; i++) {
        if(i == (CommandTableEntries - 1)) {
            Prdt[i].AddressLow = CALCULATE_DMA_ADDRESS & 0xFFFFFFFF;
            Prdt[i].AddressHigh = CALCULATE_DMA_ADDRESS >> 32;
            Prdt[i].FlagsAndSize = (uint32_t)((Crums - 1) & 0x3FFFFFFF) | (1 << 31); // Ensuring correct transfer size format
            break;
        }

        Prdt[i].AddressLow = CALCULATE_DMA_ADDRESS & 0xFFFFFFFF;
        Prdt[i].AddressHigh = CALCULATE_DMA_ADDRESS >> 32;
        Prdt[i].FlagsAndSize = (4 * MEGABYTE) - 1; // AHCI expects size to be size-1
    }
    DbgPrint("Done Setting Up Prdt Entries\n");

    if(QueuedCommand->WriteCommand){
        Options |= AHCI_COMMAND_WRITE;
    }

    if(IsAtapi){
        Options |= AHCI_COMMAND_ATAPI;
    }


    PAHCI_COMMAND_LIST_ENTRY CommandList = (PAHCI_COMMAND_LIST_ENTRY)PrivateData->CommandDma;
    CommandList = &CommandList[Slot];

    RequestPhysicalAddress((uint64_t)CommandTable, &DmaAddress);

    CommandList->CommandTableBaseLow = DmaAddress & 0xFFFFFFFF;
    CommandList->CommandTableBaseHigh = DmaAddress >> 32;
    CommandList->Flags = Options;
    CommandList->TotalTransfer = QueuedCommand->DataSize;
    QueuedCommand->HardwareTag = Slot;

    //LouPrint("Dma Virtual:%h\n", (uint64_t)CommandList);
    //LouPrint("Dma Physical:%h\n", (uint64_t)DmaAddress);

    //LouPrint("Command Lsit Address Low:%h\n", CommandList->CommandTableBaseLow);
    //LouPrint("Command Lsit Address High:%h\n", CommandList->CommandTableBaseHigh);
    //LouPrint("Command Lsit Flags:%h\n", CommandList->Flags);
    //LouPrint("Command Lsit Total:%h\n", CommandList->TotalTransfer);

    //while(1);

    return STATUS_SUCCESS;  
}

SECTIONED_CODE(".Ahci.Code")
LOUSTATUS AhciGenricDMAIssueCommand(
    PATA_QUEUED_COMMAND QueuedCommand
){
    LouPrint("AhciaGenricDMAIssueCommand\n");
    PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort = QueuedCommand->Port;
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)AhciPort->PortPrivateData;     
    PAHCI_GENERIC_PORT Port = PrivateData->GenericPort;
    uint32_t Poll = 0;

    Port->PxIS = 0xFFFFFFFF;  // Clear all interrupts
    while(Port->PxIS){
        sleep(10);
    }

    while(Port->PxTFD & (0x80 | 0x08)){
        sleep(100);
    }

    Port->PxCI |= (1 << QueuedCommand->HardwareTag);

    DbgPrint("AHCI Command Issued!\n");
    
    while(Poll <= 10000){
        if(IS_INTERRUPT_TFES(Port->PxIS)){
            DbgPrint("TFES\n");
            while(1);
        }
        if(!(Port->PxCI & (1 << QueuedCommand->HardwareTag))){
            break;
        }
        sleep(100);
        Poll += 100;
    }

    if(IS_INTERRUPT_TFES(Port->PxIS)){
        DbgPrint("TFES\n");
        while(1);
    }



    
    //LouPrint("PxIS:%h\n", Port->PxIS);
    //LouPrint("PxSERR:%h\n", Port->PxSERR);

    //uint32_t* fisPtr = (uint32_t*)PrivateData->FisDma;
    //for (int i = 0; i < 8; i++) {
    //    LouPrint("FIS[%d] = %h\n", i, fisPtr[i]);
    //}
    while(1);
    return STATUS_SUCCESS;
}

SECTIONED_CODE(".Ahci.Code")
LOUSTATUS AhciGenericHardReset(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    LouPrint("AhciGenericHardReset\n");
    while(1);
    return STATUS_SUCCESS;
}

SECTIONED_CODE(".Ahci.Code")
LOUSTATUS AhciStopCommandEngine(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)LkdmAtaPortToPrivateData(AhciPort); 
    PAHCI_GENERIC_PORT Port = PrivateData->GenericPort;
    uint32_t Tmp;

    Tmp = Port->PxCMD;
    if(!(Tmp & (AHCI_PxCMD_ST | AHCI_PxCMD_CR))){
        return STATUS_SUCCESS;
    }

    if(Tmp == 0xFFFFFFFF){
        DbgPrint("AHCI LIB:Ahci Controller Not Available\n");
        return STATUS_IO_DEVICE_ERROR;
    }

    Tmp &= ~(AHCI_PxCMD_ST);
    Port->PxCMD = Tmp;
    Tmp = 0;
    while(Tmp <= 10000){
        if(Port->PxCMD & AHCI_PxCMD_CR){
            sleep(100);
            Tmp += 100;
            continue;
        }
        break;
    }
    if(Tmp >= 10000){
        return STATUS_IO_DEVICE_ERROR;
    }
    return STATUS_SUCCESS;
}

SECTIONED_CODE(".Ahci.Code")
void AhciStartCommandEngine(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)LkdmAtaPortToPrivateData(AhciPort); 
    PAHCI_GENERIC_PORT Port = PrivateData->GenericPort;
    if(Port->PxCMD & AHCI_PxCMD_CR){
        AhciStopCommandEngine(AhciPort);
    }
    while(Port->PxCMD & AHCI_PxCMD_CR){
        sleep(100);
    }
    if(!AhciPort->DeviceAttached){
        return;
    }
    uint32_t Poll = 0;
    uint32_t Command = Port->PxCMD;
    Command |= AHCI_PxCMD_ST;
    Port->PxCMD = Command;
    Command = Port->PxCMD;
    while(!(Port->PxCMD & AHCI_PxCMD_CR)){
        sleep(100);
        Poll += 100;
        if(Poll >= 1000){
            DbgPrint("Timeout Occoured Starting Command Engine\n");
            AhciStopCommandEngine(AhciPort);
            return;
        }
    }
}

SECTIONED_CODE(".Ahci.Code") 
static LOUSTATUS AhciStopFisReception(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)LkdmAtaPortToPrivateData(AhciPort);
    PAHCI_GENERIC_PORT Port = PrivateData->GenericPort;
    uint32_t Tmp = Port->PxCMD;
    Tmp &= ~(AHCI_PxCMD_FRE);
    Port->PxCMD = Tmp;

    Tmp = 0;
    while(Tmp <= 10000){
        if(Port->PxCMD & AHCI_PxCMD_FR){
            sleep(100);
            Tmp += 100;
            continue;
        }
        break;
    }    
    if(Tmp >= 10000){
        return STATUS_IO_DEVICE_ERROR;
    }
    return STATUS_SUCCESS;
}

SECTIONED_CODE(".Ahci.Code")
void AhciStartFisReception(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)AhciPort->PortPrivateData;
    PAHCI_GENERIC_PORT Port = PrivateData->GenericPort;
    PAHCI_GENERIC_HOST_CONTROL Ghc = PrivateData->GenericHostController;
    uint32_t Command;
    bool HighMem = AHCI_SUPPORTS_S64A(Ghc->Capabilities);
    uint32_t Poll = 0;
    uintptr_t CommandDmaPhy;
    uintptr_t FisDmaPhy;

    RequestPhysicalAddress(PrivateData->CommandDma, &CommandDmaPhy);
    RequestPhysicalAddress(PrivateData->FisDma, &FisDmaPhy);

    if(HighMem){
        Port->PxCLBU = (CommandDmaPhy >> 32);
    }
    Port->PxCLB = (CommandDmaPhy & 0xFFFFFFFF);

    if(HighMem){
        Port->PxFBU = (FisDmaPhy >> 32);
    }
    Port->PxFB = (FisDmaPhy & 0xFFFFFFFF);

    Command = Port->PxCMD;
    Command |= AHCI_PxCMD_FRE;
    Port->PxCMD = Command;
    //Flush Command
    Command = Port->PxCMD;
    while(!(Port->PxCMD & AHCI_PxCMD_FR)){
        sleep(100);
        Poll += 100;
        if(Poll >= 1000){
            DbgPrint("Timeout Occoured Starting Fis Reception\n");
            AhciStartFisReception(AhciPort);
            return;
        }
    }
}

SECTIONED_CODE(".Ahci.Code") 
static LOUSTATUS AhciDeInitalizePort(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    LOUSTATUS Status;
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)LkdmAtaPortToPrivateData(AhciPort);

    //Stop Command Engine
    Status = PrivateData->StopCommandEngine(AhciPort);
    if(Status != STATUS_SUCCESS){
        DbgPrint("AHCI LIB: Failed to Stop command engine\n");
        return Status;
    }

    //Stop Fis Reception
    Status = AhciStopFisReception(AhciPort);
    if(Status != STATUS_SUCCESS){
        DbgPrint("AHCI LIB:Failed to stop FIS Reception\n");
        return Status;
    }
    return STATUS_SUCCESS;
}

SECTIONED_CODE(".Ahci.Code") 
static void AhciClearPortPendingIrq(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)LkdmAtaPortToPrivateData(AhciPort);
    PAHCI_GENERIC_PORT Port = PrivateData->GenericPort;

    //Clear the SERR Register
    Port->PxSERR = Port->PxSERR;
    //Clear the Interrupt Status Register
    if(Port->PxIS){
        Port->PxIS = Port->PxIS;
    }

    Port->PxIS |= (1 << AhciPort->PortNumber);
}

SECTIONED_CODE(".Ahci.Code")
static bool AhciDetectAttachedDevice(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)AhciPort->PortPrivateData;
    PAHCI_GENERIC_PORT Port = PrivateData->GenericPort;
    //the value below is copied from OSDEV from ahci section 
    //"Dettecting Attached Sata Device's" for the SATAPI signature
    
    //PxTFD cannot be set at the time of running this
    if(Port->PxTFD & (0x80 | 0x08)){
        DbgPrint("TFD BSY AND_OR DRQ SET Port Not A Device\n");
        return false;
    }
    // (PxSTSS DET = 0x03 || (PxSTSS IPM = (0x02 || 0x06 || 0x08) is a device
    uint32_t PxSSTS = Port->PxSSTS;
    uint8_t Det = PxSSTS & 0x0F; 
    uint8_t Ipm = (PxSSTS >> 8) & 0x0F;

    if(Det != 0x03){
        LouPrint("PxSTSS DET != 0x03:%h\n", Det);
        return false;
    }

    switch(Ipm){
        case 0x08:
        case 0x06:
        case 0x02:
        case 0x01:
            break;
        default:
            LouPrint("PxSTSS IPM Invalid:%h\n",Ipm);
            return false;
    }

    AhciPort->DeviceAttached = true;

    if(Port->PxSIG == 0xEB140101){
        DbgPrint("Ahci Port Is SATAPI Device\n");
        return true;
    }
    return false;
}

SECTIONED_CODE(".Ahci.Code") 
void AhciInitializePort(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    
    //before we intitalize completly lets find if the port
    //is a packet device before we might end up creating 
    //errors
    AhciPort->PortScsiDevice = AhciDetectAttachedDevice(AhciPort);
    //TODP: safeguard 32 bit only systems
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)AhciPort->PortPrivateData;
    //PAHCI_GENERIC_HOST_CONTROL Ghc = PrivateAhciData->GenericHostController;
    PrivateData->FisDma = (uintptr_t)LouKeMalloc(256, UNCACHEABLE_PAGE | PRESENT_PAGE | WRITEABLE_PAGE);
    PrivateData->CommandDma = (uintptr_t)LouKeMalloc(1 * KILOBYTE, UNCACHEABLE_PAGE | PRESENT_PAGE | WRITEABLE_PAGE);


    LOUSTATUS Status = AhciDeInitalizePort(AhciPort);
    if(Status != STATUS_SUCCESS){
        return;
    }
    AhciClearPortPendingIrq(AhciPort);
}


SECTIONED_CODE(".Ahci.Code") 
void AhciInitializeController(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost){
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)LkdmAtaHostToPrivateData(AtaHost);
    PAHCI_GENERIC_HOST_CONTROL Ghc = PrivateData->GenericHostController;
    uint32_t TmpControl;

    ForEachAtaPort(AtaHost){
        //skip port uinitialization if the port is a dummy port
        if(!AtaHost->Ports[AtaPortIndex].Operations){
            continue;
        }

        //otherwise intilaize the port
        AhciInitializePort(&AtaHost->Ports[AtaPortIndex]);
    }

    TmpControl = Ghc->GlobalHostControl;
    TmpControl |= (1 << 1);
    Ghc->GlobalHostControl = TmpControl;
    TmpControl = Ghc->GlobalHostControl;
    if(TmpControl & (1 << 1)){
        DbgPrint("Interrupts Are Now Active On The Host Controller\r\n");
    }
    else{
        DbgPrint("Interrupts Were Unable Activate On The Host Controller\r\n");
    }
}

SECTIONED_CODE(".Ahci.Code") 
void AhciPciInitializeController(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost){

    //TODO Initialize MV PATA

    AhciInitializeController(AtaHost);
}

SECTIONED_CODE(".Ahci.Code") 
void AhciStartPort(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)AhciPort->PortPrivateData;
    PAHCI_GENERIC_PORT Port = PrivateData->GenericPort;

    DbgPrint("Ahci Port Started\n");

    if(!AhciPort->DeviceAttached){
        DbgPrint("No Device On Port Cannot Start Port\n");
        return;
    }

    //Turn On Fis Reception
    AhciStartFisReception(AhciPort);
    //Turn On Command Engine
    PrivateData->StartCommandEngine(AhciPort);

    //TODO Turn On LED's adn activate witch activity

    //Rest Device On Port
    if(AhciPort->PortScsiDevice){
        Port->PxSCTL = 0x301;
        sleep(10);
        Port->PxSCTL = 0x300;
        while (Port->PxTFD & (0x80 | 0x01)) {
            sleep(10);
        }
    }

}

SECTIONED_CODE(".Ahci.Code")
void AhciSetPortRpm(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    //TODO: were not currently at a state for power management
}

SECTIONED_CODE(".Ahci.Code") 
void AhciStopPort(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)AhciPort->PortPrivateData;
    PAHCI_GENERIC_HOST_CONTROL Ghc = PrivateData->GenericHostController;

    AhciDeInitalizePort(AhciPort);

    Ghc->InterruptStatus = (1 << AhciPort->PortNumber);
    
    AhciSetPortRpm(AhciPort);
    DbgPrint("Ahci Port Stopped\n");
}