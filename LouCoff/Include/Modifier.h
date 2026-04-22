#ifndef _MODIFIER_H
#define _MODIFIER_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <stddef.h>
#include <ctype.h>
#include <../../include/kernel/loustatus.h>

typedef int8_t      INT8;
typedef uint8_t     UINT8, CHAR;
typedef int16_t     INT16;
typedef uint16_t    UINT16;
typedef int32_t     INT32;
typedef uint32_t    UINT32;
typedef int64_t     INT64;
typedef uint64_t    UINT64;
typedef size_t      SIZE;
typedef char*       string;
typedef void*       PVOID;
typedef UINT16*     LPWSTR;
typedef UINT16      USHORT;

static inline PVOID LouKeMallocExUnix(
    SIZE Size,
    SIZE Alignment
){
    PVOID Pointer;
    if (posix_memalign(&Pointer, Alignment, Size) != 0) {
        return 0x00;
    }

    memset(Pointer, 0, Size);

    return Pointer;
}   

#define GET_ALIGNMENT(x) _Alignof(x)

#define LouKeMallocEx(x, y, z)      LouKeMallocExUnix(x, y)
#define LouKeFree(x)                free(x)
#define LouKeMallocArray(x, y, z)   LouKeMallocEx(sizeof(x) * y, GET_ALIGNMENT(x), z)

#define MODIFIER_PARAMETER_EXECUTABLE   "-E"
#define MODIFIER_PARAMETER_SOURCE       "-S"
#define MODIFIER_PARAMETER_PRIVLEDGE    "-P"
#define MODIFIER_PARAMETER_MODIFIER     "./LPEModifier"

#define SECTION_ALIGNMENT               4096

#define GetStructureSize(type, member, count) \
    ((size_t)((uintptr_t)(&((type*)0x00)->member[count])))


typedef struct _FILE_CONTEXT{
    string      FilePath;
    void*       FileContext;
    size_t      FileSize;
}FILE_CONTEXT, * PFILE_CONTEXT;

typedef struct _LOUCOFF_MODIFIER_CONTEXT{
    int                 ArgumentCount;
    string*             Arguments;
    FILE_CONTEXT        CoffFile;
    FILE_CONTEXT        SourceFile;//opt
    PVOID               KulaSection;
    bool                KernelObject;
}LOUCOFF_MODIFIER_CONTEXT, * PLOUCOFF_MODIFIER_CONTEXT;

void StrToLower_s(string Str, size_t Size);
void StrToLower(string Str);

LOUSTATUS MakeCoffModifications(PLOUCOFF_MODIFIER_CONTEXT Context);
LOUSTATUS FileContextOpenFile(PFILE_CONTEXT FileContext);
void FileContextCloseFile(PFILE_CONTEXT FileContext);
LOUSTATUS MakeKulaSection(PLOUCOFF_MODIFIER_CONTEXT Context);

#include "Coff.h"

#define KERNEL_GENERIC_MEMORY 0


#endif