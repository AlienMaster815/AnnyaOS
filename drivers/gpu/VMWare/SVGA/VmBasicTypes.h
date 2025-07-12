#include <LouDDK.h>

#ifndef _VM_BASIC_TYPES_H
#define _VM_BASIC_TYPES_H

typedef uint64_t PA;
typedef uint32_t PPN;
typedef uint32_t PPN32;
typedef uint64_t PPN64;

#define MAX_UINT64 0xFFFFFFFFFFFFFFFF
#define MAX_UINT32 0xFFFFFFFF
#define MAX_UINT16 0xFFFF

#define CONSTANT64(x) x##ULL

#ifndef MEGABYTE_SHIFT
#define MEGABYTE_SHIFT 20
#endif
#ifndef MEGA_TO_BYTE
#define MEGA_TO_BYTE(Bytes) ((uint64_t)(Bytes) << MAGABYTE_SHIFT)
#endif

#ifndef _ATOMIC_64
#define _ATOMIC_64
typedef struct PACKED _atmoic64_t{
    atomic_t LowDWord;
    atomic_t HighDWord;
}atmoic64_t;
#endif

typedef struct _MKS_GUEST_STATUS_COUNTER{
    atmoic64_t Count;
}MKS_GUEST_STATUS_COUNTER, * PMKS_GUEST_STATUS_COUNTER;

typedef struct _MKS_GUEST_STATUS_COUNTER_TIME{
    MKS_GUEST_STATUS_COUNTER    Counter;
    atmoic64_t                  SelfCycles;
    atmoic64_t                  TotalCycles;
}MKS_GUEST_STATUS_COUNTER_TIME, * PMKS_GUEST_STATUS_COUNTER_TIME;

#define MKS_GUEST_STATUS_FLAG_NONE    0
#define MKS_GUEST_STATUS_FLAG_TIME    (1U << 0)

typedef struct __attribute__((aligned(32))) _MKS_GUEST_STATUS_INFO_ENTRY{
    union{
        const string    s;
        uint64_t        u;
    }Name;
    union{
        const string    s;
        uint64_t        u;
    }Description;
    uint64_t            Flags;
    union{
        PMKS_GUEST_STATUS_COUNTER           Counter;
        PMKS_GUEST_STATUS_COUNTER_TIME      CounterTime;
    }Status;
}MKS_GUEST_STATUS_INFO_ENTRY, * PMKS_GUEST_STATUS_INFO_ENTRY;

#define INVALID_PPN64 ((PPN64)0x000FFFFFFFFFFFFF)

#ifndef _PAGE_FRAME_SYSTEM
#define _PAGE_FRAME_SYSTEM

#define PFN_UP(x)  (((x) + 0x1000 - 1) >> 12)

#endif

#define MKS_GUEST_STATUS_INSTANCE_DESCRIPTOR_LENGTH 1024
#define MKS_GUEST_STATUS_INSTANCE_MAX_STATUS        4096
#define MKS_GUEST_STATUS_INSTANCE_MAX_STATUS_PPNS (PFN_UP(MKS_GUEST_STATUS_INSTANCE_MAX_STATUS * sizeof(MKS_GUEST_STATUS_COUNTER_TIME)))
#define MKS_GUEST_STATUS_INSTANCE_MAX_INFO_PPNS (PFN_UP(MKS_GUEST_STATUS_INSTANCE_MAX_STATUS * sizeof(MKS_GUEST_STATUS_INFO_ENTRY)))
#define MKS_GUEST_STATUS_AVERAGE_NAME_LENGTH 40
#define MKS_GUEST_STATUS_INSTANCE_MAX_STRING_PPNS (PFN_UP(MKS_GUEST_STATUS_INSTANCE_MAX_STATUS * MKS_GUEST_STATUS_AVERAGE_NAME_LENGTH))

typedef struct _MKS_GUEST_STATUS_INSTANCE_DESCRIPTOR{
    uint64_t    Rezerved0;
    uint64_t    StatusStartVA;
    uint64_t    StringStartVA;
    uint64_t    StatusLength;
    uint64_t    StringLengthl;
    PPN64       StatusPPNs[MKS_GUEST_STATUS_INSTANCE_MAX_STATUS_PPNS];
    PPN64       InfoPPNs[MKS_GUEST_STATUS_INSTANCE_MAX_INFO_PPNS];
    PPN64       StringPPNs[MKS_GUEST_STATUS_INSTANCE_MAX_STRING_PPNS];
    char        Description[MKS_GUEST_STATUS_INSTANCE_DESCRIPTOR_LENGTH];
}MKS_GUEST_STATUS_INSTANCE_DESCRIPTOR, * PMKS_GUEST_STATUS_INSTANCE_DESCRIPTOR;



#endif