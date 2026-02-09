#ifndef _PRIVATE_MEM_H
#define _PRIVATE_MEM_H

#include <LouAPI.h>

typedef struct _FAST_ALLOCATION_TRACKER{
    ListHeader      Peers;
    LOUSTR          TrackingTag;
}FAST_ALLOCATION_TRACKER, * PFAST_ALLOCATION_TRACKER;



#endif