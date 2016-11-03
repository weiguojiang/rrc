/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


#ifndef _NCP_EIOA_MAC_35XX_H_
#define _NCP_EIOA_MAC_35XX_H_

#ifdef __cplusplus
extern "C" {
#endif


/* Public Definitions */

ncp_st_t 
ncp_eioa_broadcast_filter_set_35xx(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_bool_t broadcast_filter);


ncp_st_t 
ncp_eioa_broadcast_filter_get_35xx(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_bool_t *broadcast_filter);

ncp_st_t
ncp_eioa_unicast_mac_addr_set_35xx(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_dev_unicast_addr_t *unicast_addr_info);

ncp_st_t
ncp_eioa_unicast_mac_addr_get_35xx(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_dev_unicast_addr_t *unicast_addr_info);


#ifdef __cplusplus
}
#endif

#endif /* #ifndef _NCP_EIOA_MAC_35XX_H_ */

