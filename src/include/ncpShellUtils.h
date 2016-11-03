/**************************************************************************
 *                                                                        *
 *                           Intel CONFIDENTIAL           *
 *                                                                        *
 *                       PROPRIETARY NOTE                                 *
 *                                                                        *
 *    This software contains information confidential and proprietary     *
 *    to Intel Corporation.  It shall not be reproduced in whole or in  *
 *    part, or transferred to other documents, or disclosed to third      *
 *    parties, or used for any purpose other than that for which it was   *
 *    obtained, without the prior written consent of Intel Corporation. *
 *    (c) 2008-2014, Intel Corporation.  All rights reserved.           *
 *                                                                        *
 *  ***********************************************************************
 *
 *  ***********************************************************************
 *
 *************************************************************************/

#ifndef _NCP_SHELL_UTILS_H_
#define _NCP_SHELL_UTILS_H_

#if     !defined(DOXYGEN)

#include "ncp.h"
#include "ncp_getopt.h"

#ifdef __cplusplus
extern "C" {
#endif


/* --- Common Definitions --- */

#ifndef MIN
#define MIN(x, y)       ((x) < (y) ? (x) : (y))
#endif

#ifndef MAX
#define MAX(x, y)       ((x) > (y) ? (x) : (y))
#endif

#ifndef NCP_ARRAY_SIZE
#define NCP_ARRAY_SIZE(array) (sizeof(array)/sizeof((array)[0]))
#endif

#define NCP_SHELL_BUFFER_SIZE    (512)   /* Bytes */
#define NCP_SHELL_MAX_BIT_WIDTH  (1024)

#define NCP_SHELL_NCP_DEFAULT_NODE   (0)
#define NCP_SHELL_NCP_DEFAULT_TARGET (0)

#define NCP_SHELL_MAX_FILL_WIDTH  (512/32) /* For Block Fill Command */

/* --- External Function Prototypes --- */

NCP_API
int ncpShellIntegerScan(
    const char *s,          /* IN:  ptr to integer string */
    unsigned int *val,      /* OUT: ptr to integer return location */
    int *skip);             /* OUT: ptr to sscanf offset return location */

NCP_API
int ncpShellInt8Scan(
    const char *s,          /* IN:  ptr to integer string */
    ncp_uint8_t *val8,      /* OUT: ptr to 8-bit return location */
    int *skip);             /* OUT: ptr to sscanf offset return location */

NCP_API
int ncpShellInt16Scan(
    const char *s,          /* IN:  ptr to integer string */
    ncp_uint16_t *val16,    /* OUT: ptr to 16-bit return location */
    int *skip);             /* OUT: ptr to sscanf offset return location */

NCP_API
int ncpShellInt64Scan(
    const char *s,          /* IN:  ptr to integer string */
    ncp_uint64_t *val64,    /* OUT: ptr to 16-bit return location */
    int *skip);             /* OUT: ptr to sscanf offset return location */

NCP_API
int ncpShellBdataScan(
    const char *s,          /* IN:  ptr to integer string */
    ncp_bdata_t *bdata,     /* OUT: ptr to bdata return location */
    int *skip);             /* OUT: ptr to sscanf offset return location */


NCP_API
int ncpShellNtoAddrScan(
    const char *nto,        /* IN:  ptr to node.target.offset string */
    ncp_uint32_t *devNum,   /* OUT: ptr to devNum return location */
    ncp_uint16_t *node,     /* OUT: ptr to node return location */
    ncp_uint16_t *target,   /* OUT: ptr to target return location */
    ncp_uint64_t *offset,   /* OUT: ptr to offset return location */
    int *skip);             /* OUT: ptr to sscanf offset return location */

NCP_API
int ncpShellMemSizeScan(
    const char *str,        /* IN:  ptr to memory size string */
    ncp_uint64_t *outSize); /* OUT: ptr to memory size return location */

NCP_API
int ncpShellEngineToRegion(
    const char *str,
    ncp_region_id_t *regionId);

NCP_API
int ncpShellRegionToEngine(
    ncp_region_id_t regionId,
    char **str);

NCP_API
ncp_st_t ncpShellCreateDummyNcp(
    ncp_uint32_t  devNum,
    ncp_dev_hdl_t devHdl,
    ncp_hdl_t    **ncpHdl);

NCP_API
int ncpShellBadUnsignedInt(
    const char *s,          /* IN:  ptr to unsigned integer string */
    int *skip);             /* OUT: ptr to sscanf offset return location */

#ifdef __cplusplus
}
#endif

#endif  /* !defined(DOXYGEN) */

#endif /* _NCP_SHELL_UTILS_H_ */
