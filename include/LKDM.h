#ifndef _LKDM_H
#define _LKDM_H

#ifdef __cplusplus
extern "C" {
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