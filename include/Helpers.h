#ifndef _HELPERS_H
#define _HELPERS_H

#include <stdint.h>

#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C" { 
#endif

typedef struct _uint48_t{
    uint32_t    LowDWord;
    uint16_t    HighWord;
}uint48_t;

#define SHIFT_SET(se, sh)               (Se << sh)
#define CLEAR_SET(d,c,se)               (d = (d & ~(c)) | (se & c))
#define CLEAR_SHIFT_SET(d, c, s, se)    (CLEAR_SET(d, SHIFT_SET(c, s), SHIFT_SET(se, s)))
#define SHIFT_RIGHT_GET(d,s)            (d >> s)
#define SHIFT_RIGHT_MASK_GET(d,s,m)     ((d >> s) & m)
#define SHIFT_LEFT_GET(d, s)            (d << s)
#define SHIFT_LEFT_MASK_GET(d, s, m)    ((d << s) & m)

#define UINT8_WIDTH                      (8)
#define UINT16_WIDTH                    (16)
#define UINT32_WIDTH                    (32)
#define UINT64_WIDTH                    (64)

#define UINT8_MASK                      UINT8_MAX
#define INT8_MASK                       INT8_MAX
#define UINT16_MASK                     UINT16_MAX
#define INT16_MASK                      INT16_MAX
#define UINT32_MASK                     UINT32_MAX
#define INT32_MASK                      INT32_MAX
#define UINT64_MASK                     UINT64_MAX
#define INT64_MASK                      INT64_MAX

#define SIGNBIT_INT8                    (7)
#define SIGNBIT_INT16                   (15)
#define SIGNBIT_INT32                   (31)
#define SIGNBIT_INT64                   (63)

#define SHIFT_SET_UINT8(d,s, x)         (CLEAR_SHIFT_SET((uint8_t)d, UINT8_MASK, s, x & UINT8_MASK))
#define SHIFT_SET_UINT16(d,s, x)        (CLEAR_SHIFT_SET((uint16_t)d, UINT16_MASK, s, x & UINT16_MASK))
#define SHIFT_SET_UINT32(d,s, x)        (CLEAR_SHIFT_SET((uint32_t)d, UINT32_MASK, s, x & UINT32_MASK))
#define SHIFT_SET_UINT64(d,s, x)        (CLEAR_SHIFT_SET((uint64_t)d, UINT64_MASK, s, x & UINT64_MASK)) uint64_t is machin width is 64 bit

#define SHIFT_RIGHT_GET_UINT8(d, s)     (SHIFT_RIGHT_MASK_GET((uint8_t)d, s, UINT8_MASK))
#define SHIFT_RIGHT_GET_UINT16(d, s)    (SHIFT_RIGHT_MASK_GET((uint16_t)d, s, UINT16_MASK))
#define SHIFT_RIGHT_GET_UINT32(d, s)    (SHIFT_RIGHT_MASK_GET((uint32_t)d, s, UINT32_MASK))
#define SHIFT_RIGHT_GET_UINT64(d, s)    (SHIFT_RIGHT_MASK_GET((uint64_t)d, s, UINT64_MASK))

#define SHIFT_LEFT_GET_UINT8(d, s)      (SHIFT_LEFT_MASK_GET((uint8_t)d, s, UINT8_MASK))
#define SHIFT_LEFT_GET_UINT16(d, s)     (SHIFT_LEFT_MASK_GET((uint16_t)d, s, UINT16_MASK))
#define SHIFT_LEFT_GET_UINT32(d, s)     (SHIFT_LEFT_MASK_GET((uint32_t)d, s, UINT32_MASK))
#define SHIFT_LEFT_GET_UINT64(d, s)     (SHIFT_LEFT_MASK_GET((uint64_t)d, s, UINT64_MASK)) 



#ifdef __cplusplus
}
#endif
#endif