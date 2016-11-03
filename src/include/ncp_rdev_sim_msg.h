/**************************************************************************
 *                                                                        *
 *                           Intel CONFIDENTIAL           *
 *                                                                        *
 *                       PROPRIETARY NOTE                                 *
 *                                                                        *
 *    This software contains information confidential and proprietary     *
 *    to Intel Corporation.  It shall not be reproduced in whole or in  *
 *    part, or transferred to other documents, or disclosed to third      *
 *    parties, or used for any purpose other than that for which it was   *
 *    obtained, without the prior written consent of Intel Corporation. *
 *    (c) 2008, Intel Corporation.  All rights reserved.    *
 *                                                                        *
 *  ***********************************************************************
 *
 *  ***********************************************************************
 *
 *************************************************************************/

#ifndef _NCP_RDEV_SIM_MSG_H_
#define _NCP_RDEV_SIM_MSG_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The NCP device specific include files 
 */

#include <ncp_types.h>

/* 
 * Unique Message Types and structures for NCP Device API
 * Note that we use bit 0x4000 to indicate a write request
 * with no acknowledgement.
 */

#define NCP_RDEV_MSG_READ                        0x00000201
#define NCP_RDEV_MSG_WRITE                       0x00000202
#define NCP_RDEV_MSG_WRITE_NO_ACK                0x00004202
#define NCP_RDEV_MSG_OUTPUT_TASK_PUT             0x00000203
#define NCP_RDEV_MSG_INPUT_TASK_GET              0x00000204
#define NCP_RDEV_MSG_TASK_COMPL_PUT              0x00000205

#define NCP_RDEV_MSG_STATUS                      0x00000212
#define NCP_RDEV_MSG_VERSION                     0x00000213
#define NCP_RDEV_MSG_HW_VERSION_GET              0x00000214
#define NCP_RDEV_MSG_RESET                       0x0000022E
#define NCP_RDEV_MSG_STATS                       0x0000022F

/*  NCP_CLI_MSG structure definition 
 *  This is a generic client message 
 *  TODO: fixed vs. variable msgLength ? 
 */

typedef struct ncp_rdev_sim_msg {
    ncp_msg_header_t     header;    /* standard message header */
    ncp_uint32_t         regionId;  /* NCP region ID */
    ncp_uint32_t         dummy;     /* dummy padding */
    ncp_uint64_t         offset;    /* start offset within NCP region */
    ncp_uint32_t         count;     /* count */
    ncp_uint32_t         xferWidth; /* transfer width (in bytes)  */
    ncp_uint32_t         cmdType;   /* configuration I/O command type */
    ncp_uint32_t         flags;     /* flags */
    ncp_uint32_t         data[NCP_RDEV_MSG_DEFAULT_DATA_WORDS];  /* data buffer */
} ncp_rdev_sim_msg_t;

typedef struct {
    ncp_uint16_t     bufferSize;
    ncp_uint16_t     unused_1;
    ncp_uint8_t      templateId;
    ncp_uint8_t      pduDataStart;
    ncp_uint8_t      taskErr;
    ncp_uint8_t      unused_2;
} ncp_rdev_itask_info_t;


typedef struct ncp_rdev_sim_itask_msg {
    ncp_msg_header_t       header;       /* standard message header */
    ncp_uint32_t           flags;        /* flags */
    ncp_uint32_t           queueId;
    ncp_rdev_itask_info_t  itask_info;
    ncp_uint32_t           desc[4];      /* four word descriptor */
#if 0
    ncp_uint8_t            buffer[NCP_RDEV_MSG_DEFAULT_DATA_BYTES];
#endif
} ncp_rdev_sim_itask_msg_t;

typedef struct ncp_rdev_sim_otask_msg {
    ncp_msg_header_t       header;       /* standard message header */
    ncp_uint32_t           flags;        /* flags */
    ncp_uint32_t           queueId;
    ncp_uint32_t           desc[4];      /* four word descriptor */
    ncp_uint8_t            parms[NCP_TASK_PARAM_SIZE_BYTES]; 
    ncp_uint8_t            data[NCP_RDEV_MSG_DEFAULT_DATA_BYTES];  /*  PDU Buffer*/
} ncp_rdev_sim_otask_msg_t;

typedef struct ncp_rdev_sim_ttask_msg {
    ncp_msg_header_t       header;       /* standard message header */
    ncp_uint32_t           flags;        /* flags */
    ncp_uint32_t           queueId;
    ncp_uint32_t           desc[4];      /* four word descriptor */
} ncp_rdev_sim_ttask_msg_t;


#define NCP_RDEV_SIM_MSG_HEADER_SIZE \
        (sizeof(ncp_rdev_sim_msg_t) - NCP_RDEV_MSG_DEFAULT_DATA_BYTES)

#define NCP_RDEV_SIM_OTASK_MSG_HEADER_SIZE \
        (sizeof(ncp_rdev_sim_otask_msg_t) - NCP_RDEV_MSG_DEFAULT_DATA_BYTES)

#define NCP_RDEV_SIM_ITASK_MSG_HEADER_SIZE \
        (sizeof(ncp_rdev_sim_itask_msg_t) - 16)
/*
 * TODO: 
 */
#define NCP_RDEV_SIM_TASK_GET_MSG_SIZE (sizeof(ncp_msg_header_t) + 8)

#define NCP_RDEV_SIM_TASK_COMPL_MSG_SIZE (sizeof(ncp_rdev_sim_ttask_msg_t))


/*
 * for blocking calls, any relevant API information must be saved
 * so it can be used to make the call when the event occurs.
 * These are the structure definitions that are stored in blockingInfo
 */

typedef struct {
    ncp_uint32_t flags;
} ncp_rdev_sim_pdu_recv_info_t;

typedef struct {
    ncp_uint32_t pduSize;
    ncp_uint32_t flags;
    ncp_uint32_t *pduBuf;
} ncp_rdev_sim_pdu_send_info_t;


#ifdef __cplusplus
}
#endif

#endif /* _NCP_RDEV_API_MSG_H_ */



