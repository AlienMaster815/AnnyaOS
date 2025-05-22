#include <LouAPI.h>


//TODO{
void ScsiDone(PSCSI_COMMAND ScsiCommand){

}

void ScsiDoneDirect(PSCSI_COMMAND ScsiCommand){


}
void ScsiFinishCommand(PSCSI_COMMAND ScsiCommand){
    
}

void* LouKeScsiMapAtomicScatterGather(PSCATTER_LIST ScatterGather, int ScatterGatherCount, uint64_t* Offset, uint64_t* Length){

    return 0x00;
}

void  LouKeScsiUnMapAtomicScatterGather(void* VirtualHandle){

}

LOUSTATUS ScsiAllocateScatterGatherTables(PSCSI_COMMAND ScsiCommand){

    return STATUS_SUCCESS;
}

LOUSTATUS LouKeMapScsiDma(PSCSI_COMMAND* ScsiCommand){
    return STATUS_SUCCESS;
}

void LouKeUnMapScsiDma(PSCSI_COMMAND    ScsiCommand){

}

//}

//More TODO {
void ScsiBuildSenceData(PSCSI_COMMAND ScsiCommand, int32_t Descriptor, uint8_t Key, uint8_t Ascync, uint8_t AsyncrQ){

}
//void* ScsiAllocateReques();

//}
