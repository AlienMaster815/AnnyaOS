
#include <LouDDK.h>
#include <Hal.h>

LOUSTATUS LouKeHalEnablePciDevice(P_PCI_DEVICE_OBJECT PDEV){
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
LOUSTATUS LouKeHalPciSetMmio(P_PCI_DEVICE_OBJECT PDEV){
    LOUSTATUS Status = STATUS_SUCCESS;

    LouKeWritePciCommandRegister(PDEV, MEMORY_SPACE_ENABLE);

    return Status;
}

uint8_t PciFindCapStart(P_PCI_DEVICE_OBJECT PDEV){

    uint16_t Header = getHeaderType(PDEV->Group, PDEV->bus, PDEV->slot, PDEV->func);

    uint16_t DeviceStatus = LouKeReadPciUint16(PDEV, PCI_STATUS);
    if(!(DeviceStatus & PCI_STATUS_CAP_LIST)){
        return 0;
    }

    switch(Header){
        case 0:
        case 1:
            return 0x34;
        case 2:
            return 0x14;
    }

    return 0;
}

uint8_t PciFindNextCapTtl(
    P_PCI_DEVICE_OBJECT PDEV, 
    uint8_t Position,
    int32_t Capability,
    int32_t* TTL
){

    uint8_t Identification;
    uint16_t Entity;

    Position = LouKeReadPciUint8(PDEV, Position);

    while((*TTL)--){
        if(Position < 0x40){
            break;
        }

        Position &= ~3;

        Entity = LouKeReadPciUint16(PDEV, Position);

        Identification = Entity & 0xFF;
        if(Identification == 0xFF){
            break;
        }
        if(Identification == Capability){
            return Position;
        }
        
        Position = (Entity >> 8);
        
    }
    return 0;
}

uint8_t PciFindNextCap(
    P_PCI_DEVICE_OBJECT PDEV,
    uint8_t Position,
    int32_t Capability
){
    int32_t TTL = 48;
    return PciFindNextCapTtl(PDEV, Position, Capability, &TTL);
}

uint8_t LouKeHalFindCompatibility(
    P_PCI_DEVICE_OBJECT PDEV,
    int32_t Capability
){
    uint8_t Position = 0;

    Position = PciFindCapStart(PDEV);
    if(Position){
        Position = PciFindNextCap(PDEV, Position, Capability);
    }

    return Position;
}

LOUDDK_API_ENTRY
bool LouKeHalIsDevicePcie(
    P_PCI_DEVICE_OBJECT PDEV
){
    return LouKeHalFindCompatibility(PDEV, 0x10) ? true : false;
}