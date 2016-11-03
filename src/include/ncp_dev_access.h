/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


#ifndef __NCP_DEV_ACCESS_MAP_H__
#define __NCP_DEV_ACCESS_MAP_H__

static ncp_access_map_t ncpDummyRegionMap[] = {
    { 0x00000000, 0x81000000, NCP_DEV_ACCESS_RW   },
    {          0,          0, NCP_DEV_ACCESS_NONE }
};

/*
 * Allow up to 64GB of system memory for FBRS and simulator. 
 * On h/w platforms we should detect the available memory
 * and reset this to the actual value. 
 */
static ncp_access_map_t ncpSysmemRegionMap[] = {
    { 0x00000000ULL, 0x1000000000ULL, NCP_DEV_ACCESS_RW   },
    {             0,               0, NCP_DEV_ACCESS_NONE }
};


#endif
