#ifndef _LOUCOFF_H
#define _LOUCOFF_H

#include <Annya.h>

typedef string* KULA_RVA_NAMES;
typedef string  KULA_RVA_NAME;
typedef PVOID*  KULA_RVA_ADDRESSES;
typedef PVOID   KULA_RVA_ADDRESS;

typedef struct _KULA_TBALE_ENTRIES{
    string              BinaryName; //Binary to emulate
    SIZE                Members;    //RVA Function Count
    KULA_RVA_NAMES      Names;      //RVA Function Names
    KULA_RVA_ADDRESSES  Rvas;       //RVA Function Address    
}KULA_TBALE_ENTRIES, * PKULA_TBALE_ENTRIES;

typedef struct _KULA_TABLE{
    CHAR                    KulaSignature[5];   //K U L A ;
    SIZE                    TableMembers;       //Entries Count For KULA Linker
    PKULA_TBALE_ENTRIES     Entries;            //Entries For KULA Linker
}KULA_TABLE, * PKULA_TABLE; 

typedef struct _KULA_TABLE_TRACKER{
    ListHeader              Peers;
    string                  HostBinary;
    PKULA_TABLE             Table;
}KULA_TABLE_TRACKER, * PKULA_TABLE_TRACKER;

#define DECLARE_KULA_TABLE __declspec(dllexport) const KULA_TABLE KulaTable 

#endif