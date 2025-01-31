#include <LouDDK.h>

LOUDDK_API_ENTRY
void 
LouKeMallocAtaPrivateData(
    PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost,
    uint64_t SizeofPrivateData
){
    AtaHost->PrivateDataSize = SizeofPrivateData;
    AtaHost->HostPrivateData = LouMalloc(SizeofPrivateData);
    for(uint8_t i = 0; i < AtaHost->PortCount; i++){
        AtaHost->Ports[i].PortPrivateData = LouMalloc(SizeofPrivateData);
    }
}

LOUDDK_API_ENTRY
void 
LouKeForkAtaHostPrivateDataToPorts(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost){
    void* AtaHostPrivateData = (void*)AtaHost->HostPrivateData;    
    uint64_t DataSize = AtaHost->PrivateDataSize;

    for(uint8_t i = 0; i < AtaHost->PortCount; i++){
        memcpy(AtaHostPrivateData, AtaHost->Ports[i].PortPrivateData, DataSize);
    }
}

LOUDDK_API_ENTRY
PLOUSINE_KERNEL_DEVICE_ATA_HOST
LouKeMallocAtaDevice(P_PCI_DEVICE_OBJECT PDEV, uint8_t PortCount){

    PLOUSINE_KERNEL_DEVICE_ATA_HOST NewHost;

    NewHost = (PLOUSINE_KERNEL_DEVICE_ATA_HOST)LouMallocEx((sizeof(LOUSINE_KERNEL_DEVICE_ATA_HOST) + (sizeof(LOUSINE_KERNEL_DEVICE_ATA_PORT) * PortCount)), sizeof(LOUSINE_KERNEL_DEVICE_ATA_HOST));
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



bool IsAtaController(P_PCI_DEVICE_OBJECT PDEV){
    PCI_COMMON_CONFIG PciConfig;
    GetPciConfiguration(PDEV->bus, PDEV->slot, PDEV->func, &PciConfig);

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



    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY 
LOUSTATUS LouKeAtaSendAtapiIdentifyCommand(
    PLOUSINE_KERNEL_DEVICE_ATA_PORT  AtapiPort,
    void*                            IdBuffer
){
    LOUSTATUS Result = STATUS_SUCCESS;
    LouPrint("LOUSINE ATA LIB:Creating Atapi Identify Command\n");
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
    memset((void*)Command.ScsiCommand, 0 , 16);
    LouPrint("LOUSINE ATA_LIB:Preping Atapi Identify Command\n");
    if(AtapiPort->Operations->PrepCommand){
        Result = AtapiPort->Operations->PrepCommand(&Command);
        if(Result != STATUS_SUCCESS){
            return Result;
        }
    }
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
    LouPrint("LOUSINE ATA LIB:Preparing To Read Ata Device\n");
    LOUSTATUS Result = STATUS_SUCCESS;
    ATA_QUEUED_COMMAND Command;
    Command.WriteCommand= false;
    Command.DataAddress = (uint64_t)DataBuffer;
    Command.DataSize    = BufferSize;
    Command.Port        = AtaPort;
    Command.WriteCommand= false;
    Command.Lbal        = (uint8_t)((LBA >> 0x00) & 0xFF);
    Command.Lbam        = (uint8_t)((LBA >> 0x08) & 0xFF);
    Command.Lbah        = (uint8_t)((LBA >> 0x10) & 0xFF);
    Command.SectorCount = SectorCount;
    Command.ScsiCommandLength = 12;
    Command.PacketCommand = false;

    if(AtaPort->PortScsiDevice){
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
        for(uint8_t i; i < 12; i++){
            Command.ScsiCommand[i] = Read12[i];
        }
    }else{
        
    }

    Result = AtaPort->Operations->PrepCommand(&Command);
    if(Result != STATUS_SUCCESS){
        return Result;
    }
    Result = AtaPort->Operations->IssueCommand(&Command);
    return Result;
}