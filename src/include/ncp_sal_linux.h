/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                        *
 **                                                                       *
 **************************************************************************/

/*! @file      ncp_sal_linux.h
    @brief     OS Specific definitions are located here. 
*/


#ifndef __NCP_SAL_LINUX_H__
#define __NCP_SAL_LINUX_H__

#ifdef __KERNEL__

#include <linux/module.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/interrupt.h>
#include <linux/irq.h>  /* TEST */
#include <linux/sched.h>
#include <linux/version.h>

#if defined(NCP_USE_SWAIT)
#include <linux/wait-simple.h>
#endif /* NCP_USE_SWAIT */

#include <linux/version.h>

#if defined(NCP_USE_RAW_SPINLOCKS) && (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
#include <linux/atomic.h>
#define NCP_RAW_SPINLOCK_BH_BUG
#else
#undef NCP_USE_RAW_SPINLOCKS
#undef NCP_RAW_SPINLOCK_BH_BUG
#endif

#ifdef NCP_DEV_PLB
#include <asm/dcr.h>
#endif

#else /* !#ifdef __KERNEL__ */

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/errno.h>
#include <unistd.h>
#include <sys/mman.h>
#include <syscall.h>
#include <inttypes.h>

#endif /* #ifdef __KERNEL__ */

#ifdef __cplusplus
extern "C" { 
#endif

#define NCP_SLEEP_POLL_INTERVAL 0

#if defined(NCP_KERNEL) && defined(NCP_USE_SWAIT)
typedef struct swait_head  ncp_task_isr_wait_primitive_t;
#else
typedef ncp_waitq_t ncp_task_isr_wait_primitive_t;
#endif

/*
 * For use with higher resolution monotonic timers
 */
typedef struct {
    long        tv_sec;
    long        tv_usec;    
} ncp_timespec_us_t;
NCP_API void       ncp_hr_gettime_us(ncp_timespec_us_t *timespec);
NCP_API int        ncp_hr_time_compare(ncp_timespec_us_t *timespecStart_us, ncp_timespec_us_t *timespecEnd_us);
NCP_API void       ncp_hr_addtime_us(ncp_timespec_us_t *timespecStart_us, ncp_timespec_us_t *timespecEnd_us, ncp_uint64_t uSecs);

#if defined(NCP_USE_NVM) && !defined(NCP_NVM_VADDR)
/* 
 * For linux builds, the NCP_NVM_VADDR is now defined in the makefile.
 * Make sure that it really is defined
 */
#error "linux NCP_NVM_VADDR not defined - invalid RTE target ?!?"

#endif /* #if defined(NCP_USE_NVM) && !defined(NCP_NVM_VADDR) */

#define ncp_sprint_uint64(str, v)                 sprintf(str, "%"PRIu64, v);
#define ncp_sprint_int64(str, v)                  sprintf(str, "%"PRId64, v);
#define ncp_sprint_hexuint64(str, v)              sprintf(str, "%"PRIx64, v);
#define ncp_sprint_uint64_format(str, fmt, v)     sprintf(str, fmt PRIu64, v);
#define ncp_sprint_int64_format(str, fmt, v)      sprintf(str, fmt PRId64, v);
#define ncp_sprint_hexuint64_format(str, fmt, v)  sprintf(str, fmt PRIx64, v);

#ifdef __KERNEL__

#ifndef NCP_KERNEL
#define NCP_KERNEL __KERNEL__
#endif

#else

#define NCP_EXPORT_SYMBOL(sym);

#endif /* #ifdef __KERNEL__ */

#ifdef __KERNEL__

#define NCP_EXPORT_SYMBOL(sym) EXPORT_SYMBOL(sym)

typedef irqreturn_t ncp_irqreturn_t;


typedef spinlock_t          ncp_spinlock_t;
typedef spinlock_flags_t    ncp_spinlock_flags_t;

#ifdef NCP_USE_RAW_SPINLOCKS
typedef raw_spinlock_t          ncp_raw_spinlock_t;
typedef unsigned long           ncp_raw_spinlock_flags_t;
#else /* NCP_USE_RAW_SPINLOCKS */
typedef ncp_spinlock_t          ncp_raw_spinlock_t;
typedef ncp_spinlock_flags_t    ncp_raw_spinlock_flags_t;
#endif  /* NCP_USE_RAW_SPINLOCKS */

#ifdef NCP_DEV_USE_BSP_LOCK
typedef raw_spinlock_t      ncp_bsp_spinlock_t;  
typedef unsigned long   ncp_bsp_spinlock_flags_t;      
#else
typedef ncp_raw_spinlock_t     ncp_bsp_spinlock_t;  
typedef ncp_raw_spinlock_flags_t ncp_bsp_spinlock_flags_t;      
#endif


typedef atomic_t ncp_atomic_t;
#define NCP_ATOMIC_READ(_atomicVar)         atomic_read(&(_atomicVar))
#define NCP_ATOMIC_INC(_atomicVar)          atomic_inc(&(_atomicVar))
#define NCP_ATOMIC_INC_RETURN(_atomicVar)   atomic_inc_return(&(_atomicVar))
#define NCP_ATOMIC_DEC(_atomicVar)          atomic_dec(&(_atomicVar))

#define NCP_TASK_ISR_EVENT_WAIT_TIMEOUT_VAL (HZ)
#define NCP_SE_FEM_ISR_EVENT_WAIT_TIMEOUT_VAL NCP_TASK_ISR_EVENT_WAIT_TIMEOUT_VAL
#define NCP_TIMER_ISR_EVENT_WAIT_TIMEOUT_VAL NCP_TASK_ISR_EVENT_WAIT_TIMEOUT_VAL

#define NCP_TASK_ISR_WAIT_OBJECT_SUPPLEMENT_DECL(_x)

/*
 * Linux note: some RTE components use wait queues even if swait is available!
 */
#define NCP_WAITQ_ALLOC(_pWaitPrimitive) \
    do { \
        *(_pWaitPrimitive) = ncp_malloc(sizeof(wait_queue_head_t)); \
        init_waitqueue_head((wait_queue_head_t *)*(_pWaitPrimitive)); \
    } while (0)

#define NCP_WAITQ_FREE(_pWaitPrimitive) \
    do { \
        if (_pWaitPrimitive != NULL) { \
            ncp_free(_pWaitPrimitive); \
        } \
    } while (0)
    
#define NCP_WAITQ_WAIT(_pWaitPrimitive, cond)  \
    (_pWaitPrimitive ? wait_event_interruptible(*(_pWaitPrimitive), cond) : -1)

#define NCP_WAITQ_WAIT_TIMEOUT(_pWaitPrimitive, cond, timeout) \
    (_pWaitPrimitive ? wait_event_interruptible_timeout(( *(_pWaitPrimitive)), cond, timeout) : -1)

#define NCP_WAITQ_WAKEUP(_pWaitPrimitive) \
    (_pWaitPrimitive ? wake_up_interruptible_all((wait_queue_head_t *)(_pWaitPrimitive)) : -1)

 
/* Use simple wait if preempt-RT linux */    
#ifdef NCP_USE_SWAIT /*  ======================================== */

#define NCP_TASK_ISR_WAITOBJ_ALLOC(_pWaitPrimitive) \
    do { \
        *(_pWaitPrimitive) = ncp_malloc(sizeof(struct swait_head)); \
        init_swait_head((struct swait_head *)*(_pWaitPrimitive)); \
    } while (0)

#define NCP_TASK_ISR_WAITOBJ_FREE(_pWaitPrimitive) \
    do { \
        if (_pWaitPrimitive != NULL) { \
            ncp_free(_pWaitPrimitive); \
        } \
    } while (0)

#define NCP_TASK_ISR_EVENT_WAKEUP(_pWaitObj) \
    swait_wake_all(((_pWaitObj)->pWaitPrimitive)) 
    
#define NCP_TASK_ISR_EVENT_WAIT_INTERRUPTIBLE(_pWaitObj, _cond) \
({                                                          \
     swait_event_interruptible((*(_pWaitObj)->pWaitPrimitive), (_cond)); \
}) 
    
#else /* NCP_USE_SWAIT ======================================== */

#define NCP_TASK_ISR_WAITOBJ_ALLOC(_pWaitPrimitive) NCP_WAITQ_ALLOC(_pWaitPrimitive)

#define NCP_TASK_ISR_WAITOBJ_FREE(_pWaitPrimitive) NCP_WAITQ_FREE(_pWaitPrimitive)
      
#define NCP_TASK_ISR_EVENT_WAKEUP(_pWaitObj)                        \
{                                                                   \
   if (_pWaitObj) { NCP_WAITQ_WAKEUP((_pWaitObj)->pWaitPrimitive); }\
}

#define NCP_TASK_ISR_EVENT_WAIT_INTERRUPTIBLE(_pWaitObj, _cond) \
   NCP_WAITQ_WAIT(((_pWaitObj)->pWaitPrimitive), (_cond)) 

#endif /* NCP_USE_SWAIT ======================================== */
    
#define NCP_TASK_ISR_EVENT_SET_OWNER(_pWaitObj)

#define NCP_SIGNAL_PENDING() \
    (signal_pending(current))

#define NCP_DEV_IRQ_MASK(dev, irq) \
    if (dev->irqMask) dev->irqMask(dev, irq) 

#define NCP_DEV_ISR_EOI_FN(irq)

void
ncp_edev_cleanup_isr_info(ncp_uint32_t devNum);

void
ncp_edev_init_isr_info(ncp_uint32_t devNum, ncp_uint8_t grp, void * intrData);

void
ncp_edev_wakeup_thread(void *pIsrInfoOSspecific, int wakeupType);

#define NCP_CLEANUP_ISR_INFO(_devNum) \
    ncp_edev_cleanup_isr_info(_devNum)

#define NCP_INIT_ISR_INFO(_devNum, _grp, _intrData) \
    ncp_edev_init_isr_info(_devNum, _grp, (_intrData))

#define NCP_INTERRUPT_DISABLE(intLevel) \
    local_irq_save(intLevel)

#define NCP_INTERRUPT_ENABLE(intLevel) \
    local_irq_restore(intLevel)


#define NCP_SPINLOCK_FLAGS(flags) \
    ncp_spinlock_flags_t    flags = 0

#define NCP_SPINLOCK_INTERRUPT_DISABLE(pSem, flags) \
    spin_lock_irqsave(pSem, flags)

#define NCP_SPINLOCK_INTERRUPT_ENABLE(pSem, flags) \
    spin_unlock_irqrestore(pSem, flags)

#define NCP_SPINLOCK_SW_FLAGS(flags)

#define NCP_SPINLOCK_SW_INTERRUPT_DISABLE(pSem, flags) \
    spin_lock_bh(pSem)

#define NCP_SPINLOCK_SW_INTERRUPT_ENABLE(pSem, flags) \
    spin_unlock_bh(pSem)

#define NCP_SPINLOCK_INIT(pSpinlock) \
    spin_lock_init(pSpinlock)

#define NCP_SPINLOCK_LOCK(pSpinlock) \
    spin_lock(pSpinlock)

#define NCP_SPINLOCK_UNLOCK(pSpinlock) \
    spin_unlock(pSpinlock)
   
   
#ifdef NCP_USE_RAW_SPINLOCKS

#define NCP_RAW_SPINLOCK_FLAGS(flags) \
    ncp_raw_spinlock_flags_t flags = 0

#define NCP_RAW_SPINLOCK_SW_FLAGS(flags) 

#define NCP_RAW_SPINLOCK_INTERRUPT_DISABLE(pSem, flags) \
    raw_spin_lock_irqsave(pSem, flags)

#define NCP_RAW_SPINLOCK_INTERRUPT_ENABLE(pSem, flags) \
    raw_spin_unlock_irqrestore(pSem, flags)

#ifdef NCP_RAW_SPINLOCK_BH_BUG
#define NCP_RAW_SPINLOCK_SW_INTERRUPT_DISABLE(pSem, flags)  \
    raw_spin_lock(pSem)    
#define NCP_RAW_SPINLOCK_SW_INTERRUPT_ENABLE(pSem, flags) \
    raw_spin_unlock(pSem)          
#else /* NCP_RAW_SPINLOCK_BH_BUG */
#define NCP_RAW_SPINLOCK_SW_INTERRUPT_DISABLE(pSem, flags)  \
    raw_spin_lock_bh(pSem)
#define NCP_RAW_SPINLOCK_SW_INTERRUPT_ENABLE(pSem, flags) \
    raw_spin_unlock_bh(pSem)     
#endif  /* NCP_RAW_SPINLOCK_BH_BUG */  

#define NCP_RAW_SPINLOCK_INIT(pSpinlock) \
    raw_spin_lock_init(pSpinlock)

#define NCP_RAW_SPINLOCK_LOCK(pSpinlock) \
    raw_spin_lock(pSpinlock)

#define NCP_RAW_SPINLOCK_UNLOCK(pSpinlock) \
    raw_spin_unlock(pSpinlock)

#else  /* NCP_USE_RAW_SPINLOCKS */  

#define NCP_RAW_SPINLOCK_FLAGS(flags) \
    NCP_SPINLOCK_FLAGS(flags)

#define NCP_RAW_SPINLOCK_SW_FLAGS(flags) \
    NCP_SPINLOCK_SW_FLAGS(flags) 

#define NCP_RAW_SPINLOCK_INTERRUPT_DISABLE(pSem, flags) \
    NCP_SPINLOCK_INTERRUPT_DISABLE(pSem, flags)

#define NCP_RAW_SPINLOCK_INTERRUPT_ENABLE(pSem, flags) \
    NCP_SPINLOCK_INTERRUPT_ENABLE(pSem, flags)

#define NCP_RAW_SPINLOCK_SW_INTERRUPT_DISABLE(pSem, flags)  \
    NCP_SPINLOCK_SW_INTERRUPT_DISABLE(pSem, flags)  
    
#define NCP_RAW_SPINLOCK_SW_INTERRUPT_ENABLE(pSem, flags) \
    NCP_SPINLOCK_SW_INTERRUPT_ENABLE(pSem, flags)     

#define NCP_RAW_SPINLOCK_INIT(pSpinlock) \
    NCP_SPINLOCK_INIT(pSpinlock) 

#define NCP_RAW_SPINLOCK_LOCK(pSpinlock) \
    NCP_SPINLOCK_LOCK(pSpinlock)

#define NCP_RAW_SPINLOCK_UNLOCK(pSpinlock) \
    NCP_SPINLOCK_UNLOCK(pSpinlock) 
    
#endif /* NCP_USE_RAW_SPINLOCKS */
    
/* 
 * macros for spinlocks that are shared with the BSP
 */
#ifdef NCP_DEV_USE_BSP_LOCK
#define NCP_BSP_SPINLOCK_INIT(pSpinlock)
#define NCP_BSP_SPINLOCK_FLAGS(flags) \
    unsigned long flags = 0

#define NCP_BSP_SPINLOCK_SW_FLAGS(flags) 

#define NCP_BSP_SPINLOCK_INTERRUPT_DISABLE(pSem, flags) \
    raw_spin_lock_irqsave(pSem, flags)

#define NCP_BSP_SPINLOCK_INTERRUPT_ENABLE(pSem, flags) \
    raw_spin_unlock_irqrestore((raw_spinlock_t *) pSem, flags)

#define NCP_BSP_SPINLOCK_LOCK(pSpinlock) \
    raw_spin_lock(pSpinlock)

#define NCP_BSP_SPINLOCK_UNLOCK(pSpinlock) \
    raw_spin_unlock(pSpinlock)

#else
#define NCP_BSP_SPINLOCK_INIT(pSpinlock) \
    NCP_RAW_SPINLOCK_INIT(pSpinlock)
#define NCP_BSP_SPINLOCK_FLAGS(flags) \
    NCP_RAW_SPINLOCK_FLAGS(flags)

#define NCP_BSP_SPINLOCK_SW_FLAGS(flags) 

#define NCP_BSP_SPINLOCK_INTERRUPT_DISABLE(pSem, flags) \
    NCP_RAW_SPINLOCK_INTERRUPT_DISABLE(pSem, flags) 

#define NCP_BSP_SPINLOCK_INTERRUPT_ENABLE(pSem, flags) \
    NCP_RAW_SPINLOCK_INTERRUPT_ENABLE(pSem, flags)

#define NCP_BSP_SPINLOCK_LOCK(pSpinlock) \
    NCP_RAW_SPINLOCK_LOCK(pSpinlock)

#define NCP_BSP_SPINLOCK_UNLOCK(pSpinlock) \
    NCP_RAW_SPINLOCK_UNLOCK(pSpinlock)

#endif




#define NCP_RESCHEDULE() \
    schedule()

#define NCP_CAT_DELAY_SETUP
#define NCP_CAT_DELAY_PQM()
#define NCP_CAT_DELAY_FEMAC()
#define NCP_CAT_DELAY_REGISTER()
#define NCP_CAT_DELAY_REGISTER_ROW()

#define NCP_IN_INTERRUPT() \
    in_interrupt()

ncp_st_t
ncp_isr_register(
    ncp_uint32_t devNum, 
    ncp_uint32_t irq, 
    ncp_uint32_t type,
    const char *name,
    void *isrFn, 
    void *isrArg, 
    ncp_uint32_t *pVirq);

int
ncp_isr_unregister(ncp_uint32_t irq, void *arg);

#define NCP_ISR_REGISTER(devNum, irq, type, name, isrFn, isrArg, pVirtIrq) \
        ncp_isr_register(devNum, irq, type, name, isrFn, isrArg, pVirtIrq)
   
#define NCP_ISR_UNREGISTER(irq, arg) \
        ncp_isr_unregister(irq, arg)        

#define NCP_IRQ_TYPE_LEVEL_HIGH  IRQ_TYPE_LEVEL_HIGH
#define NCP_IRQ_TYPE_EDGE_RISING IRQ_TYPE_EDGE_RISING

extern int ncp_trace_level;
extern int ncp_i2c_mode;

    /*
     * NCP_MSG
     *
     *   Print a message to the system console.
     */
#define NCP_MSG(type, ...)                 \
    do {                                            \
        if ((type) & ncp_trace_level) {             \
            if ((type) == NCP_MSG_ERROR) {          \
                printk(KERN_ERR "ncp: ERROR: ");    \
            } else {                                \
                printk(KERN_WARNING "ncp: ");       \
            }                                       \
            printk(__VA_ARGS__);                   \
        }                                           \
    } while (0)

#define ncp_udelay(n) udelay(n)

#define ncp_get_pid()   \
    current->pid

#else /* !#ifdef __KERNEL__ */


#if 0 /* not supported for user mode */
typedef ncp_uint32_t ncp_atomic_t;
#define NCP_ATOMIC_READ(_atomicVar)         ncp_atomic_read(_atomicVar)
#define NCP_ATOMIC_INC(_atomicVar)          ncp_atomic_inc(_atomicVar)
#define NCP_ATOMIC_INC_RETURN(_atomicVar)   ncp_atomic_inc_return(_atomicVar)
#define NCP_ATOMIC_DEC(_atomicVar)          ncp_atomic_dec(_atomicVar)
#endif

#ifndef NCP_SPINLOCK_DEFINED
    typedef void *          ncp_spinlock_t;
    typedef unsigned long   ncp_spinlock_flags_t;
    
    typedef void *          ncp_raw_spinlock_t;  
    typedef unsigned long   ncp_raw_spinlock_flags_t;      

    typedef void *          ncp_bsp_spinlock_t;  
    typedef unsigned long   ncp_bsp_spinlock_flags_t;      
    #define NCP_SPINLOCK_DEFINED
#endif


#ifdef SUPPORT_SPINLOCK_ALLOC_FNS
#define NCP_SPINLOCK_ALLOC() \
    ncp_malloc(sizeof(ncp_spinlock_t))
#define NCP_SPINLOCK_FREE(pSpinlock) \
    ncp_free(pSpinlock)
    
#define NCP_RAW_SPINLOCK_ALLOC() \
    ncp_malloc(sizeof(ncp_raw_spinlock_t))
#define NCP_RAW_SPINLOCK_FREE(pSpinlock) \
    ncp_free(pSpinlock)    
#endif

/* No flags required for user mode */
#define NCP_SPINLOCK_FLAGS(flags)
#define NCP_RAW_SPINLOCK_FLAGS(flags)

#define NCP_SPINLOCK_SW_FLAGS(flags)
#define NCP_RAW_SPINLOCK_SW_FLAGS(flags)


#define NCP_SPINLOCK_INTERRUPT_DISABLE(pSem, flags) 
#define NCP_RAW_SPINLOCK_INTERRUPT_DISABLE(pSem, flags) 
   
#define NCP_SPINLOCK_INTERRUPT_ENABLE(pSem, flags)
#define NCP_RAW_SPINLOCK_INTERRUPT_ENABLE(pSem, flags)

#define NCP_SPINLOCK_SW_INTERRUPT_DISABLE(pSem, flags) \
    spin_lock_bh(pSem)
#define NCP_RAW_SPINLOCK_SW_INTERRUPT_DISABLE(pSem, flags) \
    NCP_SPINLOCK_SW_INTERRUPT_DISABLE(pSem, flags) 

#define NCP_SPINLOCK_SW_INTERRUPT_ENABLE(pSem, flags) \
    spin_unlock_bh(pSem)
#define NCP_RAW_SPINLOCK_SW_INTERRUPT_ENABLE(pSem, flags) \
    NCP_SPINLOCK_SW_INTERRUPT_ENABLE(pSem, flags)

#define NCP_SPINLOCK_INIT(pSpinlock) \
    spin_lock_init(pSpinlock)
#define NCP_RAW_SPINLOCK_INIT(pSpinlock) \
    NCP_SPINLOCK_INIT(pSpinlock)

#define NCP_SPINLOCK_LOCK(pSpinlock)

#define NCP_RAW_SPINLOCK_LOCK(pSpinlock) \
    NCP_SPINLOCK_LOCK(pSpinlock)

#define NCP_SPINLOCK_UNLOCK(pSpinlock)

#define NCP_RAW_SPINLOCK_UNLOCK(pSpinlock) \
    NCP_SPINLOCK_UNLOCK(pSpinlock)

#define NCP_SPINLOCK_TRYLOCK(pSpinlock) \
    spin_trylock(pSpinlock)
#define NCP_RAW_SPINLOCK_TRYLOCK(pSpinlock) \
    NCP_SPINLOCK_TRYLOCK(pSpinlock)
    
#define NCP_BSP_SPINLOCK_INIT(pSpinlock)
#define NCP_BSP_SPINLOCK_FLAGS(flags)
#define NCP_BSP_SPINLOCK_SW_FLAGS(flags) 
#define NCP_BSP_SPINLOCK_INTERRUPT_DISABLE(pSem, flags)
#define NCP_BSP_SPINLOCK_INTERRUPT_ENABLE(pSem, flags)
#define NCP_BSP_SPINLOCK_LOCK(pSpinlock)
#define NCP_BSP_SPINLOCK_UNLOCK(pSpinlock)

extern int ncp_trace_level;

#define NCP_MSG(type, ...) \
    do { \
        if ((type) & ncp_trace_level) { \
            printf(__VA_ARGS__); \
        }    \
    } while (0)

#define NCP_MSGRAW(...) \
    do { \
       printf(__VA_ARGS__); \
    } while (0)

#define NCP_LOGDATA \
    NCP_MSGRAW


NCP_API ncp_st_t ncp_screen_startup(int *lines, int *cols);

NCP_API ncp_uint16_t ncp_ntohs(ncp_uint16_t v);
NCP_API ncp_uint16_t ncp_htons(ncp_uint16_t v);
NCP_API ncp_uint32_t ncp_ntohl(ncp_uint32_t v);
NCP_API ncp_uint32_t ncp_htonl(ncp_uint32_t v);
NCP_API ncp_uint64_t ncp_ntohll(ncp_uint64_t v);
NCP_API ncp_uint64_t ncp_htonll(ncp_uint64_t v);

typedef struct {
    long        tv_sec;
    long        tv_nsec;
} ncp_timespec_t;

NCP_API void ncp_gettime(ncp_timespec_t *timespec);
NCP_API double ncp_gettime_elapsed(ncp_timespec_t *t1, ncp_timespec_t *t2);



#include "ncp_status.h"

#define ncp_sem_alloc() \
    ncp_malloc(sizeof(ncp_sem_t))

#define ncp_sem_free(pMutex) \
    ncp_free(pMutex)

#define ncp_get_pid()   \
    getpid()

#define ncp_sleep(s)    \
    sleep(s)

#define ncp_udelay(n) ncp_usleep(n)

int ncp_create_exec_process(const char *name, 
                char *arg1, char *arg2, char *arg3, char *arg4, char *arg5);



 
ncp_st_t ncp_daemonize_self(void);

#define NCP_DAEMONIZE_SELF() ncp_daemonize_self()

#define NCP_DAEMON_EXIT()

#endif /* #ifdef __KERNEL__ */


/*!
 * @fn ncp_sem_init(ncp_sem_t *sem, ncp_int32_t shared, ncp_uint32_t value)
 */
NCP_API ncp_st_t
ncp_sem_init(ncp_sem_t *sem, ncp_int32_t shared, ncp_uint32_t value);

/*!
 * @fn ncp_sem_post(ncp_sem_t *sem)
 */
NCP_API ncp_st_t
ncp_sem_post(ncp_sem_t *sem);

/*!
 * @fn ncp_sem_wait(ncp_sem_t *sem)
 */
NCP_API ncp_st_t
ncp_sem_wait(ncp_sem_t *sem);

/*!
 * @fn ncp_sem_trywait(ncp_sem_t *sem)
 */
NCP_API ncp_st_t
ncp_sem_trywait(ncp_sem_t *sem);

/*!
 * @fn ncp_sem_destroy(ncp_sem_t *sem)
 */
NCP_API ncp_st_t
ncp_sem_destroy(ncp_sem_t *sem);
    /*
     * NCP_LOG
     *
     *   Print a message to the system log device and/or console. This
     *   interface is callable from interrupt level.
     */
#define NCP_LOG \
    NCP_MSG

#if ((defined(PROC_ARMA15) || defined(PROC_ARMA57)) && defined(NCP_BIG_ENDIAN))
#define in_8(addr)    ({ u8 __v = (*(__force volatile u8 *) (addr)); __v; })
#define in_be16(addr) ({ u16 __v = (*(__force volatile u16 *) (addr)); __v; })
#define in_be32(addr) ({ u32 __v = (*(__force volatile u32 *) (addr)); __v; })
#define in_le16(addr) ({ u16 __v = le16_to_cpu(*(__force volatile __le16 *) (addr)); __v; })
#define in_le32(addr) ({ u32 __v = le32_to_cpu(*(__force volatile __le32 *) (addr)); __v; })

#define out_8(addr,b)    (void)((*(__force volatile u8 *) (addr)) = (b))
#define out_be16(addr,w) (void)((*(__force volatile u16 *) (addr)) = (w))
#define out_be32(addr,l) (void)((*(__force volatile u32 *) (addr)) = (l))
#define out_le16(addr,w) (void)((*(__force volatile __le16 *) (addr)) = cpu_to_le16(w))
#define out_le32(addr,l) (void)((*(__force volatile __le32 *) (addr)) = cpu_to_le32(l))
#endif


#ifdef __KERNEL__

#define NCP_BUS_READ8(addr) \
    ((ncp_pio_read_delay > 0) ? \
        ncp_sys_usleep(ncp_pio_read_delay), \
            readb((volatile ncp_uint8_t *) (addr)) : \
    readb((volatile ncp_uint8_t *) (addr)))

#ifdef NCP_BIG_ENDIAN
#define NCP_BUS_READ16_ENDIAN(endian, addr) \
    ((ncp_pio_read_delay > 0) ? \
        ncp_sys_usleep(ncp_pio_read_delay), \
            in_##endian##16((volatile ncp_uint16_t *) (addr)) : \
    in_##endian##16((volatile ncp_uint16_t __iomem *) (addr)))
#else
#define NCP_BUS_READ16_ENDIAN(endian, addr) \
    ((ncp_pio_read_delay > 0) ? \
        ncp_sys_usleep(ncp_pio_read_delay), \
        endian##16_to_cpu(readw((volatile ncp_uint16_t *) (addr))) : \
        endian##16_to_cpu(readw((volatile ncp_uint16_t __iomem *) (addr))) )
#endif


#define NCP_BUS_READ16_LE(addr) NCP_BUS_READ16_ENDIAN(le, addr)

#define NCP_BUS_READ16_BE(addr) NCP_BUS_READ16_ENDIAN(be, addr)

#define NCP_BUS_READ16(addr, flags) \
    (flags & NCP_DEV_ACCESS_BIG_ENDIAN) ?   \
        NCP_BUS_READ16_BE(addr) : NCP_BUS_READ16_LE(addr)

#ifdef NCP_BIG_ENDIAN
#define NCP_BUS_READ32_ENDIAN(endian, addr) \
    ((ncp_pio_read_delay > 0) ? \
        ncp_sys_usleep(ncp_pio_read_delay), \
            in_##endian##32((volatile ncp_uint32_t __iomem *) (addr)) : \
    in_##endian##32((volatile ncp_uint32_t __iomem *) (addr)))
#else
#define NCP_BUS_READ32_ENDIAN(endian, addr) \
    ((ncp_pio_read_delay > 0) ? \
        ncp_sys_usleep(ncp_pio_read_delay), \
        endian##32_to_cpu(readl((volatile ncp_uint32_t __iomem *) (addr))) : \
        endian##32_to_cpu(readl((volatile ncp_uint32_t __iomem *) (addr))))
#endif 


#define NCP_BUS_READ32_LE(addr) NCP_BUS_READ32_ENDIAN(le, addr)

#define NCP_BUS_READ32_BE(addr) NCP_BUS_READ32_ENDIAN(be, addr)

#define NCP_BUS_READ32(addr, flags) \
    (flags & NCP_DEV_ACCESS_BIG_ENDIAN) ?   \
        NCP_BUS_READ32_BE(addr) : NCP_BUS_READ32_LE(addr)


#define NCP_BUS_WRITE8(addr, data) \
    ((ncp_pio_write_delay > 0) ? \
        ncp_sys_usleep(ncp_pio_write_delay), \
            writeb((data), (volatile ncp_uint8_t *)(addr)) : \
    writeb((data), (volatile ncp_uint8_t *) (addr)) )

#ifdef NCP_BIG_ENDIAN
#define NCP_BUS_WRITE16_ENDIAN(endian, addr, data) \
    do { \
        ncp_uint16_t * __a__ = (ncp_uint16_t *) addr; \
        ncp_uint16_t __d__ = data; \
        if (ncp_pio_write_delay > 0) ncp_sys_usleep(ncp_pio_write_delay); \
        out_##endian##16((volatile ncp_uint16_t __iomem *) __a__, __d__); \
        NCP_EDEV_BUS_ENFORCE_ORDERING(); \
    } while (0);
#else
#define NCP_BUS_WRITE16_ENDIAN(endian, addr, data) \
    do { \
        ncp_uint16_t * __a__ = (ncp_uint16_t *) addr; \
        ncp_uint16_t __d__ = cpu_to_##endian##16(data); \
        if (ncp_pio_write_delay > 0) ncp_sys_usleep(ncp_pio_write_delay); \
        writew(__d__,(volatile ncp_uint16_t __iomem *) __a__); \
        NCP_EDEV_BUS_ENFORCE_ORDERING(); \
    } while (0);
#endif

#define NCP_BUS_WRITE16_LE(addr, data) \
    NCP_BUS_WRITE16_ENDIAN(le, addr, data) \

#define NCP_BUS_WRITE16_BE(addr, data) \
    NCP_BUS_WRITE16_ENDIAN(be, addr, data) \

#define NCP_BUS_WRITE16(addr, data, flags) \
    if (flags & NCP_DEV_ACCESS_BIG_ENDIAN) {   \
         NCP_BUS_WRITE16_BE(addr, data);    \
    } else {                                     \
         NCP_BUS_WRITE16_LE(addr, data);    \
    }

#ifdef NCP_BIG_ENDIAN
#define NCP_BUS_WRITE32_ENDIAN(endian, addr, data) \
    do { \
        ncp_uint32_t * __a__ = (ncp_uint32_t *) addr; \
        ncp_uint32_t __d__ = data; \
        if (ncp_pio_write_delay > 0) ncp_sys_usleep(ncp_pio_write_delay); \
        out_##endian##32((volatile ncp_uint32_t __iomem *) __a__, __d__); \
        NCP_EDEV_BUS_ENFORCE_ORDERING(); \
    } while (0);
#else
#define NCP_BUS_WRITE32_ENDIAN(endian, addr, data) \
    do { \
        ncp_uint32_t * __a__ = (ncp_uint32_t *) addr; \
        ncp_uint32_t __d__ = cpu_to_##endian##32(data); \
        if (ncp_pio_write_delay > 0) ncp_sys_usleep(ncp_pio_write_delay); \
        writel(__d__, (volatile ncp_uint32_t __iomem *) __a__); \
        NCP_EDEV_BUS_ENFORCE_ORDERING(); \
    } while (0);
#endif

#define NCP_BUS_WRITE32_LE(addr, data) \
    NCP_BUS_WRITE32_ENDIAN(le, addr, data) \

#define NCP_BUS_WRITE32_BE(addr, data) \
    NCP_BUS_WRITE32_ENDIAN(be, addr, data) \

#define NCP_BUS_WRITE32(addr, data, flags) \
    if (flags & NCP_DEV_ACCESS_BIG_ENDIAN) {   \
         NCP_BUS_WRITE32_BE(addr, data);    \
    } else {                                     \
         NCP_BUS_WRITE32_LE(addr, data);    \
    }

void *
ncp_dma_mem_map(
        ncp_uint32_t devNum,
        ncp_uint64_t physAddr,
        ncp_uint32_t size);

void *
ncp_mem_map(
        ncp_uint32_t devNum,
        ncp_uint64_t physAddr,
        ncp_uint32_t size);

#define NCP_DMA_MEM_MAP(_devNum, _physAddr, _size) \
        ncp_dma_mem_map(_devNum, _physAddr, _size)

#define NCP_DMA_MEM_UNMAP(_devNum, _dmaAddrPtr) \
    if (_dmaAddrPtr) {                              \
        NCP_MSG(NCP_MSG_DEBUG_MEM, "NCP_DMA_MEM_UNMAP %p\r\n",_dmaAddrPtr); \
        iounmap((void *)(_dmaAddrPtr));             \
    }

#define NCP_MEM_MAP(_devNum, _physAddr, _size) \
        ncp_mem_map(_devNum, _physAddr, _size)

#define NCP_MEM_UNMAP(_devNum, _addrPtr) \
    if ((_addrPtr)) {                              \
        NCP_MSG(NCP_MSG_DEBUG_MEM, "NCP_MEM_UNMAP %p\r\n",_addrPtr); \
        iounmap((void *)(_addrPtr));               \
    }
    
#define NCP_TIMER_ADD(pTimer, timerFunc, timerFuncArg, duration) \
    (ncp_edev_timer_add(pTimer, timerFunc, timerFuncArg, duration))

#define NCP_TIMER_MOD(pTimer, duration) \
    (ncp_edev_timer_mod(pTimer, duration))

#define NCP_TIMER_CANCEL(pTimer) \
    (ncp_edev_timer_cancel(pTimer))

#define NCP_COPY_FROM_USER(to, from, size) \
    copy_from_user((void *)(to), (void *)(from), (unsigned long)(size))

#define NCP_COPY_TO_USER(to, from, size) \
    copy_to_user((void *)(to), (void *)(from), (unsigned long)(size))



#define NCP_RESCHEDULE() \
    schedule()


/* The definition of NCP_IOREMAP_CACHE varies depending
 * on the linux version/architecture. It is defined in
 * ncp_sal_linux_<target>.h
 */

#define NCP_IOREMAP_NOCACHE(_addr, _size)                                      \
({                                                                             \
    void *__p;                                                                 \
    __p = ioremap_nocache(_addr, _size);                                       \
    NCP_MSG(NCP_MSG_DEBUG_MEM, "NCP_IOREMAP_NOCACHE mapped %llx sz=%x VA %p\r\n", _addr, _size, __p); \
    __p;                                                                       \
})    


#if defined(PROC_ARMA15) || defined(PROC_ARMA57)
#define NCP_IOREMAP_DMA(_addr, _size) NCP_IOREMAP_NOCACHE(_addr, _size)
#else
#ifdef NCP_NCA_COHERENT_IO
#define NCP_IOREMAP_DMA(_addr, _size) NCP_IOREMAP_CACHE(_addr, _size)
#else 
#define NCP_IOREMAP_DMA(_addr, _size) NCP_IOREMAP_NOCACHE(_addr, _size)
#endif
#endif


#ifdef NCP_DEV_PLB

/*
 * PLB bus adaptor definitions
 * NOTE: This needs to be in sync with the BSP.
 *
 * For linux we define the APB Base VA as NULL,
 * the bus adaptor will do the mapping.
 */

#define NCP_DEV_PLB_APB_BASE_VADDR  NULL
 
#define NCP_DEV_PLB_MPIC1_DCR_BASE  0xEFC00000
#define NCP_DEV_PLB_MPIC0_DCR_BASE  0xFFC00000


/* DCR access from the internal core uses a special PPC instruction */
#define NCP_DCR_WRITE32(dcrAddr, val)  \
    mtdcr(dcrAddr, val)

#define NCP_DCR_READ32(dcrAddr) \
    mfdcr(dcrAddr)

#endif /* #ifdef NCP_DEV_PLB */

#endif /* #ifdef __KERNEL__ */

#ifdef __KERNEL__

#define ncp_task_buf_os_alloc(size)                 \
    ({                                              \
        struct sk_buff *__skb;                      \
        /* Allocate sk_buff */                      \
        __skb = dev_alloc_skb(size + NET_IP_ALIGN); \
        if(__skb != NULL) {                         \
            skb_reserve(__skb, NET_IP_ALIGN);       \
        }                                           \
        __skb;                                      \
    })

#define ncp_task_buf_os_free(taskAddr)  \
    kfree_skb((struct sk_buff *)taskAddr)

#define ncp_task_buf_data(skb)  \
    ((struct sk_buff *)(skb))->data

#else

#define NCP_USER_MEM_UNMAP(addrPtr, len)          \
    if ((addrPtr)) {                              \
        munmap((void *)(addrPtr), len);           \
    }


#define ncp_task_buf_os_alloc(size)     \
    ncp_nvm_malloc(size)

#define ncp_task_buf_os_free(taskAddr)  \
    ncp_nvm_free(taskAddr)

#define ncp_task_buf_data(buf)  \
    (buf)

NCP_API int snprintf(char *s, 
                     size_t n,
                     const char *format, 
                     ...);

#endif

#ifdef __KERNEL__

/* TODO: handle mallocs from ISR */

#define __ncp_malloc(size)              kmalloc(size, GFP_ATOMIC)
#define __ncp_free(ptr)                 kfree(ptr)
#define __ncp_realloc(ptr, size)        (NULL)
#define __ncp_calloc(no, size)          kcalloc(no, size, GFP_ATOMIC)

#define __ncp_nvm_malloc(size)          __ncp_malloc(size)
#define __ncp_nvm_free(ptr)             __ncp_free(ptr)
#define __ncp_nvm_realloc(ptr, size)    __ncp_realloc(ptr, size)
#define __ncp_nvm_calloc(no, size)      __ncp_calloc(no, size)

#else /* !#ifdef __KERNEL__ */

#define __ncp_malloc(size)              malloc(size)
#define __ncp_free(ptr)                 free(ptr)
#define __ncp_realloc(ptr, size)        realloc(ptr, size)
#define __ncp_calloc(no, size)          calloc(no, size)

#ifdef NCP_USE_NVM

extern ncp_sem_t *pNvmLock;
extern ncp_bool_t *pNvmActive;

#define __ncp_nvm_malloc(size)      \
    ({                              \
        void *__ptr = NULL;         \
        ncp_sem_wait(pNvmLock);     \
        *pNvmActive = TRUE;         \
        __ptr = mp_malloc((size));  \
        *pNvmActive = FALSE;        \
        ncp_sem_post(pNvmLock);     \
        __ptr;                      \
    })
    
#define __ncp_nvm_free(ptr)         \
    {                               \
        ncp_sem_wait(pNvmLock);     \
        *pNvmActive = TRUE;         \
        mp_free(ptr);               \
        *pNvmActive = FALSE;        \
        ncp_sem_post(pNvmLock);     \
    }

#define __ncp_nvm_realloc(ptr, size)    \
    ({                                  \
        void *__ptr = NULL;             \
        ncp_sem_wait(pNvmLock);         \
        *pNvmActive = TRUE;             \
        __ptr = mp_realloc(ptr, size);  \
        *pNvmActive = FALSE;            \
        ncp_sem_post(pNvmLock);         \
        __ptr;                          \
    })

#define __ncp_nvm_calloc(no, size)      \
    ({                                  \
        void *__ptr = NULL;             \
        ncp_sem_wait(pNvmLock);         \
        *pNvmActive = TRUE;             \
        __ptr = mp_calloc(no, size);    \
        *pNvmActive = FALSE;            \
        ncp_sem_post(pNvmLock);         \
        __ptr;                          \
    })

#else

#define __ncp_nvm_malloc(size)          __ncp_malloc(size)
#define __ncp_nvm_free(ptr)             __ncp_free(ptr)
#define __ncp_nvm_realloc(ptr, size)    __ncp_realloc(ptr, size)
#define __ncp_nvm_calloc(no, size)      __ncp_calloc(no, size)

#endif /* #ifdef NCP_USE_NVM */

#endif /* #ifdef __KERNEL__ */

#ifdef __cplusplus
}
#endif

#endif /* __NCP_SAL_LINUX_H__ */
