#ifndef _BUSSES_H
#define _BUSSES_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _LOU_BUS_OBJECT{
    ListHeader          Peers;
    string              BusName;
    PVOID               BusPrivateData;
}LOU_BUS_OBJECT, * PLOU_BUS_OBJECT;

typedef struct _LOU_BUS{
    string              BusName;
    PLOU_BUS_OBJECT     BusObjects;
    spinlock_t          BusScanLock;
    LOUSTATUS           (*SearchMachine)(struct _LOU_BUS* BusData);
    LOUSTATUS           (*InitializeBus)(struct _LOU_BUS* BusData, PLOU_BUS_OBJECT BusObject);
    LOUSTATUS           (*DeInitializeBus)(struct _LOU_BUS* BusData, PLOU_BUS_OBJECT BusObject);
}LOU_BUS, * PLOU_BUS;

#ifndef _USER_MODE_CODE_
KERNEL_EXPORT
LOUSTATUS 
LouKeCreateBusClass(
    PLOU_BUS    Bus
);
#endif
#ifdef __cplusplus
}
#endif
#endif