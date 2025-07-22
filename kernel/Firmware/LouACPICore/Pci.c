#include <LouACPI.h>
#include <acpi.h>

static BOOL PciHasE820 = true;
static BOOL PciIgnoreSeg = false;
static BOOL PciUseCrs = true;

static INTEGER SetNoE820(PDMI_SYSTEM_ID Id){
    PciHasE820 = false;
    return 0x00;
}

static INTEGER SetIgnoreSeg(PDMI_SYSTEM_ID Id){
    PciIgnoreSeg = true;
    return 0x00;
}

static INTEGER SetUseCrs(PDMI_SYSTEM_ID Id){
    PciUseCrs = true;
    return 0x00;
}

static INTEGER SetNoUseCrs(PDMI_SYSTEM_ID Id){
    PciUseCrs = false;
    return 0x00;
}

UNUSED static DMI_SYSTEM_ID AcpiCheckPciCrsQuirk[] = {
	{
		.Callback = SetUseCrs,
		.Identification = "IBM System x3800",
		.Matches = {
			DMI_MATCH(DMI_SYSTEM_VENDOR, "IBM"),
			DMI_MATCH(DMI_PRODUCT_NAME, "x3800"),
		},
	},
        {
		.Callback = SetUseCrs,
		.Identification = "ASRock ALiveSATA2-GLAN",
		.Matches = {
			DMI_MATCH(DMI_PRODUCT_NAME, "ALiveSATA2-GLAN"),
                },
        },
	{
		.Callback = SetUseCrs,
		.Identification = "ASUS M2V-MX SE",
		.Matches = {
			DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
			DMI_MATCH(DMI_BOARD_NAME, "M2V-MX SE"),
			DMI_MATCH(DMI_BIOS_VENDOR, "American Megatrends Inc."),
		},
	},
	{
		.Callback = SetUseCrs,
		.Identification = "MSI MS-7253",
		.Matches = {
			DMI_MATCH(DMI_BOARD_VENDOR, "MICRO-STAR INTERNATIONAL CO., LTD"),
			DMI_MATCH(DMI_BOARD_NAME, "MS-7253"),
			DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies, LTD"),
		},
	},
	{
		.Callback = SetUseCrs,
		.Identification = "Foxconn K8M890-8237A",
		.Matches = {
			DMI_MATCH(DMI_BOARD_VENDOR, "Foxconn"),
			DMI_MATCH(DMI_BOARD_NAME, "K8M890-8237A"),
			DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies, LTD"),
		},
	},
	{
		.Callback = SetNoUseCrs,
		.Identification = "Dell Studio 1557",
		.Matches = {
			DMI_MATCH(DMI_BOARD_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Studio 1557"),
			DMI_MATCH(DMI_BIOS_VERSION, "A09"),
		},
	},
	{
		.Callback = SetNoUseCrs,
		.Identification = "Thinkpad SL510",
		.Matches = {
			DMI_MATCH(DMI_BOARD_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_BOARD_NAME, "2847DFG"),
			DMI_MATCH(DMI_BIOS_VERSION, "6JET85WW (1.43 )"),
		},
	},
	{
		.Callback = SetNoUseCrs,
		.Identification = "Supermicro X8DTH",
		.Matches = {
			DMI_MATCH(DMI_SYSTEM_VENDOR, "Supermicro"),
			DMI_MATCH(DMI_PRODUCT_NAME, "X8DTH-i/6/iF/6F"),
			DMI_MATCH(DMI_BIOS_VERSION, "2.0a"),
		},
	},
	{
		.Callback = SetIgnoreSeg,
		.Identification = "HP xw9300",
		.Matches = {
			DMI_MATCH(DMI_SYSTEM_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, "HP xw9300 Workstation"),
		},
	},
	{
		.Callback = SetNoE820,
		.Identification = "Lenovo *IIL* product version",
		.Matches = {
			DMI_MATCH(DMI_SYSTEM_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "IIL"),
		},
	},
	{
		.Callback = SetNoE820,
		.Identification = "Acer Spin 5 (SP513-54N)",
		.Matches = {
			DMI_MATCH(DMI_SYSTEM_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Spin SP513-54N"),
		},
	},
	{
		.Callback = SetNoE820,
		.Identification = "Clevo X170KM-G Barebone",
		.Matches = {
			DMI_MATCH(DMI_BOARD_NAME, "X170KM-G"),
		},
	},
	{}
};


LOUSTATUS ParsePciMcfg(PACPI_TABLE_HEADER Header){


    LouPrint("ParsePciMcfg()\n");
    while(1);
    return AE_OK;
}


void PciMmcfgLateInit(){
    LouPrint("PciMmcfgLateInit()\n");
    LOUSTATUS Status = LouKeAcpiTableTableParse(ACPI_SIG_MCFG, ParsePciMcfg);
    if(Status != STATUS_SUCCESS){
        LouPrint("Error Saving PCI MCFG\n");
    }
}

void AcpiCheckPciCrsQuirks(){
    INTEGER Year = DmiGetBiosYear();

    if((Year >= 0) && (Year < 2008) && (GetIoMemEnd() <= UINT32_MAX)){
        PciUseCrs = false;
    }

    if(Year >= 2023){
        PciHasE820 = false;
    }

    CheckDmiSystem(AcpiCheckPciCrsQuirk);

}

//INTEGER AcpiScanAddHandlerWithHotplug(){
	
//}

void AcpiInitializePciRoot(){

    AcpiCheckPciCrsQuirks();


    LouPrint("AcpiInitializePciRoot()\n");
    while(1);
}