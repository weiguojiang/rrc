/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*! @file      ncp.h
 *  @brief     Top level header file for NCP RTE
 *  @addtogroup _ncp_top_ Top-level Structures & APIs
 *  @brief This is the top-level header file for the NCP RTE. 
 *  @details
 *  A user application should be able to include this single file
 *  and have access to all of the NCP APIs.  Everything in this file, 
 *  and included by it, is part of the external, published API. 
 *  Do not put internal private definitions, macros, etc. in here!
 *
 * @{
 */

#ifndef __NCP_H__
#define __NCP_H__



/***************************************************************************
* Global Header Files                                                      *
***************************************************************************/

#include "ncp_sal.h"
#include "ncp_types.h"
#include "ncp_dev.h"
#include "ncp_task.h"
#include "ncp_map.h"
#include "ncp_config.h"
#include "ncp_vpm.h"
#include "ncp_regions.h"

#ifndef NCP_KERNEL

#include "ncp_bitmap.h"
#include "ncp_rsrc.h"
#include "ncp_ce.h"
#include "ncp_cow.h"
#include "ncp_eioa.h"
#include "ncp_eioa_mac.h"
#include "ncp_eioa_hss_utils.h"
#include "ncp_eioa_switch.h"
#include "ncp_mtm.h"
#include "ncp_se.h"
#include "ncp_sed.h"
#include "ncp_smon.h"
#include "ncp_spp.h"
#include "ncp_timer.h"
#include "ncp_dpi.h"
#include "ncp_dpi_hfa.h"
#include "ncp_ptn.h"
#include "ncp_mme.h"
#include "ncp_bp.h"

#endif

/***************************************************************************
* Module Header Files                                                      *
***************************************************************************/


/***************************************************************************
* Type definitions                                                         *
***************************************************************************/

/*! @typedef ncp_uint32_t    ncp_bus_adaptor_t
    @brief   Type for the value of the register 0x301.0.0x4 from NCA
             (NCP_REGION_DRIVER_CFG.NCP_DEV_CFG_BUS_ADAPTOR)
 */
typedef ncp_uint32_t    ncp_bus_adaptor_t;

/*! @struct ncp_device_info_t
    @brief Query result about the open NCP device
*/
typedef struct
{
    ncp_rev_id_t        revId;
    ncp_bus_adaptor_t   busAdaptor;
}
ncp_device_info_t;

/***************************************************************************
* Hardware I/O (hwio) Trace Function Definitions                           *
***************************************************************************/

typedef enum
{
    NCP_HWIO_READ32 = 0,
    NCP_HWIO_WRITE32,
    NCP_HWIO_FILL32,
    NCP_HWIO_CRBF,
    NCP_HWIO_CRRMW,
    NCP_HWIO_CRSW,
    NCP_HWIO_CRBBW,
    NCP_HWIO_CRBSW,
    NCP_HWIO_CRBBF,
    NCP_HWIO_CSMBR,
    NCP_HWIO_CSMBW,
    NCP_HWIO_USLEEP,
    NCP_HWIO_RESET,
    NCP_HWIO_POLL,
    NCP_HWIO_POST_RESET,
    NCP_HWIO_COMMENT,
    NCP_HWIO_TRANS_START,
    NCP_HWIO_TRANS_UDELAY,
    NCP_HWIO_TRANS_STALL_2ND_PASS_POLL,
    NCP_HWIO_TRANS_END,
    NCP_HWIO_READ16,
    NCP_HWIO_WRITE16,
    NCP_HWIO_READ8,
    NCP_HWIO_WRITE8,
    NCP_HWIO_READ64,
    NCP_HWIO_WRITE64
} ncp_hwio_type_t;

typedef struct
{
    ncp_region_id_t regionId;
    ncp_uint64_t offset;
    ncp_uint32_t *buffer;
    ncp_uint32_t count;
    ncp_uint32_t xferWidth;
    ncp_uint32_t flags;
} ncp_hwio_rw_t;

typedef struct 
{
    ncp_region_id_t regionId;
    ncp_uint64_t offset;
    ncp_uint32_t delayLoops;
    ncp_uint32_t delayTime;
    ncp_uint32_t mask;
    ncp_uint32_t value;
} ncp_hwio_poll_t;

typedef void (*ncp_hwio_trace_func_t)(
    void *hwioFuncArg,
    ncp_hwio_type_t hwioType,
    ncp_uint32_t devNum,
    void *hwioArg);

NCP_API
ncp_st_t ncp_hwio_trace(
    ncp_hwio_trace_func_t hwioFunc,
    void * hwioFuncArg);

/***************************************************************************
* Exported APIs                                                            *
***************************************************************************/

NCP_API
ncp_st_t ncp_cold_start(void);


/*! @fn ncp_st_t ncp_device_info_get(ncp_hdl_t inNcpHdl, ncp_device_info_t *outDeviceInfo)
    @brief Dump a listing of the resources of a specified type to stdout
    @param[in] inNcpHdl Handle of the current NCP configuration
    @param[out] outDeviceInfo Location in calling function at which to place results
    @retval NCP_ST_SUCCESS Data retrieved successfully
    @retval NCP_ST_INVALID_HANDLE inNcpHdl is invalid
    @retval NCP_ST_INVALID_PARAMETER invalid argument(s) e.g. outDeviceInfo is NULL
    @retval other Device specific errors may occur
*/
NCP_API
ncp_st_t ncp_device_info_get(
    ncp_hdl_t            inNcpHdl,
    ncp_device_info_t   *outDeviceInfo);


/*! @fn ncp_st_t ncp_alarm_get(ncp_dev_hdl_t devHdl, ncp_bool_t blocking, ncp_alarm_source_t *alarm) 
    @brief This function retrieves the current alarm for the specified ACP
           device, possibly blocking until one or more pending alarams has
           been triggered.  Detailed information about only one of the
           possible alarms is returned for each call to this function.
    @param[in] devHdl NCP device driver handle
    @param[in] blocking specifies whether this API is blocking or non-blocking
    @param[out] alarm pointer to user provided alarm structure 
    @retval NCP_ST_SUCCESS Data retrieved successfully
    @retval NCP_ST_INVALID_HANDLE inNcpHdl is invalid
    @retval NCP_ST_INVALID_PARAMETER invalid argument(s) e.g. outDeviceInfo is NULL
    @retval NCP_ST_ALARM_NONE_PENDING No alarms ready to be reported
    @retval other Device specific errors may occur
*/
NCP_API
ncp_st_t ncp_alarm_get(
    ncp_dev_hdl_t        devHdl,
    ncp_bool_t           blocking,
    ncp_alarm_source_t  *outAlarm);

/*!
 * @}
 */


#endif /* __NCP_H__ */
