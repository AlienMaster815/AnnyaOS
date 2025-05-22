#include "../AmdGpuBasic.h"
#include "Radeon.h"

LOUSTATUS VgaSwitchClientDefer(P_PCI_DEVICE_OBJECT PDEV);

LOUSTATUS VgaClientRegister(P_PCI_DEVICE_OBJECT PDEV, uint32_t (*Handler)(P_PCI_DEVICE_OBJECT, bool));

PAGP_BRIDGE_DATA LouKeHalPciFindAgpBridge(
	P_PCI_DEVICE_OBJECT PDEV
);

LOUSTATUS RadeonInitializeAgpHeader(
    PRADEON_DEVICE RDEV
){
    LOUSTATUS Status = STATUS_SUCCESS;
    //P_PCI_DEVICE_OBJECT PDEV = (P_PCI_DEVICE_OBJECT)RDEV->PDEV;
    PRADEON_AGP_HEADER AgpHeader;

    //AgpHeader = (PRADEON_AGP_HEADER)LouMalloc(sizeof(RADEON_AGP_HEADER));
    //AgpHeader->Bridge = LouKeHalPciFindAgpBridge(PDEV);

    LouPrint("Trap For Incomplete Function RadeonInitializeAgpHeader\n");
    while(1);

    RDEV->AgpHeader = AgpHeader;
    return Status;
}



LOUSTATUS RadeonLoadKernelSettings(
    PRADEON_DEVICE RDEV
){  
    P_PCI_DEVICE_OBJECT PDEV = RDEV->PDEV;
    LOUSTATUS Status = STATUS_SUCCESS;

    if(LouKeHalFindCompatibility(PDEV, PCI_CAP_ID_AGP)){
        //RadeonInitializeAgpHeader(RDEV);
        RDEV->RadeonFlags |= RADEON_IS_AGP;
    }
    if(LouKeHalIsDevicePcie(PDEV)){
        RDEV->RadeonFlags |= RADEON_IS_PCIE;
    }
    else {
        RDEV->RadeonFlags |= RADEON_IS_PCI;
    }

    return Status;
}

uint64_t RadeonGartSizeAuto(
    uint8_t Family
){

    if(Family >= CHIP_TAHITI){
        return 2048;
    }
    else if(Family >= CHIP_RV770){
        return 1024;
    }

    return 512;

}


void RadeonCheckAgrs(
    PRADEON_DEVICE RDEV
){
 if((RDEV->RADEON_VRAM_LIMIT != 0) && (!IsPowerOf2(RDEV->RADEON_VRAM_LIMIT))){
        LouPrint("WARNING: VRAM LIMIT Must Be A Power Of Two\n");
        RDEV->RADEON_VRAM_LIMIT = 0;
    }


    if(RDEV->GART_SIZE == 0){
        LouPrint("GART SIZE IS 0 : ALLOCATING DETERMINING GART SIZE\n");
        RDEV->GART_SIZE = RadeonGartSizeAuto(RDEV->Family);
        LouPrint("GART SIZE IS NOW:%d\n", RDEV->GART_SIZE);
    }

    if(RDEV->GART_SIZE < 32){
        LouPrint("Gart Size (%d) Is Too Small\n", RDEV->GART_SIZE);
        RDEV->GART_SIZE = RadeonGartSizeAuto(RDEV->Family);
        LouPrint("GART SIZE IS NOW:%h\n", RDEV->GART_SIZE);
    }
    else if(!IsPowerOf2(RDEV->GART_SIZE)){
        LouPrint("Gart Size (%d) Must Be Power Of Two\n", RDEV->GART_SIZE);
        RDEV->GART_SIZE = RadeonGartSizeAuto(RDEV->Family);
        LouPrint("GART SIZE IS NOW:%h\n", RDEV->GART_SIZE);
    }

    RDEV->McGttSize = (uint64_t)RDEV->GART_SIZE << 20;

    //TODO: Add AGP Code Here to check modes

    if(!IsPowerOf2(RDEV->RADEON_VM_SIZE)){
        LouPrint("VM Size (%d) Must Be Power Of Too\n", RDEV->RADEON_VM_SIZE);
        RDEV->RADEON_VM_SIZE = 4;
        LouPrint("VM Size Is Now:%d\n");
    }

    if(RDEV->RADEON_VM_SIZE < 1){
        LouPrint("VM Size 0 Too Small MINIMUM 1 GB\n");
        RDEV->RADEON_VM_SIZE = 4;
    }

    if(RDEV->RADEON_VM_SIZE > 1024){
        LouPrint("VM Size (%d) Size Too Large MAXIMUM 1TB\n", RDEV->RADEON_VM_SIZE);
        RDEV->RADEON_VM_SIZE = 4;
        LouPrint("VM Size Is Now:%d\n", RDEV->RADEON_VM_SIZE);

    }

    if(RDEV->RADEON_VMBLOCK_SIZE == 0){
        unsigned bits = ILog2(RDEV->RADEON_VM_SIZE) + 18;

        if(RDEV->RADEON_VM_SIZE <= 8){
            RDEV->RADEON_VMBLOCK_SIZE = bits - 9;
        }
        else {
            RDEV->RADEON_VMBLOCK_SIZE = (bits + 3) / 2;
        }
        LouPrint("VM Block Size Is Now:%d\n", RDEV->RADEON_VMBLOCK_SIZE);
    }
    else if(RDEV->RADEON_VMBLOCK_SIZE < 9){
        LouPrint("VM Page Table Size (%d) Too Small\n", RDEV->RADEON_VMBLOCK_SIZE);
        RDEV->RADEON_VMBLOCK_SIZE = 9;
        LouPrint("VM Block Size Is Now:%d\n", RDEV->RADEON_VMBLOCK_SIZE);
    }

    if(RDEV->RADEON_VMBLOCK_SIZE > 24){
        LouPrint("Vm Page Table Size (%d) Too Large\n", RDEV->RADEON_VMBLOCK_SIZE);
        RDEV->RADEON_VMBLOCK_SIZE = 9;
        LouPrint("VM Block Size Is Now:%d\n", RDEV->RADEON_VMBLOCK_SIZE);
    }

}

LOUSTATUS RadeonInitializeAsic(
    PRADEON_DEVICE RDEV
);

void RadeonDevicePxQuirk(
    PRADEON_DEVICE RDEV
){

    LouPrint("Handleing Px Quirk\n");

}

uint32_t RadeonVgaSetDecode(P_PCI_DEVICE_OBJECT PDEV, bool State){

	return 0;
}

#define RadeonInitialize(RDEV) (RDEV)->AsicHandlers.InitializationHandler(RDEV)

LOUSTATUS InitializeRadeonDevice(
    PRADEON_DEVICE RDEV
){
    LOUSTATUS Status = STATUS_SUCCESS;

    RDEV->Shutdown = false;
    RDEV->Family = RDEV->RadeonFlags & RADEON_FAMILY_BITS;
    RDEV->AtomBios = false;
    RDEV->MsTimeout = RADEON_MAX_TIMEOUT_MS;
    RDEV->McGttSize = 512 * 1024 * 1024;
    RDEV->Acceleration = false;
    
    RadeonCheckAgrs(RDEV);

    RDEV->RadeonVmMaxPfn = RDEV->RADEON_VMBLOCK_SIZE << 18;
   
    Status = RadeonInitializeAsic(RDEV);
    if(Status != STATUS_SUCCESS){
        return STATUS_UNSUCCESSFUL;
    }

    if((RDEV->Family >= CHIP_RS400) && (RDEV->RadeonFlags & RADEON_IS_IGP)){
        RDEV->RadeonFlags &= ~(RADEON_IS_AGP);
    }

    if(RDEV->Family >= CHIP_CAYMAN){
        RDEV->McMask = 0xffffffffff;
    }
    else if(RDEV->Family >= CHIP_CEDAR){
        RDEV->McMask = 0xfffffffff;
    }else{
        RDEV->McMask = 0xffffffff;   
    }

    UNUSED int DmaBits = 40;

    if(RDEV->RadeonFlags & RADEON_IS_AGP){
        DmaBits = 32;
    }
    if((RDEV->RadeonFlags & RADEON_IS_PCI) && (RDEV->Family <= CHIP_RS740)){
        DmaBits = 32;
    }
    LouKeHalPciSetMaster(RDEV->PDEV);


    if(RDEV->Family >= CHIP_BONAIRE){
        RDEV->RMMIO_BASE = (uint64_t)LouKeHalGetPciVirtualBaseAddress((PPCI_COMMON_CONFIG)RDEV->PDEV->CommonConfig, 5);
        RDEV->RMMIO_SIZE = LouKeHalGetPciBaseAddressSize((PPCI_COMMON_CONFIG)RDEV->PDEV->CommonConfig, 5);
    }else{
        RDEV->RMMIO_BASE = (uint64_t)LouKeHalGetPciVirtualBaseAddress((PPCI_COMMON_CONFIG)RDEV->PDEV->CommonConfig, 2);
        RDEV->RMMIO_SIZE = LouKeHalGetPciBaseAddressSize((PPCI_COMMON_CONFIG)RDEV->PDEV->CommonConfig, 2);
    }

    LouPrint("RMMIO BASE Is:%h\n", RDEV->RMMIO_BASE);
    LouPrint("RMMIO SIZE Is:%h\n", RDEV->RMMIO_SIZE);

    PPCI_COMMON_CONFIG Config = (PPCI_COMMON_CONFIG)RDEV->PDEV->CommonConfig;

    for(uint8_t i = 0 ; i < 6; i ++){
        uint32_t TmpBAR = Config->Header.u.type0.BaseAddresses[i];
        if(TmpBAR & 1){
            LouPrint("BAR:%d Is The Io Port\n", i);
            RDEV->RIO_MEM = (uint64_t)LouKeHalGetPciVirtualBaseAddress((PPCI_COMMON_CONFIG)RDEV->PDEV->CommonConfig, i);
            LouPrint("IO Address:%h\n", RDEV->RIO_MEM);
            break;
        }
    }

    //if(RDEV->RadeonFlags & RADEON_IS_PX){
    //    RadeonDevicePxQuirk(RDEV);
    //}

    VgaClientRegister(RDEV->PDEV, RadeonVgaSetDecode);

    Status = RadeonInitialize(RDEV);

    return Status;

}


LOUSTATUS RadeonDrvMain(
    P_PCI_DEVICE_OBJECT PDEV,
	uint64_t RadeonFlags
){
    LOUSTATUS Status = STATUS_SUCCESS;
    LouPrint("Initializing Radeon GPU\n");
    LouKeHalEnablePciDevice(PDEV);

    Status = VgaSwitchClientDefer(PDEV);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    PRADEON_DEVICE RDEV = (PRADEON_DEVICE)LouMalloc(sizeof(RADEON_DEVICE));
    RDEV->PDEV = PDEV;
    RDEV->RadeonFlags = RadeonFlags;
    PDEV->DeviceExtendedObject = (uintptr_t)RadeonFlags;

    Status = RadeonLoadKernelSettings(RDEV);
    Status = InitializeRadeonDevice(RDEV);



    LouPrint("Radeon GPU Initialized\n");
    return Status;
}