#include <LouDDK.h>
#include <Hal.h>

//the following information is taken from the following sources
//http://bos.asmhackers.net/docs/ata/docs/pciide.pdf
//https://wiki.osdev.org/ATA_PIO_Mode
//https://wiki.osdev.org/ATAPI
//The Following Code Is Coppyright Ubnder GPL2 By:
//Tyler Grenier (C) 2025


//According to specification we can wait the 400ns byt reaing AS 4 times
static inline void AtaIoWait400ns(uint16_t ControlPort){
    CONTROL_READ_ALTERNATE_STATUS_PORT;
    CONTROL_READ_ALTERNATE_STATUS_PORT;
    CONTROL_READ_ALTERNATE_STATUS_PORT;
    CONTROL_READ_ALTERNATE_STATUS_PORT;
}

static LOUSTATUS IdLegacyDrive(
    PATA_QUEUED_COMMAND             QueuedCommand,
    PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort
){
    uint16_t CommandPort    = (uint16_t)(uintptr_t)AtaPort->CommandIoAddress;
    uint16_t ControlPort    = (uint16_t)(uintptr_t)AtaPort->ControlIoAddress;
    uint32_t PollCount             = 0;
    uint16_t* Data = (uint16_t*)QueuedCommand->DataAddress;
    uint8_t Status;
    if((AtaPort->PortNumber == 1) || (AtaPort->PortNumber == 3)){
        //Primary Bus
        COMMAND_WRITE_DRIVE_HEAD_PORT(0xA0);
    }else {
        //Secondary Bus
        COMMAND_WRITE_DRIVE_HEAD_PORT(0xB0);
    }
    //wait for the controllers Selector IC
    AtaIoWait400ns(ControlPort);
    //Zero Out
    COMMAND_WRITE_SECTOR_COUNT_PORT_LBA28(0);
    COMMAND_WRITE_LBAL_PORT_LBA28(0);
    COMMAND_WRITE_LBAM_PORT_LBA28(0);
    COMMAND_WRITE_LBAH_PORT_LBA28(0);
    //Wait For The Designator IC
    AtaIoWait400ns(ControlPort);
    //Send Command
    COMMAND_WRITE_COMMAND_PORT(QueuedCommand->Command);

    if(COMMAND_READ_STATUS_PORT == 0){
        LouPrint("Error: Detected Drive Is A Ghost Drive Quirk\n");
        AtaPort->DeviceAttached = false;
        return STATUS_NO_SUCH_DEVICE;
    }
    //LouPrint("Waiting On Device\n");
    
    Status = COMMAND_READ_STATUS_PORT;

    while(10000 >= PollCount){
        if((!(Status & 0x80)) || (Status & 0x01)){
            break;
        }
        Status = COMMAND_READ_STATUS_PORT;
        sleep(100);
        PollCount += 100;
    }

    if(PollCount >= AtaPort->PollTimer){
        LouPrint("Error Timeout Occoured\n");
        return STATUS_TIMEOUT;
    }
    if(Status & 0x01){
        LouPrint("Device Error\n");
        return STATUS_IO_DEVICE_ERROR;
    }
    //LouPrint("Command Completed Successfully\n");

    for(uint16_t i = 0 ; i < 256; i++){
        Data[i] = COMMAND_READ_DATA_PORT;
    }

    return STATUS_SUCCESS;
}

static LOUSTATUS ReadLegacyAtapi(
    PATA_QUEUED_COMMAND             QueuedCommand,
    PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort
){
    uint16_t CommandPort    = (uint16_t)(uintptr_t)AtaPort->CommandIoAddress;
    uint16_t ControlPort    = (uint16_t)(uintptr_t)AtaPort->ControlIoAddress;
    uint32_t PollCount             = 0;
    uint16_t* Data = (uint16_t*)QueuedCommand->DataAddress;
    bool WriteCommand = QueuedCommand->WriteCommand;
    uint8_t Status;

    if(WriteCommand){
        //curently there is no Write
    }else{
        if((AtaPort->PortNumber == 1) || (AtaPort->PortNumber == 3)){
            COMMAND_WRITE_DRIVE_HEAD_PORT(0xA0);
        }else{
            COMMAND_WRITE_DRIVE_HEAD_PORT(0xB0);
        }
        //wait for the controllers Selector IC
        AtaIoWait400ns(ControlPort);
        //Fill the Command Data
        COMMAND_WRITE_FEATURE_PORT_LBA28(0);
        COMMAND_WRITE_LBAM_PORT_LBA28(2048 & 0xFF);
        COMMAND_WRITE_LBAH_PORT_LBA28(2048 >> 8);
        //Send Command
        COMMAND_WRITE_COMMAND_PORT(QueuedCommand->Command);
        AtaIoWait400ns(ControlPort);
        //LouPrint("Waiting On Device\n");
        Status = COMMAND_READ_STATUS_PORT;
        while(AtaPort->PollTimer >= PollCount){
            if((((!(Status & 0x80)) && (Status & 0x08)) || (Status & 0x01))){
                break;
            }
            Status = COMMAND_READ_STATUS_PORT;
            sleep(100);
            PollCount += 100;
        }

        if(PollCount >= AtaPort->PollTimer){
            //LouPrint("Error Timeout Occoured\n");
            return STATUS_TIMEOUT;
        }
        if(Status & 0x01){
            //LouPrint("Device Error\n");
            return STATUS_IO_DEVICE_ERROR;
        }
        //Reset Poll For the next Poll
        PollCount = 0;
        //Output the Packet Command
        COMMAND_WRITE_DATA_PORT_BUFFER((uint8_t*)&QueuedCommand->ScsiCommand[0], 6);

        for(uint32_t i = 0 ; i < QueuedCommand->SectorCount; i++){
            while(1){
                Status = COMMAND_READ_STATUS_PORT;
                if(Status & 0x01){
                    return STATUS_IO_DEVICE_ERROR;
                }
                if((!(Status & 0x80)) && (Status & 0x08)){
                    break;
                }
                AtaIoWait400ns(ControlPort);
            }
            int DataSize = COMMAND_READ_LBAM_PORT_LBA28 | (COMMAND_READ_LBAH_PORT_LBA28 << 8);
            COMMAND_READ_DATA_PORT_BUFFER((uint16_t*)((uint8_t*)Data + (i * 0x800)), DataSize / 2);
        }
        return STATUS_SUCCESS;
    }
    //LouPrint("Command Completed Successfully\n");
    return STATUS_INVALID_PARAMETER;
}

static LOUSTATUS ReadLegacyAta(
    PATA_QUEUED_COMMAND             QueuedCommand,
    PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort
){
    UNUSED uint16_t CommandPort    = (uint16_t)(uintptr_t)AtaPort->CommandIoAddress;
    UNUSED uint16_t ControlPort    = (uint16_t)(uintptr_t)AtaPort->ControlIoAddress;
    UNUSED uint32_t PollCount             = 0;
    UNUSED uint16_t* Data = (uint16_t*)QueuedCommand->DataAddress;
    UNUSED bool WriteCommand = QueuedCommand->WriteCommand;
    UNUSED uint8_t Status;

    if(WriteCommand){
        //curently there is no read
    }else{
        if((AtaPort->PortNumber == 1) || (AtaPort->PortNumber == 3)){
            COMMAND_WRITE_DRIVE_HEAD_PORT(0xE0);
        }else{
            COMMAND_WRITE_DRIVE_HEAD_PORT(0xF0);
        }
        //wait for the controllers Selector IC
        AtaIoWait400ns(ControlPort);
        //Fill the Command Data
        COMMAND_WRITE_FEATURE_PORT_LBA28(0);
        COMMAND_WRITE_SECTOR_COUNT_PORT_LBA28(QueuedCommand->SectorCount);

        COMMAND_WRITE_LBAL_PORT_LBA28(QueuedCommand->Lbal);
        COMMAND_WRITE_LBAM_PORT_LBA28(QueuedCommand->Lbam);
        COMMAND_WRITE_LBAH_PORT_LBA28(QueuedCommand->Lbah);
        //Send Command
        COMMAND_WRITE_COMMAND_PORT(0x20);
        AtaIoWait400ns(ControlPort);
        //LouPrint("Waiting On Device\n");
        Status = COMMAND_READ_STATUS_PORT;
        for(uint32_t i = 0 ; i < QueuedCommand->SectorCount; i++){
            while(1){
                Status = COMMAND_READ_STATUS_PORT;
                if(Status & 0x01){
                    return STATUS_IO_DEVICE_ERROR;
                }
                if((!(Status & 0x80)) && (Status & 0x08)){
                    break;
                }
                AtaIoWait400ns(ControlPort);
            }
            COMMAND_READ_DATA_PORT_BUFFER((uint16_t*)((uint8_t*)Data + (i * 512)), 256);
        }
        return STATUS_SUCCESS;
    }
    return STATUS_INVALID_PARAMETER;
}

LOUSTATUS AtaGenricPIOIssueCommand(
    PATA_QUEUED_COMMAND QueuedCommand
){
    LouKIRQL Irql;
    LOUSTATUS Result = STATUS_SUCCESS;
    //LouPrint("Ata Genric DMA Issue Command\n");
    PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort = QueuedCommand->Port;
    LouKeAcquireSpinLock(&AtaPort->PortLock, &Irql);

    //There 2 types of different Drives for 
    //Commands the identify drive and read write drives
    //first well do ther identify commands
    if(
        (QueuedCommand->Command == ATA_COMMAND_IDENTIFY_ATA) || 
        (QueuedCommand->Command == ATA_COMMAND_IDENTIFY_ATAPI)
    ){
        //LouPrint("Handleing ATA/ATAPI Identification Command\n");
        Result = IdLegacyDrive(QueuedCommand, AtaPort);
        MutexUnlock(&AtaPort->OpreationLock);
        LouKeReleaseSpinLock(&AtaPort->PortLock, &Irql);
        return Result;
    }

    if(QueuedCommand->PacketCommand){
        Result = ReadLegacyAtapi(QueuedCommand, AtaPort);
        MutexUnlock(&AtaPort->OpreationLock);
        LouKeReleaseSpinLock(&AtaPort->PortLock, &Irql);
        return Result;
    }

    Result = ReadLegacyAta(QueuedCommand, AtaPort);
    MutexUnlock(&AtaPort->OpreationLock);
    LouKeReleaseSpinLock(&AtaPort->PortLock, &Irql);
    return Result;
}

static LOUSINE_ATA_PORT_OPERATIONS IdeGenericOperations;

static inline void AtaGenericResetDevice(PLOUSINE_KERNEL_DEVICE_ATA_PORT Port){
    LouPrint("Ata Generic Reset Device\n");
    UNUSED uint16_t ControlPort = (uint16_t)(uintptr_t)Port->ControlIoAddress;
    
    CONTROL_WRITE_DEVICE_CONTROL_PORT(1 << 2);
    AtaIoWait400ns(ControlPort);
    CONTROL_WRITE_DEVICE_CONTROL_PORT(0);
    AtaIoWait400ns(ControlPort);

}

static void AtaGenericGetDeviceType(PLOUSINE_KERNEL_DEVICE_ATA_PORT Port){
    LouPrint("Ata Generic Get Device Type\n");
    AtaGenericResetDevice(Port);
    uint16_t ControlPort = (uint16_t)(uintptr_t)Port->ControlIoAddress;
    uint16_t CommandPort = (uint16_t)(uintptr_t)Port->CommandIoAddress;
    if((Port->PortNumber == 1) || (Port->PortNumber == 3)){
        COMMAND_WRITE_DRIVE_HEAD_PORT(0xA0);
    }
    else{
        COMMAND_WRITE_DRIVE_HEAD_PORT(0xB0);
    }
    AtaIoWait400ns(ControlPort);

    uint8_t LBAL = COMMAND_READ_LBAL_PORT_LBA28;
    uint8_t LBAH = COMMAND_READ_LBAH_PORT_LBA28;

    if((LBAL == 0x14) || (LBAH == 0xEB)){
        LouPrint("PATAPI\n");
        Port->PortScsiDevice = true;
        Port->SerialDevice = false;
        Port->SectorSize = 2048;
        Port->DeviceAttached = true;
    }
    if((LBAL == 0x69) || (LBAH == 0x96)){
        LouPrint("SATAPI\n");
        Port->PortScsiDevice = true;
        Port->SerialDevice = true;
        Port->SectorSize = 2048;
        Port->DeviceAttached = true;
    }
    if((LBAL == 0) || (LBAH == 0)){
        LouPrint("ATA\n");
        Port->PortScsiDevice = false;
        Port->SerialDevice = false;
        Port->SectorSize = 512;
        Port->DeviceAttached = true;
    }
    if((LBAL == 0x3C) || (LBAH == 0xC3)){
        LouPrint("SATA\n");
        Port->PortScsiDevice = false;
        Port->SerialDevice = true;
        Port->SectorSize = 512;
        Port->DeviceAttached = true;
    }

}

LOUDDK_API_ENTRY 
LOUSTATUS LouKeAtaSendAtapiIdentifyCommand(
    PLOUSINE_KERNEL_DEVICE_ATA_PORT  AtapiPort,
    void*                            IdBuffer
);

LOUDDK_API_ENTRY
LOUSTATUS InitializeGenericAtaDevice(PPCI_DEVICE_OBJECT PDEV){

    //Allocate 4 Ports For The Ata Host
    LouPrint("Allocating Ata Device Data\n");
    PLOUSINE_KERNEL_DEVICE_ATA_HOST LegacyAtaHost = LouKeMallocAtaDevice(PDEV, 4); 
    LouPrint("Initializing Generic Ata Device\n");
    UNUSED uint8_t PortDeviceIdValue = 0;
    //Fill Port 1
    LegacyAtaHost->Ports[0].ControlIoAddress = COMPATIBILITY_PRIMARY_CONTROL_BASE;
    LegacyAtaHost->Ports[0].CommandIoAddress = COMPATIBILITY_PRIMARY_COMMAND_BASE;
    LegacyAtaHost->Ports[0].Operations       = &IdeGenericOperations;
    LegacyAtaHost->Ports[0].PollTimer        = 10000;//Ten Second Timer
    LegacyAtaHost->Ports[0].SectorCountLimit = 1;
    LegacyAtaHost->Ports[0].DeviceAttached   = false;
    AtaGenericGetDeviceType(&LegacyAtaHost->Ports[0]);
    
    //Fill Port 2
    LegacyAtaHost->Ports[1].ControlIoAddress = COMPATIBILITY_PRIMARY_CONTROL_BASE;
    LegacyAtaHost->Ports[1].CommandIoAddress = COMPATIBILITY_PRIMARY_COMMAND_BASE;
    LegacyAtaHost->Ports[1].Operations       = &IdeGenericOperations;
    LegacyAtaHost->Ports[1].PollTimer        = 10000;//Ten Second Timer
    LegacyAtaHost->Ports[1].SectorCountLimit = 1; 
    LegacyAtaHost->Ports[1].DeviceAttached   = false;
    AtaGenericGetDeviceType(&LegacyAtaHost->Ports[1]);

    //Fill Port 3
    LegacyAtaHost->Ports[2].ControlIoAddress = COMPATIBILITY_SECONDARY_CONTROL_BASE;
    LegacyAtaHost->Ports[2].CommandIoAddress = COMPATIBILITY_SECONDARY_COMMAND_BASE;
    LegacyAtaHost->Ports[2].Operations       = &IdeGenericOperations;
    LegacyAtaHost->Ports[2].PollTimer        = 10000;//Ten Second Timer
    LegacyAtaHost->Ports[2].SectorCountLimit = 1; 
    LegacyAtaHost->Ports[2].DeviceAttached   = false;
    AtaGenericGetDeviceType(&LegacyAtaHost->Ports[2]);
    
    //Fill Port 4
    LegacyAtaHost->Ports[3].ControlIoAddress = COMPATIBILITY_SECONDARY_CONTROL_BASE;
    LegacyAtaHost->Ports[3].CommandIoAddress = COMPATIBILITY_SECONDARY_COMMAND_BASE;
    LegacyAtaHost->Ports[3].Operations       = &IdeGenericOperations;
    LegacyAtaHost->Ports[3].PollTimer        = 10000;//Ten Second Timer
    LegacyAtaHost->Ports[3].SectorCountLimit = 1; 
    LegacyAtaHost->Ports[3].DeviceAttached   = false;
    AtaGenericGetDeviceType(&LegacyAtaHost->Ports[3]);


    IdeGenericOperations.IssueCommand = AtaGenricPIOIssueCommand;

    PPCI_COMMON_CONFIG Config = (PPCI_COMMON_CONFIG)PDEV->CommonConfig;
    LouKeHalGetPciConfiguration(PDEV, Config);

    //LouPrint("Dma Port Is:%h\n", Config->Header.u.type0.BaseAddresses[4]);
    //uint16_t DmaPort = (uint16_t)Config->Header.u.type0.BaseAddresses[4];

    LegacyAtaHost->Ports[0].DmaIoAddress = (void*)(uintptr_t)Config->Header.u.type0.BaseAddresses[4];
    LegacyAtaHost->Ports[0].PrdtBoundry = 64 * KILOBYTE;
    LegacyAtaHost->Ports[1].DmaIoAddress = (void*)(uintptr_t)Config->Header.u.type0.BaseAddresses[4];
    LegacyAtaHost->Ports[1].PrdtBoundry = 64 * KILOBYTE;
    LegacyAtaHost->Ports[2].DmaIoAddress = (void*)(uintptr_t)Config->Header.u.type0.BaseAddresses[4];
    LegacyAtaHost->Ports[2].PrdtBoundry = 64 * KILOBYTE;
    LegacyAtaHost->Ports[3].DmaIoAddress = (void*)(uintptr_t)Config->Header.u.type0.BaseAddresses[4];
    LegacyAtaHost->Ports[3].PrdtBoundry = 64 * KILOBYTE;

    LouPrint("Adding Ata Device To Device Manager\n");    
    LouKeRegisterDevice(
        PDEV, 
        ATA_DEVICE_T,
        "Annya/System64/Drivers/IDEGen.sys",
        (void*)LegacyAtaHost,
        LegacyAtaHost
    );

    return STATUS_SUCCESS;
}