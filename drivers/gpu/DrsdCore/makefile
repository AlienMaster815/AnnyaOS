INCLUDES = -I../../../include
TARGET = DRSDCORE.SYS
SRC = DrsdCore.cpp

CC = x86_64-w64-mingw32-g++
CFLAGS = -shared -m64 -nostdlib -nodefaultlibs -Wno-write-strings -O3 -mconsole --entry=DrsdCoreSubsystemEntry

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -L../../../KernelLibraries -llouoskrnl $(INCLUDES)

# Clean rule
clean:
	rm -f $(TARGET)
