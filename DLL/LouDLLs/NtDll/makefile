# Compiler and Assembler
CC = x86_64-w64-mingw32-gcc
NASM = nasm

# Flags
CFLAGS = -shared -nostdlib -nodefaultlibs -O3
ASFLAGS = -f win64

# Paths
INCLUDES = -I../../../include
LDFLAGS = -L../../../UserLibraries
LIBS = -lLouDll -lmingw32

# Sources
SRC = 	NtDll.c \
		Csr.c \
		Sha.c \
		Alpc.c \
		Syncronization.c \
		Allocation.c

ASM_SRC = ntdll.asm
ASM_OBJ = ntdll.o

TARGET = ntdll.dll

# Rules
all: $(TARGET)

$(ASM_OBJ): $(ASM_SRC)
	$(NASM) $(ASFLAGS) -o $@ $<

$(TARGET): $(SRC) $(ASM_OBJ)
	@echo "Building $(TARGET)..."
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(ASM_OBJ) $(INCLUDES) $(LDFLAGS) $(LIBS)

clean:
	@echo "Cleaning up..."
	rm -f $(TARGET) $(ASM_OBJ)
