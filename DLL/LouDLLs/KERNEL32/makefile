# Compiler and Flags
CC = x86_64-w64-mingw32-gcc
CFLAGS = -shared -nostdlib -nodefaultlibs 

#TODOT: kernel 32 has a bug on O3 check it out later

# Paths
INCLUDES = -I../../../include
LDFLAGS = -L../../../UserLibraries
LIBS = -lLouDll -lkernelbase -lntdll

# Source and Target
SRC = Kernel32.c
TARGET = KERNEL32.dll

# Default Rule
all: $(TARGET)

# Build Rule
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(INCLUDES) $(LDFLAGS) $(LIBS)


# Clean Rule
clean:
	@echo "Cleaning up..."
	rm -f $(TARGET)
