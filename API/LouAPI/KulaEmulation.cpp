#include <LouDDK.h>

LOUDDK_API_ENTRY
int toupper(int c);

KULA_TABLE_TRACKER MasterTracker = {0};

PVOID 
LouKeGetKulaEmulatedFunctionN(
    string BinaryName, 
    string FunctionName
){


    PKULA_TABLE_TRACKER Tmp = &MasterTracker;
    while(Tmp->Peers.NextHeader){
        Tmp = (PKULA_TABLE_TRACKER)Tmp->Peers.NextHeader;
        for(size_t i = 0 ; i < Tmp->Table->TableMembers; i++){
            if(!strcmp(BinaryName, Tmp->Table->Entries[i].BinaryName)){
                size_t Members = Tmp->Table->Entries[i].Members;
                KULA_RVA_NAMES Names = Tmp->Table->Entries[i].Names;
                KULA_RVA_ADDRESSES Rvas = Tmp->Table->Entries[i].Rvas; 
                for(size_t j = 0; j < Members; j++){
                    if(!strcmp(Names[j], FunctionName)){
                        return Rvas[j];
                    }
                }
            }
        }
    }
    return 0x00;
}

PVOID 
LouKeGetKulaEmulatedFunctionH(
    HANDLE BinaryHandle, 
    string FunctionName
){
    //PKULA_TABLE_TRACKER Tmp;
    PKULA_TBALE_ENTRIES Entry = (PKULA_TBALE_ENTRIES)BinaryHandle;
    string BinaryName = Entry->BinaryName;
    return LouKeGetKulaEmulatedFunctionN(BinaryName, FunctionName);
}


HANDLE 
LouKeGetKulaEmulatedHandle(
    string BinaryName
){
    PKULA_TABLE_TRACKER Tmp = &MasterTracker;
    while(Tmp->Peers.NextHeader){
        Tmp = (PKULA_TABLE_TRACKER)Tmp->Peers.NextHeader;
        for(size_t i = 0 ; i < Tmp->Table->TableMembers; i++){
            if(!strcmp(BinaryName, Tmp->Table->Entries[i].BinaryName)){
                return (HANDLE)&Tmp->Table->Entries[i];
            }
        }
    }
    return 0x00;
}


LOUDDK_API_ENTRY    
void
LouKeInitializeKulaEmulatedFunctions(
    string      HostBinary,
    PKULA_TABLE Table
){
    PKULA_TABLE_TRACKER Tmp = &MasterTracker;
    for(size_t i = 0 ; i < Table->TableMembers; i++){
        size_t Length = strlen(Table->Entries[i].BinaryName);
        for(size_t Foo = 0 ; Foo < Length; Foo++){
            Table->Entries[i].BinaryName[Foo] = toupper(Table->Entries[i].BinaryName[Foo]);
        }
    }
    while(Tmp->Peers.NextHeader){
        Tmp = (PKULA_TABLE_TRACKER)Tmp->Peers.NextHeader;
    }
    Tmp->Peers.NextHeader = (PListHeader)LouKeMallocType(KULA_TABLE_TRACKER, KERNEL_GENERIC_MEMORY);
    Tmp = (PKULA_TABLE_TRACKER)Tmp->Peers.NextHeader;
    Tmp->Table = Table;
    Tmp->HostBinary = LouKeMallocArray(CHAR, strlen(HostBinary) + 1, KERNEL_GENERIC_MEMORY);
    strncpy(Tmp->HostBinary, HostBinary, strlen(HostBinary));
}

void
LouKeDeInitializeKulaEmulatedFunctions(
    string      HostBinary
){
    PKULA_TABLE_TRACKER Last = &MasterTracker;
    PKULA_TABLE_TRACKER Tmp = &MasterTracker;
    while(Tmp->Peers.NextHeader){
        Tmp = (PKULA_TABLE_TRACKER)Tmp->Peers.NextHeader;
        if(!strcmp(HostBinary, Tmp->HostBinary)){
            Last->Peers.NextHeader = Tmp->Peers.NextHeader;
            LouKeFree(Tmp->HostBinary);
        }
        Last = Tmp;
    }
}