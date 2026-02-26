INCLUDES = -I../../../include
TARGET = GDI.SYS
SRC = GdiMain.cpp

CC = x86_64-w64-mingw32-g++
CFLAGS = -shared -m64 -nostdlib -nodefaultlibs -Wno-write-strings -O3 -mconsole --entry=GdiSubsystemEntry

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -L../../../KernelLibraries -llouoskrnl $(INCLUDES)

# Clean rule
clean:
	rm -f $(TARGET)
