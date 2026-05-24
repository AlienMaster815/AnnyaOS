//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include "LouDll.h"


LOUDLL_API
LOUSTATUS
LouAddAtomEx(
    LPWSTR      AtomName,
    ULONG       NameLength,
    PRTL_ATOM   OutAtom,
    UINT64      Flags
){
    UINT64 KulaPacket[6] = {0, 0, (UINT64)AtomName, (UINT64)NameLength, (UINT64)OutAtom, (UINT64)Flags};
    LouCALL(LOUADDATOMEX, (UINT64)&KulaPacket[0], 0);
    return (LOUSTATUS)KulaPacket[1];
}

LOUDLL_API
LOUSTATUS 
LouAddAtom(
    LPWSTR      AtomName,
    ULONG       Length,
    PRTL_ATOM   Atom
){
    return LouAddAtomEx(AtomName, Length, Atom, 0);
}