/*#include <LouAPI.h>

struct _IPROC_OBJECT;

typedef LOUSTATUS (*IPROC_PROCEDURE)(struct _IPROC_OBJECT*);

typedef struct _IPROC_OBJECT{
    PVOID           InData;
    PVOID           OutData;
    LOUSTATUS       Status;
    IPROC_PROCEDURE Procedure;
}IPROC_OBJECT, * PIPROC_OBJECT;

typedef struct _IPROC_LIST{
    ListHeader      Peers;
    PIPROC_OBJECT   IprocObject;
}IPROC_LIST, * PIPROC_LIST;

UNUSED static mutex_t*     IccListsLocks;
UNUSED static PListHeader  IccLists;

LOUSTATUS LouKeInitializeIccSubsystem(){


}

LOUSTATUS LouKeIccSendIcc(
    PIPROC_OBJECT Object,
){

}
*/