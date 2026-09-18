#ifndef _LOUDLL_
#define _LOUDLL_

#include <Annya.h>

#define LOUDLL_API __declspec(dllexport)

LOUDLL_API
BOOL DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    /*BOOL Tmp = true;
    if(ul_reason_for_call == DLL_PROCESS_ATTACH){
        FsiLevel = LouGetFSI();
        if(LouInitializeIoCtlTable(LouDllIoCalls) != STATUS_SUCCESS){
            LouPrint("LOUDLL.DLL Failed To Register IOCTLs\n");
        }
        LouDllHeap = LouRtlCreateHeap(
            USER_HEAP_FLAG_GROWABLE,
            0x00, 
            0x00,
            0x00,
            0x00,
            0x00
        );
        //NOTICE: this will fail for the session manager startup 
        //the error should be ignored because the session manager
        //creates the global heap and sets the session managers
        //value personaly this logic is for non session manager 
        //processes 
        PVOID GlobalHeap = 0;
        LouGetGlobalObject(L"LouDllGlobalHeap", &GlobalHeap);
        LouDllGlobalHeap = (PUSER_PROCESS_HEAP)GlobalHeap;
        //LouPrint("LouDllGlobalHeap:%h\n", LouDllGlobalHeap);
        LouPrint("LOUDLL.DLL:Attatched To New Process\n");
    }
    
    //Tmp = NtDllMainCRTStartup(hModule, ul_reason_for_call, lpReserved);
    if(!Tmp){
        return Tmp;
    }*/
    return TRUE;    
}

#endif