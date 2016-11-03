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
acl_rule_mapping_struct acl_mapping_table[32] = {0};
/*********************************************************************
* @purpose  conver ofdap flow to acl rule structure
*
* @param    flow    @b{(input)} structure containing flow entry parameters
* @param    rule    acl match rule structure
* @param    action  acl rule action
*
* @returns  ncp_st_t  
* @end
*********************************************************************/

ncp_st_t convert_flow_to_aclrule(ofdpaFlowEntry_t *flow,ncp_eioa_switch_acl_rule_t *rule,ncp_eioa_switch_acl_action_t *acl_action)
{
    

    rule->srcMacAddrs = (ncp_eioa_switch_acl_mac_addresses_t*)malloc(sizeof(ncp_eioa_switch_acl_mac_addresses_t));
    if (rule->srcMacAddrs == NULL)
    {
      LOG_ERROR("[convert_flow_to_aclrule] srcMacAddrs = NULL");
      return NCP_ST_NO_MEMORY;
    }
    else
    {

        rule->numSrcMacAddrs = 1;
        memcpy((void*)(rule->srcMacAddrs->address.value),(void*)(flow->flowData.policyAclFlowEntry.match_criteria.srcMac.addr),sizeof(uint8_t)*6);
        memcpy((void*)(rule->srcMacAddrs->mask.value),(void*)(flow->flowData.policyAclFlowEntry.match_criteria.srcMacMask.addr),sizeof(uint8_t)*6);
        LOG_INFO("[convert_flow_to_aclrule]src mac vlaue %x:%x:%x:%x:%x:%x",rule->srcMacAddrs->address.value[0]
                                                                             ,rule->srcMacAddrs->address.value[1]
                                                                             ,rule->srcMacAddrs->address.value[2]
                                                                             ,rule->srcMacAddrs->address.value[3]
                                                                             ,rule->srcMacAddrs->address.value[4]
                                                                             ,rule->srcMacAddrs->address.value[5]);

        LOG_INFO("[convert_flow_to_aclrule] src mac maskvlaue %x:%x:%x:%x:%x:%x",rule->srcMacAddrs->mask.value[0]
                                                                                  ,rule->srcMacAddrs->mask.value[1]
                                                                                  ,rule->srcMacAddrs->mask.value[2]
                                                                                  ,rule->srcMacAddrs->mask.value[3]
                                                                                  ,rule->srcMacAddrs->mask.value[4]
                                                                                  ,rule->srcMacAddrs->mask.value[5]);

    }

    rule->destMacAddrs = (ncp_eioa_switch_acl_mac_addresses_t*)malloc(sizeof(ncp_eioa_switch_acl_mac_addresses_t));
    if (rule->destMacAddrs == NULL)
    {
        LOG_ERROR("[convert_flow_to_aclrule] destMacAddrs = NULL");
        return NCP_ST_NO_MEMORY;
    }
    else
    {

        rule->numDestMacAddrs = 1;
        memcpy((void*)(rule->destMacAddrs->address.value),(void*)(flow->flowData.policyAclFlowEntry.match_criteria.destMac.addr),sizeof(uint8_t)*6);
        memcpy((void*)(rule->destMacAddrs->mask.value),(void*)(flow->flowData.policyAclFlowEntry.match_criteria.destMacMask.addr),sizeof(uint8_t)*6);
        LOG_INFO("[convert_flow_to_aclrule]dest mac vlaue %x:%x:%x:%x:%x:%x",rule->destMacAddrs->address.value[0]
                                                                              ,rule->destMacAddrs->address.value[1]
                                                                              ,rule->destMacAddrs->address.value[2]
                                                                              ,rule->destMacAddrs->address.value[3]
                                                                              ,rule->destMacAddrs->address.value[4]
                                                                              ,rule->destMacAddrs->address.value[5]);

        LOG_INFO("[convert_flow_to_aclrule]dest mac maskvlaue %x:%x:%x:%x:%x:%x",rule->destMacAddrs->mask.value[0]
                                                                                  ,rule->destMacAddrs->mask.value[1]
                                                                                  ,rule->destMacAddrs->mask.value[2]
                                                                                  ,rule->destMacAddrs->mask.value[3]
                                                                                  ,rule->destMacAddrs->mask.value[4]
                                                                                  ,rule->destMacAddrs->mask.value[5]);

    }

    uint32_t ip_addr = flow->flowData.policyAclFlowEntry.match_criteria.sourceIp4;

    rule->srcIpAddrs = (ncp_eioa_switch_acl_ip_subnet_t*)malloc(sizeof(ncp_eioa_switch_acl_ip_subnet_t));
    if (rule->srcIpAddrs == NULL)
    {
        LOG_INFO("[convert_flow_to_aclrule] srcIpAddrs = NULL");
        return NCP_ST_NO_MEMORY;
    }
    else
    {
        rule->numSrcIpAddrs = 1;
        memset(rule->srcIpAddrs->address.value,0,16);
        rule->srcIpAddrs->address.value[12] = GETU8CHAR(ip_addr, 24);
        rule->srcIpAddrs->address.value[13] = GETU8CHAR(ip_addr, 16);
        rule->srcIpAddrs->address.value[14] = GETU8CHAR(ip_addr, 8);
        rule->srcIpAddrs->address.value[15] = GETU8CHAR(ip_addr, 0);
        rule->srcIpAddrs->prefixLength = flow->flowData.policyAclFlowEntry.match_criteria.sourceIp4Mask;
        LOG_INFO("[convert_flow_to_aclrule] src IP vlaue %d",rule->srcIpAddrs->address.value[12]
                                                              ,rule->srcIpAddrs->address.value[13]
                                                              ,rule->srcIpAddrs->address.value[14]
                                                              ,rule->srcIpAddrs->address.value[15]);
        LOG_INFO("[convert_flow_to_aclrule] src prefixLength 0x%x\n",rule->srcIpAddrs->prefixLength);

    }




    ip_addr = flow->flowData.policyAclFlowEntry.match_criteria.destIp4;
    rule->destIpAddrs= (ncp_eioa_switch_acl_ip_subnet_t*)malloc(sizeof(ncp_eioa_switch_acl_ip_subnet_t));
    if (rule->destIpAddrs == NULL)
    {
        LOG_INFO("[convert_flow_to_aclrule] destIpAddrs = NULL");
        return NCP_ST_NO_MEMORY;
    }
    else
    {
        rule->numDestIpAddrs = 1;
        memset(rule->destIpAddrs->address.value,0,16);
        rule->destIpAddrs->address.value[12] = GETU8CHAR(ip_addr, 24);
        rule->destIpAddrs->address.value[13] = GETU8CHAR(ip_addr, 16);
        rule->destIpAddrs->address.value[14] = GETU8CHAR(ip_addr, 8);
        rule->destIpAddrs->address.value[15] = GETU8CHAR(ip_addr, 0);
        rule->destIpAddrs->prefixLength = flow->flowData.policyAclFlowEntry.match_criteria.destIp4Mask;
        LOG_INFO("[convert_flow_to_aclrule]dest IP vlaue %d",rule->destIpAddrs->address.value[12]
                                                              ,rule->destIpAddrs->address.value[13]
                                                              ,rule->destIpAddrs->address.value[14]
                                                              ,rule->destIpAddrs->address.value[15]);
        LOG_INFO("[convert_flow_to_aclrule]src prefixLength 0x%x",rule->destIpAddrs->prefixLength);

    }


    rule->srcLayer4Ports = (ncp_eioa_switch_acl_layer4_port_range_t*)malloc(sizeof(ncp_eioa_switch_acl_layer4_port_range_t));
    if (rule->srcLayer4Ports == NULL)
    {
       LOG_INFO("[convert_flow_to_aclrule] srcLayer4Ports = NULL");
        return NCP_ST_NO_MEMORY;
    }
    else
    {
        rule->numSrcLayer4Ports = 1;
        rule->srcLayer4Ports->high = 0xffff;
        rule->srcLayer4Ports->low = flow->flowData.policyAclFlowEntry.match_criteria.srcL4Port;
        LOG_INFO("[convert_flow_to_aclrule] srcLayer4Ports high 0x%x",rule->srcLayer4Ports->high);
        LOG_INFO("[convert_flow_to_aclrule] srcLayer4Ports low 0x%x",rule->srcLayer4Ports->low);


    }


    rule->destLayer4Ports = (ncp_eioa_switch_acl_layer4_port_range_t*)malloc(sizeof(ncp_eioa_switch_acl_layer4_port_range_t));
    if (rule->destLayer4Ports == NULL)
    {
        LOG_INFO("[convert_flow_to_aclrule] destLayer4Ports = NULL");
        return NCP_ST_NO_MEMORY;
    }
    else
    {
        rule->numDestLayer4Ports = 1;
        rule->destLayer4Ports->high = 0xffff;
        rule->destLayer4Ports->low = flow->flowData.policyAclFlowEntry.match_criteria.destL4Port;
        LOG_INFO("[convert_flow_to_aclrule] destLayer4Ports high 0x%x",rule->destLayer4Ports->high);
        LOG_INFO("[convert_flow_to_aclrule] destLayer4Ports low 0x%x",rule->destLayer4Ports->low);
    }


    rule->dscpVals = (ncp_eioa_switch_acl_dscp_t*)malloc(sizeof(ncp_eioa_switch_acl_dscp_t));
    if (rule->dscpVals == NULL)
    {
        LOG_INFO("[convert_flow_to_aclrule] dscpVals = NULL");
        return NCP_ST_NO_MEMORY;
    }
    else
    {
        rule->numDscpVals = 1;
        if ((flow->flowData.policyAclFlowEntry.match_criteria.dscp == 0) && (flow->flowData.policyAclFlowEntry.match_criteria.dscpMask == 0))
        {
           rule->dscpVals->value = 0;
           rule->dscpVals->prefixLength = 0;
        }
        else
        {
            rule->dscpVals->value = flow->flowData.policyAclFlowEntry.match_criteria.dscp;
            rule->dscpVals->prefixLength = 6;


        }
        LOG_INFO("[convert_flow_to_aclrule]dscpVals  0x%x",rule->dscpVals->value);
        LOG_INFO("[convert_flow_to_aclrule]prefixLength 0x%x",rule->dscpVals->prefixLength);

    }

 
    rule->cosVals = (ncp_eioa_switch_acl_cos_t*)malloc(sizeof(ncp_eioa_switch_acl_cos_t));
    if (rule->dscpVals == NULL)
    {
        LOG_INFO("[convert_flow_to_aclrule] dscpVals = NULL");
        return NCP_ST_NO_MEMORY;
    }
    else
    {
        rule->numCosVals = 1;
        if ((flow->flowData.policyAclFlowEntry.match_criteria.vlanPcp == 0) && (flow->flowData.policyAclFlowEntry.match_criteria.vlanPcpMask == 0))
        {
            rule->cosVals->value = 0;
            rule->cosVals->prefixLength = 0;
        }
        else
        {
            rule->cosVals->value = flow->flowData.policyAclFlowEntry.match_criteria.vlanPcp;
            rule->cosVals->prefixLength = 3;

        }

        LOG_INFO("[convert_flow_to_aclrule] number of cosval:%d",rule->numCosVals);
        LOG_INFO("[convert_flow_to_aclrule] cosVals  0x%x",rule->cosVals->value);
        LOG_INFO("[convert_flow_to_aclrule] prefixLength 0x%x",rule->cosVals->prefixLength);

    }


    rule->ethertypeVals = (ncp_eioa_switch_acl_ethertype_t*)malloc(sizeof(ncp_eioa_switch_acl_ethertype_t));
    rule->numEthertypeVals = 1;

    if (rule->ethertypeVals == NULL)
    {
        LOG_INFO("[convert_flow_to_aclrule] ethertypeVals = NULL");
        return NCP_ST_NO_MEMORY;
    }
    else
    {
        if (flow->flowData.policyAclFlowEntry.match_criteria.etherType == 0)
        {
           *(rule->ethertypeVals) = NCP_EIOA_SWITCH_ACL_ETHERTYPE_ANY;
        }
        else
        {
           *(rule->ethertypeVals) = flow->flowData.policyAclFlowEntry.match_criteria.etherType;
        }
        LOG_INFO("[convert_flow_to_aclrule] ethertypeVals = %x",*(rule->ethertypeVals));

    }


    rule->ipProtocolVals = (ncp_eioa_switch_acl_ip_protocol_t*)malloc(sizeof(ncp_eioa_switch_acl_ip_protocol_t));
    rule->numIpProtocolVals = 1;
    if (rule->ipProtocolVals == NULL)
    {
        LOG_INFO("[convert_flow_to_aclrule] ipProtocolVals = NULL");
        return NCP_ST_NO_MEMORY;
    }
    else
    {
        if (flow->flowData.policyAclFlowEntry.match_criteria.ipProto == 0)
        {
           *(rule->ipProtocolVals) = NCP_EIOA_SWITCH_ACL_IP_PROTOCOL_ANY;
        }
        else
        {
           *(rule->ipProtocolVals) = flow->flowData.policyAclFlowEntry.match_criteria.ipProto;
        }
        LOG_INFO("[convert_flow_to_aclrule] ipProtocolVals = %x",*(rule->ipProtocolVals));

    }

    rule->vlanIdVals = (ncp_eioa_switch_acl_vlan_id_t*)malloc(sizeof(ncp_eioa_switch_acl_vlan_id_t));
    rule->numVlanIds = 1;
    if (rule->vlanIdVals == NULL)
    {
        LOG_INFO("[convert_flow_to_aclrule] vlanIdVals = NULL");
        return NCP_ST_NO_MEMORY;

    }
    else
    {
        if ((flow->flowData.policyAclFlowEntry.match_criteria.vlanId == 0)&&(flow->flowData.policyAclFlowEntry.match_criteria.vlanIdMask == 0))
        {
           rule->vlanIdVals->prefixLength = 0;
           rule->vlanIdVals->value = 0;
        }
        else
        {
           rule->vlanIdVals->prefixLength = 12;
           rule->vlanIdVals->value = flow->flowData.policyAclFlowEntry.match_criteria.vlanId;
        }
        LOG_INFO("[convert_flow_to_aclrule] vlanIdVals prefixLength = %d",rule->vlanIdVals->prefixLength);
        LOG_INFO("[convert_flow_to_aclrule] vlanIdVals id = %d",rule->vlanIdVals->value);
    }
    rule->numEncryptionModes = 1;
    rule->encryptionModes = (ncp_eioa_switch_acl_encryption_mode_t*)malloc(sizeof(ncp_eioa_switch_acl_encryption_mode_t));
    if (rule->encryptionModes != NULL)
       *(rule->encryptionModes) = NCP_EIOA_SWITCH_ACL_ENCRYPTION_MODE_ANY;
    else
    {
        LOG_INFO("[convert_flow_to_aclrule] encryptionModes = NULL");
        return NCP_ST_NO_MEMORY;
    }

    /***ACL ACTION ****/
    acl_action->permit = (flow->flowData.policyAclFlowEntry.clearActions == 1)?0:1;
    if (flow->flowData.policyAclFlowEntry.dscpAction == 0)
    {
      acl_action->trustMode = NCP_EIOA_SWITCH_ACL_TRUST_MODE_TRUST_IP_PRECEDENCE;
    }
    else
    {
      acl_action->trustMode = NCP_EIOA_SWITCH_ACL_TRUST_MODE_NOT_TRUSTED;
      acl_action->dscpValue.value = flow->flowData.policyAclFlowEntry.dscp;
      acl_action->dscpValue.prefixLength = 6;
    }
    LOG_INFO("[convert_flow_to_aclrule] action:permit %d",acl_action->permit);
    if (flow->flowData.policyAclFlowEntry.vlanAction != 0)
    {
       acl_action->newVlanId.value= flow->flowData.policyAclFlowEntry.VlanId;
       acl_action->newVlanId.prefixLength = 12;
       acl_action->changeVlanId = TRUE;
    }
    else
    {
       acl_action->changeVlanId = FALSE;
    }
    
    LOG_INFO("[convert_flow_to_aclrule] action:changevlan %d,vlanid %d,vlan prefixlength :%d",acl_action->changeVlanId,acl_action->newVlanId.value,acl_action->newVlanId.prefixLength);
    return NCP_ST_SUCCESS;
}

uint32_t get_aclid_from_port(uint32_t port)
{
   if (port <=  NCP_GMAC1) 
      return port;
   if (port == NCP_GMAC49)
	   return 3;
   if (port == NCP_XGMAC16)
       return 8;
   if (port == NCP_GMAC17)
       return 9;
   if (port == NCP_GMAC18)
       return (10);
   if (port == NCP_GMAC19)
       return (11);
   if (port == NCP_GMAC20)
       return (12);
   return 0;

}
/*********************************************************************
* @purpose  save the mapping table to memory
*
* @param    aclid    acl group id
* @param    rule_id_from_of  the rule id from of prority
* @param    rule_id_in_acl   the rule id in the acl memory
* @param    *ruleid mapped rule id
* @returns  ncp_st_t  
* @end
*********************************************************************/
ncp_st_t acl_mapping_table_save(ncp_uint32_t aclid,ncp_uint32_t rule_id_from_of,ncp_uint32_t rule_id_in_acl)
{
   acl_mapping_table[aclid].aclid = aclid;
   acl_mapping_table[aclid].flag = TRUE;
   acl_mapping_table[aclid].rule_id_mapping[rule_id_from_of].flag = TRUE;
   acl_mapping_table[aclid].rule_id_mapping[rule_id_from_of].rule_id_from_of = rule_id_from_of;
   acl_mapping_table[aclid].rule_id_mapping[rule_id_from_of].rule_id_in_acl = rule_id_in_acl;
   return NCP_ST_SUCCESS;
}
/*********************************************************************
* @purpose  delete the mapping table in the  memory
*
* @param    aclid    acl group id
* @param    rule_id_from_of  the rule id from of prority
* @param    rule_id_in_acl   the rule id in the acl memory
* @param    *ruleid mapped rule id
* @returns  ncp_st_t  
* @end
*********************************************************************/

ncp_st_t acl_mapping_table_delete(ncp_uint32_t aclid,ncp_uint32_t rule_id_from_of,ncp_uint32_t rule_id_in_acl)
{
   ncp_uint8_t count = 0;
   ncp_uint8_t i = 0;
   if (acl_mapping_table[aclid].rule_id_mapping[rule_id_from_of].flag == TRUE)
   {
       acl_mapping_table[aclid].rule_id_mapping[rule_id_from_of].flag = FALSE;
       acl_mapping_table[aclid].rule_id_mapping[rule_id_from_of].rule_id_from_of = 0;
       acl_mapping_table[aclid].rule_id_mapping[rule_id_from_of].rule_id_in_acl = 0;
       for (i = 0; i < 16; i++)
       {
           if (acl_mapping_table[aclid].rule_id_mapping[i].flag == TRUE)
           {
               if (acl_mapping_table[aclid].rule_id_mapping[i].rule_id_in_acl > rule_id_in_acl)
               {
                 if (acl_mapping_table[aclid].rule_id_mapping[i].rule_id_in_acl > 0 )
                    acl_mapping_table[aclid].rule_id_mapping[i].rule_id_in_acl--;
               }
           }
       }
       return NCP_ST_SUCCESS;

   }
   else
   {
      return NCP_ST_ERROR;
   }

}
/*********************************************************************
* @purpose  get the mapped rule id
*
* @param    aclid    acl group id
* @param    rule_id_from_of  the rule id from of prority
* @param    action  ACL_RULE_ADD_OR_DELETE
* @param    *ruleid mapped rule id
* @returns  ncp_st_t  
* @end
*********************************************************************/

ncp_st_t get_mapped_rule_id(ncp_uint32_t aclid,ncp_uint32_t rule_id_from_of,ACL_RULE_ADD_OR_DELETE action,ncp_uint32_t *ruleid)
{
   ncp_st_t status = NCP_ST_SUCCESS;
   ncp_uint32_t num_rules = 0;
   if (action == ACL_RULE_ADD)
   {
      status = ncp_eioa_switch_acl_num_rules_get(inNcpHdl,aclid,&num_rules);
      if (status != NCP_ST_SUCCESS)
      { 
          return status; 
      }

  
      if (rule_id_from_of >= num_rules)
      {
          *ruleid = num_rules;
      }
      else
      {
          *ruleid = rule_id_from_of;
      }
      if (acl_mapping_table[aclid].rule_id_mapping[rule_id_from_of].flag != FALSE)
      {
           return NCP_ST_ERROR;
      }
      else
      {
           return NCP_ST_SUCCESS;
      }

    }
   if (action == ACL_RULE_DELETE)
   {
       if (acl_mapping_table[aclid].rule_id_mapping[rule_id_from_of].flag == TRUE)
       {
           *ruleid = acl_mapping_table[aclid].rule_id_mapping[rule_id_from_of].rule_id_in_acl;
           return NCP_ST_SUCCESS;
       }
       else
       {
           return NCP_ST_ERROR;
       }
   }
}
/*********************************************************************
* @purpose  Add a new entry to acl talbe
*
* @param    flow    @b{(input)} structure containing flow entry parameters
*
* @returns  ncp_st_t  
* @end
*********************************************************************/

ncp_st_t acl_rule_add(ofdpaFlowEntry_t *flow)
{
    ncp_eioa_switch_acl_rule_t rule = {0};
    ncp_eioa_switch_acl_action_t action = {0};
    ncp_st_t status = NCP_ST_SUCCESS;
    ncp_uint32_t aclid = 0 ;
    ncp_uint32_t ruleid = 0;
    ACL_RULE_ADD_OR_DELETE acl_add_or_delete;
    LOG_INFO("acl_rule_add");
    if (flow->priority > 15)
    {
       LOG_ERROR("the ACL rule id can't larger than 15");
       return NCP_ST_ERROR;
    }    
    status = convert_flow_to_aclrule(flow, &rule, &action);
    if (NCP_ST_SUCCESS == status)
    {
        aclid = get_aclid_from_port(flow->flowData.policyAclFlowEntry.match_criteria.inPort);
        status = get_mapped_rule_id(aclid,flow->priority,ACL_RULE_ADD,&ruleid);
        LOG_INFO("[acl_rule_add] status of get_mapped_rule_id:%d",status);
        LOG_INFO("[acl_rule_add] acl id = %d",aclid);
        LOG_INFO("[acl_rule_add] of rule id:%d, acl rule id:%d",flow->priority,ruleid);
        //aclid = 1;
        /*status = ncp_eioa_switch_acl_append(inNcpHdl,flow.priority,&rule,&action);*/
        status = ncp_eioa_switch_acl_insert(inNcpHdl, aclid, ruleid, &rule,&action);
        LOG_INFO("[acl_rule_add] status of ncp_eioa_switch_acl_insert:%d",status);
        if (status != NCP_ST_SUCCESS)
        {
           return status;
        }
        status = ncp_eioa_switch_acl_build(inNcpHdl);
        LOG_INFO("[acl_rule_add] ncp_eioa_switch_acl_build status:%d",status);
        if (status == NCP_ST_SUCCESS)
        {
          status = acl_mapping_table_save(aclid,flow->priority,ruleid);
          LOG_INFO("[acl_rule_add] acl_mapping_table_save status:%d",status);
        }
        return status;
        
    }
    else
    {
       return status;
    }


}

/*********************************************************************
* @purpose  delete a new entry to acl talbe
*
* @param    flow    @b{(input)} structure containing flow entry parameters
*
* @returns  ncp_st_t  
* @end
*********************************************************************/

ncp_st_t acl_rule_delete(ofdpaFlowEntry_t *flow)
{
   ncp_st_t status = NCP_ST_SUCCESS;
   ncp_uint32_t aclid = 0 ;
   ncp_uint32_t ruleid = 0;

   aclid = get_aclid_from_port(flow->flowData.policyAclFlowEntry.match_criteria.inPort);
   status = get_mapped_rule_id(aclid,flow->priority,ACL_RULE_DELETE,&ruleid);
   LOG_INFO("[acl_rule_delete] status of get_mapped_rule_id:%d",status);
   if (status == NCP_ST_SUCCESS)
   {
        LOG_INFO("[acl_rule_delete] acl id = %d",aclid);
        LOG_INFO("[acl_rule_delete] of rule id:%d, acl rule id:%d",flow->priority,ruleid);
        status = ncp_eioa_switch_acl_delete(inNcpHdl,aclid,ruleid);
        LOG_INFO("[acl_rule_delete] acl_rule_delete status:%d",status);
        if (status == NCP_ST_SUCCESS)
        {
            status = ncp_eioa_switch_acl_build(inNcpHdl);
            LOG_INFO("[acl_rule_add] ncp_eioa_switch_acl_build status:%d",status);
            if (status == NCP_ST_SUCCESS)
            {
               status = acl_mapping_table_delete(aclid,flow->priority,ruleid);
            }
        }

   }
   return status;
}

#endif

