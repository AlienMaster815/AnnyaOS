#ifndef _COFF_PRIVATE_H
#define _COFF_PRIVATE_H

#include <LouAPI.h>

LOUSTATUS LouKeLoadCoffImageA32(
    PCFI_OBJECT CoffObject
);

LOUSTATUS LouKeLoadCoffImageA64(
    PCFI_OBJECT CoffObject
);

LOUSTATUS 
LouKeRequestVirtualAddressAllocation(
    UINTPTR     Address,
    SIZE        size
);

void DisableCR0WriteProtection();
void EnableCR0WriteProtection();

#define ImageAlignment (64 * KILOBYTE)

void LouKeInitializeLibraryLookup(
    string    ModuleName,
    uint32_t  NumberOfFunctions,
    string*   FunctionNames,
    uint64_t* FunctionAddresses,
    bool IsNativeLongmode
);

typedef struct _LOADED_IMAGE_TRACKER{
    ListHeader  Peers;
    string      LoadedObjectName;
    CFI_OBJECT  LoadedObject;
}LOADED_IMAGE_TRACKER, * PLOADED_IMAGE_TRACKER;

#endif