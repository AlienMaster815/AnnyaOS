#ifndef _LOUDLL_
#define _LOUDLL_
#define _INCLUDE_DRSD_LIBRARY_
#include <Annya.h>
#include <stdarg.h>
#include <USRSPC/DRSD.h>

#define LOUDLL_API __declspec(dllexport)

#define SET_OPTIMIZATION(x) __attribute__((optimize(x)))

LOUDLL_API
void LouGlobalUserFree(void* Addr);

#endif