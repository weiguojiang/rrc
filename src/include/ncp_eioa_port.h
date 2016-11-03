/**************************************************************************
 **                                                                       *
 **                           Intel CONFIDENTIAL                            *
 **                           PROPRIETARY NOTE                            *
 **                                                                       *
 **    This software contains information confidential and proprietary    *
 **    to Intel Corporation.  It shall not be reproduced in whole or in *
 **    part, or transferred to other documents, or disclosed to third     *
 **    parties, or used for any purpose other than that for which it was  *
 **    obtained, without the prior written consent of Intel Corporation.*
 **    (c) 2008-2014, Intel Corporation.  All rights reserved.          *
 **                                                                       *
 **                                                                       *
 **  **********************************************************************/

/*! @file      ncp_eioa_port.h
 *  @brief     EIOA Port
 *
 *             EIOA Switch Port related APIs, defines and structure definitions.
 *
 *  @defgroup _eioa_port_ EIOA Port
 *  @ingroup _eioa_
 *
 *  @{
 */

#ifndef _NCP_EIOA_PORT_H_
#define _NCP_EIOA_PORT_H_

#ifdef __cplusplus
extern "C" {
#endif


/* Public Definitions */

/* Public Enumerated Types */

/*!
 *  @brief  Set cvlan to svlan mapping for the given port
 *
 *  @param[in]  ncpHdl        Handle for the NCP that the EIOA port is part of.
 *  @param[in]  port          The port number for which the mapping needs to be set.
 *  @param[in]  cvlanId       The cvlan id that needs to be mapped. 
 *  @param[in]  vlanId        The svlan id that needs to be mapped.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_PORT_NON_QINQ
 *      \li ::NCP_ST_EIOA_INVALID_CVLAN_ID
 *      \li ::NCP_ST_EIOA_INVALID_VLAN_ID
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_qinq_cvlan_map_set(ncp_hdl_t ncpHdl, ncp_macChan_t port,
    ncp_uint16_t cvlanId, ncp_uint16_t vlanId);

/*!
 *  @brief  Get the svlan id mapped to the given port/cvlan id
 *
 *  @param[in]  ncpHdl        Handle for the NCP that the EIOA is part of.
 *  @param[in]  port          The port number for which the mapping needs to be fetched.
 *  @param[in]  cvlanId       The cvlan id for which the svlan id needs to be fetched.
 *  @param[out] vlanId        The buffer where the svlan id value is written.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_PORT_NON_QINQ
 *      \li ::NCP_ST_EIOA_INVALID_CVLAN_ID
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_qinq_cvlan_map_get(ncp_hdl_t ncpHdl, ncp_macChan_t port,
    ncp_uint16_t cvlanId, ncp_uint16_t* vlanId);

/*!
 *  @brief  Remove the cvlan/svlan mapping for this port.
 *
 *  @param[in]  ncpHdl        Handle for the NCP that the EIOA is part of.
 *  @param[in]  port          The port number for which the mapping needs to be removed.
 *  @param[in]  cvlanId       The cvlan id for which the mapping needs to be removed.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_PORT_NON_QINQ
 *      \li ::NCP_ST_EIOA_INVALID_CVLAN_ID
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_qinq_cvlan_map_rem(ncp_hdl_t ncpHdl, ncp_macChan_t port,
    ncp_uint16_t cvlanId);

/*!
 *  @brief  Configure vlan id and one2oneSvlan for this port in ingress direction.
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[in]  port            The port number for which the vlan id needs to be set.
 *  @param[in]  vlanId          The vlan id to be configured.
 *  @param[in]  bOne2oneSvlan   one2oneSvlan to be configured.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_INVALID_VLAN_ID
 *      \li ::NCP_ST_EIOA_VLAN_ID_ALREADY_DEFINED
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_vlan_set(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
                               ncp_uint16_t vlanId,
                               ncp_bool_t bOne2oneSvlan);

/*!
 *  @brief  Query one2oneSvlan for a given port and vlan id.
 *
 *  @param[in]   ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[in]   port            The port number for which the vlan id needs to be set.
 *  @param[in]   vlanId          The vlan id for which the tagging needs to be configured.
 *  @param[out]  bOne2oneSvlan   Buffer to store one2oneSvlan value.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_INVALID_VLAN_ID
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_vlan_get(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
                               ncp_uint16_t vlanId,
                               ncp_bool_t *bOne2oneSvlan);


/*!
 *  @brief  Remove vlan id from this port for ingress direction.
 *
 *  @param[in]   ncpHdl                 Handle for the NCP that the EIOA is part of.
 *  @param[in]   port                   The port number for which the vlan id needs to be set.
 *  @param[in]   vlanId                 The vlan id for which the tagging needs to be configured.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_INVALID_VLAN_ID
 *      \li ::NCP_ST_EIOA_PORT_DEFAULT_VLAN_ID
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_vlan_rem(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
                               ncp_uint16_t vlanId);

/*!
 *  @brief  Configure vlan id one2oneSvlan and virtual domain id for this port 
 *          in ingress direction.
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[in]  port            The port number for which the vlan id needs to be set.
 *  @param[in]  vlanId          The vlan id to be configured.
 *  @param[in]  bOne2oneSvlan   one2oneSvlan to be configured.
 *  @param[in]  virtualDomainId virtual domain id to be configured.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_INVALID_VLAN_ID
 *      \li ::NCP_ST_EIOA_VLAN_ID_ALREADY_DEFINED
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_vlan_id_set2(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
                                ncp_uint16_t vlanId,
                                ncp_bool_t bOne2oneSvlan,
                                ncp_uint16_t virtualDomainId);

/*!
 *  @brief  Query one2oneSvlan and virtual domain id for a given port and vlan id.
 *
 *  @param[in]   ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[in]   port            The port number for which the vlan id needs to be set.
 *  @param[in]   vlanId          The vlan id for which the tagging needs to be configured.
 *  @param[out]  bOne2oneSvlan   Buffer to store one2oneSvlan value.
 *  @param[out]  virtualDomainId Buffer to store virtual domain id value.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_INVALID_VLAN_ID
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_vlan_id_get2(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
                                ncp_uint16_t vlanId,
                                ncp_bool_t *bOne2oneSvlan,
                                ncp_uint16_t *virtualDomainId);

/*!
 * @brief Ingress VLAN Id Info query data structure.
 */
typedef struct ncp_eioa_port_ingress_vlan_info_st
{
    /*! @brief mac channel info */
    ncp_macChan_t 	port;

    /*! @brief vlan ID  */
    ncp_uint16_t vlanId;

    /*! @brief one2oneSvlan value */
    ncp_bool_t	bOne2oneSvlan;	 

    /*! @brief layer_2_domain applicable to 56xx only */
    ncp_uint16_t  layer_2_domain;
 
} ncp_eioa_port_ingress_vlan_info_t;


/*!
* @brief  Callback function for VLAN List functions
* @details
* This callback function is invoked for each valid VLAN ID along with the applicaton specified callback
* data.
* @param[in] appData  	   Application specified opaque data
* @param[in] vlanInfo      structure containing VLAN Info. 
*/
typedef void (*ncp_eioa_port_ingress_vlan_list_cb_fn_t) (void *appData, 
					ncp_eioa_port_ingress_vlan_info_t *vlanInfo); 

/*!
 *  @brief  List the Ingress vlan id information for a given port. 
 *  This API is used to list the Ingress VLAN ID and corresponding one2OneSvlan information. The callback
 *  is invoked for each of the valid VLAN Ids.
 *	 
 *
 *  @param[in]   ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[in]   port            The port number for which the vlan id list is queried.
 *  @param[in]   listfn		 Application specified callback function. This function is invoked for
 *				 each valid VLAN. This function is invoked with application specified
 *				 opaque data (appData)  and ingress VLAN ID information.
 *  @param[in]   appData	 An application-specified opaque value that is passed to the listfn 
 *				 callback function.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_vlan_list_get(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
                               ncp_eioa_port_ingress_vlan_list_cb_fn_t listfn,
                               void *appData);

/*!
 *  @brief  Configure untagged cvlan id, cvlan cos and non-qinq vlan tagging for 
 *          this port in egress direction.
 *
 *  @param[in]  ncpHdl                  Handle for the NCP that the EIOA is part of.
 *  @param[in]  port                    The port number for which the vlan id needs to be set.
 *  @param[in]  vlanId                  The vlan id for which the tagging needs to be configured.
 *  @param[in]  qinqUntaggedCvlanId     cvlan id to be set for untagged egress packets.
 *  @param[in]  qinqUntaggedCvlanCos    cvlan cos to be set for untagged egress packets.
 *  @param[in]  nonQinqTagEnable        vlan tagging to be set for non-qinq packets.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_INVALID_VLAN_ID
 *      \li ::NCP_ST_EIOA_INVALID_CVLAN_ID
 *      \li ::NCP_ST_EIOA_COS_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_port_egress_vlan_set(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
                              ncp_uint16_t vlanId, 
                              ncp_uint16_t qinqUntaggedCvlanId,
                              ncp_uint8_t qinqUntaggedCvlanCos,
                              ncp_bool_t nonQinqTagEnable);

/*!
 *  @brief  Query untagged cvlan id, cvlan cos and non-qinq vlan tagging for 
 *          this port in egress direction. 
 *
 *  @param[in]   ncpHdl                 Handle for the NCP that the EIOA is part of.
 *  @param[in]   port                   The port number for which the vlan id needs to be set.
 *  @param[in]   vlanId                 The vlan id for which the tagging needs to be configured.
 *  @param[out]  qinqUntaggedCvlanId    Buffer to store cvlan id for untagged egress packets.
 *  @param[out]  qinqUntaggedCvlanCos   Buffer to store cvlan cos for untagged egress packets.
 *  @param[out]  nonQinqTagEnable       Buffer to store vlan tagging for non-qinq packets.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_INVALID_VLAN_ID
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 */
NCP_API ncp_st_t
ncp_eioa_port_egress_vlan_get(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
                       ncp_uint16_t vlanId,
                       ncp_uint16_t *qinqUntaggedCvlanId,
                       ncp_uint8_t *qinqUntaggedCvlanCos,
                       ncp_bool_t *nonQinqTagEnable);

/*!
 *  @brief  Remove vlan id from this port for egress direction.
 *
 *  @param[in]   ncpHdl                 Handle for the NCP that the EIOA is part of.
 *  @param[in]   port                   The port number for which the vlan id needs to be set.
 *  @param[in]   vlanId                 The vlan id for which the tagging needs to be configured.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_INVALID_VLAN_ID
 */
NCP_API ncp_st_t
ncp_eioa_port_egress_vlan_rem(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
                              ncp_uint16_t vlanId);

/*!
 * @brief Egress VLAN info query data structure.
 */
typedef struct ncp_eioa_port_egress_vlan_info_st
{
    /*! port id is returned here */
    ncp_macChan_t 	port;	
    /*! vlan Id */
    ncp_uint16_t 	vlanId;
    /*! qinqUntaggedCvlanId corresponding to this vlanId. */
    ncp_uint16_t 	qinqUntaggedCvlanId;
    /*! qinqUntaggedCvlanCos corresponding to this vlanId. */
    ncp_uint8_t 	qinqUntaggedCvlanCos;
    /*! nonQinqTagEnable corresponding to this vlanId. */
    ncp_bool_t		nonQinqTagEnable;

} ncp_eioa_port_egress_vlan_info_t;


/*!
 * @brief  Callback function for Egress VLAN List functions
 * @details
 * This callback function is invoked for each valid egress VLAN ID along with the applicaton specified callback
 * data.
 *  @param[in]  appData 		application specified opaque data
 *  @param[in]  vlanInfo		buffer containing vlan information along with mac channel
*/
typedef void (*ncp_eioa_port_egress_vlan_list_cb_fn_t) (void *appData, 
                	      ncp_eioa_port_egress_vlan_info_t *vlanInfo); 

/*!
 *  @brief  List the Engress vlan id information for a given port. 
 *  This API is used to list the Egress VLAN ID and corresponding information. The callback
 *  is invoked for each of the egress valid VLAN Ids.
 *
 *  When the qinqUntaggedCvlanId, qinqUntaggedCvlanCos and nonQinqTagEnable are all zeros, it is
 *  assumed the entry is not programmed or removed. Callback function is not called for those VLAN IDs. 	 
 *
 *  @param[in]   ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[in]   port            The port number for which the vlan id list is queried.
 *  @param[in]   listfn		 Application specified callback function. This function is invoked for
 *				 each valid VLAN. This function is invoked with application specified
 *				 opaque data (appData) and a buffer containing the vlanId, 
 *				 qinqUntaggedCvlanId, qinqUntaggedCvlanCos,
 *				 and nonQinqTagEnable values. Input mac channel is also returned.
 *  @param[in]   appData	 An application-specified opaque value that is passed to the listfn 
 *				 callback function.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 */
NCP_API ncp_st_t
ncp_eioa_port_egress_vlan_list_get(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
                               ncp_eioa_port_egress_vlan_list_cb_fn_t listfn,
                               void *appData);

/*!
 *  @brief  Set the vlan id to be used for the given port and ethertype index.
 *
 *  @param[in]  ncpHdl        Handle for the NCP that the EIOA is part of.
 *  @param[in]  port          The port number for which the vlan id needs to be set.
 *  @param[in]  etherTypeIdx  The ethertype index for which the vlan id needs to be set.
 *  @param[in]  vlanId        The value of vlan id to be set.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_PORT_INGRESS_ETHERTYPE_IDX_INVALID
 *      \li ::NCP_ST_EIOA_INVALID_VLAN_ID
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_ethertype_vlan_set(ncp_hdl_t ncpHdl, ncp_macChan_t port,
                                         ncp_eioa_ethertype_idx_t etherTypeIdx, 
                                         ncp_uint16_t vlanId);

/*!
 *  @brief  Get the vlan id being used for the given port and ethertype index.
 *
 *  @param[in]  ncpHdl        Handle for the NCP that the EIOA is part of.
 *  @param[in]  port          The port number for which the vlan id needs to be get.
 *  @param[in]  etherTypeIdx  The ethertype index for which the vlan id needs to be get.
 *  @param[in]  vlanId        The buffer where the value of vlan id is written.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_PORT_INGRESS_ETHERTYPE_IDX_INVALID
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_ethertype_vlan_get(ncp_hdl_t ncpHdl, ncp_macChan_t port,
                                         ncp_eioa_ethertype_idx_t etherTypeIdx, 
                                         ncp_uint16_t* vlanId);

/*!
 *  @brief  Remove the vlan id being used for the given port and ethertype index.
 *
 *  @param[in]  ncpHdl        Handle for the NCP that the EIOA is part of.
 *  @param[in]  port          The port number for which the vlan id needs to be set.
 *  @param[in]  etherTypeIdx  The ethertype index for which the vlan id needs to be removed.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_PORT_INGRESS_ETHERTYPE_IDX_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_ethertype_vlan_rem(ncp_hdl_t ncpHdl, ncp_macChan_t port,
                                         ncp_eioa_ethertype_idx_t etherTypeIdx);

/*!
 *  @brief  Set the default vlan id for the port.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the EIOA is part of.
 *  @param[in]  port        The port number for which the vlan id needs to be set.
 *  @param[in]  vlanId      The value of vlan id to be set.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_INVALID_VLAN_ID
 */
NCP_API ncp_st_t
ncp_eioa_port_default_vlan_set(ncp_hdl_t ncpHdl, ncp_macChan_t port,
                               ncp_uint16_t vlanId);

/*!
 *  @brief  Get the default vlan id for the port.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the EIOA is part of.
 *  @param[in]  port        The port number for which the vlan id needs to be fetched.
 *  @param[out] vlanId      The buffer where the vlan id is writen.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 */
NCP_API ncp_st_t
ncp_eioa_port_default_vlan_get(ncp_hdl_t ncpHdl, ncp_macChan_t port,
                               ncp_uint16_t* vlanId);

/*!
 *  @brief  Set the default cvlan id for the port.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the EIOA is part of.
 *  @param[in]  port        The port number for which the cvlan id needs to be set.
 *  @param[in]  cvlanId     The value of cvlan id to be set.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_INVALID_CVLAN_ID
 */
NCP_API ncp_st_t
ncp_eioa_port_default_cvlan_set(ncp_hdl_t ncpHdl, ncp_macChan_t port,
                                ncp_uint16_t cvlanId);

/*!
 *  @brief  Get the default cvlan id for the port.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the EIOA is part of.
 *  @param[in]  port        The port number for which the cvlan id needs to be fetched.
 *  @param[out] cvlanId     The buffer where the cvlan id is writen.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 */
NCP_API ncp_st_t
ncp_eioa_port_default_cvlan_get(ncp_hdl_t ncpHdl, ncp_macChan_t port,
                                ncp_uint16_t* cvlanId);

/*!
 * @brief MACsec transmit configuration and query data structure.
 *        Applies to AXx55xx devices only. 
 * @see ncp_eioa_port_egress_macsec_set
 * @see ncp_eioa_port_egress_macsec_get
 */
typedef struct ncp_eioa_egress_macsec_st
{
    /*! @brief Use Single Copy Broadcast(SCB) indicator. */
    ncp_bool_t enableSCB;

    /*! @brief Use End Station(ES) indicator. */
    ncp_bool_t enableES;    

    /*! @brief Indicates whether Secure Channel Identifier (SCI) should be included in 
               the security tag.
     */
    ncp_bool_t includeSCI;

    /*! @brief Indicates whether the frames should be protected. */
    ncp_bool_t protectFrames;

    /*! @brief The limit value of the next packet number. When Next Packet Number 
               reaches this value, an interrupt is raised to warn about the need for 
               a new key (SA). 
     */
    ncp_uint32_t packetNumberLimit;

    /*! @brief Secure Channel Identifier (SCI). A unique 64-bit identifier for a transmit 
               secure channel. Needs to be programmed even if SCI field is not 
               included in the security tag.
     */
    ncp_uint64_t sci;
} ncp_eioa_egress_macsec_t;

/*!
 * @brief MACsec transmit Security Association (SA) configuration and query data structure.
 *        Applies to AXx55xx devices only. 
 * @see ncp_eioa_port_egress_macsec_sa_set
 * @see ncp_eioa_port_egress_macsec_sa_get
 */
typedef struct ncp_eioa_egress_macsec_sa_st
{
    /*! @brief This register enables SA for use. When set to TRUE, this SA becomes 
               active. Only one Tx SA can be active at any time. The previously 
               active SA is disabled automatically.
     */
    ncp_bool_t valid;    

    /*! @brief 128-bit SA key value used for the MACsec cipher operation. */
    ncp_uint8_t key[16];

    /*! @brief The next SA packet number (PN), a 32-bit value. Setting it to zero will 
         stop transmission and receiving of packets, if the SA is enabled for use.
     */
    ncp_uint32_t nextPacketNumber;

    /*! @brief When the set to TRUE, the confidentiality protection (e.g. encryption) 
         is performed on the frames processed with this SA. Otherwise, the data 
         is sent unencrypted (integrity protected only).
     */
    ncp_bool_t enableEncryption;
} ncp_eioa_egress_macsec_sa_t;

/*!
 * @brief Receive packet validation mode.
 *        Applies to AXx55xx devices only. 
 * @see ncp_eioa_ingress_macsec_t
 * @see ncp_eioa_port_ingress_macsec_set
 * @see ncp_eioa_port_ingress_macsec_get
 */
typedef enum ncp_eioa_macsec_validate_mode_e
{
    NCP_EIOA_MACSEC_VALIDATE_MODE_DISABLED = 0, /*!< No validation. */
    NCP_EIOA_MACSEC_VALIDATE_MODE_STRICT = 1,   /*!< Packets are validated and dropped if security check fails. */        
    NCP_EIOA_MACSEC_VALIDATE_MODE_CHECK = 2     /*!< Packets are validated and accepted. If security check fails, a counter incremented. */
} ncp_eioa_macsec_validate_mode_t;

#define NCP_EIOA_PORT_MACSEC_NUM_SA     4
#define NCP_EIOA_PORT_MACSEC_RX_NUM_SC  2
#define NCP_EIOA_PORT_MACSEC_TX_NUM_SC  1

/*!
 * @brief MACsec receive Security Association (SA) configuration and query data structure.
 *        Applies to AXx55xx devices only. 
 * @see ncp_eioa_port_ingress_macsec_set
 * @see ncp_eioa_port_ingress_macsec_get
 */
typedef struct ncp_eioa_ingress_macsec_st
{
    /*! @brief Receive packet validation mode. @see ncp_eioa_macsec_validate_mode_t. */
    ncp_eioa_macsec_validate_mode_t validateFrameMode;

    /*! @brief Enable replay protection. */
    ncp_bool_t enableReplayProtection;

    /*! @brief The replay window width. If the replay protection is enabled, the lowest 
         packet number (PN) that can be successfully validated is a difference 
         between the stored next PN and a value stored in this register. If the 
         replay window is set to zero and the replay protection is enabled, then 
         a strict frame ordering must occur in order to successfully receive the 
         next frame.
     */
    ncp_uint32_t replayWindow;

    /*! @brief Determines which SCI is used for the validation, if the SCI field is 
         not explicitly included in the secutiry tag. The valid values are 0 and 1.
         If only one Rx SC is used, this register points to a Rx SCI register 
         that contains the correct SCI.
     */
    ncp_int32_t defaultSCI;

    /*! @brief Rx Secure Channel Identifier (SCI) for both the SCs supported. 
         A unique 64-bit identifier for a Rx secure channel. Needs to be 
         programmed even if SCI field is not included in secutiry tag.
     */
    ncp_uint64_t sci[NCP_EIOA_PORT_MACSEC_RX_NUM_SC];

    /*! @brief Indicates if a receive secure channel can receive frames.
         Set to true if Rx SA for that Rx SC is valid. This is a read-only 
         attribute.
     */
    ncp_bool_t scReceive[NCP_EIOA_PORT_MACSEC_RX_NUM_SC];
} ncp_eioa_ingress_macsec_t;

/*!
 * @brief MACsec receive Security Association (SA) configuration and query data structure.
 *        Applies to AXx55xx devices only. 
 * @see ncp_eioa_port_egress_macsec_sa_set
 * @see ncp_eioa_port_egress_macsec_sa_get
 */
typedef struct ncp_eioa_ingress_macsec_sa_st
{
    /*! @brief Enables a receive secure association (Rx SA), so it can be used for 
         receiving frames for a Rx SC it belongs to. Unlike Tx SA, it is possible 
         to enable more than one SA per Rx SC. Two successive incoming Rx frames 
         can belong to different SAs for the same SC.
     */
    ncp_bool_t valid;

    /*! @brief 128-bit SA key value used for the MACsec cipher operation. */
    ncp_uint8_t key[16];

    /*! @brief The next SA packet number (PN), a 32-bit unsigned value. If a received 
         security tag PN is bigger than this value, the existing next SA PN 
         is set to the received PN incremented by 1.
     */
    ncp_uint32_t nextPacketNumber;    
} ncp_eioa_ingress_macsec_sa_t;

/*!
 *
 * @brief This API is used to enable/disable MACsec in a port. 
 *        Applies to AXx55xx devices only.
 *
 * @param[in] ncpHdl        The NCP handle.
 * @param[in] port          The port for which MACsec needs to be enabled/disabled.
 * @param[in] enableMacsec  Whether to enable or disable MACsec for this port. 
 *                          TRUE - enable MACsec. FALSE - disable MACsec.
 *
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_PORT_MACSEC_NOT_SUPPORTED
 *
 * @see ncp_eioa_port_macsec_enable_get
 * @see ncp_macChan_t
 *
 */
NCP_API ncp_st_t
ncp_eioa_port_macsec_enable_set(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
                                ncp_bool_t enableMacsec);

/*!
 *
 * @brief This API is used to query whether MACsec is enabled/disabled in a port.
 *        Applies to AXx55xx devices only. 
 *
 * @param[in]  ncpHdl        Handle for the NCP that the EIOA is part of.
 * @param[in]  port          The port for which MACsec needs to be enabled/disabled.
 * @param[out] enableMacsec  Whether MACsec is enabled/disabled for this port. 
 *                           TRUE - MACsec enabled. FALSE - MACsec disabled.
 *
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_PORT_MACSEC_NOT_SUPPORTED
 *
 * @see ncp_eioa_port_macsec_enable_set
 * @see ncp_macChan_t
 *
 */
NCP_API ncp_st_t
ncp_eioa_port_macsec_enable_get(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
                                ncp_bool_t *enableMacsec);

/*!
 *
 * @brief This API is used to configure MACsec transmit information. 
 *        Applies to AXx55xx devices only. 
 *
 * @param[in] ncpHdl    Handle for the NCP that the EIOA is part of.
 * @param[in] port      The port for which MACsec transmit information needs 
 *                      to be configured. 
 * @param[in] macsecTx  Pointer to a structure containing MACsec transmit 
 *                      information. 
 *
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_PORT_MACSEC_NOT_SUPPORTED
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 *
 * @see ncp_eioa_port_egress_macsec_get
 * @see ncp_eioa_egress_macsec_t
 * @see ncp_macChan_t
 */
NCP_API ncp_st_t
ncp_eioa_port_egress_macsec_set(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
                            ncp_eioa_egress_macsec_t *macsecTx);

/*!
 *
 * @brief This API is used to query MACsec transmit information. 
 *        Applies to AXx55xx devices only. 
 *
 * @param[in] ncpHdl    Handle for the NCP that the EIOA is part of.
 * @param[in] port      The port for which MACsec transmit information needs 
 *                      to be queried. 
 * @param[out] macsecTx Pointer to a structure where the MACsec transmit 
 *                      information is written to.
 *
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_PORT_MACSEC_NOT_SUPPORTED
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 *
 * @see ncp_eioa_port_egress_macsec_set
 * @see ncp_eioa_egress_macsec_t
 * @see ncp_macChan_t
 */
NCP_API ncp_st_t
ncp_eioa_port_egress_macsec_get(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
                            ncp_eioa_egress_macsec_t *macsecTx);

/*!
 *
 * @brief This API is used to configure MACsec transmit Security Association (SA).
 *        Applies to AXx55xx devices only. 
 *
 * @param[in] ncpHdl      Handle for the NCP that the EIOA is part of.
 * @param[in] port        The port for which MACsec transmit SA information needs 
 *                        to be configured.
 * @param[in] sa          Security Association number for which the configuration 
 *                        is being done.
 * @param[in] macsecTxSa  Pointer to a structure containing MACsec transmit SA
 *                        information. 
 *
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_PORT_MACSEC_NOT_SUPPORTED
 *      \li ::NCP_ST_EIOA_PORT_MACSEC_TX_INVALID_SA
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 *
 * @see ncp_eioa_port_egress_macsec_sa_get
 * @see ncp_eioa_egress_macsec_sa_t
 * @see ncp_macChan_t
 */
NCP_API ncp_st_t
ncp_eioa_port_egress_macsec_sa_set(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
            ncp_uint8_t sa, ncp_eioa_egress_macsec_sa_t *macsecTxSa);

/*!
 *
 * @brief This API is used to query MACsec transmit Security Association (SA).
 *        Applies to AXx55xx devices only. 
 *
 * @param[in]  ncpHdl      Handle for the NCP that the EIOA is part of.
 * @param[in]  port        The port for which MACsec transmit SA information needs 
 *                         to be queried.
 * @param[in]  sa          Security Association number for which the configuration 
 *                         is being queried.
 * @param[out] macsecTxSa  Pointer to a MACsec transmit SA structure where 
 *                         information is written to. 
 *
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_PORT_MACSEC_NOT_SUPPORTED
 *      \li ::NCP_ST_EIOA_PORT_MACSEC_TX_INVALID_SA
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 *
 * @see ncp_eioa_port_egress_macsec_sa_set
 * @see ncp_eioa_egress_macsec_sa_t
 * @see ncp_macChan_t
 */
NCP_API ncp_st_t
ncp_eioa_port_egress_macsec_sa_get(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
            ncp_uint8_t sa, ncp_eioa_egress_macsec_sa_t *macsecTxSa);

/*!
 *
 * @brief This API is used to configure MACsec receive information. 
 *        Applies to AXx55xx devices only. 
 *
 * @param[in] ncpHdl    Handle for the NCP that the EIOA is part of.
 * @param[in] port      The port for which MACsec receive information needs 
 *                      to be configured. 
 * @param[in] macsecRx  Pointer to a structure containing MACsec receive 
 *                      information. 
 *
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_PORT_MACSEC_NOT_SUPPORTED
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 *
 * @see ncp_eioa_port_ingress_macsec_get
 * @see ncp_eioa_ingress_macsec_t
 * @see ncp_macChan_t
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_macsec_set(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
                            ncp_eioa_ingress_macsec_t *macsecRx);

/*!
 *
 * @brief This API is used to query MACsec receive information. 
 *        Applies to AXx55xx devices only. 
 *
 * @param[in] ncpHdl    Handle for the NCP that the EIOA is part of.
 * @param[in] port      The port for which MACsec receive information needs 
 *                      to be queried. 
 * @param[out] macsecRx Pointer to a structure where the MACsec receive 
 *                      information is written to.
 *
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_PORT_MACSEC_NOT_SUPPORTED
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 *
 * @see ncp_eioa_port_ingress_macsec_get
 * @see ncp_eioa_ingress_macsec_t
 * @see ncp_macChan_t
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_macsec_get(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
                            ncp_eioa_ingress_macsec_t *macsecRx);

/*!
 *
 * @brief This API is used to configure MACsec receive Security Association (SA).
 *        Applies to AXx55xx devices only. 
 *
 * @param[in] ncpHdl      Handle for the NCP that the EIOA is part of.
 * @param[in] port        The port for which MACsec receive SA information needs 
 *                        to be configured.
 * @param[in] sc          Security Channel number for which the configuration 
 *                        is being done.
 * @param[in] sa          Security Association number for which the configuration 
 *                        is being done.
 * @param[in] macsecRxSa  Pointer to a structure containing MACsec receive SA
 *                        information. 
 *
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_PORT_MACSEC_NOT_SUPPORTED
 *      \li ::NCP_ST_EIOA_PORT_MACSEC_TX_INVALID_SC
 *      \li ::NCP_ST_EIOA_PORT_MACSEC_TX_INVALID_SA
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 *
 * @see ncp_eioa_port_ingress_macsec_sa_get
 * @see ncp_eioa_ingress_macsec_sa_t
 * @see ncp_macChan_t
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_macsec_sa_set(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
            ncp_uint8_t sc, ncp_uint8_t sa, ncp_eioa_ingress_macsec_sa_t *macsecRxSa);

/*!
 *
 * @brief This API is used to query MACsec receive Security Association (SA).
 *        Applies to AXx55xx devices only. 
 *
 * @param[in]  ncpHdl      Handle for the NCP that the EIOA is part of.
 * @param[in]  port        The port for which MACsec receive SA information needs 
 *                         to be queried.
 * @param[in]  sc          Security Channel number for which the query
 *                         is being done.
 * @param[in]  sa          Security Association number for which the query
 *                         is being done.
 * @param[out] macsecRxSa  Pointer to a MACsec receive SA structure where
 *                         information is written to. 
 *
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_PORT_MACSEC_NOT_SUPPORTED
 *      \li ::NCP_ST_EIOA_PORT_MACSEC_TX_INVALID_SC
 *      \li ::NCP_ST_EIOA_PORT_MACSEC_TX_INVALID_SA
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 *
 * @see ncp_eioa_port_ingress_macsec_sa_set
 * @see ncp_eioa_ingress_macsec_sa_t
 * @see ncp_macChan_t
 */
NCP_API ncp_st_t
ncp_eioa_port_ingress_macsec_sa_get(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
            ncp_uint8_t sc, ncp_uint8_t sa, ncp_eioa_ingress_macsec_sa_t *macsecRxSa);

/*!
 * @brief MACsec stats query and clear data struct.
 *        Applies to AXx55xx devices only. 
 * @see ncp_eioa_port_macsec_stats_get
 */

typedef struct ncp_eioa_port_macsec_stats_st
{
    /*! 
     * @brief Clear all macsec stats for the port.
     */
    ncp_bool_t stats_clear_all;
    
    struct 
    {
        /*! 
         * @brief Clear egress macsec stats for the port.
         */
        ncp_bool_t stats_clear;
        
        /*! 
         * @brief Tx packets sent without MACsec processing because 
         * protectFrames=0.
         */
        ncp_uint64_t untagged;

        /*! 
         * @brief Tx packets marked for discard because their length is greater 
         * than 'Tx Max Packet Bytes'.
         */
        ncp_uint64_t dropped_too_long;

        /*! 
         * @brief The packets are discarded because length is less than 
         * 13 bytes (Destination Address + Source Address + 1 byte).
         */
        ncp_uint64_t dropped_too_short;

        /*! 
         * @brief TX discarded controlled port packets that are formed properly 
         * but are discarded because either cport_en or cport_mac_oper are 0.
         */
        ncp_uint64_t dropped_cport_not_enabled;

        /*! 
         * @brief Count of the Uncontrolled Port packets passed through MSEC in 
         * the Tx direction.
         */
        ncp_uint64_t uncontrolled;
        
        struct 
        {
            /*! 
             * @brief Clear egress SC macsec stats for the port.
             */
            ncp_bool_t stats_clear;
            
            /*! 
             * @brief Tx bytes per SC (for all SAs) with integrity protection 
             * but without encryption.
             */
            ncp_uint64_t protected_bytes;

            /*! 
             * @brief Tx bytes per SC (for all SAs) using encryption and 
             * integrity protection.
             */
            ncp_uint64_t encrypted_bytes;

            struct 
            {
                /*! 
                 * @brief Clear egress SA macsec stats for the port.
                 */
                ncp_bool_t stats_clear;
                
                /*! 
                 * @brief Tx packets processed per SA without encryption, just 
                 * with integrity protection.
                 */
                ncp_uint32_t protect;

                /*! 
                 * @brief Tx encrypted packets processed per SA.
                 */
                ncp_uint32_t encrypted;
            } sa[NCP_EIOA_PORT_MACSEC_NUM_SA];
        } sc;
    } egress;
    struct 
    {
        /*! 
         * @brief Clear ingress macsec stats for the port.
         */
        ncp_bool_t stats_clear;
        
        /*! 
         * @brief Rx packets without SecTAG when validateFrames!=Strict.
         */
        ncp_uint64_t untagged;

        /*! 
         * @brief Rx discarded packets without SecTAG when validateFrames=Strict
         */
        ncp_uint64_t no_tag;

        /*! 
         * @brief Rx discarded packets with an invalid SecTAG or ICV or a zero 
         * value PN
         */
        ncp_uint64_t bad_tag;

        /*! 
         * @brief Rx packets with unknown SCI when validateFrames!=Strict and 
         * SecTAG's C bit is not set.
         */
        ncp_uint64_t unknown_sci;

        /*! 
         * @brief Rx discarded packets with unknown SCI when validateFrames=Strict 
         * or SecTAG's C bit is set.
         */
        ncp_uint64_t no_sci;

        /*! 
         * @brief This register stores the number of packets that directly went 
         * through PTI Rx, without entering the core, because either cport_en 
         * was 0 or cport_mac_oper was 0.
         */
        ncp_uint64_t passthrough;

        /*! 
         * @brief Count of the Uncontrolled Port packets passed through MSEC in 
         * the Rx direction, excluding the timestamp packets.
         */
        ncp_uint64_t uncontrolled;

        struct 
        {
            /*! 
             * @brief Clear ingress SC macsec stats for the port.
             */
            ncp_bool_t stats_clear;
            
            /*! 
             * @brief Rx packets per SC whose PN is lower than 'Lowest PN'
             */
            ncp_uint64_t dropped_late;

            /*! 
             * @brief Rx packets per SC whose PN is lower than 'Lowest PN'.
             */
            ncp_uint64_t delayed;

            /*! 
             * @brief Rx packets per SC, that were not checked.
             */
            ncp_uint64_t unchecked;

            /*! 
             * @brief Rx bytes per SC of plaintext recovered from packets that 
             * were integrity protected but not encrypted.
             */
            ncp_uint64_t validated_bytes;

            /*! 
             * @brief Rx bytes per SC of plaintext recovered from  packets that 
             * were integrity protected and encrypted.
             */
            ncp_uint64_t decrypted_bytes;

            struct 
            {
                /*! 
                 * @brief Clear ingress SA macsec stats for the port.
                 */
                ncp_bool_t stats_clear;
                
                /*! 
                 * @brief Rx packets for the SA not in use, which are  unencrypted 
                 * when validateFrames!=Strict mode.
                 */
                ncp_uint32_t unused_sa;

                /*! 
                 * @brief Rx discarded packets for the SA not in use, which have 
                 * either the packets encrypted (C=1) or validateFrames=Strict.
                 */
                ncp_uint32_t not_using_sa;

                /*! 
                 * @brief Rx discarded packets that are not valid and one of the 
                 * following is true: the packets are encrypted or 
                 * validateFrames=Strict.
                 */
                ncp_uint32_t dropped_not_valid;

                /*! 
                 * @brief Rx packets that are not valid and validateFrames=Check.
                 */
                ncp_uint32_t dropped_invalid;

                /*! 
                 * @brief Rx packets validate OK.
                 */
                ncp_uint32_t ok;
            } sa[NCP_EIOA_PORT_MACSEC_NUM_SA];
        } sc[NCP_EIOA_PORT_MACSEC_RX_NUM_SC];
    } ingress;
} ncp_eioa_port_macsec_stats_t;

/*!
 *
 * @brief This API is used to query and clear the MACsec stats for the given port.
 *        Applies to AXx55xx devices only. The statistics cannot be correlated
 *        when they are queried with traffic passing.
 *
 * @param[in]  ncpHdl      Handle for the NCP that the EIOA is part of.
 * @param[in]  port        The port for which MACsec receive SA information needs 
 *                         to be queried.
 * @param[out] stats       Pointer to a MACsec stats structure where
 *                         statistics are written to. 
 *
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_PORT_MACSEC_NOT_SUPPORTED
 *      \li ::NCP_ST_EIOA_PORT_MACSEC_TX_INVALID_SC
 *      \li ::NCP_ST_EIOA_PORT_MACSEC_TX_INVALID_SA
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 *
 * @see ncp_eioa_port_macsec_stats_t
 */
NCP_API ncp_st_t
ncp_eioa_port_macsec_stats_get(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
            ncp_eioa_port_macsec_stats_t *stats);
/*!
 *  @brief  Set Non-QinQ-router VLAN Mapping for a given port and id
 *
 *  @param[in]  ncpHdl        Handle for the NCP that the EIOA port is part of.
 *  @param[in]  port          The port number for which the mapping needs to be set.
 *  @param[in]  id	      The id that needs to be mapped. Valid: 0-255
 *  @param[in]  newVlanId     The router VLAN ID to map to.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_INVALID_VLAN_ID
 *      \li ::NCP_ST_EIOA_VLAN_MAP_PRESENT
 */
NCP_API ncp_st_t
ncp_eioa_port_egress_non_qinq_router_vlan_map_set(ncp_hdl_t ncpHdl, ncp_macChan_t port,
    ncp_uint8_t id, ncp_uint16_t newVlanId);

/*!
 *  @brief  Get the non-QinQ-Router VLAN id mapped to the given id
 *
 *  @param[in]  ncpHdl        Handle for the NCP that the EIOA is part of.
 *  @param[in]  port          The port number for which the mapping needs to be fetched.
 *  @param[in]  id	      The id for which the mapped router vlan id needs to be fetched.valid:0-255
 *  @param[out] newVlanId     The buffer where the vlan Id value is written.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 *      \li ::NCP_ST_EIOA_MAP_NOT_SET
 */
NCP_API ncp_st_t
ncp_eioa_port_egress_non_qinq_router_vlan_map_get(ncp_hdl_t ncpHdl, ncp_macChan_t port,
    ncp_uint8_t id, ncp_uint16_t* newVlanId);


/*!
 *  @brief  Remove the Non QinQ router VLAN Id mapping for this port.
 *
 *  @param[in]  ncpHdl        Handle for the NCP that the EIOA is part of.
 *  @param[in]  port          The port number for which the mapping needs to be removed.
 *  @param[in]  id	      The id for which the mapping needs to be removed. Valid:0-255
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_PORT_CONFIG
 *      \li ::NCP_ST_MAC_INVALID_MAC
 *      \li ::NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *      \li ::NCP_ST_EIOA_MAP_NOT_SET
 */
NCP_API ncp_st_t
ncp_eioa_port_egress_non_qinq_router_vlan_map_rem(ncp_hdl_t ncpHdl, ncp_macChan_t port,
    ncp_uint8_t id);



#ifdef __cplusplus
}
#endif

#endif /* #ifndef _NCP_EIOA_PORT_H_ */

/*
 *  @}
 */

