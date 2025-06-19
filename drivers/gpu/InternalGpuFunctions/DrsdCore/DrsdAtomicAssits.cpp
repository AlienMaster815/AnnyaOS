#include "DrsdCore.h"

void DrsdPropertyDestroyBlob(PDRSD_PROPERTY_BLOB Blob){
    if(Blob){
        DrsdModeObjectObjectFree(&Blob->Base);
    }
}

void DrsdAtomicDestroyPlaneState(
    PDRSD_PLANE_STATE PlaneState
){
    if(PlaneState->FrameBuffer){
        DrsdModeObjectObjectFree(&PlaneState->FrameBuffer->Base);
    }

    if(LouKeGetAtomic(&PlaneState->Fence)){
        LouKeSetAtomic(&PlaneState->Fence, 0);
    }

    if(LouKeGetAtomic(&PlaneState->Commit.Reference)){
        LouKeSetAtomic(&PlaneState->Commit.Reference, 0);
    }    

    DrsdPropertyDestroyBlob(PlaneState->Base);

    LouPrint("DrsdAtomicDestroyPlaneState() STATUS_SUCCESS\n");
}