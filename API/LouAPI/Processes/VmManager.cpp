//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include <LouDDK.h>
#include "ProcessPrivate.h"


LOUAPI uint64_t GetCr3();

void LouKeSendPml4ToSections(UINT64* Pml4);

UINT64 LouKeVmmCreatePmlTable(){
    LouPrint("LouKeVmmCreatePmlTable()\n");
    UINT64* Pml4 = (UINT64*)LouGeneralAllocateMemory(KILOBYTE_PAGE);
    UINT64* Cloner = (UINT64*)(GetCr3() + GetKSpaceBase());

    
    
    for(UINT64 L4Scan = 256; L4Scan < 512; L4Scan++){
        Pml4[L4Scan] = Cloner[L4Scan];
    }

    LouKeVmmCloneSectionToPml(Pml4);
    
    LouKeSendPml4ToSections((UINT64*)((UINT64)Pml4 - GetKSpaceBase()));

    LouKeMemoryBarrier();
    return (UINT64)Pml4;
}