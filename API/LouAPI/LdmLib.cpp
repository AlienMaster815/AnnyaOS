#include <LouDDK.h>

KERNEL_EXPORT
LOUSTATUS 
LdmlibIoGetAffinityInterrupt(
	PKINTERRUPT     InterruptObject,
	PGROUP_AFFINITY GroupAffinity
){  
    LouPrint("LdmlibIoGetAffinityInterrupt()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
LOUSTATUS 
LdmlibIoDisconnectInterruptEx(
	struct _IO_DISCONNECT_INTERRUPT_PARAMETERS* Parameters
){
    LouPrint("LdmlibIoDisconnectInterruptEx()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
LOUSTATUS 
LdmlibIoConnectInterruptEx(
	struct _IO_CONNECT_INTERRUPT_PARAMETERS* Parameters
){
    LouPrint("LdmlibIoConnectInterruptEx()\n");
    while(1);   
    return STATUS_SUCCESS;
}