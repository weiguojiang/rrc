/*! @file      ncp_eioa_hss_utils.h
 *  @brief     EIOA HSS APIs
 *
 *             EIOA HSS APIs, defines and structure definitions.
 *
 *  @defgroup _eioa_hss_ EIOA HSS
 *  @ingroup _eioa_
 *
 *  @{
 */

#ifndef _NCP_EIOA_HSS_UTILS_H_
#define _NCP_EIOA_HSS_UTILS_H_
   
#ifdef __cplusplus
extern "C" {
#endif 
    

/* Public Definitions */
    
/****************** 
 * Data structures*
 ******************/

/*! 
 * @brief Serdes Synchronous Ethernet RefClock Select
 * @details
 * <pre>
 * NCP_SYNCE_CLK_EREF        Synchronous Ethernet RefClock select
 * NCP_SYNCE_CLK_EREFS       Synchronous Ethernet RefClock synchronous select (corrected clk from off chip)
 *</pre>
 */

typedef enum {
    NCP_SYNCE_CLK_EREF = 0,
    NCP_SYNCE_CLK_EREFS
} ncp_hss_synce_refclk_t;

/*! 
 * @brief Serdes Synchronous Ethernet Clock Control
 * @details
 * <pre>
 * NCP_SYNCE_CLOCK_0       Synchronous Ethernet Clock 0 Control
 * NCP_SYNCE_CLOCK_1       Synchronous Ethernet Clock 1 Control
 *</pre>
 */

typedef enum {
    NCP_SYNCE_CLOCK_0 = 0,
    NCP_SYNCE_CLOCK_1
} ncp_hss_synce_clkid_t;

/*! 
 * @brief EIOA Serdes TX Serdes coefficient  information
 * @details
 * <pre>
 * txSwingControl       Transmitter swing control.
 * txPostEmphasis       Transmitter post-emphasis control.
 * txPreEmphasis        Transmitter pre-emphasis control.
 *</pre>
 */

typedef struct ncp_hss_tx_coeff_s {
    ncp_uint8_t txSwingControl;
    ncp_uint8_t txPostEmphasis;
    ncp_uint8_t txPreEmphasis;
} ncp_hss_tx_coeff_t;

/*! 
 * @brief EIOA Serdes RX Serdes coefficient  information
 * @details
 * <pre>
 * finalCdrClockPhase   CdrPhase - Final CDR clock phase
 * finalAGCVlotage      AGCV - Final AGC voltage value
 * h0Voltage            H0_V - (TargetV) Target switching threshold voltage value
 * h1Voltage            H1_V - Final voltage used on the 1st DFE tap
 * h2Voltage            H1_V - Final voltage used on the 2st DFE tap
 * h3Voltage            H1_V - Final voltage used on the 3st DFE tap
 * h4Voltage            H1_V - Final voltage used on the 4st DFE tap
 * h5Voltage            H1_V - Final voltage used on the 5st DFE tap
 * h6Voltage            H1_V - Final voltage used on the 6st DFE tap
 *</pre>
 */

typedef struct ncp_hss_rx_coeff_s {
    ncp_uint8_t finalCdrClockPhase;
    ncp_uint8_t finalAGCVlotage;
    ncp_uint8_t h0Voltage;
    ncp_uint8_t h1Voltage;
    ncp_uint8_t h2Voltage;
    ncp_uint8_t h3Voltage;
    ncp_uint8_t h4Voltage;
    ncp_uint8_t h5Voltage;
    ncp_uint8_t h6Voltage;
} ncp_hss_rx_coeff_t;
 
/*! 
 * @brief EIOA Serdes PRBS information
 * @details
 * <pre>
 * txprbs_sel         TX prbs selection
 * rxprbs_sel         RX prbs selection
 * bertok_sel         0 = Selects bert_cmp_out. 1 = Selects bertok
 * ef_ber_mode        Selects EyeFinder mode: 
 *                        1 = Counter used for BERT test mode
 *                        0 = EyeScope mode
 * txbistena          1 = TX built-in self test (BIST) enable. 0 = User Data
 * bert_error_reset   Resets RX bert_error  - this resets ererrorcount
 * bertok             RX BIST OK.  Read Only.
 * eferrorcount       Error count.  Read Only
 *</pre>
 */

typedef struct ncp_hss_prbs_s {
    ncp_uint8_t  txprbs_sel;
    ncp_uint8_t  rxprbs_sel;
    ncp_uint8_t  bertok_sel;
    ncp_uint8_t  ef_ber_mode;
    ncp_uint8_t  txbistena;
    ncp_uint8_t  rxbistena;
    ncp_uint8_t  bert_error_reset;
    ncp_uint8_t  bertok;
    ncp_uint16_t eferrorcount;
} ncp_hss_prbs_t;
 
/*! 
 * @brief EIOA Serdes user defined data registers
 * @details 
 * <pre>
 * txdata_reg0        BERT transmit data register 0
 * txdata_reg1        BERT transmit data register 1
 * txdata_reg2        BERT transmit data register 2
 * txdata_reg3        BERT transmit data register 3
 *</pre>
 */

typedef struct ncp_hss_txdata_reg_s {
    ncp_uint16_t  txdata_reg0;
    ncp_uint16_t  txdata_reg1;
    ncp_uint16_t  txdata_reg2;
    ncp_uint16_t  txdata_reg3;
}  ncp_hss_txdata_reg_t;


/*!
 * @brief  Write to EIOA Serdes PRBS fields. 
 * @details This API writes the following fields in EIOA Serdes PRBS.
 * AXM5500 Only.
 *  1. txprbs_sel -             Serdes phy target>.node.0x2     (bits [4:2])
 *  2. rxprbs_sel -             Serdes phy target>110.node.0xa  (bits [2:0])
 *  3. bertok_sel -             Serdes phy target>110.node.0x20 (bit 14)
 *  4. ef_ber_mode -            Serdes phy target>110.node.0x98 (bit 15)
 *  5. txbistena -              Serdes phy target>110.node.0x0  (bit 7)
 *  6. bert_error_reset -       Serdes phy target>110.node.0x20 (bit 15)
 *                              Resets eferrorcount by toggling ber_error_reset


 * Also see #ncp_eioa_hss_lane_prbs_get().
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] hss_prbs, a pointer to an instance of ncp_hss_prbs_t, to hold
 *             the HSS PRBS information.
 * @return <ul> 
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_DEV_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_INCOMPATIBLE_TARGET_DEVICE_REVISION
 *         </ul> 
 */

ncp_st_t 
ncp_eioa_hss_lane_prbs_set(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_hss_prbs_t *hss_prbs);
/*!
 * @brief  Read from EIOA Serdes PRBS fields. 
 * @details This API reads from the following fields in EIOA Serdes PRBS.
 * AXM5500 Only.
 * <PRE>
 *  1. txprbs_sel -             Serdes phy target>.node.0x2     (bits [4:2])
 *  2. rxprbs_sel -             Serdes phy target>110.node.0xa  (bits [2:0])
 *  3. bertok_sel -             Serdes phy target>110.node.0x20 (bit 14)
 *  4. ef_ber_mode -            Serdes phy target>110.node.0x98 (bit 15)
 *  5. txbistena -              Serdes phy target>110.node.0x0  (bit 7)
 *  6. bert_error_reset -       Serdes phy target>110.node.0x20 (bit 15)
 *                              Resets eferrorcount by toggling ber_error_reset
 *  7. bertok -                 Serdes phy target>110.node.0x2c (bit 6)
 *  8. eferrorcount -           Serdes phy target>.node.0xc6    (bits [15:0])
 *                              Bert_error count
 * </PRE>
 * Also see #ncp_eioa_hss_lane_prbs_set().
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *hss_prbs, Pointerto an instance of ncp_hss_prbs_t, to hold
 *             the HSS PRBS information.
 * @return <ul> 
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_DEV_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_INCOMPATIBLE_TARGET_DEVICE_REVISION
 *         </ul> 
 */
    
ncp_st_t 
ncp_eioa_hss_lane_prbs_get(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_hss_prbs_t *hss_prbs);
    
/*!
 * @brief  Read from EIOA Serdes PRBS fields. 
 * @details This API reads from the following fields in EIOA Serdes PRBS.
 * AXM5500 Only.
 * <PRE>
 *  1. txprbs_sel -             Serdes phy target>.node.0x2     (bits [4:2])
 *  2. rxprbs_sel -             Serdes phy target>110.node.0xa  (bits [2:0])
 *  3. bertok_sel -             Serdes phy target>110.node.0x20 (bit 14)
 *  4. ef_ber_mode -            Serdes phy target>110.node.0x98 (bit 15)
 *  5. txbistena -              Serdes phy target>110.node.0x0  (bit 7)
 *  6. bert_error_reset -       Serdes phy target>110.node.0x20 (bit 15)
 *                              Resets eferrorcount by toggling ber_error_reset
 *  7. bertok -                 Serdes phy target>110.node.0x2c (bit 6)
 *  8. eferrorcount -           Serdes phy target>.node.0xc6    (bits [15:0])
 *                              Bert_error count
 * </PRE>
 * Also see #ncp_eioa_hss_lane_prbs_set().
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] use_threshold an instance of boolean valueo.
 *            This indicates wheter to use the errcnt_threshold or not.
 * @param[in] errcnt_threshold. If use_threshold is set to true, the 
 *            eferrorcount value will be compared to this.  If eferrcount is 
 *            greater, the bert_error_reset will be toggled and in turn
 *            eferrorcount will be reset.  
 *            eferrorcount will be returned in any case before it's reset.
 * @param[out] *hss_prbs, Pointerto an instance of ncp_hss_prbs_t, to hold
 *             the HSS PRBS information.
 * @return <ul> 
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_DEV_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_INCOMPATIBLE_TARGET_DEVICE_REVISION
 *         </ul> 
 */
    
ncp_st_t 
ncp_eioa_hss_lane_prbs_get2(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t   use_threshold,
    ncp_uint16_t errcnt_threshold,
    ncp_hss_prbs_t *hss_prbs);
    
/*!
 * @brief  Read RX SerDes coefficients.
 * @details This API reads frome the following fields in RX Serdes coefficients.
 * AXM5500 Only.
 * <PRE>
 *  finalCdrClockPhase   CdrPhase - Final CDR clock phase
 *  finalAGCVlotage      AGCV - Final AGC voltage value
 *  h0Voltage            H0_V - (TargetV) Target switching threshold voltage value
 *  h1Voltage            H1_V - Final voltage used on the 1st DFE tap
 *  h2Voltage            H1_V - Final voltage used on the 2st DFE tap
 *  h3Voltage            H1_V - Final voltage used on the 3st DFE tap
 *  h4Voltage            H1_V - Final voltage used on the 4st DFE tap
 *  h5Voltage            H1_V - Final voltage used on the 5st DFE tap
 *  h6Voltage            H1_V - Final voltage used on the 6st DFE tap
 * </PRE>
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] *rx_coeff, Pointerto an instance of ncp_hss_rx_coeff_t, to hold
 *             the HSS RX Coefficient information.
 * @return <ul> 
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_DEV_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_INCOMPATIBLE_TARGET_DEVICE_REVISION
 *         </ul> 
 */

ncp_st_t 
ncp_eioa_hss_rx_coefficient_get(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_hss_rx_coeff_t *rx_coeff);
    
/*!
 * @brief  Read TX SerDes coefficients.
 * @details This API reads from the following fields in TX Serdes coefficients.
 * AXM5500 Only.
 * <PRE>
 * txSwingControl       Transmitter swing control.
 * txPostEmphasis       Transmitter post-emphasis control.
 * txPreEmphasis        Transmitter pre-emphasis control.
 * </PRE>
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] *tx_coeff, Pointerto an instance of ncp_hss_tx_coeff_t, to hold
 *             the HSS TX Coefficient information.
 * @return <ul> 
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_DEV_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_INCOMPATIBLE_TARGET_DEVICE_REVISION
 *         </ul> 
 */

ncp_st_t
ncp_eioa_hss_tx_coefficient_get(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_hss_tx_coeff_t *tx_coeff);

/*!
 * @brief  Write TX SerDes coefficients.
 * @details This API writesto the following fields in TX Serdes coefficients.
 * AXM5500 Only.
 * <PRE>
 * txSwingControl       Transmitter swing control.
 * txPostEmphasis       Transmitter post-emphasis control.
 * txPreEmphasis        Transmitter pre-emphasis control.
 * </PRE>
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] *tx_coeff, a pointer to an instance of ncp_hss_tx_coeff_t, to hold
 *             the HSS TX Coefficient information.
 * @return <ul> 
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_DEV_INVALID_HANDLE
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_INCOMPATIBLE_TARGET_DEVICE_REVISION
 *         </ul> 
 */

ncp_st_t
ncp_eioa_hss_tx_coefficient_set(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_hss_tx_coeff_t *tx_coeff);

/*!
 * @brief  Program custom pattern to into pattern generator.
 * @details This API writes any custom pattern to program into the 
 * pattern generator.  There are four registers in which the pattern 
 * is entered (in hex).  Each is 16-bits wide, for a total of 64-bits.  
 * They are:
 *
 *   Txdata_reg0 
 *   Txdata_reg1
 *   Txdata_reg2
 *   Txdata_reg3
 *
 * By default, each register is all 0s.  A custom pattern is entered in 
 * chunks of 4-bits.  So, for example, a 1010 pattern would be entered 
 * as 0xAAAA in each of the four registers, or a 4-1x4-0 pattern 
 * (which is low frequency) would be entered as 0xF0F0 in each of the 
 * four registers.
 *
 * By default, the pattern generator will transmit a PRBS pattern (of 
 * which the polynomial length is selected by the txprbs_sel control).  
 * To override that and change to the user-defined pattern, we need to 
 * change two controls:
 *  
 *   txbistena = 0 (disables the PRBS pattern generator)
 *   txdata_sel = 1 (enables the user-defined pattern)
 *
 * By loading the pattern into the four data registers and setting the two
 * override controls (disable the PRBS pattern and enable the user pattern), the 
 * TX will output the desired custom pattern.  Unfortunately, the RX cannot check 
 * a custom pattern, only a PRBS.
 *
 * AXM5500 Only.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA. Use GMAC0 and on.
 * @param[in] txbist_enable an instance of ncp_bool_t, to enable or disable PRBS pattern generator
 * @param[in] txdata_sel_enable an instance of ncp_bool_t, to enable or disable user-defined pattern
 * @param[in] tx_data a pointer to an instance of ncp_hss_txdata_reg_t, to hold
 *            user defined patterns.
 * @return <ul> 
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_DEV_INVALID_HANDLE
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_INCOMPATIBLE_TARGET_DEVICE_REVISION
 *
 */

ncp_st_t
ncp_eioa_hss_user_pattern_set(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t txbist_enable,
    ncp_bool_t txdata_sel_enable,
    ncp_hss_txdata_reg_t *tx_data);

/*!
 * @brief  Retrieve user-defined pattern that is programmed into the pattern generator
 * @details
 *
 * AXM5500 Only.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of. 
 * @param[in] macChan EIOA port number specific to an EIOA. Use GMAC0 and on.
 * @param[out] txbist_enable an instance of ncp_bool_t
 * @param[out] txdata_sel_enable an instance of ncp_bool_t.
 * @param[out] tx_data a pointer to an instance of ncp_hss_txdata_reg_t, to hold
 *            user defined patterns.
 * @return <ul> 
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_DEV_INVALID_HANDLE
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_INCOMPATIBLE_TARGET_DEVICE_REVISION
 *
 */

ncp_st_t
ncp_eioa_hss_user_pattern_get(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t *txbist_enable,
    ncp_bool_t *txdata_sel_enable,
    ncp_hss_txdata_reg_t *tx_data);

/*!
 *
 * @brief  Retrieve efresoulution for serdes lane  
 * @details 
 *
 * AXM5500 Only.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.  Use GMAC0 and on.
 * @param[out] efresolution A pointer to an instance of ncp_uint8_t that holds efresolution
 * @return <ul> 
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_DEV_INVALID_HANDLE
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_INCOMPATIBLE_TARGET_DEVICE_REVISION
 *
 */
ncp_st_t
ncp_eioa_hss_efresolution_get(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint8_t *efresolution);

/*!
 *
 * @brief  Set efresoulution for serdes lane  
 * @details 
 *
 * AXM5500 Only.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.  Use GMAC0 and on.
 * @param[in] efresolution an instance of ncp_uint8_t that holds efresolution
 * @return <ul> 
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_DEV_INVALID_HANDLE
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_INCOMPATIBLE_TARGET_DEVICE_REVISION
 *  
 */
ncp_st_t
ncp_eioa_hss_efresolution_set(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint8_t efresolution);

/*!
 * @brief  Retrieve eferrorcount, efsamcoun, adjusted eferrorcount 
 * and adjusted sample count.
 * @details 
 * efferrorcount is a 16 bit register that contains the number of 
 * detected errors. Dynamic data or data from eferrorcount are 
 * snapped by efcount_sel 0->1
 * 16 bit regisiter that contains the number of 16 or 20 bit words 
 * after the divide-by-N prescaler
 *
 * AXM5500 and AXM3500 Only.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.  Use GMAC0 and on.
 * @param[out] ef_error_count an instance of ncp_uint16_t that holds efferrorcount
 * @param[out] ef_sample_count an instance of ncp_uint16_t efsamcount
 * @param[out] adj_error_count an instance of ncp_uint64_t that holds the adjusted efferrorcount
 * @param[out] adj_sample_count an instance of ncp_uint64_t that holds the adjusted efsamcount
 * @return <ul> 
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_DEV_INVALID_HANDLE
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_INCOMPATIBLE_TARGET_DEVICE_REVISION
 *
 */

ncp_st_t
ncp_eioa_hss_ef_count_get(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_uint16_t *ef_error_count,
    ncp_uint16_t *ef_sample_count,
    ncp_uint64_t *adj_error_count,
    ncp_uint64_t *adj_sample_count);

/*!
 * @brief  Retrieve eferrorcount, efsamcoun, adjusted eferrorcount 
 * and adjusted sample count.
 * @details 
 * efferrorcount is a 16 bit register that contains the number of 
 * detected errors. Dynamic data or data from eferrorcount are 
 * snapped by efcount_sel 0->1
 * 16 bit regisiter that contains the number of 16 or 20 bit words 
 * after the divide-by-N prescaler
 *  
 * AXM5500 AXM3500 Only. 
 *  
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.  Use GMAC0 and on.
 * @param[in] use_threshold an instance of boolean valueo.
 *            This indicates wheter to use the errcnt_threshold or not.
 * @param[in] errcnt_threshold. If use_threshold is set to true, the 
 *            eferrorcount and efsamcaount values will be compared to this vlue.  
 *            If eferrcount or efsamcount is greater, the bert_error_reset will 
 *            be toggled and in turn eferrorcount and efsamcount will be reset.  
 *            eferrorcount and efsaemcaount values will be returned in any case 
 *            before it's reset.
 * @param[out] ef_error_count an instance of ncp_uint16_t that holds efferrorcount
 * @param[out] ef_sample_count an instance of ncp_uint16_t efsamcount
 * @param[out] adj_error_count an instance of ncp_uint64_t that holds the adjusted eferrorcount
 * @param[out] adj_sample_count an instance of ncp_uint64_t that holds the adjusted efsamcount
 * @return <ul> 
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_DEV_INVALID_HANDLE
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_EIOA_INVALID_BUFFER
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_INCOMPATIBLE_TARGET_DEVICE_REVISION
 *
 */

ncp_st_t
ncp_eioa_hss_ef_count_get2(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t   use_threshold,
    ncp_uint16_t errcnt_threshold,
    ncp_uint16_t *ef_error_count,
    ncp_uint16_t *ef_sample_count,
    ncp_uint64_t *adj_error_count,
    ncp_uint64_t *adj_sample_count);


/*!
 * @brief  Retrieve TX and RX inversion values for transmitted data.
 * @details
 * 
 * AXM5500 Only.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of. 
 * @param[in] macChan EIOA port number specific to an EIOA. Use GMAC0 and on.
 * @param[in] tx_invert a pointer to an instance of ncp_bool_t  that holds TRUE or FALSE.
 * @param[in] rx_invert a pointer to an instance of ncp_bool_t  that holds TRUE or FALSE.
 *
 * @return <ul> 
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_DEV_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_INCOMPATIBLE_TARGET_DEVICE_REVISION
 *
 */
ncp_st_t
ncp_eioa_hss_tx_rx_inversion_get(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t *tx_invert,
    ncp_bool_t *rx_invert);

/*!
 * @brief  Set TX and RX inversion for transmitted data.
 * @details
 * 
 * AXM5500 Only.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.  
 * @param[in] macChan EIOA port number specific to an EIOA. Use GMAC0 and on.
 * @param[in] tx_invert an instance of ncp_bool_t  that holds TRUE or FALSE.
 * @param[in] rx_invert an instance of ncp_bool_t  that holds TRUE or FALSE.
 *
 * @return <ul> 
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_DEV_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_INCOMPATIBLE_TARGET_DEVICE_REVISION
 *
 */
ncp_st_t
ncp_eioa_hss_tx_rx_inversion_set(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t tx_invert,
    ncp_bool_t rx_invert);

/*!
 * @brief  Read Rx SerDes synce clock mux control setting to indicate state of lane selection.
 * @details This API extracts the state of lane selection for the synce clock mux control setting.
 * Based on macChan, if the lane was selected, it would return TRUE, otherwise FALSE in flag.
 * AXM5500 Only.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] clkid Synce clock 0 or Synce clock 1.
 * @param[out] *flag, Boolean pointer updated to show the state of lane selection for the macChan
 *
 * @return <ul> 
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_DEV_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_INCOMPATIBLE_TARGET_DEVICE_REVISION
 *         </ul> 
 */

ncp_st_t
ncp_eioa_hss_synce_lane_select_get(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_hss_synce_clkid_t clkid,
    ncp_bool_t *flag);

/*!
 * @brief  Writes the lane selection to the Rx SerDes synce clock mux control setting.
 * @details This API provisions the lane for the synce clock mux control setting. It
 * allows for selection of one input Serdes lane into the internal muxes for 
 * synce output. It also makes sure the NetworkReferenceClockProcessing circuitry also
 * selects the same Serdes as the input received recovered clock, for final synce clock
 * output off-chip.
 *
 * If flag is TRUE,
 * given that within a Serdes, only one lane can be selected for synce clock mux
 * control, this API will implicitly de-select any other selections for the particular
 * Serdes and select the passed in lane based on macChan. It will allow the gated synce
 * clock for output within the Serdes towards the Mux control. It will also provision the
 * appropriate Serdes as the Mux selection in NetworkReferenceClockProcessing circuitry
 * for DPLL pass-through and also the Bypass clock Muxes.
 *
 * If flag is FALSE, and the lane passed in based on macChan was the one provisioned,
 * then it would de-select that lane and also gate Rx serdes clock towards synce_clock
 * output.
 *
 * AXM5500 Only.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] clkid Synce clock 0 or Synce clock 1.
 * @param[in] *flag, Boolean pointer indicating intended lane selection
 *
 * @return <ul> 
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_DEV_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_INCOMPATIBLE_TARGET_DEVICE_REVISION
 *         </ul> 
 */

ncp_st_t
ncp_eioa_hss_synce_lane_select_set(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_hss_synce_clkid_t clkid,
    ncp_bool_t *flag);

/*!
 * @brief  Reads Serdes PLL's ref clock setting.
 * @details This API extracts the source clock selection driving the PLL for a particular port.
 * The reference clock can be NCP_SYNCE_CLK_EREF or NCP_SYNCE_CLK_EREFS where the latter stands for synchronous clock
 * that has undergone off-chip correction and sourced back to Serdes.
 *
 * AXM5500 Only.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *refClkSel, enumeration pointer to indicate NCP_SYNCE_CLK_EREF or NCP_SYNCE_CLK_EREFS
 *
 * @return <ul> 
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_DEV_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_INCOMPATIBLE_TARGET_DEVICE_REVISION
 *         </ul> 
 */

ncp_st_t
ncp_eioa_hss_synce_pll_refclk_select_get(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_hss_synce_refclk_t *refClkSel);

/*!
 * @brief  Writes the Serdes PLL's ref clock setting.
 * @details This API provisions the source clock selection to drive the PLL for a particular port.
 * The reference clock can be NCP_SYNCE_CLK_EREF or NCP_SYNCE_CLK_EREFS where the latter stands for synchronous clock
 * that has undergone off-chip correction and sourced back to Serdes.
 *
 * AXM5500 Only.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] *refClkSel, enumeration pointer to indicate NCP_SYNCE_CLK_EREF or NCP_SYNCE_CLK_EREFS
 *
 * @return <ul> 
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_DEV_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_INCOMPATIBLE_TARGET_DEVICE_REVISION
 *         </ul> 
 */

ncp_st_t
ncp_eioa_hss_synce_pll_refclk_select_set(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_hss_synce_refclk_t *refClkSel);

/*!
 * @brief  Reads Serdes Channel power setting.
 * @details This API extracts the Serdes channel power setting for a particular configured port.
 * The transmitter and receiver will always have the same power setting.
 * TRUE(1) means powered up and FALSE(0) means powered down state.
 * This API can be invoked during active traffic and is not intrusive in the working of channel
 * or other active channels.
 * If the port is not configured this API will return NCP_ST_EIOA_INVALID_PORT_CONFIG.
 *
 * AXM5500 Only.
 * 
 * Note: if there is a PHY between AXM5500 and Far-end, the power status reflected is what is put out
 * by AXM5500. There are PHY's that could have independant behavior upon Rx-LOS.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[out] *powerStatus, boolean pointer to indicate TRUE/1/powered-up-state, or, FALSE/0/powered-down-state
 *
 * @return <ul> 
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_DEV_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_INCOMPATIBLE_TARGET_DEVICE_REVISION
 *         </ul> 
 */

ncp_st_t
ncp_eioa_hss_lane_power_get(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t *powerStatus);

/*!
 * @brief  Provisions Serdes Channel power setting.
 * @details This API provisions the Serdes channel power setting for a particular configured port
 * to be powered up or down.
 * The transmitter and receiver will have the same power setting.
 * TRUE(1) means intention is to power up and FALSE(0) means intention is to power down channel.
 * This API only affects the channel for the particular port and does not impact other active channels.
 * It may be used to provide maximum power-savings on a per serdes channel basis.
 * If the port is not configured this API will return NCP_ST_EIOA_INVALID_PORT_CONFIG.
 * If operating in QSGMII mode please note that there is one primary lane serving the source clock.
 *
 * AXM5500 Only.
 * 
 * Note: if there is a PHY between AXM5500 and Far-end, the power status reflected is what is put out
 * by AXM5500. There are PHY's that could have independant behavior upon Rx-LOS.
 *
 * @param[in] hdl Handle for the NCP that the EIOA is part of.
 * @param[in] macChan EIOA port number specific to an EIOA.
 * @param[in] powerEnable, boolean to indicate TRUE/1/power-up, or, FALSE/0/power-down
 *
 * @return <ul> 
 *         <li> #NCP_ST_SUCCESS
 *         <li> #NCP_ST_INVALID_VALUE
 *         <li> #NCP_ST_MAC_INVALID_MAC
 *         <li> #NCP_ST_DEV_INVALID_HANDLE
 *         <li> #NCP_ST_EIOA_INVALID_PORT_CONFIG
 *         <li> #NCP_ST_EIOA_PORT_NOT_CONFIGURED
 *         <li> #NCP_ST_EIOA_FUNC_NOT_SUPPORTED
 *         <li> #NCP_ST_INCOMPATIBLE_TARGET_DEVICE_REVISION
 *         </ul> 
 */

ncp_st_t
ncp_eioa_hss_lane_power_set(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t powerEnable);

#ifdef __cplusplus
}
#endif
    
#endif /* #ifndef _NCP_EIOA_HSS_UTILS_H_ */


/*
 *  @}
 */
