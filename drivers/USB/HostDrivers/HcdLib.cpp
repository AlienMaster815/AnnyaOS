#include "usb.h"

PLOUSB_HCD LouKeMallocLousbHcd(size_t SiblingCount, size_t PrivateDataSize, size_t PrivateDataAlignment){
    PLOUSB_HCD Result = (PLOUSB_HCD)LouMallocEx(sizeof(LOUSB_HCD), GET_ALIGNMENT(LOUSB_HCD));
    PLOUSB_HCD LouHcd = Result;
    LouHcd->PrivateData = LouMallocEx(PrivateDataSize, PrivateDataAlignment);
    SiblingCount--;
    for(; SiblingCount > 0; SiblingCount--){
        LouHcd->Siblings.NextHeader = (PListHeader)LouMallocEx(sizeof(LOUSB_HCD), GET_ALIGNMENT(LOUSB_HCD));
        LouHcd = (PLOUSB_HCD)LouHcd->Siblings.NextHeader;
        LouHcd->PrivateData = LouMallocEx(PrivateDataSize, PrivateDataAlignment);
    }
    return Result;
}