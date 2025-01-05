#include <LouDDK.h>

LOUDDK_API_ENTRY
LOUSTATUS LouKeAddAtomEx(
    wchar_t* AtomName,
    uint32_t Length,
    uint16_t* Atom,
    uint32_t Flags
);

LOUDDK_API_ENTRY
NTSTATUS
NtAddAtomEx(
    PWSTR AtomName,
    ULONG Length,
    PRTL_ATOM Atom,
    ULONG Flags
){
    return LouKeAddAtomEx((wchar_t*)AtomName, (uint32_t)Length, (uint16_t*)Atom, (uint32_t)Flags);
}

LOUDDK_API_ENTRY
NTSTATUS
NtAddAtom(
    PWSTR       AtomName,
    ULONG       Length,
    PRTL_ATOM   Atom
){
    return NtAddAtomEx(AtomName, Length, Atom, 0);
}
