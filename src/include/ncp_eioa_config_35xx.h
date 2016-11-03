/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


#ifndef _NCP_EIOA_CONFIG_35XX_H_
#define _NCP_EIOA_CONFIG_35XX_H_

#ifdef __cplusplus
extern "C" {
#endif

#define NOT_DONE 1
#define NCP_GMAC_PORT(n) (0x00000300 + (0xC0 * (n)))

#define NCP_EIOA_NEMAC_EXTERNAL_PORT_TO_REGION_ID(external_port, xgmac_flag) \
    ({                                                                       \
        ncp_uint32_t __nemac_region = 0;                                     \
        if (xgmac_flag == TRUE)                                              \
        {                                                                    \
            switch(external_port)                                            \
            {                                                                \
                case NCP_XGMAC1:                                             \
                case NCP_XGMAC0:  /* handle legacy 34xx ports */             \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA0_NEMAC0;  \
                break;                                                       \
                case NCP_XGMAC9:                                             \
                case NCP_XGMAC8:  /* handle legacy 34xx ports */             \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA0_NEMAC1;  \
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
                case NCP_GMAC1:                                              \
                case NCP_GMAC2:                                              \
                case NCP_GMAC3:                                              \
                case NCP_GMAC4:                                              \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA0_NEMAC0;  \
                break;                                                       \
                case NCP_GMAC9:                                              \
                case NCP_GMAC10:                                             \
                case NCP_GMAC11:                                             \
                case NCP_GMAC12:                                             \
                    __nemac_region = (ncp_uint32_t)NCP_REGION_EIOA0_NEMAC1;  \
                break;                                                       \
                default:                                                     \
                    __nemac_region = (ncp_uint32_t)0;                        \
                break;                                                       \
            }                                                                \
        }                                                                    \
        __nemac_region;                                                      \
    })

#define NCP_EIOA_EXTERNAL_TO_INTERNAL_PORT_35xx(external_port)   \
    ({                                                      \
        ncp_uint8_t __internal_port = 0;                    \
        switch((external_port))                             \
        {                                                   \
        case NCP_GMAC1:                                     \
        case NCP_GMAC2:                                     \
        case NCP_GMAC3:                                     \
        case NCP_GMAC4:                                     \
            __internal_port = (external_port) - NCP_GMAC1;  \
            break;                                          \
        case NCP_GMAC9:                                     \
        case NCP_GMAC10:                                    \
        case NCP_GMAC11:                                    \
        case NCP_GMAC12:                                    \
            __internal_port = (external_port) - NCP_GMAC9;  \
            break;                                          \
        default:                                            \
            break;                                          \
        }                                                   \
        __internal_port;                                    \
    })

#if !defined(NCP_KERNEL)
#define NCP_EIOA_NEMAC_UCAST_OFFSET(external_port, xgmac_flag)               \
    ({                                                                       \
        ncp_uint32_t __cr_off = 0;                                           \
        if (xgmac_flag == TRUE)                                              \
        {                                                                    \
            switch(external_port)                                            \
            {                                                                \
            case NCP_XGMAC1:                                                 \
            __cr_off = (ncp_uint32_t)NCP_NEMAC0_XGMAC_BASE;                  \
            __cr_off += (ncp_uint32_t)NCP_NEMAC0_XGMAC_UCAST_MASK_LOWER;     \
            break;                                                           \
            case NCP_XGMAC9:                                                 \
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
            case NCP_GMAC1:                                                  \
            __cr_off=(ncp_uint32_t)NCP_NEMAC0_GMAC_BASE(0);                  \
            __cr_off += (ncp_uint32_t)NCP_NEMAC0_GMAC_UCAST_MASK_LOWER;      \
            break;                                                           \
            case NCP_GMAC2:                                                  \
            __cr_off=(ncp_uint32_t)NCP_NEMAC0_GMAC_BASE(1);                  \
            __cr_off += (ncp_uint32_t)NCP_NEMAC0_GMAC_UCAST_MASK_LOWER;      \
            break;                                                           \
            case NCP_GMAC3:                                                  \
            __cr_off=(ncp_uint32_t)NCP_NEMAC0_GMAC_BASE(2);                  \
            __cr_off += (ncp_uint32_t)NCP_NEMAC0_GMAC_UCAST_MASK_LOWER;      \
            break;                                                           \
            case NCP_GMAC4:                                                  \
            __cr_off=(ncp_uint32_t)NCP_NEMAC0_GMAC_BASE(3);                  \
            __cr_off += (ncp_uint32_t)NCP_NEMAC0_GMAC_UCAST_MASK_LOWER;      \
            break;                                                           \
            case NCP_GMAC9:                                                  \
            __cr_off=(ncp_uint32_t)NCP_NEMAC1_GMAC_BASE(0);                  \
            __cr_off += (ncp_uint32_t)NCP_NEMAC1_GMAC_UCAST_MASK_LOWER;      \
            break;                                                           \
            case NCP_GMAC10:                                                 \
            __cr_off=(ncp_uint32_t)NCP_NEMAC1_GMAC_BASE(1);                  \
            __cr_off += (ncp_uint32_t)NCP_NEMAC1_GMAC_UCAST_MASK_LOWER;      \
            break;                                                           \
            case NCP_GMAC11:                                                 \
            __cr_off=(ncp_uint32_t)NCP_NEMAC1_GMAC_BASE(2);                  \
            __cr_off += (ncp_uint32_t)NCP_NEMAC1_GMAC_UCAST_MASK_LOWER;      \
            break;                                                           \
            case NCP_GMAC12:                                                 \
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
            case NCP_XGMAC1:                                                 \
            __cr_off=(ncp_uint32_t)NCP_NEMAC0_XGMAC_BASE + 4 * mac_cr;       \
            break;                                                           \
            case NCP_XGMAC9:                                                 \
            __cr_off=(ncp_uint32_t)NCP_NEMAC1_XGMAC_BASE + 4 * mac_cr;       \
            break;                                                           \
            default:                                                         \
            __cr_off= 0;                                                     \
            break;                                                           \
            }                                                                \
        }                                                                    \
        else                                                                 \
        {                                                                    \
            switch(external_port)                                            \
            {                                                                \
            case NCP_GMAC1:                                                  \
            __cr_off=(ncp_uint32_t)NCP_NEMAC0_GMAC_BASE(0);                  \
            __cr_off += 4 * mac_cr;                                          \
            break;                                                           \
            case NCP_GMAC2:                                                  \
            __cr_off=(ncp_uint32_t)NCP_NEMAC0_GMAC_BASE(1);                  \
            __cr_off += 4 * mac_cr;                                          \
            break;                                                           \
            case NCP_GMAC3:                                                  \
            __cr_off=(ncp_uint32_t)NCP_NEMAC0_GMAC_BASE(2);                  \
            __cr_off += 4 * mac_cr;                                          \
            break;                                                           \
            case NCP_GMAC4:                                                  \
            __cr_off=(ncp_uint32_t)NCP_NEMAC0_GMAC_BASE(3);                  \
            __cr_off += 4 * mac_cr;                                          \
            break;                                                           \
            case NCP_GMAC9:                                                  \
            __cr_off=(ncp_uint32_t)NCP_NEMAC1_GMAC_BASE(0);                  \
            __cr_off += 4 * mac_cr;                                          \
            break;                                                           \
            case NCP_GMAC10:                                                 \
            __cr_off=(ncp_uint32_t)NCP_NEMAC1_GMAC_BASE(1);                  \
            __cr_off += 4 * mac_cr;                                          \
            break;                                                           \
            case NCP_GMAC11:                                                 \
            __cr_off=(ncp_uint32_t)NCP_NEMAC1_GMAC_BASE(2);                  \
            __cr_off += 4 * mac_cr;                                          \
            break;                                                           \
            case NCP_GMAC12:                                                 \
            __cr_off=(ncp_uint32_t)NCP_NEMAC1_GMAC_BASE(3);                  \
            __cr_off += 4 * mac_cr;                                          \
            break;                                                           \
            default:                                                         \
            __cr_off= 0;                                                     \
            break;                                                           \
            }                                                                \
        }                                                                    \
        __cr_off;                                                            \
    })

#define NCP_EIOA_CORE_EXTERNAL_PORT_TO_REGION_ID(external_port) \
    ({                                                      \
        ncp_uint32_t __regionId =  NCP_REGION_EIOA_CORE(0); \
        __regionId;                                         \
    })

#define NCP_EIOA_CORE_EIOA_NUM_TO_REGION_ID(eioa_num)       \
    ({                                                      \
        ncp_uint32_t __regionId =  NCP_REGION_EIOA_CORE(0); \
        __regionId;                                         \
    })

#endif

#define NCP_EIOA_TO_INDEX_35xx(macChan)                                \
    ({                                                                 \
        ncp_uint32_t   __eioa_index = NCP_EIOA0;                       \
        __eioa_index;                                                  \
    })

#define NCP_EIOA_PORT_TO_INDEX_35xx(hdl, macChan)                      \
({                                                                     \
    ncp_uint32_t   __port_index = 0xFFFF;                              \
    ncp_eioas_t *__p_eioas    = NULL;                                    \
    __p_eioas = hdl->eioaHdl;                                            \
    if (__p_eioas != NULL)                                               \
    {                                                                  \
        switch(macChan)                                                \
        {                                                              \
            case NCP_GMAC0:                                            \
               if (__p_eioas->legacyIDs == TRUE)                         \
               {                                                       \
                   __port_index = 0;                                   \
               }                                                       \
               else                                                    \
               {                                                       \
                   NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);          \
               }                                                       \
               break;                                                  \
            case NCP_GMAC1:                                            \
               __port_index = 0;                                       \
               break;                                                  \
            case NCP_GMAC2:                                            \
               __port_index = 1;                                       \
               break;                                                  \
            case NCP_GMAC3:                                            \
               __port_index = 2;                                       \
               break;                                                  \
            case NCP_GMAC4:                                            \
               __port_index = 3;                                       \
               break;                                                  \
            case NCP_XGMAC8:                                           \
               if (__p_eioas->legacyIDs == TRUE)                         \
               {                                                       \
                   __port_index = 4;                                   \
               }                                                       \
               else                                                    \
               {                                                       \
                   __port_index = 0xFFFF;                             \
               }                                                       \
               break;                                                  \
            case NCP_GMAC9:                                            \
               __port_index = 4;                                       \
               break;                                                  \
            case NCP_GMAC10:                                           \
               __port_index = 5;                                       \
               break;                                                  \
            case NCP_GMAC11:                                           \
               __port_index = 6;                                       \
               break;                                                  \
            case NCP_GMAC12:                                           \
               __port_index = 7;                                       \
               break;                                                  \
            default:                                                   \
               NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);              \
        }                                                              \
    }                                                                  \
    else                                                               \
    {                                                                  \
        __port_index = 0xFFFF;                                         \
    }                                                                  \
    __port_index;                                                      \
})

#if !defined(NCP_KERNEL)

#define NCP_EIOA_PORT_VALIDATE_35xx(hdl, port)                         \
({                                                                     \
    ncp_eioas_t *__ncp_eioas    = NULL;                                \
    ncp_eioa_t  *__ncp_eioa     = NULL;                                \
    ncp_port_t  *__ncp_port = NULL;                                    \
    ncp_uint32_t __port_idex;                                          \
    ncp_uint32_t __eioa_idex;                                          \
    __ncp_eioas = hdl->eioaHdl;                                        \
    if(__ncp_eioas == NULL)                                            \
    {                                                                  \
        NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                     \
    }                                                                  \
    switch(port)                                                       \
    {                                                                  \
        case NCP_GMAC0:                                                \
           if (__ncp_eioas->legacyIDs == FALSE)                        \
           {                                                           \
               NCP_CALL(NCP_ST_MAC_INVALID_MAC);                       \
           }                                                           \
        break;                                                         \
        case NCP_GMAC1:                                                \
        case NCP_GMAC2:                                                \
        case NCP_GMAC3:                                                \
        case NCP_GMAC4:                                                \
        break;                                                         \
        case NCP_XGMAC8:                                               \
           if (__ncp_eioas->legacyIDs == FALSE)                        \
           {                                                           \
               NCP_CALL(NCP_ST_MAC_INVALID_MAC);                       \
           }                                                           \
        break;                                                         \
        case NCP_GMAC9:                                                \
        case NCP_GMAC10:                                               \
        case NCP_GMAC11:                                               \
        case NCP_GMAC12:                                               \
        break;                                                         \
        default:                                                       \
            NCP_CALL(NCP_ST_MAC_INVALID_MAC);                          \
        break;                                                         \
    }                                                                  \
    __eioa_idex = NCP_EIOA_TO_INDEX_35xx(port);                        \
    __ncp_eioa = __ncp_eioas->eioa[__eioa_idex];                       \
    if (__ncp_eioa == NULL)                                            \
    {                                                                  \
        NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                     \
    }                                                                  \
    __port_idex = NCP_EIOA_PORT_TO_INDEX_35xx(hdl, port);              \
    __ncp_port = __ncp_eioa->NCP_POINTER_ARRAY(port, __port_idex);     \
    if (__ncp_port == NULL)                                            \
    {                                                                  \
        NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                     \
    }                                                                  \
})

#define NCP_EIOA_PORT_INDEX_TO_EXTERNAL_PORT_35xx(__port_index)         \
({                                                                      \
    ncp_macChan_t   __macChan = 0xFFFF;                                 \
    switch(__port_index)                                                \
    {                                                                   \
        case 0:                                                         \
            __macChan = NCP_GMAC1;                                      \
            break;                                                      \
        case 1:                                                         \
            __macChan = NCP_GMAC2;                                      \
            break;                                                      \
        case 2:                                                         \
            __macChan = NCP_GMAC3;                                      \
            break;                                                      \
        case 3:                                                         \
            __macChan = NCP_GMAC4;                                      \
            break;                                                      \
        case 4:                                                         \
            __macChan = NCP_GMAC9;                                      \
            break;                                                      \
        case 5:                                                         \
            __macChan = NCP_GMAC10;                                     \
            break;                                                      \
        case 6:                                                         \
            __macChan = NCP_GMAC11;                                     \
            break;                                                      \
        case 7:                                                         \
            __macChan = NCP_GMAC12;                                     \
            break;                                                      \
	default:                                                        \
	    NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                  \
    }                                                                   \
    __macChan;                                                          \
})

#define NCP_EIOA_PORT_PHYACCESS_35xx(hdl, macChan)                     \
({                                                                     \
    ncp_eioas_t *__ncp_eioas    = NULL;                                \
    ncp_eioa_t  *__ncp_eioa     = NULL;                                \
    ncp_port_t  *__port = NULL;                                        \
    ncp_uint32_t __port_idex;                                          \
    ncp_uint32_t __eioa_idex;                                          \
    ncp_bool_t __phyAccess;                                            \
    __ncp_eioas = hdl->eioaHdl;                                        \
    if(__ncp_eioas == NULL)                                            \
    {                                                                  \
        NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                     \
    }                                                                  \
    switch(macChan)                                                    \
    {                                                                  \
        case NCP_GMAC0:                                                \
           if (__ncp_eioas->legacyIDs == FALSE)                        \
           {                                                           \
               NCP_CALL(NCP_ST_MAC_INVALID_MAC);                       \
           }                                                           \
        break;                                                         \
        case NCP_GMAC1:                                                \
        case NCP_GMAC2:                                                \
        case NCP_GMAC3:                                                \
        case NCP_GMAC4:                                                \
        break;                                                         \
        case NCP_XGMAC8:                                               \
           if (__ncp_eioas->legacyIDs == FALSE)                        \
           {                                                           \
               NCP_CALL(NCP_ST_MAC_INVALID_MAC);                       \
           }                                                           \
        break;                                                         \
        case NCP_GMAC9:                                                \
        case NCP_GMAC10:                                               \
        case NCP_GMAC11:                                               \
        case NCP_GMAC12:                                               \
        break;                                                         \
        default:                                                       \
            NCP_CALL(NCP_ST_MAC_INVALID_MAC);                          \
        break;                                                         \
    }                                                                  \
    __eioa_idex = NCP_EIOA_TO_INDEX_35xx(macChan);                     \
    __ncp_eioa = __ncp_eioas->eioa[__eioa_idex];                       \
    if (__ncp_eioa == NULL)                                            \
    {                                                                  \
        NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                     \
    }                                                                  \
    __port_idex = NCP_EIOA_PORT_TO_INDEX_35xx(hdl, macChan);           \
    __port = __ncp_eioa->NCP_POINTER_ARRAY(port, __port_idex);         \
    if (__port == NULL)                                                \
    {                                                                  \
        NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                     \
    }                                                                  \
    if ( (__ncp_eioas->noPhyConfig == TRUE) ||                         \
       (__port->phyAccess == NCP_MAC_CHAN_CONFIG_NONE) )               \
    {                                                                  \
        __phyAccess = FALSE;                                           \
    }                                                                  \
    else                                                               \
    {                                                                  \
        __phyAccess = TRUE;                                            \
    }                                                                  \
    __phyAccess;                                                       \
})

#define NCP_EIOA_PORT_IS_XGMAC(hdl, port)                              \
({                                                                     \
    ncp_bool_t   __isXgmac = FALSE;                                    \
    {                                                                  \
        ncp_eioas_t *__eioas    = NULL;                                \
        ncp_eioa_t  *__eioa     = NULL;                                \
        ncp_port_t  *__ncp_port = NULL;                                \
        ncp_uint32_t __port_idex;                                      \
        ncp_uint32_t __eioa_idex;                                      \
        NCP_EIOA_PORT_VALIDATE_35xx(hdl, port);                        \
        __eioas     = hdl->eioaHdl;                                    \
        __eioa_idex = NCP_EIOA_TO_INDEX_35xx(port);                    \
        __eioa      = __eioas->eioa[__eioa_idex];                      \
        __port_idex = NCP_EIOA_PORT_TO_INDEX_35xx(hdl, port);          \
        __ncp_port  = __eioa->NCP_POINTER_ARRAY(port, __port_idex);    \
	if ( __ncp_port->chanType ==  NCP_MAC_CHAN_CONFIG_XAUI ||      \
	     __ncp_port->chanType ==  NCP_MAC_CHAN_CONFIG_XGMII ||     \
	     __ncp_port->chanType ==  NCP_MAC_CHAN_CONFIG_XFI )        \
        {                                                              \
            __isXgmac   = TRUE;                                        \
        }                                                              \
    }                                                                  \
    __isXgmac;                                                         \
})

#define NCP_EIOA_TO_START_EXTERNAL_PORT_35xx(eioa_num)                             \
    ({                                                                 \
        ncp_uint32_t __start_port = NCP_GMAC1;                         \
        __start_port;                                                  \
    })

#define NCP_EIOA_TO_END_EXTERNAL_PORT_35xx(eioa_num)                   \
    ({                                                                 \
        ncp_uint32_t __end_port = NCP_GMAC12;                          \
        __end_port;                                                    \
    })

#define NCP_EIOA_EXTERNAL_PORT_TO_DEST_INST_35xx(external_port)  \
    ({                                                      \
        ncp_uint8_t __dest_inst = 0;                        \
        switch((external_port))                             \
        {                                                   \
        case NCP_GMAC1:                                     \
            __dest_inst = 1;                                \
            break;                                          \
        case NCP_GMAC2:                                     \
            __dest_inst = 2;                                \
            break;                                          \
        case NCP_GMAC3:                                     \
            __dest_inst = 3;                                \
            break;                                          \
        case NCP_GMAC4:                                     \
            __dest_inst = 4;                                \
            break;                                          \
        case NCP_GMAC9:                                     \
            __dest_inst = 9;                                \
            break;                                          \
        case NCP_GMAC10:                                    \
            __dest_inst = 10;                               \
            break;                                          \
        case NCP_GMAC11:                                    \
            __dest_inst = 11;                               \
            break;                                          \
        case NCP_GMAC12:                                    \
            __dest_inst = 12;                               \
            break;                                          \
        default:                                            \
            break;                                          \
        }                                                   \
        __dest_inst;                                        \
    })

#define NCP_EIOA_DEST_INST_TO_EXTERNAL_PORT_35xx(dest_inst)  \
({                                                      \
    ncp_uint8_t __external_port = 0;                        \
    switch((dest_inst))                             \
    {                                                   \
    case 1:                                     \
        __external_port = NCP_GMAC1;                                \
        break;                                          \
    case 2:                                     \
        __external_port = NCP_GMAC2;                                \
        break;                                          \
    case 3:                                     \
        __external_port = NCP_GMAC3;                                \
        break;                                          \
    case 4:                                     \
        __external_port = NCP_GMAC4;                                \
        break;                                          \
    case 9:                                     \
        __external_port = NCP_GMAC9;                                \
        break;                                          \
    case 10:                                    \
        __external_port = NCP_GMAC10;                               \
        break;                                          \
    case 11:                                    \
        __external_port = NCP_GMAC11;                               \
        break;                                          \
    case 12:                                    \
        __external_port = NCP_GMAC12;                               \
        break;                                          \
    default:                                            \
        break;                                          \
    }                                                   \
    __external_port;                                        \
})



#define NCP_EIOA_EXTERNAL_PORT_TO_SLOT_35xx(external_port)  \
    ({                                                      \
        ncp_uint8_t __slot = 0;                             \
        switch((external_port))                             \
        {                                                   \
        case NCP_GMAC1:                                     \
        case NCP_GMAC2:                                     \
        case NCP_GMAC3:                                     \
        case NCP_GMAC4:                                     \
            __slot = 0;                                     \
            break;                                          \
        case NCP_GMAC9:                                     \
        case NCP_GMAC10:                                    \
        case NCP_GMAC11:                                    \
        case NCP_GMAC12:                                    \
            __slot = 1;                                     \
            break;                                          \
        default:                                            \
            break;                                          \
        }                                                   \
        __slot;                                             \
    })

#define NCP_EIOA_IPP_PORT_TO_REGION_ID_35xx(port)           \
    ({                                                      \
        ncp_uint32_t __regionId = 0;                        \
        switch((port))                                      \
        {                                                   \
        case NCP_GMAC1:                                     \
        case NCP_GMAC2:                                     \
        case NCP_GMAC3:                                     \
        case NCP_GMAC4:                                     \
            __regionId = NCP_REGION_EIOA_IPP0(0);           \
            break;                                          \
        case NCP_GMAC9:                                     \
        case NCP_GMAC10:                                    \
        case NCP_GMAC11:                                    \
        case NCP_GMAC12:                                    \
            __regionId = NCP_REGION_EIOA_IPP1(0);           \
            break;                                          \
        default:                                            \
            __regionId = 0;                                 \
            break;                                          \
        }                                                   \
        __regionId;                                         \
    })

#define NCP_EEPTSP_35xx(external_port) NCP_EIOA_EXTERNAL_PORT_TO_SWITCH_PORT(external_port)

#define NCP_EIOA_EXTERNAL_PORT_TO_SWITCH_PORT(external_port)  \
    ({                                                      \
        ncp_uint8_t __sport = 0;                            \
        switch((external_port))                             \
        {                                                   \
        case NCP_GMAC1:                                     \
            __sport = 0;                                    \
            break;                                          \
        case NCP_GMAC2:                                     \
            __sport = 1;                                    \
            break;                                          \
        case NCP_GMAC3:                                     \
            __sport = 2;                                    \
            break;                                          \
        case NCP_GMAC4:                                     \
            __sport = 3;                                    \
            break;                                          \
        case NCP_GMAC9:                                     \
            __sport = 4;                                    \
            break;                                          \
        case NCP_GMAC10:                                    \
            __sport = 5;                                    \
            break;                                          \
        case NCP_GMAC11:                                    \
            __sport = 6;                                    \
            break;                                          \
        case NCP_GMAC12:                                    \
            __sport = 7;                                    \
            break;                                          \
        default:                                            \
            break;                                          \
        }                                                   \
        __sport;                                            \
    })

#define NCP_ESPTEP_35xx(switch_port) NCP_EIOA_SWITCH_PORT_TO_EXTERNAL_PORT(switch_port)

#define NCP_EIOA_SWITCH_PORT_TO_EXTERNAL_PORT(switch_port)  \
    ({                                                      \
        ncp_macChan_t __macChan = 0xff;                     \
        switch((switch_port))                               \
        {                                                   \
        case 0:                                             \
            __macChan = NCP_GMAC1;                          \
            break;                                          \
        case 1:                                             \
            __macChan = NCP_GMAC2;                          \
            break;                                          \
        case 2:                                             \
            __macChan = NCP_GMAC3;                          \
            break;                                          \
        case 3:                                             \
            __macChan = NCP_GMAC4;                          \
            break;                                          \
        case 4:                                             \
            __macChan = NCP_GMAC9;                          \
            break;                                          \
        case 5:                                             \
            __macChan = NCP_GMAC10;                         \
            break;                                          \
        case 6:                                             \
            __macChan = NCP_GMAC11;                         \
            break;                                          \
        case 7:                                             \
            __macChan = NCP_GMAC12;                         \
            break;                                          \
        default:                                            \
            break;                                          \
        }                                                   \
        __macChan;                                          \
    })

#define NCP_EIOA_EPP_PORT_TO_REGION_ID_35xx(port)           \
    ({                                                      \
        ncp_uint32_t __regionId = 0;                        \
        switch((port))                                      \
        {                                                   \
        case NCP_GMAC1:                                     \
        case NCP_GMAC2:                                     \
        case NCP_GMAC3:                                     \
        case NCP_GMAC4:                                     \
            __regionId = NCP_REGION_EIOA_EPP0(0);           \
            break;                                          \
        case NCP_GMAC9:                                     \
        case NCP_GMAC10:                                    \
        case NCP_GMAC11:                                    \
        case NCP_GMAC12:                                    \
            __regionId = NCP_REGION_EIOA_EPP1(0);           \
            break;                                          \
        default:                                            \
            break;                                          \
        }                                                   \
        __regionId;                                         \
    })


#define NCP_EIOA_PORT_ID_TO_PORT_INDEX(portId, xgmac_flag)  \
    ({                                                      \
        ncp_uint8_t __port_index = 0xFF;                    \
        if (xgmac_flag == TRUE)                             \
        {                                                   \
             switch((portId))                               \
             {                                              \
             case 1:                                        \
                 __port_index = 0;                          \
                 break;                                     \
             case 9:                                        \
                 __port_index = 4;                          \
                 break;                                     \
	     default:                                       \
                 break;                                     \
             }                                              \
        }                                                   \
        else                                                \
        {                                                   \
            switch((portId))                                \
            {                                               \
             case 1:                                        \
                 __port_index = 0;                          \
                 break;                                     \
             case 2:                                        \
                 __port_index = 1;                          \
                 break;                                     \
             case 3:                                        \
                 __port_index = 2;                          \
                 break;                                     \
             case 4:                                        \
                 __port_index = 3;                          \
                 break;                                     \
             case 9:                                        \
                 __port_index = 4;                          \
                 break;                                     \
             case 10:                                       \
                 __port_index = 5;                          \
                 break;                                     \
             case 11:                                       \
                 __port_index = 6;                          \
                 break;                                     \
             case 12:                                       \
                 __port_index = 7;                          \
                 break;                                     \
            default:                                        \
                break;                                      \
            }                                               \
        }                                                   \
        __port_index;                                       \
    })

#define NCP_EIOA_PORT_INDEX_TO_MAC_CHAN(portId, xgmac_flag) \
    ({                                                      \
        ncp_macChan_t __macChan = NCP_XGMAC16;              \
        if (xgmac_flag == TRUE)                             \
        {                                                   \
             switch((portId))                               \
             {                                              \
             case 1:                                        \
                 __macChan = NCP_XGMAC1;                    \
                 break;                                     \
             case 9:                                        \
                 __macChan = NCP_XGMAC9;                    \
                 break;                                     \
	     default:                                       \
                 break;                                     \
             }                                              \
        }                                                   \
        else                                                \
        {                                                   \
            switch((portId))                                \
            {                                               \
             case 1:                                        \
                 __macChan = NCP_GMAC1;                     \
                 break;                                     \
             case 2:                                        \
                 __macChan = NCP_GMAC2;                     \
                 break;                                     \
             case 3:                                        \
                 __macChan = NCP_GMAC3;                     \
                 break;                                     \
             case 4:                                        \
                 __macChan = NCP_GMAC4;                     \
                 break;                                     \
             case 9:                                        \
                 __macChan = NCP_GMAC9;                     \
                 break;                                     \
             case 10:                                       \
                 __macChan = NCP_GMAC10;                     \
                 break;                                     \
             case 11:                                       \
                 __macChan = NCP_GMAC11;                     \
                 break;                                     \
             case 12:                                       \
                 __macChan = NCP_GMAC12;                     \
                 break;                                     \
            default:                                        \
                NCP_CALL(NCP_ST_MAC_INVALID_MAC);           \
            }                                               \
        }                                                   \
        __macChan;                                          \
    })

#define NCP_EIOA_PORT_TYPE_35xx(hdl, macChan)                          \
    ({                                                                     \
        ncp_eioas_t *__eioas    = NULL;                                    \
        ncp_eioa_t  *__eioa     = NULL;                                    \
        ncp_port_t  *__ncp_port = NULL;                                    \
        ncp_uint32_t __port_idex;                                          \
        ncp_uint32_t __eioa_idex;                                          \
        ncp_bool_t __xgmac_flag;                                           \
        __eioas = ((ncp_t *)hdl)->eioaHdl;                                 \
        if(__eioas == NULL)                                                \
        {                                                                  \
            NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                     \
        }                                                                  \
        switch(macChan)                                                    \
        {                                                                  \
            case NCP_GMAC0:                                                \
               if (__eioas->legacyIDs == FALSE)                            \
               {                                                           \
                   NCP_CALL(NCP_ST_MAC_INVALID_MAC);                       \
               }                                                           \
            break;                                                         \
            case NCP_GMAC1:                                                \
            case NCP_GMAC2:                                                \
            case NCP_GMAC3:                                                \
            case NCP_GMAC4:                                                \
            break;                                                         \
            case NCP_XGMAC8:                                               \
               if (__eioas->legacyIDs == FALSE)                            \
               {                                                           \
                   NCP_CALL(NCP_ST_MAC_INVALID_MAC);                       \
               }                                                           \
            break;                                                         \
            case NCP_GMAC9:                                                \
            case NCP_GMAC10:                                               \
            case NCP_GMAC11:                                               \
            case NCP_GMAC12:                                               \
            break;                                                         \
            default:                                                       \
                NCP_CALL(NCP_ST_MAC_INVALID_MAC);                          \
            break;                                                         \
        }                                                                  \
        __eioa_idex = NCP_EIOA_TO_INDEX_35xx(macChan);                     \
        __eioa = __eioas->eioa[__eioa_idex];                               \
        if (__eioa == NULL)                                                \
        {                                                                  \
            NCP_CALL(NCP_ST_EIOA_INVALID_PORT_CONFIG);                     \
        }                                                                  \
        __port_idex = NCP_EIOA_PORT_TO_INDEX_35xx(hdl, macChan);           \
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
                                                                           \
        })

/* Note: These values need to match with ASE values */
#define NCP_EIOA_QBB_PAUSE_BP_ID_BASE_35xx(port)     (129 + ( 8 * NCP_EEPTSP_35xx(port)))
#define NCP_EIOA_REGULAR_PAUSE_BP_ID_35xx(port)      (209 + NCP_EEPTSP_35xx(port))
#define NCP_EIOA_BP_ID_TO_ENGINE(engine, bpId)    \
    ({ \
        ncp_engine_type_t __engine = ncp_engine_eioa0; \
        __engine; \
    })

#define NCP_EIOA_QBB_PORT_BP_OFFSET(external_port)                              \
    (NCP_EIOA_CORE_BP_CFG_REGISTERS_BASE +                                      \
     NCP_BP_CFG_REGISTERS_S0_PORT_BP_OFFSET_PORT +                              \
    (NCP_EIOA_EXTERNAL_PORT_TO_SLOT_35xx(external_port) * 0x100) +              \
    (NCP_EIOA_EXTERNAL_TO_INTERNAL_PORT_35xx(external_port) * 4))

#define NCP_EIOA_QBB_TASK_QUEUE_BP_OFFSET(external_port)                        \
    (NCP_EIOA_CORE_BP_CFG_REGISTERS_BASE +                                      \
     NCP_BP_CFG_REGISTERS_S0_RX_QBB_BP_PORT_BASE(0) +                           \
    (NCP_EIOA_EXTERNAL_PORT_TO_SLOT_35xx(external_port) * 0x1000) +             \
    (NCP_EIOA_EXTERNAL_TO_INTERNAL_PORT_35xx(external_port) * 0x100))

ncp_st_t
ncp_eioa_config_35xx(
    ncp_t         *ncp,
    ncp_map_t     *map);

ncp_st_t
ncp_eioa_destroy_35xx(ncp_t *ncp);

ncp_st_t
ncp_eioa_warm_restart_35xx(ncp_t *ncp);

ncp_st_t
ncp_ueioa_config(
    ncp_t         *ncp,
    ncp_map_t     *map);

ncp_st_t
ncp_ueioa_destroy(ncp_t *ncp);

ncp_st_t
ncp_ueioa_warm_restart(ncp_t *ncp);

ncp_st_t
ncp_eioa_get_all_port_maps(ncp_t* ncp, ncp_map_t *eioaMap, ncp_map_t **portMaps, ncp_uint32_t noPortMaps, ncp_uint32_t* noPortMapsFound);

#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _NCP_EIOA_CONFIG_35XX_H_ */

