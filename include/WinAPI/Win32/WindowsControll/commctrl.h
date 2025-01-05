#ifndef _COMMCTRL_H
#define _COMMCTRL_H

#include "../WinAPIStdType.h"



#ifdef __cplusplus
extern "C"{
#endif
#ifdef _USER_MODE_CODE_

typedef struct _UDACCEL {
  UINT nSec;
  UINT nInc;
} UDACCEL, *LPUDACCEL;


typedef struct tagTVSORTCB {
  HTREEITEM    hParent;
  PFNTVCOMPARE lpfnCompare;
  LPARAM       lParam;
} TVSORTCB, *LPTVSORTCB;

typedef struct tagTVITEMW {
  UINT      mask;
  HTREEITEM hItem;
  UINT      state;
  UINT      stateMask;
  LPWSTR    pszText;
  int       cchTextMax;
  int       iImage;
  int       iSelectedImage;
  int       cChildren;
  LPARAM    lParam;
} TVITEMW, *LPTVITEMW;

typedef struct tagTVITEMEXW {
  UINT      mask;
  HTREEITEM hItem;
  UINT      state;
  UINT      stateMask;
  LPWSTR    pszText;
  int       cchTextMax;
  int       iImage;
  int       iSelectedImage;
  int       cChildren;
  LPARAM    lParam;
  int       iIntegral;
  UINT      uStateEx;
  HWND      hwnd;
  int       iExpandedImage;
  int       iReserved;
} TVITEMEXW, *LPTVITEMEXW;

typedef struct tagTVITEMEXA {
  UINT      mask;
  HTREEITEM hItem;
  UINT      state;
  UINT      stateMask;
  LPSTR     pszText;
  int       cchTextMax;
  int       iImage;
  int       iSelectedImage;
  int       cChildren;
  LPARAM    lParam;
  int       iIntegral;
  UINT      uStateEx;
  HWND      hwnd;
  int       iExpandedImage;
  int       iReserved;
} TVITEMEXA, *LPTVITEMEXA;

typedef struct tagTVITEMA {
  UINT      mask;
  HTREEITEM hItem;
  UINT      state;
  UINT      stateMask;
  LPSTR     pszText;
  int       cchTextMax;
  int       iImage;
  int       iSelectedImage;
  int       cChildren;
  LPARAM    lParam;
} TVITEMA, *LPTVITEMA;

typedef struct tagTVINSERTSTRUCTW {
  HTREEITEM hParent;
  HTREEITEM hInsertAfter;
  union {
    TVITEMEXW itemex;
    TV_ITEMW  item;
  } DUMMYUNIONNAME;
} TVINSERTSTRUCTW, *LPTVINSERTSTRUCTW;

typedef struct tagTVGETITEMPARTRECTINFO {
  HTREEITEM  hti;
  RECT       *prc;
  TVITEMPART partID;
} TVGETITEMPARTRECTINFO;

typedef struct tagTVHITTESTINFO {
  POINT     pt;
  UINT      flags;
  HTREEITEM hItem;
} TVHITTESTINFO, *LPTVHITTESTINFO;

typedef struct tagTOOLINFOW {
  UINT      cbSize;
  UINT      uFlags;
  HWND      hwnd;
  UINT_PTR  uId;
  RECT      rect;
  HINSTANCE hinst;
  LPWSTR    lpszText;
  LPARAM    lParam;
  void      *lpReserved;
} TTTOOLINFOW, *PTOOLINFOW, *LPTTTOOLINFOW;

typedef struct tagTOOLINFOA {
  UINT      cbSize;
  UINT      uFlags;
  HWND      hwnd;
  UINT_PTR  uId;
  RECT      rect;
  HINSTANCE hinst;
  LPSTR     lpszText;
  LPARAM    lParam;
  void      *lpReserved;
} TTTOOLINFOA, *PTOOLINFOA, *LPTTTOOLINFOA;

typedef struct _TT_HITTESTINFOW {
  HWND        hwnd;
  POINT       pt;
  TTTOOLINFOW ti;
} TTHITTESTINFOW, *LPTTHITTESTINFOW;

typedef struct _TT_HITTESTINFOA {
  HWND        hwnd;
  POINT       pt;
  TTTOOLINFOA ti;
} TTHITTESTINFOA, *LPTTHITTESTINFOA;
typedef struct _TTGETTITLE {
  DWORD dwSize;
  UINT  uTitleBitmap;
  UINT  cch;
  WCHAR *pszTitle;
} TTGETTITLE, *PTTGETTITLE;

typedef struct tagTCITEMW {
  UINT   mask;
  DWORD  dwState;
  DWORD  dwStateMask;
  LPWSTR pszText;
  int    cchTextMax;
  int    iImage;
  LPARAM lParam;
} TCITEMW, *LPTCITEMW;

typedef struct tagTCITEMHEADERW {
  UINT   mask;
  UINT   lpReserved1;
  UINT   lpReserved2;
  LPWSTR pszText;
  int    cchTextMax;
  int    iImage;
} TCITEMHEADERW, *LPTCITEMHEADERW;

typedef struct tagTCITEMHEADERA {
  UINT  mask;
  UINT  lpReserved1;
  UINT  lpReserved2;
  LPSTR pszText;
  int   cchTextMax;
  int   iImage;
} TCITEMHEADERA, *LPTCITEMHEADERA;

typedef struct tagTCITEMA {
  UINT   mask;
  DWORD  dwState;
  DWORD  dwStateMask;
  LPSTR  pszText;
  int    cchTextMax;
  int    iImage;
  LPARAM lParam;
} TCITEMA, *LPTCITEMA;

typedef struct tagTCHITTESTINFO {
  POINT pt;
  UINT  flags;
} TCHITTESTINFO, *LPTCHITTESTINFO;

typedef struct tagTBSAVEPARAMSW {
  HKEY    hkr;
  LPCWSTR pszSubKey;
  LPCWSTR pszValueName;
} TBSAVEPARAMSW, *LPTBSAVEPARAMW;

typedef struct tagTBSAVEPARAMSA {
  HKEY   hkr;
  LPCSTR pszSubKey;
  LPCSTR pszValueName;
} TBSAVEPARAMSA, *LPTBSAVEPARAMSA;

typedef struct {
  HINSTANCE hInstOld;
  UINT_PTR  nIDOld;
  HINSTANCE hInstNew;
  UINT_PTR  nIDNew;
  int       nButtons;
} TBREPLACEBITMAP, *LPTBREPLACEBITMAP;

typedef struct {
  UINT  cbSize;
  DWORD dwMask;
  int   cxPad;
  int   cyPad;
  int   cxBarPad;
  int   cyBarPad;
  int   cxButtonSpacing;
  int   cyButtonSpacing;
} TBMETRICS, *LPTBMETRICS;

typedef struct {
  int   iButton;
  DWORD dwFlags;
} TBINSERTMARK, *LPTBINSERTMARK;

typedef struct {
  UINT      cbSize;
  DWORD     dwMask;
  int       idCommand;
  int       iImage;
  BYTE      fsState;
  BYTE      fsStyle;
  WORD      cx;
  DWORD_PTR lParam;
  LPWSTR    pszText;
  int       cchText;
} TBBUTTONINFOW, *LPTBBUTTONINFOW;

typedef struct {
  UINT      cbSize;
  DWORD     dwMask;
  int       idCommand;
  int       iImage;
  BYTE      fsState;
  BYTE      fsStyle;
  WORD      cx;
  DWORD_PTR lParam;
  LPSTR     pszText;
  int       cchText;
} TBBUTTONINFOA, *LPTBBUTTONINFOA;

typedef struct _TBBUTTON_Ext {
  int       iBitmap;
  int       idCommand;
  BYTE      fsState;
  BYTE      fsStyle;
  BYTE      bReserved[6];
  DWORD_PTR dwData;
  INT_PTR   iString;
} TBBUTTON_Ext, *PTBBUTTON_Ext, *LPTBBUTTON_Ext;

typedef struct _TBBUTTON_Gen {
  int       iBitmap;
  int       idCommand;
  BYTE      fsState;
  BYTE      fsStyle;
  BYTE      bReserved[2];
  DWORD_PTR dwData;
  INT_PTR   iString;
} TBBUTTON_Gen, *PTBBUTTON_Gen, *LPTBBUTTON_Gen;

typedef struct tagTBADDBITMAP {
  HINSTANCE hInst;
  UINT_PTR  nID;
} TBADDBITMAP, *LPTBADDBITMAP;

typedef struct _TASKDIALOGCONFIG {
  UINT                           cbSize;
  HWND                           hwndParent;
  HINSTANCE                      hInstance;
  TASKDIALOG_FLAGS               dwFlags;
  TASKDIALOG_COMMON_BUTTON_FLAGS dwCommonButtons;
  PCWSTR                         pszWindowTitle;
  union {
    HICON  hMainIcon;
    PCWSTR pszMainIcon;
  } DUMMYUNIONNAME;
  PCWSTR                         pszMainInstruction;
  PCWSTR                         pszContent;
  UINT                           cButtons;
  const TASKDIALOG_BUTTON        *pButtons;
  int                            nDefaultButton;
  UINT                           cRadioButtons;
  const TASKDIALOG_BUTTON        *pRadioButtons;
  int                            nDefaultRadioButton;
  PCWSTR                         pszVerificationText;
  PCWSTR                         pszExpandedInformation;
  PCWSTR                         pszExpandedControlText;
  PCWSTR                         pszCollapsedControlText;
  union {
    HICON  hFooterIcon;
    PCWSTR pszFooterIcon;
  } DUMMYUNIONNAME2;
  PCWSTR                         pszFooter;
  PFTASKDIALOGCALLBACK           pfCallback;
  LONG_PTR                       lpCallbackData;
  UINT                           cxWidth;
} TASKDIALOGCONFIG;

#endif
#ifdef __cplusplus
}
#endif

#endif