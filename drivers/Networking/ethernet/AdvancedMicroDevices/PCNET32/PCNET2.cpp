// im following the WYOOS tutorial for Device infomration
// all credit for hardware manipulation Knoledge
// should go to the WYOOS creator
// code written by Tyler Grenier and is under GPL2

#define _KERNEL_MODULE_

#include <LouDDK.h>
#include "PCNETII.h"
#include <Hal.h>



void PcNetIIHardwareActivate(
    PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER DriverData
){
    PPCNET_II_DRIVER_DATA PrivateData = (PPCNET_II_DRIVER_DATA)DriverData->DriverPrivateData;
    P_PCI_DEVICE_OBJECT PDEV = DriverData->PDEV;
    uint32_t Tmp = 0;
    outw(PrivateData->RegisterAddressPort, 0);
    outw(PrivateData->RegisterDataPort, 0x7FFF);
    outw(PrivateData->RegisterAddressPort, 0);
    outw(PrivateData->RegisterDataPort, 0x41);
    outw(PrivateData->RegisterAddressPort, 4);
    Tmp = inw(PrivateData->RegisterDataPort);
    outw(PrivateData->RegisterAddressPort, 4);
    outw(PrivateData->RegisterDataPort, Tmp | 0x0C00);
    outw(PrivateData->RegisterAddressPort, 0);
    outw(PrivateData->RegisterDataPort, 0x42);
    //uint16_t CommandRegister = LouKeReadPciUint16(PDEV, 0x04);
    //uint16_t StatusRegister = LouKeReadPciUint16(PDEV, 0x06);
    //LouPrint("Command Register Is:%h\n", CommandRegister);
    //LouPrint("Status  Register Is:%h\n", StatusRegister);
    LouPrint("PCINETII Successfull INIT\n");
}

LOUSTATUS PcNetIIHardwareReset(
    PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER DriverData
){
    PPCNET_II_DRIVER_DATA PrivateData = (PPCNET_II_DRIVER_DATA)DriverData->DriverPrivateData;
    inw(PrivateData->ResetPort);
    outw(PrivateData->ResetPort, 0);
    return STATUS_SUCCESS;
}

void PcNetIIHardwareInterruptHandler(uint64_t DriverDataRaw){
    LouPrint("Interrupt From PcNetII\n");
    PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER DriverData = (PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER)(uint8_t*)DriverDataRaw;
    PPCNET_II_DRIVER_DATA PrivateData = (PPCNET_II_DRIVER_DATA)DriverData->DriverPrivateData;
    uint32_t Tmp = 0;
    outw(PrivateData->RegisterAddressPort, 0);
    Tmp = inw(PrivateData->RegisterDataPort);

    if((Tmp & 0x8000) == 0x8000)LouPrint("PCNET32::ERROR::General Error\n");
    if((Tmp & 0x2000) == 0x2000)LouPrint("PCNET32::ERROR::Colision Error\n");
    if((Tmp & 0x1000) == 0x1000)LouPrint("PCNET32::ERROR::Missed Frame\n");
    if((Tmp & 0x0800) == 0x0800)LouPrint("PCNET32::ERROR::Memory Error\n");
    if((Tmp & 0x0400) == 0x0400)LouPrint("PCNET32::Incoming Data\n");
    if((Tmp & 0x0200) == 0x0200)LouPrint("PCNET32::Outgoing Data\n");
    outw(PrivateData->RegisterAddressPort, 0);
    outw(PrivateData->RegisterDataPort, Tmp);

    if((Tmp & 0x0100) == 0x0100)LouPrint("PCNET32::INIT DONE\n");

}

static void PcNetIIGetMacAddress(PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER HardwareDriver){

    PPCNET_II_DRIVER_DATA PcNetPrivate = (PPCNET_II_DRIVER_DATA)HardwareDriver->DriverPrivateData;

    HardwareDriver->MacAddress[0] = (uint8_t)(inw(PcNetPrivate->MacAddressPortWord0) % 256);
    HardwareDriver->MacAddress[1] = (uint8_t)(inw(PcNetPrivate->MacAddressPortWord0) / 256);
    HardwareDriver->MacAddress[2] = (uint8_t)(inw(PcNetPrivate->MacAddressPortWord1) % 256);
    HardwareDriver->MacAddress[3] = (uint8_t)(inw(PcNetPrivate->MacAddressPortWord1) / 256);
    HardwareDriver->MacAddress[4] = (uint8_t)(inw(PcNetPrivate->MacAddressPortWord2) % 256);
    HardwareDriver->MacAddress[5] = (uint8_t)(inw(PcNetPrivate->MacAddressPortWord2) / 256);

}

static void PcNetIISetupNewMacAddress(PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER HardwareDriver){
    PPCNET_II_DRIVER_DATA PcNetPrivate = (PPCNET_II_DRIVER_DATA)HardwareDriver->DriverPrivateData;

    //this code dosent actually change the mac such as in a
    //mac spoof durring a reset it just sets the data in 
    //the initialization block to set the mac when the 
    //payload goes through from NetFrame

    uint64_t    NewMacAddress =  (uint64_t)HardwareDriver->MacAddress[0];
                NewMacAddress &= (uint64_t)HardwareDriver->MacAddress[1] << 8;
                NewMacAddress &= (uint64_t)HardwareDriver->MacAddress[2] << 16;
                NewMacAddress &= (uint64_t)HardwareDriver->MacAddress[3] << 24;
                NewMacAddress &= (uint64_t)HardwareDriver->MacAddress[4] << 32;
                NewMacAddress &= (uint64_t)HardwareDriver->MacAddress[5] << 40;

    PcNetPrivate->InitializationBlock.PhysicalAddress = NewMacAddress;
}

NTSTATUS InitializePcNetIIDevice(
    PDRIVER_OBJECT DriverObject,
    PDEVICE_OBJECT PlatformDevice
){
    LouPrint("InitializePcNetIIDevice()\n");
    PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER HardwareDriver;
    PPCNET_II_DRIVER_DATA PcNetPrivate;
    P_PCI_DEVICE_OBJECT PDEV = PlatformDevice->PDEV;
    LOUSTATUS LousineKernelStatus = STATUS_SUCCESS;
    uint64_t PortBase = 0;
    uint64_t Tmp;
    PortBase = (uint64_t)LouKeHalGetPciVirtualBaseAddress((PPCI_COMMON_CONFIG)PDEV->CommonConfig, 0);
    if(PortBase > 0xFFFF){
        LouPrint("PCNET32::ERROR::This Driver Cannot Run This Device Invalid Base Address\n");
        LouPrint("PortBase:%h\n", PortBase);
        return STATUS_NO_SUCH_DEVICE;
    }

    HardwareDriver = (PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER)LouKeMallocEx(
        sizeof(LOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER), 
        GET_ALIGNMENT(LOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER),                
        KERNEL_GENERIC_MEMORY
    );
    if(!HardwareDriver){
        LouPrint("PCNET32::ERROR::Could not Allocate HardwareDriver\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    PcNetPrivate = (PPCNET_II_DRIVER_DATA)LouKeMallocEx(
        sizeof(PCNET_II_DRIVER_DATA),
        GET_ALIGNMENT(PCNET_II_DRIVER_DATA),
        KERNEL_GENERIC_MEMORY
    );
    if(!PcNetPrivate){
        LouPrint("PCNET32::ERROR::Could not Allocate PcNetPrivate\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    LousineKernelStatus = LouKeHalEnablePciDevice(PDEV);
    if(LousineKernelStatus != STATUS_SUCCESS){
        return (NTSTATUS)LousineKernelStatus;
    }

    HardwareDriver->HardwareInterruptHandler    = PcNetIIHardwareInterruptHandler;
    HardwareDriver->HardwareActivate            = PcNetIIHardwareActivate;
    HardwareDriver->HardwareReset               = PcNetIIHardwareReset;
    HardwareDriver->PDEV                        = PDEV;
    HardwareDriver->DriverObject                = DriverObject;
    HardwareDriver->PlatformDevice              = PlatformDevice;
    HardwareDriver->DriverPrivateData           = PcNetPrivate;

    PcNetPrivate->MacAddressPortWord0           = PortBase;
    PcNetPrivate->MacAddressPortWord1           = PortBase + 0x02;
    PcNetPrivate->MacAddressPortWord2           = PortBase + 0x04;
    PcNetPrivate->RegisterDataPort              = PortBase + 0x10;
    PcNetPrivate->RegisterAddressPort           = PortBase + 0x12;
    PcNetPrivate->ResetPort                     = PortBase + 0x14;
    PcNetPrivate->BusControllRegisterDataPort   = PortBase + 0x16;

    PcNetIIGetMacAddress(HardwareDriver);

    //set 32 bit mode
    outw(PcNetPrivate->RegisterAddressPort,         0x0020);
    outw(PcNetPrivate->BusControllRegisterDataPort, 0x0102);

    //stop controller reset
    outw(PcNetPrivate->RegisterAddressPort,         0x0000);
    outw(PcNetPrivate->BusControllRegisterDataPort, 0x0004);

    //set initialization block payload
    PcNetPrivate->InitializationBlock.OperationMode         = 0x0000;
    PcNetPrivate->InitializationBlock.Reserved1             = 0;
    PcNetPrivate->InitializationBlock.SendBufferCount       = 3;
    PcNetPrivate->InitializationBlock.Reserved2             = 0;
    PcNetPrivate->InitializationBlock.RecieveBufferCount    = 3;
    PcNetIISetupNewMacAddress(HardwareDriver);
    PcNetPrivate->InitializationBlock.Reserved3             = 0;
    PcNetPrivate->InitializationBlock.LogicalAddress        = 0;
    
    PcNetPrivate->SendDescriptors           =   (PPCNET2_BUFFER_DESCRIPTOR)LouKeMallocEx(2048, 16, KERNEL_DMA_MEMORY);
    PcNetPrivate->ReciveDescriptors         =   (PPCNET2_BUFFER_DESCRIPTOR)LouKeMallocEx(2048, 16, KERNEL_DMA_MEMORY);
    for(uint8_t i = 0; i < 7; i++){ 
        PcNetPrivate->SendComBuffers[i]     =   (uintptr_t)LouKeMallocEx(1024, 16, KERNEL_DMA_MEMORY); 
        PcNetPrivate->ReciveComBuffers[i]   =   (uintptr_t)LouKeMallocEx(1024, 16, KERNEL_DMA_MEMORY);
        //asign buffers to the Controllers DMA Engine
        RequestPhysicalAddress(PcNetPrivate->SendComBuffers[i], &Tmp);
        PcNetPrivate->SendDescriptors[i].Address = Tmp;
        PcNetPrivate->SendDescriptors[i].FlagsLow  = 0xF7FF;  
        PcNetPrivate->SendDescriptors[i].FlagsHigh = 0;  
        PcNetPrivate->SendDescriptors[i].Available = 0;  

        RequestPhysicalAddress(PcNetPrivate->ReciveComBuffers[i], &Tmp);
        PcNetPrivate->ReciveDescriptors[i].Address   = Tmp;
        PcNetPrivate->ReciveDescriptors[i].FlagsLow  = 0x8000F7FF;  
        PcNetPrivate->ReciveDescriptors[i].FlagsHigh = 0;  
        PcNetPrivate->ReciveDescriptors[i].Available = 0;  
    }

    RequestPhysicalAddress((uint64_t)&PcNetPrivate->InitializationBlock, &Tmp);

    outw(PcNetPrivate->RegisterAddressPort, 1);
    outw(PcNetPrivate->RegisterDataPort, Tmp & 0xFFFF);
    outw(PcNetPrivate->RegisterAddressPort, 2);
    outw(PcNetPrivate->RegisterDataPort, (Tmp >> 16) & 0xFFFF);

    //set DMA engine and be off
    LouKeHalPciSetMaster(PDEV);

    LouPrint("Interrupt Line Is:%d\n", PDEV->InterruptLine);

    PcNetPrivate->Interrupt = LouKeHalPciAllocateInterrupt(
        PDEV, 
        PcNetIIHardwareInterruptHandler, 
        false, 
        (uintptr_t)HardwareDriver,
        0
    );

    LouPrint("Bus:%d :: Slot:%d :: Function:%d\n", PDEV->bus, PDEV->slot, PDEV->func);

    LouKeRegisterDevice(
        PDEV, 
        NETWORK_DEVICE_T,
        "HKEY_LOCAL_MACHINE:/ANNYA/SYSTEM64/DRIVERS/PCNET32.SYS:PCNET_II",
        HardwareDriver,
        PcNetPrivate
    );

    LouPrint("InitializePcNetIIDevice() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}