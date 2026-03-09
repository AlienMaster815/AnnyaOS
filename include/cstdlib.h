#ifndef _CSTD_LIB_H
#define _CSTD_LIB_H

#include <cstdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define STRUNCATE 80
#define EINVAL 22
#define ERANGE 34


#define IS_CPP __cplusplus
#define IS_X86 __i386__
#define IS_X86_64 __x86_64__


#define VOID 	void
#define VOIDP	void*

typedef PVOID HANDLE, * PHANDLE;

typedef struct _UNICODE_STRING{
    USHORT  Length;
    USHORT  MaximumLength;
    LPWSTR  Buffer;
}UNICODE_STRING, * PUNICODE_STRING, * LPUNICODE_STRING;

typedef const UNICODE_STRING* PCUNICODE_STRING;
typedef const UNICODE_STRING CUNICODE_STRING;

typedef struct  _ListHeader{
    struct _ListHeader* LastHeader;
    struct _ListHeader* NextHeader;
}ListHeader, * PListHeader;

#ifdef __cplusplus
#define UNUSED [[maybe_unused]]
#define UNINIT [[uninitialized]]
#else
#define UNUSED __attribute__((unused))
#define UNINIT __attribute__((uninitialized))
#endif

#define FORCE_INLINE __attribute__((always_inline)) static inline

#define ROUND_UP(value, multiple) \
    (((value) + (multiple) - 1) / (multiple) * (multiple))

#define ROUND_UP64(value, multiple) \
    (((value) + (multiple) - 1) / (multiple) * (multiple))

#define ROUND_DOWN64(value, multiple) \
    ((value) / (multiple) * (multiple))



static inline void* LouKeCastToUnalignedPointer(void* pointer){
	return pointer;
}

typedef enum MEM_EXTENDED_PARAMETER_TYPE {
    MemExtendedParameterInvalidType = 0,
    MemExtendedParameterAddressRequirements,
    MemExtendedParameterNumaNode,
    MemExtendedParameterPartitionHandle,
    MemExtendedParameterUserPhysicalHandle,
    MemExtendedParameterAttributeFlags,
    MemExtendedParameterImageMachine,
    MemExtendedParameterMax
} MEM_EXTENDED_PARAMETER_TYPE, *PMEM_EXTENDED_PARAMETER_TYPE;

#ifndef __has_declspec_attribute
#if defined(_MSC_VER)
#define __has_declspec_attribute(x) 1
#else 
#define __has_declspec_attribute(x) 0
#endif
#endif 


#ifndef DECLSPEC_ALIGN
#if __has_declspec_attribute(Align) && !defined(MIDL_PASS)
#define DECLSPEC_ALIGN(x) __declspec(align(x))
#else
#define DECLSPEC_ALIGN(x)
#endif
#endif

#define MEM_EXTENDED_PARAMETER_TYPE_BITS 8

typedef struct DECLSPEC_ALIGN(8) MEM_EXTENDED_PARAMETER {
    struct
    {
        DWORD64 Type : MEM_EXTENDED_PARAMETER_TYPE_BITS;
        DWORD64 Reserved : 64 - MEM_EXTENDED_PARAMETER_TYPE_BITS;
    } DUMMYSTRUCTNAME;

    union
    {
        DWORD64 ULong64;
        PVOID Pointer;
        SIZE_T Size;
        HANDLE Handle;
        DWORD ULong;
    } DUMMYUNIONNAME;
} MEM_EXTENDED_PARAMETER, *PMEM_EXTENDED_PARAMETER;

typedef WORD SECURITY_DESCRIPTOR_CONTROL, *PSECURITY_DESCRIPTOR_CONTROL;

typedef PVOID PSID;
typedef struct _ACL {
    BYTE AclRevision;
    BYTE Sbz1;
    WORD AclSize;
    WORD AceCount;
    WORD Sbz2;
} ACL, *PACL;

typedef struct _SECURITY_DESCRIPTOR{
    BYTE Revision;
    BYTE Sbz1;
    SECURITY_DESCRIPTOR_CONTROL Control;
    PSID Owner;
    PSID Group;
    PACL Sacl;
    PACL Dacl;
} SECURITY_DESCRIPTOR, *PISECURITY_DESCRIPTOR;

typedef struct PACKED _FLOATING_SAVE_AREA{
    UINT32  Control;
    UINT32  Status;
    UINT32  Tag;
    UINT32  ErrorOffset;
    UINT32  ErrorSelector;
    UINT32  DataOffset;
    UINT32  DataSelector;
    BYTE    RegisterArea[80];
    UINT32  Cr0NpxState;
}FLOATING_SAVE_AREA, * PFLOATING_SAVE_AREA;

#ifndef _USER_MODE_CODE_
#define ABS(x) (((x) < 0) ? -(x) : (x)) 
int abs(int x);
#ifndef _KERNEL_MODULE_
int __cxa_guard_acquire(int64_t *guard);
void __cxa_guard_release(int64_t *guard);
void __cxa_guard_abort(int64_t *);
#endif
#endif

#ifdef __cplusplus
}
#endif


#endif

