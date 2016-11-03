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

#ifndef _NCP_SHELL_H_
#define _NCP_SHELL_H_

#if     !defined(DOXYGEN)

#include "ncp.h"
#include "ncp_pvt.h"
#include "ncp_crt.h"

#ifdef __cplusplus
extern "C" {
#endif


/* --- Local Definitions --- */

#define NCP_DEFAULT_NODE      (0)
#define NCP_DEFAULT_TARGET    (0)


#define NCP_DEV_OPEN(devNum, flags, devHdl) \
    do { \
        ncp_malloc_leak_init(); \
        ncpStatus = ncp_dev_open(devNum, flags, devHdl); \
        if (ncpStatus != NCP_ST_SUCCESS) { \
            ncp_status_print("Error: ncp_dev_open failed", ncpStatus); \
            goto ncp_return; \
        } \
    } while (0);

#define NCP_DEV_CLOSE(devHdl) \
    do { \
        ncp_st_t mySt = ncp_dev_close(devHdl); \
        if (mySt != NCP_ST_SUCCESS) { \
            ncp_status_print("Error: ncp_dev_close failed", mySt); \
        } \
        ncp_malloc_leak_status(); \
    } while (0);

#define NCP_DEV_READ8(hdl, regId, offset, value) \
    do { \
        ncpStatus = ncp_read8(hdl, regId, offset, value); \
        if (ncpStatus != NCP_ST_SUCCESS) { \
            ncp_status_print( \
                "Error: ncp_read8 failed", ncpStatus); \
            goto ncp_return; \
        } \
    } while (0);

#define NCP_DEV_READ16(hdl, regId, offset, value) \
    do { \
        ncpStatus = ncp_read16(hdl, regId, offset, value); \
        if (ncpStatus != NCP_ST_SUCCESS) { \
            ncp_status_print( \
                "Error: ncp_read16 failed", ncpStatus); \
            goto ncp_return; \
        } \
    } while (0);

#define NCP_DEV_READ32(hdl, regId, offset, value) \
    do { \
        ncpStatus = ncp_read32(hdl, regId, offset, value); \
        if (ncpStatus != NCP_ST_SUCCESS) { \
            ncp_status_print( \
                "Error: ncp_read32 failed", ncpStatus); \
            goto ncp_return; \
        } \
    } while (0);

#define NCP_DEV_READ64(hdl, regId, offset, value) \
    do { \
        ncpStatus = ncp_read64(hdl, regId, offset, value); \
        if (ncpStatus != NCP_ST_SUCCESS) { \
            ncp_status_print( \
                "Error: ncp_read64 failed", ncpStatus); \
            goto ncp_return; \
        } \
    } while (0);

#define NCP_DEV_WRITE8(hdl, regId, offset, value) \
    do { \
        ncpStatus = ncp_write8(hdl, regId, offset, value); \
        if (ncpStatus != NCP_ST_SUCCESS) { \
            ncp_status_print( \
                "Error: ncp_write8 failed", ncpStatus); \
            goto ncp_return; \
        } \
    } while (0);

#define NCP_DEV_WRITE16(hdl, regId, offset, value) \
    do { \
        ncpStatus = ncp_write16(hdl, regId, offset, value); \
        if (ncpStatus != NCP_ST_SUCCESS) { \
            ncp_status_print( \
                "Error: ncp_write16 failed", ncpStatus); \
            goto ncp_return; \
        } \
    } while (0);

#define NCP_DEV_WRITE32(hdl, regId, offset, value) \
    do { \
        ncpStatus = ncp_write32(hdl, regId, offset, value); \
        if (ncpStatus != NCP_ST_SUCCESS) { \
            ncp_status_print( \
                "Error: ncp_write32 failed", ncpStatus); \
            goto ncp_return; \
        } \
    } while (0);

#define NCP_DEV_WRITE64(hdl, regId, offset, value) \
    do { \
        ncpStatus = ncp_write64(hdl, regId, offset, value); \
        if (ncpStatus != NCP_ST_SUCCESS) { \
            ncp_status_print( \
                "Error: ncp_write64 failed", ncpStatus); \
            goto ncp_return; \
        } \
    } while (0);

#define NCP_DEV_BLOCK_READ8(hdl, regId, offset, buf, count, flags) \
    do { \
        ncpStatus = ncp_block_read8(hdl, regId, offset, buf, count, flags); \
        if (ncpStatus != NCP_ST_SUCCESS) { \
            ncp_status_print( \
                "Error: ncp_block_read8 failed", ncpStatus); \
            goto ncp_return; \
        } \
    } while (0);

#define NCP_DEV_BLOCK_READ16(hdl, regId, offset, buf, count, flags) \
    do { \
        ncpStatus = ncp_block_read16(hdl, regId, offset, buf, count, flags); \
        if (ncpStatus != NCP_ST_SUCCESS) { \
            ncp_status_print( \
                "Error: ncp_block_read16 failed", ncpStatus); \
            goto ncp_return; \
        } \
    } while (0);

#define NCP_DEV_BLOCK_READ32(hdl, regId, offset, buf, count, flags) \
    do { \
        ncpStatus = ncp_block_read32(hdl, regId, offset, buf, count, flags); \
        if (ncpStatus != NCP_ST_SUCCESS) { \
            ncp_status_print( \
                "Error: ncp_block_read32 failed", ncpStatus); \
            goto ncp_return; \
        } \
    } while (0);

#define NCP_DEV_BLOCK_READ64(hdl, regId, offset, buf, count, flags) \
    do { \
        ncpStatus = ncp_block_read64(hdl, regId, offset, buf, count, flags); \
        if (ncpStatus != NCP_ST_SUCCESS) { \
            ncp_status_print( \
                "Error: ncp_block_read64 failed", ncpStatus); \
            goto ncp_return; \
        } \
    } while (0);

#define NCP_DEV_BLOCK_WRITE8(hdl, regId, offset, buf, count, flags) \
    do { \
        ncpStatus = ncp_block_write8(hdl, regId, offset, buf, count, flags); \
        if (ncpStatus != NCP_ST_SUCCESS) { \
            ncp_status_print( \
                    "Error: ncp_block_write8 failed", ncpStatus); \
            goto ncp_return; \
        } \
    } while (0);

#define NCP_DEV_BLOCK_WRITE16(hdl, regId, offset, buf, count, flags) \
    do { \
        ncpStatus = ncp_block_write16(hdl, regId, offset, buf, count, flags); \
        if (ncpStatus != NCP_ST_SUCCESS) { \
            ncp_status_print( \
                    "Error: ncp_block_write16 failed", ncpStatus); \
            goto ncp_return; \
        } \
    } while (0);

#define NCP_DEV_BLOCK_WRITE32(hdl, regId, offset, buf, count, flags) \
    do { \
        ncpStatus = ncp_block_write32(hdl, regId, offset, buf, count, flags);  \
        if (ncpStatus != NCP_ST_SUCCESS) { \
            ncp_status_print( \
                    "Error: ncp_block_write32 failed", ncpStatus); \
            goto ncp_return; \
        } \
    } while (0);

#define NCP_DEV_BLOCK_WRITE64(hdl, regId, offset, buf, count, flags) \
    do { \
        ncpStatus = ncp_block_write64(hdl, regId, offset, buf, count, flags);  \
        if (ncpStatus != NCP_ST_SUCCESS) { \
            ncp_status_print( \
                    "Error: ncp_block_write64 failed", ncpStatus); \
            goto ncp_return; \
        } \
    } while (0);

/*
 * The new generic FILL that supports address stride and variable fill width of 32-256 bits in word increments.
 */
#define NCP_DEV_BLOCK_FILL(hdl, regId, offset, ncp_fill_p, flags) \
    do { \
        ncpStatus = ncp_block_fill(hdl, regId, offset, ncp_fill_p, flags); \
        if (ncpStatus != NCP_ST_SUCCESS) { \
            ncp_status_print( \
                    "Error: ncp_block_fill failed", ncpStatus); \
            goto ncp_return; \
        } \
    } while (0);

#define NCP_DEV_SCATTER_WRITE(hdl, regId, buf, flags) \
    do { \
        ncpStatus = ncp_scatter_write(hdl, regId, buf, flags); \
        if (ncpStatus != NCP_ST_SUCCESS) { \
            ncp_status_print( \
                "Error: ncp_scatter_write failed", ncpStatus); \
            goto ncp_return; \
        } \
    } while (0);

#define NCP_DEV_BCAST_SCATTER_WRITE(hdl, regId, buf, flags) \
    do { \
        ncpStatus = ncp_broadcast_scatter_write(hdl, regId, buf, flags); \
        if (ncpStatus != NCP_ST_SUCCESS) { \
            ncp_status_print( \
                "Error: ncp_broadcast_scatter_write failed", ncpStatus); \
            goto ncp_return; \
        } \
    } while (0);


#define NCP_DEV_PCI_CONFIG_READ(hdl, offset, width, data) \
    do { \
        ncpStatus = ncp_dev_pci_config_read(hdl, offset, width, data); \
        if (ncpStatus != NCP_ST_SUCCESS) { \
            ncp_status_print( \
                    "Error: ncp_dev_pci_config_read failed", ncpStatus); \
            goto ncp_return; \
        } \
    } while (0);

#define NCP_DEV_PCI_CONFIG_WRITE(hdl, offset, width, data) \
    do { \
        ncpStatus = ncp_dev_pci_config_write(hdl, offset, width, data); \
        if (ncpStatus != NCP_ST_SUCCESS) { \
            ncp_status_print( \
                    "Error: ncp_dev_pci_config_write failed", ncpStatus); \
            goto ncp_return; \
        } \
    } while (0);

#if 0
    /* NCP_CFG_LOAD_COMPLETE is no longer used!! */
#define NCP_CFG_CHECK(hdl) \
    do { \
        ncp_uint32_t devFlags; \
        ncp_dev_info_get((hdl), &devFlags); \
        if (!(devFlags & NCP_DEV_FBAPI_MODE) && \
            !(devFlags & NCP_CFG_LOAD_COMPLETE)) { \
            printf("Error:  Configuration image not loaded.\n"); \
            goto ncp_return; \
        } \
    } while (0);
#endif

typedef enum NcpVerboseLevel_e
{
    NcpVerboseLevel0_e,
    NcpVerboseLevel1_e,
    NcpVerboseLevel2_e,

    NcpVerboseLast_e
}
NcpVerboseLevel_e;


/* --- External Function Protypes --- */

#ifdef __cplusplus
}
#endif

#endif  /* !defined(DOXYGEN) */

#endif /* _NCP_SHELL_H_ */
