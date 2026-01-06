#include <LouAPI.h>


static FXSAVE_64_CONTEXT ForkState = {0};


void LouKeDeAllocateFxSaveMemory(uint64_t Context){
    LouGeneralFreeMemory((PVOID)Context);
} 

uint64_t LouKeAllocateFxSaveMemory(){
    uint8_t* Tmp = LouGeneralAllocateMemoryEx(512, 16);
    memcpy(Tmp, &ForkState, sizeof(FXSAVE_64_CONTEXT));
    return (uint64_t)Tmp;
}

uint64_t GetFxSaveForkPointer(){
    return (uint64_t)LouGeneralAllocateMemoryEx(512, 16);
}

void SetFxSaveForkPointerData(uint64_t NewData){
    memcpy(&ForkState, (void*)NewData, sizeof(FXSAVE_64_CONTEXT));
    LouGeneralFreeMemory((void*)NewData);
}