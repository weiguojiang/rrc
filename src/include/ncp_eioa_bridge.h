/***************************************************************************
 **                                                                        *
 **                           Intel CONFIDENTIAL           *
 **                                                                        *
 **                       PROPRIETARY NOTE                                 *
 **                                                                        *
 **    This software contains information confidential and proprietary     *
 **    to Intel Corporation.  It shall not be reproduced in whole or in  *
 **    part, or transferred to other documents, or disclosed to third      *
 **    parties, or used for any purpose other than that for which it was   *
 **    obtained, without the prior written consent of Intel Corporation. *
 **    (c) 2008-2014, Intel Corporation.  All rights reserved.           *
 **                                                                        *
 **
 ** **************************************************************************/

/*! @file     ncp_eioa_bridge.h                                        */

/*! 
 * @defgroup _eioa_switch_bridge    Eioa Switch Bridging block
 * @ingroup  _eioa_switch_
 *
 * @brief    Eioa Switch Bridging APIs.
 * @details  Eioa Switch Bridging defines, structures and APIs. 
 *****************************************************************************/

#ifndef _NCP_EIOA_SWITCH_BRIDGE_H_
#define _NCP_EIOA_SWITCH_BRIDGE_H_

#include "ncp.h"

#ifdef __cplusplus
extern "C" {
#endif


/*!
 * @ingroup _eioa_switch_bridge
 * @brief Port specific attributes related to switching.
 * @see
 */
typedef struct {
    /*! @brief          Valid for 25xx only */
    ncp_bool_t          enableIgmpSnoop;
    /*! @brief          Valid for 25xx only */
    ncp_bool_t          enableDoubleVlanIgmpSnoop;
    ncp_bool_t          enableDoubleVlanRouting;        /* New for both */
    ncp_bool_t          enableUserPortSnoop;
    ncp_bool_t          enableDoubleVlanUserPortSnoop;
    ncp_bool_t          enableSupervisorRoute;
    ncp_bool_t          discardUnknownSource;
    ncp_bool_t          enableMacVlan;
    ncp_bool_t          keepVlanTag;
    ncp_bool_t          enableRouting;
    ncp_bool_t          authorizePacketReceive;
    ncp_bool_t          disregardVlanSource;
    /*! @deprecated */
    ncp_bool_t          enableMacPriority;
    /*! @brief          Valid for 25xx only */
    ncp_bool_t          enableOamPort;
    ncp_bool_t          enableProtectedPort;
    ncp_bool_t          enableMirroring;
    ncp_bool_t          enableFlooding;
    /*! @brief          The maximumAgeInUnits is 0x3f (6-bit field) for 55xx and 0x3ff (10-bit field) for 56xx and beyond */
    ncp_uint32_t        maximumAgeInUnits;
} ncp_eioa_switch_bridge_port_attrs_t;

/*!
 * @ingroup _eioa_switch_bridge
 * @struct ncp_eioa_switch_bridge_port_learn_attrs_t
 * @brief Learning attributes for a port. These attributes affect dynamic learning for packets received on a port
 * @deprecated \ref ncp_eioa_switch_bridge_port_learn_attrs_t::ageInUnits "ageInUnits" does not have enough storage for the maximum age for AXX5600 and beyond. Use
 * \ref ncp_eioa_switch_bridge_port_learn_attrs_t2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_bridge_port_learn_attrs_t2
 */
typedef struct
{
    ncp_bool_t          useMacPriority;
    ncp_uint8_t         macPriority;
    ncp_bool_t          useMacVlan;
    ncp_bool_t          destLog;
    ncp_bool_t          sourceLog;
    ncp_bool_t          sourcePermit;
    ncp_bool_t          portSourceDenyOverride;
    ncp_bool_t          globalSourceDenyOverride;
    ncp_bool_t          globalDestDenyOverride;
    ncp_uint8_t         ageInUnits;
} ncp_eioa_switch_bridge_port_learn_attrs_t;

/*!
 * @ingroup _eioa_switch_bridge
 * @struct ncp_eioa_switch_bridge_port_learn_attrs_t2
 * @brief Learning attributes for a port. These attributes affect dynamic learning for packets received on a port
 * @since 1.3.0
 */
typedef struct
{
    ncp_bool_t          useMacPriority;
    ncp_uint8_t         macPriority;
    ncp_bool_t          useMacVlan;
    ncp_bool_t          destLog;
    ncp_bool_t          sourceLog;
    ncp_bool_t          sourcePermit;
    ncp_bool_t          portSourceDenyOverride;
    ncp_bool_t          globalSourceDenyOverride;
    ncp_bool_t          globalDestDenyOverride;
    /*! @brief          The ageInUnits cannot exceed 0x3f (6-bit field) for 55xx and 0x3ff (10-bit field) for 56xx and beyond */
    ncp_uint16_t        ageInUnits;
} ncp_eioa_switch_bridge_port_learn_attrs_t2;

/*!
 * @ingroup _eioa_switch_bridge
 * @brief Spanning tree states
 * @see
 */
/* This enum needs to match HW definied values @ 0x24.1.0x90000 */
typedef enum ncp_eioa_stp_state_e {
    NCP_EIOA_STP_STATE_BLOCKING,
    NCP_EIOA_STP_STATE_LEARNING,
    NCP_EIOA_STP_STATE_FORWARDING,
    NCP_EIOA_STP_STATE_DISABLED
} ncp_eioa_stp_state_t;

/*!
 * @ingroup _eioa_switch_bridge
 * @brief Key types when learning/unlearning entries in the switching table
 * @see
 */
typedef enum 
{
    NCP_EIOA_SWITCH_KEY_IVL = 0,
    NCP_EIOA_SWITCH_KEY_SVL,
    NCP_EIOA_SWITCH_KEY_DOUBLE_TAG,
    NCP_EIOA_SWITCH_KEY_SINGLE_TAG,
    NCP_EIOA_SWITCH_KEY_MPLS,
    NCP_EIOA_SWITCH_KEY_MAX = NCP_EIOA_SWITCH_KEY_MPLS
} ncp_eioa_switch_key_type_t;

/*!
 * @ingroup _eioa_switch_bridge
 * @struct ncp_eioa_switch_key_t
 * @brief Definition of a bridge entry key. Used to identify entries in the switching table
 * @deprecated \ref ncp_eioa_switch_key_t::mplsLabel "mplsLabel" does not provide enough storage for a 20b MPLS label. Use \ref ncp_eioa_switch_key_t2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_key_t2
 */
typedef struct
{
    ncp_eioa_switch_key_type_t          type;
    ncp_uint16_t                        vlanId;
    ncp_uint8_t                         macAddress[6];
    ncp_uint16_t                        cvlanId;
    ncp_uint16_t                        mplsLabel;
} ncp_eioa_switch_key_t;

/*!
 * @ingroup _eioa_switch_bridge
 * @struct ncp_eioa_switch_key_t2
 * @brief Definition of a bridge entry key. Used to identify entries in the switching table
 * @since 1.3.0
 */
typedef struct
{
	ncp_eioa_switch_key_type_t          type;
	ncp_uint16_t                        vlanId;
	ncp_uint8_t                         macAddress[6];
	ncp_uint16_t                        cvlanId;
	ncp_uint32_t                        mplsLabel;
    /*! @brief                          The domainId is ignored for 55xx. Virtual domains are only supported in 56xx and beyond */
    ncp_uint16_t                        domainId;
} ncp_eioa_switch_key_t2;

/*!
 * @ingroup _eioa_switch_bridge
 * @brief MPLS options to be applied at egress
 * @see
 */
typedef enum {
    NCP_EIOA_MPLS_OPTIONS_NOOP = 0,
    NCP_EIOA_MPLS_OPTIONS_ADD = 1,
    NCP_EIOA_MPLS_OPTIONS_REMOVE = 2,
    NCP_EIOA_MPLS_OPTIONS_MODIFY = 3
} ncp_eioa_mpls_options_t;

/*!
 * @ingroup _eioa_switch_bridge
 * @struct ncp_eioa_switch_bridge_entry_t
 * @brief Definition of an entry. Used to learn/unlearn entries in the switching table
 * @deprecated Does not have MPLS features of AXX5600 and beyond. Uses deprecated \ref ncp_eioa_switch_bridge_port_learn_attrs_t as the attributes. Uses
 * deprecated \ref ncp_eioa_switch_key_t as the key. Use \ref ncp_eioa_switch_bridge_entry_t2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_bridge_entry_t2
 */
typedef struct
{
    ncp_eioa_switch_key_t               key;
    ncp_uint8_t                         sourceLogicalPort;
    ncp_eioa_switch_bridge_port_learn_attrs_t attrs;
    ncp_uint16_t                        macVlan;
    ncp_uint8_t                         destinationIdx;
} ncp_eioa_switch_bridge_entry_t;


/*!
 * @ingroup _eioa_switch_bridge
 * @struct ncp_eioa_switch_bridge_entry_t2
 * @brief Definition of an entry. Used to learn/unlearn entries in the switching table
 */
typedef struct
{
    ncp_eioa_switch_key_t2        key;
    ncp_uint8_t                         sourceLogicalPort;
    ncp_eioa_switch_bridge_port_learn_attrs_t2 attrs;
    ncp_uint16_t                        macVlan;
    ncp_uint8_t                         destinationIdx;
    /*! @brief                          The mplsIdx is an index into the egress table and is ignored for 55xx. Advanced mpls features
     *                                  are supported only for 56xx and beyond */
    ncp_uint8_t                         mplsIdx;
    /*! @brief                          The mplsTtlIncrement is ignored for 55xx. Advanced mpls features
     *                                  are supported only for 56xx and beyond */
    ncp_bool_t                          mplsTtlDecrement;
    /*! @brief                          The mplsOptions is ignored for 55xx. Advanced mpls features
     *                                  are supported only for 56xx and beyond */
    ncp_eioa_mpls_options_t             mplsOptions;
} ncp_eioa_switch_bridge_entry_t2;

/*!
 * @ingroup _eioa_switch_bridge
 * @struct ncp_eioa_switch_bridge_vp_name_t
 * @brief Destination VP name declaration
 * @see ncp_eioa_switch_bridge_destination_vps_name_to_id_get
 * @see ncp_eioa_switch_bridge_destination_vps_id_to_name_get
 * @see ncp_eioa_switch_bridge_destination_vps_id_to_name_set
 */
typedef struct
{
	char                                name[64];
} ncp_eioa_switch_bridge_vp_name_t;

/*!
 * @ingroup _eioa_switch_bridge
 * @typedef ncp_eioa_switch_bridge_entry_list_cb_fn_t
 * @brief Callback function declaration
 * @deprecated Uses deprecated \ref ncp_eioa_switch_bridge_entry_t. Use \ref ncp_eioa_switch_bridge_entry_list_cb_fn_t2 instead
 * @since 1.3.0
 * @see   ncp_eioa_switch_bridge_entry_list_cb_fn_t2
 * @see   ncp_eioa_switch_brigde_entry_list
 */
#ifndef SWIG
typedef int (*ncp_eioa_switch_bridge_entry_list_cb_fn_t)(void *rock, 
                                                         ncp_uint32_t idx,
                                                         ncp_eioa_switch_bridge_entry_t* entry);
#endif /* #ifndef SWIG */


/*!
 * @ingroup _eioa_switch_bridge
 * @typedef ncp_eioa_switch_bridge_entry_list_cb_fn_t2
 * @brief Callback function declaration
 * @see   ncp_eioa_switch_bridge_item_list
 */
#ifndef SWIG
typedef int (*ncp_eioa_switch_bridge_entry_list_cb_fn_t2)(void *rock,
                                                         ncp_uint32_t idx,
                                                         ncp_eioa_switch_bridge_entry_t2* entry);
#endif /* #ifndef SWIG */

/*!
 * @ingroup _eioa_switch_bridge
 * @brief The destinations in the bridging tables are made up of one or mode destination vps in the bridging vps
 *        table. These vps are identified by the specific bit number which can range from
 *        0 - 23 for the 25xx chip and 0 - 37 for 55xx. This data type
 *        is used to identify a set of vps as a bitmap containing their bit positions.
 *        For example, the vps at bit position 1 and 10 are identified as 0x000402
 *        The bridging algorithm starts off with a bitmap (destination map) and then adds or removes various vps
 *        in a set of mapping and masking steps. The specific vps for these steps can be managed through the APIs.
 *        The APIs identify vps to be added as addVps or addVp and vps to be removed as remVps or remVp.
 * @see   ncp_eioa_switch_bridge_destination_vps_set
 * @see   ncp_eioa_switch_bridge_destination_vps_get
 */
typedef ncp_int64_t    ncp_eioa_vps_bitmap_t;

/*!
 * @ingroup _eioa_switch_bridge
 * @brief The destinations in the bridging tables are made up of one or mode destination vps in the bridging vps
 *        table. These vps are identified by the specific bit number which can range from
 *        0 - 23 for the 25xx chip and 0 - 37 for 55xx. This data type
 *        is used to identify a single vp by its bit position
 *        For example, the vp at bit position 10 is identified by 10
 *        The bridging algorithm starts off with a bitmap (destination map) and then adds or removes various vps
 *        in a set of mapping and masking steps. The specific vps for these steps can be managed through the APIs.
 *        The APIs identify vps to be added as addVps or addVp and vps to be removed as remVps or remVp.
 * @see ncp_eioa_switch_bridge_learning_vps_set
 * @see ncp_eioa_switch_bridge_learning_vps_get
 */
typedef ncp_int32_t    ncp_eioa_vp_bit_t;

/*!
 * @ingroup _eioa_switch_bridge
 * \def NCP_EIOA_BRIDGING_VP_BIT_UNSET
 * @brief The NCP_EIOA_BRIDGING_VP_BIT_UNSET is used to denote a vp which is not set. Used when a single vp bit
 *        is worked on by the APIs
 * @see ncp_eioa_switch_bridge_learning_vps_set
 * @see ncp_eioa_switch_bridge_learning_vps_get
 */
#define NCP_EIOA_BRIDGING_VP_BIT_UNSET     -1

/*!
 * @ingroup _eioa_switch_bridge
 * @def NCP_EIOA_BRIDGING_DESTINATION_MAP_NAME
 * @brief The destination table is registered as a resource with the ncp resource manager. This is a table with
 *        256 ids to manage. Any ids in configuration are allocated at config startup. Application can use the
 *        resource manager to manage this id space and the bridging APIs to program the destination table
 *        The resource manager type is NCP_RSRC_EIOA and the name is NCP_EIOA_BRIDGING_DESTINATION_MAP_NAME
 * @see   ncp_eioa_switch_bridge_destination_vps_set
 * @see   ncp_eioa_switch_bridge_destination_vps_get
 */
#define NCP_EIOA_BRIDGING_DESTINATION_MAP_NAME          "DestinationMap"

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set bridging related attributes for a given port
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] port   The eioa port
 * @param[in] attrs  Port attributes
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_port_attrs_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_port_attrs_set(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
                                      ncp_eioa_switch_bridge_port_attrs_t* attrs);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to retrieve bridging related attributes for a given port
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] port   The eioa port
 * @param[out] attrs Port attributes
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_port_attrs_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_port_attrs_get(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
                                      ncp_eioa_switch_bridge_port_attrs_t* attrs);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set dynamic learning related attributes for a given port. These attribute are used
 *        to learn the source address.
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] port   The eioa port
 * @param[in] enableLearning Flag to enable dynamic learning
 * @param[in] attrs  Port learning attributes
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @deprecated Uses deprecated \ref ncp_eioa_switch_bridge_port_learn_attrs_t. Use \ref ncp_eioa_switch_bridge_port_learn_attrs_set2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_bridge_port_learn_attrs_set2
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_port_learn_attrs_set(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
                                            ncp_bool_t enableLearning, ncp_eioa_switch_bridge_port_learn_attrs_t* attrs);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to retrieve dynamic learning related attributes for a given port
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] port   The eioa port
 * @param[out] enableLearning Flag to enable dynamic learning
 * @param[out] attrs  Port learning attributes
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @deprecated Uses deprecated \ref ncp_eioa_switch_bridge_port_learn_attrs_t. Use \ref ncp_eioa_switch_bridge_port_learn_attrs_get2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_bridge_port_learn_attrs_get2
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_port_learn_attrs_get(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
                                            ncp_bool_t* enableLearning, ncp_eioa_switch_bridge_port_learn_attrs_t* attrs);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set dynamic learning related attributes for a given port. These attribute are used
 *        to learn the source address.
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] port   The eioa port
 * @param[in] enableLearning Flag to enable dynamic learning
 * @param[in] attrs  Port learning attributes
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_port_learn_attrs_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_port_learn_attrs_set2(ncp_hdl_t ncpHdl, ncp_macChan_t port,
                                            ncp_bool_t enableLearning, ncp_eioa_switch_bridge_port_learn_attrs_t2* result);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to retrieve dynamic learning related attributes for a given port
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] port   The eioa port
 * @param[out] enableLearning Flag to enable dynamic learning
 * @param[out] attrs  Port learning attributes
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_port_learn_attrs_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_port_learn_attrs_get2(ncp_hdl_t ncpHdl, ncp_macChan_t port,
                                            ncp_bool_t* enableLearning, ncp_eioa_switch_bridge_port_learn_attrs_t2* result);


/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to learn an entry in the bridging tables.
 * @details The entry is
 *        identified by the key type and all related attributes for the key. 
 *        This entry will be learnt with a starting age identified by ageInUnits. 
 *        If mac address being used is or planned to be shared, the entry->key.vlanId 
 *        needs to be set to zero. Otherwise, the look up will fail.
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] entry  The key and associated attributes to learn the entry
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_SWITCH_HANDLE_INVALID When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDGE_INVALID_KEY_TYPE When key type doesnt match with what is configured or is invalid.
 * @retval NCP_ST_EIOA_BRIDGE_SUPERVISOR_LEARN_TIMEOUT When the entry learn timesout.
 * @retval NCP_ST_EIOA_BRIDGE_SUPERVISOR_LEARN_FAILED When entry learn failed.
 * @deprecated Uses deprecated \ref ncp_eioa_switch_bridge_entry_t. Use \ref ncp_eioa_switch_bridge_entry_learn2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_bridge_entry_learn2
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_entry_learn(ncp_hdl_t ncpHdl, ncp_eioa_switch_bridge_entry_t* entry);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to learn an entry in the bridging tables.
 * @details The entry is
 *        identified by the key type and all related attributes for the key.
 *        This entry will be learnt with a starting age identified by ageInUnits.
 *        If mac address being used is or planned to be shared, the entry->key.vlanId
 *        needs to be set to zero. Otherwise, the look up will fail.
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] entry  The key and associated attributes to learn the entry
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_SWITCH_HANDLE_INVALID When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDGE_INVALID_KEY_TYPE When key type doesnt match with what is configured or is invalid.
 * @retval NCP_ST_EIOA_BRIDGE_SUPERVISOR_LEARN_TIMEOUT When the entry learn timesout.
 * @retval NCP_ST_EIOA_BRIDGE_SUPERVISOR_LEARN_FAILED When entry learn failed.
 * @see ncp_eioa_switch_bridge_item_unlearn2
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_entry_learn2(ncp_hdl_t ncpHdl, ncp_eioa_switch_bridge_entry_t2* entry);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to remove an entry in the bridging tables.
 * @details The entry is identified by the key type and
 *        the various fields. This entry will be marked as deleted and not match and lookups.
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] key  The key to unlearn
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_SWITCH_HANDLE_INVALID When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDGE_INVALID_KEY_TYPE When key type doesnt match with what is configured or is invalid.
 * @retval NCP_ST_EIOA_BRIDGE_SUPERVISOR_UNLEARN_TIMEOUT When the entry unlearn timesout.
 * @retval NCP_ST_EIOA_BRIDGE_SUPERVISOR_UNLEARN_FAILED When entry unlearn failed.
 * @deprecated Uses deprecated \ref ncp_eioa_switch_key_t. Use \ref ncp_eioa_switch_bridge_entry_unlearn2 instead
 * @since 1.3.0
 * @see ncp_eioa_switch_bridge_entry_unlearn2
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_entry_unlearn(ncp_hdl_t ncpHdl, ncp_eioa_switch_key_t* key);


/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to remove an entry in the bridging tables.
 * @details The entry is identified by the key type and
 *        the various fields. This entry will be marked as deleted and not match and lookups.
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] key  The key to unlearn
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_SWITCH_HANDLE_INVALID When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDGE_INVALID_KEY_TYPE When key type doesnt match with what is configured or is invalid.
 * @retval NCP_ST_EIOA_BRIDGE_SUPERVISOR_UNLEARN_TIMEOUT When the entry unlearn timesout.
 * @retval NCP_ST_EIOA_BRIDGE_SUPERVISOR_UNLEARN_FAILED When entry unlearn failed.
 * @see ncp_eioa_switch_bridge_entry_learn2
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_entry_unlearn2(ncp_hdl_t ncpHdl, ncp_eioa_switch_key_t2* key);


/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the logical port id for a given port. The logical port denotes an aggregation
 *        of multiple ports as a logical link. Bridging entries are learnt by the logical port id to reduce 
 *        thrashing.
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] port  The eioa port
 * @param[in] lportId The logical port id
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDGE_INVALID_LOGICAL_PORT_ID When lportIdis invalid.
 * @see ncp_eioa_switch_bridge_port_lport_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_port_lport_set(ncp_hdl_t ncpHdl, ncp_macChan_t port, ncp_uint8_t lportId);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to retrieve the logical port id for a given port.
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] port  The eioa port
 * @param[out] lportId The logical port id
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_port_lport_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_port_lport_get(ncp_hdl_t ncpHdl, ncp_macChan_t port, ncp_uint8_t* lportId);



/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the destination vps at the given index in the destination map table
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] idx    Index into the destination map table
 * @param[in] addVpsBitMap Bitmap of the vps which will be added during bridging
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_COMMON_BRIDGING_VP_ID_INVALID When a vp id is not valid
 * @retval NCP_ST_EIOA_COMMON_VP_NOT_SET When a vp id is not configured
 * @see ncp_eioa_switch_bridge_destination_vps_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_destination_vps_set(ncp_hdl_t ncpHdl, ncp_uint8_t idx, ncp_eioa_vps_bitmap_t addVpsBitMap);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to retrieve the destination vps at an index in the destination map table
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] idx    Index into the destination map table
 * @param[out] addVpsBitMap Bitmap of the vps which will be added during bridging
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_destination_vps_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_destination_vps_get(ncp_hdl_t ncpHdl, ncp_uint8_t idx, ncp_eioa_vps_bitmap_t* addVpsBitMap);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to retrieve the destination vp index for a given vp name
 * @param[in] ncpHdl NCP API state handle
 * @param[in] name Virtual pipeline name for which the id is to be retrieved
 * @param[out] idx Destination vp index mapped to this name
 * @return
 * <ul>
 * <li> #NCP_ST_EIOA_SWITCH_BRIDGE_INVALID_HANDLE - When ncpHdl is invalid
 * <li> #NCP_ST_EIOA_SWITCH_BRIDGE_DESTINATION_VP_INVALID_NAME - When no vp exists with the given name
 * <li> #NCP_ST_INVALID_PARAMETER - When idx is NULL
 * <li> #NCP_ST_API_NOT_SUPPORTED - When this API is not supported for the chip
 * </ul>
 * @see ncp_eioa_switch_bridge_destination_vps_id_to_name_get
 * @see ncp_eioa_switch_bridge_destination_vps_id_to_name_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_destination_vps_name_to_id_get(ncp_hdl_t ncpHdl, ncp_eioa_switch_bridge_vp_name_t name, ncp_uint8_t *idx);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to retrieve the destination vp name for a given destination vp index
 * @param[in] ncpHdl NCP API state handle
 * @param[in] idx Destination vp index for which the name is to be retrieved
 * @param[out] name Destination vp name mapped to this idx
 * @return
 * <ul>
 * <li> #NCP_ST_EIOA_SWITCH_BRIDGE_INVALID_HANDLE - When ncpHdl is invalid
 * <li> #NCP_ST_INVALID_PARAMETER - When name is NULL
 * <li> #NCP_ST_API_NOT_SUPPORTED - When this API is not supported for the chip
 * </ul>
 * @see ncp_eioa_switch_bridge_destination_vps_name_to_id_get
 * @see ncp_eioa_switch_bridge_destination_vps_id_to_name_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_destination_vps_id_to_name_get(ncp_hdl_t ncpHdl, ncp_uint8_t idx, ncp_eioa_switch_bridge_vp_name_t *name);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the destination vp name for a given destination vp index
 * @details Each destination vp index should be mapped to a unique name. Names are
 * case-insensitive. 
 * @param[in] ncpHdl NCP API state handle
 * @param[in] idx Destination vp index for which the name is to be set
 * @param[in] name Destination vp name to map to this idx
 * @return
 * <ul>
 * <li> #NCP_ST_EIOA_SWITCH_BRIDGE_INVALID_HANDLE - When ncpHdl is invalid
 * <li> #NCP_ST_EIOA_BRIDGE_DESTINATION_VP_DUPLICATE_NAME - When the name given is already mapped to another destination vp index
 * <li> #NCP_ST_API_NOT_SUPPORTED - When this API is not supported for the chip
 * </ul>
 * @see ncp_eioa_switch_bridge_destination_vps_name_to_id_get
 * @see ncp_eioa_switch_bridge_destination_vps_id_to_name_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_destination_vps_id_to_name_set(ncp_hdl_t ncpHdl, ncp_uint8_t idx, ncp_eioa_switch_bridge_vp_name_t name);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the destinationIdx for a port which is used for unknown multicast packets
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] port   The eioa port
 * @param[in] idx    Index into the destination map table
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_unknown_multicast_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_unknown_multicast_set(ncp_hdl_t ncpHdl, ncp_macChan_t port, ncp_uint8_t destinationIdx);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to retrieve the destinationIdx for a port from unknown multicast packets
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] port   The eioa port
 * @param[out] idx    Index into the destination map table
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_unknown_multicast_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_unknown_multicast_get(ncp_hdl_t ncpHdl, ncp_macChan_t port, ncp_uint8_t* destinationIdx);


/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the spanning tree id for a vlan
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] vlanId Vlan id
 * @param[in] stpIdx Spanning tree id
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_INVALID_VLAN_ID When vlanId is invalid.
 * @see ncp_eioa_switch_bridge_vlan_stp_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_vlan_stp_set(ncp_hdl_t ncpHdl, ncp_uint16_t vlanId, ncp_uint8_t stpIdx);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the spanning tree id for a vlan
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] vlanId Vlan id
 * @param[out] stpIdx Spanning tree id
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_INVALID_VLAN_ID When vlanId is invalid.
 * @see ncp_eioa_switch_bridge_vlan_stp_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_vlan_stp_get(ncp_hdl_t ncpHdl, ncp_uint16_t vlanId, ncp_uint8_t* stpIdx);


/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the spanning tree state for a port
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] port   The eioa port
 * @param[in] state  Spanning tree state
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_port_stp_state_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_port_stp_state_set(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
                                          ncp_uint8_t stpId, ncp_eioa_stp_state_t state);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the spanning tree state for a port
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] port   The eioa port
 * @param[out] state  Spanning tree state 
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_port_stp_state_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_port_stp_state_get(ncp_hdl_t ncpHdl, ncp_macChan_t port, 
                                          ncp_uint8_t stpId, ncp_eioa_stp_state_t* state);


/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the system wide bridging age hysteresis value. 
 *        This API is valid only for AXM55xx.
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] ageHysteresis The new age hysteresis value. Valid range: 0-63.
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDING_AGE_HYSTERESIS_INVALID When age hysteresis value is out of range.
 * @see ncp_eioa_switch_bridge_age_hysteresis_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_age_hysteresis_set(ncp_hdl_t ncpHdl, ncp_uint32_t ageHysteresis);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the system wide bridging age hysteresis value. 
 *        This API is valid only for AXM55xx.
 * @param[in] ncpHdl NCP API state handle.
 * @param[out] ageHysteresis The pointer to store the age hysteresis value.
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_INVALID_BUFFER When ageHysteresis pointer is NULL.
 * @see ncp_eioa_switch_bridge_age_hysteresis_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_age_hysteresis_get(ncp_hdl_t ncpHdl, ncp_uint32_t *ageHysteresis);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the bridging vps which will be removed during protected port masking
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] remVpaBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @see ncp_eioa_switch_bridge_protected_port_vps_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_protected_port_vps_set(ncp_hdl_t ncpHdl, ncp_eioa_vps_bitmap_t remVpsBitMap);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the bridging vps which will be removed during protected port masking
 * @param[in] ncpHdl NCP API state handle.
 * @param[out] remVpaBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_protected_port_vps_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_protected_port_vps_get(ncp_hdl_t ncpHdl, ncp_eioa_vps_bitmap_t* remVpsBitMap);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the bridging vps which will be added for flooding unknown unicast packets
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] addVpsBitMap The bridging vps which will be added
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @see ncp_eioa_switch_bridge_flooding_vps_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_flooding_vps_set(ncp_hdl_t ncpHdl, ncp_eioa_vps_bitmap_t addVpsBitMap);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the bridging vps which will be added for flooding unknown unicast packets
 * @param[in] ncpHdl NCP API state handle.
 * @param[out] addVpsBitMap The bridging vps which will be added
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_flooding_vps_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_flooding_vps_get(ncp_hdl_t ncpHdl, ncp_eioa_vps_bitmap_t* addVpsBitMap);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the bridging vps which will be removed when stp state is blocking
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @see ncp_eioa_switch_bridge_stp_blocking_state_vps_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_stp_blocking_state_vps_set(ncp_hdl_t ncpHdl, ncp_eioa_vps_bitmap_t remVpsBitMap);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the bridging vps which will be removed when stp state is blocking
 * @param[in] ncpHdl NCP API state handle.
 * @param[out] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_stp_blocking_state_vps_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_stp_blocking_state_vps_get(ncp_hdl_t ncpHdl, ncp_eioa_vps_bitmap_t* remVpsBitMap);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the bridging vps which will be removed when stp state is learning
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @see ncp_eioa_switch_bridge_stp_learning_state_vps_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_stp_learning_state_vps_set(ncp_hdl_t ncpHdl, ncp_eioa_vps_bitmap_t remVpsBitMap);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the bridging vps which will be removed when stp state is learning
 * @param[in] ncpHdl NCP API state handle.
 * @param[out] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_stp_learning_state_vps_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_stp_learning_state_vps_get(ncp_hdl_t ncpHdl, ncp_eioa_vps_bitmap_t* remVpsBitMap);


/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the bridging vp which will be added during learning queue mapping
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] addVpBit The bridging vp which will be added
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @see ncp_eioa_switch_bridge_learning_vps_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_learning_vps_set(ncp_hdl_t ncpHdl, ncp_eioa_vp_bit_t addVpBit);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the bridging vp which will be added during learning queue mapping
 * @param[in] ncpHdl NCP API state handle.
 * @param[out] addVpBit The bridging vp which will be added
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_learning_vps_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_learning_vps_get(ncp_hdl_t ncpHdl, ncp_eioa_vp_bit_t* addVpBit);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to enable/disable bridging learning notification.
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] enable Whether to enable or disable bridging learning notification
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_SWITCH_HANDLE_INVALID When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_learning_notification_enable_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_learning_notification_enable_set(ncp_hdl_t ncpHdl, ncp_bool_t enable);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get whether bridging learning notification is enabled or not.
 * @param[in] ncpHdl NCP API state handle.
 * @param[out] enable Pointer to ncp_bool_t to store whether learning notification is enabled or not.
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_learning_notification_enable_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_learning_notification_enable_get(ncp_hdl_t ncpHdl, ncp_bool_t *enable);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the bridging vp which will be added during igmp snoop mapping
 *        This API is valid for 25xx only. Later chips support per protocol snooping. Refer to
 *        ncp_eioa_switch_bridge_ethertype_snooping_vps_set
 * @param[in] ncpHdl NCP API state handle.
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @see ncp_eioa_switch_bridge_igmp_snooping_vps_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_igmp_snooping_vps_set(ncp_hdl_t ncpHdl, ncp_eioa_vp_bit_t addVpBit);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the bridging vp which will be added during igmp snoop mapping
 *        This API is valid for 25xx only. Later chips support per protocol snooping. Refer to
 *        ncp_eioa_switch_bridge_ethertype_snooping_vps_get
 * @param[in] ncpHdl NCP API state handle.
 * @param[out] addVpBit The bridging vp which will be added
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_igmp_snooping_vps_set
 * Only for 25xx
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_igmp_snooping_vps_get(ncp_hdl_t ncpHdl, ncp_eioa_vp_bit_t* addVpBit);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the bridging vp which will be added during user snoop mapping
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] tcpport The tcpport to match to perform user snooping
 * @param[in] addVpBit The bridging vp which will be added
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @see ncp_eioa_switch_bridge_user_snooping_vps_get
 * Only for 25xx
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_user_snooping_vps_set(ncp_hdl_t ncpHdl, ncp_uint16_t tcpport, ncp_eioa_vp_bit_t addVpBit);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the bridging vp and the tcpport to match during user snoop mapping
 * @param[in] ncpHdl NCP API state handle.
 * @param[out] tcpport The tcpport to match to perform user snooping
 * @param[out] addVpBit The bridging vp which will be added
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_user_snooping_vps_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_user_snooping_vps_get(ncp_hdl_t ncpHdl, ncp_uint16_t* tcpport, ncp_eioa_vp_bit_t* addVpBit);


/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the bridging vps which will be removed for the port during port aggregation
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] port   The eioa port
 * @param[in] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @see ncp_eioa_switch_bridge_aggregation_port_vps_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_aggregation_port_vps_set(ncp_hdl_t ncpHdl, ncp_macChan_t port, ncp_eioa_vps_bitmap_t remVpsBitMap);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the bridging vps which will be removed for the port during port aggregation
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] port   The eioa port
 * @param[out] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_aggregation_port_vps_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_aggregation_port_vps_get(ncp_hdl_t ncpHdl, ncp_macChan_t port, ncp_eioa_vps_bitmap_t* remVpsBitMap);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the bridging vps which will be removed for the computed hash idx during port aggregation
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] idx    The computed layer 2 or layer 3 hash idx
 * @param[in] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @retval NCP_ST_EIOA_BRIDGE_AGGREGATION_HASH_INVALID_IDX When idx invalid.
 * @see ncp_eioa_switch_bridge_aggregation_hash_vps_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_aggregation_hash_vps_set(ncp_hdl_t ncpHdl, ncp_uint8_t idx, ncp_eioa_vps_bitmap_t remVpsBitMap);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the bridging vps which will be removed for the computed hash idx during port aggregation
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] idx    The computed layer 2 or layer 3 hash idx
 * @param[out] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDGE_AGGREGATION_HASH_INVALID_IDX When idx invalid.
 * @see ncp_eioa_switch_bridge_aggregation_hash_vps_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_aggregation_hash_vps_get(ncp_hdl_t ncpHdl, ncp_uint8_t idx, ncp_eioa_vps_bitmap_t* remVpsBitMap);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the bridging vps which will be removed for a vlan during vlan masking
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] vlanId Vlan id
 * @param[in] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_INVALID_VLAN_ID When vlanId is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @see ncp_eioa_switch_bridge_vlan_vps_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_vlan_vps_set(ncp_hdl_t ncpHdl, ncp_uint16_t vlanId, ncp_eioa_vps_bitmap_t remVpsBitMap);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the bridging vps which will be removed for a vlan during vlan masking
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] vlanId Vlan id
 * @param[out] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_INVALID_VLAN_ID When vlanId is invalid.
 * @see ncp_eioa_switch_bridge_vlan_vps_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_vlan_vps_get(ncp_hdl_t ncpHdl, ncp_uint16_t vlanId, ncp_eioa_vps_bitmap_t* remVpsBitMap);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the bridging vp which will be added during supervisor queue mapping
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] addVpBit The bridging vp which will be added
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @see ncp_eioa_switch_bridge_supervisor_route_vps_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_supervisor_route_vps_set(ncp_hdl_t ncpHdl, ncp_eioa_vp_bit_t addVpBit);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the bridging vp which will be added during supervisor queue mapping
 * @param[in] ncpHdl NCP API state handle.
 * @param[out] addVpBit The bridging vp which will be added
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_supervisor_route_vps_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_supervisor_route_vps_get(ncp_hdl_t ncpHdl, ncp_eioa_vp_bit_t* addVpBit);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the bridging vps which will be removed during source port masking
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] port   The eioa port
 * @param[in] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @see ncp_eioa_switch_bridge_source_port_vps_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_source_port_vps_set(ncp_hdl_t ncpHdl, ncp_macChan_t port, ncp_eioa_vps_bitmap_t remVpsBitMap);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the bridging vps which will be removed during source port masking
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] port   The eioa port
 * @param[out] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_source_port_vps_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_source_port_vps_get(ncp_hdl_t ncpHdl, ncp_macChan_t port, ncp_eioa_vps_bitmap_t* remVpsBitMap);


/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the bridging vps which will be removed for a spanning tree during stp masking
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] stpIdx Spanning tree id
 * @param[in] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @see ncp_eioa_switch_bridge_stp_vps_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_stp_vps_set(ncp_hdl_t ncpHdl, ncp_uint8_t stpIdx, ncp_eioa_vps_bitmap_t remVpsBitMap);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the bridging vps which will be removed for a spanning tree during stp masking
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] stpIdx Spanning tree id
 * @param[out] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_stp_vps_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_stp_vps_get(ncp_hdl_t ncpHdl, ncp_uint8_t stpIdx, ncp_eioa_vps_bitmap_t* remVpsBitMap);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the bridging vps which will be added or removed for ip header error processing
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] enabled Flag to enable ip header error processing
 * @param[in] remVpsBitMap The bridging vps which will be removed
 * @param[in] addVpBit The bridging vp which will be added
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @see ncp_eioa_switch_bridge_ip_hdr_error_vps_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_ip_hdr_error_vps_set(ncp_hdl_t ncpHdl, ncp_bool_t enabled, ncp_eioa_vps_bitmap_t remVpsBitMap, ncp_eioa_vp_bit_t addVpBit);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the bridging vps which will be added or removed for ip header error processing
 * @param[in] ncpHdl NCP API state handle.
 * @param[out] enabled Flag to enable ip header error processing
 * @param[out] remVpsBitMap The bridging vps which will be removed
 * @param[out] addVpBit The bridging vp which will be added
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_ip_hdr_error_vps_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_ip_hdr_error_vps_get(ncp_hdl_t ncpHdl, ncp_bool_t* enabled, ncp_eioa_vps_bitmap_t* remVpsBitMap, ncp_eioa_vp_bit_t* addVpBit);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the bridging vps which will be added or removed for oam port processing
 *        This API is valid for 25xx only. Later chips support per ethertype snooping. Refer to
 *        ncp_eioa_switch_bridge_protocol_snooping_vps_set
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] addVpBit The bridging vp which will be added
 * @param[in] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @see ncp_eioa_switch_bridge_oam_port_vps_get
 * Only for 25xx
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_oam_port_vps_set(ncp_hdl_t ncpHdl, ncp_eioa_vp_bit_t addVpBit, ncp_eioa_vps_bitmap_t remVpsBitMap);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the bridging vps which will be added or removed for oam port processing
 *        This API is valid for 25xx only. Later chips support per ethertype snooping. Refer to
 *        ncp_eioa_switch_bridge_protocol_snooping_vps_get
 * @param[in] ncpHdl NCP API state handle.
 * @param[out] addVpBit The bridging vp which will be added
 * @param[out] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_oam_port_vps_set
 * Only for 25xx
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_oam_port_vps_get(ncp_hdl_t ncpHdl, ncp_eioa_vp_bit_t* addVpBit, ncp_eioa_vps_bitmap_t* remVpsBitMap);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the bridging vps which will be removed during layer 2 source deny processing
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @see ncp_eioa_switch_bridge_layer2_source_deny_vps_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_layer2_source_deny_vps_set(ncp_hdl_t ncpHdl, ncp_eioa_vps_bitmap_t remVpsBitMap);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the bridging vps which will be removed during layer 2 source deny processing
 * @param[in] ncpHdl NCP API state handle.
 * @param[out] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_layer2_source_deny_vps_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_layer2_source_deny_vps_get(ncp_hdl_t ncpHdl, ncp_eioa_vps_bitmap_t* remVpsBitMap);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the bridging vps which will be added or removed during ttl processing
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] remVpsBitMap The bridging vps which will be removed
 * @param[in] addVpBit The bridging vp which will be added
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @see ncp_eioa_switch_bridge_ttl_vps_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_ttl_vps_set(ncp_hdl_t ncpHdl, ncp_eioa_vps_bitmap_t remVpsBitMap, ncp_eioa_vp_bit_t addVpBit);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the bridging vps which will be added or removed during ttl processing
 * @param[in] ncpHdl NCP API state handle.
 * @param[out] remVpsBitMap The bridging vps which will be removed
 * @param[out] addVpBit The bridging vp which will be added
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_ttl_vps_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_ttl_vps_get(ncp_hdl_t ncpHdl, ncp_eioa_vps_bitmap_t* remVpsBitMap, ncp_eioa_vp_bit_t* addVpBit);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the bridging vps which will be added or removed during source or destination mirroring
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] remVpsBitMap The bridging vps which will be removed
 * @param[in] addVpBit The bridging vp which will be added
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @see ncp_eioa_switch_bridge_mirroring_vps_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_mirroring_vps_set(ncp_hdl_t ncpHdl, ncp_eioa_vps_bitmap_t remVpsBitMap, ncp_eioa_vp_bit_t addVpBit);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the bridging vps which will be added or removed during source or destination mirroring
 * @param[in] ncpHdl NCP API state handle.
 * @param[out remVpsBitMap The bridging vps which will be removed
 * @param[out] addVpBit The bridging vp which will be added
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_mirroring_vps_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_mirroring_vps_get(ncp_hdl_t ncpHdl, ncp_eioa_vps_bitmap_t* remVpsBitMap, ncp_eioa_vp_bit_t* addVpBit);


/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the bridging vps which will be removed as a global mask
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @see ncp_eioa_switch_bridge_global_vps_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_global_vps_set(ncp_hdl_t ncpHdl, ncp_eioa_vps_bitmap_t remVpsBitMap);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the bridging vps which will be removed as a global mask
 * @param[in] ncpHdl NCP API state handle.
 * @param[out] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_global_vps_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_global_vps_get(ncp_hdl_t ncpHdl, ncp_eioa_vps_bitmap_t* remVpsBitMap);


/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the bridging vps which will be added and removed for the specified ethertype
 *        This API is not supported for 25xx
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] ethertype The ethertype for which to set the vps
 * @param[in] addVpsBitMap The bridging vps which will be added
 * @param[in] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @see ncp_eioa_switch_bridge_ethertype_snooping_vps_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_ethertype_snooping_vps_set(ncp_hdl_t ncpHdl, ncp_eioa_ethertype_idx_t ethertype, ncp_eioa_vps_bitmap_t addVpsBitMap, ncp_eioa_vps_bitmap_t remVpsBitMap);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the bridging vps which will be added and removed for the specified ethertype
 *        This API is not supported for 25xx
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] ethertype The ethertype for which to get the vps
 * @param[out] addVpsBitMap The bridging vps which will be added
 * @param[out] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @see ncp_eioa_switch_bridge_ethertype_snooping_vps_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_ethertype_snooping_vps_get(ncp_hdl_t ncpHdl, ncp_eioa_ethertype_idx_t ethertype, ncp_eioa_vps_bitmap_t* addVpsBitMap, ncp_eioa_vps_bitmap_t *remVpsBitMap);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the bridging vps which will be added and removed for the specified protocol
 *        This API is not supported for 25xx
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] protocol The protocol for which to set the vps
 * @param[in] addVpsBitMap The bridging vps which will be added
 * @param[in] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @see ncp_eioa_switch_bridge_protocol_snooping_vps_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_protocol_snooping_vps_set(ncp_hdl_t ncpHdl, ncp_eioa_ip_proto_idx_t protocol, ncp_eioa_vps_bitmap_t addVpsBitMap, ncp_eioa_vps_bitmap_t remVpsBitMap);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the bridging vps which will be added and removed for the specified protocol
 *        This API is not supported for 25xx
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] protocol The protocol for which to get the vps
 * @param[in] addVpsBitMap The bridging vps which will be added
 * @param[in] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @see ncp_eioa_switch_bridge_protocol_snooping_vps_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_protocol_snooping_vps_get(ncp_hdl_t ncpHdl, ncp_eioa_ip_proto_idx_t protocol, ncp_eioa_vps_bitmap_t* addVpsBitMap, ncp_eioa_vps_bitmap_t *remVpsBitMap);


/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get a list of all bridging key entries along with their
 * attributes.
 * @details Since the switch block is continuously learning and aging entries affecting
 * multiple h/w tables, the atomic flag can be used to get a consistent snapshot. Setting
 * atomic to TRUE temporarily turns off dynamic port learning and aging while the h/w tables
 * are read.
 * At the end, application specified callback function is invoked for each valid entry
 * in the database
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] atomic This flag determines whether learning and aging should be turned off during
 *                   the operation
 * @param[in] cbfn Application specified callback function which is invoked for each valid entry
 * @param[in] rock Application specified opaque pointer passed back to the callback. Application
 *                 can use this to pass state it itself.
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @deprecated Used deprecated \ref ncp_eioa_switch_bridge_entry_list_cb_fn_t.
 * Replaced by \ref ncp_eioa_switch_bridge_entry_list2
 * @since 1.3.0
 * @see ncp_eioa_switch_bridge_entry_list2
 */
#ifndef SWIG
NCP_API ncp_st_t
ncp_eioa_switch_bridge_entry_list(ncp_hdl_t ncpHdl, ncp_bool_t atomic, 
                                  ncp_eioa_switch_bridge_entry_list_cb_fn_t cbfn, void *rock);
#endif /* #ifndef SWIG */


/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get a list of all bridging key entries along with their
 * attributes.
 * @details Since the switch block is continuously learning and aging entries affecting
 * multiple h/w tables, the atomic flag can be used to get a consistent snapshot. Setting
 * atomic to TRUE temporarily turns off dynamic port learning and aging while the h/w tables
 * are read.
 * At the end, application specified callback function is invoked for each valid entry
 * in the database
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] atomic This flag determines whether learning and aging should be turned off during
 *                   the operation
 * @param[in] cbfn Application specified callback function which is invoked for each valid entry
 * @param[in] rock Application specified opaque pointer passed back to the callback. Application
 *                 can use this to pass state it itself.
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_bridge_protocol_snooping_vps_set
 */
#ifndef SWIG
NCP_API ncp_st_t
ncp_eioa_switch_bridge_entry_list2(ncp_hdl_t ncpHdl, ncp_bool_t atomic,
                                  ncp_eioa_switch_bridge_entry_list_cb_fn_t2 cbfn, void *rock);
#endif /* #ifndef SWIG */
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to flush the briding key table. 
 * @param[in] ncpHdl NCP API state handle.
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_ERROR There was an error in flushing the entries. The operation timed out
 * @see ncp_eioa_switch_bridge_protocol_snooping_vps_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_entry_flush(ncp_hdl_t ncpHdl);


/* 56xx onwards APIs */

/*!
 * @ingroup _eioa_switch_bridge
 * @brief Per domain attributes. Only applies to 56xx
 * @see
 */
typedef struct {
    ncp_bool_t          ivlMode;
    ncp_bool_t          enableLearning;
} ncp_eioa_switch_domain_attrs_t;

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set attributes for a virtual domain. Only applies to 56xx
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] domainId   The domain id. Domain ids range is 0-511
 * @param[in] attrs  Domain attributes
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_INVALID_DOMAIN_ID When domain id is invalid.
 * @see ncp_eioa_switch_bridge_domain_attrs_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_domain_attrs_set(ncp_hdl_t ncpHdl, ncp_uint16_t domainId, ncp_eioa_switch_domain_attrs_t* attrs);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the attributes for a virtual domain. Only applies to 56xx
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] domainId   The domain id. Domain ids range is 0-511
 * @param[out] attrs  Domain attributes
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_INVALID_DOMAIN_ID When domain id is invalid.
 * @see ncp_eioa_switch_bridge_domain_attrs_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_domain_attrs_set(ncp_hdl_t ncpHdl, ncp_uint16_t domainId, ncp_eioa_switch_domain_attrs_t* attrs);

/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to set the bridging vps which will be removed for a domain during domain masking. Only applies to 56xx
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] domainId Domain id
 * @param[in] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_INVALID_DOMAIN_ID When domainId is invalid.
 * @retval NCP_ST_EIOA_BRIDING_INVALID_BRIDGING_VP When a bridging vp is invalid
 * @see ncp_eioa_switch_bridge_domain_vps_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_domain_vps_set(ncp_hdl_t ncpHdl, ncp_uint16_t domainId, ncp_eioa_vps_bitmap_t remVpsBitMap);
/*!
 * @ingroup _eioa_switch_bridge
 * @brief This API is used to get the bridging vps which will be removed for a domain during domain masking. Only applies to 56xx
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] domainId Domain id
 * @param[out] remVpsBitMap The bridging vps which will be removed
 * @retval NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @retval NCP_ST_EIOA_INVALID_DOMAIN_ID When domainId is invalid.
 * @see ncp_eioa_switch_bridge_domain_vps_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_bridge_domain_vps_get(ncp_hdl_t ncpHdl, ncp_uint16_t domainId, ncp_eioa_vps_bitmap_t* remVpsBitMap);


#ifdef __cplusplus
}
#endif

#endif /* #ifndef _NCP_EIOA_SWITCH_BRIDGE_H_ */

