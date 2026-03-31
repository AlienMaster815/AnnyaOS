#ifndef _UNICODE_SPECIFICATION_H
#define _UNICODE_SPECIFICATION_H
#ifdef __cplusplus
extern "C"{
#endif

#include <cstdint.h>
#include <cstdlib.h>
#include <kernel/loustatus.h>

LOUSTATUS 
Utf32CharToUtf16Char(
    UINT32      LongChar,
    UINT16*     ShortChar,
    BOOLEAN*    OutSurgate
);

#ifdef __cplusplus
}
#endif
#endif