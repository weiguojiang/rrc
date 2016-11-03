#ifndef _NCP_EIOA_HSS_UTILS_35XX_H_
#define _NCP_EIOA_HSS_UTILS_35XX_H_
   
#ifdef __cplusplus
extern "C" {
#endif 

#include "ncp_eioa_hss_utils.h"     

/* Public Definitions */
    
/****************** 
 * Data structures*
 ******************/

ncp_st_t 
ncp_eioa_hss_lane_prbs_set_35xx(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_hss_prbs_t *hss_prbs);
    
ncp_st_t 
ncp_eioa_hss_lane_prbs_get_35xx(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_hss_prbs_t *hss_prbs);
    
ncp_st_t 
ncp_eioa_hss_lane_prbs_get2_35xx(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t   use_threshold,
    ncp_uint16_t errcnt_threshold,
    ncp_hss_prbs_t *hss_prbs);
    
ncp_st_t 
ncp_eioa_hss_rx_coefficient_get_35xx(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_hss_rx_coeff_t *rx_coeff);
    
ncp_st_t 
ncp_eioa_hss_tx_coefficient_get_35xx(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_hss_tx_coeff_t *tx_coeff);
    
ncp_st_t 
ncp_eioa_hss_tx_coefficient_set_35xx(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_hss_tx_coeff_t *tx_coeff);
    
ncp_st_t
ncp_eioa_hss_user_pattern_set_35xx(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t txbist_enable,
    ncp_bool_t txdata_sel_enable,
    ncp_hss_txdata_reg_t *tx_data);

ncp_st_t
ncp_eioa_hss_user_pattern_get_35xx(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t *txbist_enable,
    ncp_bool_t *txdata_sel_enable,
    ncp_hss_txdata_reg_t *tx_data);

ncp_st_t
ncp_eioa_hss_efresolution_get_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint8_t *efresolution);

ncp_st_t
ncp_eioa_hss_efresolution_set_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint8_t efresolution);

ncp_st_t
ncp_eioa_hss_ef_count_get_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_uint16_t *ef_error_count,
    ncp_uint16_t *ef_sample_count,
    ncp_uint64_t *adj_error_count,
    ncp_uint64_t *adj_sample_count);

ncp_st_t
ncp_eioa_hss_ef_count_get2_35xx(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t   use_threshold,
    ncp_uint16_t errcnt_threshold,
    ncp_uint16_t *ef_error_count,
    ncp_uint16_t *ef_sample_count,
    ncp_uint64_t *adj_error_count,
    ncp_uint64_t *adj_sample_count);

ncp_st_t
ncp_eioa_hss_tx_rx_inversion_get_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t *tx_invert,
    ncp_bool_t *rx_invert);

ncp_st_t
ncp_eioa_hss_tx_rx_inversion_set_35xx(
    void *hdl,
    ncp_macChan_t macChan,
    ncp_bool_t tx_invert,
    ncp_bool_t rx_invert);

ncp_st_t
ncp_eioa_hss_synce_lane_select_get_35xx(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_hss_synce_clkid_t clkid,
    ncp_bool_t *flag);

ncp_st_t
ncp_eioa_hss_synce_lane_select_set_35xx(
     void *hdl,
    ncp_macChan_t macChan,
    ncp_hss_synce_clkid_t clkid,
    ncp_bool_t *flag);

#ifdef __cplusplus
}
#endif
    
#endif /* #ifndef _NCP_EIOA_HSS_UTILS_35XX_H_ */
