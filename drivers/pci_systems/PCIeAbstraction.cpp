#include <LouDDK.h>
#include <Hal.h>

PPCI_DEVICE_OBJECT LouKeAllocPciDevObject();
void LouKeFreePciDevObject(PPCI_DEVICE_OBJECT PDEV);

static PCIE_ECAM_DEVICE PcieEcamTrack = {0};
static mutex_t EcamAbstractionLock = {0};

LOUDDK_API_ENTRY
void LouKeInitializeEcamAbstractionDevice(
    UINTPTR         Phys,
    UINTPTR         Virt,
    UINT16          Group,
    UINT8           StartBus,
    UINT8           EndBus
){
    MutexLock(&EcamAbstractionLock);
    PPCIE_ECAM_DEVICE NewDevice = LouKeMallocType(PCIE_ECAM_DEVICE, KERNEL_GENERIC_MEMORY);
    PPCIE_ECAM_DEVICE Tmp = &PcieEcamTrack; 
    while(Tmp->Peers.NextHeader){
        Tmp = (PPCIE_ECAM_DEVICE)Tmp->Peers.NextHeader;
    }
    Tmp->Peers.NextHeader = (PListHeader)NewDevice;

    NewDevice->Phys = Phys;
    NewDevice->Virt = Virt;
    LouPrint("Virtual:%h\n", Virt);
    NewDevice->Group = Group;
    NewDevice->StartBus = StartBus;
    NewDevice->EndBus = EndBus;
    MutexUnlock(&EcamAbstractionLock);
}

LOUSTATUS 
PcieGenericReadEcam(
    PPCI_DEVICE_OBJECT Device, 
    size_t Offset, 
    size_t Width, 
    uint32_t* Value
){
    //i still dont trust the damn thing
    switch(Width){

        case sizeof(UINT8):
            *Value = READ_REGISTER_UCHAR((PUCHAR)(UINT8*)((UINTPTR)Device->EcamDevice + (UINTPTR)Offset));
            break;
        case sizeof(UINT16):
            *Value = READ_REGISTER_USHORT((PUSHORT)(UINT8*)((UINTPTR)Device->EcamDevice + (UINTPTR)Offset));
            break;
        case sizeof(UINT32):
            *Value = READ_REGISTER_ULONG((PULONG)(UINT8*)((UINTPTR)Device->EcamDevice + (UINTPTR)Offset)); 
            break;
        default:
            *Value = UINT32_MAX;
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
PcieGenericWriteEcam(
    PPCI_DEVICE_OBJECT Device, 
    size_t Offset, 
    size_t Width, 
    uint32_t Value
){
    //i dont trust my compiler
    switch(Width){
        case sizeof(UINT8):
            if(Value > UINT8_MAX){
                goto _WRITE_GAVE_INVALID;
            }
            WRITE_REGISTER_UCHAR((PUCHAR)(UINT8*)((UINTPTR)Device->EcamDevice + (UINTPTR)Offset), (UCHAR)(Value & 0x0FF));
            break;
        case sizeof(UINT16):
            if(Value > UINT16_MAX){
                goto _WRITE_GAVE_INVALID;
            }
            WRITE_REGISTER_USHORT((PUSHORT)(UINT8*)((UINTPTR)Device->EcamDevice + (UINTPTR)Offset), (USHORT)(Value & 0xFFFF));
            break;
        case sizeof(UINT32):
            WRITE_REGISTER_ULONG((PULONG)(UINT8*)((UINTPTR)Device->EcamDevice + (UINTPTR)Offset), (ULONG)Value);
            break;
        default:
            goto _WRITE_GAVE_INVALID;
    }
    return STATUS_SUCCESS;

    _WRITE_GAVE_INVALID:        
    return STATUS_INVALID_PARAMETER;

}

UNUSED static bool PcieProbeDevice(PPCI_DEVICE_OBJECT PDEV){

    PDEV->InterruptLine = LouKeGetPciInterruptLine(PDEV);
    PDEV->InterruptPin = LouKeGetPciInterruptPin(PDEV);
    LouKeHalRegisterPciDevice(
        PDEV
    );

    return true;
}

static void PcieProbeBus(
    PPCIE_ECAM_DEVICE Device
){
    UNUSED UINT8 BusIndex;
    UNUSED UINT8 BusCount = (Device->EndBus - Device->StartBus) + 1;
    UNUSED UINT8 i;
    UNUSED PVOID Base = (PVOID)Device->Virt;
    UNUSED PVOID DeviceBase;
    UNUSED PCI_DEVICE_OBJECT Test;

    for(BusIndex = 0; BusIndex < BusCount; BusIndex++){
        for(i = 0 ; i < 32; i++){

            DeviceBase = PcieCalculateDeviceBase(Base, BusIndex, i);
            Test.Group = Device->Group;
            Test.bus = BusIndex;
            Test.slot = i;
            Test.func = 0;
            Test.EcamDevice = DeviceBase;
            Test.EcamOperations.PcieReadEcam = PcieGenericReadEcam;
            Test.EcamOperations.PcieWriteEcam = PcieGenericWriteEcam;
            if(LouKeReadPciUint16(&Test, 0) != 0xFFFF){
                UINT8 HeaderType = LouKeReadPciUint8(&Test, 0x0E);
                if((HeaderType & 0x80) != 0){
                    for(size_t j = 0 ; j < 8; j++){
                        Test.func = j;
                        Test.EcamDevice = PcieCalculateFunctionBase(Base, BusIndex, i, j);
                        if(LouKeReadPciUint16(&Test, 0) != 0xFFFF){
                            PPCI_DEVICE_OBJECT NewDevice = LouKeAllocPciDevObject();
                            *NewDevice = Test;
                            PcieProbeDevice(NewDevice);
                        }
                    }
                }else{
                    PPCI_DEVICE_OBJECT NewDevice = LouKeAllocPciDevObject();
                    *NewDevice = Test;
                    PcieProbeDevice(NewDevice);
                }
            }
        }
    }
}


LOUDDK_API_ENTRY
void 
LouKePcieProbeEcam(){
    PPCIE_ECAM_DEVICE Tmp = (PPCIE_ECAM_DEVICE)PcieEcamTrack.Peers.NextHeader;
    while(Tmp){
        PcieProbeBus(Tmp);
        Tmp = (PPCIE_ECAM_DEVICE)Tmp->Peers.NextHeader;
    }
}