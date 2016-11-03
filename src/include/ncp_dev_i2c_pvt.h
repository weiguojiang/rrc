/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


/*! @file       ncp_dev_i2c_pvt.h
 *  @brief      Constants, structs, and APIs used to communicate with the
 *              direct ACP I2C Hardware Layer registers
 */

#ifndef NCP_DEV_I2C_PVT_H
#define NCP_DEV_I2C_PVT_H

#include "ncp_dev_i2c.h"

/*****************************************************************************
* Constants                                                                  *
*****************************************************************************/

#define BIT_I2C_MODE_ONLINE     0x00000001
#define BIT_I2C_MODE_AXM55xx    0x00000002
#define BIT_I2C_MODE_ACP34xx    0x00000004

#define I2C_MODE_FORCE(v)       ((v) & BIT_I2C_MODE_ONLINE)
                                /* Bring online in one of the 'forced' modes
                                 */
#define I2C_MODE_AXM55xx(v)     ((v) & BIT_I2C_MODE_AXM55xx)
                                /* Select AXM55xx chipType as force mode */
#define I2C_MODE_ACP34xx(v)     ((v) & BIT_I2C_MODE_ACP34xx)
                                /* Select ACP34xx chipType as force mode */
#define I2C_MODE_NON_AXM55xx(v) (I2C_MODE_ACP34xx(v))
#define I2C_MODE_NON_ACP34xx(v) (I2C_MODE_AXM55xx(v))


/*****************************************************************************
* Type definitions                                                           *
*****************************************************************************/

/*****************************************************************************
* Externally Visible Variables                                               *
*****************************************************************************/

extern
int     ncp_i2c_mode;           /* Override default settings to bring up
                                 * this module.  See I2C_MODE_xxx
                                 * masks and macros above for values. */

/*****************************************************************************
* Externally Visible Function Prototypes                                     *
*****************************************************************************/


#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif   /* defined(NCP_DEV_I2C_PVT_H) */
