/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


#ifndef _ncp_sorted_set_h
#define _ncp_sorted_set_h

/*
 * Base include file for our types
 */
#include "ncp_types.h"

#ifdef __cplusplus
extern "C" { 
#endif

/*
 *   ncp_sorted_set
 *   Type for using ncp_sorted_set_t
 */
typedef void* ncp_sorted_set_t;

/*
 * function pointer prototype, compares a to b, indicates the direction.
 * The user can change the sort order(high to low,low to high) and the key length with this.
 */
typedef enum {
    NCP_SORTED_SET_CMP_EQUAL = 0,
    NCP_SORTED_SET_CMP_LEFT,
    NCP_SORTED_SET_CMP_RIGHT
}ncp_sorted_set_cmp_result_t;

typedef ncp_sorted_set_cmp_result_t (*ncp_sorted_set_element_compare_function_t)(void *akey,void *bkey);

/*
 * function pointer prototype for applying a function to each set member
 * a return value other than zero is interpreted as an indication to return.
 */
typedef int (*ncp_sorted_set_element_function_t)(ncp_uint32_t n,void *key,void *value, void *args);

typedef int (*ncp_sorted_set_nodeDeleteFn_t)( void *key,void *value);

/*
 * API's
 */
NCP_API ncp_sorted_set_t* ncp_sorted_set_create(
                    ncp_uint32_t mallocSizeBytes,
                    ncp_uint32_t numInitialNodes);

NCP_API void ncp_sorted_set_delete_nodes_and_set(
                    ncp_sorted_set_t *sorted_set,
                    ncp_sorted_set_nodeDeleteFn_t delFn);

NCP_API int ncp_sorted_set_iterate_through_set(
                    ncp_sorted_set_t *sorted_set,
                    ncp_sorted_set_element_function_t fn, 
                    void *args);

NCP_API void* ncp_sorted_set_get(
                    ncp_sorted_set_t *sorted_set,
                    void *key,
                    ncp_sorted_set_element_compare_function_t compareFn);

NCP_API void* ncp_sorted_set_get_n(
                    ncp_sorted_set_t *sorted_set,
                    ncp_uint32_t n);

NCP_API void* ncp_sorted_set_put_n(
                    ncp_sorted_set_t *sorted_set,
                    ncp_uint32_t n,
                    void *value);

NCP_API ncp_uint32_t ncp_sorted_set_size(
                    ncp_sorted_set_t *sorted_set);

NCP_API void* ncp_sorted_set_put(
                    ncp_sorted_set_t *sorted_set,
                    void *key,
                    ncp_sorted_set_element_compare_function_t compareFn,
                    void* value);

NCP_API void *ncp_sorted_set_remove(
                    ncp_sorted_set_t *sorted_set,
                    void *key,  
                    ncp_sorted_set_element_compare_function_t compareFn);


#ifdef __cplusplus
}
#endif

#endif /* _ncp_sorted_set_h */
