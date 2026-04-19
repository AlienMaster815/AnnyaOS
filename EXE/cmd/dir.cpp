#include "cmd.h"
 
#define DS_FLAG_ATTRIBUTE                   (1UL << 0)  //A
#define DS_FLAG_BARE_FORMAT                 (1UL << 1)  //B
#define DS_FLAG_THOUSAND_SEPERATOR          (1UL << 2)  //C
#define DS_FLAG_SORT_COLUMN                 (1UL << 3)  //D
#define DS_FLAG_LOWERCASE_OUTPUT            (1UL << 4)  //L
#define DS_FLAG_NEW_LONG_LIST               (1UL << 5)  //N
#define DS_FLAG_SORT_ORDER                  (1UL << 6)  //O
#define DS_FLAG_PAUSE                       (1UL << 7)  //P
#define DS_FLAG_DISPLAY_OWNER               (1UL << 8)  //Q
#define DS_FLAG_DISPLAY_ALT_DATA            (1UL << 9)  //R
#define DS_FLAG_DISPLAY_FILE_RECURSIVE      (1UL << 10) //S
#define DS_FLAG_TIME_FIELD                  (1UL << 11) //T
#define DS_FLAF_WIDE_LIST_FORMAT            (1UL << 12) //W
#define DS_FLAG_DISPLAY_SHORT_NAMES         (1UL << 13) //X
#define DS_FLAG_DISPLAY_4DIGIT_YEAR         (2UL << 14) //4          


#define DSEXT_FLAG_ATTR_DIRECTORIES         (1UL << 0) //D
#define DSEXT_FLAG_ATTR_NDIRECTORIES        (1UL << 1) //-D
#define DSEXT_FLAG_ATTR_READ_ONLY           (1UL << 2) //R
#define DSEXT_FLAG_ATTR_NREAD_ONLY          (1UL << 3) //-R
#define DSEXT_FLAG_ATTR_HIDDEN              (1UL << 4) //H
#define DSEXT_FLAG_ATTR_NHIDDEN             (1UL << 5) //-H
#define DSEXT_FLAG_ATTR_ARCHIVE             (1UL << 6) //A
#define DSEXT_FLAG_ATTR_NARCHIVE            (1UL << 7) //-A
#define DSEXT_FLAG_ATTR_SYSTEM              (1UL << 8) //S
#define DSEXT_FLAG_ATTR_NSYSTEM             (1UL << 9) //-S
#define DSEXT_FLAG_ATTR_INDEXED             (1UL << 10) //I
#define DSEXT_FLAG_ATTR_NINDEXED            (1UL << 11) //-I
#define DSEXT_FLAG_ATTR_REPARSE             (1UL << 12) //L
#define DSEXT_FLAG_ATTR_NREPARSE            (1UL << 13) //-L
#define DSEXT_ATTRIUTE_FLAGS                (0x00003FFF)

#define DSEXT_FLAG_SO_NAME                  (1ULL << 14) //N
#define DSEXT_FLAG_SO_NNAME                 (1ULL << 15) //-N
#define DSEXT_FLAG_SO_SIZE                  (1ULL << 16) //S
#define DSEXT_FLAG_SO_NSIZE                 (1ULL << 17) //-S
#define DSEXT_FLAG_SO_EXT                   (1ULL << 18) //E
#define DSEXT_FLAG_SO_NEXT                  (1ULL << 19) //-E
#define DSEXT_FLAG_SO_DATE                  (1ULL << 20) //D
#define DSEXT_FLAG_SO_NDATE                 (1ULL << 21) //-D
#define DSEXT_FLAG_SO_GROUP                 (1ULL << 22) //G         
#define DSEXT_FLAG_SO_NGROUP                (1ULL << 23) //-G         
#define DSEXT_SORT_ORDER_FLAGS              (0x00FFC000)

#define DSEXT_FLAG_TF_CREATION              (1 << 24)
#define DSEXT_FLAG_TF_LAST_ACCESS           (1 << 25)
#define DSEXT_FLAG_TF_LAST_WRITE            (1 << 26)
#define DSEXT_TIME_FIELD_FLAGS              (0x07000000)

#define DSEXT_SET_ATTRIBUTE_FLAGS(Flags, Attribs)       ((Flags & ~(DSEXT_ATTRIUTE_FLAGS))   | (Attribs & DSEXT_ATTRIUTE_FLAGS))
#define DSEXT_SET_SORT_ORDER_FLAGS(Flags, Attribs)      ((Flags & ~(DSEXT_SORT_ORDER_FLAGS)) | (Attribs & DSEXT_SORT_ORDER_FLAGS))
#define DSEXT_SET_TIME_FIELD_FLAGS(Flags, Attribs)      ((Flags & ~(DSEXT_TIME_FIELD_FLAGS)) | (Attribs & DSEXT_TIME_FIELD_FLAGS))    


struct FileEntry {
    WIN32_FIND_DATAA data;
    std::string name;
    std::string ext;
};

static CMD_STATUS PrintDirectory(std::string FullSystemPath, ULONG Flags, ULONG ExtendedFlags) {
    std::vector<FileEntry> entries;
    WIN32_FIND_DATAA FindData;
    
    std::string SearchPath = FullSystemPath;
    if (SearchPath.back() != '\\') SearchPath += '\\';
    
    HANDLE FindHandle = FindFirstFileA((SearchPath + "*").c_str(), &FindData);
    if (FindHandle == INVALID_HANDLE_VALUE) return STATUS_EINVAL;

    do {
        std::string fileName = FindData.cFileName;
        if (fileName == "." || fileName == "..") continue;

        if (Flags & DS_FLAG_ATTRIBUTE) {
            DWORD attr = FindData.dwFileAttributes;
            bool skip = false;            
            if ((ExtendedFlags & DSEXT_FLAG_ATTR_DIRECTORIES) && !(attr & FILE_ATTRIBUTE_DIRECTORY)) skip = true;
            if ((ExtendedFlags & DSEXT_FLAG_ATTR_NDIRECTORIES) && (attr & FILE_ATTRIBUTE_DIRECTORY)) skip = true;
            if ((ExtendedFlags & DSEXT_FLAG_ATTR_HIDDEN) && !(attr & FILE_ATTRIBUTE_HIDDEN)) skip = true;
            if ((ExtendedFlags & DSEXT_FLAG_ATTR_NHIDDEN) && (attr & FILE_ATTRIBUTE_HIDDEN)) skip = true;
            if ((ExtendedFlags & DSEXT_FLAG_ATTR_SYSTEM) && !(attr & FILE_ATTRIBUTE_SYSTEM)) skip = true;
            if ((ExtendedFlags & DSEXT_FLAG_ATTR_NSYSTEM) && (attr & FILE_ATTRIBUTE_SYSTEM)) skip = true;
            if ((ExtendedFlags & DSEXT_FLAG_ATTR_READ_ONLY) && !(attr & FILE_ATTRIBUTE_READONLY)) skip = true;
            if ((ExtendedFlags & DSEXT_FLAG_ATTR_NREAD_ONLY) && (attr & FILE_ATTRIBUTE_READONLY)) skip = true;
            if ((ExtendedFlags & DSEXT_FLAG_ATTR_ARCHIVE) && !(attr & FILE_ATTRIBUTE_ARCHIVE)) skip = true;
            if ((ExtendedFlags & DSEXT_FLAG_ATTR_NARCHIVE) && (attr & FILE_ATTRIBUTE_ARCHIVE)) skip = true;
            
            if (skip) continue;
        }

        FileEntry fe;
        fe.data = FindData;
        fe.name = fileName;
        
        size_t dot = fe.name.find_last_of(".");
        fe.ext = (dot != std::string::npos) ? fe.name.substr(dot) : "";
        
        if (Flags & DS_FLAG_LOWERCASE_OUTPUT) {
            std::transform(fe.name.begin(), fe.name.end(), fe.name.begin(), ::tolower);
        }

        entries.push_back(fe);

        if ((Flags & DS_FLAG_DISPLAY_FILE_RECURSIVE) && (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            PrintDirectory(SearchPath + FindData.cFileName, Flags, ExtendedFlags);
        }
    } while (FindNextFileA(FindHandle, &FindData));
    FindClose(FindHandle);

    if (Flags & DS_FLAG_SORT_ORDER) {
        std::sort(entries.begin(), entries.end(), [&](const FileEntry& a, const FileEntry& b) {
            if (ExtendedFlags & DSEXT_FLAG_SO_SIZE) return a.data.nFileSizeLow < b.data.nFileSizeLow;
            if (ExtendedFlags & DSEXT_FLAG_SO_NSIZE) return a.data.nFileSizeLow > b.data.nFileSizeLow;
            if (ExtendedFlags & DSEXT_FLAG_SO_DATE) {
                return CompareFileTime(&a.data.ftLastWriteTime, &b.data.ftLastWriteTime) < 0;
            }
            if (ExtendedFlags & DSEXT_FLAG_SO_EXT) return a.ext < b.ext;
            return a.name < b.name; 
        });
    }

    int lineCount = 0;
    for (auto& entry : entries) {
        if (Flags & DS_FLAG_BARE_FORMAT) {
            std::cout << entry.name << "\n";
            continue;
        }

        FILETIME ft = entry.data.ftLastWriteTime;
        if (ExtendedFlags & DSEXT_FLAG_TF_CREATION) ft = entry.data.ftCreationTime;
        else if (ExtendedFlags & DSEXT_FLAG_TF_LAST_ACCESS) ft = entry.data.ftLastAccessTime;

        SYSTEMTIME st;
        FileTimeToSystemTime(&ft, &st);

        if (Flags & DS_FLAG_DISPLAY_4DIGIT_YEAR) 
            printf("%02d/%02d/%04d  %02d:%02d  ", st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute);
        else 
            printf("%02d/%02d/%02d  %02d:%02d  ", st.wMonth, st.wDay, st.wYear % 100, st.wHour, st.wMinute);

        if (entry.data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            std::cout << "<DIR>          ";
        } else {
            if (Flags & DS_FLAG_THOUSAND_SEPERATOR) printf("%'14u ", entry.data.nFileSizeLow);
            else printf("%14u ", entry.data.nFileSizeLow);
        }

        std::cout << entry.name << "\n";
        if ((Flags & DS_FLAG_PAUSE) && (++lineCount % 24 == 0)) {
            std::cout << "Press Enter to continue...";
            std::cin.get();
        }
    }

    return STATUS_OK;
}


static 
CMD_STATUS
GetNewExtendedAttributeFlags(
    ULONG* CurrentFlags,
    ULONG  FlagOr
){
    if((!CurrentFlags) || (FlagOr & DSEXT_ATTRIUTE_FLAGS) != FlagOr){
        return STATUS_EINVAL;
    }
    ULONG TmpFlags = *CurrentFlags;
    if(TmpFlags & DSEXT_ATTRIUTE_FLAGS){
        return STATUS_DUPLICATE;
    }
    TmpFlags = DSEXT_SET_ATTRIBUTE_FLAGS(TmpFlags, FlagOr);
    *CurrentFlags = TmpFlags;
    return STATUS_OK;
} 

static 
CMD_STATUS
GetNewExtendedSortOrderFlags(
    ULONG* CurrentFlags,
    ULONG  FlagOr
){
    if((!CurrentFlags) || (FlagOr & DSEXT_SORT_ORDER_FLAGS) != FlagOr){
        return STATUS_EINVAL;
    }
    ULONG TmpFlags = *CurrentFlags;
    if(TmpFlags & DSEXT_SORT_ORDER_FLAGS){
        return STATUS_DUPLICATE;
    }
    TmpFlags = DSEXT_SET_SORT_ORDER_FLAGS(TmpFlags, FlagOr);
    *CurrentFlags = TmpFlags;
    return STATUS_OK;
} 

static 
CMD_STATUS
GetNewExtendedTimeFieldFlags(
    ULONG* CurrentFlags,
    ULONG  FlagOr
){
    if((!CurrentFlags) || (FlagOr & DSEXT_TIME_FIELD_FLAGS) != FlagOr){
        return STATUS_EINVAL;
    }
    ULONG TmpFlags = *CurrentFlags;
    if(TmpFlags & DSEXT_TIME_FIELD_FLAGS){
        return STATUS_DUPLICATE;
    }
    TmpFlags = DSEXT_SET_TIME_FIELD_FLAGS(TmpFlags, FlagOr);
    *CurrentFlags = TmpFlags;
    return STATUS_OK;
} 

//CMD_STATUS
//ParseFlags(
//    std::string Flags,
//
//){
//
//}

CMD_STATUS 
DispatchDirCommand(
    COMMAND_PARAMETER Params
){
    if(Params == ""){
        PrintDirectory(
            DriveLetter + ":" + DrivePath,
            0,
            0
        );
        return STATUS_OK;
    }

    int PathEnd = Params.find(' ');
    bool SkipFlags = false;
    if(PathEnd == std::string::npos){
        SkipFlags = true;
        PathEnd = Params.length();
    }
    
    int DriveCoordinator = Params.find(':');
    std::string NewDriveLetter;
    std::string NewPath;
    if((DriveCoordinator != std::string::npos) && (DriveCoordinator <= PathEnd)){
        if(DriveCoordinator == 0){
            std::cout << "ERROR Invalid Directory\n";
            return STATUS_EINVAL;
        }
        NewDriveLetter = Params.substr(DriveCoordinator - 1, 2);
        NewPath = Params.substr(DriveCoordinator + 1, PathEnd - (DriveCoordinator + 1));
    }else {
        NewDriveLetter = DriveLetter;
        NewPath = Params.substr(0, PathEnd);
    }

    std::replace(NewPath.begin(), NewPath.begin() + PathEnd, '/', '\\');    

    ULONG Flags = 0;
    ULONG ExtFlags = 0;

    if(!SkipFlags){



    }

    PrintDirectory(NewDriveLetter + ":\\" + NewPath + '\\', Flags, ExtFlags);

    return STATUS_OK;
}
