/**************************************************************************
**                                                                        *
**                           Intel CONFIDENTIAL           *
**                       PROPRIETARY NOTE                                 *
**                                                                        *
**    This software contains information confidential and proprietary     *
**    to Intel Corporation.  It shall not be reproduced in whole or in  *
**    part, or transferred to other documents, or disclosed to third      *
**    parties, or used for any purpose other than that for which it was   *
**    obtained, without the prior written consent of Intel Corporation. *
**    (c) 2008-2014, Intel Corporation.  All rights reserved.           *
**                                                                        *
**  ***********************************************************************
**
**  ***********************************************************************
**
***************************************************************************/

/*! @file      ncp_hash.h
 *  @brief     This file implements a hash table for unsigned integers(NCP_U32).
 */

#ifndef _ncp_hash_h
#define _ncp_hash_h

/*!
 *  @addtogroup _hash_ Hash Table
 *  @brief Hash Table (hash)
 *  @detail This module implements a hash table for unsigned integers (NCP_U32).
 *  @{
 *  @ingroup    _utility_
 */

/*
 * Base include file for our types
 */
#include "ncp_types.h"

#ifdef __cplusplus
extern "C" { 
#endif

/*
 * ncp_hash
 *   Type for using ncp_hash_t
 */
typedef void* ncp_hash_t;

/*!
 * @fn ncp_hash_create_table(ncp_uint32_t size)
 * @brief Create a ncp_hash_t. This ncp_hash_t is then passed to the 
 *        other functions
 */
NCP_API ncp_hash_t* ncp_hash_create_table(ncp_uint32_t size);
NCP_API ncp_hash_t* ncp_leak_hash_create_table(ncp_uint32_t size);

/*!
 * @fn NCP_API void ncp_hash_delete_table(ncp_hash_t *ht)
 * @brief When finished with a ncp_hash_t this function will delete it. 
 *        After this function is called. the pointer to the ncp_hash_t has 
 *        been freed and should not be used.
 */
typedef int (*nodeDeleteFn_t)( void *node);

NCP_API void ncp_hash_delete_nodes_and_table(ncp_hash_t *ht,nodeDeleteFn_t delFn);
NCP_API void ncp_leak_hash_delete_nodes_and_table(ncp_hash_t *ht,nodeDeleteFn_t delFn);
NCP_API void ncp_hash_delete_table(ncp_hash_t *ht);
NCP_API void ncp_leak_hash_delete_table(ncp_hash_t *ht);

/*!
 * @fn ncp_hash_get(ncp_hash_t *ht, NCP_U32 key)
 * @brief  To get a value out of the ncp_hash_t that was put in under key. 
 *         If NULL is returned then no match was found.
 */
NCP_API void *ncp_hash_get(ncp_hash_t *ht, NCP_U32 key);
NCP_API void *ncp_leak_hash_get(ncp_hash_t *ht, NCP_U32 key);

/*!
 * @fn ncp_hash_put(ncp_hash_t *ht, NCP_U32 key, void *value)
 * @brief  To put a value into the ncp_hash_t under key. If a value 
 *         was previously in the table under this key, then it is returned.
 */
NCP_API void *ncp_hash_put(ncp_hash_t *ht, NCP_U32 key, void *value);
NCP_API void *ncp_leak_hash_put(ncp_hash_t *ht, NCP_U32 key, void *value);

/*! 
 * @fn ncp_hash_rem(ncp_hash_t *ht, NCP_U32 key)
 * @brief  To remove a value from the ncp_hash_t which was previously put 
 *         in under key. If there was a value under key then it is returned.
 */
NCP_API void* ncp_hash_rem(ncp_hash_t *ht, NCP_U32 key);
NCP_API void* ncp_leak_hash_rem(ncp_hash_t *ht, NCP_U32 key);

/*!
 * @fn ncp_hash_print(ncp_hash_t *ht)
 * @brief  Prints out all entries in the hash table along with the index numbers
 */
NCP_API void ncp_hash_print(ncp_hash_t *ht);
NCP_API void ncp_leak_hash_print(ncp_hash_t *ht);

/*!
 * @fn ncp_hash_first_entry(ncp_hash_t *ht,ncp_uint32_t *outKey)
 * @brief return "first" entry found in table
 */
NCP_API void * ncp_hash_first_entry(ncp_hash_t *ht,ncp_uint32_t *outKey);
NCP_API void * ncp_leak_hash_first_entry(ncp_hash_t *ht,ncp_uint32_t *outKey);

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* _ncp_hash_h */
