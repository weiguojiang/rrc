/**************************************************************************
 **                                                                       *
 **                           Intel CONFIDENTIAL                            *
 **                           PROPRIETARY NOTE                            *
 **                                                                       *
 **    This software contains information confidential and proprietary    *
 **    to Intel Corporation.  It shall not be reproduced in whole or in     *
 **    part, or transferred to other documents, or disclosed to third     *
 **    parties, or used for any purpose other than that for which it was  *
 **    obtained, without the prior written consent of Intel Corporation.    *
 **    (c) 2008-2014, Intel Corporation.  All rights reserved.  *
 **                                                                       *
 **
 **  
 **************************************************************************/

/*! @file      ncp_ptn.h                                                  */

/*! 
 *  @defgroup _ptn_Pattern Pattern
 *  @brief
 *  The Pattern APIs provide high-level control of the classification functions of the NCP device. 
 *  @details
 *  Pattern APIs are used to manage the various types of FPL tree constructs at runtime. They are
 *  divided into distinct sections
 *****************************************************************************************************/



#ifndef _NCP_PATTERN_H_
#define _NCP_PATTERN_H_

#ifndef SWIG
#ifdef __cplusplus
extern "C" { 
#endif /* #ifdef __cplusplus */

#include "agen.h"
#else

%header
%{
#include "agen.h"
#include "ncp_ptn.h"
%}

NCPTCL_SETUP();

NCPTCL_W_EXCEPTIONS();

#endif /* #ifdef SWIG */

/*!
 * @ingroup _ptn_Pattern
 * @enum ncp_ptn_action_type_t
 * Types of actions at the end of a tree rule
 */
typedef enum
{
    ncp_ptn_action_type_return,          /*!< Return a value (24-bits) */
    ncp_ptn_action_type_goto,            /*!< Goto a function (12-bits of function id) */
    ncp_ptn_action_type_unknown,         /*!< Invalid. Can only occuer in retrieving patterns using
                                          * list_ptns and an error occurs */
    ncp_ptn_action_type_return_mask,     /*!< Return a value (24-bits) with a mask indicating which 
                                          * nibbles to not change (top 8-bits). This is a special return
                                          * type which should be used only with the #ncp_ptn_learn and
                                          * #ncp_ptn_learn_any APIs. Of these top 8 bits, the bottom
                                          * 6 bits are used as a mask for each nibble of the 24-bit return
                                          * value to indicate which nibble to not change in a modification
                                          * ( bit value 1 means the nibble from the old value will be used
                                          * and the nibble in the new value ignored). For more information,
                                          * refer to the documentation. 
                                          * Currently, it is not defined what the behavior will be on using
                                          * this type for other APIs which take an #ncp_ptn_action_t 
                                          * This type is not returned in list_ptns since it is only
                                          * an indication to the API of how to setup the action. */
    ncp_ptn_action_type_return_vreturn   /*!< All trees in FPL return a total of 48 bits (accessed
                                          * in the program as the real handle ($) and virtual handle (@).
                                          * Generally, the application only specifies the real handle
                                          * and for certain types of trees, the runtime software uses
                                          * the virtual handle. This type allows the application to
                                          * specify both the real and virtual return values. This type
                                          * is valid for all trees, except for those lpm trees which
                                          * take part as a source tree in an OVTree or UVTree (since the
                                          * software assigns the virtual handle for patterns in
                                          * such trees). In those cases, the API will return an 
                                          * agen_invalid_action. The application needs to be consistent in
                                          * using the same action type for all dynamic learns/unlearns
                                          * This type is not returned in list_ptns since it is only
                                          * an indication to the API of how to setup the action. */
} ncp_ptn_action_type_t;


/*!
 * @ingroup _ptn_Pattern
 * @struct ncp_ptn_action_t
 * @brief Definition of an action
 * @details
 * If the action type is a return, the value is the return value (bottom 24-bits).
 * If the action type is a goto, the value is the function id (bottom 12-bits).
 * If the action type is a return_mask, the value (bottom 24-bits) is the return 
 * value with the top 8-bits being the mask indicating which nibbles to not 
 * change. Refer to the documentation for more info on this very special type.
 */
typedef struct
{
    ncp_ptn_action_type_t            type; /*!< action type */
    ncp_uint32_t                     value;/*!< return value */
    ncp_uint32_t                     vvalue;/*!< virtual return value */
} ncp_ptn_action_t;


#define MAX_WILDCARD_BITS       1023
/*!
 * @ingroup _ptn_Pattern
 * @struct ncp_ptn_t
 * @brief Definition of a pattern
 * @details
 * A pattern consists of a set of data bits followed by some don't care (wildcard) bits. For example,
 * an Ipv4 subnet of 10.10.10.* is a pattern which has 24 data bits and 8 wild card bits.
 * In this structure, the data is stored as an array of 32-bit words pointed to by the "data" field
 * and right justified. For example, a MAC address of 11-22-33-44-55-66 is stored as follows
 *    data[0] = 0x00001122
 *    data[1] = 0x33445566
 * The noDataBits would be set to 48 and noWildCardBits would be set to 0
 */
typedef struct
{
    ncp_uint32_t                    *data;/*!< Pattern */
    ncp_uint32_t                     noDataBits;/*!< Number of bits */
    ncp_uint32_t                     noWildCardBits;/*!< Number of wildcards */
} ncp_ptn_t;


/*!
 * @ingroup _ptn_Pattern
 * @struct ncp_vptn_t
 * @brief Definition of a virtual pattern. 
 * @details
 * A virtual pattern consists of a tree id and a pattern for that tree
 */
typedef struct
{
    ncp_uint32_t                     treeId;/*!< Tree id */
    ncp_ptn_t                        ptn;/*!< Pattern */
} ncp_vptn_t;


/*!
 * @ingroup _ptn_Pattern
 * @struct ncp_rptn_t
 * @brief A range structure
 * @details
 * noBits defines the width. The beginValue and endValue define the inclusive range and point to an array of
 * data words. The data itself is organized right justified starting from the 0th word, just like #ncp_ptn_t
 * For example, a MAC subnet of 11-22-33-44-55-** is represented with
 *    noBits = 48
 *    beginValue[0] = 0x1122 beginValue[1] = 0x33445500
 *    endValue[0] = 0x1122 endValue[1] = 0x334455ff
 */
typedef struct
{
    ncp_uint32_t                noBits;         /*!< Number of bits in the range */
    ncp_uint32_t*               beginValue;     /*!< First value of the range */
    ncp_uint32_t*               endValue;       /*!< Last value of the range */
} ncp_rptn_t;

/*!
 * @ingroup _ptn_Pattern
 * @struct ncp_ptn_a_mem_stats_t
 * @brief Statistics for a single logical memory. 
 * @details
 * It contains the memory's minimum and maximum logical
 * addresses and also the high water mark. Memory is allocated and freed as blocks of 1, 2, 4 or 8
 * instructions (with on the fly defragmentation) and the xsUsed and xsFree indicate the state of 
 * fragmentation in the memory.
 */
typedef struct
{
    ncp_uint32_t                     minAddr;/*!< Minimum Address */
    ncp_uint32_t                     maxAddr;/*!< Maximum Address */
    ncp_uint32_t                     highWater;/*!< High water mark */
    ncp_uint32_t                     memUsed;/*!< Memory used */
    ncp_uint32_t                     x8sUsed;/*!< Number of 8-instruction blocks used */
    ncp_uint32_t                     x8sFree;/*!< Number of 8-instruction blocks on the free list */
    ncp_uint32_t                     x4sUsed;/*!< Number of 4-instruction blocks used */
    ncp_uint32_t                     x4sFree;/*!< Number of 4-instruction blocks on the free list */
    ncp_uint32_t                     x2sUsed;/*!< Number of 2-instruction blocks used */
    ncp_uint32_t                     x2sFree;/*!< Number of 2-instruction blocks on the free list */
    ncp_uint32_t                     x1sUsed;/*!< Number of 1-instruction blocks used */
    ncp_uint32_t                     x1sFree;/*!< Number of 1-instruction blocks on the free list */
} ncp_ptn_a_mem_stats_t;

/*!
 * @ingroup _ptn_Pattern
 * @struct ncp_ptn_mem_stats_t
 * @brief Memory statistics structure.
 * @details
 * This structure encapsulates the statistics for all the four logical memories
 */
typedef struct
{
    ncp_ptn_a_mem_stats_t            flowMem;/*!< Flow Memory Statistics */
    ncp_ptn_a_mem_stats_t            microMem;/*!< Micro Root Memory Statistics*/
    ncp_ptn_a_mem_stats_t            rootMem;/*!< Root Memory Statistics */
    ncp_ptn_a_mem_stats_t            progMem;/*!< Program Memory Statistics */
} ncp_ptn_mem_stats_t;


/*!
 * @ingroup _ptn_Pattern
 * @struct ncp_ptn_fn_stats_t
 * @brief Statistics for each tree function. 
 * @details
 * These statistics are on a per tree function
 */
typedef struct
{
    ncp_uint32_t                      memUsed;/*!< Memory Used */
    ncp_uint32_t                      rootMemUsed;/*!< Root memory used (out of memUsed) */
    ncp_uint32_t                      noLearns;/*!< Number of Learns */
    ncp_uint32_t                      noUnlearns;/*!< Number of Unlearns */
    ncp_uint32_t                      noWrites;/*!< Number of Writes */
    ncp_uint32_t                      initialTableSize;/*!< Initial Table Size*/
    char*                             name;/*!< Tree Function. This is a pointer to internal memory and
                                            * should not be freed by the caller */
} ncp_ptn_fn_stats_t;


/*!
 * @ingroup _ptn_Pattern
 * @enum ncp_ptn_cb_return_t
 * @brief Application callback return codes
 * @details
 * Some operations such as compaction and checking program memory are expensive operations and may
 * consume a significant amount of time. These operations need to be interruptible where the application
 * should be able to abort the operation in the middle to perhaps perform other higher priority
 * tasks. These type of expensive operations have new APIs through which the application can specify a
 * callback function which gets called at regular stages during the operation.
 * This callback function returns with an application status code which tells the operation how to 
 * proceed. If this causes the operation to abort, control then returns to the application.
 */
#ifndef SWIG
typedef enum
{
    ncp_ptn_cb_return_ok, /*!< Operation can proceed */
    ncp_ptn_cb_return_abort, /*!< Operation needs to abort as soon as possible */
    ncp_ptn_cb_return_abort_if_context_change /*!< Some context has changed and operation needs to
                                               * verify the context. This code is specific to a callback
                                               * during tree compaction. Now, application can perform 
                                               * simple learns/unlearns within the  callback while a tree
                                               * is being compacted. If any such operations are done,
                                               * application needs to return the code abort_if_context_change.
                                               * This causes the tree compaction to know that something has
                                               * changed and to determine if this is a recoverable change.
                                               * If so, compaction continues. If it is a non-recoverable
                                               * change (the path to the current compaction point changed),
                                               * then compaction is aborted. Note that this code is only
                                               * valid for tree compaction. All other operations which
                                               * support callbacks will treat this as an abort code. */
} ncp_ptn_cb_return_t;
#endif /* #ifndef SWIG */

/*!
 * @ingroup _ptn_Pattern
 * @typedef ncp_ptn_cb_fn_t
 * @brief Callback function declaration
 * @param[in] rock Application specified opaque value
 * @return #ncp_ptn_cb_return_t
 */
#ifndef SWIG
typedef ncp_ptn_cb_return_t (*ncp_ptn_cb_fn_t)(void *rock);
#endif /* #ifndef SWIG */

/*!
 * @ingroup _ptn_Pattern
 * @typedef ncp_ptn_list_ptns_fn_t
 * @brief Callback function for list pattern functions
 * @details
 * The list_ptns API is used to list all the patterns in a tree. The application specified callback
 * is invoked for each pattern. Note that the same pattern (if subnet) can be returned multiple times
 * in this callback since this is simply a tree walk operation and in an LPM, a subnet can be
 * represented at multiple nodes. It is up to the application to eliminate duplicates.
 * @param[in] rock Application specified callback
 * @param[in] treeId The id of the tree
 * @param[in] ptn The pattern
 * @param[in] action The action for the pattern
 * @return void
 */
#ifndef SWIG
typedef void (*ncp_ptn_list_ptns_fn_t)(void *rock, ncp_uint32_t treeId, 
                                   ncp_ptn_t *ptn, ncp_ptn_action_t *action);
#endif /* #ifndef SWIG */

/*!
 * @ingroup _ptn_Pattern
 * @typedef ncp_ptn_list_vrules_fn_t
 * @brief Callback function for list virtual pattern functions
 * @details
 * The list_vrules API is used to list all the vrules in an OVTREE, OTREE or OTREESET
 * @param[in] rock Application specified callback
 * @param[in] treeId The id of the tree
 * @param[in] vruleidx The index of the rule
 * @param[in] novptns The number of virtual patterns in the rule
 * @param[in] vptns An array of virtual patterns
 * @param[in] action The action for the rule
 * @return void
 */
#ifndef SWIG
typedef void (*ncp_ptn_list_vrules_fn_t)(void *rock, ncp_uint32_t ovtreeId,
                                        ncp_uint32_t vruleidx,
                                        ncp_uint32_t novptns, ncp_vptn_t *vptns,
                                        ncp_ptn_action_t *action);
#endif /* #ifndef SWIG */

/*!
 * @ingroup _ptn_Pattern
 * @struct ncp_ptn_module_stats_t
 * @brief Module Statistics
 */
#ifndef SWIG
typedef struct
{
    char                *name;/*!< Module name */
    ncp_uint32_t         size;/*!< Module size */
    ncp_bool_t           inFlowMemory;/*!< Flow Memory Used */
    ncp_bool_t           isRootModule;/*!< Root Module*/
    ncp_uint32_t         noFunctions;/*!< Number of functions */
    char                **functions;/*!< Function names */
} ncp_ptn_module_stats_t;
#endif /* #ifndef SWIG */

/*!
 * @ingroup _ptn_Pattern
 * @typedef ncp_ptn_module_stats_fn_t
 * @brief Callback function declaration for module statistics
 * @param[in] rock Application specified callback
 * @param[in] stats The module statistics returned in #ncp_ptn_module_stats_t
 * @return void
 */
#ifndef SWIG
typedef void (*ncp_ptn_module_stats_fn_t)(void *rock, ncp_ptn_module_stats_t *stats);
#endif /* #ifndef SWIG */

/*!
 * @internal
 * @ingroup _ptn_Pattern
 * @brief Definition of an extended action
 * @details
 * Here, we define an ncp_ptn_eaction_t structure. This structure contains
 * the handle, virtual handle, some opaque attributes (known only to the
 * code) and a memory address. The ncp_ptn_list_ptns_any_eaction API allows
 * the application to dump the pattern(s) in a tree with the eaction_t
 * structure (as opposed to the ncp_ptn_list_ptns_any which returns the
 * ncp_ptn_action_t structure).
 * At startup time, the application would retrieve the eaction_t structures
 * for each of the patterns in the tree it is interested in (these patterns
 * are expected to be specific patterns; if it is a subnet, there may be
 * multiple eaction_t structures).
 * When a real-time change needs to be done, the application would modify
 * the handle and virtual handle in the eaction_t structure and call the
 * ncp_ptn_modify_eaction_hw() to propagate this change to the hardware
 * memory.
 */
typedef struct
{
    ncp_uint32_t         value;          /* 24-bit handle */
    ncp_uint32_t         vvalue;         /* 24-bit vhandle */
    ncp_uint32_t         attrs;          /* Opaque attributes */
    ncp_uint32_t         addr;           /* Memory address */
} ncp_ptn_eaction_t;


/* List function definition which accepts an eaction_t structure */
#ifndef SWIG
typedef void (*ncp_ptn_list_ptns_eaction_fn_t)(void *rock, ncp_uint32_t treeId, 
                                   ncp_ptn_t *ptn, ncp_ptn_eaction_t *eaction);
#endif /* #ifndef SWIG */



/*!
 *  @defgroup _tree_APIs Tree
 *  @ingroup _ptn_Pattern
 *  @brief
 *  These APIs are used to manage regular trees.
 *  @details
 *  Regular trees implement longest prefix matching. These APIs are used to learn/unlearn patterns
 *  and compact these trees.
 ***************************************************************************************************/


/*!
 * @ingroup _tree_APIs
 * @brief Learns a specified pattern to the tree with the value
 * @details
 * The function searches the tree for the given pattern and if not found, creates
 *     it with the given action. If the pattern is found, its action is changed.
 * @param[in] inHdl Handle to the NCP.
 * @param[in] inTreeId Identifier for the pattern tree.
 * @param[in] inPtn Pointer to an instance of ncp_ptn_t struct that defines 
 *              the pattern learned.
 * @param[in] inAction Pointer to an instance of #ncp_ptn_action_t that defines
 *                 the action to be performed in conjuction with the pattern.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_AGEN_INVALID_OP
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_learn(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, ncp_ptn_t *inPtn,
              ncp_ptn_action_t *inAction);

/*!
 * @ingroup _tree_APIs
 * @brief Modifies a specified pattern and any sub-pattern values to the new value
 * @details
 * The function searches the tree for the given pattern and 
 *         all patterns underneath it and resets the action to the new action.
 *         All existing patterns are preserved in the tree, only their actions 
 *         are changed. 
 *         This differs from #ncp_ptn_learn in that all original patterns 
 *         that match or are more specific than the new pattern are relearned to the new action. If the
 *         specified pattern does not exist, it is not added to the tree; 
 *         only the patterns that were contained within this pattern in the tree are changed.
 * @param[in] inHdl Handle to the NCP.
 * @param[in] inTreeId Identifier for the pattern tree.
 * @param[in] inPtn Pointer to an instance of #ncp_ptn_t that defines 
 *              the pattern learned.
 * @param[in] inAction Pointer to an instance of #ncp_ptn_action_t that defines
 *                 the action to be performed in conjuction with the pattern.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_AGEN_INVALID_OP
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
NCP_API ncp_st_t
ncp_ptn_learn_any(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, ncp_ptn_t *inPtn,
                  ncp_ptn_action_t *inAction);

/*!
 * @ingroup _tree_APIs
 * @brief Removes a pattern from a pattern tree and optionally compacts 
 *        memory for the tree
 * @details
 * This function searches the tree for the given pattern and if found, unlearns
 *     it to the new value and subnet size. If the compact flag is set to TRUE, the
 *     subtree that was walked is processed for compaction.
 * @param[in] inHdl Handle to the NCP.
 * @param[in] inTreeId Identifier for the pattern tree.
 * @param[in] inPtn Pointer to an instance of #ncp_ptn_t that defines 
 *              the pattern removed.
 * @param[in] uxsize The number of "do-not-care" pattern bits in the subnet 
 *               to which this pattern reverts after it is unlearned. 
 *               uxsize cannot exceed the width of the pattern tree.
 * @param[in] inAction Pointer to an instance of #ncp_ptn_action_t that defines
 *                 the action to which this pattern reverts after it is 
 *                 unlearned.
 * @param[in] compact Specifies whether to compact memory after the unlearn 
 *                operation:
 *                false = Do not compact memory
 *                true = Compact memory
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_UXSIZE
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_AGEN_INVALID_OP
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_unlearn(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, ncp_ptn_t *inPtn,
                ncp_uint32_t uxsize, ncp_ptn_action_t *inAction, 
                ncp_bool_t compact);

/*!
 * @ingroup _tree_APIs
 * @brief Unlearns the specified pattern and any subpatterns that are 
 *        contained in it.
 * @details
 * This function searches the tree and unlearns the specified pattern and 
 *         any subpatterns that are contained in it by searching the tree
 *         for the pattern and all  patterns below it, and replacing the pattern
 *         with the number  of wildcard bits found in uxsize. The uxsize and action 
 *         represent the specified subnet or next higher subnet. 
 *         You can also use this API to delete all patterns, except the 
 *         default pattern, in a tree.
 *         The #ncp_ptn_unlearn_any function differs from the #ncp_ptn_unlearn 
 *         function in that #ncp_ptn_unlearn_any removes subpatterns also.
 * @param[in] inHdl Handle to the NCP.
 * @param[in] inTreeId Identifier for the pattern tree.
 * @param[in] inPtn Pointer to an instance of #ncp_ptn_t that defines 
 *              the pattern removed.
 * @param[in] uxsize The number of "do-not-care" pattern bits in the subnet 
 *               to which this pattern reverts after it is unlearned. 
 *               uxsize cannot exceed the width of the pattern tree.
 * @param[in] inAction Pointer to an instance of #ncp_ptn_action_t that defines
 *                 the action to which this pattern reverts after it is 
 *                 unlearned.
 * @param[in] compact Specifies whether to compact memory after the unlearn 
 *                operation:
 *                false = Do not compact memory
 *                true = Compact memory
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_UXSIZE
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_AGEN_INVALID_OP
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_unlearn_any(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, ncp_ptn_t *inPtn,
                    ncp_uint32_t uxsize, ncp_ptn_action_t *inAction, 
                    ncp_bool_t compact);

/*!
 * @ingroup _tree_APIs
 * @brief Use to compact memory for a specified pattern function.
 * @details
 * This function is used to compact a specific tree. If any changes have been made since the last
 *     compaction, the compaction algorithm is run on the tree.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId The pattern tree to be compacted.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
NCP_API ncp_st_t 
ncp_ptn_compact_fn(ncp_hdl_t inHdl, ncp_uint32_t inTreeId);

/*!
 * @ingroup _tree_APIs
 * @brief Use to compact memory for a specified pattern tree.
 * @details
 * This function is similar to #ncp_ptn_compact_fn with two important
 *         differences:
 *         <ul>
 *          <li>The application specifies a path in the tree where compaction should be performed.
 *          <li> #ncp_ptn_compact_fn_cb supports a callback function that 
                 returns a code indicating that the compaction should be aborted
 *          Tree compaction is process intensive and time consuming, based 
 *          on the number and type of changes made to the tree since the last 
 *          compaction. Because the NCP device pattern APIs are not thread-reentrant and are serialized,
 *          the application cannot respond to higher-priority operations until 
 *          the compaction is finished. To avoid this issue, the callback 
 *          function supports a callback interface that instructs the 
 *          compaction to halt, while keeping the tree in a consistent state. 
 *          In this case an error code is returned to the application and it 
 *          can, if necessary, respond to other higher-priority events in the 
 *          system.<br>
 *          The API also accepts a pattern that specifies a particular path in 
 *          the tree along which to perform compaction. For example, a pattern 
 *          of .10.10.*.*. indicates that the compaction is performed only in 
 *          the sub-tree identified by .10.10..<br>
 *          If the pattern tree has not had any patterns added to it or 
 *          removed from it since the last memory compaction, this API does 
 *          nothing.
 *      </ul>
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId The pattern tree to be compacted.
 * @param[in] inPtn The pattern to match
 * @param[in] cbfn The application callback function that is invoked at 
 *             regular intervals during the process.
 * @param[in] cbrock Application-specified opaque value that is passed to the 
 *               callback function.
 * @param[in] cbfrequency Specifies the frequency at which the callback function. This 
 *             relates to the number of nodes examined during the compaction process.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_OP
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

#ifndef SWIG
NCP_API ncp_st_t
ncp_ptn_compact_fn_cb(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, ncp_ptn_t *inPtn,
                      ncp_ptn_cb_fn_t cbfn, void *cbrock, 
                      ncp_uint32_t cbfrequency);
#endif /* #ifndef SWIG */

/*!
 * @ingroup _tree_APIs
 * @brief Use to compact memory for all trees
 * @details
 * This function is used to compact all the trees in FPL. The API walks through all trees which can
 *     be compacted, and if any changes have been made since the last compaction, it runs the
 *     compaction algorithm on the tree.
 * @param[in] inHdl The handle to the NCP.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
NCP_API ncp_st_t
ncp_ptn_compact( ncp_hdl_t inHdl );

/*!
 * @ingroup _tree_APIs
 * @brief Looks up a fully-specified pattern in a pattern tree and returns 
 *        the action to be performed in conjunction with that pattern
 * @details
 * This API performs a pattern match just like the hardware and returns the
 * matching action. The pattern cannot be a subnet. It must be a fully
 * specified pattern with no wild-card (indeterminate) bits. 
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId The pattern tree in which the lookup is to performed.
 * @param[in] inPtn    Pointer to an instance of an ncp_ptn_t structure that 
 *                 defines the pattern to be looked up.
 * @param[out] outAction Pointer to an instance of an ncp_ptn_action_t structure 
 *                  into which the action to be performed in conjunction 
 *                  with the pattern is returned
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
NCP_API ncp_st_t
ncp_ptn_match(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, ncp_ptn_t *inPtn,
              ncp_ptn_action_t *outAction);

/*!
 * @ingroup _tree_APIs
 * @brief List the patterns in a regular tree.
 * @details
 * This API is used to list the patterns in a regular tree. The entire tree is walked
 * and all the patterns are returned to the caller by invoking the callback function.
 * Note that the callback function may be called multiple times for
 * the same pattern. Subnet patterns tend to be represented by 
 * multiple leaves in the tree and whenever a leaf is traversed, the
 * callback is invoked immediately. It is up to the caller to filter
 * out a unique list.
 * Also note that this API is only valid for regular (LPM) trees.
 * For MFC trees such as OVTree and UVTree, it will return an error
 * since these trees are constructed very specially and the specific 
 * patterns do not resemble the original rules.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId  The pattern tree in which the lookup is to be performed. 
 *                  This is the tree number specified in the symbol file.
 * @param[in] listfn    The application-specified callback function. This function 
 *                  is invoked for each pattern. The function is invoked with 
 *                  application-specified opaque data (called "rock"), the 
 *                  tree ID, the pattern and an associated action.
 * @param[in] rock      An application-specified opaque value that is passed to 
 *                  the listfn callback function.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
#ifndef SWIG
NCP_API ncp_st_t
ncp_ptn_list_ptns( ncp_hdl_t inHdl, ncp_uint32_t inTreeId, ncp_ptn_list_ptns_fn_t listfn, void *rock );
#endif /* #ifndef SWIG */

/*!
 * @ingroup _tree_APIs
 * @brief List the patterns in a regular tree.
 * @details
 * This API is used to list the patterns in a regular tree. It is an
 * extension to #ncp_ptn_list_ptns in the sense that it allows the user
 * to specify a subset of patterns be listed. Every pattern in the tree
 * which matches or is more specific than inPtn is returned to the caller
 * by invoking the callbank function. If inPtn is NULL, all patterns in
 * the tree are listed.
 * For example, if the tree contains *.*.*.*, 10.*.*.*, 10.10.*.*,
 * 10.10.10.* and 10.10.10.10 and the API is invoked with 10.10.*.*,
 * the callback functions is called with the patterns 10.10.*.*,
 * 10.10.10.* and 10.10.10.10
 * Note that the callback function may be called multiple times for
 * the same pattern. Subnet patterns tend to be represented by 
 * multiple leaves in the tree and whenever a leaf is traversed, the
 * callback is invoked immediately. It is up to the caller to filter
 * out a unique list.
 * Also note that this API is only valid for regular (LPM) trees.
 * For MFC trees such as OVTree and UVTree, it will return an error
 * since these trees are constructed very specially and the specific 
 * patterns do not resemble the original rules.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId  The pattern tree in which the lookup is to be performed. 
 *                  This is the tree number specified in the symbol file.
 * @param[in] inPtn     Pointer to an instance of an #ncp_ptn_t that defines the 
 *                  pattern to be looked up.
 * @param[in] listfn    The application-specified callback function. This function 
 *                  is invoked for each pattern. The function is invoked with 
 *                  application-specified opaque data (called "rock"), the 
 *                  tree ID, the pattern and an associated action.
 * @param[in] rock      An application-specified opaque value that is passed to 
 *                  the listfn callback function.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
#ifndef SWIG
NCP_API ncp_st_t 
ncp_ptn_list_ptns_any(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                      ncp_ptn_t *inPtn, ncp_ptn_list_ptns_fn_t listfn, 
                      void *rock);
#endif /* #ifndef SWIG */


/*!
 *  @defgroup _ovtree_APIs Ordered Virtual Tree
 *  @ingroup _ptn_Pattern
 *  @brief
 *  These APIs are used to manage ordered virtual trees
 *  @details
 *  The OVTREE construct is used to implement access control lists. OVTREE is a multi-field classification
 *  construct where the patterns may be subnets. OVTREE implements an ordered match.
 *  The data structure ncp_vptn_t is used to represent each field value. 
 *  Any changes done using the  append, insert, modify, etc. APIs do not take effect until the load 
 *  function is called.
 *  As with any tree, the user should have a default rule at the end as a catch all. If there is no 
 *  default rule, the tree is created to invoke the error handler in case of a no-match.
 */


/*!
 * @ingroup _ovtree_APIs
 * @brief Clears all the rules for an ordered virtual (OV) tree.
 * @details
 * Clears all the rules for an ordered virtual (OV) tree. 
 * The tree structure in hardware is not affected. This function simply clears the in-memory list of rules.
 * @param[in] inHdl Handle to the NCP.
 * @param[in] inTreeId Identifier (from the FPL symbol table) of the OVtree 
 *                 to clear
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_ovtree_clear(ncp_hdl_t inHdl, ncp_uint32_t inTreeId);

/*!
 * @ingroup _ovtree_APIs
 * @brief Prepends the rule to the rule list. All existing rules are moved down
 * @details
 * Prepends the rule to the rule list
 * The tree structure in hardware is not affected. This function simply modifies the in-memory list of rules.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier (assigned by the control program) of the OVTree
 *                 to update.
 * @param[in] inNumVPtns Number of virtual patterns in the rule.
 * @param[in] inVPtns Pointer to an array of instances of the data structure 
 *                 #ncp_ptn_t, each defining a virtual pattern.
 * @param[in] inAction Pointer to an instance of an #ncp_ptn_action_t structure 
 *                 that defines the action to be performed in conjunction
 *                 with the rule.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_ovtree_prepend(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                       ncp_uint32_t inNumVPtns, ncp_vptn_t *inVPtns, 
                       ncp_ptn_action_t *inAction);

/*!
 * @ingroup _ovtree_APIs
 * @brief Appends a rule(an array of one or more virtual patterns) at the 
 *        end of the list of rules for an OVTree.
 * @details
 * Appends a rule at the end of the list of rules for an OVTree. 
 * The tree structure in hardware is not affected. This function simply modifies the in-memory list of rules.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier (assigned by the control program) of the OVTree 
 *                 to update.
 * @param[in] inNumVPtns Number of virtual patterns in the rule.
 * @param[in] inVPtns    Pointer to an array of instances of ncp_vptn_t, each of 
 *                   which define a virtual pattern.
 * @param[in] inAction   Pointer to an instance of ncp_ptn_action_t
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_ovtree_append(ncp_hdl_t inHdl, ncp_uint32_t inTreeId,
                      ncp_uint32_t inNumVPtns, ncp_vptn_t *inVPtns, 
                      ncp_ptn_action_t *inAction);

/*!
 * @ingroup _ovtree_APIs
 * @brief Appends a rule(an array of one or more virtual patterns) at the 
 *        end of the list of rules for an OVTree.
 * @details
 * Adds a rule at the end of the list of rules for an OVTree. 
 * The tree structure in hardware is not affected. This function simply modifies the in-memory list of rules.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier (assigned by the control program) of the OVTree 
 *                 to update.
 * @param[in] inNumVPtns Number of virtual patterns in the rule.
 * @param[in] inVPtns    Pointer to an array of instances of ncp_vptn_t, each of 
 *                   which define a virtual pattern.
 * @param[in] inAction   Pointer to an instance of #ncp_ptn_action_t
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_ovtree_add(ncp_hdl_t inHdl, ncp_uint32_t inTreeId,
                   ncp_uint32_t inNumVPtns, ncp_vptn_t *inVPtns, 
                   ncp_ptn_action_t *inAction);
/*!
 * @ingroup _ovtree_APIs
 * @brief Inserts a rule at a specified index in the list of rules for an OVTree
 * @details
 * All current rules whose indexes are equal to or greater than the 
 *         index of the new rule are moved down by one. If the specified index 
 *         is larger than the largest current index in the OVTree, the new 
 *         rule is appended to the tree.
 * The tree structure in hardware is not affected. This function simply modifies the in-memory list of rules.
 * @param[in] inHdl      The handle to the NCP.
 * @param[in] inTreeId   Identifier (assigned by the control program) of the OVTree 
 *                   to update.
 * @param[in] inIndex    The index within the OVTree at which to insert the rule.
 * @param[in] inNumVPtns Number of virtual patterns in the rule.
 * @param[in] inVPtns    Pointer to an array of instances of ncp_vptn_t, each of 
 *                   which define a virtual pattern.
 * @param[in] inAction   Pointer to an instance of #ncp_ptn_action_t
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_AGEN_INVALID_INDEX
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_ovtree_insert(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                      ncp_uint32_t inIndex, ncp_uint32_t inNumVPtns, 
                      ncp_vptn_t *inVPtns, ncp_ptn_action_t *inAction);
/*!
 * @ingroup _ovtree_APIs
 * @brief Deletes a rule for an Ovtree at a specific index 
 * @details
 * All the rules following the deleted rules are moved up. 
 * The tree structure in hardware is not affected. This function simply modifies the in-memory list of rules.
 * @param[in] inHdl      The handle to the NCP.
 * @param[in] inTreeId   Identifier (from the FPL symbol table) of the OVTree 
 * @param[in] inIndex    The index within the OVTree at which to start deletion. 
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_AGEN_INVALID_INDEX
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_ovtree_delete(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                      ncp_uint32_t inIndex);

/*!
 * @ingroup _ovtree_APIs
 * @brief Replaces the rule at a specified index in the list of rules for an 
 *        ordered virtual (OV) tree.
 * @details
 * If the specified index is larger than the largest current index 
 *         in the OV tree, the rule is appended to the tree.
 * The tree structure in hardware is not affected. This function simply modifies the in-memory list of rules.
 * @param[in] inHdl      The handle to the NCP.
 * @param[in] inTreeId   Identifier (from the FPL symbol table) of the OVTree 
 * @param[in] inIndex    The index within the OVTree where to apply to modification
 * @param[in] inNumVPtns Number of virtual patterns in the rule.
 * @param[in] inVPtns    Pointer to array of instances of ncp_vptn_t, each of which
 *                   define a virtual pattern.
 * @param[in] inAction   Pointer to an instance of #ncp_ptn_action_t that defines the
 *                   action to be performed in conjuction with the rule.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_AGEN_INVALID_INDEX
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_ovtree_modify(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                      ncp_uint32_t inIndex, ncp_uint32_t inNumVPtns, 
                      ncp_vptn_t *inVPtns, ncp_ptn_action_t *inAction);

/*!
 * @ingroup _ovtree_APIs
 * @brief Gets the number of rules (arrays of one or more virtual patterns) 
 *        currently in an OVtree.
 * @details
 * @param[in] inHdl      The handle to the NCP.
 * @param[in] inTreeId   Identifier (from the FPL symbol table) of the OVTree 
 * @param[out] outNumVRules Pointer to the unsigned integer where the API will
 *                     return the number of rules in the OVTree.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_ovtree_novrules(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                        ncp_uint32_t *outNumVRules);

/*!
 * @ingroup _ovtree_APIs
 * @brief Lists all the virtual rules in the specified OVTree.
 * @details
 * The application callback function, listfn, is invoked for 
 *         each virtual rule in the OVTree.
 *         The function is invoked with application-specified 
 *         opaque data (called "rock"), the inOvtreeID, the virtual rule index 
 *         number, number of virtual patterns in the virtual rule, 
 *         the virtual patterns themselves and the associated action.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inOvtreeId The pattern tree in which the lookup is to performed. 
 *                   This is the tree number specified in the symbol file.
 * @param[in] listfn     The application-specified callback function. This 
 *                   function is invoked for a virtual rule. The function is 
 *                   invoked with application-specified data, the OVTree ID, 
 *                   the virtual rule index number, the number of virtual 
 *                   patterns in the virtual rule, and the virtual patterns 
 *                   that are the associated action.
 * @param[in] rock An application-specified opaque value that is passed to the 
 *             listfn callback function.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *         </ul>
 */

#ifndef SWIG
NCP_API ncp_st_t 
ncp_ptn_list_vrules(ncp_hdl_t inHdl, ncp_uint32_t inOvtreeId, 
                    ncp_ptn_list_vrules_fn_t listfn, void *rock);
#endif /* #ifndef SWIG */

/*!
 * @ingroup _ovtree_APIs
 * @brief Loads all ordered virtual (OV) trees into Program Memory
 * @details
 * This function walks through all ovtrees which have been modified by the ovtree APIs and for one, rebuilds
 * the entire rule set in hardware memory.
 * @param[in] inHdl The handle to the NCP.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
NCP_API ncp_st_t
ncp_ptn_ovtrees_load(ncp_hdl_t inHdl);

/*!
 * @ingroup ovtree_APIs
 * @brief Identical to ncp_ptn_ovtrees_load, except that application can 
 * specify a callback function to invoke in the middle of processing.
 * @details
 * Identical to #ncp_ptn_ovtrees_load, except that application can 
 * specify a callback function to invoke in the middle of processing.
 * Since OVTREE building is an expensive and time-consuming process, this
 * callback provides the application a window to handle other tasks.
 * Unlike other APIs which support callback functions, the OVTREE callback
 * function CANNOT abort processing in the middle. The return value of the
 * callback is ignored and processing continues until the relevant OVTREEs
 * are rebuilt.
 * The cbfrequency provides the application a very coarse granularity on
 * the frequency of callbacks. Though OVTREE building comprises of many
 * distinct stages, two of these stages are the most time consuming and
 * the callback functionality is provided in these stages. 
 * In the first stage, all the rules and field values are analyzed together
 * and converted into a directed graph. In this stage, the cbfrequency number
 * loosely relates to the number of rules processed. Since the processing time
 * of each rule can vary widely (depends on how the rule and it's values relate
 * to the preceding rules), this does not denote any defined time period.
 * In the second stage, each node in the directed graph is analyzed and
 * converted into a set of hardware instructions. In this stage, the cbfrequency
 * is related to the number of nodes processed.
 * To reiterate, the cbfrequency is a very coarse knob to control the frequency
 * of callbacks. Value should be > 0. Recommended to be >= 50.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] cbfn The application callback function that is invoked at 
 *             regular intervals during the process.
 * @param[in] cbrock Application-specified opaque value that is passed to the 
 *               callback function.
 * @param[in] cbfrequency Specifies the frequency at which the callback function 
 *                    is invoked. The value must be 1 or higher. A lower value 
 *                    indicates higher frequency. In some cases, the frequency 
 *                    is directly related to the number of memory instructions 
 *                    processed as the comparison algorithm sequentially
 *                    reads the memory.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

#ifndef SWIG
NCP_API ncp_st_t
ncp_ptn_ovtrees_load_cb(ncp_hdl_t inHdl, ncp_ptn_cb_fn_t cbfn, void *cbrock,
                        ncp_uint32_t cbfrequency);

#endif /* #ifndef SWIG */

/*!
 *  @defgroup _otree_APIs Ordered Tree
 *  @ingroup _ptn_Pattern
 *  @brief
 *  These APIs are used to manage ordered trees.
 *  @details
 *  The OTREE construct is used to implement access control lists. OTREE is a multi-field classification
 *  construct where the patterns may be subnets. In functionality, it is similar to OVTREE but does
 *  not require source trees.
 *  The data structure ncp_vptn_t is used to represent each field value. In this data structure, 
 *  the treeId member is not relevant for any of these operations since Otree patterns do not have 
 *  any source trees to refer to.
 *  Any changes done using the  append, insert, modify, etc. APIs do not take effect until the build
 *  function is called.
 *  As with any tree, the user should have a default rule at the end as a catch all. If there is no 
 *  default rule, the tree is created to invoke the error handler in case of a no-match.
 ***************************************************************************************************/


/*!
 * @ingroup _otree_APIs
 * @brief Deletes all the rules from an OTree rule set.
 * @details
 * The tree structure in hardware is not affected. This function simply clears the in-memory list of rules.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier of the OTree to be cleared.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_otree_clear(ncp_hdl_t inHdl, ncp_uint32_t inTreeId);

/*!
 * @ingroup _otree_APIs
 * @brief This API is used to prepend a rule (insert as first rule) to the 
 *        Otree's set of rules
 * @details
 * The new rule identified by the virtual patterns and actions is 
 *         added at the beginning of all the rules, at index 0.
 * The tree structure in hardware is not affected. 
 * @param[in] inHdl     The handle to the NCP.
 * @param[in] inTreeId  Identifier of the OTree in which to insert the new rule.
 * @param[in] inNumVPtns Number of virtual patterns in the rule.
 * @param[in] inVPtns   Pointer to an array of instances of #ncp_ptn_t, each 
 *                  defining a virtual pattern.
 * @param[in] inAction  Pointer to an instance of an #ncp_ptn_action_t structure 
 *                  that defines the rule's action.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_otree_prepend(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                      ncp_uint32_t inNumVPtns, ncp_vptn_t *inVPtns, 
                      ncp_ptn_action_t *inAction);

/*!
 * @ingroup _otree_APIs
 * @brief Appends the rule to the list of otree rules
 * @details
 * The new rule identified by the virtual patterns and actions is added as the last rule.
 * The tree structure in hardware is not affected. 
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier (assigned by the control program) of the OTree 
 *                 to update.
 * @param[in] inNumVPtns Number of virtual patterns in the rule.
 * @param[in] inVPtns Pointer to an array of instances of ncp_vptn_t, each 
 *                defining a virtual pattern.
 * @param[in] inAction Pointer to an instance of an #ncp_ptn_action_t that defines 
 *                 the action to be performed in conjunction with the rule.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_otree_append(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                     ncp_uint32_t inNumVPtns, ncp_vptn_t *inVPtns, 
                     ncp_ptn_action_t *inAction);


/*!
 * @ingroup _otree_APIs
 * @brief Used to insert a rule at the specified index to the 
 *        Otree's set of rules. The maximum value of index can be number of 
 *        rules (indices start at 0).
 * @details
 * The existing rule at inIndex and subsequent rules are moved down by 
 *         one location. The maximum value of inIndex can be numVrules, in 
 *         which case the rule is added at the end. The new rule is identified 
 *         by the virtual patterns and the action.
 * The tree structure in hardware is not affected. 
 * @param[in] inHdl    The handle to the NCP.
 * @param[in] inTreeId Identifier of the OTree in which to insert the new rule.
 * @param[in] inIndex  The index within the OTree at which to insert the rule.
 * @param[in] inNumVPtns Number of virtual patterns in the rule.
 * @param[in] inVPtns    Pointer to an array of instances of #ncp_ptn_t, each 
 *                   defining a virtual pattern.
 * @param[in] inAction   Pointer to an instance of an #ncp_ptn_action_t that 
 *                   defines rule's action.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_AGEN_INVALID_INDEX
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_otree_insert(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                     ncp_uint32_t inIndex, ncp_uint32_t inNumVPtns, 
                     ncp_vptn_t *inVPtns, ncp_ptn_action_t *inAction);

/*!
 * @ingroup _otree_APIs
 * @brief Delete the rule at the specified index from the Otree
 * @details
 * This API is used to delete a rule at the specified index from 
 *        the Otree's set of rules. The index has to identify a 
 *        valid rule (range is 0 to novrules - 1).
 * The tree structure in hardware is not affected. 
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier of the OTree
 * @param[in] inIndex  The index within the OV tree at which to delete the rule.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_INDEX
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_otree_delete(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                     ncp_uint32_t inIndex);

/*!
 * @ingroup _otree_APIs
 * @brief Replaces a rule at a given index in the Otree
 * @details
 * This API is used to replace a rule at given index with a new rule in 
 *        the Otree's set of rules. The index has to identify a valid rule 
 *        (range is 0 to novrules - 1).
 * The tree structure in hardware is not affected. 
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId    Identifier of the OTree to update.
 * @param[in] inIndex     The index within the OV tree at which to insert the rule.
 * @param[in] inNumVPtns  Number of virtual patterns in the rule.
 * @param[in] inVPtns     Pointer to an array of instances of ncp_vptn_t, 
 *                    each defining a virtual pattern.
 * @param[in] inAction    Pointer to an instance of #ncp_ptn_action_t that defines 
 *                    the action to be performed in conjunction with the rule.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_AGEN_INVALID_INDEX
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_otree_modify(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                     ncp_uint32_t inIndex, ncp_uint32_t inNumVPtns, 
                     ncp_vptn_t *inVPtns, ncp_ptn_action_t *inAction);

/*!
 * @ingroup _otree_APIs
 * @brief Retrieves number of rules in VTree
 * @details
 * Use this API to retrieve the current number of rules in a 
 *          specific set (which can be the default set). The number of rules 
 *          is returned in outNumVRules. 
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId     Identifier of the OTree to get rules from.
 * @param[in] outNumVRules   Number of rules in the set.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_otree_novrules(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                       ncp_uint32_t *outNumVRules);

/*!
 * @ingroup _otree_APIs
 * @brief List the virtual rules for the OTree
 * @details
 * This API is used to list the virtual rules for the otree
 *     The user specified callback function listfn is invoked for each rule.
 *     The rules listed are what the user added using the otree_append() API.
 *     If the rules were deleted using the otree_clear() API, no rules are listed.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier (assigned by the control program) of the OTree 
 *                 to update.
 * @param[in] listfn The application-specified callback function. This function is 
 *               invoked for a virtual rule.
 * @param[in] rock   An application-specified opaque value that is passed to the 
 *               callback function, listfn.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

#ifndef SWIG
NCP_API ncp_st_t 
ncp_ptn_otree_list_vrules(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                          ncp_ptn_list_vrules_fn_t listfn, void *rock);
#endif /* #ifndef SWIG */

/*!
 * @ingroup _otree_APIs
 * @brief Builds an OTree with the new set of rules.
 * @details
 * The OTree rule set must have a default rule at the end. If no 
 *         default rule is provided, the API temporarily adds a default rule 
 *         at the end during the build process to invoke the error handler 
 *         function on a no-match. The width of each field in an OTree can be 
 *         up to a maximum of 255 bits.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier of the OTree to build
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_otree_build(ncp_hdl_t inHdl, ncp_uint32_t inTreeId);


/*!
 * @ingroup _otree_APIs
 * @brief Identical to ncp_ptn_otree_build build, 
 *         except that application can specify a callback function to invoke 
 *         in the middle of processing.
 * @details
 * Since OTREE building is an expensive and time-consuming process, this
 * callback provides the application a window to handle other tasks.
 * Unlike other APIs which support callback functions, the OTREE callback
 * function CANNOT abort processing in the middle. The return value of the
 * callback is ignored and processing continues until the OTREE is rebuilt.
 * The cbfrequency provides the application a very coarse granularity on
 * the frequency of callbacks. Though OTREE building comprises of many
 * distinct stages, two of these stages are the most time consuming and
 * the callback functionality is provided in these stages. 
 * In the first stage, all the rules and field values are analyzed together
 * and converted into a directed graph. In this stage, the cbfrequency number
 * loosely relates to the number of rules processed. Since the processing time
 * of each rule can vary widely (depends on how the rule and it's values relate
 * to the preceding rules), this does not denote any defined time period.
 * In the second stage, each node in the directed graph is analyzed and
 * converted into a set of hardware instructions. In this stage, the cbfrequency
 * is related to the number of nodes processed.
 * To reiterate, the cbfrequency is a very coarse knob to control the frequency
 * of callbacks. Value should be > 0. Recommended to be >= 50.
 * @param[in] inHdl  The handle to the NCP.
 * @param[in] fnid The Function id
 * @param[in] cbfn The application callback function that is invoked at 
 *             regular intervals during the process.
 * @param[in] cbrock Application-specified opaque value that is passed to the 
 *               callback function.
 * @param[in] cbfrequency Specifies the frequency at which the callback function 
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_CB_ABORT
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

#ifndef SWIG
ncp_st_t
ncp_ptn_otree_build_cb( ncp_hdl_t inHdl, ncp_uint32_t fnid,
                        ncp_ptn_cb_fn_t cbfn, void *cbrock, 
                        ncp_uint32_t cbfrequency );
#endif


/*!
 *  @defgroup _otreeset_APIs Ordered Tree Set
 *  @ingroup _ptn_Pattern
 *  @brief
 *  These APIs are used to manage ordered tree sets.
 *  @details
 *  The OTREESET construct is used to implement access control lists. OTREESET is a multi-field classification
 *  construct where the patterns may be subnets. Additionally, the first field is treated as a set id and
 *  the rules are organized and built based on the set id. 
 *  The data structure ncp_vptn_t is used to represent each field value. In this data structure, 
 *  the treeId member is not relevant for any of these operations since OtreeSet patterns do not have 
 *  any source trees to refer to.
 *  Any changes done using the  append, insert, modify, etc. APIs do not take effect until the build
 *  function is called.
 *  As with any tree, the user should have a default rule at the end as a catch all. Since each set of 
 *  rules is built independently, there should be a default rule for each set (a rule with the first 
 *  field being the set id and the rest of the fields being the default patterns). If there is no 
 *  default rule, each set is created to invoke the error handler in case of a no-match.
 *  A default value for the set id indicates the default set.
 *
 *  Removal of a set can be accomplished by clearing all the rules for the set and building it. At this 
 *  point, the API recognizes that the set needs to be removed and unlearns it to the default set. 
 *  Any patterns with that set id  will now be matched to the rules for the default set. The default 
 *  set itself cannot be removed. When this set contains no rules, the set will be constructed to go 
 *  to the error handler.
 ***************************************************************************************************/

/*!
 * @ingroup _otreeset_APIs
 * @brief Deletes all the rules from an OTreeSet rule set.
 * @details
 * This API is used to clear a set of rules. The set is identified by 
 *     inVPtn. As per the definition of an OtreeSet, this field value can either 
 *     be a fully specified value or the full default (no subnet).
 *     If inVPtn is NULL, all sets are cleared. In this way, the entire set of
 *     rules for all sets can be deleted.
 * The tree structure in hardware is not affected. This function simply clears the in-memory list of rules.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier of the OTreeSet to clear.
 * @param[in] inVPtn   Set identifier. Can be the default set, NULL, or a specific 
 *                 set.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_otreeset_clear(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                       ncp_vptn_t *inVPtn);

/*!
 * @ingroup _otreeset_APIs
 * @brief Prepends a new rule to the OtreeSet
 * @details
 * The set to which the rule gets prepended to is defined by the 
 *         first field value (inVPtns[0]). As per the definition of an OtreeSet,
 *         this field value can either be a fully specified value or the full 
 *         default (no subnet).
 * The tree structure in hardware is not affected.
 * @param[in] inHdl      The handle to the NCP.
 * @param[in] inTreeId   Identifier of the OTreeSet.
 * @param[in] inNumVPtns Number of virtual patterns in the rule.
 * @param[in] inVPtns    Pointer to an array of instances of #ncp_ptn_t, each 
 *                   defining a virtual pattern.
 * @param[in] inAction   Pointer to an instance of an #ncp_ptn_action_t structure 
 *                   that defines the action to be performed in conjunction 
 *                   with the rule.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_otreeset_prepend(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                         ncp_uint32_t inNumVPtns, ncp_vptn_t *inVPtns, 
                         ncp_ptn_action_t *inAction);

/*!
 * @ingroup _otreeset_APIs
 * @brief Adds new rules to the end of an OTreeSet rule set.
 * @details
 * This API is used to append a new rule to the OtreeSet. The set to 
 *         which the rule gets appended to is defined by the first 
 *         field value (inVPtns[0]). As per the definition of an OtreeSet, 
 *         this field value can either be a fully specified value or the full 
 *         default (no subnet)
 * The tree structure in hardware is not affected.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier (assigned by the control program) of the OTree 
 *                 to update.
 * @param[in] inNumVPtns Number of virtual patterns in the rule.
 * @param[in] inVPtns    Pointer to an array of instances of ncp_vptn_t, each 
 *                   defining a virtual pattern.
 * @param[in] inAction   Pointer to an instance of #ncp_ptn_action_t that defines 
 *                   the action to be performed in conjunction with the rule.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
NCP_API ncp_st_t
ncp_ptn_otreeset_append(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                        ncp_uint32_t inNumVPtns, ncp_vptn_t *inVPtns, 
                        ncp_ptn_action_t *inAction);

/*!
 * @ingroup _otreeset_APIs
 * @brief Inserts a new rule at the specified index to the OtreeSet
 * @details
 * The set in which the rule gets inserted is defined by the 
 *         first field value (inVPtns[0]). The maximum value of index can be 
 *         number of rules (indices start at 0). As per the definition of an 
 *         OtreeSet, this field value can either be a fully specified value or 
 *         the full default (no subnet)
 * The tree structure in hardware is not affected.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier of the OTreeSet.
 * @param[in] inIndex  The index within the OTreeSet at which to insert the rule.
 * @param[in] inNumVPtns Number of virtual patterns in the rule.
 * @param[in] inVPtns    Pointer to an array of instances of ncp_vptn_t, each 
 *                   defining a virtual pattern.
 * @param[in] inAction   Pointer to an instance of #ncp_ptn_action_t that defines 
 *                   the action to be performed in conjunction with the rule
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_AGEN_INVALID_INDEX
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_otreeset_insert(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                        ncp_uint32_t inIndex, ncp_uint32_t inNumVPtns, 
                        ncp_vptn_t *inVPtns, ncp_ptn_action_t *inAction);

/*!
 * @ingroup _otreeset_APIs
 * @brief Deletes a rule at the specified index from the specified set of an OtreeSet.
 * @details
 * The set is identified by vptn. As per the definition of an OtreeSet,
 * this value can either be a fully specified value or the full default 
 * (no subnet). The index has to identify a valid rule 
 * (range is 0 to novrules - 1).
 * The tree structure in hardware is not affected.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier of the OTreeSet.
 * @param[in] inVPtn   Set identifier. Can be the default set, NULL, or a 
 *                 specific set.
 * @param[in] inIndex  The index within the OTreeSet at which to delete the rule.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_AGEN_INVALID_INDEX
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_otreeset_delete(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                        ncp_uint32_t inIndex, ncp_vptn_t *inVPtn);

/*!
 * @ingroup _otreeset_APIs
 * @brief Replaces a rule at the specified index in the specified set of an OtreeSet. 
 * @details
 * The set is identified by the first field value of the rule 
 *         (inVPtns[0]). The index has to identify a valid rule 
 *         (range is 0 to novrules - 1). As per the definition of an OtreeSet, 
 *         this field value can either be a fully specified value or the 
 *         full default (no subnet)
 * The tree structure in hardware is not affected. This function simply modifies the in-memory list of rules.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier of the OTreeSet.
 * @param[in] inIndex    The index within the OTreeSet at which to insert the rule.
 * @param[in] inNumVPtns In Number of virtual patterns in the rule.
 * @param[in] inVPtns    Pointer to an array of instances of ncp_vptn_t, each 
 *                   defining a virtual pattern.
 * @param[in] inAction   Pointer to an instance of #ncp_ptn_action_t that defines 
 *                   the action to be performed in conjunction with the rule.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_AGEN_INVALID_INDEX
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_otreeset_modify(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                        ncp_uint32_t inIndex, ncp_uint32_t inNumVPtns, 
                        ncp_vptn_t *inVPtns, ncp_ptn_action_t *inAction);

/*!
 * @ingroup _otreeset_APIs
 * @brief Retrieves number of rules in the OtreeSet for the 
 *        specified set.
 * @details
 * The set is identified by vptn. As per the definition of an 
 *          OtreeSet, this field value can either be a fully specified value 
 *          or the full default (no subnet). The inVPtn identifies the set on 
 *          which the operation is performed. If inVPtn is NULL, the number of 
 *          rules for all of the sets is returned. Please note that if the set does
 *          not exist then NCP_ST_AGEN_INVALID_PTN error is returned.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier of the OTreeSet.
 * @param[in] inVPtn   Identifies the set in which to count the number of rules.
 * @param[out] outNumVRules Number of rules in the set.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_otreeset_novrules(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                          ncp_vptn_t *inVPtn, ncp_uint32_t *outNumVRules);

/*!
 * @ingroup _otreeset_APIs
 * @brief List the virtual rules for a set
 * @details
 * This API is used to list the virtual rules for a set. The set is 
 *     identified by inVPtn. 
 *     As per the definition of an OtreeSet, this field value can either
 *     be a fully specified value or the full default (no subnet).
 *     If inVPtn is NULL, all sets are listed. In this way, the entire set of
 *     rules for all sets can be retrieved.
 *     The user specified callback function listfn is invoked for each rule
 *     The rules listed are what the user added using the otreeset_append() API.
 *     If the rules were deleted using the otreeset_clear() API, no rules are listed.
 * @param[in] inHdl    The handle to the NCP.
 * @param[in] inTreeId Identifier of the OTreeSet for which you want to list rules.
 * @param[in] inVPtn   Set identifier. Can be the default set, NULL, or a 
 *                 specific set.
 * @param[in] listfn   The application-specified callback function. This function 
 *                 is invoked for a virtual rule.
 * @param[in] rock     An application-specified opaque value that is passed to the 
 *                 callback function, listfn.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
#ifndef SWIG
NCP_API ncp_st_t 
ncp_ptn_otreeset_list_vrules(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                             ncp_vptn_t *inVPtn, 
                             ncp_ptn_list_vrules_fn_t listfn, void *rock);
#endif /* #ifndef SWIG */

/*!
 * @ingroup _otreeset_APIs
 * @brief  Builds an OTreeSet with the new set of rules.
 * @details
 * This API is used to build a set of rules. The set is 
 *         identified by inVPtn. As per the definition of an OtreeSet, this 
 *         field value can either be a fully specified value or the full 
 *         default (no subnet). If inVPtn is NULL, all sets are rebuilt. 
 *         In this way, the entire set of rules for all sets can be rebuilt.
 * @param inHdl The handle to the NCP.
 * @param inTreeId Identifier of the OTreeSet to build.
 * @param inVPtn   Set identifier. Can be the default set, NULL, or a 
 *                 specified set.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_otreeset_build(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                       ncp_vptn_t *inVPtn);


/*!
 * @ingroup _otreeset_APIs
 * @brief Identical to #ncp_ptn_otree_build and #ncp_ptn_otreeset_build, 
 *         except that application can specify a callback function to invoke 
 *         in the middle of processing.
 * @details
 * Since OTREESET building is an expensive and time-consuming process, this
 * callback provides the application a window to handle other tasks.
 * Unlike other APIs which support callback functions, the OTREESET callback
 * function CANNOT abort processing in the middle. The return value of the
 * callback is ignored and processing continues until the OTREESET is rebuilt.
 * The cbfrequency provides the application a very coarse granularity on
 * the frequency of callbacks. Though OTREESET building comprises of many
 * distinct stages, two of these stages are the most time consuming and
 * the callback functionality is provided in these stages. 
 * In the first stage, all the rules and field values are analyzed together
 * and converted into a directed graph. In this stage, the cbfrequency number
 * loosely relates to the number of rules processed. Since the processing time
 * of each rule can vary widely (depends on how the rule and it's values relate
 * to the preceding rules), this does not denote any defined time period.
 * In the second stage, each node in the directed graph is analyzed and
 * converted into a set of hardware instructions. In this stage, the cbfrequency
 * is related to the number of nodes processed.
 * To reiterate, the cbfrequency is a very coarse knob to control the frequency
 * of callbacks. Value should be > 0. Recommended to be >= 50.
 * @param[in] inHdl  The handle to the NCP.
 * @param[in] fnid The Function id
 * @param[in] inVPtn   Set identifier. Can be the default set, NULL, or a specific 
 *                 set.
 * @param[in] cbfn The application callback function that is invoked at 
 *             regular intervals during the process.
 * @param[in] cbrock Application-specified opaque value that is passed to the 
 *               callback function.
 * @param[in] cbfrequency Specifies the frequency at which the callback function 
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_CB_ABORT
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
#ifndef SWIG
ncp_st_t
ncp_ptn_otreeset_build_cb( ncp_hdl_t inHdl, ncp_uint32_t fnid, 
                           ncp_vptn_t *inVPtn, ncp_ptn_cb_fn_t cbfn, 
                           void *cbrock, ncp_uint32_t cbfrequency );
#endif /* #ifndef SWIG */


/*!
 *  @defgroup _mem_APIs Memory Statistics
 *  @ingroup _ptn_Pattern
 *  @brief
 *  These APIs are used to retrieve memory usage statistics
 *  @details
 ***************************************************************************************************/

/*!
 * @ingroup _mem_APIs
 * @brief Returns memory statistics
 * @details
 * @param[in] inHdl    The handle to the NCP.
 * @param[out] outStats Pointer to an instance of the #ncp_ptn_mem_stats_t 
 *                 that defines the statistics retrieved.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_mem_stats(ncp_hdl_t inHdl, ncp_ptn_mem_stats_t *outStats);

/*!
 * @ingroup _mem_APIs
 * @brief Gets statistics for each tree function, beginning with initial 
 *        system configuration.
 * @details
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Pattern tree for which statistics are requested.
 * @param[out] outStats Pointer to #ncp_ptn_fn_stats_t to return statistics.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *         </ul>
 */

NCP_API ncp_st_t 
ncp_ptn_fn_stats(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                 ncp_ptn_fn_stats_t *outStats);

/*!
 * @ingroup _mem_APIs
 * @brief Returns the memory used by a subtree in a specified tree function.
 * @details
 * The function is identified by inTreeId, and a particular subtree 
 *         in the function is identified by inPtn. If inPtn is specified as 
 *         the full default, the memory used by the subtree below the pattern 
 *         is returned.
 *         <br>
 *         For example, a pattern specification of 10.20.*.* returns the 
 *         memory used by the subtree below the prefix 10.20.
 * @param[in] inHdl    The handle to the NCP.
 * @param[in] inTreeId Pattern tree for which the operation is performed
 * @param[in] inPtn    The subtree for which the memory used is calculated.
 * @param[out] outMem   The amount of memory used, returned in bytes.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_fn_subtreemem(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, ncp_ptn_t *inPtn,
                      ncp_uint32_t *outMem);

/*!
 * @ingroup _mem_APIs
 * @brief Request allocation of fmemRequired flow memory.
 * @details
 * @param[in] inHdl The handle to the NCP.
 * @param[out] fmemRequired The requested size of flow memory.
 * @param[out] fmemAlloced  The amount of flow memory actually allocated.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_fmem_size( ncp_hdl_t inHdl, ncp_uint32_t *fmemRequired, 
                   ncp_uint32_t *fmemAlloced );

/*!
 * @ingroup _mem_APIs
 * @brief Request allocation of rmemRequired rmem.
 * @details
 * @param[in] inHdl The handle to the NCP.
 * @param[out] rmemRequired The requested size of memory.
 * @param[out] rmemAlloced  The amount of memory actually allocated.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_rmem_size( ncp_hdl_t inHdl, ncp_uint32_t *rmemRequired, 
                   ncp_uint32_t *rmemAlloced );

/*!
 *  @defgroup _uvtree_APIs Unordered Virtual Tree
 *  @ingroup _ptn_Pattern
 *  @brief
 *  These APIs are used to manage unordered virtual trees
 *  @details
 *  The UVTREE construct is used to implement flow matching. UVTREE is a multi-field classification
 *  construct where all the patterns are fully specified.
 *  The data structure ncp_vptn_t is used to represent each field value.
 *  As with any tree, the user should have a default rule at the end as a catch all. If there is no 
 *  default rule, the tree is created to invoke the error handler in case of a no-match.
 ***************************************************************************************************/

/*!
 * @ingroup _uvtree_APIs
 * @brief Learn a new rule for an unordered virtual (UV) tree.
 * @details
 * Each of the virtual patterns is assigned a virtual number 
 *         (if not assigned previously and if does not exceed the 
 *         VSIZE [maximum virtual handle size] value for the tree) and learned 
 *         into the respective source trees. These virtual numbers are then 
 *         concatenated into the pattern which is learned into the UVTree with 
 *         the specified action.
 *         <br>
 *         All virtual patterns in a UVTree rule must be either the default 
 *         patterns (all wild cards) or specific patterns (no wildcard).
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier (assigned by the control program) of the 
 *                   UVTree to update.
 * @param[in] inNumVPtns Number of virtual patterns in the rule.
 * @param[in] inVPtns Pointer to an array of instances of the ncp_vptn_t, each 
 *                defining a virtual pattern.
 * @param[in] inAction Pointer to an instance of an #ncp_ptn_action_t that defines 
 *                 the action to be performed in conjunction with the rule.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_uvtree_learn(ncp_hdl_t inHdl, ncp_uint32_t inTreeId,
                     ncp_uint32_t inNumVPtns, ncp_vptn_t *inVPtns, 
                     ncp_ptn_action_t *inAction);

/*!
 * @ingroup _uvtree_APIs
 * @brief Relearns a UVTree rule.
 * @details
 * The UVTree rule is assumed to have been learned previously.
 *         This API changes the action of an existing UVTree rule.
 * @param[in] inHdl The handle to the NCP
 * @param[in] inTreeId Identifier (assigned by the control program) of the UVTree 
 *                 to update.
 * @param[in] inNumVPtns Number of virtual patterns in the rule.
 * @param[in] inVPtns Pointer to an array of instances of the ncp_vptn_t, each 
 *                defining a virtual pattern.
 * @param[in] inAction Pointer to an instance of an ncp_action_t structure that 
 *                 defines the action to be performed in conjunction with the 
 *                 rule.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_uvtree_relearn(ncp_hdl_t inHdl, ncp_uint32_t inTreeId,
                       ncp_uint32_t inNumVPtns, ncp_vptn_t *inVPtns, 
                       ncp_ptn_action_t *inAction);

/*!
 * @ingroup _uvtree_APIs
 * @brief Unlearns a previously learned unordered virtual (UV) tree rule.
 * @details
 * Each of the virtual patterns' assigned virtual numbers is unlearned 
 *         from the respective source trees (if no other rule contains the 
 *         same virtual pattern). The virtual numbers are then concatenated 
 *         into the pattern which is unlearned from the UVTree.
 *         <br>
 *         The action specified needs to be an action for the default rule to 
 *         ensure application responsibility.
 *         <br>
 *         The default UVTree rule cannot be unlearned.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier (assigned by the control program) of the UVTree 
 *                 to update.
 * @param[in] inNumVPtns Number of virtual patterns in the rule.  
 * @param[in] inVPtns    Pointer to an array of instances of ncp_vptn_t, each 
 *                   defining a virtual pattern.
 * @param[in] inAction   Pointer to an instance of #ncp_ptn_action_t that defines
 *                   the action to be performed in conjunction with the rule 
 *                   (this needs to be the action of the default rule).
 * @param[in] compact Specifies whether to compact memory after the unlearn 
 *                operation:
 *                false = Do not compact memory
 *                true = Compact memory
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_uvtree_unlearn(ncp_hdl_t inHdl, ncp_uint32_t inTreeId,
                       ncp_uint32_t inNumVPtns, ncp_vptn_t *inVPtns, 
                       ncp_ptn_action_t *inAction, ncp_bool_t compact);

/*!
 * @ingroup _uvtree_APIs
 * @brief Unlearn all rules in the UVTree
 * @details
 * This API performs three actions as part of unlearning all rules in
 *         the specified UVTree:
 *       <ul>
 *        <li> Clears all the virtual numbers assigned to the virtual patterns 
 *             of all rules</li>
 *        <li> Deletes the virtual number reference count tables</li>
 *        <li> Unlearns all rules from the UVTree </li>
 *      </ul>
 *      When any of the source functions (virtual patterns) of this UVTree are 
 *      a part of another UVTree, the application must use 
 *      ncp_uvtree_unlearn_any on the other UVTree also because the virtual 
 *      numbers are cleared for that source function.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier (assigned by the control program) of the UVTree 
 *                 to update.
 * @param[in] inAction Pointer to an instance of an #ncp_ptn_action_t that defines 
 *                 the action to be performed in conjunction with the rule 
 *                 (this needs to be the action of the default rule and is the 
 *                  application's responsibility).
 * @param[in] compact Flag that specifies whether compression should be run after 
 *                the unlearn process
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_uvtree_unlearn_any(ncp_hdl_t inHdl, ncp_uint32_t inTreeId,
                           ncp_ptn_action_t *inAction, ncp_bool_t compact);


/*!
 *  @defgroup _dfmm_APIs Dynamic Flow Memory Management
 *  @ingroup _ptn_Pattern
 *  @brief
 *  These APIs are used to dynamically manage flow memory for modules
 *  @details
 *  The DFMM feature allows application to organize FPL flow functions into modules and specify
 *  at runtime, which flow functions reside in flow memory. This feature is for those environments
 *  where multiple services need to be supported (albeit, not at the same time) and the amount of
 *  flow code for all these services exceeds the amount of flow memory on the chip. The FPL MODULE
 *  is extended and exported to the API to be managed as an object. These APIs allow the application
 *  to load/unload a module (a set of flow functions contained in it) into flow memory at runtime.
 ***************************************************************************************************/


/*!
 * @ingroup _dfmm_APIs
 * @brief Determines whether dynamic loading is enabled
 * @details
 * This feature is a configuration option and if this feature is not 
 *         enabled, none of the subsequent APIs can be used.
 *         In addition, this API also returns the size of the largest flow 
 *         function, a key parameter which determines how memory efficient 
 *         modules can be
 * @param[in] inHdl The handle to the NCP.
 * @param[in] dynamicLoading Specifies if this module is dynamically loadable.
 * @param[out] largestFlowSize Returns the largest flow size.
 * @param[out] flowMemLeft Returns the amount of flow Memory left.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *         </ul>
 */
NCP_API ncp_st_t
ncp_ptn_module_mode(ncp_hdl_t inHdl, ncp_bool_t *dynamicLoading,
                   ncp_uint32_t *largestFlowSize, ncp_uint32_t *flowMemLeft);

/*!
 * @ingroup _dfmm_APIs
 * @brief Query the name of the largest flow function.
 * @details
 * This API is used to query the name of the largest flow function when
 * dynamic loading is enabled.  The returned name is a pointer into the 
 * AGEN memory and should <b>NOT</b> be freed.
 * @param[in] inHdl The handle to the NCP.
 * @param[out] name  A pointer into the API memory.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_MODE
 *         </ul>
 */
NCP_API ncp_st_t
ncp_ptn_module_largest_flow_name(ncp_hdl_t inHdl, char **name);

/*!
 * @ingroup _dfmm_APIs
 * @brief Retrieves statistics for all modules
 * @details
 * This API is used to retrieve the statistics for all modules. The user
 *         specified callback function is called for each module with the 
 *         agen_module_stats_t structure.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] cbfn The application callback function that is invoked at 
 *             regular intervals during the process.
 * @param[in] cbrock The rock is the cbrock specified by the user which is passed 
 *               through as an opaque object.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_MODE
 *         </ul>
 */

#ifndef SWIG
NCP_API ncp_st_t
ncp_ptn_module_stats(ncp_hdl_t inHdl, ncp_ptn_module_stats_fn_t cbfn, 
                     void *cbrock);
#endif /* #ifndef SWIG */

/*!
 * @ingroup _dfmm_APIs
 * @brief Retrieves the status of an individual module.
 * @details
 * The module is identified by name and the API returns the size of the
 * module and whether the module is currently executing from flow memory
 * or not.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] name  The name of the module.
 * @param[out] size  The size of the module is filled in here.
 * @param[out] inFlowMemory Flag indicating whether the module is currently 
 *                     executing in flow memory.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_MODE
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_module_status(ncp_hdl_t inHdl, const char *name, ncp_uint32_t *size,
                     ncp_bool_t *inFlowMemory);

/*!
 * @ingroup _dfmm_APIs
 * @brief This API is used to load a module into flow memory. 
 * @details
 * If the module is already executing from flow memory, it does nothing.
 *         For the API to be successful, there must be enough free space 
 *         available in the flow memory. 
 *         If the space is not available, it will return an error
 * @param[in] inHdl The handle to the NCP.
 * @param[in] name The name of the module.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_MODE
 *           <li> #NCP_ST_AGEN_INVALID_MODULE_NAME
 *           <li> #NCP_ST_AGEN_NO_FLOW_MEMORY
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_module_load(ncp_hdl_t inHdl, const char *name);

/*!
 * @ingroup _dfmm_APIs
 * @brief Unloads the module from flow memory 
 * @details
 * The unloaded module exists in tree memory and any paths which 
 *         invoke functions in this module will still function, though there 
 *         will be considerable performance degradation.
 * @param inHdl The handle to the NCP.
 * @param name The name of the module.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_MODE
 *           <li> #NCP_ST_AGEN_INVALID_MODULE_NAME
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_module_unload(ncp_hdl_t inHdl, const char *name);

/*!
 * @ingroup _dfmm_APIs
 * @brief Unloads all modules from flow memory
 * @details
 * The unloaded modules exists in tree memory and any paths which 
 *         invoke functions in these modules will still function, though there 
 *         will be considerable performance degradation.
 * @param[in] inHdl The handle to the NCP.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_MODE
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_module_unload_all(ncp_hdl_t inHdl);

/*!
 * @ingroup _dfmm_APIs
 * @brief Overwrites default function call delay
 * @details
 * This API is used to overwrite the default function call delay used by the
 * AGEN when relocating flow functions around. Due to the nature of how 
 * hardware executes function calls, when a flow function is moved to 
 * another location, the resulting free space cannot be reused until
 * any contexts executing function calls within this flow code are finished.
 * Since there is no hardware mechanism to track contexts, we need to
 * impose a worst case number for this delay. The AGEN uses a default of
 * 11 milliseconds and the caller (API) can change this by using this
 * API.
 * This API is not externalized to the application in the chipset APIs
 * since the API itself calculates this based on chip configuration and sets it.
 * @param[in] inHdl  The handle to the NCP.
 * @param[in] delay  delay in milliseconds.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *         </ul>
 */
NCP_API ncp_st_t
ncp_ptn_module_set_function_call_delay(ncp_hdl_t inHdl, ncp_uint32_t delay);



/*!
 *  @defgroup _stree_APIs Scan Tree
 *  @ingroup _ptn_Pattern
 *  @brief
 *  These APIs are used to manage scan trees
 *  @details
 *  The SCANTREE construct is used to perform regular expression matching. These APIs are used to
 *  add, clear and build regular expression patterns in a tree structure.
 *  The new set of expressions does not take effect until the build function is called.
 ***************************************************************************************************/



/*!
 * @ingroup _stree_APIs
 * @brief Determines the number of rules in STree with id inTreeId.
 * @details
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier of the Scan tree
 * @param[out] outNumRules The number of rules found.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_stree_norules(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                      ncp_uint32_t *outNumRules);

/*!
 * @ingroup _stree_APIs
 * @brief Deletes all the rules from an STree.
 * @details
 * The tree structure in hardware is not affected. This function simply clears the in-memory list of rules.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId The id of the scan tree to clear.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_stree_clear(ncp_hdl_t inHdl, ncp_uint32_t inTreeId);

/*!
 * @ingroup _stree_APIs
 * @brief Adds a scan rule to the specified Scan tree.
 * @details
 * The tree structure in hardware is not affected. This function simply modifies the in-memory list of rules.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId The id of the scan tree.
 * @param[in] inExpr   The scan rule to add.
 * @param[in] inAction   Pointer to an instance of #ncp_ptn_action_t that defines 
 *                   the action to be performed in conjunction with the rule.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_SCAN_REGEX_MISSING_PAREN
 *           <li> #NCP_ST_AGEN_SCAN_REGEX_MISSING_BRACE
 *           <li> #NCP_ST_AGEN_SCAN_REGEX_INVALID_INTERVAL
 *           <li> #NCP_ST_AGEN_SCAN_REGEX_MALFORMED_QUANTIFIER
 *           <li> #NCP_ST_AGEN_SCAN_REGEX_UNEXPECTED_TOKEN
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_stree_add(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                  const char *inExpr, ncp_ptn_action_t *inAction);

/*!
 * @ingroup _stree_APIs
 * @brief Retrieves a scan rule from a scan tree
 * @details
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId The id of the scan tree.
 * @param[in] inId The rule id
 * @param[out] outExpr The scan expression 
 * @param[out] outAction The action associated with the scan expression
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_INDEX
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 * 
 */

NCP_API ncp_st_t
ncp_ptn_stree_get(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                  ncp_uint32_t inId, const char **outExpr, 
                  ncp_ptn_action_t *outAction);

/*!
 * @ingroup _stree_APIs
 * @brief Builds a scan tree.
 * @details
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId The id of the scan tree.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
NCP_API ncp_st_t
ncp_ptn_stree_build(ncp_hdl_t inHdl, ncp_uint32_t inTreeId);

/*!
 * @internal
 * API to plot the DFA (should only be called right after fpo 
 *         load or a rebuild). This API generates output in a format suitable 
 *         to view using graphviz
 */
#ifndef SWIG
NCP_API ncp_st_t
ncp_ptn_stree_plot(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, ncp_write_fn_t wrfn, void *arg);
#endif /* #ifndef SWIG */

/*!
 * @internal
 * API to plot the program. The format of this is proprietary and has no
 * documentation or support. Used for internal debugging 
 */
#ifndef SWIG
NCP_API ncp_st_t
ncp_ptn_plot_program( ncp_hdl_t inHdl, ncp_write_fn_t wrfn, void *rock );
#endif /* #ifndef SWIG */


/*!
 *  @defgroup _misc_APIs Miscellaneous
 *  @ingroup _ptn_Pattern
 *  @brief
 *  These are miscellaneous APIs.
 *  @details
 ***************************************************************************************************/

/*!
 * @ingroup _misc_APIs
 * @brief Checks the hardware memory with the host based copy
 * @details
 * Checks the program memory image with the shadow copy kept by 
 *         the API, to verify that the FPO program and all associated pattern 
 *         API operations are correctly reflected in the hardware program memory
 * @param[in] inHdl The handle to the NCP.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *         </ul>
 */
NCP_API ncp_st_t 
ncp_ptn_check_program_image(ncp_hdl_t inHdl);


/*!
 * @ingroup _misc_APIs
 * @brief Checks the program memory image against the shadow image copy kept 
 *        by the host to verify that the FPO program and pattern API 
 *        operations are reflected correctly in the hardware program memory
 * @details
 * This process is time consuming because every address must be read 
 *         from the hardware and compared to the shadow copy. This implies
 *         application cannot respond to higher-priority operations until this
 *         process is finished. This function invokes the application specified
 *         callback periodically. The callback function 
 *         returns a code instructing the operation to abort. The comparison 
 *         is halted and an error code is returned to the application.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] cbfn  The application callback function that is invoked at regular 
 *              intervals during the process.
 * @param[in] cbrock Application-specified opaque value that is passed to the 
 *               callback function.
 * @param[in] cbfrequency Specifies the frequency at which the callback function 
 *                    is invoked. The value must be 1 or higher. A lower value 
 *                    indicates higher frequency. In some cases, the frequency 
 *                    is directly related to the number of memory instructions 
 *                    processed as the comparison algorithm sequentially reads 
 *                    the memory.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *         </ul>
 */
#ifndef SWIG
NCP_API ncp_st_t 
ncp_ptn_check_program_image_cb(ncp_hdl_t inHdl, ncp_ptn_cb_fn_t cbfn, void *cbrock,
                        ncp_uint32_t cbfrequency);
#endif /* #ifndef SWIG */

/*!
 * @ingroup _misc_APIs
 * @brief Sets the autoflush flag to the specified value.
 * @details
 * Most NCP pattern APIs result in a sequence of writes to 
 *         program memory. Typically these writes are buffered in the API 
 *         so they can be sent over the configuration bus as a single block 
 *         instead of multiple transfers. The maximum number of writes that 
 *         are buffered is 64.
 *         <br>
 *         However, for typical applications the average number of writes 
 *         per #ncp_ptn_learn operation can be significantly lower than the 
 *         buffer size (typically 8-10 writes). Since the API does not control 
 *         when the pattern APIs are invoked, at the end of each operation any 
 *         outstanding writes are flushed before returning to the application. 
 *         This can result in under utilization of the block transfer mechanism,
 *         a situation in which a much smaller number of writes than optimum 
 *         are sent to the system at the end of each operation.
 *         <br>
 *         The autoflush flag controls whether a flush operation is executed 
 *         at the end of each operation. Setting this flag to FALSE disables 
 *         this end-of-operation flushing. Setting the flag to TRUE enables 
 *         this mode and also flushes any remaining writes. Typically this 
 *         mechanism is used when application knows it has to perform a 
 *         series of operations and wishes to optimize the performance.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] value Specifies the value for the autoflush flag: 
 *              false = Do not auto flush 
 *              true = Auto flush at end of each operation
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *         </ul>
 */

NCP_API ncp_st_t 
ncp_ptn_agen_set_autoflush(ncp_hdl_t inHdl, ncp_bool_t value);

/*!
 * @ingroup _misc_APIs
 * @brief Flushes any buffered writes to the hardware program memory.
 * @details
 * @param[in] inHdl The handle to the NCP.
 * When the autoflush mechanism is disabled, this API can be used to 
 *         flush any remaining writes.
 */

NCP_API ncp_st_t 
ncp_ptn_agen_flush(ncp_hdl_t inHdl);

/*!
 * @ingroup _misc_APIs
 * @brief Look up a function name in the function table and return the id.
 * @details
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inName The name to lookup. This needs to be a fully qualified name - if the
 *          function exists within a module, name needs to be in the format
 *              <module name>.<function name>
 * @param[out] outId A pointer to the unsigned integer which will contain the id.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_SYMBOL_NOT_FOUND
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_symbol_get_id(ncp_hdl_t inHdl, const char *inName, ncp_uint32_t *outId);


/*!
 * @internal
 * @defgroup _eaction_APIs Extended Action
 * @brief These APIs allow the application to modify a tree's action directly for highly responsive
 *        situations
 * @details
 * The EACTION feature.
 * The following section contains the definitions for the EACTION feature.
 * Essentially, the customer wants a way to quickly modify the return
 * values of some limited set of patterns in LPM trees. The idea is that
 * if a link goes down, there is a mechanism to remap packets to another
 * link on a real-time basis. 
 * Normally, this would be expected to be done through a #ncp_ptn_learn
 * on the tree. However, the AGEN is not multi-threaded, nor reentrant and
 * all operations are expected to be performed sequentially. If the AGEN
 * is currently in the middle of an expensive operation, the application would
 * have to wait for this to finish, which is not acceptable.
 * The idea is to have a side mechanism where the application can perform
 * limited modifications on the hardware without going through the AGEN
 * and at some point, update the AGEN's shadow copy. In order to do this,
 * the application needs to know the memory address where the return value
 * of a pattern is stored.
 *
 * See above for definition of an ncp_ptn_eaction_t structure. This structure
 * contains the handle, virtual handle, some opaque attributes (known only to
 * the code) and a memory address. The ncp_ptn_list_ptns_any_eaction API allows
 * the application to dump the pattern(s) in a tree with the eaction_t
 * structure (as opposed to the ncp_ptn_list_ptns_any which returns the
 * ncp_ptn_action_t structure).
 * At startup time, the application would retrieve the eaction_t structures
 * for each of the patterns in the tree it is interested in (these patterns
 * are expected to be specific patterns; if it is a subnet, there may be
 * multiple eaction_t structures).
 * When a real-time change needs to be done, the application would modify
 * the handle and virtual handle in the eaction_t structure and call the
 * ncp_ptn_modify_eaction_hw() to propagate this change to the hardware
 * memory.
 * At this point, the AGEN's shadow copy is out of sync with the hardware.
 * At some point, the application should perform a ncp_ptn_modify_eaction_shadow()
 * to make the same change to this shadow copy.
 *
 * Notes:
 *   Needless to say, this feature is expected to be used sparingly because
 *   of the inherent dangers in keeping the AGEN's view out of sync. Also,
 *   the application should not perform regular learn operations on trees 
 *   handled in this fashion.
 *   This feature is only valid to modify return values. If a pattern's
 *   action is to go to another function, that is not supported.
 ****************************************************************************/

/*!
 * @internal
 * @ingroup _eaction_APIs
 * @brief List the patterns with the action returned with extra attributes in the eaction structure
 * @details
 * Since Agen needs to single thread memory access, the
 *         application must perform all tree operations sequentially. 
 *         Some of these operations are time intensive and can impede the 
 *         ability to respond in real-time, even if the only action required 
 *         is remapping pattern return values. Specifically, this feature 
 *         provides structures and interfaces that allow the application to
 *         change pattern return values of regular Longest Pattern Match (LPM) 
 *         trees directly in hardware memory and later, to update the 
 *         AGen shadow copy. This API is used by the application to traverse 
 *         the tree at start up time and have the AGen retrieve the 
 *         ag_fpp_eaction_t structures for interesting patterns. This API is 
 *         similar to ncp_ptn_list_ptns_any  except that it returns the 
 *         ncp_ptn_eaction_t structure.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId The pattern tree in which the lookup is to performed.
 * @param[in] inPtn    Pointer to an instance of an ncp_ptn_t that defines the 
 *                 pattern to be looked up.
 * @param[in] listfn   The application-specified callback function.
 * @param[in] rock     An application-specified opaque value that is passed to 
 *                 the callback function.
 *        real-time basis, temporarily bypassing the Algorithm Generator (AGen).
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_AGEN_INVALID_OP
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
#ifndef SWIG
ncp_st_t 
ncp_ptn_list_ptns_any_eaction(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                              ncp_ptn_t *inPtn, 
                              ncp_ptn_list_ptns_eaction_fn_t listfn, 
                              void *rock);
#endif /* #ifndef SWIG */

/*!
 * @internal
 * @ingroup _eaction_APIs
 * @brief Modify the handle return values directly in hardware memory
 * @details
 * This API can be invoked concurrently with another API executing in 
 *         the Algorithm Generator (AGen). This API bypasses the AGen 
 *         structures and writes the new handle directly in hardware memory.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] Pointer to the callback ncp_ptn_eaction_t for each pattern in the tree
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_AGEN_INVALID_OP
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_modify_eaction_hw(ncp_hdl_t inHdl, ncp_ptn_eaction_t *eaction);

/*!
 * @internal
 * @ingroup _eaction_APIs
 * @brief This API modifies the Algorithm Generator (AGen) structures and 
 *        must be executed sequentially with other standard operations such 
 * @details
 * This API is used to keep the AGen shadow copy synchronized with the 
 *         hardware memory. The two become unsynchronized when 
 *         ncp_ptn_modify_eaction_hw calls are made.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] eaction Pointer to the callback ncp_ptn_eaction_t structure for each 
 *                pattern in the tree.
 *        as ncp_ptn_learn
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_AGEN_INVALID_OP
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_modify_eaction_shadow(ncp_hdl_t inHdl, ncp_ptn_eaction_t *eaction);




/*!
 *  @defgroup _ovtreeset_APIs Ordered Virtual Tree Set
 *  @ingroup _ptn_Pattern
 *  @brief
 *  These APIs are used to manage ovtreeset rules
 *  @details
 *  The OVTREESET construct is used to implement access control lists. OVTREESET is a multi-field classification
 *  construct where the patterns are ranges. Additionally, the first field is treated as a set id and
 *  the rules are organized and built based on the set id. 
 *  The data structure ncp_ptn_t is used to represent a setid. A set id can only be one of two types -
 *  a fully specified value (no wildcard bits) or the full default (no data bits).
 *  The remaining fields are expressed in the ncp_rptn_t data structure. This structure specifies
 *  a range. For those fields in the OVTREESET that are denoted as LPM only, the range in the
 *  ncp_rptn_t structure must degenerate into an LPM (subnet pattern). For fields which are not
 *  denoted as LPM, any valid range can be specified.
 *  Any changes done using the  append, insert, modify, etc. APIs do not take effect until the build
 *  function is called.
 *  As with any tree, the user should have a default rule at the end as a catch all. Since each set of 
 *  rules is built independantly, there should be a default rule for each set (a rule with the first 
 *  field being the set id and the rest of the fields being the default patterns). If there is no 
 *  default rule, each set is created to invoke the error handler in case of a no-match.
 *  A default value for the set id indicates the default set.
 *
 *  Removal of a set can be accomplished by clearing all the rules for the set and building it. At this 
 *  point, the API recognizes that the set needs to be removed and unlearns it to the default set. 
 *  Any patterns with that set id  will now be matched to the rules for the default set. The default 
 *  set itself cannot be removed. When this set contains no rules, the set will be constructed to go 
 *  to the error handler.
 ***************************************************************************************************/


/*!
 * @ingroup _ovtreeset_APIs
 * @brief Deletes all the rules from an Ovtreeset rule set.
 * @details
 * This API is used to clear a set of rules. The set is identified by 
 *     inSetId. As per the definition of an Ovtreeset, this field value can either 
 *     be a fully specified value or the full default (no subnet).
 *     If inSetId is NULL, all sets are cleared. In this way, the entire set of
 *     rules for all sets can be deleted.
 * The tree structure in hardware is not affected. This function simply clears the in-memory list of rules.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier of the Ovtreeset to clear.
 * @param[in] inSetId   Set identifier. Can be the default set, NULL, or a specific 
 *                 set.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_XSIZE
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
NCP_API ncp_st_t
ncp_ptn_ovtreeset_clear(ncp_hdl_t inHdl, ncp_uint32_t inTreeId,
                        ncp_ptn_t* inSetId);
/*!
 * @ingroup _ovtreeset_APIs
 * @brief Prepends a new rule to the Ovtreeset
 * @details
 * The set to which the rule gets prepended to is specified in inSetId. As per the 
 *         definition of an Ovtreeset, this field value can either be a fully specified
 *         value or the full default (no subnet).
 * The remaining fields are specified as an array of ncp_rptn_t structures.
 * The tree structure in hardware is not affected. This function simply appends the rule to the in-memory list of rules.
 * @param[in] inHdl      The handle to the NCP.
 * @param[in] inTreeId   Identifier of the Ovtreeset.
 * @param[in] inSetId    The set id
 * @param[in] inNoRPtns  Number of range patterns in the rule.
 * @param[in] inRPtns    Pointer to an array of instances of #ncp_rptn_t, each 
 *                   defining a range pattern.
 * @param[in] inAction   Pointer to an instance of an #ncp_ptn_action_t structure 
 *                   that defines the action to be performed in conjunction 
 *                   with the rule.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_XSIZE
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
NCP_API ncp_st_t
ncp_ptn_ovtreeset_prepend(ncp_hdl_t inHdl, ncp_uint32_t inTreeId,
                          ncp_ptn_t* inSetId, ncp_uint32_t inNoRPtns, ncp_rptn_t* inRPtns,
                          ncp_ptn_action_t *inAction);
/*!
 * @ingroup _ovtreeset_APIs
 * @brief Adds new rules to the end of an Ovtreeset rule set.
 * @details
 * This API is used to append a new rule to the Ovtreeset. The set to 
 *         to which the rule gets appended to is specified in inSetId. As per the 
 *         definition of an Ovtreeset, this field value can either be a fully specified
 *         value or the full default (no subnet).
 * The remaining fields are specified as an array of ncp_rptn_t structures.
 * The tree structure in hardware is not affected. This function simply appends the rule to the in-memory list of rules
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier (assigned by the control program) of the OvtreeSet
 *                 to update.
 * @param[in] inSetId    The set id
 * @param[in] inNoRPtns  Number of range patterns in the rule.
 * @param[in] inRPtns    Pointer to an array of instances of #ncp_rptn_t, each 
 *                   defining a range pattern.
 * @param[in] inAction   Pointer to an instance of #ncp_ptn_action_t that defines 
 *                   the action to be performed in conjunction with the rule.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_XSIZE
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
NCP_API ncp_st_t
ncp_ptn_ovtreeset_append(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                        ncp_ptn_t* inSetId, ncp_uint32_t inNoRPtns, ncp_rptn_t* inRPtns,
                        ncp_ptn_action_t *inAction);
/*!
 * @ingroup _ovtreeset_APIs
 * @brief Inserts a new rule at the specified index to the Ovtreeset
 * @details
 * The set to identified by inSetId. As per the 
 *         definition of an Ovtreeset, this field value can either be a fully specified
 *         value or the full default (no subnet).
 * The maximum value of index can be number of rules (indices start at 0).
 * The remaining fields are specified as an array of ncp_rptn_t structures.
 * The tree structure in hardware is not affected. This function simply inserts the rule to the in-memory list of rules.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier of the Ovtreeset.
 * @param[in] inIndex  The index within the Ovtreeset at which to insert the rule.
 * @param[in] inSetId    The set id
 * @param[in] inNoRPtns  Number of range patterns in the rule.
 * @param[in] inRPtns    Pointer to an array of instances of #ncp_rptn_t, each 
 *                   defining a range pattern.
 * @param[in] inAction   Pointer to an instance of #ncp_ptn_action_t that defines 
 *                   the action to be performed in conjunction with the rule
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_XSIZE
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_AGEN_INVALID_INDEX
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
NCP_API ncp_st_t
ncp_ptn_ovtreeset_insert(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, ncp_uint32_t inIndex,
                        ncp_ptn_t* inSetId, ncp_uint32_t inNoRPtns, ncp_rptn_t* inRPtns,
                        ncp_ptn_action_t *inAction);
/*!
 * @ingroup _ovtreeset_APIs
 * @brief Deletes a rule at the specified index from the specified set of an Ovtreeset.
 * @details
 * The set is identified by inSetId. As per the definition of an Ovtreeset,
 * this value can either be a fully specified value or the full default 
 * (no subnet). The index has to identify a valid rule 
 * (range is 0 to novrules - 1).
 * The tree structure in hardware is not affected. This function simply deletes the in-memory list of rules.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier of the Ovtreeset.
 * @param[in] inIndex  The index within the Ovtreeset at which to delete the rule.
 * @param[in] inSetId   Set identifier. Can be the default set, NULL, or a 
 *                 specific set.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_XSIZE
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_AGEN_INVALID_INDEX
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
NCP_API ncp_st_t
ncp_ptn_ovtreeset_delete(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                        ncp_uint32_t inIndex, ncp_ptn_t *inSetId);
/*!
 * @ingroup _ovtreeset_APIs
 * @brief Replaces a rule at the specified index in the specified set of an Ovtreeset. 
 * @details
 * The set is identified by inSetId. As per the 
 *         definition of an Ovtreeset, this field value can either be a fully specified
 *         value or the full default (no subnet).
 * The index has to identify a valid rule (range is 0 to novrules - 1). 
 * The remaining fields are specified as an array of ncp_rptn_t structures.
 * The tree structure in hardware is not affected. This function simply clears the in-memory list of rules.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier of the Ovtreeset.
 * @param[in] inIndex    The index within the Ovtreeset at which to insert the rule.
 * @param[in] inSetId    The set id
 * @param[in] inNoRPtns  Number of range patterns in the rule.
 * @param[in] inRPtns    Pointer to an array of instances of #ncp_rptn_t, each 
 *                   defining a range pattern.
 * @param[in] inAction   Pointer to an instance of #ncp_ptn_action_t that defines 
 *                   the action to be performed in conjunction with the rule.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_XSIZE
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_INVALID_ACTION
 *           <li> #NCP_ST_AGEN_INVALID_INDEX
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_ovtreeset_modify(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                        ncp_uint32_t inIndex, 
                        ncp_ptn_t* inSetId, ncp_uint32_t inNoRPtns, ncp_rptn_t* inRPtns,
                        ncp_ptn_action_t *inAction);
/*!
 * @ingroup _ovtreeset_APIs
 * @brief Retrieves number of rules in the Ovtreeset for the 
 *        specified set.
 * @details
 * The set is identified by inSetId. As per the definition of an 
 *          Ovtreeset, this field value can either be a fully specified value 
 *          or the full default (no subnet). The inSetId identifies the set on 
 *          which the operation is performed. If inSetId is NULL, the number of 
 *          rules for all of the sets is returned.  Please note that if the set does
 *          not exist then NCP_ST_AGEN_INVALID_PTN error is returned.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inTreeId Identifier of the Ovtreeset to clear.
 * @param[in] inSetId   Identifies the set in which to count the number of rules.
 * @param[out] outNumVRules Number of rules in the set.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_PTN
 *           <li> #NCP_ST_AGEN_INVALID_PTNWIDTH
 *           <li> #NCP_ST_AGEN_INVALID_XSIZE
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *         </ul>
 */
NCP_API ncp_st_t
ncp_ptn_ovtreeset_norules(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                          ncp_ptn_t *inSetId, ncp_uint32_t *outNumVRules);

#ifndef SWIG
typedef void (*ncp_ptn_list_ovsrules_fn_t)(void *rock, ncp_uint32_t treeId,
                                           ncp_ptn_t *setId,
                                           ncp_uint32_t ruleIdx,
                                           ncp_uint32_t noRPtns, ncp_rptn_t *rptns,
                                           ncp_ptn_action_t *action);
#endif /* #ifndef SWIG */
/*!
 * @ingroup _ovtreeset_APIs
 * @brief List the virtual rules for a set
 * @details
 * This API is used to list the virtual rules for a set. The set is 
 *     identified by inSetId. 
 *     As per the definition of an Ovtreeset, this field value can either
 *     be a fully specified value or the full default (no subnet).
 *     If inSetId is NULL, all sets are listed. In this way, the entire set of
 *     rules for all sets can be retrieved.
 *     The user specified callback function listfn is invoked for each rule
 *     The rules listed are what the user added using the ovtreeset_append() API.
 *     If the rules were deleted using the ovtreeset_clear() API, no rules are listed.
 * @param[in] inHdl    The handle to the NCP.
 * @param[in] inTreeId Identifier of the Ovtreeset for which you want to list rules.
 * @param[in] inSetId   Set identifier. Can be the default set, NULL, or a 
 *                 specific set.
 * @param[in] listfn   The application-specified callback function. This function 
 *                 is invoked for a virtual rule.
 * @param[in] rock     An application-specified opaque value that is passed to the 
 *                 callback function, listfn.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
#ifndef SWIG
NCP_API ncp_st_t 
ncp_ptn_ovtreeset_list_rules(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                             ncp_ptn_t *inSetId, 
                             ncp_ptn_list_ovsrules_fn_t listfn, void *rock);
#endif /* #ifndef SWIG */


/*!
 * @ingroup _ovtreeset_APIs
 * @brief  Builds an Ovtreeset with the new set of rules.
 * @details
 * This API is used to build/rebuild a set of rules. The set is 
 *         identified by inSetId. As per the definition of an Ovtreeset, this 
 *         field value can either be a fully specified value or the full 
 *         default (no subnet). If inSetId is NULL, all sets are rebuilt. 
 *         In this way, the entire set of rules for all sets can be rebuilt.
 * @param inHdl The handle to the NCP.
 * @param inTreeId Identifier of the Ovtreeset to build.
 * @param inSetId   Set identifier. Can be the default set, NULL, or a 
 *                 specified set.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
NCP_API ncp_st_t
ncp_ptn_ovtreeset_build(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                       ncp_ptn_t *inSetId);

/*!
 * @ingroup _ovtreeset_APIs
 * @brief Identical to #ncp_ptn_ovtreeset_build, 
 *         except that application can specify a callback function to invoke 
 *         in the middle of processing.
 * @details
 * Since OVTREESET building is an expensive and time-consuming process, this
 * callback provides the application a window to handle other tasks.
 * Unlike other APIs which support callback functions, the OVTREESET callback
 * function CANNOT abort processing in the middle. The return value of the
 * callback is ignored and processing continues until the OVTREESET is rebuilt.
 * The cbfrequency provides the application a very coarse granularity on
 * the frequency of callbacks. Though OVTREESET building comprises of many
 * distinct stages, two of these stages are the most time consuming and
 * the callback functionality is provided in these stages. 
 * In the first stage, all the rules and field values are analyzed together
 * and converted into a directed graph. In this stage, the cbfrequency number
 * loosely relates to the number of rules processed. Since the processing time
 * of each rule can vary widely (depends on how the rule and it's values relate
 * to the preceding rules), this does not denote any defined time period.
 * In the second stage, each node in the directed graph is analyzed and
 * converted into a set of hardware instructions. In this stage, the cbfrequency
 * is related to the number of nodes processed.
 * To reiterate, the cbfrequency is a very coarse knob to control the frequency
 * of callbacks. Value should be > 0. Recommended to be >= 50.
 * @param[in] inHdl  The handle to the NCP.
 * @param[in] fnid The Function id
 * @param[in] inSetId   Set identifier. Can be the default set, NULL, or a specific 
 *                 set.
 * @param[in] cbfn The application callback function that is invoked at 
 *             regular intervals during the process.
 * @param[in] cbrock Application-specified opaque value that is passed to the 
 *               callback function.
 * @param[in] cbfrequency Specifies the frequency at which the callback function 
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_CB_ABORT
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
#ifndef SWIG
NCP_API ncp_st_t
ncp_ptn_ovtreeset_build_cb(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                           ncp_ptn_t *inSetId, ncp_ptn_cb_fn_t cbfn, 
                           void *cbrock, ncp_uint32_t cbfrequency );
#endif /* #ifndef SWIG */


/*!
 * @ingroup _ovtreeset_APIs
 * @brief  Rebuilds the entire Ovtreeset with the new set of rules.
 * @details
 * This API is used to rebuild a set of rules. All sets are rebuilt.
 * @param inHdl The handle to the NCP.
 * @param inTreeId Identifier of the Ovtreeset to build.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
NCP_API ncp_st_t
ncp_ptn_ovtreeset_rebuild(ncp_hdl_t inHdl, ncp_uint32_t inTreeId);

/*!
 * @ingroup _ovtreeset_APIs
 * @brief Identical to #ncp_ptn_ovtreeset_rebuild, 
 *         except that application can specify a callback function to invoke 
 *         in the middle of processing.
 * @details
 * Since OVTREESET building is an expensive and time-consuming process, this
 * callback provides the application a window to handle other tasks.
 * Unlike other APIs which support callback functions, the OVTREESET callback
 * function CANNOT abort processing in the middle. The return value of the
 * callback is ignored and processing continues until the OVTREESET is rebuilt.
 * The cbfrequency provides the application a very coarse granularity on
 * the frequency of callbacks. Though OVTREESET building comprises of many
 * distinct stages, two of these stages are the most time consuming and
 * the callback functionality is provided in these stages. 
 * In the first stage, all the rules and field values are analyzed together
 * and converted into a directed graph. In this stage, the cbfrequency number
 * loosely relates to the number of rules processed. Since the processing time
 * of each rule can vary widely (depends on how the rule and it's values relate
 * to the preceding rules), this does not denote any defined time period.
 * In the second stage, each node in the directed graph is analyzed and
 * converted into a set of hardware instructions. In this stage, the cbfrequency
 * is related to the number of nodes processed.
 * To reiterate, the cbfrequency is a very coarse knob to control the frequency
 * of callbacks. Value should be > 0. Recommended to be >= 50.
 * @param[in] inHdl  The handle to the NCP.
 * @param[in] fnid The Function id
 * @param[in] cbfn The application callback function that is invoked at 
 *             regular intervals during the process.
 * @param[in] cbrock Application-specified opaque value that is passed to the 
 *               callback function.
 * @param[in] cbfrequency Specifies the frequency at which the callback function 
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_FUNC
 *           <li> #NCP_ST_AGEN_INVALID_TREE
 *           <li> #NCP_ST_AGEN_CB_ABORT
 *           <li> #NCP_ST_AGEN_MEM_OVERFLOW
 *           <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
#ifndef SWIG
NCP_API ncp_st_t
ncp_ptn_ovtreeset_rebuild_cb(ncp_hdl_t inHdl, ncp_uint32_t inTreeId, 
                           ncp_ptn_cb_fn_t cbfn, 
                           void *cbrock, ncp_uint32_t cbfrequency );
#endif /* #ifndef SWIG */



/*!
 * @ingroup _ptn_Pattern
 * @struct ncp_ptn_list_t
 * @brief Represents a list of patterns
 * @details
 * This structure is used to represent a list of #ncp_ptn_t values. 
 * noPtns identifies the number of patterns
 * ptns is an array of pointer to #ncp_ptn_t structures
 */
typedef struct
{
    ncp_uint32_t        noPtns;                 /*!< Number of patterns */
    ncp_ptn_t**         ptns;                   /*!< Array of pointers to ncp_ptn_t structures */
} ncp_ptn_list_t;         

/*!
 * @ingroup _misc_APIs
 * @brief Expands a range pattern into a list of LPM patterns
 * @details
 * This API takes a range and expands it into a list of subnet patterns. The FPL trees do not accept
 * range as an input. If application deals in ranges, this API can be used to expand it into a set of LPM
 * patterns, accepted by FPL trees.
 * @param[in]  inRange   The input range
 * @paran[out] outList   The resultant LPM patterns represented as ncp_ptn_t structrues
 * @return <ul>
 *              <li> #NCP_ST_SUCCESS
 *              <li> #NCP_ST_INVALID_PTN
 *              <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
NCP_API ncp_st_t 
ncp_ptn_expand_range(ncp_rptn_t* inRange, ncp_ptn_list_t* outList);

/*!
 * @ingroup _misc_APIs
 * @brief Frees a list of patterns returned by the ncp_ptn_expand_range API
 * @details
 * Frees a list of patterns returned by the ncp_ptn_expand_range API
 * @param[in]  inList   The pattern list containing the list of ncp_ptn_t structures to be freed
 * @return <ul>
 *              <li> #NCP_ST_SUCCESS
 *         </ul>
 */
NCP_API ncp_st_t 
ncp_ptn_free_ptn_list(ncp_ptn_list_t* list);

/*!
 * @ingroup _ptn_Pattern
 * @struct ncp_ptn_list_t
 * @brief Represents a list of rules (valid for multi-field classification trees such as Ovtree, Otree, etc.)
 * @details
 * This structure is used to represent a list of #ncp_ptn_list_t values. Each value represents a list of
 * #ncp_ptn_t patterns, representing a single rule across multiple classfication fields.
 * noRules identifies the number of rules
 * rules is an array of pointer to #ncp_ptn_list_t structures
 */
typedef struct {
    ncp_uint32_t        noRules;
    ncp_ptn_list_t**    rules;
} ncp_ptn_rules_t;

/*!
 * @ingroup _misc_APIs
 * @brief Expands a range based rule into a list of LPM pattern based rules
 * @details
 * This API takes a range based rule represented by inNoRPtns and inRPtns and expands it into a list
 * simple rules, which are based on LPM patterns, returning it in outRules
 * The FPL Otree/OtreeSet/Ovtree do not accept range based rules. If application deals in range based rules,
 * this API can be used to expand them into rules accepted by these trees.
 * @param[in]  inRange   The input range based rule
 * @paran[out] outList   The resultant LPM pattern based rules represented as ncp_ptn_list_t structrues
 * @return <ul>
 *              <li> #NCP_ST_SUCCESS
 *              <li> #NCP_ST_INVALID_PTN
 *              <li> #NCP_ST_NO_MEMORY
 *         </ul>
 */
NCP_API ncp_st_t
ncp_ptn_expand_range_rule(ncp_uint32_t inNoRPtns, ncp_rptn_t *inRPtns, ncp_ptn_rules_t* outRules);

/*!
 * @ingroup _misc_APIs
 * @brief Frees a list of rules returned by the ncp_ptn_expand_range_rule API
 * @details
 * Frees a list of rules returned by the ncp_ptn_expand_range_rule API
 * @param[in]  inRules   The rule list containing the list of ncp_ptn_list_t structures to be freed
 * @return <ul>
 *              <li> #NCP_ST_SUCCESS
 *         </ul>
 */
NCP_API ncp_st_t
ncp_ptn_free_ptn_rules(ncp_ptn_rules_t* inRules);

/*!
 * @ingroup _misc_APIs
 * @brief Map an address to a function and return the function name and id
 * @details
 * This API looks up an address and returns the containing function. The address could be
 * a flow or tree instruction address (typically the address passed to the error handler).
 * Please note that in certain situations, the compiler can break up a single user FPL rule
 * across compiler generated functions. This API simply returns whatever the containing
 * function is, which may be a compiler generated function and there is no translation done
 * to the original user defined function.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] inAddr The address to map
 * @param[out] outId A pointer to the unsigned integer which will contain the function id.
 * @param[out] outName The name of the matching function. This is a pointer to internal memory and should
 *                      not be freed
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_SYMBOL_NOT_FOUND
 *         </ul>
 */

NCP_API ncp_st_t
ncp_ptn_map_addr_to_symbol(ncp_hdl_t inHdl, ncp_uint32_t inAddr, ncp_uint16_t *outId, char **outName);


/*!
 * @ingroup _misc_APIs
 * @brief The ACP classification root memory scrub function
 * @details
 * The ACP V1, V2 and V3 have a problem with the hardware scrub functionality for the classification root memory
 * (internal classification memory - IMC). This API implements a software scrub to work around this issue.
 * Application needs to create a separate thread and call this API if root memory scrubbing is desired. 
 * This API sits in a loop periodically refreshing the root memory. This thread can be cancelled by invoking
 * the ncp_ptn_rootmem_scrub_cancel() API.
 * The classification root memory can be scrubbed at a very low rate (perhaps one pass over the entire memory every 
 * 4 days) to avoid double bit errors. The scrubIntervalInSecs parameter specifies this rate. This rate
 * is then divided into the amound of idle time between each memory write depending on the memory size
 * (maximum being 128K instructions). The thread sleeps for this interval between each memory access, which
 * again can be fairly large. If the entire memory scrub rate is 4 days (345000 seconds), the thread would 
 * sleep for around 2.6 seconds (128K instructions) between each memory access. The cancelResponseTimeInMilliSecs
 * specifies the interval within which the thread needs to respond to a cancel. The thread sleeps for
 * cancelResponseTimeInMilliSecs each time (checking for cancel) until it counts off the time between each address,
 * performs a single memory access and then goes back to sleep.
 * It is recommended that that the scrubIntervalInSecs is set for about 4.5 days and cancelResponseTimeInMilliSecs
 * set for about 100ms.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] scrubIntervalInSecs The rate at which the entire memory needs to be refreshed.
 * @param[in] cancelResponseTimeInMilliSecs The smallest time the thread will sleep to respond to cancel.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_INST
 *           <li> #NCP_ST_AGEN_INVALID_OP
 *         </ul>
 */
NCP_API ncp_st_t
ncp_ptn_rootmem_scrub(ncp_hdl_t inHdl, ncp_uint32_t scrubIntervalInSecs, ncp_uint32_t cancelResponseTimeInMilliSecs);

/*!
 * @ingroup _misc_APIs
 * @brief Cancels the ACP classification root memory scrub thread
 * @details
 * This API cancels the classification root memory scrubbing thread. If the wait flag is TRUE, it waits
 * until thread finishes and returns to the caller which can then exit the thread.
 * @param[in] inHdl The handle to the NCP.
 * @param[in] wait Indicates whether to wait until the thread sees the cancel request and returns
 *                 to the caller.
 * @param[out] outId A pointer to the unsigned integer which will contain the function id.
 * @param[out] outName The name of the matching function. This is a pointer to internal memory and should
 *                      not be freed
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_AGEN_INVALID_HDL
 *           <li> #NCP_ST_AGEN_INVALID_OP
 *         </ul>
 */
NCP_API ncp_st_t
ncp_ptn_rootmem_scrub_cancel(ncp_hdl_t inHdl, ncp_bool_t wait);

/*! @internal */
#ifndef SWIG
NCP_API ncp_st_t 
ncp_ptn_fpo_checkpoint_generate(ncp_hdl_t inHdl, ncp_write_fn_t wrfn, void *arg);
#endif /* #ifndef SWIG */
/*! @internal */
#ifndef SWIG
NCP_API ncp_st_t 
ncp_ptn_fpo_checkpoint_restore(ncp_hdl_t inHdl, ncp_read_fn_t rdfn, void *arg);
#endif /* #ifndef SWIG */

#ifdef SWIG
NCPTCL_WO_EXCEPTIONS();
#endif /* #ifdef SWIG */

/* Private (for simulator tests) */
NCP_API ncp_hdl_t ncp_ptn_get_hdl(void);

#ifndef SWIG
#ifdef __cplusplus
}
#endif /* #ifndef __cplusplus */
#endif /* #ifndef SWIG */

#endif /* #ifndef _NCP_PATTERN_H_ */

