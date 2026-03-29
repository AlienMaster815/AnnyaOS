#include "../DrsdCore.h"

static SIZE TtmGlobalPageCount = 0;

static TTM_POOL_TYPE GlobalWriteCombined[NR_PAGE_ORDERS];
static TTM_POOL_TYPE GlobalUncached[NR_PAGE_ORDERS];
static TTM_POOL_TYPE GlobalDma32WriteCombined[NR_PAGE_ORDERS];
static TTM_POOL_TYPE GlobalDma32Uncached[NR_PAGE_ORDERS];

static 
void
TtmPoolTypeInitialize(
    PTTM_POOL_TYPE      PoolType,
    PTTM_POOL           Pool,
    TTM_CACHING         Caching,
    UINT                Order
){

    PoolType->Pool = Pool;
    PoolType->Caching = Caching;
    PoolType->Order = Order;
  
    //TODO: Add shrinker

} 

static 
void
TtmPoolTypeDeInitialize(
    PTTM_POOL_TYPE      PoolType
){
    LouPrint("TtmPoolTypeDeInitialize()\n");
    while(1);   
}

static 
PTTM_POOL_TYPE
TtmPoolSelectType(
    PTTM_POOL   Pool,
    TTM_CACHING Caching,
    UINT        Order
){
    if(TtmPoolUsesDmaAlloc(Pool)){
        return &Pool->Caching[Caching].Orders[Order];
    }
    switch(Caching){
    case TtmWriteCombined:
        if(Pool->Nid){
            return &Pool->Caching[Caching].Orders[Order];
        }
        if(TtmPoolUsesDma32(Pool)){
            return &GlobalDma32WriteCombined[Order];
        }
        return &GlobalWriteCombined[Order];
    case TtmUncached:
            if(Pool->Nid){
            return &Pool->Caching[Caching].Orders[Order];
        }
        if(TtmPoolUsesDma32(Pool)){
            return &GlobalDma32Uncached[Order];
        }
        return &GlobalUncached[Order];
    default:
        break;
    }
    return 0x00;
}

DRIVER_EXPORT
void 
TtmPoolInitialize(
    PTTM_POOL           Pool,
    PLATFORM_DEVICE     Device,
    int                 Nid,
    UINT64              AllocationFlags
){
    UINT i, j;

    Pool->Device = Device;
    Pool->Nid = Nid;
    Pool->AllocationFlags = AllocationFlags;

    for(i = 0 ; i < TTM_NUM_CACHING_TYPES; ++i){
        for(j = 0 ; j < NR_PAGE_ORDERS; ++j){
            PTTM_POOL_TYPE PoolType;    
            PoolType = TtmPoolSelectType(Pool, i, j);
            if(PoolType != &Pool->Caching[i].Orders[j]){
                continue;
            }
            TtmPoolTypeInitialize(PoolType, Pool, i, j);       
        }
    }
}

LOUSTATUS 
TtmPoolManagerInitialize(
    SIZE PageCount
){
    UINT i;
    if(!TtmGlobalPageCount){
        TtmGlobalPageCount = PageCount;
    }

    for(i = 0 ; i < NR_PAGE_ORDERS; ++i){
        TtmPoolTypeInitialize(&GlobalWriteCombined[i], 0x00, TtmWriteCombined, i);
        TtmPoolTypeInitialize(&GlobalUncached[i], 0x00, TtmUncached, i);
        TtmPoolTypeInitialize(&GlobalDma32WriteCombined[i], 0x00, TtmWriteCombined, i);
        TtmPoolTypeInitialize(&GlobalDma32Uncached[i], 0x00, TtmUncached, i);
    }    

    return STATUS_SUCCESS;
}

void 
TtmPoolManagerDeInitialize(){
    UINT i;
    for(i = 0; i < NR_PAGE_ORDERS; ++i){
        TtmPoolTypeDeInitialize(&GlobalWriteCombined[i]);
        TtmPoolTypeDeInitialize(&GlobalUncached[i]);
        TtmPoolTypeDeInitialize(&GlobalDma32WriteCombined[i]);
        TtmPoolTypeDeInitialize(&GlobalDma32Uncached[i]);
    }
}