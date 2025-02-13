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

void* LouKeMallocAhciCommandTable(uint16_t Entries){
    return LouKeMallocEx( 0x80 * ((sizeof(uint32_t) * 4) * Entries), 128, WRITEABLE_PAGE | UNCACHEABLE_PAGE | PRESENT_PAGE);
}

void LouKeFreeAhciCommandTable(void* Table){
    LouKeFree(Table);
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

SECTIONED_CODE(".Ahci.Code")
LOUSTATUS AhciGenricDMAPrepCommand(
    PATA_QUEUED_COMMAND QueuedCommand
){  
    UNUSED PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort = QueuedCommand->Port;
    UNUSED PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)AhciPort->PortPrivateData;
    UNUSED uint64_t PrdtEntries = ROUND_UP64(QueuedCommand->DataSize, 4 * MEGABYTE) / (4 * MEGABYTE);
    UNUSED void* NewCommandTable = LouKeMallocAhciCommandTable(PrdtEntries);    
    UNUSED int8_t FreeSlot = AhciPortGetFreeCommandSlot(AhciPort);
    if(FreeSlot == -1){
        return STATUS_IO_DEVICE_ERROR;
    }
    UNUSED PAHCI_COMMAND_LIST_STRUCTURE CommandHeaders = (PAHCI_COMMAND_LIST_STRUCTURE)PrivateData->CommandDma;

    QueuedCommandToFis(QueuedCommand, 0, 1, (uint8_t*)NewCommandTable, 0);
    
    if(QueuedCommand->PacketCommand){
        uint8_t PacketLength = QueuedCommand->ScsiCommandLength;
        uint8_t* ACMDp = (uint8_t*)(uintptr_t)NewCommandTable + 0x40; 
        for(uint8_t i = 0 ; i < 16; i++){
            if(i < PacketLength){
                ACMDp[i] = QueuedCommand->ScsiCommand[i];
            }else{
                ACMDp[i] = 0;
            }
        }
    }

    uint64_t DataAddress;
    RequestPhysicalAddress(QueuedCommand->DataAddress, &DataAddress);

    PAHCI_PRDT_ENTRY PrdtTable = (PAHCI_PRDT_ENTRY)(uintptr_t)NewCommandTable + 0x80; 
    for(uint8_t i = 0 ; i < (PrdtEntries - 1); i++){
        FillOutCommandTableStructure(&PrdtTable[i], DataAddress + (i) * (4 * MEGABYTE), (4 * MEGABYTE) - 1);
    }
    uint64_t Crums = QueuedCommand->DataSize;
    Crums -= (4 * MEGABYTE) * PrdtEntries;

    FillOutCommandTableStructure(&PrdtTable[PrdtEntries - 1], DataAddress + (PrdtEntries - 1) * (4 * MEGABYTE), Crums - 1);

    uint64_t CommandTableBase;
    RequestPhysicalAddress((uint64_t)NewCommandTable, &CommandTableBase);
    QueuedCommand->PrdtLocation = (uintptr_t)NewCommandTable;

    FillOutCommandListStructure(
        &CommandHeaders[FreeSlot], 
        20, 
        QueuedCommand->PacketCommand, 
        QueuedCommand->WriteCommand, 
        false,
        false,
        false,
        true,
        0,
        PrdtEntries,
        sizeof(AHCI_PRDT_ENTRY) * PrdtEntries,
        CommandTableBase
    );


    QueuedCommand->HardwareTag = FreeSlot;

    return STATUS_SUCCESS;  
}

SECTIONED_CODE(".Ahci.Code")
LOUSTATUS AhciGenricDMAIssueCommand(
    PATA_QUEUED_COMMAND QueuedCommand
){
    LouPrint("AhciaGenricDMAIssueCommand\n");



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
    LouPrint("Ahci Command Engine Started\n");
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
    LouPrint("Fis Reception Stopped\n");
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
    }else{
        Port->PxCLBU = 0;
    }

    Port->PxCLB = (CommandDmaPhy & 0xFFFFFFFF);

    if(HighMem){
        Port->PxFBU = (FisDmaPhy >> 32);
    }else{
        Port->PxFBU = 0;
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
    LouPrint("Fis Reception Started\n");
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
UNUSED static void AhciClearPortPendingIrq(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
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
            //LouPrint("IPM:%d\n", Ipm);
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
    LouPrint("AhciInitializePort()\n");
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)AhciPort->PortPrivateData;
    PAHCI_GENERIC_PORT Port = PrivateData->GenericPort;
    
    PrivateData->FisDma = (uintptr_t)LouKeMalloc(256, UNCACHEABLE_PAGE | PRESENT_PAGE | WRITEABLE_PAGE);
    PrivateData->CommandDma = (uintptr_t)LouKeMalloc(1 * KILOBYTE, UNCACHEABLE_PAGE | PRESENT_PAGE | WRITEABLE_PAGE);

    if(Port->PxCMD & (1 << 2)){
        LouPrint("Port Is Powered On\n");
    }
    if((Port->PxSCTL & 0x0F) != 3){
        sleep(10);
    }
    LouPrint("Communication Is Up\n");

    AhciDetectAttachedDevice(AhciPort);

    if(!AhciPort->DeviceAttached){
        return;
    }

    AhciStartFisReception(AhciPort);
    
    PrivateData->StartCommandEngine(AhciPort);
    
    while((Port->PxTFD & (1 << 7)) && (Port->PxTFD & (1 << 3))){
        sleep(10);
    }

    LouPrint("Port Is Now Idle\n");

}


SECTIONED_CODE(".Ahci.Code") 
void AhciInitializeController(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost){
    LouPrint("AhciInitializeController\n");
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

    if(!AhciPort->DeviceAttached){
        DbgPrint("No Device On Port Cannot Start Port\n");
        return;
    }

    //Turn On Fis Reception
    AhciStartFisReception(AhciPort);
    //Turn On Command Engine
    PrivateData->StartCommandEngine(AhciPort);

    //TODO Turn On LED's adn activate witch activity

    DbgPrint("Ahci Port Started\n");
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