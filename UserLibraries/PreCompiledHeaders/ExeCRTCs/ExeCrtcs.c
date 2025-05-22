#include <Annya.h>

extern int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
extern int WndProc(void* hwnd, uint32_t uMsg, void* WParam, void* LParam);

static inline void TailLouCall(
    uint64_t Call,
    uint64_t Data,
    uint64_t SystemEmulation
){
    asm("INT $0x80");
}

static mutex_t LouCallLock;

void LouCALLcrtc(
    uint64_t Call,
    uint64_t Data,
    uint64_t SystemEmulation
){
    MutexLock(&LouCallLock);
    TailLouCall(Call, Data, SystemEmulation);
    MutexUnlock(&LouCallLock);
}

uint64_t AnnyaRegisterCallbackProcedure(
    void* CallbackHandler
){
    uint64_t Data[2];
    Data[0] = 0;
    Data[1] = (uint64_t)CallbackHandler; 
    while(Data[0] != 1){
        LouCALLcrtc(LOUREGISTERCALLBACK, (uint64_t)&Data, 0);
    }
    return Data[1];
}


int __WinMainCrtc(
    uint64_t hInstance,
    uint64_t hPrev, 
    uint64_t CommandLine, 
    uint64_t CmdShow
){

    AnnyaRegisterCallbackProcedure(
        (void*)WndProc
    );

    return WinMain(
        (HINSTANCE)hInstance,
        (HINSTANCE)hPrev,
        (LPSTR)CommandLine,
        (int)CmdShow
    );
}

BOOL DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    uint64_t a, b, c, d;
    asm volatile (
        "movq %%rcx, %0\n\t"
        "movq %%rdx, %1\n\t"
        "movq %%r8, %2\n\t"
        "movq %%r9, %3\n\t"
        : "=r"(a), "=r"(b), "=r"(c), "=r"(d) // Outputs
        :                                    // Inputs
        : "rcx", "rdx", "r8", "r9"           // Clobbered registers
    );
    
    a = __WinMainCrtc(a,b,c,d);
    
    asm volatile (
        "movq %0, %%rax\n\t"
        :
        : "r"(a)  // Corrected Input
        : "rax"   // Mark `rax` as clobbered
    );
}