/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/



#ifndef _NCP_SED_REGIONS_H_
#define _NCP_SED_REGIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ncp_sal_types.h"




#include "ncp_nodes.h"

#define    NCP_REGION_SED_REGISTERS                             NCP_REGION_ID(NCP_NODE_SED, 0x0010) /* 12.16 */
#define    NCP_REGION_SED_PARM_RAM                              NCP_REGION_ID(NCP_NODE_SED, 0x0011) /* 12.17 */
#define    NCP_REGION_SED_CE                                    NCP_REGION_ID(NCP_NODE_SED, 0x0012) /* 12.18 */
#define    NCP_REGION_SED_CFG_NODE                              NCP_REGION_ID(NCP_NODE_SED, 0x00ff) /* 12.255 */


#ifdef __cplusplus
}
#endif

#endif /* _NCP_SED_REGIONS_H_ */
