#include <Compiler.h>

typedef struct _LOUSINE_NODE_TRACKER{
    ListHeader              Peers;
    PLOUSINE_NODE           TreeRoot; 
}LOUSINE_NODE_TRACKER, * PLOUSINE_NODE_TRACKER;

static LOUSINE_NODE_TRACKER NodeTreeLookup = {0}; 


PLOUSINE_NODE LouKeCreateLousineNode(
    LPWSTR  NodeID
){
    PLOUSINE_NODE_TRACKER Tmp = &NodeTreeLookup;
    PLOUSINE_NODE NewNode;
    while(Tmp->Peers.NextHeader){
        Tmp = (PLOUSINE_NODE_TRACKER)Tmp->Peers.NextHeader;
        PLOUSINE_NODE Checksum = Tmp->TreeRoot;
        if(!Lou_wcscmp(Checksum->NodeID, NodeID)){
            return Checksum;
        }
    }
    Tmp->Peers.NextHeader = (PListHeader)LouKeMallocType(LOUSINE_NODE_TRACKER, KERNEL_GENERIC_MEMORY);
    Tmp = (PLOUSINE_NODE_TRACKER)Tmp->Peers.NextHeader;
    NewNode = LouKeMallocType(LOUSINE_NODE, KERNEL_GENERIC_MEMORY);
    NewNode->NodeID = LouKeForkWcsStr(NodeID);
    NewNode->DirectoryName = 0x00; //root
    Tmp->TreeRoot = NewNode;
    return NewNode;
}

static
PLOUSINE_NODE 
GetLousineNodeEntry(
    PLOUSINE_NODE   NodeHeader,
    LPWSTR          Entry,
    bool            ModificationApplied
){
    LPWSTR Slash = 0x00;
    bool Found;
    PLOUSINE_NODE TmpHeader = NodeHeader;

    while(1){
        Found = false;

        Slash = Lou_wcspbrk(Entry, CompilerDeclarationLookup("\\/"));
        if(!Slash){
            break;
        }

        while(TmpHeader->NodePeers.Forward){
            TmpHeader = (PLOUSINE_NODE)TmpHeader->NodePeers.Forward;
            if(!Lou_wcsncmp(Entry, TmpHeader->DirectoryName, Slash - Entry) && ((size_t)(Slash - Entry) == Lou_wcslen(TmpHeader->DirectoryName))){
                Found = true;
                if(!TmpHeader->NodePeers.Downward && ModificationApplied){
                    TmpHeader->NodePeers.Downward = (PLOUSINE_NODE_LIST)LouKeMallocType(LOUSINE_NODE, KERNEL_GENERIC_MEMORY);
                    ((PLOUSINE_NODE)TmpHeader->NodePeers.Downward)->NodePeers.Upward = (PLOUSINE_NODE_LIST)TmpHeader; 
                    TmpHeader = (PLOUSINE_NODE)TmpHeader->NodePeers.Downward;
                    TmpHeader->NodeID = NodeHeader->NodeID; 
                }
                else if(TmpHeader->NodePeers.Downward){
                    TmpHeader = (PLOUSINE_NODE)TmpHeader->NodePeers.Downward;
                }else{
                    return 0x00;
                }
                break;
            }
        }
        if(!Found && ModificationApplied){
            TmpHeader->NodePeers.Forward = (PLOUSINE_NODE_LIST)LouKeMallocType(LOUSINE_NODE, KERNEL_GENERIC_MEMORY);
            ((PLOUSINE_NODE)TmpHeader->NodePeers.Forward)->NodePeers.Aftward = (PLOUSINE_NODE_LIST)TmpHeader; 
            TmpHeader = (PLOUSINE_NODE)TmpHeader->NodePeers.Forward;
            TmpHeader->NodeID = NodeHeader->NodeID;
            TmpHeader->DirectoryName = LouKeForkWcsStr_s(Entry, Slash - Entry);
            if(!TmpHeader->NodePeers.Downward && ModificationApplied){
                TmpHeader->NodePeers.Downward = (PLOUSINE_NODE_LIST)LouKeMallocType(LOUSINE_NODE, KERNEL_GENERIC_MEMORY);
                ((PLOUSINE_NODE)TmpHeader->NodePeers.Downward)->NodePeers.Upward = (PLOUSINE_NODE_LIST)TmpHeader; 
                TmpHeader = (PLOUSINE_NODE)TmpHeader->NodePeers.Downward;
                TmpHeader->NodeID = NodeHeader->NodeID; 
            }else if(TmpHeader->NodePeers.Downward){
                TmpHeader = (PLOUSINE_NODE)TmpHeader->NodePeers.Downward;
            }else{
                return 0x00;
            }
        }else if(!Found){
            return 0x00;
        }
        Entry = Slash + 1;
    }
    
    Found = false;

    while(TmpHeader->NodePeers.Forward){
        TmpHeader = (PLOUSINE_NODE)TmpHeader->NodePeers.Forward;
        if(!Lou_wcsncmp(Entry, TmpHeader->DirectoryName, Lou_wcslen(Entry)) && (Lou_wcslen(Entry) == Lou_wcslen(TmpHeader->DirectoryName))){
            Found = true;
            break;
        }
    }

    if(!Found){
        if(!ModificationApplied){
            return 0x00;
        }
        TmpHeader->NodePeers.Forward = (PLOUSINE_NODE_LIST)LouKeMallocType(LOUSINE_NODE, KERNEL_GENERIC_MEMORY);
        ((PLOUSINE_NODE)TmpHeader->NodePeers.Forward)->NodePeers.Aftward = (PLOUSINE_NODE_LIST)TmpHeader;
        TmpHeader = (PLOUSINE_NODE)TmpHeader->NodePeers.Forward;
        TmpHeader->NodeID = NodeHeader->NodeID;
        TmpHeader->DirectoryName = LouKeForkWcsStr(Entry);
    }

    return TmpHeader;
}

errno_t 
LouKeAddLousineNodeEntryToHeader(
    PLOUSINE_NODE           NodeHeader,
    LPWSTR                  Entry,
    PVOID                   Data
){
    PLOUSINE_NODE NewNode = GetLousineNodeEntry(NodeHeader, Entry, true);

    NewNode->NodeData = Data;

    return 0;
}



errno_t 
LouKeAddLousineNodeEntryToTree(
    LPWSTR      TreeName,
    LPWSTR      Entry,
    PVOID       Data
){
    bool FoundTree = false;
    PLOUSINE_NODE_TRACKER Tmp = &NodeTreeLookup;
    PLOUSINE_NODE Checksum = 0x00;
    while(Tmp->Peers.NextHeader){
        Tmp = (PLOUSINE_NODE_TRACKER)Tmp->Peers.NextHeader;
        Checksum = Tmp->TreeRoot;
        if(!Lou_wcscmp(Checksum->NodeID, TreeName)){
            FoundTree = true;
            break;
        }
    }
    if(!FoundTree){
        return EINVAL;
    }
    return LouKeAddLousineNodeEntryToHeader(
        Checksum,
        Entry,
        Data
    );
}

void
LouKeDestroyLousineNodeTree_r(
    PLOUSINE_NODE NodeTree
){
    PLOUSINE_NODE TmpNode = NodeTree; 
    PLOUSINE_NODE NextNode;
    while(TmpNode){
        NextNode = (PLOUSINE_NODE)TmpNode->NodePeers.Forward;
        if(TmpNode->NodePeers.Downward){
            LouKeDestroyLousineNodeTree_r((PLOUSINE_NODE)TmpNode->NodePeers.Downward);
        }
        LouKeFree(TmpNode->DirectoryName);
        LouKeFree(TmpNode->NodeData);
        LouKeFree(TmpNode);
        TmpNode = NextNode;
    }

}

void
LouKeDestroyLousineNodeTree(
    PLOUSINE_NODE NodeTree
){
    LouKeFree(NodeTree->NodeID);
    LouKeDestroyLousineNodeTree_r(NodeTree);
}

void SanityCheckNodes(
    PLOUSINE_NODE Node
){
    PLOUSINE_NODE TmpNode = Node; 

    while(TmpNode->NodePeers.Forward){
        TmpNode = (PLOUSINE_NODE)TmpNode->NodePeers.Forward;
        SanityCheck(TmpNode->DirectoryName, Lou_wcslen(TmpNode->DirectoryName));
        if(TmpNode->NodePeers.Downward){
            SanityCheckNodes(
                (PLOUSINE_NODE)TmpNode->NodePeers.Downward
            );
        }
    }
}

bool UpDirectory(
    UNUSED LPWSTR   Str,
    UNUSED LPWSTR   ObjectName, 
    UNUSED LPWSTR*  Object
){
    LPWSTR TmpObject = *Object;
    if(TmpObject > Str){
        TmpObject--;

        while((*TmpObject != *(CompilerDeclarationLookup("\\"))) && (*TmpObject != *(CompilerDeclarationLookup("/"))) && (TmpObject > Str)){
            TmpObject--;
        }
        
        memset(TmpObject, 0, Lou_wcslen(TmpObject) * sizeof(WCHAR));
        if(TmpObject > Str){
            Lou_wcsncpy(TmpObject, CompilerDeclarationLookup("\\"), 1);
            Lou_wcscpy(TmpObject + 1, ObjectName);
        }else{
            Lou_wcscpy(TmpObject, ObjectName);
        }

        *Object = TmpObject;

        return true;
    }
    return false;
}

PLOUSINE_NODE LouKeSearchNodeNameSpace(
    UNUSED PLOUSINE_NODE           NodeHeader,
    UNUSED LPWSTR                  DirectoryOrigin,
    UNUSED LPWSTR                  ObjectName
){

    size_t TotalStringSize = (Lou_wcslen(DirectoryOrigin) + 1) + (Lou_wcslen(ObjectName) + 1);
    LPWSTR NewString = LouKeMallocArray(WCHAR, TotalStringSize, KERNEL_GENERIC_MEMORY);
    Lou_wcsncpy(NewString, DirectoryOrigin, Lou_wcslen(DirectoryOrigin));
    Lou_wcsncpy(NewString + Lou_wcslen(DirectoryOrigin), CompilerDeclarationLookup("\\"), 1);
    Lou_wcsncpy(NewString + Lou_wcslen(DirectoryOrigin) + 1, ObjectName, Lou_wcslen(ObjectName));
    LPWSTR Object = NewString + Lou_wcslen(DirectoryOrigin);
    PLOUSINE_NODE Result = 0x00;

    while(1){

        Result = GetLousineNodeEntry(
            NodeHeader,
            NewString,
            false
        );

        if(Result){
            //SanityCheck(NewString, Lou_wcslen(NewString));
            return Result;
        }

        //SanityCheck(NewString, Lou_wcslen(NewString));

        if(!UpDirectory(NewString, ObjectName, &Object)){
            break;
        }
    }

    return 0x00;    
}