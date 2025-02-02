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
LOUSTATUS AhciGenricDMAPrepCommand(
    PATA_QUEUED_COMMAND QueuedCommand
){  
    LouPrint("AhciGenricDMAPrepCommand\n");
    while(1);
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
    uint32_t Command = Port->PxCMD;
    Command |= AHCI_PxCMD_ST;
    Port->PxCMD = Command;
    Command = Port->PxCMD;
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
void AhciInitializePort(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
        
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

