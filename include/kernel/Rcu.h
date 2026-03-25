#ifndef _RCU_H
#define _RCU_H

struct _SRCU_NODE_LIST_ITEM;

typedef struct _SRCU_NODE{
    ATOMIC64        CurrentWriteItem; //this becomes the ReadItem when the Reader Count goes to 0 and is set to 0
    ATOMIC64        CurrentReadItem;
    ATOMIC64        ReaderCount;
    struct{
        ATOMIC64    CurrentReadItem; //this checks against the current Write item to see if its poisoned
    }               PerCpuRcuData[]; //depends on cpu count
}SRCU_NODE, * PSRCU_NODE, 
    RCU_NODE, * PRCU_NODE;

typedef struct _SRCU_NODE_LIST_ITEM{
    BOOLEAN                 Sleepable;
    KERNEL_EVENT_OBJECT     SyncSleeperWakeEvent;
    void                    (*FreeReadItemWorker)(struct _SRCU_NODE_LIST_ITEM* Context);
    SRCU_NODE               SRcuItem;
}SRCU_NODE_LIST_ITEM, * PSRCU_NODE_LIST_ITEM;

FORCE_INLINE
BOOLEAN
IsRcuPoisoned(PSRCU_NODE Node, UINT64* New){
    UINT64 TmpOld = LouKeGetAtomic64(&Node->CurrentWriteItem); 
    if(TmpOld){
        *New = TmpOld;
        return true;
    }
    return false;
}

typedef struct _SRCU_MANAGER{
    mutex_t         SRcuManagerLock;
    ListHeader      SRcus;
}SRCU_MANAGER, * PSRCU_MANAGER;

#endif