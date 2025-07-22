#ifdef __x86_64__
#include <LouAPI.h>
#include <bootloader/grub/multiboot2.h>
#endif
#ifdef __i386__
#include <kernel/errors.h>
#include <kernel/kernel.h>
#include <KernelAPI/IOManager.h>
#include <kernel/interrupts.h>
#include <drivers/Lou_drivers/FileSystem.h>
#include <stdio.h>
#include <drivers/display/vga.h>
#include <LouACPI.h>

extern LOUSTATUS InitializeStartupInterruptHandleing();

#define DEBUG 1

extern void SetInterruptFlags();
extern void UnSetInterruptFlags();

#endif

uintptr_t RSP_Current;
uintptr_t RBP_Current;


/* Tyler Grenier 9/21/23 9:56 PM
-- Started the file with the main
-- functions to get us going along 
-- with allocation functions
*/

string KERNEL_VERSION = "0.5.04 RSC-1";

#ifdef __x86_64__
string KERNEL_ARCH = "64-BIT";
#endif
#ifdef __i386__
sring KERNEL_ARCH = "32-BIT";
#endif

LOUSTATUS InitFADT();
LOUSTATUS InitDSDT();
LOUSTATUS InitSSDT();
LOUSTATUS InitSBST();
LOUSTATUS InitSRAT();
LOUSTATUS InitBGRT();
LOUSTATUS InitECDT();
LOUSTATUS InitSLIT();
LOUSTATUS InitMCFG();
LOUSTATUS InitThreadManager();
LOUSTATUS SetUpTimers();
void PS2KeyboardHandler(UINT64 Rsp);
void PS2MouseHandler(UINT64 Rsp);
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
//void TSS();
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
void InitPreLoadedModules();
void ParseMBootTags(struct multiboot_tag* MBOOT);
void CreateNewPageSystem();
uint64_t GetRamSize();
void InitializeSystemCalls();
void initialize_ps2_keyboard();    uint64_t ContextHandle = 0x00;
void InitializeEfiCore();
LOUSTATUS InitializeDirecAccess();
LOUSTATUS InitializeDynamicHardwareInterruptHandleing();
void initializeInterruptRouter();
void InitializeGenericTables();
void InitializeVesaSystem();
void ListUsedAddresses();
uint64_t getTrampolineAddress();
PWINDHANDLE HWind = 0x00;
void AdvancedInterruptRouter(uint64_t InterruptNumber, uint64_t Args);
uint8_t GetTotalHardwareInterrupts();
uint64_t GetGdtBase();
void FlushTss();
LOUSTATUS SetupInitialVideoDevices();
void LouKeRunOnNewUserStack(void (*func)(void*), void* FunctionParameters, size_t StackSize);
void InitializeBasicMemcpy();
void Spurious(uint64_t FaultingStackP);
void InitializeNtKernelTransitionLayer();
void LouKeInitializeLouACPISubsystem();
void HandleProccessorInitialization();
void InitializeBootGraphics();
void LouKeDrsdDrawDesktopBackground(
    FILE* ImageFile,
    uint16_t DrsdFileType
);
void UpdateThreadManager(uint64_t Rsp);
void InitializeInterruptRouter();

void SetupGDT();
extern void ReloadGdt();
extern void LoadTaskRegister();
uint64_t GetCurrentTimeIn100ns();

LOUSTATUS LousineKernelEarlyInitialization(){

    //basic kernel initialization for IR Exceptions to keep the guru away
    SetupGDT();

    HandleProccessorInitialization();

    InitializeBootGraphics();

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
    RegisterInterruptHandler(UpdateThreadManager, INTERRUPT_SERVICE_ROUTINE_32, false, 0);
    RegisterInterruptHandler(CookieCheckFail, 0x29, false, 0);
    //RegisterInterruptHandler((void(*))getTrampolineAddress(), 0x50, false, 0);
    RegisterInterruptHandler((void(*))Spurious, 0xFF, true, 0);


    SetUpTimers();
    //DeterminCPU();

    return LOUSTATUS_GOOD;
}

void StorPortInitializeAllDevices();

int InitKThread();
int TestLoop2();


void InitializeDeviceManager();
LOUSTATUS LouKeMallocAdvancedKernelInterruptHandleing();

void HandleProccessorInitialization();
void LouKeInitializeAcpicaSubSystem();
void LouKeInitializeFullLouACPISubsystem();

void AdvancedLousineKernelInitialization(){
    if (InitializeMainInterruptHandleing() != LOUSTATUS_GOOD)LouPrint("Unable To Setup Interrupt Controller System\n");
    InitThreadManager();
    LouKeInitializeFullLouACPISubsystem();
    LouKeSetIrql(PASSIVE_LEVEL, 0x00);    
}

bool LouMapAddress(uint64_t PAddress, uint64_t VAddress, uint64_t FLAGS, uint64_t PageSize);

void LouKeDestroyThread();

void TestFontFunction();
extern void MachineCodeDebug(uint64_t FOO);

bool DetatchWindowToKrnlDebug(PWINDHANDLE WindowSecurityCheck);

void KillDebuger(){
    //DetatchWindowToKrnlDebug(HWind);
    //LouDestroyWindow(HWind);
}

void LouKeRunOnNewStack(void (*func)(void), void* FunctionParameters, size_t stack_size);

void LouKeSwitchContext(void (*Function)(), uint64_t StackSize);

LOUSTATUS LookForStorageDevices();

void LouKeRunThreadContext(
    uint64_t Ctex,
    uint64_t CCTex
);

uint64_t GetThreadContext(
    int Thread
);

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

void LouKeInitProcessorAcceleratedFeaturesList(PPROCESSOR_FEATURES Features){
    if(!ProcAcceleratedFeatures){
        ProcAcceleratedFeatures = Features;
    }else{
        *ProcAcceleratedFeatures = *Features;
    }
}

void read_rtc();
void ManualContextSwitch(uint64_t Context1, uint64_t Context_2);
void LouKeMapPciMemory();
bool LouKeMapEfiMemory();
void ListAllocatedPorts();
void ScanTheRestOfHarware();
void LouKeHandleSystemIsBios();

//static mutex_t SmpStartupMutex;

KERNEL_ENTRY LouKernelSmpStart(){

    SetupGDT();
    InitializeStartupInterruptHandleing();
    LouPrint("Processor Succesfully Idleing\n");

    while(1){
        asm ("hlt"); //spin the cpus untill context assignement
    }
}

void UsrJmp(uint64_t Entry);

bool LouMapAddressEx(uint64_t PAddress, uint64_t VAddress, uint64_t FLAGS, bool LargePage);


void PrintTest(){
    while(1){
        LouPrint("FOO ");
    }
}

void SetContext(uint64_t Context, uint64_t Function);


typedef struct  PACKED _CPUContext{

    uint64_t rip;       // Instruction Pointer (user-mode entry point)
    uint64_t cs;        // Code Segment (should be set to user mode, typically 0x1B for x86_64)
    uint64_t rflags;    // Flags Register (set the interrupt flag, clear privileged bits)
    
    uint64_t rsp;       // Stack Pointer (points to user-mode stack)
    uint64_t ss;        // Stack Segment (should be user mode, typically 0x23 for x86_64)

} CPUContext;


void SMPInit();
void InitializeUserSpace();
void LouKeInitializeSafeMemory();
void CheckForPs2Mouse();
void InitializeInternalChipsetHostDriver();
uint8_t LouKeGetNumberOfStorageDevices();
void InitializeFileSystemManager();
void GenericVideoProtocolInitialize();
void InitializePs2Mouse();
void EnablePs2Keyboard();
void CheckForSoundblaster16();
void InitializeSafePage();
void* LouKeMallocEx2(
    size_t      AllocationSize,
    size_t      Alignment,
    uint64_t    AllocationFlags
);

void LouKeFree2(void* Address);

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
void InitializeAcpiSystem();
void InitializeDebuggerComunications();
void LouKeInitializeMouseManagemet();
void LouKeIcUnmaskIrq(uint8_t irq);
void IoApicConfigureEntryFlags(
    uint8_t     irq,
    uint16_t    Flags
);
void LouKePollIoApicPinForAssertion(uint8_t Pin);

UNUSED static bool SystemIsEfiv = false;

bool IsSystemEfi(){
    return SystemIsEfiv;
}
void InitializePoolsPool();

KERNEL_ENTRY Lou_kernel_start(
    uint32_t MBOOT
){    
    struct multiboot_tag* mboot = (struct multiboot_tag*)(uintptr_t)(MBOOT + 8);
    ParseMBootTags(mboot);
    InitializeBasicMemcpy();

    ///vga set for debug
    if(!LouKeMapEfiMemory()){
        LouKeHandleSystemIsBios();
    }else {
        SystemIsEfiv = true;
        InitializeEfiCore();
    }                      
    
    LouKeInitializeSafeMemory();    
    
    LousineKernelEarlyInitialization();

    LouKeMapPciMemory();

    InitializePoolsPool();

    LouKeInitializeLouACPISubsystem();

    //INITIALIZE IMPORTANT THINGS FOR US LATER
    InitializeGenericTables();

    AdvancedLousineKernelInitialization();

    InitializeDebuggerComunications();

    //LouPrint("Here\n");
    //while(1);
    //TODO: Add a parser for the manifest for 
    //loading needed modules that need to be 
    //loaded no matter what
    LookForStorageDevices();

    uint8_t StorageDevices = LouKeGetNumberOfStorageDevices();
    if(!StorageDevices){
        LouPrint("No Storage Devices Detected\n");
        while(1);
    }

    InitializeFileSystemManager();
    InitializeNtKernelTransitionLayer();

    //CheckForSoundblaster16();
    ScanTheRestOfHarware();
    
    //SMPInit();
	
    LouPrint("Lousine Kernel Version %s %s\n", KERNEL_VERSION ,KERNEL_ARCH);
    LouPrint("Hello Im Lousine Getting Things Ready\n");
    
    LouKeRunOnNewUserStack((void (*)(void*))InitializeUserSpace, 0x00, 8 * MEGABYTE);
	LouPanic("error kernel has gone too far terminating system\n",BAD);
	// IF the Kernel returns from this
	// the whole thing crashes
}

//131df

void TrampolineFinalInit(){
    LouPrint("SMP Final Initializations\n");

    LouPrint("SMP Final Initializations Finished\n");
    LouKeRunOnNewStack(LouKernelSmpStart, 0 , 16 * KILOBYTE);
}

uint64_t GetUsedMemory();
uint32_t Random32(uint32_t Seed);

void SetGSBase(uint64_t gs_base);
uint64_t GetGSBase();

extern uint64_t GetRBP();

extern uint64_t RecreateDisasemblyIssue();
extern void SetTEB();

bool LouKeCreateProcessA(
    string                          ApplicationName,
    string                          CommandLine,
    PWIN_API_SECUTIY_ATTRIBUTES     ProcessAttributes,
    PWIN_API_SECUTIY_ATTRIBUTES     ThreadAttributes,
    bool                            Inherited,
    uint32_t                        Flags,
    void*                           Enviornment,
    string                          CurrentDirectory,
    PWIN_API_STARTUP_INFOA          StartupInformation,
    PWIN_API_PROCESS_INFORMATION    ProcessInformation,
    bool                            AnnyaAPIProcess //AnnyaAPI uses different flags and setups
);

void* LouKeVirtualAllocUser(
    size_t      CommitSize,     //allocated PhysicalMemory
    size_t      ReservedSize,   //AllocatedVirtual
    uint64_t    PageFlags
);

extern void SetPEB(uint64_t PEB);
uint16_t GetNPROC();

void InitializeUserSpace(){
    LouPrint("Initializing User Mode\n");

    LouKeLoadUserModule("C:/ANNYA/SYSTEM64/LOUDLL.DLL", 0x00); //this is the systems access into the kernel so no matter what load it
    void (*SendProcessorFeaturesToLouMemCpy)(PPROCESSOR_FEATURES) = (void (*)(PPROCESSOR_FEATURES))LouKeLinkerGetAddress("LOUDLL.DLL", "SendProcessorFeaturesToLouMemCpy");
    SendProcessorFeaturesToLouMemCpy(ProcAcceleratedFeatures);
    
    LouPrint("LOUDLL.DLL Has Loaded\n");
    LouKeLoadUserModule("C:/ANNYA/SYSTEM64/NTDLL.DLL", 0x00);
    LouPrint("NTDLL.DLL Has Loaded\n");
    LouKeLoadUserModule("C:/ANNYA/SYSTEM64/KERNEL32.DLL", 0x00); //KERNEL32 is required for loading dlls
    LouPrint("KERNEL32.DLL Has Loaded\n");
    LouKeLoadUserModule("C:/ANNYA/SYSTEM64/KERNBASE.DLL", 0x00);
    LouPrint("KERNBASE.DLL Has Loaded\n");
    LouKeLoadUserModule("C:/ANNYA/SYSTEM64/USER32.DLL", 0x00);
    LouPrint("USER32.DLL Has Loaded\n");

    PWIN_PEB ProcessExecutionBlock = (PWIN_PEB)LouKeMallocEx(sizeof(WIN_PEB), GET_ALIGNMENT(WIN_PEB), USER_GENERIC_MEMORY);
    SetPEB((uint64_t)ProcessExecutionBlock);
    LouPrint("ProcessExecutionBlock:%h\n", ProcessExecutionBlock);
    ProcessExecutionBlock->NumberOfProcessors = GetNPROC();
    ProcessExecutionBlock->ProcessHeap = (uint64_t)LouKeVirtualAllocUser(MEGABYTE_PAGE, 10 * MEGABYTE, USER_GENERIC_MEMORY);
    
    uint64_t InitEntry = (uint64_t)LouKeLoadPeExecutable("C:/ANNYA/ANNYAEXP.EXE");

    LouPrint("System Memory:%d MEGABYTES Usable\n", (GetRamSize() / (1024 * 1024)));
   
    LouPrint("Hello World\n");

    if(!InitEntry){
        LouPrint("ERROR Could Not Jump To Usermode\n");
        while(1);
    }

    UsrJmp(InitEntry);
}

void LouKeUpdateMouseState(PSYSTEM_STATE_STACK State);

void LouKeGetSystemUpdate(PSYSTEM_STATE_STACK Stack){
    LouKeUpdateMouseState(Stack);
    EnablePs2Keyboard();
    InitializePs2Mouse();
}

//0x220B21030

//TODO : 

//BUGS TO FIX:
//memcpy doesent use SSE correctly

//Intel Corporation	8086	Skylake GT2 [HD Graphics 520]	1916

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
//TODO finish Ps an WMI