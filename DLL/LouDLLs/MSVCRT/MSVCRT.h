#ifndef _MSVCRT_H
#define _MSVCRT_H
//#include <Annya.h>

#define MSVCRT_API __declspec(dllexport)

typedef void (__cdecl *FunctionVector)(void);

#include <stdint.h>
#include <stdbool.h>

#define NTSTATUS uint64_t //fillin for Nt Status
#define ENOMEM  12

typedef uint64_t size_t;

typedef void* HANDLE;

typedef void*    HWND;
typedef uint16_t MSG;

typedef void* HANDLE;
typedef void* HMODULE;

typedef bool  BOOL;
#define TRUE  true
typedef unsigned int DWORD;
typedef void* LPVOID;

#define KILOBYTE_PAGE 4096ULL
#define MEGABYTE_PAGE (2 * 1024 * 1024)
#define KILOBYTE 1 * 1024

#define PRESENT_PAGE           0b1
#define WRITEABLE_PAGE        0b10

#define USER_PAGE           (1 << 2)

#define WRITE_THROUGH_PAGE  0b1000
#define CACHE_DISABLED_PAGE 0b10000
#define UNCACHEABLE_PAGE    0b10000

#define PAGE_PRESENT        (1 << 0)
#define PAGE_WRITE          (1 << 1)
#define PAGE_USER           (1 << 2)
#define PAGE_PWT            (1 << 3)
#define PAGE_PCD            (1 << 4)
#define END_PAGE            (1 << 4)

// Section 1:1 RAM ADDRESS
#define MAXMEM 0xFFFFFFFFFFFFFFFFULL
#define RAMADD unsigned char*
#define RAMADDDATA unsigned char *
#define BLOCK 4096
#define SIZE unsigned long long

// Constants for gigabyte and megabyte sizes
#define GIGABYTE (1ULL << 30)  // 1 GB in bytes
#define MEGABYTE (1ULL << 20)  // 1 MB in bytes
#define KILOBYTE 1 * 1024

#define PAGE_TABLE_ALLIGNMENT 4096
#define PAGE_SIZE 4096

#define FLAGSSPACE 0x1FF


__declspec(dllimport)
void* LouVirtualAllocUser(
    size_t      CommitSize,     //allocated PhysicalMemory
    size_t      ReservedSize,   //AllocatedVirtual
    uint64_t    PageFlags
);

__declspec(dllimport)
void* LouGenericAllocateHeapEx(void* Heap, size_t AllocationSize, size_t Alignment);


typedef struct  _ListHeader{
    struct _ListHeader* LastHeader;
    struct _ListHeader* NextHeader;
}ListHeader, * PListHeader;

typedef struct _MSVC_CRITICAL_SECTION_DEBUG_DATA{
    uint16_t                                SectionType;
    uint16_t                                CBTI;
    struct _MSVC_CRITICAL_SECTION*          MsvcCriticalSection;
    ListHeader                              ProcessLockList;
    uint32_t                                LockListEntryCount;
    uint32_t                                ContentionCount;
    uint32_t                                SpareData[2];
}MSVC_CRITICAL_SECTION_DEBUG_DATA, * PMSVC_CRITICAL_SECTION_DEBUG_DATA;

typedef struct _MSVC_CRITICAL_SECTION{
    PMSVC_CRITICAL_SECTION_DEBUG_DATA       DebuggingInfo;
    long                                    LockCount;
    long                                    RecusionCount;
    HANDLE                                  ThreadWithPossesion;
    HANDLE                                  Semaphore;
    unsigned long*                          SpinCount;
}MSVC_CRITICAL_SECTION, * PMSVC_CRITICAL_SECTION;


typedef struct _MSVC_LOCK_TABLE_ENTRY{
    bool                    LockInitialized;
    MSVC_CRITICAL_SECTION   CriticalSection;
}MSVC_LOCK_TABLE_ENTRY, * PMSVC_LOCK_TABLE_ENTRY;

__declspec(dllimport)
int LouPrint(char* Str, ...);

__declspec(dllimport)
void DeleteCriticalSection(PMSVC_CRITICAL_SECTION CriticalSection);

__declspec(dllimport)
void EnterCriticalSection(PMSVC_CRITICAL_SECTION CriticalSection);

__declspec(dllimport)
void LeaveCriticalSection(PMSVC_CRITICAL_SECTION CriticalSection);

__declspec(dllimport)
NTSTATUS RtlEnterCriticalSection(PMSVC_CRITICAL_SECTION CriticalSection);

__declspec(dllimport)
void InitializeCriticalSectionEx(
    PMSVC_CRITICAL_SECTION CriticalSection, 
    uint64_t Reserved, 
    uint64_t Flags
);

//MSVC Lock IDs
#define MSVC_LOCK_SIGNAL            1
#define MSVC_LOCK_IOB_SCAN          2
#define MSVC_LOCK_TMPNAM            3
#define MSVC_LOCK_INPUT             4
#define MSVC_LOCK_OUTPUT            5
#define MSVC_LOCK_CSCANF            6
#define MSVC_LOCK_CPRINTF           7
#define MSVC_LOCK_CONIO             8
#define MSVC_LOCK_HEAP              9
#define MSVC_LOCK_BHEAP             10 //depreciated
#define MSVC_LOCK_TIME              11
#define MSVC_LOCK_ENV               12
#define MSVC_LOCK_EXIT1             13
#define MSVC_LOCK_EXIT2             14
#define MSVC_LOCK_THREAD_DATA       15 //depreciated
#define MSVC_LOCK_POPEN             16
#define MSVC_LOCK_LOCK_TABLE        17
#define MSVC_LOCK_OSFHND            18
#define MSVC_LOCK_SETLOCALE         19
//the following are Questioned to be depreciated
#define MSVC_LOCK_LC_COLLATE        20
#define MSVC_LOCK_LC_CTYPE          21
#define MSVC_LOCK_LC_MONETARY       22
#define MSVC_LOCK_LC_NUMERIC        23
#define MSVC_LOCK_LC_TIME           24
//ENDOF Questioned Depreciated Data
#define MSVC_LOCK_MB_CP             25
#define MSVC_LOCK_NLG               26
#define MSVC_LOCK_TYPEINFO          27
#define MSVC_LOCK_STREAM_COUNT      28
//ENDOF MSVC Lock IDs

#define MSVC_IOB_ENTRY_COUNT        20
#define MSVC_LAST_STREAM            ((MSVC_LOCK_STREAM_COUNT + MSVC_IOB_ENTRY_COUNT) - 1)        

#define MSVC_TOTAL_LOCKS            (MSVC_LAST_STREAM + 1)



#endif//_MSVCRT_H