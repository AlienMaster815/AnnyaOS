// Header: HeaderName.h

#ifndef HEADERNAME_H
#define HEADERNAME_H

#ifdef __cplusplus
extern "C" {
#endif

// ------------------- UNIVERSAL DATA ------------------- //
// Define shared types or macros here
// Example:
// typedef struct HeaderCommon { int CommonID; } HeaderCommon;

#if defined(_USER_MODE_CODE_)

// ------------------- USER MODE ------------------------ //
#include <Annya.h>    // User mode system includes

// --- Global user-mode data (visible across all DLLs) ---

#ifdef _MODULE_NAME
// --- Private user-mode data (specific to MODULE_NAME.DLL) ---
#else
// --- Shared user-mode data ---
#endif

#else // Kernel mode section

// ------------------- KERNEL MODE ---------------------- //
#ifdef __cplusplus
#include <LouDDK.h>
#else
#include <LouAPI.h>
#endif

typedef struct _LOU_BUS_OBJECT{
    ListHeader          Peers;
    string              BusName;
    PVOID               BusPrivateData;
}LOU_BUS_OBJECT, * PLOU_BUS_OBJECT;

typedef struct _LOU_BUS{
    string              BusName;
    PLOU_BUS_OBJECT     BusObjects;
    LOUSTATUS           (*SearchMachine)(struct _LOU_BUS* BusData);
    LOUSTATUS           (*InitializeBus)(struct _LOU_BUS* BusData, PLOU_BUS_OBJECT BusObject);
    LOUSTATUS           (*DeInitializeBus)(struct _LOU_BUS* BusData, PLOU_BUS_OBJECT BusObject);
}LOU_BUS, * PLOU_BUS;

#ifdef _KERNEL_MODULE_
// --- Module-specific data (MODULE_NAME.SYS) ---
KERNEL_EXPORT
LOUSTATUS 
LouKeCreateBusClass(
    PLOU_BUS    Bus
);
#else
// --- LOUOSKRNL.EXE-specific data ---
LOUSTATUS 
LouKeCreateBusClass(
    PLOU_BUS    Bus
);
#endif

#endif // end user vs kernel

#ifdef __cplusplus
}
#endif

#endif // HEADERNAME_H
