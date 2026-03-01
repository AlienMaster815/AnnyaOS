#ifndef NTINTSAFE_H
#define NTINTSAFE_H

#include <NtAPI.h>

LOUSTATUS RtlByteToChar(
    BYTE bOperand,
   CHAR *pch
);

LOUSTATUS RtlByteToInt8(
    BYTE bOperand,
   INT8 *pi8Result
);

LOUSTATUS RtlDWordPtrAdd(
    DWORD_PTR dwAugend,
    DWORD_PTR dwAddend,
   DWORD_PTR *pdwResult
);

LOUSTATUS RtlDWordPtrMult(
    DWORD_PTR dwMultiplicand,
    DWORD_PTR dwMultiplier,
   DWORD_PTR *pdwResult
);

LOUSTATUS RtlDWordPtrSub(
    DWORD_PTR dwMinuend,
    DWORD_PTR dwSubtrahend,
   DWORD_PTR *pdwResult
);

LOUSTATUS RtlInt8Add(
    INT8 i8Augend,
    INT8 i8Addend,
   INT8 *pi8Result
);

LOUSTATUS RtlInt8Mult(
    INT8 i8Multiplicand,
    INT8 i8Multiplier,
   INT8 *pi8Result
);

LOUSTATUS RtlInt8Sub(
    INT8 i8Minuend,
    INT8 i8Subtrahend,
   INT8 *pi8Result
);

LOUSTATUS RtlInt8ToUChar(
    INT8  i8Operand,
   UCHAR *pch
);

LOUSTATUS RtlInt8ToUInt(
    INT8 i8Operand,
   UINT *puResult
);

LOUSTATUS RtlInt8ToUInt8(
    INT8  i8Operand,
   UINT8 *pu8Result
);

LOUSTATUS RtlInt8ToUIntPtr(
    INT8     i8Operand,
   UINT_PTR *puResult
);

LOUSTATUS RtlInt8ToULong(
    INT8  i8Operand,
   ULONG *pulResult
);

LOUSTATUS RtlInt8ToULongLong(
    INT8      i8Operand,
   ULONGLONG *pullResult
);

LOUSTATUS RtlInt8ToULongPtr(
    INT8      i8Operand,
   ULONG_PTR *pulResult
);

LOUSTATUS RtlInt8ToUShort(
    INT8   i8Operand,
   USHORT *pusResult
);

LOUSTATUS RtlIntAdd(
    INT iAugend,
    INT iAddend,
   INT *piResult
);

LOUSTATUS RtlIntMult(
    INT iMultiplicand,
    INT iMultiplier,
   INT *piResult
);

LOUSTATUS RtlIntPtrAdd(
    INT_PTR iAugend,
    INT_PTR iAddend,
   INT_PTR *piResult
);

LOUSTATUS RtlIntPtrMult(
    INT_PTR iMultiplicand,
    INT_PTR iMultiplier,
   INT_PTR *piResult
);

LOUSTATUS RtlIntPtrSub(
    INT_PTR iMinuend,
    INT_PTR iSubtrahend,
   INT_PTR *piResult
);

LOUSTATUS RtlIntPtrToChar(
    INT_PTR iOperand,
   CHAR    *pch
);

LOUSTATUS RtlIntPtrToChar(
    INT_PTR iOperand,
   CHAR    *pch
);

LOUSTATUS RtlIntPtrToInt8(
    INT_PTR iOperand,
   INT8    *pi8Result
);

LOUSTATUS RtlIntPtrToLong(
    INT_PTR iOperand,
   LONG    *plResult
);

LOUSTATUS RtlIntPtrToLongPtr(
    INT_PTR  iOperand,
   LONG_PTR *plResult
);

LOUSTATUS RtlIntPtrToShort(
    INT_PTR iOperand,
   SHORT   *psResult
);

LOUSTATUS RtlIntPtrToUChar(
    INT_PTR iOperand,
   UCHAR   *pch
);

LOUSTATUS RtlIntPtrToUInt(
    INT_PTR iOperand,
   UINT    *puResult
);

LOUSTATUS RtlIntPtrToUInt8(
    INT_PTR iOperand,
   UINT8   *pui8Result
);

LOUSTATUS RtlIntPtrToUIntPtr(
    INT_PTR  iOperand,
   UINT_PTR *puResult
);

LOUSTATUS RtlIntPtrToULong(
    INT_PTR iOperand,
   ULONG   *pulResult
);

LOUSTATUS RtlIntPtrToULongLong(
    INT_PTR   iOperand,
   ULONGLONG *pullResult
);

LOUSTATUS RtlIntPtrToULongPtr(
    INT_PTR   iOperand,
   ULONG_PTR *pulResult
);

LOUSTATUS RtlIntPtrToUShort(
    INT_PTR iOperand,
   USHORT  *pusResult
);

LOUSTATUS RtlIntSub(
   INT iMinuend,
   INT iSubtrahend,
       INT *piResult
);

LOUSTATUS RtlIntToChar(
    INT  iOperand,
   CHAR *pch
);

LOUSTATUS RtlIntToInt8(
    INT  iOperand,
   INT8 *pi8Result
);


LOUSTATUS RtlIntToShort(
    INT   iOperand,
   SHORT *psResult
);

LOUSTATUS RtlIntToUChar(
    INT   iOperand,
   UCHAR *pch
);

LOUSTATUS RtlIntToUInt(
    INT  iOperand,
   UINT *puResult
);

LOUSTATUS RtlIntToUInt8(
    INT   iOperand,
   UINT8 *pui8Result
);

LOUSTATUS RtlIntToULong(
    INT   iOperand,
   ULONG *pulResult
);

LOUSTATUS RtlIntToULongLong(
    INT       iOperand,
   ULONGLONG *pullResult
);

LOUSTATUS RtlIntToUShort(
    INT    iOperand,
   USHORT *pusResult
);

LOUSTATUS RtlLongAdd(
    LONG lAugend,
    LONG lAddend,
   LONG *plResult
);

LOUSTATUS RtlLongLongAdd(
    LONGLONG llAugend,
    LONGLONG llAddend,
   LONGLONG *pllResult
);

LOUSTATUS RtlLongLongMult(
    LONGLONG llMultiplicand,
    LONGLONG llMultiplier,
   LONGLONG *pllResult
);

LOUSTATUS RtlLongLongSub(
    LONGLONG llMinuend,
    LONGLONG llSubtrahend,
   LONGLONG *pllResult
);

LOUSTATUS RtlLongLongToChar(
    LONGLONG llOperand,
   CHAR     *pch
);

LOUSTATUS RtlLongLongToInt(
    LONGLONG llOperand,
   INT      *piResult
);

LOUSTATUS RtlLongLongToInt8(
    LONGLONG llOperand,
   INT8     *pi8Result
);

LOUSTATUS RtlLongLongToIntPtr(
    LONGLONG llOperand,
   INT_PTR  *piResult
);

LOUSTATUS RtlLongLongToLong(
    LONGLONG llOperand,
   LONG     *plResult
);

LOUSTATUS RtlLongLongToLongPtr(
    LONGLONG llOperand,
   LONG_PTR *plResult
);

LOUSTATUS RtlLongLongToShort(
    LONGLONG llOperand,
   SHORT    *psResult
);

LOUSTATUS RtlLongLongToUChar(
    LONGLONG llOperand,
   UCHAR    *pch
);

LOUSTATUS RtlLongLongToUInt(
    LONGLONG llOperand,
   UINT     *puResult
);

LOUSTATUS RtlLongLongToUInt8(
    LONGLONG llOperand,
   UINT8    *pu8Result
);

LOUSTATUS RtlLongLongToULong(
    LONGLONG llOperand,
   ULONG    *pulResult
)
;LOUSTATUS RtlLongLongToULongLong(
    LONGLONG  llOperand,
   ULONGLONG *pullResult
);

LOUSTATUS RtlLongLongToUShort(
    LONGLONG llOperand,
   USHORT   *pusResult
);

LOUSTATUS RtlLongMult(
    LONG lMultiplicand,
    LONG lMultiplier,
   LONG *plResult
);

LOUSTATUS RtlLongPtrAdd(
  LONG_PTR lAugend,
  LONG_PTR lAddend,
  LONG_PTR *plResult
);

LOUSTATUS RtlLongPtrMult(
    LONG_PTR lMultiplicand,
    LONG_PTR lMultiplier,
   LONG_PTR *plResult
);

LOUSTATUS RtlLongPtrSub(
    LONG_PTR lMinuend,
    LONG_PTR lSubtrahend,
   LONG_PTR *plResult
);

LOUSTATUS RtlLongPtrToChar(
    LONG_PTR lOperand,
   CHAR     *pch
);

LOUSTATUS RtlLongPtrToInt(
    LONG_PTR lOperand,
   INT      *piResult
);

LOUSTATUS RtlLongPtrToInt8(
    LONG_PTR lOperand,
   INT8     *pi8Result
);

LOUSTATUS RtlLongPtrToIntPtr(
    LONG_PTR lOperand,
   INT_PTR  *piResult
);

LOUSTATUS RtlLongPtrToLong(
    LONG_PTR lOperand,
   LONG     *plResult
);

LOUSTATUS RtlLongPtrToShort(
    LONG_PTR lOperand,
   SHORT    *psResult
);

LOUSTATUS RtlLongPtrToUChar(
    LONG_PTR lOperand,
   UCHAR    *pch
);

LOUSTATUS RtlLongPtrToUInt(
    LONG_PTR lOperand,
   UINT     *puResult
);

LOUSTATUS RtlLongPtrToUInt8(
    LONG_PTR lOperand,
   UINT8    *pui8Result
);

LOUSTATUS RtlLongPtrToUIntPtr(
    LONG_PTR lOperand,
   UINT_PTR *puResult
);
LOUSTATUS RtlLongPtrToULong(
    LONG_PTR lOperand,
   ULONG    *pulResult
);

LOUSTATUS RtlLongPtrToULongLong(
    LONG_PTR  lOperand,
   ULONGLONG *pullResult
);

LOUSTATUS RtlLongPtrToULongPtr(
    LONG_PTR  lOperand,
   ULONG_PTR *pulResult
);

LOUSTATUS RtlLongPtrToUShort(
    LONG_PTR lOperand,
   USHORT   *pusResult
);

LOUSTATUS RtlLongSub(
    LONG lMinuend,
    LONG lSubtrahend,
   LONG *plResult
);

LOUSTATUS RtlLongToChar(
    LONG lOperand,
   CHAR *pch
);

LOUSTATUS RtlLongToInt(
    LONG lOperand,
   INT  *piResult
);

LOUSTATUS RtlLongToInt8(
    LONG lOperand,
   INT8 *pi8Result
);

LOUSTATUS RtlLongToIntPtr(
    LONG    lOperand,
   INT_PTR *piResult
);

LOUSTATUS RtlLongToShort(
    LONG  lOperand,
   SHORT *psResult
);

LOUSTATUS RtlLongToUChar(
    LONG  lOperand,
   UCHAR *pch
);


LOUSTATUS RtlLongToUInt(
    LONG lOperand,
   UINT *puResult
);

LOUSTATUS RtlLongToUInt8(
  LONG  lOperand,
  UINT8 *pui8Result
);

LOUSTATUS RtlLongToUIntPtr(
    LONG     lOperand,
   UINT_PTR *puResult
);

LOUSTATUS RtlLongToULong(
    LONG  lOperand,
   ULONG *pulResult
);

LOUSTATUS RtlLongToULongLong(
    LONG      lOperand,
   ULONGLONG *pullResult
);

LOUSTATUS RtlLongToULongPtr(
  LONG      lOperand,
  ULONG_PTR *pulResult
);

LOUSTATUS RtlLongToUShort(
    LONG   lOperand,
   USHORT *pusResult
);

LOUSTATUS RtlPtrdiffTAdd(
    ptrdiff_t Augend,
    ptrdiff_t Addend,
   ptrdiff_t *pResult
);

LOUSTATUS RtlPtrdiffTMult(
    ptrdiff_t Multiplicand,
    ptrdiff_t Multiplier,
   ptrdiff_t *pResult
);

LOUSTATUS RtlPtrdiffTSub(
    ptrdiff_t Minuend,
    ptrdiff_t Subtrahend,
   ptrdiff_t *pResult
);

LOUSTATUS RtlShortAdd(
    SHORT sAugend,
    SHORT sAddend,
   SHORT *psResult
);

LOUSTATUS RtlShortMult(
    SHORT sMultiplicand,
    SHORT sMultiplier,
   SHORT *psResult
);

LOUSTATUS RtlShortSub(
    SHORT sMinuend,
    SHORT sSubtrahend,
   SHORT *psResult
);

LOUSTATUS RtlShortToChar(
    SHORT sOperand,
   CHAR  *pch
);

LOUSTATUS RtlShortToDWordPtr(
    SHORT     sOperand,
   DWORD_PTR *pdwResult
);

LOUSTATUS RtlShortToInt8(
    SHORT sOperand,
   INT8  *pi8Result
);

LOUSTATUS RtlShortToUChar(
    SHORT sOperand,
   UCHAR *pch
);

LOUSTATUS RtlShortToUInt(
    SHORT sOperand,
   UINT  *puResult
);

LOUSTATUS RtlShortToUInt8(
   SHORT sOperand,
       UINT8 *pui8Result
);

LOUSTATUS RtlShortToUIntPtr(
    SHORT    sOperand,
   UINT_PTR *puResult
);

LOUSTATUS RtlShortToULong(
    SHORT sOperand,
   ULONG *pulResult
);

LOUSTATUS RtlShortToULongLong(
    SHORT     sOperand,
   ULONGLONG *pullResult
);

LOUSTATUS RtlShortToULongPtr(
    SHORT     sOperand,
   ULONG_PTR *pulResult
);

LOUSTATUS RtlShortToUShort(
    SHORT  sOperand,
   USHORT *pusResult
);

LOUSTATUS RtlSizeTAdd(
    size_t Augend,
    size_t Addend,
   size_t *pResult
);

LOUSTATUS RtlSizeTMult(
    size_t Multiplicand,
    size_t Multiplier,
   size_t *pResult
);

LOUSTATUS RtlSizeTSub(
    size_t Minuend,
    size_t Subtrahend,
   size_t *pResult
);

LOUSTATUS RtlSSIZETAdd(
    SSIZE_T Augend,
    SSIZE_T Addend,
   SSIZE_T *pResult
);

LOUSTATUS RtlSSIZETMult(
    SSIZE_T Multiplicand,
    SSIZE_T Multiplier,
   SSIZE_T *pResult
);

LOUSTATUS RtlSSIZETSub(
    SSIZE_T Minuend,
    SSIZE_T Subtrahend,
   SSIZE_T *pResult
);

LOUSTATUS RtlUInt8Add(
    UINT8 u8Augend,
    UINT8 u8Addend,
   UINT8 *pu8Result
);

LOUSTATUS RtlUInt8Mult(
    UINT8 u8Multiplicand,
    UINT8 u8Multiplier,
   UINT8 *pu8Result
);

LOUSTATUS RtlUInt8Sub(
    UINT8 u8Minuend,
    UINT8 u8Subtrahend,
   UINT8 *pu8Result
);

LOUSTATUS RtlUInt8ToChar(
    UINT8 u8Operand,
   CHAR  *pch
);

LOUSTATUS RtlUInt8ToInt8(
    UINT8 u8Operand,
   INT8  *pi8Result
);

LOUSTATUS RtlUIntAdd(
    UINT uAugend,
    UINT uAddend,
   UINT *puResult
);

LOUSTATUS RtlUIntMult(
    UINT uMultiplicand,
    UINT uMultiplier,
   UINT *puResult
);

LOUSTATUS RtlUIntPtrAdd(
    UINT_PTR uAugend,
    UINT_PTR uAddend,
   UINT_PTR *puResult
);

LOUSTATUS RtlUIntPtrMult(
    UINT_PTR uMultiplicand,
    UINT_PTR uMultiplier,
   UINT_PTR *puResult
);

LOUSTATUS RtlUIntPtrSub(
    UINT_PTR uMinuend,
    UINT_PTR uSubtrahend,
   UINT_PTR *puResult
);

LOUSTATUS RtlUIntPtrToChar(
  UINT_PTR uOperand,
  CHAR     *pch
);

LOUSTATUS RtlUIntPtrToInt(
    UINT_PTR uOperand,
   INT      *piResult
);

LOUSTATUS RtlUIntPtrToInt16(
    UINT_PTR uOperand,
   INT16    *pi16Result
);

LOUSTATUS RtlUIntPtrToInt8(
    UINT_PTR uOperand,
   INT8     *pi8Result
);

LOUSTATUS RtlUIntPtrToIntPtr(
    UINT_PTR uOperand,
   INT_PTR  *piResult
);

LOUSTATUS RtlUIntPtrToLong(
        UINT_PTR uOperand,
   LONG     *plResult
);

LOUSTATUS RtlUIntPtrToLongLong(
    UINT_PTR uOperand,
   LONGLONG *pllResult
);

LOUSTATUS RtlUIntPtrToLongPtr(
    UINT_PTR uOperand,
   LONG_PTR *plResult
);

LOUSTATUS RtlUIntPtrToShort(
    UINT_PTR uOperand,
   SHORT    *psResult
);

LOUSTATUS RtlUIntPtrToUChar(
    UINT_PTR uOperand,
   UCHAR    *pch
);

LOUSTATUS RtlUIntPtrToUInt(
        UINT_PTR uOperand,
   UINT     *puResult
);

LOUSTATUS RtlUIntPtrToUInt16(
    UINT_PTR uOperand,
   UINT16   *pu16Result
);

LOUSTATUS RtlUIntPtrToUInt8(
    UINT_PTR uOperand,
   UINT8    *pu8Result
);

LOUSTATUS RtlUIntPtrToULong(
    UINT_PTR uOperand,
   ULONG    *pulResult
);

LOUSTATUS RtlUIntPtrToUShort(
    UINT_PTR uOperand,
   USHORT   *pusResult
);

LOUSTATUS RtlUIntSub(
    UINT uMinuend,
    UINT uSubtrahend,
   UINT *puResult
);

LOUSTATUS RtlUIntToChar(
    UINT uOperand,
   CHAR *pch
);

LOUSTATUS RtlUIntToInt(
    UINT uOperand,
   INT  *piResult
);

LOUSTATUS RtlUIntToInt8(
    UINT uOperand,
   INT8 *pi8Result
);

LOUSTATUS RtlUIntToIntPtr(
    UINT    uOperand,
   INT_PTR *piResult
);

LOUSTATUS RtlUIntToLong(
    UINT uOperand,
   LONG *plResult
);

LOUSTATUS RtlUIntToLongPtr(
    UINT     uOperand,
   LONG_PTR *plResult
);

LOUSTATUS RtlUIntToShort(
    UINT  uOperand,
   SHORT *psResult
);

LOUSTATUS RtlUIntToUChar(
    UINT  uOperand,
   UCHAR *pch
);

LOUSTATUS RtlUIntToUInt8(
    UINT  uOperand,
   UINT8 *pui8Result
);

LOUSTATUS RtlUIntToUShort(
    UINT   uOperand,
   USHORT *pusResult
);

LOUSTATUS RtlULongAdd(
    ULONG ulAugend,
    ULONG ulAddend,
   ULONG *pulResult
);

LOUSTATUS RtlULongLongAdd(
   ULONGLONG ullAugend,
   ULONGLONG ullAddend,
       ULONGLONG *pullResult
);

LOUSTATUS RtlULongLongMult(
    ULONGLONG ullMultiplicand,
    ULONGLONG ullMultiplier,
   ULONGLONG *pullResult
);

LOUSTATUS RtlULongLongSub(
    ULONGLONG ullMinuend,
    ULONGLONG ullSubtrahend,
   ULONGLONG *pullResult
);

LOUSTATUS RtlULongLongToChar(
    ULONGLONG ullOperand,
   CHAR      *pch
);

LOUSTATUS RtlULongLongToInt(
    ULONGLONG ullOperand,
   INT       *piResult
);

LOUSTATUS RtlULongLongToInt8(
    ULONGLONG ullOperand,
   INT8      *pi8Result
);

LOUSTATUS RtlULongLongToLong(
    ULONGLONG ullOperand,
   LONG      *plResult
);

LOUSTATUS RtlULongLongToLongLong(
    ULONGLONG ullOperand,
   LONGLONG  *pllResult
);

LOUSTATUS RtlULongLongToLongPtr(
    ULONGLONG ullOperand,
   LONG_PTR  *plResult
);

LOUSTATUS RtlULongLongToShort(
    ULONGLONG ullOperand,
   SHORT     *psResult
);

LOUSTATUS RtlULongLongToUChar(
    ULONGLONG ullOperand,
   UCHAR     *pch
);

LOUSTATUS RtlULongLongToUInt(
    ULONGLONG ullOperand,
   UINT      *puResult
);

LOUSTATUS RtlULongLongToUInt8(
    ULONGLONG ullOperand,
   UINT8     *pu8Result
);

LOUSTATUS RtlULongLongToUIntPtr(
    ULONGLONG ullOperand,
   UINT_PTR  *puResult
);

LOUSTATUS RtlULongLongToULong(
   ULONGLONG ullOperand,
       ULONG     *pulResult
);

LOUSTATUS RtlULongLongToULongPtr(
   ULONGLONG ullOperand,
       ULONG_PTR *pulResult
);

LOUSTATUS RtlULongLongToUShort(
    ULONGLONG ullOperand,
   USHORT    *pusResult
);

LOUSTATUS RtlULongMult(
    ULONG ulMultiplicand,
    ULONG ulMultiplier,
   ULONG *pulResult
);

LOUSTATUS RtlULongPtrAdd(
    ULONG_PTR ulAugend,
    ULONG_PTR ulAddend,
   ULONG_PTR *pulResult
);

LOUSTATUS RtlULongPtrMult(
  ULONG_PTR ulMultiplicand,
  ULONG_PTR ulMultiplier,
  ULONG_PTR *pulResult
);

LOUSTATUS RtlULongPtrSub(
    ULONG_PTR ulMinuend,
    ULONG_PTR ulSubtrahend,
   ULONG_PTR *pulResult
);

LOUSTATUS RtlULongPtrToChar(
    ULONG_PTR ulOperand,
   CHAR      *pch
);

LOUSTATUS RtlULongPtrToInt(
    ULONG_PTR ulOperand,
   INT       *piResult
);

LOUSTATUS RtlULongPtrToInt8(
    ULONG_PTR ulOperand,
   INT8      *pi8Result
);

LOUSTATUS RtlULongPtrToIntPtr(
    ULONG_PTR ulOperand,
   INT_PTR   *piResult
);

LOUSTATUS RtlULongPtrToLong(
    ULONG_PTR ulOperand,
   LONG      *plResult
);

LOUSTATUS RtlULongPtrToLongLong(
    ULONG_PTR ulOperand,
   LONGLONG  *pllResult
);

LOUSTATUS RtlULongPtrToLongPtr(
    ULONG_PTR ulOperand,
   LONG_PTR  *plResult
);

LOUSTATUS RtlULongPtrToShort(
    ULONG_PTR ulOperand,
   SHORT     *psResult
);

LOUSTATUS RtlULongPtrToShort(
    ULONG_PTR ulOperand,
   SHORT     *psResult
);

LOUSTATUS RtlULongPtrToUInt(
    ULONG_PTR ulOperand,
   UINT      *puResult
);

LOUSTATUS RtlULongPtrToUInt8(
    ULONG_PTR ulOperand,
   UINT8     *pui8Result
);

LOUSTATUS RtlULongPtrToUIntPtr(
    ULONG_PTR ulOperand,
   UINT_PTR  *puResult
);

LOUSTATUS RtlULongPtrToULong(
    ULONG_PTR ulOperand,
   ULONG     *pulResult
);

LOUSTATUS RtlULongPtrToUShort(
    ULONG_PTR ulOperand,
   USHORT    *pusResult
);

LOUSTATUS RtlULongSub(
    ULONG ulMinuend,
    ULONG ulSubtrahend,
   ULONG *pulResult
);

LOUSTATUS RtlULongToChar(
    ULONG ulOperand,
   CHAR  *pch
);

LOUSTATUS RtlULongToInt(
    ULONG ulOperand,
   INT   *piResult
);

LOUSTATUS RtlULongToInt8(
    ULONG ulOperand,
   INT8  *pi8Result
);

LOUSTATUS RtlULongToIntPtr(
    ULONG   ulOperand,
   INT_PTR *piResult
);

LOUSTATUS RtlULongToLong(
    ULONG ulOperand,
   LONG  *plResult
);

LOUSTATUS RtlULongToLongPtr(
    ULONG    ulOperand,
   LONG_PTR *plResult
);

LOUSTATUS RtlULongToShort(
    ULONG ulOperand,
   SHORT *psResult
);

LOUSTATUS RtlULongToUChar(
    ULONG ulOperand,
   UCHAR *pch
);

LOUSTATUS RtlULongToUInt(
    ULONG ulOperand,
   UINT  *puResult
);

LOUSTATUS RtlULongToUInt8(
    ULONG ulOperand,
   UINT8 *pui8Result
);

LOUSTATUS RtlULongToUIntPtr(
    ULONG    ulOperand,
   UINT_PTR *puiResult
);

LOUSTATUS RtlULongToUShort(
    ULONG  ulOperand,
   USHORT *pusResult
);

LOUSTATUS RtlUShortAdd(
    USHORT usAugend,
    USHORT usAddend,
   USHORT *pusResult
);

LOUSTATUS RtlUShortAdd(
    USHORT usAugend,
    USHORT usAddend,
   USHORT *pusResult
);

LOUSTATUS RtlUShortMult(
    USHORT usMultiplicand,
    USHORT usMultiplier,
   USHORT *pusResult
);

LOUSTATUS RtlUShortSub(
    USHORT usMinuend,
    USHORT usSubtrahend,
   USHORT *pusResult
);

LOUSTATUS RtlUShortToChar(
    USHORT usOperand,
   CHAR   *pch
);

LOUSTATUS RtlUShortToInt8(
    USHORT usOperand,
   INT8   *pi8Result
);

LOUSTATUS RtlUShortToShort(
    USHORT usOperand,
   SHORT  *psResult
);

LOUSTATUS RtlUShortToUChar(
    USHORT usOperand,
   UCHAR  *pch
);

LOUSTATUS RtlUShortToUInt8(
    USHORT usOperand,
   UINT8  *pui8Result
);

#endif