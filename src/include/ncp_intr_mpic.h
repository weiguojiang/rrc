/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


#ifndef __NCP_INTR_MPIC_H__
#define __NCP_INTR_MPIC_H__

#include "regs/ncp_intr_mpic_regs.h"
#include "regs/ncp_intr_mpic_reg_defines.h"

/* 
 * enumerated list of MPIC interrupt sources for X1/X2
 */
enum {
    NCP_INTR_MPIC_SRC_X1_INT_8259 = 0,                  /*   0 */
    NCP_INTR_MPIC_SRC_PPCS_AXIS_PLB6_SYSTEM_HUNG,       /*   1 */
    NCP_INTR_MPIC_SRC_PPCS_AXIS_OVERTEMP,               /*   2 */
    NCP_INTR_MPIC_SRC_PPCS_AXIS_UNDERTEMP,              /*   3 */
    NCP_INTR_MPIC_SRC_PPCS_AXIS_TVSENSE_COMPLETE,       /*   4 */
    NCP_INTR_MPIC_SRC_PPCS_AXIS_L2C_MCHKOUT_3,          /*   5 */
    NCP_INTR_MPIC_SRC_PPCS_AXIS_L2C_MCHKOUT_2,          /*   6 */
    NCP_INTR_MPIC_SRC_PPCS_AXIS_L2C_MCHKOUT_1,          /*   7 */
    NCP_INTR_MPIC_SRC_PPCS_AXIS_L2C_MCHKOUT_0,          /*   8 */
    NCP_INTR_MPIC_SRC_PPCS_AXIS_L2C_INTERRUPTOUT_3,     /*   9 */
    NCP_INTR_MPIC_SRC_PPCS_AXIS_L2C_INTERRUPTOUT_2,     /*  10 */
    NCP_INTR_MPIC_SRC_PPCS_AXIS_L2C_INTERRUPTOUT_1,     /*  11 */
    NCP_INTR_MPIC_SRC_PPCS_AXIS_L2C_INTERRUPTOUT_0,     /*  12 */
    NCP_INTR_MPIC_SRC_PPCS_AXIS_WAKEUP_3,               /*  13 */
    NCP_INTR_MPIC_SRC_PPCS_AXIS_WAKEUP_2,               /*  14 */
    NCP_INTR_MPIC_SRC_PPCS_AXIS_WAKEUP_1,               /*  15 */
    NCP_INTR_MPIC_SRC_PPCS_AXIS_WAKEUP_0,               /*  16 */
    NCP_INTR_MPIC_SRC_PPCS_X1_INSTR_TRACE_COMPLETE,     /*  17 */
    NCP_INTR_MPIC_SRC_PPCS_X1_LA_COMPLETE,              /*  18 */
    NCP_INTR_MPIC_SRC_AXIS_GPIO,                        /*  19 */
    NCP_INTR_MPIC_SRC_AXIS_SSP,                         /*  20 */
    NCP_INTR_MPIC_SRC_AXIS_I2C,                         /*  21 */
    NCP_INTR_MPIC_SRC_AXIS_UART0,                       /*  22 */
    NCP_INTR_MPIC_SRC_AXIS_UART1,                       /*  23 */
    NCP_INTR_MPIC_SRC_AXIS_TIMER3,                      /*  24 */
    NCP_INTR_MPIC_SRC_AXIS_TIMER5,                      /*  25 */
    NCP_INTR_MPIC_SRC_AXIS_TIMER6,                      /*  26 */
    NCP_INTR_MPIC_SRC_AXIS_TIMER7,                      /*  27 */
    NCP_INTR_MPIC_SRC_AXIS_TIMERC,                      /*  28 */
    NCP_INTR_MPIC_SRC_AXIS_PEI,                         /*  29 */
    NCP_INTR_MPIC_SRC_AXIS_SRIO,                        /*  30 */
    NCP_INTR_MPIC_SRC_AXIS_USB,                         /*  31 */
    NCP_INTR_MPIC_SRC_AXIS_FEMAC_RX,                    /*  32 */
    NCP_INTR_MPIC_SRC_AXIS_FEMAC_DMA,                   /*  33 */
    NCP_INTR_MPIC_SRC_AXIS_NAND,                        /*  34 */
    NCP_INTR_MPIC_SRC_AXIS_GPDMA_0,                     /*  35 */
    NCP_INTR_MPIC_SRC_AXIS_GPDMA_1,                     /*  36 */
    NCP_INTR_MPIC_SRC_AXIS_GPDMA_2,                     /*  37 */
    NCP_INTR_MPIC_SRC_AXIS_GPDMA_3,                     /*  38 */
    NCP_INTR_MPIC_SRC_AXIS_PKA_0,                       /*  39 */
    NCP_INTR_MPIC_SRC_AXIS_PKA_1,                       /*  40 */
    NCP_INTR_MPIC_SRC_AXIS_PKA_2,                       /*  41 */
    NCP_INTR_MPIC_SRC_AXIS_TRNG,                        /*  42 */
    NCP_INTR_MPIC_SRC_NCA_5,                            /*  43 */
    NCP_INTR_MPIC_SRC_NCA_4,                            /*  44 */
    NCP_INTR_MPIC_SRC_NCA_3,                            /*  45 */
    NCP_INTR_MPIC_SRC_NCA_2,                            /*  46 */
    NCP_INTR_MPIC_SRC_NCA_1,                            /*  47 */
    NCP_INTR_MPIC_SRC_NCA_0,                            /*  48 */
    NCP_INTR_MPIC_SRC_MMB_1,                            /*  49 */
    NCP_INTR_MPIC_SRC_MMB_0,                            /*  50 */
    NCP_INTR_MPIC_SRC_MPPX_1,                           /*  51 */
    NCP_INTR_MPIC_SRC_MPPX_0,                           /*  52 */
    NCP_INTR_MPIC_SRC_EIOA0,                            /*  53 */
    NCP_INTR_MPIC_SRC_EIOA1,                            /*  54 */
    NCP_INTR_MPIC_SRC_MTM_1,                            /*  55 */
    NCP_INTR_MPIC_SRC_MTM_0,                            /*  56 */
    NCP_INTR_MPIC_SRC_PAB_1,                            /*  57 */
    NCP_INTR_MPIC_SRC_PAB_0,                            /*  58 */
    NCP_INTR_MPIC_SRC_SED_1,                            /*  59 */
    NCP_INTR_MPIC_SRC_SED_0,                            /*  60 */
    NCP_INTR_MPIC_SRC_TMGR_1,                           /*  61 */
    NCP_INTR_MPIC_SRC_TMGR_0,                           /*  62 */
    NCP_INTR_MPIC_SRC_PIC_0,                            /*  63 */
    NCP_INTR_MPIC_SRC_SPP_1,                            /*  64 */
    NCP_INTR_MPIC_SRC_SPP_0,                            /*  65 */
    NCP_INTR_MPIC_SRC_DPI_1,                            /*  66 */
    NCP_INTR_MPIC_SRC_DPI_0,                            /*  67 */
    NCP_INTR_MPIC_SRC_SPARE0,                           /*  68 */
    NCP_INTR_MPIC_SRC_SPARE1,                           /*  69 */
    NCP_INTR_MPIC_SRC_SPARE2,                           /*  70 */
    NCP_INTR_MPIC_SRC_SPARE3,                           /*  71 */
    NCP_INTR_MPIC_SRC_PEI1,                             /*  72 */
    NCP_INTR_MPIC_SRC_PEI2,                             /*  73 */
    NCP_INTR_MPIC_SRC_PEI_DOORBELL,                     /*  74 */
    NCP_INTR_MPIC_SRC_NTIMC,                            /*  75 */
    NCP_INTR_MPIC_SRC_NTEMC1,                           /*  76 */
    NCP_INTR_MPIC_SRC_NTEMC0,                           /*  77 */
    NCP_INTR_MPIC_SRC_NHA,                              /*  78 */
    NCP_INTR_MPIC_SRC_P2A,                              /*  79 */
    NCP_INTR_MPIC_SRC_A2P_PPCS_PLB6,                    /*  80 */
    NCP_INTR_MPIC_SRC_SC7,                              /*  81 */
    NCP_INTR_MPIC_SRC_SC6,                              /*  82 */
    NCP_INTR_MPIC_SRC_SC5,                              /*  83 */
    NCP_INTR_MPIC_SRC_SC4,                              /*  84 */
    NCP_INTR_MPIC_SRC_SC3,                              /*  85 */
    NCP_INTR_MPIC_SRC_SC2,                              /*  86 */
    NCP_INTR_MPIC_SRC_SC1,                              /*  87 */
    NCP_INTR_MPIC_SRC_SC0,                              /*  88 */
    NCP_INTR_MPIC_SRC_SM1,                              /*  89 */
    NCP_INTR_MPIC_SRC_SM0,                              /*  90 */
    NCP_INTR_MPIC_SRC_X1_CPT,                           /*  91 */
    NCP_INTR_MPIC_SRC_PPCS_AXIS_PMU_3,                  /*  92 */
    NCP_INTR_MPIC_SRC_PPCS_AXIS_PMU_2,                  /*  93 */
    NCP_INTR_MPIC_SRC_PPCS_AXIS_PMU_1,                  /*  94 */
    NCP_INTR_MPIC_SRC_PPCS_AXIS_PMU_0,                  /*  95 */
    NCP_INTR_MPIC_SRC_MAX  /* MUST BE LAST ENTRY */
}; 


/*
 * some of these IRQs have been reassigned for ACP2500
 * we enumerate only the differences here
 */
enum {
    NCP_INTR_MPIC_2500_DMA0_ERR            = 5,
    NCP_INTR_MPIC_2500_DMA0_BUSY           = 6,
    NCP_INTR_MPIC_2500_DMA1_ERR            = 9,
    NCP_INTR_MPIC_2500_DMA1_BUSY           = 10,
    NCP_INTR_MPIC_2500_I2C_1               = 13,
    NCP_INTR_MPIC_2500_UART_2              = 14,
    NCP_INTR_MPIC_2500_TIMER4              = 25,
    NCP_INTR_MPIC_2500_PP3_SERVICE         = 68,
    NCP_INTR_MPIC_2500_PP3_ALARM           = 69,
    NCP_INTR_MPIC_2500_MSD                 = 70,
    NCP_INTR_MPIC_2500_SBB                 = 71,
    NCP_INTR_MPIC_2500_PPCS_AXIS_WDEXPRIED = 76,
    NCP_INTR_MPIC_2500_TM_PLL              = 81,
    NCP_INTR_MPIC_2500_SM_PLL              = 82,
    NCP_INTR_MPIC_2500_SYS_PLL             = 83,
    NCP_INTR_MPIC_2500_PPC_PLL             = 84,
    NCP_INTR_MPIC_2500_LBI                 = 92,
    NCP_INTR_MPIC_2500_ECM                 = 93
};

#endif
