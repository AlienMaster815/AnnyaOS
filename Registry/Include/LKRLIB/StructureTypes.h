#ifndef _LKR_LIB_H
#define _LKR_LIB_H

typedef unsigned char   BYTE;
typedef unsigned short  SECURITY_DESCRIPTOR_CONTROL;
typedef void*           PSID;
typedef void*           PACL;

#define SE_DACL_AUTO_INHERIT_REQ    0x0100
#define SE_DACL_AUTO_INHERITED      0x0400
#define SE_DACL_DEFAULTED           0x0008
#define SE_DACL_PRESENT             0x0004
#define SE_DACL_PROTECTED           0x1000
#define SE_GROUP_DEFAULTED          0x0002
#define SE_OWNER_DEFAULTED          0x0001
#define SE_RM_CONTROL_VALID         0x4000
#define SE_SACL_AUTO_INTHERIT_REQ   0x0200
#define SE_SACL_AUTO_INTHERITED     0x0800
#define SE_SACL_DEFAULTED           0x0020
#define SE_SACL_PRESENT             0x0010
#define SE_SACL_PROTECTED           0x2000
#define SE_SELF_RELATIVE            0x8000

typedef struct _SECURITY_DESCRIPTOR{
    BYTE                            Revision;
    BYTE                            Size;
    SECURITY_DESCRIPTOR_CONTROL     Control;
    PSID                            Owner;
    PSID                            Group;
    PACL                            Sacl;
    PACL                            Dacl;
}SECURITY_DESCRIPTOR, * PISECURITY_DESCRIPTOR;

#endif