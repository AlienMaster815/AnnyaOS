#include <LouAPI.h>

typedef struct _USER_MODE_VMEM_TRACK{
    ListHeader TrackLink;
    uint64_t PAddress;
    uint64_t VAddress;
    uint64_t size;
}USER_MODE_VMEM_TRACK, * PUSER_MODE_VMEM_TRACK;

//static spinlock_t UserAllocLock;

uint64_t LouKeMallocFromMapEx(
    uint64_t BytesNeeded,
    uint64_t Alignement,
    uint64_t MapStart,
    uint64_t MapEnd,
    uint64_t MappedTrack,
    PUSER_MODE_VMEM_TRACK MappedAddresses
){

    uint64_t AlignedAddress = MapStart & ~(Alignement - 1);
    AlignedAddress += BytesNeeded;
    bool AddressValid = false;

    while((AlignedAddress + Alignement) <= MapEnd){
        PUSER_MODE_VMEM_TRACK Tmp = MappedAddresses;

        for(uint64_t i = 0 ; i <= MappedTrack; i++){
            AddressValid = RangeDoesNotInterfere(
                AlignedAddress, 
                BytesNeeded,
                Tmp->VAddress,
                Tmp->size
            );
            if(!AddressValid){
                break;
            }
            if(Tmp->TrackLink.NextHeader){
                Tmp = (PUSER_MODE_VMEM_TRACK)Tmp->TrackLink.NextHeader; 
            }
        }

        if(AddressValid){
            //found a new allocation Register it now
            PUSER_MODE_VMEM_TRACK Tmp = MappedAddresses;
            for(uint64_t i = 0 ; i <= MappedTrack; i++){
                if(Tmp->VAddress == 0x00){
                    break;
                }
                if(Tmp->TrackLink.NextHeader){
                    Tmp = (PUSER_MODE_VMEM_TRACK)Tmp->TrackLink.NextHeader; 
                }
            }

            Tmp->TrackLink.NextHeader = (PListHeader)LouMalloc(sizeof(USER_MODE_VMEM_TRACK));
            Tmp = (PUSER_MODE_VMEM_TRACK)Tmp->TrackLink.NextHeader;
            Tmp->VAddress = AlignedAddress;
            Tmp->size = BytesNeeded;
            return AlignedAddress; 
        }
        AlignedAddress += Alignement;
    }
    return 0x00;
}

uint64_t LouKeMallocFromMap(
    uint64_t BytesNeeded,
    uint64_t MapStart,
    uint64_t MapEnd,
    uint64_t MappedTrack,
    PUSER_MODE_VMEM_TRACK MappedAddresses
){
    return LouKeMallocFromMapEx(
        BytesNeeded,
        BytesNeeded,
        MapStart,
        MapEnd,
        MappedTrack,
        MappedAddresses
    );
}

void LouKeFreeFromMap(
    uint64_t                Address,
    uint64_t*               MappedTrack,
    PUSER_MODE_VMEM_TRACK   MappedAddresses
){
    PUSER_MODE_VMEM_TRACK Tmp = MappedAddresses;
    PUSER_MODE_VMEM_TRACK Tmp2 = MappedAddresses;
    uint64_t TmpTrack = *MappedTrack;
    for(uint64_t i = 0 ; i <= TmpTrack; i++){
        if(Tmp->VAddress == Address){
            if(TmpTrack <= 1){
                Tmp->VAddress = 0x00;
                return;
            }
            for(uint64_t j = 0; j < i; j++){
                if(Tmp2->TrackLink.NextHeader){
                    Tmp2 = (PUSER_MODE_VMEM_TRACK)Tmp2->TrackLink.NextHeader; 
                }    
                Tmp2->TrackLink.NextHeader = (PListHeader)Tmp->TrackLink.NextHeader;
                LouFree((uint8_t*)Tmp);
                *MappedTrack = TmpTrack - 1;;
                return;
            }
        }
        if(Tmp->TrackLink.NextHeader){
            Tmp = (PUSER_MODE_VMEM_TRACK)Tmp->TrackLink.NextHeader; 
        }
    }

}