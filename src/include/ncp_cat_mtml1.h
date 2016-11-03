/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*! @file       ncp_cat_mtml1.h
    @brief      Support data for CAT configuration of MTM L1 Cache data
                within RTE
*/

#ifndef _NCP_CAT_MTML1_H_
#define _NCP_CAT_MTML1_H_

#include "ncp.h"


/**************************************************************************
* Common Data                                                             *
**************************************************************************/

typedef struct
{
    ncp_region_id_t     regionId;
    const char         *name;
} ncp_cat_mtml1_regions_t;

#if     !defined(NCP_MTM_NO_DATA)
static
ncp_cat_mtml1_regions_t ncp_cat_mtml1_regions[6] =
{
    { NCP_REGION_ID(0x14, 0x18), "MTM Scheduler Level 5 L1" },
    { NCP_REGION_ID(0x14, 0x19), "MTM Scheduler Level 4 L1" },
    { NCP_REGION_ID(0x14, 0x1a), "MTM Scheduler Level 3 L1" },
    { NCP_REGION_ID(0x14, 0x1b), "MTM Scheduler Level 2 L1" },
    { NCP_REGION_ID(0x14, 0x1c), "MTM Scheduler Level 1 L1" },
    { NCP_REGION_ID(0x14, 0x1d), "MTM Queue L1" },
};

static
ncp_uint32_t ncp_cat_mtml1_regions_count = sizeof(ncp_cat_mtml1_regions)/sizeof(ncp_cat_mtml1_regions_t);
#endif  /* !defined(NCP_MTM_NO_DATA) */

#define NCP_CAT_MTML1C_UNDOC_REGS       5
#define NCP_CAT_MTML1C_UNDOC_REGS_STR   "Undocumented Registers"

typedef struct
{
    const char         *name;
    ncp_uint32_t        sel;
    ncp_uint32_t        num_entries;
    ncp_uint32_t        words_per_entry;
    ncp_uint32_t        custom0;        /* Usually zero.
                                         * Initial register offset for
                                         * "Undocumented Registers */
} ncp_cat_mtml1_registers_t;

#if     !defined(NCP_MTM_NO_DATA)
        /* Blocks of registers to read within each region */
static const
ncp_cat_mtml1_registers_t       ncp_cat_mtml1_registers[6] =
{
    { "MTM L1 Data RAM",          0, 32, 16, 0 },
    { "MTM L1 Tag RAM",           1, 32,  1, 0 },
    { "MTM L1 Check For Read DB", 2,  4,  1, 0 },
    { "MTM L1 Vector Valid DB",   3, 32,  1, 0 },
    { "MTM L1 Ref Count DB",      4, 32,  1, 0 },
    { NCP_CAT_MTML1C_UNDOC_REGS_STR, NCP_CAT_MTML1C_UNDOC_REGS, 10,  1, 0x120 },
};

static
ncp_uint32_t ncp_cat_mtml1_registers_count = sizeof(ncp_cat_mtml1_registers)/sizeof(ncp_cat_mtml1_registers_t);
#endif  /* !defined(NCP_MTM_NO_DATA) */


#endif /* _NCP_CAT_MTML1_H_ */
