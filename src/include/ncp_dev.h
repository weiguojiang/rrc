/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*! @file      ncp_dev.h
 *  @brief     Exported Device-level APIs.
 *  @addtogroup _device_APIs Device Level APIs
 *  Device-level APIs work with flat memory in each device, specifying addresses
 *  or ranges of addresses. The object-level APIs call these device-level APIs,
 *  and the host program can also call the device-level APIs directly.
 *
 *  @{
 */

#ifndef __NCP_DEV_H__
#define __NCP_DEV_H__

/*
 * ncp_dev.h
 *
 * This is the external header file for the NCP device driver.
 * This provides the function prototypes and associated definitions
 * needed for the user application to access the device APIs.
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Early / Forward type definitions of interest to the includes
 */
typedef void * ncp_dev_hdl_t;

/*
 * Includes
 */

#include "ncp_types.h"
#include "ncp_dev_config_regs.h"
#include "ncp_task.h"
#include "ncp_eioa.h"
#include "ncp_nodes.h"
/* #include "ncp_dev_cat.h" */


/* --- Maximum version string length --- */
#define NCP_DEV_MAX_VERSION_LENGTH  (41)

/* --- NCP I/O Flags --- */
#define NCP_IO_PIO                  (0x00000001)
#define NCP_IO_DMA                  (0x00000002)
#define NCP_IO_ZERO_COPY            (0x00000004)
#define NCP_IO_KERN_USER            (0x00000008)
#define NCP_IO_SYNC                 (0x00000010)
#define NCP_IO_TRANS                (0x00000020)
#define NCP_IO_COH_WRBACK           (0x00000040)
#define NCP_IO_COH_ATOMIC_TYPE      (0x00000080)
#define NCP_IO_I2C_SEEK             (0x00000100)
#define NCP_IO_IMC_WA               (0x00000200)
#define NCP_IO_BIG_ENDIAN           (0x00000400)
#define NCP_IO_LITTLE_ENDIAN        (0x00000800)
#define NCP_IO_ENDIAN               (0x00000c00)
#define NCP_IO_NONALIGN             (0x00001000)
#define NCP_IO_I2C_SMB              (0x00002000)
#define NCP_IO_I2C_10BIT            (0x00004000)
#define NCP_IO_CMEM_ZQ              (0x00008000)
#define NCP_IO_RESERVED             (0xFFFF0000)

/* --- NCA Config Ring Commands --- */
#define NCP_NCA_CMD_STATUS          (0x00000002)
#define NCP_NCA_CMD_CRBR            (0x00000004)
#define NCP_NCA_CMD_CRBW            (0x00000005)
#define NCP_NCA_CMD_CRSW            (0x00000006)
#define NCP_NCA_CMD_CRBF            (0x00000007)
#define NCP_NCA_CMD_CRRMW           (0x00000008)
#define NCP_NCA_CMD_CRBBW           (0x00000009)
#define NCP_NCA_CMD_CRBSW           (0x0000000A)
#define NCP_NCA_CMD_CRBBF           (0x0000000B)
#define NCP_NCA_CMD_SMBR            (0x0000000C)
#define NCP_NCA_CMD_SMBW            (0x0000000D)
#define NCP_NCA_CMD_CSMBR           (0x0000000E)
#define NCP_NCA_CMD_CSMBW           (0x0000000F)

#define NCP_NCA_NUM_IO_CMDS         12

#define NCP_CFG_CMD_BUF_SIZE    (sizeof(ncp_coherent_sysmem_io_t))

#define NCP_SM_INTR_BITS            20

/* --- NCP Trace Level Definitions --- */
#define NCP_MSG_NONE                (0x00000000)
#define NCP_MSG_INFO                (0x00000001)
#define NCP_MSG_ERROR               (0x00000002)
#define NCP_MSG_ENTRY               (0x00000004)
#define NCP_MSG_EXIT                (0x00000008)
#define NCP_MSG_CALL                (NCP_MSG_ENTRY | NCP_MSG_EXIT)
#define NCP_MSG_IOR                 (0x00000010)
#define NCP_MSG_IOW                 (0x00000020)
#define NCP_MSG_IORW                (NCP_MSG_IOR | NCP_MSG_IOW)
#define NCP_MSG_MEM                 (0x00000040)
#define NCP_MSG_MDIO                (0x00000080)
#define NCP_MSG_DEBUG_MEM           (0x10000000)
#define NCP_MSG_DEBUG_IO            (0x20000000)
#define NCP_MSG_DEBUG               (0x40000000)
#define NCP_MSG_INTR                (0x80000000)
#define NCP_MSG_ALL                 (0xFFFFFFFF)

/* --- NCP Device Instance Flags --- */
#define NCP_DEV_FLAGS_MASK          (0x0000ffff) /* driver flags */
#define NCP_USER_FLAGS_MASK         (0xffff0000) /* user/API flags */

#define NCP_DEV_BUS_PCI             (0x00000001)
#define NCP_DEV_BUS_SRIO            (0x00000002)
#define NCP_DEV_BUS_PLB             (0x00000004)
#define NCP_DEV_BUS_SRIOEP          (0x00000008)
#define NCP_DEV_BUS_PLX				(0x00000010)
#define NCP_DEV_BUS_ACE				(0x00000020)
#define NCP_DEV_BUS_HW              (0x0000003F)  /* mask for all h/w adaptors*/
#define NCP_DEV_BUS_INTERNAL        ( NCP_DEV_BUS_PLB | NCP_DEV_BUS_ACE )  /* mask for all interal cores */
                                                  /* add'l adapters may be
                                                   * enumerated in the holes
                                                   * in the above listing. */
#define NCP_DEV_BUS_FBRS            (0x00000100)
#define NCP_DEV_BUS_SOCKET          (0x00000200)
#define NCP_DEV_IS_ASIC             (0x00000400)
#define NCP_DEV_CONFIGURED          (0x00000800)
#define NCP_DEV_ISR_ENABLED         (0x00001000)
#define NCP_DEV_TRANS_BUSY          (0x00002000)


/*
 * The flag bits masked by NCP_DEV_SCRATCHPAD_MASK
 * are also stored in the scratch-pad register.
 * This makes them persistant across a driver reload,
 * so that the prior h/w state may be restored.
 */
#define NCP_DEV_SCRATCHPAD_MASK     (0xffff0000)
#define NCP_CFG_LOAD_COMPLETE       (0x00010000)
#define NCP_DOMAIN_ID_SCRATCH_VALID (0x00020000)
#define NCP_DOMAIN_ID_SCRATCH_BITS  (0x003c0000)
#define NCP_DOMAIN_ID_SCRATCH_SHIFT (18)


/* --- NCP Device Handle --- */
#define NCP_DEV_INVALID_HANDLE  ((void *)-1)


/* --- NCP Device Info Structure --- */
typedef ncp_rev_id_t ncp_version_t;

typedef struct {
    ncp_uint8_t ndevs;
    ncp_uint32_t status[NCP_MAX_DEVS];
} ncp_dev_info_t;

   
/* --- NCP Device Statistics Structure --- */

typedef struct {
    ncp_uint32_t count;
    ncp_uint32_t nBytes;
    ncp_uint32_t minSize;
    ncp_uint32_t maxSize;
} ncp_dev_io_stats_t;


typedef struct {
    ncp_uint32_t count;
    ncp_uint32_t bytes;
    ncp_uint32_t minSize;
    ncp_uint32_t maxSize;
    ncp_uint32_t queueFullCount;
    ncp_uint32_t maxQueueDepth;
} ncp_dev_pdu_stats_t;

typedef struct {
    ncp_uint32_t timeout;
    ncp_uint32_t decode;
    ncp_uint32_t node;
    ncp_uint32_t wrongAck;
    ncp_uint32_t ackTimeout;
    ncp_uint32_t unclaimedHeader;
    ncp_uint32_t ring0Parity;
    ncp_uint32_t ring1Parity;
    ncp_uint32_t ring2Parity;
    ncp_uint32_t unknown;
} ncp_dev_pio_err_t;

typedef struct {
    ncp_uint32_t    chipType;
    ncp_uint32_t    busAdaptor;

    /*
     * NCP device I/O statistics.
     */
    ncp_dev_io_stats_t pio[NCP_NCA_NUM_IO_CMDS];
    ncp_dev_io_stats_t dma[NCP_NCA_NUM_IO_CMDS];

    ncp_uint32_t dma_io8_delay_cnt;
    ncp_uint32_t dma_io32_delay_cnt;

    ncp_dev_pio_err_t  pio_err;
    ncp_uint32_t imcWorkaroundCnt;
    ncp_uint32_t imcWorkaroundFailed;

    /* PDU recv statistics */
    ncp_dev_pdu_stats_t pduRecv;

    /* PDU send statistics */
    ncp_dev_pdu_stats_t pduSend;

    /* Interrupt statistics */
    ncp_uint32_t spuriousIntCnt;

    /* sysmem interrupt statistics */
    ncp_uint32_t sysmem_intr_bits[NCP_SYSMEM_NUM_NODES][NCP_SM_INTR_BITS];

} ncp_dev_stats_t;

/* 
 * GSM (Globally Shared Memory) and LCM config attibutes
 */
typedef struct ncp_dev_gsm_info_s {
    ncp_uint32_t    cookie;
    NCP_DECLARE_POINTER(ncp_uint8_t, hwGSM_uVA);
    NCP_DECLARE_POINTER(ncp_uint8_t, hwGSM_kernVA);
    ncp_uint32_t    hwGSM_size;
    NCP_DECLARE_RAW_ADDR(hwGSM_currOffset);     /* how far into hwGSM>? - used by alloc */    
    ncp_uint64_t    hwGSM_PA;

    NCP_DECLARE_POINTER(ncp_uint8_t, LCM_uVA);
    NCP_DECLARE_POINTER(ncp_uint8_t, LCM_kernVA);
    ncp_uint32_t    LCM_size;
    ncp_uint64_t    LCM_PA;

    ncp_uint64_t    axiDmaBase;
    ncp_uint64_t    busDmaOffset;
    ncp_bool_t      useInterrupts;
} NCP_COMPAT_PACKED ncp_dev_gsm_info_t;

/* --- NCP PDU Vector Structure --- */
typedef struct {
    void * pduBuf;
    ncp_uint32_t pduBufSize;
} ncp_pdu_vec_t;


/* --- Device Target Access Map --- */
#if 0  /* Use struct that matches that used in the auto-generated RDL output include files */
typedef struct {
    ncp_uint32_t start;
    ncp_uint32_t end;
    ncp_uint8_t  rw;
} ncp_access_map_t;
#else
typedef struct ncp_access_map_s {
    ncp_uint64_t    begin;
    ncp_uint64_t    end;
    ncp_int32_t     word_size_in_bytes;
    ncp_int32_t     access_size_in_words;
} ncp_access_map_t;
#endif
/* --- Device Node/Target Address Space Map --- */
typedef struct {
    ncp_uint16_t node;
    ncp_uint16_t target;
    ncp_uint32_t size;
    ncp_access_map_t * accessMap;
} ncp_address_map_t;



/* --- NCP Device Level APIs --- */

/*! \defgroup devIoStatus Device Level I/O status codes *
 *
 * These error codes may be returned by any of the device
 * level I/O APIs.
 *
 * The following errors are detected by software as part of
 * the API parameter validation:
 * @return
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_DEV_INVALID_BUFFER
 *     \li ::NCP_ST_DEV_INVALID_FLAGS
 *     \li ::NCP_ST_DEV_INVALID_REGION_ID
 *     \li ::NCP_ST_DEV_INVALID_ACCESS
 *     \li ::NCP_ST_DEV_INVALID_PAGE_ACCESS
 *     \li ::NCP_ST_DEV_INVALID_WIDTH
 *     \li ::NCP_ST_DEV_INVALID_OFFSET
 *     \li ::NCP_ST_DEV_INVALID_COMMAND
 *     \li ::NCP_ST_DEV_UNALIGNED_OFFSET
 *
 * The following errors indicate that an attempted PIO transfer
 * has failed for non-specific reasons. 
 *     \li ::NCP_ST_DEV_IO_ERROR
 *     \li ::NCP_ST_DEV_PIO_FAILED
 *     \li ::NCP_ST_DEV_PIO_SW_TIMEOUT
 *
 * The following errors inidicate the cause of the PIO failure as 
 * reported by the NCA engine. If driver tracing is enabled there
 * should be additional details about the error in the kernel log.
 * @return
 *     \li ::NCP_ST_DEV_PIO_TIMEOUT_ERR
 *     \li ::NCP_ST_DEV_PIO_DECODE_ERR
 *     \li ::NCP_ST_DEV_PIO_NODE_ERR
 *     \li ::NCP_ST_DEV_PIO_WRONG_ACK_ERR
 *     \li ::NCP_ST_DEV_PIO_ACK_TIMEOUT_ERR
 *     \li ::NCP_ST_DEV_PIO_UNCLAIMED_HDR_ERR
 *     \li ::NCP_ST_DEV_PIO_RING0_PARITY_ERR
 *     \li ::NCP_ST_DEV_PIO_RING1_PARITY_ERR
 *     \li ::NCP_ST_DEV_PIO_RING2_PARITY_ERR
 *
 * Note that the reporting of PIO errors differs between read and write
 * operations. Since write operations are posted, the write API can
 * return to the user before the operation has completed and the final
 * status is known. If the PIO operation fails the error will be detected
 * and reported by the next device I/O API call. Since read operations 
 * must always complete they always return the true status of the operation,
 * unless they follow a failed write. If driver tracing is enabled it will
 * indicate the actual operation for which the error occurred. 
 */

/*!
 * @fn ncp_st_t ncp_dev_init(void)
 * @brief Initializes the device driver.
 *        This API is available only in kernel mode.  
 * @returns Status code indicating success or failure \link ncp_st_t \endlink
 */

NCP_API ncp_st_t ncp_dev_init(void);

/*!
 * @fn ncp_st_t ncp_dev_fini(void)
 * @brief Releases all system resources that are held by the device level API.
 *        This API is available only in kernel mode.  
 * @returns Status code indicating success or failure \link ncp_st_t \endlink
 */

NCP_API ncp_st_t ncp_dev_fini(void);

/*!
 * @fn ncp_st_t ncp_dev_open( ncp_uint32_t devNum, ncp_uint32_t flags,
 *                            ncp_dev_hdl_t *devHdl)
 * @param devNum  IN: Device instance number
 * @param flags   IN: Open flags (not used sed to zero)
 * @param devHdl  OUT: Return location for NCP handle
 * @brief Converts an NCP device instance number into a device handle for
 *        use in subsequent device driver calls.
 *
 * Valid values for the device instance number range from
 * zero to [N . 1], where N represents the total number of NCP devices
 * in the system. NCP devices are numbered based on the order in which
 * they are found during the system bus enumeration process. Upon
 * successful completion, the NCP device handle is returned into the
 * memory location specified by devHdl.
 */

NCP_API ncp_st_t
ncp_dev_open(
    ncp_uint32_t devNum,
    ncp_uint32_t flags,
    ncp_dev_hdl_t *devHdl);

/*!
 * @fn ncp_st_t ncp_config_attach( ncp_uint32_t devNum, ncp_hdl_t *ncpHdl)
 * @param devNum  IN: Device instance number
 * @param ncpHdl  OUT: Return location for NCP handle
 * @brief Converts an NCP device instance number into a NCP object handle for
 *        use in subsequent kernel resident API calls.
 *
 * Valid values for the device instance number range from
 * zero to [N . 1], where N represents the total number of NCP devices
 * in the system. 
 * Upon successful completion, the NCP device handle is returned into the
 * memory location specified by devHdl.
 */
NCP_API ncp_st_t
ncp_config_attach(
    ncp_uint32_t devNum,
    ncp_hdl_t *ncpHdl);

/*!
 * @fn ncp_st_t ncp_dev_close( ncp_dev_hdl_t devHdl);
 * @param devHdl IN: Device handle
 * @brief Frees the specified device handle.
 */

NCP_API ncp_st_t
ncp_dev_close(
    ncp_dev_hdl_t devHdl);


 /*!
 * @fn ncp_dev_atomic_enable_nca_rx_ints(ncp_dev_hdl_t devHdl, 
 *                          ncp_uint8_t grp,
 *                          int qCount,
 *                          ncp_uint8_t *ncaQueueIDs);
 * @return Status code indicating success or failure \link ncp_st_t \endlink
 * @brief Function to force nca rx interrupts to be enabled for the 
 * specified queue group.    
 * This API should only be used by NAPI/netDriver clients. 
 * This API is available only in kernel mode.
 *
 *        This API is available only in kernel mode. 
 * @param devHdl    - IN: NCP device handle.
 * @param grp       - nca pcq queue group
 */
NCP_API ncp_st_t
ncp_dev_atomic_enable_nca_rx_ints(ncp_dev_hdl_t devHdl, 
                           ncp_uint8_t grp,
                           int qCount,
                           ncp_uint8_t *ncaQueueIDs);


 /*!
 * @fn ncp_st_t ncp_dev_enable_nca_rx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp);
 * @return Status code indicating success or failure \link ncp_st_t \endlink
 * @brief Function to force nca rx interrupts to be enabled for the 
 * specified queue group.    
 * This API should only be used by NAPI clients. 
 * This API is available only in kernel mode.
 *
 *        This API is available only in kernel mode. 
 * @param devHdl    - IN: NCP device handle.
 * @param grp       - nca pcq queue group
 */
NCP_API ncp_st_t
ncp_dev_enable_nca_rx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp);

/*!
 * @fn ncp_st_t ncp_dev_disable_nca_rx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp);
 * @return Status code indicating success or failure \link ncp_st_t \endlink
 * @brief Function to force nca rx interrupts to be disabled for the 
 * specified queue group.   
 * This API should only be used by NAPI clients. 
 * This API is available only in kernel mode.

 *
 *        This API is available only in kernel mode.
 * @param devHdl    - IN: NCP device handle.
 * @param grp       - nca pcq queue group
 */
NCP_API ncp_st_t 
ncp_dev_disable_nca_rx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp);


/*!
 * @fn ncp_st_t ncp_dev_enable_nca_tx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp);
 * @return Status code indicating success or failure \link ncp_st_t \endlink
 * @brief Function to force nca tx interrupts to be enabled for the 
 * specified queue group.   
 * This API should only be used by NAPI clients. 
 * This API is available only in kernel mode.
 * @param devHdl    - IN: NCP device handle.
 * @param grp       - nca pcq queue group
 */
NCP_API ncp_st_t
ncp_dev_enable_nca_tx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp);

/*!
 * @fn ncp_st_t ncp_dev_disable_nca_tx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp);
 * @return Status code indicating success or failure \link ncp_st_t \endlink
 * @brief Function to force nca tx interrupts to be disabled for the
 * specified queue group.   
 * This API should only be used by NAPI clients. 
 * This API is available only in kernel mode.
 * @param devHdl    - IN: NCP device handle.
 * @param grp       - nca pcq queue group
 */
NCP_API ncp_st_t 
ncp_dev_disable_nca_tx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp);

/*!
 * @fn ncp_st_t ncp_dev_enable_nca_task_completion_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp);
 * @return Status code indicating success or failure \link ncp_st_t \endlink
 * @brief Function to force nca task completion interrupts to be enabled for 
 * the pecified queue group.   
 * This API should only be used by NAPI clients. 
 * This API is available only in kernel mode.
 * @param devHdl    - IN: NCP device handle.
 * @param grp       - nca pcq queue group
 */
NCP_API ncp_st_t
ncp_dev_enable_nca_task_completion_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp);

/*!
 * ncp_st_t ncp_dev_disable_nca_task_completion_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp);
 * @return Status code indicating success or failure \link ncp_st_t \endlink
 * @brief Function to force nca task completion interrupts to be disabled 
 * for the specified queue group. 
 * This API should only be used by NAPI clients. 
 * This API is available only in kernel mode. 

 *
 * @param devHdl    - IN: NCP device handle.
 * @param grp       - nca pcq queue group
 */
NCP_API ncp_st_t 
ncp_dev_disable_nca_task_completion_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp);



/*!
 * @fn ncp_st_t ncp_dev_read8( ncp_dev_hdl_t   devHdl, ncp_region_id_t regionId,
 *                             ncp_uint64_t    offset, ncp_uint8_t    *value)
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param value    OUT: Return location for read data
 *
 * @brief Reads an 8-bit value from the specified NCP device address space region
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_read8(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint8_t    *value);

/*!
 * @fn ncp_st_t ncp_dev_read16( ncp_dev_hdl_t  devHdl, ncp_region_id_t regionId,
 *                             ncp_uint64_t    offset, ncp_uint16_t    *value)
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param value    OUT: Return location for read data
 *
 * @brief Reads a 16-bit value from the specified NCP device address space region
 *
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_read16(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint16_t   *value);

/*!
 * @fn ncp_st_t ncp_dev_read32( ncp_dev_hdl_t  devHdl, ncp_region_id_t regionId,
 *                             ncp_uint64_t    offset, ncp_uint32_t    *value)
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param value    OUT: Return location for read data
 *
 * @brief Reads a 32-bit value from the specified NCP device address space region
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_read32(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint32_t   *value);
/*!
 * @fn ncp_st_t ncp_dev_read64( ncp_dev_hdl_t  devHdl, ncp_region_id_t regionId,
 *                             ncp_uint64_t    offset, ncp_uint64_t    *value)
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param value    OUT: Return location for read data
 *
 * @brief Reads a 64-bit value from the specified NCP device address space region
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_read64(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint64_t   *value);

/*!
 * @fn ncp_st_t ncp_dev_write8( ncp_dev_hdl_t  devHdl, ncp_region_id_t regionId,
 *                              ncp_uint64_t   offset, ncp_uint8_t     value)
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param value    IN: Write data
 *
 * @brief Writes an 8-bit value to the specified NCP device address space region
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_write8(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint8_t     value);

/*!
 * @fn ncp_st_t ncp_dev_write16( ncp_dev_hdl_t devHdl, ncp_region_id_t regionId,
 *                               ncp_uint64_t  offset, ncp_uint16_t    value)
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param value    IN: Write data
 *
 * @brief Writes an 16-bit value to the specified NCP device address space region
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_write16(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint16_t    value);

/*!
 * @fn ncp_st_t ncp_dev_write32( ncp_dev_hdl_t devHdl, ncp_region_id_t regionId,
 *                               ncp_uint64_t  offset, ncp_uint32_t     value)
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param value    IN: Write data
 *
 * @brief Writes an 32-bit value to the specified NCP device address space region
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_write32(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint32_t    value);

/*!
 * @fn ncp_st_t ncp_dev_write64( ncp_dev_hdl_t devHdl, ncp_region_id_t regionId,
 *                               ncp_uint64_t  offset, ncp_uint64_t     value)
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param value    IN: Write data
 *
 * @brief Writes an 64-bit value to the specified NCP device address space region
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_write64(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint64_t    value);

/*!
 * @fn ncp_st_t ncp_dev_block_read8( ncp_dev_hdl_t  devHdl, ncp_region_id_t regionId,
 *                      ncp_uint64_t   offset, ncp_uint8_t *buffer,
 *                      ncp_uint32_t   count,  ncp_uint32_t  flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param buffer  OUT: Return location for read data
 * @param count    IN: Number of 8-bit words to read
 * @param flags    IN: Operational control flags.
 *
 * @brief Reads a block of 8-bit values from the specified device address space
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_block_read8(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint8_t    *buffer,
    ncp_uint32_t    count,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_block_read16(ncp_dev_hdl_t devHdl,
 *                                   ncp_region_id_t regionId,
 *                                   ncp_uint64_t  offset,
 *                                   ncp_uint16_t *buffer,
 *                                   ncp_uint32_t  count,
 *                                   ncp_uint32_t  flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param buffer  OUT: Return location for read data
 * @param count    IN: Number of 16-bit words to read
 * @param flags    IN: Operational control flags.
 *
 * @brief Reads a block of 16-bit values from the specified device address space
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_block_read16(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint16_t   *buffer,
    ncp_uint32_t    count,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_block_read32( ncp_dev_hdl_t   devHdl,
 *                                    ncp_region_id_t regionId,
 *                                    ncp_uint64_t    offset,
 *                                    ncp_uint32_t   *buffer,
 *                                    ncp_uint32_t    count,
 *                                    ncp_uint32_t    flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param buffer  OUT: Return location for read data
 * @param count    IN: Number of 32-bit words to read
 * @param flags    IN: Operational control flags.
 *
 * @brief Reads a block of 32-bit values from the specified device address space
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_block_read32(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint32_t   *buffer,
    ncp_uint32_t    count,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_block_read64( ncp_dev_hdl_t   devHdl,
 *                                    ncp_region_id_t regionId,
 *                                    ncp_uint64_t    offset,
 *                                    ncp_uint64_t   *buffer,
 *                                    ncp_uint32_t    count,
 *                                    ncp_uint32_t    flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param buffer  OUT: Return location for read data
 * @param count    IN: Number of 64-bit value to read
 * @param flags    IN: Operational control flags.
 *
 * @brief Reads a block of 32-bit values from the specified device address space
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_block_read64(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint64_t   *buffer,
    ncp_uint32_t    count,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_block_write8( ncp_dev_hdl_t  devHdl, ncp_region_id_t regionId,
 *                       ncp_uint64_t   offset, ncp_uint8_t *buffer,
 *                       ncp_uint32_t   count,  ncp_uint32_t  flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param buffer  OUT: Return location for write data
 * @param count    IN: Number of 8-bit words to read
 * @param flags    IN: Operational control flags.
 *
 * @brief Writes a block of 8-bit values to the specified device address space
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_block_write8(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint8_t    *buffer,
    ncp_uint32_t    count,
    ncp_uint32_t    flags);


/*!
 * @fn ncp_st_t ncp_dev_block_write16( ncp_dev_hdl_t  devHdl, ncp_region_id_t regionId,
 *                        ncp_uint64_t   offset, ncp_uint16_t *buffer,
 *                        ncp_uint32_t   count,  ncp_uint32_t  flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param buffer  OUT: Return location for write data
 * @param count    IN: Number of 16-bit words to read
 * @param flags    IN: Operational control flags.
 *
 * @brief Writes a block of 16-bit values to the specified device address space
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_block_write16(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint16_t   *buffer,
    ncp_uint32_t    count,
    ncp_uint32_t    flags);


/*!
 * @fn ncp_st_t ncp_dev_block_write32( ncp_dev_hdl_t  devHdl, ncp_region_id_t regionId,
 *                        ncp_uint64_t   offset, ncp_uint32_t *buffer,
 *                        ncp_uint32_t   count,  ncp_uint32_t  flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param buffer  OUT: Return location for write data
 * @param count    IN: Number of 32-bit words to read
 * @param flags    IN: Operational control flags.
 *
 * @brief Writes a block of 32-bit values to the specified device address space
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_block_write32(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint32_t   *buffer,
    ncp_uint32_t    count,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_block_write64( ncp_dev_hdl_t  devHdl, ncp_region_id_t regionId,
 *                        ncp_uint64_t   offset, ncp_uint64_t *buffer,
 *                        ncp_uint32_t   count,  ncp_uint32_t  flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param buffer  OUT: Return location for write data
 * @param count    IN: Number of 64-bit values to read
 * @param flags    IN: Operational control flags.
 *
 * @brief Writes a block of 32-bit values to the specified device address space
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_block_write64(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint64_t   *buffer,
    ncp_uint32_t    count,
    ncp_uint32_t    flags);


/*!
 * @fn ncp_st_t ncp_dev_block_fill( ncp_dev_hdl_t  devHdl, ncp_region_id_t regionId,
 *                     ncp_uint64_t   offset, ncp_fill_t *ncp_fill_p,
 *                     ncp_uint32_t  flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param ncp_fill_p   IN: pointer to fill command buffer.
 * @param flags    IN: Operational control flags.
 *
 * @brief Fills a specified device address space with a constant value.
 *
 * For config ring targets the fill operation will use the NCA engine
 * Config Ring Block Fill (CRBF) command. This allows the user to 
 * specify the width of the fill pattern and address stride for each
 * successive write. 
 *
 * For non config ring targets only a simple 32-bit fill is supported.
 *
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_block_fill(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset64,
    ncp_fill_t     *ncp_fill_p,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_read_modify_write(ncp_dev_hdl_t devHdl, ncp_region_id_t regionId,
 *                               ncp_uint64_t  offset, ncp_rmw_t *ncp_rmw_p,
 *                               ncp_uint32_t  flags)
 *
 * @param devHdl    IN: Device handle
 * @param regionId  IN: Node/target address
 * @param offset    IN: Node/target offset
 * @param ncp_rmw_p IN: pointer to read-modify-write(RMW) structure.
 * @param flags     IN: Operational control flags.
 *
 * @brief Performs an atomic Read Modify Write command on the specified 
 * region offset. 
 *
 * For each offset the user specifies a value/mask pair. The mask 
 * indicates which bits of the register are to be modified.
 *
 * This command is only supported for real config ring targets (nodeId <= 0xff).
 *
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_read_modify_write(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset64,
    ncp_rmw_t      *ncp_rmw_p,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_scatter_write(ncp_dev_hdl_t devHdl,
 *                                        ncp_region_id_t regionId,
 *                                        ncp_crsw_t   *crsw_p,
 *                                        ncp_uint32_t  flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param crsw_p   IN: pointer to CRSW structure.
 * @param flags    IN: Operational control flags.
 *
 * @brief Performs a 32-bit scatter write operation.
 *
 * The scatter buffer provides a set of address/data pairs, and 
 * each data value will be written to the associated address. 
 *
 * This command is only supported for real config ring targets (nodeId <= 0xff).
 *
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_scatter_write(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_crsw_t     *crsw_p,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_broadcast_block_write(ncp_dev_hdl_t devHdl,
 *                                   ncp_region_id_t regionId,
 *                                   ncp_uint64_t  offset, ncp_crbbw_t *crbbw_p,
 *                                   ncp_uint32_t flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param buffer   IN: pointer to CRBBW structure.
 * @param flags    IN: Operational control flags.
 *
 * @brief Performs a broadcast block write of a 64-bit value
 *
 * The write operation will be broadcast to each node in the 
 * specified nodeVector. They will all use the target specified
 * in the regionId. The node specified in the regionId should 
 * be one of the nodes in the nodeVector.
 *
 * For example, to broadcast to regions 0.0, 2.0, 4.0, and 6.0,
 * one would set the nodeVector to 0x00000055, and set the
 * regionId to 0.0. 
 *
 * This command is only supported for real config ring targets (nodeId <= 0xff).
 *
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_broadcast_block_write(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset64,
    ncp_crbbw_t    *crbbw_p,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_broadcast_scatter_write(
 *                                     ncp_dev_hdl_t devHdl,
 *                                     ncp_region_id_t regionId,
 *                                     ncp_crbsw_t *crbsw_p,
 *                                     ncp_uint32_t flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param buffer   IN: pointer to CRBSW structure
 * @param flags    IN: Operational control flags.
 *
 * @brief Perform a broadcast scatter write of 64-bit values.
 *
 * The scatter buffer provides a set of address/data pairs, and 
 * each data value will be written to the associated address. 
 *
 * Each write operation will be broadcast to each node in the 
 * specified nodeVector. They will all use the target specified
 * in the regionId. The node specified in the regionId should 
 * be one of the nodes in the nodeVector.
 *
 * This command is only supported for real config ring targets (nodeId <= 0xff).
 *
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_broadcast_scatter_write(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_crbsw_t    *crbsw_p,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_broadcast_block_fill(
 *                                           ncp_dev_hdl_t   devHdl,
 *                                           ncp_region_id_t regionId,
 *                                           ncp_uint64_t    offset64,
 *                                           ncp_fill_t     *ncp_fill_p,
 *                                           ncp_uint32_t    flags)
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param buffer   IN: pointer to ncp_fill_t structure
 * @param flags    IN: Operational control flags.
 *
 * @brief Perform a broadcast block fill of a 64-bit value. 
 *
 * The broadcast fill operation does not support variable pattern
 * widths, it is always a 64-bit operation. 
 *
 * This command is only supported for real config ring targets (nodeId <= 0xff).
 *
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_broadcast_block_fill(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset64,
    ncp_fill_t     *ncp_fill_p,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_coherent_sysmem_read(ncp_dev_hdl_t devHdl,
 *                                  ncp_region_id_t regionId,
 *                                  ncp_uint64_t address,
 *                                  ncp_uint8_t *buffer,
 *                                  ncp_uint32_t  count,
 *                                  ncp_uint32_t  xferWidth,
 *                                  ncp_uint32_t  flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Engine Node/target
 * @param address  IN: System Memory Address
 * @param buffer  OUT: read data buffer
 * @param count    IN: number of bytes to read
 * @param xferWidth IN: transfer width in bytes
 * @param flags    IN: Operational control flags.
 *
 * @brief perform a system memory read that is coherent with respect
 * to the engine specified by regionId. 
 *
 * Coherent sysmem access is only supported by the MPP State Engine, 
 * MTM, SPP, and DPI, and the maximum transfer size is one cache line
 * (256 bytes). 
 *
 * There are two bits in the 'flags' argument specific to the coherent
 * sysmem access: NCP_IO_COH_ATOMIC_TYPE and NCP_IO_COH_WRBACK. These
 * are used to set the atomic_type and wrback bits in the atomic update
 * control register. See the ACP register programming guide for details.
 *
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_coherent_sysmem_read(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    address,
    ncp_uint8_t    *buffer,
    ncp_uint32_t    count,
    ncp_uint32_t    xferWidth,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_coherent_sysmem_write(ncp_dev_hdl_t devHdl,
 *                                   ncp_region_id_t regionId,
 *                                   ncp_uint64_t  address,
 *                                   ncp_uint8_t  *buffer,
 *                                   ncp_uint32_t count,
 *                                  ncp_uint32_t  xferWidth,
 *                                   ncp_uint32_t  flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Engine Node/target
 * @param address  IN: System Memory address
 * @param buffer   IN: write data
 * @param count    IN: number of bytes to write
 * @param xferWidth IN: transfer width in bytes
 * @param flags    IN: Operational control flags.
 *
 * @brief perform a system memory write that is coherent with respect
 * to the engine specified by regionId. 
 *
 * Coherent sysmem access is only supported by the MPP State Engine, 
 * MTM, SPP, and DPI, and the maximum transfer size is one cache line
 * (256 bytes). 
 *
 * There are two bits in the 'flags' argument specific to the coherent
 * sysmem access: NCP_IO_COH_ATOMIC_TYPE and NCP_IO_COH_WRBACK. These
 * are used to set the atomic_type and wrback bits in the atomic update
 * control register. See the ACP register programming guide for details.
 *
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_coherent_sysmem_write(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    address,
    ncp_uint8_t    *buffer,
    ncp_uint32_t    count,
    ncp_uint32_t    xferWidth,
    ncp_uint32_t    flags);


/*!
 * @fn ncp_st_t ncp_dev_info( ncp_dev_info_t *devInfo)
 * @param devInfo  OUT: Return location for device info
 *
 * @brief Retrieves system level device information.
 */

NCP_API ncp_st_t ncp_dev_info(
    ncp_dev_info_t *devInfo);

/*!
 * @fn ncp_st_t ncp_dev_info_get( ncp_dev_hdl_t devHdl, ncp_uint32_t *flags)
 * @brief Returns the current flags for a single NCP instance.
 * @param devHdl    IN: Device handle.
 * @param devInfo  OUT: Return location for device info
 *
 */

NCP_API ncp_st_t ncp_dev_info_get(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t *flags);

/*!
 * @fn ncp_st_t ncp_dev_info_set( ncp_dev_hdl_t devHdl, ncp_uint32_t flags)
 * @param devHdl    IN: Device handle.
 * @param flags    OUT: New flags for device.
 *
 * Sets the flags for a single NCP instance.
 */

NCP_API ncp_st_t ncp_dev_info_set(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t flags);

/*!
 * @fn ncp_st_t ncp_dev_hw_version_get( ncp_dev_hdl_t devHdl,
 *                                      ncp_version_t *version)
 * @brief Returns the version of the hardware device associated with devHdl.
 *        See NCP_CHIP_... constants for examples.
 * @param devHdl   IN: Device handle
 * @param version OUT: Return location for dev version
 *
 */

NCP_API ncp_st_t ncp_dev_hw_version_get(
    ncp_dev_hdl_t devHdl,
    ncp_version_t *version);

/*!
 * @fn ncp_st_t ncp_dev_stats( ncp_dev_hdl_t devHdl, ncp_dev_stats_t *devStats)
 * @param devHdl    IN: Device handle
 * @param devStats OUT: Return location for device stats
 *
 * @brief retrieve device driver statistics
 */

NCP_API ncp_st_t ncp_dev_stats(
    ncp_dev_hdl_t devHdl,
    ncp_dev_stats_t *devStats);

/*!
 * @fn ncp_st_t ncp_dev_version( char *version)
 * @param version OUT: Return location for version info
 *
 * @brief returns the device driver software version (release ID).
 */

NCP_API ncp_st_t ncp_dev_version(
    char *version);

/*!
 * @fn ncp_st_t ncp_dev_trace_level_get( ncp_dev_hdl_t devHdl,
 *                                       ncp_uint32_t *traceLevel)
 * @brief Gets the current trace level of the ACP device driver.
 *        The device driver supportes up to 32 distinct mesage classes,
 *        each class associated with a bit of the trace level.  [See
 *        NCP_MSG_...  bit handles for the values that have been
 *        implemented.]  Not all of the possible classes may be
 *        implemented.
 * @param devHdl      IN: Device handle
 * @param traceLevel OUT: Current trace level
 */

NCP_API ncp_st_t ncp_dev_trace_level_get(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t *traceLevel);

/*!
 * @fn ncp_st_t ncp_dev_trace_level_set( ncp_dev_hdl_t devHdl,
 *                                       ncp_uint32_t traceLevel)
 * @brief Gets the current trace level of the ACP device driver.
 *        The device driver supportes up to 32 distinct mesage classes,
 *        each class associated with a bit of the trace level.  One can
 *        independently enable and disable the classes.  [See NCP_MSG_...
 *        bit handles for the values that have been implemented.]  Not
 *        all of the possible classes may be implemented.
 * @param devHdl     IN: Device handle
 * @param traceLevel IN: Selected trace level
 */

NCP_API ncp_st_t ncp_dev_trace_level_set(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t traceLevel);

/*!
 * @fn ncp_st_t ncp_dev_reset( ncp_dev_hdl_t devHdl)
 * @brief Performs a reset of the hardware and software of the ACP device
 *        associated with devHdl.  Only the primary domain is permitted
 *        to reset the device.
 * @param devHdl  IN: Device handle
 */

NCP_API ncp_st_t ncp_dev_reset(
    ncp_dev_hdl_t devHdl);

/*!
 * @fn ncp_st_t ncp_dev_num_get( ncp_dev_hdl_t devHdl, ncp_uint32_t *devNum)
 * @brief Returns the device instance number for the specified ACP device.
 * @param devHdl   IN: Device handle
 * @param devNum   OUT: Device number
 */

NCP_API ncp_st_t ncp_dev_num_get(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t *devNum);

/*!
 * @fn ncp_st_t ncp_dev_alarm_irq_get( ncp_dev_hdl_t devHdl, 
 *                                 ncp_bool_t    blocking,
 *                                 ncp_alarm_bitmask_t  *alarm );
 * @brief This functions retrieves the current alarm mask for the specified
 *        ACP device, possibly blocking until one or more has been triggered.
 *        The mask buffer must be allocated by the caller.  It should be
 *        large enough to contain a bit position for every possible alarm
 *        source.
 * @param devHdl     IN: Device handle
 * @param blocking   IN: API is blocking when true, non-blocking when false
 * @param alarm     OUT: bitmask of alarm interrupts 
 */

NCP_API ncp_st_t ncp_dev_alarm_irq_get(
    ncp_dev_hdl_t devHdl,
    ncp_bool_t    blocking,
    ncp_alarm_bitmask_t *alarm);

/*!
 * @fn  ncp_st_t ncp_dev_alarm_handler_register( ncp_dev_hdl_t devHdl, 
 *                                               ncp_uint32_t  irq,
 *                                               ncp_uint32_t  size,
 *                                               ncp_alarm_intr_regs_t *regs);
 * @brief Register the alarm ISR and enable  IRQ 
 * @param devHdl     IN: Device handle
 * @param irq        IN: The IRQ instance to copy the registers from.
 * @param size       IN: The number of registers to copy.
 * @param regs      OUT: The registers from the specified IRQ.
 */
NCP_API ncp_st_t ncp_dev_alarm_handler_register(
     ncp_dev_hdl_t devHdl, 
     ncp_uint32_t  irq,
     ncp_uint32_t  size,
     ncp_alarm_intr_regs_t *regs);


/*!
 * @fn ncp_st_t ncp_dev_se_fem_event_get( ncp_dev_hdl_t devHdl);
 * @brief This function waits for an SE service interrupt.  It blocks waiting for
 * the interrupt if interrupts are supported on the platform, and sleeps as part
 * of a polling implementation if interrupts are not supported.
 * @param devHdl     IN: Device handle
 */

#define NCP_SE_FEM_POLL_TIME 1000

NCP_API ncp_st_t ncp_dev_se_fem_event_get(ncp_dev_hdl_t devHdl);

/*!
 * @fn ncp_st_t ncp_dev_sm_treemem_zq_calibrate_start( ncp_hdl_t hdl, ncp_uint32_t timerInterval, ncp_uint32_t numCmems)
 * @brief Starts the software-based ZQCS routine
 * @param hdl            IN: Device handle
 * @param timerInterval  IN: Interval to send ZQCS command
 * @param numCmems       IN: Number of CMEMs to calibrate
 */
  NCP_API ncp_st_t ncp_dev_sm_treemem_zq_calibrate_start(ncp_hdl_t hdl, ncp_uint32_t timerInterval, ncp_uint32_t numCmems);

/*!
 * @fn ncp_st_t ncp_dev_sm_treemem_zq_calibrate_stop( ncp_hdl_t hdl)
 * @brief Stops the software-based ZQCS routine
 * @param hdl            IN: Device handle
 */
NCP_API ncp_st_t ncp_dev_sm_treemem_zq_calibrate_stop(ncp_hdl_t hdl);

/*!
 * @fn ncp_st_t ncp_dev_timer_event_get( ncp_dev_hdl_t devHdl,ncp_uint64_t *ticks);
 * @brief This function waits for a Timer service interrupt.  It blocks waiting for
 * the interrupt if interrupts are supported on the platform, and returns if
 * interrupts are not supported.
 * @param devHdl     IN: Device handle
 * @param ticks      OUT: Timer ref strobe timestamp
 */
NCP_API ncp_st_t ncp_dev_timer_event_get(ncp_dev_hdl_t devHdl, ncp_uint64_t *ticks);

/*!
 * @fn ncp_st_t ncp_dev_timer_cpu_timer_event_wait(ncp_hdl_t hdl, 
 *                    ncp_uint32_t timerIndex, ncp_uint64_t lastSeq, 
 *                    ncp_uint64_t *currentSeq, ncp_uint32_t flags);
 * @brief Block on CPU Timer event.  Blocks until a CPU timer fires with sequence number greater than lastSeq.
 * @param hdl         IN: Device handle
 * @param timerIndex  IN: Timer index for the requested CPU timer.  Range from 0-15.
 * @param lastSeq     IN: The last captured sequence number for this CPU timer.
 * @param currentSeq OUT: The returned sequence number for this CPU timer.
 * @param flags       IN: Don't block if NCP_TIMER_FLAGS_CPU_TIMER_WAIT_NO_BLOCK is specified.
 */
NCP_API ncp_st_t ncp_dev_timer_cpu_timer_event_wait(ncp_hdl_t hdl, ncp_uint32_t timerIndex, ncp_uint64_t lastSeq, ncp_uint64_t *currentSeq, ncp_uint32_t flags);

/*
 * --- ACP2500 LBI/GPIO configuration/access functions
 */

/*!
 * @fn ncp_st_t ncp_dev_lbi_cs_config( ncp_dev_hdl_t devHdl, 
 *                                     ncp_uint32_t  chipSelect,
 *                                     ncp_uint32_t  deviceWidth,
 *                                     ncp_uint32_t  csFlags)
 * @param devHdl       IN: Device handle
 * @param chipSelect   IN: the LBI chipSelect to be configured 
 * @param deviceWidth  IN: the deviceWidth of the external device (8 or 16 bit)
 * @param csFlags      IN: bitmask of additional per-chipSelect options
 *
 * @brief performs initial configuration for LBI access to an external device using the specified chipSelect
 */

#define NCP_DEV_LBI_DEVICE_WIDTH_16_BIT 16
#define NCP_DEV_LBI_DEVICE_WIDTH_8_BIT   8

#define NCP_DEV_LBI_CS_FLAGS_ACK_EN             0x0001
#define NCP_DEV_LBI_CS_FLAGS_SWAP_EN            0x0002
#define NCP_DEV_LBI_CS_FLAGS_PARITY_EN          0x0004
#define NCP_DEV_LBI_CS_FLAGS_STROBE_DELAY_EN    0x0008
#define NCP_DEV_LBI_CS_ADDR_TRANSLATION_EN      0x0010

NCP_API ncp_st_t ncp_dev_lbi_cs_config(
    ncp_dev_hdl_t               devHdl,
    ncp_uint32_t                chipSelect,
    ncp_uint32_t                deviceWidth,
    ncp_uint32_t                csFlags);


/*!
 * @fn ncp_st_t ncp_dev_lbi_intr_wait( ncp_dev_hdl_t devHdl, 
 *                                 ncp_uint32_t intrSelect);
 * @param devHdl       IN: Device handle
 * @param intrSelect   IN: specify which LBI interrupt source should be waited on
 */

/* 
 * enumerated type to give a name to each LBI 
 * interrupt source. The enumerated value is
 * the bit position in the LBI interrupt status 
 * register.
 */
typedef enum {
    NCP_DEV_LBI_INTR_NOR_ACCESS_DONE = 0,
    NCP_DEV_LBI_INTR_CBI_ACCESS_DONE,
    NCP_DEV_LBI_INTR_LLP,
    NCP_DEV_LBI_INTR_LLP_PARITY_ERR,
    NCP_DEV_LBI_INTR_GPIO_16,
    NCP_DEV_LBI_INTR_GPIO_17,
    NCP_DEV_LBI_INTR_GPIO_18,
    NCP_DEV_LBI_INTR_GPIO_19,
    NCP_DEV_LBI_INTR_GPIO_20,
    NCP_DEV_LBI_INTR_GPIO_21,
    NCP_DEV_LBI_INTR_GPIO_22,
    NCP_DEV_LBI_INTR_GPIO_23,
    NCP_DEV_LBI_INTR_MAX
} ncp_dev_lbi_intr_src_t;


NCP_API ncp_st_t ncp_dev_lbi_intr_wait(
    ncp_dev_hdl_t               devHdl,
    ncp_dev_lbi_intr_src_t      intrSelect);


/*!
 * @fn ncp_st_t ncp_dev_lbi_gpio_config( ncp_dev_hdl_t devHdl, 
 *                                       ncp_dev_lbi_gpio_t  gpioSelect,
 *                                       ncp_dev_lbi_gpio_mode_t mode,
 *                                       ncp_uint32_t sense);
 *
 * @param devHdl       IN: Device handle
 * @param gpioSelect   IN: specify which GPIO pin to configure
 * @param mode         IN: specify the mode for the selected GPIO pin
 * @param sense        IN: specify the sense (depending on the mode)
 */

/*
 * the user configurable GPIO pins 
 */
typedef enum {
    NCP_DEV_LBI_GPIO_0 = 0,
    NCP_DEV_LBI_GPIO_1,
    NCP_DEV_LBI_GPIO_2,
    NCP_DEV_LBI_GPIO_3,
    NCP_DEV_LBI_GPIO_4,
    NCP_DEV_LBI_GPIO_5,
    NCP_DEV_LBI_GPIO_6,
    NCP_DEV_LBI_GPIO_7,
    NCP_DEV_LBI_GPIO_8,
    NCP_DEV_LBI_GPIO_9,
    NCP_DEV_LBI_GPIO_10,
    NCP_DEV_LBI_GPIO_11,
    NCP_DEV_LBI_GPIO_12,
    NCP_DEV_LBI_GPIO_13,
    NCP_DEV_LBI_GPIO_14,
    NCP_DEV_LBI_GPIO_15,
    NCP_DEV_LBI_GPIO_16,
    NCP_DEV_LBI_GPIO_17,
    NCP_DEV_LBI_GPIO_18,
    NCP_DEV_LBI_GPIO_19,
    NCP_DEV_LBI_GPIO_20,
    NCP_DEV_LBI_GPIO_21,
    NCP_DEV_LBI_GPIO_22,
    NCP_DEV_LBI_GPIO_23,
    NCP_DEV_LBI_GPIO_MAX
} ncp_dev_lbi_gpio_t;

#define NCP_DEV_LBI_GPIO(n) (n)

/*
 * possible modes for each GPIO pin
 */
typedef enum {
    /* device specific modes */
    NCP_DEV_LBI_GPIO_MODE_NAND = 0,
    NCP_DEV_LBI_GPIO_MODE_NOR,
    NCP_DEV_LBI_GPIO_MODE_LLP,
    NCP_DEV_LBI_GPIO_MODE_RMII,
    NCP_DEV_LBI_GPIO_MODE_UART,
    NCP_DEV_LBI_GPIO_MODE_SPI,
    /* general purpose i/o */
    NCP_DEV_LBI_GPIO_MODE_GPIO,
    NCP_DEV_LBI_GPIO_MODE_INTR,
    NCP_DEV_LBI_GPIO_MODE_MAX
} ncp_dev_lbi_gpio_mode_t;


/*
 * the 'sense' for GPIO I/O and interrupt pins
 */
#define NCP_DEV_LBI_GPIO_OUTPUT     0
#define NCP_DEV_LBI_GPIO_INPUT      1
#define NCP_DEV_LBI_GPIO_INTR_LO    0
#define NCP_DEV_LBI_GPIO_INTR_HI    1


NCP_API ncp_st_t ncp_dev_lbi_gpio_config(
    ncp_dev_hdl_t               devHdl,
    ncp_dev_lbi_gpio_t          gpioSelect,
    ncp_dev_lbi_gpio_mode_t     mode,
    ncp_uint32_t                sense);

/*!
 * @fn ncp_st_t ncp_dev_lbi_gpio_read( ncp_dev_hdl_t devHdl, 
 *                                       ncp_dev_lbi_gpio_t  gpioSelect,
 *                                       ncp_uint8_t *val);
 *
 * @param devHdl       IN: Device handle
 * @param gpioSelect   IN: specify which GPIO pin to read
 * @param val         OUT: returns the bit value for the selected GPIO pin
 */
NCP_API ncp_st_t ncp_dev_lbi_gpio_read(
    ncp_dev_hdl_t               devHdl,
    ncp_dev_lbi_gpio_t          gpioSelect,
    ncp_uint8_t                *val);

/*!
 * @fn ncp_st_t ncp_dev_lbi_gpio_write( ncp_dev_hdl_t devHdl, 
 *                                       ncp_dev_lbi_gpio_t  gpioSelect,
 *                                       ncp_uint8_t val);
 *
 * @param devHdl       IN: Device handle
 * @param gpioSelect   IN: specify which GPIO pin to read
 * @param val          IN: specify the bit value for the selected GPIO pin
 */
NCP_API ncp_st_t ncp_dev_lbi_gpio_write(
    ncp_dev_hdl_t               devHdl,
    ncp_dev_lbi_gpio_t          gpioSelect,
    ncp_uint8_t                 val);



/* --- NCP Device Level Transaction Interfaces --- */

typedef enum {
    NCP_DEV_TRANS_UNKNOWN = 0,
    NCP_DEV_TRANS_UDELAY,
    NCP_DEV_TRANS_BLOCK_FILL32,
    NCP_DEV_TRANS_BLOCK_WRITE32,
    NCP_DEV_TRANS_BLOCK_SCATTER32,
    NCP_DEV_TRANS_BLOCK_FILL64
} ncp_dev_trans_type_t;

typedef ncp_uint32_t ncp_dev_trans_udelay_t;

typedef struct {
    ncp_region_id_t regionId;
    ncp_uint32_t offset;
    ncp_uint32_t value;
    ncp_uint32_t reserved;
    ncp_uint32_t count;
} ncp_dev_trans_block_fill32_t;

typedef struct {
    ncp_region_id_t regionId;
    ncp_uint32_t offset;
    NCP_DECLARE_POINTER(ncp_uint32_t, dataBuf);
    ncp_uint32_t reserved;
    ncp_uint32_t count;
} ncp_dev_trans_block_write32_t;

#if     !defined(DOXYGEN)

/*!
 * @fn ncp_st_t ncp_dev_transaction_start( ncp_dev_hdl_t devHdl)
 * @param devHdl   IN: Device handle
 *
 */

NCP_API ncp_st_t
ncp_dev_transaction_start(
    ncp_dev_hdl_t devHdl);

/*!
 * @fn ncp_st_t ncp_dev_transaction_add( ncp_dev_hdl_t devHdl,
 *                                       ncp_dev_trans_type_t transType,
 *                                       void *trans, ncp_uint32_t flags);
 * @param devHdl   IN: Device handle
 */

NCP_API ncp_st_t
ncp_dev_transaction_add(
    ncp_dev_hdl_t devHdl,
    ncp_dev_trans_type_t transType,
    void *trans,
    ncp_uint32_t flags);

/*!
 * @fn ncp_st_t ncp_dev_transaction_end( ncp_dev_hdl_t devHdl)
 * @param devHdl   IN: Device handle
 *
 */

NCP_API ncp_st_t
ncp_dev_transaction_end(
    ncp_dev_hdl_t devHdl);

#endif  /* !defined(DOXYGEN) */

/*!
 * @enum ncp_dev_event_type_t.
 * @brief Enum defining different event types supported for registering
 *        callback functions.
 */

/*
 * WARN: When adding new events, add entries in eventInfo table (ncp_dev_event.c).
 */
typedef enum ncp_dev_event_type_e {
    /* this needs to be first */
    NCP_DEV_EVENT_FIRST = 0,

    NCP_DEV_EVENT_CFG_START = 0,
    NCP_DEV_EVENT_CFG_COMPLETE,
    NCP_DEV_EVENT_CFG_DESTROY,

    NCP_DEV_EVENT_NCA_GRP_ANY,               /* any nca grp interrupt source */
    NCP_DEV_EVENT_NCA_GRP_I_PCQ_INTERRUPT,   
    NCP_DEV_EVENT_NCA_GRP_O_PCQ_INTERRUPT,   
    NCP_DEV_EVENT_NCA_GRP_T_PCQ_INTERRUPT,   
    NCP_DEV_EVENT_NCA_GRP_C_PCQ_INTERRUPT,           
    NCP_DEV_EVENT_NCA_GRP0_ERROR_INTERRUPT,  /* Only valid for group 0 */  
    
    NCP_DEV_EVENT_NCA_SHUTDOWN,              /* ncp driver is being unloaded */ 
    NCP_DEV_EVENT_PHY_STATUS_CHANGE,         /* Port Link Change event */
    NCP_DEV_EVENT_HOLDOVER,         	     /* Holdover event */

    /* this needs to be the last */
    NCP_DEV_EVENT_LAST
} ncp_dev_event_type_t;

/*!
 * @typedef ncp_dev_event_hdl_t
 * @brief NCP device event handle.
 */
typedef void * ncp_dev_event_hdl_t;

/* forward decleration */
struct ncp_dev_event_handler_st;

/*!
 * @fn NCP device event callback function.
 * @param cbk_info  - IN: Type of event for which the callback is being called.
 * @param eventData - IN: Parameter passed at register time.
 */

typedef void (* ncp_dev_event_fn_t)(const struct ncp_dev_event_handler_st *event,
                                    const void *eventData);

/*!
 * @struct ncp_dev_event_handler_t
 * @brief Event callback handler registration struct
 */

typedef struct ncp_dev_event_handler_st {
    ncp_dev_event_type_t type;      /* Type of event that has occured. */
    ncp_uint32_t id;                /* id of object for which the event has occured. */
    ncp_dev_event_fn_t cbkFn;       /* Callback function to be called when this event happens. */
    void *cbkArg;                   /* Parameter to be passed when calling the callback function. */
} ncp_dev_event_handler_t;


/*!
 * @fn ncp_st_t ncp_dev_event_handler_register(ncp_dev_hdl_t devHdl,
 *                              ncp_dev_event_handler_t *handlerInfo,
 *                              ncp_dev_event_hdl_t *eventHdl);
 * @return Status code indicating success or failure \link ncp_st_t \endlink 
 * @brief NCP device event callback registration function.
 *        This API is available only in kernel mode.  
 * @param devHdl    - IN: NCP device handle.
 * @param eventType - IN: Type of event for which the callback is being called.
 * @param eventHdl  - OUT: Handle to event.
 */

NCP_API ncp_st_t
ncp_dev_event_handler_register(ncp_dev_hdl_t devHdl,
                               ncp_dev_event_handler_t *handlerInfo,
                               ncp_dev_event_hdl_t *eventHdl);

/*!
 * @fn ncp_st_t ncp_dev_event_handler_unregister(ncp_dev_hdl_t devHdl,
 *                                               ncp_dev_event_hdl_t eventHdl);
 * @return Status code indicating success or failure \link ncp_st_t \endlink  
 * @brief NCP device event callback un-registration function.
 *        This API is available only in kernel mode.  
 * @param devHdl    - IN: NCP device handle.
 * @param eventHdl  - IN: Handle to event.
 */

NCP_API ncp_st_t
ncp_dev_event_handler_unregister(ncp_dev_hdl_t devHdl,
                                 ncp_dev_event_hdl_t eventHdl);

/*!
 * @fn ncp_st_t ncp_dev_event_dispatch_cfg_start(ncp_dev_hdl_t devHdl);
 * @brief Function to dispatch config load start event.
 *        This API is available only in kernel mode.  
 * @param devHdl    - IN: NCP device handle.
 */

NCP_API ncp_st_t
ncp_dev_event_dispatch_cfg_start(ncp_dev_hdl_t devHdl);

/*!
 * @fn ncp_st_t ncp_dev_event_dispatch_cfg_complete(ncp_dev_hdl_t devHdl);
 * @brief Function to dispatch config complete event.
 *        This API is available only in kernel mode.  
 * @param devHdl    - IN: NCP device handle.
 */

NCP_API ncp_st_t
ncp_dev_event_dispatch_cfg_complete(ncp_dev_hdl_t devHdl);

/*!
 * @fn ncp_st_t ncp_dev_event_dispatch_cfg_destroy(ncp_dev_hdl_t devHdl);
 * @brief Function to dispatch config destroy event.
 *        This API is available only in kernel mode.  
 * @param devHdl    - IN: NCP device handle.
 */

NCP_API ncp_st_t
ncp_dev_event_dispatch_cfg_destroy(ncp_dev_hdl_t devHdl);

/*!
 * @fn ncp_st_t ncp_dev_mdioRead(
 *                                ncp_dev_hdl_t  devHdl,
 *                                ncp_region_id_t    regionId,
 *                                ncp_uint64_t        offset,
 *                                ncp_uint32_t       *buffer,
 *                                ncp_uint32_t        count,
 *                                ncp_uint32_t        flag)
 *
 * @brief Perform MDIO read sequence from PHY at target PHY address,
 *        and register offset.
 * @param devHdl    - IN: NCP device handle.
 * @param regionId  - IN: Node/Target of register
 * @param offset    - IN: Specific (start) register displacement
 * @param buffer    - OUT: Location to place results
 * @param count     - IN: Number of registers to read
 * @param flag      - IN: Control flag bits for read operation
 */

ncp_st_t
ncp_dev_mdioRead(
    ncp_dev_hdl_t       devHdl,
    ncp_region_id_t    regionId,
    ncp_uint64_t        offset,
    ncp_uint32_t       *buffer,
    ncp_uint32_t        count,
    ncp_uint32_t        flag);

/*!
 * @fn ncp_st_t ncp_dev_mdioWrite(
 *                                 ncp_dev_hdl_t       devHdl,
 *                                 ncp_region_id_t     regionId,
 *                                 ncp_uint64_t        offset,
 *                                 ncp_uint32_t       *buffer,
 *                                 ncp_uint32_t        count,
 *                                 ncp_uint32_t        flags)
 *
 * @brief Perform MDIO write sequence to PHY at target PHY address,
 *        and register offset.
 * @param devHdl    - IN: NCP device handle.
 * @param regionId  - IN: Node/Target of register
 * @param offset    - IN: Specific (start) register displacement
 * @param buffer    - IN: Location to provide write data
 * @param count     - IN: Number of registers to write
 * @param flag      - IN: Control flag bits for write operation
 */

ncp_st_t
ncp_dev_mdioWrite(
    ncp_dev_hdl_t       devHdl,
    ncp_region_id_t     regionId,
    ncp_uint64_t        offset,
    ncp_uint32_t       *buffer,
    ncp_uint32_t        count,
    ncp_uint32_t        flags); 

/*!
 * @}
 */


NCP_API ncp_st_t
ncp_dev_eioa_alloc(ncp_dev_hdl_t devHdl,
                   ncp_macChan_t macChan,
                   ncp_uint32_t flags);

NCP_API ncp_st_t
ncp_dev_eioa_sync(ncp_dev_hdl_t devHdl,
                   ncp_macChan_t macChan,
                   void *eioa_ptr,
                   ncp_uint32_t eioa_size,
                   ncp_uint32_t flags);

NCP_API ncp_st_t
ncp_dev_eioa_port_alloc(ncp_dev_hdl_t devHdl,
                   ncp_macChan_t macChan,
                   ncp_uint32_t flags);

NCP_API ncp_st_t
ncp_dev_eioa_port_sync(ncp_dev_hdl_t devHdl,
                   ncp_macChan_t macChan,
                   void *port_ptr,
                   void *mcast_ptr,
                   void *shaper_ptr,
                   void *scheduler_ptr,
                   ncp_uint32_t port_size,
                   ncp_uint32_t mcast_size,
                   ncp_uint32_t shaper_size,
                   ncp_uint32_t scheduler_size,
                   ncp_uint32_t flags);

/*!
 * @ingroup _eioa_port_
 * @brief  Retrieve the TX/RX global port enables for a given port.
 * <br> Supports all ACP chiptypes.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *tx_enable Pointer to an instance of ncp_bool_t that indicates
               transmitter state:
 *               <br>TRUE = Transmitter is enabled
 *               <br>FALSE = Transmitter is disabled
 * @param[out] *rx_enable Pointer to an instance of ncp_bool_t that indicates
 *             reciever state:
 *               <br>TRUE = Reciever is enabled
 *               <br>FALSE = Reciever is disabled
 *
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */


NCP_API ncp_st_t
ncp_eioa_port_enable_get(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_bool_t *rx_enable,
             ncp_bool_t *tx_enable);

/*!
 * @ingroup _eioa_port_
 * @brief  Enable and/or Disable TX/RX for the given port.
 * <br> Supports all ACP chiptypes.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] tx_enable  The transmit enable boolean value:
 *            <br>TRUE = Enable Transmitter
 *            <br>FALSE = Disable Transmitter
 * @param[in] rx_enable  The recieve enable boolean value:
 *            <br>TRUE = Enable Reciever
 *            <br>FALSE = Disable Reciever
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_port_enable_set(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_bool_t rx_enable,
             ncp_bool_t tx_enable);

/*!
 * @ingroup _eioa_port_
 * @brief Return the value of the global QinQ setting for the EIOA.
 * <br> Supports all ACP chiptypes.
 * @details
 * When asserted, the QinQ enables the user defined VLAN ethertypes used for
 * outer VLAN tagging. VLAN tags are set on a port by port basis. <br>QinQ is a
 * global setting that affects all configured ports on an EIOA. See - 
 * #ncp_eioa_vlan_config_get()
 * and #ncp_eioa_vlan_config_set().
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *qinq_enable Pointer to an instance of ncp_bool_t for QinQ state
 *             <br>TRUE = QinQ enabled for EIOA
 *             <br>FALSE = QinQ disabled for EIOA
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_qinq_get(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_bool_t *qinq_enable);

/*!
 * @ingroup _eioa_port_
 * @brief Enable/Disable the global QinQ setting for the EIOA.
 * <br> Supports all ACP chiptypes.
 * @details
 * When asserted, the QinQ enables the user defined VLAN ethertypes used for
 * outer VLAN tagging. VLAN tags are set on a port by port basis. <br>QinQ is a
 * global setting that affects all configured ports on an EIOA. See - 
 * #ncp_eioa_vlan_config_get()
 * and #ncp_eioa_vlan_config_set().
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] qinq_enable The QinQ boolean value.
 *            <br>TRUE = QinQ enabled for EIOA
 *            <br>FALSE = QinQ disabled for EIOA
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_EIOA_PORT_VLANS_PRESENT
 */

NCP_API ncp_st_t
ncp_eioa_qinq_set(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_bool_t qinq_enable);

/* Not a public API */
NCP_API ncp_st_t
ncp_dev_eioa_ipp_port_vlan_count_update(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint16_t vlanCount);

/*!
 * @ingroup _eioa_port_
 * @brief  Enable/Disable and/or restart AutoNegotiation on a specified port.
 * <br> Supports all ACP chiptypes.
 * @details
 * <p>If <b>enable_flag</b> is set, auto negotiation will be started on
 * this port. </p>
 * <p>If auto negotiation is already enabled for the port, and the
 * <b>enable_flag</b> is set, and the link is good, and
 * <b>restart_flag</b> is false, then return success.</p>
 * <p>If auto negotiation is already enabled for the port, and the
 * <b>enable_flag</b> is set, and <b>restart_flag</b> is true, then
 * then autonegotiation is restarted.</p>
 * <p>If auto negotiation is already enabled for the port, and the
 * <b>enable_flag</b> is not set, then autonegotiation is disabled</p>
 * <p>If auto negotiation is not enabled for the port, and the
 * <b>enable_flag</b> is set, then autonegotiation is restarted.</p>
 * <p>If the port is a NCP_GMAC* port, and it has been configured for
 * overClock2_5G, an error will be returned. 2.5G auto negotiation is
 * not support for the NCP_GMAC* ports.</p>
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] enable_flag Boolean value to enable/disable AN.
 *   <br>TRUE = Enable AN
 *   <br>FALSE = Disable AN
 * @param[in] restart_flag Boolean value to restart AN.
 *   <br>TRUE = restart AN
 *   <br>FALSE = dont restart AN
 * 
 * @return Error Codes:
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_INVALID_VALUE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 */

NCP_API ncp_st_t
ncp_eioa_auto_neg_set(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_bool_t enable_flag,
             ncp_bool_t restart_flag);

/*!
 * @ingroup _eioa_port_
 * @brief Retrieve the link configuration values for the given port.
 * <br> Supports all ACP chiptypes.
 * @details
 * If <b>enable_flag</b> is set, auto negotiation has been enabled on
 * this port.
 * <p>The <b>speed</b> is returned as a #ncp_mac_speed_t. The speed is only
 * valid when <b>link_good</b> and <b>auto_neg_complete</b> are true,
 * or <b>link_force</b> is true. </p>
 * <p>The <b>link_force</b> flag indicates that the link speed has been forced.</p>
 * <p>The <b>enable_flag</b> and <b>link_force</b> flag should never be
 * set at the same time. </p> 
 * <p>When set, <b>link_good</b> and <b>auto_neg_complete</b> indicated
 * a successful AN process, and a valid speed has been negotiated. </p>
 * <p>If the port is a NCP_GMAC* port, and it has been configured for
 * overClock2_5G, the speed is valid when <b>link_force</b> is true. </p>
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *enable_flag Pointer to and instance of ncp_bool_t, to place the
 *             value of the AN enable flag.
 * @param[out] *speed Pointer to and instance of ncp_mac_speed_t, to place the
 *             value of the negotiated speed.
 * @param[out] *link_force Pointer to an instance of ncp_bool_t, to place the
 *             value of the link_force flag.
 * @param[out] *link_good Pointer to and instance of ncp_bool_t, to place the
 *             value of the link_good flag.
 * @param[out] *auto_neg_complete Pointer to and instance of ncp_bool_t, to
 *             place the value of the auto_neg_complete flag.
 * 
 * @return Error Codes:
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 */

NCP_API ncp_st_t
ncp_eioa_auto_neg_get(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_bool_t *enable_flag,
             ncp_mac_speed_t *speed,
             ncp_bool_t *link_force,
             ncp_bool_t *link_good,
             ncp_bool_t *auto_neg_complete);

/*!
 * @ingroup _eioa_mac_
 * @brief Return packet and octet counters for transmit and recieve interfaces 
 * <br> Supports all ACP chiptypes.
 * @details
 * Transmit statistics pertain to frames transmitted at the line interface by
 * the MAC. Received statistics pertain to frames received at the line
 * interface by the MAC. All counters are 64 bit and conform to #ncp_bdata_t
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *mac_tx_stats Pointer to instance of ncp_mac_txstat_t
 * @param[out] *mac_rx_stats Pointer to instance of ncp_mac_rxstat_t
 * @param[in] clr_flg Boolean value used to clear/not clear the counters
 *            after reading.
 *            <br>TRUE = Reset counter immediatly after reading
 *            <br>FALSE = Do not clear counter after reading
 *
 * @returns 
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_INVALID_HANDLE
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_INVALID_VALUE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_mac_statistics_get(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_mac_txstat_t *mac_tx_stats,
    ncp_mac_rxstat_t *mac_rx_stats,
    ncp_bool_t clr_flg);

/*!
 * @ingroup _eioa_mac_
 * @brief Retrieve the Speed and Duplex settings for a given port.
 * <br> Supports all ACP chiptypes.
 * @details
 * Return the current speed and duplex settings for the designated
 * port.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *speed Pointer to instance of ncp_mac_speed_t
 * @param[out] *duplex Pointer to instance of ncp_bool_t
 *
 * @returns 
 * 	\li ::NCP_ST_SUCCESS
 * 	\li ::NCP_ST_INVALID_HANDLE
 * 	\li ::NCP_ST_DEV_INVALID_HANDLE
 * 	\li ::NCP_ST_EIOA_INVALID_BUFFER
 * 	\li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 * 	\li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 * 	\li ::NCP_ST_MAC_INVALID_MAC
 * 	\li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 */

NCP_API ncp_st_t 
ncp_mac_speed_duplex_get(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_mac_speed_t *speed,
             ncp_bool_t *duplex);

/*!
 * @ingroup _eioa_mac_
 * @brief Configures the Speed and Duplex settings for a given port.
 * <br> Supports all ACP chiptypes.
 * @details
 * This function will force a speed and duplex setting on an EIOA port.
 * Autonegotiation will be disabled and speed/duplex settings shall be set
 * manually. <br>
 * <br>Half Duplex setting is only valid for port speeds of #NCP_MAC_PHY_SPEED10
 * and #NCP_MAC_PHY_SPEED100. An error will be returned for any other settings 
 * of <br>Half Duplex other than these two speeds. <br>
 * <br> The speed setting of #NCP_MAC_PHY_SPEED2_5G can only be used for the
 * #NCP_XGMAC0 and #NCP_XGMAC8 ports when using this API.<br>
 * <br>The speed setting of #NCP_MAC_PHY_SPEED2_5G on the NCP_GMAC* ports are 
 * set at configuration time via the EIOA overClock2_5G flag and affects all 
 * four of the ports on an EIOA.  (i.e - All four ports must run at 2.5G due to
 * overclocking). An error shall be returned should an attempt be made to set
 * the speed  to #NCP_MAC_PHY_SPEED2_5G or change the speed from 
 * #NCP_MAC_PHY_SPEED2_5G on any of the NCP_GMAC* ports using this API.<br>
 * <br>The #NCP_MAC_PHY_SPEED10G rate are only valid for #NCP_XGMAC0 and
 * #NCP_XGMAC8.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] speed The ncp_mac_speed_t value for given port.
 * @param[in] duplex The ncp_bool_t boolean value for given port.
 *
 * @return <ul>
 * 	<li> #NCP_ST_SUCCESS
 * 	<li> #NCP_ST_INVALID_HANDLE
 * 	<li> #NCP_ST_DEV_INVALID_HANDLE
 * 	<li> #NCP_ST_EIOA_INVALID_BUFFER
 * 	<li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 * 	<li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 * 	<li> #NCP_ST_MAC_INVALID_MAC
 * 	<li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 * 	</ul>
 */

NCP_API ncp_st_t 
ncp_mac_speed_duplex_set(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_mac_speed_t speed,
             ncp_bool_t duplex);

/*!
 * @ingroup _eioa_port_
 * @brief Retrieve the 64bit transmit timestamp at counter index.
 * <br> Supports all ACP chiptypes.
 * @details
 * The EIOA captures the time of received and transmitted packets on a per port
 * basis. Timestamp enable flags are set at configuration to enable the
 * timestamp feature in EIOA. <br>When timestamping is enabled at configuration
 * load time, on the receive interface, each incoming packet to the EIOA
 * shall note the time the packet arrived.  <br> On ingress, at the end of a 
 * packet,  the MAC captures the current timestamp and passes it to the ingress
 * block.<br>  The timestamp of each ingress packet is made available as part
 * of the parameters of the outgoing task.<br>
 * <br>For outgoing packets, it is acceptable to have only a limited number of
 * packets with a known timestamp. On egress, when timestamping is enabled,
 * the incoming task has a 6-bit index associated with a packet (for packets
 * that require timestamp). <br> The egress block sends a strobe and this 6-bit
 * index at the end of packet to the MAC.  When the MAC detects this strobe,
 * it updates the internal 64x64 table. <br> The 6-bit index indicates which 
 * table entry to update.  The 64-bit value updated is 64 bits of timestamp.<br>
 * <br>For each EIOA, there are two 64 entry by 64 bit timestamp tables. One
 * table is associated with the XGMAC* port and the second table is
 * assocatiated with the remaining GMAC* ports. The #ncp_macChan_t is used
 * to determine which timestamp table to use.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to the timestamp table.
 * @param[in] tsIndex The value of the table index. Valid range of 0 thru 63.
 * @param[out] *tStamp Pointer to an instance of ncp_uint32_t[2] to place the
 *             <br>32bit high and low timestamp values (64 bits)
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_INVALID_TS_INDEX
 */

NCP_API ncp_st_t 
ncp_eioa_tx_ts_get(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t tsIndex,
    ncp_uint32_t *tStamp);

/*!
 * @ingroup _eioa_port_
 * @brief Retrieve the 64bit transmit timestamp at counter index with i
 * polling iterrations and delay time between polling.
 * <br> Supports all ACP chiptypes.
 * @details
 * The EIOA captures the time of received and transmitted packets on a per port
 * basis. Timestamp enable flags are set at configuration to enable the
 * timestamp feature in EIOA. <br>When timestamping is enabled at configuration
 * load time, on the receive interface, each incoming packet to the EIOA
 * shall note the time the packet arrived.  <br> On ingress, at the end of a 
 * packet,  the MAC captures the current timestamp and passes it to the ingress
 * block.<br>  The timestamp of each ingress packet is made available as part
 * of the parameters of the outgoing task.<br>
 * <br>For outgoing packets, it is acceptable to have only a limited number of
 * packets with a known timestamp. On egress, when timestamping is enabled,
 * the incoming task has a 6-bit index associated with a packet (for packets
 * that require timestamp). <br> The egress block sends a strobe and this 6-bit
 * index at the end of packet to the MAC.  When the MAC detects this strobe,
 * it updates the internal 64x64 table. <br> The 6-bit index indicates which 
 * table entry to update.  The 64-bit value updated is 64 bits of timestamp.<br>
 * <br>For each EIOA, there are two 64 entry by 64 bit timestamp tables. One
 * table is associated with the XGMAC* port and the second table is
 * assocatiated with the remaining GMAC* ports. The #ncp_macChan_t is used
 * to determine which timestamp table to use.
 * 
 * The hardware clears the timestamp on read.  The value of timestamp will be
 * zero as soon as it's read.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to the timestamp table.
 * @param[in] tsIndex The value of the table index. Valid range of 0 thru 63.
 * @param[in] nPollCount Number of times to poll the timestamp register for an updated value.
 * @param[in] uPollDelay Number of microseconds to delay between polling attempts.
 * @param[out] *tStamp Pointer to an instance of ncp_uint32_t[2] to place the
 *             <br>32bit high and low timestamp values (64 bits)
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_INVALID_TS_INDEX
 *     \li ::NCP_ST_POLL_TIMEOUT
 */
NCP_API ncp_st_t
ncp_eioa_tx_ts_get_poll(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t tsIndex,
    ncp_uint32_t nPollCount,
    ncp_uint32_t uPollDelay,
    ncp_uint32_t *tStamp);

/*!
 * @ingroup _eioa_port_
 * @brief  Return the timestamp resolution settings for the port.
 * <br> Supported only on ACP55XX chiptypes.
 * @details
 * Return the timestamp resolution settings for the port.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *resolution  Pointer to an instance of ncp_timestamp_resolution_t 
 * to place the resolution value.
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */
NCP_API ncp_st_t
ncp_eioa_timestamp_resolution_get(ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_timestamp_resolution_t *resolution);

/*!
 * @ingroup _eioa_port_
 * @brief Return the user defined VLAN ethertypes for specified port.
 * <br> Supported only on ACP34XX chiptypes. 
 * @details
 * User defined VLANs are only valid when the global QinQ is asserted
 * and are only used for outer VLAN tagging. <br>VLAN tags are limited to
 * 16bit values.  Also see #ncp_eioa_qinq_set() and #ncp_eioa_qinq_get()
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *vlan_type1 Pointer to an instance of ncp_uint32_t to put
 *             the value of vlan_type1.
 * @param[out] *vlan_type0 Pointer to an instance of ncp_uint32_t to put
 *             the value of vlan_type0.
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 */

NCP_API ncp_st_t 
ncp_eioa_vlan_config_get(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_uint32_t *vlan_type1,
             ncp_uint32_t *vlan_type0);

/*!
 * @ingroup _eioa_port_
 * @brief Set the user defined VLAN ethertypes for specified port.
 * <br> Supported only on ACP34XX chiptypes.
 * @details
 * User defined VLANs are only valid when the global QinQ is asserted
 * and are only used for outer VLAN tagging. <br>VLAN tags are limited to
 * 16bit values.  Also see #ncp_eioa_qinq_set() and #ncp_eioa_qinq_get()
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] vlan_type1 Value of vlan_type1. Limit to 16 bit value
 * @param[in] vlan_type0 Value of vlan_type0. Limit to 16 bit value
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_VLAN_TYPE
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t 
ncp_eioa_vlan_config_set(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_uint32_t vlan_type1,
             ncp_uint32_t vlan_type0);

/*!
 * @ingroup _eioa_port_
 * @brief  Retrieve the tag configuration values for the given port.
 * <br> Supports all ACP chiptypes.
 * @details
 * Each EIOA interface needs to be configured with the assignment of Ethernet
 * interface IDs to physical interfaces. There are seperate tags associated
 * with ingress packets on physical ports and egress packets on physical ports.
 * <ul>
 * <li> For incoming packets, the 16 most significant bits of the tag output
 *      task parameter are used to uniquely identify which physical interface
 *      packets are received on. The <b>tag_msb</b> parameter is set to
 *      register this user configurable unique value.
 * <li> For outgoing packets, the queue ID configuration dictates which
 *      physical interface packets are sent to. These values are set at config
 *      load and should not be modified by the user.
 * <ul>
 * <li> <b>XGMAC0, XGMAC8, XGMAC16, XGMAC32, XGMAC48, XGMAC64, XGMAC80, XGMAC96, XGMAC112</b><br>
 *      <b>GMAC0, GMAC16, GMAC32, GMAC48, GMAC64, GMAC80, GMAC96, GMAC112</b><br>
 *      High Priority Queue ID: 0 <br>
 *      Low Priority Queue ID: 5
 * <li> <b>GMAC1 or GMAC9, XGMAC17, XGMAC33, XGMAC49, XGMAC65, XGMAC81, XGMAC97, XGMAC113</b><br>
 *      <b>GMAC17, GMAC33, GMAC49, GMAC65, GMAC81, GMAC97, GMAC113</b><br>
 *      High Priority Queue ID: 1 <br>
 *      Low Priority Queue ID: 6
 * <li> <b>GMAC2 or GMAC10 or GMAC18</b><br>
 *      High Priority Queue ID: 2 <br>
 *      Low Priority Queue ID: 7
 * <li> <b>GMAC3, GMAC11 or GMAC19</b><br>
 *      High Priority Queue ID: 3 <br>
 *      Low Priority Queue ID: 8
 * <li> <b>GMAC4, GMAC12 or GMAC20</b><br>
 *      High Priority Queue ID: 4 <br>
 *      Low Priority Queue ID: 9
 * </ul>
 * </ul>
 * Each EIOA interface needs to be configured with the value of the "tag"
 * metadata to send with the packet and <b>start_offset</b> - 
 * <b>stop_offset</b> if configurable tag  generation is being used. <br>
 * If the configurable tag generation option is being used, 16 bits of the
 * tag are statically configured per Ethernet interface and 16 bits are
 * generated based on hashing the packet data using the start and stop
 * offsets into the packet configured. <br>This is most useful when packets are
 * being sent to the CPU first.  When the <b>start_offset</b> -
 * <b>stop_offset</b> indicates only 16 bits of the packet are being
 * used, the "trivial hash" is used which just copies the 2 bytes selected
 * into the tag field.<br>  Note the hash is only done on a portion of the first
 * 64 bytes based on the start and stop offsets.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *stop_offset Pointer to an instance of ncp_uint32_t to put
 *             the value of stop_offset.
 * @param[out] *start_offset Pointer to an instance of ncp_uint32_t to put
 *             the value of start_offset.
 * @param[out] *tag_msb Pointer to an instance of ncp_uint32_t to put
 *             the value of tag_msb.
 * @param[out] *enable_flag Pointer to an instance of ncp_bool_t to put
 *             the value of enable_flag.
 * 
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 */

NCP_API ncp_st_t 
ncp_eioa_tag_config_get(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_uint32_t *stop_offset,
             ncp_uint32_t *start_offset,
             ncp_uint32_t *tag_msb,
             ncp_bool_t *enable_flag);

/*!
 * @ingroup _eioa_port_
 * @brief  Set the tag configuration values for the given port.
 * <br> Supports all ACP chiptypes.
 * @details
 * Each EIOA interface needs to be configured with the assignment of Ethernet
 * interface IDs to physical interfaces. There are seperate tags associated
 * with ingress packets on physical ports and egress packets on physical ports.
 * <ul>
 * <li> For incoming packets, the 16 most significant bits of the tag output
 *      task parameter are used to uniquely identify which physical interface
 *      packets are received on. The <b>tag_msb</b> parameter is set to
 *      register this user configurable unique value.
 * <li> For outgoing packets, the queue ID configuration dictates which
 *      physical interface packets are sent to. These values are set at config
 *      load and should not be modified by the user.
 * <ul>
 * <li> <b>XGMAC0, XGMAC8, XGMAC16, XGMAC32, XGMAC48, XGMAC64, XGMAC80, XGMAC96, XGMAC112</b><br>
 *      <b>GMAC0, GMAC16, GMAC32, GMAC48, GMAC64, GMAC80, GMAC96, GMAC112</b><br>
 *      High Priority Queue ID: 0 <br>
 *      Low Priority Queue ID: 5
 * <li> <b>GMAC1 or GMAC9, XGMAC17, XGMAC33, XGMAC49, XGMAC65, XGMAC81, XGMAC97, XGMAC113</b><br>
 *      <b>GMAC17, GMAC33, GMAC49, GMAC65, GMAC81, GMAC97, GMAC113</b><br>
 *      High Priority Queue ID: 1 <br>
 *      Low Priority Queue ID: 6
 * <li> <b>GMAC2, GMAC10 or GMAC18</b><br>
 *      High Priority Queue ID: 2 <br>
 *      Low Priority Queue ID: 7
 * <li> <b>GMAC3, GMAC11 or GMAC19</b><br>
 *      High Priority Queue ID: 3 <br>
 *      Low Priority Queue ID: 8
 * <li> <b>GMAC4, GMAC12 or GMAC20</b><br>
 *      High Priority Queue ID: 4 <br>
 *      Low Priority Queue ID: 9
 * </ul>
 * </ul>
 * Each EIOA interface needs to be configured with the value of the "tag"
 * metadata to send with the packet and <b>start_offset</b> -
 * <b>stop_offset</b> if configurable tag  generation is being used. <br>
 * If the configurable tag generation option is being used, 16 bits of the
 * tag are statically configured per Ethernet interface and 16 bits are
 * generated based on hashing the packet data using the start and stop
 * offsets into the packet configured. <br>This is most useful when packets are
 * being sent to the CPU first.  When the <b>start_offset</b> -
 * <b>stop_offset</b> indicates only 16 bits of the packet are being
 * used, the "trivial hash" is used which just copies the 2 bytes selected
 * into the tag field.<br>  Note the hash is only done on a portion of the first
 * 64 bytes based on the start and stop offsets.<br> The <b>start_offset</b>/
 * <b>stop_offset</b> should only be changed when the <b>enable_flag</b> 
 * is disabled.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] stop_offset The 6 bit value of stop_offset.
 * @param[in] start_offset The 6 bit value of start_offset.
 * @param[in] tag_msb The 16 bit value of tag_msb.
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_TAG
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t 
ncp_eioa_tag_config_set(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_uint32_t stop_offset,
             ncp_uint32_t start_offset,
             ncp_uint32_t tag_msb);

/*!
 * @ingroup _eioa_port_
 * @brief  Set and enable/disable the tag configuration values for the given port.
 * <br> Supports all ACP chiptypes.
 * @details
 * Each EIOA interface needs to be configured with the assignment of Ethernet
 * interface IDs to physical interfaces. There are seperate tags associated
 * with ingress packets on physical ports and egress packets on physical ports.
 * <ul>
 * <li> For incoming packets, the 16 most significant bits of the tag output
 *      task parameter are used to uniquely identify which physical interface
 *      packets are received on. The <b>tag_msb</b> parameter is set to
 *      register this user configurable unique value.
 * <li> For outgoing packets, the queue ID configuration dictates which
 *      physical interface packets are sent to. These values are set at config
 *      load and should not be modified by the user.
 * <ul>
 * <li> <b>XGMAC0, XGMAC8, XGMAC16, XGMAC32, XGMAC48, XGMAC64, XGMAC80, XGMAC96, XGMAC112</b><br>
 *      <b>GMAC0, GMAC16, GMAC32, GMAC48, GMAC64, GMAC80, GMAC96, GMAC112</b><br>
 *      High Priority Queue ID: 0 <br>
 *      Low Priority Queue ID: 5
 * <li> <b>GMAC1 or GMAC9, XGMAC17, XGMAC33, XGMAC49, XGMAC65, XGMAC81, XGMAC97, XGMAC113</b><br>
 *      <b>GMAC17, GMAC33, GMAC49, GMAC65, GMAC81, GMAC97, GMAC113</b><br>
 *      High Priority Queue ID: 1 <br>
 *      Low Priority Queue ID: 6
 * <li> <b>GMAC2, GMAC10 or GMAC18</b><br>
 *      High Priority Queue ID: 2 <br>
 *      Low Priority Queue ID: 7
 * <li> <b>GMAC3, GMAC11< or GMAC19/b><br>
 *      High Priority Queue ID: 3 <br>
 *      Low Priority Queue ID: 8
 * <li> <b>GMAC4, GMAC12 or GMAC20</b><br>
 *      High Priority Queue ID: 4 <br>
 *      Low Priority Queue ID: 9
 * </ul>
 * </ul>
 * Each EIOA interface needs to be configured with the value of the "tag"
 * metadata to send with the packet and <b>start_offset</b> -
 * <b>stop_offset</b> if configurable tag  generation is being used. <br>
 * If the configurable tag generation option is being used, 16 bits of the
 * tag are statically configured per Ethernet interface and 16 bits are
 * generated based on hashing the packet data using the start and stop
 * offsets into the packet configured. <br>This is most useful when packets are
 * being sent to the CPU first.  When the <b>start_offset</b> -
 * <b>stop_offset</b> indicates only 16 bits of the packet are being
 * used, the "trivial hash" is used which just copies the 2 bytes selected
 * into the tag field.<br>  Note the hash is only done on a portion of the first
 * 64 bytes based on the start and stop offsets.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] stop_offset The 6 bit value of stop_offset.
 * @param[in] start_offset The 6 bit value of start_offset.
 * @param[in] tag_msb The 16 bit value of tag_msb.
 * @param[in] enable_flag The boolean value to enable/disable tag generation
 * 
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_TAG
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t 
ncp_eioa_tag_config_set_enable(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_uint32_t stop_offset,
             ncp_uint32_t start_offset,
             ncp_uint32_t tag_msb,
             ncp_bool_t enable_flag);

/*!
 * @ingroup _eioa_port_
 * @brief  Retrieve the value of the tag generation flag for given port.
 * <br> Supports all ACP chiptypes.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *enable_flag Pointer to an instance of ncp_bool_t to put
 *             the value of enable_flag.
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t 
ncp_eioa_tag_enable_get(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_bool_t *enable_flag);

/*!
 * @ingroup _eioa_port_
 * @brief  Set the value of the tag generation flag for given port.
 * <br> Supports all ACP chiptypes.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] enable_flag The value of enable_flag.
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t 
ncp_eioa_tag_enable_set(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_bool_t enable_flag);

/*!
 * @ingroup _eioa_port_
 * @brief Retrieve the CRC settings for given port.
 * <br> Supports all ACP chiptypes.
 * @details
 * Each EIOA interface needs to be configured with whether it should append a
 * correct or incorrect CRC to outgoing packets. Each EIOA interface needs to
 * be configured with whether it should strip the CRC from incoming packets.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *crc_append Pointer to an instance of ncp_bool_t to put
 *             that value of crc_append.
 * @param[out] *crc_appendbad Pointer to an instance of ncp_bool_t to put
 *             that value of crc_appendbad.
 * @param[out] *crc_strip Pointer to an instance of ncp_bool_t to put
 *             that value of crc_strip.
 * 
 * @return 
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t 
ncp_eioa_crc_get(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_bool_t *crc_append,
             ncp_bool_t *crc_appendbad,
             ncp_bool_t *crc_strip);

/*!
 * @ingroup _eioa_port_
 * @brief  Set the CRC values for given port.
 * <br> Supports all ACP chiptypes.
 * @details
 * Each EIOA interface needs to be configured with whether it should append a
 * correct or incorrect CRC to outgoing packets. Each EIOA interface needs to
 * be configured with whether it should strip the CRC from incoming packets.
 * If <b>crc_append</b> and <b>crc_appendbad</b> are both enabled, a
 * #NCP_ST_EIOA_INVALID_PORT_CONFIG error will be returned. It is acceptable 
 * for both <b>crc_append</b> and <b>crc_appendbad</b> to be disabled,
 * which would not append any CRC to outgoing packets.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] crc_append The value of crc_append.
 *        <br>TRUE = Append good CRC to outgoing packet.
 *        <br>FALSE = Do Not append any CRC to outgoing packet.
 * @param[in] crc_appendbad The value of crc_appendbad.
 *        <br>TRUE = Append bad CRC to outgoing packet.
 *        <br>FALSE = Do Not append any CRC to outgoing packet.
 * @param[in] crc_strip The value of crc_strip.
 *        <br>TRUE = Strip CRC from incoming packet.
 *        <br>FALSE = Do Not strip CRC from incoming packet.
 *
 * @returns
 *      \li ::NCP_ST_SUCCESS
 *      \li ::NCP_ST_DEV_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t 
ncp_eioa_crc_set(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_bool_t crc_append,
    ncp_bool_t crc_appendbad,
    ncp_bool_t crc_strip);

/*!
 * @ingroup _eioa_port_
 * @brief  Retrieve configuration status for the given port.
 * <br> Supports all ACP chiptypes.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *port_stat Not used at this time, for future reference
 * @param[out] *port_cfg_ok Pointer to and instance of ncp_bool_t, to place
 *             the port configuration OK value.
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t 
ncp_eioa_status_get(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_port_t *port_stat,
             ncp_bool_t *port_cfg_ok);

/*!
 * @ingroup _eioa_mac_
 * @brief  Retrieve the MAC address for the given port.
 * <br> Supports all ACP chiptypes.
 * @details
 * The MAC address for this port. This 48bit address is also the MAC Source
 * Address used in transmitted PAUSE frames, and to recognize received
 * PAUSE frames which don't use the reserved multicast destination address.
 * The MAC address is set at configuration and programmed at configuration
 * load time.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *mac_addr Pointer to and instance of ncp_uint8_t[6], to place
 *             the 48bit mac address.
 *
 * @return <ul>
 * 	<li> #NCP_ST_SUCCESS
 * 	<li> #NCP_ST_INVALID_HANDLE
 * 	<li> #NCP_ST_DEV_INVALID_HANDLE
 * 	<li> #NCP_ST_EIOA_INVALID_BUFFER
 * 	<li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 * 	<li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 * 	<li> #NCP_ST_MAC_INVALID_MAC
 *	</ul>
 */

NCP_API ncp_st_t 
ncp_eioa_mac_addr_get(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_uint8_t *mac_addr);


/*!
 * @ingroup _eioa_mac_
 * @brief  Set the MAC address for the given port.
 * <br> Supports all ACP chiptypes.
 * @details
 * The MAC address for this port. This 48bit address is also the MAC Source
 * Address used in transmitted PAUSE frames, and to recognize received
 * PAUSE frames which don't use the reserved multicast destination address.
 * The MAC address is set at configuration and programmed at configuration
 * load time.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] *mac_addr Pointer to and instance of ncp_uint8_t[6], to place
 *             the 48bit mac address.
 *
 * @return <ul>
 * 	<li> #NCP_ST_SUCCESS
 * 	<li> #NCP_ST_INVALID_HANDLE
 * 	<li> #NCP_ST_DEV_INVALID_HANDLE
 * 	<li> #NCP_ST_EIOA_INVALID_BUFFER
 * 	<li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 * 	<li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 * 	<li> #NCP_ST_MAC_INVALID_MAC
 *	</ul>
 */

NCP_API ncp_st_t
ncp_eioa_mac_addr_set(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_uint8_t *mac_addr);
/*!
 * @ingroup _eioa_port_
 * @brief  Enable promiscuous mode.
 * <br> Supports all ACP chiptypes.
 * When promiscuous mode is enabled, all packets are accepted.
 * @details
 * Write 0 to bit 0 of control register 12 of negmac to enable promiscuous mode.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA. 
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_promisc_enable(
		ncp_hdl_t hdl,
		ncp_macChan_t macChan);
/*!
 * @ingroup _eioa_port_
 * @brief  Disable promiscuous mode.
 * <br> Supports all ACP chiptypes.
 * When promiscuous mode is disabled, packet filtering is re-enabled.
 * Please note the filtering settings that were effective earlier (prior to applying
 * promiscous mode) will come into effect again. For example, if there was 
 * unicast/multicast filtering in effect, enabling promiscous mode will disable all 
 * filtering. Promiscous mode disable is going to re-enable the filtering.
 * @details
 * Write 1 to bit0 control register 12 of negmac to disable promiscuous mode.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA. 
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_promisc_disable(
		ncp_hdl_t hdl,
		ncp_macChan_t macChan);


/*!
 * @ingroup _eioa_port_
 * @brief  Ethernet address filtering. Enable or Disable unicast filtering.
 * <br> Supports all ACP chiptypes.
 * When Unicast Filtering is enabled, all packets matching the programmed
 * destination addressses set for this port are accepted.
 * @details
 * The GMAC shall support up to 3 48bit Unicast Destination Addresses per port.
 * When enabled, packets matching the programmed addresses are accepted, and
 * all other Unicast packets are discarded.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] enable_flag The boolean value of enable/disable Unicast
 * filtering flag.
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_unicast_filter_enable(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_bool_t enable_flag);

/*!
 * @ingroup _eioa_port_
 * @brief  Return the unicast enable value and the values of the three Unicast
 * destination address filters.
 * <br> Supports all ACP chiptypes. Also see #ncp_eioa_unicast_mac_addr_get for more comprehensive output.
 * @details
 * The GMAC shall support up to 3 48bit Unicast Destination Addresses per port.
 * When enabled, packets matching the programmed addresses are accepted, and
 * all other Unicast packets are discarded.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *enable_flag Pointer to an instance of ncp_bool_t, to place
 * the boolean value of enable/disable Unicast filtering flag.
 * @param[out] *unicast_addr_1 Pointer to an instance of ncp_uint8_t[6], to
 *             place the 48bit Unicast filter address.
 * @param[out] *unicast_addr_2 Pointer to an instance of ncp_uint8_t[6], to
 *             place the 48bit Unicast filter address.
 * @param[out] *unicast_addr_3 Pointer to an instance of ncp_uint8_t[6], to
 *             place the 48bit Unicast filter address.
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_unicast_filter_get(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_bool_t *enable_flag,
    ncp_uint8_t *unicast_addr_1,
    ncp_uint8_t *unicast_addr_2,
    ncp_uint8_t *unicast_addr_3);

/*!
 * @ingroup _eioa_port_
 * @brief  Enables/Disable unicast filtering and set the three unicast address
 * filter values.
 * <br> This API is depricated for ACP55xx.  For ACP55xx see #ncp_eioa_unicast_mac_addr_set
 * @details
 * The GMAC shall support up to 3 48bit Unicast Destination Addresses per port.
 * When enabled, packets matching the programmed addresses are accepted, and
 * all other Unicast packets are discarded. <br> Pointers to all three Unicast
 * address variables need to be valid, even if the 48bit addresses are set to
 * default values of all 0's.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] enable_flag Boolean value to enable/disable Unicast Filtering
              for this port.
 * @param[in] *unicast_addr_1 Pointer to an instance of ncp_uint8_t[6], to
 *             retrieve the 48bit Unicast filter address.
 * @param[in] *unicast_addr_2 Pointer to an instance of ncp_uint8_t[6], to
 *             retrieve the 48bit Unicast filter address.
 * @param[in] *unicast_addr_3 Pointer to an instance of ncp_uint8_t[6], to
 *             retrieve the 48bit Unicast filter address.
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_INVALID_VALUE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_unicast_filter_set(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_bool_t enable_flag,
    ncp_uint8_t *unicast_addr_1,
    ncp_uint8_t *unicast_addr_2,
    ncp_uint8_t *unicast_addr_3);

/*!
 * @ingroup _eioa_port_
 * @brief  Returns the multicast filter address at the table_index location
 * in the multicast address table. In additon, the current size of the
 * multicast address table and  the value of the enable flag is returned to
 * the caller.
 * <br> Supports all ACP chiptypes.
 * @details
 * When multicast filtering is enabled, a 128 bit programmable hash function
 * is used to determine whether to filter (discard) or forward the frame.
 * <br>Each received frame is passed through the Multicast Filter.<br>
 * The frame's 48-bit destination address (DA) is used to determine whether
 * the Multicast Filter is activated and, if so, whether or not the frame is
 * to be discarded. <br>
 * If bit 40 of the 48 bit DA equals 1, and the DA is neither a broadcast
 * nor pause frame address, the Multicast Filter is activated. <br>
 * If the Multicast Filter is activated, the DA is used to generate a CRC,
 * the lower seven bits of which index into the 128-bit hash table. <br>
 * Should the DA address match the value in hash table, the frame will be 
 * forwarded.<br>
 * A seperate 128 entry multicast table of 48 bit addresses is kept to track
 * hash table settings on a per port basis. <br>
 * <br><b>table_index</b> A valid table index is in the range of 0 through
 * 127. <br>
 * <b>multicast_address</b> This is the address in the mulicast table at
 * the offset specified by table_index. <br>
 * <b>table_size</b> The current size of the multicast table. This is the
 * top of the table. As multicast addresses are added to the table, the size
 * shall increment to a maximum size of 128. If  the table size is  zero, then
 * the table is empty. <br>
 * <b>enable_flag</b> The flag to enable/disable multicast filtering for
 * this port.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] table_index Index into the multicast table to retrieve the
 *            address.
 * @param[out] *multicast_addr Pointer to an instance of ncp_uint8_t[6], to
 *             place the 48 bit multicast filter address.
 * @param[out] *table_size Pointer to an instance of ncp_uint32_t, to place
 *             the value for the currnt size of the table.
 * @param[out] *enable_flag Pointer to an instance of ncp_bool_t, to place the
 *             value of the multicast enable flag for this port.
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_INVALID_VALUE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_EIOA_MCAST_TBL_IDX_ERROR
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */
NCP_API ncp_st_t
ncp_eioa_multicast_filter_get(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t table_index,
    ncp_uint8_t *multicast_addr,
    ncp_uint32_t *table_size,
    ncp_bool_t *enable_flag);

/*!
 * @ingroup _eioa_port_
 * @brief Modifies the multicast filter address at the table_index location
 * in the multicast address table, computes and adds the new entry into the
 * hash table, and deletes the provious entry in the hash table. In additon,
 * the current size of the multicast address table is returned to the caller.
 * <br> Supports all ACP chiptypes.
 * @details
 * When multicast filtering is enabled, a 128 bit programmable hash function
 * is used to determine whether to filter (discard) or forward the frame.
 * <br>Each received frame is passed through the Multicast Filter.<br>
 * The frame's 48-bit destination address (DA) is used to determine whether
 * the Multicast Filter is activated and, if so, whether or not the frame is
 * to be discarded. <br>
 * If bit 40 of the 48 bit DA equals 1, and the DA is neither a broadcast
 * nor pause frame address, the Multicast Filter is activated. <br>
 * If the Multicast Filter is activated, the DA is used to generate a CRC,
 * the lower seven bits of which index into the 128-bit hash table. <br>
 * Should the DA address match the value in hash table, the frame will be
 * forwarded.<br>
 * A seperate 128 entry multicast table of 48 bit addresses is kept to track
 * hash table settings on a per port basis. <br>
 * <br><b>table_index</b> A valid table index is in the range of 0 through
 * 127. <br>
 * <b>multicast_address</b> This is the address in the mulicast table at
 * the offset specified by table_index. <br>
 * <b>table_size</b> The current size of the multicast table. This is the
 * top of the table. As multicast addresses are added to the table, the size
 * shall increment to a maximum size of 128. If  the table size is  zero, then
 * the table is empty. <br>
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] table_index Index into the multicast table to retrieve the
 *            address.
 * @param[in] *multicast_addr Pointer to an instance of ncp_uint8_t[6], to
 *             retrieve the 48 bit multicast filter address.
 * @param[out] *table_size Pointer to an instance of ncp_uint32_t, to place
 *             the value for the current size of the table.
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_INVALID_VALUE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_EIOA_MCAST_TBL_IDX_ERROR
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_multicast_filter_set(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t table_index,
    ncp_uint8_t *multicast_addr,
    ncp_uint32_t *table_size);

/*!
 * @ingroup _eioa_port_
 * @brief  Adds a new multicast filter address to the top of the multicast
 * table, computes and adds an entry to the hash table. The location of the
 * multicast address in the table is returned as the table_index value. The
 * size of the multicast address table is returned as table_size.
 * <br> Supports all ACP chiptypes.
 * @details
 * When multicast filtering is enabled, a 128 bit programmable hash function
 * is used to determine whether to filter (discard) or forward the frame.
 * <br>Each received frame is passed through the Multicast Filter.<br>
 * The frame's 48-bit destination address (DA) is used to determine whether
 * the Multicast Filter is activated and, if so, whether or not the frame is
 * to be discarded. <br>
 * If bit 40 of the 48 bit DA equals 1, and the DA is neither a broadcast
 * nor pause frame address, the Multicast Filter is activated. <br>
 * If the Multicast Filter is activated, the DA is used to generate a CRC,
 * the lower seven bits of which index into the 128-bit hash table. <br>
 * Should the DA address match the value in hash table, the frame will be
 * forwarded.<br>
 * A seperate 128 entry multicast table of 48 bit addresses is kept to track
 * hash table settings on a per port basis. <br>
 * <br><b>table_index</b> A valid table index is in the range of 0 through
 * 127. <br>
 * <b>multicast_address</b> This is the address in the mulicast table at
 * the offset specified by table_index. <br>
 * <b>table_size</b> The current size of the multicast table. This is the
 * top of the table. As multicast addresses are added to the table, the size
 * shall increment to a maximum size of 128. If  the table size is  zero, then
 * the table is empty. <br>
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] table_index Pointer to an instance of ncp_uint32_t, to place the
 *             value of the table index.
 * @param[in] *multicast_addr Pointer to an instance of ncp_uint8_t[6], to
 *             retrieve the 48 bit multicast filter address.
 * @param[out] *table_size Pointer to an instance of ncp_uint32_t, to place
 *             the value for the current size of the table.
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_EIOA_MCAST_TBL_IDX_ERROR
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_multicast_filter_add(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t *table_index,
    ncp_uint8_t *multicast_addr,
    ncp_uint32_t *table_size);

/*!
 * @ingroup _eioa_port_
 * @brief  Deletes the multicast address in the multicast address table at
 * the table_index location, and deletes the entry in the hash table. The
 * current size of the multicast address table is returned to the caller.
 * <br> Supports all ACP chiptypes.
 * @details
 * When multicast filtering is enabled, a 128 bit programmable hash function
 * is used to determine whether to filter (discard) or forward the frame.
 * <br>Each received frame is passed through the Multicast Filter.<br>
 * The frame's 48-bit destination address (DA) is used to determine whether
 * the Multicast Filter is activated and, if so, whether or not the frame is
 * to be discarded. <br>
 * If bit 40 of the 48 bit DA equals 1, and the DA is neither a broadcast
 * nor pause frame address, the Multicast Filter is activated. <br>
 * If the Multicast Filter is activated, the DA is used to generate a CRC,
 * the lower seven bits of which index into the 128-bit hash table. <br>
 * Should the DA address match the value in hash table, the frame will be
 * forwarded.<br>
 * A seperate 128 entry multicast table of 48 bit addresses is kept to track
 * hash table settings on a per port basis. <br>
 * <br><b>table_index</b> A valid table index is in the range of 0 through
 * 127. <br>
 * <b>table_size</b> The current size of the multicast table. This is the
 * top of the table. As multicast addresses are added to the table, the size
 * shall increment to a maximum size of 128. If  the table size is  zero, then
 * the table is empty. <br>
 * Note that deleting entries in the table does not reduce the size, it only 
 * zeros out the entry at the index.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] table_index Index into the multicast address table.
 * @param[out] *table_size Pointer to an instance of ncp_uint32_t, to place
 *             the value for the current size of the table.
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_INVALID_VALUE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_EIOA_MCAST_TBL_IDX_ERROR
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_multicast_filter_delete(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t table_index,
    ncp_uint32_t *table_size);

/*!
 * @ingroup _eioa_port_
 * @brief  Enable or Disable multicast address filtering for this EIOA/Channel
 * <br> Supports all ACP chiptypes.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] enable_flag The boolean value of the enable flag.
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_INVALID_VALUE
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_multicast_filter_enable(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_bool_t enable_flag);

/*!
 * @ingroup _eioa_port_
 * @brief  Return the virtual pipline name and the pipline id this EIOA/Channel
 * and pipline 802.1p priority. 
 * <br> Supported only on ACP34XX chiptypes.
 * @details 
 * Each EIOA interface needs to be configured with the virtual pipeline and 
 * launch template to launch received packets into, including information on 
 * which task queue should be used per 802.1p priority, or default to use if 
 * the packet is not priority tagged. 
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] **vpName  Pointer to an instance of a string to place the 
 * virtual pipeline name. 
 * @param[out] *vp_id  Pointer to a instance of ncp_uint8_t to place the 
 * virtual pipline id.
 * @param[in] vpPriority The 801.1p priority.  
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_INVALID_VALUE
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_vp_id_get(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    char *vpName,
    ncp_uint8_t *vp_id,
    ncp_uint32_t vpPriority);

/*!
 * @ingroup _eioa_port_
 * @brief  Configure the virtual pipline and launch template id for the EIOA/Channel
 * <br> Supported only on ACP34XX chiptypes.
 * @details
 * Each EIOA interface needs to be configured with the virtual pipeline and
 * launch template to launch received packets into, including information on
 * which task queue should be used per 802.1p priority, or default to use if
 * the packet is not priority tagged.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] vpName  The name of the virtual pipline
 * @param[in] vpPriority The 801.1p priority.
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_INVALID_VALUE
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_vp_id_set(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    char *vpName,
    ncp_uint32_t vpPriority);


/*!
 * @ingroup _eioa_port_
 * @brief  Return the virtual pipline name and the pipline id this EIOA/Channel
 * and pipline 802.1p priority. 
 * <br> Supported on AXX3500 and AXX5500 chiptypes.
 * @details 
 * Each EIOA interface needs to be configured with the virtual pipeline and 
 * launch template to launch received packets into, including information on 
 * which task queue should be used per 802.1p priority, or default to use if 
 * the packet is not priority tagged. 
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] type An instance of enumerated ncp_vflow_priority_t to hold the priority - tagged or unknown.
 * The enumerated values are:
 *         NCP_EIOA_VFLOW_PRIORITY_UNKNOWN<br>
 *         NCP_EIOA_VFLOW_PRIORITY_KNOWN 
 *
 * @param[out] *vpName  Pointer to an instance of a string to place the 
 * virtual pipeline name. 
 * @param[out] *vp_id  Pointer to a instance of ncp_uint8_t to place the 
 * virtual pipline id.
 * @param[out] attrs   The data structure holding priorities - 801.1p priority.
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_INVALID_VALUE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */
NCP_API ncp_st_t
ncp_eioa_port_vp_get(ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_vflow_priority_t type,
    char* vpname,
    ncp_uint8_t* vflow_id,
    ncp_eioa_port_vp_info_t* attrs);


/*!
 * @ingroup _eioa_port_
 * @brief  Configure the virtual pipline and launch template id for the EIOA/Channel
 * <br> Supported on AXX3500 and AXX5500 chiptypes.
 * @details
 * Each EIOA interface needs to be configured with the virtual pipeline and
 * launch template to launch received packets into, including information on
 * which task queue should be used per 802.1p priority, or default to use if
 * the packet is not priority tagged.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] type An instance of enumerated ncp_vflow_priority_t to hold the priority  - tagged or unknown.
 * The enumerated types are:
 *         NCP_EIOA_VFLOW_PRIORITY_UNKNOWN<br>
 *         NCP_EIOA_VFLOW_PRIORITY_KNOWN 
 * @param[in] vpName  The name of the virtual pipline
 * @param[in] attrs   The data structure holding priorities - 801.1p priority.
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_INVALID_VALUE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_port_vp_set(ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_vflow_priority_t type,
    char* vpname,
    ncp_eioa_port_vp_info_t* attrs);

/*!
 * @ingroup _eioa_port_
 * @brief  Return the timestamp marker delay information for the MAC.
 * <br> Supported only on ACP55XX chiptypes.
 * @details 
 * Return the timestamp marker delay information for the MAC.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *md_tx  Pointer to an instance of ncp_uint16_t to place the 
 * Transmit Marker delay.
 * @param[out] *md_rx  Pointer to an instance of ncp_uint16_t to place the 
 * Receive Marker delay.
 *
 * @returns
 *     \li NCP_ST_SUCCESS
 *     \li NCP_ST_DEV_INVALID_HANDLE
 *     \li NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li NCP_ST_MAC_INVALID_MAC
 */
NCP_API ncp_st_t
ncp_eioa_port_ts_marker_delay_get(ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_uint16_t *md_tx,
    ncp_uint16_t *md_rx);

/*!
 * @ingroup _eioa_port_
 * @brief  Return the configuration for the maximum packet size for ingress 
 * packets on this EIOA/Channel
 * <br> Supported on AXX3500 and AXX5500 chiptypes.
 * @details
 * Each EIOA interface needs to be configured with the maximum packet size
 * supported <i>(4 options: 2KBytes, 4KBytes, 8KBytes and 10KBytes)</i>, with
 * 10KBytes being the absolute maximum.  On ingress, if a packet is greater
 * than the configured maximum packet size, the packet is truncated and
 * framerError is asserted in the output parameters.  The remainder of the
 * packet from the MAC is discarded.  
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *packetSize  Pointer to an instance for the enumerated value of
 * the maximum packet size.
 *         <ul>
 *         <li> #NCP_EIOA_PKTSIZE_10K = 0
 *         <li> #NCP_EIOA_PKTSIZE_2K = 1
 *         <li> #NCP_EIOA_PKTSIZE_4K = 2
 *         <li> #NCP_EIOA_PKTSIZE_8K = 3
 *         </ul>
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_INVALID_VALUE
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_rx_max_pkt_size_get(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_eioa_pktsize_t *packetSize);

/*!
 * @ingroup _eioa_port_
 * @brief  Configure the maximum packet size for ingress packets on this EIOA/Channel
 * <br> Supports all ACP chiptypes.
 * @details
 * Each EIOA interface needs to be configured with the maximum packet size 
 * supported <i>(4 options: 2KBytes, 4KBytes, 8KBytes and 10KBytes)</i>, with
 * 10KBytes being the absolute maximum.  On ingress, if a packet is greater
 * than the configured maximum packet size, the packet is truncated and 
 * framerError is asserted in the output parameters.  The remainder of the 
 * packet from the MAC is discarded. 
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] packetSize  The enum value for the maximum packet size.
 *         <ul>
 *         <li> #NCP_EIOA_PKTSIZE_10K = 0
 *         <li> #NCP_EIOA_PKTSIZE_2K = 1
 *         <li> #NCP_EIOA_PKTSIZE_4K = 2
 *         <li> #NCP_EIOA_PKTSIZE_8K = 3
 *         </ul>
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_INVALID_VALUE
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_rx_max_pkt_size_set(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_eioa_pktsize_t packetSize);

/*!
 * @ingroup _eioa_port_
 * @brief  Return the configuration for the maximum packet size of egress
 * packets on this EIOA/Channel
 * <br> Supports all ACP chiptypes.
 * @details
 * Each EIOA interface needs to be configured with the maximum packet size 
 * supported <i>(4 options: 2KBytes, 4KBytes, 8KBytes and 10KBytes)</i>, with 
 * 10KBytes being the absolute maximum. On egress, if a packet is greater than 
 * the configured maximum packet size, the packet is truncated and CRC error 
 * is appended.  The remainder of the packet from system memory is discarded.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *packetSize  Pointer to an instance of the enumerated value for
 *  the maximum packet size.
 *         <ul>
 *         <li> #NCP_EIOA_PKTSIZE_10K = 0
 *         <li> #NCP_EIOA_PKTSIZE_2K = 1
 *         <li> #NCP_EIOA_PKTSIZE_4K = 2
 *         <li> #NCP_EIOA_PKTSIZE_8K = 3
 *         </ul>
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_INVALID_VALUE
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_tx_max_pkt_size_get(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_eioa_pktsize_t *packetSize);

/*!
 * @ingroup _eioa_port_
 * @brief  Configure the maximum packet size for egress packets on this EIOA/Channel
 * <br> Supports all ACP chiptypes.
 * @details
 * Each EIOA interface needs to be configured with the maximum packet size 
 * supported <i>(4 options: 2KBytes, 4KBytes, 8KBytes and 10KBytes)</i>, with 
 * 10KBytes being the absolute maximum. On egress, if a packet is greater than 
 * the configured maximum packet size, the packet is truncated and CRC error 
 * is appended.  The remainder of the packet from system memory is discarded.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] packetSize  The enumerated value for the maximum packet size.
 *         <ul>
 *         <li> #NCP_EIOA_PKTSIZE_10K = 0
 *         <li> #NCP_EIOA_PKTSIZE_2K = 1
 *         <li> #NCP_EIOA_PKTSIZE_4K = 2
 *         <li> #NCP_EIOA_PKTSIZE_8K = 3
 *         </ul>
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_INVALID_VALUE
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_tx_max_pkt_size_set(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_eioa_pktsize_t packetSize);

/*!
 * @ingroup _eioa_mac_
 * @brief  Configure the EIOA/Channel to respond to, filter or forward flow 
 * control indications (PAUSE packets) from the network. <br>Configure the 
 * EIOA/Channel to generate (PAUSE packets) to the network. 
 * <br> Supports all ACP chiptypes.
 * @details
 * <ul> 
 * <li> PAUSE packets from the network
 * <ul> 
 * <li> If configured to <b>respond</b> and PAUSE packets are received the
 * EIOA/Channel will cease to send packets on the offending output port for
 * <b>pauseTime</b> (it does complete transmission of the current packet). 
 * The output port's task queues eventually back up, resulting in a BP message
 * on the BP ring for all sources of traffic for the corresponding output 
 * port. 
 * <li> If configured to <b>filter</b>, EIOA simply drops all PAUSE packets.
 * <li> If configured to <b>forward</b>, EIOA simply forwards PAUSE packets 
 * like all other packets.  
 * <li> Note: the three options for PAUSE packets from the network 
 * <i>(respond, filter, forward)</i> are mutually exclusive. 
 * </ul>
 * <li> PAUSE packets to the network
 * <ul> 
 * <li> If configured to <b>generate</b> flow control, a BP "on" message from 
 * the BP ring indicates that PAUSE packets should be generated. One PAUSE 
 * packet is generated every pauseTime/2 until a BP "off" message is received.
 * <li> If configured to <b>generate but drop recieve</b>, all packets on 
 * input port will be dropped when PAUSE packets are transmitted 
 * on corresponding output port (default is to NOT drop packets). 
 * <ul> 
 * </ul>
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] pauseEnable The boolean value for the pauseType flag.
 * @param[in] pauseType The type PAUSE to configure.
 *            <ul>
 *            <li> #NCP_PAUSE_RESPOND = 0x01
 *            <li> #NCP_PAUSE_FILTER = 0x02
 *            <li> #NCP_PAUSE_FORWARD = 0x04
 *            <li> #NCP_PAUSE_GENERATE = 0x08
 *            <li> #NCP_PAUSE_GENERATE_DROP_RX = 0x10
 *            </ul>
 * @param[in] pauseTime The MAC PAUSE Quanta time set for generating PAUSE 
 *                      packets to the network, and the MAC PAUSE Quanta when 
 *                      responding to PAUSE packets from the network.
 *
 * @return <ul>
 * 	<li> #NCP_ST_SUCCESS
 * 	<li> #NCP_ST_INVALID_HANDLE
 * 	<li> #NCP_ST_DEV_INVALID_HANDLE
 * 	<li> #NCP_ST_INVALID_VALUE
 * 	<li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 * 	<li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 * 	<li> #NCP_ST_MAC_INVALID_MAC
 *	</ul>
 */

NCP_API ncp_st_t
ncp_eioa_mac_flow_ctrl_set(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_bool_t pauseEnable,
    ncp_uint32_t pauseType,
    ncp_uint16_t pauseTime);

/*!
 * @ingroup _eioa_mac_
 * @brief  Return the EIOA/Channel configurations for PAUSE packets to and 
 * from the network.
 * <br> Supports all ACP chiptypes.
 * @details
 * <ul> 
 * <li> PAUSE packets from the network
 * <ul> 
 * <li> If configured to <b>respond</b> and PAUSE packets are received the
 * EIOA/Channel will cease to send packets on the offending output port for
 * <b>pauseTime</b> (it does complete transmission of the current packet). 
 * The output port's task queues eventually back up, resulting in a BP message
 * on the BP ring for all sources of traffic for the corresponding output 
 * port. 
 * <li> If configured to <b>filter</b>, EIOA simply drops all PAUSE packets.
 * <li> If configured to <b>forward</b>, EIOA simply forwards PAUSE packets 
 * like all other packets.  
 * <li> Note: the three options for PAUSE packets from the network 
 * <i>(respond, filter, forward)</i> are mutually exclusive. 
 * </ul>
 * <li> PAUSE packets to the network
 * <ul> 
 * <li> If configured to <b>generate</b> flow control, a BP "on" message from 
 * the BP ring indicates that PAUSE packets should be generated. One PAUSE 
 * packet is generated every pauseTime/2 until a BP "off" message is received.
 * <li> If configured to <b>generate but drop recieve</b>, all packets on 
 * input port will be dropped when PAUSE packets are transmitted 
 * on corresponding output port (default is to NOT drop packets). 
 * <ul> 
 * </ul>
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] pauseEnable  Pointer to an instance of ncp_bool_t that indicates
 * the state of the pauseType configuration.
 * @param[in] pauseType  The type PAUSE that we are retrieving the configuration of. 
 *            <ul>
 *            <li> #NCP_PAUSE_RESPOND = 0x01
 *            <li> #NCP_PAUSE_FILTER = 0x02
 *            <li> #NCP_PAUSE_FORWARD = 0x04
 *            <li> #NCP_PAUSE_GENERATE = 0x08
 *            <li> #NCP_PAUSE_GENERATE_DROP_RX = 0x10
 *            </ul>
 * @param[out] pauseTime  Pointer to an instance of ncp_uint16_t which is the 
 * MAC PAUSE Quanta time set for generating PAUSE packets to the network.
 *
 * @return <ul>
 * 	<li> #NCP_ST_SUCCESS
 * 	<li> #NCP_ST_INVALID_HANDLE
 * 	<li> #NCP_ST_DEV_INVALID_HANDLE
 * 	<li> #NCP_ST_INVALID_VALUE
 * 	<li> #NCP_ST_EIOA_INVALID_BUFFER
 * 	<li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 * 	<li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 * 	<li> #NCP_ST_MAC_INVALID_MAC
 * 	</ul>
 */

NCP_API ncp_st_t
ncp_eioa_mac_flow_ctrl_get(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_bool_t *pauseEnable,
    ncp_uint32_t pauseType,
    ncp_uint16_t *pauseTime);

/*!
 * @ingroup _eioa_mac_
 * @brief This API returns port link status for the specified macChan.
 * <br> Supports all ACP chiptypes.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *phyStatus  Pointer to an instance of ncp_mac_phy_status_t_t 
 * that indicates the state of the pauseType configuration.
 * @param[out] *link_mask Pointer to an instance of ncp_uint32_t that  
 * returns a link_mask value. 
 *
 * For AXM55xx and AXM35xx - The information is returned in ncp_mac_phy_status_t_t
 * structure (phyStatus) and link_mask value will be NULL.
 *
 *            <ul>
 *            <li> NCP_PORT_PHY_AN_COMPLETE = 0x01
 *            <li> NCP_PORT_PHY_REMOTE_FAULT = 0x02
 *            <li> NCP_PORT_PHY_DUPLEX = 0x04
 *            <li> NCP_PORT_PHY_SPEED = 0x18
 *            <li> NCP_PORT_PHY_LINK_STATUS = 0x20
 *            <li> NCP_PORT_PHY_CONFIGURED = 0x40
 *            </ul>
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_INVALID_VALUE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_mac_link_status_get(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_mac_phy_status_t *phyStatus,
             ncp_uint32_t *link_mask);

/*!
 * @ingroup _eioa_mac_
 * @brief This API blocks on a link status change for the specified macChan.
 * <br> Supports all ACP chiptypes.
 * @details 
 * The calling process/thread is put to sleep until a link state change occurs
 * for the requested state that is set by the <b>link_mask</b> parameter. 
 * Any or all link state changes for a given macChan can be requested via the 
 * <b>mask</b> value. Upen detecting a link state change, the <b>phyStatus</b>
 * and the <b>link_mask</b> will be updated with the lastest link state and
 * returned to the caller. 
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *phyStatus  Pointer to an instance of ncp_mac_phy_status_t_t 
 * that indicates the state of the pauseType configuration.
 * @param[in/out] *link_mask Pointer to an instance of ncp_uint32_t that 
 * contains a passed in link_mask value that the process process is interested
 * in, and a returned link_mask value when a link state changed is detected.
 *            <ul>
 *            <li> NCP_PORT_PHY_AN_COMPLETE = 0x01
 *            <li> NCP_PORT_PHY_REMOTE_FAULT = 0x02
 *            <li> NCP_PORT_PHY_DUPLEX = 0x04
 *            <li> NCP_PORT_PHY_SPEED = 0x18
 *            <li> NCP_PORT_PHY_LINK_STATUS = 0x20
 *            <li> NCP_PORT_PHY_CONFIGURED = 0x40
 *            </ul>
 *
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_INVALID_VALUE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_mac_link_status_get_blocking(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_mac_phy_status_t *phyStatus,
             ncp_uint32_t *link_mask);


/*!
 * @ingroup _eioa_port_
 * @brief Retrieve the overclock settings for an EIOA and EIOA slot.
 * @details
 * Return the overclock speed and duplex settings for an EIOA and slot. 
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] eioaNum The ncp_eioa_num_t for given device.  
 * @param[in] eioaSlot The ncp_eioa_slot_t for given EIOA. Only #NCP_EIOA_SLOT1 
 * is valid.  
 * @param[out] *speed Pointer to and instace of ncp_mac_speed_t
 * @param[out] *duplex Pointer to and instance of ncp_bool_t
 * @param[out] *flags Pointer to an instance of ncp_uint32_t
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 */

NCP_API ncp_st_t
ncp_eioa_slot_overclock_get(
             ncp_hdl_t     hdl,
             ncp_eioa_num_t eioaNum,
             ncp_eioa_slot_t eioaSlot,
             ncp_mac_speed_t *speed,
             ncp_bool_t *duplex,
             ncp_uint32_t *flags);


/*!
 * @ingroup _eioa_port_
 * @brief Configures all the SGMII ports within an EIOA slot to run in an 
 * overclocked mode.
 * @details
 * This function shall overclock all the SGMII ports within an EIOA slot. The 
 * overclocked rate for transmitting Ethernet frames is 2.5 gigabits per 
 * second (2.5 GigE). <br>
 * This function can also be used to set the SGMII ports within an EIOA slot to
 * a normal clocking mode of 1 gigbit per second.   <br>
 * Autonegotiation will be disabled and speed/duplex settings shall be set
 * manually. <br>
 * <br> The speed setting of #NCP_MAC_PHY_SPEED2_5G shall be used for the 
 * overclocked mode. Overclocking is functional for Fiber mode only. <br>An
 * #NCP_ST_MAC_SPEED_REQUIRES_FIBER error will be returned of Fiber mode is 
 * not set at config time.   
 * All lesser speed settings shall be used for the normal clocked mode. 
 * <br>The speed setting of #NCP_MAC_PHY_SPEED2_5G shall set the EIOA 
 * overClock2_5G flag and affects all the ports in an EIOA slot. 
 * (i.e - All ports must run at 2.5G due to overclocking).
 * <ul> <b> SLOT to PORT Mappings </b>
 *    <li> #NCP_EIOA0
 *    <ul>
 *        <li> #NCP_EIOA_SLOT0
 *        <ul>
 *            <li> #NCP_XGMAC0
 *        </ul>
 *        <li> #NCP_EIOA_SLOT1
 *        <ul>
 *            <li> #NCP_GMAC1
 *            <li> #NCP_GMAC2
 *            <li> #NCP_GMAC3
 *            <li> #NCP_GMAC4
 *        </ul>
 *    </ul>
 *    <li> #NCP_EIOA1
 *    <ul>
 *        <li> #NCP_EIOA_SLOT0
 *        <ul>
 *            <li> #NCP_XGMAC8
 *        </ul>
 *        <li> #NCP_EIOA_SLOT1
 *        <ul>
 *            <li> #NCP_GMAC9
 *            <li> #NCP_GMAC10
 *            <li> #NCP_GMAC11
 *            <li> #NCP_GMAC12
 *        </ul>
 *    </ul>
 * </ul>
 * <br>Overclocking is only valid when running in fiber mode. An error will 
 * be returned when the <b>isFiber</b> flag is not set in the configuration.
 * <br>The #NCP_MAC_PHY_SPEED10G rate are only valid for #NCP_XGMAC0 and
 * #NCP_XGMAC8.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] eioaNum The ncp_eioa_num_t for given device.  
 * @param[in] eioaSlot The ncp_eioa_slot_t for given EIOA. Only #NCP_EIOA_SLOT1 
 * is valid.  
 * @param[in] speed The ncp_mac_speed_t value for given port.
 * @param[in] duplex The ncp_bool_t boolean value for given port.
 * @param[in] flags The ncp_uint32_t type. Reserved for future use. 
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_MAC_SPEED_REQUIRES_FIBER
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 */

NCP_API ncp_st_t
ncp_eioa_slot_overclock_set(
             ncp_hdl_t     hdl,
             ncp_eioa_num_t eioaNum,
             ncp_eioa_slot_t eioaSlot,
             ncp_mac_speed_t speed,
             ncp_bool_t duplex,
             ncp_uint32_t flags);

/*!
 * @ingroup _eioa_mac_
 * @brief Perform MDIO read sequence from the  PHY at target PHY address
 *
 * @details
 * This function shall read the PHY register via the MDIO bus connected to
 * the EIOA port and place the value in given reg_val 
 * Supoorted for all chip types.
 * @param devHdl        - IN: NCP device handle.
 * @param macChan       - IN: EIOA port number specific to an EIOA.
 * @param reg_num       - IN: PHY registesr value
 * @param *reg_value    - OUT: Pointer to unsigned integer location to provide read data
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t 
ncp_eioa_phy_reg_get(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_uint32_t reg_num,
             ncp_uint32_t *reg_val);

/*!
 * @ingroup _eioa_mac_
 * @brief Perform MDIO write sequence to PHY at target PHY address
 * @details
 * This function shall program the PHY register via the MDIO bus connected to
 * the EIOA port with the given value 
 * Supoorted for all chip types.
 * @param devHdl        - IN: NCP device handle.
 * @param macChan       - IN: EIOA port number specific to an EIOA.
 * @param reg_num       - IN: PHY registesr value
 * @param reg_value     - IN: Unsigned integer to provide write data
 * @returns
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t 
ncp_eioa_phy_reg_set(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_uint32_t reg_num,
             ncp_uint32_t reg_val);

/*!
 * @ingroup _eioa_mac_
 * @brief Set the MAC or the Serdes to loopback.
 * <br> Supports ACP3400 X2 and AXM500 chiptypes.
 * @details 
 * This API allows the user to set the Serdes PHY or the MAC 
 * Channel to loopback.
 *
 * For ACp3400 and AXM5500, once called with any MAC channel, 
 * all the MACs for that EIOA slot is set to loopback since 
 * the loopback is set at the PTI level. This is only for MAC
 * loopback
 *
 * For Serdes and ACP3400, once set to loopback, the whole lane is 
 * set to loopback. 
 *
 * For Serdes and AXM5500, is based on the serdes lane and the MAC on 
 * that lane. The serdes PHY channel will be set to loopback where the 
 * MAC channel resides. To set the loopback, use GMACs and not XGMACs
 * for macChan attribute.
 * 
 * The followings are the loopbackType and their values.
 *     <ul>
 *       <li> 1 = NCP_MAC_LOOPBACK                   
 *       <li> 2 = NCP_SERDES_SERIAL_LOOPBACK    (ACP3400 ONLY)
 *       <li> 3 = NCP_SERDES_PARALLEL_LOOPBACK  (ACP3400 ONLY)
 *       <li> 2 = NCP_SERDES_INTERNAL_LOOPBACK  (AXM5500 ONLY: EIOA->HSS->EIOA)
 *       <li> 3 = NCP_SERDES_EXTERNAL_LOOPBACK  (AXM5500 ONLY: HSS->EIOA->HSS)
 *     </ul>
 *
 * NOTE: <b>NCP_SERDES_PARALLEL_LOOPBACK is not supported for ACP3400</b>
 *
 * @param devHdl        - IN: NCP device handle.
 * @param[in] macChan   - EIOA port number specific to an EIOA GMAC
 * @param loopbackType  - IN: an instance of ncp_loopback_t to determine the loopback type
 * @param enable        - IN: an instatnce of ncp_bool_t to enable (TRUE) or disable (FALSE) the loopback
 *
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_chan_loopback_set(
             ncp_hdl_t      hdl,
             ncp_macChan_t  macChan,
             ncp_loopback_t loopbackType,
             ncp_bool_t     enable);

/*!
 * @ingroup _eioa_
 * @brief Retrieve FEC (Forward Error Correction) Control Information
 * <br> Supports AXM5500 only chiptype.
 * @details
 * This API returns the configured values for fec setting.
 * 
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *fec_enable Pointer to an instance of ncp_bool_t to put
 *             that value of fec_enable. 
 *             TRUE = Enable FEC, FALSE = Disable FEC
 * @param[out] *fec_enable_err_ind Pointer to an instance of ncp_bool_t to put
 *             that value of fec_enable_err_ind.
 *             TRUE = Allow FEC decoder to indicate errors to the PCS layer 
 *             FALSE = Don't allow FEC decoder to indicate errors to the PCS layer 
 *
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_fec_get(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_bool_t *fec_enable,
    ncp_bool_t *fec_enable_err_ind);

/*!
 * @ingroup _eioa_
 * @brief Configure FEC Settings
 * <br> Supports AXM5500 only chiptype.
 * @details
 * This API configures values for FEC (Forward Error Correction) setting.
 * 
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *fec_enable Pointer to an instance of ncp_bool_t to put
 *             that value of fec_enable. 
 *             TRUE = Enable FEC, FALSE = Disable FEC
 * @param[out] *fec_enable_err_ind Pointer to an instance of ncp_bool_t to put
 *             that value of fec_enable_err_ind.
 *             TRUE = Allow FEC decoder to indicate errors to the PCS layer 
 *             FALSE = Don't allow FEC decoder to indicate errors to the PCS layer 
 *
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_fec_set(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_bool_t fec_enable,
    ncp_bool_t fec_enable_err_ind);

/*!
 * @ingroup _eioa_port_
 * @brief  Return the configuration for the maximum packet lenght of 
 * oversized packets on this EIOA/Channel
 * <br> Supports all ACP chiptypes.
 * @details
 * Return the configuration for the maximum packet lenght of oversized 
 * packets on this EIOA/Channel
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *maxPacketLength  Pointer to an instance of the ncp_uint16_t to hold 
 * the maximum packet size.
 *
 * @returns 
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_stats_max_pkt_length_get(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_uint16_t *maxPacketLength);

/*!
 * @ingroup _eioa_port_
 * @brief Write the maximum packet lenght of oversized packets on 
 * this EIOA/Channel
 * <br> Supports all ACP chiptypes.
 * @details
 * Write the maximum packet lenght of oversized packets on 
 * this EIOA/Channel
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] maxPacketLength  an instance of the ncp_uint16_t to hold 
 * the maximum packet size.
 *
 * @returns 
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_INVALID_VALUE
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 */

NCP_API ncp_st_t
ncp_eioa_stats_max_pkt_length_set(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_uint16_t maxPacketLength);

NCP_API ncp_st_t
ncp_eioa_mac_timer_shutdown(
    void           *hdl,
    ncp_macChan_t  macChan,
    ncp_uint32_t   flags);

NCP_API ncp_st_t
ncp_dev_eioa_destroy(ncp_dev_hdl_t devHdl);

NCP_API ncp_st_t
ncp_dev_eioa_AN_start(ncp_hdl_t hdl,
             ncp_macChan_t macChan,
             ncp_uint32_t flags);

NCP_API ncp_st_t
ncp_dev_eioa_AN_stop(ncp_hdl_t hdl,
             ncp_macChan_t macChan,
             ncp_uint32_t flags);

#if defined(NCP_EIOA_PORT_AN_TRACE)
NCP_API ncp_st_t 
ncp_mac_AN_trace(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_port_trace_t *port_trace,
             ncp_bool_t *port_cfg_ok);
#endif

NCP_API ncp_st_t
ncp_dev_nca_initiate_shutdown(ncp_dev_hdl_t devHdl);

#ifdef NCP_KERNEL
NCP_API void
ncp_dev_nca_taskio_write_reg32(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t  offset,
    ncp_uint32_t  val);
        
NCP_API void 
ncp_dev_nca_taskio_read_reg32(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t  offset,
    ncp_uint32_t  *pVal);
#endif
            
NCP_API ncp_st_t
ncp_dev_nca_wait_for_isr_wakeup(
    ncp_dev_hdl_t dev,
    ncp_uint32_t intrType, 
    ncp_uint8_t grp, 
    ncp_uint32_t grpRelQueueId,
    ncp_uint8_t  tqsID);

ncp_st_t ncp_dev_nca_grp_intr_disable(ncp_dev_hdl_t devHdl, 
        ncp_uint32_t type, 
        ncp_uint8_t grp);
            
ncp_st_t 
ncp_dev_nca_grp_intr_enable(ncp_dev_hdl_t devHdl, 
        ncp_uint32_t type, 
        ncp_uint8_t grp);
            
#ifdef __cplusplus
}
#endif

#endif /* __NCP_DEV_H__ */
