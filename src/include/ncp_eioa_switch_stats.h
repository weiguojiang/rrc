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

/*! @file     ncp_eioa_switch_stats.h                                        */

/*! 
 * @defgroup _eioa_switch_stats    Eioa Switch Statistics
 * @ingroup  _eioa_switch_
 *
 * @brief    Eioa Switch Statistics APIs.
 * @details  Eioa Switch Statistics defines, structures and APIs. These APIs provide the ability
 *           to get/set counters and group memberships for ports, dscp values and vlan ids.
 *
 *****************************************************************************/

#ifndef _NCP_EIOA_SWITCH_STATS_H_
#define _NCP_EIOA_SWITCH_STATS_H_

#include "ncp.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @ingroup _eioa_switch_stats
 * @brief EIOA Switch Stats direction enum. Enum defining the direction of stats being monitored.
 * @see ncp_eioa_switch_stats_get
 */
typedef enum ncp_eioa_switch_stats_direction_e
{
    ncp_direction_rx,   /*!< Ingress direction */
    ncp_direction_tx,   /*!< Egress direction */
    ncp_direction_both  /*!< Don't care. This type is valid for 25xx only. The 25xx chip has the same 
                         * counters which can divided between rx and tx counters. 55xx and later chips
                         * have separate counters for rx and tx */
} ncp_eioa_switch_stats_direction_t;

/*!
 * @ingroup _eioa_switch_stats
 * @brief EIOA Switch Statistics data structure
 * @see ncp_eioa_switch_stats_get
 */
typedef struct ncp_eioa_switch_stats_st
{
    ncp_uint64_t packet_count; /*!< Number of packets. */
    ncp_uint64_t byte_count;   /*!< Number of bytes. */
} ncp_eioa_switch_stats_t;

/*!
 * @ingroup _eioa_switch_stats
 * @typedef ncp_eioa_switch_stats_callback_fn_t
 * @brief   User specified callback function which is invoked for each group combination defined. 
 *          (Deprecated) See ncp_eioa_switch_statistics_callback_fn_t
 *     \li :: If non-zero is returned, the callback is aborted.
 * @see     ncp_eioa_switch_stats_get_all
 */
typedef int (*ncp_eioa_switch_stats_callback_fn_t)
                                    (void *rock, ncp_eioa_switch_stats_direction_t direction,
                                     ncp_uint32_t portGroup, ncp_uint32_t dscpGroup,
                                     ncp_uint32_t vlanGroup, ncp_uint32_t counterId,
                                     ncp_eioa_switch_stats_t *stats);


/*!
 * @ingroup _eioa_switch_stats
 * @brief This API retrieves the EIOA Switch Statistics for the given
 * direction, portGroup, dscpGroup and vlanGroup. The counter values are filled
 * in stats parameter if provided. If reset parameter is set to true, the stats
 * are cleared.
 * (Deprecated) Only valid for 25xx. See ncp_eioa_switch_statistics_get
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] direction The direction of stats being collected.
 * @param[in] portGroupId Port group for which the stats are to be fetched.
 * @param[in] dscpGroupId DSCP group for which the stats are to be fetched.
 * @param[in] vlanGroupId VLAN group for which the stats are to be fetched.
 * @param[out] stats Pointer to ncp_eioa_switch_stats_t where the stats are filled.
 * @param[in] reset If TRUE, the stats are cleared.
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_DIRECTION When direction is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_PORT_GROUP When portGroup is invalid
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_DSCP_GROUP When DSCP group is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_VLAN_GROUP When VLAN group is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_COUNTER_NOT_DEFINED When the counter identified by
 *         the parameters is not defined.
 * @see ncp_eioa_switch_stats_direction_t
 * @see ncp_eioa_switch_stats_t
 * @see ncp_eioa_switch_stats_get_all
 */
NCP_API ncp_st_t
ncp_eioa_switch_stats_get(ncp_hdl_t ncpHdl, ncp_eioa_switch_stats_direction_t direction,
                          ncp_uint32_t portGroup, ncp_uint32_t dscpGroup,
                          ncp_uint32_t vlanGroup, ncp_eioa_switch_stats_t *stats,
                          ncp_bool_t reset);


/*!
 * @ingroup _eioa_switch_stats
 * @brief This API retrieves the EIOA Switch Statistics for all the defined
 * combinations of direction, portGroup, dscpGroup and vlanGroup. For each
 * combination, user specified callback function is invoked. If readStats is 
 * specified as TRUE, the counter values are filled in. If readStats is TRUE and
 * reset is also TRUE, the counters are cleared after reading.
 * (Deprecated) Only valid for 25xx. See ncp_eioa_switch_statistics_get_all
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] readStats   Whether the counters need to be read
 * @param[in] reset  Whether the counters need to be reset. Only valid if read is TRUE
 * @param[in] cbfn   User callback function
 * @param[in] cbarg  User argument passed to callback function
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_stats_direction_t
 * @see ncp_eioa_switch_stats_t
 * @see ncp_eioa_switch_stats_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_stats_get_all(ncp_hdl_t ncpHdl, ncp_bool_t readStats, ncp_bool_t reset, 
                              ncp_eioa_switch_stats_callback_fn_t cbfn, void* cbarg);



/*!
 * @ingroup _eioa_switch_stats
 * @brief This API reads the specified counter values. If reset is TRUE, the
 * counter values are reset
 * (Deprecated) Only valid for 25xx. See ncp_eioa_switch_statistics_counter_read
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] counterId  The counter id to read
 * @param[out] stats Pointer to ncp_eioa_switch_stats_t where the stats are filled.
 * @param[in] reset If TRUE, the stats are cleared.
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_COUNTER When counter id is invalid.
 * @see ncp_eioa_switch_stats_direction_t
 * @see ncp_eioa_switch_stats_t
 * @see ncp_eioa_switch_stats_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_stats_counter_read(ncp_hdl_t ncpHdl, ncp_uint32_t counterId, 
                                   ncp_eioa_switch_stats_t *stats, ncp_bool_t reset);

/*!
 * @ingroup _eioa_switch_stats
 * @brief This API sets the counter to use for the specified
 * direction, portGroup, dscpGroup and vlanGroup. 
 * (Deprecated) Only valid for 25xx. See ncp_eioa_switch_statistics_counter_set
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] direction The direction of stats being collected.
 * @param[in] portGroupId Port group for which the stats are to be fetched.
 * @param[in] dscpGroupId DSCP group for which the stats are to be fetched.
 * @param[in] vlanGroupId VLAN group for which the stats are to be fetched.
 * @param[in] counterId   The counter id to assign to this combination
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_DIRECTION When direction is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_PORT_GROUP When portGroup is invalid
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_DSCP_GROUP When DSCP group is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_VLAN_GROUP When VLAN group is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_COUNTER When the counter id is invalid
 * @see ncp_eioa_switch_stats_direction_t
 * @see ncp_eioa_switch_stats_t
 * @see ncp_eioa_switch_stats_counter_get
 * @see ncp_eioa_switch_stats_counter_rem
 */
NCP_API ncp_st_t
ncp_eioa_switch_stats_counter_set(ncp_hdl_t ncpHdl, ncp_eioa_switch_stats_direction_t direction,
                                  ncp_uint32_t portGroupId, ncp_uint32_t dscpGroupId,
                                  ncp_uint32_t vlanGroupId, ncp_uint32_t counterId);

/*!
 * @ingroup _eioa_switch_stats
 * @brief This API retrieves the counter id mapped to the specified
 * direction, portGroup, dscpGroup and vlanGroup. 
 * (Deprecated) Only valid for 25xx. See ncp_eioa_switch_statistics_counter_get
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] direction The direction of stats being collected.
 * @param[in] portGroupId Port group for which the stats are to be fetched.
 * @param[in] dscpGroupId DSCP group for which the stats are to be fetched.
 * @param[in] vlanGroupId VLAN group for which the stats are to be fetched.
 * @param[out] counterId   The counter id assigned to this combination
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_DIRECTION When direction is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_PORT_GROUP When portGroup is invalid
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_DSCP_GROUP When DSCP group is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_VLAN_GROUP When VLAN group is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_COUNTER_NOT_DEFINED When this combination is not mapped to a counter
 * @see ncp_eioa_switch_stats_direction_t
 * @see ncp_eioa_switch_stats_t
 * @see ncp_eioa_switch_stats_counter_set
 * @see ncp_eioa_switch_stats_counter_rem
 */
NCP_API ncp_st_t
ncp_eioa_switch_stats_counter_get(ncp_hdl_t ncpHdl, ncp_eioa_switch_stats_direction_t direction,
                                  ncp_uint32_t portGroupId, ncp_uint32_t dscpGroupId,
                                  ncp_uint32_t vlanGroupId, ncp_uint32_t* counterId);

/*!
 * @ingroup _eioa_switch_stats
 * @brief This API removes the counter id mapped to the specified
 * direction, portGroup, dscpGroup and vlanGroup. 
 * (Deprecated) Only valid for 25xx. See ncp_eioa_switch_statistics_counter_rem
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] direction The direction for which the counter is to be removed
 * @param[in] portGroupId Port group for which the counter is to be removed
 * @param[in] dscpGroupId DSCP group for which the counter is to be removed
 * @param[in] vlanGroupId VLAN group for which the counter is to be removed
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_DIRECTION When direction is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_PORT_GROUP When portGroup is invalid
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_DSCP_GROUP When DSCP group is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_VLAN_GROUP When VLAN group is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_COUNTER_NOT_DEFINED When the counter identified by
 *         the parameters is not defined.
 * @see ncp_eioa_switch_stats_direction_t
 * @see ncp_eioa_switch_stats_t
 * @see ncp_eioa_switch_stats_counter_get
 * @see ncp_eioa_switch_stats_counter_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_stats_counter_rem(ncp_hdl_t ncpHdl, ncp_eioa_switch_stats_direction_t direction,
                                  ncp_uint32_t portGroupId, ncp_uint32_t dscpGroupId,
                                  ncp_uint32_t vlanGroupId);

/*!
 * @ingroup _eioa_switch_stats
 * @brief This API retrieves the default port group id
 * (Deprecated) Only valid for 25xx. See ncp_eioa_switch_statistics_default_port_group_get
 * @param[in] ncpHdl NCP API state handle.
 * @param[out] defaultPortGroupId   The default port group id
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_stats_port_group_get
 * @see ncp_eioa_switch_stats_port_group_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_stats_default_port_group_get(ncp_hdl_t ncpHdl, ncp_uint32_t *defaultPortGroupId);

/*!
 * @ingroup _eioa_switch_stats
 * @brief This API sets the group for the port
 * (Deprecated) Only valid for 25xx. See ncp_eioa_switch_statistics_port_group_set
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] port The port
 * @param[in] portGroupId   The group id to assign to the port
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 *     \li ::NCP_ST_INVALID_PORT_GROUP When portGroupId is invalid.
 * @see ncp_eioa_switch_stats_default_port_group_get
 * @see ncp_eioa_switch_stats_port_group_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_stats_port_group_set(ncp_hdl_t ncpHdl, ncp_macChan_t port, ncp_uint32_t portGroupId);

/*!
 * @ingroup _eioa_switch_stats
 * @brief This API retrieves the port group assigned to the port
 * (Deprecated) Only valid for 25xx. See ncp_eioa_switch_statistics_port_group_get
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] port The port
 * @param[out] portGroupId   The port group assigned to the port
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_stats_default_port_group_get
 * @see ncp_eioa_switch_stats_port_group_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_stats_port_group_get(ncp_hdl_t ncpHdl, ncp_macChan_t port, ncp_uint32_t* portGroupId);

/*!
 * @ingroup _eioa_switch_stats
 * @brief This API retrieves the default dscp group id
 * (Deprecated) Only valid for 25xx. See ncp_eioa_switch_statistics_default_dscp_group_get
 * @param[in] ncpHdl NCP API state handle.
 * @param[out] defaultDscpGroupId   The default dscp group id
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_stats_dscp_group_get
 * @see ncp_eioa_switch_stats_dscp_group_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_stats_default_dscp_group_get(ncp_hdl_t ncpHdl, ncp_uint32_t *defaultDscpGroupId);

/*!
 * @ingroup _eioa_switch_stats
 * @brief This API sets the group for the dscp
 * (Deprecated) Only valid for 25xx. See ncp_eioa_switch_statistics_dscp_group_set
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] dscp The dscp
 * @param[in] dscpGroupId   The group id to assign to the dscp
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 *     \li ::NCP_ST_EIOA_DSCP_INVALID When dscp is invalid.
 *     \li ::NCP_ST_INVALID_DSCP_GROUP When dscpGroupId is invalid.
 * @see ncp_eioa_switch_stats_default_dscp_group_get
 * @see ncp_eioa_switch_stats_dscp_group_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_stats_dscp_group_set(ncp_hdl_t ncpHdl, ncp_uint32_t dscp, ncp_uint32_t dscpGroupId);

/*!
 * @ingroup _eioa_switch_stats
 * @brief This API retrieves the dscp group assigned to the dscp
 * (Deprecated) Only valid for 25xx. See ncp_eioa_switch_statistics_dscp_group_get
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] dscp The dscp
 * @param[out] dscpGroupId   The dscp group assigned to the dscp
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 *     \li ::NCP_ST_EIOA_DSCP_INVALID When dscp is invalid.
 * @see ncp_eioa_switch_stats_default_dscp_group_get
 * @see ncp_eioa_switch_stats_dscp_group_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_stats_dscp_group_get(ncp_hdl_t ncpHdl, ncp_uint32_t dscp, ncp_uint32_t* dscpGroupId);

/*!
 * @ingroup _eioa_switch_stats
 * @brief This API retrieves the default vlan group id
 * (Deprecated) Only valid for 25xx. See ncp_eioa_switch_statistics_default_vlan_group_get
 * @param[in] ncpHdl NCP API state handle.
 * @param[out] defaultVlanGroupId   The default vlan group id
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_stats_vlan_group_get
 * @see ncp_eioa_switch_stats_vlan_group_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_stats_default_vlan_group_get(ncp_hdl_t ncpHdl, ncp_uint32_t *defaultVlanGroupId);

/*!
 * @ingroup _eioa_switch_stats
 * @brief This API sets the group for the vlan
 * (Deprecated) Only valid for 25xx. See ncp_eioa_switch_statistics_vlan_group_set
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] vlan The vlan
 * @param[in] vlanGroupId   The group id to assign to the vlan
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 *     \li ::NCP_ST_EIOA_INVALID_VLAN_ID When vlan is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_VLAN_GROUP When vlanGroupId is invalid.
 * @see ncp_eioa_switch_stats_default_vlan_group_get
 * @see ncp_eioa_switch_stats_vlan_group_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_stats_vlan_group_set(ncp_hdl_t ncpHdl, ncp_uint32_t vlan, ncp_uint32_t vlanGroupId);

/*!
 * @ingroup _eioa_switch_stats
 * @brief This API retrieves the vlan group assigned to the vlan
 * (Deprecated) Only valid for 25xx. See ncp_eioa_switch_statistics_vlan_group_get
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] vlan The vlan
 * @param[out] vlanGroupId   The vlan group assigned to the vlan
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 *     \li ::NCP_ST_EIOA_INVALID_VLAN_ID When vlan is invalid.
 * @see ncp_eioa_switch_stats_default_vlan_group_get
 * @see ncp_eioa_switch_stats_vlan_group_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_stats_vlan_group_get(ncp_hdl_t ncpHdl, ncp_uint32_t vlan, ncp_uint32_t* vlanGroupId);


/*!
 * @ingroup _eioa_switch_stats
 * @brief EIOA Switch Stats packet type. Enum defining the type of the packet
 *        Not valid for 25xx
 * @see ncp_eioa_switch_statistics_get
 */
typedef enum
{
    ncp_packettype_ip,      /*!< Ip packet */
    ncp_packettype_nonip,   /*!< Non Ip packet */
    ncp_packettype_both     /*!< Don't care */
} ncp_eioa_switch_stats_packettype_t;

/*!
 * @ingroup _eioa_switch_stats
 * @brief EIOA Switch Statistics counter specification. A counter is identified by the
 * direction, packettype (not valid for 25xx), port group, dscp group and  vlan group
 * @see ncp_eioa_switch_statistics_get
 */
typedef struct
{
    ncp_eioa_switch_stats_direction_t           direction;    /*!< Packet direction - tx/rx */
    ncp_eioa_switch_stats_packettype_t          packetType;   /*!< Packet type - ip/nonip */
    ncp_uint32_t                                portGroup;    /*!< Group the port belongs to */
    ncp_uint32_t                                dscpGroup;    /*!< Group the dscp value belongs to */
    ncp_uint32_t                                vlanGroup;    /*!< Group the vlan belongs to */
} ncp_eioa_switch_stats_counterspec_t;


/*!
 * @ingroup _eioa_switch_stats
 * @typedef ncp_eioa_switch_statistics_callback_fn_t
 * @brief   User specified callback function which is invoked for each direction/group combination defined. 
 *
 * @return
 *     \li :: If non-zero is returned, the callback is aborted.
 * @see     ncp_eioa_switch_statistics_get_all
 */
typedef int (*ncp_eioa_switch_statistics_callback_fn_t)
                                    (void *rock, ncp_eioa_switch_stats_counterspec_t* cspec,
                                     ncp_uint32_t counterId, ncp_eioa_switch_stats_t *stats);

/*!
 * @ingroup _eioa_switch_stats
 * @brief This API retrieves the EIOA Switch Statistics for the given
 * direction, packetType, portGroup, dscpGroup and vlanGroup. The counter values are filled
 * in stats parameter if provided. If reset parameter is set to true, the stats
 * are cleared.
 * Packettype is not valid 25xx and is ignored
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] cspec The counter specification structure which defines the direction,
 *            packetType, portGroup, dscpGroup and vlanGroup
 * @param[out] stats Pointer to ncp_eioa_switch_stats_t where the stats are filled.
 * @param[in] reset If TRUE, the stats are cleared.
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_DIRECTION When direction is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_PACKET_TYPE When packet type is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_PORT_GROUP When portGroup is invalid
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_DSCP_GROUP When DSCP group is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_VLAN_GROUP When VLAN group is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_COUNTER_NOT_DEFINED When the counter identified by
 *         the parameters is not defined.
 * @see ncp_eioa_switch_stats_direction_t
 * @see ncp_eioa_switch_stats_packettype_t
 * @see ncp_eioa_switch_stats_t
 * @see ncp_eioa_switch_statistics_get_all
 */
NCP_API ncp_st_t
ncp_eioa_switch_statistics_get(ncp_hdl_t ncpHdl, ncp_eioa_switch_stats_counterspec_t* cspec,
                               ncp_eioa_switch_stats_t *stats,
                               ncp_bool_t reset);
/*!
 * @ingroup _eioa_switch_stats
 * @brief This API retrieves the EIOA Switch Statistics for all the defined
 * combinations of direction, packetType, portGroup, dscpGroup and vlanGroup. For each
 * combination, user specified callback function is invoked. If readStats is 
 * specified as TRUE, the counter values are filled in. If readStats is TRUE and
 * reset is also TRUE, the counters are cleared after reading.
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] readStats   Whether the counters need to be read
 * @param[in] reset  Whether the counters need to be reset. Only valid if read is TRUE
 * @param[in] cbfn   User callback function
 * @param[in] cbarg  User argument passed to callback function
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_stats_direction_t
 * @see ncp_eioa_switch_stats_packettype_t
 * @see ncp_eioa_switch_stats_t
 * @see ncp_eioa_switch_statistics_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_statistics_get_all(ncp_hdl_t ncpHdl, ncp_bool_t readStats, ncp_bool_t reset, 
                                    ncp_eioa_switch_statistics_callback_fn_t cbfn, void* cbarg);
/*!
 * @ingroup _eioa_switch_stats
 * @brief This API reads the specified counter values. If reset is TRUE, the
 * counter values are reset
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] counterId  The counter id to read
 * @param[out] stats Pointer to ncp_eioa_switch_stats_t where the stats are filled.
 * @param[in] reset If TRUE, the stats are cleared.
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_DIRECTION When direction is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_COUNTER When counter id is invalid.
 * @see ncp_eioa_switch_stats_direction_t
 * @see ncp_eioa_switch_stats_packettype_t
 * @see ncp_eioa_switch_stats_t
 * @see ncp_eioa_switch_statistics_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_statistics_counter_read(ncp_hdl_t ncpHdl, ncp_eioa_switch_stats_direction_t direction,
                                        ncp_uint32_t counterId, ncp_eioa_switch_stats_t *stats, ncp_bool_t reset);
/*!
 * @ingroup _eioa_switch_stats
 * @brief This API sets the counter to use for the specified
 * direction, portGroup, packetType, dscpGroup and vlanGroup. 
 * Packettype is not valid 25xx and is ignored
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] cspec The counter specification structure which defines the direction,
 *            packetType, portGroup, dscpGroup and vlanGroup
 * @param[in] counterId   The counter id to assign to this combination
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_DIRECTION When direction is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_PACKET_TYPE When packet type is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_PORT_GROUP When portGroup is invalid
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_DSCP_GROUP When DSCP group is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_VLAN_GROUP When VLAN group is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_COUNTER When the counter id is invalid
 * @see ncp_eioa_switch_stats_direction_t
 * @see ncp_eioa_switch_stats_packettype_t
 * @see ncp_eioa_switch_stats_t
 * @see ncp_eioa_switch_statistics_counter_get
 * @see ncp_eioa_switch_statistics_counter_rem
 */
NCP_API ncp_st_t
ncp_eioa_switch_statistics_counter_set(ncp_hdl_t ncpHdl, ncp_eioa_switch_stats_counterspec_t* cspec,
                                       ncp_uint32_t counterId);
/*!
 * @ingroup _eioa_switch_stats
 * @brief This API retrieves the counter id mapped to the specified
 * direction, packetType, portGroup, dscpGroup and vlanGroup. 
 * Packettype is not valid 25xx and is ignored
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] cspec The counter specification structure which defines the direction,
 *            packetType, portGroup, dscpGroup and vlanGroup
 * @param[out] counterId   The counter id assigned to this combination
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_DIRECTION When direction is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_PACKET_TYPE When packet type is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_PORT_GROUP When portGroup is invalid
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_DSCP_GROUP When DSCP group is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_VLAN_GROUP When VLAN group is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_COUNTER_NOT_DEFINED When this combination is not mapped to a counter
 * @see ncp_eioa_switch_stats_direction_t
 * @see ncp_eioa_switch_stats_packettype_t
 * @see ncp_eioa_switch_stats_t
 * @see ncp_eioa_switch_statistics_counter_set
 * @see ncp_eioa_switch_statistics_counter_rem
 */
NCP_API ncp_st_t
ncp_eioa_switch_statistics_counter_get(ncp_hdl_t ncpHdl, ncp_eioa_switch_stats_counterspec_t* cspec,
                                       ncp_uint32_t* counterId);
/*!
 * @ingroup _eioa_switch_stats
 * @brief This API removes the counter id mapped to the specified
 * direction, packetType, portGroup, dscpGroup and vlanGroup. 
 * Packettype is not valid 25xx and is ignored
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] cspec The counter specification structure which defines the direction,
 *            packetType, portGroup, dscpGroup and vlanGroup
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_DIRECTION When direction is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_PACKET_TYPE When packet type is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_PORT_GROUP When portGroup is invalid
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_DSCP_GROUP When DSCP group is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_VLAN_GROUP When VLAN group is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_COUNTER_NOT_DEFINED When the counter identified by
 *         the parameters is not defined.
 * @see ncp_eioa_switch_stats_direction_t
 * @see ncp_eioa_switch_stats_packettype_t
 * @see ncp_eioa_switch_stats_t
 * @see ncp_eioa_switch_statistics_counter_get
 * @see ncp_eioa_switch_statistics_counter_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_statistics_counter_rem(ncp_hdl_t ncpHdl, ncp_eioa_switch_stats_counterspec_t* cspec);
/*!
 * @ingroup _eioa_switch_stats
 * @brief This API retrieves the default port group id for the specified tx or rx direction. 
 * Direction specification is not valid for 25xx and is ignored
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] direction The tx or rx direction. Not valid for 25xx and is ignored
 * @param[out] defaultPortGroupId   The default port group id
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_statistics_port_group_get
 * @see ncp_eioa_switch_statistics_port_group_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_statistics_default_port_group_get(ncp_hdl_t ncpHdl, ncp_eioa_switch_stats_direction_t direction, 
                                                  ncp_uint32_t *defaultPortGroupId);
/*!
 * @ingroup _eioa_switch_stats
 * @brief This API sets the group for the port for the specified tx or rx direction. 
 * Direction specification is not valid for 25xx and is ignored
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] direction The tx or rx direction. Not valid for 25xx and is ignored
 * @param[in] port The port
 * @param[in] portGroupId   The group id to assign to the port
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 *     \li ::NCP_ST_INVALID_PORT_GROUP When portGroupId is invalid.
 * @see ncp_eioa_switch_statistics_default_port_group_get
 * @see ncp_eioa_switch_statistics_port_group_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_statistics_port_group_set(ncp_hdl_t ncpHdl, ncp_eioa_switch_stats_direction_t direction, 
                                          ncp_macChan_t port, ncp_uint32_t portGroupId);
/*!
 * @ingroup _eioa_switch_stats
 * @brief This API retrieves the port group assigned to the port for the specified tx or rx direction. 
 * Direction specification is not valid for 25xx and is ignored
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] direction The tx or rx direction. Not valid for 25xx and is ignored
 * @param[in] port The port
 * @param[out] portGroupId   The port group assigned to the port
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_statistics_default_port_group_get
 * @see ncp_eioa_switch_statistics_port_group_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_statistics_port_group_get(ncp_hdl_t ncpHdl, ncp_eioa_switch_stats_direction_t direction, 
                                          ncp_macChan_t port, ncp_uint32_t* portGroupId);
/*!
 * @ingroup _eioa_switch_stats
 * @brief This API retrieves the default dscp group id
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] direction The tx or rx direction. Not valid for 25xx and is ignored
 * @param[out] defaultDscpGroupId   The default dscp group id
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_statistics_dscp_group_get
 * @see ncp_eioa_switch_statistics_dscp_group_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_statistics_default_dscp_group_get(ncp_hdl_t ncpHdl, ncp_eioa_switch_stats_direction_t direction, 
                                                  ncp_uint32_t *defaultDscpGroupId);
/*!
 * @ingroup _eioa_switch_stats
 * @brief This API sets the group for the dscp for the specified tx or rx direction. 
 * Direction specification is not valid for 25xx and is ignored
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] direction The tx or rx direction. Not valid for 25xx and is ignored
 * @param[in] dscp The dscp
 * @param[in] dscpGroupId   The group id to assign to the dscp
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 *     \li ::NCP_ST_EIOA_DSCP_INVALID When dscp is invalid.
 *     \li ::NCP_ST_INVALID_DSCP_GROUP When dscpGroupId is invalid.
 * @see ncp_eioa_switch_statistics_default_dscp_group_get
 * @see ncp_eioa_switch_statistics_dscp_group_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_statistics_dscp_group_set(ncp_hdl_t ncpHdl, ncp_eioa_switch_stats_direction_t direction, 
                                          ncp_uint32_t dscp, ncp_uint32_t dscpGroupId);
/*!
 * @ingroup _eioa_switch_stats
 * @brief This API retrieves the dscp group assigned to the dscp for the specified tx or rx direction. 
 * Direction specification is not valid for 25xx and is ignored
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] direction The tx or rx direction. Not valid for 25xx and is ignored
 * @param[in] dscp The dscp
 * @param[out] dscpGroupId   The dscp group assigned to the dscp
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 *     \li ::NCP_ST_EIOA_DSCP_INVALID When dscp is invalid.
 * @see ncp_eioa_switch_statistics_default_dscp_group_get
 * @see ncp_eioa_switch_statistics_dscp_group_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_statistics_dscp_group_get(ncp_hdl_t ncpHdl, ncp_eioa_switch_stats_direction_t direction, 
                                          ncp_uint32_t dscp, ncp_uint32_t* dscpGroupId);
/*!
 * @ingroup _eioa_switch_stats
 * @brief This API retrieves the default vlan group id for the specified tx or rx direction. 
 * Direction specification is not valid for 25xx and is ignored
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] direction The tx or rx direction. Not valid for 25xx and is ignored
 * @param[out] defaultVlanGroupId   The default vlan group id
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 * @see ncp_eioa_switch_statistics_vlan_group_get
 * @see ncp_eioa_switch_statistics_vlan_group_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_statistics_default_vlan_group_get(ncp_hdl_t ncpHdl, ncp_eioa_switch_stats_direction_t direction, 
                                                  ncp_uint32_t *defaultVlanGroupId);
/*!
 * @ingroup _eioa_switch_stats
 * @brief This API sets the group for the vlan for the specified tx or rx direction. 
 * Direction specification is not valid for 25xx and is ignored
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] direction The tx or rx direction. Not valid for 25xx and is ignored
 * @param[in] vlan The vlan
 * @param[in] vlanGroupId   The group id to assign to the vlan
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 *     \li ::NCP_ST_EIOA_INVALID_VLAN_ID When vlan is invalid.
 *     \li ::NCP_ST_EIOA_SWITCH_STATS_INVALID_VLAN_GROUP When vlanGroupId is invalid.
 * @see ncp_eioa_switch_statistics_default_vlan_group_get
 * @see ncp_eioa_switch_statistics_vlan_group_get
 */
NCP_API ncp_st_t
ncp_eioa_switch_statistics_vlan_group_set(ncp_hdl_t ncpHdl, ncp_eioa_switch_stats_direction_t direction, 
                                          ncp_uint32_t vlan, ncp_uint32_t vlanGroupId);
/*!
 * @ingroup _eioa_switch_stats
 * @brief This API retrieves the vlan group assigned to the vlan for the specified tx or rx direction. 
 * Direction specification is not valid for 25xx and is ignored
 * @param[in] ncpHdl NCP API state handle.
 * @param[in] direction The tx or rx direction. Not valid for 25xx and is ignored
 * @param[in] vlan The vlan
 * @param[out] vlanGroupId   The vlan group assigned to the vlan
 *
 * @return
 *     \li ::NCP_ST_INVALID_HANDLE When ncpHdl is invalid.
 *     \li ::NCP_ST_EIOA_INVALID_VLAN_ID When vlan is invalid.
 * @see ncp_eioa_switch_statistics_default_vlan_group_get
 * @see ncp_eioa_switch_statistics_vlan_group_set
 */
NCP_API ncp_st_t
ncp_eioa_switch_statistics_vlan_group_get(ncp_hdl_t ncpHdl, ncp_eioa_switch_stats_direction_t direction, 
                                          ncp_uint32_t vlan, ncp_uint32_t* vlanGroupId);





#ifdef __cplusplus
}
#endif

#endif /* #ifndef _NCP_EIOA_SWITCH_STATS_H_ */

