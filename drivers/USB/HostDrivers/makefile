# Compiler and flags
CC = x86_64-w64-mingw32-g++
CFLAGS = -shared -m64 -nostdlib -nodefaultlibs -Wno-write-strings

# Paths
INCLUDES = -I../../../include


# Source and target
SRC1 = Xhci.cpp
TARGET1 = XHCI.SYS

SRC2 = Ohci.cpp \
		OhciPci.cpp \
		OhciMem.cpp
TARGET2 = OHCI.SYS

SRC3 = Ehci.cpp \
		EhciPci.cpp \
		EhciCap.cpp \
		EhciMem.cpp
TARGET3 = EHCI.SYS



# Build rule
all: $(TARGET1) $(TARGET2) $(TARGET3)

$(TARGET1): $(SRC1)
	$(CC) $(CFLAGS) -o $(TARGET1) $(SRC1) -L../../../KernelLibraries -llouoskrnl -lLouDDKCrtc $(INCLUDES)

$(TARGET2): $(SRC2)
	$(CC) $(CFLAGS) -o $(TARGET2) $(SRC2) -L../../../KernelLibraries -llouoskrnl -lLouDDKCrtc $(INCLUDES)

$(TARGET3): $(SRC3)
	$(CC) $(CFLAGS) -o $(TARGET3) $(SRC3) -L../../../KernelLibraries -llouoskrnl -lLouDDKCrtc $(INCLUDES)

# Clean rule
clean:
	rm -f $(TARGET1)
	rm -f $(TARGET2)
	rm -f $(TARGET3)
