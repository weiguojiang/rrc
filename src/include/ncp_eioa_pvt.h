/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


#ifndef _NCP_EIOA_PVT_H_
#define _NCP_EIOA_PVT_H_

#include "ncp_eioa.h"
#include "ncp_sal.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(NCP_KERNEL)

#define NCP_EIOA_VALIDATE_HANDLE_ACTIVE  \
    eioas = NULL;                        \
    NCP_CALL(ncp_validate_handle(ncp));  \
    eioas = (ncp_eioas_t *)ncp->eioaHdl; \
    ncpStatus = ncp_eioa_validate_and_lock_handle(eioas, TRUE); \
    if ( ncpStatus != NCP_ST_SUCCESS ) { \
        eioas = NULL;                    \
        NCP_CALL(ncpStatus);             \
    }

#define NCP_EIOA_VALIDATE_HANDLE_INACTIVE \
    eioas = NULL;                         \
    NCP_CALL(ncp_validate_handle(ncp));   \
    eioas = (ncp_eioas_t *)ncp->eioaHdl;  \
    ncpStatus = ncp_eioa_validate_and_lock_handle(eioas, FALSE); \
    if ( ncpStatus != NCP_ST_SUCCESS ) { \
        eioas = NULL;                    \
        NCP_CALL(ncpStatus);             \
    }

#define NCP_EIOA_COMMON_VALIDATE_HANDLE_ACTIVE \
    eioas = NULL;                              \
    NCP_CALL(ncp_validate_handle(ncp));        \
    eioas = (ncp_eioas_t *)ncp->eioaHdl;       \
    ncpStatus = ncp_eioa_common_validate_and_lock_handle(eioas, TRUE); \
    if ( ncpStatus != NCP_ST_SUCCESS ) {       \
        eioas = NULL;                          \
        NCP_CALL(ncpStatus);                   \
    }


#define NCP_EIOA_COMMON_VALIDATE_HANDLE_INACTIVE \
    eioas = NULL;                                \
    NCP_CALL(ncp_validate_handle(ncp));          \
    eioas = (ncp_eioas_t *)ncp->eioaHdl;         \
    ncpStatus = ncp_eioa_common_validate_and_lock_handle(eioas, FALSE); \
    if ( ncpStatus != NCP_ST_SUCCESS ) {         \
        eioas = NULL;                            \
        NCP_CALL(ncpStatus);                     \
    }

#define NCP_EIOA_RETURN \
    if (eioas != NULL && eioas->lockActive == TRUE) { \
        eioas->lockActive = FALSE; \
        eioas->apiActive = FALSE; \
        ncp_sem_post(&eioas->threadLock); \
    } \
    return ncpStatus;

#define NCP_EIOA_PORT_TYPE_CUST                 "CUSTOMER"
#define NCP_EIOA_PORT_TYPE_CUST_ACCESS          "CUSTOMER_ACCESS"
#define NCP_EIOA_PORT_TYPE_SERVICE_PROVIDER     "SERVICE_PROVIDER"

ncp_st_t
ncp_eioa_validate_handle(ncp_eioas_t *eioas);

ncp_st_t
ncp_eioa_validate_and_lock_handle(ncp_eioas_t *eioas, ncp_bool_t isActive);

ncp_st_t
ncp_eioa_common_validate_handle(ncp_eioas_t *eioas);

ncp_st_t
ncp_eioa_common_validate_and_lock_handle(ncp_eioas_t *eioas, ncp_bool_t isActive);

ncp_st_t
ncp_eioa_common_vps_is_valid_vp(ncp_hdl_t ncpHdl, ncp_uint32_t regOffset);

ncp_st_t
ncp_eioa_common_vps_valid_vp_set(ncp_hdl_t ncpHdl, ncp_uint32_t regOffset);

ncp_st_t
ncp_eioa_ipp_dscp_cos_set(ncp_dev_hdl_t devHdl,
                          ncp_uint32_t eioaNum,
                          ncp_uint8_t dscpValue,
                          ncp_uint8_t cosValue);

ncp_st_t
ncp_eioa_epp_dscp_cos_set(ncp_t *ncp,
                          ncp_uint32_t eioaNum,
                          ncp_uint8_t dscpValue,
                          ncp_uint8_t cosValue);

ncp_st_t
ncp_eioa_ipp_dscp_cos_get(ncp_dev_hdl_t devHdl,
                          ncp_uint32_t eioaNum,
                          ncp_uint8_t dscpValue,
                          ncp_uint8_t *cosValue);

ncp_st_t
ncp_eioa_common_qinq_svlan_write(ncp_dev_hdl_t devHdl, ncp_uint32_t  eioa_num, 
        ncp_uint16_t svlanId, ncp_bool_t valid, ncp_bool_t one2oneSvlan);

ncp_st_t
ncp_eioa_vlan_is_valid(ncp_dev_hdl_t devHdl, ncp_uint16_t vlanId, 
                       ncp_bool_t *o2oSvlan, ncp_uint8_t *svlanIndex);

ncp_st_t
    get_multicast_index(ncp_uint8_t *hash_index,
        ncp_uint8_t *hash_crc);

ncp_st_t
    ncp_eioa_mcast_hash_crc(ncp_port_t *ncp_port,
        ncp_uint8_t *hash_crc, ncp_uint32_t mcast_index);

ncp_uint8_t get_byteparity(ncp_uint8_t x);

ncp_st_t
ncp_eioa_common_vps_vflow_valid_get(ncp_t *ncp, ncp_uint32_t vflowIdRegOffset);

#define NCP_EIOA_VFLOW_REG_OFFSET_TO_BIT_NUM(regOffset) (((regOffset) & 0xF00) >> 8)
#define NCP_EIOA_VFLOW_REG_OFFSET_TO_BIT_NUM_5500(regOffset) (((regOffset) & 0x0F0) >> 4)

#endif

#define NCP_EIOA_PORT_VALIDATE(hdl, port)                                       \
{                                                                               \
    ncp_eioas_t *__eioas    = NULL;                                             \
    ncp_eioa_t  *__eioa     = NULL;                                             \
    ncp_port_t  *__ncp_port = NULL;                                             \
                                                                                \
    __eioas = hdl->eioaHdl;                                                     \
    if(__eioas == NULL)                                                         \
    {                                                                           \
        NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                              \
    }                                                                           \
    if((port >= NCP_XGMAC0) && (port <= NCP_GMAC4))                             \
    {                                                                           \
        __eioa = __eioas->eioa0;                                                \
        if (__eioa == NULL)                                                     \
        {                                                                       \
            NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                          \
        }                                                                       \
    }                                                                           \
    else if((port >= NCP_XGMAC8) && (port <= NCP_GMAC12))                       \
    {                                                                           \
        __eioa = __eioas->eioa1;                                                \
        if(__eioa == NULL)                                                      \
        {                                                                       \
            NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                          \
        }                                                                       \
    }                                                                           \
    else                                                                        \
    {                                                                           \
        NCP_CALL(NCP_ST_MAC_INVALID_MAC);                                       \
    }                                                                           \
                                                                                \
    __ncp_port = __eioa->NCP_POINTER_ARRAY(port, port);                         \
    if (__ncp_port == NULL)                                                     \
    {                                                                           \
        NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                              \
    }                                                                           \
                                                                                \
    if (__ncp_port->cfg_ok != TRUE)                                             \
    {                                                                           \
        NCP_CALL(NCP_ST_EIOA_PORT_NOT_CONFIGURED);                              \
    }                                                                           \
}

/*
 * Verify that a given EIOA handle is valid. 
 * Only for 55xx
 */
#define NCP_EIOA_VALIDATE_EIOA_NUM_55xx(eioasHdl, eioaNum)       \
({                                                               \
    ncp_bool_t   __isValid        = FALSE;                       \
    ncp_eioas_t* eioaContainer    = (ncp_eioas_t *)eioasHdl;     \
    if ( eioaContainer->eioa != NULL &&                          \
         eioaContainer->eioa[(eioaNum)] != NULL )                \
    {                                                            \
        __isValid = TRUE;                                        \
    }                                                            \
                                                                 \
    __isValid;                                                   \
})

#define NCP_EIOA_RATE_LIMIT_MAX_BIT_SEL     (15)    /* 4 bits */
#define NCP_EIOA_RATE_LIMIT_MAX_MULTIPLIER  (255)   /* 8 bits */

#define NCP_EIOA_NUM_COS_ENTRIES    8
#define NCP_EIOA_NUM_DSCP_ENTRIES   64

#define NCP_EIOA_VFLOW_ID_REGS_BASE ((NCP_EIOA_CORE_ENHANCED_CLASSIFICATION_BASE) + (NCP_ENHANCED_CLASSIFICATION_VFLOW_ID_REGISTERS_BASE))
#define NCP_EIOA_MCAST_REPL_BASE    ((NCP_EIOA_CORE_ENHANCED_CLASSIFICATION_BASE) + (NCP_ENHANCED_CLASSIFICATION_MULTICAST_REPLICATION_BASE))



#ifdef __cplusplus
}
#endif

#endif /* #ifndef _NCP_EIOA_PVT_H_ */

