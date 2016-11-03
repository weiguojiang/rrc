/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/



#ifndef _NCP_DEV_EIOA_MAC_55XX_H_
#define _NCP_DEV_EIOA_MAC_55XX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ncp_sal_types.h"

ncp_st_t
ncp_dev_eioa_mac_phy_init_55xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

ncp_st_t
ncp_dev_mac_phy_config_common_55xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

ncp_st_t
ncp_dev_eioa_mac_an_start_55xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

ncp_st_t
ncp_dev_eioa_mac_an_stop_55xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

ncp_st_t
ncp_dev_mac_an_intr_55xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

ncp_st_t
ncp_dev_eioa_mac_c37_an_start_55xx(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

ncp_st_t
ncp_dev_eioa_mac_c37_an_stop_55xx(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

ncp_st_t
ncp_dev_mac_an_c73_intr_55xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

ncp_st_t
ncp_dev_mac_an_c37_intr_55xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

#ifdef __cplusplus
}
#endif

#endif /* _NCP_DEV_EIOA_MAC_55XX_H_ */

