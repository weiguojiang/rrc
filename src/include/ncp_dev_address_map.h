/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


#ifndef __NCP_DEV_ADDRESS_MAP_H__
#define __NCP_DEV_ADDRESS_MAP_H__


/* 
 * This file defines the memory addresses for each h/w block
 * that is accessible as a direct bus i/o operation. 
 *
 */

typedef enum {
    NCP_DEV_MAP_PCI = 0,
    NCP_DEV_MAP_SRIO,
    NCP_DEV_MAP_DCR,
    NCP_DEV_MAP_APB,
    NCP_DEV_MAP_SAS = NCP_DEV_MAP_APB, /* AXM55xx */
    NCP_DEV_MAP_AHB,
    NCP_DEV_MAP_FAS = NCP_DEV_MAP_AHB, /* AXM55xx */
    NCP_DEV_MAP_NCA,
    NCP_DEV_MAP_SYS,
    NCP_DEV_MAP_PAGED,
    NCP_DEV_MAP_MISC,
    NCP_DEV_MAP_MAX
} ncp_dev_map_segments_t;


/*
 * NCA mapping
 * This is the same for both ACP34xx and ACP25xx architectures.
 * On the ppc476 platform we map the NCA first so we can read
 * the module revision to tell which chipType we're running on.
 */

ncp_dev_addr_map_t ncp_dev_map_nca[] = {
    { NCP_DEV_PAGE_NCA,             0x2000520000ULL, 
                                    NCP_CONST_128KB,
                                    NCP_DEV_ACCESS_BIG_ENDIAN},

};


/*
 * miscellaneous directly addressable bus-mappings 
 * Some of these are host memory regions instead of 
 * blocks within the ACP itself.
 */
ncp_dev_addr_map_t ncp_dev_map_misc[] = {
    { NCP_DEV_PAGE_DMA_MEM_LE,      0x00000000000ULL, 
                                    NCP_CONST_32MB, 
                                    NCP_DEV_ACCESS_LITTLE_ENDIAN},

    { NCP_DEV_PAGE_DMA_MEM_BE,      0x00000000000ULL, 
                                    NCP_CONST_32MB, 
                                    NCP_DEV_ACCESS_BIG_ENDIAN},

    { NCP_DEV_PAGE_TASK_MEM_LE,     0x00000000000ULL, 
                                    NCP_CONST_32MB, 
                                    NCP_DEV_ACCESS_LITTLE_ENDIAN},

    { NCP_DEV_PAGE_TASK_MEM_BE,     0x00000000000ULL, 
                                    NCP_CONST_32MB, 
                                    NCP_DEV_ACCESS_BIG_ENDIAN},
                                                  
    { NCP_DEV_PAGE_HOSTMEM_LE,      0x00000000000ULL, 
                                    NCP_CONST_32MB, 
                                    NCP_DEV_ACCESS_LITTLE_ENDIAN},

    { NCP_DEV_PAGE_HOSTMEM_BE,      0x00000000000ULL, 
                                    NCP_CONST_32MB, 
                                    NCP_DEV_ACCESS_BIG_ENDIAN},
                                                  
    { NCP_DEV_PAGE_SIMULATOR_IF,    0x00000000000ULL, 
                                    NCP_CONST_1KB, 
                                    NCP_DEV_ACCESS_BIG_ENDIAN}
    
};

#define NCP_DEV_NUM_NCA_PAGES (sizeof(ncp_dev_map_nca) / sizeof(ncp_dev_addr_map_t))
#define NCP_DEV_NUM_MISC_PAGES (sizeof(ncp_dev_map_misc) / sizeof(ncp_dev_addr_map_t))

#include "ncp_dev_addr_map_acp34xx.h"
#include "ncp_dev_addr_map_axm35xx.h"
#include "ncp_dev_addr_map_axm55xx.h"
#include "ncp_dev_addr_map_axm56xx.h"
#include "ncp_dev_addr_map_xlf.h"

#endif
