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
* @filename     rte_of_driver_mac_statistics.c
*
* @purpose      
*
* @component    
*
* @comments     none
*
* @create       06/12/2015
*
* @end
*
**********************************************************************/
#ifdef RTE_MODE
#include <stdio.h>
#include <string.h>
#include <ind_of_util.h>
#include <unistd.h>
#include <ind_of_log.h>
#include <ncp.h>
#include <ncp_pvt.h>
#include <ncp_eioa.h>
#include <ncp_eioa_config_55xx.h>


#include "RTEOfDriver_api.h"

#ifndef __PORT_DBG__
//#define __PORT_DBG__
#endif

const char *xgmac_name[] = {"XGMAC0","XGMAC1","NULL2","NULL3",
    "NULL4","XGMAC8","NULL6","NULL7","NULL8","NULL9","NULL10","NULL11",
    "NULL12","NULL13","NULL14","NULL15","XGMAC16","XGMAC17","NULL18",
    "NULL19","NULL20","NULL21","NULL22","NULL23","NULL24","NULL25",
    "NULL26","NULL27","NULL28","NULL29","NULL30","NULL31","XGMAC32",
    "XGMAC33","NULL34","NULL35","NULL36","NULL37","NULL38","NULL39",
    "NULL40","NULL41","NULL42","NULL43","NULL44","NULL45","NULL46","NULL47",
    "XGMAC48","XGMAC49","NULL50","NULL51","NULL52","NULL53","NULL54",
    "NULL55","NULL56","NULL57","NULL58","NULL59","NULL60","NULL61","NULL62",
    "NULL63","XGMAC64","XGMAC65","NULL66","NULL67","NULL68","NULL69",
    "NULL70","NULL71","NULL72","NULL73","NULL74","NULL75","NULL76","NULL77",
    "NULL78","NULL79","XGMAC80","XGMAC81","NULL82","NULL83","NULL84",
    "NULL85","NULL86","NULL87","NULL88","NULL89","NULL90","NULL91","NULL92",
    "NULL93","NULL94","NULL95","XGMAC96","XGMAC97","NULL98","NULL99",
    "NULL100","NULL101","NULL102","NULL103","NULL104","NULL105","NULL106",
    "NULL107","NULL108","NULL109","NULL110","NULL111","XGMAC112",
    "XGMAC113", "NULL114","NULL115","NULL116","NULL117","NULL118","NULL119"};

const char *gmac_name[] = {"GMAC0","GMAC1","GMAC2",
    "GMAC3","GMAC4","NULL5","GMAC9","GMAC10","GMAC11",
    "GMAC12","NULL10","NULL11","NULL12","NULL13","NULL14","NULL15",
    "GMAC16","GMAC17","GMAC18","GMAC19","GMAC20","NULL21",
    "NULL22","NULL23","NULL24","NULL25","NULL26","NULL27","NULL28","NULL29",
    "NULL30","NULL31","GMAC32","GMAC33","NULL34","NULL35","NULL36",
    "NULL37","NULL38","NULL39","NULL40","NULL41","NULL42","NULL43","NULL44",
    "NULL45","NULL46","NULL47","GMAC48","GMAC49","NULL50","NULL51",
    "NULL52","NULL53","NULL54","NULL55","NULL56","NULL57","NULL58","NULL59",
    "NULL60","NULL61","NULL62","NULL63","GMAC64","GMAC65","NULL66",
    "NULL67","NULL68","NULL69","NULL70","NULL71","NULL72","NULL73","NULL74",
    "NULL75","NULL76","NULL77","NULL78","NULL79","GMAC80","GMAC81",
    "NULL82","NULL83","NULL84","NULL85","NULL86","NULL87","NULL88","NULL89",
    "NULL90","NULL91","NULL92","NULL93","NULL94","NULL95","GMAC96",
    "GMAC97","NULL98","NULL99","NULL100","NULL101","NULL102","NULL103",
    "NULL104","NULL105","NULL106","NULL107","NULL108","NULL109","NULL110",
    "NULL111","GMAC112","GMAC113","NULL114","NULL115","NULL116",
    "NULL117","NULL118","NULL119"};

const char *tx_stat_name[] = {"TX_OCTETS", "TX_BAD_OCTETS", "TX_FRM",
        "TX_BAD_FRM", "TX_MCAST", "TX_BCAST", "TX_PAUSE", "TX_FCS", "TX_DEFER",
        "TX_XSDFR", "TX_1COL", "TX_MCOL", "TX_LCOL", "TX_XSCOL", "TX_FRAG",
        "TX_USIZE", "TX_64", "TX_65", "TX_128", "TX_256", "TX_512", "TX_1024",
        "TX_1519", "TX_OSIZE", "TX_JAB", "TX_URUN", "TX_STAT_OVFL" };

const char *rx_stat_name[] = {"RX_OCTETS", "RX_BAD_OCTETS", "RX_FRM",
        "RX_BAD_FRM", "RX_MCAST", "RX_BCAST", "RX_CTL", "RX_PAUSE", "RX_UNK_OP",
        "RX_FCS", "RX_ALIGN", "RX_LENGTH", "RX_CODE", "RX_FRAG", "RX_USIZE",
        "RX_64", "RX_65", "RX_128", "RX_256", "RX_512", "RX_1024", "RX_1519",
        "RX_OSIZE", "RX_JAB", "RX_DROP", "RX_CARRIER", "RX_ORUN", "RX_STAT_OVFL" };

extern ncp_hdl_t inNcpHdl;


ncp_st_t rte_port_next_get(int32_t portNum, int32_t *nextPortNum, ncp_bool_t xgmac_flag)
{
    int32_t i = portNum;    
    while(++i < 120)
    {
        if(xgmac_flag)
        {
            if(strncmp(xgmac_name[i],"NULL",4) != 0)
            {
                *nextPortNum = i;
                return NCP_ST_SUCCESS;
            }
        }
        else
        {
            if(strncmp(gmac_name[i],"NULL",4) != 0)
            {
                *nextPortNum = i;
                return NCP_ST_SUCCESS;
            }
        }
    }
    return NCP_ST_ERROR;
}

ncp_st_t rte_port_mchan_get(int32_t portNum, ncp_macChan_t *macChan, ncp_bool_t xgmac_flag)
{
    if(xgmac_flag)
    {
        if(strncmp(xgmac_name[portNum],"NULL",4) == 0)
           return NCP_ST_ERROR;
    }
    else
    {
        if(strncmp(gmac_name[portNum],"NULL",4) == 0)
           return NCP_ST_ERROR;
    }
    *macChan = (ncp_macChan_t)portNum;
    return NCP_ST_SUCCESS; 
}

ncp_st_t rte_port_name_get(int32_t portNum, char *name, ncp_bool_t xgmac_flag)
{
    if(xgmac_flag)
    {
        if(strncmp(xgmac_name[portNum],"NULL",4) == 0)
           return NCP_ST_ERROR;
        else
        {
           strcpy(name,xgmac_name[portNum]);
           return NCP_ST_SUCCESS;
        }
    }
    else
    {
        if(strncmp(gmac_name[portNum],"NULL",4) == 0)
           return NCP_ST_ERROR;
        else
        {
           strcpy(name,gmac_name[portNum]);
           return NCP_ST_SUCCESS;
        }
    }
}

/*********************************************************************
* @purpose  Rte port statistics get
*
* @param    macChan    
*
* @returns  ncp_st_t  
* @end
*********************************************************************/

ncp_st_t rte_port_statistics_get(ncp_macChan_t macChan, ncp_bool_t xgmac_flag,
            ncp_mac_txstat_t *tx_mac_stats,
            ncp_mac_rxstat_t *rx_mac_stats)
{
    int             i;
    ncp_st_t        ncpStatus = NCP_ST_SUCCESS;
    //ncp_uint32_t    devNum = 0;
    //ncp_hdl_t       ncpHdl = NULL;
    //ncp_dev_hdl_t   devHdl = NULL;
    //ncp_device_info_t  di;
    //ncp_uint32_t     chip = 0;
    ncp_uint32_t    sreset, zero_out;
    ncp_bdata_t     *rx_stats;
    ncp_bdata_t     *tx_stats;
    //ncp_t           *ncp       = NULL;
    //ncp_eioa_t      *eioa      = NULL;
    //ncp_eioas_t     *eioas     = NULL;
    //ncp_macChan_t   port;
    //ncp_port_t      *ncp_port  = NULL;
    //ncp_uint32_t    eioa_index  = 0;
    //ncp_uint32_t    port_index  = 0;


    sreset = 1;
    zero_out = 0;

    rx_stats = (ncp_bdata_t *)rx_mac_stats;
    tx_stats = (ncp_bdata_t *)tx_mac_stats;
    for (i = 0; i < TX_STAT_CNT; i++)
    {
        tx_stats[i].h = 0;
        tx_stats[i].l = 0;
        rx_stats[i].h = 0;
        rx_stats[i].l = 0;
    }

    rx_stats[i].h = 0;
    rx_stats[i].l = 0;
#if 0
    NCP_CALL(ncp_config_attach(devNum, &ncpHdl));
    ncp = (ncp_t *)inNcpHdl;
    eioas = ncp->eioaHdl;
    port = macChan;
    NCP_CALL(ncp_config_dev_hdl_get(ncpHdl, &devHdl));

    NCP_CALL(ncp_device_info_get(ncpHdl, &di));

    chip = di.revId.chipType;

    if (chip == NCP_CHIP_ACP55xx)
    {
        /* Validate the MAC Channel */
        NCP_EIOA_PORT_VALIDATE_55xx(ncp, port);

        eioa_index = NCP_EIOA_TO_INDEX_55xx(macChan);
        if (eioa_index == 0xFFFF)
        {
            NCP_CALL(NCP_ST_MAC_INVALID_MAC);
        }

        port_index = NCP_EIOA_PORT_TO_INDEX_55xx(ncp, macChan);
        if (port_index == 0xFFFF)
        {
            NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);
        }

        eioa = eioas->eioa[eioa_index];
        ncp_port = eioa->port[port_index];
        if (ncp_port->chanType >= NCP_MAC_CHAN_CONFIG_XAUI)
        {
            if (xgmac_flag != TRUE) 
            {
                NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);
            }
        }
        else
        {
            if ( xgmac_flag != FALSE)
            {
                NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);
            }
        }
    }

    NCP_CALL(ncp_eioa_mac_statistics_get(
                ncpHdl,
                macChan,
                tx_mac_stats,
                rx_mac_stats,
                (sreset == 1 ? TRUE : FALSE)));
#else
    ncpStatus = ncp_eioa_mac_statistics_get(
                inNcpHdl,
                macChan,
                tx_mac_stats,
                rx_mac_stats,
                (sreset == 1 ? TRUE : FALSE));
    if(ncpStatus != NCP_ST_SUCCESS)
    {
        LOG_ERROR("rte_port_statistics_get port %d ncpStatus =%d line:%d\n",macChan,ncpStatus,__LINE__); 
        return (int)ncpStatus;
    }
#endif
#ifdef __PORT_DBG__
    if (xgmac_flag)
    {
        LOG_INFO("TX Statistics for port: %s\n", xgmac_name[macChan]);
    }
    else
    {
        LOG_INFO("TX Statistics for port: %s\n", gmac_name[macChan]);
    }

    for (i = 0; i < TX_STAT_CNT; i++)
    {
        if (zero_out == 1)
        {
            LOG_INFO("%s : 0x%08x%08x\n", tx_stat_name[i],
               tx_stats[i].h, tx_stats[i].l);
        }
        else
        {
            if (i == 0)
            {
                /*
                 * Always print first value
                 */
                LOG_INFO("%s 0x%08x%08x\n", tx_stat_name[i],
                   tx_stats[i].h, tx_stats[i].l);
            }
            else if ((tx_stats[i].h !=  0) || (tx_stats[i].l != 0))
            {
                LOG_INFO("%s : 0x%08x%08x\n", tx_stat_name[i],
                   tx_stats[i].h, tx_stats[i].l);
            }
        }
    }


    if (xgmac_flag)
    {
        LOG_INFO("RX Statistics for port: %s\n", xgmac_name[macChan]);
    }
    else
    {
        LOG_INFO("RX Statistics for port: %s\n", gmac_name[macChan]);
    }
    for (i = 0; i < RX_STAT_CNT; i++)
    {
        if (zero_out == 1)
        {
            LOG_INFO("%s : 0x%08x%08x\n", rx_stat_name[i],
               rx_stats[i].h, rx_stats[i].l);
        }
        else
        {
            if (i == 0)
            {
                /*
                 * Always print first value
                 */
                LOG_INFO("%s 0x%08x%08x\n", rx_stat_name[i],
                   rx_stats[i].h, rx_stats[i].l);
            }
            else if ((rx_stats[i].h !=  0) || (rx_stats[i].l != 0))
            {
                LOG_INFO("%s 0x%08x%08x\n", rx_stat_name[i],
                   rx_stats[i].h, rx_stats[i].l);
            }
        }
    }
#endif

NCP_RETURN_LABEL
    //if (ncpHdl != NULL)
    //{
    //    ncp_config_detach(ncpHdl);
    //}

    if ((ncpStatus == NCP_ST_EIOA_PORT_NOT_CONFIGURED) || (ncpStatus == NCP_ST_EIOA_INVALID_PORT_CONFIG))
    {
        if (xgmac_flag)
            LOG_INFO("%s has not been CONFIGURED. No statistics available.\n",
                xgmac_name[macChan]);
        else
            LOG_INFO("%s has not been CONFIGURED. No statistics available.\n",
                gmac_name[macChan]);
    }

    if ((ncpStatus != NCP_ST_SUCCESS) && (ncpStatus != NCP_ST_EIOA_PORT_NOT_CONFIGURED) && (ncpStatus != NCP_ST_EIOA_INVALID_PORT_CONFIG))
    {
        ncp_status_print("Error", ncpStatus);
    }

    return (int)ncpStatus;
}


/*********************************************************************
* @purpose  Rte port link status get
*
* @param    macChan    
*
* @returns  ncp_st_t  
* @end
*********************************************************************/

ncp_st_t rte_port_link_status_get(ncp_macChan_t macChan, ncp_bool_t xgmac_flag, ncp_mac_phy_status_t *phyStatus)
{
    int             skip, c;
    ncp_st_t        ncpStatus = NCP_ST_SUCCESS;
    //ncp_uint32_t    devNum = 0;
    //ncp_hdl_t       ncpHdl = NULL;
    ncp_uint32_t    mode = 0x18;
    //ncp_dev_info_t  info;
    //ncp_port_t      ncp_port;
    ncp_bool_t      flag; 
    
#ifdef __PORT_DBG__
    const char *port_speed[] = {"10Mbit", "100Mbit" ,"1Gbit", "RESERVED"};
    const char *port_duplex[] = {"Half", "Full" };
    const char *link_ok[] = {"Link = Down ", "Link = Up" };
    const char *bool_flag[] = {"FALSE" , "TRUE"};

    
    LOG_INFO("rte_port_link_status_get line %d\n",__LINE__);
#endif    
    /* Get device information */
    //NCP_CALL(ncp_dev_info(&info));

    //NCP_CALL(ncp_config_attach(devNum, &ncpHdl));
    //NCP_CALL(ncp_eioa_status_get(ncpHdl, macChan, &ncp_port, &flag));
    ncpStatus = ncp_eioa_mac_link_status_get( inNcpHdl, macChan, phyStatus, &mode);
    if(ncpStatus != NCP_ST_SUCCESS)
    {
        //LOG_ERROR("rte_port_link_status_get port %d ncpStatus =%d line:%d\n",macChan,ncpStatus,__LINE__); 
        return (int)ncpStatus;
    }
#ifdef __PORT_DBG__
    LOG_INFO("phyStatus:  Configured = %d,linkStatus = %d,speed= %d,duplex =%d,remoteFault =%d,autoNegDone =%d",
        phyStatus->configured,phyStatus->linkStatus,phyStatus->speed,
        phyStatus->duplex,phyStatus->remoteFault,phyStatus->autoNegDone);
    /*
     * Phy configured
     */
        LOG_INFO("PHY for Port %s \n  Configured = %s\n", 
              (xgmac_flag == TRUE ? xgmac_name[macChan] : gmac_name[macChan]), 
               bool_flag[(mode & 0x00000040) >> 6]);

    /*
     * SGMII Link has gained sync and is ok to use.
     *
     * For Clause 45:  This is the bit 2 of the PMA Status 1 register (1x0001).
     */

    LOG_INFO("  Port %s \n", link_ok[(mode & 0x00000020) >> 5]);

    /*
     * Value of the speed mode bits coming from the SGMII module.
     * 00 = 10 Mbs mode.
     * 01 = 100 Mbs mode.
     * 10 = 1 Gbps mode.
     * 11 = Reserved. 0x0
     * For XGMACs always 10Gbps
     */

    if (xgmac_flag) 
    {
        LOG_INFO("  Speed = 10Gbps \n");
    }
    else
    {
        LOG_INFO("  Speed =  %s \n", port_speed[(mode & 0x00000018) >> 3]);
    }

    /*
     * Value of the duplex bit coming from the SGMII module.
     * for XGMAC the duplex is always Full.
     */
    if (xgmac_flag)
    {
        LOG_INFO("  Duplex = Full \n");      
    }
    else
    {
        LOG_INFO("  Duplex = %s \n", port_duplex[(mode & 0x00000004) >> 2]);      
    }

    /*
     * In fiber mode, a fault has been detected. These bits correspond to
     * the RF1 and RF2 bits defined in section 37.2.1.5 of the IEEE 802.3
     * specification.
     * 
     * For Clause 45:  This is the bit 7 of the PMA Status 1 register (1x0001).
     */
    LOG_INFO("  Remote Fault = %s\n", bool_flag[((mode & 0x00000002) >> 1)]);

    /*
     * Auto-negotiation process complete indication.
     */
    LOG_INFO("  AN Complete = %s \n\n", bool_flag[mode & 0x00000001]);
#endif

NCP_RETURN_LABEL
    //if (ncpHdl != NULL)
    //{
    //    ncp_config_detach(ncpHdl);  
    //}
 
    return (int)ncpStatus;
}


#endif
