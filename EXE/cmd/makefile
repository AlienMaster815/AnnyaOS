CPP = x86_64-w64-mingw32-g++
SOURCE = 	cmd.cpp \
			assoc.cpp \
			cd.cpp \
			color.cpp \
			dir.cpp
TARGET = cmd.exe
DLLTOOL = x86_64-w64-mingw32-dlltool

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
	$(CPP) -o $(TARGET) $(SOURCE) $(LIBS)

clean:
	rm -f $(TARGET)
	rm -f $(ADVAPI_TARGET)
	rm -f $(SHELL_TARGET)