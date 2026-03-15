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
