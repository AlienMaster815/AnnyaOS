#ifndef _GDT_H
#define _GDT_H
#include <cstdlib.h>
#include <stddef.h>
#include <cstdint.h>
#include <kernel/loustatus.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _GDT_RECORD{
    ListHeader  Peers;
    UINT32      ProcessorID;
    UINT64      GdtBase;
    UINT64      TssBase;
}GDT_RECORD, * PGDT_RECORD;

#ifndef _USER_MODE_CODE_

LOUSTATUS Initialize_Gdt();

#endif

#ifdef __cplusplus
}
#endif
#endif