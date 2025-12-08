#include <LouDDK.h>
#include "ProcessPrivate.h"


KERNEL_IMPORT uint64_t GetCr3();



UINT64 LouKeVmmCreatePmlTable(){
    LouPrint("LouKeVmmCreatePmlTable()\n");
    UINT64* Pml4 = (UINT64*)LouGeneralAllocateMemory(KILOBYTE_PAGE);
    UINT64* Cloner = (UINT64*)(GetCr3() + GetKSpaceBase());

    UINT64 L4Scan = 0;
    
    for(;L4Scan < 512; L4Scan++){
        Pml4[L4Scan] = Cloner[L4Scan];
    }

    //LouKeVmmCloneSectionToPml(Pml4);

    LouKeMemoryBarrier();

    return (UINT64)Pml4;
}