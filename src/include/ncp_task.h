/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

 
/*! @file      ncp_task.h
 *
 *  @brief     Task I/O APIs
 *
 *  @addtogroup _task_ Task Management
 *             
 *  @details   This document discusses the APIs for, and high level design of, the runtime software 
 *             interfaces that enable the host CPU to send tasks to and receive tasks from virtual 
 *             pipelines.
 *             The CPU communicates with other engines in the system via tasks. The CPU sends and 
 *             receives tasks using very efficient, cacheable memory based producer-consumer style 
 *             DMA queues. These queues are called task queues and hardware support for task queues 
 *             is provided by the Nuevo CPU Adapter (NCA). Four types of task queues are supported: 
 *             task input queues, task output queues,   task completion queues,  and NCA task 
 *             receive buffer queues.     Note that input (Rx) and output (Tx) directions are from 
 *             the CPU?s perspective. That is, the CPU transmits tasks using task output queues and 
 *             receives tasks using task input queues.  The CPU uses task completion queues to 
 *             notify the NCA that processing is complete for a particular task.   Similarly,   the 
 *             CPU uses NCA task receive buffer queues to provide buffers to the NCA?s receive 
 *             buffer pool.
 *             The NCA is designed for multi-core CPUs and therefore provides redundant resources 
 *             to allow independent operation of each core (i.e. no shared resource contention 
 *             issues between cores). The first implementation of Nuevo is designed to support up 
 *             to 6 (4 internal + 2 external) CPUs. It provides 24 task input queues and 12 task 
 *             output,  completion,   and receive buffer queues. The motivation behind the 24 task 
 *             input queue number is to provide a minimum of 4 input queues per CPU core. This 
 *             allows each core to have high and low priority user mode and kernel mode task input 
 *             queues. The reason for 12 task output queues is to provide each CPU core with both a 
 *             user mode and kernel mode task output queue. Note that the queue usages mentioned 
 *             here are only for design sizing purposes. All NCA task queues are general purpose 
 *             and can be partitioned in any number of different ways, as configured by software.
 *             In addition to the 24 task input queues described above, the NCA provides a total of 
 *             8 logical task input queues where each logical queue can be mapped to as many as 8 
 *             real input queues. The NCA performs load balancing and ordering (if configured to do 
 *             so) for tasks sent to logical queues.
 *             As noted above the NCA design sizing accounts for the possibility of having both 
 *             ?user mode? and ?kernel mode? queues. This comes from the requirement to support a 
 *             very efficient (low CPU overhead) runtime environment for Linux user mode 
 *             applications. 
 *  @note      As noted above,  the NCA exposes numerous queues that are used to interact with the
 *             CPU in order to accomplish sending and receiving tasks.   Output queues can be used
 *             in either exclusive or shared mode. Exclusive mode 
 *             assumes that there will be no contention for the queue between multiple threads
 *             or processes.   In this mode,   no locking or other means of access synchronization
 *             are employed.   Exclusive mode therefore provides the highest level of performance
 *             since applications interact directly with the target NCA hardware queue in a lockless manner.
 *             Serialization using mutual exclusion primitives is required when output queues are shared,      
 *             so shared queues will not allow for maximum performance.
 * @note       When a task handle is created,   the RTE stores  a copy of the handle in thread local storage.   Following NCA config,
 *             the RTE creates a default task handle,   and that handle persists for the duration of config.  This allows non-NCA RTE SW executing
 *             at config time to send tasks as part of engine configuration without needing to understand task handle creation,
 *             or thread queue sets (TQS).  Rather,   the RTE engine configuration SW will pass NULL for the task handle and
 *             the RTE, seeing NULL,  will queuery thread local storage to retreive the task handle.    This scheme will technically work for end user
 *             applications,   but is highly discouraged,   since accessing thread local storage is inefficient,   and doing so
 *             could dramatically impact throughput and latency.  
 *
 * @note       It is invalid for a thread to use a task handle created by a different thread.
 * @note       If an API returns an error status,   then all output (returned) parameter values are undefined and
 *             must not be used.
 * 
 *  @{
 */

#ifndef __ncp_task_h__
#define __ncp_task_h__

#ifdef __cplusplus
extern "C" { 
#endif
 
/*!
 * @brief ncp_raw_addr_t :   Special type used to help prevent compilation warnings.   The size of this data
 * structure will depend on the architecture of the target processor.
 *
*/
#ifdef NCP_64
typedef ncp_uint64_t ncp_raw_addr_t;
#else
typedef ncp_uint32_t ncp_raw_addr_t;
#endif


/*! 
 *  @brief Task IO Handle:  Obtained by calling ncp_task_hdl_create().  
 *       Once created,   the task handle is supplied as a parameter to all other TaskIO APIs
*/
typedef void  * ncp_task_hdl_t;

/*! 
 * @brief Raw Receive Handle: Obtained by calling ncp_task_recv_queue_bind().  
 *       Once created, the raw receive handle is supplied as a parameter to the
 *       raw receive function.
*/
typedef void* ncp_task_raw_recv_hdl_t;

/*! 
 *  @brief NCP_TASK_PARAM_SIZE_BYTES :   Constant equal to the number of bytes of parameter data supported by Task I/O APIs
 *  that receive or transmit tasks.
*/
#define NCP_TASK_PARAM_SIZE_BYTES         32

/*! 
 *  @brief NCP_TASK_MAX_RESOURCE_NAME_LEN :   Constant equal to the 
 * the maximum length of a string use to hold the name of a Task 
 * I/O resource,   such as a thread queue set name or a queue name.
 * Note that Task I/O resourcre names are C strings,  and thus one
 * character is reserved for the null terminator.   This limits the
 * useable text length of the name to 95 characters.
*/
#define NCP_TASK_MAX_RESOURCE_NAME_LEN     96

/*!
 * @brief NCP Task IO Receive buffer:   Tasks received using the ncp_task_recv() API function are presented to  
 *        the application in a buffer containing a data structure of this type.
*/
typedef struct ncp_task_recv_buf_s 
{
#ifdef NCP_BIG_ENDIAN
            ncp_uint32_t            dataOffset;             /*!< Word 0: offset of received task data           */
            unsigned                reserved3       :14;    /*!< Word 1: reserved                               */
            unsigned                launchId        :18;    /*!< The ID of the lauching engine                  */
            unsigned                traceEn         :1;     /*!< Word 2: debug bit to enable task tracing       */
            unsigned                taskPrio        :3;     /*!< The priority of this task                      */
            unsigned                TOID            :12;    /*!< The task order ID associated with this task    */ 
            unsigned                dataSz          :16;    /*!< The number of bytes of data in the received task */ 
            unsigned                QID             :8;     /*!< Word 3: The ID of the NCA Queue this task was sent to */
            unsigned                templateId      :8;     /*!< The template ID associated with this task      */
            unsigned                taskErr         :1;     /*!< Task Error Status - general                    */
            unsigned                bufferSizeErr   :1;     /*!< Task Buffer Error Status - failure due to buffer error */
            unsigned                bufferSize      :2;     /*!< The logical buffer size indicator 00..11 for sizes 0..3 */
            unsigned                debugFieldV     :2;     /*!< 00-None, 01-Debug For trace, 10-Debug For Performance, 11-reserved */
            unsigned                destId_9_0      :10;    /*!< The task destination instance ID, bits 0..9 */
            ncp_uint8_t             parms[NCP_TASK_PARAM_SIZE_BYTES]; /*< Word 4..11: Task parameters */
#else
            ncp_uint32_t            dataOffset;             /*!< Word 0: virtual address of received task data  */
            unsigned                launchId        :18;    /*!< Word 1: The ID of the lauching engine          */
            unsigned                reserved        :14;    /*!< reserved                                       */
            unsigned                dataSz          :16;    /*!< Word 2: The number of bytes of data in the received task */ 
            unsigned                TOID            :12;    /*!< The task order ID associated with this task    */ 
            unsigned                taskPrio        :3;     /*!< The priority of this task                      */                   
            unsigned                traceEn         :1;     /*!< debug bit to enable task tracing               */
            unsigned                destId_9_0      :10;    /*!< Word 3:The task destination instance ID, bits 0..9      */
            unsigned                debugFieldV     :2;     /*!< 00-None, 01-Debug For trace, 10-Debug For Performance, 11-reserved */
            unsigned                bufferSize      :2;     /*!< The logical buffer size indicator 00..11 for sizes 0..3 */
            unsigned                bufferSizeErr   :1;     /*!< Task Buffer Error Status - failure due to buffer error */
            unsigned                taskErr         :1;     /*!< Task Error Status - general                    */
            unsigned                templateId      :8;     /*!< The template ID associated with this task      */
            unsigned                QID             :8;     /*!< The ID of the NCA Queue this task was sent to  */                                                 
            ncp_uint8_t             parms[NCP_TASK_PARAM_SIZE_BYTES]; /*< Word 4..11: Task parameters */
#endif
} ncp_task_recv_buf_t;

/*!
 * @brief NCP Task Send Meta Data:   populated by the application and supplied to the ncp_task_send()
 *                                   or ncp_task_send_segments() APIs when transmitting a task.
 *
*/
typedef struct ncp_task_send_meta_s
{
#ifdef NCP_BIG_ENDIAN    
    unsigned    reserved0           :8;     /*!< Word 0: reserved   */    
    unsigned    flowId              :24;    /*!< The FLOWID associated with this task transmission */
    unsigned    reserved1           :1;     /*!< Word 1: reserved   */
    unsigned    reserved2           :1;     /*!< reserved           */
    unsigned    priority            :3;     /*!< The priority associated with this task */
    unsigned    reserved3           :2;     /*!< reserved           */
    unsigned    debugFieldV         :1;     /*!< debug/trace enabled */   
    unsigned    debugData           :24;    /*!< 3 bytes of debug data, valid if debugFieldV above is 01 or 10 */
    unsigned    dataSize            :16;    /*!< Word 2: size in bytes of task payload */
    unsigned    reserved4           :4;     /*!< reserved           */
    unsigned    reserved5           :1;     /*!< reserved           */
    unsigned    reserved6           :5;     /*!< reserved           */    
    unsigned    reserved7           :6;     /*!< reserved           */
    unsigned    reserved8           :32;    /*!< Word 3: reserved   */        
    ncp_uint8_t taskParms[NCP_TASK_PARAM_SIZE_BYTES];  /*!< Word 4...11: The task parameters associated with this task */
    ncp_uint32_t reserved9_12       [4];    /*!< Word 12-15: reserved */
#else
    unsigned    flowId              :24;    /*!< Word 0: The FLOWID associated with this task transmission */
    unsigned    reserved0           :8;     /*!< reserved           */
    unsigned    debugData           :24;    /*!< 3 bytes of debug data, valid if debugFieldV below is 01 or 10 */
    unsigned    debugFieldV         :1;     /*!< 00-No debug, 01-Debug field for tracing, 10-debug field for performance, 11-reserved */ 
    unsigned    reserved3           :2;     /*!< reserved           */
    unsigned    priority            :3;     /*!< The priority associated with this task */
    unsigned    reserved2           :1;     /*!< reserved           */          
    unsigned    reserved1           :1;     /*!< reserved           */
    unsigned    reserved7           :6;     /*!< Word 2: reserved   */
    unsigned    reserved6           :5;     /*!< reserved           */
    unsigned    reserved5           :1;     /*!< reserved           */
    unsigned    reserved4           :4;     /*!< reserved           */
    unsigned    dataSize            :16;    /*!< size in bytes of task payload */
    unsigned    reserved8           :32;    /*!< Word 3: reserved           */       
    ncp_uint8_t taskParms[NCP_TASK_PARAM_SIZE_BYTES]; /*!< Word 4...11: The task parameters associated with this task */
    ncp_uint32_t reserved9_12       [4];    /*!< Word 12-15: reserved */
#endif
} ncp_task_send_meta_t;

/*!
 * @brief NCP Task Send Gather-Mode DMA Descriptor Field:   populated by the application and supplied to the 
 *                                                          ncp_task_send_segments() APIs when transmitting non-contiguous task
 *                                                          using gather-mode DMA. The NCA supports gather-mode DMA of up to 16 
 *                                                          non-contiguous segments,   and the application allocates a table of
 *                                                          the desired number of descriptor fields such that there is one descriptor
 *                                                          field per segment to be transmitted.
*/
typedef struct ncp_task_segment_entry_s
{
   ncp_uint16_t   size;     /*!< The size in bytes of this gather mode segment */
   void           *addr;    /*!< The virtual address of this gather mode segment */
} ncp_task_segment_entry_t;


/*!
 * @brief Global statistics maintained by the Task I/O modules:   supplied to the ncp_task_get_stats() API to
 *        to retrieve the task statistics from the Task I/O module. 
 */
typedef struct ncp_task_stats_s
{
    /* Task Stats - SUCCESS */
    ncp_uint32_t stat_RxTaskDispatched;             /*!< The total number of tasks successfully received using dispatch receive mode */
    ncp_uint32_t stat_RxTaskDirect;                 /*!< The total number of tasks successfully received using direct receive mode */ 
    ncp_uint32_t stat_TxTask;                       /*!< The total number of tasks successfully transmitted */
    ncp_uint32_t stat_TxTaskSegments;               /*!< The total number of tasks successfully transmitted using gather-mode DMA */
    ncp_uint32_t stat_TxTaskComp;                   /*!< The total number of task completions   successfully transmitted */    
    /* Task Stats - FAILURE */    
    ncp_uint32_t stat_RxDroppedNoBind;              /*!< The total number of tasks received and discarded due to no active VP binding */
    ncp_uint32_t stat_RxDroppedTaskErr;             /*!< The total number of tasks received and discarded due to a generic task error */
    ncp_uint32_t stat_RxDroppedBufferSizeErr;       /*!< The total number of tasks received and discarded due to a buffer size error */
    
    /* Queue State Statistics */
    ncp_uint32_t stat_RxQueueEmpty;                 /*!< Number of times Rx Queue was empty - wait for irq */
    ncp_uint32_t stat_RxQueueNotEmpty;              /*!< Number of times Rx Queue was not empty */
    ncp_uint32_t stat_TxQueueFull;                  /*!< Number of times Tx Queue was full - wait for irq */
    ncp_uint32_t stat_TxQueueNotFull;               /*!< Number of times Tx Queue was not full */
    ncp_uint32_t stat_CompQueueFull;                /*!< Number of times Comp Queue was full - wait for irq */
    ncp_uint32_t stat_CompQueueNotFull;             /*!< Number of times Comp Queue was not full */    
    
    /* API Stats - SUCCESS  */
    ncp_uint32_t stat_api_task_hdl_create_ok;       /*!< The total number of successful API invocations */
    ncp_uint32_t stat_api_task_hdl_remove_ok;       /*!< The total number of successful API invocations */
    ncp_uint32_t stat_api_recv_queue_bind_ok;       /*!< The total number of successful API invocations */
    ncp_uint32_t stat_api_recv_queue_unbind_ok;     /*!< The total number of successful API invocations */
    ncp_uint32_t stat_api_recv_queue_vp_bind_ok;    /*!< The total number of successful API invocations */
    ncp_uint32_t stat_api_recv_queue_vp_unbind_ok;  /*!< The total number of successful API invocations */
    ncp_uint32_t stat_api_recv_ok;                  /*!< The total number of successful API invocations */
    ncp_uint32_t stat_api_recv_done_ok;             /*!< The total number of successful API invocations */
    ncp_uint32_t stat_api_send_ok;                  /*!< The total number of successful API invocations */
    ncp_uint32_t stat_api_send_segments_ok;         /*!< The total number of successful API invocations */
    ncp_uint32_t stat_api_task_buffer_alloc_ok;     /*!< The total number of successful API invocations */
    ncp_uint32_t stat_api_task_buffer_free_ok;      /*!< The total number of successful API invocations */
    ncp_uint32_t stat_api_send_mutex_disable_ok;    /*!< The total number of successful API invocations */
    /* API Stats - FAILURE  */    
    ncp_uint32_t stat_api_task_hdl_create_err;      /*!< The total number of API invocations that failed due to error(s) */
    ncp_uint32_t stat_api_task_hdl_remove_err;      /*!< The total number of API invocations that failed due to error(s) */
    ncp_uint32_t stat_api_recv_queue_bind_err;      /*!< The total number of API invocations that failed due to error(s) */
    ncp_uint32_t stat_api_recv_queue_unbind_err;    /*!< The total number of API invocations that failed due to error(s) */
    ncp_uint32_t stat_api_recv_queue_vp_bind_err;   /*!< The total number of API invocations that failed due to error(s) */
    ncp_uint32_t stat_api_recv_queue_vp_unbind_err; /*!< The total number of API invocations that failed due to error(s) */
    ncp_uint32_t stat_api_recv_err;                 /*!< The total number of API invocations that failed due to error(s) */
    ncp_uint32_t stat_api_recv_done_err;            /*!< The total number of API invocations that failed due to error(s) */
    ncp_uint32_t stat_api_send_err;                 /*!< The total number of API invocations that failed due to error(s) */
    ncp_uint32_t stat_api_send_segments_err;        /*!< The total number of API invocations that failed due to error(s) */
    ncp_uint32_t stat_api_task_buffer_alloc_err;    /*!< The total number of API invocations that failed due to error(s) */
    ncp_uint32_t stat_api_task_buffer_free_err;     /*!< The total number of API invocations that failed due to error(s) */
    ncp_uint32_t stat_api_send_mutex_disable_err;   /*!< The total number of API invocations that failed due to error(s) */
    /* User Mode Buffer Pool Statistics */
    ncp_uint32_t stat_upool_sz0_buffers_total;      /*!< The total number of size0 buffers in user mode pool */
    ncp_uint32_t stat_upool_sz1_buffers_total;      /*!< The total number of size1 buffers in user mode pool */
    ncp_uint32_t stat_upool_sz2_buffers_total;      /*!< The total number of size2 buffers in user mode pool */
    ncp_uint32_t stat_upool_sz3_buffers_total;      /*!< The total number of size3 buffers in user mode pool */    
    ncp_uint32_t stat_upool_sz0_buffers_free;       /*!< The current number of free size0 buffers in user mode pool */
    ncp_uint32_t stat_upool_sz1_buffers_free;       /*!< The current number of free size1 buffers in user mode pool */
    ncp_uint32_t stat_upool_sz2_buffers_free;       /*!< The current number of free size2 buffers in user mode pool */
    ncp_uint32_t stat_upool_sz3_buffers_free;       /*!< The current number of free size3 buffers in user mode pool */ 
    ncp_uint32_t stat_upool_sz0_buffers_low_water;  /*!< The lowest number of free size0 buffers in user mode pool */
    ncp_uint32_t stat_upool_sz1_buffers_low_water;  /*!< The lowest number of free size1 buffers in user mode pool */
    ncp_uint32_t stat_upool_sz2_buffers_low_water;  /*!< The lowest number of free size2 buffers in user mode pool */
    ncp_uint32_t stat_upool_sz3_buffers_low_water;  /*!< The lowest number of free size3 buffers in user mode pool */     
    /* Kernel Mode Buffer Pool Statistics */
    ncp_uint32_t stat_kpool_sz0_buffers_total;      /*!< The total number of size0 buffers in kernel mode pool */
    ncp_uint32_t stat_kpool_sz1_buffers_total;      /*!< The total number of size1 buffers in kernel mode pool */
    ncp_uint32_t stat_kpool_sz2_buffers_total;      /*!< The total number of size2 buffers in kernel mode pool */
    ncp_uint32_t stat_kpool_sz3_buffers_total;      /*!< The total number of size3 buffers in kernel mode pool */    
    ncp_uint32_t stat_kpool_sz0_buffers_free;       /*!< The current number of free size0 buffers in kernel mode pool */
    ncp_uint32_t stat_kpool_sz1_buffers_free;       /*!< The current number of free size1 buffers in kernel mode pool */
    ncp_uint32_t stat_kpool_sz2_buffers_free;       /*!< The current number of free size2 buffers in kernel mode pool */
    ncp_uint32_t stat_kpool_sz3_buffers_free;       /*!< The current number of free size3 buffers in kernel mode pool */ 
    ncp_uint32_t stat_kpool_sz0_buffers_low_water;  /*!< The lowest number of free size0 buffers in kernel mode pool */
    ncp_uint32_t stat_kpool_sz1_buffers_low_water;  /*!< The lowest number of free size1 buffers in kernel mode pool */
    ncp_uint32_t stat_kpool_sz2_buffers_low_water;  /*!< The lowest number of free size2 buffers in kernel mode pool */
    ncp_uint32_t stat_kpool_sz3_buffers_low_water;  /*!< The lowest number of free size3 buffers in kernel mode pool */                  
} NCP_COMPAT_PACKED ncp_task_stats_t;


/*!
 * @brief ncp_ncaV2_free_pdu_segments_t : Data structure supplied to supplied to the ncp_task_ncav2_free_pdu_segments API.
 * Application must set ptrCnt,   and pduSegAddr0..pduSegAddr<ptrCnt-1>.   PtrCnt must be in the range of 1..6 .
 */


typedef struct ncp_ncaV2_free_pdu_segments_s
{
#ifdef NCP_BIG_ENDIAN     
    unsigned reserved0          :3;    /* Word 0 - 3b100 */
    unsigned reserved1          :1;          
    unsigned reserved2          :28;  
        
    unsigned reserved3          :2;    /* Word 1 */
    unsigned reserved4          :2;
    unsigned reserved5          :2;
    unsigned reserved6          :2;
    unsigned reserved7          :2;
    unsigned reserved8          :2; 
    unsigned reserved9          :9;           
    unsigned ptrCnt             :3;
    unsigned reserved10         :2;
    unsigned reserved11         :6;    /* hidden - poolID */    
            
    ncp_uint64_t pduSegAddr0       ;     /* Word 2-3 */  
    ncp_uint64_t pduSegAddr1       ;     /* Word 4-5 */ 
    ncp_uint64_t pduSegAddr2       ;     /* Word 6-7 */ 
    ncp_uint64_t pduSegAddr3       ;     /* Word 8-9 */ 
    ncp_uint64_t pduSegAddr4       ;     /* Word 10-11 */ 
    ncp_uint64_t pduSegAddr5       ;     /* Word 12-13 */                     
    ncp_uint32_t pad[2]            ;     /* Words 14..15 */ 
#else
    unsigned reserved2          :28;     /* Word 0 - 3b100 */
    unsigned reserved1          :1; 
    unsigned reserved0          :3;   

    unsigned reserved11         :6;     /* Word 1 */ /* hidden - poolID */ 
    unsigned reserved10         :2; 
    unsigned ptrCnt             :3; 
    unsigned reserved9          :9;
    unsigned reserved8          :2;         
    unsigned reserved7          :2;        
    unsigned reserved6          :2;     
    unsigned reserved5          :2;        
    unsigned reserved4          :2;           
    unsigned reserved3          :2;    
   
            
    ncp_uint64_t pduSegAddr0       ;     /* Word 2-3 */  
    ncp_uint64_t pduSegAddr1       ;     /* Word 4-5 */ 
    ncp_uint64_t pduSegAddr2       ;     /* Word 6-7 */ 
    ncp_uint64_t pduSegAddr3       ;     /* Word 8-9 */ 
    ncp_uint64_t pduSegAddr4       ;     /* Word 10-11 */ 
    ncp_uint64_t pduSegAddr5       ;     /* Word 12-13 */                     
    ncp_uint32_t pad[2]            ;     /* Words 14..15 */ 
#endif           
} ncp_ncaV2_free_pdu_segments_t;

/*
 * Matches ncaV2 input task header
 */
 
 /*!
 * @brief ncp_task_ncaV2_recv_buf_t : NCP Task IO NcaV2 Receive buffer header:   Tasks received using the ncp_task_ncav2_recv() API function are presented to  
 *        the application in a buffer containing a data structure of this type.  
*/

typedef struct ncp_task_ncaV2_recv_buf_s 
{
#ifdef NCP_BIG_ENDIAN
    unsigned templateID         :8;     /* Word 0 */
    unsigned QID                :8;        
    unsigned pduSize            :16;   
         
    unsigned reserved0          :6;     /* Word 1 */
    unsigned dstID_9_0          :10; 
    unsigned reserved1          :1; 
    unsigned priority           :3;                  
    unsigned TOID               :12; 
        
    unsigned char params[NCP_TASK_PARAM_SIZE_BYTES];           /* Words 2..9 */
    
    unsigned pduBlockSz0        :2;     /* Word 10 */
    unsigned pduBlockSz1        :2;
    unsigned pduBlockSz2        :2;
    unsigned pduBlockSz3        :2;
    unsigned pduBlockSz4        :2;
    unsigned pduBlockSz5        :2;                        
    unsigned reserved2          :2;     
    unsigned debug              :2;         
    unsigned reserved3          :5;
    unsigned ptrCnt             :3;
    unsigned reserved4          :2;    
    unsigned poolID             :6;
        
    unsigned pduSegSize0        :16;     /* Word 11 */
    unsigned pduSegSize1        :16;   
        
    ncp_uint64_t pduSegAddr0       ;     /* Word 12-13 */
    
    ncp_uint64_t pduSegAddr1       ;     /* Word 14-15 */
    
    unsigned pduSegSize2        :16;     /* Word 16 */
    unsigned pduSegSize3        :16; 
          
    unsigned pduSegSize4        :16;     /* Word 17 */
    unsigned pduSegSize5        :16;
           
    ncp_uint64_t pduSegAddr2       ;     /* Word 18-19 */
    
    ncp_uint64_t pduSegAddr3       ;     /* Word 20-21 */
    
    ncp_uint64_t pduSegAddr4       ;     /* Word 22-23 */
    
    ncp_uint64_t pduSegAddr5       ;     /* Word 24-25 */
    
    unsigned debugDataWord0     :32;     /* Word 26 */ 
          
    unsigned debugDataWord1     :32;     /* Word 27 */   
#else
    unsigned pduSize            :16;     /* Word 0 */
    unsigned QID                :8;
    unsigned templateID         :8;
         
    unsigned TOID               :12;     /* Word 1 */ 
    unsigned priority           :3;    
    unsigned reserved1          :1;
    unsigned dstID_9_0          :10;
    unsigned reserved0          :6;
        
    unsigned char params[NCP_TASK_PARAM_SIZE_BYTES];           /* Words 2..9 */
    
    unsigned poolID             :6;     /* Word 10 */
    unsigned reserved4          :2;        
    unsigned ptrCnt             :3;
    unsigned reserved3          :5;    
    unsigned debug              :2;
    unsigned reserved2          :2;
    unsigned pduBlockSz5        :2;    
    unsigned pduBlockSz4        :2;    
    unsigned pduBlockSz3        :2;
    unsigned pduBlockSz2        :2;        
    unsigned pduBlockSz1        :2;
    unsigned pduBlockSz0        :2;    
        
    unsigned pduSegSize1        :16;     /* Word 11 */
    unsigned pduSegSize0        :16;     
        
    ncp_uint64_t pduSegAddr0       ;     /* Word 12-13 */
    
    ncp_uint64_t pduSegAddr1       ;     /* Word 14-15 */
    
    unsigned pduSegSize3        :16;     /* Word 16 */
    unsigned pduSegSize2        :16;    
          
    unsigned pduSegSize5        :16;     /* Word 17 */    
    unsigned pduSegSize4        :16;     
           
    ncp_uint64_t pduSegAddr2       ;     /* Word 18-19 */
    
    ncp_uint64_t pduSegAddr3       ;     /* Word 20-21 */
    
    ncp_uint64_t pduSegAddr4       ;     /* Word 22-23 */
    
    ncp_uint64_t pduSegAddr5       ;     /* Word 24-25 */
    
    unsigned debugDataWord0     :32;     /* Word 26 */ 
          
    unsigned debugDataWord1     :32;     /* Word 27 */   

#endif
} ncp_task_ncaV2_recv_buf_t; 

/*
 * Matches concatenated ncaV2 OPCQ entry & extension 
 */
 
/*!
 * @brief ncp_task_ncaV2_send_meta_t : NCP Task Send Meta Data:   populated by the application,  and supplied to the ncp_task_ncav2_send()
 *                                   API when transmitting a task.
 *
*/ 
typedef struct ncp_task_ncaV2_send_meta_s
{
#ifdef NCP_BIG_ENDIAN 
    unsigned reserved7           :3;     /* Word 0 - 3b001*/
    unsigned interruptOnComplete :1;
    unsigned setTaskErr          :1;       
    unsigned debugFieldV         :1;   
    unsigned reserved5           :1;
    unsigned reserved6           :1;        
    unsigned flowDataIndex       :24;  
        
    unsigned virtualFlowID       :8;    /* Word 1 */              
    unsigned debugData           :24;    
   
    unsigned char params[NCP_TASK_PARAM_SIZE_BYTES]       ;    /* Words 2..9 */

    unsigned pduBlockSz0        :2;     /* Word 10 */
    unsigned pduBlockSz1        :2;
    unsigned pduBlockSz2        :2;
    unsigned pduBlockSz3        :2;
    unsigned pduBlockSz4        :2;
    unsigned pduBlockSz5        :2;                        
    unsigned reserved2          :1;     
    unsigned priority           :3;         
    unsigned reserved3          :5;
    unsigned ptrCnt             :3;
    unsigned reserved4          :2;    
    unsigned poolID             :6;
               
    unsigned pduSegSize0        :16;    /* Word 11 */
    unsigned pduSegSize1        :16;     
                           
    ncp_uint64_t pduSegAddr0       ;    /* Word 12-13 */
    
    ncp_uint64_t pduSegAddr1       ;    /* Word 14-15 */
    
    /* ----------------------- */
    
    unsigned reserved8          :3;    /* Word 0 - 3b010 */
    unsigned reserved0          :29;  
    
    unsigned reserved1          :32;    /* Word 1 */      
        
    unsigned pduSegSize2        :16;     /* Word 2 */
    unsigned pduSegSize3        :16; 
          
    unsigned pduSegSize4        :16;     /* Word 3 */
    unsigned pduSegSize5        :16; 
          
    ncp_uint64_t pduSegAddr2       ;     /* Word 4-5 */
    
    ncp_uint64_t pduSegAddr3       ;     /* Word 6-7 */
    
    ncp_uint64_t pduSegAddr4       ;     /* Word 8-9 */
    
    ncp_uint64_t pduSegAddr5       ;     /* Word 10-11 */

    ncp_uint32_t    pad[4]         ;     /* Words 12-15 */
    
#else    

    unsigned flowDataIndex       :24;   /* Word 0 - 3b001*/
    unsigned reserved6           :1;     
    unsigned reserved5           :1;
    unsigned debugFieldV         :1;        
    unsigned setTaskErr          :1;        
    unsigned interruptOnComplete :1;        
    unsigned reserved7           :3;
        
        
    unsigned debugData           :24;   /* Word 1 */         
    unsigned virtualFlowID       :8;               
   
    unsigned char params[NCP_TASK_PARAM_SIZE_BYTES]       ;    /* Words 2..9 */

    unsigned poolID             :6;     /* Word 10 */
    unsigned reserved4          :2;
    unsigned ptrCnt             :3;
    unsigned reserved3          :5;        
    unsigned priority           :3;        
    unsigned reserved2          :1;        
    unsigned pduBlockSz5        :2;
    unsigned pduBlockSz4        :2;        
    unsigned pduBlockSz3        :2;        
    unsigned pduBlockSz2        :2;        
    unsigned pduBlockSz1        :2;                
    unsigned pduBlockSz0        :2;    
        
         
    unsigned pduSegSize1        :16;    /* Word 11 */
    unsigned pduSegSize0        :16;    
     
                           
    ncp_uint64_t pduSegAddr0       ;    /* Word 12-13 */
    
    ncp_uint64_t pduSegAddr1       ;    /* Word 14-15 */
    
    /* ----------------------- */        
    
    unsigned reserved0          :29;    /* Word 0 - 3b010 */
    unsigned reserved8          :3;    
    
    unsigned reserved1          :32;    /* Word 1 */      

    unsigned pduSegSize3        :16;    /* Word 2 */     
    unsigned pduSegSize2        :16;    
 
    unsigned pduSegSize5        :16;    /* Word 3 */        
    unsigned pduSegSize4        :16;     
          
    ncp_uint64_t pduSegAddr2       ;     /* Word 4-5 */
    
    ncp_uint64_t pduSegAddr3       ;     /* Word 6-7 */
    
    ncp_uint64_t pduSegAddr4       ;     /* Word 8-9 */
    
    ncp_uint64_t pduSegAddr5       ;     /* Word 10-11 */

    ncp_uint32_t    pad[4]         ;     /* Words 12-15 */
        
#endif
    
} ncp_task_ncaV2_send_meta_t;    

typedef enum {
    NCP_TASK_TQS_MODE_USER = 0,
    NCP_TASK_TQS_MODE_KERNEL 
} ncp_task_tqs_mode_t;
    
/*! 
 *  @brief ncp_nca_task_block_sizes_t: An enum for the four memory block sizes.
 *          TASK_BLOCK_SZ_UNKNOWN is used when the block size is unknown, such
 *          as when the block is acquired from an *_alloc() call.
*/
typedef enum {
    TASK_BLOCK_SZ0 = 0,    /*!< Block size 0 */
    TASK_BLOCK_SZ1,        /*!< Block size 1 */
    TASK_BLOCK_SZ2,        /*!< Block size 2 */
    TASK_BLOCK_SZ3,        /*!< Block size 3 */
    TASK_BLOCK_SZ_UNKNOWN, /*!< Unknown block size */
} ncp_nca_task_block_sizes_t;

/*! 
 *  @brief ncp_task_pool_type_t: an enum for the two pool types that a task
 *          may use.
*/
typedef enum {
    MME_MANAGED_SHARED_POOL, /*!< MME-managed pool */
    CPU_MANAGED_POOL,        /*!< CPU-managed pool */
} ncp_task_pool_type_t;

/*! 
 *  @brief core_location_t: an enum for the location (and if external, the bus 
 *          type) of the CPU.
*/
typedef enum {
    INTERNAL_CPU=0,         /*!< Internal CPU */
    EXTERNAL_SRIO,          /*!< External CPU, SRIO-connected */
    EXTERNAL_PCIe0,         /*!< External CPU, PCIe0-connected */
    EXTERNAL_PCIe1,         /*!< External CPU, PCIe1-connected */
    EXTERNAL_PCIe2,         /*!< External CPU, PCIe2-connected */
} core_location_t;

/*! 
 *  @brief ncp_task_completion_mode_t: an enum for the completion mode setting
 *      for ordered queues.
 */
typedef enum
{
    NCP_TASK_COMPLETION_HW_AUTOMATIC=0,
    NCP_TASK_COMPLETION_MANUAL
} ncp_task_completion_mode_t;    

/*!
 *  @brief ncp_task_tbr_hash_fn_ptr_t: a function signature for TBR
 *      hash functions.
 */
typedef ncp_uint32_t (*ncp_task_tbr_hash_fn_ptr_t)(
    ncp_task_hdl_t taskHdl,
    void *taskBufferAddr,
    ncp_uint8_t poolBlockIndex);

/*!
 *  @brief ncp_task_tbr_desc_t: a struct for user customization of TBR hashing.
 */
typedef struct {
    ncp_task_tbr_hash_fn_ptr_t hashFuncPtrs[4];
    ncp_uint32_t           numHashBuckets[4];
} ncp_task_tbr_desc_t;




/* ============================================================================================================
 * BEGIN Common APIs.   These APIs are common across both NCA V1 and NCA V2 hardware.
 * ============================================================================================================
 */
 
/*!
 * @fn ncp_st_t
 *     ncp_task_get_taskHdl(void **pTaskHdl);
 *
 * @brief This API creates returns the thread-local task handle if one has been previously created in this
 *        thread context.   If sw executing in the current thread context has not already created a task handle,   then
 *        this API will return an error.   This API accesses thread local storage (TLS),   and therefore has an
 *        associated performance penalty.   It is reecommended that callers cache the returned handle for later use,
 *        rather than invoke this API repeatedly at runtime.
 *
 * 
 * @param[in,out]   pTaskHdl: On success, the task handle is returned here.
 *
 * @retval NCP_ST_TASK_INVALID_TASK_HANDLE A valid task handle associated with this thread could be found.
*/	 

NCP_API ncp_st_t
ncp_task_get_taskHdl(void **pTaskHdl);


/*!
 * @fn ncp_st_t ncp_task_hdl_create(ncp_hdl_t ncpHdl,
 *                                  ncp_uint8_t     threadQueueSetId,
 *                                  ncp_bool_t      shared,
 *                                  ncp_bool_t      orderedTaskCompletion,
 *                                  ncp_task_hdl_t  *taskHdl);
 *
 * @brief This API creates a thread-local task handle,   and must be the first Task I/O API issued by the application thread.
 *        The handle returned is used in all subsequent calls to Task I/O APIs. 
 *        Task handles are thread-local,   and must not be shared among other threads in a process.   
 *        Requiring task handles to be thread-local greatly improves performance since serial access is guaranteed;   thus, eliminating 
 *        the need for a mutex.

 * @param[in]       ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in]       threadQueueSetId: The linear ID (0..11) of the Thread Queue Set
 * @param[in]       shared: if TRUE,   then the output type queues in the Thread Queue Set are shared,   
 *                  otherwise they are reserved for exclusive use.   Note that input queues can never be shared.
 * @param[in]       orderedTaskCompletion: If TRUE,   then TaskIO module will perform output related maintenance operations
 *                  on the task completion PCQ,   otherwise no maintenance operations will be performed.
 * @param[in,out]   taskHdl: On success, the task handle is returned here.
 *
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down dur to config_destroy 
 * @retval NCP_ST_TASK_NO_MALLOC_MEM insufficient memory resources to satisfy request
 * @retval NCP_ST_TASK_TQS_DISABLED the thread queue set is disabled
*/	
	
NCP_API ncp_st_t 
ncp_task_hdl_create(
    ncp_hdl_t       ncpHdl,
    ncp_uint8_t     threadQueueSetId,
    ncp_bool_t      shared,
    ncp_bool_t      orderedTaskCompletion,   
    ncp_task_hdl_t  *taskHdl);

/*!
 * @fn ncp_st_t ncp_task_hdl_remove(ncp_task_hdl_t taskHdl);
 * @brief This API removes the specified task handle from service. All resources associated with the specified task  
 *        handle are freed. Note that all associated pipelines and receive queues must be specifically unbound prior to 
 *        calling this function.   Failure to call this function prior to thread termination will result in a memory leak.
 *
 * @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
 *
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy  
 * @retval NCP_ST_TASK_INVALID_TASK_HANDLE The taskHdl parameter is not valid
 * @retval NCP_ST_HANDLE_IN_USE cannot remove taskHdl until queues and VPs unbound
 * @retval NCP_ST_TASK_QUESET_NOT_IN_LOCAL_DOMAIN The Thread Queue Set ID supplied references a queueset owned by another AMP domain.
 * @retval NCP_ST_TASK_TBR_BUFFERS_OWNED_DURING_REMOVE This TBR-enabled task
 *          handle owned task buffers when ncp_task_hdl_remove() was called.
 *          This is status is meant to inform the developer that their 
 *          application is leaking buffers; it is not an error. The task handle
 *          is successfully removed, despite the buffer leak.
*/
NCP_API ncp_st_t 
ncp_task_hdl_remove(
    ncp_task_hdl_t  taskHdl);
	
/*!
 * @fn ncp_st_t ncp_task_send_mutex_disable( ncp_task_hdl_t taskHdl)
 * @brief This API can be used to disable mutex operations associated with sharing a queueset.
 * See the RTE user's guide for the specific scenario where this function can be used.  If used incorrectly,
 * corruption will be almost certain,   so care must be taken.
 *
 * @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
 *
 * @retval NCP_ST_TASK_INVALID_PARAMETER The taskHdl parameter is NULL
 *
*/
NCP_API ncp_st_t
ncp_task_send_mutex_disable(
    ncp_task_hdl_t taskHdl);

/*!
 * @fn ncp_st_t ncp_task_recv_queue_bind(	ncp_task_hdl_t taskHdl,
 *                                      	ncp_uint8_t ncaQueueId,
 *                                      	ncp_uint8_t weight,
 *                                      	ncp_bool_t shared,
 *                               	ncp_bool_t fixedRecvQueueId,
 *                                      	ncp_uint8_t *recvQueueId)
 *
 * @brief   This API binds the specified task handle to the specified NCA task input queue. Upon success a receive queue ID is 
 *          returned that can be used in later ncp_task_recv_queue_vp_bind calls to specify the various pipelines that terminate at this
 *          particular receive queue. 
 *          
 *          An exclusive binding (shared = FALSE) allows a single process to bind directly to an NCA task input queue,   and access that
 *          queue in a lockless manner.   This type of binding provides maximum efficiency.
 *
 *          Multiple receive queue bindings can be created by calling the ncp_task_recv_queue_bind function multiple times with a unique 
 *          ncaReceiveQueueId specified in each call. When a receive handle contains multiple receive queue bindings,  the ncp_task_recv 
 *          function services each queue using a weighted round robin (WRR) scheduling arbitration policy.
 *          Receive queue bindings can be created and removed dynamically throughout the life of the system.
 *
 *          Note that if a shared binding is requested,   a lock will be used to serialize access to the physical NCA queue,   
 *          and that the use of a lock has an associated performance penalty.   When sharing receive queues,   all participating threads
 *          should have requested identical VP bindings.   As traffic is dequeued from the input queue,  it is given to the next caller of
 *          ncp_task_recv,   and if the VP associated with the received task does not have an active binding for that task handle   
 *          the task will be silently discarded by the RTE.   
 *
 *          If dispatch mode is enabled,   and the receive queue is shared,   then all threads sharing the receive queue must also
 *          share the same address space (e.g. a multi threaded process).   Otherwise it would be possible for the RTE to invoke a dispatch
 *          callback for a function address that is not vallid in the current ncp_task_recv context.
 *
 *
 * @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
 * @param[in] ncaQueueId: Specifies the NCA task input queue association for this receive queue.
 * @param[in] weight: Specifies the WRR scheduling arbitration weight to use for this receive queue.
 * @param[in] shared: Set to FALSE for exclusive use,   or TRUE for shared use.   
 * @param[in] fixedRecvQueueId:  If set to TRUE, to use the receive queue ID pointed to by recvQueueId. If set to FALSE,  
 *                           dynamically allocate the receive queue ID and return it in the location pointed to by recvQueueId. Note that 
 *                           the 8-bit receive queue ID space is partitioned into two equal ranges. The 0-127 range is reserved for 
 *                           dynamically allocated IDs and the 128-255 range is reserved for fixed (user managed) IDs. For additional 
 *                           information see ncp_task_recv_queue_vp_bind.
 * @param[in,out] recvQueueId: Pointer to the receive queue ID. On success, the unique ID associated with this receive queue is stored in 
 *                this location.
 *
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy  
 * @retval NCP_ST_TASK_INVALID_TASK_HANDLE The taskHdl parameter is not valid
 * @retval NCP_ST_TASK_SHARED_RECEIVE_QUEUES_NOT_SUPPORTED Shared binding to receive queues is no longer supported
 * @retval NCP_ST_TASK_NO_MALLOC_MEM    A request for memory allocation could not be satisfied due to insufficient resources.
 * @retval NCP_ST_TASK_NULL_RECVQUEUEID_PTR the recvQueueId pointer is NULL
 * @retval NCP_ST_TASK_INVALID_NCA_INPUT_QUEUE queue ID exceeds upper limit
 * @retval NCP_ST_TASK_INVALID_FIXED_QUEUEID fixed queue IDs must be in the rang 128..255 
 * @retval NCP_ST_TASK_QMAP_ERR_TOO_BIG queue ID exceeds the upper limit 
 * @retval NCP_ST_TASK_NULL_PCQ_PRODUCER_PTR internal error
 * @retval NCP_ST_TASK_NULL_PCQ_CONSUMER_PTR  internal error
 * @retval NCP_ST_TASK_EXCLUSIVE_BINDING_NOT_AVAIL resource to bind is already in use
 * @retval NCP_ST_TASK_RECEIVE_QUEUES_MUST_HAVE_SAME_SHARE_PERMISSION All receive queues used by a thread must have same share permission, either all exclusive,  or all shared.
 * @retval NCP_ST_TASK_RECV_ACCESS_MODE_NOT_SAME_AS_QUEUESET If the ncp_task_hdl_create API was used to open a queueset in exclusive mode, all assoiated receive queues must be bound in exclusive mode too.
 * @retval NCP_ST_TASK_NULL_RECV_QUEUE_PTR invalid receive queue pointer encountered
 * @retval NCP_ST_TASK_NULL_TASK_QUEUE_PTR invalid task queue pointer encountered
 * @retval NCP_ST_TASK_QUEUESET_NOT_SHARED Shared binding to the receive queue
 *          attempted for a non-shared thread queue set
*/

NCP_API ncp_st_t
ncp_task_recv_queue_bind(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t ncaQueueId,
	ncp_uint8_t weight,
	ncp_bool_t shared,
	ncp_bool_t fixedRecvQueueId,
	ncp_uint8_t *recvQueueId);

/*!
 * @fn ncp_st_t ncp_task_recv_queue_unbind(ncp_task_hdl_t taskHdl,	
 *                                         ncp_uint8_t recvQueueId);
 * @brief This API removes the specified receive queue binding from service. All resources associated with the receive 
 *        queue itself are freed. Note that all VP bindings associated with this receive queue binding must be removed prior 
 *        to calling this function.
 *
 * @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
 * @param[in] recvQueueId:  Receive queue ID returned from previous call to ncp_task_recv_queue_bind.
 *
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy  
 * @retval NCP_ST_TASK_INVALID_TASK_HANDLE  The taskHdl parameter is not valid 
 * @NCP_ST_TASK_RECEIVE_HANDLE_HEAD_NULL No receive queues are currently bound for this task handle
 * @retval NCP_ST_TASK_INVALID_RECEIVE_QUEUE receive queue ID is not currently bound
 * @retval NCP_ST_TASK_RECEIVE_QUEUE_NOT_FOUND The specified receive queue was not found in the list of receive queues associated with this task handle.
 */
 
NCP_API ncp_st_t
ncp_task_recv_queue_unbind(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t recvQueueId);


/*!
 * @brief NCP Task IO Receive Dispatch Callback:
 *       describes the function that is called when the ncp_task_receive() API is called and  
 *       the virtual pipeline associated with the current received task was bound by calling the ncp_task_recv_queue_vp_bind() API with a 
 *       non NULL  recvFunc parameter.
*/
typedef ncp_st_t (*ncp_task_recv_fn_t)(
	ncp_uint8_t recvQueueId,        /*!< The receive queue ID associated with this task,  as returned in the ncp_task_recv_queue_bind API */
	ncp_vp_hdl_t vpHdl,             /*!< The VP (virtual pipeline) handle associated with the received task */
	ncp_uint8_t engineSequenceId,	/* The engine sequeunce ID associated with the received task */
	void *recvFuncArg,              /* The argument provided by the application to the ncp_task_recv_queue_vp_bind() API for this VP bind */
	void *task,                     /* Virtual address of task is returned here. 
	                                 * Note: legacy ncp_task_recv API returns ncaV1 header,  otherwise ncaV2 
	                                 */
	void                *taskData); /* Virtual address of task Data is returned here        */


/*!
 *  @fn ncp_st_t ncp_task_recv_queue_vp_bind(ncp_task_hdl_t taskHdl,
 *	                                    ncp_uint8_t recvQueueId,
 *	                                    ncp_vp_hdl_t vpHdl,
 *	                                    ncp_uint8_t engineSequenceId,
 *	                                    ncp_bool_t shared,
 *	                                    ncp_task_recv_fn_t recvFunc,
 *	                                    void *recvFuncArg);
 * @brief   This API creates a binding between the specified receive queue and the specified virtual pipeline (VP). This is called a VP 
 *          level binding. Multiple VP level bindings can be created by calling this function multiple times with a unique {vpHdl, 
 *          engineSequenceId} pair specified in each call.
 *          Two types of VP level bindings are supported: shared and exclusive. An exclusive VP level binding allows a single process to 
 *          receive all tasks from the specified VP.   Shared VP bindings are not supported. This API is used to setup the per-VP "dispatch" function.
 *          If a task receive function is 
 *          specified (recvFunc != NULL) then tasks for this binding are dispatched to the specified function, within the context of the 
 *          ncp_task_recv caller. If a task receive function is not specified (recvFunc == NULL) then tasks for this binding are returned to 
 *          the ncp_task_recv caller.
 *          VP level bindings can be created and removed dynamically throughout the life of the system.
 *
 * @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
 * @param[in] recvQueueId: The receive queue ID returned by the API ncp_task_recv_queue_bind (dynamic queue), or the fixed queue ID supplied to the API ncp_task_recv_queue_bind.
 * @param[in] vpHdl: Virtual pipeline handle
 * @param[in] engineSequenceId: Engine Sequence (Formerly Pipeline) ID
 * @param[in] shared:  This parameter must be set to FALSE.   Sharing virtual pipelines is not supported.
 * @param[in] recvFunc:  Receive handler function pointer. If not null then incoming tasks will be delivered by receive dispatch mode.
 * @param[in] recvFuncArg: If a receive handler is not specified (recvFunc == NULL) then this argument is ignored.
 *
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy  
 * @retval NCP_ST_TASK_INVALID_TASK_HANDLE  The taskHdl parameter is not valid 
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
 * @retval NCP_ST_TASK_INVALID_RECEIVE_QUEUE  receive queue ID is not currently bound
 * @retval NCP_ST_TASK_NO_MEM_L1BIND  insufficient memory available to allocate bind table
 * @retval NCP_ST_TASK_EXCLUSIVE_BINDING_NOT_AVAIL resource to bind is already in use
 * @retval NCP_ST_TASK_SHARED_PIPELINES_NOT_SUPPORTED Shared bindings to Virtual Pipelines is no longer supported
 * @retval NCP_ST_VPM_INVALID_VP_HDL the vpHdl parameter is not valid
 * @retval NCP_ST_VPM_ENGINE_SEQUENCE_NOT_FOUND invalid engine sequence
 */
NCP_API ncp_st_t
ncp_task_recv_queue_vp_bind(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t recvQueueId,
	ncp_vp_hdl_t vpHdl,
	ncp_uint8_t engineSequenceId,
	ncp_bool_t shared,
	ncp_task_recv_fn_t recvFunc,
	void *recvFuncArg);	 

/*!
 * @fn ncp_st_t ncp_task_recv_queue_vp_unbind(ncp_task_hdl_t taskHdl,
 *                                      	ncp_uint8_t recvQueueId,
 *                                          ncp_vp_hdl_t vpHdl,
 *                                          ncp_uint8_t engineSequenceId);
 * @brief This API removes the specified VP binding from the specified receive queue. All resources associated with 
 *        the VP binding are freed.
 *
 * @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
 * @param[in] ncaQueueId: Specifies the NCA task input queue ID for this receive queue.
 * @param[in] vpHdl: Virtual pipeline handle
 * @param[in] engineSequenceId: (Formerly Pipeline) Engine Sequence ID
 *
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy  
 * @retval NCP_ST_TASK_INVALID_TASK_HANDLE  The taskHdl parameter is not valid
 * @retval NCP_ST_TASK_INVALID_RECEIVE_QUEUE receive queue ID is not currently bound
 * @retval NCP_ST_TASK_NULL_L1_BINDP  no binding exists
 * @retval NCP_ST_TASK_INVALID_VP_HANDLE  the vpHdl parameter is invalid
 * @retval NCP_ST_TASK_INVALID_BIND_TABLE_ENTRY internal error
 * @retval NCP_ST_VPM_INVALID_VP_HDL the vpHdl parameter is not valid
 * @retval NCP_ST_VPM_ENGINE_SEQUENCE_NOT_FOUND invalid engine sequence
 *
*/
NCP_API ncp_st_t
ncp_task_recv_queue_vp_unbind(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t recvQueueId,
	ncp_vp_hdl_t vpHdl,
	ncp_uint8_t engineSequenceId);

/*!
 * @fn ncp_st_t ncp_task_send_queue_flush(	
 *                                      ncp_task_hdl_t taskHdl,
 *                                      ncp_bool_t wait,
 *                                      ncp_bool_t *pQueueStatus);
 * @brief This API is called to test send/output queue for the empty condition.   If the wait parameter is set to true,  
 *         then the function will block until all previously queued output tasks have been processed by the NCA.
 *
 * @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
 * @param[in] wait: If FALSE,   then return current queue status in queueEmpty,  else wait for queue to drain
 * @param[in,out] pQueueEmpty: Pointer to boolean where queue status (0 if empty or,  1 if non-empty) is returned
 *
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_TASK_SHUTDOWN  Task I/O is shutting down due to config_destroy
*/
NCP_API  ncp_st_t
ncp_task_send_queue_flush(
	ncp_task_hdl_t taskHdl,
    ncp_bool_t wait,
    ncp_bool_t *pQueueEmpty);





/*!
 * @fn void ncp_task_reset_stats( ncp_hdl_t ncpHdl )
 * @brief This API is called to reset task statistics
 *
 * @param[in] ncpHdl:  NCP handle returned by previous call to ncp_config.  
 *
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 */
NCP_API ncp_st_t
ncp_task_reset_stats(	ncp_hdl_t ncpHdl );

/*!
 * @fn void ncp_task_get_stats( ncp_hdl_t ncpHdl, ncp_task_stats_t *pStats );
 * @brief This API is called to retrieve task statistics
 *
 * @param[in] ncpHdl:  NCP handle returned by previous call to ncp_config. 
 * @param[in,out]  pStats: pointer to ncp_task_stats_t structure to receive task statistics 
 *
 * @retval NCP_ST_TASK_NO_GSM  Task I/O Shared Memory Not Initialized
 */
NCP_API ncp_st_t
ncp_task_get_stats(	ncp_hdl_t ncpHdl,
                        ncp_task_stats_t *pStats);

/*!
 * @fn ncp_st_t ncp_nca_bp_dest_val_get(ncp_hdl_t ncpHdl, ncp_uint8_t destBit, 
 *                                      ncp_bool_t *destVal)
 * @brief For a given dest bit, this function returns the NCA backpressure state.
 *
 * @param[in]  ncpHdl:  NCP API state handle.
 * @param[in]  destBit: The bp dest bit that needs to be queried. 
 *                      Valid values: 0-31
 * @param[out] destVal: TRUE - if bp state is on for the given bit.
 *                      FALSE - if bp state is off for the given bit.
 */
NCP_API ncp_st_t 
ncp_nca_bp_dest_val_get(ncp_hdl_t ncpHdl, ncp_uint8_t destBit, 
                        ncp_bool_t *destVal);

/*!
 * @fn ncp_st_t ncp_nca_bp_state_get(ncp_hdl_t ncpHdl, ncp_uint32_t *bpState)
 *
 * @brief This API returns the NCA backpressure state.
 *
 * @param[in]  ncpHdl:  NCP API state handle.
 * @param[out] bpState: Buffer where the NCA backpressure state is written.
 */
NCP_API ncp_st_t
ncp_nca_bp_state_get(ncp_hdl_t ncpHdl, ncp_uint32_t *bpState);

/*!
 * @fn ncp_st_t ncp_task_recv_queue_select(
 *      ncp_task_hdl_t  taskHdl,
 *      ncp_uint32_t    numQueues,
 *      ncp_uint32_t   *queueIds,
 *      ncp_bool_t     *queueEmpty,
 *      ncp_bool_t      wait)
 *
 * @brief This function allows a thread to wait (similar to the POSIX select()
 *        function) on a set of receive queues until one or more queues have
 *        tasks available. The receive queues to be waited on must be bound to
 *        the caller's task handle. The queueIds argument specifies the NCA
 *        queue IDs of the queues to wait on, and the queueEmpty argument is an
 *        array of booleans that specifies whether a given queue is empty or
 *        non-empty. Note that this API is implemented without using a lock.
 *        This provides for fast execution, but may return spurious false
 *        "non-empty" status under certain situations where a race condition
 *        occurs, especially if the receive queue(s) is/are being shared.
 *
 *        The wait behavior is dictated by the task handle's wait profile for
 *        the NCP_TASK_API_CLASS_RECV_QUEUE_SELECT class.
 *
 * @param[in] taskHdl Task handle returned by previous call to
 *            ncp_task_hdl_create().
 * @param[in] numQueues The depth of the queueIds and queueEmpty arrays.
 * @param[in] queueIds  An array of NCA queue IDs.
 * @param[out] queueEmpty An array of booleans that indicate whether the 
 *              corresponding receive queue is empty or non-empty.
 * @param[in] wait Controls whether to wait (in the manner dictated by the
 *              task handle's wait profile) until at least one queue
 *              is non-empty or not. If wait is false and all queues are
 *              empty, the function will return NCP_ST_SUCCESS.
 *
 * @retval NCP_ST_INVALID_PARAMETER queueIds is NULL.
 * @retval NCP_ST_INVALID_PARAMETER queueEmpty is NULL.
 * @retval NCP_ST_TASK_INVALID_TASK_HANDLE  The taskHdl parameter is not valid.
 * @retval NCP_ST_TASK_TQS_DISABLED the thread queue set is disabled.
 * @retval NCP_ST_TASK_QUEUE_NOT_BOUND_TO_TASK_HANDLE One of the NCA queues
 *          referred to in queueIds is not bound to the task handle.
 * @retval NCP_ST_TASK_QMAP_ERR_TOO_BIG ncaQueueId exceeds the number of
 *          available hardware input queues.
 */
NCP_API ncp_st_t
ncp_task_recv_queue_select(
    ncp_task_hdl_t  taskHdl,
    ncp_uint32_t    numQueues,
    ncp_uint32_t   *queueIds,
    ncp_bool_t     *queueEmpty,
    ncp_bool_t      wait);


/*!
 * @fn ncp_st_t ncp_task_oPCQ_depth_get(
 *      ncp_task_hdl_t  taskHdl,
 *      ncp_uint16_t   *qDepth);
 *
 * @brief This function returns the depth of the oPCQ associated with
 *          taskHdl's thread queue set.
 *
 * @param[in] taskHdl: Task handle returned by previous call to
 *              ncp_task_hdl_create().
 * @param[out] qDepth: the depth of the oPCQ.
 *
 * @retval NCP_ST_INVALID_PARAMETER qDepth is NULL
 */

NCP_API ncp_st_t
ncp_task_oPCQ_depth_get(
    ncp_task_hdl_t  taskHdl,
    ncp_uint16_t   *qDepth);

/*!
 * @fn ncp_st_t ncp_task_recv_queue_flush(
 *      ncp_hdl_t      ncpHdl,
 *      ncp_task_hdl_t taskHdl,
 *      ncp_uint32_t   queueId);
 *
 * @brief This function removes tasks from the specified receive queue until
 *          it depletes both the NCA receive queue and the corresponding COW receive queue.
 *
 *        Note: this function may issue access the task handle's send
 *          queue to free tasks or to issue completion messages. The
 *          send queue's mutex must not be disabled if another thread
 *          is using it simultaneously.
 *
 * @param[in] ncpHdl:  NCP handle returned by previous call to ncp_config.
 * @param[in] taskHdl Task handle returned by previous call to
 *            ncp_task_hdl_create().
 * @param[in] queueId Specifies the NCA task input queue to flush.
 *
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid.
 * @retval NCP_ST_TASK_INVALID_TASK_HANDLE The taskHdl parameter is not valid
 * @retval NCP_ST_PLL_OPERATION_NOT_SUPPORTED Internal error.
 * @retval NCP_ST_TASK_QMAP_ERR_TOO_BIG ncaQueueId exceeds the number of
 *          hardware input queues.
 */

NCP_API ncp_st_t
ncp_task_recv_queue_flush(
    ncp_hdl_t      ncpHdl, 
    ncp_task_hdl_t taskHdl,
    ncp_uint32_t   queueId);


/* ============================================================================================================
 * BEGIN common raw API. These functions are common across both NCA V1 and NCA V2 hardware.
 * ============================================================================================================
 */

/*!
 * @fn ncp_st_t ncp_task_raw_recv_queue_bind(
 *      ncp_task_hdl_t           taskHdl,
 *      ncp_uint8_t              ncaQueueId,
 *      ncp_bool_t               shared,
 *      ncp_task_raw_recv_hdl_t *rxHdl);
 *
 * @brief This function binds the specified receive handle to the specified NCA
 *        task input queue. Upon success a raw receive handle is returned that
 *        can be used in later ncp_task_raw_recv calls to acquire available
 *        tasks from the input queue.
 *        Only one NCA receive queue can be bound to a receive handle, however
 *        shared bindings (multiple handles bound to the same queue) are
 *        supported.
 *        Receive queue bindings can be created and removed dynamically
 *        throughout the life of the system.
 *
 * @param[in] taskHdl Task handle returned by previous call to
 *            ncp_task_hdl_create().
 * @param[in] ncaQueueId Specifies the NCA task input queue association for
 *                        this receive queue.
 * @param[in] shared Specifies whether this receive queue will be shared by
 *                      more than one thread.
 * @param[out] rxHdl On success, the receive handle is stored in this location.
 *
 * @retval NCP_ST_INVALID_PARAMETER rxHdl is NULL.
 * @retval NCP_ST_NOT_IMPLEMENTED Called with a v1 NCA task handle 
 *          (not supported, yet).
 * @retval NCP_ST_TASK_QMAP_ERR_TOO_BIG ncaQueueId exceeds the number of
 *          available hardware input queues.
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy
 * @retval NCP_ST_TASK_INVALID_TASK_HANDLE The taskHdl parameter is not valid
 * @retval NCP_ST_TASK_QUEUESET_NOT_SHARED Shared binding to the receive queue
 *          attempted for a non-shared thread queue set
 * @retval NCP_ST_TASK_NO_MALLOC_MEM A request for memory allocation could not
 *          be satisfied due to insufficient resources.
 * @retval NCP_ST_TASK_NULL_RECVQUEUEID_PTR the recvQueueId pointer is NULL
 * @retval NCP_ST_TASK_INVALID_NCA_INPUT_QUEUE queue ID exceeds upper limit
 * @retval NCP_ST_TASK_INVALID_FIXED_QUEUEID fixed queue IDs must be in the
 *          rang 128..255
 * @retval NCP_ST_TASK_NULL_PCQ_PRODUCER_PTR internal error
 * @retval NCP_ST_TASK_NULL_PCQ_CONSUMER_PTR  internal error
 * @retval NCP_ST_TASK_EXCLUSIVE_BINDING_NOT_AVAIL resource to bind is already
 *          in use
 * @retval NCP_ST_TASK_RECEIVE_QUEUES_MUST_HAVE_SAME_SHARE_PERMISSION All
 *          receive queues used by a thread must have same share permission,
 *          either all exclusive, or all shared.
 * @retval NCP_ST_TASK_RECV_ACCESS_MODE_NOT_SAME_AS_QUEUESET If the
 *          ncp_task_hdl_create function was used to open a queueset in
 *          exclusive mode, all assoiated receive queues must be bound in
 *          exclusive mode too.
 * @retval NCP_ST_TASK_NULL_RECV_QUEUE_PTR invalid receive queue pointer
 *          encountered
 * @retval NCP_ST_TASK_NULL_TASK_QUEUE_PTR invalid task queue pointer
 *          encountered
 * @retval NCP_ST_TASK_TQS_DISABLED the thread queue set is disabled
 */


NCP_API ncp_st_t
ncp_task_raw_recv_queue_bind(
    ncp_task_hdl_t           taskHdl,
    ncp_uint8_t              ncaQueueId,
    ncp_bool_t               shared,
    ncp_task_raw_recv_hdl_t *rxHdl);

/*!
 * @fn ncp_st_t ncp_task_raw_recv_queue_unbind(
 *      ncp_task_hdl_t taskHdl,
 *      ncp_task_raw_recv_hdl_t rxHdl);
 *
 * @brief This function removes the specified receive queue binding from
 *        service.
 *        All resources associated with the receive queue itself are freed.
 *
 * @param[in] taskHdl Task handle returned by previous call to
 *            ncp_task_hdl_create().
 * @param[in] rxHdl   The receive handle to unbind.
 *
 * @retval NCP_ST_NOT_IMPLEMENTED attempted to execute function with a v1 NCA.
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy
 * @retval NCP_ST_TASK_INVALID_TASK_HANDLE  The taskHdl parameter is not valid
 * @retval NCP_ST_TASK_RECEIVE_HANDLE_HEAD_NULL No receive queues are currently
 *          bound for this task handle
 * @retval NCP_ST_TASK_INVALID_RECEIVE_QUEUE receive queue ID is not currently
 *          bound
 * @retval NCP_ST_TASK_RECEIVE_QUEUE_NOT_FOUND The specified receive queue was
 *          not found in the list of receive queues associated with this task
 *          handle.
 */

NCP_API ncp_st_t
ncp_task_raw_recv_queue_unbind(
	ncp_task_hdl_t          taskHdl,
    ncp_task_raw_recv_hdl_t rxHdl);

/*!
 * @fn ncp_st_t ncp_task_raw_recv_queue_depth_get(
 *      ncp_task_raw_recv_hdl_t rxHdl,
 *      ncp_uint32_t   *depth)
 *
 * @brief This function returns the depth of the recv queue associated with
 *        rxHdl.
 *
 * @param[in] rxHdl   The receive handle to unbind.
 * @param[out] depth  Receive queue depth.
 *
 * @retval NCP_ST_NOT_IMPLEMENTED attempted to execute function with a v1 NCA.
 * @retval NCP_ST_INVALID_PARAMETER rxHdl is invalid.
 */
ncp_st_t ncp_task_raw_recv_queue_depth_get(
    ncp_task_raw_recv_hdl_t  rxHdl,
    ncp_uint32_t            *depth);

/* ============================================================================================================
 * END common raw API.
 * ============================================================================================================
 */

/*!
 * @fn ncp_st_t ncp_task_bulk_buffer_alloc(
 *      ncp_task_hdl_t   taskHdl,
 *      ncp_uint32_t     numTaskBuffers,
 *      ncp_uint32_t    *numTaskBuffersAllocated,
 *      ncp_uint32_t    *taskBufferSizes,
 *      void           **taskBuffers,
 *      ncp_bool_t       wait);
 *
 * @brief This function allocates one or more task buffers, up to a maximum of
 *        64 per function invocation. If numTaskBuffers is greater than 64,
 *        the function will return a failure status.
 *
 *        If a failure occurs after one or more buffers are successfully
 *        allocated, the function returns NCP_ST_SUCCESS and sets
 *        numTaskBuffersAllocated to the number of successfully allocated
 *        buffers.
 *
 * @note  If wait is TRUE and there are no buffers available, the function will
 *        wait until one or more buffers become available. Deadlock is
 *        possible, for instance if the thread that calls
 *        ncp_task_bulk_buffer_alloc() is holding all the buffers.
 *
 * @param[in] taskHdl Task handle returned by previous call to
 *            ncp_task_hdl_create().
 * @param[in] taskBufferSizes array of task sizes.
 * @param[in] numTaskBuffers number of task buffers requested. Must be less
 *            than or equal to 64.
 * @param[in, out] taskBuffers array of pointers that, upon successful
 *                 completion, contain the task buffer virtual addresses.
 * @param[out] numTaskBuffersAllocated number of allocated buffers.
 * @param[in] wait: If wait is set to FALSE, ncp_task_bulk_buffer_alloc will
 *                  allocate zero or more buffers, stopping if an error or
 *                  blocking condition is encountered, or if all buffers are
 *                  allocated. If wait is set to TRUE,
 *                  ncp_task_bulk_buffer_alloc will allocate one or more
 *                  buffers, buffer up to numTaskBuffers.
 *                  ncp_task_bulk_buffer_alloc may return with fewer than
 *                  numTaskBuffers buffers if an error occurs, or if a
 *                  blocking condition occurs after the first buffer is
 *                  allocated.
 *
 * @retval NCP_ST_INVALID_PARAMETER taskBuffers, taskBufferSizes, or 
 *          numTaskBuffersAllocated are NULL.
 * @retval NCP_ST_INVALID_PARAMETER numTaskBuffers is greater than 64.
 * @retval NCP_ST_INVALID_PARAMETER one or more taskBufferSizes entries is
 *          greater than the largest configured block size.
 * @retval NCP_ST_NOT_IMPLEMENTED Called with a v1 NCA (not supported, yet).
 * @retval NCP_ST_TASK_REQUEST_FOR_ZERO_LENGTH_TASK_BUFFER size must be greater
 *          than zero.
 * @retval NCP_ST_TASK_NO_MALLOC_MEM insufficient memory resources to satisfy
 *          request.
 * @retval NCP_ST_TASK_NO_MME_ALLOCATOR No MME allocator is configured for this
 *          task handle.
 */

NCP_API ncp_st_t
ncp_task_bulk_buffer_alloc(
    ncp_task_hdl_t   taskHdl,
    ncp_uint32_t     numTaskBuffers,
    ncp_uint32_t    *numTaskBuffersAllocated,
    ncp_uint32_t    *taskBufferSizes,
    void           **taskBuffers,
    ncp_bool_t       wait);

/*!
 * @fn ncp_st_t ncp_task_bulk_buffer_free(
 *      ncp_task_hdl_t   taskHdl,
 *      ncp_uint32_t     numTaskBuffers,
 *      ncp_uint32_t    *numTaskBuffersFreed,
 *      void           **taskBuffers,
 *      ncp_bool_t       wait);
 *
 * @brief This function frees one or more task buffers.
 *
 *        If a failure occurs after one or more buffers are successfully freed,
 *        the function returns NCP_ST_SUCCESS and sets numTaskBuffersFreed to
 *        the number of successfully freed buffers.
 *
 * @param[in] taskHdl: Task handle returned by previous call to
 *            ncp_task_hdl_create().
 * @param[in] numTaskBuffers: number of task buffers to be freed.
 * @param[in] taskBuffers: array of pointers to buffers to be freed.
 * @param[out] numTaskBuffersFreed: number of freed buffers.
 * @param[in] wait: If wait is set to FALSE, ncp_task_bulk_buffer_free will
 *                  free zero or more buffers, stopping if an error or blocking
 *                  condition is encountered, or if all buffers are freed.
 *                  If wait is set to TRUE, ncp_task_bulk_buffer_free will
 *                  free every buffer supplied, unless an error occurs.
 *
 * @retval NCP_ST_INVALID_PARAMETER taskBuffers or numTaskBuffersFreed are
 *          NULL.
 * @retval NCP_ST_INVALID_VALUE CPU pools only: a taskBuffer address is outside
 *          of the virtual address range of the CPU pool. No frees are
 *          performed in this case.
 * @retval NCP_ST_NOT_IMPLEMENTED Called with a v1 NCA.
 * @retval NCP_ST_TASK_CLIENT_FREE_NULLPTR tried to free a null buffer pointer.
 * @retval NCP_ST_TASK_REQUEST_FOR_ZERO_LENGTH_TASK_BUFFER size must be greater
 *          than zero.
 * @retval NCP_ST_TASK_NO_MALLOC_MEM insufficient memory resources to satisfy
 *          request.
 * @retval NCP_ST_TASK_SEND_DONE_RECURSION_DETECTED this function was called
 *          from a sendDone callback function.
 */

NCP_API ncp_st_t
ncp_task_bulk_buffer_free(
    ncp_task_hdl_t   taskHdl,
    ncp_uint32_t     numTaskBuffers,
    ncp_uint32_t    *numTaskBuffersFreed,
    void           **taskBuffers,
    ncp_bool_t       wait);

/*!
 * @fn ncp_st_t ncp_task_pool_ID_get(
 *      ncp_task_hdl_t  taskHdl,
 *      ncp_uint8_t    *poolID);
 *
 * @brief This function gets the pool ID associated with the task handle.
 *
 * @param[in] taskHdl: Task handle returned by previous call to
 *            ncp_task_hdl_create().
 * @param[out] poolID: a pointer to a location whose contents are filled with
 *              the pool ID.
 *
 * @retval NCP_ST_NOT_IMPLEMENTED attempted to execute function with a v1 NCA.
 * @retval NCP_ST_INVALID_PARAMETER poolID is NULL.
 */

NCP_API ncp_st_t
ncp_task_pool_ID_get(
    ncp_task_hdl_t  taskHdl,
    ncp_uint8_t    *poolID);

/*!
 * @fn ncp_st_t ncp_task_pool_type_get(
 *      ncp_task_hdl_t        taskHdl,
 *      ncp_task_pool_type_t *poolType);
 *
 * @brief This function gets the pool type associated with the task handle.
 *
 * @param[in] taskHdl: Task handle returned by previous call to
 *            ncp_task_hdl_create().
 * @param[out] poolType: a pointer to a location whose contents are filled with
 *              the pool type.
 *
 * @retval NCP_ST_NOT_IMPLEMENTED attempted to execute function with a v1 NCA.
 * @retval NCP_ST_INVALID_PARAMETER poolType is NULL.
 */

NCP_API ncp_st_t
ncp_task_pool_type_get(
    ncp_task_hdl_t        taskHdl,
    ncp_task_pool_type_t *poolType);

/*!
 * @fn ncp_st_t ncp_task_block_size_to_bytes(
 *      ncp_task_hdl_t              taskHdl,
 *      ncp_nca_task_block_sizes_t  pduBlockSize,
 *      ncp_uint32_t               *size);
 *
 * @brief This function converts the memory block size to its corresponding size *        in bytes.
 *
 * @param[in] pduBlockSize: the memory block size.
 * @param[out] size: a pointer to a location whose contents are filled with the
 *              size.
 *
 * @retval NCP_ST_INVALID_PARAMETER size is NULL or pduBlockSize is not in the
 * @retval NCP_ST_INVALID_PARAMETER pduBlockSize is not in the range 0-3
 *          (inclusive).
 * @retval NCP_ST_INVALID_PARAMETER pduBlockSize is greater than the largest
 *          configured block size.
 */

NCP_API ncp_st_t
ncp_task_block_size_to_bytes(
    ncp_task_hdl_t              taskHdl,
    ncp_nca_task_block_sizes_t  pduBlockSize,
    ncp_uint32_t               *size);

/*!
 * @fn ncp_st_t ncp_task_bytes_to_block_size(
 *      ncp_task_hdl_t              taskHdl,
 *      ncp_uint32_t                size,
 *      ncp_nca_task_block_sizes_t *pduBlockSize);
 *
 * @brief This function converts size (bytes) to the smallest memory block size
 *          that is at least as large as size. pduBlockSize is set to
 *          TASK_BLOCK_SZ_UNKNOWN if size is greater than the largest
 *          configured memory block size.
 *
 * @param[in] size: size (in bytes)
 * @param[in] pduBlockSize: a pointer to a location whose contents are filled
 *              with the calculated memory block size.
 *
 * @retval NCP_ST_INVALID_PARAMETER pduBlockSize is NULL or size is greater
 *          than any of the configured memory blocks.
 */

NCP_API ncp_st_t
ncp_task_bytes_to_block_size(
    ncp_task_hdl_t              taskHdl,
    ncp_uint32_t                size,
    ncp_nca_task_block_sizes_t *pduBlockSize);


/* ============================================================================================================
 * BEGIN common task buffer recovery API. These functions are common across both NCA V1 and NCA V2 hardware.
 * ============================================================================================================
 */


/*!
 * @fn ncp_st_t ncp_task_hdl_create_named(
 *                                  ncp_hdl_t            ncpHdl,
 *                                  ncp_uint8_t          threadQueueSetId,
 *                                  ncp_bool_t           shared,
 *                                  ncp_bool_t           orderedTaskCompletion,
 *                                  char                *name,
 *                                  ncp_bool_t          *taskHdlExists,
 *                                  ncp_task_hdl_t      *taskHdl);
 *
 * @brief This function is an extension of ncp_task_hdl_create().
 *        In addition to the actions performed by ncp_task_hdl_create(), this
 *        function allows for naming a task handle.
 *        Named task handles are introduced to enable continuous use of the
 *        same task handle across application thread restarts.
 *        The name must be unique; if two or more simultaneously active task
 *        handles share the same name, corruption will occur.
 *        Since task handles are thread-local, it is invalid to call
 *        ncp_task_hdl_create_named() more than once in a thread of execution.
 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to ncp_config.
 * @param[in]       threadQueueSetId: The linear ID (0..11) of the Thread
 *                      Queue Set.
 * @param[in]       shared: if TRUE, then the output type queues in the Thread
 *                      Queue Set are shared, otherwise they are reserved for
 *                      exclusive use. Note that input queues can never be
 *                      shared.
 * @param[in]       orderedTaskCompletion: If TRUE, then TaskIO module will 
 *                      perform output related maintenance operations on the
 *                      task completion PCQ, otherwise no maintenance
 *                      operations will be performed.
 * @param[in]       name: a unique null-terminated identifier for this task
 *                      handle. If a task handle with this name exists in NVM,
 *                      that handle will be used. If set to NULL, no name is
 *                      registered. The maximum length of name is
 *                      NCP_TASK_MAX_RESOURCE_NAME_LEN characters.
 * @param[out]      taskHdlExists: a boolean that indicates whether a task
 *                      handle with the given name already exists in NVM.
 * @param[in,out]   taskHdl: On success, the task handle is returned here.
 *
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid.
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized.
 * @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down dur to config_destroy .
 * @retval NCP_ST_TASK_NO_MALLOC_MEM insufficient memory resources to satisfy request.
 * @retval NCP_ST_TASK_TQS_DISABLED the thread queue set is disabled.
 * @rteval NCP_ST_TBR_ENABLED_BUT_NO_NAME_GIVEN tbrEnable is TRUE but name is NULL.
 * @retval NCP_ST_TASK_INVALID_TASK_HANDLE  The thread attempted to create a
 *          second handle.
*/	
	
NCP_API ncp_st_t
ncp_task_hdl_create_named(
    ncp_hdl_t            ncpHdl,
    ncp_uint8_t          threadQueueSetId,
    ncp_bool_t           shared,
    ncp_bool_t           orderedTaskCompletion,
    char                *name,
    ncp_bool_t          *taskHdlExists,
    ncp_task_hdl_t      *taskHdl);

/*!
 * @fn ncp_st_t ncp_task_tbr_enable(
 *       ncp_task_hdl_t       taskHdl,
 *       ncp_task_tbr_desc_t *tbrDesc);
 *
 * @brief This function enables Task Buffer Recovery (TBR) for a task handle.
 *
 *        TBR tracks task buffers held by application threads and (for named
 *        task handles only) provides a mechanism to recover those buffers if
 *        the thread experiences an unexpected termination.
 *       
 *        Internally each TBR-enabled task handle has one hash table per
 *        memory pool size, which track every application-owned buffer.
 *        Task receive and buffer allocation functions add buffers to the
 *        appropriate hash table, while task send, buffer free, and NCA refill
 *        functions remove buffers from the appropriate hash table.
 *
 *        If the application experiences an unexpected termination while owning
 *        one or more task buffers, the TBR data structure persists in NVM
 *        memory. When the named task handle is re-created with
 *        ncp_task_hdl_create_named(), the RTE will detect these outstanding
 *        buffers and flush them.
 *
 *        NOTE: ncp_task_tbr_enable() must be called before calling any
 *        functions that may operate on the TBR hash tables. Ideally, this
 *        function is called immediately after creating the task handle.
 *
 * @param[in]       taskHdl: task handle returned by previous call to
 *                      ncp_task_hdl_create or ncp_task_hdl_create_named.
 *                      If taskHdl is a named task handle, it is possible
 *                      to recover task buffers after a crash.
 * @param[in]       tbrDesc: an optional argument to customize the Task Buffer
 *                      Recovery hash tables. If set to NULL and tbrEnabled is
 *                      true, the default number of hash buckets and hash
 *                      functions are used.
 *
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_TASK_NO_MALLOC_MEM insufficient memory resources to satisfy request
 * @retval NCP_ST_TASK_TQS_DISABLED the thread queue set is disabled
*/	
	
NCP_API ncp_st_t
ncp_task_tbr_enable(
    ncp_task_hdl_t       taskHdl,
    ncp_task_tbr_desc_t *tbrDesc);

/*!
 * @fn ncp_st_t ncp_task_tbr_stats_get(
 *       ncp_task_hdl_t taskHdl,
 *       ncp_uint32_t   numBuffers[4]);
 *
 * @brief This function returns the occupancy of each TBR hash table and is
 *          intended for debug purposes.
 *
 * @param[in]       taskHdl: task handle returned by previous call to
 *                      ncp_task_hdl_create or ncp_task_hdl_create_named.
 *                      If taskHdl is a named task handle, it is possible
 *                      to recover task buffers after a crash.
 * @param[in]       numBuffers: an array containing the hash table occupancy
 *                      of the four hash tables.
 *
 * @retval NCP_ST_TASK_INVALID_TASK_HANDLE  The taskHdl parameter is not valid
 * @retval NCP_ST_INVALID_PARAMETER  The numBuffers parameter is NULL
*/	
	
NCP_API ncp_st_t
ncp_task_tbr_stats_get(
    ncp_task_hdl_t taskHdl,
    ncp_uint32_t   numBuffers[4]);

/*!
 * @fn ncp_st_t ncp_task_cpu_pool_reinit(
 *       ncp_hdl_t   ncpHdl,
 *       ncp_uint8_t poolID);
 *
 * @brief This function reinitializes the specified CPU pool to its
 *        post-configuration state, in order to recover from unexpected
 *        application termination. ncp_task_cpu_pool_reinit() flushes all NCA
 *        queues that use the specified pool, empties all affected TBR hash
 *        tables, and deletes any outstanding sendDone callbacks from affected
 *        output queues. All buffers from this pool held by application threads
 *        prior to this function's execution are invalid upon completion of
 *        this function.
 *
 *        NOTE: When this function is executing, all task handles that are
 *        bound to this pool must be quiesced (i.e. not executing any RTE
 *        functions), otherwise corruption will occur.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config.
 * @param[in] poolID: The ID of the CPU pool to reinitialize.
 *
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
 * @retval NCP_ST_TASK_SHARED_POOLS_NOT_SUPPORTED Called for a shared pool.
 * @retval NCP_ST_TASK_NO_TASK_HDL_USES_POOL No taskHdl is bound to the pool.
*/	
NCP_API ncp_st_t
ncp_task_cpu_pool_reinit(
    ncp_hdl_t   ncpHdl,
    ncp_uint8_t poolID);

/* ============================================================================================================
 * END Common APIs.   These APIs are common across both NCA V1 and NCA V2 hardware.
 * ============================================================================================================
 */



/* ============================================================================================================
 * Begin NCA V1 Legacy APIs.   The following APIs were developed for the ACP34xx/25xx family of prducts,  and more
 * specifically,   those chips that utilize the NCA V1 architecture.
 * The data structures used/returned by these APIs match those used by NCA V1 hardware.
 * The legacy APIs can be used when running on a platform that uses NCA V2 hardware,   but there is a performance
 * penalty for doing so,   since the RTE software must convert between NCA V1 and NCA V2 data structures.
 * Futhermore,   an application that is designed to use the legacy APIs,   cannot take advantage of some of the
 * new APIs that were developed specifically for the NCA V2 hardware.
 * ============================================================================================================
 */
 
 
/*!
 * @fn ncp_st_t ncp_task_buffer_alloc(  ncp_uint32_t size,
 *                                  	void **taskAddr);
 * @brief This API is called to allocate task buffers.   Note: this function cannot be called in kernel mode for AXM55xx (ncaV2).   Instead use the
 * native ncav2 equivalent function ncp_task_ncav2_buffer_alloc.    For AXM55xx targets this function will access POSIX thread local storage.   It is
 * recommended that the native ncaV2 API be used instead,  as it will be considerably faster.
 * 
 * @param[in]        size:     Task Size.
 * @param[in,out]    taskAddr: Aaddress of location wshere the allocated task buffer virtual address will be stored.
 * 
 * @retval NCP_ST_TASK_ALLOC_REQUIRES_POINTER  task alloc pointer for return val is NULL
 * @retval NCP_ST_TASK_REQUEST_FOR_ZERO_LENGTH_TASK_BUFFER size must be greater than zero
 * @retval NCP_ST_TASK_NO_MALLOC_MEM insufficient memory resources to satisfy request
 *
*/
NCP_API ncp_st_t
ncp_task_buffer_alloc (
	ncp_uint32_t size,
	void **taskAddr);

/*!
 * @fn ncp_st_t ncp_task_buffer_free(void *taskAddr);
 * @brief This API is called to free task buffers.  Note: this function cannot be called in kernel mode for AXM55xx (ncaV2).   Instead use the
 * native ncav2 equivalent function ncp_task_ncav2_buffer_free.  For AXM55xx targets this function will access POSIX thread local storage.   It is
 * recommended that the native ncaV2 API be used instead,  as it will be considerably faster.
 *
 * @param[in] taskAddr: task buffer to be freed.
 *
 * @retval NCP_ST_TASK_CLIENT_FREE_NULLPTR tried to free a null pointer
*/
NCP_API ncp_st_t
ncp_task_buffer_free (void *taskAddr);

 
/*!
 * @brief NCP_TASK_DATA : Task IO macro to return 32/64 bit virtual address of task data,   given the task header's VA.
 * @param[in]       task:  Pointer to task receive buffer
 * @retval          Pointer to start of task data within the task receive buffer supplied (no errors returned)
*/
#define NCP_TASK_DATA(_task) ((void *)((ncp_uint8_t *)(_task) + (_task)->dataOffset))


/*!
 * @fn ncp_st_t ncp_task_get_recv_queue_depth(ncp_task_hdl_t taskHdl,
 *                             ncp_uint8_t   ncaQueueId,
 *                             ncp_uint32_t   *pDepth);
 *
 *
 * @brief This API returns the number of tasks currently present in the receive queue specified in ncaQueueId
 * @param[in] taskHdl:    Task handle returned by previous call to ncp_task_hdl_create()
 * @param[in] ncaQueueId: Queue Number of receive queue to check.
 * @param[in,out] pointer to 32bit interger where result will be returned
 * @retval NCP_ST_SUCCESS The API was successfully executed,   and the RResult was returned in *pDepth
 * @retval NCP_ST_TASK_INVALID_NCA_INPUT_QUEUE The value supplied in ncaQueueId is too large
 * @retval NCP_ST_NOT_IMPLEMENTED The API is not supported for native mode simulation.
*/

NCP_API ncp_st_t
ncp_task_get_recv_queue_depth(ncp_task_hdl_t taskHdl,
                              ncp_uint8_t    ncaQueueId,
                              ncp_uint32_t   *pDepth);

/*!
 * @fn ncp_st_t ncp_task_recv(
 *      ncp_task_hdl_t taskHdl,
 *      ncp_uint8_t *pRecvQueueId,
 *      ncp_vp_hdl_t *pVpHdl,
 *      ncp_uint8_t *pEngineSequenceId,
 *      ncp_task_recv_buf_t **task,
 *      void **taskData,
 *      void **recvHandlerArg,
 *      ncp_bool_t wait)
 *
 * @brief   This API is called to receive a task. If the specified receive handle contains multiple receive queues then a weighted 
 *          round robin scheduling policy is used to arbitrate between the various queues. Note that the individual queue weights are 
 *          established at queue binding time. See ncp_task_recv_queue_vp_bind.
 *          Two task delivery models are supported: a return model and a dispatch model. In the return model the ncp_task_recv function 
 *          simply returns the next task and associated recvFuncArg to the caller.
 *          In the dispatch model the task is delivered directly to a pre-registered callback function (see ncp_task_recv_vp_bind). In this 
 *          case the ncp_task_recv function does not return with the task. Instead the ncp_task_recv function calls the user function that 
 *          is registered for the task's source VP. Upon completion of the client provided task receive function call,  the ncp_task_recv 
 *          API function will then return control to the caller with a status code of NCP_ST_TASK_DISPATCHED in order to allow the caller to 
 *          perform other work before processing the next task.
 *          Note that the task delivery model is configurable on a per-VP basis.
 *          Also note that, regardless of the delivery model, task receive processing is always performed within the context of the calling 
 *          thread.
 *
 * @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
 * @param[in,out] pRecvQueueId: Receive queue ID pointer. If the return delivery mechanism is enabled for the source VP then 
 *                the ID for the receive queue that this task was received from is stored in this location.
 * @param[in] vpHdl: Virtual pipeline handle
 * @param[in] engineSequenceId: Formerly Pipeline ID
 * @param[in,out] task: Pointer to a task receive buffer pointer. If the return delivery mechanism is enabled for the source pipeline 
 *                then the task buffer is stored in this location. See ncp_task_recv_buf_t.
 * @param[in,out] taskData: Pointer to a void pointer that references the first byte of task Data, if any. If the return delivery 
                  mechanism is enabled for the source pipeline then the virtual address of the task Data is stored in this location.
 * @param[in,out] recvHandlerArg: If supplied,   then the application supplied argument is returned here 
 * @param[in] wait: Boolean flag. If set to TRUE, specifies that the call should block if necessary until an input task becomes available
 *
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy   
 * @retval NCP_ST_TASK_INVALID_TASK_HANDLE  The taskHdl parameter is not valid
 * @retval NCP_ST_TASK_RECV_RET_SUCCESS_WITH_NULL_PTR internal error
 * @retval NCP_ST_TASK_CORRUPT_NCA_INPUT_QUEUE queue structure may be corrupt
 * @retval NCP_ST_TASK_INVALID_NCA_INPUT_ELEMENT_BUFFERID queue element is corrupt
 * @retval NCP_ST_TASK_ALLOC_REQUIRES_POINTER task alloc pointer for return val is NULL
 * @retval NCP_ST_TASK_REQUEST_FOR_ZERO_LENGTH_TASK_BUFFER size must be greater than zero
 * @retval NCP_ST_TASK_NO_MALLOC_MEM insufficient memory resources to satisfy request
 * @retval NCP_ST_TASK_POOLALLOC_RET_NULL Could not replenish NCA buffer pool
 * @retval NCP_ST_TASK_POOLALLOC_RET_PHYSADDR_NULL uUnexpected error when computing PA
 * @retval NCP_ST_TASK_QMAP_ERR_TOO_BIG queue ID exceeds upper limit
 * @retval NCP_ST_TASK_RXBUFFER_QUEUE_NOT_CONFIGURED queue must be configured in ASE config
 * @retval NCP_ST_TASK_NULL_PCQ_PRODUCER_PTR internal error
 * @retval NCP_ST_TASK_NULL_PCQ_CONSUMER_PTR   internal error
 * @retval NCP_ST_TASK_DISPATCHED informative status, task was successfully dispatched
 * @retval NCP_ST_TASK_RECV_QUEUE_EMPTY informative status, no tasks currently available
 * @retval NCP_ST_TASK_PUT_NULL_TASK_COMPLETION_QUEUE completion queue not bound
 * @retval NCP_ST_VPM_INVALID_VP_HDL the vpHdl parameter is not valid
 * @retval NCP_ST_VPM_ENGINE_SEQUENCE_NOT_FOUND invalid engine sequence
 * @retval NCP_ST_TASK_TQS_DISABLED the thread queue set is disabled
*/
NCP_API ncp_st_t
ncp_task_recv(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t *pRecvQueueId,
	ncp_vp_hdl_t *pVpHdl,
	ncp_uint8_t *pEngineSequenceId,
	ncp_task_recv_buf_t **task,
    void                **taskData,	
	void **recvHandlerArg,
	ncp_bool_t wait);

/*!
 * @fn ncp_st_t ncp_task_directed_recv(
 *      ncp_task_hdl_t taskHdl,
 *      ncp_uint8_t  ncaQueueId,
 *      ncp_vp_hdl_t *pVpHdl,
 *      ncp_uint8_t *pEngineSequenceId,
 *      ncp_task_recv_buf_t **task,
 *      void **taskData,
 *      void **recvHandlerArg,
 *      ncp_bool_t wait)
 *
 * @brief   This API is called to receive a task from a specific Nca receive queue.  The WRR state used by the ncp_task_recv API
 *          is not used,   and is not effected.   Note that if wait==TRUE,   then this API will block awaiting the arrival of
 *          an input task on the specified receive queue.   Tasks that arrive on other receive queues which may be bound to this
 *          task handle will be ignored,   and will not result in this API returning.   
 *          Two task delivery models are supported: a return model and a dispatch model. In the return model the ncp_task_recv function 
 *          simply returns the next task and associated recvFuncArg to the caller.
 *          In the dispatch model the task is delivered directly to a pre-registered callback function (see ncp_task_recv_vp_bind). In this 
 *          case the ncp_task_recv function does not return with the task. Instead the ncp_task_recv function calls the user function that 
 *          is registered for the task's source VP. Upon completion of the client provided task receive function call,  the ncp_task_recv 
 *          API function will then return control to the caller with a status code of NCP_ST_TASK_DISPATCHED in order to allow the caller to 
 *          perform other work before processing the next task.
 *          Note that the task delivery model is configurable on a per-VP basis.
 *          Also note that, regardless of the delivery model, task receive processing is always performed within the context of the calling 
 *          thread.
 *
 * @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
 * @param[in] ncaQueueId: The real ncaQueueID of the queue that this API will attempt to receive from. This is the same
 *                value supplied to the receive queue bind API.
  * @param[in] vpHdl: Virtual pipeline handle
 * @param[in] engineSequenceId: Formerly Pipeline ID
 * @param[in,out] task: Pointer to a task receive buffer pointer. If the return delivery mechanism is enabled for the source pipeline 
 *                then the task buffer is stored in this location. See ncp_task_recv_buf_t.
 * @param[in,out] taskData: Pointer to a void pointer that references the first byte of task Data, if any. If the return delivery 
                  mechanism is enabled for the source pipeline then the virtual address of the task Data is stored in this location.
 * @param[in,out] recvHandlerArg: If supplied,   then the application supplied argument is returned here 
 * @param[in] wait: Boolean flag. If set to TRUE, specifies that the call should block if necessary until an input task becomes available
 *
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy   
 * @retval NCP_ST_TASK_INVALID_TASK_HANDLE  The taskHdl parameter is not valid
 * @retval NCP_ST_TASK_RECV_RET_SUCCESS_WITH_NULL_PTR internal error
 * @retval NCP_ST_TASK_CORRUPT_NCA_INPUT_QUEUE queue structure may be corrupt
 * @retval NCP_ST_TASK_INVALID_NCA_INPUT_ELEMENT_BUFFERID queue element is corrupt
 * @retval NCP_ST_TASK_ALLOC_REQUIRES_POINTER task alloc pointer for return val is NULL
 * @retval NCP_ST_TASK_REQUEST_FOR_ZERO_LENGTH_TASK_BUFFER size must be greater than zero
 * @retval NCP_ST_TASK_NO_MALLOC_MEM insufficient memory resources to satisfy request
 * @retval NCP_ST_TASK_POOLALLOC_RET_NULL Could not replenish NCA buffer pool
 * @retval NCP_ST_TASK_POOLALLOC_RET_PHYSADDR_NULL uUnexpected error when computing PA
 * @retval NCP_ST_TASK_QMAP_ERR_TOO_BIG queue ID exceeds upper limit
 * @retval NCP_ST_TASK_RXBUFFER_QUEUE_NOT_CONFIGURED queue must be configured in ASE config
 * @retval NCP_ST_TASK_NULL_PCQ_PRODUCER_PTR internal error
 * @retval NCP_ST_TASK_NULL_PCQ_CONSUMER_PTR   internal error
 * @retval NCP_ST_TASK_DISPATCHED informative status, task was successfully dispatched
 * @retval NCP_ST_TASK_RECV_QUEUE_EMPTY informative status, no tasks currently available
 * @retval NCP_ST_TASK_PUT_NULL_TASK_COMPLETION_QUEUE completion queue not bound
 * @retval NCP_ST_VPM_INVALID_VP_HDL the vpHdl parameter is not valid
 * @retval NCP_ST_VPM_ENGINE_SEQUENCE_NOT_FOUND invalid engine sequence
 * @retval NCP_ST_TASK_TQS_DISABLED the thread queue set is disabled
*/
NCP_API ncp_st_t
ncp_task_directed_recv(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t  ncaQueueId,
	ncp_vp_hdl_t *pVpHdl,
	ncp_uint8_t *pEngineSequenceId,
	ncp_task_recv_buf_t **task,
    void                **taskData,	
	void **recvHandlerArg,
	ncp_bool_t wait);

/*!
 * @fn ncp_st_t ncp_task_recv_done(
 *                                  ncp_task_hdl_t taskHdl,
 *                              	ncp_task_recv_buf_t *task);
 * @brief   This API is called to indicate that CPU processing for the task is complete. The receiver is responsible for calling this 
 *          function when it finishes processing a task that was received from an ordered NCA queue and automatic flow completion mode is 
 *          disabled. This call is not required for tasks that are received from unordered NCA queues; or from ordered NCA queues when 
 *          automatic flow completion mode is configured. 
 *
 * @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
 * @param[in] task: Pointer to a task receive buffer pointer from a previous call to ncp_task_recv.
 *
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy   
ncp_task_create_recv_hdl
 * @retval NCP_ST_TASK_INVALID_TASK_HANDLE  The taskHdl parameter is not valid 
 * @retval NCP_ST_TASK_NULL_TASK_IN_RECVDONE must pass pointer to task to be completed
 * @retval NCP_ST_TASK_QMAP_ERR_TOO_BIG queue ID exceeds upper limit
 * @retval NCP_ST_TASK_COMPLETION_QUEUE_NOT_CONFIGURED queue must be configured in ASE config
 * @retval NCP_ST_TASK_NULL_PCQ_PRODUCER_PTR internal error
 * @retval NCP_ST_TASK_NULL_PCQ_CONSUMER_PTR  internal error
 * @retval NCP_ST_TASK_NO_MAN_COMPLETION_OWED The task supplied in the ncp_task_recv_done API does not match one which is awaiting manual completion.
 * @retval NCP_ST_TASK_NULL_MAN_COMPLETION_LIST No tasks received on this task handle are awaiting manual completion.
*/
NCP_API ncp_st_t
ncp_task_recv_done(
	ncp_task_hdl_t taskHdl,
	ncp_task_recv_buf_t *task);

	
/*!
 * @brief NCP Task IO Send Done Callback Function Prototype:
 *        describes the function that is called when the ncp_task_send() API is called in send 
 *        completion notification mode.   In send completion mode,  the Task I/O module calls this function after the NCA
 *        has successfully dequeued the task from the NCA output queue.   In this mode,   the Task I/O module does not automatically
 *        free the buffer(s) associated with the task,   and after receiving the callback the application must free or reuse 
 *        the buffer.   Note the buffer was allocated by the the ncp_task_buffer_alloc API and therefore belongs to the task 
 *        I/O module and must be eventually returned to the pool by calling the ncp_task_buffer_free API.
*/
typedef void (*ncp_task_send_done_fn_t)(
    void *sendDoneFuncArg,  /*!< An opaque argument supplied by the application on the ncp_task_send() and returned at task-done time */
	void *txBuffer);        /*!< The task buffer that was suppllied to the ncp_task_send API */
		 

/*!
 * @fn ncp_st_t ncp_task_send(	ncp_task_hdl_t taskHdl,
 *                          ncp_vp_hdl_t vpHdl,
 *                      	ncp_task_send_meta_t    *taskMetaData,
 *                      	void *taskBuffer, 
 *                      	void *taskPduData,
 *                      	ncp_bool_t wait,
 * 	                        ncp_task_send_done_fn_t sendDoneFn,
 *                          void *                  sendDoneFuncArg);
 *
 * @brief API function sends a task. The entire task must be contiguous.
 *
 * @param[in]:  taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
 * @param vpHdl: Virtual Pipeline handle
 * @param[in] taskMetaData: Pointer to task meta data
 * @param[in] taskBuffer: Pointer to task buffer address that was allocated by the ncp_task_buffer_alloc() API (used in free)
 * @param[in] taskPduData: Pointer to start of task PDU data to be transmitted.  May be same as taskBuffer. 
 * @param[in] wait:  Boolean flag. If set to TRUE, specifies that the call should block if necessary until task output queue resources are 
 *               available to queue this task for transmission.
 * @param[in] sendDoneDoneFn: If null,   then send completion mode is not in effect for the current send,  and the RTE will automatically free the task buffers
 *            associated with this API.   The task buffer(s) must not be modified or reused after calling this API with sendDoneFn == NULL.
 *            If not null,   then this parameter specifies the application provided function pointer to be called when the task has been delivered to the NCA.   The task buffers
 *            provided must not be modified in any manner whatsoever between the time that this API returns and when the callback function is executed.
 *            It is the threads responsibility to eventually free or reuse the buffers associated with this API when a sendDoneFn is provided.
 *            The callback will be performed in the context of the thread that requested it,   and will be executed while processing a subsequent call 
 *            to a send-type API,  including send_queue_flush.
 * @param[in] sendDoneFuncArg: Opaque argument to be included in call to sendDoneFn,  if sendDoneFn provided.  
 *
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
 * @retval NCP_ST_TASK_SEND_NULL_METADATA_PTR  metadata pointer must not be NULL
 * @retval NCP_ST_TASK_SEND_NULL_TASK_PTR  task pointer must not be NULL if dataSize != 0
 * @retval NCP_ST_TASK_SEND_QUEUE_FULL  informative status, no room for task in send queue
 * @retval NCP_ST_TASK_BUFFSIZE_TOO_LARGE  task size exceeds memory pool maximum size buffer
 * @retval NCP_ST_TASK_BUFFPOOL_CORRUPTION  internal error,  buffer pool corruption detected
 * @retval NCP_ST_NO_MEMORY  insufficient memory
 * @retval NCP_ST_TASK_PUT_NULL_TASK_OUTPUT_QUEUE  send queue not bound
 * @retval NCP_ST_TASK_PUT_NULL_TASK_COMPLETION_QUEUE  completion queue not bound
 * @retval NCP_ST_TASK_CLIENT_FREE_NULLPTR tried to free a null pointer
 * @retval NCP_ST_VPM_INVALID_VP_HDL the vpHdl parameter is not valid
 * @retval NCP_ST_TASK_SEND_DONE_RECURSION_DETECTED this function was called
 *          from a sendDone callback function.
 * @retval NCP_ST_TASK_TQS_DISABLED the thread queue set is disabled
 *
*/
NCP_API ncp_st_t
ncp_task_send (
	ncp_task_hdl_t taskHdl,
	ncp_vp_hdl_t vpHdl,
	ncp_task_send_meta_t *taskMetaData,
	void *taskBuffer,
	void *taskPduData,
	ncp_bool_t wait,
	ncp_task_send_done_fn_t sendDoneFn,
    void                   *sendDoneFuncArg);

/*!
 * @fn ncp_st_t ncp_task_send_segments(	ncp_task_hdl_t taskHdl,
 *                          ncp_vp_hdl_t                vpHdl,
 *                      	ncp_task_send_meta_t        *taskMetaData,
  *                      	ncp_uint8_t                 numSegs,
 *                          ncp_task_segment_entry_t    *pSegTable,
 *                      	ncp_bool_t                  wait,
 *                      	ncp_task_send_done_fn_t     sendDoneFn,
 *                          void                       *sendDoneFuncArg)
 *
 * @brief This API sends a discontiguous task using output gather-mode DMA. 
 *
 * @param[in]:   taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
 * @param vpHdl: Virtual Pipeline handle
 * @param[in] taskMetaData: Pointer to task meta data
 * @param[in] numSegs: The number of desriptors pointed to by pSegTable below.
 * The valid range for this parameter is 1..16 for ncaV1 platforms (ACP34xx.ACP25xx)
 * Zero is valid if the task contains no data. The valid range is limited to 1..6 when running on ncaV2 harware (AXM55xx and beyond).
 * @param[in] pSegTable: Pointer to the descriptor table associated with the output gather-mode DMA.   There is one descriptor per contiguous segment.
 * @param[in] wait:  Boolean flag. If set to TRUE, specifies that the call should block if necessary until task output queue resources are 
 *               available to queue this task for transmission.
 * @param[in] sendDoneDoneFn: If null,   then send completion mode is not in effect for the current send,  and the RTE will automatically free the task buffers
 *            associated with this API.   The task buffer(s) must not be modified or reused after calling this API with sendDoneFn == NULL.
 *            If not null,   then this parameter specifies the application provided function pointer to be called when the task has been delivered to the NCA.   The task buffers
 *            provided must not be modified in any manner whatsoever between the time that this API returns and when the callback function is executed.
 *            It is the threads responsibility to eventually free or reuse the buffers associated with this API when a sendDoneFn is provided.
 *            The callback will be performed in the context of the thread that requested it,   and will be executed while processing a subsequent call 
 *            to a send-type API,  including send_queue_flush.
 * @param[in] sendDoneFuncArg:   Application provided opaqueue data to be used in sendDone callback function above is provided. 
 *
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
 * @retval NCP_ST_TASK_SEND_NULL_METADATA_PTR metadata pointer must not be NULL
 * @retval NCP_ST_TASK_SEND_SEGMENTS_INVALID_DESC A call to ncp_task_send_segments failed due to a NULL descriptor table pointer.
 * @retval NCP_ST_TASK_SEND_SEGMENTS_INVALID_NUM_SEGS A call to ncp_task_send_segments failed due to the number of segments being less that zero or greater than 16. 
 * @retval NCP_ST_TASK_SEND_QUEUE_FULL  informative status, no room for task in send queue
 * @retval NCP_ST_TASK_BUFFSIZE_TOO_LARGE  task size exceeds memory pool maximum size buffer
 * @retval NCP_ST_TASK_BUFFPOOL_CORRUPTION  internal error,  buffer pool corruption detected
 * @retval NCP_ST_NO_MEMORY  insufficient memory
 * @retval NCP_ST_TASK_PUT_NULL_TASK_OUTPUT_QUEUE  send queue not bound
 * @retval NCP_ST_TASK_PUT_NULL_TASK_COMPLETION_QUEUE  completion queue not bound
 * @retval NCP_ST_TASK_CLIENT_FREE_NULLPTR tried to free a null pointer
 * @retval NCP_ST_VPM_INVALID_VP_HDL the vpHdl parameter is not valid
 * @retval NCP_ST_TASK_SEND_DONE_RECURSION_DETECTED this function was called
 *          from a sendDone callback function.
 * @retval NCP_ST_TASK_TQS_DISABLED the thread queue set is disabled
 */
 
NCP_API ncp_st_t
ncp_task_send_segments (
	ncp_task_hdl_t taskHdl,
	ncp_vp_hdl_t         vpHdl,
	ncp_task_send_meta_t *taskMetaData,
   	ncp_uint8_t          numSegs,
    ncp_task_segment_entry_t    *pSegTable,
	ncp_bool_t                  wait,
	ncp_task_send_done_fn_t     sendDoneFn,
	void                        *sendDoneFuncArg);


/*!
 * @fn ncp_st_t ncp_task_completion_queue_flush(	
 *                                      ncp_task_hdl_t taskHdl,
 *                                      ncp_bool_t wait,
 *                                      ncp_bool_t *pQueueStatus);
 *
 * @brief This API is called to test the task completion queue for the empty condition.   If the wait parameter is set to true,  
 *         then the function will block until all previously queued output tasks have been processed by the NCA.
 *
 * @param[in] taskHdl: taskHdl handle returned by task module in a previous call to ncp_task_hdl_create
 * @param[in] wait: If FALSE,   then return current queue status in queueEmpty,  else wait for queue to drain
 * @param[in,out] pQueueEmpty: Pointer to boolean where queue status is returned, 0->empty, 1->not empty
 *
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy  
*/
NCP_API ncp_st_t
ncp_task_completion_queue_flush(
    ncp_task_hdl_t taskHdl,
    ncp_bool_t     wait,
    ncp_bool_t     *pQueueStatus);
    
/*!
 * @fn ncp_st_t ncp_task_queue_group_to_core(	
 *                  ncp_hdl_t        ncpHdl,
 *                  int              queueGroup,
 *                  int             *core,
 *                  core_location_t *location);
 *
 * @brief This API is called to determine the core affinity of a given queue
 *          group. On success, *(core) contains the core ID of the queue
 *          group, or -1 to indicate any cpu. *(location) indicates whether
 *          the affinity is to an internal or external core.
 *
 * @param[in] ncpHdl:  NCP API state handle.
 * @param[in] queueGroup: the queue group ID
 * @param[out] core: the core ID
 * @param[out] location: the location (internal or external) of the core.
 *
 * @retval NCP_ST_INVALID_PARAMETER queueGroup is outside the range of valid
 *          queue group IDs.
 * @retval NCP_ST_INVALID_PARAMETER location is NULL
 * @retval NCP_ST_INVALID_PARAMETER core is NULL
*/

NCP_API ncp_st_t
ncp_task_queue_group_to_core(
    ncp_hdl_t        ncpHdl,
    ncp_int32_t      queueGroup,
    ncp_int32_t     *core,
    core_location_t *location);
 
/* ============================================================================================================
 * End NCA V1 Legacy APIs.   
 * ============================================================================================================
 */ 

   
/* ============================================================================================================
 * Begin NCA V2 Native APIs.   The following APIs were developed for the AXM55xx,  and more
 * specifically,   those chips that utilize the NCA V2 architecture.
 * The data structures used/returned by these APIs match those used by NCA V2 hardware.
 * The NCA V2 Native APIs are not backward compatible,  and can only be used when running on a platform that 
 * uses NCA V2 hardware.
 * ============================================================================================================
 */
   
/*!
 * @brief NCP Task NCAv2 I/O Send Done Callback Function Prototype:
 *          describes the function that is called when ncp_task_ncav2_send() or
 *          ncp_task_ncav2_raw_send() is called in send completion notification
 *          mode. In send completion mode, the Task I/O module calls this
 *          function after the NCA has successfully dequeued the task from the
 *          NCA output queue. In this mode, the Task I/O module does not
 *          automatically free the buffer(s) associated with the task, and
 *          after receiving the callback the application is free to free or
 *          reuse the buffer.
 *
 *          Note that within a sendDone callback, only a subset of the task I/O
 *          API may be called. No send functions, free functions (unless the
 *          TQS uses a CPU-managed pool), recv functions, or NCA refill
 *          functions may be called within the send callback. Specifically, the
 *          following functions may not be called from an NCAv2 sendDone
 *          callback: ncp_task_send(), ncp_task_ncav2_send()
 *          ncp_task_send_segments(), ncp_task_ncav2_raw_send(),
 *          ncp_task_buffer_free(), ncp_task_ncav2_buffer_free(),
 *          ncp_task_ncav2_free_pdu_segments(), ncp_task_ncav2_free_rx_task(),
 *          ncp_task_ncav2_bulk_buffer_free(), ncp_task_recv(),
 *          ncp_task_ncav2_recv(), ncp_task_recv_done(),
 *          ncp_task_ncav2_recv_done(), ncp_task_ncav2_raw_nca_refill().
 *
 *          One common send done callback usage it to note which buffers are
 *          available for reuse, then to free them upon return from the send or
 *          queue flush function.
 *
 *          Note that when using send completion mode with multiple transmit
 *          threads sharing a thread queue set, the threads must share the same
 *          address space.
*/

typedef void (*ncp_task_ncav2_send_done_fn_t)(
    void *sendDoneFuncArg, /* An opaque argument supplied by the application
                              and returned at task-done time */
    ncp_int32_t ptrCnt, /* The number of valid task buffers */
    void *pduSegAddr0,  /* Task buffer address #0 */
    void *pduSegAddr1,  /* Task buffer address #1 */
    void *pduSegAddr2,  /* Task buffer address #2 */
    void *pduSegAddr3,  /* Task buffer address #3 */
    void *pduSegAddr4,  /* Task buffer address #4 */
    void *pduSegAddr5   /* Task buffer address #5 */
);


   
/*!
 *
 * @brief NCP_TASK_NCAV2_DATA : NCP Task IO macro to return 32/64 bit virtual address of task data start address,   given the task header's VA
 * @param[in]       task:  Pointer to task receive buffer
 * @retval          Pointer to start of task data within the task receive buffer supplied (no errors returned)
*/   
#define NCP_TASK_NCAV2_DATA(_task) ((void *)(ncp_raw_addr_t)((ncp_task_ncaV2_recv_buf_t *)(_task))->pduSegAddr0) 

/*!
 * @fn ncp_st_t ncp_task_ncav2_recv(
 *      ncp_task_hdl_t taskHdl,
 *      ncp_uint8_t *pRecvQueueId,
 *      ncp_vp_hdl_t *pVpHdl,
 *      ncp_uint8_t *pEngineSequenceId,
 *      ncp_task_ncaV2_recv_buf_t **task,
 *      void **recvHandlerArg,
 *      ncp_bool_t wait)
 *
 * @brief   This API is called to receive a task. If the specified receive handle contains multiple receive queues then a weighted 
 *          round robin scheduling policy is used to arbitrate between the various queues. Note that the individual queue weights are 
 *          established at queue binding time. See ncp_task_recv_queue_vp_bind.
 *          Two task delivery models are supported: a return model and a dispatch model. In the return model the ncp_task_recv function 
 *          simply returns the next task and associated recvFuncArg to the caller.
 *          In the dispatch model the task is delivered directly to a pre-registered callback function (see ncp_task_recv_vp_bind). In this 
 *          case the ncp_task_recv function does not return with the task. Instead the ncp_task_recv function calls the user function that 
 *          is registered for the task's source VP. Upon completion of the client provided task receive function call,  the ncp_task_recv 
 *          API function will then return control to the caller with a status code of NCP_ST_TASK_DISPATCHED in order to allow the caller to 
 *          perform other work before processing the next task.
 *          Note that the task delivery model is configurable on a per-VP basis.
 *          Also note that, regardless of the delivery model, task receive processing is always performed within the context of the calling 
 *          thread.
 *
 * @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
 * @param[in,out] pRecvQueueId: Receive queue ID pointer. If the return delivery mechanism is enabled for the source VP then 
 *                the ID for the receive queue that this task was received from is stored in this location.
 * @param[in] vpHdl: Virtual pipeline handle
 * @param[in] engineSequenceId: Formerly Pipeline ID
 * @param[in,out] task: Pointer to a task receive buffer pointer. If the return delivery mechanism is enabled for the source pipeline 
 *                then the task buffer is stored in this location. See ncp_task_recv_buf_t.
 * @param[in,out] recvHandlerArg: If supplied,   then the application supplied argument is returned here 
 * @param[in] wait: Boolean flag. If set to TRUE, specifies that the call should block if necessary until an input task becomes available
 *
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy   
 * @retval NCP_ST_TASK_INVALID_TASK_HANDLE  The taskHdl parameter is not valid
 * @retval NCP_ST_TASK_RECV_RET_SUCCESS_WITH_NULL_PTR internal error
 * @retval NCP_ST_TASK_CORRUPT_NCA_INPUT_QUEUE queue structure may be corrupt
 * @retval NCP_ST_TASK_INVALID_NCA_INPUT_ELEMENT_BUFFERID queue element is corrupt
 * @retval NCP_ST_TASK_ALLOC_REQUIRES_POINTER task alloc pointer for return val is NULL
 * @retval NCP_ST_TASK_REQUEST_FOR_ZERO_LENGTH_TASK_BUFFER size must be greater than zero
 * @retval NCP_ST_TASK_NO_MALLOC_MEM insufficient memory resources to satisfy request
 * @retval NCP_ST_TASK_POOLALLOC_RET_NULL Could not replenish NCA buffer pool
 * @retval NCP_ST_TASK_POOLALLOC_RET_PHYSADDR_NULL uUnexpected error when computing PA
 * @retval NCP_ST_TASK_QMAP_ERR_TOO_BIG queue ID exceeds upper limit
 * @retval NCP_ST_TASK_RXBUFFER_QUEUE_NOT_CONFIGURED queue must be configured in ASE config
 * @retval NCP_ST_TASK_NULL_PCQ_PRODUCER_PTR internal error
 * @retval NCP_ST_TASK_NULL_PCQ_CONSUMER_PTR   internal error
 * @retval NCP_ST_TASK_DISPATCHED informative status, task was successfully dispatched
 * @retval NCP_ST_TASK_RECV_QUEUE_EMPTY informative status, no tasks currently available
 * @retval NCP_ST_TASK_PUT_NULL_TASK_COMPLETION_QUEUE completion queue not bound
 * @retval NCP_ST_VPM_INVALID_VP_HDL the vpHdl parameter is not valid
 * @retval NCP_ST_VPM_ENGINE_SEQUENCE_NOT_FOUND invalid engine sequence
 * @retval NCP_ST_TASK_TQS_DISABLED the thread queue set is disabled
*/
NCP_API ncp_st_t
ncp_task_ncav2_recv(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t *pRecvQueueId,
	ncp_vp_hdl_t *pVpHdl,
	ncp_uint8_t *pEngineSequenceId,
	ncp_task_ncaV2_recv_buf_t **task,
	void **recvHandlerArg,
	ncp_bool_t wait);

/*!
 * @fn ncp_st_t ncp_task_ncav2_directed_recv(
 *      ncp_task_hdl_t taskHdl,
 *      ncp_uint8_t ncaQueueId,
 *      ncp_vp_hdl_t *pVpHdl,
 *      ncp_uint8_t *pEngineSequenceId,
 *      ncp_task_ncaV2_recv_buf_t **task,
 *      void **recvHandlerArg,
 *      ncp_bool_t wait)
 *
 * @brief   This API is called to receive a task from a specific Nca receive queue.  The WRR state used by the ncp_task_recv API
 *          is not used,   and is not effected.   Note that if wait==TRUE,   then this API will block awaiting the arrival of
 *          an input task on the specified receive queue.   Tasks that arrive on other receive queues which may be bound to this
 *          task handle will be ignored,   and will not result in this API returning. 
 *          Two task delivery models are supported: a return model and a dispatch model. In the return model the ncp_task_recv function 
 *          simply returns the next task and associated recvFuncArg to the caller.
 *          In the dispatch model the task is delivered directly to a pre-registered callback function (see ncp_task_recv_vp_bind). In this 
 *          case the ncp_task_recv function does not return with the task. Instead the ncp_task_recv function calls the user function that 
 *          is registered for the task's source VP. Upon completion of the client provided task receive function call,  the ncp_task_recv 
 *          API function will then return control to the caller with a status code of NCP_ST_TASK_DISPATCHED in order to allow the caller to 
 *          perform other work before processing the next task.
 *          Note that the task delivery model is configurable on a per-VP basis.
 *          Also note that, regardless of the delivery model, task receive processing is always performed within the context of the calling 
 *          thread.
 *
 * @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
 * @param[in] ncaQueueId: The real ncaQueueID of the queue that this API will attempt to receive from. This is the same
 *                value supplied to the receive queue bind API.
 * @param[in] vpHdl: Virtual pipeline handle
 * @param[in] engineSequenceId: Formerly Pipeline ID
 * @param[in,out] task: Pointer to a task receive buffer pointer. If the return delivery mechanism is enabled for the source pipeline 
 *                then the task buffer is stored in this location. See ncp_task_recv_buf_t.
 * @param[in,out] recvHandlerArg: If supplied,   then the application supplied argument is returned here 
 * @param[in] wait: Boolean flag. If set to TRUE, specifies that the call should block if necessary until an input task becomes available
 *
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy   
 * @retval NCP_ST_TASK_INVALID_TASK_HANDLE  The taskHdl parameter is not valid
 * @retval NCP_ST_TASK_RECV_RET_SUCCESS_WITH_NULL_PTR internal error
 * @retval NCP_ST_TASK_CORRUPT_NCA_INPUT_QUEUE queue structure may be corrupt
 * @retval NCP_ST_TASK_INVALID_NCA_INPUT_ELEMENT_BUFFERID queue element is corrupt
 * @retval NCP_ST_TASK_ALLOC_REQUIRES_POINTER task alloc pointer for return val is NULL
 * @retval NCP_ST_TASK_REQUEST_FOR_ZERO_LENGTH_TASK_BUFFER size must be greater than zero
 * @retval NCP_ST_TASK_NO_MALLOC_MEM insufficient memory resources to satisfy request
 * @retval NCP_ST_TASK_POOLALLOC_RET_NULL Could not replenish NCA buffer pool
 * @retval NCP_ST_TASK_POOLALLOC_RET_PHYSADDR_NULL uUnexpected error when computing PA
 * @retval NCP_ST_TASK_QMAP_ERR_TOO_BIG queue ID exceeds upper limit
 * @retval NCP_ST_TASK_RXBUFFER_QUEUE_NOT_CONFIGURED queue must be configured in ASE config
 * @retval NCP_ST_TASK_NULL_PCQ_PRODUCER_PTR internal error
 * @retval NCP_ST_TASK_NULL_PCQ_CONSUMER_PTR   internal error
 * @retval NCP_ST_TASK_DISPATCHED informative status, task was successfully dispatched
 * @retval NCP_ST_TASK_RECV_QUEUE_EMPTY informative status, no tasks currently available
 * @retval NCP_ST_TASK_PUT_NULL_TASK_COMPLETION_QUEUE completion queue not bound
 * @retval NCP_ST_VPM_INVALID_VP_HDL the vpHdl parameter is not valid
 * @retval NCP_ST_VPM_ENGINE_SEQUENCE_NOT_FOUND invalid engine sequence
 * @retval NCP_ST_TASK_TQS_DISABLED the thread queue set is disabled
*/
NCP_API ncp_st_t
ncp_task_ncav2_directed_recv(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t  ncaQueueId,
	ncp_vp_hdl_t *pVpHdl,
	ncp_uint8_t *pEngineSequenceId,
	ncp_task_ncaV2_recv_buf_t **task,
	void **recvHandlerArg,
	ncp_bool_t wait);

/*!
 * @fn ncp_st_t NCP_API ncp_st_t ncp_task_ncav2_send (
 *	ncp_task_hdl_t taskHdl,
 *	ncp_vp_hdl_t vpHdl,
 *	ncp_task_ncaV2_send_meta_t *taskMetaData,
 *	ncp_bool_t wait,
 *	ncp_task_ncav2_send_done_fn_t sendDoneFn,
 *  void                   *sendDoneFuncArg	);
 *
 * @brief API function sends a task. The task pdu data can be split into a maximum of six segments,  as identified by the meta data pointer count,
* pdu segment addresses,  and pdu segment sizes.   Each segment must be a unique task buffer.   It is not valid  for more than on pduSegAddr
* to reference any potion of the same task buffer.
 *
 * @param[in]:  taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
 * @param vpHdl: Virtual Pipeline handle
 * @param[in] taskMetaData: Pointer to task meta data
 * @param[in] wait:  Boolean flag. If set to TRUE, specifies that the call should block if necessary until task output queue resources are 
 *               available to queue this task for transmission.
 * @param[in] sendDoneDoneFn: If null,   then send completion mode is not in effect for the current send,  and the RTE will automatically free the task buffers
 *            associated with this API.   The task buffer(s) must not be modified or reused after calling this API with sendDoneFn == NULL.
 *            If not null,   then this parameter specifies the application provided function pointer to be called when the task has been delivered to the NCA.   The task buffers
 *            provided must not be modified in any manner whatsoever between the time that this API returns and when the callback function is executed.
 *            It is the threads responsibility to eventually free or reuse the buffers associated with this API when a sendDoneFn is provided.
 *            The callback will be performed in the context of the thread that requested it,   and will be executed while processing a subsequent call 
 *            to a send-type API,  including send_queue_flush.
 * @param[in] sendDoneFuncArg: Opaque argument to be included in call to sendDoneFn,  if sendDoneFn provided.  
 * 
 *
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
 * @retval NCP_ST_TASK_SEND_NULL_METADATA_PTR  metadata pointer must not be NULL
 * @retval NCP_ST_TASK_SEND_NULL_TASK_PTR  task pointer must not be NULL if dataSize != 0
 * @retval NCP_ST_TASK_SEND_QUEUE_FULL  informative status, no room for task in send queue
 * @retval NCP_ST_TASK_BUFFSIZE_TOO_LARGE  task size exceeds memory pool maximum size buffer
 * @retval NCP_ST_TASK_BUFFPOOL_CORRUPTION  internal error,  buffer pool corruption detected
 * @retval NCP_ST_NO_MEMORY  insufficient memory
 * @retval NCP_ST_TASK_PUT_NULL_TASK_OUTPUT_QUEUE  send queue not bound
 * @retval NCP_ST_TASK_PUT_NULL_TASK_COMPLETION_QUEUE  completion queue not bound
 * @retval NCP_ST_TASK_CLIENT_FREE_NULLPTR tried to free a null pointer
 * @retval NCP_ST_VPM_INVALID_VP_HDL the vpHdl parameter is not valid
 * @retval NCP_ST_TASK_TQS_DISABLED the thread queue set is disabled
 *
*/
NCP_API ncp_st_t
ncp_task_ncav2_send (
	ncp_task_hdl_t taskHdl,
	ncp_vp_hdl_t vpHdl,
	ncp_task_ncaV2_send_meta_t *taskMetaData,
	ncp_bool_t wait,
	ncp_task_ncav2_send_done_fn_t sendDoneFn,
    void *sendDoneFuncArg);


/*!
 * @fn ncp_st_t ncp_task_ncav2_recv_done(
 *	ncp_task_hdl_t taskHdl,
 * 	ncp_task_ncaV2_recv_buf_t *task,
 *	ncp_bool_t freePduSegments);
 * @brief   This API is called to indicate that CPU processing for the task is complete. The receiver is responsible for calling this 
 *          function when it finishes processing a task that was received from an ordered NCA queue and automatic flow completion mode is 
 *          disabled. This call is not required for tasks that are received from unordered NCA queues; or from ordered NCA queues when 
 *          automatic flow completion mode is configured. 
 *
 * @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
 * @param[in] task: Pointer to a task receive buffer pointer from a previous call to ncp_task_recv.
 * @param[in] freePduSegments: If true,   then the task and all of its pdu segments will be freed in addition to the
 *            task completion being performed.
 *
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy   
ncp_task_create_recv_hdl
 * @retval NCP_ST_TASK_INVALID_TASK_HANDLE  The taskHdl parameter is not valid 
 * @retval NCP_ST_TASK_NULL_TASK_IN_RECVDONE must pass pointer to task to be completed
 * @retval NCP_ST_TASK_QMAP_ERR_TOO_BIG queue ID exceeds upper limit
 * @retval NCP_ST_TASK_COMPLETION_QUEUE_NOT_CONFIGURED queue must be configured in ASE config
 * @retval NCP_ST_TASK_NULL_PCQ_PRODUCER_PTR internal error
 * @retval NCP_ST_TASK_NULL_PCQ_CONSUMER_PTR  internal error
 * @retval NCP_ST_TASK_NO_MAN_COMPLETION_OWED The task supplied in the ncp_task_recv_done API does not match one which is awaiting manual completion.
 * @retval NCP_ST_TASK_NULL_MAN_COMPLETION_LIST No tasks received on this task handle are awaiting manual completion.
*/
NCP_API ncp_st_t
ncp_task_ncav2_recv_done(
	ncp_task_hdl_t taskHdl,
	ncp_task_ncaV2_recv_buf_t *task,
	ncp_bool_t freePduSegments);

/*!
 * @fn ncp_st_t ncp_task_ncav2_free_rx_task(
 *	ncp_task_hdl_t taskHdl,
 *	ncp_task_ncaV2_recv_buf_t *task);	
 * @brief This API is called to free a previously received task and all of its associated pdu segments.
 * The receive buffer header contents must not be changed prior to calling this API.   This API must
 * not be called to free tasks or buffers obtained using the legacy ncp_task_recv API.
 *
 * @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create() 
 * @param[in] taskAddr: task previously returned by ncp_task_ncav2_recv API
 *
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized 
 * @retval NCP_ST_TASK_CLIENT_FREE_NULLPTR tried to free a null pointer
 * @retval NCP_ST_TASK_SEND_DONE_RECURSION_DETECTED this function was called
 *          from a sendDone callback function.
*/	
NCP_API ncp_st_t
ncp_task_ncav2_free_rx_task(
	ncp_task_hdl_t taskHdl,
	ncp_task_ncaV2_recv_buf_t *task);	

/*!
 * @fn ncp_st_t ncp_task_ncav2_free_pdu_segments(
 *	ncp_task_hdl_t taskHdl,
 *	ncp_ncaV2_free_pdu_segments_t *task);
 *	
 * @brief This API is called to free multiple task buffers.   It is the callers responsibility to
 * fully populate the ncp_ncaV2_free_pdu_segments_t data structure.
 *
 * @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create() 
 * @param[in] taskAddr: task buffer to be freed.
 *
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized 
 * @retval NCP_ST_TASK_CLIENT_FREE_NULLPTR tried to free a null pointer
 * @retval NCP_ST_TASK_SEND_DONE_RECURSION_DETECTED this function was called
 *          from a sendDone callback function.
*/	
NCP_API ncp_st_t
ncp_task_ncav2_free_pdu_segments(
	ncp_task_hdl_t taskHdl,
	ncp_ncaV2_free_pdu_segments_t *task);		

/*!
 * @fn ncp_st_t ncp_task_ncav2_buffer_alloc(
 *  ncp_task_hdl_t taskHdl,
 * 	ncp_uint32_t size,
 *	void **taskAddr)
 * @brief This API is called to allocate task buffers.   It is equivalent to ncp_task_buffer_alloc,   but faster
 * since the caller provides the task handle,   therefore allowing the RTE to avoid accessing thread local storage
 * in order to aquire the task handle.
 * 
 * @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()  
 * @param[in]        size:     Task Size.
 * @param[in,out]    taskAddr: Aaddress of location wshere the allocated task buffer virtual address will be stored.
 * 
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized 
 * @retval NCP_ST_TASK_ALLOC_REQUIRES_POINTER  task alloc pointer for return val is NULL
 * @retval NCP_ST_TASK_REQUEST_FOR_ZERO_LENGTH_TASK_BUFFER size must be greater than zero
 * @retval NCP_ST_TASK_NO_MALLOC_MEM insufficient memory resources to satisfy request
 *
*/
NCP_API ncp_st_t
ncp_task_ncav2_buffer_alloc (
    ncp_task_hdl_t taskHdl,
	ncp_uint32_t size,
	void **taskAddr);	

/*!
 * @fn ncp_st_t ncp_task_ncav2_buffer_free (
 *    ncp_task_hdl_t taskHdl,
 *	void *taskAddr);	
 * @brief This API is called to free a single task buffer or pduSegment.   It is equivalent to ncp_task_buffer_free,   but faster
 * since the caller provides the task handle,   therefore allowing the RTE to avoid accessing thread local storage
 * in order to aquire the task handle.
 * 
 * @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()  
 * @param[in]    taskAddr: Address of task buffer to be freed.
 * 
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
 * @retval NCP_ST_TASK_INVALID_PARAMETER The taskHdl parameter is NULL
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized 
 * @retval NCP_ST_TASK_ALLOC_REQUIRES_POINTER  task alloc pointer for return val is NULL
 * @retval NCP_ST_TASK_REQUEST_FOR_ZERO_LENGTH_TASK_BUFFER size must be greater than zero
 * @retval NCP_ST_TASK_NO_MALLOC_MEM insufficient memory resources to satisfy request
 * @retval NCP_ST_TASK_SEND_DONE_RECURSION_DETECTED this function was called
 *          from a sendDone callback function.
 *
*/	
NCP_API ncp_st_t
ncp_task_ncav2_buffer_free (
    ncp_task_hdl_t taskHdl,
	void *taskAddr);	
	
/*!
 * @fn ncp_task_ncav2_cpuPool_mutex_disable (
 *    ncp_task_hdl_t taskHdl);
 * @brief This API is called to request exclusive access to a CPU managed task memory pool.   No mutex is required when 
 * allocating of freeing buffers if the pool is used exclusively by a single thread.    This API can substantially increase
 * thread performance.   This API must not be called if multiple threads are privatley sharing the task handle,  since memory
 * pool corruption will occur.
 * 
 * @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()  
 * 
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized 
 * @retval NCP_ST_TASK_POOL_IN_USE The pool is already in use.   Locks cannot be disabled for CPU managed pools used by more than 1 thread.
 *
*/	
NCP_API ncp_st_t
ncp_task_ncav2_cpuPool_mutex_disable(
    ncp_task_hdl_t taskHdl);

/*!
 * @fn ncp_task_ncav2_use_exclusive_allocator(
 *    ncp_task_hdl_t taskHdl);
 * @brief This API is called to request an exclusive mode allocator for the shared pool configured for this thread queue set.   Exclusive mode
 * allocators, if configured for the associated thread queue set,  allow lockless allocations for hw managed shared pools for task handles 
 * created in shared mode.   If no exclusive  mode allocator is configured or free,   then  the task handle will remain associated with the
 * default allocator,   which by definition is exclusive id the task handle create was issued with shared=FALSE,   or shared if the task handle
 * was created with shared=TRUE.  Applications can ignore this error and continue using the default * allocator if that is acceptable.
 * Exclusive mode allocators are freed when the task handle is removed.
 *
 * @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
 *
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_TASK_NO_MME_ALLOCATOR  No exclusive mode allocators are available for this thread queue set.   
 * @retval NCP_ST_TASK_INVALID_PARAMETER The taskHdl parameter is NULL
 *
*/
NCP_API ncp_st_t
ncp_task_ncav2_use_exclusive_allocator(
    ncp_task_hdl_t taskHdl);
  
   
/* ============================================================================================================
 * BEGIN NCA V2 raw API. 
 * ============================================================================================================
 */
   
 /*!
 * @fn ncp_st_t ncp_task_ncav2_raw_recv_queue_bind(
 *      ncp_task_hdl_t           taskHdl,
 *      ncp_uint8_t              ncaQueueId,
 *      ncp_bool_t               shared,
 *      ncp_task_raw_recv_hdl_t *rxHdl);
 *
 * @brief (see ncp_task_raw_recv_queue_bind())
 */
NCP_API ncp_st_t
ncp_task_ncav2_raw_recv_queue_bind(
    ncp_task_hdl_t      taskHdl,
    ncp_uint8_t              ncaQueueId,
    ncp_bool_t               shared,
    ncp_task_raw_recv_hdl_t *rxHdl);

/*!
 * @fn ncp_st_t ncp_task_ncav2_raw_recv_queue_unbind(
 *      ncp_task_hdl_t           taskHdl,
 *      ncp_task_raw_recv_hdl_t  rxHdl);
 *
 * @brief (see ncp_task_raw_recv_queue_unbind())
 */
NCP_API ncp_st_t
ncp_task_ncav2_raw_recv_queue_unbind(
    ncp_task_hdl_t          taskHdl,
    ncp_task_raw_recv_hdl_t rxHdl);

/*!
 * @fn ncp_st_t ncp_task_ncav2_raw_recv(
 *      ncp_task_hdl_t                  taskHdl,
 *      ncp_task_raw_recv_hdl_t         rxHdl,
 *      ncp_uint32_t                    maxNumTasks,
 *      ncp_uint32_t                   *numTasksReceived,
 *      ncp_task_ncaV2_recv_buf_t     **tasks,
 *      void                           *reserved,
 *      ncp_bool_t                      wait);
 *
 * @brief This function is called to receive one or more tasks.
 *        Unlike ncp_task_ncav2_recv(), this function does not refill the NCA
 *        for every buffer received - that responsibility is the user's.
 *        This function does not support receive callback functions or their
 *        arguments, since raw task I/O does not support virtual pipeline
 *        binding.
 * @note  Standard task I/O versions of raw task I/O functions must be mixed
 *        with their raw task I/O counterparts.
 * @note  Standard task I/O threads and raw task I/O threads cannot share
 *        receive queues.
 * @note  The user is responsible for decoding task params in raw task
 *        I/O. The ASE-generated decode function is accessible via the
 *        ncp_vp_task_param_decode_func_get() interface.
 *
 * @param[in] taskHdl: Task handle returned by previous call to
 *              ncp_task_hdl_create().
 * @param[in] rxHdl: raw receive handle from whose bound input queue the
 *              function receives.
 * @param[in] wait: Boolean flag. If set to TRUE, specifies that the call should
 *              wait if necessary until an input task becomes available.
 * @param[in] maxNumTasks: number of tasks to receive.
 * @param[out] numTasksReceived: Pointer to an unsigned integer. The number of
 *              succesfully received tasks is stored in this location.
 * @param[out] tasks: Array of task receive buffer pointers. Every received
 *                  task buffer is stored in this location.
 * @param reserved: reserved for future use. Must be set to NULL.
 *
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_TASK_RECV_QUEUE_EMPTY informative status, no tasks currently available
 * @retval NCP_ST_TASK_TQS_DISABLED the thread queue set is disabled
 */

NCP_API ncp_st_t
ncp_task_ncav2_raw_recv(
    ncp_task_hdl_t              taskHdl,
    ncp_task_raw_recv_hdl_t     rxHdl,
    ncp_uint32_t                maxNumTasks,
    ncp_uint32_t               *numTasksReceived,
    ncp_task_ncaV2_recv_buf_t **tasks,
    void                       *reserved,
    ncp_bool_t                  wait
);

/*!
 * @fn ncp_st_t ncp_task_ncav2_raw_send(
 *      ncp_task_hdl_t                  taskHdl,
 *      ncp_uint32_t                    maxNumTasks,
 *      ncp_uint32_t                   *numTasksSent,
 *      ncp_task_ncav2_send_done_fn_t  *sendDoneFns,
 *      void                          **sendDoneFnArgs,
 *      ncp_task_ncaV2_send_meta_t    **taskMetaData,
 *      ncp_bool_t                      wait);
 *
 * @brief This function is called to send one or more tasks to the task
 *        handle's thread queue set's associated oPCQ.
 * @note  Standard task I/O versions of raw task I/O functions must be mixed
 *        with their raw task I/O counterparts.
 * @note  Standard task I/O threads and raw task I/O threads cannot share
 *        receive queues.
 * @note  Unlike standard task send, the user must set the virtualFlowID
 *        member in each entry in the send meta data array.
 * @note  The user is responsible for encoding task params in raw task
 *        I/O. The ASE-generated encode function is accessible via the
 *        ncp_vp_task_param_encode_func_get() interface.
 *
 * @param[in] taskHdl: Task handle returned by previous call to
 *              ncp_task_hdl_create().
 * @param[in] wait: Boolean flag. If set to TRUE, specifies that the call should
 *              block if necessary until all tasks are placed on the output
 *              queue.
 * @param[in] maxNumTasks: number of tasks to send.
 * @param[in] sendDoneFns: Application provided function pointer array, one
 *              function per task, to be called when the task has been
 *              delivered to the NCA and the buffer can be reused or deleted.
 *              Otherwise, NULL if task I/O module will free the buffer. If the
 *              array pointer is NULL, none of the tasks will have a callback
 *              function. Otherwise, if any individual sendDoneFns element is
 *              NULL, the corresponding send will not have a callback. Refer to
 *              ncp_task_ncav2_send_done_fn_t for more information.
 * @param[in] sendDoneFuncArgs: Array of opaque arguments, one for each task to
 *              be sent, to be included in call to sendDoneFn, if sendDoneFn
 *              provided.
 * @param[in] taskMetaData: Array of send metadata structs.
 *                  task buffer is stored in this location.
 * @param[out] numTasksSent: Pointer to an integer. The number of successfully
 *              sent tasks is stored in this location.
 *
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_INVALID_PARAMETER numTasksSent is NULL.
 * @retval NCP_ST_INVALID_PARAMETER sendDoneFns is non-NULL, but sendDoneFnArgs
    is NULL.
 * @retval NCP_ST_TASK_SEND_NULL_METADATA_PTR  metadata pointer must not be NULL
 * @retval NCP_ST_TASK_SEND_NULL_TASK_PTR  task pointer must not be NULL if dataSize != 0
 * @retval NCP_ST_TASK_SENDDONE_FN_WITH_VP_MANAGED_POOL sendDoneFn is non-NULL
    with a shared pool task.
 * @retval NCP_ST_NOT_IMPLEMENTED sendDoneFn is non-NULL.
 * @retval NCP_ST_INVALID_VALUE ptrCnt in one of the metadata is invalid.
 * @retval NCP_ST_TASK_SEND_QUEUE_FULL  informative status, no room for task in send queue
 * @retval NCP_ST_TASK_BUFFSIZE_TOO_LARGE  task size exceeds memory pool maximum size buffer
 * @retval NCP_ST_TASK_BUFFPOOL_CORRUPTION  internal error,  buffer pool corruption detected
 * @retval NCP_ST_NO_MEMORY  insufficient memory
 * @retval NCP_ST_TASK_CLIENT_FREE_NULLPTR tried to free a null pointer
 * @retval NCP_ST_VPM_INVALID_VP_HDL the vpHdl parameter is not valid
 * @retval NCP_ST_TASK_TQS_DISABLED the thread queue set is disabled
 */

NCP_API ncp_st_t
ncp_task_ncav2_raw_send(
	ncp_task_hdl_t                  taskHdl,
    ncp_uint32_t                    maxNumTasks,
    ncp_uint32_t                   *numTasksSent,
    ncp_task_ncav2_send_done_fn_t  *sendDoneFns,
    void                          **sendDoneFnArgs,
	ncp_task_ncaV2_send_meta_t    **taskMetaData,
	ncp_bool_t                      wait
);
 
/*!
 * @fn ncp_st_t ncp_task_ncav2_raw_nca_refill(
 *      ncp_task_hdl_t               taskHdl,
 *      ncp_uint32_t                 numTaskBuffers,
 *      ncp_uint32_t                *numTaskBuffersRefilled,
 *      void                       **taskBuffers,
 *      ncp_nca_task_block_sizes_t  *taskBufferBlockSizes,
 *      ncp_bool_t                   wait);
 *
 * @brief This function supplies one or more buffers to the NCA. The buffers
 *        can originate from an *_alloc() or a task receive.
 *        If the block size of a buffer is unknown, e.g. if it was acquired
 *        from ncp_task_buffer_alloc(), TASK_BLOCK_SZ_UNKNOWN indicates to the
 *        RTE that it must calculate the block size of this buffer.
 *        This function is only valid for CPU-managed memory pools.
 *        This function returns NCP_ST_SUCCESS if 1 or more buffers are
 *        refilled. The caller must check the value pointed to by
 *        numTaskBuffersRefilled to ensure whether numTaskBuffers buffers
 *        were succesfully refilled.
 *
 * @param[in] taskHdl: Task handle returned by previous call to
 *              ncp_task_hdl_create().
 * @param[in] wait: Boolean flag. If set to TRUE, specifies that the call should
 *              block if necessary until all tasks are placed on the output
 *              queue.
 * @param[in] taskBuffers: an array of task buffer pointers.
 * @param[in] taskBufferBlockSizes: an array of block sizes, one for each buffer
 *              that is to be supplied to the NCA.
 * @param[in] numTaskBuffers: number of task buffers to send to the NCA.
 * @param[out] numTaskBuffersRefilled: Pointer to an integer. The number of
 *              successfully refilled task buffers is stored in this location.
 *
 * @retval NCP_ST_INVALID_PARAMETER taskBuffers, taskBufferBlockSizes, or
 *          numTaskBuffersRefilled is NULL
 * @retval NCP_ST_ERROR the function was called with a task handle that uses
 *          shared pools.
 * @retval NCP_ST_TASK_SEND_QUEUE_FULL  informative status, no room for task in send queue
 * @retval NCP_ST_TASK_TQS_DISABLED the thread queue set is disabled
 */

NCP_API ncp_st_t
ncp_task_ncav2_raw_nca_refill(
    ncp_task_hdl_t               taskHdl,
    ncp_uint32_t                 numTaskBuffers,
    ncp_uint32_t                *numTaskBuffersRefilled,
    void                       **taskBuffers,
    ncp_nca_task_block_sizes_t  *taskBufferBlockSizes,
    ncp_bool_t                   wait
);


/* ============================================================================================================
 * END NCA V2 raw API. 
 * ============================================================================================================
 */

/*!
 * @fn ncp_st_t ncp_task_ncav2_bulk_buffer_alloc(
 *      ncp_task_hdl_t   taskHdl,
 *      ncp_uint32_t     numTaskBuffers,
 *      ncp_uint32_t    *numTaskBuffersAllocated,
 *      ncp_uint32_t    *taskBufferSizes,
 *      void           **taskBuffers,
 *      ncp_bool_t      wait);
 *
 * @brief (refer to ncp_task_bulk_buffer_alloc())
 */

NCP_API ncp_st_t
ncp_task_ncav2_bulk_buffer_alloc(
    ncp_task_hdl_t   taskHdl,
    ncp_uint32_t     numTaskBuffers,
    ncp_uint32_t    *numTaskBuffersAllocated,
    ncp_uint32_t    *taskBufferSizes,
    void           **taskBuffers,
    ncp_bool_t       wait
);

/*!
 * @fn ncp_st_t ncp_task_ncav2_bulk_buffer_free(
 *      ncp_task_hdl_t   taskHdl,
 *      ncp_uint32_t     numTaskBuffers,
 *      ncp_uint32_t    *numTaskBuffersAllocated,
 *      void           **taskBuffers,
 *      ncp_bool_t      wait);
 *
 * @brief (refer to ncp_task_bulk_buffer_free())
 */

NCP_API ncp_st_t
ncp_task_ncav2_bulk_buffer_free(
    ncp_task_hdl_t   taskHdl,
    ncp_uint32_t     numTaskBuffers,
    ncp_uint32_t    *numTaskBuffersFreed,
    void           **taskBuffers,
    ncp_bool_t       wait
);

/*!
 * @fn ncp_st_t ncp_task_ncav2_oPCQ_depth_get(
 *      ncp_task_hdl_t  taskHdl,
 *      ncp_uint16_t   *qDepth);
 *
 * @brief This function returns the depth of the oPCQ associated with
 *          taskHdl's thread queue set.
 *
 * @param[in] taskHdl: Task handle returned by previous call to
 *              ncp_task_hdl_create().
 * @param[out] qDepth: the depth of the oPCQ.
 *
 * @retval NCP_ST_INVALID_PARAMETER qDepth is NULL
 */

NCP_API ncp_st_t
ncp_task_ncav2_oPCQ_depth_get(
    ncp_task_hdl_t  taskHdl,
    ncp_uint16_t   *qDepth);

/*!
 * @fn ncp_st_t ncp_task_ncav2_pool_ID_get(
 *      ncp_task_hdl_t  taskHdl,
 *      ncp_uint8_t    *poolID);
 *
 * @brief (refer to ncp_task_pool_ID_get())
 */

NCP_API ncp_st_t
ncp_task_ncav2_pool_ID_get(
    ncp_task_hdl_t  taskHdl,
    ncp_uint8_t    *poolID);

/*!
 * @fn ncp_st_t ncp_task_ncav2_pool_type_get(
 *      ncp_task_hdl_t        taskHdl,
 *      ncp_task_pool_type_t *poolType);
 *
 * @brief (refer to ncp_task_pool_type_get())
 */

NCP_API ncp_st_t
ncp_task_ncav2_pool_type_get(
    ncp_task_hdl_t   taskHdl,
    ncp_task_pool_type_t *poolType);

/*!
 * @fn ncp_st_t ncp_task_ncav2_block_size_get(
 *      ncp_task_ncaV2_recv_buf_t  *task,
 *      ncp_uint16_t                numBlocks,
 *      ncp_nca_task_block_sizes_t *blockSize);
 *
 * @brief This function returns a list of block sizes, of length equal to
 *          numBlocks, for the memory buffers that this task points to.
 *
 * @param[in] task: pointer to a task buffer
 * @param[in] numBlocks: number of blocks
 * @param[out] blockSize: array of block sizes filled by this function.
 *
 * @retval NCP_ST_INVALID_PARAMETER qDepth is NULL

 */

/*
NCP_API ncp_st_t
ncp_task_ncav2_block_size_get(
    ncp_task_ncaV2_recv_buf_t  *task,
    ncp_uint16_t                numBlocks,
    ncp_nca_task_block_sizes_t *blockSize);
*/

/*!
 * @fn ncp_st_t ncp_task_ncav2_block_size_to_bytes(
 *      ncp_task_hdl_t              taskHdl,
 *      ncp_nca_task_block_sizes_t  pduBlockSize,
 *      ncp_uint32_t               *size);
 *
 * @brief (refer to ncp_task_block_size_to_bytes())
 */

NCP_API ncp_st_t
ncp_task_ncav2_block_size_to_bytes(
    ncp_task_hdl_t              taskHdl,
    ncp_nca_task_block_sizes_t  pduBlockSize,
    ncp_uint32_t               *size);

/*!
 * @fn ncp_st_t ncp_task_ncav2_bytes_to_block_size(
 *      ncp_task_hdl_t              taskHdl,
 *      ncp_uint32_t                size,
 *      ncp_nca_task_block_sizes_t *pduBlockSize);
 *
 * @brief (refer to ncp_task_bytes_to_block_size())
 */

NCP_API ncp_st_t
ncp_task_ncav2_bytes_to_block_size(
    ncp_task_hdl_t              taskHdl,
    ncp_uint32_t                size,
    ncp_nca_task_block_sizes_t *pduBlockSize);

/*!
 * @brief NCP_TASK_NCAV2_BLOCK_SIZE: NCAv2 Task IO macro to return the 2-bit
 *                                   block size of a certain PDU block pointed
 *                                   to by a task receive buffer.
 * @note Refer to the definition of ncp_task_ncaV2_recv_buf_tto see how block
 *       sizes are extracted
 * @param[in] task: Pointer to task receive buffer
 * @param[in] idx: PDU block index. Must be between 0 and 5, inclusive.
 * @retval PDU block size, or TASK_BLOCK_SZ_UNKNOWN if idx is greater than 5.
*/
#ifdef NCP_BIG_ENDIAN
#define NCP_TASK_NCAV2_BLOCK_SIZE(idx, task) \
    (idx > 5) ? TASK_BLOCK_SZ_UNKNOWN : \
    (ncp_nca_task_block_sizes_t)((((ncp_uint32_t *) task)[10] >> idx*2) & 0x3)
#else
#define NCP_TASK_NCAV2_BLOCK_SIZE(idx, task) \
    (idx > 5) ? TASK_BLOCK_SZ_UNKNOWN : \
    (ncp_nca_task_block_sizes_t) \
        ((((ncp_uint32_t *) task)[10] >> (30 - idx*2)) & 0x3)
#endif


   
/* ============================================================================================================
 * End NCA V2 Native APIs.   
 * ============================================================================================================
 */ 
 
 
/* ============= Begin Task I/O Resource Lookup APIs ============ */

/*!
 * @fn ncp_st_t ncp_task_recv_queue_id_to_name(
 *                          ncp_hdl_t ncpHdl, 
 *                          ncp_uint8_t ncaQueueID,
 *                          char        *recvQueueName);
 *
 * @brief This API will map a Nca Receive Queue ID to its name.  
 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to 
 *                  ncp_config
 * @param[in]       ncaQueueID.  The linear ID (0..X) of the NCA receive 
 *                  queue,   where X varies by chip type.
 * @param[in,out]   recvQueueName: pointer to string storage (array) 
 *                  where the NCA Receive Queue name will be copied.  
 *                  The caller should provide adequate storage to hold a  
 *                  maximum sized name,   which can be up to 
 *                  NCP_TASK_MAX_RESOURCE_NAME_LEN characters in length 
 *                  including the null termination character.             
 *
 * @note            This API has been updated to work on resources configured for
 *                  both kernel and user mode,   regardless of the mode (user/kernel)
 *                  that the caller is executing in.   It is therefore necessary to
 *                  check the mode or the resource prior to attmepting to use that
 *                  that resource.   This can be done by calling the ncp_task_tqs_id_get_mode API. 
 *
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
 * @retval NCP_ST_TASK_RECV_QUEUE_ID_NOT_FOUND The NCA Receive Queue ID 
 *          supplied ie either out of range,  or not present in the 
 *          currently loaded ASE configuration.
 * @retval NCP_ST_INVALID_PARAMETER recvQueueName is NULL
*/	
NCP_API ncp_st_t
ncp_task_recv_queue_id_to_name(ncp_hdl_t ncpHdl, 
                           ncp_uint8_t ncaQueueID,
                           char        *recvQueueName);

/*!
 * @fn ncp_st_t ncp_task_recv_queue_name_to_id(
 *                          ncp_hdl_t ncpHdl,
 *                          char *recvQueueName, 
 *                          ncp_uint8_t *p_ncaQueueID);
 *
 * @brief This API will map a Nca Receive Queue name to its ID   
 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to 
 *                  ncp_config
 * @param[in,out]   recvQueueName: pointer to null terminated character
 *                  string containing the NCA Receive Queue name.   The 
 *                  internal Task I/O RX queue state information associated with the 
 *                  currently loaded configuration will be searched
 *                  using this string. The string provided can be up to 
 *                  NCP_TASK_MAX_RESOURCE_NAME_LEN characters in length 
 *                  including the null termination character.  
 * @param[in, out]  p_ncaQueueID.  Pointer to storage where the linear 
 *                  ID (0..X) of the NCA Receive Queue will be returned. 
 *           
 *
 * @note            This API has been updated to work on resources configured for
 *                  both kernel and user mode,   regardless of the mode (user/kernel)
 *                  that the caller is executing in.   It is therefore necessary to
 *                  check the mode or the resource prior to attmepting to use that
 *                  that resource.   This can be done by calling the ncp_task_tqs_id_get_mode API. 
 *
 *
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
 * @retval NCP_ST_TASK_BAD_RXQ_NAME The NCA Receive Queue name is not 
 *         valid.  It is either too short or too long.   
 * @retval NCP_ST_TASK_RECVQUEUE_NAME_NOT_FOUND No receive queue with 
 *         the specified name was found.       
 * @retval NCP_ST_INVALID_PARAMETER p_ncaQueueID is NULL
*/
NCP_API ncp_st_t
ncp_task_recv_queue_name_to_id(ncp_hdl_t ncpHdl,
                           char *recvQueueName, 
                           ncp_uint8_t *p_ncaQueueID);

/*!
 * @fn ncp_st_t ncp_task_recv_queue_get_tqs_id(
 *                          ncp_hdl_t ncpHdl, 
 *                          ncp_uint8_t ncaQueueID, 
 *                          ncp_uint8_t *p_tqsID);
 *
 * @brief This API will map a Nca Receive Queue ID to the ID of the 
 * thread queue of which it is a member.
 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to 
 *                  ncp_config
 * @param[in]       ncaQueueID.  The linear ID (0..X) of the NCA receive 
 *                  queue,   where X varies by chip type.
 * @param[in,out]   p_tqsID: p_ncaQueueID.  Pointer to storage where the 
 *                  ID (0..X) of the NCA thread queue set will be 
 *                  returned.            
 *
 *
 * @note            This API has been updated to work on resources configured for
 *                  both kernel and user mode,   regardless of the mode (user/kernel)
 *                  that the caller is executing in.   It is therefore necessary to
 *                  check the mode or the resource prior to attmepting to use that
 *                  that resource.   This can be done by calling the ncp_task_tqs_id_get_mode API. 
 *
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
 * @retval NCP_ST_TASK_RECV_QUEUE_ID_NOT_FOUND The NCA Receive Queue ID 
 *           supplied ie either out of range,  or not present in the 
 *           currently loaded ASE configuration.
 * @retval NCP_ST_INVALID_PARAMETER p_tqsID is NULL
*/
NCP_API ncp_st_t
ncp_task_recv_queue_get_tqs_id(ncp_hdl_t ncpHdl, 
                           ncp_uint8_t ncaQueueID, 
                           ncp_uint8_t *p_tqsID);

/*!
 * @fn ncp_st_t ncp_task_recv_queue_get_queue_group_id(
 *                          ncp_hdl_t ncpHdl,
 *                          ncp_uint8_t ncaQueueID, 
 *                          ncp_uint8_t *p_grpID); 
 *
 * @brief This API will map a Nca Receive Queue ID to the NCA Queue 
 * Group of which it is a member.
 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to 
 *                  ncp_config
 * @param[in]       ncaQueueID:  The linear ID (0..X) of the NCA Receive 
 *                  Queue,   where X varies by chip type.
 * @param[in,out]   p_grpID:  Pointer to storage where the 
 *                  ID (0..X) of the NCA Queue Group will be 
 *                  returned.                
 *
 *
 * @note            This API has been updated to work on resources configured for
 *                  both kernel and user mode,   regardless of the mode (user/kernel)
 *                  that the caller is executing in.   It is therefore necessary to
 *                  check the mode or the resource prior to attmepting to use that
 *                  that resource.   This can be done by calling the ncp_task_tqs_id_get_mode API. 
 *
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
 * @retval NCP_ST_TASK_RECV_QUEUE_ID_NOT_FOUND The NCA Receive Queue ID 
 *           supplied ie either out of range,  or not present in the 
 *           currently loaded ASE configuration.
 * @retval NCP_ST_INVALID_PARAMETER p_grpID is NULL
*/
NCP_API ncp_st_t
ncp_task_recv_queue_get_queue_group_id(ncp_hdl_t ncpHdl,
                           ncp_uint8_t ncaQueueID, 
                           ncp_uint8_t *p_grpID); 

/*!
 * @fn ncp_st_t ncp_task_tqs_id_to_name(
 *                       ncp_hdl_t ncpHdl, 
 *                       ncp_uint8_t tqsID,
 *                       char        *tqsName);
 *
 *
 * @brief This API will map a Nca Thread Queue Set ID to its name.  
 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to 
 *                  ncp_config
 * @param[in]       tqsID.  The linear ID (0..X) of the NCA Thread Queue 
 *                  Set,   where X varies by chip type.
 * @param[in,out]   tqsName: pointer to string storage (array) 
 *                  where the Thread Queue Set name will be copied.  
 *                  The caller should provide adequate storage to hold a  
 *                  maximum sized name,   which can be up to 
 *                  NCP_TASK_MAX_RESOURCE_NAME_LEN characters in length 
 *                  including the null termination character.               
 *
 *
 * @note            This API has been updated to work on resources configured for
 *                  both kernel and user mode,   regardless of the mode (user/kernel)
 *                  that the caller is executing in.   It is therefore necessary to
 *                  check the mode or the resource prior to attmepting to use that
 *                  that resource.   This can be done by calling the ncp_task_tqs_id_get_mode API. 
 *
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
 * @retval NCP_ST_TASK_TQSID_NOT_FOUND The NCA Thread Queue Set ID 
 *          supplied ie either out of range,  or not present in the 
 *          currently loaded ASE configuration.
 * @retval NCP_ST_INVALID_PARAMETER tqsName is NULL
*/
NCP_API ncp_st_t
ncp_task_tqs_id_to_name(ncp_hdl_t ncpHdl, 
                        ncp_uint8_t tqsID,
                        char        *tqsName);

/*!
 * @fn ncp_st_t ncp_task_tqs_name_to_id(
 *                       ncp_hdl_t ncpHdl, 
 *                       char        *tqsName,
 *                       ncp_uint8_t *p_tqsID);
 *
 * @brief This API will map a Nca Thread Queue Set name to its ID.  
 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to 
 *                  ncp_config
 * @param[in]       tqsName.  pointer to null terminated character
 *                  string containing the NCA Thread Queue Set name.   The 
 *                  internal Task I/O TQS state information associated with the 
 *                  currently loaded configuration will be searched
 *                  using this string. The string provided can be up to 
 *                  NCP_TASK_MAX_RESOURCE_NAME_LEN characters in length 
 *                  including the null termination character.  
 * @param[in,out]   p_tqsID: Pointer to storage where the 
 *                  ID (0..X) of the NCA Thread Queue Set will be 
 *                  returned.          
 *
 * @note            This API has been updated to work on resources configured for
 *                  both kernel and user mode,   regardless of the mode (user/kernel)
 *                  that the caller is executing in.   It is therefore necessary to
 *                  check the mode or the resource prior to attmepting to use that
 *                  that resource.   This can be done by calling the ncp_task_tqs_id_get_mode API. 
 *
 *
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
 * @retval NCP_ST_TASK_TQSNAME_NOT_FOUND The NCA thread queue set name 
 * supplied did not match any thread queue set names in the currently 
 * loaded ASE ocnfiguarion.
 * @retval NCP_ST_TASK_BAD_TQS_NAME The thread queue set name supplied
 *         is either too short or too long.
 * @retval NCP_ST_INVALID_PARAMETER tqsName or p_tqsID is NULL
*/
NCP_API ncp_st_t
ncp_task_tqs_name_to_id(ncp_hdl_t ncpHdl, 
                        char        *tqsName,
                        ncp_uint8_t *p_tqsID);


/*!
 * @fn ncp_task_tqs_id_get_mode(ncp_hdl_t ncpHdl, 
 *                              ncp_uint8_t tqsID,
 *                              ncp_task_tqs_mode_t *pTqsMode);
 *
 * @brief This API will map a Nca Thread Queue Set name to its mode (kernel or user).  
 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to 
 *                  ncp_config
 * @param[in]       tqsID.  The linear ID (0..X) of the NCA Thread Queue 
 *                  Set,   where X varies by chip type.
 * @param[in,out]   pTqsMode: pointer to enum where the thread queue set's mode will be stored.           
 *
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
 * @retval NCP_ST_TASK_TQSID_NOT_FOUND The NCA Thread Queue Set ID 
 *          supplied ie either out of range,  or not present in the 
 *          currently loaded ASE configuration.
 * @retval NCP_ST_INVALID_PARAMETER tqsName is NULL
*/
NCP_API ncp_st_t
ncp_task_tqs_id_get_mode(ncp_hdl_t ncpHdl, 
                         ncp_uint8_t tqsID,
                         ncp_task_tqs_mode_t *pTqsMode);
                         
/*!
 * @fn ncp_st_t ncp_task_tqs_get_queue_group_id(
 *                       ncp_hdl_t ncpHdl,
 *                       ncp_uint8_t tqsID,
 *                       ncp_uint8_t *p_grpID);
 *
 * @brief This API will map a Nca Thread Queue Set ID to the NCA Queue Group ID of which it is a member.
 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to 
 *                  ncp_config
 * @param[in]       tqsID.  The linear ID (0..X) of the NCA Thread Queue 
 *                  Set,   where X varies by chip type.
 * @param[in,out]   p_grpID: pointer to storage where the NCA Queue 
 *                  Group ID will be returned.
 *
 *
 * @note            This API has been updated to work on resources configured for
 *                  both kernel and user mode,   regardless of the mode (user/kernel)
 *                  that the caller is executing in.   It is therefore necessary to
 *                  check the mode or the resource prior to attmepting to use that
 *                  that resource.   This can be done by calling the ncp_task_tqs_id_get_mode API. 
 *
 *
 *
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
 * @retval NCP_ST_TASK_TQSID_NOT_FOUND The NCA Thread Queue Set ID 
 *           supplied is either out of range,  or not present in the 
 *           currently loaded ASE configuration.
 * @retval NCP_ST_INVALID_PARAMETER p_grpID is NULL
*/
NCP_API ncp_st_t
ncp_task_tqs_get_queue_group_id(ncp_hdl_t ncpHdl,
                        ncp_uint8_t tqsID,
                        ncp_uint8_t *p_grpID);

/*!
 * @fn ncp_st_t ncp_task_logical_queue_is_ordered(
 *          ncp_hdl_t    ncpHdl,
 *          ncp_uint8_t  qID,
 *          ncp_bool_t  *p_isOrdered);
 *
 * @brief This function determines whether a logical queue is ordered.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config.
 * @param[in] qId: the logical queue ID.
 * @param[out] p_isOrdered: TRUE if the logical queue is ordered, FALSE
 *      otherwise.
 *
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid.
 * @retval NCP_ST_INVALID_PARAMETER isOrdered is NULL.
 * @retval NCP_ST_INVALID_PARAMETER qId is not a valid logical queue ID.
 *
 */
NCP_API ncp_st_t
ncp_task_logical_queue_is_ordered(
    ncp_hdl_t    ncpHdl,
    ncp_uint8_t  qId,
    ncp_bool_t  *p_isOrdered);

/*!
 * @fn ncp_st_t ncp_task_logical_queue_name_get(
 *          ncp_hdl_t    ncpHdl,
 *          ncp_uint8_t  qID,
 *          char        *name);
 *
 * @brief This function returns the name of a logical queue.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config.
 * @param[in] qId: the logical queue ID.
 * @param[out] name: A pointer to the name of the logical queue.
 *
 *
 * @note            This API has been updated to work on resources configured for
 *                  both kernel and user mode,   regardless of the mode (user/kernel)
 *                  that the caller is executing in.   It is therefore necessary to
 *                  check the mode or the resource prior to attmepting to use that
 *                  that resource.   This can be done by calling the ncp_task_tqs_id_get_mode API. 
 *
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid.
 * @retval NCP_ST_INVALID_PARAMETER name is NULL.
 * @retval NCP_ST_INVALID_PARAMETER qId is not a valid logical queue ID.
 * @retval NCP_ST_TASK_LOGICAL_QUEUE_NOT_FOUND no logical queue was configured
 *          for the given qId.
 *
 */
NCP_API ncp_st_t
ncp_task_logical_queue_name_get(
    ncp_hdl_t    ncpHdl,
    ncp_uint8_t  qId,
    char        *name);

/*!
 * @fn ncp_st_t ncp_task_recv_queue_logical_queue_id_get(
 *          ncp_hdl_t    ncpHdl,
 *          ncp_uint8_t  qID,
 *          ncp_uint8_t *p_logicalQueue);
 *
 * @brief This function returns the ID of a logical queue of which a given
 *          receive queue is a member.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config.
 * @param[in] qId: the receive queue ID.
 * @param[out] p_logicalQueue: A pointer to the ID of the logical queue.
 *
 *
 * @note            This API has been updated to work on resources configured for
 *                  both kernel and user mode,   regardless of the mode (user/kernel)
 *                  that the caller is executing in.   It is therefore necessary to
 *                  check the mode or the resource prior to attmepting to use that
 *                  that resource.   This can be done by calling the ncp_task_tqs_id_get_mode API. 
 *
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid.
 * @retval NCP_ST_INVALID_PARAMETER p_logicalQueue is NULL.
 * @retval NCP_ST_RECV_QUEUE_ID_NOT_FOUND the qId is not a valid receive
 *          queue ID.
 * @retval NCP_ST_RECV_QUEUE_ID_NOT_FOUND the receive queue indicated by
 *          qId is not configured.
 *
 */
NCP_API ncp_st_t
ncp_task_recv_queue_logical_queue_id_get(
    ncp_hdl_t    ncpHdl,
    ncp_uint8_t  qId,
    ncp_uint8_t *p_logicalQueue);

/*!
 * @fn ncp_st_t ncp_task_logical_queue_name_to_id(
 *          ncp_hdl_t    ncpHdl,
 *          char        *name,
 *          ncp_uint8_t *logicalQueueId);
 *
 * @brief This function returns the ID of a logical queue, given its name.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config.
 * @param[in] name: the logical queue name.
 * @param[out] logicalQueueId: A pointer to the ID of the logical queue.
 *
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid.
 * @retval NCP_ST_INVALID_PARAMETER name is NULL.
 * @retval NCP_ST_INVALID_PARAMETER p_logicalQueue is NULL.
 * @retval NCP_ST_TASK_BAD_LOGICAL_QUEUE_NAME name is an empty string or
 *          exceeds the maximum length.
 * @retval NCP_ST_TASK_LOGICAL_QUEUE_NAME_NOT_FOUND No logical was found with
 *          that name.
 *
 */
NCP_API ncp_st_t
ncp_task_logical_queue_name_to_id(
    ncp_hdl_t    ncpHdl,
    char        *name,
    ncp_uint8_t *logicalQueueId);

/*!
 * @fn ncp_st_t ncp_task_recv_queue_wrrWeight_get(
 *          ncp_hdl_t     ncpHdl,
 *          ncp_uint8_t   qID,
 *          ncp_uint32_t *p_wrr);
 *
 * @brief This function returns the round-robin weight of a receive queue.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config.
 * @param[in] qID: the receive queue ID.
 * @param[out] p_wrr: A pointer to the weight.
 *
 *
 * @note            This API has been updated to work on resources configured for
 *                  both kernel and user mode,   regardless of the mode (user/kernel)
 *                  that the caller is executing in.   It is therefore necessary to
 *                  check the mode or the resource prior to attmepting to use that
 *                  that resource.   This can be done by calling the ncp_task_tqs_id_get_mode API. 
 *
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid.
 * @retval NCP_ST_INVALID_PARAMETER p_wrr is NULL.
 * @retval NCP_ST_TASK_RECV_QUEUE_ID_NOT_FOUND The NCA Receive Queue ID 
 *           supplied ie either out of range,  or not present in the 
 *           currently loaded ASE configuration.
 *
 */
NCP_API ncp_st_t
ncp_task_recv_queue_wrrWeight_get(
    ncp_hdl_t     ncpHdl,
    ncp_uint8_t   qId,
    ncp_uint32_t *p_wrr);

/*!
 * @fn ncp_st_t ncp_task_recv_queue_task_completion_mode_get(
 *          ncp_hdl_t                   ncpHdl,
 *          ncp_uint8_t                 qID,
 *          ncp_task_completion_mode_t *p_tcMode);
 *
 * @brief This function returns the task completion mode of a receive queue.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config.
 * @param[in] qID: the receive queue ID.
 * @param[out] p_tcMode: A pointer to the mode.
 *
 *
 * @note            This API has been updated to work on resources configured for
 *                  both kernel and user mode,   regardless of the mode (user/kernel)
 *                  that the caller is executing in.   It is therefore necessary to
 *                  check the mode or the resource prior to attmepting to use that
 *                  that resource.   This can be done by calling the ncp_task_tqs_id_get_mode API. 
 *
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid.
 * @retval NCP_ST_INVALID_PARAMETER p_tcMode is NULL.
 * @retval NCP_ST_TASK_RECV_QUEUE_ID_NOT_FOUND The NCA Receive Queue ID 
 *           supplied ie either out of range,  or not present in the 
 *           currently loaded ASE configuration.
 *
 */
NCP_API ncp_st_t 
ncp_task_recv_queue_task_completion_mode_get(
    ncp_hdl_t                   ncpHdl,
    ncp_uint8_t                 qId,
    ncp_task_completion_mode_t *p_tcMode);

/* ============= END Task I/O Resource Lookup APIs ============ */

/* ============= BEGIN Task I/O TQS enable/disable/status APIs ============ */

/*!
 * @fn ncp_st_t ncp_task_tqs_is_enabled(
 *                       ncp_hdl_t ncpHdl,
 *                       ncp_uint8_t tqsID,
 *                       ncp_bool_t *pStatus);
 *
 * @brief This API will map a Nca Thread Queue Set ID to the NCA Queue Group ID of which it is a member.
 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to 
 *                  ncp_config
 * @param[in]       tqsID.  The linear ID (0..X) of the NCA Thread Queue 
 *                  Set,   where X varies by chip type.
 * @param[in,out]   pStatus: pointer to storage where the NCA TQS status will be returned if API
 *                  returns success;  TRUE if TQS is enabled,   FALSE if disabled.
 *
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
 * @retval NCP_ST_TASK_TQSID_NOT_FOUND The NCA Thread Queue Set ID 
 *           supplied is either out of range,  or not present in the 
 *           currently loaded ASE configuration.
 * @retval NCP_ST_INVALID_PARAMETER pStatus is NULL
*/
NCP_API ncp_st_t
ncp_task_tqs_is_enabled(ncp_hdl_t ncpHdl,
                        ncp_uint8_t tqsID,
                        ncp_bool_t  *pStatus);
                        
/*!
 * @fn ncp_st_t ncp_task_tqs_disable(
 *                      ncp_hdl_t ncpHdl,
 *                      ncp_uint8_t tqsID);
 *
 * @brief This API will disable the specified TQS.   While a TQS is disabled,   attempts
 * to create new task handles to that TQS will be disallowed,   and similarly any atempt to 
 * send or receive tasks will result in an error.   Threads currently blocked pending an interrupt
 * for a queue contained in this TQS will be unblocked and completed with the NCP_ST_TASK_TQS_DISABLED
 * status code.
 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to 
 *                  ncp_config
 * @param[in]       tqsID.  The linear ID (0..X) of the NCA Thread Queue 
 *                  Set,   where X varies by chip type.
 *
 *
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
 * @retval NCP_ST_TASK_TQSID_NOT_FOUND The NCA Thread Queue Set ID 
 *           supplied is either out of range,  or not present in the 
 *           currently loaded ASE configuration.
*/
NCP_API ncp_st_t
ncp_task_tqs_disable(ncp_hdl_t ncpHdl,
                     ncp_uint8_t tqsID);

/*!
 * @fn ncp_st_t ncp_task_tqs_enable(
 *                      ncp_hdl_t ncpHdl,
 *                      ncp_uint8_t tqsID);
 *
 * @brief This API will enable the specified TQS.   All configured TQSets are enabled
 * by default at startup,   but can be explicitly disabled by using the ncp_task_tqs_disable API.
 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to 
 *                  ncp_config
 * @param[in]       tqsID.  The linear ID (0..X) of the NCA Thread Queue 
 *                  Set,   where X varies by chip type.
 *
 *
 * @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
 * @retval NCP_ST_TASK_TQSID_NOT_FOUND The NCA Thread Queue Set ID 
 *           supplied is either out of range,  or not present in the 
 *           currently loaded ASE configuration.
*/
NCP_API ncp_st_t
ncp_task_tqs_enable(ncp_hdl_t ncpHdl,
                    ncp_uint8_t tqsID);


/* ============= END Task I/O TQS enable/disable/status APIs ============ */

/* ============= END Task I/O Wait Profile APIs and Structs ============ */

/*! 
 *  @brief ncp_task_api_class_t: an enum for the wait profile classes.
*/
typedef enum {
NCP_TASK_API_CLASS_RECV=0,
NCP_TASK_API_CLASS_RECV_QUEUE_SELECT,
NCP_TASK_API_CLASS_SEND,
NCP_TASK_API_CLASS_ALLOC,
NCP_TASK_API_CLASS_FREE /* Must be last! */
} ncp_task_api_class_t;

/*! 
 *  @brief ncp_task_poll_type_t: an enum for the wait profile polling types.
*/
typedef enum {
NCP_TASK_POLL_TYPE_SLEEP_POLL=0,
NCP_TASK_POLL_TYPE_HARD_POLL
} ncp_task_poll_type_t;

/*! 
 *  @brief ncp_task_wait_profile_type_t: an enum for the wait profile types.
*/
typedef enum {
NCP_TASK_WAIT_ISR=0,
NCP_TASK_WAIT_WFI,     /* Valid only for receive API(s),  and only for AXM5xxx device accessed from ARM core(s). */
NCP_TASK_WAIT_TIMEOUT
} ncp_task_wait_profile_type_t;


/*!
 * @fn ncp_st_t ncp_task_set_wait_profile(
 *                         ncp_task_hdl_t              taskHdl,
 *                         ncp_task_api_class_t          api_class,
 *                         ncp_task_wait_profile_type_t  wait_profile,
 *                         ncp_uint32_t                  poll_timeout_value,  
 *                         ncp_task_poll_type_t          poll_type,
 *                         ncp_uint32_t                  sleep_poll_value);
 *
 * @brief This API is used to override the default "blocking mode" behavior associated with 
 * task send,   receive,   alloc,   and free APIs.
 *
 * @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
 * @param[in] api_class: Any of the enum members of the type ncp_task_api_class_t.   This parameter 
 *                       describes which API class (send, receive, ....) the user defined wait profile will be 
 *                       applied to.   Note that not all behaviors are valid for all APIs.   Additionally,   some
 *                       behaviors are restricted to certain hardware platforms (i.e. AXM55xx device accessed from ARM core(s).
 * @param[in] wait_profile : This API allows threads to override the default wait semantics of Nca Task I/O APIs.
 *                       This API can be used to define the behavior when send, receive, or receive queue select APIs are called with wait==TRUE and a condition is encountered 
 *                       where the API would block.   If wait==FALSE,   then the wait profile is not executed,   and the application will immediately return with an appropriate 
 *                       status if the API cannot be completed.
 *
 *                       This API can be used to define the behavior for alloc and free APIs when a buffer is not available,   or when a free cannot be completed due to
 *                       insufficient space in the output pcq.
 *
 *                       NCP_TASK_WAIT_ISR is valid for recevie,  send,  and receive queue select APIs.
 *                       This wait profile will wait for a hardware generated interrupt that signals that the wait condition has
 *                       been remedied,   and that the queue is no longer full/empty.    The API will not return until the condition
 *                       no longer exists,   or a shutdown is requested due to the TQS being disabled.
 *
 *                       NCP_TASK_WAIT_WFI is valid only for receive APIs and only when the RTE us executing on the local ARM core(s) of a AXM55XX device.
 *                       NCP_TASK_WAIT_WFI is similar to WAIT_ISR,   except that the processor is put into a low power state
 *                       while waiting for the hardware interrupt.   No other threads,  whether application or system will execute
 *                       while the processor is in low power state.   It is the application responsibility to ensure that interrupt
 *                       steering has been set up,   and that the executing application thread is executing on the same core that the interrupt will be delivered 
 *                       to (interrupt affinity ).   It is not valid to mix NCP_TASK_WAIT_WFI and NCP_TASK_WAIT_ISR on the same core,  and additionally it is expected 
 *                       that NCP_TASK_WAIT_WFI will typically be used only when a single thread is receiving on any particular core.
 *
 *                       NCP_TASK_WAIT_TIMEOUT is used to poll the interface,   rather whan wait for an interrupt.   The poll_timeout
 *                       and poll_type will be used to control how to poll and how long to poll before returning to the caller.
 *
 * @param[in] poll_timeout_value : Units are Microsends.  This parameter determines how long to poll before either returning to the application (NCP_TASK_WAIT_TIMEOUT),
 *                       or before entering the kernel to wait for an interrupt (WAIT_ISR or NCP_TASK_WAIT_WFI).   A value of -1 
 *                       means poll forever.    The poll_type parameter is used to determine how to poll (hard vs sleep).                                 
 * @param[in] poll_type: Sets the poll method to be performed by the RTE.   NCP_TASK_POLL_TYPE_HARD_POLL will cause the RTE to
 *                       poll the interface repeatedly without performing any operations to specifically relinquish the CPU so that
 *                       other threads can be scheduled.   The poll type NCP_TASK_POLL_TYPE_SLEEP_POLL will cause the RTE to 
 *                       call sleep after each poll.   For most operating systems,   this will allow other threads to be scheduled.
 * @param[in] sleep_poll_value:  Units are microseconds.  If NCP_TASK_POLL_TYPE_SLEEP_POLL was specified,   then this parameter defines the amout of time
 *                       to sleep after each non productive poll.   For most operating systems,   a value of zero will result in 
 *                       scheduling other threads of equal or higher priority.                        
 * 
 * @note:                WAIT_ISR with poll_timeout==0 (no polling) is the default behavior for send, receive,   and receive queue select APIs when a queue 
 *                       full (send) or empty (recv) condition is encountered.  
 * @note:                WAIT_TIMEOUT and poll_timeout==0 (no polling) is the default behavior for all alloc and free APIs.
 *
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured,  or the application has not attached to the configuration.
 * @retval NCP_ST_INVALID_HANDLE the taskHdl provided is not valid
 * @retval NCP_ST_INVALID_VALUE One or more input parameters are invalid.
*/
ncp_st_t
ncp_task_set_wait_profile(ncp_task_hdl_t                taskHdl,
                          ncp_task_api_class_t          api_class,
                          ncp_task_wait_profile_type_t  wait_profile,
                          ncp_uint32_t                  poll_timeout_value,  /* 0 -> no polling, -1 -> poll forever */
                          ncp_task_poll_type_t          poll_type,
                          ncp_uint32_t                  sleep_poll_value);


/* ============= END Task I/O Wait Profile APIs and Structs ============ */
                                 
#ifdef __cplusplus
}
#endif

#endif

/*!
 * @}
 */

