
loader_asm_source_files := $(shell find ../LouLoad -name *.asm)
loader_asm_object_files := $(patsubst ../LouLoad/%.asm, build/loaderasm/%.o, $(loader_asm_source_files))

NASM_COMPILE_FLAGS = elf64

LD = ld

$(loader_asm_object_files): $(loader_asm_source_files)
	mkdir -p $(dir $@) && \
	nasm -f $(NASM_COMPILE_FLAGS) $(loader_asm_source_files) -o $@


LOADER_OBJECTS = $(loader_asm_object_files)
TARGET = LOULOAD.EXE

all: $(LOADER_OBJECTS)
	$(LD) -n -o LOULOAD.EXE -T linker.ld $(LOADER_OBJECTS)
	rm -rf build

clean:
	rm -rf build
	rm -f $(TARGET)