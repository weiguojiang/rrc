/**************************************************************************
 **                                                                       *
 **                           Intel CONFIDENTIAL        *
 **                           PROPRIETARY NOTE                            *
 **                                                                       *
 **    This software contains information confidential and proprietary    *
 **    to Intel Corporation.  It shall not be reproduced in whole or in *
 **    part, or transferred to other documents, or disclosed to third     *
 **    parties, or used for any purpose other than that for which it was  *
 **    obtained, without the prior written consent of Intel Corporation.*
 **    (c) 2008-2014, Intel Corporation.  All rights reserved.          *
 **                                                                       *
 **
 **************************************************************************/
/*! @file  ncpFpgaReader.h
    @brief Porting definitions to integrate 3rd-party loaders for various
           FPGA JTAG image file formats.
*/

#ifndef _NCP_FPGA_READER_H_
#define _NCP_FPGA_READER_H_

#include <ctype.h>
#include <string.h>
#include <setjmp.h>

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************
 **   Constants, Macros & Type Definitions
 **************************************************************************/

/*! @def NCP_WAIT_USECS(usecs)
    @brief A macro approximation of the system usleep() function with
           better performance than the granularity of the system call.
*/
#ifdef NCP_DEBUG
    #define FAUX_USLEEP       56
#else
    #define FAUX_USLEEP       560
#endif
     /* Hack around wide granularity of some system usleep functions.
      * Define the symbol FAUX_USLEEP with an integer number to be
      * used as loop limit / overhead estimate for 1 us.  Larger values
      * are needed for the busy loop when an optimized compilation is
      * performed, or when running on a faster processor. */

#ifdef FAUX_USLEEP
    #define NCP_WAIT_USECS(t)         if(t > 0) { long iii, jjj, kkk=0; /*printf("usleep %dus\n", t);*/ for(iii=0; iii < (long)t; iii++){ for(jjj=0; jjj < FAUX_USLEEP; jjj++) { kkk = iii ^ jjj ^ kkk; } } }
#else
    #define NCP_WAIT_USECS(t)         if(t > 0) { /*printf("usleep %dus\n", t);*/ ncp_sys_usleep(t); }
#endif

/*! @enum  ncp_fpga_debug_t
    @brief FPGA diagnostic mode
 */
typedef enum
{
    NCP_FPGA_DEBUG_NONE,
    NCP_FPGA_DEBUG_APPLICATION
}
ncp_fpga_debug_t;

/*
 * Shared output pin descriptions
 *   Based on standard cable definition.  These are the values
 *   constructed by or returned to the FPGA module libs by the
 *   functions _inp() or _outp() in the board-specific layers.
 */
#define NCP_FPGA_PIN_None       0x0000    /* Bit address of 'all off'  */
#define NCP_FPGA_PIN_TDI        0x0001    /* Bit address of TDI signal */
#define NCP_FPGA_PIN_TCK        0x0002    /* Bit address of TCK signal */
#define NCP_FPGA_PIN_TMS        0x0004    /* Bit address of TMS signal */
#define NCP_FPGA_PIN_TDO        0x0040    /* Bit address of TDO signal */
#define NCP_FPGA_PIN_ENABLE     0x0080    /* Bit address of Enable signal */
#define NCP_FPGA_PIN_ENABLE_OFF 0x0100    /* Bit address of !Enable signal */


/*! @fn int NCP_FPGALOAD_EXIT_MAIN(void)
    @brief Configuration/return point for local implementation of
           'program exit' for the FPGA module libs.  Must be called
	   by the main application prior to use of that feature.
	   Location of the call must interpret return value with
	   setjmp() semantics.
    @returns Success/failure code -- see setjmp() for details
*/
#define NCP_FPGALOAD_EXIT_MAIN(n)   setjmp(ncp_fpgaLoad_jmpEnv)


/*! @fn void NCP_FPGALOAD_EXIT(code)
    @brief Local implementation of 'program exit' for the FPGA module libs
*/
#define NCP_FPGALOAD_EXIT(n)   longjmp(ncp_fpgaLoad_jmpEnv, n)


/**************************************************************************
 **   Function Prototypes & Extern Variables
 **************************************************************************/

/*! @var extern jmp_buf ncp_fpgaLoad_jmpEnv
    @brief State variable support for module implementation of
           NCP_FPGALOAD_EXIT().  We jump back to the FPGA Load
           main instead of exiting from any place in the libraries.
*/
extern jmp_buf ncp_fpgaLoad_jmpEnv;

/*! @var ncp_fpga_debug_t ncpFpgaLoadDebug
    @brief Common debug level indicator
*/
extern ncp_fpga_debug_t ncpFpgaLoadDebug;

/*! @fn int _inp(short portHdl)
    @brief Emulation of port input function mapped to current FPGA hardware
    @param portHdl Port selection
    @returns Value of byte read/failure code
*/
extern int _inp(short portHdl);

/*! @fn int _outp(short portHdl, short pinMask)
    @brief Emulation of port output function mapped to current FPGA hardware
    @param portHdl Port selection
    @param pinMask Value of byte to be written
    @returns Success/failure code
*/
extern int _outp(short portHdl, short pinMask);


#ifdef __cplusplus
}
#endif

#endif /* _NCP_FPGA_READER_H_ */
