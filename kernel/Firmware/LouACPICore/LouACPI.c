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

static void LouACPIParseRsdt(
    PROOT_SYSTEM_DISCRIPTION_POINTER Rsdp
){
    LouPrint("Parseing Rsdt At:%h\n", Rsdp->RsdtAddress);
    uint64_t RsdtPhyCheck;
    PROOT_SYSTEM_DISCRIPTION_TABLE  Rsdt = (PROOT_SYSTEM_DISCRIPTION_TABLE)(uintptr_t)Rsdp->RsdtAddress;
    RequestPhysicalAddress((uint64_t)Rsdt, &RsdtPhyCheck);
    if((uint64_t)Rsdt != RsdtPhyCheck){
        //this should also not happen
        LouPrint("Rsdt:%h RsdtPhyCheck:%h\n", Rsdt, RsdtPhyCheck);
        while(1);
    }

    LouKeInitializeLouACPITable((void*)(uintptr_t)Rsdt);
    FOR_EACH_PRSDT_ENTRY(Rsdt){
        LouKeInitializeLouACPITable((void*)(uintptr_t)Rsdt->DescriptionHeaders[RsdtEntry]);
    }

}


UNUSED static void LouACPIParseXsdt(
    PROOT_SYSTEM_DISCRIPTION_POINTER Rsdp
){
    LouPrint("Parseing Xsdt At:%h\n", Rsdp->XsdtAddress);
    uint64_t XsdtPhyCheck;
    PEXTENDED_SYSTEM_DESCRIPTION_TABLE  Xsdt = (PEXTENDED_SYSTEM_DESCRIPTION_TABLE)(uintptr_t)Rsdp->XsdtAddress;
    RequestPhysicalAddress((uint64_t)Xsdt, &XsdtPhyCheck);
    if((uint64_t)Xsdt != XsdtPhyCheck){
        //this should also not happen
        LouPrint("Xsdt:%h XsdtPhyCheck:%h\n", Xsdt, XsdtPhyCheck);
        while(1);
    }

    LouKeInitializeLouACPITable((void*)(uintptr_t)Xsdt);

    FOR_EACH_PXSDT_ENTRY(Xsdt){
        LouKeInitializeLouACPITable((void*)(uintptr_t)Xsdt->DescriptionHeaders[XsdtEntry]);
    }
}


void LouKeInitializeLouACPISubsystem(){

    LouPrint("Initializing LouACPI Subsystem\n");
    PROOT_SYSTEM_DISCRIPTION_POINTER Rsdp = 0x00;

    uint64_t RsdpPhy = (uint64_t)LouKeGetRsdp();
    uint64_t RsdpPhyCheck;
    RequestPhysicalAddress(RsdpPhy, &RsdpPhyCheck);
    if(RsdpPhy != RsdpPhyCheck){
        //this should never happen
        LouPrint("RsdpPhy:%h RsdpMap:%h\n", RsdpPhy, RsdpPhyCheck);
        while(1);
    }
    
    Rsdp = (PROOT_SYSTEM_DISCRIPTION_POINTER)RsdpPhy;
    LouPrint("Rsdp Version:%d\n", Rsdp->Revision);
    
    AcpiVersion = Rsdp->Revision;

    if(Rsdp->Revision > 1){
        LouACPIParseXsdt(Rsdp);
    }
    LouACPIParseRsdt(Rsdp);

    LouPrint("Initialization Successfull\n");
}