#ifndef ATA_CORE_H
#define ATA_CORE_H

#define _KERNEL_MODULE_

#include <LouDDK.h>

void AtaCoreDbgPrint(char* format, ...);

typedef struct _ATA_SATDEV_PRIVATE_DATA{
    
    PVOID AtaDevPrivate;
}ATA_SATDEV_PRIVATE_DATA, * PATA_SATDEV_PRIVATE_DATA;

#endif