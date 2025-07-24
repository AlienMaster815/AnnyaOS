#include <usb.h>
#include <Hal.h>

typedef void (*COMPANION_WORK_FUNCTION)(P_PCI_DEVICE_OBJECT PDEV, PUSB_HOST_CONTROLER_DEVICE HostDevice, PUSB_HOST_CONTROLER_DEVICE CompanionHostDevice); 

static void EhciWorkPreAddition(
    P_PCI_DEVICE_OBJECT PDEV, 
    PUSB_HOST_CONTROLER_DEVICE HostDevice, 
    PUSB_HOST_CONTROLER_DEVICE CompanionHostDevice
){

    LouPrint("EhciWorkPreAddition()\n");
    while(1);
}

static void EhciWorkPostAddition(
    P_PCI_DEVICE_OBJECT PDEV, 
    PUSB_HOST_CONTROLER_DEVICE HostDevice, 
    PUSB_HOST_CONTROLER_DEVICE CompanionHostDevice
){
    LouPrint("EhciWorkPostAddition()\n");
    while(1);
}

static void NonEhciWorkAddition(
    P_PCI_DEVICE_OBJECT PDEV, 
    PUSB_HOST_CONTROLER_DEVICE HostDevice, 
    PUSB_HOST_CONTROLER_DEVICE CompanionHostDevice
){
    LouPrint("NonEhciWorkAddition()\n");
    while(1);
}

UNUSED
static 
void 
DoForAllCompanions(
    P_PCI_DEVICE_OBJECT Self,
    PPCI_DEVICE_GROUP DeviceGroup, 
    PUSB_HOST_CONTROLER_DEVICE HostDevice, 
    COMPANION_WORK_FUNCTION WorkToDo
){
    PPCI_COMMON_CONFIG  CommonConfig;
    //do for 8 all posible companions
    for(uint8_t i = 0; i < 8; i++){
        if(DeviceGroup[i].PDEV){
            CommonConfig = (PPCI_COMMON_CONFIG)DeviceGroup[i].PDEV->CommonConfig;
            if(
                (
                    (CommonConfig->Header.ProgIf != 0x10) && 
                    (CommonConfig->Header.ProgIf != 0x20) && 
                    (CommonConfig->Header.ProgIf != 0x30)
                ) 
                || 
                (
                    (CommonConfig->Header.BaseClass != 0x0C) || 
                    (CommonConfig->Header.SubClass != 0x03)
                )
            ){
                continue;
            }

            if((!DeviceGroup[i].PDEV->DevicePrivateData) || (DeviceGroup[i].PDEV == Self)){
                continue;
            }
            
            //LouPrint("Master Bus :%d:%d:%d\n", Self->bus, Self->slot, Self->func);
            //LouPrint("Slave  Bus :%d:%d:%d\n", DeviceGroup[i].PDEV->bus, DeviceGroup[i].PDEV->slot, DeviceGroup[i].PDEV->func);

            //LouPrint("Master Host ProgIF:%h :: Slave Host ProgIF:%h\n", ((PPCI_COMMON_CONFIG)Self->CommonConfig)->Header.ProgIf, ((PPCI_COMMON_CONFIG)DeviceGroup[i].PDEV->CommonConfig)->Header.ProgIf);
            WorkToDo(DeviceGroup[i].PDEV, HostDevice, (PUSB_HOST_CONTROLER_DEVICE)DeviceGroup[i].PDEV->DevicePrivateData);
        }   
    }

}

LOUSTATUS LoUSBAddHostController(PUSB_HOST_CONTROLER_DEVICE HostController){
    LouPrint("Adding New USB Host Controller\n");



    LouPrint("Added New USB Host Controller Succefully\n");
    return STATUS_SUCCESS;
}

LOUSTATUS LoUSBInitializeHostController(P_PCI_DEVICE_OBJECT PDEV, PUSB_HOST_CONTROLER_DRIVER HostDriver){
    LouPrint("Initializing Host Controller\n");
    UNUSED PUSB_HOST_CONTROLER_DEVICE HostController;
    LOUSTATUS Status = STATUS_SUCCESS;

    if(!HostDriver){
        return STATUS_NO_SUCH_DEVICE;
    }

    if(!NT_SUCCESS(LouKeHalEnablePciDevice(PDEV))){
        return STATUS_NO_SUCH_DEVICE;
    }

    //now the fun begins

    //according to XHCI specification there is different
    //interrupt management then the common EHCI, OHCI and UHCI
    //so we are just going to skip XHCI 
    if((HostDriver->DriverFlags & HCD_MASK) < HCD_USB3_0){

        //TODO: Create A IRQ Allocator

        //RegisterInterruptHandler(HostDriver->InterruptHandler, LouKeGetPciInterruptLine(PDEV), false, (uint64_t)HostDriver);

    }

    HostController = (PUSB_HOST_CONTROLER_DEVICE)LouKeMallocType(USB_HOST_CONTROLER_DEVICE,  KERNEL_GENERIC_MEMORY);

    HostController->PDEV = PDEV;
    PDEV->DevicePrivateData = (uintptr_t)&HostController;

    //TODO: Check for Amd Resume Bug
    LouPrint("LoUSBInitializeHostController\n");
    while(1);
    if(HostDriver->DriverFlags & HCD_MEMORY){
        //OHCI and EHCI Devices Only
        HostController->DeviceMemory = 0x00;//LouKeHalGetPciVirtualBaseAddress((PPCI_COMMON_CONFIG)PDEV->CommonConfig, 0);
        HostController->IoRegionBase = (uintptr_t)HostController->DeviceMemory; 
        HostController->IoRegionLimit = (size_t)LouKeHalGetPciBaseAddressSize((PPCI_COMMON_CONFIG)PDEV->CommonConfig, 0);
        //LouPrint("Host Controller IO Base:%h\n", HostController->IoRegionBase);
        //LouPrint("Host Controller IO Size:%h\n", HostController->IoRegionLimit);

        if(!HostController->DeviceMemory){
            LouPrint("Device Has No MMIO\n");
            return STATUS_IO_DEVICE_ERROR;
        }        
    }
    else{
        //TODO: Initialization for UHCI
    }

    //Ready Set Bus Master
    LouKeHalPciSetMaster(PDEV);

    if(((PPCI_COMMON_CONFIG)PDEV->CommonConfig)->Header.ProgIf == 0x20){ //if Genuine EHCI
        LouPrint("Initializing EHCI Class Device\n");
        PPCI_DEVICE_GROUP EhciSiblings = LouKeHalOpenPciCompanions(PDEV);
        DoForAllCompanions(PDEV, EhciSiblings, HostController, EhciWorkPreAddition);
        Status = LoUSBAddHostController(HostController);
        if(!NT_SUCCESS(Status)){
            PDEV->DevicePrivateData = 0;
        }
        DoForAllCompanions(PDEV, EhciSiblings, HostController, EhciWorkPostAddition);
        LouKeHalClosePciCompanions(EhciSiblings);
    }
    else{
        //OHCI, UHCI, XHCI
        LouPrint("Initializing Non Ehci Class Device\n");
        PPCI_DEVICE_GROUP HcdSiblings = LouKeHalOpenPciCompanions(PDEV);
        Status = LoUSBAddHostController(HostController);
        if(!NT_SUCCESS(Status)){
            PDEV->DevicePrivateData = 0;
        }
        else{
            DoForAllCompanions(PDEV, HcdSiblings, HostController, NonEhciWorkAddition);
        }
        LouKeHalClosePciCompanions(HcdSiblings);
    }

    if(!NT_SUCCESS(Status)){
        //TODO: Put HCD and Disable Device
        return Status;
    }

    //TODO:configure power management

    return Status;
}

LOUSTATUS LoUSBDeInitializeHostController(P_PCI_DEVICE_OBJECT PDEV, PUSB_HOST_CONTROLER_DRIVER HostDriver){
    LouPrint("DeInitializing Host Controller\n");
    

    return STATUS_SUCCESS;
}