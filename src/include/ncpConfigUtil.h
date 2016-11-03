/**************************************************************************
 **                                                                       *
 **                           Intel CONFIDENTIAL      *
 **                           PROPRIETARY NOTE                            *
 **                                                                       *
 **    This software contains information confidential and proprietary    *
 **    to Intel Corporation.  It shall not be reproduced in whole or in *
 **    part, or transferred to other documents, or disclosed to third     *
 **    parties, or used for any purpose other than that for which it was  *
 **    obtained, without the prior written consent of Intel Corporation.*
 **    (c) 2008-2014, Intel Corporation.  All rights reserved.          *
 **                                                                       *
 **
 **
 **************************************************************************/

#ifndef __ncpConfigUtil_h__
#define __ncpConfigUtil_h__

#if     !defined(DOXYGEN)

#include "ncp.h"
#include "ncp_sal.h"

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */


/***************************************************************************
* Constants & Type Definitions                                             *
***************************************************************************/

/*
 * Define the NCP_CHIPNAME that we want to handle.
 */

#define NCP_CHIPNAME    "ACP"
#define NCP_CFGFILE     "acp_diag.cfg"

#define NCP_UTIL_MSG(...)                 \
    do {                                           \
        printf(__VA_ARGS__);                      \
        if (ncp_utilLogFP) {                       \
            fprintf(ncp_utilLogFP, __VA_ARGS__);  \
        }                                          \
    } while (0)

/* States for NCP  */
#define MAX_STATES 10 
typedef struct
{
    char          states[MAX_STATES][64];
    ncp_uint32_t  num_states;
} CHIP_STATES_T;

/* possible modes of operation */
typedef enum
{
    NCP_CFG_TOOL_MODE_DUMP_FULL=0,
    NCP_CFG_TOOL_MODE_DUMP_HIER,
    NCP_CFG_TOOL_MODE_DUMP_BIN,
    NCP_CFG_TOOL_MODE_DUMP_SCRIPTS,
    NCP_CFG_TOOL_MODE_APPLY_OVERRIDE,
    NCP_CFG_TOOL_MODE_INTERACTIVE,
    NCP_CFG_TOOL_MODE_WARM_RESTART,
    NCP_CFG_TOOL_MODE_UNKNOWN
} ncp_cfg_tool_mode_t;

/* Bitmasks for hwioTraceFlags */
#define NCP_HWIO_TRACE_OPT_NONE          0x00000000
#define NCP_HWIO_TRACE_OPT_SHOWRDVALS    0x11111111

/***************************************************************************
* Global State Variables & APIs                                            *
***************************************************************************/

NCP_API FILE* ncp_utilLogFP;

NCP_API int   cfgToolRV;

NCP_API void ncp_util_start_clock(void);

NCP_API double ncp_util_end_clock(void);

NCP_API
int ncp_cfg_tool_set_mode(ncp_cfg_tool_mode_t *curMode,
                          ncp_cfg_tool_mode_t reqMode);

NCP_API ncp_int64_t ncp_str_to_i64(char *pnt);
NCP_API ncp_uint64_t ncp_str_to_u64(char *pnt);

NCP_API int cfgDumpFullMap(ncp_map_t *map, void * arg);
NCP_API int cfgDumpHierMap(ncp_map_t *map, void * arg);
NCP_API char *cfgAttachIdToKey(ncp_map_t *map, char *key, ncp_bool_t create);
NCP_API void cfgPrintType(ncp_map_type_t type);
NCP_API int cfgModApplyOverrides(ncp_map_t *map, void * arg);


#if 0
NCP_API ncp_st_t
ncp_util_attach_chipset_instance(
    int         instanceNum,
    ncp_bool_t *attached);
#endif

NCP_API ncp_st_t
ncp_util_config(
    ncp_uint32_t         devNum,
    ncp_uint32_t         logicalDevNum,
    char *               cfgFile,
    ncp_cfg_event_fn_t   optionalEventFn,
    void *               eventFnArg,
    ncp_dynamic_cfg_fn_t cfgModCallBack,
    void *               cbArg,
    ncp_hdl_t *          ncpHdl,
    ncp_uint32_t         flags);

NCP_API int
ncp_configUtilReadFnDefault(
    void *arg,
    void *buf,
    int   len);

NCP_API void
ncp_configUtilEventFnDefault(
    char              *chipName,
    ncp_uint32_t       elementInstance,
    char              *cfgModule,
    ncp_cfg_status_t   cfgStatus,
    void              *callBackFnArg);

NCP_API ncp_st_t 
ncp_util_destroy(
    ncp_uint32_t         devNum);

#if 0
NCP_API ncp_st_t
ncp_util_reconfig(
    char *               cfgFile,
    ncp_cfg_event_fn_t   optionalEventFn,
    void *               eventFnArg,
    ncp_dynamic_cfg_fn_t cfgModCallBack,
    void *               cbArg,
    ncp_hdl_t *          ncpHdl);

NCP_API ncp_st_t
ncp_util_build_upgrade_list(
    char                   *optArg, 
    ncp_chipset_upgrade_t **upgradeList,
    ncp_uint32_t           *count);

NCP_API ncp_st_t
ncp_util_upgrade(
    char                             *cfgFile, 
    ncp_uint32_t                      chipsetInstance,
    ncp_util_chipset_instance_info_t *chipsetInfo,
    ncp_chipset_upgrade_t            *upgradeList,
    ncp_uint32_t                      upgradeListCount);

#endif

/***************************************************************************
* APIs: Features for tracing NCP device driver calls                       *
***************************************************************************/

NCP_API ncp_uint32_t ncp_hwioTraceFlags;
                        /* Mask of extra options that control the output
                         * of this feature. */

NCP_API ncp_uint32_t ncp_numTraceWords;

    /* Standard trace function to be provided to ncp_hwio_trace() */
NCP_API void
ncp_hwioTraceDefaultFn(
    void           *hwioFuncArg,     /* IN: Opaque function argument */
    ncp_hwio_type_t hwioType,        /* IN: hwio event type */
    ncp_uint32_t    devNum,          /* IN: device number */
    void           *hwioArg);        /* IN: hwio event specific argument */


#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif  /* !defined(DOXYGEN) */

#endif /* __ncpConfigUtil_h__ */
