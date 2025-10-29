#ifndef _KULA_H
#define _KULA_H

#ifndef __cplusplus 
#include <LouAPI.h
#else
#include <LouDDK.h>
extern "C" {
#endif

UINT64 
LouKeGetCurrentTransitionState();

#ifdef __cplusplus
}
#endif
#endif