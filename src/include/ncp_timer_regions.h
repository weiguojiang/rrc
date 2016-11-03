/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/



#ifndef _NCP_TIMER_REGIONS_H_
#define _NCP_TIMER_REGIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ncp_sal_types.h"




#include "ncp_nodes.h"

#define    NCP_REGION_TIMER_TIMER_CORE                          NCP_REGION_ID(NCP_NODE_TIMER, 0x0010) /* 25.16 */
#define    NCP_REGION_TIMER_CFG_NODE                            NCP_REGION_ID(NCP_NODE_TIMER, 0x00ff) /* 25.255 */
#define    NCP_REGION_TIMER_TMGR_NU_TIMER_125                   NCP_REGION_ID(NCP_NODE_TIMER, 0x0011) /* 25.17 */
#define    NCP_REGION_TIMER_TMGR_SYSTEM_COUNT                   NCP_REGION_ID(NCP_NODE_TIMER, 0x0012) /* 25.18 */


#ifdef __cplusplus
}
#endif

#endif /* _NCP_TIMER_REGIONS_H_ */
