#ifndef _LDM_DRIVES_H
#define _LDM_DRIVES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <Ldm/CommonTypes.h>

typedef struct _PARTITION_INFORMATION{
    LARGE_INTEGER StartingOffset;
    LARGE_INTEGER PartitionLength;
    ULONG         HiddenSectors;
    ULONG         PartitionNumber;
    UCHAR         PartitionType;
    BOOLEAN       BootIndicator;
    BOOLEAN       RecognizedPartition;
    BOOLEAN       RewritePartition;
}PARTITION_INFORMATION, * PPARTITION_INFORMATION;

typedef struct _DRIVE_LAYOUT_INFORMATION{
    ULONG                 PartitionCount;
    ULONG                 Signature;
    PARTITION_INFORMATION PartitionEntry[1];
}DRIVE_LAYOUT_INFORMATION, * PDRIVE_LAYOUT_INFORMATION;


#ifdef __cplusplus
}
#endif
#endif