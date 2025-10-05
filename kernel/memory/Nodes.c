#include <LouAPI.h>

typedef struct _LOUSINE_NODE_LIST{
    struct _LOUSINE_NODE_LIST*   Forward;
    struct _LOUSINE_NODE_LIST*   Aftward;
    struct _LOUSINE_NODE_LIST*   Downward;
    struct _LOUSINE_NODE_LIST*   Upward;
}LOUSINE_NODE_LIST, * PLOUSINE_NODE_LIST;


typedef struct _LOUSINE_NODE{
    LOUSINE_NODE_LIST       NodePeers;
    LPWSTR                  NodeID;
    LPWSTR                  DirectoryName;
    PVOID                   NodeData;
}LOUSINE_NODE, * PLOUSINE_NODE;

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
        if(!wcscmp(Checksum->NodeID, NodeID)){
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
        Slash = wcspbrk(Entry, L"\\/");
        if(!Slash){
            break;
        }
        Found = false;

        while(TmpHeader->NodePeers.Forward){
            TmpHeader = (PLOUSINE_NODE)TmpHeader->NodePeers.Forward;
            if(!wcsncmp(Entry, TmpHeader->DirectoryName, Slash - Entry) && ((size_t)(Slash - Entry) == wcslen(TmpHeader->DirectoryName))){
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
        if(!wcsncmp(Entry, TmpHeader->DirectoryName, wcslen(Entry)) && (wcslen(Entry) == wcslen(TmpHeader->DirectoryName))){
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

LOUSTATUS 
LouKeAddLousineNodeEntryToHeader(
    PLOUSINE_NODE           NodeHeader,
    LPWSTR                  Entry,
    PVOID                   Data
){
    PLOUSINE_NODE NewNode = GetLousineNodeEntry(NodeHeader, Entry, true);

    NewNode->NodeData = Data;

    return STATUS_SUCCESS;
}



LOUSTATUS 
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
        if(!wcscmp(Checksum->NodeID, TreeName)){
            FoundTree = true;
            break;
        }
    }
    if(!FoundTree){
        return STATUS_INVALID_PARAMETER;
    }
    return LouKeAddLousineNodeEntryToHeader(
        Checksum,
        Entry,
        Data
    );
}