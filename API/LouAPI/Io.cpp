//Copyright GPL-2 Tyler Grenier (2026)
#include <LouDDK.h>

KERNEL_EXPORT 
LOUSTATUS 
LouKeIoAllocateAdapterChannel( //Export KULA as NTOSKRNL.EXE:IoAllocateAdapterChannel
    PADAPTER_OBJECT         AdapterObject, 
    PDEVICE_OBJECT          DeviceObject, 
    ULONG                   NumberOfMapRegisters, 
    PDRIVER_CONTROL         ExecutionRoutine, 
    PVOID                   Context
){
    LouPrint("LouKeIoAllocateAdapterChannel()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
void 
LouKeIoAllocateController(
    PCONTROLLER_OBJECT  ControllerObject, 
    PDEVICE_OBJECT      DeviceObject, 
    PDRIVER_CONTROL     ExecutionRoutine, 
    PVOID               Context
){
    LouPrint("LouKeIoAllocateController()\n");
    while(1);
}

KERNEL_EXPORT 
void 
LouKeIoClearActivityIdThread(
    LPCGUID OriginalId
){
    LouPrint("LouKeIoClearActivityIdThread()\n");
    while(1);
}

KERNEL_EXPORT 
PCONTROLLER_OBJECT 
LouKeIoCreateController(
    ULONG Size
){
    LouPrint("LouKeIoCreateController()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeIoDecrementKeepAliveCount(
    PFILE_OBJECT            FileObject, 
    struct _EPROCESS*       Process
){
    LouPrint("LouKeIoDecrementKeepAliveCount()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
void 
LouKeIoDeleteController(
    PCONTROLLER_OBJECT ControllerObject
){
    LouPrint("LouKeIoDeleteController()\n");
    while(1);       
}

KERNEL_EXPORT 
void 
LouKeIoFreeController(
    PCONTROLLER_OBJECT ControllerObject
){
    LouPrint("LouKeIoFreeController()\n");
    while(1);
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeIoGetActivityIdIrp(
    PIRP    Irp, 
    PGUID   Guid
){
    LouPrint("LouKeIoGetActivityIdIrp()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LPCGUID 
LouKeIoGetActivityIdThread(){
    LouPrint("LouKeIoGetActivityIdThread()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
PCONFIGURATION_INFORMATION 
LouKeIoGetConfigurationInformation(){
    LouPrint("LouKeIoGetConfigurationInformation()\n");
    return 0x00;
}

KERNEL_EXPORT 
PGENERIC_MAPPING 
LouKeIoGetFileObjectGenericMapping(){
    LouPrint("LouKeIoGetFileObjectGenericMapping()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
PEPROCESS 
LouKeIoGetInitiatorProcess(
    PFILE_OBJECT FileObject
){
    LouPrint("LouKeIoGetInitiatorProcess()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
IO_PAGING_PRIORITY 
LouKeIoGetPagingIoPriority(
    PIRP Irp
){
    LouPrint("LouKeIoGetPagingIoPriority()\n");
    while(1);
    return (IO_PAGING_PRIORITY)0x00;
}

KERNEL_EXPORT 
PIO_FOEXT_SHADOW_FILE 
LouKeIoGetShadowFileInformation(
    PFILE_OBJECT FileObject
){
    LouPrint("LouKeIoGetShadowFileInformation()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeIoIncrementKeepAliveCount(
    PFILE_OBJECT    FileObject, 
    PEPROCESS       Process
){
    LouPrint("LouKeIoIncrementKeepAliveCount()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOGICAL 
LouKeIoIsValidIrpStatus(
    LOUSTATUS Status
){
    LouPrint("LouKeIoIsValidIrpStatus()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
PIRP
LouKeIoMakeAssociatedIrp(
    PIRP    Irp, 
    CCHAR   StackSize
){
    LouPrint("LouKeIoMakeAssociatedIrp()\n");
    while(1);
    return 0x00;    
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeIoPropagateActivityIdToThread(
    PIRP        Irp, 
    LPGUID      PropagatedId, 
    LPCGUID*    OriginalId
){
    LouPrint("LouKeIoPropagateActivityIdToThread()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeIoQueryFullDriverPath(
    PDRIVER_OBJECT  DriverObject, 
    PUNICODE_STRING FullPath
){
    LouPrint("LouKeIoQueryFullDriverPath()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
void 
LouKeIoRaiseHardError(
    PIRP            Irp, 
    PVPB            Vpb, 
    PDEVICE_OBJECT  RealDeviceObject
){
    LouPrint("LouKeIoRaiseHardError()\n");
    while(1);
}

KERNEL_EXPORT 
BOOLEAN 
LouKeIoRaiseInformationalHardError(
    LOUSTATUS       ErrorStatus, 
    PUNICODE_STRING String, 
    PKTHREAD        Thread
){
    LouPrint("LouKeIoRaiseInformationalHardError()\n");
    while(1);
    return false;
}

KERNEL_EXPORT 
PVOID 
LouKeIoRegisterBootDriverCallback(
    PBOOT_DRIVER_CALLBACK_FUNCTION  CallbackFunction, 
    PVOID                           CallbackContext
){
    LouPrint("LouKeIoRegisterBootDriverCallback()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
void 
LouKeIoRegisterBootDriverReinitialization(
    PDRIVER_OBJECT          DriverObject, 
    PDRIVER_REINITIALIZE    DriverReinitializationRoutine,
    PVOID                   Context
){
    LouPrint("LouKeIoRegisterBootDriverReinitialization()\n");
    while(1);
}

KERNEL_EXPORT 
void 
LouKeIoRegisterDriverReinitialization(
    PDRIVER_OBJECT          DriverObject, 
    PDRIVER_REINITIALIZE    DriverReinitializationRoutine, 
    PVOID                   Context
){
    LouPrint("LouKeIoRegisterDriverReinitialization()\n");
    while(1);
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeIoReportDetectedDevice(
    PDRIVER_OBJECT                  DriverObject, 
    INTERFACE_TYPE                  LegacyBusType, 
    ULONG                           BusNumber, 
    ULONG                           SlotNumber, 
    PCM_RESOURCE_LIST               ResourceList, 
    PIO_RESOURCE_REQUIREMENTS_LIST  ResourceRequirements, 
    BOOLEAN                         ResourceAssigned, 
    PDEVICE_OBJECT*                 DeviceObject
){
    LouPrint("LouKeIoReportDetectedDevice()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeIoReportResourceForDetection(
    PDRIVER_OBJECT      DriverObject, 
    PCM_RESOURCE_LIST   DriverList, 
    ULONG               DriverListSize, 
    PDEVICE_OBJECT      DeviceObject, 
    PCM_RESOURCE_LIST   DeviceList, 
    ULONG               DeviceListSize, 
    PBOOLEAN            ConflictDetected
){
    LouPrint("LouKeIoReportResourceForDetection()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeIoReportRootDevice(
    PDRIVER_OBJECT DriverObject
){
    LouPrint("LouKeIoReportRootDevice()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeIoSetActivityIdIrp(
    PIRP        Irp, 
    LPCGUID     Guid
){
    LouPrint("LouKeIoSetActivityIdIrp()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LPCGUID 
LouKeIoSetActivityIdThread(
    LPCGUID ActivityId
){
    LouPrint("LouKeIoSetActivityIdThread()\n");
    while(1);
    return 0x00;    
}

KERNEL_EXPORT 
void 
LouKeIoSetHardErrorOrVerifyDevice(
    PIRP            Irp, 
    PDEVICE_OBJECT  DeviceObject
){
    LouPrint("LouKeIoSetHardErrorOrVerifyDevice()\n");
    while(1);
}

KERNEL_EXPORT 
void 
LouKeIoSetMasterIrpStatus(
    PIRP        MasterIrp, 
    LOUSTATUS   Status
){
    LouPrint("LouKeIoSetMasterIrpStatus()\n");
    while(1);
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeIoSetShadowFileInformation(
    PFILE_OBJECT    FileObject, 
    PFILE_OBJECT    BackingFileObject, 
    PVOID           BackingFltInstance
){
    LouPrint("LouKeIoSetShadowFileInformation()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeIoSetSystemPartition(
    PUNICODE_STRING VolumeNameString
){
    LouPrint("LouKeIoSetSystemPartition()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
BOOLEAN 
LouKeIoSetThreadHardErrorMode(
    BOOLEAN EnableHardErrors
){
    LouPrint("LouKeIoSetThreadHardErrorMode()\n");
    while(1);
    return false;
}

KERNEL_EXPORT 
void 
LouKeIoTransferActivityId(
    LPCGUID     ActivityId, 
    LPCGUID     RelatedActivityId
){
    LouPrint("LouKeIoTransferActivityId()\n");
    while(1);
}

KERNEL_EXPORT 
void 
LouKeIoUnregisterBootDriverCallback(
    PVOID CallbackHandle
){
    LouPrint("LouKeIoUnregisterBootDriverCallback()\n");
    while(1);
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeIoVerifyPartitionTable(
    PDEVICE_OBJECT  DeviceObject, 
    BOOLEAN         FixErrors
){
    LouPrint("LouKeIoVerifyPartitionTable()\n");
    while(1);
    return STATUS_SUCCESS;   
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeIoVolumeDeviceToDosName(
    PVOID               VolumeDeviceObject, 
    PUNICODE_STRING     DosName
){
    LouPrint("LouKeIoVolumeDeviceToDosName()\n");
    while(1);
    return STATUS_SUCCESS;
}


KERNEL_EXPORT 
BOOLEAN 
LouKeIoCheckFileObjectOpenedAsCopyDestination(
    PFILE_OBJECT FileObject
){
    LouPrint("LouKeIoCheckFileObjectOpenedAsCopyDestination()\n");
    while(1);
    return false;
}

KERNEL_EXPORT 
BOOLEAN 
LouKeIoCheckFileObjectOpenedAsCopySource(
    PFILE_OBJECT FileObject
){
    LouPrint("LouKeIoCheckFileObjectOpenedAsCopySource()\n");
    while(1);
    return false;
}

KERNEL_EXPORT 
PDEVICE_OBJECT 
LouKeIoGetAttachedDeviceReference(
    PDEVICE_OBJECT DeviceObject
){
    LouPrint("LouKeIoGetAttachedDeviceReference()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
void 
LouKeIoSetStartIoAttributes(
    PDEVICE_OBJECT  DeviceObject, 
    BOOLEAN         DeferredStartIo, 
    BOOLEAN         NonCancelable
){
    LouPrint("LouKeIoSetStartIoAttributes()\n");
    while(1);
}

KERNEL_EXPORT 
void 
LouKeIoSizeOfIrp(
    uint64_t StackSize
){
    LouPrint("LouKeIoSizeOfIrp()\n");
    while(1);
}

KERNEL_EXPORT 
void 
LouKeIoStartNextPacket(
    PDEVICE_OBJECT DeviceObject, 
    BOOLEAN Cancelable
){
    LouPrint("LouKeIoStartNextPacket()\n");
}

KERNEL_EXPORT 
void 
LouKeIoStartNextPacketByKey(
    PDEVICE_OBJECT DeviceObject, 
    BOOLEAN Cancelable, 
    ULONG Key
){
    LouPrint("LouKeIoStartNextPacketByKey()\n");
    while(1);
}

KERNEL_EXPORT 
void 
LouKeIoStartPacket(
    PDEVICE_OBJECT DeviceObject, 
    PIRP Irp, 
    PULONG Key, 
    PDRIVER_CANCEL CancelFunction
){
    LouPrint("LouKeIoStartPacket()\n");
    while(1);
}

KERNEL_EXPORT 
void 
LouKeIoStartTimer(
    PDEVICE_OBJECT DeviceObject
){
    LouPrint("LouKeIoStartTimer()\n");
    while(1);
}

KERNEL_EXPORT 
void 
LouKeIoStopTimer(
    PDEVICE_OBJECT DeviceObject
){
    LouPrint("LouKeIoStopTimer()\n");
    while(1);
}

KERNEL_EXPORT 
void 
LouKeIoWriteErrorLogEntry(
    PVOID ElEntry
){
    LouPrint("LouKeIoWriteErrorLogEntry()\n");
    while(1);
}