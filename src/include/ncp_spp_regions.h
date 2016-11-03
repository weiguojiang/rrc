/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/



#ifndef _NCP_SPP_REGIONS_H_
#define _NCP_SPP_REGIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ncp_sal_types.h"




#include "ncp_nodes.h"

#define    NCP_REGION_SPP_MPE                                   NCP_REGION_ID(NCP_NODE_SPP, 0x0010) /* 11.16 */
#define    NCP_REGION_SPP_NU_L1_PLC                             NCP_REGION_ID(NCP_NODE_SPP, 0x0020) /* 11.32 */
#define    NCP_REGION_SPP_CFG_NODE                              NCP_REGION_ID(NCP_NODE_SPP, 0x00ff) /* 11.255 */


#ifdef __cplusplus
}
#endif

#endif /* _NCP_SPP_REGIONS_H_ */
