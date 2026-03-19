CC = x86_64-w64-mingw32-gcc
CFLAGS = -m64 -O3 -fPIC -fno-stack-protector -nostdlib -nodefaultlibs -fno-builtin
LDFLAGS = \
    -Wl,--entry=InitMain \
    -Wl,--subsystem,console \
    -Wl,--dynamicbase \
    -Wl,--high-entropy-va \
    -L../../UserLibraries
INCLUDES = -I../../include
LIBS = -lLouDll

# Source and target
SRC = Init.c
TARGET = Init.exe

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS) $(LIBS) $(INCLUDES)

# Clean rule
clean:
	rm -f $(TARGET)
