#include "AtaIdeGeneric.h"

#define ATA_BOARD_ID_ISA_DEVICE_NO_DMA      0
#define ATA_BOARD_ID_NATIVE_DEVICE_NO_DMA   1
#define ATA_BOARD_ID_ISA_DEVICE_HAS_DMA     2
#define ATA_BOARD_ID_NATIVE_DEVICE_HAS_DMA  3

LOUSTATUS AtaGenericPortDeviceGetCommandStatus(PATA_PORT_DEVICE_OBJECT PortDevice, PATA_COMMAND_PACKET CommandPacket){
    PATA_GENERIC_PRIVATE_DATA PrivateData = (PATA_GENERIC_PRIVATE_DATA)(UINT8*)PortDevice->PortPrivateData;
    if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_EXT_CMD){
        CommandPacket->PacketEx.Status = inb(PrivateData->Ports.CmdSts);
        CommandPacket->PacketEx.Device = inb(PrivateData->Ports.Device);
        outb(PrivateData->Ports.AltDevSts, 0x00);
        CommandPacket->PacketEx.Error = ATA_CMDBLK_ENCODE_CURR_VALUE(inb(PrivateData->Ports.ErrFeat));
        CommandPacket->PacketEx.SectorCount = ATA_CMDBLK_ENCODE_CURR_VALUE(inb(PrivateData->Ports.SectorCount));
        CommandPacket->PacketEx.LbaLow = ATA_CMDBLK_ENCODE_CURR_VALUE(inb(PrivateData->Ports.LbaLow));
        CommandPacket->PacketEx.LbaMid = ATA_CMDBLK_ENCODE_CURR_VALUE(inb(PrivateData->Ports.LbaMid));
        CommandPacket->PacketEx.LbaHigh = ATA_CMDBLK_ENCODE_CURR_VALUE(inb(PrivateData->Ports.LbaHigh));
        outb(PrivateData->Ports.AltDevSts, 0x80);
        CommandPacket->PacketEx.Error |= ATA_CMDBLK_ENCODE_PREV_VALUE(inb(PrivateData->Ports.ErrFeat));
        CommandPacket->PacketEx.SectorCount |= ATA_CMDBLK_ENCODE_PREV_VALUE(inb(PrivateData->Ports.SectorCount));
        CommandPacket->PacketEx.LbaLow |= ATA_CMDBLK_ENCODE_PREV_VALUE(inb(PrivateData->Ports.LbaLow));
        CommandPacket->PacketEx.LbaMid |= ATA_CMDBLK_ENCODE_PREV_VALUE(inb(PrivateData->Ports.LbaMid));
        CommandPacket->PacketEx.LbaHigh |= ATA_CMDBLK_ENCODE_PREV_VALUE(inb(PrivateData->Ports.LbaHigh));
        outb(PrivateData->Ports.AltDevSts, 0x00);
    }else{
        CommandPacket->Packet.Status = inb(PrivateData->Ports.CmdSts);
        CommandPacket->Packet.Error = inb(PrivateData->Ports.ErrFeat);
        CommandPacket->Packet.SectorCount = inb(PrivateData->Ports.SectorCount);
        CommandPacket->Packet.LbaLow = inb(PrivateData->Ports.LbaLow);
        CommandPacket->Packet.LbaMid = inb(PrivateData->Ports.LbaMid);
        CommandPacket->Packet.LbaHigh = inb(PrivateData->Ports.LbaHigh);
        CommandPacket->Packet.Device = inb(PrivateData->Ports.Device);
    }
    return STATUS_SUCCESS;
}
    

LOUSTATUS AtaGenericPortDevicePrepCommand(PATA_PORT_DEVICE_OBJECT PortDevice, PATA_COMMAND_PACKET CommandPacket){
    PATA_GENERIC_PRIVATE_DATA PrivateData = (PATA_GENERIC_PRIVATE_DATA)(UINT8*)PortDevice->PortPrivateData;
    if(!(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_DMA)){
        return STATUS_SUCCESS;
    }
    PLOUSINE_DMA_TRANSFER DmaTransfer;
    PLOUSINE_DMA_DEVICE DmaDevice;
    PATA_PRDT_ENTRY NewPrdEntry;
    if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_OUT_CMD){
        DmaTransfer = CommandPacket->DmaDataOut;
    }else{
        DmaTransfer = CommandPacket->DmaDataIn;
    }
    DmaDevice = DmaTransfer->DmaDevice;
    NewPrdEntry = (PATA_PRDT_ENTRY)(UINT8*)LouKeDmaDeviceAllocateDmaMemory(DmaDevice, sizeof(ATA_PRDT_ENTRY), MAX(GET_ALIGNMENT(ATA_PRDT_ENTRY) , ATA_PRDT_ALIGNMENT));
    NewPrdEntry->DmaAddress = DmaTransfer->DmaAddress;
    NewPrdEntry->DmaSize = DmaTransfer->DmaSize;
    if(NewPrdEntry->DmaSize == (64 * KILOBYTE)){
        NewPrdEntry->DmaSize = 0;
    }
    NewPrdEntry->Edt = ATA_PRDT_EDT_VALUE;
    DmaTransfer->PrivateData = (PVOID)(UINT8*)NewPrdEntry;
    return STATUS_SUCCESS;
}
    
LOUSTATUS AtaGenericPortDeviceIssueCommand(PATA_PORT_DEVICE_OBJECT PortDevice, PATA_COMMAND_PACKET CommandPacket){
    PATA_GENERIC_PRIVATE_DATA PrivateData = (PATA_GENERIC_PRIVATE_DATA)(UINT8*)PortDevice->PortPrivateData;
    UINT8 Foo = inb(PrivateData->Ports.CmdSts);
    UINT8 BmCommand;
    if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_EXT_CMD){
        outb(PrivateData->Ports.Device, CommandPacket->PacketEx.Device);   
    }else{
        outb(PrivateData->Ports.Device, CommandPacket->Packet.Device);   
    }

    sleep(1);

    SIZE Timeout = 1000;

    while(inb(PrivateData->Ports.CmdSts) & 0x80){
        sleep(1);
        Timeout--;
    }
    if(!Timeout){
        return STATUS_IO_DEVICE_ERROR;
    }

    if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_DMA){
        outb(PrivateData->Ports.BusMasterCmd, 0x00);
        outb(PrivateData->Ports.BusMasterSts, 0x06);
        BmCommand = 0;
        UINT64  PhysicalPrdt;
        UINT64  VirtualPrdt;
        if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_OUT_CMD){
            VirtualPrdt = (UINT64)(UINT8*)CommandPacket->DmaDataOut->PrivateData;
        }else{
            VirtualPrdt = (UINT64)(UINT8*)CommandPacket->DmaDataIn->PrivateData;
            BmCommand = (1 << 3); 
        }
        RequestPhysicalAddress(VirtualPrdt, &PhysicalPrdt);
        outl(PrivateData->Ports.BusMasterPrd, PhysicalPrdt);
        outb(PrivateData->Ports.BusMasterCmd, BmCommand);
    }

    if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_EXT_CMD){
        outb(PrivateData->Ports.SectorCount, ATA_CMDBLK_DECODE_PREV_VALUE(CommandPacket->PacketEx.SectorCount));
        outb(PrivateData->Ports.ErrFeat, ATA_CMDBLK_DECODE_PREV_VALUE(CommandPacket->PacketEx.Features));
        outb(PrivateData->Ports.LbaLow, ATA_CMDBLK_DECODE_PREV_VALUE(CommandPacket->PacketEx.LbaLow));   
        outb(PrivateData->Ports.LbaMid, ATA_CMDBLK_DECODE_PREV_VALUE(CommandPacket->PacketEx.LbaMid));   
        outb(PrivateData->Ports.LbaHigh, ATA_CMDBLK_DECODE_PREV_VALUE(CommandPacket->PacketEx.LbaHigh));   

        outb(PrivateData->Ports.SectorCount, ATA_CMDBLK_DECODE_CURR_VALUE(CommandPacket->PacketEx.SectorCount));
        outb(PrivateData->Ports.ErrFeat, ATA_CMDBLK_DECODE_CURR_VALUE(CommandPacket->PacketEx.Features));
        outb(PrivateData->Ports.LbaLow, ATA_CMDBLK_DECODE_CURR_VALUE(CommandPacket->PacketEx.LbaLow));   
        outb(PrivateData->Ports.LbaMid, ATA_CMDBLK_DECODE_CURR_VALUE(CommandPacket->PacketEx.LbaMid));   
        outb(PrivateData->Ports.LbaHigh, ATA_CMDBLK_DECODE_CURR_VALUE(CommandPacket->PacketEx.LbaHigh));   
        outb(PrivateData->Ports.CmdSts, CommandPacket->PacketEx.Command); 

    }else{
        outb(PrivateData->Ports.SectorCount, CommandPacket->Packet.SectorCount);
        outb(PrivateData->Ports.ErrFeat, CommandPacket->Packet.Features);
        outb(PrivateData->Ports.LbaLow, CommandPacket->Packet.LbaLow);   
        outb(PrivateData->Ports.LbaMid, CommandPacket->Packet.LbaMid);   
        outb(PrivateData->Ports.LbaHigh, CommandPacket->Packet.LbaHigh);   
        outb(PrivateData->Ports.CmdSts, CommandPacket->Packet.Command);   
    }
    
    sleep(1);

    if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_PACKET_CMD){
        Timeout = 1000;
        UINT8 Status;
        while(1){
            Status = inb(PrivateData->Ports.CmdSts);
            
            if((!(Status & 0x80)) && (Status & 0x08)){
                break;
            }
            
            if(Status & 0x01){
                return STATUS_IO_DEVICE_ERROR;
            }

            if(!Timeout){
                return STATUS_TIMEOUT;
            }

            sleep(1);
            Timeout--;
        }
        outsw(PrivateData->Ports.Data, CommandPacket->PacketData, CommandPacket->PacketSize / 2);
        sleep(1);
    }
    
    if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_DMA){
        BmCommand = inb(PrivateData->Ports.BusMasterCmd);
        outb(PrivateData->Ports.BusMasterCmd, BmCommand | 0x01);
    }

    return STATUS_SUCCESS;
}
    
LOUSTATUS AtaGenericPortDeviceCleanupCommand(PATA_PORT_DEVICE_OBJECT PortDevice, PATA_COMMAND_PACKET CommandPacket){
    PATA_GENERIC_PRIVATE_DATA PrivateData = (PATA_GENERIC_PRIVATE_DATA)(UINT8*)PortDevice->PortPrivateData;
    SIZE Timeout = 100;
    if(!(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_DMA)){
        if(CommandPacket->CommandStatus == STATUS_SUCCESS){
            if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_TRAN_CMD){
                UINT8 Status;
                if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_EXT_CMD){
                    Status = CommandPacket->PacketEx.Status;
                }else{
                    Status = CommandPacket->Packet.Status;
                }
                if((!(Status & 0x08)) || (Status & 0x01)){
                    goto _PIO_TRANSFER_DONE;
                }   
                if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_OUT_CMD){
                    outsw(PrivateData->Ports.Data, CommandPacket->PioDataOut, CommandPacket->PioSize);
                }else{
                    insw(PrivateData->Ports.Data, CommandPacket->PioDataIn, CommandPacket->PioSize);
                }
            }
            _PIO_TRANSFER_DONE:
            return STATUS_SUCCESS;
        }else{
            return STATUS_SUCCESS;
        }
    }
    PLOUSINE_DMA_TRANSFER DmaTransfer;
    PLOUSINE_DMA_DEVICE DmaDevice;
    if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_OUT_CMD){
        DmaTransfer = CommandPacket->DmaDataOut;
    }else{
        DmaTransfer = CommandPacket->DmaDataIn;
    }
    DmaDevice = DmaTransfer->DmaDevice;

    UINT8 BmCommand = inb(PrivateData->Ports.BusMasterCmd);
    outb(PrivateData->Ports.BusMasterCmd, BmCommand & ~(0x01));
    outb(PrivateData->Ports.BusMasterSts, 0x06);
    LouKeDmaDeviceFreeDmaMemory(DmaDevice, DmaTransfer->PrivateData);
    return STATUS_SUCCESS;
}

static LOUSINE_DMA_DEVICE PciIdeBusMasterDevice = {
    .AllocatorData = {
        .DmaLimit = 32,
        .DmaThreshold = 64 * KILOBYTE,
    },
};

static ATA_PORT_OPERATIONS PortOperations = {
    .AtaPortDevicePrepCommand = AtaGenericPortDevicePrepCommand,
    .AtaPortDeviceIssueCommand = AtaGenericPortDeviceIssueCommand,
    .AtaPortDeviceGetCommandStatus = AtaGenericPortDeviceGetCommandStatus,
    .AtaPortDeviceCleanupCommand = AtaGenericPortDeviceCleanupCommand,
//    .AtaPortDeviceReset = AtaGenericPortDeviceReset,
//    .AtaPortDeviceStart = AtaGenericPortDeviceStart,
//    .AtaPortDeviceStop = AtaGenericPortDeviceStop,
//    .AtaPortDeviceWake = AtaGenericPortDeviceWake,
//    .AtaPortDeviceSleep = AtaGenericPortDeviceSleep,
//    .AtaPortDevicePowerUp = AtaGenericPortDevicePowerUp,
//    .AtaPortDevicePowerDown = AtaGenericPortDevicePowerDown,
};

static ATA_HOST_OPERATIONS AtaOperations = {
//    .AtaHostDeviceReset = AtaGenericHostDeviceReset,
//    .AtaHostDeviceStart = AtaGenericHostDeviceStart,
//    .AtaHostDeviceStop = AtaGenericHostDeviceStop,
//    .AtaHostDeviceWake = AtaGenericHostDeviceWake,
//    .AtaHostDeviceSleep = AtaGenericHostDeviceSleep,
//    .AtaHostDevicePowerUp = AtaGenericHostDevicePowerUp,
//    .AtaHostDevicePowerDown = AtaGenericHostDevicePowerDown,
};

static LOUSINE_PCI_DEVICE_TABLE AtaDevices[] = {
    //Generic ATA devices
    //NO DMA Devs
    {.BaseClass = 0x01, .SubClass = 0x01, .ProgIf = 0x00, .BoardID = ATA_BOARD_ID_ISA_DEVICE_NO_DMA, .GenericEntry = true},
    {.BaseClass = 0x01, .SubClass = 0x01, .ProgIf = 0x05, .BoardID = ATA_BOARD_ID_NATIVE_DEVICE_NO_DMA, .GenericEntry = true},
    {.BaseClass = 0x01, .SubClass = 0x01, .ProgIf = 0x0A, .BoardID = ATA_BOARD_ID_ISA_DEVICE_NO_DMA, .GenericEntry = true},
    {.BaseClass = 0x01, .SubClass = 0x01, .ProgIf = 0x0F, .BoardID = ATA_BOARD_ID_NATIVE_DEVICE_NO_DMA, .GenericEntry = true},
    //DMA Devs
    {.BaseClass = 0x01, .SubClass = 0x01, .ProgIf = 0x80, .BoardID = ATA_BOARD_ID_ISA_DEVICE_HAS_DMA, .GenericEntry = true},
    {.BaseClass = 0x01, .SubClass = 0x01, .ProgIf = 0x85, .BoardID = ATA_BOARD_ID_NATIVE_DEVICE_HAS_DMA, .GenericEntry = true},
    {.BaseClass = 0x01, .SubClass = 0x01, .ProgIf = 0x8A, .BoardID = ATA_BOARD_ID_ISA_DEVICE_HAS_DMA, .GenericEntry = true},
    {.BaseClass = 0x01, .SubClass = 0x01, .ProgIf = 0x8F, .BoardID = ATA_BOARD_ID_NATIVE_DEVICE_HAS_DMA, .GenericEntry = true},
};

//DRIVER_EXPORT LOUSTATUS AtaCoreAllocatePortsForHost(
//    PATA_HOST_DEVICE_OBJECT HostDevice,
//    SIZE                    PortCount,
//    SIZE                    PrivateDataSize,
//    SIZE                    PrivateDataAlignment
//);

//DRIVER_EXPORT LOUSTATUS AtaCoreAllocateHostDevice(
//    PATA_HOST_DEVICE_OBJECT*    HostDeviceOut,
//    SIZE                        PrivateDataSize,
//    SIZE                        PrivateDataAlignment
//);

LOUSTATUS AddAtaDevice(
    PDRIVER_OBJECT DriverObject,
    struct _DEVICE_OBJECT* Device
){
    LouPrint("ATA.SYS:AddAtaDevice()\n");
    LOUSTATUS Status;
    PPCI_DEVICE_OBJECT PDEV = PciHalGetPciDeviceObjectFromLdmDeviceObject(Device);
    SIZE i;
    PciHalEnableIoSpace(PDEV);
    PciHalEnableMemorySpace(PDEV);

    for(SIZE i = 0 ; i < 4; i++){
        Status = PciHalMapPciResource(
            PDEV, 
            i, 
            PCI_IOMAP_FLAGS_DEFAULT_MAPPING
        );
        if(Status != STATUS_SUCCESS){
            LouPrint("ATA.SYS:AddAtaDevice() Failed To Allocate PCI Resource\n");
            while(1);
        }
    }

    SIZE BoardID = AtaDevices[PDEV->DeviceID].BoardID;

    LouPrint("ATA.SYS:BoardID:%d\n", (UINT64)BoardID);
    PATA_HOST_DEVICE_OBJECT NewHostDevice;    
    
    Status = AtaCoreAllocateHostDevice(&NewHostDevice, 0, 0);
    if(Status != STATUS_SUCCESS){
        LouPrint("ATA.SYS:AddAtaDevice() Failed To Allocate Host\n");
        while(1);
    }
        
    Status = AtaCoreAllocatePortsForHost(NewHostDevice, 2, sizeof(ATA_GENERIC_PRIVATE_DATA), GET_ALIGNMENT(ATA_GENERIC_PRIVATE_DATA));
    if(Status != STATUS_SUCCESS){
        LouPrint("ATA.SYS:AddAtaDevice() Failed To Allocate Ports\n");
        while(1);
    }

    NewHostDevice->Operations = &AtaOperations;
   

    NewHostDevice->HostFlags = ATA_HOST_FLAGS_SUPPORTS_PIO | ATA_HOST_FLAGS_DUAL_CHANNEL;
    if((BoardID == ATA_BOARD_ID_ISA_DEVICE_HAS_DMA) || (BoardID == ATA_BOARD_ID_NATIVE_DEVICE_HAS_DMA)){
        NewHostDevice->HostFlags |= ATA_HOST_FLAGS_SUPPORTS_DMA;
    }
    
    UINT16 CommandBlock[2];
    UINT16 AltDevSts[2];
    UINT16 BusMaster = 0x00;
    if((BoardID == ATA_BOARD_ID_NATIVE_DEVICE_HAS_DMA) || (BoardID == ATA_BOARD_ID_NATIVE_DEVICE_NO_DMA)){
        CommandBlock[0] = (UINT16)(UINTPTR)PciHalGetIoRegion(PDEV, 0, 0); 
        CommandBlock[1] = (UINT16)(UINTPTR)PciHalGetIoRegion(PDEV, 2, 0);
        AltDevSts[0] = ATA_PCICTL_ALTDEVSTS_OFFSET(PciHalGetIoRegion(PDEV, 1, 0));
        AltDevSts[1] = ATA_PCICTL_ALTDEVSTS_OFFSET(PciHalGetIoRegion(PDEV, 3, 0));
        if(BoardID == ATA_BOARD_ID_NATIVE_DEVICE_HAS_DMA){
            BusMaster = (UINT16)(UINTPTR)PciHalGetIoRegion(PDEV, 4, 0);
        }
    }else{
        CommandBlock[0] = 0x01F0; 
        CommandBlock[1] = 0x0170;
        AltDevSts[0] = ATA_ISACTL_ALTDEVSTS_OFFSET(0x03F6);
        AltDevSts[1] = ATA_ISACTL_ALTDEVSTS_OFFSET(0x0376);
        if(BoardID == ATA_BOARD_ID_ISA_DEVICE_HAS_DMA){
            BusMaster = (UINT16)(UINTPTR)PciHalGetIoRegion(PDEV, 4, 0);
        }
    }

    PATA_PORT_DEVICE_OBJECT TmpPort;
    ForEachAtaPort(NewHostDevice, TmpPort, i){
        PATA_GENERIC_PRIVATE_DATA GenericData = (PATA_GENERIC_PRIVATE_DATA)(UINT8*)TmpPort->PortPrivateData;
        TmpPort->Operations = &PortOperations;
        GenericData->Ports.Data = ATA_GENCMD_DATA_OFFSET(CommandBlock[i]);
        GenericData->Ports.ErrFeat = ATA_GENCMD_ERRFEAT_OFFSET(CommandBlock[i]);
        GenericData->Ports.SectorCount = ATA_GENCMD_SECTORCOUNT_OFFSET(CommandBlock[i]);
        GenericData->Ports.LbaLow = ATA_GENCMD_LBALOW_OFFSET(CommandBlock[i]);
        GenericData->Ports.LbaMid = ATA_GENCMD_LBAMID_OFFSET(CommandBlock[i]);
        GenericData->Ports.LbaHigh = ATA_GENCMD_LBAHIGH_OFFSET(CommandBlock[i]);
        GenericData->Ports.Device = ATA_GENCMD_DEVICE_OFFSET(CommandBlock[i]);
        GenericData->Ports.CmdSts = ATA_GENCMD_CMDSTS_OFFSET(CommandBlock[i]);
        GenericData->Ports.AltDevSts = AltDevSts[i];
        if(BusMaster){
            GenericData->Ports.BusMasterCmd = BusMaster + (ATA_BM_SEC_IDE_CMD_REG_OFFSET * i) + ATA_BM_PRI_IDE_CMD_REG_OFFSET;
            GenericData->Ports.BusMasterSts = BusMaster + (ATA_BM_SEC_IDE_CMD_REG_OFFSET * i) + ATA_BM_PRI_IDE_STS_REG_OFFSET;
            GenericData->Ports.BusMasterPrd = BusMaster + (ATA_BM_SEC_IDE_CMD_REG_OFFSET * i) + ATA_BM_PRI_IDE_PRD_REG_OFFSET;
            TmpPort->OptionalDmaDevice = &PciIdeBusMasterDevice;
        }
    
    }

    Status = AtaCoreRegisterAtaHostDevice(NewHostDevice);
    if(Status != STATUS_SUCCESS){
        LouPrint("ATA.SYS:AddAtaDevice() Could Not Register ATA Host Device\n");
        while(1);
    }

    LouPrint("ATA.SYS:AddAtaDevice() STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS; //Status;
}


VOID AtaUnloadDriver(
    PDRIVER_OBJECT DriverObject
){
    LouPrint("ATA.SYS:AtaUnloadDriver()\n");
    //this is a dummy function due to the module
    //being built in there is nothing to unload
    LouPrint("ATA.SYS:AtaUnloadDriver() RETURN\n");
}

LOUAPI
LOUSTATUS 
DriverEntry(
    PDRIVER_OBJECT  DriverObject, 
    PUNICODE_STRING RegistryEntry
){
    LouPrint("ATA.SYS:DriverEntry()\n");

    //tell the System where are key Nt driver functions are
    DriverObject->DriverUnload = AtaUnloadDriver;
    DriverObject->DriverExtension->AddDevice = AddAtaDevice;

    LOUSTATUS Status = PciHalRegisterLousinePciDeviceTable(DriverObject, AtaDevices);
    if(Status != STATUS_SUCCESS){
        LouPrint("ATA.SYS:DriverEntry():ERROR Unable To Register Pci Device Table\n");
    }
    
    LouPrint("ATA.SYS:DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}