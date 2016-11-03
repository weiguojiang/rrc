/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


/*! @file       ncp_dev_i2c.h
 *  @brief      Constants, structs, and APIs used to communicate with the
 *              direct ACP I2C Hardware Layer registers
 */

#ifndef NCP_DEV_I2C_H
#define NCP_DEV_I2C_H

#include "ncp_dev_pvt.h"
#include "ncp_sal_types.h"
#include "regs/ncp_i2c_regs.h"

/*****************************************************************************
* Constants                                                                  *
*****************************************************************************/

    /*****************************
    * Common                     *
    *****************************/

/*! @def NCP_I2C_VALID_NODE
    @brief Macro to evaluate a node within a regionId for validity.
*/
#define NCP_I2C_VALID_NODE(rId)       \
    (NCP_I2C_VALID_NODE_ACP3400(rId) ||           \
     NCP_I2C_VALID_NODE_AXM5500(rId))

/*! @def NCP_I2C_VALID_NODE_ACP3400
    @brief Macro to evaluate a node within a regionId for validity.
*/
#define NCP_I2C_VALID_NODE_ACP3400(rId)       \
    ((NCP_NODE_ID(rId) == NCP_NODE_I2C_PROTOCOL)   ||           \
     (NCP_NODE_ID(rId) == NCP_NODE_I2C_1_PROTOCOL))

/*! @def NCP_I2C_VALID_NODE_AXM5500
    @brief Macro to evaluate a node within a regionId for validity.
*/
#define NCP_I2C_VALID_NODE_AXM5500(rId)       \
    ((NCP_NODE_ID(rId) == NCP_NODE_I2C_PROTOCOL)   ||           \
     (NCP_NODE_ID(rId) == NCP_NODE_I2C_1_PROTOCOL) ||           \
     (NCP_NODE_ID(rId) == NCP_NODE_I2C_2_PROTOCOL) ||           \
     (NCP_NODE_ID(rId) == NCP_NODE_SMB_0_PROTOCOL))

/*! @def NCP_I2C_VALID_TARGET
    @brief Macro to evaluate a target within a regionId for validity.
*/
#define NCP_I2C_VALID_TARGET(rId)       (NCP_TARGET_ID(rId) <= 0x3FF)

/*! @def NCP_I2CPROT_MAX_XFR_SIZE
    @brief Maximum number of bytes that may be moved at one time over the
           I2C bus.
*/
#define NCP_I2CPROT_MAX_XFR_SIZE           8

/*! @def NCP_I2CPROT_MAX_BUF_SIZE
    @brief Maximum number of bytes that may be stored at one time over
           the I2C bus i.e. size of TXD0+TXD1.
*/
#define NCP_I2CPROT_MAX_BUF_SIZE           8

#define NCP_I2C_CHECK_COUNT           0x1000
        /* Max number of  tries at looking for an I/O success */

#define NCP_I2C_SMB_CHECK_COUNT       (0x1000 * 0x2000)
        /* Max number of  tries at looking for an SMB I/O success */

    /*****************************
    * ACP3400                    *
    *****************************/

/*! @def NCP_I2CPROT_MAX_XFR_BOUND
    @brief Value mask that is anded with any I2C offset to determine a
           write transfer boundary.  If a transfer is going to cross this
           byte boundary, it should be broken into two smaller write
           transactions before and after the boundary.
*/
#define NCP_I2CPROT_MAX_XFR_BOUND          (NCP_I2CPROT_MAX_XFR_SIZE-1)

/*
 * Device-specific macros and tests for command manipulation
 */
#define NCP_I2CPROT_MASK_TENBIT_ENABLE           (0x0001)
#define NCP_I2CPROT_MASK_TENBIT_DISABLE          (0x0002)
#define NCP_I2CPROT_MASK_TENBIT_CONSECUTIVE      (0x0004)

#define TENBIT_SETENABLED(ioc)       {(ioc)->tenBitMode = NCP_I2CPROT_MASK_TENBIT_ENABLE;}
#define TENBIT_SETDISABLED(ioc)      {(ioc)->tenBitMode = NCP_I2CPROT_MASK_TENBIT_DISABLE;}
#define TENBIT_SETCONSECUTIVE(ioc)   {(ioc)->tenBitMode |= NCP_I2CPROT_MASK_TENBIT_CONSECUTIVE;}
#define TENBIT_CLRCONSECUTIVE(ioc)   {(ioc)->tenBitMode &= ~NCP_I2CPROT_MASK_TENBIT_CONSECUTIVE;}
#define TENBIT_IFENABLED(ioc)        ((ioc)->tenBitMode & NCP_I2CPROT_MASK_TENBIT_ENABLE)
#define TENBIT_IFDISABLED(ioc)       ((ioc)->tenBitMode & NCP_I2CPROT_MASK_TENBIT_DISABLE)
#define TENBIT_IFCONSECUTIVE(ioc)    ((ioc)->tenBitMode & NCP_I2CPROT_MASK_TENBIT_CONSECUTIVE)

#define DEV_10BIT_AUTO(ioc)          TENBIT_SETENABLED(ioc)


/*
 * Application-specific (BUS) timing constants, types, etc.
 */

#define CFG_CLK_CONFIG_SCL_LOW        (1000) /* (MCC-0x143.0x0.0x1c) - bits 9:0 (MCC LPD) */
 
#define CFG_CLK_CONFIG_SCL_HIGH       (1000) /* (MCC-0x143.0x0.0x1c) - bits 25:16 (MCC HPD) */

#define CFG_START_SETUP_PERIOD        (940)  /* (MSTSHC-0x143.0x0.0x20) - bits 9:0 (MSTSHC SETDU) */

#define CFG_START_HOLD_PERIOD         (800)  /* (MSTSHC-0x143.0x0.0x20) - bits 25:16 (MSTSHC HLDDU) */

#define CFG_STOP_SETUP_PERIOD         (800)  /* (MSPSHC-0x143.0x0.0x24) - bits 9:0 (MSPSHC SETDU) */

#define CFG_STOP_HOLD_PERIOD          (0)    /* (MSPSHC-0x143.0x0.0x24) - bits 25:16 (MSPSHC HLDDU) */

#define CFG_DATA_SETUP_PERIOD         (50)   /* (MDSHC-0x143.0x0.0x28) - bits 9:0 (MDSHC SETDU) */

#define CFG_DATA_HOLD_PERIOD          (0)    /* (MSPSHC-0x143.0x0.0x28) - bits 25:16 (MDSHC HLDDU) */


/*! @def NCP_I2C_IOCONFIG_READ_DEFAULT
 *  @brief Easy default initialization for ncp_i2cprot_config_acp3400_t.readTiming.
 */
#define NCP_I2C_IOCONFIG_READ_DEFAULT \
    { \
    CFG_CLK_CONFIG_SCL_HIGH, \
    CFG_CLK_CONFIG_SCL_LOW, \
    CFG_START_SETUP_PERIOD, \
    CFG_START_HOLD_PERIOD, \
    CFG_STOP_SETUP_PERIOD, \
    CFG_STOP_HOLD_PERIOD, \
    CFG_DATA_SETUP_PERIOD, \
    CFG_DATA_HOLD_PERIOD, \
    }

/*! @def NCP_I2C_IOCONFIG_WRITE_DEFAULT
 *  @brief Easy default initialization for ncp_i2cprot_config_acp3400_t.writeTiming.
 */
#define NCP_I2C_IOCONFIG_WRITE_DEFAULT \
    { \
    CFG_CLK_CONFIG_SCL_HIGH, \
    CFG_CLK_CONFIG_SCL_LOW, \
    CFG_START_SETUP_PERIOD, \
    CFG_START_HOLD_PERIOD, \
    CFG_STOP_SETUP_PERIOD, \
    CFG_STOP_HOLD_PERIOD, \
    CFG_DATA_SETUP_PERIOD, \
    CFG_DATA_HOLD_PERIOD, \
    }

#define NCP_I2C_IOCONFIG_WAITPOSTWRITE_DEFAULT    (5000) /* 5ms for each */
#define NCP_I2C_IOCONFIG_WAITPOSTREAD_DEFAULT     (0)    /* 0ms for each */


/*! @enum ncp_i2c_operation_t
    @brief Operation handles passed as arguments to selected callback functions
*/
typedef enum
{
    NCP_I2C_WRITE_TRANS = 0,    /*!< Write transaction tag */
    NCP_I2C_READ_TRANS  = 1     /*!< Read transaction tag */
} ncp_i2cprot_operation_t;



/*****************************************************************************
* Type definitions                                                           *
*****************************************************************************/

    /*********************************************
     * Common Protocol State & Callbacks
     ********************************************/

struct ncp_i2c_region_s;
typedef struct ncp_i2c_region_s ncp_i2c_region_t;

/*! @typedef ncp_dev_i2c_block_write8_t
    @brief Signature for callback function that may be called from I2C
           protocol read/write operations to write 8-bit data to the
           target device.
    @param[in] dev Device handle
    @param[in] i2cRegion Node+target reference
    @param[in] inOffset Byte offset to write location
    @param[in] buffer   Data to written supplied by caller
    @param[in] count    number of bytes in the write transfer
    @param[in] flags    Other operation flags
    @returns success/failure of operation
*/
typedef ncp_st_t (*ncp_dev_i2c_block_write8_t)(
    ncp_dev_hdl_t    *dev,
    ncp_i2c_region_t *i2cRegion,
    ncp_uint32_t      offset,
    ncp_uint8_t      *buffer,
    ncp_uint32_t      count,
    ncp_uint32_t      flags);

/*! @typedef ncp_dev_i2c_block_read8_t
    @brief Signature for callback function that may be called from I2C
           protocol read/write operations to read 8-bit data from the
           target device.
    @param[in] dev Device handle
    @param[in] i2cRegion Node+target reference
    @param[in] inOffset Byte offset to read location
    @param[in] buffer   Where to place the data read from device
    @param[in] count    number of bytes in the read transfer
    @param[in] flags    Other operation flags
    @returns success/failure of operation
*/
typedef ncp_st_t (*ncp_dev_i2c_block_read8_t)(
    ncp_dev_hdl_t    *dev,
    ncp_i2c_region_t *i2cRegion,
    ncp_uint32_t      offset,
    ncp_uint8_t      *buffer,
    ncp_uint32_t      count,
    ncp_uint32_t      flags);

struct ncp_i2c_region_s
{
    void                       *config;
    ncp_uint32_t                seekPos;
    ncp_region_id_t             regionId;
    ncp_uint32_t                i2cRegionId;
    ncp_uint32_t                tenBitMode;
                                /*!< Use 10-bit addressing mode.  See constants
                                 * NCP_I2CPROT_MASK_TENBIT_xxx above. */
    ncp_uint32_t                maxXfrSize;
                                /*!< Maximum number of bytes for a single
                                 * data transfer */
    ncp_uint32_t                deviceLen;
                                /*!< Maximum number of bytes / seek location
                                 * where 0 means ignore this setting */
    ncp_dev_i2c_block_write8_t  wrFn;
    ncp_dev_i2c_block_read8_t   rdFn;
};

struct  ncp_TreeNode_s;
typedef struct ncp_TreeNode_s *ncp_Position;
typedef struct ncp_TreeNode_s *ncp_BinTree;

typedef struct ncp_TreeNode_s
{
    ncp_i2c_region_t *Element;
    ncp_BinTree       Left;
    ncp_BinTree       Right;
} ncp_TreeNode;

#define ELEMENT_KEY(p)          (p->regionId)

/*! @fn ncp_i2c_region_t* ncp_i2c_MakeElement(void *config, ncp_uint32_t seekPos, ncp_region_id_t regionId, ncp_uint32_t i2cRegionId);
 @brief Support fn that allocates memory to track state of I2C protocol engines
 @param[in] config: chip-specific state structure reference
 @param[in] seekPos: initial position of 'seek' reference
 @param[in] regionId: ACP region id matching this protocol
 @param[in] i2cRegionId: ACP I2C stream protocol handle
 @returns
*/
NCP_API
ncp_i2c_region_t*
ncp_dev_i2c_MakeElement(
    void                 *config,
    ncp_uint32_t          seekPos,
    ncp_region_id_t       regionId,
    ncp_uint32_t          i2cRegionId);


/*! @struct ncp_dev_i2c_state_t
    @brief Runtime state for the I2C protocol that should be retained on
           a per-NCP device basis.
*/
typedef struct
{
    ncp_bool_t                  tmrInitDone;
    ncp_BinTree                 regionProtoList;
} ncp_dev_i2c_state_t;

    /*********************************************
     * ACP3400-like I2C Devices Definitions, etc.
     ********************************************/

/*! @typedef ncp_i2cprot_setup_xmt_cfg_t
    @brief Signature for callback function that may be called from I2C
           read/write operations to get custom formatting of the MAST_XMT_CFG
           register for the operation.  This function returns ((ncp_st_t)-1)
           to indicate that the write of the command register may be skipped
           without aborting the operation.  This function may not perform I/O
           to the NCP or I2C devices.
    @param[in] inOp read or write operation code
    @param[in] inSlaveId Target device slave id
    @param[in] inOffset byte offset to register
    @param[in] inNumBytes number of bytes in the read/write transfer
    @param[in,out] inOutCommand Value to be sent to command register
    @param[in] appData Application-specific data passed to callback function
    @returns success/failure of operation
*/
typedef ncp_st_t (*ncp_i2cprot_setup_xmt_cfg_t)(
    ncp_i2cprot_operation_t inOp,
    ncp_uint32_t        inSlaveId,
    ncp_uint32_t        inOffset,
    ncp_uint32_t        inNumBytes,
    ncp_uint32_t       *inOutCommand,
    ncp_i2c_region_t   *appData);

/*! @typedef ncp_i2cprot_setup_rcv_cfg_t
    @brief Signature for callback function that may be called from I2C
           read/write operations to get custom formatting of the MAST_RCV_CFG
           register for the operation.  This function return ((ncp_st_t)-1)
           to indicate that the write of the command register may be skipped
           without aborting the operation.  This function may not perform I/O
           to the NCP or I2C devices.
    @param[in] inOp read or write operation code
    @param[in] inSlaveId Target device slave id
    @param[in] inOffset byte offset to register
    @param[in] inNumBytes number of bytes in the read/write transfer
    @param[in,out] inOutCommand Value to be sent to command register
    @param[in] appData Application-specific data passed to callback function
    @returns success/failure of operation
*/
typedef ncp_st_t (*ncp_i2cprot_setup_rcv_cfg_t)(
    ncp_i2cprot_operation_t inOp,
    ncp_uint32_t        inSlaveId,
    ncp_uint32_t        inOffset,
    ncp_uint32_t        inNumBytes,
    ncp_uint32_t       *inOutCommand,
    ncp_i2c_region_t   *appData);

/*! @typedef ncp_i2cprot_setup_slv_addr_t
    @brief Signature for callback function that may be called from I2C
           read/write operations to custom format the MAST_SLV_ADDRESS
           register for the operation.  This function return ((ncp_st_t)-1)
           to indicate that the write of the command register may be skipped
           without aborting the operation.  This function may not perform I/O
           to the NCP or I2C devices.
    @param[in] inOp read or write operation code
    @param[in] inSlaveId Target device slave id
    @param[in] inOffset byte offset to register
    @param[in] inNumBytes number of bytes in the read/write transfer
    @param[in,out] inOutCommand Image of the command bytes to be transferred
    @param[in] appData Application-specific data passed to callback function
    @returns success/failure of operation
*/
typedef ncp_st_t (*ncp_i2cprot_setup_slv_addr_t)(
    ncp_i2cprot_operation_t inOp,
    ncp_uint32_t        inSlaveId,
    ncp_uint32_t        inOffset,
    ncp_uint32_t        inNumBytes,
    ncp_uint32_t       *inOutCommand,
    ncp_i2c_region_t   *appData);


/*! @struct ncp_i2cprot_ioconfig_t
    @brief  Timing Control Configuration for I2C registers
*/
typedef struct
{
    ncp_uint32_t clkPulseWidthHigh:10;
                     /*!< Number of pclk durations that equal
                      * high period of SCL*/
    ncp_uint32_t clkPulseWidthLow:10;
                     /*!< Number of pclk durations that equal
                      * low period of SCL */
    ncp_uint32_t startSetupTime:10;
                     /*!< Number of pclk durations that equal
                      * setup condition on SDA */
    ncp_uint32_t startHoldTime:10;
                     /*!< Number of pclk durations that equal
                      * hold condition on SDA */
    ncp_uint32_t stopSetupTime:10;
                     /*!< Number of pclk durations that equal
                      * stop condition on SDA */
    ncp_uint32_t stopHoldTime:10;
                     /*!< Number of pclk durations that equal
                      * setup condition on SDA */
    ncp_uint32_t dataSetupTime:10;
                     /*!< Number of pclk durations that equal
                      * setup condition on SDA for data changing*/
    ncp_uint32_t dataHoldTime:10;
                     /*!< Number of pclk durations that equal
                      * hold condition on SDA for data changing*/
} ncp_i2cprot_ioconfig_t;


/*! @struct ncp_i2cprot_config_acp3400_t
    @brief  Configuration state argument for calls to ncp_i2cprot_config()
           NULL timing array pointers will be skipped.
           NULL function pointers will be skipped.
*/
typedef struct
{
    ncp_uint32_t            maxXfrSize;
                              /*!< Maximum number of bytes for a single
                               * data transfer */
    ncp_uint32_t            deviceLen;
                              /*!< Maximum number of bytes / seek location
                               * where 0 means ignore this setting */
    ncp_uint32_t            waitPostRead;
                              /*!< Number of usecs to wait after performing
                               * a read operation */
    ncp_uint32_t            waitPostWrite;
                              /*!< Number of usecs to wait after performing
                               * a write operation */
    ncp_uint32_t            tenBitMode;
                              /*!< Use 10-bit addressing mode.  See constants
                               * NCP_I2CPROT_MASK_TENBIT_xxx above. */
    ncp_i2cprot_ioconfig_t *readTiming;
                              /*!< Custom I2C block Timing for read operations */
    ncp_i2cprot_ioconfig_t *writeTiming;
                              /*!< Custom I2C block Timing for write operations*/
    ncp_i2cprot_setup_xmt_cfg_t xmtCfgFn;
                              /*!< Callback function for I2C data read/write
                               * to modify value to be written to MAST_XMT_CFG */
    ncp_i2cprot_setup_rcv_cfg_t rcvCfgFn;
                              /*!< Callback function for I2C data read/write
                               * to modify value to be written to MAST_RCV_CFG */
    ncp_i2cprot_setup_slv_addr_t slvAddrFn;
                              /*!< Callback function for I2C data read/write
                               * to modify value to be written to MAST_SLV_ADDRESS reg */
    void                    *appData;
                              /*!< User data pointer passed to the callback fns */
} ncp_i2cprot_config_acp3400_t;


    /*********************************************
     * AXM5500-like I2C Devices Definitions, etc.
     ********************************************/


    /*********************************************
     * ACP3400-specific Callbacks, etc.
     ********************************************/

/*! @fn ncp_st_t ncp_dev_i2c_device_init_acp3400(ncp_dev_hdl_t inDevHdl, ncp_bool_t inInit);
    @brief I2C on ACP3400-like devices timer & reset initialiation
    @param[in] inDevHdl Reference to device handle structure
    @param[in] inInit   Re-Initialize even if already running
    @returns success/failure of operation
*/
NCP_API
ncp_st_t ncp_dev_i2c_device_init_acp3400(
    ncp_dev_hdl_t      *inDevHdl,
    ncp_bool_t          inInit);

/*! @fn ncp_i2c_region_t* ncp_dev_i2cprot_setup_acp3400(ncp_dev_hdl_t inDevHdl, ncp_region_id_t inRegionId);
    @brief This function will fill/overwrite a custom protocol entry
           for the specified I2C region appropriate to the ACP3400-
           like devices.
    @param[in] inDevHdl   Reference to device handle structure
    @param[in] inRegionId ID of the region/slave address with which to associate
                         the new configuration
    @Returns pointer to runtime protocol state to be used to manage
                     the protocol for this device
*/
NCP_API
ncp_i2c_region_t* ncp_dev_i2cprot_setup_acp3400(
    ncp_dev_hdl_t        *inDevHdl,
    ncp_region_io_t      *inRegionId);

/*! @fn ncp_st_t ncp_dev_i2c_block_write8_acp3400
    @brief ACP3400-specific callback function that may be called from I2C
           protocol read/write operations to write 8-bit data to the
           target device.
    @param[in] dev Device handle
    @param[in] i2cRegion Node+target reference
    @param[in] inOffset Byte offset to write location
    @param[in] buffer   Data to written supplied by caller
    @param[in] count    number of bytes in the write transfer
    @param[in] flags    Other operation flags
    @Returns Reference to runtime protocol state to be used to manage
             the protocol for this device
*/
NCP_API
ncp_st_t ncp_dev_i2c_block_write8_acp3400(
    ncp_dev_hdl_t    *dev,
    ncp_i2c_region_t *i2cRegion,
    ncp_uint32_t      offset,
    ncp_uint8_t      *buffer,
    ncp_uint32_t      count,
    ncp_uint32_t      flags);

/*! @fn ncp_st_t ncp_dev_i2c_block_read8_acp3400
    @brief ACP3400-specific callback function that may be called from I2C
           protocol read/write operations to read 8-bit data from the
           target device.
    @param[in] dev Device handle
    @param[in] i2cRegion Node+target reference
    @param[in] inOffset Byte offset to read location
    @param[in] buffer   Where to place the data read from device
    @param[in] count    number of bytes in the read transfer
    @param[in] flags    Other operation flags
    @returns success/failure of operation
*/
NCP_API
ncp_st_t ncp_dev_i2c_block_read8_acp3400(
    ncp_dev_hdl_t    *dev,
    ncp_i2c_region_t *i2cRegion,
    ncp_uint32_t      offset,
    ncp_uint8_t      *buffer,
    ncp_uint32_t      count,
    ncp_uint32_t      flags);

    /*********************************************
     * AXM5500-specific Callbacks, etc.
     ********************************************/

/*! @fn ncp_st_t ncp_dev_i2c_device_init_axm5500(ncp_dev_hdl_t inDevHdl, ncp_bool_t inInit);
    @brief I2C on axm5500-like devices timer & reset initialiation
    @param[in] inDevHdl Reference to device handle structure
    @param[in] inInit   Re-Initialize even if already running
    @returns success/failure of operation
*/
NCP_API
ncp_st_t ncp_dev_i2c_device_init_axm5500(
    ncp_dev_hdl_t      *inDevHdl,
    ncp_bool_t          inInit);

/*! @fn ncp_i2c_region_t* ncp_dev_i2cprot_setup_axm5500(ncp_dev_hdl_t inDevHdl, ncp_region_id_t inRegionId);
    @brief This function will fill/overwrite a custom protocol entry
           for the specified I2C region appropriate to the axm5500-
           like devices.
    @param[in] inDevHdl   Reference to device handle structure
    @param[in] inRegionId ID of the region/slave address with which to associate
                         the new configuration
    @Returns Reference to runtime protocol state to be used to manage
             the protocol for this device
*/
NCP_API
ncp_i2c_region_t* ncp_dev_i2cprot_setup_axm5500(
    ncp_dev_hdl_t        *inDevHdl,
    ncp_region_io_t      *inRegionId);

/*! @fn ncp_st_t ncp_dev_i2c_block_write8_axm5500
    @brief axm5500-specific callback function that may be called from I2C
           protocol read/write operations to write 8-bit data to the
           target device.
    @param[in] dev Device handle
    @param[in] i2cRegion Node+target reference
    @param[in] inOffset Byte offset to write location
    @param[in] buffer   Data to written supplied by caller
    @param[in] count    number of bytes in the write transfer
    @param[in] flags    Other operation flags
    @returns success/failure of operation
*/
NCP_API
ncp_st_t ncp_dev_i2c_block_write8_axm5500(
    ncp_dev_hdl_t    *dev,
    ncp_i2c_region_t *i2cRegion,
    ncp_uint32_t      offset,
    ncp_uint8_t      *buffer,
    ncp_uint32_t      count,
    ncp_uint32_t      flags);

/*! @fn ncp_st_t ncp_dev_i2c_block_read8_axm5500
    @brief axm5500-specific callback function that may be called from I2C
           protocol read/write operations to read 8-bit data from the
           target device.
    @param[in] dev Device handle
    @param[in] i2cRegion Node+target reference
    @param[in] inOffset Byte offset to read location
    @param[in] buffer   Where to place the data read from device
    @param[in] count    number of bytes in the read transfer
    @param[in] flags    Other operation flags
    @returns success/failure of operation
*/
NCP_API
ncp_st_t ncp_dev_i2c_block_read8_axm5500(
    ncp_dev_hdl_t    *dev,
    ncp_i2c_region_t *i2cRegion,
    ncp_uint32_t      offset,
    ncp_uint8_t      *buffer,
    ncp_uint32_t      count,
    ncp_uint32_t      flags);

/*****************************************************************************
* Externally Visible Function Prototypes                                     *
*****************************************************************************/

/*! @fn ncp_st_t ncp_dev_i2cprot_init(ncp_dev_hdl_t inDevHdl);
    @brief This is a one time initialization for the I2C protocol
           layers to be called by the chip device initialization step.
    @param[in] inDevHdl Reference to device handle structure
    @Returns success/failure status of the operation
*/
NCP_API ncp_st_t
ncp_dev_i2cprot_init(
    ncp_dev_hdl_t   *inDev);

/*! @fn ncp_st_t ncp_dev_i2cprot_block_read8(ncp_dev_hdl_t *inDev,
                     ncp_region_io_t *inRegion, ncp_uint64_t inOffset,
                     ncp_uint8_t *inBuffer, ncp_uint32_t inCount,
                     ncp_uint32_t inFlags);
  @brief Read num bytes from the offset and store it in buffer.
  @param[in] dev:    handle of device to access
  @param[in] region: region / slave address to access
  @param[in] offset: Offset into device to address
  @param[in] buffer: Read data will be stored this buffer
  @param[in] count:  Number of bytes to be read.
  @param[in] flags:  Extra flags to pass to low-level device I/O functions
  @Returns success/failure completion status
*/
NCP_API ncp_st_t
ncp_dev_i2cprot_block_read8(
    ncp_dev_hdl_t   *inDev,
    ncp_region_io_t *inRegion,
    ncp_uint64_t     inOffset,
    ncp_uint8_t     *inBuffer,
    ncp_uint32_t     inCount,
    ncp_uint32_t     inFlags);

/*! @fn ncp_st_t ncp_dev_i2cprot_block_write8(ncp_dev_hdl_t *inDev,
                     ncp_region_io_t *inRegion, ncp_uint64_t inOffset,
                     ncp_uint8_t *inBuffer, ncp_uint32_t inCount,
                     ncp_uint32_t inFlags);
  @brief Write num bytes to the offset from buffer contents.
  @param[in] dev:    handle of device to access
  @param[in] region: region / slave address to access
  @param[in] offset: Offset into device to address
  @param[in] buffer: Read data will be stored this buffer
  @param[in] count:  Number of bytes to be read.
  @param[in] flags:  Extra flags to pass to low-level device I/O functions
  @Returns success/failure completion status
*/
NCP_API ncp_st_t
ncp_dev_i2cprot_block_write8(
    ncp_dev_hdl_t   *inDev,
    ncp_region_io_t *inRegion,
    ncp_uint64_t     inOffset,
    ncp_uint8_t     *outBuffer,
    ncp_uint32_t     inCount,
    ncp_uint32_t     inFlags);

/*! @fn ncp_st_t ncp_dev_i2cprot_destroy(ncp_dev_hdl_t inDevHdl);
    @brief This function will release resources acquired for the specified
           I2C region.
    @param[in] inDevHdl Reference to device handle structure
    @Returns success/failure status of the operation
*/
NCP_API
ncp_st_t ncp_dev_i2cprot_destroy(
    ncp_dev_hdl_t        *inDevHdl);



#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif   /* defined(NCP_DEV_I2C_H) */
