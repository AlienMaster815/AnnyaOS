// im following the WYOOS tutorial for Device infomration
// all credit for hardware manipulation should go to the
// WYOOS creator

//code written by Tyler Grenier and is under GPL2

#define _KERNEL_MODULE_

#include <LouDDK.h>
#include "PCNETII.h"
#include <Hal.h>



void PcNetIIHardwareActivate(
    PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER DriverData
){

}

LOUSTATUS PcNetIIHardwareReset(
    PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER DriverData
){


    return STATUS_SUCCESS;
}

void PcNetIIHardwareInterruptHandler(uint64_t DriverData){
    LouPrint("Interrupt From PcNetII\n");
}

static void PcNetIIGetMacAddress(PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER HardwareDriver){

    PPCNET_II_DRIVER_DATA PcNetPrivate = (PPCNET_II_DRIVER_DATA)HardwareDriver->DriverPrivateData;

    HardwareDriver->MacAddress[0] = (uint8_t)inw(PcNetPrivate->MacAddressPortWord0) % 256;
    HardwareDriver->MacAddress[1] = (uint8_t)inw(PcNetPrivate->MacAddressPortWord0) / 256;
    HardwareDriver->MacAddress[2] = (uint8_t)inw(PcNetPrivate->MacAddressPortWord1) % 256;
    HardwareDriver->MacAddress[3] = (uint8_t)inw(PcNetPrivate->MacAddressPortWord1) / 256;
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

    HardwareDriver->HardwareInterruptHandler = PcNetIIHardwareInterruptHandler;
    HardwareDriver->HardwareActivate = PcNetIIHardwareActivate;
    HardwareDriver->HardwareReset = PcNetIIHardwareReset;
    HardwareDriver->PDEV = PDEV;
    HardwareDriver->DriverObject = DriverObject;
    HardwareDriver->PlatformDevice = PlatformDevice;
    HardwareDriver->DriverPrivateData = PcNetPrivate;

    PcNetPrivate->MacAddressPortWord0 = PortBase;
    PcNetPrivate->MacAddressPortWord1 = PortBase + 0x02;
    PcNetPrivate->MacAddressPortWord2 = PortBase + 0x04;
    PcNetPrivate->RegisterAddressPort = PortBase + 0x10;

    PcNetIIGetMacAddress(HardwareDriver);

    LouPrint("InitializePcNetIIDevice() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}