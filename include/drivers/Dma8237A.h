// Header: HeaderName.h

#ifndef DMA8237_H
#define DMA8237_H

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



#ifdef _KERNEL_MODULE_
// --- Module-specific data (MODULE_NAME.SYS) ---
KERNEL_EXPORT
PVOID LouKeMallocDma16Ex(
    SIZE AllocationSize, 
    UINT64 Alignment
);
KERNEL_EXPORT
PVOID LouKeMallocDma16(
    SIZE AllocationSize
);
KERNEL_EXPORT
void LouKeFreeDma16(
    PVOID Address
);
#else
// --- LOUOSKRNL.EXE-specific data ---
PVOID LouKeMallocDma16Ex(
    SIZE AllocationSize, 
    UINT64 Alignment
);
PVOID LouKeMallocDma16(
    SIZE AllocationSize
);
void LouKeFreeDma16(
    PVOID Address
);
#endif

#endif // end user vs kernel

#ifdef __cplusplus
}
#endif

#endif // HEADERNAME_H
