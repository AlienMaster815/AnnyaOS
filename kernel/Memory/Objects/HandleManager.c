#include "ObjectManager.h"

static LOUSTATUS CreateHandleForObject(
    POBJECT_HEADER ObjectHeader, 
    ACCESS_MASK RequestedAccess, 
    bool SkipAccessTokenCheck //for access token creations and kernel privaledge allocations
){
    if(!SkipAccessTokenCheck){
        LouPrint("CreateHandleForObject():SkipAccessTokenCheck\n");
        while(1);
    }
    
    LouPrint("CreateHandleForObject()\n");
    while(1);
    return STATUS_SUCCESS;
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