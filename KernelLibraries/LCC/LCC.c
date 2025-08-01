
//#include <LouAPI.h>
#include <stdint.h>
#include <stdbool.h>

typedef void* PDRIVER_OBJECT;
typedef void* PUNICODE_STRING;
typedef bool BOOL;
typedef void* HMODULE;
typedef void* LPVOID;
typedef uint32_t DWORD;
typedef uint64_t LOUSTATUS;

//__declspec(dllimport) int LouPrint(char* format, ...);

BOOL DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    //uint64_t a, b; //, c, d;
    
    //asm volatile (
    //    "movq %%rcx, %0\n\t"
    //    "movq %%rdx, %1\n\t"
    //    : "=r"(a), "=r"(b)  // Outputs
    //    :                   // Inputs
    //    : "rcx", "rdx", "r8", "r9" // Clobbered registers
    //);


    //asm volatile (
    //    "movq %0, %%rax\n\t"
    //    :
    //    : "r"(a)  // Corrected Input
    //    : "rax"   // Mark `rax` as clobbered
    //);
}

//void LouKeVmDebuggerPrintHex(uint64_t HexValue){
//    LouPrint("LouKeVmDebuggerPrintHex:%h\n", HexValue);
//}