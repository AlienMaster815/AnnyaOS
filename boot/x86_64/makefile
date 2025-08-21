
ASM := nasm
ASM_FILES := trampoline.asm
TARGET := SmpBoot.bin

all:
	$(ASM) -f bin $(ASM_FILES) -o $(TARGET)


clean:
	rm -f $(TARGET)