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

//typedef struct 

LOUSTATUS LouKeOpenStoredAccessToken(
    PVOID*  Out,
    LPWSTR  AcTokRegEntry
);

#ifdef __cplusplus
}
#endif
#endif
#endif