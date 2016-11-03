/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/



#ifndef _NCP_SYSCON_CLK_REGIONS_H_
#define _NCP_SYSCON_CLK_REGIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ncp_sal_types.h"




#include "ncp_nodes.h"

#define    NCP_REGION_SYSCON_CLK_SYS_CLKCTL                     NCP_REGION_ID(NCP_NODE_SYSCON_CLK, 0x0000) /* 397.0 */
#define    NCP_REGION_SYSCON_CLK_SYS_PLLCTL                     NCP_REGION_ID(NCP_NODE_SYSCON_CLK, 0x0001) /* 397.1 */
#define    NCP_REGION_SYSCON_CLK_PPC_PLLCTL                     NCP_REGION_ID(NCP_NODE_SYSCON_CLK, 0x0002) /* 397.2 */
#define    NCP_REGION_SYSCON_CLK_TM_PLLCTL                      NCP_REGION_ID(NCP_NODE_SYSCON_CLK, 0x0003) /* 397.3 */
#define    NCP_REGION_SYSCON_CLK_SM_PLLCTL                      NCP_REGION_ID(NCP_NODE_SYSCON_CLK, 0x0004) /* 397.4 */
#define    NCP_REGION_SYSCON_CLK_NRCP_PLLCTL                    NCP_REGION_ID(NCP_NODE_SYSCON_CLK, 0x0005) /* 397.5 */


#ifdef __cplusplus
}
#endif

#endif /* _NCP_SYSCON_CLK_REGIONS_H_ */
