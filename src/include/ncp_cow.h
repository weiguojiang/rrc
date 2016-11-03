/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*! @file      ncp_cow.h
 *  @brief     COW and Task Tracing features
 * 
 *  @addtogroup _cow_ Common Task Management
 * 
 *  @{
 */
#ifndef _NCP_COW_H_
#define _NCP_COW_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ncp_sal.h"


/* 
 * Enum of HW engines in acp. The enum numbers from eioa0 thru tdmioa needs to be 
 * same as it matches HW dest type. 
 * expander needs to be next to mtm as thats how config file has it.
 */

/* 
 * @enum ncp_engine_type_t
 * @brief Enum of HW engines.
 */
typedef enum ncp_engine_type_e {
    ncp_engine_min      = 0,    /*!< Min value. Not used. */
    ncp_engine_eioa0    = 1,    /*!< eioa0 engine. */
    ncp_engine_timer    = 2,    /*!< timer engine. */
    ncp_engine_pab      = 3,    /*!< pab engine. */
    ncp_engine_mpp      = 4,    /*!< mpp engine. */
    ncp_engine_spp      = 5,    /*!< spp engine. */
    ncp_engine_sed      = 6,    /*!< sed engine. */
    ncp_engine_cpu      = 7,    /*!< cpu engine. */
    ncp_engine_dpi      = 8,    /*!< dpi engine. */
    ncp_engine_pic      = 9,    /*!< pic engine. */
    ncp_engine_mtm      = 10,   /*!< mtm engine. */
    ncp_engine_expander = 11,   /*!< expander engine. */
    ncp_engine_eioa1    = 12,   /*!< eioa1 engine. */
    ncp_engine_isb      = 13,   /*!< isb engine. */
    ncp_engine_tdmioa   = 14,   /*!< tdmioa engine. */
    ncp_engine_isbs     = 15,   /*!< isbs engine. */
    ncp_engine_eioa2    = 16,   /*!< eioa2 engine. */
    ncp_engine_eioa3    = 17,   /*!< eioa3 engine. */
    ncp_engine_eioa4    = 18,   /*!< eioa4 engine. */
    ncp_engine_eioa5    = 19,   /*!< eioa5 engine. */
    ncp_engine_eioa6    = 20,   /*!< eioa6 engine. */
    ncp_engine_eioa7    = 21,   /*!< eioa7 engine. */
    ncp_engine_max              /*!< Max engine value. Not used. */
} ncp_engine_type_t;

/* 
 * Data type definitions 
 */

/*! 
 *
 *  @}
 *
 *  @addtogroup _task_trace_ Task Tracing
 * 
 *  @{
 */
 
typedef struct ncp_task_trace_entry_s ncp_task_trace_entry_t;

/*!
 * @brief Data structure for Task Trace log entries
 */
struct ncp_task_trace_entry_s {
    /*!
     * @brief Size in bytes of this trace log entry.  Can be 32 or 128.
     */
    ncp_uint8_t entrySize;
    /*!
     * @brief Trace log entry outgoing timestamp.  Valid from 0 to ((2^64) - 1).
     */
    ncp_uint64_t timestamp;
    /*!
     * @brief Corresponding task header for trace log entry
     */
    ncp_byte_string_t taskHeader;
    /*!
     * @brief Trace log entry Next Task Data field
     */
    ncp_byte_string_t nextTaskData;
};

/* APIs */

/*! @fn ncp_st_t ncp_task_trace_enable(ncp_hdl_t ncpHdl, ncp_engine_type_t engine)
    @brief Enables task tracing for the specified engine, using the statically 
           configured parameters.  (Not supported on 55xx.)
    @param ncpHdl Incoming handle of the current NCP device
    @param engine The engine for which the Nuevo Trace Facility is being enabled
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_COW_INVALID_ENGINE The engine specified is invalid
    @retval NCP_ST_COW_NOT_TASK_LOG_DEBUG_MODE The top-level debug mode does not allow task logging
    @retval NCP_ST_COW_TASK_TRACE_ALREADY_ENABLED Task tracing is already enabled for this engine
    @retval NCP_ST_API_NOT_SUPPORTED Task tracing is not supported on this platform
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_task_trace_enable(ncp_hdl_t ncpHdl,
                      ncp_engine_type_t engine);

/*! @fn ncp_st_t ncp_task_trace_disable(ncp_hdl_t ncpHdl, ncp_engine_type_t engine)
    @brief Disables task tracing for the specified engine.  (Not supported on 55xx.)
    @param ncpHdl Incoming handle of the current NCP device
    @param engine The engine for which the Nuevo Trace Facility is being disabled
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_COW_INVALID_ENGINE The engine specified is invalid
    @retval NCP_ST_COW_NOT_TASK_LOG_DEBUG_MODE The top-level debug mode does not allow task logging
    @retval NCP_ST_COW_TASK_TRACE_ALREADY_DISABLED Task tracing is already disabled for this engine
    @retval NCP_ST_API_NOT_SUPPORTED Task tracing is not supported on this platform
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_task_trace_disable(ncp_hdl_t ncpHdl,
                       ncp_engine_type_t engine);

/*! @fn ncp_st_t ncp_task_trace_trigger_enable(ncp_hdl_t ncpHdl, ncp_engine_type_t engine)
    @brief Enables triggering for task tracing in the specified engine.  Once enabled, the
           trigger conditions specified in ncp_task_trace_trigger_set() must be satisfied
           for tracing to occur.  If triggering is already enabled for this engine, the match
           count is reset.  (Not supported on 55xx.)
    @param ncpHdl Incoming handle of the current NCP device
    @param engine The engine for which triggering for task tracing is being enabled
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_COW_INVALID_ENGINE The engine specified is invalid
    @retval NCP_ST_COW_NOT_TASK_LOG_DEBUG_MODE The top-level debug mode does not allow task logging
    @retval NCP_ST_API_NOT_SUPPORTED Task tracing is not supported on this platform
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_task_trace_trigger_enable(ncp_hdl_t ncpHdl,
                              ncp_engine_type_t engine);

/*! @fn ncp_st_t ncp_task_trace_trigger_disable(ncp_hdl_t ncpHdl, ncp_engine_type_t engine)
    @brief Disables triggering for task tracing in the specified engine.  Once disabled,
           task tracing can occur as long as tracing is enabled, regardless of the trigger
           conditions.  (Not supported on 55xx.)
    @param ncpHdl Incoming handle of the current NCP device
    @param engine The engine for which triggering for task tracing is being disabled
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_COW_INVALID_ENGINE The engine specified is invalid
    @retval NCP_ST_COW_NOT_TASK_LOG_DEBUG_MODE The top-level debug mode does not allow task logging
    @retval NCP_ST_COW_TASK_TRACE_TRIGGER_ALREADY_DISABLED Triggering for tis engine is already disabled
    @retval NCP_ST_API_NOT_SUPPORTED Task tracing is not supported on this platform
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_task_trace_trigger_disable(ncp_hdl_t ncpHdl,
                               ncp_engine_type_t engine);

/*! @fn ncp_st_t ncp_task_trace_trigger_set(ncp_hdl_t ncpHdl, ncp_engine_type_t engine,
                 ncp_bool_t countMatches, ncp_uint32_t countThreshold, ncp_bool_t triggerStart,
                 ncp_byte_string_t taskHeaderPattern, ncp_byte_string_t taskParamPattern,
                 ncp_byte_string_t taskHeaderMask, ncp_bool_t taskParamMask[8],
                 ncp_uint8_t taskParamByteAddr[8])
    @brief Configures the trace trigger condition for the Nuevo Trace Facility of the specified engine.  (Not supported on 55xx.)
    @param ncpHdl Incoming handle of the current NCP device
    @param engine The engine for which triggering for task tracing is being configured
    @param countMatches Specifies if trigger is set after counting pattern matches (TRUE) or pattern
                        mismatches (FALSE)
    @param countThreshold The number of pattern matches/mismatches counted before setting the trigger
    @param triggerStart Specifies whether to start (TRUE) or stop (FALSE) triggering when the countThreshold
                        is reached
    @param taskHeaderPattern The byte pattern to which the task header is compared for match/mismatch
    @param taskParamPattern The byte pattern to which portions of the task parameters are compared for
                            match/mismatch
    @param taskHeaderMask Bitmask for the task header bit comparisons.  If a bit is set, it is ignored for
                          comparison.
    @param taskParamMask The ith entry of this boolean array specifies whether or not the ith byte of the
                         taskParamPattern is masked for comparison
    @param taskParamByteAddr The byte offset into the merged output parameters of the task for the byte to
                             be compared to the ith byte of the taskParamPattern.  Must be between 0 and 127.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_COW_INVALID_ENGINE The engine specified is invalid
    @retval NCP_ST_COW_NOT_TASK_LOG_DEBUG_MODE The top-level debug mode does not allow task logging
    @retval NCP_ST_COW_TASK_TRACE_INVALID_PARAM_OFFSET A task parameter byte offset is out of range
    @retval NCP_ST_API_NOT_SUPPORTED Task tracing is not supported on this platform
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_task_trace_trigger_set(ncp_hdl_t ncpHdl,
                           ncp_engine_type_t engine,
                           ncp_bool_t countMatches,
                           ncp_uint32_t countThreshold,
                           ncp_bool_t triggerStart,
                           ncp_byte_string_t taskHeaderPattern,
                           ncp_byte_string_t taskParamPattern,
                           ncp_byte_string_t taskHeaderMask,
                           ncp_bool_t taskParamMask[8],
                           ncp_uint8_t taskParamByteAddr[8]);

/*! @fn ncp_st_t ncp_task_trace_buffer_get(ncp_hdl_t ncpHdl, ncp_engine_type_t engine,
        ncp_task_trace_entry_t *entryList, ncp_uint32_t startEntry,
        ncp_uint32_t maxEntries, ncp_uint32_t *numEntries)
    @brief Facilitates the retrieval and analysis of the trace buffer of the specified engine.  (Not supported on 55xx.)
    @param ncpHdl Incoming handle of the current NCP device
    @param engine The engine whose trace buffer is being retrieved
    @param entryList Returned array of task trace buffer entries
    @param startEntry The index of the first entry to return
    @param maxEntries The maximum number of trace buffer entries to return
    @param numEntries The actual number of trace buffer entries returned
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_COW_INVALID_ENGINE The engine specified is invalid
    @retval NCP_ST_COW_NOT_TASK_LOG_DEBUG_MODE The top-level debug mode does not allow task logging
    @retval NCP_ST_INVALID_VALUE The startEntry is outside of the valid range of log entries
    @retval NCP_ST_API_NOT_SUPPORTED Task tracing is not supported on this platform
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_task_trace_buffer_get(ncp_hdl_t ncpHdl,
                          ncp_engine_type_t engine,
                          ncp_task_trace_entry_t *entryList,
                          ncp_uint32_t startEntry,
                          ncp_uint32_t maxEntries,
                          ncp_uint32_t *numEntries);


/*! @fn ncp_st_t ncp_task_trace_buffer_clear(ncp_hdl_t ncpHdl, ncp_engine_type_t engine)
    @brief Clears the trace buffer of the specified engine.  (Not supported on 55xx.)
    @param ncpHdl Incoming handle of the current NCP device
    @param engine The engine whose trace buffer is being cleared
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_COW_INVALID_ENGINE The engine specified is invalid
    @retval NCP_ST_COW_NOT_TASK_LOG_DEBUG_MODE The top-level debug mode does not allow task logging
    @retval NCP_ST_API_NOT_SUPPORTED Task tracing is not supported on this platform
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_task_trace_buffer_clear(ncp_hdl_t ncpHdl,
                            ncp_engine_type_t engine);

/*! 
 *
 *  @}
 *
 *  @addtogroup _cow_ Common Task Management
 * 
 *  @{
 */

/*! @fn ncp_st_t ncp_cow_queue_discard_stats_get(ncp_hdl_t ncpHdl, 
                                ncp_engine_type_t engine, 
                                ncp_uint32_t destInstance, 
				                ncp_uint8_t taskPriority,
                                ncp_uint32_t *discardStats)
    @brief Returns the discard stats for the given engine/destInstance/taskPriority.
    @param[in] ncpHdl Incoming handle of the current NCP device
    @param[in] engine The engine to read the discard stats. 
    @param[in] destInstance The destination instance to read the discard stats.
               The values to be provided as below.
               TIMER, MPP, SED, PIC, PAB, SPP, DPI:
                   All Chips: destInstance = 0.
               MTM:
                   All Chips: destInstance = 0, 1.
               TDMIOA:
                   AXM25xx only: destInstance = 0.
               EIOA:
                   ACP344x, AXX25xx: 1-4,8-12.
                   ACP342x, AXX35xx: 1-4,9-12.
                   AXX55xx: 0-4,16-20,32,33,48,49,64,65,80,81,96,97,112,113.
               NCA:
                   Task Queues:
                       ACP344x: destInstance = 0-23.
                       ACP342x: destInstance = 0-15.
                       AXX25xx: destInstance = 0-11.
                       AXX35xx: destInstance = 0-31.
                       AXX55xx: destInstance = 0-63.
                   Logical Queues:
                       All Chips: 128-135.
    @param[in] taskPriority The task priority to read the discard stats.
               Valid values are 0-7.
    @param[out] discardStats Pointer to ncp_uint32_t where discard stats is stored.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_COW_INVALID_ENGINE The engine specified is invalid or not present in this chip.
    @retval NCP_ST_COW_INVALID_DEST_INST The destInstance param is invalid.
    @retval NCP_ST_COW_INVALID_PRIORITY The taskPriority param is invalid.
    @retval NCP_ST_COW_INVALID_DISCARD_STATS_BUFFER The discardStats param is invalid.
*/
NCP_API ncp_st_t
ncp_cow_queue_discard_stats_get(ncp_hdl_t ncpHdl, 
                                ncp_engine_type_t engine, 
                                ncp_uint32_t destInstance, 
				                ncp_uint8_t taskPriority,
                                ncp_uint32_t *discardStats);

/*!
 * @brief struct for priority to queue index mapping.
 * @see ncp_cow_priority_to_queue_index_map_get
 */

typedef struct ncp_cow_queue_index_map_st {
	ncp_uint8_t queueIndex[8]; /*!< queue index per priority. */
}  ncp_cow_queue_index_map_t;

/*! @fn ncp_st_t ncp_cow_priority_to_queue_index_map_get(ncp_hdl_t ncpHdl, 
                                        ncp_engine_t engine,
                                        ncp_uint32_t destInstance,
                                        ncp_uint8_t *queueIndexMap)
    @brief Returns the queue indexes for the given engine/destInstance.
    @param[in] ncpHdl Incoming handle of the current NCP device
    @param[in] engine The engine to read the queue index. 
    @param[in] destInstance The destination instance to read the queue index. 
               The values to be provided as below.
               TIMER, MPP, SED, PIC, PAB, SPP, DPI:
                   All Chips: destInstance = 0.
               MTM:
                   All Chips: destInstance = 0, 1.
               TDMIOA:
                   AXM25xx only: destInstance = 0.
               EIOA:
                   ACP344x, AXX25xx: 1-4,8-12.
                   ACP342x, AXX35xx: 1-4,9-12.
                   AXX55xx: 0-4,16-20,32,33,48,49,64,65,80,81,96,97,112,113.
               NCA:
                   Task Queues:
                       ACP344x: destInstance = 0-23.
                       ACP342x: destInstance = 0-15.
                       AXX25xx: destInstance = 0-11.
                       AXX35xx: destInstance = 0-31.
                       AXX55xx: destInstance = 0-63.
                   Logical Queues:
                       All Chips: 128-135.
    @param[out] queueIndexMap Pointer to ncp_cow_queue_index_map_t where 
                queue indexes are stored.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_COW_INVALID_ENGINE The engine specified is invalid or not present in this chip.
    @retval NCP_ST_COW_INVALID_DEST_INST The destInstance param is invalid.
    @retval NCP_ST_COW_INVALID_QUEUE_INDEX_MAP_BUFFER The queueIndexMap param is invalid.
*/
NCP_API ncp_st_t
ncp_cow_priority_to_queue_index_map_get(ncp_hdl_t ncpHdl, 
                                        ncp_engine_type_t engine,
                                        ncp_uint32_t destInstance,
                                        ncp_cow_queue_index_map_t *queueIndexMap);

#ifdef __cplusplus
}
#endif

/*! 
 *
 *  @}
 *
 */

#endif /* #ifndef _NCP_TASK_TRACE_H_ */
