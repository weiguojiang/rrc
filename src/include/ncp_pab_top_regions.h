/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/



#ifndef _NCP_PAB_TOP_REGIONS_H_
#define _NCP_PAB_TOP_REGIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ncp_sal_types.h"




#include "ncp_nodes.h"

#define    NCP_REGION_PAB_TOP_PAB                               NCP_REGION_ID(NCP_NODE_PAB_TOP, 0x0010) /* 28.16 */
#define    NCP_REGION_PAB_TOP_PAB_BL1C                          NCP_REGION_ID(NCP_NODE_PAB_TOP, 0x0011) /* 28.17 */
#define    NCP_REGION_PAB_TOP_PAB_EL1C                          NCP_REGION_ID(NCP_NODE_PAB_TOP, 0x0012) /* 28.18 */
#define    NCP_REGION_PAB_TOP_CFG_NODE                          NCP_REGION_ID(NCP_NODE_PAB_TOP, 0x00ff) /* 28.255 */


#ifdef __cplusplus
}
#endif

#endif /* _NCP_PAB_TOP_REGIONS_H_ */
