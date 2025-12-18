#define _KERNEL_MODULE_
#include <LouDDK.h>
#include "AhciMod.h"

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

static BOOL AhciMessagesEnabled = true;
 
void* LouKeMallocAhciCommandTable(uint16_t Entries){
    return LouKeMallocEx( 0x80 + ((sizeof(uint32_t) * 4) * Entries), 128, WRITEABLE_PAGE | UNCACHEABLE_PAGE | PRESENT_PAGE);
}

void LouKeFreeAhciCommandTable(void* Table){
    LouKeFree(Table);
}


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

LOUSTATUS AhciGenricDMAPrepCommand(
    PATA_QUEUED_COMMAND QueuedCommand
){  
   
    return STATUS_SUCCESS;  
}

static spinlock_t AhciCommandLock;

LOUSTATUS AhciGenricDMAIssueCommand(
    PATA_QUEUED_COMMAND QueuedCommand
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&AhciCommandLock, &Irql);
    PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort = QueuedCommand->Port;
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)AhciPort->PortPrivateData;
    uint64_t PrdtEntries = ROUND_UP64(QueuedCommand->DataSize, 4 * MEGABYTE) / (4 * MEGABYTE);
    void* NewCommandTable = LouKeMallocAhciCommandTable(PrdtEntries);    
    int8_t FreeSlot = AhciPortGetFreeCommandSlot(AhciPort);
    PAHCI_GENERIC_PORT Port = PrivateData->GenericPort;
    Port->PxIS = 0xFFFFFFFF;
    Port->PxSERR = 0xFFFFFFFF;
    if(FreeSlot == -1){
        LouPrint("AHCI.SYS:AhciIssueCommand() STATUS_IO_DEVICE_ERROR\n");
        LouKeFreeAhciCommandTable(NewCommandTable);
        LouKeReleaseSpinLock(&AhciCommandLock, &Irql);
        return STATUS_IO_DEVICE_ERROR;
    }
    UNUSED PAHCI_COMMAND_LIST_STRUCTURE CommandHeaders = (PAHCI_COMMAND_LIST_STRUCTURE)PrivateData->CommandDma;

    QueuedCommandToFis(QueuedCommand, 0, 1, (uint8_t*)NewCommandTable, 0);
    
    if(QueuedCommand->PacketCommand){
        uint8_t PacketLength = QueuedCommand->ScsiCommandLength;
        uint8_t* ACMDp = (uint8_t*)(uintptr_t)NewCommandTable + 0x40; 
        memset((void*)ACMDp, 0, 16);
        memcpy((void*)ACMDp, (const void*)(uintptr_t)&QueuedCommand->ScsiCommand[0], PacketLength);
    }

    uint64_t DataAddress;
    RequestPhysicalAddress(QueuedCommand->DataAddress, &DataAddress);

    PAHCI_PRDT_ENTRY PrdtTable = (PAHCI_PRDT_ENTRY)((uint8_t*)NewCommandTable + 0x80);
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
        5, 
        QueuedCommand->PacketCommand, 
        QueuedCommand->WriteCommand, 
        false,
        false,
        false,
        false,
        0,
        PrdtEntries,
        sizeof(AHCI_PRDT_ENTRY) * PrdtEntries,
        CommandTableBase
    );

    while(Port->PxTFD & ((1 << 7 )| (1 << 3))){
        sleep(10);
    }

    Port->PxCI |= (1 << FreeSlot);

    while(1){
        if(!(Port->PxCI & (1 << FreeSlot))){
            break;
        }
        if(IS_INTERRUPT_TFES(Port->PxIS)){
            LouPrint("AHCI.SYS:AhciIssueCommand() STATUS_IO_DEVICE_ERROR\n");
            LouKeReleaseSpinLock(&AhciCommandLock, &Irql);
            LouKeFreeAhciCommandTable(NewCommandTable);
            return STATUS_IO_DEVICE_ERROR;
        }
    }
    LouKeFreeAhciCommandTable(NewCommandTable);
    LouKeReleaseSpinLock(&AhciCommandLock, &Irql);
    return STATUS_SUCCESS;
}

LOUSTATUS AhciGenericHardReset(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    LouPrint("AHCI.SYS:AhciGenericHardReset\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS AhciStopCommandEngine(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)LkdmAtaPortToPrivateData(AhciPort); 
    PAHCI_GENERIC_PORT Port = PrivateData->GenericPort;
    uint32_t Tmp;

    Tmp = Port->PxCMD;
    if(!(Tmp & (AHCI_PxCMD_ST | AHCI_PxCMD_CR))){
        return STATUS_SUCCESS;
    }

    if(Tmp == 0xFFFFFFFF){
        LouPrint("AHCI.SYS:Ahci Controller Not Available\n");
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
        LouPrint("AHCI.SYS:Ahci Controller Command Engine Timeout Occoured\n");
        return STATUS_IO_DEVICE_ERROR;
    }
    LouPrint("AHCI.SYS:Ahci Controller Command Engine Stopped\n");
    return STATUS_SUCCESS;
}

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
            LouPrint("AHCI.SYS:Timeout Occoured Starting Command Engine\n");
            AhciStopCommandEngine(AhciPort);
            return;
        }
    }
    LouPrint("AHCI.SYS:Ahci Command Engine Started\n");
}

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
    LouPrint("AHCI.SYS:Fis Reception Stopped\n");
    return STATUS_SUCCESS;
}

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
            LouPrint("AHCI.SYS:Timeout Occoured Starting Fis Reception\n");
            AhciStartFisReception(AhciPort);
            return;
        }
    }
    LouPrint("AHCI.SYS:Fis Reception Started\n");
}

static LOUSTATUS AhciDeInitalizePort(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    LOUSTATUS Status;
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)LkdmAtaPortToPrivateData(AhciPort);

    //Stop Command Engine
    Status = PrivateData->StopCommandEngine(AhciPort);
    if(Status != STATUS_SUCCESS){
        LouPrint("AHCI.SYS:Failed to Stop command engine\n");
        return Status;
    }

    //Stop Fis Reception
    Status = AhciStopFisReception(AhciPort);
    if(Status != STATUS_SUCCESS){
        LouPrint("AHCI.SYS:Failed to stop FIS Reception\n");
        return Status;
    }
    return STATUS_SUCCESS;
}

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

static bool AhciDetectAttachedDevice(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)AhciPort->PortPrivateData;
    volatile PAHCI_GENERIC_PORT Port = PrivateData->GenericPort;
    //the value below is copied from OSDEV from ahci section 
    //"Dettecting Attached Sata Device's" for the SATAPI signature
    AhciPort->DeviceAttached = false;
    
    //PxTFD cannot be set at the time of running this
    if(Port->PxTFD & (0x80 | 0x08)){
        LouPrint("AHCI.SYS:TFD BSY AND_OR DRQ SET Port Not A Device\n");
        return false;
    }
    // (PxSTSS DET = 0x03 || (PxSTSS IPM = (0x02 || 0x06 || 0x08) is a device
    uint32_t PxSSTS = Port->PxSSTS;
    uint8_t Det = PxSSTS & 0x0F; 
    uint8_t Ipm = (PxSSTS >> 8) & 0x0F;


    if(Det != 0x03){
        LouPrint("AHCI.SYS:PxSTSS DET != 0x03:%h\n", Det);
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
            LouPrint("AHCI.SYS:PxSTSS IPM Invalid:%h\n",Ipm);
            return false;
    }

    AhciPort->DeviceAttached = true;

    if(Port->PxSIG == 0xEB140101){
        LouPrint("AHCI.SYS:Ahci Port Is SATAPI Device\n");
        return true;
    }
    return false;
}


void AhciInitializePort(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    LouPrint("AHCI.SYS:AhciInitializePort()\n");
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)AhciPort->PortPrivateData;
    volatile PAHCI_GENERIC_PORT Port = PrivateData->GenericPort;
    
    AhciPort->PortScsiDevice = AhciDetectAttachedDevice(AhciPort);
    if(!AhciPort->DeviceAttached){
        return;
    }

    if(PrivateData->DmaBits == 64){
        PrivateData->CommandDma = (uintptr_t)LouKeMalloc(1 * KILOBYTE, UNCACHEABLE_PAGE | PRESENT_PAGE | WRITEABLE_PAGE);
        PrivateData->FisDma = (uintptr_t)LouKeMalloc(256, UNCACHEABLE_PAGE | PRESENT_PAGE | WRITEABLE_PAGE);
    }else{
        PrivateData->CommandDma = (uintptr_t)LouKeMallocPhy32(1 * KILOBYTE, UNCACHEABLE_PAGE | PRESENT_PAGE | WRITEABLE_PAGE);
        PrivateData->FisDma = (uintptr_t)LouKeMallocPhy32(256, UNCACHEABLE_PAGE | PRESENT_PAGE | WRITEABLE_PAGE);
    }


    if(Port->PxCMD & (1 << 2)){
        LouPrint("AHCI.SYS:Port Is Powered On\n");
    }
    if((Port->PxSCTL & 0x0F) != 3){
        sleep(10);
    }
    LouPrint("AHCI.SYS:Communication Is Up\n");

    AhciStartFisReception(AhciPort);

    LouPrint("AHCI.SYS:PrivateData->StartCommandEngine:%h\n", PrivateData->StartCommandEngine);

    PrivateData->StartCommandEngine(AhciPort);

    while((Port->PxTFD & (1 << 7)) && (Port->PxTFD & (1 << 3))){
        sleep(10);
    }
    
    AhciPort->DmaPort = true;
    AhciPort->SerialDevice = true;
}


void AhciInitializeController(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost){
    LouPrint("AHCI.SYS:AhciInitializeController\n");
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
        LouPrint("Interrupts Are Now Active On The Host Controller\n");
    }
    else{
        LouPrint("Interrupts Were Unable Activate On The Host Controller\n");
    }
}

void AhciPciInitializeController(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost){
    PAHCI_DRIVER_PRIVATE_DATA AhciPrivate = (PAHCI_DRIVER_PRIVATE_DATA)AtaHost->HostPrivateData;
    PPCI_DEVICE_OBJECT PDEV = AhciPrivate->PDEV;
    PPCI_COMMON_CONFIG CommonConfig = (PPCI_COMMON_CONFIG)PDEV->CommonConfig;
    UINT32 Tmp;
    UINT8 Mv;

    if(AhciPrivate->AhciFlags & AHCI_FLAG_MV_PATA){
        if(CommonConfig->Header.DeviceID == 0x6121){
            Mv = 2;
        }else{
            Mv = 4;
        }

        if(AtaHost->PortCount > Mv){
            PAHCI_DRIVER_PRIVATE_DATA MvPort = (PAHCI_DRIVER_PRIVATE_DATA)AtaHost->Ports[Mv].PortPrivateData;
            MvPort->GenericPort->PxIE = 0;
            Tmp = MvPort->GenericPort->PxIS;
            if(Tmp){
                MvPort->GenericPort->PxIS = Tmp;
            }
        }
    }
    AhciInitializeController(AtaHost);
}

void AhciStartPort(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)AhciPort->PortPrivateData;

    if(!AhciPort->DeviceAttached){
        LouPrint("AHCI.SYS:No Device On Port Cannot Start Port\n");
        return;
    }

    //Turn On Fis Reception
    AhciStartFisReception(AhciPort);
    //Turn On Command Engine
    PrivateData->StartCommandEngine(AhciPort);

    //TODO Turn On LED's adn activate witch activity

    LouPrint("AHCI.SYS:Ahci Port Started\n");
}

void AhciSetPortRpm(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    //TODO: were not currently at a state for power management
}

void AhciStopPort(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)AhciPort->PortPrivateData;
    PAHCI_GENERIC_HOST_CONTROL Ghc = PrivateData->GenericHostController;

    AhciDeInitalizePort(AhciPort);

    Ghc->InterruptStatus = (1 << AhciPort->PortNumber);
    
    AhciSetPortRpm(AhciPort);
    LouPrint("AHCI.SYS:Ahci Port Stopped\n");
}

void QueuedCommandToFis(PATA_QUEUED_COMMAND QueuedCommand, uint8_t PortMultiplier, uint8_t IsCommand, uint8_t* Fis, uint8_t IsNcq) {
    Fis[0] = 0x27;  // Host-to-Device Register FIS
    Fis[1] = PortMultiplier & 0x0F;
    if (IsCommand) {
        Fis[1] |= (1 << 7);
    }
    Fis[2] = QueuedCommand->Command;
    Fis[3] = QueuedCommand->Feature;
    Fis[4] = QueuedCommand->Lbal;
    Fis[5] = QueuedCommand->Lbam;
    Fis[6] = QueuedCommand->Lbah;
    Fis[7] = QueuedCommand->Device;
    Fis[8] = QueuedCommand->HobLbal;
    Fis[9] = QueuedCommand->HobLbam;
    Fis[10] = QueuedCommand->HobLbah;
    Fis[11] = QueuedCommand->HobFeature;
    Fis[12] = QueuedCommand->SectorCount;
    Fis[13] = QueuedCommand->HobSectorCount;
    if(IsNcq){
        Fis[13] |= (1 << 3);
    }
    Fis[14] = 0;
    Fis[15] = QueuedCommand->Control;
    Fis[16] = QueuedCommand->Auxillery & 0xFF;
    Fis[17] = (QueuedCommand->Auxillery >> 8) & 0xFF;
    Fis[18] = (QueuedCommand->Auxillery >> 16) & 0xFF;
    Fis[19] = (QueuedCommand->Auxillery >> 24) & 0xFF;
}

void AhciSetEmMessages(
    PAHCI_DRIVER_PRIVATE_DATA HostPrivate
){
    UINT8 Messages;
    PAHCI_GENERIC_HOST_CONTROL Ghc = HostPrivate->GenericHostController;
    UINT32 EmLocation = Ghc->EmLocation;
    UINT32 EmControl = Ghc->EmControl;

    if((!AhciMessagesEnabled) || (!(AHCI_SUPPORTS_EMS(Ghc->Capabilities)))){
        LouPrint("AHCI.SYS:AhciSetEmMessages() EM Not Supported\n");
        return;
    }

    Messages = ((EmControl & EM_CONTROL_MESSAGE_TYPE) >> 16);

    if(Messages){
        HostPrivate->EmLocation = EmLocation;
        HostPrivate->EmBufferSize = ((EmLocation & 0xFF) * 4);
        HostPrivate->EmMessageType = Messages;
        HostPrivate->AtaFlags |= ATA_FLAG_EM;
        if(!(EmControl & EM_CONTROL_ALHD)){
            HostPrivate->AtaFlags |= ATA_FLAG_SW_ACTIVITY;
        }
    }else{
        LouPrint("AHCI.SYS:AhciSetEmMessages() EM Not Supported\n");
    }

}

LOUSTATUS  
AhciResetEm(
    PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost
){
    PAHCI_DRIVER_PRIVATE_DATA PrivateData = (PAHCI_DRIVER_PRIVATE_DATA)AtaHost->HostPrivateData;
    UNUSED PAHCI_GENERIC_HOST_CONTROL Ghc = PrivateData->GenericHostController;
    UINT32 EmControl = Ghc->EmControl;
    if((EmControl & EM_CONTROL_TM) || (EmControl & EM_CONTROL_RST)){
        LouPrint("AHCI.SYS:AhciResetEm() STATUS_INVALID_PARAMETER\n");
        return STATUS_INVALID_PARAMETER;
    }
    Ghc->EmControl = (EmControl | EM_CONTROL_RST);
    return STATUS_SUCCESS;
}