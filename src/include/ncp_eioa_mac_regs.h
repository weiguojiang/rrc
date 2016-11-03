/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2014, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/



#ifndef _NCP_EIOA_MAC_REGS_H_
#define _NCP_EIOA_MAC_REGS_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "ncp_sal_types.h"

/* PHY OUI */
#define NCP_MAC_PHY_OUI_UNKNOWN       0x000000
#define NCP_MAC_PHY_OUI_AGERE_ET1081  0x00053D
#define NCP_MAC_PHY_OUI_VITESSE_8634  0x008083
#define NCP_MAC_PHY_OUI_MARVELL_88E1111 0x005043
#define NCP_MAC_PHY_OUI_VITESSE_8574  0x008083

/* PHY model numbers */
#define NCP_MAC_PHY_MDL_UNKNOWN       0x00
#define NCP_MAC_PHY_MDL_ET1081        0x03
#define NCP_MAC_PHY_MDL_VSC8634       0x24
#define NCP_MAC_PHY_MDL_88E1111       0x0C
#define NCP_MAC_PHY_MDL_VSC8574       0x0A

/* PHY revision numbers */
#define NCP_MAC_PHY_REV_ET1081        0x05
#define NCP_MAC_PHY_REV_VSC8634       0x00
#define NCP_MAC_PHY_REV_88E1111       0x00
#define NCP_MAC_PHY_REV_VSC8574       0x02

/* These are specific to Agere TruePHY ET1018 SGMII PHY */
#define NCP_AGERE_INTR_MASK_REG          24
#define NCP_AGERE_INTR_STAT_REG          25
#define NCP_AGERE_PHY_STAT_REG           26

/* External MDIO Registers */
#define NCP_MAC_PHY_CTRL_REG               0
#define NCP_MAC_PHY_STAT_REG               1
#define NCP_MAC_PHY_ID1_REG                2
#define NCP_MAC_PHY_ID2_REG                3
#define NCP_MAC_PHY_AN_ADVERT_REG          4
#define NCP_MAC_PHY_AN_LP_ABLTY_REG        5
#define NCP_MAC_PHY_AN_EXP_REG             6
#define NCP_MAC_PHY_AN_NP_XMIT_REG         7
#define NCP_MAC_PHY_AN_LP_NEXT_REG         8
#define NCP_MAC_PHY_1000T_100T2_CTRL_REG   9
#define NCP_MAC_PHY_1000T_100T2_STAT_REG   10
#define NCP_MAC_PHY_EXT_STAT_REG           15

#define NCP_ADV_1G_FDX 0x0200
#define NCP_ADV_100MB_FDX 0x0100
#define NCP_ADV_100MB_HDX 0x0080
#define NCP_ADV_10MB_FDX 0x0040
#define NCP_ADV_10MB_HDX 0x0020

extern ncp_mac_phy_t ncp_mac_phys[]; 

/* Operations to MAC PHY registers */

typedef enum 
{ 
    NCP_DEV_MAC_OP_TYPE_DELAY = 1,
    NCP_DEV_MAC_OP_TYPE_READ,
    NCP_DEV_MAC_OP_TYPE_WRITE,
    NCP_DEV_MAC_OP_TYPE_ROW,
    NCP_DEV_MAC_OP_TYPE_RAW
} ncp_dev_mac_op_type_t;

typedef struct ncp_dev_mac_op_info_s {
    ncp_dev_mac_op_type_t dmo_opType;  /* address offset for the register */
    ncp_uint32_t              dmo_regAddr; /* address offset for the register */
    ncp_uint32_t              dmo_opValue; /* value for the operation */
} ncp_dev_mac_op_info_t;

typedef struct ncp_mac_phy_id1_s {
#ifdef NCP_BIG_ENDIAN
    unsigned rsvd            :16;
    unsigned oui_2_17        :16;
#else
    unsigned oui_2_17        :16;
    unsigned rsvd            :16;
#endif
} ncp_mac_phy_id1_t;

typedef struct ncp_mac_phy_id2_s {
#ifdef NCP_BIG_ENDIAN
    unsigned rsvd            :16;
    unsigned oui_18_23       :6;
    unsigned model           :6;
    unsigned revision        :4;
#else
    unsigned revision        :4;
    unsigned model           :6;
    unsigned oui_18_23       :6;
    unsigned rsvd            :16;
#endif
} ncp_mac_phy_id2_t;

typedef struct ncp_mac_phy_ctrl_s {
#ifdef NCP_BIG_ENDIAN
    unsigned rsvd2           :16;
    unsigned reset           :1;
    unsigned loopBack        :1;
    unsigned speedBit0       :1;
    unsigned autoNegEnable   :1;
    unsigned powerDown       :1;
    unsigned isolate         :1;
    unsigned autoNegRestart  :1;
    unsigned duplex          :1;
    unsigned collisionTest   :1;
    unsigned speedBit1       :1;
    unsigned rsvd1           :6;
#else
    unsigned rsvd1           :6;
    unsigned speedBit1       :1;
    unsigned collisionTest   :1;
    unsigned duplex          :1;
    unsigned autoNegRestart  :1;
    unsigned isolate         :1;
    unsigned powerDown       :1;
    unsigned autoNegEnable   :1;
    unsigned speedBit0       :1;
    unsigned loopBack        :1;
    unsigned reset           :1;
    unsigned rsvd2           :16;
#endif
} ncp_mac_phy_ctrl_t;

typedef struct ncp_mac_phy_stat_s {
#ifdef NCP_BIG_ENDIAN
    unsigned rsvd2           :16;
    unsigned base100T4       :1;
    unsigned base100Xfull    :1;
    unsigned base100Xhalf    :1;
    unsigned base10full      :1;
    unsigned base10half      :1;
    unsigned base100T2full   :1;
    unsigned base100T2half   :1;
    unsigned extendedStatus  :1;
    unsigned rsvd1           :1;
    unsigned mfPreSupp       :1;
    unsigned autoNegDone     :1;
    unsigned remoteFault     :1;
    unsigned autoNegAble     :1;
    unsigned linkStatus      :1;
    unsigned jabberDetect    :1;
    unsigned extendedCapable :1;
#else
    unsigned extendedCapable :1;
    unsigned jabberDetect    :1;
    unsigned linkStatus      :1;
    unsigned autoNegAble     :1;
    unsigned remoteFault     :1;
    unsigned autoNegDone     :1;
    unsigned mfPreSupp       :1;
    unsigned rsvd1           :1;
    unsigned extendedStatus  :1;
    unsigned base100T2half   :1;
    unsigned base100T2full   :1;
    unsigned base10half      :1;
    unsigned base10full      :1;
    unsigned base100Xhalf    :1;
    unsigned base100Xfull    :1;
    unsigned base100T4       :1;
    unsigned rsvd2           :16;
#endif
} ncp_mac_phy_stat_t;

typedef struct ncp_mac_phy_an_advert_s {
#ifdef NCP_BIG_ENDIAN
    unsigned rsvd3           :16;
    unsigned nextPage        :1;
    unsigned rsvd2           :1;
    unsigned remoteFault     :2;
    unsigned asymPause       :1;
    unsigned pause           :1;
    unsigned cap100BaseT4    :1;
    unsigned cap100BaseTxFull:1;
    unsigned cap100BaseTx    :1;
    unsigned cap10BaseTFull  :1;
    unsigned cap10BaseT      :1;
    unsigned rsvd1           :5;
#else
    unsigned rsvd1           :5;
    unsigned cap10BaseT      :1;
    unsigned cap10BaseTFull  :1;
    unsigned cap100BaseTx    :1;
    unsigned cap100BaseTxFull:1;
    unsigned cap100BaseT4    :1;
    unsigned pause           :1;
    unsigned asymPause       :1;
    unsigned remoteFault     :2;
    unsigned rsvd2           :1;
    unsigned nextPage        :1;
    unsigned rsvd3           :16;
#endif
} ncp_mac_phy_an_advert_t;

typedef struct ncp_mac_phy_an_link_ability_s {
#ifdef NCP_BIG_ENDIAN
    unsigned rsvd            :16;
    unsigned nextPage        :1;
    unsigned acknowledge     :1;
    unsigned remoteFault     :2;
    unsigned lpAsmDir        :1;
    unsigned pause           :1;
    unsigned cap100BaseT4    :1;
    unsigned cap100BaseTxFull:1;
    unsigned cap100BaseTx    :1;
    unsigned cap10BaseTFull  :1;
    unsigned cap10BaseT      :1;
    unsigned selector        :5;
#else
    unsigned selector        :5;
    unsigned cap10BaseT      :1;
    unsigned cap10BaseTFull  :1;
    unsigned cap100BaseTx    :1;
    unsigned cap100BaseTxFull:1;
    unsigned cap100BaseT4    :1;
    unsigned pause           :1;
    unsigned lpAsmDir        :1;
    unsigned remoteFault     :2;
    unsigned acknowledge     :1;
    unsigned nextPage        :1;
    unsigned rsvd            :16;
#endif
} ncp_mac_phy_an_link_ability_t;

typedef struct ncp_mac_phy_1000T_ctrl_s {
#ifdef NCP_BIG_ENDIAN
    unsigned rsvd2           :16;
    unsigned tst_mode        :3;
    unsigned master_slv_en   :1;
    unsigned phy_master      :1;
    unsigned port_type       :1;
    unsigned base1000Tfull   :1;
    unsigned base1000Thalf   :1;
    unsigned rsvd1           :8;
#else
    unsigned rsvd1           :8;
    unsigned base1000Thalf   :1;
    unsigned base1000Tfull   :1;
    unsigned port_type       :1;
    unsigned phy_master      :1;
    unsigned master_slv_en   :1;
    unsigned tst_mode        :3;
    unsigned rsvd2           :16;
#endif
} ncp_mac_phy_1000T_ctrl_t;

typedef struct ncp_mac_phy_ext_stat_s {
#ifdef NCP_BIG_ENDIAN
    unsigned rsvd2           :16;
    unsigned base1000Xfull   :1;
    unsigned base1000Xhalf   :1;
    unsigned base1000Tfull   :1;
    unsigned base1000Thalf   :1;
    unsigned rsvd1           :12;
#else
    unsigned rsvd1           :12;
    unsigned base1000Thalf   :1;
    unsigned base1000Tfull   :1;
    unsigned base1000Xhalf   :1;
    unsigned base1000Xfull   :1;
    unsigned rsvd2           :16;
#endif
} ncp_mac_phy_ext_stat_t;

/*
 * ncp_nemac1_gmac_nem_gmac_control_25_r_t
 *  Clause 73 AN Control Register 
 */
typedef struct ncp_mac_c73_an_ctrl_s 
{
#ifdef NCP_BIG_ENDIAN
    unsigned rsvd4              :16;
    unsigned an_reset           :1;
    unsigned rsvd3              :2;
    unsigned an_en              :1;
    unsigned rsvd2              :2;
    unsigned restart_an         :1;
    unsigned tmr_speed_up       :1;
    unsigned rsvd1              :6;
    unsigned link_incompatible  :1;
    unsigned link_hcd_ok        :1;
#else
    unsigned link_hcd_ok        :1;
    unsigned link_incompatible  :1;
    unsigned rsvd1              :6;
    unsigned tmr_speed_up       :1;
    unsigned restart_an         :1;
    unsigned rsvd2              :2;
    unsigned an_en              :1;
    unsigned rsvd3              :2;
    unsigned an_reset           :1;
    unsigned rsvd4               :16;
#endif
} ncp_mac_c73_an_ctrl_t;

/*
 * ncp_nemac1_gmac_nem_gmac_control_26_r_t
 *  Clause 73 AN Status Register 
 */
typedef struct ncp_mac_c73_an_status_s {
#ifdef NCP_BIG_ENDIAN
    unsigned rsvd                   :17;
    unsigned los_chg                :1;
    unsigned an_compl_chg           :1;
    unsigned link_status_chg        :1;
    unsigned restart_an_fault       :1;
    unsigned an_link_ok             :1;
    unsigned los_status             :1;
    unsigned nonce_fail             :1;
    unsigned parl_detect_fault      :1;
    unsigned parl_detect_complete   :1;
    unsigned page_rcvd              :1;
    unsigned an_complete            :1;
    unsigned rem_fault              :1;
    unsigned loc_an_ability         :1;
    unsigned loc_link_status        :1;
    unsigned rem_an_ability         :1;
#else
    unsigned rem_an_ability         :1;
    unsigned loc_link_status        :1;
    unsigned loc_an_ability         :1;
    unsigned rem_fault              :1;
    unsigned an_complete            :1;
    unsigned page_rcvd              :1;
    unsigned parl_detect_complete   :1;
    unsigned parl_detect_fault      :1;
    unsigned nonce_fail             :1;
    unsigned los_status             :1;
    unsigned an_link_ok             :1;
    unsigned restart_an_fault       :1;
    unsigned link_status_chg        :1;
    unsigned an_compl_chg           :1;
    unsigned los_chg                :1;
    unsigned rsvd                   :17;
#endif
} ncp_mac_c73_an_status_t;

#ifdef __cplusplus
}
#endif

#endif /* _NCP_EIOA_MAC_REGS_H_ */
