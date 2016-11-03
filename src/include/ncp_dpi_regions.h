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


#ifndef _NCP_DPI_REGIONS_H_
#define _NCP_DPI_REGIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ncp_sal_types.h"




#include "ncp_nodes.h"

#define    NCP_REGION_DPI_NU_COW                                NCP_REGION_ID(NCP_NODE_DPI, 0x0000) /* 14.0 */
#define    NCP_REGION_DPI_NU_TCLD                               NCP_REGION_ID(NCP_NODE_DPI, 0x0000) /* 14.0 */
#define    NCP_REGION_DPI_NU_TIL                                NCP_REGION_ID(NCP_NODE_DPI, 0x0001) /* 14.1 */
#define    NCP_REGION_DPI_NU_TDGL                               NCP_REGION_ID(NCP_NODE_DPI, 0x0002) /* 14.2 */
#define    NCP_REGION_DPI_NU_TGL                                NCP_REGION_ID(NCP_NODE_DPI, 0x0003) /* 14.3 */
#define    NCP_REGION_DPI_NU_CNAL                               NCP_REGION_ID(NCP_NODE_DPI, 0x0005) /* 14.5 */
#define    NCP_REGION_DPI_NU_TCLS                               NCP_REGION_ID(NCP_NODE_DPI, 0x0006) /* 14.6 */
#define    NCP_REGION_DPI_DPI_CORE                              NCP_REGION_ID(NCP_NODE_DPI, 0x0010) /* 14.16 */
#define    NCP_REGION_DPI_DPI_L1_P1C                            NCP_REGION_ID(NCP_NODE_DPI, 0x0011) /* 14.17 */
#define    NCP_REGION_DPI_CFG_NODE                              NCP_REGION_ID(NCP_NODE_DPI, 0x00ff) /* 14.255 */


#ifdef __cplusplus
}
#endif

#endif /* _NCP_DPI_REGIONS_H_ */
