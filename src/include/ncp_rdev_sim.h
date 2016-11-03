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

#ifndef __ncp_rdev_sim_h__
#define __ncp_rdev_sim_h__

#include <ncp.h>

#define NCP_RDEV_PROCESS_API     ncp_rdev_process_sim_api
#define NCP_RDEV_PROCESS_EVENT   ncp_rdev_process_sim_event

#define NCP_RDEV_DEV_OPEN        ncp_dev_open
#define NCP_RDEV_DEV_HDL_T       ncp_dev_hdl_t
#define NCP_RDEV_DEV_FD_GET      ncp_dev_fd_get

#include <ncp_rdev_sim_msg.h>

NCP_API ncp_st_t
ncp_rdev_process_sim_api(ncp_rdev_server_conn_t    *conn,
                        ncp_rdev_msg_info_t       *minfo);


NCP_API ncp_st_t
ncp_rdev_process_sim_event(ncp_rdev_server_session_t *session);
#endif
