/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*! @file      ncp_sal_target.h
    @brief     Include Target specific header file here.
*/


#ifndef __NCP_SAL_TARGET_H__
#define __NCP_SAL_TARGET_H__

/* 
 * Include the right target-processor type based on platform and 
 * the right processor as defined by -DPROC_<processor-name>
 */

#ifdef NCP_LINUX

#ifdef PROC_PPC476
#include "ncp_sal_linux-ppc476.h"
#endif

#ifdef PROC_ARMA15
#include "ncp_sal_linux-arma15.h"
#endif

#ifdef PROC_ARMA57
#include "ncp_sal_linux-arma57.h"
#endif

#ifdef PROC_X86
#include "ncp_sal_linux-x86.h"
#endif

#ifdef PROC_X86_PLX64
#ifdef NCP_WRL_X86_64
#include "ncp_sal_wrl-x86_64.h"
#else
#include "ncp_sal_linux-x86_64.h"
#endif
#endif

#if defined(PROC_EP8572)
#include "ncp_sal_linux-ep8572.h"
#endif

#ifdef PROC_EP8641
#include "ncp_sal_linux-ep8641.h"
#endif

#ifdef PROC_EP4080
#include "ncp_sal_linux-ep4080.h"
#endif

#ifdef PROC_EP5020
#include "ncp_sal_linux-ep5020.h"
#endif

#ifdef PROC_PM750F
#include "ncp_sal_hhl-pmppc750f.h"
#endif

#ifdef PROC_EP5020
#include "ncp_sal_linux-ep5020.h"
#endif

#endif /* NCP_LINUX */

#ifdef NCP_OSE 

#ifdef PROC_PPC476
#include "ncp_sal_ose-ppc476.h"
#endif

#ifdef PROC_X86
#include "ncp_sal_ose-x86.h"
#endif

#endif /* NCP_OSE */

#ifdef NCP_VXWORKS

#ifdef PROC_PPC476
#include "ncp_sal_vxworks-ppc476.h"
#endif

#endif /* NCP_VXWORKS */

#ifdef WIN32 

#ifdef PROC_X86
#include "ncp_sal_mingw-w32.h"
#endif

#endif /* WIN32 */

#endif /* NCP_SAL_TARGET_H */
