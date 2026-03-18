#ifndef _HDMI_CEC_H
#define _HDMI_CEC_H

#define CEC_MAX_MESSAGE_SIZE 16

typedef struct _CEC_MESSAGE{
    UINT32  TxTs;
    UINT32  RxTs;
    UINT32  Length;
    UINT32  Timeout;
    UINT32  Sequence;
    UINT32  Flags;
    UINT8   Message[CEC_MAX_MESSAGE_SIZE];
    UINT8   Reply;
    UINT8   RxStatus;
    UINT8   TxStatus;
    UINT8   TxArbLostCnt;
    UINT    TxNackCount;
    UINT    TxLowDriveCount;
    UINT8   ErrorCount;
}CEC_MESSAGE, * PCEC_MESSAGE;

#endif