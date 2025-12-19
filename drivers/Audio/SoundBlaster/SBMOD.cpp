#include "SBMOD.h"

UNUSED LOUSINE_PCI_DEVICE_TABLE SupportedSoundBalsters[] = {
    {0},
};

static LOUSTATUS (*Initialize8237ADmaTransfer)(PDMA16_TRANSFER_PACKET Packet);

//DMA16_TRANSFER_PACKET

static DMA16_TRANSFER_PACKET SbModInitializeSc16DmaPacket(
    PVOID   Buffer,
    SIZE    BufferLength
){
    DMA16_TRANSFER_PACKET NewPacket = {0};
    UINT64 PAddress;
    RequestPhysicalAddress((UINT64)Buffer, &PAddress);

    NewPacket.DmaAddress = PAddress;
    NewPacket.Transferlength = BufferLength;
    NewPacket.Channel = 5;    

    NewPacket.Transfer = 1;
    NewPacket.Auto = 0;
    NewPacket.Mode = 1;

    return NewPacket;
}

static DMA16_TRANSFER_PACKET SbModInitializeAi16DmaPacket(
    PVOID   Buffer,
    SIZE    BufferLength
){
    DMA16_TRANSFER_PACKET NewPacket = {0};
    UINT64 PAddress;
    RequestPhysicalAddress((UINT64)Buffer, &PAddress);

    NewPacket.DmaAddress = PAddress;
    NewPacket.Transferlength = BufferLength;
    NewPacket.Channel = 5;    

    NewPacket.Transfer = 1;
    NewPacket.Auto = 1;
    NewPacket.Mode = 2;

    return NewPacket;
}

static DMA16_TRANSFER_PACKET SbModInitializeAi8DmaPacket(
    PVOID   Buffer,
    SIZE    BufferLength
){
    DMA16_TRANSFER_PACKET NewPacket = {0};
    UINT64 PAddress;
    RequestPhysicalAddress((UINT64)Buffer, &PAddress);

    NewPacket.DmaAddress = PAddress;
    NewPacket.Transferlength = BufferLength;
    NewPacket.Channel = 1;    
    
    NewPacket.Transfer = 1;
    NewPacket.Auto = 1;
    NewPacket.Mode = 2;

    return NewPacket;
}

static DMA16_TRANSFER_PACKET SbModInitializeSc8DmaPacket(
    PVOID   Buffer,
    SIZE    BufferLength
){
    DMA16_TRANSFER_PACKET NewPacket = {0};
    UINT64 PAddress;
    RequestPhysicalAddress((UINT64)Buffer, &PAddress);

    NewPacket.DmaAddress = PAddress;
    NewPacket.Transferlength = BufferLength;
    NewPacket.Channel = 1;

    NewPacket.Transfer = 1;
    NewPacket.Auto = 0;
    NewPacket.Mode = 1;

    return NewPacket;
}


DRIVER_EXPORT
LOUSTATUS 
LouKeAddSbIsaDevice(){
    LouPrint("SBMOD.SYS::LouKeAddSbIsaDevice()\n");


    LouPrint("SBMOD.SYS::LouKeAddSbIsaDevice() STATUS_SUCCESS\n"); 
    return STATUS_SUCCESS;
}


LOUDDK_API_ENTRY 
VOID UnloadDriver(PDRIVER_OBJECT DriverObject){
    LouPrint("SBMOD.SYS::UnloadDriver()\n");
    //TODO: Unload 8237A.SYS
    LouPrint("SBMOD.SYS::UnloadDriver() STATUS_SUCCESS\n");
    while(1);
}

NTSTATUS AddDevice(
    PDRIVER_OBJECT DriverObject, 
    struct _DEVICE_OBJECT* PlatformDevice
){

    LouPrint("SBMOD.SYS::AddDevice()\n");


    LouPrint("SBMOD.SYS::AddDevice() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
NTSTATUS DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryEntry
){
    LouPrint("SBMOD.SYS::DriverEntry()\n");
    //tell the System where are key Nt driver functions are
    DriverObject->DriverExtension->AddDevice = AddDevice;
    DriverObject->DriverUnload = UnloadDriver;
    //tell the lousine kernel we will be using the
    //Lousine Kernel Driver Module (LKDM) alongside the
    //NT Kernel Moudle Subsystem so it fills
    //out the extra information relating to the LKDM
    DriverObject->DriverUsingLkdm = true;
    //fill LDM information
    DriverObject->DeviceTable = (uintptr_t)SupportedSoundBalsters;

    LouKeLoadDriver("8237A.SYS", 0x00);
    Initialize8237ADmaTransfer = (LOUSTATUS(*)(PDMA16_TRANSFER_PACKET))LouKeLinkerGetAddress("8237A.SYS", "Initialize8237ADmaTransfer");

    LouPrint("SBMOD.SYS::DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

