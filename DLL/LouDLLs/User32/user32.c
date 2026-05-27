#include "user32.h"

ANNA_IMPORT PUSER_PROCESS_HEAP LouDllGlobalHeap;

USER32_API
ATOM RegisterClassExW(
    const WINDOW_CLASS_EX_W* NewClass
){  
    if(!NewClass->ClassName){
        return 0x00;
    }
    //PLOU_IPC_MESSAGE Message = 0;
    PREGISTER_CLASS_EX_W_MESSAGE_DATA NewClassMessageData = LouRtlAllocateHeapEx(LouDllGlobalHeap, sizeof(REGISTER_CLASS_EX_W_MESSAGE_DATA), GET_ALIGNMENT(REGISTER_CLASS_EX_W_MESSAGE_DATA), USER_HEAP_FLAG_ZERO_MEMORY);
    NewClassMessageData->Done = false;
    NewClassMessageData->OutAtom = 0x00;
    NewClassMessageData->WindowClass = LouRtlAllocateHeapEx(LouDllGlobalHeap, sizeof(WINDOW_CLASS_EX_W) + NewClass->ExtraClassDataSize + NewClass->ExtraWindowDataSize, GET_ALIGNMENT(WINDOW_CLASS_EX_W), USER_HEAP_FLAG_ZERO_MEMORY);
    LouMemCpy(NewClassMessageData->WindowClass, (PVOID)NewClass, sizeof(WINDOW_CLASS_EX_W) + NewClass->ExtraClassDataSize + NewClass->ExtraWindowDataSize);
    NewClassMessageData->WindowClass->Size = sizeof(WINDOW_CLASS_EX_W) + NewClass->ExtraClassDataSize + NewClass->ExtraWindowDataSize;

    //LOUSTATUS Status = LouIpcCreateIpcMessage(    
    //    &Message,
    //    AWM_IPC_MSGID_REGISTER_CLASS_EX_W, 
    //    (PVOID)NewClassMessageData,
    //    sizeof(REGISTER_CLASS_EX_W_MESSAGE_DATA)
    //);
    //if(Status != STATUS_SUCCESS){
    //    return 0;
    //}

    //Status = LouIpcSendIpcMessage(ASMSS_PROCESS_NAME_UNICODE, Message);
    //if(Status != STATUS_SUCCESS){
    //    return Status;
    //}

    //while(!NewClassMessageData->Done && Status == STATUS_SUCCESS){
    //    Status = LouIpcGetIpcMessageData(
    //        Message,
    //        (PVOID)NewClassMessageData,
    //        sizeof(REGISTER_CLASS_EX_W_MESSAGE_DATA)
    //    );
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