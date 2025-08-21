#include <LouAPI.h>



void LouKeLoadLousineBootTrampoline(string FilePath){
    LouPrint("FilePath:%s\n", FilePath);
    UNUSED FILE* TrampolineFile = fopen(FilePath, KERNEL_GENERIC_MEMORY);
    LouKeMapContinuousMemoryBlock(0x7000, 0x7000, 0x2000, KERNEL_DMA_MEMORY);
    memset((PVOID)0x7000, 0, 0x2000);
    memcpy((PVOID)0x8000, (PVOID)TrampolineFile, fsize(TrampolineFile));




}