/*********************************************************************
*
* (C) Copyright Nokia HZ SITE HETNET WBTS UP15 20015-2016
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
* @filename     RTEOfDriver.h
*
* @purpose      
*
* @component    
*
* @comments     none
*
* @create       05/12/2015
*
* @end
*
**********************************************************************/
#ifndef INCLUDE_RTE_OF_DRIVER_API_H
#define INCLUDE_RTE_OF_DRIVER_API_H
#include "ofdpa_datatypes.h"

#define GETU8CHAR(a,b)   ((a>>b)&0xff) 
struct rule_id_mapping_struct
{
   ncp_uint32_t rule_id_from_of;
   ncp_uint32_t rule_id_in_acl;
   ncp_uint8_t flag;
};
typedef struct acl_rule_mapping_struct
{
   ncp_uint32_t aclid;
   struct rule_id_mapping_struct rule_id_mapping[16];
   ncp_uint8_t flag;
}acl_rule_mapping_struct;
typedef enum 
{
    ACL_RULE_ADD = 0,
    ACL_RULE_DELETE,
    ACL_RULE_NONE
}ACL_RULE_ADD_OR_DELETE;
#ifdef RTE_MODE
/*********************************************************************
* @purpose  Add a new entry to acl talbe
*
* @param    flow    @b{(input)} structure containing flow entry parameters
*
* @returns  ncp_st_t  
* @end
*********************************************************************/
ncp_st_t acl_rule_add(ofdpaFlowEntry_t *flow);
ncp_st_t acl_rule_delete(ofdpaFlowEntry_t *flow);
ncp_st_t bridge_static_entry_add(ofdpaFlowEntry_t *flow);
ncp_st_t bridge_static_entry_delete(ofdpaFlowEntry_t *flow);
ncp_st_t bridge_static_entry_modify(ofdpaFlowEntry_t *flow);
ncp_st_t rte_port_next_get(int32_t portNum, int32_t *nextPortNum, ncp_bool_t xgmac_flag);
ncp_st_t rte_port_statistics_get(ncp_macChan_t macChan, ncp_bool_t xgmac_flag,
            ncp_mac_txstat_t *tx_mac_stats,
            ncp_mac_rxstat_t *rx_mac_stats);
ncp_st_t rte_port_name_get(int32_t portNum, char *name, ncp_bool_t xgmac_flag);
ncp_st_t rte_port_mchan_get(int32_t portNum, ncp_macChan_t *macChan, ncp_bool_t xgmac_flag);
ncp_st_t rte_port_link_status_get(ncp_macChan_t macChan, ncp_bool_t xgmac_flag, ncp_mac_phy_status_t *phyStatus);

#endif
#endif

