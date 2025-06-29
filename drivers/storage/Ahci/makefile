# Compiler and flags
CC = x86_64-w64-mingw32-g++
CFLAGS = -shared -m64 -nostdlib -nodefaultlibs -Wno-write-strings -O3

# Paths
INCLUDES = -I../../../include


# Source and target
SRC = 	Ahci.cpp \
		Ahci-Avn.cpp \
		Ahci-Vt8251.cpp \
		AhciLib.cpp \
		AhciPhyLayer.cpp \
		AhciPowerManagement.cpp \
		Ahci-P5wdh.cpp

TARGET = AHCI.SYS

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -L../../../KernelLibraries -llouoskrnl -lLouDDKCrtc $(INCLUDES)

# Clean rule
clean:
	rm -f $(TARGET)
