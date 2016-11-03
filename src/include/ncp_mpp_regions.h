/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/



#ifndef _NCP_MPP_REGIONS_H_
#define _NCP_MPP_REGIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ncp_sal_types.h"




#include "ncp_nodes.h"

#define    NCP_REGION_MPP_DBC                                   NCP_REGION_ID(NCP_NODE_MPP, 0x0010) /* 26.16 */
#define    NCP_REGION_MPP_PQM                                   NCP_REGION_ID(NCP_NODE_MPP, 0x0011) /* 26.17 */
#define    NCP_REGION_MPP_MPIC                                  NCP_REGION_ID(NCP_NODE_MPP, 0x0012) /* 26.18 */
#define    NCP_REGION_MPP_SCH                                   NCP_REGION_ID(NCP_NODE_MPP, 0x0013) /* 26.19 */
#define    NCP_REGION_MPP_CNAL2_MPP                             NCP_REGION_ID(NCP_NODE_MPP, 0x0021) /* 26.33 */
#define    NCP_REGION_MPP_CAAL2_MPPY                            NCP_REGION_ID(NCP_NODE_MPP, 0x0021) /* 26.33 */
#define    NCP_REGION_MPP_HE                                    NCP_REGION_ID(NCP_NODE_MPP, 0x0022) /* 26.34 */
#define    NCP_REGION_MPP_CNAL_MPPX                             NCP_REGION_ID(NCP_NODE_MPP, 0x0023) /* 26.35 */
#define    NCP_REGION_MPP_CAAL_MPPY                             NCP_REGION_ID(NCP_NODE_MPP, 0x0023) /* 26.35 */
#define    NCP_REGION_MPP_SENG                                  NCP_REGION_ID(NCP_NODE_MPP, 0x0028) /* 26.40 */
#define    NCP_REGION_MPP_CE                                    NCP_REGION_ID(NCP_NODE_MPP, 0x0029) /* 26.41 */
#define    NCP_REGION_MPP_SENG_CEPC                             NCP_REGION_ID(NCP_NODE_MPP, 0x002a) /* 26.42 */
#define    NCP_REGION_MPP_SENG_STPC                             NCP_REGION_ID(NCP_NODE_MPP, 0x002b) /* 26.43 */
#define    NCP_REGION_MPP_SENG_STPC1                            NCP_REGION_ID(NCP_NODE_MPP, 0x002c) /* 26.44 */
#define    NCP_REGION_MPP_ETAC                                  NCP_REGION_ID(NCP_NODE_MPP, 0x0030) /* 26.48 */
#define    NCP_REGION_MPP_FBI                                   NCP_REGION_ID(NCP_NODE_MPP, 0x0031) /* 26.49 */
#define    NCP_REGION_MPP_SEM                                   NCP_REGION_ID(NCP_NODE_MPP, 0x0032) /* 26.50 */
#define    NCP_REGION_MPP_CFG_NODE                              NCP_REGION_ID(NCP_NODE_MPP, 0x00ff) /* 26.255 */
#define    NCP_REGION_MPP_CNAL_MPPY_5500                        NCP_REGION_ID(NCP_NODE_MPP, 0x0023) /* 26.35 */
#define    NCP_REGION_MPP_SENG_STPC0_5500                       NCP_REGION_ID(NCP_NODE_MPP, 0x002b) /* 26.43 */
#define    NCP_REGION_MPP_SENG_STPC1_5500                       NCP_REGION_ID(NCP_NODE_MPP, 0x002c) /* 26.44 */


#ifdef __cplusplus
}
#endif

#endif /* _NCP_MPP_REGIONS_H_ */
