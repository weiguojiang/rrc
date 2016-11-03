/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


/*! @file       ncp_dev_cat.h
    @brief      Low-level (Device) APIs for access to CAT module and
                storage/retrieval of register information from a 'crashed'
                system.
*/

#ifndef _NCP_CAT_DEV_H_
#define _NCP_CAT_DEV_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "ncp_dev.h"
#include "ncp_cat_common.h"

/*!
    @defgroup   _cat_ Crash Analysis Tools

    @defgroup   _catdev_ CAT Device level
    @brief      Crash Analysis Tools Device level (catdev)
    @detail     Device-level APIs for access to CAT module and
                storage/retrieval of register information from a 'crashed'
                system.
    @{
    @ingroup    _cat_
 */

/**************************************************************************
* Type definitions & related external state                               *
**************************************************************************/

/*! @struct ncp_cat_dcr_check_t
 *  @brief Internal representation of a single DCR region forming part
 *         of the checks for available/valid DCR regions on the current
 *         ACP device.
 */
typedef struct
{
    ncp_region_id_t     regionId;       /* node+target of a DCR region */
    ncp_uint32_t        chkOff;         /* offset to check register    */
    ncp_uint32_t        expValue;       /* expected value              */
    ncp_uint32_t        mask;           /* bits to check in expValue   */
    ncp_uint32_t        always;         /* 0 = never safe to check
                                         * 1 = consider always present
                                         * 2 = check                   */
} ncp_cat_dcr_check_t;

/*! @struct ncp_cat_pqm_state_t
 *  @brief Temporary storage support PQM state modifications
 */
typedef struct
{
    ncp_uint32_t        pqmInProg;      /* Is PQM mod in progress?     */
    ncp_uint32_t        pqm_config;     /* Snapshot of 0x1a.0x11.0x8   */
    ncp_uint32_t        int_enable;     /* Snapshot of 0x1a.0x11.0x14 */
} ncp_cat_pqm_state_t;

/*! @struct ncp_cat_femac_state_t
 *  @brief Temporary storage support FEMAC state modifications
 */
typedef struct
{
    ncp_uint32_t        femacInProg;    /* Is FEMAC mod in progress?     */
    ncp_uint32_t        rxMacSoftReset; /* Snapshot of 0x122.0x0.0x808   */
    ncp_uint32_t        txMacSoftReset; /* Snapshot of 0x122.0x0.0x1808  */
} ncp_cat_femac_state_t;


/**************************************************************************
* Constants                                                               *
**************************************************************************/

/**************************************************************************
* Macros                                                                  *
**************************************************************************/

#undef NCP_CAT_GET_RTEVERSION
/*! @def NCP_CAT_GET_RTEVERSION(inDevHdl, outRteVersion)
    @brief Driver variant of macro to generate a 'standardized'
           RTE Version string for comparison across different
           stored CAT memory records.
*/
#define NCP_CAT_GET_RTEVERSION(devHdl, verStr)                           \
    {                                                                    \
        strncpy(verStr, release_id, NCP_CAT_RTE_VER_NAME_LEN);           \
    }

/*! @def NCP_SWAP16(x)
    @brief Simple byte swap within 16-bit words.
*/
#define NCP_SWAP16(x)        ( (((x) & 0xFF  ) << 8) | (((x) & 0xFF00) >> 8) )

/*! @def NCP_SWAP32(x)
    @brief Simple byte swap within 32-bit words.
*/
#define NCP_SWAP32(x)        ( (((x) & 0x000000FF) << 24) | (((x) & 0x0000FF00) <<  8) | (((x) & 0x00FF0000) >> 8) | (((x) & 0xFF000000) >> 24) )

#ifdef NCP_BIG_ENDIAN
/*! @def NCP_CAT_TOBE32(x)
    @brief Take host 32-bit value and produce big-endian 32-bit value
*/
    #define NCP_CAT_TOBE32(v)   v

/*! @def NCP_CAT_FRMBE32(x)
    @brief Take big-endian 32-bit value and produce host 32-bit value
*/
    #define NCP_CAT_FRMBE32(v)  v
#else
/*! @def NCP_CAT_TOBE32(x)
    @brief Take host 32-bit value and produce big-endian 32-bit value
*/
    #define NCP_CAT_TOBE32(v)   NCP_SWAP32(v)

/*! @def NCP_CAT_FRMBE32(x)
    @brief Take big-endian 32-bit value and produce host 32-bit value
*/
    #define NCP_CAT_FRMBE32(v)  NCP_SWAP32(v)
#endif /* NCP_BIG_ENDIAN */

        /* DCR check related macros */

#define CAT_IS_DCR(ri) \
        ((ri >= NCP_REGION_DCR_ARB) && (ri <= NCP_REGION_MPIC_0))

#define CAT_DCR_CHK_REG(ri) \
        catDcrChk[ri].regionId

#define CAT_DCR_CHK_OFF(ri) \
        catDcrChk[ri].chkOff

#define CAT_DCR_CHK_EXP(ri) \
        catDcrChk[ri].expValue

#define CAT_DCR_CHK_MASK(ri) \
        catDcrChk[ri].mask

#define CAT_DCR_ALWAYS(ri) \
        (catDcrChk[ri].always == 1)

#define CAT_DCR_NEVER(ri) \
        (catDcrChk[ri].always == 0)

#define CAT_DCR_MAYBE(ri) \
        (catDcrChk[ri].always == 2)


/**************************************************************************
* Low-Level APIs                                                          *
**************************************************************************/

/*!
 * @fn ncp_st_t ncp_dev_cat_config(ncp_dev_hdl_t  devHdl,
 *                                 ncp_bool_t     memoryEnable,
 *                                 ncp_uint64_t   memoryBaseAddr,
 *                                 ncp_uint64_t   memorySize,
 *                                 ncp_uint64_t  *oMemoryNeeded);
 * @brief Configures the physical memory to be used by the CAT functions
 * @param[in] dev Device handle
 * @param[in] memoryEnable Specify whether the feature is enabled for the
 *                         current configuration
 * @param[in] memoryBaseAddr Location at which to place/read the crash data
 * @param[in] memorySize Number of bytes that may be used to store crash data
 * @param[out] oMemoryNeeded Min num of bytes needed to store crash data
 * @retval NCP_ST_SUCCESS operation successfully completed
 * @retval NCP_ST_INVALID_HANDLE devHdl is invalid
 * @retval NCP_ST_CAT_MEMORY_ADDR_INVALID 'catMemoryPhysAddr' argument is invalid e.g. NULL
 * @retval NCP_ST_CAT_MEMORY_SIZE_INVALID 'catMemorySize' argument is invalid e.g. zero
 * @retval NCP_ST_CAT_INSUFFICIENT_MEMORY 'catMemorySize' argument is too small to allow storage of the latest register map
 */
NCP_API
ncp_st_t ncp_dev_cat_config(
    ncp_dev_hdl_t      devHdl,
    ncp_bool_t         memoryEnable,
    ncp_uint64_t       memoryBaseAddr,
    ncp_uint64_t       memorySize,
    ncp_uint64_t      *oMemoryNeeded);

/*!
 *  @fn ncp_st_t ncp_dev_cat_destroy(ncp_dev_hdl_t inDevHdl);
 *  @brief This function will release resources acquired for the CAT function
 *         during module initialization.
 *  @param[i] dev Reference to device handle structure
 *  @Returns success/failure status of the operation
 */
NCP_API
ncp_st_t ncp_dev_cat_destroy(
    ncp_dev_hdl_t     *inDevHdl);

/*!
 * @fn ncp_st_t ncp_dev_cat_iofns(ncp_dev_hdl_t      devHdl,
 *                                ncp_cat_write_t    wrFn,
 *                                void              *wrFnArg,
 *                                ncp_cat_read_t     rd,
 *                                void              *rdArg);
 * @brief Tell the API and/or driver to use application-specific functions
 *        to store the CAT recovery data, instead of the builtin memory copy
 *        functions.  Application-specific functions may use the physical
 *        memory configured to \link ncp_dev_cat_config() \endlink or they
 *        may store/retrieve the data elsewhere e.g. FLASH.
 *
 *        Note that the value of 'wrFnArg' may be the same as the value of
 *        the 'rdFnArg'.
 * @param[in] dev Device handle
 * @param[in] wrFn Callback function that the caller may provide to store
 *                 the NCP critical state into a protected area.
 * @param[in] wrFnArg Support region for wrFn callback function that the
 *                    caller may provide for the operation of the wrFn.
 * @param[in] rdFn Callback function that the caller may provide to retrieve
 *                 the NCP critical state from a protected area.  This is the
 *                 inverse of the 'wrFn'.
 * @param[in] rdFnArg Support region for rdFn callback function that the
 *                    caller may provide for the operation of the rdFn.
 * @retval NCP_ST_SUCCESS operation successfully completed
 * @retval NCP_ST_INVALID_HANDLE devHdl is invalid
 * @retval NCP_ST_CAT_NOT_CONFIGURED The CAT module was not configured prior
 *                    to this function call.
 * @retval NCP_ST_CAT_NOT_ENABLED The CAT module was not enabled when the
 *                    configuration was created.
 * @retval NCP_ST_CAT_MISSING_WRITEFN 'wrFn' argument is NULL
 * @retval NCP_ST_CAT_MISSING_READFN ''rdFn' argument is NULL
 */
NCP_API
ncp_st_t ncp_dev_cat_iofns(
    ncp_dev_hdl_t      devHdl,
    ncp_cat_write_t    wrFn,
    void              *wrFnArg,
    ncp_cat_read_t     rdFn,
    void              *rdFnArg);

/*!
 * @fn ncp_st_t ncp_dev_cat_write(ncp_dev_hdl_t      devHdl);
 * @brief Tell the API and/or driver to save critical NCP state for examination
 *        after the NCP device is reset.
 * @param[in] dev Device handle
 * @retval NCP_ST_SUCCESS operation successfully completed
 * @retval NCP_ST_INVALID_HANDLE devHdl is invalid
 * @retval NCP_ST_CAT_NOT_CONFIGURED The CAT module was not configured prior
 *                    to this function call.
 * @retval NCP_ST_CAT_NOT_ENABLED The CAT module was not enabled when the
 *                    configuration was created.
 * @retval other Other device driver error codes may be observed.
 */
NCP_API
ncp_st_t ncp_dev_cat_write(
    ncp_dev_hdl_t      devHdl);

/*!
 * @fn ncp_st_t ncp_dev_cat_write_raw(ncp_dev_hdl_t devHdl,
 *                                    ncp_uint32_t  count,
 *                                    void         *buffer);
 * @brief Tell the API and/or driver to save more NCP state for subsequent
 *        retrieval and examination, where any necessary header and the
 *        data is passed in by these function arguments.
 * @param[in] dev Device handle
 * @param[in] count Data byte count for buffer content
 * @param[in] buffer Data source to be added to the NCP CAT state.
 * @retval NCP_ST_SUCCESS operation successfully completed
 * @retval NCP_ST_INVALID_HANDLE devHdl is invalid
 * @retval NCP_ST_CAT_NOT_CONFIGURED The CAT module was not configured prior
 *                    to this function call.
 * @retval NCP_ST_CAT_NOT_ENABLED The CAT module was not enabled when the
 *                    configuration was created.
 * @retval other Other device driver error codes may be observed.
 */
NCP_API
ncp_st_t ncp_dev_cat_write_raw(
    ncp_dev_hdl_t       devHdl,
    ncp_uint32_t        count,
    void               *buffer);

/*!
 * @fn ncp_st_t ncp_dev_cat_write_finalize(ncp_dev_hdl_t      devHdl);
 * @brief Tell the API and/or driver to complete saving critical NCP state
 *        to the CAT memory for examination after the NCP device is reset.
 *        This final data may include lengths, checksums, etc.
 * @param[in] dev Device handle
 * @retval NCP_ST_SUCCESS operation successfully completed
 * @retval NCP_ST_INVALID_HANDLE devHdl is invalid
 * @retval NCP_ST_CAT_NOT_CONFIGURED The CAT module was not configured prior
 *                    to this function call.
 * @retval NCP_ST_CAT_NOT_ENABLED The CAT module was not enabled when the
 *                    configuration was created.
 * @retval other Other device driver error codes may be observed.
 */
NCP_API
ncp_st_t ncp_dev_cat_write_finalize(
    ncp_dev_hdl_t      devHdl);

/*!
 * @fn ncp_st_t ncp_dev_cat_size(ncp_dev_hdl_t  devHdl,
 *                               ncp_uint64_t  *catMemorySize);
 * @brief Retrieves the size of the data configured for storage of critical
 *        NCP state by the CAT utilities.
 * @param[in] dev Device handle
 * @param[in] catMemorySize Size configured for storing the CAT data
 * @retval NCP_ST_SUCCESS operation successfully completed
 * @retval NCP_ST_INVALID_HANDLE devHdl is invalid
 * @retval NCP_ST_CAT_NOT_CONFIGURED The CAT module was not configured prior
 *                    to this function call.
 * @retval NCP_ST_CAT_NOT_ENABLED The CAT module was not enabled when the
 *                    configuration was created.
 * @retval NCP_ST_CAT_MEMORY_SIZE_INVALID 'catMemorySize' argument is invalid e.g. NULL pointer
 * @retval other Other device driver error codes may be observed.
 */
NCP_API
ncp_st_t ncp_dev_cat_size(
    ncp_dev_hdl_t      devHdl,
    ncp_uint64_t      *catMemorySize);

/*!
 * @fn ncp_st_t ncp_dev_cat_read(ncp_dev_hdl_t      devHdl,
 *                               ncp_uint8_t       *buffer,
 *                               ncp_uint32_t       bufferSize,
 *                               ncp_uint64_t      *offset,
 *                               ncp_uint32_t      *readSize);
 * @brief Read back a block of data from the previously captured critical state.
 *        This function can be used in an iterative fashion, starting at offset=0,
 *        advancing by the 'readSize' after making use of the retrieved block,
 *        and repeating until the return code of NCP_ST_CAT_DATA_EOF is seen.
 *        Normal operation would include allocating a buffer of the size reported
 *        by \link ncp_dev_cat_size() \endlink, and then filling it from front
 *        to back with the data supplied by this function.
 *
 *        Note that the variables in the user code pointed to by 'offset' and
 *        'readSize' must be zero prior to the first call to retrieve the
 *        initial block of CAT recovery data.
 * @param[in] dev Device handle
 * @param[in] buffer Address of buffer provided by caller into which a subset
 *                of the previously cached data is deposited
 * @param[in] bufferSize Size of 'buffer' in bytes
 * @param[in] offset Displacement in bytes into the block of data stored by CAT
 * @param[out] readSize Address to deposit size of data actually read
 * @retval NCP_ST_SUCCESS operation successfully completed
 * @retval NCP_ST_CAT_DATA_EOF Non-fatal notification that no more data is available to retrieve from the CAT recovery data block.
 * @retval NCP_ST_INVALID_HANDLE devHdl is invalid
 * @retval NCP_ST_CAT_NOT_CONFIGURED The CAT module was not configured prior
 *                    to this function call.
 * @retval NCP_ST_CAT_NOT_ENABLED The CAT module was not enabled when the
 *                    configuration was created.
 * @retval NCP_ST_CAT_DATA_BUFFER_INVALID 'buffer' argument is invalid e.g. NULL
 * @retval NCP_ST_CAT_DATA_BUFSIZE_INVALID 'bufferSize' argument is invalid e.g. zero
 * @retval NCP_ST_CAT_INVALID_ITERATOR 'offset' or 'readSize' arguments are invalid e.g. NULL pointers
 * @retval other Other device driver error codes may be observed.
 */
NCP_API
ncp_st_t ncp_dev_cat_read(
    ncp_dev_hdl_t      devHdl,
    ncp_uint8_t       *buffer,
    ncp_uint32_t       bufferSize,
    ncp_uint64_t      *offset,
    ncp_uint32_t      *readSize);


#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* _NCP_DEV_CAT_H_ */
