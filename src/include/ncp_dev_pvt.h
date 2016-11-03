/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


#ifndef __NCP_DEV_PVT_H__
#define __NCP_DEV_PVT_H__

#include "ncp_sal.h"

#if defined ( NCP_KERNEL ) && ! defined ( NCP_OSE ) && ! defined ( NCP_VXWORKS )

#include <linux/version.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 2, 9)
extern void acp_spin_lock_init(void *);
extern void acp_spin_lock(void *);
extern void acp_spin_unlock(void *);
extern void acp_spin_lock_bh(void *);
extern void acp_spin_unlock_bh(void *);
extern void acp_spin_lock_irqsave(void *, unsigned long);
extern void acp_spin_unlock_irqrestore(void *, unsigned long);
#endif

#endif

/* BEGIN: Important forward type references */

typedef struct ncp_region_io_s ncp_region_io_t;
typedef struct ncp_region_coh_io_s ncp_region_coh_io_t;
typedef struct ncp_dev_s       ncp_dev_t;
typedef struct ncp_dev_cpcq_s  ncp_dev_cpcq_t;

/* END:   Important forward type references */

#include "ncp.h"
#include "ncp_pvt.h"
#if 0
#ifndef NCP_KERNEL
#include "ncp.h"
#include "ncp_pvt.h"
#else
#include "ncp_api_trace.h"
#endif
#endif

#include "ncp_regions.h"
#include "ncp_dev.h"
#include "regs/ncp_nca_regs.h"
#include "regs/ncp_nca_reg_defines.h"
#include "ncp_dev_config_regs.h"
#include "regs/ncp_pei_reg_defines.h"

#include "ncp_intr_mpic.h"
#include "ncp_intr_mpic_x3.h"
#include "ncp_intr_gic.h"
#include "ncp_intr_x9.h"
#include "regs/ncp_misc_regs.h"

#include "ncp_intr_gic.h"

#include "ncp_syscon_rst_regs.h"
#include "ncp_syscon_rst_reg_defines.h"

#include "ncp_syscon_regs.h"
#include "ncp_syscon_reg_defines.h"

#include "regs/ncp_cfg_node_regs.h"
#include "regs/ncp_cfg_node_reg_defines.h"

#include "regs/ncp_ddr_reg_defines.h"

#include "regs/ncp_seng_regs.h"
#include "regs/ncp_seng_reg_defines.h"

#include "regs/ncp_tmgr_system_count_reg_defines.h"
#include "regs/ncp_timer_core_reg_defines.h"

#include "regs/ncp_x7_nrcp_reg_defines.h"
#include "regs/ncp_x7_nrcp_regs.h"

#include "ncp_dev_cat_pvt.h"

#include "ncp_alarm_ext.h"

/* --- Linux References --- */
#define NCP_MOD_NAME        "ncp"

/* ---- Conditional Debug */
#undef NCP_NCA_DBG_BOTTOM_HALF

/* --- Module Parameters --- */
extern int ncp_devs_found;
extern int ncp_devs_configured;
extern int ncp_access_checking;
extern int ncp_scatter_checking;
extern unsigned int ncp_vendor_id;
extern unsigned int ncp_device_id;
extern int ncp_safe_mode;
extern int ncp_pio_write_delay;
extern int ncp_pio_read_delay;
extern ncp_bool_t nca_axi_lock_required;
extern ncp_bool_t nca_int_generation_bug;
extern ncp_bool_t nca_wait_timeout_required;
extern int ncp_dma_threshold;

extern int ncp_trace_level;

#if defined(NCP_DEV_SRIOEP)
extern int ncp_srio_root_regs_start;
extern int ncp_srio_root_regs_length;
extern int ncp_srio_debug;
#endif


ncp_st_t
ncp_dev_task_mem_unmap(ncp_dev_t *dev);

void 
ncp_task_v2_free_swMem(void);

void
ncp_dev_ncav2_set_irq_affinity(int grp, int irq);

ncp_st_t
ncp_task_v2_kmode_available_blocks_get(ncp_dev_hdl_t devHdl,
                                       ncp_uint32_t poolId,
                                       ncp_uint32_t blockSize,
                                       ncp_uint32_t *numBlocks);

/*!
 * @fn ncp_st_t ncp_dev_timer_sync_external( ncp_dev_hdl_t devHdl);
 * @brief This function syncs the external clock to the Nuevo TS
 * @param devHdl     IN: Device handle
 */

#define NCP_TIMER_MAX_POLL_TIME                10000 /* 10ms */
#define NCP_TIMER_ITER_POLL_TIME               1000  /* 1ms */
#define NCP_TIMER_NUM_POLL_ITERS  (NCP_TIMER_MAX_POLL_TIME / NCP_TIMER_ITER_POLL_TIME)

ncp_st_t ncp_dev_timer_sync_external(ncp_dev_hdl_t devHdl);

#if defined(NCP_LINUX) && defined(NCP_KERNEL)
#define NCP_TASK_V2_GET_PGIT_UPLOAD_PERIOD(_grp) \
    ncp_task_v2_get_pgit_upload_period(_grp)
#define NCP_TASK_V2_FREE_SWMEM() ncp_task_v2_free_swMem()
#define NCP_DEV_NCAV2_SET_IRQ_AFFINITY(_grp, _irq) \
    ncp_dev_ncav2_set_irq_affinity(_grp, (_irq)) 
#else
#define NCP_TASK_V2_GET_PGIT_UPLOAD_PERIOD(_grp)
#define NCP_TASK_V2_FREE_SWMEM() /* NcaV2 is presently linux only! */
#define NCP_DEV_NCAV2_SET_IRQ_AFFINITY(_grp, _irq)
#endif /* defined(NCP_LINUX) && defined(NCP_KERNEL) */


#define NCP_EIOA_USE_INTR_55XX
#define NCP_EIOA_USE_INTR_35XX

/*
#define NCP_EIOA_USE_INTR_34XX
*/

extern int ncp_pka_in_fpga;

/*
 * ncaV1 has 6 queue groups,   but ncaV2 has 16,  so we need to make sure
 * all structs are allocated such that they can support wither ncaV1 or ncaV2
 * since we do not build separate versions for ncaV1 and ncaV2.
 */
 
#define NCP_NCA_MAX_PCQ_GROUPS 16

#define NCP_DEV_ACCESS_NONE            (0x00)
#define NCP_DEV_ACCESS_READ            (0x01)
#define NCP_DEV_ACCESS_WRITE           (0x02)
#define NCP_DEV_ACCESS_RW              (0x03)
#define NCP_DEV_ACCESS_BIG_ENDIAN      (0x04)
#define NCP_DEV_ACCESS_LITTLE_ENDIAN   (0x08)
#define NCP_DEV_ACCESS_ENDIAN          (0x0c)
#define NCP_DEV_ACCESS_IO_SYNC         (0x10)
#define NCP_DEV_ACCESS_PAGED           (0x20)

#define NCP_DEV_PAGE_MAPPED           (0x0100)


/* --- Internal Types & Definitions --- */

#define NCP_DEV_TAG         (0x67103388)    /* TODO - need a real tag for NCP*/

#ifdef NCP_BIG_ENDIAN
#define NCP_HOST_TO_BUS16(n) \
         ((((ncp_uint16_t)(n) >>  8) & 0x00ff) |  \
          (((ncp_uint16_t)(n) <<  8) & 0xff00))

#define NCP_HOST_TO_BUS32(n) \
        ((((ncp_uint32_t)(n) >> 24) & 0x000000ff) |  \
         (((ncp_uint32_t)(n) >>  8) & 0x0000ff00) |  \
         (((ncp_uint32_t)(n) <<  8) & 0x00ff0000) |  \
         (((ncp_uint32_t)(n) << 24) & 0xff000000))

#else
#define NCP_HOST_TO_BUS16(n) (n)
#define NCP_HOST_TO_BUS32(n) (n)
#endif /* NCP_BIG_ENDIAN */

#define NCP_BUS_TO_HOST16(n) NCP_HOST_TO_BUS16(n)
#define NCP_BUS_TO_HOST32(n) NCP_HOST_TO_BUS32(n)


#define NCP_DEV_CACHE_LINE_SHIFT_BITS    (4)      /* 16 bytes */
#define NCP_DEV_CACHE_LINE_SIZE          ( 1 << NCP_DEV_CACHE_LINE_SHIFT_BITS)
#define NCP_DEV_CACHE_LINE_ALIGN_MASK    (NCP_DEV_CACHE_LINE_SIZE - 1)
#define NCP_DEV_CACHE_LINE_MASK          (~NCP_DEV_CACHE_LINE_ALIGN_MASK)


#define EXTERNAL_HOST  /* TODO: Should get this from configuration! */

#define NCP_DEV_CMEM_ZQ_TIMER_INTERVAL               100   /* ms */
#define NCP_DEV_CMEM_ZQ_MAX_POLL_TIME                5000  /* 5ms */
#define NCP_DEV_CMEM_ZQ_ITER_POLL_TIME               100   /* 100us */
#define NCP_DEV_CMEM_ZQ_POLL_ITERS  (NCP_DEV_CMEM_ZQ_MAX_POLL_TIME / NCP_DEV_CMEM_ZQ_ITER_POLL_TIME)
#define NCP_DEV_CMEM_DDR_ACTIVE                      0x2



/*
 * NCP direct paged access
 *
 */

enum {
    /* Raw BAR access pages */
    NCP_DEV_PAGE_PCIE0_BAR_0 = 0,
    NCP_DEV_PAGE_PCIE0_BAR_1,
    NCP_DEV_PAGE_PCIE0_BAR_2,
    NCP_DEV_PAGE_PCIE0_PEI,
    NCP_DEV_PAGE_PCIE0_AXI_SLV,

    NCP_DEV_PAGE_PCIE1_BAR_0,
    NCP_DEV_PAGE_PCIE1_BAR_1,
    NCP_DEV_PAGE_PCIE1_BAR_2,
    NCP_DEV_PAGE_PCIE1_PEI,
    NCP_DEV_PAGE_PCIE1_AXI_SLV,

    NCP_DEV_PAGE_PCIE2_BAR_0,
    NCP_DEV_PAGE_PCIE2_BAR_1,
    NCP_DEV_PAGE_PCIE2_BAR_2,
    NCP_DEV_PAGE_PCIE2_PEI,
    NCP_DEV_PAGE_PCIE2_AXI_SLV,

    NCP_DEV_PAGE_SRIO_PIO_WIN_0,
    NCP_DEV_PAGE_SRIO_PIO_WIN_1,
    NCP_DEV_PAGE_SRIO_PIO_WIN_2,
    NCP_DEV_PAGE_SRIO_PIO_WIN_3,
    NCP_DEV_PAGE_SRIO_PIO_WIN_4,
    NCP_DEV_PAGE_SRIO_PIO_WIN_5,
    NCP_DEV_PAGE_SRIO_PIO_WIN_6,
    NCP_DEV_PAGE_SRIO_PIO_WIN_7,
    NCP_DEV_PAGE_SRIO_PIO_WIN_8,
    NCP_DEV_PAGE_SRIO_PIO_WIN_9,
    NCP_DEV_PAGE_SRIO_PIO_WIN_10,
    NCP_DEV_PAGE_SRIO_PIO_WIN_11,
    NCP_DEV_PAGE_SRIO_PIO_WIN_12,
    NCP_DEV_PAGE_SRIO_PIO_WIN_13,
    NCP_DEV_PAGE_SRIO_PIO_WIN_14,
    NCP_DEV_PAGE_SRIO_PIO_WIN_15,
    NCP_DEV_PAGE_SRIO_CFG_GRIO,
    NCP_DEV_PAGE_SRIO_CFG_RAB,
    NCP_DEV_PAGE_SRIO_AXI_SLV,

    /* do we really need all those PIO_WINs?? */
    NCP_DEV_PAGE_SRIO_1_CFG_GRIO,
    NCP_DEV_PAGE_SRIO_1_CFG_RAB,
    NCP_DEV_PAGE_SRIO_1_AXI_SLV,

    /* special regions */
    NCP_DEV_PAGE_DMA_MEM_LE,
    NCP_DEV_PAGE_DMA_MEM_BE,
    NCP_DEV_PAGE_TASK_MEM_LE,
    NCP_DEV_PAGE_TASK_MEM_BE,
    NCP_DEV_PAGE_PLB_SYSMEM,
    NCP_DEV_PAGE_PLB_SYSMEM_LE,
    NCP_DEV_PAGE_HOSTMEM_LE,
    NCP_DEV_PAGE_HOSTMEM_BE,

    NCP_DEV_PAGE_MPC_RIO_ENDPOINT,
    NCP_DEV_PAGE_MPC_RIO_MSG_UNIT,

    NCP_DEV_PAGE_SIMULATOR_IF,

    /* AXI address mappings */
    /* DCR */
    NCP_DEV_PAGE_DCR_ARB,
    NCP_DEV_PAGE_PLB6_ARB,
    NCP_DEV_PAGE_TVSENSE,
    NCP_DEV_PAGE_L2_0,
    NCP_DEV_PAGE_L2_1,
    NCP_DEV_PAGE_L2_2,
    NCP_DEV_PAGE_L2_3,
    NCP_DEV_PAGE_L2_4,          /* AXM3500 */
    NCP_DEV_PAGE_L2_5,          /* AXM3500 */
    NCP_DEV_PAGE_PPC_ITRACE,
    NCP_DEV_PAGE_L2_0_TRACE,
    NCP_DEV_PAGE_L2_1_TRACE,
    NCP_DEV_PAGE_L2_2_TRACE,
    NCP_DEV_PAGE_L2_3_TRACE,
    NCP_DEV_PAGE_L2_4_TRACE,    /* AXM3500 */
    NCP_DEV_PAGE_L2_5_TRACE,    /* AXM3500 */
    NCP_DEV_PAGE_LAM_TRACE,
    NCP_DEV_PAGE_CLK_CTRL,
    NCP_DEV_PAGE_SYS_PLL_CTRL,  /* ACP2500 only */
    NCP_DEV_PAGE_PPC_PLL_CTRL,  /* ACP2500 only */
    NCP_DEV_PAGE_TM_PLL_CTRL,   /* ACP2500 only */
    NCP_DEV_PAGE_SM_PLL_CTRL,   /* ACP2500 only */
    NCP_DEV_PAGE_NRCP_PLL_CTRL, /* ACP2500 only */
    NCP_DEV_PAGE_RESET_CTRL,
    NCP_DEV_PAGE_NHA,
    NCP_DEV_PAGE_P2A,
    NCP_DEV_PAGE_A2P,
    NCP_DEV_PAGE_LAM_MUX_CTRL,  /* ACP34xx only */
    NCP_DEV_PAGE_ECM,           /* ACP2500 only */
    NCP_DEV_PAGE_NRCP,          /* ACP2500 only */
    NCP_DEV_PAGE_MISC,          /* ACP2500 only */
    NCP_DEV_PAGE_MPIC_1,
    NCP_DEV_PAGE_MPIC_0,


    /* APB - not all exist on every chipType */
    NCP_DEV_PAGE_GPIO_0,
    NCP_DEV_PAGE_GPIO_1,
    NCP_DEV_PAGE_SSP,
    NCP_DEV_PAGE_SRIO_GPREG,
    NCP_DEV_PAGE_I2C_0,
    NCP_DEV_PAGE_I2C_1,
    NCP_DEV_PAGE_I2C_2,
    NCP_DEV_PAGE_UART_0,
    NCP_DEV_PAGE_UART_1,
    NCP_DEV_PAGE_UART_2,
    NCP_DEV_PAGE_UART_3,
    NCP_DEV_PAGE_TIMER,
    NCP_DEV_PAGE_MDIO,
    NCP_DEV_PAGE_APB2RC,
    NCP_DEV_PAGE_GPREG,

    NCP_DEV_PAGE_SRIO_CONF,
    NCP_DEV_PAGE_SRIO_1_CONF,
    NCP_DEV_PAGE_PL301_0_CONF,
    NCP_DEV_PAGE_PL301_1_CONF,
    NCP_DEV_PAGE_PL301_2_CONF,

    NCP_DEV_PAGE_LBI,
    NCP_DEV_PAGE_SCB,
    NCP_DEV_PAGE_APB2SER,
    NCP_DEV_PAGE_TZC_0,
    NCP_DEV_PAGE_TZC_1,

    /* AHB */
    NCP_DEV_PAGE_NAND,
    NCP_DEV_PAGE_TRNG,
    NCP_DEV_PAGE_FEMAC,
    NCP_DEV_PAGE_USB,
    NCP_DEV_PAGE_GPDMA_0,
    NCP_DEV_PAGE_GPDMA_1,

    NCP_DEV_PAGE_MSD,
    NCP_DEV_PAGE_SBB,

    /* !!!! START OF AXI PERIPHERALS !!!! */
    NCP_DEV_PAGE_NCA,
    NCP_DEV_PAGE_PKA,
    NCP_DEV_PAGE_ROM,
    NCP_DEV_PAGE_LCM,

    /* AXM5500 */
    NCP_DEV_PAGE_LSM,
    NCP_DEV_PAGE_MME_CONF,

    NCP_DEV_PAGE_XVRC,
    NCP_DEV_PAGE_SPF,
    NCP_DEV_PAGE_SYSCON,
    NCP_DEV_PAGE_X7_ECM,
    NCP_DEV_PAGE_IPI,
    NCP_DEV_PAGE_ELM_0,
    NCP_DEV_PAGE_ELM_1,
    NCP_DEV_PAGE_SMB,
    NCP_DEV_PAGE_MTC,
    NCP_DEV_PAGE_AXIS_GIC_CPU,
    NCP_DEV_PAGE_AXIS_GIC_DIST,
    NCP_DEV_PAGE_SEAHAWK_GIC,

    NCP_DEV_PAGE_APB2SER_PHY,
    NCP_DEV_PAGE_APB2SER_CPM,
    NCP_DEV_PAGE_APB2SER_CLK,

    NCP_DEV_PAGE_DICKENS,
    NCP_DEV_PAGE_M3SS,
    NCP_DEV_PAGE_STM,
    NCP_DEV_PAGE_CORESIGHT,

    /* AXM5600 */
    NCP_DEV_PAGE_AXI2SER4_CPM,
    NCP_DEV_PAGE_AXI2SER5,
    NCP_DEV_PAGE_AXI2SER6_USB,
    NCP_DEV_PAGE_AXI2SER7_ELM,
    /* AXI2SER_7 is, for now, the ELM */


    /* Lionfish */
    NCP_DEV_PAGE_AXI2SER8_NCAP,
    NCP_DEV_PAGE_AXI2SER9_CDC,
    NCP_DEV_PAGE_AXI2SER10_NLINK,
    NCP_DEV_PAGE_AXI2SER11,

    NCP_DEV_PAGE_SATA_CFG_0,
    NCP_DEV_PAGE_SATA_CFG_1,


    NCP_DEV_PAGE_AXI_MMAP_GPREG,
    NCP_DEV_PAGE_AXI_MMAP_SCB,
    NCP_DEV_PAGE_AXI_PERIPH_GPREG,
    NCP_DEV_PAGE_AXI_PERIPH_SCB,
    NCP_DEV_PAGE_AXI_PCI_GPREG,
    NCP_DEV_PAGE_AXI_PCI_SCB,
    NCP_DEV_PAGE_AXI_USB_GPREG,
    NCP_DEV_PAGE_AXI_USB_SCB,


    /* !!!! END OF TABLE MARKER */
    NCP_DEV_MAX_PAGES
};

typedef struct {
    ncp_uint32_t  pageId;
    char          *name;
} ncp_dev_page_name_t;


#define NCP_DEV_SRIO_NUM_PIO_WIN 16
#define NCP_DEV_PAGE_SRIO_PIO_WIN(n) (NCP_DEV_PAGE_SRIO_PIO_WIN_0 + n)


/* 
 * the ppc476 simulator uses the top 256 bytes of NCA AXI register 
 * space as our simulator control registers. We map this for all
 * platforms, on h/w these registers all read as 0.
 */
#define NCP_DEV_SIM_IF_REG_OFFSET 0x0001ff00


typedef struct ncp_task_ncaV2_domain_bundle_s
{
    ncp_uint64_t sharedPhysAddr;
    ncp_int32_t  sharedSize;
    void         *kernVA;    
    ncp_bool_t   isMapped;
}ncp_task_ncaV2_domain_bundle_t;


typedef struct {
    int          id;
    ncp_uint64_t busAddr; /* 38-bit AXI address */
    ncp_uint32_t size;
    ncp_uint32_t flags;
} ncp_dev_addr_map_t;

typedef struct {
    void *          addr;       /* CPU virtual address */
    ncp_uint64_t    axiAddr;    /* 38-bit AXI address  */
    ncp_uint32_t    size;
    ncp_uint32_t    flags;
    ncp_uint32_t    curBase;    /* currently mapped page base for dynamic mappings */
    ncp_uint32_t    extraData;  /* access-method specific */
    char           *name;
} ncp_dev_page_t;

typedef struct {
    ncp_dev_addr_map_t  *map;
    ncp_uint32_t        numPages;
    char                *name;
} ncp_dev_mappings_t;

typedef ncp_st_t (*ncp_dev_bus_dyn_page_map_fn_t) (
        ncp_uint32_t    devNum,
        ncp_uint32_t    pageBase,
        ncp_dev_page_t *page);
        

/* ============================================
 * New ISR specific-wakeup support - Common across all hw platforms and operating systems
 */
 
typedef ncp_uint32_t (*ncp_cfgDma_condition_met_fn_ptr_t)(ncp_dev_cpcq_t *pcq,  ncp_uint16_t idx);

typedef struct ncp_cfgDma_condition_met_s {
     ncp_cfgDma_condition_met_fn_ptr_t conditionMetFn;
     ncp_dev_cpcq_t *pcq;
     ncp_uint16_t idx;
} ncp_cfgDma_condition_met_t;     
     
typedef ncp_bool_t (*ncp_iTask_condition_met_fn_ptr_t)(
                                         ncp_dev_t * dev,
                                         ncp_uint32_t grp, 
                                         ncp_uint32_t iPCQmask,
                                         ncp_uint32_t myTqsBitMask,
                                         ncp_st_t   *pNcpStatus);
                                         
typedef struct ncp_iTask_condition_met_s {
     ncp_iTask_condition_met_fn_ptr_t conditionMetFn;
     ncp_uint32_t grp;
     ncp_uint32_t iPCQmask;
     ncp_uint32_t myTqsBitMask;
     ncp_st_t   *pNcpStatus;    
} ncp_iTask_condition_met_t; 

typedef ncp_bool_t (*ncp_oTask_condition_met_fn_ptr_t)(
                                         ncp_dev_t * dev,
                                         ncp_uint32_t grp,
                                         ncp_uint32_t grpRelQueueId,
                                         ncp_uint32_t  myTqsBitMask,
                                         ncp_st_t    *pNcpStatus);
                                         
typedef ncp_oTask_condition_met_fn_ptr_t ncp_tTask_condition_met_fn_ptr_t;
                                           
typedef struct ncp_oTask_condition_met_s {
     ncp_oTask_condition_met_fn_ptr_t conditionMetFn;    
     ncp_uint32_t grp;
     ncp_uint32_t grpRelQueueId;
     ncp_uint32_t  myTqsBitMask;
     ncp_st_t    *pNcpStatus;
} ncp_oTask_condition_met_t;  

typedef ncp_oTask_condition_met_t ncp_tTask_condition_met_t;

/*
 * Used *only* for cfgDma, iTask, oTask (55xx +) and cfgDma iTask, oTask, and tTask (34/35xx) ISR handling.
 */
typedef union ncp_isr_condition_test_u {
    ncp_iTask_condition_met_t  iTaskConditionMet;
    ncp_oTask_condition_met_t  oTaskConditionMet;    
    ncp_tTask_condition_met_t  tTaskConditionMet;
    ncp_cfgDma_condition_met_t cfgDmaConditionMet;   
} ncp_isr_condition_test_t;

/*
 * This is the structure that will be hung of the specific nca group interrupt.
 * The isr will run this list waking up only those threads whose wait condition has been satisfied.
 */
typedef struct ncp_task_isr_wait_object_s 
{
    struct ncp_task_isr_wait_object_s  *pNextWaitObj;
    ncp_isr_condition_test_t           waitCondition;
    ncp_task_isr_wait_primitive_t      *pWaitPrimitive;
#ifdef NCP_OSE
    PROCESS                             pid;
    int                                 sigNum;
    int                                 signalled;    
#endif    
} ncp_task_isr_wait_object_t;
 
 
/*
 * The following macros should only be used by Task I/O clients,   as they assume a 
 * pool of wait objects and fined grain wait/wakeup support.
 */
 
#define NCP_TASK_ISR_GET_WAITOBJ(_head, _pWaitObj) \
    ncp_task_isr_get_waitObj((_head), (_pWaitObj))

   
#define NCP_TASK_ISR_FREE_ALL_WAITOBJS(_head) \
{                                             \
    ncp_task_isr_free_all_waitObjs(_head);    \
    _head = NULL;                             \
}    

#define NCP_TASK_ISR_REMOVE_WAITOBJ(_head, _pWaitObj) \
    ncp_task_isr_remove_waitObj((_head), _pWaitObj)                
    
    
#define NCP_TASK_ISR_PUT_WAITOBJ(_head, _pWaitObj) \
    ncp_task_isr_put_waitObj((_head), _pWaitObj) 
 
void 
ncp_task_isr_event_force_wakeup_all(ncp_task_isr_wait_object_t *pWaitListHead);

#define NCP_TASK_ISR_EVENT_FORCE_WAKEUP_ALL(_pWaitObj, _isrLock)    \
{                                                                   \
    NCP_RAW_SPINLOCK_FLAGS(_flags);                                 \
    NCP_RAW_SPINLOCK_INTERRUPT_DISABLE(&(_isrLock), _flags);        \
    ncp_task_isr_event_force_wakeup_all(_pWaitObj);                 \
    NCP_RAW_SPINLOCK_INTERRUPT_ENABLE(&(_isrLock), _flags);         \
}

/*
 * TX Complete selective wakeup
 */
void
ncp_task_isr_txTask_selective_wakeup(ncp_dev_t *dev,
                                     ncp_task_isr_wait_object_t *pWaitListHead);
#define NCP_TASK_ISR_TX_SELECTIVE_WAKEUP(_dev, _wait_head) \
        ncp_task_isr_txTask_selective_wakeup(_dev, _wait_head);
    
/*
 * Task Completion Complete selective wakeup
 */
void
ncp_task_isr_tComp_selective_wakeup(ncp_dev_t *dev,
                                     ncp_task_isr_wait_object_t *pWaitListHead);
#define NCP_TASK_ISR_TCOMP_SELECTIVE_WAKEUP(_dev, _wait_head) \
        ncp_task_isr_tComp_selective_wakeup(_dev, _wait_head);      

/*
 * RX Task Arrival selective wakeup
 */    
void
ncp_task_isr_rxTask_selective_wakeup(ncp_dev_t *dev,
                                     ncp_task_isr_wait_object_t *pWaitListHead);
#define NCP_TASK_ISR_RX_SELECTIVE_WAKEUP(_dev, _wait_head) \
    ncp_task_isr_rxTask_selective_wakeup(_dev, _wait_head);     
 
/*
 * cfgDma complete selective wakeup
 */      
void
ncp_cfgdma_isr_selective_wakeup(ncp_dev_cpcq_t *pCPCQ);
    
#define NCP_CFGDMA_ISR_SELECTIVE_WAKEUP(_cpcq, _isrLock) \
{                                                                   \
    NCP_RAW_SPINLOCK_FLAGS(_flags);                                 \
    NCP_RAW_SPINLOCK_INTERRUPT_DISABLE(&(_isrLock), _flags);        \
    ncp_cfgdma_isr_selective_wakeup(_cpcq);                         \
    NCP_RAW_SPINLOCK_INTERRUPT_ENABLE(&(_isrLock), _flags);         \
}      
    
#define NCP_TASK_ISR_EVENT_ADD_TO_WAITLIST(_ppWaitList,_pWaitObj)   \
{                                                                   \
   NCP_TASK_ISR_PUT_WAITOBJ((_ppWaitList),(_pWaitObj));             \
} 

ncp_st_t 
ncp_task_isr_event_freelist_init(ncp_task_isr_wait_object_t **pFreeListObjs, int num);

#define NCP_TASK_ISR_EVENT_FREELIST_INIT(_pFreeListObjs, _num)      \
    ncp_task_isr_event_freelist_init(_pFreeListObjs, _num)

#define NCP_TASK_ISR_EVENT_OBJECT_FREE(_pWaitObj)   \
    if (_pWaitObj)                                  \
    {                                               \
        if ((_pWaitObj)->pWaitPrimitive)            \
        {                                           \
            NCP_WAITQ_FREE((_pWaitObj)->pWaitPrimitive);  \
        }                                           \
        ncp_free(_pWaitObj);                        \
    }


ncp_st_t
ncp_dev_enable_1shot_nca_rx_ints(ncp_dev_hdl_t devHdl, 
                                 ncp_uint8_t grp,
                                 ncp_iTask_condition_met_fn_ptr_t conditionMetFn,
                                 ncp_uint32_t grpRelQueueId,
                                 ncp_uint32_t myTqsBitMask,
                                 ncp_task_isr_wait_object_t **ppWaitStruct,
                                 ncp_st_t                   *pNcpStatus);
ncp_st_t
ncp_dev_enable_1shot_nca_tx_ints(ncp_dev_hdl_t devHdl, 
                                 ncp_uint8_t grp,
                                 ncp_oTask_condition_met_fn_ptr_t conditionMetFn,
                                 ncp_uint32_t grpRelQueueId,
                                 ncp_uint32_t myTqsBitMask,
                                 ncp_task_isr_wait_object_t **ppWaitStruct,
                                 ncp_st_t                   *pNcpStatus);
ncp_st_t 
ncp_dev_enable_1shot_nca_task_completion_ints(ncp_dev_hdl_t devHdl, 
                                 ncp_uint8_t grp,
                                 ncp_tTask_condition_met_fn_ptr_t conditionMetFn,
                                 ncp_uint32_t grpRelQueueId,
                                 ncp_uint32_t myTqsBitMask,
                                 ncp_task_isr_wait_object_t **ppWaitStruct,
                                 ncp_st_t                   *pNcpStatus);    
                                 
ncp_st_t 
ncp_dev_disable_1shot_nca_rx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp, ncp_task_isr_wait_object_t *pWaitStruct);

ncp_st_t 
ncp_dev_disable_1shot_nca_tx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp, ncp_task_isr_wait_object_t *pWaitStruct);   

ncp_st_t 
ncp_dev_disable_1shot_nca_task_completion_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp, ncp_task_isr_wait_object_t *pWaitStruct);    

                                 
                                 
#define NCP_TASK_ENABLE_1SHOT_RX_INTS(_dev,                                      \
                                   _grp,                                         \
                                   _conditionMetFn,                              \
                                   _grpRelQueueId,                               \
                                   _myTqsBitMask,                                \
                                   _ppWaitStruct,                                 \
                                   _pNcpStatus)                                  \
ncp_dev_enable_1shot_nca_rx_ints(_dev,                                           \
                                   _grp,                                         \
                                   _conditionMetFn,                              \
                                   _grpRelQueueId,                               \
                                   _myTqsBitMask,                                \
                                   _ppWaitStruct,                                 \
                                   _pNcpStatus)                                

#define NCP_TASK_ENABLE_1SHOT_TX_INTS(_dev,                                      \
                                   _grp,                                         \
                                   _conditionMetFn,                              \
                                   _grpRelQueueId,                               \
                                   _myTqsBitMask,                                \
                                   _ppWaitStruct,                                 \
                                   _pNcpStatus)                                  \
ncp_dev_enable_1shot_nca_tx_ints(_dev,                                           \
                                   _grp,                                         \
                                   _conditionMetFn,                              \
                                   _grpRelQueueId,                               \
                                   _myTqsBitMask,                                \
                                   _ppWaitStruct,                                 \
                                   _pNcpStatus)                                  
                                   
#define NCP_TASK_ENABLE_1SHOT_TCOMP_INTS(_dev,                                   \
                                   _grp,                                         \
                                   _conditionMetFn,                              \
                                   _grpRelQueueId,                               \
                                   _myTqsBitMask,                                \
                                   _ppWaitStruct,                                 \
                                   _pNcpStatus)                                  \
ncp_dev_enable_1shot_nca_task_completion_ints(_dev,                              \
                                   _grp,                                         \
                                   _conditionMetFn,                              \
                                   _grpRelQueueId,                               \
                                   _myTqsBitMask,                                \
                                   _ppWaitStruct,                                 \
                                   _pNcpStatus)                                  

#define NCP_TASK_DISABLE_1SHOT_RX_INTS(_dev, _grp, _pWaitObj) \
ncp_dev_disable_1shot_nca_rx_ints(_dev, _grp, _pWaitObj)

#define NCP_TASK_DISABLE_1SHOT_TX_INTS(_dev, _grp, _pWaitObj) \
ncp_dev_disable_1shot_nca_tx_ints(_dev, _grp, _pWaitObj)

#define NCP_TASK_DISABLE_1SHOT_TCOMP_INTS(_dev, _grp, _pWaitObj) \
ncp_dev_disable_1shot_nca_task_completion_ints(_dev, _grp, _pWaitObj)
                                   
/*
 * PRIVATE - Task ISR Wait Control
 */
 
void
ncp_task_isr_wakeup_all(ncp_task_isr_wait_object_t *waitListHead);

void 
ncp_task_isr_free_all_waitObjs(ncp_task_isr_wait_object_t *objListHead);

void
ncp_task_isr_put_waitObj(ncp_task_isr_wait_object_t **pWaitListHead, 
                       ncp_task_isr_wait_object_t *pWaitObj);

void
ncp_task_isr_get_waitObj(ncp_task_isr_wait_object_t **pWaitListHead, 
                       ncp_task_isr_wait_object_t **pWaitObj);
void
ncp_task_isr_remove_waitObj(ncp_task_isr_wait_object_t **pWaitListHead, 
                       ncp_task_isr_wait_object_t *pWaitObj);                       



/*
 * ISR Related Macros
 */
#if !defined(NCP_DEV_FBRS) && !defined(NCP_DEV_SOCKET) && !defined(NCP_DEV_FBDEV) && defined(NCP_KERNEL)
#define NCP_DEV_PWAITSTRUCT_DECL(_pWaitStruct) \
ncp_task_isr_wait_object_t *_pWaitStruct=NULL
#else
#define NCP_DEV_PWAITSTRUCT_DECL(_pWaitStruct)
#endif

/* ==============================================
 * End - For new ISR specific-wakeup support
 */ 
 
typedef struct {
    ncp_uint32_t dataBufferCount;
    ncp_uint32_t hdrCount;
    ncp_uint32_t unitSize;
    ncp_uint32_t statCount;
    ncp_uint32_t maxCmdXferCount;
} ncp_dev_cfg_cmd_var_t;


typedef void (*ncp_dev_cpcq_entry_put_fn_t) (
    struct ncp_dev_cpcq_s *pcq,
    ncp_uint16_t   *idx,
    ncp_uint32_t   *entry);

typedef void (*ncp_dev_cpcq_buffer_write_fn_t) (
        void *to,
        void *from,
        ncp_uint32_t size);

struct ncp_dev_cpcq_s {
    ncp_uint32_t  blockSize;
    ncp_uint32_t  nEntries;
    volatile ncp_uint16_t *producer_ptr;
    volatile ncp_uint16_t *consumer_ptr;
    ncp_uint32_t *baseCpuAddr;
    ncp_uint32_t *buffCpuAddr;
    ncp_uint64_t  buffBusAddr;
    ncp_uint8_t   buffShiftBits;
    ncp_uint8_t   grpId;
    ncp_bool_t    swap_desc;
    ncp_uint8_t   dba_mem_sel;
    ncp_uint16_t  ioCount;
    ncp_uint32_t  swTailIdx;
    ncp_uint32_t   *swState;
    ncp_uint32_t  work_without_interrupt_cnt;
    ncp_uint32_t  interrupt_without_work_cnt;
    ncp_dev_cpcq_entry_put_fn_t entryPutFn;
    ncp_dev_cpcq_buffer_write_fn_t bufferWriteFn;
    ncp_raw_spinlock_t          cfgDma_isrLock;
    ncp_task_isr_wait_object_t  *cfgDmaWaitList; 
    ncp_task_isr_wait_object_t  *free_cfgDmaWaitList;     
#if defined(NCP_LINUX) && defined(NCP_KERNEL)
    /* TODO: timer structure should be SAL-ified! */
    struct timer_list        timer;
    /* TODO: handle non-linux operating systems! */
#else
#if defined(NCP_OSE)
    PROCESS timer;
#else /* Includes NCP_VXWORKS */
    ncp_uint8_t timer[0x20];
#endif /* NCP_OSE */
#endif
};

#define  NCP_DEV_CPCQ_SWSTATE_DMA_COMPLETE           0xcccccccc
#define  NCP_DEV_CPCQ_SWSTATE_DMA_WRITE_PENDING      0x11111111
#define  NCP_DEV_CPCQ_SWSTATE_DMA_READ_PENDING       0xeeeeeeee
#define  NCP_DEV_CPCQ_SWSTATE_FREE                   0xffffffff

#define  NCP_DEV_CPCQ_INTR_INTVL   25

#define NCP_DEV_US_PER_MS   (1000)
#define NCP_DEV_IPCQ_DELAY_MS (10)
#define NCP_DEV_OPCQ_DELAY_MS (10)
#define NCP_DEV_TPCQ_DELAY_MS (10)
#define NCP_DEV_RPCQ_DELAY_MS (10)

#define NCP_DEV_CPCQ_DELAY_US (10)
#define NCP_DEV_CPCQ_MAX_XFER_SIZE          (65536)
#define NCP_DEV_CPCQ_MAX_XFER_COUNT         (NCP_DEV_CPCQ_MAX_XFER_SIZE / 4)
#define NCP_DEV_DMA_THRESHOLD                  (32)

#define NCP_DEV_PIO_DAT_REGS                  (128)
#define NCP_DEV_PIO_MAX_TRANSACTIONS           (64)
#define NCP_DEV_PIO_MAX_BCAST_TRANSACTIONS     (31)
#define NCP_DEV_CFG_NODE_LOCAL_TARGET         (255)

#define NCP_DEV_MAX_SW_FILL_SIZE            (65536)
#define NCP_DEV_MAX_HW_FILL_SIZE           (131072)

#define NCP_DEV_PIO_DELAY_MAX   (400000)

#if defined(NCP_DEV_FBDEV) || defined (NCP_TEMP_USE_APP_HW)
#define NCP_DEV_PIO_DELAY()

#define NCP_DEV_DOMAIN_LOCK()

#define NCP_DEV_DOMAIN_UNLOCK()
#define NCP_DEV_IRQ_DOMAIN_UNLOCK()

#define NCP_TIMER_EVENTS_PRESENT(_myDevHdl)     (1)
#define NCP_TIMER_CPU_TIMER_EXPIRED(_myLastSeq) (1)
#define NCP_SE_FEM_EVENTS_PRESENT(_myDevHdl)    (1)

#define NCP_DEV_NCA_CPCQ_IS_FULL(pcq) FALSE
#define NCP_DEV_NCA_CPCQ_IS_EMPTY(pcq) TRUE
#define NCP_DEV_NCA_CPCQ_IS_FULL_DELAY(dev, pcq, stat)
#define NCP_DEV_NCA_CPCQ_IS_EMPTY_DELAY(dev, pcq, stat)
#define NCP_DEV_NCA_PCQ_IDX_DECREMENT(pcq, idx)

#else
#define NCP_DEV_PIO_DELAY() \
    do { \
        ncp_uint32_t _reg32_; \
        volatile ncp_nca_cfg_pio_cdr0_reg_t * _cdr0_ = (ncp_nca_cfg_pio_cdr0_reg_t *)&_reg32_; \
        int _pioDelay_ = NCP_DEV_PIO_DELAY_MAX; \
        while (_pioDelay_) { \
            _reg32_ = NCP_DEV_BUS_READ32( \
                  dev, NCP_DEV_PAGE_NCA, NCP_NCA_CFG_PIO_CDR0); \
            if (_cdr0_->start_done == 0) { \
                if ((_reg32_ != 0) && (_cdr0_->status != 3)) { \
                    st = ncp_dev_pio_error(dev); \
                    if (st == NCP_ST_SUCCESS) st = NCP_ST_DEV_PIO_FAILED; \
                    goto cleanup; \
                } \
                break; \
            } \
            if (_reg32_ == 0xffffffff) { \
                st = NCP_ST_DEV_IO_ERROR; \
                goto cleanup; \
            } \
            if (--_pioDelay_ == 0) { \
                st = NCP_ST_DEV_PIO_SW_TIMEOUT; \
                goto cleanup; \
            } \
        } \
    } while (0);

#ifdef NCP_VXWORKS
#define NCP_DEV_DOMAIN_LOCK()    \
{                                                               \
    ncp_uint32_t __nloops = 0;                                  \
    ncp_uint32_t *dlAddr;         \
    dlAddr = (ncp_uint32_t *) NCP_DEV_BUS_ADDR(dev, \
                              NCP_DEV_PAGE_NCA, \
                              NCP_NCA_PIO_LOCK(dev->config->domainId)); \
    while ( *dlAddr != 0) \
    {                                                           \
        if (__nloops++ >= dev->config->domainLockRetryCnt) {     \
            st = NCP_ST_DEV_DOMAIN_LOCK_TIMEOUT;                \
            goto cleanup;                                       \
        }                                                       \
    }                                                           \
}

#else
#define NCP_DEV_DOMAIN_LOCK()                                   \
{                                                               \
    ncp_uint32_t __nloops = 0;                                  \
    ncp_uint32_t domLockReg;                                    \
    domLockReg = NCP_DEV_BUS_READ32( dev, NCP_DEV_PAGE_NCA,     \
                NCP_NCA_PIO_LOCK(dev->config->domainId));       \
    while (domLockReg != 0)                                     \
    {                                                           \
        if (__nloops++ >= dev->config->domainLockRetryCnt) {    \
            st = NCP_ST_DEV_DOMAIN_LOCK_TIMEOUT;                \
            goto cleanup;                                       \
        }                                                       \
        domLockReg = NCP_DEV_BUS_READ32( dev, NCP_DEV_PAGE_NCA, \
                NCP_NCA_PIO_LOCK(dev->config->domainId));       \
    }                                                           \
}
#endif

#ifdef NCP_VXWORKS
#define NCP_DEV_IRQ_DOMAIN_UNLOCK()
#define NCP_DEV_DOMAIN_UNLOCK() \
  {                             \
    ncp_uint32_t *domUlAddr;  \
    domUlAddr = (ncp_uint32_t *) NCP_DEV_BUS_ADDR(dev, \
                                 NCP_DEV_PAGE_NCA, \
                                 NCP_NCA_PIO_LOCK(dev->config->domainId)); \
    *domUlAddr = 0; \
  }
#else
#define NCP_DEV_IRQ_DOMAIN_UNLOCK()
#define NCP_DEV_DOMAIN_UNLOCK()                                 \
{                                                               \
    NCP_DEV_BUS_WRITE32( dev, NCP_DEV_PAGE_NCA,                 \
            NCP_NCA_PIO_LOCK(dev->config->domainId), 0);         \
}
#endif

#define NCP_DEV_NCA_CPCQ_BUFFER_CPU_ADDR(pcq, idx) \
    ( (void *) (pcq)->buffCpuAddr + ( (idx) * (pcq)->blockSize)) 


/*
 * Is the PCQ full?
 */        

#define NCP_DEV_NCA_CPCQ_PROD_IDX(pcq) \
     (pcq->swap_desc) ? NCP_ENDIAN_SWAP_16(*(pcq)->producer_ptr) : (*(pcq)->producer_ptr);

#define NCP_DEV_NCA_CPCQ_CONS_IDX(pcq) \
     (pcq->swap_desc) ? NCP_ENDIAN_SWAP_16(*(pcq)->consumer_ptr) : (*(pcq)->consumer_ptr);



#define NCP_DEV_NCA_CPCQ_IS_FULL(pcq)                                        \
    ({                                                                       \
         ncp_uint16_t prod, consumer;                                        \
         prod = NCP_DEV_NCA_CPCQ_PROD_IDX(pcq);                              \
         consumer = NCP_DEV_NCA_CPCQ_CONS_IDX(pcq);                          \
         (((( prod + 1) & (pcq->nEntries - 1)) == consumer) ? TRUE : FALSE); \
     })

/*
 * Is the PCQ empty?
 *
 * For PCQ empty we are just checking if (producer == consumer).
 * If the queue is empty this will be true regardless of whether
 * the values are swapped or not. So we don't bother swapping.
 */

#define NCP_DEV_NCA_CPCQ_IS_EMPTY(pcq)                \
    ({                                                \
         ncp_uint16_t prod, consumer;                 \
         prod = (*(pcq)->producer_ptr);               \
         consumer = (*(pcq)->consumer_ptr);           \
         ((prod == consumer) ? TRUE : FALSE);         \
     }) 


/*
 * advance non-consumer/producer mirror index using num PCQ entries as water mark
 */

#define NCP_DEV_NCA_PCQ_IDX_ADVANCE(pcq, idx) \
    {                                         \
        if ((idx) == (pcq->nEntries - 1))     \
            (idx) = 0;                        \
        else                                  \
            (idx)+=1;                         \
    }

#define NCP_DEV_NCA_PCQ_IDX_DECREMENT(pcq, idx) \
    {                                           \
        if ((idx) == 0)                         \
            (idx) = (pcq->nEntries - 1);        \
        else                                    \
            (idx)-=1;                           \
    }


#define NCP_DEV_NCA_PCQ_IDX_PUT(pcq, idx)                            \
    {                                                                \
        NCP_SYSMEM_BARRIER();                                        \
        if (pcq->swap_desc) {                                        \
            *pcq->producer_ptr = NCP_ENDIAN_SWAP_16(idx);            \
        } else {                                                     \
            *pcq->producer_ptr = idx;                                \
        }                                                            \
    }



#ifdef NCP_DEV_SOCKET
#define NCP_DEV_NCA_CPCQ_IS_FULL_DELAY(dev, pcq, stat)
#define NCP_DEV_NCA_CPCQ_IS_EMPTY_DELAY(dev, pcq, stat)
#else
#define NCP_DEV_NCA_CPCQ_IS_FULL_DELAY(dev, pcq, stat)          \
    {                                                           \
        ncp_uint32_t waitCount = 0;                             \
        while (NCP_DEV_NCA_CPCQ_IS_FULL(pcq))                    \
        {                                                       \
            /* TODO: This should wait on an interrupt event */  \
            ncp_usleep(NCP_DEV_CPCQ_DELAY_US);                  \
            NCP_DEV_BUS_READ32(dev, NCP_DEV_PAGE_SIMULATOR_IF, 0x10); \
            dev->stats.dma_io##stat##_delay_cnt++;                     \
            if (++waitCount == dev->config->cpcqTimeoutMs)       \
            {                                                   \
                NCP_MSG(NCP_MSG_ERROR, "cPCQ timeout\n");       \
                NCP_CALL(NCP_ST_DEV_PCQ_TIMEOUT);               \
            }                                                   \
        }                                                       \
    }

#define NCP_DEV_NCA_CPCQ_IS_EMPTY_DELAY(dev, pcq, stat)         \
    {                                                           \
        ncp_uint32_t waitCount = 0;                             \
                                                                \
        for (waitCount = 0; waitCount < dev->config->cpcqTimeoutMs; \
             waitCount++)                                       \
        {                                                       \
            if (NCP_DEV_NCA_CPCQ_IS_EMPTY(pcq) == TRUE)          \
            {                                                   \
                break;                                          \
            }                                                   \
            ncp_usleep(NCP_DEV_CPCQ_DELAY_US);                  \
            NCP_DEV_BUS_READ32(dev, NCP_DEV_PAGE_SIMULATOR_IF, 0x10); \
            dev->stats.dma_io##stat##_delay_cnt++;              \
        }                                                       \
                                                                \
        if (NCP_DEV_NCA_CPCQ_IS_EMPTY(pcq) == FALSE)             \
        {                                                       \
            NCP_MSG(NCP_MSG_ERROR, "cPCQ timeout\n");           \
            NCP_CALL(NCP_ST_DEV_PCQ_TIMEOUT);                   \
        }                                                       \
    }
#endif


#define NCP_SE_FEM_EVENTS_PRESENT(_myDevHdl) \
    ({ \
    ncp_seng_event_q_wr_ptr_r_t _myFemWrPtr;  \
    ncp_seng_event_q_rd_ptr_r_t _myFemRdPtr; \
    ncp_seng_event_q_size_r_t _myFemQSize; \
    ncp_uint32_t _myQWrPtr = 0; \
    ncp_uint32_t _myQRdPtr = 0; \
    ncp_uint32_t _myQSize = 0; \
    ncp_bool_t _myQWrWrap = FALSE; \
    ncp_bool_t _myQRdWrap = FALSE; \
    ncp_bool_t _myEventsOnQueue; \
    void *_myU32Valp; \
    \
    _myU32Valp = &(_myFemQSize);       \
    NCP_CALL(ncp_dev_read32(_myDevHdl, \
                            NCP_REGION_MPP_SENG, \
                            NCP_SENG_EVENT_Q_SIZE, \
                            (ncp_uint32_t *)(_myU32Valp)));     \
    _myQSize = _myFemQSize.size; \
    _myU32Valp = &(_myFemWrPtr);       \
    NCP_CALL(ncp_dev_read32(_myDevHdl, \
                            NCP_REGION_MPP_SENG, \
                            NCP_SENG_EVENT_Q_WR_PTR, \
                            (ncp_uint32_t *)(_myU32Valp)));     \
    _myQWrPtr = _myFemWrPtr.write_ptr; \
    _myQWrWrap = _myFemWrPtr.write_wrap; \
    \
    _myU32Valp = &_myFemRdPtr; \
    NCP_CALL(ncp_dev_read32(_myDevHdl, \
                            NCP_REGION_MPP_SENG, \
                            NCP_SENG_EVENT_Q_RD_PTR, \
                            (ncp_uint32_t *)(_myU32Valp))); \
    _myQRdPtr = _myFemRdPtr.read_ptr; \
    _myQRdWrap = _myFemRdPtr.read_wrap; \
    if ( _myQWrWrap == _myQRdWrap)      \
    { \
        NCP_ASSERT( ( _myQWrPtr >= _myQRdPtr), NCP_ST_SE_INVALID_FEM_POINTER); \
        _myEventsOnQueue =  ( (_myQWrPtr - _myQRdPtr) != 0); \
    } else \
    { \
        NCP_ASSERT( ( _myQWrPtr <= _myQRdPtr), NCP_ST_SE_INVALID_FEM_POINTER); \
        _myEventsOnQueue = ( (_myQSize + _myQWrPtr - _myQRdPtr) != 0); \
    } \
    _myEventsOnQueue; \
    })

#define NCP_TIMER_EVENTS_PRESENT(_myDevHdl) \
    ({ \
    void *_myU32Valp; \
    ncp_uint32_t _myIruptStatus7 = 0; \
    ncp_bool_t _myEventPresent = FALSE; \
    \
    _myU32Valp = &(_myIruptStatus7);       \
    NCP_CALL(ncp_dev_read32(_myDevHdl, \
                            NCP_REGION_TIMER_TIMER_CORE, \
                            NCP_TIMER_CORE_INTERRUPT_STATUS7, \
                            (ncp_uint32_t *)(_myU32Valp)));     \
    if ( _myIruptStatus7 & NCP_TIMER_EVENT_INTR_MASK) \
    { \
        _myEventPresent = TRUE; \
    } else \
    { \
        _myEventPresent = FALSE; \
    } \
    _myEventPresent; \
    })

#define NCP_TIMER_CPU_TIMER_EXPIRED(_myLastSeq)        \
    ({ \
    (_myLastSeq < dev->cpuIsrSeq[timerIndex]);  \
    })

#endif


/* Internal I/O transaction type */
#if 0
typedef struct ncp_dev_trans_s {
    ncp_dev_trans_type_t type;
    ncp_region_io_t *region;
    union {
        ncp_dev_trans_udelay_t udelay;
        ncp_dev_trans_block_fill32_t bf32;
        ncp_dev_trans_block_write32_t bw32;
    } u;
    struct ncp_dev_trans_s *next;
} ncp_dev_trans_t;
#endif


/*
 * common ncaV2 interrupt types
 */
typedef enum {
NCA_GRP_INTR_ITASK_ARRIVAL=1,  
NCA_GRP_INTR_OPCQ_COMPLETE,  
NCA_GRP_INTR_CPCQ_COMPLETE,     
NCA_GRP_INTR_TPCQ_COMPLETE  /* ncaV2 does not use tPCQs */
} ncp_dev_nca_intr_types_t;


/* NCA V1 Interrupt bit definitions */
/* ===================================================== */
/*
 * Setup some convenient masks
 */
 
/*
 * Setup some convenient masks
 */
 
#define      NCA_OVERALL_INT_GRP5                      (1<<30) 
#define      NCA_OVERALL_INT_GRP4                      (1<<29) 
#define      NCA_OVERALL_INT_GRP3                      (1<<28) 
#define      NCA_OVERALL_INT_GRP2                      (1<<27) 
#define      NCA_OVERALL_INT_GRP1                      (1<<26) 
#define      NCA_OVERALL_INT_GRP0                      (1<<25)   
 
#define      NCA_NON_GRP_INT               (1<<31)
#define      NCA_GRP5_CNAL_CFGRNG_INT      (1<<30) 
#define      NCA_GRP4_CNAL_CFGRNG_INT      (1<<29) 
#define      NCA_GRP3_CNAL_CFGRNG_INT      (1<<28) 
#define      NCA_GRP2_CNAL_CFGRNG_INT      (1<<27) 
#define      NCA_GRP1_CNAL_CFGRNG_INT      (1<<26)  
#define      NCA_GRP0_CNAL_CFGRNG_INT      (1<<25)  
#define      NCA_CFG_INST_COMPL_INT        (1<<24)                   
#define      NCA_ITASK_ARRIVAL_INT_GRP5    (1<<23)                  
#define      NCA_ITASK_ARRIVAL_INT_GRP4    (1<<22)                   
#define      NCA_ITASK_ARRIVAL_INT_GRP3    (1<<21)                   
#define      NCA_ITASK_ARRIVAL_INT_GRP2    (1<<20)                   
#define      NCA_ITASK_ARRIVAL_INT_GRP1    (1<<19)                   
#define      NCA_ITASK_ARRIVAL_INT_GRP0    (1<<18)                   
#define      NCA_OPCQ_COMPLETE_INT_GRP5    (1<<17)                   
#define      NCA_OPCQ_COMPLETE_INT_GRP4    (1<<16)                   
#define      NCA_OPCQ_COMPLETE_INT_GRP3    (1<<15)                   
#define      NCA_OPCQ_COMPLETE_INT_GRP2    (1<<14)                   
#define      NCA_OPCQ_COMPLETE_INT_GRP1    (1<<13)                   
#define      NCA_OPCQ_COMPLETE_INT_GRP0    (1<<12)                   
#define      NCA_TPCQ_COMPLETE_INT_GRP5    (1<<11)                   
#define      NCA_TPCQ_COMPLETE_INT_GRP4    (1<<10)                   
#define      NCA_TPCQ_COMPLETE_INT_GRP3    (1<<9)                    
#define      NCA_TPCQ_COMPLETE_INT_GRP2    (1<<8)                    
#define      NCA_TPCQ_COMPLETE_INT_GRP1    (1<<7)                    
#define      NCA_TPCQ_COMPLETE_INT_GRP0    (1<<6)                    
#define      NCA_CPCQ_COMPLETE_INT_GRP5    (1<<5)                    
#define      NCA_CPCQ_COMPLETE_INT_GRP4    (1<<4)                    
#define      NCA_CPCQ_COMPLETE_INT_GRP3    (1<<3)                    
#define      NCA_CPCQ_COMPLETE_INT_GRP2    (1<<2)                    
#define      NCA_CPCQ_COMPLETE_INT_GRP1    (1<<1)                    
#define      NCA_CPCQ_COMPLETE_INT_GRP0    (1<<0)               
 

 
#define      NCA_GRP0_INT_MASK  \
   (NCA_ITASK_ARRIVAL_INT_GRP0 + \
    NCA_OPCQ_COMPLETE_INT_GRP0 + \
    NCA_TPCQ_COMPLETE_INT_GRP0 + \
    NCA_CPCQ_COMPLETE_INT_GRP0)

#define      NCA_GRP1_INT_MASK  \
   (NCA_ITASK_ARRIVAL_INT_GRP1 + \
    NCA_OPCQ_COMPLETE_INT_GRP1 + \
    NCA_TPCQ_COMPLETE_INT_GRP1 + \
    NCA_CPCQ_COMPLETE_INT_GRP1)

#define      NCA_GRP2_INT_MASK \
   (NCA_ITASK_ARRIVAL_INT_GRP2 + \
    NCA_OPCQ_COMPLETE_INT_GRP2 + \
    NCA_TPCQ_COMPLETE_INT_GRP2 + \
    NCA_CPCQ_COMPLETE_INT_GRP2)

#define      NCA_GRP3_INT_MASK \
   (NCA_ITASK_ARRIVAL_INT_GRP3 + \
    NCA_OPCQ_COMPLETE_INT_GRP3 + \
    NCA_TPCQ_COMPLETE_INT_GRP3 + \
    NCA_CPCQ_COMPLETE_INT_GRP3)

#define      NCA_GRP4_INT_MASK  \
   (NCA_ITASK_ARRIVAL_INT_GRP4 + \
    NCA_OPCQ_COMPLETE_INT_GRP4 + \
    NCA_TPCQ_COMPLETE_INT_GRP4 + \
    NCA_CPCQ_COMPLETE_INT_GRP4)

#define      NCA_GRP5_INT_MASK \
   (NCA_ITASK_ARRIVAL_INT_GRP5 + \
    NCA_OPCQ_COMPLETE_INT_GRP5 + \
    NCA_TPCQ_COMPLETE_INT_GRP5 + \
    NCA_CPCQ_COMPLETE_INT_GRP5)  

#define NCP_SE_FEM_EVENT_INTR_MASK            0x1

#define NCP_TIMER_EVENT_INTR_MASK             0x200


/* #define NCP_CONFIG_DMA_POLL_FOR_COMPLETION */
/* NCA V2 Interrupt bit definitions */
/* ===================================================== */
/*
 * Setup some convenient masks
 */
 
/*
 * Setup some convenient masks
 */
 
#define      NCA_V2_ITASK_ARRIVAL_INT_GRP15    (1<<31) 
#define      NCA_V2_ITASK_ARRIVAL_INT_GRP14    (1<<30) 
#define      NCA_V2_ITASK_ARRIVAL_INT_GRP13    (1<<29) 
#define      NCA_V2_ITASK_ARRIVAL_INT_GRP12    (1<<28) 
#define      NCA_V2_ITASK_ARRIVAL_INT_GRP11    (1<<27) 
#define      NCA_V2_ITASK_ARRIVAL_INT_GRP10    (1<<26) 
#define      NCA_V2_ITASK_ARRIVAL_INT_GRP9    (1<<25) 
#define      NCA_V2_ITASK_ARRIVAL_INT_GRP8    (1<<24) 
#define      NCA_V2_ITASK_ARRIVAL_INT_GRP7    (1<<23) 
#define      NCA_V2_ITASK_ARRIVAL_INT_GRP6    (1<<22) 
#define      NCA_V2_ITASK_ARRIVAL_INT_GRP5    (1<<21) 
#define      NCA_V2_ITASK_ARRIVAL_INT_GRP4    (1<<20)                
#define      NCA_V2_ITASK_ARRIVAL_INT_GRP3    (1<<19)                   
#define      NCA_V2_ITASK_ARRIVAL_INT_GRP2    (1<<18)                   
#define      NCA_V2_ITASK_ARRIVAL_INT_GRP1    (1<<17)                   
#define      NCA_V2_ITASK_ARRIVAL_INT_GRP0    (1<<16) 

#define      NCA_V2_OPCQ_COMPLETE_INT_GRP15   (1<<15)                   
#define      NCA_V2_OPCQ_COMPLETE_INT_GRP14   (1<<14)                   
#define      NCA_V2_OPCQ_COMPLETE_INT_GRP13   (1<<13)                   
#define      NCA_V2_OPCQ_COMPLETE_INT_GRP12   (1<<12)                   
#define      NCA_V2_OPCQ_COMPLETE_INT_GRP11   (1<<11)                   
#define      NCA_V2_OPCQ_COMPLETE_INT_GRP10   (1<<10)  
#define      NCA_V2_OPCQ_COMPLETE_INT_GRP9    (1<<9)                   
#define      NCA_V2_OPCQ_COMPLETE_INT_GRP8    (1<<8)                   
#define      NCA_V2_OPCQ_COMPLETE_INT_GRP7    (1<<7)                   
#define      NCA_V2_OPCQ_COMPLETE_INT_GRP6    (1<<6)                   
#define      NCA_V2_OPCQ_COMPLETE_INT_GRP5    (1<<5)                   
#define      NCA_V2_OPCQ_COMPLETE_INT_GRP4    (1<<4)                    
#define      NCA_V2_OPCQ_COMPLETE_INT_GRP3    (1<<3)                   
#define      NCA_V2_OPCQ_COMPLETE_INT_GRP2    (1<<2)                   
#define      NCA_V2_OPCQ_COMPLETE_INT_GRP1    (1<<1)                   
#define      NCA_V2_OPCQ_COMPLETE_INT_GRP0    (1<<0)                   


#define      NCA_V2_CPCQ_COMPLETE_INT_GRP15   (1<<15)                   
#define      NCA_V2_CPCQ_COMPLETE_INT_GRP14   (1<<14)                   
#define      NCA_V2_CPCQ_COMPLETE_INT_GRP13   (1<<13)                   
#define      NCA_V2_CPCQ_COMPLETE_INT_GRP12   (1<<12)                   
#define      NCA_V2_CPCQ_COMPLETE_INT_GRP11   (1<<11)                   
#define      NCA_V2_CPCQ_COMPLETE_INT_GRP10   (1<<10)  
#define      NCA_V2_CPCQ_COMPLETE_INT_GRP9    (1<<9)                   
#define      NCA_V2_CPCQ_COMPLETE_INT_GRP8    (1<<8)                   
#define      NCA_V2_CPCQ_COMPLETE_INT_GRP7    (1<<7)                   
#define      NCA_V2_CPCQ_COMPLETE_INT_GRP6    (1<<6)                   
#define      NCA_V2_CPCQ_COMPLETE_INT_GRP5    (1<<5)                   
#define      NCA_V2_CPCQ_COMPLETE_INT_GRP4    (1<<4)                    
#define      NCA_V2_CPCQ_COMPLETE_INT_GRP3    (1<<3)                   
#define      NCA_V2_CPCQ_COMPLETE_INT_GRP2    (1<<2)                   
#define      NCA_V2_CPCQ_COMPLETE_INT_GRP1    (1<<1)                   
#define      NCA_V2_CPCQ_COMPLETE_INT_GRP0    (1<<0)   
                
/*
 * We define the group interrupt types to be the 
 * grp0 bit value.
 */
#define      NCA_V2_GRP_INTR_CPCQ_COMPLETE     NCA_V2_CPCQ_COMPLETE_INT_GRP0
#define      NCA_V2_GRP_INTR_OPCQ_COMPLETE     NCA_V2_OPCQ_COMPLETE_INT_GRP0
#define      NCA_V2_GRP_INTR_ITASK_ARRIVAL     NCA_V2_ITASK_ARRIVAL_INT_GRP0
 
 
#define      NCA_V2_GRP0_R0_INT_MASK  \
   (NCA_V2_ITASK_ARRIVAL_INT_GRP0 + \
    NCA_V2_OPCQ_COMPLETE_INT_GRP0)

#define      NCA_V2_GRP1_R0_INT_MASK  \
   (NCA_V2_ITASK_ARRIVAL_INT_GRP1 + \
    NCA_V2_OPCQ_COMPLETE_INT_GRP1)

#define      NCA_V2_GRP2_R0_INT_MASK \
   (NCA_V2_ITASK_ARRIVAL_INT_GRP2 + \
    NCA_V2_OPCQ_COMPLETE_INT_GRP2)

#define      NCA_V2_GRP3_R0_INT_MASK \
   (NCA_V2_ITASK_ARRIVAL_INT_GRP3 + \
    NCA_V2_OPCQ_COMPLETE_INT_GRP3)

#define      NCA_V2_GRP4_R0_INT_MASK  \
   (NCA_V2_ITASK_ARRIVAL_INT_GRP4 + \
    NCA_V2_OPCQ_COMPLETE_INT_GRP4)

#define      NCA_V2_GRP5_R0_INT_MASK \
   (NCA_V2_ITASK_ARRIVAL_INT_GRP5 + \
    NCA_V2_OPCQ_COMPLETE_INT_GRP5)
    
#define      NCA_V2_GRP6_R0_INT_MASK  \
   (NCA_V2_ITASK_ARRIVAL_INT_GRP6 + \
    NCA_V2_OPCQ_COMPLETE_INT_GRP6)

#define      NCA_V2_GRP7_R0_INT_MASK  \
   (NCA_V2_ITASK_ARRIVAL_INT_GRP7 + \
    NCA_V2_OPCQ_COMPLETE_INT_GRP7)

#define      NCA_V2_GRP8_R0_INT_MASK \
   (NCA_V2_ITASK_ARRIVAL_INT_GRP8 + \
    NCA_V2_OPCQ_COMPLETE_INT_GRP8)

#define      NCA_V2_GRP9_R0_INT_MASK \
   (NCA_V2_ITASK_ARRIVAL_INT_GRP9 + \
    NCA_V2_OPCQ_COMPLETE_INT_GRP9)

#define      NCA_V2_GRP10_R0_INT_MASK  \
   (NCA_V2_ITASK_ARRIVAL_INT_GRP10 + \
    NCA_V2_OPCQ_COMPLETE_INT_GRP10)

#define      NCA_V2_GRP11_R0_INT_MASK \
   (NCA_V2_ITASK_ARRIVAL_INT_GRP11 + \
    NCA_V2_OPCQ_COMPLETE_INT_GRP11)

#define      NCA_V2_GRP12_R0_INT_MASK  \
   (NCA_V2_ITASK_ARRIVAL_INT_GRP12 + \
    NCA_V2_OPCQ_COMPLETE_INT_GRP12)

#define      NCA_V2_GRP13_R0_INT_MASK  \
   (NCA_V2_ITASK_ARRIVAL_INT_GRP13 + \
    NCA_V2_OPCQ_COMPLETE_INT_GRP13)

#define      NCA_V2_GRP14_R0_INT_MASK \
   (NCA_V2_ITASK_ARRIVAL_INT_GRP14 + \
    NCA_V2_OPCQ_COMPLETE_INT_GRP14)

#define      NCA_V2_GRP15_R0_INT_MASK \
   (NCA_V2_ITASK_ARRIVAL_INT_GRP15 + \
    NCA_V2_OPCQ_COMPLETE_INT_GRP15)



#define      NCA_V2_GRP0_R1_INT_MASK \
    NCA_V2_CPCQ_COMPLETE_INT_GRP0

#define      NCA_V2_GRP1_R1_INT_MASK \
    NCA_V2_CPCQ_COMPLETE_INT_GRP1

#define      NCA_V2_GRP2_R1_INT_MASK \
    NCA_V2_CPCQ_COMPLETE_INT_GRP2

#define      NCA_V2_GRP3_R1_INT_MASK \
    NCA_V2_CPCQ_COMPLETE_INT_GRP3

#define      NCA_V2_GRP4_R1_INT_MASK \
    NCA_V2_CPCQ_COMPLETE_INT_GRP4

#define      NCA_V2_GRP5_R1_INT_MASK \
    NCA_V2_CPCQ_COMPLETE_INT_GRP5  
    
#define      NCA_V2_GRP6_R1_INT_MASK \
    NCA_V2_CPCQ_COMPLETE_INT_GRP6

#define      NCA_V2_GRP7_R1_INT_MASK \
    NCA_V2_CPCQ_COMPLETE_INT_GRP7

#define      NCA_V2_GRP8_R1_INT_MASK \
    NCA_V2_CPCQ_COMPLETE_INT_GRP8

#define      NCA_V2_GRP9_R1_INT_MASK \
    NCA_V2_CPCQ_COMPLETE_INT_GRP9

#define      NCA_V2_GRP10_R1_INT_MASK \
    NCA_V2_CPCQ_COMPLETE_INT_GRP10

#define      NCA_V2_GRP11_R1_INT_MASK \
    NCA_V2_CPCQ_COMPLETE_INT_GRP11  

#define      NCA_V2_GRP12_R1_INT_MASK \
    NCA_V2_CPCQ_COMPLETE_INT_GRP12

#define      NCA_V2_GRP13_R1_INT_MASK \
    NCA_V2_CPCQ_COMPLETE_INT_GRP13

#define      NCA_V2_GRP14_R1_INT_MASK \
    NCA_V2_CPCQ_COMPLETE_INT_GRP14

#define      NCA_V2_GRP15_R1_INT_MASK \
    NCA_V2_CPCQ_COMPLETE_INT_GRP15


/* END NCAV2 Interrupt bit definitions */
/* ============================================================== */

typedef void (*ncp_dev_isr_t)(void *isrArg);

typedef ncp_st_t (*ncp_dev_isr_register_t) (
        struct ncp_dev_s *dev, 
        ncp_uint32_t irq,
        ncp_dev_isr_t isr);

typedef ncp_st_t (*ncp_dev_isr_fn_t) (
        ncp_dev_t *dev, 
        ncp_uint32_t irq);


#define NCP_NCA_INTR_SRC_COOKIE 0xABCD7777
typedef struct ncp_dev_intr_src_s
{
    ncp_uint32_t         cookie;
    ncp_uint32_t         irq;    /* hardware vector */    
    ncp_uint32_t         vIrq;   /* virtual irq     */
    ncp_dev_isr_t        isrFn;
    ncp_uint32_t         devNum;
    struct ncp_dev_s     *dev;
    void                 *handle;
    ncp_bool_t           registered;
} ncp_dev_intr_src_t;


/* --- NCP Device Interrupt Structure ---       */
/* --- Contains isr status snapshot for use by bottom half */

typedef struct ncp_dev_nca_isr_common_s {
    ncp_uint32_t devNum;
    ncp_uint32_t thisGroup;
    void         *pIsrInfoOSspecific; /* reverse pointer to base edev struct */
    /* linked list of waiters,  all to be awakened when interrupt occurs */
#if (1) || defined(NCP_KERNEL)
    ncp_bool_t                       wait_heads_initialized;

    ncp_raw_spinlock_t               iTaskArrival_isrLock;
    ncp_task_isr_wait_object_t       *iTaskArrivalWaitList;

    ncp_raw_spinlock_t               oTaskComplete_isrLock;
    ncp_task_isr_wait_object_t       *oTaskCompleteWaitList;

    ncp_raw_spinlock_t               tTaskComplete_isrLock;
    ncp_task_isr_wait_object_t       *tTaskCompleteWaitList; 
  
    /* available wait objects - dynamically managed */
    ncp_task_isr_wait_object_t       *free_oTaskCompleteWaitList;   
    ncp_task_isr_wait_object_t       *free_iTaskArrivalWaitList;       
    ncp_task_isr_wait_object_t       *free_tTaskCompleteWaitList; 
#endif         
    /*
     * Runtime control, stats, and flags
     */
    ncp_bool_t   stop;
   
    
    /*
     * ISR Control and state
     */ 
    ncp_uint32_t         thisGrpIntAllMask_r0;
    ncp_uint32_t         thisGrpIntAllMask_r1;
    ncp_uint32_t         thisGrpRxIntBit;
    ncp_uint32_t         thisGrpTxIntBit;
    ncp_uint32_t         thisGrpTPCQIntBit;
    ncp_uint32_t         thisGrpCPCQIntBit;

#ifdef NCP_KERNEL
    ncp_uint32_t          asyncRxIntEnabCnt;
    ncp_uint32_t          rxIntEnabCnt;
    
    ncp_uint32_t          txIntEnabCnt;

    ncp_uint32_t          tcompIntEnabCnt;
    ncp_bool_t            WFI_waitInprogress;
#endif
    
    ncp_int32_t          cfgDmaIntEnabCnt;
    
    /*
     * Statistics
     */
     
    ncp_uint32_t         iTaskInts;
    ncp_uint32_t         oTaskInts;
    ncp_uint32_t         tCompInts;        
    ncp_uint32_t         cfgDmaInts;        
    ncp_uint32_t         interrupts;
#ifdef NCP_KERNEL
    ncp_uint32_t         asyncRxWakeups;
#endif
    
} ncp_dev_nca_isr_common_t;




/*
 * Region mapped i/o methods
 */

/* read/write fn prototypes for region map function pointers */

typedef ncp_st_t (*_ncp_dev_read_fn_t) (
                   ncp_dev_t           *dev,
                   ncp_region_io_t     *region,
                   ncp_uint64_t         offset,
                   ncp_uint32_t        *buffer,
                   ncp_uint32_t         count,
                   ncp_uint32_t         flags,
                   ncp_uint32_t         cmdType,
                   ncp_uint32_t         xferWidth);

typedef ncp_st_t (*_ncp_dev_write_fn_t) (
                   ncp_dev_t           *dev,
                   ncp_region_io_t     *region,
                   ncp_uint64_t         offset,
                   ncp_uint32_t        *buffer,
                   ncp_uint32_t         count,
                   ncp_uint32_t         flags,
                   ncp_uint32_t         cmdType,
                   ncp_uint32_t         xferWidth);

/*
 * Structure definition(s) for the region map.
 * See above for typedef ncp_region_io_t.
 */
struct ncp_region_io_s
{
    ncp_region_id_t       regionId;
    ncp_access_map_t     *accessMap;
    _ncp_dev_read_fn_t    readFn;
    _ncp_dev_write_fn_t   writeFn;
    ncp_uint32_t          pageId;
};

struct ncp_region_coh_io_s
{
    ncp_region_id_t       regionId;
    ncp_access_map_t     *accessMap;
    _ncp_dev_read_fn_t    readFn;
    _ncp_dev_write_fn_t   writeFn;
    ncp_uint32_t          controlOffset;
    ncp_uint32_t          dataOffset;
};

typedef struct {
    ncp_region_id_t       regionId;
    ncp_uint32_t          offset;
} ncp_node_per_tgt_offset_t;

/*
 * Region lookup function
 */
ncp_st_t
ncp_dev_region_lookup (
        ncp_dev_t           *dev,
        ncp_region_id_t   regionId,
        ncp_region_io_t  *region);

extern ncp_st_t ncp_dev_config(ncp_dev_t *dev);

extern void ncp_dev_sched_async_rx_callback(ncp_dev_nca_isr_common_t *pIsrCommon);

extern void ncp_dev_intr_mpic(void *intrSrc);

extern ncp_st_t ncp_dev_intr_free_nca(ncp_dev_t *dev);

extern ncp_st_t ncp_dev_intr_config_ncaV2(ncp_dev_t *dev); 
extern ncp_st_t ncp_dev_intr_config_ncaV1(ncp_dev_t *dev); 

extern ncp_st_t ncp_dev_lbi_init(ncp_dev_t *dev);

extern void ncp_dev_intr_alarm_ncaV2(void *intrSrc);
extern void ncp_dev_intr_alarm_ncaV1(void *intrSrc);

extern void ncp_dev_timer_intr(void *intrSrc);

#define NCP_DEV_BUS_ADDR(dev, pageId, offset) \
        ((dev)->pages[pageId].addr + offset)

#define NCP_DEV_PAGE_FLAGS(dev, pageId) (dev->pages[pageId].flags)

/*
 * wakeup types
 */ 
 
enum {
    NCP_NCA_RX_INTR_WAITERS = 0,
    NCP_NCA_RX_INTR_ASYNC_WAITERS, /* <- will sched rx callback */
    NCP_NCA_TX_INTR_WAITERS,
    NCP_NCA_TCOMP_INTR_WAITERS,
    NCP_NCA_CPCQ_INTR_WAITERS
};
     
#define NCP_DEV_INIT_ISR_INFO(_devNUM, _grp, _intrData) \
    NCP_INIT_ISR_INFO(_devNUM, _grp, (_intrData))   

#define NCP_DEV_CLEANUP_ISR_INFO(_devNum) \
    NCP_CLEANUP_ISR_INFO(_devNum)

/*
 * Basic i/o methods
 * Note that FBRS has it's own implementation of these defined
 * in ncp_dev_fbrs.h
 */

#if !defined (NCP_DEV_FBRS) && !defined (NCP_DEV_SOCKET)

#if 0
/* GKM TEMP DEBUG */
#define DEBUG_EDEV_IO
#undef NCP_BUS_WRITE32
#undef NCP_BUS_READ32
#define NCP_BUS_WRITE32(a,v,f)
#define NCP_BUS_READ32(a,f) (0)
#endif


#ifdef DEBUG_EDEV_IO
#define NCP_WRITE_LOG(ctx, dev, pageId, offset, value) \
        NCP_MSG(NCP_MSG_DEBUG_IO, \
            "%s: pageId=0x%x offset=0x%x addr=0x%x value=0x%02x\n", \
            ctx, pageId, offset, NCP_DEV_BUS_ADDR(dev, pageId, offset), value)
#else
#define NCP_WRITE_LOG(ctx, dev, pageId, offset, value)
#endif

#define NCP_DEV_BUS_READ8(dev, pageId, offset) \
        NCP_BUS_READ8(NCP_DEV_BUS_ADDR(dev, pageId, offset))

#define NCP_DEV_BUS_READ16(dev, pageId, offset) \
        NCP_BUS_READ16(NCP_DEV_BUS_ADDR(dev, pageId, offset),\
                NCP_DEV_PAGE_FLAGS(dev, pageId))

#define NCP_DEV_BUS_READ32_UNLOCKED(dev, pageId, offset) \
    ( { \
        unsigned long __val32; \
        __val32 = NCP_BUS_READ32(NCP_DEV_BUS_ADDR(dev, pageId, offset),\
                NCP_DEV_PAGE_FLAGS(dev, pageId)); \
      __val32; \
      } )

#ifdef NCP_KERNEL
#define NCP_DEV_BUS_READ32(dev, pageId, offset) \
    ( { \
        unsigned long __val32; \
        NCP_BSP_SPINLOCK_FLAGS(_flags); \
        if ((FALSE == nca_axi_lock_required) ||                          \
            (pageId != NCP_DEV_PAGE_NCA))                                \
        {                                                                \
            __val32 = NCP_BUS_READ32(NCP_DEV_BUS_ADDR(dev, pageId, offset), \
                    NCP_DEV_PAGE_FLAGS(dev, pageId));                       \
        }                                                                   \
        else                                                                \
        {                                                                   \
            NCP_BSP_SPINLOCK_INTERRUPT_DISABLE(&(NCP_NCA_ACCESS_LOCK),      \
                                               _flags);                     \
            __val32 = NCP_BUS_READ32(NCP_DEV_BUS_ADDR(dev, pageId, offset), \
                    NCP_DEV_PAGE_FLAGS(dev, pageId));                       \
            NCP_BSP_SPINLOCK_INTERRUPT_ENABLE(&(NCP_NCA_ACCESS_LOCK),          \
                                               _flags);                     \
        }                                                                   \
      __val32;                                                              \
      } )
#else
#define NCP_DEV_BUS_READ32(dev, pageId, offset) \
    NCP_DEV_BUS_READ32_UNLOCKED((dev), (pageId), (offset))
#endif

#define NCP_DEV_BUS_WRITE8(dev, pageId, offset, value) \
    do { \
        NCP_WRITE_LOG("edev_bus_write8", dev, pageId, offset, value); \
        NCP_BUS_WRITE8( \
                NCP_DEV_BUS_ADDR(dev, pageId, offset), value); \
        if (NCP_DEV_PAGE_FLAGS(dev, pageId) & NCP_DEV_ACCESS_IO_SYNC) { \
            /* volatile ncp_uint32_t ___val___; \
            ___val___ = */ NCP_BUS_READ32( NCP_DEV_BUS_ADDR(dev, NCP_DEV_PAGE_PCIE0_PEI, NCP_PEI_CONFIG), \
                    NCP_DEV_ACCESS_LITTLE_ENDIAN); \
        } \
    } while (0);

#define NCP_DEV_BUS_WRITE16(dev, pageId, offset, value) \
    do { \
        NCP_WRITE_LOG("edev_bus_write16", dev, pageId, offset, value); \
        NCP_BUS_WRITE16( \
                NCP_DEV_BUS_ADDR(dev, pageId, offset), value); \
        if (NCP_DEV_PAGE_FLAGS(dev, pageId) & NCP_DEV_ACCESS_IO_SYNC) { \
            /* volatile ncp_uint32_t ___val___; \
            ___val___ = */ NCP_BUS_READ32( NCP_DEV_BUS_ADDR(dev, NCP_DEV_PAGE_PCIE0_PEI, NCP_PEI_CONFIG), \
                    NCP_DEV_ACCESS_LITTLE_ENDIAN); \
        } \
    } while (0);


#define NCP_DEV_BUS_WRITE32_UNLOCKED(dev, pageId, offset, value) \
    do { \
        NCP_WRITE_LOG("edev_bus_write32", dev, pageId, offset, value); \
        NCP_BUS_WRITE32(                       \
            NCP_DEV_BUS_ADDR(dev, pageId, offset),  \
            value,                                  \
            NCP_DEV_PAGE_FLAGS(dev, pageId));       \
        if (NCP_DEV_PAGE_FLAGS(dev, pageId) & NCP_DEV_ACCESS_IO_SYNC) { \
            /* volatile ncp_uint32_t ___val___; \
            ___val___ = */ NCP_BUS_READ32( NCP_DEV_BUS_ADDR(dev, NCP_DEV_PAGE_PCIE0_PEI, NCP_PEI_CONFIG), \
                    NCP_DEV_ACCESS_LITTLE_ENDIAN); \
        } \
    } while (0);

#ifdef NCP_KERNEL
#define NCP_DEV_BUS_WRITE32(dev, pageId, offset, value) \
    do { \
        NCP_BSP_SPINLOCK_FLAGS(_flags); \
        NCP_WRITE_LOG("edev_bus_write32", dev, pageId, offset, value); \
        if ((FALSE == nca_axi_lock_required) ||                        \
            (pageId != NCP_DEV_PAGE_NCA))                              \
        {                                               \
            NCP_BUS_WRITE32(                            \
                NCP_DEV_BUS_ADDR(dev, pageId, offset),  \
                value,                                  \
                NCP_DEV_PAGE_FLAGS(dev, pageId));       \
        }                                               \
        else                                            \
        {                                               \
            NCP_BSP_SPINLOCK_INTERRUPT_DISABLE(&(NCP_NCA_ACCESS_LOCK), _flags); \
            NCP_BUS_WRITE32(                       \
                NCP_DEV_BUS_ADDR(dev, pageId, offset),  \
                value,                                  \
                NCP_DEV_PAGE_FLAGS(dev, pageId));       \
            NCP_BSP_SPINLOCK_INTERRUPT_ENABLE(&(NCP_NCA_ACCESS_LOCK), _flags); \
        }                                                                   \
        if (NCP_DEV_PAGE_FLAGS(dev, pageId) & NCP_DEV_ACCESS_IO_SYNC)       \
        {                                                                   \
            NCP_BUS_READ32( NCP_DEV_BUS_ADDR(dev, NCP_DEV_PAGE_PCIE0_PEI,   \
                NCP_PEI_CONFIG),                                            \
                NCP_DEV_ACCESS_LITTLE_ENDIAN);                              \
        }                                                                   \
    } while (0);
#else
#define NCP_DEV_BUS_WRITE32(dev, pageId, offset, value) \
    NCP_DEV_BUS_WRITE32_UNLOCKED((dev), (pageId), (offset), (value))
#endif

#endif /* NCP_DEV_FBRS */

/* macros for the hostmem access methods */
#define NCP_DEV_HOSTMEM_PAGE_SHIFT 18
#define NCP_DEV_HOSTMEM_PAGE_SIZE ( (ncp_uint64_t) 1 << NCP_DEV_HOSTMEM_PAGE_SHIFT) 
#define NCP_DEV_HOSTMEM_PAGE_MASK (NCP_DEV_HOSTMEM_PAGE_SIZE - 1)
#define NCP_DEV_HOSTMEM_PAGE_BASE(x) \
        ( (ncp_uint32_t) ( ((x) & (~NCP_DEV_HOSTMEM_PAGE_MASK)) >> NCP_DEV_HOSTMEM_PAGE_SHIFT) )

/* 
 * Some bus adapter includes reference task IO data structures
 */

#include "ncp_task_pvt.h" 

/* 
 * Include the bus-adaptor specific headers 
 *
 *   first include any default empty macros that are defined only
 *   for one (or a few) bus adaptors. 
 */

#define NCP_DEV_PCI_MPAGE_SETUP(dev) 


#if defined (NCP_DEV_FBRS)
#include "ncp_dev_fbrs.h"
#elif defined (NCP_DEV_FBDEV)
#include "ncp_dev_fbdev.h"
#elif defined (NCP_DEV_SOCKET)
#include "ncp_dev_socket.h"
#else
#if defined (NCP_LINUX)
#include "ncp_dev_linux.h"
#endif
#if defined (NCP_OSE)
#include "ncp_dev_ose.h"
#endif
#ifdef NCP_DEV_PCI
#include "ncp_bus_pci.h"
#endif
#ifdef NCP_DEV_PLX
#include "ncp_bus_plx.h"
#endif
#ifdef NCP_DEV_SRIO
#include "ncp_bus_srio.h"
#endif
#if defined(NCP_DEV_SRIOEP)
#include "ncp_bus_srioep.h"
#endif
#ifdef NCP_DEV_PLB
#include "ncp_bus_plb.h"
#endif
#ifdef NCP_DEV_ACE
#include "ncp_bus_ace.h"
#endif
#endif

#ifndef NCP_BAR_REGS
        /* Guesstimate used in kernel-independent code */
#ifndef EXTERNAL_HOST
        #define NCP_BAR_REGS              3
#else
        #define NCP_BAR_REGS              1
#endif
#endif



#define NCP_INIT_REG32(_reg,_v) {ncp_uint32_t *_x=(ncp_uint32_t *)&(_reg); *_x=_v;}

#if 0
#define NCP_DEV_EVENT_DEBUG
#endif

/* function prototype for event enable function */
typedef ncp_st_t (* ncp_dev_event_enable_fn_t)(ncp_dev_hdl_t devHdl);

/* function prototype for event init function */
typedef ncp_st_t (* ncp_dev_event_disable_fn_t)(ncp_dev_hdl_t devHdl);

typedef struct ncp_dev_event_st {
    ncp_dev_event_type_t type;              /* event type */
    ncp_bool_t bIdValid;                    /* TRUE if id field is valid for this event. */
    ncp_dev_event_enable_fn_t enableFn;     /* automatic enable function. Called when first callback is registered. */
    ncp_dev_event_disable_fn_t disableFn;   /* automatic disable function. Called when last callback is unregistered. */
} ncp_dev_event_t;

#define NCP_DEV_EVENT_HDL_COOKIE    (0x0a0b0c0d)

typedef struct ncp_dev_event_cbk_node_st {
    ncp_uint32_t                cookie;
    ncp_dev_event_handler_t     handlerInfo;
    struct ncp_dev_event_cbk_node_st   *next;
    struct ncp_dev_event_cbk_node_st   *prev;
    ncp_bool_t                  unlinked;
    ncp_bool_t                  inUse;
} ncp_dev_event_cbk_node_t;

typedef struct ncp_dev_event_hdlr_list_st {
    ncp_dev_event_cbk_node_t *cbkList;
    ncp_dev_event_t          *eventInfo;
} ncp_dev_event_hdlr_list_t;

typedef struct ncp_dev_event_list_st {
    ncp_dev_event_hdlr_list_t lists[NCP_DEV_EVENT_LAST];
} ncp_dev_event_list_t;

/* Function to notify an event */
ncp_st_t
ncp_dev_event_dispatch(ncp_dev_hdl_t devHdl, ncp_dev_event_type_t type,
                       ncp_uint32_t id, void *eventData);

#define NCP_DEV_LBI_CS_MAX 16

/*
 * ncp_dev_t
 *
 * Per-NCP instance device structure.
 *
 */

struct ncp_dev_s
{
    ncp_uint32_t             tag;           /* Structure validation tag */
    int                      num;           /* instance number */
    ncp_uint32_t             flags;         /* driver flags */
    ncp_byte_order_t         hostEndian;    /* is this host big/little endian */
    struct {
        ncp_uint64_t         busAddr;       /* BUS base address */
        void                *cpuAddr;       /* CPU virtual base address */
        ncp_uint32_t         size;          /* size of BAR space */
    } bar[NCP_BAR_REGS];                    /* base addresses */
    ncp_dev_page_t           pages[NCP_DEV_MAX_PAGES];
    ncp_uint64_t             axiDmaBase;
    ncp_uint64_t             busDmaOffset;
    ncp_dev_addr_map_t      *pLcmMap;
    ncp_uint32_t             fixedTpage7;

    ncp_region_io_t         *lastRegion;    /* last valid region map entry */
    ncp_region_coh_io_t     *coherentMap;   /* pointer to the chip-specific coherent map */

    ncp_uint32_t             lastMappedPage; /* last paged access mapping */
    ncp_dev_bus_dyn_page_map_fn_t  dynamicPageMapFn;
    ncp_bool_t               initDevConfig;  /* devConfig init control */
    ncp_dev_config_t        *config;         /* driver configuration variables */


    ncp_gpreg_revnum_t       fpgaRev;       /* c3s AXIS FPGA revision */
    ncp_uint32_t             ncaConfigInit; /* cached value of config_init reg*/
    ncp_uint32_t             ncaAckTimeoutCnt; /* NCA PIO timeout */

#ifdef NCP_DEV_SOCKET
    ncp_dev_hdl_t            sockHdl;
#endif

    ncp_hdl_t                vpmHdl;        /* handle for kernel vpm module */
    ncp_dev_event_list_t     eventList;     /* internal event management */
    ncp_hdl_t                eioaHdl;       /* handle for kernel eioa module */

    ncp_dev_event_hdl_t      eventHandlers[NCP_DEV_EVENT_LAST]; /* driver registered events */

    ncp_bool_t               useInterrupts; /* does platform support interrupts? */
    ncp_uint8_t              isrActive;     /* non-zero when in interrupt */
    ncp_bool_t               isNCAv2; 
    ncp_dev_isr_t            isr[NCP_INTR_GIC_MAX];                /* External ACP */
    ncp_dev_intr_src_t       localIrqSources[NCP_INTR_GIC_MAX];    /* Local ACP    */

    ncp_dev_isr_register_t   isrRegister;
    ncp_dev_isr_fn_t         isrFree;
    ncp_dev_isr_fn_t         irqMask;
    ncp_uint32_t             irqMax;
    ncp_uint32_t             ncaGrpIrqMin;
    ncp_uint32_t             ncaGrpIrqMax;
    ncp_uint32_t             timerIrq;
    ncp_dev_isr_t            ncaAlarmIsr;
    ncp_dev_isr_t            timerIsr;
    const char             **irqNames;
    ncp_alarm_intr_regs_t    *alarmSrcRegs[NCP_INTR_GIC_MAX];
    ncp_dev_isr_t            serviceIsr[NCP_INTR_GIC_MAX];
    ncp_waitq_t              *fem_waitq;
    ncp_waitq_t              *alarm_waitq;
    ncp_waitq_t              *timer_waitq;
    ncp_waitq_t              *timer_cpu_waitq[16];
    ncp_waitq_t              *lbiIntr_waitq[NCP_DEV_LBI_INTR_MAX];   /* LBI interrupt support */
    ncp_uint32_t             lbiIntrStatus;
    ncp_uint32_t             lbiGpioEnbMask;
    ncp_uint32_t             lbiCsEnbMask;

    ncp_raw_spinlock_t           lock;
    ncp_bsp_spinlock_t       ncaAccessLock;
    ncp_raw_spinlock_t       isrLock;  /* Should this be per group ? */
    ncp_spinlock_t           lbiLock;  /* TODO: should this be a semaphore instead?? */
    ncp_sem_t                dmaIoSem;
    ncp_sem_t                i2cLock;

    ncp_dev_nca_isr_common_t ncp_dev_IsrCommon[
                      NCP_NCA_MAX_PCQ_GROUPS]; /* bottom half status bits */  
    ncp_dev_stats_t          stats;         /* device statistics */
    ncp_hdl_t                i2cHdl;        /* relevant runtime state */
    ncp_hdl_t                catHdl;        /* relevant runtime state */
    ncp_hdl_t                pkaHdl;        /* relevant runtime state */
    ncp_uint32_t             *ntimcWriteBuf;/* pointer to buffer for ntimc writes */
    ncp_uint64_t             refStrobeTs;  /* Captured ref strobe timestamp */
    ncp_uint64_t             cpuIsrSeq[16];  /* Captured CPU Timer timestamp */
#if defined(NCP_LINUX) && defined(NCP_KERNEL)
    struct timer_list        cmemZqCalibTimer;
#else
#if defined(NCP_OSE)
    PROCESS cmemZqCalibTimer;
#else /* Includes NCP_VXWORKS */
    ncp_uint8_t cmemZqCalibTimer[0x20];
#endif /* NCP_OSE */
#endif /* NCP_LINUX */
    ncp_uint32_t zqTimerInterval;
    ncp_uint32_t numCmems;
    ncp_spinlock_t           cmemLock[2];
    ncp_bool_t zqTimerInitted;
#ifdef NCP_PROFILER
    ncp_hdl_t                profilerHdl;
    ncp_hdl_t                profilerHdlIsr;
#endif
    ncp_bool_t               noPhyConfig;
    ncp_uint32_t        activeGrpMask; /* groups associated with local domain */
    ncp_uint32_t        numPCQgroups;  /* ncav2 has 16, others have 6 */
    ncp_task_ncaV2_domain_bundle_t myDomainBundle;
    ncp_dev_cpcq_t           cpcq;
};


#ifdef USE_SE_ISR_WAKEUP
ncp_st_t
ncp_dev_se_fem_wait_for_isr_wakeup(ncp_dev_t *dev);
#endif

ncp_st_t
ncp_se_fem_intr_enable(ncp_dev_hdl_t devHdl);

ncp_st_t
ncp_se_fem_intr_disable(ncp_dev_hdl_t devHdl);

ncp_st_t
ncp_timer_intr_enable(ncp_dev_hdl_t devHdl);

ncp_st_t
ncp_timer_intr_disable(ncp_dev_hdl_t devHdl);


/*
 * Miscellanous forwards
 */

ncp_st_t ncp_dev_assign_pages(
    ncp_dev_t *dev);

/* --- forwards ... the following are accessed outside of ncp_dev.c now --- */

#define NCP_DEV_IO_PROTOTYPE(method, rw) \
    ncp_st_t ncp_dev_##method##_##rw  ( \
        ncp_dev_t       *dev,           \
        ncp_region_io_t *region,        \
        ncp_uint64_t     offset,        \
        ncp_uint32_t    *buffer,        \
        ncp_uint32_t     count,         \
        ncp_uint32_t     flags,         \
        ncp_uint32_t     cmdType,       \
        ncp_uint32_t     xferWidth);

NCP_DEV_IO_PROTOTYPE(direct, read)
NCP_DEV_IO_PROTOTYPE(direct, write)
NCP_DEV_IO_PROTOTYPE(indirect, read)
NCP_DEV_IO_PROTOTYPE(indirect, write)
NCP_DEV_IO_PROTOTYPE(dcr, read)
NCP_DEV_IO_PROTOTYPE(dcr, write)
NCP_DEV_IO_PROTOTYPE(plb_srio_paged, read)
NCP_DEV_IO_PROTOTYPE(plb_srio_paged, write)
NCP_DEV_IO_PROTOTYPE(bus_config, read)
NCP_DEV_IO_PROTOTYPE(bus_config, write)
NCP_DEV_IO_PROTOTYPE(sysmem_cr, read)
NCP_DEV_IO_PROTOTYPE(sysmem_cr, write)
NCP_DEV_IO_PROTOTYPE(sysmem_nic, read)
NCP_DEV_IO_PROTOTYPE(sysmem_nic, write)
NCP_DEV_IO_PROTOTYPE(paged, read)
NCP_DEV_IO_PROTOTYPE(paged, write)
NCP_DEV_IO_PROTOTYPE(tgt_indexed, read)
NCP_DEV_IO_PROTOTYPE(tgt_indexed, write)
NCP_DEV_IO_PROTOTYPE(coherent, read)
NCP_DEV_IO_PROTOTYPE(coherent, write)
NCP_DEV_IO_PROTOTYPE(mdio, read)
NCP_DEV_IO_PROTOTYPE(mdio, write)
NCP_DEV_IO_PROTOTYPE(i2cprot, read)
NCP_DEV_IO_PROTOTYPE(i2cprot, write)
NCP_DEV_IO_PROTOTYPE(ntimc, read)
NCP_DEV_IO_PROTOTYPE(ntimc, write)
NCP_DEV_IO_PROTOTYPE(l2_indirect, read)
NCP_DEV_IO_PROTOTYPE(l2_indirect, write)
NCP_DEV_IO_PROTOTYPE(trace_indirect, read)
NCP_DEV_IO_PROTOTYPE(trace_indirect, write)
NCP_DEV_IO_PROTOTYPE(hss_phy, read)
NCP_DEV_IO_PROTOTYPE(hss_phy, write)
NCP_DEV_IO_PROTOTYPE(lbi, read)
NCP_DEV_IO_PROTOTYPE(lbi, write)
NCP_DEV_IO_PROTOTYPE(hostmem, read)
NCP_DEV_IO_PROTOTYPE(hostmem, write)
NCP_DEV_IO_PROTOTYPE(sysmem_vindex, read)
NCP_DEV_IO_PROTOTYPE(sysmem_vindex, write)
NCP_DEV_IO_PROTOTYPE(sysmem_vaddr, read)
NCP_DEV_IO_PROTOTYPE(sysmem_vaddr, write)
NCP_DEV_IO_PROTOTYPE(apb2ser_indirect, read)
NCP_DEV_IO_PROTOTYPE(apb2ser_indirect, write)
NCP_DEV_IO_PROTOTYPE(cdc_paged, read)
NCP_DEV_IO_PROTOTYPE(cdc_paged, write)

#if defined ( NCP_KERNEL ) || defined ( NCP_OSE )

/*  define user-level i/o functions for kernel-mode */
#define  ncp_usleep(us) ncp_sys_usleep(us)

#define  ncp_read8(d, r, o, v)  ncp_dev_read8(d, r, o, v)
#define ncp_read16(d, r, o, v) ncp_dev_read16(d, r, o, v)
#define ncp_read32(d, r, o, v) ncp_dev_read32(d, r, o, v)
#define ncp_read64(d, r, o, v) ncp_dev_read64(d, r, o, v)

#define  ncp_block_read8(d, r, o, b, c, f)  ncp_dev_block_read8(d, r, o, b, c, f)
#define ncp_block_read16(d, r, o, b, c, f) ncp_dev_block_read16(d, r, o, b, c, f)
#define ncp_block_read32(d, r, o, b, c, f) ncp_dev_block_read32(d, r, o, b, c, f)
#define ncp_block_read64(d, r, o, b, c, f) ncp_dev_block_read64(d, r, o, b, c, f)


#define  ncp_write8(d, r, o, v)  ncp_dev_write8(d, r, o, v)
#define ncp_write16(d, r, o, v) ncp_dev_write16(d, r, o, v)
#define ncp_write32(d, r, o, v) ncp_dev_write32(d, r, o, v)
#define ncp_write64(d, r, o, v) ncp_dev_write64(d, r, o, v)

#define  ncp_block_write8(d, r, o, b, c, f)  ncp_dev_block_write8(d, r, o, b, c, f)
#define ncp_block_write16(d, r, o, b, c, f) ncp_dev_block_write16(d, r, o, b, c, f)
#define ncp_block_write32(d, r, o, b, c, f) ncp_dev_block_write32(d, r, o, b, c, f)
#define ncp_block_write64(d, r, o, b, c, f) ncp_dev_block_write64(d, r, o, b, c, f)

#define ncp_block_fill(d, r, o, s, f)   ncp_dev_block_fill(d, r, o, s, f) 
#define ncp_broadcast_block_write(d, r, o, s, f)   ncp_dev_broadcast_block_write(d, r, o, s, f) 
#define ncp_broadcast_block_fill(d, r, o, s, f)   ncp_dev_broadcast_block_fill(d, r, o, s, f) 
#define ncp_read_modify_write(d, r, o, s, f)   ncp_dev_read_modify_write(d, r, o, s, f) 
#define ncp_scatter_write(d, r, s, f)   ncp_dev_scatter_write(d, r, s, f)
#define ncp_broadcast_scatter_write(d, r, s, f)   ncp_dev_broadcast_scatter_write(d, r, s, f)

#define ncp_coherent_sysmem_read(d, r, a, b, c, w, f) ncp_dev_coherent_sysmem_read(d, r, a, b, c, w, f)
#define ncp_coherent_sysmem_write(d, r, a, b, c, w, f) ncp_dev_coherent_sysmem_write(d, r, a, b, c, w, f)

#define  ncp_mdio_read(d, r, o, b, c, f)  ncp_dev_mdioRead(d, r, o, b, c, f)
#define  ncp_mdio_write(d, r, o, b, c, f)  ncp_dev_mdioWrite(d, r, o, b, c, f)

#define ncp_comment(s)

#endif

ncp_st_t
ncp_dev_read_invalid_access(
    ncp_dev_t       *dev,
    ncp_region_io_t *region,
    ncp_uint64_t     offset,
    ncp_uint32_t    *buffer,
    ncp_uint32_t     count,
    ncp_uint32_t     flags,
    ncp_uint32_t     cmdType,
    ncp_uint32_t     xferWidth);

ncp_st_t
ncp_dev_write_invalid_access(
    ncp_dev_t       *dev,
    ncp_region_io_t *region,
    ncp_uint64_t     offset,
    ncp_uint32_t    *buffer,
    ncp_uint32_t     count,
    ncp_uint32_t     flags,
    ncp_uint32_t     cmdType,
    ncp_uint32_t     xferWidth);



void
ncp_nca_v1_cpcq_entry_put(
    ncp_dev_cpcq_t *pcq,
    ncp_uint16_t   *idx,
    ncp_uint32_t   *entry);
void
ncp_nca_v2_cpcq_entry_put(
    ncp_dev_cpcq_t *pcq,
    ncp_uint16_t   *idx,
    ncp_uint32_t   *entry);

ncp_bool_t
ncp_dev_pcq_is_full(ncp_task_pcq_t *pcq);


/* interrupt configuration/service functions */
/* interrupt service routines */

#ifdef NCP_KERNEL
ncp_irqreturn_t ncp_dev_intr_ncaV2(int irq, void *intrSrc);
ncp_irqreturn_t ncp_dev_intr_ncaV1(int irq, void *intrSrc);
#ifdef NCP_DEV_USE_BSP_LOCK
extern int ncr_lock(int);
extern int ncr_unlock(int);
extern raw_spinlock_t  nca_access_lock;
#define NCP_NCA_ACCESS_LOCK (nca_access_lock)
#else
#define NCP_NCA_ACCESS_LOCK (dev->ncaAccessLock)
#endif
#endif  /* NCP_KERNEL */

void ncp_dev_intr(void *intrSrc);
void ncp_dev_intr_local (int irq, void *myIsrCookie);
/* interrupt configuration functions */
void ncp_dev_intr_config(ncp_dev_t *dev);


ncp_st_t
ncp_dev_intr_isr_free(ncp_dev_t *dev, ncp_uint32_t irq);

ncp_st_t ncp_dev_intr_isr_register(
        ncp_dev_t *dev,
        ncp_uint32_t irq,
        ncp_dev_isr_t isr);

void
ncp_task_breakpoint(int reason);

ncp_st_t ncp_dev_gsm_info_get(
    ncp_dev_hdl_t devHdl,
    ncp_dev_gsm_info_t *gsmInfo);

/* 
 * the basic PIO config ring function. 
 * use this for config ring access from interrup handlers 
 */
ncp_st_t
ncp_dev_cfg_pio_io32(
    ncp_dev_t * dev,
    ncp_region_io_t *region,
    ncp_uint64_t offset,
    ncp_uint32_t * buffer,
    ncp_uint32_t count,
    ncp_uint32_t cmdType,
    ncp_uint32_t maxXferCount,
    ncp_uint32_t flags);

ncp_st_t
ncp_dev_sysmem_nic_fill(
    ncp_dev_t          *dev,
    ncp_region_io_t    *region,
    ncp_uint64_t        offset,
    ncp_uint32_t       *buffer,
    ncp_uint32_t        count,
    ncp_uint32_t        flags,
    ncp_uint32_t        cmdType,
    ncp_uint32_t        xferWidth,
    _ncp_dev_write_fn_t  writeFn);

#endif /* __NCP_DEV_PVT_H__ */
