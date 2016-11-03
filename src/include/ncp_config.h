/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*! @file      ncp_config.h
 *  @brief     Configuration Management
 * 
 *  @addtogroup _config_ Configuration Management
 * 
 *  @{
 */


#ifndef __NCP_CONFIG_H__
#define __NCP_CONFIG_H__

#ifndef SWIG

#include "ncp.h"
#include "ncp_map.h"


#ifdef __cplusplus
extern "C" {
#endif

#else

%header
%{
#include "ncp.h"
#include "ncp_map.h"
#include "ncp_config.h"
#include "ncpConfigUtil.h"
%}

%inline
%{
NCPTCL_REF(ncp_hdl_t)
NCPTCL_REF_DETAIL(ncp_hdl_t*,p_ncp_hdl_t,void,,)
%}

NCPTCL_SETUP();

NCPTCL_W_EXCEPTIONS();

#endif /* #ifndef SWIG */


/**************************************************************************/
/* Constants & Type Definitions                                           */
/**************************************************************************/

#ifndef SWIG

#define NCP_CFG_V1_COOKIE  (0x43464733) /* TEMP: use AG_CHIPSET_3_COOKIE */

/* Flags that may be passed to the config function */
#define NCP_CFG_FLAGS_DEBUG         0x1
#define NCP_CFG_FLAGS_COLD_START    0x2
#define NCP_CFG_FLAGS_CMEM_TEST     0x4
#define NCP_CFG_FLAGS_SMEM_TEST     0x8
#define NCP_CFG_FLAGS_NO_PHY_CONFIG 0x10 /* BZ: 42187 and 42192*/

/* NCP configuration modules */
typedef enum ncp_cfg_modules_s {
    NCP_CFG_NCA = 0,
    NCP_CFG_MPP,
    NCP_CFG_MME,
    NCP_CFG_MMB,
    NCP_CFG_TIMER,
    NCP_CFG_PAB,
    NCP_CFG_PIC,
    NCP_CFG_EIOA,
    NCP_CFG_EIOA_SWITCH,
    NCP_CFG_MTM,
    NCP_CFG_SED,
    NCP_CFG_DPI,
    NCP_CFG_TRNG,
    NCP_CFG_PKA,
    NCP_CFG_SPP,
    NCP_CFG_CRYPTO,
    NCP_CFG_NS,
    NCP_CFG_PLL,
    NCP_CFG_SYSMEM,
    NCP_CFG_VPM,
    NCP_CFG_BP_AGG,
    NCP_CFG_ENGINES,
    NCP_CFG_LOAD,
    NCP_CFG_CAT,
    NCP_CFG_MEMORY_LAYOUT,
    NCP_CFG_TDMIOA,
    NCP_CFG_ALARM,

    NCP_CFG_COMPLETE  /* must be last entry */
} ncp_cfg_modules_t;


typedef enum ncp_cfg_status_s {
    NCP_CFG_ERROR,
    NCP_CFG_SUCCESS,
    NCP_CFG_CONFIGURED,
    NCP_CFG_FAILED,
    NCP_CFG_NO_MAP,
    NCP_CFG_NO_CFG_FN,
    NCP_CFG_NO_IMAGE
} ncp_cfg_status_t;


/* Domain configuration status */

typedef enum {
    NCP_DOMAIN_STATUS_CONFIGURED = 0,
    NCP_DOMAIN_STATUS_TBD
} ncp_domain_status_type_t; 


typedef int (* ncp_dynamic_cfg_fn_t)(
        ncp_map_t * map, 
        void *      dynamicCfgFnArg);


typedef void (* ncp_cfg_event_fn_t)( 
        char         *chipName,
        ncp_uint32_t  id,
        char         *cfgModule,
        ncp_uint32_t  cfgStatus,
        void         *eventFnArg);

#endif /* #ifndef SWIG */

/**************************************************************************/
/* APIs                                                                   */
/**************************************************************************/

#ifndef SWIG
/*!
 * @fn ncp_st_t ncp_config_handle_validate(ncp_hdl_t ncpHdl)
 * @param ncpHdl The handle to validate.
 *
 * @brief Validates a given handle.
 *
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 */
NCP_API ncp_st_t
ncp_config_handle_validate(ncp_hdl_t ncpHdl);
#endif /* #ifndef SWIG */

/*!
 * @fn ncp_st_t ncp_config_destroy(ncp_hdl_t ncpHdl)
 * @param ncpHdl The handle to destroy.
 * @brief Destroys the given handle and frees up all resources allocated to it.
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 */
NCP_API ncp_st_t
ncp_config_destroy(ncp_hdl_t ncpHdl);


/*!
 * @fn ncp_st_t ncp_config_domain_id_set( ncp_dev_hdl_t devHdl, ncp_uint32_t domainId)

 * @param devHdl device handle
 * @param domainId sets the AMP domainId to the specified value
 * @brief Sets the domainId for this instance
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 */
NCP_API ncp_st_t
ncp_config_domain_id_set(
    ncp_dev_hdl_t             devHdl,
    ncp_uint32_t              domainId);

/*!
 * @fn ncp_st_t ncp_config_domain_id_get( ncp_dev_hdl_t devHdl, ncp_uint32_t *domainId)

 * @param devHdl device handle
 * @param domainId retrieves the current domainId
 * @brief Gets the value of the specified attribute for the specified domain 
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 */
NCP_API ncp_st_t
ncp_config_domain_id_get(
    ncp_dev_hdl_t             devHdl,
    ncp_uint32_t             *domainId);


/*!
 * @fn ncp_st_t ncp_config_domain_status_set( ncp_dev_hdl_t devHdl, ncp_uint32_t domainId, ncp_domain_status_type_t type, ncp_bool_t status)

 * @param devHdl device handle
 * @param domainId specifies which domain instance to set
 * @param type specifies which domain attribute to set
 * @param status the value to which the specified domain attribute should be set. (TRUE or FALSE)  
 * @brief Sets the specified attribute for the specified domain to the specified value
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 */
NCP_API ncp_st_t
ncp_config_domain_status_set(
    ncp_dev_hdl_t             devHdl,
    ncp_uint32_t              domainId,
    ncp_domain_status_type_t  type,
    ncp_bool_t                status);

/*!
 * @fn ncp_st_t ncp_config_domain_status_get( ncp_dev_hdl_t devHdl, ncp_uint32_t domainId, ncp_domain_status_type_t type, ncp_bool_t *status)

 * @param devHdl device handle
 * @param domainId specifies which domain instance to get
 * @param type specifies which domain attribute to get
 * @param status returns the value of the specified domain attribute (TRUE or FALSE)  
 * @brief Gets the value of the specified attribute for the specified domain 
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 */
NCP_API ncp_st_t
ncp_config_domain_status_get(
    ncp_dev_hdl_t             devHdl,
    ncp_uint32_t              domainId,
    ncp_domain_status_type_t  type,
    ncp_bool_t               *status);


/*!
 * @fn ncp_st_t ncp_config_attach( ncp_uint32_t id, ncp_hdl_t *ncpHdl)
 *
 * @param id NCP instance 
 * @param ncpHdl handle to the NCP instance
 *
 * @brief Attach to the specified config instance. 
 *
 * This function allows a process to attach to an existing config 
 * instance. If the config instance exists then the ACP device is
 * opened (if necessary) and the object-level handle is returned.
 *
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_INVALID_INSTANCE
 *      \li ::NCP_ST_NOT_CONFIGURED
 *      \li ::NCP_ST_STATE_VERSION_MISMATCH
 *      \li ::NCP_ST_NO_MEMORY
 *
 */
NCP_API ncp_st_t
ncp_config_attach( ncp_uint32_t id,
                   ncp_hdl_t *ncpHdl);

/*!
 * @fn ncp_st_t ncp_config_detach(ncp_hdl_t ncpHdl)
 * @param ncpHdl Handle to the config instance.
 * 
 * @brief Detach from the specified config instance. 
 *
 * This will close the device handle for the calling process 
 * without destroying the configuration state. 
 *
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 */
NCP_API ncp_st_t 
ncp_config_detach(
    ncp_hdl_t ncpHdl);

/*!
 * @fn ncp_st_t ncp_config_warm_restart( ncp_uint32_t id, ncp_hdl_t *ncpHdl)
 * @param id NCP instance 
 * @param ncpHdl handle to the NCP instance
 *
 * @brief Perform a warm restart of the specified config instance. 
 *
 * This function allows a process to attach and restart an existing config 
 * instance after the host has been restarted. If the config instance exists
 * and passes consistency checks, then the ACP device is opened (if necessary)
 * and the object-level handle is returned.
 *
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 *      \li ::NCP_ST_INVALID_INSTANCE
 *      \li ::NCP_ST_NOT_CONFIGURED
 *      \li ::NCP_ST_STATE_VERSION_MISMATCH
 *      \li ::NCP_ST_STATE_INCONSISTENT
 *      \li ::NCP_ST_MTM_HANDLE_INVALID
 *      \li ::NCP_ST_MTM_SEM_INIT_ERROR
 *
 */
NCP_API ncp_st_t
ncp_config_warm_restart(ncp_uint32_t id, ncp_hdl_t *ncpHdl);

/*!
 * @fn ncp_st_t ncp_config_status(ncp_uint32_t id, ncp_hdl_t *ncpHdl)
 *
 * @param id NCP instance
 * @param ncpHdl Handle to the config instance
 *
 * @brief Return the status of the specified config instance, and the 
 * config handle if it exists.
 *
 * DEPRECATED: Use ncp_config_attach instead
 *
 */
NCP_API ncp_st_t
ncp_config_status(ncp_uint32_t id,
                   ncp_hdl_t *ncpHdl);

/*!
 * @fn ncp_st_t ncp_config_dev_hdl_get(ncp_hdl_t ncpHdl, ncp_dev_hdl_t *outHdl)
 * @param ncpHdl Handle to the config instance.
 * @param outHdl A pointer to driver level handle.
 * 
 * @brief Return the specified chip's device driver-level API handle.
 *
 * @return Error Codes:
 *      \li ::NCP_ST_INVALID_HANDLE
 */
NCP_API ncp_st_t 
ncp_config_dev_hdl_get(
    ncp_hdl_t ncpHdl, 
    ncp_dev_hdl_t *outHdl);

/*!
 * @fn ncp_st_t ncp_config_module_version(ncp_hdl_t ncpHdl, ncp_region_id_t  region, ncp_rev_id_t    *rev);
 * @param ncpHdl Handle to the config instance.
 * @param region Region ID of the module for which the version is to be checked
 * @param rev    Revision register for the specified module
 * 
 * @brief Internal function to get the h/w revision for the specified module.
 *
 */
NCP_API ncp_st_t
ncp_config_module_version(
        ncp_hdl_t        ncpHdl,
        ncp_region_id_t  region,
        ncp_rev_id_t    *rev);

#ifndef SWIG

/*! @fn ncp_st_t ncp_config(ncp_uint32_t deviceNum, ncp_uint32_t domainId, ncp_read_fn_t cfgReadFn, void *cfgReadFnArg, ncp_dynamic_cfg_fn_t dynamicCfgFn, void *dynamicCfgFnArg, ncp_cfg_event_fn_t eventFn, void * eventFnArg, ncp_uint32_t flags, ncp_hdl_t *ncpHdl);
    @brief Load a configuration image from a file
    @param deviceNum Device instance to be configured
    @param domainId AMP Domain ID
    @param cfgReadFn I/O function to read in the configuration file image
    @param cfgReadFnArg Optional state arg to be passed to cfgReadFn
    @param dynamicCfgFn Function that gives the user an opportunity to
                        dynamically modify and/or add configuration attribs.
    @param dynamicCfgFnArg Optional state arg to be passed to dynamicCfgFn
    @param eventFn Callback function for configuration events
    @param eventFnArg Optional state arg to be passed to eventReadFn
    @param ncpHdl  Output handle of the configuration image when successful

    For details on using ncp_config to configure the ACP device see
    the RTE Software User Guide.

    @returns Success/failure status
*/
NCP_API ncp_st_t
ncp_config(
    ncp_uint32_t          deviceNum,
    ncp_uint32_t          domainId,
    ncp_read_fn_t         cfgReadFn,
    void *                cfgReadFnArg,
    ncp_dynamic_cfg_fn_t  dynamicCfgFn,
    void *                dynamicCfgFnArg,
    ncp_cfg_event_fn_t    eventFn,
    void *                eventFnArg,
    ncp_uint32_t          flags,
    ncp_hdl_t *           ncpHdl);

#else

%inline
%{
static ncp_st_t
_tcl_ncp_config_load(
    char                 *cfgFile,
    ncp_hdl_t            *ncpHdl)
{
    ncp_st_t              ncpStatus = NCP_ST_SUCCESS;
    void *                eventFnArg = NULL;
    ncp_dynamic_cfg_fn_t  cfgModCallBack = NULL;
    void *                cbArg = NULL;
    ncp_uint32_t          flags = 0;

    FILE                 *cfgFp = 0;

    /*
     * Open configuration file
     */
    cfgFp = fopen(cfgFile, "r");
    if (cfgFp == NULL)
    {
        printf("ERROR:  Could not open config file:  %s\n", cfgFile);
        return NCP_ST_ERROR;
    }

    /*
     * Configure the chipset instance
     */
    NCP_CALL(ncp_config(0,
                        0,
                        ncp_configUtilReadFnDefault,
                        (void *)cfgFp,
                        cfgModCallBack,
                        cbArg,
                        ncp_configUtilEventFnDefault,
                        (void *)eventFnArg,
                        flags,
                        ncpHdl));

ncp_return:
    if (cfgFp)
    {
        fclose(cfgFp);
    }

    return ncpStatus;
}
%}
%rename(ncp_config_load) _tcl_ncp_config_load;
ncp_st_t
_tcl_ncp_config_load(char *cfgFile, ncp_hdl_t *ncpHdl);

#endif /* #ifndef SWIG */


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

#endif /* __NCP_CONFIG_H__ */
