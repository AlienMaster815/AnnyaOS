//Copyright GPL-2 Tyler Grenier (2026)
#ifndef _AMD_VI_H
#define _AMD_VI_H

#include "VmCore.h"

#define AMD_VIRTUALIZATION_ACPI_TABLE   "IVRS"

typedef struct _AMD_VI_GUEST_VIRTUAL_APIC_LOG{

}AMD_VI_GUEST_VIRTUAL_APIC_LOG, * PAMD_VI_GUEST_VIRTUAL_APIC_LOG;

typedef struct _AMD_VI_GUEST_VIRTUAL_APIC_TABLE{

}AMD_VI_GUEST_VIRTUAL_APIC_TABLE, * PAMD_VI_GUEST_VIRTUAL_APIC_TABLE;

typedef struct _AMD_VI_PERIPHERAL_PAGE_REQUEST_LOG{

}AMD_VI_PERIPHERAL_PAGE_REQUEST_LOG, * PAMD_VI_PERIPHERAL_PAGE_REQUEST_LOG;

typedef struct _AMD_VI_INTERRUPT_REMAP_TABLE{

}AMD_VI_INTERRUPT_REMAP_TABLE, * PAMD_VI_INTERRUPT_REMAP_TABLE;

typedef struct _AMD_VI_EVENT_LOG{

}AMD_VI_EVENT_LOG, * PAMD_VI_EVENT_LOG;

typedef struct _AMD_VI_COMMAND_BUFFER{

}AMD_VI_COMMAND_BUFFER, * PAMD_VI_COMMAND_BUFFER;

typedef struct _AMD_VI_IO_PAGE_TABLE{

}AMD_VI_IO_PAGE_TABLE, * PAMD_VI_IO_PAGE_TABLE;

typedef union PACKED _AMD_VI_DEVICE_ID{
    struct {
        UINT16      Function    :   3;
        UINT16      Device      :   5;
        UINT16      Bus         :   8;             
    }RequesterID;
    struct{
        UINT16      RsvZero     :   3;
        UINT16      UnitID      :   5;
        UINT16      Bus         :   8;             
    }UnitID;
    UINT16          AsUINT16;
}AMD_VI_DEVICE_ID, * PAMD_VI_DEVICE_ID;

typedef struct PACKED _AMD_VI_DEVICE_TABLE{

}AMD_VI_DEVICE_TABLE, * PAMD_VI_DEVICE_TABLE;

typedef enum _AMD_VI_TRANSLATION_TABLE_LEVELS{
    TRANSLATION_TABLE_LEVEL_COUNT_UNSPECIFIED = 0,
    TRANSLATION_TABLE_HAS_ONE_LEVEL,
    TRANSLATION_TABLE_HAS_TWO_LEVELS,
}AMD_VI_TRANSLATION_TABLE_LEVELS, * PAMD_VI_TRANSLATION_TABLE_LEVELS;

//Generic IOMMU Read And Write
#define AMD_VI_IOMMU_READ_ULONGLONG(Reg, Mask, Shift)     ((READ_REGISTER_ULONGLONG(Reg, Shift, Mask) >> Shift) & Mask)
#define AMD_VI_IOMMU_WRITE_ULONGLONG(Reg, Mask, Shift, Val) WRITE_REGISTER_ULONGLONG(Reg, ((Val & Mask) << Shift))
//end
//Device Table Base Address Register
#define AMD_VI_READ_DTBAR(Register)                         AMD_VI_IOMMU_READ_ULONGLONG(Register, ULONGLONG_MAX, 0)
#define AMD_VI_WRITE_DTBAR(Register, Val)                   AMD_VI_IOMMU_WRITE_ULONGLONG(Register, ULONGLONG_MAX, 0)
#define AMD_VI_DTBAR_SIZE_MASK                              0xFF
#define AMD_VI_DTBAR_SIZE_SHIFT                             0
#define AMD_VI_READ_DTBAR_SIZE(Register)                    AMD_VI_IOMMU_READ_ULONGLONG(Register, AMD_VI_DTBAR_SIZE_MASK, AMD_VI_DTBAR_SIZE_SHIFT)
#define AMD_VI_WRITE_DTBAR_SIZE(Register, Val)              AMD_VI_IOMMU_WRITE_ULONGLONG(Register, AMD_VI_DTBAR_SIZE_MASK, AMD_VI_DTBAR_SIZE_SHIFT, Val)

#define AMD_VI_DTBAR_DEVTABBASE_MASK                        0xFFFFFFFFFF
#define AMD_VI_DTBAR_DEVTABBASE_SHIFT                       12
#define AMD_VI_READ_DTBAR_DEVTABBASE(Register)              AMD_VI_IOMMU_READ_ULONGLONG(Register, AMD_VI_DTBAR_DEVTABBASE_MASK, AMD_VI_DTBAR_DEVTABBASE_SHIFT)
#define AMD_VI_WRITE_DTBAR_DEVTABBASE(Register, Val)        AMD_VI_IOMMU_WRITE_ULONGLONG(Register, AMD_VI_DTBAR_DEVTABBASE_MASK, AMD_VI_DTBAR_DEVTABBASE_SHIFT, Val)
//end
//Command Buffer Base Address Register
#define AMD_VI_READ_CBBAR(Register)                         AMD_VI_IOMMU_READ_ULONGLONG(Register, ULONGLONG_MAX, 0)
#define AMD_VI_WRITE_CBBAR(Register, Val)                   AMD_VI_IOMMU_WRITE_ULONGLONG(Register, ULONGLONG_MAX, 0)

#define AMD_VI_CBBAR_COMBASE_MASK                           0xFFFFFFFFFF
#define AMD_VI_CBBAR_COMBASE_SHIFT                          12
#define AMD_VI_READ_CBBAR_COMBASE(Register)                 AMD_VI_IOMMU_READ_ULONGLONG(Register, AMD_VI_CBBAR_COMBASE_MASK, AMD_VI_CBBAR_COMBASE_SHIFT)
#define AMD_VI_WRITE_CBBAR_COMBASE(Register, Val)           AMD_VI_IOMMU_WRITE_ULONGLONG(Register, AMD_VI_CBBAR_COMBASE_MASK, AMD_VI_CBBAR_COMBASE_SHIFT, Val)

#define AMD_VI_CBBAR_COMLEN_MASK                            0x0F
#define AMD_VI_CBBAR_COMLEN_SHIFT                           56
#define AMD_VI_CBBAR_COMLEN_GET_ENTRY_COUNT(Value)          ((Value & (1 << 3)) ? Value & 0x07 : 0)                 
#define AMD_VI_READ_CBBAR_COMLEN(Register)                  AMD_VI_IOMMU_READ_ULONGLONG(Register, AMD_VI_CBBAR_COMLEN_MASK, AMD_VI_CBBAR_COMLEN_SHIFT)
#define AMD_VI_WRITE_CBBAR_COMLEN(Register, Val)            AMD_VI_IOMMU_WRITE_ULONGLONG(Register, AMD_VI_CBBAR_COMLEN_MASK, AMD_VI_CBBAR_COMLEN_SHIFT, Val)
//end
//Event Log Base Address Reguster
#define AMD_VI_READ_ELBAR(Register)                         AMD_VI_IOMMU_READ_ULONGLONG(Register, ULONGLONG_MAX, 0)
#define AMD_VI_WRITE_ELBAR(Register, Val)                   AMD_VI_IOMMU_WRITE_ULONGLONG(Register, ULONGLONG_MAX, 0, Val)

#define AMD_VI_ELBAR_EVENT_BASE_MASK                        0xFFFFFFFFFF
#define AMD_VI_ELBAR_EVENT_BASE_SHIFT                       12
#define AMD_VI_READ_ELBAR_EVENT_BASE(Register)              AMD_VI_IOMMU_READ_ULONGLONG(Register, AMD_VI_ELBAR_EVENT_BASE_MASK, AMD_VI_ELBAR_EVENT_BASE_SHIFT)
#define AMD_VI_WRITE_ELBAR_EVENT_BASE(Register, Val)        AMD_VI_IOMMU_WRITE_ULONGLONG(Register, AMD_VI_ELBAR_EVENT_BASE_MASK, AMD_VI_ELBAR_EVENT_BASE_SHIFT, Val)  

#define AMD_VI_ELBAR_EVENTLEN_MASK                          0x0F
#define AMD_VI_ELBAR_EVENTLEN_SHIFT                         56
#define AMD_VI_ELBAR_EVENTLEN_GET_ENTRY_COUNT(Value)        ((Value & (1 << 3)) ? Value & 0x07 : 0)                 
#define AMD_VI_READ_ELBAR_EVENTLEN(Register)                AMD_VI_IOMMU_READ_ULONGLONG(Register, AMD_VI_ELBAR_EVENTLEN_MASK, AMD_VI_ELBAR_EVENTLEN_SHIFT)
#define AMD_VI_WRITE_ELBAR_EVENTLEN(Register, Val)          AMD_VI_IOMMU_WRITE_ULONGLONG(Register, AMD_VI_ELBAR_EVENTLEN_MASK, AMD_VI_ELBAR_EVENTLEN_SHIFT, Val)
//end
//Iommu Control Register
#define AMD_VI_READ_ICR(Register)                           AMD_VI_IOMMU_READ_ULONGLONG(Register, ULONGLONG_MAX, 0)
#define AMD_VI_WRITE_ICR(Register, Val)                     AMD_VI_IOMMU_WRITE_ULONGLONG(Register, ULONGLONG_MAX, 0, Val)

#define AMD_VI_ICR_IOMMUEN_MASK                             0x01
#define AMD_VI_ICR_IOMMUEN_SHIFT                            0x00
#define AMD_VI_READ_ICR_IOMMUEN(Register)                   AMD_VI_IOMMU_READ_ULONGLONG(Register, AMD_VI_ICR_IOMMUEN_MASK, AMD_VI_ICR_IOMMUEN_SHIFT)
#define AMD_VI_WRITE_ICR_IOMMUEN(Register, Val)             AMD_VI_IOMMU_WRITE_ULONGLONG(Register, AMD_VI_ICR_IOMMUEN_MASK, AMD_VI_ICR_IOMMUEN_SHIFT, Val)

#define AMD_VI_ICR_HTTUNEN_MASK                             0x01
#define AMD_VI_ICR_HTTUNEN_SHIFT                            1
#define AMD_VI_READ_ICR_HTTUNEN(Register)                   AMD_VI_IOMMU_READ_ULONGLONG(Register, AMD_VI_ICR_HTTUNEN_MASK, AMD_VI_ICR_HTTUNEN_SHIFT)
#define AMD_VI_WRITE_ICR_HTTUNEN(Register, Val)             AMD_VI_IOMMU_WRITE_ULONGLONG(Register, AMD_VI_ICR_HTTUNEN_MASK, AMD_VI_ICR_HTTUNEN_SHIFT, Val)

#define AMD_VI_ICR_EVENTLOGEN_MASK                          0x01
#define AMD_VI_ICR_EVENTLOGEN_SHIFT                         2
#define AMD_VI_READ_ICR_EVENTLOGEN(Register)                AMD_VI_IOMMU_READ_ULONGLONG(Register, AMD_VI_ICR_EVENTLOGEN_MASK, AMD_VI_ICR_EVENTLOGEN_SHIFT)
#define AMD_VI_WRITE_ICR_EVENTLOGEN(Register, Val)          AMD_VI_IOMMU_WRITE_ULONGLONG(Register, AMD_VI_ICR_EVENTLOGEN_MASK, AMD_VI_ICR_EVENTLOGEN_SHIFT, Val)

#define AMD_VI_ICR_EVENTINTEN_MASK                          0x01
#define AMD_VI_ICR_EVENTINTEN_SHIFT                         3
#define AMD_VI_READ_ICR_EVENTINTEN(Register)                AMD_VI_IOMMU_READ_ULONGLONG(Register, AMD_VI_ICR_EVENTINTEN_MASK, AMD_VI_ICR_EVENTINTEN_SHIFT)
#define AMD_VI_WRITE_ICR_EVENTINTEN(Register, Val)          AMD_VI_IOMMU_WRITE_ULONGLONG(Register, AMD_VI_ICR_EVENTINTEN_MASK, AMD_VI_ICR_EVENTINTEN_SHIFT, Val)

#define AMD_VI_ICR_COMWAITINTEN_MASK                        0x01
#define AMD_VI_ICR_COMWAITINTEN_SHIFT                       4
#define AMD_VI_READ_ICR_COMWAITINTEN(Register)              AMD_VI_IOMMU_READ_ULONGLONG(Register, AMD_VI_ICR_COMWAITINTEN_MASK, AMD_VI_ICR_COMWAITINTEN_SHIFT)
#define AMD_VI_WRITE_ICR_COMWAITINTEN(Register, Val)        AMD_VI_IOMMU_WRITE_ULONGLONG(Register, AMD_VI_ICR_COMWAITINTEN_MASK, AMD_VI_ICR_COMWAITINTEN_SHIFT, Val)

#define AMD_VI_ICR_INVTIMEOUT_MASK                          0x07
#define AMD_VI_ICR_INVTIMEOUT_SHIFT                         5
#define AMD_VI_ICR_INVTIMEOUT_1MS                           0b001
#define AMD_VI_ICR_INVTIMEOUT_10MS                          0b010
#define AMD_VI_ICR_INVTIMEOUT_100MS                         0b011
#define AMD_VI_ICR_INVTIMEOUT_1S                            0b100
#define AMD_VI_ICR_INVTIMEOUT_10S                           0b101
#define AMD_VI_ICR_INVTIMEOUT_100S                          0b110
#define AMD_VI_READ_ICR_INVTIMEOUT(Register)                AMD_VI_IOMMU_READ_ULONGLONG(Register, AMD_VI_ICR_INVTIMEOUT_MASK, AMD_VI_ICR_INVTIMEOUT_SHIFT)
#define AMD_VI_WRITE_ICR_INVTIMEOUT(Register, Val)          AMD_VI_IOMMU_WRITE_ULONGLONG(Register, AMD_VI_ICR_INVTIMEOUT_MASK, AMD_VI_ICR_INVTIMEOUT_SHIFT, Val)



//end

//211

typedef struct PACKED _AMD_VI_IOMMU_MMIO_REGISTERS{
    PULONGLONG      Dtbar; //Device Table Base Address Register
    PULONGLONG      Cbbar; //Command Buffer Base Address Register
    PULONGLONG      Elbar; //Event Log Base Address Register
}AMD_VI_IOMMU_MMIO_REGISTERS, * PAMD_VI_IOMMU_MMIO_REGISTERS;

typedef struct _AMD_VI_DRIVER{
    PVOID                               IvrsPointer;
    AMD_VI_TRANSLATION_TABLE_LEVELS     SupportedTranslationTableLevels;
    AMD_VI_TRANSLATION_TABLE_LEVELS     CurrentTranslationTableLevels;
    

    mutex_t                             DeviceTableMutex;
    ListHeader                          DeviceTables;
    mutex_t                             IoPageTablesMutex;
    ListHeader                          IoPageTables;
    mutex_t                             CommandBuffersMutex;
    ListHeader                          CommandBuffers;
    mutex_t                             EventLogsMutex;
    ListHeader                          EventLogs;
    mutex_t                             InterruptRemapTablesMutex; 
    ListHeader                          InterruptRemapTables;
    mutex_t                             PeripheralPageRequestLogMutex;
    ListHeader                          PeripheralPageRequestLog;
    mutex_t                             GuestVirtualApicTablesMutex;
    ListHeader                          GuestVirtualApicTables;
    mutex_t                             GuestVirtualApicLogsMutex;
    ListHeader                          GuestVirtualApicLogs;
}AMD_VI_DRIVER, * PAMD_VI_DRIVER;

#endif