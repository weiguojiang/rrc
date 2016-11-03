/**************************************************************************
 **                                                                        *
 **                           Intel CONFIDENTIAL           *
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
 ** **************************************************************************/
/*! @file      ncp_ce.h
 *  @brief     Compute Engine
 * 
 *  @addtogroup _ce_ Compute Engine
 * 
 *  @{
 */


#ifndef __NCP_CE_H__
#define __NCP_CE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ncp_llist.h"

/*!
 * @enum   ncp_ce_module_t
 * @brief  This enum defines the CE modules of the system
 */
typedef enum
{
    /*!
     * @brief MPPX State Engine CE
     */
    NCP_CE_MODULE_SE,
    /*!
     * @brief MTM Buffer Manager CE
     */
    NCP_CE_MODULE_TM,
    /*!
     * @brief MTM Traffic Shaper CE
     */
    NCP_CE_MODULE_TS,
    /*!
     * @brief Stream Editor CE
     */
    NCP_CE_MODULE_SED
} ncp_ce_module_t;

typedef struct ncp_ce_script_status_s ncp_ce_script_status_t;

/*!
 * @brief Data structure for the CE script status parameters, used for
 *        ncp_ce_script_status_get()
 */
struct ncp_ce_script_status_s {
    /*!
     * @brief Script ID
     */
    ncp_uint32_t id;
    /*!
     * @brief Script size, given in VLIWs
     */
    ncp_uint32_t size;
    /*!
     * @brief TRUE if script is currently loaded, FALSE otherwise
     */
    ncp_bool_t loaded;
    /*!
     * @brief Number of outstanding references for the script
     */
    ncp_uint32_t referenceCount;
};

/* APIs */

/*! @fn ncp_st_t ncp_ce_script_load(ncp_hdl_t ncpHdl, ncp_ce_module_t ceMod, ncp_uint32_t *id,
        ncp_uint32_t numIds)
    @brief Dynamically loads specified scripts into the indicated Compute Engine
    @param ncpHdl Incoming handle of the current NCP device
    @param ceMod Compute Engine target module.  Can be NCP_CE_MODULE_SE, NCP_CE_MODULE_TM,
           NCP_CE_MODULE_TS, or NCP_CE_MODULE_SED.
    @param id Array that specifies the IDs of scripts to load.  Each ID must correspond
           to an unloaded script that was specified during configuration or upgrade.  If
           a script-specific error is encountered, the script ID of the script causing
           the error is returned in id[0].
    @param numIds Number of IDs to load.  Up to 128 IDs can be loaded dynamically.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_CE_INVALID_REGION ceMod does not specify a valid CE in the system
    @retval NCP_ST_CE_SCRIPT_INVALID_ID An invalid script ID was specified in the id array,
            or an invalid number of scripts was specified
    @retval NCP_ST_CE_SCRIPT_LOADED A script specified in the id array was already loaded
    @retval NCP_ST_CE_LOAD_FAILED There was an error when loading the new script image to
            the specified CE
    @retval NCP_ST_* Lower level NCP device access error codes
*/

NCP_API ncp_st_t
ncp_ce_script_load(
                   ncp_hdl_t ncpHdl,
                   ncp_ce_module_t ceMod,
                   ncp_uint32_t *id,
                   ncp_uint32_t numIds);

/*! @fn ncp_st_t ncp_ce_script_unload(ncp_hdl_t ncpHdl, ncp_ce_module_t ceMod, ncp_uint32_t *id,
        ncp_uint32_t numIds)
    @brief Unloads specified scripts from the indicated Compute Engine memory
    @param ncpHdl Incoming handle of the current NCP device
    @param ceMod Compute Engine target module.  Can be NCP_CE_MODULE_SE, NCP_CE_MODULE_TM,
           NCP_CE_MODULE_TS, or NCP_CE_MODULE_SED.
    @param id Array that specifies the IDs of scripts to unload.  Each ID must
           correspond to an unloaded script that was specified during configuration or
           upgrade.  If a script-specific error is encountered, the script ID of the
           script causing the error is returned in id[0].
    @param numIds Number of IDs to unload.  Up to 128 IDs can be unloaded dynamically.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_CE_INVALID_REGION ceMod does not specify a valid CE in the system
    @retval NCP_ST_CE_SCRIPT_INVALID_ID An invalid script ID was specified in the id array,
            or an invalid number of scripts was specified
    @retval NCP_ST_CE_SCRIPT_NOT_LOADED A script specified in the id array was not loaded
    @retval NCP_ST_CE_SCRIPT_IN_USE A script specified in the id array has a nonzero
            reference count
    @retval NCP_ST_CE_LOAD_FAILED There was an error when loading the new script image to
            the specified CE
    @retval NCP_ST_* Lower level NCP device access error codes
*/

NCP_API ncp_st_t
ncp_ce_script_unload(
                     ncp_hdl_t ncpHdl,
                     ncp_ce_module_t ceMod,
                     ncp_uint32_t *id,
                     ncp_uint32_t numIds);

/*! @fn ncp_st_t ncp_ce_script_status_get(ncp_hdl_t ncpHdl, ncp_ce_module_t ceMod,
        ncp_uint32_t id, ncp_ce_script_status_t *status)
    @brief Returns the status of the specified script
    @param ncpHdl Incoming handle of the current NCP device
    @param ceMod Compute Engine target module
    @param id ID of script
    @param status Returned struct that contains the script status
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_INVALID_PARAMETER An invalid pointer was passed in the status field
    @retval NCP_ST_DEV_INVALID_BUFFER The specified CE was not correctly configured
    @retval NCP_ST_CE_INVALID_REGION ceMod does not specify a valid CE in the system
    @retval NCP_ST_CE_SCRIPT_INVALID_ID An invalid script ID was specified in the id array,
            an invalid number of scripts was specified, or the CE was not properly configured
    @retval NCP_ST_* Lower level NCP device access error codes
*/

NCP_API ncp_st_t
ncp_ce_script_status_get(
                         ncp_hdl_t ncpHdl,
                         ncp_ce_module_t ceMod,
                         ncp_uint32_t id,
                         ncp_ce_script_status_t *status);

/*! @fn ncp_st_t ncp_ce_script_freespace_get(ncp_hdl_t ncpHdl, ncp_ce_module_t ceMod,
        ncp_uint32_t *size)
    @brief Returns available script memory for the specified Compute Engine
    @param ncpHdl Incoming handle of the current NCP device
    @param ceMod Compute Engine target module.  Can be NCP_CE_MODULE_SE, NCP_CE_MODULE_TM,
           NCP_CE_MODULE_TS, or NCP_CE_MODULE_SED.
    @param size Returned available size, specified in VLIWs.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_DEV_INVALID_BUFFER An invalid pointer was passed in the size field
    @retval NCP_ST_CE_INVALID_REGION ceMod does not specify a valid CE in the system
    @retval NCP_ST_* Lower level NCP device access error codes
*/

NCP_API ncp_st_t
ncp_ce_script_freespace_get(
                            ncp_hdl_t ncpHdl,
                            ncp_ce_module_t ceMod,
                            ncp_uint32_t *size);

/*! @fn ncp_st_t ncp_ce_script_reference_add(ncp_hdl_t ncpHdl, ncp_ce_module_t ceMod,
        ncp_uint32_t id)
    @param ncpHdl Incoming handle of the current NCP device
    @param ceMod Compute Engine target module.  Can be NCP_CE_MODULE_SE, NCP_CE_MODULE_TM,
           NCP_CE_MODULE_TS, or NCP_CE_MODULE_SED.
    @param id ID of the referenced script.  The ID must correspond to a loaded script.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_CE_INVALID_REGION ceMod does not specify a valid CE in the system
    @retval NCP_ST_CE_SCRIPT_INVALID_ID An invalid script ID was specified
    @retval NCP_ST_* Lower level NCP device access error codes
*/

NCP_API ncp_st_t
ncp_ce_script_reference_add(
                            ncp_hdl_t ncpHdl,
                            ncp_ce_module_t ceMod,
                            ncp_uint32_t id);

/*! @fn ncp_st_t ncp_ce_script_reference_rem(ncp_hdl_t ncpHdl, ncp_ce_module_t ceMod,
        ncp_uint32_t id)
    @brief Decrements the reference count for the specified script
    @param ncpHdl Incoming handle of the current NCP device
    @param ceMod Compute Engine target module.  Can be NCP_CE_MODULE_SE, NCP_CE_MODULE_TM,
           NCP_CE_MODULE_TS, or NCP_CE_MODULE_SED.
    @param id ID of the referenced script.  The ID must correspond to a loaded script.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_CE_INVALID_REGION ceMod does not specify a valid CE in the system
    @retval NCP_ST_CE_SCRIPT_INVALID_ID An invalid script ID was specified
    @retval NCP_ST_* Lower level NCP device access error codes
*/

NCP_API ncp_st_t
ncp_ce_script_reference_rem(
                            ncp_hdl_t ncpHdl,
                            ncp_ce_module_t ceMod,
                            ncp_uint32_t id);

/*! @fn ncp_st_t ncp_ce_script_get_address(ncp_hdl_t ncpHdl, ncp_ce_module_t ceMod,
        ncp_uint32_t scriptId, ncp_uint16_t *pcAddress)
    @brief Returns the PC address of the script in the script IRAM
    @param ncpHdl Incoming handle of the current NCP device
    @param ceMod Compute Engine target module.  Can be NCP_CE_MODULE_SE, NCP_CE_MODULE_TM,
           NCP_CE_MODULE_TS, or NCP_CE_MODULE_SED.
    @param scriptId ID of the script for which the address is requested
    @param pcAddress The PC address of the script, specified in VLIWs and relative to the start
           of the CE's codespace.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_CE_INVALID_REGION ceMod does not specify a valid CE in the system
    @retval NCP_ST_DEV_INVALID_BUFFER An invalid pointer was passed in the pcAddress field
    @retval NCP_ST_CE_SCRIPT_INVALID_ID An invalid script ID was specified
    @retval NCP_ST_* Lower level NCP device access error codes
*/

NCP_API ncp_st_t
ncp_ce_script_get_address(
                          ncp_hdl_t ncpHdl,
                          ncp_ce_module_t ceMod,
                          ncp_uint32_t scriptId,
                          ncp_uint16_t *pcAddress);

/*! @fn ncp_st_t ncp_ce_script_get_id(ncp_hdl_t ncpHdl, ncp_ce_module_t ceMod,
        ncp_uint32_t *scriptId, ncp_uint16_t pcAddress)
    @brief Returns the ID for the script with the specified starting
           PC address in the script IRAM
    @param ncpHdl Incoming handle of the current NCP device
    @param ceMod Compute Engine target module.  Can be NCP_CE_MODULE_SE, NCP_CE_MODULE_TM,
           NCP_CE_MODULE_TS, or NCP_CE_MODULE_SED.
    @param scriptId ID of the script with the specified starting PC address
    @param pcAddress The PC address of the script, specified in VLIWs and relative to the start
           of the CE's codespace.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_CE_INVALID_REGION ceMod does not specify a valid CE in the system
    @retval NCP_ST_DEV_INVALID_BUFFER An invalid pointer was passed in the scriptId field
    @retval NCP_ST_CE_SCRIPT_INVALID_ADDRESS No matching PC address was found
    @retval NCP_ST_* Lower level NCP device access error codes
*/

NCP_API ncp_st_t
ncp_ce_script_get_id(
                     ncp_hdl_t ncpHdl,
                     ncp_ce_module_t ceMod,
                     ncp_uint32_t *scriptId,
                     ncp_uint16_t pcAddress);

/*! @fn ncp_st_t ncp_ce_script_isloaded(ncp_hdl_t ncpHdl, ncp_ce_module_t ceMod,
        ncp_uint32_t id, ncp_bool_t *isLoaded)
    @brief Returns true if the specified script is loaded in the CE instruction
           memory
    @param ncpHdl Incoming handle of the current NCP device
    @param ceMod Compute Engine target module.  Can be NCP_CE_MODULE_SE, NCP_CE_MODULE_TM,
           NCP_CE_MODULE_TS, or NCP_CE_MODULE_SED.
    @param id ID of the referenced script
    @param isLoaded True if the specified script is loaded, else false
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_CE_INVALID_REGION ceMod does not specify a valid CE in the system
    @retval NCP_ST_DEV_INVALID_BUFFER An invalid pointer was passed in the isLoaded field
    @retval NCP_ST_* Lower level NCP device access error codes
*/

NCP_API ncp_st_t
ncp_ce_script_isloaded(
                       ncp_hdl_t ncpHdl,
                       ncp_ce_module_t ceMod,
                       ncp_uint32_t id,
                       ncp_bool_t *isLoaded);

#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

/*!
 * @}
 */

#endif /* __NCP_CE_H__ */
