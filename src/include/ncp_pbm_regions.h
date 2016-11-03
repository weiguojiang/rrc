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
 **    (c) 2001-2014, Intel Corporation.  All rights reserved.          *
 **                                                                       *
 **                                                                       *
 **  **********************************************************************/


#ifndef _NCP_PBM_REGIONS_H_
#define _NCP_PBM_REGIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ncp_sal_types.h"




#include "ncp_nodes.h"

#define    NCP_REGION_PBM_PBM_CORE                              NCP_REGION_ID(NCP_NODE_PBM, 0x0010) /* 51.16 */
#define    NCP_REGION_PBM_CFG_NODE                              NCP_REGION_ID(NCP_NODE_PBM, 0x00ff) /* 51.255 */


#ifdef __cplusplus
}
#endif

#endif /* _NCP_PBM_REGIONS_H_ */
