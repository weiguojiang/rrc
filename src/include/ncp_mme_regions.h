/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/



#ifndef _NCP_MME_REGIONS_H_
#define _NCP_MME_REGIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ncp_sal_types.h"




#include "ncp_nodes.h"

#define    NCP_REGION_MME_MME_CORE                              NCP_REGION_ID(NCP_NODE_MME, 0x0010) /* 21.16 */
#define    NCP_REGION_MME_POKE                                  NCP_REGION_ID(0x109,0x0) /* 265.0 */
#define    NCP_REGION_MME_CFG_NODE                              NCP_REGION_ID(NCP_NODE_MME, 0x00ff) /* 21.255 */


#ifdef __cplusplus
}
#endif

#endif /* _NCP_MME_REGIONS_H_ */
