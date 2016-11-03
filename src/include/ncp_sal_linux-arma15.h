/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*! @file      ncp_sal_linux-arma15.h
    @brief     RTE Target ARM A15 layer specific definitions.
*/

#ifndef __NCP_SAL_LINUX_ARMA15_H__
#define __NCP_SAL_LINUX_ARMA15_H__

#ifdef __KERNEL__

#include <linux/semaphore.h>
#include <linux/timer.h>
#include <linux/math64.h>

#endif

#include <linux/version.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NCP_LINUX
#define NCP_LINUX
#endif



#define   NCP_NVM_VADDR            0x48080000
#define   NCP_DMA_VADDR            0x70000000


#define NCP_EDEV_BUS_ENFORCE_ORDERING() 


#ifdef  __KERNEL__
#if LINUX_VERSION_CODE >= KERNEL_VERSION (3, 12, 0)

#define NCP_IOREMAP_CACHE(_addr, _size)                                   \
({  NCP_MSG(NCP_MSG_DEBUG, "Map CACHED_WB %llx sz=%x\r\n", _addr, _size);  \
    ioremap_cache(_addr, _size);                                          \
})
#else
#define NCP_IOREMAP_CACHE(_addr, _size)                                   \
({  NCP_MSG(NCP_MSG_DEBUG, "Map CACHED_WB %llx sz=%x\r\n", _addr, _size);  \
    ioremap_cached(_addr, _size);                                          \
})
#endif
#else
#define NCP_IOREMAP_CACHE(_addr, _size)                                   \
({  NCP_MSG(NCP_MSG_DEBUG, "Map CACHED_WB %llx sz=%x\r\n", _addr, _size);  \
    ioremap_cached(_addr, _size);                                          \
})
#endif


#ifdef  __KERNEL__
#define NCP_I2C_DIV64_BY_32(div64,div32)                                \
        div_u64((div64), (div32))
#endif


#ifdef __cplusplus
}
#endif

#endif /* __NCP_SAL_LINUX_ARMA15_H__ */
