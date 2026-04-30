#include "ObjectManager.h"

LOUSTATUS LouKeCreateHandleForObject(
    POBJECT_HANDLE* OutHandle,
    POBJECT_HEADER  ObjectHeader, 
    ACCESS_MASK     RequestedAccess
){
    if(!OutHandle || !ObjectHeader){
        return STATUS_INVALID_PARAMETER;
    }

    if(LouKeGetReferenceCount(&ObjectHeader->MaxHandles) && ((LouKeGetReferenceCount(&ObjectHeader->Handles) >= LouKeGetReferenceCount(&ObjectHeader->MaxHandles)))){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    *OutHandle = (POBJECT_HANDLE)LouKeAllocateVmmSharedBuffer32(sizeof(POBJECT_HANDLE), GET_ALIGNMENT(OBJECT_HANDLE) , true, USER_GENERIC_MEMORY);
    if(!(*OutHandle)){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    (*OutHandle)->Header = ObjectHeader;
    (*OutHandle)->AccessMask = RequestedAccess;

    LouKeNotifyHandleOfAcquisition(*OutHandle);

    LouKeListAddTail(&(*OutHandle)->Peers, &ObjectHeader->ObjectHandles.Peers);
    
    return STATUS_SUCCESS;
}

void LouKeDestroyHandleFromObject(
    POBJECT_HANDLE ObjectHandle
){



}

void LouKeNotifyHandleOfAcquisition(
    POBJECT_HANDLE  ObjectHandle
){
    LouKeAcquireReference(&ObjectHandle->KRef);
}

void LouKeNotifyHandleOfRelease(
    POBJECT_HANDLE  ObjectHandle
){
    LouKeReleaseReference(&ObjectHandle->KRef);
}

POBJECT_HEADER LouKeGetObjectHeaderFromHandle(HANDLE Handle){
    return ((POBJECT_HANDLE)Handle)->Header;
}

PVOID LouKeGetObjectFromHandle(HANDLE Handle){
    if(!Handle){
        return 0x00;
    }
    POBJECT_HEADER Header = LouKeGetObjectHeaderFromHandle(Handle);
    if(!Header){
        return 0x00;
    }
    return Header->ObjectPointer;
}