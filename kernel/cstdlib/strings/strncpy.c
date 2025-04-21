#include <stdint.h>
#include <stddef.h>
#include <string.h>
char* strncpy(char* dest, const char* src, size_t n) {
    char* original_dest = dest;

    // Copy at most 'n' characters from src to dest
    while (*src && n > 0) {
        *dest++ = *src++;
        n--;
    }

    // If 'n' is greater than the length of src, pad with null bytes
    while (n > 0) {
        *dest++ = '\0';
        n--;
    }

    return original_dest;
}

char* strcpy(char* Destination, const char* Source){

    if((!Source) || (!Destination)){
        return Destination;
    }

    for(size_t Index = 0 ; Index < strlen(Source); Index++){
        Destination[Index] = Source[Index]; 
    }

    return Destination;
}
