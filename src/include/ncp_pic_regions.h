/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/



#ifndef _NCP_PIC_REGIONS_H_
#define _NCP_PIC_REGIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ncp_sal_types.h"




#include "ncp_nodes.h"

#define    NCP_REGION_PIC_PIC_CORE                              NCP_REGION_ID(NCP_NODE_PIC, 0x0010) /* 27.16 */
#define    NCP_REGION_PIC_CFG_NODE                              NCP_REGION_ID(NCP_NODE_PIC, 0x00ff) /* 27.255 */


#ifdef __cplusplus
}
#endif

#endif /* _NCP_PIC_REGIONS_H_ */
