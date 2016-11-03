/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


/*! @file      ncp_map.h
 *  @brief     ncp_map_t definition and APIs to read a HW configuration image.
 *
 * @details
 * This file defines the interface to a ncp_map_t structure. The ncp_map_t
 * structure maintains a set of attributes. Each attribute has a key (name)
 * and a value. The value can be an integer, a string, a buffer (binary)
 * or another ncp_map_t structure. This allows a hierarchical attribute
 * structure which is very extensible
 */

#ifndef __ncp_map_h__
#define __ncp_map_h__

#include "ncp_types.h"
#ifndef NCP_KERNEL
#include <stdio.h>
#endif

/*!
 *  @addtogroup _map_ Configuration Map
 *  @brief Configuration Map (map)
 *  @detail The Config Map API provide the capability to create, read, and
 *         manipulate maps through its ncp_map interface.  The ncp_map
 *         interface provides all of the required definitions for data
 *         types and structures, and a collection of functions for map
 *         management, retrieving values from the map, modifying values,
 *         or creating new maps or values. 
 *  @{
 *  @ingroup _utility_
 */

#ifdef __cplusplus
extern "C" { 
#endif

/*!
 * @typedef   ncp_map_t
 * @brief     Definition of a map_t structure
 */
typedef void *ncp_map_t;

/*!
 * @enum       ncp_map_type_t
 * @brief      A ncp_map_t object can store one of 5 data types. This enum
 *      defines the type of the data
 */
typedef enum
{
    ncp_map_type_str = 1,
    ncp_map_type_map = 2,
    ncp_map_type_bin = 3,
    ncp_map_type_i32 = 4,
    ncp_map_type_i64 = 5,
    ncp_map_type_float = 6,
    ncp_map_type_bool = 7,
    ncp_map_type_u32 = 8,
    ncp_map_type_double = 9,
    ncp_map_type_u64 = 10,
    ncp_map_type_unknown = -1
} ncp_map_type_t;

/*!
 * @struct    ncp_map_value_t
 * @brief     The structure of an ncp_map value. Contains a type followed by 
 *            a union on the actual value type
 */
typedef struct _ncp_map_value_t
{
    ncp_map_type_t        type;
    union
    {
        ncp_int32_t       i32Value;
        ncp_int64_t       i64Value;
        float             floatValue;
        char             *strValue;
        ncp_byte_string_t binValue;
        ncp_map_t        *mapValue;
        ncp_bool_t        boolValue;
        ncp_uint32_t      u32Value;
        ncp_uint64_t      u64Value;
        double            doubleValue;
    } u;
} ncp_map_value_t;


/*!
 * Exported functions
 *      These are the exported functions for a map_t object
 */

/*!
 * @fn ncp_st_t ncp_map_create(ncp_map_t **map)
 * @brief Create an empty ncp_map_t object
 * Creates an empty ncp_map_t structure and returns it. This pointer 
 *         is then passed to all functions to manipulate it
 */
NCP_API ncp_st_t ncp_map_create(ncp_map_t **map);

/*!
 * @fn ncp_st_t ncp_map_destroy(ncp_map_t *map)
 * @param map A pointer to the map structure to be destroyed.
 * @brief Destroy an existing ncp_map_t object deleting all keys and values
 * Destroys a ncp_map_t structure by freeing all it's elements
 */
NCP_API ncp_st_t ncp_map_destroy(ncp_map_t *map);

#define ncp_map_set_value(x, y, z) ncp_map_set_value_ll((x), (y), (z), TRUE)
#define ncp_map_set_value_unique(x, y, z) ncp_map_set_value_ll((x), (y), (z), FALSE)
/*!
 * Methods to set and get a key/value pair. Here, the value is allocated
 * by the application and needs to be allocated/freed using the
 * ncp_map_malloc/ncp_map_free methods
 */
/*!
 * @fn ncp_st_t ncp_map_set_value_ll(ncp_map_t *map, const char *key, ncp_map_value_t *value, ncp_bool_t checkForKey)
 * @brief Adds the specified attribute with the specified value.
 */
NCP_API ncp_st_t ncp_map_set_value_ll(ncp_map_t *map, const char *key, ncp_map_value_t *value, ncp_bool_t checkForKey);

/*!
 * @fn ncp_st_t ncp_map_get_value(ncp_map_t *map, const char *key, ncp_map_value_t **value)
 * @brief     Returns the value for the specified attribute
 */
NCP_API ncp_st_t ncp_map_get_value(ncp_map_t *map, const char *key, ncp_map_value_t **value);

/*!
 * @fn ncp_st_t ncp_map_get_all_values(ncp_map_t *map, const char *key, ncp_map_value_t **value, ncp_uint32_t maxValues, ncp_uint32_t *nKeysFound, ncp_uint32_t keyLength)
 * @brief     Returns all values for the specified attribute.
 *
 *     The "maxValues" argument specifies the size of the caller's 
 *             "value" array and hence the maximum number of values that can 
 *             be returned.
 *
 *      If "nKeysFound" is not NULL, then the total number of matching
 *      attribute elements is returned. Note that upon return "nKeysFound"
 *      may be greater than "maxValues".
 *
 *      If "keyLength" is non-zero then only the first "keyLength"
 *      characters of the key (attribute name) are matched. This allows
 *      retrieval of all values for a given key name prefix.
 */
NCP_API ncp_st_t ncp_map_get_all_values(ncp_map_t *map, const char *key, ncp_map_value_t **value, ncp_uint32_t maxValues, ncp_uint32_t *nKeysFound, ncp_uint32_t keyLength);

/*
 * @fn ncp_st_t ncp_map_free_value( ncp_map_value_t *v) 
 * @brief Free a map value
 */
NCP_API ncp_st_t ncp_map_free_value( ncp_map_value_t *v) ;


/*!
 * @fn ncp_st_t ncp_map_count_keys(ncp_map_t *map, const char *key, ncp_uint32_t *nKeysFound)
 * @brief Count the number of keys present in the given map.
 * @param map: Input map to search.
 * @param key: key to match.
 * @param nKeysFound: Returns the number of keys matching the key string.
 */
NCP_API ncp_st_t ncp_map_count_keys(ncp_map_t *map, const char *key, ncp_uint32_t *nKeysFound);

/*!
 * Methods to set the different value types. The memory for the ncp_map_value_t
 * is allocated by these functions
 */
/*!
 * @fn ncp_st_t ncp_map_set_i32_ll(ncp_map_t *map, const char *key, ncp_int32_t value, ncp_bool_t checkForKey)
 * @brief     Adds the specified attribute with an i32 value
 */
#define ncp_map_set_i32(x, y, z) ncp_map_set_i32_ll((x), (y), (z), TRUE)
#define ncp_map_set_i32_unique(x, y, z) ncp_map_set_i32_ll((x), (y), (z), FALSE)
NCP_API ncp_st_t ncp_map_set_i32_ll(ncp_map_t *map, const char *key, ncp_int32_t value, ncp_bool_t checkForKey);

/*!
 * @fn ncp_st_t ncp_map_set_i64_ll(ncp_map_t *map, const char *key, ncp_int64_t value, ncp_bool_t checkForKey)
 * @brief     Adds the specified attribute with an i64 value
 */
#define ncp_map_set_i64(x, y, z) ncp_map_set_i64_ll((x), (y), (z), TRUE)
#define ncp_map_set_i64_unique(x, y, z) ncp_map_set_i64_ll((x), (y), (z), FALSE)
NCP_API ncp_st_t ncp_map_set_i64_ll(ncp_map_t *map, const char *key, ncp_int64_t value, ncp_bool_t checkForKey);

/*!
 * @fn ncp_st_t ncp_map_set_float_ll(ncp_map_t *map, const char *key, float value, ncp_bool_t checkForKey)
 * @brief  Adds the specified attribute with an float value
 */
#define ncp_map_set_float(x, y, z) ncp_map_set_float_ll((x), (y), (z), TRUE)
#define ncp_map_set_float_unique(x, y, z) ncp_map_set_float_ll((x), (y), (z), FALSE)
NCP_API ncp_st_t ncp_map_set_float_ll(ncp_map_t *map, const char *key, float value, ncp_bool_t checkForKey);

/*!
 * @fn ncp_st_t ncp_map_set_str_ll(ncp_map_t *map, const char *key, char *value, ncp_bool_t checkForKey)
 * @brief Adds the specified attribute with an str value
 */
#define ncp_map_set_str(x, y, z) ncp_map_set_str_ll((x), (y), (z), TRUE)
#define ncp_map_set_str_unique(x, y, z) ncp_map_set_str_ll((x), (y), (z), FALSE)
NCP_API ncp_st_t ncp_map_set_str_ll(ncp_map_t *map, const char *key, char *value, ncp_bool_t checkForKey);

/*!
 * @fn ncp_st_t ncp_map_set_bin_ll(ncp_map_t *map, const char *key, char *value, ncp_int32_t len, ncp_bool_t checkForKey)
 * @brief Adds the specified attribute with an bin value
 */
#define ncp_map_set_bin(x, y, z, a) ncp_map_set_bin_ll((x), (y), (z), (a), TRUE)
#define ncp_map_set_bin_unique(x, y, z, a) ncp_map_set_bin_ll((x), (y), (z), (a), FALSE)
NCP_API ncp_st_t ncp_map_set_bin_ll(ncp_map_t *map, const char *key, char *value, ncp_int32_t len, ncp_bool_t checkForKey);

/*!
 * @fn ncp_st_t ncp_map_set_map_ll(ncp_map_t *map, const char *key, ncp_map_t *value, ncp_bool_t checkForKey)
 * @brief Adds the specified attribute with an map value
 */
#define ncp_map_set_map(x, y, z) ncp_map_set_map_ll((x), (y), (z), TRUE)
#define ncp_map_set_map_unique(x, y, z) ncp_map_set_map_ll((x), (y), (z), FALSE)
NCP_API ncp_st_t ncp_map_set_map_ll(ncp_map_t *map, const char *key, ncp_map_t *value, ncp_bool_t checkForKey);

/*!
 * @fn ncp_st_t ncp_map_set_bool_ll(ncp_map_t *map, const char *key, ncp_bool_t value, ncp_bool_t checkForKey)
 * @brief Adds the specified attribute with an bool value
 */
#define ncp_map_set_bool(x, y, z) ncp_map_set_bool_ll((x), (y), (z), TRUE)
#define ncp_map_set_bool_unique(x, y, z) ncp_map_set_bool_ll((x), (y), (z), FALSE)
NCP_API ncp_st_t ncp_map_set_bool_ll(ncp_map_t *map, const char *key, ncp_bool_t value, ncp_bool_t checkForKey);

/*!
 * @fn ncp_st_t ncp_map_set_u32_ll(ncp_map_t *map, const char *key, ncp_uint32_t value, ncp_bool_t checkForKey)
 * @brief Adds the specified attribute with an u32 value
 */
#define ncp_map_set_u32(x, y, z) ncp_map_set_u32_ll((x), (y), (z), TRUE)
#define ncp_map_set_u32_unique(x, y, z) ncp_map_set_u32_ll((x), (y), (z), FALSE)
NCP_API ncp_st_t ncp_map_set_u32_ll(ncp_map_t *map, const char *key, ncp_uint32_t value, ncp_bool_t checkForKey);

/*
 * @fn ncp_st_t ncp_map_set_u64_ll(ncp_map_t *map, const char *key, ncp_uint64_t value, ncp_bool_t checkForKey)
 * @brief Adds the specified attribute with an u64 value
 */
#define ncp_map_set_u64(x, y, z) ncp_map_set_u64_ll((x), (y), (z), TRUE)
#define ncp_map_set_u64_unique(x, y, z) ncp_map_set_u32_ll((x), (y), (z), FALSE)
NCP_API ncp_st_t ncp_map_set_u64_ll(ncp_map_t *map, const char *key, ncp_uint64_t value, ncp_bool_t checkForKey);

/*!
 * @fn ncp_st_t ncp_map_set_double_ll(ncp_map_t *map, const char *key, double value, ncp_bool_t checkForKey)
 * @double Adds the specified attribute with an double value
 */
#define ncp_map_set_double(x, y, z) ncp_map_set_double_ll((x), (y), (z), TRUE)
#define ncp_map_set_double_unique(x, y, z) ncp_map_set_double_ll((x), (y), (z), FALSE)
NCP_API ncp_st_t ncp_map_set_double_ll(ncp_map_t *map, const char *key, double value, ncp_bool_t checkForKey);

/*!
 * Methods to retrieve individual types of values
 */
/*!
 * @fn ncp_st_t ncp_map_get_i32(ncp_map_t *map, const char *key, ncp_int32_t *value)
 * @brief Returns the signed 32-bit value for the specified attribute
 */
NCP_API ncp_st_t ncp_map_get_i32(ncp_map_t *map, const char *key, ncp_int32_t *value);
/*!
 * @fn ncp_st_t ncp_map_get_i64(ncp_map_t *map, const char *key, ncp_int64_t *value)
 * @brief Returns the signed 64-bit value for the specified attribute
 */
NCP_API ncp_st_t ncp_map_get_i64(ncp_map_t *map, const char *key, ncp_int64_t *value);
/*!
 * @fn ncp_st_t ncp_map_get_float(ncp_map_t *map, const char *key, float *value)
 * @brief Returns the float value for the specified attribute
 */
NCP_API ncp_st_t ncp_map_get_float(ncp_map_t *map, const char *key, float *value);
/*!
 * @fn ncp_st_t ncp_map_get_str(ncp_map_t *map, const char *key, char **value)
 * @brief Returns the str value for the specified attribute
 */
NCP_API ncp_st_t ncp_map_get_str(ncp_map_t *map, const char *key, char **value);
/*!
 * @fn ncp_st_t ncp_map_get_bin(ncp_map_t *map, const char *key, char **value, ncp_uint32_t *len)
 * @brief Returns the bin value for the specified attribute
 */
NCP_API ncp_st_t ncp_map_get_bin(ncp_map_t *map, const char *key, char **value, ncp_uint32_t *len);
/*
 * @fn ncp_st_t ncp_map_get_map(ncp_map_t *map, const char *key, ncp_map_t **value)
 * @brief Returns sub-map within the current map.
 */
NCP_API ncp_st_t ncp_map_get_map(ncp_map_t *map, const char *key, ncp_map_t **value);
/*!
 * @fn ncp_st_t ncp_map_get_bool(ncp_map_t *map, const char *key, ncp_bool_t *value)
 * @brief Returns the boolean value for the specified attribute
 */
NCP_API ncp_st_t ncp_map_get_bool(ncp_map_t *map, const char *key, ncp_bool_t *value);
/*!
 * @fn ncp_st_t ncp_map_get_u32(ncp_map_t *map, const char *key, ncp_uint32_t *value)
 * @brief Returns the unsigned 32-bit value for the specified attribute
 */
NCP_API ncp_st_t ncp_map_get_u32(ncp_map_t *map, const char *key, ncp_uint32_t *value);
/*!
 * @fn ncp_st_t ncp_map_get_u64(ncp_map_t *map, const char *key, ncp_uint64_t *value)
 * @brief Returns the unsigned 64-bit value for the specified attribute
 */
NCP_API ncp_st_t ncp_map_get_u64(ncp_map_t *map, const char *key, ncp_uint64_t *value);
/*
 * @fn ncp_st_t ncp_map_get_double(ncp_map_t *map, const char *key, double *value)
 * @brief Returns the double value for the specified attribute
 */
NCP_API ncp_st_t ncp_map_get_double(ncp_map_t *map, const char *key, double *value);

/*!
 * @fn ncp_st_t ncp_map_get_type(ncp_map_t *map, const char *key, ncp_map_type_t *type)
 * @brief Returns the type of the value for the specified key
 */
NCP_API ncp_st_t ncp_map_get_type(ncp_map_t *map, const char *key, ncp_map_type_t *type);

/*!
 * @fn ncp_st_t ncp_map_delete(ncp_map_t *map, const char *key)
 * @brief Method to delete a given key and it's associated value
 */
NCP_API ncp_st_t ncp_map_delete(ncp_map_t *map, const char *key);

/*!
 * @fn ncp_st_t ncp_map_length(ncp_map_t *map, ncp_uint32_t *length)
 * @brief Returns the number of keys in the map
 */
NCP_API ncp_st_t ncp_map_length(ncp_map_t *map, ncp_uint32_t *length);

/*!
 * @fn ncp_st_t ncp_map_clear(ncp_map_t *map)
 * @brief Deletes all keys and values without deleting the map itself
 */
NCP_API ncp_st_t ncp_map_clear(ncp_map_t *map);

/*!
 * Methods to iterate through the map keys and values
 */
/*!
 * @fn ncp_st_t ncp_map_get_ith_key(ncp_map_t *map, ncp_int32_t i, char **key)
 * @brief  Returns the ith key
 */
NCP_API ncp_st_t ncp_map_get_ith_key(ncp_map_t *map, ncp_int32_t i, char **key);
/*!
 * @fn ncp_st_t ncp_map_get_ith_value(ncp_map_t *map, ncp_int32_t i, ncp_map_value_t **value)
 * @brief  Returns the ith value
 */
NCP_API ncp_st_t ncp_map_get_ith_value(ncp_map_t *map, ncp_int32_t i, ncp_map_value_t **value);
/*!
 * @fn ncp_st_t ncp_map_get_ith_key_value(ncp_map_t *map, ncp_int32_t i, char* key, ncp_map_value_t **value)
 * @brief  Returns the ith value, for the specific key. If  key is NULL or empty string, default to ith_value.
 */
NCP_API ncp_st_t ncp_map_get_ith_key_value(ncp_map_t *map, ncp_int32_t idx, const char* key, ncp_map_value_t **value);
/*!
 * @fn ncp_st_t ncp_map_get_ith_type(ncp_map_t *map, ncp_int32_t i, ncp_map_type_t *type)
 * @brief Returns the ith value type
 */
NCP_API ncp_st_t ncp_map_get_ith_type(ncp_map_t *map, ncp_int32_t i, ncp_map_type_t *type);

/*!
 * Method to decode a binary buffer into the map
 */
/*!
 * @fn ncp_st_t ncp_map_decode(ncp_map_t *map, char *buf, ncp_int32_t len)
 * @brief Constructs the attributes and values from an encoded buffer
 */
NCP_API ncp_st_t ncp_map_decode(ncp_map_t *map, char *buf, ncp_int32_t len);
NCP_API ncp_st_t ncp_map_decode_from(ncp_map_t *map, ncp_read_fn_t rdfn, void *arg);
/*!
 * @fn ncp_st_t ncp_map_encode(ncp_map_t *map, char **buf, ncp_int32_t *len)
 * @brief Encodes a given map to a buffer.
 */
NCP_API ncp_st_t ncp_map_encode(ncp_map_t *map, char **buf, ncp_int32_t *len);
NCP_API ncp_st_t ncp_map_encode_to(ncp_map_t *map, ncp_write_fn_t wrfn, void *arg);

/*!
 * @fn ncp_st_t ncp_map_copy(ncp_map_t *ncp_map, ncp_map_t *ncp_mapcopy);
 * @brief Method to copy a map into another map
 * @details Copies contents of ncp_map into ncp_mapcopy
 */
NCP_API ncp_st_t ncp_map_copy(ncp_map_t *ncp_map, ncp_map_t *ncp_mapcopy);

/*!
 * Memory allocation routines used within the ncp_map functions
 * These are exposed if the application wants to allocate/free memory
 * for ncp_map_value_t structures
 */
NCP_API void *ncp_map_malloc(ncp_int32_t size);
NCP_API void *ncp_map_realloc(void *ptr, ncp_int32_t size);
NCP_API void  ncp_map_free(void *ptr);
NCP_API char *ncp_map_strdup(const char *str);

NCP_API ncp_st_t ncp_map_dump_to_console(ncp_map_t *map);
#ifndef NCP_KERNEL
NCP_API ncp_st_t ncp_map_dump_to_stream(ncp_map_t *ncp_map, FILE *stream);
NCP_API ncp_st_t ncp_map_dump_full_map(ncp_map_t *ncp_map, FILE *stream);
#endif

/* max string length for a fully qualified config attribute */
#define NCP_MAP_MAX_ATTR_STR_LENGTH 1024

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* __ncp_map_h__ */
