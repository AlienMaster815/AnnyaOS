#ifndef _IOINTEX_H
#define _IOINTEX_H

#include <NtAPI.h>

NTSTATUS WdmlibIoGetAffinityInterrupt(
	  PKINTERRUPT     InterruptObject,
	 PGROUP_AFFINITY GroupAffinity
);


NTSTATUS WdmlibIoDisconnectInterruptEx(
	  PIO_DISCONNECT_INTERRUPT_PARAMETERS Parameters
);

NTSTATUS WdmlibIoConnectInterruptEx(
	  PIO_CONNECT_INTERRUPT_PARAMETERS Parameters
);

#endif