// Header: HeaderName.h

#ifndef _ELF_H
#define _ELF_H

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

#ifdef _ELF_LOU
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
#else
// --- LOUOSKRNL.EXE-specific data ---
#endif

#endif // end user vs kernel

#ifdef __cplusplus
}
#endif

#endif // HEADERNAME_H
