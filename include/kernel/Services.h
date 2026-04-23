#ifndef _KERNEL_SERVICES_H
#define _KERNEL_SERVICES_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct _LOUSINE_ECS_OPERATIONS{
    int         (*PrintAsciiCharecter)(CHAR AsciiCharecter);
    int         (*PrintUnicodeCharecter)(UINT32 Charecter);
    void        (*EndofData)();
}LOUSINE_ECS_OPERATIONS, * PLOUSINE_ECS_OPERATIONS;

typedef struct _LOUSINE_ECS_DRIVER{
    LOUSTR                      DriverName;
    LOUSTR                      ModuleName;
    UINT64                      EcsId;
    LOUSINE_ECS_OPERATIONS      EcsOperations;
}LOUSINE_ECS_DRIVER, * PLOUSINE_ECS_DRIVER;

#ifndef _USER_MODE_CODE_

KERNEL_EXPORT 
LOUSTATUS 
LouKeRegisterEcsDriver(
    PLOUSINE_ECS_DRIVER EcsDriver
);

KERNEL_EXPORT 
void 
LouKeUnRegisterEcsDriver(
    PLOUSINE_ECS_DRIVER EcsDriver
);

#ifndef _KERNEL_MODULE_

int
LouKeEcsPrintAsciiCharecter(
    CHAR    Charecter
);

int 
LouKeEcsPrintUnicodeCharecter(
    UINT32  Charecter
);

void LouKeEcsEndofData();

#endif
#endif

#ifdef __cplusplus
}
#endif
#endif