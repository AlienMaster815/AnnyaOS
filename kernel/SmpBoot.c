#include <LouAPI.h>

void* LouKeGetBootDevice(size_t Index);
size_t LouKeGetBootDeviceSize(size_t Index);
INTEGER GetCpuTrackMemberFromID(UINT32 CpuID);
void LouKeSendProcessorWakeupSignal(INTEGER TrackMember);
INTEGER 
GetCurrentCpuTrackMember();

uint16_t GetNPROC();

PML* GetPageBase();

static mutex_t* TrampolineLock;
static UINT64* TrampolineStack;
static UINT64* FunctionAddress;
static UINT64* GlobalParkFunction;
static UINT64* Pml4Address;
static UINT64* Pml4Address32;
static INTEGER Bsp = 0;
UNUSED static bool SmpBootInitialized = false;

bool LouKeIsCpuBroken(INTEGER Cpu);

static mutex_t WakeLock = {0};

LOUSTATUS LouKeSmpWakeAssistant(
    INTEGER Assistant, 
    UINT64 Stack, 
    UINT64 CpuInitFunction
){
    if(!SmpBootInitialized){
        return STATUS_NO_SUCH_DEVICE;
    }
    INTEGER CurrentCpu = GetCurrentCpuTrackMember();

    if(Assistant == CurrentCpu){
        return STATUS_UNSUCCESSFUL;
    }

    MutexLock(&WakeLock);

    MutexLock(TrampolineLock);

    *TrampolineStack    = Stack; 
    *GlobalParkFunction = CpuInitFunction; 
    *Pml4Address        = (UINT64)GetPageBase();
    
    LouKeMemoryBarrier();

    LouKeSendProcessorWakeupSignal(Assistant);

    MutexUnlock(&WakeLock);

    return STATUS_SUCCESS;
}

void LouKeSmpWakeFunction(){
    MutexUnlock(TrampolineLock);
    void (*InitializationFunction)() = (void (*)())*GlobalParkFunction;
    InitializationFunction();
}


void LouKeLoadLousineBootTrampoline(){
    
    
    PVOID SmpLoadOrderHandle = LouKeOpenRegistryHandle(L"KERNEL_DEFAULT_CONFIG\\Subsystems\\Smp\\LoadOrder" , 0x00); 
    WORD SmpBootLoadOrder = 0x00; 

    if(LouKeGetRegistryKeySize(SmpLoadOrderHandle) != sizeof(WORD)){
        LouPrint("ERROR:Registry Key Corrupt\n");
        return;
    }    

    if(LouKeReadRegistryWordValue(SmpLoadOrderHandle, &SmpBootLoadOrder) != STATUS_SUCCESS){
        LouPrint("ERROR: Unable To Read Registry Value\n");
        return;
    }

    UNUSED FILE* TrampolineFile = LouKeGetBootDevice(SmpBootLoadOrder);//fopen(FilePath, KERNEL_GENERIC_MEMORY);
    size_t TrampolineSize = ROUND_UP64(LouKeGetBootDeviceSize(SmpBootLoadOrder), KILOBYTE_PAGE) + 2 * KILOBYTE_PAGE;
    LouKeMapContinuousMemoryBlock(0x7000, 0x7000, TrampolineSize, KERNEL_DMA_MEMORY);
    LouKeCreateDeviceSection((PVOID)0x7000, (PVOID)0x7000, (SIZE)TrampolineSize, PAGE_READWRITE | SEC_NOCACHE);
    memset((PVOID)0x7000, 0, TrampolineSize);
    memcpy((PVOID)0x8000, (PVOID)TrampolineFile, LouKeGetBootDeviceSize(SmpBootLoadOrder));

    
    INTEGER CurrentCpu = GetCurrentCpuTrackMember();
    Bsp = CurrentCpu;

    TrampolineStack = (UINT64*)0x7000;
    FunctionAddress = (UINT64*)0x7008;
    Pml4Address = (UINT64*)0x7010;
    GlobalParkFunction = (UINT64*)0x7018;
    Pml4Address32 = (UINT64*)0x7020;
    TrampolineLock = (mutex_t*)(UINT64)0x7028;

    *Pml4Address     = (UINT64)GetPageBase();
    *FunctionAddress = (UINT64)LouKeSmpWakeFunction; 
    *Pml4Address32   = (UINT64)(LouGeneralAllocateMemory32(4096) - GetKSpaceBase());

    LouKeMapContinuousMemoryBlockEx32(0x7000, 0x7000, TrampolineSize, KERNEL_DMA_MEMORY, (UINT64*)*Pml4Address32);

    //*TrampolineStack = (UINT64)(LouKeMallocPhysicalEx(16 * KILOBYTE, 16, KERNEL_GENERIC_MEMORY) + ((16 * KILOBYTE) - 16)); 

    SmpBootInitialized = true;

    LouKeMemoryBarrier();

    //for(INTEGER i = 0 ; i < GetNPROC(); i++){
    //    if(i == CurrentCpu){
    //        continue;
    //    }
    //    LouKeSmpWakeAssistant(
    //        i,
    //        (UINT64)(LouKeMallocPhysicalEx(16 * KILOBYTE, 16, KERNEL_GENERIC_MEMORY) + ((16 * KILOBYTE) - 16)),
    //        (UINT64)LouSmpTestWake
    //    );
    //}

}

