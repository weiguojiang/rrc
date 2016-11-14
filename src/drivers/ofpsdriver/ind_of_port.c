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
* @filename     ind_ofdpa_port.c
*
* @purpose      OF-DPA Driver for Indigo
*
* @component    OF-DPA
*
* @comments     none
*
* @create       6 Nov 2013
*
* @end
*
**********************************************************************/

#include <linux/if_ether.h>
#include "indigo/port_manager.h"
#include "indigo/of_state_manager.h"
#include "ind_ofdpa_util.h"
#include "ind_ofdpa_log.h"
#include "indigo/error.h"
#include "loci/of_match.h"
#include "loci/loci.h"
#include "ofdpa_api.h"

#ifdef RTE_MODE
#include <ncp.h>
extern ncp_hdl_t inNcpHdl;
#endif
extern int ofagent_of_version;

static indigo_error_t ind_ofdpa_queue_stats_set(of_port_no_t req_of_port_num, 
                                                uint32_t req_of_port_queue_id, 
                                                of_list_queue_stats_entry_t *list);

static indigo_error_t ind_ofdpa_port_stats_set(uint32_t port, of_list_port_stats_entry_t *list);

static indigo_error_t ind_ofdpa_queue_config_queue_set(of_packet_queue_t *of_packet_queue, 
                                                       of_port_no_t port, 
                                                       uint32_t queueId);

static indigo_error_t ind_ofdpa_queue_config_queue_set(of_packet_queue_t *of_packet_queue, 
                                                       uint32_t port, uint32_t queueId)
{
  indigo_error_t err = INDIGO_ERROR_NONE;
  OFDPA_ERROR_t ofdpa_rv = OFDPA_E_NONE;
  uint32_t minRate, maxRate;
  of_list_queue_prop_t of_list_queue_prop;
  of_queue_prop_t of_queue_prop; 
  of_queue_prop_min_rate_t *min_rate;
  of_queue_prop_max_rate_t *max_rate;

  min_rate = &of_queue_prop;
  max_rate = &of_queue_prop;

  /* Set the queue id: id for the specific queue. */
  of_packet_queue_queue_id_set(of_packet_queue, queueId);
    
  /* Set the port: Port this queue is attached to. */
  of_packet_queue_port_set(of_packet_queue, port);

  ofdpa_rv = ofdpaQueueRateGet(port, queueId, &minRate, &maxRate);
  if (ofdpa_rv != OFDPA_E_NONE)
  { 
    LOG_ERROR("Failed to get port queue min and max rates. (ofdpa_rv = %d)", ofdpa_rv);
    err = (indigoConvertOfdpaRv(ofdpa_rv));
  }
  else
  {
    of_packet_queue_properties_bind(of_packet_queue, &of_list_queue_prop);

    of_queue_prop_min_rate_init(min_rate, of_packet_queue->version, -1, 1);
    of_list_queue_prop_append_bind(&of_list_queue_prop, (of_queue_prop_t *)min_rate);
    of_queue_prop_min_rate_rate_set(min_rate, (uint16_t)minRate);


    of_queue_prop_max_rate_init(max_rate, of_packet_queue->version, -1, 1);
    of_list_queue_prop_append_bind(&of_list_queue_prop, (of_queue_prop_t *)max_rate);
    of_queue_prop_max_rate_rate_set(max_rate, (uint16_t)maxRate);

  }

  return err;
}


static indigo_error_t ind_ofdpa_port_stats_set(uint32_t port, of_list_port_stats_entry_t *list)
{
  OFDPA_ERROR_t ofdpa_rv = OFDPA_E_NONE; 
  ofdpaPortStats_t portStats;
  of_port_stats_entry_t entry[1];

  of_port_stats_entry_init(entry, list->version, -1, 1);
  if (of_list_port_stats_entry_append_bind(list, entry) < 0)
  {
    LOG_ERROR("too many port stats replies");
    return INDIGO_ERROR_UNKNOWN;
  }

  memset(&portStats, 0, sizeof(portStats));
  ofdpa_rv = ofdpaPortStatsGet(port, &portStats);
  if (ofdpa_rv != OFDPA_E_NONE)
  {
    //LOG_ERROR("Failed to get stats on port %d.", port);
  }

  of_port_stats_entry_port_no_set(entry, port);
  of_port_stats_entry_rx_packets_set(entry, portStats.rx_packets);
  of_port_stats_entry_tx_packets_set(entry, portStats.tx_packets);
  of_port_stats_entry_rx_bytes_set(entry, portStats.rx_bytes);
  of_port_stats_entry_tx_bytes_set(entry, portStats.tx_bytes);
  of_port_stats_entry_rx_errors_set(entry, portStats.rx_errors);
  of_port_stats_entry_tx_errors_set(entry, portStats.tx_errors);
  of_port_stats_entry_rx_dropped_set(entry, portStats.rx_drops);
  of_port_stats_entry_tx_dropped_set(entry, portStats.tx_drops);
  if (entry->version < OF_VERSION_1_4) {
      of_port_stats_entry_rx_frame_err_set(entry, portStats.rx_frame_err);
      of_port_stats_entry_rx_over_err_set(entry, portStats.rx_over_err);
      of_port_stats_entry_rx_crc_err_set(entry, portStats.rx_crc_err);
      of_port_stats_entry_collisions_set(entry, portStats.collisions);
  }
  of_port_stats_entry_duration_sec_set(entry, portStats.duration_seconds); 
//  of_port_stats_entry_duration_nsec_set(entry, portStats.duration_nseconds);

  return (indigoConvertOfdpaRv(ofdpa_rv));
}

static indigo_error_t ind_ofdpa_queue_stats_set(of_port_no_t port, 
                                                uint32_t req_of_port_queue_id, 
                                                of_list_queue_stats_entry_t *list)
{
  indigo_error_t err = INDIGO_ERROR_NONE;
  ofdpaPortQueueStats_t queueStats;
  OFDPA_ERROR_t	ofdpa_rv = OFDPA_E_NONE;
  uint32_t numQueues;
  uint32_t queueId;
  uint32_t all_queues = 0;
  of_queue_stats_entry_t entry[1];


  /* Check if the request if for all queues (OFPQ_ALL) */ 
  if (req_of_port_queue_id == OF_QUEUE_ALL_BY_VERSION(list->version))
  {   
    queueId = 0;
    all_queues = 1;
  } 
  else
  { 
    queueId = req_of_port_queue_id;
  }  

  ofdpa_rv = ofdpaNumQueuesGet(port, &numQueues);
  if (ofdpa_rv != OFDPA_E_NONE)
  {
    LOG_ERROR("Failed to get no. of port queues. (ofdpa_rv = %d)", ofdpa_rv);
    return (indigoConvertOfdpaRv(ofdpa_rv));
  }

  if (queueId >= numQueues)
  {
    LOG_ERROR("Invalid queue Id (queueId = %d)", queueId); 
    return INDIGO_ERROR_RANGE;
  }

  while (queueId < numQueues)
  {
    of_queue_stats_entry_init(entry, list->version, -1, 1);
    if (of_list_queue_stats_entry_append_bind(list, entry) < 0)
    {
      LOG_ERROR("Too many queue stats replies.");
      return INDIGO_ERROR_RESOURCE;
    }
    ofdpa_rv = ofdpaQueueStatsGet(port, queueId, &queueStats);
    if (ofdpa_rv != OFDPA_E_NONE)
    {
      LOG_ERROR("Failed to queue stats for port %d on queue %d.", port, queueId);
      err = indigoConvertOfdpaRv(ofdpa_rv);
      break;
    }
    of_queue_stats_entry_port_no_set(entry, port);
    of_queue_stats_entry_queue_id_set(entry, queueId);
    of_queue_stats_entry_tx_bytes_set(entry, queueStats.txBytes);
    of_queue_stats_entry_tx_packets_set(entry, queueStats.txPkts);
    of_queue_stats_entry_tx_errors_set(entry, 0);
    of_queue_stats_entry_duration_sec_set(entry, queueStats.duration_seconds);
    of_queue_stats_entry_duration_nsec_set(entry, (queueStats.duration_seconds)*IND_OFDPA_NANO_SEC);


    /* Check if the queueId is all queues OFPQ_ALL */
    if (!all_queues)
    {
      break;
    }

    queueId++;
  }

  return err;
}

/* Set the port features in LOCI structure 
 * Parameters:                             
 *    port          (input)   Port number 
 *    of_port_desc  (output)  Port description LOCI object
 */
static indigo_error_t ind_ofdpa_port_features_set(of_port_no_t port, 
                                                  of_port_desc_t *of_port_desc)
{
  OFDPA_ERROR_t ofdpa_rv = OFDPA_E_NONE;
  ofdpaPortFeature_t  features;

  ofdpa_rv = ofdpaPortFeatureGet(port, &features); 
  if (ofdpa_rv != OFDPA_E_NONE)
  {
    LOG_ERROR("Error getting port features");
    return (indigoConvertOfdpaRv(ofdpa_rv));
  }

  /* Port Current Features */
  of_port_desc_curr_set(of_port_desc, features.curr);
  /* Port Advertised Features */
  of_port_desc_advertised_set(of_port_desc, features.advertised);
  /* Port Supported Features */
  of_port_desc_supported_set(of_port_desc, features.supported);
  /* Peer Features */
  of_port_desc_peer_set(of_port_desc, features.peer);

  return INDIGO_ERROR_NONE;
}

/* Set the port description in LOCI structure 
 * Parameters:                             
 *    port          (input)   Port number 
 *    of_port_desc  (output)  Port description LOCI object
 */
static indigo_error_t ind_ofdpa_port_desc_set(of_port_no_t port, of_port_desc_t *of_port_desc)
{
  OFDPA_ERROR_t ofdpa_rv = OFDPA_E_NONE;
  indigo_error_t err = INDIGO_ERROR_NONE;
  ofdpaMacAddr_t mac;
  of_mac_addr_t of_mac;
  ofdpa_buffdesc nameDesc;
  OFDPA_PORT_STATE_t  state = 0;
  OFDPA_PORT_CONFIG_t config = 0;
  char buff[64];
  uint32_t speed;

  /* Set the port description parameters in LOCI structure */

  /* Port ID */
  of_port_desc_port_no_set(of_port_desc, port);
  /* Port MAC */
  ofdpa_rv = ofdpaPortMacGet(port, &mac);
  if (ofdpa_rv != OFDPA_E_NONE)
  {
    LOG_ERROR("Failed to get Port MAC. (ofdpa_rv = %d)\n", ofdpa_rv);
  }
  memcpy(&of_mac, &mac, sizeof(of_mac)); 
  of_port_desc_hw_addr_set(of_port_desc, of_mac);

#if 1
  /* Port Name */
  memset(buff, 0, sizeof(buff));
  nameDesc.pstart = buff;
  nameDesc.size = OFDPA_PORT_NAME_STRING_SIZE;
  ofdpa_rv = ofdpaPortNameGet(port, &nameDesc);
  if (ofdpa_rv != OFDPA_E_NONE)
  {
    LOG_ERROR("Failed to get Port Name. (ofdpa_rv = %d)\n", ofdpa_rv);
  }
  of_port_desc_name_set(of_port_desc, nameDesc.pstart);

  /* Port Config*/
  ofdpa_rv = ofdpaPortConfigGet(port, &config);
  if (ofdpa_rv != OFDPA_E_NONE)
  {
    LOG_ERROR("Failed to get Port Admin State. (ofdpa_rv = %d)\n", ofdpa_rv);
  }
  of_port_desc_config_set(of_port_desc, config);

  /* Port State */
  ofdpa_rv = ofdpaPortStateGet(port, &state);
  if (ofdpa_rv != OFDPA_E_NONE)
  {
    LOG_ERROR("Failed to get Port State. (ofdpa_rv = %d)\n", ofdpa_rv);
  }
//#else
//  sprintf(portName, "SDN port%d", port); 
#endif
  of_port_desc_state_set(of_port_desc, state);

  /* Port Features */
  err = ind_ofdpa_port_features_set(port, of_port_desc);
  if (err != INDIGO_ERROR_NONE)
  {
    LOG_ERROR("Failed to get Port Features. (err = %d)\n", err);
  }

  /* Port Current Speed in kbps */
  ofdpa_rv = ofdpaPortCurrSpeedGet(port, &speed);
  if (ofdpa_rv != OFDPA_E_NONE)
  {
    LOG_ERROR("Failed to get Port Current Speed. (ofdpa_rv = %d)\n", ofdpa_rv);
  }
  of_port_desc_curr_speed_set(of_port_desc, speed);


  /* Port Maximum Speed in kbps */
  speed = 0;
  ofdpa_rv = ofdpaPortMaxSpeedGet(port, &speed);
  if (ofdpa_rv != OFDPA_E_NONE)
  {
    LOG_ERROR("Failed to get Port Max Speed. (ofdpa_rv = %d)\n", ofdpa_rv);
  }
  of_port_desc_max_speed_set(of_port_desc, speed);
  
  return INDIGO_ERROR_NONE;
}
/*add by liuxiao for port status update debugging*/
uint8_t isPortConfigured(uint32_t port_no)
{
    return g_of_port_status[port_no].isPortConfigured;
}

uint32_t g_link_state = 0;

static indigo_error_t port_desc_set(of_port_desc_t *of_port_desc, uint32_t port_no)
{
    #ifdef RTE_MODE
	ncp_st_t ofdpa_rv;
	ncp_mac_phy_status_t phyStatus;
	#endif

	uint32_t link_mask, speedMax, speedCurr, state=0;
    of_mac_addr_t mac;

#ifdef RTE_MODE
    if(0xFF == isPortConfigured(port_no)) /*only called once*/
    {
        /*This API can use to check whether the port has been confiured?  */
    	ofdpa_rv = ncp_eioa_mac_addr_get(inNcpHdl, port_no, &mac);
    	
    	if(ofdpa_rv != NCP_ST_SUCCESS)
    	{
    		LOG_INFO("###Nokia DPA Integration###:chendong !!ncp_eioa_mac_addr_get ofdpa_rv = %d", ofdpa_rv);
            g_of_port_status[port_no].isPortConfigured = 0; /*set to not configured*/
    		return (indigoConvertOfdpaRv(ofdpa_rv));
    	}
        else
        {
            /*store the mac Address*/
            memcpy(g_of_port_status[port_no].macAddress,&mac,6);
            /* set to configed state*/
            g_of_port_status[port_no].isPortConfigured = 1; /*set to configured*/

            #if 1 /*debugging tracing, enable it if needed*/
            LOG_INFO("port :%d with Mac address %02x:%02x:%02x:%02x:%02x:%02x",port_no,g_of_port_status[port_no].macAddress[0],
                g_of_port_status[port_no].macAddress[1],g_of_port_status[port_no].macAddress[2],g_of_port_status[port_no].macAddress[3],
                g_of_port_status[port_no].macAddress[4],g_of_port_status[port_no].macAddress[5]);
            #endif
        }
    }
    /*if port has been confiured , check the link status*/

	ofdpa_rv = ncp_eioa_mac_link_status_get(inNcpHdl, port_no, &phyStatus, &link_mask);
	if(ofdpa_rv != NCP_ST_SUCCESS)
	{
		LOG_INFO("###ncp_eioa_mac_link_status_get failure port %d,errNo:%d",port_no,ofdpa_rv);
		return (indigoConvertOfdpaRv(ofdpa_rv));
	}
    g_link_state = phyStatus.linkStatus;
#else
    g_of_port_status[port_no].macAddress[5] = port_no;
    g_of_port_status[port_no].isPortConfigured = 1;
    //memcpy(g_of_port_status[port_no].macAddress,&mac,6);
    g_link_state = 0; //down first
#endif
    /*Here introduced a workaround that port_no 0,1 has been used by floodlight SDN controller, so we have to skip 0,1. currently add 2 only*/
    /*It's very urgly , but we have to do this workaround*/
    if(port_no < 10)
        of_port_desc_port_no_set(of_port_desc, (port_no+2));
    else
        of_port_desc_port_no_set(of_port_desc, port_no);
    
    of_port_desc_hw_addr_set(of_port_desc, mac);
    of_port_desc_name_set(of_port_desc, "Nokia");

    uint32_t config = 0;

    of_port_desc_config_set(of_port_desc, config);


    if(0xFF != g_of_port_status[port_no].simPortDownUp)
    {
        /*simulate port down up,it will not run in real HW*/
        g_link_state = g_of_port_status[port_no].simPortDownUp;
    }

    LOG_TRACE("\n PORT NUM = %d g_link_state:%d!!!!!!!!!!!!!!!!!!!!!!\n",port_no,g_link_state);

	if(g_link_state == 0)
	{state |= OF_PORT_STATE_FLAG_LINK_DOWN;}
    of_port_desc_state_set(of_port_desc, state);

    uint32_t curr, advertised, supported, peer;

    curr = OF_PORT_FEATURE_FLAG_10GB_FD |
               OF_PORT_FEATURE_FLAG_COPPER_BY_VERSION(of_port_desc->version);
    advertised = 0;
    supported = 0;
    peer = 0;    
    if (of_port_desc->version < OF_VERSION_1_4) {
        of_port_desc_curr_set(of_port_desc, curr);
        of_port_desc_advertised_set(of_port_desc, advertised);
        of_port_desc_supported_set(of_port_desc, supported);
        of_port_desc_peer_set(of_port_desc, peer);
    } else {
        of_object_t props;
        of_object_t prop;
        of_port_desc_properties_bind(of_port_desc, &props);
        of_port_desc_prop_ethernet_init(&prop, props.version, -1, 1);
        if (of_list_port_desc_prop_append_bind(&props, &prop) < 0) {
            AIM_DIE("unexpected error appending to port_desc");
        }
        of_port_desc_prop_ethernet_curr_set(&prop, curr);
        of_port_desc_prop_ethernet_advertised_set(&prop, advertised);
        of_port_desc_prop_ethernet_supported_set(&prop, supported);
        of_port_desc_prop_ethernet_peer_set(&prop, peer);
        /* TODO curr_speed, max_speed */
        #if 0
        if (port->is_uplink) {
            of_port_desc_prop_bsn_uplink_init(&prop, props.version, -1, 1);
            if (of_list_port_desc_prop_append_bind(&props, &prop) < 0) {
                AIM_DIE("unexpected error appending to port_desc");
            }
        }
        #endif
    }

	#ifdef RTE_MODE
	speedMax = phyStatus.speed;
	speedCurr = phyStatus.speed;
	#endif
	
	of_port_desc_curr_speed_set(of_port_desc, speedCurr);
	of_port_desc_max_speed_set(of_port_desc, speedMax);
	
	return INDIGO_ERROR_NONE;
}

#if 0
indigo_error_t indigo_port_features_get(of_features_reply_t *features)
{
  indigo_error_t      err             = INDIGO_ERROR_NONE;
  of_list_port_desc_t *of_list_port_desc = 0;
  of_port_desc_t      *of_port_desc      = 0;
  uint32_t port = 0, nextPort = 0;
  OFDPA_ERROR_t ofdpa_rv = OFDPA_E_NONE;


  LOG_TRACE("%s() called\n",__FUNCTION__);

  if (features->version < OF_VERSION_1_3) 
  {
    return INDIGO_ERROR_VERSION;
  }

  /* Allocates memory for of_port_desc */
  of_port_desc = of_port_desc_new(features->version);
  if (of_port_desc == NULL)
  {
    LOG_ERROR("of_port_desc_new() failed");
    return INDIGO_ERROR_RESOURCE;
  }

  /* Allocates memory for of_list_port_desc */
  of_list_port_desc = of_list_port_desc_new(features->version);
  if (of_list_port_desc == NULL)
  {
    LOG_ERROR("of_list_port_desc_new() failed");

    /* free of_list_port_desc */
    of_port_desc_delete(of_port_desc);

    return INDIGO_ERROR_RESOURCE;
  } 

  ofdpa_rv = ofdpaPortNextGet(port, &nextPort);
  while(ofdpa_rv == OFDPA_E_NONE) 
  {
    err = ind_ofdpa_port_features_set(nextPort, of_port_desc);
    if (err != INDIGO_ERROR_NONE)
    {
      LOG_ERROR("Failed to get OpenFlow port stats.");
      break;
    }
    of_list_port_desc_append(of_list_port_desc, of_port_desc);
    port = nextPort;
    ofdpa_rv = ofdpaPortNextGet(port, &nextPort);
  }

  if (of_features_reply_ports_set(features, of_list_port_desc) < 0)
  {
    LOG_ERROR("of_features_reply_ports_set() failed");
    err = INDIGO_ERROR_UNKNOWN;
  }

  /* free the allocated memory */
  of_port_desc_delete(of_port_desc);
  of_list_port_desc_delete(of_list_port_desc);

  return err;
}
#else
indigo_error_t
indigo_port_features_get(of_features_reply_t *features)
{
	uint32_t capabilities = 0;

	AIM_LOG_VERBOSE("port features get called\n");

    OF_CAPABILITIES_FLAG_FLOW_STATS_SET(capabilities, features->version);
    OF_CAPABILITIES_FLAG_TABLE_STATS_SET(capabilities, features->version);
    OF_CAPABILITIES_FLAG_PORT_STATS_SET(capabilities, features->version);
    OF_CAPABILITIES_FLAG_QUEUE_STATS_SET(capabilities, features->version);
    of_features_reply_capabilities_set(features, capabilities);

    return INDIGO_ERROR_NONE;
}
#endif

/*
 * Truncate the object to its initial length.
 *
 * This allows the caller to reuse a single allocated object even if
 * it has been appended to.
 */
static void
truncate_of_object(of_object_t *obj)
{
    of_object_init_map[obj->object_id](obj, obj->version, -1, 0);
    obj->wbuf->current_bytes = obj->length;
}

indigo_error_t indigo_port_desc_stats_get(of_port_desc_stats_reply_t *port_desc_stats_reply)
{
  indigo_error_t err = INDIGO_ERROR_NONE;
  OFDPA_ERROR_t ofdpa_rv = OFDPA_E_NONE;
  of_port_desc_t *of_port_desc = 0;
  of_list_port_desc_t *of_list_port_desc = 0;
  int32_t port = 0, nextPort = 0;
      
  //LOG_TRACE("%s() called.", __FUNCTION__);
  //LOG_INFO("indigo_port_desc_stats_get line %d.",__LINE__);  
  if (port_desc_stats_reply->version < OF_VERSION_1_3)
  {
    return INDIGO_ERROR_VERSION;
  }
  
  /* Allocates memory for of_port_desc */
  of_port_desc = of_port_desc_new(port_desc_stats_reply->version);
  if (of_port_desc == NULL)
  {
    LOG_ERROR("of_port_desc_new() failed");
    return INDIGO_ERROR_RESOURCE;
  }
  
  /* Allocates memory for of_list_port_desc */
  of_list_port_desc = of_list_port_desc_new(port_desc_stats_reply->version); 
  if (of_list_port_desc == NULL)
  {
    LOG_ERROR("of_list_port_desc_new() failed");
    of_port_desc_delete(of_port_desc);
    return INDIGO_ERROR_RESOURCE;
  }

  ofdpa_rv = ofdpaPortNextGet(port, &nextPort);
  while(ofdpa_rv == OFDPA_E_NONE)
  {
    
    //LOG_INFO("indigo_port_desc_stats_get port %d nextPort %d line %d.",port,nextPort,__LINE__);  
    truncate_of_object(of_port_desc);
    /* Set the port description parameters in LOCI structure (of_port_desc)
       to be sent in the reply message */
    err = ind_ofdpa_port_desc_set(nextPort, of_port_desc);
    if (err != INDIGO_ERROR_NONE)
    {
      LOG_ERROR("Failed to get OpenFlow port description for port %d.", nextPort);
      break;
    }

    if (of_list_port_desc_append(of_list_port_desc, of_port_desc) < 0)
    {
      LOG_ERROR("of_list_port_desc_append() failed");
      err = INDIGO_ERROR_UNKNOWN;
      break;
    }
    port = nextPort;
    ofdpa_rv = ofdpaPortNextGet(port, &nextPort);
  }

  if (of_port_desc_stats_reply_entries_set(port_desc_stats_reply, of_list_port_desc) < 0)
  {
    LOG_ERROR("of_port_desc_stats_reply_entries_set() failed");
    err = INDIGO_ERROR_UNKNOWN;
  }
  
  //LOG_INFO("indigo_port_desc_stats_get line %d err= %d.",__LINE__,err);  
  /* free the allocated memory */
  if(of_list_port_desc)
      of_list_port_desc_delete(of_list_port_desc);
  if(of_port_desc)
      of_port_desc_delete(of_port_desc);
  return err;  
}

#if 0
indigo_error_t indigo_port_modify(of_port_mod_t *port_mod)
{
  OFDPA_ERROR_t ofdpa_rv = OFDPA_E_NONE;
  of_port_no_t of_port_no;
  of_mac_addr_t of_mac;
  uint32_t of_config;
  uint32_t of_mask;
  uint32_t of_advertise;
  ofdpaMacAddr_t mac;

  LOG_TRACE("%s() called", __FUNCTION__);

  of_port_mod_port_no_get(port_mod, &of_port_no);

  /* Check if the port hardware address is the same. Sanity check */
  ofdpa_rv = ofdpaPortMacGet(of_port_no, &mac);
  if (ofdpa_rv != OFDPA_E_NONE)
  {
    LOG_ERROR("Failed to get MAC address on port %d. (ofdpa_rv = %d)", of_port_no, ofdpa_rv);
    return (indigoConvertOfdpaRv(ofdpa_rv));
  }

  of_port_mod_hw_addr_get(port_mod, &of_mac);
  if (memcmp(&of_mac, &mac, sizeof(of_mac)) != 0)
  {
    LOG_ERROR("Invalid mac address.");
  }

  /* Set the port config state (admin state)*/
  of_port_mod_config_get(port_mod, &of_config);
  of_port_mod_mask_get(port_mod, &of_mask);
 
  of_config &= of_mask;

  ofdpa_rv = ofdpaPortConfigSet(of_port_no, of_config);
  if (ofdpa_rv != OFDPA_E_NONE)
  {
    LOG_ERROR("Failed to set config state on port %d. (ofdpa_rv = %d)", of_port_no, ofdpa_rv);
    return (indigoConvertOfdpaRv(ofdpa_rv));
  }

  /* Set advertise features */
  of_port_mod_advertise_get(port_mod, &of_advertise);
  ofdpa_rv = ofdpaPortAdvertiseFeatureSet(of_port_no, of_advertise);
  if (ofdpa_rv != OFDPA_E_NONE)
  {                     
    LOG_ERROR("Failed to set advertise features on port %d. (ofdpa_rv = %d)", of_port_no, ofdpa_rv);
    return (indigoConvertOfdpaRv(ofdpa_rv));
  }
    
  return INDIGO_ERROR_NONE;
}
#else
indigo_error_t
indigo_port_modify(of_port_mod_t *port_mod)
{
    AIM_LOG_VERBOSE("port mod called\n");
    return INDIGO_ERROR_NONE;
}
#endif

indigo_error_t indigo_port_stats_get(of_port_stats_request_t *port_stats_request,
                                     of_port_stats_reply_t **port_stats_reply)
{
  indigo_error_t err = INDIGO_ERROR_NONE;
  OFDPA_ERROR_t ofdpa_rv = OFDPA_E_NONE;
  of_port_no_t req_of_port_num;
  of_port_stats_reply_t *reply;
  int dump_all = 0;
  uint32_t port = 0;


  //LOG_TRACE("%s() called", __FUNCTION__);
  
  //LOG_INFO("indigo_port_stats_get line %d.",__LINE__);
  if (port_stats_request->version < OF_VERSION_1_3)
  {
    return INDIGO_ERROR_VERSION;
  }

  /* Allocate memory for the port stats reply 
     Note: Memory allocated is freed by the caller 
     of indigo_port_stats_get()*/ 
  reply = of_port_stats_reply_new(port_stats_request->version);
  if (reply == NULL) 
  {
    LOG_ERROR("Error allocating memory for port stats reply.");
    return INDIGO_ERROR_RESOURCE;
  }

  *port_stats_reply = reply;

  of_list_port_stats_entry_t list;
  of_port_stats_reply_entries_bind(reply, &list);

  of_port_stats_request_port_no_get(port_stats_request, &req_of_port_num);
  if (req_of_port_num == OF_PORT_DEST_NONE_BY_VERSION(port_stats_request->version)) 
  {
    ofdpa_rv = ofdpaPortNextGet(0, &port);
    if (ofdpa_rv != OFDPA_E_NONE)
    {
      LOG_ERROR("Failed to get first port.");
      of_port_stats_reply_delete(*port_stats_reply);
      return indigoConvertOfdpaRv(ofdpa_rv);
    }

    /* dump the stats of all the ports */
    dump_all = 1;
  }
  else
  {
    port = req_of_port_num;
  }
  //LOG_INFO("port number %x req_of_port_num=%d.",port,req_of_port_num);
  do
  {
    err = ind_ofdpa_port_stats_set(port, &list);
    if (err != INDIGO_ERROR_NONE)
    {
      LOG_ERROR("Error setting port stats LOCI object.");
      break;
    }
    /* Break from the loop if he request is for a single port */
    if (!dump_all)
    {
      break;
    }

  }while((ofdpaPortNextGet(port, &port) == OFDPA_E_NONE));

  /* Free the reply message only on failure.
     Reply message is freed by the caller on success */ 
  if (err != INDIGO_ERROR_NONE) 
  {
    of_port_stats_reply_delete(*port_stats_reply);
    *port_stats_reply = NULL;
  }

  return err;
}

#if 0
indigo_error_t indigo_port_queue_config_get(of_queue_get_config_request_t *queue_config_request,
                                            of_queue_get_config_reply_t **queue_config_reply)
{
  of_queue_get_config_reply_t *reply;
  indigo_error_t err = INDIGO_ERROR_NONE;
  OFDPA_ERROR_t ofdpa_rv = OFDPA_E_NONE;
  of_port_no_t req_of_port_num;
  of_packet_queue_t *of_packet_queue;
  of_list_packet_queue_t *of_list_packet_queue;

  uint32_t queueId = 0;
  uint32_t numQueues = 0;
  uint32_t dump_all = 0;
  uint32_t port;

  LOG_TRACE("%s called", __FUNCTION__);

  if (queue_config_request->version < OF_VERSION_1_3)
  {
    LOG_ERROR("Unsupported OpenFlow version 0x%x.", queue_config_request->version);
    return INDIGO_ERROR_VERSION;
  }

  /* Allocate memory for reply. 
   * NOTE: This memory is freed by the caller of 
   *       indigo_port_queue_config_get()  */
  reply = of_queue_get_config_reply_new(queue_config_request->version);
  if (reply == NULL) 
  {
    LOG_ERROR("Could not allocate queue config reply");
    return INDIGO_ERROR_RESOURCE;
  }

  *queue_config_reply = reply;

  of_packet_queue = of_packet_queue_new(queue_config_request->version);
  if (of_packet_queue == NULL)
  {
    LOG_ERROR("Failed to allocate memory for of_packet_queue.");
    of_queue_get_config_reply_delete(*queue_config_reply);
    return INDIGO_ERROR_RESOURCE;
  }

  /* Allocate the memory for the packet_queue struct */
  of_list_packet_queue = of_list_packet_queue_new(queue_config_request->version);
  if (of_list_packet_queue == NULL)
  {
    LOG_ERROR("Failed to allocate memory for of_list_packet_queue.");
    of_packet_queue_delete(of_packet_queue);
    of_queue_get_config_reply_delete(*queue_config_reply);
    return INDIGO_ERROR_RESOURCE;
  }
   
  of_queue_get_config_reply_queues_bind(*queue_config_reply, of_list_packet_queue);

  /* Get the port from request */
  of_queue_get_config_request_port_get(queue_config_request, &req_of_port_num);

  /* Check if the port is OFPP_ANY */
  if (req_of_port_num == OF_PORT_DEST_WILDCARD_BY_VERSION(queue_config_request->version))
  {
    ofdpa_rv = ofdpaPortNextGet(0, &port);
    if (ofdpa_rv != OFDPA_E_NONE)
    {
      LOG_ERROR("Error geting first port. (ofdpa_rv = %d)", ofdpa_rv);
    }
    err = indigoConvertOfdpaRv(ofdpa_rv);
    dump_all = 1;
  }
  else
  {
    port = req_of_port_num;
  }

  if (err == INDIGO_ERROR_NONE)
  {
    do
    {
      of_queue_get_config_reply_port_set(*queue_config_reply, port);
      /* Set the of_packet_queue struct elements */
      ofdpa_rv = ofdpaNumQueuesGet(port, &numQueues);
      if (ofdpa_rv != OFDPA_E_NONE)
      {
        LOG_ERROR("Error getting maximum queues supported on port %d. (ofdpa_rv = %d)", port, ofdpa_rv);
        err = indigoConvertOfdpaRv(ofdpa_rv);
        break;
      }
      for (queueId = 0; queueId < numQueues; queueId++)
      {
        err = ind_ofdpa_queue_config_queue_set(of_packet_queue, port, queueId);
        if (err != INDIGO_ERROR_NONE)
        {
          LOG_ERROR("Error setting of_packet_queue. (err = %d)", err);
          err = indigoConvertOfdpaRv(ofdpa_rv);
          break;
        }

        of_list_packet_queue_append(of_list_packet_queue, of_packet_queue);
      }

      if (!dump_all)
      {
        break;
      }
    }while((ofdpaPortNextGet(port, &port) == OFDPA_E_NONE) && (err == INDIGO_ERROR_NONE));
  }

  of_packet_queue_delete(of_packet_queue); 
  of_list_packet_queue_delete(of_list_packet_queue);  

 /* Free the reply message only on failure.
    Reply message is freed by the caller on success */
  if (err != INDIGO_ERROR_NONE)
  {
    of_queue_get_config_reply_delete(*queue_config_reply);
    *queue_config_reply = NULL;
  }

  return err;
}
#else
indigo_error_t
indigo_port_queue_config_get(of_queue_get_config_request_t *request,
                             of_queue_get_config_reply_t **reply_ptr)
{
    AIM_LOG_VERBOSE("queue config get called\n");
    *reply_ptr = of_queue_get_config_reply_new(request->version);
    return INDIGO_ERROR_NONE;
}
#endif

#if 0
indigo_error_t indigo_port_queue_stats_get(of_queue_stats_request_t *queue_stats_request,
                                           of_queue_stats_reply_t **queue_stats_reply)
{
  indigo_error_t err = INDIGO_ERROR_NONE;
  OFDPA_ERROR_t ofdpa_rv = OFDPA_E_NONE;
  of_queue_stats_reply_t *reply;
  uint32_t req_of_port_queue_id; 
  of_port_no_t req_of_port_num;
  uint32_t port, all_ports = 0;
  

  LOG_TRACE("Port queue stats called");

  if (queue_stats_request->version < OF_VERSION_1_3)
  {
    LOG_ERROR("Unsupported OpenFlow version 0x%x.", queue_stats_request->version);
    return INDIGO_ERROR_VERSION;
  }

  /* Allocate memory for reply message 
   * NOTE: This memory is freed by the caller of 
   *       indigo_port_queue_stats_get()  */
  reply = of_queue_stats_reply_new(queue_stats_request->version);
  if (reply == NULL)
  {
    LOG_ERROR("Error allocating memory for queue stats reply.");
    return INDIGO_ERROR_RESOURCE;
  }

  *queue_stats_reply = reply;

  of_list_queue_stats_entry_t list[1];
  of_queue_stats_reply_entries_bind(*queue_stats_reply, list);

  /* Get the port id from request message */
  of_queue_stats_request_port_no_get(queue_stats_request, &req_of_port_num);

  /* Get the queue id from request message */
  of_queue_stats_request_queue_id_get(queue_stats_request, &req_of_port_queue_id);

  /* Check if the queue stats request is for ALL ports (OFPP_ANY) */
  if (req_of_port_num == OF_PORT_DEST_WILDCARD_BY_VERSION(queue_stats_request->version))
  {
    /* Get the first port if the queue stats message is for all the ports*/
    ofdpa_rv = ofdpaPortNextGet(0, &port);
    if (ofdpa_rv != OFDPA_E_NONE)
    {
      LOG_ERROR("Failed to get first port. (ofdpa_rv = %d)", ofdpa_rv);
      of_queue_stats_reply_delete(*queue_stats_reply);
      return (indigoConvertOfdpaRv(ofdpa_rv));
    } 
    all_ports = 1;
  } 
  else
  {
    port = req_of_port_num;
  } 
  

  do
  {
    err = ind_ofdpa_queue_stats_set(port, req_of_port_queue_id, list); 
    if (err != INDIGO_ERROR_NONE)
    {
      LOG_ERROR("Failed to get port queue stats. (err = %d)", err);
      break; 
    }

    if (!all_ports)
    {
      break;
    }

  }while(ofdpaPortNextGet(port, &port) == OFDPA_E_NONE);

  /* Free the reply message only on failure.
     Reply message is freed by the caller on success */
  if (err != INDIGO_ERROR_NONE)
  {
    of_queue_stats_reply_delete(*queue_stats_reply);
    *queue_stats_reply = NULL;
  }
 
  return err; 
}
#else
indigo_error_t
indigo_port_queue_stats_get(of_queue_stats_request_t *request,
                            of_queue_stats_reply_t **reply_ptr)
{

    AIM_LOG_VERBOSE("queue stats get called\n");
    *reply_ptr = of_queue_stats_reply_new(request->version);
    return INDIGO_ERROR_NONE;
}

#endif

indigo_error_t indigo_port_interface_add(indigo_port_name_t port_name,
                                         of_port_no_t of_port,
                                         indigo_port_config_t *config)
{
  LOG_ERROR("indigo_port_interface_add() unsupported.");
  return INDIGO_ERROR_NOT_SUPPORTED;
}

indigo_error_t indigo_port_interface_modified(indigo_port_name_t port_name)
{
  LOG_ERROR("indigo_port_interface_modified() unsupported.");
  return INDIGO_ERROR_NOT_SUPPORTED;
}

indigo_error_t indigo_port_interface_remove(indigo_port_name_t port_name)
{
  LOG_ERROR("indigo_port_interface_remove() unsupported.");
  return INDIGO_ERROR_NOT_SUPPORTED;
}

indigo_error_t indigo_port_interface_list(indigo_port_info_t** list)
{
  LOG_ERROR("indigo_port_interface_list() unsupported.");
  return INDIGO_ERROR_NOT_SUPPORTED;
}

void indigo_port_interface_list_destroy(indigo_port_info_t* list)
{
  LOG_ERROR("indigo_port_interface_list_destroy() unsupported.");
  return;
}

indigo_error_t indigo_port_experimenter(of_experimenter_t *experimenter,
                                        indigo_cxn_id_t cxn_id)
{
  LOG_ERROR("indigo_port_experimenter() unsupported.");
  return INDIGO_ERROR_NOT_SUPPORTED;
}

indigo_error_t indigo_port_packet_emit(of_port_no_t egress_port,
                                       unsigned queue_id,
                                       uint8_t *data,
                                       unsigned length)
{
  LOG_ERROR("indigo_port_packet_emit() unsupported.");
  return INDIGO_ERROR_NOT_SUPPORTED;
}

indigo_error_t indigo_port_packet_emit_all(of_port_no_t skip_egress_port,
                                           uint8_t *data,
                                           unsigned length)
{
  LOG_ERROR("indigo_port_packet_emit_all() unsupported.");
  return INDIGO_ERROR_NOT_SUPPORTED;
}

indigo_error_t indigo_port_packet_emit_group(uint32_t group_id,
                                             of_port_no_t ingress_port_num,
                                             uint8_t *data,
                                             unsigned len)
{
  LOG_ERROR("indigo_port_packet_emit_group() unsupported.");
  return INDIGO_ERROR_NOT_SUPPORTED;
}
uint32_t g_report_once_flag = 0; /*define this parameter so that only once packet-in has been reported in one timer out*/

void
port_status_notify(uint32_t port_no, unsigned reason)
{
    indigo_error_t   result = INDIGO_ERROR_NONE;
    of_port_desc_t   *of_port_desc   = 0;
    of_port_status_t *of_port_status = 0;
    of_version_t ctrlr_of_version;
    uint32_t temp_port_no = 0;
	#ifdef RTE_MODE    
	ncp_st_t ofdpa_rv;
	#endif
    if (indigo_cxn_get_async_version(&ctrlr_of_version) != INDIGO_ERROR_NONE) {
        LOG_TRACE("No active controller connection");
        return;
    }
    if ((of_port_desc = of_port_desc_new(ctrlr_of_version)) == 0) {
        LOG_ERROR("of_port_desc_new() failed");
        goto done;
    }
    //ind_ofdpa_port_desc_set(of_port_desc, port_no);
    #ifdef RTE_MODE
    if ((ofdpa_rv = port_desc_set(of_port_desc, port_no)) != NCP_ST_SUCCESS)
    {
 //       LOG_ERROR("port_desc_set() failed");
        //result = INDIGO_ERROR_UNKNOWN;
        //if(g_of_port_status[port_no].port == 0xffffffff)//If the port never configed, return. 
        goto done;
	}
	#endif
    if ((of_port_status = of_port_status_new(ctrlr_of_version)) == 0) {
        LOG_ERROR("of_port_status_new() failed");
        //result = INDIGO_ERROR_UNKNOWN;
        goto done;
    }

	/*Nothing changed, no need to report*/
	if((g_of_port_status[port_no].port == port_no) && (g_of_port_status[port_no].link_state == g_link_state))//&& (g_of_port_status[port_no].reason == reason)
	{
		//LOG_INFO("Port %d Nothing CHANGED, EXIT!!!!", port_no);
		goto done;
	}
	/*New port added, need report*/
	if(g_of_port_status[port_no].port == 0xffffffff)
	{
		g_of_port_status[port_no].port = port_no;
		g_of_port_status[port_no].reason = OF_PORT_CHANGE_REASON_ADD;
		g_of_port_status[port_no].link_state = g_link_state;
		LOG_INFO("Port %d is the NEW PORT!!!!", port_no);
	}
	/*Legacy port, link status changed, change the reason to Modify/Delete*/
	if((g_of_port_status[port_no].port != 0xffffffff) && (g_of_port_status[port_no].link_state != g_link_state))
	{
		//LOG_INFO("Port %d is the LEGACY PORT!!!!, state changed, current state is %d", port_no, g_link_state);
		g_of_port_status[port_no].link_state = g_link_state;
        g_of_port_status[port_no].reason = OF_PORT_CHANGE_REASON_MODIFY;
	}

	of_port_status_reason_set(of_port_status, g_of_port_status[port_no].reason);
	of_port_status_desc_set(of_port_status, of_port_desc);

    #if 0
    if(port_no < 10)
    {
        /*Here introduced a workaround that port_no 0,1 has been used by floodlight SDN controller, so we have to skip 0,1. currently add 2 only*/
        /*It's very urgly , but we have to do this workaround*/
        of_port_desc_port_no_set(of_port_desc, (port_no + 2));
    }
    #endif
    indigo_core_port_status_update(of_port_status);
    if(1 == g_link_state)/*means UP*/
    {
        /*change from down to UP,Need send out packet in message*/
        if(port_no < 10)
        {
            ind_ofdpa_pkt_in_construct_fwd((port_no + 2),g_of_port_status[port_no].macAddress);
        }
        else
        {
            ind_ofdpa_pkt_in_construct_fwd(port_no,g_of_port_status[port_no].macAddress);
        }
    }
    LOG_INFO("g_link_state %d is the port_no:%d ,reson:%d send out packet in and status !!!!", g_link_state,port_no,g_of_port_status[port_no].reason);
    g_report_once_flag++;
    of_port_desc   = 0;     /* No longer owned */
    of_port_status = 0;     /* No longer owned */
 done:
    if (of_port_desc)    of_port_desc_delete(of_port_desc);
    if (of_port_status)  of_port_status_delete(of_port_status);
    return;
}
//#define OF_PORT_CHANGE_REASON_ADD 0

uint32_t g_callback_counter=0;

uint8_t gPortNumber = 0;

#define ENABLE 1
#define DISABLE 0

#ifdef RTE_MODE
void portEnableDisable(ncp_macChan_t macChan)
{
#if 0
	ncp_st_t ofdpa_rv = 0;

    /*These two funciton can not change port linkstauts*/
	if(g_callback_counter == 2)
	{
		ofdpa_rv = ncp_eioa_port_enable_set(inNcpHdl, macChan, ENABLE, ENABLE);
	}
	if(g_callback_counter == 4)
	{
		ofdpa_rv = ncp_eioa_port_enable_set(inNcpHdl, macChan, DISABLE, DISABLE);
	}

	if(ofdpa_rv!=0)
	{
		LOG_INFO("ncp_eioa_port_enable_set failed, port ID = %d.", macChan);
	}
#endif
#if 0 //no simulator in really case
    /*add for simulate port down and up*/    
    if(g_callback_counter >= 2 && g_callback_counter < 113)
    {
        g_of_port_status[g_callback_counter-2].simPortDownUp = 1;
    }
#endif
    
}
#else
void portEnableDisable(uint32_t macChan)
{
}
#endif

void testPortStatus()
{
	uint32_t port_num;
	
	g_callback_counter++;
    g_report_once_flag = 0;
	/*case 1, port 0, resean 0*/
    //LOG_INFO("testPortStatus called, COUNTER %d", g_callback_counter);

	for(port_num=0; (port_num<10) && (0 == g_report_once_flag); port_num++)
	{
	    if(0 !=  isPortConfigured(port_num))
        {   
  		    portEnableDisable(port_num);
  		    port_status_notify(port_num,OF_PORT_CHANGE_REASON_ADD);
  	        //LOG_INFO("port_status_notify done, port ID = %d.", port_num);
        }
	}
	for(port_num=16; (port_num<21) && (0 == g_report_once_flag); port_num++)
	{
	    if(0 !=  isPortConfigured(port_num))
        {   
		    portEnableDisable(port_num);
		    port_status_notify(port_num,OF_PORT_CHANGE_REASON_ADD);
	        //LOG_INFO("port_status_notify done, port ID = %d.", port_num); 
        }
	}
	for(port_num=32; (port_num<34) && (0 == g_report_once_flag); port_num++)
	{
	    if(0 !=  isPortConfigured(port_num))
        {   
		    portEnableDisable(port_num);
		    port_status_notify(port_num,OF_PORT_CHANGE_REASON_ADD);
	        //LOG_INFO("port_status_notify done, port ID = %d.", port_num); 
        }
	}
	for(port_num=48; (port_num<50) && (0 == g_report_once_flag); port_num++)
	{
	    if(0 !=  isPortConfigured(port_num))
        {   
		    portEnableDisable(port_num);
		    port_status_notify(port_num,OF_PORT_CHANGE_REASON_ADD);
	        //LOG_INFO("port_status_notify done, port ID = %d.", port_num);
        }
	}
	for(port_num=64; (port_num<66) && (0 == g_report_once_flag); port_num++)
	{
	    if(0 !=  isPortConfigured(port_num))
        {   
		    portEnableDisable(port_num);
		    port_status_notify(port_num,OF_PORT_CHANGE_REASON_ADD);
	        //LOG_INFO("port_status_notify done, port ID = %d.", port_num);
        }
	}
	for(port_num=80; (port_num<82) && (0 == g_report_once_flag); port_num++)
	{
	    if(0 !=  isPortConfigured(port_num))
        {   
		    portEnableDisable(port_num);
		    port_status_notify(port_num,OF_PORT_CHANGE_REASON_ADD);
	        //LOG_INFO("port_status_notify done, port ID = %d.", port_num); 
        }
	}
	for(port_num=96; (port_num<98) && (0 == g_report_once_flag); port_num++)
	{
	    if(0 !=  isPortConfigured(port_num))
        {   
		    portEnableDisable(port_num);
		    port_status_notify(port_num,OF_PORT_CHANGE_REASON_ADD);
	        //LOG_INFO("port_status_notify done, port ID = %d.", port_num); 
        }
	}
	for(port_num=112; (port_num<114) && (0 == g_report_once_flag); port_num++)
	{
	    if(0 !=  isPortConfigured(port_num))
        {   
		    portEnableDisable(port_num);
		    port_status_notify(port_num,OF_PORT_CHANGE_REASON_ADD);
	        //LOG_INFO("port_status_notify done, port ID = %d.", port_num); 
        }
	}
}
void
ind_ofdpa_port_event_receive(void)
{
  of_port_desc_t   *of_port_desc   = 0;
  of_port_status_t *of_port_status = 0;
  ofdpaPortEvent_t portEventData;
  int reason = 0;

  LOG_TRACE("Reading Port Events");

  memset(&portEventData, 0, sizeof(portEventData));
  while (ofdpaPortEventNextGet(&portEventData) == OFDPA_E_NONE)
  {
    LOG_TRACE("client_event: retrieved port event: port no = %d, eventMask = 0x%x, state = %d\n",
              portEventData.portNum, portEventData.eventMask, portEventData.state);

    of_port_desc = of_port_desc_new(ofagent_of_version);
    if (of_port_desc == 0) 
    {
      LOG_ERROR("of_port_desc_new() failed");
      break;
    }

    if ((ind_ofdpa_port_desc_set(portEventData.portNum, of_port_desc)) < 0)
    {
      LOG_ERROR("ind_ofdpa_port_desc_set() failed");
      break;
    }

    of_port_status = of_port_status_new(ofagent_of_version);
    if (of_port_status == 0) 
    {
      LOG_ERROR("of_port_status_new() failed");
      break;
    }

    if (portEventData.eventMask & OFDPA_EVENT_PORT_CREATE)
    {
      reason = OF_PORT_CHANGE_REASON_ADD;
    }
    else if (portEventData.eventMask & OFDPA_EVENT_PORT_DELETE)
    {
      reason = OF_PORT_CHANGE_REASON_DELETE;
    }
    else if (portEventData.eventMask & OFDPA_EVENT_PORT_STATE)
    {
      reason = OF_PORT_CHANGE_REASON_MODIFY;
    }

    of_port_status_reason_set(of_port_status, reason);
    of_port_status_desc_set(of_port_status, of_port_desc);
    of_port_desc_delete(of_port_desc);

    indigo_core_port_status_update(of_port_status);

    of_port_desc   = 0;     /* No longer owned */
    of_port_status = 0;     /* No longer owned */
  }

  if (of_port_desc)
  {
    of_port_desc_delete(of_port_desc);
  }

  return;
}

