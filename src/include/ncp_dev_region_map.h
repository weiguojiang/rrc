/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


#ifndef __NCP_REGION_REGION_MAP_H__
#define __NCP_REGION_REGION_MAP_H__


#include "ncp_dev_access.h"
#include "ncp_regions.h"


ncp_region_io_t ncp_region_io_map[] =
{
    /* TEMP - Dummy Regions */
    { NCP_REGION_DUMMY_INDIRECT,        ncpDummyRegionMap,
                                        __ncp_dev_indirect_read,
                                        __ncp_dev_indirect_write,
                                        0,
    }, 

    { NCP_REGION_DUMMY_DIRECT,          ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        0,
    }, 

    { NCP_REGION_DUMMY_INVALID,         ncpDummyRegionMap,
                                        ncp_dev_read_invalid_access,
                                        ncp_dev_write_invalid_access,
                                        0,
    }, 

    /* *** Config Ring Regions *** */

    /* 
     * NOTE! 
     * For the time being we don't yet define all the config ring regions.
     * Any attempted access to a region not defined in this table will
     * automatically default to the config ring. 
     *
     */


    /* *** Virtual Regions *** */

    /* Node 256 - PCI Express */
    /* 0x100.0 */
    { NCP_REGION_PCIE0_BAR_0,            ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_PCIE0_BAR_0,
    },

    /* 0x100.1 */
    { NCP_REGION_PCIE0_BAR_1,            ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_PCIE0_BAR_1,
    },

    /* 0x100.2 */
    { NCP_REGION_PCIE0_BAR_2,            ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_PCIE0_BAR_2,
    },

    /* 0x100.3 */
    { NCP_REGION_PCIE0_CONFIG,           ncpDummyRegionMap,
                                        __ncp_dev_bus_config_read,
                                        __ncp_dev_bus_config_write,
                                        0,
    },

    /* 0x100.4 */
    { NCP_REGION_PCIE0_PEI,              ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_PCIE0_PEI,
    },

    /* 0x100.5 */
    { NCP_REGION_PCIE0_AXI_SLV,          ncpDummyRegionMap,
                                        __ncp_dev_paged_read,
                                        __ncp_dev_paged_write,
                                        NCP_DEV_PAGE_PCIE0_AXI_SLV,
    },



    /* 0x101.0 */ 
    { NCP_REGION_NCA_AXI,               ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_NCA,
    },

    /* Node 258 - SRIO */
    /* 0x102.0 */
    { NCP_REGION_SRIO_PIO_WIN_0,        ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SRIO_PIO_WIN_0,
    },

    /* 0x102.1 */
    { NCP_REGION_SRIO_PIO_WIN_1,        ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SRIO_PIO_WIN_1,
    },

    /* 0x102.2 */
    { NCP_REGION_SRIO_PIO_WIN_2,        ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SRIO_PIO_WIN_2,
    },

    /* 0x102.3 */
    { NCP_REGION_SRIO_PIO_WIN_3,        ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SRIO_PIO_WIN_3,
    },

    /* 0x102.4 */
    { NCP_REGION_SRIO_PIO_WIN_4,        ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SRIO_PIO_WIN_4,
    },

    /* 0x102.5 */
    { NCP_REGION_SRIO_PIO_WIN_5,        ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SRIO_PIO_WIN_5,
    },

    /* 0x102.6 */
    { NCP_REGION_SRIO_PIO_WIN_6,        ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SRIO_PIO_WIN_6,
    },

    /* 0x102.7 */
    { NCP_REGION_SRIO_PIO_WIN_7,        ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SRIO_PIO_WIN_7,
    },

    /* 0x102.8 */
    { NCP_REGION_SRIO_PIO_WIN_8,        ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SRIO_PIO_WIN_8,
    },

    /* 0x102.9 */
    { NCP_REGION_SRIO_PIO_WIN_9,        ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SRIO_PIO_WIN_9,
    },

    /* 0x102.10 */
    { NCP_REGION_SRIO_PIO_WIN_10,       ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SRIO_PIO_WIN_10,
    },

    /* 0x102.11 */
    { NCP_REGION_SRIO_PIO_WIN_11,       ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SRIO_PIO_WIN_11,
    },

    /* 0x102.12 */
    { NCP_REGION_SRIO_PIO_WIN_12,       ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SRIO_PIO_WIN_12,
    },

    /* 0x102.13 */
    { NCP_REGION_SRIO_PIO_WIN_13,       ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SRIO_PIO_WIN_13,
    },

    /* 0x102.14 */
    { NCP_REGION_SRIO_PIO_WIN_14,       ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SRIO_PIO_WIN_14,
    },

    /* 0x102.15 */
    { NCP_REGION_SRIO_PIO_WIN_15,       ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SRIO_PIO_WIN_15,
    },

    /* 0x102.16 */
    { NCP_REGION_SRIO_CFG_GRIO,         ncpDummyRegionMap,
                                        __ncp_dev_srio_cfg_read,
                                        __ncp_dev_srio_cfg_write,
                                        NCP_DEV_PAGE_SRIO_CFG_GRIO,
    },

    /* 0x102.17 */
    { NCP_REGION_SRIO_CFG_RAB,          ncpDummyRegionMap,
                                        __ncp_dev_srio_cfg_read,
                                        __ncp_dev_srio_cfg_write,
                                        NCP_DEV_PAGE_SRIO_CFG_RAB,
    },

    /* 103.0 */ 
    { NCP_REGION_PKA,                   ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_PKA,
    },

    /* 0x104.0 */ 
    { NCP_REGION_ROM,                   ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_ROM,
    },


    /* V2 only - additional PCI Express cores */
    /* 0x105.0 */
    { NCP_REGION_PCIE1_BAR_0,            ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_PCIE1_BAR_0,
    },

    /* 0x105.1 */
    { NCP_REGION_PCIE1_BAR_1,            ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_PCIE1_BAR_1,
    },

    /* 0x105.2 */
    { NCP_REGION_PCIE1_BAR_2,            ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_PCIE1_BAR_2,
    },

    /* 0x105.3 */
    { NCP_REGION_PCIE1_CONFIG,           ncpDummyRegionMap,
                                        __ncp_dev_bus_config_read,
                                        __ncp_dev_bus_config_write,
                                        0,
    },

    /* 0x105.4 */
    { NCP_REGION_PCIE1_PEI,              ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_PCIE1_PEI,
    },

    /* 0x105.5 */
    { NCP_REGION_PCIE1_AXI_SLV,          ncpDummyRegionMap,
                                        __ncp_dev_paged_read,
                                        __ncp_dev_paged_write,
                                        NCP_DEV_PAGE_PCIE1_AXI_SLV,
    },

    /* 0x106.0 */
    { NCP_REGION_PCIE2_BAR_0,            ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_PCIE2_BAR_0,
    },

    /* 0x106.1 */
    { NCP_REGION_PCIE2_BAR_1,            ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_PCIE2_BAR_1,
    },

    /* 0x106.2 */
    { NCP_REGION_PCIE2_BAR_2,            ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_PCIE2_BAR_2,
    },

    /* 0x106.3 */
    { NCP_REGION_PCIE2_CONFIG,           ncpDummyRegionMap,
                                        __ncp_dev_bus_config_read,
                                        __ncp_dev_bus_config_write,
                                        0,
    },

    /* 0x106.4 */
    { NCP_REGION_PCIE2_PEI,              ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_PCIE2_PEI,
    },

    /* 0x106.5 */
    { NCP_REGION_PCIE2_AXI_SLV,          ncpDummyRegionMap,
                                        __ncp_dev_paged_read,
                                        __ncp_dev_paged_write,
                                        NCP_DEV_PAGE_PCIE2_AXI_SLV,
    },



    /* AXM55xx - SRIO1 */
    /* TODO: add all the PIO windows!! */
    /* 0x107.16 */
    { NCP_REGION_SRIO1_CFG_GRIO,         ncpDummyRegionMap,
                                        __ncp_dev_srio_cfg_read,
                                        __ncp_dev_srio_cfg_write,
                                        NCP_DEV_PAGE_SRIO_1_CFG_GRIO,
    },

    /* 0x107.17 */
    { NCP_REGION_SRIO1_CFG_RAB,          ncpDummyRegionMap,
                                        __ncp_dev_srio_cfg_read,
                                        __ncp_dev_srio_cfg_write,
                                        NCP_DEV_PAGE_SRIO_1_CFG_RAB,
    },


    /* 0x108.0 */
    { NCP_REGION_LSM,                   ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_LSM,
    },

    /* 0x109.0 */
    { NCP_REGION_MME_CONF,              ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_MME_CONF,
    },

    /* And back to common stuff */

    /* 0x120.0     = 288.0 */ 
    { NCP_REGION_NAND,                  ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_NAND,
    },

    /* 0x121.0    = 289.0 */ 
    { NCP_REGION_TRNG,                  ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_TRNG,
    },

    /* 0x122.0   =  290.0 */ 
    { NCP_REGION_FEMAC,                 ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_FEMAC,
    },

    /* 0x123.0   = 291.0 */ 
    { NCP_REGION_USB,                   ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_USB,
    },

    /* 0x124.0   (292.0) */ 
    { NCP_REGION_GPDMA_0,               ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_GPDMA_0,
    },

    /* 0x125.0   = 293.0 */ 
    { NCP_REGION_GPDMA_1,               ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_GPDMA_1,
    },

    /* 0x126.0   - 294.0 */
    { NCP_REGION_M3SS,                 ncpDummyRegionMap,
                                        __ncp_dev_paged_read,
                                        __ncp_dev_paged_write,
                                        NCP_DEV_PAGE_M3SS,
    },

    /* 0x127.0   - 295.0 */
    { NCP_REGION_STM,                   ncpDummyRegionMap,
                                        __ncp_dev_paged_read,
                                        __ncp_dev_paged_write,
                                       NCP_DEV_PAGE_STM,
    },

    /* 0x140.0   (320.0) */ 
    { NCP_REGION_GPIO_0,                ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_GPIO_0,
    },

    /* 0x141.0   (321.0) */ 
    { NCP_REGION_GPIO_1,                ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_GPIO_1,
    },

    /* 0x142.0   (322.0) */ 
    { NCP_REGION_SSP,                   ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SSP,
    },

    /* 0x143.0   (323.0) */ 
    { NCP_REGION_I2C,                   ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_I2C_0,
    },

    /* 0x144.0    (324.0) */ 
    { NCP_REGION_UART_0,                ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_UART_0,
    },

    /* 0x145.0    (325.0) */ 
    { NCP_REGION_UART_1,                ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_UART_1,
    },

    /* 0x146.0    (326.0) */ 
    { NCP_REGION_TIMER,                 ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_TIMER,
    },

    /* 0x147.0    (327.0) */ 
    { NCP_REGION_MDIO,                  ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_MDIO,
    },

    /* 0x148.0   (328.0) */ 
    { NCP_REGION_APB2RC,                ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_APB2RC,
    },

    /* 0x149.0    (329.0) */ 
    { NCP_REGION_GPREG,                 ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_GPREG,
    },

    /* 0x14a    (330.0) */ 
    { NCP_REGION_SRIO_CONF,             ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SRIO_CONF,
    },

    /* 0x14b     (331.0) */ 
    { NCP_REGION_PL301,                 ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_PL301_0_CONF,
    },

    /* 0x14c.0    (332.0) */ 
    { NCP_REGION_I2C_1,                 ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_I2C_1,
    },

    /* 0x14d.0    (333.0) */ 
    { NCP_REGION_UART_2,                ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_UART_2,
    },

    /* new for AXM55xx */
    /* 0x14e.0     (334.0) */ 
    { NCP_REGION_XVRC,                  ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_XVRC,
    },

    /* 0x14f.0     (335.0) */ 
    { NCP_REGION_SRIO_GPREG,            ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SRIO_GPREG,
    },

    /* 0x150.0     (336.0) */ 
    { NCP_REGION_SPF,                   ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SPF,
    },

    /* 0x151.0     (337.0) */ 
    { NCP_REGION_SRIO_1_CONF,           ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SRIO_1_CONF,
    },

    /* 0x152.0     (338.0) */ 
    { NCP_REGION_I2C_2,                 ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_I2C_2,
    },


    /* 342.0 */ 
    { NCP_REGION_SYSCON,                ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SYSCON,
    },

    /* 342.1 */ 
    { NCP_REGION_X7_ECM,                ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_X7_ECM,
    },

    /* 343.0 */ 
    { NCP_REGION_IPI,                   ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_IPI,
    },

    /* 0x158.0   (344.0) */ 
    { NCP_REGION_X7_ELM_0,                 ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_ELM_0,
    },

    /* 0x159.0    (345.0) */ 
    { NCP_REGION_X7_ELM_1,                 ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_ELM_1,
    },

    /* 0x15a.0    (346.0) */ 
    { NCP_REGION_UART_3,                ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_UART_3,
    },

    /* 0x15b.0    (347.0) */ 
    { NCP_REGION_PL301_1,               ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_PL301_1_CONF,
    },

    /* 0x15c.0    (348.0) */ 
    { NCP_REGION_SMB,                   ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SMB,
    },

    /* 0x15d.0    (349.0) */ 
    { NCP_REGION_MTC,                   ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_MTC,
    },

    /* 0x160.0    (352.0) */ 
    { NCP_REGION_AXIS_GIC_CPU,          ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_AXIS_GIC_CPU,
    },

    /* 0x160.1    (352.1) */ 
    { NCP_REGION_AXIS_GIC_DIST,         ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_AXIS_GIC_DIST,
    },

    /* For the Seahawk GIC we use per-tgt paging so it's 
     * defined in the node_io_map below...  */

    /* 0x167.0   (359.0) */ 
    { NCP_REGION_ELM_0,                 ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_ELM_0,
    },

    /* 0x167.1    (359.1) */ 
    { NCP_REGION_ELM_1,                 ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_ELM_1,
    },

    /* 0x170.0   (368.0) */ 
    { NCP_REGION_AXI_MMAP_GPREG,        ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_AXI_MMAP_GPREG,
    },

    /* 0x170.1   (368.1) */ 
    { NCP_REGION_AXI_MMAP_SCB,          ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_AXI_MMAP_SCB,
    },

    /* 0x171.0   (369.0) */ 
    { NCP_REGION_AXI_PERIPH_GPREG,      ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_AXI_PERIPH_GPREG,
    },

    /* 0x171.1   (369.1) */ 
    { NCP_REGION_AXI_PERIPH_SCB,        ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_AXI_PERIPH_SCB,
    },

    /* 0x172.0   (370.0) */ 
    { NCP_REGION_AXI_PCI_GPREG,         ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_AXI_PCI_GPREG,
    },

    /* 0x172.1   (370.1) */ 
    { NCP_REGION_AXI_PCI_SCB,           ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_AXI_PCI_SCB,
    },

    /* 0x173.0   (371.0) */ 
    { NCP_REGION_AXI_USB_GPREG,         ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_AXI_USB_GPREG,
    },

    /* 0x173.1   (371.1) */ 
    { NCP_REGION_AXI_USB_SCB,           ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_AXI_USB_SCB,
    },



    /* *** DCR Peripherals *** */
    /* 384.0 */ 
    { NCP_REGION_DCR_ARB,               ncpDummyRegionMap,  
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_DCR_ARB,
    },

    /* 385.0 */ 
    { NCP_REGION_PLB6_ARB,              ncpDummyRegionMap,  
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_PLB6_ARB,
    },

    /* 386.0 */ 
    { NCP_REGION_TVSENSE,               ncpDummyRegionMap,  
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_TVSENSE,
    },

    /* 387.0 */ 
    { NCP_REGION_L2_0,                  ncpDummyRegionMap,  
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_L2_0,
    },

    /* 387.1 */ 
    { NCP_REGION_L2_0_INDIRECT,         ncpDummyRegionMap,
                                        __ncp_dev_l2_indirect_read,
                                        __ncp_dev_l2_indirect_write,
                                        0,
    },

    /* 387.2 */ 
    { NCP_REGION_L2_0_PMU,              ncpDummyRegionMap,
                                        __ncp_dev_l2_indirect_read,
                                        __ncp_dev_l2_indirect_write,
                                        0,
    },

    /* 388.0 */ 
    { NCP_REGION_L2_1,                  ncpDummyRegionMap,  
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_L2_1,
    },

    /* 388.1 */ 
    { NCP_REGION_L2_1_INDIRECT,         ncpDummyRegionMap,
                                        __ncp_dev_l2_indirect_read,
                                        __ncp_dev_l2_indirect_write,
                                        0,
    },

    /* 388.2 */ 
    { NCP_REGION_L2_1_PMU,              ncpDummyRegionMap,
                                        __ncp_dev_l2_indirect_read,
                                        __ncp_dev_l2_indirect_write,
                                        0,
    },

    /* 389.0 */ 
    { NCP_REGION_L2_2,                  ncpDummyRegionMap,  
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_L2_2,
    },

    /* 389.1 */ 
    { NCP_REGION_L2_2_INDIRECT,         ncpDummyRegionMap,
                                        __ncp_dev_l2_indirect_read,
                                        __ncp_dev_l2_indirect_write,
                                        0,
    },

    /* 389.2 */ 
    { NCP_REGION_L2_2_PMU,              ncpDummyRegionMap,
                                        __ncp_dev_l2_indirect_read,
                                        __ncp_dev_l2_indirect_write,
                                        0,
    },

    /* 390.0 */ 
    { NCP_REGION_L2_3,                  ncpDummyRegionMap,  
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_L2_3,
    },

    /* 390.1 */ 
    { NCP_REGION_L2_3_INDIRECT,         ncpDummyRegionMap,
                                        __ncp_dev_l2_indirect_read,
                                        __ncp_dev_l2_indirect_write,
                                        0,
    },

    /* 390.2 */ 
    { NCP_REGION_L2_3_PMU,              ncpDummyRegionMap,
                                        __ncp_dev_l2_indirect_read,
                                        __ncp_dev_l2_indirect_write,
                                        0,
    },

    /* 391.0 */ 
    { NCP_REGION_PPC_ITRACE,            ncpDummyRegionMap,
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_PPC_ITRACE,
    },

    /* 391.1 */ 
    { NCP_REGION_PPC_ITRACE_INDIRECT,   ncpDummyRegionMap,
                                        __ncp_dev_trace_indirect_read,
                                        __ncp_dev_trace_indirect_write,
                                        0,
    },

    /* 392.0 */ 
    { NCP_REGION_L2_0_TRACE,            ncpDummyRegionMap,
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_L2_0_TRACE,
    },

    /* 392.1 */ 
    { NCP_REGION_L2_0_TRACE_INDIRECT,   ncpDummyRegionMap,
                                        __ncp_dev_trace_indirect_read,
                                        __ncp_dev_trace_indirect_write,
                                        0,
    },

    /* 393.0 */ 
    { NCP_REGION_L2_1_TRACE,            ncpDummyRegionMap,  
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_L2_1_TRACE,
    },

    /* 393.1 */ 
    { NCP_REGION_L2_1_TRACE_INDIRECT,   ncpDummyRegionMap,
                                        __ncp_dev_trace_indirect_read,
                                        __ncp_dev_trace_indirect_write,
                                        0,
    },

    /* 394.0 */ 
    { NCP_REGION_L2_2_TRACE,            ncpDummyRegionMap,  
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_L2_2_TRACE,
    },

    /* 394.1 */ 
    { NCP_REGION_L2_2_TRACE_INDIRECT,   ncpDummyRegionMap,
                                        __ncp_dev_trace_indirect_read,
                                        __ncp_dev_trace_indirect_write,
                                        0,
    },

    /* 395.0 */ 
    { NCP_REGION_L2_3_TRACE,            ncpDummyRegionMap,  
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_L2_3_TRACE,
    },

    /* 395.1 */ 
    { NCP_REGION_L2_3_TRACE_INDIRECT,   ncpDummyRegionMap,
                                        __ncp_dev_trace_indirect_read,
                                        __ncp_dev_trace_indirect_write,
                                        0,
    },

    /* 396.0 */ 
    { NCP_REGION_LAM_TRACE,             ncpDummyRegionMap,  
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_LAM_TRACE,
    },

    /* 396.1 */ 
    { NCP_REGION_LAM_TRACE_INDIRECT,   ncpDummyRegionMap,
                                        __ncp_dev_trace_indirect_read,
                                        __ncp_dev_trace_indirect_write,
                                        0,
    },

    /* 397.0 */ 
    { NCP_REGION_CLK_CTRL,              ncpDummyRegionMap,
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_CLK_CTRL,
    },

    /* 25xx PLL regions */
    /* 397.1 */ 
    { NCP_REGION_SYSCON_CLK_SYS_PLLCTL, ncpDummyRegionMap,
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_SYS_PLL_CTRL,
    },

    /* 397.2 */ 
    { NCP_REGION_SYSCON_CLK_PPC_PLLCTL, ncpDummyRegionMap,
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_PPC_PLL_CTRL,
    },

    /* 397.3 */ 
    { NCP_REGION_SYSCON_CLK_TM_PLLCTL, ncpDummyRegionMap,
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_TM_PLL_CTRL,
    },

    /* 397.4 */ 
    { NCP_REGION_SYSCON_CLK_SM_PLLCTL, ncpDummyRegionMap,
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_SM_PLL_CTRL,
    },

    /* 397.5 */ 
    { NCP_REGION_SYSCON_CLK_NRCP_PLLCTL, ncpDummyRegionMap,
                                         __ncp_dev_dcr_read,
                                         __ncp_dev_dcr_write,
                                         NCP_DEV_PAGE_NRCP_PLL_CTRL,
    },

    /* 398.0 */ 
    { NCP_REGION_RESET_CTRL,            ncpDummyRegionMap,
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_RESET_CTRL,
    },

    /* 399.0 */ 
    { NCP_REGION_NHA,                   ncpDummyRegionMap,
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_NHA,
    },

    /* 400.0 */ 
    { NCP_REGION_P2A,                   ncpDummyRegionMap,
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_P2A,
    },

    /* 401.0 */ 
    { NCP_REGION_A2P,                   ncpDummyRegionMap,
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_A2P,
    },

    /* 402.0 */ 
    { NCP_REGION_MPIC_1,                ncpDummyRegionMap,
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_MPIC_1,
    },

    /* 403.0 */ 
    { NCP_REGION_MPIC_0,                ncpDummyRegionMap,
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_MPIC_0,
    },

    /* 404.0 */ 
    { NCP_REGION_LAM_MUX_CTRL,          ncpDummyRegionMap,
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_LAM_MUX_CTRL,
    },

    /* 405.0 */ 
    { NCP_REGION_ECM,                   ncpDummyRegionMap,
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_ECM,
    },

    /* 406.0 */ 
    { NCP_REGION_NRCP,                  ncpDummyRegionMap,
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_NRCP,
    },

    /* 407.0 */ 
    { NCP_REGION_MISC,                  ncpDummyRegionMap,
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_MISC,
    },

    /* 416.0 */ 
    { NCP_REGION_LCM,                   ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_LCM,
    },

    /* additional L2 slices for 3500 */
    /* 417.0 */ 
    { NCP_REGION_L2_4,                  ncpDummyRegionMap,  
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_L2_4,
    },

    /* 417.1 */ 
    { NCP_REGION_L2_4_INDIRECT,         ncpDummyRegionMap,
                                        __ncp_dev_l2_indirect_read,
                                        __ncp_dev_l2_indirect_write,
                                        0,
    },

    /* 417.2 */ 
    { NCP_REGION_L2_4_PMU,              ncpDummyRegionMap,
                                        __ncp_dev_l2_indirect_read,
                                        __ncp_dev_l2_indirect_write,
                                        0,
    },

    /* 418.0 */ 
    { NCP_REGION_L2_5,                  ncpDummyRegionMap,  
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_L2_5,
    },

    /* 418.1 */ 
    { NCP_REGION_L2_5_INDIRECT,         ncpDummyRegionMap,
                                        __ncp_dev_l2_indirect_read,
                                        __ncp_dev_l2_indirect_write,
                                        0,
    },

    /* 418.2 */ 
    { NCP_REGION_L2_5_PMU,              ncpDummyRegionMap,
                                        __ncp_dev_l2_indirect_read,
                                        __ncp_dev_l2_indirect_write,
                                        0,
    },

    /* 419.0 */ 
    { NCP_REGION_L2_4_TRACE,            ncpDummyRegionMap,
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_L2_4_TRACE,
    },

    /* 419.1 */ 
    { NCP_REGION_L2_4_TRACE_INDIRECT,   ncpDummyRegionMap,
                                        __ncp_dev_trace_indirect_read,
                                        __ncp_dev_trace_indirect_write,
                                        0,
    },

    /* 420.0 */ 
    { NCP_REGION_L2_5_TRACE,            ncpDummyRegionMap,  
                                        __ncp_dev_dcr_read,
                                        __ncp_dev_dcr_write,
                                        NCP_DEV_PAGE_L2_5_TRACE,
    },

    /* 420.1 */ 
    { NCP_REGION_L2_5_TRACE_INDIRECT,   ncpDummyRegionMap,
                                        __ncp_dev_trace_indirect_read,
                                        __ncp_dev_trace_indirect_write,
                                        0,
    },


    /* ACP25xx targets */
    /* 0x1b0 */
    { NCP_REGION_SBB,                   ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SBB,
    },

    /* 0x1c0 */
    { NCP_REGION_MSD,                   ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_MSD,
    },

    /* 0x1d0 */
    { NCP_REGION_SCB,                   ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SCB,
    },

    /* 0x1d2 */
    { NCP_REGION_TZC_0,                ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_TZC_0,
    },

    /* 0x1d3 */
    { NCP_REGION_LBI,                   ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_LBI,
    },

    /* 0x1d4 */
    { NCP_REGION_TZC_1,                 ncpDummyRegionMap,  
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_TZC_1,
    },

    /*
     * Virtual regions 0x200-0x2ff are software defined
     */
    /* 512.0 -  sysmem access via NCA Config Ring interface */
    { NCP_REGION_NCA_CR_SYSMEM,         ncpSysmemRegionMap,
                                        __ncp_dev_sysmem_cr_read,
                                        __ncp_dev_sysmem_cr_write,
                                        0,
    },

    /* 512.1 -  sysmem access via NCA NIC interface */
    { NCP_REGION_NCA_NIC_SYSMEM,        ncpSysmemRegionMap,
                                        __ncp_dev_sysmem_nic_read,
                                        __ncp_dev_sysmem_nic_write,
                                        0,
    },

    /* 512.2 -  paged sysmem access via PLB interface */
    { NCP_REGION_AXI_PLB_SYSMEM,        ncpSysmemRegionMap,
                                        __ncp_dev_paged_read,
                                        __ncp_dev_paged_write,
                                        NCP_DEV_PAGE_PLB_SYSMEM,
    },

    /* 512.3 -  paged sysmem access via PLB interface */
    { NCP_REGION_AXI_PLB_SYSMEM_LE,     ncpSysmemRegionMap,
                                        __ncp_dev_paged_read,
                                        __ncp_dev_paged_write,
                                        NCP_DEV_PAGE_PLB_SYSMEM_LE,
    },

    /* 513.0, 513.1 - little/big endian access to NCA DMA memory */
    { NCP_REGION_NCA_DMA_MEM_LE,        ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_DMA_MEM_LE,
    },

    { NCP_REGION_NCA_DMA_MEM_BE,        ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_DMA_MEM_BE,
    },

    /* 514.0, 514.1 - little/big endian access to NCA Shared Task memory */
    { NCP_REGION_NCA_TASK_MEM_LE,        ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_TASK_MEM_LE,
    },

    { NCP_REGION_NCA_TASK_MEM_BE,        ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_TASK_MEM_BE,
    },

    /*
     * 515.0, 515.1 - MPC RIO endpoint and message unit 
     */

    { NCP_REGION_MPC_RIO_ENDPOINT,      ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_MPC_RIO_ENDPOINT,
    },

    { NCP_REGION_MPC_RIO_MSG_UNIT,      ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_MPC_RIO_MSG_UNIT,
    },

    /* 516.0, 516.1 - little/big endian access to local host memory */
    { NCP_REGION_HOSTMEM_LE,            ncpDummyRegionMap,
                                        ncp_dev_hostmem_read,
                                        ncp_dev_hostmem_write,
                                        NCP_DEV_PAGE_HOSTMEM_LE,
    },

    { NCP_REGION_HOSTMEM_BE,            ncpDummyRegionMap,
                                        ncp_dev_hostmem_read,
                                        ncp_dev_hostmem_write,
                                        NCP_DEV_PAGE_HOSTMEM_BE,
    },

#ifdef NCP_PLX
    /*
     * 516.0  - PLX PEX8608 endpoint 
     */
    { NCP_REGION_PCIE_PLX,	        ncpDummyRegionMap,
					__ncp_dev_direct_read,
					__ncp_dev_direct_write,
					NCP_DEV_PAGE_PCIE0_BAR_1,
    },
#endif

    /* Node 0x300 - Simulator interface */
    { NCP_REGION_SIMULATOR_IF,          ncpDummyRegionMap,
                                        __ncp_dev_direct_read,
                                        __ncp_dev_direct_write,
                                        NCP_DEV_PAGE_SIMULATOR_IF,
    },

    /* Node 0x301 - Driver Configuration interface */
    { NCP_REGION_DRIVER_CFG,            ncpDummyRegionMap,
                                        __ncp_dev_internal_read,
                                        __ncp_dev_internal_write,
                                        0,
    },

    /* 0x302-0x304 are used for MDIO access */

    /* Node 0x305 - Driver CPCQ swstate debug */
    { NCP_REGION_DRIVER_SWSTATE,        ncpDummyRegionMap,
                                        ncp_dev_swstate_read,
                                        ncp_dev_swstate_write,
                                        0,
    },

    /* The End */
    {NCP_REGION_ID(NCP_MAX_NODE, NCP_MAX_TARGET), NULL, NULL, NULL}
};


/*
 * This table lists only those engines which support 
 * coherent system memory access. 
 *
 * For 5500 there we have separate offsets for control
 * and data registers. Unfortunately, the h/w doesn't
 * have all the control registers in the same place so
 * we need to define a separate table for 5500. 
 */

ncp_region_coh_io_t ncp_region_coherent_io_map[] =
{
    /* 0x1a.0x28 */
    { NCP_REGION_MPP_SENG,             ncpDummyRegionMap,
                                       __ncp_dev_coherent_read,
                                       __ncp_dev_coherent_write,
                                       NCP_SENG_ATOMIC_UPDATE_CONTROL0,
                                       0
    },

    /* 0x14.0x10 */
    { NCP_REGION_MTM_MTM_REGISTERS,    ncpDummyRegionMap,
                                       __ncp_dev_coherent_read,
                                       __ncp_dev_coherent_write,
                                       0x1064,  /* NCP_MTM_REGISTERS_ATOMIC_UPDATE_CONTROL0 */
                                       0
    },
    /* 0xb.0x10 */
    { NCP_REGION_SPP_MPE,              ncpDummyRegionMap,
                                       __ncp_dev_coherent_read,
                                       __ncp_dev_coherent_write,
                                       0x35f00200, /* NCP_MPE_L1_ATOMIC_ADD */
                                       0
    },

    /* The End (again) */
    {NCP_REGION_ID(NCP_MAX_NODE, NCP_MAX_TARGET), NULL, NULL, NULL}
};

ncp_region_coh_io_t ncp_region_coherent_io_map_5500[] =
{
    /* 0x1a.0x28 */
    { NCP_REGION_MPP_SENG,             ncpDummyRegionMap,
                                       __ncp_dev_coherent_read,
                                       __ncp_dev_coherent_write,
                                       0x640,
                                       0x600
                                       
    },

    /* 0x14.0x10 */
    { NCP_REGION_MTM_MTM_REGISTERS,    ncpDummyRegionMap,
                                       __ncp_dev_coherent_read,
                                       __ncp_dev_coherent_write,
                                       0x1064,      /* NCP_MTM_REGISTERS_ATOMIC_UPDATE_CONTROL0 */
                                       0x000016c0
    },
    /* 0xb.0x10 */
    { NCP_REGION_SPP_MPE,              ncpDummyRegionMap,
                                       __ncp_dev_coherent_read,
                                       __ncp_dev_coherent_write,
                                       0x35f00200,      /* NCP_MPE_L1_ATOMIC_ADD */
                                       0x35f00210       /* NCP_MPE_L1_ATOMIC_DATA_5500_BASE */
    },

    /* The End (again) */
    {NCP_REGION_ID(NCP_MAX_NODE, NCP_MAX_TARGET), NULL, NULL, NULL}
};


/*
 * this map defines regions for which each target in the node
 * uses the same access method. Note that if one or more targets
 * in the node use a different access method they may be listed
 * in the main region map which gets scanned first. 
 * It is up to the access function to validate the targetId. 
 */
ncp_region_io_t ncp_node_io_map[] =
{
    /* 0x110 */
    { NCP_REGION_EIOA_PHY_0,            ncpDummyRegionMap,  
                                        __ncp_dev_apb2ser_indirect_read,
                                        __ncp_dev_apb2ser_indirect_write,
                                        0,
    },

    /* 0x111 */
    { NCP_REGION_EIOA_PHY_1,            ncpDummyRegionMap,  
                                        __ncp_dev_apb2ser_indirect_read,
                                        __ncp_dev_apb2ser_indirect_write,
                                        0,
    },

    /* 0x112 */
    { NCP_REGION_EIOA_PHY_2,            ncpDummyRegionMap,  
                                        __ncp_dev_apb2ser_indirect_read,
                                        __ncp_dev_apb2ser_indirect_write,
                                        0,
    },

    /* 0x113 */
    { NCP_REGION_EIOA_PHY_3,            ncpDummyRegionMap,  
                                        __ncp_dev_apb2ser_indirect_read,
                                        __ncp_dev_apb2ser_indirect_write,
                                        0,
    },

    /* 0x114 */
    { NCP_REGION_EIOA_PHY_4,            ncpDummyRegionMap,  
                                        __ncp_dev_apb2ser_indirect_read,
                                        __ncp_dev_apb2ser_indirect_write,
                                        0,
    },

    /* 0x115 */
    { NCP_REGION_PCI_SRIO_PHY,          ncpDummyRegionMap,  
                                        __ncp_dev_apb2ser_indirect_read,
                                        __ncp_dev_apb2ser_indirect_write,
                                        0,
    },

    /* 0x1d1 */
    { NCP_REGION_APB2SER,               ncpDummyRegionMap,  
                                        ncp_dev_tgt_indexed_read,
                                        ncp_dev_tgt_indexed_write,
                                        NCP_DEV_PAGE_APB2SER,
    },

    /* APB2SER */
    /* 0x153  (339.0) */
    { NCP_REGION_APB2SER_PHY,           ncpDummyRegionMap,  
                                        ncp_dev_tgt_indexed_read,
                                        ncp_dev_tgt_indexed_write,
                                        NCP_DEV_PAGE_APB2SER_PHY,
    },

    /* 0x154  (340.0) */
    { NCP_REGION_APB2SER_CPM,           ncpDummyRegionMap,  
                                        ncp_dev_tgt_indexed_read,
                                        ncp_dev_tgt_indexed_write,
                                        NCP_DEV_PAGE_APB2SER_CPM,
    },

    /* 0x155  (341.0) */
    { NCP_REGION_APB2SER_CLK,           ncpDummyRegionMap,  
                                        ncp_dev_tgt_indexed_read,
                                        ncp_dev_tgt_indexed_write,
                                        NCP_DEV_PAGE_APB2SER_CLK,
    },

    /* 353.1 */ 
    { NCP_REGION_SEAHAWK_GIC_DIST,     ncpDummyRegionMap,  
                                        ncp_dev_tgt_indexed_read,
                                        ncp_dev_tgt_indexed_write,
                                        NCP_DEV_PAGE_SEAHAWK_GIC,
    },


    /* 0x1e0 : AXM5500 Dickens configuration target indexed */
    { NCP_REGION_DICKENS(0),           ncpDummyRegionMap,
                                       ncp_dev_tgt_indexed_read,
                                       ncp_dev_tgt_indexed_write,
                                       NCP_DEV_PAGE_DICKENS,
    },

    /* 0x1e0 : AXM5500 Coresight target indexed */
    { NCP_REGION_CORESIGHT(0),         ncpDummyRegionMap,
                                       ncp_dev_tgt_indexed_read,
                                       ncp_dev_tgt_indexed_write,
                                       NCP_DEV_PAGE_CORESIGHT,
    },

    /* 0x169 : XLF CDC target indexed */
    { NCP_REGION_AXI2SER9_CDC,         ncpDummyRegionMap,
                                       ncp_dev_tgt_indexed_read,
                                       ncp_dev_tgt_indexed_write,
                                       NCP_DEV_PAGE_AXI2SER9_CDC,
    },

    /* 0x148.0x10 - 0x148.0x45 : SERDES HSS PHY indirect access */
    { NCP_REGION_ID(0x148, 0x10),      ncpDummyRegionMap,
                                       __ncp_dev_hss_phy_read,
                                       __ncp_dev_hss_phy_write,
                                       0,
    },

    /* 0x1f0 : XLF CDC0 CORE */
    { NCP_REGION_CDC0_CORE(0),         ncpDummyRegionMap,
                                       ncp_dev_cdc_paged_read,
                                       ncp_dev_cdc_paged_write,
                                       0,
    },

    /* 0x1f1 : XLF CDC1 CORE */
    { NCP_REGION_CDC1_CORE(0),         ncpDummyRegionMap,
                                       ncp_dev_cdc_paged_read,
                                       ncp_dev_cdc_paged_write,
                                       0,
    },

    /* 0x1f2 : XLF CDC2 CORE */
    { NCP_REGION_CDC2_CORE(0),         ncpDummyRegionMap,
                                       ncp_dev_cdc_paged_read,
                                       ncp_dev_cdc_paged_write,
                                       0,
    },

    /* 0x1f3 : XLF CDC3 CORE */
    { NCP_REGION_CDC3_CORE(0),         ncpDummyRegionMap,
                                       ncp_dev_cdc_paged_read,
                                       ncp_dev_cdc_paged_write,
                                       0,
    },

    /* 0x206 Sysmem pool Vindex access */
    { NCP_REGION_SYSMEM_POOL_VINDEX(0),ncpDummyRegionMap,
                                       ncp_dev_sysmem_vindex_read,
                                       ncp_dev_sysmem_vindex_write,
                                       0,
    },

    /* 0x207 Sysmem pool Vindex access */
    { NCP_REGION_SYSMEM_POOL_VADDR(0), ncpDummyRegionMap,
                                       ncp_dev_sysmem_vaddr_read,
                                       ncp_dev_sysmem_vaddr_write,
                                       0,
    },


    /* Node 0x210.0-255: I2C protcocol communicating with mult devices, Dev 0 */
    { NCP_REGION_I2C_PROTOCOL(0),      ncpDummyRegionMap,
                                       __ncp_dev_i2cprot_read,
                                       __ncp_dev_i2cprot_write,
                                       NCP_REGION_I2C,
    },

    /* Node 0x211.0-255: I2C protcocol communicating with mult devices, Dev 1 */
    { NCP_REGION_I2C_1_PROTOCOL(0),    ncpDummyRegionMap,
                                       __ncp_dev_i2cprot_read,
                                       __ncp_dev_i2cprot_write,
                                       NCP_REGION_I2C_1,
    },

    /* Node 0x212.0-255: I2C protcocol communicating with mult devices, Dev 2 */
    { NCP_REGION_I2C_2_PROTOCOL(0),    ncpDummyRegionMap,
                                       __ncp_dev_i2cprot_read,
                                       __ncp_dev_i2cprot_write,
                                       NCP_REGION_I2C_2,
    },

    /* Node 0x218.0-255: SMB/I2C protcocol communicating with mult devices, Dev 0 */
    { NCP_REGION_SMB_0_PROTOCOL(0),    ncpDummyRegionMap,
                                       __ncp_dev_i2cprot_read,
                                       __ncp_dev_i2cprot_write,
                                       NCP_REGION_SMB,
    },

    /* Node 0x220.0-15: external devices over LBI bus */
    { NCP_REGION_LBI_DEVICE(0),        ncpDummyRegionMap,
                                       __ncp_dev_lbi_read,
                                       __ncp_dev_lbi_write,
                                       0,
    },

    /* Node 0x302.0 0x302.0x1F - Clause 22 MDIO PHY interface */
    { NCP_REGION_C22_MDIO_PHY(0),      ncpDummyRegionMap,
                                       __ncp_dev_mdio_read,
                                       __ncp_dev_mdio_write,
                                       0,
    },

    /* Node 0x303.0 0x303.0x1F - Clause 45 MDIO PHY interface */
    { NCP_REGION_C45_MDIO_PHY(0),       ncpDummyRegionMap,
                                        __ncp_dev_mdio_read,
                                        __ncp_dev_mdio_write,
                                        0,
    },

    /* Node 0x303.0 0x303.0x1F - Clause 45 MDIO ADR interface */
    { NCP_REGION_C45_MDIO_ADR(0),       ncpDummyRegionMap,
                                        __ncp_dev_mdio_read,
                                        __ncp_dev_mdio_write,
                                        0,
    },


    /* The End (again) */
    {NCP_REGION_ID(NCP_MAX_NODE, NCP_MAX_TARGET),
     NULL, NULL, NULL}
};

ncp_node_per_tgt_offset_t 
ncp_node_per_tgt_offset[] = {
    { NCP_REGION_APB2SER,      0x00000010 },
    { NCP_REGION_APB2SER_PHY,  0x00000010 },
    { NCP_REGION_APB2SER_CPM,  0x00000040 },
    { NCP_REGION_APB2SER_CLK,  0x00000800 },
    { NCP_REGION_DICKENS(0),   0x00010000 },
    { NCP_REGION_CORESIGHT(0), 0x00001000 },
    { NCP_REGION_SEAHAWK_GIC_DIST, 0x00001000 },
    { NCP_REGION_AXI2SER9_CDC,  0x00020000 },
    { NCP_REGION_ID(NCP_MAX_NODE, NCP_MAX_TARGET)}
}; 




#endif /* __NCP_REGION_REGION_MAP_H__ */
