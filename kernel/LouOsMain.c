#define KERNEL_MAIN_FILE
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


/* Tyler Grenier 10/4/23 9:56 PM
-- Started the file with the main
-- functions to get us going along 
-- with allocation functions
*/

string KERNEL_VERSION = "0.6.04 RSC-5";

string KERNEL_ARCH = "64-BIT";

LOUSINE_LOADER_INFO KernelLoaderInfo = {0};


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
uint64_t GetRamSize();
void InitializeEfiCore();
LOUSTATUS InitializeDirecAccess();
void initializeInterruptRouter();
void InitializeGenericTables();
void ListUsedAddresses();
uint64_t getTrampolineAddress();
uint8_t GetTotalHardwareInterrupts();
uint64_t GetGdtBase();
void FlushTss();
void InitializeBasicMemcpy();
void Spurious(uint64_t FaultingStackP);
void InitializeNtKernelTransitionLayer();
void LouKeInitializeLouACPISubsystem();
void HandleProccessorInitialization();
void InitializeBootGraphics();
void InitializeInterruptRouter();
void LouKeProbeSbIsa();
void SetupGDT();
extern void ReloadGdt();
extern void LoadTaskRegister();
uint64_t GetCurrentTimeIn100ns();
int TestLoop2();
void LouKeInitializeFullLouACPISubsystem();
extern void MachineCodeDebug(uint64_t FOO);
void LouKeSwitchContext(void (*Function)(), uint64_t StackSize);
LOUSTATUS LookForStorageDevices();
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
void LouKeMapPciMemory();
bool LouKeMapEfiMemory();
void ListAllocatedPorts();
void ScanTheRestOfHarware();
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
extern uint64_t GetRBP();
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
void LouKePcieProbeEcam();
LOUSTATUS LouKeInitializeRegistry();
HANDLE LouKeLoadLibraryA(string Name);
void InitializeProcessManager();
void LouKeInitializeSmpLouPrint();
void LouKeUnmaskSmpInterrupts();
void ParserLouLoaderInformation(
    PLOUSINE_LOADER_INFO LoaderInfo
);
void* memcpy_basic(void* destination, const void* source, size_t num);
DWORD LouKeThreadManagerDemon(PVOID Params);
struct _GENERIC_THREAD_DATA* LouKeThreadIdToThreadData(UINT64 ThreadID);
uint64_t GetCr3();



LOUSTATUS LousineKernelEarlyInitialization(){

    //basic kernel initialization for IR Exceptions to keep the guru away
    SetupGDT();

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

    return LOUSTATUS_GOOD;
}

void InitializeSymmetricMultiProcessing(){
    LouPrint("Checking If System Supports SMP\n");
    if(GetNPROC() < 2)return;
    LouPrint("InitializeSymmetricMultiProcessing()\n");    
    LouKeLoadLousineBootTrampoline();

    LouKeInitializeSmpLouPrint();

    LouPrint("InitializeSymmetricMultiProcessing() STATUS_SUCCESS\n");    

}

void LouKeWaitForProcessorInitialization();

void AdvancedLousineKernelInitialization(){
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

    LouKeUnmaskSmpInterrupts();

    LouPrint("Kernel Advanced System Initialized\n");
    
}

void KillDebuger(){
    //DetatchWindowToKrnlDebug(HWind);
    //LouDestroyWindow(HWind);
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


UNUSED static bool SystemIsEfiv = false;

bool IsSystemEfi(){
    return SystemIsEfiv;
}

void PrintProcessManagerSwaps();

void LouKeInitializePciDevices(){

    LouKeMapPciMemory();

    PciMmcfgEarlyInit();

    LouKePcieProbeEcam();
}

void LouKeSantyCheckPciDevices();

KERNEL_ENTRY LouOsKrnlStart(
    UINT64 pKernelLoaderInfo
){    

    memcpy_basic((void*)&KernelLoaderInfo, (void*)pKernelLoaderInfo, sizeof(LOUSINE_LOADER_INFO));
    
    UINT64 Cr3 =  (UINT64)GetCr3();
    Cr3 += GetKSpaceBase();

    for(size_t i = 0 ; i < 255; i++){
        ((UINT64*)Cr3)[i] = 0;
    }

    EnableCR0WriteProtection();

    
    ParserLouLoaderInformation(
        &KernelLoaderInfo
    );

    InitializeBasicMemcpy();

    ///vga set for debug
    if(!LouKeMapEfiMemory()){
        LouKeHandleSystemIsBios();
    }else {
        SystemIsEfiv = true;
        InitializeEfiCore();
    }                      

    LouKeInitializeRegistry();
     
    LousineKernelEarlyInitialization();
    
    InitializePoolsPool();

    LouKeInitializeLouACPISubsystem();

    InitializeDebuggerComunications();

    LouKeInitializePciDevices();

    LouKeSantyCheckPciDevices();

    InitializeBootGraphics();

    //INITIALIZE IMPORTANT THINGS FOR US LATER
    InitializeGenericTables();

    AdvancedLousineKernelInitialization();

    LookForStorageDevices();
        
    uint8_t StorageDevices = LouKeGetNumberOfStorageDevices();
    if(!StorageDevices){
        LouPrint("No Storage Devices Detected\n");
        while(1);
    }

    InitializeFileSystemManager();

    InitializeNtKernelTransitionLayer();

    LouKeInitializeMouseHandling();

    InitializeBusCore();

    LouKeProbeSbIsa();

    ScanTheRestOfHarware();

    LouPrint("Lousine Kernel Version %s %s\n", KERNEL_VERSION ,KERNEL_ARCH);
    LouPrint("Hello Im Lousine Getting Things Ready\n");

    //LOUSTATUS LouKePmCreateProcessEx(
    //    PHPROCESS                       HandleOut,          //Optional                       
    //    string                          ProcessName,        //Process Name
    //    PHPROCESS                       ParrentProcess,     //Parent Process Handle           
    //    UINT8                           Priority,           //Process Schedualer Priority
    //    HANDLE                          Section,            //Section of the Executable Image
    //    PLOUSINE_CREATE_PROCESS_PARAMS  Params              //otpional Params
    //);

    PVOID AsmssKey = LouKeOpenRegistryHandle(
        L"KERNEL_DEFAULT_CONFIG\\Subsystems\\Asmss",
        0x00
    );
    if(!AsmssKey){
        LouPrint("ERROR Opening Sesion Manager Key\n");
        goto _SESSION_MANAGER_LAUNCH_FAILURE;
    }
    string PathKey;
    LOUSTATUS Status;

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

    FILE* AsmssExe = fopen(PathKey, KERNEL_GENERIC_MEMORY);
    if(!AsmssExe){
        LouPrint("ERROR Unable To Open File\n");
        goto _SESSION_MANAGER_LAUNCH_FAILURE;
    }

    HANDLE SectionHandle;

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

    Status = LouKePmCreateProcessEx(
        0x00,
        ASMSS_PROCESS_NAME,
        0x00,
        PROCESS_PRIORITY_HIGH,
        SectionHandle,
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

void LouKeGetSystemUpdate(PSYSTEM_STATE_STACK Stack){

}

//TODO:
// check and optimize Lousine Kernel Exports in API/LouAPI/tables.c

//BUGS TO FIX:

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
