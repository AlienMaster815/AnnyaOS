//Copyright GPL-2 Tyler Grenier (2024 - 2026)
#include <LouDDK.h>

static void AcquireListLock(PLIST_OBJECT Object){
    MutexLock(&Object->Lock);
}

static void ReleaseListLock(PLIST_OBJECT Object){
    MutexUnlock(&Object->Lock);
}

static PLIST_LINK LouKeGetLinkHeader(PLIST_OBJECT ListObject){
    if(!ListObject->Initialized){
        ListObject->Head.FLink = &ListObject->Head;
        ListObject->Head.BLink = &ListObject->Head;
        ListObject->Initialized = true;
    }
    return &ListObject->Head;
}

void LouKeLinkObjectToListHead(PLIST_OBJECT ListObject, PLIST_LINK Link){
    AcquireListLock(ListObject);
    PLIST_LINK Head = LouKeGetLinkHeader(ListObject);
    PLIST_LINK NewObj = (PLIST_LINK)Link;
    NewObj->FLink = Head->FLink; 
    Head->FLink->BLink = NewObj;
    NewObj->BLink = Head;
    Head->FLink = NewObj;
    ReleaseListLock(ListObject);
}

void LouKeLinkObjectToListTail(PLIST_OBJECT ListObject, PLIST_LINK Link){
    AcquireListLock(ListObject);
    PLIST_LINK Head = LouKeGetLinkHeader(ListObject);
    PLIST_LINK NewObj = (PLIST_LINK)Link;
    NewObj->FLink = Head;
    Head->BLink->FLink = NewObj;
    NewObj->BLink = Head->BLink;
    Head->BLink = NewObj;
    ReleaseListLock(ListObject);
}
void LouKeUnlinkObjectFromList(PLIST_OBJECT ListObject, PLIST_LINK Link){
    AcquireListLock(ListObject);
    PLIST_LINK BLink = Link->BLink;
    PLIST_LINK FLink = Link->FLink;
    BLink->FLink = FLink->FLink;
    FLink->BLink = BLink;
    ReleaseListLock(ListObject);
}

void* LouKeLinkGetMemberWithFunction(PLIST_OBJECT ListObject, LIST_SEARCH_FUNC Func, void* Param){
    AcquireListLock(ListObject);
    PLIST_LINK Head = LouKeGetLinkHeader(ListObject);
    PLIST_LINK TmpLink = Head->FLink; 
    while(TmpLink && TmpLink != Head){
        if(Func(TmpLink, Param)){
            ReleaseListLock(ListObject);
            return TmpLink;
        }
        TmpLink = TmpLink->FLink;
    }
    ReleaseListLock(ListObject);
    return 0x00;
}