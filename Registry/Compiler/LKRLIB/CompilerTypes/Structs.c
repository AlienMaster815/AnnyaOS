#include <Compiler.h>


/*size_t 
LkrStructureGetCount(
    LPWSTR      Buffer, 
    size_t      Length
){


    return 0;
}*/

LPWSTR GetDeclaration(
    LPWSTR Buffer, 
    LPWSTR Data,
    LPWSTR* DataEnd
);

errno_t 
LouKeLexerWcsWithoutTerminator(
    LPWSTR              Buffer,
    LPWSTR              OpenToken,
    size_t              Length,
    LEXER_HANLDER       Handler,
    PVOID               Data
);

typedef struct _LKR_STRUCT_DESCRIPOTR{
    size_t NextDescriptor;
    size_t DescriptorSize;
    size_t NameSize;
    size_t TypeSize;
    size_t DataSize;
}LKR_STRUCT_DESCRIPOTR, * PLKR_STRUCT_DESCRIPOTR;


static errno_t StructrueDescriptorConstructor(
    UNUSED LPWSTR  Buffer,
    UNUSED size_t  Length,
    UNUSED PVOID   Data
){
    //SanityCheck(Buffer, Length);
    PLKR_STRUCT_DESCRIPOTR Tmp = (PLKR_STRUCT_DESCRIPOTR)Data;
    while(Tmp->NextDescriptor){
        Tmp = (PLKR_STRUCT_DESCRIPOTR)Tmp->NextDescriptor;
    }
    
    LPWSTR StructueHint = Lou_wcsnstr(Buffer, CompilerDeclarationLookup(":"), Length);
    size_t TmpLength = StructueHint ? (size_t)(StructueHint - Buffer) : Length;
    LPWSTR Last = 0;
    LPWSTR Declaration = GetDeclaration(Buffer, (Buffer + TmpLength), &Last);
    size_t TypeSize = (Last - Declaration);

    LPWSTR Name = Lou_wcsnstr(Buffer, CompilerDeclarationLookup("\""), Declaration - Buffer);
    Name++;
    LPWSTR NameEnd = Lou_wcsnstr(Name + 1, CompilerDeclarationLookup("\""), Declaration - (Name + 1));
    size_t NameLength = NameEnd - Name;
    size_t DataSize = LkrParserGetTypeSize(Declaration, TypeSize);
    

    size_t DescriptorSize =  sizeof(LKR_STRUCT_DESCRIPOTR) + ((NameLength + 1) * sizeof(WCHAR)) + ((TypeSize + 1) * sizeof(WCHAR)) + (DataSize);
    Tmp->NextDescriptor = (size_t)LouKeMalloc(
        DescriptorSize,
        KERNEL_GENERIC_MEMORY
    );
    Tmp = (PLKR_STRUCT_DESCRIPOTR)Tmp->NextDescriptor;
    Tmp->DescriptorSize = DescriptorSize;
    Tmp->NameSize = NameLength;
    Tmp->TypeSize = TypeSize;
    Tmp->DataSize = DataSize;

    uint8_t* DescriptorBuffer = ((uint8_t*)Tmp + sizeof(LKR_STRUCT_DESCRIPOTR));
    LPWSTR Names = (LPWSTR)DescriptorBuffer; 
    Lou_wcsncpy(Names, Name, NameLength);
    Names += NameLength + 1;
    Lou_wcsncpy(Names, Declaration, TypeSize);
    //skip data now for null until an actual declaration forks the template
    //ALSO NOTE: this data will not be compiled into the LKR systems this is
    //a compiler definition "Fork Resource" for Source
    return 0;
}



errno_t LkrCreateStructureDefinitionDescriptor(
    LPWSTR      Buffer,
    size_t*     Length,
    PVOID*      OutDecsriptor
){
    if((!Length) || (!Buffer) || (!OutDecsriptor)){
        return EINVAL;
    }
    size_t InBufferLength = *Length;
    
    LKR_STRUCT_DESCRIPOTR ConstructorList =  {0};

    LouKeLexerWcsWithMultiCharecterTermination(
        Buffer,
        CompilerDeclarationLookup("\""),
        CompilerDeclarationLookup(",}"),
        InBufferLength,
        StructrueDescriptorConstructor, 
        (PVOID)&ConstructorList
    );

    PLKR_STRUCT_DESCRIPOTR Tmp = (PLKR_STRUCT_DESCRIPOTR)ConstructorList.NextDescriptor;
    UNUSED PLKR_STRUCT_DESCRIPOTR CompiledData;
    UNUSED PLKR_STRUCT_DESCRIPOTR TmpCompiledData;
    PLKR_STRUCT_DESCRIPOTR Next;
    size_t ArrayLength = 0;
    while(Tmp){        
        ArrayLength += ROUND_UP64(Tmp->DescriptorSize, 8);
        Tmp = (PLKR_STRUCT_DESCRIPOTR)Tmp->NextDescriptor;
    }

    CompiledData = (PLKR_STRUCT_DESCRIPOTR)LouKeMalloc(ArrayLength, KERNEL_GENERIC_MEMORY);
    TmpCompiledData = CompiledData;
    Tmp = (PLKR_STRUCT_DESCRIPOTR)ConstructorList.NextDescriptor;
    
    while(Tmp){
        memcpy(TmpCompiledData, Tmp, Tmp->DescriptorSize);
        if(Tmp->NextDescriptor){
            TmpCompiledData->NextDescriptor = ROUND_UP64(Tmp->DescriptorSize, 8);
        }
        TmpCompiledData = (PLKR_STRUCT_DESCRIPOTR)((uint8_t*)TmpCompiledData + TmpCompiledData->NextDescriptor);
        Tmp = (PLKR_STRUCT_DESCRIPOTR)Tmp->NextDescriptor;
    }

    Tmp = (PLKR_STRUCT_DESCRIPOTR)ConstructorList.NextDescriptor;

    while(Tmp){
        Next = (PLKR_STRUCT_DESCRIPOTR)Tmp->NextDescriptor;
        LouKeFree(Tmp);
        Tmp = (PLKR_STRUCT_DESCRIPOTR)Next;
    }

    *Length = ArrayLength;
    *OutDecsriptor = (PVOID)CompiledData;

    return 0;
}

errno_t LkrAssmblerForkStructureData(
    LPWSTR  tName,
    size_t  NameLength,    
    LPWSTR  ObjectName,
    size_t  ObjectSize,
    PVOID*  OutData,
    PVOID   tContext
){
    if((!OutData) || (!tContext) || (!tName)){
        return EINVAL;
    }
    PCOMPILER_CONTEXT Context = (PCOMPILER_CONTEXT)tContext;
    LPWSTR Name = LouKeForkWcsStr_s(tName, NameLength);
    LPWSTR Object = LouKeForkWcsStr_s(ObjectName, ObjectSize);
    errno_t Result = 0;
    PLOUSINE_NODE ForkNode = LouKeSearchNodeNameSpace(
        Context->CompilerNode,
        Context->NodeContext.CurrentDirectory,
        Object
    );

    if(!ForkNode){
        return -1;
    }

    PLKR_NODE_ENTRY Node = ForkNode->NodeData;

    size_t NodeSize = LkrGetNodeSize(Node);

    PLKR_NODE_ENTRY NewNode = LkrAllocateNode(
        Name,
        NodeSize
    );
    
    Result = LkrFillNodeData(
        NewNode,
        (PVOID)Node,
        NodeSize
    );

    LouKeFree(Name);
    LouKeFree(Object);
    *OutData = (PVOID)NewNode;
    return Result;
}


errno_t LkrHandleStrcutureCreation(
    UNUSED LPWSTR   Buffer,
    UNUSED size_t   Length,
    UNUSED LPWSTR   NameIndex,
    UNUSED LPWSTR   NameEndIndex,
    UNUSED LPWSTR   DeclarationIndex,
    UNUSED LPWSTR   DataIndex,
    UNUSED PVOID    Data
){
    PVOID ForkedResource = 0x00;  
    errno_t Result = 0;
    Result = LkrAssmblerForkStructureData(
        NameIndex,
        NameEndIndex - NameIndex, 
        DataIndex,
        DataIndex - DeclarationIndex,
        &ForkedResource,
        Data
    );

    if(Result){
        return Result;
    }

    //printf("LkrHandleStrcutureCreation()\n");
    
    PLKR_NODE_ENTRY StructResource = (PLKR_NODE_ENTRY)LkrGetNodeData(ForkedResource);
    //printf("Name Size:%zu\n", StructResource->NameSize);

    PVOID StructureData = (PVOID)LkrOpenNodeData(StructResource);

    SanityCheck(LkrGetNodeName(StructResource), StructResource->NameSize);

    PLKR_STRUCT_DESCRIPOTR Descriptor = (PLKR_STRUCT_DESCRIPOTR)StructureData;
    size_t Members = 0;
    while(1){
        Members++;
        if(!Descriptor->NextDescriptor){
            break;
        }
        Descriptor = (PLKR_STRUCT_DESCRIPOTR)((size_t)Descriptor + Descriptor->NextDescriptor);
    }

    printf("Mebers:%zu\n", Members);

    LkrCloseNodeData(StructResource, StructureData);

    LkrParserCreateNode(
        NameIndex,
        NameEndIndex - NameIndex,
        Data,
        (PVOID)ForkedResource
    );
 
    return 0;
}

errno_t LkrHandleStrcutureDefinition(
    UNUSED LPWSTR   Buffer,
    UNUSED size_t   Length,
    UNUSED LPWSTR   NameIndex,
    UNUSED LPWSTR   NameEndIndex,
    UNUSED LPWSTR   DeclarationIndex,
    UNUSED LPWSTR   DataIndex,
    UNUSED PVOID    Data
){
    errno_t Result = 0;
    size_t DataLength = Length - (DataIndex - Buffer);
    PVOID Descriptor = 0;

    Result = LkrCreateStructureDefinitionDescriptor(
        DataIndex,
        &DataLength,
        &Descriptor
    );

    LPWSTR NewName = LouKeForkWcsStr_s(NameIndex, NameEndIndex - NameIndex);

    PLKR_NODE_ENTRY NewNode = LkrAllocateNode(
        NewName,
        DataLength
    );

    Result = LkrFillNodeData(
        NewNode,
        Descriptor,
        DataLength
    );

    LouKeFree(NewName);

    if(Result){
        return Result;
    }

    LkrParserCreateNode(
        NameIndex,
        NameEndIndex - NameIndex,
        Data,
        NewNode
    );
    return 0;
}