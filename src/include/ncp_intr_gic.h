
/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


#ifndef __NCP_INTR_GIC_H__
#define __NCP_INTR_GIC_H__

#include "regs/ncp_gic_c_regs.h"
#include "regs/ncp_gic_c_reg_defines.h"
#include "regs/ncp_gic_d_regs.h"
#include "regs/ncp_gic_d_reg_defines.h"

/*
 * enumerated list of GIC interrupt sources for X7
  */

enum {
    NCP_INTR_GIC_AXIS_SPARE_IRQ_0 = 0,          /* IRQ 0 */
    NCP_INTR_GIC_AXIS_SPARE_IRQ_1,              /* IRQ 1 */
    NCP_INTR_GIC_TXMAC_INT,                     /* IRQ 2 */
    NCP_INTR_GIC_RXMAC_INT,                     /* IRQ 3 */
    NCP_INTR_GIC_MAC_DMA_INT,                   /* IRQ 4 */
    NCP_INTR_GIC_AXIS_SPARE_IRQ_2,              /* IRQ 5 */
    NCP_INTR_GIC_PKA_INT,                       /* IRQ 6 */
    NCP_INTR_GIC_AXIS_SPARE_IRQ_3,              /* IRQ 7 */
    NCP_INTR_GIC_TRNG_INT,                      /* IRQ 8 */
    NCP_INTR_GIC_SBB_INT,                       /* IRQ 9 */
    NCP_INTR_GIC_GPIO_INT_0,                    /* IRQ 10 */
    NCP_INTR_GIC_GPIO_INT_1,                    /* IRQ 11 */
    NCP_INTR_GIC_GPIO_INT_2,                    /* IRQ 12 */
    NCP_INTR_GIC_GPIO_INT_3,                    /* IRQ 13 */
    NCP_INTR_GIC_GPIO_INT_4,                    /* IRQ 14 */
    NCP_INTR_GIC_GPIO_INT_5,                    /* IRQ 15 */
    NCP_INTR_GIC_GPIO_INT_6,                    /* IRQ 16 */
    NCP_INTR_GIC_GPIO_INT_7,                    /* IRQ 17 */
    NCP_INTR_GIC_GPIO_INT158OR,                 /* IRQ 18 */
    NCP_INTR_GIC_I2C0_INT,                      /* IRQ 19 */
    NCP_INTR_GIC_I2C1_INT,                      /* IRQ 20 */
    NCP_INTR_GIC_I2C2_INT,                      /* IRQ 21 */
    NCP_INTR_GIC_I2C3_INT,                      /* IRQ 22 */
    NCP_INTR_GIC_M3_A15_INT_0,                  /* IRQ 23 */
    NCP_INTR_GIC_M3_A15_INT_1,                  /* IRQ 24 */
    NCP_INTR_GIC_M3_A15_INT_2,                  /* IRQ 25 */
    NCP_INTR_GIC_M3_A15_INT_3,                  /* IRQ 26 */
    NCP_INTR_GIC_M3_A15_INT_4,                  /* IRQ 27 */
    NCP_INTR_GIC_M3_A15_INT_5,                  /* IRQ 28 */
    NCP_INTR_GIC_M3_A15_INT_6,                  /* IRQ 29 */
    NCP_INTR_GIC_M3_A15_INT_7,                  /* IRQ 30 */
    NCP_INTR_GIC_M3_A15_INT_8,                  /* IRQ 31 */
    NCP_INTR_GIC_M3_A15_INT_9,                  /* IRQ 32 */
    NCP_INTR_GIC_M3_A15_INT_10,                 /* IRQ 33 */
    NCP_INTR_GIC_M3_A15_INT_11,                 /* IRQ 34 */
    NCP_INTR_GIC_M3_A15_INT_12,                 /* IRQ 35 */
    NCP_INTR_GIC_M3_A15_INT_13,                 /* IRQ 36 */
    NCP_INTR_GIC_M3_A15_INT_14,                 /* IRQ 37 */
    NCP_INTR_GIC_M3_A15_INT_15,                 /* IRQ 38 */
    NCP_INTR_GIC_M3_SED_INT,                    /* IRQ 39 */
    NCP_INTR_GIC_M3_DED_INT,                    /* IRQ 40 */
    NCP_INTR_GIC_MSD_INT,                       /* IRQ 41 */
    NCP_INTR_GIC_SSP0_INT,                      /* IRQ 42 */
    NCP_INTR_GIC_XVRC_INT,                      /* IRQ 43 */
    NCP_INTR_GIC_SPF_INT,                       /* IRQ 44 */
    NCP_INTR_GIC_MTC_INT,                       /* IRQ 45 */
    NCP_INTR_GIC_TIMER0_INT,                    /* IRQ 46 */
    NCP_INTR_GIC_TIMER1_INT,                    /* IRQ 47 */
    NCP_INTR_GIC_TIMER2_INT,                    /* IRQ 48 */
    NCP_INTR_GIC_TIMER3_INT,                    /* IRQ 49 */
    NCP_INTR_GIC_TIMER4_INT,                    /* IRQ 50 */
    NCP_INTR_GIC_TIMER5_INT,                    /* IRQ 51 */
    NCP_INTR_GIC_TIMER6_INT,                    /* IRQ 52 */
    NCP_INTR_GIC_TIMER7_INT,                    /* IRQ 53 */
    NCP_INTR_GIC_TIMER8_INT,                    /* IRQ 54 */
    NCP_INTR_GIC_USB_INT,                       /* IRQ 55 */
    NCP_INTR_GIC_UART0_INT,                     /* IRQ 56 */
    NCP_INTR_GIC_UART1_INT,                     /* IRQ 57 */
    NCP_INTR_GIC_UART2_INT,                     /* IRQ 58 */
    NCP_INTR_GIC_UART3_INT,                     /* IRQ 59 */
    NCP_INTR_GIC_GPDMA0_BUSY,                   /* IRQ 60 */
    NCP_INTR_GIC_GPDMA0_ERR,                    /* IRQ 61 */
    NCP_INTR_GIC_GPDMA0_REQ_0,                  /* IRQ 62 */
    NCP_INTR_GIC_GPDMA0_REQ_1,                  /* IRQ 63 */
    NCP_INTR_GIC_GPDMA1_BUSY,                   /* IRQ 64 */
    NCP_INTR_GIC_GPDMA1_ERR,                    /* IRQ 65 */
    NCP_INTR_GIC_GPDMA1_REQ_0,                  /* IRQ 66 */
    NCP_INTR_GIC_GPDMA1_REQ_1,                  /* IRQ 67 */
    NCP_INTR_GIC_PEI0_INT,                      /* IRQ 68 */
    NCP_INTR_GIC_PEI1_INT,                      /* IRQ 69 */
    NCP_INTR_GIC_PEI2_INT,                      /* IRQ 70 */
    NCP_INTR_GIC_PEI0_DOOR_BELL,                /* IRQ 71 */
    NCP_INTR_GIC_PEI2_DOOR_BELL,                /* IRQ 72 */
    NCP_INTR_GIC_MSI_LOWER_0,                   /* IRQ 73 */
    NCP_INTR_GIC_MSI_LOWER_1,                   /* IRQ 74 */
    NCP_INTR_GIC_MSI_LOWER_2,                   /* IRQ 75 */
    NCP_INTR_GIC_MSI_LOWER_3,                   /* IRQ 76 */
    NCP_INTR_GIC_MSI_LOWER_4,                   /* IRQ 77 */
    NCP_INTR_GIC_MSI_LOWER_5,                   /* IRQ 78 */
    NCP_INTR_GIC_MSI_LOWER_6,                   /* IRQ 79 */
    NCP_INTR_GIC_MSI_LOWER_7,                   /* IRQ 80 */
    NCP_INTR_GIC_MSI_UPPER_0,                   /* IRQ 81 */
    NCP_INTR_GIC_MSI_UPPER_1,                   /* IRQ 82 */
    NCP_INTR_GIC_MSI_UPPER_2,                   /* IRQ 83 */
    NCP_INTR_GIC_MSI_UPPER_3,                   /* IRQ 84 */
    NCP_INTR_GIC_MSI_UPPER_4,                   /* IRQ 85 */
    NCP_INTR_GIC_MSI_UPPER_5,                   /* IRQ 86 */
    NCP_INTR_GIC_MSI_UPPER_6,                   /* IRQ 87 */
    NCP_INTR_GIC_MSI_UPPER_7,                   /* IRQ 88 */
    NCP_INTR_GIC_SRIO0_INT,                     /* IRQ 89 */
    NCP_INTR_GIC_SRIO1_INT,                     /* IRQ 90 */
    NCP_INTR_GIC_LSM_SEC_INT,                   /* IRQ 91 */
    NCP_INTR_GIC_LSM_DED_INT,                   /* IRQ 92 */
    NCP_INTR_GIC_TZC380W_INT,                   /* IRQ 93 */
    NCP_INTR_GIC_TZC380R_INT,                   /* IRQ 94 */
    NCP_INTR_GIC_AXIS_SPARE,                    /* IRQ 95 */
    NCP_INTR_GIC_TVSENSE_OVERTEMP,              /* IRQ 96 */
    NCP_INTR_GIC_TVSENSE_UNDERTEMP,             /* IRQ 97 */
    NCP_INTR_GIC_TVSENSE_COMPLETE,              /* IRQ 98 */
    NCP_INTR_GIC_AXIS_CHIP_WDEXPIRED,           /* IRQ 99 */
    NCP_INTR_GIC_NCA_GRP_0,                     /* IRQ 100 */
    NCP_INTR_GIC_NCA_GRP_1,                     /* IRQ 101 */
    NCP_INTR_GIC_NCA_GRP_2,                     /* IRQ 102 */
    NCP_INTR_GIC_NCA_GRP_3,                     /* IRQ 103 */
    NCP_INTR_GIC_NCA_GRP_4,                     /* IRQ 104 */
    NCP_INTR_GIC_NCA_GRP_5,                     /* IRQ 105 */
    NCP_INTR_GIC_NCA_GRP_6,                     /* IRQ 106 */
    NCP_INTR_GIC_NCA_GRP_7,                     /* IRQ 107 */
    NCP_INTR_GIC_NCA_GRP_8,                     /* IRQ 108 */
    NCP_INTR_GIC_NCA_GRP_9,                     /* IRQ 109 */
    NCP_INTR_GIC_NCA_GRP_10,                    /* IRQ 110 */
    NCP_INTR_GIC_NCA_GRP_11,                    /* IRQ 111 */
    NCP_INTR_GIC_NCA_GRP_12,                    /* IRQ 112 */
    NCP_INTR_GIC_NCA_GRP_13,                    /* IRQ 113 */
    NCP_INTR_GIC_NCA_GRP_14,                    /* IRQ 114 */
    NCP_INTR_GIC_NCA_GRP_15,                    /* IRQ 115 */
    NCP_INTR_GIC_NCA_HW_INT,                    /* IRQ 116 */
    NCP_INTR_GIC_TMGR_TIMER_0,                  /* IRQ 117 */
    NCP_INTR_GIC_TMGR_TIMER_1,                  /* IRQ 118 */
    NCP_INTR_GIC_TMGR_TIMER_2,                  /* IRQ 119 */
    NCP_INTR_GIC_TMGR_TIMER_3,                  /* IRQ 120 */
    NCP_INTR_GIC_TMGR_TIMER_4,                  /* IRQ 121 */
    NCP_INTR_GIC_TMGR_TIMER_5,                  /* IRQ 122 */
    NCP_INTR_GIC_TMGR_TIMER_6,                  /* IRQ 123 */
    NCP_INTR_GIC_TMGR_TIMER_7,                  /* IRQ 124 */
    NCP_INTR_GIC_TMGR_TIMER_8,                  /* IRQ 125 */
    NCP_INTR_GIC_TMGR_TIMER_9,                  /* IRQ 126 */
    NCP_INTR_GIC_TMGR_TIMER_10,                 /* IRQ 127 */
    NCP_INTR_GIC_TMGR_TIMER_11,                 /* IRQ 128 */
    NCP_INTR_GIC_TMGR_TIMER_12,                 /* IRQ 129 */
    NCP_INTR_GIC_TMGR_TIMER_13,                 /* IRQ 130 */
    NCP_INTR_GIC_TMGR_TIMER_14,                 /* IRQ 131 */
    NCP_INTR_GIC_TMGR_TIMER_15,                 /* IRQ 132 */
    NCP_INTR_GIC_TMGR_INT1_OUT,                 /* IRQ 133 */
    NCP_INTR_GIC_TMGR_INT0_OUT,                 /* IRQ 134 */
    NCP_INTR_GIC_MPPY_INTERRUPT1,               /* IRQ 135 */
    NCP_INTR_GIC_MPPY_INTERRUPT0,               /* IRQ 136 */
    NCP_INTR_GIC_EIOA0_INTERRUPT,               /* IRQ 137 */
    NCP_INTR_GIC_EIOAM1_INTERRUPT,              /* IRQ 138 */
    NCP_INTR_GIC_MTM_INTERRUPT1,                /* IRQ 139 */
    NCP_INTR_GIC_MTM_INTERRUPT0,                /* IRQ 140 */
    NCP_INTR_GIC_PAB_INT1,                      /* IRQ 141 */
    NCP_INTR_GIC_PAB_INT0,                      /* IRQ 142 */
    NCP_INTR_GIC_SED_INT1_OUT,                  /* IRQ 143 */
    NCP_INTR_GIC_SED_INT0_OUT,                  /* IRQ 144 */
    NCP_INTR_GIC_PIC_INT0_OUT,                  /* IRQ 145 */
    NCP_INTR_GIC_SPP_INT1,                      /* IRQ 146 */
    NCP_INTR_GIC_SPP_INT0,                      /* IRQ 147 */
    NCP_INTR_GIC_DPI_INT1,                      /* IRQ 148 */
    NCP_INTR_GIC_DPI_INT0,                      /* IRQ 149 */
    NCP_INTR_GIC_SM1_PLL_INTR,                  /* IRQ 150 */
    NCP_INTR_GIC_SM0_PLL_INTR,                  /* IRQ 151 */
    NCP_INTR_GIC_TM0_PLL_INTR,                  /* IRQ 152 */
    NCP_INTR_GIC_SYS_PLL_INTR,                  /* IRQ 153 */
    NCP_INTR_GIC_NTIMC_INTERRUPT,               /* IRQ 154 */
    NCP_INTR_GIC_NTEMC1_INTR,                   /* IRQ 155 */
    NCP_INTR_GIC_NTEMC0_INTR,                   /* IRQ 156 */
    NCP_INTR_GIC_MME_INTERRUPT1,                /* IRQ 157 */
    NCP_INTR_GIC_MME_INTERRUPT0,                /* IRQ 158 */
    NCP_INTR_GIC_PB_INT_OR,                     /* IRQ 159 */
    NCP_INTR_GIC_SM1_INT,                       /* IRQ 160 */
    NCP_INTR_GIC_SM0_INT,                       /* IRQ 161 */
    NCP_INTR_GIC_ELM_INT0,                      /* IRQ 162 */
    NCP_INTR_GIC_ELM_INT1,                      /* IRQ 163 */
    NCP_INTR_GIC_EIOASM0_INTERRUPT,             /* IRQ 164 */
    NCP_INTR_GIC_EIOASM1_INTERRUPT,             /* IRQ 165 */
    NCP_INTR_GIC_EIOAS2_INTERRUPT,              /* IRQ 166 */
    NCP_INTR_GIC_EIOAS3_INTERRUPT,              /* IRQ 167 */
    NCP_INTR_GIC_EIOAS4_INTERRUPT,              /* IRQ 168 */
    NCP_INTR_GIC_EIOAS5_INTERRUPT,              /* IRQ 169 */
    NCP_INTR_GIC_ISB_INTERRUPT,                 /* IRQ 170 */
    NCP_INTR_GIC_ISBS_INTERRUPT,                /* IRQ 171 */
    NCP_INTR_GIC_PBM_INTERRUPT1,                /* IRQ 172 */
    NCP_INTR_GIC_PBM_INTERRUPT0,                /* IRQ 173 */
    NCP_INTR_GIC_PCX_INT0,                      /* IRQ 174 */
    NCP_INTR_GIC_PCX_INT1,                      /* IRQ 175 */
    NCP_INTR_GIC_NRCP_PLL_INTR,                 /* IRQ 176 */
    NCP_INTR_GIC_CPU_PLL_INTR,                  /* IRQ 177 */
    NCP_INTR_GIC_FAB_PLL_INTR,                  /* IRQ 178 */
    NCP_INTR_GIC_CCM_INTERRUPT,                 /* IRQ 179 */
    NCP_INTR_GIC_CCMS_INTERRUPT,                /* IRQ 180 */
    NCP_INTR_GIC_DICKENS_INTREQ,                /* IRQ 181 */
    NCP_INTR_GIC_INTERRIRQ_0,                   /* IRQ 182 */
    NCP_INTR_GIC_INTERRIRQ_1,                   /* IRQ 183 */
    NCP_INTR_GIC_INTERRIRQ_2,                   /* IRQ 184 */
    NCP_INTR_GIC_INTERRIRQ_3,                   /* IRQ 185 */
    NCP_INTR_GIC_AXIERRIRQ_0,                   /* IRQ 186 */
    NCP_INTR_GIC_AXIERRIRQ_1,                   /* IRQ 187 */
    NCP_INTR_GIC_AXIERRIRQ_2,                   /* IRQ 188 */
    NCP_INTR_GIC_AXIERRIRQ_3,                   /* IRQ 189 */
    NCP_INTR_GIC_PMUIRQ_0,                      /* IRQ 190 */
    NCP_INTR_GIC_PMUIRQ_1,                      /* IRQ 191 */
    NCP_INTR_GIC_PMUIRQ_2,                      /* IRQ 192 */
    NCP_INTR_GIC_PMUIRQ_3,                      /* IRQ 193 */
    NCP_INTR_GIC_CTIIRQ_0,                      /* IRQ 194 */
    NCP_INTR_GIC_CTIIRQ_1,                      /* IRQ 195 */
    NCP_INTR_GIC_CTIIRQ_2,                      /* IRQ 196 */
    NCP_INTR_GIC_CTIIRQ_3,                      /* IRQ 197 */
    NCP_INTR_GIC_X7_SEND_IPI0_0,                /* IRQ 198 */
    NCP_INTR_GIC_X7_SEND_IPI0_1,                /* IRQ 199 */
    NCP_INTR_GIC_X7_SEND_IPI0_2,                /* IRQ 200 */
    NCP_INTR_GIC_X7_SEND_IPI1_0,                /* IRQ 201 */
    NCP_INTR_GIC_X7_SEND_IPI1_1,                /* IRQ 202 */
    NCP_INTR_GIC_X7_SEND_IPI1_2,                /* IRQ 203 */
    NCP_INTR_GIC_X7_SEND_IPI2_0,                /* IRQ 204 */
    NCP_INTR_GIC_X7_SEND_IPI2_1,                /* IRQ 205 */
    NCP_INTR_GIC_X7_SEND_IPI2_2,                /* IRQ 206 */
    NCP_INTR_GIC_X7_SEND_IPI3_0,                /* IRQ 207 */
    NCP_INTR_GIC_X7_SEND_IPI3_1,                /* IRQ 208 */
    NCP_INTR_GIC_X7_SEND_IPI3_2,                /* IRQ 209 */
    NCP_INTR_GIC_X7_SPARE_EXT_IRQ_0,            /* IRQ 210 */
    NCP_INTR_GIC_X7_SPARE_EXT_IRQ_1,            /* IRQ 211 */
    NCP_INTR_GIC_X7_SPARE_EXT_IRQ_2,            /* IRQ 212 */
    NCP_INTR_GIC_X7_SPARE_EXT_IRQ_3,            /* IRQ 213 */
    NCP_INTR_GIC_X7_SPARE_EXT_IRQ_4,            /* IRQ 214 */
    NCP_INTR_GIC_X7_SPARE_EXT_IRQ_5,            /* IRQ 215 */
    NCP_INTR_GIC_X7_SPARE_EXT_IRQ_6,            /* IRQ 216 */
    NCP_INTR_GIC_X7_SPARE_EXT_IRQ_7,            /* IRQ 217 */
    NCP_INTR_GIC_X7_SPARE_EXT_IRQ_8,            /* IRQ 218 */
    NCP_INTR_GIC_ZEROIZE,                       /* IRQ 219 */
    NCP_INTR_GIC_EMC_INT,                       /* IRQ 220 */
    NCP_INTR_GIC_NRCP_COLS_INT,                 /* IRQ 221 */
    NCP_INTR_GIC_X7_SPARE_EXT_IRQ_9,            /* IRQ 222 */
    NCP_INTR_GIC_X7_SPARE_EXT_IRQ_10,           /* IRQ 223 */
    NCP_INTR_GIC_MAX
};

#endif
