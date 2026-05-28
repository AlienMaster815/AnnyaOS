
#ifndef _LOUDLL_GLOBAL_H
#define _LOUDLL_GLOBAL_H

#include "User.h"

#ifdef _USER_MODE_CODE_
#ifndef _LOUDLL_

ANNA_IMPORT
void*
LouMemCpy(
    void* OutStream,
    void* InStream,
    size_t ByteCount
);

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

ANNA_IMPORT
LOUSTATUS
LouCreateIpcManagerForProcess(
    LOU_IPC_CALLBACK    Callback
);

ANNA_IMPORT
LOUSTATUS
LouIpcGetIpcMessage(
    PLOU_IPC_MESSAGE*   OutMessage,
    BOOLEAN             WaitForMessage
);

ANNA_IMPORT
LOUSTATUS 
LouIpcProcessIpcMessage(
    PLOU_IPC_MESSAGE Message
);

ANNA_IMPORT
LOUSTATUS
LouIpcSendIpcMessage(
    LPWSTR              ProcessName,
    PLOU_IPC_MESSAGE    Message
);

ANNA_IMPORT
LOUSTATUS
LouIpcCreateIpcMessage(
    PLOU_IPC_MESSAGE*   OutMessage,
    UINT64              MessageID,
    PVOID               DataIn,
    SIZE                DataInSize
);

ANNA_IMPORT 
void 
LouIpcDestroyIpcMessage(
    PLOU_IPC_MESSAGE    Message
);

ANNA_IMPORT
LOUSTATUS
LouIpcGetIpcMessageData(
    PLOU_IPC_MESSAGE    Message,
    PVOID               DataOut,
    SIZE                DataOutSize
);

ANNA_IMPORT
LOUSTATUS
LouIpcSetIpcMessageData(
    PLOU_IPC_MESSAGE Message,
    PVOID            Data,
    SIZE             DataSize
);

ANNA_IMPORT
LOUSTATUS
LouGetGlobalObject(
    LPWSTR ObjectName,
    PVOID* Object
);

ANNA_IMPORT
LOUSTATUS
LouGetGlobalObjectEx(
    LPWSTR      ObjectName,
    PVOID*      Object,
    PRTL_ATOM   OutAtom
);

ANNA_IMPORT
LOUSTATUS
LouUnRegisterGlobalObject(
    LPWSTR  ObjectName
);

ANNA_IMPORT
LOUSTATUS 
LouRegisterGlobalObject(
    LPWSTR  ObjectName, 
    PVOID   Object
);

ANNA_IMPORT
PUSER_PROCESS_HEAP
LouRtlCreateSharedHeap(
    ULONG                   Flags,
    PVOID                   HeapBase,
    SIZE                    ReservedSize,
    SIZE                    CommitSize,
    PERESOURCE_OBJECT       ResourceLock,
    PUSER_HEAP_PARAMETERS   Parameters
);

ANNA_IMPORT
LPWSTR
wcscpy(
    LPWSTR Destination,
    LPWSTR Source
);

ANNA_IMPORT
int
wcscmp(
    LPWSTR Str1,
    LPWSTR Str2
);

ANNA_IMPORT
LOUSTATUS 
LouDeleteAtom(
    RTL_ATOM Atom
);

ANNA_IMPORT
LOUSTATUS 
LouRegisterGlobalObjectEx(
    LPWSTR      ObjectName, 
    PVOID       Object,
    PRTL_ATOM   OutAtom
);

ANNA_IMPORT
LOUSTATUS LouGetGlobalObjectFromAtom(
    RTL_ATOM    Atom,
    PVOID*      Object
);

#ifndef _MSVCRT_H

ANNA_IMPORT size_t strlen(string Str); //TODO: change to LouStrLen

#endif

#endif
#endif
#endif