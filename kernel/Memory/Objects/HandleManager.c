#include "ObjectManager.h"

static LOUSTATUS CreateHandleForObject(
    POBJECT_HEADER ObjectHeader, 
    ACCESS_MASK RequestedAccess, 
    bool SkipAccessTokenCheck //for access token creations and kernel privaledge allocations
){
    if(!SkipAccessTokenCheck){
        PLOUSINE_ACCESS_TOKEN AccessToken;
        LOUSTATUS Status = LouKeZwGetAccessTokenData(&AccessToken, LouKePsmGetCurrentProcessAccessToken());

        if((Status != STATUS_SUCCESS) || (!AccessToken)){
            LouPrint("CreateHandleForObject() Unable To Get Token\n");
            return Status;
        }

        LouPrint("CreateHandleForObject():SkipAccessTokenCheck\n");
        while(1);
    }
    


    LouPrint("CreateHandleForObject()\n");
    while(1);
    return STATUS_SUCCESS;
}

void LouKeDestroyHandleFromObject(POBJECT_HANDLE ObjectHandle){

}

LOUSTATUS LouKeZwCreateHandleForObject(
    POBJECT_HEADER  ObjectHeader,
    ACCESS_MASK     RequestedAccess
){
    return CreateHandleForObject(
        ObjectHeader,
        RequestedAccess,
        true
    );
}

LOUSTATUS LouKeCreateHandleForObject(
    POBJECT_HEADER ObjectHeader, 
    ACCESS_MASK RequestedAccess
){
    return CreateHandleForObject(
        ObjectHeader,
        RequestedAccess,
        false
    );
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
    return Header->ObjectPointer;
}