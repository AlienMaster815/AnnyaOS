#include <LouAPI.h>

static const GENERIC_MAPPING PcGenericMapping = {
    .GenericRead = STD_RIGHTS_READ | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
    .GenericWrite = STD_RIGHTS_WRITE | PROCESS_SET_INFORMATION | PROCESS_VM_WRITE | PROCESS_CREATE_PROCESS | PROCESS_CREATE_THREAD | PROCESS_DUP_HANDLE | PROCESS_SET_QUOTA,
    .GenericExecute = STD_RIGHTS_EXECUTE | PROCESS_SET_INFORMATION | PROCESS_VM_OPERATION | PROCESS_CREATE_THREAD,
    .GenericAll = PROCESS_ALL_ACCESS,
};

KERNEL_EXPORT 
void LouKeMapGenericMask(
    PACCESS_MASK            AccessMask,
    const GENERIC_MAPPING*  GenericMapping
){
    if (*AccessMask & ACCESS_MASK_GENERIC_READ) {
        *AccessMask |= GenericMapping->GenericRead;
    }

    if (*AccessMask & ACCESS_MASK_GENERIC_WRITE) {
        *AccessMask |= GenericMapping->GenericWrite;
    }

    if (*AccessMask & ACCESS_MASK_GENERIC_EXECUTE) {
        *AccessMask |= GenericMapping->GenericExecute;
    }

    if (*AccessMask & ACCESS_MASK_GENERIC_ALL) {
        *AccessMask |= GenericMapping->GenericAll;
    }
    *AccessMask &= ~(ACCESS_MASK_GENERIC_MASK);
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
    PLOUSINE_ACCESS_TOKEN NewToken = LouKeAllocateFastObject("LOUSINE_ACCESS_TOKEN");

    LouKeMapGenericMask(&CurrentAccess, &PcGenericMapping);

    NewToken->SystemAccessToken = SystemAccessToken;
    NewToken->CurrentAccess = CurrentAccess;
    NewToken->SecurityDescriptor = SecurityDescriptor;

    *OutToken = NewToken;

    return STATUS_SUCCESS;
}


LOUSTATUS 
LouKeCheckRequestedAccessToProcessAccessToken(
    ACCESS_MASK AccessMask
){
    PLOUSINE_ACCESS_TOKEN AccessToken;
    HANDLE AccessTokenHandle = LouKePsmGetCurrentProcessAccessToken();
    LOUSTATUS Status = LouKeZwGetAccessTokenData(&AccessToken, AccessTokenHandle);
    if(Status != STATUS_SUCCESS){
        LouPrint("ERROR:Invalid Parameter To LouKeZwGetAccessTokenData()\n");
        return STATUS_ACCESS_DENIED;
    }

    LouKeMapGenericMask(&AccessMask, &PcGenericMapping);

    if(AccessToken->SystemAccessToken){
        return STATUS_SUCCESS;
    }else if((AccessToken->CurrentAccess & AccessMask) == AccessMask){     
        return STATUS_SUCCESS;
    }
    return STATUS_ACCESS_DENIED;
}

LOUSTATUS LouKeCreateAccessToken(
    PLOUSINE_ACCESS_TOKEN*  OutToken, 
    BOOL                    SystemAccessToken,
    ACCESS_MASK             CurrentAccess,
    PSECURITY_DESCRIPTOR    SecurityDescriptor
){
    PLOUSINE_ACCESS_TOKEN AccessToken;
    HANDLE AccessTokenHandle = LouKePsmGetCurrentProcessAccessToken();
    LOUSTATUS Status = LouKeZwGetAccessTokenData(&AccessToken, AccessTokenHandle);
    if(Status != STATUS_SUCCESS){
        LouPrint("ERROR:Invalid Parameter To LouKeZwGetAccessTokenData()\n");
        return STATUS_ACCESS_DENIED;
    }

    if(!AccessToken->SystemAccessToken && SystemAccessToken){
        return STATUS_ACCESS_DENIED;
    }

    Status = LouKeCheckRequestedAccessToProcessAccessToken(CurrentAccess);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    return LouKeZwCreateAccessToken(
        OutToken,
        SystemAccessToken,
        CurrentAccess,
        SecurityDescriptor
    );
}


LOUSTATUS
LouKeCreateAccessTokenCall(
    PHANDLE                 OutToken, 
    ACCESS_MASK             CurrentAccess,
    PSECURITY_DESCRIPTOR    SecurityDescriptor
){ 
    PLOUSINE_ACCESS_TOKEN Token;
    LOUSTATUS Status = LouKeCreateAccessToken(
        &Token,
        false,
        CurrentAccess,
        SecurityDescriptor
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    Status = LouKeRegisterObjectToObjectManager(
        Token,
        sizeof(PLOUSINE_ACCESS_TOKEN),
        "LOUSINE_ACCESS_TOKEN_POINTER",
        1,
        0x00
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    HANDLE UserHandle;
    Status = LouKeAcquireHandleForObject(
        &UserHandle,
        Token, 
        CurrentAccess
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    *OutToken = UserHandle;
    return STATUS_SUCCESS;
}