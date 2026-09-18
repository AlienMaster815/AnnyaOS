# Compiler and Flags
CC = i686-w64-mingw32-gcc
NASM = nasm
CFLAGS = -shared -nostdlib -nodefaultlibs -mstackrealign -fno-builtin
ASFLAGS = -f win32
LIBS = ../../../UserLibraries/LouDll/LouDll.def

# Paths
INCLUDES = -I../../../include

# Source and Target
SRC = LouDll.c
#ASM_SRC = Lou.asm
#ASM_OBJ = Lou.o
TARGET = LouDll.dll

# Rules
all: $(TARGET)

#$(ASM_OBJ): $(ASM_SRC)
#	$(NASM) $(ASFLAGS) -o $@ $<

$(TARGET): $(SRC) $(ASM_OBJ)
	@echo "Building $(TARGET)..."
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(INCLUDES) $(LDFLAGS) $(LIBS) 
#$(ASM_OBJ)

clean:
	@echo "Cleaning up..."
	rm -f $(TARGET) $(ASM_OBJ)
