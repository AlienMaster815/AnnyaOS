#include <LouACPI.h>
#include <acpi.h>

UNUSED static bool DmiAvailable = false;

UNUSED static string DmiIndetification[DMI_STRING_MAX] = {0};

static void DmiScanMachine(){
    UNUSED UINT8* SmBiosTables = GetSmBiosAddress();
    if(!SmBiosTables){
        return;
    }
    DmiAvailable = true;



}

static bool DmiMatch(PDMI_SYSTEM_ID SystemID){

    UNUSED INTEGER s = 0x00;

    for(SIZE i = 0 ; SystemID->Matches[i].ValidEntry; i++){
        s = SystemID->Matches[i].Slot;
        if(s == DMI_NONE){
            break;
        }
        if(s == DMI_OEM_STRING){
            LouPrint("DmiMatch()\n");
            while(1);
        }else if((s < DMI_STRING_MAX) && (DmiIndetification[s])){
            if(SystemID->Matches[i].ExactMatch){
                if(!strcmp(DmiIndetification[s], SystemID->Matches[i].SubString)){
                    continue;
                }
            }else{
                if(strstr(DmiIndetification[s], SystemID->Matches[i].SubString)){
                    continue;
                }
            }
        }
        return false;
    }
    return true;
}



INTEGER CheckDmiSystem(PDMI_SYSTEM_ID IdList){
    
    INTEGER Count = 0;

    for(SIZE i = 0 ; IdList[i].ValidEntry ; i++){
        if(DmiMatch(&IdList[i])){
            Count++;
            if(IdList[i].Callback){
                if(IdList[i].Callback(&IdList[i])){
                    break;
                }
            }
        }
    }

    return Count;
}


void InitializeDmiSystem(){

    DmiScanMachine();

}