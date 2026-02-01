#include "PIIX.h"

//According to specification we can wait the 400ns byt reaing AS 4 times
static inline void AtaIoWait400ns(uint16_t ControlPort){
    CONTROL_READ_ALTERNATE_STATUS_PORT;
    CONTROL_READ_ALTERNATE_STATUS_PORT;
    CONTROL_READ_ALTERNATE_STATUS_PORT;
    CONTROL_READ_ALTERNATE_STATUS_PORT;
}


static void PiixSetPrimaryMasterPioTiming(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost, UINT8 Mode){
    UINT8 MaxPio = ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[0].PortPrivateData)->MaxPioMode;
    PPCI_DEVICE_OBJECT PDEV = AtaHost->PDEV;
    Mode = MIN(Mode, MaxPio);
    UINT16 Time;

    Time = LouKeReadPciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET);
        
    Time |= (IDETIM_IDE | IDETIM_IE0 | IDETIM_IE1 | IDETIM_SITRE);
    
    LouKeWritePciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET, Time);
    
    Time = LouKeReadPciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET);

    if(Mode == 4){
        Time &= ~(IDETIM_ISP | IDETIM_RTC);
        Time |= (IDETIM_ISP_2CLOCK | IDETIM_RTC_1CLOCK);
        LouKeWritePciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[0].PortPrivateData)->CurrentPioMode = 4;
    }else if(Mode == 3){
        Time &= ~(IDETIM_ISP | IDETIM_RTC);
        Time |= (IDETIM_ISP_3CLOCK | IDETIM_RTC_2CLOCK);
        LouKeWritePciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[0].PortPrivateData)->CurrentPioMode = 3;
    }else if(Mode == 2){
        Time &= ~(IDETIM_ISP | IDETIM_RTC);
        Time |= (IDETIM_ISP_4CLOCK | IDETIM_RTC_3CLOCK);
        LouKeWritePciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[0].PortPrivateData)->CurrentPioMode = 3;
    }else if(Mode == 1){
        Time &= ~(IDETIM_ISP | IDETIM_RTC);
        Time |= (IDETIM_ISP_5CLOCK | IDETIM_RTC_4CLOCK);
        LouKeWritePciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[0].PortPrivateData)->CurrentPioMode = 3;
    }else {
        LouPrint("PIIX.SYS:WARNING Piix Clocks Could Not Be Set\n");
    }

}

static void PiixSetPrimarySlavePioTiming(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost, UINT8 Mode){
    UINT8 MaxPio = ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[1].PortPrivateData)->MaxPioMode;
    PPCI_DEVICE_OBJECT PDEV = AtaHost->PDEV;
    Mode = MIN(Mode, MaxPio);
    UINT16 Time;

    Time = LouKeReadPciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET);
        
    Time |= (IDETIM_IDE | IDETIM_IE0 | IDETIM_IE1 | IDETIM_SITRE);
    
    LouKeWritePciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET, Time);
    
    Time = LouKeReadPciUint16(PDEV, SIDETIM_REGISTER_OFFSET);

    if(Mode == 4){
        Time &= ~(SIDTIM_PISP1 | SIDTIM_PRTC1);
        Time |= (SIDTIM_PISP1_2CLOCK | SIDTIM_PRTC1_1CLOCK);
        LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[1].PortPrivateData)->CurrentPioMode = 4;
    }else if(Mode == 3){
        Time &= ~(SIDTIM_PISP1 | SIDTIM_PRTC1);
        Time |= (SIDTIM_PISP1_3CLOCK | SIDTIM_PRTC1_2CLOCK);
        LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[1].PortPrivateData)->CurrentPioMode = 3;
    }else if(Mode == 2){
        Time &= ~(SIDTIM_PISP1 | SIDTIM_PRTC1);
        Time |= (SIDTIM_PISP1_4CLOCK | SIDTIM_PRTC1_3CLOCK);
        LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[1].PortPrivateData)->CurrentPioMode = 3;
    }else if(Mode == 1){
        Time &= ~(SIDTIM_PISP1 | SIDTIM_PRTC1);
        Time |= (SIDTIM_PISP1_5CLOCK | SIDTIM_PRTC1_4CLOCK);
        LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[1].PortPrivateData)->CurrentPioMode = 3;
    }else {
        LouPrint("PIIX.SYS:WARNING Piix Clocks Could Not Be Set\n");
    }

}

static void PiixSetSecondaryMasterPioTiming(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost, UINT8 Mode){
    UINT8 MaxPio = ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[2].PortPrivateData)->MaxPioMode;
    PPCI_DEVICE_OBJECT PDEV = AtaHost->PDEV;
    Mode = MIN(Mode, MaxPio);
    UINT16 Time;

    Time = LouKeReadPciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET);
        
    Time |= (IDETIM_IDE | IDETIM_IE0 | IDETIM_IE1 | IDETIM_SITRE | IDETIM_TIME0);
    
    LouKeWritePciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET, Time);
    
    Time = LouKeReadPciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET);

    if(Mode == 4){
        Time &= ~(IDETIM_ISP | IDETIM_RTC);
        Time |= (IDETIM_ISP_2CLOCK | IDETIM_RTC_1CLOCK);
        LouKeWritePciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[2].PortPrivateData)->CurrentPioMode = 4;
    }else if(Mode == 3){
        Time &= ~(IDETIM_ISP | IDETIM_RTC);
        Time |= (IDETIM_ISP_3CLOCK | IDETIM_RTC_2CLOCK);
        LouKeWritePciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[2].PortPrivateData)->CurrentPioMode = 3;
    }else if(Mode == 2){
        Time &= ~(IDETIM_ISP | IDETIM_RTC);
        Time |= (IDETIM_ISP_4CLOCK | IDETIM_RTC_3CLOCK);
        LouKeWritePciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[2].PortPrivateData)->CurrentPioMode = 3;
    }else if(Mode == 1){
        Time &= ~(IDETIM_ISP | IDETIM_RTC);
        Time |= (IDETIM_ISP_5CLOCK | IDETIM_RTC_4CLOCK);
        LouKeWritePciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[2].PortPrivateData)->CurrentPioMode = 3;
    }else {
        LouPrint("PIIX.SYS:WARNING Piix Clocks Could Not Be Set\n");
    }

}

static void PiixSetSecondarySlavePioTiming(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost, UINT8 Mode){
    UINT8 MaxPio = ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[1].PortPrivateData)->MaxPioMode;
    PPCI_DEVICE_OBJECT PDEV = AtaHost->PDEV;
    Mode = MIN(Mode, MaxPio);
    UINT16 Time;

    Time = LouKeReadPciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET);
        
    Time |= (IDETIM_IDE | IDETIM_IE0 | IDETIM_IE1 | IDETIM_SITRE);
    
    LouKeWritePciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET, Time);
    
    Time = LouKeReadPciUint16(PDEV, SIDETIM_REGISTER_OFFSET);

    if(Mode == 4){
        Time &= ~(SIDTIM_SISP1 | SIDTIM_SRTC1);
        Time |= (SIDTIM_SISP1_2CLOCK | SIDTIM_SRTC1_1CLOCK);
        LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[1].PortPrivateData)->CurrentPioMode = 4;
    }else if(Mode == 3){
        Time &= ~(SIDTIM_SISP1 | SIDTIM_SRTC1);
        Time |= (SIDTIM_SISP1_3CLOCK | SIDTIM_SRTC1_2CLOCK);
        LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[1].PortPrivateData)->CurrentPioMode = 3;
    }else if(Mode == 2){
        Time &= ~(SIDTIM_SISP1 | SIDTIM_SRTC1);
        Time |= (SIDTIM_SISP1_4CLOCK | SIDTIM_SRTC1_3CLOCK);
        LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[1].PortPrivateData)->CurrentPioMode = 3;
    }else if(Mode == 1){
        Time &= ~(SIDTIM_SISP1 | SIDTIM_SRTC1);
        Time |= (SIDTIM_SISP1_5CLOCK | SIDTIM_SRTC1_4CLOCK);
        LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[1].PortPrivateData)->CurrentPioMode = 3;
    }else {
        LouPrint("PIIX.SYS:WARNING Piix Clocks Could Not Be Set\n");
    }

}

static PVOID Piix3BuildPrdt(PVOID* BufferVirtual, SIZE Size){

    UINT64 Tables = (ROUND_UP64(Size, (64 * KILOBYTE)) / (64 * KILOBYTE)); 
    PPIIX3_DMA_PRD NewTable = (PPIIX3_DMA_PRD)LouKeMallocExPhy32(Tables * sizeof(PIIX3_DMA_PRD), 16, KERNEL_DMA_MEMORY);    
    *BufferVirtual = LouKeMallocExPhy32(Size, 16, KERNEL_DMA_MEMORY);
    UINT64 PhyAddress = 0;
    size_t i = 0;
    for(; i < (Tables - 1); i++){
        RequestPhysicalAddress((UINT64)*BufferVirtual + (i * (64 * KILOBYTE)), &PhyAddress);
        if(PhyAddress > UINT32_MAX){
            LouPrint("PIIX.SYS:Physical Address Invalid\n");
            while(1);
        }
        NewTable[i].PhyAddress = PhyAddress;
        NewTable[i].ByteCount = 0;
        NewTable[i].Flags = 0; 
    }

    RequestPhysicalAddress((UINT64)*BufferVirtual + (i * (64 * KILOBYTE)), &PhyAddress);
    if(PhyAddress > UINT32_MAX){
        LouPrint("PIIX.SYS:Physical Address Invalid\n");
        while(1);
    }

    NewTable[i].PhyAddress = PhyAddress;
    if((Size - (i * (64 * KILOBYTE))) == (64 * KILOBYTE)){
        NewTable[i].ByteCount = 0; 
    }else {
        NewTable[i].ByteCount = (Size - (i * (64 * KILOBYTE))) - 1; 
    }

    NewTable[i].Flags = PIIX3_PRD_FLAG_EOT; 

    return (PVOID)NewTable;
}

LOUSTATUS Piix3DmaIssueCommand(
    PATA_QUEUED_COMMAND QueuedCommand
){
    if(QueuedCommand->DataSize > 0xFFFF){
        LouPrint("PIIX.SYS:ERROR Buffer Too Big\n");
        return STATUS_IO_DEVICE_ERROR;
    }
    UNUSED PLOUSINE_KERNEL_DEVICE_ATA_PORT PiixPort = QueuedCommand->Port;
    UNUSED PPIIX3_HOST_PRIVATE_DATA PiixPrivate = (PPIIX3_HOST_PRIVATE_DATA)PiixPort->AtaHost->HostPrivateData;
    UNUSED BOOL PrimaryChannel = false;
    UNUSED UINT16 BmiCommand;
    UNUSED UINT16 BmiStatus;
    UNUSED UINT8 CommandValue;
    UNUSED UINT8 StatusValue;
    UNUSED UINT32 PrdtRegister; 
    UNUSED UINT64 PrdtPhy;
    UNUSED uint32_t PollCount = 0;
    UNUSED uint16_t CommandPort = (uint16_t)(uintptr_t)PiixPort->CommandIoAddress;
    UNUSED uint16_t ControlPort = (uint16_t)(uintptr_t)PiixPort->ControlIoAddress;
    UNUSED uint8_t Status;
    
    if(PiixPort->PortNumber < 3){
        PrimaryChannel = true;
    }
    PVOID DmaOutBuffer = 0x00;
    PVOID Prdt = Piix3BuildPrdt(&DmaOutBuffer, QueuedCommand->DataSize);

    if(PrimaryChannel){
        MutexLock(&PiixPrivate->PrimaryDmaLock);

        BmiCommand = PRIMARY_BMICOM_REGISTER(PiixPrivate);
        BmiStatus = PRIMARY_BMISTA_REGISTER(PiixPrivate);
        PrdtRegister = PRIMARY_BMIDTP_REGISTER(PiixPrivate);

        CommandValue = inb(BmiCommand);
        StatusValue = inb(BmiStatus);

        RequestPhysicalAddress((UINT64)Prdt, &PrdtPhy);
        if(PrdtPhy > UINT32_MAX){
            LouPrint("PIIX.SYS:Error Invalid Memory\n");
            while(1);
        }
        CommandValue = inb(BmiCommand);
        CommandValue |= (BMICOM_RWCON);
        StatusValue = BMISTA_IDEINTR | BMISTA_DMAERR;
        outb(BmiCommand, CommandValue);
        outb(BmiStatus, StatusValue);
        outl(PrdtRegister, (UINT32)PrdtPhy);

        if(QueuedCommand->WriteCommand){


        }else{
            if(PiixPort->PortNumber == 1){
                COMMAND_WRITE_DRIVE_HEAD_PORT(0xA0);
            }else{
                COMMAND_WRITE_DRIVE_HEAD_PORT(0xB0);
            }
            //wait for the controllers Selector IC
            AtaIoWait400ns(ControlPort);
            //Fill the Command Data
            if(PiixPort->PortScsiDevice){
                COMMAND_WRITE_FEATURE_PORT_LBA28(1);
                COMMAND_WRITE_LBAM_PORT_LBA28(QueuedCommand->DataSize & 0xFF);
                COMMAND_WRITE_LBAH_PORT_LBA28(QueuedCommand->DataSize >> 8);
            }else{
                COMMAND_WRITE_FEATURE_PORT_LBA28(1);
                COMMAND_WRITE_SECTOR_COUNT_PORT_LBA28(QueuedCommand->SectorCount);

                COMMAND_WRITE_LBAL_PORT_LBA28(QueuedCommand->Lbal);
                COMMAND_WRITE_LBAM_PORT_LBA28(QueuedCommand->Lbam);
                COMMAND_WRITE_LBAH_PORT_LBA28(QueuedCommand->Lbah);
            }
            //Send Command
            COMMAND_WRITE_COMMAND_PORT(QueuedCommand->Command);

            AtaIoWait400ns(ControlPort);
            //LouPrint("Waiting On Device\n");
            Status = COMMAND_READ_STATUS_PORT;
            while(PiixPort->PollTimer >= PollCount){
                if((((!(Status & 0x80)) && (Status & 0x08)) || (Status & 0x01))){
                    break;
                }
                Status = COMMAND_READ_STATUS_PORT;
                sleep(100);
                PollCount += 100;
            }
            if(PollCount >= PiixPort->PollTimer){
                LouPrint("PIIX.SYS:Error Timeout Occoured\n");
                return STATUS_TIMEOUT;
            }
            if(Status & 0x01){
                LouPrint("PIIX.SYS:Device Error\n");
                return STATUS_IO_DEVICE_ERROR;
            }

            if(PiixPort->PortScsiDevice){
                //Reset Poll For the next Poll
                COMMAND_WRITE_DATA_PORT_BUFFER((uint8_t*)&QueuedCommand->ScsiCommand[0], 6);
                Status = COMMAND_READ_STATUS_PORT;
                while(PiixPort->PollTimer >= PollCount){
                    if((((!(Status & 0x80)) && (Status & 0x08)) || (Status & 0x01))){
                        break;
                    }
                    Status = COMMAND_READ_STATUS_PORT;
                    sleep(100);
                    PollCount += 100;
                }
                if(PollCount >= PiixPort->PollTimer){
                    LouPrint("PIIX.SYS:Error Timeout Occoured\n");
                    return STATUS_TIMEOUT;
                }
                if(Status & 0x01){
                    LouPrint("PIIX.SYS:Device Error\n");
                    return STATUS_IO_DEVICE_ERROR;
                }
    
            }
    
            outb(BmiCommand, CommandValue | BMICOM_SSBM);

            LouKeWaitForEvent(&PiixPrivate->PrimaryEvent);

            memcpy((PVOID)QueuedCommand->DataAddress, (PVOID)DmaOutBuffer, (SIZE)QueuedCommand->DataSize);    

            LouKeFreePhy32(Prdt);
            LouKeFreePhy32(DmaOutBuffer);

            MutexUnlock(&PiixPrivate->PrimaryDmaLock);
            return STATUS_SUCCESS;
        }
        
    }else{

        MutexLock(&PiixPrivate->SecondaryDmaLock);

        BmiCommand = SECONDARY_BMICOM_REGISTER(PiixPrivate);
        BmiStatus = SECONDARY_BMISTA_REGISTER(PiixPrivate);
        PrdtRegister = SECONDARY_BMIDTP_REGISTER(PiixPrivate);

        CommandValue = inb(BmiCommand);
        StatusValue = inb(BmiStatus);

        RequestPhysicalAddress((UINT64)Prdt, &PrdtPhy);
        if(PrdtPhy > UINT32_MAX){
            LouPrint("PIIX.SYS:Error Invalid Memory\n");
            while(1);
        }
        CommandValue = inb(BmiCommand);
        CommandValue |= (BMICOM_RWCON);
        StatusValue = BMISTA_IDEINTR | BMISTA_DMAERR;
        outb(BmiCommand, CommandValue);
        outb(BmiStatus, StatusValue);
        outl(PrdtRegister, (UINT32)PrdtPhy);

        if(QueuedCommand->WriteCommand){


        }else{
            if(PiixPort->PortNumber == 3){
                COMMAND_WRITE_DRIVE_HEAD_PORT(0xA0);
            }else{
                COMMAND_WRITE_DRIVE_HEAD_PORT(0xB0);
            }
            //wait for the controllers Selector IC
            AtaIoWait400ns(ControlPort);
            //Fill the Command Data
            if(PiixPort->PortScsiDevice){
                COMMAND_WRITE_FEATURE_PORT_LBA28(1);
                COMMAND_WRITE_LBAM_PORT_LBA28(QueuedCommand->DataSize & 0xFF);
                COMMAND_WRITE_LBAH_PORT_LBA28(QueuedCommand->DataSize >> 8);
            }else{
                COMMAND_WRITE_FEATURE_PORT_LBA28(1);
                COMMAND_WRITE_SECTOR_COUNT_PORT_LBA28(QueuedCommand->SectorCount);

                COMMAND_WRITE_LBAL_PORT_LBA28(QueuedCommand->Lbal);
                COMMAND_WRITE_LBAM_PORT_LBA28(QueuedCommand->Lbam);
                COMMAND_WRITE_LBAH_PORT_LBA28(QueuedCommand->Lbah);
            }
            //Send Command
            COMMAND_WRITE_COMMAND_PORT(QueuedCommand->Command);

            AtaIoWait400ns(ControlPort);
            //LouPrint("Waiting On Device\n");
            Status = COMMAND_READ_STATUS_PORT;
            while(PiixPort->PollTimer >= PollCount){
                if((((!(Status & 0x80)) && (Status & 0x08)) || (Status & 0x01))){
                    break;
                }
                Status = COMMAND_READ_STATUS_PORT;
                sleep(100);
                PollCount += 100;
            }
            if(PollCount >= PiixPort->PollTimer){
                LouPrint("PIIX.SYS:Error Timeout Occoured\n");
                return STATUS_TIMEOUT;
            }
            if(Status & 0x01){
                LouPrint("PIIX.SYS:Device Error\n");
                return STATUS_IO_DEVICE_ERROR;
            }

            if(PiixPort->PortScsiDevice){
                //Reset Poll For the next Poll
                COMMAND_WRITE_DATA_PORT_BUFFER((uint8_t*)&QueuedCommand->ScsiCommand[0], 6);
                Status = COMMAND_READ_STATUS_PORT;
                while(PiixPort->PollTimer >= PollCount){
                    if((((!(Status & 0x80)) && (Status & 0x08)) || (Status & 0x01))){
                        break;
                    }
                    Status = COMMAND_READ_STATUS_PORT;
                    sleep(100);
                    PollCount += 100;
                }
                if(PollCount >= PiixPort->PollTimer){
                    LouPrint("PIIX.SYS:Error Timeout Occoured\n");
                    return STATUS_TIMEOUT;
                }
                if(Status & 0x01){
                    LouPrint("PIIX.SYS:Device Error\n");
                    return STATUS_IO_DEVICE_ERROR;
                }
    
            }
    
            outb(BmiCommand, CommandValue | BMICOM_SSBM);

            LouKeWaitForEvent(&PiixPrivate->SecondaryEvent);

            memcpy((PVOID)QueuedCommand->DataAddress, (PVOID)DmaOutBuffer, (SIZE)QueuedCommand->DataSize);    

            LouKeFreePhy32(Prdt);
            LouKeFreePhy32(DmaOutBuffer);

            MutexUnlock(&PiixPrivate->SecondaryDmaLock);
            return STATUS_SUCCESS;
        }
    }
    LouPrint("Piix3DmaIssueCommand() STATUS_INVALID_PARAMETER\n");
    while(1);
    return STATUS_INVALID_PARAMETER;
}

void Piix3PrimaryInterruptHandler(UINT64 Data){
    PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost = (PLOUSINE_KERNEL_DEVICE_ATA_HOST)Data;
    PPIIX3_HOST_PRIVATE_DATA PiixPrivate = (PPIIX3_HOST_PRIVATE_DATA)AtaHost->HostPrivateData;
    UNUSED UINT16 BmiCommand;
    UINT16 BmiStatus;
    UINT8 StatusValue; 
    UINT8 CommandValue;

    BmiCommand = PRIMARY_BMICOM_REGISTER(PiixPrivate);
    BmiStatus = PRIMARY_BMISTA_REGISTER(PiixPrivate);

    StatusValue = inb(BmiStatus);
    if(!(StatusValue & BMISTA_IDEINTR)){
        return;
    }

    if(StatusValue & BMISTA_DMAERR){
        LouPrint("PIIX.SYS:DMAERR\n");
    }

    CommandValue &= ~(BMICOM_SSBM);
    outb(BmiCommand, CommandValue);
    LouKeSignalEvent(&PiixPrivate->PrimaryEvent);
}

void Piix3SecondaryInterruptHandler(UINT64 Data){
    PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost = (PLOUSINE_KERNEL_DEVICE_ATA_HOST)Data;
    PPIIX3_HOST_PRIVATE_DATA PiixPrivate = (PPIIX3_HOST_PRIVATE_DATA)AtaHost->HostPrivateData;
    UNUSED UINT16 BmiCommand;
    UINT16 BmiStatus;
    UINT8 StatusValue; 
    UINT8 CommandValue;

    BmiCommand = SECONDARY_BMICOM_REGISTER(PiixPrivate);
    BmiStatus = SECONDARY_BMISTA_REGISTER(PiixPrivate);

    StatusValue = inb(BmiStatus);
    if(!(StatusValue & BMISTA_IDEINTR)){
        return;
    }

    if(StatusValue & BMISTA_DMAERR){
        LouPrint("PIIX.SYS:DMAERR\n");
    }

    CommandValue &= ~(BMICOM_SSBM);
    outb(BmiCommand, CommandValue);
    LouKeSignalEvent(&PiixPrivate->SecondaryEvent);
}


LOUSTATUS PiixInitializePiix3Xceleration(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost){
    LOUSTATUS Status;
    UINT16  Tmp;
    UINT8   MaxPio;
    UINT8   MaxUDma;
    PPCI_DEVICE_OBJECT PDEV = AtaHost->PDEV;
    BOOL Channel1Used;
    BOOL Channel2Used;
    LouKeMallocAtaPrivateData(AtaHost, sizeof(PIIX3_HOST_PRIVATE_DATA), GET_ALIGNMENT(PIIX3_HOST_PRIVATE_DATA));
    PPIIX3_HOST_PRIVATE_DATA PiixPrivateData = (PPIIX3_HOST_PRIVATE_DATA)AtaHost->HostPrivateData;

    LouKeInitializeEventTimeOut(&PiixPrivateData->PrimaryEvent, 10000);
    LouKeInitializeEventTimeOut(&PiixPrivateData->SecondaryEvent, 10000);

    PiixPrivateData->Bmiba = (UINT32)(UINTPTR)LouKePciGetIoRegion(PDEV, BMBIA_BAR, 0);
    PiixPrivateData->MaxPioMode = 4;
    PiixPrivateData->MaxUDmaMode = 7;

    LouKeForkAtaHostPrivateDataToPorts(AtaHost);

    LouPrint("PIIX.SYS:PIIX BMIBA IO Port:%h\n", PiixPrivateData->Bmiba);
    UINT16* Buffer = (UINT16*)LouKeMalloc(512, KERNEL_GENERIC_MEMORY);    
    for(size_t i = 0 ; i < 4; i++){
        MaxPio = 2;
        MaxUDma = 0;
        if(AtaHost->Ports[i].PortScsiDevice){

            Status = LouKeAtaSendAtapiIdentifyCommand(
                &AtaHost->Ports[i],
                Buffer
            );

            if(Status != STATUS_SUCCESS){
                LouPrint("PIIX.SYS:ERROR:Faild To Send Identify Data\n");
                continue;
            }

        }else if(AtaHost->Ports[i].DeviceAttached){
            Status = LouKeAtaSendAtaIdentifyCommand(
                &AtaHost->Ports[i],
                Buffer
            );

            if(Status != STATUS_SUCCESS){
                LouPrint("PIIX.SYS:ERROR:Faild To Send Identify Data\n");
                continue;
            }
        }else {
            continue;
        }

        Tmp = Buffer[53];

        if(Tmp & (1 << 1)){
            LouPrint("PIIX.SYS:Fast PIO Supported\n");
            Tmp = Buffer[64];
            if(Tmp & (1 << 1)){
                MaxPio = 4;
            }
            else if(Tmp & (1 << 0)){
                MaxPio = 3;
            }
        }

        if(i < 2){
            Channel1Used = true;
            ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[i].PortPrivateData)->MaxPioMode = MaxPio;
        }else{
            Channel2Used = true;
            ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[i].PortPrivateData)->MaxPioMode = MaxPio;
        }

        Tmp = Buffer[53];
        if(Tmp & (1 << 2)){
            LouPrint("PIIX.SYS:UDMA Supported\n");
            Tmp = Buffer[88];
            for(int i = 7; i >= 0; i--){
                if(!(Tmp & (1 << i))){
                    MaxUDma = i;
                    break;
                }
            }   
            if(i < 2){
                ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[i].PortPrivateData)->MaxUDmaMode = MIN(MaxUDma, 2);
            }else{
                ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[i].PortPrivateData)->MaxUDmaMode = MIN(MaxUDma, 2);
            }

        }
        AtaHost->Ports[i].DmaPort = true;
        memset(Buffer, 0, 512);
    }
    LouKeFree(Buffer);

    UINT16 Time;

    if(Channel1Used){

        LouPrint("PIIX.SYS:Primary Max PIO Mode:%d\n", MaxPio);
        LouPrint("PIIX.SYS:Primary Max UDMA Mode:%d\n", MaxUDma);

        if(AtaHost->Ports[0].DeviceAttached){
            PiixSetPrimaryMasterPioTiming(AtaHost, MaxPio);
        }

        if(AtaHost->Ports[1].DeviceAttached){
            PiixSetPrimarySlavePioTiming(AtaHost, MaxPio);
        }

        if(((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[0].PortPrivateData)->MaxPioMode){
            
            UINT16 Time = LouKeReadPciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET);
            Time |= IDETIM_DTE0;
            LouKeWritePciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET, Time);

            AtaHost->Ports[0].Operations->IssueCommand = Piix3DmaIssueCommand;

        }


        if(((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[1].PortPrivateData)->MaxPioMode){
            
            UINT16 Time = LouKeReadPciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET);
            Time |= IDETIM_DTE1;
            LouKeWritePciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET, Time);

            AtaHost->Ports[1].Operations->IssueCommand = Piix3DmaIssueCommand;


        }
    
        RegisterInterruptHandler(Piix3PrimaryInterruptHandler, 0x20 + 14, false, (UINT64)AtaHost);

    }

    if(Channel2Used){

        if(AtaHost->Ports[2].DeviceAttached){
            PiixSetSecondaryMasterPioTiming(AtaHost, MaxPio);
        }

        if(AtaHost->Ports[3].DeviceAttached){
            PiixSetSecondarySlavePioTiming(AtaHost, MaxPio);
        }
    

        if(((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[2].PortPrivateData)->MaxPioMode){
            
            UINT16 Time = LouKeReadPciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET);
            Time |= IDETIM_DTE0;
            LouKeWritePciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET, Time);

            AtaHost->Ports[2].Operations->IssueCommand = Piix3DmaIssueCommand;

        }


        if(((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[3].PortPrivateData)->MaxPioMode){
            
            UINT16 Time = LouKeReadPciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET);
            Time |= IDETIM_DTE1;
            LouKeWritePciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET, Time);

            AtaHost->Ports[3].Operations->IssueCommand = Piix3DmaIssueCommand;

        }

        RegisterInterruptHandler(Piix3SecondaryInterruptHandler, 0x20 + 15, false, (UINT64)AtaHost);

    }

    LouKeHalPciSetMaster(PDEV);

    return STATUS_SUCCESS;
}
