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

/*! @file      ncp_subnet.h                                               */

/*! **************************************************************************************************
 *  @defgroup _subnet_APIs Subnet
 *  @ingroup _ptn_Pattern
 *  @brief     Subnet APIs are utility functions to help application maintain a separate
 *             database of subnets which may be necessary for unlearning patterns in an
 *             LPM tree.
 *  @details
 *  The pattern unlearn API (ncp_ptn_unlearn()) requires the application to
 *  specify the pattern's next higher subnet size and action in order to
 *  unlearn a pattern. Some applications may not have this information in
 *  a convenient fashion. These utility functions implement a simple 
 *  hash-table based database of subnets allowing the application to
 *  query this information.
 *
 *  The implementation consists of a set of hash tables. Each table
 *  maintains subnets for a specifid number of don't cares (xsize).
 *  For example, for maintaining Ip address subnets, 32 tables are
 *  used (subnet sizes being 1, 2, 3, ... 32).
 *  When a pattern's next higher subnet is to be found, all tables
 *  which contain a higher number of don't care bits are queried in
 *  order to find a match.
 *****************************************************************************************************/

#ifndef _ncp_subnet_h
#define _ncp_subnet_h


/*
 * Base include file for our types
 */
#include "ncp_status.h"
#include "ncp_ptn.h"

#ifdef __cplusplus
extern "C" { 
#endif


/*
 * Status codes returned by ncp_subnet_*** functions
 */
#define  ncp_subnet_ok                   NCP_ST_SUCCESS
#define  ncp_subnet_seminit_error	 NCP_ST_SUBNET_SEM_INIT_ERROR
#define  ncp_subnet_invalid_ptn          NCP_ST_SUBNET_INVALID_PTN
#define  ncp_subnet_invalid_hdl          NCP_ST_SUBNET_INVALID_HDL
#define  ncp_subnet_no_match             NCP_ST_SUBNET_NO_MATCH
#define  ncp_subnet_invalid_xsize        NCP_ST_SUBNET_INVALID_XSIZE
#define  ncp_subnet_invalid_bucket_idx   NCP_ST_SUBNET_INVALID_BUCKET_IDX
#define  ncp_subnet_invalid_checkpoint   NCP_ST_SUBNET_INVALID_CHECKPOINT
#define  ncp_subnet_read_error           NCP_ST_SUBNET_READ_ERROR
#define  ncp_subnet_write_error          NCP_ST_SUBNET_WRITE_ERROR
#define  ncp_subnet_no_memory            NCP_ST_NO_MEMORY

/*!
 * @ingroup _pattern_APIs
 * @struct ncp_subnet_t
 * @brief A subnet database handle
 */
typedef void* ncp_subnet_t;


/*!
 * @ingroup _ptn_Pattern
 * @typedef ncp_subnet_hash_fn_t
 * @brief Definition for a hash function. 
 * @details Applications can implement their
 *     own hash function and register it with the database. This function
 *     gets called for hashing a pattern to a specific hash bucket when
 *     adding/deleting or querying patterns
 */
typedef ncp_uint32_t (*ncp_subnet_hash_fn_t)(ncp_uint32_t hash_table_size, ncp_ptn_t *ptn);


/*! 
 * @ingroup _subnet_APIs
 * @brief  Create a ncp_subnet_t handle. This handle is then passed to the other functions. 
 * @param[in]  maxsize Maximum subnet size for this database. For example, an Ip address 
 *                database would have maxsize as 32 since the maximum subnet is a 
 *                32-bit subnet. 
 * @param[in]  hash_fn Specifies a user specified hashing function to call for hashing
 *                patterns to hash buckets. If this is NULL, an internal hash function
 *                is used.
 * @param[in]  hash_table_sizes Specifies the number of hash buckets to use for each hash
 *                table. Since each subnet size is maintained in a different table, 
 *                this parameter is specified as an array of sizes. If this parameter
 *                is NULL, each hash table is allocated a size of 32.
 * @param[out] hdl     The hdl is returned once the database is successfully created.
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_SUBNET_SEM_INIT_ERROR
 *         </ul>
 */
NCP_API ncp_st_t 
ncp_subnet_create(ncp_uint32_t maxsize, ncp_subnet_hash_fn_t hash_fn, 
                 ncp_uint32_t *hash_table_sizes, ncp_subnet_t *hdl);


/*!
 * @ingroup _subnet_APIs
 * @brief When finished with a ncp_subnet_t this function will destroy it. After this
 *                function is called. the pointer to the ncp_subnet_t has been freed and 
 *                should not be used.
 * @param[in]  hdl     The subnet database to destroy
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_SUBNET_INVALID_HDL
 *         </ul>
 */
NCP_API ncp_st_t 
ncp_subnet_destroy(ncp_subnet_t *hdl);


/*! 
 * @ingroup _subnet_APIs
 * @brief Adds a pattern and it's action to the subnet database. 
 * @details Normally, this API is used in conjunction with ncp_ptn_learn.
 *      <ul>
 *       <li>  ncp_ptn_learn(hdl, ptn, action);
 *       <li>  ncp_subnet_add_subnet(shdl, ptn, action);
 *      </ul>
 * @param[in]  hdl     The subnet database handle
 * @param[in]  ptn     The pattern to add
 * @param[in]  action  The action forn the pattern
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_SUBNET_INVALID_HDL
 *           <li> #NCP_ST_SUBNET_INVALID_PTN
 *           <li> #NCP_ST_SUBNET_INVALID_XSIZE
 *           <li> #NCP_ST_SUBNET_NO_MATCH
 *         </ul>
 */
NCP_API ncp_st_t 
ncp_subnet_add_subnet(ncp_subnet_t hdl, ncp_ptn_t *ptn,
                     ncp_ptn_action_t *action);


/*!
 * @ingroup _subnet_APIs
 * @brief  Deletes a pattern from the subnet database. 
 * @details Normally, this API is used in conjunction with ncp_ptn_unlearn
 *      <ul>
 *       <li>   ncp_subnet_find_higher_subnet(shdl, ptn, &xsize, &action);
 *       <li>   ncp_ptn_unlearn(hdl, ptn, &xsize, &action);
 *       <li>   ncp_subnet_del_subnet(shdl, ptn);
 *      </ul>
 * @param[in]  hdl     The subnet database handle
 * @param[in]  ptn     The pattern to delete
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_SUBNET_INVALID_HDL
 *           <li> #NCP_ST_SUBNET_INVALID_PTN
 *           <li> #NCP_ST_SUBNET_INVALID_XSIZE
 *           <li> #NCP_ST_SUBNET_NO_MATCH
 *         </ul>
 */
NCP_API ncp_st_t 
ncp_subnet_del_subnet(ncp_subnet_t hdl, ncp_ptn_t *ptn);


/*! 
 * @ingroup _subnet_APIs
 * @brief Returns the next higher subnet's xsize and it's action for a given pattern
 * @details Normally, this API is used in conjunction with ncp_ptn_unlearn
 *      <ul>
 *       <li>  ncp_subnet_find_higher_subnet(shdl, ptn, &xsize, &action);
 *       <li>  ncp_ptn_unlearn(hdl, ptn, &xsize, &action);
 *       <li>  ncp_subnet_del_subnet(shdl, ptn);
 *      </ul>
 * @param[in]  hdl     The subnet database handle
 * @param[in]  ptn     The pattern for which the next higher subnet is looked up
 * @param[in]  sxsize  If found, the next higher subnet's subnet size
 * @param[out] action  If found, the next higher subnet's action
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_SUBNET_INVALID_HDL
 *           <li> #NCP_ST_SUBNET_INVALID_HDL
 *           <li> #NCP_ST_SUBNET_INVALID_PTN
 *           <li> #NCP_ST_SUBNET_INVALID_XSIZE
 *           <li> #NCP_ST_SUBNET_NO_MATCH
 *         </ul>
 */
NCP_API ncp_st_t 
ncp_subnet_find_higher_subnet(ncp_subnet_t hdl, ncp_ptn_t *ptn,
                             ncp_uint32_t *sxsize, ncp_ptn_action_t *action);

/*!
 * @ingroup _subnet_APIs
 * @brief Returns the action for the specified subnet. 
 * @details The subnet is searched for in the appropriate
 *          hash table for the pattern's hash table. Patterns with no wild cards (no subnet)
 *          will not be found since they are not stored in the subnet database.
 * @param[in]  hdl     The subnet database handle
 * @param[in]  ptn     The pattern to find
 * @param[out] action  If found, the subnet's action
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_SUBNET_INVALID_HDL
 *           <li> #NCP_ST_SUBNET_INVALID_PTN
 *           <li> #NCP_ST_SUBNET_INVALID_XSIZE
 *           <li> #NCP_ST_SUBNET_NO_MATCH
 *         </ul>
 */
NCP_API ncp_st_t 
ncp_subnet_find_subnet(ncp_subnet_t hdl, ncp_ptn_t *ptn,
                       ncp_ptn_action_t *action);

/*!
 * @ingroup _subnet_APIs
 * @brief API to query the number of hash buckets in the hash table for the
 *                specified xsize. 
 * @details Each xsize from 1 to max_xsize has a hash table. 
 *          So, xsize value ranges from 1 to max_xsize
 * @param[in]  hdl     The subnet database handle
 * @param[in]  xsize   The hash table to lookup
 * @param[out] no_buckets The number of buckets for the hash table
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_SUBNET_INVALID_HDL
 *         </ul>
 */
NCP_API ncp_st_t 
ncp_subnet_get_no_buckets(ncp_subnet_t hdl, ncp_uint32_t xsize, 
                         ncp_uint32_t *no_buckets);

/*!
 * @ingroup _subnet_APIs
 * @brief  API to query the number of entries stored for the specified bucket
 *                in the hash table for the specified xsize. 
 * @details xsize values range from
 *          1 to max_xsize. bucket_idx values range from 1 to no_buckets returned
 *          in ncp_subnet_get_no_buckets()
 * @param[in]  hdl     The subnet database handle
 * @param[in]  xsize   The hash table to lookup
 * @param[in]  bucket_idx The bucket index in the hash table
 * @param[out] no_entries The number of entries in the bucket is returned
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_SUBNET_INVALID_HDL
 *           <li> #NCP_ST_SUBNET_INVALID_BUCKET_IDX
 *         </ul>
 */
NCP_API ncp_st_t 
ncp_subnet_get_no_bucket_entries(ncp_subnet_t hdl, ncp_uint32_t xsize, 
                                ncp_uint32_t bucket_idx, ncp_uint32_t *no_entries);


/*!
 * @ingroup _subnet_APIs
 * @brief API to free all the entries in a subnet database. The database itself
 *                is empty when the API finishes.
 * @param[in]  hdl     The subnet database handle
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_SUBNET_INVALID_HDL
 *         </ul>
 */
NCP_API ncp_st_t 
ncp_subnet_destroy_entries(ncp_subnet_t hdl);

/*!
 * @ingroup _subnet_APIs
 * @brief API to set the hash function to use. 
 * @details If NULL, then an internal function is used.
 *          This API is particularly meant for a API warm restart scenario. On a
 *          crash/recovery of the API state using NVM, the text space might be
 *          different and the pointer stored to the hash function may be invalid.
 *          This API allows the application to reset it properly.
 *          Note: This API is NOT meant to switch over the subnet database hash
 *          function in a running system.
 * @param[in]  hdl     The subnet database handle
 * @param[in]  hash_fn The hash function to set
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_SUBNET_INVALID_HDL
 *         </ul>
 */
NCP_API ncp_st_t
ncp_subnet_set_hash_fn(ncp_subnet_t hdl, ncp_subnet_hash_fn_t hash_fn);


/*!
 * @internal
 * @ingroup _subnet_APIs
 * @brief Subnet database checkpointing. 
 * @details The checkpoint is a snapshot of the
 *          database in a canonical form. Allows the application to snapshot
 *          the current state and reinitialize from a snapshot without having
 *          to re-add all the entries.
 *          The ncp_subnet_write_checkpoint is used to take the snapshot. The 
 *          application provides the write function which is used to create the
 *          snapshot. The rock is an opaque pointer passed as-is to the write
 *          function.
 *          The ncp_subnet_init_from_checkpoint is used to initialize from a 
 *          checkpoint. The database (handle) used should match the original
 *          database from which the checkpoint has been taken, in terms of the
 *          width. The application provides the read function which is used to
 *          in the checkpoint and recreate the database. The rock is an opaque
 *          read pointer passed as-is to the read function. Any current entries
 *          in the database are deleted before recreating the new database.
 * @param[in]  hdl     The subnet database handle
 * @param[in]  wrfn    The function used to write the data
 * @param[in]  rock    The opaque handle passed to the wrfn
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_SUBNET_INVALID_HDL
 *           <li> #NCP_ST_SUBNET_WRITE_ERROR
 *         </ul>
 */
NCP_API ncp_st_t
ncp_subnet_write_checkpoint(ncp_subnet_t hdl, ncp_write_fn_t wrfn, void *rock);
/*!
 * @internal
 * @ingroup _subnet_APIs
 * @brief Subnet database checkpointing. 
 * @details The checkpoint is a snapshot of the
 *          database in a canonical form. Allows the application to snapshot
 *          the current state and reinitialize from a snapshot without having
 *          to re-add all the entries.
 *          The ncp_subnet_write_checkpoint is used to take the snapshot. The 
 *          application provides the write function which is used to create the
 *          snapshot. The rock is an opaque pointer passed as-is to the write
 *          function.
 *          The ncp_subnet_init_from_checkpoint is used to initialize from a 
 *          checkpoint. The database (handle) used should match the original
 *          database from which the checkpoint has been taken, in terms of the
 *          width. The application provides the read function which is used to
 *          in the checkpoint and recreate the database. The rock is an opaque
 *          read pointer passed as-is to the read function. Any current entries
 *          in the database are deleted before recreating the new database.
 * @param[in]  hdl     The subnet database handle
 * @param[in]  rdfn    The function used to read the data
 * @param[in]  rock    The opaque handle passed to the wrfn
 * @return <ul>
 *           <li> #NCP_ST_SUCCESS
 *           <li> #NCP_ST_SUBNET_INVALID_HDL
 *           <li> #NCP_ST_SUBNET_READ_ERROR
 *         </ul>
 */
NCP_API ncp_st_t
ncp_subnet_init_from_checkpoint(ncp_subnet_t hdl, ncp_read_fn_t rdfn, void *rock);

#ifdef __cplusplus
}
#endif

#endif /* _ncp_subnet_h */



