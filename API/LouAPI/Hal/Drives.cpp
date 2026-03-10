#include <Hal.h>

KERNEL_EXPORT 
LOUSTATUS 
LouKeHalIoReadPartitionTable(
    PDEVICE_OBJECT DeviceObject, 
    ULONG SectorSize, 
    BOOLEAN ReturnRecognizedPartitions, 
    PDRIVE_LAYOUT_INFORMATION* PartitionBuffer
){
    LouPrint("LouKeHalIoReadPartitionTable()\n");
    while(1);
    return STATUS_SUCCESS;
}


KERNEL_EXPORT 
LOUSTATUS 
LouKeHalIoSetPartitionInformation(
    PDEVICE_OBJECT DeviceObject, 
    ULONG SectorSize, 
    ULONG PartitionNumber, 
    ULONG PartitionType
){
    LouPrint("LouKeHalIoSetPartitionInformation()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeHalIoWritePartitionTable(
    PDEVICE_OBJECT DeviceObject, 
    ULONG SectorSize, 
    ULONG SectorsPerTrack, 
    ULONG NumberOfHeads
){
    LouPrint("LouKeHalIoWritePartitionTable()\n");
    while(1);
    return STATUS_SUCCESS;
}
