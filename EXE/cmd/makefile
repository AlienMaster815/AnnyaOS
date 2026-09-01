CPP = x86_64-w64-mingw32-g++
STRIP = x86_64-w64-mingw32-strip
DLLTOOL = x86_64-w64-mingw32-dlltool

# Optimization and Release flags
# -O2: High optimization for execution speed
# -s: Tells the linker to omit all symbol tables and debug sections
RELEASE_FLAGS = -O2 -s

SOURCE = 	cmd.cpp \
			assoc.cpp \
			cd.cpp \
			color.cpp \
			dir.cpp \
			date.cpp

TARGET = cmd.exe

ADVAPI_TARGET = advapi.lib
ADVAPI_SOURCE = advapi.def

SHELL_TARGET = shell.lib
SHELL_SOURCE = shell.def

LIBS = -L../cmd -ladvapi -lshell

$(ADVAPI_TARGET): $(ADVAPI_SOURCE)
	$(DLLTOOL) $(ADVAPI_SOURCE) --output-lib $(ADVAPI_TARGET)

$(SHELL_TARGET): $(SHELL_SOURCE)
	$(DLLTOOL) $(SHELL_SOURCE) --output-lib $(SHELL_TARGET)

all: $(ADVAPI_TARGET) $(SHELL_TARGET)  
	$(CPP) $(RELEASE_FLAGS) -static -static-libgcc -static-libstdc++ -o $(TARGET) $(SOURCE) $(LIBS)
	$(STRIP) --strip-all $(TARGET)

clean:
	rm -f $(TARGET)
	rm -f $(ADVAPI_TARGET)
	rm -f $(SHELL_TARGET)
