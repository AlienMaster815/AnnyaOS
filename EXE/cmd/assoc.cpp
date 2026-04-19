#include "cmd.h"

//im having issues with SetRegKeyValueA so im falling back to Ex
CMD_STATUS SetRegistryValue(HKEY hKeyRoot, LPCSTR lpSubKey, LPCSTR lpValueName, DWORD dwType, LPCVOID lpData, DWORD cbData) {
    HKEY hKey;
    LSTATUS status = RegCreateKeyExA(hKeyRoot, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &hKey, NULL);    
    if (status != ERROR_SUCCESS) {
        return STATUS_UNSUCCESSFUL; 
    }
    status = RegSetValueExA(hKey, lpValueName, 0, dwType, (const BYTE*)lpData, cbData);
    RegCloseKey(hKey);
    if (status != ERROR_SUCCESS) {
        return STATUS_UNSUCCESSFUL;
    }
    return STATUS_OK;
}



static void PrintRegisteredExtensionsFileType() {
    HKEY hRootKey;
    if (RegOpenKeyExA(HKEY_CLASSES_ROOT, NULL, 0, KEY_READ, &hRootKey) != ERROR_SUCCESS) {
        std::cerr << "Could not open registry key." << std::endl;
        return;
    }

    char keyName[256];
    DWORD nameSize;
    DWORD index = 0;

    while (true) {
        nameSize = sizeof(keyName);
        LONG result = RegEnumKeyExA(hRootKey, index, keyName, &nameSize, NULL, NULL, NULL, NULL);

        if (result == ERROR_NO_MORE_ITEMS) break;

        if (result == ERROR_SUCCESS) {
            if (keyName[0] == '.') {
                char fileType[256];
                DWORD fileTypeSize = sizeof(fileType);
                HKEY hSubKey;
                if (RegOpenKeyExA(hRootKey, keyName, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS) {
                    if (RegQueryValueExA(hSubKey, NULL, NULL, NULL, (LPBYTE)fileType, &fileTypeSize) == ERROR_SUCCESS) {
                        std::cout << keyName << "=" << fileType << std::endl;
                    } else {
                        std::cout << keyName << "= (No Type Defined)" << std::endl;
                    }
                    RegCloseKey(hSubKey);
                }
            }
        }
        index++;
    }
    RegCloseKey(hRootKey);
}

static 
CMD_STATUS 
GetRegisteredExtensionsFileType(
    std::string     Extension,
    std::string*    FileTypeOut
){
    if (Extension.empty() || Extension[0] != '.') {
        return STATUS_EINVAL;
    }

    char buffer[256];
    DWORD bufferSize = sizeof(buffer);

    LSTATUS status = RegGetValueA(
        HKEY_CLASSES_ROOT, 
        Extension.c_str(), 
        NULL, 
        RRF_RT_REG_SZ,
        NULL, 
        buffer, 
        &bufferSize
    );
    if (status == ERROR_SUCCESS) {
        if(FileTypeOut){
            *FileTypeOut = std::string(buffer);
        }
        return STATUS_OK;
    } else if (status == ERROR_FILE_NOT_FOUND) {
        return STATUS_EINVAL; 
    }
    return STATUS_EINVAL;
}

static 
CMD_STATUS 
SetRegisteredExtensionsFileType(
    std::string Extension, 
    std::string NewFileType
) {
    if (Extension.empty() || Extension[0] != '.') {
        return STATUS_EINVAL;
    }
    LSTATUS status = SetRegistryValue(
        HKEY_CLASSES_ROOT, 
        Extension.c_str(), 
        NULL, 
        REG_SZ, 
        NewFileType.c_str(), 
        (DWORD)(NewFileType.length() + 1) // Add +1 for the null terminator
    );


    if (status == STATUS_UNSUCCESSFUL) {
        return STATUS_UNSUCCESSFUL;
    }

    if (status == STATUS_OK) {
        SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);
        return STATUS_OK;
    }

    return STATUS_UNSUCCESSFUL;
}

CMD_STATUS 
DispatchAssocCommand(
    COMMAND_PARAMETER Params
){  
    if(Params == "help"){
        std::cout << "assoc [.ext[=[FileType]]]\n";
        std::cout << std::endl;
        std::cout << "assoc displays a file association of each of the file extentions on the computer\n";
        std::cout << "assoc [.ext] displays the file association of the specified extention\n";
        std::cout << "assoc [.ext[=[FileType]]] changes the specified file extentions to the specificed File Type\n";
        std::cout << std::endl;
        return STATUS_OK;
    }   

    std::string FileType = "";
    int DefinitionIndex;
    CMD_STATUS  Status;
    std::string CheckString;
    if(Params == ""){
        PrintRegisteredExtensionsFileType();
        return STATUS_OK;
    }

    CheckString = Params.substr(1);
    
    if(
        (Params.compare(0, 1, ".")) || 
        (CheckString.find('.') != std::string::npos) ||
        (CheckString.find(' ') != std::string::npos)
    ){
        goto _EINVAL_FXT;
    }

    DefinitionIndex = Params.find('=');

    if(DefinitionIndex == std::string::npos){
        Status = GetRegisteredExtensionsFileType(Params, &FileType);
        if(Status == STATUS_OK){
            std::cout << Params << "=" << FileType << std::endl;
        }else{
            std::cout << "ERROR Unable To Get File Type For Extention\n";
        }
        return STATUS_OK;
    }else{
        std::string Ext = Params.substr(0, DefinitionIndex);
        std::string Type = Params.substr(DefinitionIndex + 1); 
        Status = SetRegisteredExtensionsFileType(Ext, Type);
        if(Status == STATUS_EINVAL){
            std::cout << "ERROR Unable To Set File Extention: Invalid Extention Parameter\n";
        }else if(Status == STATUS_UNSUCCESSFUL){
            std::cout << "ERROR Unable To Set File Extention: Access Denied\n";
        }
        return STATUS_OK;
    }

    _EINVAL_FXT:
    std::cout << "ERROR Invalid File Extention\n";
    return STATUS_EINVAL;
}