#include "PIIX.h"

static spinlock_t PiixLock = {0};

void PiixPrimaryInterruptHandler(UINT64 HandlerData){
    PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost = (PLOUSINE_KERNEL_DEVICE_ATA_HOST)HandlerData;
    PPIIX_HOST_PRIVATE_DATA Private = (PPIIX_HOST_PRIVATE_DATA)AtaHost->HostPrivateData;
    UINT16 BmiCommand = PRIMARY_BMICOM_REGISTER(Private);
    UINT16 BmiStatus = PRIMARY_BMISTA_REGISTER(Private);
    UINT8 CommandValue = inb(BmiCommand);
    UINT8 StatusValue = inb(BmiStatus);
    
    if(!(CommandValue & BMICOM_SSBM)) return;

    if(StatusValue & BMISTA_DMAERR){
        LouPrint("PIIX.SYS:ERROR Durring DMA Transfer\n");
    }
    CommandValue &= ~(BMICOM_SSBM);
    outb(BmiCommand, CommandValue);

    StatusValue |= (BMISTA_IDEINTR | BMISTA_DMAERR);
    outb(BmiStatus, StatusValue);
    LouKeSignalEvent(&Private->PrimaryEvent);
}

void PiixSecondryInterruptHandler(UINT64 HandlerData){



    LouPrint("PIIX.SYS:PiixSecondryInterruptHandler()\n");
    while(1);
}

//the following information is taken from the following sources
//http://www.bitsavers.org/components/intel/pci/290550-001_82371FB_82371SB_PCI_ISA_IDE_Xcelerator_199605.pdf
//http://bos.asmhackers.net/docs/ata/docs/pciide.pdf
//https://wiki.osdev.org/ATA_PIO_Mode
//https://wiki.osdev.org/ATAPI
//The Following Code Is Coppyright Ubnder GPL2 By:
//Tyler Grenier (C) 2025 - 2026

static void PiixCommitTransfer(PPIIX_HOST_PRIVATE_DATA Private, BOOL Primary){
    mutex_t* Lock = Primary ? &Private->PrimaryDmaLock : &Private->SecondaryDmaLock;
    PKERNEL_EVENT_OBJECT Object = Primary ? &Private->PrimaryEvent : &Private->SecondaryEvent;
    LouKeWaitForEvent(Object);
    MutexUnlock(Lock);
}

static void PiixInitializeBmi(PPIIX_HOST_PRIVATE_DATA Private, PVOID Prdt, BOOL Primary, BOOL Write){
    UINT16 BmiCommand = Primary ? PRIMARY_BMICOM_REGISTER(Private) : SECONDARY_BMICOM_REGISTER(Private);
    UINT16 BmiStatus = Primary ? PRIMARY_BMISTA_REGISTER(Private) : SECONDARY_BMISTA_REGISTER(Private);
    UINT16 BmiPtr = Primary ? PRIMARY_BMIDTP_REGISTER(Private) : SECONDARY_BMIDTP_REGISTER(Private);
    UINT8  CommandValue = 0;
    UINT8  StatusValue = 0;
    mutex_t* Lock = Primary ? &Private->PrimaryDmaLock : &Private->SecondaryDmaLock;
    UINT64 PhyPrdt;
    RequestPhysicalAddress((UINT64)Prdt, &PhyPrdt);
    MutexLock(Lock);

    CommandValue = inb(BmiCommand);
    if(Write){
        CommandValue &= ~(BMICOM_RWCON);
    }else{
        CommandValue |= (BMICOM_RWCON);
    }
    CommandValue |= (BMICOM_SSBM);
    outb(BmiCommand, CommandValue);

    StatusValue = inb(BmiStatus);
    StatusValue |= (BMISTA_IDEINTR | BMISTA_DMAERR);
    outb(BmiStatus, StatusValue);

    outl(BmiPtr, (UINT32)PhyPrdt);

}

static LOUSTATUS PiixAllocateDmaTransfer(
    PVOID* OutPrdt, 
    PVOID* OutDma, 
    SIZE DmaTransferSize
){
    if((!DmaTransferSize) || (!OutPrdt) || (!OutDma)){
        LouPrint("PIIX.SYS:PiixAllocateDmaTransfer() EINVAL\n");
        return STATUS_INVALID_PARAMETER;
    }
    SIZE Tables = ROUND_UP64(DmaTransferSize, 64 * KILOBYTE) / (64 * KILOBYTE);
    PVOID BufferOut = LouKeMallocExPhy32(DmaTransferSize, 64 * KILOBYTE, KERNEL_DMA_MEMORY);
    *OutDma = BufferOut; 
    PPIIX3_DMA_PRD PrdtBuffer = (PPIIX3_DMA_PRD)LouKeMallocExPhy32(Tables * sizeof(PIIX3_DMA_PRD), 64 * KILOBYTE, KERNEL_DMA_MEMORY);
    *OutPrdt = (PVOID)PrdtBuffer;
    UINT64 PhyAddress = 0x00;
    SIZE i = 0;
    for(; i < (Tables - 1); i++){
        RequestPhysicalAddress((UINT64)BufferOut + (i * (64 * KILOBYTE)), &PhyAddress);
        PrdtBuffer[i].PhyAddress = (UINT32)PhyAddress;
        PrdtBuffer[i].ByteCount = 0x00;
        PrdtBuffer[i].Flags = 0x00;
    }

    RequestPhysicalAddress((UINT64)BufferOut + (i * (64 * KILOBYTE)), &PhyAddress);
    PrdtBuffer[i].PhyAddress = (UINT32)PhyAddress;
    PrdtBuffer[i].ByteCount = (((DmaTransferSize - (i * (64 * KILOBYTE))) == (64 * KILOBYTE)) ? 0 : (DmaTransferSize - (i * (64 * KILOBYTE))));
    PrdtBuffer[i].Flags = PIIX3_PRD_FLAG_EOT;
    return STATUS_SUCCESS;
}

//According to specification we can wait the 400ns byt reaing AS 4 times
static inline void PiixIoWait400ns(uint16_t ControlPort){
    CONTROL_READ_ALTERNATE_STATUS_PORT;
    CONTROL_READ_ALTERNATE_STATUS_PORT;
    CONTROL_READ_ALTERNATE_STATUS_PORT;
    CONTROL_READ_ALTERNATE_STATUS_PORT;
}

static LOUSTATUS IdPiixDrive(
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
    PiixIoWait400ns(ControlPort);
    //Zero Out
    COMMAND_WRITE_SECTOR_COUNT_PORT_LBA28(0);
    COMMAND_WRITE_LBAL_PORT_LBA28(0);
    COMMAND_WRITE_LBAM_PORT_LBA28(0);
    COMMAND_WRITE_LBAH_PORT_LBA28(0);
    //Wait For The Designator IC
    PiixIoWait400ns(ControlPort);
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

static LOUSTATUS ReadPiixAtapi(
    PATA_QUEUED_COMMAND             QueuedCommand,
    PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort
){
    uint16_t CommandPort    = (uint16_t)(uintptr_t)AtaPort->CommandIoAddress;
    uint16_t ControlPort    = (uint16_t)(uintptr_t)AtaPort->ControlIoAddress;
    uint32_t PollCount             = 0;
    uint16_t* Data = (uint16_t*)QueuedCommand->DataAddress;
    bool WriteCommand = QueuedCommand->WriteCommand;
    uint8_t Status;

    PVOID OutDma = 0;
    PVOID NewPrdt = 0;

    LOUSTATUS Result = PiixAllocateDmaTransfer(&NewPrdt, &OutDma, QueuedCommand->DataSize);

    if(Result != STATUS_SUCCESS){
        LouPrint("PIIX.SYS:ERROR Allocating DMA Data\n");
        return Result;
    }

    if(WriteCommand){
        //curently there is no Write
    }else{

        PiixInitializeBmi((PPIIX_HOST_PRIVATE_DATA)AtaPort->AtaHost->HostPrivateData, NewPrdt, AtaPort->PortNumber < 3, false);

        if((AtaPort->PortNumber == 1) || (AtaPort->PortNumber == 3)){
            COMMAND_WRITE_DRIVE_HEAD_PORT(0xA0);
        }else{
            COMMAND_WRITE_DRIVE_HEAD_PORT(0xB0);
        }
        //wait for the controllers Selector IC
        PiixIoWait400ns(ControlPort);
        //Fill the Command Data
        COMMAND_WRITE_FEATURE_PORT_LBA28(1);
        COMMAND_WRITE_LBAM_PORT_LBA28(2048 & 0xFF);
        COMMAND_WRITE_LBAH_PORT_LBA28(2048 >> 8);
        //Send Command
        COMMAND_WRITE_COMMAND_PORT(QueuedCommand->Command);
        PiixIoWait400ns(ControlPort);
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

        PiixCommitTransfer((PPIIX_HOST_PRIVATE_DATA)AtaPort->AtaHost->HostPrivateData, AtaPort->PortNumber < 3);
                
        memcpy((PVOID)QueuedCommand->DataAddress, OutDma, QueuedCommand->DataSize);

        LouKeFreePhy32(OutDma);
        LouKeFreePhy32(NewPrdt);
        return STATUS_SUCCESS;
    }
    //LouPrint("Command Completed Successfully\n");
    return STATUS_INVALID_PARAMETER;
}

static LOUSTATUS ReadPiixAta(
    PATA_QUEUED_COMMAND             QueuedCommand,
    PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort
){
    UNUSED uint16_t CommandPort    = (uint16_t)(uintptr_t)AtaPort->CommandIoAddress;
    UNUSED uint16_t ControlPort    = (uint16_t)(uintptr_t)AtaPort->ControlIoAddress;
    UNUSED uint32_t PollCount             = 0;
    UNUSED uint16_t* Data = (uint16_t*)QueuedCommand->DataAddress;
    UNUSED bool WriteCommand = QueuedCommand->WriteCommand;
    UNUSED uint8_t Status;

    PVOID OutDma = 0;
    PVOID NewPrdt = 0;

    PiixAllocateDmaTransfer(&NewPrdt, &OutDma, QueuedCommand->DataSize);

    if(WriteCommand){
        //curently there is no read
    }else{
        PiixInitializeBmi((PPIIX_HOST_PRIVATE_DATA)AtaPort->AtaHost->HostPrivateData, NewPrdt, AtaPort->PortNumber < 3, false);

        if((AtaPort->PortNumber == 1) || (AtaPort->PortNumber == 3)){
            COMMAND_WRITE_DRIVE_HEAD_PORT(0xE0);
        }else{
            COMMAND_WRITE_DRIVE_HEAD_PORT(0xF0);
        }
        //wait for the controllers Selector IC
        PiixIoWait400ns(ControlPort);
        //Fill the Command Data
        COMMAND_WRITE_FEATURE_PORT_LBA28(0);
        COMMAND_WRITE_SECTOR_COUNT_PORT_LBA28(QueuedCommand->SectorCount);

        COMMAND_WRITE_LBAL_PORT_LBA28(QueuedCommand->Lbal);
        COMMAND_WRITE_LBAM_PORT_LBA28(QueuedCommand->Lbam);
        COMMAND_WRITE_LBAH_PORT_LBA28(QueuedCommand->Lbah);
        //Send Command
        COMMAND_WRITE_COMMAND_PORT(0x20);
        PiixIoWait400ns(ControlPort);
        //LouPrint("Waiting On Device\n");

        PiixCommitTransfer((PPIIX_HOST_PRIVATE_DATA)AtaPort->AtaHost->HostPrivateData, AtaPort->PortNumber < 2);

        LouKeFreePhy32(OutDma);
        LouKeFreePhy32(NewPrdt);
        return STATUS_SUCCESS;
    }
    return STATUS_INVALID_PARAMETER;
}

LOUSTATUS PiixDmaIssueCommand(
    PATA_QUEUED_COMMAND QueuedCommand
){
    LouKIRQL Irql;
    LOUSTATUS Result = STATUS_SUCCESS;
    //LouPrint("Ata Genric DMA Issue Command\n");
    PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort = QueuedCommand->Port;

    //There 2 types of different Drives for 
    //Commands the identify drive and read write drives
    //first well do ther identify commands
    if(
        (QueuedCommand->Command == ATA_COMMAND_IDENTIFY_ATA) || 
        (QueuedCommand->Command == ATA_COMMAND_IDENTIFY_ATAPI)
    ){
        //LouPrint("Handleing ATA/ATAPI Identification Command\n");
        Result = IdPiixDrive(QueuedCommand, AtaPort);
        return Result;
    }

    if(QueuedCommand->PacketCommand){
        Result = ReadPiixAtapi(QueuedCommand, AtaPort);
        return Result;
    }

    Result = ReadPiixAta(QueuedCommand, AtaPort);
    return Result;
}

static LOUSINE_PCI_DEVICE_TABLE PiixPciDeviceTable[] = {
    //PATA Devices
    {.VendorID = 0x8086, .DeviceID = 0x7010 , .BoardID = PIIX_CONTROLLER_ID_PATA_MWDMA, .SimpleEntry = true},
    //{.VendorID = 0x8086, .DeviceID = 0x7111 , .SubVendorID = 0x15AD, .SubDeviceID = 0x1976, .BoardID = PIIX_CONTROLLER_ID_VMWARE, .AdvancedEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x7111 , .BoardID = PIIX_CONTROLLER_ID_PATA_33, .SimpleEntry = true},
    {0},
};

void UnloadDriver(PDRIVER_OBJECT Driver){

}

LOUSTATUS PiixInitializePiix3Xceleration(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost);
LOUSTATUS PiixInitializePiix4Xceleration(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost);

LOUDDK_API_ENTRY
NTSTATUS AddDevice(PDRIVER_OBJECT DriverObject, struct _DEVICE_OBJECT* PlatformDevice){
    LouPrint("PIIX.SYS:AddDevice()\n");
    PPCI_DEVICE_OBJECT PDEV = PlatformDevice->PDEV;
    LOUSTATUS Status;

    uint8_t DeviceID = PlatformDevice->DeviceID;
    PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost = LouKeDeviceManagerGetAtaDevice(PDEV);

    if(!AtaHost){
        LouPrint("PIIX.SYS:Error Controller Not In Ata Manager\n");
        return STATUS_NO_SUCH_DEVICE;
    }

    Status = LouKeHalEnablePciDevice(PDEV);
    if(Status != STATUS_SUCCESS){
        return (NTSTATUS)Status;
    }

    if(PiixPciDeviceTable[DeviceID].BoardID == PIIX_CONTROLLER_ID_PATA_MWDMA){
        Status = PiixInitializePiix3Xceleration(AtaHost);
    }else if(PiixPciDeviceTable[DeviceID].BoardID == PIIX_CONTROLLER_ID_PATA_33){
        Status = PiixInitializePiix4Xceleration(AtaHost);
        while(1);
    }else {
        Status = STATUS_NO_SUCH_DEVICE;
    }

    if(Status != STATUS_SUCCESS){
        LouPrint("PIIX.SYS:Error Unable To Initialize Acceleration\n");
        return Status;
    }

    for(size_t i = 0 ; i < 4; i++){
        AtaHost->Ports[i].Operations->IssueCommand = PiixDmaIssueCommand;
    }

    RegisterInterruptHandler(PiixPrimaryInterruptHandler, 0x20 + 14, false, (UINT64)AtaHost);
    RegisterInterruptHandler(PiixSecondryInterruptHandler, 0x20 + 15, false, (UINT64)AtaHost);

    LouPrint("PIIX.SYS:AddDevice() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
NTSTATUS DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryEntry
){

    LouPrint("PIIX.SYS:DriverEntry()\n");
    //tell the System where are key Nt driver functions are
    DriverObject->DriverExtension->AddDevice = AddDevice;
    DriverObject->DriverUnload = UnloadDriver;
    //tell the lousine kernel we will be using the
    //Lousine Kernel Driver Module (LKDM) alongside the
    //NT Kernel Moudle Subsystem so it fills
    //out the extra information relating to the LKDM
    DriverObject->DriverUsingLkdm = true;
    //fill LDM information
    DriverObject->DeviceTable = (uintptr_t)PiixPciDeviceTable;

    LouPrint("PIIX.SYS:DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

static const UINT8 PiixTimingModes[][2]{
    {IDETIM_ISP_5CLOCK, IDETIM_RTC_4CLOCK}, //Timing 0
    {IDETIM_ISP_5CLOCK, IDETIM_RTC_4CLOCK}, //Timing 1
    {IDETIM_ISP_5CLOCK, IDETIM_RTC_4CLOCK}, //Timing 2
    {IDETIM_ISP_5CLOCK, IDETIM_RTC_3CLOCK}, //Timing 3
    {IDETIM_ISP_5CLOCK, IDETIM_RTC_1CLOCK}, //Timing 4
};

LOUSTATUS PiixSetPioTiming(
    PLOUSINE_KERNEL_DEVICE_ATA_PORT Port,
    UINT8                           TimingMode
){
    PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost = Port->AtaHost; 
    BOOL MasterChannel = (Port->PortNumber < 3);
    BOOL SlaveDevice = ((Port->PortNumber == 2) || (Port->PortNumber == 4));
    PPCI_DEVICE_OBJECT PDEV = AtaHost->PDEV;
    UINT8 MasterTimingPort = SECONDARY_IDETIM_REGISTER_OFFSET;
    UINT8 SlaveTimeingPort = SIDETIM_REGISTER_OFFSET;
    UINT16 Control = 0;
    UINT16 MasterData = 0;
    UINT8 SlaveData = 0;

    if(TimingMode > ((PPIIX_HOST_PRIVATE_DATA)Port->PortPrivateData)->MaxPioMode){
        LouPrint("PIIX.SYS:ERROR Invalid Timing Mode Mode Too High\n");
        return STATUS_INVALID_PARAMETER;
    }

    if(MasterChannel){
        MasterTimingPort = PRIMARY_IDETIM_REGISTER_OFFSET;
    }

    if(TimingMode >= 2){
        Control |= IDETIM_TIME0;
    }

    Control |= IDETIM_IE0;

    if((Port->DeviceAttached) && (!Port->PortScsiDevice)){
        Control |= IDETIM_PPE0;
    }

    if(((PPIIX_HOST_PRIVATE_DATA)Port->PortPrivateData)->MaxDmaMode > TimingMode){
        Control |= IDETIM_DTE0;
    }
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&PiixLock, &Irql);

    MasterData = LouKeReadPciUint16(PDEV, MasterTimingPort);
    if(SlaveDevice){
        MasterData &= (0xFF0F);
        MasterData |= (Control << 4);
        SlaveData = LouKeReadPciUint8(PDEV, SlaveTimeingPort);
        SlaveData &= (MasterChannel ? 0xF0 : 0x0F);
        SlaveData |= ((((PiixTimingModes[TimingMode][0] & 0b11) << 2) | (PiixTimingModes[TimingMode][1] & 0b11)) << (MasterChannel ? 0 : 4));
    }else{
        MasterData &= (0xCCF0);
        MasterData |= Control;
        MasterData |= (((PiixTimingModes[TimingMode][0] & 0b11) << 12) | ((PiixTimingModes[TimingMode][1] & 0b11) << 8)); 
    }

    MasterData |= IDETIM_SITRE;

    LouKeWritePciUint16(PDEV, MasterTimingPort, MasterData);
    if(SlaveDevice){
        LouKeWritePciUint8(PDEV, SlaveTimeingPort, SlaveData);
    }

    if(((PPIIX_HOST_PRIVATE_DATA)Port->PortPrivateData)->UsesUDMA){
        LouPrint("TODO:UDMA Devices\n"); //Ill get to this when doing PIIX4
        while(1);
    }

    LouKeReleaseSpinLock(&PiixLock, &Irql);

    LouPrint("PIIX.SYS:Changed Device Timing To PIO:%d Mode\n", TimingMode);

    return STATUS_SUCCESS;
}
