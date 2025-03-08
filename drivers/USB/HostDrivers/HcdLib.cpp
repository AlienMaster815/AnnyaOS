#include "usb.h"

PLOUSB_HCD LouKeMallocLousbHcd(size_t SiblingCount, size_t PrivateDataSize, size_t PrivateDataAlignment){
    PLOUSB_HCD Result = (PLOUSB_HCD)LouKeMallocEx(sizeof(LOUSB_HCD), GET_ALIGNMENT(LOUSB_HCD), WRITEABLE_PAGE | PRESENT_PAGE);
    PLOUSB_HCD LouHcd = Result;
    LouHcd->PrivateData = LouKeMallocEx(PrivateDataSize, PrivateDataAlignment, WRITEABLE_PAGE | PRESENT_PAGE);
    SiblingCount--;
    for(; SiblingCount > 0; SiblingCount--){
        LouHcd->Siblings.NextHeader = (PListHeader)LouKeMallocEx(sizeof(LOUSB_HCD), GET_ALIGNMENT(LOUSB_HCD), WRITEABLE_PAGE | PRESENT_PAGE);
        LouHcd = (PLOUSB_HCD)LouHcd->Siblings.NextHeader;
        LouHcd->PrivateData = LouKeMallocEx(PrivateDataSize, PrivateDataAlignment, WRITEABLE_PAGE | PRESENT_PAGE);
    }
    return Result;
}