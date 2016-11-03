/***************************************************************************
 **                                                                        *
 **                          Intel CONFIDENTIAL            *
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
 **************************************************************************/

/*! @file      ncp_dpt.h
 *  @brief     Dense Page Table Functions
 */

#ifndef _NCP_DPT_H
#define _NCP_DPT_H

#include "ncp_types.h"
#include "ncp_bitmap.h"

/*!
 *  @ingroup    _unexported_fns
 * 
 *  @{
 *
 *  @addtogroup _dpt_fns         Dense Page Table Fns
 */

#ifdef __cplusplus
extern "C" { 
#endif

/* opaque type */

typedef void* ncp_dpt_t;

/*!
 *  @fn ncp_dpt_create_table( ncp_uint32_t tableSize, ncp_uint32_t pageSize)
 *  @brief create dense page table.
 */
NCP_API ncp_dpt_t* ncp_dpt_create_table(
    ncp_uint32_t tableSize,
    ncp_uint32_t pageSize);

/*!
 * @fn ncp_dpt_delete_nodes_and_table(ncp_dpt_t *dpt,dptNodeDeleteFn_t delFn)
 * @brief When finished with a ncp_dpt_t this function will delete it. 
 *        After this function is called. the pointer to the ncp_dpt_t has 
 *        been freed and should not be used.
 * @ret   void
 */
typedef int (*dptNodeDeleteFn_t)( void *node);

NCP_API void ncp_dpt_delete_nodes_and_table(ncp_dpt_t *dpt,dptNodeDeleteFn_t delFn);

/*!
 * @fn ncp_dpt_get(ncp_dpt_t *dpt, ncp_uint32_t key)
 * @brief  To get a value out of the ncp_dpt_t that was put in under key. 
 *         If NULL is returned then no match was found.
 * @ret    void *
 */
NCP_API void *ncp_dpt_get(ncp_dpt_t *dpt, ncp_uint32_t key);

/*!
 * ncp_dpt_put()
 *   To put a value into the ncp_dpt_t under key. If a value was previously
 *   in the table under this key, then it is returned.
 */
NCP_API int ncp_dpt_put(ncp_dpt_t *dpt, ncp_uint32_t key, void *value, void **old_value);

/*!
 * @fn ncp_dpt_pick_key(ncp_dpt_t *dpt, ncp_uint32_t *outKey)
 * @brief  Select an optimal key, based upon the current page usage.
 *         No dpt state is modified.
 * @ret  int
 */
NCP_API int ncp_dpt_pick_key(ncp_dpt_t *dpt, ncp_uint32_t *outKey); 

/*! 
 * @fn ncp_dpt_put_pick_key(ncp_dpt_t *dpt, void *value, ncp_uint32_t *outKey)
 * @brief Allow the dpt API to pick the "best" key. The key value is returned.
 * The decision is made so that the page tables are kept as dense as possible.
 * 
 * @ret int
 */
NCP_API int ncp_dpt_put_pick_key(ncp_dpt_t *dpt, void *value, ncp_uint32_t *outKey);


/*!
 * @fn ncp_dpt_rem(ncp_dpt_t *dpt, ncp_uint32_t key)
 * @brief  To remove a value from the ncp_dpt_t which was previously put 
 *         in under key. If there was a value under key then it is returned.
 * @ret    void*
 */
NCP_API void* ncp_dpt_rem(ncp_dpt_t *dpt, ncp_uint32_t key);

/*!
 * @fn ncp_dpt_traverse(ncp_dpt_t *dpt,dptNodetTraverseFn_t tFn)
 * @brief Traverse all the valid entries in the dpt database and call the 
 *        traverse function supplied in the argument on each entry.
 *        This can be used for a "printf" function or something
 *        that performs a transform on everything in the database.
 *        API Checkpointing would find this useful.
 * @ret  void
 */

/*        Currently, the performance on this is lame. */
typedef int (*dptNodetTraverseFn_t)(ncp_uint32_t key, void *node);

NCP_API void ncp_dpt_traverse(ncp_dpt_t *dpt,dptNodetTraverseFn_t tFn);

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* _NCP_DPT_H */
