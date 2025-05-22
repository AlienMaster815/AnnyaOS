#ifndef _FIBRE_CHANNEL_OE_SYSTEM_H
#define _FIBRE_CHANNEL_OE_SYSTEM_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else 
#include <LouAPI.h>
#endif

#define FIP_CONNECTION_TYPE_UNKOWN  0
#define FIP_CONNECTION_TYPE_FABRIC  1
#define FIP_CONNECTION_TYPE_VN2VN   2

#define FIBRE_CHANNEL_OE_CONTROLER_ENEABLED_STATE_ENABLED       0
#define FIBRE_CHANNEL_OE_CONTROLER_ENEABLED_STATE_DISABLED      1
#define FIBRE_CHANNEL_OE_CONTROLER_ENEABLED_STATE_UNUSED        2



typedef struct _FIBRE_CHANNEL_COTROLER_DEVICE{
    uint32_t                                        Identification;
    struct _FIBRE_CHANNEL_OE_FUNCTION_TEMPLATE*     SystemOperations;
    ListHeader                                      FcSystem;
    PLOUQ_WORK                                      WorkQs;
    PLOUQ_WORK                                      DeviceLossWork;
    mutex_t                                         Lock;
    int                                             FibreChannelDeviceLossTimeout;
    uint8_t                                         FipConnectionType;
    uint8_t                                         ControlerEnableState;
    FIBRE_CHANNEL_OE_ELS_LESB                       Lesb;                
}FIBRE_CHANNEL_COTROLER_DEVICE, * PFIBRE_CHANNEL_COTROLER_DEVICE;

#define FIBRE_CHANNEL_OE_FCF_STATE_UNKOWN           0
#define FIBRE_CHANNEL_OE_FCF_STATE_DISCONNECTED     1
#define FIBRE_CHANNEL_OE_FCF_STATE_CONNECTED        2
#define FIBRE_CHANNEL_OE_FCF_STATE_DELETED          3

typedef struct _FIBRE_CHANNEL_OE_FCF_DEVICE{
    uint32_t            Identification;
    ListHeader          Neighbors;
    void*               DeleteWorkData;
    DELAYED_FUNCTION    DeviceLossWork;
    uint32_t            DeviceLossTimeout;
    void*               PrivateData;
    uint32_t            FcfState;
    uint64_t            FabricNames;
    uint64_t            SwitchNames;
    uint32_t            FcMap;
    uint16_t            VFId;
    uint8_t             Mac[ETH_ALEN];
    uint8_t             Priority;
    uint32_t            FkaPeriod;
    uint16_t            VLanID;
}FIBRE_CHANNEL_OE_FCF_DEVICE, * PFIBRE_CHANNEL_OE_FCF_DEVICE;

typedef struct _FIBRE_CHANNEL_OE_FUNCTION_TEMPLATE{
    void (*GetFcOeControllerLinkFail)(PFIBRE_CHANNEL_COTROLER_DEVICE);
    void (*GetFcOeControllerVlinkFail)(PFIBRE_CHANNEL_COTROLER_DEVICE);
    void (*GetFcOeControllerMissFka)(PFIBRE_CHANNEL_COTROLER_DEVICE);
    void (*GetFcOeControllerLinkSymbolError)(PFIBRE_CHANNEL_COTROLER_DEVICE);
    void (*GetFcOeControllerErrorBlock)(PFIBRE_CHANNEL_COTROLER_DEVICE);
    void (*GetFcOeControllerFcsError)(PFIBRE_CHANNEL_COTROLER_DEVICE);
    void (*SetFcOeControllerMode)(PFIBRE_CHANNEL_COTROLER_DEVICE);
    void (*SetFcOeControllerEnabled)(PFIBRE_CHANNEL_COTROLER_DEVICE);
    int (*GetFcOeControllerFcfSelected)(PFIBRE_CHANNEL_COTROLER_DEVICE);
    void (*GetFcOeControllerFcfVlanID)(PFIBRE_CHANNEL_COTROLER_DEVICE);
}FIBRE_CHANNEL_OE_FUNCTION_TEMPLATE, * PFIBRE_CHANNEL_OE_FUNCTION_TEMPLATE;

#ifdef __cplusplus
}
#endif
#endif 