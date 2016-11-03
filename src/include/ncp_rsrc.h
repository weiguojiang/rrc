/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


/*! @file       ncp_rsrc.h
 *  @brief      Named Resource Management
 */

#ifndef __ncp_rsrc_h__
#define __ncp_rsrc_h__

#ifndef SWIG

#include "ncp_types.h"

#ifdef __cplusplus
extern "C" { 
#endif /* #ifdef __cplusplus */

#else

%header
%{
#include "ncp_types.h"
#include "ncp_rsrc.h"
%}

NCPTCL_SETUP();

#endif /* #ifndef SWIG */

/*!
 *  @addtogroup _rsrc_  Named Resource Management
 *  @brief      Support the use of Named Resource allocators, and user
 *              application requirements.
 *  @details This module defines the interface to a collection of NCP Resource
 *           Ids enumerations/sets.  Each member of the collection is an
 *           enumerations/sets of integer Ids that are of interest to various
 *           applications or algorithms within or using the NCP software.
 *           The interface provides mechanisms to find an enumeration/set
 *           of interest, and to safely allocate and return members of the
 *           enumeration to the algorithms.  Often the enumeration/set has
 *           been constructed in association with loading a configuration,
 *           and represents the resources limits available to the associated
 *           applications.
 *  @{
 *  @ingroup    _utility_
 */

/***************************************************************************
* Constants                                                                *
***************************************************************************/

/***************************************************************************
* Type Definitions                                                         *
***************************************************************************/

/*! @typedef void *ncp_rsrc_hdl_t
    @brief Public handle for an NCP Resource Id enumeration
*/
typedef void *ncp_rsrc_hdl_t;

/*! @enum ncp_rsrc_type_t
    @brief Use classification of the NCP Named Resources
*/
typedef enum
{
    NCP_RSRC_NS,          /*!< Base type for configuration-defined namespaces */
    NCP_RSRC_VP_CPU,      /*!< */
    NCP_RSRC_VP_MPP,      /*!< */
    NCP_RSRC_VP_EXPANDER, /*!< */
    NCP_RSRC_VP_EXPANDER_MG,/*!< Number of MG in an expander launched VP */
    NCP_RSRC_USER_DEFINED,/*!< Type for user-defined/-used resources */
    NCP_RSRC_EIOA,        /*!< Base type for eioa related resources */
    NCP_RSRC_CPU_TIMER,   /*!< Timer Module CPU Timers */
    NCP_RSRC_WILDCARD,    /*!< Describes all types; for ncp_rsrc_dump() only */
    NCP_RSRC_LAST_ENTRY   /*!< Must be last item in enum */
}
ncp_rsrc_type_t;

/*! @struct ncp_rsrc_query_t
    @brief Attribute query for an NCP Resource Id enumeration
*/
typedef struct
{
    ncp_rsrc_type_t kind;       /* Kind of RSRC of interest */
    char           *name;       /* Name of RSRC of interest */
    ncp_uint32_t    baseId;             /* BaseId for the RSRC located */
    ncp_uint32_t    numElems;           /* No. of ids for the RSRC located */
    ncp_uint32_t    numElemsFree;       /* No. of ids not allocated */
}
ncp_rsrc_query_t;

#ifdef SWIG

NCP_WO_EXCEPTIONS();

%inline
%{
NCPTCL_REF(ncp_rsrc_hdl_t);
%}

NCP_W_EXCEPTIONS();

#endif /* #ifdef SWIG */


/***************************************************************************
* Exported Functions                                                       *
***************************************************************************/

/*! @fn ncp_st_t ncp_rsrc_create(ncp_hdl_t inNcpHdl, ncp_rsrc_type_t inKind, const char *inName, ncp_uint32_t inNumElems, ncp_uint32_t inBaseId, ncp_rsrc_hdl_t *outRsrcHdl)
    @brief Create an ncp_rsrc_hdl_t enumeration object
    @param[in] inNcpHdl Handle of the current NCP configuration
    @param[in] inKind Use classification of the object to be created
    @param[in] inName Name of the object to be created
    @param[in] inNumElems Maximum number of items that may be allocated from
               the object.  Value of zero  treated as '1'.
    @param[in] inBaseId Lowest integer value that may be allocated from the
               object.  user should add this value to the range of IDs that
               it wants to allocate or verify with other APIs.
    @param[out] outRsrcHdl Location to deposit handle of the successfully created object
    @retval NCP_ST_SUCCESS RSRC object successfully created
    @retval NCP_ST_INVALID_HANDLE inNcpHdl is invalid
    @retval NCP_ST_ERROR configuration error related to RSRC prevents further operation
    @retval NCP_ST_INVALID_PARAMETER invalid argument(s) e.g. null inName, inKind out of range
    @retval NCP_ST_INVALID_VALUE invalid argument e.g. duplicate name
    @retval NCP_ST_NO_MEMORY unable to allocate memory to create RSRC
    @retval NCP_ST_RSRC_INIT_FAILED unable to initialize other resources needed to create RSRC
    @retval other device driver errors may be observed
*/
NCP_API ncp_st_t
ncp_rsrc_create(
    ncp_hdl_t       inNcpHdl,
    ncp_rsrc_type_t inKind,
    const char     *inName,
    ncp_uint32_t    inNumElems,
    ncp_uint32_t    inBaseId,
    ncp_rsrc_hdl_t *outRsrcHdl);

/*! @fn ncp_st_t ncp_rsrc_destroy(ncp_hdl_t inNcpHdl, ncp_rsrc_hdl_t inRsrcHdl)
    @brief Destroy an existing ncp_rsrc_hdl_t enumeration object
    @param[in] inNcpHdl Handle of the current NCP configuration
    @param[in] inRsrcHdl Handle of the rsrc enumeration object to be deleted
    @retval NCP_ST_SUCCESS RSRC object successfully destroyed
    @retval NCP_ST_INVALID_HANDLE inNcpHdl is invalid
    @retval NCP_ST_ERROR configuration error related to RSRC prevents further operation
    @retval NCP_ST_INVALID_PARAMETER invalid argument e.g. bad inRsrcHdl
*/
NCP_API ncp_st_t
ncp_rsrc_destroy(
    ncp_hdl_t       inNcpHdl,
    ncp_rsrc_hdl_t  inRsrcHdl);

/*! @fn ncp_st_t ncp_rsrc_find(ncp_hdl_t inNcpHdl, ncp_rsrc_type_t inKind, const char *inName, ncp_rsrc_hdl_t *outRsrcHdl)
    @brief Find a named ncp_rsrc_hdl_t enumeration object
    @param[in] inNcpHdl Handle of the current NCP configuration
    @param[in] inKind Use classification of the object to be located
    @param[in] inName Name of the object to be located
    @param[out] outRsrcHdl Location to deposit handle of the successfully located object
    @retval NCP_ST_SUCCESS RSRC object successfully located
    @retval NCP_ST_INVALID_HANDLE inNcpHdl is invalid
    @retval NCP_ST_ERROR configuration error related to RSRC prevents further operation
    @retval NCP_ST_INVALID_PARAMETER invalid argument(s) e.g. null inName, null outRsrcHdl
    @retval NCP_ST_INVALID_VALUE invalid argument e.g. combination of inKind/inName not found
*/
NCP_API ncp_st_t
ncp_rsrc_find(
    ncp_hdl_t       inNcpHdl,
    ncp_rsrc_type_t inKind,
    const char     *inName,
    ncp_rsrc_hdl_t *outRsrcHdl);

/*! @fn ncp_st_t ncp_rsrc_allocate(ncp_rsrc_hdl_t inRsrcHdl, ncp_uint32_t inNumIds, ncp_uint32_t *outStartId)
    @brief Allocate an id or ids contiguously from an existing resource where the id or ids have not been previously reserved.
    @param inRsrcHdl Handle of the current named resource object
    @param inNumIds Number of values that are to be allocated/reserved.  Must be
                    less than or equal to the maximum number of ids in the RSRC.
    @param outStartId Location to deposit the value of the lowest integer item of the range of allocated ids
    @retval NCP_ST_SUCCESS Range of ids successfully allocated
    @retval NCP_ST_INVALID_HANDLE inRsrcHdl is invalid
    @retval NCP_ST_ERROR configuration error related to RSRC prevents further operation
    @retval NCP_ST_INVALID_PARAMETER invalid argument(s) e.g. zero inNumIds, error in contiguous range
    @retval NCP_ST_RSRC_INSUFF_IDS_AVAIL number of unallocated ids remaining is less than inNumIds
    @retval NCP_ST_RSRC_INSUFF_IDS_AVAIL_IN_RANGE no range of inNumIds size found
    @retval NCP_ST_RSRC_READ_ONLY not allowed to allocate more IDs from a read-only RSRC
*/
NCP_API ncp_st_t
ncp_rsrc_allocate(
    ncp_rsrc_hdl_t inRsrcHdl,
    ncp_uint32_t   inNumIds,
    ncp_uint32_t  *outStartId);

/*! @fn ncp_st_t ncp_rsrc_allocate_fixed(ncp_rsrc_hdl_t inRsrcHdl, ncp_uint32_t inNumIds, ncp_uint32_t inStartId)
    @brief Allocate an id or ids contiguously from an existing resource where the id or ids have not been previously reserved, and the first id is inStartId.
    @param[in] inRsrcHdl Handle of the current named resource object
    @param[in] inNumIds Number of values that are to be allocated/reserved.  Must be less than or equal to the maximum number of ids in the RSRC.
    @param[in] inStartId Value of the lowest integer item of the range ids to be allocated.  Must be >= BaseId provided at RSRC creation and <= the maximum id value relative to that BaseId.
    @retval NCP_ST_SUCCESS Range of ids successfully allocated
    @retval NCP_ST_INVALID_HANDLE inRsrcHdl is invalid
    @retval NCP_ST_ERROR configuration error related to RSRC prevents further operation
    @retval NCP_ST_INVALID_PARAMETER invalid argument(s) e.g. zero inNumIds, error in contiguous range, invalid inStartId/inNumIds combination for the RSRC
    @retval NCP_ST_RSRC_INSUFF_IDS_AVAIL number of unallocated ids remaining is less than inNumIds
    @retval NCP_ST_RSRC_INSUFF_IDS_AVAIL_IN_RANGE no range of inNumIds size found relative to inStartId
    @retval NCP_ST_RSRC_READ_ONLY not allowed to allocate more IDs from a read-only RSRC
*/
NCP_API ncp_st_t
ncp_rsrc_allocate_fixed(
    ncp_rsrc_hdl_t inRsrcHdl,
    ncp_uint32_t   inNumIds,
    ncp_uint32_t   inStartId);

/*! @fn ncp_st_t ncp_rsrc_free(ncp_rsrc_hdl_t inRsrcHdl, ncp_uint32_t inStartId, ncp_uint32_t inNumIds)
    @brief Release an id or ids previously allocated from an existing resource i.e. from the inStartId free inNumIds contiguously
    @param[in] inRsrcHdl Handle of the current named resource object
    @param[in] inStartId Value of the lowest integer item of the range of allocated ids to be freed
    @param[in] inNumIds Number of items that are to be freed.
    @retval NCP_ST_SUCCESS RSRC object successfully released
    @retval NCP_ST_INVALID_HANDLE inRsrcNcpHdl is invalid
    @retval NCP_ST_ERROR configuration error related to RSRC prevents further operation
    @retval NCP_ST_INVALID_PARAMETER invalid argument(s) e.g. zero inNumIds, error specifying contiguous range or allocated ids, or invalid inStartId/inNumIds combination for the RSRC
    @retval NCP_ST_RSRC_READ_ONLY not allowed to free IDs from a read-only RSRC
*/
NCP_API ncp_st_t
ncp_rsrc_free(
    ncp_rsrc_hdl_t inRsrcHdl,
    ncp_uint32_t   inStartId,
    ncp_uint32_t   inNumIds);

/*! @fn ncp_bool_t ncp_rsrc_isset(ncp_rsrc_hdl_t inRsrcHdl, ncp_uint32_t inId)
    @brief Check whether a specified id has already been reserved within a rsrc enumeration object
    @param[in] inRsrcHdl Handle of the current named resource object
    @param[in] inId Value of the id/item of interest
    @retval TRUE RSRC valid and the specified Id is allocated
    @retval FALSE RSRC invalid or the specified Id is not allocated
*/
NCP_API ncp_bool_t
ncp_rsrc_isset(
    ncp_rsrc_hdl_t inRsrcHdl,
    ncp_uint32_t   inId);

/*! @fn ncp_st_t ncp_rsrc_query(ncp_rsrc_hdl_t inRsrcHdl, ncp_rsrc_query_t *outInfo)
    @brief Query the attributes of an NCP Resource Id enumeration
    @param[in] inRsrcHdl Handle of the current named resource object
    @param[out] outInfo Location to deposit attributes for the object
    @retval NCP_ST_SUCCESS Query performed successfully
    @retval NCP_ST_INVALID_HANDLE inRsrcNcpHdl is invalid
    @retval NCP_ST_ERROR configuration error related to RSRC prevents further operation
    @retval NCP_ST_INVALID_PARAMETER invalid argument(s) e.g. null outInfo
    @retval other device driver errors may be observed
*/
NCP_API ncp_st_t
ncp_rsrc_query(
    ncp_rsrc_hdl_t    inRsrcHdl,
    ncp_rsrc_query_t *outInfo);

/*! @fn ncp_st_t ncp_rsrc_dump(ncp_hdl_t inNcpHdl, ncp_rsrc_type_t inKind)
    @brief Dump a listing of the resources of a specified type or types to stdout
    @param[in] inNcpHdl Handle of the current NCP configuration
    @param[in] inKind Use classification of the object to be displayed (wild card is allowed)
    @retval NCP_ST_SUCCESS Information dump performed successfully
    @retval NCP_ST_INVALID_HANDLE inRsrcNcpHdl is invalid
    @retval NCP_ST_ERROR configuration error related to RSRC prevents further operation
    @retval NCP_ST_INVALID_PARAMETER invalid argument(s) e.g. inKind out of range
*/
NCP_API ncp_st_t
ncp_rsrc_dump(
    ncp_hdl_t       inNcpHdl,
    ncp_rsrc_type_t inKind);


#ifdef SWIG
NCPTCL_WO_EXCEPTIONS();
#endif /* #ifdef SWIG */


#ifndef SWIG
#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */
#endif /* #ifndef SWIG */

/*!
 * @}
 */

#endif /* __ncp_rsrc_h__ */
