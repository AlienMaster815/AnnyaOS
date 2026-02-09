#ifndef _OBJECT_MANAGER_H
#define _OBJECT_MANAGER_H

#include <LouAPI.h>

struct _OBJECT_HEADER;

typedef struct _OBJECT_HANDLE{
    ListHeader              Peers;
    struct _OBJECT_HEADER*  Header;
    KERNEL_REFERENCE        KRef;
    PVOID                   ObjectRawData;
    SIZE                    ObjectSize;
    ACCESS_MASK             AccessMask;
}OBJECT_HANDLE, * POBJECT_HANDLE;

//This Is Not A WINAPI Internal Structure The
//Object Header IS NOT Openly Defined By The WINAPI
//this is redefined for LouAPI Glue for WINAPI Systems
typedef struct _OBJECT_HEADER{
    UINT8                   Revision;
    LOUSTR                  ObjectName;
    SECURITY_DESCRIPTOR     SecurityDescriptor;
    OBJECT_HANDLE           ObjectHandles;
}OBJECT_HEADER, * POBJECT_HEADER;



#endif