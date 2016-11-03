/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


/*! @file      ncp_eioa_common.h
 *  @brief     EIOA Common
 *
 *             EIOA Switch Common APIs, defines and structure definitions.
 *
 *  @defgroup _eioa_common_ EIOA Common
 *  @ingroup _eioa_
 *
 *  @{
 */

#ifndef _NCP_EIOA_COMMON_H_
#define _NCP_EIOA_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif


/* Public Definitions */

/* Public Enumerated Types */

/*!
 * @brief EIOA IP protocol indicies.
 */
typedef enum ncp_eioa_ip_proto_idx_e
{
    NCP_EIOA_IP_PROTO_IDX_ICMP       = 0,
    NCP_EIOA_IP_PROTO_IDX_IGMP       = 1,
    NCP_EIOA_IP_PROTO_IDX_TCP        = 2,
    NCP_EIOA_IP_PROTO_IDX_UDP        = 3,
    NCP_EIOA_IP_PROTO_IDX_USER0      = 4,
    NCP_EIOA_IP_PROTO_IDX_USER1      = 5,
    NCP_EIOA_IP_PROTO_IDX_USER2      = 6,
    NCP_EIOA_IP_PROTO_IDX_USER3      = 7,
    NCP_EIOA_IP_PROTO_IDX_USER4      = 8,
    NCP_EIOA_IP_PROTO_IDX_USER5      = 9,
    NCP_EIOA_IP_PROTO_IDX_USER6      = 10,
    NCP_EIOA_IP_PROTO_IDX_USER7      = 11,
    NCP_EIOA_IP_PROTO_IDX_USER8      = 12,
    NCP_EIOA_IP_PROTO_IDX_USER9      = 13,
    NCP_EIOA_IP_PROTO_IDX_USER10     = 14,
    NCP_EIOA_IP_PROTO_IDX_UNKNOWN    = 15,    
    NCP_EIOA_IP_PROTO_IDX_ANY        = 16,
    NCP_EIOA_IP_PROTO_IDX_MAX        = 17,
} ncp_eioa_ip_proto_idx_t;

/*!
 * @brief EIOA Ethertype protocol indicies.
 */
typedef enum ncp_eioa_ethertype_idx_e
{
    NCP_EIOA_ETHERTYPE_IDX_IPV4          = 0,
    /*!< Applies to: AXM25xx, AXM55xx. */
    NCP_EIOA_ETHERTYPE_IDX_IPV4_FRAG     = 1,
    /*!< Applies to: AXM25xx, AXM55xx. */
    NCP_EIOA_ETHERTYPE_IDX_IPV6          = 2,
    /*!< Applies to: AXM25xx, AXM55xx. */
    NCP_EIOA_ETHERTYPE_IDX_ARP           = 3,
    /*!< Applies to: AXM25xx. */
    NCP_EIOA_ETHERTYPE_IDX_RARP          = 4,
    /*!< Applies to: AXM25xx. */
    NCP_EIOA_ETHERTYPE_IDX_MPLS          = 5,
    /*!< Applies to: AXM25xx, AXM55xx. */
    NCP_EIOA_ETHERTYPE_IDX_OAM           = 6,
    /*!< Applies to: AXM25xx. */
    NCP_EIOA_ETHERTYPE_IDX_USER0         = 7,
    /*!< Applies to: AXM25xx, AXM55xx. */
    NCP_EIOA_ETHERTYPE_IDX_USER1         = 8,
    /*!< Applies to: AXM25xx, AXM55xx. */
    NCP_EIOA_ETHERTYPE_IDX_USER2         = 9,
    /*!< Applies to: AXM25xx, AXM55xx. */
    NCP_EIOA_ETHERTYPE_IDX_USER3         = 10,
    /*!< Applies to: AXM25xx, AXM55xx. */
    NCP_EIOA_ETHERTYPE_IDX_USER4         = 11,
    /*!< Applies to: AXM25xx, AXM55xx. */
    NCP_EIOA_ETHERTYPE_IDX_USER5         = 12,
    /*!< Applies to: AXM25xx, AXM55xx. */
    NCP_EIOA_ETHERTYPE_IDX_USER6         = 13,
    /*!< Applies to: AXM25xx, AXM55xx. */
    NCP_EIOA_ETHERTYPE_IDX_USER7         = 14,
    /*!< Applies to: AXM25xx, AXM55xx. */
    NCP_EIOA_ETHERTYPE_IDX_USER8_55xx    = 3,
    /*!< Applies to: AXM55xx. */
    NCP_EIOA_ETHERTYPE_IDX_USER9_55xx    = 4,
    /*!< Applies to: AXM55xx. */
    NCP_EIOA_ETHERTYPE_IDX_USER10_55xx   = 6,
    /*!< Applies to: AXM55xx. */
    NCP_EIOA_ETHERTYPE_IDX_UNKNOWN       = 15,    
    /*!< Applies to: AXM25xx, AXM55xx. */
    NCP_EIOA_ETHERTYPE_IDX_ANY           = 16,
    /*!< Applies to: AXM25xx, AXM55xx. */
    NCP_EIOA_ETHERTYPE_IDX_MAX           = 17,
    /*!< Applies to: AXM25xx, AXM55xx. */
} ncp_eioa_ethertype_idx_t;



/* Public Structures */




/* Published APIs */

/*!
 *  @brief  Set a DSCP to COS mapping
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the EIOA is part of.
 *  @param[in]  dscpValue   The DSCP value for which the COS value will be set.
 *  @param[in]  cosValue    The COS value to set for the specified DSCP value.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_DSCP_INVALID
 *      \li ::NCP_ST_EIOA_COS_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_common_dscp_cos_set(ncp_hdl_t ncpHdl,
                             ncp_uint8_t dscpValue,
                             ncp_uint8_t cosValue);



/*!
 *  @brief  Get a DSCP to COS mapping
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the EIOA is part of.
 *  @param[in]  dscpValue   The DSCP value for which the COS value will retrived.
 *  @param[out] cosValue    Pointer to an ncp_uint8_t where the retrieved COS
 *                          value will be placed.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_DSCP_INVALID
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 */
NCP_API ncp_st_t
ncp_eioa_common_dscp_cos_get(ncp_hdl_t ncpHdl,
                             ncp_uint8_t dscpValue,
                             ncp_uint8_t *cosValue);

/*!
 *  @brief  Set a DSCP to COS mapping. Applies to AXX5600 only.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the EIOA is part of.
 *  @param[in]  dscpValue   The DSCP value for which the COS value will be set.
 *  @param[in]  cosValue    The COS value to set for the specified DSCP value.
 *  @param[in]  mplsCosValue The MPLS COS value to set for the specified DSCP value.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_DSCP_INVALID
 *      \li ::NCP_ST_EIOA_COS_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_common_dscp_mplscos_set(ncp_hdl_t ncpHdl,
                             ncp_uint8_t dscpValue,
                             ncp_uint8_t mplsCosValue);



/*!
 *  @brief  Get a DSCP to COS mapping. Applies to AXX5600 only.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the EIOA is part of.
 *  @param[in]  dscpValue   The DSCP value for which the COS value will retrived.
 *  @param[out] cosValue    Pointer to an ncp_uint8_t where the retrieved COS
 *                          value will be placed.
 *  @param[out] mplsCosValue Pointer to an ncp_uint8_t where the retrieved MPLS COS
 *                           value will be placed.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_DSCP_INVALID
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 */
NCP_API ncp_st_t
ncp_eioa_common_dscp_mplscos_get(ncp_hdl_t ncpHdl,
                             ncp_uint8_t dscpValue,
                             ncp_uint8_t *mplsCosValue);

/*!
 *  @brief  Set the shared mac address.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the EIOA is part of.
 *  @param[in]  indx        The index of mac address to be set. Valid values: 0-7.
 *  @param[in]  macAddr     Pointer to an ncp_uint8_t containing six bytes of
 *                          mac address to be set.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_COMMON_SHARED_MAC_ADDR_INVALID_INDEX
 *      \li ::NCP_ST_EIOA_COMMON_SHARED_MAC_ADDR_INVALID_MAC_ADDR
 */
NCP_API ncp_st_t
ncp_eioa_common_shared_mac_address_set(ncp_hdl_t ncpHdl,
                                       ncp_uint8_t indx,
                                       ncp_uint8_t* macAddr);

/*!
 *  @brief  Get the shared mac address.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the EIOA is part of.
 *  @param[in]  indx        The index of mac address to be fetched. Valid values: 0-7.
 *  @param[out] macAddr     Pointer to an ncp_uint8_t buffer where the
 *                          mac address would be filled.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_COMMON_SHARED_MAC_ADDR_INVALID_INDEX
 *      \li ::NCP_ST_EIOA_COMMON_SHARED_MAC_ADDR_INVALID_MAC_ADDR
 */
NCP_API ncp_st_t
ncp_eioa_common_shared_mac_address_get(ncp_hdl_t ncpHdl,
                                       ncp_uint8_t indx,
                                       ncp_uint8_t* macAddr);

/*!
 * @enum ncp_eioa_common_vp_type_t
 * @brief Types of Virtual Pipelines for EIOA. 
 *        This is meant to be all inclusive for all current chipsets.
 */

typedef enum ncp_eioa_common_vflow_type_e
{
    NCP_EIOA_COMMON_VP_L2_FRAMER_ERR = 100,
    /*!< Layer 2 Framer Error VP. */
    NCP_EIOA_COMMON_VP_L3_FRAMER_ERR,
    /*!< Layer 3 Framer Error VP. */
    NCP_EIOA_COMMON_VP_L4_FRAMER_ERR,
    /*!< Layer 4 Framer Error VP. */
    NCP_EIOA_COMMON_VP_ESMC,
    /*!< ESMC VP. Only for AX[EM]25xx */
    NCP_EIOA_COMMON_VP_LEARNING_NOTIFICATION,
    /*!< Learning Notification VP. */
    NCP_EIOA_COMMON_VP_MULTICAST_REPLICATION,
    /*!< Multicast Replication VP. */
    NCP_EIOA_COMMON_VP_OSSP,
    /*!< OSSP VP. Only for AX[EM]55xx */
    NCP_EIOA_COMMON_VP_MACSEC_SECURE,
    /*!< MACSEC Secure VP. Only for AX[EM]55xx */
    NCP_EIOA_COMMON_VP_MACSEC_UNSECURE
    /*!< MACSEC Unsecure VP. Only for AX[EM]55xx */
} ncp_eioa_common_vp_type_t;

/*!
 * @brief Common VFlow data-structures.
 */
typedef struct ncp_eioa_common_vp_s
{
    /*! @brief      The VPM handle for the VP */
    ncp_vp_hdl_t    vpHdl;
    /*! @brief      The taskPriority for this Vflow */
    ncp_uint8_t     taskPriority;
    /*! @brief      Flag to indicate if packets should be discarded 
                    based on CCM discard indication 
                    Only for AX[EM]55xx */
    ncp_bool_t      enableCcmDiscard;
    /*! @brief      Flag to indicate packets using this vflow with 
                    cfi bit set are eligible to be discarded based on the CCM 
                    bp indication
                    Only for AX[EM]55xx */
    ncp_bool_t      enableCcmBpDeiDiscard;
    /*! @brief      Flag to indicate packets using this vflow with 
                    dscp_discard are eligible to be discarded based on the CCM 
                    bp indication.
                    Only for AX[EM]55xx */
    ncp_bool_t      enableCcmBpDscpDiscard;
} ncp_eioa_common_vp_t;

/*!
 *  @brief  Get virtual pipeline info for the vpType requested. Please refer to 
 *          ncp_eioa_common_vp_t for more details on what information is 
 *          returned.
 *
 *  @param[in] ncpHdl           Handle for the NCP that the EIOA is part of.
 *  @param[in] vpType           Type of virtual pipeline type for which the info is
 *                              being requested. Refer to ncp_eioa_common_vp_type_t
 *                              for more details.
 *  @param[out] vpSettings      Pointer to an ncp_eioa_common_vp_t where the 
 *                              virtual pipeline info is provided.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_HANDLE_INVALID
 *      \li ::NCP_ST_API_NOT_SUPPORTED
 *      \li ::NCP_ST_EIOA_COMMON_VP_TYPE_INVALID
 *      \li ::NCP_ST_EIOA_COMMON_VP_NOT_SET
 *      \li ::NCP_ST_VPM_INVALID_LAUNCH_ENGINE
 *      \li ::NCP_ST_VPM_VP_NOT_FOUND
 */

NCP_API ncp_st_t
ncp_eioa_common_vp_get(ncp_hdl_t                     ncpHdl, 
                       ncp_eioa_common_vp_type_t     vpType,
			           ncp_eioa_common_vp_t         *vpSettings);

/*!
 *  @brief  Set the virtual pipeline info for the vpType requested. Please refer 
 *          to ncp_eioa_common_vp_t for more details on what information 
 *          can be set.
 *
 *  @param[in] ncpHdl         Handle for the NCP that the EIOA is part of.
 *  @param[in] vpType         The virtual pipeline type for which the info is 
 *                            being set.
 *  @param[in] vpSettings     Pointer to an ncp_eioa_common_vp_t containing 
 *                            the virtual pipeline info to be set.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_HANDLE_INVALID
 *      \li ::NCP_ST_API_NOT_SUPPORTED
 *      \li ::NCP_ST_EIOA_COMMON_VP_TYPE_INVALID
 *      \li ::NCP_ST_VPM_OUTPUT_FORMAT_INVALID
 *      \li ::NCP_ST_EIOA_COMMON_TASK_PRIORITY_INVALID
 *      \li ::NCP_ST_VPM_INVALID_VP_HDL
 */

NCP_API ncp_st_t
ncp_eioa_common_vp_set(ncp_hdl_t                     ncpHdl, 
                       ncp_eioa_common_vp_type_t     vpType,
			           ncp_eioa_common_vp_t         *vpSettings);

/*!
 *  @brief  Get the handle of the virtual pipeline that is used to report
 *          packets with layer 2 framer errors, Also get the task priority
 *          that is assigned to tasks that are sent to the pipeline.
 *          (Deprecated) see ncp_eioa_common_vp_get
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[out] vpHdl           Pointer to a ncp_vp_hdl_t where the virtual
 *                              pipeline handle will be placed.
 *  @param[out] taskPriority    Pointer to an ncp_uint8_t where the task
 *                              priority will be placed.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_HANDLE_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_common_vps_l2framererror_vp_get(ncp_hdl_t ncpHdl, ncp_vp_hdl_t *vpHdl,
                                         ncp_uint8_t *taskPriority);

/*!
 *  @brief  Set the virtual pipeline and task priority for tasks used to
 *          report packets with layer 2 framer errors.
 *          (Deprecated) see ncp_eioa_common_vp_set
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[in]  vpHdl           The virtual pipeline handle for the VP that
 *                              will be assigned.
 *  @param[in] taskPriority     The task priority that will be assigned.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_COMMON_TASK_PRIORITY_INVALID
 *      \li ::NCP_ST_VPM_LAUNCH_ENGINE_MISMATCH
 *      \li ::NCP_ST_VPM_OUTPUT_FORMAT_INVALID
 */

NCP_API ncp_st_t
ncp_eioa_common_vps_l2framererror_vp_set(ncp_hdl_t ncpHdl, ncp_vp_hdl_t vpHdl,
                                         ncp_uint8_t taskPriority);

/*!
 *  @brief  Get the handle of the virtual pipeline that is used to report
 *          packets with layer 3 framer errors, Also get the task priority
 *          that is assigned to tasks that are sent to the pipeline.
 *          (Deprecated) see ncp_eioa_common_vp_get
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[out] vpHdl           Pointer to a ncp_vp_hdl_t where the virtual
 *                              pipeline handle will be placed.
 *  @param[out] taskPriority    Pointer to an ncp_uint8_t where the task
 *                              priority will be placed.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_HANDLE_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_common_vps_l3framererror_vp_get(ncp_hdl_t ncpHdl, ncp_vp_hdl_t *vpHdl,
                                         ncp_uint8_t *taskPriority);

/*!
 *  @brief  Set the virtual pipeline and task priority for tasks used to
 *          report packets with packets with layer 3 framer errors.
 *          (Deprecated) see ncp_eioa_common_vp_set
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[in]  vpHdl           The virtual pipeline handle for the VP that
 *                              will be assigned.
 *  @param[in] taskPriority     The task priority that will be assigned.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_COMMON_TASK_PRIORITY_INVALID
 *      \li ::NCP_ST_VPM_LAUNCH_ENGINE_MISMATCH
 *      \li ::NCP_ST_VPM_OUTPUT_FORMAT_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_common_vps_l3framererror_vp_set(ncp_hdl_t ncpHdl, ncp_vp_hdl_t vpHdl,
                                         ncp_uint8_t taskPriority);
/*!
 *  @brief  Get the handle of the virtual pipeline that is used to report
 *          packets with layer 4 framer errors, Also get the task priority
 *          that is assigned to tasks that are sent to the pipeline.
 *          (Deprecated) see ncp_eioa_common_vp_get
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[out] vpHdl           Pointer to a ncp_vp_hdl_t where the virtual
 *                              pipeline handle will be placed.
 *  @param[out] taskPriority    Pointer to an ncp_uint8_t where the task
 *                              priority will be placed.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_HANDLE_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_common_vps_l4framererror_vp_get(ncp_hdl_t ncpHdl, ncp_vp_hdl_t *vpHdl,
                                         ncp_uint8_t *taskPriority);

/*!
 *  @brief  Set the virtual pipeline and task priority for tasks used to
 *          report packets with layer 4 framer errors.
 *          (Deprecated) see ncp_eioa_common_vp_set
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[in]  vpHdl           The virtual pipeline handle for the VP that
 *                              will be assigned.
 *  @param[in] taskPriority     The task priority that will be assigned.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_COMMON_TASK_PRIORITY_INVALID
 *      \li ::NCP_ST_VPM_LAUNCH_ENGINE_MISMATCH
 *      \li ::NCP_ST_VPM_OUTPUT_FORMAT_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_common_vps_l4framererror_vp_set(ncp_hdl_t ncpHdl, ncp_vp_hdl_t vpHdl,
                                         ncp_uint8_t taskPriority);

/*!
 *  @brief  Get the handle of the virtual pipeline that is used to send
 *          tasks containing ESMC packets.  Also get the task priority that
 *          is assigned to tasks that are sent to the pipeline.
 *          (Deprecated) see ncp_eioa_common_vp_get
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[out] vpHdl           Pointer to a ncp_vp_hdl_t where the virtual
 *                              pipeline handle will be placed.
 *  @param[out] taskPriority    Pointer to an ncp_uint8_t where the task
 *                              priority will be placed.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_HANDLE_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_common_vps_esmc_vp_get(ncp_hdl_t ncpHdl, ncp_vp_hdl_t *vpHdl,
                                ncp_uint8_t *taskPriority);
/*!
 *  @brief  Set the virtual pipeline and task priority for tasks containing
 *          esmc packets.
 *          (Deprecated) see ncp_eioa_common_vp_set
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[in]  vpHdl           The virtual pipeline handle for the VP that
 *                              will be assigned.
 *  @param[in] taskPriority     The task priority that will be assigned.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_COMMON_TASK_PRIORITY_INVALID
 *      \li ::NCP_ST_VPM_LAUNCH_ENGINE_MISMATCH
 *      \li ::NCP_ST_VPM_OUTPUT_FORMAT_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_common_vps_esmc_vp_set(ncp_hdl_t ncpHdl, ncp_vp_hdl_t vpHdl,
                                ncp_uint8_t taskPriority);

/*!
 *  @brief  Get the handle of the virtual pipeline that is used to send
 *          learning notification tasks. Also get the task priority that
 *          is assigned to tasks that are sent to the pipeline.
 *          (Deprecated) see ncp_eioa_common_vp_get
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[out] vpHdl           Pointer to a ncp_vp_hdl_t where the virtual
 *                              pipeline handle will be placed.
 *  @param[out] taskPriority    Pointer to an ncp_uint8_t where the task
 *                              priority will be placed.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_COMMON_VP_NOT_SET
 */
NCP_API ncp_st_t
ncp_eioa_common_vps_learningnotification_vp_get(ncp_hdl_t ncpHdl,
                                                ncp_vp_hdl_t *vpHdl,
                                                ncp_uint8_t *taskPriority);
/*!
 *  @brief  Set the virtual pipeline and task priority for learning
 *          notification tasks used to.
 *          (Deprecated) see ncp_eioa_common_vp_set
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[in]  vpHdl           The virtual pipeline handle for the VP that
 *                              will be assigned.
 *  @param[in] taskPriority     The task priority that will be assigned.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_COMMON_TASK_PRIORITY_INVALID
 *      \li ::NCP_ST_EIOA_BRIDGE_LEARNING_NOTIFICATION_DISABLED
 *      \li ::NCP_ST_VPM_LAUNCH_ENGINE_MISMATCH
 *      \li ::NCP_ST_VPM_OUTPUT_FORMAT_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_common_vps_learningnotification_vp_set(ncp_hdl_t ncpHdl,
                                                ncp_vp_hdl_t vpHdl,
                                                ncp_uint8_t taskPriority);

/*!
 *  @brief  Get the task priority for tasks sent to the multicast replication
 *          virtual pipeline.
 *          (Deprecated) see ncp_eioa_common_vp_get
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[out] taskPriority    Pointer to an ncp_uint8_t where the task
 *                              priority will be placed.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_HANDLE_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_common_vps_multicastreplication_vp_get_pri(ncp_hdl_t ncpHdl,
                                                    ncp_uint8_t *taskPriority);

/*!
 *  @brief  Set the task priority for tasks sent to the multicast replication
 *          virtual pipeline.
 *          (Deprecated) see ncp_eioa_common_vp_set
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[in] taskPriority     The task priority that will be assigned.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_COMMON_TASK_PRIORITY_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_common_vps_multicastreplication_vp_set_pri(ncp_hdl_t ncpHdl,
                                                    ncp_uint8_t taskPriority);

/*!
 * @brief Bridging VP settings
 */
typedef struct ncp_eioa_common_bridging_vp_e
{
    /*! @brief      The VPM handle for the VP */
    ncp_vp_hdl_t    vpHdl;
    /*! @brief      Entries contan the input COS value to task priority
     *              mapping.  The array index corresponds to the COS
     *              value.  The array value is the task priority */
    ncp_uint8_t     cosToTaskPriority[8];
    /*! @brief      Flag to indicate if normal forwarding of ethernet traffic
     *              is enabled or not. */
    ncp_bool_t      enableNormalEthernetTraffic;
    /*! @brief      Flag to indicate if mirroring is enabled.  If true traffic
     *              on the vp is copied to the mirroring port. */
    ncp_bool_t      enableDestMirroring;
    /*! @brief      Flag to indicate if packets should be discarded 
     *              based on CCM discard indication 
     *              Only for AX[EM]55xx */
    ncp_bool_t      enableCcmDiscard;
    /*! @brief      Flag to indicate packets using this vflow with 
     *              cfi bit set are eligible to be discarded based on the CCM 
     *              bp indication
     *              Only for AX[EM]55xx */
    ncp_bool_t      enableCcmBpDeiDiscard;
    /*! @brief      Flag to indicate packets using this vflow with 
     *              dscp_discard are eligible to be discarded based on the CCM 
     *              bp indication.
     *              Only for AX[EM]55xx */
    ncp_bool_t      enableCcmBpDscpDiscard;
} ncp_eioa_common_bridging_vp_t;


/*!
 *  @brief  Get the VP settings for a bridging virtual pipeline entry.
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[in]  bridgingVpId    The ID of the bridging VP to retrieve.
 *  @param[out] bridgingVp      Pointer to an ncp_eioa_common_bridging_vp_t
 *                              structure that will be populated with the
 *                              values corresponding to bridgingVpId.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_COMMON_BRIDGING_VP_ID_INVALID
 *      \li ::NCP_ST_EIOA_COMMON_VP_NOT_SET
 */
NCP_API ncp_st_t
ncp_eioa_common_vps_bridging_vp_get(ncp_hdl_t ncpHdl,
                                    ncp_uint8_t bridgingVpId,
                                    ncp_eioa_common_bridging_vp_t *bridgingVp);


/*!
 *  @brief  Set a VP corresponding to the bridgingVpId.  For the port
 *          bridging  VPs (IDs 0 to 9), the VP cannot be modified, but
 *          the CoS priority mapping, dest mirroring and normal traffic
 *          attributes can be changed.  In these cases, the vpHdl field
 *          in the bridgingVp structure is ignored.
 *
 *  @param[in] ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[in] bridgingVpId    The ID of the bridging VP to query.
 *  @param[in] bridgingVp      Pointer to an ncp_eioa_common_bridging_vp_t
 *                             structure containing the VP information that
 *                             will be used to set the bridging VP.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_COMMON_BRIDGING_VP_ID_INVALID
 *      \li ::NCP_ST_EIOA_COMMON_TASK_PRIORITY_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_common_vps_bridging_vp_set(ncp_hdl_t ncpHdl,
                                    ncp_uint8_t bridgingVpId,
                                    ncp_eioa_common_bridging_vp_t *bridgingVp);

/*!
 * @brief Virtual Pipeline Extension data structure.
 */
typedef struct ncp_eioa_vpe_s
{
    /*! @brief      Enable VPE for this EIOA. */
    ncp_bool_t      enableVpe;
    
    /*! @brief      The taskPriority to use for VPE taskks. Values: 0 - 7 */
    ncp_uint8_t     taskPriority;
    
    /*! @brief      Use Congestion Control for VPE tasks. */
    ncp_bool_t      useCCM;
    
    /*! @brief      Ethertype for VPE packets. */
    ncp_uint16_t    etherType;
    
    /*! @brief      Ethertype for errored VPE packets. */
    ncp_uint16_t    errorEtherType;
} ncp_eioa_vpe_t;

/*!
 *  @brief  Configure Virtual Pipeline Extension(VPE) for the EIOA.
 *
 *  @param[in] ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[in] eioa            The EIOA for which this needs to be configured.
 *  @param[in] vpe             Pointer to an ncp_eioa_vpe_t structure containing 
 *                             the VPE information that needs to be configured.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_INVALID_EIOA
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 */
NCP_API ncp_st_t
ncp_eioa_vpe_set(ncp_hdl_t ncpHdl, ncp_eioa_num_t eioa, ncp_eioa_vpe_t *vpe);


/*!
 *  @brief  Read Virtual Pipeline Extension(VPE) for the EIOA.
 *
 *  @param[in] ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[in] eioa            The EIOA for which this needs to be read.
 *  @param[in] vpe             Pointer to an ncp_eioa_vpe_t structure where 
 *                             the VPE information is written to.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_INVALID_EIOA
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 */
NCP_API ncp_st_t
ncp_eioa_vpe_get(ncp_hdl_t ncpHdl, ncp_eioa_num_t eioa, ncp_eioa_vpe_t *vpe);


/*!
 *  @brief  Configure Non-EIOA Multicast Bitmap Memory Table row.
 *  This API is supported in ACP55xx version of the chip only.
 *
 *  @param[in] ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[in] destIndex       Destination index with in the table. 
 *                             Each index representing one group. Index Value: 0 - 255.
 *  @param[in] VpBitMap        The bitmap representing the bridging virtual piplines IDs 
 *                             within the multicast group. bitMap: 38 lsb bits;
 *                             All pipelines must have the same input format. 
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_API_NOT_SUPPORTED
 *      \li ::NCP_ST_VPM_VP_NOT_FOUND
 *      \li ::NCP_ST_VPM_INPUT_FORMAT_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_common_non_eioa_multicast_destination_map_set(ncp_hdl_t ncpHdl,
                                                      ncp_uint8_t destIndex,
                                                      ncp_uint64_t vpBitMap);

/*!
 *  @brief  Read Non-EIOA Multicast Bitmap Memory Table row.
 *  This API is supported in ACP55xx version of the chip only.
 *
 *  @param[in] ncpHdl          Handle for the NCP that the EIOA is part of.
 *  @param[in] destIndex       Destination index with in the table. 
 *                             Each index representing one group. Index Value: 0 - 255.
 *  @param[out] VpBitMap       The bitmap representing the bridging virtual piplines IDs 
 *                             within the multicast group. bitMap: 38 lsb bits; 
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_API_NOT_SUPPORTED
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 */
NCP_API ncp_st_t
ncp_eioa_common_non_eioa_multicast_destination_map_get(ncp_hdl_t ncpHdl,
                                                      ncp_uint8_t destIndex,
                                                      ncp_uint64_t *vpBitMap);

/*!
 *  @brief  Set Router Next Hop destination Mac Address for a given id.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the EIOA is part of.
 *  @param[in]  id	    The id for which the router dest mac address is to be setup.valid:0-255
 *  @param[in]  macAddr	    The buffer containing the mac address.
 *			    eg.,AA:BB:CC:DD:EE:FF -> macAddr[0]=AA,macAddr[1]=BB
 *					macAddr[2]=CC, macAddr[3]=DD
 *					macAddr[4]=EE, macAddr[5]=FF
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 */

NCP_API ncp_st_t
ncp_eioa_common_router_next_hop_macaddr_set(ncp_hdl_t ncpHdl,
                             ncp_uint8_t	id,
                             ncp_uint8_t *macAddr);

/*!
 *  @brief  Get Router Next Hop Destination Mac Address for a given id.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the EIOA is part of.
 *  @param[in]  id	    The id for which the router destination mac address is queried 
 *				valid: 0-255
 *  @param[out]  macAddr    The buffer where the mac address is returned.
 *			    eg.,AA:BB:CC:DD:EE:FF -> macAddr[0]=AA,macAddr[1]=BB
 *					macAddr[2]=CC, macAddr[3]=DD
 *					macAddr[4]=EE, macAddr[5]=FF
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_INVALID_BUFFER
 */

NCP_API ncp_st_t
ncp_eioa_common_router_next_hop_macaddr_get(ncp_hdl_t ncpHdl,
                             ncp_uint8_t	id,
                             ncp_uint8_t *macAddr);


#ifdef __cplusplus
}
#endif

#endif /* #ifndef _NCP_EIOA_COMMON_H_ */

/*
 *  @}
 */

