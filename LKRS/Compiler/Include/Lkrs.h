
#ifndef _LKRS_H
#define _LKRS_H

#include "namespace.h"
#include "SiHelpers.h"

#define LKRS_INVALID_OPCODE                     0x00
#define LKRS_NAMESPACE_DECLARATION_OPCODE       0x01    
#define LKRS_STRUCTURE_DECLARATION              0x02
//#define LKRS_PCI_DEVICE_OPCODE                  0x03
#define LKRS_WORD_OPCODE                        0x04
#define LKRS_DWORD_OPCODE                       0x05
#define LKRS_BYTE_OPCODE                        0x06
#define LKRS_QWORD_OPCODE                       0x07
//#define LKRS_PCI_DEVICE_REGISTRY_END_OPCODE     0x08
#define LKRS_STRING_OPCODE                      0x09
#define LKRS_NAMESPACE_DATA_START               0x0A
#define LKRS_NAMESPACE_DATA_END                 0x0B
#define LKRS_ZERO_OPCODE                        0x0C

typedef struct _KERNEL_REGISTRY_SOURCE_HANDLE{
    FILE*                   Krf;
    size_t                  KrfSize;
    uint8_t*                KrfData;
    size_t                  CompiledSize;
    uint8_t*                CompiledData;
    LKRS_NAMESPACE_NODE     NameNodes;
}KERNEL_REGISTRY_SOURCE_HANDLE, * PKERNEL_REGISTRY_SOURCE_HANDLE;

int WalkSourceNamespaceDeclarations(PKERNEL_REGISTRY_SOURCE_HANDLE KrsFile);
int LkrsCompileSourceFile(PKERNEL_REGISTRY_SOURCE_HANDLE KrsFile);
int LkrsBuildGlobalNameSpaceDefinitions(PKERNEL_REGISTRY_SOURCE_HANDLE KrfHandle);
size_t LkrsGetNameSpaceSize(PLKRS_NAMESPACE_NODE Node);
int LkrsBuildNameSpaceData(PKERNEL_REGISTRY_SOURCE_HANDLE KrfHandle);
size_t CountNameSpaceData(PLKRS_NAMESPACE_NODE NameNode);
char* LkrsGetNameSpaceEntryFromRawStreamSafe(char* Stream, size_t StreamSize, char* NameSpaceVariable);
void LkrsWriteUint64(char* Base, uint64_t Data);
size_t LkrsCreateByteOpcodeHandle(PLKRS_NAMESPACE_HANDLE_TREE TreeHandle, char* ByteBuffer);
size_t LkrsIncrementByteType(char* ByteBuffer);
int WriteNameSpaceToFile(PLKRS_NAMESPACE_NODE NameNode);
int LkrsWriteByteDataToFile(PLKRS_NAMESPACE_NODE NameNode, PLKRS_NAMESPACE_HANDLE_TREE ByteHandle);
size_t LkrsCreateStructureDeclarationHandle(PLKRS_NAMESPACE_HANDLE_TREE MasterTree, PLKRS_NAMESPACE_HANDLE_TREE TreeHandle, char* StructBuffer);
size_t LkrsIncrementStructureDeclaration(char* StructBuffer);
size_t LkrsIncrementByteDeclaration(char* ByteBuffer);
size_t LkrsCountByteDeclarationSize(char* ByteBuffer);
size_t LkrsCountWordDeclarationSize(char* WordBuffer);
size_t LkrsCountStringDeclarationSize(char* StringBuffer);
size_t LkrsCountByteDeclarationSourceLength(char* ByteBuffer);
size_t LkrsCountWordDeclarationSourceLength(char* ByteBuffer);
size_t LkrsCountStringDeclarationSourceLength(char* StringBuffer);

#ifdef _KERNEL_COMPILER_
#define LkrsMallocType(x) (x*)LouKeMallocType(sizeof(x), KERNEL_GENERIC_MEMORY)
#define LkrsMalloc(x) LouKeMalloc(x, KERNEL_GENERIC_MEMORY)
#else
#define LkrsMallocType(x) (x*)malloc(sizeof(x))
#define LkrsMalloc(x) malloc(x)
#endif

#endif