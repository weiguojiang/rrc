/**************************************************************************
 **                                                                       *
 **                           Intel CONFIDENTIAL                            *
 **                           PROPRIETARY NOTE                            *
 **                                                                       *
 **    This software contains information confidential and proprietary    *
 **    to Intel Corporation.  It shall not be reproduced in whole or in *
 **    part, or transferred to other documents, or disclosed to third     *
 **    parties, or used for any purpose other than that for which it was  *
 **    obtained, without the prior written consent of Intel Corporation.*
 **    (c) 2008-2014, Intel Corporation.  All rights reserved.          *
 **                                                                       *
 **************************************************************************/

#ifndef __ncpCfgTool_h__
#define __ncpCfgTool_h__

#if     !defined(DOXYGEN)

#include <stdlib.h>
#include <ncp.h>

#define CONFIG_OBJECT_COOKIE        0x56789abe



#define cfgtool_dyn_config_fn_t ncp_dynamic_cfg_fn_t

#define CFG_TOOL_MSG(...) \
    do {                                   \
        printf(__VA_ARGS__);              \
    } while (0)

#define CFG_TOOL_PRINT_LINE_FILE (printf("\n%s, line = %d\n",__FILE__,__LINE__))


#define NCP_MAP_CALL(fn) \
    do { \
        ncp_st_t ret = (ncp_st_t) (fn); \
        if (ret != NCP_ST_SUCCESS) { \
            CFG_TOOL_PRINT_LINE_FILE; \
            printf("%s\n", #fn); \
            ncp_status_print("Error", ret); \
            return ret; \
         } \
    } while (0);


#define NCP_MAP_CALL_EXIT(fn) \
    do { \
        ncpStatus = (ncp_st_t) (fn); \
        if (ncpStatus != NCP_ST_SUCCESS) { \
            CFG_TOOL_PRINT_LINE_FILE; \
            printf("%s\n", #fn); \
            ncp_status_print("Error", ncpStatus); \
            goto ncp_return; \
         } \
    } while (0);

/* return code to load or not load config */
NCP_API int cfgToolRV;
#define NCP_CFG_TOOL_NO_LOAD 1

#define CFG_CB_NULL_COOKIE 0x0BADF00D
#define CFG_CB_QUIET_COOKIE 0xABBACABA

typedef struct
{
    ncp_map_value_t *val;
    char           *key;
    ncp_map_t       *map;
} cfg_map_info_t;

typedef struct
{
    void        *fp;
    ncp_uint32_t  mapCookie;
} cfg_callback_arg_t;
    
typedef struct ncp_map_list_s
{
    ncp_map_value_t *value;
    ncp_map_t       *map;
    char           *fullKey;
    struct ncp_map_list_s  *next;
} ncp_map_list_t;


/* 
 * prototypes for config modification callback functions and
 * other shared functions
 */
#if 0
int cfgDumpFullMap(ncp_map_t *map, void * arg);
int cfgDumpHierMap(ncp_map_t *map, void * arg);
int cfgScripts(ncp_map_t *map, void *arg);
char *cfgAttachIdToKey(ncp_map_t *map, char *key, ncp_bool_t create);
#endif

int cfgBin(ncp_map_t *map, void *arg);
int cfgMenu(ncp_map_t *map, void *arg);

ncp_st_t loadConfigDebug ( char *cfgFile, int   cfgInstanceNum,
        cfgtool_dyn_config_fn_t cfgModCallBack, void *cfgModCbArg);

ncp_st_t
cfgScriptsFindAll (ncp_map_t *map, char * tgtKey, ncp_map_list_t **list);

#endif  /* !defined(DOXYGEN) */
    
#endif /* __ncpCfgTool_h__ */
