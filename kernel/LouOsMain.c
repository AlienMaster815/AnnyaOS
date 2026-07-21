#define KERNEL_MAIN_FILE
#ifdef __x86_64__
#include <LouAPI.h>
#include <bootloader/grub/multiboot2.h>
#endif


uintptr_t RSP_Current;
uintptr_t RBP_Current;


/* Tyler Grenier 10/4/23 9:56 PM
-- Started the file with the main
-- functions to get us going along 
-- with allocation functions
*/

string KERNEL_VERSION = "0.6.06";

string KERNEL_ARCH = "64-BIT";


KERNEL_EXPORT UINT64 LouKeGetSpaceBase(){
    return KSpaceBase;
}

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

static PPROCESSOR_FEATURES ProcAcceleratedFeatures = 0;

LOUSTATUS InitThreadManager();
LOUSTATUS SetUpTimers();
void DoubleFault(UINT64 Rsp);
void Clock(UINT64 SavedState);
void INTERRUPT(UINT8 interrupt_number);
void CookieCheckFail(UINT64 Rsp);
void ParseMBootTags(struct multiboot_tag* MBOOT);
uint64_t LouKeGetRamSize();
void InitializeEfiCore();
LOUSTATUS InitializeDirecAccess();
void InitializeInterruptRouter();
void LouKeInitializeKernelRuntimeEnviornment(KHANDLE KernelHandle);
void LouKeInitializeEarlyKernelRuntimeEnviornment(KHANDLE KernelHandle);
void ListUsedAddresses();
uint64_t getTrampolineAddress();
uint8_t GetTotalHardwareInterrupts();
uint64_t GetGdtBase();
void FlushTss();
void Spurious(uint64_t FaultingStackP);
void LouKeInitializeLouACPISubsystem();
LOUSTATUS HandleProccessorInitialization();
void LouKeProbeSbIsa();
LOUSTATUS SetupGDT(UINT32 ProcessorID);
extern void ReloadGdt();
extern void LoadTaskRegister();
uint64_t GetCurrentTimeIn100ns();
int TestLoop2();
void LouKeInitializeFullLouACPISubsystem();
extern void MachineCodeDebug(uint64_t FOO);
void LouKeSwitchContext(void (*Function)(), uint64_t StackSize);
void LouKeRunThreadContext(
    uint64_t Ctex,
    uint64_t CCTex
);
uint64_t GetThreadContext(
    int Thread
);
void UsrJmp(uint64_t Entry);
void read_rtc();
void ManualContextSwitch(uint64_t Context1, uint64_t Context_2);
bool LouKeMapEfiMemory();
void ListAllocatedPorts();
void LouKeHandleSystemIsBios();
void SetContext(uint64_t Context, uint64_t Function);
void SMPInit();
void LouOsKrnlMain();
uint8_t LouKeGetNumberOfStorageDevices();
void InitializeFileSystemManager();
void GenericVideoProtocolInitialize();
void InitializePoolsPool();
void CheckAndInitializePs2Controller();
void InitializeBusCore();
void InitializeAcpiSystem();
void InitializeDebuggerComunications();
void LouKeInitializeMouseHandling();
void LouKeIcUnmaskIrq(uint8_t irq);
void LouKePollIoApicPinForAssertion(uint8_t Pin);
uint64_t GetUsedMemory();
uint32_t Random32(uint32_t Seed);
void SetGSBase(uint64_t gs_base);
extern uint64_t RecreateDisasemblyIssue();
extern void SetTEB();
void* LouKeVirtualAllocUser(
    size_t      CommitSize,     //allocated PhysicalMemory
    size_t      ReservedSize,   //AllocatedVirtual
    uint64_t    PageFlags
);
uint32_t GetNPROC();
LOUSTATUS LouKeInitializeDefaultDemons();
void LouKeLoadLousineBootTrampoline();
int LouKeMainWorkDemon();
void PciMmcfgEarlyInit();
LOUSTATUS LouKeInitializeBootRegistry();
HANDLE LouKeLoadLibraryA(string Name);
void InitializeProcessManager();
void LouKeUnmaskSmpInterrupts();
DWORD LouKeThreadManagerDemon(PVOID Params);
struct _GENERIC_THREAD_DATA* LouKeThreadIdToThreadData(UINT32 ThreadID);
uint64_t GetCr3();
UINT64 GetPageBase();
LOUSTATUS LouKeObjManInitialize();
void LouKeInitializeSecuritySubsystem();
LOUSTATUS LouKeCreateSystemWorkQeueue();
void SetRamSize(UINT64 Size);
LOUSTATUS LouKeInitializeRatSubsystem(PLOADER_INFORMATION Info);
LOUSTATUS LouKeSetEfiTable(uint64_t Address);
LOUSTATUS LouKeSetRsdp(uintptr_t RSDP,uint8_t Type);
void InitializeFrameBuffer(PLOADER_FB_MEMORY_MAP FbMaps, SIZE Framebuffers);
void InitializeBootRegistry(uintptr_t Base, uintptr_t Top);
LOUSTATUS AddDriverToBootDeviceManager(uintptr_t Base, uintptr_t Top);
void SetTSCFrequency(uint64_t Frequency);
void SetTSC();
LOUSTATUS LouKeInitializeInterruptSubsystems();
void LouKeWaitForProcessorInitialization();
void LouKeApIdleTillApInitFunction();
void InitializeApicTimerVariableForIrql();
LOUAPI void LouKeWaitForApInitializationCompletion();

void AdvancedLousineKernelInitialization(){

    LouKeObjManInitialize();

    LouKeInitializeSecuritySubsystem();

    LouKeInitializeInterruptSubsystems();
        
    InitializeProcessManager();

    InitializeApicTimerVariableForIrql();

    LouKeSetIrql(PASSIVE_LEVEL, 0x00); 

    LouKeUnmaskSmpInterrupts();

    LouKeWaitForApInitializationCompletion();

    LouKeCreateDemon(
        LouKeThreadManagerDemon,
        0,
        16 * KILOBYTE,
        31
    );

    LouKeCreateSystemWorkQeueue();    

    while(1);

    LouKeInitializeFullLouACPISubsystem();







    LouPrint("Kernel Advanced System Initialized\n");
    
}

void LouKeInitProcessorAcceleratedFeaturesList(PPROCESSOR_FEATURES Features){
    if(!ProcAcceleratedFeatures){
        ProcAcceleratedFeatures = Features;
    }else{
        *ProcAcceleratedFeatures = *Features;
    }
}

typedef struct  PACKED _CPUContext{

    uint64_t rip;       // Instruction Pointer (user-mode entry point)
    uint64_t cs;        // Code Segment (should be set to user mode, typically 0x1B for x86_64)
    uint64_t rflags;    // Flags Register (set the interrupt flag, clear privileged bits)
    
    uint64_t rsp;       // Stack Pointer (points to user-mode stack)
    uint64_t ss;        // Stack Segment (should be user mode, typically 0x23 for x86_64)

} CPUContext;


void EnableCR0WriteProtection() {
    uint64_t cr0;
    asm volatile ("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= (1ULL << 16); // Set WP bit
    asm volatile ("mov %0, %%cr0" :: "r"(cr0));
}

void DisableCR0WriteProtection() {
    uint64_t cr0;
    asm volatile ("mov %%cr0, %0" : "=r"(cr0));
    cr0 &= ~(1ULL << 16); // Set WP bit
    asm volatile ("mov %0, %%cr0" :: "r"(cr0));
}


UNUSED static bool SystemIsEfi = false;

bool IsSystemEfi(){
    return SystemIsEfi;
}

void PrintProcessManagerSwaps();

LOUSTATUS LouKePlayWaveFile(FILE* WaveFile);
PRIFF_OBJECT LouKeOpenRiffFile(LOUSTR PathAndFile);

LOUAPI
LONG 
LouKeRtlCompareUtf16StringSafe(
    LPWSTR  String1,
    LPWSTR  String2,
    BOOLEAN CaseInSensitive,
    SIZE    Length
);

static LOADER_INFORMATION LousineKernelLoaderInformation = {0};

UINT64 LouKeGetKernelBase(){
    return (UINT64)LousineKernelLoaderInformation.KernelHandle;
}

LOUSTATUS SetUpTimers() {
	LOUSTATUS Status = STATUS_SUCCESS;
	SetTSCFrequency(LousineKernelLoaderInformation.TscCount);
	SetTSC();
	return Status;
}

KERNEL_EXPORT
uint64_t LouKeGetRamSize() {
    return LousineKernelLoaderInformation.RamSize;
}

void HaltAndCatchFile(){
    for (;;) {
        asm ("hlt");
    }
}

ULONG LouKeGetIdleingApCount();

LOUSTATUS ParserLouLoaderInformation(
    PLOADER_INFORMATION LoaderInfo
){
    LOUSTATUS Status;
    LouKeSetEfiTable((UINT64)LoaderInfo->EfiSystemTable);
    
    LouKeSetRsdp((UINT64)LoaderInfo->RsdpPointer, (UINT64)LoaderInfo->RsdpVersion);

    InitializeFrameBuffer(LoaderInfo->FrameBuffers, LoaderInfo->FrameBufferCount);

    InitializeBootRegistry(LoaderInfo->BootModulesBase[0].Tracker.Base, LoaderInfo->BootModulesBase[0].Tracker.Length);

    for(SIZE i = 1 ; i < LoaderInfo->BootModulesCount; i++){
        Status = AddDriverToBootDeviceManager(LoaderInfo->BootModulesBase[i].Tracker.Base, LoaderInfo->BootModulesBase[i].Tracker.Length);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
    }
    return STATUS_SUCCESS;
}

void LouOsKrnlStart(
    UINT64 pKernelLoaderInfo
){    
    PLOADER_INFORMATION OldLoader = (PLOADER_INFORMATION)pKernelLoaderInfo;
    OldLoader->LoaderApEntry = (UINT64)LouKeApIdleTillApInitFunction; 

    while(LouKeGetIdleingApCount() < OldLoader->ApCount){
        LouKeMemoryBarrier();
    }

    memcpy(&LousineKernelLoaderInformation, (PVOID)pKernelLoaderInfo, sizeof(LOADER_INFORMATION));

    pKernelLoaderInfo = 0x00;
    UINT64* Pml4  = (UINT64*)((UINT64)GetPageBase() + KSpaceBase);
    for(SIZE i = 0 ; i < 255; i++){
        Pml4[i] = 0x00;
    }
    LouKeReloadCR3();

    LOUSTATUS Status = LouKeInitializeRatSubsystem(&LousineKernelLoaderInformation);
    if(Status != STATUS_SUCCESS){
        HaltAndCatchFile();
    }

    ParserLouLoaderInformation(
        &LousineKernelLoaderInformation
    );

    LouKeInitializeBootRegistry();

    Status = SetupGDT(0);
    if(Status != STATUS_SUCCESS){
        HaltAndCatchFile();
    }

    Status = HandleProccessorInitialization();
    if(Status != STATUS_SUCCESS){
        HaltAndCatchFile();
    }

    SetUpTimers();
   
    LouKeInitializeEarlyKernelRuntimeEnviornment(LousineKernelLoaderInformation.KernelHandle);


    if(!LousineKernelLoaderInformation.EfiSystemTable){
        LouKeHandleSystemIsBios();
    }else {
        SystemIsEfi = true;
        InitializeEfiCore();
    }

    InitializePoolsPool();


    LouKeInitializeLouACPISubsystem();
        
    InitializeDebuggerComunications();

    AdvancedLousineKernelInitialization();

    LouKeInitializeKernelRuntimeEnviornment(LousineKernelLoaderInformation.KernelHandle);

    PciHalScanBootDevices();
         
    uint8_t StorageDevices = LouKeGetNumberOfStorageDevices();
    if(!StorageDevices){
        LouPrint("No Storage Devices Detected\n");
        while(1);
    }


    LouPrint("Successful Boot\n");
    while(1);

    InitializeFileSystemManager();

    LouKeInitializeMouseHandling();

    InitializeBusCore();

    LouKeProbeSbIsa();

    //PciHalScanRuntimeDevices();    

    //TODO: stub LdmCore.h 

    LouPrint("Lousine Kernel Version %s %s\n", KERNEL_VERSION ,KERNEL_ARCH);
    LouPrint("Hello Im Lousine Getting Things Ready\n");
    
    //while(1);

    PLOUSINE_ACCESS_TOKEN AccessToken = 0x00;

    PVOID AsmssKey = LouKeOpenRegistryHandle(
        L"KERNEL_DEFAULT_CONFIG\\Subsystems\\Asmss",
        0x00
    );
    if(!AsmssKey){
        LouPrint("ERROR Opening Sesion Manager Key\n");
        goto _SESSION_MANAGER_LAUNCH_FAILURE;
    }

    string PathKey;
    HANDLE SectionHandle;

    Status = LouKeRegGetAndCombineStringPath(
        AsmssKey,
        L"Path",
        L"Executable",
        &PathKey
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("ERROR Unable To Create String For Session Manager Path\n");
        goto _SESSION_MANAGER_LAUNCH_FAILURE;
    }

    LouPrint("Session Manager:%s\n", PathKey);    

    FILE* AsmssExe = LouKeZwOpenFile(PathKey, FOPEN_KERNEL_GENERIC_MEMORY);
    if(!AsmssExe){
        LouPrint("ERROR Unable To Open File\n");
        goto _SESSION_MANAGER_LAUNCH_FAILURE;
    }

    LouKeVmmCreateSectionEx(
        &SectionHandle,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        AsmssExe,
        0x00,
        0x00
    );    

    Status = LouKeZwCreateAccessToken(
        &AccessToken,
        true,
        0x00,
        0x00
    );

    if(Status != STATUS_SUCCESS){
        LouPrint("PANIC:Unable To Create System Token\n");
        while(1);
    }

    Status = LouKeZwRegisterAccessTokenToObjectManager(
        AccessToken,
        0
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("PANIC:Unable To Register System Token\n");
        while(1);
    }

    HANDLE AccessTokenHandle;
    
    Status = LouKeZwAcquireHandleForObjectEx(
        &AccessTokenHandle, 
        (PVOID)AccessToken
    );

    if(Status != STATUS_SUCCESS){
        LouPrint("PANIC:Unable To Get System Token Handle\n");
        while(1);
    }

    Status = LouKePmCreateProcessEx(
        0x00,
        ASMSS_PROCESS_NAME,
        PathKey,
        0x00,
        PROCESS_PRIORITY_HIGH,
        SectionHandle,
        AccessTokenHandle,
        0x00
    );

    if(Status != STATUS_SUCCESS){
        _SESSION_MANAGER_LAUNCH_FAILURE:
        LouPrint("ERROR Unable To Start Session Manager\n");
        sleep(5000);
        LouKeSystemShutdown(ShutdownReboot);
        while(1);
    }
    LouPrint("Lousine Kernel Successfully Initialized\n");
    //sleep(3000);
    //LouKeSystemShutdown(ShutdownReboot);
    LouKeDestroyThread(LouKeThreadIdToThreadData(LouKeGetThreadIdentification()));
    //ITS ALIIIIIVVVVEE!!!
    while(1);
}


//TODO: 
//Check on NULL references as i go through code : I Updated How The Memory Manager Handles Errors
//Add mutex to the registry keys and a close function
//tighten read only security
//add a schedualer stop for DISPATCH_LEVEL

//BUGS TO FIX:

//58015

/*	
USB 1.1 (UHCI / OHCI)	Moderate	Fits here (simpler linked list design).
PCI Sound Cards	Moderate	
Intel 8254x NIC	Moderate	
USB 2.0 (EHCI)	Moderate-to-Hard	Fits here (periodic/asynchronous queues).
USB 3.0+ (xHCI)	Harder	Fits here (TRBs, ring buffers).
PCI Storage (NVMe)	Harder	
GPUs	Hardest	
PCIe FPGA Cards	Hardest	
High-Performance NICs	Hardest
*/
