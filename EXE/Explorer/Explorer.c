//Copyright GPL-2 Tyler Grenier (2025 - 2026)

#include <Annya.h> 

LRESULT NewWindowProc(HWND WindowHandle, UINT Message, WPARAM WordParam, LPARAM LongParam);

LOUSTATUS AnnyaExplorerProcessStartup(HANDLE Peb){
    
    LouPrint("Hello Annya OS Explorer\n");
    
    WINDOW_CLASS_EX_W NewWindowClass = {0};

    NewWindowClass.WindowProcedure = NewWindowProc;
    NewWindowClass.ClassName = L"MyNewClass";

    RegisterClassExW(&NewWindowClass);

    LouPrint("Annya OS Explorer Successfully Initialized\n");
    while(1);
    return 0x00;
}

LRESULT NewWindowProc(HWND WindowHandle, UINT Message, WPARAM WordParam, LPARAM LongParam){


    return 0;
}