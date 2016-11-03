/**************************************************************************
 **                                                                       *
 **                           Intel CONFIDENTIAL                            *
 **                           PROPRIETARY NOTE                            *
 **                                                                       *
 **    This software contains information confidential and proprietary    *
 **    to Intel Corporation.  It shall not be reproduced in whole or in     *
 **    part, or transferred to other documents, or disclosed to third     *
 **    parties, or used for any purpose other than that for which it was  *
 **    obtained, without the prior written consent of Intel Corporation.    *
 **    (c) 2008-2014, Intel Corporation.  All rights reserved.  *
 **                                                                       *
 **
 **   File:       $URL$
 **  
 **************************************************************************/

/*! @file  ncp_eioa_switch_acl.h                                          */
/*!
 * @defgroup _eioa_switch_acl_ EIOA Switch ACL
 * @ingroup _eioa_switch_
 * @brief EIOA Switch ACL APIs.
 * @details EIOA Switch ACL APIs are used to
 * - modify ACL selection based on Port, VLAN Id or Port and VLAN Id combination
 * - add/delete/modify ACL rules 
 * - modify ACL based Policer selection
 * - modify DSCP selection based on COS, IP Precedence or packet DSCP
 * - modify Routing Table
 */
#ifndef _NCP_EIOA_SWITCH_ACL_H_
#define _NCP_EIOA_SWITCH_ACL_H_

#include "ncp.h"
#include "ncp_eioa.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @ingroup _eioa_switch_acl_
 * @struct ncp_eioa_switch_acl_mac_addr_t
 * @brief EIOA Switch ACL MAC address declaration
 */
typedef struct ncp_eioa_switch_acl_mac_addr_s
{
    ncp_uint8_t value[6];
} ncp_eioa_switch_acl_mac_addr_t;
/*!
 * @ingroup _eioa_switch_acl_
 * @struct ncp_eioa_switch_acl_mac_addr_mask_t
 * @brief EIOA Switch ACL MAC address mask declaration
 */
typedef struct ncp_eioa_switch_acl_mac_addr_mask_s
{
    ncp_uint8_t value[6];
} ncp_eioa_switch_acl_mac_addr_mask_t;
/*!
 * @ingroup _eioa_switch_acl_
 * @struct ncp_eioa_switch_acl_ip_addr_t
 * @brief EIOA Switch ACL IP address declaration
 */
typedef struct ncp_eioa_switch_acl_ip_addr_s
{
    ncp_uint8_t value[16];
} ncp_eioa_switch_acl_ip_addr_t;
/*!
 * @ingroup _eioa_switch_acl_
 * @typedef ncp_eioa_switch_acl_layer4_port_t
 * @brief EIOA Switch ACL Layer 4 port declaration
 */
typedef ncp_uint16_t ncp_eioa_switch_acl_layer4_port_t; 
/*!
 * @ingroup _eioa_switch_acl_
 * @struct ncp_eioa_switch_acl_dscp_t
 * @brief EIOA Switch ACL DSCP declaration. \c prefixLength field can have two
 * values: 0 or 6. A \c prefixLength of 0 (zero) is used when adding an ACL
 * rule and specifies a \c ANY DSCP value.
 */
typedef struct ncp_eioa_switch_acl_dscp_s
{
    ncp_uint8_t prefixLength;
    ncp_uint8_t value;
} ncp_eioa_switch_acl_dscp_t;

/*! 
 * @ingroup _eioa_switch_acl_
 * @typedef ncp_eioa_switch_acl_ip_precedence_t
 * @brief EIOA Switch ACL IP Precedence declaration
 */
typedef ncp_uint8_t ncp_eioa_switch_acl_ip_precedence_t;
/*!
 * @ingroup _eioa_switch_acl_
 * @struct ncp_eioa_switch_acl_cos_t
 * @brief EIOA Switch ACL COS declaration. \c prefixLength field can have two
 * values: 0 or 3. A \c prefixLength of 0 (zero) is used when adding an ACL
 * rule and specifies a \c ANY COS value.
 */
typedef struct ncp_eioa_switch_acl_cos_s
{
    ncp_uint8_t prefixLength;
    ncp_uint8_t value;
} ncp_eioa_switch_acl_cos_t;

/*!
 * @ingroup _eioa_switch_acl_
 * @struct ncp_eioa_switch_acl_vlan_id_t
 * @brief EIOA Switch ACL VLAN id declaration
 */
typedef struct ncp_eioa_switch_acl_vlan_id_s
{ 
    /*!
     * @brief Number of bits to consider in value 
     * \c prefixLength can have two values: 0 or 12. A \c prefixLength
     * of 0 ignores the \c value field whereas \c
     * prefixLength of 12 considers the \c value field in its
     * entirety.
     * @see ncp_eioa_switch_acl_vlan_id_t::value
     */
    ncp_uint8_t prefixLength;
    ncp_uint16_t value;
} ncp_eioa_switch_acl_vlan_id_t;

/*!
 * @ingroup _eioa_switch_acl_
 * @enum ncp_eioa_switch_acl_ethertype_t
 * @brief Types of Ethertype in EIOA Switch ACL
 */
typedef enum ncp_eioa_switch_acl_ethertype_e
{
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_IPv4             = 0,      /*!< Ethertype index for IPv4 */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_IPv4_FRAGMENT    = 1,      /*!< Ethertype index for IPv4 Fragment */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_IPv6             = 2,      /*!< Ethertype index for IPv6 */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_ARP_25xx              = 3, /*!< Ethertype index for ARP. This is relevant only for ACP25xx */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_RARP_25xx             = 4, /*!< Ethertype index for RARP. This is relevant only for ACP25xx */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_MPLS             = 5,      /*!< Ethertype index for MPLS */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_OAM_CFM_25xx          = 6, /*!< Ethertype index for OAM. This is relevant only for ACP25xx */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_USER_DEFINED_0   = 7,      /*!< Ethertype index for user defined etherype 0 */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_USER_DEFINED_1   = 8,      /*!< Ethertype index for user defined etherype 1 */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_USER_DEFINED_2   = 9,      /*!< Ethertype index for user defined etherype 2 */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_USER_DEFINED_3   = 10,      /*!< Ethertype index for user defined etherype 3 */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_USER_DEFINED_4   = 11,      /*!< Ethertype index for user defined etherype 4 */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_USER_DEFINED_5   = 12,      /*!< Ethertype index for user defined etherype 5 */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_USER_DEFINED_6   = 13,     /*!< Ethertype index for user defined etherype 6 */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_USER_DEFINED_7   = 14,     /*!< Ethertype index for user defined etherype 7 */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_USER_DEFINED_8   = 3,     /*!< Ethertype index for user defined etherype 8 */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_USER_DEFINED_9   = 4,     /*!< Ethertype index for user defined etherype 9 */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_USER_DEFINED_10  = 6,     /*!< Ethertype index for user defined etherype 10 */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_USER_DEFINED_0_25xx   = 7, /*!< Ethertype index for user defined etherype 0 for ACP25xx */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_USER_DEFINED_1_25xx   = 8, /*!< Ethertype index for user defined etherype 1 for ACP25xx */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_USER_DEFINED_2_25xx   = 9, /*!< Ethertype index for user defined etherype 2 for ACP25xx */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_USER_DEFINED_3_25xx   = 10, /*!< Ethertype index for user defined etherype 3 for ACP25xx */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_USER_DEFINED_4_25xx   = 11, /*!< Ethertype index for user defined etherype 4 for ACP25xx */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_USER_DEFINED_5_25xx   = 12, /*!< Ethertype index for user defined etherype 5 for ACP25xx */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_USER_DEFINED_6_25xx   = 13, /*!< Ethertype index for user defined etherype 6 for ACP25xx */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_USER_DEFINED_7_25xx   = 14, /*!< Ethertype index for user defined etherype 7 for ACP25xx */
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_UNKNOWN          = 15,     /*!< Ethertype index for unknown etherype */ 
    NCP_EIOA_SWITCH_ACL_ETHERTYPE_ANY              = 16      /*!< Ethertype index for any ethertype. Use this ethertype index to match any ethertype */
} ncp_eioa_switch_acl_ethertype_t;

/*!
 * @ingroup _eioa_switch_acl_
 * @enum ncp_eioa_switch_acl_ip_protocol_t
 * @brief Types of IP Protocol in EIOA Switch ACL
 */
typedef enum ncp_eioa_switch_acl_ip_protocol_e
{
    NCP_EIOA_SWITCH_ACL_IP_PROTOCOL_ICMP,                /*!< IP protocol index for ICMP */
    NCP_EIOA_SWITCH_ACL_IP_PROTOCOL_IGMP,                /*!< IP protocol index for IGMP */
    NCP_EIOA_SWITCH_ACL_IP_PROTOCOL_TCP,                 /*!< IP protocol index for TCP */
    NCP_EIOA_SWITCH_ACL_IP_PROTOCOL_UDP,                 /*!< IP protocol index for UDP */
    NCP_EIOA_SWITCH_ACL_IP_PROTOCOL_USER_DEFINED_0,      /*!< IP protocol index for user defined protocol index 0 */
    NCP_EIOA_SWITCH_ACL_IP_PROTOCOL_USER_DEFINED_1,      /*!< IP protocol index for user defined protocol index 1 */
    NCP_EIOA_SWITCH_ACL_IP_PROTOCOL_USER_DEFINED_2,      /*!< IP protocol index for user defined protocol index 2 */
    NCP_EIOA_SWITCH_ACL_IP_PROTOCOL_USER_DEFINED_3,      /*!< IP protocol index for user defined protocol index 3 */
    NCP_EIOA_SWITCH_ACL_IP_PROTOCOL_USER_DEFINED_4,      /*!< IP protocol index for user defined protocol index 4 */
    NCP_EIOA_SWITCH_ACL_IP_PROTOCOL_USER_DEFINED_5,      /*!< IP protocol index for user defined protocol index 5 */
    NCP_EIOA_SWITCH_ACL_IP_PROTOCOL_USER_DEFINED_6,      /*!< IP protocol index for user defined protocol index 6 */
    NCP_EIOA_SWITCH_ACL_IP_PROTOCOL_USER_DEFINED_7,      /*!< IP protocol index for user defined protocol index 7 */
    NCP_EIOA_SWITCH_ACL_IP_PROTOCOL_USER_DEFINED_8,      /*!< IP protocol index for user defined protocol index 8 */
    NCP_EIOA_SWITCH_ACL_IP_PROTOCOL_USER_DEFINED_9,      /*!< IP protocol index for user defined protocol index 9 */
    NCP_EIOA_SWITCH_ACL_IP_PROTOCOL_USER_DEFINED_10,     /*!< IP protocol index for user defined protocol index 10 */
    NCP_EIOA_SWITCH_ACL_IP_PROTOCOL_UNKNOWN,             /*!< IP protocol index for unknown IP protocol */
    NCP_EIOA_SWITCH_ACL_IP_PROTOCOL_ANY                  /*!< IP protocol index for any IP protocol. Use this IP protocol index to match any IP protocol */
} ncp_eioa_switch_acl_ip_protocol_t;

/*!
 * @ingroup _eioa_switch_acl_
 * @struct ncp_eioa_switch_acl_mac_addresses_t
 * @brief EIOA Switch ACL MAC addresses declaration
 * @details A collection of MAC addresses is specified using a combination of \c address and 
 * \c mask. To specify a single MAC address use \c address to hold the address value and set 
 * \c mask to \c 0xffffffffffff. To ignore certain bits in the address specify a MAC address in 
 * \c address, and set the bits to ignore to 0 in the \c mask . For example, to specify 
 * \c 0b0001000x1110x0000xxxxx001101101x0000000000000000, where \c x is ignore, set address to 
 * \c 0b000100001110000000000000110110100000000000000000 and mask to 
 * \c 0b111111101111011110000011111111101111111111111111. To specify all MAC addresses set \c mask to 0.
 */
typedef struct ncp_eioa_switch_acl_mac_addresses_s
{
    ncp_eioa_switch_acl_mac_addr_t	    address;
    ncp_eioa_switch_acl_mac_addr_mask_t mask;
} ncp_eioa_switch_acl_mac_addresses_t;

/*! 
 * @ingroup _eioa_switch_acl_
 * @struct ncp_eioa_switch_acl_ip_subnet_t
 * @brief EIOA Switch ACL IP subnet declaration
 * @details An IP subnet is specified using a combination of \c address and \c prefixLength in 
 * <a href="http://en.wikipedia.org/wiki/CIDR_notation"> CIDR </a> notation.
 * For IPv4 addresses \c address is right justified and \c prefixLength should be between 0 and 32.
 * For example to specify 10.10.*.* set \c address to 
 * <tt> { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 0, 0 } </tt> and set \c prefixLength to 16.
 * For IPv6 addresses \c prefixLength should be between 0 and 128. A \c prefixLength of 0 covers the
 * entire IP address space.
 */
typedef struct ncp_eioa_switch_acl_ip_subnet_s
{
    ncp_eioa_switch_acl_ip_addr_t   address;
    ncp_uint32_t		    prefixLength;
} ncp_eioa_switch_acl_ip_subnet_t;

/*!
 * @ingroup _eioa_switch_acl_
 * @struct ncp_eioa_switch_acl_layer4_port_range_t
 * @brief EIOA Switch ACL Layer 4 port range declaration
 * @details A range of layer 4 ports is specified using \c low and \c high. The range includes both 
 * \c high and \c low. 
 */
typedef struct ncp_eioa_switch_acl_layer4_port_range_s
{
    ncp_eioa_switch_acl_layer4_port_t high;
    ncp_eioa_switch_acl_layer4_port_t low;
} ncp_eioa_switch_acl_layer4_port_range_t;

/*!
 * @ingroup _eioa_switch_acl_
 * @enum ncp_eioa_switch_acl_ip_address_mode_t
 * @brief EIOA Switch ACL IP mode operation
 * @details EIOA Switch ACL can operate in either IPv4 only mode or in IPv4 and IPv6 mode. In IPv4 and IPv6 mode all IP 
 * addresses are stored as IPv6 addresses
 */
typedef enum ncp_eioa_switch_acl_ip_address_mode_e
{
    NCP_EIOA_SWITCH_ACL_IPv4_ADDRESS_MODE, /*!< Only IPv4 addresses are stored in ACL */
    NCP_EIOA_SWITCH_ACL_IPv4_AND_IPv6_ADDRESS_MODE /*!< Both IPv4 and IPv6 addresses are stored in ACL as IPv6 addresses */
} ncp_eioa_switch_acl_ip_address_mode_t;

/*!
 * @ingroup _eioa_switch_acl_
 * @enum ncp_eioa_switch_acl_trust_mode_t
 * @brief EIOA Switch ACL IP trust mode declaration
 * @details Trust mode is used specifies the source for task priority for IP
 * packets.
 */
typedef enum ncp_eioa_switch_acl_trust_mode_e
{
    NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED, /*!< Defer to input port's trust mode, if input port's trust mode is also NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED then either use the dscpValue specified in default action or the dscpValue in the ACL rule that matched the packet*/           
    NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_COS,   /*!< Use COS to map to a task priority*/        
    NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_DSCP,   /*!< Use DSCP to map to a task priority*/      
    NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_IP_PRECEDENCE /*!< Use IP precedence value to map to a task priority*/ 
} ncp_eioa_switch_acl_trust_mode_t;

/*!
 * @ingroup _eioa_switch_acl_
 * @enum ncp_eioa_switch_acl_is_mac_sec_t
 * @brief AXM5500 EIOA Switch ACL encrypted mode declaration
 * @details Specifies whether to classify encrypted packets
 */
typedef enum ncp_eioa_switch_acl_encryption_mode_e
{
	NCP_EIOA_SWITCH_ACL_ENCRYPTION_MODE_NOT_ENCRYPTED, /*!< Classify unencrypted packets only */
	NCP_EIOA_SWITCH_ACL_ENCRYPTION_MODE_ENCRYPTED, /*!< Classify encrypted packets only */
	NCP_EIOA_SWITCH_ACL_ENCRYPTION_MODE_ANY /*!< Classify both encrypted and unencrypted packets */
} ncp_eioa_switch_acl_encryption_mode_t;

/*!
 * @ingroup _eioa_switch_acl_
 * @struct ncp_eioa_switch_acl_domain_id_t
 * @brief EIOA Switch ACL domain id declaration
 */
typedef struct ncp_eioa_switch_acl_domain_id_s
{
    /*!
     * @brief Number of bits to consider in value
     * \c prefixLength can have two values: 0 or 9. A \c prefixLength
     * of 0 ignores the \c value field whereas \c
     * prefixLength of 9 considers the \c value field in its
     * entirety.
     * @see ncp_eioa_switch_acl_domain_id_t::value
     */
    ncp_uint8_t prefixLength;
    /*!
     * @brief Value of this domain
     * @details Depending upon the value of \c prefixLength either is value is ignored or the entire
     * value of this field is used
     * @see ncp_eioa_switch_acl_domain_id_t::prefixLength
     */
    ncp_uint16_t value;
} ncp_eioa_switch_acl_domain_id_t;
/*!
 * @ingroup _eioa_switch_acl_
 * @struct ncp_eioa_switch_acl_action_t
 * @brief EIOA Switch ACL rule action declaration
 * @details Defines the action to be performed if a ACL rule matches. A match occurs if all the fields in a rule are 
 * either equal to or subsumes the value in the packet. 
 */
typedef struct ncp_eioa_switch_acl_action_s
{
    /*!
     * @brief Permits packet 
     * As opposed to permit, denying a packet might result in the dropping the packet in EIOA Core
     * @see ncp_eioa_switch_bridge_acl_deny_vps_get
     */
    ncp_bool_t                              permit; 
    /*! 
     * @brief Log packet
     * Send the packet to a logging virtual pipeline too
     * @see ncp_eioa_switch_bridge_acl_log_vps_get
     */
    ncp_bool_t                              enableLogging;
    /*! 
     * @brief Whether to change the VLAN id used for further processing
     * @see ncp_eioa_egress_modification_options_get
     * @see ncp_eioa_switch_acl_action_t::newVlanId
     */
    ncp_bool_t                              changeVlanId;
    /*!
     * @brief New value of VLAN Id to be used for further processing
     * @details If 
     * \ref ncp_eioa_switch_acl_action_t::changeVlanId is
     * \c TRUE then use this VLAN id to populate the VLAN id field in task
     * parameters
     */
    ncp_eioa_switch_acl_vlan_id_t           newVlanId;
    /*!
     * @brief Enables policing 
     * @see ncp_eioa_switch_acl_action_t::policerId
     */
    ncp_bool_t                              enablePolicing;
    /*!
     * @brief Policer Id to use
     * If \ref ncp_eioa_switch_acl_action_t::enablePolicing
     * is set to true then use this policer id to select the policer
     */
    ncp_uint16_t                            policerId;
    /*!
     * @brief Enable mirroring
     * @see ncp_eioa_switch_acl_action_t::mirrorBridgeVpId
     */
    ncp_bool_t                              enableMirroring;
    /*!
     * @brief Mirror virtual pipeline
     * @details If 
     * \ref ncp_eioa_switch_acl_action_t::enableMirroring "enableMirroring"
     * is set then send the packet on this virtual pipeline too
     * @see ncp_eioa_ingress_acl_mirror_port_get
     */
    ncp_uint8_t                             mirrorBridgeVpId;
    /*!
     * @brief Define trust mode for this rule 
     * @details \ref ncp_eioa_switch_acl_trust_mode_t "trustMode" 
     * specifies the source for setting the task priority
     * If #NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_COS is specified then use 
     * COS DSCP map to assign task 
     * priority. If #NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_IP_PRECEDENCE is 
     * specified then use IP Precedence
     * DSCP map to assign task priority. If 
     * #NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_DSCP
     * is specified then use DSCP DSCP map to assign task priority
     * If #NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED is specified then use 
     * input port's trust mode. 
     * If input port's trust mode is also set to 
     * #NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED then use 
     * \ref ncp_eioa_switch_acl_action_t::dscpValue value to 
     * decide the task priority
     * @see ncp_eioa_switch_acl_action_t::dscpValue
     * @see ncp_eioa_switch_acl_cos_to_dscp_map_get
     */
    ncp_eioa_switch_acl_trust_mode_t        trustMode;
    /*!
     * @brief DSCP value to use if 
     * \ref ncp_eioa_switch_acl_action_t::trustMode 
     * is set to #NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED as well as input port's trust mode is also set
     * to #NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED
     * @see ncp_eioa_switch_acl_action_t::trustMode
     */
    ncp_eioa_switch_acl_dscp_t              dscpValue;
} ncp_eioa_switch_acl_action_t;

/*!
 * @ingroup _eioa_switch_acl_
 * @struct ncp_eioa_switch_acl_default_action_t
 * @brief EIOA Switch ACL default action declaration
 * @details Defines the action to be performed if none of the ACL rule matches. A match occurs if all the fields in a rule are 
 * either equal to or subsumes the value in the packet. This action is shared across all ACLs. 
 */
typedef struct ncp_eioa_switch_acl_default_action_s
{
    /*! 
     * @brief Log unmatched packet
     * Send the packet to a logging virtual pipeline too
     * @see ncp_eioa_switch_bridge_acl_log_vps_get
     */
    ncp_bool_t                              enableLogging;
    /*!
     * @brief Enables policing for unmatched IP packets 
     * @see ncp_eioa_switch_acl_action_t::policerId
     */
    ncp_bool_t                              enableIpPolicing;
    /*!
     * @brief Policer Id to use for unmatched IP packets
     * If \ref ncp_eioa_switch_acl_default_action_t::enableIpPolicing
     * is set to true then use this policer id to select the policer
     */
    ncp_uint16_t                            ipPolicerId;
    /*!
     * @brief Define trust mode for unmatched IP packets
     * @details \ref ncp_eioa_switch_acl_trust_mode_t "trustMode" 
     * specifies the source for setting the task priority
     * If #NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_COS is specified then use 
     * COS DSCP map to assign task 
     * priority. If #NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_IP_PRECEDENCE is 
     * specified then use IP Precedence
     * DSCP map to assign task priority. If 
     * #NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_DSCP
     * is specified then use DSCP DSCP map to assign task priority
     * If #NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED is specified then use 
     * input port's trust mode. 
     * If input port's trust mode is also set to 
     * #NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED then use 
     * \ref ncp_eioa_switch_acl_default_action_t::ipDscpValue value to 
     * decide the task priority
     * @see ncp_eioa_switch_acl_default_action_t::ipDscpValue
     * @see ncp_eioa_switch_acl_cos_to_dscp_map_get
     * @see ncp_eioa_switch_acl_ip_precedence_to_dscp_map_get
     * @see ncp_eioa_switch_acl_dscp_to_dscp_map_get
     */
    ncp_eioa_switch_acl_trust_mode_t     ipTrustMode;
    /*!
     * @brief DSCP value to use for unmatched IP packets if 
     * \ref ncp_eioa_switch_acl_default_action_t::ipTrustMode
     * is set to #NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED as well as input port's trust mode is also set
     * to #NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED
     * @see ncp_eioa_switch_acl_default_action_t::ipTrustMode
     */
    ncp_eioa_switch_acl_dscp_t              ipDscpValue;
    /*!
     * @brief Enables policing for unmatched non IP packets 
     * @see ncp_eioa_switch_acl_action_t::policerId
     */
    ncp_bool_t                              enableNonIpPolicing;
    /*!
     * @brief Policer Id to use for unmatched non IP packets
     * If \ref ncp_eioa_switch_acl_default_action_t::enableNonIpPolicing
     * is set to true then use this policer id to select the policer
     */
    ncp_uint16_t                            nonIpPolicerId;
    /*!
     * @brief Define trust mode for unmatched non IP packets
     * @details \ref ncp_eioa_switch_acl_trust_mode_t
     * specifies the source for setting the task priority
     * If #NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_COS is specified then use 
     * COS DSCP map to assign task priority.
     * If #NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED is specified then use 
     * input port's trust mode. 
     * If input port's trust mode is also set to 
     * #NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED then use 
     * \ref ncp_eioa_switch_acl_default_action_t::nonIpDscpValue value to 
     * decide the task priority.
     * #NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED and
     * #NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_COS are the only applicable values
     * for this field.
     * @see ncp_eioa_switch_acl_default_action_t::nonIpDscpValue
     * @see ncp_eioa_switch_acl_cos_to_dscp_map_get
     */
    ncp_eioa_switch_acl_trust_mode_t nonIpTrustMode;
    /*!
     * @brief DSCP value to use for unmatched non IP packets if 
     * \ref ncp_eioa_switch_acl_default_action_t::nonIpTrustMode
     * is set to #NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED as well as input port's trust mode is also set
     * to #NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED
     * @see ncp_eioa_switch_acl_default_action_t::nonIpTrustMode
     */
    ncp_eioa_switch_acl_dscp_t              nonIpDscpValue;
    /*!
     * @brief Enable mirroring
     * @see ncp_eioa_switch_acl_default_action_t::mirrorBridgeVpId
     */
    ncp_bool_t                              enableMirroring;
    /*!
     * @brief Mirror virtual pipeline
     * @details If 
     * \ref ncp_eioa_switch_acl_default_action_t::enableMirroring "enableMirroring"
     * is set then send the packet on this virtual pipeline too
     * @see ncp_eioa_ingress_acl_mirror_port_get
     */
    ncp_uint8_t                             mirroringBridgeVpId;
    /*!
     * @brief Permits packet 
     * As opposed to permit, denying a packet might result in the dropping the packet in EIOA Core
     * @see ncp_eioa_switch_bridge_acl_deny_vps_get
     */
    ncp_bool_t                              permit;
    /*! 
     * @brief Whether to change the VLAN id used for further processing
     * @see ncp_eioa_egress_modification_options_get
     * @see ncp_eioa_switch_acl_default_action_t::newVlanId
     */
    ncp_bool_t                              changeVlanId;
    /*!
     * @brief New value of VLAN Id to be used for further processing
     * @details If 
     * \ref ncp_eioa_switch_acl_default_action_t::changeVlanId is
     * \c TRUE then use this VLAN id to populate the VLAN id field in task
     * parameters
     */
    ncp_eioa_switch_acl_vlan_id_t           newVlanId;
} ncp_eioa_switch_acl_default_action_t;

/*!
 * @ingroup _eioa_switch_acl_
 * @struct ncp_eioa_switch_acl_rule_t
 * @brief Structure of a rule in EIOA Switch ACL
 * @details Every ACL rule has 12 fields
 * <ul>
 * <li> Destination MAC Address
 * <li> Source MAC Address
 * <li> Destination IP Address
 * <li> Source IP Address
 * <li> Ethertype
 * <li> IP Protocol 
 * <li> Layer 4 Source Port
 * <li> Layer 4 Destination Port
 * <li> DSCP 
 * <li> COS
 * <li> VLAN Id
 * <li> Encryption mode
 * </ul>
 * An ACL rule can specify values to match for every field or a subset of fields. A field produces a match if any one
 * of the values specified for the field matches the corresponding field in the packet. An ACL rule is said to match if all 
 * fields in the rule produce a match. If more than one rule in an ACL matches then the action associated with the rule with 
 * the lowest id is used. To ignore certain fields in a rule set the number of values to 0 for that field.
 * @deprecated Does not address domain id field in AXM5600 and beyond. Use \ref ncp_eioa_switch_acl_rule_t2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_acl_rule_t2
 */
typedef struct ncp_eioa_switch_acl_rule_s
{
    ncp_uint32_t                            numSrcMacAddrs;
    ncp_eioa_switch_acl_mac_addresses_t     *srcMacAddrs;
    ncp_uint32_t                            numDestMacAddrs;
    ncp_eioa_switch_acl_mac_addresses_t     *destMacAddrs;
    ncp_uint32_t                            numSrcIpAddrs;
    ncp_eioa_switch_acl_ip_subnet_t         *srcIpAddrs;
    ncp_uint32_t                            numDestIpAddrs;
    ncp_eioa_switch_acl_ip_subnet_t         *destIpAddrs;
    ncp_uint32_t                            numSrcLayer4Ports;
    ncp_eioa_switch_acl_layer4_port_range_t *srcLayer4Ports;
    ncp_uint32_t                            numDestLayer4Ports;
    ncp_eioa_switch_acl_layer4_port_range_t *destLayer4Ports;
    ncp_uint32_t                            numDscpVals;
    ncp_eioa_switch_acl_dscp_t              *dscpVals;
    ncp_uint32_t                            numCosVals;
    ncp_eioa_switch_acl_cos_t               *cosVals;
    ncp_uint32_t                            numEthertypeVals;
    ncp_eioa_switch_acl_ethertype_t         *ethertypeVals;
    ncp_uint32_t                            numIpProtocolVals;
    ncp_eioa_switch_acl_ip_protocol_t       *ipProtocolVals;
    ncp_uint32_t                            numVlanIds;
    ncp_eioa_switch_acl_vlan_id_t           *vlanIdVals;
    ncp_uint32_t                            numEncryptionModes;
    ncp_eioa_switch_acl_encryption_mode_t   *encryptionModes;
} ncp_eioa_switch_acl_rule_t;


/*!
 * @ingroup _eioa_switch_acl_
 * @struct ncp_eioa_switch_acl_rule_t2
 * @brief Structure of a rule in EIOA Switch ACL
 * @details Every ACL rule has 13 fields
 * <ul>
 * <li> Destination MAC Address
 * <li> Source MAC Address
 * <li> Destination IP Address
 * <li> Source IP Address
 * <li> Ethertype
 * <li> IP Protocol
 * <li> Layer 4 Source Port
 * <li> Layer 4 Destination Port
 * <li> DSCP
 * <li> COS
 * <li> VLAN Id
 * <li> Encryption mode
 * <li> Domain Id (applicable for 56xx and beyond)
 * </ul>
 * An ACL rule can specify values to match for every field or a subset of fields. A field produces a match if any one
 * of the values specified for the field matches the corresponding field in the packet. An ACL rule is said to match if all
 * fields in the rule produce a match. If more than one rule in an ACL matches then the action associated with the rule with
 * the lowest id is used. To ignore certain fields in a rule set the number of values to 0 for that field.
 */
typedef struct ncp_eioa_switch_acl_rule_s2
{
    ncp_uint32_t                            numSrcMacAddrs;
    ncp_eioa_switch_acl_mac_addresses_t     *srcMacAddrs;
    ncp_uint32_t                            numDestMacAddrs;
    ncp_eioa_switch_acl_mac_addresses_t     *destMacAddrs;
    ncp_uint32_t                            numSrcIpAddrs;
    ncp_eioa_switch_acl_ip_subnet_t         *srcIpAddrs;
    ncp_uint32_t                            numDestIpAddrs;
    ncp_eioa_switch_acl_ip_subnet_t         *destIpAddrs;
    ncp_uint32_t                            numSrcLayer4Ports;
    ncp_eioa_switch_acl_layer4_port_range_t *srcLayer4Ports;
    ncp_uint32_t                            numDestLayer4Ports;
    ncp_eioa_switch_acl_layer4_port_range_t *destLayer4Ports;
    ncp_uint32_t                            numDscpVals;
    ncp_eioa_switch_acl_dscp_t              *dscpVals;
    ncp_uint32_t                            numCosVals;
    ncp_eioa_switch_acl_cos_t               *cosVals;
    ncp_uint32_t                            numEthertypeVals;
    ncp_eioa_switch_acl_ethertype_t         *ethertypeVals;
    ncp_uint32_t                            numIpProtocolVals;
    ncp_eioa_switch_acl_ip_protocol_t       *ipProtocolVals;
    ncp_uint32_t                            numVlanIds;
    ncp_eioa_switch_acl_vlan_id_t           *vlanIdVals;
    ncp_uint32_t                            numEncryptionModes;
    ncp_eioa_switch_acl_encryption_mode_t   *encryptionModes;
    ncp_uint32_t                            numDomainIds;
    ncp_eioa_switch_acl_domain_id_t         *domainIdVals;
} ncp_eioa_switch_acl_rule_t2;

/*!
 * @ingroup _eioa_switch_acl_
 * @typedef ncp_eioa_switch_acl_route_policy_t2
 * @brief Structure of a routing policy in EIOA Switch ACL route
 * @see ncp_eioa_switch_acl_rule_t2
 */
typedef ncp_eioa_switch_acl_rule_t2 ncp_eioa_switch_acl_route_policy_t2;

/*!
 * @ingroup _eioa_switch_acl_
 * @typedef ncp_eioa_switch_acl_route_policy_t
 * @brief Structure of a routing policy in EIOA Switch ACL route
 * @see ncp_eioa_switch_acl_rule_t2
 * @deprecated Uses deprecated \ref ncp_eioa_switch_acl_rule_t. Use \ref ncp_eioa_switch_acl_route_policy_t instead
 * @since 1.3.0
 * @see ncp_eioa_switch_acl_route_policy_t
 */
typedef ncp_eioa_switch_acl_rule_t ncp_eioa_switch_acl_route_policy_t;

/*!
 * @ingroup _eioa_switch_acl_
 * @struct ncp_eioa_switch_acl_route_action_t
 * @brief Structure of a route.
 */
typedef struct ncp_eioa_switch_acl_route_action_s
{
	/*!
	 * @brief Destination Virtual Pipeline Index
	 * @details This is an index in the destination map table and specifies the virtual pipelines this routed packet should be transmitted on.
	 * In ACP25xx this index is also used to select the next hop MAC address and new VLAN id to be used to replace or add a new one.
	 * In AXM55xx and beyond \ref ncp_eioa_switch_acl_route_action_t::routingIndex "routingIndex" is used to select the next hop MAC
	 * address and new VLAN id.
	 * @see ncp_eioa_switch_bridge_destination_vps_get
	 * @see ncp_eioa_epp_next_hop_mac_address_config
	 * @see ncp_eioa_epp_non_qinq_router_vlan_map_config
	 * @see ncp_eioa_switch_acl_route_action_t::routingIndex
	 */
    ncp_uint8_t                         destVpsIndex;
    /*!
     * @brief Index to use in AXM55xx and beyond for selecting next hop MAC address and new VLAN id for routed packets.
     * @details This index separates destination virtual pipeline selection from selection of next hop MAC address and new
     * VLAN id.
     * In ACP25xx \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "destVpsIndex" is used to select the next hop MAC address
     * and new VLAN id.
     * @see ncp_eioa_epp_next_hop_mac_address_config
	 * @see ncp_eioa_epp_non_qinq_router_vlan_map_config
	 * @see ncp_eioa_switch_acl_route_action_t::destVpsIndex
     */
    ncp_uint8_t                         routingIndex;
} ncp_eioa_switch_acl_route_action_t;

/*!
 * @ingroup _eioa_switch_acl_
 * @struct ncp_eioa_switch_acl_pbr_route_action_t
 * @brief Structure of a PBR route.
 * @deprecated Does not capture AXM5600 attributes. Use \ref
 * ncp_eioa_switch_acl_pbr_route_action_t2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_acl_pbr_route_action_t2
 */
typedef struct ncp_eioa_switch_acl_pbr_route_action_s
{
	/*!
	 * @brief Specifies destination virtual pipelines index and other routing details.
	 * @details The destination virtual pipelines and other routing related information will be used only if
	 * \ref ncp_eioa_switch_acl_pbr_route_action_t::useRoutingAction is set.
	 * @see ncp_eioa_switch_acl_route_action_t
	 * @see ncp_eioa_switch_acl_pbr_route_action_t::useRoutingAction
	 */
    ncp_eioa_switch_acl_route_action_t    routingAction;
    /*!
     * @brief Enables the use of \ref ncp_eioa_switch_acl_pbr_route_action_t::routingAction "routingAction"
     * @details If set destination virtual pipeline index and other routing details specified in
     * \ref ncp_eioa_switch_acl_pbr_route_action_t::routingAction will be used. If this flag is not set then routing results from
     * destination IP address routing will be used.
     * @see ncp_eioa_switch_acl_route_action_t
     * @see ncp_eioa_switch_acl_pbr_route_action_t::routingAction
     */
    ncp_bool_t                            useRoutingAction;
    /*!
     * @brief Specifies an id for this action
     * @details This field specified a value within the range <tt> 0 <= actionId < 1024 </tt>. When
     * \ref ncp_eioa_switch_acl_pbr_route_action_t::useActionIdInTask is set, this field can be used to specify an id to downstream engine to
     * identify unique actions in policy based routing tables. An action is considered unique if it has a unique combination of
     * \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "routingAction.destVpsIndex" and
     * \ref ncp_eioa_switch_acl_route_action_t::routingIndex "routingAction.routingIndex". If
     * \ref ncp_eioa_switch_acl_pbr_route_action_t::useActionIdInTask is not set then this field can have undefined value.
     * @see ncp_eioa_switch_acl_pbr_route_action_t::useActionIdInTask
     * @see ncp_eioa_switch_acl_route_action_t::destVpsIndex
     * @see ncp_eioa_switch_acl_route_action_t::routingIndex
     */
    ncp_uint16_t                          actionId;
    /*!
     * @brief Enables use of \ref ncp_eioa_switch_acl_pbr_route_action_t::actionId "actionId" in task parameters
     * @details If this field is set then \ref ncp_eioa_switch_acl_pbr_route_action_t::actionId "actionId" is used to populate task parameters
     * in classification format.
     * @see ncp_eioa_switch_acl_pbr_route_action_t::actionId
     */
    ncp_bool_t                            useActionIdInTask;
} ncp_eioa_switch_acl_pbr_route_action_t;

/*!
 * @ingroup _eioa_switch_acl_
 * @struct ncp_eioa_switch_acl_pbr_route_action_t2
 * @brief Structure of a route.
 */
typedef struct ncp_eioa_switch_acl_pbr_route_action_s2
{
	/*!
	 * @brief Specifies destination virtual pipelines index and other routing details.
	 * @details The destination virtual pipelines and other routing related information will be used only if
	 * \ref ncp_eioa_switch_acl_pbr_route_action_t2::useRoutingAction is set.
	 * @see ncp_eioa_switch_acl_route_action_t
	 * @see ncp_eioa_switch_acl_pbr_route_action_t2::useRoutingAction
	 */
    ncp_eioa_switch_acl_route_action_t    routingAction;
    /*!
     * @brief Enables the use of \ref ncp_eioa_switch_acl_pbr_route_action_t2::routingAction "routingAction"
     * @details If set destination virtual pipeline index and other routing details specified in
     * \ref ncp_eioa_switch_acl_pbr_route_action_t2::routingAction will be used. If this flag is not set then routing results from
     * destination IP address routing will be used.
     * @see ncp_eioa_switch_acl_route_action_t
     * @see ncp_eioa_switch_acl_pbr_route_action_t2::routingAction
     */
    ncp_bool_t                            useRoutingAction;
    /*!
     * @brief Specifies an id for this action
     * @details This field specified a value within the range <tt> 0 <= actionId < 1024 </tt>. When
     * \ref ncp_eioa_switch_acl_pbr_route_action_t2::useActionIdInTask is set, this field can be used to specify an id to downstream engine to
     * identify unique actions in policy based routing tables. An action is considered unique if it has a unique combination of
     * \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "routingAction.destVpsIndex" and
     * \ref ncp_eioa_switch_acl_route_action_t::routingIndex "routingAction.routingIndex". If
     * \ref ncp_eioa_switch_acl_pbr_route_action_t2::useActionIdInTask is not set then this field can have undefined value.
     * @see ncp_eioa_switch_acl_pbr_route_action_t2::useActionIdInTask
     * @see ncp_eioa_switch_acl_route_action_t::destVpsIndex
     * @see ncp_eioa_switch_acl_route_action_t::routingIndex
     */
    ncp_uint16_t                          actionId;
    /*!
     * @brief Enables use of \ref ncp_eioa_switch_acl_pbr_route_action_t2::actionId "actionId" in task parameters
     * @details If this field is set then \ref ncp_eioa_switch_acl_pbr_route_action_t2::actionId "actionId" is used to populate task parameters
     * in classification format.
     * @see ncp_eioa_switch_acl_pbr_route_action_t2::actionId
     */
    ncp_bool_t                            useActionIdInTask;
    /*!
     * @brief Enables the use of \ref ncp_eioa_switch_acl_pbr_route_action_t2::routingAction "routingAction" as bridging action
     * @details If set destination virtual pipeline index specified in
     * \ref ncp_eioa_switch_acl_pbr_route_action_t2::routingAction will be used. If this flag is not set and \ref ncp_eioa_switch_acl_pbr_route_action_t2::useRoutingAction "useRoutingAction"
     * is also not set then destination virtual pipeline index from destination MAC table look up is used
     * @see ncp_eioa_switch_acl_route_action_t
     * @see ncp_eioa_switch_acl_pbr_route_action_t2::routingAction
     */
    ncp_bool_t                            useBridgingAction;
} ncp_eioa_switch_acl_pbr_route_action_t2;


/*!
 * @ingroup _eioa_switch_acl_
 * @struct ncp_eioa_switch_acl_port_cfg_t
 * @brief Port configuration used EIOA Switch ACL declaration
 */
typedef struct ncp_eioa_switch_acl_port_cfg_s
{
    /*!
     * @brief Define trust mode for IP packets
     * @details \ref ncp_eioa_switch_acl_trust_mode_t "trustMode"
     * specifies the source for setting the task priority
     * If #NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_COS is specified then use
     * COS DSCP map to assign task
     * priority. If #NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_IP_PRECEDENCE is
     * specified then use IP Precedence
     * DSCP map to assign task priority. If
     * #NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_DSCP
     * is specified then use DSCP DSCP map to assign task priority
     * If #NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED is specified then use
     * \ref ncp_eioa_switch_acl_default_action_t::ipDscpValue value to
     * decide the task priority
     * @see ncp_eioa_switch_acl_default_action_t::ipDscpValue
     * @see ncp_eioa_switch_acl_cos_to_dscp_map_get
     * @see ncp_eioa_switch_acl_ip_precedence_to_dscp_map_get
     * @see ncp_eioa_switch_acl_dscp_to_dscp_map_get
     */
    ncp_eioa_switch_acl_trust_mode_t        ipTrustMode;
    /*!
     * @brief Define trust mode for non IP packets
     * @details \ref ncp_eioa_switch_acl_trust_mode_t
     * specifies the source for setting the task priority
     * If #NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_COS is specified then use
     * COS DSCP map to assign task priority.
     * If #NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED is specified then use
     * \ref ncp_eioa_switch_acl_default_action_t::nonIpDscpValue value to
     * decide the task priority.
     * #NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED and
     * #NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_COS are the only applicable values
     * for this field.
     * @see ncp_eioa_switch_acl_default_action_t::nonIpDscpValue
     * @see ncp_eioa_switch_acl_cos_to_dscp_map_get
     */
    ncp_eioa_switch_acl_trust_mode_t        nonIpTrustMode;
    /*!
     * @brief Enable use of MAC priority as COS value
     * @see ncp_eioa_switch_bridge_port_attrs_get
     */
    ncp_bool_t                              enableMacPriority;
    /*!
     * @brief Enable use of priority from MPLS header as COS value
     * @see ncp_ipp_options_t::enableMpls
     */
    ncp_bool_t                              enableMplsPriority;
    /*!
     * @brief COS value for a Ethertype
     * @details Maps a \ref ncp_eioa_switch_acl_ethertype_t to a COS value.
     * If \ref ncp_eioa_switch_acl_cos_t::prefixLength is set to 0 then that mapping is considered invalid.
     */
    ncp_eioa_switch_acl_cos_t               ethertypeCosMap[16];
    /*!
     * @brief COS value to use if all else fails
     * @details Use this COS value for a untagged VLAN packet and if \ref ncp_eioa_switch_acl_port_cfg_t::enableMacPriority is FALSE
     * and if there is no mapping for the \ref ncp_eioa_switch_acl_ethertype_t in \ref ncp_eioa_switch_acl_port_cfg_t::ethertypeCosMap
     * and \ref ncp_eioa_switch_acl_port_cfg_t::ipTrustMode is #NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_COS
     * for a IP packet or \ref ncp_eioa_switch_acl_port_cfg_t::nonIpTrustMode is #NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_COS for a non-IP
     * packet
     */
    ncp_eioa_switch_acl_cos_t               defaultCosValue;
} ncp_eioa_switch_acl_port_cfg_t;

/*!
 * @ingroup _eioa_switch_acl_
 * @struct ncp_eioa_switch_acl_port_trust_cfg_t
 * @brief Port trust configuration used EIOA Switch ACL declaration
 */
typedef struct ncp_eioa_switch_acl_port_trust_cfg_s
{
    /*!
     * @brief Define trust mode for IP packets
     * @details \ref ncp_eioa_switch_acl_trust_mode_t "trustMode"
     * specifies the source for setting the task priority
     * If #NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_COS is specified then use
     * COS DSCP map to assign task
     * priority. If #NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_IP_PRECEDENCE is
     * specified then use IP Precedence
     * DSCP map to assign task priority. If
     * #NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_DSCP
     * is specified then use DSCP DSCP map to assign task priority
     * If #NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED is specified then use
     * \ref ncp_eioa_switch_acl_default_action_t::ipDscpValue value to
     * decide the task priority
     * @see ncp_eioa_switch_acl_default_action_t::ipDscpValue
     * @see ncp_eioa_switch_acl_cos_to_dscp_map_get
     * @see ncp_eioa_switch_acl_ip_precedence_to_dscp_map_get
     * @see ncp_eioa_switch_acl_dscp_to_dscp_map_get
     */
    ncp_eioa_switch_acl_trust_mode_t        ipTrustMode;
    /*!
     * @brief Define trust mode for non IP packets
     * @details \ref ncp_eioa_switch_acl_trust_mode_t
     * specifies the source for setting the task priority
     * If #NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_COS is specified then use
     * COS DSCP map to assign task priority.
     * If #NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED is specified then use
     * \ref ncp_eioa_switch_acl_default_action_t::nonIpDscpValue value to
     * decide the task priority.
     * #NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED and
     * #NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_COS are the only applicable values
     * for this field.
     * @see ncp_eioa_switch_acl_default_action_t::nonIpDscpValue
     * @see ncp_eioa_switch_acl_cos_to_dscp_map_get
     */
    ncp_eioa_switch_acl_trust_mode_t        nonIpTrustMode;
    /*!
     * @brief Enables use of \ref ncp_eioa_switch_acl_port_cfg_t::untaggedTrustMode "untaggedTrustMode"
     */
    ncp_bool_t                              overrideUntaggedTrustMode;
    /*!
     * @brief Trust mode to use when \ref ncp_eioa_switch_acl_port_cfg_t::overrideUntaggedTrustMode "overrideUntaggedTrustMode" is set and the packet is untagged
     */
    ncp_eioa_switch_acl_trust_mode_t        untaggedTrustMode;
    /*!
     * @brief Enables use of \ref ncp_eioa_switch_acl_port_cfg_t::taggedTrustMode "taggedTrustMode"
     */
    ncp_bool_t                              overrideTaggedTrustMode;
    /*!
     * @brief Trust mode to use when \ref ncp_eioa_switch_acl_port_cfg_t::overrideTaggedTrustMode "overrideTaggedTrustMode" is set and the packet is tagged
     */
    ncp_eioa_switch_acl_trust_mode_t        taggedTrustMode;
    /*!
     * @brief Enables the use of \ref ncp_eioa_switch_acl_port_cfg_t::priorityTaggedTrustMode "priorityTaggedTrustMode"
     */
    ncp_bool_t                              overridePriorityTaggedTrustMode;
    /*!
     * @brief Trust mode to use when \ref ncp_eioa_switch_acl_port_cfg_t::overridePriorityTaggedTrustMode "overridePriorityTaggedTrustMode" is set and the packet is priority tagged
     * @details A packet is priority tagged if the packet is VLAN tagged and the VLAN id equals 0 (zero)
     */
    ncp_eioa_switch_acl_trust_mode_t        priorityTaggedTrustMode;
} ncp_eioa_switch_acl_port_trust_cfg_t;

/*!
 * @ingroup _eioa_switch_acl_
 * @brief Deletes all rules from in-memory ACL data structure.
 * @details Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] aclId ACL with ACL ID to be cleared
 * @return 
 * <ul>
 * <li> #NCP_ST_SUCCESS - if API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_ACL_ID - if \c aclId is not in the range <tt> 0 <= aclId < 32 </tt>
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_clear(ncp_hdl_t ncpHdl, ncp_uint32_t aclId );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Adds a rule as the first rule to in-memory ACL data structure.
 * @details This is the same as invoking \ref ncp_eioa_switch_acl_insert with
 * \c ruleId as 0. Shifts the rule currently at first position (if any) and
 * any subsequent rules down (adds one to their \c ruleId).
 * Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] aclId ACL with the ACL ID where this rule is to be added
 * @param[in] rule ACL rule to be prepended
 * @param[in] action The action associated with the rule to be added
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c rule or \c action is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_ACL_ID - if \c aclId is not in the range <tt> 0 <= aclId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_RULES - if the number of rules in an ACL exceeds the maximum number of rules allowed
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_ADDRESSES - if no more MAC addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_WILDCARD_ADDRESSES - if no more MAC addresses with ignore bits can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_MAC_WILDCARD_ADDRESS_PARTIAL_OVERLAP - if one
 * of the MAC wild card addresses partially overlaps with another MAC wild card
 * address
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IPv4_ADDRESSES - if no more IPv4 addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IP_ADDRESSES - if no more IP addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_IPv6_ADDRESS_IN_IPv4_MODE - if encountered an IPv6 address in IPv4 \ref ncp_eioa_switch_acl_ip_address_mode_t "mode"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_LAYER_4_PORTS - if no more Layer 4 ports can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_VLAN_ID - if 
 * \ref ncp_eioa_switch_acl_action_t::changeVlanId "action->changeVlanId" is 
 * \c TRUE and is invalid or
 * if any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids"
 * in rules has a non-zero \ref ncp_eioa_switch_acl_vlan_id_t::prefixLength "prefixLength" 
 * when \ref ncp_eioa_switch_acl_selection_mode_get "ACL selection" is based on 
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_VLAN_SELECTS "VLAN" or 
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_PORT_AND_VLAN_SELECTS "Port and VLAN"
 * or any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids" in
 * rules are invalid. A \ref ncp_eioa_switch_acl_vlan_id_t "rule VLAN Id" is 
 * invalid if either <tt> vlanId.prefixLength != 12 </tt> or 
 * <tt> vlanId.prefixLength != 0 </tt> or VLAN id value is not in the range 
 * <tt> 0 <= vlanId.value < 4096 </tt>. A 
 * \ref ncp_eioa_switch_acl_action_t::newVlanId "action VLAN Id" is invalid if
 * either <tt> vlanId.prefixLength != 12 </tt> or VLAN id value is not in the 
 * range <tt> 0 <= vlanId.value < 4096 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_POLICER_ID - if
 * \ref ncp_eioa_switch_acl_action_t::policerId "action->policerId"
 * is not in the range <tt> 0 <= action->policerId < 512 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_POLICER_MAP - if 
 * \ref ncp_eioa_switch_acl_action_t::enablePolicing "action->enablePolicing" is \c TRUE and
 * \ref ncp_eioa_switch_policer_mode_t "Policer selection" is not #NCP_EIOA_SWITCH_POLICER_MODE_ACL_RULE
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_DSCP - if any of the \ref ncp_eioa_switch_acl_rule_t2::dscpVals "DSCPs" in rule has
 * <tt> dscp->prefixLength != 6 </tt> or \c dscp->value is not in the range <tt> 0 <= dscp->value < 64 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_COS - if any of the \ref ncp_eioa_switch_acl_rule_t2::cosVals "COS values" in rule has <tt>cos.prefixLength != 3</tt>
 * or \c cos.value is not in the range <tt> 0 <= cos.value < 8 </tt>
 * <li> #NCP_ST_NO_MEMORY - if host memory allocation failed when modifying this rule in the in-memory ACL data structure
 * </ul>
 * @deprecated Uses deprecated \ref ncp_eioa_switch_acl_rule_t. Use \ref ncp_eioa_switch_acl_prepend2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_acl_prepend2
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_prepend(ncp_hdl_t ncpHdl, ncp_uint32_t aclId, const ncp_eioa_switch_acl_rule_t *rule, const ncp_eioa_switch_acl_action_t *action );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Adds a rule as the first rule to in-memory ACL data structure.
 * @details This is the same as invoking \ref ncp_eioa_switch_acl_insert with
 * \c ruleId as 0. Shifts the rule currently at first position (if any) and
 * any subsequent rules down (adds one to their \c ruleId).
 * Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] aclId ACL with the ACL ID where this rule is to be added
 * @param[in] rule ACL rule to be prepended
 * @param[in] action The action associated with the rule to be added
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c rule or \c action is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_ACL_ID - if \c aclId is not in the range <tt> 0 <= aclId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_RULES - if the number of rules in an ACL exceeds the maximum number of rules allowed
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_ADDRESSES - if no more MAC addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_WILDCARD_ADDRESSES - if no more MAC addresses with ignore bits can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_MAC_WILDCARD_ADDRESS_PARTIAL_OVERLAP - if one
 * of the MAC wild card addresses partially overlaps with another MAC wild card
 * address
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IPv4_ADDRESSES - if no more IPv4 addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IP_ADDRESSES - if no more IP addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_IPv6_ADDRESS_IN_IPv4_MODE - if encountered an IPv6 address in IPv4 \ref ncp_eioa_switch_acl_ip_address_mode_t "mode"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_LAYER_4_PORTS - if no more Layer 4 ports can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_VLAN_ID - if
 * \ref ncp_eioa_switch_acl_action_t::changeVlanId "action->changeVlanId" is
 * \c TRUE and is invalid or
 * if any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids"
 * in rules has a non-zero \ref ncp_eioa_switch_acl_vlan_id_t::prefixLength "prefixLength"
 * when \ref ncp_eioa_switch_acl_selection_mode_get "ACL selection" is based on
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_VLAN_SELECTS "VLAN" or
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_PORT_AND_VLAN_SELECTS "Port and VLAN"
 * or any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids" in
 * rules are invalid. A \ref ncp_eioa_switch_acl_vlan_id_t "rule VLAN Id" is
 * invalid if either <tt> vlanId.prefixLength != 12 </tt> or
 * <tt> vlanId.prefixLength != 0 </tt> or VLAN id value is not in the range
 * <tt> 0 <= vlanId.value < 4096 </tt>. A
 * \ref ncp_eioa_switch_acl_action_t::newVlanId "action VLAN Id" is invalid if
 * either <tt> vlanId.prefixLength != 12 </tt> or VLAN id value is not in the
 * range <tt> 0 <= vlanId.value < 4096 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_POLICER_ID - if
 * \ref ncp_eioa_switch_acl_action_t::policerId "action->policerId"
 * is not in the range <tt> 0 <= action->policerId < 512 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_POLICER_MAP - if
 * \ref ncp_eioa_switch_acl_action_t::enablePolicing "action->enablePolicing" is \c TRUE and
 * \ref ncp_eioa_switch_policer_mode_t "Policer selection" is not #NCP_EIOA_SWITCH_POLICER_MODE_ACL_RULE
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_DSCP - if any of the \ref ncp_eioa_switch_acl_rule_t2::dscpVals "DSCPs" in rule has
 * <tt> dscp->prefixLength != 6 </tt> or \c dscp->value is not in the range <tt> 0 <= dscp->value < 64 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_COS - if any of the \ref ncp_eioa_switch_acl_rule_t2::cosVals "COS values" in rule has <tt>cos.prefixLength != 3</tt>
 * or \c cos.value is not in the range <tt> 0 <= cos.value < 8 </tt>
 * <li> #NCP_ST_NO_MEMORY - if host memory allocation failed when modifying this rule in the in-memory ACL data structure
 * </ul>
 * @see ncp_eioa_switch_acl_insert
 * @see ncp_eioa_switch_acl_num_rules_get
 * @see ncp_eioa_switch_acl_num_mac_addresses_get
 * @see ncp_eioa_switch_acl_num_mac_addresses_with_wildcards_get
 * @see ncp_eioa_switch_acl_num_ip_addresses_get
 * @see ncp_eioa_switch_acl_num_l4_ports_get
 * @see ncp_eioa_switch_acl_ip_address_mode_get
 * @see ncp_eioa_switch_policer_mode_get
 * @see ncp_eioa_switch_acl_selection_mode_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_prepend2(ncp_hdl_t ncpHdl, ncp_uint32_t aclId, const ncp_eioa_switch_acl_rule_t2 *rule, const ncp_eioa_switch_acl_action_t *action );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Adds a rule as the last rule to in-memory ACL data structure.
 * @details Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] aclId ACL with the ACL ID where this rule is to be added
 * @param[in] rule ACL rule to append
 * @param[in] action The action associated with the rule to be added
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c rule or \c action is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_ACL_ID - if \c aclId is not in the range <tt> 0 <= aclId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_RULES - if the number of rules in an ACL exceeds the maximum number of rules allowed
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_ADDRESSES - if no more MAC addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_WILDCARD_ADDRESSES - if no more MAC addresses with ignore bits can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_MAC_WILDCARD_ADDRESS_PARTIAL_OVERLAP - if one
 * of the MAC wild card addresses partially overlaps with another MAC wild card
 * address
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IPv4_ADDRESSES - if no more IPv4 addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IP_ADDRESSES - if no more IP addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_IPv6_ADDRESS_IN_IPv4_MODE - if encountered an IPv6 address in IPv4 \ref ncp_eioa_switch_acl_ip_address_mode_t "mode"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_LAYER_4_PORTS - if no more Layer 4 ports can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_VLAN_ID - if 
 * \ref ncp_eioa_switch_acl_action_t::changeVlanId "action->changeVlanId" is 
 * \c TRUE and is invalid or
 * if any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids"
 * in rules has a non-zero \ref ncp_eioa_switch_acl_vlan_id_t::prefixLength "prefixLength" 
 * when \ref ncp_eioa_switch_acl_selection_mode_get "ACL selection" is based on 
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_VLAN_SELECTS "VLAN" or 
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_PORT_AND_VLAN_SELECTS "Port and VLAN"
 * or any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids" in
 * rules are invalid. A \ref ncp_eioa_switch_acl_vlan_id_t "rule VLAN Id" is 
 * invalid if either <tt> vlanId.prefixLength != 12 </tt> or 
 * <tt> vlanId.prefixLength != 0 </tt> or VLAN id value is not in the range 
 * <tt> 0 <= vlanId.value < 4096 </tt>. A 
 * \ref ncp_eioa_switch_acl_action_t::newVlanId "action VLAN Id" is invalid if
 * either <tt> vlanId.prefixLength != 12 </tt> or VLAN id value is not in the 
 * range <tt> 0 <= vlanId.value < 4096 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_POLICER_ID - if
 * \ref ncp_eioa_switch_acl_action_t::policerId "action->policerId"
 * is not in the range <tt> 0 <= action->policerId < 512 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_POLICER_MAP - if
 * \ref ncp_eioa_switch_acl_action_t::enablePolicing "action->enablePolicing" is \c TRUE and
 * \ref ncp_eioa_switch_policer_mode_t "Policer selection" is not #NCP_EIOA_SWITCH_POLICER_MODE_ACL_RULE
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_DSCP - if any of the \ref ncp_eioa_switch_acl_rule_t2::dscpVals "DSCPs" in rule has
 * <tt> dscp->prefixLength != 6 </tt> or \c dscp->value is not in the range <tt> 0 <= dscp->value < 64 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_COS - if any of the \ref ncp_eioa_switch_acl_rule_t2::cosVals "COS values" in rule has <tt>cos.prefixLength != 3</tt>
 * or \c cos.value is not in the range <tt> 0 <= cos.value < 8 </tt>
 * <li> #NCP_ST_NO_MEMORY - if host memory allocation failed when creating this rule in the in-memory ACL data structure
 * </ul>
 * @deprecated Uses deprecated \ref ncp_eioa_switch_acl_rule_t. Use \ref ncp_eioa_switch_acl_append2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_acl_append2
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_append(ncp_hdl_t ncpHdl, ncp_uint32_t aclId, const ncp_eioa_switch_acl_rule_t *rule, const ncp_eioa_switch_acl_action_t *action );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Adds a rule as the last rule to in-memory ACL data structure.
 * @details Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] aclId ACL with the ACL ID where this rule is to be added
 * @param[in] rule ACL rule to append
 * @param[in] action The action associated with the rule to be added
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c rule or \c action is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_ACL_ID - if \c aclId is not in the range <tt> 0 <= aclId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_RULES - if the number of rules in an ACL exceeds the maximum number of rules allowed
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_ADDRESSES - if no more MAC addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_WILDCARD_ADDRESSES - if no more MAC addresses with ignore bits can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_MAC_WILDCARD_ADDRESS_PARTIAL_OVERLAP - if one
 * of the MAC wild card addresses partially overlaps with another MAC wild card
 * address
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IPv4_ADDRESSES - if no more IPv4 addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IP_ADDRESSES - if no more IP addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_IPv6_ADDRESS_IN_IPv4_MODE - if encountered an IPv6 address in IPv4 \ref ncp_eioa_switch_acl_ip_address_mode_t "mode"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_LAYER_4_PORTS - if no more Layer 4 ports can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_VLAN_ID - if
 * \ref ncp_eioa_switch_acl_action_t::changeVlanId "action->changeVlanId" is
 * \c TRUE and is invalid or
 * if any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids"
 * in rules has a non-zero \ref ncp_eioa_switch_acl_vlan_id_t::prefixLength "prefixLength"
 * when \ref ncp_eioa_switch_acl_selection_mode_get "ACL selection" is based on
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_VLAN_SELECTS "VLAN" or
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_PORT_AND_VLAN_SELECTS "Port and VLAN"
 * or any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids" in
 * rules are invalid. A \ref ncp_eioa_switch_acl_vlan_id_t "rule VLAN Id" is
 * invalid if either <tt> vlanId.prefixLength != 12 </tt> or
 * <tt> vlanId.prefixLength != 0 </tt> or VLAN id value is not in the range
 * <tt> 0 <= vlanId.value < 4096 </tt>. A
 * \ref ncp_eioa_switch_acl_action_t::newVlanId "action VLAN Id" is invalid if
 * either <tt> vlanId.prefixLength != 12 </tt> or VLAN id value is not in the
 * range <tt> 0 <= vlanId.value < 4096 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_POLICER_ID - if
 * \ref ncp_eioa_switch_acl_action_t::policerId "action->policerId"
 * is not in the range <tt> 0 <= action->policerId < 512 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_POLICER_MAP - if
 * \ref ncp_eioa_switch_acl_action_t::enablePolicing "action->enablePolicing" is \c TRUE and
 * \ref ncp_eioa_switch_policer_mode_t "Policer selection" is not #NCP_EIOA_SWITCH_POLICER_MODE_ACL_RULE
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_DSCP - if any of the \ref ncp_eioa_switch_acl_rule_t2::dscpVals "DSCPs" in rule has
 * <tt> dscp->prefixLength != 6 </tt> or \c dscp->value is not in the range <tt> 0 <= dscp->value < 64 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_COS - if any of the \ref ncp_eioa_switch_acl_rule_t2::cosVals "COS values" in rule has <tt>cos.prefixLength != 3</tt>
 * or \c cos.value is not in the range <tt> 0 <= cos.value < 8 </tt>
 * <li> #NCP_ST_NO_MEMORY - if host memory allocation failed when creating this rule in the in-memory ACL data structure
 * </ul>
 * @see ncp_eioa_switch_acl_num_rules_get
 * @see ncp_eioa_switch_acl_num_mac_addresses_get
 * @see ncp_eioa_switch_acl_num_mac_addresses_with_wildcards_get
 * @see ncp_eioa_switch_acl_num_ip_addresses_get
 * @see ncp_eioa_switch_acl_num_l4_ports_get
 * @see ncp_eioa_switch_acl_ip_address_mode_get
 * @see ncp_eioa_switch_policer_mode_get
 * @see ncp_eioa_switch_acl_selection_mode_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_append2(ncp_hdl_t ncpHdl, ncp_uint32_t aclId, const ncp_eioa_switch_acl_rule_t2 *rule, const ncp_eioa_switch_acl_action_t *action );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Inserts a rule at the specified position to in-memory ACL data structure.
 * @details Shifts the rule currently at \c ruleId position (if any) and any
 * subsequent rules down (adds one to their \c ruleId).
 * Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] aclId ACL with the ACL ID where this rule is to be added
 * @param[in] ruleId ACL rule id at which the specified rule will be added
 * @param[in] rule ACL rule to insert
 * @param[in] action The action associated with the rule to be added
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c rule or \c action is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_ACL_ID - if \c aclId is not in the range <tt> 0 <= aclId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_RULES - if the number of rules in an ACL exceeds the maximum number of rules allowed
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_RULE_ID - if \c ruleId is not in
 * the range <tt> 0 <= ruleId <= </tt> \ref ncp_eioa_switch_acl_num_rules_get "ACL size "
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_ADDRESSES - if no more MAC addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_WILDCARD_ADDRESSES - if no more MAC addresses with ignore bits can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_MAC_WILDCARD_ADDRESS_PARTIAL_OVERLAP - if one
 * of the MAC wild card addresses partially overlaps with another MAC wild card
 * address
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IPv4_ADDRESSES - if no more IPv4 addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IP_ADDRESSES - if no more IP addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_IPv6_ADDRESS_IN_IPv4_MODE - if encountered an IPv6 address in IPv4 \ref ncp_eioa_switch_acl_ip_address_mode_t "mode"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_LAYER_4_PORTS - if no more Layer 4 ports can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_VLAN_ID - if 
 * \ref ncp_eioa_switch_acl_action_t::changeVlanId "action->changeVlanId" is 
 * \c TRUE and is invalid or
 * if any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids"
 * in rules has a non-zero \ref ncp_eioa_switch_acl_vlan_id_t::prefixLength "prefixLength" 
 * when \ref ncp_eioa_switch_acl_selection_mode_get "ACL selection" is based on 
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_VLAN_SELECTS "VLAN" or 
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_PORT_AND_VLAN_SELECTS "Port and VLAN"
 * or any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids" in
 * rules are invalid. A \ref ncp_eioa_switch_acl_vlan_id_t "rule VLAN Id" is 
 * invalid if either <tt> vlanId.prefixLength != 12 </tt> or 
 * <tt> vlanId.prefixLength != 0 </tt> or VLAN id value is not in the range 
 * <tt> 0 <= vlanId.value < 4096 </tt>. A 
 * \ref ncp_eioa_switch_acl_action_t::newVlanId "action VLAN Id" is invalid if
 * either <tt> vlanId.prefixLength != 12 </tt> or VLAN id value is not in the 
 * range <tt> 0 <= vlanId.value < 4096 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_POLICER_ID - if
 * \ref ncp_eioa_switch_acl_action_t::policerId "action->policerId"
 * is not in the range <tt> 0 <= action->policerId < 512 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_POLICER_MAP - if
 * \ref ncp_eioa_switch_acl_action_t::enablePolicing "action->enablePolicing" is
 * \c TRUE and
 * \ref ncp_eioa_switch_policer_mode_t "Policer selection" is not #NCP_EIOA_SWITCH_POLICER_MODE_ACL_RULE
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_DSCP - if any of the \ref ncp_eioa_switch_acl_rule_t2::dscpVals "DSCPs" in rule has
 * <tt> dscp->prefixLength != 6 </tt> or \c dscp->value is not in the range <tt> 0 <= dscp->value < 64 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_COS - if any of the \ref ncp_eioa_switch_acl_rule_t2::cosVals "COS values" in rule has <tt>cos.prefixLength != 3</tt>
 * or \c cos.value is not in the range <tt> 0 <= cos.value < 8 </tt>
 * <li> #NCP_ST_NO_MEMORY - if host memory allocation failed when creating this rule in the in-memory ACL data structure
 * </ul>
 * @deprecated Uses deprecated \ref ncp_eioa_switch_acl_rule_t. Use \ref ncp_eioa_switch_acl_insert2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_acl_insert2
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_insert(ncp_hdl_t ncpHdl, ncp_uint32_t aclId, ncp_uint32_t ruleId, const ncp_eioa_switch_acl_rule_t *rule, const ncp_eioa_switch_acl_action_t *action );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Inserts a rule at the specified position to in-memory ACL data structure.
 * @details Shifts the rule currently at \c ruleId position (if any) and any
 * subsequent rules down (adds one to their \c ruleId).
 * Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] aclId ACL with the ACL ID where this rule is to be added
 * @param[in] ruleId ACL rule id at which the specified rule will be added
 * @param[in] rule ACL rule to insert
 * @param[in] action The action associated with the rule to be added
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c rule or \c action is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_ACL_ID - if \c aclId is not in the range <tt> 0 <= aclId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_RULES - if the number of rules in an ACL exceeds the maximum number of rules allowed
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_RULE_ID - if \c ruleId is not in
 * the range <tt> 0 <= ruleId <= </tt> \ref ncp_eioa_switch_acl_num_rules_get "ACL size "
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_ADDRESSES - if no more MAC addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_WILDCARD_ADDRESSES - if no more MAC addresses with ignore bits can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_MAC_WILDCARD_ADDRESS_PARTIAL_OVERLAP - if one
 * of the MAC wild card addresses partially overlaps with another MAC wild card
 * address
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IPv4_ADDRESSES - if no more IPv4 addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IP_ADDRESSES - if no more IP addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_IPv6_ADDRESS_IN_IPv4_MODE - if encountered an IPv6 address in IPv4 \ref ncp_eioa_switch_acl_ip_address_mode_t "mode"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_LAYER_4_PORTS - if no more Layer 4 ports can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_VLAN_ID - if
 * \ref ncp_eioa_switch_acl_action_t::changeVlanId "action->changeVlanId" is
 * \c TRUE and is invalid or
 * if any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids"
 * in rules has a non-zero \ref ncp_eioa_switch_acl_vlan_id_t::prefixLength "prefixLength"
 * when \ref ncp_eioa_switch_acl_selection_mode_get "ACL selection" is based on
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_VLAN_SELECTS "VLAN" or
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_PORT_AND_VLAN_SELECTS "Port and VLAN"
 * or any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids" in
 * rules are invalid. A \ref ncp_eioa_switch_acl_vlan_id_t "rule VLAN Id" is
 * invalid if either <tt> vlanId.prefixLength != 12 </tt> or
 * <tt> vlanId.prefixLength != 0 </tt> or VLAN id value is not in the range
 * <tt> 0 <= vlanId.value < 4096 </tt>. A
 * \ref ncp_eioa_switch_acl_action_t::newVlanId "action VLAN Id" is invalid if
 * either <tt> vlanId.prefixLength != 12 </tt> or VLAN id value is not in the
 * range <tt> 0 <= vlanId.value < 4096 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_POLICER_ID - if
 * \ref ncp_eioa_switch_acl_action_t::policerId "action->policerId"
 * is not in the range <tt> 0 <= action->policerId < 512 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_POLICER_MAP - if
 * \ref ncp_eioa_switch_acl_action_t::enablePolicing "action->enablePolicing" is
 * \c TRUE and
 * \ref ncp_eioa_switch_policer_mode_t "Policer selection" is not #NCP_EIOA_SWITCH_POLICER_MODE_ACL_RULE
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_DSCP - if any of the \ref ncp_eioa_switch_acl_rule_t2::dscpVals "DSCPs" in rule has
 * <tt> dscp->prefixLength != 6 </tt> or \c dscp->value is not in the range <tt> 0 <= dscp->value < 64 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_COS - if any of the \ref ncp_eioa_switch_acl_rule_t2::cosVals "COS values" in rule has <tt>cos.prefixLength != 3</tt>
 * or \c cos.value is not in the range <tt> 0 <= cos.value < 8 </tt>
 * <li> #NCP_ST_NO_MEMORY - if host memory allocation failed when creating this rule in the in-memory ACL data structure
 * </ul>
 * @see ncp_eioa_switch_acl_num_rules_get
 * @see ncp_eioa_switch_acl_num_mac_addresses_get
 * @see ncp_eioa_switch_acl_num_mac_addresses_with_wildcards_get
 * @see ncp_eioa_switch_acl_num_ip_addresses_get
 * @see ncp_eioa_switch_acl_num_l4_ports_get
 * @see ncp_eioa_switch_acl_ip_address_mode_get
 * @see ncp_eioa_switch_policer_mode_get
 * @see ncp_eioa_switch_acl_selection_mode_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_insert2(ncp_hdl_t ncpHdl, ncp_uint32_t aclId, ncp_uint32_t ruleId, const ncp_eioa_switch_acl_rule_t2 *rule, const ncp_eioa_switch_acl_action_t *action );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Deletes a rule at the specified position from in-memory ACL data structure.
 * @details Shifts any subsequent rules up 
 * (substracts one from their \c ruleId).
 * Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] aclId ACL with the ACL ID where this rule is to be added
 * @param[in] ruleId ACL rule id to delete
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_ACL_ID - if \c aclId is not in the range <tt> 0 <= aclId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_RULE_ID - if \c ruleId is not in the range
 * <tt> 0 <= ruleId < </tt> \ref ncp_eioa_switch_acl_num_rules_get "ACL size "
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_delete(ncp_hdl_t ncpHdl, ncp_uint32_t aclId, ncp_uint32_t ruleId );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Modify a rule at the specified position in in-memory ACL data structure.
 * @details Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] aclId ACL with the ACL ID where this rule is to be added
 * @param[in] rule The rule that will be modified
 * @param[in] action The action associated with the rule to be modified
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c rule or \c action is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_ACL_ID - if \c aclId is not in the range <tt> 0 <= aclId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_RULE_ID - if \c ruleId is not in the range
 * <tt> 0 <= ruleId < </tt> \ref ncp_eioa_switch_acl_num_rules_get "ACL size "
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_ADDRESSES - if no more MAC addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_WILDCARD_ADDRESSES - if no more MAC addresses with ignore bits can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_MAC_WILDCARD_ADDRESS_PARTIAL_OVERLAP - if one
 * of the MAC wild card addresses partially overlaps with another MAC wild card
 * address
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IPv4_ADDRESSES - if no more IPv4 addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IP_ADDRESSES - if no more IP addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_IPv6_ADDRESS_IN_IPv4_MODE - if encountered an IPv6 address in IPv4 \ref ncp_eioa_switch_acl_ip_address_mode_t "mode"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_LAYER_4_PORTS - if no more Layer 4 ports can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_VLAN_ID - if 
 * \ref ncp_eioa_switch_acl_action_t::changeVlanId "action->changeVlanId" is 
 * \c TRUE and is invalid or
 * if any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids"
 * in rules has a non-zero \ref ncp_eioa_switch_acl_vlan_id_t::prefixLength "prefixLength" 
 * when \ref ncp_eioa_switch_acl_selection_mode_get "ACL selection" is based on 
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_VLAN_SELECTS "VLAN" or 
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_PORT_AND_VLAN_SELECTS "Port and VLAN"
 * or any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids" in
 * rules are invalid. A \ref ncp_eioa_switch_acl_vlan_id_t "rule VLAN Id" is 
 * invalid if either <tt> vlanId.prefixLength != 12 </tt> or 
 * <tt> vlanId.prefixLength != 0 </tt> or VLAN id value is not in the range 
 * <tt> 0 <= vlanId.value < 4096 </tt>. A 
 * \ref ncp_eioa_switch_acl_action_t::newVlanId "action VLAN Id" is invalid if
 * either <tt> vlanId.prefixLength != 12 </tt> or VLAN id value is not in the 
 * range <tt> 0 <= vlanId.value < 4096 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_POLICER_ID - if
 * \ref ncp_eioa_switch_acl_action_t::policerId "action->policerId"
 * is not in the range <tt> 0 <= action->policerId < 512 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_POLICER_MAP - if
 * \ref ncp_eioa_switch_acl_action_t::enablePolicing "action->enablePolicing" is
 * \c TRUE and
 * \ref ncp_eioa_switch_policer_mode_t "Policer selection" is not #NCP_EIOA_SWITCH_POLICER_MODE_ACL_RULE
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_DSCP - if any of the \ref ncp_eioa_switch_acl_rule_t2::dscpVals "DSCPs" in rule has
 * <tt> dscp->prefixLength != 6 </tt> or \c dscp->value is not in the range <tt> 0 <= dscp->value < 64 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_COS - if any of the \ref ncp_eioa_switch_acl_rule_t2::cosVals "COS values" in rule has <tt>cos.prefixLength != 3</tt>
 * or \c cos.value is not in the range <tt> 0 <= cos.value < 8 </tt>
 * <li> #NCP_ST_NO_MEMORY - if host memory allocation failed when modifying this rule in the in-memory ACL data structure
 * </ul>
 * @deprecated Used deprecated \ref ncp_eioa_switch_acl_rule_t. Use \ref ncp_eioa_switch_acl_modify2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_acl_modify2
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_modify(ncp_hdl_t ncpHdl, ncp_uint32_t aclId, ncp_uint32_t ruleId, const ncp_eioa_switch_acl_rule_t *rule, const ncp_eioa_switch_acl_action_t *action );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Modify a rule at the specified position in in-memory ACL data structure.
 * @details Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] aclId ACL with the ACL ID where this rule is to be added
 * @param[in] rule The rule that will be modified
 * @param[in] action The action associated with the rule to be modified
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c rule or \c action is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_ACL_ID - if \c aclId is not in the range <tt> 0 <= aclId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_RULE_ID - if \c ruleId is not in the range
 * <tt> 0 <= ruleId < </tt> \ref ncp_eioa_switch_acl_num_rules_get "ACL size "
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_ADDRESSES - if no more MAC addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_WILDCARD_ADDRESSES - if no more MAC addresses with ignore bits can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_MAC_WILDCARD_ADDRESS_PARTIAL_OVERLAP - if one
 * of the MAC wild card addresses partially overlaps with another MAC wild card
 * address
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IPv4_ADDRESSES - if no more IPv4 addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IP_ADDRESSES - if no more IP addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_IPv6_ADDRESS_IN_IPv4_MODE - if encountered an IPv6 address in IPv4 \ref ncp_eioa_switch_acl_ip_address_mode_t "mode"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_LAYER_4_PORTS - if no more Layer 4 ports can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_VLAN_ID - if
 * \ref ncp_eioa_switch_acl_action_t::changeVlanId "action->changeVlanId" is
 * \c TRUE and is invalid or
 * if any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids"
 * in rules has a non-zero \ref ncp_eioa_switch_acl_vlan_id_t::prefixLength "prefixLength"
 * when \ref ncp_eioa_switch_acl_selection_mode_get "ACL selection" is based on
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_VLAN_SELECTS "VLAN" or
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_PORT_AND_VLAN_SELECTS "Port and VLAN"
 * or any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids" in
 * rules are invalid. A \ref ncp_eioa_switch_acl_vlan_id_t "rule VLAN Id" is
 * invalid if either <tt> vlanId.prefixLength != 12 </tt> or
 * <tt> vlanId.prefixLength != 0 </tt> or VLAN id value is not in the range
 * <tt> 0 <= vlanId.value < 4096 </tt>. A
 * \ref ncp_eioa_switch_acl_action_t::newVlanId "action VLAN Id" is invalid if
 * either <tt> vlanId.prefixLength != 12 </tt> or VLAN id value is not in the
 * range <tt> 0 <= vlanId.value < 4096 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_POLICER_ID - if
 * \ref ncp_eioa_switch_acl_action_t::policerId "action->policerId"
 * is not in the range <tt> 0 <= action->policerId < 512 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_POLICER_MAP - if
 * \ref ncp_eioa_switch_acl_action_t::enablePolicing "action->enablePolicing" is
 * \c TRUE and
 * \ref ncp_eioa_switch_policer_mode_t "Policer selection" is not #NCP_EIOA_SWITCH_POLICER_MODE_ACL_RULE
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_DSCP - if any of the \ref ncp_eioa_switch_acl_rule_t2::dscpVals "DSCPs" in rule has
 * <tt> dscp->prefixLength != 6 </tt> or \c dscp->value is not in the range <tt> 0 <= dscp->value < 64 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_COS - if any of the \ref ncp_eioa_switch_acl_rule_t2::cosVals "COS values" in rule has <tt>cos.prefixLength != 3</tt>
 * or \c cos.value is not in the range <tt> 0 <= cos.value < 8 </tt>
 * <li> #NCP_ST_NO_MEMORY - if host memory allocation failed when modifying this rule in the in-memory ACL data structure
 * </ul>
 * @see ncp_eioa_switch_acl_num_rules_get
 * @see ncp_eioa_switch_acl_num_mac_addresses_get
 * @see ncp_eioa_switch_acl_num_mac_addresses_with_wildcards_get
 * @see ncp_eioa_switch_acl_num_ip_addresses_get
 * @see ncp_eioa_switch_acl_num_l4_ports_get
 * @see ncp_eioa_switch_acl_ip_address_mode_get
 * @see ncp_eioa_switch_policer_mode_get
 * @see ncp_eioa_switch_acl_selection_mode_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_modify2(ncp_hdl_t ncpHdl, ncp_uint32_t aclId, ncp_uint32_t ruleId, const ncp_eioa_switch_acl_rule_t2 *rule, const ncp_eioa_switch_acl_action_t *action );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Retrieves default action for specified ACL
 * @param[in] ncpHdl NCP handle
 * @param[in] aclId ACL id for which the default action to be retrieved
 * @param[out] action Default action
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c action is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_ACL_ID - if \c aclId is not in the range <tt> 0 <= aclId < 32 </tt>
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_default_action_get(ncp_hdl_t ncpHdl, ncp_uint32_t aclId, ncp_eioa_switch_acl_default_action_t *action );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Retrieves default action for specified ACL
 * @param[in] ncpHdl NCP handle
 * @param[out] action Default action
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c action is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_overall_default_action_get(ncp_hdl_t ncpHdl, ncp_eioa_switch_acl_default_action_t *action );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Sets default action for ACL specified in in-memory ACL data structure
 * @details Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] aclId ACL id for which the default action to be set
 * @param[in] action Default action
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c action is \c NULL or if 
 * \ref ncp_eioa_switch_acl_default_action_t::nonIpTrustMode 
 * "action->nonIpTrustMode" is set to value other than
 * #NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED or
 * #NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_COS
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_ACL_ID - if \c aclId is not in the range <tt> 0 <= aclId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_POLICER_ID - if
 * \ref ncp_eioa_switch_acl_default_action_t::ipPolicerId "action->ipPolicerId" 
 * is not in the range <tt> 0 <= action->ipPolicerId < 512 </tt> or
 * \ref ncp_eioa_switch_acl_default_action_t::nonIpPolicerId
 * "action->nonIpPolicerId" is not in the range
 * <tt> 0 <= action->nonIpPolicerId < 512 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_POLICER_MAP - if Policer selection is not #NCP_EIOA_SWITCH_POLICER_MODE_ACL_RULE and
 * \ref ncp_eioa_switch_acl_default_action_t::enableIpPolicing
 * "action->enableIpPolicing" is \c TRUE or
 * \ref ncp_eioa_switch_acl_default_action_t::enableNonIpPolicing
 * "action->enableNonIpPolicing" is \c TRUE
 * <li> #NCP_ST_NO_MEMORY - if host memory allocation failed when creating this default action in the in-memory ACL data structure
 * </ul>
 * @see ncp_eioa_switch_policer_mode_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_default_action_set(ncp_hdl_t ncpHdl, ncp_uint32_t aclId, const ncp_eioa_switch_acl_default_action_t *action );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Sets overall default action for ACL specified in in-memory ACL data structure
 * @details Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] action Default action
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c action is \c NULL or if
 * \ref ncp_eioa_switch_acl_default_action_t::nonIpTrustMode
 * "action->nonIpTrustMode" is set to value other than
 * #NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED or
 * #NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_COS
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_POLICER_ID - if
 * \ref ncp_eioa_switch_acl_default_action_t::ipPolicerId "action->ipPolicerId"
 * is not in the range <tt> 0 <= action->ipPolicerId < 512 </tt> or
 * \ref ncp_eioa_switch_acl_default_action_t::nonIpPolicerId
 * "action->nonIpPolicerId" is not in the range
 * <tt> 0 <= action->nonIpPolicerId < 512 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_POLICER_MAP - if Policer selection is not #NCP_EIOA_SWITCH_POLICER_MODE_ACL_RULE and
 * \ref ncp_eioa_switch_acl_default_action_t::enableIpPolicing
 * "action->enableIpPolicing" is \c TRUE or
 * \ref ncp_eioa_switch_acl_default_action_t::enableNonIpPolicing
 * "action->enableNonIpPolicing" is \c TRUE
 * <li> #NCP_ST_NO_MEMORY - if host memory allocation failed when creating this default action in the in-memory ACL data structure
 * </ul>
 * @see ncp_eioa_switch_policer_mode_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_overall_default_action_set(ncp_hdl_t ncpHdl, const ncp_eioa_switch_acl_default_action_t *action);

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Number of rules in the ACL
 * @details Retrieves number of rules in the ACL. All rules that have been added to the in-memory ACL data structure are also
 * counted.
 * @param[in] ncpHdl NCP handle
 * @param[in] aclId ACL with ACL ID for which the number of rules have to be retrieved
 * @param[out] numRules Number of rules in the ACL
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_ACL_ID - if \c aclId is not in the range <tt> 0 <= aclId < 32 </tt>
 * <li> #NCP_ST_INVALID_PARAMETER - if \c numRules is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_num_rules_get(ncp_hdl_t ncpHdl, ncp_uint32_t aclId, ncp_uint32_t *numRules );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Number of MAC addresses used across all ACLs and Routing tables
 * @details Retrieves number of source and destination MAC addresses used across all ACLs and Routing tables. All MAC addresses that have been
 * added to the in-memory ACL data structure are also counted.
 * @param[in] ncpHdl NCP handle
 * @param[out] numMacAddresses Number of MAC addresses used across all ACLs and Routing tables
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c numMacAddresses is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_num_mac_addresses_get( ncp_hdl_t ncpHdl, ncp_uint32_t *numMacAddresses );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Number of source MAC addresses used across all ACLs and Routing tables
 * @details Retrieves number of source MAC addresses used across all ACLs and Routing tables. All source MAC addresses that have been
 * added to the in-memory ACL data structure are also counted.
 * @param[in] ncpHdl NCP handle
 * @param[out] numSrcMacAddresses Number of source MAC addresses used across all ACLs and Routing tables
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c numMacAddresses is \c NULL
 * </ul>
 * @see ncp_eioa_switch_acl_num_src_mac_addresses_get
 * @see ncp_eioa_switch_acl_num_dest_mac_addresses_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_num_src_mac_addresses_get( ncp_hdl_t ncpHdl, ncp_uint32_t *numSrcMacAddresses );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Number of destination MAC addresses used across all ACLs and Routing tables
 * @details Retrieves number of destination MAC addresses used across all ACLs and Routing tables. All destination MAC addresses that have been
 * added to the in-memory ACL data structure are also counted.
 * @param[in] ncpHdl NCP handle
 * @param[out] numDestMacAddresses Number of destination MAC addresses used across all ACLs and Routing tables
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c numMacAddresses is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_num_dest_mac_addresses_get( ncp_hdl_t ncpHdl, ncp_uint32_t *numDestMacAddresses );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Number of destination MAC addresses used across all ACLs and Routing tables
 * @details Retrieves number of destination MAC addresses used across all ACLs and Routing tables. All destination MAC addresses that have been
 * added to the in-memory ACL data structure are also counted.
 * @param[in] ncpHdl NCP handle
 * @param[out] numMacAddresses Number of destination MAC addresses used across all ACLs and Routing tables
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c numMacAddresses is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_num_src_mac_addresses_get( ncp_hdl_t ncpHdl, ncp_uint32_t *numSrcMacAddresses );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Number of MAC addresses with wildcards used across all ACLs
 * @details Retrieves the number of source and destination MAC addresses with wildcards used across all ACLs. All MAC filter 
 * addresses that have been added to the in-memory ACL data structure are also counted.
 * @param[in] ncpHdl NCP handle
 * @param[out] numWildcardMacAddresses Number of MAC addresses with wildcards used across all ACLs
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c numMacWildcardAddresses is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_num_mac_addresses_with_wildcards_get( ncp_hdl_t ncpHdl, ncp_uint32_t *numWildcardMacAddresses );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Number of source MAC addresses with wildcards used across all ACLs and Routing tables
 * @details Retrieves the number of source MAC addresses with wildcards used across all ACLs and Routing tables. All MAC filter
 * addresses that have been added to the in-memory ACL data structure are also counted.
 * @param[in] ncpHdl NCP handle
 * @param[out] numWildcardMacAddresses Number of source MAC addresses with wildcards used across all ACLs and Routing tables
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c numMacWildcardAddresses is \c NULL
 * </ul>
 * @see ncp_eioa_switch_acl_num_src_mac_addresses_with_wildcards_get
 * @see ncp_eioa_switch_acl_num_dest_mac_addresses_with_wildcards_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_num_src_mac_addresses_with_wildcards_get( ncp_hdl_t ncpHdl, ncp_uint32_t *numWildcardSrcMacAddresses );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Number of destination MAC addresses with wildcards used across all ACLs and Routing tables
 * @details Retrieves the number of destination MAC addresses with wildcards used across all ACLs and Routing tables. All MAC filter
 * addresses that have been added to the in-memory ACL data structure are also counted.
 * @param[in] ncpHdl NCP handle
 * @param[out] numWildcardMacAddresses Number of destination MAC addresses with wildcards used across all ACLs and Routing tables
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c numMacWildcardAddresses is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_num_dest_mac_addresses_with_wildcards_get( ncp_hdl_t ncpHdl, ncp_uint32_t *numWildcardDestMacAddresses );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Number of IP addresses used across all ACLs and Routing tables
 * @details Retrieves number of source and destination IP addresses used across all ACLs and Routing tables. All IP addresses that have been
 * added to the in-memory ACL data structure are also counted.
 * @param[in] ncpHdl NCP handle
 * @param[out] numIpAddresses Number of IP addresses used across all ACLs and Routing tables
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c numIpAddresses is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_num_ip_addresses_get( ncp_hdl_t ncpHdl, ncp_uint32_t *numIpAddresses );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Number of source IP addresses used across all ACLs and Routing tables
 * @details Retrieves number of source IP addresses used across all ACLs and Routing tables. All IP addresses that have been
 * added to the in-memory ACL data structure are also counted.
 * @param[in] ncpHdl NCP handle
 * @param[out] numSrcIpAddresses Number of source IP addresses used across all ACLs and Routing tables
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c numIpAddresses is \c NULL
 * </ul>
 * @see ncp_eioa_switch_acl_num_src_ip_addresses_get
 * @see ncp_eioa_switch_acl_num_dest_ip_addresses_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_num_src_ip_addresses_get( ncp_hdl_t ncpHdl, ncp_uint32_t *numSrcIpAddresses );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Number of destination IP addresses used across all ACLs and Routing tables
 * @details Retrieves number of destination IP addresses used across all ACLs and Routing tables. All IP addresses that have been
 * added to the in-memory ACL data structure are also counted.
 * @param[in] ncpHdl NCP handle
 * @param[out] numDestIpAddresses Number of destination IP addresses used across all ACLs and Routing tables
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c numIpAddresses is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_num_dest_ip_addresses_get( ncp_hdl_t ncpHdl, ncp_uint32_t *numDestIpAddresses );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Number of Layer 4 ports used across all ACLs and Routing tables
 * @details Retrieves number of source and destination layer 4 ports used across all ACLs and Routing tables. All layer 4 ports that have been
 * added to the in-memory ACL data structure are also counted.
 * @param[in] ncpHdl NCP handle
 * @param[out] numL4Ports Number of layer 4 ports used across all ACLs and Routing tables
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c numL4Ports is \c NULL
 * </ul>
 * @see ncp_eioa_switch_acl_num_src_l4_ports_get
 * @see ncp_eioa_switch_acl_num_dest_l4_ports_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_num_l4_ports_get( ncp_hdl_t ncpHdl, ncp_uint32_t *numL4Ports );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Number of source Layer 4 ports used across all ACLs and Routing tables
 * @details Retrieves number of source layer 4 ports used across all ACLs and Routing tables. All layer 4 ports that have been
 * added to the in-memory ACL data structure are also counted.
 * @param[in] ncpHdl NCP handle
 * @param[out] numSrcL4Ports Number of source layer 4 ports used across all ACLs and Routing tables
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c numL4Ports is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_num_src_l4_ports_get( ncp_hdl_t ncpHdl, ncp_uint32_t *numSrcL4Ports );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Number of destination Layer 4 ports used across all ACLs and Routing tables
 * @details Retrieves number of destination layer 4 ports used across all ACLs and Routing tables. All layer 4 ports that have been
 * added to the in-memory ACL data structure are also counted.
 * @param[in] ncpHdl NCP handle
 * @param[out] numDestL4Ports Number of destination layer 4 ports used across all ACLs and Routing tables
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c numL4Ports is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_num_dest_l4_ports_get( ncp_hdl_t ncpHdl, ncp_uint32_t *numDestL4Ports );

/*!
 * @ingroup _eioa_switch_acl_
 * @typedef ncp_eioa_switch_acl_list_rules_fn_t
 * @brief EIOA Switch ACL list rules callback function declaration
 * @deprecated Uses deprecated \ref ncp_eioa_switch_acl_rule_t. Use \ref ncp_eioa_switch_acl_list_rules_fn_t2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_acl_list_rules_fn_t2
 */
typedef void (*ncp_eioa_switch_acl_list_rules_fn_t)(void *appData, ncp_uint32_t aclId, const ncp_eioa_switch_acl_rule_t *rule, const ncp_eioa_switch_acl_action_t *action );

/*!
 * @ingroup _eioa_switch_acl_
 * @typedef ncp_eioa_switch_acl_list_rules_fn_t2
 * @brief EIOA Switch ACL list entries callback function declaration
 */
typedef void (*ncp_eioa_switch_acl_list_rules_fn_t2)(void *appData, ncp_uint32_t aclId, const ncp_eioa_switch_acl_rule_t2 *rule, const ncp_eioa_switch_acl_action_t *action );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Lists all rules of specified ACL
 * @details For every rule of the specified ACL calls the callback function with the rule and the action
 * @param[in] ncpHdl NCP handle
 * @param[in] aclId ACL with ACL ID for which to list the rules from
 * @param[in] listfn Callback function to be called everytime a ACL rule is encountered
 * @param[in] appData Application specified data structure that is supplied to the callback function everytime the callback 
 * function is invoked
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_ACL_ID - if \c aclId is not in the range <tt> 0 <= aclId < 32 </tt>
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_list_rules_get2( ncp_hdl_t ncpHdl, ncp_uint32_t aclId, ncp_eioa_switch_acl_list_rules_fn_t2 listfn, void *appData );


/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Lists all rules of specified ACL
 * @details For every rule of the specified ACL calls the callback function with the rule and the action
 * @param[in] ncpHdl NCP handle
 * @param[in] aclId ACL with ACL ID for which to list the rules from
 * @param[in] listfn Callback function to be called everytime a ACL rule is encountered
 * @param[in] appData Application specified data structure that is supplied to the callback function everytime the callback
 * function is invoked
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_ACL_ID - if \c aclId is not in the range <tt> 0 <= aclId < 32 </tt>
 * </ul>
 * @deprecated Uses deprecated \ref ncp_eioa_switch_acl_list_rules_fn_t. Use
 * \ref ncp_eioa_switch_acl_list_rules_get2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_acl_list_rules_get2
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_list_rules_get( ncp_hdl_t ncpHdl, ncp_uint32_t aclId, ncp_eioa_switch_acl_list_rules_fn_t listfn, void *appData );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * EIOA Switch ACL IP address mode
 * @param[in] ncpHdl NCP handle
 * @param[out] mode IP address mode
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c mode is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_ip_address_mode_get( ncp_hdl_t ncpHdl, ncp_eioa_switch_acl_ip_address_mode_t *mode );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Uses the in-memory ACL data structure and commits the in-memory ACL data structure to hardware. 
 * @param[in] ncpHdl NCP handle
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_DSCP_COS_VALUES - if the number of DSCP and COS values exceed HW storage space.
 * Reducing the number of DSCP and COS value combinations  will eliminate this error
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MACSEC_ETHERTYPE_PROTOCOL_VALUES - if the number of MAC SEC (in AXM5500 and beyond), Ethertype and
 * Protocol combinations exceed HW storage space. Reducing the number of MAC SEC (in AXM5500 and beyond), Ethertype and Protocol combinations
 * will eliminate this error
 * <li> #NCP_ST_EIOA_SWITCH_ACL_UNSATISFIABLE_PORT_VLAN_TO_ACL_ID_COMBINATIONS- if port VLAN id to ACL 
 * id mappings are such that it cannot be fulfilled given the HW constraints on table sizes etc. 
 * Reducing the number of port VLAN id to ACL id mappings will eliminate this error.
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_build(ncp_hdl_t inHdl);

/*!
 * @ingroup _eioa_switch_acl_
 * @enum ncp_eioa_switch_acl_selection_mode_t
 * @brief EIOA Switch ACL selection mode
 * @details Specifies how an EIOA Switch ACL is selected. 
 */
typedef enum{
    NCP_EIOA_SWITCH_ACL_PORT_SELECTS		= 0, /*!< EIOA Core port that received the packet is used to determine the ACL to use */
    NCP_EIOA_SWITCH_ACL_VLAN_SELECTS		= 1, /*!< VLAN Id of the packet is used to determine the ACL to use */
    NCP_EIOA_SWITCH_ACL_PORT_AND_VLAN_SELECTS	= 2  /*!< Both EIOA Core port and VLAN Id of the packet is used to determine the ACL to use */
} ncp_eioa_switch_acl_selection_mode_t;

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Retrieves the EIOA Switch ACL selection mode
 * @param[in] ncpHdl NCP handle
 * @param[out] mode ACL selection mode
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c mode is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_selection_mode_get( ncp_hdl_t ncpHdl, ncp_eioa_switch_acl_selection_mode_t *mode );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Retrieves the ACL mapped to the specified port, vlan or port and vlan combination. 
 * @details If \ref ncp_eioa_switch_acl_selection_mode_t "ACL selection mode" is 
 * #NCP_EIOA_SWITCH_ACL_PORT_SELECTS only \c port is used to retrieve the 
 * corresponding ACL. If \ref ncp_eioa_switch_acl_selection_mode_t "ACL selection mode" is 
 * #NCP_EIOA_SWITCH_ACL_VLAN_SELECTS
 * only \c vlanId is used to retrieve the corresponding ACL. If \ref ncp_eioa_switch_acl_selection_mode_t "ACL slection mode" is
 * #NCP_EIOA_SWITCH_ACL_PORT_AND_VLAN_SELECTS then both \c port and \c vlanId are used
 * to retrieve the ACL
 * @param[in] ncpHdl NCP handle
 * @param[in] port EIOA port on which this packet has been received
 * @param[in] vlanId VLAN Id of the packet
 * @param[out] aclId The EIOA Switch ACL id to which either \c port, \c vlanId or both \c port and \c vlanId are mapped
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c aclId is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_VLAN_ID - 
 * if <tt> vlanId.prefixLength != 12 </tt> or \c vlanId.value does not fall in 
 * the range <tt> 0 <= vlanId < 4096 </tt> and
 * \ref ncp_eioa_switch_acl_selection_mode_t "ACL selection mode" is 
 * #NCP_EIOA_SWITCH_ACL_VLAN_SELECTS or #NCP_EIOA_SWITCH_ACL_PORT_AND_VLAN_SELECTS
 * </ul>
 * @see ncp_eioa_switch_acl_selection_mode_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_id_get( ncp_hdl_t ncpHdl, ncp_macChan_t port, ncp_eioa_switch_acl_vlan_id_t vlanId, ncp_uint32_t *aclId );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Maps the specified \c aclId to either \c port, \c vlanId, or both \c port and \c vlanId in in-memory ACL data structure
 * @details If \ref ncp_eioa_switch_acl_selection_mode_t "ACL selection mode" is 
 * #NCP_EIOA_SWITCH_ACL_PORT_SELECTS only \c port is mapped to \c aclId. If 
 * \ref ncp_eioa_switch_acl_selection_mode_t "ACL selection mode" is 
 * #NCP_EIOA_SWITCH_ACL_VLAN_SELECTS
 * only \c vlanId is mapped to \c aclId. If \ref ncp_eioa_switch_acl_selection_mode_t "ACL slection mode" is
 * #NCP_EIOA_SWITCH_ACL_PORT_AND_VLAN_SELECTS then both \c port and \c vlanId are 
 * mapped to \c aclId. The changes are made to in-memory ACL data structure. The same \c port, \c vlanId, or \c port and \c vlanId combination is used to select a policy based routing table. 
 * Hardware contents is not changed. To change hardware contents use \ref ncp_eioa_switch_acl_build
 * @param[in] ncpHdl NCP handle
 * @param[in] port EIOA port on which this packet has been received
 * @param[in] vlanId VLAN Id of the packet
 * @param[in] aclId The EIOA Switch ACL id to which either \c port, \c vlanId or both \c port and \c vlanId are to be mapped
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c aclId is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_ACL_ID - if \c aclId is not in the range <tt> 0 <= aclId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_VLAN_ID -
 * if <tt> vlanId.prefixLength != 12 </tt> or \c vlanId.value does not fall in 
 * the range <tt> 0 <= vlanId < 4096 </tt> and
 * \ref ncp_eioa_switch_acl_selection_mode_t "ACL selection mode" is 
 * #NCP_EIOA_SWITCH_ACL_VLAN_SELECTS or #NCP_EIOA_SWITCH_ACL_PORT_AND_VLAN_SELECTS
 * </ul>
 * @see ncp_eioa_switch_acl_selection_mode_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_id_set( ncp_hdl_t ncpHdl, ncp_macChan_t port, ncp_eioa_switch_acl_vlan_id_t vlanId, const ncp_uint32_t *aclId );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Retrieves the \c dscp mapped to the specified \c cos
 * @param[in] ncpHdl NCP handle
 * @param[in] cos COS value in the packet
 * @param[out] dscp DSCP value mapped to the specified \c cos
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c dscp is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_DSCP - if \c dscp is
 * invalid. An invalid DSCP is one where <tt> dscp->prefixLength != 6 </tt> or 
 * \c dscp->value is not in the range <tt> 0 <= dscp->value < 64 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_COS - if <tt>cos.prefixLength != 3</tt>
 * or \c cos.value is not in the range <tt> 0 <= cos.value < 8 </tt>
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_cos_to_dscp_map_get( ncp_hdl_t ncpHdl, ncp_eioa_switch_acl_cos_t cos, ncp_eioa_switch_acl_dscp_t *dscp );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Maps the \c dscp to the specified \c cos
 * @param[in] ncpHdl NCP handle
 * @param[in] cos COS value in the packet
 * @param[in] dscp DSCP value mapped to the specified \c cos
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c dscp is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_COS - if <tt>cos.prefixLength != 3</tt>
 * or \c cos.value is not in the range <tt> 0 <= cos.value < 8 </tt>
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_cos_to_dscp_map_set( ncp_hdl_t ncpHdl, ncp_eioa_switch_acl_cos_t cos, const ncp_eioa_switch_acl_dscp_t *dscp );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Retrieves the \c dscp mapped to the specified \c dscp
 * @param[in] ncpHdl NCP handle
 * @param[in] packetDscp DSCP value in the packet
 * @param[out] dscp DSCP value mapped to the specified \c dscp
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c dscp is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_DSCP - if 
 * <tt> packetDscp.prefixLength != 6 </tt> or \c packetDscp.value is not in the 
 * range <tt> 0 <= packetDscp.value < 64 </tt>
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_dscp_to_dscp_map_get( ncp_hdl_t ncpHdl, ncp_eioa_switch_acl_dscp_t packetDscp, ncp_eioa_switch_acl_dscp_t *dscp );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Maps the \c dscp to the specified \c dscp
 * @param[in] ncpHdl NCP handle
 * @param[in] packetDscp DSCP value in the packet
 * @param[in] dscp DSCP value mapped to the specified \c dscp
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c dscp is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_DSCP - if \c packetDscp or \c dscp is
 * invalid. An invalid DSCP is one where <tt> dscp->prefixLength != 6 </tt> or 
 * \c dscp->value is not in the range <tt> 0 <= dscp->value < 64 </tt>
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_dscp_to_dscp_map_set( ncp_hdl_t ncpHdl, ncp_eioa_switch_acl_dscp_t packetDscp, const ncp_eioa_switch_acl_dscp_t *dscp );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Retrieves the \c dscp mapped to the specified \c ipPrecedence
 * @param[in] ncpHdl NCP handle
 * @param[in] ipPrecedence IP Precedence value in the packet
 * @param[out] dscp DSCP value mapped to the specified \c ipPrecedence
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c dscp is \c NULL or if \c ipPrecedence value is not in the range <tt> 0 <= ipPrecedence < 8 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_DSCP - if <tt> dscp->prefixLength != 6
 * </tt> or \c dscp->value is not in the range <tt> 0 <= dscp->value < 8 </tt>
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_ip_precedence_to_dscp_map_get( ncp_hdl_t ncpHdl, ncp_eioa_switch_acl_ip_precedence_t ipPrecedence, ncp_eioa_switch_acl_dscp_t *dscp );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Maps the \c ipPrecedence to the specified \c dscp
 * @param[in] ncpHdl NCP handle
 * @param[in] ipPrecedence IP Precedence value in the packet
 * @param[in] dscp DSCP value mapped to the specified \c dscp
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c dscp is \c NULL or \c ipPrecedence 
 * value is not in the range <tt> 0 <= ipPrecedence < 8 </tt> 
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_DSCP - if <tt> dscp->prefixLength != 6
 * </tt> or \c dscp->value is not in the range <tt> 0 <= dscp->value < 8 </tt>
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_ip_precedence_to_dscp_map_set( ncp_hdl_t ncpHdl, ncp_eioa_switch_acl_ip_precedence_t ipPrecedence, const ncp_eioa_switch_acl_dscp_t *dscp );

/*!
 * @ingroup _eioa_switch_acl_
 * @typedef ncp_eioa_switch_acl_list_routes_fn_t
 * @brief EIOA Switch ACL list routes callback function declaration
 * @deprecated Uses deprecated \ref ncp_eioa_switch_acl_route_policy_t. Use \ref ncp_eioa_switch_acl_list_routes_fn_t2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_acl_list_routes_fn_t2
 */
typedef void (*ncp_eioa_switch_acl_list_routes_fn_t)(void *appData, ncp_uint32_t routingTable, const ncp_eioa_switch_acl_route_policy_t * policy, const ncp_eioa_switch_acl_route_action_t *route );

/*!
 * @ingroup _eioa_switch_acl_
 * @typedef ncp_eioa_switch_acl_list_routes_fn_t2
 * @brief EIOA Switch ACL list routes callback function declaration
 */
typedef void (*ncp_eioa_switch_acl_list_routes_fn_t2)(void *appData, ncp_uint32_t routingTable, const ncp_eioa_switch_acl_route_policy_t2 * policy, const ncp_eioa_switch_acl_route_action_t *route );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Lists all routes of specified routing table
 * @details For every route of the specified routing table calls the callback function with the route and the action
 * @param[in] ncpHdl NCP handle
 * @param[in] routingTable Routing table for which to list the routes from
 * @param[in] listfn Callback function to be called everytime a route is encountered
 * @param[in] appData Application specified data structure that is supplied to the callback function everytime the callback
 * function is invoked
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * </ul>
 * @deprecated Uses deprecated \ref ncp_eioa_switch_acl_list_routes_fn_t. Use \ref ncp_eioa_switch_acl_list_routes_get2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_acl_list_routes_get2
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_list_routes_get( ncp_hdl_t ncpHdl, ncp_uint32_t routingTable, ncp_eioa_switch_acl_list_routes_fn_t listfn, void *appData );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Lists all routes of specified routing table
 * @details For every route of the specified routing table calls the callback function with the route and the action
 * @param[in] ncpHdl NCP handle
 * @param[in] routingTable Routing table for which to list the routes from
 * @param[in] listfn Callback function to be called everytime a route is encountered
 * @param[in] appData Application specified data structure that is supplied to the callback function everytime the callback
 * function is invoked
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_list_routes_get2( ncp_hdl_t ncpHdl, ncp_uint32_t routingTable, ncp_eioa_switch_acl_list_routes_fn_t2 listfn, void *appData );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Deletes a IP destination address route associated with \c policy.
 * @details Unlike \ref ncp_eioa_switch_acl_route_get \c policy provided should exactly match one
 * of the routes in the routing table. None of the fields other than destIpAddress in \ref ncp_eioa_switch_acl_route_policy_t "policy" is used.
 * Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] policy Route matching this routing policy that will
 * be deleted
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c policy is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_UNKNOWN_ROUTE - if no route is found matching \c destIpAddress
 * <li> #NCP_ST_EIOA_SWITCH_ACL_IPv6_ADDRESS_IN_IPv4_MODE - if encountered an IPv6 address in IPv4 \ref ncp_eioa_switch_acl_ip_address_mode_t "mode"
 * </ul>
 * @deprecated Uses deprecated \ref ncp_eioa_switch_acl_route_policy_t. Use \ref ncp_eioa_switch_acl_route_delete2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_acl_route_delete2
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_route_delete( ncp_hdl_t ncpHdl, const ncp_eioa_switch_acl_route_policy_t *policy );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Deletes a IP destination address route associated with \c policy.
 * @details Unlike \ref ncp_eioa_switch_acl_route_get \c policy provided should exactly match one
 * of the routes in the routing table. None of the fields other than destIpAddress in \ref ncp_eioa_switch_acl_route_policy_t "policy" is used.
 * Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] policy Route matching this routing policy that will
 * be deleted
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c policy is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_UNKNOWN_ROUTE - if no route is found matching \c destIpAddress
 * <li> #NCP_ST_EIOA_SWITCH_ACL_IPv6_ADDRESS_IN_IPv4_MODE - if encountered an IPv6 address in IPv4 \ref ncp_eioa_switch_acl_ip_address_mode_t "mode"
 * </ul>
 * @see ncp_eioa_switch_acl_ip_address_mode_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_route_delete2( ncp_hdl_t ncpHdl, const ncp_eioa_switch_acl_route_policy_t2 *policy );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Modifies a IP destination address route associated with \ref ncp_eioa_switch_acl_route_policy_t
 * "policy->destIpAddress".
 * @details \c policy provided should exactly match one of the routes in the routing table.
 * None of the fields other than destIpAddress in \ref ncp_eioa_switch_acl_route_policy_t "policy" is used. Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] policy Route policy associated with the policy that is to be modified
 * @param[in] route New route
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c destIpAddress is \c NULL or \c route is \c NULL
 * <li> #NCP_ST_UNKNOWN_ROUTE - if no route is found matching \c destIpAddress
 * </ul>
 * @deprecated Uses deprecated \ref ncp_eioa_switch_acl_route_policy_t. Use \ref ncp_eioa_switch_acl_route_modify2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_acl_route_modify2
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_route_modify( ncp_hdl_t ncpHdl, const ncp_eioa_switch_acl_route_policy_t *policy, const ncp_eioa_switch_acl_route_action_t *route );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Modifies a IP destination address route associated with \ref ncp_eioa_switch_acl_route_policy_t
 * "policy->destIpAddress".
 * @details \c policy provided should exactly match one of the routes in the routing table.
 * None of the fields other than destIpAddress in \ref ncp_eioa_switch_acl_route_policy_t "policy" is used. Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] policy Route policy associated with the policy that is to be modified
 * @param[in] route New route
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c destIpAddress is \c NULL or \c route is \c NULL
 * <li> #NCP_ST_UNKNOWN_ROUTE - if no route is found matching \c destIpAddress
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_route_modify2( ncp_hdl_t ncpHdl, const ncp_eioa_switch_acl_route_policy_t2 *policy, const ncp_eioa_switch_acl_route_action_t *route );
/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Number of routes specified
 * @details Retrieves number of unique routes specified. This number includes all
 * routes that have been added to the in-memory ACL data structure as well as
 * the default route. Therefore, the number of routes will at the minimum be 1
 * because default route is always present. A unique route is one that has a unique
 * \ref ncp_eioa_switch_acl_pbr_route_action_t2::actionId "action id" or unique combination of
 * \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "destVpsIndex" and \ref ncp_eioa_switch_acl_route_action_t::routingIndex "routingIndex".
 * A unique route is included in this count
 * if \ref ncp_eioa_switch_acl_pbr_route_action_t2::routingAction "routing action" is \ref ncp_eioa_switch_acl_pbr_route_action_t2::useRoutingAction "used" or
 * if \ref ncp_eioa_switch_acl_pbr_route_action_t2::routingAction "bridging action" is \ref ncp_eioa_switch_acl_pbr_route_action_t2::useBridgingAction "used" or
 * if \ref ncp_eioa_switch_acl_pbr_route_action_t2::actionId "action id" is \ref ncp_eioa_switch_acl_pbr_route_action_t2::useActionIdInTask "used" or
 * if the route was a IP destination address route.
 * @param[in] ncpHdl NCP handle
 * @param[out] numRoutes Number of routes
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c numRoutes is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_num_routes_get( ncp_hdl_t ncpHdl, ncp_uint32_t *numRoutes );


/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Adds a IP destination address route associated with \ref ncp_eioa_switch_acl_route_policy_t
 * "policy->destIpAddress"
 * @details None of the other fields in \ref ncp_eioa_switch_acl_route_policy_t "policy" is used. Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] policy Routing policy to select the new route
 * @param[in] route New route to add
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c destIpAddress is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_ROUTE_INVALID_SUB_INTERFACE - if \ref ncp_eioa_switch_acl_route_action_t::destinationVpsIndex "destination VP index" does not reach a \ref ncp_eioa_switch_acl_action_t::subinterfaces "subinterface"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_ROUTES - If no more routes can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IP_ADDRESSES - if no more routes can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_IPv6_ADDRESS_IN_IPv4_MODE - if encountered an IPv6 address in IPv4 \ref ncp_eioa_switch_acl_ip_address_mode_t "mode"
 * <li> #NCP_ST_NO_MEMORY - if host memory allocation failed when adding this route in the in-memory ACL data structure
 * </ul>
 * @deprecated Uses deprecated \ref ncp_eioa_switch_acl_route_policy_t. Use \ref ncp_eioa_switch_acl_route_add2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_acl_route_add2
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_route_add( ncp_hdl_t ncpHdl, const ncp_eioa_switch_acl_route_policy_t *policy, const ncp_eioa_switch_acl_route_action_t *route );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Adds a IP destination address route associated with \ref ncp_eioa_switch_acl_route_policy_t
 * "policy->destIpAddress"
 * @details None of the other fields in \ref ncp_eioa_switch_acl_route_policy_t "policy" is used. Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] policy Routing policy to select the new route
 * @param[in] route New route to add
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c destIpAddress is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_ROUTE_INVALID_SUB_INTERFACE - if \ref ncp_eioa_switch_acl_route_action_t::destinationVpsIndex "destination VP index" does not reach a \ref ncp_eioa_switch_acl_action_t::subinterfaces "subinterface"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_ROUTES - If no more routes can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IP_ADDRESSES - if no more routes can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_IPv6_ADDRESS_IN_IPv4_MODE - if encountered an IPv6 address in IPv4 \ref ncp_eioa_switch_acl_ip_address_mode_t "mode"
 * <li> #NCP_ST_NO_MEMORY - if host memory allocation failed when adding this route in the in-memory ACL data structure
 * </ul>
 * @see ncp_eioa_switch_acl_ip_address_mode_get
 * @see ncp_eioa_switch_acl_num_ip_addresses_get
 * @see ncp_eioa_switch_acl_num_routes_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_route_add2( ncp_hdl_t ncpHdl, const ncp_eioa_switch_acl_route_policy_t2 *policy, const ncp_eioa_switch_acl_route_action_t *route );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Retrieves router MAC Address
 * @param[in] ncpHdl NCP handle
 * @param[out] routerMacAddress Router MAC address to retrieve
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c routerMacAddress is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_router_mac_address_get( ncp_hdl_t ncpHdl, ncp_eioa_switch_acl_mac_addr_t *routerMacAddress );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Sets router MAC Address
 * @param[in] ncpHdl NCP handle
 * @param[out] routerMacAddress New router MAC address
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c routerMacAddress is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_router_mac_address_set( ncp_hdl_t ncpHdl, const ncp_eioa_switch_acl_mac_addr_t *macAddress );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief Retrieves port configuration used by ACL
 * @param[in] ncpHdl NCP handle
 * @param[in] port Port for which ACL configuration needs to be retrieved
 * @param[out] cfg ACL port configuration
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c cfg is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_port_cfg_get(ncp_hdl_t ncpHdl, ncp_macChan_t port, ncp_eioa_switch_acl_port_cfg_t *cfg);

/*!
 * @ingroup _eioa_switch_acl_
 * @brief Sets port configuration used by ACL.
 * @param[in] ncpHdl NCP handle
 * @param[in] port Port for which ACL configuration needs to be retrieved
 * @param[in] cfg ACL port configuration
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c cfg is \c NULL
 * </ul>
 */

NCP_API ncp_st_t
ncp_eioa_switch_acl_port_cfg_set(ncp_hdl_t ncpHdl, ncp_macChan_t port, const ncp_eioa_switch_acl_port_cfg_t *cfg);

/*!
 * @ingroup _eioa_switch_acl_
 * @brief Retrieves port trust configuration used by ACL
 * @param[in] ncpHdl NCP handle
 * @param[in] port Port for which ACL configuration needs to be retrieved
 * @param[out] cfg ACL port trust configuration
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c cfg is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_port_trust_cfg_get(ncp_hdl_t ncpHdl, ncp_macChan_t port, ncp_eioa_switch_acl_port_trust_cfg_t *cfg);

/*!
 * @ingroup _eioa_switch_acl_
 * @brief Sets port trust configuration used by ACL.
 * @param[in] ncpHdl NCP handle
 * @param[in] port Port for which ACL configuration needs to be retrieved
 * @param[in] cfg ACL port trust configuration
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c cfg is \c NULL
 * </ul>
 */

NCP_API ncp_st_t
ncp_eioa_switch_acl_port_trust_cfg_set(ncp_hdl_t ncpHdl, ncp_macChan_t port, const ncp_eioa_switch_acl_port_trust_cfg_t *cfg);
/*!
 * @ingroup _eioa_switch_acl_
 * @brief Deletes all policy based routing rules from in-memory ACL data structure.
 * @details Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] pbrId Policy based routing table with PBR ID to be cleared
 * @return 
 * <ul>
 * <li> #NCP_ST_SUCCESS - if API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_PBR_ID - if \c pbrId is not in the range <tt> 0 <= pbrId < 32 </tt>
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_pbr_clear(ncp_hdl_t ncpHdl, ncp_uint32_t pbrId );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Adds a rule as the first rule in policy based routing table to in-memory ACL data structure.
 * @details This is the same as invoking \ref ncp_eioa_switch_acl_pbr_insert with
 * \c ruleId as 0. Shifts the rule currently at first position (if any) and
 * any subsequent rules down (adds one to their \c ruleId).
 * Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] pbrId Policy based routing table with the PBR ID where this rule is to be added
 * @param[in] rule PBR rule to be prepended
 * @param[in] action The action associated with the rule to be added
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c rule or \c action is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_PBR_ID - if \c pbrId is not in the range <tt> 0 <= pbrId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_RULES - if the number of rules in an PBR exceeds the maximum number of rules allowed
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_ADDRESSES - if no more MAC addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_WILDCARD_ADDRESSES - if no more MAC addresses with ignore bits can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_MAC_WILDCARD_ADDRESS_PARTIAL_OVERLAP - if one
 * of the MAC wild card addresses partially overlaps with another MAC wild card
 * address
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IPv4_ADDRESSES - if no more IPv4 addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IP_ADDRESSES - if no more IP addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_IPv6_ADDRESS_IN_IPv4_MODE - if encountered an IPv6 address in IPv4 \ref ncp_eioa_switch_acl_ip_address_mode_t "mode"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_LAYER_4_PORTS - if no more Layer 4 ports can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_ACTION_ID_CLASH - if \ref ncp_eioa_switch_acl_pbr_route_action_t::useActionIdInTask "action->useActionIdInTask" is set and
 * \ref ncp_eioa_switch_acl_pbr_route_action_t::useRoutingAction "action->useRoutingAction" is set and \ref ncp_eioa_switch_acl_pbr_route_action_t::actionId "action->actionId" is used by another route that does not have the same
 * \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "action->routingAction.destVpsIndex" and
 * \ref ncp_eioa_switch_acl_route_action_t::routingIndex "action->routingAction.routingIndex" combination
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_ROUTES - if the number of routes exceed the maximum number of routes permitted. The total number of routes
 * is sum of unique number of \ref ncp_eioa_switch_acl_pbr_route_action_t::actionId "actionIds"
 * \ref ncp_eioa_switch_acl_pbr_route_action_t::useActionIdInTask "used in tasks" and unique number of
 * \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "destVpsIndex" and \ref ncp_eioa_switch_acl_route_action_t::routingIndex "routingIndex combination
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_VLAN_ID - 
 * if any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids"
 * in rules has a non-zero \ref ncp_eioa_switch_acl_vlan_id_t::prefixLength "prefixLength" 
 * when \ref ncp_eioa_switch_acl_selection_mode_get "PBR selection" is based on 
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_VLAN_SELECTS "VLAN" or 
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_PORT_AND_VLAN_SELECTS "Port and VLAN"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_DSCP - if any of the \ref ncp_eioa_switch_acl_rule_t2::dscpVals "DSCPs" in rule has
 * <tt> dscp->prefixLength != 6 </tt> or \c dscp->value is not in the range <tt> 0 <= dscp->value < 64 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_COS - if any of the \ref ncp_eioa_switch_acl_rule_t2::cosVals "COS values" in rule has <tt>cos.prefixLength != 3</tt>
 * or \c cos.value is not in the range <tt> 0 <= cos.value < 8 </tt>
 * <li> #NCP_ST_NO_MEMORY - if host memory allocation failed when modifying this rule in the in-memory ACL data structure
 * </ul>
 * @deprecated Uses deprecated \ref ncp_eioa_switch_acl_route_policy_t and \ref ncp_eioa_switch_acl_route_action_t. Use \ref ncp_eioa_switch_acl_pbr_prepend2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_acl_pbr_prepend2
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_pbr_prepend(ncp_hdl_t ncpHdl, ncp_uint32_t pbrId, const ncp_eioa_switch_acl_route_policy_t *rule, const ncp_eioa_switch_acl_pbr_route_action_t *action );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Adds a rule as the first rule in policy based routing table to in-memory ACL data structure.
 * @details This is the same as invoking \ref ncp_eioa_switch_acl_pbr_insert with
 * \c ruleId as 0. Shifts the rule currently at first position (if any) and
 * any subsequent rules down (adds one to their \c ruleId).
 * Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] pbrId Policy based routing table with the PBR ID where this rule is to be added
 * @param[in] rule PBR rule to be prepended
 * @param[in] action The action associated with the rule to be added
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c rule or \c action is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_PBR_ID - if \c pbrId is not in the range <tt> 0 <= pbrId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_RULES - if the number of rules in an PBR exceeds the maximum number of rules allowed
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_ADDRESSES - if no more MAC addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_WILDCARD_ADDRESSES - if no more MAC addresses with ignore bits can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_MAC_WILDCARD_ADDRESS_PARTIAL_OVERLAP - if one
 * of the MAC wild card addresses partially overlaps with another MAC wild card
 * address
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IPv4_ADDRESSES - if no more IPv4 addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IP_ADDRESSES - if no more IP addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_IPv6_ADDRESS_IN_IPv4_MODE - if encountered an IPv6 address in IPv4 \ref ncp_eioa_switch_acl_ip_address_mode_t "mode"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_LAYER_4_PORTS - if no more Layer 4 ports can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_ACTION_ID_CLASH - if \ref ncp_eioa_switch_acl_pbr_route_action_t2::useActionIdInTask "action->useActionIdInTask" is set and
 * \ref ncp_eioa_switch_acl_pbr_route_action_t2::useRoutingAction "action->useRoutingAction" is set and \ref ncp_eioa_switch_acl_pbr_route_action_t2::actionId "action->actionId" is used by another route that does not have the same
 * \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "action->routingAction.destVpsIndex" and
 * \ref ncp_eioa_switch_acl_route_action_t::routingIndex "action->routingAction.routingIndex" combination
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_ROUTES - if the number of routes exceed the maximum number of routes permitted. The total number of routes
 * is sum of unique number of \ref ncp_eioa_switch_acl_pbr_route_action_t2::actionId "actionIds"
 * \ref ncp_eioa_switch_acl_pbr_route_action_t2::useActionIdInTask "used in tasks" and unique number of
 * \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "destVpsIndex" and \ref ncp_eioa_switch_acl_route_action_t::routingIndex "routingIndex combination
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_VLAN_ID -
 * if any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids"
 * in rules has a non-zero \ref ncp_eioa_switch_acl_vlan_id_t::prefixLength "prefixLength"
 * when \ref ncp_eioa_switch_acl_selection_mode_get "PBR selection" is based on
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_VLAN_SELECTS "VLAN" or
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_PORT_AND_VLAN_SELECTS "Port and VLAN"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_DSCP - if any of the \ref ncp_eioa_switch_acl_rule_t2::dscpVals "DSCPs" in rule has
 * <tt> dscp->prefixLength != 6 </tt> or \c dscp->value is not in the range <tt> 0 <= dscp->value < 64 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_COS - if any of the \ref ncp_eioa_switch_acl_rule_t2::cosVals "COS values" in rule has <tt>cos.prefixLength != 3</tt>
 * or \c cos.value is not in the range <tt> 0 <= cos.value < 8 </tt>
 * <li> #NCP_ST_NO_MEMORY - if host memory allocation failed when modifying this rule in the in-memory ACL data structure
 * </ul>
 * @see ncp_eioa_switch_acl_pbr_insert
 * @see ncp_eioa_switch_acl_pbr_num_rules_get
 * @see ncp_eioa_switch_acl_num_mac_addresses_get
 * @see ncp_eioa_switch_acl_num_mac_addresses_with_wildcards_get
 * @see ncp_eioa_switch_acl_num_ip_addresses_get
 * @see ncp_eioa_switch_acl_num_l4_ports_get
 * @see ncp_eioa_switch_acl_ip_address_mode_get
 * @see ncp_eioa_switch_acl_num_routes_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_pbr_prepend2(ncp_hdl_t ncpHdl, ncp_uint32_t pbrId, const ncp_eioa_switch_acl_route_policy_t2 *rule, const ncp_eioa_switch_acl_pbr_route_action_t2 *action );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Adds a rule as the last rule to policy based routing table to in-memory ACL data structure.
 * @details Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] pbrId PBR with the PBR ID where this rule is to be added
 * @param[in] rule PBR rule to append
 * @param[in] action The action associated with the rule to be added
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c rule or \c action is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_PBR_ID - if \c pbrId is not in the range <tt> 0 <= pbrId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_RULES - if the number of rules in an PBR exceeds the maximum number of rules allowed
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_ADDRESSES - if no more MAC addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_WILDCARD_ADDRESSES - if no more MAC addresses with ignore bits can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_MAC_WILDCARD_ADDRESS_PARTIAL_OVERLAP - if one
 * of the MAC wild card addresses partially overlaps with another MAC wild card
 * address
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IPv4_ADDRESSES - if no more IPv4 addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IP_ADDRESSES - if no more IP addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_IPv6_ADDRESS_IN_IPv4_MODE - if encountered an IPv6 address in IPv4 \ref ncp_eioa_switch_acl_ip_address_mode_t "mode"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_LAYER_4_PORTS - if no more Layer 4 ports can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_ACTION_ID_CLASH - if \ref ncp_eioa_switch_acl_pbr_route_action_t::useActionIdInTask "action->useActionIdInTask" is set and
 * \ref ncp_eioa_switch_acl_pbr_route_action_t::useRoutingAction "action->useRoutingAction" is set and \ref ncp_eioa_switch_acl_pbr_route_action_t::actionId "action->actionId" is used by another route that does not have the same
 * \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "action->routingAction.destVpsIndex" and
 * \ref ncp_eioa_switch_acl_route_action_t::routingIndex "action->routingAction.routingIndex" combination
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_ROUTES - if the number of routes exceed the maximum number of routes permitted. The total number of routes
 * is sum of unique number of \ref ncp_eioa_switch_acl_pbr_route_action_t::actionId "actionIds"
 * \ref ncp_eioa_switch_acl_pbr_route_action_t::useActionIdInTask "used in tasks" and unique number of
 * \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "destVpsIndex" and \ref ncp_eioa_switch_acl_route_action_t::routingIndex "routingIndex combination
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_VLAN_ID - 
 * if any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids"
 * in rules has a non-zero \ref ncp_eioa_switch_acl_vlan_id_t::prefixLength "prefixLength" 
 * when \ref ncp_eioa_switch_acl_selection_mode_get "PBR selection" is based on 
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_VLAN_SELECTS "VLAN" or 
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_PORT_AND_VLAN_SELECTS "Port and VLAN"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_DSCP - if any of the \ref ncp_eioa_switch_acl_rule_t2::dscpVals "DSCPs" in rule has
 * <tt> dscp->prefixLength != 6 </tt> or \c dscp->value is not in the range <tt> 0 <= dscp->value < 64 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_COS - if any of the \ref ncp_eioa_switch_acl_rule_t2::cosVals "COS values" in rule has <tt>cos.prefixLength != 3</tt>
 * or \c cos.value is not in the range <tt> 0 <= cos.value < 8 </tt>
 * <li> #NCP_ST_NO_MEMORY - if host memory allocation failed when creating this rule in the in-memory ACL data structure
 * </ul>
 * @deprecated Uses deprecated \ref ncp_eioa_switch_acl_route_policy_t and \ref ncp_eioa_switch_acl_route_action_t. Use \ref ncp_eioa_switch_acl_pbr_append2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_acl_pbr_append2
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_pbr_append(ncp_hdl_t ncpHdl, ncp_uint32_t pbrId, const ncp_eioa_switch_acl_route_policy_t *rule, const ncp_eioa_switch_acl_pbr_route_action_t *action );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Adds a rule as the last rule to policy based routing table to in-memory ACL data structure.
 * @details Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] pbrId PBR with the PBR ID where this rule is to be added
 * @param[in] rule PBR rule to append
 * @param[in] action The action associated with the rule to be added
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c rule or \c action is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_PBR_ID - if \c pbrId is not in the range <tt> 0 <= pbrId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_RULES - if the number of rules in an PBR exceeds the maximum number of rules allowed
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_ADDRESSES - if no more MAC addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_WILDCARD_ADDRESSES - if no more MAC addresses with ignore bits can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_MAC_WILDCARD_ADDRESS_PARTIAL_OVERLAP - if one
 * of the MAC wild card addresses partially overlaps with another MAC wild card
 * address
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IPv4_ADDRESSES - if no more IPv4 addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IP_ADDRESSES - if no more IP addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_IPv6_ADDRESS_IN_IPv4_MODE - if encountered an IPv6 address in IPv4 \ref ncp_eioa_switch_acl_ip_address_mode_t "mode"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_LAYER_4_PORTS - if no more Layer 4 ports can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_ACTION_ID_CLASH - if \ref ncp_eioa_switch_acl_pbr_route_action_t2::useActionIdInTask "action->useActionIdInTask" is set and
 * \ref ncp_eioa_switch_acl_pbr_route_action_t2::useRoutingAction "action->useRoutingAction" is set and \ref ncp_eioa_switch_acl_pbr_route_action_t2::actionId "action->actionId" is used by another route that does not have the same
 * \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "action->routingAction.destVpsIndex" and
 * \ref ncp_eioa_switch_acl_route_action_t::routingIndex "action->routingAction.routingIndex" combination
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_ROUTES - if the number of routes exceed the maximum number of routes permitted. The total number of routes
 * is sum of unique number of \ref ncp_eioa_switch_acl_pbr_route_action_t2::actionId "actionIds"
 * \ref ncp_eioa_switch_acl_pbr_route_action_t2::useActionIdInTask "used in tasks" and unique number of
 * \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "destVpsIndex" and \ref ncp_eioa_switch_acl_route_action_t::routingIndex "routingIndex combination
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_VLAN_ID -
 * if any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids"
 * in rules has a non-zero \ref ncp_eioa_switch_acl_vlan_id_t::prefixLength "prefixLength"
 * when \ref ncp_eioa_switch_acl_selection_mode_get "PBR selection" is based on
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_VLAN_SELECTS "VLAN" or
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_PORT_AND_VLAN_SELECTS "Port and VLAN"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_DSCP - if any of the \ref ncp_eioa_switch_acl_rule_t2::dscpVals "DSCPs" in rule has
 * <tt> dscp->prefixLength != 6 </tt> or \c dscp->value is not in the range <tt> 0 <= dscp->value < 64 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_COS - if any of the \ref ncp_eioa_switch_acl_rule_t2::cosVals "COS values" in rule has <tt>cos.prefixLength != 3</tt>
 * or \c cos.value is not in the range <tt> 0 <= cos.value < 8 </tt>
 * <li> #NCP_ST_NO_MEMORY - if host memory allocation failed when creating this rule in the in-memory ACL data structure
 * </ul>
 * @see ncp_eioa_switch_acl_id_get
 * @see ncp_eioa_switch_acl_pbr_num_rules_get
 * @see ncp_eioa_switch_acl_num_mac_addresses_get
 * @see ncp_eioa_switch_acl_num_mac_addresses_with_wildcards_get
 * @see ncp_eioa_switch_acl_num_ip_addresses_get
 * @see ncp_eioa_switch_acl_ip_address_mode_get
 * @see ncp_eioa_switch_acl_num_l4_ports_get
 * @see ncp_eioa_switch_acl_num_routes_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_pbr_append2(ncp_hdl_t ncpHdl, ncp_uint32_t pbrId, const ncp_eioa_switch_acl_route_policy_t2 *rule, const ncp_eioa_switch_acl_pbr_route_action_t2 *action );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Inserts a rule at the specified position to policy based routing table to in-memory ACL data structure.
 * @details Shifts the rule currently at \c ruleId position (if any) and any
 * subsequent rules down (adds one to their \c ruleId).
 * Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] pbrId PBR with the PBR ID where this rule is to be added
 * @param[in] ruleId PBR rule id at which the specified rule will be added
 * @param[in] rule PBR rule to insert
 * @param[in] action The action associated with the rule to be added
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c rule or \c action is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_PBR_ID - if \c pbrId is not in the range <tt> 0 <= pbrId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_RULES - if the number of rules in an PBR exceeds the maximum number of rules allowed
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_RULE_ID - if \c ruleId is not in
 * the range <tt> 0 <= ruleId <= </tt> \ref ncp_eioa_switch_acl_pbr_num_rules_get "PBR size "
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_ADDRESSES - if no more MAC addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_WILDCARD_ADDRESSES - if no more MAC addresses with ignore bits can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_MAC_WILDCARD_ADDRESS_PARTIAL_OVERLAP - if one
 * of the MAC wild card addresses partially overlaps with another MAC wild card
 * address
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IPv4_ADDRESSES - if no more IPv4 addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IP_ADDRESSES - if no more IP addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_IPv6_ADDRESS_IN_IPv4_MODE - if encountered an IPv6 address in IPv4 \ref ncp_eioa_switch_acl_ip_address_mode_t "mode"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_LAYER_4_PORTS - if no more Layer 4 ports can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_ACTION_ID_CLASH - if \ref ncp_eioa_switch_acl_pbr_route_action_t::useActionIdInTask "action->useActionIdInTask" is set and
 * \ref ncp_eioa_switch_acl_pbr_route_action_t::useRoutingAction "action->useRoutingAction" is set and \ref ncp_eioa_switch_acl_pbr_route_action_t::actionId "action->actionId" is used by another route that does not have the same
 * \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "action->routingAction.destVpsIndex" and
 * \ref ncp_eioa_switch_acl_route_action_t::routingIndex "action->routingAction.routingIndex" combination
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_ROUTES - if the number of routes exceed the maximum number of routes permitted. The total number of routes
 * is sum of unique number of \ref ncp_eioa_switch_acl_pbr_route_action_t::actionId "actionIds"
 * \ref ncp_eioa_switch_acl_pbr_route_action_t::useActionIdInTask "used in tasks" and unique number of
 * \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "destVpsIndex" and \ref ncp_eioa_switch_acl_route_action_t::routingIndex "routingIndex combination
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_VLAN_ID - 
 * if any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids"
 * in rules has a non-zero \ref ncp_eioa_switch_acl_vlan_id_t::prefixLength "prefixLength" 
 * when \ref ncp_eioa_switch_acl_selection_mode_get "PBR selection" is based on 
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_VLAN_SELECTS "VLAN" or 
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_PORT_AND_VLAN_SELECTS "Port and VLAN"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_DSCP - if any of the \ref ncp_eioa_switch_acl_rule_t2::dscpVals "DSCPs" in rule has
 * <tt> dscp->prefixLength != 6 </tt> or \c dscp->value is not in the range <tt> 0 <= dscp->value < 64 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_COS - if any of the \ref ncp_eioa_switch_acl_rule_t2::cosVals "COS values" in rule has <tt>cos.prefixLength != 3</tt>
 * or \c cos.value is not in the range <tt> 0 <= cos.value < 8 </tt>
 * <li> #NCP_ST_NO_MEMORY - if host memory allocation failed when creating this rule in the in-memory ACL data structure
 * </ul>
 * @deprecated Uses deprecated \ref ncp_eioa_switch_acl_route_policy_t and \ref ncp_eioa_switch_acl_route_action_t. Use \ref ncp_eioa_switch_acl_pbr_insert2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_acl_pbr_insert2
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_pbr_insert(ncp_hdl_t ncpHdl, ncp_uint32_t pbrId, ncp_uint32_t ruleId, const ncp_eioa_switch_acl_route_policy_t *rule, const ncp_eioa_switch_acl_pbr_route_action_t *action );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Inserts a rule at the specified position to policy based routing table to in-memory ACL data structure.
 * @details Shifts the rule currently at \c ruleId position (if any) and any
 * subsequent rules down (adds one to their \c ruleId).
 * Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] pbrId PBR with the PBR ID where this rule is to be added
 * @param[in] ruleId PBR rule id at which the specified rule will be added
 * @param[in] rule PBR rule to insert
 * @param[in] action The action associated with the rule to be added
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c rule or \c action is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_PBR_ID - if \c pbrId is not in the range <tt> 0 <= pbrId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_RULES - if the number of rules in an PBR exceeds the maximum number of rules allowed
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_RULE_ID - if \c ruleId is not in
 * the range <tt> 0 <= ruleId <= </tt> \ref ncp_eioa_switch_acl_pbr_num_rules_get "PBR size "
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_ADDRESSES - if no more MAC addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_WILDCARD_ADDRESSES - if no more MAC addresses with ignore bits can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_MAC_WILDCARD_ADDRESS_PARTIAL_OVERLAP - if one
 * of the MAC wild card addresses partially overlaps with another MAC wild card
 * address
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IPv4_ADDRESSES - if no more IPv4 addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IP_ADDRESSES - if no more IP addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_IPv6_ADDRESS_IN_IPv4_MODE - if encountered an IPv6 address in IPv4 \ref ncp_eioa_switch_acl_ip_address_mode_t "mode"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_LAYER_4_PORTS - if no more Layer 4 ports can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_ACTION_ID_CLASH - if \ref ncp_eioa_switch_acl_pbr_route_action_t2::useActionIdInTask "action->useActionIdInTask" is set and
 * \ref ncp_eioa_switch_acl_pbr_route_action_t2::useRoutingAction "action->useRoutingAction" is set and \ref ncp_eioa_switch_acl_pbr_route_action_t2::actionId "action->actionId" is used by another route that does not have the same
 * \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "action->routingAction.destVpsIndex" and
 * \ref ncp_eioa_switch_acl_route_action_t::routingIndex "action->routingAction.routingIndex" combination
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_ROUTES - if the number of routes exceed the maximum number of routes permitted. The total number of routes
 * is sum of unique number of \ref ncp_eioa_switch_acl_pbr_route_action_t2::actionId "actionIds"
 * \ref ncp_eioa_switch_acl_pbr_route_action_t2::useActionIdInTask "used in tasks" and unique number of
 * \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "destVpsIndex" and \ref ncp_eioa_switch_acl_route_action_t::routingIndex "routingIndex combination
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_VLAN_ID -
 * if any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids"
 * in rules has a non-zero \ref ncp_eioa_switch_acl_vlan_id_t::prefixLength "prefixLength"
 * when \ref ncp_eioa_switch_acl_selection_mode_get "PBR selection" is based on
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_VLAN_SELECTS "VLAN" or
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_PORT_AND_VLAN_SELECTS "Port and VLAN"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_DSCP - if any of the \ref ncp_eioa_switch_acl_rule_t2::dscpVals "DSCPs" in rule has
 * <tt> dscp->prefixLength != 6 </tt> or \c dscp->value is not in the range <tt> 0 <= dscp->value < 64 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_COS - if any of the \ref ncp_eioa_switch_acl_rule_t2::cosVals "COS values" in rule has <tt>cos.prefixLength != 3</tt>
 * or \c cos.value is not in the range <tt> 0 <= cos.value < 8 </tt>
 * <li> #NCP_ST_NO_MEMORY - if host memory allocation failed when creating this rule in the in-memory ACL data structure
 * </ul>
 * @see ncp_eioa_switch_acl_id_get
 * @see ncp_eioa_switch_acl_pbr_num_rules_get
 * @see ncp_eioa_switch_acl_num_mac_addresses_get
 * @see ncp_eioa_switch_acl_num_mac_addresses_with_wildcards_get
 * @see ncp_eioa_switch_acl_num_ip_addresses_get
 * @see ncp_eioa_switch_acl_num_l4_ports_get
 * @see ncp_eioa_switch_acl_ip_address_mode_get
 * @see ncp_eioa_switch_acl_num_routes_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_pbr_insert2(ncp_hdl_t ncpHdl, ncp_uint32_t pbrId, ncp_uint32_t ruleId, const ncp_eioa_switch_acl_route_policy_t2 *rule, const ncp_eioa_switch_acl_pbr_route_action_t2 *action );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Deletes a rule from policy based routing table at the specified position from in-memory ACL data structure.
 * @details Shifts any subsequent rules up 
 * (substracts one from their \c ruleId).
 * Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] pbrId PBR with the PBR ID where this rule is to be added
 * @param[in] ruleId PBR rule id to delete
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_PBR_ID - if \c pbrId is not in the range <tt> 0 <= pbrId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_RULE_ID - if \c ruleId is not in the range
 * <tt> 0 <= ruleId < </tt> \ref ncp_eioa_switch_acl_pbr_num_rules_get "PBR size "
 * </ul>
 * @see ncp_eioa_switch_acl_id_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_pbr_delete(ncp_hdl_t ncpHdl, ncp_uint32_t pbrId, ncp_uint32_t ruleId );

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Modify a rule in policy based routing table at the specified position in in-memory ACL data structure.
 * @details Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] pbrId PBR with the PBR ID where this rule is to be added
 * @param[in] rule The rule that will be modified
 * @param[in] action The action associated with the rule to be modified
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c rule or \c action is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_PBR_ID - if \c pbrId is not in the range <tt> 0 <= pbrId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_RULE_ID - if \c ruleId is not in the range
 * <tt> 0 <= ruleId < </tt> \ref ncp_eioa_switch_acl_pbr_num_rules_get "PBR size "
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_ADDRESSES - if no more MAC addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_WILDCARD_ADDRESSES - if no more MAC addresses with ignore bits can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_MAC_WILDCARD_ADDRESS_PARTIAL_OVERLAP - if one
 * of the MAC wild card addresses partially overlaps with another MAC wild card
 * address
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IPv4_ADDRESSES - if no more IPv4 addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IP_ADDRESSES - if no more IP addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_IPv6_ADDRESS_IN_IPv4_MODE - if encountered an IPv6 address in IPv4 \ref ncp_eioa_switch_acl_ip_address_mode_t "mode"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_LAYER_4_PORTS - if no more Layer 4 ports can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_ACTION_ID_CLASH -if \ref ncp_eioa_switch_acl_pbr_route_action_t::useActionIdInTask "action->useActionIdInTask" is set and
 * \ref ncp_eioa_switch_acl_pbr_route_action_t::useRoutingAction "action->useRoutingAction" is set and \ref ncp_eioa_switch_acl_pbr_route_action_t::actionId "action->actionId" is used by another route that does not have the same
 * \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "action->routingAction.destVpsIndex" and
 * \ref ncp_eioa_switch_acl_route_action_t::routingIndex "action->routingAction.routingIndex" combination
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_ROUTES - if the number of routes exceed the maximum number of routes permitted. The total number of routes
 * is sum of unique number of \ref ncp_eioa_switch_acl_pbr_route_action_t::actionId "actionIds"
 * \ref ncp_eioa_switch_acl_pbr_route_action_t::useActionIdInTask "used in tasks" and unique number of
 * \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "destVpsIndex" and \ref ncp_eioa_switch_acl_route_action_t::routingIndex "routingIndex combination
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_VLAN_ID - 
 * if any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids"
 * in rules has a non-zero \ref ncp_eioa_switch_acl_vlan_id_t::prefixLength "prefixLength" 
 * when \ref ncp_eioa_switch_acl_selection_mode_get "PBR selection" is based on 
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_VLAN_SELECTS "VLAN" or 
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_PORT_AND_VLAN_SELECTS "Port and VLAN"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_DSCP - if any of the \ref ncp_eioa_switch_acl_rule_t2::dscpVals "DSCPs" in rule has
 * <tt> dscp->prefixLength != 6 </tt> or \c dscp->value is not in the range <tt> 0 <= dscp->value < 64 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_COS - if any of the \ref ncp_eioa_switch_acl_rule_t2::cosVals "COS values" in rule has <tt>cos.prefixLength != 3</tt>
 * or \c cos.value is not in the range <tt> 0 <= cos.value < 8 </tt>
 * <li> #NCP_ST_NO_MEMORY - if host memory allocation failed when modifying this rule in the in-memory ACL data structure
 * </ul>
 * @deprecated Uses deprecated \ref ncp_eioa_switch_acl_route_policy_t and \ref ncp_eioa_switch_acl_route_action_t. Use \ref ncp_eioa_switch_acl_pbr_modify2 instead.
 * @since 1.3.0
 * @see ncp_eioa_switch_acl_pbr_modify2
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_pbr_modify(ncp_hdl_t ncpHdl, ncp_uint32_t pbrId, ncp_uint32_t ruleId, const ncp_eioa_switch_acl_route_policy_t *rule, const ncp_eioa_switch_acl_pbr_route_action_t *action );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Modify a rule in policy based routing table at the specified position in in-memory ACL data structure.
 * @details Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] pbrId PBR with the PBR ID where this rule is to be added
 * @param[in] rule The rule that will be modified
 * @param[in] action The action associated with the rule to be modified
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c rule or \c action is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_PBR_ID - if \c pbrId is not in the range <tt> 0 <= pbrId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_RULE_ID - if \c ruleId is not in the range
 * <tt> 0 <= ruleId < </tt> \ref ncp_eioa_switch_acl_pbr_num_rules_get "PBR size "
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_ADDRESSES - if no more MAC addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_WILDCARD_ADDRESSES - if no more MAC addresses with ignore bits can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_MAC_WILDCARD_ADDRESS_PARTIAL_OVERLAP - if one
 * of the MAC wild card addresses partially overlaps with another MAC wild card
 * address
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IPv4_ADDRESSES - if no more IPv4 addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IP_ADDRESSES - if no more IP addresses can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_IPv6_ADDRESS_IN_IPv4_MODE - if encountered an IPv6 address in IPv4 \ref ncp_eioa_switch_acl_ip_address_mode_t "mode"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_LAYER_4_PORTS - if no more Layer 4 ports can be added
 * <li> #NCP_ST_EIOA_SWITCH_ACL_ACTION_ID_CLASH -if \ref ncp_eioa_switch_acl_pbr_route_action_t2::useActionIdInTask "action->useActionIdInTask" is set and
 * \ref ncp_eioa_switch_acl_pbr_route_action_t2::useRoutingAction "action->useRoutingAction" is set and \ref ncp_eioa_switch_acl_pbr_route_action_t2::actionId "action->actionId" is used by another route that does not have the same
 * \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "action->routingAction.destVpsIndex" and
 * \ref ncp_eioa_switch_acl_route_action_t::routingIndex "action->routingAction.routingIndex" combination
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_ROUTES - if the number of routes exceed the maximum number of routes permitted. The total number of routes
 * is sum of unique number of \ref ncp_eioa_switch_acl_pbr_route_action_t2::actionId "actionIds"
 * \ref ncp_eioa_switch_acl_pbr_route_action_t2::useActionIdInTask "used in tasks" and unique number of
 * \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "destVpsIndex" and \ref ncp_eioa_switch_acl_route_action_t::routingIndex "routingIndex combination
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_VLAN_ID -
 * if any of the \ref ncp_eioa_switch_acl_rule_t2::vlanIdVals "VLAN Ids"
 * in rules has a non-zero \ref ncp_eioa_switch_acl_vlan_id_t::prefixLength "prefixLength"
 * when \ref ncp_eioa_switch_acl_selection_mode_get "PBR selection" is based on
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_VLAN_SELECTS "VLAN" or
 * \ref ncp_eioa_switch_acl_selection_mode_t::NCP_EIOA_SWITCH_ACL_PORT_AND_VLAN_SELECTS "Port and VLAN"
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_DSCP - if any of the \ref ncp_eioa_switch_acl_rule_t2::dscpVals "DSCPs" in rule has
 * <tt> dscp->prefixLength != 6 </tt> or \c dscp->value is not in the range <tt> 0 <= dscp->value < 64 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_INVALID_COS - if any of the \ref ncp_eioa_switch_acl_rule_t2::cosVals "COS values" in rule has <tt>cos.prefixLength != 3</tt>
 * or \c cos.value is not in the range <tt> 0 <= cos.value < 8 </tt>
 * <li> #NCP_ST_NO_MEMORY - if host memory allocation failed when modifying this rule in the in-memory ACL data structure
 * </ul>
 * @see ncp_eioa_switch_acl_id_get
 * @see ncp_eioa_switch_acl_pbr_num_rules_get
 * @see ncp_eioa_switch_acl_num_mac_addresses_get
 * @see ncp_eioa_switch_acl_num_mac_addresses_with_wildcards_get
 * @see ncp_eioa_switch_acl_num_ip_addresses_get
 * @see ncp_eioa_switch_acl_num_l4_ports_get
 * @see ncp_eioa_switch_acl_ip_address_mode_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_pbr_modify2(ncp_hdl_t ncpHdl, ncp_uint32_t pbrId, ncp_uint32_t ruleId, const ncp_eioa_switch_acl_route_policy_t2 *rule, const ncp_eioa_switch_acl_pbr_route_action_t2 *action );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Retrieves default action for specified ACL
 * @param[in] ncpHdl NCP handle
 * @param[out] action Default action
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c action is \c NULL
 * </ul>
 * @deprecated Uses deprecated \ref ncp_eioa_switch_acl_route_action_t. Use \ref ncp_eioa_switch_acl_pbr_overall_default_action_get2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_acl_pbr_overall_default_action_get2
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_pbr_overall_default_action_get(ncp_hdl_t ncpHdl, ncp_eioa_switch_acl_pbr_route_action_t *action );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Sets overall default action for all policy based routing tables in in-memory ACL data structure
 * @details Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] action Default action
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c action is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_ACTION_ID_CLASH -if \ref ncp_eioa_switch_acl_pbr_route_action_t2::useActionIdInTask "action->useActionIdInTask" is set and
 * \ref ncp_eioa_switch_acl_pbr_route_action_t2::useRoutingAction "action->useRoutingAction" is set and \ref ncp_eioa_switch_acl_pbr_route_action_t2::actionId "action->actionId" is used by another route that does not have the same
 * \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "action->routingAction.destVpsIndex" and
 * \ref ncp_eioa_switch_acl_route_action_t::routingIndex "action->routingAction.routingIndex" combination
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_ROUTES - if the number of routes exceed the maximum number of routes permitted. The total number of routes
 * is sum of unique number of \ref ncp_eioa_switch_acl_pbr_route_action_t2::actionId "actionIds"
 * \ref ncp_eioa_switch_acl_pbr_route_action_t2::useActionIdInTask "used in tasks" and unique number of
 * \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "destVpsIndex" and \ref ncp_eioa_switch_acl_route_action_t::routingIndex "routingIndex combination
 * <li> #NCP_ST_NO_MEMORY - if host memory allocation failed when creating this default action in the in-memory ACL data structure
 * </ul>
 * @deprecated Uses deprecated \ref ncp_eioa_switch_acl_route_action_t. Use \ref ncp_eioa_switch_acl_pbr_overall_default_action_set2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_acl_pbr_overall_default_action_set2
 * @see ncp_eioa_switch_acl_num_routes_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_pbr_overall_default_action_set(ncp_hdl_t ncpHdl, const ncp_eioa_switch_acl_pbr_route_action_t *action);

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Retrieves default action for specified ACL
 * @param[in] ncpHdl NCP handle
 * @param[out] action Default action
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c action is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_pbr_overall_default_action_get2(ncp_hdl_t ncpHdl, ncp_eioa_switch_acl_pbr_route_action_t2 *action );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Sets overall default action for all policy based routing tables in in-memory ACL data structure
 * @details Hardware contents are not affected. To change hardware contents use \ref ncp_eioa_switch_acl_build.
 * @param[in] ncpHdl NCP handle
 * @param[in] action Default action
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c action is \c NULL
 * <li> #NCP_ST_EIOA_SWITCH_ACL_ACTION_ID_CLASH -if \ref ncp_eioa_switch_acl_pbr_route_action_t2::useActionIdInTask "action->useActionIdInTask" is set and
 * \ref ncp_eioa_switch_acl_pbr_route_action_t2::useRoutingAction "action->useRoutingAction" is set and \ref ncp_eioa_switch_acl_pbr_route_action_t2::actionId "action->actionId" is used by another route that does not have the same
 * \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "action->routingAction.destVpsIndex" and
 * \ref ncp_eioa_switch_acl_route_action_t::routingIndex "action->routingAction.routingIndex" combination
 * <li> #NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_ROUTES - if the number of routes exceed the maximum number of routes permitted. The total number of routes
 * is sum of unique number of \ref ncp_eioa_switch_acl_pbr_route_action_t2::actionId "actionIds"
 * \ref ncp_eioa_switch_acl_pbr_route_action_t2::useActionIdInTask "used in tasks" and unique number of
 * \ref ncp_eioa_switch_acl_route_action_t::destVpsIndex "destVpsIndex" and \ref ncp_eioa_switch_acl_route_action_t::routingIndex "routingIndex combination
 * <li> #NCP_ST_NO_MEMORY - if host memory allocation failed when creating this default action in the in-memory ACL data structure
 * </ul>
 * @see ncp_eioa_switch_acl_num_routes_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_pbr_overall_default_action_set2(ncp_hdl_t ncpHdl, const ncp_eioa_switch_acl_pbr_route_action_t2 *action);

/*! 
 * @ingroup _eioa_switch_acl_
 * @brief
 * Number of rules in the policy based routing table
 * @details Retrieves number of rules in the PBR. All rules that have been added to the in-memory ACL data structure are also
 * counted.
 * @param[in] ncpHdl NCP handle
 * @param[in] pbrId PBR with PBR ID for which the number of rules have to be retrieved
 * @param[out] numRules Number of rules in the PBR
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_PBR_ID - if \c pbrId is not in the range <tt> 0 <= pbrId < 32 </tt>
 * <li> #NCP_ST_INVALID_PARAMETER - if \c numRules is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_pbr_num_rules_get(ncp_hdl_t ncpHdl, ncp_uint32_t pbrId, ncp_uint32_t *numRules );

/*!
 * @ingroup _eioa_switch_acl_
 * @brief Retrieves number of times the overall ACL default action or per ACL default action has been used
 * @param[in] ncpHdl NCP handle
 * @param[out] count Number of times the default rule has been used
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c count is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_count_default_match_get(ncp_hdl_t ncpHdl, ncp_uint64_t *count);

/*!
 * @ingroup _eioa_switch_acl_
 * @brief Reset the number of times the overall ACL default action or per ACL default action has been used
 * @param[in] ncpHdl NCP handle
 * @param[in] count Reset value
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c count is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_count_default_match_set(ncp_hdl_t ncpHdl, const ncp_uint64_t *count);

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Retrieves number of times the specified ACL rule has been used
 * @param[in] ncpHdl NCP handle
 * @param[in] aclId ACL id that contains the rule for which the count is to be retrieved
 * @param[in] ruleId in the ACL for which the count is to be retrieved
 * @param[out] count Number of times the action associated with this rule has been used
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_ACL_ID - if \c aclId is not in the range <tt> 0 <= aclId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_RULE_ID - if \c ruleId is not in the range
 * <tt> 0 <= ruleId < </tt> \ref ncp_eioa_switch_acl_num_rules_get "ACL size "
 * <li> #NCP_ST_INVALID_PARAMETER - if \c count is \c NULL
 * </ul>
 * @see ncp_eioa_switch_acl_num_rules_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_count_rule_match_get(ncp_hdl_t ncpHdl, ncp_uint32_t aclId, ncp_uint32_t ruleId, ncp_uint64_t *count);

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Reset the count of number of times the specified ACL rule has been used
 * @param[in] ncpHdl NCP handle
 * @param[in] aclId ACL id that contains the rule for which the count is to be set
 * @param[in] ruleId in the ACL for which the count is to be set
 * @param[in] count Reset value
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_ACL_ID - if \c aclId is not in the range <tt> 0 <= aclId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_RULE_ID - if \c ruleId is not in the range
 * <tt> 0 <= ruleId < </tt> \ref ncp_eioa_switch_acl_num_rules_get "ACL size "
 * <li> #NCP_ST_INVALID_PARAMETER - if \c count is \c NULL
 * </ul>
 * @see ncp_eioa_switch_acl_num_rules_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_count_rule_match_set(ncp_hdl_t ncpHdl, ncp_uint32_t aclId, ncp_uint32_t ruleId, const ncp_uint64_t *count);

/*!
 * @ingroup _eioa_switch_acl_
 * @brief Retrieves number of times the overall PBR default action has been used
 * @param[in] ncpHdl NCP handle
 * @param[out] count Number of times the default rule has been used
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c count is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_pbr_count_default_match_get(ncp_hdl_t ncpHdl, ncp_uint64_t *count);

/*!
 * @ingroup _eioa_switch_acl_
 * @brief Reset the number of times the overall PBR default action has been used
 * @param[in] ncpHdl NCP handle
 * @param[in] count Reset value
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - if \c count is \c NULL
 * </ul>
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_pbr_count_default_match_set(ncp_hdl_t ncpHdl, const ncp_uint64_t *count);

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Retrieves number of times the specified PBR rule has been used
 * @param[in] ncpHdl NCP handle
 * @param[in] pbrId PBR id that contains the rule for which the count is to be retrieved
 * @param[in] ruleId in the PBR for which the count is to be retrieved
 * @param[out] count Number of times the action associated with this rule has been used
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_PBR_ID - if \c pbrId is not in the range <tt> 0 <= pbrId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_RULE_ID - if \c ruleId is not in the range
 * <tt> 0 <= ruleId < </tt> \ref ncp_eioa_switch_acl_pbr_num_rules_get "PBR size "
 * <li> #NCP_ST_INVALID_PARAMETER - if \c count is \c NULL
 * </ul>
 * @see ncp_eioa_switch_acl_pbr_num_rules_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_pbr_count_rule_match_get(ncp_hdl_t ncpHdl, ncp_uint32_t pbrId, ncp_uint32_t ruleId, ncp_uint64_t *count);

/*!
 * @ingroup _eioa_switch_acl_
 * @brief
 * Reset the count of number of times the specified PBR rule has been used
 * @param[in] ncpHdl NCP handle
 * @param[in] pbrId PBR id that contains the rule for which the count is to be set
 * @param[in] ruleId in the PBR for which the count is to be set
 * @param[in] count Reset value
 * @return
 * <ul>
 * <li> #NCP_ST_SUCCESS - if the API succeeds
 * <li> #NCP_ST_INVALID_HANDLE - if \c ncpHdl is invalid
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_PBR_ID - if \c pbrId is not in the range <tt> 0 <= pbrId < 32 </tt>
 * <li> #NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_RULE_ID - if \c ruleId is not in the range
 * <tt> 0 <= ruleId < </tt> \ref ncp_eioa_switch_acl_pbr_num_rules_get "PBR size "
 * <li> #NCP_ST_INVALID_PARAMETER - if \c count is \c NULL
 * </ul>
 * @see ncp_eioa_switch_acl_pbr_num_rules_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_acl_pbr_count_rule_match_set(ncp_hdl_t ncpHdl, ncp_uint32_t pbrId, ncp_uint32_t ruleId, const ncp_uint64_t *count);


#ifdef __cplusplus
}
#endif

#endif /* #ifndef _NCP_EIOA_SWITCH_ACL_H_ */

