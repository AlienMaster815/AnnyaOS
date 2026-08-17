#include "ScsiCore.h"

static LouKeXaDefine(ScsiHostDriverArray);
static ListHeader ScsiHostDriverList = {0};
static mutex_t ScsiHostDriverListLock = {0};

static PSCSI_INTERNAL_HOST_DEVICE_DRIVER_OBJECT ScsiCoreGetInternalHostObjectFromExternalHostObject(PSCSI_HOST_DEVICE_DRIVER_OBJECT ExternalHostDriver){
    PSCSI_INTERNAL_HOST_DEVICE_DRIVER_OBJECT InternalDriver = 0x00;
    PSCSI_INTERNAL_HOST_DEVICE_DRIVER_OBJECT TmpInternal;
    MutexLock(&ScsiHostDriverListLock);
    ForEachListEntry(TmpInternal, &ScsiHostDriverList, DriverList){
        if(TmpInternal->DriverObject == ExternalHostDriver){
            InternalDriver = TmpInternal;
            break;
        }
    }
    MutexUnlock(&ScsiHostDriverListLock);
    return InternalDriver;
}

DRIVER_EXPORT LOUSTATUS ScsiCoreRegisterScsiHostDeviceDriver(
    PSCSI_HOST_DEVICE_DRIVER_OBJECT NewScsiDriverObject,
    SIZE                            DriverPrivateDataSize,
    SIZE                            DriverPrivateDataAlignment
){
    LOUSTATUS Status;
    ScsiCoreDbgPrint("SCSICORE.SYS:Adding New Host Driver:%s:Object:%h\n", NewScsiDriverObject->DriverName, (UINT64)NewScsiDriverObject);
    PSCSI_INTERNAL_HOST_DEVICE_DRIVER_OBJECT NewScsiCoreHostDriver = LouKeMallocType(SCSI_INTERNAL_HOST_DEVICE_DRIVER_OBJECT, KERNEL_GENERIC_MEMORY);
    if(!NewScsiCoreHostDriver){
        ScsiCoreDbgPrint("SCSICORE.SYS:Unable To Allocate Data For New Host Driver\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    //NewScsiCoreHostDriver->DriverXaID = 0; already 0 adding this for behavior reference
    MutexLock(&ScsiHostDriverListLock);
    Status = LouKeXarrayAllocateUint64(
        &ScsiHostDriverArray,
        &NewScsiCoreHostDriver->DriverXaID,
        NewScsiCoreHostDriver,
        UINT32_MAX,
        KERNEL_GENERIC_MEMORY
    );
    if(Status != STATUS_SUCCESS){
        ScsiCoreDbgPrint("SCSICORE.SYS:Unable To Allocate ID For New Host Driver\n");
        MutexUnlock(&ScsiHostDriverListLock);
        LouKeFree(NewScsiCoreHostDriver);
        return Status;
    }

    NewScsiCoreHostDriver->PrivateDataSize = DriverPrivateDataSize;
    NewScsiCoreHostDriver->PrivateDataAlignment = DriverPrivateDataAlignment;
    NewScsiCoreHostDriver->DriverObject = NewScsiDriverObject;
    LouKeListAddTail(&NewScsiCoreHostDriver->DriverList, &ScsiHostDriverList);
    MutexUnlock(&ScsiHostDriverListLock);
    ScsiCoreDbgPrint("SCSICORE.SYS:Successfully Added New Host Driver\n");
    return STATUS_SUCCESS;
}

DRIVER_EXPORT LOUSTATUS ScsiCoreCreateScsiHostDeviceObject(
    PSCSI_HOST_DEVICE_DRIVER_OBJECT ScsiDriverObject,
    PDEVICE_OBJECT                  LdmDevice,
    PSCSI_HOST_DEVICE_OBJECT*       NewDeviceObjectOut
){
    LOUSTATUS Status;
    ScsiCoreDbgPrint("SCSICORE.SYS:Creating New Device Object For Driver Object:%h\n", ScsiDriverObject);
    if((!ScsiDriverObject) || (!NewDeviceObjectOut)){
        ScsiCoreDbgPrint("SCSICORE.SYS:Unable To Create New Device Object:Invalid Parameter\n");
        return STATUS_INVALID_PARAMETER;
    }
    
    PSCSI_INTERNAL_HOST_DEVICE_DRIVER_OBJECT ScsiHostDriver = ScsiCoreGetInternalHostObjectFromExternalHostObject(ScsiDriverObject);
    if(!ScsiHostDriver){
        ScsiCoreDbgPrint("SCSICORE.SYS:Unable To Create New Device Object:Invalid Parameter\n");
        return STATUS_INVALID_PARAMETER;
    }
    PSCSI_INTERNAL_HOST_DEVICE_OBJECT NewDeviceObject = LouKeMallocType(SCSI_INTERNAL_HOST_DEVICE_OBJECT, KERNEL_GENERIC_MEMORY);
    
    if(!NewDeviceObject){
        ScsiCoreDbgPrint("SCSICORE.SYS:Unable To Allocate New Device Object ID\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    if(ScsiHostDriver->PrivateDataSize){
        ScsiHostDriver->PrivateDataAlignment = ScsiHostDriver->PrivateDataAlignment ? ScsiHostDriver->PrivateDataAlignment : 1;
        NewDeviceObject->ScsiHostDevice.ShddPrivateData = LouKeMallocEx(ScsiHostDriver->PrivateDataSize, ScsiHostDriver->PrivateDataAlignment, KERNEL_GENERIC_MEMORY);
        if(!NewDeviceObject->ScsiHostDevice.ShddPrivateData){
            LouKeFree(NewDeviceObject);
            return STATUS_INSUFFICIENT_RESOURCES;
        }
    }

    MutexLock(&ScsiHostDriver->HostDeviceListLock);
    Status = LouKeXarrayAllocateUint64(
        &ScsiHostDriver->HostDeviceArray, 
        &NewDeviceObject->HostXaID, 
        NewDeviceObject, 
        UINT32_MAX, 
        KERNEL_GENERIC_MEMORY
    );
    if(Status != STATUS_SUCCESS){
        ScsiCoreDbgPrint("SCSICORE.SYS:Unable To Allocate New Device Object ID\n");
        MutexUnlock(&ScsiHostDriver->HostDeviceListLock);
        LouKeFree(NewDeviceObject->ScsiHostDevice.ShddPrivateData);
        LouKeFree(NewDeviceObject);
        return Status;
    }
    
    NewDeviceObject->DriverObject = ScsiDriverObject;
    NewDeviceObject->LdmDevice = LdmDevice;
    LouKeListAddTail(&NewDeviceObject->HostDeviceList, &ScsiHostDriver->HostDeviceList);
    MutexUnlock(&ScsiHostDriver->HostDeviceListLock);
    *NewDeviceObjectOut = &NewDeviceObject->ScsiHostDevice; 
    ScsiCoreDbgPrint("SCSICORE.SYS:Successfully Created New Device Object\n");
    _OUT_ERROR:
    return Status;
}