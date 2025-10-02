#include <LouDDK.h>

typedef struct __attribute__((packed)) _LOU_VFS_FILE{
    size_t                  RemainingBytes;
    size_t                  LBA;
    size_t                  Sectors;
    PVOID                   Sector;
    struct _LOU_VFS_FILE*   NextSectors;
}LOU_VFS_FILE, * PLOU_VFS_FILE;

typedef struct __attribute__((packed)) _LOU_VFS_DIRECTORY_ENTRY{
    struct _LOU_VFS_DIRECTORY_ENTRY*    NextDirectoryEntry;
    struct _LOU_VFS_DIRECTORY_ENTRY*    UpperDirectory;
    size_t                              LBA;
    size_t                              Sectors;
    LOU_VFS_FILE                        File;
    WCHAR                               EntryName[];
}LOU_VFS_DIRECTORY_ENTRY, * PLOU_VFS_DIRECTORY_ENTRY;

static LOU_VFS_DIRECTORY_ENTRY RootDirectory = {
    .NextEntryOffset = 0x00,
    .UpperDirectory = 0x00,
    .File = 0x00,
    .EntryName = L"/",
};

static PLOU_VFS_DIRECTORY_ENTRY GetNextDirectory(
    PLOU_VFS_DIRECTORY_ENTRY    Current,
    LPWSTR                      Next,
    size_t                      PathLength,
    bool                        CreateNew
){
    PLOU_VFS_FILE File = &Current->File;
    PLOU_VFS_DIRECTORY_ENTRY DirectoryFile = (PLOU_VFS_DIRECTORY_ENTRY)File->Sector; 
    //scroll over the entries
    while(1){   
        if(!wcsncmp(Next, DirectoryFile->EntryName, PathLength) && (wcsnlen(DirectoryFile->EntryName) == PathLength)){ //found Directory entry
            return DirectoryFile;
        }
        if(DirectoryFile->NextDirectoryEntry){ //nothing else
            DirectoryFile = DirectoryFile->NextDirectoryEntry;
        }else {
            break;
        }
    }
    if(!CreateNew){
        return 0x00;
    }
    //if not found check for room otherwise allocate more room...

    DirectoryFile->NextDirectoryEntry = LouKeMallocEx(
        GetStructureSize((PLOU_VFS_DIRECTORY_ENTRY)0, EntryName, PathLength + 1),
        GET_ALIGNMENT(LOU_VFS_DIRECTORY_ENTRY),
        KERNEL_GENERIC_MEMORY
    );
    DirectoryFile = DirectoryFile->NextDirectoryEntry
    wcsncpy(DirectoryFile->EntryName, Next, PathLength);
    DirectoryFile->EntryName[PathLength] = L'\0';
    DirectoryFile->UpperDirectory = Current;
    return DirectoryFile;
}

static LPWSTR FileToFilePath(PLOU_VFS_DIRECTORY_ENTRY File)
{
    PLOU_VFS_DIRECTORY_ENTRY Tmp = File;
    size_t PathLength = 0;
    size_t Levels = 0;

    // First pass: calculate length
    while(Tmp) {
        PathLength += wcslen(Tmp->EntryName);
        Levels++;
        Tmp = Tmp->UpperDirectory;
    }

    PathLength += (Levels - 1); 
    LPWSTR Path = LouKeMallocArray(WCHAR, PathLength + 1, KERNEL_GENERIC_MEMORY);
    Path[PathLength] = L'\0';

    Tmp = File;
    size_t Pos = PathLength;
    while(Tmp) {
        size_t EntryLength = wcslen(Tmp->EntryName);
        Pos -= EntryLength;
        wmemcpy(&Path[Pos], Tmp->EntryName, EntryLength);

        if (Tmp->UpperDirectory) {
            Pos--;
            Path[Pos] = L'\\';
        }

        Tmp = Tmp->UpperDirectory;
    }

    return Path;
}

LOUDDK_API_ENTRY
FILE* LouKeFmCreateFile(
    LPWSTR  Path, 
    string  FileName 
){  
    WCHAR Drive[2];
    if(Path[1] == L':'){
        Drive[0] = Path[0];
        Drive[1] = L'\0';
        Path = &Path[2];
        PLOU_VFS_DIRECTORY_ENTRY TmpDir = GetNextDirectory(&RootDirectory, Drive, 1, false);
        if(!TmpDir){
            return 0x00;
        }
        while (*Path) {
            WCHAR* Slash1 = wcschr(Path, L'\\');
            WCHAR* Slash2 = wcschr(Path, L'/');
            WCHAR* Slash = Slash1 && Slash2 ? (Slash1 < Slash2 ? Slash1 : Slash2)
               : (Slash1 ? Slash1 : Slash2);            
            if (!Slash) {
                TmpDir = GetNextDirectory(TmpDir, Path, wcslen(Path), true);
                break;
            } else {
                size_t Foo = Slash - Path;
                TmpDir = GetNextDirectory(TmpDir, Path, Foo, true);
                Path = Slash + 1;
            }
        }
        if(FileName){
            TmpDir = GetNextDirectory(TmpDir, FileName, wcslen(FileName), true);
        }
        return (FILE*)TmpDir;
    }else if(Path[0] == L'/'){
        //root;
        Drive[0] = L'C';
        Drive[1] = L'\0';
        Path++;
        PLOU_VFS_DIRECTORY_ENTRY TmpDir = GetNextDirectory(&RootDirectory, Drive, 1, true);

        while (*Path) {
            WCHAR* Slash1 = wcschr(Path, L'\\');
            WCHAR* Slash2 = wcschr(Path, L'/');
            WCHAR* Slash = Slash1 && Slash2 ? (Slash1 < Slash2 ? Slash1 : Slash2)
                : (Slash1 ? Slash1 : Slash2);
                if (!Slash) {
                TmpDir = GetNextDirectory(TmpDir, Path, wcslen(Path), true);
                break;
            } else {
                size_t Foo = Slash - Path;
                TmpDir = GetNextDirectory(TmpDir, Path, Foo, true);
                Path = Slash + 1;
            }
        }
        if(FileName){
            TmpDir = GetNextDirectory(TmpDir, FileName, wcslen(FileName), true);
        }
        return (FILE*)TmpDir;
    }
    WCHAR* Slash1 = wcschr(Path, L'\\');
    WCHAR* Slash2 = wcschr(Path, L'/');
    WCHAR* Slash = Slash1 && Slash2 ? (Slash1 < Slash2 ? Slash1 : Slash2)
               : (Slash1 ? Slash1 : Slash2);
    if(Slash && !wcsncmp(L"%SYSTEMROOT%", Path, Slash - Path)){
        
                //root;
        Drive[0] = L'C';
        Drive[1] = L'\0';
        Path++;
        PLOU_VFS_DIRECTORY_ENTRY TmpDir = GetNextDirectory(&RootDirectory, Drive, 1, true);

        TmpDir = GetNextDirectory(TmpDir, L"ANNYA", wcslen(L"ANNYA"), true);

        while (*Path) {
            WCHAR* Slash1 = wcschr(Path, L'\\');
            WCHAR* Slash2 = wcschr(Path, L'/');
            WCHAR* Slash = Slash1 && Slash2 ? (Slash1 < Slash2 ? Slash1 : Slash2)
                : (Slash1 ? Slash1 : Slash2);
            if (!Slash) {
                TmpDir = GetNextDirectory(TmpDir, Path, wcslen(Path), true);
                break;
            } else {
                size_t Foo = Slash - Path;
                TmpDir = GetNextDirectory(TmpDir, Path, Foo, true);
                Path = Slash + 1;
            }
        }
        if(FileName){
            TmpDir = GetNextDirectory(TmpDir, FileName, wcslen(FileName), true);
        }
        return (FILE*)TmpDir;
    }else{
        //TODO: Check enviornment variables
    }
    return 0x00;
}

//TODO: add filesystem 
LOUDDK_API_ENTRY
FILE* LouKeFmOpenFile(
    LPWSTR  Path, 
    string  FileName 
){  
    WCHAR Drive[2];
    if(Path[1] == L':'){
        Drive[0] = Path[0];
        Drive[1] = L'\0';
        Path = &Path[2];
        PLOU_VFS_DIRECTORY_ENTRY TmpDir = GetNextDirectory(&RootDirectory, Drive, 1, false);
        if(!TmpDir){
            return 0x00;
        }
        while (*Path) {
            WCHAR* Slash1 = wcschr(Path, L'\\');
            WCHAR* Slash2 = wcschr(Path, L'/');
            WCHAR* Slash = Slash1 && Slash2 ? (Slash1 < Slash2 ? Slash1 : Slash2)
               : (Slash1 ? Slash1 : Slash2);            
            if (!Slash) {
                TmpDir = GetNextDirectory(TmpDir, Path, wcslen(Path), false);
                break;
            } else {
                size_t Foo = Slash - Path;
                TmpDir = GetNextDirectory(TmpDir, Path, Foo, false);
                Path = Slash + 1;
            }
        }
        if(FileName){
            TmpDir = GetNextDirectory(TmpDir, FileName, wcslen(FileName), false);
        }
        return (FILE*)TmpDir;
    }else if(Path[0] == L'/'){
        //root;
        Drive[0] = L'C';
        Drive[1] = L'\0';
        Path++;
        //root references can create the c drive in the boot process
        PLOU_VFS_DIRECTORY_ENTRY TmpDir = GetNextDirectory(&RootDirectory, Drive, 1, true);

        while (*Path) {
            WCHAR* Slash1 = wcschr(Path, L'\\');
            WCHAR* Slash2 = wcschr(Path, L'/');
            WCHAR* Slash = Slash1 && Slash2 ? (Slash1 < Slash2 ? Slash1 : Slash2)
                : (Slash1 ? Slash1 : Slash2);
                if (!Slash) {
                TmpDir = GetNextDirectory(TmpDir, Path, wcslen(Path), false);
                break;
            } else {
                size_t Foo = Slash - Path;
                TmpDir = GetNextDirectory(TmpDir, Path, Foo, false);
                Path = Slash + 1;
            }
        }
        if(FileName){
            TmpDir = GetNextDirectory(TmpDir, FileName, wcslen(FileName), false);
        }
        return (FILE*)TmpDir;
    }
    WCHAR* Slash1 = wcschr(Path, L'\\');
    WCHAR* Slash2 = wcschr(Path, L'/');
    WCHAR* Slash = Slash1 && Slash2 ? (Slash1 < Slash2 ? Slash1 : Slash2)
               : (Slash1 ? Slash1 : Slash2);
    if(Slash && !wcsncmp(L"%SYSTEMROOT%", Path, Slash - Path)){
        
                //root;
        Drive[0] = L'C';
        Drive[1] = L'\0';
        Path++;
        PLOU_VFS_DIRECTORY_ENTRY TmpDir = GetNextDirectory(&RootDirectory, Drive, 1, false);

        TmpDir = GetNextDirectory(TmpDir, L"ANNYA", wcslen(L"ANNYA"), false);

        while (*Path) {
            WCHAR* Slash1 = wcschr(Path, L'\\');
            WCHAR* Slash2 = wcschr(Path, L'/');
            WCHAR* Slash = Slash1 && Slash2 ? (Slash1 < Slash2 ? Slash1 : Slash2)
                : (Slash1 ? Slash1 : Slash2);
            if (!Slash) {
                TmpDir = GetNextDirectory(TmpDir, Path, wcslen(Path), false);
                break;
            } else {
                size_t Foo = Slash - Path;
                TmpDir = GetNextDirectory(TmpDir, Path, Foo, false);
                Path = Slash + 1;
            }
        }
        if(FileName){
            TmpDir = GetNextDirectory(TmpDir, FileName, wcslen(FileName), false);
        }
        return (FILE*)TmpDir;
    }else{
        //TODO: Check enviornment variables
    }
    return 0x00;
}

LOUDDK_API_ENTRY
LOUSTATUS LouKeFmConcatenateFile(
    FILE* File, 
    PVOID Buffer, 
    size_t BufferSize
){
    size_t NewSectorSize = ROUND_UP64(BufferSize, 512);

    while(File->NextSectors){
        File = File->NextSectors;
    }

    if(File->Sector){
        if(File->RemainingBytes >= BufferSize){
            size_t SectorIndex = (File->Sectors * 512) - File->RemainingBytes;
            memcpy((PVOID)(UINTPTR)File->Sector + SectorIndex, Buffer, BufferSize);
            File->RemainingBytes -= BufferSize;
            return STATUS_SUCCESS;
        }else{
            File->NextSectors = LouKeMallocType(LOU_VFS_FILE, KERNEL_GENERIC_MEMORY);
            File = File->NextSectors;
            File->Sector = LouKeMallocEx(NewSectorSize, 512, KERNEL_GENERIC_MEMORY);
            File->Sectors = NewSectorSize / 512;
            File->RemainingBytes = NewSectorSize - BufferSize;
            memcpy(File->Sector, Buffer, BufferSize);
            return STATUS_SUCCESS;
        }   
    }else{
        File->Sector = LouKeMallocEx(NewSectorSize, 512, KERNEL_GENERIC_MEMORY);
        File->Sectors = NewSectorSize / 512;
        File->RemainingBytes = NewSectorSize - BufferSize;
        memcpy(File->Sector, Buffer, BufferSize);
        return STATUS_SUCCESS;
    }
    return STATUS_UNSUCCESSFUL;
}

LOUDDK_API_ENTRY
LOUSTATUS LouKeFmMountObject(
    WCHAR  DriveLetter,
    LPWSTR Directory,
    size_t Sector,
    size_t SectorCount
){
    Drive[2] = {DriveLetter, L'\0'}; //Directory is exspected as /Path/To/Dir
    
    PLOU_VFS_DIRECTORY_ENTRY TmpDir = GetNextDirectory(&RootDirectory, Drive, 1, true);

    while (*Path) {
        WCHAR* Slash1 = wcschr(Path, L'\\');
        WCHAR* Slash2 = wcschr(Path, L'/');
        WCHAR* Slash = Slash1 && Slash2 ? (Slash1 < Slash2 ? Slash1 : Slash2)
            : (Slash1 ? Slash1 : Slash2);
        if (!Slash) {
            TmpDir = GetNextDirectory(TmpDir, Path, wcslen(Path), true);
            break;
        } else {
            size_t Foo = Slash - Path;
            TmpDir = GetNextDirectory(TmpDir, Path, Foo, true);
            Path = Slash + 1;
        }
    }
    TmpDir->LBA = Sector;
    TmpDir->SectorCount = SectorCount;
}

LOUDDK_API_ENTRY
LOUDTATUS LouKeFmMountDrive(
    PLOUSINE_KERNEL_FILESYSTEM LouKeFileSystem
){  
    LouPrint("LouKeFmMountDrive()\n");

    while(1);
    return STATUS_SUCCESS;
}