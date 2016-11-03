/**************************************************************************
**                                                                        *
**                           Intel CONFIDENTIAL           *
**                                                                        *
**                       PROPRIETARY NOTE                                 *
**                                                                        *
**    This software contains information confidential and proprietary     *
**    to Intel Corporation.  It shall not be reproduced in whole or in  *
**    part, or transferred to other documents, or disclosed to third      *
**    parties, or used for any purpose other than that for which it was   *
**    obtained, without the prior written consent of Intel Corporation. *
**    (c) 2008-2014, Intel Corporation.  All rights reserved.           *
**                                                                        *
**  ***********************************************************************
**
**  ***********************************************************************
**
**************************************************************************/


/*
 * ncp_dev_linux_stubs.h
 *
 * common macro stubs for the various non-hardware based
 * linux libraries (FBRS, socket, and fbdev). Any macros 
 * that are specific to a particular adaptor are defined
 * in the adaptor specific header (i.e. ncp_dev_fbrs.h)
 *
 *
 */

#ifndef __NCP_DEV_LINUX_STUBS_H__
#define __NCP_DEV_LINUX_STUBS_H__

#ifdef __cplusplus
extern "C" { 
#endif

#ifdef NCP_OSE
#define NCP_SLEEP_POLL_INTERVAL 1000
#else
#define NCP_SLEEP_POLL_INTERVAL 0
#endif

#define ncp_task_isr_put_waitObj(pWaitListHead, pWaitObj)

#define ncp_task_isr_get_waitObj(pWaitListHead, ppWaitObj) (*ppWaitObj = NULL);

#define ncp_cfgdma_isr_selective_wakeup(pCPCQ) /* (NCP_ST_SUCCESS) */

#define ncp_task_isr_remove_waitObj(pWaitListHead, pWaitObj)

/* --- Types and Definitions --- */

#define NCP_USER_MEM_UNMAP(addrPtr, len)          

#define NCP_INIT_ISR_INFO(_devNum, _grp, _intData) (0)

#define NCP_CLEANUP_ISR_INFO(_devNum) 

#define NCP_EDEV_FREE(devNum) ncp_edev_bus_cleanup(devNum)

#define NCP_EDEV_FINI()

#define NCP_EDEV_BUS_CLEANUP(devNum)

#define NCP_EDEV_BUS_ADDR(devNum, pageId) (1)

#define NCP_EDEV_BUS_SIZE(devNum, segNum) (0x100000)

#define NCP_EDEV_BUS_FIND_DEVS() (1)


#define NCP_EDEV_BUS_SPACE_MAP(devNum, pciAddr, size) ((void *) 1)

#define NCP_EDEV_BUS_SPACE_UNMAP(devNum, cpuAddr, size)

#define NCP_EDEV_BUS_PAGE_SIZE 0x00040000ULL

#define NCP_EDEV_BUS_PAGE_MASK (NCP_EDEV_BUS_PAGE_SIZE - 1)

#define NCP_EDEV_BUS_PAGE_BASE(x) \
        (((ncp_uint32_t)((x) & (~NCP_EDEV_BUS_PAGE_MASK))) >> 18)

#define NCP_EDEV_BUS_MAP_PAGE(devNum, pageOffset, cpuAddr) \
        (NCP_ST_SUCCESS)

#define NCP_BUS_READ8(addr) (0)

#define NCP_BUS_READ16(addr, flags) (0)

#define NCP_BUS_READ32(addr, flags) (0)

#define NCP_BUS_WRITE8(addr, data)

#define NCP_BUS_WRITE16(addr, data, flags)

#define NCP_BUS_WRITE32(addr, data, flags)

#define NCP_EDEV_BUS_CONFIG_READ8(devNum, byteOffset, value) 0

#define NCP_EDEV_BUS_CONFIG_READ16(devNum, byteOffset, value) 0

#define NCP_EDEV_BUS_CONFIG_READ32(devNum, byteOffset, value) 0

#define NCP_EDEV_BUS_CONFIG_WRITE8(devNum, byteOffset, value) 

#define NCP_EDEV_BUS_CONFIG_WRITE16(devNum, byteOffset, value) 

#define NCP_EDEV_BUS_CONFIG_WRITE32(devNum, byteOffset, value) 

#define NCP_DMA_MEM_MAP(devNum, physAddr, size) (0)

#define NCP_MEM_MAP(devNum, physAddr, size) (0)

        
#define NCP_DMA_MEM_UNMAP(devNum, dmaAddrPtr) 

#define NCP_COPY_FROM_USER(to, from, size) \
    (ncp_memcpy((void *)(to), (const void *)(from), (size_t)(size)) ? 0 : 1)

#define NCP_COPY_TO_USER(to, from, size) \
    (ncp_memcpy((void *)(to), (const void *)(from), (size_t)(size)) ? 0 : 1)

#define ncp_edev_interrupt_connect(devHdl) (0)    /* Uses Unix "0 is good" metaphor */

#define ncp_edev_interrupt_disconnect(devHdl) (0) /* Uses Unix "0 is good" metaphor */

#define NCP_DEV_INTERRUPT_CONNECT(_dev) (0) 

#define NCP_DEV_INTERRUPT_DISCONNECT(_dev)

#define NCP_INTERRUPT_ENABLE(intLevel)

#define NCP_INTERRUPT_DISABLE(intLevel)

#define NCP_EDEV_SPINLOCK_INTERRUPT_DISABLE(pSem, pFlags)

#define NCP_EDEV_SPINLOCK_INTERRUPT_ENABLE(pSem, pFlags)

#define NCP_IN_INTERRUPT() (0)

#define NCP_WAITQ_ALLOC(pWaitqHdl)

#define NCP_WAITQ_FREE(pWaitqHdl)

#define NCP_WAITQ_WAIT(waitqHdl, cond) 

#define NCP_WAITQ_WAIT_TIMEOUT(waitqHdl, cond, timeout)

#define NCP_WAITQ_WAKEUP(waitqHdl)

#define NCP_TASK_ISR_EVENT_FREELIST_INIT(_freeListObjs, _num) 

#define NCP_TASK_ISR_EVENT_OBJECT_FREE(pWaitqHdl) 

#define NCP_TASK_ISR_EVENT_WAIT_INTERRUPTIBLE(waitqHdl, cond) 

#define NCP_TASK_ISR_EVENT_WAIT_TIMEOUT(waitqHdl, cond, timeout) 

#define NCP_TASK_ISR_EVENT_WAKEUP(waitqHdl) 

#define NCP_TASK_ISR_EVENT_FORCE_WAKEUP_ALL(waitqHdl, isrLock) 

#define NCP_SIGNAL_PENDING() (FALSE)

#define NCP_TIMER_ADD(timer, timerFunc, timerFuncArg, duration)

#define NCP_TIMER_MOD(timer, duration)

#define NCP_TIMER_CANCEL(timer)

#define NCP_EDEV_BUS_SETUP(dev) \
        (NCP_ST_SUCCESS)

#ifndef NCP_SPINLOCK_DEFINED
    typedef void * ncp_spinlock_t;
    typedef ncp_spinlock_t ncp_raw_spinlock_t;    
    typedef ncp_spinlock_t ncp_bsp_spinlock_t;    
    #define NCP_SPINLOCK_DEFINED
#endif

#undef NCP_SPINLOCK_INIT
#define NCP_SPINLOCK_INIT(lock) 

#undef NCP_SPINLOCK_FLAGS
#define NCP_SPINLOCK_FLAGS(flags)

#undef NCP_SPINLOCK_INTERRUPT_DISABLE
#define NCP_SPINLOCK_INTERRUPT_DISABLE(pSem,flags)

#undef NCP_SPINLOCK_INTERRUPT_ENABLE
#define NCP_SPINLOCK_INTERRUPT_ENABLE(pSem,flags)

#undef NCP_SPINLOCK_SW_FLAGS
#define NCP_SPINLOCK_SW_FLAGS(flags)

#undef NCP_SPINLOCK_SW_INTERRUPT_DISABLE
#define NCP_SPINLOCK_SW_INTERRUPT_DISABLE(pSem, flags)

#undef NCP_SPINLOCK_SW_INTERRUPT_ENABLE
#define NCP_SPINLOCK_SW_INTERRUPT_ENABLE(pSem, flags)

/* Now for raw spinlocks */

#define NCP_RAW_SPINLOCK_INIT(lock) \
    NCP_SPINLOCK_INIT(lock)

#define NCP_RAW_SPINLOCK_FLAGS(flags) \
    NCP_SPINLOCK_FLAGS(flags)

#define NCP_RAW_SPINLOCK_INTERRUPT_DISABLE(pSem, flags) \
    NCP_SPINLOCK_INTERRUPT_DISABLE(pSem, flags)

#define NCP_RAW_SPINLOCK_INTERRUPT_ENABLE(pSem, flags) \
    NCP_SPINLOCK_INTERRUPT_ENABLE(pSem, flags)

#define NCP_RAW_SPINLOCK_SW_FLAGS(flags) \
    NCP_SPINLOCK_SW_FLAGS(flags)

#define NCP_RAW_SPINLOCK_SW_INTERRUPT_DISABLE(pSem, flags) \
    NCP_SPINLOCK_SW_INTERRUPT_DISABLE(pSem, flags)    

#define NCP_RAW_SPINLOCK_SW_INTERRUPT_ENABLE(pSem, flags) \
    NCP_SPINLOCK_SW_INTERRUPT_ENABLE(pSem, flags)

#define NCP_RAW_SPINLOCK_LOCK(pSpinlock)   \
        NCP_SPINLOCK_LOCK(pSpinlock)

#define NCP_RAW_SPINLOCK_UNLOCK(pSpinlock) \
        NCP_SPINLOCK_UNLOCK(pSpinlock)

#define NCP_RAW_SPINLOCK_TRYLOCK(pSpinlock) \
        NCP_SPINLOCK_TRYLOCK(pSpinlock)



#ifndef NCP_DAEMONIZE_SELF
#define NCP_DAEMONIZE_SELF() NCP_ST_SUCCESS
#endif

#ifndef NCP_RESCHEDULE
#define NCP_RESCHEDULE()
#endif

#ifndef NCP_CAT_DELAY_SETUP
#define NCP_CAT_DELAY_SETUP
#endif
#ifndef NCP_CAT_DELAY_FEMAC
#define NCP_CAT_DELAY_FEMAC()
#endif
#ifndef NCP_CAT_DELAY_PQM
#define NCP_CAT_DELAY_PQM()
#endif
#ifndef NCP_CAT_DELAY_REGISTER
#define NCP_CAT_DELAY_REGISTER()
#endif
#ifndef NCP_CAT_DELAY_REGISTER_ROW
#define NCP_CAT_DELAY_REGISTER_ROW()
#endif


#ifndef ncp_udelay
#define ncp_udelay(n)
#endif

#ifdef __cplusplus
}
#endif

#endif /* _NCP_DEV_LINUX_STUBS_H_ */
