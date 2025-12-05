#include <LouDDK.h>
#include "ProcessPrivate.h"

#define L4SCAN_START ((0xFFFF800000000000ULL >> 39) & 0x1FF)

extern "C" uint64_t GetCr3();


UINT64 LouKeVmmCreatePmlTable(){
    LouPrint("LouKeVmmCreatePmlTable()\n");
    UINT64* Pml4 = (UINT64*)LouGeneralAllocateMemory(KILOBYTE_PAGE);
    UINT64* Cloner = (UINT64*)GetCr3();

    UINT64 L4Scan = L4SCAN_START;
    
    for(;L4Scan < 512; L4Scan++){
        Pml4[L4Scan] = Cloner[L4Scan];
    }

    LouKeVmmCloneSectionToPml(Pml4);

    LouKeMemoryBarrier();

    return (UINT64)Pml4;
}