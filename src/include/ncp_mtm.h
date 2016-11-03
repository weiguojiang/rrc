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

/*! @file      ncp_mtm.h
 *  @brief     Modular Traffic Manager
 *             
 *             Modular Traffic Manager APIs, defines and structure definitions.
 *             The MTM API calls provide the ability to add. delete, query
 *             and modify MTM nodes (schedulers and queues).
 * 
 *  @addtogroup _mtm_ Modular Traffic Manager
 * 
 *  @{
 */


#ifndef _NCP_MTM_H_
#define _NCP_MTM_H_

#ifdef __cplusplus
extern "C" {
#endif


/* Public Definitions */
/*! 
 * @brief 24 bit value for the root scheduler ID.
 */
#define NCP_MTM_ROOT_SCHED_ID       (0x00FFFFFF)

/*! 
 * @brief   Value to be used as a parent ID when a queue is going to be
 *          "parked".  All incomming tasks for the queue will be dropped
 *          until it is moved to an existing parent scheduler.
 */
#define NCP_MTM_PARKING_SCHED_ID    (0xFFFFFFFF)

/*! 
 * @brief   Value to be used for the TSscriptID when a scheduler will not be
 *          running a TS script.
 */
#define NCP_MTM_NO_TS_SCRIPT        (0x000000FF)

/*! 
 * @brief   Value to be used for the sharedPramId when a queue will not be
 *          specifying the shared parameter block in the queue structure.
 */
#define NCP_MTM_NO_SHARED_PARAM_ID  (0x00FFFFFF)

/*! 
 * @brief Value to be used for the bpDestIndex when a queue or scheduler does
 * not need to be a backpressure destination.
 */
#define NCP_MTM_NO_BP_DEST          (0x0F000000)

/*! 
 * @brief Value to be used for the timeScale field when a queue or scheduler
 * wants the API to determine the time scale that will be used.
 */
#define NCP_MTM_TIME_SCALE_AUTO     (-1)

/*! 
 * @brief The maximum number of scheduler script parameter bytes.
 */
#define NCP_MTM_MAX_SCHEDULER_PARAMS        16

/*! 
 * @brief The maximum number of queue script parameter bytes.
 */
#define NCP_MTM_MAX_QUEUE_PARAMS            32

/*! 
 * @brief The maximum number of queue script parameter bytes when the queue
 * is using the internal HW shaper for scheduling.
 */
#define NCP_MTM_MAX_QUEUE_PARAMS_HW_SCHED   16

/*! 
 * @brief The maximum number of queue script parameter bytes when the queue
 * is using TS compute engine for scheduling.
 */
#define NCP_MTM_MAX_QUEUE_PARAMS_SW_SCHED   32

/*! 
 * @brief The maximum number queue shared parameter bytes.
 */
#define NCP_MTM_MAX_SHARED_PARAMS           32

/*! 
 * @brief The maximum number of global parameter bytes for the TM and TS
 * compute engines.
 */
#define NCP_MTM_MAX_CE_GLOBAL_PARAMS        16



/* Public Enumerated Types */
/*!
 * @brief Arbtration Modes
 *
 *    Specifies the algoritim that will be used when a parent scheduler
 *    is arbitrating its children. There are 3 modes, each of which can be
 *    implemented by the internal hardware or by the TS CE script. The modes
 *    are smooth deficit weighted round robin (SDWRR), deficit weighted round
 *    robin (DWRR) and strict.  All the children of a parent scheduler must
 *    be in a schedulig mode that matches the arbitration mode of the parent.
 *    A parent scheduler that is using strict arbitration mode can only have
 *    a total of four children, one at each of the priority levels P0-P3.
 */
typedef enum ncp_mtm_arbitration_mode_e
{
    NCP_MTM_ARB_SDWRR = 0,      /*!< Smooth Deficit Weighted Round Robin */
    NCP_MTM_ARB_SDWRR_SCRIPT,   /*!< Script Managed SDWRR */
    NCP_MTM_ARB_DWRR,           /*!< Deficit Weighted Round Robin */
    NCP_MTM_ARB_DWRR_SCRIPT,    /*!< Script Managed DWRR */
    NCP_MTM_ARB_STRICT,         /*!< Strict Priority */
    NCP_MTM_ARB_STRICT_SCRIPT,  /*!< Script Managed Strict Priority */
    NCP_MTM_ARB_MAX = NCP_MTM_ARB_STRICT_SCRIPT
} ncp_mtm_arbitration_mode_t;

/*!
 * @brief Scheduling Modes
 *
 *    Specifies the type of scheduling for the queue or scheduler node.
 *    The modes are smooth deficit weighted round robin (SDWRR), deficit
 *    weighted round robin (DWRR) and one of 4 strict priority levels
 *    (STRICT_P0 to STRICT_P3).  P0 is the highest priority.  There can
 *    only exist one node at each of the strict priority levels.
 */
typedef enum ncp_mtm_scheduling_mode_e
{
    NCP_MTM_SCHED_SDWRR = 0,    /*!< Smooth Deficit Weighted Round Robin */
    NCP_MTM_SCHED_DWRR,         /*!< Deficit Weighted Round Robin */
    NCP_MTM_SCHED_STRICT_P0,    /*!< Strict Priority Level 0 */
    NCP_MTM_SCHED_STRICT_P1,    /*!< Strict Priority Level 1 */
    NCP_MTM_SCHED_STRICT_P2,    /*!< Strict Priority Level 2 */
    NCP_MTM_SCHED_STRICT_P3,    /*!< Strict Priority Level 3 */
    NCP_MTM_SCHED_MAX = NCP_MTM_SCHED_STRICT_P3
} ncp_mtm_scheduling_mode_t;

/*!
 * @brief Shaping Modes
 *
 *    Specifies the rate shaping algorithm for the queue or scheduler node.
 */
typedef enum ncp_mtm_shaping_mode_e
{
    NCP_MTM_SHAPING_NONE = 0,   /*!< The shaper is turned off */
    NCP_MTM_SHAPING_PR,         /*!< Peak rate only */
    NCP_MTM_SHAPING_PR_SR,      /*!< Peak and sustained rate */
    NCP_MTM_SHAPING_PR_MR,      /*!< Peak and minimum rate */
    NCP_MTM_SHAPING_SCRIPT,     /*!< Shaping performed by the TS CE script */
    NCP_MTM_SHAPING_MAX = NCP_MTM_SHAPING_SCRIPT
} ncp_mtm_shaping_mode_t;


/*!
 * @brief Rate Rounding Algorithms
 *
 *    Specifies the rate rounding algorithm to use.
 */
typedef enum ncp_mtm_rounding_alg_e
{
    NCP_MTM_ROUNDING_ALG_NEAREST = 0,   /*!< Closest value > or < */
    NCP_MTM_ROUNDING_ALG_CEILING,       /*!< Closest value >= requested value */
    NCP_MTM_ROUNDING_ALG_FLOOR,         /*!< Closest value <= requested value */
    NCP_MTM_ROUNDING_ALG_MAX = NCP_MTM_ROUNDING_ALG_FLOOR
} ncp_mtm_rounding_alg_t;


/*!
 * @brief Generic structure to map enum strings to/from integer values
 */
typedef struct ncp_mtm_pair_s {
    const char               *enumStr;
    ncp_uint32_t             enumVal;
} ncp_mtm_pair_t;

/*!
 *  @brief  convvert from a string to an enumerated type integer.
 */
NCP_API ncp_st_t
ncp_mtm_pair_str_to_int(ncp_mtm_pair_t *pairs, 
                        const char *enumStr,
                        ncp_uint32_t *outVal);

/*!
 *  @brief  convvert from a an enumerated type integer to a string.
 */
NCP_API ncp_st_t
ncp_mtm_pair_int_to_str(ncp_mtm_pair_t *pairs, 
                        ncp_uint32_t enumVal,
                        const char **outStr);

/* Public Structures */

/*!
 * @brief MTM global statistics.
 */
typedef struct ncp_mtm_global_stats_s
{
    /*! @brief  The number of tasks received */
    ncp_uint32_t    tasksReceived;
    /*! @brief  The number of tasks received with QID set to 0xFFFFFF */
    ncp_uint32_t    tasksDroppedQid;
    /*! @brief  The number of tasks accepted by the traffic manager */
    ncp_uint32_t    tasksAcceptedTm;
    /*! @brief  The number of tasks dropped by the traffic manager */
    ncp_uint32_t    tasksDroppedTm;
    /*!
     * @brief   The number of tasks dropped by the traffic manager because
     *          the TM script set the drop predicate.
     */
    ncp_uint32_t    tasksDroppedTmCePred;
    /*! @brief  The number of tasks received with an invalid queue index */
    ncp_uint32_t    tasksDroppedInvalidQid;
    /*!
     * @brief   The number of tasks dropped by the traffic manager because
     *          the number of 2KB blocks was lower than the set threshold.
     */
    ncp_uint32_t    tasksDroppedTm2kbLow;
    /*!
     * @brief   The number of tasks dropped by the traffic manager because
     *          the task queue was full.
     */
    ncp_uint32_t    tasksDroppedTmTaskQueueFull;
    /*!
     * @brief   The number of tasks dropped by the traffic manager because
     *          the TM script end status had and error.
     */
    ncp_uint32_t    tasksDroppedTmCeError;
    /*! @brief  The number of tasks transmitted */
    ncp_uint32_t    tasksTransmitted;
    /*! @brief  The number of tasks dropped by the traffic shaper */
    ncp_uint32_t    tasksDroppedTs;
    /*! @brief  The number 2KB blocks in use */
    ncp_uint32_t    memBlocksInUse;
    /*! @brief  The number tasks dropped because of an invalid parent ID */
    ncp_uint32_t    tasksDroppedInvalidParent;
    /*!
     * @brief   The number of tasks dropped by the traffic shaper because
     *          the TS script had and error.
     */
    ncp_uint32_t    tasksDroppedTsCeError;
    /*! @brief  The number tasks dropped by the multicast engine */
    ncp_uint32_t    tasksDroppedMulticast;
    /*! @brief  The number tasks dropped because of enqueue drain */
    ncp_uint32_t    tasksDroppedEnqueueDrain;
    /*! @brief  The number tasks dropped because of dequeue drain */
    ncp_uint32_t    tasksDroppedDequeueDrain;
} ncp_mtm_global_stats_t;

/*!
 * @brief MTM per node statistics.
 */
typedef struct ncp_mtm_node_stats_s
{
    /*! @brief  The number of 256 byte blocks in use by the node */
    ncp_uint32_t        memBlocksInUse;
    /*! @brief  The number of packets - only valid for queue nodes */
    ncp_uint32_t        packetCount;
    /*! @brief  The node's script parameters. */
    ncp_byte_string_t   scriptParams;
} ncp_mtm_node_stats_t;

/*!
 * @brief Specification for a queue shared parameter block.
 */
typedef struct ncp_mtm_shared_param_s
{
    /*! @brief  The parameter ID, usually obtained from the resource manager.*/
    ncp_uint32_t                sharedParamId;
    /*! @brief  Byte string specifying the initial value of the parameters. */
    ncp_byte_string_t           paramValue;
} ncp_mtm_shared_param_t;

/*!
 * @brief Specification of shaping rates.
 */
typedef struct ncp_mtm_shaping_rate_s
{
    /*! @brief  The peak shaping rate in bits per second.*/
    ncp_uint64_t                peakRate;
    /*! @brief  Peak bucket size in bytes. */
    ncp_uint32_t                peakBucketSize;
    /*!
     * @brief   Secondary shaping rate in bits per second.  Depending on the
     *          shaping mode of the node, the secondary rate can be either a
     *          sustained rate or a minimum rate.
     */
    ncp_uint64_t                secondaryRate;
    /*! @brief  Secondary bucket size in bytes */
    ncp_uint32_t                secondaryBucketSize;
    /*!
     * @brief   The maximum packet size for any packet going through
     *          the node.
     */
    ncp_uint32_t                maxPacketSize;
} ncp_mtm_shaping_rate_t;

/*!
 * @brief Specification of a scheduler node.
 */
typedef struct ncp_mtm_scheduler_s
{
    /*! @brief  The ID of this scheduler */
    ncp_uint32_t                schedId;
    /*! @brief  The ID of the parent scheduler. */
    ncp_uint32_t                parentId;
    /*! @brief  The arbitration mode of this scheduler. */
    ncp_mtm_arbitration_mode_t  arbitrationMode;
    /*! @brief  The scheduling mode of this scheduler. */
    ncp_mtm_scheduling_mode_t   schedulingMode;
    /*! @brief  The shaping mode of this scheduler. */
    ncp_mtm_shaping_mode_t      shapingMode;
    /*! @brief  The shaping rates for this scheduler.  This field does not
     *          apply if the scheduler is in script shaping mode.
     */
    ncp_mtm_shaping_rate_t      *shapingRates;
    /*! @brief  In WRR scheduling modes, the deficit weighted round robin
     *          limit.  In STRICT scheduling mode, the starvation avoidance
     *          limit.  A value of 0 in STRICT scheduling mode turns the
     *          starvation avoidence function off.  Value is in bytes.
     */
    ncp_uint32_t                serviceQuantum;
    /*! @brief  The identifier of one of the static backpressure destinations.
     *          ASE code generation creates #define values for thesse BP
     *          destinations in the C header file.  If the scheduler is not
     *          going to be backpressured, set this field to NCP_MTM_NO_BP_DEST.
     */
    ncp_uint32_t                bpDestIndex;
    /*! @brief  The length correction to be applied to the calculated
     *          packet length.
     */
    ncp_int8_t                  lengthCorrection;
    /*! @brief  Indicates if the 2 byte output ID should be populated 
     *          with parameter bytes 0-1 from this level. */
    ncp_bool_t                  outputIdSelect;
    /*! @brief  Specify how time is scaled.  Ranges from 0 to 15. Set to
     *          NCP_MTM_TIME_SCALE_AUTO for the API to determine the best
     *          value.  In a hardware shaping mode, AUTO will use the smallest
     *          time scale possible for the selected shaping rates.  In script
     *          shaping mode, AUTO will set the scale to 2 (no time scaling).
     */
    ncp_int8_t                  timeScale;
    /*! @brief  The ID of the traffic shaping script.  If a shaping script
     *          will not be running, set to NCP_MTM_NO_TS_SCRIPT.
     */
    ncp_uint8_t                 tsScriptId;
    /*! @brief  The scheduler script parameters. */
    ncp_byte_string_t           scriptParams;
} ncp_mtm_scheduler_t;

/*!
 * @brief Specification of a queue node.
 */
typedef struct ncp_mtm_queue_s
{
    /*! @brief  The ID of this queue */
    ncp_uint32_t                queueId;
    /*! @brief  The ID of the parent scheduler. */
    ncp_uint32_t                parentId;
    /*! @brief  The scheduling mode of this queue. */
    ncp_mtm_scheduling_mode_t   schedulingMode;
    /*! @brief  The shaping mode of this queue. */
    ncp_mtm_shaping_mode_t      shapingMode;
    /*! @brief  The shaping rates for this queue.  This field does not
     *          apply if the scheduler is in script shaping mode.
     */
    ncp_mtm_shaping_rate_t      *shapingRates;
    /*! @brief  In WRR scheduling modes, the deficit weighted round robin
     *          limit.  In STRICT scheduling mode, the starvation avoidance
     *          limit.  A value of 0 in STRICT scheduling mode turns the
     *          starvation avoidence function off.  Value is in bytes.
     */
    ncp_uint32_t                serviceQuantum;
    /*! @brief  The ID of the shared parameter block. To not use a shared
     *          parameter block, set to NCP_MTM_NO_SHARED_PARAM_ID.
     */
    ncp_uint32_t                sharedParamId;
    /*! @brief  The identifier of one of the static backpressure destinations.
     *          ASE code generation creates #define values for thesse BP
     *          destinations in the C header file. If the queue is not going
     *          to be backpressured, set this field to NCP_MTM_NO_BP_DEST.
     */
    ncp_uint32_t                bpDestIndex;
    /*! @brief  The hierarchy level from which to get the second set of
     *          scheduler parameters for the traffic management script.
     */
    ncp_uint8_t                 tmParamsRelativeHigherLevel;
    /*! @brief  The hierarchy level from which to get the second set of
     *          scheduler parameters for the traffic shaping script.
     */
    ncp_uint8_t                 tsParamsRelativeHigherLevel;
    /*! @brief  Indicates if the 2 byte output ID should be populated with
     *          parameter bytes 0-1 from this level.
     */
    ncp_bool_t                  outputIdSelect;
    /*! @brief  Specify how time is scaled.  Ranges from 0 to 15. Set to
     *          NCP_MTM_TIME_SCALE_AUTO for the API to determine the best
     *          value.  In a hardware shaping mode, AUTO will use the smallest
     *          time scale possible for the selected shaping rates.  In script
     *          shaping mode, AUTO will set the scale to 2 (no time scaling).
     */
    ncp_int8_t                  timeScale;
    /*! @brief  The ID of the traffic management script. */
    ncp_uint8_t                 tmScriptId;
    /*! @brief  The queue script parameters. */
    ncp_byte_string_t           scriptParams;
} ncp_mtm_queue_t;

/*!
 * @brief Multicast flow list.
 */
typedef struct ncp_mtm_multicast_flow_list_s
{
    /*! @brief  The number of entries that there is space for in the flowIds array */
    ncp_uint32_t    numEntries;
    /*! @brief  An array of flow IDs.  */
    ncp_uint32_t    *flowIds;
} ncp_mtm_multicast_flow_list_t;

/*!
 * @brief Multicast group information.
 */
typedef struct ncp_mtm_multicast_group_info_s
{
    /*! @brief  The ID of the group */
    ncp_uint32_t                    groupId;
    /*! @brief  The number of flows currently in the group */
    ncp_uint32_t                    numFlows;
    /*! @brief  The number of 256 byte blocks being allocated to the group.
     *          Each 256 byte block can hold 63 flow entries.
     */
    ncp_uint32_t                    numMemBlocks;
    /*! @brief  A structure in which to return the list of flows */
    ncp_mtm_multicast_flow_list_t   flowList;
} ncp_mtm_multicast_group_info_t;



/* Published APIs */

/*!
 *  @brief  Get the MTM global statistics.
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the MTM is part of.
 *  @param[out] globalStats     Pointer to a structure where the retrieved
 *                              statistics values will be placed.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_global_stats_get(ncp_hdl_t ncpHdl, ncp_mtm_global_stats_t *globalStats);


/*!
 *  @brief  Get the MTM rate rounding algorithm.
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the MTM is part of.
 *  @param[out] roundingAlg     Pointer to a ncp_mtm_rounding_alg_t variable
 *                              where the value of the current rounding
 *                              algorithm being used will be placed.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_rate_rounding_alg_get(ncp_hdl_t ncpHdl, ncp_mtm_rounding_alg_t *roundingAlg);


/*!
 *  @brief  Set the MTM rate rounding algorithm.
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the MTM is part of.
 *  @param[in]  roundingAlg     The rounding algorithm to use when setting rates.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_MTM_RATE_ROUNDING_ALG_INVALID
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_rate_rounding_alg_set(ncp_hdl_t ncpHdl, ncp_mtm_rounding_alg_t roundingAlg);

/*!
 *  @brief  Get the MTM TM compute engine global parameters.
 *
 *          The len field of the globalParam structure should be set
 *          to size of the buffer that is pointed to by buf field.
 *          If the length is less than NCP_MTM_MAX_CE_GLOBAL_PARAMS,
 *          only len bytes will be retrieved.
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the MTM is part of.
 *  @param[out] globalParam     Pointer to a structure containing a buffer
 *                              where the parameters read will be placed.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_MTM_PARAMETER_LENGTH_INVALID
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_tm_global_param_get(ncp_hdl_t ncpHdl, ncp_byte_string_t *globalParam);


/*!
 *  @brief  Get the MTM TS compute engine global parameters.
 *
 *          The len field of the globalParam structure should be set
 *          to size of the buffer that is pointed to by buf field.
 *          If the length is less than NCP_MTM_MAX_CE_GLOBAL_PARAMS,
 *          only len bytes will be retrieved.
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the MTM is part of.
 *  @param[out] globalParam     Pointer to a structure containing a buffer
 *                              where the parameters read will be placed.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_MTM_PARAMETER_LENGTH_INVALID
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_ts_global_param_get(ncp_hdl_t ncpHdl, ncp_byte_string_t *globalParam);


/*!
 *  @brief  Modify the MTM TM compute engine global parameters.
 *
 *          The len field of the globalParam structure should be set
 *          to the number of bytes from the buffer that are to be written
 *          to the global parameter space.  If len is less than
 *          NCP_MTM_MAX_CE_GLOBAL_PARAMS, the global parameter bytes from
 *          byte[len] to byte[NCP_MTM_MAX_CE_GLOBAL_PARAMS - 1] will be
 *          written with zeros.  Note that the new parameter values will
 *          not take effect until the TM compute engine runs.  
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the MTM is part of.
 *  @param[in]  globalParam     Pointer to a structure containing the byte
 *                              string of values to write to the parameter
 *                              space.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_MTM_PARAMETER_LENGTH_INVALID
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_tm_global_param_mod(ncp_hdl_t ncpHdl, ncp_byte_string_t *globalParam);


/*!
 *  @brief  Modify the MTM TS compute engine global parameters.
 *
 *          The len field of the globalParam structure should be set
 *          to the number of bytes from the buffer that are to be written
 *          to the global parameter space.  If len is less than
 *          NCP_MTM_MAX_CE_GLOBAL_PARAMS, the global parameter bytes from
 *          byte[len] to byte[NCP_MTM_MAX_CE_GLOBAL_PARAMS - 1] will be
 *          written with zeros.  Note that the new parameter values will
 *          not take effect until the TS compute engine runs.  
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the MTM is part of.
 *  @param[in]  globalParam     Pointer to a structure containing the byte
 *                              string of values to write to the parameter
 *                              space.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_MTM_PARAMETER_LENGTH_INVALID
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_ts_global_param_mod(ncp_hdl_t ncpHdl, ncp_byte_string_t *globalParam);

/*!
 *  @brief  Get the statistics for an MTM queue or scheduler.
 *
 *          The values returned in the nodeStats structure are a snapshot
 *          of the state of the node when this function is called.
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the MTM is part of.
 *  @param[in]  nodeId          The ID of the queue or scheduler node.
 *  @param[out] nodeStats       Pointer to a structure where the retrieved
 *                              statistics values will be placed.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *      \li ::NCP_ST_MTM_NODE_ID_INVALID
 *      \li ::NCP_ST_MTM_QUEUE_DOES_NOT_EXIST
 *      \li ::NCP_ST_MTM_SCHEDULER_DOES_NOT_EXIST
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_node_stats_get(ncp_hdl_t ncpHdl, ncp_uint32_t nodeId,
                       ncp_mtm_node_stats_t *nodeStats);


/*!
 *  @brief  Get the external backpressure state for an MTM queue or scheduler.
 *
 *          The value returned will be the current external backpressure
 *          state of the node when this function is called.
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the MTM is part of.
 *  @param[in]  nodeId          The ID of the queue or scheduler node.
 *  @param[out] bpState         Pointer to an ncp_bool_t where the retrieved
 *                              external backpressure state will be placed.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *      \li ::NCP_ST_MTM_NODE_ID_INVALID
 *      \li ::NCP_ST_MTM_QUEUE_DOES_NOT_EXIST
 *      \li ::NCP_ST_MTM_SCHEDULER_DOES_NOT_EXIST
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_node_bp_state_get(ncp_hdl_t ncpHdl, ncp_uint32_t nodeId,
                          ncp_bool_t *bpState);


/*!
 *  @brief  Retrieve the number of bits of length correction given an average error.
 *
 *          The value calculated represents a number of bits that should be
 *          added to the length correction value in the traffic management
 *          script.  The primary intention of this API call is to aid an
 *          application with working around errata 34146.
 *          Note that errata 34146 only applies to 344x device types.
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the MTM is part of.
 *  @param[in]  nodeId          The ID of the queue or scheduler to calculate
 *                              the length correction for.
 *  @param[in]  avgErr          Pointer to a float value containing th average error.
 *                              If a NULL pointer is passed, a value of 0.5 is used.
 *  @param[out] lenCorrection   Pointer to a uint32 where the number of bits of
 *                              length correction value calculated will be placed.
 *
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_NO_MEMORY
 *      \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *      \li ::NCP_ST_MTM_NODE_ID_INVALID
 *      \li ::NCP_ST_MTM_QUEUE_DOES_NOT_EXIST
 *      \li ::NCP_ST_MTM_SCHEDULER_DOES_NOT_EXIST
 *      \li ::NCP_ST_MTM_SHAPING_MODE_INVALID
 *      \li ::NCP_ST_MTM_SCHEDULER_AVG_ERROR_INVALID
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_node_len_correction_calc(ncp_hdl_t ncpHdl, ncp_uint32_t nodeId,
                                 float *avgErr, ncp_uint32_t *lenCorrection);


/*!
 *  @brief  Calculate and return modified shaping rates to correct for .5 sclaed ticks.
 *
 *          The rates calculated represents the rates that sould be passed
 *          to one of the node add API or rate modify API calls in order to
 *          effect the actual rates specified in the inputRates parameter.
 *          The maxPacketSize field of the inputRates structure should be
 *          set to the average packet size that will be processed by the node.
 *          The correction uses a statistical algorithm. the actual rate may
 *          be different from the requested rate depending on how the actual
 *          traffic relates to the maxPacketSize specified.  The correction
 *          will be most accurate for traffic proflies that have fixed packet
 *          sizes.  This node only applies to the PR, PR_SR and PR_MR shaping
 *          modes.  The intention of this API call is to aid an application
 *          with working around errata 34146.  
 *          Note that errata 34146 only applies to 344x device types.
 *          If this API is called on a device other than 34xx, it will
 *          populate the corrected rates with unmodified values from the
 *          input rates specified.
 *
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the MTM is part of.
 *  @param[in]  shapingMode     The shaping mode.
 *  @param[in]  inputRates      Pointer to a shaping rate structure that
 *                              contains the desired rates and bucket depths.
 *  @param[out] correctedRates  Pointer to a shaping rate structure where
 *                              the corrected rate values will be placed.
 *
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_MTM_SHAPING_MODE_INVALID
 *      \li ::NCP_ST_MTM_SHAPING_PEAK_LESS_THAN_SECONDARY
 *      \li ::NCP_ST_MTM_SHAPING_BUCKET_LESS_THAN_MAX_PACKET
 *      \li ::NCP_ST_MTM_SHAPING_RATES_INCOMPATIBLE
 *      \li ::NCP_ST_MTM_SHAPING_MODE_INVALID
 *      \li ::NCP_ST_MTM_SHAPING_MODE_INVALID
 *      \li ::NCP_ST_MTM_SCHEDULER_AVG_ERROR_INVALID
 */
NCP_API ncp_st_t
ncp_mtm_errata_34146_rate_correction_calc(ncp_hdl_t ncpHdl,
                                          ncp_mtm_shaping_mode_t shapingMode,
                                          ncp_mtm_shaping_rate_t *inputRates,
                                          ncp_mtm_shaping_rate_t *correctedRates);


/*!
 *  @brief  Add an MTM scheduler object.
 *
 *          Use this API to add a scheduler node to the MTM.  The scheduler
 *          will be created in accordance with the specifications in the
 *          input ncp_mtm_scheduler_t structure.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the MTM is part of.
 *  @param[in]  scheduler   Strucutre that specifies the attributes of the
 *                          scheduler to be added.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_NO_MEMORY
 *      \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *      \li ::NCP_ST_MTM_PARENT_ID_INVALID
 *      \li ::NCP_ST_MTM_PARENT_DOES_NOT_EXIST
 *      \li ::NCP_ST_MTM_PARENT_HIER_LEVEL_INCORRECT
 *      \li ::NCP_ST_MTM_PARENT_DRAINING
 *      \li ::NCP_ST_MTM_TOO_MANY_CHILDREN
 *      \li ::NCP_ST_MTM_SCHEDULING_MODE_INVALID
 *      \li ::NCP_ST_MTM_PARAMETER_LENGTH_INVALID
 *      \li ::NCP_ST_MTM_SERVICE_QUANTUM_INVALID
 *      \li ::NCP_ST_MTM_TIME_SCALE_INVALID
 *      \li ::NCP_ST_MTM_TIME_SCALE_INCOMPATIBLE
 *      \li ::NCP_ST_BP_INVALID_DEST_INDEX
 *      \li ::NCP_ST_BP_DEST_ID_ALREADY_SET
 *      \li ::NCP_ST_MTM_SHAPING_MODE_INVALID
 *      \li ::NCP_ST_MTM_SHAPING_RATES_INCOMPATIBLE
 *      \li ::NCP_ST_MTM_SHAPING_PEAK_LESS_THAN_SECONDARY
 *      \li ::NCP_ST_MTM_SHAPING_BUCKET_LESS_THAN_MAX_PACKET
 *      \li ::NCP_ST_MTM_PRIORITY_LEVEL_IN_USE
 *      \li ::NCP_ST_MTM_MR_IN_STRICT_MODE
 *      \li ::NCP_ST_MTM_SCHEDULER_ID_INVALID
 *      \li ::NCP_ST_MTM_SCHEDULER_EXISTS
 *      \li ::NCP_ST_MTM_SCHEDULER_ARB_MODE_INVALID
 *      \li ::NCP_ST_MTM_SCHEDULER_TS_SCRIPT_ID_INVALID
 *      \li ::NCP_ST_MTM_SCHEDULER_TS_SCRIPT_DOES_NOT_EXIST
 *      \li ::NCP_ST_MTM_SCHEDULER_TS_ALREADY_RUNNING
 *      \li ::NCP_ST_MTM_SCHEDULER_TS_SCRIPT_REQUIRED
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_scheduler_add(ncp_hdl_t ncpHdl, ncp_mtm_scheduler_t *scheduler);



/*!
 *  @brief  Retrieve information about an existing MTM scheduler.
 *
 *          This call is used to populate an ncp_mtm_scheduler_t structure
 *          with the attributes of an existing scheduler.
 *
 *  @param[in]      ncpHdl      Handle for the NCP that the MTM is part of.
 *  @param[in,out]  scheduler   The scheduler structure to be filled in by
 *                              the get call. The caller must populate the
 *                              schedId field with the ID of the scheduler to
 *                              be retrived.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *      \li ::NCP_ST_MTM_SCHEDULER_ID_INVALID
 *      \li ::NCP_ST_MTM_SCHEDULER_DOES_NOT_EXIST
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_scheduler_get(ncp_hdl_t ncpHdl, ncp_mtm_scheduler_t *scheduler);



/*!
 *  @brief  Modify the script paramters of an MTM scheduler.
 *
 *          If the offset parameter is non-zero, the updated begins
 *          at offset bytes form the beginning of the parameter block.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the MTM is part of.
 *  @param[in]  schedId     The ID of the scheduler whose script parameters
 *                          will be modified.
 *  @param[in]  paramValue  Pointer to a structure containing the byte string
 *                          of vaules to write to the parameter space
 *  @param[in]  offset      Offset from the beginning of the parameter block
 *                          where the byte string will be written.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_NO_MEMORY
 *      \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *      \li ::NCP_ST_MTM_SCHEDULER_ID_INVALID
 *      \li ::NCP_ST_MTM_SCHEDULER_DOES_NOT_EXIST
 *      \li ::NCP_ST_MTM_PARAMETER_LENGTH_INVALID
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_scheduler_param_mod(ncp_hdl_t ncpHdl, ncp_uint32_t schedId,
                            ncp_byte_string_t *paramValue, ncp_uint32_t offset);


/*!
 *  @brief  Modify the shaping rates of an MTM scheduler.
 *
 *  @param[in]  ncpHdl    Handle for the NCP that the MTM is part of.
 *  @param[in]  schedId   The ID of the scheduler whose rates will be modified.
 *  @param[in]  newRates  The new rates and bucket depths to assign.
 *
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *      \li ::NCP_ST_MTM_SCHEDULER_ID_INVALID
 *      \li ::NCP_ST_MTM_SCHEDULER_DOES_NOT_EXIST
 *      \li ::NCP_ST_MTM_SHAPING_PEAK_LESS_THAN_SECONDARY
 *      \li ::NCP_ST_MTM_SHAPING_BUCKET_LESS_THAN_MAX_PACKET
 *      \li ::NCP_ST_MTM_SHAPING_RATES_INCOMPATIBLE
 *      \li ::NCP_ST_MTM_HW_SHAPER_NOT_IN_USE
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_scheduler_rate_mod(ncp_hdl_t ncpHdl, ncp_uint32_t schedId,
                       ncp_mtm_shaping_rate_t *newRates);


/*!
 *  @brief  Modify the service quantum of an MTM scheduler.
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the MTM is part of.
 *  @param[in]  schedId         The ID of the scheduler whose service quantum
 *                              will be modified.
 *  @param[in]  serviceQuantum  The new service quanutm to assign.
 *
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *      \li ::NCP_ST_MTM_SCHEDULER_ID_INVALID
 *      \li ::NCP_ST_MTM_SCHEDULER_DOES_NOT_EXIST
 *      \li ::NCP_ST_MTM_SERVICE_QUANTUM_INVALID
 *      \li ::NCP_ST_MTM_SERVICE_QUANTUM_NOT_APPLICABLE
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_scheduler_service_quantum_mod(ncp_hdl_t ncpHdl, ncp_uint32_t schedId,
                                      ncp_uint32_t serviceQuantum);


/*!
 *  @brief  Remove an MTM scheduler object.
 *
 *  @param[in]  ncpHdl  Handle for the NCP that the MTM is part of.
 *  @param[in]  schedId The ID of the scheduler to remove.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *      \li ::NCP_ST_MTM_SCHEDULER_ID_INVALID
 *      \li ::NCP_ST_MTM_SCHEDULER_DOES_NOT_EXIST
 *      \li ::NCP_ST_MTM_SCHEDULER_HAS_CHILDREN
 *      \li ::NCP_ST_MTM_NODE_DRAINING
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_scheduler_rem(ncp_hdl_t ncpHdl, ncp_uint32_t schedId);



/*!
 *  @brief  Retrieve the contents of a queue shared parameter block.
 *
 *          If the offset parameter is non-zero, the bytes retrieved begin
 *          at offset bytes form the beginning of the parameter block.
 *
 *  @param[in]      ncpHdl      Handle for the NCP that the MTM is part of.
 *  @param[in,out]  sharedParam The shared parameter block specification
 *                              containing the parameter ID and the buffer
 *                              where the retrieved bytes will be placed.
 *  @param[in]      offset      Offset from the beginning of the parameter
 *                              block where the byte string will be retrieved.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *      \li ::NCP_ST_MTM_OFFSET_INVALID
 *      \li ::NCP_ST_MTM_PARAMETER_LENGTH_INVALID
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_shared_param_get(ncp_hdl_t ncpHdl, ncp_mtm_shared_param_t *sharedParam,
                         ncp_uint32_t offset);


/*!
 *  @brief  Modify the contents of a queue shared parameter block.
 *
 *          If the offset parameter is non-zero, the update begins
 *          at offset bytes form the beginning of the parameter block.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the MTM is part of.
 *  @param[in]  sharedParam The shared parameter block specification containing
 *                          the parameter ID and the byte string to be written.
 *  @param[in]  offset      Offset from the beginning of the parameter block
 *                          where the byte string will be written.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *      \li ::NCP_ST_MTM_OFFSET_INVALID
 *      \li ::NCP_ST_MTM_PARAMETER_LENGTH_INVALID
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_shared_param_mod(ncp_hdl_t ncpHdl, ncp_mtm_shared_param_t *sharedParam,
                         ncp_uint32_t offset);



/*!
 *  @brief  Add a queue object to the MTM.
 *
 *          Use this API to add a queue node to the MTM.  The queue will
 *          will be created in accordance with the specifications in the
 *          input ncp_mtm_queue_t structure.
 *
 *  @param[in]  ncpHdl  Handle for the NCP that the MTM is part of.
 *  @param[in]  queue   The queue specifications.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_NO_MEMORY
 *      \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *      \li ::NCP_ST_MTM_PARENT_ID_INVALID
 *      \li ::NCP_ST_MTM_PARENT_DOES_NOT_EXIST
 *      \li ::NCP_ST_MTM_PARENT_DRAINING
 *      \li ::NCP_ST_MTM_TOO_MANY_CHILDREN
 *      \li ::NCP_ST_MTM_PARAMETER_LENGTH_INVALID
 *      \li ::NCP_ST_MTM_PRIORITY_LEVEL_IN_USE
 *      \li ::NCP_ST_MTM_MR_IN_STRICT_MODE
 *      \li ::NCP_ST_MTM_QUEUE_EXISTS
 *      \li ::NCP_ST_MTM_QUEUE_ID_INVALID
 *      \li ::NCP_ST_MTM_QUEUE_NO_TS_RUNNING
 *      \li ::NCP_ST_MTM_QUEUE_TM_PARAMS_HIGHER_LEVEL_INVALID
 *      \li ::NCP_ST_MTM_QUEUE_TS_PARAMS_HIGHER_LEVEL_INVALID
 *      \li ::NCP_ST_MTM_QUEUE_TM_SCRIPT_ID_INVALID
 *      \li ::NCP_ST_MTM_QUEUE_TM_SCRIPT_DOES_NOT_EXIST
 *      \li ::NCP_ST_MTM_SERVICE_QUANTUM_INVALID
 *      \li ::NCP_ST_MTM_TIME_SCALE_INVALID
 *      \li ::NCP_ST_MTM_TIME_SCALE_INCOMPATIBLE
 *      \li ::NCP_ST_BP_INVALID_DEST_INDEX
 *      \li ::NCP_ST_BP_DEST_ID_ALREADY_SET
 *      \li ::NCP_ST_MTM_SCHEDULING_MODE_INVALID
 *      \li ::NCP_ST_MTM_SHAPING_MODE_INVALID
 *      \li ::NCP_ST_MTM_SHAPING_RATES_INCOMPATIBLE
 *      \li ::NCP_ST_MTM_SHAPING_PEAK_LESS_THAN_SECONDARY
 *      \li ::NCP_ST_MTM_SHAPING_BUCKET_LESS_THAN_MAX_PACKET
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_queue_add(ncp_hdl_t ncpHdl, ncp_mtm_queue_t *queue);



/*!
 *  @brief  Retrieve information about an existing MTM queue.
 *
 *          This call is used to populate an ncp_mtm_queue_t structure
 *          with the attributes of an existing queue.
 *
 *  @param[in]      ncpHdl  Handle for the NCP that the MTM is part of.
 *  @param[in,out]  queue   The queue structure to be filled in by the get
 *                          call. The caller must populate the queueId field
 *                          with the ID of the queue to be retrived.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *      \li ::NCP_ST_MTM_QUEUE_ID_INVALID
 *      \li ::NCP_ST_MTM_QUEUE_DOES_NOT_EXIST
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_queue_get(ncp_hdl_t ncpHdl, ncp_mtm_queue_t *queue);



/*!
 *  @brief  Modify the script paramters of an MTM queue.
 *
 *          If the offset parameter is non-zero, the updated begins
 *          at offset bytes form the beginning of the parameter block.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the MTM is part of.
 *  @param[in]  queueId     The ID of the queue whose script parameters will
 *                          be modified.
 *  @param[in]  paramValue  Pointer to a structure containing the byte string
 *                          of values to write to the parameter space.
 *  @param[in]  offset      Offset from the beginning of the parameter block
 *                          where the byte string will be written.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_NO_MEMORY
 *      \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *      \li ::NCP_ST_MTM_QUEUE_ID_INVALID
 *      \li ::NCP_ST_MTM_QUEUE_DOES_NOT_EXIST
 *      \li ::NCP_ST_MTM_OFFSET_INVALID
 *      \li ::NCP_ST_MTM_PARAMETER_LENGTH_INVALID
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_queue_param_mod(ncp_hdl_t ncpHdl, ncp_uint32_t queueId,
                        ncp_byte_string_t *paramValue, ncp_uint32_t offset);


/*!
 *  @brief  Modify the shaping rates of an MTM queue.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the MTM is part of.
 *  @param[in]  queueId     The ID of the queue whose rates will be modified.
 *  @param[in]  newRates    The new rates and bucket depths to assign.
 *
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *      \li ::NCP_ST_MTM_QUEUE_ID_INVALID
 *      \li ::NCP_ST_MTM_QUEUE_DOES_NOT_EXIST
 *      \li ::NCP_ST_MTM_SHAPING_PEAK_LESS_THAN_SECONDARY
 *      \li ::NCP_ST_MTM_SHAPING_BUCKET_LESS_THAN_MAX_PACKET
 *      \li ::NCP_ST_MTM_SHAPING_RATES_INCOMPATIBLE
 *      \li ::NCP_ST_MTM_HW_SHAPER_NOT_IN_USE
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_queue_rate_mod(ncp_hdl_t ncpHdl, ncp_uint32_t queueId,
                       ncp_mtm_shaping_rate_t *newRates);


/*!
 *  @brief  Modify the service quantum of an MTM queue.
 *
 *  @param[in]  ncpHdl          Handle for the NCP that the MTM is part of.
 *  @param[in]  queueId         The ID of the queue whose service quantum
 *                              will be modified.
 *  @param[in]  serviceQuantum  The new service quanutm to assign.
 *
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *      \li ::NCP_ST_MTM_QUEUE_ID_INVALID
 *      \li ::NCP_ST_MTM_QUEUE_DOES_NOT_EXIST
 *      \li ::NCP_ST_MTM_SERVICE_QUANTUM_INVALID
 *      \li ::NCP_ST_MTM_SERVICE_QUANTUM_NOT_APPLICABLE
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_queue_service_quantum_mod(ncp_hdl_t ncpHdl, ncp_uint32_t queueId,
                                  ncp_uint32_t serviceQuantum);


/*!
 *  @brief  Modify the shared parameter ID of an MTM queue.
 *
 *  @param[in]  ncpHdl         Handle for the NCP that the MTM is part of.
 *  @param[in]  queueId        The ID of the queue whose shared parameter ID
 *                             will be modified.
 *  @param[in]  sharedParamId  The shared parameter ID to assign.
 *
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *      \li ::NCP_ST_MTM_QUEUE_ID_INVALID
 *      \li ::NCP_ST_MTM_QUEUE_DOES_NOT_EXIST
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_queue_shared_param_id_mod(ncp_hdl_t ncpHdl, ncp_uint32_t queueId,
                                  ncp_uint32_t sharedParamId);


/*!
 *  @brief  Remove a queue object from the MTM
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the MTM is part of.
 *  @param[in]  queueId     The ID of the queue to remove.
 *  @param[in]  delayTime   The time in microseconds to delay between removal
 *                          retries.
 *  @param[in]  retryCount  The number of times to retry the removal.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *      \li ::NCP_ST_MTM_QUEUE_ID_INVALID
 *      \li ::NCP_ST_MTM_QUEUE_DOES_NOT_EXIST
 *      \li ::NCP_ST_MTM_NODE_DRAINING
 *      \li ::NCP_ST_MTM_DRAIN_BUSY
 *      \li ::NCP_ST_MTM_DRAIN_ENQUEUE_STOP_TIMEOUT
 *      \li ::NCP_ST_MTM_DRAIN_TIMEOUT
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_queue_rem(ncp_hdl_t ncpHdl, ncp_uint32_t queueId,
                  ncp_uint32_t delayTime, ncp_uint32_t retryCount);


/*!
 *  @brief  Drain the data from an MTM node
 *
 *  The node ID can be either a queue or a scheduler.  Optionally, update 
 *  the parentId for the node.  The newParentId parameter allows a node
 *  to be moved in the MTM hierarchy.  If the nodeId is a scheduler,
 *  specifying a  newParentId will move the entire sub-hierarchy.
 *  If the node being drained is a queue, #NCP_MTM_PARKING_SCHED_ID can
 *  be specified for the newParentId parameter.  In that case, the queue
 *  will be left in a parked state, and no more tasks will be enqueued
 *  (they will be dropped).  The queue can be returned to service with a
 *  subsequent call to <b>ncp_mtm_node_drain</b> which updates the parentId
 *  and reconnects the queue to a functioning parent scheduler.
 *
 *  @param[in]  ncpHdl      Handle for the NCP that the MTM is part of.
 *  @param[in]  nodeId      The ID of the node to drain.
 *  @param[in]  newParentId The ID of the new parent that the node will be
 *                          assigned after it is drained.
 *  @param[in]  delayTime   The time in microseconds to delay between checks
 *                          for empty.
 *  @param[in]  retryCount  The number of times to retry the check for empty.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *      \li ::NCP_ST_MTM_NODE_ID_INVALID
 *      \li ::NCP_ST_MTM_PARENT_ID_INVALID
 *      \li ::NCP_ST_MTM_QUEUE_DOES_NOT_EXIST
 *      \li ::NCP_ST_MTM_SCHEDULER_DOES_NOT_EXIST
 *      \li ::NCP_ST_MTM_PARENT_DOES_NOT_EXIST
 *      \li ::NCP_ST_MTM_PARENT_DRAINING
 *      \li ::NCP_ST_MTM_TOO_MANY_CHILDREN
 *      \li ::NCP_ST_MTM_PARENT_HIER_LEVEL_INCORRECT
 *      \li ::NCP_ST_MTM_NODE_DRAINING
 *      \li ::NCP_ST_MTM_SCHEDULING_MODE_INVALID
 *      \li ::NCP_ST_MTM_SHAPING_MODE_INVALID
 *      \li ::NCP_ST_MTM_PRIORITY_LEVEL_IN_USE
 *      \li ::NCP_ST_MTM_DRAIN_BUSY
 *      \li ::NCP_ST_MTM_DRAIN_ENQUEUE_STOP_TIMEOUT
 *      \li ::NCP_ST_MTM_DRAIN_TIMEOUT
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_node_drain(ncp_hdl_t ncpHdl, ncp_uint32_t nodeId,
                   ncp_uint32_t newParentId, ncp_uint32_t delayTime,
                   ncp_uint32_t retryCount);


/*!
 *  @brief  Add a flow to a multicast group
 *          The flow is added to the list in the fisrt available slot.
 *
 *  @param[in]  ncpHdl    Handle for the NCP that the MTM is part of.
 *  @param[in]  vpHdl     Handle for the VP that the multicast group belongs to.
 *  @param[in]  groupId   The multicast group to add the flow to. 
 *  @param[in]  flowId    The ID of the flow to add to the group.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_VPM_INVALID_VP_HDL
 *      \li ::NCP_ST_VPM_INVALID_FLOW_ID
 *      \li ::NCP_ST_VPM_LAUNCH_ENGINE_MISMATCH
 *      \li ::NCP_ST_MTM_MCAST_GROUP_DOES_NOT_EXIST
 *      \li ::NCP_ST_MTM_MCAST_NO_MEMORY
 *      \li ::NCP_ST_NO_MEMORY
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_multicast_flow_add(ncp_hdl_t ncpHdl, ncp_vp_hdl_t vpHdl,
                           ncp_uint32_t groupId, ncp_uint32_t flowId);


/*!
 *  @brief  Remove a flow from a multicast group
 *          If the flow exists in the group multiple times,
 *          only the first instance is removed.
 *
 *  @param[in]  ncpHdl    Handle for the NCP that the MTM is part of.
 *  @param[in]  vpHdl     Handle for the VP that the multicast group belongs to.
 *  @param[in]  groupId   The multicast group to remove the flow from. 
 *  @param[in]  flowId    The ID of the flow to remove from the group.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_VPM_INVALID_VP_HDL
 *      \li ::NCP_ST_VPM_INVALID_FLOW_ID
 *      \li ::NCP_ST_VPM_LAUNCH_ENGINE_MISMATCH
 *      \li ::NCP_ST_MTM_MCAST_GROUP_DOES_NOT_EXIST
 *      \li ::NCP_ST_MTM_MCAST_FLOW_NOT_IN_GROUP
 *      \li ::NCP_ST_NO_MEMORY
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_multicast_flow_rem(ncp_hdl_t ncpHdl, ncp_vp_hdl_t vpHdl,
                           ncp_uint32_t groupId, ncp_uint32_t flowId);


/*!
 *  @brief  Compact the system memory that contains the flow list for the
 *          specified multicast group.  This is useful if the memory containing
 *          the flow list has become fragmented by numerous flow add/delete
 *          operations. The group will use the minimum amount of system memory
 *          for its flow list after calling this function.
 *
 *  @param[in]  ncpHdl    Handle for the NCP that the MTM is part of.
 *  @param[in]  vpHdl     Handle for the VP that the multicast group belongs to.
 *  @param[in]  groupId   The multicast group to compact. 
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_VPM_INVALID_VP_HDL
 *      \li ::NCP_ST_VPM_LAUNCH_ENGINE_MISMATCH
 *      \li ::NCP_ST_MTM_MCAST_GROUP_DOES_NOT_EXIST
 *      \li ::NCP_ST_MTM_MCAST_NO_MEMORY
 *      \li ::NCP_ST_NO_MEMORY
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_multicast_group_compact(ncp_hdl_t ncpHdl, ncp_vp_hdl_t vpHdl,
                                ncp_uint32_t groupId);


/*!
 *  @brief  Retrieve information about an MTM multicast group. The information
 *          returned consists of the number of flow entries currently in the group
 *          and the number of 256 byte system memory blocks used for the flow list.
 *          A list of the flow entries can also be returned if space is provided for
 *          it in the groupInfo structure.
 *
 *  @param[in]     ncpHdl       Handle for the NCP that the MTM is part of.
 *  @param[in]     vpHdl        Handle for the VP that the multicast group belongs to.
 *  @param[in,out] groupInfo    Structure that spedifies the ID of the group and that 
 *                              will be filled in with the group information.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_VPM_INVALID_VP_HDL
 *      \li ::NCP_ST_VPM_LAUNCH_ENGINE_MISMATCH
 *      \li ::NCP_ST_MTM_MCAST_GROUP_DOES_NOT_EXIST
 *      \li ::NCP_ST_NO_MEMORY
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_multicast_group_info_get(ncp_hdl_t ncpHdl, ncp_vp_hdl_t vpHdl,
                                 ncp_mtm_multicast_group_info_t *groupInfo);


/*!
 *  @brief  Set the backpressure destination id.
 *
 *          Set the backpressure destination id to list of sources already created
 *          and identified by bpDestIndex.
 *
 *  @param[in]  ncpHdl  Handle for the NCP that the MTM is part of.
 *  @param[in]  bpDestIndex  Index identifying list of backpressure sources 
 *              already created.
 *  @param[in]  destId  Backpressure destination id. This is the queue or scheduler
 *              id that needs to be backpressured.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_SERVICE_UNAVAILABLE_ON_THIS_DOMAIN
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_NS_NO_NAMESPACES_DEFINED
 *      \li ::NCP_ST_NS_ENTRY_ID_INVALID
 *      \li ::NCP_ST_BP_INVALID_DEST_INDEX
 *      \li ::NCP_ST_BP_DEST_ID_ALREADY_SET
 *      \li Low level device access error codes.
 */
NCP_API ncp_st_t
ncp_mtm_bp_dest_id_set(ncp_hdl_t ncpHdl, ncp_uint32_t bpDestIndex, 
                       ncp_uint32_t destId);

/*!
 *  @brief  Unset the backpressure destination id.
 *
 *          Unset the backpressure destination id to list of sources already created
 *          and identified by bpDestIndex.
 *
 *  @param[in]  ncpHdl  Handle for the NCP that the MTM is part of.
 *  @param[in]  bpDestIndex  Index identifying list of backpressure sources 
 *              already created.
 *
 *  @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_SERVICE_UNAVAILABLE_ON_THIS_DOMAIN
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_BP_INVALID_DEST_INDEX
 *      \li ::NCP_ST_BP_DEST_ID_ALREADY_UNSET
 *      \li Low level device access error codes
 */
NCP_API ncp_st_t
ncp_mtm_bp_dest_id_unset(ncp_hdl_t ncpHdl, ncp_uint32_t bpDestIndex);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _NCP_MTM_H_ */

