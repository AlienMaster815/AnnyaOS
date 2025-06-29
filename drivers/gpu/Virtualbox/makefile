# Compiler and flags
CC = x86_64-w64-mingw32-g++
CFLAGS = -shared -m64 -nostdlib -nodefaultlibs -Wno-write-strings -O3

# Paths
INCLUDES = -I../../../include


# Source and target
SRC = VirtualBoxMain.cpp \
      HgsmiBase.cpp \
      VirtualboxHgsmi.cpp \
      ModeSetting.cpp \
	  VirtualboxInterrupts.cpp \
	  VirtualboxMode.cpp \
	  VirtualboxBufferObjects.cpp \
	  VbvaBase.cpp \
	  VBoxDrsd.cpp

TARGET = VBOXGPU.SYS

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -L../../../KernelLibraries -llouoskrnl -lLouDDKCrtc $(INCLUDES)

# Clean rule
clean:
	rm -f $(TARGET)
