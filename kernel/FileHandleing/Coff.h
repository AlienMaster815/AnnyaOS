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

#endif