
#include <LouDDK.h>
#include <Hal.h>

LOUSTATUS LouKeHalEnablePciDevice(PPCI_DEVICE_OBJECT PDEV){
    uint16_t Command = LouKeReadPciCommandRegister(PDEV);
    Command &= ~(1 << 10); 
    LouKeWritePciCommandRegister(PDEV, Command | MEMORY_SPACE_ENABLE | IO_SPACE_ENABLE);
    if(!(LouKeReadPciCommandRegister(PDEV) & (MEMORY_SPACE_ENABLE | IO_SPACE_ENABLE))){
        LouPrint("Pci Device Error : Error Enableing Pci Device Bus:%d :: Slot:%d :: Function:%d\n", PDEV->bus, PDEV->slot, PDEV->func);
        return STATUS_IO_DEVICE_ERROR;
    }
    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
LOUSTATUS LouKeHalPciSetMmio(PPCI_DEVICE_OBJECT PDEV){
    LOUSTATUS Status = STATUS_SUCCESS;

    LouKeWritePciCommandRegister(PDEV, MEMORY_SPACE_ENABLE);

    return Status;
}


UINT8 LouKePciHalGetNextCapabilityPointer(
    PPCI_DEVICE_OBJECT PDEV, 
    UINT8 CurrentPointer
){
    UINT8 NextPointer = LouKeReadPciUint8(PDEV, CurrentPointer + 1) & ~(0b11);

    if(CurrentPointer == NextPointer){
        return 0x00;
    }

    return NextPointer;
}

uint8_t LouKePciReadCapabilitiesPointer(PPCI_DEVICE_OBJECT PDEV);

UINT8 LouKeHalPciGetCapabilityPointer(
    PPCI_DEVICE_OBJECT   PDEV,
    UINT8               CapID
){
    UINT8 CurrentPointer = LouKePciReadCapabilitiesPointer(PDEV);
    UINT8 CurrentID = 0x00;
    if(!CurrentPointer){
        return 0x00;
    }
    while(CurrentPointer){
        CurrentID = LouKeReadPciUint8(PDEV, CurrentPointer);
        //LouPrint("ID:%h\n", CurrentID);
        if(CurrentID == CapID){
            return CurrentPointer;
        }
        CurrentPointer = LouKePciHalGetNextCapabilityPointer(PDEV, CurrentPointer);
    }
    return CurrentPointer;
}