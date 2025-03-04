#include <LouDDK.h>

int LouWStrnCpy(PWSTR WString, ULONG StrLen, PWSTR StringCopy);

uint64_t NumberOfNtAtoms = 0;

typedef struct _LOU_KE_ATOM_TABLE_ENTRY{
    ListHeader Neighbors;
    wchar_t* AtomName;
    uint32_t Length;
    uint16_t* Atom;
    uint32_t Flags;
}LOU_KE_ATOM_TABLE_ENTRY, * PLOU_KE_ATOM_TABLE_ENTRY;

LOU_KE_ATOM_TABLE_ENTRY AtomMasterTable;

LOUDDK_API_ENTRY
LOUSTATUS LouKeAddAtomEx(
    wchar_t* AtomName,
    uint32_t Length,
    uint16_t* Atom,
    uint32_t Flags
){

    PLOU_KE_ATOM_TABLE_ENTRY TmpAtomTable = &AtomMasterTable;


    for(uint64_t i = 0 ; i < NumberOfNtAtoms; i++){
        if(TmpAtomTable->Neighbors.NextHeader){
            TmpAtomTable = (PLOU_KE_ATOM_TABLE_ENTRY)TmpAtomTable->Neighbors.NextHeader;
        }
        else{
            TmpAtomTable->Neighbors.NextHeader = (PListHeader)LouMallocEx(sizeof(LOU_KE_ATOM_TABLE_ENTRY) , GET_ALIGNMENT(LOU_KE_ATOM_TABLE_ENTRY));
            TmpAtomTable = (PLOU_KE_ATOM_TABLE_ENTRY)TmpAtomTable->Neighbors.NextHeader;
        }
    }

    //allocate Atom name
    TmpAtomTable->AtomName = (wchar_t*)LouMallocEx(sizeof(WCHAR) * Length, GET_ALIGNMENT(WCHAR));
    //copy atom name
    LouWStrnCpy(TmpAtomTable->AtomName, (ULONG)Length, AtomName);
    //place Atom
    TmpAtomTable->Atom = Atom;
    //Place Flags
    TmpAtomTable->Flags = Flags;
    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
LOUSTATUS LouKeAddAtom(
    wchar_t* AtomName,
    uint32_t Length,
    uint16_t* Atom
){
    return LouKeAddAtomEx(AtomName, Length, Atom, 0);
}