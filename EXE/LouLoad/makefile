loader_asm_source_files := $(shell find ../LouLoad -name "*.asm")
loader_asm_object_files := $(patsubst ../LouLoad/%.asm, build/loaderasm/%.o, $(loader_asm_source_files))

loader_source_files := $(shell find ../LouLoad -name "*.c")
loader_object_files := $(patsubst ../LouLoad/%.c, build/LoaderC/%.o, $(loader_source_files))

INCLUDE = -I ../../include -I ../LouLoad

CFLAGS = -m64 -c -ffreestanding -Werror -Wall -Wno-multichar \
         -fno-omit-frame-pointer -fno-common -fno-builtin -fno-asynchronous-unwind-tables \
         -fstrict-aliasing $(INCLUDE)

NASM_COMPILE_FLAGS = elf64

LD = ld
CC = x86_64-w64-mingw32-gcc

build/loaderasm/%.o: ../LouLoad/%.asm
	mkdir -p $(dir $@)
	nasm -f $(NASM_COMPILE_FLAGS) $< -o $@

build/LoaderC/%.o: ../LouLoad/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

LOADER_OBJECTS := $(loader_asm_object_files) $(loader_object_files)
TARGET = LOULOAD.EXE

all: $(LOADER_OBJECTS)
	$(LD) -n -o LOULOAD.bin -T linker.ld $(LOADER_OBJECTS)
	cp LOULOAD.bin $(TARGET)
	rm -rf build

clean:
	rm -rf build
	rm -f LOULOAD.bin
	rm -f $(TARGET)
