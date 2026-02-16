#include <LouAPI.h>

LOUSTATUS LouKeZwCreateAccessToken(
    PLOUSINE_ACCESS_TOKEN*  OutToken, 
    BOOL                    SystemAccessToken,
    ACCESS_MASK             CurrentAccess,
    PSECURITY_DESCRIPTOR    SecurityDescriptor
){
    if(!OutToken){
        LouPrint("LouKeZwCreateAccessToken():EINVAL");
        return STATUS_INVALID_PARAMETER;
    }    
    PLOUSINE_ACCESS_TOKEN NewToken = LouKeAllocateFastObject("LOUSINE_ACCESS_TOKEN");

    NewToken->SystemAccessToken = SystemAccessToken;
    NewToken->CurrentAccess = CurrentAccess;
    NewToken->SecurityDescriptor = SecurityDescriptor;

    *OutToken = NewToken;

    return STATUS_SUCCESS;
}

LOUSTATUS LouKeCreateAccessToken(
    PLOUSINE_ACCESS_TOKEN*  OutToken, 
    BOOL                    SystemAccessToken,
    ACCESS_MASK             CurrentAccess,
    PSECURITY_DESCRIPTOR    SecurityDescriptor
){
/*
    LOUSINE_ACCESS_TOKEN TokenTemplate = {0;}
    
    TokenTemplate.SystemAccessToken = SystemAccessToken;
    TokenTemplate.CurrentAccess = CurrentAccess;
    TokenTemplate.SecurityDescriptor = SecurityDescriptor;
*/


    return STATUS_SUCCESS;
}