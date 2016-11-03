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
 **/
/*! @file      ncp_crt.h
 *  @brief     CRT Argument Parsing Simulation Functions
 */

#ifndef NCP_CRT_H
#define NCP_CRT_H

#include "ncp_types.h"

/*! @defgroup _unexported_fns  UnExported Functions
 *
 * @{
 * 
 *  @defgroup _crt_APIs        CRT Argument Parsing Simulation
 */

#ifdef __cplusplus
extern "C" {
#endif

#define NCP_MAX_ARGV     32
    
#define NCP_MAX_ARG_LEN  512

typedef int (*ncp_mainFunc_t)(int argc, const char * argv[]);

NCP_API int ncp_crt(const char *cmdName, char *cmdArgs, ncp_mainFunc_t mainFunc);

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* NCP_CRT_H */
