#ifndef _LKRS_NAMESPACE_H
#define _LKRS_NAMESPACE_H

typedef uint8_t LKRS_NAMESPACE, * PLKRS_NAMESPACE;


#define LKRS_NAMESPACE                      "NAMESPACE::"
#define LKRS_BYTE                           "BYTE::"
#define LKRS_WORD                           "WORD::"
#define LKRS_DWORD                          "DWORD::"
#define LKRS_QWORD                          "QWORD::"
#define LKRS_STRING                         "STRING::"
#define LKRS_STRUCTURE                      "STRUCTURE_DECLARATION::"
#define LKRS_NAMESPACE_HEADER_END           "NAMESPACE_HEADER_END"

typedef struct _STRING_DECLARATION{
    char*    StringData;
    uint8_t  NameLength;
    char*    DeclarationName;
}STRING_DECLARATION, * PSTRING_DECLARATION;

typedef struct _BYTE_DECLARATION{
    uint8_t ByteData;
    uint8_t NameLength;
    char*   DeclarationName;
}BYTE_DECLARATION, * PBYTE_DECLARATION;

typedef struct _WORD_DECLARATION{
    uint16_t WordData;
    uint8_t  NameLength;
    char*    DeclarationName;
}WORD_DECLARATION, * PWORD_DECLARATION;

typedef struct _DWORD_DECLARATION{
    uint16_t DWordData;
    uint8_t  NameLength;
    char*    DeclarationName;
}DWORD_DECLARATION, * PDWORD_DECLARATION;

typedef struct _QWORD_DECLARATION{
    uint16_t DWordData;
    uint8_t  NameLength;
    char*    DeclarationName;
}QWORD_DECLARATION, * PQWORD_DECLARATION;

typedef struct _STRUCTURE_DECLARATION{
    struct _STRUCTURE_DECLARATION*              NextDeclaration;
    uint8_t                                     NameLength;
    uint8_t                                     StructMemberCount;
    char*                                       StructureName;
    char*                                       CompilerTag;
    struct{
        uint8_t                                 Opcode;
        union{
            STRING_DECLARATION                  String;
            BYTE_DECLARATION                    Byte;
            WORD_DECLARATION                    Word;
            DWORD_DECLARATION                   DWord;
            QWORD_DECLARATION                   QWord;
            struct _STRUCTURE_DECLARATION*      Struct;
        };
    }StructMembers[];
}STRUCTURE_DECLARATION, * PSTRUCTURE_DECLARATION;

typedef struct _LKRS_NAMESPACE_HANDLE_TREE{
    struct _LKRS_NAMESPACE_HANDLE_TREE* NextTreeEntry;
    uint8_t                             Opcode;
    union{
        STRING_DECLARATION              String;
        BYTE_DECLARATION                Byte;
        WORD_DECLARATION                Word;
        DWORD_DECLARATION               DWord;
        QWORD_DECLARATION               QWord;
        PSTRUCTURE_DECLARATION          Struct;
    };
}LKRS_NAMESPACE_HANDLE_TREE, * PLKRS_NAMESPACE_HANDLE_TREE;;

typedef struct _LKRS_NAMESPACE_NODE{
    struct _LKRS_NAMESPACE_NODE*    NextNode;
    struct{
        char*                       NodeName;
        size_t                      DataRef;
        size_t                      NodeDataSize;
        char*                       NodeData;
        size_t                      CurrentWriteIndex;
        char*                       CompilationBuffer;
        LKRS_NAMESPACE_HANDLE_TREE  NodeTree;
    };
}LKRS_NAMESPACE_NODE, * PLKRS_NAMESPACE_NODE;


#endif