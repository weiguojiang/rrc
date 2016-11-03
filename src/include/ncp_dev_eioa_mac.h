/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/



#ifndef _NCP_DEV_EIOA_MAC_H_
#define _NCP_DEV_EIOA_MAC_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "ncp_sal_types.h"

/*
 * Call from all api's in 
 * the files:
 * ncp_dev_eioa.c
 * ncp_eioa_mac_phy_common.c
 */
ncp_st_t
ncp_eioa_port_get(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_port_t **port,
    ncp_uint32_t flags);
/*
 * called from ncp_dev_mac_an_intr()
 * in ncp_eioa_mac_phy_common.c
 * defined in ncp_eioa_mac_phy_common.c
ncp_st_t
ncp_dev_mac_an_c37_intr(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);
 */

/* 
 * Called from ncp_dev_mac_phy_handle_link_timer()
 * in ncp_dev_eioa.c
 * Defined in ncp_eioa_mac_phy_common.c
 */
ncp_st_t
ncp_dev_mac_an_intr(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

/*
 * called from ncp_dev_mac_an_intr()
 * in ncp_eioa_mac_phy_common.c
 * defined in ncp_eioa_mac_phy_common.c
ncp_st_t
ncp_dev_mac_an_c73_intr(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);
 */

/*
 * called from ncp_dev_eioa_AN_start()
 * in ncp_dev_eioa.c
 * Defined in ncp_eioa_mac_phy_common.c
 */
ncp_st_t
ncp_dev_eioa_mac_an_start(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

/*
 * called from ncp_dev_eioa_AN_stop()
 * in ncp_dev_eioa.c
 * Defined in ncp_eioa_mac_phy_common.c
 */
ncp_st_t
ncp_dev_eioa_mac_an_stop(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

/*
 * called from ncp_dev_eioa_mac_an_start()
 * in ncp_eioa_mac_phy_common.c
 * Defined in ncp_eioa_mac_phy_common.c
ncp_st_t
ncp_dev_eioa_mac_c37_an_start(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);
 */

/*
 * called from ncp_dev_eioa_mac_an_stop()
 * in ncp_eioa_mac_phy_common.c
 * Defined in ncp_eioa_mac_phy_common.c
ncp_st_t
ncp_dev_eioa_mac_c37_an_stop(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);
 */

/*
 * called from ncp_dev_eioa_mac_an_start()
 * in ncp_eioa_mac_phy_common.c
 * Defined in ncp_eioa_mac_phy_common.c
ncp_st_t
ncp_dev_eioa_mac_c73_an_start(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);
 */

/*
 * called from ncp_dev_eioa_mac_an_stop()
 * in ncp_eioa_mac_phy_common.c
 * Defined in ncp_eioa_mac_phy_common.c
ncp_st_t
ncp_dev_eioa_mac_c73_stop(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);
 */

/*
 * called from ncp_dev_eioa_AN_start()
 * in ncp_dev_eioa.c
 * Defined in ncp_eioa_mac_phy_common.c
 */
ncp_st_t
ncp_dev_mac_phy_config_common(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

/*
 * called from ncp_dev_mac_phy_config_common()
 * in ncp_eioa_mac_phy_common.c
 * Defined in ncp_eioa_mac_mdio_phy.c
 */
ncp_st_t
ncp_eioa_mac_mdio_phy_config_common(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);
/*
 * called from ncp_dev_mac_phy_config_common()
 * in ncp_eioa_mac_phy_common.c
 * Defined in ncp_eioa_mac_custom_phy.c
 */
ncp_st_t
ncp_eioa_mac_custom_phy_config_common(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);


/*
 * called from ncp_dev_eioa_AN_start()
 * in ncp_dev_eioa.c
 * Defined in ncp_eioa_mac_phy_common.c
 */
ncp_st_t
ncp_dev_eioa_mac_phy_init(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

/*************** Begin 35xx prototypes ***************/
/* 
 * Called from ncp_dev_mac_phy_handle_link_timer()
 * in ncp_dev_eioa.c
 * Defined in ncp_eioa_mac_phy_common.c
 */
ncp_st_t
ncp_dev_mac_an_intr_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);
    
/*
 * called from ncp_dev_eioa_AN_start()
 * in ncp_dev_eioa.c
 * Defined in ncp_eioa_mac_phy_common.c
 */
ncp_st_t
ncp_dev_eioa_mac_an_start_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

/*
 * called from ncp_dev_eioa_AN_stop()
 * in ncp_dev_eioa.c
 * Defined in ncp_eioa_mac_phy_common.c
 */
ncp_st_t
ncp_dev_eioa_mac_an_stop_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

/*
 * called from ncp_dev_eioa_AN_start_35xx()
 * in ncp_dev_eioa.c
 * Defined in ncp_eioa_mac_phy_common.c
 */
ncp_st_t
ncp_dev_eioa_mac_phy_init_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);
/*
 * called from ncp_dev_eioa_AN_start_35xx()
 * in ncp_dev_eioa.c
 * Defined in ncp_eioa_mac_phy_common.c
 */
ncp_st_t
ncp_dev_mac_phy_config_common_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

/*************** End 35xx prototypes ***************/

/* 
 * Called from ncp_dev_mac_phy_handle_link_timer()
 * in ncp_dev_eioa.c
 * Defined in ncp_eioa_mac_phy_common.c
 */
ncp_st_t
ncp_dev_mac_an_intr_55xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

/*
 * called from ncp_dev_eioa_AN_start()
 * in ncp_dev_eioa.c
 * Defined in ncp_eioa_mac_phy_common.c
 */
ncp_st_t
ncp_dev_eioa_mac_an_start_55xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

/*
 * called from ncp_dev_eioa_AN_stop()
 * in ncp_dev_eioa.c
 * Defined in ncp_eioa_mac_phy_common.c
 */
ncp_st_t
ncp_dev_eioa_mac_an_stop_55xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

/*
 * called from ncp_dev_eioa_AN_start_55xx()
 * in ncp_dev_eioa.c
 * Defined in ncp_eioa_mac_phy_common.c
 */
ncp_st_t
ncp_dev_eioa_mac_phy_init_55xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);
/*
 * called from ncp_dev_eioa_AN_start_55xx()
 * in ncp_dev_eioa.c
 * Defined in ncp_eioa_mac_phy_common.c
 */
ncp_st_t
ncp_dev_mac_phy_config_common_55xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

/*
 * called from ncp_dev_eioa_mac_an_start()
 * in ncp_eioa_mac_phy_common.c
 * called from ncp_dev_mac_phy_handle_link_timer()
 * in ncp_dev_eioa.c
 * called from ncp_eioa_mac_link_status_get_blocking()
 * in ncp_dev_eioa.c
 * Defined in ncp_dev_eioa.c
 */
ncp_st_t
ncp_dev_mac_phy_link_timer_start(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags,
    ncp_uint32_t owner);

/*
 * called from ncp_dev_eioa_mac_an_stop()
 * in ncp_eioa_mac_phy_common.c
 * called from ncp_eioa_mac_link_status_get_blocking()
 * in ncp_dev_eioa.c
 * Defined in ncp_dev_eioa.c
 */
ncp_st_t
ncp_dev_mac_phy_link_timer_stop(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags,
    ncp_uint32_t owner);

/*
 * Called from ncp_eioa_phy_reg_set()
 * in ncp_dev_eioa.c
 * Defined in ncp_eioa_mac_custom_phy.c
 */
ncp_st_t
ncp_dev_custom_phy_reg_set(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t regNum,
    ncp_uint32_t regVal,
    ncp_uint32_t flags);

/*
 * Called from ncp_eioa_phy_reg_get()
 * in ncp_dev_eioa.c
 * Defined in ncp_eioa_mac_custom_phy.c
 */
ncp_st_t
ncp_dev_custom_phy_reg_get(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t regNum,
    ncp_uint32_t *regVal,
    ncp_uint32_t flags);

ncp_st_t
ncp_dev_phy_agere_et1081_init(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

ncp_st_t
ncp_dev_mac_phy_agere_et1081_get_speed(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_phy_speed_t *speed,
    ncp_uint32_t flags);

ncp_st_t
ncp_dev_phy_vitess_vsc8634_init(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

ncp_st_t
ncp_dev_mac_phy_vitess_vsc8634_get_speed(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_phy_speed_t *speed,
    ncp_uint32_t flags);

ncp_uint32_t
ncp_dev_reverse(
    ncp_uint32_t value,
    ncp_uint32_t width);

ncp_st_t
ncp_dev_phy_vitess_vsc8574_init(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

ncp_st_t
ncp_dev_mac_phy_vitess_vsc8574_get_speed(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_phy_speed_t *speed,
    ncp_uint32_t flags);

#ifdef __cplusplus
}
#endif

#endif /* _NCP_DEV_EIOA_MAC_H_ */

