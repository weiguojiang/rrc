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
* @filename     RTEOfDriverACL.h
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
* @purpose  Add a new entry to acl talbe
*
* @param    flow    @b{(input)} structure containing flow entry parameters
*
* @returns  ncp_st_t  
* @end
*********************************************************************/

ncp_st_t Ingress_Vlan_add(ofdpaFlowEntry_t *flow)
{
    ncp_st_t status = NCP_ST_SUCCESS;
    ncp_st_t status2 = NCP_ST_SUCCESS;
    uint32_t port=0;
    ncp_uint16_t vlan=0;
    ncp_bool_t one2oneSvlan=0;
    
    LOG_INFO("Ingress_Vlan_add ");

    port = flow->flowData.IngressvlanFlowEntry.match_criteria.inPort;
    vlan = flow->flowData.IngressvlanFlowEntry.match_criteria.vlanId;
    
    status = ncp_eioa_port_ingress_vlan_set(inNcpHdl,port,vlan,one2oneSvlan);
    LOG_INFO("%s %d: set status %d,port %d vlan %d ",__FUNCTION__,__LINE__,status,port,vlan);

    //status2 = ncp_eioa_port_ingress_vlan_get(inNcpHdl,port,vlan,&one2oneSvlan);
    //LOG_INFO("%s %d: get status %d,port %d vlan %d ",__FUNCTION__,__LINE__,status2,port,vlan);
    return status;
}

ncp_st_t Ingress_Vlan_delete(ofdpaFlowEntry_t *flow)
{
    ncp_st_t status = NCP_ST_SUCCESS;
    ncp_st_t status2 = NCP_ST_SUCCESS;
    uint32_t port=0;
    ncp_uint16_t vlan=0;
    ncp_bool_t one2oneSvlan=0;
    
    LOG_INFO("Ingress_Vlan_add ");

    port = flow->flowData.IngressvlanFlowEntry.match_criteria.inPort;
    vlan = flow->flowData.IngressvlanFlowEntry.match_criteria.vlanId;
    
    status = ncp_eioa_port_ingress_vlan_rem(inNcpHdl,port,vlan);
    LOG_INFO("%s %d: set status %d,port %d vlan %d ",__FUNCTION__,__LINE__,status,port,vlan);

    //status2 = ncp_eioa_port_ingress_vlan_get(inNcpHdl,port,vlan,&one2oneSvlan);
    //LOG_INFO("%s %d: get status %d,port %d vlan %d ",__FUNCTION__,__LINE__,status2,port,vlan);
    return status;
}

#endif


