#include <LouAPI.h>

typedef struct _CACHE_MANAGER_HANDLE{
    ListHeader    Peers;
    SIZE          TotalCacheMembers;
    SIZE          UsedCacheMembers;
    SIZE          MemberSize;
    SIZE          MemberAlignment;
    UINT64        PageFlags;
    mutex_t       LockOutTagOut;
    PVOID         Pointers[];
}CACHE_MANAGER_HANDLE, * PCACHE_MANAGER_HANDLE;

static mutex_t GlobalCacheManagerLota = {0};
static ListHeader GlobalCacheManagerList = {0};

PCACHE_MANAGER_HANDLE LouKeCreateCacheManager(
    SIZE     TotalCacheMembers,
    SIZE     MemberSize,
    SIZE     MemberAlignment,
    UINT64   PageFlags
){
    PCACHE_MANAGER_HANDLE NewCacheHandle = LouKeMallocEx(GetStructureSize(CACHE_MANAGER_HANDLE, Pointers, TotalCacheMembers), GET_ALIGNMENT(CACHE_MANAGER_HANDLE), KERNEL_GENERIC_MEMORY);
    NewCacheHandle->TotalCacheMembers = TotalCacheMembers;
    NewCacheHandle->UsedCacheMembers = 0;
    NewCacheHandle->MemberSize = MemberSize;
    NewCacheHandle->MemberAlignment = MemberAlignment;
    NewCacheHandle->PageFlags = PageFlags;
    MutexLock(&GlobalCacheManagerLota);
    LouKeListAddTail(&NewCacheHandle->Peers, &GlobalCacheManagerList);
    MutexUnlock(&GlobalCacheManagerLota);
    return NewCacheHandle;
}

PVOID LouKeCacheManagerAllocate(
    PCACHE_MANAGER_HANDLE CacheHandle
){
    PVOID  Result = 0x00;
    MutexLock(&CacheHandle->LockOutTagOut);
    if(CacheHandle->UsedCacheMembers){
        Result = CacheHandle->Pointers[--CacheHandle->UsedCacheMembers];
    }
    MutexUnlock(&CacheHandle->LockOutTagOut);
    if(!Result){
        Result = LouKeMallocEx(CacheHandle->MemberSize, CacheHandle->MemberAlignment, CacheHandle->PageFlags);
    }
    return Result;
}

void LouKeCacheManagerFree(
    PVOID                 CacheMember,
    PCACHE_MANAGER_HANDLE CacheHandle
){
    if(CacheHandle->UsedCacheMembers >= CacheHandle->TotalCacheMembers){
	LouKeFree(CacheMember);
        return;
    }
    MutexLock(&CacheHandle->LockOutTagOut);
    CacheHandle->Pointers[CacheHandle->UsedCacheMembers++] = CacheMember;
    MutexUnlock(&CacheHandle->LockOutTagOut);
}
