#define _SAL_INTERNALS_
#include <Sal.h>

PSAL_ALLOCATION_OBJECT_NODE SalAllocationObjectManager::AllocateNode(){
    PSAL_ALLOCATION_OBJECT_NODE NewNode = SalAllocateType(SAL_ALLOCATION_OBJECT_NODE);
    if(!NewNode){
        return NewNode;
    }
    ListAddTail(&NewNode->Peers, &this->NodeList);
    return NewNode;
}

void SalAllocationObjectManager::FreeNode(PSAL_ALLOCATION_OBJECT_NODE Node){
    if(!Node){
        return;
    }
    ListDeleteItem(&Node->Peers);
    SalFreeMemory((PVOID)Node);
}

PSAL_ALLOCATION_OBJECT SalAllocationObjectManager::_AllocateObject(){
    PSAL_ALLOCATION_OBJECT_NODE TmpNode;
    PSAL_ALLOCATION_OBJECT      Result = 0x00;
    ForEachListEntry(TmpNode, &this->NodeList, Peers){
        if(TmpNode->NodeMap == UINT64_MAX){
            continue;
        }
        for(SIZE i = 0 ; i < 64; i++){
            if(!(TmpNode->NodeMap & (1ULL << i))){
                TmpNode->NodeMap |= (1ULL << i);
                Result = &TmpNode->NodeItems[i];
                goto _DONE;
            }            
        }
    }
_DONE:
    return Result;
}

bool SalAllocationObjectManager::SetupAllocationObjectManager(){
    bool Status;
    Status = pthread_mutex_init(&this->NodeListLock, nullptr) ? false : true;
    if(!Status){
        return Status;
    }
    return true;
}

PSAL_ALLOCATION_OBJECT SalAllocationObjectManager::AllocateObject(){
    pthread_mutex_lock(&this->NodeListLock);
    PSAL_ALLOCATION_OBJECT NewObject = this->_AllocateObject();
    if(!NewObject){
        if(this->AllocateNode()){
            NewObject = this->_AllocateObject();
        }
    }
    pthread_mutex_unlock(&this->NodeListLock);
    if(NewObject){
        memset(NewObject, 0, sizeof(SAL_ALLOCATION_OBJECT));
    }
    return NewObject;
}

void SalAllocationObjectManager::FreeObject(PSAL_ALLOCATION_OBJECT Object){
    PSAL_ALLOCATION_OBJECT_NODE TmpNode;
    PSAL_ALLOCATION_OBJECT_NODE Result = 0x00;
    SIZE ObjectOffset;
    if(!Object){
        return;
    }
    pthread_mutex_lock(&this->NodeListLock);
    ForEachListEntry(TmpNode, &this->NodeList, Peers){
        if(RangeInterferes((uint64_t)TmpNode, sizeof(SAL_ALLOCATION_OBJECT_NODE), (uint64_t)Object, sizeof(SAL_ALLOCATION_OBJECT))){
            Result = TmpNode;
            goto _DONE;
        }
    }
_DONE:
    if(Result){
        ObjectOffset = (((SIZE)(UINT8*)Object) - ((SIZE)(UINT8*)&Result->NodeItems[0])) / sizeof(SAL_ALLOCATION_OBJECT);
        Result->NodeMap &= ~(1ULL << ObjectOffset); 
        if(!Result->NodeMap){
            this->FreeNode(Result);
        }
    }
    pthread_mutex_unlock(&this->NodeListLock);
}
