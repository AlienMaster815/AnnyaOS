#include <LouAPI.h>


#define KERNEL_REGISTRY_SOURCE_FILE_HEADER  L"Lousine Kernel Registry File Source"
#define COMENT_LINE                         L"//"
#define COMENT_OPEN                         L"/*"
#define COMENT_CLOSE                        L"*/"
#define ITEM_DECLARATION                    L"\""
#define ITEM_TERMINATION                    ITEM_DECLARATION
#define STRING_ITEM_TYPE                    L"STRING"
#define BYTE_ITEM_TYPE                      L"BYTE"
#define WORD_ITEM_TYPE                      L"WORD"
#define DWORD_ITEM_TYPE                     L"WORD"
#define QWORD_ITEM_TYPE                     L"WORD"
#define STRUCTURE_ITEM_TYPE                 L"DEFINE_STRUCTURE"
#define STRUCTURE_REFERENCE                 L"DECLARE_STRUCTURE"
#define CODE_TERMINATOR                     L";"
#define NAMESPACE_OPEN                      L"["
#define NAMESPACE_CLOSE                     L"]"
#define ARRAY_DECLARATION                   L"DECLARE_ARRAY"

static uintptr_t BootRegistryBase = 0; 
static uintptr_t BootRegistryTop = 0; 

void InitializeBootRegistry(uintptr_t Base, uintptr_t Top){
    BootRegistryBase = Base;
    BootRegistryTop = Top;
}

LOUSTATUS LouKeInitializeRegistry(){
    LouPrint("LouKeInitializeRegistry()\n");



    while(1);
    return STATUS_SUCCESS;
}