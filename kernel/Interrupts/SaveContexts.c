#include <LouAPI.h>

typedef struct _PROCESSOR_CALLBACKS{
    void        (*SaveHandler)(uint8_t*);
    void        (*RestoreHandler)(uint8_t*);
    void        (*InitializeThreadDataHandler)(uint8_t*, uint8_t*);
    uint64_t    (*AllocateSaveContext)();
    void        (*DeAllocateSaveContext)(uint64_t);
}PROCESSOR_CALLBACKS, * PPROCESSOR_CALLBACKS;

static PPROCESSOR_CALLBACKS ProcessorCallbacks;

void LouKeRegisterProcessorCallback(PPROCESSOR_CALLBACKS Callback){
    ProcessorCallbacks = Callback;
}

uint64_t GetAdvancedRegisterInterruptsStorage();

//Fuck It Well do it live
void SaveEverythingWithInterruptBuffer(uint64_t* ContextHandle){
    if(!ContextHandle)return;   
    *ContextHandle = GetAdvancedRegisterInterruptsStorage();
    if(!(*ContextHandle))return;
    ProcessorCallbacks->SaveHandler((uint8_t*)(*ContextHandle));
}

void RestoreEverythingWithInterruptBuffer(uint64_t* ContextHandle){
    if(!ContextHandle)return;
    if(!(*ContextHandle))return;
    ProcessorCallbacks->RestoreHandler((uint8_t*)(*ContextHandle));
}

void SaveEverything(uint64_t ContextHandle){
    if(!ContextHandle)return;
    ProcessorCallbacks->SaveHandler((uint8_t*)ContextHandle);
}

void RestoreEverything(uint64_t ContextHandle){
    if(!ContextHandle)return;
    ProcessorCallbacks->RestoreHandler((uint8_t*)ContextHandle);
}

uint64_t AllocateSaveContext(){
    if(!ProcessorCallbacks->AllocateSaveContext){
        return 0x00;
    }
    return ProcessorCallbacks->AllocateSaveContext();
}

void DeAllocateSaveContext(uint64_t Context){
    if(!ProcessorCallbacks->DeAllocateSaveContext){
        return;
    }
    ProcessorCallbacks->DeAllocateSaveContext(Context);
}
