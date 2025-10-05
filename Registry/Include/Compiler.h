#ifndef _COMPILER_H
#define _COMPILER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#define PVOID void*
#define LOU_STRING char*

typedef int error_t;

#define LKR_SECTION_SIZE 4096

static inline void* SafeMalloc(size_t x){
    void* Foo = malloc(x);
    memset(Foo, 0, x);
    return Foo;
}

#define LouKeMallocType(x,y) SafeMalloc(sizeof(x))
#define LouKeMallocArray(x, y, z) SafeMalloc(sizeof(x) * y)
#define LouKeFree(x) free(x)

#include "LKRLIB/LKRLIB.h"
#include "wcsext.h"

typedef struct _ListHeader{
    struct _ListHeader* NextHeader;
    struct _ListHeader* LastHeader;
}ListHeader, * PListHeader;

typedef struct _COMPILER_CONTEXT{
    LOU_STRING      Path;
    size_t          FileSize;
    void*           FileContext;
    PLOUSINE_NODE   CompilerNode;
}COMPILER_CONTEXT, * PCOMPILER_CONTEXT;

PLOUSINE_NODE LouKeCreateLousineNode(
    LPWSTR  NodeID
);

error_t 
LouKeAddLousineNodeEntryToHeader(
    PLOUSINE_NODE           NodeHeader,
    LPWSTR                  Entry,
    PVOID                   Data
);

error_t 
LouKeAddLousineNodeEntryToTree(
    LPWSTR      TreeName,
    LPWSTR      Entry,
    PVOID       Data
);

void
LouKeDestroyLousineNodeTree(
    PLOUSINE_NODE NodeTree
);

error_t
LouKeCreateSourceNodes(
    PCOMPILER_CONTEXT Context
);

LPWSTR CompilerDeclarationLookup(LOU_STRING Str);

#endif