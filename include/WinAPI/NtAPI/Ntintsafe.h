#ifndef NTINTSAFE_H
#define NTINTSAFE_H

#include <NtAPI.h>

NTSTATUS RtlByteToChar(
    BYTE bOperand,
   CHAR *pch
);

NTSTATUS RtlByteToInt8(
    BYTE bOperand,
   INT8 *pi8Result
);

NTSTATUS RtlDWordPtrAdd(
    DWORD_PTR dwAugend,
    DWORD_PTR dwAddend,
   DWORD_PTR *pdwResult
);

NTSTATUS RtlDWordPtrMult(
    DWORD_PTR dwMultiplicand,
    DWORD_PTR dwMultiplier,
   DWORD_PTR *pdwResult
);

NTSTATUS RtlDWordPtrSub(
    DWORD_PTR dwMinuend,
    DWORD_PTR dwSubtrahend,
   DWORD_PTR *pdwResult
);

NTSTATUS RtlInt8Add(
    INT8 i8Augend,
    INT8 i8Addend,
   INT8 *pi8Result
);

NTSTATUS RtlInt8Mult(
    INT8 i8Multiplicand,
    INT8 i8Multiplier,
   INT8 *pi8Result
);

NTSTATUS RtlInt8Sub(
    INT8 i8Minuend,
    INT8 i8Subtrahend,
   INT8 *pi8Result
);

NTSTATUS RtlInt8ToUChar(
    INT8  i8Operand,
   UCHAR *pch
);

NTSTATUS RtlInt8ToUInt(
    INT8 i8Operand,
   UINT *puResult
);

NTSTATUS RtlInt8ToUInt8(
    INT8  i8Operand,
   UINT8 *pu8Result
);

NTSTATUS RtlInt8ToUIntPtr(
    INT8     i8Operand,
   UINT_PTR *puResult
);

NTSTATUS RtlInt8ToULong(
    INT8  i8Operand,
   ULONG *pulResult
);

NTSTATUS RtlInt8ToULongLong(
    INT8      i8Operand,
   ULONGLONG *pullResult
);

NTSTATUS RtlInt8ToULongPtr(
    INT8      i8Operand,
   ULONG_PTR *pulResult
);

NTSTATUS RtlInt8ToUShort(
    INT8   i8Operand,
   USHORT *pusResult
);

NTSTATUS RtlIntAdd(
    INT iAugend,
    INT iAddend,
   INT *piResult
);

NTSTATUS RtlIntMult(
    INT iMultiplicand,
    INT iMultiplier,
   INT *piResult
);

NTSTATUS RtlIntPtrAdd(
    INT_PTR iAugend,
    INT_PTR iAddend,
   INT_PTR *piResult
);

NTSTATUS RtlIntPtrMult(
    INT_PTR iMultiplicand,
    INT_PTR iMultiplier,
   INT_PTR *piResult
);

NTSTATUS RtlIntPtrSub(
    INT_PTR iMinuend,
    INT_PTR iSubtrahend,
   INT_PTR *piResult
);

NTSTATUS RtlIntPtrToChar(
    INT_PTR iOperand,
   CHAR    *pch
);

NTSTATUS RtlIntPtrToChar(
    INT_PTR iOperand,
   CHAR    *pch
);

NTSTATUS RtlIntPtrToInt8(
    INT_PTR iOperand,
   INT8    *pi8Result
);

NTSTATUS RtlIntPtrToLong(
    INT_PTR iOperand,
   LONG    *plResult
);

NTSTATUS RtlIntPtrToLongPtr(
    INT_PTR  iOperand,
   LONG_PTR *plResult
);

NTSTATUS RtlIntPtrToShort(
    INT_PTR iOperand,
   SHORT   *psResult
);

NTSTATUS RtlIntPtrToUChar(
    INT_PTR iOperand,
   UCHAR   *pch
);

NTSTATUS RtlIntPtrToUInt(
    INT_PTR iOperand,
   UINT    *puResult
);

NTSTATUS RtlIntPtrToUInt8(
    INT_PTR iOperand,
   UINT8   *pui8Result
);

NTSTATUS RtlIntPtrToUIntPtr(
    INT_PTR  iOperand,
   UINT_PTR *puResult
);

NTSTATUS RtlIntPtrToULong(
    INT_PTR iOperand,
   ULONG   *pulResult
);

NTSTATUS RtlIntPtrToULongLong(
    INT_PTR   iOperand,
   ULONGLONG *pullResult
);

NTSTATUS RtlIntPtrToULongPtr(
    INT_PTR   iOperand,
   ULONG_PTR *pulResult
);

NTSTATUS RtlIntPtrToUShort(
    INT_PTR iOperand,
   USHORT  *pusResult
);

NTSTATUS RtlIntSub(
   INT iMinuend,
   INT iSubtrahend,
       INT *piResult
);

NTSTATUS RtlIntToChar(
    INT  iOperand,
   CHAR *pch
);

NTSTATUS RtlIntToInt8(
    INT  iOperand,
   INT8 *pi8Result
);


NTSTATUS RtlIntToShort(
    INT   iOperand,
   SHORT *psResult
);

NTSTATUS RtlIntToUChar(
    INT   iOperand,
   UCHAR *pch
);

NTSTATUS RtlIntToUInt(
    INT  iOperand,
   UINT *puResult
);

NTSTATUS RtlIntToUInt8(
    INT   iOperand,
   UINT8 *pui8Result
);

NTSTATUS RtlIntToULong(
    INT   iOperand,
   ULONG *pulResult
);

NTSTATUS RtlIntToULongLong(
    INT       iOperand,
   ULONGLONG *pullResult
);

NTSTATUS RtlIntToUShort(
    INT    iOperand,
   USHORT *pusResult
);

NTSTATUS RtlLongAdd(
    LONG lAugend,
    LONG lAddend,
   LONG *plResult
);

NTSTATUS RtlLongLongAdd(
    LONGLONG llAugend,
    LONGLONG llAddend,
   LONGLONG *pllResult
);

NTSTATUS RtlLongLongMult(
    LONGLONG llMultiplicand,
    LONGLONG llMultiplier,
   LONGLONG *pllResult
);

NTSTATUS RtlLongLongSub(
    LONGLONG llMinuend,
    LONGLONG llSubtrahend,
   LONGLONG *pllResult
);

NTSTATUS RtlLongLongToChar(
    LONGLONG llOperand,
   CHAR     *pch
);

NTSTATUS RtlLongLongToInt(
    LONGLONG llOperand,
   INT      *piResult
);

NTSTATUS RtlLongLongToInt8(
    LONGLONG llOperand,
   INT8     *pi8Result
);

NTSTATUS RtlLongLongToIntPtr(
    LONGLONG llOperand,
   INT_PTR  *piResult
);

NTSTATUS RtlLongLongToLong(
    LONGLONG llOperand,
   LONG     *plResult
);

NTSTATUS RtlLongLongToLongPtr(
    LONGLONG llOperand,
   LONG_PTR *plResult
);

NTSTATUS RtlLongLongToShort(
    LONGLONG llOperand,
   SHORT    *psResult
);

NTSTATUS RtlLongLongToUChar(
    LONGLONG llOperand,
   UCHAR    *pch
);

NTSTATUS RtlLongLongToUInt(
    LONGLONG llOperand,
   UINT     *puResult
);

NTSTATUS RtlLongLongToUInt8(
    LONGLONG llOperand,
   UINT8    *pu8Result
);

NTSTATUS RtlLongLongToULong(
    LONGLONG llOperand,
   ULONG    *pulResult
)
;NTSTATUS RtlLongLongToULongLong(
    LONGLONG  llOperand,
   ULONGLONG *pullResult
);

NTSTATUS RtlLongLongToUShort(
    LONGLONG llOperand,
   USHORT   *pusResult
);

NTSTATUS RtlLongMult(
    LONG lMultiplicand,
    LONG lMultiplier,
   LONG *plResult
);

NTSTATUS RtlLongPtrAdd(
  LONG_PTR lAugend,
  LONG_PTR lAddend,
  LONG_PTR *plResult
);

NTSTATUS RtlLongPtrMult(
    LONG_PTR lMultiplicand,
    LONG_PTR lMultiplier,
   LONG_PTR *plResult
);

NTSTATUS RtlLongPtrSub(
    LONG_PTR lMinuend,
    LONG_PTR lSubtrahend,
   LONG_PTR *plResult
);

NTSTATUS RtlLongPtrToChar(
    LONG_PTR lOperand,
   CHAR     *pch
);

NTSTATUS RtlLongPtrToInt(
    LONG_PTR lOperand,
   INT      *piResult
);

NTSTATUS RtlLongPtrToInt8(
    LONG_PTR lOperand,
   INT8     *pi8Result
);

NTSTATUS RtlLongPtrToIntPtr(
    LONG_PTR lOperand,
   INT_PTR  *piResult
);

NTSTATUS RtlLongPtrToLong(
    LONG_PTR lOperand,
   LONG     *plResult
);

NTSTATUS RtlLongPtrToShort(
    LONG_PTR lOperand,
   SHORT    *psResult
);

NTSTATUS RtlLongPtrToUChar(
    LONG_PTR lOperand,
   UCHAR    *pch
);

NTSTATUS RtlLongPtrToUInt(
    LONG_PTR lOperand,
   UINT     *puResult
);

NTSTATUS RtlLongPtrToUInt8(
    LONG_PTR lOperand,
   UINT8    *pui8Result
);

NTSTATUS RtlLongPtrToUIntPtr(
    LONG_PTR lOperand,
   UINT_PTR *puResult
);
NTSTATUS RtlLongPtrToULong(
    LONG_PTR lOperand,
   ULONG    *pulResult
);

NTSTATUS RtlLongPtrToULongLong(
    LONG_PTR  lOperand,
   ULONGLONG *pullResult
);

NTSTATUS RtlLongPtrToULongPtr(
    LONG_PTR  lOperand,
   ULONG_PTR *pulResult
);

NTSTATUS RtlLongPtrToUShort(
    LONG_PTR lOperand,
   USHORT   *pusResult
);

NTSTATUS RtlLongSub(
    LONG lMinuend,
    LONG lSubtrahend,
   LONG *plResult
);

NTSTATUS RtlLongToChar(
    LONG lOperand,
   CHAR *pch
);

NTSTATUS RtlLongToInt(
    LONG lOperand,
   INT  *piResult
);

NTSTATUS RtlLongToInt8(
    LONG lOperand,
   INT8 *pi8Result
);

NTSTATUS RtlLongToIntPtr(
    LONG    lOperand,
   INT_PTR *piResult
);

NTSTATUS RtlLongToShort(
    LONG  lOperand,
   SHORT *psResult
);

NTSTATUS RtlLongToUChar(
    LONG  lOperand,
   UCHAR *pch
);


NTSTATUS RtlLongToUInt(
    LONG lOperand,
   UINT *puResult
);

NTSTATUS RtlLongToUInt8(
  LONG  lOperand,
  UINT8 *pui8Result
);

NTSTATUS RtlLongToUIntPtr(
    LONG     lOperand,
   UINT_PTR *puResult
);

NTSTATUS RtlLongToULong(
    LONG  lOperand,
   ULONG *pulResult
);

NTSTATUS RtlLongToULongLong(
    LONG      lOperand,
   ULONGLONG *pullResult
);

NTSTATUS RtlLongToULongPtr(
  LONG      lOperand,
  ULONG_PTR *pulResult
);

NTSTATUS RtlLongToUShort(
    LONG   lOperand,
   USHORT *pusResult
);

NTSTATUS RtlPtrdiffTAdd(
    ptrdiff_t Augend,
    ptrdiff_t Addend,
   ptrdiff_t *pResult
);

NTSTATUS RtlPtrdiffTMult(
    ptrdiff_t Multiplicand,
    ptrdiff_t Multiplier,
   ptrdiff_t *pResult
);

NTSTATUS RtlPtrdiffTSub(
    ptrdiff_t Minuend,
    ptrdiff_t Subtrahend,
   ptrdiff_t *pResult
);

NTSTATUS RtlShortAdd(
    SHORT sAugend,
    SHORT sAddend,
   SHORT *psResult
);

NTSTATUS RtlShortMult(
    SHORT sMultiplicand,
    SHORT sMultiplier,
   SHORT *psResult
);

NTSTATUS RtlShortSub(
    SHORT sMinuend,
    SHORT sSubtrahend,
   SHORT *psResult
);

NTSTATUS RtlShortToChar(
    SHORT sOperand,
   CHAR  *pch
);

NTSTATUS RtlShortToDWordPtr(
    SHORT     sOperand,
   DWORD_PTR *pdwResult
);

NTSTATUS RtlShortToInt8(
    SHORT sOperand,
   INT8  *pi8Result
);

NTSTATUS RtlShortToUChar(
    SHORT sOperand,
   UCHAR *pch
);

NTSTATUS RtlShortToUInt(
    SHORT sOperand,
   UINT  *puResult
);

NTSTATUS RtlShortToUInt8(
   SHORT sOperand,
       UINT8 *pui8Result
);

NTSTATUS RtlShortToUIntPtr(
    SHORT    sOperand,
   UINT_PTR *puResult
);

NTSTATUS RtlShortToULong(
    SHORT sOperand,
   ULONG *pulResult
);

NTSTATUS RtlShortToULongLong(
    SHORT     sOperand,
   ULONGLONG *pullResult
);

NTSTATUS RtlShortToULongPtr(
    SHORT     sOperand,
   ULONG_PTR *pulResult
);

NTSTATUS RtlShortToUShort(
    SHORT  sOperand,
   USHORT *pusResult
);

NTSTATUS RtlSizeTAdd(
    size_t Augend,
    size_t Addend,
   size_t *pResult
);

NTSTATUS RtlSizeTMult(
    size_t Multiplicand,
    size_t Multiplier,
   size_t *pResult
);

NTSTATUS RtlSizeTSub(
    size_t Minuend,
    size_t Subtrahend,
   size_t *pResult
);

NTSTATUS RtlSSIZETAdd(
    SSIZE_T Augend,
    SSIZE_T Addend,
   SSIZE_T *pResult
);

NTSTATUS RtlSSIZETMult(
    SSIZE_T Multiplicand,
    SSIZE_T Multiplier,
   SSIZE_T *pResult
);

NTSTATUS RtlSSIZETSub(
    SSIZE_T Minuend,
    SSIZE_T Subtrahend,
   SSIZE_T *pResult
);

NTSTATUS RtlUInt8Add(
    UINT8 u8Augend,
    UINT8 u8Addend,
   UINT8 *pu8Result
);

NTSTATUS RtlUInt8Mult(
    UINT8 u8Multiplicand,
    UINT8 u8Multiplier,
   UINT8 *pu8Result
);

NTSTATUS RtlUInt8Sub(
    UINT8 u8Minuend,
    UINT8 u8Subtrahend,
   UINT8 *pu8Result
);

NTSTATUS RtlUInt8ToChar(
    UINT8 u8Operand,
   CHAR  *pch
);

NTSTATUS RtlUInt8ToInt8(
    UINT8 u8Operand,
   INT8  *pi8Result
);

NTSTATUS RtlUIntAdd(
    UINT uAugend,
    UINT uAddend,
   UINT *puResult
);

NTSTATUS RtlUIntMult(
    UINT uMultiplicand,
    UINT uMultiplier,
   UINT *puResult
);

NTSTATUS RtlUIntPtrAdd(
    UINT_PTR uAugend,
    UINT_PTR uAddend,
   UINT_PTR *puResult
);

NTSTATUS RtlUIntPtrMult(
    UINT_PTR uMultiplicand,
    UINT_PTR uMultiplier,
   UINT_PTR *puResult
);

NTSTATUS RtlUIntPtrSub(
    UINT_PTR uMinuend,
    UINT_PTR uSubtrahend,
   UINT_PTR *puResult
);

NTSTATUS RtlUIntPtrToChar(
  UINT_PTR uOperand,
  CHAR     *pch
);

NTSTATUS RtlUIntPtrToInt(
    UINT_PTR uOperand,
   INT      *piResult
);

NTSTATUS RtlUIntPtrToInt16(
    UINT_PTR uOperand,
   INT16    *pi16Result
);

NTSTATUS RtlUIntPtrToInt8(
    UINT_PTR uOperand,
   INT8     *pi8Result
);

NTSTATUS RtlUIntPtrToIntPtr(
    UINT_PTR uOperand,
   INT_PTR  *piResult
);

NTSTATUS RtlUIntPtrToLong(
        UINT_PTR uOperand,
   LONG     *plResult
);

NTSTATUS RtlUIntPtrToLongLong(
    UINT_PTR uOperand,
   LONGLONG *pllResult
);

NTSTATUS RtlUIntPtrToLongPtr(
    UINT_PTR uOperand,
   LONG_PTR *plResult
);

NTSTATUS RtlUIntPtrToShort(
    UINT_PTR uOperand,
   SHORT    *psResult
);

NTSTATUS RtlUIntPtrToUChar(
    UINT_PTR uOperand,
   UCHAR    *pch
);

NTSTATUS RtlUIntPtrToUInt(
        UINT_PTR uOperand,
   UINT     *puResult
);

NTSTATUS RtlUIntPtrToUInt16(
    UINT_PTR uOperand,
   UINT16   *pu16Result
);

NTSTATUS RtlUIntPtrToUInt8(
    UINT_PTR uOperand,
   UINT8    *pu8Result
);

NTSTATUS RtlUIntPtrToULong(
    UINT_PTR uOperand,
   ULONG    *pulResult
);

NTSTATUS RtlUIntPtrToUShort(
    UINT_PTR uOperand,
   USHORT   *pusResult
);

NTSTATUS RtlUIntSub(
    UINT uMinuend,
    UINT uSubtrahend,
   UINT *puResult
);

NTSTATUS RtlUIntToChar(
    UINT uOperand,
   CHAR *pch
);

NTSTATUS RtlUIntToInt(
    UINT uOperand,
   INT  *piResult
);

NTSTATUS RtlUIntToInt8(
    UINT uOperand,
   INT8 *pi8Result
);

NTSTATUS RtlUIntToIntPtr(
    UINT    uOperand,
   INT_PTR *piResult
);

NTSTATUS RtlUIntToLong(
    UINT uOperand,
   LONG *plResult
);

NTSTATUS RtlUIntToLongPtr(
    UINT     uOperand,
   LONG_PTR *plResult
);

NTSTATUS RtlUIntToShort(
    UINT  uOperand,
   SHORT *psResult
);

NTSTATUS RtlUIntToUChar(
    UINT  uOperand,
   UCHAR *pch
);

NTSTATUS RtlUIntToUInt8(
    UINT  uOperand,
   UINT8 *pui8Result
);

NTSTATUS RtlUIntToUShort(
    UINT   uOperand,
   USHORT *pusResult
);

NTSTATUS RtlULongAdd(
    ULONG ulAugend,
    ULONG ulAddend,
   ULONG *pulResult
);

NTSTATUS RtlULongLongAdd(
   ULONGLONG ullAugend,
   ULONGLONG ullAddend,
       ULONGLONG *pullResult
);

NTSTATUS RtlULongLongMult(
    ULONGLONG ullMultiplicand,
    ULONGLONG ullMultiplier,
   ULONGLONG *pullResult
);

NTSTATUS RtlULongLongSub(
    ULONGLONG ullMinuend,
    ULONGLONG ullSubtrahend,
   ULONGLONG *pullResult
);

NTSTATUS RtlULongLongToChar(
    ULONGLONG ullOperand,
   CHAR      *pch
);

NTSTATUS RtlULongLongToInt(
    ULONGLONG ullOperand,
   INT       *piResult
);

NTSTATUS RtlULongLongToInt8(
    ULONGLONG ullOperand,
   INT8      *pi8Result
);

NTSTATUS RtlULongLongToLong(
    ULONGLONG ullOperand,
   LONG      *plResult
);

NTSTATUS RtlULongLongToLongLong(
    ULONGLONG ullOperand,
   LONGLONG  *pllResult
);

NTSTATUS RtlULongLongToLongPtr(
    ULONGLONG ullOperand,
   LONG_PTR  *plResult
);

NTSTATUS RtlULongLongToShort(
    ULONGLONG ullOperand,
   SHORT     *psResult
);

NTSTATUS RtlULongLongToUChar(
    ULONGLONG ullOperand,
   UCHAR     *pch
);

NTSTATUS RtlULongLongToUInt(
    ULONGLONG ullOperand,
   UINT      *puResult
);

NTSTATUS RtlULongLongToUInt8(
    ULONGLONG ullOperand,
   UINT8     *pu8Result
);

NTSTATUS RtlULongLongToUIntPtr(
    ULONGLONG ullOperand,
   UINT_PTR  *puResult
);

NTSTATUS RtlULongLongToULong(
   ULONGLONG ullOperand,
       ULONG     *pulResult
);

NTSTATUS RtlULongLongToULongPtr(
   ULONGLONG ullOperand,
       ULONG_PTR *pulResult
);

NTSTATUS RtlULongLongToUShort(
    ULONGLONG ullOperand,
   USHORT    *pusResult
);

NTSTATUS RtlULongMult(
    ULONG ulMultiplicand,
    ULONG ulMultiplier,
   ULONG *pulResult
);

NTSTATUS RtlULongPtrAdd(
    ULONG_PTR ulAugend,
    ULONG_PTR ulAddend,
   ULONG_PTR *pulResult
);

NTSTATUS RtlULongPtrMult(
  ULONG_PTR ulMultiplicand,
  ULONG_PTR ulMultiplier,
  ULONG_PTR *pulResult
);

NTSTATUS RtlULongPtrSub(
    ULONG_PTR ulMinuend,
    ULONG_PTR ulSubtrahend,
   ULONG_PTR *pulResult
);

NTSTATUS RtlULongPtrToChar(
    ULONG_PTR ulOperand,
   CHAR      *pch
);

NTSTATUS RtlULongPtrToInt(
    ULONG_PTR ulOperand,
   INT       *piResult
);

NTSTATUS RtlULongPtrToInt8(
    ULONG_PTR ulOperand,
   INT8      *pi8Result
);

NTSTATUS RtlULongPtrToIntPtr(
    ULONG_PTR ulOperand,
   INT_PTR   *piResult
);

NTSTATUS RtlULongPtrToLong(
    ULONG_PTR ulOperand,
   LONG      *plResult
);

NTSTATUS RtlULongPtrToLongLong(
    ULONG_PTR ulOperand,
   LONGLONG  *pllResult
);

NTSTATUS RtlULongPtrToLongPtr(
    ULONG_PTR ulOperand,
   LONG_PTR  *plResult
);

NTSTATUS RtlULongPtrToShort(
    ULONG_PTR ulOperand,
   SHORT     *psResult
);

NTSTATUS RtlULongPtrToShort(
    ULONG_PTR ulOperand,
   SHORT     *psResult
);

NTSTATUS RtlULongPtrToUInt(
    ULONG_PTR ulOperand,
   UINT      *puResult
);

NTSTATUS RtlULongPtrToUInt8(
    ULONG_PTR ulOperand,
   UINT8     *pui8Result
);

NTSTATUS RtlULongPtrToUIntPtr(
    ULONG_PTR ulOperand,
   UINT_PTR  *puResult
);

NTSTATUS RtlULongPtrToULong(
    ULONG_PTR ulOperand,
   ULONG     *pulResult
);

NTSTATUS RtlULongPtrToUShort(
    ULONG_PTR ulOperand,
   USHORT    *pusResult
);

NTSTATUS RtlULongSub(
    ULONG ulMinuend,
    ULONG ulSubtrahend,
   ULONG *pulResult
);

NTSTATUS RtlULongToChar(
    ULONG ulOperand,
   CHAR  *pch
);

NTSTATUS RtlULongToInt(
    ULONG ulOperand,
   INT   *piResult
);

NTSTATUS RtlULongToInt8(
    ULONG ulOperand,
   INT8  *pi8Result
);

NTSTATUS RtlULongToIntPtr(
    ULONG   ulOperand,
   INT_PTR *piResult
);

NTSTATUS RtlULongToLong(
    ULONG ulOperand,
   LONG  *plResult
);

NTSTATUS RtlULongToLongPtr(
    ULONG    ulOperand,
   LONG_PTR *plResult
);

NTSTATUS RtlULongToShort(
    ULONG ulOperand,
   SHORT *psResult
);

NTSTATUS RtlULongToUChar(
    ULONG ulOperand,
   UCHAR *pch
);

NTSTATUS RtlULongToUInt(
    ULONG ulOperand,
   UINT  *puResult
);

NTSTATUS RtlULongToUInt8(
    ULONG ulOperand,
   UINT8 *pui8Result
);

NTSTATUS RtlULongToUIntPtr(
    ULONG    ulOperand,
   UINT_PTR *puiResult
);

NTSTATUS RtlULongToUShort(
    ULONG  ulOperand,
   USHORT *pusResult
);

NTSTATUS RtlUShortAdd(
    USHORT usAugend,
    USHORT usAddend,
   USHORT *pusResult
);

NTSTATUS RtlUShortAdd(
    USHORT usAugend,
    USHORT usAddend,
   USHORT *pusResult
);

NTSTATUS RtlUShortMult(
    USHORT usMultiplicand,
    USHORT usMultiplier,
   USHORT *pusResult
);

NTSTATUS RtlUShortSub(
    USHORT usMinuend,
    USHORT usSubtrahend,
   USHORT *pusResult
);

NTSTATUS RtlUShortToChar(
    USHORT usOperand,
   CHAR   *pch
);

NTSTATUS RtlUShortToInt8(
    USHORT usOperand,
   INT8   *pi8Result
);

NTSTATUS RtlUShortToShort(
    USHORT usOperand,
   SHORT  *psResult
);

NTSTATUS RtlUShortToUChar(
    USHORT usOperand,
   UCHAR  *pch
);

NTSTATUS RtlUShortToUInt8(
    USHORT usOperand,
   UINT8  *pui8Result
);

#endif