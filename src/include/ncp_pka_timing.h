/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*! @file        ncp_pka_timing.h
    @brief       Low-level timing function
*/

#ifndef NCP_PKA_TIMING_H
#define NCP_PKA_TIMING_H

#if     defined(NCP_KERNEL) || defined(MODULE)
    #include "ncp_dev.h"
#else
    #include <stdio.h>
    #include "ncp_types.h"
#endif  /* defined(NCP_KERNEL) || defined(MODULE) */

#ifdef  NCP_PROFILE
/******************************************************************************/
/* Typedefs, Constants, etc.                                                  */
/******************************************************************************/

/*
 * General constants/macros
 *   For performance profiling on 476 local cores only!
 */
#define SPRN_TBL 268 /*0x10C*/
#define SPRN_TBU 269 /*0x10D*/

#define __stringify_1(x)    #x
#define __stringify(x)      __stringify_1(x)

#define mfspr(rn)                                                          \
        ({unsigned long rval;                                              \
          __asm__ __volatile__("mfspr %0," __stringify(rn) : "=r" (rval)); \
          rval; })

/*
 * Profile measurement for PKA
 */
typedef enum
{
        /* DATA PATH PROFILE POINTS */
    NCP_PROFILE_PROFILE=0,
    NCP_PROFILE_VALIDATE_HANDLE,  
    NCP_PROFILE_INIT_PROG_MEMORY,
    NCP_PROFILE_IN_PROG_CHK,

    NCP_PROFILE_TRANS_START_OVERALL_API,
    NCP_PROFILE_TRANS_POLL_OVERALL_API,
    NCP_PROFILE_TRANS_BLOCKING_OVERALL_API,
    NCP_PROFILE_TRANS_KILL_OVERALL_API,

    NCP_PROFILE_TRANS_START_OVERALL_DRIVER,
    NCP_PROFILE_TRANS_POLL_OVERALL_DRIVER,
    NCP_PROFILE_TRANS_BLOCKING_OVERALL_DRIVER,
    NCP_PROFILE_TRANS_KILL_OVERALL_DRIVER,

    NCP_PROFILE_UTIL_ALLOCATE_VECTOR,
    NCP_PROFILE_UTIL_FREE_VECTOR,
    NCP_PROFILE_UTIL_COPY_VECTOR_TO_DEVICE,
    NCP_PROFILE_UTIL_COPY_VECTOR_FROM_DEVICE,
    NCP_PROFILE_UTIL_ZERO_VECTOR,
    NCP_PROFILE_UTIL_ALLOCATE_VECTOR_DRIVER,
    NCP_PROFILE_UTIL_FREE_VECTOR_DRIVER,
    NCP_PROFILE_UTIL_COPY_VECTOR_TO_DEVICE_DRIVER,
    NCP_PROFILE_UTIL_COPY_VECTOR_FROM_DEVICE_DRIVER,
    NCP_PROFILE_UTIL_ZERO_VECTOR_DRIVER,

    NCP_PROFILE_MID_COPY_VECTOR_TO_KERNEL,
    NCP_PROFILE_MID_COPY_VECTOR_FROM_KERNEL,

    NCP_PROFILE_SEM_TAKE,
    NCP_PROFILE_SEM_FREE,
    NCP_PROFILE_SEM_TAKE_DRIVER,
    NCP_PROFILE_SEM_FREE_DRIVER,

    NCP_PROFILE_OP_TRANS_START_ARG_PARSE,
    NCP_PROFILE_OP_TRANS_START_RUN,
    NCP_PROFILE_OP_TRANS_RESULT_OVHD,
    NCP_PROFILE_OP_TRANS_BLOCK_WAIT_OVHD,

        /* MUST BE LAST */
    NCP_PROFILE_LAST
} ncp_profile_points_t;


#define NCP_NUM_PROFILE_DATAPOINTS      (10 * 1024)

typedef struct ncp_ncp_profile_entry_s
{
    char               *name;
    ncp_bool_t          enabled;
    ncp_int32_t         index;
    ncp_uint64_t        results[NCP_NUM_PROFILE_DATAPOINTS];
} ncp_profile_entry_t;


typedef struct
{
    ncp_bool_t          profileOn;
    ncp_profile_entry_t profileData[NCP_PROFILE_LAST];
} ncp_prof_t;


/*
 * Lock/semaphore management
 */

#define NCP_INIT_LOCK(_p, _s, _v)  	ncp_sem_init(_p, _s, _v)
#define NCP_DESTROY_LOCK(_p)       	ncp_sem_destroy(_p)

#ifdef PROC_PPC476

#define NCP_CLAIM_LOCK(_p, _f)  { \
    ncp_pka_start_profile(&pka->prof, NCP_PROFILE_SEM_TAKE); \
    ncp_sem_wait(_p); \
    ncp_pka_stop_profile(&pka->prof, NCP_PROFILE_SEM_TAKE); \
    }

#define NCP_FREE_LOCK(_p, _f)  { \
    ncp_pka_start_profile(&pka->prof, NCP_PROFILE_SEM_FREE); \
    ncp_sem_post(_p); \
    ncp_pka_stop_profile(&pka->prof, NCP_PROFILE_SEM_FREE); \
    }

#else

#define NCP_CLAIM_LOCK(_p, _f)		ncp_sem_wait(_p)
#define NCP_FREE_LOCK(_p, _f)		ncp_sem_post(_p)

#endif /* PROC_PPC476 */


/******************************************************************************/
/* APIs                                                                       */
/******************************************************************************/

#ifdef PROC_PPC476

static __inline__
void ncp_pka_get_profile_timestamp(
    ncp_uint64_t *pTicks)
{
    ncp_uint32_t *pUpper = (ncp_uint32_t *)pTicks;
    ncp_uint32_t *pLower = pUpper+1;
    ncp_uint32_t upper1;
    ncp_uint32_t upper2;

    do
    {
        upper1  = mfspr(SPRN_TBU);
        *pLower = mfspr(SPRN_TBL);
        upper2  = mfspr(SPRN_TBU);
    } while (upper1 != upper2);
    *pUpper = upper1;

    return;
}

static __inline__
void ncp_pka_start_profile(
    ncp_prof_t                 *myProfHdl,
    ncp_profile_points_t        pointIndex)
{
    int i;

    if ((NULL == myProfHdl) ||
        (FALSE == myProfHdl->profileOn) ||
        (FALSE == myProfHdl->profileData[pointIndex].enabled))
    {
        return;
    }
    if ((i = myProfHdl->profileData[pointIndex].index) != NCP_NUM_PROFILE_DATAPOINTS)
    {
        ncp_pka_get_profile_timestamp(&myProfHdl->profileData[pointIndex].results[i]);
    }
    return;
}

static __inline__
void ncp_pka_stop_profile(
    ncp_prof_t                 *myProfHdl,
    ncp_profile_points_t        pointIndex)
{
    int          i;
    ncp_uint64_t tmp64;

    if ((NULL == myProfHdl) ||
        (FALSE == myProfHdl->profileOn) ||
        (FALSE == myProfHdl->profileData[pointIndex].enabled))
    {
        return;
    }
    if ((i = myProfHdl->profileData[pointIndex].index) != NCP_NUM_PROFILE_DATAPOINTS)
    {
        ncp_pka_get_profile_timestamp(&tmp64);
        if (tmp64 > myProfHdl->profileData[pointIndex].results[i])
        {
            myProfHdl->profileData[pointIndex].results[i] =
                tmp64 - myProfHdl->profileData[pointIndex].results[i];
        }
        else
        {
            myProfHdl->profileData[pointIndex].results[i] =
                0xFFFFFFFFFFFFFFFFLL - myProfHdl->profileData[pointIndex].results[i] + tmp64;
        }
        myProfHdl->profileData[pointIndex].index++;
    }
    return;
}


void ncp_pka_init_profile(
    ncp_prof_t                 *myProfHdl);
void ncp_pka_stop_profile(
    ncp_prof_t                 *myProfHdl,
    ncp_profile_points_t        pointIndex);
void ncp_pka_start_profile(
    ncp_prof_t                 *myProfHdl,
    ncp_profile_points_t        pointIndex);

#if     !(defined(NCP_KERNEL) || defined(MODULE))
void ncp_pka_display_profile_stats(
    ncp_prof_t                 *myProfHdl,
    FILE                       *logFp);
#endif  /* !(defined(NCP_KERNEL) || defined(MODULE)) */


#else

#define ncp_pka_init_profile(a)
#define ncp_pka_get_profile_timestamp(a)
#define ncp_pka_stop_profile(a, b)
#define ncp_pka_start_profile(a, b)
#if     !(defined(NCP_KERNEL) || defined(MODULE))
#define ncp_pka_display_profile_stats(a, f)
#endif  /* !(defined(NCP_KERNEL) || defined(MODULE)) */

#endif /* PROC_PPC476 */

#else

#define ncp_pka_init_profile(a)
#define ncp_pka_get_profile_timestamp(a)
#define ncp_pka_stop_profile(a, b)
#define ncp_pka_start_profile(a, b)
#if     !(defined(NCP_KERNEL) || defined(MODULE))
#define ncp_pka_display_profile_stats(a, f)
#endif  /* !(defined(NCP_KERNEL) || defined(MODULE)) */

#define NCP_INIT_LOCK(_p, _s, _v)  	ncp_sem_init(_p, _s, _v)
#define NCP_DESTROY_LOCK(_p)       	ncp_sem_destroy(_p)
#define NCP_CLAIM_LOCK(_p, _f)		ncp_sem_wait(_p)
#define NCP_FREE_LOCK(_p, _f)		ncp_sem_post(_p)

typedef struct
{
    ncp_bool_t          profileOn;
} ncp_prof_t;

#endif /* NCP_PROFILE */


#endif /* NCP_PKA_TIMING_H */
