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

#ifndef __ncp_strlist_h__
#define __ncp_strlist_h__

#include "ncp_types.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" { 
#endif

/**************************************************************************
 * This file defines the interface to data types and functions to
 * parse a string and build a list of objects in a linked list and to
 * iterate and fetch individual objects.
 **************************************************************************/

/*
 * ncp_strlist_val_type_t
 *      Definition of the type of elements in the list to be parsed and
 *      built.
 */
typedef enum {
    ncp_strlist_val_type_none = -1,
    ncp_strlist_val_type_str = 1,
    ncp_strlist_val_type_int32 = 2,
    ncp_strlist_val_type_int64 = 3,
    ncp_strlist_val_type_cus = 4 /* custom object */
} ncp_strlist_val_type_t;

/*
 * ncp_strlist_val_t
 *      Definition of the value of an element in the list to be built.
 */
typedef struct {
    ncp_strlist_val_type_t type;
    union {
        char                *strval;
        ncp_int32_t          i32val;
        ncp_int64_t          i64val;
        void                *cusval;
    }                     val;
} ncp_strlist_val_t;

/*
 * ncp_strlist_cusconv_t
 *      Definition of the converter function that is used to convert a
 *      string into a custom value.
 */
typedef void *(*ncp_strlist_cusconv_t)(const char *);

/*
 * ncp_strlist_cmpfunc_t
 *      Definition of the comparator function that is used to compare
 *      two values to aid sorting during building of a list.
 */

typedef int (*ncp_strlist_cmpfunc_t)(void *, void *);

/*
 * ncp_strlist_node_t
 *      Definition of a node in a list that is built from an input string
 *      of values.
 */
typedef struct _ncp_strlist_node_s {
    struct _ncp_strlist_node_s   *next;
    ncp_strlist_val_t            *val;
} ncp_strlist_node_t;

/*
 * ncp_strlist_iter_t
 *      Definition of an iterator object for a list.
 */
typedef struct {
    ncp_strlist_node_t           *head;
    ncp_strlist_node_t           *cur;
} ncp_strlist_iter_t;




/*
 * Exported functions
 */

/*
 * Parse and build a list of elements from a given string.
 */
NCP_API ncp_st_t ncp_strlist_list_build(const char *valstr, ncp_strlist_val_type_t type, char sepSpecifier, char rangeSpecifier, ncp_strlist_cusconv_t converter, ncp_strlist_cmpfunc_t, ncp_strlist_node_t **list);

/*
 * Free memory used up in a list.
 */
NCP_API ncp_st_t ncp_strlist_list_free(ncp_strlist_node_t *list);

/*
 * Fetch an iterator off a list.
 */
NCP_API ncp_st_t ncp_strlist_iter_fetch(ncp_strlist_node_t *list, ncp_strlist_iter_t **iter);

/*
 * Function to check if an iterator has more elements.
 */
NCP_API ncp_bool_t ncp_strlist_iter_hasNext(ncp_strlist_iter_t *iter);

/*
 * Function to fetch the next element from an iterator.
 */
NCP_API ncp_strlist_node_t *ncp_strlist_iter_getNext(ncp_strlist_iter_t *iter);

/*
 * Function to free the iterator.
 */
NCP_API void ncp_strlist_iter_free(ncp_strlist_iter_t *iter);

/*
 * Functions to fetch the type and value from a node.
 */
NCP_API ncp_st_t ncp_strlist_node_val_getString(ncp_strlist_node_t *node, char **val);
NCP_API ncp_st_t ncp_strlist_node_val_getInt32(ncp_strlist_node_t *node, ncp_int32_t *val);
NCP_API ncp_st_t ncp_strlist_node_val_getInt64(ncp_strlist_node_t *node, ncp_int64_t *val);
NCP_API ncp_st_t ncp_strlist_node_val_getCusval(ncp_strlist_node_t *node, void **val);
NCP_API ncp_st_t ncp_strlist_node_val_getType(ncp_strlist_node_t *node, ncp_strlist_val_type_t *type);


/*
 * Memory allocation routines used within these functions.
 * These are exposed if the application wants to allocate/free memory
 * for any of the ncp_strlist structures such as iter, node.
 */
NCP_API void *ncp_strlist_malloc(ncp_int32_t size);
NCP_API void *ncp_strlist_realloc(void *ptr, ncp_int32_t size);
NCP_API void  ncp_strlist_free(void *ptr);
NCP_API char *ncp_strlist_strdup(const char *str);


/*
 * Defines of constants.
 */
#define NCP_STRLIST_ITEM_MAXLEN  (255)
#define NCP_STRLIST_ITEM_CHAR_SEP  ','
#define NCP_STRLIST_ITEM_CHAR_RANGE  ':'



#ifdef __cplusplus
}
#endif

#endif /* __ncp_strlist_h__ */
