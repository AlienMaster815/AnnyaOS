#include "user32.h"

ANNA_IMPORT PUSER_PROCESS_HEAP LouDllGlobalHeap;
ANNA_IMPORT PUSER_PROCESS_HEAP LouDllHeap;

typedef struct _WINDOW_CLASS_TRACKER{
    ListHeader              Peers;
    RTL_ATOM                Atom;
    KERNEL_REFERENCE        ClassReferences;
    KERNEL_REFERENCE        ActiveWindows;           
    WINDOW_CLASS_EX_W       ClassExW;
}WINDOW_CLASS_TRACKER, * PWINDOW_CLASS_TRACKER;

typedef struct _GLOBAL_WINDOW_CLASS_TRACKER{
    ListHeader              Peers;
    PWINDOW_CLASS_TRACKER   GlobalClass;
}GLOBAL_WINDOW_CLASS_TRACKER, * PGLOBAL_WINDOW_CLASS_TRACKER;

static mutex_t      ClassesLock;
static ListHeader   LocalClasses;
static ListHeader   GlobalClassReferences;

static 
void
WindClassWToWindClassExW(
    PWINDOW_CLASS_EX_W  NewClass,
    PWINDOW_CLASS_W     OldClass
){
    //NOTICE:ClassEx Functions handle missing Values Gracefully
    //so ignore the class size and small icon
    NewClass->Style = OldClass->Style;
    NewClass->WindowProcedure = OldClass->WindowProcedure;
    NewClass->ExtraClassDataSize = OldClass->ExtraClassDataSize;
    NewClass->ExtraWindowDataSize = OldClass->ExtraWindowDataSize;
    NewClass->WndProcInstance = OldClass->WndProcInstance;
    NewClass->ClassIcon = OldClass->ClassIcon;
    NewClass->ClassCursor = OldClass->ClassCursor;
    NewClass->BackgroundBrush = OldClass->BackgroundBrush;
    NewClass->MenuName = OldClass->MenuName;
    NewClass->ClassName = OldClass->ClassName; 
}

static 
void
WindClassExAToWindClassExW(
    PWINDOW_CLASS_EX_W  NewClass,
    PWINDOW_CLASS_EX_A  OldClass,
    LPWSTR              WideClassName,
    LPWSTR              WideMenuName
){
    //NOTICE:ClassEx Functions handle missing Values Gracefully
    //so ignore the class size and small icon
    NewClass->Style = OldClass->Style;
    NewClass->WindowProcedure = OldClass->WindowProcedure;
    NewClass->ExtraClassDataSize = OldClass->ExtraClassDataSize;
    NewClass->ExtraWindowDataSize = OldClass->ExtraWindowDataSize;
    NewClass->WndProcInstance = OldClass->WndProcInstance;
    NewClass->ClassIcon = OldClass->ClassIcon;
    NewClass->ClassCursor = OldClass->ClassCursor;
    NewClass->BackgroundBrush = OldClass->BackgroundBrush;
    NewClass->MenuName = WideMenuName;
    NewClass->ClassName = WideClassName;
    NewClass->SmallClassIcon = OldClass->SmallClassIcon; 
}

static 
void
WindClassAToWindClassExA(
    PWINDOW_CLASS_EX_A  NewClass,
    PWINDOW_CLASS_A     OldClass
){
    //NOTICE:ClassEx Functions handle missing Values Gracefully
    //so ignore the class size and small icon
    NewClass->Style = OldClass->Style;
    NewClass->WindowProcedure = OldClass->WindowProcedure;
    NewClass->ExtraClassDataSize = OldClass->ExtraClassDataSize;
    NewClass->ExtraWindowDataSize = OldClass->ExtraWindowDataSize;
    NewClass->WndProcInstance = OldClass->WndProcInstance;
    NewClass->ClassIcon = OldClass->ClassIcon;
    NewClass->ClassCursor = OldClass->ClassCursor;
    NewClass->BackgroundBrush = OldClass->BackgroundBrush;
    NewClass->MenuName = OldClass->MenuName;
    NewClass->ClassName = OldClass->ClassName;
}

static LOUSTATUS GetGlobalClass(
    LPWSTR                          ClassName,
    PWINDOW_CLASS_TRACKER*          Tracker,
    RTL_ATOM                        InAtom, 
    PRTL_ATOM                       OutAtom
){
    if(!Tracker){
        return STATUS_INVALID_PARAMETER;
    }
    //check the kernel for global items the kernel
    //does not use shared local items and has unique
    //per process local atoms for safety reasone any 
    //shared objects need to get and store as
    //global object
    PVOID Out = 0;
    LOUSTATUS Status;
    if(InAtom){
        Status = LouGetGlobalObjectFromAtom(InAtom, &Out);
    }else{
        Status = LouGetGlobalObject(ClassName, &Out);
    }
    if(Status == STATUS_SUCCESS){
        *Tracker = (PWINDOW_CLASS_TRACKER)Out;
        LouKeAcquireReference(&(*Tracker)->ClassReferences);
        if(OutAtom){
            *OutAtom  = (*Tracker)->Atom;
        }
        return STATUS_SUCCESS;
    }
    return STATUS_UNSUCCESSFUL;
}

static LOUSTATUS FreeGlobalClass(
    PWINDOW_CLASS_TRACKER Tracker
){
    if(!Tracker){
        return STATUS_INVALID_PARAMETER;
    }
    LouKeReleaseReference(&Tracker->ClassReferences);
    if(!LouKeGetReferenceCount(&Tracker->ClassReferences)){
        LouUnRegisterGlobalObject(Tracker->ClassExW.ClassName);
        if((UINTPTR)Tracker->ClassExW.MenuName > UINT16_MAX){
            LouRtlFreeHeap(LouDllGlobalHeap, Tracker->ClassExW.MenuName, 0);
        }
        LouRtlFreeHeap(LouDllGlobalHeap, Tracker->ClassExW.ClassName, 0);
        LouRtlFreeHeap(LouDllGlobalHeap, Tracker, 0);
        return STATUS_SUCCESS;
    }
    return STATUS_UNSUCCESSFUL;
}

static LOUSTATUS AllocateGlobalClass(
    LPWSTR                  ClassName,
    PWINDOW_CLASS_TRACKER*  Tracker,
    PRTL_ATOM               OutAtom,
    SIZE                    ClassExtraData,
    LPWSTR                  MenuName
){
    if(!ClassName || !Tracker){
        return STATUS_INVALID_PARAMETER;
    }
    LOUSTATUS Status = GetGlobalClass(ClassName, Tracker, 0x00, OutAtom);
    if(Status == STATUS_SUCCESS){
        FreeGlobalClass(*Tracker);
        return STATUS_DUPLICATE_NAME;
    }
    BOOLEAN MenuNameIsAtom = ((UINTPTR)MenuName <= UINT16_MAX) ? true : false;

    SIZE MenuNameLength = 0x00; 
    SIZE ClassNameLength = wcslen(ClassName);
    *Tracker = LouRtlAllocateHeapEx(LouDllGlobalHeap, sizeof(WINDOW_CLASS_TRACKER) + ClassExtraData, GET_ALIGNMENT(WINDOW_CLASS_TRACKER), USER_HEAP_FLAG_ZERO_MEMORY);
    
    if(!MenuNameIsAtom && MenuName){
        MenuNameLength = wcslen(MenuName);
    } 
    
    PWINDOW_CLASS_EX_W NewClass = &(*Tracker)->ClassExW;
    NewClass->ClassName = LouRtlAllocateHeapArray(LouDllGlobalHeap, WCHAR, ClassNameLength + 1);    
    wcscpy(NewClass->ClassName, ClassName);

    if(MenuNameIsAtom){
        NewClass->MenuName = (LPWSTR)MenuName;
    }else if(MenuName){
        NewClass->MenuName = LouRtlAllocateHeapArray(LouDllGlobalHeap, WCHAR, MenuNameLength + 1);
        wcscpy(NewClass->MenuName, MenuName);
    }

    LouKeAcquireReference(&(*Tracker)->ClassReferences);
    Status = LouRegisterGlobalObjectEx(ClassName, *Tracker, OutAtom);
    if(Status != STATUS_SUCCESS){
        if(!MenuNameIsAtom){
            LouRtlFreeHeap(LouDllGlobalHeap, NewClass->MenuName, 0);
        }
        LouRtlFreeHeap(LouDllGlobalHeap, NewClass->ClassName, 0);
        LouRtlFreeHeap(LouDllGlobalHeap, *Tracker, 0);
        return Status;
    }
    return STATUS_SUCCESS;
}

static LOUSTATUS GetLocalClass(
    LPWSTR                          ClassName,
    PWINDOW_CLASS_TRACKER*          Tracker,
    RTL_ATOM                        InAtom, 
    PRTL_ATOM                       OutAtom
){
    if(!Tracker){
        return STATUS_INVALID_PARAMETER;
    }
    PWINDOW_CLASS_TRACKER TmpTracker;
    BOOLEAN Found = false;
    ForEachListEntry(TmpTracker, &LocalClasses, Peers){
        if(ClassName){
            if(!wcscmp(TmpTracker->ClassExW.ClassName, ClassName)){
                Found = true;
                break;
            }
        }
        else if(InAtom && (TmpTracker->Atom == InAtom)){
            Found = true;
            break;
        }
    }
    if(Found){
        LouKeAcquireReference(&TmpTracker->ClassReferences);
        *Tracker = TmpTracker;
        if(OutAtom){
            *OutAtom = TmpTracker->Atom;
        }
        return STATUS_SUCCESS;
    }
    return STATUS_UNSUCCESSFUL;
}

static LOUSTATUS FreeLocalClass(
    PWINDOW_CLASS_TRACKER Tracker
){
    if(!Tracker){
        return STATUS_INVALID_PARAMETER;
    }
    LouKeReleaseReference(&Tracker->ClassReferences);
    if(!LouKeGetReferenceCount(&Tracker->ClassReferences)){
        LouKeListDeleteItem(&Tracker->Peers);
        if((UINTPTR)Tracker->ClassExW.MenuName > UINT16_MAX){
            LouRtlFreeHeap(LouDllHeap, Tracker->ClassExW.MenuName, 0);
        }
        LouRtlFreeHeap(LouDllHeap, Tracker->ClassExW.ClassName, 0);
        LouRtlFreeHeap(LouDllHeap, Tracker, 0);
        return STATUS_SUCCESS;
    }
    return STATUS_UNSUCCESSFUL;
}

static LOUSTATUS AllocateLocalClass(
    LPWSTR                  ClassName,
    PWINDOW_CLASS_TRACKER*  Tracker,
    PRTL_ATOM               OutAtom,
    SIZE                    ClassExtraData,
    LPWSTR                  MenuName
){
    if(!ClassName || !Tracker){
        return STATUS_INVALID_PARAMETER;
    }
    LOUSTATUS Status = GetLocalClass(ClassName, Tracker, 0x00, OutAtom);
    if(Status == STATUS_SUCCESS){
        FreeLocalClass(*Tracker);
        return STATUS_DUPLICATE_NAME;
    }
    BOOLEAN MenuNameIsAtom = ((UINTPTR)MenuName <= UINT16_MAX) ? true : false;

    SIZE MenuNameLength = 0x00; 
    SIZE ClassNameLength = wcslen(ClassName);
    if(OutAtom){
        Status = LouAddAtomEx(ClassName, ClassNameLength, OutAtom , ADD_ATOM_FLAG_LOCAL);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
    }
    
    *Tracker = LouRtlAllocateHeapEx(LouDllHeap, sizeof(WINDOW_CLASS_TRACKER) + ClassExtraData, GET_ALIGNMENT(WINDOW_CLASS_TRACKER), USER_HEAP_FLAG_ZERO_MEMORY);
    
    if(!MenuNameIsAtom && MenuName){
        MenuNameLength = wcslen(MenuName);
    } 

    PWINDOW_CLASS_EX_W NewClass = &(*Tracker)->ClassExW;
    NewClass->ClassName = LouRtlAllocateHeapArray(LouDllHeap, WCHAR, ClassNameLength + 1);    
    wcscpy(NewClass->ClassName, ClassName);

    if(MenuNameIsAtom){
        NewClass->MenuName = (LPWSTR)MenuName;
    }else if(MenuName){
        NewClass->MenuName = LouRtlAllocateHeapArray(LouDllHeap, WCHAR, MenuNameLength + 1);
        wcscpy(NewClass->MenuName, MenuName);
    }

    LouKeAcquireReference(&(*Tracker)->ClassReferences);
    LouKeListAddTail(&(*Tracker)->Peers, &LocalClasses);
    return STATUS_SUCCESS;
}

USER32_API
ATOM RegisterClassExW(
    const WINDOW_CLASS_EX_W* NewClass
){  
    //TODO if new class instance is null check afinity
    if(!NewClass->ClassName){
        return 0x00;
    }
    LOUSTATUS Status;
    PWINDOW_CLASS_TRACKER NewTracker;
    PGLOBAL_WINDOW_CLASS_TRACKER TmpGlobalTracker;
    RTL_ATOM Atom = 0x00;
    BOOLEAN GlobalClass = (NewClass->Style & WINDOW_CS_GLOBAL_CLASS) ? true : false;
    LPWSTR ClassName = 0x00;
    LPWSTR MenuName = 0x00;
    MutexLock(&ClassesLock);

    if(GlobalClass){
        Status = AllocateGlobalClass(
            NewClass->ClassName,
            &NewTracker,
            &Atom,
            NewClass->ExtraClassDataSize,
            NewClass->MenuName
        );
        if(Status == STATUS_INVALID_PARAMETER){
            MutexUnlock(&ClassesLock);    
            LouPrint("USER32.DLL:RegisterClassExW() Unable To Create Global Class EINVAL\n");
            return 0x00;
        }
        else if(Status != STATUS_SUCCESS){
            MutexUnlock(&ClassesLock);    
            LouPrint("USER32.DLL:RegisterClassExW() Unable To Create Global Class Allocation Error\n");
            return 0x00;
        }
    }else{
        Status = AllocateLocalClass(
            NewClass->ClassName,
            &NewTracker,
            &Atom,
            NewClass->ExtraClassDataSize,
            NewClass->MenuName
        );
        if(Status == STATUS_INVALID_PARAMETER){
            MutexUnlock(&ClassesLock);    
            LouPrint("USER32.DLL:RegisterClassExW() Unable To Create Local Class EINVAL\n");
            return 0x00;
        }
        else if(Status != STATUS_SUCCESS){
            MutexUnlock(&ClassesLock);    
            LouPrint("USER32.DLL:RegisterClassExW() Unable To Create Local Class Allocation Error\n");
            return 0x00;
        }
    }
    NewTracker->ClassExW.Style = NewClass->Style;
    NewTracker->ClassExW.WindowProcedure = NewClass->WindowProcedure;
    NewTracker->ClassExW.ExtraClassDataSize = NewClass->ExtraClassDataSize;
    NewTracker->ClassExW.ExtraWindowDataSize = NewClass->ExtraWindowDataSize;
    NewTracker->ClassExW.WndProcInstance = NewClass->WndProcInstance;
    NewTracker->ClassExW.ClassIcon = NewClass->ClassIcon;
    NewTracker->ClassExW.ClassCursor = NewClass->ClassCursor;
    NewTracker->ClassExW.BackgroundBrush = NewClass->BackgroundBrush;
    NewTracker->Atom = Atom;
    MutexUnlock(&ClassesLock);    
    return Atom;
}

USER32_API
ATOM RegisterClassW(
    const WINDOW_CLASS_W* NewClass
){
    if(!NewClass->ClassName){
        return 0x00;
    }
    WINDOW_CLASS_EX_W NewClassEx = {0};
    WindClassWToWindClassExW(&NewClassEx, (PWINDOW_CLASS_W)NewClass);
    return RegisterClassExW((const WINDOW_CLASS_EX_W*)&NewClassEx);
}

USER32_API
ATOM RegisterClassExA(
    const WINDOW_CLASS_EX_A* NewClass 
){
    if(!NewClass->ClassName){
        return 0x00;
    }
    BOOLEAN MenuNameIsAtom = false;
    WINDOW_CLASS_EX_W NewClassEx = {0};
    LPWSTR TmpMenuName = 0x00;
    RTL_ATOM Result = 0x00;
    size_t ClassStrLen = strlen(NewClass->ClassName);
    size_t MenuStrLen = 0x00;
    LPWSTR TmpClassName = LouRtlAllocateHeapArray(LouDllHeap, WCHAR, ClassStrLen + 1);
    for(size_t i = 0; i < ClassStrLen; i++){
        TmpClassName[i] = (WCHAR)NewClass->ClassName[i];
    }
    TmpClassName[ClassStrLen] = L'\0'; 
    if(NewClass->MenuName){
        MenuNameIsAtom = ((UINTPTR)NewClass->MenuName <= UINT16_MAX) ? true : false;
        if(MenuNameIsAtom){
            TmpMenuName = (LPWSTR)NewClass->MenuName;
        }else{
            MenuStrLen = strlen(NewClass->MenuName);
            TmpMenuName = LouRtlAllocateHeapArray(LouDllHeap, WCHAR, MenuStrLen + 1);
            for(size_t i = 0; i < MenuStrLen; i++){
                TmpMenuName[i] = (WCHAR)NewClass->MenuName[i]; 
            }
            TmpMenuName[MenuStrLen] = L'\0';
        } 
    }
    WindClassExAToWindClassExW(&NewClassEx, (PWINDOW_CLASS_EX_A)NewClass, TmpClassName, TmpMenuName);
    Result = RegisterClassExW((const WINDOW_CLASS_EX_W*)&NewClassEx);
    //RegisterClassExW has a copy of the new Wide string 
    //so free the temp string for no leaks
    if(TmpMenuName && !MenuNameIsAtom){
        LouRtlFreeHeap(LouDllHeap, TmpMenuName, 0);
    }
    LouRtlFreeHeap(LouDllHeap, TmpClassName, 0);
    return Result;
}

USER32_API
ATOM RegisterClassA(
    const WINDOW_CLASS_A* NewClass
){
    WINDOW_CLASS_EX_A NewClassEx = {0};
    WindClassAToWindClassExA(&NewClassEx, (PWINDOW_CLASS_A)NewClass);
    return RegisterClassExA((const WINDOW_CLASS_EX_A*)&NewClassEx);
}

static BOOLEAN UnregisterClassWAtom(
    RTL_ATOM    Atom,
    HINSTANCE   Instance
){
    PWINDOW_CLASS_TRACKER TmpTracker;
    LOUSTATUS Status = GetLocalClass(
        0x00,
        &TmpTracker,
        Atom,
        0x00
    );
    if(Status == STATUS_SUCCESS){
        FreeLocalClass(TmpTracker);
        if(TmpTracker->ClassExW.WndProcInstance == Instance){
            FreeLocalClass(TmpTracker);
            return true;
        }
    }
    Status = GetGlobalClass(
        0x00,
        &TmpTracker,
        Atom,
        0x00
    );
    if(Status == STATUS_SUCCESS){
        FreeGlobalClass(TmpTracker);
        if(TmpTracker->ClassExW.WndProcInstance == Instance){
            FreeGlobalClass(TmpTracker);
            return true;
        }
    }
    return false;
}

static BOOLEAN UnregisterClassWName(
    LPWSTR      Name,
    HINSTANCE   Instance
){
 PWINDOW_CLASS_TRACKER TmpTracker;
    LOUSTATUS Status = GetLocalClass(
        Name,
        &TmpTracker,
        0x00,
        0x00
    );
    if(Status == STATUS_SUCCESS){
        FreeLocalClass(TmpTracker);
        if(TmpTracker->ClassExW.WndProcInstance == Instance){
            FreeLocalClass(TmpTracker);
            return true;
        }
    }
    Status = GetGlobalClass(
        Name,
        &TmpTracker,
        0x00,
        0x00
    );
    if(Status == STATUS_SUCCESS){
        FreeGlobalClass(TmpTracker);
        if(TmpTracker->ClassExW.WndProcInstance == Instance){
            FreeGlobalClass(TmpTracker);
            return true;
        }
    }
    return false;
}

USER32_API
BOOLEAN
UnregisterClassW(
    LPCWSTR                 ClassName,
    HINSTANCE               Instance
){
    //TODO if new class instance is null check afinity
    RTL_ATOM OptAtom = ((UINTPTR)ClassName <= UINT16_MAX) ? (RTL_ATOM)(UINTPTR)ClassName : 0;
    BOOLEAN Result = false;; 
    if(!ClassName){
        return false;
    }
    if(OptAtom){
        MutexLock(&ClassesLock);    
        Result = UnregisterClassWAtom(OptAtom, Instance);
        MutexUnlock(&ClassesLock);
        return Result;
    }
    MutexLock(&ClassesLock);    
    Result = UnregisterClassWName((LPWSTR)ClassName, Instance);
    MutexUnlock(&ClassesLock);
    return Result;
}
