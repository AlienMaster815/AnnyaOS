/*#ifndef _NTOSKRNL_LIB
#define _NTOSKRNL_LIB

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _KERNEL_MODULE_
string strtok_s(
    string str,
    string Delimiters,
    string* Context
);



size_t strspn(
   string str,
   string strCharSet
);

string strrchr(
   string str,
   int c
);

int sscanf_s(
    char *buffer,
    char *format, 
    va_list va_arg
);

int _sscanf_s_l(
    char *buffer,
    char *format,
    va_list va_arg
);

int swscanf_s(
    wchar_t* buffer,
    wchar_t* format, 
    va_list va_arg
);
int _swscanf_s_l(
    wchar_t* buffer,
    wchar_t* format, 
    va_list va_arg
);

int strncpy_s(
    string Destination,
    size_t ElementsCount,
    string Source,
    size_t Count
);


string strncat(
    string Destination,
    string Source,
    size_t Count
);

int strcpy_s(
    string Destination,
    size_t DestinationSize,
    string Source
);

int strcat_s(
    string Destination,
    size_t Elements,
    string Source
);

void *memmove(void *dest, const void *src, size_t n);

void srand(
    unsigned int seed
);

int rand();

float sqrtf(
    float x
);

double sqrt(
    double x
);

//Add To Table


int sprintf(char *buffer, const char *format, ...);

int vsprintf(char *buffer, const char *format, va_list args);

LOUSTATUS HeadlessDispatch(
    uint32_t DispatchCommand, 
    uint32_t* CommandData, 
    uint64_t Flags, 
    uint8_t* HeadlessLocal, 
    uint64_t* size
);

void RtlRaiseStatus(LOUSTATUS Status);
 
int64_t InterlockedPushListSList(
    uint64_t* InputList, 
    uint64_t  Unused2,
    uint64_t* OutputList,
    uint16_t  Unused4
);

int512_t InitializeSListHead(__int128* InitData);



#else //Is Kernel Module

#endif //KernelModues
#ifdef __cplusplus
}
#endif
*/