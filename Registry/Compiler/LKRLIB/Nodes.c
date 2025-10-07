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
        static const char Tmp[] = {'\\', 0x00, '/', 0x00, 0x00, 0x00};
        static uint16_t Foo[3];
        memcpy(Foo, Tmp, 3 * sizeof(uint16_t));
        Slash = Lou_wcspbrk(Entry, (LPWSTR)Foo);
        if(!Slash){
            break;
        }
        Found = false;

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
        }else{
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