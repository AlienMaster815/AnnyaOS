#include "Blkdev.h"

BOOLEAN DbgPrintEn = false;

void BlkDevDbgPrint(char* format, ...){
    if(DbgPrintEn){
        va_list args;
        va_start(args, format);
        LouPrintEx(format, args);
        va_end(args);
    }
}


LOUSTATUS BlkDevEntry(){
    HANDLE BlkDebugKey = LouKeOpenRegistryHandle(L"KERNEL_DEFAULT_CONFIG\\DEBUG\\BLKDEV_DEBUG", 0x00);
    BYTE DbgValue = 0;
    LouKeReadRegistryByteValue(BlkDebugKey, &DbgValue);
    DbgPrintEn = DbgValue ? true : false;

    BlkDevDbgPrint("BLKDEV.SYS:Hello World!!!\n");

    

    return STATUS_SUCCESS;
}