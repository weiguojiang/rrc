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
 **    (c) 2008-2014, Intel Corporation.  All rights reserved.    *
 **                                                                        *
 **
 ** **************************************************************************/

/*! @file      ncp_sed.h
 *  @brief     Stream Editor
 * 
 *  @addtogroup _sed_ Stream Editor
 *
 *  @{
 */

#ifndef _NCP_SED_H_
#define _NCP_SED_H_

/*!
 * @brief ncp_sed_indirect_parm_t : Data structure used to pass the SED indirect
 * parameters.
 *
*/
typedef struct ncp_sed_indirect_parm_s ncp_sed_indirect_parm_t;

/*!
 * @brief Data structure used to pass the SED indirect parameters
 */
struct ncp_sed_indirect_parm_s {
    /*!
     * @brief The indirect parameter flags.  An OR'd combination of
     * NCP_SED_INDIR_FLAGS_SCRIPT_ID_VALID, NCP_SED_INDIR_FLAGS_FRAG_HDR_LEN_VALID,
     * NCP_SED_INDIR_FLAGS_FRAG_SIZE_VALID, NCP_SED_INDIR_FLAGS_MIN_FRAG_LEN_VALID,
     * NCP_SED_INDIR_FLAGS_MIN_FR_LEN_IS_FR_SIZE, and 
     * NCP_SED_INDIR_FLAGS_PREPEND_DATA_LEN_VALID, as well as the Start Delta
     * Valid and End Delta Valid flags.  The Start and End Delta Valid flags are
     * determined dynamically, based on the presence of the Start Delta and End
     * Delta fields, unless overridden using the enableFlagByte field in the ASE.
     */
    unsigned flags                     :8;
    /*!
     * @brief Number of bytes that should be added or deleted from the start of the PDU
     */
    int      startDelta                :8;
    /*!
     * @brief Number of bytes that should be deleted from the end of the PDU
     */
    unsigned endDelta                  :8;
    unsigned reserved                  :1;
    /*!
     * @brief 7-bit script ID
     */
    unsigned scriptId                  :7;
    /*!
     * @brief Number of packet bytes that should be repeated for each fragment
     */
    unsigned fragHdrLen                :8;
    /*!
     * @brief Size if bytes of each fragment
     */
    unsigned fragSize                  :16;
    /*!
     * @brief The maximum length of a packet that will not be fragmented
     */
    unsigned minFragLen                :16;
    /*!
     * @brief The number of bytes from the parameter data block that should be
     * prepended to the packet rather than sent to the SED script
     */
    unsigned prePendDataLen            :8;
};

#define NCP_SED_INDIR_FLAGS_SCRIPT_ID_VALID           0x20
#define NCP_SED_INDIR_FLAGS_FRAG_HDR_LEN_VALID        0x10
#define NCP_SED_INDIR_FLAGS_FRAG_SIZE_VALID           0x8
#ifdef USE_FRSIZE_OVERRIDE
/* Defect 37168: useFrSizeAsMinFrLen not currently supported */
#define NCP_SED_INDIR_FLAGS_MIN_FRAG_LEN_VALID        0x4
#define NCP_SED_INDIR_FLAGS_MIN_FR_LEN_IS_FR_SIZE     0x2
#else
#define NCP_SED_INDIR_FLAGS_UNUSED                    0x4
#define NCP_SED_INDIR_FLAGS_MIN_FRAG_LEN_VALID        0x2
#endif
#define NCP_SED_INDIR_FLAGS_PREPEND_DATA_LEN_VALID    0x1

/*! @fn ncp_st_t ncp_sed_param_get(ncp_hdl_t ncpHdl, ncp_uint32_t tableIndex,
        ncp_uint8_t entryOffset, ncp_byte_string_t outBuffer)
    @brief Read a SED direct parameter entry from an indexed SEDDirectParams
           Namespace
    @param ncpHdl Incoming handle of the current NCP device, specified by the user.
    @param tableIndex The 24-bit Namespace index for the requested SEDDirectParams
           entry, specified by the user.  This index must correspond to a valid
           SEDDirectParams entry established during configuration.
    @param entryOffset Starting byte offset into entry, specified by the user.
           The entryOffset must be
           chosen such that the request does not exceed the boundary of the
           Namespace table entry.
    @param outBuffer Client buffer into which the entry is written.  The len
           field must be chosen such that the request does not exceed the
           boundary of the Namespace table entry.  The user provides the buffer
           pointer and length, and the direct parameter entry is returned in the
           buffer.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_NS_ENTRY_ID_INVALID tableIndex points to an invalid Namespace entry
    @retval NCP_ST_DEV_INVALID_BUFFER An invalid pointer was passed in the outBuffer field
    @retval NCP_ST_SED_INVALID_HANDLE The SED module was not properly configured
    @retval NCP_ST_SED_INVALID_PARAM_REQUEST_SIZE Data was requested outside of the table entry data range
    @retval NCP_ST_* Lower level NCP device access error codes
*/
ncp_st_t
ncp_sed_param_get(
                  ncp_hdl_t ncpHdl,
                  ncp_uint32_t tableIndex,
                  ncp_uint8_t entryOffset,
                  ncp_byte_string_t outBuffer);

/*! @fn ncp_st_t ncp_sed_param_set(ncp_hdl_t ncpHdl, ncp_uint32_t tableIndex,
        ncp_uint8_t entryOffset, ncp_byte_string_t inBuffer)
    @brief Write a SED direct parameter entry to an indexed SEDDirectParams Namespace
    @param ncpHdl Incoming handle of the current NCP device
    @param tableIndex The 24-bit Namespace index for the requested SEDDirectParams entry.
           This index must correspond to a valid SEDDirectParams entry established during
           configuration.
    @param entryOffset Starting byte offset into the entry.  The entryOffset must be chosen
           such that the request does not exceed the boundary of the Namespace table entry.
    @param inBuffer Client buffer from which the entry is read.  The len field must be
           chosen such that the request does not exceed the boundary of the Namespace table
           entry.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_NS_ENTRY_ID_INVALID tableIndex points to an invalid Namespace entry
    @retval NCP_ST_DEV_INVALID_BUFFER An invalid pointer was passed in the inBuffer field
    @retval NCP_ST_SED_INVALID_HANDLE The SED module was not properly configured
    @retval NCP_ST_SED_INVALID_PARAM_REQUEST_SIZE Data was specified outside of the table entry data range
    @retval NCP_ST_* Lower level NCP device access error codes
*/
ncp_st_t
ncp_sed_param_set(
                  ncp_hdl_t ncpHdl,
                  ncp_uint32_t tableIndex,
                  ncp_uint8_t entryOffset,
                  ncp_byte_string_t inBuffer);

/*! @fn ncp_st_t ncp_sed_indirect_param_get(ncp_hdl_t ncpHdl, ncp_uint32_t tableIndex,
        ncp_sed_indirect_parm_t *parms, ncp_byte_string_t prependData, ncp_byte_string_t scriptParms)
    @brief Read a SED indirect parameter entry from an indexed SEDIndirectParams Namespace
    @param ncpHdl Incoming handle of the current NCP device, specified by the
           user.
    @param tableIndex The 24-bit Namespace index for the requested
           SEDIndirectParams entry, specified by the user.  This index must
           correspond to a valid SEDIndirectParams entry established during
           configuration.
    @param parms SED Indirect Mode parameters.  The parameters are returned by
           ncp_sed_indirect_param_get in the fields of the parms structure.
    @param prependData Data array to be prepended to PDU.  The user provides
           the buffer pointer and length, and the prepend data is
           returned in the buffer.  Note the user-provided length must be
           greater than or equal to the actual length of prepend data to be
           returned.
    @param scriptParms Script parameters for the identified SED indirect
           parameter entry.  The user provides the buffer pointer and length,
           and the script parameters are returned in the buffer.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_NS_ENTRY_ID_INVALID tableIndex points to an invalid Namespace entry
    @retval NCP_ST_DEV_INVALID_BUFFER An invalid pointer was passed in the parms, prependData,
            or scriptParms field
    @retval NCP_ST_SED_INVALID_HANDLE The SED module was not properly configured
    @retval NCP_ST_SED_INVALID_PARAM_INDEX The requested index does not correspond to a
            SEDIndirectParams Namespace entry
    @retval NCP_ST_SED_INVALID_PARAM_REQUEST_SIZE Data was requested outside of the
            table entry data range
    @retval NCP_ST_* Lower level NCP device access error codes
*/
ncp_st_t
ncp_sed_indirect_param_get(
                           ncp_hdl_t ncpHdl,
                           ncp_uint32_t tableIndex,
                           ncp_sed_indirect_parm_t *parms,
                           ncp_byte_string_t prependData,
                           ncp_byte_string_t scriptParms);

/*! @fn ncp_st_t ncp_sed_indirect_param_set(ncp_hdl_t ncpHdl, ncp_uint32_t tableIndex,
                 ncp_sed_indirect_parm_t parms, ncp_byte_string_t prependData, ncp_byte_string_t scriptParms)
    @brief Write a SED indirect parameter entry to an indexed SEDIndirectParams Namespace
    @param ncpHdl Incoming handle of the current NCP device
    @param tableIndex The 24-bit Namespace index for the requested SEDIndirectParams entry.
           This index must correspond to a valid SEDIndirectParams entry established during
           configuration.
    @param parms SED Indirect Mode parameters
    @param prependData Data array to be prepended to PDU
    @param scriptParms Script parameters for the identified SED indirect parameter entry
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_NS_ENTRY_ID_INVALID tableIndex points to an invalid Namespace entry
    @retval NCP_ST_DEV_INVALID_BUFFER An invalid pointer was passed in the prependData
            or scriptParms field
    @retval NCP_ST_SED_INVALID_HANDLE The SED module was not properly configured
    @retval NCP_ST_SED_INVALID_PARAM_INDEX The requested index does not correspond to a
            SEDIndirectParams Namespace entry
    @retval NCP_ST_SED_INVALID_PARAM_REQUEST_SIZE Data was specified outside of the
            table entry data range
    @retval NCP_ST_SED_INVALID_PARAM One of the following restrictions is violated and the corresponding flags denote that the fields are valid: (fragHdrLen < fragSize), (fragSize >= startDelta + prePendDataLen), (fragSize > 0)
    @retval NCP_ST_* Lower level NCP device access error codes
*/
ncp_st_t
ncp_sed_indirect_param_set(
                           ncp_hdl_t ncpHdl,
                           ncp_uint32_t tableIndex,
                           ncp_sed_indirect_parm_t parms,
                           ncp_byte_string_t prependData,
                           ncp_byte_string_t scriptParms);


/*
 *  @}
 */

#endif /* _NCP_SED_H_ */
