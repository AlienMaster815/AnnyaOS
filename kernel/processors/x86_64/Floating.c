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

static PVOID AvxPreDefinedData = 0x00;
static SIZE AvxAllocationSize = 0x00;

void LouKeDeAllocateXSaveMemory(uint64_t OldData){
    LouGeneralFreeMemory((PVOID)OldData);
}

uint64_t LouKeAllocateXSaveMemory(){
    PVOID NewData = LouGeneralAllocateMemoryEx(AvxAllocationSize, 64);
    memcpy(NewData, AvxPreDefinedData, AvxAllocationSize);
    return (uint64_t)NewData;
}

void SetAvxAllocationSize(SIZE Size){
    AvxAllocationSize = Size;
    AvxPreDefinedData = LouGeneralAllocateMemoryEx(Size, 64);
}

uint64_t GetXSaveForkPointer(){
    return (uint64_t)LouGeneralAllocateMemoryEx(AvxAllocationSize, 64);
}

void SetXSaveForkPointerData(uint64_t NewData){
    memcpy(AvxPreDefinedData, (PVOID)NewData, AvxAllocationSize);
    LouGeneralFreeMemory((PVOID)NewData);
}
