
#ifndef _LOUDLL_GLOBAL_H
#define _LOUDLL_GLOBAL_H

#include "User.h"

#ifdef _USER_MODE_CODE_
#ifndef _LOUDLL_

ANNA_IMPORT
LOUSTATUS
LouAddAtomEx(
    LPWSTR      AtomName,
    ULONG       NameLength,
    PRTL_ATOM   OutAtom,
    UINT64      Flags
);

ANNA_IMPORT
LOUSTATUS
LouAddAtom(
    LPWSTR      AtomName,
    ULONG       NameLength,
    PRTL_ATOM   OutAtom
);

#define ADD_ATOM_FLAG_LOCAL (1 << 0)

ANNA_IMPORT
size_t 
wcslen(
    LPCWSTR str
);

#endif
#endif
#endif