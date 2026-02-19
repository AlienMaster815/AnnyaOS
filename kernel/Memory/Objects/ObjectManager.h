#ifndef _OBJECT_MANAGER_H
#define _OBJECT_MANAGER_H

#include <LouAPI.h>

struct _OBJECT_HEADER;

typedef struct _OBJECT_HANDLE{
    ListHeader              Peers;
    struct _OBJECT_HEADER*  Header;
    KERNEL_REFERENCE        KRef;
    PVOID                   ObjectData;
    SIZE                    ObjectSize;
    ACCESS_MASK             AccessMask;
}OBJECT_HANDLE, * POBJECT_HANDLE;

//This Is Not A WINAPI Internal Structure The
//Object Header IS NOT Openly Defined By The WINAPI
//this is redefined for LouAPI Glue for WINAPI Systems
typedef struct _OBJECT_HEADER{
    ListHeader              Peers;
    LOUSTR                  ObjectName;
    SECURITY_DESCRIPTOR     SecurityDescriptor;
    KERNEL_REFERENCE        MaxHandles;
    KERNEL_REFERENCE        Handles;
    PVOID                   ObjectPointer;
    SIZE                    ObjectSize;
    OBJECT_HANDLE           ObjectHandles;
}OBJECT_HEADER, * POBJECT_HEADER;

typedef struct _OBJHDR_CONSTRUCTOR_PARAMS{
    PVOID                   ObjectPointer;
    SIZE                    ObjectSize;
    LOUSTR                  ObjectName;
    PSECURITY_DESCRIPTOR    SecurityDescriptor;
    int                     MaxHandles;
}OBJHDR_CONSTRUCTOR_PARAMS, * POBJHDR_CONSTRUCTOR_PARAMS;

LOUSTATUS LouKeZwCreateHandleForObject(
    POBJECT_HEADER  ObjectHeader,
    ACCESS_MASK     RequestedAccess
);

LOUSTATUS LouKeCreateHandleForObject(
    POBJECT_HEADER ObjectHeader, 
    ACCESS_MASK RequestedAccess
);

void LouKeNotifyHandleOfAcquisition(
    POBJECT_HANDLE  ObjectHandle
);

void LouKeNotifyHandleOfRelease(
    POBJECT_HANDLE  ObjectHandle
);

POBJECT_HEADER LouKeGetObjectHEaderFromHandle(HANDLE Handle);
LOUSTATUS LouKeZwGetAccessTokenData(PLOUSINE_ACCESS_TOKEN* Out, HANDLE TokenHandle);

//Objects TODO:

//User TODO:
//Accelerator Table
//Caret
//Cursor
//DDE Conversation
//Hook
//Icon
//Menu
//Window
//WindowPosition

//Gdi TODO:
//Bitmap
//DeviceContext DC
//MetaFile
//MetaFile DC
//Palette
//Pen / Extended Pens
//Region/s

//Kernel TODO:
//Access Tokens
//Change Notifications
//Communications Device
//Console Input
//Console Screen Buffer
//Dekstop
//Event
//Event Log
//File
//File Mapping
//Heap
//Job
//Mailslot
//Module
//Mutex
//Pipe
//Process
//Semaphore
//Socket
//Thread
//Timer
//TimerQueue
//Timer-Queue Timer
//Update Resource
//Window Station

#endif