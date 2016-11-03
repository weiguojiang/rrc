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
 **    (c) 2009-2014, Intel Corporation.  All rights reserved.           *
 **                                                                        *
 **
 **
 ** **************************************************************************/

/*! @file ncp_i2c_amc_bus_desc.h
 *  @brief APIs for AMC I/O devices
 */

#ifndef NCP_I2C_AMC_BUS_DESC_H
#define NCP_I2C_AMC_BUS_DESC_H

#include "ncp_i2c_amc_bus.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @defgroup _i2c_amc_bus_desc_     I2C AMC Bus Descriptions
 * @brief     I2C AMC Bus Descriptions (i2camcbusdesc)
 * @{
 * @ingroup _i2c_
 */

/*****************************************************************************
 * Constant definitions                                                      *
 *****************************************************************************/


/*****************************************************************************
 * Type definitions                                                          *
 *****************************************************************************/

/*! @struct ncp_i2c_amc_bus_cardList_t
   @brief Structure describing one of the possible AMC Slots for the
          NCP development boards.
*/
typedef struct
{
    ncp_uint32_t        cardId;   /*!< Value of 'Device Id' reg for card */
    char               *name;     /*!< Human readable name for card */
} ncp_i2c_amc_bus_cardList_t;

/*! @struct ncp_i2c_amc_bus_devList_t
   @brief Structure describing one of the possible AMC I/O cards for the
          NCP development boards.
*/
typedef struct
{
    ncp_uint32_t        boardId;   /*!< Value of the board id registers
                                    * at 0x00,0x01 */
    char               *name;      /*!< Board name */
    ncp_uint32_t        deviceLen; /*!< Max # of bytes that can be read */
} ncp_i2c_amc_bus_devList_t;


/*****************************************************************************
 * Externally Visible State                                                  *
 *****************************************************************************/

/*! @var ncp_i2c_amc_bus_card_list[]
    @brief Array of 'ncp_i2c_amc_bus_cardList_t*' structs that describes
           the supported set of AMC slots for the NCP development boards.
*/
NCP_API
ncp_i2c_amc_bus_cardList_t ncp_i2c_amc_bus_card_list[];

/*! @var ncp_i2c_amc_bus_card_list_len
    @brief Size of the array 'ncp_i2c_amc_bus_card_list'
*/
NCP_API
ncp_uint32_t ncp_i2c_amc_bus_card_list_len;

/*! @var ncp_i2c_amc_bus_device_list[]
    @brief Array of 'ncp_i2c_amc_bus_devList_t*' structs that describes the
           supported set of AMC I/O boards for the NCP development boards.
*/
NCP_API
ncp_i2c_amc_bus_devList_t *ncp_i2c_amc_bus_device_list[];


/*****************************************************************************
 * Externally Visible Function Prototypes                                    *
 *****************************************************************************/

/*! @fn ncp_i2c_amc_bus_cardList_t* ncp_i2c_amc_bus_cardFind(ncp_uint32_t inCardId)
    @brief Find/validate an AMC slot
    @param[in] inCardId Id of the card that we wish to identify/validate
    @returns ncp_i2c_amc_bus_cardList_t*
              Pointer to description of the card that matches the id
              or NULL if not found.
*/
NCP_API
ncp_i2c_amc_bus_cardList_t*
ncp_i2c_amc_bus_cardFind(
    ncp_uint32_t inCardId);

/*! @fn ncp_i2c_amc_bus_devList_t* ncp_i2c_amc_bus_devFind(ncp_uint32_t inBoardId)
    @brief Find/validate an AMC I/O card
    @param[in] inBoardId Id of the board that we wish to identify/validate
    @returns ncp_i2c_amc_bus_devList_t*
              Pointer to description of the board that matches the id
              or NULL if not found.
*/
NCP_API
ncp_i2c_amc_bus_devList_t*
ncp_i2c_amc_bus_devFind(
    ncp_uint32_t inBoardId);


#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif   /* defined(NCP_I2C_AMC_BUS_DESC_H) */
