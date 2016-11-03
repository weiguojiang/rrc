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

/*! @file      ncp_pll.h
 *  @brief     Phase Locked Loop
 *             
 *             Phase Locked Loop APIs, defines and structure definitions.
 *             The PLL API calls provide the ability to modify and retrieve
 *             the frequency of the system clock.
 * 
 *  @addtogroup _pll_ Phase Locked Loop
 * 
 *  @{
 */


#ifndef _NCP_PLL_H_
#define _NCP_PLL_H_

#ifdef __cplusplus
extern "C" {
#endif


/* Public Enumerated Types */
/*!
 * @brief PLL output speed specification
 *
 *    Specifies the output of the PLL - high frequency (with higher power usage)
 *    or low frequency (with lower power usage).
 */
typedef enum ncp_pll_frequency_e
{
    NCP_PLL_FREQUENCY_HIGH = 0,     /*!< High speed */
    NCP_PLL_FREQUENCY_LOW,          /*!< Low speed  */
    NCP_PLL_FREQUENCY_MAX = NCP_PLL_FREQUENCY_LOW
} ncp_pll_frequency_t;



/* Public Structures */
/*!
 * @brief PLL settings
 */
typedef struct ncp_pll_settings_s
{
    /*! @brief  The high frequency setting of the PLL (Hz) */
    ncp_uint64_t            highFrequency;
    /*! @brief  The low frequency setting of the PLL (Hz) */
    ncp_uint64_t            lowFrequency;
    /*! @brief  The current frequency setting of the PLL (High/Low) */
    ncp_pll_frequency_t     setting;
} ncp_pll_settings_t;



/* Published APIs */
/*!
 *  @brief  Set the frequency of the system clock.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the PLL is part of.
 *  @param[in]  frequency   The frequency to set the PLL to (HIGH/LOW)
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_PLL_HANDLE_INVALID
 *      \li ::NCP_ST_PLL_FREQUENCY_INVALID
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_pll_sys_clock_set(ncp_hdl_t ncpHdl, ncp_pll_frequency_t frequency);


/*!
 *  @brief  Get the current settings of the system clock.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the PLL is part of.
 *  @param[out] setting     The current frequency setting of the PLL (HIGH/LOW).
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_PLL_HANDLE_INVALID
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_pll_sys_clock_get(ncp_hdl_t ncpHdl, ncp_pll_settings_t *settings);

/*!
 *  @brief  Get the current settings of the core clock.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the PLL is part of.
 *  @param[out] setting     The current frequency setting of the PLL (HIGH/LOW).
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_PLL_HANDLE_INVALID
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_pll_core_clock_get(ncp_hdl_t ncpHdl, ncp_pll_settings_t *settings);


#ifdef __cplusplus
}
#endif

#endif /* #ifndef _NCP_PLL_H_ */

