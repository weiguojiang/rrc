/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


#ifndef _NCP_EIOA_HSS_55XXH_
#define _NCP_EIOA_HSS_55XXH_

#include "ncp_types.h"
#include "ncp_bitmap.h"
#include "ncp_eioa_hss.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    NCP_EIOA_PHY0_CFG = 0,
    NCP_EIOA_PHY0_SERDES,
    NCP_EIOA_PHY0_AD0,
    NCP_EIOA_PHY0_AD1,
    NCP_EIOA_PHY0_AD2,
    NCP_EIOA_PHY0_AD3,
    NCP_EIOA_PHY1_CFG = 6,
    NCP_EIOA_PHY1_SERDES,
    NCP_EIOA_PHY1_AD0,
    NCP_EIOA_PHY1_AD1,
    NCP_EIOA_PHY1_AD2,
    NCP_EIOA_PHY1_AD3,
    NCP_EIOA_PHY2_CFG = 12,
    NCP_EIOA_PHY2_SERDES,
    NCP_EIOA_PHY2_AD0,
    NCP_EIOA_PHY2_AD1,
    NCP_EIOA_PHY2_AD2,
    NCP_EIOA_PHY2_AD3,
    NCP_EIOA_PHY3_CFG = 18,
    NCP_EIOA_PHY3_SERDES,
    NCP_EIOA_PHY3_AD0,
    NCP_EIOA_PHY3_AD1,
    NCP_EIOA_PHY3_AD2,
    NCP_EIOA_PHY3_AD3,
    NCP_EIOA_PHY4_CFG = 24,
    NCP_EIOA_PHY4_SERDES,
    NCP_EIOA_PHY4_AD0,
    NCP_EIOA_PHY4_AD1,
    NCP_EIOA_PHY4_AD2,
    NCP_EIOA_PHY4_AD3
} ncp_eioa_phy_node_id_t;
    
/*
 * Init Routines
 */
ncp_st_t
ncp_eioa_hss_init_55xx(
    void *hdl,
    ncp_eioa_phy_node_id_t node_id,
    ncp_eioa_phy_rate_mode_t lane0_rate,
    ncp_eioa_phy_rate_mode_t lane1_rate,
    ncp_eioa_phy_rate_mode_t lane2_rate,
    ncp_eioa_phy_rate_mode_t lane3_rate,
    ncp_eioa_hss_init_data data[]
);

/*
 * Routine to setup link for 10GBASEKR and start link training
 */
ncp_st_t
ncp_eioa_hss_ad_training_start_55xx(
    void *hdl,
     ncp_macChan_t macChan);

#ifdef PRE_GA
ncp_st_t
ncp_eioa_hss_ad_training_setup_55xx(
    void *hdl, ncp_macChan_t macChan);
#else
ncp_st_t
ncp_eioa_hss_ad_training_config_55xx(
    void *hdl, ncp_macChan_t macChan);
#endif

ncp_st_t
ncp_eioa_hss_lane_rate_get(
    ncp_t *ncp,
    ncp_uint32_t hss,
    ncp_eioa_phy_rate_mode_t *lane_rate);

ncp_st_t
ncp_eioa_hss_lanerate_validate(
    ncp_t *ncp,
    ncp_eioa_num_t eioa_num,
    ncp_eioa_phy_rate_mode_t *lane_rate);

ncp_st_t
ncp_eioa_hss_lanerate_change_55xx(
    void *hdl,
    ncp_uint32_t hss_num,
    ncp_uint32_t lane_num,
    ncp_eioa_port_config_switchover_t *new_config);

ncp_st_t
ncp_eioa_hss_lane_enable_set_55xx(
    void *hdl,
    ncp_uint32_t hss_num,
    ncp_uint32_t lane_num,
    ncp_bool_t enable_flag);

#ifdef __cplusplus
}
#endif

#endif /* _NCP_EIOA_HSS_55XX_H_ */

