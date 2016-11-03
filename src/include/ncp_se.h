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
/*! @file      ncp_se.h
 *  @brief     State Engine (se)
 * 
 *  @addtogroup _se_ State Engine
 * 
 *  @{
 */


#ifndef __NCP_SE_H__
#define __NCP_SE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Defines and macros */

/*!
 * @brief Statistics FEM type
 */
#define NCP_SE_FEM_TYPE_STAT        0
/*!
 * @brief Compute Engine FEM type
 */
#define NCP_SE_FEM_TYPE_CE          1

/*!
 * @brief Used to determine if the FEM function is Statistics or Compute Engine type
 */
#define NCP_SE_FEM_EVENT_TYPE(fcnId) \
    ( ( ( (fcnId) < 64)                       ||        \
        ( ( (fcnId) >= 128) && ( (fcnId) < 192)))   ?   \
    NCP_SE_FEM_TYPE_CE : NCP_SE_FEM_TYPE_STAT)

/*!
 * @brief Used to convert an FPL ID to Namespace index and offset
 */
#define NCP_SE_FPLID_TO_INDEX(fplId,index,offset) \
    do                                            \
    {                                             \
        (index) = ( (fplId) >> 8);                \
        (offset) = ( (fplId) & 0xff);             \
    } while (0)

/* Typedefs */

typedef struct ncp_se_fem_event_s ncp_se_fem_event_t;
typedef struct ncp_se_fem_stat_data_s ncp_se_fem_stat_data_t;
typedef struct ncp_se_fem_ce_data_s ncp_se_fem_ce_data_t;

/*!
 * @brief Data structure used to store FEM attributes
 */
struct ncp_se_fem_stat_data_s
{
    /*!
     * @brief Event 1 is valid
     */
    ncp_bool_t event1Valid;
    /*!
     * @brief Event 1 is an overflow event
     */
    ncp_bool_t event1isOvf;
    /*!
     * @brief Event 2 is valid
     */
    ncp_bool_t event2Valid;
    /*!
     * @brief Event 2 is an overflow event
     */
    ncp_bool_t event2isOvf;
};

/*!
 * @brief Data structure used to store event data for CE FEM events
 */
struct ncp_se_fem_ce_data_s
{
    ncp_uint32_t ceRegFileWordC;
    ncp_uint32_t ceRegFileWordD;
};

/*!
 * @brief Data structure used to store FEM event data
 */
struct ncp_se_fem_event_s
{
    /*!
     * @brief The Function ID for the event
     */
    ncp_uint8_t fcnId;
    /*!
     * @brief The event data for the event
     */
    union
    {
        ncp_se_fem_stat_data_t stat;
        ncp_se_fem_ce_data_t   ce;
    } data;
    /*!
     * @brief FPL Index 1 for the FEM event
     */
    ncp_uint32_t fplIndex1;
    /*!
     * @brief FPL Index 2 for the FEM event
     */
    ncp_uint32_t fplIndex2;
};

/* APIs */

/*! @fn ncp_st_t ncp_se_state_get(ncp_hdl_t ncpHdl, ncp_uint32_t tableIndex,
        ncp_uint8_t entryOffset, ncp_byte_string_t outBuffer)
    @brief Read an entry from indexed CE and ALU state memory
    @param ncpHdl Incoming handle of the current NCP device
    @param tableIndex The 24-bit Namespace index for the requested MPPStateEngine entry.
           This index must correspond to a valid MPPStateEngine entry established during
           configuration.
    @param entryOffset Starting byte offset into entry for request.  The entryOffset must
           be chosen such that the request does not exceed the boundary of the Namespace
           table entry.
    @param outBuffer Client buffer into which the entry is written.  The
           buffer size (outBuffer.len) should be chosen such that it matches
           the number of bytes requested.  It is subject to the constraint that
           (outBuffer.len + entryOffset <= entrySize), where entrySize is the
           configured entry size of the Namespace referred to by tableIndex.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_NS_ENTRY_ID_INVALID tableIndex points to an invalid Namespace entry
    @retval NCP_ST_DEV_INVALID_BUFFER An invalid pointer was passed in the outBuffer field
    @retval NCP_ST_SE_INVALID_HANDLE The SE module was not properly configured
    @retval NCP_ST_SE_INVALID_MLT_REQUEST_SIZE Data was requested outside of the table entry data range
    @retval NCP_ST_SE_INVALID_MLT_INDEX The tableIndex corresponds to an invalid subtable (bits 31:24 are nonzero).
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_se_state_get(
                 ncp_hdl_t ncpHdl,
                 ncp_uint32_t tableIndex,
                 ncp_uint8_t entryOffset,
                 ncp_byte_string_t outBuffer);

/*! @fn ncp_st_t ncp_se_state_set(ncp_hdl_t ncpHdl, ncp_uint32_t tableIndex,
        ncp_uint8_t entryOffset, ncp_byte_string_t inBuffer)
    @brief Write an entry to indexed CE and ALU state memory
    @param ncpHdl Incoming handle of the current NCP device
    @param tableIndex The 24-bit Namespace index for the requested entry.
           This index must correspond to a valid MPPStateEngine entry established during
           configuration.
    @param entryOffset Starting byte offset into entry for request.  The entryOffset must
           be chosen such that the request does not exceed the boundary of the Namespace
           table entry.
    @param outBuffer Client buffer from which the entry is written.  The
           buffer size (inBuffer.len) should be chosen such that it matches
           the number of bytes requested.  It is subject to the constraint that
           (inBuffer.len + entryOffset <= entrySize), where entrySize is the
           configured entry size of the Namespace referred to by tableIndex.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_NS_ENTRY_ID_INVALID tableIndex points to an invalid Namespace entry
    @retval NCP_ST_DEV_INVALID_BUFFER An invalid pointer was passed in the inBuffer field
    @retval NCP_ST_SE_INVALID_HANDLE The SE module was not properly configured
    @retval NCP_ST_SE_INVALID_MLT_REQUEST_SIZE Data was specified outside of the table entry data range
    @retval NCP_ST_SE_INVALID_MLT_INDEX The tableIndex corresponds to an invalid subtable (bits 31:24 are nonzero).
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_se_state_set(
                 ncp_hdl_t ncpHdl,
                 ncp_uint32_t tableIndex,
                 ncp_uint8_t entryOffset,
                 ncp_byte_string_t inBuffer);

/*! @fn ncp_st_t ncp_se_state_block_get(ncp_hdl_t ncpHdl, ncp_uint32_t tableIndex,
        ncp_uint8_t entryOffset, ncp_uint32_t numEntries, ncp_byte_string_t outBuffer)
    @brief Read one or more entries from indexed CE and ALU state memory
    @param ncpHdl Incoming handle of the current NCP device
    @param tableIndex The 24-bit Namespace index for the requested MPPStateEngine entry.
           This index must correspond to a valid MPPStateEngine entry established during
           configuration.
    @param entryOffset Starting byte offset into entry for request.  The entryOffset must
           be chosen such that the request does not exceed the boundary of the Namespace
           table entry.
    @param numEntries The number of entries requested.
    @param outBuffer Client buffer into which the entries are written.  The
           buffer size (outBuffer.len) should be chosen such that it matches
           the number of bytes requested.  It is subject to the constraint that
           (outBuffer.len + entryOffset <= entrySize*numEntries), where entrySize
           is the configured entry size of the Namespace referred to by tableIndex.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_NS_ENTRY_ID_INVALID tableIndex points to an invalid Namespace entry
    @retval NCP_ST_DEV_INVALID_BUFFER An invalid pointer was passed in the outBuffer field
    @retval NCP_ST_SE_INVALID_HANDLE The SE module was not properly configured
    @retval NCP_ST_SE_INVALID_MLT_REQUEST_SIZE Data was requested outside of the table entry data range
    @retval NCP_ST_SE_INVALID_MLT_INDEX The requested block is not contained in a single subtable
    @retval NCP_ST_SE_NS_NOT_CONTIGUOUS The targeted namespace does not have contiguous entries
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_se_state_block_get(
                       ncp_hdl_t ncpHdl,
                       ncp_uint32_t tableIndex,
                       ncp_uint8_t entryOffset,
                       ncp_uint32_t numEntries,
                       ncp_byte_string_t outBuffer);


/*! @fn ncp_st_t ncp_se_fem_event_get(ncp_hdl_t ncpHdl,
        ncp_se_fem_event_t *events, ncp_uint32_t maxEvents,
        ncp_uint32_t *numEvents, ncp_bool_t wait)
    @brief Read entries from the function event manager
    @param ncpHdl Incoming handle of the current NCP device
    @param events Pointer to the first entry of the output function event array
    @param maxEvents The maximum number of events to capture
    @param numEvents The returned number of captured events
    @param wait Specifies blocking (wait==TRUE) or non-blocking (wait==FALSE)
                operation
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_DEV_INVALID_BUFFER An invalid pointer was passed in the numEvents or events field
    @retval NCP_ST_SE_INVALID_HANDLE The SE module was not properly configured
    @retval NCP_ST_SE_INVALID_FEM_POINTER The function event manager is in an unknown state
    @retval NCP_ST_SE_FEM_NOT_ENABLED The function event manager is not enabled
    @retval NCP_ST_SE_FEM_EVENT_QUEUE_FLUSHED The event queue was near capacity, and was flushed without processing
    @retval NCP_ST_* Lower level NCP device access error codes
*/

NCP_API ncp_st_t
ncp_se_fem_event_get(
                     ncp_hdl_t ncpHdl,
                     ncp_se_fem_event_t *events,
                     ncp_uint32_t maxEvents,
                     ncp_uint32_t *numEvents,
                     ncp_bool_t wait);

#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

/*!
 * @}
 */

#endif /* __NCP_SE_H__ */
