/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


#ifndef __NCP_DEV_LINUX_H__
#define __NCP_DEV_LINUX_H__

#include "ncp_dev.h"

#ifndef LINUX_VERSION_CODE
#  include <linux/version.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

#ifdef __KERNEL__
#include <linux/version.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/ioctl.h>
#include <linux/slab.h>
#include <linux/pci.h>
#include <linux/poll.h>
#include <linux/interrupt.h>
#include <linux/skbuff.h>

#else

#include <sys/ioctl.h>

#endif /* __KERNEL__ */

#ifdef NCP_DEV_PCI
#include "ncp_bus_pci.h"
#endif
#ifdef NCP_DEV_PLX
#include "ncp_bus_plx.h"
#endif
#ifdef NCP_DEV_SRIO
#include "ncp_bus_srio.h"
#endif
#ifdef NCP_DEV_SRIOEP
#include "ncp_bus_srioep.h"
#endif
#ifdef NCP_DEV_PLB
#include "ncp_bus_plb.h"
#endif

#include "ncp_pka.h"
#include "ncp_pka_timing.h"


/******************************************************************************
* Constants and 'Switches'
******************************************************************************/

#define NCP_PQFPGA_CHECK_MULTIPLE

/******************************************************************************
* VM_RESERVED Flag is deprecated in Linux 3.10 kernel 
******************************************************************************/
#ifndef VM_RESERVED
#define VM_RESERVED (VM_DONTEXPAND | VM_DONTDUMP)
#endif


/******************************************************************************
* IOCTL Structures and constants
******************************************************************************/

/*
 * IOC Structure typedefs, constants, and macros
 */

/* NCP_IOC_TR_LVL_SET IOCTL structure definition */
typedef struct ncp_ioc_tr_lvl_set {
    ncp_uint32_t     level;      /* trace level */
    NCP_DECLARE_POINTER(ncp_st_t, st);         /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_tr_lvl_set_t;

/* NCP_IOC_TR_LVL_GET IOCTL structure definition */
typedef struct ncp_ioc_tr_lvl_get {
    NCP_DECLARE_POINTER(ncp_uint32_t, level);      /* trace level */
    NCP_DECLARE_POINTER(ncp_st_t, st);         /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_tr_lvl_get_t;

/* NCP_IOC_VERSION IOCTL structure definition */
typedef struct ncp_ioc_version {
    NCP_DECLARE_POINTER(char, version);    /* version string return location */
    NCP_DECLARE_POINTER(ncp_st_t, st);         /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_version_t;

/* NCP_IOC_HW_VERSION IOCTL structure definition */
typedef struct ncp_ioc_hw_version {
    NCP_DECLARE_POINTER(ncp_version_t, version);/* version return location */
    NCP_DECLARE_POINTER(ncp_st_t, st);         /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_hw_version_t;

/* NCP_IOC_DEV_NUM_GET IOCTL structure definition */
typedef struct {
    NCP_DECLARE_POINTER(ncp_uint32_t, devNum);         /* OUT: device number */
    NCP_DECLARE_POINTER(ncp_st_t, st);             /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_dev_num_get_t;

/* NCP_IOC_INFO IOCTL structure definition */
typedef struct ncp_ioc_info {
    NCP_DECLARE_POINTER(ncp_dev_info_t, info);    /* device driver information */
    NCP_DECLARE_POINTER(ncp_st_t, st);         /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_info_t;

/* NCP_IOC_INFO_GET IOCTL structure definition */
typedef struct ncp_ioc_info_get {
    NCP_DECLARE_POINTER(ncp_uint32_t, info);       /* device driver state information */
    NCP_DECLARE_POINTER(ncp_st_t, st);         /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_info_get_t;

/* NCP_IOC_GSM_INFO IOCTL structure definition */
typedef struct ncp_ioc_gsm_info_get {
    NCP_DECLARE_POINTER(ncp_dev_gsm_info_t, info);
    NCP_DECLARE_POINTER(ncp_st_t, st);              /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_gsm_info_t;

/* NCP_IOC_TASK_KMODE_CFG_T structure definition */
typedef struct ncp_ioc_task_kmode_cfg_s {
    NCP_DECLARE_POINTER(void,  cfgPtr);   /* ptr to swState */
    ncp_int32_t        cfgSize;          /* NumBytes to copy into kernel space */                                    
    NCP_DECLARE_POINTER(void, pGSMinfo);
    NCP_DECLARE_POINTER(ncp_st_t, st);    /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_task_nca_kmode_cfg_t;

/* NCP_IOC_TASK_FINISH_KMODE_CFG_T structure definition */
typedef struct ncp_ioc_task_kmode_finish_cfg_s {
    NCP_DECLARE_POINTER(void, pGSMinfo);
    ncp_uint32_t        kmodePoolSz;
    NCP_DECLARE_POINTER(ncp_st_t, st);    /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_task_nca_kmode_finish_cfg_t;

/* NCP_IOC_TASK_KMODE_CFG_T structure definition */
typedef struct ncp_ioc_task_kmode_blocks_s {
    void                *cfgPtr;   /* Hack - cannot include both v1 and v2 */
                                    /* headers */
    ncp_uint32_t        cfgSize;   /* NumBytes to copy into kernel space */                                    
    ncp_st_t            *st;         /* OUT: status code */
    ncp_uint32_t        poolId;       /* ID of pool to query */
    ncp_uint32_t        blockSize;    /* Blocksize to query */
    ncp_uint32_t        *numBlocks;   /* OUT: number of blocks available */
} NCP_COMPAT_PACKED ncp_ioc_task_ncaV2_kmode_blocks_t;

/* NCP_TASK_NCAV2_SET_DOMAIN_BUNDLE_T structure definition */
typedef struct ncp_ioc_task_ncaV2_set_domain_bundle_s {
    ncp_uint64_t domainBundlePA;
    ncp_int32_t  domainBundleSize;
    ncp_st_t     *st;         /* OUT: status code */    
} NCP_COMPAT_PACKED ncp_ioc_task_ncaV2_set_domain_bundle_t;

typedef struct ncp_task_tqs_state_modify_s {
    ncp_uint8_t      tqsID;      /* which TQS? */
    ncp_bool_t       disableTQS; /* TRUE->disable, FALSE->enable */
    ncp_uint8_t      grp;        /* grp membership */
    NCP_DECLARE_POINTER(ncp_st_t, st);         /* OUT: status code */    
} NCP_COMPAT_PACKED ncp_task_tqs_state_modify_t;

/* NCP_IOC_INFO_SET IOCTL structure definition */
typedef struct ncp_ioc_info_set {
    ncp_uint32_t     info;             /* device driver state information */
    NCP_DECLARE_POINTER(ncp_st_t, st); /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_info_set_t;

/* NCP_IOC_STATS IOCTL structure definition */
typedef struct ncp_ioc_stat {
    NCP_DECLARE_POINTER(ncp_dev_stats_t, stats);  /* device driver statistics */
    NCP_DECLARE_POINTER(ncp_st_t, st);            /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_stats_t;

typedef struct ncp_ioc_status {
    NCP_DECLARE_POINTER(ncp_st_t, st);         /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_status_t;

/* NCP_TIMER_WAIT_FOR_INTERRUPT structure definition */
typedef struct ncp_ioc_timestamp {
    NCP_DECLARE_POINTER(ncp_uint64_t, ticks);  /* ref strobe timestamp */
    NCP_DECLARE_POINTER(ncp_st_t, st);         /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_timestamp_t;

/* NCP_TIMER_WAIT_FOR_CPU_INTERRUPT structure definition */
typedef struct ncp_ioc_cpu_timer_info {
    ncp_uint32_t timerIndex;  /* cpu timer index 0-15 */
    ncp_uint32_t     flags;
    ncp_uint64_t     lastSeq;  /* IN: last user captured sequence # for CPU Timer */
    NCP_DECLARE_POINTER(ncp_uint64_t, currentSeq);  /* OUT: sequence number of CPU Timer */
    NCP_DECLARE_POINTER(ncp_st_t, st);         /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_cpu_timer_info_t;

/* generic read/write IOCTL definition */
typedef struct ncp_ioc_rw {
    ncp_region_id_t  regionId;         /* NCP region ID */
    ncp_uint64_t     offset;           /* start offset within NCP region */
    NCP_DECLARE_POINTER(void, buffer); /* buffer address */
    ncp_uint32_t     count;            /* transfer count */
    ncp_uint32_t     flags;            /* I/O control flags */
    ncp_uint32_t     xferWidth;        /* transfer width */
    NCP_DECLARE_POINTER(ncp_st_t, st); /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_rw_t;

/* NCP_IOC_TRANS_ADD */
typedef struct ncp_ioc_trans_add_s {
    ncp_dev_trans_type_t transType;
    union {
        ncp_dev_trans_udelay_t udelay;
        ncp_dev_trans_block_fill32_t bf32;
        ncp_dev_trans_block_write32_t bw32;
    } u;
    ncp_uint32_t flags;
    NCP_DECLARE_POINTER(ncp_st_t, st);
} NCP_COMPAT_PACKED ncp_ioc_trans_add_t;


/* NCP_IOC_ALARM_GET */
typedef struct {
    ncp_bool_t           blocking;
    NCP_DECLARE_POINTER(ncp_alarm_bitmask_t, alarm);
    NCP_DECLARE_POINTER(ncp_st_t,            st);
} NCP_COMPAT_PACKED ncp_ioc_alarm_t;

typedef struct {
    ncp_uint32_t irq;
    ncp_uint32_t size;
    NCP_DECLARE_POINTER(ncp_alarm_intr_regs_t, regs);
    NCP_DECLARE_POINTER(ncp_st_t,              st);
} NCP_COMPAT_PACKED ncp_ioc_alarm_reg_t;

typedef struct {
    ncp_uint32_t timerInterval;
    ncp_uint32_t numCmems;
} NCP_COMPAT_PACKED ncp_ioc_treemem_zq_cal_t;

/* NCP_IOC_LBI_CTRL */
typedef struct {
    ncp_uint32_t      select;
    ncp_uint32_t      action;
    ncp_uint32_t      mode;
    ncp_uint32_t      sense;
    NCP_DECLARE_POINTER(ncp_uint8_t, val);
    ncp_uint32_t      deviceWidth;
    ncp_uint32_t      csFlags;
    NCP_DECLARE_POINTER(ncp_st_t, st);
} NCP_COMPAT_PACKED ncp_ioc_lbi_ctrl_t;

/*
 * Begin New IOCTL structures for NCA Task IO, including the NCA Task IO system call model
 */


#define NCP_NCA_VM_FLAGS_COHERENT (VM_IO | VM_SHARED | VM_LOCKED)

/* #define NCP_NCA_PAGE_FLAGS_COHERENT (_PAGE_RW | _PAGE_COHERENT | _PAGE_ACCESSED | _PAGE_PRESENT | _PAGE_GUARDED) */
#define NCP_NCA_PAGE_FLAGS_COHERENT (_PAGE_RW | _PAGE_COHERENT | _PAGE_ACCESSED | _PAGE_PRESENT) 


void *
ncp_mem_mmap(ncp_dev_hdl_t devHdl, void *startAddr, ncp_uint32_t size, 
             ncp_uint64_t physAddr);
 
#define NCP_MEM_MMAP(devHdl, pStartAddr, size, physAddr)  \
     ({                                          \
         void *_ptr = NULL;                      \
         _ptr = ncp_mem_mmap((ncp_dev_hdl_t)devHdl, (void *)pStartAddr, size, physAddr);  \
         _ptr;                                   \
     })

 /*
  * End New IOCTL structures for NCA Task IO
  */


/********************* Begin data structs for VPM *************/

typedef struct ncp_vpm_kernel_info_st {
    NCP_DECLARE_HDL(ncp_hdl_t, uVpmHdl);
    NCP_DECLARE_POINTER(ncp_st_t, st);
} ncp_vpm_kernel_info_t;

/********************* End data structs for VPM *************/


/*
 * Begin IOCTL structures for EIOA kernel mode API's
 */
/*
 * generic stucture 
 */
typedef struct ncp_eioa_t5_s {
    NCP_DECLARE_HDL(ncp_hdl_t, ncpHdl);
    ncp_uint32_t        macChan;
    ncp_uint32_t        vOne;
    ncp_uint32_t        vTwo;
    ncp_uint32_t        vThree;
    ncp_uint32_t        vFour;
    ncp_uint32_t        vFive;
    NCP_DECLARE_POINTER(void, pOne);
    NCP_DECLARE_POINTER(void, pTwo);
    NCP_DECLARE_POINTER(void, pThree);
    NCP_DECLARE_POINTER(void, pFour);
    NCP_DECLARE_POINTER(void, pFive);
    NCP_DECLARE_POINTER(ncp_st_t, ncp_status);
}  NCP_COMPAT_PACKED ncp_eioa_t5_t;

 /*
  * End IOCTL structures for EIOA API's ***********************
  */


/*
 * BEGIN IOCTL structures for Crash Analysis Tools ************
 */

typedef struct ncp_ioc_cat_config_s
{
    ncp_bool_t        catMemoryEnable;   /* IN: */
    ncp_uint64_t      catMemoryPhysAddr; /* IN: */
    ncp_uint64_t      catMemorySize;     /* IN: */
    NCP_DECLARE_POINTER(ncp_uint64_t, oCatMemoryNeeded);  /* OUT: */
    NCP_DECLARE_POINTER(ncp_st_t, ncp_status);        /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_cat_config_t;

typedef struct ncp_ioc_cat_write_s
{
    ncp_uint32_t      flags;      /* I/O control flags */
    NCP_DECLARE_POINTER(ncp_st_t, ncp_status); /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_cat_write_t;

typedef struct ncp_ioc_cat_write_raw_s
{
    NCP_DECLARE_POINTER(void, buffer);         /* buffer address */
    ncp_uint32_t      count;               /* byte count in buffer */
    ncp_uint32_t      flags;               /* I/O control flags */
    NCP_DECLARE_POINTER(ncp_st_t, ncp_status); /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_cat_write_raw_t;

typedef struct ncp_ioc_cat_write_finalize_s
{
    ncp_uint32_t      flags;      /* I/O control flags */
    NCP_DECLARE_POINTER(ncp_st_t, ncp_status); /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_cat_write_finalize_t;

typedef struct ncp_ioc_cat_read_s
{
    NCP_DECLARE_POINTER(ncp_uint8_t, buffer);     /* OUT: location to place read data */
    ncp_uint32_t      bufferSize; /* IN: max # of bytes to place in buffer */
    NCP_DECLARE_POINTER(ncp_uint64_t, offset);     /* OUT: displace into recovery data to read */
    NCP_DECLARE_POINTER(ncp_uint32_t, readSize);   /* OUT: # of bytes actually read */
    ncp_uint32_t      flags;      /* IN: I/O control flags */
    NCP_DECLARE_POINTER(ncp_st_t, ncp_status); /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_cat_read_t;

typedef struct ncp_cat_size_s
{
    NCP_DECLARE_POINTER(ncp_uint32_t, catMemorySize); /* OUT: Size of storage being used for CAT */
    NCP_DECLARE_POINTER(ncp_st_t, ncp_status); /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_cat_size_t;

/*
 * END IOCTL structures for Crash Analysis Tools ************
 */


/*
 * BEGIN IOCTL structures for Crypto/PKA APIs ************
 */

typedef struct ncp_ioc_pka_config_s
{
    NCP_DECLARE_POINTER(ncp_st_t, ncp_status); /* OUT: status code */
    ncp_bool_t online;                         /* IN:  Force online? */
} NCP_COMPAT_PACKED ncp_ioc_pka_config_t;
        /* 
         * ncp_dev_pka_config()
         */

typedef struct ncp_ioc_pka_fn_s
{
    NCP_DECLARE_POINTER(ncp_st_t, ncp_status); /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_pka_fn_t;
        /* 
         * ncp_dev_pka_destroy()
         * ncp_dev_pka_trans_kill()
         * ncp_dev_pka_profile_init()
         */

typedef struct ncp_ioc_pka_trans_start_s
{
    ncp_pka_trans_in_t  inArgs;         /* IN: Specification of next op */
    NCP_DECLARE_POINTER(ncp_st_t, ncp_status); /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_pka_trans_start_t;

typedef struct ncp_ioc_pka_trans_poll_s
{
    NCP_DECLARE_POINTER(ncp_pka_trans_out_t, outArgs);    /* OUT: Result of in-progress op */
    NCP_DECLARE_POINTER(ncp_st_t,            ncp_status); /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_pka_trans_poll_t;

typedef struct ncp_ioc_pka_trans_blocking_s
{
    ncp_pka_trans_in_t  inArgs;         /* IN: Specification of next op */
    NCP_DECLARE_POINTER(ncp_pka_trans_out_t, outArgs);    /* OUT: Result of in-progress op */
    NCP_DECLARE_POINTER(ncp_st_t,            ncp_status); /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_pka_trans_blocking_t;

typedef struct ncp_ioc_pka_info_s
{
    NCP_DECLARE_POINTER(ncp_pka_info_t, outInfo);    /* OUT: Result of operation */
    NCP_DECLARE_POINTER(ncp_st_t,       ncp_status); /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_pka_info_t;

typedef struct ncp_ioc_pka_prof_retrieve_s
{
#if     defined(NCP_PROFILE)
    NCP_DECLARE_POINTER(ncp_prof_t, prof);          /* INOUT: Result of operation */
#endif
    NCP_DECLARE_POINTER(ncp_st_t, ncp_status);    /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_pka_prof_retrieve_t;


/*
 * END IOCTL structures for Crypto/PKA APIs ************
 */

/********************* Begin data structs for Profiler *************/

typedef struct ncp_ioc_profiler_num_entries_st
{
    ncp_uint32_t *numEntries;
    ncp_st_t *st;
} ncp_ioc_profiler_num_entries_t;

typedef struct ncp_ioc_profiler_entries_st
{
    ncp_uint32_t startEntry;
    ncp_uint32_t numEntries;
    void *entries;
        
    ncp_st_t *st;
} ncp_ioc_profiler_entries_t;


/********************* End data structs for Profiler *************/

/* generic structure for passing in an ncp_uint32_t value */
typedef struct ncp_ioc_u32 {
    ncp_uint32_t    value;    /* array of u32 values */
    NCP_DECLARE_POINTER(ncp_st_t, st);
} NCP_COMPAT_PACKED ncp_ioc_u32_t;



/******************************************************************************
** I/O control (IOCTL) command definitions
******************************************************************************/

#define NCP_IOC                 ('n')
#define NCP_IOC_UNREF           _IO(NCP_IOC, 1)    /* reset mod usage cnt */
#define NCP_IOC_TR_LVL_SET      _IOWR(NCP_IOC, 2, ncp_ioc_tr_lvl_set_t)
#define NCP_IOC_TR_LVL_GET      _IOWR(NCP_IOC, 3, ncp_ioc_tr_lvl_get_t)
#define NCP_IOC_HW_VERSION      _IOWR(NCP_IOC, 4, ncp_ioc_hw_version_t)
#define NCP_IOC_VERSION         _IOWR(NCP_IOC, 5, ncp_ioc_version_t)
#define NCP_IOC_DEV_NUM_GET     _IOWR(NCP_IOC, 6, ncp_ioc_dev_num_get_t)
#define NCP_IOC_RESET           _IOWR(NCP_IOC, 7, ncp_ioc_status_t)
#define NCP_IOC_PCI_RESET       _IOWR(NCP_IOC, 8, ncp_ioc_status_t)
#define NCP_IOC_PCI_REINIT      _IOWR(NCP_IOC, 9, ncp_ioc_status_t)
#define NCP_IOC_ISR_DISABLE     _IOWR(NCP_IOC, 10, ncp_ioc_status_t)
#define NCP_IOC_INFO            _IOWR(NCP_IOC, 11, ncp_ioc_info_t)
#define NCP_IOC_INFO_GET        _IOWR(NCP_IOC, 12, ncp_ioc_info_get_t)
#define NCP_IOC_INFO_SET        _IOWR(NCP_IOC, 13, ncp_ioc_info_set_t)
#define NCP_IOC_STATS           _IOWR(NCP_IOC, 14, ncp_ioc_stats_t)
#define NCP_IOC_READ8           _IOWR(NCP_IOC, 15, ncp_ioc_rw_t)
#define NCP_IOC_READ16          _IOWR(NCP_IOC, 16, ncp_ioc_rw_t)
#define NCP_IOC_READ32          _IOWR(NCP_IOC, 17, ncp_ioc_rw_t)
#define NCP_IOC_WRITE8          _IOWR(NCP_IOC, 18, ncp_ioc_rw_t)
#define NCP_IOC_WRITE16         _IOWR(NCP_IOC, 19, ncp_ioc_rw_t)
#define NCP_IOC_WRITE32         _IOWR(NCP_IOC, 20, ncp_ioc_rw_t)
#define NCP_IOC_FILL            _IOWR(NCP_IOC, 21, ncp_ioc_rw_t)


#define NCP_IOC_RMW             _IOWR(NCP_IOC, 22, ncp_ioc_rw_t)
#define NCP_IOC_BBW             _IOWR(NCP_IOC, 23, ncp_ioc_rw_t)
#define NCP_IOC_BSW             _IOWR(NCP_IOC, 24, ncp_ioc_rw_t)
#define NCP_IOC_BBF             _IOWR(NCP_IOC, 25, ncp_ioc_rw_t)
#define NCP_IOC_CSMBR           _IOWR(NCP_IOC, 26, ncp_ioc_rw_t)
#define NCP_IOC_CSMBW           _IOWR(NCP_IOC, 27, ncp_ioc_rw_t)
#define NCP_IOC_SW              _IOWR(NCP_IOC, 28, ncp_ioc_rw_t)

#define NCP_IOC_READ64          _IOWR(NCP_IOC, 29, ncp_ioc_rw_t)
#define NCP_IOC_WRITE64         _IOWR(NCP_IOC, 30, ncp_ioc_rw_t)

#define NCP_IOC_CBI_DMA_SYNC    _IOWR(NCP_IOC, 31, ncp_ioc_status_t)
#define NCP_IOC_TRANS_START     _IOWR(NCP_IOC, 32, ncp_ioc_status_t)
#define NCP_IOC_TRANS_ADD       _IOWR(NCP_IOC, 33, ncp_ioc_trans_add_t)
#define NCP_IOC_TRANS_END       _IOWR(NCP_IOC, 34, ncp_ioc_status_t)


/************* BEGIN EVENT MANAGER CODES **********************/
#define NCP_IOC_EVENT_CFG_START     _IO(NCP_IOC, 40)
#define NCP_IOC_EVENT_CFG_COMPLETE  _IO(NCP_IOC, 41)
#define NCP_IOC_EVENT_CFG_DESTROY   _IO(NCP_IOC, 42)
/************* END EVENT MANAGER CODES **********************/

/************* BEGIN VPM CODES **********************/

#define NCP_IOC_VPM_KERNEL_CONFIG   _IOWR(NCP_IOC, 43, ncp_vpm_kernel_info_t)
#define NCP_IOC_VPM_KERNEL_DESTROY  _IOWR(NCP_IOC, 44, ncp_vpm_kernel_info_t)

/************* END VPM CODES **********************/

/* BEGIN: New IOCTL codes for TASK I/O */

/* 50 is free, but reserved for Task I/O  */
/* 51 is free, but reserved for Task I/O  */
#define NCP_TASK_WAIT_FOR_INTERRUPT                     _IOWR(NCP_IOC, 52, ncp_task_interrupt_t)
#define NCP_TASK_INIT_KERNEL_SPINLOCKS                  _IO(NCP_IOC,   53)
#define NCP_TASK_REGISTER_GRP_INTERRUPTS                _IOWR(NCP_IOC, 54, ncp_ioc_u32_t)
#define NCP_TASK_DISPLAY_MEM_ATTTRIBUTES                _IOWR(NCP_IOC, 55, ncp_task_display_mem_atttributes_t)
#define NCP_IOC_TASK_TQS_STATE_MODIFY                   _IOWR(NCP_IOC, 56, ncp_task_tqs_state_modify_t)
#define NCP_IOC_TASK_INITIATE_SHUTDOWN                  _IO(NCP_IOC,   57)
/* 58 is free, but reserved for Task I/O  */
#define NCP_IOC_GSM_INFO_GET                            _IOWR(NCP_IOC, 59, ncp_ioc_gsm_info_t)
#define NCP_TASK_NCA_DO_KMODE_CFG                       _IOWR(NCP_IOC, 60, ncp_ioc_task_nca_kmode_cfg_t)
#define NCP_TASK_NCAV2_SET_DOMAIN_BUNDLE                _IOWR(NCP_IOC, 61, ncp_ioc_task_ncaV2_set_domain_bundle_t)
#define NCP_TASK_NCA_FINISH_KMODE_CFG                   _IOWR(NCP_IOC, 62, ncp_ioc_task_nca_kmode_finish_cfg_t)
#define NCP_TASK_NCAV2_KMODE_AVAILABLE_BLOCKS_GET       _IOWR(NCP_IOC, 63, ncp_ioc_task_ncaV2_kmode_blocks_t)

/* END: TASK I/O IOCTL Codes */


/* BEGIN: New IOCTL codes for EIOA */

#define NCP_IOC_EIOA_ALLOC                  _IOWR(NCP_IOC, 70, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_PORT_ALLOC             _IOWR(NCP_IOC, 71, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_PORT_ENABLE_GET        _IOWR(NCP_IOC, 72, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_PORT_ENABLE_SET        _IOWR(NCP_IOC, 73, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_QINQ_GET               _IOWR(NCP_IOC, 74, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_QINQ_SET               _IOWR(NCP_IOC, 75, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_AUTO_NEG_GET           _IOWR(NCP_IOC, 76, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_AUTO_NEG_SET           _IOWR(NCP_IOC, 77, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MAC_STATS_GET          _IOWR(NCP_IOC, 78, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_VLAN_CONFIG_GET        _IOWR(NCP_IOC, 79, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_VLAN_CONFIG_SET        _IOWR(NCP_IOC, 80, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_TAG_CONFIG_GET         _IOWR(NCP_IOC, 81, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_TAG_CONFIG_SET         _IOWR(NCP_IOC, 82, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_TAG_ENABLE_GET         _IOWR(NCP_IOC, 83, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_TAG_ENABLE_SET         _IOWR(NCP_IOC, 84, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_TAG_CONFIG_ENABLE_SET  _IOWR(NCP_IOC, 85, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MAC_TIMESTAMP_GET      _IOWR(NCP_IOC, 86, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MAC_SPEED_DUPLEX_GET   _IOWR(NCP_IOC, 87, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MAC_SPEED_DUPLEX_SET   _IOWR(NCP_IOC, 88, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_CRC_CONFIG_GET         _IOWR(NCP_IOC, 89, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_CRC_CONFIG_SET         _IOWR(NCP_IOC, 90, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_BROADCAST_FILTER_GET   _IOWR(NCP_IOC, 91, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_BROADCAST_FILTER_SET   _IOWR(NCP_IOC, 92, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_UNICAST_FILTER_GET     _IOWR(NCP_IOC, 93, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_UNICAST_FILTER_SET     _IOWR(NCP_IOC, 94, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_UNICAST_FILTER_ENABLE  _IOWR(NCP_IOC, 95, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MULTICAST_FILTER_GET   _IOWR(NCP_IOC, 96, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MULTICAST_FILTER_SET   _IOWR(NCP_IOC, 97, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MULTICAST_FILTER_ADD   _IOWR(NCP_IOC, 98, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MULTICAST_FILTER_DELETE _IOWR(NCP_IOC, 99, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MULTICAST_FILTER_ENABLE _IOWR(NCP_IOC, 100, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MAC_PAUSE_GET          _IOWR(NCP_IOC, 101, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MAC_PAUSE_SET          _IOWR(NCP_IOC, 102, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_VP_ID_GET              _IOWR(NCP_IOC, 103, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_VP_ID_SET              _IOWR(NCP_IOC, 104, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_SYNC                   _IOWR(NCP_IOC, 105, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_PORT_SYNC              _IOWR(NCP_IOC, 106, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MAC_ADDR_GET           _IOWR(NCP_IOC, 107, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_STAT_GET               _IOWR(NCP_IOC, 108, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_PHY_REG_GET            _IOWR(NCP_IOC, 109, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_PHY_REG_SET            _IOWR(NCP_IOC, 110, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_DESTROY                _IOWR(NCP_IOC, 111, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_AN_START               _IOWR(NCP_IOC, 112, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_AN_STOP                _IOWR(NCP_IOC, 113, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_TX_MAXPKT_SET          _IOWR(NCP_IOC, 114, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_TX_MAXPKT_GET          _IOWR(NCP_IOC, 115, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_RX_MAXPKT_SET          _IOWR(NCP_IOC, 116, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_RX_MAXPKT_GET          _IOWR(NCP_IOC, 117, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MAC_ADDR_SET           _IOWR(NCP_IOC, 118, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_LINK_STAT_GET          _IOWR(NCP_IOC, 119, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_LINK_STAT_GET_BLOCK    _IOWR(NCP_IOC, 120, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_OVRCLK_GET             _IOWR(NCP_IOC, 121, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_OVRCLK_SET             _IOWR(NCP_IOC, 122, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_CHAN_LOOPBACK_SET      _IOWR(NCP_IOC, 123, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MAC_TIMER_SHUTDOWN     _IOWR(NCP_IOC, 124, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_PORT_VP_GET            _IOWR(NCP_IOC, 125, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_PORT_VP_SET            _IOWR(NCP_IOC, 126, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_TS_MARKER_DELAY_GET    _IOWR(NCP_IOC, 127, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_TS_RESOLUTION_GET      _IOWR(NCP_IOC, 128, ncp_eioa_t5_t)

/* CONTINUE: New IOCTL codes for EIOA */

#define NCP_IOC_EIOA_MAC_TIMESTAMP_GET_POLL     _IOWR(NCP_IOC, 129, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_FEC_SET                    _IOWR(NCP_IOC, 130, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_FEC_GET                    _IOWR(NCP_IOC, 131, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_STATS_MAX_PKT_LENGTH_SET   _IOWR(NCP_IOC, 132, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_STATS_MAX_PKT_LENGTH_GET   _IOWR(NCP_IOC, 133, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_PROMISC_ENABLE	    	    _IOWR(NCP_IOC, 134, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_PROMISC_DISABLE	    	_IOWR(NCP_IOC, 135, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MAC_AN_TRACE               _IOWR(NCP_IOC, 136, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_IPP_PORT_VLAN_COUNT_UPDATE  _IOWR(NCP_IOC, 137, ncp_eioa_t5_t)

/* END: IOCTL codes for EIOA */


/************* BEGIN MDIO CODES **********************/

#define NCP_IOC_MDIO_WRITE                  _IOWR(NCP_IOC, 140, ncp_ioc_rw_t)
#define NCP_IOC_MDIO_READ                   _IOWR(NCP_IOC, 141, ncp_ioc_rw_t)

/************* END   MDIO CODES **********************/


/************* BEGIN CAT CODES **********************/

#define NCP_IOC_CAT_CONFIG                  _IOWR(NCP_IOC, 145, ncp_ioc_cat_config_t)
#define NCP_IOC_CAT_WRITE                   _IOWR(NCP_IOC, 146, ncp_ioc_cat_write_t)
#define NCP_IOC_CAT_WRITE_RAW               _IOWR(NCP_IOC, 147, ncp_ioc_cat_write_raw_t)
#define NCP_IOC_CAT_WRITE_FINALIZE          _IOWR(NCP_IOC, 148, ncp_ioc_cat_write_finalize_t)
#define NCP_IOC_CAT_READ                    _IOWR(NCP_IOC, 149, ncp_ioc_cat_read_t)
#define NCP_IOC_CAT_SIZE                    _IOWR(NCP_IOC, 150, ncp_ioc_cat_size_t)

/************* END   CAT CODES **********************/


/************* BEGIN PKA CODES **********************/

#define NCP_IOC_PKA_CONFIG                  _IOWR(NCP_IOC, 155, ncp_ioc_pka_fn_t)
#define NCP_IOC_PKA_DESTROY                 _IOWR(NCP_IOC, 156, ncp_ioc_pka_fn_t)
#define NCP_IOC_PKA_TRANS_START             _IOWR(NCP_IOC, 157, ncp_ioc_pka_trans_start_t)
#define NCP_IOC_PKA_TRANS_POLL              _IOWR(NCP_IOC, 158, ncp_ioc_pka_trans_poll_t)
#define NCP_IOC_PKA_TRANS_BLOCKING          _IOWR(NCP_IOC, 159, ncp_ioc_pka_trans_blocking_t)
#define NCP_IOC_PKA_TRANS_KILL              _IOWR(NCP_IOC, 160, ncp_ioc_pka_fn_t)
#define NCP_IOC_PKA_INFO                    _IOWR(NCP_IOC, 161, ncp_ioc_pka_info_t)
#define NCP_IOC_PKA_PROF_RETRIEVE           _IOWR(NCP_IOC, 162, ncp_ioc_pka_prof_retrieve_t)
#define NCP_IOC_PKA_PROF_INIT               _IOWR(NCP_IOC, 163, ncp_ioc_pka_fn_t)

/************* END   PKA CODES **********************/

/************* BEGIN PROFILER CODES **********************/

#define NCP_IOC_PROFILER_INIT               _IOWR(NCP_IOC, 170, ncp_ioc_status_t)
#define NCP_IOC_PROFILER_FREE               _IOWR(NCP_IOC, 171, ncp_ioc_status_t)
#define NCP_IOC_PROFILER_START              _IOWR(NCP_IOC, 172, ncp_ioc_status_t)
#define NCP_IOC_PROFILER_STOP               _IOWR(NCP_IOC, 173, ncp_ioc_status_t)
#define NCP_IOC_PROFILER_NUM_ENTRIES_GET    _IOWR(NCP_IOC, 174, ncp_ioc_profiler_num_entries_t)
#define NCP_IOC_PROFILER_ENTRIES_GET        _IOWR(NCP_IOC, 175, ncp_ioc_profiler_entries_t)
#define NCP_IOC_PROFILER_CLEAR              _IOWR(NCP_IOC, 176, ncp_ioc_status_t)


/************* END PROFILER CODES **********************/
/************* BEGIN SE CODES  **********************/

#define NCP_SE_FEM_WAIT_FOR_INTERRUPT       _IO(NCP_IOC, 180)

/************* END   SE CODES  **********************/

/************* BEGIN SYSMEM CODES  **********************/
#define NCP_SM_TREEMEM_ZQ_CALIB_START       _IOWR(NCP_IOC, 185, ncp_ioc_treemem_zq_cal_t)
#define NCP_SM_TREEMEM_ZQ_CALIB_STOP        _IOWR(NCP_IOC, 186, ncp_ioc_treemem_zq_cal_t)
/************* END  SYSMEM CODES  **********************/

/************* BEGIN TIMER CODES  **********************/

#define NCP_TIMER_WAIT_FOR_INTERRUPT       _IOWR(NCP_IOC, 190, ncp_ioc_timestamp_t)
#define NCP_TIMER_WAIT_FOR_CPU_INTERRUPT   _IOWR(NCP_IOC, 191, ncp_ioc_cpu_timer_info_t)
#define NCP_TIMER_SYNC_EXTERNAL            _IO(NCP_IOC, 192)

/************* END   TIMER CODES  **********************/

#define NCP_IOC_LBI_CTRL        _IOWR(NCP_IOC, 195, ncp_ioc_lbi_ctrl_t)
#define NCP_IOC_ALARM_IRQ_GET   _IOWR(NCP_IOC, 196, ncp_ioc_alarm_t)
#define NCP_IOC_ALARM_REG       _IOWR(NCP_IOC, 197, ncp_ioc_alarm_reg_t)

/******************************************************************************
* Macros & Procedure Prototypes
******************************************************************************/


#define NCP_EDEV_INIT() ncp_edev_bus_init()
#define NCP_EDEV_FINI() ncp_edev_bus_fini()

#define NCP_EDEV_BUS_CLEANUP(devNum) ncp_edev_bus_cleanup(devNum)

#define NCP_EDEV_BUS_FIND_DEVS()   ncp_edev_bus_find_devs()

#define NCP_EDEV_BUS_SETUP(devNum) ncp_edev_bus_setup(devNum)

#define NCP_EDEV_BUS_MAP_PAGE(dev, pageAddress, cpuAddress) \
    ncp_edev_bus_map_page(dev, pageAddress, cpuAddress)

#define NCP_EDEV_BUS_TO_PHYS(busAddr, devNum, barNum) \
    ncp_edev_bus_to_phys(busAddr, devNum, barNum)

int
ncp_edev_bus_init(void);

int
ncp_edev_bus_fini(void);

ncp_st_t
ncp_edev_bus_cleanup(int);

ncp_uint64_t
ncp_edev_bus_to_phys(
    ncp_uint64_t        busAddr,
    ncp_uint32_t        devNum,
    ncp_uint32_t        busNum);

int
ncp_edev_timer_add(
    void *pTimer,
    void *timerFunc,         
    void *timerFuncArg,     
    unsigned long duration);

int
ncp_edev_timer_mod(
    void *pTimer,
    unsigned long duration);

int
ncp_edev_timer_cancel(
    void *pTimer);
  
/* --- Function pointer assignment macros, used by the region map --- */
/* --- Don't forget to add prototype @ ncp_dev_pvt.h:NCP_DEV_IO_PROTOTYPE */
#define  __ncp_dev_direct_read                  ncp_dev_direct_read
#define  __ncp_dev_direct_write                 ncp_dev_direct_write
#define  __ncp_dev_indirect_read                ncp_dev_indirect_read
#define  __ncp_dev_indirect_write               ncp_dev_indirect_write
#define  __ncp_dev_bus_config_read              ncp_dev_bus_config_read
#define  __ncp_dev_bus_config_write             ncp_dev_bus_config_write
#define  __ncp_dev_sysmem_cr_read               ncp_dev_sysmem_cr_read
#define  __ncp_dev_sysmem_cr_write              ncp_dev_sysmem_cr_write
#define  __ncp_dev_sysmem_nic_read              ncp_dev_sysmem_nic_read
#define  __ncp_dev_sysmem_nic_write             ncp_dev_sysmem_nic_write
#define  __ncp_dev_paged_read                   ncp_dev_paged_read
#define  __ncp_dev_paged_write                  ncp_dev_paged_write
#define  __ncp_dev_coherent_read                ncp_dev_coherent_read
#define  __ncp_dev_coherent_write               ncp_dev_coherent_write
#define  __ncp_dev_internal_read                ncp_dev_internal_read
#define  __ncp_dev_internal_write               ncp_dev_internal_write
#define  __ncp_dev_mdio_read                    ncp_dev_mdio_read
#define  __ncp_dev_mdio_write                   ncp_dev_mdio_write
#define  __ncp_dev_i2cprot_read                 ncp_dev_i2cprot_read
#define  __ncp_dev_i2cprot_write                ncp_dev_i2cprot_write
#define  __ncp_dev_ntimc_read                   ncp_dev_ntimc_read
#define  __ncp_dev_ntimc_write                  ncp_dev_ntimc_write
#define  __ncp_dev_l2_indirect_read             ncp_dev_l2_indirect_read
#define  __ncp_dev_l2_indirect_write            ncp_dev_l2_indirect_write
#define  __ncp_dev_trace_indirect_read          ncp_dev_trace_indirect_read
#define  __ncp_dev_trace_indirect_write         ncp_dev_trace_indirect_write
#define  __ncp_dev_hss_phy_read                 ncp_dev_hss_phy_read
#define  __ncp_dev_hss_phy_write                ncp_dev_hss_phy_write
#define  __ncp_dev_lbi_read                     ncp_dev_lbi_read
#define  __ncp_dev_lbi_write                    ncp_dev_lbi_write
#define  __ncp_dev_apb2ser_indirect_read        ncp_dev_apb2ser_indirect_read
#define  __ncp_dev_apb2ser_indirect_write       ncp_dev_apb2ser_indirect_write

#ifdef __cplusplus
}
#endif

#endif /* _NCP_DEV_LINUX_H_ */
