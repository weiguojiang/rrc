/**************************************************************************
 **                                                                       *
 **                           Intel CONFIDENTIAL      *
 **                           PROPRIETARY NOTE                            *
 **                                                                       *
 **    This software contains information confidential and proprietary    *
 **    to Intel Corporation.  It shall not be reproduced in whole or in *
 **    part, or transferred to other documents, or disclosed to third     *
 **    parties, or used for any purpose other than that for which it was  *
 **    obtained, without the prior written consent of Intel Corporation.*
 **    (c) 2008-2014, Intel Corporation.  All rights reserved.          *
 **                                                                       *
 **
 **
 **************************************************************************/

#ifndef __NCP_EIOA_PHY_H__
#define __NCP_EIOA_PHY_H__

#ifdef __cplusplus
extern "C" {
#endif

#define MDIO_CTRL 0
#define MDIO_OFFSET 8
#define MDIO_PERIOD 0x0C

/* mask for phy register 0x00 */
#define NCP_EIOA_PHY_MII_REG0_MASK 0xccbf
/* mask for phy register 0x04 */
#define NCP_EIOA_PHY_MII_REG4_MASK 0xfe1f
/* mask for phy register 0x09 */
#define NCP_EIOA_PHY_MII_REG9_MASK 0xfdff

ncp_st_t
    ncp_eioa_phy_mii_reg_config(ncp_t *ncp,
        ncp_uint32_t eioa,
        ncp_uint32_t slot,
        ncp_uint32_t port,
        ncp_uint32_t phyAddr);
#ifdef __cplusplus
}
#endif

#endif /* __NCP_EIOA_PHY_H__ */

