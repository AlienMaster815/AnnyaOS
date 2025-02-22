# Compiler and Assembler
CC = x86_64-w64-mingw32-gcc
NASM = nasm

# Compiler and Assembler Flags
CFLAGS = -shared -nostdlib -nodefaultlibs
ASFLAGS = -f win64  # Ensure 64-bit output for Windows

# Paths
INCLUDES = -I../../../include
LDFLAGS = -L../../../UserLibraries
LIBS = -lLouDll

# Source and Target
SRC = 	NtDll.c \
		Sha.c \
		Alpc.c 

ASM_SRC = 	NtLow.asm 

ASM_OBJ = 	NtLow.o 

TARGET = ntdll.dll

# Default Rule
all: $(TARGET)

# Assemble the ASM file
$(ASM_OBJ): $(ASM_SRC)
	@echo "Assembling $(ASM_SRC)..."
	$(NASM) $(ASFLAGS) -o $(ASM_OBJ) $(ASM_SRC)

# Build Rule (Compiles C files and links with ASM object)
$(TARGET): $(SRC) $(ASM_OBJ)
	@echo "Building $(TARGET)..."
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(ASM_OBJ) $(INCLUDES) $(LDFLAGS) $(LIBS)

# Clean Rule
clean:
	@echo "Cleaning up..."
	rm -f $(TARGET) $(ASM_OBJ)
