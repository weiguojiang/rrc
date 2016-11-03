/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

#ifndef __NCP_API_TRACE_H__
#define __NCP_API_TRACE_H__

/*
    #define NCP_API_TRACE
*/

#if defined ( NCP_API_TRACE ) && (!defined ( NCP_KERNEL ) || defined ( NCP_VXWORKS ))


#define NCP_API_TRACE_SIZE 1024


typedef struct {
    ncp_uint32_t    ts;
    ncp_uint16_t    pid;
    ncp_uint16_t    tag;
    ncp_uint32_t    val[2];
} ncp_api_trace_entry_t;

typedef struct {
    ncp_sem_t       lock;
    ncp_uint32_t    idx;
    ncp_uint32_t    active;
    ncp_api_trace_entry_t *traceBuf;
} ncp_api_trace_info_t;

NCP_API ncp_st_t 
ncp_api_trace_init(void);

NCP_API ncp_st_t
ncp_api_trace_event(
        ncp_uint32_t tag, 
        ncp_uint32_t val0, 
        ncp_uint32_t val1 );
#else

#define ncp_api_trace_init()
#define ncp_api_trace_event(a, b, c)

#endif   /* defined NCP_API_TRACE */


#endif
