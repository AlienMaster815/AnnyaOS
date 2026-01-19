#include "Ps2Bus.h"

static spinlock_t Ps2Lock = {0};
static mutex_t Ps2Mutex = {0};
static LOU_BUS_OBJECT Ps2BusObjects = {0};

static PS2_DEVICE_OBJECT Ps2Devices[TOTAL_PS2_PORTS] = {0};

static 
LOUSTATUS 
Ps2ReadDataRegister(UINT8* Data){
    size_t TimeOut;
    LouKIRQL Irql;
    if(!Data){
        return STATUS_INVALID_PARAMETER;
    }
    LouKeAcquireSpinLock(&Ps2Lock, &Irql);
    for(TimeOut = PS2_TIMEOUT_MS; TimeOut > 0; TimeOut--){
        if(Ps2ReadStatus() & (PS2_OUTPUT_BUFFER_FULL)){
            break;
        }else if(Ps2ReadStatus() & PS2_TIMEOUT_ERROR){
            TimeOut = 0;
            break;
        }
        sleep(5);
    }
    if(!TimeOut){
        LouKeReleaseSpinLock(&Ps2Lock, &Irql);
        return STATUS_TIMEOUT;
    }
    *Data = Ps2ReadData(); 
    LouKeReleaseSpinLock(&Ps2Lock, &Irql);
    return STATUS_SUCCESS;
}

static
LOUSTATUS 
Ps2WriteDataRegister(UINT8 Data){
    size_t TimeOut;
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&Ps2Lock, &Irql);
    for(TimeOut = PS2_TIMEOUT_MS; TimeOut > 0; TimeOut--){
        if(!(Ps2ReadStatus() & (PS2_INPUT_BUFFER_FULL))){
            break;
        }else if(Ps2ReadStatus() & PS2_TIMEOUT_ERROR){
            TimeOut = 0;
            break;
        }
        sleep(5);
    }
    if(!TimeOut){
        LouKeReleaseSpinLock(&Ps2Lock, &Irql);
        return STATUS_TIMEOUT;
    }
    Ps2WriteData(Data);
    LouKeReleaseSpinLock(&Ps2Lock, &Irql);
    return STATUS_SUCCESS;
}

//TODO: Tommorow Start with Command Writing

static LOUSTATUS Ps2WriteCommandRegister(UINT8 Command){
    size_t TimeOut;
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&Ps2Lock, &Irql);
    for(TimeOut = PS2_TIMEOUT_MS; TimeOut > 0; TimeOut--){
        if(!(Ps2ReadStatus() & (PS2_INPUT_BUFFER_FULL))){
            break;
        }else if(Ps2ReadStatus() & PS2_TIMEOUT_ERROR){
            TimeOut = 0;
            break;
        }
        sleep(5);
    }
    if(!TimeOut){
        LouKeReleaseSpinLock(&Ps2Lock, &Irql);
        return STATUS_TIMEOUT;
    }
    Ps2WriteCommand(Command);
    LouKeReleaseSpinLock(&Ps2Lock, &Irql);
    return STATUS_SUCCESS;
}

static LOUSTATUS Ps2BindDeviceToDriver(PPS2_DEVICE_OBJECT Ps2Device){
    LOUSTATUS Status;
    LOUSTATUS (*Ps2DeviceInitFunction)(PPS2_DEVICE_OBJECT);
    switch(Ps2Device->DeviceClass){

        case PS2_MF2_KEYBOARD1:
        case PS2_MF2_KEYBOARD2:
            Ps2DeviceInitFunction = (LOUSTATUS (*)(PPS2_DEVICE_OBJECT))LouKeLoadDriver("MF2KBD.SYS", "LouKeHalInitializeMf2Ps2Keyboard");
            if(Ps2DeviceInitFunction){
                Status = Ps2DeviceInitFunction(Ps2Device);
                if(Status == STATUS_SUCCESS){
                    Ps2Device->HasDriver = true;
                }
            }else {
                LouPrint("ERROR:Unable To Register Device\n");
                Status = STATUS_UNSUCCESSFUL;
            }
            break;
        case PS2_MOUSE:
            Ps2DeviceInitFunction = (LOUSTATUS (*)(PPS2_DEVICE_OBJECT))LouKeLoadDriver("PS2MOUSE.SYS", "LouKeHalInitializePs2Mouse");
            if(Ps2DeviceInitFunction){
                Status = Ps2DeviceInitFunction(Ps2Device);
                if(Status == STATUS_SUCCESS){
                    Ps2Device->HasDriver = true;
                }
            }
            break;
        default:
            LouPrint("Device Unkown Could Not Bind To Driver\n");
            LouPrint("DEVICE_CLASS DEBUG_DUMP:%h\n", Ps2Device->DeviceClass);
            Status = STATUS_UNSUCCESSFUL;
    }
    return Status;
}

DRIVER_EXPORT
LOUSTATUS 
LouKeHalPs2ReadConfigurationByte(
    UINT8* Byte
){
    LOUSTATUS Status = STATUS_NO_SUCH_DEVICE;
    MutexLock(&Ps2Mutex);
    if((Ps2Devices[0].ChipsetDevice) && (Ps2Devices[0].DeviceExists)){
        Status = Ps2WriteCommandRegister(PS2_READ_BYTE(PS2_CONFIG_BYTE));
        if(Status != STATUS_SUCCESS){
            MutexUnlock(&Ps2Mutex);
            return Status;
        }
        Status = Ps2ReadDataRegister(Byte);
    }
    MutexUnlock(&Ps2Mutex);
    return Status;
}

DRIVER_EXPORT 
LOUSTATUS
LouKeHalPs2WriteConfigurationByte(
    UINT8               Byte
){
    LOUSTATUS Status = STATUS_NO_SUCH_DEVICE;
    MutexLock(&Ps2Mutex);
    if((Ps2Devices[0].ChipsetDevice) && (Ps2Devices[0].DeviceExists)){
        Status = Ps2WriteCommandRegister(PS2_WRITE_BYTE(PS2_CONFIG_BYTE));
        if(Status != STATUS_SUCCESS){
            MutexUnlock(&Ps2Mutex);
            return Status;
        }
        Status = Ps2WriteDataRegister(Byte);
    }
    MutexUnlock(&Ps2Mutex);
    return Status;
}

DRIVER_EXPORT
LOUSTATUS 
LouKeHalPs2DisableSecondaryPort(){
    LOUSTATUS Status = STATUS_NO_SUCH_DEVICE;
    MutexLock(&Ps2Mutex);
    if((Ps2Devices[1].ChipsetDevice) && (Ps2Devices[1].DeviceExists)){
        Status = Ps2WriteCommandRegister(PS2_DISABLE_SECONDARY_PORT);
    }
    MutexUnlock(&Ps2Mutex);
    return Status;
}

DRIVER_EXPORT
LOUSTATUS
LouKeHalPs2EnableSecondaryPort(){
    LOUSTATUS Status = STATUS_NO_SUCH_DEVICE;
    MutexLock(&Ps2Mutex);
    if((Ps2Devices[1].ChipsetDevice) && (Ps2Devices[1].DeviceExists)){
        Status = Ps2WriteCommandRegister(PS2_ENABLE_SECONDARY_PORT);
    }
    MutexUnlock(&Ps2Mutex);
    return Status;
}

DRIVER_EXPORT
LOUSTATUS 
LouKeHalPs2TestSecondaryPort(
    UINT8*   Result
){
    LOUSTATUS Status = STATUS_NO_SUCH_DEVICE;
    if((Ps2Devices[1].ChipsetDevice) && (Ps2Devices[1].DeviceExists)){
        Status = Ps2WriteCommandRegister(PS2_TEST_SECONDARY_PORT);
        if(Status != STATUS_SUCCESS){
            MutexUnlock(&Ps2Mutex);
            return Status;
        }
        Status = Ps2ReadDataRegister(Result);
    }
    MutexUnlock(&Ps2Mutex);
    return Status;
}

DRIVER_EXPORT
LOUSTATUS 
LouKeHalPs2TestController(
    UINT8* Result
){
    LOUSTATUS Status = STATUS_NO_SUCH_DEVICE;
    if(!Result){
        return STATUS_INVALID_PARAMETER;
    }
    MutexLock(&Ps2Mutex);
    if((Ps2Devices[0].ChipsetDevice) && (Ps2Devices[0].DeviceExists)){
        Status = Ps2WriteCommandRegister(PS2_TEST_CONTROLLER);
        if(Status != STATUS_SUCCESS){
            MutexUnlock(&Ps2Mutex);
            return Status;
        }
        Status = Ps2ReadDataRegister(Result);
    }
    MutexUnlock(&Ps2Mutex);
    return Status;
}

DRIVER_EXPORT
LOUSTATUS 
LouKeHalPs2TestPrimaryPort(UINT8* Result){
    LOUSTATUS Status = STATUS_NO_SUCH_DEVICE;
    MutexLock(&Ps2Mutex);
    if((Ps2Devices[0].ChipsetDevice) && (Ps2Devices[0].DeviceExists)){
        Status = Ps2WriteCommandRegister(PS2_TEST_PRIMARY_PORT);
        if(Status != STATUS_SUCCESS){
            MutexUnlock(&Ps2Mutex);
            return Status;
        }
        Status = Ps2ReadDataRegister(Result);
    }
    MutexUnlock(&Ps2Mutex);
    return Status;
}

DRIVER_EXPORT
LOUSTATUS 
LouKeHalPs2DisablePrimaryPort(){
    LOUSTATUS Status = STATUS_NO_SUCH_DEVICE;
    MutexLock(&Ps2Mutex);
    if((Ps2Devices[0].ChipsetDevice) && (Ps2Devices[0].DeviceExists)){
        Status = Ps2WriteCommandRegister(PS2_DISABLE_PRIMARY_PORT);
    }
    MutexUnlock(&Ps2Mutex);
    return Status;
}

DRIVER_EXPORT
LOUSTATUS
LouKeHalPs2EnablePrimaryPort(){
    LOUSTATUS Status = STATUS_NO_SUCH_DEVICE;
    MutexLock(&Ps2Mutex);
    if((Ps2Devices[0].ChipsetDevice) && (Ps2Devices[0].DeviceExists)){
        Status = Ps2WriteCommandRegister(PS2_ENABLE_PRIMARY_PORT);
    }
    MutexUnlock(&Ps2Mutex);
    return Status;
}

DRIVER_EXPORT
LOUSTATUS
LouKeHalPs2FlushBuffer(){
    LOUSTATUS Status = STATUS_NO_SUCH_DEVICE;
    MutexLock(&Ps2Mutex);
    if((Ps2Devices[0].ChipsetDevice) && (Ps2Devices[0].DeviceExists)){
        Ps2ReadData();
        Status = STATUS_SUCCESS;
    }
    MutexUnlock(&Ps2Mutex);
    return Status;
}

DRIVER_EXPORT
LOUSTATUS
LouKeHalPs2CommandPs2Device(
    PPS2_DEVICE_OBJECT Ps2Device, 
    UINT8*  Input, //req
    SIZE    InSize, //req
    UINT8*  Output, //opt
    SIZE    OutSize //opt
){
    LOUSTATUS Status = STATUS_UNSUCCESSFUL;
    if((!Input) || (!InSize) || (!Ps2Device)){
        return STATUS_INVALID_PARAMETER;
    }
    MutexLock(&Ps2Mutex);
    if((Ps2Device->ChipsetDevice) && (Ps2Device->DeviceExists)){
        switch(Ps2Device->PortNumber){
            case 1:
                Status = Ps2WriteCommandRegister(PS2_WRITE_TO_SECONDARY_INPUT);
                if(Status != STATUS_SUCCESS){
                    MutexUnlock(&Ps2Mutex);
                    return Status;
                }
                for(size_t i = 0 ; i < InSize; i++){
                    Status = Ps2WriteDataRegister(Input[i]); 
                    if(Status != STATUS_SUCCESS){
                        MutexUnlock(&Ps2Mutex);
                        return Status;
                    }
                }
                if(Output){
                    for(size_t i = 0 ; i < OutSize; i++){
                        Status = Ps2ReadDataRegister(&Output[i]);
                        if(Status != STATUS_SUCCESS){
                            MutexUnlock(&Ps2Mutex);
                            return Status;
                        }
                    }
                }
                break;
            default: //0
                for(size_t i = 0 ; i < InSize; i++){
                    Status = Ps2WriteDataRegister(Input[i]); 
                    if(Status != STATUS_SUCCESS){
                        MutexUnlock(&Ps2Mutex);
                        return Status;
                    }
                }
                if(Output){
                    for(size_t i = 0 ; i < OutSize; i++){
                        Status = Ps2ReadDataRegister(&Output[i]);
                        if(Status != STATUS_SUCCESS){
                            MutexUnlock(&Ps2Mutex);
                            return Status;
                        }
                    }
                }
                break;
        }
    }
    MutexUnlock(&Ps2Mutex);
    return Status;
}

DRIVER_EXPORT
void 
LouKeHalPs2InstallInterruptHandler(
    PPS2_DEVICE_OBJECT Device, 
    void(*Handler)(uint64_t)
){
    RegisterInterruptHandler(Handler, Device->Irq + 0x20, false, (uint64_t)Device);  
}

DRIVER_EXPORT 
LOUSTATUS 
LouKeHalPs2EnableInterrupt(PPS2_DEVICE_OBJECT Ps2Device){
    UINT8   ConfigByte;
    LOUSTATUS Status = STATUS_UNSUCCESSFUL;

    if((Ps2Device->ChipsetDevice) && (Ps2Device->DeviceExists)){
        switch(Ps2Device->PortNumber){
            case 1:
                Status = LouKeHalPs2ReadConfigurationByte(&ConfigByte);
                if(Status != STATUS_SUCCESS){
                    return Status;
                }
                ConfigByte |= (PS2_SECONDARY_PORT_IRQ_ENABLED);
                Status = LouKeHalPs2WriteConfigurationByte(ConfigByte);
                break;
            default: //0
                Status = LouKeHalPs2ReadConfigurationByte(&ConfigByte);
                if(Status != STATUS_SUCCESS){
                    return Status;
                }
                ConfigByte |= (PS2_PRIMARY_PORT_IRQ_ENABLED);
                Status = LouKeHalPs2WriteConfigurationByte(ConfigByte);
                break;
        }
    }
    return Status;
}

DRIVER_EXPORT 
LOUSTATUS 
LouKeHalPs2DisableInterrupt(PPS2_DEVICE_OBJECT Ps2Device){
    UINT8   ConfigByte;
    LOUSTATUS Status = STATUS_UNSUCCESSFUL;
    if((Ps2Device->ChipsetDevice) && (Ps2Device->DeviceExists)){
        switch(Ps2Device->PortNumber){
            case 1:
                Status = LouKeHalPs2ReadConfigurationByte(&ConfigByte);
                if(Status != STATUS_SUCCESS){
                    return Status;
                }
                ConfigByte &= ~(PS2_SECONDARY_PORT_IRQ_ENABLED);
                Status = LouKeHalPs2WriteConfigurationByte(ConfigByte);
                break;
            default: //0
                Status = LouKeHalPs2ReadConfigurationByte(&ConfigByte);
                if(Status != STATUS_SUCCESS){
                    return Status;
                }
                ConfigByte &= ~(PS2_PRIMARY_PORT_IRQ_ENABLED);
                Status = LouKeHalPs2WriteConfigurationByte(ConfigByte);
                break;
        }
    }
    return Status;
}

DRIVER_EXPORT
LOUSTATUS
LouKeHalPs2ReadDeviceBuffer(
    PPS2_DEVICE_OBJECT Ps2Device, 
    UINT8* Buffer, 
    SIZE Length
){
    if(!Buffer){
        return STATUS_INVALID_PARAMETER;
    }
    LOUSTATUS Status = STATUS_UNSUCCESSFUL;
    if((Ps2Device->ChipsetDevice) && (Ps2Device->DeviceExists)){
        MutexUnlock(&Ps2Mutex);
        for(size_t i = 0 ; i < Length; i++){
            Status = Ps2ReadDataRegister(&Buffer[i]);
            if(Status != STATUS_SUCCESS){
                MutexUnlock(&Ps2Mutex);
                return Status;
            }
        }
        MutexUnlock(&Ps2Mutex);
    }
    return Status;
}

DRIVER_EXPORT
UINT8 
LouKeHalPs2CheckControllerStatus(){
    return Ps2ReadStatus();
}

LOUSTATUS Ps2InitializeBus(PLOU_BUS BussClass, PLOU_BUS_OBJECT Object){
    LOUSTATUS InitStatus;
    LouPrint("PS2IO.SYS:Ps2InitializeBus()\n");
    Object->BusPrivateData = (PVOID)Ps2Devices;
    //Initialize Port 1
    Ps2Devices[0].PortNumber = 0;
    Ps2Devices[0].Irq = KEYBOARD_INTERRUPT;
    //Initialize Port 2
    Ps2Devices[1].PortNumber = 1;
    Ps2Devices[1].Irq = AUX_INTERRUPT;
    for(size_t i = 0 ; i < 2; i++){
        Ps2Devices[i].DeviceExists = true; 
        Ps2Devices[i].ChipsetDevice = true; 
    }
    UINT8 DataByte;
    UINT8 CommandByte;

    InitStatus = LouKeHalPs2DisablePrimaryPort();
    if(InitStatus != STATUS_SUCCESS){
        return InitStatus;
    }
    LouKeHalPs2DisableSecondaryPort();
    
    LouKeHalPs2FlushBuffer();

    InitStatus = LouKeHalPs2ReadConfigurationByte(&CommandByte);
    if(InitStatus != STATUS_SUCCESS){
        return InitStatus;
    }

    CommandByte &= ~(PS2_PRIMARY_PORT_IRQ_ENABLED | PS2_PRIMARY_PORT_CLOCK_DISABLED | PS2_PRIMARY_PORT_TRANSLATION);

    LouKeHalPs2WriteConfigurationByte(CommandByte);

    InitStatus = LouKeHalPs2TestController(&DataByte);
    if(InitStatus != STATUS_SUCCESS){
        return InitStatus;
    }

    if(DataByte != PS2_RET_CONTROLL_TEST){
        return STATUS_IO_DEVICE_ERROR;
    }

    LouKeHalPs2WriteConfigurationByte(CommandByte);

    LouKeHalPs2EnableSecondaryPort();

    LouKeHalPs2ReadConfigurationByte(&DataByte);

    if(DataByte & (PS2_SECONDARY_PORT_CLOCK_DSIABLED)){
        Ps2Devices[1].DeviceExists = false; 
        LouPrint("NOTICE: PS2 Controller Has Only One Channel\n");
    }else{
        LouPrint("NOTICE: PS2 Controller Is Dual Channel\n");
        CommandByte &= ~(PS2_SECONDARY_PORT_IRQ_ENABLED | PS2_SECONDARY_PORT_CLOCK_DSIABLED);
    }

    LouKeHalPs2DisableSecondaryPort();

    LouKeHalPs2WriteConfigurationByte(CommandByte);

    InitStatus = LouKeHalPs2TestPrimaryPort(&DataByte);
    if((InitStatus == STATUS_SUCCESS) && (DataByte == 0x00)){
        LouPrint("Primary Ps2 Port Self Test [OK]\n");
    }else{
        LouPrint("Primary Ps2 Port Self Test [FAILED]\n");
        Ps2Devices[0].DeviceExists = false;
    }

    InitStatus = LouKeHalPs2TestSecondaryPort(&DataByte);
    if((InitStatus == STATUS_SUCCESS) && (DataByte == 0x00)){
        LouPrint("Secondary Ps2 Port Self Test [OK]\n");
    }else{
        LouPrint("Secondary Ps2 Port Self Test [FAILED]\n");
        Ps2Devices[1].DeviceExists = false;
    }

    InitStatus = STATUS_SUCCESS;

    LouKeHalPs2EnablePrimaryPort();
    LouKeHalPs2EnableSecondaryPort();

    UINT8 Return[3];
    UINT8 Command = PS2_RESET_DEVICE;
    memset(Return, 0 , 3);

    InitStatus = LouKeHalPs2CommandPs2Device(&Ps2Devices[0], &Command, 1, Return, 2);
    if(
        (InitStatus != STATUS_SUCCESS) || 
        ((Return[0] != 0xFA && Return[0] != 0xAA) && (Return[1] != 0xFA && Return[1] != 0xAA))
    ){
        LouPrint("Primary PS2 Device Reset Failed\n");
        Ps2Devices[0].DeviceExists = false;
    }

    //flush in case the ID Comes
    LouKeHalPs2FlushBuffer();
    LouKeHalPs2FlushBuffer();

    Command = PS2_DISABLE_SCANNING;
    memset(Return, 0 , 3);

    InitStatus = LouKeHalPs2CommandPs2Device(&Ps2Devices[0], &Command, 1, Return, 1);
    if((InitStatus != STATUS_SUCCESS) || (Return[0] != PS2_DEVICE_ACK)){
        LouPrint("Primary PS2 Device Did Not Respond\n");
        Ps2Devices[0].DeviceExists = false;
    }

    Command = PS2_IDENTIFY_DEVICE;
    memset(Return, 0 , 3);
    LouKeHalPs2CommandPs2Device(&Ps2Devices[0], &Command, 1, Return, 3);
    if(Return[0] == PS2_DEVICE_ACK){
        Ps2Devices[0].DeviceClass = (PS2_DEVICE_CLASS)(((UINT32)Return[1] << 8) | ((UINT32)Return[2]));
        Ps2BindDeviceToDriver(&Ps2Devices[0]);
    }else{
        LouPrint("Primary PS2 Device Did Not Respond\n");
        Ps2Devices[0].DeviceExists = false;
    }


    Command = PS2_RESET_DEVICE;
    memset(Return, 0 , 3);
    InitStatus = LouKeHalPs2CommandPs2Device(&Ps2Devices[1], &Command, 1, Return, 2);
    if(
        (InitStatus != STATUS_SUCCESS) || 
        ((Return[0] != 0xFA && Return[0] != 0xAA) && (Return[1] != 0xFA && Return[1] != 0xAA))
    ){
        LouPrint("Secondary PS2 Device Reset Failed\n");
        Ps2Devices[1].DeviceExists = false;
    }
    //flush in case the ID Comes
    LouKeHalPs2FlushBuffer();
    LouKeHalPs2FlushBuffer();
    
    Command = PS2_DISABLE_SCANNING;
    memset(Return, 0 , 3);
    InitStatus = LouKeHalPs2CommandPs2Device(&Ps2Devices[1], &Command, 1, Return, 1);
    if((InitStatus != STATUS_SUCCESS) || (Return[0] != PS2_DEVICE_ACK)){
        LouPrint("Secondary PS2 Device Did Not Respond\n");
        Ps2Devices[1].DeviceExists = false;
    }

    Command = PS2_IDENTIFY_DEVICE;
    memset(Return, 0 , 3);
    LouKeHalPs2CommandPs2Device(&Ps2Devices[1], &Command, 1, Return, 3);
    if(Return[0] == PS2_DEVICE_ACK){
        Ps2Devices[1].DeviceClass = (PS2_DEVICE_CLASS)(((UINT32)Return[1] << 8) | ((UINT32)Return[2]));
        Ps2BindDeviceToDriver(&Ps2Devices[1]);

    }else{
        LouPrint("Secondary PS2 Device Did Not Respond\n");
        Ps2Devices[1].DeviceExists = false;
    }


    LouPrint("PS2IO.SYS:Ps2InitializeBus() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS Ps2DeInitializeBus(PLOU_BUS BussClass, PLOU_BUS_OBJECT Object){
    LouPrint("PS2IO.SYS:Ps2DeInitializeBus()\n");



    LouPrint("PS2IO.SYS:Ps2DeInitializeBus() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

static LOU_BUS Ps2Bus = {
    .BusName = PS2_CHIPSET_CLASS,
    .BusObjects = &Ps2BusObjects,
    .InitializeBus = Ps2InitializeBus,
    .DeInitializeBus = Ps2DeInitializeBus,
};

LOUDDK_API_ENTRY
NTSTATUS
DriverEntry(
    PDRIVER_OBJECT DrvObject, 
    PUNICODE_STRING RegEntry
){
    LouPrint("PS2IO.SYS:DriverEntry()\n");

    //LouKeCreateBusClass(
    //    &Ps2Bus
    //);

    LouPrint("PS2IO.SYS:DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}