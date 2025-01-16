#ifndef _SCSI_COMMAND_H
#define _SCSI_COMMAND_H
#ifdef __cplusplus
    #include <LouDDK.h>
    extern "C"{
#else
#include <LouAPI.h>
#endif

#include "../ScatterList.h"
#include "ScsiDevice.h"

struct _LOUSINE_SCSI_HOST;
struct _LOUSINE_SCSI_DEVICE;

#define MAXIMUM_COMMAND_SIZE            16

typedef struct _SCSI_DATA_BUFFER{
    SCATTER_GATHER_TABLE    ScatterGatherTable;
    uint64_t                TableLength;
}SCSI_DATA_BUFFER, * PSCSI_DATA_BUFFER;

typedef struct _SCSI_POINTER{
    //PLOUSINE_SCSI_DEVICE  ScsiDevice;
    string              Pointer;
    int                 ThisResidual;    
    PSCATTER_LIST       Buffer;
    int                 BufferResidual;
    uint64_t            DmaHandle;
    int32_t             Status;
    int32_t             Message;
    int32_t             DataIn;
    int32_t             SentCommand;
    int32_t             Phase;
}SCSI_POINTER, * PSCSI_POINTER;

#define SCSI_COMMAND_TAGGED                 (1 << 8)
#define SCSI_COMMAND_INITIALIZED            (1 << 1)
#define SCSI_COMMAND_LAST                   (1 << 2)
#define SCSI_COMMAND_FORCE_UH_SUCCESS       (1 << 3)
#define SCSI_COMMAND_FAIL_IF_RECOVERING     (1 << 4)
#define SCSI_COMMAND_PRESERVED_FLAGS        (SCSI_COMMAND_INITIALIZED | SCSI_COMMAND_FAIL_IF_RECOVERING)
#define SCSI_COMMAND_STATE_COMPLETE         0
#define SCSI_COMMAND_STATE_IN_FLIGHT        2
#define SCSI_COMMAND_SUBMITTER_IO_STACK     0
#define SCSI_COMMAND_ERROR_HANDLER          1
#define SCSI_COMMAND_RESET_REQUEST          2

typedef struct _SCSI_COMMAND{
    struct _LOUSINE_SCSI_DEVICE*        ScsiDevice;
    ListHeader                          IoStackObject;
    DELAYED_FUNCTION                    AbortWork;
    struct _READ_COPY_UPDATE_HEADER     ReadCopyUpdateHeader;
    int32_t                             IoStackErrorFlags; //Atomic Value
    LOU_TOKEN                           Budget;
    TIME_T                              TimeOfAllocation;
    COUNTER                             Retries;
    int                                 ALLOWED;
    uint8_t                             PorotocolOperation;
    uint8_t                             ProtocolType;
    uint8_t                             ProtocolFlags;
    uint8_t                             ScsiCommandSubmitter;
    uint16_t                            CommadnLength;
    bool                                IoToDevice;
    uint8_t                             ScsiCommandDataBuffer[32];
    SCSI_DATA_BUFFER                    ScsiDataBuffer;
    PSCSI_DATA_BUFFER                   ProtocolScsiDataBuffer;
    uint64_t                            UnderflowCount;
    uint64_t                            TransferSize;
    uint64_t                            ResidualLength;
    uint64_t                            SenceLength;
    uint8_t*                            SenceBuffer;
    int                                 Flags;
    uint32_t                            State;
    uint32_t                            ExtraLength;
    uint8_t*                            HostScribbleData;
    int                                 DriverStatus;
}SCSI_COMMAND, *  PSCSI_COMMAND;

static inline void* ScsiCommandGetProprietaryData(PSCSI_COMMAND ScsiCommand){
    return &ScsiCommand[1];
}

//TODO{
void ScsiDone(PSCSI_COMMAND ScsiCommand);
void ScsiDoneDirect(PSCSI_COMMAND ScsiCommand);
void ScsiFinishCommand(PSCSI_COMMAND ScsiCommand);
void* LouKeScsiMapAtomicScatterGather(PSCATTER_LIST ScatterGather, int ScatterGatherCount, uint64_t* Offset, uint64_t* Length);
void  LouKeScsiUnMapAtomicScatterGather(void* VirtualHandle);
LOUSTATUS ScsiAllocateScatterGatherTables(PSCSI_COMMAND ScsiCommand);
LOUSTATUS LouKeMapScsiDma(PSCSI_COMMAND* ScsiCommand);
void LouKeUnMapScsiDma(PSCSI_COMMAND ScsiCommand);

//}

static inline uint64_t GetScsiScatterGatherCount(PSCSI_COMMAND ScsiCommand){
    return(uint64_t)ScsiCommand->ScsiDataBuffer.ScatterGatherTable.EntryCount;
}

static inline PSCATTER_LIST GetScsiScatterGatherList(PSCSI_COMMAND ScsiCommand){
    return ScsiCommand->ScsiDataBuffer.ScatterGatherTable.ScatterGatherList;
}

static inline uint64_t GetScsiBufferLength(PSCSI_COMMAND ScsiCommand){
    return (uint64_t)ScsiCommand->ScsiDataBuffer.TableLength;
}

static inline void SetScsiResidualLength(PSCSI_COMMAND ScsiCommand, uint64_t ResidualLength){
    ScsiCommand->ResidualLength = ResidualLength;
}

static inline uint64_t GetScsiResidualLength(PSCSI_COMMAND ScsiCommand){
    return ScsiCommand->ResidualLength;
}

#define ForEachScsiScatterGatherList(Command, ScatterGatherList, SegmentCount, i)   ForEachScatterGatherList(GetScsiScatterGatherList(Command), ScatterGatherList,SegmentCount, i)

static inline int ScsiScatterGatherCopyFromBuffer(PSCSI_COMMAND ScsiCommand, void* Buffer, int BufferLength){
    return ScatterGatherCopyFromBuffer(
            GetScsiScatterGatherList(ScsiCommand),
            GetScsiScatterGatherCount(ScsiCommand),
            Buffer,
            BufferLength
        );
}

static inline int ScsiScatterGatherCopyToBuffer(PSCSI_COMMAND ScsiCommand, void* Buffer, int BufferLength){
    return ScatterGatherCopyToBuffer(
        GetScsiScatterGatherList(ScsiCommand),
        GetScsiScatterGatherCount(ScsiCommand),
        Buffer,
        BufferLength
    );
}

static inline uint64_t GetScsiSector(PSCSI_COMMAND ScsiCommand){
    return 0x00;
}

static inline uint64_t GetScsiLba(PSCSI_COMMAND ScsiCommand){
    return 0x00;
}

static inline uint64_t GetScsiLogicalBlockCount(){
    return 0x00;
}

#define SCSI_PROTOCOL_FLAGS_TRANSFER_PI             1 << 0
#define SCSI_PROTOCOL_FLAGS_GUARD_CHECK             1 << 1
#define SCSI_PROTOCOL_FLAGS_REFERENCE_CHECK         1 << 2
#define SCSI_PROTOCOL_FLAGS_REFERENCE_INCREMENT     1 << 3
#define SCSI_PROTOCOL_FLAGS_IP_CHECKSUM             1 << 4

#define SCSI_PROTOCOL_TYPE_DIF_TYPE0                0
#define SCSI_PROTOCOL_TYPE_DIF_TYPE1                1
#define SCSI_PROTOCOL_TYPE_DIF_TYPE2                2
#define SCSI_PROTOCOL_TYPE_DIF_TYPE3                3

static inline void SetScsiProtocolType(PSCSI_COMMAND ScsiCommand, uint8_t Type){
    ScsiCommand->ProtocolType = Type;
}

static inline uint8_t GetScsiProtocolType(PSCSI_COMMAND ScsiCommand){
    return ScsiCommand->ProtocolType;
}

static inline uint32_t GetScsiProtocolReferenceTag(PSCSI_COMMAND ScsiCommand){
    return 0x00;
}

static inline uint32_t GetScsiProtocolInterval(PSCSI_COMMAND ScsiCommand){
    return ScsiCommand->ScsiDevice->SectorSize;
}

static inline uint32_t GetScsiProtocolScatterGatherCount(PSCSI_COMMAND ScsiCommand){
    return ScsiCommand->ProtocolScsiDataBuffer ? ScsiCommand->ProtocolScsiDataBuffer->ScatterGatherTable.EntryCount : 0;
}

static inline PSCATTER_LIST GetScsiProtocolScatterGatherList(PSCSI_COMMAND ScsiCommand){
    return ScsiCommand->ProtocolScsiDataBuffer ? ScsiCommand->ProtocolScsiDataBuffer->ScatterGatherTable.ScatterGatherList : 0x00;
}

static inline PSCSI_DATA_BUFFER GetScsiProtocol(PSCSI_COMMAND ScsiCommand){
    return ScsiCommand->ProtocolScsiDataBuffer;
}

#define ForEachScsiProtocolScatterGather(ScsiCommand, ScatterGather, SementCount, i) ForEachScatterGatherList(GetScsiProtocolScatterGatherList(ScsiCommand), ScatterGather, SementCount, i)

static inline void ScsiSetStatusByte(PSCSI_COMMAND ScsiCommand, int8_t  Status){
    ScsiCommand->DriverStatus = (ScsiCommand->DriverStatus & 0xFFFFFF00) | Status;
}

static inline uint8_t ScsiGetStatusByte(PSCSI_COMMAND ScsiCommand){
    return ScsiCommand->DriverStatus & 0xFF;
}

static inline void ScsiSetHostByte(PSCSI_COMMAND ScsiCommand, int8_t Status){
    ScsiCommand->DriverStatus = (ScsiCommand->DriverStatus & 0xFF00FFFF) | (Status << 16);
}

static inline uint8_t ScsiGetHostByte(PSCSI_COMMAND ScsiCommand){
    return (ScsiCommand->DriverStatus >> 16) & 0xFF;
}

static inline void ScsiDispatchMessageToHost(PSCSI_COMMAND ScsiCommand, uint8_t ScsiMessage){
    switch(ScsiMessage){
        case SCSI_COMMAND_STATE_COMPLETE:{
            return;
        }
        //case ABORT_TASK:{
            //ScsiSetHostByte(ScsiCommand, DID_ABORT);
            //return;
        //}
        //case TARGET_RESET:{
            //ScsiSetHostByte(ScsiCommand, DID_RESET);
            //return;
        //}
        default:{
            //ScsiSetHostByte(ScsiCommand, DID_ERROR);
            return;
        }
    }
}

static inline uint64_t GetScsiTransferLength(PSCSI_COMMAND ScsiCommand){
    uint32_t TransferLength = ScsiCommand->ScsiDataBuffer.TableLength;
    uint32_t ProtocolInterval = GetScsiProtocolInterval(ScsiCommand);

    if(ScsiCommand->ProtocolFlags & SCSI_PROTOCOL_FLAGS_TRANSFER_PI){
        TransferLength += (TransferLength >> ILog2(ProtocolInterval)) * 8;
    }

    return TransferLength;
}

//More TODO {
void ScsiBuildSenceData(PSCSI_COMMAND ScsiCommand, int32_t Descriptor, uint8_t Key, uint8_t Ascync, uint8_t AsyncrQ);
//void* ScsiAllocateReques();

//}

#ifdef __cplusplus
}
#endif
#endif //_SCSI_COMMAND_H
