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
#ifndef INCLUDE_RTE_OF_DRIVER_API_H
#define INCLUDE_RTE_OF_DRIVER_API_H
#if defined RTE_MODE_MT || defined RTE_CFG_LOAD
void eioa_flow_add_ACL_vlan_Test1(void);
void eioa_flow_add_ACL_vlan_Test2(void);
void eioa_flow_add_ACL_vlan_Test3(void);
void eioa_flow_add_ACL_vlan_test4(void);
void eioa_flow_add_ACL_vlan_test5(void);
void eioa_flow_add_ACL_vlan_test6(void);


void eioa_flow_add_bridge_static_entry_test1(void);
void eioa_flow_add_bridge_static_entry_test2(void);
void eioa_flow_add_bridge_static_entry_test3(void);
void eioa_flow_add_bridge_static_entry_test4(void);

void eioa_flow_add_ingress_map_entry_test1(void);
void eioa_flow_add_ingress_map_entry_test2(void);
void eioa_flow_add_ingress_map_entry_test3(void);

void eioa_flow_add_egress_map_entry_test1(void);
void eioa_flow_add_egress_map_entry_test2(void);
void eioa_flow_add_egress_map_entry_test3(void);
void eioa_flow_add_egress_map_entry_test4(void);


void call_system_traffic(void);
#endif

#endif
