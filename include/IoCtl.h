#include <cstdlib.h>

#define DEFINE_LOU_IOCTL_TABLE(Name, ...) \
    LOU_IOCTL_TABLE_ENTRY Name[] = { \
        __VA_ARGS__ \
        {0,0, false, 0}, \
    }

#define DEFINE_LOU_IOCTL_TABLE_ENTRY(ExeName, FunctionName, Fail) \
    {ExeName, FunctionName, Fail, 0}

#define DEFINE_CRITICAL_LOU_IOCTL_ENTRY(ExeName, FunctionName) \
    DEFINE_LOU_IOCTL_TABLE_ENTRY(ExeName, FunctionName, true)

#define DEFINE_OPTIONAL_LOU_IOCTL_ENTRY(ExeName, FunctionName) \
    DEFINE_LOU_IOCTL_TABLE_ENTRY(ExeName, FunctionName, false)


typedef LOUSTATUS (*IOCTL_FUNCTION)(UINT64*);

typedef struct _LOU_IOCTL_TABLE_ENTRY{
    LOUSTR              ExeName;
    LOUSTR              FunctionName;
    BOOLEAN             FailIfNotFound;
    IOCTL_FUNCTION*     IoFunction;
}LOU_IOCTL_TABLE_ENTRY, * PLOU_IOCTL_TABLE_ENTRY;

#ifdef _USER_MODE_CODE_

#ifndef _LOUDLL_
ANNA_IMPORT LOUSTATUS LouInitializeIoCtlTable(PVOID Table);
ANNA_IMPORT LOUSTATUS LouCallIoCtlFunction(PLOU_IOCTL_TABLE_ENTRY Entry, UINT64* KulaPacket);
#else
ANNA_EXPORT LOUSTATUS LouInitializeIoCtlTable(PVOID Table);
ANNA_EXPORT LOUSTATUS LouCallIoCtlFunction(PLOU_IOCTL_TABLE_ENTRY Entry, UINT64* KulaPacket);
#endif

#else 
#ifndef _KERNEL_MODULE_
KERNEL_EXPORT LOUSTATUS LouKeInitializeIoCtlTable(PVOID Table);
KERNEL_EXPORT LOUSTATUS LouKeCallIoCtlFunction(PLOU_IOCTL_TABLE_ENTRY Entry, UINT64* KulaPacket);
#endif
#endif