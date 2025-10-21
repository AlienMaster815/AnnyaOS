# Compiler and flags
CC = x86_64-w64-mingw32-gcc
CFLAGS = -m64 -O3 -fPIC -fno-stack-protector -nostdlib -nodefaultlibs
LDFLAGS = \
    -Wl,--entry=AnnyaSmssNtProcessStartup \
    -Wl,--subsystem,native \
    -Wl,--dynamicbase \
    -Wl,--high-entropy-va \
    -L../../UserLibraries
INCLUDES = -I../../include
LIBS = -lLouDll -lntdll

# Source and target
SRC = asmss.c
TARGET = asmss.exe

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS) $(LIBS) $(INCLUDES)

# Clean rule
clean:
	rm -f $(TARGET)
