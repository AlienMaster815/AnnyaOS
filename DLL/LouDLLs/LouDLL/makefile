# Compiler and Flags
CC = x86_64-w64-mingw32-gcc
NASM = nasm
CFLAGS = -shared -nostdlib -nodefaultlibs
ASFLAGS = -f win64

# Paths
INCLUDES = -I../../../include

# Source and Target
SRC = LouDll.c \
	Dispatch.c \
	memory.c \
	DrsdUserCore/Drsd.c \
	DrsdUserCore/DrsdDraw.c \
	Nt/Syncronization.c \
	Nt/Allocation.c \
	Nt/Alpc.c \
	Nt/NtDll.c \
	Nt/Sha.c \
	Nt/wcstring.c

ASM_SRC = Lou.asm
ASM_OBJ = Lou.o

TARGET = LouDll.dll

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
