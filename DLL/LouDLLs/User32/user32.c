#include "user32.h"


USER32_API
BOOL 
DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved){

    if(ul_reason_for_call == DLL_PROCESS_ATTACH){
        LouPrint("USER32.DLL:Attatched To New Process\n");    
    }

    return TRUE;
}