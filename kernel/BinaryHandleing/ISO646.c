#include <LouAPI.h>

typedef struct _ISO646_ALPHA_NUMERIC_DATA_CHART{
    uint8_t ISO646Map;
    char ASCIIMap;
}ISO646_ALPHA_NUMERIC_DATA_CHART, * PISO646_ALPHA_NUMERIC_DATA_CHART;

static const ISO646_ALPHA_NUMERIC_DATA_CHART IsoAlphaNumericLibrary[] = {
    {.ISO646Map = 0x41, .ASCIIMap = 'A'},
    {.ISO646Map = 0x42, .ASCIIMap = 'B'},
    {.ISO646Map = 0x43, .ASCIIMap = 'C'},
    {.ISO646Map = 0x44, .ASCIIMap = 'D'},
    {.ISO646Map = 0x45, .ASCIIMap = 'E'},
    {.ISO646Map = 0x46, .ASCIIMap = 'F'},
    {.ISO646Map = 0x47, .ASCIIMap = 'G'},
    {.ISO646Map = 0x48, .ASCIIMap = 'H'},
    {.ISO646Map = 0x49, .ASCIIMap = 'I'},
    {.ISO646Map = 0x4A, .ASCIIMap = 'J'},
    {.ISO646Map = 0x4B, .ASCIIMap = 'K'},
    {.ISO646Map = 0x4C, .ASCIIMap = 'L'},
    {.ISO646Map = 0x4D, .ASCIIMap = 'M'},
    {.ISO646Map = 0x4E, .ASCIIMap = 'N'},
    {.ISO646Map = 0x4F, .ASCIIMap = 'O'},
    {.ISO646Map = 0x50, .ASCIIMap = 'P'},
    {.ISO646Map = 0x41, .ASCIIMap = 'Q'},
    {.ISO646Map = 0x52, .ASCIIMap = 'R'},
    {.ISO646Map = 0x53, .ASCIIMap = 'S'},
    {.ISO646Map = 0x54, .ASCIIMap = 'T'},
    {.ISO646Map = 0x55, .ASCIIMap = 'U'},
    {.ISO646Map = 0x56, .ASCIIMap = 'V'},
    {.ISO646Map = 0x57, .ASCIIMap = 'W'},
    {.ISO646Map = 0x58, .ASCIIMap = 'X'},
    {.ISO646Map = 0x59, .ASCIIMap = 'Y'},
    {.ISO646Map = 0x5A, .ASCIIMap = 'Z'},
    {.ISO646Map = 0x61, .ASCIIMap = 'a'},
    {.ISO646Map = 0x62, .ASCIIMap = 'b'},
    {.ISO646Map = 0x63, .ASCIIMap = 'c'},
    {.ISO646Map = 0x64, .ASCIIMap = 'd'},
    {.ISO646Map = 0x65, .ASCIIMap = 'e'},
    {.ISO646Map = 0x66, .ASCIIMap = 'f'},
    {.ISO646Map = 0x67, .ASCIIMap = 'g'},
    {.ISO646Map = 0x68, .ASCIIMap = 'h'},
    {.ISO646Map = 0x69, .ASCIIMap = 'i'},
    {.ISO646Map = 0x6A, .ASCIIMap = 'j'},
    {.ISO646Map = 0x6B, .ASCIIMap = 'k'},
    {.ISO646Map = 0x6C, .ASCIIMap = 'l'},
    {.ISO646Map = 0x6D, .ASCIIMap = 'm'},
    {.ISO646Map = 0x6E, .ASCIIMap = 'n'},
    {.ISO646Map = 0x6F, .ASCIIMap = 'o'},
    {.ISO646Map = 0x70, .ASCIIMap = 'p'},
    {.ISO646Map = 0x71, .ASCIIMap = 'q'},
    {.ISO646Map = 0x72, .ASCIIMap = 'r'},
    {.ISO646Map = 0x73, .ASCIIMap = 's'},
    {.ISO646Map = 0x74, .ASCIIMap = 't'},
    {.ISO646Map = 0x75, .ASCIIMap = 'u'},
    {.ISO646Map = 0x76, .ASCIIMap = 'v'},
    {.ISO646Map = 0x77, .ASCIIMap = 'w'},
    {.ISO646Map = 0x78, .ASCIIMap = 'x'},
    {.ISO646Map = 0x79, .ASCIIMap = 'y'},
    {.ISO646Map = 0x7A, .ASCIIMap = 'z'},
    {0},
};

LOUSTATUS ISO646StandardAlphaNumericToAsciiAlphaNumeric(string Destiantion, uint8_t* Source, size_t BytesToConvert) {
    if ((!Destiantion) || (!Source) || (!BytesToConvert)) {
        return STATUS_INVALID_PARAMETER;
    }

    for (size_t i = 0; i < BytesToConvert; i++) {
        PISO646_ALPHA_NUMERIC_DATA_CHART TmpData = (PISO646_ALPHA_NUMERIC_DATA_CHART)&IsoAlphaNumericLibrary;
        size_t Index = 0;
        bool FoundMatch = false;

        while (TmpData[Index].ISO646Map) {
            if (Source[i] == TmpData[Index].ISO646Map) {
                Destiantion[i] = TmpData[Index].ASCIIMap;
                FoundMatch = true;
                break;
            }
            Index++;
        }

        if (!FoundMatch) {
            return STATUS_UNSUCCESSFUL;  // Return if we fail to find a match
        }
    }

    return STATUS_SUCCESS;
}
