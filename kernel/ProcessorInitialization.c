#include <LouAPI.h>

extern uint64_t GetCr4();
void save_fpu_state(uint8_t* buffer) ;
void restore_fpu_state(uint8_t* buffer);
void fxsave_handler(uint8_t* buffer);
void fxrstor_handler(uint8_t* buffer);
extern void StoreAdvancedRegisters(uint8_t* buffer);
extern void RestoreAdvancedRegisters(uint8_t* buffer);

typedef struct _PROCESSOR_CALLBACKS{
    void        (*SaveHandler)(uint8_t*);
    void        (*RestoreHandler)(uint8_t*);
    void        (*InitializeThreadDataHandler)(uint8_t*, uint8_t*);
    uint64_t    (*AllocateSaveContext)();
}PROCESSOR_CALLBACKS, * PPROCESSOR_CALLBACKS;

typedef struct _PROCESSOR_FEATURES{
    bool    Sse1Supported;
    bool    Sse2Supported;
    bool    Sse3Supported;
    bool    Ssse3Supported;
    bool    Sse41Supported;
    bool    Sse42Supported;
    bool    Avx1Supported;
    bool    Avx2Supported;
    bool    Avx512Supported;
}PROCESSOR_FEATURES, * PPROCESSOR_FEATURES;

void LouKeRegisterProcessorCallback(PPROCESSOR_CALLBACKS Callback);
void SendProcessorFeaturesToMemCpy(PPROCESSOR_FEATURES ProcessorFeatures);
void LouKeInitProcessorAcceleratedFeaturesList(PPROCESSOR_FEATURES Features);
uint64_t LouKeAllocateFxSaveMemory();

extern void initialize_thread_fpu_state(uint8_t* New, uint8_t* Current);
extern void initialize_thread_fxsave_state(uint8_t* New, uint8_t* Current);
extern void InitializeXSaveThread(uint8_t* New, uint8_t* Current);

static const PROCESSOR_CALLBACKS ProcessorHandlerTable[] = {
    {
        .SaveHandler = save_fpu_state,
        .RestoreHandler = restore_fpu_state,
        .InitializeThreadDataHandler = initialize_thread_fpu_state,
    },
    {
        .SaveHandler = fxsave_handler,
        .RestoreHandler = fxrstor_handler,
        .InitializeThreadDataHandler = initialize_thread_fxsave_state,
        .AllocateSaveContext = LouKeAllocateFxSaveMemory,
    },
    {
        .SaveHandler = StoreAdvancedRegisters,
        .RestoreHandler = RestoreAdvancedRegisters,
        .InitializeThreadDataHandler = InitializeXSaveThread,
    },
    { 0 },
};

static PROCESSOR_FEATURES ProcessorFeatures;

extern void enable_fxsave();
extern void initialize_fpu();
extern void InitializeXSave();

void HandleProccessorInitialization(){
    //the processor should be up by now
    //for apic however now we need to 
    //register our processor core
    //features
    unsigned int  rax, rbx, rcx, rdx;
    cpuid(1, &rax, &rbx, &rcx, &rdx);

    if(rcx & (1 << 26)){
        //InitializeXSave();
        //LouKeRegisterProcessorCallback((PPROCESSOR_CALLBACKS)&ProcessorHandlerTable[2]);        
    }
    if(rdx & (1 << 25)){
        enable_fxsave();
        LouKeRegisterProcessorCallback((PPROCESSOR_CALLBACKS)&ProcessorHandlerTable[1]);       

    }else{
        initialize_fpu();
        LouKeRegisterProcessorCallback((PPROCESSOR_CALLBACKS)&ProcessorHandlerTable[0]);
    }

    ProcessorFeatures.Sse1Supported = (rdx & (1 << 25)) ? true : false; 
    ProcessorFeatures.Sse2Supported = (rdx & (1 << 26)) ? true : false; 
    ProcessorFeatures.Sse3Supported = (rcx & (1 <<  0)) ? true : false; 
    ProcessorFeatures.Ssse3Supported = (rcx & (1 << 9)) ? true : false; 
    ProcessorFeatures.Sse41Supported = (rcx & (1 << 20)) ? true : false; 
    ProcessorFeatures.Avx1Supported = (rcx & (1 << 28)) ? true : false; 

    if(ProcessorFeatures.Avx1Supported){
        cpuid(7, &rax, &rbx, &rcx, &rdx);
        ProcessorFeatures.Avx2Supported = (rbx & (1 << 5)) ? true : false; 
        ProcessorFeatures.Avx512Supported = (rbx & (1 << 16)) ? true : false; 
    }else{
        ProcessorFeatures.Avx2Supported = false; 
        ProcessorFeatures.Avx512Supported = false; 
    }

    SendProcessorFeaturesToMemCpy(&ProcessorFeatures);
    
    PPROCESSOR_FEATURES UserCopy = LouKeMallocType(PROCESSOR_FEATURES, USER_GENERIC_MEMORY);
    memcpy(UserCopy, &ProcessorFeatures, sizeof(PROCESSOR_FEATURES));
    LouKeInitProcessorAcceleratedFeaturesList(UserCopy);
}

void HandleApProccessorInitialization(){
    unsigned int  rax, rbx, rcx, rdx;
    cpuid(1, &rax, &rbx, &rcx, &rdx);

    if(rcx & (1 << 26)){
        InitializeXSave();
    }
    if(rdx & (1 << 25)){
        enable_fxsave();
    }else{
        initialize_fpu();
    }
}