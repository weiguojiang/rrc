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
 **    (c) 2008-2014, Intel Corporation.  All rights reserved.           *
 **                                                                        *
 **
 ** **************************************************************************/

/*! @file      ncp_bp.h
 *  @brief     This file contains APIs related to Backpressure.
 *
 *  @addtogroup _bp_ Backpressure
 *
 *  @{
 */

#ifndef _NCP_BP_H_
#define _NCP_BP_H_

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Buffer size enum. Enum defining the different buffer sizes.
 * @see ncp_bp_global_threshold_pool_select_get
 * @see ncp_bp_global_threshold_pool_select_set
 */
typedef enum
{
    NCP_BP_BUFFER_SIZE_256B = 0,    /*!< Buffer size 256B */
    NCP_BP_BUFFER_SIZE_2KB,         /*!< Buffer size 2KB */
    NCP_BP_BUFFER_SIZE_16KB,        /*!< Buffer size 16KB */
    NCP_BP_BUFFER_SIZE_MAX
} ncp_bp_buffer_size_t;

/*!
 * @brief This API is used to get the selections indicating whether free buffers 
 *        in the given pool/buffer size are included in global free buffers and
 *        Buffer Manager script total free memory.
 * @param[in] ncpHdl  NCP API state handle.
 * @param[in] poolId The pool id for the selection. Valid values: 0-7.
 * @param[in] bufferSize The buffer size for the selection.
 * @param[in, out] globalFreeBuffers selection indicating inclusion in global free buffers.
 * @param[in, out] bmScriptTotalFreeMemory selection indicating inclusion in 
 *                 Buffer Manager script total free memory.
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_MME_INVALID_POOL_ID When pooId provided is out of range or not configured.
 * @retval NCP_ST_BP_INVALID_BUFFER_SIZE When bufferSize value is invalid.
 * @retval NCP_ST_BP_INVALID_BUFFER When globalFreeBuffers and/or bmScriptTotalFreeMemory
 *         are NULL.
 */

NCP_API ncp_st_t
ncp_bp_global_threshold_pool_select_get(ncp_hdl_t ncpHdl, ncp_uint8_t poolId, 
    ncp_bp_buffer_size_t bufferSize, ncp_bool_t *globalFreeBuffers, 
    ncp_bool_t *bmScriptTotalFreeMemory);

/*!
 * @brief This API is used to set the selections indicating whether free buffers 
 *        in the given pool/buffer size are included in global free buffers and
 *        Buffer Manager script total free memory.
 * @param[in] ncpHdl  NCP API state handle.
 * @param[in] poolId The pool id for the selection. Valid values: 0-7.
 * @param[in] bufferSize The buffer size for the selection.
 * @param[in] globalFreeBuffers selection indicating inclusion in global free buffers.
 * @param[in] bmScriptTotalFreeMemory selection indicating inclusion in 
 *            Buffer Manager script total free memory.
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_MME_INVALID_POOL_ID When pooId provided is out of range or not configured.
 * @retval NCP_ST_BP_INVALID_BUFFER_SIZE When bufferSize value is invalid.
 */

NCP_API ncp_st_t
ncp_bp_global_threshold_pool_select_set(ncp_hdl_t ncpHdl, ncp_uint8_t poolId, 
    ncp_bp_buffer_size_t bufferSize, ncp_bool_t globalFreeBuffers, 
    ncp_bool_t bmScriptTotalFreeMemory);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _NCP_BP_H_ */

/*!
 * @}
 */

