#include "kernelbase.h"

KERNELBASE_API
BOOL DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}

