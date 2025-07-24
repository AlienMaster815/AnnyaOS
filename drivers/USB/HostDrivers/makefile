# Compiler and flags
CC = x86_64-w64-mingw32-g++
CFLAGS = -shared -m64 -nostdlib -nodefaultlibs -Wno-write-strings -O3

# Paths
INCLUDES = -I../../../include


# Source and target
XHCI_SRC = 	XHCI.cpp

XHCI_TARGET = XHCI.SYS

# Build rule
xhci: $(XHCI_TARGET)

$(XHCI_TARGET): $(XHCI_SRC)
	$(CC) $(CFLAGS) -o $(XHCI_TARGET) $(XHCI_SRC) -L../../../KernelLibraries -llouoskrnl -lLouDDKCrtc $(INCLUDES)

# Clean rule
clean_xhci:
	rm -f $(XHCI_TARGET)
