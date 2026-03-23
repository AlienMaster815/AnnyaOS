#include <LouAPI.h>


KERNEL_EXPORT
PVOID 
LouKeXaStoreEx(
    PXARRAY     Array,
    UINT64      Index,
    PVOID       Pointer,
    UINT64      PageFlags
){

    PXARRAY_NODE TmpNode = ListItemToType(Array->Nodes.NextHeader, XARRAY_NODE, Peers);

    BOOLEAN NodePreExists = false;
    UINTPTR Result;
    UINT64 Member;
    while(TmpNode){
        if(RangeInterferes(
            TmpNode->Base, 512,
            Index, 1
        )){
            NodePreExists = true;
            break;
        }       
        TmpNode = ListItemToType(TmpNode->Peers.NextHeader, XARRAY_NODE, Peers);
    }
    if(!NodePreExists){
        TmpNode = LouKeMallocType(XARRAY_NODE, PageFlags);
        LouKeListAddTail(&TmpNode->Peers, &Array->Nodes);  
    }

    TmpNode->Base = ROUND_DOWN64(Index, 512);
    Member = Index - TmpNode->Base;
    Result = TmpNode->Entries[Member];
    TmpNode->Entries[Member] = (UINT64)Pointer;
    TmpNode->Bitmap |= (1 << Member);

    return (PVOID)Result;
}

KERNEL_EXPORT
BOOLEAN 
LouKeXaIsIndexUsedEx(
    PXARRAY     Array,
    UINT64      Index
){
    PXARRAY_NODE TmpNode = ListItemToType(Array->Nodes.NextHeader, XARRAY_NODE, Peers);
    BOOLEAN NodePreExists = false;
    UINT64 Member;
    while(TmpNode){
        if(RangeInterferes(
            TmpNode->Base, 512,
            Index, 1
        )){
            NodePreExists = true;
            break;
        }       
        TmpNode = ListItemToType(TmpNode->Peers.NextHeader, XARRAY_NODE, Peers);
    }
    if(!NodePreExists){
        return false;
    }
    Member = Index - TmpNode->Base;
    return (TmpNode->Bitmap & (1 << Member));
}

KERNEL_EXPORT
BOOLEAN 
LouKeXaIsIndexUsed(
    PXARRAY     Array,
    UINT64      Index
){ 
    BOOLEAN Result;
    LouKeXaLockArray(Array);
    Result = LouKeXaIsIndexUsedEx(
        Array,
        Index
    );
    LouKeXaUnlockArray(Array);
    return Result;
}

KERNEL_EXPORT
PVOID 
LouKeXaStore(
    PXARRAY     Array,
    UINT64      Index,
    PVOID       Pointer,
    UINT64      PageFlags
){
    PVOID Result;
    LouKeXaLockArray(Array);
    Result = LouKeXaStoreEx(Array, Index, Pointer, PageFlags);
    LouKeXaUnlockArray(Array);
    return Result;
}