#ifndef _KERNEL_LIST_H
#define _KERNEL_LIST_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C"{
#else 
#include <LouAPI.h>
#endif

#include <WinAPI/NtAPI/ntstatus.h>

//List Header Is Define in shared types due to the compiler being fussy

static inline 
PListHeader LouKeGetListEnd(
    PListHeader MasterObject, 
    size_t ListSize
){
    PListHeader SlaveObject = MasterObject;
    for(;(uintptr_t)ListSize > 1; ListSize--){
        if(SlaveObject->NextHeader){
            SlaveObject = SlaveObject->NextHeader;
        }
    }
    return SlaveObject;
}

static inline 
LOUSTATUS LouKeUnLinkMemberFromList(
    PListHeader MasterObject,
    PListHeader Handle,
    size_t ListSize
){
    PListHeader SlaveObject = MasterObject;
    for(;(uintptr_t)ListSize > 1; ListSize--){
        if(SlaveObject->NextHeader == Handle){

            return STATUS_SUCCESS;    
        }
        if(SlaveObject->NextHeader){
            SlaveObject = SlaveObject->NextHeader;
        }
    }
    return STATUS_UNSUCCESSFUL;
}

#ifdef __cplusplus
}
#endif
#endif