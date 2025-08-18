#include <LouACPI.h>
#include <acpi.h>

UNUSED static bool DmiAvailable = false;

UNUSED static string DmiIndetification[DMI_STRING_MAX] = {0};

static inline string DmiGetSystemInformation(DMI_FIELD Field){
    return DmiIndetification[Field];
}

void RegisterDmiDevice(DMI_FIELD Field, string String){
    DmiIndetification[Field] = String;
}

BOOL DmiGetDate(DMI_FIELD Field, INTEGER* Year, INTEGER* Month, INTEGER* Day){
    INTEGER TYear = 0, TMonth = 0 , TDay = 0;    
    string s = DmiGetSystemInformation(Field);
    if(!s){
        return false;
    }

    // parse MM/DD/YYYY
    char* p = s;
    char* end;

    TMonth = strtoul(p, &end, 10);
    if (p == end || *end != '/' || TMonth == 0 || TMonth > 12)
        goto _OUT;

    p = end + 1;
    TDay = strtoul(p, &end, 10);
    if (p == end || *end != '/' || TDay == 0 || TDay > 31)
        goto _OUT;

    p = end + 1;
    TYear = strtoul(p, &end, 10);
    if (p == end || TYear > 9999)
        goto _OUT;

    // adjust 2-digit years
    if (TYear < 100) {
        TYear += 1900;
        if (TYear < 1996)
            TYear += 100;
    }

_OUT:
    if (Year)  *Year  = TYear;
    if (Month) *Month = TMonth;
    if (Day)   *Day   = TDay;

    return true;
}


INTEGER DmiGetBiosYear(){
    BOOL DataExists = false;
    INTEGER Year = 0;

    DataExists = DmiGetDate(DMI_BIOS_DATE, &Year, 0x00, 0x00);
    if(!DataExists){
        return 0;
    }
    return Year;
}

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