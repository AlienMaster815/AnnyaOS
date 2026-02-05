# Ubuntu: mingw-w64 nasm xorriso mtools cmake make gcc git binutils flex meson ninja-build openssl
#git clone https://github.com/limine-bootloader/limine.git --branch=v9.x-binary --depth=1
#cd limine
#make
#sudo make install

#EFI Systems :: grub-efi-amd64

# Target Architecture Supported x86_64 ARM 

#dll targets
#x86_64-w64-mingw32-gcc -shared -o mydll.dll mydll.c -nostdlib -nodefaultlibs 

#lib compile line
#x86_64-w64-mingw32-dlltool --input-def KernelDefs.def --output-lib louoskrnl.lib

#AnnyaExp Compile Line
#x86_64-w64-mingw32-gcc -shared -ffreestanding -nostdlib -nostartfiles -o AnnyaExp.exe AnnyaExp.c -L/path/to/library -lname

#target OS can be WINDOWS or LINUX

#qemu-system-x86_64 -m 8192M -cdrom annya.iso
#VirtualBoxVM --startvm "AnnyaOS" --dbg


INCLUDE = -I. -I include -I include/drivers/acpi -I include/ACPICA

FileStructureTable = Config/System_Config/FileStructure.xml
SystemFileTable = Config/System_Config/SystemFiles.xml

OSBUILDX64 := $(shell cat Config/OSIMGBUILDX64.cfg)

MAKEDIR := $(shell awk -F '[<>]' '/<MainDirectoryStructure>/{print " " $$3 ";"}' $(FileStructureTable) | tr '\n' ' ')
MAKEDIR64 := $(shell awk -F '[<>]' '/<MainDirectoryStructure64>/{print " " $$3 ";"}' $(FileStructureTable) | tr '\n' ' ')

CPY32 := $(shell awk -F '[<>]' '/<FILETOCPY32>/{print " " $$3 ";"}' $(SystemFileTable) | tr '\n' ' ')
CPY64 := $(shell awk -F '[<>]' '/<FILETOCPY64>/{print " " $$3 ";"}' $(SystemFileTable) | tr '\n' ' ')

EXPORT := $(KernelEXPORTS) $(WDFLDRModuleEXPORTS)

CC = x86_64-w64-mingw32-gcc
CP = x86_64-w64-mingw32-g++
LD = x86_64-w64-mingw32-ld --entry=LouOsKrnlStart \
    --subsystem=console \
    --dynamicbase \
    --high-entropy-va \
	--image-base=0x1000000 \
	--section-alignment=0x200000

PELD = x86_64-w64-mingw32-ld

C_COMPILE_FLAGS = -m64
NASM_COMPILE_FLAGS = elf64

RELEASE_PATH = Releases/Annya.iso

#define this flag for porting -fmax-errors=1

#Wextra
CFLAGS = -c -ffreestanding -Werror -Wall -Wno-multichar \
         -fno-omit-frame-pointer -O2 -fno-common -fno-builtin -fno-asynchronous-unwind-tables \
         -fstrict-aliasing $(INCLUDE) 


#Wextra
CPPFLAGS = -c -ffreestanding -Wall  -fno-exceptions -fno-rtti -Werror \
           -fno-use-cxa-atexit -fno-threadsafe-statics -fno-common \
           -fno-builtin -fstrict-aliasing -O2 -I include \
		   -Wno-write-strings -Wno-multichar $(INCLUDE)




kernel_source_files := $(shell find kernel -name *.c)
kernel_object_files := $(patsubst kernel/%.c, build/kernel/%.o, $(kernel_source_files))

driver_cpp_source_files := $(shell find drivers/AGP -name *.cpp)
driver_cpp_source_files += $(shell find drivers/DriverInterrupts -name *.cpp)
driver_cpp_source_files += $(shell find drivers/FileSystems -name *.cpp)
driver_cpp_source_files += $(shell find drivers/gpu/InternalGpuFunctions -name *.cpp)
driver_cpp_source_files += $(shell find drivers/io -name *.cpp)
driver_cpp_source_files += $(shell find drivers/ISA -name *.cpp)
driver_cpp_source_files += $(shell find drivers/pci_systems -name *.cpp)
driver_cpp_source_files += $(shell find drivers/PnP -name *.cpp)
driver_cpp_source_files += $(shell find drivers/processors -name *.cpp)
#driver_cpp_source_files += $(shell find drivers/Serial -name *.cpp)
driver_cpp_source_files += $(shell find drivers/Busses -name *.cpp)
driver_cpp_source_files += $(shell find drivers/storage/InternalStorageDrivers -name *.cpp)
driver_cpp_source_files += $(shell find drivers/USB/UsbInternals -name *.cpp)
#driver_cpp_source_files += $(shell find drivers/virtualization -name *.cpp)
driver_cpp_source_files += $(shell find drivers/Subsystems -name *.cpp)

driver_cpp_object_files := $(patsubst drivers/%.cpp, build/drivers/%.o, $(driver_cpp_source_files))

x86_64_API_cpp_source_files := $(shell find API -name *.cpp)
x86_64_API_cpp_object_files := $(patsubst API/%.cpp, build/x86_64/API/%.o, $(x86_64_API_cpp_source_files))



x86_64_API_cpp_source_files := $(shell find API -name *.cpp)
x86_64_API_cpp_object_filee := $(patsubst API/%.cpp, build/x86_64/API/%.o, $(x86_64_API_cpp_source_files))

x86_64_API_asm_source_files := $(shell find API -name *.asm)
x86_64_API_asm_object_files := $(patsubst API/%.asm, build/x86_64/asm/API/%.o, $(x86_64_API_asm_source_files))

kernel_s_source_files := $(shell find kernel -name *.s)
kernel_asm_object_files := $(patsubst kernel/%.asm, build/x86_64/kernelasm/%.o, $(kernel_asm_source_files))


#x86_64_asm_source_files = boot/x86_64/BOOT.asm
#x86_64_asm_object_files = build/x86_64/boot/boot.o 

kernel_asm_source_files := $(shell find kernel -name *.asm)
kernel_asm_object_files := $(patsubst kernel/%.asm, build/x86_64/kernelasm/%.o, $(kernel_asm_source_files))

x86_64_object_files := $(kernel_object_files) $(x86_64_asm_object_files) $(driver_cpp_object_files) $(x86_64_API_asm_object_files) $(x86_64_API_cpp_object_files) $(kernel_asm_object_files) $(kernel_s_object_files)




$(kernel_object_files): build/kernel/%.o : kernel/%.c
	mkdir -p $(dir $@) && \
	$(CC) $(C_COMPILE_FLAGS) $(CFLAGS) $(patsubst build/kernel/%.o, kernel/%.c, $@) -o $@



$(driver_cpp_object_files): build/drivers/%.o : drivers/%.cpp
	mkdir -p $(dir $@) && \
	$(CP) $(C_COMPILE_FLAGS) $(CPPFLAGS) $(patsubst build/drivers/%.o, drivers/%.cpp, $@) -o $@ -lc
	


$(x86_64_API_cpp_object_files): build/x86_64/API/%.o : API/%.cpp
	mkdir -p $(dir $@) && \
	$(CP) $(C_COMPILE_FLAGS) $(CPPFLAGS) $(patsubst build/x86_64/API/%.o, API/%.cpp, $@) -o $@ -lc

$(x86_64_API_asm_object_files): build/x86_64/asm/API/%.o : API/%.asm
	mkdir -p $(dir $@) && \
	nasm -f $(NASM_COMPILE_FLAGS) $(patsubst build/x86_64/asm/API/%.o, API/%.asm, $@) -o $@


$(x86_64_asm_object_files): $(x86_64_asm_source_files)
	mkdir -p $(dir $@) && \
	nasm -f $(NASM_COMPILE_FLAGS) $(x86_64_asm_source_files) -o $@

$(kernel_asm_object_files): build/x86_64/kernelasm/%.o : kernel/%.asm
	mkdir -p $(dir $@) && \
	nasm -f $(NASM_COMPILE_FLAGS) $(patsubst build/x86_64/kernelasm/%.o, kernel/%.asm, $@) -o $@


$(kernel_s_object_files): build/kernel/%.o : kernel/%.s
	mkdir -p $(dir $@) && \
	$(CC) -c $(C_COMPILE_FLAGS) $(patsubst build/kernel/%.o, kernel/%.s, $@) -o $@



clean:
	rm -r build


lou.exe: $(x86_64_object_files) $(kernel_object_files)
	mkdir -p dist/x86_64
	$(LD) -n -o dist/x86_64/LOUOSKRNL.EXE $(x86_64_object_files)
	rm -r build

release: lou.exe
	mkdir -p release/x86_64 && \
	cp dist/x86_64/LOUOSKRNL.EXE release/x86_64/LOUOSKRNL.exe



KernelModules:

	$(MAKE) -C Registry clean
	$(MAKE) -C Registry all
	./Registry/LKRCompiler Config/System_Config/LOUOSKRNL.LRS Registry/build/LOUOSKRNL.LKR

	$(MAKE) -C KernelLibraries clean
	$(MAKE) -C KernelLibraries all

	$(MAKE) -C drivers clean
	$(MAKE) -C drivers all

	$(MAKE) -C boot/x86_64 clean
	$(MAKE) -C boot/x86_64 all

	$(MAKE) -C EXE/LouLoad clean
	$(MAKE) -C EXE/LouLoad all

UserSpace:
	$(MAKE) -C UserLibraries/LouDll clean
	$(MAKE) -C UserLibraries/LouDll all

	$(MAKE) -C UserLibraries/KernelBase clean
	$(MAKE) -C UserLibraries/KernelBase all

	$(MAKE) -C UserLibraries/Kernel32 clean
	$(MAKE) -C UserLibraries/Kernel32 all

	$(MAKE) -C UserLibraries/ntdll clean
	$(MAKE) -C UserLibraries/ntdll all

	$(MAKE) -C UserLibraries/GDI32 clean
	$(MAKE) -C UserLibraries/GDI32 all

	$(MAKE) -C UserLibraries/User32 clean
	$(MAKE) -C UserLibraries/User32 all
	
	$(MAKE) -C UserLibraries/PreCompiledHeaders/ExeCRTCs clean
	$(MAKE) -C UserLibraries/PreCompiledHeaders/ExeCRTCs all

	$(MAKE) -C EXE/asmss/ clean
	$(MAKE) -C EXE/asmss/ all

	$(MAKE) -C EXE/Explorer clean
	$(MAKE) -C EXE/Explorer all

	$(MAKE) -C EXE/Init clean
	$(MAKE) -C EXE/Init all

	$(MAKE) -C DLL/LouDLLs/User32 clean
	$(MAKE) -C DLL/LouDLLs/User32 all

	$(MAKE) -C DLL/LouDLLs/VCRUNTIME140 clean 
	$(MAKE) -C DLL/LouDLLs/VCRUNTIME140 all 

	$(MAKE) -C DLL/LouDLLs/MSVCRT clean
	$(MAKE) -C DLL/LouDLLs/MSVCRT all

	$(MAKE) -C DLL/LouDLLs/LouDLL clean
	$(MAKE) -C DLL/LouDLLs/LouDLL all

	$(MAKE) -C DLL/3rdParty/zlib -f win32/Makefile.gcc clean
	$(MAKE) -C DLL/3rdParty/zlib -f win32/Makefile.gcc PREFIX=x86_64-w64-mingw32-

	$(MAKE) -C DLL/LouDLLs/Codecs clean
	$(MAKE) -C DLL/LouDLLs/Codecs all

	$(MAKE) -C DLL/LouDLLs/GDI32 clean
	$(MAKE) -C DLL/LouDLLs/GDI32 all

annya.iso: release KernelModules UserSpace
	rm -rf ISO
	
	$(MAKE) -C LouCoff clean
	$(MAKE) -C LouCoff all
	$(MAKE) -C LouCoff modifications

	#Make The System Directories
	$(MAKEDIR)

	#Make 64 Bit System Directories
	$(MAKEDIR64)
	#Copy System Files To The Appropriate Directories
	$(CPY64)
	#Build The Image In One Shabang
	$(OSBUILDX64)


	rm -rf release
	rm -rf ISO

PxeInstall: annya.iso
	cp annya.iso ~/iventoy-1.0.21/iso/annya.iso
#uses 26000 protocol for flush


PublicRelease: annya.iso
	cp annya.iso $(RELEASE_PATH)
	rm -rf annya.iso

cleanall:
	$(MAKE) -C Registry clean
	$(MAKE) -C KernelLibraries clean
	$(MAKE) -C drivers clean
	$(MAKE) -C UserLibraries/KernelBase clean
	$(MAKE) -C UserLibraries/LouDll clean
	$(MAKE) -C UserLibraries/ntdll clean
	$(MAKE) -C UserLibraries/User32 clean
	$(MAKE) -C UserLibraries/Kernel32 clean
	$(MAKE) -C UserLibraries/PreCompiledHeaders/ExeCRTCs clean
	$(MAKE) -C EXE/Explorer clean
	$(MAKE) -C EXE/Init clean
	$(MAKE) -C EXE/LouLoad clean
	$(MAKE) -C DLL/LouDLLs/User32 clean
	$(MAKE) -C DLL/LouDLLs/VCRUNTIME140 clean 
	$(MAKE) -C DLL/LouDLLs/LouDLL clean
	$(MAKE) -C drivers/Networking/PCNET32 clean
	$(MAKE) -C DLL/3rdParty/zlib -f win32/Makefile.gcc clean
	$(MAKE) -C DLL/LouDLLs/MSVCRT clean
	$(MAKE) -C DLL/LouDLLs/Codecs clean
	$(MAKE) -C DLL/LouDLLs/GDI32 clean
	$(MAKE) -C boot/x86_64 clean
	$(MAKE) -C EXE/asmss/ clean
	$(MAKE) -C LouCoff clean
	rm -rf release
	rm -rf ISO
	rm -rd dist
	rm annya.iso