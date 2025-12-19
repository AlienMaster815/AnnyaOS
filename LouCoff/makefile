# --- Configuration ---
CC = gcc
CFLAGS = -Wall -Wextra -O2 -IInclude -IModifier
LDFLAGS = 
TARGET = LPEModifier
SRC = $(shell find Modifier -name "*.c")
OBJ	= $(patsubst %.c, build/%.o, $(SRC))

# --- Build Rules ---
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# --- Cleanup ---
clean:
	rm -rf build $(TARGET)

modifications:
	./LPEModifier -E../drivers/storage/Ahci/AHCI.SYS -PKernel
	./LPEModifier -E../drivers/gpu/Virtualbox/VBOXGPU.SYS -PKernel
	./LPEModifier -E../drivers/Serial/Ps2Bus/PS2IO.SYS -PKernel
	./LPEModifier -E../drivers/Input/Mouse/Ps2Mouse/PS2MOUSE.SYS -PKernel
	./LPEModifier -E../drivers/Input/Keyboard/Mf2Ps2/MF2KBD.SYS -PKernel
	./LPEModifier -E../drivers/Audio/SoundBlaster/SBMOD.SYS -PKernel
	./LPEModifier -E../drivers/DMA/8237A/8237A.SYS -PKernel
	./LPEModifier -E../DLL/LouDLLs/LouDLL/LouDll.dll -PUser 
#-S../DLL/LouDLLs/LouDLL/LOUDLL.KSF