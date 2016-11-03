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
* @filename     rte_of_driver_mt.h
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
#ifdef RTE_MODE
#include <ind_of_util.h>
#include <unistd.h>
#include <ind_of_log.h>
#include <ncp.h>
#include "rte_of_driver_mt.h"
#include "RTEOfDriver_api.h"

void eioa_flow_add_ACL_vlan_Test1(void)
{
    ofdpaFlowEntry_t flow = {0};
    ncp_st_t status = NCP_ST_SUCCESS;
    flow.tableId = OFDPA_FLOW_TABLE_ID_ACL_POLICY;
    flow.priority = 0;
    LOG_INFO("eioa_flow_add_ACL_vlan_Test1");
    flow.flowData.policyAclFlowEntry.match_criteria.inPort = NCP_GMAC1;
    flow.flowData.policyAclFlowEntry.match_criteria.destMac.addr[0] = 0x00;
    flow.flowData.policyAclFlowEntry.match_criteria.destMac.addr[1] = 0x01;
    flow.flowData.policyAclFlowEntry.match_criteria.destMac.addr[2] = 0x01;
    flow.flowData.policyAclFlowEntry.match_criteria.destMac.addr[3] = 0x01;
    flow.flowData.policyAclFlowEntry.match_criteria.destMac.addr[4] = 0x01;
    flow.flowData.policyAclFlowEntry.match_criteria.destMac.addr[5] = 0x00;
    memset(flow.flowData.policyAclFlowEntry.match_criteria.destMacMask.addr,0xff,6);
    flow.flowData.policyAclFlowEntry.clearActions = 1;
    status = acl_rule_add(&flow);
}

void eioa_flow_add_ACL_vlan_Test2(void)
{
    ofdpaFlowEntry_t flow = {0};
    ncp_st_t status = NCP_ST_SUCCESS;
    flow.tableId = OFDPA_FLOW_TABLE_ID_ACL_POLICY;
    flow.priority = 1;
    LOG_INFO("eioa_flow_add_ACL_vlan_Test2");
    flow.flowData.policyAclFlowEntry.match_criteria.inPort = NCP_GMAC1;
    //flow.flowData.policyAclFlowEntry.match_criteria.destIp4= 0x0a0a1402;
    ///flow.flowData.policyAclFlowEntry.match_criteria.destIp4Mask= 32;
    flow.flowData.policyAclFlowEntry.match_criteria.vlanId = 3013;
    flow.flowData.policyAclFlowEntry.match_criteria.vlanIdMask = 0xffff;
    flow.flowData.policyAclFlowEntry.match_criteria.vlanPcp = 3;
    flow.flowData.policyAclFlowEntry.match_criteria.vlanPcpMask = 0xffff;
    flow.flowData.policyAclFlowEntry.clearActions = 0;
    flow.flowData.policyAclFlowEntry.vlanAction = 0;
    flow.flowData.policyAclFlowEntry.VlanId = 0;
    status = acl_rule_add(&flow);

}

void eioa_flow_add_ACL_vlan_Test3(void)
{
    ofdpaFlowEntry_t flow = {0};
    ncp_st_t status = NCP_ST_SUCCESS;
    flow.tableId = OFDPA_FLOW_TABLE_ID_ACL_POLICY;
    flow.priority = 2;
    LOG_INFO("eioa_flow_add_ACL_vlan_Test3");
    flow.flowData.policyAclFlowEntry.match_criteria.inPort = NCP_GMAC1;
    flow.flowData.policyAclFlowEntry.clearActions = 0;
    //flow.flowData.policyAclFlowEntry.vlanAction = 1;
    //flow.flowData.policyAclFlowEntry.VlanId = 20;
    status = acl_rule_add(&flow);

}

void eioa_flow_add_ACL_vlan_test4(void)
{
    ofdpaFlowEntry_t flow = {0};
    ncp_st_t status = NCP_ST_SUCCESS;
    flow.tableId = OFDPA_FLOW_TABLE_ID_ACL_POLICY;
    flow.flowData.policyAclFlowEntry.match_criteria.inPort = NCP_GMAC1;
    flow.priority = 1;
    LOG_INFO("%s",__FUNCTION__);
    status = acl_rule_delete(&flow);
}


void eioa_flow_add_ACL_vlan_test5(void)
{
    ofdpaFlowEntry_t flow = {0};
    ncp_st_t status = NCP_ST_SUCCESS;
    flow.tableId = OFDPA_FLOW_TABLE_ID_ACL_POLICY;
    flow.flowData.policyAclFlowEntry.match_criteria.inPort = NCP_GMAC1;
    flow.priority = 2;
    LOG_INFO("%s",__FUNCTION__);
    status = acl_rule_delete(&flow);
}

void eioa_flow_add_ACL_vlan_test6(void)
{
    ofdpaFlowEntry_t flow = {0};
    ncp_st_t status = NCP_ST_SUCCESS;
    flow.tableId = OFDPA_FLOW_TABLE_ID_ACL_POLICY;
    flow.priority = 3;
    flow.flowData.policyAclFlowEntry.match_criteria.inPort = NCP_GMAC1;
    LOG_INFO("%s",__FUNCTION__);
    status = acl_rule_delete(&flow);
}


void eioa_flow_add_bridge_static_entry_test1(void)
{
     ofdpaFlowEntry_t flow = {0};
     ncp_st_t status = NCP_ST_SUCCESS;
     LOG_INFO("eioa_flow_add_bridge_static_entry_test1");
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[0] = 0x00;
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[1] = 0x01;
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[2] = 0x01;
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[3] = 0x01;
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[4] = 0x01;
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[5] = 0x01;
     flow.flowData.bridgingFlowEntry.match_criteria.vlanId = 101;
     flow.flowData.bridgingFlowEntry.outputPort = NCP_GMAC18;
     flow.flowData.bridgingFlowEntry.match_criteria.tunnelId = NCP_GMAC17;
     status = bridge_static_entry_add(&flow);
}

void eioa_flow_add_bridge_static_entry_test2(void)
{
     ofdpaFlowEntry_t flow = {0};
     ncp_st_t status = NCP_ST_SUCCESS;
     LOG_INFO("eioa_flow_add_bridge_static_entry_test2");
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[0] = 0x00;
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[1] = 0x01;
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[2] = 0x01;
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[3] = 0x01;
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[4] = 0x02;
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[5] = 0x01;
     flow.flowData.bridgingFlowEntry.match_criteria.vlanId = 101;
     flow.flowData.bridgingFlowEntry.outputPort = NCP_GMAC17;
     flow.flowData.bridgingFlowEntry.match_criteria.tunnelId = NCP_GMAC18;
     status = bridge_static_entry_add(&flow);
}

void eioa_flow_add_bridge_static_entry_test3(void)
{
     ofdpaFlowEntry_t flow = {0};
     ncp_st_t status = NCP_ST_SUCCESS;
     LOG_INFO("eioa_flow_add_bridge_static_entry_test3");
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[0] = 0x11;
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[1] = 0x12;
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[2] = 0x11;
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[3] = 0x11;
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[4] = 0x11;
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[5] = 0x11;
     flow.flowData.bridgingFlowEntry.match_criteria.vlanId = 21;
     flow.flowData.bridgingFlowEntry.outputPort = NCP_GMAC1;
     status = bridge_static_entry_modify(&flow);
}

void eioa_flow_add_bridge_static_entry_test4(void)
{
     ofdpaFlowEntry_t flow = {0};
     ncp_st_t status = NCP_ST_SUCCESS;
     LOG_INFO("eioa_flow_add_bridge_static_entry_test4");
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[0] = 0x00;
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[1] = 0x11;
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[2] = 0x11;
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[3] = 0x11;
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[4] = 0x11;
     flow.flowData.bridgingFlowEntry.match_criteria.destMac.addr[5] = 0x13;
     flow.flowData.bridgingFlowEntry.match_criteria.vlanId = 3013;
     flow.flowData.bridgingFlowEntry.outputPort = NCP_GMAC0;
     flow.flowData.bridgingFlowEntry.match_criteria.tunnelId = NCP_GMAC1;
     status = bridge_static_entry_add(&flow);
}

void eioa_flow_add_ingress_map_entry_test1(void)
{
     ofdpaFlowEntry_t flow = {0};
     ncp_st_t status = NCP_ST_SUCCESS;
     LOG_INFO("eioa_flow_add_ingress_map_entry_test1");
     flow.flowData.IngressvlanFlowEntry.match_criteria.inPort = NCP_GMAC17;
     flow.flowData.IngressvlanFlowEntry.match_criteria.vlanId = 101;
     status = Ingress_Vlan_add(&flow);
     
}


void eioa_flow_add_ingress_map_entry_test2(void)
{
     ofdpaFlowEntry_t flow = {0};
     ncp_st_t status = NCP_ST_SUCCESS;
     LOG_INFO("eioa_flow_add_ingress_map_entry_test2");
     flow.flowData.IngressvlanFlowEntry.match_criteria.inPort = NCP_GMAC18;
     flow.flowData.IngressvlanFlowEntry.match_criteria.vlanId = 101;
     status = Ingress_Vlan_add(&flow);
     
}

void eioa_flow_add_ingress_map_entry_test3(void)
{
     ofdpaFlowEntry_t flow = {0};
     ncp_st_t status = NCP_ST_SUCCESS;
     LOG_INFO("eioa_flow_add_ingress_map_entry_test1");
     flow.flowData.IngressvlanFlowEntry.match_criteria.inPort = NCP_GMAC1;
     flow.flowData.IngressvlanFlowEntry.match_criteria.vlanId = 3013;
     status = Ingress_Vlan_add(&flow);
     
}

void eioa_flow_add_egress_map_entry_test1(void)
{
     ofdpaFlowEntry_t flow = {0};
     ncp_st_t status = NCP_ST_SUCCESS;
     LOG_INFO("eioa_flow_add_egress_map_entry_test1");
     flow.flowData.IngressvlanFlowEntry.match_criteria.inPort = NCP_GMAC17;
     flow.flowData.IngressvlanFlowEntry.match_criteria.vlanId = 101;
     flow.flowData.IngressvlanFlowEntry.newVlanId = 0;
     status = Egress_Vlan_add(&flow);
     
}

void eioa_flow_add_egress_map_entry_test2(void)
{
     ofdpaFlowEntry_t flow = {0};
     ncp_st_t status = NCP_ST_SUCCESS;
     LOG_INFO("eioa_flow_add_egress_map_entry_test2");
     flow.flowData.IngressvlanFlowEntry.match_criteria.inPort = NCP_GMAC18;
     flow.flowData.IngressvlanFlowEntry.match_criteria.vlanId = 101;
     flow.flowData.IngressvlanFlowEntry.newVlanId = 0;
     status = Egress_Vlan_add(&flow);
     
}

void eioa_flow_add_egress_map_entry_test3(void)
{
     ofdpaFlowEntry_t flow = {0};
     ncp_st_t status = NCP_ST_SUCCESS;
     LOG_INFO("eioa_flow_add_egress_map_entry_test1");
     flow.flowData.IngressvlanFlowEntry.match_criteria.inPort = NCP_GMAC0;
     flow.flowData.IngressvlanFlowEntry.match_criteria.vlanId = 3013;
     flow.flowData.IngressvlanFlowEntry.newVlanId = 0;
     status = Egress_Vlan_add(&flow);
     
}

void eioa_flow_add_egress_map_entry_test4(void)
{
     ofdpaFlowEntry_t flow = {0};
     ncp_st_t status = NCP_ST_SUCCESS;
     LOG_INFO("eioa_flow_add_egress_map_entry_test1");
     flow.flowData.IngressvlanFlowEntry.match_criteria.inPort = NCP_GMAC0;
     flow.flowData.IngressvlanFlowEntry.match_criteria.vlanId = 15;
     flow.flowData.IngressvlanFlowEntry.newVlanId = 0;
     status = Egress_Vlan_add(&flow);
     
}

void call_system_traffic(void)
{
     LOG_INFO("call traffic");
     system("ncpWrite 0x300.0.4 1");
}
#endif
