#include <LouAPI.h>

KERNEL_EXPORT 
LOUSTATUS 
LouKeInitializeIoCtlTable(
    PVOID Table
){
    size_t Count = 0;
    PLOU_IOCTL_TABLE_ENTRY Base = (PLOU_IOCTL_TABLE_ENTRY)Table;
    while(Base[Count].ExeName && Base[Count].FunctionName){
        Count++;
    }

    IOCTL_FUNCTION* NewDirectory = LouKeMallocArray(IOCTL_FUNCTION, Count, KERNEL_GENERIC_MEMORY);

    for(SIZE i = 0 ; i < Count; i++){
        IOCTL_FUNCTION TmpFunction = (IOCTL_FUNCTION)LouKeLinkerGetAddress(Base[i].ExeName, Base[i].FunctionName);
        if(!TmpFunction && Base[i].FailIfNotFound){
            goto _IOCTL_LINK_FAILED;
        }
        NewDirectory[i] = TmpFunction;
        Base[i].IoFunction = &NewDirectory[i];
    }
    return STATUS_SUCCESS;    
_IOCTL_LINK_FAILED:
    for(SIZE i = 0 ; i < Count; i++){
        Base[i].IoFunction = 0x00; 
    }
    LouKeFree(NewDirectory);
    return STATUS_UNSUCCESSFUL;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeCallIoCtlFunction(
    PLOU_IOCTL_TABLE_ENTRY  Entry, 
    UINT64*                 KulaPacket
){
    if(!Entry->IoFunction){
        return STATUS_UNSUCCESSFUL;
    }else if(!(*Entry->IoFunction)){
        return STATUS_UNSUCCESSFUL;
    }

    IOCTL_FUNCTION Function = *Entry->IoFunction;
    
    return Function(KulaPacket);
}