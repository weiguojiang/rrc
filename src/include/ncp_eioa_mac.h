/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


/*! @file      ncp_eioa_mac.h
 *  @brief     EIOA MAC
 *
 *             EIOA Mac APIs, defines and structure definitions.
 *
 *  @defgroup _eioa_mac_ EIOA MAC
 *  @ingroup _eioa_port_
 *
 *  @{
 */

#ifndef _NCP_EIOA_MAC_H_
#define _NCP_EIOA_MAC_H_

#ifdef __cplusplus
extern "C" {
#endif


/* Public Definitions */

/* Public Enumerated Types */

/*!
 * @brief EIOA .
 */

/********************** 
 * Public Structures  *
 **********************/

/*!
 * @brief EIOA Unicast MAC Adress Filtering information
 * @details
 * <pre>
 * addr_1             Unicast filter MAC address 1 - pointer to an array of 6 8-bit elements
 * addr_2             Unicast filter MAC address 2 - pointer to an array of 6 8-bit elements
 * addr_3             Unicast filter MAC address 3 - pointer to an array of 6 8-bit elements
 * addr_2_mask        Unicast filter MAC address 2 bitmask - pointer to an array of 6 8-bit elements
 * filter_enable      Unicast filtering enable-disable bit
 * sa_filter_enable   Unicast MAC address 3 Source Address enable-disable filter
 *</pre>
 */

typedef struct ncp_dev_unicast_addr_s {
  ncp_uint8_t *addr_1;
  ncp_uint8_t *addr_2;
  ncp_uint8_t *addr_3;
  ncp_uint8_t *addr_2_mask;
  ncp_bool_t  filter_enable;
  ncp_bool_t  sa_filter_enable;
} ncp_dev_unicast_addr_t;

/******************* 
 * Published APIs  *
 *******************/

/*!
 * @brief  Enable or Disable broadcast address filtering for this EIOA/Channel
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] broadcast_filter The boolean value of the filter flag.
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         </ul>
 */

NCP_API ncp_st_t 
ncp_eioa_broadcast_filter_set(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_bool_t broadcast_filter);


/*!
 * @brief  Retrieve the broadcast address filtering value for this EIOA/Channel.
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] broadcast_filter Pointer to an instance of ncp_bool_t, to place
              value of the broadcast_filter flag.
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         </ul>
 */

NCP_API ncp_st_t 
ncp_eioa_broadcast_filter_get(
    ncp_hdl_t     hdl,
    ncp_macChan_t macChan,
    ncp_bool_t *broadcast_filter);

/*!
 * @brief  Set the Unicast MAC address 1,2 and 3, MAC address 2 mask, 
 * MAC address 3 SA filtering and MAC address filtering for the given port.
 * @details
 * The EIOA shall support 3 48bit Unicast destination addresses per GMAC 
 * and XGMAC port.
 * When enabled, packets matching the programmed addresses are accepted, and
 * all other Unicast packets are discarded. <br> Pointers to all three Unicast
 * address variables need to be valid. if the pointers are set to NULL, the 
 * update does not take place and that MAC address filtering will be left as it was.
 * To disable the filtering the MAC addresses have to be set to 0.
 * there is also a MAC address 2 bit mask that is 48 bits.  This mask specifies which
 * bits of the Unicast Address 2 are don't care bits when those bits are set to 1.  
 * If this filed is set to NULL, it will not be updated.
 * It shall support a one bit Unicast SA MAC Address 3 filter enable/disable. This is 
 * achieved by setting sa_filter_enable field of ncp_dev_unicast_addr_t to TRUE or FALSE. 
 * Once this field is enabled, the Source Address on MAC address 3 is filtered instead
 * of Destination MAC Address. 
 * It also enables or disables the MAC Address filtering if the filter_enable field of 
 * ncp_dev_unicast_addr_t is set to TRUE or FALSE respectively. 
 *
 * Also see #ncp_eioa_unicast_filter_set().
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] *unicast_addr_info Pointerto an instance of ncp_dev_unicast_addr_t, to hold
 *             the unicast address filtering information.
 * @return <ul> 
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_DEV_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_INCOMPATIBLE_TARGET_DEVICE_REVISION
 *         </ul> 
 */

NCP_API ncp_st_t
ncp_eioa_unicast_mac_addr_set(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_dev_unicast_addr_t *unicast_addr_info);

/*!
 * @brief  Retrieve the Unicast MAC address 1,2 and 3, MAC address 2 mask, 
 * SA filtering and MAC address filtering for the given port.
 * @details 
 * Retrieve the Unicast MAC address 1,2 and 3, MAC address 2 mask, 
 * Source Address filtering and MAC address filtering for the given port.
 *
 * Note:  User must allocate the required space for the structure members that 
 * are needed in ncp_dev_unicast_addr_t.
 *
 * Also see #ncp_eioa_unicast_filter_get().
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *unicast_addr_info Pointer to and instance of ncp_dev_unicast_addr_t, 
 *              to place the unicast address filtering information.
 *
 * @return <ul>
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_INVALID_HANDLE
 *         <li> #NCP_ST_DEV_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_INCOMPATIBLE_TARGET_DEVICE_REVISION
 *         </ul>
 */

NCP_API ncp_st_t
ncp_eioa_unicast_mac_addr_get(
             ncp_hdl_t     hdl,
             ncp_macChan_t macChan,
             ncp_dev_unicast_addr_t *unicast_addr_info);


#ifdef __cplusplus
}
#endif

#endif /* #ifndef _NCP_EIOA_MAC_H_ */

