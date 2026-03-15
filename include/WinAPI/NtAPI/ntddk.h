

#ifndef _NTDDK_H
#define _NTDDK_H

#include <NtAPI.h>
#include "irp.h"
#include "ntoapi.h"
#include "wdm.h"



BOOLEAN SeSinglePrivilegeCheck(
   LUID            PrivilegeValue,
   KPROCESSOR_MODE PreviousMode
);

void SiloContextCleanupCallback(
   PVOID SiloContext
);

void SiloMonitorTerminateCallback(
   PESILO Silo
);

#endif