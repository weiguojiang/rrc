/***************************************************************************
 **                                                                        *
 **                           Intel CONFIDENTIAL                             *
 **                                                                        *
 **                       PROPRIETARY NOTE                                 *
 **                                                                        *
 **    This software contains information confidential and proprietary     *
 **    to Intel Corporation.  It shall not be reproduced in whole or in  *
 **    part, or transferred to other documents, or disclosed to third      *
 **    parties, or used for any purpose other than that for which it was   *
 **    obtained, without the prior written consent of Intel Corporation. *
 **    (c) 2009-2014, Intel Corporation.  All rights reserved.           *
 **                                                                        *
 **************************************************************************/
/*! @file ncp_i2c_amc_bus.h
 *  @brief Constants, structs, and APIs to communicate with AMC bus devices
 */

#ifndef NCP_I2C_AMC_BUS_H
#define NCP_I2C_AMC_BUS_H

#include "ncp.h"
#include "regs/ncp_i2c_sysfpga_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @defgroup _i2c_amc_bus_  AMC Bus devices
 * @brief     I2C AMC Bus devices (i2camcbus)
 * @{
 * @ingroup   _i2c_
 */

/*****************************************************************************
* Macros & Constants                                                         *
*****************************************************************************/

/*! @def NCP_I2C_AMC_BUS_SLAVE_ADDRESS(mux,i2c8bit)
 *  @brief Construct a single, combined slave address value from the desired values to be programmed into the System FPGA 'Mux Control' and 'Master Slave Address' registers
 */
#define NCP_I2C_AMC_BUS_SLAVE_ADDRESS(mux,i2c8bit) \
        (((mux) << 16) | ((i2c8bit) & 0xffff))

/*! @def NCP_I2C_AMC_BUS_SLOT_ID(target)
 *  @brief Extract MUX Control setting from combined address value
 */
#define NCP_I2C_AMC_BUS_SLOT_ID(target) \
        (((target) >> 16) & 0xffff)

/*! @def NCP_I2C_AMC_BUS_8BIT_ID(target)
 *  @brief Extract I2C Master Address setting (for secondary I2C bus) from combined address value
 */
#define NCP_I2C_AMC_BUS_8BIT_ID(target) \
        ((target) & 0xffff)

/*! @def NCP_I2C_ADDR_AMC_DEFAULT_SLOT
 *  @brief Default AMC MUX Control selection
 */
#define NCP_I2C_ADDR_AMC_DEFAULT_SLOT   NCP_I2C_SYSFPGA_MUX_AMC_SLOT_1

/*! @def NCP_I2C_ADDR_AMC_DEFAULT_8BIT
 *  @brief Default 'Master Slave Address' selection
 */
#define NCP_I2C_ADDR_AMC_DEFAULT_8BIT   0

/*! @def NCP_I2C_AMC_BUS_SLAVE_ADDRESS_DEFAULT
 *  @brief Default setting for slave address/regionId + mux control
 */
#define NCP_I2C_AMC_BUS_SLAVE_ADDRESS_DEFAULT           \
        NCP_I2C_AMC_BUS_SLAVE_ADDRESS(0,0x80)

/*! @def NCP_I2C_AMC_BUS_IOFLAG_NONE
 *  @brief Default setting for bus open ioFlags
 */
#define NCP_I2C_AMC_BUS_IOFLAG_NONE           (0x00000000)

/*! @def NCP_I2C_AMC_BUS_IOFLAG_NOTIMECFG
 *  @brief Disable automatic time config by the read/write I/O calls
 *         for this protocol session.
 */
#define NCP_I2C_AMC_BUS_IOFLAG_NOTIMECFG      (0x00000001)

/*! @def NCP_I2C_AMC_BUS_IOFLAG_NOACK
 *  @brief Determines if a I2C Master in Three River FPGA will send an ACK or NACK in response to a byte read from
 *	slave. Set this for NACK. Default is ACK.
 */
#define NCP_I2C_AMC_BUS_IOFLAG_NOACK	(0x00000002)



/*****************************************************************************
 * Type definitions                                                          *
 *****************************************************************************/

/*! @def NCP_I2C_AMC_BUS_INVALID_HANDLE
   @brief Invalid device handle for comparison to returns from
          ncp_i2c_amc_bus_open()
*/
#define NCP_I2C_AMC_BUS_INVALID_HANDLE   ((void*)-1)

/*! @typedef ncp_i2c_amc_bus_hdl_t
   @brief I2C AMC BUS Handle
*/
typedef void* ncp_i2c_amc_bus_hdl_t;

/*! @struct ncp_i2c_amc_bus_config_t
   @brief Configuration structure for I2C AMC BUS Open calls
*/
typedef struct
{
    ncp_uint32_t        busNum; /*!< Bus/Node of the associated I2C device
                                 *   e.g. NCP_NODE_I2C, NCP_NODE_I2C_1 */
    ncp_uint32_t        ioFlags;/*!< Flags passed to I/O calls */
    ncp_uint32_t        slaveAddress;
                                /*!< Value put in MAST_SLV_ADDRESS.targSlvAddr
                                 * field unless overridden by callback.
                                 * Value of ~0 requests default setting */
    ncp_uint32_t        deviceLen;
                                /*!< Max # bytes to read / seek */
} ncp_i2c_amc_bus_config_t;


/*****************************************************************************
 * Externally Visible State                                                  *
 *****************************************************************************/


/*****************************************************************************
 * Externally Visible Function Prototypes                                    *
 *****************************************************************************/

/*! @fn ncp_st_t ncp_i2c_amc_bus_open(ncp_hdl_t inDevHdl, ncp_i2c_amc_bus_config_t *inFlags, ncp_i2c_amc_bus_hdl_t *outDevHdl)
    @brief Open the I2C region for the BUS device and initialize internal
           state for its use.
    @param[in] inDevHdl Incoming handle of the current NCP configuration
    @param[in] inFlags  Incoming argument state structure to configure access
                    to the I2C AMC BUS device
    @param[out] outDevHdl Outgoing handle to be used in other I2C AMC BUS device
                     calls when the open is successful
    @returns success/failure status of the operation
*/
NCP_API ncp_st_t
ncp_i2c_amc_bus_open(
    ncp_hdl_t                 inDevHdl,
    ncp_i2c_amc_bus_config_t *inFlags,
    ncp_i2c_amc_bus_hdl_t    *outDevHdl);

/*! @fn ncp_st_t ncp_i2c_amc_bus_close(ncp_i2c_amc_bus_hdl_t inDevHdl)
    @brief Close/disconnect access to the I2C AMC BUS device through
           this handle.
    @param[in] devHdl Handle of the I2C SERPOM device from which we wish to
                  disconnect
    @returns success/failure status of the operation
*/
NCP_API ncp_st_t
ncp_i2c_amc_bus_close(
    ncp_i2c_amc_bus_hdl_t     inDevHdl);

/*! @fn ncp_st_t ncp_i2c_amc_bus_block_read8(ncp_i2c_amc_bus_hdl_t inDevHdl, ncp_uint32_t inOffset, ncp_uint8_t *inBuffer, ncp_uint32_t inCount, ncp_uint32_t inFlags)
    @brief To read N number of bytes from previously 'opened' device
    @param[in] devHdl Handle of the I2C AMC BUS device from which to read
    @param[in] offset Displacement into the 'device' to start the read
    @param[out] buffer Location to deposit the data that is read
    @param[in] count  Number of bytes to read
    @param[in] flags  Additional I/O control flags
    @returns success/failure status of the operation
*/
NCP_API ncp_st_t
ncp_i2c_amc_bus_block_read8(
    ncp_i2c_amc_bus_hdl_t     inDevHdl,
    ncp_uint32_t              inOffset,
    ncp_uint8_t              *inBuffer,
    ncp_uint32_t              inCount,
    ncp_uint32_t              inFlags);

/*! @fn ncp_st_t ncp_i2c_amc_bus_block_write8(ncp_i2c_amc_bus_hdl_t inDevHdl, ncp_uint32_t inOffset, ncp_uint8_t *outBuffer, ncp_uint32_t inCount, ncp_uint32_t inFlags)
    @brief To write N number of bytes to previously 'opened' device
    @param[in] devHdl Handle of the I2C AMC BUS device from which to write
    @param[in] offset Displacement into the 'device' to start the write
    @param[in] buffer Location to find the data that is to be written
    @param[in] count  Number of bytes to write
    @param[in] flags  Additional I/O control flags
    @returns success/failure status of the operation
*/
NCP_API ncp_st_t
ncp_i2c_amc_bus_block_write8(
    ncp_i2c_amc_bus_hdl_t    inDevHdl,
    ncp_uint32_t             inOffset,
    ncp_uint8_t             *outBuffer,
    ncp_uint32_t             inCount,
    ncp_uint32_t             inFlags);


#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif   /* defined(NCP_I2C_AMC_BUS_H) */
