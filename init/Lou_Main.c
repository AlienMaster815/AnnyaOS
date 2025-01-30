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

string KERNEL_VERSION = "0.4.06 Build-2";

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
void LastSataRun();
void PS2KeyboardHandler();
void PS2MouseHandler();
void PageFault();
void GPF();
void DoubleFault();
void Clock(uint64_t SavedState);
void INTERRUPT(uint8_t interrupt_number);
void NMI();
void BreakPoint();
void DivideByZero();
void OverFlow();
void BoundRange();
void Debug();
void InvalidOpcode();
void FloatDeviceNotAvailable();
//void TSS();
void CpOverun();
void SegmentNotPresent();
void StackSegmentFault();
void x87FloatPointError();
void AlignmentCheck();
void MachineCheck();
void SIMDFloatPointException();
void VirtualizationException();
void ControlProtectionException();
void CookieCheckFail();
void InitPreLoadedModules();
void ParseMBootTags(struct multiboot_tag* MBOOT);
void CreateNewPageSystem();
uint64_t GetRamSize();
void InitializeSystemCalls();
void SYSCALLS();
void initialize_ps2_keyboard();
LOUSTATUS InitializeDirecAccess();
LOUSTATUS InitializeDynamicHardwareInterruptHandleing();
void initializeInterruptRouter();
void InitializeGenericTables();
void InitializeVesaSystem();
void ListUsedAddresses();
uint64_t getTrampolineAddress();
PWINDHANDLE HWind;
void AdvancedInterruptRouter(uint64_t InterruptNumber, uint64_t Args);
uint8_t GetTotalHardwareInterrupts();
uint64_t GetGdtBase();
void FlushTss();
LOUSTATUS SetupInitialVideoDevices();
void InitializeAllProcessorFeatures();


void LouKeDrsdDrawDesktopBackground(
    FILE* ImageFile,
    uint16_t DrsdFileType
);


void SetupGDT();
extern void ReloadGdt();
extern void LoadTaskRegister();
LOUSTATUS Lou_kernel_early_initialization(){

    //basic kernel initialization for IR Exceptions to keep the guru away

    SetupGDT();

    InitializeStartupInterruptHandleing();
    initializeInterruptRouter();
    RegisterInterruptHandler(DivideByZero, INTERRUPT_SERVICE_ROUTINE_0);
    RegisterInterruptHandler(Debug, INTERRUPT_SERVICE_ROUTINE_1);
    RegisterInterruptHandler(NMI, INTERRUPT_SERVICE_ROUTINE_2);
    RegisterInterruptHandler(BreakPoint, INTERRUPT_SERVICE_ROUTINE_3);
    RegisterInterruptHandler(OverFlow, INTERRUPT_SERVICE_ROUTINE_4);
    RegisterInterruptHandler(BoundRange, INTERRUPT_SERVICE_ROUTINE_5);
    RegisterInterruptHandler(InvalidOpcode, INTERRUPT_SERVICE_ROUTINE_6);
    RegisterInterruptHandler(FloatDeviceNotAvailable, INTERRUPT_SERVICE_ROUTINE_7);
    RegisterInterruptHandler(DoubleFault, INTERRUPT_SERVICE_ROUTINE_8);
    RegisterInterruptHandler(CpOverun, INTERRUPT_SERVICE_ROUTINE_9);
    //RegisterInterruptHandler(TSS, INTERRUPT_SERVICE_ROUTINE_10);//
    RegisterInterruptHandler(SegmentNotPresent, INTERRUPT_SERVICE_ROUTINE_11);
    RegisterInterruptHandler(StackSegmentFault, INTERRUPT_SERVICE_ROUTINE_12);
    RegisterInterruptHandler(GPF, INTERRUPT_SERVICE_ROUTINE_13);
    //RegisterInterruptHandler(PageFault, INTERRUPT_SERVICE_ROUTINE_14);
    RegisterInterruptHandler(x87FloatPointError, INTERRUPT_SERVICE_ROUTINE_16);
    RegisterInterruptHandler(AlignmentCheck, INTERRUPT_SERVICE_ROUTINE_17);
    RegisterInterruptHandler(MachineCheck, INTERRUPT_SERVICE_ROUTINE_18);
    RegisterInterruptHandler(SIMDFloatPointException, INTERRUPT_SERVICE_ROUTINE_19);
    RegisterInterruptHandler(VirtualizationException, INTERRUPT_SERVICE_ROUTINE_20);
    RegisterInterruptHandler(ControlProtectionException, INTERRUPT_SERVICE_ROUTINE_21);
    RegisterInterruptHandler(SYSCALLS, 0x80);
    RegisterInterruptHandler(Clock, INTERRUPT_SERVICE_ROUTINE_32);
    RegisterInterruptHandler(CookieCheckFail, 0x29);
    RegisterInterruptHandler((void(*))getTrampolineAddress(), 0x50);

    RegisterInterruptHandler(HardwareInterruptManager, 33);
    RegisterInterruptHandler(HardwareInterruptManager, 44);

    SetUpTimers();
    DeterminCPU();

    LouPrint("Finished\n");

    return LOUSTATUS_GOOD;
}

void StorPortInitializeAllDevices();

int InitKThread();
int TestLoop2();


void InitializeDeviceManager();
LOUSTATUS LouKeMallocAdvancedKernelInterruptHandleing();

void LouKeInitializeFirmwareDeviceParseing();

void Advanced_Kernel_Initialization(){
    //if(LOUSTATUS_GOOD != InitFADT())LouPrint("Unable To Start FADT Handleing\n");
    LouKeInitializeFirmwareDeviceParseing();
    //if(LOUSTATUS_GOOD != InitSSDT())LouPrint("Unable To Start SSDT Handleing\n");
    //if(LOUSTATUS_GOOD != InitSBST())LouPrint("Unable To Start SBST Handleing\n");
    //if(LOUSTATUS_GOOD != InitSRAT())LouPrint("Unable To Start SRAT Handleing\n");
    //if(LOUSTATUS_GOOD != InitBGRT())LouPrint("Unable To Start BGRT Handleing\n");
    //if(LOUSTATUS_GOOD != InitECDT())LouPrint("Unable To Start ECDT Handleing\n");
    //if(LOUSTATUS_GOOD != InitSLIT())LouPrint("Unable To Start SLIT Handleing\n");
    //if(LOUSTATUS_GOOD != InitMCFG())LouPrint("Unable To Start MCFG Handleing\n");
    if (InitializeMainInterruptHandleing() != LOUSTATUS_GOOD)LouPrint("Unable To Start APIC System\n");
    InitializeDynamicHardwareInterruptHandleing();
    //LouKeMallocAdvancedKernelInterruptHandleing();
    //for(uint8_t i = GetTotalHardwareInterrupts() + 0x20; i < 0x50; i++){
    //    RegisterInterruptHandler(AdvancedInterruptRouter,i);
    //}


    if (LOUSTATUS_GOOD != InitThreadManager())LouPrint("SHIT!!!:I Hope You Hate Efficency: No Thread Management\n");
    LouKeSetIrql(PASSIVE_LEVEL, 0x00);
    InitializeAllProcessorFeatures();
}

bool LouMapAddress(uint64_t PAddress, uint64_t VAddress, uint64_t FLAGS, uint64_t PageSize);

void LouKeDestroyThread();

void TestFontFunction();
extern void MachineCodeDebug(uint64_t FOO);

bool DetatchWindowToKrnlDebug(PWINDHANDLE WindowSecurityCheck);

void StartDebugger(){
    
    WINDOW_CHARECTERISTICS Charecteristics;

    Charecteristics.Type = TEXT_WINDOW;
    Charecteristics.WindowName = "louoskrnl.exe";

    HWind = LouCreateWindow(
        0, 0,
        //30, 30,
        //GetScreenBufferWidth() ,GetScreenBufferHeight() ,
        1024, 768,
        0x00, 
        &Charecteristics
    );
    AttatchWindowToKrnlDebug(HWind);
    
}

void KillDebuger(){
    DetatchWindowToKrnlDebug(HWind);
    LouDestroyWindow(HWind);
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

LOUSTATUS InitilaizeUserMode(){

    LouKeLoadUserModule("C:/ANNYA/SYSTEM64/LOUDLL.DLL");
    LouKeLoadUserModule("C:/ANNYA/SYSTEM64/USER32.DLL");
    LouKeLoadUserModule("C:/ANNYA/SYSTEM64/CRT140.DLL");
    
    return STATUS_SUCCESS;
}

void UsrJmp(uint64_t Entry);

bool LouMapAddressEx(uint64_t PAddress, uint64_t VAddress, uint64_t FLAGS, bool LargePage);

void SYSCALLS(uint64_t Call, uint64_t Data, uint64_t SystemEmulation);

void PrintTest(){
    while(1){
        LouPrint("FOO ");
    }
}

void SetContext(uint64_t Context, uint64_t Function);


typedef struct  __attribute__((packed)) _CPUContext{

    uint64_t rip;       // Instruction Pointer (user-mode entry point)
    uint64_t cs;        // Code Segment (should be set to user mode, typically 0x1B for x86_64)
    uint64_t rflags;    // Flags Register (set the interrupt flag, clear privileged bits)
    
    uint64_t rsp;       // Stack Pointer (points to user-mode stack)
    uint64_t ss;        // Stack Segment (should be user mode, typically 0x23 for x86_64)

} CPUContext;


void SMPInit();
void InitializeUserSpace();

void LouKeRunOnNewUserStack(void (*func)(void*), void* FunctionParameters, size_t Pages);
void CheckForPs2Mouse();
void InitializeInternalChipsetHostDriver();
uint8_t LouKeGetNumberOfStorageDevices();

static bool SystemIsEfi = false;
KERNEL_ENTRY Lou_kernel_start(
    uint32_t MBOOT
){
    struct multiboot_tag* mboot = (struct multiboot_tag*)(uintptr_t)(MBOOT + 8);

    ParseMBootTags(mboot);
    //vga set for debug
    if(!LouKeMapEfiMemory()){
        LouKeHandleSystemIsBios();
    }else {
        SystemIsEfi = true;
    }

    LouKeMapPciMemory();

    SetupInitialVideoDevices();

    //INITIALIZE IMPORTANT THINGS FOR US LATER
    Lou_kernel_early_initialization();

    InitializeGenericTables();

	LouPrint("Lousine Kernel Version %s %s\n", KERNEL_VERSION ,KERNEL_ARCH);
    LouPrint("Hello Im Lousine Getting Things Ready\n");
        
    Advanced_Kernel_Initialization();


    InitializeInternalChipsetHostDriver();

    //SETUP DEVICES AND DRIVERS
    LookForStorageDevices();

    uint8_t StorageDevices = LouKeGetNumberOfStorageDevices();
    if(!StorageDevices){
        LouPrint("No Storage Devices Detected\n");
        while(1);
    }

    FileSystemSetup();
    ScanTheRestOfHarware();

    //SMPInit();
    LouPrint("Initializing User Mode\n");
    LouKeRunOnNewUserStack(InitializeUserSpace,0x00, 512);

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

void InitializeUserSpace(){

    InitilaizeUserMode();
    uint64_t InitEntry = (uint64_t)LouKeLoadPeExecutable("C:/ANNYA/ANNYAEXP.EXE");

    LouPrint("Lousine Kernel Video Mode:%dx%d\n", GetScreenBufferWidth(), GetScreenBufferHeight());
    LouPrint("System Memory:%d MEGABYTES Usable\n", (GetRamSize() / (1024 * 1024)));

    LouUpdateWindow(
        GetScreenBufferWidth() / 2, GetScreenBufferHeight() / 2,
        GetScreenBufferWidth() / 2, (GetScreenBufferHeight() / 2) - 62,
        HWind
    );
    
    LouPrint("Hello World\n");
    UsrJmp(InitEntry);
}

//Intel Corporation	8086	Skylake GT2 [HD Graphics 520]	1916


/*	
AMD PCNet-PCI II	Easy Am79C970A	
USB 1.1 (UHCI / OHCI)	Moderate	Fits here (simpler linked list design).
PCI Sound Cards	Moderate	
Intel 8254x NIC	Moderate	
USB 2.0 (EHCI)	Moderate-to-Hard	Fits here (periodic/asynchronous queues).
PCI Storage (AHCI)	Hard	
USB 3.0+ (xHCI)	Harder	Fits here (TRBs, ring buffers).
PCI Storage (NVMe)	Harder	
GPUs	Hardest	
PCIe FPGA Cards	Hardest	
High-Performance NICs	Hardest
*/