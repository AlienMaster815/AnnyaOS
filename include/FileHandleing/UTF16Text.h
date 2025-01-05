#ifndef _UTF16_TEXT_H
#define _UTF16_TEXT_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else 
#ifndef _USER_MODE_CODE_
#include <LouAPI.h>
#else 
typedef void* FILE;
#endif
#endif


#define UTF16TXT_CR 0x000D
#define UTF16TCT_LF 0x000A


#ifdef __cplusplus
}
#endif

#endif