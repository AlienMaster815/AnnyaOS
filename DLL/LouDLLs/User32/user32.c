#include "user32.h"

ANNA_IMPORT PUSER_PROCESS_HEAP LouDllGlobalHeap;
ANNA_IMPORT PUSER_PROCESS_HEAP LouDllHeap;

typedef struct _WINDOW_CLASS_TRACKER{
    ListHeader              Peers;
    RTL_ATOM                Atom;               
    WINDOW_CLASS_EX_W       ClassExW;
}WINDOW_CLASS_TRACKER, * PWINDOW_CLASS_TRACKER;


static mutex_t      ClassesLock;
static ListHeader   LocalClasses;


USER32_API
ATOM RegisterClassExW(
    const WINDOW_CLASS_EX_W* NewClass
){  
    if(!NewClass->ClassName){
        return 0x00;
    }
    LOUSTATUS Status;
    PWINDOW_CLASS_TRACKER NewTracker;
    RTL_ATOM Atom = 0x00;
    BOOLEAN GlobalClass = (NewClass->Style & WINDOW_CS_GLOBAL_CLASS) ? true : false;
    LPWSTR ClassName = 0x00;
    LPWSTR MenuName = 0x00;
    MutexLock(&ClassesLock);    
    if(GlobalClass){
        PVOID Out = 0;
        Status = LouGetGlobalObject(NewClass->ClassName, &Out);
        if(Status == STATUS_SUCCESS){
            NewTracker = (PWINDOW_CLASS_TRACKER)Out;
            MutexUnlock(&ClassesLock);    
            return NewTracker->Atom;
        }
        NewTracker = LouRtlAllocateHeapEx(LouDllGlobalHeap, sizeof(WINDOW_CLASS_TRACKER) + NewClass->ExtraClassDataSize, GET_ALIGNMENT(WINDOW_CLASS_TRACKER), USER_HEAP_FLAG_ZERO_MEMORY);
        ClassName = LouRtlAllocateHeapArray(LouDllGlobalHeap, WCHAR, wcslen(NewClass->ClassName) + 1);
        wcscpy(ClassName, NewClass->ClassName);
        if(NewClass->MenuName){
            MenuName = LouRtlAllocateHeapArray(LouDllGlobalHeap, WCHAR, wcslen(NewClass->MenuName) + 1);
            wcscpy(MenuName, NewClass->MenuName);
        }
        Status = LouRegisterGlobalObject(NewClass->ClassName, NewTracker);
        if(Status != STATUS_SUCCESS){
            LouRtlFreeHeap(LouDllGlobalHeap, ClassName, 0);
            if(MenuName){
                LouRtlFreeHeap(LouDllGlobalHeap, MenuName, 0);
            }
            LouRtlFreeHeap(LouDllGlobalHeap, NewTracker, 0);
            MutexUnlock(&ClassesLock);    
            LouPrint("USER32.DLL:RegisterClassExW()ERROR Unable To Register Global Class\n"); 
            return 0x00;
        }
        Status = LouAddAtom(NewClass->ClassName, wcslen(NewClass->ClassName), &Atom); //Acquire the global objects atom id
        if(Status != STATUS_SUCCESS){
            LouUnRegisterGlobalObject(NewClass->ClassName);
            LouRtlFreeHeap(LouDllGlobalHeap, ClassName, 0);
            if(MenuName){
                LouRtlFreeHeap(LouDllGlobalHeap, MenuName, 0);
            }
            LouRtlFreeHeap(LouDllGlobalHeap, NewTracker, 0);
            MutexUnlock(&ClassesLock);   
            LouPrint("USER32.DLL:RegisterClassExW()ERROR Unable To Get Atom Reference For Global Class\n"); 
            return 0x00;
        }
        LouDeleteAtom(Atom); //Release global object atom reference
    }else{
        ForEachListEntry(NewTracker, &LocalClasses, Peers){
            if(!wcscmp(NewTracker->ClassExW.ClassName, NewClass->ClassName)){
                MutexUnlock(&ClassesLock);    
                return NewTracker->Atom;
            }
        }
        Status = LouAddAtomEx(NewClass->ClassName, wcslen(NewClass->ClassName), &Atom, ADD_ATOM_FLAG_LOCAL); //allocate a private atom
        if(Status != STATUS_SUCCESS){
            LouPrint("USER32.DLL:RegisterClassExW()ERROR Unable To Create Atom For Local Class\n"); 
            MutexUnlock(&ClassesLock);    
            return 0x00;
        }
        NewTracker = LouRtlAllocateHeapEx(LouDllHeap, sizeof(WINDOW_CLASS_TRACKER) + NewClass->ExtraClassDataSize, GET_ALIGNMENT(WINDOW_CLASS_TRACKER), USER_HEAP_FLAG_ZERO_MEMORY);
        ClassName = LouRtlAllocateHeapArray(LouDllHeap, WCHAR, wcslen(NewClass->ClassName) + 1);
        wcscpy(ClassName, NewClass->ClassName);
        if(NewClass->MenuName){
            MenuName = LouRtlAllocateHeapArray(LouDllHeap, WCHAR, wcslen(NewClass->MenuName) + 1);
            wcscpy(MenuName, NewClass->MenuName);
        }
        LouKeListAddTail(&NewTracker->Peers, &LocalClasses);
    }

    LouMemCpy(&NewTracker->ClassExW, (PVOID)NewClass, sizeof(WINDOW_CLASS_EX_W));
    if(!NewTracker->ClassExW.Size){
        NewTracker->ClassExW.Size = sizeof(WINDOW_CLASS_EX_W);
    }
    NewTracker->ClassExW.ClassName = ClassName;
    NewTracker->ClassExW.MenuName = MenuName;
    NewTracker->Atom = Atom;
    MutexUnlock(&ClassesLock);    
    return Atom;
}

USER32_API
BOOL 
DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved){

    if(ul_reason_for_call == DLL_PROCESS_ATTACH){
        LouPrint("USER32.DLL:Attatched To New Process\n");    
    }

    return TRUE;
}