COMPILER = x86_64-w64-mingw32-gcc
SOURCE = Explorer.c

  # Compiler and flags
CC = x86_64-w64-mingw32-gcc
CFLAGS = -m64 -mwindows

# Paths
#LDFLAGS = -L../../UserLibraries
#INCLUDES = -I../../include
LIBS = -luser32

# Source and target
SRC = Explorer.c
TARGET = Explorer.exe

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

# Clean rule
clean:
	rm -f $(TARGET)
