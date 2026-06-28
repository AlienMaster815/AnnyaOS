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
void PageFault(UINT64 Rsp);
void GPF(UINT64 Rsp);
void DoubleFault(UINT64 Rsp);
void Clock(UINT64 SavedState);
void INTERRUPT(UINT8 interrupt_number);
void NMI(UINT64 Rsp);
void BreakPoint(UINT64 Rsp);
void DivideByZero(UINT64 Stack);
void OverFlow(UINT64 Rsp);
void BoundRange(UINT64 Rsp);
void Debug(UINT64 Rsp);
void InvalidOpcode(UINT64 Rsp);
void FloatDeviceNotAvailable(UINT64 Rsp);
void CpOverun(UINT64 Rsp);
void SegmentNotPresent(UINT64 Rsp);
void StackSegmentFault(UINT64 Rsp);
void x87FloatPointError(UINT64 Rsp);
void AlignmentCheck(UINT64 Rsp);
void MachineCheck(UINT64 Rsp);
void SIMDFloatPointException(UINT64 Rsp);
void VirtualizationException(UINT64 Rsp);
void ControlProtectionException(UINT64 Rsp);
void CookieCheckFail(UINT64 Rsp);
void ParseMBootTags(struct multiboot_tag* MBOOT);
uint64_t LouKeGetRamSize();
void InitializeEfiCore();
LOUSTATUS InitializeDirecAccess();
void initializeInterruptRouter();
void LouKeInitializeKernelRuntimeEnviornment(KHANDLE KernelHandle);
void ListUsedAddresses();
uint64_t getTrampolineAddress();
uint8_t GetTotalHardwareInterrupts();
uint64_t GetGdtBase();
void FlushTss();
void Spurious(uint64_t FaultingStackP);
void LouKeInitializeLouACPISubsystem();
void HandleProccessorInitialization();
void InitializeInterruptRouter();
void LouKeProbeSbIsa();
void SetupGDT(UINT32 ProcessorID);
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
uint16_t GetNPROC();
LOUSTATUS LouKeInitializeDefaultDemons();
void LouKeLoadLousineBootTrampoline();
int LouKeMainWorkDemon();
void PciMmcfgEarlyInit();
LOUSTATUS LouKeInitializeBootRegistry();
HANDLE LouKeLoadLibraryA(string Name);
void InitializeProcessManager();
void LouKeInitializeSmpLouPrint();
void LouKeUnmaskSmpInterrupts();
DWORD LouKeThreadManagerDemon(PVOID Params);
struct _GENERIC_THREAD_DATA* LouKeThreadIdToThreadData(UINT32 ThreadID);
uint64_t GetCr3();
UINT64* GetPageBase();
LOUSTATUS LouKeObjManInitialize();
void LouKeInitializeSecuritySubsystem();
LOUSTATUS LouKeCreateSystemWorkQeueue();
void SetRamSize(UINT64 Size);
LOUSTATUS LouKeInitializeRatSubsystem(PLOADER_INFORMATION Info);
LOUSTATUS LouKeSetEfiTable(uint64_t Address);
LOUSTATUS LouKeSetRsdp(uintptr_t RSDP,uint8_t Type);
void InitializeFrameBuffer(PLOADER_FB_MEMORY_MAP FbMaps, SIZE Framebuffers);
void InitializeBootRegistry(uintptr_t Base, uintptr_t Top);
void AddDriverToBootDeviceManager(uintptr_t Base, uintptr_t Top);
void SetTSCFrequency(uint64_t Frequency);
void SetTSC();

LOUSTATUS LousineKernelEarlyInitialization(){

    //basic kernel initialization for IR Exceptions to keep the guru away
    SetupGDT(0);

    HandleProccessorInitialization();

    InitializeInterruptRouter();

    InitializeStartupInterruptHandleing();

    RegisterInterruptHandler(DivideByZero, INTERRUPT_SERVICE_ROUTINE_0, false, 0);
    RegisterInterruptHandler(Debug, INTERRUPT_SERVICE_ROUTINE_1, false, 0);
    RegisterInterruptHandler(NMI, INTERRUPT_SERVICE_ROUTINE_2, false, 0);
    RegisterInterruptHandler(BreakPoint, INTERRUPT_SERVICE_ROUTINE_3, false, 0);
    RegisterInterruptHandler(OverFlow, INTERRUPT_SERVICE_ROUTINE_4, false, 0);
    RegisterInterruptHandler(BoundRange, INTERRUPT_SERVICE_ROUTINE_5, false, 0);
    RegisterInterruptHandler(InvalidOpcode, INTERRUPT_SERVICE_ROUTINE_6, false, 0);
    RegisterInterruptHandler(FloatDeviceNotAvailable, INTERRUPT_SERVICE_ROUTINE_7, false, 0);
    RegisterInterruptHandler(DoubleFault, INTERRUPT_SERVICE_ROUTINE_8, false, 0);
    RegisterInterruptHandler(CpOverun, INTERRUPT_SERVICE_ROUTINE_9, false, 0);
    //RegisterInterruptHandler(TSS, INTERRUPT_SERVICE_ROUTINE_10);//
    RegisterInterruptHandler(SegmentNotPresent, INTERRUPT_SERVICE_ROUTINE_11, false, 0);
    RegisterInterruptHandler(StackSegmentFault, INTERRUPT_SERVICE_ROUTINE_12, false, 0);
    RegisterInterruptHandler(GPF, INTERRUPT_SERVICE_ROUTINE_13, false, 0);
    RegisterInterruptHandler(PageFault, INTERRUPT_SERVICE_ROUTINE_14, false, 0);
    RegisterInterruptHandler(x87FloatPointError, INTERRUPT_SERVICE_ROUTINE_16, false, 0);
    RegisterInterruptHandler(AlignmentCheck, INTERRUPT_SERVICE_ROUTINE_17, false, 0);
    RegisterInterruptHandler(MachineCheck, INTERRUPT_SERVICE_ROUTINE_18, false, 0);
    RegisterInterruptHandler(SIMDFloatPointException, INTERRUPT_SERVICE_ROUTINE_19, false, 0);
    RegisterInterruptHandler(VirtualizationException, INTERRUPT_SERVICE_ROUTINE_20, false, 0);
    RegisterInterruptHandler(ControlProtectionException, INTERRUPT_SERVICE_ROUTINE_21, false, 0);
    //RegisterInterruptHandler(UpdateProcessManager, INTERRUPT_SERVICE_ROUTINE_32, false, 0);
    //RegisterInterruptHandler(CookieCheckFail, 0x29, false, 0);
    //RegisterInterruptHandler((void(*))getTrampolineAddress(), 0x50, false, 0);
    RegisterInterruptHandler((void(*))Spurious, 0xFF, true, 0);


    SetUpTimers();
    //DeterminCPU();

    return STATUS_SUCCESS;
}

void InitializeSymmetricMultiProcessing(){
    LouPrint("Checking If System Supports SMP\n");
    if(GetNPROC() < 2)return;
    //TODO: redo SMP
    //LouPrint("InitializeSymmetricMultiProcessing()\n");    
    //LouKeLoadLousineBootTrampoline();

    //LouKeInitializeSmpLouPrint();

    //LouPrint("InitializeSymmetricMultiProcessing() STATUS_SUCCESS\n");    

}

void LouKeWaitForProcessorInitialization();

void AdvancedLousineKernelInitialization(){

    LouKeObjManInitialize();

    LouKeInitializeSecuritySubsystem();

    if (InitializeMainInterruptHandleing() != STATUS_SUCCESS)LouPrint("Unable To Setup Interrupt Controller System\n");
        
    InitializeSymmetricMultiProcessing();

    InitializeProcessManager();

    LouKeInitializeFullLouACPISubsystem();

    LouKeSetIrql(PASSIVE_LEVEL, 0x00); 
    
    LouKeCreateDemon(
        LouKeThreadManagerDemon,
        0,
        16 * KILOBYTE,
        31
    );

    LouKeCreateSystemWorkQeueue();    

    LouKeUnmaskSmpInterrupts();

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

static void HaltAndCatchFile() {
    for (;;) {
        asm ("hlt");
    }
}

void ParserLouLoaderInformation(
    PLOADER_INFORMATION LoaderInfo
){

    LouKeSetEfiTable((UINT64)LoaderInfo->EfiSystemTable);

    LouKeSetRsdp((UINT64)LoaderInfo->RsdpPointer, (UINT64)LoaderInfo->RsdpVersion);

    InitializeFrameBuffer(LoaderInfo->FrameBuffers, LoaderInfo->FrameBufferCount);

    InitializeBootRegistry(LoaderInfo->BootModulesBase[0].Tracker.Base, LoaderInfo->BootModulesBase[0].Tracker.Length);

    for(SIZE i = 1 ; i < LoaderInfo->BootModulesCount; i++){
        AddDriverToBootDeviceManager(LoaderInfo->BootModulesBase[i].Tracker.Base, LoaderInfo->BootModulesBase[i].Tracker.Length);
    }

}
/* TODO:Destroy loader States

*/

void LouOsKrnlStart(
    UINT64 pKernelLoaderInfo
){    

    EnableCR0WriteProtection();
    memcpy(&LousineKernelLoaderInformation, (PVOID)pKernelLoaderInfo, sizeof(LOADER_INFORMATION));
    UINT64* Pml4 = (UINT64*)((UINT64)GetPageBase() + KSpaceBase);

    LOUSTATUS Status = LouKeInitializeRatSubsystem(&LousineKernelLoaderInformation);
    if(Status != STATUS_SUCCESS){
        HaltAndCatchFile();
    }
    ParserLouLoaderInformation(
        &LousineKernelLoaderInformation
    );

    for(SIZE i = 0 ; i < 255; i++){
        Pml4[i] = 0x00;
    }
    LouKeReloadCR3();
    LouKeRatFreeAddress((UINTPTR)LousineKernelLoaderInformation.LoaderHandle);

    if(!LousineKernelLoaderInformation.EfiSystemTable){
        LouKeHandleSystemIsBios();
    }else {
        SystemIsEfi = true;
        InitializeEfiCore();
    }

    LouKeInitializeBootRegistry();

    LousineKernelEarlyInitialization();

    InitializePoolsPool();

    LouKeInitializeLouACPISubsystem();
    
    InitializeDebuggerComunications();

    AdvancedLousineKernelInitialization();

    LouKeInitializeKernelRuntimeEnviornment(LousineKernelLoaderInformation.KernelHandle);

    while(1);

    PciHalScanBootDevices();
         
    uint8_t StorageDevices = LouKeGetNumberOfStorageDevices();
    if(!StorageDevices){
        LouPrint("No Storage Devices Detected\n");
        while(1);
    }


    //LouPrint("Successful Boot\n");
    //while(1);

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
//xAPIC has been depreciated work on x2APIC
//Add mutex to the registry keys and a close function
//Fix SMP Booting
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
