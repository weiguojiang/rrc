/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


#ifndef _NCP_EIOA_HSS_35XXH_
#define _NCP_EIOA_HSS_35XXH_

#include "ncp_types.h"
#include "ncp_bitmap.h"
#include "ncp_eioa_hss.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    NCP_EIOA_PHY0_CFG = 5,
    NCP_EIOA_PHY0_SERDES,
    NCP_EIOA_PHY1_CFG = 11,
    NCP_EIOA_PHY1_SERDES
} ncp_eioa_phy_node_id_t;
    
/*
 * Init Routines
 */
ncp_st_t
ncp_eioa_hss_init_35xx(
    void *hdl,
    ncp_eioa_phy_node_id_t node_id,
    ncp_eioa_phy_rate_mode_t lane0_rate,
    ncp_eioa_phy_rate_mode_t lane1_rate,
    ncp_eioa_phy_rate_mode_t lane2_rate,
    ncp_eioa_phy_rate_mode_t lane3_rate,
    ncp_eioa_hss_init_data data[]
);

ncp_st_t
ncp_eioa_hss_lane_rate_get_35xx(
    ncp_t *ncp,
    ncp_uint32_t hss,
    ncp_eioa_phy_rate_mode_t *lane_rate);

ncp_st_t
ncp_eioa_hss_lanerate_validate_35xx(
    ncp_t *ncp,
    ncp_eioa_slot_t slot_num,
    ncp_eioa_phy_rate_mode_t *lane_rate);

ncp_st_t
ncp_eioa_hss_lanerate_change_35xx(
    void *hdl,
    ncp_uint32_t hss_num,
    ncp_uint32_t lane_num,
    ncp_eioa_port_config_switchover_t *new_config);

ncp_st_t
ncp_eioa_hss_lane_enable_set_35xx(
    void *hdl,
    ncp_uint32_t hss_num,
    ncp_uint32_t lane_num,
    ncp_bool_t enable_flag);

#ifdef __cplusplus
}
#endif

#endif /* _NCP_EIOA_HSS_35XX_H_ */

