CC = x86_64-w64-mingw32-gcc
SRC = msvcrt.c
CFLAGS = -shared -nostdlib -nodefaultlibs -mabi=ms -mno-red-zone -mstackrealign -fno-builtin
INCLUDES = -I../../../include
TARGET = msvcrt.dll
LIBS = -L../../../UserLibraries -lLouDll

all: $(TARGET)

$(TARGET): $(SRC)
	@echo "Building $(TARGET)..."
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(INCLUDES) $(LIBS)

clean:
	@echo "Cleaning up..."
	rm -f $(TARGET)
