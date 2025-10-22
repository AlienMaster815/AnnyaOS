#ifndef _WINNT_H
#define _WINNT_H

#include "winapifamily.h"

#ifndef _LIST_ENTRY_
#define _LIST_ENTRY_
typedef struct _LIST_ENTRY{
    struct _LIST_ENTRY* Flink;
    struct _LIST_ENTRY* Blink;
}LIST_ENTRY, * PLIST_ENTRY, *RESTRICTED_POINTER;
#endif

#endif