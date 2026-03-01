#ifndef _ERRORS_H
#define _ERRORS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <cstdint.h>

#ifndef _KERNEL_MODULE_
void LouPanic(char* error_message);
#endif



#ifdef __cplusplus
}
#endif

#endif
