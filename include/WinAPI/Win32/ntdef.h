#ifndef _NTDEF_
#define _NTDEF_

#include "specstrings.h"

typedef unsigned long* ULONG_PTR;

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _EVENT_TYPE {
    NotificationEvent = 0,
    SynchronizationEvent = 1,
} EVENT_TYPE;

typedef enum _TIMER_TYPE {
    NotificationTimer = 0,
    SynchronizationTimer = 1,
} TIMER_TYPE;

typedef enum _WAIT_TYPE {
    WaitAll = 0,
    WaitAny = 1,
    WaitNotification = 2,
} WAIT_TYPE;
#ifdef __cplusplus
}
#endif

#include <WinAPI/NtAPI/ntstatus.h>

#define NT_SUCCESS(status)      (((NTSTATUS)(status)) >= 0)
#define NT_INFORMATION(status)  ((((NTSTATUS)(status)) & 0xc0000000) == 0x40000000)
#define NT_WARNING(status)      ((((NTSTATUS)(status)) & 0xc0000000) == 0x80000000)
#define NT_ERROR(status)        ((((NTSTATUS)(status)) & 0xc0000000) == 0xc0000000)
#define InitializeObjectAttributes(p,n,a,r,s) \
    do { \
        (p)->Length = sizeof(OBJECT_ATTRIBUTES); \
        (p)->RootDirectory = r; \
        (p)->Attributes = a; \
        (p)->ObjectName = n; \
        (p)->SecurityDescriptor = s; \
        (p)->SecurityQualityOfService = NULL; \
    } while (0)
#ifndef BASETYPES
#define BASETYPES
typedef unsigned char UCHAR, *PUCHAR;
typedef unsigned short USHORT, *PUSHORT;
typedef unsigned long ULONG, *PULONG;
#endif
typedef ULONG CLONG;
typedef CLONG *PCLONG;
typedef struct _RTL_BALANCED_NODE
{
    union
    {
        struct _RTL_BALANCED_NODE *Children[2];
        struct{
            struct _RTL_BALANCED_NODE *Left;
            struct _RTL_BALANCED_NODE *Right;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;
    union{
        UCHAR Red : 1;
        UCHAR Balance : 2;
        ULONG_PTR ParentValue;
    } DUMMYUNIONNAME2;
} RTL_BALANCED_NODE, *PRTL_BALANCED_NODE;

#define RTL_BALANCED_NODE_RESERVED_PARENT_MASK 3

typedef struct _RTL_RB_TREE{
    RTL_BALANCED_NODE *root;
    RTL_BALANCED_NODE *min;
} RTL_RB_TREE, *PRTL_RB_TREE;

#define RTL_CONSTANT_STRING(s) { sizeof(s) - sizeof(s[0]), sizeof(s), (void*)s }
#endif