/**************************************************************************
 **                                                                       *
 **                           Intel CONFIDENTIAL                            *
 **                           PROPRIETARY NOTE                            *
 **                                                                       *
 **    This software contains information confidential and proprietary    *
 **    to Intel Corporation.  It shall not be reproduced in whole or in *
 **    part, or transferred to other documents, or disclosed to third     *
 **    parties, or used for any purpose other than that for which it was  *
 **    obtained, without the prior written consent of Intel Corporation.*
 **    (c) 2008-2014, Intel Corporation.  All rights reserved.          *
 **                                                                       *
 **                                                                       *
 **  **********************************************************************/

/*! @file      ncp_eioa_core.h
 *  @brief     EIOA Core
 *
 */

#ifndef _NCP_EIOA_CORE_H_
#define _NCP_EIOA_CORE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Public Definitions */

/* Public Enumerated Types */

/*!
 * @brief EIOA 
 */

/* Public Structures */

/*!
 * @ingroup _eioa_port_
 * @struct ncp_port_egress_options_t
 * @brief Port Egress Options
 */ 
typedef struct ncp_port_egress_options_s {
    ncp_bool_t  isMirroringPort;                   /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t  enableQinQCorruptCrcOnError;       /*!< For AXX3500/AXX5500 */ 
    ncp_uint16_t outerVlanEtherType;               /*!< For AXX3500/AXX5500 */ 
    ncp_uint16_t innerVlanEtherType;               /*!< For AXX3500/AXX5500 */ 
} ncp_port_egress_options_t; 

/*!
 * @ingroup _eioa_port_
 * @struct ncp_port_ingress_options_t
 * @brief Port Ingress Options
 */ 
typedef struct ncp_port_ingress_options_s {
    ncp_bool_t  enableSwitching;                   /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t  bypassAccessControl;                       /*!< For AXX5500 */
    ncp_bool_t  bypassPolicyBasedRouting;                  /*!< For AXX5500 */
    ncp_bool_t  enableVpe;                         /*!< For AXX3500/AXX5500 */
    ncp_bool_t  useBridgingVPs;                    /*!< For AXX5500 */
    ncp_bool_t  deleteOnParserDiscard;             /*!< For AXX3500/AXX5500 */
    ncp_bool_t  deleteOnPolicerDiscard;            /*!< For AXX5500 */
    ncp_bool_t  deleteOnMulticastPolicerDiscard;           /*!< For AXX5500 */
    ncp_bool_t  deleteOnAclDeny;                           /*!< For AXX5500 */
    ncp_bool_t  nonSwitchingGenericDiscardDeletePacket;     /*!< Depracated */
    ncp_int32_t defaultVlanId;                     /*!< For AXX3500/AXX5500 */
    ncp_int32_t defaultCvlanId;                    /*!< For AXX3500/AXX5500 */
    ncp_bool_t  setTaskErrorForFramerErrorPackets;         /*!< For AXX5500 */
    ncp_bool_t  setTaskErrorForRuntPackets;                /*!< For AXX5500 */
} ncp_port_ingress_options_t; 

/*!
 * @ingroup _eioa_port_
 * @struct ncp_ipp_vp_options_t
 * @brief Ingress Virtual Pipeline Packet Parser Options
 */ 
typedef struct ncp_ipp_vp_options_s {
    ncp_bool_t enableEsmcVp;                                /*!< Depracated */
    ncp_bool_t enableL2FramerErrorVp;               /*!< For AXX3500/AXX5500 */
    ncp_bool_t enableL3FramerErrorVp;               /*!< For AXX3500/AXX5500 */
    ncp_bool_t enableL4FramerErrorVp;               /*!< For AXX3500/AXX5500 */
    ncp_bool_t enableOsspVp;                        /*!< For AXX3500/AXX5500 */
    ncp_bool_t enableMacSecControlledVp;                    /*!< For AXX5500 */
    ncp_bool_t enableMacSecUnControlledVp;                  /*!< For AXX5500 */
} ncp_ipp_vp_options_t;

/*!
 * @ingroup _eioa_port_
 * @struct ncp_ipp_options_t
 * @brief Ingress Packet Parser Options
 */ 
typedef struct ncp_ipp_struct_s 
{
    ncp_bool_t discardPausePackets;                 /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t discardControlPackets;               /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t discardVlanCfiPackets;               /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t discardBadLengthPackets;             /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t discardInvalidVlanidPackets;         /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t discardIpv4OptionPackets;            /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t errorIpv4OptionPackets;              /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t enableMpls;                          /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t enableCustomerDoubleVlanTags;        /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t enableDoubleVlanParsing;             /*!< For AXX3500/AXX5500 */
    ncp_bool_t discardUnknownIpProtocolPackets;     /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t discardTaggedVlan;                   /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t discardUntaggedVlan;                 /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t discardUnknownEtherType;             /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t discardUnknownEncapsulation;         /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t enableBridgeGARPProtocolSnoop;       /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t useDscpAsPriorityForTasks;           /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t enableBroadcastRateLimit;            /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t enableMulticastRateLimit;            /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t enableReplaceSourceMacAddress;       /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t enableUpdateHeader;                  /*!< For AXX3500/AXX5500 */ 
} ncp_ipp_options_t;

/*!
 * @ingroup _eioa_port_
 * @struct ncp_epp_options_t
 * @brief Egress Packet Parser modification options
 */

typedef struct ncp_epp_options_s {
    ncp_bool_t replaceSourceMacAddress;             /*!< For AXX3500/AXX5500 */
    ncp_uint8_t routerSourceMacAddress[6];          /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t overrideOuterVlanCos;                /*!< For AXX3500/AXX5500 */ 
    ncp_uint8_t outerVlanCos;                       /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t updateIpv4Ipv6Dscp;                  /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t modifyCVlanTagLocalTraffic;          /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t modifyCVlanTagSystemTraffic;         /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t updateHeader;                        /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t updateCos;                           /*!< For AXX3500/AXX5500 */ 
    ncp_bool_t errorQinQUntaggedPackets;            /*!< For AXX3500/AXX5500 */ 
} ncp_epp_options_t;

/*!
 * @ingroup _eioa_port_
 * @struct ncp_epp_mpls_options_t
 * @brief Egress Packet Parser MPLS options for AXX5600
 */
typedef struct ncp_epp_mpls_options_s {
    /*!
     * @brief Whether to corrupt CRC when MPLS operations encounter an error.
     * @details MPLS operations that can result in errors are
     * <ul>
     * <li> TTL is zero before decrementing TTL
     * <li> TTL becomes zero after decrementing
     * <li> Try to pop the last label
     * <li> If there are more than 2 VLAN tags in the packet
     * </ul>
     */
    ncp_bool_t crcErrorOnMplsError;
    /*!
     * @brief Whether to select MPLS priority value based on the MPLS priority of the incoming packet or whether to use the COS value provided in \ref ncp_epp_mpls_options_t::mplsCos
     * @details When set select COS value provided in \ref ncp_epp_mpls_options_t::mplsCos
     */
    ncp_bool_t overrideMplsCos;
    /*!
     * @brief COS value to use when \ref ncp_epp_mpls_options_t::overrideMplsCos is set
     * @details This COS value will be used when adding or modifying a MPLS label.
     */
    ncp_uint8_t mplsCos;
} ncp_epp_mpls_options_t;

/*!
 * @ingroup _eioa_port_
 * @enum ncp_port_pause_t
 * @brief Port Pause types
 */
typedef enum {
    pauseQbb_802_1 = 0,
    /* 802_3: not supported by ncp_eioa_port_pause_set() API */
    pause802_3
} ncp_port_pause_t;

/*!
 * @ingroup _eioa_port_
 * @struct ncp_port_pause_options_t
 * @brief 802.1 Qbb Pause options 
 * NOTE: 
 * pauseType and pauseTime are not used when in 802.1 PFC pause mode as they are applicable to 802.3 mode only.
 * 802.3 mode is not supported by ncp_eioa_port_pause_set()/get() APIs. 
 * When in 802.3 standard pause mode , ncp_eioa_mac_flow_ctrl_set() and get() APIs are to be used.
 * <pre>
 * cosValue0_taskPriority	802.1 Qbb priorities for class-of-service 0 with range 0xff-0x00 for 8 levels (55xx) /4 levels (35xx)
 * cosValue1_taskPriority	802.1 Qbb priorities for class-of-service 1 with range 0xff-0x00 for 8 levels (55xx)/4 levels (35xx)
 * cosValue2_taskPriority	802.1 Qbb priorities for class-of-service 2 with range 0xff-0x00 for 8 levels (55xx)/4 levels (35xx)
 * cosValue3_taskPriority	802.1 Qbb priorities for class-of-service 3 with range 0xff-0x00 for 8 levels (55xx)/4 levels (35xx)
 * cosValue4_taskPriority	802.1 Qbb priorities for class-of-service 4 with range 0xff-0x00 for 8 levels (55xx)
 * cosValue5_taskPriority	802.1 Qbb priorities for class-of-service 5 with range 0xff-0x00 for 8 levels (55xx)
 * cosValue6_taskPriority	802.1 Qbb priorities for class-of-service 6 with range 0xff-0x00 for 8 levels (55xx)
 * cosValue7_taskPriority	802.1 Qbb priorities for class-of-service 7 with range 0xff-0x00 for 8 levels (55xx)
 * pausePacketMode		IEEE 802.1 PFC Pause 
 * allowUcast			Allow/Deny unicast IEEE 802.1 PFC Pause frames to be recognized by receiver
 * pauseEnable			Enable/Disable IEEE 802.1 PFC Pause
 * pauseType 			802.3 Pause config of type NCP_PAUSE_RESPOND/FILTER/FORWARD/GENERATE/GENERATE_DROP_RX (ignored as not applicable to 802.1 mode)
 * pauseTime			802.3 16-bit MAC Pause Quanta  (ignored as not applicable to 802.1 mode)
 *</pre>
 */

typedef struct ncp_port_pause_options_s {
    ncp_int32_t cosValue0_taskPriority;
    ncp_int32_t cosValue1_taskPriority;
    ncp_int32_t cosValue2_taskPriority;
    ncp_int32_t cosValue3_taskPriority;
    ncp_int32_t cosValue4_taskPriority;
    ncp_int32_t cosValue5_taskPriority;
    ncp_int32_t cosValue6_taskPriority;
    ncp_int32_t cosValue7_taskPriority;
    ncp_port_pause_t pausePacketMode;
    ncp_bool_t allowUcast;
    ncp_bool_t pauseEnable;
    ncp_uint32_t pauseType;
    ncp_uint16_t pauseTime;
} ncp_port_pause_options_t;
    
/*!
 * @ingroup _eioa_port_
 * @struct ncp_port_counters_t
 * @brief port counters 
 * <pre>
 * rx_pkt_drop_ctr                        Rx Packet Drop Counter
 * oversize_rx_pkt_drop_ctr               Oversize Rx Packet Counter 
 * oversize_tx_pkt_drop_ctr               Oversize Tx Packet Drop Counter
 * debug_pkt_ctr                          Debug Packet Counter 
 * policer_discard_ctr                    Policer discard counter
 * policer_mcast_discard_ctr              Policer multicast discard counter 
 * acl_deny_ctr                           ACL deny counter
 * bridging_null_map_drop_ctr             Bridging Null Destination Map Packet Drop Counter
 * bridging_null_dest_map_ctr             Bridging null destination map counter
 * adjust_null_dest_map_ctr               Adjusted null destination map counter 
 * ccm_drop_ctr                           CCM Drop Counter
 * tdgl_task_err_ctr                      TDGL task error counter
 * tdgl_framer_err_drop_ctr               TDGL Framer Error Packet Drop Counter
 * tdgl_fdata_delete_framer_err_drop_ctr  TDGL FetchData Delete Framer Error Packet Drop Counte  
 * tdgl_fdata_delete_pkt_drop_ctr         TDGL FetchData Delete Packet Drop Counter 
 * multiple_bits_pkt_ctr                  Multiple Bits Packet Counter
 *</pre>
 */

typedef struct  ncp_port_counters_s {
    ncp_uint32_t rx_pkt_drop_ctr;
    ncp_uint32_t oversize_rx_pkt_drop_ctr;
    ncp_uint32_t oversize_tx_pkt_drop_ctr;
    ncp_uint32_t debug_pkt_ctr;
    ncp_uint32_t policer_discard_ctr;
    ncp_uint32_t policer_mcast_discard_ctr;
    ncp_uint32_t acl_deny_ctr;
    ncp_uint32_t bridging_null_map_drop_ctr;
    ncp_uint32_t bridging_null_dest_map_ctr;
    ncp_uint32_t adjust_null_dest_map_ctr;
    ncp_uint32_t ccm_drop_ctr;
    ncp_uint32_t tdgl_task_err_ctr;
    ncp_uint32_t tdgl_framer_err_drop_ctr;
    ncp_uint32_t tdgl_fdata_delete_framer_err_drop_ctr;
    ncp_uint32_t tdgl_fdata_delete_pkt_drop_ctr;
    ncp_uint32_t multiple_bits_pkt_ctr;

} ncp_port_counters_t;

/*!
 * @ingroup _eioa_port_
 * @struct ncp_parser_discard_counters_t
 * @brief parser discard counters  
 * <pre>
 * parser_cfi_discard_ctr              Parser CFI discard counter 
 * parser_vlan_tagged_discard_ctr      Parser VLAN tagged discard counter 
 * parser_vlan_untagged_discard_ctr    Parser VLAN untagged discard counter
 * parser_pause_discard_ctr            Parser pause discard counter
 * parser_control_discard_ctr          Parser control discard counter
 * parser_qinq_discard_ctr             Parser QinQ discard counter
 * parser_unknown_encap_discard_ctr    Parser unknown encap discard counter
 * parser_protocol_discard_ctr         Parser protocol discard counter  
 * parser_ethertype_discard_ctr        Parser ethertype discard counter
 * parser_vlan_assign_discard_ctr      Parser VLAN assignment discard counter
 * parser_snap_length_discard_ctr      Parser snap length discard counter
 *</pre>
 */
typedef struct ncp_parser_discard_counters_s {
    ncp_uint32_t parser_cfi_discard_ctr;
    ncp_uint32_t parser_vlan_tagged_discard_ctr;
    ncp_uint32_t parser_vlan_untagged_discard_ctr;
    ncp_uint32_t parser_pause_discard_ctr;
    ncp_uint32_t parser_control_discard_ctr;
    ncp_uint32_t parser_qinq_discard_ctr;
    ncp_uint32_t parser_unknown_encap_discard_ctr;
    ncp_uint32_t parser_protocol_discard_ctr;
    ncp_uint32_t parser_ethertype_discard_ctr;
    ncp_uint32_t parser_vlan_assign_discard_ctr;
    ncp_uint32_t parser_snap_length_discard_ctr;

} ncp_parser_discard_counters_t;

/*!
 * @ingroup _eioa_port_
 * @struct ncp_misc_counters_t
 * @brief Counters other than port and parser counters 
 * mcast_fwd_pkt_drop_ctr              Multicast Forward Packet Drop Counter
 * s0_macsec_rx_control_pkt_ctr        MACsec Rx Control Packet Counter
 * s0_macsec_rx_uncontrol_pkt_ctr      MACsec Rx Uncontrol Packet Counter
 * s0_macsec_tx_control_pkt_ctr        MACsec Tx Control Packet Counter  
 * s0_macsec_tx_uncontrol_pkt_ctr      MACsec Tx Uncontrol Packet Counter 
 * global_unlearn_hash_ctr             Global Unlearned Hash Counter
 * mcast_pkt_ctr                       Multicast Packet Counter
 * til_task_error_ctr                  TIL Task Error Counter
 * tids_in_use_ctr                     Task IDs (TIDs) In Use Counter
 * task_drop_ctr                       Task Drop Counter 
 * til_tcri_data_err_pkt_ctr           TIL TCRI Data Error Packet Counter 
 * mcast_replication_pkt_drop_ctr      Multicast Replication Packet Drop Counter
 */
typedef struct ncp_misc_counters_s {
    ncp_uint32_t mcast_fwd_pkt_drop_ctr;
    ncp_uint32_t s0_macsec_rx_control_pkt_ctr;
    ncp_uint32_t s0_macsec_rx_uncontrol_pkt_ctr;
    ncp_uint32_t s0_macsec_tx_control_pkt_ctr;
    ncp_uint32_t s0_macsec_tx_uncontrol_pkt_ctr;
    ncp_uint32_t global_unlearn_hash_ctr;
    ncp_uint32_t mcast_pkt_ctr;
    ncp_uint32_t til_task_error_ctr;
    ncp_uint32_t tids_in_use_ctr;
    ncp_uint32_t task_drop_ctr;
    ncp_uint32_t til_tcri_data_err_pkt_ctr;
    ncp_uint32_t mcast_replication_pkt_drop_ctr;
} ncp_misc_counters_t;

/*!
 * @brief Data structure for MPLS Label get/set
 */
typedef struct ncp_eioa_mpls_label_s 
{
    /*!
     * @brief Index for the MPLS label entry. 0-255.
     */
    ncp_uint8_t mplsLabelIndex;
    
    /*!
     * @brief If cleared, TTL from MPLS label in packet will be used for all 
     * MPLS tags operated on. If set, TTL from this table will be used.
     */
    ncp_bool_t useTTL;
    
    /*!
     * @brief TTL to use for MPLS label(s) if useTTL is set.
     */
    ncp_uint8_t ttl;

    /*!
     * @brief If cleared, a push operation will only push the outermost tag. 
     * If set, a push operation will also cause the next tag to be replaced.
     */
    ncp_bool_t pushAndReplace;
    
    /*!
     * @brief MPLS label to be replaced in MPLS stack if replace operation or 
     * push operation and pushAndReplace is set.
     */
    ncp_uint32_t replacementLabel;

    /*!
     * @brief MPLS label to be pushed onto MPLS stack if push operation.
     */
    ncp_uint32_t newLabel;
} ncp_eioa_mpls_label_t;


/* Published APIs */

/*!
 * @ingroup _eioa_port_
 * @brief Set options for port backpressure using  IEEE 802.1 PFC frames 
 * @details
 * Defines the mapping of Class-Of-Service Value to task priority if IEEE 802.1 PFC frames is chosen.
 * Sets the type of pause packets used for port backpressure to PFC frames.
 * NOTE:
 * TX_PFC is the MAC statistic counter corresponding to IEEE 802.1 Qbb frames.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] *options  Pointer to an instance of ncp_port_pause_options_t,
 *              for values of modification options.
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_INVALID_PRIORITY
 *         <li> #NCP_ST_EIOA_PAUSE_MODE_NOT_SUPPORTED
 *         </ul>
 */
NCP_API ncp_st_t
ncp_eioa_port_pause_set(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_port_pause_options_t *options);

/*!
 * @ingroup _eioa_port_
 * @brief Get options for port backpressure settings
 * @details
 * Returns the mapping of Class-Of-Service Value to task priority for IEEE 802.1 PFC frames.
 * Gets the type of pause packets used for port backpressure.
 *
 * NOTE:
 * If pauseEnable returned is FALSE/0, then what is returned in pausePacketMode should be ignored.
 * 
 * NOTE:
 * pauseType and  pauseTime values returned by this API  are to be ignored. 
 * These are applicable to 802.3 mode only and not supported by this API. 
 * ncp_eioa_mac_flow_ctrl_get() API is to be used for querying these parameters in this mode. 
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] *options  Pointer to an instance of ncp_port_pause_options_t,
 *              for values of modification options.
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PAUSE_MODE_NOT_SUPPORTED
 *         </ul>
 */

NCP_API ncp_st_t
ncp_eioa_port_pause_get(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_port_pause_options_t *options);

/*!
 * @ingroup _eioa_port_
 * @brief  Set options to modify packet header fields on egress.
 * @details
 * Egress packet modification options allow packet fields to be modified,
 * such as MAC source/destination addresses IP Priority, and VLAN tags. <br>
 * In addition, up to two VLAN tags may be added/removed.
 * <br> Valid for <b>AXX3500</b> and <b>AXX5500</b> devices.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] *options  Pointer to an instance of ncp_epp_options_t, 
 *              for values of modification options. 
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_EIOA_COS_INVALID
 *         </ul>
 */
NCP_API ncp_st_t
ncp_eioa_port_egress_modification_options_set(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_epp_options_t *options);

/*!
 * @ingroup _eioa_port_
 * @brief  Get options for modified packet header fields on egress.
 * @details
 * Egress packet modification options allow packet fields to be modified,
 * such as MAC source/destination addresses IP Priority, and VLAN tags. <br>
 * In addition, up to two VLAN tags may be added/removed.
 * <br> Valid for <b>AXX3500</b> and <b>AXX5500</b> devices.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] *options  Pointer to an instance of ncp_epp_options_t, 
 *              for values of modification options. 
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         </ul>
 */
NCP_API ncp_st_t
ncp_eioa_port_egress_modification_options_get(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_epp_options_t *options);


/*!
 * @ingroup _eioa_port_
 * @brief  Set egress packet processing MPLS options
 * @details
 * <br> Valid for <b>AXX5600</b> device.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] *options  MPLS options to set
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         </ul>
 */
NCP_API ncp_st_t
ncp_eioa_port_egress_mpls_options_set(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_epp_mpls_options_t *options);

/*!
 * @ingroup _eioa_port_
 * @brief  Get egress packet processing MPLS options
 * @details
 * <br> Valid for <b>AXX5600</b> device.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] *options  MPLS options to retrieve
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         </ul>
 */
NCP_API ncp_st_t
ncp_eioa_port_egress_mpls_options_get(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_epp_mpls_options_t *options);


/*!
 * @ingroup _eioa_port_
 * @brief  Configure MPLS label modification entry.
 * @details
 * Configure a MPLS label modification entry for the given port. 
 * There could be up to 256 entries per port.
 * <br> Valid for <b>AXX5600</b> devices only.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number for which the MPLS lable entry is configured.
 * @param[in] *mplsLabel  Pointer to an instance of ncp_eioa_mpls_label_t 
 *            containing MPLS label information. 
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         </ul>
 */
NCP_API ncp_st_t
ncp_eioa_port_egress_mpls_label_set(
    ncp_hdl_t     hdl,
    ncp_macChan_t port,
    ncp_eioa_mpls_label_t *mplsLabel);

/*!
 * @ingroup _eioa_port_
 * @brief  Retrieve MPLS label modification entry.
 * @details
 * Retrieve a MPLS label modification entry for the given port. 
 * There could be up to 256 entries per port.
 * <br> Valid for <b>AXX5600</b> devices only.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number for which the MPLS lable entry is retrieved.
 * @param[out] *mplsLabel  Pointer to an instance of ncp_eioa_mpls_label_t 
 *            that will be filled with MPLS label information. 
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         </ul>
 */

NCP_API ncp_st_t
ncp_eioa_port_egress_mpls_label_get(
    ncp_hdl_t     hdl,
    ncp_macChan_t port,
    ncp_eioa_mpls_label_t *mplsLabel);

/*!
 * @ingroup _eioa_port_
 * @brief  Set options for parsing packet header fields on ingress.
 * @details
 * Ingress packets are parsed for fields to apply to table lookups for VLAN 
 * mapping and packet header field extraction used to supply the ACL, BL, <br>
 * Policer and Statistics blocks with packet information needed for further 
 * processing. Valid for <b>AXX3500</b> and <b>AXX5500</b> devices.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] *options  Pointer to an instance of #ncp_ipp_options_t, 
 *              for values of parsing options. 
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         </ul>
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_parsing_options_set(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_ipp_options_t *options);

/*!
 * @ingroup _eioa_port_
 * @brief  Get options for parsed packer header fields on ingress.
 * @details
 * Ingress packets are parsed for fields to apply to table lookups for VLAN 
 * mapping and packet header field extraction used to supply the ACL, BL, <br>
 * Policer and Statistics blocks with packet information needed for further 
 * processing. Valid for <b>AXX3500</b> and <b>AXX5500</b> devices.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] *options  Pointer to an instance of #ncp_ipp_options_t, 
 *              for values of parsing options. 
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         </ul>
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_parsing_options_get(ncp_hdl_t hdl, ncp_macChan_t port, ncp_ipp_options_t *options);

/*!
 * @ingroup _eioa_port_
 * @brief  Set state for virtual pipeline parsing of fields on ingress.
 * packets.
 * @details
 * Ingress packets are parsed for fields that identify certain packet types.
 *
 * <ul>
 *   <li> <b>enableL2FramerErrorVp</b><br> 
 *        When enabled, use L2 framer error VFOW ID for packets that the 
 *        Ingres Packet Parser recognizes as a framerError or L2 not 
 *        understood. Valid for AXX3500 and AXX5500 families
 *   <li> <b>enableL3FramerErrorVp</b><br> 
 *        When enabled, use L3 framer error VFOW ID for packets that the 
 *        Ingres Packet Parser recognizes as L3 not good. Valid for AXX3500 and
 *         AXX5500 familes
 *   <li> <b>enableL4FramerErrorVp</b><br> 
 *        When enabled, use L4 framer error VFOW ID for packets that the 
 *        Ingres Packet Parser recognizes as L4 not good. Valid for AXX3500 and
 *        AXX5500 families. 
 *   <li> <b>enableOsspVp</b><br> 
 *        When enabled, use OSSP VFOW ID for packets that the Ingres Packet 
 *        Parser recognizes OSSP packets. Valid for AXX3500 and AXX5500 family.
 *   <li> <b>enableMacSecControlledVp</b><br> 
 *        When enabled, use MACsec controlled port VFOW ID for packets that the 
 *        Ingres Packet Parser recognizes as an MACsec controlled port. Valid 
 *        for AXX5500 family. 
 *   <li> <b>enableMacSecUnControlledVp</b><br> 
 *        When enabled, use MACsec not controlled port VFOW ID for packets 
 *        that the Ingres Packet Parser recognizes as an uncontrolled MACsec
 *        port. Valid for AXX5500 family. 
 * </ul>
 * See #ncp_eioa_common_vps_l4framererror_vp_set() <br>
 * See #ncp_eioa_common_vps_l3framererror_vp_set() <br>
 * See #ncp_eioa_common_vps_l2framererror_vp_set() <br>
 * See #ncp_eioa_common_vps_esmc_vp_set() <br>
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] *options  Pointer to an instance of ncp_ipp_vp_options_t,
 *              for values of parsing options.
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         </ul>
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_vp_parsing_options_set(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_ipp_vp_options_t *options);

/*!
 * @ingroup _eioa_port_
 * @brief  Get state of virtual pipeline parsing of fields on ingress. 
 * packets.
 * @details
 *
 * <ul>
 *   <li> <b>enableL2FramerErrorVp</b><br>
 *        When enabled, use L2 framer error VFOW ID for packets that the
 *        Ingres Packet Parser recognizes as a framerError or L2 not
 *        understood. Valid for AXX3500 and AXX5500 families
 *   <li> <b>enableL3FramerErrorVp</b><br>
 *        When enabled, use L3 framer error VFOW ID for packets that the
 *        Ingres Packet Parser recognizes as L3 not good. Valid for AXX3500 and
 *         AXX5500 familes
 *   <li> <b>enableL4FramerErrorVp</b><br>
 *        When enabled, use L4 framer error VFOW ID for packets that the
 *        Ingres Packet Parser recognizes as L4 not good. Valid for AXX3500 and
 *        AXX5500 families.
 *   <li> <b>enableOsspVp</b><br>
 *        When enabled, use OSSP VFOW ID for packets that the Ingres Packet
 *        Parser recognizes OSSP packets. Valid for AXX3500 and AXX5500 family.
 *   <li> <b>enableMacSecControlledVp</b><br>
 *        When enabled, use MACsec controlled port VFOW ID for packets that the
 *        Ingres Packet Parser recognizes as an MACsec controlled port. Valid
 *        for AXX5500 family.
 *   <li> <b>enableMacSecUnControlledVp</b><br>
 *        When enabled, use MACsec not controlled port VFOW ID for packets
 *        that the Ingres Packet Parser recognizes as an uncontrolled MACsec
 *        port. Valid for AXX5500 family.
 * </ul>
 * See #ncp_eioa_common_vps_l4framererror_vp_get() <br>
 * See #ncp_eioa_common_vps_l3framererror_vp_get() <br>
 * See #ncp_eioa_common_vps_l2framererror_vp_get() <br>
 * See #ncp_eioa_common_vps_esmc_vp_get() <br>
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] *options  Pointer to an instance of ncp_ipp_vp_options_t, 
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         </ul>
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_vp_parsing_options_get(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_ipp_vp_options_t *options);

/*!
 * @ingroup _eioa_port_
 * @brief  Get port ingress classification options  
 * @details
 * Get Ingress option values for enable/disable switching, ACL, 
 * Virtual Pipeline Extension and Briding Virtual Pipelines. <br>
 * Get the port default VLAN ID and Customer VLAN ID. 
 * <br> Valid for <b>AXX3500</b> and <b>AXX5500</b> devices.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] *options  Pointer to an instance of #ncp_port_ingress_options_t 
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         </ul>
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_options_get(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_port_ingress_options_t *options);

/*!
 * @ingroup _eioa_port_
 * @brief  Set port ingress classification options  
 * @details
 * Set Ingress options to enable/disable switching, ACL, Virtual Pipeline 
 * Extension and Briding Virtual Pipelines. <br>
 * Set the port default VLAN ID and Customer VLAN ID. 
 * <br> Valid for <b>AXX3500</b> and <b>AXX5500</b> devices.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] *options  Pointer to an instance of #ncp_port_ingress_options_t 
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         </ul>
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_options_set(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_port_ingress_options_t *options);

/*!
 * @ingroup _eioa_port_
 * @brief  Get port egress options  
 * @details
 * Get Egress option values of enable/disable port mirroring and corrupt CRC on
 * QinQ error.  <br>
 * Get outer and inner Vlan Ethertypes.  
 * <br> Valid for <b>AXX3500</b> and <b>AXX5500</b> devices.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] *options  Pointer to an instance of ncp_port_egress_options_t 
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         </ul>
 */
NCP_API ncp_st_t
ncp_eioa_port_egress_options_get(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_port_egress_options_t *options);

/*!
 * @ingroup _eioa_port_
 * @brief  Set port egress options  
 * @details
 * Set Egress options to enable/disable port mirroring and to corrupt CRC on
 * QinQ error.  <br>
 * Set outer and inner Vlan Ethertypes.  
 * <br> Valid for <b>AXX3500</b> and <b>AXX5500</b> devices.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] *options  Pointer to an instance of ncp_port_egress_options_t 
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         </ul>
 */
NCP_API ncp_st_t
ncp_eioa_port_egress_options_set(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_port_egress_options_t *options);

/*!
 * @ingroup _eioa_port_
 * @brief  Set one of the user specified Ethertypes used to identify an 
 *         Outer VLAN tag.
 *         <br> This API is <b>deprecated</b>.
 * #ncp_eioa_port_ingress_outer_vlan_ethertype_set should be used instead.
 *
 * 
 * @param[in] hdl  Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] indx  The index of vlan tag to set. Valid values: 0-2.
 * @param[in] outerVlanTag  An ncp_uint16_t value that contains the VLAN
 *                          tag.
 *
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 */ 
NCP_API ncp_st_t
ncp_eioa_port_ingress_outer_vlan_set(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_uint8_t indx,
    ncp_uint16_t outerVlanTag);

/*!
 * @ingroup _eioa_port_
 * @brief  Set one of the user specified Ethertypes used to identify an
 *         Outer VLAN tag.
 *
 * @param[in] hdl  Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] indx  The index of vlan tag to set. Valid values: 0-2.
 * @param[in] outerVlanTag  An ncp_uint16_t value that contains the VLAN
 *                          tag.
 *
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_outer_vlan_ethertype_set(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_uint8_t indx,
    ncp_uint16_t outerVlanTag);

/*!
 * @ingroup _eioa_port_
 * @brief  Return one of the user specified Ethertypes used to identify an 
 *         Outer VLAN tag.
 *         <br> This API is <b>deprecated</b>.
 * #ncp_eioa_port_ingress_outer_vlan_ethertype_get should be used instead.
 *
 * @param[in] hdl  Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] indx  The index of vlan tag to return. Valid values: 0-2.
 * @param[in] outerVlanTag  Pointer to an ncp_uint16_t that contains the VLAN
 *                          tag.
 *
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_outer_vlan_get(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_uint8_t indx,
    ncp_uint16_t *outerVlanTag);

/*!
 * @ingroup _eioa_port_
 * @brief  Return one of the user specified Ethertypes used to identify an
 *         Outer VLAN tag.
 *
 * @param[in] hdl  Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] indx  The index of vlan tag to return. Valid values: 0-2.
 * @param[in] outerVlanTag  Pointer to an ncp_uint16_t that contains the VLAN
 *                          tag.
 *
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_outer_vlan_ethertype_get(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_uint8_t indx,
    ncp_uint16_t *outerVlanTag);

/*!
 * @ingroup _eioa_port_
 * @brief  Remove one of the user specified Ethertypes that is used to identify 
 *         an Outer VLAN tag.
 *         <br> This API is <b>deprecated</b>.
 * #ncp_eioa_port_ingress_outer_vlan_ethertype_rem should be used instead.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] indx  The index of vlan tag to remove. Valid values: 0-2. 
 *
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 * 
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_outer_vlan_rem(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_uint8_t indx);

/*!
 * @ingroup _eioa_port_
 * @brief  Remove one of the user specified Ethertypes that is used to identify
 *         an Outer VLAN tag.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] indx  The index of vlan tag to remove. Valid values: 0-2.
 *
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_outer_vlan_ethertype_rem(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_uint8_t indx);

/*!
 * @ingroup _eioa_port_
 * @brief  Set one of the user specified Ethertypes used to identify an 
 *         Inner VLAN tag.
 *         <br> This API is <b>deprecated</b>.
 * #ncp_eioa_port_ingress_inner_vlan_ethertype_set should be used instead.
 * 
 * @param[in] hdl  Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] indx  The index of vlan tag to set. Valid values: 0-2.
 * @param[in] innerVlanTag  An ncp_uint16_t value that contains the VLAN
 *                          tag.
 *
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 */ 
NCP_API ncp_st_t
ncp_eioa_port_ingress_inner_vlan_set(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_uint8_t indx,
    ncp_uint16_t innerVlanTag);

/*!
 * @ingroup _eioa_port_
 * @brief  Set one of the user specified Ethertypes used to identify an
 *         Inner VLAN tag.
 *
 * @param[in] hdl  Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] indx  The index of vlan tag to set. Valid values: 0-2.
 * @param[in] innerVlanTag  An ncp_uint16_t value that contains the VLAN
 *                          tag.
 *
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_inner_vlan_ethertype_set(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_uint8_t indx,
    ncp_uint16_t innerVlanTag);

/*!
 * @ingroup _eioa_port_
 * @brief  Return one of the user specified Ethertypes used to identify an 
 *         Outer VLAN tag.
 *         <br> This API is <b>deprecated</b>.
 * #ncp_eioa_port_ingress_inner_vlan_ethertype_get should be used instead.
 *
 * @param[in] hdl  Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] indx  The index of vlan tag to return. Valid values: 0-2.
 * @param[in] innerVlanTag  Pointer to an ncp_uint16_t that contains the VLAN
 *                          tag.
 *
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_inner_vlan_get(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_uint8_t indx,
    ncp_uint16_t *innerVlanTag);

/*!
 * @ingroup _eioa_port_
 * @brief  Return one of the user specified Ethertypes used to identify an
 *         Outer VLAN tag.
 *
 * @param[in] hdl  Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] indx  The index of vlan tag to return. Valid values: 0-2.
 * @param[in] innerVlanTag  Pointer to an ncp_uint16_t that contains the VLAN
 *                          tag.
 *
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_inner_vlan_ethertype_get(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_uint8_t indx,
    ncp_uint16_t *innerVlanTag);

/*!
 * @ingroup _eioa_port_
 * @brief  Remove one of the user specified Ethertypes used to identify 
 *         an Inner VLAN tag.
 *         <br> This API is <b>deprecated</b>.
 * #ncp_eioa_port_ingress_inner_vlan_ethertype_rem should be used instead.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] indx  The index of vlan tag to remove. Valid values: 0-2. 
 *
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 * 
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_inner_vlan_rem(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_uint8_t indx);

/*!
 * @ingroup _eioa_port_
 * @brief  Remove one of the user specified Ethertypes used to identify
 *         an Inner VLAN tag.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] indx  The index of vlan tag to remove. Valid values: 0-2.
 *
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_inner_vlan_ethertype_rem(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_uint8_t indx);

/*!
 * @ingroup _eioa_port_
 * @brief Set the state of the egress port scheduler. 
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] *options  Void pointer to an instance of 
 * ncp_port_scheduler_options_t 
 *
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *     \li ::NCP_ST_EIOA_PORT_SCHEDULER_INVALID_VALUE
 *
 */
NCP_API ncp_st_t
ncp_eioa_port_scheduler_set(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_port_scheduler_options_t *options);

/*!
 * @ingroup _eioa_port_
 * @brief Get the state of the egress port shaper. 
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] *options  Void pointer to an instance of 
 * ncp_port_scheduler_options_t
 *
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *
 */
NCP_API ncp_st_t
ncp_eioa_port_scheduler_get(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_port_scheduler_options_t *options);

/*!
 * @ingroup _eioa_port_
 * @brief Set the state of the egress port shaper. 
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] *options  Pointer to an instance of ncp_port_shaper_options_t
 *
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *     \li ::NCP_ST_EIOA_PORT_SHAPER_INVALID_VALUE
 *
 */
NCP_API ncp_st_t
ncp_eioa_port_shaper_set(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_port_shaper_options_t *options);

/*!
 * @ingroup _eioa_port_
 * @brief Get the state of the egress port shaper. 
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] *options  Pointer to an instance of ncp_port_shaper_options_t
 *
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_BUFFER
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *
 */
NCP_API ncp_st_t
ncp_eioa_port_shaper_get(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_port_shaper_options_t *options);

/*!
 * @ingroup _eioa_port_
 * @brief  Disable egress port shaper.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 *
 * @return
 *     \li ::NCP_ST_SUCCESS
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *     \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *     \li ::NCP_ST_MAC_INVALID_MAC
 *     \li ::NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *
 */
NCP_API ncp_st_t
ncp_eioa_port_shaper_delete(
    ncp_hdl_t hdl,
    ncp_macChan_t macChan);

/*!
 * @ingroup _eioa_port_
 * @brief  Compute trivial hash on tag metadata normal sent with ingress
 * packets.
 * @details
 * Compute  the hash value of the "tag" metadata that is normally sent along
 * with ingress packets on the EIOA.  <br>
 * <b>start_offset</b> - <b>stop_offset</b> values or used to determine which
 * part of the first 64 byte packet to compute the hash on. <br>
 * Also see #ncp_eioa_tag_config_get() for the hardware generated equivalent
 * for this software hash function.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] *data  Pointer to a 64 byte array of packet data.
 * @param[in] startOff Value of the starting offset to compute the hash
 * @param[in] stopOff Value of the ending offset to compute the hash
 * @param[out] *hash_result  Pointer to an instance of ncp_uint32_t, to place
 *              value of the hash result.
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_EIOA_INVALID_TAG
 *         </ul>
 */
NCP_API ncp_st_t 
ncp_eioa_hash_value_get(
    ncp_hdl_t    hdl,
    ncp_uint8_t  *data,
    ncp_uint32_t startOff,
    ncp_uint32_t stopOff,
    ncp_uint32_t *hash_result,
    ncp_uint32_t flags);

/*!
 * @ingroup _eioa_port_
 * @brief Get PCX Counters Clear on Read Mode
 * packets.
 * @details
 * This API provides a way to get the clear on read register content for PCX counters
 * Returned Values:
 *   - TRUE  - Clear on read is enabled
 *   - FALSE - Clear on read is disabled
 *
 * <br> Valid for <b>AXX5500</b> devices only.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[out] *enable_clr_on_read  a pointer an instance of ncp_bool_t
 *            When set to TRUE, Couner clear on read is enabled.
 *            When set to FALSE, Couner clear on read is disabled.
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         </ul>
 */

NCP_API ncp_st_t
ncp_eioa_port_counter_reg_mode_get(
    ncp_hdl_t hdl,
    ncp_macChan_t port,
    ncp_bool_t    *enable_clr_on_read);

/*!
 * @ingroup _eioa_port_
 * @brief Enable PCX Counters Clear on Read
 * packets.
 * @details
 * This API provides a way to set the clear on read register for PCX counters
 * All counters that are provided by callin ncp_eioa_port_counter_reg_get will
 * be clear if this API is called to set the clear bit except for the following
 * counters:
 *   - global_unlearn_hash_ctr 
 *   - mcast_pkt_ctr 
 *   - tids_in_use_ctr  
 *   - unlrn_hash_cntr memory tables
 * <br> Valid for <b>AXX5500</b> devices only.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] enable_clr_on_read  an instance of ncp_bool_t
 *            When set to TRUE, counters will clear on read
 *            When set to FALSE, this option is disabled. 
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         </ul>
 */

NCP_API ncp_st_t
ncp_eioa_port_counter_reg_mode_set(
    ncp_hdl_t hdl,
    ncp_macChan_t port,
    ncp_bool_t    enable_clr_on_read);

/*!
 * @ingroup _eioa_port_
 * @brief Provide EIOA PCX Error Counters
 * packets.
 * @details
 * This API provides Statistics and Monitoring counters for PCX.
 * There are 3 separate secions of counters the are provided here:
 *    1. port counters
 *    2. parser discard counters
 *    3. other counters such as MACSec rx and tx control and multicast forward drop counters
 * <br> Valid for <b>AXX5500</b> devices only.
 * Also see #ncp_eioa_port_counter_reg_mode_set and #ncp_eioa_port_counter_reg_mode_get
 * All counters that are provided will be cleared by callin ncp_eioa_port_counter_reg_get
 * except for the following counters:
 *   - global_unlearn_hash_ctr 
 *   - mcast_pkt_ctr 
 *   - tids_in_use_ctr  
 *   - unlrn_hash_cntr memory tables
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[out] *port_counter  Pointer to an instance of ncp_port_counters_t, to place
 *              port counter results.
 * @param[out] *parser_counter  Pointer to an instance of ncp_parser_discard_counters_t, to place
 *              parser discard counter results.
 * @param[out] *misc_counter  Pointer to an instance of ncp_misc_counters_t, to place
 *              the rest of port counter results.
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         </ul>
 */

NCP_API ncp_st_t
ncp_eioa_port_counter_reg_get(
    ncp_hdl_t hdl,
    ncp_macChan_t port,
    ncp_port_counters_t *port_counter,
    ncp_parser_discard_counters_t *parser_counter,
    ncp_misc_counters_t *misc_counter);

/*!
 * @ingroup _eioa_port_
 * @brief Dynamically switch between port speeds of 10G bps and 1G bps.
 * @details
 * Switch port speeds at runtime.  
 * The limitations for this API are:
 * <ul>
 * <li> Must have a channel type of SGMII for 1G bps
 * <li> Must have a channel type of SFI for 10G bps
 * <li> Must be Fiber for 1G bps link. 10G bps fiber is expected.
 * <li> 10G Links are forced speed, and Autonegotiation is disabled
 * <li> 1G Link speed may be forced, or Autonegotiation can be enabled.d
 * <li> On <b>AXX55xx</b> platforms - For EIOA0 ports, only X/GMAC0 and <br>
 * X/GMAC1 can be configured. For EIOA1 ports, only X/GMAC16 and X/GMAC17<br>
 * can be configured.
 * <li>All ports on the extended domain are supported. For EIOA2, X/GMAC32 and X/GMAC33. For EIOA3, X/GMAC48 and X/GMAC49. For EIOA4, X/GMAC64 and X/GMAC65. For EIOA5, X/GMAC80 and X/GMAC81. For EIOA6, X/GMAC96 and X/GMAC97. For EIOA7, X/GMAC112 and X/GMAC113.
 * <li>If the API fails, the original port configuration should remain intact. 
 * This means that the port should continue to opperate at original settings.
 * <li>For port switchover to function correctly, the port must have originally
 * been configured in the ASE for 10G or 1G speeds. This API does not 
 * <b>create</b> a new configuration, it can only modify an existing one.
 * <li>Any other API run against the port during a switchover should return #NCP_ST_EIOA_PORT_NOT_CONFIGURED.
 * <li>All GMAC ports must have been originally configured with the <b>isFiber</b> set. This is implied for all XGMAC ports.
 * </ul>
 * <br>Valid for <b>AXX55xx</b> devices.
 * 
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan  EIOA port number specific to an EIOA.
 * @param[in] *switchover_config  Pointer to an instance of 
 *            #ncp_eioa_port_config_switchover_t, for values of port switchover
 *            options. 
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER     
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_MAC_INVALID_SPEED
 *         <li> #NCP_ST_MAC_INVALID_DUPLEX
 *         <li> #NCP_ST_EIOA_PORT_SWITCHOVER_COMBINATION_NOT_SUPPORTED
 *         <li> #NCP_ST_EIOA_PORT_SWITCHOVER_NOT_FIBER
 *         <li> #NCP_ST_EIOA_PORT_SWITCHOVER_BAD_PARAMETERS
 *         </ul>
 */

NCP_API ncp_st_t
ncp_eioa_port_config_switchover(ncp_hdl_t hdl,
    ncp_macChan_t macChan,
    ncp_eioa_port_config_switchover_t *switchover_config);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _NCP_EIOA_CORE_H_ */
