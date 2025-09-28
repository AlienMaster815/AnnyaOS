#include <LouDDK.h>

static uintptr_t BootRegistryBase = 0; 
static uintptr_t BootRegistryTop = 0;

LOUDDK_API_ENTRY
void InitializeBootRegistry(uintptr_t Base, uintptr_t Top){
    BootRegistryBase = Base;
    BootRegistryTop = Top;
}

UNUSED static FILE* SystemRegistryFile = 0x00;
UNUSED static FILE* SoftwareRegistryFile = 0x00;
UNUSED static FILE* DefaultRegistryFile = 0x00;
UNUSED static FILE* UsersRegistryFile = 0x00;
UNUSED static FILE* SecurityRegistryFile = 0x00;
UNUSED static FILE* SamRegistryFile = 0x00;

static void CreateFiles(){

    //SystemRegistryFile = LouKeCreateRegistryFile(
    //    L"/ANNYA/PROFILES/DEFAULT",
    //    L"SYSTEM"
    //);

    //SoftwareRegistryFile = LouKeCreateRegistryFile(
    //    L"/ANNYA/PROFILES/DEFAULT",
    //    L"SOFTWARE"
    //);

    //DefaultRegistryFile = LouKeCreateRegistryFile(
    //    L"/ANNYA/PROFILES/DEFAULT",
    //    L"DEFAULT"
    //);

    //UsersRegistryFile = LouKeCreateRegistryFile(
    //    L"/ANNYA/PROFILES/DEFAULT",
    //    L"USERS"
    //);

    //SecurityRegistryFile = LouKeCreateRegistryFile(
    //    L"/ANNYA/PROFILES/DEFAULT",
    //    L"SECURITY"
    //);
    
    //SamRegistryFile = LouKeCreateRegistryFile(
    //    L"/ANNYA/PROFILES/DEFAULT",
    //    L"SAM"
    //);
}

LOUDDK_API_ENTRY
LOUSTATUS 
LouKeInitializeRegistrySystem(){
    LouPrint("LouKeInitializeRegistrySystem()\n");
    while(1);

    CreateFiles();

}