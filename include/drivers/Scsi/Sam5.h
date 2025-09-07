// Header: HeaderName.h

#ifndef _SAM5_H
#define _SAM5_H

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
// --- Private user-mode data (specific to LOUDLL.DLL) ---
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

//command descriptor block

typedef struct __attribute__((packed)) _SCSI_CDB8{
    UINT8   OperationCode;
    UINT8   MiscLbaHigh;
    UINT8   LbaMid;
    UINT8   LbaLow;
    UINT8   OptData;
    UINT8   Control;
}SCSI_CDB8, * PSCSI_CDB8;

#define CDB8_LBA_HIGH_MASK   0x1F
#define CDB8_MISC_INFO_MASK  0xE0
#define CDB8_LBA_HIGH(x)     (x & CDB8_LBA_HIGH_MASK)
#define CDB8_MISC_INFO_SHIFT (5)
#define CDB8_MISC_INFO(x)    ((x & CDB8_MISC_INFO_MASK) << CDB8_MISC_INFO_SHIFT)

typedef struct __attribute__((packed)) _SCSI_CDB10{
    UINT8   OperationCode;
    UINT8   MiscServiceAction;
    UINT8   LbaHigh; 
    UINT8   LbaMidHigh;
    UINT8   LbaMidLow;
    UINT8   LbaLow;
    UINT8   MiscInforEx;
    UINT8   OptDataHigh;
    UINT8   OptDataLow;
    UINT8   Control;
}SCSI_CDB10, * PSCSI_CDB10;

#define CDB10_SERVICE_ACTION_MASK       0x1F
#define CDB10_MISC_INFO_MASK            CDB8_MISC_INFO_MASK
#define CDB10_MISC_INFO_SHIFT           CDB8_MISC_INFO_SHIFT
#define CDB10_SERVICE_ACTION(x)         (x & CDB10_SERVICE_ACTION_MASK)
#define CDB10_MISC_INFO(x)              ((x & CDB10_MISC_INFO_MASK) << CDB10_MISC_INFO_SHIFT)

typedef struct __attribute__((packed)) _SCSI_CDB12{
    UINT8   OperationCode;
    UINT8   MiscServiceAction;
    UINT8   LbaHigh; 
    UINT8   LbaMidHigh;
    UINT8   LbaMidLow;
    UINT8   LbaLow;
    UINT8   OptDataHigh;
    UINT8   OptDataMidHigh;
    UINT8   OptDataMidLow;
    UINT8   OptDataLow;
    UINT8   MiscInforEx;
    UINT8   Control;
}SCSI_CDB12, * PSCSI_CDB12;

#define CDB12_SERVICE_ACTION_MASK       0x1F
#define CDB12_MISC_INFO_MASK            CDB8_MISC_INFO_MASK
#define CDB12_MISC_INFO_SHIFT           CDB8_MISC_INFO_SHIFT
#define CDB12_SERVICE_ACTION(x)         (x & CDB10_SERVICE_ACTION_MASK)
#define CDB12_MISC_INFO(x)              ((x & CDB10_MISC_INFO_MASK) << CDB10_MISC_INFO_SHIFT)

typedef struct __attribute__((packed)) _SCSI_CDB16{
    UINT8   OperationCode;
    UINT8   MiscInfo;
    UINT8   LbaHighHigh; 
    UINT8   LbaHighMid;  
    UINT8   LbaHighLow;  
    UINT8   LbaMidHigh;  
    UINT8   LbaMidLow;   
    UINT8   LbaLowHigh;  
    UINT8   LbaLowMid;   
    UINT8   LbaLowLow;
    UINT8   OptDataHigh;
    UINT8   OptDataMidHigh;
    UINT8   OptDataMidLow;
    UINT8   OptDataLow;
    UINT8   MiscInfoEx;
    UINT8   Control;
}SCSI_CDB16, * PSCSI_CDB16;



#ifdef _KERNEL_MODULE_
// --- Module-specific data (LOUOSKRNL.EXPORT) ---
#else
// --- LOUOSKRNL.EXE-specific data ---
#endif

#endif // end user vs kernel

#ifdef __cplusplus
}
#endif

#endif // _SAM5_H
