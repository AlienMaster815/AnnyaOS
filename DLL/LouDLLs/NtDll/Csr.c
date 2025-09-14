#include "ntdll.h"

PVOID
NTDLL_API
CsrAllocateCaptureBuffer(
    ULONG ArgumentCount,
    ULONG BufferSize
){
    PCSR_CAPTURE_BUFFER CaptureBuffer;

    if(BufferSize >= MAX_LONG){
        return 0x00;
    }

    BufferSize += sizeof(CSR_CAPTURE_BUFFER) + (ArgumentCount * sizeof(PVOID));

    CaptureBuffer = RtlAllocateHeap(GetCsrPortHeap(), 0, BufferSize);

    if(!CaptureBuffer){
        return 0x00;
    }

    CaptureBuffer->Size = BufferSize;
    CaptureBuffer->PointerCount = 0;
    CaptureBuffer->BufferEnd = (uintptr_t)(CaptureBuffer->PointerArray + (ArgumentCount * sizeof(uintptr_t)));

    return CaptureBuffer;    
}

ULONG 
NTDLL_API
CsrAllocateMessagePointer(
    PCSR_CAPTURE_BUFFER CaptureBuffer,
    ULONG               MessageLength,
    void**              CaptureData
){
    if(!MessageLength){
        *CaptureData = 0x00;
        return 0;
    }else{
        *CaptureData = (void*)CaptureBuffer->BufferEnd;
        if(MessageLength >= MAX_LONG){
            return 0x00;
        } 
        MessageLength = (MessageLength + 3) & ~(3);
        CaptureBuffer->BufferEnd += MessageLength;
    }
    CaptureBuffer->PointerArray[CaptureBuffer->PointerCount] = (uintptr_t)CaptureData;
    CaptureBuffer->PointerCount++;
    return MessageLength;
}

void 
NTDLL_API
CsrCaptureMessageBuffer(
    PCSR_CAPTURE_BUFFER CaptureBuffer,
    void*               MessageString,
    ULONG               StringLength,
    void**              CaptureData
){

    CsrAllocateMessagePointer(CaptureBuffer, StringLength, CaptureData);

    if((!MessageString) || (!StringLength)){
        return;
    }

    //LouMemCpy Copys by (Destination, Source, Length)
    LouMemCpy(MessageString, *CaptureData , StringLength);
}

//NTSTATUS 
//NTDLL_API
//CsrCaptureMessageMultiUnicodeStringsInPlace(

//){

//    return STATUS_SUCCESS;
//}