#include "ObjectManager.h"

static mutex_t          ObjectHeaderLock = {0};
static OBJECT_HEADER    ObjectHeaderList = {0};

static POBJECT_HEADER GetObjectHeaderFromName(LOUSTR Name){
    POBJECT_HEADER TmpHeader = &ObjectHeaderList;
    MutexLock(&ObjectHeaderLock);
    while(TmpHeader->Peers.NextHeader){
        TmpHeader = (POBJECT_HEADER)TmpHeader->Peers.NextHeader;
        if(!strcmp(TmpHeader->ObjectName, Name)){
            MutexUnlock(&ObjectHeaderLock);
            return TmpHeader;
        }
    }
    MutexUnlock(&ObjectHeaderLock);
    return 0x00;
}


static POBJECT_HEADER GetObjectHeaderFromObject(PVOID Object){
    POBJECT_HEADER TmpHeader = &ObjectHeaderList;
    MutexLock(&ObjectHeaderLock);
    while(TmpHeader->Peers.NextHeader){
        TmpHeader = (POBJECT_HEADER)TmpHeader->Peers.NextHeader;
        if(TmpHeader->ObjectPointer == Object){
            MutexUnlock(&ObjectHeaderLock);
            return TmpHeader;
        }
    }
    MutexUnlock(&ObjectHeaderLock);
    return 0x00;
}

BOOLEAN ObjectHeaderInObjectManager(POBJECT_HEADER Header){
    return (Header == GetObjectHeaderFromObject(Header->ObjectPointer));
}

static void LinkObjectHeaderToList(
    POBJECT_HEADER  NewObject
){
    POBJECT_HEADER TmpHeader = &ObjectHeaderList;
    MutexLock(&ObjectHeaderLock);
    while(TmpHeader->Peers.NextHeader){
        TmpHeader = (POBJECT_HEADER)TmpHeader->Peers.NextHeader;
    }
    TmpHeader->Peers.NextHeader = (PListHeader)NewObject;
    MutexUnlock(&ObjectHeaderLock);
}

static void UnLinkObjectHeaderFromList(POBJECT_HEADER Object){
    POBJECT_HEADER TmpHeader = &ObjectHeaderList;
    POBJECT_HEADER Follower;
    MutexLock(&ObjectHeaderLock);
    while(TmpHeader->Peers.NextHeader){
        Follower = TmpHeader;
        TmpHeader = (POBJECT_HEADER)TmpHeader->Peers.NextHeader;
        if(TmpHeader == Object){
            Follower->Peers.NextHeader = TmpHeader->Peers.NextHeader;
            MutexUnlock(&ObjectHeaderLock);
            return;
        }

    }
    MutexUnlock(&ObjectHeaderLock);
}

UNUSED static LOUSTATUS ObjectHeaderConstructor(PVOID Object, PVOID Params){
    POBJECT_HEADER NewObject = (POBJECT_HEADER)Object;
    POBJHDR_CONSTRUCTOR_PARAMS ConstructData = (POBJHDR_CONSTRUCTOR_PARAMS)Params;
    int MaxHandles = ConstructData->MaxHandles;

    NewObject->ObjectPointer = ConstructData->ObjectPointer;
    NewObject->ObjectSize = ConstructData->ObjectSize;

    if(ConstructData->ObjectName){
        NewObject->ObjectName = LouKeMallocArray(CHAR, strlen(ConstructData->ObjectName) + 1, KERNEL_GENERIC_MEMORY);
        strcpy(NewObject->ObjectName, ConstructData->ObjectName);
    }

    if(MaxHandles){
        //TODO: Create A LouKeSetReferenceValue Function For This
        for(int i = 0 ; i < MaxHandles; i++){
            LouKeAcquireReference(&NewObject->MaxHandles);
        }
    }

    if(ConstructData->SecurityDescriptor){
        memcpy(&NewObject->SecurityDescriptor, ConstructData->SecurityDescriptor, sizeof(SECURITY_DESCRIPTOR));
    }


    NewObject->ObjectHandles.Header = NewObject;
    
    LouKeNotifyHandleOfAcquisition(&NewObject->ObjectHandles);

    LinkObjectHeaderToList(NewObject);

    return STATUS_SUCCESS;
}

UNUSED static LOUSTATUS ObjectHeaderDeConstructor(PVOID Object){
    POBJECT_HEADER OldObject = (POBJECT_HEADER)Object;

    UnLinkObjectHeaderFromList(OldObject);

    if(OldObject->ObjectName){
        LouKeFree(OldObject->ObjectName);
    }

    

    return STATUS_SUCCESS;
}

LOUSTATUS LouKeObjManInitialize(){
    LouPrint("LouKeObjManInitialize()\n");
    LOUSTATUS Status;
    
    LouPrint("Initializing Header Class\n");
    Status = LouKeCreateFastObjectClassEx(
        "OBJECT_HEADER",
        512, //cached object count can be changed later
        sizeof(OBJECT_HEADER),
        GET_ALIGNMENT(OBJECT_HEADER),
        0,
        KERNEL_GENERIC_MEMORY,
        ObjectHeaderConstructor,
        ObjectHeaderDeConstructor
    );

    if(Status != STATUS_SUCCESS){
        LouPrint("LouKeObjManInitialize():Failed To Create Fast Object\n");
        return Status;
    }
    
    LouPrint("Successfully Initialized Header Class\n");

    LouPrint("LouKeObjManInitialize() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS LouKeRegisterObjectToObjectManager(
    PVOID                   ObjectPointer,
    SIZE                    ObjectSize,
    LOUSTR                  ObjectName,
    int                     MaxHandles,
    PSECURITY_DESCRIPTOR    SecurityDescriptor
){
    OBJHDR_CONSTRUCTOR_PARAMS NewObjectParams = {0};

    NewObjectParams.ObjectPointer = ObjectPointer;
    NewObjectParams.ObjectSize = ObjectSize;
    NewObjectParams.ObjectName = ObjectName;
    NewObjectParams.SecurityDescriptor = SecurityDescriptor;
    NewObjectParams.MaxHandles = MaxHandles;


    LouKeAllocateFastObjectEx("OBJECT_HEADER", (PVOID)&NewObjectParams);

    return STATUS_SUCCESS;
}

void LouKeUnRegisterObjectToObjectManager(
    POBJECT_HEADER Header
){
    LouKeFreeFastObject("OBJECT_HEADER", Header);
}

LOUSTATUS LouKeGetObjectHeaderByName(
    LOUSTR  ObjectName,
    PVOID*  ObjectHeader
){
    if((!ObjectHeader) || (!ObjectName)){
        LouPrint("LouKeGetObjectHeaderByName() EINVAL\n");
        if(!ObjectName)LouPrint("ObjectName Is NULL\n");
        if(!ObjectHeader)LouPrint("ObjectHeader Is NULL\n");
        return STATUS_INVALID_PARAMETER;
    }    

    *ObjectHeader = GetObjectHeaderFromName(ObjectName);

    return ((*ObjectHeader) ? STATUS_SUCCESS : STATUS_UNSUCCESSFUL);
}

LOUSTATUS LouKeAcquireHandleForObject(
    PHANDLE     OutHandle,
    PVOID       Object, 
    ACCESS_MASK RequestedAccess
){
    if((!Object) || (!OutHandle)){
        LouPrint("LouKeAcquireHandleForObject() EINVAL\n");
        if(!Object)LouPrint("Object Is NULL\n");
        if(!OutHandle)LouPrint("OutHandle Is NULL\n");
        return STATUS_INVALID_PARAMETER;
    }

    PLOUSINE_ACCESS_TOKEN AccessToken;
    LOUSTATUS Status = LouKeZwGetAccessTokenData(&AccessToken, LouKePsmGetCurrentProcessAccessToken());
    if((Status != STATUS_SUCCESS) || (!AccessToken)){
        LouPrint("CreateHandleForObject() Unable To Get Token\n");
        return Status;
    }

    if(AccessToken->SystemAccessToken){
        return LouKeZwAcquireHandleForObjectEx(
            OutHandle,
            Object
        );
    }

    Status = LouKeCheckRequestedAccessToProcessAccessToken(RequestedAccess);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    POBJECT_HEADER ObjectHeader = GetObjectHeaderFromObject(Object);
    
    if(!ObjectHeader){
        LouPrint("LouKeAcquireHandleForObject() ObjectHeader NULL\n");
        return STATUS_UNSUCCESSFUL;
    }

    return LouKeCreateHandleForObject(
        (POBJECT_HANDLE*)OutHandle,
        ObjectHeader,
        RequestedAccess
    );
}

LOUSTATUS 
LouKeZwReleaseHandleFromObject(
    POBJECT_HANDLE  ObjectHandle,
    BOOLEAN*        ReleasedObject
){
    POBJECT_HEADER ObjectHeader = LouKeGetObjectHeaderFromHandle(ObjectHandle);
    if(!ObjectHeader){
        return STATUS_UNSUCCESSFUL;
    }

    LouKeNotifyHandleOfRelease(ObjectHandle);
    LouKeReleaseReference(&ObjectHeader->Handles);
    
    if(ReleasedObject){
        *ReleasedObject = LouKeGetReferenceCount(&ObjectHeader->Handles) ? false : true;
    }

    return STATUS_SUCCESS;
}



LOUSTATUS LouKeZwAcquireHandleForObjectEx(
    PHANDLE     OutHandle,
    PVOID       Object
){
    if((!Object) || (!OutHandle)){
        LouPrint("LouKeAcquireHandleForObjectEx() EINVAL\n");
        if(!Object)LouPrint("Object Is NULL\n");
        if(!OutHandle)LouPrint("OutHandle Is NULL\n");
        return STATUS_INVALID_PARAMETER;
    }

    UNUSED POBJECT_HEADER ObjectHeader = GetObjectHeaderFromObject(Object);
    LouKeNotifyHandleOfAcquisition(&ObjectHeader->ObjectHandles);
    LouKeAcquireReference(&ObjectHeader->Handles);
    *OutHandle = &ObjectHeader->ObjectHandles;
    return STATUS_SUCCESS;
}

LOUSTATUS LouKeZwAcquireHandleForObject(
    PHANDLE     OutHandle,
    PVOID       Object
){
    return LouKeZwAcquireHandleForObjectEx(
        OutHandle, 
        Object
    );
}

void LouKeDestroyHandleFromObject(POBJECT_HANDLE ObjectHandle);

LOUSTATUS LouKeReleaseHandleFromObject(HANDLE Handle, BOOLEAN* ReleasedObject){
    PLOUSINE_ACCESS_TOKEN AccessToken;
    LOUSTATUS Status = LouKeZwGetAccessTokenData(&AccessToken, LouKePsmGetCurrentProcessAccessToken());
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    if(AccessToken->SystemAccessToken){
        return LouKeZwReleaseHandleFromObject(
            (POBJECT_HANDLE)Handle,
            ReleasedObject
        );
    }



    //LouKeDestroyHandleFromObject((POBJECT_HANDLE)Handle);
    LouPrint("LouKeReleaseHandleFromObject()\n");
    while(1);
    return STATUS_SUCCESS;
}
