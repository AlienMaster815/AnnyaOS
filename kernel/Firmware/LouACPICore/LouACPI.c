//LouACPI core file and initializations
#include <LouACPI.h>

uintptr_t LouKeGetRsdp();
static uint8_t AcpiVersion = 0;

uint8_t LouKeAcpiGetVersion(){
    return AcpiVersion;
}

LOUSTATUS LouKeAcpiBuildNameSpace();

void LouKeAcpiPrintTableSignature(void* TableBase){
    PTABLE_DESCRIPTION_HEADER Table = (PTABLE_DESCRIPTION_HEADER)TableBase;
    char TableName[5] = {'\0'};
    strncpy(TableName, Table->Signature, 4);
    LouPrint("Table:%s At Address:%h\n", TableName, TableBase);
}

UNUSED static void LouACPIParseRsdt(
    PROOT_SYSTEM_DISCRIPTION_POINTER Rsdp
){
    LouPrint("Parseing Rsdt At:%h\n", Rsdp->RsdtAddress);
    PROOT_SYSTEM_DISCRIPTION_TABLE  Rsdt = (PROOT_SYSTEM_DISCRIPTION_TABLE)(uintptr_t)(Rsdp->RsdtAddress + GetKSpaceBase());

    LouKeInitializeLouACPITable((void*)(uintptr_t)Rsdt);
    FOR_EACH_PRSDT_ENTRY(Rsdt){
        LouKeInitializeLouACPITable((void*)((uintptr_t)Rsdt->DescriptionHeaders[RsdtEntry] + GetKSpaceBase()));
    }

}


UNUSED static void LouACPIParseXsdt(
    PROOT_SYSTEM_DISCRIPTION_POINTER Rsdp
){
    LouPrint("Parseing Xsdt At:%h\n", Rsdp->XsdtAddress);
    PEXTENDED_SYSTEM_DESCRIPTION_TABLE  Xsdt = (PEXTENDED_SYSTEM_DESCRIPTION_TABLE)((uintptr_t)Rsdp->XsdtAddress + GetKSpaceBase());

    LouKeInitializeLouACPITable((void*)(uintptr_t)Xsdt);

    FOR_EACH_PXSDT_ENTRY(Xsdt){
        LouKeInitializeLouACPITable((void*)((uintptr_t)Xsdt->DescriptionHeaders[XsdtEntry] + GetKSpaceBase()));
    }
}


void LouKeInitializeLouACPISubsystem(){

    LouPrint("Initializing LouACPI Subsystem\n");
    UNUSED PROOT_SYSTEM_DISCRIPTION_POINTER Rsdp = (PROOT_SYSTEM_DISCRIPTION_POINTER)(UINT8*)LouKeGetRsdp();
    LouPrint("Rsdp Version:%d\n", Rsdp->Revision);
        
    AcpiVersion = Rsdp->Revision;

    if(Rsdp->Revision > 1){
        LouACPIParseXsdt(Rsdp);
    }
    
    LouACPIParseRsdt(Rsdp);

    LouPrint("Initialization Successfull\n");
}