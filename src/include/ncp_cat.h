/**************************************************************************
 **                                                                       *
 **                           Intel CONFIDENTIAL                            *
 **                           PROPRIETARY NOTE                            *
 **                                                                       *
 **    This software contains information confidential and proprietary    *
 **    to Intel Corporation.  It shall not be reproduced in whole or in *
 **    part, or transferred to other documents, or disclosed to third     *
 **    parties, or used for any purpose other than that for which it was  *
 **    obtained, without the prior written consent of Intel Corporation.*
 **    (c) 2010-2014, Intel Corporation.  All rights reserved.          *
 **                                                                       *
 ** 
 **
 **  **********************************************************************/

/*! @file       ncp_cat.h
    @brief      User-level (non-kernel) APIs for access to CAT module, and
                the storage, retrieval, and decoding of information from
                'crashed' systems.
*/

#ifndef _NCP_CAT_H_
#define _NCP_CAT_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "ncp.h"
#include "ncp_cat_common.h"

/*!
    @defgroup    _cat_ Crash Analysis Tools

    @defgroup    _cat_user_ User-Level Crash Analysis Tools
    @brief      User-level (non-kernel) APIs for access to CAT module, and
                the storage, retrieval, and decoding of information from
                'crashed' systems.
    @{
    @ingroup     _cat_
 */

/**************************************************************************
* Useful Interface Constants                                              *
**************************************************************************/

/*!
 * @enum ncp_cat_match_t
 */
typedef enum
{
    NCP_CAT_MATCH_RTEVER_EXACT,         /*!< Match 'rteVer' string exactly,
                                         *   Match 'chipVer' exactly */
    NCP_CAT_MATCH_RTEVER_NUMERIC_ONLY,  /*!< Match 'rteVer' string only for leading
                                         *   x.y.z numerics,
                                         *   Match 'chipVer' exactly */
    NCP_CAT_MATCH_WITHOUT_RTEVER,       /*!< Match CAT register map without 'rteVer'
                                         *   Match 'chipVer' exactly */
} ncp_cat_match_t;

/*!
 * @enum ncp_cat_save_t
 * @brief There is an entry for every save code prior to 'save_all'
 *        in one or more arrays within the 'ncp_cat.c' dump/decode code.
 */
typedef enum
{
    NCP_CAT_SAVE_GLOBAL_HDR,     /*!< Save global header only */
    NCP_CAT_SAVE_REGMAP_HDR,     /*!< Save register map header only */
    NCP_CAT_SAVE_REGMAP_DATA,    /*!< Save register map data only */
    NCP_CAT_SAVE_MTML1CACHE_HDR, /*!< Save MTM L1 Cache header only */
    NCP_CAT_SAVE_MTML1CACHE_DATA,/*!< Save MTM L1 Cache data only */
    NCP_CAT_SAVE_MME_HDR,        /*!< Save MME header only */
    NCP_CAT_SAVE_MME_DATA,       /*!< Save MME data only */
    NCP_CAT_SAVE_RAW_HDR,        /*!< Save RAW header only */
    NCP_CAT_SAVE_RAW_DATA,       /*!< Save RAW data only */
    NCP_CAT_SAVE_ALL,            /*!< Save all items to best of ability */
    NCP_CAT_SAVE_UNDEFINED,      /*!< Undefined save item code */
} ncp_cat_save_t;


/**************************************************************************
* Application-Level APIs                                                  *
**************************************************************************/

/*!
 * @fn ncp_st_t ncp_cat_write(ncp_dev_hdl_t  devHdl);
 * @brief Tell the API and/or driver to save critical NCP state for
 *        examination after the NCP device is reset.  This state may
 *        include copies of registers, copies of the MTM L1 cache info,
 *        or other fixed/required data.
 * @param[in] ncp: Device handle
 * @retval NCP_ST_SUCCESS Operation successfully completed
 * @retval NCP_ST_INVALID_HANDLE devHdl is invalid
 * @retval NCP_ST_CAT_NOT_CONFIGURED The CAT module was not configured
 *                    prior to this function call.
 * @retval NCP_ST_CAT_NOT_ENABLED The CAT module was not enabled when
 *                    the configuration was created.
 * @retval other Other device driver error codes may be observed.
 */
NCP_API
ncp_st_t ncp_cat_write(
    ncp_dev_hdl_t  devHdl);

/*!
 * @fn ncp_st_t ncp_cat_write_raw(ncp_dev_hdl_t devHdl,
 *                                ncp_uint32_t  count,
 *                                void         *buffer);
 * @brief Tell the API and/or driver to save more NCP state for subsequent
 *        retrieval and examination, where any necessary header and the
 *        data is passed in by these function arguments.
 * @param[in] dev Device handle
 * @param[in] count Data byte count for buffer content
 * @param[in] buffer Data source to be added to the NCP CAT state.
 * @retval NCP_ST_SUCCESS operation successfully completed
 * @retval NCP_ST_INVALID_HANDLE devHdl is invalid
 * @retval NCP_ST_CAT_NOT_CONFIGURED The CAT module was not configured prior
 *                    to this function call.
 * @retval NCP_ST_CAT_NOT_ENABLED The CAT module was not enabled when the
 *                    configuration was created.
 * @retval other Other device driver error codes may be observed.
 */
NCP_API
ncp_st_t ncp_cat_write_raw(
    ncp_dev_hdl_t       devHdl,
    ncp_uint32_t        count,
    void               *buffer);

/*!
 * @fn ncp_st_t ncp_cat_write_finalize(ncp_dev_hdl_t      devHdl);
 * @brief Tell the API and/or driver to complete saving critical NCP state
 *        to the CAT memory for examination after the NCP device is reset.
 *        This final data may include lengths, checksums, etc.
 * @param[in] dev Device handle
 * @retval NCP_ST_SUCCESS operation successfully completed
 * @retval NCP_ST_INVALID_HANDLE devHdl is invalid
 * @retval NCP_ST_CAT_NOT_CONFIGURED The CAT module was not configured prior
 *                    to this function call.
 * @retval NCP_ST_CAT_NOT_ENABLED The CAT module was not enabled when the
 *                    configuration was created.
 * @retval other Other device driver error codes may be observed.
 */
NCP_API
ncp_st_t ncp_cat_write_finalize(
    ncp_dev_hdl_t      devHdl);

/*!
 * @fn ncp_st_t ncp_cat_save(ncp_dev_hdl_t   devHdl,
 *                           ncp_uint8_t    *catData,
 *                           ncp_uint32_t    catDataSize,
 *                           ncp_cat_save_t  itemSave,
 *                           ncp_cat_match_t matchEnum);
 * @brief Store the data, previously captured via ncp_cat_write() and recovered
 *        via ncp_cat_read(), in a form that can be analyzed for NCP problems
 *        using standard panels/scripts/utilities.
 * @param[in] ncp Device handle
 * @param[in] catData Start of complete block of data read back via ncp_cat_read()
 * @param[in] catDataSize Length of data found at 'catData' buffer
 * @param[in] itemSize Kind of item to be saved
 * @param[in] matchEnum Kind of match needed for rteVer, etc.
 * @retval NCP_ST_SUCCESS Operation successfully completed
 * @retval NCP_ST_INVALID_HANDLE devHdl is invalid
 * @retval NCP_ST_CAT_DATA_BUFFER_INVALID 'buffer' argument is invalid e.g. NULL
 * @retval NCP_ST_CAT_DATA_BUFSIZE_INVALID 'bufferSize' argument is invalid e.g. zero
 * @retval NCP_ST_CAT_NO_RECOVERY_DATA Buffer pointed to by 'catData' does not have any CAT recovery data within it
 * @retval NCP_ST_CAT_MISMATCH_RTE_VERSION RTE Version used to encode/store the 'catData' does not match the one trying to decode/extract it
 * @retval NCP_ST_CAT_MISMATCH_CHIP_VERSION ACP chip version/revision used to encode/store the 'catData' does not match the one trying to decode/extract it
 * @retval NCP_ST_CAT_MISMATCH_DATA_TRUNCATED The information stored in 'catData' has too little register data
 * @retval NCP_ST_CAT_CORRUPT_RECOVERY_DATA Checksum computed for the 'catData' does not match the one that was expected
 * @retval other Other device driver error codes may be observed.
 */
NCP_API
ncp_st_t ncp_cat_save(
    ncp_dev_hdl_t   devHdl,
    ncp_uint8_t    *catData,
    ncp_uint32_t    catDataSize,
    ncp_cat_save_t  itemSave,
    ncp_cat_match_t matchEnum);

/*!
 * @fn ncp_st_t ncp_cat_size(ncp_dev_hdl_t  devHdl,
 *                           ncp_uint64_t  *memorySize);
 * @brief Retrieves the size of the data configured for storage of critical
 *        NCP state by the CAT utilities.
 * @param[in] ncp Device handle
 * @param[in] memorySize Size configured for storing the CAT data
 * @retval NCP_ST_SUCCESS Operation successfully completed
 * @retval NCP_ST_INVALID_HANDLE devHdl is invalid
 * @retval NCP_ST_CAT_NOT_CONFIGURED The CAT module was not configured prior
 *                    to this function call
 * @retval NCP_ST_CAT_NOT_ENABLED The CAT module was not enabled when the
 *                    configured was created.
 * @retval NCP_ST_CAT_MEMORY_SIZE_INVALID 'catMemorySize' argument is invalid e.g. NULL pointer
 * @retval other Other device driver error codes may be observed.
 */
NCP_API
ncp_st_t ncp_cat_size(
    ncp_dev_hdl_t  devHdl,
    ncp_uint64_t  *memorySize);

/*!
 * @fn ncp_st_t ncp_cat_read(ncp_dev_hdl_t  devHdl,
 *                           ncp_uint8_t   *buf,
 *                           ncp_uint32_t   bufSize,
 *                           ncp_uint64_t  *offset,
 *                           ncp_uint32_t  *readSize);
 * @brief Read back a block of data from the previously captured critical state.
 *        This function can be used in an iterative fashion, starting at offset=0,
 *        advancing by the 'readSize' after making use of the retrieved block,
 *        and repeating until the return code of NCP_ST_CAT_DATA_EOF is seen.
 * @param[in] ncp Device handle
 * @param[in] buf Address of buffer provided by caller into which a subset
 *                of the previously cached data is deposited
 * @param[in] bufSize Size of 'buffer' in bytes
 * @param[in,out] offset Displacement in bytes into the block of data stored by CAT
 * @param[out] readSize Address to deposit size of data actually read
 * @retval NCP_ST_SUCCESS Operation successfully completed
 * @retval NCP_ST_CAT_NOT_CONFIGURED The CAT module was not configured prior
 *                    to this function call.
 * @retval NCP_ST_CAT_NOT_ENABLED The CAT module was not enabled when the
 *                    configured was created.
 * @retval NCP_ST_CAT_DATA_EOF Non-fatal notification that no more data is available to retrieve from the CAT recovery data block.
 * @retval NCP_ST_INVALID_HANDLE devHdl is invalid
 * @retval NCP_ST_CAT_NOT_CONFIGURED The CAT module was not configured prior
 *                    to this function call
 * @retval NCP_ST_CAT_DATA_BUFFER_INVALID 'buffer' argument is invalid e.g. NULL
 * @retval NCP_ST_CAT_DATA_BUFSIZE_INVALID 'bufferSize' argument is invalid e.g. zero
 * @retval NCP_ST_CAT_INVALID_ITERATOR 'offset' or 'readSize' arguments are invalid e.g. NULL pointers
 * @retval other Other device driver error codes may be observed.
 */
NCP_API
ncp_st_t ncp_cat_read(
    ncp_dev_hdl_t  devHdl,
    ncp_uint8_t   *buf,
    ncp_uint32_t   bufSize,
    ncp_uint64_t  *offset,
    ncp_uint32_t  *readSize);


#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* _NCP_CAT_H_ */
