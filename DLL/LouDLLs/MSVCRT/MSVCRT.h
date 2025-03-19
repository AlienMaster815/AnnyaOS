#ifndef _MSVCRT_H
#define _MSVCRT_H
//#include <Annya.h>

#define MSVCRT_API __declspec(dllexport)

typedef void (__cdecl *FunctionVector)(void);

#include <stdint.h>
#include <stdbool.h>

typedef void* HANDLE;

typedef void*    HWND;
typedef uint16_t MSG;

typedef void* HANDLE;
typedef void* HMODULE;

typedef bool  BOOL;
#define TRUE  true
typedef unsigned int DWORD;
typedef void* LPVOID;


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