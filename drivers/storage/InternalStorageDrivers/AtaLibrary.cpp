#include <LouDDK.h>

LOUDDK_API_ENTRY
void 
LouKeMallocAtaPrivateData(
    PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost,
    uint64_t SizeofPrivateData,
    uint64_t AlignmentOfPrivateData
){
    AtaHost->PrivateDataSize = SizeofPrivateData;
    AtaHost->HostPrivateData = LouKeMallocEx(SizeofPrivateData, AlignmentOfPrivateData, WRITEABLE_PAGE | PRESENT_PAGE);
    for(uint8_t i = 0; i < AtaHost->PortCount; i++){
        AtaHost->Ports[i].AtaHost = AtaHost;
        AtaHost->Ports[i].PortPrivateData = LouKeMallocEx(SizeofPrivateData, AlignmentOfPrivateData, WRITEABLE_PAGE | PRESENT_PAGE);
    }
}

LOUDDK_API_ENTRY
void 
LouKeForkAtaHostPrivateDataToPorts(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost){
    
    void* AtaHostPrivateData = (void*)AtaHost->HostPrivateData;    
    uint64_t DataSize = AtaHost->PrivateDataSize;

    for(uint8_t i = 0; i < AtaHost->PortCount; i++){
        memcpy(AtaHost->Ports[i].PortPrivateData,AtaHostPrivateData, DataSize);
    }
    
}

LOUDDK_API_ENTRY
PLOUSINE_KERNEL_DEVICE_ATA_HOST
LouKeMallocAtaDevice(PPCI_DEVICE_OBJECT PDEV, uint8_t PortCount){

    PLOUSINE_KERNEL_DEVICE_ATA_HOST NewHost = 0x00;

    NewHost = (PLOUSINE_KERNEL_DEVICE_ATA_HOST)LouKeMallocEx(GetStructureSize(NewHost, Ports, PortCount), GET_ALIGNMENT(LOUSINE_KERNEL_DEVICE_ATA_HOST), KERNEL_GENERIC_MEMORY);
    NewHost->PDEV = PDEV;
    NewHost->PortCount = PortCount;
    
    for(uint8_t i = 0 ; i < PortCount; i++){
        NewHost->Ports[i].Siblings = PortCount - 1;
        NewHost->Ports[i].PDEV = PDEV;
        NewHost->Ports[i].AtaHost = NewHost;    
        NewHost->Ports[i].PortNumber = i + 1;    
    }


    return NewHost;
}



bool IsAtaController(PPCI_DEVICE_OBJECT PDEV){
    PCI_COMMON_CONFIG PciConfig;
    GetPciConfiguration(PDEV->Group, PDEV->bus, PDEV->slot, PDEV->func, &PciConfig);

    if((PciConfig.Header.BaseClass == 0x01) && PciConfig.Header.SubClass == 0x01){
        LouPrint("Found ATA Controller\n");
        return true;
    }
    return false;
}

LOUDDK_API_ENTRY
LOUSTATUS LouKeAtaSendAtaIdentifyCommand(
    PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort,
    void* IdBuffer
){
    LOUSTATUS Result = STATUS_SUCCESS;
    //LouPrint("LOUSINE ATA LIB:Creating Ata Identify Command\n");
    UNUSED ATA_QUEUED_COMMAND Command;
    Command.Command     = ATA_COMMAND_IDENTIFY_ATA;
    Command.WriteCommand= false;
    Command.DataAddress = (uint64_t)IdBuffer;
    Command.DataSize    = 512;
    Command.Port        = AtaPort;
    Command.WriteCommand= false;
    Command.Lbal        = 0;
    Command.Lbam        = 0;
    Command.Lbah        = 0;
    Command.SectorCount = 0;
    Command.ScsiCommandLength = 0;
    Command.PacketCommand = false;
    Command.Feature = 0;
    Command.Device = 0xE0;
    Command.HobLbal        = 0;
    Command.HobLbam        = 0;
    Command.HobLbah        = 0;
    Command.HobSectorCount = 0;
    Command.Control = 0x08;
    Command.Auxillery = 0;

    memset((void*)Command.ScsiCommand, 0 , 16);
    //LouPrint("LOUSINE ATA_LIB:Preping Ata Identify Command\n");
    if(AtaPort->Operations->PrepCommand){
        Result = AtaPort->Operations->PrepCommand(&Command);
        if(Result != STATUS_SUCCESS){
            return Result;
        }
    }
    //LouPrint("LOUSINE ATA_LIB:Issueing Ata Identify Command\n");
    if(AtaPort->Operations->IssueCommand){
        Result = AtaPort->Operations->IssueCommand(&Command);
    }
    return Result;  
}

LOUDDK_API_ENTRY 
LOUSTATUS LouKeAtaSendAtapiIdentifyCommand(
    PLOUSINE_KERNEL_DEVICE_ATA_PORT  AtapiPort,
    void*                            IdBuffer
){
    LOUSTATUS Result = STATUS_SUCCESS;
    //LouPrint("LOUSINE ATA LIB:Creating Atapi Identify Command\n");
    UNUSED ATA_QUEUED_COMMAND Command;
    Command.Command     = ATA_COMMAND_IDENTIFY_ATAPI;
    Command.WriteCommand= false;
    Command.DataAddress = (uint64_t)IdBuffer;
    Command.DataSize    = 512;
    Command.Port        = AtapiPort;
    Command.WriteCommand= false;
    Command.Lbal        = 0;
    Command.Lbam        = 0;
    Command.Lbah        = 0;
    Command.SectorCount = 0;
    Command.ScsiCommandLength = 0;
    Command.PacketCommand = false;
    Command.Feature = 0;
    Command.Device = 0xE0;
    Command.HobLbal        = 0;
    Command.HobLbam        = 0;
    Command.HobLbah        = 0;
    Command.HobSectorCount = 0;
    Command.Control = 0x08;
    Command.Auxillery = 0;

    memset((void*)Command.ScsiCommand, 0 , 16);
    //LouPrint("LOUSINE ATA_LIB:Preping Atapi Identify Command\n");
    if(AtapiPort->Operations->PrepCommand){
        Result = AtapiPort->Operations->PrepCommand(&Command);
        if(Result != STATUS_SUCCESS){
            return Result;
        }
    }
    //LouPrint("LOUSINE ATA_LIB:Issueing Atapi Identify Command\n");
    if(AtapiPort->Operations->IssueCommand){
        Result = AtapiPort->Operations->IssueCommand(&Command);
    }
    return Result;
}


LOUDDK_API_ENTRY
LOUSTATUS LouKeAtaReadDevice(
	PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort,
    uint64_t LBA,
    uint32_t SectorCount,
    uint64_t BufferSize,
    void* DataBuffer
){
    LOUSTATUS Result = STATUS_SUCCESS;
    ATA_QUEUED_COMMAND Command = {0};

    Command.WriteCommand= false;
    Command.DataAddress = (uint64_t)DataBuffer;
    Command.DataSize    = BufferSize;
    Command.Port        = AtaPort;
    Command.Lbal        = (uint8_t)((LBA >> 0x00) & 0xFF);
    Command.Lbam        = (uint8_t)((LBA >> 0x08) & 0xFF);
    Command.Lbah        = (uint8_t)((LBA >> 0x10) & 0xFF);
    Command.SectorCount = SectorCount & 0xFF;
    Command.ScsiCommandLength = 12;
    Command.PacketCommand = false;
    Command.Feature = 0;
    Command.Device = 0xE0;
    Command.HobLbal        = (uint8_t)((LBA >> 24) & 0xFF);
    Command.HobLbam        = (uint8_t)((LBA >> 32) & 0xFF);
    Command.HobLbah        = (uint8_t)((LBA >> 40) & 0xFF);
    Command.HobSectorCount = (SectorCount >> 8) & 0xFF;
    Command.Control = 0x08;
    Command.Auxillery = 0;
    if(AtaPort->DmaPort){
        Command.Command = ATA_COMMAND_READ;
    }else{
        Command.Command = ATA_COMMAND_PIO_READ;
    }

    if(AtaPort->PortScsiDevice){
        //LouPrint("LOUSINE ATA LIB:Preparing To Read Atapi Device\n");

        Command.PacketCommand   = true;
        Command.Command         = ATA_COMMAND_PACKET;
        volatile uint8_t Read12[12] = {     0xA8, 0,
                                            (uint8_t)((LBA >> 0x18) & 0xFF), 
                                            (uint8_t)((LBA >> 0x10) & 0xFF), 
                                            (uint8_t)((LBA >> 0x08) & 0xFF),
                                            (uint8_t)((LBA >> 0x00) & 0xFF),
                                            (uint8_t)((SectorCount >> 0x18) & 0xFF), 
                                            (uint8_t)((SectorCount >> 0x10) & 0xFF), 
                                            (uint8_t)((SectorCount >> 0x08) & 0xFF),
                                            (uint8_t)((SectorCount >> 0x00) & 0xFF),
                                            0, 0};
        
        memset((void*)Command.ScsiCommand, 0 , 16);
        for(uint8_t i = 0; i < 12; i++){
            Command.ScsiCommand[i] = Read12[i];
        }
    }else{
        //LouPrint("LOUSINE ATA LIB:Preparing To Read Ata Device\n");
        //while(1);
    }

    if(AtaPort->Operations->PrepCommand){
        Result = AtaPort->Operations->PrepCommand(&Command);
        if(Result != STATUS_SUCCESS){
            return Result;
        }
    }
    Result = AtaPort->Operations->IssueCommand(&Command);
    return Result;
}

