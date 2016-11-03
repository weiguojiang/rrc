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

#ifndef __ncp_rdev_server_h__
#define __ncp_rdev_server_h__

#ifdef __cplusplus
extern "C" {
#endif

#include <ncp_rdev_if.h>
#include <ncp_sal.h>
#include <ncp_rdev_msg.h>



/*
 * Server logging 
 */
#define NCP_RDEV_LOG_ERROR       0x0001
#define NCP_RDEV_LOG_INFO        0x0002
#define NCP_RDEV_LOG_MESSAGE     0x0004
#define NCP_RDEV_LOG_DEBUG       0x0008

typedef struct {
    ncp_uint32_t     logMask;
    FILE           *stream;
} ncp_rdev_log_info_t;

/* 
 * logging macros. The LT log macro assumes a local pointer to
 * the server structure. The WT log macro is passed a pointer 
 * to either the session or connection structure, depending on
 * which exist in the calling function
 */
#define NCP_RDEV_SERVER_LT_LOG(ltype, fmt, ...) \
    do { \
        if ((server != NULL) && ((ltype) & (server->logInfo.logMask))) { \
            ncp_rdev_print_timestamp(server->logInfo.stream); \
            fprintf(server->logInfo.stream, "  LT   : "); \
            fprintf(server->logInfo.stream, fmt, ##__VA_ARGS__); \
        } \
    } while (0)

#define NCP_RDEV_SERVER_WT_LOG(ptr, ltype, fmt, ...) \
    do { \
        if ((ltype) & (ptr->logInfo->logMask)) { \
            ncp_rdev_print_timestamp(ptr->logInfo->stream); \
            fprintf(ptr->logInfo->stream, "  WT%1x%1x : ", \
                        ptr->cInfo.sessionId, ptr->cInfo.connId); \
            fprintf(ptr->logInfo->stream, fmt, ##__VA_ARGS__); \
        } \
    } while (0)


/*
 * basic function prototypes 
 */
typedef ncp_st_t (*rdevOpenFn_t) (ncp_uint32_t  devNum,
                                 ncp_uint32_t  flags,
                                 void          **devHdl);

typedef ncp_st_t (*rdevCloseFn_t) (void  *devHdl);

typedef ncp_st_t (*rdevWriteFn_t)(void *        devHdl,
                                 ncp_uint32_t  regionId,
                                 ncp_uint64_t  offset,
                                 ncp_uint32_t  xferWidth,
                                 ncp_uint32_t  count,
                                 ncp_uint32_t  flags,
                                 ncp_uint32_t  cmdType,
                                 ncp_uint32_t  *cmdBuf);

typedef ncp_st_t (*rdevReadFn_t) (void *        devHdl,
                                 ncp_uint32_t  regionId,
                                 ncp_uint64_t  offset,
                                 ncp_uint32_t  xferWidth,
                                 ncp_uint32_t  count,
                                 ncp_uint32_t  flags,
                                 ncp_uint32_t  cmdType,
                                 ncp_uint32_t  *cmdBuf);

/*
 * task structures and function prototypes 
 */

typedef struct _ncp_rdev_task_mdata_t {
    ncp_uint32_t               flowId;
    ncp_uint8_t                vpId;
    ncp_uint16_t               dataSize;
    ncp_uint8_t                priority;
    ncp_bool_t                 debugFieldV;
    ncp_uint32_t               debugData;
    ncp_uint8_t                taskParms[32];
} ncp_rdev_task_mdata_t;

typedef struct _ncp_rdev_task_hdr_t {
    ncp_uint32_t               launchId;
    ncp_uint32_t               destId;
    ncp_uint16_t               TOID;
    ncp_uint16_t               dataSz;
    ncp_uint8_t                QID;
    ncp_uint8_t                taskPrio;
    ncp_uint8_t                paramSz;
    ncp_bool_t                 traceEn;
    ncp_bool_t                 taskErr;
    ncp_bool_t                 bufferSizeErr;
    ncp_uint8_t                bufferSize;
    ncp_bool_t                 debugFieldV;
    ncp_uint8_t               *buffer; /* empty desc + parms + debug + data */
} ncp_rdev_task_hdr_t;

typedef struct _ncp_rdev_task_complete_t {
    ncp_uint16_t               destId;
    ncp_uint16_t               toId;
    ncp_uint16_t               dataSize;
    ncp_uint8_t                queueId;
    ncp_uint8_t                taskPriority;
    ncp_bool_t                 intOnComplete;
    ncp_uint8_t                completionCntInc;
    ncp_bool_t                 nOp;
} ncp_rdev_task_complete_t;

typedef ncp_st_t (*rdevOutputTaskPutFn_t) 
        (void *                  devHdl,
         ncp_uint8_t             nca_oPCQ_id,
         ncp_rdev_task_mdata_t  *pMetaData, 
         void                   *pTaskData,
         ncp_uint32_t             flags);


typedef ncp_st_t (*rdevInputTaskGetFn_t) 
        (void *                  devHdl,
         ncp_uint8_t             nca_iPCQ_id,
         ncp_uint16_t           *outBufferSize,
         ncp_uint8_t            *pTemplateId,
         ncp_uint8_t            *pPduDataStart,
         ncp_rdev_task_hdr_t    *pInputHdr,
         ncp_bool_t             *pTaskErr,
         ncp_uint32_t            flags);

typedef ncp_st_t (*rdevTaskCompletePutFn_t)
        (void *                     devHdl,
         ncp_uint8_t                nca_tPCQ_id,
         ncp_rdev_task_complete_t  *pTaskCompleteData,
         ncp_uint32_t               flags);



/*
 * size of structure allocated to hold information for each 
 * blocking call. 
 * TODO: determine correct size, somewhere ought to make sure 
 * this is sufficient
 */
#define NCP_RDEV_SERVER_CONN_BLOCKING_INFO_SIZE 128


/* forward declaration */
typedef struct _ncp_rdev_server_session_t ncp_rdev_server_session_t;
typedef struct _ncp_rdev_server_t ncp_rdev_server_t;

typedef struct _ncp_rdev_server_conn_t {
    void                        *devHdl;
    ncp_rdev_conn_info_t         cInfo;
    ncp_uint8_t                  active;
    ncp_uint8_t                  shutdown;
    ncp_rdev_log_info_t         *logInfo;

    ncp_rdev_server_t           *server;
    ncp_rdev_server_session_t   *session;

    ncp_thread_t                 workerThread;

    ncp_msg_t                   *inReqMsg;
    ncp_msg_t                   *outRespMsg;

    ncp_uint32_t                 epfd;
    ncp_uint32_t                 devfd;
    fd_set                       read_fds;
#if 0
    fd_set                       write_fds;
    fd_set                       except_fds;
    ncp_uint32_t                 selMask;
#endif
    ncp_uint16_t                 altReturnCode;
    ncp_uint32_t                 timeouts;

    struct _ncp_rdev_server_conn_t  *next;
} ncp_rdev_server_conn_t;

struct _ncp_rdev_server_session_t {
    ncp_uint8_t                  id;
    ncp_uint8_t                  active;
    ncp_uint16_t                 localPort;
    ncp_rdev_conn_info_t         cInfo;
 
    ncp_rdev_log_info_t         *logInfo;
    ncp_int32_t                 numConns;
    ncp_rdev_server_conn_t      *conns;

    ncp_rdev_server_t           *server;

    ncp_rdev_server_session_t   *next;
    ncp_rdev_server_session_t   *prev;
} ;


typedef struct {
    ncp_uint32_t                  totalSessions;
} ncp_rdev_server_stats_t;

struct _ncp_rdev_server_t {
    ncp_uint32_t                  devNum;
    ncp_uint16_t                  basePort;
    ncp_uint16_t                  maxSessions;
    ncp_rdev_conn_info_t          ltConn;
    ncp_sem_t                     sessionLock;
    ncp_rdev_server_session_t    *freeSessionHead;
    ncp_rdev_server_session_t    *freeSessionTail;
    ncp_rdev_server_session_t    *activeSessions;

    ncp_rdev_log_info_t           logInfo;
    ncp_rdev_server_stats_t       stats;
    ncp_bool_t                    timeoutsEnabled;

    rdevOpenFn_t                  openFn;
    rdevCloseFn_t                 closeFn;
    rdevWriteFn_t                 writeFn;
    rdevReadFn_t                  readFn;
    rdevOutputTaskPutFn_t         oTaskPutFn;
    rdevInputTaskGetFn_t          iTaskGetFn;
    rdevTaskCompletePutFn_t       tTaskPutFn;

};


/* function prototypes */

NCP_API ncp_st_t
ncp_rdev_server_listener(ncp_rdev_server_t *server);

NCP_API ncp_st_t
ncp_rdev_server_init(ncp_uint16_t basePort, 
                     ncp_uint32_t devNum, 
                     ncp_uint16_t maxSessions, 
                     ncp_rdev_server_t **newServer);

NCP_API ncp_st_t
ncp_rdev_server_free(ncp_rdev_server_t *server);

NCP_API void * ncp_rdev_server_worker_func(void *arg);

NCP_API ncp_rdev_server_conn_t *
ncp_rdev_server_find_conn_by_event(ncp_rdev_server_session_t *session,
                                  ncp_uint32_t event);
NCP_API ncp_st_t
ncp_rdev_server_send_control_msg(ncp_rdev_conn_info_t *cInfo,
                                ncp_uint8_t sessionId, ncp_uint8_t connId,
                                ncp_uint16_t seqId, ncp_uint16_t msgType,
                                ncp_uint16_t returnCode);

NCP_API ncp_st_t
ncp_rdev_server_send_msg( ncp_rdev_server_conn_t *conn, ncp_uint16_t msgType,
                         ncp_msg_t *msg, ncp_uint32_t nbytes, ncp_uint16_t rc);

NCP_API ncp_st_t
ncp_rdev_server_shutdown(ncp_rdev_server_t *server);


/*
 * Include the chipset specific files for device API function messages
 */

#include <ncp_rdev_sim.h>

#ifdef __cplusplus
}
#endif

#endif
