#include <Lkrs.h>

size_t CountNameSpaceData(PLKRS_NAMESPACE_NODE NameNode){
    size_t CompiledSize = 2;
    char*  SearchAnchor = NameNode->NodeData;
    size_t SearchLength = NameNode->NodeDataSize;
    size_t SearchIndex = 0;
    PLKRS_NAMESPACE_HANDLE_TREE TreeHandle = &NameNode->NodeTree;
    while(SearchIndex < SearchLength){
        if(!strncmp(&SearchAnchor[SearchIndex], LKRS_BYTE, strlen(LKRS_BYTE))){
            CompiledSize += LkrsCreateByteOpcodeHandle(TreeHandle, &SearchAnchor[SearchIndex]);
            SearchIndex += LkrsIncrementByteType(&SearchAnchor[SearchIndex]);
            TreeHandle->NextTreeEntry = LkrsMallocType(LKRS_NAMESPACE_HANDLE_TREE);
            TreeHandle = TreeHandle->NextTreeEntry;
        }else if(!strncmp(&SearchAnchor[SearchIndex], LKRS_STRUCTURE, strlen(LKRS_STRUCTURE))){
            LkrsCreateStructureDeclarationHandle(&NameNode->NodeTree, TreeHandle, &SearchAnchor[SearchIndex]);
            SearchIndex += LkrsIncrementStructureDeclaration(&SearchAnchor[SearchIndex]);
        }else{
            SearchIndex++;
        }
    }
    return CompiledSize;
}

int WriteNameSpaceToFile(PLKRS_NAMESPACE_NODE NameNode){
    PLKRS_NAMESPACE_HANDLE_TREE TreeHandle = &NameNode->NodeTree;

    while(TreeHandle->NextTreeEntry){

        switch(TreeHandle->Opcode){
            case LKRS_BYTE_OPCODE:
                LkrsWriteByteDataToFile(NameNode, TreeHandle);
                break;
        }
        
        TreeHandle = TreeHandle->NextTreeEntry;
    }

    return 0;
}