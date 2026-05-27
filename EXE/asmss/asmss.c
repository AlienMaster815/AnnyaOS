//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include "asmss.h"

ANNA_IMPORT PUSER_PROCESS_HEAP LouDllHeap;
ANNA_IMPORT PUSER_PROCESS_HEAP LouDllGlobalHeap;

static HANDLE SessionManagerProcessHandle = 0x00;

LOUSTATUS AnnyaSmssIpcClallback(PVOID Message, UINT64 MessageID);

LOUSTATUS AnnyaSmssProcessStartup(HANDLE Peb){

    LouPrint("ASMSS: Hello User Mode\n");
    
    LouDllGlobalHeap = LouRtlCreateSharedHeap(
        USER_HEAP_FLAG_GROWABLE,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00
    );

    //LouPrint("LouDllGlobalHeap:%h\n", LouDllGlobalHeap);

    LOUSTATUS Status = LouRegisterGlobalObject(L"LouDllGlobalHeap", (PVOID)LouDllGlobalHeap);
    if(Status != STATUS_SUCCESS){
        LouPrint("ASMSS.EXE:ERROR Unable To Register Global Heap\n");
        return Status;
    }

    Status = LouGetCurrentProccessHandle(
        &SessionManagerProcessHandle,
        ACCESS_MASK_GENERIC_ALL
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    Status = LouCreateIpcManagerForProcess(AnnyaSmssIpcClallback);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    //LouExitDosMode();

    //HPROCESS WindowManager;

    LouCreateProcessA(
        AWM_PROCESS_NAME,
        "C:/ANNYA/SYSTEM64/AWM.EXE",
        0x00,
        ACCESS_MASK_GENERIC_ALL,
        PROCESS_PRIORITY_HIGH,
        0x00
    );

    LouCreateProcessA(
        EXPLORER_PROCESS_NAME,
        "C:/ANNYA/EXPLORER.EXE",
        0x00,
        ACCESS_MASK_GENERIC_ALL,
        PROCESS_PRIORITY_NORMAL,
        0x00
    );

    //TODO: Check object manager to make sure its safe to continue
    LouPrint("Session Manager Successfully Initialized\n");    
    PLOU_IPC_MESSAGE Message;
    while(1){
        LouIpcGetIpcMessage(&Message, true);
        LouIpcProcessIpcMessage(Message);
    }
}


LOUSTATUS AnnyaSmssIpcClallback(PVOID Message, UINT64 MessageID){

    switch(MessageID){

        default:
            break;
    }


    LouPrint("ASMSS.EXE:AnnyaSmssIpcClallback():%d\n", MessageID);
    while(1);

    return STATUS_SUCCESS;
}