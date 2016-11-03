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
* @filename     rte_of_driver_bridge.h
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
#include <ind_of_util.h>
#include <unistd.h>
#include <ind_of_log.h>
#include <stdbool.h>
#include <pthread.h>
#include <errno.h>
#ifdef RTE_MODE
#include <ncp.h>
#include "RTEOfDriver_api.h"
extern ncp_hdl_t inNcpHdl;


/*********************************************************************
* @purpose  get the setted vps id
*
* @param    port_id 
*
* @returns  ncp_uint8_t   index
* @end
*********************************************************************/

ncp_uint8_t get_destination_vps_id(ncp_uint32_t out_port_id)
{
   if (out_port_id == NCP_GMAC0)
     return 1;
   if (out_port_id == NCP_GMAC1)
     return 2;
   if (out_port_id == NCP_GMAC17)
     return 21;
   if (out_port_id == NCP_GMAC18)
     return 22;
   return 1;
}

ncp_uint8_t get_source_logic_port(ncp_uint16_t in_port_id)
{
   if (in_port_id == NCP_GMAC0)
      return 0;
   if (in_port_id == NCP_GMAC1)
      return 1;
   if (in_port_id == NCP_GMAC17)
      return 10; 
   return 0;
}
/*********************************************************************
* @purpose  Add a new entry to bridge static entry
*
* @param    flow    @b{(input)} structure containing flow entry parameters
*
* @returns  ncp_st_t  
* @end
*********************************************************************/

ncp_st_t bridge_static_entry_add(ofdpaFlowEntry_t *flow)
{
    ncp_eioa_switch_bridge_entry_t entry_attrs;
    ncp_st_t status = NCP_ST_SUCCESS;
    memset(&entry_attrs,0,sizeof(ncp_eioa_switch_bridge_entry_t));
    entry_attrs.key.type = NCP_EIOA_SWITCH_KEY_IVL;
    entry_attrs.key.vlanId = flow->flowData.bridgingFlowEntry.match_criteria.vlanId;
    memcpy(entry_attrs.key.macAddress,flow->flowData.bridgingFlowEntry.match_criteria.destMac.addr,6* sizeof(ncp_uint8_t));
    entry_attrs.sourceLogicalPort = get_source_logic_port(flow->flowData.bridgingFlowEntry.match_criteria.tunnelId);
    entry_attrs.destinationIdx = get_destination_vps_id(flow->flowData.bridgingFlowEntry.outputPort);
    LOG_INFO("[bridge_static_entry_add] keytype:%d,vlanId:%d,sourceLogicalPort:%d,destinationIdx:%d",entry_attrs.key.type
                                                                                                    ,entry_attrs.key.vlanId
                                                                                                    ,entry_attrs.sourceLogicalPort
                                                                                                    ,entry_attrs.destinationIdx);
    LOG_INFO("[bridge_static_entry_add] key mac address:%x:%x:%x:%x:%x:%x",entry_attrs.key.macAddress[0]
                                                                          ,entry_attrs.key.macAddress[1]
                                                                          ,entry_attrs.key.macAddress[2]
                                                                          ,entry_attrs.key.macAddress[3]
                                                                          ,entry_attrs.key.macAddress[4]
                                                                          ,entry_attrs.key.macAddress[5]);
    status = ncp_eioa_switch_bridge_entry_learn(inNcpHdl,&entry_attrs);
    LOG_INFO("[bridge_static_entry_add] status of ncp_eioa_switch_bridge_entry_learn :%d",status);
    return status;
}

ncp_st_t bridge_static_entry_delete(ofdpaFlowEntry_t *flow)
{

    ncp_eioa_switch_key_t key;
    memset(&key,0,sizeof(ncp_eioa_switch_bridge_entry_t));
    ncp_st_t status = NCP_ST_SUCCESS;
    key.type = NCP_EIOA_SWITCH_KEY_IVL;
    key.vlanId = flow->flowData.bridgingFlowEntry.match_criteria.vlanId;
    memcpy(key.macAddress,flow->flowData.bridgingFlowEntry.match_criteria.destMac.addr,6* sizeof(ncp_uint8_t));
    LOG_INFO("[bridge_static_entry_delete] keytype:%d,vlanId:%d",key.type,key.vlanId);
    LOG_INFO("[bridge_static_entry_delete] key mac address:%x:%x:%x:%x:%x:%x",key.macAddress[0]
                                                                          ,key.macAddress[1]
                                                                          ,key.macAddress[2]
                                                                          ,key.macAddress[3]
                                                                          ,key.macAddress[4]
                                                                          ,key.macAddress[5]);

    
    status = ncp_eioa_switch_bridge_entry_unlearn(inNcpHdl, &key);
    LOG_INFO("[bridge_static_entry_delete] status of ncp_eioa_switch_bridge_entry_unlearn :%d",status);
    return status;
}
ncp_st_t bridge_static_entry_modify(ofdpaFlowEntry_t *flow)
{
   return bridge_static_entry_add(flow);
}

#endif
