#ifndef _ASMSS_GLOBALS_H
#define _ASMSS_GLOBALS_H

#include "LouDll.h"

#define AWM_IPC_MSGID_REGISTER_CLASS_EX_W  0x01

typedef struct _REGISTER_CLASS_EX_W_MESSAGE_DATA{
    BOOLEAN             Done;
    ATOM                OutAtom;
    PWINDOW_CLASS_EX_W  WindowClass;
}REGISTER_CLASS_EX_W_MESSAGE_DATA, * PREGISTER_CLASS_EX_W_MESSAGE_DATA;

#endif