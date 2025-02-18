#ifndef _PROCESS_H
#define _PROCESS_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C"{
#else 
#include <LouAPI.h>

#endif

#pragma pack(push, 1)

#ifndef _SECTION_HEADER_DEF
#define _SECTION_HEADER_DEF
typedef struct _SECTION_HEADER{
    char name[0x8];
    uint32_t virtualSize;
    uint32_t virtualAddress;
    uint32_t sizeOfRawData;
    uint32_t pointerToRawData;
    uint32_t pointerToRelocations;
    uint32_t pointerToLineNumbers;
    uint16_t numberOfRelocations;
    uint16_t numberOfLineNumbers;
    uint32_t characteristics;
}SECTION_HEADER, * PSECTION_HEADER;
#endif



#ifndef _WINDOW_HANDLE_
#define _WINDOW_HANDLE_
typedef struct  _COLOR_MAP{
    uint8_t r;
    uint8_t g;
    uint8_t b;
}COLOR_MAP, * PCOLOR_MAP;

typedef enum{
    GENERIC_WINDOW = 0,
    TEXT_WINDOW = 1,
    CANVAS_WINDOW = 2,
}WINDOW_TYPE;

typedef struct  _WINDOW_CURSOR{
    uint16_t x;
    uint16_t y;
}WINDOW_CURSOR, * PWINDOW_CURSOR;

//notice: the dementions are only for the internal window 
//not the window itself the window itself is in the window
//handle
typedef struct  _WINDOW_DIMENTIONS{
    uint16_t x;         //Current X Location
    uint16_t y;         //Current Y Location
    uint16_t width;     //Current Width
    uint16_t height;    //Current height
}WINDOW_DIMENTIONS, * PWINDOW_DIMENTIONS;

typedef enum{
    GENRIC_BUTTON = 0,
    PUSH_TEXT_BUTTON = 1,
    MENU_TEXT_BUTTON = 2,
}BUTTON_TYPE;

typedef struct  _BUTTON_CHARECTERISTICS{
    bool IsButton3D;
    bool Inverted3D;
    BUTTON_TYPE Type;
    string ButtonName;
    string ButtonText;
}BUTTON_CHARECTERISTICS, * volatile  PBUTTON_CHARECTERISTICS;

typedef struct  _WINDOW_CHARECTERISTICS{
    WINDOW_TYPE Type;
    WINDOW_DIMENTIONS Dimentions;
    string WindowName;
}WINDOW_CHARECTERISTICS, * PWINDOW_CHARECTERISTICS;

typedef struct  _WINDHANDLE{
    COLOR_MAP ForgroundColor;
    COLOR_MAP BackgroundColor;
    COLOR_MAP BorderFront;
    COLOR_MAP BorderBack;
    COLOR_MAP ForwardHighLite;
    COLOR_MAP AftHighLight;
    WINDOW_CHARECTERISTICS Charecteristics;
    WINDOW_CURSOR Cursor;
    string WindowName;
    uint16_t CurrentX;
    uint16_t CurrentY;
    uint16_t CurrentWidth;
    uint16_t CurrentHeight;
    uintptr_t ParentWindow;
    uintptr_t ChildWindows;
    uint16_t NumberOfChildWindows;
    volatile uint32_t* InnerWindowData;
    COLOR_MAP WindowDataColor;
} WINDHANDLE, * volatile PWINDHANDLE;


typedef struct  _BUTTONHANDLE{
    COLOR_MAP Letters;
    COLOR_MAP ButtonColor;
    //keep in mind the system will flip
    //the data below if the button is 3D
    COLOR_MAP ForwardHighLite;
    COLOR_MAP AftHighLight;
    COLOR_MAP ButtonTextColor;
    uint16_t CurrentX;
    uint16_t CurrentY;
    uint16_t CurrentWidth;
    uint16_t CurrentHeight;
    BUTTON_CHARECTERISTICS Charecteristics;
    uintptr_t ParentWindow;
    uintptr_t ChildWindow;
    uint16_t NumberOfChildWindows; 
    uint32_t* InnerWindowData;
    WINDOW_CURSOR Cursor;
    uintptr_t Shader;
    uint8_t   ShaderFileType;
    uint16_t XScaleing;
    uint16_t YScaleing;
} BUTTONHANDLE, * PBUTTONHANDLE;
#endif

typedef struct _WINDOW_BINARY_LOG{
    ListHeader Neighbors;
    volatile PWINDHANDLE ButtonHandle;
}WINDOW_BINARY_LOG, * PWINDOW_BINARY_LOG;

typedef struct _BUTTON_BINARY_LOG{
    ListHeader Neighbors;
    PBUTTONHANDLE ButtonHandle;
}BUTTON_BINARY_LOG, * PBUTTON_BINARY_LOG;

#define PU_LOW      0
#define PU_MID      1
#define PU_HIGH     2
#define PU_CRITICAL 3
#define PU_PANIC    4
#define PU_FATAL    5

typedef struct _PROCESS_EVENT_LOUQ{
    ListHeader  Neighbors;
    uint64_t    EventUrgency;
    uint32_t    EventType;
    void*       WindowHandle;
    void*       WParam;
    void*       LParam;
}PROCESS_EVENT_LOUQ, * PPROCESS_EVENT_LOUQ;

typedef struct _LOADED_WIN32_BINARY_OBJECT{
    ListHeader              Neighbors;                  //Neighbors in the master object list
    uintptr_t               VirtualLoadedAddress;       //Virtual Address Of the UnPacked Module
    uintptr_t               PhysicalLoadedAddress;      //Physical Address Of The UnPacked Module;
    size_t                  TotalUsedMemory;            //Total Used Memory used by the Unpacked Module;
    string                  BinaryName;                 //Name Of Moudle Parent For the data;
    size_t                  SectionCount;               //Count Of Section Object Members;
    PSECTION_HEADER         SectionObject;              //Packed Array of Structure Data;
    bool                    KernelModule;               //Defines if the module is used in kernel mode/ring 0
    size_t                  NumWindowLogs;
    size_t                  NumButtonLogs;
    WINDOW_BINARY_LOG       WindowLogs;
    BUTTON_BINARY_LOG       ButtonLogs;
    int                     (*WndProc)(void* hwnd, uint32_t uMsg, void* WParam, void* LParam);
}LOADED_WIN32_BINARY_OBJECT, * PLOADED_WIN32_BINARY_OBJECT;

typedef enum{
    Divide0Case = 0,
    DebugCase = 1,
    NmiCase = 2,
    BreakPointCase = 3,
    OverFlowCase = 4,
    BoundRangeCase = 5,
    InvalidOpcodeCase = 6,
    FloatDeviceNotAvailableCase = 7,
    DoubleFaultCase = 8,
    CpOverunCase = 9,
    SegmentNotPresentCase = 10,
    StackSegmentFaultCase = 11,
    GeneralProtectionFaultCase = 12,
    PageFaultCase = 13,
    x87FPECase = 14,
    AlignmentCheckCase = 15,
    MachineCheckCase = 16,
    SIMDCheckCase = 17,
    VmExceptionCase = 18,
    ControlProtectionCase = 19,
    CookieCheckFailCase = 20,
}EXCEPTION_CASE;

typedef union _PROCESS_EXCEPTION_DATA_PACKET{
    struct{
        struct _CPUContext* FaultContext;
        EXCEPTION_CASE ExceptionCase;
    }OutData;
    struct{
        PLOADED_WIN32_BINARY_OBJECT ProcessOfFault;
    }InData;
}PROCESS_EXCEPTION_DATA_PACKET, * PPROCESS_EXCEPTION_DATA_PACKET;

#pragma pack(pop)

#ifndef _KERNEL_MODULE_

#define LouKeLogBinaryTotalSize(x,y) (x->TotalUsedMemory = y)
#define LouKeLogBinaryPhysicalAddress(x,y) (x->PhysicalLoadedAddress = y)
#define LouKeLogBinaryVirtualAddress(x,y) (x->VirtualLoadedAddress = y)
#define LouKeLogKernelBinary(x,y) (x->KernelModule = y)

LOUSTATUS LouKeMallocBinarySectionLogs(
    PLOADED_WIN32_BINARY_OBJECT BinaryObject,
    size_t NumberOfLogs
);

LOUSTATUS LouKeLogBinarySection(
    PLOADED_WIN32_BINARY_OBJECT BinaryObject,
    size_t SectionNumber,
    PSECTION_HEADER Header
);

LOUSTATUS 
LouKeDestroyBinaryObject(
    PLOADED_WIN32_BINARY_OBJECT BinaryObjectHandle
);

PLOADED_WIN32_BINARY_OBJECT 
LouKeCreateBinaryObjectLog(
    string BinaryName
);

LOUSTATUS LouKeGetFaultBnaryHande(
    PPROCESS_EXCEPTION_DATA_PACKET DataPacket
);

#endif

#ifdef __cplusplus
}
#endif
#endif