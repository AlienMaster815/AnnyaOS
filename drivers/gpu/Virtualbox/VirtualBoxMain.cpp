/* SPDX-License-Identifier: MIT */
/* Copyright (C) 2006-2017 Oracle Corporation */
/* Port Copyright (C) 2025-2026 Tyler Grenier */


#define _KERNEL_MODULE_
#include <LouDDK.h>
#include "VirtualboxDriver.h"
#include <Hal.h>
#include <drivers/VBoxError.h>

static LOUSINE_PCI_DEVICE_TABLE VBoxGpuPciDeviceTable[] = {
    //VBOXGPU Devices
    {0x80EE, 0xBEEF, ANY_PCI_ID, ANY_PCI_ID, 0, 0, 0},
    {0},
};

LOUAPI
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

static void VirtualboxAccellerationFailedInitialization(PVIRTUALBOX_PRIVATE_DATA VBox){
    for(UINT32 i = 0 ; i < VBox->CrtcCount; i++){
        VbvaDisable(&VBox->VbvaInformation[i], VBox->GuestPool, i);
    } 
}

static LOUSTATUS VBoxAccelerationInitialize(
    PVIRTUALBOX_PRIVATE_DATA VBox
){
    LouPrint("VBOXGPU.SYS:VBoxAccelerationInitialize()\n");
    PPCI_DEVICE_OBJECT PDEV = VBox->PDEV;
    VBVA_BUFFER* VBva;

    VBox->VbvaInformation = LouKeMallocArray(VBVA_BUFFER_CONTEXT, VBox->CrtcCount, KERNEL_GENERIC_MEMORY);
    
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
    LouPrint("VBOXGPU.SYS:VBoxAccelerationInitialize() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS VBoxMemoryManagementInitialization(
    PVIRTUALBOX_PRIVATE_DATA VBox 

){
    PDRSD_DEVICE Device = &VBox->DrsdDevice;
    PPCI_DEVICE_OBJECT PDEV = VBox->PDEV;
    UINT64 VramBase = (UINT64)LouKePciGetIoRegion(PDEV, 0, 0);
    LOUSTATUS Result;

    Result = DrsdVRamHelperInitialize(Device, VramBase, VBox->AvailableVramSize);
    if(Result != STATUS_SUCCESS){
        LouPrint("VBOXGPU.SYS:Unable To Initialize VRam Helper\n");
    }
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

    VBox->LastModeHints = LouKeMallocArray(VBVA_MODE_HINT, VBox->CrtcCount, KERNEL_GENERIC_MEMORY);
    if(!VBox->LastModeHints){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    return VBoxAccelerationInitialize(VBox);

}

static DRSD_DRIVER Driver = {
    .DriverFeatures = DRIVER_MODESET | DRIVER_GXE | DRIVER_ATOMIC | DRIVER_CURSOR_HOTSPOT,
    DRSD_GXE_VRAM_DRIVER,
    DRSD_FBDEV_TTM_DRIVER_OPS,
};

LOUAPI
LOUSTATUS
AddDevice(PDRIVER_OBJECT DriverObject, struct _DEVICE_OBJECT* PlatformDevice){
    LouPrint("VBOXGPU::AddDevice()\n");
    LOUSTATUS Status = STATUS_SUCCESS;
    PPCI_DEVICE_OBJECT PDEV = PlatformDevice->PDEV;
    
    PVIRTUALBOX_PRIVATE_DATA VBox;
    if(!VboxCheckSupport(VIRTUALBOX_VBE_DISPI_ID_HGSMI)){
        return STATUS_NO_SUCH_DEVICE;
    }
    VBox = (PVIRTUALBOX_PRIVATE_DATA)DrsdDeviceManagerAllocateDevice(PDEV, &Driver, VIRTUALBOX_PRIVATE_DATA, DrsdDevice);
    if(LOU_KE_PTR_ERROR(VBox)){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    VBox->PDEV = PDEV;

    //LouKeDrsdHandleConflictingDevices(PDEV);
    //TODO handle conflicting devices

    Status = LouKeHalEnablePciDevice(PDEV);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    Status = VBoxInitializeHardware(VBox);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    
    Status = VBoxMemoryManagementInitialization(VBox);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    LouPrint("VBOXGPU::AddDevice() STATUS_SUCCESS\n");
    while(1);
    return Status;
/*

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
    return Status;

    ERROR_IRQ_FAILED_INIT:
        VirtualBoxInterruptsFailedInitialization(VBox);
    ERROR_MODE_FAILED_INIT:
        VirtualBoxModeFaildInitialization(VBox);
    ERROR_HARDWARE_FAILED_INIT:
        VirtualBoxHardwareFailedInitialization(VBox);*/
    return Status;
}

LOUAPI
LOUSTATUS
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
    DriverObject->DeviceTable = (uintptr_t)VBoxGpuPciDeviceTable;
    LouPrint("VBOXGPU::DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

void VirtualBoxHardwareFailedInitialization(PVIRTUALBOX_PRIVATE_DATA VBox){
    VirtualboxAccellerationFailedInitialization(VBox);
}