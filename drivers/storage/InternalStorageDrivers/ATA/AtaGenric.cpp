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


LOUSTATUS AtaGenricPIOPrepCommand(
    PATA_QUEUED_COMMAND QueuedCommand
){
    LouPrint("Ata Generic Prepping Command\n");
    PLOUSINE_KERNEL_DEVICE_ATA_PORT Port = QueuedCommand->Port;

    uint16_t CommandPort = (uint16_t)(uintptr_t)Port->CommandIoAddress;
    uint16_t ControlPort = (uint16_t)(uintptr_t)Port->ControlIoAddress;

    QueuedCommand->CommandCompleted = false;

    if((Port->PortNumber == 1) || (Port->PortNumber == 3)){
        COMMAND_WRITE_DRIVE_HEAD_PORT(0xA0);
    }else{
        COMMAND_WRITE_DRIVE_HEAD_PORT(0xB0);
    }
    //wait 400ns
    AtaIoWait400ns(ControlPort);

    if(QueuedCommand->PacketCommand){
        if(Port->CommandLengthFlags & (COMMAND_LENGTH_FLAG_LBA48)){
            COMMAND_WRITE_FEATURE_PORT_LBA48(QueuedCommand->DmaCommand ? 1 : 0); //Using operand for C++ Mangling
            COMMAND_WRITE_LBAL_PORT_LBA48(0);
            COMMAND_WRITE_LBAM_PORT_LBA48(2048 & 0xFF);
            COMMAND_WRITE_LBAH_PORT_LBA48(2048 >> 8);

        }else{
            COMMAND_WRITE_FEATURE_PORT_LBA28(QueuedCommand->DmaCommand ? 1 : 0); //Using operand for C++ Mangling
            COMMAND_WRITE_LBAL_PORT_LBA28(0);
            COMMAND_WRITE_LBAM_PORT_LBA28(2048 & 0xFF);
            COMMAND_WRITE_LBAH_PORT_LBA28(2048 >> 8);
        }
        LouPrint("Ata Generic Command Successfully preped\n");
        return STATUS_SUCCESS;
    }



    if(Port->CommandLengthFlags & (COMMAND_LENGTH_FLAG_LBA48)){
        COMMAND_WRITE_LBAL_PORT_LBA48(QueuedCommand->Lbal);
        COMMAND_WRITE_LBAM_PORT_LBA48(QueuedCommand->Lbam);
        COMMAND_WRITE_LBAH_PORT_LBA48(QueuedCommand->Lbah);
    }else {
        COMMAND_WRITE_LBAL_PORT_LBA28(QueuedCommand->Lbal);
        COMMAND_WRITE_LBAM_PORT_LBA28(QueuedCommand->Lbam);
        COMMAND_WRITE_LBAH_PORT_LBA28(QueuedCommand->Lbah);
    }
    LouPrint("Ata Generic Command Successfully preped\n");

    return STATUS_SUCCESS;
}   

LOUSTATUS AtaGenricPIOIssueCommand(
    PATA_QUEUED_COMMAND QueuedCommand
){
    LouPrint("Ata Generic Issueing Command\n");
    PLOUSINE_KERNEL_DEVICE_ATA_PORT Port = QueuedCommand->Port;

    uint16_t CommandPort = (uint16_t)(uintptr_t)Port->CommandIoAddress;
    uint16_t ControlPort = (uint16_t)(uintptr_t)Port->ControlIoAddress;
    uintptr_t DataAddress = (uintptr_t)QueuedCommand->DataAddress;
    uint32_t PollClock = 0;
    COMMAND_WRITE_COMMAND_PORT(QueuedCommand->Command);
    AtaIoWait400ns(ControlPort);
    if(QueuedCommand->PacketCommand){
        COMMAND_WRITE_DATA_PORT_BUFFER(QueuedCommand->ScsiCommand, QueuedCommand->ScsiCommandLength / 2);
        if(QueuedCommand->WriteCommand){

        }else{
            for(uint32_t i = 0 ; i < QueuedCommand->SectorCount; i++){
                while(PollClock <= Port->PollTimer){
                    uint8_t Status = COMMAND_READ_SATUS_PORT;
                    if(Status & 0x01){
                        return STATUS_UNSUCCESSFUL;
                    }
                    if((!(Status & 0x80)) && (Status & 0x08)){
                        break;
                    }
                    sleep(100);
                    PollClock += 100;
                }
                if(PollClock >= Port->PollTimer){
                    return STATUS_UNSUCCESSFUL;
                }
                COMMAND_READ_DATA_PORT_BUFFER((uint16_t*)((uint8_t*)DataAddress), Port->SectorSize / 2);
            }
        }
        AtaIoWait400ns(ControlPort);
        return STATUS_SUCCESS;
    } 
    if(QueuedCommand->WriteCommand){

    }else{
        while(PollClock <= Port->PollTimer){
            uint8_t Status = COMMAND_READ_SATUS_PORT;
            if(Status & 0x01){
                return STATUS_UNSUCCESSFUL;
            }
            if(!(Status & 0x80) && (Status & 0x08)){
                break;
            }
            sleep(100);
            PollClock += 100;
        }
        if(PollClock >= Port->PollTimer){
            return STATUS_UNSUCCESSFUL;
        }
        COMMAND_READ_DATA_PORT_BUFFER((uint16_t*)((uint8_t*)DataAddress), Port->SectorSize / 2);
    }
    AtaIoWait400ns(ControlPort);
    return STATUS_SUCCESS;
}

LOUSINE_ATA_PORT_OPERATIONS IdeGenericOperations;

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
        //LouPrint("PATAPI\n");
        Port->PortScsiDevice = true;
        Port->SerialDevice = false;
        Port->SectorSize = 2048;
    }
    if((LBAL == 0x69) || (LBAH == 0x96)){
        //LouPrint("SATAPI\n");
        Port->PortScsiDevice = true;
        Port->SerialDevice = true;
        Port->SectorSize = 2048;
    }
    if((LBAL == 0) || (LBAH == 0)){
        //LouPrint("ATA\n");
        Port->PortScsiDevice = false;
        Port->SerialDevice = false;
        Port->SectorSize = 512;
    }
    if((LBAL == 0x3C) || (LBAH == 0xC3)){
        //LouPrint("SATA\n");
        Port->PortScsiDevice = false;
        Port->SerialDevice = true;
        Port->SectorSize = 512;
    }

}

LOUSTATUS InitializeGenericAtaDevice(P_PCI_DEVICE_OBJECT PDEV){

    //Allocate 4 Ports For The Ata Host
    LouPrint("Allocating Ata Device Data\n");
    PLOUSINE_KERNEL_DEVICE_ATA_HOST LegacyAtaHost = LouMallocAtaDevice(PDEV, 4); 
    LouPrint("Initializing Generic Ata Device\n");
    UNUSED uint8_t PortDeviceIdValue = 0;
    //Fill Port 1
    LegacyAtaHost->Ports[0].ControlIoAddress = COMPATIBILITY_PRIMARY_CONTROL_BASE;
    LegacyAtaHost->Ports[0].CommandIoAddress = COMPATIBILITY_PRIMARY_COMMAND_BASE;
    LegacyAtaHost->Ports[0].Operations       = &IdeGenericOperations;
    LegacyAtaHost->Ports[0].PollTimer        = 10000;//Ten Second Timer
    AtaGenericGetDeviceType(&LegacyAtaHost->Ports[0]);
    
    //Fill Port 2
    LegacyAtaHost->Ports[1].ControlIoAddress = COMPATIBILITY_PRIMARY_CONTROL_BASE;
    LegacyAtaHost->Ports[1].CommandIoAddress = COMPATIBILITY_PRIMARY_COMMAND_BASE;
    LegacyAtaHost->Ports[1].Operations       = &IdeGenericOperations;
    LegacyAtaHost->Ports[1].PollTimer        = 10000;//Ten Second Timer
    AtaGenericGetDeviceType(&LegacyAtaHost->Ports[1]);

    //Fill Port 3
    LegacyAtaHost->Ports[2].ControlIoAddress = COMPATIBILITY_SECONDARY_CONTROL_BASE;
    LegacyAtaHost->Ports[2].CommandIoAddress = COMPATIBILITY_SECONDARY_COMMAND_BASE;
    LegacyAtaHost->Ports[2].Operations       = &IdeGenericOperations;
    LegacyAtaHost->Ports[2].PollTimer        = 10000;//Ten Second Timer
    AtaGenericGetDeviceType(&LegacyAtaHost->Ports[2]);
    
    //Fill Port 4
    LegacyAtaHost->Ports[3].ControlIoAddress = COMPATIBILITY_SECONDARY_CONTROL_BASE;
    LegacyAtaHost->Ports[3].CommandIoAddress = COMPATIBILITY_SECONDARY_COMMAND_BASE;
    LegacyAtaHost->Ports[3].Operations       = &IdeGenericOperations;
    LegacyAtaHost->Ports[3].PollTimer        = 10000;//Ten Second Timer
    AtaGenericGetDeviceType(&LegacyAtaHost->Ports[3]);


    IdeGenericOperations.PrepCommand = AtaGenricPIOPrepCommand;
    IdeGenericOperations.IssueCommand = AtaGenricPIOIssueCommand;

    LouPrint("Adding Ata Device To Device Manager\n");

    LouKeRegisterDevice(
        PDEV, 
        ATA_DEVICE_T,
        "Annya/System64/Drivers/IDEGeneric.sys",
        (void*)LegacyAtaHost,
        0x00
    );

    return STATUS_SUCCESS;
}