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

#ifndef __ncp_rdev_msg_h__
#define __ncp_rdev_msg_h__

#include <ncp_rdev_if.h>

/* 
 * NCP_RDEV_MAX_MSG_SIZE is the maximum possible message size that
 * that can be sent/received by a user application using the messaging 
 * interface. It is currently limited to 64kB, since the 'msgLength' 
 * field in the rdev header is only 16 bits.
 *
 * NCP_RDEV_MAX_MSG_SIZE may be greater than the maximum packet size
 * supported by the underlying messaging protocol (NCP_MSG_MAX_PACKET_SIZE)
 * A message which is longer than the max packet size will need to
 * be fragmented and reassembled.
 */
#define NCP_RDEV_MAX_MSG_SIZE            (64 * 1024)

/*
 * KeepAlive definitions
 * NCP_RDEV_KEEPALIVE_PERIOD specifies the period (in seconds) at
 * which the client keepalive thread will send keepalive messages
 * to the server. This is also the used as the timeout value used
 * by the server worker thread select call.
 *
 * NCP_RDEV_TIMEOUT_THRESHOLD specifies the number of keepalive periods
 * after which, if no messages have been received, the server will timeout
 * the client session.
 */
#define NCP_RDEV_KEEPALIVE_PERIOD    2
#define NCP_RDEV_TIMEOUT_THRESHOLD   3
    
/*
 * the basic message header. used for both request and response 
 */
typedef struct {
    ncp_uint8_t        sessionId ;
    ncp_uint8_t        connId ;
    ncp_uint16_t       seqId ;

    ncp_uint16_t       msgType ;
    ncp_uint16_t       msgLength ;
    
    ncp_uint8_t        nFrags;
    ncp_uint8_t        fragId;
    ncp_uint8_t        unused;
    ncp_uint8_t        userReq;

    ncp_uint16_t       altRetCode;
    ncp_uint16_t       returnCode ;
} ncp_msg_header_t;

#define NCP_RDEV_MSG_HDR_SIZE  (sizeof(ncp_msg_header_t))


/* 
 * the request and response message structs are defined with a 
 * default data size of NCP_RDEV_MSG_DEFAULT_DATA_WORDS.
 * Small messages may be sent simply by declaring an instance of 
 * the message structure and filling in the data. 
 * For larger messages, the message structure should be malloc'ed 
 * to the appropriate size, effectively increasing the size of 
 * the data field. 
 *
 * NOTE: we have to be careful here, since sizof(ncp_msg_*_t)
 * does not necessarily indicate the size of the message.
 * Might have to redo this...
 */

#define NCP_RDEV_MSG_DEFAULT_DATA_WORDS 8
#define NCP_RDEV_MSG_DEFAULT_DATA_BYTES 4 * NCP_RDEV_MSG_DEFAULT_DATA_WORDS

typedef struct _ncp_msg_t {
    ncp_msg_header_t     hdr;
    ncp_uint32_t         data[NCP_RDEV_MSG_DEFAULT_DATA_WORDS];
} ncp_msg_t;



/* macro to set MSB in response messages */
#define NCP_RDEV_MSG_RESPONSE(m) (m | 0x8000)

/* the special purpose messages */
#define NCP_RDEV_DEVICE_OPEN             0x100
#define NCP_RDEV_DEVICE_CLOSE            0x101

#define NCP_RDEV_CONNECTION_OPEN         0x110
#define NCP_RDEV_CONNECTION_CLOSE        0x111

#define NCP_RDEV_KEEPALIVE               0x120

#define NCP_RDEV_SERVER_SHUTDOWN         0x130

/* a few test messages */
#define NCP_RDEV_LOOPBACK_MSG_1          0x180
#define NCP_RDEV_LOOPBACK_MSG_2          0x181
#define NCP_RDEV_LOOPBACK_MSG_3          0x182
#define NCP_RDEV_LOOPBACK_MSG_4          0x183

/* byte swapping macros */
#ifdef NCP_BIG_ENDIAN

#define NCP_RDEV_SWAP16(n) n
#define NCP_RDEV_SWAP16_BUFFER(p, count)
#define NCP_RDEV_SWAP16_COPY(dst, src, count) \
            memcpy(dst, src, count*sizeof(ncp_uint16_t))

#define NCP_RDEV_SWAP32(n) n
#define NCP_RDEV_SWAP32_BUFFER(p, count)
#define NCP_RDEV_SWAP32_COPY(dst, src, count) \
            memcpy(dst, src, count*sizeof(ncp_uint32_t))

#define NCP_RDEV_SWAP64(n) n
#define NCP_RDEV_SWAP64_BUFFER(p, count)
#define NCP_RDEV_SWAP64_COPY(dst, src, count) \
            memcpy(dst, src, count*sizeof(ncp_uint64_t))

#else
/* byte-swapping for little-endian only */
#define NCP_RDEV_SWAP16(n)  ((n & 0xff00) >> 8 | (n & 0x00ff) << 8)

#define NCP_RDEV_SWAP32(n) ((n & 0xff000000) >> 24 | \
                            (n & 0x00ff0000) >> 8  | \
                            (n & 0x0000ff00) << 8  | \
                            (n & 0x000000ff) << 24)

#define NCP_RDEV_SWAP64(n)   ((((n) & 0xff00000000000000ull) >> 56)  \
                            | (((n) & 0x00ff000000000000ull) >> 40)  \
                            | (((n) & 0x0000ff0000000000ull) >> 24)  \
                            | (((n) & 0x000000ff00000000ull) >> 8)   \
                            | (((n) & 0x00000000ff000000ull) << 8)   \
                            | (((n) & 0x0000000000ff0000ull) << 24)  \
                            | (((n) & 0x000000000000ff00ull) << 40)  \
                            | (((n) & 0x00000000000000ffull) << 56))


#define NCP_RDEV_SWAP16_BUFFER(p, count) \
    do { \
        ncp_uint16_t *__pbuf = (ncp_uint16_t *) p; \
        int i; \
        for (i=0; i<count; i++, __pbuf++) { \
            *__pbuf = NCP_RDEV_SWAP16(*__pbuf); \
        } \
    } while (0);

#define NCP_RDEV_SWAP32_BUFFER(p, count) \
    do { \
        ncp_uint32_t *__pbuf = (ncp_uint32_t *)p; \
        int i; \
        for (i=0; i<count; i++, __pbuf++) { \
            *__pbuf = NCP_RDEV_SWAP32(*__pbuf); \
        } \
    } while (0);

#define NCP_RDEV_SWAP64_BUFFER(p, count) \
    do { \
        ncp_uint64_t *__pbuf = (ncp_uint64_t *)p; \
        int i; \
        for (i=0; i<count; i++, __pbuf++) { \
            *__pbuf = NCP_RDEV_SWAP64(*__pbuf); \
        } \
    } while (0);


#define NCP_RDEV_SWAP16_COPY(dst, src, count) \
    do { \
        int i; \
        ncp_uint16_t *__pDst = (ncp_uint16_t *) dst; \
        ncp_uint16_t *__pSrc = (ncp_uint16_t *) src; \
        for (i=0; i<count; i++, __pSrc++, __pDst++) { \
            *__pDst = NCP_RDEV_SWAP16(*__pSrc); \
        } \
    } while (0);

#define NCP_RDEV_SWAP32_COPY(dst, src, count) \
    do { \
        int i; \
        ncp_uint32_t *__pDst = (ncp_uint32_t *) dst; \
        ncp_uint32_t *__pSrc = (ncp_uint32_t *) src; \
        for (i=0; i<count; i++, __pSrc++, __pDst++) { \
            *__pDst = NCP_RDEV_SWAP32(*__pSrc); \
        } \
    } while (0);

#define NCP_RDEV_SWAP64_COPY(dst, src, count) \
    do { \
        int i; \
        ncp_uint64_t *__pDst = (ncp_uint64_t *) dst; \
        ncp_uint64_t *__pSrc = (ncp_uint64_t *) src; \
        for (i=0; i<count; i++, __pSrc++, __pDst++) { \
            *__pDst = NCP_RDEV_SWAP64(*__pSrc); \
        } \
    } while (0);

#endif


/* interface for the generic send/recv functions */
typedef struct {
    ncp_uint8_t      sessionId;
    ncp_uint8_t      connId;
    ncp_uint16_t     seqId;
    ncp_uint16_t     msgType;
    ncp_uint32_t     msgLength;
    ncp_uint8_t      userReq;
    ncp_uint16_t     altRetCode;
    ncp_uint16_t     returnCode;
} ncp_rdev_msg_info_t;

typedef struct {
    ncp_sock_t        sock;
    ncp_msg_addr_t   *destAddr;
    ncp_uint8_t       sessionId;
    ncp_uint8_t       connId;
    ncp_uint16_t      seqId;
    ncp_uint32_t      nMsgSent;
    ncp_uint32_t      nMsgRcvd;
    ncp_bool_t        timeoutsEnabled;
} ncp_rdev_conn_info_t;


ncp_st_t
ncp_rdev_dump_msg_header(ncp_msg_header_t *pHdr);

ncp_st_t
ncp_rdev_send_msg(ncp_rdev_conn_info_t *cinfo, ncp_rdev_msg_info_t *minfo,
                    ncp_msg_t *msg);

ncp_st_t
ncp_rdev_recv_msg(ncp_rdev_conn_info_t *cinfo, ncp_timespec_t *timeout,
                    ncp_rdev_msg_info_t *minfo, ncp_msg_t *msg);

ncp_st_t
ncp_rdev_send_control_msg(ncp_rdev_conn_info_t *cInfo,
                         ncp_uint16_t msgType,
                         ncp_uint16_t returnCode);

ncp_st_t
ncp_rdev_recv_control_msg(ncp_rdev_conn_info_t *cInfo,
                         ncp_uint16_t expMType,
                         ncp_rdev_msg_info_t *minfo,
                         ncp_timespec_t *timeout);


#endif
