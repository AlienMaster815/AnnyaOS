#ifndef _GDT_H
#define _GDT_H
#include <cstdlib.h>
#include <stddef.h>
#include <cstdint.h>
#include <kernel/loustatus.h>

#ifdef __cplusplus
extern "C" {
#endif



#ifndef _USER_MODE_CODE_

LOUSTATUS Initialize_Gdt();

#endif

#ifdef __cplusplus
}
#endif
#endif