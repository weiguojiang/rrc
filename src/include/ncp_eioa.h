/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


/*! @file      ncp_eioa.h
 *  @brief     Ethernet I/O Adapter
 * 
 *  @addtogroup _eioa_ Ethernet I/O Adapter
 *
 *  @{
 */


#ifndef _NCP_EIOA_H_
#define _NCP_EIOA_H_

#include "ncp_types.h"
#include "ncp_nrcp.h"
#include "ncp_bitmap.h"

#if 0
#undef NCP_EIOA_PORT_AN_TRACE
#define NCP_EIOA_PORT_AN_TRACE
#endif

#if defined(NCP_EIOA_PORT_AN_TRACE)

#include "ncp_port_trace.h"

#endif

#ifdef __cplusplus
extern "C" {
#endif


/*********************************/
/* API Typedefs, Constants, etc. */
/*********************************/
#define TX_STAT_CNT 27
#define RX_STAT_CNT 28

/*!
 * @ingroup _eioa_
 * @struct ncp_mac_rxstat_t
 * @brief Receive statistics counter definition
 * @details
 * <pre>
 * Counter Name           Description 
 * ------- ----------     ----------- 
 *       0 rx_octets      Each received frame, good and bad, increments
 *                        RX_OCTETS by the frame length, up to maxFrmSize bytes
 *       1 rx_bad_octets  Each bad received frame increments RX_BAD_OCTETS by
 *                        the frame length, up to maxFrmSize bytes
 *       2 rx_frm         Each received frame, good and bad, increments RX_FRM
 *                        by 1.
 *       3 rx_bad_frm     Each bad received frame increments RX_BAD_FRM by 1.
 *       4 rx_mcast       Each good frame identified as directed to a multicast
 *                        address increments RX_MCAST by 1
 *       5 rx_bcast       Each good frame identified as directed to the
 *                        broadcast address increments RX_BCAST by 1
 *       6 rx_ctl         Each good frame identified as a control frame (either
 *                        PAUSE or unsupported) increments RX_CTL by 1
 *       7 rx_pause       Each good frame identified as a PAUSE control frame
 *                        increments RX_PAUSE by 1
 *       8 rx_unk_op      Each good control frame not identified as a PAUSE
 *                        increments RX_UNK_OP by 1
 *       9 rx_fcs         Each received frame with an errored CRC, excluding
 *                        frames flagged as RX_ALIGN, increments RX_FCS by 1
 *      10 rx_align       Each received frame with a length in [ 64 .. 1518 ]
 *                        but with a non-integral number of bytes increments
 *                        RX_ALIGN by 1.
 *      11 rx_length      Each received frame with a bad length, excluding
 *                        frames flagged as RX_FCS, RX_ALIGN, RX_USIZE,
 *                        RX_CODE, or RX_CARRIER, increments RX_LENGTH by 1.
 *      12 rx_code        Incremented by 1 when a bad code is detected
 *      13 rx_frag        Each received frame with a bad CRC, less than 64
 *                        octets in length, increments RX_FRAG by 1
 *      14 rx_usize       Each good received frame, less than 64 octets in
 *                        length, increments RX_USIZE by 1
 *      15 rx_64          Each received frame, good and bad, 64 octets in
 *                        length, increments RX_64 by 1
 *      16 rx_65          Each received frame, good and bad, [ 65 .. 127 ]
 *                        octets in length, increments RX_65 by 1
 *      17 rx_128         Each received frame, good and bad, [ 128 .. 255 ]
 *                        octets in length, increments RX_128 by 1
 *      18 rx_256         Each received frame, good and bad, [ 256 .. 511 ]
 *                        octets in length, increments RX_256 by 1
 *      19 rx_512         Each received frame, good and bad, [ 512 .. 1023 ]
 *                        octets in length, increments RX_512 by 1
 *      20 rx_1024        Each received frame, good and bad, [ 1024 .. 1518 ]
 *                        octets in length, increments RX_1024 by 1
 *      21 rx_1519        Each received frame, good and bad, [ 1024 .. maxFr ]
 *                        octets in length, increments RX_1519 by 1
 *      22 rx_osize       Each received frame with a good CRC, greater than
 *                        maxFrmSize octets in length, increments RX_OSIZE by 1
 *      23 rx_jab         Each received frame with a bad CRC, greater than
 *                        maxFrmSize octets in length, increments RX_JAB by 1
 *      24 rx_drop        Each good received frame that is filtered by the MAC
 *                        (excluding PAUSE frames) increments RX_DROP by 1
 *      25 rx_carrier     Incremented each time a false carrier is detected
 *                        during idle, as defined by a 1 on RX_ER and an '0xE'
 *                        on RXD. The event is reported along with the
 *                        statistics generated on the next received frame
 *      26 rx_orun        (Historical ... always 0)
 *      27 rx_stat_ovfl   Any non-zero value indicates a too-low CLK frequency
 *                        relative to the received data rate
 * </pre>
 *
 */

typedef struct ncp_mac_rxstat_s
{
    ncp_bdata_t rx_octets;
    ncp_bdata_t rx_bad_octets;
    ncp_bdata_t rx_frm;
    ncp_bdata_t rx_bad_frm;
    ncp_bdata_t rx_mcast;
    ncp_bdata_t rx_bcast;
    ncp_bdata_t rx_ctl;
    ncp_bdata_t rx_pause;
    ncp_bdata_t rx_unk_op;
    ncp_bdata_t rx_fcs;
    ncp_bdata_t rx_align;
    ncp_bdata_t rx_length;
    ncp_bdata_t rx_code;  
    ncp_bdata_t rx_frag;  
    ncp_bdata_t rx_usize;  
    ncp_bdata_t rx_64;    
    ncp_bdata_t rx_65;    
    ncp_bdata_t rx_128;   
    ncp_bdata_t rx_256;   
    ncp_bdata_t rx_512;   
    ncp_bdata_t rx_1024;   
    ncp_bdata_t rx_1519;   
    ncp_bdata_t rx_osize;  
    ncp_bdata_t rx_jab;  
    ncp_bdata_t rx_drop;  
    ncp_bdata_t rx_carrier;
    ncp_bdata_t rx_urun;
    ncp_bdata_t rx_stat_ovfl;
} ncp_mac_rxstat_t;


/*!
 * @ingroup _eioa_
 * @struct ncp_mac_txstat_t
 * @brief Transmit statistics counter definition
 * @details
 * <pre>
 * Counter Name           Description
 * ------- ----------     -----------
 *       0 tx_octets      Each transmitted frame, good and bad, increments
 *                        TX_OCTETS by the frame length, up to maxFrmSize bytes
 *       1 tx_bad_octets  Each bad transmitted frame increments TX_BAD_OCTETS
 *                        by the frame length, up to maxFrmSize bytes
 *       2 tx_frm         Each transmitted frame, good and bad, increments
 *                        TX_FRM  by 1.
 *       3 tx_bad_frm     Each transmitted bad frame increments TX_BAD_FRM by 1.
 *       4 tx_mcast       Each good frame identified as directed to a multicast
 *                        address increments TX_MCAST by 1
 *       5 tx_bcast       Each good frame identified as directed to the
 *                        broadcast address increments TX_BCAST by 1
 *       6 tx_pause       Each good frame identified as a PAUSE control frame
 *                        increments TX_PAUSE by 1
 *       7 tx_fcs         Each transmitted frame with an errored CRC increments
 *                        TX_FCS by 1
 *       8 tx_defer       Each transmitted frame that is deferred on its first
 *                        transmission attempt increments TX_DEFER by 1.
 *                        Does not include frames involved in collision
 *       9 tx_xsdfr       Each transmit-aborted frame which is deferred for an
 *                        excessive period of time (3036 byte times) increments
 *                        TX_XSDFR by 1
 *      10 tx_1col        Each transmitted frame which experiences exactly one
 *                        collision during transmission increments TX_1COL by 1
 *      11 tx_mcol        Each transmitted frame which experiences 2-15
 *                        collisions (including late collisions) during
 *                        transmission increments TX_MCOL by 1
 *      12 tx_lcol        Each transmitted frame which experiences a late
 *                        collision during transmission increments TX_LCOL by 1
 *      13 tx_xscol       Each transmit-aborted frame which experiences > 15
 *                        collisions during transmission attempt increments
 *                        TX_XSCOL by 1
 *      14 tx_frag        Each transmitted frame with a bad CRC, less than 64
 *                        octets in length, increments TX_FRAG by 1
 *      15 tx_usize       Each good transmitted frame, less than 64 octets in
 *                        length, increments TX_USIZE by 1
 *      16 tx_64          Each transmitted frame, good and bad, 64 octets in
 *                        length, increments RX_64 by 1
 *      17 tx_65          Each transmitted frame, good and bad, [ 65 .. 127 ]
 *                        octets in length, increments TX_65 by 1
 *      18 tx_128         Each transmitted frame, good and bad, [ 128 .. 255 ]
 *                        octets in length, increments TX_128 by 1
 *      19 tx_256         Each transmitted frame, good and bad, [ 256 .. 511 ]
 *                        octets in length, increments TX_256 by 1
 *      20 tx_512         Each transmitted frame, good and bad, [ 512 .. 1023 ]
 *                        octets in length, increments TX_512 by 1
 *      21 tx_1024        Each transmitted frame, good and bad, [ 1024 .. 1518]
 *                        octets in length, increments TX_1024 by 1
 *      22 tx_1519        Each transmitted frame, good and bad, [1519 .. maxFm]
 *                        octets in length, increments TX_1519 by 1
 *      23 tx_osize       Each transmitted frame with a good CRC, greater than
 *                        maxFrmSize octets in length, increments TX_OSIZE by 1
 *      24 tx_jab         Each transmitted frame with a bad CRC, greater than
 *                        maxFrmSize octets in length, increments TX_JAB by 1
 *      25 tx_urun        Incremented when the MAC FIFO underruns during
 *                        transmission, causing transmit-abort
 *      26 tx_stat_ovfl   Any non-zero value indicates a too-low CLK frequency
 *                        relative to the transmitted data rate
 * </pre>
 */

typedef struct ncp_mac_txstat_s
{
    ncp_bdata_t tx_octets;
    ncp_bdata_t tx_bad_octets;
    ncp_bdata_t tx_frm;
    ncp_bdata_t tx_bad_frm;
    ncp_bdata_t tx_mcast;
    ncp_bdata_t tx_bcast;
    ncp_bdata_t tx_pause;
    ncp_bdata_t tx_fcs;
    ncp_bdata_t tx_defer;
    ncp_bdata_t tx_xsdfr; 
    ncp_bdata_t tx_1col;
    ncp_bdata_t tx_mcol; 
    ncp_bdata_t tx_lcol;  
    ncp_bdata_t tx_xscol;  
    ncp_bdata_t tx_frag;
    ncp_bdata_t tx_usize;
    ncp_bdata_t tx_64;  
    ncp_bdata_t tx_65;
    ncp_bdata_t tx_128;
    ncp_bdata_t tx_256;
    ncp_bdata_t tx_512;
    ncp_bdata_t tx_1024;
    ncp_bdata_t tx_1519;
    ncp_bdata_t tx_osize;
    ncp_bdata_t tx_jab; 
    ncp_bdata_t tx_urun;
    ncp_bdata_t tx_stat_ovfl;
} ncp_mac_txstat_t;

/*
 * Clause 73 AN Advt Lo Register
 * and
 * Clause 73 AN LP Base Page Lo Register
 */

typedef struct ncp_mac_c73_an_advt_lo_s {
#ifdef NCP_BIG_ENDIAN
    unsigned ability_rsvd           :8;
    unsigned ability_10gkr          :1;
    unsigned ability_10gkx4         :1;
    unsigned ability_1gkx           :1;
    unsigned tx_nonce               :5;
    unsigned next_page              :1;
    unsigned ack                    :1;
    unsigned rem_fault              :1;
    unsigned pause                  :3;
    unsigned rx_nonce               :5;
    unsigned selector               :5;
#else
    unsigned selector               :5;
    unsigned rx_nonce               :5;
    unsigned pause                  :3;
    unsigned rem_fault              :1;
    unsigned ack                    :1;
    unsigned next_page              :1;
    unsigned tx_nonce               :5;
    unsigned ability_1gkx           :1;
    unsigned ability_10gkx4         :1;
    unsigned ability_10gkr          :1;
    unsigned ability_rsvd           :8;
#endif
} ncp_mac_c73_an_advt_lo_t;

/*
 * Clause 73 AN Advt Hi Register
 * and
 * Clause 73 AN LP Base Page Hi Register
 */
typedef struct ncp_mac_c73_an_advt_hi_s {
#ifdef NCP_BIG_ENDIAN
    unsigned rsvd               :16;
    unsigned fec_request        :1;
    unsigned fec_ability        :1;
    unsigned ability_rsvd       :14;
#else
    unsigned ability_rsvd       :14;
    unsigned fec_ability        :1;
    unsigned fec_request        :1;
    unsigned rsvd               :16;
#endif
} ncp_mac_c73_an_advt_hi_t;

/*
 * Clause 73 AN Next Page Lo Register
 * and
 * Clause 73 AN LP Next Page Lo Register
 */
typedef struct ncp_mac_c73_an_next_page_lo_s {
#ifdef NCP_BIG_ENDIAN
    unsigned unformat_code1         :16;
    unsigned next_page              :1;
    unsigned ack                    :1;
    unsigned msg_page               :1;
    unsigned ack2                   :1;
    unsigned toggle                 :1;
    unsigned msg_unformat_code      :11;
#else
    unsigned msg_unformat_code      :11;
    unsigned toggle                 :1;
    unsigned ack2                   :1;
    unsigned msg_page               :1;
    unsigned ack                    :1;
    unsigned next_page              :1;
    unsigned unformat_code1         :16;
#endif
} ncp_mac_c73_an_next_page_lo_t;

/*
 * Clause 73 AN Next Page Hi Register
 * and
 * Clause 73 AN LP Next Page Hi Register
 */

typedef struct ncp_mac_c73_an_next_page_hi_s {
#ifdef NCP_BIG_ENDIAN
    unsigned rsvd                   :16;
    unsigned unformat_code2         :16;
#else
    unsigned unformat_code2         :16;
    unsigned rsvd                   :16;
#endif
} ncp_mac_c73_an_next_page_hi_t;

#define NCP_PAUSE_RESPOND 0x01
#define NCP_PAUSE_FILTER 0x02
#define NCP_PAUSE_FORWARD 0x04
#define NCP_PAUSE_GENERATE 0x08
#define NCP_PAUSE_GENERATE_DROP_RX 0x10 

#define NCP_EIOA_WARM_RESTART 1
#define NCP_EIOA_NO_PHY_CONFIG 0x02

/*!
 * @enum ncp_eioa_pktsize_t
 * @brief Packet Size for EIOA ports.
 */
typedef enum{
    NCP_EIOA_PKTSIZE_10K = 0,
    NCP_EIOA_PKTSIZE_2K,
    NCP_EIOA_PKTSIZE_4K,
    NCP_EIOA_PKTSIZE_8K
} ncp_eioa_pktsize_t;

typedef enum {
    NCP_STATE_TX_DISABLE = 0,
    NCP_STATE_ABILITY_DETECT,
    NCP_STATE_ACK_DETECT,
    NCP_STATE_CMPL_ACK,
    NCP_STATE_NEXT_PAGE_WAIT,
    NCP_STATE_AN_GOOD_CHECK,
    NCP_STATE_AN_GOOD,
    NCP_STATE_AN_ENABLE,
    NCP_STATE_LINK_STATUS_CHECK,
    NCP_STATE_PDET_FAULT
}ncp_an_minor_state_t;

typedef enum {
    NCP_AN_FORCED = 0,
    NCP_AN_C73_LSI,
    NCP_AN_C73_IEEE,
    NCP_AN_PARALLEL_DETECT_2_5G,
    NCP_AN_PARALLEL_DETECT_1G,
    NCP_AN_C37,
    NCP_AN_PARALLEL_DETECT_10G,
    NCP_AN_PARALLEL_DETECT_10GKR
}ncp_an_major_state_t;

typedef enum {
    NCP_SW_C73_AN_START = 0,
    NCP_SW_C73_AN_DISABLED,
    NCP_SW_C73_AN_PAGE_RECIEVED,
    NCP_SW_C73_AN_PRI_RES_PAR_DETECT,
    NCP_SW_C73_AN_DME_COMPLETE,
    NCP_SW_C73_AN_PRI_RES_DME,
    NCP_SW_C73_AN_PAR_DETECT_COMPLETE
}ncp_an_sw_state_t;

/*!
 * @enum ncp_chanType_t
 * @brief A designated channel type for each port
 */
 typedef enum ncp_chanType_s {
    NCP_MAC_CHAN_CONFIG_NONE,
    NCP_MAC_CHAN_CONFIG_CUSTOM,
    NCP_MAC_CHAN_CONFIG_PMA,
    NCP_MAC_CHAN_CONFIG_GMII,
    NCP_MAC_CHAN_CONFIG_SMII,
    NCP_MAC_CHAN_CONFIG_SGMII,
    NCP_MAC_CHAN_CONFIG_QSGMII,
    NCP_MAC_CHAN_CONFIG_I2C,
    NCP_MAC_CHAN_CONFIG_XAUI,
    NCP_MAC_CHAN_CONFIG_XGMII,
    NCP_MAC_CHAN_CONFIG_XFI,
    NCP_MAC_CHAN_CONFIG_SFI,
    NCP_MAC_CHAN_CONFIG_10GBASEKR
} ncp_chanType_t;


/*!
 * @enum ncp_timestamp_resolution_t
 * @brief Eioa Timestamp Resolution setting 
 */

typedef enum {
    NCP_NUEVO_TIME_256 = 0,
    NCP_NUEVO_TIME_1024 = 1
} ncp_timestamp_resolution_t;

/*!
 * @enum ncp_mac_speed_t
 * @brief Port Speed definitions for the MAC
 */

typedef enum {
    NCP_MAC_PHY_SPEED10 = 1,
    NCP_MAC_PHY_SPEED100,
    NCP_MAC_PHY_SPEED1000,
    NCP_MAC_PHY_SPEED2_5G,
    NCP_MAC_PHY_SPEED10G
} ncp_mac_speed_t;

typedef enum {
    NCP_PHY_SPEED10 = 0,
    NCP_PHY_SPEED100,
    NCP_PHY_SPEED1000,
    NCP_PHY_SPEED10000
} ncp_phy_speed_t;

/*!
 * @enum ncp_eioa_slot_t
 * @brief Slot definitions for NCP EIOA's.
 */
typedef enum {
    NCP_EIOA_SLOT0,     /* EIOA - Slot 0 */
    NCP_EIOA_SLOT1      /* EIOA - Slot 1 */
} ncp_eioa_slot_t; 

/*!
 * @enum ncp_eioa_num_t
 * @brief Definitions for NCP EIOA's.
 */
typedef enum {
    NCP_EIOA0,     /* EIOA 0 */
    NCP_EIOA1,     /* EIOA 1 */
    NCP_EIOA2,     /* EIOA 2 */
    NCP_EIOA3,     /* EIOA 3 */
    NCP_EIOA4,     /* EIOA 4 */
    NCP_EIOA5,     /* EIOA 5 */
    NCP_EIOA6,     /* EIOA 6 */
    NCP_EIOA7,     /* EIOA 7 */
} ncp_eioa_num_t; 


/*!
 * @enum ncp_macChan_t
 * @brief Port definitions for NCP EIOA's.
 * @details
 * <ul>
 *   <li><b>EIOA 0 Port Names</b>
 *     <ul>
 *        <li><b>NCP_XGMAC0</b>  
 *            <br> Supported for <I>ACP344x</I> and <I>ACP342x</I> devices. 
 *            <br> Supported for <I>AXX2500</I> family of devices. 
 *            <br> Supported for <I>AXX5500</I> family of devices.  
 *        <li><b>NCP_GMAC0</b>  
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_XGMAC1</b>  
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *            <br> Supported for <I>AXX3500</I> family of devices. 
 *        <li><b>NCP_GMAC1</b> 
 *            <br> Supported for <I>ACP344x</I> and <I>ACP342x</I> devices. 
 *            <br> Supported for <I>AXX2500</I> family of devices.
 *            <br> Supported for <I>AXX5500</I> family of devices.  
 *            <br> Supported for <I>AXX3500</I> family of devices. 
 *        <li><b>NCP_GMAC2</b>  
 *            <br> Supported for <I>ACP344x</I> and <I>ACP342x</I> devices.
 *            <br> Supported for <I>AXX2500</I> family of devices.
 *            <br> Supported for <I>AXX5500</I> family of devices.  
 *            <br> Supported for <I>AXX3500</I> family of devices. 
 *        <li><b>NCP_GMAC3</b> 
 *            <br> Supported for <I>ACP344x</I> and <I>ACP342x</I> devices. 
 *            <br> Supported for <I>AXX2500</I> family of devices.
 *            <br> Supported for <I>AXX5500</I> family of devices. 
 *            <br> Supported for <I>AXX3500</I> family of devices.  
 *        <li><b>NCP_GMAC4</b>  
 *            <br> Supported for <I>ACP344x</I> and <I>ACP342x</I> devices.
 *            <br> Supported for <I>AXX2500</I> family of devices.
 *            <br> Supported for <I>AXX5500</I> family of devices. 
 *            <br> Supported for <I>AXX3500</I> family of devices.  
 *     </ul>
 *   <li><b>EIOA 1 Port Names</b>  
 *     <ul>
 *        <li><b>NCP_XGMAC8</b> 
 *            <br> Supported for <I>ACP344x</I> devices. 
 *            <br> Supported for <I>AXX2500</I> family of devices. 
 *        <li><b>NCP_XGMAC9</b> 
 *            <br> Supported for <I>AXX3500</I> family of devices. 
 *        <li><b>NCP_GMAC9</b> 
 *            <br> Supported for <I>ACP344x</I> and <I>ACP342x</I> devices.
 *            <br> Supported for <I>AXX2500</I> family of devices. 
 *            <br> Supported for <I>AXX3500</I> family of devices. 
 *        <li><b>NCP_GMAC10</b> 
 *            <br> Supported for <I>ACP344x</I> and <I>ACP342x</I> devices.
 *            <br> Supported for <I>AXX2500</I> family of devices.
 *            <br> Supported for <I>AXX3500</I> family of devices. 
 *        <li><b>NCP_GMAC11</b> 
 *            <br> Supported for <I>ACP344x</I> and <I>ACP342x</I> devices.
 *            <br> Supported for <I>AXX2500</I> family of devices. 
 *            <br> Supported for <I>AXX3500</I> family of devices. 
 *        <li><b>NCP_GMAC12</b> 
 *            <br> Supported for <I>ACP344x</I> and <I>ACP342x</I> devices.
 *            <br> Supported for <I>AXX2500</I> family of devices. 
 *            <br> Supported for <I>AXX3500</I> family of devices. 
 *        <li><b>NCP_XGMAC16</b> 
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_GMAC16</b> 
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_XGMAC17</b> 
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_GMAC17</b> 
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_GMAC18</b> 
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_GMAC19</b> 
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_GMAC20</b> 
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *     </ul>
 *   <li><b>EIOA 2 Port Names</b>  
 *     <ul>
 *        <li><b>NCP_XGMAC32</b> 
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_GMAC32</b>
 *            <br>  Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_XGMAC33</b> 
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_GMAC33</b>
 *            <br>  Supported for <I>AXX5500</I> family of devices.
 *     </ul>
 *   <li><b>EIOA 3 Port Names</b>  
 *     <ul>
 *        <li><b>NCP_XGMAC48</b> 
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_GMAC48</b> 
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_XGMAC49</b> 
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_GMAC49</b>
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *     </ul>
 *   <li><b>EIOA 4 Port Names</b>  
 *     <ul>
 *        <li><b>NCP_XGMAC64</b>
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_GMAC64</b>  
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_XGMAC65</b>  
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_GMAC65</b>  
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *     </ul>
 *   <li><b>EIOA 5 Port Names</b>  
 *     <ul>
 *        <li><b>NCP_XGMAC80</b>  
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_GMAC80</b>  
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_XGMAC81</b>  
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_GMAC81</b>  
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *     </ul>
 *   <li><b>EIOA 6 Port Names</b>  
 *     <ul>
 *        <li><b>NCP_XGMAC96</b>  
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_GMAC96</b>  
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_XGMAC97</b>  
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_GMAC97</b>  
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *     </ul>
 *   <li><b>EIOA 7 Port Names</b>  
 *     <ul>
 *        <li><b>NCP_XGMAC112</b>  
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_GMAC112</b>  
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_XGMAC113</b>  
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *        <li><b>NCP_GMAC113</b>  
 *            <br> Supported for <I>AXX5500</I> family of devices.
 *     </ul>
 * </ul>
 */
 
typedef enum {
    NCP_XGMAC0 = 0,      /* E0 - S0 - P0 */
    NCP_GMAC0 = 0,       /* E0, S0, P0 = 55xx  */
    NCP_XGMAC1 = 1,      /* E0 - S1 - P0 != 55xx | E0, S0, P0 = X3 */
    NCP_GMAC1 = 1,       /* E0 - S1 - P0 != 55xx | E0, S0, P0 = X3 */
    NCP_GMAC2 = 2,       /* E0 - S1 - P1 != 55xx | E0, S0, P1 = X3 */
    NCP_GMAC3 = 3,       /* E0 - S1 - P2 != 55xx | E0, S0, P2 = X3 */
    NCP_GMAC4 = 4,       /* E0, S1, P3 != 55xx | E0, S1, P0 = 55xx | E0, S0, P3 =X3 */
    NCP_XGMAC8 = 5,      /* EIOA 1 - Slot 0 - Port 0  != 55xx | E0, S1,P0 =X3 */
    NCP_XGMAC9 = 6,      /* EIOA 1 - Slot 1 - Port 0  != 55xx | E0, S1, P0 = X3 */
    NCP_GMAC9 = 6,       /* EIOA 1 - Slot 1 - Port 0  != 55xx | E0, S1, P0 = X3 */
    NCP_GMAC10 = 7,      /* EIOA 1 - Slot 1 - Port 1  != 55xx | E0, S1, P1 = X3 */
    NCP_GMAC11 = 8,      /* EIOA 1 - Slot 1 - Port 2  != 55xx | E0, S1, P2 = X3 */
    NCP_GMAC12 = 9,      /* EIOA 1 - Slot 1 - Port 3  != 55xx | E0, S1, P3 = X3 */
    NCP_XGMAC16 = 16,    /* E1, S0, P0 = 55xx */
    NCP_GMAC16= 16,      /* E1, S0, P0 = 55xx */
    NCP_XGMAC17= 17,     /* E1, S0, P0 = 55xx */
    NCP_GMAC17= 17,      /* E1, S0, P0 = 55xx */
    NCP_GMAC18= 18,      /* E1, S0, P0 = 55xx */
    NCP_GMAC19= 19,      /* E1, S0, P0 = 55xx */
    NCP_GMAC20= 20,      /* E1, S0, P0 = 55xx */
    NCP_XGMAC32 = 32,    /* E2, S0, P0 = 55xx */
    NCP_GMAC32 = 32,     /* E2, S0, P0 = 55xx */
    NCP_XGMAC33 = 33,    /* E2, S1, P0 = 55xx */
    NCP_GMAC33 = 33,     /* E2, S1, P0 = 55xx */
    NCP_XGMAC48 = 48,    /* E3, S0, P0 = 55xx */
    NCP_GMAC48 = 48,     /* E3, S0, P0 = 55xx */
    NCP_XGMAC49 = 49,    /* E3, S1, P0 = 55xx */
    NCP_GMAC49 = 49,     /* E3, S1, P0 = 55xx */
    NCP_XGMAC64 = 64,    /* E4, S0, P0 = 55xx */
    NCP_GMAC64 = 64,     /* E4, S0, P0 = 55xx */
    NCP_XGMAC65 = 65,    /* E4, S1, P0 = 55xx */
    NCP_GMAC65 = 65,     /* E4, S1, P0 = 55xx */
    NCP_XGMAC80 = 80,    /* E5, S0, P0 = 55xx */
    NCP_GMAC80 = 80,     /* E5, S0, P0 = 55xx */
    NCP_XGMAC81 = 81,    /* E5, S1, P0 = 55xx */
    NCP_GMAC81 = 81,     /* E5, S1, P0 = 55xx */
    NCP_XGMAC96 = 96,    /* E6, S0, P0 = 55xx */
    NCP_GMAC96 = 96,     /* E6, S0, P0 = 55xx */
    NCP_XGMAC97 = 97,    /* E6, S1, P0 = 55xx */
    NCP_GMAC97 = 97,     /* E6, S1, P0 = 55xx */
    NCP_XGMAC112 = 112,  /* E7, S0, P0 = 55xx */
    NCP_GMAC112 = 112,   /* E7, S0, P0 = 55xx */
    NCP_XGMAC113 = 113,  /* E7, S1, P0 = 55xx */
    NCP_GMAC113 = 113,   /* E7, S1, P0 = 55xx */
} ncp_macChan_t; 

#define NCP_EIOA_HANDLE_COOKIE 0x45494F41
#define EIOA_MCAST_HASH_TABLE_SIZE 128
#define MAX_NUM_EIOA_PORTS 8
#define MAX_NUM_EIOAS 8

typedef enum ncp_mdioType_e
{
    CLAUSE22 = 1,
    CLAUSE45
} ncp_mdioType_t;

typedef enum ncp_slotcfg_e
{
    S0_ONLY = 1,
    S1_ONLY = 4,
    S1_S2,
    S0_XFI,
    S0_XAUI
} ncp_slotcfg_t;

typedef enum ncp_portTimer_owner_e
{
    NCP_LINK_NONE,
    NCP_LINK_STATUS,
    NCP_LINK_STATE,
    NCP_LINK_SHARED
} ncp_portTimer_owner_t;

#define NCP_MAC_SELECTOR_IEEE 1
#define NCP_MAC_SELECTOR_LSI 4

/*
 * AN timer in ms.
 */
#define NCP_MAC_AN_TIMER 1000


/*!
 * @enum port_mask_t
 * @brief Link State Mask for phyStatus.
 */
 
typedef enum {
    NCP_PORT_PHY_AN_COMPLETE = 1,
    NCP_PORT_PHY_REMOTE_FAULT,
    NCP_PORT_PHY_DUPLEX = 4,
    NCP_PORT_PHY_SPEED = 0x18,
    NCP_PORT_PHY_LINK_STATUS = 0x20,
    NCP_PORT_PHY_CONFIGURED = 0x40
} port_mask_t;

/*!
 * @ingroup _eioa_port_
 * @enum ncp_port_burstSize_t
 * @brief The maximum burst size for the port shaper.
 */
typedef enum{
    SIZE_32_BYTES = 0,
    SIZE_64_BYTES,
    SIZE_128_BYTES,
    SIZE_256_BYTES,
    SIZE_512_BYTES,
    SIZE_1K_BYTES,
    SIZE_2K_BYTES,
    SIZE_4K_BYTES,
    SIZE_8K_BYTES,
    SIZE_16K_BYTES,
    SIZE_32K_BYTES,
    SIZE_64K_BYTES,
    SIZE_128K_BYTES,
    SIZE_256K_BYTES,
    SIZE_512K_BYTES,
    SIZE_1M_BYTES
} ncp_port_burstSize_t;

/*!
 * @enum ncp_loopback_mask_t
 * @breif Loopback Mask for ncp_eioa_chan_loopback_set
 */
typedef enum {
    NCP_MAC_LOOPBACK             = 1,
    NCP_SERDES_SERIAL_LOOPBACK   = 2,    /* ACP3400 ONLY                  */
    NCP_SERDES_INTERNAL_LOOPBACK = 2,  /* AXM5500 ONLY: EIOA->HSS->EIOA */
    NCP_SERDES_PARALLEL_LOOPBACK = 3,  /* ACP3400 ONLY                  */
    NCP_SERDES_EXTERNAL_LOOPBACK = 3   /* AXM5500 ONLY: HSS->EIOA->HSS  */
} ncp_loopback_t;

/*!
 * @enum ncp_vflow_priority_t
 * @brief priorities for ncp_eioa_port_get and ncp_eioa_port_set
 * NCP_EIOA_VFLOW_PRIORITY_UNKNOWN Unknown priority
 * NCP_EIOA_VFLOW_PRIORITY_KNOWN   Known priority (Vlan Tagged)
 */
typedef enum {
    NCP_EIOA_VFLOW_PRIORITY_UNKNOWN = 0,
    NCP_EIOA_VFLOW_PRIORITY_KNOWN   = 1
} ncp_vflow_priority_t;

/*
 * These flags are used for vflow priority
 */
#define NCP_EIOA_VFLOW_PRIORITY_MIN     0
#define NCP_EIOA_VFLOW_PRIORITY_MAX     7

/*!
 * @ingroup _eioa_port_
 * @struct ncp_eioa_port_vp_info_t
 * @breif Parameters for vflow priority and 
 * vflow unknown priority on AXM25xx and 
 * AXM55xx
 */
typedef struct {
    ncp_uint8_t vlanPriorities[8];
    ncp_uint8_t nonVlanPriority;
    ncp_bool_t  enableCcmDiscard;        /* Valid only for 55xx */
    ncp_bool_t  enableCcmBpDeiDiscard;   /* Valid only for 55xx */
    ncp_bool_t  enableCcmBpDscpDiscard;  /* Valid only for 55xx */
} NCP_COMPAT_PACKED ncp_eioa_port_vp_info_t;

/*!
 * @ingroup _eioa_port_
 * @struct ncp_port_shaper_options_t
 * @brief Paramters for the Egress port Shaper on
 * AXM35xx, and AXM55xx platforms.<br>
 * <b>enableShaping</b> Enable TRUE/FALSE for EIOA Port Shaping functionality <br>
 * <b>committedRate</b> Committed rate in bits-per-sec <br>
 * <b>maxBurstSize</b> See Enumeration <br>
 * <b>overheadBytes</b> Any overhead bytes for Shaper accounting purposes <br>
 * <b>shortIFG</b> Deprecated <br>
 * <b>minPktSize</b> Maximum packet size on the wire to shape to (example 1518 bytes)
 * (member name unchanged due to bin compat). Range is 64-10000 bytes <br>
 */

typedef struct ncp_port_shaper_options_s {
    ncp_bool_t enableShaping;
    ncp_int64_t committedRate;
    ncp_port_burstSize_t maxBurstSize;
    ncp_uint32_t overheadBytes;
    ncp_bool_t shortIFG;
    ncp_uint32_t minPktSize;
} NCP_COMPAT_PACKED ncp_port_shaper_options_t;

#define NUM_EIOA_25xx_PORT_SCH_QUEUES 4
#define NUM_EIOA_55xx_PORT_SCH_QUEUES 8 
#define NUM_EIOA_35xx_PORT_SCH_QUEUES 4 

/*!
 * @ingroup _eioa_port_
 * @struct ncp_port_scheduler_options_t
 * @brief Paramaters for the Egress port scheduler<br>
 * <b>queueId</b> Id number assigned to this queue<br>
 * <b>weight</b> Weight in bytes<br>
 * Strict Priority(SP) Weighted Deficit Round Robin (DRR)<br>
 * <b>mode</b> SP3 = 0; DRR = 1; SP1 = 2; SP2 = 3;<br>
 * <b>minPktSize</b> Readonly value typically 64 bytes<br>
 * <b>wp_priority</b> Also called priorityDRR
 */

typedef struct ncp_port_sheduler_options_s {
    ncp_uint32_t queueId[NUM_EIOA_55xx_PORT_SCH_QUEUES];
    ncp_uint32_t weight[NUM_EIOA_55xx_PORT_SCH_QUEUES];
    ncp_uint32_t mode[NUM_EIOA_55xx_PORT_SCH_QUEUES];
    ncp_port_burstSize_t maxBurstSize[NUM_EIOA_55xx_PORT_SCH_QUEUES];
    ncp_uint32_t overheadBytes;
    ncp_uint32_t minPktSize;
    ncp_bool_t shortIFG;
    ncp_uint32_t wp_priority;
    ncp_uint32_t sp1_weight;
    ncp_uint32_t sp1_mbs;
    ncp_uint32_t sp2_weight;
    ncp_uint32_t sp2_mbs;
} NCP_COMPAT_PACKED ncp_port_scheduler_options_t;

    /* Default MDIO is ncp_eioa_phy_reg_read() */
typedef ncp_st_t (*phyRegReadFunc_t)(
                        void* dev,
                        ncp_macChan_t macChan,
                        ncp_uint32_t reg,
                        ncp_uint32_t *data);

    /* Default MDIO is ncp_eioa_phy_reg_write() */
typedef ncp_st_t (*phyRegWriteFunc_t)(
                        void* dev,
                        ncp_macChan_t macChan,
                        ncp_uint32_t reg,
                        ncp_uint32_t data);

typedef ncp_st_t (*initFunc_t)(       /* Optional: Ptr to PHY init routine */
                        void *dev,
                        ncp_uint32_t macChan,
                        ncp_uint32_t flags);

typedef ncp_st_t (*getSpeedFunc_t)(       /* Optional: Ptr to phy getSpeed  */
                        void *dev,
                        ncp_uint32_t macChan,
                        ncp_phy_speed_t *speed,
                        ncp_uint32_t flags);

typedef ncp_st_t (*isrFunc_t)(         /* Optional: Ptr to PHY interrupt
                                          service routine */
                        void  *dev,
                        ncp_uint32_t macChan,
                        ncp_uint32_t macPort,
                        ncp_uint32_t intrStatusReg,
                        ncp_uint32_t flags);

typedef struct ncp_mac_phy_s {
    ncp_uint32_t    oui;               /* Organizationally Unique ID (Vendor) */
    ncp_uint32_t    model;             /* PHY's model number */
    ncp_uint32_t    revision;          /* PHY's revision number */
    NCP_DECLARE_POINTER(char const, description);      /* PHY's description */
    ncp_uint32_t    type;              /* PHY type(has to match chan config) */
    ncp_bool_t      cmpRevision;       /* compare PHY's revision number? */

    ncp_bool_t      intrSupport;       /* whether this PHY supports intr */
    ncp_uint32_t    intrEnableOffset;  /* offset to PHY intr enable mask reg */
    ncp_uint32_t    intrEnableMask;    /* bits that need to be wiggled  */
    ncp_uint32_t    intrEnableInitVal; /* value it needs to be set to */
    ncp_uint32_t    intrStatusOffset;  /* offset to PHY interrupt status reg */
    ncp_uint32_t    phy_flag_reserve[4];
    NCP_DECLARE_POINTER_ARRAY(void, phy_reserve, 4);


    /* Default MDIO is ncp_eioa_phy_reg_read() */
    NCP_DECLARE_FN_POINTER(phyRegReadFunc_t, phyRegReadFunc);

    /* Default MDIO is ncp_eioa_phy_reg_write() */
    NCP_DECLARE_FN_POINTER(phyRegWriteFunc_t, phyRegWriteFunc);

    NCP_DECLARE_FN_POINTER(initFunc_t, initFunc);

    NCP_DECLARE_FN_POINTER(getSpeedFunc_t, getSpeedFunc);

    NCP_DECLARE_FN_POINTER(isrFunc_t, isrFunc);

} NCP_COMPAT_PACKED ncp_mac_phy_t;

typedef struct ncp_mac_link_timer_info_s
{
    ncp_bool_t timerOn;
    ncp_bool_t callByInt;
    NCP_DECLARE_POINTER(void, dev);
    ncp_uint32_t iflags;
    ncp_uint32_t cflags;
    ncp_uint32_t mask;
    ncp_macChan_t macChan;
    ncp_portTimer_owner_t owner;
    ncp_uint32_t tm_set;
    ncp_uint32_t tm_count;
#if defined(NCP_KERNEL)
#if defined(NCP_LINUX)
    volatile struct timer_list *my_timer;
#endif
#if defined(NCP_OSE)
    volatile PROCESS my_timer;
#endif
#if defined(NCP_VXWORKS)
    ncp_uint8_t my_timer[0x18];
#endif
#else
    ncp_uint8_t my_timer[0x18];
#endif
} NCP_COMPAT_PACKED ncp_mac_link_timer_info_t;

typedef struct ncp_mac_base_page_s
{
/*
 *  ncp_gmac_nem_gmac_control_27_r_t lo;
 *  ncp_gmac_nem_gmac_control_28_r_t hi;
 *  ncp_uint32_t lo;
 *  ncp_uint32_t hi;
 */
    ncp_mac_c73_an_advt_lo_t      lo;
    ncp_mac_c73_an_advt_hi_t      hi;
} NCP_COMPAT_PACKED ncp_mac_base_page_t;

typedef struct ncp_mac_next_page_s
{
  /*
   *  ncp_gmac_nem_gmac_control_30_r_t lo;
   *  ncp_gmac_nem_gmac_control_31_r_t hi;
   * ncp_uint32_t lo;
   * ncp_uint32_t hi;
   */
    ncp_mac_c73_an_next_page_lo_t      lo;
    ncp_mac_c73_an_next_page_hi_t      hi;
} NCP_COMPAT_PACKED ncp_mac_next_page_t;

typedef enum {
    NCP_MAC_LINK_NONE = 0,
    NCP_MAC_LINK_1GKX,
    NCP_MAC_LINK_2_5GKX,
    NCP_MAC_LINK_10GKX4,
    NCP_MAC_LINK_10GKR
} ncp_sw_link_status_t;

#define NCP_MAC_MAX_NEXT_PAGE 10

typedef struct ncp_mac_state_info_s
{
    ncp_an_major_state_t       major_state;
    ncp_an_minor_state_t       minor_state;
    ncp_an_sw_state_t          sw_state;
    ncp_bool_t                 tryANAgain;
    ncp_uint32_t               prev_c37_an_status;
    ncp_uint32_t               prev_c73_an_hw_state;
    ncp_uint32_t               prev_c73_an_sw_state;
    ncp_uint32_t               nextPageIndx;
    ncp_mac_base_page_t        loc_base;
    ncp_mac_next_page_t        loc_next[NCP_MAC_MAX_NEXT_PAGE];
    ncp_mac_base_page_t        rem_base;
    ncp_mac_next_page_t        rem_next[NCP_MAC_MAX_NEXT_PAGE];
    NCP_DECLARE_POINTER(void, port_waitq);
    NCP_DECLARE_POINTER(ncp_mac_link_timer_info_t, link_timer);
    ncp_sw_link_status_t       sw_linkStatus;
} NCP_COMPAT_PACKED ncp_mac_state_info_t;

/*!
 * @ingroup _eioa_
 * @struct ncp_mac_phy_status_t
 * @brief EIOA Mac PHY definition
 */
typedef struct ncp_mac_phy_status_s {
    ncp_bool_t   configured;
    ncp_bool_t   linkStatus;
    ncp_phy_speed_t  speed;
    ncp_bool_t   duplex;
    ncp_bool_t   remoteFault;
    ncp_bool_t   autoNegDone;
} NCP_COMPAT_PACKED ncp_mac_phy_status_t;

/*!
 * @ingroup _eioa_port_
 * @enum ncp_macType_t
 * @brief The type of port for this part.
 */
typedef enum {
    NCP_XGMAC = 0,
    NCP_GMAC
} ncp_macType_t;

/*!
 * @ingroup _eioa_
 * @struct ncp_port_t
 * @brief EIOA port definition
 */
typedef struct ncp_port_s
{
    ncp_bool_t cfg_ok;
    ncp_bool_t isFiber;
    ncp_uint32_t phyAddr;
    ncp_bool_t enableAN;
    ncp_bool_t enableFEC;
    ncp_bool_t duplex;
    ncp_bool_t enable_ovr;
    ncp_mdioType_t mdioType;
    ncp_chanType_t chanType;
    ncp_mac_speed_t speed;
    ncp_mac_state_info_t state_info;
    ncp_mac_phy_status_t phyStatus;
    ncp_mac_phy_t phyType;
    ncp_bool_t rxPause;
    ncp_bool_t txPause;
    ncp_uint16_t xfi_sf_control;
    ncp_uint32_t port_flag_reserve[11];
    ncp_uint32_t port_state_cache; 
    ncp_chanType_t phyAccess;
#if defined(NCP_EIOA_PORT_AN_TRACE)
    NCP_DECLARE_POINTER_ARRAY(void, port_reserve, 13);
    void *port_trace;
#else
    NCP_DECLARE_POINTER_ARRAY(void, port_reserve, 14);
#endif
    NCP_DECLARE_POINTER(ncp_port_shaper_options_t, port_shaper);
    NCP_DECLARE_POINTER(ncp_port_scheduler_options_t, port_scheduler);
    ncp_macType_t macType;
    ncp_uint32_t portID;
    ncp_uint32_t mcast_index;
    NCP_DECLARE_POINTER(char, mcast_addr);
} NCP_COMPAT_PACKED ncp_port_t;


#include "ncp_eioa_hss_utils.h"

/*!
 * @ingroup _eioa_port_
 * @struct ncp_eioa_port_config_switchover_t
 * @brief EIOA port switchover definitions
 * For member <b>chanType</b>, this is the new setting the port will use<br>
 * <ul>
 * <li>For XGMAC to GMAC switchover, <b>chanType</b> is #NCP_MAC_CHAN_CONFIG_SGMII
 * <li>For GMAC to XGMAC switchover, <b>chanType</b> is #NCP_MAC_CHAN_CONFIG_SFI
 * </ul>
 * <br>For member <b>enableAutoNegotiation</b>, value must be <b>FALSE</b> <br>
 * For member <b>speed</b>, this is the speed of the new port setting<br>
 * <ul>
 * <li>For XGMAC to GMAC switchover, <b>speed</b> is #NCP_MAC_PHY_SPEED1000
 * <li>For GMAC to XGMAC switchover, <b>speed</b> is #NCP_MAC_PHY_SPEED10G
 * </ul>
 * <br>For member <b>duplex</b>, value must be <b>TRUE</b> <br>
 * For member <b>enableDicMode/b>, what ever value is required for new port settings <br>
 * For member <b>shaping</b>, port shaping values to support new port speed<br>
 * For member <b>scheduling</b>, port scheduling values to support new port speed<br>
 * For member <b>tx_coeff</b>, values to support the new port type. 
 */
typedef struct ncp_eioa_port_config_switchover_st
{
    ncp_chanType_t chanType;
    ncp_bool_t enableAutoNegotiation;
    ncp_mac_speed_t speed;
    ncp_bool_t duplex;
    ncp_bool_t enableDicMode;
    ncp_port_shaper_options_t *shaping;
    ncp_port_scheduler_options_t *scheduling;
    ncp_hss_tx_coeff_t *tx_coeff;
    ncp_bool_t fec_enable;
    ncp_bool_t fec_enable_err_ind;
} ncp_eioa_port_config_switchover_t;


typedef struct ncp_eioa_common_s
{
    ncp_bitmap_t    *protoIdxValid;
    ncp_bitmap_t    *etherTypeIdxValid;
    ncp_bitmap_t    *bridgingVpIdValid;
    ncp_bitmap_t    *vflowVpValid;
} ncp_eioa_common_t;

typedef struct ncp_eioa_port_vlan_map_st
{
    ncp_uint16_t cvlanId;
    ncp_uint16_t svlanId;
    ncp_bool_t o2oSvlan;
} NCP_COMPAT_PACKED ncp_eioa_port_vlan_map_t;

typedef struct ncp_eioa_port_vlan_map_info_v1_st
{
    NCP_DECLARE_POINTER(ncp_bitmap_t, usedSvlan);
    ncp_eioa_port_vlan_map_t vlanMap[256];
    ncp_int16_t origSvlanIndex;
    ncp_uint16_t numVlans;
} NCP_COMPAT_PACKED ncp_eioa_port_vlan_map_info_v1_t;

typedef struct ncp_eioa_port_vlan_info_st
{
    NCP_DECLARE_POINTER(ncp_bitmap_t, usedSvlan);
    NCP_DECLARE_POINTER(ncp_bitmap_t, o2oSvlan);
    ncp_uint16_t	layer_2_domain[4096]; /* 9-bits of layer 2 domain. applicable to 56xx only.*/
    ncp_bitmap_t *usedCvlan;
    ncp_uint16_t numVlans;
} NCP_COMPAT_PACKED ncp_eioa_port_vlan_info_t;

typedef struct ncp_eioa_vlan_info_st
{
    NCP_DECLARE_POINTER_ARRAY(ncp_eioa_port_vlan_map_info_v1_t,
                                portVlanMapV1,
                                MAX_NUM_EIOA_PORTS);
    NCP_DECLARE_POINTER_ARRAY(ncp_eioa_port_vlan_info_t,
                                portVlan,
                                MAX_NUM_EIOA_PORTS);
} NCP_COMPAT_PACKED ncp_eioa_vlan_info_t;

typedef struct ncp_eioa_vps_tid_s
{
    ncp_bool_t         valid;
    ncp_uint8_t        vpId;
    ncp_uint8_t        origNextTid;
    ncp_bool_t         enableNextTid;
    ncp_uint8_t        nextTid;
    ncp_uint8_t        outputFormat;
} NCP_COMPAT_PACKED ncp_eioa_vps_tid_t;

#define NCP_EIOA_VP_TEMPLATE_IDS_MAX 128
typedef struct ncp_eioa_s
{
    ncp_slotcfg_t slotcfg;
    NCP_DECLARE_POINTER_ARRAY(ncp_port_t, port, 2 * MAX_NUM_EIOA_PORTS + 1);
    ncp_bool_t gmacOvrClock2_5G;
    ncp_uint32_t ovrClockMap;
    ncp_uint32_t nTicksPerSecond;
    ncp_uint32_t minSyncSel;
    ncp_bool_t hssInit;
    ncp_bool_t disabled;
    ncp_eioa_vlan_info_t vlanInfo;
    ncp_eioa_vps_tid_t vpsTidInfo[NCP_EIOA_VP_TEMPLATE_IDS_MAX];  /* Used only for 55xx */
} NCP_COMPAT_PACKED ncp_eioa_t;

typedef struct ncp_eioas_s
{
    ncp_uint32_t        cookie;
    ncp_hdl_t           ncpHdl;
    ncp_sem_t           threadLock;
    ncp_bool_t          lockActive;
    ncp_uint32_t        nTicksPerSecond;
    ncp_uint32_t        minSyncSel;
    ncp_eioa_common_t   *eioaCommon;
    ncp_eioa_t          *eioa0;  /* Support for legacy */
    ncp_eioa_t          *eioa1;  /* Support for legacy */
    ncp_eioa_t          *eioa[MAX_NUM_EIOAS + 1];  /* New for 55xx */
    ncp_bool_t          apiActive;
    ncp_bool_t          noPhyConfig;  /* BZ: 42187 and 42192 */
    ncp_bool_t          legacyIDs;    /* Legacy VP Destination ids 35xx */
    ncp_nrcp_Config_t 	*nrcpHdl;
} ncp_eioas_t;

#ifndef NCP_KERNEL

#include "ncp_eioa_common.h"
#include "ncp_eioa_port.h"
#include "ncp_eioa_core.h"

#endif

/******************/
/* published APIs */
/******************/
#ifdef __cplusplus
}
#endif

#endif /* _NCP_EIOA_H_ */

/*
 *  @}
 */
