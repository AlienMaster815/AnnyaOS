
loader_asm_object_files := $(shell find Source -name *.asm)
loader_asm_object_files := $(patsubst Source/%.asm, build/kernelasm/%.o, $(loader_asm_object_files))

NASM_COMPILE_FLAGS = elf64

LD = ld

TARGET = LOULOAD.EXE

$(loader_asm_object_files): build/kernelasm/%.o : Source/%.asm
	mkdir -p $(dir $@) && \
	nasm -f $(NASM_COMPILE_FLAGS) $(patsubst build/kernelasm/%.o, Source/%.asm, $@) -o $@


LOADER_OBJECTS := $(loader_asm_object_files)

all: $(LOADER_OBJECTS)
	$(LD) -n -o $(TARGET) -T linker.ld $(LOADER_OBJECTS)
	rm -rf build

clean:
	rm -rf build
	rm -f $(TARGET)