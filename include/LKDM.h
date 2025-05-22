#ifndef _LKDM_H
#define _LKDM_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else
#include <LouAPI.h>
#endif 

#define LkdmDeviceObjectToPciDevice(DevObj) (DevObj)->PDEV
#define LkdmAtaHostToPciDevice(AtaHost)     (AtaHost)->PDEV
#define LkdmAtaPortToPciDevice(AtaPort)     (AtaPort)->PDEV
#define LkdmAtaHostToPrivateData(AtaHost)   (AtaHost)->HostPrivateData
#define LkdmAtaPortToPrivateData(AtaPort)   (AtaPort)->PortPrivateData;

#ifdef __cplusplus
}
#endif
#endif //_LKDM_H