#include <LouDDK.h>

typedef enum{
    GenericLessThan     = 0,
    GenericGreaterThan  = 1,
    GenericEqual        = 2,
}_RTL_GENERIC_COMPARE_RESULT, RTL_GENERIC_COMPARE_RESULT, * PRTL_GENERIC_COMPARE_RESULT;

typedef RTL_GENERIC_COMPARE_RESULT(*PRTL_GENERIC_COMPARE_ROUTINE)(struct _RTL_GENERIC_TABLE* Table, PVOID FirstStructure, PVOID SecondStructure);
typedef PVOID(*PRTL_GENERIC_ALLOCATE_ROUTINE)(struct _RTL_GENERIC_TABLE* Table, CLONG ByteSize);
typedef VOID(*PRTL_GENERIC_FREE_ROUTINE)(struct _RTL_GENERIC_TABLE* Table, PVOID Buffer);

typedef struct _RTL_SPLAY_LINKS{
    struct _RTL_SPLAY_LINKS*    Parent;
    struct _RTL_SPLAY_LINKS*    Left;
    struct _RTL_SPLAY_LINKS*    Right;
}RTL_SPLAY_LINKS, * PRTL_SPLAY_LINKS;

typedef struct _NT_LIST_ENTRY{
    struct _NT_LIST_ENTRY*      ForwardLink;
    struct _NT_LIST_ENTRY*      BackwardLink;
}NT_LIST_ENTRY, * PNT_LIST_ENTRY;

typedef struct _RTL_GENERIC_TABLE{
    PRTL_SPLAY_LINKS                TableRoot;
    NT_LIST_ENTRY                   InsertOrderList;
    PNT_LIST_ENTRY                  OrderPointer;
    ULONG                           WhichOrderElement;
    ULONG                           NumberGenricTableElements;
    PRTL_GENERIC_COMPARE_ROUTINE    CompareRoutine;
    PRTL_GENERIC_ALLOCATE_ROUTINE   AllocationRoutine;
    PRTL_GENERIC_FREE_ROUTINE       FreeRoutine;
    PVOID                           TableContext;
}RTL_GENERIC_TABLE, * PRTL_GENERIC_TABLE;
