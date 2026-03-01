
#include <LouAPI.h>


LOUAPI
void 
uintToHexString(
    uint64_t number, 
    char* hexString
){
    int i = 0;
    hexString[0] = '0';
    hexString[1] = 'x';
    i = 2;

    char tempString[16];
    int tempIndex = 0;

    if (number == 0) {
        hexString[i++] = '0';
        hexString[i] = '\0';
        return;
    }

    while (number != 0) {
        int digit = number % 16;
        tempString[tempIndex++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'A');
        number /= 16;
    }

    while (tempIndex > 0) {
        hexString[i++] = tempString[--tempIndex];
    }

    hexString[i] = '\0';
}