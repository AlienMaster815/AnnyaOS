#include <LouAPI.h>

LOUSTATUS LouKeConstructAccessToken(PVOID Token, PVOID Params){
    memcpy(Token, Params, sizeof(LOUSINE_ACCESS_TOKEN));
    return STATUS_SUCCESS;
}

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
    UNUSED LOUSINE_ACCESS_TOKEN TokenTemplate = {0};
    
    TokenTemplate.SystemAccessToken = SystemAccessToken;
    TokenTemplate.CurrentAccess = CurrentAccess;
    TokenTemplate.SecurityDescriptor = SecurityDescriptor;

    *OutToken = LouKeAllocateFastObjectEx("LOUSINE_ACCESS_TOKEN", &TokenTemplate);

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