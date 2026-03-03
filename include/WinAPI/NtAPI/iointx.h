#ifndef _IOINTEX_H
#define _IOINTEX_H

#include <NtAPI.h>

LOUSTATUS WdmlibIoGetAffinityInterrupt(
	  PKINTERRUPT     InterruptObject,
	 PGROUP_AFFINITY GroupAffinity
);

LOUAPI
LOUSTATUS WdmlibIoDisconnectInterruptEx(
	  PIO_DISCONNECT_INTERRUPT_PARAMETERS Parameters
);

LOUAPI
LOUSTATUS WdmlibIoConnectInterruptEx(
	  PIO_CONNECT_INTERRUPT_PARAMETERS Parameters
);

#endif