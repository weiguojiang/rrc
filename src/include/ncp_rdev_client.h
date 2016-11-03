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

#ifndef __ncp_rdev_client_h__
#define __ncp_rdev_client_h__

#ifdef __cplusplus
extern "C" {
#endif


#include <ncp_rdev_if.h>
#include <ncp_sal.h>
#include <ncp_rdev_msg.h>

#define NCP_RDEV_CLIENT_HANDLE_COOKIE    0x52444556
typedef void * ncp_rdev_hdl_t;

/*
 * Controls for how many non-acknowledged writes may be sent
 */
#define NCP_RDEV_MAX_NON_ACK_WRITES 0
#define NCP_RDEV_MAX_NON_ACK_BYTES  (128*1024)

typedef struct _ncp_rdev_client_conn_t {
    ncp_uint16_t         localPort;
    ncp_rdev_conn_info_t cInfo;
    ncp_uint32_t         nNonAckMsgs;
    ncp_uint32_t         nNonAckBytes;
    ncp_thread_t         threadId;
    ncp_msg_t           *msgBuff;

    struct _ncp_rdev_client_conn_t   *next;
} ncp_rdev_client_conn_t;

typedef struct {
    ncp_uint32_t         cookie;
    ncp_uint32_t         devNum;
    ncp_msg_addr_t      *wtAddr;
    ncp_rdev_conn_info_t ltConn;
    ncp_uint8_t          sessionId;
    ncp_uint16_t         basePort;
    ncp_uint16_t         nextPort;
    ncp_sem_t            lock;
    ncp_uint16_t         numConns;
    ncp_uint16_t         needKeepalive;
    ncp_thread_t         keepaliveThread;
    ncp_uint32_t         serverTimeouts;
    ncp_bool_t           timeoutsEnabled;

    ncp_rdev_client_conn_t    *connList;
} ncp_rdev_client_t;


/* external APIs */
NCP_API ncp_st_t
ncp_rdev_client_open_device(ncp_uint32_t devNum, ncp_uint32_t flags, 
                ncp_rdev_hdl_t *devHdl);

NCP_API ncp_st_t
ncp_rdev_client_close_device(ncp_rdev_hdl_t *devHdl);

NCP_API ncp_st_t
ncp_rdev_client_dev_num_get(ncp_rdev_hdl_t devHdl, ncp_uint32_t *devNum);

NCP_API ncp_st_t
ncp_rdev_client_check_async(ncp_rdev_hdl_t devHdl, ncp_uint32_t msgLength, 
                            ncp_bool_t *needAck);

NCP_API ncp_st_t
ncp_rdev_client_get_buffer(ncp_rdev_hdl_t devHdl, ncp_msg_t **buff);

NCP_API ncp_st_t
ncp_rdev_client_send_msg(ncp_rdev_hdl_t devHdl, ncp_uint16_t msgType,
                        ncp_msg_t *msg, ncp_uint32_t nbytes);

NCP_API ncp_st_t
ncp_rdev_client_recv_msg(ncp_rdev_hdl_t devHdl, ncp_msg_t *msg,
                         ncp_uint32_t *nbytes, ncp_uint32_t *apirc,
                         ncp_timespec_t *timeout);

#ifdef __cplusplus
}
#endif

#endif
