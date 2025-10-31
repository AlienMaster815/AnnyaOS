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

#define CFI_OPTIONAL_HEADER_LOUCOFF_MAGIC               0x0815
#define CFI_SUBSYSTEM_ANNYA_NATIVE                      17
#define CFI_SUBSUSTEM_LOUSINE_KULA                      18
#define CFI_DLLCHARACTERISTICS_LOUSINE_KERNEL_DRIVER    CFI_DLLCHARACTERISTICS_WDM_DRIVER
#define CFI_DDOFFSET_KULA_TABLE                         CFI_DDOFFSET_UNUSED_TABLE
#define CFI_DDOFFSET_FORWARDER_TABLE                    CFI_DDOFFSET_ARCHITECTURE_TABLE

//the following are reserved if necisary
//      CFI_DLLCHARACTERISTICS_RESERVED                 (0x0001) 
//      CFI_DLLCHARACTERISTICS_RESERVED                 (0x0002) 
//      CFI_DLLCHARACTERISTICS_RESERVED                 (0x0004) 
//      CFI_DLLCHARACTERISTICS_RESERVED                 (0x0008)
//      CFI_DLLCHARACTERISTICS_RESERVED                 (0x0010)

#endif