/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


#ifndef _NCP_EIOA_CONFIG_55XX_H_
#define _NCP_EIOA_CONFIG_55XX_H_

#ifdef __cplusplus
extern "C" {
#endif

#define NOT_DONE 1
#define NCP_GMAC_PORT(n) (0x00000300 + (0xC0 * (n)))

#define NCP_ISB_ID 0xff

#define NCP_ISB_REGION_ID(d)                                                    \
    ({                                                                          \
        ncp_uint32_t __regionId = 0;                                            \
        if(d)                                                                   \
        {                                                                       \
            __regionId = NCP_REGION_ID(0x31, 0x10);                             \
        }                                                                       \
        else                                                                    \
        {                                                                       \
            __regionId = NCP_REGION_ID(0x32, 0x10);                             \
        }                                                                       \
        __regionId;                                                             \
    })

#if !defined(NCP_KERNEL)
#define NCP_EIOA_NEMAC_UCAST_OFFSET(external_port, xgmac_flag)               \
    ({                                                                       \
        ncp_uint32_t __cr_off = 0;                                           \
        if (xgmac_flag == TRUE)                                              \
        {                                                                    \
            switch(external_port)                                            \
            {                                                                \
            case NCP_XGMAC0:                                                 \
            case NCP_XGMAC16:                                                \
            case NCP_XGMAC32:                                                \
            case NCP_XGMAC48:                                                \
            case NCP_XGMAC64:                                                \
            case NCP_XGMAC80:                                                \
            case NCP_XGMAC96:                                                \
            case NCP_XGMAC112:                                               \
            __cr_off = (ncp_uint32_t)NCP_NEMAC0_XGMAC_BASE;                  \
            __cr_off += (ncp_uint32_t)NCP_NEMAC0_XGMAC_UCAST_MASK_LOWER;     \
            break;                                                           \
            case NCP_XGMAC1:                                                 \
            case NCP_XGMAC17:                                                \
            case NCP_XGMAC33:                                                \
            case NCP_XGMAC49:                                                \
            case NCP_XGMAC65:                                                \
            case NCP_XGMAC81:                                                \
            case NCP_XGMAC97:                                               \
            case NCP_XGMAC113:                                               \
            __cr_off = (ncp_uint32_t)NCP_NEMAC1_XGMAC_BASE;                  \
            __cr_off += (ncp_uint32_t)NCP_NEMAC1_XGMAC_UCAST_MASK_LOWER;     \
            break;                                                           \
            default:                                                         \
            __cr_off = 0;                                                    \
            break;                                                           \
            }                                                                \
        }                                                                    \
        else                                                                 \
        {                                                                    \
            switch(external_port)                                            \
            {                                                                \
            case NCP_GMAC0:                                                  \
            case NCP_GMAC16:                                                 \
            case NCP_GMAC32:                                                 \
            case NCP_GMAC48:                                                 \
            case NCP_GMAC64:                                                 \
            case NCP_GMAC80:                                                 \
            case NCP_GMAC96:                                                 \
            case NCP_GMAC112:                                                \
            __cr_off=(ncp_uint32_t)NCP_NEMAC0_GMAC_BASE(0);                  \
            __cr_off += (ncp_uint32_t)NCP_NEMAC0_GMAC_UCAST_MASK_LOWER;      \
            break;                                                           \
            case NCP_GMAC1:                                                  \
            case NCP_GMAC17:                                                 \
            case NCP_GMAC33:                                                 \
            case NCP_GMAC49:                                                 \
            case NCP_GMAC65:                                                 \
            case NCP_GMAC81:                                                 \
            case NCP_GMAC97:                                                \
            case NCP_GMAC113:                                                \
            __cr_off=(ncp_uint32_t)NCP_NEMAC1_GMAC_BASE(0);                  \
            __cr_off += (ncp_uint32_t)NCP_NEMAC1_GMAC_UCAST_MASK_LOWER;      \
            break;                                                           \
            case NCP_GMAC2:                                                  \
            case NCP_GMAC18:                                                 \
            __cr_off=(ncp_uint32_t)NCP_NEMAC1_GMAC_BASE(1);                  \
            __cr_off += (ncp_uint32_t)NCP_NEMAC1_GMAC_UCAST_MASK_LOWER;      \
            break;                                                           \
            case NCP_GMAC3:                                                  \
            case NCP_GMAC19:                                                 \
            __cr_off=(ncp_uint32_t)NCP_NEMAC1_GMAC_BASE(2);                  \
            __cr_off += (ncp_uint32_t)NCP_NEMAC1_GMAC_UCAST_MASK_LOWER;      \
            break;                                                           \
            case NCP_GMAC4:                                                  \
            case NCP_GMAC20:                                                 \
            __cr_off=(ncp_uint32_t)NCP_NEMAC1_GMAC_BASE(3);                  \
            __cr_off += (ncp_uint32_t)NCP_NEMAC1_GMAC_UCAST_MASK_LOWER;      \
            break;                                                           \
            default:                                                         \
            __cr_off = 0;                                                    \
            break;                                                           \
            }                                                                \
        }                                                                    \
        __cr_off;                                                            \
    })

#define NCP_EIOA_NEMAC_CR_OFFSET(external_port, mac_cr, xgmac_flag)          \
    ({                                                                       \
        ncp_uint32_t __cr_off = 0;                                           \
        if (xgmac_flag == TRUE)                                              \
        {                                                                    \
            switch(external_port)                                            \
            {                                                                \
            case NCP_XGMAC0:                                                 \
            case NCP_XGMAC16:                                                \
            case NCP_XGMAC32:                                                \
            case NCP_XGMAC48:                                                \
            case NCP_XGMAC64:                                                \
            case NCP_XGMAC80:                                                \
            case NCP_XGMAC96:                                                \
            case NCP_XGMAC112:                                               \
            __cr_off=(ncp_uint32_t)NCP_NEMAC0_XGMAC_BASE + 4 * mac_cr;       \
            break;                                                           \
            case NCP_XGMAC1:                                                 \
            case NCP_XGMAC17:                                                \
            case NCP_XGMAC33:                                                \
            case NCP_XGMAC49:                                                \
            case NCP_XGMAC65:                                                \
            case NCP_XGMAC81:                                                \
            case NCP_XGMAC97:                                               \
            case NCP_XGMAC113:                                               \
            __cr_off=(ncp_uint32_t)NCP_NEMAC1_XGMAC_BASE + 4 * mac_cr;       \
            break;                                                           \
            case NCP_XGMAC8:                                             \
            case NCP_GMAC9:                                              \
            case NCP_GMAC10:                                             \
            case NCP_GMAC11:                                             \
            case NCP_GMAC12:                                             \
            __cr_off= 0;                                                     \
            break;                                                           \
            default:                                                     \
            __cr_off= 0;                                                     \
            break;                                                           \
            }                                                                \
        }                                                                    \
        else                                                                 \
        {                                                                    \
            switch(external_port)                                            \
            {                                                                \
            case NCP_GMAC0:                                                  \
            case NCP_GMAC16:                                                 \
            case NCP_GMAC32:                                                 \
            case NCP_GMAC48:                                                 \
            case NCP_GMAC64:                                                 \
            case NCP_GMAC80:                                                 \
            case NCP_GMAC96:                                                 \
            case NCP_GMAC112:                                                \
            __cr_off=(ncp_uint32_t)NCP_NEMAC0_GMAC_BASE(0);                  \
            __cr_off += 4 * mac_cr;                                          \
            break;                                                           \
            case NCP_GMAC1:                                                  \
            case NCP_GMAC17:                                                 \
            case NCP_GMAC33:                                                 \
            case NCP_GMAC49:                                                 \
            case NCP_GMAC65:                                                 \
            case NCP_GMAC81:                                                 \
            case NCP_GMAC97:                                                \
            case NCP_GMAC113:                                                \
            __cr_off=(ncp_uint32_t)NCP_NEMAC1_GMAC_BASE(0);                  \
            __cr_off += 4 * mac_cr;                                          \
            break;                                                           \
            case NCP_GMAC2:                                                  \
            case NCP_GMAC18:                                                 \
            __cr_off=(ncp_uint32_t)NCP_NEMAC1_GMAC_BASE(1);                  \
            __cr_off += 4 * mac_cr;                                          \
            break;                                                           \
            case NCP_GMAC3:                                                  \
            case NCP_GMAC19:                                                 \
            __cr_off=(ncp_uint32_t)NCP_NEMAC1_GMAC_BASE(2);                  \
            __cr_off += 4 * mac_cr;                                          \
            break;                                                           \
            case NCP_GMAC4:                                                  \
            case NCP_GMAC20:                                                 \
            __cr_off=(ncp_uint32_t)NCP_NEMAC1_GMAC_BASE(3);                  \
            __cr_off += 4 * mac_cr;                                          \
            break;                                                           \
            case NCP_XGMAC8:                                                  \
            case NCP_GMAC9:                                                  \
            case NCP_GMAC10:                                                 \
            case NCP_GMAC11:                                                 \
            case NCP_GMAC12:                                                 \
            __cr_off= 0;                                                     \
            break;                                                           \
            default:                                                         \
            __cr_off= 0;                                                     \
            break;                                                           \
            }                                                                \
        }                                                                    \
        __cr_off;                                                            \
    })

#define NCP_EIOA_NEMAC_EXTERNAL_PORT_TO_REGION_ID(external_port, xgmac_flag) \
    ({                                                                       \
        ncp_uint32_t __nemac_region = 0;                                     \
        if (xgmac_flag == TRUE)                                              \
        {                                                                    \
            switch(external_port)                                            \
            {                                                                \
                case NCP_XGMAC0:                                             \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA0_NEMAC0;  \
                break;                                                       \
                case NCP_XGMAC1:                                             \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA0_NEMAC1;  \
                break;                                                       \
                case NCP_XGMAC16:                                            \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA1_NEMAC0;  \
                break;                                                       \
                case NCP_XGMAC17:                                            \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA1_NEMAC1;  \
                break;                                                       \
                case NCP_XGMAC32:                                            \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA2_NEMAC0;  \
                break;                                                       \
                case NCP_XGMAC33:                                            \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA2_NEMAC1;  \
                break;                                                       \
                case NCP_XGMAC48:                                            \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA3_NEMAC0;  \
                break;                                                       \
                case NCP_XGMAC49:                                            \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA3_NEMAC1;  \
                break;                                                       \
                case NCP_XGMAC64:                                            \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA4_NEMAC0;  \
                break;                                                       \
                case NCP_XGMAC65:                                            \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA4_NEMAC1;  \
                break;                                                       \
                case NCP_XGMAC80:                                            \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA5_NEMAC0;  \
                break;                                                       \
                case NCP_XGMAC81:                                            \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA5_NEMAC1;  \
                break;                                                       \
                case NCP_XGMAC96:                                            \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA6_NEMAC0;  \
                break;                                                       \
                case NCP_XGMAC97:                                           \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA6_NEMAC1;  \
                break;                                                       \
                case NCP_XGMAC112:                                           \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA7_NEMAC0;  \
                break;                                                       \
                case NCP_XGMAC113:                                           \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA7_NEMAC1;  \
                break;                                                       \
                case NCP_XGMAC8:                                             \
                case NCP_GMAC9:                                              \
                case NCP_GMAC10:                                             \
                case NCP_GMAC11:                                             \
                case NCP_GMAC12:                                             \
                    __nemac_region = (ncp_uint32_t)0;                        \
                break;                                                       \
                default:                                                     \
                    __nemac_region = (ncp_uint32_t)0;                        \
                break;                                                       \
            }                                                                \
        }                                                                    \
        else                                                                 \
        {                                                                    \
            switch(external_port)                                            \
            {                                                                \
                case NCP_GMAC0:                                              \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA0_NEMAC0;  \
                break;                                                       \
                case NCP_GMAC1:                                              \
                case NCP_GMAC2:                                              \
                case NCP_GMAC3:                                              \
                case NCP_GMAC4:                                              \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA0_NEMAC1;  \
                break;                                                       \
                case NCP_GMAC16:                                             \
                   __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA1_NEMAC0;  \
                break;                                                       \
                case NCP_GMAC17:                                             \
                case NCP_GMAC18:                                             \
                case NCP_GMAC19:                                             \
                case NCP_GMAC20:                                             \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA1_NEMAC1;  \
                break;                                                       \
                case NCP_GMAC32:                                             \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA2_NEMAC0;  \
                break;                                                       \
                case NCP_GMAC33:                                             \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA2_NEMAC1;  \
                break;                                                       \
                case NCP_GMAC48:                                             \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA3_NEMAC0;  \
                break;                                                       \
                case NCP_GMAC49:                                             \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA3_NEMAC1;  \
                break;                                                       \
                case NCP_GMAC64:                                             \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA4_NEMAC0;  \
                break;                                                       \
                case NCP_GMAC65:                                             \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA4_NEMAC1;  \
                break;                                                       \
                case NCP_GMAC80:                                             \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA5_NEMAC0;  \
                break;                                                       \
                case NCP_GMAC81:                                             \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA5_NEMAC1;  \
                break;                                                       \
                case NCP_GMAC96:                                             \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA6_NEMAC0;  \
                break;                                                       \
                case NCP_GMAC97:                                            \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA6_NEMAC1;  \
                break;                                                       \
                case NCP_GMAC112:                                            \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA7_NEMAC0;  \
                break;                                                       \
                case NCP_GMAC113:                                            \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA7_NEMAC1;  \
                break;                                                       \
                case NCP_XGMAC8:                                             \
                case NCP_GMAC9:                                              \
                case NCP_GMAC10:                                             \
                case NCP_GMAC11:                                             \
                case NCP_GMAC12:                                             \
                    __nemac_region = (ncp_uint32_t)0;                        \
                break;                                                       \
                default:                                                     \
                    __nemac_region = (ncp_uint32_t)0;                        \
                break;                                                       \
            }                                                                \
        }                                                                    \
        __nemac_region;                                                      \
    })

#define NCP_EIOA_CORE_EXTERNAL_PORT_TO_REGION_ID(external_port) \
    ({                                                      \
        ncp_uint32_t __regionId = 0;                        \
        switch(external_port)                               \
        {                                                   \
        case NCP_GMAC0:                                     \
        case NCP_GMAC1:                                     \
        case NCP_GMAC2:                                     \
        case NCP_GMAC3:                                     \
        case NCP_GMAC4:                                     \
            __regionId = NCP_REGION_EIOA0_CORE;             \
        break;                                              \
        case NCP_GMAC16:                                    \
        case NCP_GMAC17:                                    \
        case NCP_GMAC18:                                    \
        case NCP_GMAC19:                                    \
        case NCP_GMAC20:                                    \
            __regionId = NCP_REGION_EIOA1_CORE;             \
        break;                                              \
        case NCP_GMAC32:                                    \
        case NCP_GMAC33:                                    \
            __regionId = NCP_REGION_EIOA2_CORE;             \
        break;                                              \
        case NCP_GMAC48:                                    \
        case NCP_GMAC49:                                    \
            __regionId = NCP_REGION_EIOA3_CORE;             \
        break;                                              \
        case NCP_GMAC64:                                    \
        case NCP_GMAC65:                                    \
            __regionId = NCP_REGION_EIOA4_CORE;             \
        break;                                              \
        case NCP_GMAC80:                                    \
        case NCP_GMAC81:                                    \
            __regionId = NCP_REGION_EIOA5_CORE;             \
        break;                                              \
        case NCP_GMAC96:                                    \
        case NCP_GMAC97:                                    \
            __regionId = NCP_REGION_EIOA6_CORE;             \
        break;                                              \
        case NCP_GMAC112:                                   \
        case NCP_GMAC113:                                   \
            __regionId = NCP_REGION_EIOA7_CORE;             \
        break;                                              \
        case NCP_XGMAC8:                                    \
        case NCP_GMAC9:                                     \
        case NCP_GMAC10:                                    \
        case NCP_GMAC11:                                    \
        case NCP_GMAC12:                                    \
            __regionId = 0;                                 \
        break;                                              \
        default:                                            \
            __regionId = 0;                                 \
        break;                                              \
        }                                                   \
        __regionId;                                         \
    })

#define NCP_EIOA_CORE_EIOA_NUM_TO_REGION_ID(eioa_num)       \
    ({                                                      \
        ncp_uint32_t __regionId = 0xFFFF;                   \
        switch(eioa_num)                                    \
        {                                                   \
        case NCP_EIOA0:                                     \
            __regionId = NCP_REGION_EIOA0_CORE;             \
            break;                                          \
        case NCP_EIOA1:                                     \
            __regionId = NCP_REGION_EIOA1_CORE;             \
            break;                                          \
        case NCP_EIOA2:                                     \
            __regionId = NCP_REGION_EIOA2_CORE;             \
            break;                                          \
        case NCP_EIOA3:                                     \
            __regionId = NCP_REGION_EIOA3_CORE;             \
            break;                                          \
        case NCP_EIOA4:                                     \
            __regionId = NCP_REGION_EIOA4_CORE;             \
            break;                                          \
        case NCP_EIOA5:                                     \
            __regionId = NCP_REGION_EIOA5_CORE;             \
            break;                                          \
        case NCP_EIOA6:                                     \
            __regionId = NCP_REGION_EIOA6_CORE;             \
            break;                                          \
        case NCP_EIOA7:                                     \
            __regionId = NCP_REGION_EIOA7_CORE;             \
            break;                                          \
        default:                                            \
            NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);      \
            break;                                          \
        }                                                   \
        __regionId;                                         \
    })

#endif

#define NCP_EIOA_TO_INDEX_55xx(macChan)                                    \
    ({                                                                     \
        ncp_uint32_t   __eioa_index = NCP_EIOA0;                           \
        if ((macChan >= NCP_XGMAC0) && (macChan <= NCP_GMAC4))             \
        {                                                                 \
            __eioa_index = NCP_EIOA0;                                              \
        }                                                                 \
        else if ((macChan >= NCP_XGMAC16) && (macChan <= NCP_GMAC20))      \
        {                                                                 \
            __eioa_index = NCP_EIOA1;                                              \
        }                                                                 \
        else if ((macChan >= NCP_XGMAC32) && (macChan <= NCP_GMAC33))      \
        {                                                                 \
            __eioa_index = NCP_EIOA2;                                              \
        }                                                                 \
        else if ((macChan >= NCP_XGMAC48) && (macChan <= NCP_GMAC49))      \
        {                                                                 \
            __eioa_index = NCP_EIOA3;                                              \
        }                                                                 \
        else if ((macChan >= NCP_XGMAC64) && (macChan <= NCP_GMAC65))      \
        {                                                                 \
            __eioa_index = NCP_EIOA4;                                              \
        }                                                                 \
        else if ((macChan >= NCP_XGMAC80) && (macChan <= NCP_GMAC81))      \
        {                                                                 \
            __eioa_index = NCP_EIOA5;                                              \
        }                                                                 \
        else if ((macChan >= NCP_XGMAC96) && (macChan <= NCP_GMAC97))     \
        {                                                                 \
            __eioa_index = NCP_EIOA6;                                              \
        }                                                                 \
        else if ((macChan >= NCP_XGMAC112) && (macChan <= NCP_GMAC113))    \
        {                                                                 \
            __eioa_index = NCP_EIOA7;                                              \
        }                                                                 \
        __eioa_index;                                                      \
    })

#if !defined(NCP_KERNEL)

#define NCP_EIOA_PORT_TO_HSS_LANE(macChn)                                  \
({                                                                         \
    ncp_uint32_t __lane = 0xff;                                            \
    switch(macChan)                                                        \
    {                                                                      \
        case NCP_GMAC0:                                                    \
        case NCP_GMAC17:                                                   \
        case NCP_GMAC32:                                                   \
        case NCP_GMAC64:                                                   \
        case NCP_GMAC96:                                                   \
            __lane = 0;                                                    \
        break;                                                             \
        case NCP_GMAC1:                                                    \
        case NCP_GMAC3:                                                    \
        case NCP_GMAC4:                                                    \
        case NCP_GMAC18:                                                   \
        case NCP_GMAC33:                                                   \
        case NCP_GMAC65:                                                   \
        case NCP_GMAC97:                                                   \
            __lane = 1;                                                    \
        break;                                                             \
        case NCP_GMAC2:                                                    \
        case NCP_GMAC19:                                                   \
        case NCP_GMAC48:                                                   \
        case NCP_GMAC80:                                                   \
        case NCP_GMAC112:                                                  \
            __lane = 2;                                                    \
        break;                                                             \
        case NCP_GMAC16:                                                   \
        case NCP_GMAC20:                                                   \
        case NCP_GMAC49:                                                   \
        case NCP_GMAC81:                                                   \
        case NCP_GMAC113:                                                  \
            __lane = 3;                                                    \
        break;                                                             \
        default:                                                           \
            NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                     \
        break;                                                             \
    }                                                                      \
    __lane;                                                                \
})

#define NCP_EIOA_NUM_TO_HSS(eioa_num)                                           \
({                                                                              \
    ncp_uint32_t __hss = 0xff;                                                  \
    switch(eioa_num)                                                            \
    {                                                                           \
    case NCP_EIOA0:                                                             \
        __hss = 0;                                                              \
        break;                                                                  \
    case NCP_EIOA1:                                                             \
        __hss = 1;                                                              \
        break;                                                                  \
    case NCP_EIOA2:                                                             \
    case NCP_EIOA3:                                                             \
        __hss = 2;                                                              \
        break;                                                                  \
    case NCP_EIOA4:                                                             \
    case NCP_EIOA5:                                                             \
        __hss = 3;                                                              \
        break;                                                                  \
    case NCP_EIOA6:                                                             \
    case NCP_EIOA7:                                                             \
        __hss = 4;                                                              \
        break;                                                                  \
    }                                                                           \
    __hss;                                                                      \
})

#define NCP_EIOA_MODULE_IS_ENABLED(ncp, eioa_num)                               \
({                                                                              \
    ncp_bool_t __enabled = FALSE;                                               \
    ncp_eioas_t *__eioas = (ncp_eioas_t *)((ncp_t *)ncp)->eioaHdl;              \
    if(__eioas && __eioas->eioa[eioa_num])                                      \
    {                                                                           \
        __enabled = !(__eioas->eioa[eioa_num]->disabled);                       \
    }                                                                           \
    __enabled;                                                                  \
})

#endif

#define NCP_EIOA_PORT_TO_INDEX_55xx(hdl, macChan)                      \
({                                                                     \
    ncp_uint32_t   __port_index = 0xFFFF;                              \
    switch(macChan)                                                    \
    {                                                                  \
        case NCP_XGMAC0:                                               \
        case NCP_XGMAC16:                                              \
        case NCP_XGMAC32:                                              \
        case NCP_XGMAC48:                                              \
        case NCP_XGMAC64:                                              \
        case NCP_XGMAC80:                                              \
        case NCP_XGMAC96:                                              \
        case NCP_XGMAC112:                                             \
            __port_index = 0;                                          \
        break;                                                         \
        case NCP_GMAC1:                                                \
        case NCP_GMAC17:                                                \
        case NCP_XGMAC33:                                              \
        case NCP_XGMAC49:                                              \
        case NCP_XGMAC65:                                              \
        case NCP_XGMAC81:                                              \
        case NCP_XGMAC97:                                              \
        case NCP_XGMAC113:                                             \
            __port_index = 1;                                          \
        break;                                                         \
        case NCP_GMAC2:                                                \
        case NCP_GMAC18:                                                \
            __port_index = 2;                                          \
        break;                                                         \
        case NCP_GMAC3:                                                \
        case NCP_GMAC19:                                                \
            __port_index = 3;                                          \
        break;                                                         \
        case NCP_GMAC4:                                               \
        case NCP_GMAC20:                                              \
            __port_index = 4;                                          \
        break;                                                         \
        default:                                                       \
            NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                 \
    }                                                                  \
    __port_index;                                                      \
})


#if !defined(NCP_KERNEL)

#define NCP_EIOA_PORT_VALIDATE_55xx(hdl, port)                         \
({                                                                    \
    ncp_eioas_t *__eioas    = NULL;                                    \
    ncp_eioa_t  *__eioa     = NULL;                                    \
    ncp_port_t  *__ncp_port = NULL;                                    \
    ncp_uint32_t __port_idex;                                          \
    ncp_uint32_t __eioa_idex;                                          \
    __eioas = hdl->eioaHdl;                                            \
    if(__eioas == NULL)                                                \
    {                                                                  \
        NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                     \
    }                                                                  \
    switch(port)                                                       \
    {                                                                  \
        case NCP_XGMAC0:                                               \
        case NCP_XGMAC16:                                              \
        case NCP_XGMAC32:                                              \
        case NCP_XGMAC48:                                              \
        case NCP_XGMAC64:                                              \
        case NCP_XGMAC80:                                              \
        case NCP_XGMAC96:                                              \
        case NCP_XGMAC112:                                             \
        case NCP_GMAC1:                                                \
        case NCP_GMAC17:                                               \
        case NCP_XGMAC33:                                              \
        case NCP_XGMAC49:                                              \
        case NCP_XGMAC65:                                              \
        case NCP_XGMAC81:                                              \
        case NCP_XGMAC97:                                              \
        case NCP_XGMAC113:                                             \
        case NCP_GMAC2:                                                \
        case NCP_GMAC18:                                               \
        case NCP_GMAC3:                                                \
        case NCP_GMAC19:                                               \
        case NCP_GMAC4:                                                \
        case NCP_GMAC20:                                               \
        break;                                                         \
        case NCP_XGMAC8:                                               \
        case NCP_GMAC9:                                                \
        case NCP_GMAC10:                                               \
        case NCP_GMAC11:                                               \
        case NCP_GMAC12:                                               \
            NCP_CALL(NCP_ST_MAC_INVALID_MAC);                          \
        break;                                                         \
        default:                                                       \
            NCP_CALL(NCP_ST_MAC_INVALID_MAC);                          \
        break;                                                         \
    }                                                                  \
    __eioa_idex = NCP_EIOA_TO_INDEX_55xx(port);                       \
    __eioa = __eioas->eioa[__eioa_idex];                              \
    if (__eioa == NULL)                                                \
    {                                                                  \
        NCP_MSG(NCP_MSG_INFO, "port=%d, eioa = NULL\n", port);          \
        NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                     \
    }                                                                  \
    __port_idex = NCP_EIOA_PORT_TO_INDEX_55xx(hdl, port);             \
    __ncp_port = __eioa->NCP_POINTER_ARRAY(port, __port_idex);         \
    if (__ncp_port == NULL)                                            \
    {                                                                  \
        NCP_MSG(NCP_MSG_INFO, "port=%d, port = NULL\n", port);          \
        NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                     \
    }                                                                  \
})

#define NCP_EIOA_PORT_PHYACCESS_55xx(hdl, macChan)                        \
({                                                                     \
    ncp_eioas_t *__eioas    = NULL;                                    \
    ncp_eioa_t  *__eioa     = NULL;                                    \
    ncp_port_t  *__ncp_port = NULL;                                    \
    ncp_uint32_t __port_idex;                                          \
    ncp_uint32_t __eioa_idex;                                          \
    ncp_bool_t __phyaccess;                                            \
    __eioas = hdl->eioaHdl;                                            \
    if(__eioas == NULL)                                                \
    {                                                                  \
        NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                     \
    }                                                                  \
    switch(macChan)                                                       \
    {                                                                  \
        case NCP_XGMAC0:                                               \
        case NCP_XGMAC16:                                              \
        case NCP_XGMAC32:                                              \
        case NCP_XGMAC48:                                              \
        case NCP_XGMAC64:                                              \
        case NCP_XGMAC80:                                              \
        case NCP_XGMAC96:                                              \
        case NCP_XGMAC112:                                             \
        case NCP_GMAC1:                                                \
        case NCP_GMAC17:                                               \
        case NCP_XGMAC33:                                              \
        case NCP_XGMAC49:                                              \
        case NCP_XGMAC65:                                              \
        case NCP_XGMAC81:                                              \
        case NCP_XGMAC97:                                              \
        case NCP_XGMAC113:                                             \
        case NCP_GMAC2:                                                \
        case NCP_GMAC18:                                               \
        case NCP_GMAC3:                                                \
        case NCP_GMAC19:                                               \
        case NCP_GMAC4:                                                \
        case NCP_GMAC20:                                               \
        break;                                                         \
        case NCP_XGMAC8:                                               \
        case NCP_GMAC9:                                                \
        case NCP_GMAC10:                                               \
        case NCP_GMAC11:                                               \
        case NCP_GMAC12:                                               \
            NCP_CALL(NCP_ST_MAC_INVALID_MAC);                          \
        break;                                                         \
        default:                                                       \
            NCP_CALL(NCP_ST_MAC_INVALID_MAC);                          \
        break;                                                         \
    }                                                                  \
    __eioa_idex = NCP_EIOA_TO_INDEX_55xx(macChan);                     \
    __eioa = __eioas->eioa[__eioa_idex];                               \
    if (__eioa == NULL)                                                \
    {                                                                  \
        NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                     \
    }                                                                  \
    __port_idex = NCP_EIOA_PORT_TO_INDEX_55xx(hdl, macChan);           \
    __ncp_port = __eioa->NCP_POINTER_ARRAY(port, __port_idex);         \
    if (__ncp_port == NULL)                                            \
    {                                                                  \
        NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                     \
    }                                                                  \
    if ( (__eioas->noPhyConfig == TRUE) || (__ncp_port->phyAccess == NCP_MAC_CHAN_CONFIG_NONE) )           \
    {                                                                  \
        __phyaccess = FALSE;                                           \
    }                                                                  \
    else                                                               \
    {                                                                  \
        __phyaccess = TRUE;                                            \
    }                                                                  \
    __phyaccess;                                                       \
})

#define NCP_EIOA_PORT_TYPE_55xx(hdl, macChan)                          \
({                                                                     \
    ncp_eioas_t *__eioas    = NULL;                                    \
    ncp_eioa_t  *__eioa     = NULL;                                    \
    ncp_port_t  *__ncp_port = NULL;                                    \
    ncp_uint32_t __port_idex;                                          \
    ncp_uint32_t __eioa_idex;                                          \
    ncp_bool_t __xgmac_flag;                                            \
    __eioas = ((ncp_t *)hdl)->eioaHdl;                                            \
    if(__eioas == NULL)                                                \
    {                                                                  \
        NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                     \
    }                                                                  \
    switch(macChan)                                                       \
    {                                                                  \
        case NCP_XGMAC0:                                               \
        case NCP_XGMAC16:                                              \
        case NCP_XGMAC32:                                              \
        case NCP_XGMAC48:                                              \
        case NCP_XGMAC64:                                              \
        case NCP_XGMAC80:                                              \
        case NCP_XGMAC96:                                              \
        case NCP_XGMAC112:                                             \
        case NCP_GMAC1:                                                \
        case NCP_GMAC17:                                               \
        case NCP_XGMAC33:                                              \
        case NCP_XGMAC49:                                              \
        case NCP_XGMAC65:                                              \
        case NCP_XGMAC81:                                              \
        case NCP_XGMAC97:                                              \
        case NCP_XGMAC113:                                             \
        case NCP_GMAC2:                                                \
        case NCP_GMAC18:                                               \
        case NCP_GMAC3:                                                \
        case NCP_GMAC19:                                               \
        case NCP_GMAC4:                                                \
        case NCP_GMAC20:                                               \
        break;                                                         \
        default:                                                       \
            NCP_CALL(NCP_ST_MAC_INVALID_MAC);                          \
        break;                                                         \
    }                                                                  \
    __eioa_idex = NCP_EIOA_TO_INDEX_55xx(macChan);                     \
    __eioa = __eioas->eioa[__eioa_idex];                               \
    if (__eioa == NULL)                                                \
    {                                                                  \
        NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                     \
    }                                                                  \
    __port_idex = NCP_EIOA_PORT_TO_INDEX_55xx(hdl, macChan);           \
    __ncp_port = __eioa->NCP_POINTER_ARRAY(port, __port_idex);         \
    if (__ncp_port == NULL)                                            \
    {                                                                  \
        NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                     \
    }                                                                  \
    if ((__ncp_port->chanType == NCP_MAC_CHAN_CONFIG_XFI) ||           \
        (__ncp_port->chanType == NCP_MAC_CHAN_CONFIG_XAUI) ||          \
        (__ncp_port->chanType == NCP_MAC_CHAN_CONFIG_SFI) ||           \
        (__ncp_port->chanType == NCP_MAC_CHAN_CONFIG_10GBASEKR) ||     \
        (__ncp_port->chanType == NCP_MAC_CHAN_CONFIG_XGMII))           \
    {                                                                  \
        __xgmac_flag = TRUE;                                           \
    }                                                                  \
    else                                                               \
    {                                                                  \
        __xgmac_flag = FALSE;                                          \
    }                                                                  \
    __xgmac_flag;                                                      \
})


#define NCP_EIOA_TO_START_EXTERNAL_PORT_55xx(eioa_num)                             \
    ({                                                                        \
        ncp_uint32_t __start_port = NCP_XGMAC0;                               \
        switch(eioa_num)                                                      \
        {                                                                     \
            case NCP_EIOA0:                                                   \
                __start_port = NCP_XGMAC0;                                    \
            break;                                                            \
            case NCP_EIOA1:                                                   \
                __start_port = NCP_XGMAC16;                                   \
            break;                                                            \
            case NCP_EIOA2:                                                   \
                __start_port = NCP_XGMAC32;                                   \
            break;                                                            \
            case NCP_EIOA3:                                                   \
                __start_port = NCP_XGMAC48;                                   \
            break;                                                            \
            case NCP_EIOA4:                                                   \
                __start_port = NCP_XGMAC64;                                   \
            break;                                                            \
            case NCP_EIOA5:                                                   \
                __start_port = NCP_XGMAC80;                                   \
            break;                                                            \
            case NCP_EIOA6:                                                   \
                __start_port = NCP_XGMAC96;                                   \
            break;                                                            \
            case NCP_EIOA7:                                                   \
                __start_port = NCP_XGMAC112;                                  \
            break;                                                            \
        }                                                                     \
    __start_port;                                                             \
    })

#define NCP_EIOA_TO_END_EXTERNAL_PORT_55xx(eioa_num)                          \
    ({                                                                        \
        ncp_uint32_t __end_port = NCP_GMAC4;                                  \
        switch(eioa_num)                                                      \
        {                                                                     \
            case NCP_EIOA0:                                                   \
                __end_port = NCP_GMAC4;                                       \
            break;                                                            \
            case NCP_EIOA1:                                                   \
                __end_port = NCP_GMAC20;                                      \
            break;                                                            \
            case NCP_EIOA2:                                                   \
                __end_port = NCP_XGMAC33;                                     \
            break;                                                            \
            case NCP_EIOA3:                                                   \
                __end_port = NCP_XGMAC49;                                     \
            break;                                                            \
            case NCP_EIOA4:                                                   \
                __end_port = NCP_XGMAC65;                                     \
            break;                                                            \
            case NCP_EIOA5:                                                   \
                __end_port = NCP_XGMAC81;                                     \
            break;                                                            \
            case NCP_EIOA6:                                                   \
                __end_port = NCP_XGMAC97;                                     \
            break;                                                            \
            case NCP_EIOA7:                                                   \
                __end_port = NCP_XGMAC113;                                    \
            break;                                                            \
        }                                                                     \
    __end_port;                                                               \
    })

#endif

#define NCP_EIOA_EXTERNAL_TO_INTERNAL_PORT_55xx(external_port)   \
    ({                                                      \
        ncp_uint8_t __internal_port = 0;                    \
        switch((external_port))                             \
        {                                                   \
        case NCP_XGMAC0:                                    \
        case NCP_XGMAC16:                                   \
        case NCP_GMAC32:                                    \
        case NCP_GMAC33:                                    \
        case NCP_GMAC48:                                    \
        case NCP_GMAC49:                                    \
        case NCP_GMAC64:                                    \
        case NCP_GMAC65:                                    \
        case NCP_GMAC80:                                    \
        case NCP_GMAC81:                                    \
        case NCP_GMAC96:                                    \
        case NCP_GMAC97:                                    \
        case NCP_GMAC112:                                   \
        case NCP_GMAC113:                                   \
            __internal_port = 0;                            \
            break;                                          \
        case NCP_GMAC1:                                     \
        case NCP_GMAC2:                                     \
        case NCP_GMAC3:                                     \
        case NCP_GMAC4:                                     \
            __internal_port = (external_port) - NCP_GMAC1;  \
            break;                                          \
        case NCP_GMAC17:                                    \
        case NCP_GMAC18:                                    \
        case NCP_GMAC19:                                    \
        case NCP_GMAC20:                                    \
            __internal_port = (external_port) - NCP_GMAC17; \
            break;                                          \
        default:                                            \
            break;                                          \
        }                                                   \
        __internal_port;                                    \
    })

#if !defined(NCP_KERNEL)

#define NCP_EIOA_EXTERNAL_PORT_TO_DEST_INST_55xx(external_port)  (external_port)

#define NCP_EIOA_EXTERNAL_PORT_TO_SLOT_55xx(external_port)  \
    ({                                                      \
        ncp_uint8_t __slot = 0;                             \
        switch((external_port))                             \
        {                                                   \
        case NCP_XGMAC0:                                    \
        case NCP_XGMAC16:                                   \
        case NCP_GMAC32:                                    \
        case NCP_GMAC48:                                    \
        case NCP_GMAC64:                                    \
        case NCP_GMAC80:                                    \
        case NCP_GMAC96:                                    \
        case NCP_GMAC112:                                   \
            __slot = 0;                                     \
            break;                                          \
        case NCP_GMAC1:                                     \
        case NCP_GMAC2:                                     \
        case NCP_GMAC3:                                     \
        case NCP_GMAC4:                                     \
        case NCP_GMAC17:                                    \
        case NCP_GMAC18:                                    \
        case NCP_GMAC19:                                    \
        case NCP_GMAC20:                                    \
        case NCP_GMAC33:                                    \
        case NCP_GMAC49:                                    \
        case NCP_GMAC65:                                    \
        case NCP_GMAC81:                                    \
        case NCP_GMAC97:                                    \
        case NCP_GMAC113:                                   \
            __slot = 1;                                     \
            break;                                          \
        default:                                            \
            break;                                          \
        }                                                   \
        __slot;                                             \
    })

#define NCP_EIOA_EXTERNAL_PORT_IS_NATIVE_DOMAIN(external_port)  \
    ({                                                      \
        ncp_bool_t __nativeDomain = FALSE;                  \
        switch((external_port))                             \
        {                                                   \
        case NCP_XGMAC0:                                    \
        case NCP_GMAC1:                                     \
        case NCP_GMAC2:                                     \
        case NCP_GMAC3:                                     \
        case NCP_GMAC4:                                     \
        case NCP_XGMAC16:                                   \
        case NCP_GMAC17:                                    \
        case NCP_GMAC18:                                    \
        case NCP_GMAC19:                                    \
        case NCP_GMAC20:                                    \
            __nativeDomain = TRUE;                          \
            break;                                          \
        default:                                            \
            break;                                          \
        }                                                   \
        __nativeDomain;                                     \
    })

#define NCP_EEPTSP_55xx(external_port) NCP_EIOA_EXTERNAL_PORT_TO_SWITCH_PORT(external_port)
#define NCP_EIOA_EXTERNAL_PORT_TO_SWITCH_PORT(external_port)  \
    ({                                                      \
        ncp_uint8_t __sport = 0;                            \
        switch((external_port))                             \
        {                                                   \
        case NCP_GMAC0:                                     \
            __sport = 0;                                    \
            break;                                          \
        case NCP_GMAC1:                                     \
            __sport = 1;                                    \
            break;                                          \
        case NCP_GMAC2:                                     \
            __sport = 2;                                    \
            break;                                          \
        case NCP_GMAC3:                                     \
            __sport = 3;                                    \
            break;                                          \
        case NCP_GMAC4:                                     \
            __sport = 4;                                    \
            break;                                          \
        case NCP_GMAC16:                                    \
            __sport = 5;                                    \
            break;                                          \
        case NCP_GMAC17:                                    \
            __sport = 6;                                    \
            break;                                          \
        case NCP_GMAC18:                                    \
            __sport = 7;                                    \
            break;                                          \
        case NCP_GMAC19:                                    \
            __sport = 8;                                    \
            break;                                          \
        case NCP_GMAC20:                                    \
            __sport = 9;                                    \
            break;                                          \
        case NCP_GMAC32:                                    \
            __sport = 10;                                   \
            break;                                          \
        case NCP_GMAC33:                                    \
            __sport = 11;                                   \
            break;                                          \
        case NCP_GMAC48:                                    \
            __sport = 12;                                   \
            break;                                          \
        case NCP_GMAC49:                                    \
            __sport = 13;                                   \
            break;                                          \
        case NCP_GMAC64:                                    \
            __sport = 14;                                   \
            break;                                          \
        case NCP_GMAC65:                                    \
            __sport = 15;                                   \
            break;                                          \
        case NCP_GMAC80:                                    \
            __sport = 16;                                   \
            break;                                          \
        case NCP_GMAC81:                                    \
            __sport = 17;                                   \
            break;                                          \
        case NCP_GMAC96:                                    \
            __sport = 18;                                   \
            break;                                          \
        case NCP_GMAC97:                                    \
            __sport = 19;                                   \
            break;                                          \
        case NCP_GMAC112:                                   \
            __sport = 20;                                   \
            break;                                          \
        case NCP_GMAC113:                                   \
            __sport = 21;                                   \
            break;                                          \
        default:                                            \
            break;                                          \
        }                                                   \
        __sport;                                            \
    })

#define NCP_ESPTEP_55xx(switch_port) NCP_EIOA_SWITCH_PORT_TO_EXTERNAL_PORT(switch_port)
#define NCP_EIOA_SWITCH_PORT_TO_EXTERNAL_PORT(switch_port)  \
    ({                                                      \
        ncp_macChan_t __macChan = 0xff;                     \
        switch((switch_port))                               \
        {                                                   \
        case 0:                                             \
            __macChan = NCP_GMAC0;                          \
            break;                                          \
        case 1:                                             \
            __macChan = NCP_GMAC1;                          \
            break;                                          \
        case 2:                                             \
            __macChan = NCP_GMAC2;                          \
            break;                                          \
        case 3:                                             \
            __macChan = NCP_GMAC3;                          \
            break;                                          \
        case 4:                                             \
            __macChan = NCP_GMAC4;                          \
            break;                                          \
        case 5:                                             \
            __macChan = NCP_GMAC16;                         \
            break;                                          \
        case 6:                                             \
            __macChan = NCP_GMAC17;                         \
            break;                                          \
        case 7:                                             \
            __macChan = NCP_GMAC18;                         \
            break;                                          \
        case 8:                                             \
            __macChan = NCP_GMAC19;                         \
            break;                                          \
        case 9:                                             \
            __macChan = NCP_GMAC20;                         \
            break;                                          \
        case 10:                                            \
            __macChan = NCP_GMAC32;                         \
            break;                                          \
        case 11:                                            \
            __macChan = NCP_GMAC33;                         \
            break;                                          \
        case 12:                                            \
            __macChan = NCP_GMAC48;                         \
            break;                                          \
        case 13:                                            \
            __macChan = NCP_GMAC49;                         \
            break;                                          \
        case 14:                                            \
            __macChan = NCP_GMAC64;                         \
            break;                                          \
        case 15:                                            \
            __macChan = NCP_GMAC65;                         \
            break;                                          \
        case 16:                                            \
            __macChan = NCP_GMAC80;                         \
            break;                                          \
        case 17:                                            \
            __macChan = NCP_GMAC81;                         \
            break;                                          \
        case 18:                                            \
            __macChan = NCP_GMAC96;                         \
            break;                                          \
        case 19:                                            \
            __macChan = NCP_GMAC97;                         \
            break;                                          \
        case 20:                                            \
            __macChan = NCP_GMAC112;                        \
            break;                                          \
        case 21:                                            \
            __macChan = NCP_GMAC113;                        \
            break;                                          \
        default:                                            \
            NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);      \
        }                                                   \
        __macChan;                                          \
    })

#define NCP_EIOA_IPP_PORT_TO_REGION_ID_55xx(port)           \
    ({                                                      \
        ncp_uint32_t __regionId = 0;                        \
        switch((port))                                      \
        {                                                   \
        case NCP_XGMAC0:                                    \
            __regionId = NCP_REGION_EIOA0_IPP0;             \
            break;                                          \
        case NCP_GMAC1:                                     \
        case NCP_GMAC2:                                     \
        case NCP_GMAC3:                                     \
        case NCP_GMAC4:                                     \
            __regionId = NCP_REGION_EIOA0_IPP1;             \
            break;                                          \
        case NCP_XGMAC16:                                   \
            __regionId = NCP_REGION_EIOA1_IPP0;             \
            break;                                          \
        case NCP_GMAC17:                                    \
        case NCP_GMAC18:                                    \
        case NCP_GMAC19:                                    \
        case NCP_GMAC20:                                    \
            __regionId = NCP_REGION_EIOA1_IPP1;             \
            break;                                          \
        case NCP_XGMAC32:                                   \
            __regionId = NCP_REGION_EIOA2_IPP0;             \
            break;                                          \
        case NCP_XGMAC33:                                   \
            __regionId = NCP_REGION_EIOA2_IPP1;             \
            break;                                          \
        case NCP_XGMAC48:                                   \
            __regionId = NCP_REGION_EIOA3_IPP0;             \
            break;                                          \
        case NCP_XGMAC49:                                   \
            __regionId = NCP_REGION_EIOA3_IPP1;             \
            break;                                          \
        case NCP_XGMAC64:                                   \
            __regionId = NCP_REGION_EIOA4_IPP0;             \
            break;                                          \
        case NCP_XGMAC65:                                   \
            __regionId = NCP_REGION_EIOA4_IPP1;             \
            break;                                          \
        case NCP_XGMAC80:                                   \
            __regionId = NCP_REGION_EIOA5_IPP0;             \
            break;                                          \
        case NCP_XGMAC81:                                   \
            __regionId = NCP_REGION_EIOA5_IPP1;             \
            break;                                          \
        case NCP_XGMAC96:                                   \
            __regionId = NCP_REGION_EIOA6_IPP0;             \
            break;                                          \
        case NCP_XGMAC97:                                   \
            __regionId = NCP_REGION_EIOA6_IPP1;             \
            break;                                          \
        case NCP_XGMAC112:                                  \
            __regionId = NCP_REGION_EIOA7_IPP0;             \
            break;                                          \
        case NCP_XGMAC113:                                  \
            __regionId = NCP_REGION_EIOA7_IPP1;             \
            break;                                          \
        default:                                            \
            __regionId = 0;                                 \
            break;                                          \
        }                                                   \
        __regionId;                                         \
    })

#define NCP_EIOA_EPP_PORT_TO_REGION_ID_55xx(port)           \
    ({                                                      \
        ncp_uint32_t __regionId = 0;                        \
        switch((port))                                      \
        {                                                   \
        case NCP_XGMAC0:                                    \
            __regionId = NCP_REGION_EIOA0_EPP0;             \
            break;                                          \
        case NCP_GMAC1:                                     \
        case NCP_GMAC2:                                     \
        case NCP_GMAC3:                                     \
        case NCP_GMAC4:                                     \
            __regionId = NCP_REGION_EIOA0_EPP1;             \
            break;                                          \
        case NCP_XGMAC16:                                   \
            __regionId = NCP_REGION_EIOA1_EPP0;             \
            break;                                          \
        case NCP_GMAC17:                                    \
        case NCP_GMAC18:                                    \
        case NCP_GMAC19:                                    \
        case NCP_GMAC20:                                    \
            __regionId = NCP_REGION_EIOA1_EPP1;             \
            break;                                          \
        case NCP_XGMAC32:                                   \
            __regionId = NCP_REGION_EIOA2_EPP0;             \
            break;                                          \
        case NCP_XGMAC33:                                   \
            __regionId = NCP_REGION_EIOA2_EPP1;             \
            break;                                          \
        case NCP_XGMAC48:                                   \
            __regionId = NCP_REGION_EIOA3_EPP0;             \
            break;                                          \
        case NCP_XGMAC49:                                   \
            __regionId = NCP_REGION_EIOA3_EPP1;             \
            break;                                          \
        case NCP_XGMAC64:                                   \
            __regionId = NCP_REGION_EIOA4_EPP0;             \
            break;                                          \
        case NCP_XGMAC65:                                   \
            __regionId = NCP_REGION_EIOA4_EPP1;             \
            break;                                          \
        case NCP_XGMAC80:                                   \
            __regionId = NCP_REGION_EIOA5_EPP0;             \
            break;                                          \
        case NCP_XGMAC81:                                   \
            __regionId = NCP_REGION_EIOA5_EPP1;             \
            break;                                          \
        case NCP_XGMAC96:                                   \
            __regionId = NCP_REGION_EIOA6_EPP0;             \
            break;                                          \
        case NCP_XGMAC97:                                   \
            __regionId = NCP_REGION_EIOA6_EPP1;             \
            break;                                          \
        case NCP_XGMAC112:                                  \
            __regionId = NCP_REGION_EIOA7_EPP0;             \
            break;                                          \
        case NCP_XGMAC113:                                  \
            __regionId = NCP_REGION_EIOA7_EPP1;             \
            break;                                          \
        default:                                            \
            break;                                          \
        }                                                   \
        __regionId;                                         \
    })

/* Note: These values need to match with ASE values */
#define NCP_EIOA_POLICER_BP_ID_BASE_55xx(eioa)       (1 + (16 * (eioa)))

#define NCP_EIOA_QBB_PAUSE_BP_ID_BASE_55xx(port)                                     \
({                                                                              \
    ncp_uint32_t base = 0;                                                      \
    ncp_uint8_t eioa_num = NCP_EIOA_TO_INDEX_55xx((port));                      \
                                                                                \
    if(eioa_num == NCP_EIOA0 || eioa_num == NCP_EIOA1)                          \
    {                                                                           \
        base = 129 + (8 * NCP_EEPTSP_55xx(port));                               \
    }                                                                           \
    else                                                                        \
    {                                                                           \
        base = 220 + (8 * (NCP_EEPTSP_55xx(port) - 10));                        \
    }                                                                           \
    base;                                                                       \
})

#define NCP_EIOA_REGULAR_PAUSE_BP_ID_55xx(port)                                      \
({                                                                              \
    ncp_uint32_t base = 0;                                                      \
    ncp_uint8_t eioa_num = NCP_EIOA_TO_INDEX_55xx((port));                      \
                                                                                \
    if(eioa_num == NCP_EIOA0 || eioa_num == NCP_EIOA1)                          \
    {                                                                           \
        base = 209 + NCP_EEPTSP_55xx(port);                                     \
    }                                                                           \
    else                                                                        \
    {                                                                           \
        base = 316 + NCP_EEPTSP_55xx(port) - 10;                                \
    }                                                                           \
    base;                                                                       \
})

#define NCP_EIOA_ALL_POLICER_BP_ID_55xx              (219)

#define NCP_EIOA_BP_ID_TO_ENGINE_55xx(engine, bpId)                                  \
({                                                                              \
    ncp_engine_type_t __engine = (engine);                                      \
    if(engine == ncp_engine_eioa0)                                              \
    {                                                                           \
        if((bpId) >= NCP_EIOA_POLICER_BP_ID_BASE(NCP_EIOA0) &&                  \
           (bpId) <= (NCP_EIOA_POLICER_BP_ID_BASE(NCP_EIOA7) + 16))             \
        {                                                                       \
            __engine = NCP_EIOA_TO_COW_ENGINE((bpId) >> 4);                     \
        }                                                                       \
        else if((bpId) >= NCP_EIOA_QBB_PAUSE_BP_ID_BASE(NCP_GMAC0) &&           \
                (bpId) <= (NCP_EIOA_QBB_PAUSE_BP_ID_BASE(NCP_GMAC4) + 8))       \
        {                                                                       \
            __engine = ncp_engine_eioa0;                                        \
        }                                                                       \
        else if((bpId) >= NCP_EIOA_QBB_PAUSE_BP_ID_BASE(NCP_GMAC16) &&          \
                (bpId) <= (NCP_EIOA_QBB_PAUSE_BP_ID_BASE(NCP_GMAC20) + 8))      \
        {                                                                       \
            __engine = ncp_engine_eioa1;                                        \
        }                                                                       \
        else if((bpId) >= NCP_EIOA_REGULAR_PAUSE_BP_ID(NCP_GMAC0) &&            \
                (bpId) <= NCP_EIOA_REGULAR_PAUSE_BP_ID(NCP_GMAC4))              \
        {                                                                       \
            __engine = ncp_engine_eioa0;                                        \
        }                                                                       \
        else if((bpId) >= NCP_EIOA_REGULAR_PAUSE_BP_ID(NCP_GMAC16) &&           \
                (bpId) <= NCP_EIOA_REGULAR_PAUSE_BP_ID(NCP_GMAC20))             \
        {                                                                       \
            __engine = ncp_engine_eioa1;                                        \
        }                                                                       \
        else if((bpId) >= NCP_EIOA_QBB_PAUSE_BP_ID_BASE(NCP_GMAC32) &&          \
                (bpId) <= (NCP_EIOA_QBB_PAUSE_BP_ID_BASE(NCP_GMAC33) + 8))      \
        {                                                                       \
            __engine = ncp_engine_eioa2;                                        \
        }                                                                       \
        else if((bpId) >= NCP_EIOA_QBB_PAUSE_BP_ID_BASE(NCP_GMAC48) &&          \
                (bpId) <= (NCP_EIOA_QBB_PAUSE_BP_ID_BASE(NCP_GMAC49) + 8))      \
        {                                                                       \
            __engine = ncp_engine_eioa3;                                        \
        }                                                                       \
        else if((bpId) >= NCP_EIOA_QBB_PAUSE_BP_ID_BASE(NCP_GMAC64) &&          \
                (bpId) <= (NCP_EIOA_QBB_PAUSE_BP_ID_BASE(NCP_GMAC65) + 8))      \
        {                                                                       \
            __engine = ncp_engine_eioa4;                                        \
        }                                                                       \
        else if((bpId) >= NCP_EIOA_QBB_PAUSE_BP_ID_BASE(NCP_GMAC80) &&          \
                (bpId) <= (NCP_EIOA_QBB_PAUSE_BP_ID_BASE(NCP_GMAC81) + 8))      \
        {                                                                       \
            __engine = ncp_engine_eioa5;                                        \
        }                                                                       \
        else if((bpId) >= NCP_EIOA_QBB_PAUSE_BP_ID_BASE(NCP_GMAC96) &&          \
                (bpId) <= (NCP_EIOA_QBB_PAUSE_BP_ID_BASE(NCP_GMAC97) + 8))      \
        {                                                                       \
            __engine = ncp_engine_eioa6;                                        \
        }                                                                       \
        else if((bpId) >= NCP_EIOA_QBB_PAUSE_BP_ID_BASE(NCP_GMAC112) &&         \
                (bpId) <= (NCP_EIOA_QBB_PAUSE_BP_ID_BASE(NCP_GMAC113) + 8))     \
        {                                                                       \
            __engine = ncp_engine_eioa7;                                        \
        }                                                                       \
        else if((bpId) >= NCP_EIOA_REGULAR_PAUSE_BP_ID(NCP_GMAC32) &&           \
                (bpId) <= NCP_EIOA_REGULAR_PAUSE_BP_ID(NCP_GMAC33))             \
        {                                                                       \
            __engine = ncp_engine_eioa2;                                        \
        }                                                                       \
        else if((bpId) >= NCP_EIOA_REGULAR_PAUSE_BP_ID(NCP_GMAC48) &&           \
                (bpId) <= NCP_EIOA_REGULAR_PAUSE_BP_ID(NCP_GMAC49))             \
        {                                                                       \
            __engine = ncp_engine_eioa3;                                        \
        }                                                                       \
        else if((bpId) >= NCP_EIOA_REGULAR_PAUSE_BP_ID(NCP_GMAC64) &&           \
                (bpId) <= NCP_EIOA_REGULAR_PAUSE_BP_ID(NCP_GMAC65))             \
        {                                                                       \
            __engine = ncp_engine_eioa4;                                        \
        }                                                                       \
        else if((bpId) >= NCP_EIOA_REGULAR_PAUSE_BP_ID(NCP_GMAC80) &&           \
                (bpId) <= NCP_EIOA_REGULAR_PAUSE_BP_ID(NCP_GMAC81))             \
        {                                                                       \
            __engine = ncp_engine_eioa5;                                        \
        }                                                                       \
        else if((bpId) >= NCP_EIOA_REGULAR_PAUSE_BP_ID(NCP_GMAC96) &&           \
                (bpId) <= NCP_EIOA_REGULAR_PAUSE_BP_ID(NCP_GMAC97))             \
        {                                                                       \
            __engine = ncp_engine_eioa6;                                        \
        }                                                                       \
        else if((bpId) >= NCP_EIOA_REGULAR_PAUSE_BP_ID(NCP_GMAC112) &&          \
                (bpId) <= NCP_EIOA_REGULAR_PAUSE_BP_ID(NCP_GMAC113))            \
        {                                                                       \
            __engine = ncp_engine_eioa7;                                        \
        }                                                                       \
    }                                                                           \
    __engine;                                                                   \
})

#define NCP_EIOA_BP_ID_IS_POLICER_55xx(bpId)                                         \
({                                                                              \
    ncp_bool_t __policer = FALSE;                                               \
    if((bpId) >= NCP_EIOA_POLICER_BP_ID_BASE(0) &&                              \
       (bpId) < NCP_EIOA_QBB_PAUSE_BP_ID_BASE(NCP_GMAC0))                       \
    {                                                                           \
        __policer = TRUE;                                                       \
    }                                                                           \
    __policer;                                                                  \
})

#define NCP_EIOA_QBB_PORT_BP_OFFSET(external_port)                              \
    (NCP_EIOA_CORE_BP_CFG_REGISTERS_BASE +                                      \
     NCP_BP_CFG_REGISTERS_S0_PORT_BP_OFFSET_PORT +                              \
    (NCP_EIOA_EXTERNAL_PORT_TO_SLOT_55xx(external_port) * 0x100) +              \
    (NCP_EIOA_EXTERNAL_TO_INTERNAL_PORT_55xx(external_port) * 4))

#define NCP_EIOA_QBB_TASK_QUEUE_BP_OFFSET(external_port)                        \
    (NCP_EIOA_CORE_BP_CFG_REGISTERS_BASE +                                      \
     NCP_BP_CFG_REGISTERS_S0_RX_QBB_BP_PORT_BASE(0) +                           \
    (NCP_EIOA_EXTERNAL_PORT_TO_SLOT_55xx(external_port) * 0x1000) +             \
    (NCP_EIOA_EXTERNAL_TO_INTERNAL_PORT_55xx(external_port) * 0x100))

#define NCP_EIOA_CORE_MACSEC_CFG_REG_OFFSET(port) \
    NCP_EIOA_CORE_GEN_CFG_REGISTERS_BASE + \
    (NCP_EIOA_EXTERNAL_PORT_TO_SLOT_55xx(port) * 0x00010000) + \
    (NCP_EIOA_EXTERNAL_TO_INTERNAL_PORT_55xx(port) * 0x00001000) + \
    NCP_5600_S0_PORT_GEN_CFG_MACSEC_CFG

ncp_st_t
ncp_eioa_config_55xx(
    ncp_t         *ncp,
    ncp_map_t     *map);

ncp_st_t
ncp_eioa_destroy_55xx(ncp_t *ncp);

ncp_st_t
ncp_eioa_warm_restart_55xx(ncp_t *ncp);

ncp_st_t
ncp_ueioa_config(
    ncp_t         *ncp,
    ncp_map_t     *map);

ncp_st_t
ncp_ueioa_destroy(ncp_t *ncp);

ncp_st_t
ncp_ueioa_warm_restart(ncp_t *ncp);

ncp_st_t
ncp_eioa_ports_enable(
    ncp_t         *ncp,
    ncp_map_t     *map);

ncp_st_t
ncp_eioa_get_all_port_maps(ncp_t* ncp, ncp_map_t *eioaMap, ncp_map_t **portMaps, ncp_uint32_t noPortMaps, ncp_uint32_t* noPortMapsFound);

#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _NCP_EIOA_CONFIG_55XX_H_ */

