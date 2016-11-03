/**************************************************************************
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

/*! @file      ncp_eioa_policing.h
 *             
 *  @defgroup _eioa_switch_policer EIOA Switch Policer
 *  @ingroup  _eioa_switch_
 *
 *  @brief     EIOA switch policing APIs
 *
 *  @details   EIOA Switch Policing APIs, defines and structure definitions.
 *             The Policing API calls provide the ability to set and get 
 *             individual policers, color maps, and the demote map as well
 *             as the mapping of specifif VLANs and ACL rules to a policer.
 * 
 *  @{
 */


#ifndef _NCP_EIOA_POLICING_H_
#define _NCP_EIOA_POLICING_H_

#ifdef __cplusplus
extern "C" {
#endif


/* Public Definitions */


/* Public Enumerated Types */

/*!
 * @brief Policing mode.
 */
typedef enum ncp_eioa_switch_policer_mode_e
{
    NCP_EIOA_SWITCH_POLICER_MODE_ACL_RULE = 0,
    NCP_EIOA_SWITCH_POLICER_MODE_VLAN,
    NCP_EIOA_SWITCH_POLICER_MODE_ACL,
    NCP_EIOA_SWITCH_POLICER_MODE_MAX = NCP_EIOA_SWITCH_POLICER_MODE_ACL
} ncp_eioa_switch_policer_mode_t;

/*!
 * @brief Policer packet color codes.
 */
typedef enum ncp_eioa_switch_policer_color_e
{
    NCP_EIOA_SWITCH_POLICER_COLOR_GREEN = 0,
    NCP_EIOA_SWITCH_POLICER_COLOR_YELLOW,
    NCP_EIOA_SWITCH_POLICER_COLOR_RED,
    NCP_EIOA_SWITCH_POLICER_COLOR_UNKNOWN,
    NCP_EIOA_SWITCH_POLICER_COLOR_MAX = NCP_EIOA_SWITCH_POLICER_COLOR_UNKNOWN
} ncp_eioa_switch_policer_color_t;

/*!
 * @brief Available policer maximum burst sizes.
 */
typedef enum ncp_eioa_switch_policer_burst_size_e
{
    NCP_EIOA_SWITCH_POLICER_BURST_SIZE_MIN = 1,
    NCP_EIOA_SWITCH_POLICER_BURST_SIZE_64_BYTES = 1,
    NCP_EIOA_SWITCH_POLICER_BURST_SIZE_128_BYTES,
    NCP_EIOA_SWITCH_POLICER_BURST_SIZE_256_BYTES,
    NCP_EIOA_SWITCH_POLICER_BURST_SIZE_512_BYTES,
    NCP_EIOA_SWITCH_POLICER_BURST_SIZE_1_KBYTES,
    NCP_EIOA_SWITCH_POLICER_BURST_SIZE_2_KBYTES,
    NCP_EIOA_SWITCH_POLICER_BURST_SIZE_4_KBYTES,
    NCP_EIOA_SWITCH_POLICER_BURST_SIZE_8_KBYTES,
    NCP_EIOA_SWITCH_POLICER_BURST_SIZE_16_KBYTES,
    NCP_EIOA_SWITCH_POLICER_BURST_SIZE_32_KBYTES,
    NCP_EIOA_SWITCH_POLICER_BURST_SIZE_64_KBYTES,
    NCP_EIOA_SWITCH_POLICER_BURST_SIZE_128_KBYTES,
    NCP_EIOA_SWITCH_POLICER_BURST_SIZE_256_KBYTES,
    NCP_EIOA_SWITCH_POLICER_BURST_SIZE_512_KBYTES,
    NCP_EIOA_SWITCH_POLICER_BURST_SIZE_1_MBYTES,
    NCP_EIOA_SWITCH_POLICER_BURST_SIZE_MAX = 
                        NCP_EIOA_SWITCH_POLICER_BURST_SIZE_1_MBYTES
} ncp_eioa_switch_policer_burst_size_t;

/*! 
 * @brief Value to be used for the backpressureId when the policer does
 * not need to be a backpressure destination.
 */
#define NCP_EIOA_POLICER_NO_BP_DEST                   (0)

/* Public Structures */

/*!  * @brief Individual policer specifications.  */
typedef struct ncp_eioa_switch_policer_s
{
    /*! @brief  The ID of this policer */
    ncp_uint32_t    policerId;
    /*! @brief  The CIR in bits per second */
    ncp_uint64_t    committedRate;
    /*! @brief  The CIR max burst size in bytes */
    ncp_eioa_switch_policer_burst_size_t    committedMaxBurstSize;
    /*! @brief  The EIR in bits per second */
    ncp_uint64_t    peakRate;
    /*! @brief  The EIR max burst size in bytes */
    ncp_eioa_switch_policer_burst_size_t    peakMaxBurstSize;
    /*! @brief  The backpressure ID if the policer is to be a backpressure
     *          destination. The values are generated in C header file when the 
     *          user defines them in ASE. If this policer doesnt need to be a 
     *          backpressure destination set the value to NCP_EIOA_POLICER_NO_BP_DEST.
     */
    ncp_uint32_t    backpressureId;
    /*! @brief  Reserved - set to zero */
    ncp_uint32_t    flags;
    /*! @brief  Set to true if the EIR is to be ignored  */
    ncp_bool_t      useCommittedRateOnly;
    /*! @brief  Set to true if the EIR burst is to be coupled with
     *          the CIR burst size.  If true, excess CIR burst capacity
     *          is added to the EIR burst capacity.
     */
    ncp_bool_t      enableCoupling;
    /*! @brief  Set to true if the policer is to be color aware */
    ncp_bool_t      useColorMap;
    /*! @brief  If true, allows modification of the packet priority if the
     *          policing result color is yellow.  N/A for Multicast policers.
     */
    ncp_bool_t      demote;
    /*! @brief  If true, allows modification of the packet priority if there is
     *          backpressure, and the policing result color is yellow.
     *          N/A for Multicast policers.
     */
    ncp_bool_t      demoteIfCongested;
    /*! @brief  Set to false if the policer rates and attributes are to be set
     *          but the policer should be left disabled. 
     */
    ncp_bool_t      enablePolicer;

} ncp_eioa_switch_policer_t;


/*!  @brief DSCP demote map specification.  */
typedef struct ncp_eioa_switch_policer_dscp_demote_s
{
    /*! @brief  The initial DSCP value of the incomming packet */
    ncp_uint16_t    dscpValue;
    /*! @brief  The DSCP value to set if the priotity is to be demoted */
    ncp_uint16_t    dscpDemoteValue;
} ncp_eioa_switch_policer_dscp_demote_t;


/*!  @union dscpOrCos
 *   @brief dscpOrCos The initial ID (CoS or DSCP) the incomming packet.
 */
union dscpOrCos
{
    /*! @brief  The cos Value to assign a color to */
    ncp_uint16_t    cosValue;
    /*! @brief  The dscp Value to assign a color to */
    ncp_uint16_t    dscpValue;
};

/*!  @brief Color map specification */
typedef struct ncp_eioa_switch_policer_color_map_s
{
    /*! @brief  The MEF color to assign */
    ncp_eioa_switch_policer_color_t color;
    union dscpOrCos                 id;
    /*! @brief  Indicates if the entry is to be used when a backpressure
     *          condition exists.
     */
    ncp_bool_t                      backpressure;
} ncp_eioa_switch_policer_color_map_t;



/* Published APIs */

/*!
 *  @brief  Get the configured mode of the policing module
 *
 *  @param[in]  ncpHdl          Handle for the NCP containing the EIOA switch.
 *  @param[out] policingMode    Pointer to a ncp_eioa_switch_policer_mode_t
 *                              variable where the current mode will be placed.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_SWITCH_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_POLICER_HANDLE_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_switch_policer_mode_get(ncp_hdl_t ncpHdl,
                                 ncp_eioa_switch_policer_mode_t *policingMode);


/*!
 *  @brief  Set the parameters of an EIOA unicast policer.
 *
 *          The INVALID_PARAMETER status code is returned if an unsupported
 *          flag value is set.
 *
 *  @param[in]  ncpHdl      Handle for the NCP containing the EIOA switch.
 *  @param[in]  policer     Pointer to a ncp_eioa_switch_policer_t structure
 *                          that conteins the spcifications to set.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_INVALID_PARAMETER
 *      \li ::NCP_ST_EIOA_SWITCH_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_POLICER_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_ID_INVALID
 *      \li ::NCP_ST_EIOA_POLICER_RATE_TOO_FAST
 *      \li ::NCP_ST_EIOA_POLICER_RATE_TOO_SLOW
 *      \li ::NCP_ST_EIOA_POLICER_RATE_PEAK_LESS_THAN_COMMITTED
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_MAX_BURST_SIZE_INVALID
 *      \li ::NCP_ST_BP_INVALID_DEST_INDEX
 *      \li ::NCP_ST_BP_DEST_ID_ALREADY_SET
 */
NCP_API ncp_st_t
ncp_eioa_switch_policer_ucast_set(ncp_hdl_t ncpHdl,
                                  ncp_eioa_switch_policer_t *policer);


/*!
 *  @brief  Get the parameters of an EIOA unicast policer.
 *
 *          The INVALID_PARAMETER status code is returned if an unsupported
 *          flag value is set.
 *
 *  @param[in]      ncpHdl      Handle for the NCP containing the EIOA switch.
 *  @param[in,out]  policer     Pointer to a ncp_eioa_switch_policer_t structure
 *                              where the retrived values will be placed.
 *                              The policerId field of the structure needs
 *                              to be initilized with the ID of the policer
 *                              that is to be retrived.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_SWITCH_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_POLICER_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_ID_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_switch_policer_ucast_get(ncp_hdl_t ncpHdl,
                                  ncp_eioa_switch_policer_t *policer);

/*!
 *  @brief  Get the configured mode of the policing module
 *
 *  @param[in]  ncpHdl          Handle for the NCP containing the EIOA switch.
 *  @param[out] policingMode    Pointer to a ncp_eioa_switch_policer_mode_t
 *                              variable where the current mode will be placed.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_SWITCH_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_POLICER_HANDLE_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_switch_policer_mode_get(ncp_hdl_t ncpHdl,
                                 ncp_eioa_switch_policer_mode_t *policingMode);


/*!
 *  @brief  Set ignore backpressure flag for this policerId.
 *
 *          The INVALID_PARAMETER status code is returned if an unsupported
 *          flag value is set. Applies to 56xx and beyond
 *
 *  @param[in]  ncpHdl              Handle for the NCP containing the EIOA switch.
 *  @param[in]  policerId           Policer id for which the ignore backpressure flag needs to set
 *  @param[in]  ignoreBackpressure  Ignore backpressure flag that needs to be set
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_INVALID_PARAMETER
 *      \li ::NCP_ST_EIOA_SWITCH_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_POLICER_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_ID_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_switch_policer_ignore_backpressure_set(ncp_hdl_t ncpHdl, ncp_uint32_t policerId, ncp_bool_t *ignoreBackpressure);


/*!
 *  @brief  Get whether to ignore backpressure for this policerId.
 *
 *          The INVALID_PARAMETER status code is returned if an unsupported
 *          flag value is set. Applies to 56xx and beyond
 *
 *  @param[in]      ncpHdl             Handle for the NCP containing the EIOA switch.
 *  @param[in]      policerId          Policer id for which ignore backpressure flag has to be retrieved
 *  @param[out]     ignoreBackpressure Ignore backpressure flag that is returned
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_SWITCH_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_POLICER_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_ID_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_switch_policer_ignore_backpressure_get(ncp_hdl_t ncpHdl, ncp_uint32_t policerId, ncp_bool_t *ignoreBackpressure);

/*!
 *  @brief  Set the parameters of an EIOA multicast policer.
 *
 *  @param[in]  ncpHdl      Handle for the NCP containing the EIOA switch.
 *  @param[in]  policer     Pointer to a ncp_eioa_switch_policer_t structure
 *                          that conteins the spcifications to set.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_SWITCH_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_POLICER_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_ID_INVALID
 *      \li ::NCP_ST_EIOA_POLICER_RATE_TOO_FAST
 *      \li ::NCP_ST_EIOA_POLICER_RATE_TOO_SLOW
 *      \li ::NCP_ST_EIOA_POLICER_RATE_PEAK_LESS_THAN_COMMITTED
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_MAX_BURST_SIZE_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_switch_policer_mcast_set(ncp_hdl_t ncpHdl,
                                  ncp_eioa_switch_policer_t *policer);


/*!
 *  @brief  Get the parameters of an EIOA multicast policer.
 *
 *  @param[in]      ncpHdl      Handle for the NCP containing the EIOA switch.
 *  @param[in,out]  policer     Pointer to a ncp_eioa_switch_policer_t structure
 *                              where the retrived values will be placed.
 *                              The policerId field of the structure needs
 *                              to be initilized with the ID of the policer
 *                              that is to be retrived.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_SWITCH_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_POLICER_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_ID_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_switch_policer_mcast_get(ncp_hdl_t ncpHdl,
                                  ncp_eioa_switch_policer_t *policer);


/*!
 *  @brief  Set an EIOA policer CoS to color mapping.
 *
 *  @param[in]  ncpHdl      Handle for the NCP containing the EIOA switch.
 *  @param[in]  colorMap    Pointer to an ncp_eioa_switch_policer_color_map_t
 *                          structure. The id.cosValue field of the structure
 *                          needs to be initilized with the CoS value whose
 *                          color will be set. The color field needs to be
 *                          initialized with the color value to set.  The
 *                          backPressure field should be set to indicate if the
 *                          mapping applies when backpressure present or not.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_SWITCH_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_POLICER_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_COS_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_COLOR_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_switch_policer_cos_color_set(ncp_hdl_t ncpHdl,
                                  ncp_eioa_switch_policer_color_map_t *colorMap);


/*!
 *  @brief  Get an EIOA policer CoS to color mapping.
 *
 *  @param[in]      ncpHdl      Handle for the NCP containing the EIOA switch.
 *  @param[in,out]  colorMap    Pointer to an ncp_eioa_switch_policer_color_map_t
 *                              structure where the color value will be placed.
 *                              The id.cosValue field of the structure needs
 *                              to be initilized with the CoS value whose
 *                              setting is to be retrived. The backPressure
 *                              field should be set to indicate if the mapping
 *                              for backpressure present is wanted.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_SWITCH_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_POLICER_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_COS_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_switch_policer_cos_color_get(ncp_hdl_t ncpHdl,
                                  ncp_eioa_switch_policer_color_map_t *colorMap);


/*!
 *  @brief  Set an EIOA policer DSCP to color mapping.
 *
 *  @param[in]  ncpHdl      Handle for the NCP containing the EIOA switch.
 *  @param[in]  colorMap    Pointer to an ncp_eioa_switch_policer_color_map_t
 *                          structure. The id.dscpValue field of the structure
 *                          needs to be initilized with the DSCP value whose
 *                          color will be set. The color field needs to be
 *                          initialized with the color value to set.  The
 *                          backPressure field should be set to indicate if the
 *                          mapping applies when backpressure present or not.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_SWITCH_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_POLICER_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_DSCP_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_COLOR_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_switch_policer_dscp_color_set(ncp_hdl_t ncpHdl,
                              ncp_eioa_switch_policer_color_map_t *colorMap);


/*!
 *  @brief  Get an EIOA policer DSCP to color mapping.
 *
 *  @param[in]      ncpHdl      Handle for the NCP containing the EIOA switch.
 *  @param[in,out]  colorMap    Pointer to an ncp_eioa_switch_policer_color_map_t
 *                              structure where the color value will be placed.
 *                              The id.dscpValue field of the structure needs
 *                              to be initilized with the DSCP value whose
 *                              setting is to be retrived. The backPressure
 *                              field should be set to indicate if the mapping
 *                              for backpressure present is wanted.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_SWITCH_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_POLICER_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_DSCP_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_switch_policer_dscp_color_get(ncp_hdl_t ncpHdl,
                               ncp_eioa_switch_policer_color_map_t *colorMap);


/*!
 *  @brief  Set an EIOA policer DSCP demote mapping.
 *
 *  @param[in]  ncpHdl  Handle for the NCP containing the EIOA switch.
 *  @param[in]  demote  Pointer to an ncp_eioa_switch_dscp_demote_t
 *                      structure. The dscpValue field of the structure
 *                      needs to be initilized with the DSCP value whose
 *                      demote value will be set. The dscpDemote field needs
 *                      to be initialized with the demote value to set.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_SWITCH_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_POLICER_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_DSCP_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_switch_policer_dscp_demote_set(ncp_hdl_t ncpHdl,
                                ncp_eioa_switch_policer_dscp_demote_t *demote);


/*!
 *  @brief  Get an EIOA policer DSCP demote mapping.
 *
 *  @param[in]      ncpHdl  Handle for the NCP containing the EIOA switch.
 *  @param[in,out]  demote  Pointer to an ncp_eioa_switch_policer_dscp_demote_t
 *                          structure where the dscp demote value will be placed.
 *                          The dscpValue field of the structure needs to be
 *                          initilized with the DSCP value whose setting is to
 *                          be retrived.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_SWITCH_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_POLICER_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_DSCP_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_switch_policer_dscp_demote_get(ncp_hdl_t ncpHdl,
                                ncp_eioa_switch_policer_dscp_demote_t *demote);


/*!
 *  @brief  Set an EIOA VLAN to policer mapping.
 *
 *  @param[in]  ncpHdl      Handle for the NCP containing the EIOA switch.
 *  @param[in]  vlanId      The VLAN ID that will be mapped.
 *  @param[in]  policerId   The policer ID that the VLAN ID will be
 *                          mapped to.
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_SWITCH_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_POLICER_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_VLAN_ID_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_ID_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_MODE_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_switch_policer_vlan_set(ncp_hdl_t ncpHdl,
                                 ncp_uint32_t vlanId,
                                 ncp_uint32_t policerId);


/*!
 *  @brief  Get an EIOA VLAN to policer mapping.
 *
 *  @param[in]  ncpHdl      Handle for the NCP containing the EIOA switch.
 *  @param[in]  vlanId      The VLAN ID to retrieve the map for.
 *  @param[out] policerId   A pointer to a variable where the ID of the
 *                          policer that is mapped will be placed.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_SWITCH_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_POLICER_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_VLAN_ID_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_MODE_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_ENTRY_DISABLED
 */
NCP_API ncp_st_t
ncp_eioa_switch_policer_vlan_get(ncp_hdl_t ncpHdl,
                                 ncp_uint32_t vlanId,
                                 ncp_uint32_t *policerId);


/*!
 *  @brief  Set an EIOA ACL to policer mapping.
 *
 *  @param[in]  ncpHdl      Handle for the NCP containing the EIOA switch.
 *  @param[in]  aclId       The ACL ID that will be mapped.
 *  @param[in]  cos         The CoS value that will be mapped.
 *  @param[in]  policerId   The policer ID that the ACL ID/Cos will be
 *                          mapped to.
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_SWITCH_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_POLICER_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_ID_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_ACL_ID_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_COS_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_MODE_INVALID
 */
NCP_API ncp_st_t
ncp_eioa_switch_policer_acl_cos_set(ncp_hdl_t ncpHdl,
                                    ncp_uint32_t aclId,
                                    ncp_uint8_t  cos,
                                    ncp_uint32_t policerId);


/*!
 *  @brief  Get an EIOA ACL to policer mapping.
 *
 *  @param[in]  ncpHdl      Handle for the NCP containing the EIOA switch.
 *  @param[in]  aclId       The ACL ID to retrieve the map for.
 *  @param[in]  cos         The CoS value to retrieve the map for.
 *  @param[out] policerId   A pointer to a variable where the ID of the
 *                          policer that is mapped to the specified ACL ID/CoS
 *                          will be placed.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_EIOA_SWITCH_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_POLICER_HANDLE_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_ACL_ID_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_COS_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_POLICER_MODE_INVALID
 *      \li ::NCP_ST_EIOA_SWITCH_ENTRY_DISABLED
 */
NCP_API ncp_st_t
ncp_eioa_switch_policer_acl_cos_get(ncp_hdl_t ncpHdl,
                                    ncp_uint32_t aclId,
                                    ncp_uint8_t  cos,
                                    ncp_uint32_t *policerId);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _NCP_EIOA_POLICING_H_ */

