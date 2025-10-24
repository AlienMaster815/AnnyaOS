/* SPDX-License-Identifier: MIT */
/* Copyright (C) 2006-2017 Oracle Corporation */


#define _KERNEL_MODULE_
#include <LouDDK.h>
#include "VirtualboxDriver.h"
#include <Hal.h>
#include <drivers/VBoxError.h>

static LOUSINE_PCI_DEVICE_TABLE PiixPciDeviceTable[] = {
    //PATA Devices
    {0x80EE, 0xBEEF, ANY_PCI_ID, ANY_PCI_ID, 0, 0, 0},
    {0},
};

LOUDDK_API_ENTRY
VOID
UnloadDriver(PDRIVER_OBJECT DriverObject){
    LouPrint("Unloaded VBOXGPU\n");
}

void VirtualboxReportCapabilities(
    PVIRTUALBOX_PRIVATE_DATA Vbox
){
    uint32_t Capabilities = VBVACAPS_DISABLE_CURSOR_INTEGRATION | VBVACAPS_IRQ | VBVACAPS_USE_VBVA_ONLY;

    HgsmiSendCapabilityInfo(Vbox->GuestPool, Capabilities);
    Capabilities |= VBVACAPS_VIDEO_MODE_HINTS;
    HgsmiSendCapabilityInfo(Vbox->GuestPool, Capabilities);
}

static bool HaveHgsmiModeHints(PVIRTUALBOX_PRIVATE_DATA VBox){
    uint32_t HaveHint, HaveCursor;

    bool Return = HgsmiQueryConfiguration(
        VBox->GuestPool, 
        VIRTUALBOX_VBVA_CONFIGURATION32_MODE_HINT_REPORTING,
        &HaveHint
    );

    if(Return){
        return false;
    }

    Return = HgsmiQueryConfiguration(
        VBox->GuestPool,
        VIRTUALBOX_VBVA_CONFIGURATION32_GUEST_CURSOR_REPORTING,
        &HaveCursor
    );

    return ((HaveHint == VINF_SUCCESS) && (HaveCursor == VINF_SUCCESS));
}

bool VboxCheckSupport(uint16_t Identification){
    uint16_t IDCheck = 0;
    VBOX_IO_WRITE(VIRTUALBOX_VBE_DISPI_INDEX_ID, Identification);
    IDCheck = inw(VIRTUALBOX_VBE_DISPI_IO_DATA_PORT);
    return (Identification == IDCheck);
}

static LOUSTATUS VBoxAccelerationInitialize(
    PVIRTUALBOX_PRIVATE_DATA VBox
){
    PPCI_DEVICE_OBJECT PDEV = VBox->PDEV;
    VBVA_BUFFER* VBva;

    VBox->VbvaInformation = LouKeMallocType(VBVA_BUFFER_CONTEXT, KERNEL_GENERIC_MEMORY);
    
    VBox->AvailableVramSize -= VBox->CrtcCount * VBVA_MINIMUM_BUFFER_SIZE;

    VBox->VbvaBuffers = (uint8_t*)LouKePciGetIoRegion(PDEV, 0, VBox->AvailableVramSize);
    if(!VBox->VbvaBuffers){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    for(size_t i = 0; i < VBox->CrtcCount; i++){
        VbvaSetupBufferContext(
            &VBox->VbvaInformation[i], 
            VBox->AvailableVramSize + i * VBVA_MINIMUM_BUFFER_SIZE,
            VBVA_MINIMUM_BUFFER_SIZE
        );
        VBva = (VBVA_BUFFER*)(VBox->VbvaBuffers + i * VBVA_MINIMUM_BUFFER_SIZE);
        if(!VbvaEnable(&VBox->VbvaInformation[i], VBox->GuestPool, VBva, i)){
            LouPrint("VBOXVIDEO ERROR: Unable To Start Crtc:%d\n", i + 1);
        }
        
    }

    return STATUS_SUCCESS;
}

LOUSTATUS VBoxMemoryManagementInitialization(
    PVIRTUALBOX_PRIVATE_DATA VBox 

){
    PDRSD_DEVICE Device = &VBox->DrsdDevice;
    PPCI_DEVICE_OBJECT PDEV = VBox->PDEV;
    void* VramBase = LouKePciGetIoRegion(PDEV, 0, 0);
    LOUSTATUS Result;

    Result = LouKePassVramToDrsdMemoryManager(Device, VramBase, VBox->AvailableVramSize, 0);

    return Result;
}

LOUSTATUS VBoxInitializeHardware(
    PVIRTUALBOX_PRIVATE_DATA VBox
){

    PPCI_DEVICE_OBJECT PDEV = VBox->PDEV;
    LOUSTATUS Status;
    VBox->FullVRamSize = inl(VIRTUALBOX_VBE_DISPI_IO_DATA_PORT);
    VBox->AnyPitch = VboxCheckSupport(VIRTUALBOX_VBE_DISPI_ID_ANYX);    
    VBox->VBoxVideo = VboxCheckSupport(VIRTUALBOX_VBE_DISPI_ID_VBOX_VIDEO);
    LouPrint("Virtualbox VRAM Size:%h\n", VBox->FullVRamSize);    
    LouPrint("Support For Any Pitch : %s\n", VBox->AnyPitch ? "YES" : "NO");
    LouPrint("Support For VBVA      : %s\n", VBox->VBoxVideo ? "YES" : "NO");

    VBox->GuestHeap = (uint8_t*)((uint64_t)LouKePciGetIoRegion(
        PDEV, 
        0, 
        VIRTUALBOX_GUEST_HEAP_OFFSET(VBox)
    ));
    
    LouPrint("Guest Heap:%h\n", VBox->GuestHeap);

    VBox->GuestPool = LouKeCreateGenericPool(
        (uint64_t)VBox->GuestHeap,
        VIRTUALBOX_GUEST_HEAP_OFFSET(VBox),
        VIRTUALBOX_GUEST_HEAP_USABLE_SIZE,
        0
    ); 

    HgsmiTestQueryConfiguration(VBox->GuestPool);
    
    VBox->AvailableVramSize = VIRTUALBOX_GUEST_HEAP_OFFSET(VBox);

    HgsmiQueryConfiguration(VBox->GuestPool, VIRTUALBOX_VBVA_CONFIGURATION32_MONITOR_CCOUNT, &VBox->CrtcCount);
    VBox->CrtcCount = LouClamp_t(uint32_t, VBox->CrtcCount, 1 ,  VIRTUALBOX_VIDEO_MAX_SCREENS);
    LouPrint("CRTC Count:%h\n", VBox->CrtcCount);
    
    if(!HaveHgsmiModeHints(VBox)){
        return STATUS_NOT_SUPPORTED;
    }

    VBox->LastModeHints = LouKeMallocType(VBVA_MODE_HINT, KERNEL_GENERIC_MEMORY);
    if(!VBox->LastModeHints){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    return VBoxAccelerationInitialize(VBox);

}

LOUDDK_API_ENTRY
NTSTATUS
AddDevice(PDRIVER_OBJECT DriverObject, struct _DEVICE_OBJECT* PlatformDevice){
    LouPrint("VBOXGPU::AddDevice()\n");
    
    PPCI_DEVICE_OBJECT PDEV = PlatformDevice->PDEV;
    
    PVIRTUALBOX_PRIVATE_DATA VBox;
    LOUSTATUS Status;
    if(!VboxCheckSupport(VIRTUALBOX_VBE_DISPI_ID_HGSMI)){
        return STATUS_NO_SUCH_DEVICE;
    }
    VBox = LouKeMallocType(VIRTUALBOX_PRIVATE_DATA, KERNEL_GENERIC_MEMORY);
    if(!VBox){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    LouKeDrsdHandleConflictingDevices(PDEV);

    Status = LouKeHalEnablePciDevice(PDEV);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    VBox->PDEV = PDEV;
    VBox->DrsdDevice.PDEV = PDEV;
    Status = VBoxInitializeHardware(VBox);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    Status = VBoxMemoryManagementInitialization(VBox);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    Status = VirtualboxModeInitialization(VBox);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    Status = InitializeVirtualboxInterrupts(VBox);    
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    PDEV->DevicePrivateData = (uintptr_t)VBox;


    LouKeRegisterDevice(
        (PPCI_DEVICE_OBJECT)PDEV, 
        GRAPHICS_DEVICE_T, 
        "HKEY:Annya/System64/Drivers/VBoxGpu", 
        (void*)VBox, 
        (void*)VBox
    );

    LouPrint("VBOXGPU::AddDevice() STATUS_SUCCESS\n");
    return Status;
}

LOUDDK_API_ENTRY
NTSTATUS
DriverEntry(
    PDRIVER_OBJECT DriverObject, 
    PUNICODE_STRING RegistryEntry
){

    LouPrint("VBOXGPU::DriverEntry()\n");
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
    LouPrint("VBOXGPU::DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}