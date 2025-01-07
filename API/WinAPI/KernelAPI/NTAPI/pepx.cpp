#include <LouDDK.h>
#include <NtAPI.h>

NTSTATUS PoFxRegisterCoreDevice(
      PCUNICODE_STRING   Id,
      PPO_FX_CORE_DEVICE Device,
     POHANDLE* Handle
) {

    return 0;
}

NTSTATUS PoFxRegisterPlugin(
          PPEP_INFORMATION        PepInformation,
      PPEP_KERNEL_INFORMATION KernelInformation
) {

    return 0;
}

NTSTATUS PoFxRegisterPluginEx(
          PPEP_INFORMATION        PepInformation,
          ULONGLONG               Flags,
      PPEP_KERNEL_INFORMATION KernelInformation
) {

    return 0;
}


void PEP_ACPI_INITIALIZE_EXTENDED_IO_RESOURCE(
      BOOLEAN            ResourceUsage,
      UCHAR              Decode,
      BOOLEAN            IsMinFixed,
      BOOLEAN            IsMaxFixed,
      UCHAR              ISARanges,
      ULONGLONG          AddressGranularity,
      ULONGLONG          AddressMinimum,
      ULONGLONG          AddressMaximum,
      ULONGLONG          AddressTranslation,
      ULONGLONG          RangeLength,
      ULONGLONG          TypeSpecificAttributes,
      PUNICODE_STRING    DescriptorName,
      BOOLEAN            TranslationTypeNonStatic,
      BOOLEAN            TanslationSparseDensity,
     PPEP_ACPI_RESOURCE Resource
) {


}

void PEP_ACPI_INITIALIZE_EXTENDED_MEMORY_RESOURCE(
      BOOLEAN            ResourceUsage,
      UCHAR              Decode,
      BOOLEAN            IsMinFixed,
      BOOLEAN            IsMaxFixed,
      UCHAR              Cacheable,
      BOOLEAN            ReadWrite,
      ULONGLONG          AddressGranularity,
      ULONGLONG          AddressMinimum,
      ULONGLONG          AddressMaximum,
      ULONGLONG          AddressTranslation,
      ULONGLONG          RangeLength,
      ULONGLONG          TypeSpecificAttributes,
      PUNICODE_STRING    DescriptorName,
      UCHAR              MemoryRangeType,
    BOOLEAN            TranslationTypeNonStatic,
     PPEP_ACPI_RESOURCE Resource
) {


}

void PEP_ACPI_INITIALIZE_GPIO_INT_RESOURCE(
      KINTERRUPT_MODE      InterruptType,
      KINTERRUPT_POLARITY  LevelType,
      BOOLEAN              Shareable,
      BOOLEAN              CanWake,
      GPIO_PIN_CONFIG_TYPE PinConfig,
      USHORT               DebounceTimeout,
      UCHAR                ResourceSourceIndex,
      PUNICODE_STRING      ResourceSourceName,
      BOOLEAN              ResourceUsage,
      PUCHAR               VendorData,
      USHORT               VendorDataLength,
      PUSHORT              PinTable,
      UCHAR                PinCount,
     PPEP_ACPI_RESOURCE   Resource
) {



}


void PEP_ACPI_INITIALIZE_GPIO_IO_RESOURCE(
      BOOLEAN                     Shareable,
      BOOLEAN                     CanWake,
      GPIO_PIN_CONFIG_TYPE        PinConfig,
      USHORT                      DebounceTimeout,
      USHORT                      DriveStrength,
      GPIO_PIN_IORESTRICTION_TYPE IoRestriction,
      UCHAR                       ResourceSourceIndex,
      PUNICODE_STRING             ResourceSourceName,
      BOOLEAN                     ResourceUsage,
      PUCHAR                      VendorData,
      USHORT                      VendorDataLength,
      PUSHORT                     PinTable,
      USHORT                      PinCount,
     PPEP_ACPI_RESOURCE          Resource
) {



}


void PEP_ACPI_INITIALIZE_INTERRUPT_RESOURCE(
      BOOLEAN             ResourceUsage,
      KINTERRUPT_MODE     EdgeLevel,
      KINTERRUPT_POLARITY InterruptLevel,
      BOOLEAN             ShareType,
      BOOLEAN             Wake,
      PULONG              PinTable,
      UCHAR               PinCount,
     PPEP_ACPI_RESOURCE  Resource
) {



}

void PEP_ACPI_INITIALIZE_IOPORT_RESOURCE(
      UCHAR              Decode,
      USHORT             MinimumAddress,
      USHORT             MaximumAddress,
      UCHAR              Alignment,
      UCHAR              PortLength,
     PPEP_ACPI_RESOURCE Resource
) {




}

void PEP_ACPI_INITIALIZE_SPB_UART_RESOURCE(
      ULONG              BaudRate,
      UCHAR              BitsPerByte,
      UCHAR              StopBits,
      UCHAR              LinesInUse,
      UCHAR              IsBigEndian,
      UCHAR              Parity,
      UCHAR              FlowControl,
      USHORT             RxSize,
      USHORT             TxSize,
      PUNICODE_STRING    ResourceSource,
      UCHAR              ResourceSourceIndex,
      BOOLEAN            ResourceUsage,
      BOOLEAN            SharedMode,
      PCHAR              VendorData,
      USHORT             VendorDataLength,
     PPEP_ACPI_RESOURCE Resource
) {



}

void PEP_ACPI_INITIALIZE_MEMORY_RESOURCE(
      UCHAR              ReadWrite,
      ULONG              MinimumAddress,
      ULONG              MaximumAddress,
      ULONG              Alignment,
      ULONG              MemorySize,
     PPEP_ACPI_RESOURCE Resource
) {




}


void PEP_ACPI_INITIALIZE_SPB_SPI_RESOURCE(
      USHORT             DeviceSelection,
      UCHAR              DeviceSelectionPolarity,
      UCHAR              WireMode,
      UCHAR              DataBitLength,
      BOOLEAN            SlaveMode,
      ULONG              ConnectionSpeed,
      UCHAR              ClockPolarity,
      UCHAR              ClockPhase,
      PUNICODE_STRING    ResourceSource,
      UCHAR              ResourceSourceIndex,
      BOOLEAN            ResourceUsage,
      BOOLEAN            SharedMode,
      PCHAR              VendorData,
      USHORT             VendorDataLength,
     PPEP_ACPI_RESOURCE Resource
) {



}

void PEP_ACPI_INITIALIZE_SPB_I2C_RESOURCE(
      USHORT             SlaveAddress,
      BOOLEAN            DeviceInitiated,
      ULONG              ConnectionSpeed,
      BOOLEAN            AddressingMode,
      PUNICODE_STRING    ResourceSource,
      UCHAR              ResourceSourceIndex,
      BOOLEAN            ResourceUsage,
      BOOLEAN            SharedMode,
      PCHAR              VendorData,
      USHORT             VendorDataLength,
     PPEP_ACPI_RESOURCE Resource
) {



}
