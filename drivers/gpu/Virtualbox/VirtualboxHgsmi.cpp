/* SPDX-License-Identifier: MIT */
/* Copyright (C) 2006-2017 Oracle Corporation */

 #define _KERNEL_MODULE_
 #include <LouDDK.h>
 #include "VirtualboxDriver.h"
 
static uint32_t HgsmiHashProcess(uint32_t Hash, const uint8_t* Data, int Size){
    while(Size--){
        Hash += *Data++;
        Hash += (Hash << 10);
        Hash ^= (Hash >> 6);
    }    
    return Hash;
}

static uint32_t HgsmiHashEnd(uint32_t Hash){
    Hash += (Hash << 3);
    Hash ^= (Hash >> 11);
    Hash += (Hash << 15);
    return Hash;
}

static uint32_t HgsmiChecksum(uint32_t Offset, PHGSMI_BUFFER_HEADER Header, PHGSMI_BUFFER_TAIL Tail){

    uint32_t Checksum;

    Checksum = HgsmiHashProcess(0, (uint8_t*)&Offset, sizeof(uint32_t));
    Checksum = HgsmiHashProcess(Checksum, (uint8_t*)Header, sizeof(HGSMI_BUFFER_HEADER));
    Checksum = HgsmiHashProcess(Checksum, (uint8_t*)Tail, 4);
    return HgsmiHashEnd(Checksum);
}

void* HgsmiBufferAllocate(
    POOL GuestPool, 
    size_t size,
    uint8_t Channel,
    uint16_t ChannelInfo
){
    size_t Offset;
    PHGSMI_BUFFER_HEADER Header;
    PHGSMI_BUFFER_TAIL Tail;
    size_t TotalSize = size + sizeof(HGSMI_BUFFER_HEADER) + sizeof(HGSMI_BUFFER_TAIL);
    Header = (PHGSMI_BUFFER_HEADER)LouKeGenricAllocateDmaPool(GuestPool, TotalSize, &Offset);
    if(!Header){
        return 0x00;
    }
    Tail = (PHGSMI_BUFFER_TAIL)((uint8_t*)Header + size + sizeof(HGSMI_BUFFER_HEADER));
    memset(Header, 0, TotalSize);
    
    Header->Flags = HGSMI_BUFFER_HEADER_F_SEQUENCE_SINGLE;
    Header->DataSize = size;
    Header->Channel = Channel;
    Header->ChannelInformation = ChannelInfo;

    Tail->Reserved = 0;
    Tail->Checksum = HgsmiChecksum(Offset, Header, Tail);
    return (uint8_t*)Header + sizeof(HGSMI_BUFFER_HEADER);
}

void HgsmiBufferFree(POOL GuestPool, void* Buffer){
    LouKeFreeFromDynamicPool(GuestPool, (uint8_t*)Buffer - sizeof(HGSMI_BUFFER_HEADER));
}

int HgsmiBufferSubmit(POOL GuestPool, void* Buffer){
    uint64_t Offset = 0x00;
    Offset = (uint64_t)LouKeGenericPoolGetPhyAddress(GuestPool, (void*)((uint64_t)Buffer - sizeof(HGSMI_BUFFER_HEADER))); 
    outl(VIRTUALBOX_VGA_HGSMI_GUEST, (uint32_t)Offset);
    LouKeMemoryBarrier();
    return 0;
}