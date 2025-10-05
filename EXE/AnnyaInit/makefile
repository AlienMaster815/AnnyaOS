# Compiler and flags
CC = x86_64-w64-mingw32-gcc
CFLAGS = -shared -m64 -nostdlib -nodefaultlibs -O3

# Paths
LDFLAGS = -L../../UserLibraries
INCLUDES = -I../../include
LIBS = -lLouDll

# Source and target
SRC = AnnyaInit.c
TARGET = AnnyaInit.exe

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS) $(LIBS) $(INCLUDES)

# Clean rule
clean:
	rm -f $(TARGET)
