# Compiler and Flags
CC = x86_64-w64-mingw32-gcc
CFLAGS = -shared -nostdlib -nodefaultlibs -O3

# Paths
INCLUDES = -I../../../include
LDFLAGS = -L../../../UserLibraries
LIBS = -lLouDll -lntdll -lKERNEL32

# Source and Target
SRC = User32.c \
		Awm.c

TARGET = user32.dll

# Default Rule
all: $(TARGET)

# Build Rule
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(INCLUDES) $(LDFLAGS) $(LIBS)

# Clean Rule
clean:
	rm -f $(TARGET)
