CC = x86_64-w64-mingw32-gcc
CFLAGS = -m64 -fPIC -fno-stack-protector -nostdlib -nodefaultlibs -fno-builtin -ffreestanding -Werror -Wall -Wno-multichar \
         -fno-omit-frame-pointer -fno-common -fstrict-aliasing -mno-mmx -mno-sse -mno-avx
LDFLAGS = \
    -Wl,--entry=LouLoadStartLoader \
    -Wl,--subsystem,console \
    -Wl,--dynamicbase \
    -Wl,--high-entropy-va
INCLUDES = -I../../include
LIBS =

# Source and target
SRC = LouLoad.c
TARGET = LOULOAD.EXE

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS) $(LIBS) $(INCLUDES)

# Clean rule
clean:
	rm -f $(TARGET)
