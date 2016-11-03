/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


#ifndef __NCP_DEV_EIOA_35XX_H__
#define __NCP_DEV_EIOA_35XX_H__

ncp_st_t
ncp_dev_eioa_alloc_35xx(
    ncp_dev_hdl_t devHdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

ncp_st_t
ncp_eioa_kfree(ncp_dev_hdl_t devHdl,
    ncp_eioa_t *eioa);

ncp_st_t
ncp_dev_eioa_destroy_35xx(
    ncp_dev_hdl_t devHdl);

ncp_st_t
ncp_dev_eioa_port_alloc_35xx(
    ncp_dev_hdl_t devHdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

ncp_st_t
ncp_dev_eioa_sync_35xx(
    ncp_dev_hdl_t devHdl,
    ncp_macChan_t macChan,
    void *eioa_ptr,
    ncp_uint32_t eioa_size,
    ncp_uint32_t flags);

ncp_st_t
ncp_dev_eioa_port_sync_35xx(
    ncp_dev_hdl_t devHdl,
    ncp_macChan_t macChan,
    void *port_ptr,
    void *mcast_ptr,
    void *shaper_ptr,
    void *scheduler_ptr,
    ncp_uint32_t port_size,
    ncp_uint32_t mcast_size,
    ncp_uint32_t shaper_size,
    ncp_uint32_t scheduler_size,
    ncp_uint32_t flags);

ncp_st_t
ncp_eioa_port_enable_set_35xx(
    void *     hdl,
    ncp_macChan_t macChan,
    ncp_bool_t rx_enable,
    ncp_bool_t tx_enable);

ncp_st_t
ncp_eioa_port_enable_get_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t *rx_enable,
    ncp_bool_t *tx_enable);

ncp_st_t
ncp_dev_eioa_ipp_port_vlan_count_update_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint16_t vlanCount);

ncp_st_t
ncp_eioa_qinq_get_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t *qinq_enable);

ncp_st_t
ncp_eioa_qinq_set_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t qinq_enable);

ncp_st_t
ncp_eioa_auto_neg_set_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t enable_flag,
    ncp_bool_t restart_flag);

ncp_st_t
ncp_eioa_auto_neg_get_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t *enable_flag,
    ncp_mac_speed_t *speed,
    ncp_bool_t *link_force,
    ncp_bool_t *link_good,
    ncp_bool_t *auto_neg_complete);

ncp_st_t
ncp_eioa_mac_statistics_get_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_mac_txstat_t *mac_tx_stats,
    ncp_mac_rxstat_t *mac_rx_stats,
    ncp_bool_t clr_flg);

ncp_st_t
ncp_eioa_slot_overclock_get_35xx(
    void *     hdl,
    ncp_eioa_num_t eioaNum,
    ncp_eioa_slot_t eioaSlot,
    ncp_mac_speed_t *speed,
    ncp_bool_t *duplex,
    ncp_uint32_t *flags);

ncp_st_t
ncp_eioa_slot_overclock_set_35xx(
    void *     hdl,
    ncp_eioa_num_t eioaNum,
    ncp_eioa_slot_t eioaSlot,
    ncp_mac_speed_t speed,
    ncp_bool_t duplex,
    ncp_uint32_t flags);

ncp_st_t
ncp_mac_speed_duplex_get_35xx(
    void *     hdl,
    ncp_macChan_t macChan,
    ncp_mac_speed_t *speed,
    ncp_bool_t *duplex);

ncp_st_t
ncp_mac_speed_duplex_set_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_mac_speed_t speed,
    ncp_bool_t duplex);

ncp_st_t
ncp_eioa_tx_ts_get_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t tsIndex,
    ncp_uint32_t *tStamp);

ncp_st_t
ncp_eioa_tx_ts_get_poll_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t tsIndex,
    ncp_uint32_t nPollCount,
    ncp_uint32_t uPollDelay,
    ncp_uint32_t *tStamp);

ncp_st_t
ncp_eioa_tag_config_get_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t *stop_offset,
    ncp_uint32_t *start_offset,
    ncp_uint32_t *tag_msb,
    ncp_bool_t *enable_flag);

ncp_st_t
ncp_eioa_tag_config_set_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t stop_offset,
    ncp_uint32_t start_offset,
    ncp_uint32_t tag_msb);

ncp_st_t
ncp_eioa_tag_config_set_enable_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t stop_offset,
    ncp_uint32_t start_offset,
    ncp_uint32_t tag_msb,
    ncp_bool_t enable_flag);

ncp_st_t
ncp_eioa_tag_enable_get_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t *enable_flag);

ncp_st_t
ncp_eioa_tag_enable_set_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t enable_flag);

ncp_st_t
ncp_eioa_crc_set_35xx(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_bool_t crc_append,
    ncp_bool_t crc_appendbad,
    ncp_bool_t crc_strip);

ncp_st_t
ncp_eioa_crc_get_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t *crc_append,
    ncp_bool_t *crc_appendbad,
    ncp_bool_t *crc_strip);

ncp_st_t
ncp_eioa_vlan_config_get_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t *vlan_type1,
    ncp_uint32_t *vlan_type0);

ncp_st_t
ncp_eioa_vlan_config_set_35xx(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t vlan_type1,
    ncp_uint32_t vlan_type0);

ncp_st_t
ncp_eioa_promisc_enable_35xx(
    void *hdl,
    ncp_macChan_t macChan);

ncp_st_t
ncp_eioa_promisc_disable_35xx(
    void *hdl,
    ncp_macChan_t macChan);

ncp_st_t
ncp_eioa_unicast_filter_get_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t *enable_flag,
    ncp_uint8_t *unicast_addr_1,
    ncp_uint8_t *unicast_addr_2,
    ncp_uint8_t *unicast_addr_3);

ncp_st_t
ncp_eioa_unicast_filter_set_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t enable_flag,
    ncp_uint8_t *unicast_addr_1,
    ncp_uint8_t *unicast_addr_2,
    ncp_uint8_t *unicast_addr_3);

ncp_st_t
ncp_eioa_unicast_filter_enable_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t enable_flag);

ncp_st_t
ncp_eioa_multicast_filter_add_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t *table_index,
    ncp_uint8_t *multicast_addr,
    ncp_uint32_t *table_size);

ncp_st_t
ncp_eioa_multicast_filter_delete_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t table_index,
    ncp_uint32_t *table_size);

ncp_st_t
ncp_eioa_multicast_filter_set_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t table_index,
    ncp_uint8_t *multicast_addr,
    ncp_uint32_t *table_size);

ncp_st_t
ncp_eioa_multicast_filter_get_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t table_index,
    ncp_uint8_t *multicast_addr,
    ncp_uint32_t *table_size,
    ncp_bool_t *enable_flag);

ncp_st_t
ncp_eioa_multicast_filter_enable_35xx(
    void * hdl,
    ncp_macChan_t macChan,
    ncp_bool_t    enable_flag);

ncp_st_t
ncp_dev_update_phy_status_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flag);

ncp_st_t
ncp_eioa_mac_link_status_get_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_mac_phy_status_t *phyStatus,
    ncp_uint32_t *mask);

ncp_st_t
ncp_eioa_mac_link_status_get_blocking_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_mac_phy_status_t *phyStatus,
    ncp_uint32_t *mask);

ncp_st_t
ncp_eioa_mac_addr_get_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint8_t *mac_addr);

ncp_st_t
ncp_eioa_mac_addr_set_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint8_t *mac_addr);

ncp_st_t
ncp_eioa_status_get_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_port_t *port_stat,
    ncp_bool_t *port_cfg_ok);

ncp_st_t
ncp_eioa_phy_reg_read_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t reg_num,
    ncp_uint32_t *reg_val,
    ncp_uint32_t flags);

ncp_st_t
ncp_eioa_phy_reg_get_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t reg_num,
    ncp_uint32_t *reg_val);

ncp_st_t
ncp_eioa_phy_reg_write_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t reg_num,
    ncp_uint32_t reg_val,
    ncp_uint32_t flags);

ncp_st_t
ncp_eioa_phy_reg_set_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t reg_num,
    ncp_uint32_t reg_val);

ncp_st_t
ncp_eioa_chan_loopback_set_35xx(
    void           *hdl,
    ncp_macChan_t  macChan,
    ncp_loopback_t loopbackType,
    ncp_bool_t     enable);

ncp_st_t
ncp_eioa_chan_loopback_write_35xx(
    void *hdl,
    ncp_macChan_t  macChan,
    ncp_loopback_t loopbackType,
    ncp_bool_t     enable,
    ncp_uint32_t   flags);

ncp_st_t
ncp_eioa_mac_timer_shutdown_35xx(
    void           *hdl,
    ncp_macChan_t  macChan,
    ncp_uint32_t   flags);

ncp_st_t
ncp_dev_eioa_AN_start_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

ncp_st_t
ncp_dev_eioa_AN_stop_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint32_t flags);

ncp_st_t
ncp_eioa_tx_max_pkt_size_set_35xx(void *hdl,
    ncp_macChan_t macChan,
    ncp_eioa_pktsize_t  packetSize);

ncp_st_t
ncp_eioa_tx_max_pkt_size_get_35xx(void *hdl,
    ncp_macChan_t macChan,
    ncp_eioa_pktsize_t *packetSize);

ncp_st_t
ncp_eioa_rx_max_pkt_size_set_35xx(void *hdl,
    ncp_macChan_t macChan,
    ncp_eioa_pktsize_t packetSize);

ncp_st_t
ncp_eioa_rx_max_pkt_size_get_35xx(void *hdl,
    ncp_macChan_t macChan,
    ncp_eioa_pktsize_t *packetSize);

ncp_st_t
ncp_eioa_vp_id_get_35xx(void *hdl,
    ncp_macChan_t macChan,
    char *vpName,
    ncp_uint8_t *vp_Id,
    ncp_uint32_t vpPriority);

ncp_st_t
ncp_eioa_vp_id_set_35xx(void *hdl,
    ncp_macChan_t macChan,
    char *vpName,
    ncp_uint32_t vpPriority);

ncp_st_t
ncp_eioa_port_vp_get_35xx(void *hdl,
    ncp_macChan_t macChan,
    ncp_uint8_t type,
    char* vpname,
    ncp_uint8_t* vflow_id,
    ncp_eioa_port_vp_info_t* attrs);

ncp_st_t
ncp_eioa_port_vp_set_35xx(void *hdl,
    ncp_macChan_t macChan,
    ncp_uint8_t type,
    char* vpname,
    ncp_eioa_port_vp_info_t* attrs);

ncp_st_t
ncp_eioa_mac_flow_ctrl_set_35xx(void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t pauseEnable,
    ncp_uint32_t pauseType,
    ncp_uint16_t pauseTime);

ncp_st_t
ncp_eioa_mac_flow_ctrl_get_35xx(void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t *pauseEnable,
    ncp_uint32_t pauseType,
    ncp_uint16_t *pauseTime);

ncp_st_t
ncp_eioa_stats_max_pkt_length_get_35xx(void *hdl,
    ncp_macChan_t macChan,
    ncp_uint16_t *maxPacketLength);
ncp_st_t
ncp_eioa_stats_max_pkt_length_set_35xx(void *hdl,
    ncp_macChan_t macChan,
    ncp_uint16_t  maxPacketLength);

ncp_st_t
ncp_eioa_port_ts_marker_delay_get_35xx(void *hdl,
    ncp_macChan_t macChan,
    ncp_uint16_t *md_tx,
    ncp_uint16_t *md_rx);

ncp_st_t
ncp_eioa_timestamp_resolution_get_35xx(
    void* hdl,
    ncp_macChan_t macChan,
    ncp_timestamp_resolution_t *resolution);
#endif
