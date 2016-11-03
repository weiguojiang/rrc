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
 **    (c) 2008-2014, Intel Corporation.  All rights reserved.          *
 **                                                                       *
 **                                                                       *
 **  **********************************************************************/

/*! @file      ncp_ecm.h
 *  @brief     ECM Fuse Access
 * 
 *  @addtogroup _ecm_ ECM Fuse Access
 *
 *  @{
 */


#ifndef _NCP_ECM_H_
#define _NCP_ECM_H_

#include "ncp_types.h"

#ifdef __cplusplus
extern "C" {
#endif

    /******************/
    /* published APIs */
    /******************/

    ncp_st_t ncp_ecm_bits_by_offset(ncp_dev_hdl_t, ncp_uint32_t, ncp_uint32_t *);

    ncp_st_t ncp_ecm_NoRB_by_offset(ncp_dev_hdl_t, ncp_uint32_t, ncp_bool_t *);

    ncp_st_t ncp_ecm_read_fuse(ncp_dev_hdl_t, ncp_uint32_t, ncp_uint32_t *);

    ncp_st_t ncp_ecm_write_fuse(ncp_dev_hdl_t, ncp_uint32_t, ncp_uint32_t *);

#ifdef __cplusplus
}
#endif

#endif /* _NCP_EIOA_H_ */

/*
 *  @}
 */
