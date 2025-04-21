#include <LouAPI.h>

char* strcat(char* Destination, const char* Source){
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