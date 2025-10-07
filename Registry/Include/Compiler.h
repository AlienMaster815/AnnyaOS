#ifndef _COMPILER_H
#define _COMPILER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#define PVOID void*
#define LOU_STRING char*

typedef int errno_t;

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


#ifdef __cplusplus
#define UNUSED [[maybe_unused]]
#define UNINIT [[uninitialized]]
#else
#define UNUSED __attribute__((unused))
#define UNINIT __attribute__((uninitialized))
#endif

//EDEF
#define ENO_DECLSEPORATOR           1
#define ENO_DECLARATION             2
#define EINVALID_NAME_DECLARATION   3

void LkrDispatchErrorMessage(
    LPWSTR  Buffer,
    size_t  Length,
    errno_t Error,
    PVOID   Data
);

//EDEF

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

errno_t 
LouKeAddLousineNodeEntryToHeader(
    PLOUSINE_NODE           NodeHeader,
    LPWSTR                  Entry,
    PVOID                   Data
);

errno_t 
LouKeAddLousineNodeEntryToTree(
    LPWSTR      TreeName,
    LPWSTR      Entry,
    PVOID       Data
);

void
LouKeDestroyLousineNodeTree(
    PLOUSINE_NODE NodeTree
);

errno_t
LouKeCreateSourceNodes(
    PCOMPILER_CONTEXT Context
);

LPWSTR CompilerDeclarationLookup(LOU_STRING Str);

typedef errno_t (*LEXER_HANLDER)(LPWSTR Stream, size_t Length, PVOID Data);

errno_t 
LouKeLexerWcsWithTerminator(
    LPWSTR              Buffer,
    LPWSTR              OpenToken,
    LPWSTR              CloseToken,
    size_t              Length,
    LEXER_HANLDER       Handle,
    PVOID               Data
);

errno_t 
LouKeLexerWcsWithoutTerminator(
    LPWSTR              Buffer,
    LPWSTR              OpenToken,
    size_t              Length,
    LEXER_HANLDER       Handler,
    PVOID               Data
);

LPWSTR 
Lou_wcsnstr(
    LPWSTR Str,
    LPWSTR Sub,
    size_t Length
);

errno_t 
LouKeLexerGetSyntaxes(
    LPWSTR     Buffer,
    size_t      Length,
    LPWSTR*     Name,
    LPWSTR*     NameEnd,
    LPWSTR*     Declaration,
    LPWSTR*     Data,
    PVOID       Context
);

void CreateSourceDeclarationLookup(
    LPWSTR SourceName, 
    size_t SourceNameLength,
    LPWSTR CommonName,
    size_t CommonNameLength
);

#endif