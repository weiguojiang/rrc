/*********************************************************************
*
* (C) Copyright Broadcom Corporation 2013-2014
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
**********************************************************************
*
* @filename   ind_ofdpa_fwd.c
*
* @purpose    OF-DPA Driver for Indigo
*
* @component  OF-DPA
*
* @comments   none
*
* @create     6 Nov 2013
*
* @end
*
**********************************************************************/

#include <unistd.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <stdbool.h>
#include <pthread.h>
#include <errno.h>
#include "ind_ofdpa_util.h"
#include "indigo/memory.h"
#include "indigo/forwarding.h"
#include "ind_ofdpa_log.h"
#include "indigo/of_state_manager.h"
#include "indigo/fi.h"
#include "OFStateManager/ofstatemanager.h"


ind_ofdpa_fields_t ind_ofdpa_match_fields_bitmask;

static indigo_error_t ind_ofdpa_packet_out_actions_get(of_list_action_t *of_list_actions, 
                                                       indPacketOutActions_t *packetOutActions);
static indigo_error_t ind_ofdpa_match_fields_masks_get(const of_match_t *match, ofdpaFlowEntry_t *flow);
static indigo_error_t ind_ofdpa_translate_openflow_actions(of_list_action_t *actions, ofdpaFlowEntry_t *flow);

extern int ofagent_of_version;

/*
 * Build up a record of all the match fields included in the flow_mod message. This is used to detect when the message
 * contains a match field that is not supported by the flow table. The agent is required to reject flows that request
 * a match that the switch cannot support.
 */
static void ind_ofdpa_populate_flow_bitmask(const of_match_t *match, ind_ofdpa_fields_t *ind_ofdpa_match_fields_bitmask)
{
  of_mac_addr_t macAddr;
  of_ipv6_t     ipAddr;

  *ind_ofdpa_match_fields_bitmask = 0;

  if (match->masks.vlan_vid != 0)
  {
    (*ind_ofdpa_match_fields_bitmask) |= IND_OFDPA_VLANID;
  }

  memset(&macAddr, 0, sizeof(macAddr));

  if ((memcmp(&match->masks.eth_src, &macAddr, sizeof(match->masks.eth_src))) != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_SRCMAC;
  }

  if ((memcmp(&match->masks.eth_dst, &macAddr, sizeof(match->masks.eth_dst))) != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_DSTMAC;
  }

  if ((match->masks.in_port != 0) ||(match->masks.in_phy_port != 0))
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_PORT;
  }

  if (match->masks.eth_type != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_ETHER_TYPE;
  }

  if (match->masks.ipv4_dst != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_IPV4_DST;
  }

  if (match->masks.ipv4_src != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_IPV4_SRC;
  }

  memset(&ipAddr, 0, sizeof(ipAddr));

  if ((memcmp(&match->masks.ipv6_dst, &ipAddr, sizeof(match->masks.ipv6_dst))) != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_IPV6_DST;
  }

  if ((memcmp(&match->masks.ipv6_src, &ipAddr, sizeof(match->masks.ipv6_src))) != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_IPV6_SRC;
  }

  if (match->masks.tunnel_id != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_TUNNEL_ID;
  }

  if (match->masks.vlan_pcp != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_VLAN_PCP;
  }
/*
  if (match->masks.ofdpa_dei != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_VLAN_DEI;
  }
*/
  if (match->masks.arp_spa != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_IPV4_ARP_SPA;
  }

  if (match->masks.ip_dscp != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_IP_DSCP;
  }

  if (match->masks.ip_ecn != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_IP_ECN;
  }

  if (match->masks.ip_proto != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_IP_PROTO;
  }

  if (match->masks.tcp_src != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_TCP_L4_SRC_PORT;
  }

  if (match->masks.tcp_dst != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_TCP_L4_DST_PORT;
  }

  if (match->masks.udp_src != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_UDP_L4_SRC_PORT;
  }

  if (match->masks.udp_dst != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_UDP_L4_DST_PORT;
  }

  if (match->masks.sctp_src != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_SCTP_L4_SRC_PORT;
  }

  if (match->masks.sctp_dst != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_SCTP_L4_DST_PORT;
  }

  if (match->masks.icmpv4_type != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_ICMPV4_TYPE;
  }

  if (match->masks.icmpv4_code != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_ICMPV4_CODE;
  }

  if (match->masks.ipv6_flabel != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_IPV6_FLOW_LABEL;
  }

  if (match->masks.icmpv6_type != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_ICMPV6_TYPE;
  }

  if (match->masks.icmpv6_code != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_ICMPV6_CODE;
  }
/*
  if (match->masks.mpls_label != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_MPLS_LABEL;
  }
  if (match->masks.mpls_bos != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_MPLS_BOS;
  }
  if (match->masks.mpls_tc != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_MPLS_TC;
  }
  if (match->masks.ofdpa_mpls_l2_port != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_MPLS_L2_PORT;
  }
  if (match->masks.ofdpa_ovid != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_OVID;
  }
  if (match->masks.ofdpa_vrf != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_VRF;
  }
  if (match->masks.ofdpa_qos_index != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_QOS_INDEX;
  }
  if (match->masks.ofdpa_lmep_id != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_LMEP_ID;
  }
  if (match->masks.ofdpa_mpls_ttl != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_MPLS_TTL;
  }
  if (match->masks.ofdpa_bfd_discriminator != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_BFD_DISCRIMINATOR;
  }
  if (match->masks.ofdpa_mpls_data_first_nibble != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_MPLS_DATA_FIRST_NIBBLE;
  }
  if (match->masks.ofdpa_mpls_ach_channel != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_MPLS_ACH_CHANNEL;
  }
  if (match->masks.ofdpa_mpls_next_label_is_gal != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_MPLS_NEXT_LABEL_IS_GAL;
  }
  if (match->masks.ofdpa_oam_y1731_mdl != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_OAM_Y1731_MDL;
  }
  if (match->masks.ofdpa_oam_y1731_opcode != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_OAM_Y1731_OPCODE;
  }
  if (match->masks.ofdpa_color_actions_index != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_COLOR_ACTIONS_INDEX;
  }
  if (match->masks.ofdpa_txfcl != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_TXFCL;
  }
  if (match->masks.ofdpa_rxfcl != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_RXFCL;
  }
  if (match->masks.ofdpa_rx_timestamp != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_RX_TIMESTAMP;
  }
  if (match->masks.ofdpa_l3_in_port != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_L3_IN_PORT;
  }
  if (match->masks.ofdpa_protection_index != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_PROTECTION_INDEX;
  }
  if (match->masks.ofdpa_color != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_COLOR;
  }
  if (match->masks.ofdpa_traffic_class != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_TC;
  }
  if (match->masks.ofdpa_allow_vlan_translation != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_OFDPA_ALLOW_VLAN_TRANSLATION;
  }
  if (match->masks.onf_actset_output != 0)
  {
    *ind_ofdpa_match_fields_bitmask |= IND_ONF_ACTSET_OUTPUT;
  }
*/  
  LOG_TRACE("match_fields_bitmask is 0x%llX", *ind_ofdpa_match_fields_bitmask);
}

/* Get the flow match criteria from of_match */

static indigo_error_t ind_ofdpa_match_fields_masks_get(const of_match_t *match, ofdpaFlowEntry_t *flow)
{
  indigo_error_t err = INDIGO_ERROR_NONE;
  ind_ofdpa_fields_t ind_ofdpa_match_fields_bitmask;

  ind_ofdpa_populate_flow_bitmask(match, &ind_ofdpa_match_fields_bitmask);
#if 0
  switch (flow->tableId)
  {
    case OFDPA_FLOW_TABLE_ID_ACL_POLICY:
      if ((ind_ofdpa_match_fields_bitmask| IND_OFDPA_ACL_POLICY_FLOW_MATCH_BITMAP) != IND_OFDPA_ACL_POLICY_FLOW_MATCH_BITMAP)
      {
        err = INDIGO_ERROR_COMPAT;
      }
      else
      {
        flow->flowData.policyAclFlowEntry.match_criteria.inPort         = match->fields.in_port;
        flow->flowData.policyAclFlowEntry.match_criteria.inPortMask     = match->masks.in_port;
        flow->flowData.policyAclFlowEntry.match_criteria.mplsL2Port     = match->fields.ofdpa_mpls_l2_port;
        flow->flowData.policyAclFlowEntry.match_criteria.mplsL2PortMask = match->masks.ofdpa_mpls_l2_port;

        memcpy(flow->flowData.policyAclFlowEntry.match_criteria.srcMac.addr, &match->fields.eth_src, OF_MAC_ADDR_BYTES);
        memcpy(flow->flowData.policyAclFlowEntry.match_criteria.srcMacMask.addr, &match->masks.eth_src, OF_MAC_ADDR_BYTES);
        memcpy(flow->flowData.policyAclFlowEntry.match_criteria.destMac.addr, &match->fields.eth_dst, OF_MAC_ADDR_BYTES);
        memcpy(flow->flowData.policyAclFlowEntry.match_criteria.destMacMask.addr, &match->masks.eth_dst, OF_MAC_ADDR_BYTES);

        flow->flowData.policyAclFlowEntry.match_criteria.etherType     = match->fields.eth_type;
        flow->flowData.policyAclFlowEntry.match_criteria.etherTypeMask = match->masks.eth_type;
        flow->flowData.policyAclFlowEntry.match_criteria.vlanId        = match->fields.vlan_vid;
        flow->flowData.policyAclFlowEntry.match_criteria.vlanIdMask    = match->masks.vlan_vid & (OFDPA_VID_PRESENT | OFDPA_VID_EXACT_MASK);
        flow->flowData.policyAclFlowEntry.match_criteria.vlanPcp       = match->fields.vlan_pcp;
        flow->flowData.policyAclFlowEntry.match_criteria.vlanPcpMask   = match->masks.vlan_pcp;
        flow->flowData.policyAclFlowEntry.match_criteria.vlanDei       = match->fields.ofdpa_dei;
        flow->flowData.policyAclFlowEntry.match_criteria.vlanDeiMask   = match->masks.ofdpa_dei;
        flow->flowData.policyAclFlowEntry.match_criteria.tunnelId      = match->fields.tunnel_id;
        flow->flowData.policyAclFlowEntry.match_criteria.tunnelIdMask  = match->masks.tunnel_id;
        flow->flowData.policyAclFlowEntry.match_criteria.vrf           = match->fields.ofdpa_vrf;
        flow->flowData.policyAclFlowEntry.match_criteria.vrfMask       = match->masks.ofdpa_vrf;
        flow->flowData.policyAclFlowEntry.match_criteria.sourceIp4     = match->fields.ipv4_src;
        flow->flowData.policyAclFlowEntry.match_criteria.sourceIp4Mask = match->masks.ipv4_src;
        flow->flowData.policyAclFlowEntry.match_criteria.destIp4       = match->fields.ipv4_dst;
        flow->flowData.policyAclFlowEntry.match_criteria.destIp4Mask   = match->masks.ipv4_dst;

        memcpy(flow->flowData.policyAclFlowEntry.match_criteria.sourceIp6.s6_addr, match->fields.ipv6_src.addr, OF_IPV6_BYTES);
        memcpy(flow->flowData.policyAclFlowEntry.match_criteria.sourceIp6Mask.s6_addr, match->masks.ipv6_src.addr, OF_IPV6_BYTES);
        memcpy(flow->flowData.policyAclFlowEntry.match_criteria.destIp6.s6_addr, match->fields.ipv6_dst.addr, OF_IPV6_BYTES);
        memcpy(flow->flowData.policyAclFlowEntry.match_criteria.destIp6Mask.s6_addr, match->masks.ipv6_dst.addr, OF_IPV6_BYTES);

        flow->flowData.policyAclFlowEntry.match_criteria.ipv4ArpSpa     = match->fields.arp_spa;
        flow->flowData.policyAclFlowEntry.match_criteria.ipv4ArpSpaMask = match->masks.arp_spa;
        flow->flowData.policyAclFlowEntry.match_criteria.ipProto        = match->fields.ip_proto;
        flow->flowData.policyAclFlowEntry.match_criteria.ipProtoMask    = match->masks.ip_proto;
        flow->flowData.policyAclFlowEntry.match_criteria.dscp           = match->fields.ip_dscp;
        flow->flowData.policyAclFlowEntry.match_criteria.dscpMask       = match->masks.ip_dscp;
        flow->flowData.policyAclFlowEntry.match_criteria.ecn            = match->fields.ip_ecn;
        flow->flowData.policyAclFlowEntry.match_criteria.ecnMask        = match->masks.ip_ecn;

        if (match->fields.ip_proto == IPPROTO_TCP)
        {
          flow->flowData.policyAclFlowEntry.match_criteria.srcL4Port      = match->fields.tcp_src;
          flow->flowData.policyAclFlowEntry.match_criteria.srcL4PortMask  = match->masks.tcp_src;
          flow->flowData.policyAclFlowEntry.match_criteria.destL4Port     = match->fields.tcp_dst;
          flow->flowData.policyAclFlowEntry.match_criteria.destL4PortMask = match->masks.tcp_dst;
        }
        else if (match->fields.ip_proto == IPPROTO_UDP)
        {
          flow->flowData.policyAclFlowEntry.match_criteria.srcL4Port      = match->fields.udp_src;
          flow->flowData.policyAclFlowEntry.match_criteria.srcL4PortMask  = match->masks.udp_src;
          flow->flowData.policyAclFlowEntry.match_criteria.destL4Port     = match->fields.udp_dst;
          flow->flowData.policyAclFlowEntry.match_criteria.destL4PortMask = match->masks.udp_dst;
        }
        else if (match->fields.ip_proto == IPPROTO_SCTP)
        {
          flow->flowData.policyAclFlowEntry.match_criteria.srcL4Port      = match->fields.sctp_src;
          flow->flowData.policyAclFlowEntry.match_criteria.srcL4PortMask  = match->masks.sctp_src;
          flow->flowData.policyAclFlowEntry.match_criteria.destL4Port     = match->fields.sctp_dst;
          flow->flowData.policyAclFlowEntry.match_criteria.destL4PortMask = match->masks.sctp_dst;
        }

        if (match->fields.ip_proto == IPPROTO_ICMP)
        {
          flow->flowData.policyAclFlowEntry.match_criteria.icmpType     = match->fields.icmpv4_type;
          flow->flowData.policyAclFlowEntry.match_criteria.icmpTypeMask = match->masks.icmpv4_type;
          flow->flowData.policyAclFlowEntry.match_criteria.icmpCode     = match->fields.icmpv4_code;
          flow->flowData.policyAclFlowEntry.match_criteria.icmpCodeMask = match->masks.icmpv4_code;
        }
        else if (match->fields.ip_proto == IPPROTO_ICMPV6)
        {
          flow->flowData.policyAclFlowEntry.match_criteria.icmpType     = match->fields.icmpv6_type;
          flow->flowData.policyAclFlowEntry.match_criteria.icmpTypeMask = match->masks.icmpv6_type;
          flow->flowData.policyAclFlowEntry.match_criteria.icmpCode     = match->fields.icmpv6_code;
          flow->flowData.policyAclFlowEntry.match_criteria.icmpCodeMask = match->masks.icmpv6_code;
        }

        flow->flowData.policyAclFlowEntry.match_criteria.ipv6FlowLabel     = match->fields.ipv6_flabel;
        flow->flowData.policyAclFlowEntry.match_criteria.ipv6FlowLabelMask = match->masks.ipv6_flabel;
      }
      break;

    default:
      LOG_ERROR("Invalid table id %d", flow->tableId);
      err = INDIGO_ERROR_PARAM;
      break;
  }

  if (err == INDIGO_ERROR_COMPAT)
  {
    LOG_ERROR("Incompatible match field(s) for table %d.", flow->tableId);
  }
#endif

  return err;
}

static indigo_error_t ind_ofdpa_translate_openflow_actions(of_list_action_t *actions, ofdpaFlowEntry_t *flow)
{
  of_action_t act;
  of_port_no_t port_no;
  uint32_t invalidPort = 0; /* Flag to check if the output port is valid*/
  int rv;

  OF_LIST_ACTION_ITER(actions, &act, rv) 
  {
    switch (act.object_id) 
    {
      case OF_ACTION_OUTPUT: 
      {
        of_action_output_port_get(&act, &port_no);
        break;
      }
      case OF_ACTION_SET_FIELD: 
      {
        /* HACK loci does not yet support the OXM field in the set-field action */
        of_list_oxm_t oxm;

        oxm.parent = &act;
        
        OF_LIST_OXM_ITER(&act,&oxm, rv);

        oxm.obj_offset+= 4; 
        of_object_wire_init(&oxm, OF_OXM, 0);

        if (oxm.length == 0) 
        {
          LOG_ERROR("Failed to parse set-field action");
          return INDIGO_ERROR_COMPAT;
        }

        switch (oxm.object_id) 
        {
          case OF_OXM_VLAN_VID: 
          {
            uint16_t vlan_vid;
            of_oxm_vlan_vid_value_get(&oxm, &vlan_vid);
 
            {
              LOG_ERROR("Unsupported set-field oxm %s for table %d", of_object_id_str[oxm.object_id], flow->tableId);
              return INDIGO_ERROR_COMPAT;
            }
          }
          case OF_OXM_VLAN_PCP: 
          {
            uint8_t vlan_pcp;
            of_oxm_vlan_pcp_value_get(&oxm, &vlan_pcp);
            break;
          }
          case OF_OXM_ETH_SRC: 
          {
            of_mac_addr_t mac;
            of_oxm_eth_src_value_get(&oxm, &mac);
            break;
          }
          case OF_OXM_ETH_DST: 
          {
            of_mac_addr_t mac;
            of_oxm_eth_dst_value_get(&oxm, &mac);
            break;
          }
          case OF_OXM_IPV4_SRC: 
          {
            uint32_t ipv4;
            of_oxm_ipv4_src_value_get(&oxm, &ipv4);
            break;
          }
          case OF_OXM_IPV4_DST: 
          {
            uint32_t ipv4;
            of_oxm_ipv4_dst_value_get(&oxm, &ipv4);
            break;
          }
          case OF_OXM_IP_DSCP: 
          {
            uint8_t ip_dscp;
            of_oxm_ip_dscp_value_get(&oxm, &ip_dscp);
            if (ip_dscp > ((uint8_t)IND_OFDPA_IP_DSCP_MASK >> 2)) 
            {
              LOG_ERROR("invalid dscp %d in action %s", ip_dscp,
                        of_object_id_str[act.object_id]);
              return INDIGO_ERROR_COMPAT;
            }
            break;
          }
          case OF_OXM_IP_ECN: 
          {
            uint8_t ip_ecn;
            of_oxm_ip_ecn_value_get(&oxm, &ip_ecn);

            if (ip_ecn > IND_OFDPA_IP_ECN_MASK) 
            {
              LOG_ERROR("invalid ecn %d in action %s", ip_ecn,
                        of_object_id_str[act.object_id]);
              return INDIGO_ERROR_COMPAT;
            }
            break;
          }
          case OF_OXM_IPV6_SRC: 
          {
            of_ipv6_t ipv6;
            of_oxm_ipv6_src_value_get(&oxm, &ipv6);
            break;
          }
          case OF_OXM_IPV6_DST: 
          {
            of_ipv6_t ipv6;
            of_oxm_ipv6_dst_value_get(&oxm, &ipv6);
            break;
          }
          case OF_OXM_IPV6_FLABEL: 
          {
            uint32_t flabel;
            of_oxm_ipv6_flabel_value_get(&oxm, &flabel);
            if (flabel > IND_OFDPA_IPV6_FLABEL_MASK) 
            {
              LOG_ERROR("invalid flabel 0x%04x in action %s", flabel,
                        of_object_id_str[act.object_id]);
              return INDIGO_ERROR_COMPAT;
            }
            break;
          }
          case OF_OXM_TCP_SRC: 
          {
            uint16_t port;
            of_oxm_tcp_src_value_get(&oxm, &port);
            break;
          }
          case OF_OXM_TCP_DST: 
          {
            uint16_t port;
            of_oxm_tcp_dst_value_get(&oxm, &port);
            break;
          }
          case OF_OXM_UDP_SRC:
          {
            uint16_t port;
            of_oxm_udp_src_value_get(&oxm, &port);
            break;
          }
          case OF_OXM_UDP_DST: 
          {
            uint16_t port;
            of_oxm_udp_dst_value_get(&oxm, &port);
            break;
          }
         
          default:
           LOG_ERROR("unsupported set-field oxm %d", oxm.object_id);
           return INDIGO_ERROR_COMPAT;
        }
        break;
      }
      case OF_ACTION_SET_QUEUE:
      {
        uint32_t queue_id;
        of_action_set_queue_queue_id_get(&act, &queue_id);
        break;
      } 
      case OF_ACTION_SET_DL_DST: 
      {
        of_mac_addr_t mac;
        of_action_set_dl_dst_dl_addr_get(&act, &mac);
        break;
      }
      case OF_ACTION_SET_DL_SRC: 
      {
        of_mac_addr_t mac;
        of_action_set_dl_src_dl_addr_get(&act, &mac);
        break;
      }
      case OF_ACTION_SET_NW_DST: 
      {
        uint32_t ipv4;
        of_action_set_nw_dst_nw_addr_get(&act, &ipv4);
        break;
      }
      case OF_ACTION_SET_NW_SRC: 
      {
        uint32_t ipv4;
        of_action_set_nw_src_nw_addr_get(&act, &ipv4);
        break;
      }
      case OF_ACTION_SET_NW_TOS: 
      {
        uint8_t tos;
        of_action_set_nw_tos_nw_tos_get(&act, &tos);
        break;
      }
      case OF_ACTION_SET_TP_DST: 
      {
        uint16_t port;
        of_action_set_tp_dst_tp_port_get(&act, &port);
        break;
      }
      case OF_ACTION_SET_TP_SRC: 
      {
        uint16_t port;
        of_action_set_tp_src_tp_port_get(&act, &port);
        break;
      }
      case OF_ACTION_SET_VLAN_VID: 
      {
        uint16_t vlan_vid;
        of_action_set_vlan_vid_vlan_vid_get(&act, &vlan_vid);

        break;
      }
      case OF_ACTION_SET_VLAN_PCP: 
      {
        uint8_t vlan_pcp;
        of_action_set_vlan_pcp_vlan_pcp_get(&act, &vlan_pcp);
        break;
      }
      case OF_ACTION_POP_VLAN:
      case OF_ACTION_STRIP_VLAN: 
      {
        break;
      }
      case OF_ACTION_PUSH_VLAN: 
      {
        uint16_t eth_type;
        of_action_push_vlan_ethertype_get(&act, &eth_type);

        if (eth_type != ETH_P_8021Q) 
        {
          LOG_ERROR("unsupported eth_type 0x%04x in action %s", eth_type,
                    of_object_id_str[act.object_id]);
           return INDIGO_ERROR_COMPAT;
        }
        break;
      }
      case OF_ACTION_DEC_NW_TTL:
      case OF_ACTION_NICIRA_DEC_TTL: 
      {
        break;
      }
      case OF_ACTION_SET_NW_TTL: 
      {
        uint8_t ttl;
        of_action_set_nw_ttl_nw_ttl_get(&act, &ttl);
        break;
      }
      case OF_ACTION_GROUP: 
      {
        uint32_t group_id;
        of_action_group_group_id_get(&act, &group_id);
        break;
      }
      default:
       LOG_ERROR("unsupported action %s", of_object_id_str[act.object_id]);
       return INDIGO_ERROR_COMPAT;
    }
  }

  return INDIGO_ERROR_NONE;
}
#if 0
static indigo_error_t
ind_ofdpa_instructions_get(of_flow_modify_t *flow_mod, ofdpaFlowEntry_t *flow)
{

  return INDIGO_ERROR_NONE;
}
#else
static indigo_error_t
ind_ofdpa_instructions_get(of_flow_modify_t *flow_mod, ofdpaFlowEntry_t *flow)
{
  of_list_action_t openflow_actions;
  indigo_error_t err;
  uint8_t next_table_id;
  uint32_t meter_id;
  int rv;
  of_list_instruction_t insts;
  of_instruction_t inst;
  uint8_t table_id;


  of_flow_modify_instructions_bind(flow_mod, &insts);

  of_flow_modify_table_id_get(flow_mod, &table_id);

  OF_LIST_INSTRUCTION_ITER(&insts, &inst, rv)
  {
    switch (inst.object_id)
    {
      case OF_INSTRUCTION_APPLY_ACTIONS:
//        of_instruction_apply_actions_actions_bind(&inst.apply_actions, &openflow_actions);
//        if ((err = ind_ofdpa_translate_openflow_actions(&openflow_actions, flow)) < 0)
//        {
//          return err;
//        }
        break;
      case OF_INSTRUCTION_WRITE_ACTIONS:
//        of_instruction_write_actions_actions_bind(&inst.write_actions, &openflow_actions);
//        if ((err = ind_ofdpa_translate_openflow_actions(&openflow_actions, flow)) < 0)
//        {
//          return err;
//        }
        break;
      case OF_INSTRUCTION_CLEAR_ACTIONS:
        break;
      case OF_INSTRUCTION_GOTO_TABLE:
//        of_instruction_goto_table_table_id_get(&inst.goto_table, &next_table_id);
        break;
      case OF_INSTRUCTION_METER:
//        of_instruction_meter_meter_id_get(&inst.meter, &meter_id);
        LOG_ERROR("Unsupported instruction: meter_id.");
        break;
      default:
        LOG_ERROR("Invalid instruction.");
        return INDIGO_ERROR_COMPAT;
    }
  }
  return INDIGO_ERROR_NONE;
}
#endif

static indigo_error_t ind_ofdpa_packet_out_actions_get(of_list_action_t *of_list_actions, 
                                                       indPacketOutActions_t *packetOutActions)
{
  of_action_t act;
  indigo_error_t err = INDIGO_ERROR_NONE;
  int rv;


  OF_LIST_ACTION_ITER(of_list_actions, &act, rv)
  {
    switch (act.object_id)
    {
      case OF_ACTION_OUTPUT:
      {
        of_port_no_t port_no;
        of_action_output_port_get(&act, &port_no);
        switch (port_no)
        {
          case OF_PORT_DEST_CONTROLLER:
          case OF_PORT_DEST_FLOOD:
          case OF_PORT_DEST_ALL:
          case OF_PORT_DEST_LOCAL:
          case OF_PORT_DEST_IN_PORT:
          case OF_PORT_DEST_NORMAL:
            LOG_INFO("Unsupported output port 0x%x", port_no);
            err = INDIGO_ERROR_NOT_SUPPORTED;
            break;
          case OF_PORT_DEST_USE_TABLE:
            packetOutActions->pipeline = 1;
            break;
          default:
            packetOutActions->outputPort = port_no;
            break;
        }
        break;
      }
      default:
        LOG_ERROR("Unsupported action for packet out: %s", of_object_id_str[act.object_id]);
        err = INDIGO_ERROR_NOT_SUPPORTED;
        break;
    }
  } 

  return err; 
}

#if 0
indigo_error_t indigo_fwd_forwarding_features_get(of_features_reply_t *features_reply)
{
  uint32_t tableId, tableCount = 0;

  LOG_TRACE("%s() called", __FUNCTION__);

  if (features_reply->version < OF_VERSION_1_3)
  {
    LOG_ERROR("Unsupported OpenFlow version 0x%x.", features_reply->version);
    return INDIGO_ERROR_VERSION;
  }

  /* Number of tables supported by datapath. */
  /* Number of tables supported by datapath. */
  for (tableId = 0; tableId < 255; tableId++)
  {
    if (ofdpaFlowTableSupported(tableId) == OFDPA_E_NONE)
    {
      tableCount++;
    }
  }
  of_features_reply_n_tables_set(features_reply, tableCount);

  return INDIGO_ERROR_NONE;
}

#else
indigo_error_t
indigo_fwd_forwarding_features_get(of_features_reply_t *features)
{
    AIM_LOG_VERBOSE("forwarding features get called\n");
    uint32_t capabilities = 0, actions = 0;

    of_features_reply_n_tables_set(features, 1);

    OF_CAPABILITIES_FLAG_FLOW_STATS_SET(capabilities, features->version);
    OF_CAPABILITIES_FLAG_TABLE_STATS_SET(capabilities, features->version);
    OF_CAPABILITIES_FLAG_PORT_STATS_SET(capabilities, features->version);
    OF_CAPABILITIES_FLAG_QUEUE_STATS_SET(capabilities, features->version);
    OF_CAPABILITIES_FLAG_ARP_MATCH_IP_SET(capabilities, features->version);
    of_features_reply_capabilities_set(features, capabilities);

    return INDIGO_ERROR_NONE;
}
#endif

indigo_error_t indigo_fwd_flow_create(indigo_cookie_t flow_id,
                                      of_flow_add_t *flow_add,
                                      uint8_t *table_id)
{
  indigo_error_t err = INDIGO_ERROR_NONE;
  OFDPA_ERROR_t ofdpa_rv = OFDPA_E_NONE;
  ofdpaFlowEntry_t flow;
  uint16_t priority;
  uint16_t idle_timeout, hard_timeout;
  of_match_t of_match;

  LOG_INFO("###Nokia DPA Integration###:Flow create called");

  if (flow_add->version < OF_VERSION_1_3) 
  {
    LOG_ERROR("OpenFlow version 0x%x unsupported", flow_add->version);
    return INDIGO_ERROR_VERSION;
  }

  memset(&flow, 0, sizeof(flow));

  #if 0

  for(i=0;i<flow_add->length;i++)
  {
        of_wire_buffer_u8_get(flow_add->wbuf,(flow_add->obj_offset+i),&value);
        LOG_INFO("%d: %02x",i,value);
   }
   #endif

    
  flow.cookie = flow_id;
  /* Get the Flow Table ID */
  of_flow_add_table_id_get(flow_add, table_id);
  flow.tableId = (uint32_t)*table_id;

  /* ofdpa Flow priority */
  of_flow_add_priority_get(flow_add, &priority);
  flow.priority = (uint32_t)priority;

  /* Get the idle time and hard time */
  (void)of_flow_modify_idle_timeout_get((of_flow_modify_t *)flow_add, &idle_timeout);
  (void)of_flow_modify_hard_timeout_get((of_flow_modify_t *)flow_add, &hard_timeout);
  flow.idle_time = (uint32_t)idle_timeout;
  flow.hard_time = (uint32_t)hard_timeout;

  memset(&of_match, 0, sizeof(of_match));
  if (of_flow_add_match_get(flow_add, &of_match) < 0)
  {
    LOG_ERROR("Error getting openflow match criteria.");
    return INDIGO_ERROR_UNKNOWN;
  }

  /* Get the match fields and masks from LOCI match structure */
  err = ind_ofdpa_match_fields_masks_get(&of_match, &flow);
  if (err != INDIGO_ERROR_NONE)
  {
    LOG_ERROR("Error getting match fields and masks. (err = %d)", err);
    return err;
  }

  /* Get the instructions set from the LOCI flow add object */
  err = ind_ofdpa_instructions_get(flow_add, &flow); 
  if (err != INDIGO_ERROR_NONE)
  {
    LOG_TRACE("Failed to get flow instructions. (err = %d)", err);
    return err;
  }

  // todo: adjust to the rrc api here.

  /* Submit the changes to ofdpa */
  ofdpa_rv = ofdpaFlowAdd(&flow);
  if (ofdpa_rv != OFDPA_E_NONE)
  {
    LOG_TRACE("Failed to add flow. (ofdpa_rv = %d)", ofdpa_rv);
  }
  else
  {
    LOG_TRACE("Flow added successfully. (ofdpa_rv = %d)", ofdpa_rv);
  }
  

  return (indigoConvertOfdpaRv(ofdpa_rv));
}

indigo_error_t indigo_fwd_flow_modify(indigo_cookie_t flow_id,
                                      of_flow_modify_t *flow_modify)
{
  indigo_error_t err = INDIGO_ERROR_NONE;
  ofdpaFlowEntry_t flow;
  ofdpaFlowEntryStats_t flowStats;
  OFDPA_ERROR_t ofdpa_rv = OFDPA_E_NONE;  
  of_match_t of_match;

  LOG_TRACE("Flow modify called");	

  if (flow_modify->version < OF_VERSION_1_3)
  {
    LOG_ERROR("OpenFlow version 0x%x unsupported", flow_modify->version);
    return INDIGO_ERROR_VERSION;
  }

  memset(&flow, 0, sizeof(flow));
  memset(&flowStats, 0, sizeof(flowStats));

  /* Get the flow entries and flow stats from the indigo cookie */
  ofdpa_rv = ofdpaFlowByCookieGet(flow_id, &flow, &flowStats);
  if (ofdpa_rv != OFDPA_E_NONE)
  {
    if (ofdpa_rv == OFDPA_E_NOT_FOUND)
    {
      LOG_ERROR("Request to modify non-existent flow. (ofdpa_rv = %d)", ofdpa_rv);
    }
    else
    {
      LOG_ERROR("Invalid flow. (ofdpa_rv = %d)", ofdpa_rv);
    }
    return (indigoConvertOfdpaRv(ofdpa_rv));   
  }

  memset(&of_match, 0, sizeof(of_match));
  if (of_flow_add_match_get(flow_modify, &of_match) < 0)
  {
    LOG_ERROR("Error getting openflow match criteria.");
    return INDIGO_ERROR_UNKNOWN;
  }
  
  memset(&flow.flowData, 0, sizeof(flow.flowData));

  /* Get the match fields and masks from LOCI match structure */
  err = ind_ofdpa_match_fields_masks_get(&of_match, &flow);
  if (err != INDIGO_ERROR_NONE)
  {
    LOG_ERROR("Error getting match fields and masks. (err = %d)", err);
    return err;
  }

  /* Get the modified instructions set from the LOCI flow add object */
  err = ind_ofdpa_instructions_get(flow_modify, &flow);
  if (err != INDIGO_ERROR_NONE)  
  {
    LOG_TRACE("Failed to get flow instructions. (err = %d)", err);
    return err;
  } 

  /* Submit the changes to ofdpa */
  ofdpa_rv = ofdpaFlowModify(&flow);
  if (ofdpa_rv!= OFDPA_E_NONE)
  {
    LOG_TRACE("Failed to modify flow. (ofdpa_rv = %d)", ofdpa_rv);
  }
  else
  {
    LOG_TRACE("Flow modified successfully. (ofdpa_rv = %d)", ofdpa_rv);
  }

  return (indigoConvertOfdpaRv(ofdpa_rv));
}

indigo_error_t indigo_fwd_flow_delete(indigo_cookie_t flow_id,
                                      indigo_fi_flow_stats_t *flow_stats)
{
  ofdpaFlowEntry_t flow;
  ofdpaFlowEntryStats_t flowStats;
  OFDPA_ERROR_t ofdpa_rv = OFDPA_E_NONE;


  LOG_TRACE("Flow delete called");

  memset(&flow, 0, sizeof(flow));
  memset(&flowStats, 0, sizeof(flowStats));

      ofdpa_rv = ofdpaFlowByCookieGet(flow_id, &flow, &flowStats);
      if (ofdpa_rv != OFDPA_E_NONE)
      {
          if (ofdpa_rv == OFDPA_E_NOT_FOUND)
          {
              LOG_INFO("Request to delete non-existent flow. (ofdpa_rv = %d)", ofdpa_rv);
          }
          else
          {
              LOG_ERROR("Invalid flow. (ofdpa_rv = %d)", ofdpa_rv);
          }
          return (indigoConvertOfdpaRv(ofdpa_rv));
       }

       //flow_stats->flow_id = flow_id;
       flow_stats->packets = flowStats.receivedPackets;
       flow_stats->bytes = flowStats.receivedBytes;
       //flow_stats->duration_ns = (flowStats.durationSec)*(IND_OFDPA_NANO_SEC); /* Convert to nano seconds*/

       /* Delete the flow entry */
       ofdpa_rv = ofdpaFlowByCookieDelete(flow_id);
       if (ofdpa_rv != OFDPA_E_NONE)
       {
         LOG_INFO("Failed to delete flow. (ofdpa_rv = %d)", ofdpa_rv);
       }
       else
       {
         LOG_TRACE("Flow deleted successfully. (ofdpa_rv = %d)", ofdpa_rv);
       }


  
  return (indigoConvertOfdpaRv(ofdpa_rv));;
}

indigo_error_t indigo_fwd_flow_stats_get(indigo_cookie_t flow_id,
                                         indigo_fi_flow_stats_t *flow_stats)
{
  OFDPA_ERROR_t ofdpa_rv = OFDPA_E_NONE;
  ofdpaFlowEntry_t flow;
  ofdpaFlowEntryStats_t flowStats;

  memset(&flow, 0, sizeof(flow));
  memset(&flowStats, 0, sizeof(flowStats));

  /* Get the flow and flow stats from flow id */	
  ofdpa_rv = ofdpaFlowByCookieGet(flow_id, &flow, &flowStats);
  if (ofdpa_rv == OFDPA_E_NONE)
  {
    //flow_stats->flow_id = flow_id;
    //flow_stats->duration_ns = (flowStats.durationSec) * (IND_OFDPA_NANO_SEC); /* Convert to nsecs */
    flow_stats->packets = flowStats.receivedPackets;
    flow_stats->bytes = flowStats.receivedBytes;

    LOG_INFO("Flow stats get successful. (ofdpa_rv = %d)", ofdpa_rv);
  }
  else if (ofdpa_rv == OFDPA_E_NOT_FOUND)
  {
    LOG_ERROR("Request to get stats of a non-existent flow. (ofdpa_rv = %d)", ofdpa_rv);
  }
  else
  {
    LOG_ERROR("Failed to get flow stats. (ofdpa_rv = %d)", ofdpa_rv);
  }

  return (indigoConvertOfdpaRv(ofdpa_rv));
}

void indigo_fwd_table_mod(of_table_mod_t *of_table_mod,
                          indigo_cookie_t callback_cookie)
{
  LOG_INFO("indigo_fwd_table_mod() unsupported.");
  return;
}

indigo_error_t indigo_fwd_table_stats_get(of_table_stats_request_t *table_stats_request,
                                          of_table_stats_reply_t **table_stats_reply)
{
  of_version_t version = table_stats_request->version;
  uint32_t xid;
  uint32_t i;
  ofdpaFlowTableInfo_t tableInfo;
  of_table_stats_entry_t entry[1];
  of_table_stats_reply_t *reply;
  of_list_table_stats_entry_t list[1];


  if (table_stats_request->version < OF_VERSION_1_3)
  {
    LOG_ERROR("Unsupported OpenFlow version 0x%x.", version);
    return INDIGO_ERROR_VERSION;
  }

  reply = of_table_stats_reply_new(version);
  if (reply == NULL)
  {
    LOG_ERROR("Error allocating memory");
    return INDIGO_ERROR_RESOURCE;
  }

  *table_stats_reply = reply;

  of_table_stats_request_xid_get(table_stats_request, &xid);
  of_table_stats_reply_xid_set(*table_stats_reply, xid);

  of_table_stats_reply_entries_bind(*table_stats_reply, list);


  for (i = 0; i < 255; i++)
  {
    if (1)
    {
      of_table_stats_entry_init(entry, version, -1, 1);
      (void)of_list_table_stats_entry_append_bind(list, entry);

      /* Table Id */
      of_table_stats_entry_table_id_set(entry, i);

      /* Number of entries in the table */
      if (ofdpaFlowTableInfoGet(i, &tableInfo) == OFDPA_E_NONE)
      {
        of_table_stats_entry_active_count_set(entry, tableInfo.numEntries);
      }

      /* Number of packets looked up in table not supported. */
      of_table_stats_entry_lookup_count_set(entry, 0);

      /* Number of packets that hit table not supported. */
      of_table_stats_entry_matched_count_set(entry, 0);
    }
  }

  return(INDIGO_ERROR_NONE);
}
#if 1
indigo_error_t indigo_fwd_packet_out(of_packet_out_t *packet_out)
{
  OFDPA_ERROR_t  ofdpa_rv = OFDPA_E_NONE;
  indigo_error_t err = INDIGO_ERROR_NONE;
  indPacketOutActions_t packetOutActions;
  ofdpa_buffdesc pkt;

  of_port_no_t   of_port_num;
  of_list_action_t of_list_action[1];
  of_octets_t    of_octets[1];

  of_packet_out_in_port_get(packet_out, &of_port_num);
  of_packet_out_data_get(packet_out, of_octets);
  of_packet_out_actions_bind(packet_out, of_list_action);

	
  pkt.pstart = (char *)of_octets->data;
  pkt.size = of_octets->bytes; 

  memset(&packetOutActions, 0, sizeof(packetOutActions)); 
  err = ind_ofdpa_packet_out_actions_get(of_list_action, &packetOutActions);
  if (err != INDIGO_ERROR_NONE)
  {
    LOG_ERROR("Failed to get packet out actions. (err = %d)", err);
    return err;
  }


  if (packetOutActions.pipeline)
  {
    ofdpa_rv = ofdpaPktSend(&pkt, OFDPA_PKT_LOOKUP, packetOutActions.outputPort, of_port_num);
  }
  else
  {
    ofdpa_rv = ofdpaPktSend(&pkt, 0, packetOutActions.outputPort, 0);
  }

  if (ofdpa_rv != OFDPA_E_NONE)
  {
    LOG_ERROR("Packet send failed. (ofdpa_rv = %d)", ofdpa_rv);
  }
  else
  {
    LOG_INFO("Packet sent out of output port (%d) successfully. (ofdpa_rv = %d)", packetOutActions.outputPort, ofdpa_rv);
  }

  return (indigoConvertOfdpaRv(ofdpa_rv));
}
#else
indigo_error_t
indigo_fwd_packet_out(of_packet_out_t *of_packet_out)
{
    AIM_LOG_VERBOSE("packet out called\n");
    return INDIGO_ERROR_NONE;
}
#endif
indigo_error_t indigo_fwd_experimenter(of_experimenter_t *experimenter,
                                       indigo_cxn_id_t cxn_id)
{
  LOG_INFO("indigo_fwd_experimenter() unsupported.");
  return INDIGO_ERROR_NOT_SUPPORTED;
}

indigo_error_t indigo_fwd_expiration_enable_set(int is_enabled)
{
  LOG_TRACE("indigo_fwd_expiration_enable_set() unsupported.");
  return INDIGO_ERROR_NOT_SUPPORTED;
}

indigo_error_t indigo_fwd_expiration_enable_get(int *is_enabled)
{
  LOG_TRACE("indigo_fwd_expiration_enable_get() unsupported.");
  return INDIGO_ERROR_NOT_SUPPORTED;
}

void ind_ofdpa_flow_event_receive(void)
{
  int flowTableId;
  ofdpaFlowEvent_t flowEventData;

  LOG_TRACE("Reading Flow Events");

  for (flowTableId = 0; flowTableId < 255; flowTableId++)
  {
    if (1)
    {
      memset(&flowEventData, 0, sizeof(flowEventData));
      flowEventData.flowMatch.tableId = flowTableId;

  while (ofdpaFlowEventNextGet(&flowEventData) == OFDPA_E_NONE)
  {
    if (flowEventData.eventMask & OFDPA_FLOW_EVENT_HARD_TIMEOUT)
    {
      LOG_INFO("Received flow event on hard timeout.");
      //ind_core_flow_expiry_handler(flowEventData.flowMatch.cookie,
      //                             INDIGO_FLOW_REMOVED_HARD_TIMEOUT);
    }
    else
    {
      LOG_INFO("Received flow event on idle timeout.");
      //ind_core_flow_expiry_handler(flowEventData.flowMatch.cookie,
      //                             INDIGO_FLOW_REMOVED_IDLE_TIMEOUT);
        }
      }
    }
  }

  return;
}

static void ind_ofdpa_key_to_match(uint32_t portNum, of_match_t *match)
{
  memset(match, 0, sizeof(*match));

  /* We only populate the masks for this OF version */
  match->version = ofagent_of_version;
  match->fields.in_port = portNum;
  OF_MATCH_MASK_IN_PORT_EXACT_SET(match);
}

static indigo_error_t
ind_ofdpa_fwd_pkt_in(of_port_no_t in_port,
               uint8_t *data, unsigned int len, unsigned reason,
               of_match_t *match, OFDPA_FLOW_TABLE_ID_t tableId)
{
  of_octets_t of_octets = { .data = data, .bytes = len };
  of_packet_in_t *of_packet_in;

  LOG_TRACE("Sending packet-in");

  of_packet_in = of_packet_in_new(ofagent_of_version);
  if (of_packet_in == NULL) 
  {
    return INDIGO_ERROR_RESOURCE;
  }

  of_packet_in_total_len_set(of_packet_in, len);
  of_packet_in_reason_set(of_packet_in, reason);
  of_packet_in_table_id_set(of_packet_in, tableId);
  of_packet_in_cookie_set(of_packet_in, 0xffffffffffffffffLL);

  if (of_packet_in_match_set(of_packet_in, match) != OF_ERROR_NONE) 
  {
    LOG_ERROR("Failed to write match to packet-in message");
    of_packet_in_delete(of_packet_in);
    return INDIGO_ERROR_UNKNOWN;
  }

  if (of_packet_in_data_set(of_packet_in, &of_octets) != OF_ERROR_NONE) 
  {
    LOG_ERROR("Failed to write packet data to packet-in message");
    of_packet_in_delete(of_packet_in);
    return INDIGO_ERROR_UNKNOWN;
  }

  return indigo_core_packet_in(of_packet_in);
}

/*******************************************************************************
*
*   @brief    ind_ofdpa_pkt_in_construct_fwd
       SDN controller need packet_in + port_status message to show the topology and hosts, so introduced 
       this funciton
       it will Construct packet in receive message and send to SDN controller
       Note:for later use , this ethernet packet should be came from AXM recevied packet itself,
               currently, just fake a ethernet packet
     @input parameters 
*******************************************************************************/
void ind_ofdpa_pkt_in_construct_fwd(uint32_t port_no,uint8_t *srcMacPtr)
{
#if 0
  /*need test , does packet in only need once*/
  indigo_error_t rc;
  uint32_t i;
  uint32_t maxPktSize;
  ofdpaPacket_t rxPkt;
  of_match_t match;
  struct ind_ovs_parsed_key *constructKeyPtr;

  /*in HW testing need use actually mac address by calling funciton ncp_eioa_mac_addr_get();*/

  //__u8 srcMac[ETH_ALEN] = { 0xa, 0xb, 0xc, 0xd, 0xe, 0xf }; /*source MAC address of the port*/
  __u8 destMac[ETH_ALEN] = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15 }; /*Destination MAC address of the port*/

  LOG_INFO("ind_ofdpa_pkt_in_construct_fwd called port %d",port_no);
  
  memset(&rxPkt, 0, sizeof(ofdpaPacket_t));
  /* Determine how large receive buffer must be */
  /*typically , a ethernet packet would be 64~1500 Bytes*/
  maxPktSize = 1024;
  rxPkt.pktData.pstart =  malloc(maxPktSize);
  if (rxPkt.pktData.pstart == NULL)
  {
    LOG_ERROR("\nFailed to allocate receive packet buffer\r\n");
    return;
  }
  memset(rxPkt.pktData.pstart,0,maxPktSize);
  
  /*construct the packet-in data*/
  rxPkt.pktData.size = 256; /*just temporarity set this size*/
  rxPkt.inPortNum = port_no;  /*does the inport should align with AXM port?  */
  rxPkt.reason = OFDPA_PACKET_IN_REASON_ACTION; /*ACTION*/
  //rxPkt.tableId = OFDPA_FLOW_TABLE_ID_INGRESS_PORT;
  rxPkt.tableId = OFDPA_FLOW_TABLE_ID_ACL_POLICY;
  /*construct ethernet packet, in this demo phase, it's very very simple that just consturct a MAC address*/
  constructKeyPtr = (struct ind_ovs_parsed_key*)rxPkt.pktData.pstart;
  /*skip vlan and in_port temporarily */
  // constructKeyPtr->in_port = 0;
  //constructKeyPtr->vlan = 0;
  
//  constructKeyPtr->ethertype = htons(ETHERNET_TYPE_IP);;/*need convert to network order*/
  
  memcpy(constructKeyPtr->ethernet.eth_src,srcMacPtr,ETH_ALEN);
  memcpy(constructKeyPtr->ethernet.eth_dst,destMac,ETH_ALEN);
  
  ind_ofdpa_key_to_match(rxPkt.inPortNum, &match);

  rc = ind_ofdpa_fwd_pkt_in(rxPkt.inPortNum, rxPkt.pktData.pstart, 
                       (rxPkt.pktData.size - 4), rxPkt.reason, 
                       &match, rxPkt.tableId);
  
  if (rc != INDIGO_ERROR_NONE)
  {
    LOG_ERROR("Could not send Packet-in message, rc = 0x%x", rc);
  }
  
  free(rxPkt.pktData.pstart);
#endif
  return;
}


void ind_ofdpa_pkt_receive(void)
{
  indigo_error_t rc;
  uint32_t i;
  uint32_t maxPktSize;
  ofdpaPacket_t rxPkt;
  of_match_t match;
  struct timeval timeout;

  /* Determine how large receive buffer must be */
  if (ofdpaMaxPktSizeGet(&maxPktSize) != OFDPA_E_NONE)
  {
    LOG_ERROR("\nFailed to determine maximum receive packet size.\r\n");
    return;
  }

  memset(&rxPkt, 0, sizeof(ofdpaPacket_t));
  rxPkt.pktData.pstart = (char*) malloc(maxPktSize);
  if (rxPkt.pktData.pstart == NULL)
  {
    LOG_ERROR("\nFailed to allocate receive packet buffer\r\n");
    return;
  }
  rxPkt.pktData.size = maxPktSize;

  timeout.tv_sec = 0;
  timeout.tv_usec = 0;

  while (ofdpaPktReceive(&timeout, &rxPkt) == OFDPA_E_NONE)
  {
    LOG_TRACE("Client received packet");
    LOG_TRACE("Reason:  %d", rxPkt.reason);
    LOG_TRACE("Table ID:  %d", rxPkt.tableId);
    LOG_TRACE("Ingress port:  %u", rxPkt.inPortNum);
    LOG_TRACE("Size:  %u\r\n", rxPkt.pktData.size);
    for (i = 0; i < rxPkt.pktData.size; i++)
    {
      if (i && ((i % 16) == 0))
        LOG_TRACE("\r\n");
      LOG_TRACE("%02x ", (unsigned int) *(rxPkt.pktData.pstart + i));
    }
    LOG_TRACE("\r\n");

    ind_ofdpa_key_to_match(rxPkt.inPortNum, &match);

    rc = ind_ofdpa_fwd_pkt_in(rxPkt.inPortNum, rxPkt.pktData.pstart, 
                         (rxPkt.pktData.size - 4), rxPkt.reason, 
                         &match, rxPkt.tableId);

    if (rc != INDIGO_ERROR_NONE)
    {
      LOG_ERROR("Could not send Packet-in message, rc = 0x%x", rc);
    }
  }
  free(rxPkt.pktData.pstart);
  return;
}

/* It has been copied from modules/OFStateManager/utest/main.c */

void
indigo_fwd_pipeline_get(of_desc_str_t pipeline)
{
    LOG_TRACE("fwd switch pipeline get");
    strcpy(pipeline, "ofdpa_pipeline");
}

indigo_error_t
indigo_fwd_pipeline_set(of_desc_str_t pipeline)
{
    LOG_ERROR("fwd switch pipeline set: %s", pipeline);
    return INDIGO_ERROR_NOT_SUPPORTED;
}

void
indigo_fwd_pipeline_stats_get(of_desc_str_t **pipeline, int *num_pipelines)
{
    LOG_TRACE("fwd switch pipeline stats get");
    *num_pipelines = 0;
}

