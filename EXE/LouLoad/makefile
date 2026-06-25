CC = x86_64-w64-mingw32-gcc
AS = nasm

CFLAGS = -m64 -fPIC -O3 -fno-stack-protector -nostdlib -nodefaultlibs -fno-builtin \
         -ffreestanding -Werror -Wall -Wno-multichar -fno-omit-frame-pointer \
         -fno-common -fstrict-aliasing -mno-mmx -mno-sse -mno-avx

ASFLAGS = -f win64

LDFLAGS = \
    -Wl,--entry=LouLoadStartLoader \
    -Wl,--subsystem,console \
    -Wl,--dynamicbase \
    -Wl,--high-entropy-va

INCLUDES = -I../../include
LIBS = 

C_SRC = LouLoad.c cstdlib.c memory.c CpuFeatures.c
ASM_SRC = Assembly.asm 

OBJ = $(C_SRC:.c=.o) $(ASM_SRC:.asm=.o)

TARGET = LOULOAD.EXE

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS) $(LIBS) $(INCLUDES)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)
