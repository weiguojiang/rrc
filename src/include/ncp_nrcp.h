/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


/*! @file      ncp_nrcp.h
 *  @brief     Network Reference Clock Processing
 *             
 *             NRCP APIs, defines and structure definitions.
 *             The NRCP API calls provide the ability to configure the NRCP block, 
 *             and switch reference clock at run-time.
 * 
 *  @addtogroup _nrcp_ Network Reference Clock Processing
 * 
 *  @{
 */


    
#ifndef _NCP_NRCP_H_
#define _NCP_NRCP_H_

#ifdef __cplusplus
extern "C" {
#endif


/* Public Enumerated Types */

/*!
 * @brief NRCP reference clock specification
 *
 *    Specifies the reference clock for NRCP block.
 */
typedef enum ncp_nrcp_ref_src_e
{
       NCP_NRCP_SRC_NET_REF_CLK = 0,           /*!< network reference clock */
       NCP_NRCP_SRC_NCO_CLK=12,           /*!< 1588 recovered clock */
       NCP_NRCP_SRC_SYNCE_0_CLK=2,         /*!< Selected recovered clock for serdes block 0 (any of 4 lanes)*/
       NCP_NRCP_SRC_SYNCE_1_CLK=3,         /*!< Selected recovered clock for serdes block 1 (any of 4 lanes)*/
       NCP_NRCP_SRC_SYNCE_2_CLK=4,         /*!< Selected recovered clock for serdes block 2 (any of 2 lanes)*/
       NCP_NRCP_SRC_GND,                 /*!< Ground, freerun */
        
       NCP_NRCP_SRC_NET_REF_CLK1=1,        /*!< network reference clock1, only available on AXM5500 */

       NCP_NRCP_SRC_SYNCE_3_CLK=5,         /*!< Selected recovered clock for serdes block 3, only available on AXM5500  */
       NCP_NRCP_SRC_SYNCE_4_CLK=6,         /*!< Selected recovered clock for serdes block 4, only available on AXM5500  */
       NCP_NRCP_SRC_SYNCE1_0_CLK=7,         /*!< Selected recovered clock1 for serdes block 0, only available on AXM5500  */
       NCP_NRCP_SRC_SYNCE1_1_CLK=8,         /*!< Selected recovered clock1 for serdes block 1, only available on AXM5500  */
       NCP_NRCP_SRC_SYNCE1_2_CLK=9,         /*!< Selected recovered clock1 for serdes block 2, only available on AXM5500  */
       NCP_NRCP_SRC_SYNCE1_3_CLK=10,         /*!< Selected recovered clock1 for serdes block 3, only available on AXM5500  */
       NCP_NRCP_SRC_SYNCE1_4_CLK=11,         /*!< Selected recovered clock1 for serdes block 4, only available on AXM5500  */

       NCP_NRCP_SRC_MAX
 }ncp_nrcp_ref_src_t;



 /*!
  * @brief NRCP reference clock rate specification
  *
  *   Specifies the reference clock rate for NRCP block.
  */
typedef enum ncp_nrcp_ref_freq_e
{
    NCP_NRCP_REF_FREQ_0_008 = 0,           /*!< 8.0KHz */
    NCP_NRCP_REF_FREQ_1_544,           /*!< 1.544MHZ */
    NCP_NRCP_REF_FREQ_2_048,           /*!< 2.048MHZ */
    NCP_NRCP_REF_FREQ_4_096,           /*!< 4.096MHZ */
    NCP_NRCP_REF_FREQ_8_192,           /*!< 8.192MHZ */
    NCP_NRCP_REF_FREQ_16_384,           /*!< 16.384MHZ */
    NCP_NRCP_REF_FREQ_19_440,           /*!< 19.440MHZ */
    NCP_NRCP_REF_FREQ_25_000,          /*!< 25 MHz */
    NCP_NRCP_REF_FREQ_34_368,          /*!< 34.368MHz*/
    NCP_NRCP_REF_FREQ_44_736,          /*!< 44.736MHz */
    NCP_NRCP_REF_FREQ_125_000,          /*!< 125 MHz */
    NCP_NRCP_REF_FREQ_156_250,          /*!< 156.25 MHz */

    NCP_NRCP_REF_FREQ_MAX
}ncp_nrcp_ref_freq_t;

/*!
  * @brief NRCP DPLL select  *
  *   Selects the DPLL for NRCP block.
  */
typedef enum ncp_nrcp_dpll_select_e
{
    NCP_NRCP_TRANSPORT_DPLL = 0,           /*!< transport DPLL (DPLL1) */
    NCP_NRCP_EEC_DPLL,           /*!< EEC DPLL (DPLL2)*/

    
    NCP_NRCP_DPLL_MAX
}ncp_nrcp_dpll_select_t;



/*!
  * @brief NRCP DPLL holdoever mode  *
  *   Specifies DPLL holdover mode.
  */
typedef enum ncp_nrcp_dpll_holdoverMode_e
{
    NCP_NRCP_HOLDOVER_ACQUIRED_FREQ = 0,           /*!< previous acquired frequency*/
    NCP_NRCP_HOLDOVER_LOCAL_FREQ,           /*!< local frequency (free run) */

    
    NCP_NRCP_HOLDOVER_MAX
}ncp_nrcp_dpll_holdoverMode_t;


/*!
  * @brief NRCP CLKO configuration  *
  *   Specifies NRCP CLKO configuration .
  */


typedef enum ncp_nrcp_clkoSelect_e
{
    NCP_NRCP_CLKOSEL_1544 = 0,     /*< 1.544MHz NRCP devider output*/
    NCP_NRCP_CLKOSEL_2048,        /*< 2.048MHz NRCP devider output*/
    NCP_NRCP_CLKOSEL_44736,        /*< 44.736MHz NRCP devider output, invalid for AXM5500*/
    NCP_NRCP_CLKOSEL_34378,        /*< 34.368MHz NRCP devider output, invalid for AXM5500**/
    NCP_NRCP_CLKOSEL_155520,        /*< 155.52MHz NRCP devider output, invalid for AXM5500**/
    NCP_NRCP_CLKOSEL_103680,        /*< 103.69MHz NRCP devider output, invalid for AXM5500**/
    NCP_NRCP_CLKOSEL_NRCKI,        /*< nrcki input frequency*/
    NCP_NRCP_CLKOSEL_CORECLK_DIV4,     /*< NRCP core clock divided by 4*/
    NCP_NRCP_CLKOSEL_125000,        /*< 125MHz - nrcp apll ourput devided by 10*/
    NCP_NRCP_CLKOSEL_25000,        /*< 25MHz - nrcp apll reference clock */

    
    NCP_NRCP_CLKOSEL_DISABLED = 0xF,      /*< CLKO disabled */
    NCP_NRCP_CLKOSEL_MAX

}ncp_nrcp_clkoSelect_t;


/*!
  * @brief NRCP ETHCLKO configuration  *
  *   Specifies NRCP ETHCLKO configuration .
  */


typedef enum ncp_nrcp_ethclkoSelect_e
{
    NCP_NRCP_ETHCLKOSEL_25000 = 0,     /*< 25 MHz NRCP devider output*/
    NCP_NRCP_ETHCLKOSEL_125000,        /*< 125MHz NRCP devider output*/
    NCP_NRCP_ETHCLKOSEL_156250,        /*< 156.25MHz NRCP devider output*/
    NCP_NRCP_ETHCLKOSEL_NRCKI,        /*< nrcki input frequency */
    
    NCP_NRCP_ETHCLKOSEL_DISABLED = 0x7,      /*< ETHCLKO disabled */

    NCP_NRCP_ETHCLKOSEL_MAX

}ncp_nrcp_ethclkoSelect_t;



/*!
  * @brief NRCP DPLL acquisition mode  *
  *   Specifies NRCP DPLL acquisition mode  .
  */


typedef enum ncp_nrcp_acquisitionMode_e
{
    NCP_NRCP_NORMAL_ACQUISITION_MODE=0,     /*< normal acquisition mode*/
    NCP_NRCP_FAST_ACQUISITION_MODE,        /*< fast acquisition mode*/
  
    NCP_NRCP_ACQUISITION_MODE_MAX

}ncp_nrcp_acquisitionMode_t;


/*!
  * @brief NRCP ETHCLKO configuration  *
  *   Specifies NRCP ETHCLKO configuration .
  */



/*!
  * @brief NRCP SYNC0 pin output selection  *
  *   Specifies SYNC0 pin output clock.
  */
typedef enum ncp_nrcp_SYNC0_PIN_Select_e
{
    NCP_NRCP_SYNC0_ETHCLKOUT= 0,     /*< NRCP ethernet devider output*/

    NCP_NRCP_SYNC0_EIOA0_PHY_SYNC_CLK,    /*< AXM2500 only, EIOA0 PHY SYNC clock */
    NCP_NRCP_SYNC0_NRCPSRC_BYPASS,       /*< bypassed NRCP reference clock, not available on AXM2500*/
    NCP_NRCP_DPLL_REFCLK,                /*< DPLL reference clock */
    NCP_NRCP_SYNC0_GPO_0,                /*< AXM2500 only, GPO output=1 */
    NCP_NRCP_SYNC0_GPO_1,                /*< AXM2500 only, GPO output=0 */
   
    NCP_NRCP_SYNC0_MAX

}ncp_nrcp_SYNC0_PIN_Select_t;


/*!
  * @brief NRCP SYNC1 pin output selection  *
  *   Specifies SYNC1 pin output clock.
  */
typedef enum ncp_nrcp_SYNC1_PIN_Select_e
{
    NCP_NRCP_SYNC1_CLKOUT= 0,     /*< NRCP PDH clock devider output*/
    NCP_NRCP_SYNC1_NRCPSRC_BYPASS,        /*< bypassed NRCP reference clock,  not available on AXM2500*/
    NCP_NRCP_SYNC1_EIOA1_PHY_SYNC_CLK,    /*< AXM2500 only, EIOA1 PHY SYNC clock */
    NCP_NRCP_SYNC1_DPLL_REF,              /*< DPLL reference clock, not available on AXM2500 */
    NCP_NRCP_SYNC1_GPO_0,                /*< AXM2500 only, GPO output=1 */
    NCP_NRCP_SYNC1_GPO_1,                /*< AXM2500 only, GPO output=0 */

    NCP_NRCP_SYNC1_MAX

}ncp_nrcp_SYNC1_PIN_Select_t;



/* Public Structures */
/*!
 * @brief PLL settings
 */

typedef struct  ncp_nrcp_Config_s
{

        ncp_nrcp_ref_src_t nrcpRefClkSrc;              /*!< NRCP reference clock source */
        ncp_nrcp_ref_freq_t nrcpRefFreq;             /*!< NRCP reference clock frequence */
        ncp_nrcp_dpll_select_t  nrcpDPLL;           /*< Select NRCP DPLL */
        ncp_bool_t isDPLLbypass;                     /*!< bypass DPLL */
        ncp_bool_t  isNrcpHoldoverEnabled;        /*!< enable NRCP holdover feature */
        ncp_nrcp_dpll_holdoverMode_t holdoverMode; /*!< holdover mode */

} ncp_nrcp_Config_t;


/* Public Structures */
/*!
 * @brief NRCP status */
typedef struct  ncp_nrcp_status_s
{
      ncp_bool_t holdoverState;         /**!< if set to TRUE, NRCP is currently in holdover mode */
      ncp_bool_t lockState;         /**!< if set to TRUE, NRCP is currently locked */
      ncp_bool_t holdover;              /*!< if set to TRUE, NRCP DPLL experienced holdover */
      ncp_bool_t unlock;              /*!< if set to TRUE, NRCP DPLL experienced unlock */
      ncp_bool_t phaseErrSlip;              /*!< if set to TRUE, NRCP phase error slipped */
      ncp_bool_t ACC1_overflow;              /*!< if set to TRUE, ACC1 overflowed */
      ncp_bool_t ACC2_overflow;              /*!< if set to TRUE, ACC2 overflowed */
      
} ncp_nrcp_status_t;




/* Public Structures */
/*!
 * @brief NRCP reference clock update parameters
 */
typedef struct  ncp_nrcp_refclk_updateparam_s
{
       ncp_nrcp_ref_src_t nrcpRefClkSrc;              /*!< NRCP reference clock source */
      
} ncp_nrcp_refclk_updateparam_t;


/* Public Structures */
/*!
 * @brief NRCP SYNC0 pin configuration
 */
typedef struct  ncp_nrcp_SYNCE0_Pin_Config_s
{
       ncp_nrcp_SYNC0_PIN_Select_t sync0_select;    /*!< Select SYNC0 pin ouput source */
       ncp_nrcp_ethclkoSelect_t  ethClkO;           /*!< NRCP ethernet divider output, used when ethclko is selected in sync0_select field*/
       ncp_nrcp_ref_src_t        bypassedClk;      /*!< bypassed NRCP reference clock, used when bypass is selected in sync0_select field*/
      
} ncp_nrcp_SYNCE0_Pin_Config_t;

/* Public Structures */
/*!
 * @brief NRCP SYNC1 pin configuration
 */
typedef struct  ncp_nrcp_SYNCE1_Pin_Config_s
{
       ncp_nrcp_SYNC1_PIN_Select_t sync1_select;    /*!< Select SYNC1 pin ouput source */
       ncp_nrcp_clkoSelect_t  clko;           /*!< NRCP clock divider output, used when clko is selected in sync1_select field*/
       ncp_nrcp_ref_src_t        bypassedClk;      /*!< bypassed NRCP reference clock, used when bypass is selected in sync0_select field*/
      
} ncp_nrcp_SYNCE1_Pin_Config_t;

/* Published APIs */
/*!
 *  @brief  Configure the NRCP DPLL.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the NRCP is part of.
 *  @param[in]  nrcpCfg     Pointer to NRCP configuration data structure.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_PLL_HANDLE_INVALID
 *      \li ::NCP_ST_PLL_FREQUENCY_INVALID
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_nrcp_dpll_set(ncp_hdl_t ncpHdl, ncp_nrcp_Config_t *nrcpCfg);



/*!
 *  @brief  release NRCP divider from reset.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that NRCP is part of
 *  
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_nrcp_divider_reset_release(ncp_hdl_t ncpHdl);

/*!
 *  @brief  Configure NRCP CLKO.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the NRCP is part of.
 *  @param[in]  clkoSelect   CLKO select.

 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_nrcp_clko_set(ncp_hdl_t ncpHdl, ncp_nrcp_clkoSelect_t clkoSelect);



/*!
 *  @brief  Configure NRCP ETHCLKO.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the NRCP is part of.
 *  @param[in]  ethclkoSelect   ETHCLKO select.

 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_nrcp_ethclko_set(ncp_hdl_t ncpHdl, ncp_nrcp_ethclkoSelect_t ethclkoSelect);




/*!
 *  @brief  Update NRCP reference clock
 *  @details  This API assumes the NRCP reference clock has currently been  configured to ground.
 *            It will switch the reference clock from ground to the specified source.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the PLL is part of.
 *  @param[in]  refclk      New reference clock parameters.

 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_nrcp_refclk_update(ncp_hdl_t ncpHdl, ncp_nrcp_refclk_updateparam_t *refclk);



/*!
 *  @brief  NRCP status
 *  @details  This API retrieves the NRCP status
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the PLL is part of.
 *  @param[out]  nrcpStatus      NRCP status.

 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_nrcp_status_get(ncp_hdl_t ncpHdl, ncp_nrcp_status_t *nrcpStatus);



/*!
 *  @brief  NRCP status
 *  @details  This API retrieves the NRCP status
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the PLL is part of.
 *  @param[out]  acquisitionMode      DPLL aqcusition mode.

 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_nrcp_acquisitionMode_sel (ncp_hdl_t ncpHdl, ncp_nrcp_acquisitionMode_t  acquisitionMode);
    

/*!
 *  @brief  Configure the Sync CLK0 pin.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the NRCP is part of.
 *  @param[in]  syncE0PinCfg  pointer to SyncE0 pin configurtion structure.

 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_nrcp_SYNCE_CLK0_set(ncp_hdl_t ncpHdl,  ncp_nrcp_SYNCE0_Pin_Config_t *syncE0PinCfg);


/*!
 *  @brief  Configure the SyncE CLK1 pin.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the NRCP is part of.
 *  @param[in]  syncE1PinCfg  pointer to SyncE1 pin configurtion structure.

 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_nrcp_SYNCE_CLK1_set(ncp_hdl_t ncpHdl,  ncp_nrcp_SYNCE1_Pin_Config_t *syncE1PinCfg);



#ifdef __cplusplus
}
#endif

#endif /* #ifndef _NCP_NRCP_H_ */

