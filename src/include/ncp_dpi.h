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
 ** **************************************************************************/


#ifndef __NCP_DPI_H__
#define __NCP_DPI_H__

#ifdef __cplusplus
extern "C" {
#endif


/*! @file ncp_dpi.h
    @brief Deep Packet Inspection Engine (dpi)
    @addtogroup _dpi_ Deep Packet Inspection
    The APIs provide an interface for applications to comiple ruleset,
    ininitalize DPI block, allocate resources, send scan jobs to the DPI
    engine and process scan results.  This document provides a description of
    each API, including its purpose, parameters, and return values.

    For background information on the RegEx product, basic features, and a
    description of the RegEx compiler and ruleset syntax, refer to the
    POSIX Rule Writer's Guide (POSIX_Rule_Writers_User_Guide.pdf).

    @{
*/


#include "ncp.h"
#include "ncp_types.h"
/*
#include "ncp_vpm.h"
*/
/* Regex configuration */
#define NCP_DPI_MAX_JOBS_BITS      7
#define NCP_DPI_MAX_THREADS        32


/* Global flag defines for scan job */

/* Last packet on a crosspacket stream. */
#define NCP_DPI_JOB_FLAG_LAST_PACKET                  (1 << 0)
/* Recover from a crosspacket error.  Only set this flag on the first 
 * packet of an error recovery sequence.
 */

#define NCP_DPI_JOB_FLAG_RECOVER_FROM_ERROR           (1 << 2)
/* Submit a job to free a LCB.  Most commonly used with a 0-byte job and a stream that is currently holding a LCB. Use \ref rgxStreamHasLCB to detect if a stream is holding a LCB.*/

#define NCP_DPI_JOB_FLAG_FREE_LCB                     (1 << 3)
/* Recover from output overflow error.*/

#define NCP_DPI_JOB_FLAG_RECOVER_FROM_OVERFLOW_ERROR  (1 << 4)
/* Recover from LCB allocation error.*/

#define NCP_DPI_JOB_FLAG_RECOVER_FROM_LCB_ERROR       (1 << 5)
#define NCP_DPI_JOB_FLAG_FORCE_FLUSH                  (1 << 7) 

#define NCP_DPI_SIZE_SCB 0
#define NCP_DPI_NUM_LCB  1


/*! \brief Ruleset data structure used for ruleset loading and updates*/
typedef struct {
    ncp_uint8_t  *data;     /* the ruleset data */
    ncp_uint32_t len;       /* the length of the ruleset data (in bytes) */
    ncp_uint64_t blob;      /* unused */
} ncp_dpi_ruleset_t;

/*! \brief DPI Stream handle returned from ncp_dpi_allocate_stream()*/
typedef ncp_uint32_t ncp_dpi_stream_handle;

/*
    Typedef for enumerations for the different result modes offered
*/
/*! \brief Scan result type enumerations for the different result modes. */
enum ncp_dpi_result_type{NCP_DPI_RESULT_END_PTR       = 1, /*!< Token, Start, End */
                      NCP_DPI_RESULT_START_END_PTRS   = 1, /*!< Token, Start, End */
                      NCP_DPI_RESULT_NO_END_PTR       = 2, /*!< Token, Start */
                      NCP_DPI_RESULT_START_PTR        = 2, /*!< Token, Start */
                      NCP_DPI_RESULT_NO_PTRS          = 3, /*!< Token */
                      NCP_DPI_RESULT_BIT_VECTOR       = 4, /*!< Bit Vector */
                      NCP_DPI_RESULT_NOSTART_PTR      = 5, /*!< Token, End */
                      NCP_DPI_RESULT_EACH_TOKEN_ONCE  = 6  /*!< Each token once*/
};


/* 
    Typedef for enumerations of the different result modes offered
*/

/*! 
  \brief 1-attribute result type (token only) 
*/
typedef ncp_uint32_t  ncp_dpi_result_type1_t;  /* token id */
 

/*!
  \brief 2-attribute result type (token and start pointer)
*/
typedef struct
{
    ncp_uint32_t  id;       /* token id */
    ncp_int32_t  locStart;  /* start pointer */
} ncp_dpi_result_type2_t;

/*!
  \brief 3-attribute result type (token, start pointer, and end pointer)
*/
typedef struct
{
    ncp_uint32_t  id;       /* token id */
    ncp_int32_t  locStart;  /* start pointer */
    ncp_int32_t  locEnd;    /* end pointer     */
} ncp_dpi_result_type3_t;

/*!
  \brief Alternate result type (token id, end pointer)
*/
typedef struct
{
    ncp_uint32_t  id;       /* token id */
    ncp_int32_t  locEnd;    /* end pointer */
} ncp_dpi_result_type4_t;

/*!
  \brief Bit vector result type
*/
typedef ncp_uint32_t ncp_dpi_result_bitvec_type_t;

/*!
  \brief List of pointers to the results.
*/
typedef struct
{
    enum ncp_dpi_result_type type;
    union {
        ncp_dpi_result_type1_t *pat1;      /* array of tokens */
        ncp_dpi_result_type2_t *pat2;      /* array of token and start pointer pairs */
        ncp_dpi_result_type3_t *pat3;      /* array of token, start pointer, and end pointer tuplets */
        ncp_dpi_result_type4_t *pat4;      /* array of token and end pointer pairs */
        ncp_dpi_result_bitvec_type_t *bvec;      /* array of bit vectors */
    } data;
} ncp_dpi_result_list_t;


/*! \brief Result list structure

    This structure is used by the scan APIs to return results for a scan.
*/
typedef struct
{
    enum ncp_dpi_result_type     type;            /* the result type */
    ncp_uint32_t            numResults;           /* the number of matches */
    ncp_dpi_result_list_t     list;               /* the list of matches */
    ncp_uint32_t            outputLen;            /* the output length. */
    ncp_uint32_t            outputOverflowLen;    /* the output overflow length (only applicable on an overflow error) */

    ncp_uint8_t            *buffer;               /* the output buffer */
    ncp_uint32_t            bufferLen;            /* the output buffer length */

    ncp_uint32_t            fullStatus;           /* debug status. */
} ncp_dpi_result_t;


/*! @brief Defines the prototype of user callback function which is called when
           a scan result is returned from DPI engine and processed by the DPI library.
    @param status Status of the scan call. It returns NCP_ST_SUCCESS for success,
           otherwise error code on failure.
    @param result Container for the results.  Includes number of results and list of results.
    @param rgxCallbackParam Pointer to parameter to pass back when the callback function
           is called.
    @retval NCP_ST_SUCCESS On success
    @retval non-zero error code on failure
    @see ncp_dpi_init()
*/
typedef ncp_uint32_t (*ncp_dpi_callback_fn_t)(
               void *rgxCallbackParam, 
               ncp_dpi_result_t *result, 
               ncp_uint32_t status);

/*!
\brief DPI parameter structure. This structure is used by ncp_dpi_config_get()
       to return  the parameters.
*/
typedef struct ncp_dpi_parms_s
{
    ncp_uint32_t     maxOutputLen;
    ncp_uint32_t     numLargeContextRecords;
    ncp_uint32_t     instrMemorySize;
    ncp_uint64_t     instrBaseAddr;
    ncp_uint32_t     xpiMaxNumSCs;
    ncp_uint32_t     scbSize;
}ncp_dpi_parms_t;


/*! @fn ncp_st_t ncp_dpi_config_set(
     ncp_hdl_t ncpHdl,
     ncp_uint8_t opt,
     void *optval)
   @brief This function dynamically sets DPI configuration. The parameters
          that can be set include:
   - Small context buffer size
   - Maximum number of large context buffer
   @param ncpHdl[in] NCP device handle.
   @param opt[in] Identify the parameter to set. Currently supported parameters are
   - NCP_DPI_SIZE_SCB
   - NCP_DPI_NUM_LCB
   @param optval[in] Contains the option value.
   @retval NCP_ST_SUCCESS on success.
   @retval non-zero error code on failure
*/
NCP_API ncp_st_t ncp_dpi_config_set(
    ncp_hdl_t ncpHdl,
    ncp_uint8_t opt,
    void *optval);


/*! @fn ncp_st_t ncp_dpi_config_get(
      ncp_hdl_t ncpHdl,
      ncp_dpi_parms_t *dpiParms)
    @brief This function retrieves the DPI configurations.
    @param ncpHdl[in]  NCP device handle.
    @param dpiParms[out] Pointer to the structure what contains DPI parameters returned.
           The parameters include maximum output length, number of large context buffer records, 
           size of small context buffer, ruleset base address,
           maximum number of small context buffers and result queue polling mode.
    @retval  NCP_ST_SUCCESS on success
    @retval  NCP_ST_DEV_INVALID_BUFFER An invalid pointer was passed in the dpiParms
*/
NCP_API ncp_st_t ncp_dpi_config_get(
   ncp_hdl_t        ncpHdl,
   ncp_dpi_parms_t  *dpiParms);


/*! 
    @brief This function initializes data structures and allocates software queues in the
           DPI module. This function should be called after ACP configuration image is loaded.
    @param ncpHdl[in]  NCP device handle.
    @param taskHdl[in] Task handle returned from ncp_task_hdl_create(). 
    @param ncaIuputQueueId[in] NCA input queue ID. 
    @param ncaOutputQueueId[in] NCA output queue ID. 
    @retval NCP_ST_SUCCESS on success
    @retval non-zero error code on failure
    @see ncp_dpi_shutdown()
*/
NCP_API ncp_st_t ncp_dpi_init( 
    ncp_hdl_t       ncpHdl,  
    ncp_task_hdl_t  taskHdl,
    ncp_uint8_t     ncaIuputQueueId,
    ncp_uint8_t     ncaOutputQueueId); 


/*! @brief This function releases resources allocated by ncp_dpi_init().
    @param ncpHdl[in]  NCP device handle.
    @retval NCP_ST_SUCCESS on success
    @retval non-zero error code on failure
    @see ncp_dpi_init()
*/
NCP_API ncp_st_t ncp_dpi_shutdown( ncp_hdl_t ncpHdl);


/*! 
    @brief This function initializes internal resources including job queue
           specific to a thread for multi-thread applications. The argument
           rgxThreadID is the Id assigned to the initialized thread. It is
           passed to DPI scan functions as an argument, so scan result can
           be associated to the thread that calls the scan function.
    @param ncpHdl[in]  NCP device handle.
    @param dpiThreadID[out] Pointer to thread ID.
    @retval NCP_ST_SUCCESS on success
    @retval non-zero error code on failure
    @see ncp_dpi_thread_deinit()
 */
NCP_API ncp_st_t ncp_dpi_thread_init(
    ncp_hdl_t       ncpHdl,
    ncp_task_hdl_t  taskHdl,
    ncp_uint8_t     recvDpiCpuQueueId,
    ncp_uint32_t    *rgxThreadID);

/*! @fn ncp_st_t ncp_dpi_thread_deinit(
          ncp_hdl_t ncpHdl,
          ncp_uint32_t dpiThreadID);
    @brief This function frees resources and releases the thread handle allocated
           by ncp_dpi_thread_init().
    @param ncpHdl[in]  NCP device handle.
    @param dpiThreadID[in] Thread ID.
    @retval NCP_ST_SUCCESS on success
    @retval non-zero error code on failure
    @see ncp_dpi_thread_init()
 */
NCP_API ncp_st_t ncp_dpi_thread_deinit(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t rgxThreadID);


/*! 
    @brief This function allocates an available small context buffer for
           cross packet scan and returns a stream handle.
    @param ncpHdl[in]  NCP device handle
    @param dpiStreamHandle[out] Pointer to stream handle.
    @retval NCP_ST_SUCCESS on success
    @retval NCP_ST_DPI_INSUFFICIENT_RESOURCES_ERROR No small context buffer is available
    @see ncp_dpi_free_stream()
*/
NCP_API ncp_st_t ncp_dpi_allocate_stream(
    ncp_hdl_t ncpHdl,
    ncp_dpi_stream_handle* rgxStreamHandle);


/*! 
    @brief This function frees the stream handle returned by 
           ncp_dpi_allocate_stream(). The function checks if a XPI stream
           occupies a large XPI context or not.
    @param ncpHdl[in]  NCP device handle.
    @param dpiStreamHandle[in] Pointer to stream handle.
    @param dpiThreadID[in] The thread Id that frees the stream handle.
    @retval NCP_ST_SUCCESS on success
    @retval NCP_DPI_INVALID_STREAM_HANDLE The stream handle passed in is invalid
    @see ncp_dpi_allocate_stream()
*/
NCP_API ncp_st_t ncp_dpi_free_stream(
    ncp_hdl_t ncpHdl,
    ncp_dpi_stream_handle handle,
    ncp_uint32_t rgxThreadID);


/*
 * Ruleset Management Calls
 */

/*!
    @brief This function compiles the textual representation of a ruleset into
      a binary structure. Given a NULL-terminated text string representing the
      ruleset to compile, this function will compile the ruleset, allocate a
      ruleset structure, perform various validations, and store the result in the
      ruleset structure.  These structures should be considered opaque.  As memory
      is dynamically allocated, the resultant ruleset should be deallocated
      via ncp_dpi_free_ruleset().
    @param rgxDoc[in]  A pointer to the ruleset text.
    @param ruleset[out] The resultant ruleset structure.
    @retval NCP_ST_SUCCESS on success.
    @retval NCP_DPI_LIBRARY_NOT_INITIALIZED     DPI RTE module is not initialized.
    @see ncp_dpi_free_ruleset()
 */
NCP_API ncp_st_t ncp_dpi_ruleset_compile(
    char *rgxDoc,
    ncp_dpi_ruleset_t **ruleset );


/*! 
    @brief This funciton incrementally compiles updates to a ruleset using both the updated
           and previous string representations of a ruleset, and the previously
           compiled ruleset.

    Both oldRgxDoc, and newRgxDoc are NULL-terminated text string represenations
    of the rules to compile. oldRgxBin is the binary ruleset file produced by the
    initial compilation. Incremental compilation requires that the previous compile
    was made with the intention of future incremental compiles. To perform the
    intial compilation call this function setting the oldRgxDoc and oldRgxBin as NULL.
    Rulesets produced by such a call are suitable for future incremental compilation.
    A ruleset can be continuously updated by further calls to this API.  This API is
    available for RegEx user-space only.

    There are advantages and disadvantages to using incremental compilation. Rulesets
    with multiple start conditions will benefit the most from incremental compilation
    as compiling such rulesets incrementally will reduce the compilation memory footprint
    and in most cases processing cost. This is even true for the initial compilation.
    The down side is that in some cases the resulting binary ruleset may be larger.

    As with ncp_dpi_compile_ruleset() this function will compile the ruleset, allocate
    a ruleset structure, perform various validations, and store the result in the ruleset
    structure.  These structures should be considered opaque.  As memory
    is dynamically allocated, the resultant ruleset should be deallocated
    via ncp_dpi_free_ruleset().

    @param oldRgxDoc[in] A pointer to the old ruleset text (must be NULL
           for initial compilation).
    @param oldRgxBin[in] A pointer to the old binary ruleset (must be NULL
           for initial compilation).
    @param oldRgxBinLen[in] The length of the oldRgxBin buffer (must be 0
           for initial compilation).
    @param newRgxDoc[in] A pointer to the new ruleset text.
    @param ruleset[out] The resultant ruleset structure.

    @retval NCP_ST_SUCCESS on success
    @retval NCP_DPI_LIBRARY_NOT_INITIALIZED     DPI RTE module is not initialized.

    @see ncp_dpi_free_ruleset()
 */
NCP_API ncp_st_t ncp_dpi_ruleset_incremental_compile(
    char *oldRgxDoc,
    char *oldRgxBin,
    ncp_uint32_t oldRgxBinLen,
    char *newRgxDoc,
    ncp_dpi_ruleset_t **ruleset );


/*! @fn ncp_st_t ncp_dpi_free_ruleset(ncp_dpi_ruleset_t *ruleset)
    @brief Deallocates a ruleset structure created via ncp_dpi_compile_ruleset()
           or ncp_dpi_incremental_compile_rulesets().
    @param ruleset[in] A pointer to the ruleset to deallocate.
    @retval NCP_ST_SUCCESS on success
    @retval NCP_ST_DEV_INVALID_BUFFER An invalid pointer was passed in the ruleset
    @see ncp_dpi_compile_ruleset, ncp_dpi_incremental_compile_rulesets
 */
NCP_API ncp_st_t ncp_dpi_free_ruleset(ncp_dpi_ruleset_t *ruleset);


/*! @fn ncp_st_t ncp_dpi_ruleset_load(
    ncp_hdl_t ncpHdl,
    ncp_uint8_t* rulesetBuf,
    ncp_uint32_t rulesetLen)

    @brief This function loads a compiled ruleset binary. Tables are loaded to the 
           DPI internal memory and instructions are loaded to system memory.

    @param ncpHdl[in]  NCP device handle.
    @param rulesetBuf[in] Pointer to ruleset data buffer.
    @param rulesetLen[in] Length of ruleset.
    @retval NCP_ST_SUCCESS on success
    @retval non-zero error code on failure
    @see ncp_dpi_ruleset_update()
*/
NCP_API ncp_st_t ncp_dpi_ruleset_load(
    ncp_hdl_t ncpHdl,
    ncp_uint8_t* rulesetBuf,
    ncp_uint32_t rulesetLen);


/*! @fn ncp_st_t ncp_dpi_ruleset_update(
    ncp_hdl_t ncpHdl,
    ncp_uint8_t* rulesetBuf,
    ncp_uint32_t rulesetLen)

    @brief This function loads ruleset dynamically to update existing ruleset.

    @param ncpHdl[in]  NCP device handle.
    @param rulesetBuf[in] Pointer to ruleset data buffer.
    @param rulesetLen[in] Length of ruleset.
    @retval NCP_ST_SUCCESS on success
    @retval non-zero error code on failure
    @see ncp_dpi_ruleset_load()
*/
NCP_API ncp_st_t ncp_dpi_ruleset_update(
    ncp_hdl_t ncpHdl,
    ncp_uint8_t* rulesetBuf,
    ncp_uint32_t rulesetLen);

/*
 * Scanning Calls
 */

/*! 
    @brief This function performs a non cross packet and non-blocking scan of an input
           buffer against a compiled and loaded ruleset on a Long-reach engine.
           The load-balancing among available engines is achieved in the COW block,
           and API does not  have any control over it.

    @param ncpHdl[in]  NCP device handle.
    @param  rgxFlags[in] One of the following job flag can be passed in:
            - NCP_DPI_JOB_FLAG_LAST_PACKET
            - NCP_DPI_JOB_FLAG_RECOVER_FROM_ERROR
            - NCP_DPI_JOB_FLAG_RETAIN_PACKET

    @param  rgxThreadID[in] Thread id, as obtained from ncp_dpi_thread_init(),
            for thread performing the scan or 0 for single thread application.
    @param  rgxStartState[in] User specified start condition for the scan.
    @param  rgxBuffer[in] Pointer to input data buffer.
    @param  rgxBufOffset[in] Offset of input data in the data buffer.
    @param  rgxBufSize[in] Input data buffer size.
    @param  rgxResult[in] Pointer to the container holding scan result.
    @param  rgxCallbackParam[in] Pointer to object to be returned as a parameter
            to the function callback.
    @retval NCP_ST_SUCCESS on success
    @retval non-zero error code on failure
*/
NCP_API ncp_st_t  ncp_dpi_scan_non_block(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t rgxFlags,
    ncp_uint32_t rgxThreadID,
    ncp_uint32_t rgxStartState,
    ncp_uint8_t *rgxBuffer,
    ncp_uint32_t rgxBufOffset,
    ncp_uint32_t rgxBufSize,
    ncp_dpi_result_t *rgxResult,
    ncp_dpi_callback_fn_t rgxFpCallback,
    void  *rgxCallbackParam);

#if 0
/*! @fn ncp_st_t  ncp_dpi_scan_block(
    ncp_hdl_t        ncpHdl,
    ncp_uint32_t     rgxFlags,
    ncp_uint32_t     rgxThreadID,
    ncp_uint32_t     rgxStartState,
    ncp_uint8_t      *rgxBuffer,
    ncp_uint32_t     rgxBufOffset,
    ncp_uint32_t     rgxBufSize,
    ncp_dpi_result_t *rgxResult);

    @brief This function performs a blocking non cross packet scan of an input
           buffer against a compiled and loaded ruleset on a Long-reach engine.
           Results are populated in rgxResult. The load-balancing among available
           engines is achieved in the COW block.
    @param ncpHdl[in]  NCP device handle.
    @param rgxFlags[in] One of following job flags can be passed in:
           - NCP_DPI_JOB_FLAG_LAST_PACKET
           - NCP_DPI_JOB_FLAG_RECOVER_FROM_ERROR
           - NCP_DPI_JOB_FLAG_RETAIN_PACKET
    @param rgxThreadID[in] Thread id, as obtained from rgxThreadInit, for thread
           performing the scan or 0 for single thread application.
    @param rgxStartState[in] Start condition for the scan.
    @param rgxBuffer[in] Input buffer.
    @param rgxBufSize[in] Size of input buffer in bytes.
    @param rgxResult[in] Pointer to a container holding the scan results.
    @retval NCP_ST_SUCCESS on success
    @retval non-zero error code on failure
*/
NCP_API ncp_st_t  ncp_dpi_scan_block(
    ncp_hdl_t        ncpHdl,
/*    ncp_task_hdl_t   taskHdl,*/
    ncp_uint32_t     rgxFlags,
    ncp_uint32_t     rgxThreadID,
    ncp_uint32_t     rgxStartState,
    ncp_uint8_t      *rgxBuffer,
    ncp_uint32_t     rgxBufOffset,
    ncp_uint32_t     rgxBufSize,
    ncp_dpi_result_t *rgxResult);
#endif

/*! @brief This function performs non-blocking cross-packet scan of a packet
           against a loaded ruleset on a crosspacket stream allocated via the
           call to ncp_dpi_allocate_stream(). The load-balancing among available
           engines is achieved in the COW block, and the API is not responsible for
           load balancing among engines.
    @param ncpHdl[in]  NCP device handle.
    @param rgxStreamHandle Stream handle of XPI scan.
    @param rgxFlags[in] One of following job flags can be passed in:
           - NCP_DPI_JOB_FLAG_LAST_PACKET
           - NCP_DPI_JOB_FLAG_RECOVER_FROM_ERROR
           - NCP_DPI_JOB_FLAG_RETAIN_PACKET
    @param rgxThreadID[in] Thread id, as obtained from rgxThreadInit, for thread
           performing the scan or 0 for single thread application.
    @param rgxStartState[in] Start condition for the scan.
    @param rgxBuffer[in] Input buffer.
    @param rgxBufSize[in] Size of input buffer in bytes.
    @param rgxResult[in] Pointer to a container holding the scan results.
    @param rgxCallbackParam[in] Pointer to object to be returned as a parameter to
           the function callback.
    @retval NCP_ST_SUCCESS on success
    @retval non-zero error code on failure
    @see ncp_dpi_allocate_stream()
*/
NCP_API ncp_st_t ncp_dpi_scan_xp_non_block(
    ncp_dev_hdl_t devHdl,
    ncp_dpi_stream_handle *rgxStreamHandle,
    ncp_uint32_t rgxFlags,
    ncp_uint32_t rgxThreadID,
    ncp_uint32_t rgxStartState,
    ncp_uint8_t  *rgxBuffer,
    ncp_uint32_t rgxBufOffset,
    ncp_uint32_t rgxBufSize,
    ncp_dpi_result_t *rgxResult,
    ncp_dpi_callback_fn_t rgxFpCallback,
    void *rgxCallbackParam);


/*! @fn ncp_st_t ncp_dpi_task_post(
    ncp_hdl_t ncpHdl,
    ncp_task_recv_buf_t  *task)
    @brief This function posts a scan result task received from DPI engine to the RTE.
           The RTE matches result with packet based on job ID, and invoke user
           callback function registered in the initialization function.
    @param ncpHdl[in]  NCP device handle.
    @param task[in] Pointer to task received by the CPU from the DPI.

    @retval NCP_ST_SUCCESS on success
    @retval non-zero error code on failure
 */
/*
NCP_API ncp_st_t ncp_dpi_task_post(
    ncp_hdl_t ncpHdl,
    ncp_task_recv_buf_t  *task);
*/

/*!
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _NCP_DPI_H_ */
