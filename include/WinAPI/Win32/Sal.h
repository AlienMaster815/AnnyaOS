/* 
 * Clean-room reimplementation of functionality from Wine project file: <Sal.h>
 *
 * This file contains original source code written from scratch based on
 * publicly available behavior of the Windows API and documented interfaces.
 *
 * No Wine source code was copied or reused. Behavior is matched only for
 * compatibility.
 *
 * This implementation is NOT a derivative of Wine source code and is not
 * subject to Wine licensing terms.
 */

#ifndef _SAL_H
#define _SAL_H

#define _Always_(exp)

#define _Analysis_assume_(x)
#define _Analysis_noreturn_

#define _At_(Alpha, Beta)
#define _At_buffer(Alpha, Beta, Charlie, Delta)

#define _Check_return_

#define _COM_Outptr_
#define _COM_Outptr_result_maybenull_

#define _Deref_in_range_(Count)
#define _Deref_out_
#define _Deref_out_z_
#define _Deref_out_opt_
#define _Deref_out_opt_z_
#define _Deref_out_range_(x, y)
#define _Deref_post_maybenull_
#define _Deref_post_opt_cap_(Count)
#define _Deref_post_opt_valid_
#define _Deref_post_opt_z_cap_(Count)
#define _Deref_post_valid_
#define _Deref_post_z_
#define _Deref_pre_maybenull_
#define _Deref_pre_z_
#define _Deref_prepost_opt_z_
#define _Deref_ret_z_

#define _Field_range_(Min, Max)

#define _In_
#define _In_bytecount_(Count)
#define _In_bytecount_c_(Count)
#define _In_bytecount_x_(Count)
#define _In_count_(Count)
#define _In_count_c_(Count)
#define _In_count_x_(Count)
#define _In_opt_
#define _In_opt_bytecount_(Count)
#define _In_opt_bytecount_c_(Count)
#define _In_opt_bytecount_x_(Count)
#define _In_opt_count_(Count)
#define _In_opt_ptrdiff_count_(Count)
#define _In_opt_z_
#define _In_opt_z_count_(Count)
#define _In_opt_z_count_c_(Count)
#define _In_opt_z_bytecount_(Count)
#define _In_opt_z_bytecount_c_(Count)
#define _In_ptrdiff_count_(Count)
#define _In_range_(Min, Max)
#define _In_reads_(Count)
#define _In_reads_bytes_(Count)
#define _In_reads_bytes_opt_(Count)
#define _In_reads_opt_(Count)
#define _In_reads_opt_z_(Count)
#define _In_reads_or_z_(Count)
#define _In_reads_or_z_opt_(Count)
#define _In_reads_z_(Count)
#define _In_z_
#define _In_z_bytecount_(Count)
#define _In_z_bytecount_c_(Count)
#define _In_z_count_(Count)
#define _In_z_count_c_(Count)


#define _Inout_
#define _Inout_bytecap_x_(Count)
#define _Inout_cap_(Count)
#define _Inout_cap_c_(Count)
#define _Inout_opt_
#define _Inout_opt_cap_c_(Count)
#define _Inout_opt_z_
#define _Inout_opt_z_bytecap_(Count)
#define _Inout_updates_(Count)
#define _Inout_updates_bytes_(Count)
#define _Inout_updates_bytes_all_opt_(Count)
#define _Inout_updates_bytes_opt_(Count)
#define _Inout_updates_opt_(Count)
#define _Inout_updates_z_(Count)
#define _Inout_updates_opt_z_(Count)
#define _Inout_z_
#define _Inout_z_bytecap_(Count)
#define _Inout_z_cap_(Count)
#define _Inout_z_cap_c_(Count)

#define _Must_inspect_result_

#define _Null_
#define _Null_terminated_

#define _On_failure_(Delta)

#define _Out_
#define _Outptr_
#define _Out_bytecap_(Count)
#define _Out_bytecap_c_(Count)
#define _Out_bytecap_x_(Count)
#define _Out_bytecapcount_(Count)
#define _Out_bytecap_post_bytecount_(Count1, Count2)
#define _Out_cap_(Count)
#define _Out_cap_c_(Count)
#define _Out_cap_m_(Count1, Count2)
#define _Out_cap_x_(Count)
#define _Out_cap_post_count_(Count1, Count2)
#define _Out_opt_
#define _Out_opt_bytecap_(Count)
#define _Out_opt_bytecap_c_(Count)
#define _Out_opt_bytecap_x_(Count)
#define _Out_opt_bytecap_post_bytecount_(Count1, Count2)
#define _Out_opt_bytecapcount_(Count)
#define _Out_opt_cap_(Count)
#define _Out_opt_cap_m_(Count1, Count2)
#define _Out_opt_cap_c_(Count)
#define _Out_opt_cap_x_(Count)
#define _Out_opt_cap_post_count_(Count1, Count2)
#define _Out_opt_ptrdiff_cap_(Count)
#define _Out_opt_z_bytecap_(Count)
#define _Out_opt_z_bytecap_c_(Count)
#define _Out_opt_z_bytecap_x_(Count)
#define _Out_opt_z_bytecap_post_bytecount_(Count1, Count2)
#define _Out_opt_z_cap_(Count)
#define _Out_opt_z_cap_c_(Count)
#define _Out_opt_z_cap_m_(Count1, Count2)
#define _Out_opt_z_cap_x_(Count)
#define _Out_opt_z_cap_post_count_(Count1, Count2)
#define _Out_ptrdiff_cap_(Count)
#define _Out_range_(X, Y)
#define _Out_writes_(Count)
#define _Out_writes_all_(Count)
#define _Out_writes_bytes_(Count)
#define _Out_writes_bytes_all_(Count)
#define _Out_writes_bytes_all_opt_(Count)
#define _Out_writes_bytes_opt_(Count)
#define _Out_writes_bytes_to_(Count1, Count2)
#define _Out_writes_bytes_to_opt_(Count1, Count2)
#define _Out_writes_opt_(Count)
#define _Out_writes_opt_z_(Count)
#define _Out_writes_to_(Count1, Count2)
#define _Out_writes_to_opt_(Count1, Count2)
#define _Out_writes_z_(Count)
#define _Out_z_bytecap_(Count)
#define _Out_z_bytecap_c_(Count)
#define _Out_z_bytecap_x_(Count)
#define _Out_z_bytecap_post_bytecount_(Count1, Count2)
#define _Out_z_cap_(Count)
#define _Out_z_cap_c_(Count)
#define _Out_z_cap_m_(Count1, Count2)
#define _Out_z_cap_x_(Count)
#define _Out_z_cap_post_count_(Count1, Count2)

#define _Outptr_opt_
#define _Outptr_opt_result_buffer_(Count)
#define _Outptr_opt_result_maybenull_
#define _Outptr_opt_result_maybenull_z_
#define _Outptr_opt_result_z_
#define _Outptr_result_buffer_(Count)
#define _Outptr_result_buffer_all_maybenull_(Pointer)
#define _Outptr_result_buffer_maybenull_(Count)
#define _Outptr_result_maybenull_
#define _Outptr_result_maybenull_z_
#define _Outptr_result_nullonfailure_
#define _Outptr_result_z_

#define _Post_count_(Count)
#define _Post_count_c_(Count)
#define _Post_equal_to_(Exp)
#define _Post_invalid_
#define _Post_maybez_
#define _Post_ptr_invalid_
#define _Post_readable_byte_size_(Count)
#define _Post_readable_size_(Count)
#define _Post_satisfies_(Exp)
#define _Post_writable_byte_size_(Count)
#define _Post_writable_size_(Count)
#define _Post_z_

#define _Pre_cap_for_(Count)
#define _Pre_maybenull_
#define _Pre_notnull_
#define _Pre_null_
#define _Pre_opt_z_
#define _Pre_valid_
#define _Pre_writable_size_(Count)
#define _Pre_z_
#define _Prepost_z_

#define _Printf_format_string_
#define _Printf_format_string_params_(Count)

#define _Reserved_

#define _Result_nullonfailure_

#define _Ret_maybenull_
#define _Ret_maybenull_z_
#define _Ret_notnull_
#define _Ret_opt_
#define _Ret_opt_bytecap_(Count)
#define _Ret_opt_bytecap_x_(Count)
#define _Ret_opt_z_cap_(Count)
#define _Ret_range_(Exp, Exp2)
#define _Ret_writes_bytes_maybenull_(Count)
#define _Ret_writes_maybenull_(Count)
#define _Ret_writes_z_(Count)
#define _Ret_z_

#define _Return_type_success_(Count)

#define _Scanf_format_string_
#define _Scanf_format_string_params_(Count)
#define _Scanf_s_format_string_
#define _Scanf_s_format_string_params_(Count)

#define _Success_(Exp)

#define _When_(Exp1, Exp2)

#define __bcount(Size)
#define __bcount_opt(Size)

#define __deref_bcount(Size)
#define __deref_bcount_opt(Size)
#define __deref_ecount(Size)
#define __deref_ecount_opt(Size)
#define __deref_inout
#define __deref_inout_bcount(Size)
#define __deref_inout_bcount_full(Size)
#define __deref_inout_bcount_full_opt(Size)
#define __deref_inout_bcount_nz(Size)
#define __deref_inout_bcount_nz_opt(Size)
#define __deref_inout_bcount_opt(Size)
#define __deref_inout_bcount_part(Size, Length)
#define __deref_inout_bcount_part_opt(Size, Length)
#define __deref_inout_bcount_z(Size)
#define __deref_inout_bcount_z_opt(Size)
#define __deref_inout_ecount(Size)
#define __deref_inout_ecount_full(Size)
#define __deref_inout_ecount_full_opt(Size)
#define __deref_inout_ecount_nz(Size)
#define __deref_inout_ecount_nz_opt(Size)
#define __deref_inout_ecount_opt(Size)
#define __deref_inout_ecount_part(Size, Length)
#define __deref_inout_ecount_part_opt(Size, Length)
#define __deref_inout_ecount_z(Size)
#define __deref_inout_ecount_z_opt(Size)
#define __deref_inout_nz
#define __deref_inout_nz_opt
#define __deref_inout_opt
#define __deref_inout_z
#define __deref_inout_z_opt
#define __deref_opt_bcount(Size)
#define __deref_opt_bcount_opt(Size)
#define __deref_opt_ecount(Size)
#define __deref_opt_ecount_opt(Size)
#define __deref_opt_inout
#define __deref_opt_inout_bcount(Size)
#define __deref_opt_inout_bcount_full(Size)
#define __deref_opt_inout_bcount_full_opt(Size)
#define __deref_opt_inout_bcount_nz(Size)
#define __deref_opt_inout_bcount_nz_opt(Size)
#define __deref_opt_inout_bcount_opt(Size)
#define __deref_opt_inout_bcount_part(Size, Length)
#define __deref_opt_inout_bcount_part_opt(Size, Length)
#define __deref_opt_inout_bcount_z(Size)
#define __deref_opt_inout_bcount_z_opt(Size)
#define __deref_opt_inout_ecount(Size)
#define __deref_opt_inout_ecount_full(Size)
#define __deref_opt_inout_ecount_full_opt(Size)
#define __deref_opt_inout_ecount_nz(Size)
#define __deref_opt_inout_ecount_nz_opt(Size)
#define __deref_opt_inout_ecount_opt(Size)
#define __deref_opt_inout_ecount_part(Size, Length)
#define __deref_opt_inout_ecount_part_opt(Size, Length)
#define __deref_opt_inout_ecount_z(Size)
#define __deref_opt_inout_ecount_z_opt(Size)
#define __deref_opt_inout_nz
#define __deref_opt_inout_nz_opt
#define __deref_opt_inout_opt
#define __deref_opt_inout_z
#define __deref_opt_inout_z_opt
#define __deref_opt_out
#define __deref_opt_out_bcount(Size)
#define __deref_opt_out_bcount_full(Size)
#define __deref_opt_out_bcount_full_opt(Size)
#define __deref_opt_out_bcount_nz_opt(Size)
#define __deref_opt_out_bcount_opt(Size)
#define __deref_opt_out_bcount_part(Size, Length)
#define __deref_opt_out_bcount_part_opt(Size, Length)
#define __deref_opt_out_bcount_z_opt(Size)
#define __deref_opt_out_ecount(Size)
#define __deref_opt_out_ecount_full(Size)
#define __deref_opt_out_ecount_full_opt(Size)
#define __deref_opt_out_ecount_nz_opt(Size)
#define __deref_opt_out_ecount_opt(Size)
#define __deref_opt_out_ecount_part(Size, Length)
#define __deref_opt_out_ecount_part_opt(Size, Length)
#define __deref_opt_out_ecount_z_opt(Size)
#define __deref_opt_out_nz_opt
#define __deref_opt_out_opt
#define __deref_opt_out_z
#define __deref_opt_out_z_opt
#define __deref_out
#define __deref_out_bcount(Size)
#define __deref_out_bcount_full(Size)
#define __deref_out_bcount_full_opt(Size)
#define __deref_out_bcount_nz(Size)
#define __deref_out_bcount_nz_opt(Size)
#define __deref_out_bcount_opt(Size)
#define __deref_out_bcount_part(Size, Length)
#define __deref_out_bcount_part_opt(Size, Length)
#define __deref_out_bcount_z(Size)
#define __deref_out_bcount_z_opt(Size)
#define __deref_out_ecount(Size)
#define __deref_out_ecount_full(Size)
#define __deref_out_ecount_full_opt(Size)
#define __deref_out_ecount_nz(Size)
#define __deref_out_ecount_nz_opt(Size)
#define __deref_out_ecount_opt(Size)
#define __deref_out_ecount_part(Size, Length)
#define __deref_out_ecount_part_opt(Size, Length)
#define __deref_out_ecount_z(Size)
#define __deref_out_ecount_z_opt(Size)
#define __deref_out_nz
#define __deref_out_nz_opt
#define __deref_out_opt
#define __deref_out_z
#define __deref_out_z_opt

#define __ecount(Size)
#define __ecount_opt(Size)

#define __in_bcount(Size)
#define __in_bcount_nz(Size)
#define __in_bcount_nz_opt(Size)
#define __in_bcount_opt(Size)
#define __in_bcount_z(Size)
#define __in_bcount_z_opt(Size)
#define __in_ecount(Size)
#define __in_ecount_nz(Size)
#define __in_ecount_nz_opt(Size)
#define __in_ecount_opt(Size)
#define __in_ecount_z(Size)
#define __in_ecount_z_opt(Size)
#define __in_nz
#define __in_nz_opt
#define __in_opt
#define __in_z
#define __in_z_opt
#define __inout
#define __inout_bcount(Size)
#define __inout_bcount_full(Size)
#define __inout_bcount_full_opt(Size)
#define __inout_bcount_nz(Size)
#define __inout_bcount_nz_opt(Size)
#define __inout_bcount_opt(Size)
#define __inout_bcount_part(Size, Length)
#define __inout_bcount_part_opt(Size, Length)
#define __inout_bcount_z(Size)
#define __inout_bcount_z_opt(Size)
#define __inout_ecount(Size)
#define __inout_ecount_full(Size)
#define __inout_ecount_full_opt(Size)
#define __inout_ecount_nz(Size)
#define __inout_ecount_nz_opt(Size)
#define __inout_ecount_opt(Size)
#define __inout_ecount_part(Size, Length)
#define __inout_ecount_part_opt(Size, Length)
#define __inout_ecount_z(Size)
#define __inout_ecount_z_opt(Size)
#define __inout_ecount_z_opt(Size)
#define __inout_nz
#define __inout_nz_opt
#define __inout_opt
#define __inout_z
#define __inout_z_opt

#define __out_bcount(Size)
#define __out_bcount_full(Size)
#define __out_bcount_full_opt(Size)
#define __out_bcount_full_z(Size)
#define __out_bcount_full_z_opt(Size)
#define __out_bcount_nz(Size)
#define __out_bcount_nz_opt(Size)
#define __out_bcount_opt(Size)
#define __out_bcount_part(Size, Length)
#define __out_bcount_part_opt(Size, Length)
#define __out_bcount_part_z(Size, Length)
#define __out_bcount_part_z_opt(Size, Length)
#define __out_bcount_z(Size)
#define __out_bcount_z_opt(Size)
#define __out_ecount(Size)
#define __out_ecount_full(Size)
#define __out_ecount_full_opt(Size)
#define __out_ecount_full_z(Size)
#define __out_ecount_full_z_opt(Size)
#define __out_ecount_nz(Size)
#define __out_ecount_nz_opt(Size)
#define __out_ecount_opt(Size)
#define __out_ecount_part(Size, Length)
#define __out_ecount_part_opt(Size, Length)
#define __out_ecount_part_z(Size, Length)
#define __out_ecount_part_z_opt(Size, Length)
#define __out_ecount_z(Size)
#define __out_ecount_z_opt(Size)
#define __out_nz
#define __out_nz_opt
#define __out_opt
#define __out_z
#define __out_z_opt

#endif