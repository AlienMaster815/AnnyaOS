//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include "asmss.h"

/*__declspec(dllimport)
LOUSTATUS 
LouCreateSectionEx(
    PHANDLE                 OutSectionHandle,
    ACCESS_MASK             DesiredAccess,
    POBJECT_ATTRIBUTES      ObjectAttributes,
    PLARGE_INTEGER          MaximumSize,
    ULONG                   SectionPageProtection,
    ULONG                   AllocationAttributes,
    HANDLE                  FileHandle,
    PMEM_EXTENDED_PARAMETER ExtendedParameters,
    ULONG                   ExtendedParameterCount
);*/

static HANDLE SessionManagerProcessHandle = 0x00;

LOUSTATUS AnnyaSmssIpcClallback(UINT64 MessageID, PVOID DataIn, SIZE DataInSize);

LOUSTATUS AnnyaSmssProcessStartup(HANDLE Peb){

    LouPrint("ASMSS: Hello User Mode\n");
    LOUSTATUS Status;
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


LOUSTATUS AnnyaSmssIpcClallback(UINT64 MessageID, PVOID DataIn, SIZE DataInSize){



    return STATUS_SUCCESS;
}