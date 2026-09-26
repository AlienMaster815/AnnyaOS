#include "AtaIdeGeneric.h"

#define ATA_BOARD_ID_ISA_DEVICE_NO_DMA      0
#define ATA_BOARD_ID_NATIVE_DEVICE_NO_DMA   1
#define ATA_BOARD_ID_ISA_DEVICE_HAS_DMA     2
#define ATA_BOARD_ID_NATIVE_DEVICE_HAS_DMA  3

#define ATA_IDE_COMMAND_GRACE_PERIOD        10000

void AtaGeneric400NsDelay(PATA_GENERIC_PRIVATE_DATA PrivateData){
    inb(PrivateData->Ports.AltDevSts);
    inb(PrivateData->Ports.AltDevSts);
    inb(PrivateData->Ports.AltDevSts);
    inb(PrivateData->Ports.AltDevSts);
}

LOUSTATUS AtaPortDeviceGetDeviceType(PATA_PORT_DEVICE_OBJECT PortDevice, SIZE Dev, ATA_DEVICE_TYPE* Type){
    if((!PortDevice) || (!Type) || (Dev > 1)){
        return STATUS_INVALID_PARAMETER;
    }
    PATA_GENERIC_PRIVATE_DATA PrivateData = (PATA_GENERIC_PRIVATE_DATA)PortDevice->PortPrivateData;
    SIZE    Timeout;
    UINT8   Status;
    UINT16  SigLo;    
    UINT16  SigHi;
    UINT16  Sig;
    UINT8   Device = 0xA0 | (Dev << 4);
    
    outb(PrivateData->Ports.Device, Device);
    AtaGeneric400NsDelay(PrivateData);

    Status = inb(PrivateData->Ports.CmdSts);
    if(
        (Status == 0xFF) || 
        (Status == 0x7F) || 
        (!Status)
    ){
        *Type = ATA_DEVICE_TYPE_NO_DEVICE;
        return STATUS_SUCCESS;
    }

    outb(PrivateData->Ports.AltDevSts, 0x04);
    AtaGeneric400NsDelay(PrivateData);
    outb(PrivateData->Ports.AltDevSts, 0x00);

    Timeout = 10000;
    while(Timeout--){
        Status = inb(PrivateData->Ports.CmdSts);
        if((Status & (1 << 6)) && (!(Status & (1 <<  7)))){
            break;
        }
        AtaGeneric400NsDelay(PrivateData);
    }
    if(!Timeout){
        return STATUS_TIMEOUT;
    }

    outb(PrivateData->Ports.Device, Device);
    AtaGeneric400NsDelay(PrivateData);
    SigLo = inb(PrivateData->Ports.LbaMid);
    SigHi = inb(PrivateData->Ports.LbaHigh);
    Sig = SigLo | (SigHi << 8);
    LouPrint("SIG:%h\n", Sig);
    switch(Sig){
        case 0:
            *Type = ATA_DEVICE_TYPE_ATA_DEVICE; 
            break;
        case 0xEB14:
            *Type = ATA_DEVICE_TYPE_ATAPI_DEVICE;
            break;
        case 0xC33C:
            *Type = ATA_DEVICE_TYPE_SATA_DEVICE;
            break;
        case 0x9669:
            *Type = ATA_DEVICE_TYPE_SATAPI_DEVICE;
            break;
        default:
            return STATUS_UNSUCCESSFUL;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS AtaGenericPortDeviceGetCommandStatus(PATA_PORT_DEVICE_OBJECT PortDevice, PATA_COMMAND_PACKET CommandPacket){
    PATA_GENERIC_PRIVATE_DATA PrivateData = (PATA_GENERIC_PRIVATE_DATA)(UINT8*)PortDevice->PortPrivateData;
    if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_EXT_CMD){
        CommandPacket->PacketEx.Status = inb(PrivateData->Ports.CmdSts);
        CommandPacket->PacketEx.Device = inb(PrivateData->Ports.Device);
        outb(PrivateData->Ports.AltDevSts, 0x00);
        AtaGeneric400NsDelay(PrivateData);
        CommandPacket->PacketEx.Error = ATA_CMDBLK_ENCODE_CURR_VALUE(inb(PrivateData->Ports.ErrFeat));
        CommandPacket->PacketEx.SectorCount = ATA_CMDBLK_ENCODE_CURR_VALUE(inb(PrivateData->Ports.SectorCount));
        CommandPacket->PacketEx.LbaLow = ATA_CMDBLK_ENCODE_CURR_VALUE(inb(PrivateData->Ports.LbaLow));
        CommandPacket->PacketEx.LbaMid = ATA_CMDBLK_ENCODE_CURR_VALUE(inb(PrivateData->Ports.LbaMid));
        CommandPacket->PacketEx.LbaHigh = ATA_CMDBLK_ENCODE_CURR_VALUE(inb(PrivateData->Ports.LbaHigh));
        outb(PrivateData->Ports.AltDevSts, 0x80);
        AtaGeneric400NsDelay(PrivateData);
        CommandPacket->PacketEx.Error |= ATA_CMDBLK_ENCODE_PREV_VALUE(inb(PrivateData->Ports.ErrFeat));
        CommandPacket->PacketEx.SectorCount |= ATA_CMDBLK_ENCODE_PREV_VALUE(inb(PrivateData->Ports.SectorCount));
        CommandPacket->PacketEx.LbaLow |= ATA_CMDBLK_ENCODE_PREV_VALUE(inb(PrivateData->Ports.LbaLow));
        CommandPacket->PacketEx.LbaMid |= ATA_CMDBLK_ENCODE_PREV_VALUE(inb(PrivateData->Ports.LbaMid));
        CommandPacket->PacketEx.LbaHigh |= ATA_CMDBLK_ENCODE_PREV_VALUE(inb(PrivateData->Ports.LbaHigh));
        outb(PrivateData->Ports.AltDevSts, 0x00);
        AtaGeneric400NsDelay(PrivateData);
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

static void InitializeGenericAtaSgElement(
    PLOUSINE_DMA_TRANSFER   DmaTransfer,
    PATA_PRDT_ENTRY*        AtaSg         
){
    PLOUSINE_DMA_DEVICE DmaDevice = DmaTransfer->DmaDevice;
    PATA_PRDT_ENTRY     NewPrdEntry;
    SIZE                TransferCount = 1;
    if(DmaTransfer->Type == LOUSINE_DMA_TRANSFER_TYPE_SCATTERED){
        LouPrint("ATA.SYS:InitializeGenericAtaSgElement()\n");
        while(1);
    }

    NewPrdEntry = (PATA_PRDT_ENTRY)(UINT8*)LouKeDmaDeviceAllocateDmaMemory(DmaDevice, sizeof(ATA_PRDT_ENTRY), MAX(GET_ALIGNMENT(ATA_PRDT_ENTRY) , ATA_PRDT_ALIGNMENT));
    NewPrdEntry->DmaAddress = DmaTransfer->StandardTransfer.DmaAddress;
    NewPrdEntry->DmaSize = DmaTransfer->StandardTransfer.DmaSize;
    if(NewPrdEntry->DmaSize == (64 * KILOBYTE)){
        NewPrdEntry->DmaSize = 0;
    }
    NewPrdEntry->Edt = ATA_PRDT_EDT_VALUE;
    *AtaSg = (PATA_PRDT_ENTRY)(UINT8*)NewPrdEntry;
}

LOUSTATUS AtaGenericPortDevicePrepCommand(PATA_PORT_DEVICE_OBJECT PortDevice, PATA_COMMAND_PACKET CommandPacket){
    PATA_GENERIC_PRIVATE_DATA PrivateData = (PATA_GENERIC_PRIVATE_DATA)(UINT8*)PortDevice->PortPrivateData;
    if(!(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_DMA)){
        return STATUS_SUCCESS;
    }
    PLOUSINE_DMA_TRANSFER DmaTransfer;
    PATA_PRDT_ENTRY NewPrdEntry;
    if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_OUT_CMD){
        DmaTransfer = CommandPacket->DmaDataOut;
    }else{
        DmaTransfer = CommandPacket->DmaDataIn;
    }
    InitializeGenericAtaSgElement(DmaTransfer, &NewPrdEntry);
    DmaTransfer->PrivateData = NewPrdEntry;
    return STATUS_SUCCESS;
}
 
void AtaGenericSetTaskFile(PATA_PORT_DEVICE_OBJECT PortDevice, PATA_COMMAND_PACKET CommandPacket){
    PATA_GENERIC_PRIVATE_DATA PrivateData = (PATA_GENERIC_PRIVATE_DATA)(UINT8*)PortDevice->PortPrivateData;
    if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_EXT_CMD){
        outb(PrivateData->Ports.Device, CommandPacket->PacketEx.Device);
        AtaGeneric400NsDelay(PrivateData);
        outb(PrivateData->Ports.ErrFeat, ATA_CMDBLK_DECODE_PREV_VALUE(CommandPacket->PacketEx.Features));
        outb(PrivateData->Ports.SectorCount, ATA_CMDBLK_DECODE_PREV_VALUE(CommandPacket->PacketEx.SectorCount));
        outb(PrivateData->Ports.LbaLow, ATA_CMDBLK_DECODE_PREV_VALUE(CommandPacket->PacketEx.LbaLow));
        outb(PrivateData->Ports.LbaMid, ATA_CMDBLK_DECODE_PREV_VALUE(CommandPacket->PacketEx.LbaMid));
        outb(PrivateData->Ports.LbaHigh, ATA_CMDBLK_DECODE_PREV_VALUE(CommandPacket->PacketEx.LbaHigh));
        AtaGeneric400NsDelay(PrivateData);
        outb(PrivateData->Ports.ErrFeat, ATA_CMDBLK_DECODE_CURR_VALUE(CommandPacket->PacketEx.Features));
        outb(PrivateData->Ports.SectorCount, ATA_CMDBLK_DECODE_CURR_VALUE(CommandPacket->PacketEx.SectorCount));
        outb(PrivateData->Ports.LbaLow, ATA_CMDBLK_DECODE_CURR_VALUE(CommandPacket->PacketEx.LbaLow));
        outb(PrivateData->Ports.LbaMid, ATA_CMDBLK_DECODE_CURR_VALUE(CommandPacket->PacketEx.LbaMid));
        outb(PrivateData->Ports.LbaHigh, ATA_CMDBLK_DECODE_CURR_VALUE(CommandPacket->PacketEx.LbaHigh));
        AtaGeneric400NsDelay(PrivateData);
        outb(PrivateData->Ports.CmdSts, CommandPacket->Packet.Command);
    }else{
        outb(PrivateData->Ports.Device, CommandPacket->Packet.Device);
        AtaGeneric400NsDelay(PrivateData);
        outb(PrivateData->Ports.ErrFeat, CommandPacket->Packet.Features);
        outb(PrivateData->Ports.SectorCount, CommandPacket->Packet.SectorCount);
        outb(PrivateData->Ports.LbaLow, CommandPacket->Packet.LbaLow);
        outb(PrivateData->Ports.LbaMid, CommandPacket->Packet.LbaMid);
        outb(PrivateData->Ports.LbaHigh, CommandPacket->Packet.LbaHigh);
        AtaGeneric400NsDelay(PrivateData);
        outb(PrivateData->Ports.CmdSts, CommandPacket->Packet.Command);
    }
    AtaGeneric400NsDelay(PrivateData);
}

LOUSTATUS AtaGenericPortDeviceIssuePioCommand(PATA_PORT_DEVICE_OBJECT PortDevice, PATA_COMMAND_PACKET CommandPacket){
    PATA_GENERIC_PRIVATE_DATA PrivateData = (PATA_GENERIC_PRIVATE_DATA)(UINT8*)PortDevice->PortPrivateData;
    SIZE Timeout = ATA_IDE_COMMAND_GRACE_PERIOD;
    UINT8 Status;
    SIZE TransferDone = 0;
    SIZE tSize;

    AtaGenericSetTaskFile(PortDevice, CommandPacket);

    Timeout = ATA_IDE_COMMAND_GRACE_PERIOD;
    while(Timeout--){
        Status = inb(PrivateData->Ports.CmdSts);
        if(Status & 1){
            return STATUS_IO_DEVICE_ERROR;
        }
        if(!(Status & (1 << 7)) && (Status & (1 << 3))) {
            break;
        }
        AtaGeneric400NsDelay(PrivateData);
    }
    if(!Timeout){
        return STATUS_TIMEOUT;
    }
 

    if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_PACKET_CMD){
        outsw(PrivateData->Ports.Data, CommandPacket->PacketData, CommandPacket->PacketSize / 2);
    }

    Timeout = ATA_IDE_COMMAND_GRACE_PERIOD;
    if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_TRAN_CMD){
        tSize = (CommandPacket->SectorSize ? CommandPacket->SectorSize : 512);
        if(CommandPacket->PioSize < tSize){
            tSize = CommandPacket->PioSize;
        }
        while(TransferDone < CommandPacket->PioSize){
            Timeout = ATA_IDE_COMMAND_GRACE_PERIOD;
            while(Timeout--){
                Status = inb(PrivateData->Ports.CmdSts);
                if(Status & 1){
                    return STATUS_IO_DEVICE_ERROR;
                }
                if(!(Status & (1 << 7)) && (Status & (1 << 3))) {
                    break;
                }
                AtaGeneric400NsDelay(PrivateData);
            }
            if(!Timeout){
                return STATUS_TIMEOUT;
            }
            if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_OUT_CMD){
                outsw(PrivateData->Ports.Data, (UINT16*)((UINT8*)CommandPacket->PioDataOut + TransferDone), tSize / 2);
            }else{
                insw(PrivateData->Ports.Data, (UINT16*)((UINT8*)CommandPacket->PioDataIn + TransferDone), tSize / 2);
            }
            TransferDone += tSize;
        }
    }    
    return STATUS_SUCCESS;
}

LOUSTATUS AtaGenericPortDeviceIssueCommand(PATA_PORT_DEVICE_OBJECT PortDevice, PATA_COMMAND_PACKET CommandPacket){
    PATA_GENERIC_PRIVATE_DATA PrivateData = (PATA_GENERIC_PRIVATE_DATA)(UINT8*)PortDevice->PortPrivateData;
    if(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_DMA){
        LouPrint("ATA>SYS:AtaGenericPortDeviceIssueCommand():HERE\n"); //not doing dma yet
        while(1);
    }
    return AtaGenericPortDeviceIssuePioCommand(PortDevice, CommandPacket);
}
    
LOUSTATUS AtaGenericPortDeviceCleanupCommand(PATA_PORT_DEVICE_OBJECT PortDevice, PATA_COMMAND_PACKET CommandPacket){
    PATA_GENERIC_PRIVATE_DATA PrivateData = (PATA_GENERIC_PRIVATE_DATA)(UINT8*)PortDevice->PortPrivateData;
    if(!(CommandPacket->CommandFlags & ATA_COMMAND_PACKET_FLAGS_DMA)){
        return STATUS_SUCCESS;
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
    .DmaDeviceFlags = LOUSINE_DMA_DEVICE_FLAGS_SCATTER_DMA_SUPPORTED,
    .MaxScatterCount = 8320,
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
    .AtaPortDeviceGetDeviceType = AtaPortDeviceGetDeviceType,
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

    for(SIZE i = 0 ; i < 5; i++){
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
            if(BusMaster){
                NewHostDevice->HostFlags |= ATA_HOST_FLAGS_SUPPORTS_DMA;
            }
        }
    }else{
        CommandBlock[0] = 0x01F0; 
        CommandBlock[1] = 0x0170;
        AltDevSts[0] = ATA_ISACTL_ALTDEVSTS_OFFSET(0x03F6);
        AltDevSts[1] = ATA_ISACTL_ALTDEVSTS_OFFSET(0x0376);
        if(BoardID == ATA_BOARD_ID_ISA_DEVICE_HAS_DMA){
            BusMaster = (UINT16)(UINTPTR)PciHalGetIoRegion(PDEV, 4, 0);
            if(BusMaster){
                NewHostDevice->HostFlags |= ATA_HOST_FLAGS_SUPPORTS_DMA;
            }
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
        }
        TmpPort->OptionalDmaDevice = &PciIdeBusMasterDevice;
    }
    Status = AtaCoreRegisterAtaHostDevice(NewHostDevice);
    if(Status != STATUS_SUCCESS){
        LouPrint("ATA.SYS:AddAtaDevice() Could Not Register ATA Host Device\n");
        while(1);
    }

    LouPrint("ATA.SYS:AddAtaDevice() STATUS_SUCCESS\n");
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