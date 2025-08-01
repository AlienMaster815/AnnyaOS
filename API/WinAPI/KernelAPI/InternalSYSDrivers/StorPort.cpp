#include <LouDDK.h>
#include <NtAPI.h>

KERNEL_IMPORT LOUSTATUS RequestPhysicalAddress(
    uint64_t VAddress,
    uint64_t* PAddress
);

KERNEL_IMPORT uint64_t GetAllocationBlockSize(uint64_t Address);


UNUSED static PSTOR_PORT_STACK_OBJECT StorPortStack[255] = {0};

PSTOR_PORT_STACK_OBJECT GetStorPortObject(PDRIVER_OBJECT DrvObject){
    
    for(uint8_t i = 0; i < 255; i++){
        if(StorPortStack[i]->DrvObj == DrvObject){
            return StorPortStack[i];
        }
    }
    
    return 0x00;
}

STOR_PHYSICAL_ADDRESS StorPortGetPhysicalAddress(
     PVOID HwDeviceExtension,
     PSCSI_REQUEST_BLOCK Srb,
     PVOID VirtualAddress,
    ULONG *Length
){
    LouPrint("void StorPortGetPhysicalAddress()\n");

    STOR_PHYSICAL_ADDRESS Result;

    uint64_t PhysicalAdress;
    RequestPhysicalAddress((uint64_t)VirtualAddress, &PhysicalAdress);

    Result.QuadPart = PhysicalAdress;

    uint64_t BlockSize =  GetAllocationBlockSize((uint64_t)VirtualAddress);

    *Length = (ULONG)BlockSize;

    //LouPrint("Length:%d\n", *Length);
    //LouPrint("VirtualAddress:%h\n",VirtualAddress);
    //LouPrint("BlockSize:%h\n", *Length);

    LouPrint("void StorPortGetPhysicalAddress() SUCCESS\n");
    return (STOR_PHYSICAL_ADDRESS)Result;
}

VOID StorPortStallExecution(
    ULONG Microseconds
){
    //LouPrint("void StorPortStallExecution()\n");
    if(Microseconds <= 1999){//sanity check
        sleep(2);
        //LouPrint("void StorPortStallExecution() SUCCESS\n");
        return;
    }

    Microseconds /= 1000;
    sleep(Microseconds);
    //LouPrint("void StorPortStallExecution() SUCCESS\n");

}

void StorPortNotification(
  SCSI_NOTIFICATION_TYPE NotificationType,
  PVOID HwDeviceExtension,
  ...
){
    LouPrint("void StorPortNotification()\n");



    LouPrint("void StorPortNotification() LOUSINE IS NOTIFIED\n");
    while(1);
}

void StorPortSetDeviceQueueDepth(){
    LouPrint("void StorPortSetDeviceQueueDepth()\n");
    while(1);
}

PVOID StorPortGetUncachedExtension(
   PVOID HwDeviceExtension,
   PPORT_CONFIGURATION_INFORMATION ConfigInfo,
   ULONG NumberOfBytes
){
    LouPrint("void StorPortGetUncachedExtension()\n");

    LouPrint("Allocating:%d Bytes\n",NumberOfBytes);

    PVOID AllocatedBlock = LouKeAllocateUncachedVMemoryEx(NumberOfBytes, KILOBYTE_PAGE);

    if(AllocatedBlock == 0x00){
        LouPrint("void StorPortGetUncachedExtension() FAILED : Insufficent Resources\n");
        return 0x00;
    }

    LouPrint("void StorPortGetUncachedExtension() SUCCESS\n");
    return AllocatedBlock;
}

NTSTATUS StorPortInitialize(
    PDRIVER_OBJECT DrvObj,
    PUNICODE_STRING RegistryEntry,
    PSTORPORT_HW_INITIALIZATION_DATA HwInitializationData,
    PVOID HwContext
){
    LouPrint("NTSTATUS StorPortInitialize()\n");

    
    if((DrvObj == 0x00) || (RegistryEntry == 0x00) || 
       (HwInitializationData == 0x00)){
        LouPrint("One Or More Parameters are Null\n");
        LouPrint("NTSTATUS StorPortInitialize() STATUS_INVALID_PARAMETER\n");
        return STATUS_INVALID_PARAMETER;
    }

    uint8_t i = 0;
    for(;i < 255; i++){
        if(StorPortStack[i] == 0x00){
            break;
        }
    }

    if(i == 254){
        LouPrint("NTSTATUS StorPortInitialize() STATUS_INSUFFICIENT_RESOURCES\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    StorPortStack[i] = LouKeMallocType(STOR_PORT_STACK_OBJECT, KERNEL_GENERIC_MEMORY);

    if(StorPortStack[i] == 0x00){
        LouPrint("NTSTATUS StorPortInitialize() STATUS_INSUFFICIENT_RESOURCES\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    LouPrint("Found An Available Storport Slot [slot Number]:%d\n", i);


    StorPortStack[i]->DrvObj = DrvObj;

    
    StorPortStack[i]->FindAdapter = (uint64_t)HwInitializationData->HwFindAdapter;
    StorPortStack[i]->InitAdapter = (uint64_t)HwInitializationData->HwInitialize;
    StorPortStack[i]->InterruptHandler = (uint64_t)HwInitializationData->HwInterrupt;

    if(HwInitializationData->DeviceExtensionSize > 0x00){
        StorPortStack[i]->DeviceExtention = LouKeMalloc(HwInitializationData->DeviceExtensionSize, KERNEL_GENERIC_MEMORY);
    }
    if(HwInitializationData->SpecificLuExtensionSize > 0x00){
        StorPortStack[i]->SpecificLuExtention = LouKeMalloc(HwInitializationData->SpecificLuExtensionSize, KERNEL_GENERIC_MEMORY);
    }
    if(HwInitializationData->SrbExtensionSize > 0x00){
        StorPortStack[i]->SrbExtension = LouKeMalloc(HwInitializationData->SrbExtensionSize, KERNEL_GENERIC_MEMORY);
    }

    StorPortStack[i]->ConfigInfo = (PPORT_CONFIGURATION_INFORMATION)LouKeMalloc(sizeof(PORT_CONFIGURATION_INFORMATION), KERNEL_GENERIC_MEMORY);

    StorPortStack[i]->ConfigInfo->NumberOfAccessRanges = HwInitializationData->NumberOfAccessRanges;

    StorPortStack[i]->ConfigInfo->AddressRanges = (uint64_t*)LouKeMallocArray(ACCESS_RANGE, StorPortStack[i]->ConfigInfo->NumberOfAccessRanges, KERNEL_GENERIC_MEMORY);


    LouPrint("NTSTATUS StorPortInitialize() STATUS SUCCESS\n");
    return STATUS_SUCCESS;
}   

void StorPortGetScatterGatherList(){
    LouPrint("void StorPortGetScatterGatherList()\n");
    while(1);
}

PVOID StorPortGetDeviceBase(
    PVOID   HwDeviceExtension,
    INTERFACE_TYPE BusType,
    ULONG   SystemIoBusNumber,
    PHYSICAL_ADDRESS IoAddress,
    ULONG   NumberOfBytes,
    BOOLEAN InIoSpace
){
    LouPrint("PVOID StorPortGetDeviceBase()\n");

    if(IoAddress.QuadPart == 0x01){
        LouPrint("StorPort Address Not Valid\n");
        LouPrint("PVOID StorPortGetDeviceBase() OK\n");
        return (PVOID)0x00;
    }

    LouPrint("IoAddress:%h\n", IoAddress.QuadPart);
    LouPrint("Size:%h\n", NumberOfBytes);

    uint64_t NewAddress = ((uint64_t)IoAddress.QuadPart & ~(MEGABYTE_PAGE - 1));

    for(uint64_t i = 0; i <= NumberOfBytes + (IoAddress.QuadPart - NewAddress); i+= MEGABYTE_PAGE){
        LouMapAddress(NewAddress + i, NewAddress + i, KERNEL_PAGE_WRITE_PRESENT, MEGABYTE_PAGE);
    }

    LouPrint("PVOID StorPortGetDeviceBase() SUCCESS\n");
    return (PVOID)IoAddress.QuadPart;
}
/**
typedef enum _BUS_DATA_TYPE {
    Cmos,
    EisaConfiguration,
    Pos,
    CbusConfiguration,
    PCIConfiguration,
    VMEConfiguration,
    NuBusConfiguration,
    PCMCIAConfiguration,
    MPIConfiguration,
    MPSAConfiguration,
    PNPISAConfiguration,
    SgiInternalConfiguration,
    MaximumBusDataType
} BUS_DATA_TYPE;
*/
// Holds Adapter Information

ULONG StorPortGetBusData(
  PVOID HwDeviceExtension,
  ULONG BusDataType,
  ULONG SystemIoBusNumber,
  ULONG SlotNumber,
  PVOID Buffer,
  ULONG Length
){
    LouPrint("void StorPortGetBusData()\n");


    if(BusDataType == PCIConfiguration){
        LouPrint("StorPort: Retrieving PCI CONFIGURATION INFORMATION\n");
        // Ensure the buffer is not NULL and the length is valid
        if (Buffer == 0x00 || Length == 0) {
            LouPrint("Invalid buffer or length\n");
            return 0;
        }
        PPCI_COMMON_CONFIG ConfigBuffer = (PPCI_COMMON_CONFIG)Buffer;

        GetPciConfiguration(0, SystemIoBusNumber, SlotNumber, 0,ConfigBuffer);

        LouPrint("void StorPortGetBusData() COMPLETE\n");
        return sizeof(PCI_COMMON_CONFIG);
    }

    LouPrint("void StorPortGetBusData() FAILED\n");
    LouPrint("Unsuported Type\n");
    return 0;
}

