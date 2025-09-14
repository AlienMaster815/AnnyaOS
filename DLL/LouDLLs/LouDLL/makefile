# Compiler and Flags
CC      = x86_64-w64-mingw32-gcc
CFLAGS  = -shared -nostdlib -nodefaultlibs
AS      = nasm
ASFLAGS = -f win64

# Paths
INCLUDES = -I../../../include

# Source and Target
C_SRC = LouDll.c \
        Dispatch.c \
        memory.c \
        DrsdUserCore/Drsd.c \
        DrsdUserCore/DrsdDraw.c \
        Allocation.c \
        Alpc.c \
        Csr.c \
        NtDll.c \
        Sha.c \
        Syncronization.c \
        WcString.c

ASM_SRC = ntdll.asm

C_OBJ   = $(C_SRC:.c=.o)
ASM_OBJ = $(ASM_SRC:.asm=.o)
OBJ     = $(C_OBJ) $(ASM_OBJ)

TARGET = LouDll.dll

# Default Rule
all: $(TARGET)

# Link Rule
$(TARGET): $(OBJ)
	@echo "Linking $(TARGET)..."
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(INCLUDES)

# Compile C sources
%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

# Assemble ASM sources
%.o: %.asm
	@echo "Assembling $<..."
	$(AS) $(ASFLAGS) $< -o $@

# Clean Rule
clean:
	@echo "Cleaning up..."
	rm -f $(TARGET) $(OBJ)
