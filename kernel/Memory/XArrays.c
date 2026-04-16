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
    PXARRAY_NODE TmpNode;
    BOOLEAN NodePreExists = false;
    UINT64 Member;
    ForEachListEntry(TmpNode, &Array->Nodes, Peers){
        if(RangeInterferes(
            TmpNode->Base, 512,
            Index, 1
        )){
            NodePreExists = true;
            break;
        }       
    }
    if(!NodePreExists){
        return false;
    }
    Member = Index - TmpNode->Base;
    return (TmpNode->Bitmap & (1 << Member));
}

KERNEL_EXPORT
LOUSTATUS
LouKeXaGetEx(
    PXARRAY     Array,
    UINT64      Index,
    UINT64*     Out
){
    if((!Out) || (!Array)){
        return STATUS_INVALID_PARAMETER;
    }    

    PXARRAY_NODE TmpNode;
    BOOLEAN NodePreExists = false;
    UINT64 Member;
    ForEachListEntry(TmpNode, &Array->Nodes, Peers){
        if(RangeInterferes(
            TmpNode->Base, 512,
            Index, 1
        )){
            NodePreExists = true;
            break;
        }       
    }
    if(!NodePreExists){
        return STATUS_UNSUCCESSFUL;
    }

    Member = Index - TmpNode->Base;
    *Out = TmpNode->Entries[Member];
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
LOUSTATUS
LouKeXaGet(
    PXARRAY     Array,
    UINT64      Index,
    UINT64*     Out
){
    LOUSTATUS Result;
    LouKeXaLockArray(Array);
    Result = LouKeXaGetEx(
        Array,
        Index,
        Out
    );
    LouKeXaUnlockArray(Array);
    return Result;
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

KERNEL_EXPORT 
LOUSTATUS 
LouKeXarrayAllocateUint64(
    PXARRAY Array,
    UINT64* Id,
    PVOID   Entry, 
    UINT64  Limit,
    UINT64  PageFlags
){
    LouKeXaLockArray(Array);
    for(UINT64 i = 0; i < Limit; i++){
        if(!LouKeXaIsIndexUsedEx(Array, i)){
            LouKeXaStoreEx(
                Array,
                i,
                Entry,
                PageFlags
            );
            *Id = i;
            LouKeXaUnlockArray(Array);
            return STATUS_SUCCESS;
        }
    }   
    LouKeXaUnlockArray(Array);
    return STATUS_DEVICE_BUSY;
}

KERNEL_EXPORT
LOUSTATUS 
LouKeXarrayAllocateInt(
    PXARRAY Array,
    int*    Id,
    PVOID   Entry, 
    int     Limit,
    UINT64  PageFlags
){
    int i = *Id;
    if((i < 0) && (Limit > 0)){
        i = 0;
    }else if(i < 0){
        return STATUS_INVALID_PARAMETER;   
    }
    LouKeXaLockArray(Array);
    Limit = Limit ? Limit : INT32_MAX;
    for(; i <= Limit; i++){
        if(!LouKeXaIsIndexUsedEx(Array, i)){
            LouKeXaStoreEx(
                Array,
                i,
                Entry,
                PageFlags
            );
            *Id = i;
            LouKeXaUnlockArray(Array);
            return STATUS_SUCCESS;
        }
    }   
    LouKeXaUnlockArray(Array);
    return STATUS_DEVICE_BUSY;
}

KERNEL_EXPORT
LOUSTATUS 
LouKeXarrayAllocateUint32(
    PXARRAY Array,
    UINT32* Id,
    PVOID   Entry, 
    UINT32  Limit,
    UINT64  PageFlags
){
    LouKeXaLockArray(Array);
    UINT32 i = *Id;
    Limit = Limit ? Limit : UINT32_MAX;
    for(; i <= Limit; i++){
        if(!LouKeXaIsIndexUsedEx(Array, (UINT64)i)){
            LouKeXaStoreEx(
                Array,
                (UINT64)i,
                Entry,
                PageFlags
            );
            *Id = i;
            LouKeXaUnlockArray(Array);
            return STATUS_SUCCESS;
        }
    }   
    LouKeXaUnlockArray(Array);
    return STATUS_DEVICE_BUSY;
}

static void DeleteNodeIfEmpty(
    PXARRAY_NODE Node
){

    for(size_t i = 0 ; i < 64; i++){
        if(Node->Bitmap & (1 << i)){
            return;
        }
    }
    LouKeListDeleteItem(&Node->Peers);
    LouKeFree(Node);
}

KERNEL_EXPORT
void 
LouKeXaFreeUint64(
    PXARRAY Array,
    UINT64  Id
){
    LouKeXaLockArray(Array);
    PXARRAY_NODE TmpNode;
    UINT64 Member;
    ForEachListEntry(TmpNode, &Array->Nodes, Peers){
        if(RangeInterferes(
            TmpNode->Base, 512,
            Id, 1
        )){
            break;
        }       
    }

    if(!TmpNode){
        LouPrint("LouKeXaFree():Array:%h ID:%d Is Not Used\n", Array, Id);
    }else{
        Member = Id - TmpNode->Base;
        TmpNode->Entries[Member] = 0x00;
        (TmpNode->Bitmap &= ~(1 << Member));
        DeleteNodeIfEmpty(TmpNode);
    }    
    LouKeXaUnlockArray(Array);
}

KERNEL_EXPORT
void 
LouKeXaFreeUint32(
    PXARRAY Array,
    UINT32  Id
){
    LouKeXaLockArray(Array);
    PXARRAY_NODE TmpNode;
    UINT64 Member;
    ForEachListEntry(TmpNode, &Array->Nodes, Peers){
        if(RangeInterferes(
            TmpNode->Base, 512,
            (UINT64)Id, 1
        )){
            break;
        }       
    }

    if(!TmpNode){
        LouPrint("LouKeXaFree():Array:%h ID:%d Is Not Used\n", Array, Id);
    }else{
        Member = Id - TmpNode->Base;
        TmpNode->Entries[Member] = 0x00;
        (TmpNode->Bitmap &= ~(1 << Member));
        DeleteNodeIfEmpty(TmpNode);
    }    
    LouKeXaUnlockArray(Array);
}


KERNEL_EXPORT
void 
LouKeXaDestroy(
    PXARRAY Array
){
    LouKeXaLockArray(Array);
    PXARRAY_NODE TmpNode;
    PXARRAY_NODE ForwardNode;
    ForEachListEntrySafe(TmpNode, ForwardNode, &Array->Nodes, Peers){
        for(size_t i = 0 ; i < 64; i++){
            TmpNode->Entries[i] = 0x00;
            (TmpNode->Bitmap &= ~(1 << i));   
        }
        DeleteNodeIfEmpty(TmpNode); //it is
    }    
    LouKeXaUnlockArray(Array);
}