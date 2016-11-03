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
/*! @file      ncp_agen.h
    @brief     agen interfaces for the NCP.
*/

#ifndef __agen_h__
#define __agen_h__

#include "ncp_types.h"

#if defined(WIN32) && defined(AGEN_EXPORTS)
#define AGEN_API __declspec(dllexport)
#else
#if defined(WIN32)
#define AGEN_API __declspec(dllimport)
#else
#define AGEN_API
#endif
#endif

#ifdef __cplusplus
extern "C" { 
#endif


typedef enum {
    cChipAcp3400
} agen_chip_t;

typedef enum {
    cStrictPriority,
    cOptimizedDistribution
} agen_rootmem_usage_t;

typedef struct {
    ncp_uint32_t		base;
    ncp_uint32_t		size;
    ncp_uint32_t		numbanks; /* How many banks there are - for IMC, this is number of
                                           * IMC controllers after performance mode. DDR - its 
                                           * usually 16 */
    ncp_uint32_t                banksize; /* Size of each bank in instructions. For IMC, its the
                                           * size of each IMC memory. For DDR - its usually 8.
                                           * This needs to be a power of 2 */
} agen_memsection_t;

typedef struct {
    ncp_uint32_t		flowDualMode;
    agen_memsection_t		flow;
    agen_memsection_t		micro;
    agen_memsection_t		rootHigh;
    agen_memsection_t		rootMed;
    agen_memsection_t		rootLow;
    agen_memsection_t		progHigh;
    agen_memsection_t		progMed;
    agen_memsection_t		progLow;
    ncp_uint64_t		hashStaticBase;        /* 64-byte block address */
    ncp_uint32_t		hashStaticSize;		/* Number of 64-byte blocks */
    ncp_uint32_t		hashOverflowSize;	/* Number of 64-byte blocks */
} agen_memspec_t;

typedef enum {
    cAddrUnknown,
    cAddrFlow,
    cAddrMicro,
    cAddrRootHigh,
    cAddrRootMed,
    cAddrRootLow,
    cAddrProgHigh,
    cAddrProgMed,
    cAddrProgLow
} agen_addrtype_t;

typedef struct {
    ncp_hdl_t			devHdl;
    agen_chip_t			chip;
    ncp_uint32_t		major_version;
    ncp_uint32_t		minor_version;

    ncp_bool_t			checkVpaiVersion;
    ncp_uint32_t		vpaiVersionHigh;
    ncp_uint32_t		vpaiVersionLow;

    agen_memspec_t		memSpec;

    agen_rootmem_usage_t	rootMemUsage;
    ncp_bool_t			dynamicFlowLoading;
    ncp_bool_t			isuEnable;
    ncp_uint32_t		fmemReserve;
    ncp_uint32_t		rmemReserve;

    ncp_uint32_t		allocSize;
    ncp_uint32_t		noWritesToBuffer;
    ncp_bool_t			noHardwareWrites;
    ncp_uint32_t		initialShadowSize;
} agen_if_t;
	


/*
 * Status codes returned by AGEN functions
 */
typedef ncp_st_t agen_status_t;

#define agen_ok                                 NCP_ST_SUCCESS
#define agen_invalid_hdl                        NCP_ST_AGEN_INVALID_HDL
#define agen_invalid_inst                       NCP_ST_AGEN_INVALID_INST
#define agen_invalid_func                       NCP_ST_AGEN_INVALID_FUNC
#define agen_invalid_op                         NCP_ST_AGEN_INVALID_OP
#define agen_invalid_index                      NCP_ST_AGEN_INVALID_INDEX
#define agen_invalid_ptnwidth                   NCP_ST_AGEN_INVALID_PTNWIDTH
#define agen_vnums_exhausted                    NCP_ST_AGEN_VNUMS_EXHAUSTED
#define agen_mem_overflow                       NCP_ST_AGEN_MEM_OVERFLOW
#define agen_invalid_version                    NCP_ST_AGEN_INVALID_FPO_VERSION
#define agen_not_yet_done                       NCP_ST_AGEN_NOT_YET_DONE
#define agen_no_memory                          NCP_ST_NO_MEMORY
#define agen_invalid_checkpoint                 NCP_ST_AGEN_INVALID_CHECKPOINT
#define agen_invalid_checkpoint_processor       NCP_ST_AGEN_INVALID_CHECKPOINT_PROCESSOR
#define agen_checkpoint_read_error              NCP_ST_AGEN_CHECKPOINT_READ_ERROR
#define agen_checkpoint_write_error             NCP_ST_AGEN_CHECKPOINT_WRITE_ERROR
#define agen_invalid_image                      NCP_ST_AGEN_INVALID_PROGRAM_IMAGE
#define agen_cb_abort                           NCP_ST_AGEN_CB_ABORT
#define agen_invalid_fpo                        NCP_ST_AGEN_INVALID_FPO_BUFFER
#define agen_invalid_fpo_cookie                 NCP_ST_AGEN_INVALID_FPO_FILE_COOKIE
#define agen_invalid_action                     NCP_ST_AGEN_INVALID_ACTION
#define agen_invalid_tree                       NCP_ST_AGEN_INVALID_TREE
#define agen_invalid_ptn                        NCP_ST_AGEN_INVALID_PTN
#define agen_invalid_xsize                      NCP_ST_AGEN_INVALID_XSIZE
#define agen_invalid_uxsize                     NCP_ST_AGEN_INVALID_UXSIZE
#define agen_symbol_table_not_loaded            NCP_ST_AGEN_SYMBOL_TABLE_NOT_LOADED
#define agen_symbol_not_found                   NCP_ST_AGEN_SYMBOL_NOT_FOUND
#define agen_invalid_mode                       NCP_ST_AGEN_INVALID_MODE
#define agen_invalid_module_name                NCP_ST_AGEN_INVALID_MODULE_NAME
#define agen_no_flow_memory                     NCP_ST_AGEN_NO_FLOW_MEMORY
#define agen_isu_not_enabled                    NCP_ST_AGEN_ISU_NOT_ENABLED
#define agen_isu_rmem_too_small                 NCP_ST_AGEN_ISU_RMEM_TOO_SMALL
#define agen_isu_fmem_too_small                 NCP_ST_AGEN_ISU_FMEM_TOO_SMALL
#define agen_isu_new_fn_name_conflict           NCP_ST_AGEN_ISU_NEW_FN_NAME_CONFLICT
#define agen_isu_old_fn_name_mismatch           NCP_ST_AGEN_ISU_OLD_FN_NAME_MISMATCH
#define agen_isu_old_fn_type_mismatch           NCP_ST_AGEN_ISU_OLD_FN_TYPE_MISMATCH
#define agen_isu_old_fn_width_mismatch          NCP_ST_AGEN_ISU_OLD_FN_WIDTH_MISMATCH
#define agen_isu_old_fn_vsize_mismatch          NCP_ST_AGEN_ISU_OLD_FN_VSIZE_MISMATCH
#define agen_isu_old_fn_srcfns_mismatch         NCP_ST_AGEN_ISU_OLD_FN_SRCFNS_MISMATCH
#define agen_isu_old_fn_swidths_mismatch        NCP_ST_AGEN_ISU_OLD_FN_SWIDTHS_MISMATCH
#define agen_isu_del_fn_caller_exists           NCP_ST_AGEN_ISU_DEL_FN_CALLER_EXISTS
#define agen_isu_vtree_srcfn_invalid            NCP_ST_AGEN_ISU_VTREE_SRCFN_INVALID

/*!
 * An AGEN handle
 */
typedef void *agen_t;

typedef struct {
    ncp_uint32_t         addr1;
    ncp_uint32_t         addr2;
} agen_addrs_t;

typedef struct {
    ncp_uint32_t         highprio;
    ncp_uint32_t         medprio;
    ncp_uint32_t         lowprio;
} agen_flowmem_stats_t;


NCP_API ncp_st_t
ncp_agen_init(ncp_hdl_t hdl);

/*!
 * Create an AG instance
 * @fn ncp_agen_init(ncp_hdl_t hdl)
 */
NCP_API ncp_st_t
ncp_agen_init(ncp_hdl_t hdl);

/*!
 * @fn agen_init(agen_if_t *agenIf)
 */
NCP_API ncp_hdl_t
agen_init(agen_if_t *agenIf);

/*!
 * @fn agen_free(ncp_hdl_t ncp)
 * @brief Completely destroy the AG instance (frees up all allocated memory)
 */
NCP_API agen_status_t
agen_free(ncp_hdl_t ncp);



/*!
 * @fn agen_get_bp_addrs( ncp_hdl_t ncp, ncp_uint32_t id, agen_addrs_t *addrs)
 * @detail For debugging (in simulation only), the compiler inserts special
 * instructions to record breakpoints. Each breakpoint is specified
 * by an id. For this id, the AG records the memory address where 
 * the next real instruction will be encoded. Then, at runtime, the
 * debugging application can query this memory address to figure out
 * if FPP (emulate.c) needs to stop somewhere. The assumption is that
 * the breakpoint ids start from 0 and are contiguous.
 * In 10G, we have two memories (Pretac and Etac), though for now, we
 * have a single address. However, we may also need to address the pass
 * (1 or 2) where the breakpoint may occur. So, we define two addresses.
 * The bottom 24 bits contain the actual address. The top 8 bits are
 * used to specify the pass (1 or 2).
 */
NCP_API agen_status_t
agen_get_bp_addrs( ncp_hdl_t ncp, ncp_uint32_t id, agen_addrs_t *addrs);


/*!
 * A cookie for the checkpoint
 */
#define CHECKPOINT_MAGIC_COOKIE 0x3243433a

NCP_API agen_status_t
agen_write_checkpoint( ncp_hdl_t ncp, ncp_write_fn_t wrFn, void *rock );

NCP_API agen_status_t
agen_init_from_checkpoint( ncp_hdl_t ncp, ncp_read_fn_t rdFn, void *rock );

/*!
 * @fn agen_check_image( ncp_hdl_t ncp )
 * @brief This function is used to check that the hardware program memory
 * image matches with the AGEN's shadow copy
 */
NCP_API agen_status_t
agen_check_image( ncp_hdl_t ncp );


/*!
 * @fn agen_load_fpo( ncp_hdl_t ncp, ncp_read_fn_t rdFn, void *rock, ncp_write_fn_t traceFn, void *tracerock )
 */
NCP_API agen_status_t
agen_load_fpo( ncp_hdl_t ncp, ncp_read_fn_t rdFn, void *rock, ncp_write_fn_t traceFn, void *tracerock );

/*!
 * @fn agen_load_fpo_buf( ncp_hdl_t ncp, void *buf, ncp_uint32_t len )
 */

NCP_API agen_status_t
agen_load_fpo_buf( ncp_hdl_t ncp, void *buf, ncp_uint32_t len );

NCP_API agen_status_t
agen_flowmem_stats(ncp_hdl_t ncp, agen_flowmem_stats_t *etac);

/*!
 * @fn agen_pvt_hdl(void)
 * @brief Private function for some test cases in simulator
 * Not to be used externally
 */
NCP_API agen_t agen_pvt_hdl(void);


/*!
 * @fn agen_fpo_checkpoint_restore_buf( ncp_hdl_t ncp, void *buf, ncp_uint32_t len )
 */
NCP_API ncp_st_t
agen_fpo_checkpoint_restore_buf( ncp_hdl_t ncp, void *buf, ncp_uint32_t len );


/*!
 * Functions related to In-Service Upgrade (ISU)
 */
NCP_API ncp_st_t
agen_isu_prepare( ncp_hdl_t ncp, void *buf, ncp_uint32_t len );
NCP_API ncp_st_t
agen_isu_update( ncp_hdl_t ncp );
NCP_API ncp_st_t
agen_isu_cleanup( ncp_hdl_t ncp );

/*!
 * @fn agen_apiactive( ncp_hdl_t ncp, ncp_bool_t *flag )
 * @brief Check whether the API active flag is set (warm restart feature) 
 */
NCP_API ncp_st_t
agen_apiactive( ncp_hdl_t ncp, ncp_bool_t *flag );

/*!
 * @fn agen_resync( ncp_hdl_t ncp )
 * @brief  To resync the agen (reinit the internal lock) on a restart 
 */
NCP_API ncp_st_t
agen_resync( ncp_hdl_t ncp );

/*!
 * Some debugging APIs for the simulator on a stack overflow 
 */
NCP_API ncp_st_t
agen_get_caller_info_for_addr( ncp_hdl_t ncp, ncp_uint32_t addr, ncp_uint16_t *fid, char **fname );
NCP_API ncp_st_t
agen_get_callee_info_for_addr( ncp_hdl_t ncp, ncp_uint32_t addr, ncp_uint16_t *fid, char **fname );

/*!
 * @fn agen_write_fpi( ncp_hdl_t ncp, ncp_write_fn_t wrfn, void *arg )
 */
NCP_API ncp_st_t
agen_write_fpi( ncp_hdl_t ncp, ncp_write_fn_t wrfn, void *arg );


NCP_API ncp_st_t
agen_get_ovnumsize(ncp_hdl_t ncp, ncp_uint16_t treeId, ncp_uint32_t* ovnumsize);


/*******************************************************************************************
 * Agen HEMEM Analyzer
 * These are a set of utility functions to allocate hash engine memory among the hash trees.
 * These functions are used by the agen and also by the compiler to validate as well as to
 * tell the user how much to allocate. 
 * There are two sizes
 *    staticSize - represents amount of memory for namespaces and the DMTs of hash trees.
 *                      SPECICIED AS 64 BYTE BLOCKS
 *    overflowSize - represents amount of overflow memory among all the hash trees
 *                      SPECICIED AS 256 BYTE BLOCKS
 * Caller first creates a handle and then adds the namespaces and functions. 
 * The algorithm is run by calling agen_heanalyzer_analyze(). This function takes the staticSize
 * and overflowSize, both of which can be 0.
 *         First the minimum static size, optimal static size, optimal overflow for the optimal
 *         static is calculated. 
 *         If staticSize is > 0, it is distributed among the functions. Then the required overflow
 *         is calculated.
 *         If overflowSize > 0, required is checked to be enough. Excess is redistributed 
 * At the end, caller calls specific methods to retrieve the calculated values
 **********************************************************************************************/
typedef void* agen_heanalyzer_t;
NCP_API agen_heanalyzer_t
agen_heanalyzer_create(ncp_uint32_t numNamespaces, ncp_uint32_t numFunctions);
NCP_API agen_status_t
agen_heanalyzer_destroy(agen_heanalyzer_t hhdl);
NCP_API agen_status_t
agen_heanalyzer_add_namespace(agen_heanalyzer_t hhdl, ncp_uint32_t id, ncp_uint32_t numEntries);
NCP_API agen_status_t
agen_heanalyzer_add_function(agen_heanalyzer_t hhdl, ncp_uint32_t id, ncp_uint32_t prio, ncp_uint32_t numEntries, ncp_bool_t optional);
NCP_API agen_status_t
agen_heanalyzer_get_required_static_size(agen_heanalyzer_t hhdl, ncp_uint32_t *staticSize);
NCP_API agen_status_t
agen_heanalyzer_get_optimal_static_size(agen_heanalyzer_t hhdl, ncp_uint32_t *staticSize);
NCP_API agen_status_t
agen_heanalyzer_get_optimal_overflow_size(agen_heanalyzer_t hhdl, ncp_uint32_t *overflowSize);
NCP_API agen_status_t
agen_heanalyzer_get_required_overflow_size(agen_heanalyzer_t hhdl, ncp_uint32_t *overflowSize);
NCP_API agen_status_t
agen_heanalyzer_get_namespace_info(agen_heanalyzer_t hhdl, ncp_uint32_t id, ncp_uint32_t *numBlocks);
NCP_API agen_status_t
agen_heanalyzer_get_function_info(agen_heanalyzer_t hhdl, ncp_uint32_t id, ncp_uint32_t *numBuckets, ncp_uint32_t *numBucketsPerIndex, ncp_uint32_t *numOverflowBuckets);
NCP_API agen_status_t
agen_heanalyzer_analyze(agen_heanalyzer_t hhdl, ncp_uint32_t staticSize, ncp_uint32_t overflowSize);

#ifdef __cplusplus
}
#endif

#endif /* __agen_h__ */
