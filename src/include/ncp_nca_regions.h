/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/



#ifndef _NCP_NCA_REGIONS_H_
#define _NCP_NCA_REGIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ncp_sal_types.h"



#include "ncp_nodes.h"


#define    NCP_REGION_NCA_NU                                    NCP_REGION_ID(NCP_NODE_NCA, 0x0000) /* 16.0 */
#define    NCP_REGION_NCA_TIL                                   NCP_REGION_ID(NCP_NODE_NCA, 0x0001) /* 16.1 */
#define    NCP_REGION_NCA_TDGL                                  NCP_REGION_ID(NCP_NODE_NCA, 0x0002) /* 16.2 */
#define    NCP_REGION_NCA_TGL                                   NCP_REGION_ID(NCP_NODE_NCA, 0x0003) /* 16.3 */
#define    NCP_REGION_NCA_CNAL                                  NCP_REGION_ID(NCP_NODE_NCA, 0x0005) /* 16.5 */
#define    NCP_REGION_NCA_TCLS                                  NCP_REGION_ID(NCP_NODE_NCA, 0x0006) /* 16.6 */




#ifdef __cplusplus
}
#endif

#endif /* _NCP_NCA_REGIONS_H_ */
