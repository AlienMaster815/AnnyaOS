#ifndef _USER_MODE_CODE_
#ifndef _ACCESS_TOKENS_H
#define _ACCESS_TOKENS_H

#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C"{
#endif

/*
-- The WINAPI Documentation doesent actuallu have OR
-- expose an actual definition of the access token and
-- only exposes handles but for the LouAPI this is for
-- Lousine Kernel Implementations
*/

typedef struct _LOUSINE_ACCESS_TOKEN{
    BOOL                    SystemAccessToken; //if a token is a SystemAccess token then access is treated as a super user 
    ACCESS_MASK             CurrentAccess;      //If Access Is A System Access Token Then This Is Set To 0
    PSECURITY_DESCRIPTOR    SecurityDescriptor; //If Access Is A System Access Token Then This Is Set To 0
}LOUSINE_ACCESS_TOKEN, * PLOUSINE_ACCESS_TOKEN;

LOUSTATUS LouKeZwCreateAccessToken(
    PLOUSINE_ACCESS_TOKEN*  OutToken, 
    BOOL                    SystemAccessToken,
    ACCESS_MASK             CurrentAccess,
    PSECURITY_DESCRIPTOR    SecurityDescriptor
);

LOUSTATUS LouKeCreateAccessToken(
    PLOUSINE_ACCESS_TOKEN*  OutToken, 
    BOOL                    SystemAccessToken,
    ACCESS_MASK             CurrentAccess,
    PSECURITY_DESCRIPTOR    SecurityDescriptor
);


LOUSTATUS LouKeZwRegisterAccessTokenToObjectManager(
    PLOUSINE_ACCESS_TOKEN   AccessToken,
    int                     MaxHandles
);

#ifdef __cplusplus
}
#endif
#endif
#endif