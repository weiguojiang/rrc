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
 **  ***********************************************************************
 **
 **  ***********************************************************************
 ** **************************************************************************/


    
#ifndef _NCP_NRCP_55XX_H_
#define _NCP_NRCP_55XX_H_

#ifdef __cplusplus
extern "C" {
#endif


/*
 *  Configure the NRCP DPLL for 55xx.
 *
 *  param[in]  ncpHdl      Handle for the NCP that the NRCP is part of.
 *  param[in]  nrcpCfg     Pointer to NRCP configuration data structure.
 *
 *  return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_PLL_HANDLE_INVALID
 *      \li ::NCP_ST_PLL_FREQUENCY_INVALID
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_nrcp_dpll_set_55xx(ncp_hdl_t ncpHdl, ncp_nrcp_Config_t *nrcpCfg);



/*
 *  brief  release NRCP divider from reset.
 *
 *  param[in]  ncpHdl      Handle for the NCP that NRCP is part of
 *  
 *
 *  return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_nrcp_divider_reset_release_55xx(ncp_hdl_t ncpHdl);

/*
 *  brief  Configure NRCP CLKO.
 *
 *  param[in]  ncpHdl      Handle for the NCP that the NRCP is part of.
 *  param[in]  clkoSelect   CLKO select.

 *
 *  return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_nrcp_clko_set_55xx(ncp_hdl_t ncpHdl, ncp_nrcp_clkoSelect_t clkoSelect);



/*
 *  brief  Configure NRCP CLKO.
 *
 *  param[in]  ncpHdl      Handle for the NCP that the NRCP is part of.
 *  param[in]  ethclkoSelect   ETHCLKO select.

 *
 *  return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_nrcp_ethclko_set_55xx(ncp_hdl_t ncpHdl, ncp_nrcp_ethclkoSelect_t ethclkoSelect);




/*
 *  brief  Update NRCP reference clock
 *  details  This API assumes the NRCP reference clock has currently been  configured to ground.
 *            It will switch the reference clock from ground to the specified source.
 *
 *  param[in]  ncpHdl      Handle for the NCP that the PLL is part of.
 *  param[in]  refclk      New reference clock parameters.

 *
 *  return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_nrcp_refclk_update_55xx(ncp_hdl_t ncpHdl, ncp_nrcp_refclk_updateparam_t *refclk);



/*
 * brief  NRCP status
 * details  This API retrieves the NRCP status
 *
 *  param[in]  ncpHdl      Handle for the NCP that the PLL is part of.
 *  param[out]  nrcpStatus      NRCP status.

 *
 *  return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *       \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_nrcp_status_get_55xx(ncp_hdl_t ncpHdl, ncp_nrcp_status_t *nrcpStatus);


/*
 *  brief  NRCP status
 *  details  This API retrieves the NRCP status
 *
 *  param[in]  ncpHdl      Handle for the NCP that the PLL is part of.
 *  param[out]  acquisitionMode      DPLL aqcusition mode.

 *
 *  return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_nrcp_acquisitionMode_sel_55xx (ncp_hdl_t ncpHdl, ncp_nrcp_acquisitionMode_t  acquisitionMode);
    

NCP_API ncp_st_t
ncp_nrcp_SYNCE0_set_55xx(ncp_hdl_t ncpHdl,  ncp_nrcp_SYNCE0_Pin_Config_t *syncE0PinCfg);

NCP_API ncp_st_t
ncp_nrcp_SYNCE1_set_55xx(ncp_hdl_t ncpHdl,  ncp_nrcp_SYNCE1_Pin_Config_t *syncE1PinCfg);

ncp_st_t
ncp_nrcp_config_55xx( ncp_t         *ncp, ncp_map_t     *map);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _NCP_NRCP_55XX_H_ */

