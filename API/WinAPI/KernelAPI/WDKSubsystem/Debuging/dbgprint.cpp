#include <WDKSubsystem/WDKSubsystem.h>
#include <LouDDK.h>
#include <stdarg.h>
#include <kernel/exports.h>
//I Will Need To Change The Cases To The Real Cases

LOUDDK_API_ENTRY
ULONG
vDbgPrintEx(
    ULONG ComponentId,
    ULONG Level,
    PCCH Format,
    va_list args
){
    while (*Format) {
        if (*Format == '%') {
            Format++; // Move past '%'
                                
            if((strncmp(Format, "x", strlen("x")) == 0) || (strncmp(Format, "X", strlen("X")) == 0)){
                int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                LouPrint("%h", num); // Print Hex String;
                Format += 1;
            }
            else if((strncmp(Format, "#x", strlen("#x")) == 0) || (strncmp(Format, "#X", strlen("#X")) == 0)){
                int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                LouPrint("%h", num); // Print Hex String;
                Format += 2;
            }
            else if((strncmp(Format, "02x", strlen("02x")) == 0x00) || 
                    (strncmp(Format, "02X", strlen("02X")) == 0x00) ||
                    (strncmp(Format, "04x", strlen("04x")) == 0x00) ||
                    (strncmp(Format, "04X", strlen("04X")) == 0x00) ||
                    (strncmp(Format, "08x", strlen("08x")) == 0x00) ||
                    (strncmp(Format, "08x", strlen("08x")) == 0x00)) {

                int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                LouPrint("%h", num); // Print Hex String;
                Format += 3;
            }
            else if((strncmp(Format, "d", strlen("d")) == 0) || (strncmp(Format, "D", strlen("D")) == 0) ||
                    (strncmp(Format, "u", strlen("u")) == 0) || (strncmp(Format, "U", strlen("U")) == 0)){
                        int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                        LouPrint("%d", num); // Print Decimal String;
                        Format += 1;
            }
            else if((strncmp(Format, "ld", strlen("ld")) == 0) || (strncmp(Format, "LD", strlen("LD")) == 0) || 
                    (strncmp(Format, "lu", strlen("lu")) == 0) || (strncmp(Format, "LU", strlen("LU")) == 0) ||
                    (strncmp(Format, "hd", strlen("hd")) == 0) || (strncmp(Format, "HD", strlen("HD")) == 0) ||
                    (strncmp(Format, "hu", strlen("hu")) == 0) || (strncmp(Format, "HU", strlen("HU")) == 0)){
                        int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                        LouPrint("%d", num); // Print Decimal String;
                        Format += 2;
                    }

            //Format++; // Move to the next character in the format string
        }
        else if(*Format == '\r'){
                //Do Nothing In This Case
                Format++;
        }
        else {
            LouPrint("%c", *Format);
            Format++;
        }
    }
    return 0;
}


LOUDDK_API_ENTRY
ULONG
vDbgPrintExWithPrefix (
    PCCH Prefix,
    ULONG ComponentId,
    ULONG Level,
    PCCH Format,
    va_list args
){
    while (*Format) {
        if (*Format == '%') {
            Format++; // Move past '%'
                                
            if((strncmp(Format, "x", strlen("x")) == 0) || (strncmp(Format, "X", strlen("X")) == 0)){
                int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                LouPrint("%h", num); // Print Hex String;
                Format += 1;
            }
            else if((strncmp(Format, "#x", strlen("#x")) == 0) || (strncmp(Format, "#X", strlen("#X")) == 0)){
                int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                LouPrint("%h", num); // Print Hex String;
                Format += 2;
            }
            else if((strncmp(Format, "02x", strlen("02x")) == 0x00) || 
                    (strncmp(Format, "02X", strlen("02X")) == 0x00) ||
                    (strncmp(Format, "04x", strlen("04x")) == 0x00) ||
                    (strncmp(Format, "04X", strlen("04X")) == 0x00) ||
                    (strncmp(Format, "08x", strlen("08x")) == 0x00) ||
                    (strncmp(Format, "08x", strlen("08x")) == 0x00)) {

                int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                LouPrint("%h", num); // Print Hex String;
                Format += 3;
            }
            else if((strncmp(Format, "d", strlen("d")) == 0) || (strncmp(Format, "D", strlen("D")) == 0) ||
                    (strncmp(Format, "u", strlen("u")) == 0) || (strncmp(Format, "U", strlen("U")) == 0)){
                        int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                        LouPrint("%d", num); // Print Decimal String;
                        Format += 1;
            }
            else if((strncmp(Format, "ld", strlen("ld")) == 0) || (strncmp(Format, "LD", strlen("LD")) == 0) || 
                    (strncmp(Format, "lu", strlen("lu")) == 0) || (strncmp(Format, "LU", strlen("LU")) == 0) ||
                    (strncmp(Format, "hd", strlen("hd")) == 0) || (strncmp(Format, "HD", strlen("HD")) == 0) ||
                    (strncmp(Format, "hu", strlen("hu")) == 0) || (strncmp(Format, "HU", strlen("HU")) == 0)){
                        int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                        LouPrint("%d", num); // Print Decimal String;
                        Format += 2;
                    }

            //Format++; // Move to the next character in the format string
        }
        else if(*Format == '\r'){
                //Do Nothing In This Case
                Format++;
        }
        else {
            LouPrint("%c", *Format);
            Format++;
        }
    }
    return 0;
}


ULONG DbgPrint(PCSTR Format, ...){
    va_list args;
    va_start(args, Format);

    while (*Format) {
        if (*Format == '%') {
            Format++; // Move past '%'
                                
            if((strncmp(Format, "x", strlen("x")) == 0) || (strncmp(Format, "X", strlen("X")) == 0)){
                int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                LouPrint("%h", num); // Print Hex String;
                Format += 1;
            }
            else if((strncmp(Format, "#x", strlen("#x")) == 0) || (strncmp(Format, "#X", strlen("#X")) == 0)){
                int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                LouPrint("%h", num); // Print Hex String;
                Format += 2;
            }
            else if((strncmp(Format, "02x", strlen("02x")) == 0x00) || 
                    (strncmp(Format, "02X", strlen("02X")) == 0x00) ||
                    (strncmp(Format, "04x", strlen("04x")) == 0x00) ||
                    (strncmp(Format, "04X", strlen("04X")) == 0x00) ||
                    (strncmp(Format, "08x", strlen("08x")) == 0x00) ||
                    (strncmp(Format, "08x", strlen("08x")) == 0x00)) {

                int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                LouPrint("%h", num); // Print Hex String;
                Format += 3;
            }
            else if((strncmp(Format, "d", strlen("d")) == 0) || (strncmp(Format, "D", strlen("D")) == 0) ||
                    (strncmp(Format, "u", strlen("u")) == 0) || (strncmp(Format, "U", strlen("U")) == 0)){
                        int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                        LouPrint("%d", num); // Print Decimal String;
                        Format += 1;
            }
            else if((strncmp(Format, "ld", strlen("ld")) == 0) || (strncmp(Format, "LD", strlen("LD")) == 0) || 
                    (strncmp(Format, "lu", strlen("lu")) == 0) || (strncmp(Format, "LU", strlen("LU")) == 0) ||
                    (strncmp(Format, "hd", strlen("hd")) == 0) || (strncmp(Format, "HD", strlen("HD")) == 0) ||
                    (strncmp(Format, "hu", strlen("hu")) == 0) || (strncmp(Format, "HU", strlen("HU")) == 0)){
                        int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                        LouPrint("%d", num); // Print Decimal String;
                        Format += 2;
                    }

            //Format++; // Move to the next character in the format string
        }
        else if(*Format == '\r'){
                //Do Nothing In This Case
                Format++;
        }
        else {
            LouPrint("%c", *Format);
            Format++;
        }
    }

    va_end(args);
    return 0;
}

ULONG DbgPrintEx (  ULONG ComponentId,  ULONG Level, PCSTR Format, ...){
       va_list args;
    va_start(args, Format);

    while (*Format) {
        if (*Format == '%') {
            Format++; // Move past '%'
                                
            if((strncmp(Format, "x", strlen("x")) == 0) || (strncmp(Format, "X", strlen("X")) == 0)){
                int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                LouPrint("%h", num); // Print Hex String;
                Format += 1;
            }
            else if((strncmp(Format, "#x", strlen("#x")) == 0) || (strncmp(Format, "#X", strlen("#X")) == 0)){
                int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                LouPrint("%h", num); // Print Hex String;
                Format += 2;
            }
            else if((strncmp(Format, "02x", strlen("02x")) == 0x00) || 
                    (strncmp(Format, "02X", strlen("02X")) == 0x00) ||
                    (strncmp(Format, "04x", strlen("04x")) == 0x00) ||
                    (strncmp(Format, "04X", strlen("04X")) == 0x00) ||
                    (strncmp(Format, "08x", strlen("08x")) == 0x00) ||
                    (strncmp(Format, "08x", strlen("08x")) == 0x00)) {

                int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                LouPrint("%h", num); // Print Hex String;
                Format += 3;
            }
            else if((strncmp(Format, "d", strlen("d")) == 0) || (strncmp(Format, "D", strlen("D")) == 0) ||
                    (strncmp(Format, "u", strlen("u")) == 0) || (strncmp(Format, "U", strlen("U")) == 0)){
                        int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                        LouPrint("%d", num); // Print Decimal String;
                        Format += 1;
            }
            else if((strncmp(Format, "ld", strlen("ld")) == 0) || (strncmp(Format, "LD", strlen("LD")) == 0) || 
                    (strncmp(Format, "lu", strlen("lu")) == 0) || (strncmp(Format, "LU", strlen("LU")) == 0) ||
                    (strncmp(Format, "hd", strlen("hd")) == 0) || (strncmp(Format, "HD", strlen("HD")) == 0) ||
                    (strncmp(Format, "hu", strlen("hu")) == 0) || (strncmp(Format, "HU", strlen("HU")) == 0)){
                        int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                        LouPrint("%d", num); // Print Decimal String;
                        Format += 2;
                    }

            //Format++; // Move to the next character in the format string
        }
        else if(*Format == '\r'){
                //Do Nothing In This Case
                Format++;
        }
        else {
            LouPrint("%c", *Format);
            Format++;
        }
    }

    va_end(args);
    return 0;
}
