#ifndef _PROCESS_H
#define _PROCESS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <cstdint.h>
#include <cstdlib.h>
#include <Time.h>
#include "loustatus.h"

typedef HANDLE PWINDHANDLE;

typedef struct _LOUSINE_CREATE_PROCESS_PARAMS{
    TIME_T      OptionalStartTime;   //null for default
    UINT64      TimeQuantum;         //0 for default
    UINT64      Subsystem;           //0 for Annya/Winapi
    UINT8*      ProcessAffinityMask; //optional
}LOUSINE_CREATE_PROCESS_PARAMS, * PLOUSINE_CREATE_PROCESS_PARAMS;

typedef HANDLE HPROCESS, * PHPROCESS;

#define PROCESS_PRIORITY_HIGH       0
#define PROCESS_PRIORITY_ABOVE      1
#define PROCESS_PRIORITY_NORMAL     2
#define PROCESS_PRIORITY_BELOW      3
#define PROCESS_PRIORITY_LOW        4
#define PROCESS_PRIORITY_RINGS      5

#define KERNEL_PROCESS_NAME         "The Lousine Kernel"
#define ASMSS_PROCESS_NAME          "Annya Os Session Manager Subsystem"

#ifndef _USER_MODE_CODE_

LOUSTATUS LouKePmCreateProcessEx(
    PHPROCESS                       HandleOut,          //Optional                       
    LOUSTR                          ProcessName,        //Process Name
    PHPROCESS                       ParrentProcess,     //Parent Process Handle           
    UINT8                           Priority,           //Process Schedualer Priority
    HANDLE                          Section,            //Section of the Executable Image
    HANDLE                          AccessToken,        //Access Token
    PLOUSINE_CREATE_PROCESS_PARAMS  Params              //otpional Params
);

HANDLE LouKePsmGetCurrentProcessAccessToken();
#endif

#ifdef __cplusplus
}
#endif
#endif