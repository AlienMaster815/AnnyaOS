#include <LouDDK.h>

LOUDDK_API_ENTRY
LOUSTATUS LouKeAsciiInterpreterFetchNonTerminatedString(
    LPWSTR* Start, 
    LPWSTR OpenStr, 
    LPWSTR CloseStr, 
    size_t* Length
){
    if(!Start || !Length || !OpenStr || !CloseStr){
        return STATUS_INVALID_PARAMETTER;
    }
    if(!(*Start)){
        return STATUS_INVALID_PARAMETTER;
    }

    *Start = wcsstr(*Start, OpenStr);

    if(!(*Start)){
        return STATUS_UNSUCCESSFUL;
    }
    
    CloseStr = wcsstr(*Start, CloseStr);

    *Length = CloseStr - *Start;

    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
LOUSTATUS LouKeAsciiLexerNonTerminatedToken(
    LPWSTR*     Start, 
    LPWSTR      OpenStr,
    LPWSTR      CloseStr,
    LOUSTATUS   (*HitCallback)(LPWSTR Str, size_t Length);
){
    if(!Start || !OpenStr || !CloseStr || !HitCallback){
        return STATUS_INVALID_PARAMETTER;
    }
    size_t Length = 0;
    LOUSTATUS Result;
    while(LouKeAsciiInterpreterFetchNonTerminatedString(
        Start, 
        OpenStr,
        CloseStr,
        &Length
    )){
        Result = HitCallback(*Start, Length);
        *Start += Length;
        if((Result != STATUS_SUCCESS) && (Result != STATUS_UNSUCCESSFUL)){
            return Result;
        }
    }
    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
LOUSTATUS LouKeAsciiLexerTerminatedToken(
    LPWSTR*     Start, 
    LPWSTR      Str,
    LOUSTATUS   (*HitCallback)(LPWSTR Str);
){
    LOUSTATUS Status;
    while(*Start = wcsstr(*Start, Str)){//its not a tuma
        Status = HitCallback(*Start);
        (*Start)++;
    }
    return STATUS_SUCCESS;
}

