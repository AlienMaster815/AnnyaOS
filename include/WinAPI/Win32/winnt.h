#ifndef _WINNT_H
#define _WINNT_H

#include "winapifamily.h"

#ifdef __cplusplus
extern "C"{
#endif

#define DECLSPEC_IMPORT __declspec(dllimport)
#define DECLSPEC_EXPORT __declspec(dllexport)

#ifndef __has_declspec_attribute
#if defined(_MSC_VER)
#define __has_declspec_attribute(x) 1
#else 
#define __has_declspec_attribute(x) 0
#endif
#endif 

#ifdef _LOUDLL_
#define NTSYSAPI DECLSPEC_EXPORT
#else
#define NTSYSAPI DECLSPEC_IMPORT
#endif

#define NTAPI __stdcall
#define FASTCALL __fastcall

#ifndef DECLSPEC_NORETURN
#if __has_declspec_attribute(noreturn) && !defined(MIDL_PASS)
#define DECLSPEC_NORETURN __declspec(noreturn)
#else
#define DECLSPEC_NORETURN
#endif
#endif

#ifndef DECLSPEC_ALIGN
#if __has_declspec_attribute(Align) && !defined(MIDL_PASS)
#define DECLSPEC_ALIGN(x) __declspec(align(x))
#else
#define DECLSPEC_ALIGN(x)
#endif
#endif

#ifndef DECLSPEC_NOTHROW
#if __has_declspec_attribute(nothrow) && !defined(MIDL_PASS)
#define DECLSPEC_NOTHROW __declspec(nothrow)
#else
#define DECLSPEC_NOTHROW
#endif
#endif

typedef void (NTAPI * PFLS_CALLBACK_FUNCTION)(PVOID);

#ifndef _LIST_ENTRY_
#define _LIST_ENTRY_
typedef struct _LIST_ENTRY{
    struct _LIST_ENTRY* Flink;
    struct _LIST_ENTRY* Blink;
}LIST_ENTRY, * PLIST_ENTRY, *RESTRICTED_POINTER;
#endif

#define DELETE                              0x00010000
#define READ_CONTROL                        0x00020000
#define WRITE_DAC                           0x00040000
#define WRITE_OWNER                         0x00080000
#define SYNCHRONIZE                         0x00100000
#define STANDARD_RIGHTS_REQUIRED            0x000f0000

#define STANDARD_RIGHTS_READ                READ_CONTROL
#define STANDARD_RIGHTS_WRITE               READ_CONTROL
#define STANDARD_RIGHTS_EXECUTE             READ_CONTROL

#define STANDARD_RIGHTS_ALL                 0x001f0000

#define SPECIFIC_RIGHTS_ALL                 0x0000ffff

#define GENERIC_READ                        0x80000000
#define GENERIC_WRITE                       0x40000000
#define GENERIC_EXECUTE                     0x20000000
#define GENERIC_ALL                         0x10000000

#define MAXIMUM_ALLOWED                     0x02000000
#define ACCESS_SYSTEM_SECURITY              0x01000000

#define EVENT_QUERY_STATE                   0x0001
#define EVENT_MODIFY_STATE                  0x0002
#define EVENT_ALL_ACCESS                    (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x3)

#define SEMAPHORE_QUERY_STATE               0x0001
#define SEMAPHORE_MODIFY_STATE              0x0002
#define SEMAPHORE_ALL_ACCESS                (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x3)

#define MUTANT_QUERY_STATE                  0x0001
#define MUTANT_ALL_ACCESS                   (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | MUTANT_QUERY_STATE)

#define JOB_OBJECT_ASSIGN_PROCESS           0x0001
#define JOB_OBJECT_SET_ATTRIBUTES           0x0002
#define JOB_OBJECT_QUERY                    0x0004
#define JOB_OBJECT_TERMINATE                0x0008
#define JOB_OBJECT_SET_SECURITY_ATTRIBUTES  0x0010
#define JOB_OBJECT_IMPERSONATE              0x0020
#define JOB_OBJECT_ALL_ACCESS               (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x3f)

#define TIMER_QUERY_STATE                   0x0001
#define TIMER_MODIFY_STATE                  0x0002
#define TIMER_ALL_ACCESS                    (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x3)

#define PROCESS_TERMINATE                   0x0001
#define PROCESS_CREATE_THREAD               0x0002
#define PROCESS_VM_OPERATION                0x0008
#define PROCESS_VM_READ                     0x0010
#define PROCESS_VM_WRITE                    0x0020
#define PROCESS_DUP_HANDLE                  0x0040
#define PROCESS_CREATE_PROCESS              0x0080
#define PROCESS_SET_QUOTA                   0x0100
#define PROCESS_SET_INFORMATION             0x0200
#define PROCESS_QUERY_INFORMATION           0x0400
#define PROCESS_SUSPEND_RESUME              0x0800
#define PROCESS_QUERY_LIMITED_INFORMATION   0x1000
#define PROCESS_SET_LIMITED_INFORMATION     0x2000
#define PROCESS_ALL_ACCESS                  (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0xffff)



#ifdef __cplusplus
}
#endif
#endif