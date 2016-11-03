/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/



#ifndef _NCP_MTM_REGIONS_H_
#define _NCP_MTM_REGIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ncp_sal_types.h"




#include "ncp_nodes.h"

#define    NCP_REGION_MTM_MTM_REGISTERS                         NCP_REGION_ID(NCP_NODE_MTM, 0x0010) /* 26.16 */
#define    NCP_REGION_MTM_GLOBAL_STATS                          NCP_REGION_ID(NCP_NODE_MTM, 0x0011) /* 26.17 */
#define    NCP_REGION_MTM_ADDR_XLATION                          NCP_REGION_ID(NCP_NODE_MTM, 0x0012) /* 26.18 */
#define    NCP_REGION_MTM_QE                                    NCP_REGION_ID(NCP_NODE_MTM, 0x0013) /* 26.19 */
#define    NCP_REGION_MTM_MCAST_FLOW                            NCP_REGION_ID(NCP_NODE_MTM, 0x0014) /* 26.20 */
#define    NCP_REGION_MTM_BUF_MAN_CE                            NCP_REGION_ID(NCP_NODE_MTM, 0x0015) /* 26.21 */
#define    NCP_REGION_MTM_TRAFFIC_SHAPER_CE                     NCP_REGION_ID(NCP_NODE_MTM, 0x0016) /* 26.22 */
#define    NCP_REGION_MTM_SH_L1                                 NCP_REGION_ID(NCP_NODE_MTM, 0x0017) /* 26.23 */
#define    NCP_REGION_MTM_LEVEL5_L1                             NCP_REGION_ID(NCP_NODE_MTM, 0x0018) /* 26.24 */
#define    NCP_REGION_MTM_LEVEL4_L1                             NCP_REGION_ID(NCP_NODE_MTM, 0x0019) /* 26.25 */
#define    NCP_REGION_MTM_LEVEL3_L1                             NCP_REGION_ID(NCP_NODE_MTM, 0x001a) /* 26.26 */
#define    NCP_REGION_MTM_LEVEL2_L1                             NCP_REGION_ID(NCP_NODE_MTM, 0x001b) /* 26.27 */
#define    NCP_REGION_MTM_LEVEL1_L1                             NCP_REGION_ID(NCP_NODE_MTM, 0x001c) /* 26.28 */
#define    NCP_REGION_MTM_QUEUE_L1                              NCP_REGION_ID(NCP_NODE_MTM, 0x001d) /* 26.29 */
#define    NCP_REGION_MTM_BP_AGG                                NCP_REGION_ID(NCP_NODE_MTM, 0x001f) /* 26.31 */
#define    NCP_REGION_MTM_CFG_NODE                              NCP_REGION_ID(NCP_NODE_MTM, 0x00ff) /* 26.255 */


#ifdef __cplusplus
}
#endif

#endif /* _NCP_MTM_REGIONS_H_ */
