/* 
 * Clean-room reimplementation of functionality from Wine project file: <concurrencysal.h>
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

#ifndef CONCURRENCYSAL_HXX
#define CONCURRENCYSAL_HXX

#define _Benign_race_begin_
#define _Benign_race_end_
#define _No_competing_thread_begin_
#define _No_competing_thread_end_

#define _Acquires_exclusive_lock_(lock)
#define _Acquires_lock_(lock)
#define _Acquires_nonreentrant_lock_(lock)
#define _Acquires_shared_lock_(lock)
#define _Analysis_assume_lock_acquired_(lock)
#define _Analysis_assume_lock_released_(lock)
#define _Analysis_assume_lock_held_(lock)
#define _Analysis_assume_lock_not_held_(lock)
#define _Analysis_assume_same_lock_(lock1, lock2)
#define _Analysis_suppress_lock_checking_(lock)
#define _Create_lock_level_(level)
#define _Csalcat1_(x,y)
#define _Csalcat2_(x,y)
#define _Function_ignore_lock_checking_(lock)
#define _Guarded_by_(lock)
#define _Has_lock_kind_(kind)
#define _Has_lock_level_(level)
#define _Interlocked_
#define _Internal_lock_level_order_(a,b)
#define _Lock_level_order_(a,b)
#define _No_competing_thread_
#define _Post_same_lock_(lock1,lock2)
#define _Releases_exclusive_lock_(lock)
#define _Releases_lock_(lock)
#define _Releases_nonreentrant_lock_(lock)
#define _Releases_shared_lock_(lock)
#define _Requires_exclusive_lock_held_(lock)
#define _Requires_shared_lock_held_(lock)
#define _Requires_lock_held_(lock)
#define _Requires_lock_not_held_(lock)
#define _Requires_no_locks_held_
#define _Write_guarded_by_(lock)

#endif