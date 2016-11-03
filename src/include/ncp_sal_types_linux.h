/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*! @file      ncp_sal_types_linux.h
    @brief     OS Specific types are located here. 
*/


#ifndef __NCP_SAL_TYPES_LINUX_H__
#define __NCP_SAL_TYPES_LINUX_H__

/**************************************************************************
* Platform Dependent Type Definitions
**************************************************************************/

#ifdef __KERNEL__

#include <linux/types.h>
#include <linux/wait.h>

/* ========== BEGIN: Addional feature control ============ */

#if !defined(NCP_SWAIT_DISABLE) && defined(CONFIG_PREEMPT_RT_BASE)
#define NCP_USE_SWAIT
#define NCP_USE_HARD_IRQ
#define NCP_USE_RAW_SPINLOCKS
#else   /* NCP_USES_LINUX_PREEMPT_RT */
#undef  NCP_USE_SWAIT
#undef  NCP_USE_HARD_IRQ
#undef  NCP_USE_RAW_SPINLOCKS
#endif /* NCP_SWAIT_DISABLE */

#ifdef CONFIG_PREEMPT_RT_BASE
/* 
 * The Kconfig option CONFIG_IRQ_FORCED_THREADING forces all irq handlers
 * registered via request irq into bottom-half handlers.
 * CONFIG_IRQ_FORCED_THREADING is a prerequisite for CONFIG_PREEMPT_RT_FULL, as
 * is CONFIG_PREEMPT_RT_BASE. But CONFIG_PREEMPT_RT_BASE does not depend on
 * CONFIG_IRQ_FORCED_THREADING. Since our CONFIG_PREEMPT_RT_BASE code assumes
 * the ISRs run threaded, we must check these definitions at compile-time.
 */
#ifndef CONFIG_IRQ_FORCED_THREADING
#error "The RTE's Preempt RT support assumes preemptible ISRs -- i.e., kernels built with CONFIG_PREEMPT_RT_FULL."
#endif

/* 
 * When NCP_USE_HARD_IRQ is defined, the NCAV2 ISR (ncp_dev_intr_ncaV2()) is
 * run in hard IRQ context. This function can acquire a spinlock. If swait
 * queues are disabled, we use normal spinlocks, which can sleep in preempt RT
 * kernels. Acquiring a normal spinlock in the hard IRQ context is a bug
 * ("scheduling while atomic").
 */
#if defined(NCP_SWAIT_DISABLE) && defined(NCP_USE_HARD_IRQ)
#error "The combination of NCP_SWAIT_DISABLE and NCP_USE_HARD_IRQ is not supported at this time."
#endif

#endif /* CONFIG_PREEMPT_RT_BASE */

#undef  NCP_USE_ATOMIC
/* ========== END: Addional feature control ============ */


    typedef __s8   ncp_int8_t;
    typedef __u8   ncp_uint8_t;
    typedef __s16  ncp_int16_t;
    typedef __u16  ncp_uint16_t;
    typedef __s32  ncp_int32_t;
    typedef __u32  ncp_uint32_t;
    typedef __s64  ncp_int64_t;
    typedef __u64  ncp_uint64_t;
    typedef __u8   ncp_bool_t;

    typedef size_t  ncp_size_t;
    typedef ssize_t ncp_ssize_t;

    typedef wait_queue_head_t ncp_waitq_t;

    typedef struct semaphore ncp_sem_t;
    
#else /* __KERNEL__ */

#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <pthread.h>

    typedef struct ncp_sem_st {
        pthread_mutex_t     mutex;
        pthread_mutexattr_t mutexAttr;
    } ncp_sem_t;    

    typedef int8_t     ncp_int8_t;
    typedef int16_t    ncp_int16_t;
    typedef int32_t    ncp_int32_t;

    typedef __uint8_t  ncp_uint8_t;
    typedef __uint16_t ncp_uint16_t;
    typedef __uint32_t ncp_uint32_t;

    typedef __uint8_t  ncp_bool_t;

    typedef int64_t    ncp_int64_t;
    typedef __uint64_t ncp_uint64_t;

    typedef size_t     ncp_size_t;
    typedef ssize_t    ncp_ssize_t;

    typedef void * ncp_waitq_t;
#endif /* __KERNEL__ */


typedef unsigned long spinlock_flags_t;

#define NCP_API extern

/****************************************************
 * Support for 32-bit applications on 64-bit kernels
*****************************************************/
/* 32-bit compatibility support. (Not currently defined)*/


#ifdef NCP_32_BIT_COMPAT

#define NCP_COMPAT_PACKED __attribute__((packed))

#ifdef NCP_64

#define NCP_DECLARE_RAW_ADDR(a) \
    union {                       \
        ncp_uint64_t   a;         \
        ncp_uint64_t __p;         \
    } u_##a
    
#define NCP_DECLARE_RAW_ADDR_AND_ZEROINIT(a) \
    union {                       \
        ncp_uint64_t   a;         \
        ncp_uint64_t __p;         \
    } u_##a = {.__p=0LL}   
    
#define NCP_DECLARE_POINTER(t, a) \
    union {                       \
        t *a;                     \
        ncp_uint64_t __p;         \
    } u_##a

#define NCP_DECLARE_POINTER_ARRAY(t, a, _n) \
    union {                                 \
        t *a[_n];                           \
        ncp_uint64_t __p[_n];               \
    } u_##a

#define NCP_DECLARE_FN_POINTER(t, a) \
    union {                          \
        t a;                         \
        ncp_uint64_t __p;            \
    } u_##a    

#define NCP_DECLARE_HDL(t, a) NCP_DECLARE_FN_POINTER(t, a)

#define NCP_RAW_ADDR(a) u_##a.a

#define NCP_RAW_ADDR_FIXUP(a) \
    a = (__typeof__(a)) ((ncp_uint64_t) a & (ncp_uint64_t) 0x00000000FFFFFFFF)

#define NCP_POINTER(a) u_##a.a

#define NCP_POINTER_64(a) u_##a.__p

#define NCP_POINTER_FIXUP(a) \
    a = (__typeof__(a)) ((ncp_uint64_t) a & (ncp_uint64_t) 0x00000000FFFFFFFF)

#define NCP_POINTER_ARRAY(a, idx) u_##a.a[idx]

#define NCP_DECLARE_LONG(a) \
    union {                 \
        long a;             \
        ncp_uint64_t __p;   \
    } u_##a

#define NCP_LONG(a) u_##a.a

#define NCP_LONG_FIXUP(a) \
    a = a & ((long) 0x00000000FFFFFFFF)

#else

#define NCP_DECLARE_RAW_ADDR(a) \
    union {                       \
        struct {                  \
            ncp_uint32_t a1;      \
            ncp_uint32_t a2;      \
        } s;                      \
        ncp_uint64_t __p;         \
    } u_##a

#define NCP_DECLARE_RAW_ADDR_AND_ZEROINIT(a) \
    union {                       \
        struct {                  \
            ncp_uint32_t a1;      \
            ncp_uint32_t a2;      \
        } s;                      \
        ncp_uint64_t __p;         \
    } u_##a = {.__p=0LL}   
        
#define NCP_DECLARE_POINTER(t, a) \
    union {                       \
        struct {                  \
            t *a1;                \
            t *a2;                \
        } s;                      \
        ncp_uint64_t __p;         \
    } u_##a

#define NCP_DECLARE_POINTER_ARRAY(t, a, _n) \
    union {                                 \
        struct {                            \
            t *a1;                          \
            t *a2;                          \
        } s[_n];                            \
        ncp_uint64_t __p[_n];               \
    } u_##a

#define NCP_DECLARE_FN_POINTER(t, a) \
    union {                          \
        struct {                     \
            t a1;                    \
            t a2;                    \
        } s;                         \
        ncp_uint64_t __p;            \
    } u_##a

#define NCP_DECLARE_HDL(t, a) NCP_DECLARE_FN_POINTER(t, a)

#ifdef NCP_BIG_ENDIAN
#define NCP_RAW_ADDR(a) u_##a.s.a2
#define NCP_POINTER(a) u_##a.s.a2
#define NCP_POINTER_64(a) u_##a.__p
#define NCP_POINTER_ARRAY(a, idx) u_##a.s[idx].a2
#else
#define NCP_RAW_ADDR(a) u_##a.s.a1
#define NCP_POINTER(a) u_##a.s.a1
#define NCP_POINTER_64(a) u_##a.__p
#define NCP_POINTER_ARRAY(a, idx) u_##a.s[idx].a1
#endif

#define NCP_RAW_ADDR_FIXUP(a)

#define NCP_POINTER_FIXUP(a)

#define NCP_DECLARE_LONG(a) \
    union {                 \
        struct {            \
            long a1;        \
            long a2;        \
        } s;                \
        ncp_uint64_t __p;   \
    } u_##a

#ifdef NCP_BIG_ENDIAN
#define NCP_LONG(a) u_##a.s.a2
#else
#define NCP_LONG(a) u_##a.s.a1
#endif

#define NCP_LONG_FIXUP(a)

#endif

    
#else /* NCP_32_BIT_COMPAT */

#ifdef NCP_64
#define NCP_DECLARE_RAW_ADDR(a) ncp_uint64_t a
#define NCP_DECLARE_RAW_ADDR_AND_ZEROINIT(a) ncp_uint64_t a = 0LL
#else
#define NCP_DECLARE_RAW_ADDR(a) ncp_uint32_t a
#define NCP_DECLARE_RAW_ADDR_AND_ZEROINIT(a) ncp_uint32_t a = 0
#endif

#define NCP_COMPAT_PACKED
#define NCP_DECLARE_POINTER(t, a) t *a
#define NCP_DECLARE_POINTER_ARRAY(t, a, _n) t *a[_n]
#define NCP_DECLARE_FN_POINTER(t, a) t a
#define NCP_DECLARE_HDL(t, a) t a
#define NCP_RAW_ADDR(a) a
#define NCP_POINTER(a) a
#define NCP_POINTER_64(a) a
#define NCP_RAW_ADDR_FIXUP(a) 
#define NCP_POINTER_FIXUP(a)
#define NCP_POINTER_ARRAY(a, idx) a[idx]
#define NCP_DECLARE_LONG(a) long a
#define NCP_LONG(a) a
#define NCP_LONG_FIXUP(a)

#endif


#endif /* NCP_SAL_TYPES_LINUX_H */
