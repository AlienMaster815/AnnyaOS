#include <LouDDK.h>

LOUDDK_API_ENTRY
string Winstrchr(
    string str,
    int c
){

    for(size_t i = 0 ; i < strlen(str); i++){
        if(str[i] == (char)c)return &str[i];
    }
    return 0x00;
}

LOUDDK_API_ENTRY
string strtok_s(
    string str,
    string Delimiters,
    string* Context
){
    if((!str) && (!(*Context))){goto _STRTOK_S_RET_ERR;}
    if(!Delimiters)            {goto _STRTOK_S_RET_ERR;}
    if(!(*Context))            {goto _STRTOK_S_RET_ERR;}

    string token;
    string start;

    // Use `str` if provided, otherwise continue from the previous context
    start = (str) ? str : *Context;

    // Skip leading delimiters
    while (*start && Winstrchr(Delimiters, *start)) {
        start++;
    }

    // If we reached the end of the string, return NULL
    if (!*start) {
        *Context = 0x00;
        return 0x00;
    }

    // Set the token start
    token = start;

    // Find the end of the token
    while (*start && !Winstrchr(Delimiters, *start)) {
        start++;
    }

    // If we found a delimiter, terminate the token and update the context
    if (*start) {
        *start = '\0';
        *Context = start + 1;
    } else {
        // If no delimiter is found, set the context to NULL (end of the string)
        *Context = 0x00;
    }

    return token;

    _STRTOK_S_RET_ERR:
    return 0x00;
}

LOUDDK_API_ENTRY
string Winstrstr(
   string str,
   string strSearch
){

    if((!str) || (!strSearch)){
        return 0x00;
    }

    if(strlen(strSearch) == 0){
        return str;
    }

    for(size_t Context = 0; Context < (strlen(str) - strlen(strSearch)); Context++){
        if(strncmp(str, &strSearch[Context], strlen(strSearch)) == 0) return &strSearch[Context];
    }

    return 0x00;
}

LOUDDK_API_ENTRY
size_t strspn(
   string str,
   string strCharSet
){
    if((!str) || (!str)){
        return 0x00;
    }

    for(size_t StrIndex = 0; StrIndex < strlen(str); StrIndex++){
        bool Result = false;
        for(size_t CharSetIndex = 0 ; CharSetIndex < strlen(strCharSet); CharSetIndex++){
            if(str[StrIndex] == strCharSet[CharSetIndex]){
                Result = true;
            }
        }
        if(!Result) return StrIndex;
    }
    return strlen(str);
}

LOUDDK_API_ENTRY
string strrchr(
   string str,
   int c
){
    if(!str)return 0x00;
    for(size_t Index = 0 ; Index < strlen(str); Index++){
        if(str[Index] == (char)c){
            return &str[Index];
        }
    }
    return 0x00;
}

LOUDDK_API_ENTRY
int strncpy_s(
    string Destination,
    size_t ElementsCount,
    string Source,
    size_t Count
){  
    if(Count > ElementsCount){
        Destination[0] = 0;
        return STRUNCATE;
    }
    else if((!Destination) || (!ElementsCount)){
        return EINVAL;
    }
    else if(!Source){
        Destination[0] = 0;
        return EINVAL;
    }
    for(size_t Index = 0; Index < Count; Index++){
        Destination[Index] = Source[Index];
    }
    return 0;
}

LOUDDK_API_ENTRY
string Winstrcpy(
    string Destination,
    string Source
){

    if((!Source) || (!Destination)){
        return Destination;
    }

    for(size_t Index = 0 ; Index < strlen(Source); Index++){
        Destination[Index] = Source[Index]; 
    }

    return Destination;
}

LOUDDK_API_ENTRY
int strncat_s(
    string Destination,
    size_t NumElements,
    string Source,
    size_t Count
) {
    // Validate inputs
    if (!Destination || !Source || NumElements == 0)
        return EINVAL; // Invalid argument error code

    size_t destLen = 0, srcLen = 0;

    // Find the length of the destination string
    while (destLen < NumElements && Destination[destLen] != '\0') {
        destLen++;
    }

    // If Destination is not null-terminated
    if (destLen == NumElements)
        return EINVAL;

    // Append characters from Source to Destination
    while (srcLen < Count && Source[srcLen] != '\0' && (destLen + 1) < NumElements) {
        Destination[destLen++] = Source[srcLen++];
    }

    // Null-terminate the result
    if (destLen < NumElements)
        Destination[destLen] = '\0';
    else
        return ERANGE; // Insufficient space

    return 0; // Success
}

LOUDDK_API_ENTRY
string Winstrncat(
    string Destination,
    string Source,
    size_t Count
) {
    if (!Destination || !Source)
        return 0x00;

    size_t destLen = 0, srcLen = 0;

    // Find the length of the destination string
    while (Destination[destLen] != '\0') {
        destLen++;
    }

    // Append characters from Source to Destination
    while (srcLen < Count && Source[srcLen] != '\0') {
        Destination[destLen++] = Source[srcLen++];
    }

    // Null-terminate the result
    Destination[destLen] = '\0';

    return Destination;
}

LOUDDK_API_ENTRY
int strcpy_s(
    string Destination,
    size_t DestinationSize,
    string Source
){
    if((DestinationSize == 0) || (DestinationSize < strlen(Source))){
        return ERANGE;
    }
    else if((!Destination) || (!Source)){
        return EINVAL;
    }

    Winstrcpy(
        Destination,
        Source
    );

    return 0;
}

LOUDDK_API_ENTRY
int strcat_s(
    string Destination,
    size_t Elements,
    string Source
) {
    // Validate inputs
    if (!Destination || !Source || Elements == 0)
        return EINVAL; // Invalid argument

    size_t destLen = 0, srcLen = 0;

    // Find the length of the destination string
    while (destLen < Elements && Destination[destLen] != '\0') {
        destLen++;
    }

    // If the destination is not null-terminated
    if (destLen == Elements)
        return EINVAL;

    // Append Source to Destination
    while (srcLen < Elements - destLen - 1 && Source[srcLen] != '\0') {
        Destination[destLen++] = Source[srcLen++];
    }

    // If the buffer is not large enough
    if (Source[srcLen] != '\0') {
        Destination[destLen] = '\0'; // Null-terminate the result
        return ERANGE; // Insufficient buffer space
    }

    // Null-terminate the result
    Destination[destLen] = '\0';

    return 0; // Success
}

LOUDDK_API_ENTRY
string Winstrcat(
    string Destination,
    string Source
) {
    // Validate inputs
    if (!Destination || !Source)
        return 0x00; // Return NULL if inputs are invalid

    size_t destLen = 0, srcLen = 0;

    // Find the end of the Destination string
    while (Destination[destLen] != '\0') {
        destLen++;
    }

    // Append Source to Destination
    while (Source[srcLen] != '\0') {
        Destination[destLen++] = Source[srcLen++];
    }

    // Null-terminate the result
    Destination[destLen] = '\0';

    return Destination; // Return the concatenated string
}

KERNEL_IMPORT
void SetRANDSeed(uint32_t NewSeed);

LOUDDK_API_ENTRY
void srand(
    unsigned int seed
){
    SetRANDSeed((uint32_t)seed);
}

KERNEL_IMPORT
uint32_t LouKeRandCStdLib();

LOUDDK_API_ENTRY
int rand(){
    return (int)LouKeRandCStdLib();
}

void qsort_s(
    void* Base, 
    size_t NumberMeneber, 
    size_t Size, 
    int (*CompareFunction)(void*, void*),
    void* Context
){

}

void qsort(
    void* Base, 
    size_t NumberMeneber, 
    size_t Size, 
    int (*CompareFunction)(void*, void*)
){

}