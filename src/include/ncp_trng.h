/**************************************************************************
 **                                                                       *
 **                           Intel CONFIDENTIAL      *
 **                           PROPRIETARY NOTE                            *
 **                                                                       *
 **    This software contains information confidential and proprietary    *
 **    to Intel Corporation.  It shall not be reproduced in whole or in *
 **    part, or transferred to other documents, or disclosed to third     *
 **    parties, or used for any purpose other than that for which it was  *
 **    obtained, without the prior written consent of Intel Corporation.*
 **    (c) 2008-2014, Intel Corporation.  All rights reserved.          *
 **                                                                       *
 **
 **
 **************************************************************************/
/*! @file        ncp_trng.h
    @brief       Crypto/TRNG (trng)

    @defgroup    _trng_ True Random Number Generator
    @ingroup     _spp_

    @{
*/

#ifndef ncp_trng_h
#define ncp_trng_h

#include "ncp_types.h"

#ifdef __cplusplus
extern "C"
{
#endif


/******************************************************************************/
/* Constants & Type definitions                                               */
/******************************************************************************/

/******************************************************************************/
/* APIs                                                                       */
/******************************************************************************/

/*! @fn ncp_st_t ncp_st_t ncp_trng_getNumbers(ncp_hdl_t ncpHdl, ncp_uint32_t numRandom, ncp_uint32_t *outRN)
    @brief Acquire 'numRandom' new random numbers
    @param[in] ncp Incoming handle of the current NCP configuration
    @param[in] numRandom Number of new random numbers to retrieve and deposit
                     in the 'outRN' array.  The caller is responsible for
                     ensuring that the array is large enough to hold the
                     number of requested results.
    @param[out] outRN Caller array in which to deposit the requested numbers
    @retval NCP_ST_SUCCESS operation successfully completed
    @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
    @retval NCP_ST_TRNG_NOT_INSTALLED TRNG module not present in hardware
    @retval NCP_ST_TRNG_INVALID_VALUE invalid argument(s) e.g. null outRN, numRandom == 0
    @retval NCP_ST_TRNG_BIST_ERROR failure reseeding the TRNG module
    @retval NCP_ST_TRNG_FIPS_OUT_ERROR failure initializing the TRNG module
    @retval other device driver errors may be observed
*/
NCP_API
ncp_st_t ncp_trng_getNumbers(
     ncp_hdl_t           ncpHdl,
     ncp_uint32_t        numRandom,
     ncp_uint32_t       *outRN);


#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* ncp_trng_h */
