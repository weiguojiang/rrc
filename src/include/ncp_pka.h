/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*! @file        ncp_pka.h
    @brief       Crypto/PKA (pka)

    @defgroup    _pka_ Public Key Accelerator
    @ingroup     _spp_

    @{
*/

#ifndef NCP_PKA_H
#define NCP_PKA_H

#include <stdarg.h>
#include "ncp_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************/
/* API Typedefs, Constants, etc.                                              */
/******************************************************************************/

/*! @struct ncp_pka_vector_t
    @brief  Structure that defines data vectors that represent all PKA
            input or output arguments.
*/
typedef struct
{
    int           wordLen;      /* Starts with the length of the allocated
                                 * 'data' field in words.
                                 *
                                 * Input Arguments: This field should be set
                                 * to the exact size of the value that is to
                                 * be used for a PKA transaction when it is
                                 * passed for (one of) the argument values
                                 * in 'ncp_pka_trans_in_t'.  The actual size
                                 * of the allocated 'data' may be larger.
                                 *
                                 * Output Results: This field may be reset to
                                 * smaller values by ncp_pka_trans_poll or
                                 * ncp_trans_start_blocking when this vector
                                 * is passed for (one of) the return values
                                 * in 'ncp_pka_trans_out_t'. */
    NCP_DECLARE_POINTER(ncp_uint32_t, data); /* Pointer to data vector words */
    int           user;         /* Reserved for user application data */
} NCP_COMPAT_PACKED ncp_pka_vector_t;

/*!
 * @enum  ncp_pka_operation_t
 * @brief This enum defines the set of operations that may be performed
 *        with the PKA logic.
 */
typedef enum
{
    NCP_PKA_OP_NONE,
    NCP_PKA_OP_MULTIPLY,
    NCP_PKA_OP_ADD,
    NCP_PKA_OP_SUBTRACT,
    NCP_PKA_OP_ADDSUB,
    NCP_PKA_OP_RIGHTSHIFT,
    NCP_PKA_OP_LEFTSHIFT,
    NCP_PKA_OP_DIVIDE,
    NCP_PKA_OP_MODULO,
    NCP_PKA_OP_COMPARE,
    NCP_PKA_OP_COPY,
    NCP_PKA_OP_EXPMOD_ACT2,
    NCP_PKA_OP_EXPMOD_ACT4,
    NCP_PKA_OP_EXPMOD_VARIABLE,
    NCP_PKA_OP_EXPMOD_CRT,
    NCP_PKA_OP_ECC_ADD,
    NCP_PKA_OP_ECC_MUL,
    NCP_PKA_OP_MODINV
} ncp_pka_operation_t;

/*!
 * @struct  ncp_pka_multiply_t
 * @brief   This struct defines the input arguments to a PKA multiply operation.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t, multiplicand);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, multiplier);
} NCP_COMPAT_PACKED ncp_pka_multiply_t;

/*!
 * @struct  ncp_pka_add_t
 * @brief   This struct defines the input arguments to a PKA add operation.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t, addend1);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, addend2);
} NCP_COMPAT_PACKED ncp_pka_add_t;

/*!
 * @struct  ncp_pka_subtract_t
 * @brief   This struct defines the input arguments to a PKA subtract operation.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t, minuend);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, subtrahend);
} NCP_COMPAT_PACKED ncp_pka_subtract_t;

/*!
 * @struct  ncp_pka_addsub_t
 * @brief   This struct defines the input arguments to a PKA addsub operation.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t, addend1);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, addend2);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, subtrahend);
} NCP_COMPAT_PACKED ncp_pka_addsub_t;

/*!
 * @struct  ncp_pka_rightshift_t
 * @brief   This struct defines the input arguments to a PKA rightshift operation.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t, input);
    ncp_uint32_t      shift;
} NCP_COMPAT_PACKED ncp_pka_rightshift_t;

/*!
 * @struct  ncp_pka_leftshift_t
 * @brief   This struct defines the input arguments to a PKA leftshift operation.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t, input);
    ncp_uint32_t      shift;
} NCP_COMPAT_PACKED ncp_pka_leftshift_t;

/*!
 * @struct  ncp_pka_divide_t
 * @brief   This struct defines the input arguments to a PKA divide operation.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t, dividend);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, divisor);
} NCP_COMPAT_PACKED ncp_pka_divide_t;

/*!
 * @struct  ncp_pka_modulo_t
 * @brief   This struct defines the input arguments to a PKA modulo operation.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t, dividend);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, divisor);
} NCP_COMPAT_PACKED ncp_pka_modulo_t;

/*!
 * @struct  ncp_pka_compare_t
 * @brief   This struct defines the input arguments to a PKA compare operation.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t, input1);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, input2);
} NCP_COMPAT_PACKED ncp_pka_compare_t;

/*!
 * @struct  ncp_pka_copy_t
 * @brief   This struct defines the input arguments to a PKA vector copy operation.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t, input);
} NCP_COMPAT_PACKED ncp_pka_copy_t;

/*!
 * @struct  ncp_pka_expmod_t
 * @brief   This struct defines the input arguments to a PKA EXPMOD operation
 *          for EXPMOD_ACT2, and EXPMOD_ACT4 operations.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t, exponent);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, modulus);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, base);
} NCP_COMPAT_PACKED ncp_pka_expmod_t;

/*!
 * @struct  ncp_pka_expmod_var_t
 * @brief   This struct defines the input arguments to a PKA EXPMOD operation
 *          for EXPMOD_VARIABLE operations.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t, exponent);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, modulus);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, base);
    ncp_uint32_t      numOddPowers;
} NCP_COMPAT_PACKED ncp_pka_expmod_var_t;

/*!
 * @struct  ncp_pka_expmod_crt_t
 * @brief   This struct defines the input arguments to a PKA EXPMOD CRT operation.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t, input);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, modP);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, modQ);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, expP);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, expQ);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, Qinverse);
    ncp_uint32_t      numOddPowers;
} NCP_COMPAT_PACKED ncp_pka_expmod_crt_t;

/*!
 * @struct  ncp_pka_modinv_t
 * @brief   This struct defines the input arguments to a PKA MODINV operation.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t, numToInvert);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, modulus);
} NCP_COMPAT_PACKED ncp_pka_modinv_t;

/*!
 * @struct  ncp_pka_ecc_add_t
 * @brief   This struct defines the input arguments to a PKA ECC Add operation.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t, pntAX);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, pntAY);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, curveParamP);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, curveParamA);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, pntCX);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, pntCY);
} NCP_COMPAT_PACKED ncp_pka_ecc_add_t;

/*!
 * @struct  ncp_pka_ecc_mul_t
 * @brief   This struct defines the input arguments to a PKA ECC Multiply operation.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t, scalarK);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, curveParamP);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, curveParamA);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, curveParamB);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, pntCX);
    NCP_DECLARE_POINTER(ncp_pka_vector_t, pntCY);
} NCP_COMPAT_PACKED ncp_pka_ecc_mul_t;

/*!
 * @struct  ncp_pka_trans_in_t
 * @brief   This struct defines the input presentation of a single PKA transaction
 *          as operation and a union with which the associated arguments are to
 *          be provided.
 *
 *          Note that the 'ncp_pka_vector_t *' sub-elements are allocated
 *          and filled in by the callers to the PKA API with the values to be
 *          used by the EIP28.  It is the responsibility of the caller to free
 *          these entries after the successful start of a transaction.
 */
typedef struct
{
    ncp_pka_operation_t opType;
    union
    {
        ncp_pka_multiply_t   multiply;
        ncp_pka_add_t        add;
        ncp_pka_subtract_t   subtract;
        ncp_pka_addsub_t     addsub;
        ncp_pka_rightshift_t rightshift;
        ncp_pka_leftshift_t  leftshift;
        ncp_pka_divide_t     divide;
        ncp_pka_modulo_t     modulo;
        ncp_pka_compare_t    compare;
        ncp_pka_copy_t       copy;
        ncp_pka_expmod_t     expmod;
        ncp_pka_expmod_var_t expmod_var;
        ncp_pka_expmod_crt_t expmod_crt;
        ncp_pka_modinv_t     modinv;
        ncp_pka_ecc_add_t    ecc_add;
        ncp_pka_ecc_mul_t    ecc_mul;
    } u;
} NCP_COMPAT_PACKED ncp_pka_trans_in_t;

/*!
 * @enum  ncp_pka_comp_enum_t
 * @brief This enum defines the set of conditions that may be identified as
 *        a result of a PKA compare operation.
 */
typedef enum
{
    NCP_PKA_COMPARE_AEQB=1,
    NCP_PKA_COMPARE_ALTB=2,
    NCP_PKA_COMPARE_AGTB=4
} ncp_pka_comp_enum_t;

/*!
 * @enum  ncp_pka_opstat_enum_t
 * @brief This enum defines the set of success/fail conditions associated
 *        with a few of the PKA operations that are not guaranteed to complete.
 */
typedef enum
{
    NCP_PKA_OPSTAT_SUCCESS=0,
    NCP_PKA_OPSTAT_NO_INVERSE_EXISTS=7,
    NCP_PKA_OPSTAT_ERROR=31
} ncp_pka_opstat_enum_t;

/*!
 * @struct  ncp_pka_out_multiply_t
 * @brief   This struct defines the output result value for a PKA Multiply operation.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t,  product);
} NCP_COMPAT_PACKED ncp_pka_out_multiply_t;

/*!
 * @struct  ncp_pka_out_add_t
 * @brief   This struct defines the output result value for a PKA add operation.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t,  sum);
} NCP_COMPAT_PACKED ncp_pka_out_add_t;

/*!
 * @struct  ncp_pka_out_subtract_t
 * @brief   This struct defines the output result value for a PKA subtract operation.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t,  difference);
} NCP_COMPAT_PACKED ncp_pka_out_subtract_t;

/*!
 * @struct  ncp_pka_out_addsub_t
 * @brief   This struct defines the output result value for a PKA AddSub operation.
 */
typedef struct
{
NCP_DECLARE_POINTER(    ncp_pka_vector_t,  result);
} NCP_COMPAT_PACKED ncp_pka_out_addsub_t;

/*!
 * @struct  ncp_pka_out_rightshift_t
 * @brief   This struct defines the output result value for a PKA rightshift operation.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t,  result);
} NCP_COMPAT_PACKED ncp_pka_out_rightshift_t;

/*!
 * @struct  ncp_pka_out_leftshift_t
 * @brief   This struct defines the output result value for a PKA leftshift operation.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t,  result);
} NCP_COMPAT_PACKED ncp_pka_out_leftshift_t;

/*!
 * @struct  ncp_pka_out_divide_t
 * @brief   This struct defines the output result values for a PKA divide operation.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t,  remainder);
    NCP_DECLARE_POINTER(ncp_pka_vector_t,  quotient);
} NCP_COMPAT_PACKED ncp_pka_out_divide_t;

/*!
 * @struct  ncp_pka_out_modulo_t
 * @brief   This struct defines the output result value for a PKA modulo operation.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t,  remainder);
} NCP_COMPAT_PACKED ncp_pka_out_modulo_t;

/*!
 * @struct  ncp_pka_out_compare_t
 * @brief   This struct defines the output result value for a PKA compare operation.
 */
typedef struct
{
    ncp_pka_comp_enum_t result;
} NCP_COMPAT_PACKED ncp_pka_out_compare_t;

/*!
 * @struct  ncp_pka_out_copy_t
 * @brief   This struct defines the output result value for a PKA copy operation.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t,  result);
} NCP_COMPAT_PACKED ncp_pka_out_copy_t;

/*!
 * @struct  ncp_pka_out_expmod_t
 * @brief   This struct defines the output result value for a PKA EXPMOD operation
 *          for EXPMOD_ACT2, EXPMOD_ACT4, EXPMOD_VARIABLE, and EXPMOD_CRT operations.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t,  result);
} NCP_COMPAT_PACKED ncp_pka_out_expmod_t;

/*!
 * @struct  ncp_pka_out_modinv_t
 * @brief   This struct defines the output result values for a PKA modulo inverse operation.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t,    result);
    ncp_pka_opstat_enum_t status;
} NCP_COMPAT_PACKED ncp_pka_out_modinv_t;

/*!
 * @struct  ncp_pka_out_ecc_t
 * @brief   This struct defines the output result values for a PKA ECC operation
  *         for ECC_ADD and ECC_MUL operations.
 */
typedef struct
{
    NCP_DECLARE_POINTER(ncp_pka_vector_t,    pntDX);
    NCP_DECLARE_POINTER(ncp_pka_vector_t,    pntDY);
    ncp_pka_opstat_enum_t status;
} NCP_COMPAT_PACKED ncp_pka_out_ecc_t;

/*!
 * @struct  ncp_pka_trans_out_t
 * @brief   This struct defines the output presentation of the results of a
 *          single PKA transaction as a union from which to select the result
 *          matching the associated input transaction.
 *
 *          Note that the 'ncp_pka_vector_t *' sub-elements may be allocated
 *          and filled in by the PKA API with the results from the EIP28, if
 *          the calling application does not provide a result field.
 *
 *          It is the responsibility of the caller to free these entries
 *          when they are no longer needed.  The result values are provided as
 *          pointers with the expectation that the caller will perform further
 *          operations using these values, and the intent that the values may
 *          be reused by a simple assign/copy step.  The caller may use the
 *          convenience function ncp_pka_free_outArg() to simplify this task.
 *
 *          The caller to the PKA API is expected to create a local instance
 *          of the 'ncp_pka_trans_out_t' structure and pass a pointer to it
 *          to the PKA API to be filled in with the results.  This local
 *          instance may be created by,
 *
 *          + p = (ncp_pka_trans_out_t*)ncp_malloc(sizeof(ncp_pka_trans_out_t));
 *            ncp_memset(p, 0, sizeof(ncp_pka_trans_out_t));
 *
 *          + ncp_pka_make_outArg(<opType>, &p, ...);
 */
typedef union
{
    ncp_pka_out_multiply_t   multiply;
    ncp_pka_out_add_t        add;
    ncp_pka_out_subtract_t   subtract;
    ncp_pka_out_addsub_t     addsub;
    ncp_pka_out_rightshift_t rightshift;
    ncp_pka_out_leftshift_t  leftshift;
    ncp_pka_out_divide_t     divide;
    ncp_pka_out_modulo_t     modulo;
    ncp_pka_out_compare_t    compare;
    ncp_pka_out_copy_t       copy;
    ncp_pka_out_expmod_t     expmod;
    ncp_pka_out_modinv_t     modinv;
    ncp_pka_out_ecc_t        ecc_add;
    ncp_pka_out_ecc_t        ecc_mul;
        /* For ECC_ADD & ECC_MUL operations */
} NCP_COMPAT_PACKED ncp_pka_trans_out_t;

/*!
 * @struct  ncp_pka_info_t
 * @brief   This struct defines the output result values for a PKA info query
 *         operation.
 */
typedef struct
{
    ncp_uint32_t                pkaRamWordsAvail;
} ncp_pka_info_t;


/******************************************************************************/
/* APIs                                                                       */
/******************************************************************************/

#if     !defined(NCP_KERNEL)

/*! @fn ncp_st_t ncp_pka_trans_blocking(ncp_hdl_t ncpHdl, ncp_pka_trans_in_t *inArgs, ncp_pka_trans_out_t *outArgs)
    @brief Entry point to initiate a new PKA transaction, and return the results
    @param[in] ncpHdl Incoming device handle
    @param[in] inArgs Incoming arguments to define a transaction
    @param[out] outArgs Output results
    @retval NCP_ST_SUCCESS operation successfully initiated and completed
    @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
    @retval NCP_ST_PKA_INVALID_VALUE invalid argument(s)
    @retval NCP_ST_PKA_NOT_INSTALLED PKA module not present in hardware
    @retval NCP_ST_PKA_INVALID_ARGUMENT_LENGTH Combinations of argument lengths invalid for operation request, or too large for available memory
    @retval NCP_ST_PKA_OPERATION_NOT_RUNNING PKA operation expected to be running, but no operation is in progress
    @retval other device driver errors may be observed
*/
NCP_API
ncp_st_t
ncp_pka_trans_blocking(
    ncp_hdl_t            ncpHdl,
    ncp_pka_trans_in_t  *inArgs,
    ncp_pka_trans_out_t *outArgs);

/*! @fn ncp_st_t ncp_pka_trans_start(ncp_hdl_t ncpHdl, ncp_pka_trans_in_t *inArgs)
    @brief Entry point to initiate a new PKA transaction
    @param[in] ncpHdl Incoming device handle
    @param[in] inArgs Incoming arguments to define a transaction
    @retval NCP_ST_SUCCESS operation successfully initiated
    @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
    @retval NCP_ST_PKA_INVALID_VALUE invalid argument(s)
    @retval NCP_ST_PKA_NOT_INSTALLED PKA module not present in hardware
    @retval NCP_ST_PKA_INVALID_ARGUMENT_LENGTH Combinations of argument lengths invalid for operation request, or too large for available memory
    @retval NCP_ST_PKA_OPERATION_NOT_RUNNING PKA operation expected to be running, but no operation is in progress
    @retval other device driver errors may be observed
*/
NCP_API
ncp_st_t
ncp_pka_trans_start(
    ncp_hdl_t            ncpHdl,
    ncp_pka_trans_in_t  *inArgs);

/*! @fn ncp_st_t ncp_pka_trans_poll(ncp_hdl_t ncpHdl, ncp_pka_trans_out_t *outArgs)
    @brief Entry point to check on progress of an ongoing PKA transaction, and return results
    @param[in] ncpHdl Incoming device handle
    @param[out] outArgs Outgoing results of a successful PKA transaction
    @retval NCP_ST_SUCCESS operation successfully completed
    @retval NCP_ST_PKA_OPERATION_IN_PROGRESS previously created operation is still running; check back later; not fatal
    @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
    @retval NCP_ST_PKA_INVALID_VALUE invalid argument(s) e.g. outArgs
    @retval NCP_ST_PKA_NOT_INSTALLED PKA module not present in hardware
    @retval NCP_ST_PKA_INVALID_ARGUMENT_LENGTH Combinations of argument lengths invalid for operation request, or too large for available memory
    @retval NCP_ST_PKA_OPERATION_NOT_RUNNING PKA operation expected to be running, but no operation is in progress
    @retval other device driver errors may be observed
*/
NCP_API
ncp_st_t
ncp_pka_trans_poll(
    ncp_hdl_t            ncpHdl,
    ncp_pka_trans_out_t *outArgs);

/*! @fn ncp_st_t ncp_pka_trans_kill(ncp_hdl_t ncpHdl)
    @brief Entry point to terminate an ongoing transaction
    @param[in] ncpHdl Incoming device handle
    @retval NCP_ST_SUCCESS operation successfully completed
    @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
    @retval NCP_ST_PKA_INVALID_VALUE invalid argument(s)
    @retval NCP_ST_PKA_NOT_INSTALLED PKA module not present in hardware
    @retval other device driver errors may be observed
*/
NCP_API
ncp_st_t
ncp_pka_trans_kill(
    ncp_hdl_t            ncpHdl);

/*! @fn ncp_st_t ncp_pka_info(ncp_hdl_t ncpHdl, ncp_pka_info_t *outInfo)
    @brief Return information about the PKA module
    @param[in] ncpHdl Incoming device handle
    @param[out] outInfo Outgoing - caller location to deposit information about PKA module
    @retval NCP_ST_SUCCESS operation successfully completed
    @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
    @retval NCP_ST_PKA_INVALID_VALUE invalid argument(s) e.g. outInfo
    @retval NCP_ST_PKA_NOT_INSTALLED PKA module not present in hardware
    @retval NCP_ST_PKA_INVALID_ARGUMENT_LENGTH Combinations of argument lengths invalid for operation request, or too large for available memory
    @retval other device driver errors may be observed
*/
NCP_API
ncp_st_t
ncp_pka_info(
    ncp_hdl_t            ncpHdl,
    ncp_pka_info_t      *outInfo);

/*! @fn ncp_st_t ncp_pka_make_vector(ncp_uint32_t vecWordLen, ncp_pka_vector_t **madeVec)
    @brief Create a vector of the specified size.
    @param[in] vecWordLen Num of words in the desired vector.
                          If zero (0), use maximum possible vec size instead.
    @param[out] madeVec Location to place the created vector
    @retval NCP_ST_SUCCESS operation successfully completed
    @retval NCP_ST_PKA_INVALID_VALUE vecWordLen > 128
    @retval NCP_ST_INVALID_PARAMETER madeVec is NULL
    @retval NCP_ST_NO_MEMORY Unable to allocate memory
    @retval other device driver errors may be observed
    @desc Usage Note: If the allocated size of the vector is necessary, then
          the user should make efforts to record/recall this information
          separately from the 'madeVec' that is created and returned.  This
          is because the 'wordLen' element may be rewritten by the PKA APIs
          (e.g. ncp_pka_trans_start_blocking(), ncp_pka_trans_start_poll())
          with the computed length of the return value after 'madeVec' is
          used to create 'madeOutArg'.
*/
NCP_API
ncp_st_t
ncp_pka_make_vector(
    ncp_uint32_t        vecWordLen,
    ncp_pka_vector_t  **madeVec);

/*! @fn ncp_st_t ncp_pka_copy_vector(ncp_pka_vector_t *oldVec, ncp_pka_vector_t **newVec)
    @brief Create a vector of the specified size.
    @param[in] oldVec Location to place the created vector
    @param[out] newVec Location to place the created vector
    @retval NCP_ST_SUCCESS operation successfully completed
    @retval NCP_ST_PKA_INVALID_VALUE vecWordLen > 128
    @retval NCP_ST_INVALID_PARAMETER madeVec is NULL
    @retval NCP_ST_NO_MEMORY Unable to allocate memory
    @retval other device driver errors may be observed
    @desc Usage Note: If the allocated size of the vector is necessary, then
          the user should make efforts to record/recall this information
          separately from the 'newVec' that is created and returned.  This
          is because the 'wordLen' element may be rewritten by the PKA APIs
          (e.g. ncp_pka_trans_start_blocking(), ncp_pka_trans_start_poll())
          with the computed length of the return value after 'newVec' is
          used to create 'madeOutArg'.
*/
NCP_API
ncp_st_t
ncp_pka_copy_vector(
    ncp_pka_vector_t   *oldVec,
    ncp_pka_vector_t  **newVec);

/*! @fn ncp_st_t ncp_pka_free_vector(ncp_pka_vector_t *madeVec)
    @brief Release memory allocated to a dynamically created vector.
    @param[in] madeVec Pointer to dynamically created vector
    @retval NCP_ST_SUCCESS operation successfully completed
    @retval NCP_ST_INVALID_PARAMETER madeVec is NULL
    @retval other device driver errors may be observed
*/
NCP_API
ncp_st_t
ncp_pka_free_vector(
    ncp_pka_vector_t   *madeVec);

/*! @fn ncp_st_t ncp_pka_make_outArg(ncp_pka_operation_t opType, ncp_pka_trans_out_t **madeOutArg, ...)
    @brief Create an output argument structure for the PKA ops.
           User must pass the appropriate number of values to fill in the
           result for the specified operation type to avoid runtime errors.
    @param[in] opType Type of operation to fill in
    @param[out] madeOutArg Location to place the created structure
    @param[in] ... Variable list of zero or more vectors (ncp_pka_vector_t*),
                   appropriate to the opType, to use for the resulting values.
                   The values provided left to right will be plugged into the
                   appropriate result value structure top to bottom in the
                   'ncp_pka_vector_t*' locations.  Other types of values
                   positions in the result value structures will be skipped.
    @retval NCP_ST_SUCCESS operation successfully completed
    @retval NCP_ST_INVALID_VALUE opType unknown, or NULL resVec value provided
    @retval NCP_ST_INVALID_PARAMETER madeOutArg is NULL
    @retval other device driver errors may be observed
*/
NCP_API
ncp_st_t
ncp_pka_make_outArg(
    ncp_pka_operation_t opType,
    ncp_pka_trans_out_t **madeOutArg,
    ...);

/*! @fn ncp_st_t ncp_pka_free_outArg(ncp_pka_operation_t opType, ncp_pka_trans_out_t *madeOutArg)
    @brief Release memory allocated to a dynamically created output Arg.
    @param[in] opType Type of operation to free
    @param[in] madeOutArg Pointer to dynamically created outArg
    @retval NCP_ST_SUCCESS operation successfully completed
    @retval NCP_ST_INVALID_PARAMETER madeOutArg is NULL
    @retval NCP_ST_INVALID_VALUE madeOutArg->opType unknown
    @retval other device driver errors may be observed
*/
NCP_API
ncp_st_t
ncp_pka_free_outArg(
    ncp_pka_operation_t  opType,
    ncp_pka_trans_out_t *madeOutArg);

/*! @fn ncp_st_t ncp_pka_free_inArg(ncp_pka_trans_in_t *madeInArg)
    @brief Release memory allocated to a dynamically created input Arg.
    @param[in] madeInArg Pointer to dynamically created inArg
    @retval NCP_ST_SUCCESS operation successfully completed
    @retval NCP_ST_INVALID_PARAMETER madeInArg is NULL
    @retval NCP_ST_INVALID_VALUE madeInArg->opType unknown
    @retval other device driver errors may be observed
*/
NCP_API
ncp_st_t
ncp_pka_free_inArg(
    ncp_pka_trans_in_t  *madeInArg);

#endif  /* !defined(NCP_KERNEL) */

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* NCP_PKA_H */
