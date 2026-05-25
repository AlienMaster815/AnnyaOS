#include "user32.h"


//static ListHeader WindowClasses = {0};

USER32_API
ATOM RegisterClassExW(
    const WINDOW_CLASS_EX_W* NewClass
){  
    if(!NewClass->ClassName){
        return 0x00;
    }
    //PLOU_IPC_MESSAGE Message;
    //LOUSTATUS Status = LouIpcCreateIpcMessage(    
    //    &Message,
    //    AWM_IPC_MSGID_REGISTER_CLASS_EX_W, 
    //    (PVOID)NewClass,
    //    sizeof(WINDOW_CLASS_EX_W)
    //);
    //if(Status != STATUS_SUCCESS){
    //    return 0;
    //}

    //Status = LouIpcSendIpcMessage(ASMSS_PROCESS_NAME_UNICODE, Message);
    //if(Status != STATUS_SUCCESS){
    //    return Status;
    //}

    //LouIpcDestroyIpcMessage(Message);

    LouPrint("USER32.DLL:RegisterClassExW()\n");
    //while(1);
    return 0x00;
}

USER32_API
BOOL 
DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved){

    if(ul_reason_for_call == DLL_PROCESS_ATTACH){
        LouPrint("USER32.DLL:Attatched To New Process\n");    
    }

    return TRUE;
}