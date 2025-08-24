
#define _KERNEL_MODULE_

#include <LouDDK.h>
#include "HDAPCI.h"


UNUSED LOUSINE_PCI_DEVICE_TABLE SupportedHdaPciDevices[] = {
    {.VendorID = 0x8086, .DeviceID = HDA_CPT, .DriverData = AZX_DRIVER_PCH | AZX_DCAPS_INTEL_PCH_NO_POWER_MANAGEMENT, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_PBG, .DriverData = AZX_DRIVER_PCH | AZX_DCAPS_INTEL_PCH_NO_POWER_MANAGEMENT, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_PPT, .DriverData = AZX_DRIVER_PCH | AZX_DCAPS_INTEL_PCH_NO_POWER_MANAGEMENT, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_LPT, .DriverData = AZX_DRIVER_PCH | AZX_DCAPS_INTEL_PCH,.SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_9_SERIES, .DriverData = AZX_DRIVER_PCH | AZX_DCAPS_INTEL_PCH,.SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_WBG0, .DriverData = AZX_DRIVER_PCH | AZX_DCAPS_INTEL_PCH,.SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_WBG1, .DriverData = AZX_DRIVER_PCH | AZX_DCAPS_INTEL_PCH,.SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_LBG0, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_LBG1, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_LPT0, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_LPT1, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_WPT_LP, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_SKL, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_KBL, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_KBL_LP, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_KBL_H, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_CNL_H, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_CNL_LP, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_CML_LP, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_CML_H, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_RKL_S, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_CML_S, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_CML_R, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_ICL_LP, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_ICL_H, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_ICL_N, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_JSL_N, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_TGL_LP, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_DG1, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_DG2_0, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_DG2_1, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_DG2_2, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_ADL_S, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_ADL_PS, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_ADL_PX, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_ADL_M, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_ADL_N, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_EHL_0, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_EHL_3, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_RPL_S, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_RPL_P0, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_RPL_P1, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_RPL_M, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_RPL_PX, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_MTL, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_BMG, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_LNL_P, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_ARL_S, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_ARL, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_PTL, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_PTL_H, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_APL, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_GML, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_HASWELL0, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_HASWELL2, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_HASWELL3, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_BROADWELL, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_5_3400_SERIES0, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_5_3400_SERIES1, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_POULSBO, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_OAKTRAIL, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_BAYTRAIL, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_BRASWELL, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_ICH6, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_ICH7, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_ESB2, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_ICH8, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_ICH9_0, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_ICH9_1, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_ICH10_0, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_ICH10_1, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDA_LOONGSON, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = HDMI_LOONGSON, .SimpleEntry = true},
    {0},
};

LOUDDK_API_ENTRY 
VOID UnloadDriver(PDRIVER_OBJECT DriverObject){
    LouPrint("HDAPCI::UnloadDriver()\n");
    //we have nothing to unload
    LouPrint("HDAPCI::UnloadDriver() STATUS_SUCCESS\n");
}


NTSTATUS AddDevice(
    PDRIVER_OBJECT DriverObject, 
    PDEVICE_OBJECT PlatformDevice
){
    LouPrint("HDAPCI::AddDevice()\n");
    PPCI_DEVICE_OBJECT PDEV = PlatformDevice->PDEV;
    uint8_t DeviceID = PlatformDevice->DeviceID;

    LouPrint("Pci Device ID:%d\n", DeviceID);

    LouPrint("PCI Device Flags:%bl\n", SupportedHdaPciDevices[DeviceID].DriverData);

    LouPrint("HDAPCI::AddDevice() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
NTSTATUS DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryEntry
){
    LouPrint("HDAPCI::DriverEntry()\n");
    //tell the System where are key Nt driver functions are
    DriverObject->DriverExtension->AddDevice = AddDevice;
    DriverObject->DriverUnload = UnloadDriver;
    //tell the lousine kernel we will be using the
    //Lousine Kernel Driver Module (LKDM) alongside the
    //NT Kernel Moudle Subsystem so it fills
    //out the extra information relating to the LKDM
    DriverObject->DriverUsingLkdm = true;
    //fill LDM information
    DriverObject->DeviceTable = (uintptr_t)SupportedHdaPciDevices;

    LouPrint("HDAPCI::DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

