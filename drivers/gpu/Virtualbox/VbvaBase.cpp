/* SPDX-License-Identifier: MIT */
/* Copyright (C) 2006-2017 Oracle Corporation */
/* Port Copyright (C) 2025-2026 Tyler Grenier */

 #define _KERNEL_MODULE_
 #include <LouDDK.h>
 #include "VirtualboxDriver.h"
 #include <drivers/VBoxError.h>


static uint32_t VbvaBufferAvailable(PVBVA_BUFFER Vbva){

    INT32 Difference = Vbva->DataOffset - Vbva->FreeOffset;

    return Difference > 0 ? Difference : Vbva->DataLength + Difference;
}

static void VbvaBufferPlaceDataAt(PVBVA_BUFFER_CONTEXT VbvaContext, void* Pointer, uint32_t Length, uint32_t Offset){
    PVBVA_BUFFER Vbva = VbvaContext->VbvaBuffer;
    UINT32 BytesTillBoundry = Vbva->DataLength - Offset;
    UINT8* Destination = &Vbva->Data[Offset];
    INT32 Difference = Length - BytesTillBoundry;

    if(Difference <= 0){
        memcpy(Destination, Pointer, Length);
    }else{
        memcpy(Destination, Pointer, BytesTillBoundry);
        memcpy(&Vbva->Data[0], (UINT8*)Pointer + BytesTillBoundry, Difference);
    }
}

static void VbvaBufferFlush(POOL Context){
    PVBVA_FLUSH Flush;

    Flush = (PVBVA_FLUSH)HgsmiBufferAllocate(Context, sizeof(VBVA_FLUSH), HGSMI_CH_VBVA, VBVA_FLUSH_COMMAND);
    if(!Flush){
        return;
    }
    Flush->Reserved = 0;

    HgsmiBufferSubmit(Context, Flush);
    HgsmiBufferFree(Context, Flush);
}

static bool VbvaInformHost(PVBVA_BUFFER_CONTEXT VbvaContext, POOL Context, int32_t Screen, bool Enable){

    bool Result = false;
    PVBVA_ENABLE_EX EnablePacket = (PVBVA_ENABLE_EX)HgsmiBufferAllocate(Context, sizeof(VBVA_ENABLE_EX), HGSMI_CH_VBVA, VBVA_ENABLE_COMMAND);
    if(!EnablePacket){
        return false;
    }
    
    EnablePacket->Base.Flags = Enable ? VBVA_F_ENABLE : VBVA_F_DISABLE;
    EnablePacket->Base.Offset = VbvaContext->BufferOffset;
    EnablePacket->Base.Result = VERR_NOT_SUPPORTED;

    if(Screen > MAXIMUM_VIRTUALBOX_MONITORS){
        return false;
    }

    EnablePacket->Base.Flags |= VBVA_F_EXTENDED | VBVA_F_ABSOFFSET;
    EnablePacket->ScreenID = Screen;

    HgsmiBufferSubmit(Context, EnablePacket);

    if(Enable){
        Result = EnablePacket->Base.Result >= 0;
    }else{
        Result = true;
    }

    HgsmiBufferFree(Context, EnablePacket);
    
    return Result;
}

void VbvaDisable(PVBVA_BUFFER_CONTEXT VbvaContext, POOL Context, int32_t Screen){
    VbvaContext->BufferOverflow = false;
    VbvaContext->Record = 0x00;
    VbvaContext->VbvaBuffer = 0x00;
    VbvaInformHost(VbvaContext, Context, Screen, false);
}


bool VbvaEnable(PVBVA_BUFFER_CONTEXT VbvaContext, POOL Context, PVBVA_BUFFER  VbvaBuffer, int32_t Screen){
    bool Result = false;

    memset(VbvaBuffer, 0, sizeof(VBVA_BUFFER));

    VbvaBuffer->PartialWriteTresh = 256;
    VbvaBuffer->DataLength = VbvaContext->BufferLength - sizeof(VBVA_BUFFER);
    VbvaContext->VbvaBuffer = VbvaBuffer;

    Result = VbvaInformHost(VbvaContext, Context, Screen, true);
    if(!Result){
        VbvaDisable(VbvaContext, Context, Screen);
    }

    return Result;
}

bool VbvaBufferBeginUpdate(PVBVA_BUFFER_CONTEXT VbvaContext, POOL Context){

    PVBVA_RECORD Record;
    UINT32 Next;

    if((!VbvaContext->VbvaBuffer) || (!(VbvaContext->VbvaBuffer->VbVaHostFlags.HostEvents & VBVA_F_MODE_ENABLED))){
        return false;
    }

    Next = (VbvaContext->VbvaBuffer->RecordFreeIndex + 1) % VBVA_MAXIMUM_RECORDS;

    if(Next == VbvaContext->VbvaBuffer->RecordFirstIndex){
        VbvaBufferFlush(Context);
    }

    if(Next == VbvaContext->VbvaBuffer->RecordFirstIndex){
        return false;
    }

    Record = &VbvaContext->VbvaBuffer->VbVaRecords[VbvaContext->VbvaBuffer->RecordFreeIndex];
    Record->LengthAndFlags = VBVA_F_RECORD_PARTIAL;
    VbvaContext->VbvaBuffer->RecordFreeIndex = Next;    
    VbvaContext->Record = Record;
    return true;
}

void VbvaBufferEndUpdate(PVBVA_BUFFER_CONTEXT VbvaContext){
    PVBVA_RECORD Record = VbvaContext->Record;

    Record->LengthAndFlags &= VBVA_F_RECORD_PARTIAL;
    VbvaContext->BufferOverflow = false;
    VbvaContext->Record = 0x00;
}

bool VbvaWrite(PVBVA_BUFFER_CONTEXT BufferContext, POOL Context, void* Pixels, uint32_t Length){
    PVBVA_RECORD Record;
    PVBVA_BUFFER Vbva;
    UINT32 Available;

    Vbva = BufferContext->VbvaBuffer;
    Record = BufferContext->Record;

    if((!Vbva) || (BufferContext->BufferOverflow) || (!Record) || (!(Record->LengthAndFlags & VBVA_F_RECORD_PARTIAL))){
        return false;
    }

    Available = VbvaBufferAvailable(Vbva);

    while(Length > 0){
        UINT32 Chunk = Length;
        if(Chunk >= Available){
            VbvaBufferFlush(Context);
            Available = VbvaBufferAvailable(Vbva);
        }
        if(Chunk >= Available){
            if(Available <= Vbva->PartialWriteTresh){
                BufferContext->BufferOverflow = true;
                return false;
            }
            Chunk = Available - Vbva->PartialWriteTresh;
        }

        VbvaBufferPlaceDataAt(BufferContext, Pixels, Chunk, Vbva->FreeOffset);

        Vbva->FreeOffset = ((Vbva->FreeOffset + Chunk) % Vbva->DataLength);
        Record->LengthAndFlags += Chunk;
        Available -= Chunk;
        Pixels = (PVOID)((UINTPTR)Pixels + Chunk);
    }

    return true;
}

void VbvaSetupBufferContext(
    PVBVA_BUFFER_CONTEXT VbvaContext, 
    uint32_t BufferOffset, 
    uint32_t BufferLength
){
    VbvaContext->BufferOffset = BufferOffset;
    VbvaContext->BufferLength = BufferLength;
}
