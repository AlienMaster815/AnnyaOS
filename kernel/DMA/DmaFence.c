// SPDX-License-Identifier: GPL-2.0-only
/*
 * Fence mechanism for dma-buf and to allow for asynchronous dma access
 *
 * Copyright (C) 2012 Canonical Ltd
 * Copyright (C) 2012 Texas Instruments
 *
 * Authors:
 * Rob Clark <robdclark@gmail.com>
 * Maarten Lankhorst <maarten.lankhorst@canonical.com>
 */
//Port By Tyler Grenier (C) 2026

#include <LouAPI.h>

KERNEL_EXPORT 
void 
LouKeDmaFenceInitialize(
    PDMA_FENCE              DmaFence, 
    PDMA_FENCE_OPERATIONS   Operations, 
    spinlock_t*             Lock, 
    UINT64                  Context, 
    UINT64                  SequenceNumber
){

}

KERNEL_EXPORT 
void 
LouKeDmaFenceInitialize64(
    PDMA_FENCE              DmaFence, 
    PDMA_FENCE_OPERATIONS   Operations, 
    spinlock_t*             Lock, 
    UINT64                  Context, 
    UINT64                  SequenceNumber
){

}

KERNEL_EXPORT 
void 
LouKeDmaFenceRelease(
    PKERNEL_REFERENCE Reference
){

}

KERNEL_EXPORT 
void 
LouKeDmaFenceFree(
    PDMA_FENCE DmaFence
){

}

KERNEL_EXPORT 
void 
LouKeDmaFenceDescribe(
    PDMA_FENCE  DmaFence, 
    FILE*       SequenceFile
){

}