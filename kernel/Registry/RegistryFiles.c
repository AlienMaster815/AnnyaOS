#include <LouAPI.h>
#include "Registry.h"



static uintptr_t BootRegistryBase = 0; 
static uintptr_t BootRegistryTop = 0; 

void InitializeBootRegistry(uintptr_t Base, uintptr_t Top){
    BootRegistryBase = Base;
    BootRegistryTop = Top;   
}

UNUSED static void SanityCheck(LPWSTR Str, size_t Length){
    for(size_t i = 0 ; i < Length; i++){
        LouPrint("%c", (char)Str[i]);
    }
    LouPrint("\n");
}

static PLKR_FILE_HEADER RegistryHandle = 0x00;

PVOID GetRegHiveOffsetHandle(PVOID Key){
    return (PVOID)(Key - (PVOID)RegistryHandle);
}

LOUSTATUS LouKeInitializeRegistry(){
    LouPrint("LouKeInitializeRegistry()\n");

    if(wcscmp((LPWSTR)BootRegistryBase, L"LOUSINE_SYSTEM_FILE")){
        LouPrint("File Is Not Registry File\n");
        return STATUS_UNSUCCESSFUL;
    }

    RegistryHandle = (PLKR_FILE_HEADER)BootRegistryBase;

    return STATUS_SUCCESS;
}


LOUSTATUS 
LouKeReadRegistryValue(
    LPWSTR  Key,
    PVOID   Data,
    size_t  Count
){

    //todo

    return STATUS_UNSUCCESSFUL;
}

PVOID 
LouKeOpenRegistryHandle(
    LPWSTR  Key,
    PVOID   RootHandle
){

    LPWSTR TmpKey = Key;
    LPWSTR EndKey = wcspbrk(Key, L"\\/");
    
    if(!EndKey){
        EndKey = TmpKey + wcslen(TmpKey);
    }

    if(TmpKey == EndKey){
        return 0x00;
    }

    PCOMPILED_NODE_ENTRY TmpNode;
    if(!RootHandle){
       TmpNode = (PCOMPILED_NODE_ENTRY)(uint8_t*)((uintptr_t)RegistryHandle + (uintptr_t)RegistryHandle->FirstEntry);
    }else{
        TmpNode = (PCOMPILED_NODE_ENTRY)(uint8_t*)(uintptr_t)(RootHandle);
        if(!TmpNode->NodePeers.Downward){
            return 0x00;
        }
        TmpNode = (PCOMPILED_NODE_ENTRY)(uint8_t*)((uintptr_t)RegistryHandle + (uintptr_t)TmpNode->NodePeers.Downward);
    }

    while(1){
        UNUSED LPWSTR NodeName = (LPWSTR)(uint8_t*)((uintptr_t)TmpNode + sizeof(COMPILED_NODE_ENTRY));
        UNUSED size_t NameSize = TmpNode->Node.NameSize;
        //SanityCheck(NodeName, NameSize);

        if(((size_t)(EndKey - TmpKey) == NameSize) && (!wcsncmp(NodeName, TmpKey, NameSize))){
            //SanityCheck(NodeName, NameSize);
            if((size_t)(EndKey - TmpKey) == wcslen(TmpKey)){
                return (PVOID)TmpNode;
            }
            
            TmpKey = EndKey + 1;
            EndKey = wcspbrk(TmpKey, L"\\/");
            if(!EndKey){
                EndKey = TmpKey + wcslen(TmpKey);
            }



            if(!TmpNode->NodePeers.Downward){
                return 0x00;
            }

            TmpNode = (PCOMPILED_NODE_ENTRY)(uint8_t*)((uintptr_t)RegistryHandle + (uintptr_t)TmpNode->NodePeers.Downward);

                    
            continue;
        }


        if(!TmpNode->NodePeers.Forward){
            break;
        }
        TmpNode = (PCOMPILED_NODE_ENTRY)(uint8_t*)((uintptr_t)RegistryHandle + (uintptr_t)TmpNode->NodePeers.Forward);
    }

    return 0x00;
}

size_t LouKeGetRegistryKeySize(PVOID Key){
    return ((PCOMPILED_NODE_ENTRY)Key)->Node.ItemSize;
}

LOUSTATUS LouKeReadRegistryWcsValue(
    PVOID Key, 
    LPWSTR String
){

    if(!String){
        return STATUS_INVALID_PARAMETER;
    }else if(!Key){
        String[0] = L'\0';
        return STATUS_INVALID_PARAMETER;
    }

    PCOMPILED_NODE_ENTRY Node = (PCOMPILED_NODE_ENTRY)Key;

    if(GET_ITEM_OPCODE(&Node->Node) != STRING_OPCODE){
        return STATUS_INVALID_PARAMETER;
    }

    wcsncpy(String, (LPWSTR)((size_t)&Node->Node + GET_ITEM_OFFSET(&Node->Node)), Node->Node.ItemSize / 2);

    return STATUS_SUCCESS;
}

LOUSTATUS LouKeReadRegistryWordValue(
    PVOID Key, 
    WORD* Data
){

    if(!Data){
        return STATUS_INVALID_PARAMETER;
    }else if(!Key){
        *Data = 0;
        return STATUS_INVALID_PARAMETER;
    }

    PCOMPILED_NODE_ENTRY Node = (PCOMPILED_NODE_ENTRY)Key;

    if(GET_ITEM_OPCODE(&Node->Node) != WORD_OPCODE){
        return STATUS_INVALID_PARAMETER;
    }

    *Data = *(WORD*)((size_t)&Node->Node + GET_ITEM_OFFSET(&Node->Node));

    return STATUS_SUCCESS;
}

LOUSTATUS LouKeReadRegistryByteValue(
    PVOID Key, 
    BYTE* Data
){

    if(!Data){
        return STATUS_INVALID_PARAMETER;
    }else if(!Key){
        *Data = 0;
        return STATUS_INVALID_PARAMETER;
    }

    PCOMPILED_NODE_ENTRY Node = (PCOMPILED_NODE_ENTRY)Key;

    if(GET_ITEM_OPCODE(&Node->Node) != BYTE_OPCODE){
        return STATUS_INVALID_PARAMETER;
    }

    *Data = *(BYTE*)((size_t)&Node->Node + GET_ITEM_OFFSET(&Node->Node));

    return STATUS_SUCCESS;
}

LOUSTATUS LouKeReadRegistryDWordValue(
    PVOID Key, 
    DWORD* Data
){

    if(!Data){
        return STATUS_INVALID_PARAMETER;
    }else if(!Key){
        *Data = 0;
        return STATUS_INVALID_PARAMETER;
    }

    PCOMPILED_NODE_ENTRY Node = (PCOMPILED_NODE_ENTRY)Key;

    if(GET_ITEM_OPCODE(&Node->Node) != DWORD_OPCODE){
        return STATUS_INVALID_PARAMETER;
    }

    *Data = *(DWORD*)((size_t)&Node->Node + GET_ITEM_OFFSET(&Node->Node));

    return STATUS_SUCCESS;
}

LOUSTATUS LouKeReadRegistryQWordValue(
    PVOID Key, 
    QWORD* Data
){

    if(!Data){
        return STATUS_INVALID_PARAMETER;
    }else if(!Key){
        *Data = 0;
        return STATUS_INVALID_PARAMETER;
    }

    PCOMPILED_NODE_ENTRY Node = (PCOMPILED_NODE_ENTRY)Key;

    if(GET_ITEM_OPCODE(&Node->Node) != QWORD_OPCODE){
        return STATUS_INVALID_PARAMETER;
    }

    *Data = *(QWORD*)((size_t)&Node->Node + GET_ITEM_OFFSET(&Node->Node));

    return STATUS_SUCCESS;
}