
#define SATA_SIGNATURE_ATA      0x101
#define SATA_SIGNATURE_ATAPI    0xEB140101
#define SATA_SIGNATURE_SEMB     0xC33C0101
#define SATA_SIGNATURE_PM       0x96690101

#define HBA_PORT_IPM_ACTIVE     1
#define HBA_PORT_DET_PRESENT    3

//AHCI Device list information from linux kernel documentation

#define AHCI_BOARD_NORMAL_AHCI  0 //Ahci Device Conforms to specification
#define AHCI_BOARD_43_BIT_DMA   1 //43 bit dma only ahci device
#define AHCI_BOARD_IGN_IFFER    2 //IGN_IFFER is iffy;
#define AHCI_BOARD_NO_BOUNCE    3 //systems dont require bounce delay
#define AHCI_BOARD_NO_MSI       4 //device has broken MSI
#define AHCI_BOARD_INTEL_PCS    5 //pci quirk for old intel chips however cannot assume they are not still broken until verification withought quirk code
#define AHCI_BOARD_PCS_NO_SLEEP 6 //Device has broken sleep system
#define AHCI_BOARD_PCS_NO_SNTF  7 //HBA's SNTF System Is Broken
#define AHCI_BOARD_HAS_FBS      8 //HBA Supports Fiss based switching but doesent report it 

//the following are specifica chips that need special attention
#define AHCI_BOARD_AL_CHIP      9
#define AHCI_BOARD_AVN_CHIP     10
#define AHCI_BOARD_MCP65_CHIP   11
#define AHCI_BOARD_MCP77_CHIP   12
#define AHCI_BOARD_MCP89_CHIP   13
#define AHCI_BOARD_MV_CHIP      14
#define AHCI_BOARD_SB600_CHIP   15
#define AHCI_BOARD_SB700_CHIP   16
#define AHCI_BOARD_VT8251_CHIP  17
//the following are the systems that are familiy membors of the above mcp
#define AHCI_BOARD_LINUX_CHIP   AHCI_BOARD_MCP65_CHIP //this is a board designed with a linux firmware
#define AHCI_BOARD_MCP67_CHIP   AHCI_BOARD_MCP65_CHIP
#define AHCI_BOARD_MCP73_CHIP   AHCI_BOARD_MCP65_CHIP
#define AHCI_BOARD_MCP79_CHIP   AHCI_BOARD_MCP77_CHIP

//End of Device list from Linux Kernel Documetation

#define AHCI_STANDARD_ABAR                  5
#define AHCI_STA2X11_ABAR                   0
#define AHCI_ENMOTUS_ABAR                   2
#define AHCI_CAVIUM_ABAR                    0
#define AHCI_GENERATION_5_CAVIUM_ABAR       4
#define AHCI_LOONGSON_ABAR                  0

typedef struct _AHCI_DRIVER_PRIVATE_DATA{
    PAHCI_GENERIC_HOST_CONTROL  GenericHostController;
    PAHCI_GENERIC_PORT          GenericPort;
    P_PCI_DEVICE_OBJECT         PDEV;
    uint64_t                    AhciFlags;
    uint64_t                    AtaFlags;
    uint64_t                    PioFlags;
    uint64_t                    DmaFlags;
    uint64_t                    PrivateFlags;
    uint8_t                     InterruptRequestVector;
    uint8_t                     DmaBits;
    uint16_t                    PortMap;
}AHCI_DRIVER_PRIVATE_DATA, * PAHCI_DRIVER_PRIVATE_DATA;

//Driver Operations
LOUSTATUS AhciGenricDMAPrepCommand(
    PATA_QUEUED_COMMAND QueuedCommand
);
LOUSTATUS AhciGenricDMAIssueCommand(
    PATA_QUEUED_COMMAND QueuedCommand
);
LOUSTATUS AhciGenericHardReset(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort);
LOUSTATUS AhciVt8251HardReset(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort);
LOUSTATUS AhciP5wdhHardReset(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort);
LOUSTATUS AhciAvnHardReset(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort);
LOUSTATUS ResetAhcPciController(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost);

//Endof Driver Operations

