/**************************************************************************
**                                                                        *
**                           Intel CONFIDENTIAL           *
**                       PROPRIETARY NOTE                                 *
**                                                                        *
**    This software contains information confidential and proprietary     *
**    to Intel Corporation.  It shall not be reproduced in whole or in  *
**    part, or transferred to other documents, or disclosed to third      *
**    parties, or used for any purpose other than that for which it was   *
**    obtained, without the prior written consent of Intel Corporation. *
**    (c) 2008-2014, Intel Corporation.  All rights reserved.           *
**                                                                        *
**  ***********************************************************************
**
**  ***********************************************************************
**
 **************************************************************************/
#ifndef __scan_h__
#define __scan_h__

#include "ncp_types.h"
#include "ncp_ptn.h"

#if defined(WIN32) && defined(SCAN_EXPORTS)
#define SCAN_API __declspec(dllexport)
#else
#if defined(WIN32)
#define SCAN_API __declspec(dllimport)
#else
#define SCAN_API
#endif
#endif

#ifdef __cplusplus
extern "C" { 
#endif

/*
 * Status codes returned by SCAN functions
 */
typedef ncp_st_t scan_status_t;

#define scan_ok                                 NCP_ST_SUCCESS
#define scan_invalid_hdl                        NCP_ST_AGEN_INVALID_HDL
#define scan_invalid_version                    NCP_ST_SCAN_INVALID_FPO_VERSION
#define scan_not_yet_done                       NCP_ST_AGEN_NOT_YET_DONE
#define scan_no_memory                          NCP_ST_NO_MEMORY
#define scan_corrupt_memory                     NCP_ST_NO_MEMORY
#define scan_write_error                        NCP_ST_AGEN_CHECKPOINT_WRITE_ERROR
#define scan_read_error                         NCP_ST_AGEN_INVALID_FPO_BUFFER
#define scan_invalid_index                      NCP_ST_AGEN_INVALID_INDEX
#define scan_regex_missing_paren                NCP_ST_AGEN_SCAN_REGEX_MISSING_PAREN
#define scan_regex_missing_brace                NCP_ST_AGEN_SCAN_REGEX_MISSING_BRACE
#define scan_regex_invalid_interval             NCP_ST_AGEN_SCAN_REGEX_INVALID_INTERVAL
#define scan_regex_malformed_quantifier         NCP_ST_AGEN_SCAN_REGEX_MALFORMED_QUANTIFIER
#define scan_regex_unexpected_token             NCP_ST_AGEN_SCAN_REGEX_UNEXPECTED_TOKEN



typedef void *ncp_scan_t;
typedef void *ncp_scan_state_t;
typedef void (*ncp_scan_list_rules_fn_t)(void* rock, const char* pattern, ncp_ptn_action_t action );

#define NCP_SCAN_DEFAULT_PREFIXLEN               5


NCP_API scan_status_t ncp_scan_create( ncp_uint32_t prefixlen, ncp_scan_t *hdl );
NCP_API scan_status_t ncp_scan_destroy( ncp_scan_t *hdl );
NCP_API ncp_uint32_t ncp_scan_get_prefixlen( ncp_scan_t hdl );

NCP_API scan_status_t ncp_scan_encode_get_bufsize( ncp_scan_t hdl, ncp_uint32_t *bufsize );
NCP_API scan_status_t ncp_scan_encode( ncp_scan_t hdl, ncp_write_fn_t writer, void *rock );
NCP_API scan_status_t ncp_scan_decode( ncp_scan_t hdl, ncp_read_fn_t reader, void *rock );
NCP_API scan_status_t ncp_scan_plot( ncp_scan_t hdl, ncp_write_fn_t writer, void* rock );

NCP_API scan_status_t ncp_scan_add_rule( ncp_scan_t hdl, const char *expression, ncp_ptn_action_t action );
NCP_API scan_status_t ncp_scan_get_rule( ncp_scan_t hdl, ncp_uint32_t id, const char **expression, ncp_ptn_action_t *action );
NCP_API scan_status_t ncp_scan_get_norules( ncp_scan_t hdl, ncp_uint32_t *norules );
NCP_API scan_status_t ncp_scan_clear_rules( ncp_scan_t hdl );
NCP_API scan_status_t ncp_scan_list_rules( ncp_scan_t hdl, ncp_scan_list_rules_fn_t cbfn, void *rock );

NCP_API scan_status_t ncp_scan_build( ncp_scan_t hdl );

NCP_API scan_status_t ncp_scan_get_nostates( ncp_scan_t hdl, ncp_uint32_t *nostates );
NCP_API scan_status_t ncp_scan_get_start_stateid( ncp_scan_t hdl, ncp_uint32_t *id );
NCP_API scan_status_t ncp_scan_get_state( ncp_scan_t hdl, ncp_uint32_t stateid, ncp_scan_state_t *state );

NCP_API scan_status_t ncp_scan_state_get_transitions( ncp_scan_t hdl, ncp_uint32_t id, ncp_uint32_t nstates[], ncp_uint32_t *default_stateid );

NCP_API ncp_uint32_t ncp_scan_state_get_id( ncp_scan_state_t state );
NCP_API ncp_bool_t ncp_scan_state_is_normal( ncp_scan_state_t state );
NCP_API ncp_bool_t ncp_scan_state_is_repeat( ncp_scan_state_t state );
NCP_API ncp_bool_t ncp_scan_state_is_final( ncp_scan_state_t state );
NCP_API ncp_bool_t ncp_scan_state_is_dummy( ncp_scan_state_t state );
NCP_API ncp_bool_t ncp_scan_state_is_reverse( ncp_scan_state_t state );
NCP_API ncp_uint32_t ncp_scan_state_get_repeat( ncp_scan_state_t state );
NCP_API ncp_ptn_action_t *ncp_scan_state_get_action( ncp_scan_state_t state );
NCP_API void ncp_scan_state_put_addr( ncp_scan_state_t state, ncp_uint32_t addr );
NCP_API ncp_uint32_t ncp_scan_state_get_addr( ncp_scan_state_t state );
NCP_API void ncp_scan_state_put_addr2( ncp_scan_state_t state, ncp_uint32_t addr );
NCP_API ncp_uint32_t ncp_scan_state_get_addr2( ncp_scan_state_t state );
NCP_API void ncp_scan_state_put_data( ncp_scan_state_t state, ncp_bdata_t data );
NCP_API ncp_bdata_t ncp_scan_state_get_data( ncp_scan_state_t state );






#ifdef __cplusplus
}
#endif

#endif /* __scan_h__ */
