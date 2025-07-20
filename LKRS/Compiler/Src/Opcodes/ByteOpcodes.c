#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <Lkrs.h>

static size_t LkrsByteDeclarationFindLineTerminator(char* ByteBuffer){
    size_t i = 0;
    while(ByteBuffer[i] != ';'){

        i++;
    }
    return i;
}

static size_t LkrsGetByteNameLength(char* ByteBuffer, char** Name){
    size_t Length = 0;
    size_t Fubar = 0;
    bool Null1 = false;
    while(1){
        if(Name){
            if((!Name[0]) && (ByteBuffer[Length] != ' ')){
                Name[0] = &ByteBuffer[Length];
            }
        }
        if(ByteBuffer[Length] == ' '){
            Null1 = true;
            Fubar++;
        }else if(ByteBuffer[Length] == '=' || (ByteBuffer[Length] == ';')){
            break;
        }else if((Null1) && (ByteBuffer[Length] == ' ')){
            return (uint8_t)-1;
        }
        Length++;
    }
    return Length - Fubar;
}

static size_t LkrsGetByteDataIndex(char* ByteBuffer){
    size_t Length = 1;
    while(1){
        if((ByteBuffer[Length] == ' ') || (ByteBuffer[Length] == '=')){
            Length++;
        }else {
            break;
        }
    }
    return Length;
}

size_t LkrsGetByteDataLength(char* ByteBuffer){
    size_t Length = 0;
    while(1){
        if((ByteBuffer[Length] == ' ') || (ByteBuffer[Length] == ';')){
            break;
        }
        Length++;
    }
    return Length;
}

typedef struct _ASCII_TO_HEX_MAP{
    uint8_t Hexmal;
    char    Charecter;
}ASCII_TO_HEX_MAP, * PASCII_TO_HEX_MAP;

static ASCII_TO_HEX_MAP HexmalMap[22] = {
    {.Hexmal = 0, .Charecter = '0'},
    {.Hexmal = 1, .Charecter = '1'},
    {.Hexmal = 2, .Charecter = '2'},
    {.Hexmal = 3, .Charecter = '3'},
    {.Hexmal = 4, .Charecter = '4'},
    {.Hexmal = 5, .Charecter = '5'},
    {.Hexmal = 6, .Charecter = '6'},
    {.Hexmal = 7, .Charecter = '7'},
    {.Hexmal = 8, .Charecter = '8'},
    {.Hexmal = 9, .Charecter = '9'},
    {.Hexmal = 10, .Charecter = 'A'},
    {.Hexmal = 11, .Charecter = 'B'},
    {.Hexmal = 12, .Charecter = 'C'},
    {.Hexmal = 13, .Charecter = 'D'},
    {.Hexmal = 14, .Charecter = 'E'},
    {.Hexmal = 15, .Charecter = 'F'},
    {.Hexmal = 10, .Charecter = 'a'},
    {.Hexmal = 11, .Charecter = 'b'},
    {.Hexmal = 12, .Charecter = 'c'},
    {.Hexmal = 13, .Charecter = 'f'},
    {.Hexmal = 14, .Charecter = 'e'},
    {.Hexmal = 15, .Charecter = 'f'},
};

static uint8_t StringHexToNible(char Byte){
    for(uint8_t i = 0 ; i < 22; i++){
        if(HexmalMap[i].Charecter == Byte){
            return HexmalMap[i].Hexmal;
        }
    }
    return 16;
}

static uint8_t LkrsGetByteData(char* ByteData){
    uint8_t Result = 0;
    if((!strncmp(ByteData, "0x", 2)) || (!strncmp(ByteData, "0X", 2))){
        Result = ((StringHexToNible(ByteData[2]) & 0x0F) << 4);
        Result |= (StringHexToNible(ByteData[3]) & 0x0F);
        return Result;
    }
    return 0;
}


size_t LkrsCreateByteOpcodeHandle(PLKRS_NAMESPACE_HANDLE_TREE TreeHandle, char* ByteBuffer){
    char* Name = 0;
    size_t Foo = strlen(LKRS_BYTE);
    TreeHandle->Byte.NameLength = LkrsGetByteNameLength(&ByteBuffer[Foo], &Name);
    if(TreeHandle->Byte.NameLength == (uint8_t)-1){
        return 1;
    }
    TreeHandle->Byte.DeclarationName = LkrsMalloc(TreeHandle->Byte.NameLength);
    strncpy(TreeHandle->Byte.DeclarationName, &ByteBuffer[Foo], TreeHandle->Byte.NameLength);
    size_t Increment = 2;
    Increment += TreeHandle->Byte.NameLength;
    Foo += TreeHandle->Byte.NameLength;
    size_t Bar = LkrsGetByteDataIndex(&ByteBuffer[Foo]);
    
    TreeHandle->Byte.ByteData = LkrsGetByteData(&ByteBuffer[Foo + Bar]);

    TreeHandle->Opcode = LKRS_BYTE_OPCODE;
    Increment += 1;//one for byte data
    return Increment;
}

size_t LkrsIncrementByteType(char* ByteBuffer){
    size_t Increment =  LkrsGetByteNameLength(ByteBuffer, 0x00);
    Increment += LkrsGetByteDataIndex(&ByteBuffer[Increment]);
    return LkrsGetByteDataLength(&ByteBuffer[Increment]);
}

size_t LkrsIncrementByteDeclaration(char* ByteBuffer){
    return LkrsGetByteNameLength(ByteBuffer, 0x00);
}

int LkrsWriteByteDataToFile(
    PLKRS_NAMESPACE_NODE NameNode, 
    PLKRS_NAMESPACE_HANDLE_TREE ByteHandle
){
    char* DataBuffer = NameNode->CompilationBuffer;
    size_t WriteIndex = NameNode->CurrentWriteIndex;

    DataBuffer[WriteIndex++] = LKRS_BYTE_OPCODE;
    DataBuffer[WriteIndex++] = ByteHandle->Byte.NameLength;
    strncpy(&DataBuffer[WriteIndex], ByteHandle->Byte.DeclarationName ,ByteHandle->Byte.NameLength);
    WriteIndex += ByteHandle->Byte.NameLength;
    DataBuffer[WriteIndex++] = ByteHandle->Byte.ByteData;
    NameNode->CurrentWriteIndex = WriteIndex;
    return 0;
}

size_t LkrsCountByteDeclarationSize(char* ByteBuffer){
    size_t Foo = strlen(LKRS_BYTE);
    size_t NameLength = LkrsGetByteNameLength(&ByteBuffer[Foo], 0x00);
    return NameLength + 3;//op, namesize, (name), Byte; 
}

size_t LkrsCountByteDeclarationSourceLength(char* ByteBuffer){
    return LkrsGetLineTerminator(ByteBuffer);
}