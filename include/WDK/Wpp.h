#ifndef _WPP_H
#define _WPP_H

#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C"{
#endif

extern
uint64_t 
WppLoadTracingSupport();

#ifdef __cplusplus
}
#endif
#endif