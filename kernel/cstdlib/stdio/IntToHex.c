
#include <LouAPI.h>

#ifdef __x86_64__

#include <stdint.h>

void uintToHexString(uint64_t number, char* hexString) {
    int i = 0;
    hexString[0] = '0';
    hexString[1] = 'x';
    i = 2;  // Start filling the string after '0x'

    char tempString[16];  // Temporary array to store reversed hex string (16 hex digits for 64 bits)
    int tempIndex = 0;

    // Handle the case when number is 0
    if (number == 0) {
        hexString[i++] = '0';
        hexString[i] = '\0';
        return;
    }

    // Convert number to hex string in reverse order
    while (number != 0) {
        int digit = number % 16;
        tempString[tempIndex++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'A');
        number /= 16;
    }

    // Copy the reversed hex string to the final string
    while (tempIndex > 0) {
        hexString[i++] = tempString[--tempIndex];
    }

    hexString[i] = '\0'; // Null-terminate the string
}



#endif

#ifdef __i386__

void uintToHexString(uint32_t number, char* hexString) {
    
    int i = 2;
    hexString[0] = '0';
    hexString[1] = 'x';
    char tempString[18]; // Temporary array to store reversed hex string

    do {
        int digit = number % 16;
        tempString[i++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'A');
        number /= 16;
    } while (number != 0);

    // Copy the reversed hex string to the final string
    for (int j = 0; j < i; ++j) {
        hexString[j + 2] = tempString[i - j - 1];
    }

    hexString[i] = '\0'; // Null-terminate the string    
    
    /*int i = 2;
    hexString[0] = '0';
    hexString[1] = 'x';
    do {
        int digit = number % 16;
        hexString[i++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'a');
        number /= 16;
    } while (number != 0);

    hexString[i] = '\0'; // Null-terminate the string */
}


#endif

