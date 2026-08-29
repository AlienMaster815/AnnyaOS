#include "AtaCore.h"

/*
TODO:
    * = multiple commands under a single ATA feature
    CFA ERASE SECTORS: 
        this command is used in advance of the CFA WRITE_SECTORS_WITHOUGHT_ERASE or
        a CFA WRITE MULTIPLE WITHOUGHT ERASE command to increase execution speed  
    CFA REQUEST EXTENDED ERROR CODES:
        define error commands and create logic for error handling : ATA-ATAPI.PDF Page 80
    CFA_TRANSLATE_SECTOR:
        create structure for the Translation Information : ATA-ATAPI.PDF Page 82
    CHECK_POWER_MODE:
        handle result data : ATA-ATAPI.PDF Page 90
    DEVICE CONFIGURATION * : 
        Check over them when finished with the basics 
    IDENTIFY DEVICE:
        read all the data and behavior, implement the data and behavior: ATA-ATAPI.PDF Page 117
*/


BOOLEAN DbgPrintEn = false;

void AtaCoreDbgPrint(char* format, ...){
    if(DbgPrintEn){
        va_list args;
        va_start(args, format);
        LouPrintEx(format, args);
        va_end(args);
    }
}

LOUSTATUS AtaCoreEntry(){
    HANDLE AtaDebugKey = LouKeOpenRegistryHandle(L"KERNEL_DEFAULT_CONFIG\\DEBUG\\ATA_CORE_DEBUG", 0x00);
    BYTE DbgValue = 0;
    LouKeReadRegistryByteValue(AtaDebugKey, &DbgValue);
    DbgPrintEn = DbgValue ? true : false;

    AtaCoreDbgPrint("ATACORE.SYS:AtaCoreEntry()\n");



    AtaCoreDbgPrint("ATACORE.SYS:AtaCoreEntry():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}