# Compiler and flags
CC = x86_64-w64-mingw32-gcc
CFLAGS = -m64 -O3 -fPIC -fno-stack-protector -nostdlib -nodefaultlibs -fno-builtin
LDFLAGS = \
    -Wl,--entry=AnnyAwmProcessStartup \
    -Wl,--subsystem,console \
    -Wl,--dynamicbase \
    -Wl,--high-entropy-va \
    -L../../UserLibraries
INCLUDES = -I../../include
LIBS = -lLouDll

# Source and target
SRC = awm.c
TARGET = awm.exe

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS) $(LIBS) $(INCLUDES)

# Clean rule
clean:
	rm -f $(TARGET)
