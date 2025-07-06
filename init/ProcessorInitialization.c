#include <LouAPI.h>

extern uint64_t GetCr4();
void save_fpu_state(uint8_t* buffer) ;
void restore_fpu_state(const uint8_t* buffer);
void fxsave_handler(uint8_t* buffer);
void fxrstor_handler(const uint8_t* buffer);
extern void StoreAdvancedRegisters(uint8_t* buffer);
extern void RestoreAdvancedRegisters(const uint8_t* buffer);

typedef struct _PROCESSOR_CALLBACKS{
    void (*SaveHandler)(uint8_t*);
    void (*RestoreHandler)(const uint8_t*);
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


static const PROCESSOR_CALLBACKS ProcessorHandlerTable[] = {
    {
        .SaveHandler = save_fpu_state,
        .RestoreHandler = restore_fpu_state,
    },
    {
        .SaveHandler = fxsave_handler,
        .RestoreHandler = fxrstor_handler,
    },
    {
        .SaveHandler = StoreAdvancedRegisters,
        .RestoreHandler = RestoreAdvancedRegisters,
    },
    { 0 },
};

static PROCESSOR_FEATURES ProcessorFeatures;

void enable_fxsave() {
    uint64_t cr4;

    // Read CR4
    __asm__ volatile (
        "mov %%cr4, %0"
        : "=r" (cr4)
    );

    // Set OSFXSR (bit 9)
    cr4 |= (1 << 9);

    // Write back to CR4
    __asm__ volatile (
        "mov %0, %%cr4"
        :
        : "r" (cr4)
    );
}


void initialize_fpu() {
    __asm__ volatile ("finit");  // Initialize FPU to known state
}

void InitializeXSave();

void HandleProccessorInitialization(){
    //the processor should be up by now
    //for apic however now we need to 
    //register our processor core
    //features
    unsigned int  rax, rbx, rcx, rdx;
    cpuid(1, &rax, &rbx, &rcx, &rdx);

    if(rcx & (1 << 26)){
        InitializeXSave();
        LouKeRegisterProcessorCallback((PPROCESSOR_CALLBACKS)&ProcessorHandlerTable[2]);        
    }
    if(rdx & (1 << 24)){
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
    //memcpy(UserCopy, &ProcessorFeatures, sizeof(PROCESSOR_FEATURES));
    LouKeInitProcessorAcceleratedFeaturesList(UserCopy);
}