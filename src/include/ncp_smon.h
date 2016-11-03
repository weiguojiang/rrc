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

/*! @file      ncp_smon.h
 *  @brief     System Monitor
 * 
 *  @addtogroup _smon_ System Monitor
 * 
 *  @{
 */

#ifndef _NCP_SMON_H_
#define _NCP_SMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#define NCP_SMON_FLAGS_INTERRUPT_TIMER_OVFLOW             (1 << 0)
#define NCP_SMON_FLAGS_INTERRUPT_COUNTER_OVFLOW           (1 << 1)
#define NCP_SMON_FLAGS_STOP_TIMER_OVFLOW                  (1 << 2)
#define NCP_SMON_FLAGS_STOP_COUNTER_OVFLOW                (1 << 3)
#define NCP_SMON_FLAGS_RESUME                             (1 << 4)

  /* aliases over architectures */

#define NCP_SMON_MODULE_MME NCP_SMON_MODULE_MMB
#define NCP_SMON_MODULE_MPPY NCP_SMON_MODULE_MPPX
#define NCP_SMON_SUBMODULE_SE_ST0_L1 NCP_SMON_SUBMODULE_SE_ST_L1
#define NCP_SMON_MODULE_NCAV2_AXI NCP_SMON_MODULE_NCA_AXI
#define NCP_SMON_MODULE_NCAV2 NCP_SMON_MODULE_NCA
#define NCP_SMON_SUBMODULE_CORE0 NCP_SMON_SUBMODULE_CORE
#define NCP_SMON_SUBMODULE_QE0 NCP_SMON_SUBMODULE_QE

/*!
 * @enum   ncp_smon_module_t
 * @brief  This enum defines the modules within which SMON logic can be
 *         manipulated
 */
typedef enum
{
    /*!
     * @brief DPI: 0xe.X.X
     */
    NCP_SMON_MODULE_DPI,
    /*!
     * @brief EIOA0: 0x1f.X.X
     */
    NCP_SMON_MODULE_EIOA0,
    /*!
     * @brief EIOA1: 0x17.X.X
     */
    NCP_SMON_MODULE_EIOA1,
    /*!
     * @brief MMB/MME: 0x15.X.X
     */
    NCP_SMON_MODULE_MMB,
    /*!
     * @brief MPPX: 0x1a.X.X
     */
    NCP_SMON_MODULE_MPPX,
    /*!
     * @brief MTM: 0x14.X.X
     */
    NCP_SMON_MODULE_MTM,
    /*!
     * @brief NCA: 0x16.X.X
     */
    NCP_SMON_MODULE_NCA,
    /*!
     * @brief PAB: 0x1c.X.X
     */
    NCP_SMON_MODULE_PAB,
    /*!
     * @brief PIC: 0x1b.X.X
     */
    NCP_SMON_MODULE_PIC,
    /*!
     * @brief SED: 0xc.X.X
     */
    NCP_SMON_MODULE_SED,
    /*!
     * @brief SPP: 0xb.X.X
     */
    NCP_SMON_MODULE_SPP,
    /*!
     * @brief Timer Manager: 0x19.X.X
     */
    NCP_SMON_MODULE_TIMER,
    /*!
     * @brief NCA AXI: 0x101.X.X
     */
    NCP_SMON_MODULE_NCA_AXI,
    /*!
     * @brief EIOASM0: 0x28.X.X (55xx only)
     */
    NCP_SMON_MODULE_EIOASM0,
    /*!
     * @brief EIOASM1: 0x29.X.X (55xx only)
     */
    NCP_SMON_MODULE_EIOASM1,
    /*!
     * @brief EIOAS2: 0x2a.X.X (55xx only)
     */
    NCP_SMON_MODULE_EIOAS2,
    /*!
     * @brief EIOAS3: 0x2b.X.X (55xx only)
     */
    NCP_SMON_MODULE_EIOAS3,
    /*!
     * @brief EIOAS4: 0x2c.X.X (55xx only)
     */
    NCP_SMON_MODULE_EIOAS4,
    /*!
     * @brief EIOAS5: 0x2d.X.X (55xx only)
     */
    NCP_SMON_MODULE_EIOAS5,
    /*!
     * @brief PCX: 0x2e.X.X (55xx only)
     */
    NCP_SMON_MODULE_PCX,
    /*!
     * @brief CCM: 0x2f.X.X (55xx only)
     */
    NCP_SMON_MODULE_CCM,
    /*!
     * @brief CCMS: 0x30.X.X (55xx only)
     */
    NCP_SMON_MODULE_CCMS,
    /*!
     * @brief PBM: 0x33.X.X (55xx only)
     */
    NCP_SMON_MODULE_PBM,
    /*!
     * @brief PEI0: 0x100.X.X (55xx only)
     */
    NCP_SMON_MODULE_PEI0,
    /*!
     * @brief PEI2: 0x106.X.X (55xx only)
     */
    NCP_SMON_MODULE_PEI2,
    /*!
     * @brief SRIO0: 0x102.X.X (55xx only)
     */
    NCP_SMON_MODULE_SRIO0,
    /*!
     * @brief SRIO1: 0x107.X.X (55xx only)
     */
    NCP_SMON_MODULE_SRIO1,
    /*!
     * @brief PB0: 0x80.X.X (55xx only)
     */
    NCP_SMON_MODULE_PB0,
    /*!
     * @brief PB1: 0x81.X.X (55xx only)
     */
    NCP_SMON_MODULE_PB1,
    /*!
     * @brief PB2: 0x82.X.X (55xx only)
     */
    NCP_SMON_MODULE_PB2,
    /*!
     * @brief PB3: 0x83.X.X (55xx only)
     */
    NCP_SMON_MODULE_PB3,
    /*!
     * @brief PB4: 0x84.X.X (55xx only)
     */
    NCP_SMON_MODULE_PB4,
    /*!
     * @brief PB5: 0x85.X.X (55xx only)
     */
    NCP_SMON_MODULE_PB5,
    /*!
     * @brief PB6: 0x86.X.X (55xx only)
     */
    NCP_SMON_MODULE_PB6,
    /*!
     * @brief PB7: 0x87.X.X (55xx only)
     */
    NCP_SMON_MODULE_PB7,
    /*!
     * @brief ELM0: 0x158.X.X (55xx only)
     */
    NCP_SMON_MODULE_ELM0,
    /*!
     * @brief ELM1: 0x159.X.X (55xx only)
     */
    NCP_SMON_MODULE_ELM1,
    /*!
     * @brief ISB: 0x31.X.X (55xx only)
     */
    NCP_SMON_MODULE_ISB,
    /*!
     * @brief ISBS: 0x32.X.X (55xx only)
     */
    NCP_SMON_MODULE_ISBS,
    /*!
     * @brief RING_BP: 0x34.X.X (55xx only)
     */
    NCP_SMON_MODULE_RING_BP
} ncp_smon_module_t;

/*!
 * @enum   ncp_smon_submodule_t
 * @brief  This enum defines the submodules for each module within which
 * SMON logic can be manipulated
 */
typedef enum
{
    /*!
     * @brief Core register submodule
     */
    NCP_SMON_SUBMODULE_CORE,
    /*!
     * @brief L1 cache submodule
     */
    NCP_SMON_SUBMODULE_L1,
    /*!
     * @brief nu_cow MCIP submodule
     */
    NCP_SMON_SUBMODULE_MCIP,
    /*!
     * @brief nu_cow TCLD0 submodule
     */
    NCP_SMON_SUBMODULE_TCLD0,
    /*!
     * @brief nu_cow TCLD1 submodule
     */
    NCP_SMON_SUBMODULE_TCLD1,
    /*!
     * @brief nu_cow TCLS submodule
     */
    NCP_SMON_SUBMODULE_TCLS,
    /*!
     * @brief nu_cow TDBI submodule
     */
    NCP_SMON_SUBMODULE_TDBI,
    /*!
     * @brief nu_cow TDGL submodule
     */
    NCP_SMON_SUBMODULE_TDGL,
    /*!
     * @brief nu_cow TGL submodule
     */
    NCP_SMON_SUBMODULE_TGL,
    /*!
     * @brief nu_cow TIL submodule
     */
    NCP_SMON_SUBMODULE_TIL,
    /*!
     * @brief MPPX etac_core_0, SMON 0
     */
    NCP_SMON_SUBMODULE_ETAC0_0,
    /*!
     * @brief MPPX etac_core_1, SMON 0
     */
    NCP_SMON_SUBMODULE_ETAC1_0,
    /*!
     * @brief MPPX etac_core_2, SMON 0
     */
    NCP_SMON_SUBMODULE_ETAC2_0,
    /*!
     * @brief MPPX etac_core_3, SMON 0
     */
    NCP_SMON_SUBMODULE_ETAC3_0,
    /*!
     * @brief MPPX etac_core_0, SMON 1
     */
    NCP_SMON_SUBMODULE_ETAC0_1,
    /*!
     * @brief MPPX etac_core_1, SMON 1
     */
    NCP_SMON_SUBMODULE_ETAC1_1,
    /*!
     * @brief MPPX etac_core_2, SMON 1
     */
    NCP_SMON_SUBMODULE_ETAC2_1,
    /*!
     * @brief MPPX etac_core_3, SMON 1
     */
    NCP_SMON_SUBMODULE_ETAC3_1,
    /*!
     * @brief MPPX FBI submodule
     */
    NCP_SMON_SUBMODULE_FBI,
    /*!
     * @brief MPPX HE submodule, MSM SMON
     */
    NCP_SMON_SUBMODULE_HE_MSM,
    /*!
     * @brief MPPX HE submodule, ORD SMON
     */
    NCP_SMON_SUBMODULE_HE_ORD,
    /*!
     * @brief MPPX MPIC submodule
     */
    NCP_SMON_SUBMODULE_MPIC,
    /*!
     * @brief MPPX SEM submodule
     */
    NCP_SMON_SUBMODULE_SEM,
    /*!
     * @brief MPPX State Engine submodule
     */
    NCP_SMON_SUBMODULE_SE,
    /*!
     * @brief Compute Engine submodule
     */
    NCP_SMON_SUBMODULE_CE,
    /*!
     * @brief MPPX State Engine cepc L1 PLC submodule
     */
    NCP_SMON_SUBMODULE_SE_CE_L1,
    /*!
     * @brief MPPX State Engine stpc L1 PLC submodule
     */
    NCP_SMON_SUBMODULE_SE_ST_L1,
    /*!
     * @brief MTM Buffer Manager Compute Engine submodule
     */
    NCP_SMON_SUBMODULE_BUFMAN_CE,
    /*!
     * @brief MTM Traffic Shaper Compute Engine submodule
     */
    NCP_SMON_SUBMODULE_TS_CE,
    /*!
     * @brief MTM BP_Agg TDBI SMON
     */
    NCP_SMON_SUBMODULE_BP_AGG,
    /*!
     * @brief MTM Registers Deq0 SMON
     */
    NCP_SMON_SUBMODULE_DEQUEUE0,
    /*!
     * @brief MTM Registers Deq1 SMON
     */
    NCP_SMON_SUBMODULE_DEQUEUE1,
    /*!
     * @brief MTM Registers Enq0 SMON
     */
    NCP_SMON_SUBMODULE_ENQUEUE0,
    /*!
     * @brief MTM Registers Enq1 SMON
     */
    NCP_SMON_SUBMODULE_ENQUEUE1,
    /*!
     * @brief MTM Level1_L1 submodule
     */
    NCP_SMON_SUBMODULE_LEVEL1_L1,
    /*!
     * @brief MTM Level2_L1 submodule
     */
    NCP_SMON_SUBMODULE_LEVEL2_L1,
    /*!
     * @brief MTM Level3_L1 submodule
     */
    NCP_SMON_SUBMODULE_LEVEL3_L1,
    /*!
     * @brief MTM Level4_L1 submodule
     */
    NCP_SMON_SUBMODULE_LEVEL4_L1,
    /*!
     * @brief MTM Level5_L1 submodule
     */
    NCP_SMON_SUBMODULE_LEVEL5_L1,
    /*!
     * @brief MTM Registers QE0 SMON
     */
    NCP_SMON_SUBMODULE_QE,
    /*!
     * @brief MTM Queue_L1 submodule
     */
    NCP_SMON_SUBMODULE_QUEUE_L1,
    /*!
     * @brief MTM SH_L1 submodule
     */
    NCP_SMON_SUBMODULE_SH_L1,
    /*!
     * @brief MTM output_tgl_address_map submodule
     */
    NCP_SMON_SUBMODULE_TGL_OUT,
    /*!
     * @brief MTM ext_exp_unicast_tgl_address_map submodule
     */
    NCP_SMON_SUBMODULE_TGL_UNI,
    /*!
     * @brief MTM til_input_address_map submodule
     */
    NCP_SMON_SUBMODULE_TIL_INPUT,
    /*!
     * @brief MTM til_launch_address_map submodule
     */
    NCP_SMON_SUBMODULE_TIL_LAUNCH,
    /*!
     * @brief MTM til_inp_merge_address_map submodule
     */
    NCP_SMON_SUBMODULE_TIL_MERGE,
    /*!
     * @brief PAB Base L1 submodule
     */
    NCP_SMON_SUBMODULE_BASE_L1,
    /*!
     * @brief PAB Ext L1 submodule
     */
    NCP_SMON_SUBMODULE_EXT_L1,
    /*!
     * @brief EIOA Debug submodule
     */
    NCP_SMON_SUBMODULE_DEBUG,
    /*!
     * @brief EIOA IPP0 submodule
     */
    NCP_SMON_SUBMODULE_IPP0,
    /*!
     * @brief EIOA IPP1 submodule
     */
    NCP_SMON_SUBMODULE_IPP1,
    /*!
     * @brief MME Core1 submodule
     */
    NCP_SMON_SUBMODULE_CORE1,
    /*!
     * @brief MPP ETAC4_0 submodule
     */
    NCP_SMON_SUBMODULE_ETAC4_0,
    /*!
     * @brief MPP ETAC4_1 submodule
     */
    NCP_SMON_SUBMODULE_ETAC4_1,
    /*!
     * @brief MPP ETAC5_0 submodule
     */
    NCP_SMON_SUBMODULE_ETAC5_0,
    /*!
     * @brief MPP ETAC5_1 submodule
     */
    NCP_SMON_SUBMODULE_ETAC5_1,
    /*!
     * @brief MPP ETAC6_0 submodule
     */
    NCP_SMON_SUBMODULE_ETAC6_0,
    /*!
     * @brief MPP ETAC6_1 submodule
     */
    NCP_SMON_SUBMODULE_ETAC6_1,
    /*!
     * @brief MPP ETAC7_0 submodule
     */
    NCP_SMON_SUBMODULE_ETAC7_0,
    /*!
     * @brief MPP ETAC7_1 submodule
     */
    NCP_SMON_SUBMODULE_ETAC7_1,
    /*!
     * @brief MPP SCH submodule
     */
    NCP_SMON_SUBMODULE_SCH,
    /*!
     * @brief MPP HE MSM Dual submodule
     */
    NCP_SMON_SUBMODULE_HE_MSM_DUAL,
    /*!
     * @brief MTM QE1 submodule
     */
    NCP_SMON_SUBMODULE_QE1,
    /*!
     * @brief MTM ENQ0 submodule
     */
    NCP_SMON_SUBMODULE_ENQ0,
    /*!
     * @brief MTM ENQ1 submodule
     */
    NCP_SMON_SUBMODULE_ENQ1,
    /*!
     * @brief PAB CORE2 submodule
     */
    NCP_SMON_SUBMODULE_CORE2,
    /*!
     * @brief NCAV2_AXI TASK submodule
     */
    NCP_SMON_SUBMODULE_TASK,
    /*!
     * @brief NCAV2_AXI TASK 1 submodule
     */
    NCP_SMON_SUBMODULE_TASK1,
    /*!
     * @brief PCX CHAIN_IF submodule
     */
    NCP_SMON_SUBMODULE_CHAIN_IF,
    /*!
     * @brief SRIO RAB_CFG submodule
     */
    NCP_SMON_SUBMODULE_RAB_CFG,
    /*!
     * @brief ELM SBSX_MON submodule
     */
    NCP_SMON_SUBMODULE_SBSX_MON,
    /*!
     * @brief ISBS BP_AGG_TDBI submodule
     */
    NCP_SMON_SUBMODULE_BP_AGG_TDBI,
    /*!
     * @brief MPPY State Engine stpc1 L1 PLC submodule
     */
    NCP_SMON_SUBMODULE_SE_ST1_L1
} ncp_smon_submodule_t;

/*!
 * @enum   ncp_smon_mode_t
 * @brief  This enum defines the SMON modes of operation, which in turn define
 *         how the counters and timer are used.
 */
typedef enum
{
    /*!
     * @brief Counter 0 and Counter 1 run independently of each other
     */
    NCP_SMON_MODE_INDEPENDENT,
    /*!
     * @brief Counter 0 event starts the Timer, Counter 1 event stops the Timer,
     *        Counter 0 accumulates event occurrences, Counter 1 accumulates
     *        timestamps.  For multiple stops per start, accumulate each
     *        start-to-stop.
     */
    NCP_SMON_MODE_AVG_LATENCY,
    /*!
     * @brief Counter 0 event starts the Timer, Counter 1 event stops the Timer,
     *        Counter 0 captures minimum timestamp, Counter 1 captures maximum timestamp
     */
    NCP_SMON_MODE_MINMAX_LATENCY,
    /*!
     * @brief Counter 0 event increments Counter 0, values are accumulated in Counter 1,
     *        Counter 1 events are disabled
     */
    NCP_SMON_MODE_AVG,
    /*!
     * @brief Counter 0 event starts the Timer, Counter 1 event stops the Timer,
     *        Counter 0 accumulates event occurrences, Counter 1 accumulates
     *        timestamps.  For multiple stops per start, only accumulate the
     *        first start-to-stop.
     */
    NCP_SMON_MODE_AVG_LATENCY_2,
    /*!
     * @brief Counter 0 event starts the Timer, Counter 1 event stops the Timer,
     *        Counter 0 accumulates event occurrences, Counter 1 accumulates
     *        timestamps.  For multiple stops per start, accumulate the
     *        incremental start-to-stops with the initial one.
     */
    NCP_SMON_MODE_AVG_LATENCY_3
} ncp_smon_mode_t;

/*!
 * @enum   ncp_smon_function_t
 * @brief  This enum defines the SMON functions, which in turn define
 *         when the counters and timer are updated.
 */
typedef enum
{
    /*!
     * @brief Trigger accumulates value into SMON Count when event is valid
     */
    NCP_SMON_FUNCTION_FREE_RUNNING,
    /*!
     * @brief Trigger accumulates value into SMON Count when event is valid
     *        and compared matches Compare value
     */
    NCP_SMON_FUNCTION_COMPARE,
    /*!
     * @brief Trigger accumulates value into SMON Count when event is valid
     *        and larger than current value stored in SMON Count
     */
    NCP_SMON_FUNCTION_MAX,
    /*!
     * @brief Capture Timer value on first occurrence of event
     */
    NCP_SMON_FUNCTION_TIMESTAMP_FIRST,
    /*!
     * @brief Capture Timer value on every occurrence of event
     */
    NCP_SMON_FUNCTION_TIMESTAMP,


    /*!
     * @brief Trigger increments SMON Count when event is valid (55xx only)
     */
    NCP_SMON_FUNCTION_FREE_RUNNING_INCR,
    /*!
     * @brief Trigger accumulates value into SMON Count when event is valid,
     *        and compared matches Compare value (55xx only)
     */
    NCP_SMON_FUNCTION_FREE_RUNNING_COMPARE,
    /*!
     * @brief Trigger increments SMON Count when event is valid, using Compare
     *        value (55xx only)
     */
    NCP_SMON_FUNCTION_FREE_RUNNING_INCR_COMPARE,
    /*!
     * @brief Trigger accumulates value into SMON Count when event is valid
     *        and larger than current value stored in SMON Count, using compare
     *        (55xx only)
     */
    NCP_SMON_FUNCTION_MAX_COMPARE,
    /*!
     * @brief Capture Timer value on first occurrence of event, using compare (55xx only)
     */
    NCP_SMON_FUNCTION_TIMESTAMP_FIRST_COMPARE,
    /*!
     * @brief Capture Timer value on every occurrence of event, using compare (55xx only)
     */
    NCP_SMON_FUNCTION_TIMESTAMP_COMPARE
} ncp_smon_function_t;

/* APIs */

/*! @fn ncp_st_t ncp_smon_init(ncp_hdl_t ncpHdl, ncp_smon_module_t module,
        ncp_smon_module_t submodule, ncp_uint8_t event0, ncp_uint8_t event1,
        ncp_smon_mode_t mode, ncp_smon_function_t function0,
        ncp_smon_function_t function1,
        ncp_uint32_t compare0, ncp_uint32_t compare1, ncp_uint32_t timerMaxVal,
        ncp_uint8_t  timerPrescale, ncp_uint32_t flags)
    @brief Initializes the SMON logic for a given module and submodule
    @param ncpHdl Incoming handle of the current NCP device
    @param module Target NCP module for SMON initialization.  Any member
           of the ncp_smon_module_t enum is valid.
    @param submodule Target NCP submodule for SMON initialization.  Members of the
           ncp_smon_submodule_t that correspond to SMON regions within the
           given module are valid.
    @param event0 Signal input for SMON counter0.  The signal table is submodule
           specific.  Refer to the SMON Logic documentation for details.
    @param event1 Signal input for SMON counter1.  The signal table is submodule
           specific.  Refer to the SMON Logic documentation for details.
    @param mode Mode of SMON operation, describing how timer and counters are
           used.  Can be NCP_SMON_MODE_INDEPENDENT, NCP_SMON_MODE_AVG_LATENCY,
           NCP_SMON_MODE_MINMAX_LATENCY, or NCP_SMON_MODE_AVG.
    @param function0 SMON0 function, describing when timer and counters are updated.
           Can be NCP_SMON_FUNCTION_FREE_RUNNING, NCP_SMON_FUNCTION_COMPARE,
           NCP_SMON_FUNCTION_MAX, NCP_SMON_FUNCTION_TIMESTAMP_FIRST, or
           NCP_SMON_FUNCTION_TIMESTAMP.
    @param function1 SMON1 function, describing when timer and counters are updated.
           Can be NCP_SMON_FUNCTION_FREE_RUNNING, NCP_SMON_FUNCTION_COMPARE,
           NCP_SMON_FUNCTION_MAX, NCP_SMON_FUNCTION_TIMESTAMP_FIRST, or
           NCP_SMON_FUNCTION_TIMESTAMP.
    @param compare0 Compare register for counter0, used when Compare function is
           specified
    @param compare1 Compare register for counter1, used when Compare function is
           specified
    @param timerMaxVal The maximum timer value used for comparison
    @param timerPrescale The number of clock ticks for each timer increment.  The
           actual number of ticks is 2^timerPrescale.  Valid values are in the range
           of 0 to 19.
    @param flags Specifies various modes of execution.  Can specify interrupt or
           stop on timer or counter overflow, or can specify whether to reset counters
           or resume counting.  Can be any OR'd combination of
           NCP_SMON_FLAGS_INTERRUPT_TIMER_OVFLOW, NCP_SMON_FLAGS_INTERRUPT_COUNTER_OVFLOW,
           NCP_SMON_FLAGS_STOP_TIMER_OVFLOW, NCP_SMON_FLAGS_STOP_COUNTER_OVFLOW, and
           NCP_SMON_FLAGS_RESUME.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_SMON_INVALID_PRESCALE An invalid value was passed in the timerPrescale field
    @retval NCP_ST_SMON_INVALID_MODULE A value was passed in the module field that does not
            correspond to a valid system module
    @retval NCP_ST_SMON_INVALID_SUBMODULE A value was passed in the submodule field that does not
            correspond to a valid SMON region for the given system module
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_smon_init(
              ncp_hdl_t ncpHdl,
              ncp_smon_module_t module,
              ncp_smon_module_t submodule,
              ncp_uint8_t event0,
              ncp_uint8_t event1,
              ncp_smon_mode_t mode,
              ncp_smon_function_t function0,
              ncp_smon_function_t function1,
              ncp_uint32_t compare0,
              ncp_uint32_t compare1,
              ncp_uint32_t timerMaxVal,
              ncp_uint8_t  timerPrescale,  /* actual prescale is 2^timerPrescale */
              ncp_uint32_t flags);

/*! @fn ncp_st_t ncp_smon_query(
                     ncp_hdl_t ncpHdl,
                     ncp_smon_module_t  module,
                     ncp_smon_submodule_t submodule,
                     ncp_uint32_t *count0,
                     ncp_uint32_t *count1,
                     ncp_uint32_t *timer,
                     ncp_bool_t *timerOvf,
                     ncp_bool_t *count0Ovf,
                     ncp_bool_t *count1Ovf)

    @brief Queries the SMON logic of the specified module and submodule for counter0,
           counter1, and timer values
    @param ncpHdl Incoming handle of the current NCP device
    @param module target NCP module for SMON query.  Any member
           of the ncp_smon_module_t enum is valid.
    @param submodule target NCP submodule for SMON query.  Members of the
           ncp_smon_submodule_t that correspond to SMON regions within the
           given module are valid.
    @param counter0 Returned value of the counter0 register
    @param counter1 Returned value of the counter1 register
    @param timer Returned value of the timer register
    @param timerOvf Returned timer overflow status.  0 if false, 1 if true.
    @param count0Ovf Returned count0 overflow status.  0 if false, 1 if true.
    @param count1Ovf Returned count1 overflow status.  0 if false, 1 if true.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_DEV_INVALID_BUFFER An invalid pointer was passed in the count0, count1, timer, timerOvf,
            count0Ovf, or count1Ovf field
    @retval NCP_ST_SMON_INVALID_MODULE A value was passed in the module field that does not
            correspond to a valid system module
    @retval NCP_ST_SMON_INVALID_SUBMODULE A value was passed in the submodule field that does not
            correspond to a valid SMON region for the given system module
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_smon_query(
               ncp_hdl_t ncpHdl,
               ncp_smon_module_t  module,
               ncp_smon_submodule_t submodule,
               ncp_uint32_t *count0,
               ncp_uint32_t *count1,
               ncp_uint32_t *timer,
               ncp_bool_t *timerOvf,
               ncp_bool_t *count0Ovf,
               ncp_bool_t *count1Ovf);

/*! @fn ncp_st_t ncp_smon_stop(
                    ncp_hdl_t ncpHdl,
                    ncp_smon_module_t module,
                    ncp_smon_submodule_t submodule)

    @brief Disables the SMON logic of the specified module and submodule
    @param ncpHdl Incoming handle of the current NCP device
    @param module target NCP module for SMON initialization.  Any member
           of the ncp_smon_module_t enum is valid.
    @param submodule target NCP submodule for SMON initialization.  Members of the
           ncp_smon_submodule_t that correspond to SMON regions within the
           given module are valid.

    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_SMON_INVALID_MODULE A value was passed in the module field that does not
            correspond to a valid system module
    @retval NCP_ST_SMON_INVALID_SUBMODULE A value was passed in the submodule field that does not
            correspond to a valid SMON region for the given system module
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_smon_stop(
              ncp_hdl_t ncpHdl,
              ncp_smon_module_t module,
              ncp_smon_submodule_t submodule);

/*! @fn ncp_st_t ncp_smon_queue_select(
                    ncp_hdl_t ncpHdl,
                    ncp_smon_module_t module,
                    ncp_smon_submodule_t submodule,
                    ncp_uint32_t queue)

    @brief Select the queue to monitor for a specified module and submodule.  Should be set before the selected SMON is initialized
    @param ncpHdl Incoming handle of the current NCP device
    @param module target NCP module for SMON initialization
    @param submodule target NCP submodule for SMON initialization
    @param queue Queue ID for target SMON (for queue-based statistics)
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_SMON_INVALID_MODULE A value was passed in the module field that does not correspond to a valid system module
    @retval NCP_ST_SMON_INVALID_SUBMODULE A value was passed in the submodule field that does not correspond to a valid SMON region for the given system module
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_smon_queue_select(
                      ncp_hdl_t ncpHdl,
                      ncp_smon_module_t module,
                      ncp_smon_submodule_t submodule,
                      ncp_uint32_t queue);

/*! @fn ncp_st_t ncp_smon_mux_select(
                    ncp_hdl_t ncpHdl,
                    ncp_smon_module_t module,
                    ncp_smon_submodule_t submodule,
                    ncp_uint32_t muxa,
                    ncp_uint32_t muxb,
                    ncp_uint32_t muxa_mode,
                    ncp_uint32_t muxb_mode)

    @brief Select the muxes to use for a NCA mux-based statistics.  Should be set before the selected SMON is initialized
    @param ncpHdl Incoming handle of the current NCP device
    @param module target NCP module for SMON initialization
    @param submodule target NCP submodule for SMON initialization
    @param muxa Mux A for target SMON (for mux-based NCA statistics)
    @param muxb Mux B for target SMON (for mux-based NCA statistics)
    @param muxa_mode Mux A param mode for target SMON.  0: bit is selected by corresponding Mux A bit, 1: logical OR of all bits, 2: logical AND of all bits
    @param muxb_mode Mux B param mode for target SMON.  0: bit is selected by corresponding Mux B bit, 1: logical OR of all bits, 2: logical AND of all bits
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_SMON_INVALID_MODULE A value was passed in the module field that does not correspond to a valid system module
    @retval NCP_ST_SMON_INVALID_SUBMODULE A value was passed in the submodule field that does not correspond to a valid SMON region for the given system module
    @retval NCP_ST_NOT_IMPLEMENTED Not implemented for this architecture
    @retval NCP_ST_SMON_INVALID_MUX An invalid Mux was specified
    @retval NCP_ST_SMON_INVALID_MUX_MODE An invalid Mux mode was specified
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_smon_mux_select(
                    ncp_hdl_t ncpHdl,
                    ncp_smon_module_t module,
                    ncp_smon_submodule_t submodule,
                    ncp_uint32_t muxa,
                    ncp_uint32_t muxb,
                    ncp_uint32_t muxa_mode,
                    ncp_uint32_t muxb_mode);

/*! @fn ncp_st_t ncp_smon_param_select(
                    ncp_hdl_t ncpHdl,
                    ncp_smon_module_t module,
                    ncp_smon_submodule_t submodule,
                    ncp_uint32_t param)

    @brief Select the parameter to use for PB parameter-based statistics.  Should be set before the selected SMON is initialized
    @param ncpHdl Incoming handle of the current NCP device
    @param module target NCP module for SMON initialization
    @param submodule target NCP submodule for SMON initialization
    @param param Param for target SMON (for param-based statistics)
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_SMON_INVALID_MODULE A value was passed in the module field that does not correspond to a valid system module
    @retval NCP_ST_SMON_INVALID_SUBMODULE A value was passed in the submodule field that does not correspond to a valid SMON region for the given system module
    @retval NCP_ST_NOT_IMPLEMENTED Not implemented for this architecture
    @retval NCP_ST_SMON_INVALID_PARAM An invalid param was specified
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_smon_param_select(
                      ncp_hdl_t ncpHdl,
                      ncp_smon_module_t module,
                      ncp_smon_submodule_t submodule,
                      ncp_uint32_t param);


#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* _NCP_SMON_H_ */
