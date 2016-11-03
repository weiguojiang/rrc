/**************************************************************************
 **                                                                        *
 **                           Intel CONFIDENTIAL           *
 **                                                                        *
 **                       PROPRIETARY NOTE                                 *
 **                                                                        *
 **    This software contains information confidential and proprietary     *
 **    to Intel Corporation.  It shall not be reproduced in whole or in  *
 **    part, or transferred to other documents, or disclosed to third      *
 **    parties, or used for any purpose other than that for which it was   *
 **    obtained, without the prior written consent of Intel Corporation. *
 **    (c) 2008-2014, Intel Corporation.  All rights reserved.           *
 **                                                                        *
 **
 **  
 **************************************************************************/
/*! @file      ncp_sysmem.h
 *  @brief     System Memory
 * 
 *  @addtogroup _sysmem_ System Memory
 * 
 *  @{
 */


#ifndef __NCP_SYSMEM_H__
#define __NCP_SYSMEM_H__

#include "ncp.h"

/*
 * External Memory MBIST interface
 */

typedef enum {
    NCP_MBIST_CMEM_TEST_PATTERN_REGS = 0,
    NCP_MBIST_CMEM_TEST_PATTERN_ADDR,
    NCP_MBIST_CMEM_TEST_PATTERN_WALKING_ONES,
    NCP_MBIST_CMEM_TEST_PATTERN_WALKING_ZEROS
} ncp_mbist_cmem_test_pattern_t;

typedef enum {
    NCP_MBIST_CMEM_TEST_DISABLE = 0,
    NCP_MBIST_CMEM_TEST_ONE_SHOT,
    NCP_MBIST_CMEM_TEST_CONTINUOUS
} ncp_mbist_cmem_test_enable_t;

typedef enum {
    NCP_MBIST_INACTIVE = 0,
    NCP_MBIST_ACTIVE,
    NCP_MBIST_TERMINATED,
    NCP_MBIST_SUCCESS,
    NCP_MBIST_FAILURE
} ncp_mbist_status_t;

/*! @struct ncp_mbist_fault_t
 *  @brief Address and data values for MBIST fault 
 */
typedef struct {
    /*! @brief upper address bits */
    ncp_uint32_t    addr_h;
    /*! @brief lower address bits */
    ncp_uint32_t    addr_l;
    /*! @brief expected data values */
    ncp_uint32_t    expected[4];
    /*! @brief actual data values */
    ncp_uint32_t    actual[4];
} ncp_mbist_fault_t;

/*! @struct ncp_mbist_cmem_parms_t
 *  @brief parameters for CMEM MBIST
 */
typedef struct {
    /*! @brief the API will initiate the test and user polls for completion */
    ncp_bool_t                      user_polled;
    /*! @brief mix writes and reads, based on block size  */
    ncp_uint8_t                     mixed_mode;
    /*! @brief number of reads/writes before switching in mixed mode */
    ncp_uint8_t                     block_size;
    /*! @brief 0: stop on first failure, 1: continue after failure  */
    ncp_uint8_t                     fail_mode;
    /*! @brief upper 32-bit value of user provided data pattern */
    ncp_uint32_t                    test_data_h;
    /*! @brief lower 32-bit value of user provided data pattern */
    ncp_uint32_t                    test_data_l;
    /*! @brief enable CMEM MBIST */
    ncp_mbist_cmem_test_enable_t    test_enable;
    /*! @brief test pattern for MBIST test */
    ncp_mbist_cmem_test_pattern_t   test_pattern;
    /*! @brief status of MBIST test */
    ncp_mbist_status_t              status;
    /*! @brief MBIST test fault data */
    ncp_mbist_fault_t               fault;
} ncp_mbist_cmem_parms_t;


typedef enum {
    NCP_MBIST_SMEM_TEST_DISABLE = 0,
    NCP_MBIST_SMEM_TEST_DATA,
    NCP_MBIST_SMEM_TEST_ADDR
} ncp_mbist_smem_test_enable_t;

/*! @struct ncp_mbist_smem_parms_t
 *  @brief parameters for SMEM MBIST
 */
typedef struct {
    /*! @brief the API will initiate the test and user polls for completion */
    ncp_bool_t                      user_polled;
    /*! @brief enable SMEM data or address MBIST */
    ncp_uint32_t                    test_enable;
    /*! @brief specify memory size (max address) for MBIST test */
    ncp_uint32_t                    mem_size_MB;
    /*! @brief specify starting address for MBIST test */
    ncp_uint64_t                    start_addr;
    /*! @brief status of MBIST test */
    ncp_mbist_status_t              status;
    /*! @brief MBIST test fault data */
    ncp_mbist_fault_t               fault;
} ncp_mbist_smem_parms_t;


/*! 
 *  @brief  Check status and get results for CMEM MBIST 
 *
 *  @param[in]      ncpHdl    user handle for this ACP instance
 *  @param[in]      memId     ID of the CMEM to test (i.e. 0 for CMEM0, etc.)
 *  @param[in/out]  parms     CMEM BIST parameters and result structure
 *  @param[in]      logFp     optional file pointer for additional logging 
 *
 *  @return Error Codes:
 *      /li ::NCP_ST_INVALID_HANDLE
 *      /li ::NCP_ST_INVALID_PARAMETER
 *
 */
NCP_API ncp_st_t
ncp_mbist_cmem_result(
        ncp_hdl_t                ncpHdl,
        ncp_uint32_t             memId,
        ncp_mbist_cmem_parms_t  *parms,
        FILE                    *logFp);

/*! 
 *  @brief  Initiate CMEM MBIST 
 *
 *  @param[in]      ncpHdl    user handle for this ACP instance
 *  @param[in]      memId     ID of the CMEM to test (i.e. 0 for CMEM0, etc.)
 *  @param[in/out]  parms     CMEM BIST parameters and result structure
 *  @param[in]      logFp     optional file pointer for additional logging 
 *
 *  @return Error Codes:
 *      /li ::NCP_ST_INVALID_HANDLE
 *      /li ::NCP_ST_INVALID_PARAMETER
 *
 */
NCP_API ncp_st_t
ncp_mbist_cmem(
        ncp_hdl_t                ncpHdl,
        ncp_uint32_t             memId,
        ncp_mbist_cmem_parms_t  *parms,
        FILE                    *logFp);

/*! 
 *  @brief  Check status and get results for SMEM MBIST 
 *
 *  @param[in]      ncpHdl    user handle for this ACP instance
 *  @param[in]      memId     ID of the SMEM to test (i.e. 0 for SMEM0, etc.)
 *  @param[in/out]  parms     SMEM BIST parameters and result structure
 *  @param[in]      logFp     optional file pointer for additional logging 
 *
 *  @return Error Codes:
 *      /li ::NCP_ST_INVALID_HANDLE
 *      /li ::NCP_ST_INVALID_PARAMETER
 *
 */
NCP_API ncp_st_t
ncp_mbist_smem_result(
        ncp_hdl_t                ncpHdl,
        ncp_uint32_t             memId,
        ncp_mbist_smem_parms_t  *parms,
        FILE                    *logFp);

/*! 
 *  @brief  Initiate SMEM MBIST 
 *
 *  @param[in]      ncpHdl    user handle for this ACP instance
 *  @param[in]      memId     ID of the SMEM to test (i.e. 0 for SMEM0, etc.)
 *  @param[in/out]  parms     SMEM BIST parameters and result structure
 *  @param[in]      logFp     optional file pointer for additional logging 
 *
 *  @return Error Codes:
 *      /li ::NCP_ST_INVALID_HANDLE
 *      /li ::NCP_ST_INVALID_PARAMETER
 *
 */
NCP_API ncp_st_t
ncp_mbist_smem(
        ncp_hdl_t                ncpHdl,
        ncp_uint32_t             memId,
        ncp_mbist_smem_parms_t  *parms,
        FILE                    *logFp);

/*! 
 *  @brief  Start software-based ZQ calibration routine
 *
 *  @param[in]      hdl       user handle for this ACP instance
 *  @param[in]      timerInterval  Duration of interval between ZQCS commands
 *
 *  @return Error Codes:
 *      /li ::NCP_ST_INVALID_HANDLE
 *      /li ::NCP_ST_SYSMEM_INVALID_HANDLE
 *      /li ::NCP_ST_INVALID_PARAMETER
 *      /li ::NCP_ST_API_NOT_SUPPORTED
 *
 */
NCP_API ncp_st_t
ncp_sm_treemem_zq_calibrate_start(
        ncp_hdl_t                hdl,
        ncp_uint32_t             timerInterval);

/*! 
 *  @brief  Stop software-based ZQ calibration routine
 *
 *  @param[in]      hdl       user handle for this ACP instance
 *
 *  @return Error Codes:
 *      /li ::NCP_ST_INVALID_HANDLE
 *      /li ::NCP_ST_SYSMEM_INVALID_HANDLE
 *      /li ::NCP_ST_API_NOT_SUPPORTED
 *
 */
NCP_API ncp_st_t
ncp_sm_treemem_zq_calibrate_stop(
                                 ncp_hdl_t                hdl);

/*! 
 *  @brief  Start hardware-based auto ZQ calibration routine
 *
 *  @param[in]      hdl       user handle for this ACP instance
 *  @param[in]      timerInterval  Duration of interval between ZQCS commands
 *
 *  @return Error Codes:
 *      /li ::NCP_ST_INVALID_HANDLE
 *      /li ::NCP_ST_SYSMEM_INVALID_HANDLE
 *      /li ::NCP_ST_INVALID_PARAMETER
 *      /li ::NCP_ST_API_NOT_SUPPORTED
 *
 */
NCP_API ncp_st_t
ncp_sm_treemem_autozq_start(
                            ncp_hdl_t                hdl,
                            ncp_uint32_t             timerInterval);

/*! 
 *  @brief  Stop hardware-based auto ZQ calibration routine
 *
 *  @param[in]      hdl       user handle for this ACP instance
 *
 *  @return Error Codes:
 *      /li ::NCP_ST_INVALID_HANDLE
 *      /li ::NCP_ST_SYSMEM_INVALID_HANDLE
 *      /li ::NCP_ST_API_NOT_SUPPORTED
 *
 */
NCP_API ncp_st_t
ncp_sm_treemem_autozq_stop(
                           ncp_hdl_t                hdl);

#endif
