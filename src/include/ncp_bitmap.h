/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*! @file        ncp_bitmap.h
 *  @brief       APIs for bitmap manipulation
 */

#ifndef _NCP_BITMAP_H_
#define _NCP_BITMAP_H_

#include "ncp_sal_target.h"
#include "ncp_types.h"

#ifdef __cplusplus
extern "C" { 
#endif

/*!
 *  @addtogroup  _bitmap_  Bitmap Object
 *  @{
 *  @ingroup     _utility_
*/

/*! @typedef void *ncp_bitmap_t
    @brief   Public handle for references to an existing bitmap object
*/
typedef void *ncp_bitmap_t;

/*! @fn ncp_bitmap_t *ncp_bitmap_create(NCP_U32 length)
    @brief Create a bitmap object
    @param[in] length Number of bits required in the bitmap object
*/
NCP_API ncp_bitmap_t *ncp_bitmap_create(NCP_U32 length);

/*! @fn ncp_uint32_t ncp_bitmap_get_size(ncp_bitmap_t *map)
    @brief Get the size of an existing bitmap object
    @param[in] map Bitmap object to query
    @returns Number of bits available in the bitmap object
*/
NCP_API ncp_uint32_t ncp_bitmap_get_size(ncp_bitmap_t *map);

/*! @fn ncp_uint32_t ncp_bitmap_delete(ncp_bitmap_t *map)
    @brief Release dynamic storage allocated to a bitmap object
    @param[in] map Bitmap object to destroy
    @returns Success/failure status
*/
NCP_API NCP_S32 ncp_bitmap_delete(ncp_bitmap_t *map);

/*! @fn ncp_uint32_t ncp_bitmap_reserve(ncp_bitmap_t *map, NCP_U32 size, NCP_U32 *base_id)
    @brief Search the speciried bit field for 'size' contiguous cleared ('0')
           bits starting a index base. An index to the first bit of the range
           is returned if found, or -2 if the number of consecutive bits can't
           be found, or -1 for all other errors. If the bits are found they
           are set in the bit field.
    @param[in] map Bitmap object to update
    @param[in] size Number of bits to reserve
    @param[out] base_id Location to deposit index to first bit id if successful
    @returns Success/failure status
*/
NCP_API NCP_S32 ncp_bitmap_reserve(ncp_bitmap_t *map, NCP_U32 size, NCP_U32 *base_id);

/*! @fn ncp_uint32_t ncp_bitmap_find(ncp_bitmap_t *map, NCP_U32 size, NCP_U32 *base_id)
    @brief Search the specified bitmap for 'size' contiguous cleared ('0')
           bits starting at index base.  An index to the first bit of the
           range is returned if found or -1 if the bits can't be found.
           The bitmap is not modified.
    @param[in] map Bitmap object to query
    @param[in] size Number of bits to reserve
    @param[out] base_id Location to deposit index to first bit id if successful
    @returns Success/failure status
*/
NCP_API NCP_S32 ncp_bitmap_find(ncp_bitmap_t *map, NCP_U32 size, NCP_U32 *base_id);

/*! @fn ncp_uint32_t ncp_bitmap_find_from(ncp_bitmap_t *map, NCP_U32 size, NCP_U32 start, NCP_U32 *base_id)
    @brief Search the specified bitmap for 'size' contiguous cleared ('0')
           bits starting at index base.  An index to the first bit of the
           range is returned if found or -1 if the bits can't be found.
           The bitmap is not modified.
    @param[in] map Bitmap object to query
    @param[in] start index to start looking from. If zero, it will start from first free index.
    @param[in] size Number of bits to reserve
    @param[out] base_id Location to deposit index to first bit id if successful
    @returns Success/failure status
*/
NCP_API NCP_S32 ncp_bitmap_find_from(ncp_bitmap_t *map, NCP_U32 start, NCP_U32 size, NCP_U32 *base_id);


/*! @fn ncp_uint32_t ncp_bitmap_count(ncp_bitmap_t *map, NCP_BOOL value);
    @brief Count the number of 'value' bits in a given 'map'
    @param[in] map Bitmap object to query
    @param[in] value Set/clear value for which to search
    @returns Number of bits of the specified 'value'
*/
NCP_API NCP_U32 ncp_bitmap_count(ncp_bitmap_t *map, NCP_BOOL value);

/*! NCP_S32 ncp_bitmap_reserve_fixed(ncp_bitmap_t *map, NCP_U32 size, NCP_U32 *base_id);
    @brief Try to reserve 'size' bits at the given 'base_id' location
           If the bits are found they are set in the bit field.
    @param[in] map Bitmap object to query
    @param[in] size Number of bits to reserve
    @param[out] base_id Location to deposit index to first bit id if successful
    @retval n Number of bits of the specified 'value' allocated.
    @retval -2 if the number of consecutive bits can't be found
    @retval -1 for all other errors
*/
NCP_API NCP_S32 ncp_bitmap_reserve_fixed(ncp_bitmap_t *map, NCP_U32 size, NCP_U32 base_id);

/*! NCP_S32 ncp_bitmap_unreserve(ncp_bitmap_t *map, NCP_U32 size, NCP_U32 base_id);
    @brief Try to release 'size' bits at the given 'base_id' location
    @param[in] map Bitmap object to update
    @param[in] size Number of bits to release
    @param[in] base_id Index to first bit id to unreserve
    @returns Success/failure status
*/
NCP_API NCP_S32 ncp_bitmap_unreserve(ncp_bitmap_t *map, NCP_U32 size, NCP_U32 base_id);

/*! NCP_S32 ncp_bitmap_set(ncp_bitmap_t *map, NCP_U32 id);
    @brief[in] Try to set bit at the given 'id' location
    @param[in] map Bitmap object to update
    @param[in] id Index to bit id to be set
    @returns Success/failure status
*/
NCP_API NCP_S32 ncp_bitmap_set(ncp_bitmap_t *map, NCP_U32 id);

/*! NCP_S32 ncp_bitmap_isset(ncp_bitmap_t *map, NCP_U32 id);
    @brief Check whether bit at the given 'id' location is set ('1')
    @param[in] map Bitmap object to query
    @param[in] id Index to bit id to be queried
    @returns Success/failure status
*/
NCP_API NCP_BOOL ncp_bitmap_isset(ncp_bitmap_t *map, NCP_U32 id);

/*! NCP_S32 ncp_bitmap_clr(ncp_bitmap_t *map, NCP_U32 id);
    @brief Try to clear bit at the given 'id' location
    @param[in] map Bitmap object to update
    @param[in] id Index to bit id to be clear
    @returns Success/failure status
*/
NCP_API NCP_S32 ncp_bitmap_clr(ncp_bitmap_t *map, NCP_U32 id);

/*! ncp_bitmap_t* ncp_bitmap_copy(ncp_bitmap_t *map);
    @brief Make a copy of the argument bitmap
    @param[in] map Bitmap object to duplicate
    @returns Duplicate bitmap or null when failure
*/
NCP_API ncp_bitmap_t *ncp_bitmap_copy(ncp_bitmap_t *map);

/*! @fn NCP_S32 ncp_bitmap_reserve_aligned(ncp_bitmap_t *map, ncp_uint32_t size, ncp_uint32_t *base,ncp_uint32_t align)
    @brief Find size bits on given alignment.
    @param[in] map Bitmap object to query
    @param[in] size Length in bits of block space
    @param[out] base Calculated starting bit id of block space
    @param[in] align Space is/is not aligned on byte boundaries
    @returns Success/failure status
*/
NCP_API NCP_S32 ncp_bitmap_reserve_aligned(ncp_bitmap_t *map, 
                                           NCP_U32 size,
                                           NCP_U32 align,
                                           NCP_U32 *base);

/*! @fn NCP_S32 ncp_bitmap_reserve_ranged(ncp_bitmap_t *map, ncp_uint32_t size, ncp_uint32_t *base,ncp_uint32_t startRange, ncp_uint32_t endRange)
    @brief Find size available bits in the range given.
    @param[in] map Bitmap object to query
    @param[in] size Length in bits of block space
    @param[out] base Calculated starting bit id of block space
    @param[in] startRange First bit id to check
    @param[in] endRange Last bit id to check
    @returns Success/failure status
*/
NCP_API NCP_S32
ncp_bitmap_reserve_ranged(ncp_bitmap_t *map, ncp_uint32_t size, 
                          ncp_uint32_t *base,ncp_uint32_t startRange,
                          ncp_uint32_t endRange);

/*! @fn NCP_S32 ncp_bitmap_reserve_aligned_offsets(ncp_bitmap_t *map, ncp_uint32_t size, ncp_uint32_t *base,ncp_uint32_t align, ncp_uint32_t startOff, ncp_uint32_t endOff)
    @brief Find size bits on given alignment/offset constraints.
    @param[in] map Bitmap object to query
    @param[in] size Length in bits of block space
    @param[in] base Calculated starting bit id of block space
    @param[in] align Space is/is not aligned on byte boundaries
    @param[in] startOff First bit id to check
    @param[in] endOff Last bit id to check
    @returns Success/failure status
*/
NCP_API NCP_S32
ncp_bitmap_reserve_aligned_offsets(ncp_bitmap_t *map, ncp_uint32_t size, 
                                   ncp_uint32_t *base,ncp_uint32_t align,
                                   ncp_uint32_t startOff,ncp_uint32_t endOff);

/*! @fn NCP_S32 ncp_bitmap_reserve_ranged_test(ncp_bitmap_t *map, ncp_uint32_t size, ncp_uint32_t *base,ncp_uint32_t startRange, ncp_uint32_t endRange)
    @brief Try finding size available bits in the range given.  It just
           tries to find them, and will not really reserve them.
    @param[in] map Bitmap object to query
    @param[in] size Length in bits of block space
    @param[out] base Calculated starting bit id of block space
    @param[in] startRange First bit id to check
    @param[in] endRange Last bit id to check
    @returns Success/failure status
*/
NCP_API NCP_S32
ncp_bitmap_reserve_ranged_test(ncp_bitmap_t *map, ncp_uint32_t size, 
                               ncp_uint32_t *base,ncp_uint32_t startRange,
                               ncp_uint32_t endRange);

/*! @fn NCP_S32 ncp_bitmap_reserve_aligned_offsets_test(ncp_bitmap_t *map, ncp_uint32_t size, ncp_uint32_t *base,ncp_uint32_t align, ncp_uint32_t startOff, ncp_uint32_t endOff)
    @brief Try finding size bits on given alignment/offset constraints.
    @param[in] map Bitmap object to query
    @param[in] size Length in bits of block space
    @param[out] base Calculated starting bit id of block space
    @param[in] align Space is/is not aligned on byte boundaries
    @param[in] startOff First bit id to check
    @param[in] endOff Last bit id to check
    @returns Success/failure status
*/
NCP_API NCP_S32
ncp_bitmap_reserve_aligned_offsets_test(ncp_bitmap_t *map, ncp_uint32_t size, 
                                        ncp_uint32_t *base,ncp_uint32_t align,
                                        ncp_uint32_t startOff,
                                        ncp_uint32_t endOff);

/*! @fn NCP_S32 ncp_bitmap_reserve_test(ncp_bitmap_t *map, NCP_U32 size, NCP_U32 *base_id)
    @brief Test if we can reserve a block space
    @param[in] map Bitmap object to query
    @param[in] size Length in bits of desired block space
    @param[out] base_id Starting bit index of block space if successful
    @returns Success/failure status
*/
NCP_API NCP_S32 
ncp_bitmap_reserve_test(ncp_bitmap_t  *map, 
                        NCP_U32        size, 
                        NCP_U32       *base_id);

/*! @typedef ncp_bitmap_find_spans_callback_fn_t
    @brief   Function signature for callback functions passed to ncp_bitmap_find_spans
*/
typedef int (*ncp_bitmap_find_spans_callback_fn_t)(ncp_uint32_t start,ncp_uint32_t stop,void *args);

/*! @fn NCP_S32 ncp_bitmap_find_spans(ncp_bitmap_t *map,ncp_bitmap_find_spans_callback_fn_t fn, void *args)
    @brief Traverse the bitmap, invoking the callback function for every
           1->0,0,0,...0->1 transition span found.
    @param[in] map Bitmap object to query
    @param[in] fn Callback function to invoke
    @param[in] args Additional argumenst to pass to callback function
    @returns Success/failure status
*/
NCP_API NCP_S32
ncp_bitmap_find_spans(ncp_bitmap_t *map,ncp_bitmap_find_spans_callback_fn_t fn, void *args);

/*! @fn ncp_uint32_t ncp_pick_a_nice_id_from_bitmap(ncp_bitmap_t *map)
    @brief Given a bitmap, choose a bit so that the map is as "balanced" as
           possible.  This should be helpful in picking the initial starting
           slot for a queue in the static timeslot table, especially when
           there are many queues with the same or similar rates/frequencies,
           where this will help differentiate their phases so that there are
           not clumps in the timeslot table.
    @param[in] map Bitmap object to query
    @returns Best start point for some algorithms
*/
NCP_API ncp_uint32_t ncp_pick_a_nice_id_from_bitmap(ncp_bitmap_t *map);

/*! @fn ncp_uint32_t ncp_pick_a_nice_id_from_bitmap1(ncp_bitmap_t *map)
    @brief This algorithm is a faster and simpler way to get the best start.
           But in some situations, the algorithm may not give a balanced
           time slot allocation.  The function determines the biggest
           unused timeslot gap in the given map and returns the midpoint
           of that unused gap as the start.  If no slot available, it
           returns size.
    @param[in] map Bitmap object to query
    @returns Best start point for some algorithms
*/
NCP_API ncp_uint32_t ncp_pick_a_nice_id_from_bitmap1(ncp_bitmap_t *map);


#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* _NCP_BITMAP_H_ */
