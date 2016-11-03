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

#ifndef __ncp_parser_h__
#define __ncp_parser_h__

#if     !defined(DOXYGEN)


#include "ncp.h"
#include "ncp_pvt.h"
#include "ncpCli.h"
#include "ncpConfigUtil.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/* enumerate possible commands */
typedef enum ncp_sh_cmds
{
    NCP_SH_SET,
    NCP_SH_LET,
    NCP_SH_BREAK,
    NCP_SH_ECHO,
    NCP_SH_EXIT,
    NCP_SH_PAUSE,
    NCP_SH_INCLUDE,
    NCP_SH_COND_IF,
    NCP_SH_COND_ELSE,
    NCP_SH_COND_END,
    NCP_SH_COND_WHILE,
    NCP_SH_DUMP_VARS,
    NCP_SH_TRACE,
    NCP_SH_UNKNOWN
} ncp_sh_cmd_t;

typedef enum {
    NCP_SH_VERBOSITY_MIN,
    NCP_SH_VERBOSITY_SHOW_CALLS,
    NCP_SH_VERBOSITY_SHOW_ARGS,
    NCP_SH_VERBOSITY_SHOW_EVERYTHING
} ncp_sh_verbosity_t;

typedef struct {
    ncp_sh_verbosity_t verbosity;
} ncp_sh_api_opts_t;


/* 
 * TODO: 
 * try to consolidate and or choose 'correct' values for these...
 */
#define NCP_MAX_VAL_STR_LEN 128
#define NCP_MAX_TOK_STR_LEN 128
#define NCP_MAX_CMD_STR_LEN 1024 


typedef struct {
    char            *cmdLine;
    ncp_uint32_t     size;
    ncp_map_t       *varMap;
    ncp_map_t       *globMap;
    char            *p;
} ncp_cmd_buf_t;

typedef struct ncp_sh_scope_s ncp_sh_scope_t;
typedef struct ncp_sh_condex_s ncp_sh_condex_t;

/* 
 * conditional execution control
 */

struct ncp_sh_condex_s {
    int     lineno;
    int     start_ptr;
    int     else_ptr;
    int     end_ptr;
    int     type;
    int     nloops;
    int     nest_depth;

    ncp_cmd_buf_t *wbuf;
    ncp_bool_t     in_else;
    ncp_bool_t     is_true;
    ncp_sh_condex_t *prev;
};

/* 
 * The shell 'scope of execution' keeps track of where we are 
 * in the current script file along with the list of variables 
 * and conditional execution state. 
 *
 */

struct ncp_sh_scope_s {
    FILE * fp;
    int    lineno;
    char * fname;
    int    interactive;
    ncp_sh_condex_t *condex;
    ncp_map_t       *varMap;
    ncp_map_t       *globMap;
    ncp_sh_scope_t *prev;
};


struct test_stats_t {
    char  * testName;
    int     apiCalls;
    int     apiErrs;
    int     pduCalls;
    int     pduErrs;
    int     testCalls;
    int     testErrs;
    struct test_stats_t * prev;
};



#define NCP_STRUCT_MALLOC(struct_t, rv) \
    ( \
     { \
      struct_t * __v = (struct_t *) ncp_malloc(sizeof(struct_t)); \
      if (__v == NULL) { \
        printf("%s:%d : couldn't malloc %s\n", __FILE__, __LINE__, #struct_t); \
        return rv; \
      } \
      memset(__v, 0, sizeof(struct_t)); \
      __v; \
      } \
    )


/* convenience macros for grabbing an integer from the parmMap */
 
/* for required parameters */
#define NCP_VAR_GET_INT(type, name, idx, dest) \
    { ncp_int64_t __i64 = 0; \
      NCP_CALL(ncp_map_get_i64(parmMap, name,  &__i64)); \
      dest = (ncp_##type##_t) __i64; \
    }

/* for optional parameters */
#define NCP_VAR_GET_INT_OPTIONAL(type, name, idx, dest, dflt) \
    { ncp_int64_t __i64 = 0; \
      ncpStatus = ncp_map_get_i64(parmMap, name,  &__i64); \
      if (ncpStatus == NCP_ST_SUCCESS) { \
          dest = (ncp_##type##_t) __i64; \
      } else { \
          if (ncpStatus != NCP_ST_MAP_KEY_NOT_EXIST) { \
              NCP_CALL(ncpStatus); \
          } \
          dest = (ncp_##type##_t) dflt; \
      } \
    }

#define NCP_VAR_GET_BOOL(name, dest) \
    {                                                                 \
      NCP_CALL(ncp_map_get_bool(parmMap, name,  &dest));              \
    }

#define NCP_VAR_GET_BOOL_OPTIONAL(name, dest, dflt)           \
    { ncp_bool_t __b = FALSE;                                         \
      if ( ncp_map_get_bool(parmMap, name,  &__b) == NCP_ST_SUCCESS ) \
          dest = (ncp_bool_t) __b;                                    \
      else                                                            \
          dest = (ncp_bool_t) dflt;                                   \
    }

#define NCP_VAR_GET_STR(name, dest)                     \
    {                                                   \
      NCP_CALL(ncp_map_get_str(parmMap, name, &dest));  \
    }

#define NCP_VAR_GET_MAC_ADDR(name, dest) \
    { ncp_uint32_t __len = 0; \
      NCP_CALL(ncp_map_get_bin(parmMap, name, (char **)&dest, &__len)); \
      if(__len != 6)    \
        NCP_CALL(NCP_ST_INVALID_VALUE); \
    }

#define NCP_VAR_GET_IP_ADDR(name, dest, len) \
      NCP_CALL(ncp_map_get_bin(parmMap, name, &dest, &len));


#define NCP_VAR_GET_BP_BLOCK_SIZE(name, dest) \
    { char* __str = 0; \
      NCP_CALL(ncp_map_get_str(parmMap, name,  &__str)); \
      if ( ncp_stricmp(__str, "NCP_BP_BUFFER_SIZE_256B") == 0 )                 \
        dest = NCP_BP_BUFFER_SIZE_256B;                                \
      else if ( ncp_stricmp(__str, "NCP_BP_BUFFER_SIZE_2KB") == 0 )            \
          dest = NCP_BP_BUFFER_SIZE_2KB;                              \
      else if ( ncp_stricmp(__str, "NCP_BP_BUFFER_SIZE_16KB") == 0 )            \
          dest = NCP_BP_BUFFER_SIZE_16KB;                              \
      else                                               \
      {                                                  \
          printf("Invalid port specified\n");            \
          NCP_CALL(NCP_ST_INVALID_PARAMETER);            \
      }                                                  \
    }

#define NCP_SH_PRINT_ARG_BP_BLOCK_SIZE(arg)      \
    if ( arg == NCP_BP_BUFFER_SIZE_256B)                               \
        printf("\t%s = NCP_BP_BUFFER_SIZE_256B\n", #arg);                  \
    else if ( arg == NCP_BP_BUFFER_SIZE_2KB)                          \
        printf("\t%s = NCP_BP_BUFFER_SIZE_2KB\n", #arg);                  \
    else if ( arg == NCP_BP_BUFFER_SIZE_16KB)                          \
        printf("\t%s = NCP_BP_BUFFER_SIZE_16KB\n", #arg);

/* a couple of macros for printing arguments */
#define NCP_SH_PRINT_ARG_INT(arg) printf("\t%s = %d\n", #arg, arg);
#define NCP_SH_PRINT_ARG_I64(arg)       \
{                                       \
   printf("\t%s = %s\n", #arg,          \
       NCP_CONVERT_LONG_TO_STR(arg));   \
}
#define NCP_SH_PRINT_ARG_U64(arg)       \
{                                       \
   printf("\t%s = %s\n", #arg,          \
       NCP_CONVERT_ULONG_TO_STR(arg));  \
}
#define NCP_SH_PRINT_ARG_HEX(arg) printf("\t%s = 0x%08x\n", #arg, arg);

#define NCP_SH_PRINT_VPS_BITMASK(arg)                    \
{                                                        \
    printf("\t%s = 0x%s\n", #arg,                        \
        NCP_CONVERT_LONG_TO_HEX_STR_FORMAT("%09", arg)); \
}

#define NCP_SH_PRINT_ARG_BOOL(arg) printf("\t%s = %s\n", #arg, arg ? "true" : "false");
#define NCP_SH_PRINT_ARG_STRING(arg) printf("\t%s = %s\n", #arg, arg);

#define NCP_SH_PRINT_ARG_BIN(arg) \
    { int i; \
        printf("\t%s = \n\t\t(bin) [", #arg); \
        for (i = 0; i < arg.len; i++) { \
            printf("%02x", (ncp_uint8_t)arg.buf[i]); \
            if ((i & 3) == 3) printf(" "); \
            if ((i & 15) == 15) printf("\n\t\t       ");\
        } \
        printf("]:%d\n", arg.len); \
    }

#define NCP_SH_PRINT_ARG_MAC_ADDR(arg) \
    printf("\t%s = %02x:%02x:%02x:%02x:%02x:%02x\n", #arg, arg[0], arg[1], arg[2], arg[3], \
        arg[4], arg[5]);

#define NCP_SH_PRINT_ARG_IPV4_ADDR(arg) \
    printf("\t%s = %03d.%03d.%03d.%03d\n", #arg, arg[0], arg[1], arg[2], arg[3]);

#define NCP_SH_PRINT_ARG_IPV6_ADDR(arg) \
    printf("\t%s = %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n", \
        #arg, arg[0], arg[1], arg[2], arg[3], \
        arg[4], arg[5], arg[6], arg[7], \
        arg[8], arg[9], arg[10], arg[11], \
        arg[12], arg[13], arg[14], arg[15]);

/*
#define NCP_SH_PRINT_ARG_HEX1(arg) printf("\t%s = 0x%08x", #arg, arg);
#define NCP_SH_PRINT_ARG_HEX2(arg) printf(", 0x%08x\n", arg);
#define NCP_SH_PRINT_ARG_FLOAT(arg) printf("\t%s = %f\n", #arg, arg);
*/


/* Map a launch engine string to the correct ncp_launch_engint_type_t value */
#define NCP_MAP_LAUNCH_ENGINE_STRING(name, dest)                        \
    if      ((ncp_stricmp(name, "ncp_launch_engine_eioa") == 0) ||      \
             (ncp_stricmp(name, "eioa") == 0))                          \
                    dest = ncp_launch_engine_eioa;                      \
    else if ((ncp_stricmp(name, "ncp_launch_engine_mpp") == 0)  ||      \
             (ncp_stricmp(name, "mpp") == 0))                           \
                    dest = ncp_launch_engine_mpp;                       \
    else if ((ncp_stricmp(name, "ncp_launch_engine_cpu") == 0)  ||      \
             (ncp_stricmp(name, "cpu") == 0))                           \
                    dest = ncp_launch_engine_cpu;                       \
    else if ((ncp_stricmp(name, "ncp_launch_engine_expander") == 0)  || \
             (ncp_stricmp(name, "expander") == 0))                      \
                    dest = ncp_launch_engine_expander;                  \
    else if ((ncp_stricmp(name, "ncp_launch_engine_tdmioa") == 0)  ||   \
             (ncp_stricmp(name, "tdmioa") == 0))                        \
                    dest = ncp_launch_engine_tdmioa;                    \
    else                                                                \
    {                                                                   \
          printf("Invalid launch engine specified\n");                  \
          NCP_CALL(NCP_ST_INVALID_PARAMETER);                           \
    }


extern int parse_script ( void );
extern int build_parm_map(ncp_cmd_buf_t *buf, ncp_map_t *parmMap);


int ncp_next_varname(ncp_cmd_buf_t *buf, char *tok);
int ncp_next_token(ncp_cmd_buf_t *buf, char *tok);
int ncp_next_expr(ncp_cmd_buf_t *buf, char *expr);
int ncp_next_word(ncp_cmd_buf_t *buf, char *tok, ncp_uint32_t *separator);
int ncp_match_token(ncp_cmd_buf_t *buf, const char *str, ncp_bool_t consume);
int ncp_get_token_value(ncp_cmd_buf_t *buf, char *tok, ncp_map_value_t **val, ncp_bool_t  *isGlobal);


/* expression evaluator functions */
void ncp_map_value_to_string(ncp_map_value_t * val, char *str, int len);
void ncp_map_value_to_formatted_string( ncp_map_value_t * val,
                        char *str, char  fmt, int   fmtlen, int   maxlen);

ncp_map_value_t * ncp_eval (ncp_cmd_buf_t *buf);
ncp_bool_t ncp_eval_truth(ncp_cmd_buf_t *buf);
char * ncp_expand_expr(ncp_cmd_buf_t *buf, char *argStr, int argStrSize);

/* API/CLI bindings */
ncp_st_t ncp_sh_cli(ncp_cmd_buf_t *buf);
ncp_st_t ncp_sh_api(ncp_cmd_buf_t *buf);

NCP_API ncp_st_t
ncp_sh_mtm_apis(char *apiName,
                ncp_hdl_t ncpHdl,
                ncp_map_t *parmMap,
                ncp_sh_api_opts_t *opts);

NCP_API ncp_st_t
ncp_sh_sm_apis(char *apiName,
                ncp_dev_hdl_t devHdl,
                ncp_map_t *parmMap,
                ncp_sh_api_opts_t *opts);

NCP_API ncp_st_t
ncp_sh_eioa_switch_apis(char *apiName,
                        ncp_hdl_t ncpHdl,
                        ncp_map_t *parmMap,
                        ncp_sh_api_opts_t *opts);
NCP_API ncp_st_t
ncp_sh_mac_apis(char *apiName,
                ncp_hdl_t ncpHdl,
                ncp_map_t *parmMap,
                ncp_sh_api_opts_t *opts);

NCP_API ncp_st_t
ncp_sh_eioa_apis(char *apiName,
                 ncp_hdl_t ncpHdl,
                 ncp_map_t *parmMap,
                 ncp_sh_api_opts_t *opts);

NCP_API ncp_st_t
ncp_sh_eioa_vp_apis(char *apiName,
                    ncp_hdl_t ncpHdl,
                    ncp_vp_hdl_t vpHdl,
                    ncp_map_t *parmMap,
                    ncp_sh_api_opts_t *opts);

NCP_API ncp_st_t
ncp_sh_cow_apis(char *apiName, 
                ncp_hdl_t ncpHdl, 
                ncp_map_t *parmMap,
                ncp_sh_api_opts_t *opts);

NCP_API ncp_st_t
ncp_sh_bp_apis(char *apiName, 
                ncp_hdl_t ncpHdl, 
                ncp_map_t *parmMap,
                ncp_sh_api_opts_t *opts);

#endif  /* !defined(DOXYGEN) */

#endif /* __ncp_parser_h__ */
