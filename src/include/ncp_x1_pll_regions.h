/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/



#ifndef _NCP_X1_PLL_REGIONS_H_
#define _NCP_X1_PLL_REGIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ncp_sal_types.h"


#include "ncp_nodes.h"

#define    NCP_REGION_DDR0_PLL_REGS         NCP_REGION_ID(NCP_NODE_DDR0_PLL, 0x0)    /* 35.0 */
#define    NCP_REGION_DDR0_PLL_CFG_NODE     NCP_REGION_ID(NCP_NODE_DDR0_PLL, 0x00ff) /* 35.255 */

#define    NCP_REGION_DDR1_PLL_REGS         NCP_REGION_ID(NCP_NODE_DDR1_PLL, 0x0)    /* 13.0 */
#define    NCP_REGION_DDR1_PLL_CFG_NODE     NCP_REGION_ID(NCP_NODE_DDR1_PLL, 0x00ff) /* 13.255 */

#ifdef __cplusplus
}
#endif

#endif /* _NCP_X1_PLL_REGIONS_H_ */
