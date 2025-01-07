#include <NtAPI.h>
#include <LouDDK.h>

VOID RtlZeroMemory(void* Location ,size_t Size){
	memset(Location, 0 , Size);
}

NTSTATUS IoAllocateAdapterChannel(
	PADAPTER_OBJECT AdapterObject,
	PDEVICE_OBJECT  DeviceObject,
	ULONG           NumberOfMapRegisters,
	PDRIVER_CONTROL ExecutionRoutine,
	PVOID           Context
) {

	return STATUS_SUCCESS;
}

BOOLEAN WheaSignalHandlerOverrideCallback(
	  UINT_PTR Context
){

	return true;
}


void BootDriverCallbackFunction(
	PVOID CallbackContext,
	BDCB_CALLBACK_TYPE Classification,
	PBDCB_IMAGE_INFORMATION ImageInformation
) {


}

void CUSTOM_SYSTEM_EVENT_TRIGGER_INIT(
	PCUSTOM_SYSTEM_EVENT_TRIGGER_CONFIG Config,
	PCWSTR                              TriggerId
) {


}

void DriverReinitialize(
	          _DRIVER_OBJECT* DriverObject,
	 PVOID Context,
	           ULONG Count
) {


}

void ExFreePool(
   PVOID P
){

}

void ExpandStackCallout(
	 PVOID Parameter
) {


}

void ExRaiseAccessViolation() {
	asm volatile ("INT $0xD");
}

void ExRaiseDatatypeMisalignment() {
	LouPrint("DataTypeMissAlligned\n");
	while(1);
}

KERNEL_IMPORT uint64_t GetCurrentTimeInMilliseconds();

void KeQuerySystemTime(LARGE_INTEGER* TimeCurrent){ //T = OUT
    // Validate the output pointer
    if (TimeCurrent == 0x00) {
		return;
    }

    // Get the current time in milliseconds
    uint64_t current_time_ms = GetCurrentTimeInMilliseconds();
    
    // Convert milliseconds to 100-nanosecond intervals
    uint64_t time_100ns = current_time_ms * 10000;
    
    // Fill the LARGE_INTEGER with the calculated time
    TimeCurrent->QuadPart = time_100ns;

}

NTSTATUS ExUuidCreate(
	 UUID* Uuid
) {


	

	return STATUS_SUCCESS;
}

NTSTATUS HalAllocateHardwareCounters(
	PGROUP_AFFINITY                 GroupAffinty,
	  ULONG                           GroupCount,
	  PPHYSICAL_COUNTER_RESOURCE_LIST ResourceList,
	 PHANDLE                         CounterSetHandle
) {

	return STATUS_SUCCESS;
}

void HalExamineMBR(
	  PDEVICE_OBJECT DeviceObject,
	  ULONG          SectorSize,
	  ULONG          MBRTypeIdentifier,
	 PVOID* Buffer
) {


}

NTSTATUS HalFreeHardwareCounters(
	 HANDLE CounterSetHandle
) {

	return STATUS_SUCCESS;
}

//WARNING BACKPATIBLE STABILITY THREAT
ULONG HalGetBusDataByOffset(
	 BUS_DATA_TYPE BusDataType,
	 ULONG         BusNumber,
	 ULONG         SlotNumber,
	 PVOID         Buffer,
	 ULONG         Offset,
	 ULONG         Length
) {


	return 0;
}

ULONG HalSetBusDataByOffset(
	 BUS_DATA_TYPE BusDataType,
	 ULONG         BusNumber,
	 ULONG         SlotNumber,
	 PVOID         Buffer,
	 ULONG         Offset,
	 ULONG         Length
) {

	return 0;
}

void IoAllocateController(
	           PCONTROLLER_OBJECT ControllerObject,
	           PDEVICE_OBJECT     DeviceObject,
	           PDRIVER_CONTROL    ExecutionRoutine,
	 PVOID              Context
) {


}
/*
void IoAssignArcName(
	  ArcName,
	  DeviceName
) {


}
*/

void IoClearActivityIdThread(
	 LPCGUID OriginalId
) {


}

PCONTROLLER_OBJECT IoCreateController(
	 ULONG Size
) {

	return 0;
}

//void IoDeassignArcName(
//	  ArcName
//){

//}

//void IoDeassignArcName(
//	  ArcName
//){

//}

NTSTATUS IoDecrementKeepAliveCount(
	  PFILE_OBJECT FileObject,
	  PEPROCESS    Process
) {

	return STATUS_SUCCESS;
}

void IoDeleteController(
   PCONTROLLER_OBJECT ControllerObject
){

}

bool NT_SUCCESS(NTSTATUS Status){
	switch(Status){
		case 0:
			return true;
		default:
			return false;
	}
}

void IoFreeController(
   PCONTROLLER_OBJECT ControllerObject
){

}

NTSTATUS IoGetActivityIdIrp(
    PIRP   Irp,
   LPGUID Guid
){


	return STATUS_SUCCESS;
}

LPCGUID IoGetActivityIdThread(){

	return 0x00;
}

PCONFIGURATION_INFORMATION IoGetConfigurationInformation(){
	LouPrint("IoGetConfigurationInformation()\n");

	LouPrint("IoGetConfigurationInformation() STATUS_SUCCESS\n");
	while(1);
	return 0x00;
}

PGENERIC_MAPPING IoGetFileObjectGenericMapping(){


	return 0x00;
}

PEPROCESS IoGetInitiatorProcess(
   PFILE_OBJECT FileObject
){



	return 0x00;
}

IO_PAGING_PRIORITY IoGetPagingIoPriority(
   PIRP Irp
){

	return IoPagingPriorityInvalid;

}

NTSTATUS IoIncrementKeepAliveCount(
	  PFILE_OBJECT FileObject,
	  PEPROCESS    Process
){


	return STATUS_SUCCESS;
}

LOGICAL IoIsValidIrpStatus(
   NTSTATUS Status
){


	return 0x00;
}