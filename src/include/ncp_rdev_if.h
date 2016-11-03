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

#ifndef __ncp_rdev_if_h__
#define __ncp_rdev_if_h__


/* ncp includes */
#ifdef WIN32
#include <winsock2.h>
#include <io.h>
#include <ws2tcpip.h>
/*
#define inet_pton( af, src, dst ) \
        do { 
              ncp_int32_t sslen = sizeof(dst); \
              WSAStringToAddress( (src), (af), NULL, (dst),  (&sslen) ); \
           } while(0);
*/
#endif

#include <ncp_sal.h>

/* threads and semaphore includes */
#include <pthread.h>
#if 0
#include <semaphore.h>
#endif

#ifndef WIN32

/* socket interface includes */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

/* select interface */
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 128
#endif

#endif

/* various includes for debug purposes */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#ifdef NCP_LEAK_DEBUG
extern void ncp_malloc_leak_init(void);
extern void ncp_malloc_leak_status(void);
#endif


/* 
 * threads and semaphore operations
 */
typedef pthread_t       ncp_thread_t;
typedef pthread_attr_t  ncp_thread_attr_t;
#if 0
typedef sem_t           ncp_sem_t;
#endif

ncp_st_t
ncp_thread_create(ncp_thread_t *thread, ncp_thread_attr_t *attr, 
            void * (*thread_func)(void *), void *arg);

#define ncp_thread_exit(rv)     pthread_exit(rv)
#define ncp_thread_cancel(thr)  pthread_cancel(thr)
#define ncp_thread_testcancel   pthread_testcancel


ncp_thread_t
ncp_thread_get_id(void);

#if 0
ncp_st_t
ncp_sem_init(ncp_sem_t *sem, ncp_int32_t shared, ncp_uint32_t value);

ncp_st_t
ncp_sem_post(ncp_sem_t *sem);

ncp_st_t
ncp_sem_wait(ncp_sem_t *sem);

ncp_st_t
ncp_sem_trywait(ncp_sem_t *sem);

#endif

#if 0
/*
 * select interface 
 */

typedef struct {
    int         maxfd;
    fd_set      read_fds;
    fd_set      write_fds;
    fd_set      except_fds;
} ncp_select_fd_t;

#define NCP_RDEV_SELECT_EVENT_READ   1
#define NCP_RDEV_SELECT_EVENT_WRITE  2
#define NCP_RDEV_SELECT_EVENT_EXCEPT 4
#endif



/* 
 * sockets-based message interface 
 */ 

/* 
 * NCP_MSG_MAX_PACKET_SIZE is the maximum packet size supported by this
 * messageing protocol. For UDP, we limit this to be 8 kB.
 */
#if 1
#define NCP_MSG_MAX_PACKET_SIZE      (8 * 1024)
#else
/* TEMP: try sizing about equal to ethernet frames */
#define NCP_MSG_MAX_PACKET_SIZE     1472
#endif

typedef struct {
    struct in_addr  addr;
    ncp_uint16_t     port;
} ncp_msg_addr_t;

typedef ncp_int32_t ncp_sock_t;

NCP_API ncp_st_t
ncp_sock_init(ncp_sock_t *sock, ncp_uint16_t *port);

NCP_API ncp_st_t
ncp_sock_connect(ncp_sock_t sock, ncp_msg_addr_t *dest);

NCP_API ncp_st_t
ncp_sock_close(ncp_sock_t sock);

NCP_API ncp_st_t
ncp_msg_send(ncp_sock_t sock, char *msg, ncp_uint32_t nbytes);

NCP_API ncp_st_t
ncp_msg_recv(ncp_sock_t sock, char *msg, ncp_uint32_t *bytes_received);


/* mapping function */
NCP_API ncp_st_t
ncp_rdev_map_devNum_to_server(ncp_uint32_t devNum, ncp_msg_addr_t *servAddr);


NCP_API ncp_st_t
ncp_rdev_get_server_from_env(const char *envName, ncp_msg_addr_t *servAddr);

/* timestamp */
NCP_API void ncp_rdev_print_timestamp(FILE *fp);

NCP_API int
ncp_select(int             nfds,
           fd_set         *rfds,
           fd_set         *wfds,
           fd_set         *xfds,
           ncp_timespec_t *timeout);

#endif
