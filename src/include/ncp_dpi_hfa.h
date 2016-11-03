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
 **    Copyright 2004-2014, Intel Corporation.  All rights reserved.     *
 **                                                                        *
  *  code style options set by astyle as follows with 4 spaces as indentation
  *  astyle --indent=spaces=4 --style=ansi --pad-paren-out  --pad-oper --mode=c
  *
  *  code compiled locally with "make clean debug"
  *  and compiled at the top level as
  *      make -f make.linux-x86 clean mklinks debug install
  *  and make -f make.linux-ep8572 clean  clobber mklinks debug install
  *
  *  Using the following make utility: GNU Make 3.81 This program built for x86_64-redhat-linux-gnu
  *
 ** **************************************************************************/

#ifndef _NCP_DPI_HFA_H_
#define _NCP_DPI_HFA_H_

#ifdef __cplusplus
extern "C" {
#endif

/*! @file ncp_dpi_hfa.h
 *  @brief Deep Packet Inspection Hybrid Finite Automota Engine (dpi_hfa)
 *  @addtogroup _dpi_ Runtime DPI APIs
 *
 *  @detail The APIs provide an interface for applications to compile a ruleset,
 *  initialize the DPI HFA block, allocate resources, send scan jobs to the DPI
 *  engine and process scan results.  This document provides a description of
 *  each API, including its purpose, parameters, and return values.
 *
 *  For background information on the RegEx product, basic features, and a
 *  description of the RegEx compiler and ruleset syntax, refer to the
 *  PCRE Rule Writer's Guide.
 *
 *  @{
*/


/* Regex configuration */

#define NCP_DPI_HFA_MAX_JOBS_BITS      9
#define NCP_DPI_HFA_MAX_THREADS        3

#define NCP_DPI_HFA_JOB_FLAG_LAST_PACKET                  (1 << 0)
/*
 * Recover from a crosspacket error.  Only set this flag on the first packet
 * of an error recovery sequence.
 */
#define NCP_DPI_HFA_JOB_FLAG_RECOVER_FROM_ERROR           (1 << 2)
/* Submit a job to free a LCB.  Most commonly used with a 0-byte job and a stream that is currently holding a LCB. Use \ref rgxStreamHasLCB to detect if a stream is holding a LCB.*/
#define NCP_DPI_HFA_JOB_FLAG_FREE_LCB                     (1 << 3)
/* Recover from output overflow error.*/
#define NCP_DPI_HFA_JOB_FLAG_RECOVER_FROM_OVERFLOW_ERROR  (1 << 4)
/* Recover from LCB allocation error.*/
#define NCP_DPI_HFA_JOB_FLAG_RECOVER_FROM_LCB_ERROR       (1 << 5)

#define   NCP_DPI_HFA_FIRST_RESULT_TYPE        0x0
#define   NCP_DPI_HFA_VECTOR_RESULT_TYPE       0x1
#define   NCP_DPI_HFA_ALL_RESULT_4BYTE_TYPE    0x4
#define   NCP_DPI_HFA_ALL_RESULT_8BYTE_TYPE    0x5
#define   NCP_DPI_HFA_ALL_RESULT_12BYTE_TYPE   0x7
#define   NCP_DPI_HFA_SIZE_SCB                   1
#define   NCP_DPI_HFA_NUM_LCB                    2
#define   NCP_DPI_HFA_NEWLINE_DEFINITION         3


/*! @brief Ruleset data structure */
typedef struct
{
    ncp_uint8_t  *data;     /* the ruleset data */
    ncp_uint32_t len;       /* the length of the ruleset data (in bytes) */
    ncp_uint64_t blob;      /* unused */
} ncp_dpi_hfa_ruleset_t;


/*! @brief DPI Stream handle returned from ncp_dpi_hfa_allocate_stream() */
typedef ncp_uint32_t ncp_dpi_hfa_stream_handle;


/*
    Typedef for enumerations for the different result modes offered
*/
/*! @brief Scan result type enumerations for the different result modes. */
enum ncp_dpi_hfa_result_type
{
    NCP_DPI_HFA_RESULT_SINGLE_RESULT = 0, /*!< Single Result only */
    NCP_DPI_HFA_RESULT_START_END_PTRS   = 1, /*!< Token, Start, End */
    NCP_DPI_HFA_RESULT_NO_END_PTR       = 2, /*!< Token, Start */
    NCP_DPI_HFA_RESULT_START_PTR        = 2, /*!< Token, Start */
    NCP_DPI_HFA_RESULT_NO_PTRS          = 3, /*!< Token */
    NCP_DPI_HFA_RESULT_BIT_VECTOR       = 4, /*!< Bit Vector */
    NCP_DPI_HFA_RESULT_NOSTART_PTR      = 5, /*!< Token, End */
    NCP_DPI_HFA_RESULT_EACH_TOKEN_ONCE  = 6,  /*!< Each token once*/
    NCP_DPI_HFA_RESULT_IDL           = 8, /*!< IDL */
    NCP_DPI_HFA_RESULT_IDL_SP        = 9, /*!< IDL SP */
    NCP_DPI_HFA_RESULT_IDL_EP        = 10, /*!< IDL EP */
    NCP_DPI_HFA_RESULT_IDL_SP_EP     = 11, /*!< IDL SP EP */
    NCP_DPI_HFA_RESULT_IDH_IDL       = 12, /*!< IDH IDL for large token counts */
    NCP_DPI_HFA_RESULT_IDH_IDL_SP    = 13, /*!< IDH IDL SP for large token counts */
    NCP_DPI_HFA_RESULT_IDH_IDL_EP    = 14, /*!< IDH IDL EP for large token counts */
    NCP_DPI_HFA_RESULT_IDH_IDL_SP_EP = 15, /*!< IDH IDL SP EP for large token counts */
};


/*!
 * @brief 1-attribute result type (token only)
 */
typedef ncp_uint32_t  ncp_dpi_hfa_result_type1_t;  /* token id */

/*!
 * @brief 2-attribute result type (token and start pointer)
 */
typedef struct
{
    ncp_uint32_t  id;       /* token id */
    ncp_int32_t  locStart;  /* start pointer */
} ncp_dpi_hfa_result_type2_t;

/*!
 * @brief 3-attribute result type (token, start pointer, and end pointer)
 */
typedef struct
{
    ncp_uint32_t  id;       /* token id */
    ncp_int32_t  locStart;  /* start pointer */
    ncp_int32_t  locEnd;    /* end pointer     */
} ncp_dpi_hfa_result_type3_t;

/*!
 * @brief Alternate result type (token id, end pointer)
 */
typedef struct
{
    ncp_uint32_t  id;       /* token id */
    ncp_int32_t  locEnd;    /* end pointer */
} ncp_dpi_hfa_result_type4_t;

/*!
 * @brief Bit vector result type
 */
typedef ncp_uint32_t ncp_dpi_hfa_result_bitvec_type_t;

/*!
 * @brief List of pointers to the results.
 */
typedef struct
{
    enum ncp_dpi_hfa_result_type type;
    union
    {
        ncp_dpi_hfa_result_type1_t *pat1;      /* array of tokens */
        ncp_dpi_hfa_result_type2_t *pat2;      /* array of token and start pointer pairs */
        ncp_dpi_hfa_result_type3_t *pat3;      /* array of token, start pointer, and end pointer tuplets */
        ncp_dpi_hfa_result_type4_t *pat4;      /* array of token and end pointer pairs */
        ncp_dpi_hfa_result_bitvec_type_t *bvec;      /* array of bit vectors */
    } data;
} ncp_dpi_hfa_result_list_t;

/*! @brief Result list structure
 *
 *  This structure is used by the scan APIs to return results for a scan.
 */
typedef struct
{
    enum ncp_dpi_hfa_result_type     type;            /* the result type */
    ncp_uint32_t            numResults;           /* the number of matches */
    ncp_dpi_hfa_result_list_t     list;               /* the list of matches */
    ncp_uint32_t            outputLen;            /* the output length. */
    ncp_uint32_t            outputOverflowLen;    /* the output overflow length (only applicable on an overflow error) */

    ncp_uint8_t            *buffer;               /* the output buffer */
    ncp_uint32_t            bufferLen;            /* the output buffer length */

    ncp_uint32_t            fullStatus;           /* debug status. */
} ncp_dpi_hfa_result_t;


/*! @brief Defines the prototype of user callback function which is called when
 *         a scan result is returned from DPI engine and processed by the DPI library.
 *  @param status Status of the scan call. It returns NCP_ST_SUCCESS for success,
 *         otherwise error code on failure.
 *  @param result Container for the results.  Includes number of results and list of results.
 *  @param rgxCallbackParam Pointer to parameter to pass back when the callback function
 *         is called.
 *  @retval NCP_ST_SUCCESS On success
 *  @retval non-zero error code on failure
 *  @see ncp_dpi_hfa_init()
 */
typedef void (*ncp_dpi_hfa_callback_fn_t) (
    void                 *rgxCallbackParam,
    ncp_dpi_hfa_result_t     *result,
    ncp_uint32_t         status);


/*!
 * @brief DPI parameter structure. This structure is used by ncp_dpi_hfa_config_get()
 *        to return the configuration.
*/
typedef struct
{
    ncp_uint32_t             maxOutputLen;
    ncp_uint32_t             numLargeContextRecords;
    ncp_uint32_t             instrMemorySize;    /* DFA = Swarm */
    ncp_uint64_t             instrBaseAddr;      /* DFA = Swarm*/
    ncp_uint32_t             NFAinstrMemorySize; /* NFA = Oyster */
    ncp_uint64_t             NFAinstrBaseAddr;   /* NFA = Oyster*/
    ncp_uint32_t             xpiMaxNumSCs;       /* store the subtable num entries */
    ncp_uint32_t             newLineDefinition;
    ncp_uint32_t             burstAddress;

} ncp_dpi_hfa_parms_t;


/*! @fn ncp_st_t ncp_dpi_hfa_config_set(
 *   ncp_hdl_t ncpHdl,
 *   ncp_uint8_t opt,
 *   void *optval)
 * @brief This function dynamically sets the DPI configuration. The parameters
 *        that can be set include:
 * - Small context buffer size
 * - Maximum number of large context buffer
 * @param ncpHdl[in] NCP device handle.
 * @param opt[in] Identify the parameter to set. Currently supported parameters are
 * - NCP_DPI_HFA_NUM_LCB
 * - NCP_DPI_HFA_NEWLINE_DEFINITION as [0 = (0xA), 1 = (0xA or 0xD), 2 = (0xD)
 *
 * @param optval[in] Contains the option value.
 * @retval NCP_ST_SUCCESS on success.
 * @retval NCP_ST_DPI_INVALID_PARAMETER error code on failure
 */
NCP_API ncp_st_t
ncp_dpi_hfa_config_set (
    ncp_hdl_t ncpHdl,
    ncp_uint8_t opt,
    void *optval);


/*! @fn ncp_st_t ncp_dpi_hfa_config_get(
 *    ncp_hdl_t ncpHdl,
 *    ncp_dpi_hfa_parms_t *dpiParms)
 *  @brief This function retrieves the DPI configurations stored in ncp_dpi_hfa_t data structure.
 *  @param ncpHdl[in]  NCP device handle.
 *  @param dpiParms[out] Pointer to the DPI parameters returned. 
 *
 *  @retval  NCP_ST_SUCCESS on success
 *  @retval  NCP_ST_DPI_INVALID_PARAMETER An invalid pointer was passed in the dpiParms
 */
NCP_API ncp_st_t
ncp_dpi_hfa_config_get (
    ncp_hdl_t        ncpHdl,
    ncp_dpi_hfa_parms_t  *dpiParms);


/*!
 *  @brief This function is obsolete on the AXM 55XX device due to changes in the Task software block.
 *         Use ncp_dpi_hfa_init_v2() instead.
 *
 *  @param ncpHdl[in] not used
 *  @param taskHdl[in] not used
 *  @param recvDpiCpuQueueId[in] not used
 *  @param ncaOutputQueueId [in] not used
 *
 *  @retval NCP_ST_SUCCESS on success
 *  @retval error from the register writes during initialization.
 */
NCP_API ncp_st_t
ncp_dpi_hfa_init (
    ncp_hdl_t       ncpHdl,
    ncp_task_hdl_t  taskHdl,
    ncp_uint8_t     recvDpiCpuQueueId,
    ncp_uint8_t     ncaOutputQueueId);

/*!
 *  @brief This function initializes data structures and allocates software queues in the
 *         DPI module. This function should be called after ACP configuration image is loaded to initialize
 *          the DPI software and hardware using the AXM 55XX series Task interface functions.
 *
 *  @param ncpHdl[in]  NCP device handle.
 *  @param taskHdl[in]  Task handle returned from ncp_task_hdl_create() call. A NULL value here will not use the
 *     parameters recvDpiCpuQueueId, vpCookie, vpName, but will use vpHandle. A non null value here will use the values passed
 *     in the parameters recvDpiCpuQueueId, vpCookie, vpName, but will not use vpHandle.
 *  @param recvDpiCpuQueueId[in]  Receive queue ID returned from ncp_task_recv_queue_bind() call.
 *  @param vpCookie [in] if used the virtual pipe handle for the CPU-DPI-CPU pipe, set to null if not used.
 *  @param vpName [in] if used the virtual pipe string name for CPU-DPI-CPU, set to null if not used.
 *  @param vpHandle [in] if used the virtual pipe handle which has already been created, only used if taskHdl == NULL
*
 *  @retval NCP_ST_SUCCESS on success
 *  @retval non-zero error code on failure
 *  @see ncp_dpi_hfa_shutdown()
 */
ncp_st_t ncp_dpi_hfa_init_v2 (
    ncp_hdl_t       ncpHdl,
    ncp_task_hdl_t  taskHdl,
    ncp_uint8_t      recvDpiCpuQueueId,
    ncp_uint64_t    vpCookie,
    char               *vpName,
    ncp_vp_hdl_t vpHandle);

/*! @brief This function releases resources allocated by ncp_dpi_hfa_init().
 *  @param ncpHdl[in]  NCP device handle.
 *  @retval NCP_ST_SUCCESS on success
 *  @retval non-zero error code on failure
 *  @see ncp_dpi_hfa_init()
 */
NCP_API ncp_st_t
ncp_dpi_hfa_shutdown (
    ncp_hdl_t ncpHdl);


/*! @fn ncp_st_t ncp_dpi_hfa_thread_init(
 *         ncp_hdl_t ncpHdl,
 *         ncp_uint32_t *rgxThreadID)
 *  @brief Not Supported
 *  @param ncpHdl[in]  NCP device handle.
 *  @param taskHdl[out] Pointer to thread ID.
 *  @param recvDpiCpuQueueId[in] a preallocated to thread ID.
 *  @param rgxThreadID[out] Pointer to thread ID.
 *
 *  @retval NCP_ST_API_NOT_SUPPORTED
 */
NCP_API ncp_st_t
ncp_dpi_hfa_thread_init (
    ncp_hdl_t       ncpHdl,
    ncp_task_hdl_t  taskHdl,
    ncp_uint8_t     recvDpiCpuQueueId,
    ncp_uint32_t    *rgxThreadID);

/*! @fn ncp_st_t ncp_dpi_hfa_thread_deinit(
 *        ncp_hdl_t ncpHdl,
 *        ncp_uint32_t dpiThreadID);
 *  @brief Not implemented.
 *  @param ncpHdl[in]  NCP device handle.
 *  @param dpiThreadID[in] Thread ID.
 
 *  @retval NCP_ST_API_NOT_SUPPORTED
 *  @see ncp_dpi_hfa_thread_init()
 */
NCP_API ncp_st_t
ncp_dpi_hfa_thread_deinit (
    ncp_hdl_t ncpHdl,
    ncp_uint32_t dpiThreadID);


/*! @fn ncp_st_t ncp_dpi_hfa_allocate_stream(
 *        ncp_hdl_t ncpHdl,
 *        ncp_dpi_hfa_stream_handle* dpiStreamHandle);
 *  @brief This function allocates an available small context buffer for
 *         cross packet scan and returns a stream handle.
 *  @param ncpHdl[in]  NCP device handle
 *  @param dpiStreamHandle[out] Pointer to stream handle.
 *
 *  @retval RGX_SUCCESS on success
 *  @retval NCP_ST_DPI_INVALID_SMALL_CONTEXT_MAX attempt to allocate more than the maximum number of small context blocks, which is set in the ASE GUI crossPacketInspectionMaxStreamId attribute.
 *
 *  @retval NCP_ST_DPI_INSUFFICIENT_RESOURCES_ERROR No small context buffer is available memory limit reached.
 *  @see ncp_dpi_hfa_free_stream()
 */
NCP_API ncp_st_t
ncp_dpi_hfa_allocate_stream (
    ncp_hdl_t ncpHdl,
    ncp_dpi_hfa_stream_handle* dpiStreamHandle);


/*! @fn ncp_st_t ncp_dpi_hfa_free_stream(
 *    ncp_hdl_t ncpHdl,
 *    ncp_dpi_hfa_stream_handle* dpiStreamHandle)
 *  @brief This function free the stream handle returned from
 *         ncp_dpi_hfa_allocate_stream(). 
 *
 *  @param ncpHdl[in]  NCP device handle.
 *  @param dpiStreamHandle[in] Pointer to stream handle.
 *  @retval NCP_ST_SUCCESS on success
 *  @retval NCP_DPI_HFA_INVALID_STREAM_HANDLE The stream handle passed in is invalid
 *  @retval NCP_ST_INVALID_PARAMETER if the stream handle is out of range.
 *  @see ncp_dpi_hfa_allocate_stream()
 */
NCP_API ncp_st_t
ncp_dpi_hfa_free_stream (
    ncp_hdl_t ncpHdl,
    ncp_dpi_hfa_stream_handle);

/*
 * Ruleset Management Calls
 */
/*! @brief This function loads a compiled ruleset binary to the tables in the DPI
 *         internal memory and instructions the system memory configured in the ASE. This function can be used to load the initiali ruleset file and also can be used to load the backup ruleset file which will be hot loaded at run time.
 *
 *  @param ncpHdl[in]  NCP device handle.
 *  @param rulesetBuf[in] Pointer to ruleset data buffer.
 *  @param rulesetLen[in] Length of ruleset.
 *
 *  @retval RGX_SUCCESS on success
 *  @retval NCP_ST_DPI_HFA_INVALID_HDL device handle error
 *  @retval NCP_ST_DPI_INVALID_PARAMETER the input arguments are invalid.
 *  @retval NCP_ST_DPI_INSUFFICIENT_RESOURCES_ERROR out of memory to store the binary ruleset
 *  @retval NCP_ST_DPI_HFA_INVALID_RST_MISSING_OYSTER_OR_V2RST - missing the Oyster or V2 ruleset section.
 *  @retval NCP_ST_DPI_HFA_INVALID_RST_NUMBER_OF_SECTIONS_OOB invalid value of ruleset sections
 *  @retval NCP_ST_DPI_HFA_INVALID_RST_SECTION_TYPE section type value out of range
 *  @retval NCP_ST_DPI_HFA_INVALID_RST_SRAM_OR_BLUT_MISSING - missing either the SRAM or BLUT section.
 *
 *  @see ncp_dpi_hfa_compile_ruleset()
 */
NCP_API ncp_st_t
ncp_dpi_hfa_ruleset_load (
    ncp_hdl_t    ncpHdl,
    ncp_uint8_t* rulesetBuf,
    ncp_uint32_t rulesetLen);

/*! @brief Prepares a ruleset to be loaded using the DMA burst feature
 *  @param ncpHdl[in]  NCP device handle.
 *  @param rulesetBuf[in] Pointer to ruleset data buffer.
 *  @param rulesetLen[in] Length of ruleset.
 *  @retval NCP_ST_SUCCESS on success
 *  @retval NCP_ST_DPI_HFA_INVALID_HDL device handle error
 *  @retval NCP_ST_DPI_INVALID_PARAMETER the input arguments are invalid.
 *  @retval NCP_ST_DPI_INSUFFICIENT_RESOURCES_ERROR out of memory to store the binary ruleset
 *  @retval NCP_ST_DPI_HFA_INVALID_RST_MISSING_OYSTER_OR_V2RST - missing the Oyster or V2 ruleset section.
 *  @retval NCP_ST_DPI_HFA_INVALID_RST_NUMBER_OF_SECTIONS_OOB invalid value of ruleset sections
 *  @retval NCP_ST_DPI_HFA_INVALID_RST_SECTION_TYPE section type value out of range
 *  @retval NCP_ST_DPI_HFA_INVALID_RST_SRAM_OR_BLUT_MISSING - missing either the SRAM or BLUT section.
 *  @see ncp_dpi_hfa_compile_ruleset()
 */
NCP_API ncp_st_t
ncp_dpi_hfa_ruleset_burst_load_prepare(
                                       ncp_hdl_t ncpHdl,
                                       ncp_uint8_t* rulesetBuf,
                                       ncp_uint32_t rulesetLen);

/*! @brief Loads a ruleset using the DMA burst feature
 *  @param ncpHdl[in]  NCP device handle.
 *  @param rulesetBuf[in] Pointer to ruleset data buffer.
 *  @param rulesetLen[in] Length of ruleset.
 *  @retval NCP_ST_SUCCESS on success
 *  @retval NCP_ST_DPI_HFA_INVALID_HDL device handle error
 *  @retval NCP_ST_DPI_INVALID_PARAMETER the input arguments are invalid.
 */
NCP_API ncp_st_t
ncp_dpi_hfa_ruleset_burst_load(
                               ncp_hdl_t ncpHdl,
                               ncp_uint8_t* rulesetBuf,
                               ncp_uint32_t rulesetLen);

/*! @brief This function loads a new ruleset at run time to change the DPI engine rules.
 * The new rule set file must be compiled with the DPI HFA compatible compiler. 
 *
 *
 @code
        #include "ncp_types.h"
        #include "ncp_pvt.h"
        #include "ncp_getopt.h"
        #include "ncp_dpi_hfa.h"
        char           rstFile[512];
        struct stat    stat_buf;
        ncp_uint8_t    *blob;
        ncp_uint32_t   len;
        FILE           *fp;
    
        stat(rstFile, &stat_buf);
		len = stat_buf.st_size;
		blob = malloc( len );
		fp = fopen( rstFile, "rb" );
		fread( blob, len, 1, fp );        
        
        ncp_dpi_hfa_ruleset_update(ncpHdl, blob, len);
                
 @endcode
 *
 *  @param ncpHdl[in]  NCP device handle.
 *  @param rulesetBuf[in] Pointer to ruleset data buffer.
 *  @param rulesetLen[in] Length of ruleset.
 *
 *  @retval RGX_SUCCESS on success
 *  @retval NCP_ST_DPI_HFA_INVALID_HDL device handle error
 *  @retval NCP_ST_DPI_INVALID_PARAMETER the input arguments are invalid.
 *  @retval NCP_ST_DPI_INSUFFICIENT_RESOURCES_ERROR out of memory to store the binary ruleset
 *  @retval NCP_ST_DPI_HFA_INVALID_RST_MISSING_OYSTER_OR_V2RST - missing the Oyster or V2 ruleset section.
 *  @retval NCP_ST_DPI_HFA_INVALID_RST_NUMBER_OF_SECTIONS_OOB invalid value of ruleset sections
 *  @retval NCP_ST_DPI_HFA_INVALID_RST_SECTION_TYPE section type value out of range
 *  @retval NCP_ST_DPI_HFA_INVALID_RST_SRAM_OR_BLUT_MISSING - missing either the SRAM or BLUT section.
 *  @see ncp_dpi_hfa_compile_ruleset()
 */
NCP_API ncp_st_t 
ncp_dpi_hfa_ruleset_update (
    ncp_hdl_t ncpHdl,
    ncp_uint8_t* rulesetBuf,
    ncp_uint32_t rulesetLen);

/*
 * Scanning Calls
 */

/*! @brief This function performs a non cross packet and non-blocking scan of an input
 *         buffer against a compiled and loaded ruleset on a Long-reach engine.
 *         The load-balancing among available engines is achieved in the COW block,
 *         and the API is not responsible for load balancing among engines.
 *
 *  @param ncpHdl[in]  NCP device handle.
 *  @param  rgxFlags[in] One of following job flag can be passed in:
 *          - NCP_DPI_HFA_JOB_FLAG_LAST_PACKET
 *          - NCP_DPI_HFA_JOB_FLAG_RECOVER_FROM_ERROR
 *          - NCP_DPI_HFA_JOB_FLAG_RETAIN_PACKET
 *
 *  @param  rgxThreadID[in] Thread id, as obtained from ncp_dpi_hfa_thread_init(),
 *          for thread performing the scan or 0 for single thread application.
 *  @param  rgxStartState[in] User specified start condition for the scan.
 *  @param  rgxBuffer[in] Pointer to input data buffer.
 *  @param  rgxBufOffset[in] Offset of input data in the data buffer.
 *  @param  rgxBufSize[in] Input data buffer size.
 *  @param  rgxResult[in] Pointer to the container holding scan result.
 *  @param  rgxFpCallback[in]
 *  @param  rgxCallbackParam[in] Pointer to object to be returned as a parameter
 *          to the function callback.
 *
 *  @retval RGX_SUCCESS on success
 *  @retval non-zero error code on failure
 */
NCP_API ncp_st_t
ncp_dpi_hfa_scan_non_block (
    ncp_hdl_t                 ncpHdl,
    ncp_uint32_t              rgxFlags,
    ncp_uint32_t              rgxThreadID,
    ncp_uint32_t              rgxStartState,
    ncp_uint8_t               *rgxBuffer,
    ncp_uint32_t              rgxBufOffset,
    ncp_uint32_t              rgxBufSize,
    ncp_dpi_hfa_result_t      *rgxResult,
    ncp_dpi_hfa_callback_fn_t rgxFpCallback,
    void                      *rgxCallbackParam);


/*! @brief This function performs a blocking non cross packet scan of an input
 *         buffer against a compiled and loaded ruleset on a Long-reach engine.
 *         Results are populated in rgxResult. The load-balancing among available
 *         engines is achieved in the COW block.
 *
 *  @param ncpHdl[in]  NCP device handle.
 *  @param rgxFlags[in] One of following job flags can be passed in:
 *         - NCP_DPI_HFA_JOB_FLAG_LAST_PACKET
 *         - NCP_DPI_HFA_JOB_FLAG_RECOVER_FROM_ERROR
 *         - NCP_DPI_HFA_JOB_FLAG_RETAIN_PACKET
 *  @param rgxThreadID[in] Thread id, as obtained from rgxThreadInit, for thread
 *         performing the scan or 0 for single thread application.
 *  @param rgxStartState[in] Start condition for the scan.
 *  @param rgxBuffer[in] Input buffer.
 *  @param rgxBuffOffset[in]
 *  @param rgxBufSize[in] Size of input buffer in bytes.
 *  @param rgxResult[in] Pointer to a container holding the scan results.
 *
 *  @retval RGX_SUCCESS on success
 *  @retval non-zero error code on failure
 */
NCP_API ncp_st_t
ncp_dpi_hfa_scan_block (
    ncp_hdl_t            ncpHdl,
    ncp_uint32_t         rgxFlags,
    ncp_uint32_t         rgxThreadID,
    ncp_uint32_t         rgxStartState,
    ncp_uint8_t          *rgxBuffer,
    ncp_uint32_t         rgxBufOffset,
    ncp_uint32_t         rgxBufSize,
    ncp_dpi_hfa_result_t *rgxResult);


/*! @brief This function performs non-blocking cross-packet scan of a packet
 *         against a loaded ruleset on a crosspacket stream allocated via the
 *         call to ncp_dpi_hfa_allocate_stream(). The load-balancing among available
 *         engines is achieved in the COW block, and the API is not responsible for
 *         load balancing among engines.
 *
 *  @param devHdl[in]  NCP device handle.
 *  @param rgxStreamHandle Stream handle of XPI scan.
 *  @param rgxFlags[in] One of following job flags can be passed in:
 *         - NCP_DPI_HFA_JOB_FLAG_LAST_PACKET
 *         - NCP_DPI_HFA_JOB_FLAG_RECOVER_FROM_ERROR
 *         - NCP_DPI_HFA_JOB_FLAG_RETAIN_PACKET
 *  @param rgxThreadID[in] Thread id, as obtained from rgxThreadInit, for thread
 *         performing the scan or 0 for single thread application.
 *  @param rgxStartState[in] Start condition for the scan.
 *  @param rgxBuffer[in] Input buffer.
 *  @param rgxBufOffset[in]
 *  @param rgxBufSize[in] Size of input buffer in bytes.
 *  @param rgxResult[in] Pointer to a container holding the scan results.
 *  @param rgxFpCallback[in] Pointer to object to be returned as a parameter to
 *         the function callback.
 *  @param rgxCallbackParam[in]
 *
 *  @retval RGX_SUCCESS on success
 *  @retval non-zero error code on failure
 *  @see ncp_dpi_hfa_allocate_stream()
 */
NCP_API ncp_st_t
ncp_dpi_hfa_scan_xp_non_block (
    ncp_dev_hdl_t             devHdl,
    ncp_dpi_hfa_stream_handle *rgxStreamHandle,
    ncp_uint32_t              rgxFlags,
    ncp_uint32_t              rgxThreadID,
    ncp_uint32_t              rgxStartState,
    ncp_uint8_t               *rgxBuffer,
    ncp_uint32_t              rgxBufOffset,
    ncp_uint32_t              rgxBufSize,
    ncp_dpi_hfa_result_t      *rgxResult,
    ncp_dpi_hfa_callback_fn_t rgxFpCallback,
    void                      *rgxCallbackParam);

/*!
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _NCP_DPI_HFA_H_ */
