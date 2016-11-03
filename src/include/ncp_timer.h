/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*! @file      ncp_timer.h
 *  @brief     Timer (timer)
 * 
 *  @addtogroup _timer_ Timer
 * 
 *  @{
 */



#ifndef _NCP_TMGR_H_
#define _NCP_TMGR_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Public flags */

#define NCP_TIMER_FLAGS_EXPIRES_SECONDS             (0x1)
#define NCP_TIMER_FLAGS_EXPIRES_MILLISECONDS        (0x2)
#define NCP_TIMER_FLAGS_EXPIRES_MICROSECONDS        (0x4)
#define NCP_TIMER_FLAGS_PASS_INVALID_INDEX          (0x8)
#define NCP_TIMER_FLAGS_CPU_TIMER_WAIT_NO_BLOCK     (0x10)

/*!
 * @enum ncp_timer_clock_t
 * Clocks adjustable in timestamp logic using ncp_timer_adjust_clock_ratio
 */
typedef enum
{
    NCP_TIMER_CLOCK_HIGH,        /*!< The higher speed system clock */
    NCP_TIMER_CLOCK_LOW,         /*!< The lower speed system clock */
    NCP_TIMER_CLOCK_LOW_TO_HIGH, /*!< The low-speed system clock to high-speed system clock transition */
    NCP_TIMER_CLOCK_HIGH_TO_LOW, /*!< The high-speed system clock to low-speed system clock transition */
    NCP_TIMER_CLOCK_BOOT_COUNT   /*!< The boot counter clock */
} ncp_timer_clock_t;

/*!
 * @enum ncp_timer_ts_t
 * Types of system timestamps that can be accessed using ncp_timer_get_timestamp()
 */
typedef enum
{
    NCP_TIMER_TIMESTAMP_CORE,          /*!< The core clock timestamp */
    NCP_TIMER_TIMESTAMP_REF_CLOCK,     /*!< The reference clock captured timestamp */
    NCP_TIMER_TIMESTAMP_REF_STROBE     /*!< The timestamp captured when the reference strobe is asserted */
} ncp_timer_ts_t;

/*!
 * @enum ncp_timer_ts_attrib_t
 * Timestamp logic attributes that can be accessed using ncp_timer_get/set_attributes
 */
typedef enum
{
    NCP_TIMER_TS_INIT_COUNT,            /*!< The core timestamp value upon initialization */
    NCP_TIMER_TS_REF_CLOCK_OUTPUT,      /*!< If true, the reference clock i/o pin is used as output, otherwise input */
    NCP_TIMER_TS_REF_STROBE_OUTPUT,     /*!< If true, the reference strobe i/o pin is used as output, otherwise input */
    NCP_TIMER_TS_REF_CLOCK_IN_COUNT,    /*!< The number the reference clock input counter should count to before capturing the timestamp */
    NCP_TIMER_TS_REF_STROBE_OUT_WIDTH   /*!< The reference strobe output signal width, in clock cycles */
} ncp_timer_ts_attrib_t;

/*!
 * @enum ncp_timer_refclk_t
 * Types of system reference clocks that can be used to drive the timestamp logic.
 */
typedef enum
{
    NCP_TIMER_REF_CLOCK_INTERNAL,      /*!< The internal fixed frequency clock */
    NCP_TIMER_REF_CLOCK_EXTERNAL,      /*!< The external reference clock */
} ncp_timer_refclk_t;

/*! @typedef ncp_timer_func_t
 *  @brief ncp_timer_func_t The timer callback function specified in ncp_timer_class_init() should be of this type
 */
typedef void (*ncp_timer_func_t)(void *timerFuncArg);
typedef void* ncp_timer_class_hdl_t;

typedef ncp_st_t (* ncp_task_recv_handler_t)(
                                             ncp_uint8_t recvQueueId,
                                             ncp_uint8_t vpId,
                                             void *recvHandlerArg,
                                             ncp_task_recv_buf_t **task);

/* APIs */

/*! @fn ncp_st_t ncp_timer_class_init(ncp_hdl_t ncpHdl, const char *timerClassName,
        ncp_timer_func_t timerClassHandler, ncp_uint8_t ncaQueueId,
        ncp_uint8_t recvQueueId, ncp_task_hdl_t taskHdl,
        ncp_timer_class_hdl_t *timerClassHdl)
    @brief Initializes a timer class and associates a handler function with it
    @param ncpHdl Incoming handle of the current NCP device
    @param timerClassName Name of the timer class to initialize.  The name must
           match a named timer class from the configuration file
    @param timerClassHandler Pointer to the class handler function.  This function
           is executed when ncp_task_recv is called after a timer assigned to this
           class expires
    @param ncaQueueId NCA queue ID number, used to determine the DIID.  Valid range
           is from 0 to 23
    @param recvQueueId Logical receive queue number, which is used for receiving the
           Timer expiry tasks.  Valid range is from 0 to 255
    @param taskHdl Task receive handle on which to receive timer expiry message
    @param timerClassHdl Returned handle to initialized timer class
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_DEV_INVALID_BUFFER An invalid pointer was passed in the timerClassName or timerClassHdl field
    @retval NCP_ST_TIMER_INVALID_HANDLE The Timer module was not properly configured
    @retval NCP_ST_TIMER_INVALID_CLASS The specified class was not properly configured, or was already initialized
    @retval NCP_ST_TIMER_INVALID_QUEUE_ID The specified queue ID is not valid
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_timer_class_init(
                     ncp_hdl_t ncpHdl,
                     const char *timerClassName,
                     ncp_timer_func_t timerClassHandler,
                     ncp_uint8_t ncaQueueId,
                     ncp_uint8_t recvQueueId,
                     ncp_task_hdl_t taskHdl,
                     ncp_timer_class_hdl_t *timerClassHdl);

/*! @fn ncp_st_t ncp_timer_class_fini(ncp_hdl_t ncpHdl, ncp_timer_class_hdl_t timerClassHdl)
    @brief Removes a timer class handle association
    @param ncpHdl Incoming handle of the current NCP device
    @param timerClassHdl Incoming handle of initialized timer class.  This handle is returned
           by a prior call to ncp_timer_class_init()
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_TIMER_INVALID_HANDLE The Timer module was not properly configured
    @retval NCP_ST_TIMER_INVALID_CLASS The specified class was not properly configured, or was not initialized
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_timer_class_fini(
                     ncp_hdl_t ncpHdl,
                     ncp_timer_class_hdl_t timerClassHdl);

/*! @fn ncp_st_t ncp_timer_create(ncp_hdl_t ncpHdl, ncp_timer_class_hdl_t timerClassHdl,
        ncp_uint64_t expires, void *classHandlerArg, ncp_uint16_t toid,
        ncp_uint32_t *timerIndex, ncp_uint32_t timerFlags)
    @brief Schedules a new cancelable timer with the TIMER module
    @param ncpHdl Incoming handle of the current NCP device
    @param timerClassHdl Client handle to initialized timer's timer class.  This
           handle is returned by a prior call to ncp_timer_class_init()
    @param expires Amount of time after which the timer will expire, expressed
           as the integer number of time units.  The time unit used for the
           timer (seconds/milliseconds/microseconds) is determined by the value
           of timerFlags
    @param classHandlerArg Pointer to a client structure that contains the class
           handler function parameters to be used on timer expiry
    @param toid Task order ID for the associated flow.  See the ACP3400 Technical
           Guide for details on its usage
    @param timerIndex Timer index returned to the client
    @param timerFlags Flags field to specify non-default behavior.  Valid values
           are NCP_TIMER_FLAGS_EXPIRES_MICROSECONDS, NCP_TIMER_FLAGS_EXPIRES_MILLISECONDS,
           and NCP_TIMER_FLAGS_EXPIRES_SECONDS
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_DEV_INVALID_BUFFER An invalid pointer was passed in the timerIndex or classHandlerArg field
    @retval NCP_ST_TIMER_INVALID_FLAGS An invalid combination of flags was used
    @retval NCP_ST_TIMER_INVALID_HANDLE The Timer module was not properly configured
    @retval NCP_ST_TIMER_NO_VALID_VP No Virtual Pipeline for sending Timer requests was configured
    @retval NCP_ST_TIMER_INVALID_CLASS The specified class was not properly configured, or was not initialized
    @retval NCP_ST_TIMER_NO_INDEX No timer could be created, because there were no available indexes
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_timer_create(
                 ncp_hdl_t ncpHdl,
                 ncp_timer_class_hdl_t timerClassHdl,
                 ncp_uint64_t expires,
                 void *classHandlerArg,
                 ncp_uint16_t toid,
                 ncp_uint32_t *timerIndex,
                 ncp_uint32_t timerFlags);

/*! @fn ncp_st_t ncp_timer_modify(ncp_hdl_t ncpHdl, ncp_timer_class_hdl_t timerClassHdl,
        ncp_uint64_t expires, void *classHandlerArg, ncp_uint16_t toid,
        ncp_uint32_t timerIndex, ncp_uint32_t timerFlags)
    @brief Modifies a previously scheduled cancelable timer with the Timer module
    @param ncpHdl Incoming handle of the current NCP device
    @param timerClassHdl Client handle to initialized timer's intended class.  This
           handle is returned by a prior call to ncp_timer_class_init()
    @param expires Amount of time after which the timer will expire, expressed
           as the integer number of time units.  The time unit used for the
           timer (seconds/milliseconds/microseconds) is determined by the value
           of timerFlags.
    @param classHandlerArg Pointer to a client structure that contains the class
           handler function parameters to be used on timer expiry
    @param toid Task order ID for the associated flow.  See the ACP3400 Technical
           Guide for details on its usage
    @param timerIndex Timer index for the specified timer.  This value is provided
           by a prior call to ncp_timer_create()
    @param timerFlags Flags field to specify non-default behavior.  Valid values
           are NCP_TIMER_FLAGS_EXPIRES_MICROSECONDS, NCP_TIMER_FLAGS_EXPIRES_MILLISECONDS,
           and NCP_TIMER_FLAGS_EXPIRES_SECONDS
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_DEV_INVALID_BUFFER An invalid pointer was passed in the classHandlerArg field
    @retval NCP_ST_TIMER_INVALID_FLAGS An invalid combination of flags was used
    @retval NCP_ST_TIMER_INVALID_HANDLE The Timer module was not properly configured
    @retval NCP_ST_TIMER_NO_VALID_VP No Virtual Pipeline for sending Timer requests was configured
    @retval NCP_ST_TIMER_INVALID_INDEX The specified timerIndex does not correspond to an active timer
    @retval NCP_ST_TIMER_INVALID_CLASS The specified class was not properly configured, or was not initialized
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_timer_modify(
                 ncp_hdl_t ncpHdl,
                 ncp_timer_class_hdl_t timerClassHdl,
                 ncp_uint64_t expires,
                 void *classHandlerArg,
                 ncp_uint16_t toid,
                 ncp_uint32_t timerIndex,
                 ncp_uint32_t timerFlags);

/*! @fn ncp_st_t ncp_timer_delete(ncp_hdl_t ncpHdl, ncp_timer_class_hdl_t timerClassHdl,
        ncp_uint32_t timerIndex, ncp_uint32_t timerFlags)
    @brief Deletes a previously scheduled cancelable timer with the TIMER module
    @param ncpHdl Incoming handle of the current NCP device
    @param timerClassHdl Client handle to initialized timer's intended class.  This
           handle is returned by a prior call to ncp_timer_class_init()
    @param timerIndex Timer index returned to the client.  This value is provided
           by a prior call to ncp_timer_create()
    @param timerFlags Flags field to specify non-default behavior
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_TIMER_INVALID_FLAGS An invalid combination of flags was used
    @retval NCP_ST_TIMER_INVALID_HANDLE The Timer module was not properly configured
    @retval NCP_ST_TIMER_NO_VALID_VP No Virtual Pipeline for sending Timer requests was configured
    @retval NCP_ST_TIMER_INVALID_INDEX The specified timerIndex does not correspond to an active timer
    @retval NCP_ST_TIMER_INVALID_CLASS The specified class was not properly configured, or was not initialized
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_timer_delete(
                 ncp_hdl_t ncpHdl,
                 ncp_timer_class_hdl_t timerClassHdl,
                 ncp_uint32_t timerIndex,
                 ncp_uint32_t timerFlags);

/*! @fn ncp_st_t ncp_timer_adjust_clock_ratio(ncp_hdl_t ncpHdl, ncp_timer_clock_t tClock, double ratio)
    @brief Adjust the ratio that specifies the amount to increment the timestamp for each core clock cycle (i.e. ratio = frequency(timestamp) / frequency(core clock)).
    @param ncpHdl Incoming handle of the current NCP device
    @param tClock The core clock to which this ratio applies (NCP_TIMER_CLOCK_HIGH, NCP_TIMER_CLOCK_LOW, NCP_TIMER_CLOCK_LOW_TO_HIGH, NCP_TIMER_CLOCK_HIGH_TO_LOW, NCP_TIMER_CLOCK_BOOT_COUNT).
    @param ratio Specifies the ratio of timestamp frequency to core clock frequency
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_TIMER_INVALID_HANDLE The Timer module was not properly configured
    @retval NCP_ST_INVALID_VALUE An invalid tClock or ratio was specified
    @retval NCP_ST_TIMER_INIT_FAILED The timestamp logic could not be reinitialized
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_timer_adjust_clock_ratio(
                             ncp_hdl_t ncpHdl,
                             ncp_timer_clock_t tClock,
                             double ratio);

/*! @fn ncp_st_t ncp_timer_get_clock_ratio(ncp_hdl_t ncpHdl, ncp_timer_clock_t tClock, double *ratio)
    @brief Get the ratio that specifies the amount to increment the timestamp for each core clock cycle (i.e. ratio = frequency(timestamp) / frequency(core clock)).
    @param ncpHdl Incoming handle of the current NCP device
    @param tClock The core clock to which this ratio applies (NCP_TIMER_CLOCK_HIGH, NCP_TIMER_CLOCK_LOW, NCP_TIMER_CLOCK_LOW_TO_HIGH, NCP_TIMER_CLOCK_HIGH_TO_LOW, NCP_TIMER_CLOCK_BOOT_COUNT)
    @param ratio Returned value that specifies the ratio of timestamp frequency to core clock frequency
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_TIMER_INVALID_HANDLE The Timer module was not properly configured
    @retval NCP_ST_INVALID_VALUE An invalid tClock was specified
    @retval NCP_ST_DEV_INVALID_BUFFER ratio points to an invalid buffer
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_timer_get_clock_ratio(
                          ncp_hdl_t ncpHdl,
                          ncp_timer_clock_t tClock,
                          double *ratio);

/*! @fn ncp_st_t ncp_timer_get_timestamp(ncp_hdl_t ncpHdl, ncp_timer_ts_t timestamp, ncp_uint64_t *ticks)
    @brief Get the specified system timestamp 
    @param ncpHdl Incoming handle of the current NCP device
    @param timestamp The system timestamp to capture (NCP_TIMER_TIMESTAMP_CORE, NCP_TIMER_TIMESTAMP_REF_CLOCK, NCP_TIMER_TIMESTAMP_REF_STROBE)
    @param ticks Returned value that specifies the timestamp value.  The 64-bit value has a precision of 1/256 microseconds (i.e. shifting the value eight places to the right gives the value in microseconds)
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_TIMER_INVALID_HANDLE The Timer module was not properly configured
    @retval NCP_ST_INVALID_VALUE An invalid timestamp was specified
    @retval NCP_ST_DEV_INVALID_BUFFER ticks points to an invalid buffer
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_timer_get_timestamp(
                        ncp_hdl_t ncpHdl,
                        ncp_timer_ts_t timestamp,
                        ncp_uint64_t *ticks);

/*! @fn ncp_st_t ncp_timer_set_attribute(ncp_hdl_t ncpHdl, ncp_timer_ts_attrib_t attribute, ncp_uint64_t value)
    @brief Set the specified timestamp logic attribute
    @param ncpHdl Incoming handle of the current NCP device
    @param attribute Specifies the attribute to set (NCP_TIMER_TS_INIT_COUNT, NCP_TIMER_TS_REF_CLOCK_OUTPUT, NCP_TIMER_TS_REF_STROBE_OUTPUT, NCP_TIMER_TS_REF_CLOCK_IN_COUNT, NCP_TIMER_TS_REF_STROBE_OUT_WIDTH)
    @param value Specifies the value to assign to the attribute
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_TIMER_INVALID_HANDLE The Timer module was not properly configured
    @retval NCP_ST_INVALID_VALUE An invalid attribute or value was specified
    @retval NCP_ST_TIMER_INIT_FAILED The timestamp logic could not be reinitialized (only applies to NCP_TIMER_TS_INIT_COUNT)
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_timer_set_attribute(
                        ncp_hdl_t ncpHdl,
                        ncp_timer_ts_attrib_t attribute,
                        ncp_uint64_t value); 

/*! @fn ncp_st_t ncp_timer_get_attribute(ncp_hdl_t ncpHdl, ncp_timer_ts_attrib_t attribute, ncp_uint64_t *value)
    @brief Get the value of the specified timestamp logic attribute
    @param ncpHdl Incoming handle of the current NCP device
    @param attribute Specifies the attribute to get (NCP_TIMER_TS_INIT_COUNT, NCP_TIMER_TS_REF_CLOCK_OUTPUT, NCP_TIMER_TS_REF_STROBE_OUTPUT, NCP_TIMER_TS_REF_CLOCK_IN_COUNT, NCP_TIMER_TS_REF_STROBE_OUT_WIDTH)
    @param value Points to the returned value of the specified attribute
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_TIMER_INVALID_HANDLE The Timer module was not properly configured
    @retval NCP_ST_INVALID_VALUE An invalid attribute or value was specified
    @retval NCP_ST_DEV_INVALID_BUFFER value points to an invalid buffer
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_timer_get_attribute(
                        ncp_hdl_t ncpHdl,
                        ncp_timer_ts_attrib_t attribute,
                        ncp_uint64_t *value);

/*! @fn ncp_st_t ncp_timer_set_refstrobe_trigger(ncp_hdl_t ncpHdl)
    @brief Set the reference strobe strigger.  Trigger is cleared after being set
    @param ncpHdl Incoming handle of the current NCP device
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_TIMER_INVALID_HANDLE The Timer module was not properly configured
    @retval NCP_ST_TIMER_REF_STROBE_OUTPUT_NOT_ENABLED The reference strobe output is not enabled
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_timer_set_refstrobe_trigger(
                                ncp_hdl_t ncpHdl);

/*! @fn ncp_st_t ncp_timer_event_get(ncp_hdl_t ncpHdl, ncp_uint64_t *ticks)
    @brief Blocking wait on Timer reference strobe interrupt
    @param ncpHdl Incoming handle of the current NCP device
    @param ticks Returned value that specifies the timestamp value.  The 64-bit value has a precision of 1/256 microseconds (i.e. shifting the value eight places to the right gives the value in microseconds)
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_TIMER_INVALID_HANDLE The Timer module was not properly configured
    @retval NCP_ST_DEV_INVALID_BUFFER ticks points to an invalid buffer
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_timer_event_get(
                    ncp_hdl_t ncpHdl,
                    ncp_uint64_t *ticks);

/*! @fn ncp_st_t ncp_timer_refclk_select(ncp_hdl_t ncpHdl, ncp_timer_refclk_t tRefClock)
    @brief Select the timestamp logic reference clock
    @param ncpHdl Incoming handle of the current NCP device
    @param tRefClk The reference clock to be selected (NCP_TIMER_REF_CLOCK_INTERNAL, NCP_TIMER_REF_CLOCK_EXTERNAL)
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_TIMER_INVALID_HANDLE The Timer module was not properly configured
    @retval NCP_ST_NOT_IMPLEMENTED The API is not implemented in this configuration
    @retval NCP_ST_TIMER_INVALID_REFCLK An invalid reference clock was specified
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_timer_refclk_select(
                        ncp_hdl_t ncpHdl,
                        ncp_timer_refclk_t tRefClock);

/*! @fn ncp_st_t ncp_timer_sync_external(ncp_hdl_t ncpHdl)
    @brief Sync external clock to Axxia Time
    @param ncpHdl Incoming handle of the current NCP device
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_TIMER_INVALID_HANDLE The Timer module was not properly configured
    @retval NCP_ST_NOT_IMPLEMENTED The API is not implemented in this configuration
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_timer_sync_external(
                        ncp_hdl_t ncpHdl);

/*! @fn ncp_st_t ncp_timer_unsync_external(ncp_hdl_t ncpHdl)
    @brief Unsync external clock from Axxia Time
    @param ncpHdl Incoming handle of the current NCP device
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_TIMER_INVALID_HANDLE The Timer module was not properly configured
    @retval NCP_ST_NOT_IMPLEMENTED The API is not implemented in this configuration
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_timer_unsync_external(
                          ncp_hdl_t ncpHdl);

/*! @fn ncp_st_t ncp_timer_cpu_timer_alloc(ncp_hdl_t ncpHdl, ncp_uint32_t *timerIndex)
    @brief Request a CPU timer resource
    @param ncpHdl Incoming handle of the current NCP device
    @param timerIndex Timer index for the requested CPU timer.  Range from 0-15.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_TIMER_INVALID_HANDLE The Timer module was not properly configured
    @retval NCP_ST_DEV_INVALID_BUFFER timerIndex points to an invalid buffer
    @retval NCP_ST_NOT_IMPLEMENTED The API is not implemented in this configuration
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_timer_cpu_timer_alloc(
                          ncp_hdl_t ncpHdl,
                          ncp_uint32_t *timerIndex);

/*! @fn ncp_st_t ncp_timer_cpu_timer_start(ncp_hdl_t ncpHdl, ncp_uint64_t expires, ncp_uint64_t firstFireTime, ncp_uint32_t timerIndex, ncp_uint32_t timerFlags)
    @brief Start/enable a CPU timer
    @param ncpHdl Incoming handle of the current NCP device
    @param expires Interval after which the timer will expire, expressed
           as the integer number of time units.  The time unit used for the
           timer (seconds/milliseconds/microseconds) is determined by the value
           of timerFlags.
    @param firstFireTime The time for the first timer expiry.  firstFireTime will use the time unit specified in timerFlags.
    @param timerIndex Timer index for the requested CPU timer.  Range from 0-15.
    @param timerFlags Flags field to modify default behavior.  Valid values are
           NCP_TIMER_FLAGS_EXPIRES_MICROSECONDS, NCP_TIMER_FLAGS_EXPIRES_MILLISECONDS, and NCP_TIMER_FLAGS_EXPIRES_SECONDS.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_TIMER_INVALID_HANDLE The Timer module was not properly configured
    @retval NCP_ST_TIMER_INVALID_INDEX timerIndex is invalid
    @retval NCP_ST_TIMER_CPU_TIMER_NOT_ALLOCATED The specified timer has not been allocated
    @retval NCP_ST_TIMER_CPU_TIMER_NOT_STOPPED The specified timer is already started
    @retval NCP_ST_NOT_IMPLEMENTED The API is not implemented in this configuration
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_timer_cpu_timer_start(
                          ncp_hdl_t ncpHdl,
                          ncp_uint64_t expires,
                          ncp_uint64_t firstFireTime,
                          ncp_uint32_t timerIndex,
                          ncp_uint32_t timerFlags);

/*! @fn ncp_st_t ncp_timer_cpu_timer_stop(ncp_hdl_t ncpHdl, ncp_uint32_t timerIndex)
    @brief Disable a CPU timer
    @param ncpHdl Incoming handle of the current NCP device
    @param timerIndex Timer index for the requested CPU timer.  Range from 0-15.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_TIMER_INVALID_HANDLE The Timer module was not properly configured
    @retval NCP_ST_TIMER_INVALID_INDEX timerIndex is invalid
    @retval NCP_ST_TIMER_CPU_TIMER_NOT_ALLOCATED The specified timer has not been allocated
    @retval NCP_ST_TIMER_CPU_TIMER_NOT_STARTED The specified timer is not started
    @retval NCP_ST_NOT_IMPLEMENTED The API is not implemented in this configuration
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_timer_cpu_timer_stop(
                         ncp_hdl_t ncpHdl,
                         ncp_uint32_t timerIndex);

/*! @fn ncp_st_t ncp_timer_cpu_timer_free(ncp_hdl_t ncpHdl, ncp_uint32_t timerIndex)
    @brief Free a CPU timer resource
    @param ncpHdl Incoming handle of the current NCP device
    @param timerIndex Timer index for the requested CPU timer.  Range from 0-15.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_TIMER_INVALID_HANDLE The Timer module was not properly configured
    @retval NCP_ST_TIMER_INVALID_INDEX timerIndex is invalid
    @retval NCP_ST_TIMER_CPU_TIMER_NOT_ALLOCATED The specified timer has not been allocated
    @retval NCP_ST_TIMER_CPU_TIMER_NOT_STOPPED The specified timer is not stopped
    @retval NCP_ST_NOT_IMPLEMENTED The API is not implemented in this configuration
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_timer_cpu_timer_free(
                         ncp_hdl_t ncpHdl,
                         ncp_uint32_t timerIndex);

/*! @fn ncp_st_t ncp_timer_cpu_timer_event_wait(ncp_hdl_t hdl, ncp_uint32_t timerIndex, ncp_uint64_t lastSeq, ncp_uint64_t *currentSeq, ncp_uint32_t flags)
    @brief Block on CPU Timer event.  Blocks until a CPU timer fires with sequence number greater than lastSeq.
    @param hdl Incoming handle of the current NCP device
    @param timerIndex Timer index for the requested CPU timer.  Range from 0-15.
    @param lastSeq The last user-captured sequence number for this CPU timer
    @param currentSeq The returned sequence number for this CPU timer
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_TIMER_INVALID_HANDLE The Timer module was not properly configured
    @retval NCP_ST_TIMER_INVALID_INDEX timerIndex is invalid
    @retval NCP_ST_TIMER_CPU_TIMER_NOT_ALLOCATED The specified timer has not been allocated
    @retval NCP_ST_NOT_IMPLEMENTED The API is not implemented in this configuration
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_timer_cpu_timer_event_wait(
                               ncp_hdl_t hdl,
                               ncp_uint32_t timerIndex,
                               ncp_uint64_t lastSeq,
                               ncp_uint64_t *currentSeq,
                               ncp_uint32_t flags);

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* _NCP_TMGR_H_ */
