
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

extern LOUSTATUS DriverEntry(PDRIVER_OBJECT DrvObj, PUNICODE_STRING RegistryEntry);

LOUSTATUS _DriverEntry(PDRIVER_OBJECT _DrvObj, PUNICODE_STRING _RegistryEntry){
    return DriverEntry(_DrvObj, _RegistryEntry);
}

BOOL DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    uint64_t a, b; //, c, d;
    
    asm volatile (
        "movq %%rcx, %0\n\t"
        "movq %%rdx, %1\n\t"
        : "=r"(a), "=r"(b)  // Outputs
        :                   // Inputs
        : "rcx", "rdx", "r8", "r9" // Clobbered registers
    );

    a = _DriverEntry((PDRIVER_OBJECT)(uintptr_t)a, (PUNICODE_STRING)(uintptr_t)b);

    asm volatile (
        "movq %0, %%rax\n\t"
        :
        : "r"(a)  // Corrected Input
        : "rax"   // Mark `rax` as clobbered
    );
}
