# Compiler and flags
CC = x86_64-w64-mingw32-g++
CFLAGS = -shared -m64 -nostdlib -nodefaultlibs -Wno-write-strings -O3 -fno-builtin -mabi=ms -mno-red-zone

# Paths
INCLUDES = -I../../../include


# Source and target
SRC = 	Ahci.c \
		AhciLib.c
TARGET = AHCI.SYS

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -L../../../KernelLibraries -llouoskrnl -lLouDDKCrtc $(INCLUDES) -L../../PCI -lPCI -L../Ata -lAta

# Clean rule
clean:
	rm -f $(TARGET)


#TODO List
#TODO:Update Ahci Driver To Support Power Management
#TODO:Add Support For Accelerated Commands and queueing