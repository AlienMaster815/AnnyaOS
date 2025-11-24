#include <LouAPI.h>

typedef struct _BOOT_DRIVER_LIST{
    ListHeader  Peers;
    uintptr_t   Base;
    uintptr_t   Top;
}BOOT_DRIVER_LIST, * PBOOT_DRIVER_LIST;

static BOOT_DRIVER_LIST BootDriverList = {0};
static size_t BootCount = 0;

void AddDriverToBootDeviceManager(uintptr_t Base, uintptr_t Top){
    PBOOT_DRIVER_LIST Tmp = &BootDriverList;
    while(Tmp->Peers.NextHeader){
        Tmp = (PBOOT_DRIVER_LIST)Tmp->Peers.NextHeader;
    }
    Tmp->Base = Base;
    Tmp->Top = Top;
    Tmp->Peers.NextHeader = (PListHeader)LouKeMallocType(BOOT_DRIVER_LIST, KERNEL_GENERIC_MEMORY);
    BootCount++;
}


void* LouKeGetBootDevice(size_t Index){
    size_t i = 0;
    PBOOT_DRIVER_LIST Tmp = &BootDriverList;
    for(; i < Index && Tmp->Peers.NextHeader; i++){
        Tmp = (PBOOT_DRIVER_LIST)Tmp->Peers.NextHeader;
    }
    return (i == Index) ? (void*)Tmp->Base : 0x00;
} 

size_t LouKeGetBootDeviceSize(size_t Index){
    size_t i = 0;
    PBOOT_DRIVER_LIST Tmp = &BootDriverList;
    for(; i < Index && Tmp->Peers.NextHeader; i++){
        Tmp = (PBOOT_DRIVER_LIST)Tmp->Peers.NextHeader;
    }
    return (i == Index) ? (size_t)Tmp->Top : 0x00;
} 


size_t GetBootDeviceCount(){
    return BootCount;
}