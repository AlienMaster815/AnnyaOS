//https://github.com/torvalds/linux/blob/master/include/linux/dma-fence.h#L70
/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Fence mechanism for dma-buf to allow for asynchronous dma access
 *
 * Copyright (C) 2012 Canonical Ltd
 * Copyright (C) 2012 Texas Instruments
 *
 * Authors:
 * Rob Clark <robdclark@gmail.com>
 * Maarten Lankhorst <maarten.lankhorst@canonical.com>
 */
//Port By Tyler Grenier (C) 2026

#ifndef _DMA_FENCE_H
#define _DMA_FENCE_H

#include <Modulation.h>
#include <cstdlib.h>
#include <kernel/threads.h>
#include <kernel/Rcu.h>

#ifdef __cplusplus
extern "C"{
#endif

struct _DMA_FENCE_OPERATIONS;
struct _DMA_FENCE_CALLBACK;

typedef enum {
    DMA_FENCE_FLAG_INITIALIZED          = (1 << 0),
    DMA_FENCE_FLAG_INLINE_LOCK          = (1 << 1),
    DMA_FENCE_FLAG_SEQUENCE_NUMBER64    = (1 << 2),
    DMA_FENCE_FLAG_SIGNALED_BIT         = (1 << 3),
    DMA_FENCE_FLAG_TIMESTAMP            = (1 << 4),
    DMA_FENCE_FLAG_ENABLE_SIGNAL        = (1 << 5),
    DMA_FENCE_FLAG_MASK                 = ((1 << 6) - 1),
}DMA_FENCE_FLAGS;

typedef struct _DMA_FENCE{
    union{
        spinlock_t*                 ExternalLock;
        spinlock_t                  InternalLock;
    };
    struct _DMA_FENCE_OPERATIONS*   Operations;
    union{
        ListHeader                  CallbackList;
        TIME_T                      Timestamp;
        RCU_OBJECT                  Rcu;                    
    };
    UINT64                          Context;
    UINT64                          SequenceNumber;
    DMA_FENCE_FLAGS                 Flags;
    KERNEL_REFERENCE                ReferenceCount;
    LOUSTATUS                       Error;
}DMA_FENCE, * PDMA_FENCE;

typedef void (*DMA_FENCE_FUNCTION)(PDMA_FENCE Fence, struct _DMA_FENCE_CALLBACK* Callback);

typedef struct _DMA_FENCE_CALLBACK{
    ListHeader          Peers;
    DMA_FENCE_FUNCTION  Function;
}DMA_FENCE_CALLBACK, * PDMA_FENCE_CALLBACK;

typedef struct _DMA_FENCE_OPERATIONS{
    PCHAR       (*GetDriverName)(PDMA_FENCE Fence);
    PCHAR       (*GetTimelineName)(PDMA_FENCE Fence);
    BOOLEAN     (*EnableSignaling)(PDMA_FENCE Fence);
    BOOLEAN     (*Signaled)(PDMA_FENCE Fence);
    LOUSTATUS   (*Wait)(PDMA_FENCE Fence, BOOLEAN Intr, ULONG Timeout);
    void        (*Release)(PDMA_FENCE Fence);
    void        (*SetDeadline)(PDMA_FENCE Fence, TIME_T Deadline);
}DMA_FENCE_OPERATIONS, * PDMA_FENCE_OPERATIONS;

KERNEL_EXPORT void LouKeDmaFenceInitialize(PDMA_FENCE DmaFence, PDMA_FENCE_OPERATIONS Operations, spinlock_t* Lock, UINT64 Context, UINT64 SequenceNumber);
KERNEL_EXPORT void LouKeDmaFenceInitialize64(PDMA_FENCE DmaFence, PDMA_FENCE_OPERATIONS Operations, spinlock_t* Lock, UINT64 Context, UINT64 SequenceNumber);

KERNEL_EXPORT void LouKeDmaFenceRelease(PKERNEL_REFERENCE Reference);
KERNEL_EXPORT void LouKeDmaFenceFree(PDMA_FENCE DmaFence);
KERNEL_EXPORT void LouKeDmaFenceDescribe(PDMA_FENCE DmaFence, FILE* SequenceFile);

static inline BOOLEAN LouKeDmaFenceWasInitialized(PDMA_FENCE DmaFence){
    if(!DmaFence){
        return false;
    }
    return DmaFence->Flags & DMA_FENCE_FLAG_INITIALIZED;
}

static inline void LouKeDmaFencePut(PDMA_FENCE Fence){
    if(Fence){
        LouKeReleaseReferenceAndCall(&Fence->ReferenceCount, LouKeDmaFenceRelease);
    }
} 

static inline PDMA_FENCE LouKeDmaFenceGet(PDMA_FENCE DmaFence){
    if(DmaFence){
        LouKeAcquireReference(&DmaFence->ReferenceCount);
    }
    return DmaFence;
}

//320

#ifdef __cplusplus
}
#endif
#endif