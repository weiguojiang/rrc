/**************************************************************************
 **                                                                        *
 **   Intel Corporation CONFIDENTIAL                                   *
 **                                                                        *
 **                       PROPRIETARY NOTE                                 *
 **                                                                        *
 **    This software contains information confidential and proprietary     *
 **    to Intel Corporation.  It shall not be reproduced in whole or in  *
 **    part, or transferred to other documents, or disclosed to third      *
 **    parties, or used for any purpose other than that for which it was   *
 **    obtained, without the prior written consent of Intel Corporation. *
 **    (c) 2008, Intel Corporation.  All rights reserved.                *
 **                                                                        *
 **  ***********************************************************************
 **
 **  ***********************************************************************
 **   File:       $HeadURL: http://txasoft2.agere.com/svn/software/src/trunk/rte/api/mme/ncp_mme.h $
 **   Version:    $Revision: 3317 $
 **   Date:       $Date: 2008-11-15 00:57:17 -0600 (Sat, 15 Nov 2008) $
 ** **************************************************************************/

/*! @file      ncp_mme.h
 *  @brief     Memory Management Engine
 * 
 *  @addtogroup _mme_ Memory Management Engine
 *
 *  @{
 */

#ifndef __NCP_MME_H__
#define __NCP_MME_H__


/*! @fn ncp_st_t ncp_mme_mpcq_poke(ncp_hdl_t ncpHdl, ncp_uint32_t mpcqId)
    @brief Request more valid mPCQ entries from the MME.
    @param ncpHdl Incoming handle of the current NCP device
    @param mpcqId Id of the mPCQ to poke
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_MME_INVALID_HANDLE The MME module was not properly configured
    @retval NCP_ST_MME_INVALID_MPCQ_ID The specified mPCQ is not valid
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t ncp_mme_mpcq_poke(ncp_hdl_t ncpHdl,
                                   ncp_uint32_t mpcqId);

/*! @fn ncp_st_t ncp_mme_mpcq_polling_interval_get(ncp_hdl_t ncpHdl, ncp_uint32_t *cycles)
    @brief Query the MME mPCQ read pointer polling interval.
    @param ncpHdl Incoming handle of the current NCP device
    @param cycles Returned number of cycles between mPCQ read pointer polls
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_MME_INVALID_HANDLE The MME module was not properly configured
    @retval NCP_ST_DEV_INVALID_BUFFER cycles is not a valid buffer
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t ncp_mme_mpcq_polling_interval_get(ncp_hdl_t ncpHdl,
                                                   ncp_uint32_t *cycles);

/*! @fn ncp_st_t ncp_mme_mpcq_polling_interval_set(ncp_hdl_t ncpHdl, ncp_uint32_t cycles)
    @brief Set the MME mPCQ read pointer polling interval.
    @param ncpHdl Incoming handle of the current NCP device
    @param cycles Number of cycles between mPCQ read pointer polls (range 0 - 255)
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_MME_INVALID_HANDLE The MME module was not properly configured
    @retval NCP_ST_INVALID_VALUE cycles is not a valid value
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t ncp_mme_mpcq_polling_interval_set(ncp_hdl_t ncpHdl,
                                                   ncp_uint32_t cycles);


/*! @fn ncp_st_t ncp_mme_available_blocks_get(ncp_hdl_t ncpHdl, ncp_uint32_t poolId, ncp_uint32_t blockSize, ncp_uint32_t *numBlocks)
    @brief Query the number of available blocks for a specified pool and block size
    @param ncpHdl Incoming handle of the current NCP device
    @param poolId Id of the pool to query
    @param blockSize Block size to query
    @param numBlocks Returned number of available blocks
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_MME_INVALID_HANDLE The MME module was not properly configured
    @retval NCP_ST_MME_INVALID_POOL_ID The specified poolId is not valid
    @retval NCP_ST_MME_INVALID_BLOCK_SIZE The specified blockSize is not valid
    @retval NCP_ST_DEV_INVALID_BUFFER numBlocks is not a valid buffer
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t ncp_mme_available_blocks_get(ncp_hdl_t ncpHdl,
                                              ncp_uint32_t poolId,
                                              ncp_uint32_t blockSize,
                                              ncp_uint32_t *numBlocks);

/*! @fn ncp_st_t ncp_mme_pool_flush(ncp_hdl_t ncpHdl, ncp_uint32_t poolId);
    @brief Flush an MME pool, returning it to its original state.
    @param ncpHdl Incoming handle of the current NCP device
    @param poolId Id of the pool to flush
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_MME_INVALID_HANDLE The MME module was not properly configured
    @retval NCP_ST_MME_INVALID_POOL_ID The specified poolId is not valid
    @retval NCP_ST_MME_FLUSH_MPCQ_NOT_STOPPED Activity for an mPCQ associated with the pool could not be stopped
    @retval NCP_ST_MME_FLUSH_MREF_NOT_STOPPED mREF activity for the pool could not be stopped
    @retval NCP_ST_MME_FLUSH_IFLS_NOT_STOPPED IFLS activity for the pool could not be stopped
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t ncp_mme_pool_flush(ncp_hdl_t ncpHdl,
                                    ncp_uint32_t poolId);

/*
 *  @}
 */

#endif /* __NCP_MME_H__ */
