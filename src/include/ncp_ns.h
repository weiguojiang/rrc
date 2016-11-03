/**************************************************************************
 **                                                                       *
 **                           Intel CONFIDENTIAL                            *
 **                           PROPRIETARY NOTE                            *
 **                                                                       *
 **    This software contains information confidential and proprietary    *
 **    to Intel Corporation.  It shall not be reproduced in whole or in *
 **    part, or transferred to other documents, or disclosed to third     *
 **    parties, or used for any purpose other than that for which it was  *
 **    obtained, without the prior written consent of Intel Corporation.*
 **    (c) 2008-2014, Intel Corporation.  All rights reserved.          *
 **                                                                       *
 **
 **
 **  **********************************************************************/
/*! @file        ncp_ns.h
 *  @brief       Namespace access/management services (ns)
*/

#ifndef _NCP_NS_H_
#define _NCP_NS_H_

#include "ncp.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @addtogroup  _ns_      Namespaces
 * @brief       Namespace access/management services (ns)
 * @{
 * @ingroup     _utility_
 */

/*********************************/
/* API Typedefs, Constants, etc. */
/*********************************/

    /*********************/
    /* Type descriptions */
    /*********************/

/*!
 * @enum ncp_ns_engine_t
 * @brief Enumerates the set of engines tables that Namespaces supports.
 */
typedef enum
{
    NCP_NS_ENG_PAB,
    NCP_NS_ENG_SE,
    NCP_NS_ENG_TIMER,
    NCP_NS_ENG_MTM_QUEUES,
    NCP_NS_ENG_MTM_PARAMS,
    NCP_NS_ENG_SED,
    NCP_NS_ENG_DPI,
    NCP_NS_ENG_SPP,
    NCP_NS_ENG_LAST_ENTRY,
} ncp_ns_engine_t;

/*!
 * @struct ncp_ns_entry_t
 * @brief The structure is used to retrieve information about a namespace
 *        entry and how to access it using the NCP read/write APIs.
 *        The original arguments are echoed back in case the caller needs
 *        to maintain several such references concurrently.
 */
typedef struct
{
    ncp_ns_engine_t engineNdx;          /* INOUT: Engine selection */
    ncp_uint64_t    entryId;            /* INOUT: ID/index of the entry */
    ncp_uint32_t    engineRegion;       /* E.g. NCP_REGION_PAB_TOP_PAB */
    ncp_uint32_t    rdwrRegion;         /* E.g. NCP_REGION_NCA_NIC_SYSMEM
                                         * -- region with entry's memory */
    ncp_uint64_t    offset;             /* I.e. offset to entry with
                                         * rdwrRegion */
    ncp_uint32_t    byteWidth;          /* I.e. byte with of entry to rd/wr */
} ncp_ns_entry_t;

    /********/
    /* APIs */
    /********/

/*!
 * @fn ncp_st_t ncp_ns_get_entry(ncp_dev_hdl_t devHdl, ncp_ns_engine_t engineNdx, ncp_uint64_t entryId, ncp_ns_entry_t *info, ncp_uint8_t *buffer, ncp_uint32_t bufferLen);
 * @brief Compute the location of a namespace entry for a specified engine.
 *        Provide the location information and/or the actual data back to
 *        the caller.
 * @param[in] devHdl Incoming device handle
 * @param[in] engineNdx Engine selection
 * @param[in] entryId ID/index of the entry
 * @param[out] info Information about the entry (optional)
 * @param[out] buffer Content of entry (optional)
 * @param[in] bufferLen Length of 'buffer' when it is non-NULL (optional)
 * @retval NCP_ST_SUCCESS operation successfully completed
 * @retval NCP_ST_NS_ENGINE_UNKNOWN value of 'engineNdx' not from the
 *           enumeration 'ncp_ns_engine_t'
 * @retval NCP_ST_NS_ENTRY_OUT_OF_RANGE value of 'entryId' exceeds the
 *           sizes of the engine tables configuration
 * @retval other Device specific errors may occur
 */
NCP_API ncp_st_t
ncp_ns_get_entry(
    ncp_dev_hdl_t       devHdl,
    ncp_ns_engine_t     engineNdx,
    ncp_uint64_t        entryId,
    ncp_ns_entry_t     *info,
    ncp_uint8_t        *buffer,
    ncp_uint32_t        bufferLen);


#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* _NCP_NS_H_ */
