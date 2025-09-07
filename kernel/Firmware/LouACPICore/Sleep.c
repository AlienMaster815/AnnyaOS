#include <LouACPI.h>
#include <acpi.h>

static bool AcpiOldSuspendOrdering = false;
static bool AcpiSleepDefaultS3 = false;
static bool NvsNoSaveS3 = false;
static UINT32 SavedBmRld = 0x00;

static void AcpiStoreBmRld(){
    AcpiReadBitRegister(ACPI_BITREG_BUS_MASTER_RLD, &SavedBmRld);
}

static void AcpiRestoreBmRld(){
    UINT32 Data; 
    AcpiReadBitRegister(ACPI_BITREG_BUS_MASTER_RLD, &Data);
    if(Data == SavedBmRld){
        return;
    }
    AcpiWriteBitRegister(ACPI_BITREG_BUS_MASTER_RLD, SavedBmRld);
}
static const LOUSINE_POWER_TRANSITION_OPERATIONS Operations = {
    .SuspendOperation = AcpiStoreBmRld,
    .ResumeOperation = AcpiRestoreBmRld,
};

static UINT8 AcpiSleepStates[ACPI_S_STATE_COUNT] = {0};

static INTEGER InitializeOldSuspendOrdering(PDMI_SYSTEM_ID Unused){
    AcpiOldSuspendOrdering = true;
    return 0;
}

static INTEGER InitializeDefaultS3(PDMI_SYSTEM_ID Unused){
    AcpiSleepDefaultS3 = true;
    return 0;
}

static INTEGER InitializeNvsSaveS3(PDMI_SYSTEM_ID Unused){
    NvsNoSaveS3 = false;
    return 0;
}

static INTEGER InitializeNvsNoSave(PDMI_SYSTEM_ID Unused){
    NvsNoSaveS3 = true;
    return 0;
}

UNUSED static const DMI_SYSTEM_ID AcpiSleepDmiTable[] = {
    {
        .Callback = InitializeOldSuspendOrdering,
        .Identification = "Abit KN9 (nForce Variant)",
        .Matches = {
            DMI_MATCH(DMI_BOARD_VENDOR, "http://www.abit.com.tw/"),
            DMI_MATCH(DMI_BOARD_NAME,   "KN9 Series(NF-CK804)"),
        },
    },
    {
	    .Callback = InitializeOldSuspendOrdering,
	    .Identification = "HP xw4600 Workstation",
	    .Matches = {
		    DMI_MATCH(DMI_SYSTEM_VENDOR, "Hewlett-Packard"),
		    DMI_MATCH(DMI_PRODUCT_NAME, "HP xw4600 Workstation"),
		},
	},
	{
	    .Callback = InitializeOldSuspendOrdering,
	    .Identification = "Asus Pundit P1-AH2 (M2N8L motherboard)",
	    .Matches = {
		    DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTek Computer INC."),
		    DMI_MATCH(DMI_BOARD_NAME, "M2N8L"),
		},
	},
	{
	    .Callback = InitializeOldSuspendOrdering,
	    .Identification = "Panasonic CF51-2L",
	    .Matches = {
		    DMI_MATCH(DMI_BOARD_VENDOR, "Matsushita Electric Industrial Co.,Ltd."),
		    DMI_MATCH(DMI_BOARD_NAME, "CF51-2L"),
		},
	},
	{
	    .Callback = InitializeNvsNoSave,
	    .Identification = "Sony Vaio VGN-FW41E_H",
	    .Matches = {
		    DMI_MATCH(DMI_SYSTEM_VENDOR, "Sony Corporation"),
		    DMI_MATCH(DMI_PRODUCT_NAME, "VGN-FW41E_H"),
		},
	},
	{
	    .Callback = InitializeNvsNoSave,
	    .Identification = "Sony Vaio VGN-FW21E",
	    .Matches = {
		    DMI_MATCH(DMI_SYSTEM_VENDOR, "Sony Corporation"),
		    DMI_MATCH(DMI_PRODUCT_NAME, "VGN-FW21E"),
		},
	},
	{
	    .Callback = InitializeNvsNoSave,
	    .Identification = "Sony Vaio VGN-FW21M",
	    .Matches = {
		    DMI_MATCH(DMI_SYSTEM_VENDOR, "Sony Corporation"),
		    DMI_MATCH(DMI_PRODUCT_NAME, "VGN-FW21M"),
		},
	},
	{
	    .Callback = InitializeNvsNoSave,
	    .Identification = "Sony Vaio VPCEB17FX",
	    .Matches = {
		    DMI_MATCH(DMI_SYSTEM_VENDOR, "Sony Corporation"),
		    DMI_MATCH(DMI_PRODUCT_NAME, "VPCEB17FX"),
		},
	},
	{
	    .Callback = InitializeNvsNoSave,
	    .Identification = "Sony Vaio VGN-SR11M",
	    .Matches = {
		    DMI_MATCH(DMI_SYSTEM_VENDOR, "Sony Corporation"),
		    DMI_MATCH(DMI_PRODUCT_NAME, "VGN-SR11M"),
		},
	},
	{
	    .Callback = InitializeNvsNoSave,
	    .Identification = "Everex StepNote Series",
	    .Matches = {
		    DMI_MATCH(DMI_SYSTEM_VENDOR, "Everex Systems, Inc."),
		    DMI_MATCH(DMI_PRODUCT_NAME, "Everex StepNote Series"),
		},
	},
	{
	    .Callback = InitializeNvsNoSave,
	    .Identification = "Sony Vaio VPCEB1Z1E",
	    .Matches = {
		    DMI_MATCH(DMI_SYSTEM_VENDOR, "Sony Corporation"),
		    DMI_MATCH(DMI_PRODUCT_NAME, "VPCEB1Z1E"),
		},
	},
	{
	    .Callback = InitializeNvsNoSave,
	    .Identification = "Sony Vaio VGN-NW130D",
	    .Matches = {
		    DMI_MATCH(DMI_SYSTEM_VENDOR, "Sony Corporation"),
		    DMI_MATCH(DMI_PRODUCT_NAME, "VGN-NW130D"),
		},
	},
	{
	    .Callback = InitializeNvsNoSave,
	    .Identification = "Sony Vaio VPCCW29FX",
	    .Matches = {
		    DMI_MATCH(DMI_SYSTEM_VENDOR, "Sony Corporation"),
		    DMI_MATCH(DMI_PRODUCT_NAME, "VPCCW29FX"),
		},
	},
	{
	    .Callback = InitializeNvsNoSave,
	    .Identification = "Averatec AV1020-ED2",
	    .Matches = {
		    DMI_MATCH(DMI_SYSTEM_VENDOR, "AVERATEC"),
		    DMI_MATCH(DMI_PRODUCT_NAME, "1000 Series"),
		},
	},
	{
	    .Callback = InitializeOldSuspendOrdering,
	    .Identification = "Asus A8N-SLI DELUXE",
	    .Matches = {
		    DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
		    DMI_MATCH(DMI_BOARD_NAME, "A8N-SLI DELUXE"),
		},
	},
	{
	    .Callback = InitializeOldSuspendOrdering,
	    .Identification = "Asus A8N-SLI Premium",
	    .Matches = {
		    DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
		    DMI_MATCH(DMI_BOARD_NAME, "A8N-SLI Premium"),
		},
	},
	{
	    .Callback = InitializeNvsNoSave,
	    .Identification = "Sony Vaio VGN-SR26GN_P",
	    .Matches = {
		    DMI_MATCH(DMI_SYSTEM_VENDOR, "Sony Corporation"),
		    DMI_MATCH(DMI_PRODUCT_NAME, "VGN-SR26GN_P"),
		},
	},
	{
	    .Callback = InitializeNvsNoSave,
	    .Identification = "Sony Vaio VPCEB1S1E",
	    .Matches = {
		    DMI_MATCH(DMI_SYSTEM_VENDOR, "Sony Corporation"),
		    DMI_MATCH(DMI_PRODUCT_NAME, "VPCEB1S1E"),
		},
	},
	{
	    .Callback = InitializeNvsNoSave,
	    .Identification = "Sony Vaio VGN-FW520F",
	    .Matches = {
		    DMI_MATCH(DMI_SYSTEM_VENDOR, "Sony Corporation"),
		    DMI_MATCH(DMI_PRODUCT_NAME, "VGN-FW520F"),
		},
	},
	{
	    .Callback = InitializeNvsNoSave,
	    .Identification = "Asus K54C",
	    .Matches = {
		    DMI_MATCH(DMI_SYSTEM_VENDOR, "ASUSTeK Computer Inc."),
		    DMI_MATCH(DMI_PRODUCT_NAME, "K54C"),
		},
	},
	{
	    .Callback = InitializeNvsNoSave,
	    .Identification = "Asus K54HR",
	    .Matches = {
		    DMI_MATCH(DMI_SYSTEM_VENDOR, "ASUSTeK Computer Inc."),
		    DMI_MATCH(DMI_PRODUCT_NAME, "K54HR"),
		},
	},
	{
	    .Callback = InitializeNvsSaveS3,
	    .Identification = "Asus 1025C",
	    .Matches = {
		    DMI_MATCH(DMI_SYSTEM_VENDOR, "ASUSTeK COMPUTER INC."),
		    DMI_MATCH(DMI_PRODUCT_NAME, "1025C"),
		},
	},
	{
	    .Callback = InitializeDefaultS3,
	    .Identification = "ASUS ROG Zephyrus M16 (2023)",
	    .Matches = {
		    DMI_MATCH(DMI_SYSTEM_VENDOR, "ASUSTeK COMPUTER INC."),
		    DMI_MATCH(DMI_PRODUCT_NAME, "ROG Zephyrus M16 GU604V"),
		},
	},
	{
	    .Callback = InitializeNvsSaveS3,
	    .Identification = "Lenovo G50-45",
	    .Matches = {
		    DMI_MATCH(DMI_SYSTEM_VENDOR, "LENOVO"),
		    DMI_MATCH(DMI_PRODUCT_NAME, "80E3"),
		},
	},
	{
	    .Callback = InitializeNvsSaveS3,
	    .Identification = "Lenovo G40-45",
	    .Matches = {
		    DMI_MATCH(DMI_SYSTEM_VENDOR, "LENOVO"),
		    DMI_MATCH(DMI_PRODUCT_NAME, "80E1"),
		},
	},
	{
	    .Callback = InitializeDefaultS3,
	    .Identification = "ThinkPad X1 Tablet(2016)",
	    .Matches = {
		    DMI_MATCH(DMI_SYSTEM_VENDOR, "LENOVO"),
		    DMI_MATCH(DMI_PRODUCT_NAME, "20GGA00L00"),
		},
	},
	{},
};

static void AcpiSleepDmiCheck(){
    if(DmiGetBiosYear() >= 2012){
        InitializeNvsNoSave(0x00);
    }
    LouKeCheckDmiSystem((PDMI_SYSTEM_ID)AcpiSleepDmiTable);
}

static BOOL AcpiSleepStateSupported(INTEGER i){
    ACPI_STATUS Status;
    UINT8 TypeA, TypeB;

    Status = AcpiGetSleepTypeData(i, &TypeA, &TypeB);
    return (ACPI_SUCCESS(Status) && (AcpiGbl_FADT.SleepControl.Address) && (AcpiGbl_FADT.SleepStatus.Address));
}

static void AcpiSleepSuspendSetup(){
    UNUSED BOOL    SuspendOpsNeeded = false;
    INTEGER i = 0;

    for(i = ACPI_STATE_S1; i < ACPI_STATE_S4; i++){
        if(AcpiSleepStateSupported(i)){
            AcpiSleepStates[i] = 1;
            SuspendOpsNeeded = true;
        }
    }
    //TODO:
	//while(1);
}

LOUSTATUS AcpiInitializeSleep(){

    UNUSED CHAR    Supported[ACPI_S_STATE_COUNT * 3 + 1];
    UNUSED string  Position;
    UNUSED INTEGER i = 0x00;

    AcpiSleepDmiCheck();    
    AcpiSleepStates[ACPI_STATE_S0] = 1;
    LouKeRegisterPowerTransitionOperations(
        (PLOUSINE_POWER_TRANSITION_OPERATIONS)&Operations
    );
    AcpiSleepSuspendSetup();
    //TODO:

	//while(1);
    return STATUS_SUCCESS;
}