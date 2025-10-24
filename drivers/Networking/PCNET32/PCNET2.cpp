// im following the WYOOS tutorial for Device infomration
// all credit for hardware manipulation should go to the
// WYOOS creator

//code written by Tyler Grenier and is under GPL2

#define _KERNEL_MODULE_

#include <LouDDK.h>
#include "PCNETII.h"
#include <Hal.h>

LOUSTATUS PcNetIIHardwareInitialize(
    PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER HardwareDriver
){
    LouPrint("PcNetIIHardwareInitialize()\n");
    PPCNET_II_DRIVER_DATA PcNetPrivate = (PPCNET_II_DRIVER_DATA)HardwareDriver->DriverPrivateData;

    outw(PcNetPrivate->RegisterAddressPort, 1);
    outw(PcNetPrivate->RegisterDataPort, (uint16_t)(((uint64_t)&PcNetPrivate->InitializationBlock) & 0xFFFF));
    outw(PcNetPrivate->RegisterAddressPort, 2);
    outw(PcNetPrivate->RegisterDataPort, (uint16_t)(((uint64_t)&PcNetPrivate->InitializationBlock >> 16) & 0xFFFF));

    return STATUS_SUCCESS;
}

void PcNetIIHardwareActivate(
    PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER HardwareDriver
){
    LouPrint("PcNetIIHardwareActivate()\n");
    PPCNET_II_DRIVER_DATA PcNetPrivate = (PPCNET_II_DRIVER_DATA)HardwareDriver->DriverPrivateData;
    PPCI_DEVICE_OBJECT PDEV = HardwareDriver->PDEV;
    outw(PcNetPrivate->RegisterAddressPort, 0);           // CSR0
    outw(PcNetPrivate->RegisterDataPort, 0x0001);         // INIT only
    
    outw(PcNetPrivate->RegisterAddressPort, 0);
    outw(PcNetPrivate->RegisterDataPort, 0x41);
    outw(PcNetPrivate->RegisterAddressPort, 4);
    uint32_t Tmp = inw(PcNetPrivate->RegisterDataPort);
    outw(PcNetPrivate->RegisterAddressPort, 4);
    outw(PcNetPrivate->RegisterDataPort, Tmp | 0x0C00);
    outw(PcNetPrivate->RegisterAddressPort, 0);
    outw(PcNetPrivate->RegisterDataPort, 0x42);
}

LOUSTATUS PcNetIIHardwareReset(
    PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER HardwareDriver
){
    LouPrint("PcNetIIHardwareReset()\n");
    PPCNET_II_DRIVER_DATA PcNetPrivate = (PPCNET_II_DRIVER_DATA)HardwareDriver->DriverPrivateData;
    inw(PcNetPrivate->ResetPort);
    outw(PcNetPrivate->ResetPort, 0);
    return STATUS_SUCCESS;
}

void PcNetIIHardwareInterruptHandler(uint64_t HardwareDriver){
    LouPrint("Interrupt From PcNetII\n");
}

static void PcNetIIGetMacAddress(PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER HardwareDriver){

    PPCNET_II_DRIVER_DATA PcNetPrivate = (PPCNET_II_DRIVER_DATA)HardwareDriver->DriverPrivateData;

    HardwareDriver->MacAddress[0] = (uint8_t)inw(PcNetPrivate->MacAddressPortWord0) % 256;
    HardwareDriver->MacAddress[1] = (uint8_t)inw(PcNetPrivate->MacAddressPortWord0) / 256;
    HardwareDriver->MacAddress[2] = (uint8_t)inw(PcNetPrivate->MacAddressPortWord1) % 256;
    HardwareDriver->MacAddress[3] = (uint8_t)inw(PcNetPrivate->MacAddressPortWord1) / 256;
    HardwareDriver->MacAddress[4] = (uint8_t)inw(PcNetPrivate->MacAddressPortWord2) % 256;
    HardwareDriver->MacAddress[5] = (uint8_t)inw(PcNetPrivate->MacAddressPortWord2) / 256;
}

void PcNetIIHardwareSetMacAddress(
    PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER HardwareDriver
){
    PPCNET_II_DRIVER_DATA PcNetPrivate = (PPCNET_II_DRIVER_DATA)HardwareDriver->DriverPrivateData;

    uint64_t Mac = ((uint64_t)HardwareDriver->MacAddress[5] << 40) 
                 | ((uint64_t)HardwareDriver->MacAddress[4] << 32) 
                 | ((uint64_t)HardwareDriver->MacAddress[3] << 24) 
                 | ((uint64_t)HardwareDriver->MacAddress[2] << 16) 
                 | ((uint64_t)HardwareDriver->MacAddress[1] << 8) 
                 | ((uint64_t)HardwareDriver->MacAddress[0]);

    PcNetPrivate->InitializationBlock.PhysicalAddress = Mac;
}

NTSTATUS InitializePcNetIIDevice(
    PDRIVER_OBJECT DriverObject,
    struct _DEVICE_OBJECT* PlatformDevice
){
    LouPrint("InitializePcNetIIDevice()\n");
    PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER HardwareDriver;
    PPCNET_II_DRIVER_DATA PcNetPrivate;
    PPCI_DEVICE_OBJECT PDEV = PlatformDevice->PDEV;
    LOUSTATUS LousineKernelStatus = STATUS_SUCCESS;
    uint64_t PortBase = 0;
   
    PortBase = (uint64_t)LouKePciGetIoRegion(PDEV, 0, 0);
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
    LouKeHalPciSetMaster(PDEV);

    HardwareDriver->HardwareInterruptHandler = PcNetIIHardwareInterruptHandler;
    HardwareDriver->HardwareActivate = PcNetIIHardwareActivate;
    HardwareDriver->HardwareReset = PcNetIIHardwareReset;
    HardwareDriver->PDEV = PDEV;
    HardwareDriver->DriverObject = DriverObject;
    HardwareDriver->PlatformDevice = PlatformDevice;
    HardwareDriver->DriverPrivateData = PcNetPrivate;
    HardwareDriver->HardwareSetAddress = PcNetIIHardwareSetMacAddress;
    HardwareDriver->HardwareInitialize = PcNetIIHardwareInitialize;

    PcNetPrivate->MacAddressPortWord0 = PortBase;
    PcNetPrivate->MacAddressPortWord1 = PortBase + 0x02;
    PcNetPrivate->MacAddressPortWord2 = PortBase + 0x04;
    PcNetPrivate->RegisterDataPort = PortBase + 0x10;
    PcNetPrivate->RegisterAddressPort = PortBase + 0x12;
    PcNetPrivate->ResetPort = PortBase + 0x14;
    PcNetPrivate->BusControllRegisterDataPort = PortBase + 0x16;
    PcNetIIGetMacAddress(HardwareDriver);
    outw(PcNetPrivate->RegisterAddressPort, 0x20);
    outw(PcNetPrivate->BusControllRegisterDataPort, 0x0102);
    outw(PcNetPrivate->RegisterAddressPort, 0);
    outw(PcNetPrivate->RegisterDataPort, 0x04);

    PcNetPrivate->InitializationBlock.OperationMode = 0x0000;
    PcNetPrivate->InitializationBlock.Reserved1 = 0;
    PcNetPrivate->InitializationBlock.SendBufferCount = 3;
    PcNetPrivate->InitializationBlock.Reserved2 = 0;
    PcNetPrivate->InitializationBlock.RecieveBufferCount = 3;
    PcNetIIHardwareSetMacAddress(HardwareDriver);
    PcNetPrivate->InitializationBlock.Reserved3 = 0;
    PcNetPrivate->InitializationBlock.LogicalAddress = 0;
    PcNetPrivate->SendDescriptors = (uintptr_t)LouKeMallocEx(2048, 16, KERNEL_DMA_MEMORY); 
    PcNetPrivate->ReciveDescriptors = (uintptr_t)LouKeMallocEx(2048, 16, KERNEL_DMA_MEMORY);

    PPCNET2_BUFFER_DESCRIPTOR Send = (PPCNET2_BUFFER_DESCRIPTOR)PcNetPrivate->SendDescriptors;
    PPCNET2_BUFFER_DESCRIPTOR Recieve = (PPCNET2_BUFFER_DESCRIPTOR)PcNetPrivate->ReciveDescriptors;
    uint64_t Tmp = 0x00;
    RequestPhysicalAddress((uint64_t)Send, &Tmp);
    if(Tmp > 0xFFFFFFFF){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    PcNetPrivate->InitializationBlock.SendBufferDescriptorAddress = (uint32_t)(uintptr_t)Tmp; 
    RequestPhysicalAddress((uint64_t)Recieve, &Tmp);
    if((uint64_t)Tmp > 0xFFFFFFFF){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    PcNetPrivate->InitializationBlock.RecieveBufferDescriptorAddress = (uint32_t)(uintptr_t)Tmp; 

    for(uint8_t i = 0 ; i < 8; i++){
        PcNetPrivate->SendComBuffers[i] = (uintptr_t)LouKeMallocEx(2048, 16, KERNEL_DMA_MEMORY);
        RequestPhysicalAddress(PcNetPrivate->SendComBuffers[i], &Tmp);
        if(Tmp > 0xFFFFFFFF){
            return STATUS_INSUFFICIENT_RESOURCES;
        }
        Send[i].Address = Tmp;
        Send[i].FlagsLow = 0xF7FF;
        Send[i].FlagsHigh = 0;
        Send[i].Available = 0;
        PcNetPrivate->ReciveComBuffers[i] = (uintptr_t)LouKeMallocEx(2048, 16, KERNEL_DMA_MEMORY);
        RequestPhysicalAddress(PcNetPrivate->ReciveComBuffers[i], &Tmp);
        if(Tmp > 0xFFFFFFFF){
            return STATUS_INSUFFICIENT_RESOURCES;
        }
        Recieve[i].Address = Tmp;
        Recieve[i].FlagsLow = 0x8000F7FF;
        Recieve[i].FlagsHigh = 0;
        Recieve[i].Available = 0;
    }

    RegisterInterruptHandler(PcNetIIHardwareInterruptHandler, LouKePciGetInterruptLine(PDEV), false, (uint64_t)HardwareDriver);


    LoukeRegisterNetFrameHardwareDriver(HardwareDriver);

    LouPrint("InitializePcNetIIDevice() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}