#include <LouAPI.h>

uint8_t LouKeAcquireSpinLockRaiseToDpc(uint64_t* LockData);

static void* HeadlessGlobals = 0x00;

void* LouKeGetHeadlessGlobals(){
    return HeadlessGlobals;
}

void LouKeHdlspBugCheckProcessing();
void LouKeHdlspAddLogEntry(uint32_t* LogEntry);
void LouKeHdlspProcessDumpCommand(uint32_t DumpCommandData);


LOUSTATUS LouKeHdlspSendBlueScreenInfo(uint32_t* BSODInfo, size_t Sizep){

    return STATUS_SUCCESS;
}

void LouKeHdlspSendStringAtBaud(string Data){

}

uint64_t LouKeHldspGetLine(uint8_t* DataPointer, uint64_t Size){

    return 0;
}

void LouKeHldspPutString(uint32_t* DispatchString){

}



LOUSTATUS LouKeHdlspEnableTerminal(uint8_t TerminalData){

    return STATUS_SUCCESS;
}

uint8_t LouKeInbvPortPollOnly(uint32_t Port){

    return 0;
}

void LouKeInbvPortGetByte(uint32_t Port, uint8_t* Byte){

}

void LouKeHldspPutWideString(uint32_t* PWSTR){
    
}


//If you are looking at this function before you comment
//take a moment to think about the poor bastard that needed
//to first reverse engineer this from the binary in my clean room
//and my poor ass for actually having to write probably the biggest
//piece of shit functions of my 15+ Years of C Programming... 
//P.S. I HATED EVERY MOMENT OF IT...
//  -Tyler Greneir
LOUSTATUS LouKeHdlspDispatch(    
    uint32_t DispatchCommand, 
    uint32_t* CommandData, 
    uint64_t CommandSize, 
    uint8_t* HeadlessLocal, 
    uint64_t* size
){
    LOUSTATUS Result = STATUS_SUCCESS;
    LOUSTATUS Result1 = STATUS_SUCCESS;
    LOUSTATUS Result2 = STATUS_SUCCESS;

    LouKIRQL Irql;
    size_t s = (size_t)*size;

    if((DispatchCommand == 0x11) || (DispatchCommand == 0x0E)){
        _LABEL_PROCESS_COMAND:
        if(DispatchCommand == 0x0E){
            *(uint32_t*)((string)HeadlessGlobals + 0x30) = ((*(uint32_t*)((string)HeadlessGlobals + 0x30) | 0x02) & 0xFFFFFFBF);
            Result = Result1;
        }
        else if(DispatchCommand == 0x0F){
            
            if((1 & ((uint8_t)*(uint32_t*)(HeadlessGlobals + 0x30))) != 0x00){
                LouKeHdlspBugCheckProcessing();
            }
            Result = Result1;
        }
        else if(DispatchCommand == 0x10){
            if((HeadlessLocal != 0) && (size != 0) && (*(uint64_t*)size >= 0x20)){
                *(uint32_t*)HeadlessLocal = 0x01;
                HeadlessLocal[8] = 0x01;
                HeadlessLocal[9] = (((uint8_t)(*(uint32_t*)((uint8_t*)HeadlessGlobals + 0x30) >> 3)) & 0x01);
                *(uint32_t*)(HeadlessLocal + 0x18) = *(uint32_t*)((string)HeadlessGlobals + 0x34);
                uint32_t TmpHG32 = *(uint32_t*)((uint8_t*)HeadlessGlobals + 0x30);
                uint64_t TmpHG64 = ((uint64_t)(TmpHG32 >> 0x09) & 0x07);
                if((TmpHG64 >= 0x01) || ((1 & ((uint8_t)(TmpHG32 >> 3))) != 0)){
                    *(uint32_t*)(HeadlessLocal + 0x0C) = TmpHG64;
                    *(uint64_t*)(HeadlessLocal + 0x10) = *(uint64_t*)((uint8_t*)HeadlessGlobals + 0x40);
                }
                else {
                    *(uint32_t*)(HeadlessLocal + 0x0C) = 0;
                    *(uint64_t*)(HeadlessLocal + 0x10) = 0;
                }
                TmpHG64 = *(uint8_t*)((uint8_t*)HeadlessGlobals + 54);
                HeadlessLocal[0x1C]= TmpHG64;
                goto _LABEL_GLOBAL_CLEANUP;
            }
        _LABEL_HDLSP_INVALID:
            Result1 = (LOUSTATUS)-0x3ffffff3;
        _LABEL_GLOBAL_CLEANUP:
            *(uint32_t*)((char*)HeadlessGlobals + 0x30) &= 0xFFFFFFBF;
            Result = Result1;
        }
        else if(DispatchCommand == 0x11){
            if(CommandData != 0){
                LouKeHdlspAddLogEntry(CommandData);
            }
            else {
                Result1 = (LOUSTATUS)-0x3ffffff3;
            }
            Result = Result1;
        }
        else {
            if(DispatchCommand == 0x12){
                if((CommandData == 0) || (CommandSize != 1)){
                    goto _LABEL_HDLSP_INVALID;
                }
                uint32_t Command = *(uint8_t*)CommandData;
                LouKeHdlspProcessDumpCommand(Command);
                goto _LABEL_GLOBAL_CLEANUP;
            }
        _LABEL_HDLSP_INVALID2:
            Result1 = (LOUSTATUS)-0x3ffffff3;
            
            if(
            (DispatchCommand != 0x11) && 
            (DispatchCommand != 0x0E) && 
            (DispatchCommand != 0x14) && 
            (DispatchCommand != 0x0F)
            ){
                goto _LABEL_GLOBAL_CLEANUP;   
            }
            Result = Result1;
        }
    }
    else if(DispatchCommand == 0x14){
        _LABEL_140B71830:
        if((((uint8_t)*(uint32_t*)(HeadlessGlobals + 0x30))& 0x03) != 3){
            Result = Result1;
        }
        else if((DispatchCommand == 0) || (CommandSize != 4)){
            Result = STATUS_INVALID_PARAMETER;
        }
        else{
            LouKeHdlspSendBlueScreenInfo(CommandData, CommandSize);
            LouKeHdlspSendStringAtBaud("\n\r!SAC>");
            Result = Result1;
        }
    }
    else {
        if(DispatchCommand == 0x0F){
            goto _LABEL_PROCESS_COMAND;
        }
            
        uint8_t DpcLockOldIrql = 0x00;
        uint64_t* TmpHeadlessGlobal = (uint64_t*)HeadlessGlobals;
        if((((uint8_t)TmpHeadlessGlobal[6]) & 2) != 0){
            DpcLockOldIrql = 0xFF;
        }
        else {
            DpcLockOldIrql = LouKeAcquireSpinLockRaiseToDpc(TmpHeadlessGlobal);
        }
        uint32_t Checksum = (uint32_t)TmpHeadlessGlobal[6];
        if((Checksum & 0x40) == 0){
            TmpHeadlessGlobal[6] = (Checksum | 0x40);
            if(DpcLockOldIrql != 0xFF){
                Irql = (LouKIRQL)DpcLockOldIrql;
                LouKeReleaseSpinLock((spinlock_t*)TmpHeadlessGlobal, &Irql);
            }

            if(DispatchCommand < 0x0D){
                uint64_t Checksum;
                if(DispatchCommand == 0x0D){
                    if((HeadlessGlobals == 0) || (size == 0)){
                        goto _LABEL_HDLSP_INVALID;
                    }
                    if(s < 2){
                        goto _LABEL_HDLSP_INVALID;
                    }
                    if((1 & ((uint8_t)*(uint32_t*)(HeadlessGlobals + 0x30))) == 0){
                        _LABEL_HDLSP_GET_LINE_CHECK0_SKIP:
                            Checksum = 0;
                            goto _LABEL_HDLSP_SKIP_GET_LINE;
                    }
                    Checksum = LouKeHldspGetLine(&HeadlessLocal[1], (s - 1)); 
                    _LABEL_HDLSP_SKIP_GET_LINE:
                    *(uint8_t*)HeadlessLocal = Checksum;
                    goto _LABEL_GLOBAL_CLEANUP;
                }

                string CommandString = 0x00;

                if(DispatchCommand <= 7){
                    if(DispatchCommand == 7){
                        goto _LABEL_140B71422;
                    }
                    if(DispatchCommand == 1){
                        if((CommandData == 0) || (CommandSize != 1)){
                            goto _LABEL_HDLSP_INVALID;
                        }

                        Result2 = LouKeHdlspEnableTerminal(*(uint8_t*)CommandData);
                        goto _LABEL_R2CLEANUP;

                    }

                    if(DispatchCommand == 2){
                        if((HeadlessLocal == 0) || (size == 0)){
                            goto _LABEL_HDLSP_INVALID;
                        }
                        char Rdi1 = 1;
                        if(*(uint64_t*)size != 1){
                            goto _LABEL_HDLSP_INVALID;
                        }

                        if((1 & ((uint8_t)*(uint32_t*)(HeadlessGlobals + 0x30))) == 0){
                            _LABEL_HEADLESS_GLOBAL_CLEANUP:
                                *(uint8_t*)HeadlessLocal = 0;
                                goto _LABEL_GLOBAL_CLEANUP;
                        }
                        if(LouKeHldspGetLine((uint8_t*)CommandString, 0x50) != 0){
                            if((strcmp(CommandString, "reboot") != 0) && (strcmp(CommandString, "shutdown") != 0)){
                                Rdi1 = 0;
                            }
                            *(uint8_t*)HeadlessLocal = Rdi1;
                        }

                        goto _LABEL_GLOBAL_CLEANUP;
                    }

                    if(DispatchCommand == 3){
                        if(CommandData == 0){
                            goto _LABEL_HDLSP_INVALID;
                        }
                        if((1 & ((uint8_t)*(uint32_t*)(HeadlessGlobals + 0x30))) != 0){
                            LouKeHldspPutString(CommandData);
                        }

                        goto _LABEL_GLOBAL_CLEANUP;
                    }

                    if(((DispatchCommand != 4) && (DispatchCommand != 5)) || (DispatchCommand != 6)){
                        goto _LABEL_HDLSP_INVALID2;
                    }
                }
                else if((DispatchCommand != 8) && (DispatchCommand != 9) && (DispatchCommand != 0x0A)){
                    if(DispatchCommand == 0x0B){
                        if((HeadlessLocal == 0) || (size == 0) || (*size != 1)){
                            goto _LABEL_HDLSP_INVALID;
                        }

                        if((1 & *(uint32_t*)((uint8_t*)HeadlessGlobals + 0x30)) == 0){
                            goto _LABEL_HDLSP_GET_LINE_CHECK0_SKIP;
                        }

                        Checksum = LouKeInbvPortPollOnly(*(uint32_t*)((uint8_t*)HeadlessGlobals + 0x38));
                        goto _LABEL_HDLSP_SKIP_GET_LINE;
                    }

                    if(DispatchCommand != 0x0C){
                        goto _LABEL_HDLSP_INVALID2;
                    }

                    if((HeadlessGlobals == 0) || (size == 0)){
                        goto _LABEL_HDLSP_INVALID;
                    }
                    size_t LocalSize = ((uint64_t)DispatchCommand - 0x0B);

                    if(*(uint64_t*)size != LocalSize){
                        goto _LABEL_HDLSP_INVALID;
                    }

                    if((LocalSize * ((uint8_t)*(uint32_t*)((uint8_t*)HeadlessGlobals + 0x30))) == 0){
                        goto _LABEL_HEADLESS_GLOBAL_CLEANUP;
                    }
                    if(LouKeInbvPortPollOnly(*(uint32_t*)(HeadlessGlobals + 0x38)) == 0){
                        goto _LABEL_HEADLESS_GLOBAL_CLEANUP;
                    }

                    LouKeInbvPortGetByte(*(uint32_t*)(HeadlessGlobals + 0x38), HeadlessLocal);
                    goto _LABEL_GLOBAL_CLEANUP;
                }

            _LABEL_140B71422:

                if((1 & ((uint8_t)*(uint32_t*)(HeadlessGlobals + 0x30))) == 0){
                    goto _LABEL_GLOBAL_CLEANUP;
                }

                string Format = (string)GetStackVariable(0x98);

                if(DispatchCommand == 4){
                    Format = "\x1b|2J";
                }
                else if(DispatchCommand == 5){
                    Format = "\x1b|0J";
                }
                else if(DispatchCommand == 6){
                    Format = "\x1b|0K";
                }
                else if (DispatchCommand == 7){
                    Format = "\x1b|0m";
                }
                else if (DispatchCommand == 8){
                    Format = "\x1b|7m";
                }
                else{
                    //uint32_t Checksum;
                    if(DispatchCommand == 9){
                        if((CommandData == 0) || (CommandSize != 8)){
                            goto _LABEL_HDLSP_INVALID;
                        }
                        //Checksum = *(uint32_t*)CommandData;
                        Format = "\x1b[%d;%dm";
                    }
                    else{
                        if((DispatchCommand != 0x0A) || (CommandData == 0) || (CommandSize != 8)){
                            goto _LABEL_HDLSP_INVALID;
                        
                        }
                        Format = "\x1b[%d;%dH";
                        //Checksum = (*(uint32_t*)CommandData + 1);
                    }

                    //uint32_t Checksum2 = Checksum;
                    sprintf_s(CommandString, 0x50, Format);
                }
                LouKeHdlspSendStringAtBaud(Format);
                goto _LABEL_GLOBAL_CLEANUP;
            }
            else if(DispatchCommand > 0x13){

                if(DispatchCommand == 0x14){
                    goto _LABEL_140B71830;
                }

                if(DispatchCommand == 0x15){
                    if((HeadlessLocal == 0) || (*size < 0x18)){
                        goto _LABEL_HDLSP_INVALID;
                    }

                    *(unsigned __int128*)HeadlessLocal = *(unsigned __int128*)(HeadlessGlobals + 0x64);
                    goto _LABEL_GLOBAL_CLEANUP;
                }
                if(DispatchCommand == 0x16){
                    if((CommandData == 0) || (CommandSize == 0)){
                        goto _LABEL_HDLSP_INVALID;
                    }   
                    if ((1 & ((int8_t)*(uint32_t*)(HeadlessGlobals + 0x30))) != 0){
                        uint32_t i = 0;
                        if(CommandSize != 0){
                            string Tmp = 0x00;
                            do{
                                Tmp = *(string*)((uintptr_t)i + (uintptr_t)CommandData);
                                LouKeInbvPortGetByte(*(uint32_t*)(HeadlessGlobals + 0x38), (uint8_t*)Tmp);
                                i++;
                            }while(i < CommandSize);
                        }
                    }
                
                    goto _LABEL_GLOBAL_CLEANUP;

                }
                if(DispatchCommand == 0x17){
                    if(CommandData == 0){
                        goto _LABEL_HDLSP_INVALID;
                    }
                    if((1 & ((uint8_t)*(uint32_t*)(HeadlessGlobals + 0x30))) != 0){
                        LouKeHldspPutWideString(CommandData);
                    }
                    goto _LABEL_GLOBAL_CLEANUP;
                }
                if(DispatchCommand != 0x18){
                    goto _LABEL_HDLSP_INVALID2;
                }
                
                if((HeadlessLocal == 0) || (size == 0) || (*size < 0x0C)){
                    goto _LABEL_HDLSP_INVALID;
                }

                *(uint64_t*)HeadlessLocal = *(uint64_t*)((uint8_t*)HeadlessGlobals + 0x76);
                *(uint32_t*)(HeadlessLocal + 8) = *(uint32_t*)((uint8_t*)HeadlessGlobals + 0x7E);
                goto _LABEL_GLOBAL_CLEANUP;
            }

            if(DispatchCommand != 0x13){
                goto _LABEL_PROCESS_COMAND;
            }
            if(CommandData != 0){
                Result2 = LouKeHdlspSendBlueScreenInfo(CommandData, CommandSize);
                _LABEL_R2CLEANUP:
                    Result1 = Result2;
                    goto _LABEL_GLOBAL_CLEANUP;
            }
            Result = STATUS_INVALID_PARAMETER;
        }   
        else{
            if(DpcLockOldIrql != 0xFF){
                Irql = (LouKIRQL)DpcLockOldIrql;
                LouKeReleaseSpinLock(HeadlessGlobals, &Irql);
            }
            Result = STATUS_UNSUCCESSFUL;
        }
    }



    return Result;
}