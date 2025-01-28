#include <LouAPI.h>


static spinlock_t UserMallocLock;

void LouUserMalloc(uint64_t DataP){
    LouKIRQL LouIrql;
    LouKeAcquireSpinLock(&UserMallocLock, &LouIrql);
    uint64_t size = *(uint64_t*)DataP;
    *(uint64_t*)DataP = (uint64_t)LouKeMalloc(size, USER_PAGE | WRITEABLE_PAGE | PRESENT_PAGE);
    
    LouKeReleaseSpinLock(&UserMallocLock, &LouIrql);
    return;//Endof SYSTEMCALL
}

void LouUserFree(uint64_t DataP){
    LouKIRQL LouIrql;
    LouKeAcquireSpinLock(&UserMallocLock, &LouIrql);

    uint64_t size = *(uint64_t*)DataP;
    LouKeFree((void*)size);

    while(1);
    LouKeReleaseSpinLock(&UserMallocLock, &LouIrql);
    return;//Endof SYSTEMCALL
}

void LouKeUserFree(void* AddressToFree){
    uint64_t Data = (uint64_t)AddressToFree;
    LouUserFree((uint64_t)&Data);
    return;
}

void* LouKeUserMalloc(size_t NumberOfBytes){
    uint64_t Foo = NumberOfBytes;
    LouUserMalloc((uint64_t)&Foo);
    return (void*)Foo;
}