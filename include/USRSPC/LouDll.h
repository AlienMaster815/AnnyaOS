
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

#define AWM_IPC_MSGID_REGISTER_CLASS_EX_W  0x01


#endif
#endif
#endif