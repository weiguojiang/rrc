# Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University
# Copyright (c) 2011, 2012 Open Networking Foundation
# Copyright (c) 2012, 2013 Big Switch Networks, Inc.
# See the file LICENSE.pyloxi which should have been included in the source distribution

# Automatically generated by LOXI from template const.py
# Do not modify

OFP_VERSION = 1

# Identifiers from group macro_definitions
OFP_MAX_TABLE_NAME_LEN = 32
OFP_MAX_PORT_NAME_LEN = 16
OFP_TCP_PORT = 6653
OFP_SSL_PORT = 6653
OFP_ETH_ALEN = 6
OFP_DEFAULT_MISS_SEND_LEN = 128
OFP_VLAN_NONE = 65535
OFPFW_ICMP_TYPE = 64
OFPFW_ICMP_CODE = 128
OFP_DL_TYPE_ETH2_CUTOFF = 1536
OFP_DL_TYPE_NOT_ETH_TYPE = 1535
OFP_FLOW_PERMANENT = 0
OFP_DEFAULT_PRIORITY = 32768
DESC_STR_LEN = 256
SERIAL_NUM_LEN = 32
OFPQ_ALL = 4294967295
OFPQ_MIN_RATE_UNCFG = 65535

# Identifiers from group of_bsn_pdu_slot_num
BSN_PDU_SLOT_NUM_ANY = 255

of_bsn_pdu_slot_num_map = {
    255: 'BSN_PDU_SLOT_NUM_ANY',
}

# Identifiers from group ofp_action_type
OFPAT_OUTPUT = 0
OFPAT_SET_VLAN_VID = 1
OFPAT_SET_VLAN_PCP = 2
OFPAT_STRIP_VLAN = 3
OFPAT_SET_DL_SRC = 4
OFPAT_SET_DL_DST = 5
OFPAT_SET_NW_SRC = 6
OFPAT_SET_NW_DST = 7
OFPAT_SET_NW_TOS = 8
OFPAT_SET_TP_SRC = 9
OFPAT_SET_TP_DST = 10
OFPAT_ENQUEUE = 11
OFPAT_EXPERIMENTER = 65535

ofp_action_type_map = {
    0: 'OFPAT_OUTPUT',
    1: 'OFPAT_SET_VLAN_VID',
    2: 'OFPAT_SET_VLAN_PCP',
    3: 'OFPAT_STRIP_VLAN',
    4: 'OFPAT_SET_DL_SRC',
    5: 'OFPAT_SET_DL_DST',
    6: 'OFPAT_SET_NW_SRC',
    7: 'OFPAT_SET_NW_DST',
    8: 'OFPAT_SET_NW_TOS',
    9: 'OFPAT_SET_TP_SRC',
    10: 'OFPAT_SET_TP_DST',
    11: 'OFPAT_ENQUEUE',
    65535: 'OFPAT_EXPERIMENTER',
}

# Identifiers from group ofp_bad_action_code
OFPBAC_BAD_TYPE = 0
OFPBAC_BAD_LEN = 1
OFPBAC_BAD_EXPERIMENTER = 2
OFPBAC_BAD_EXPERIMENTER_TYPE = 3
OFPBAC_BAD_OUT_PORT = 4
OFPBAC_BAD_ARGUMENT = 5
OFPBAC_EPERM = 6
OFPBAC_TOO_MANY = 7
OFPBAC_BAD_QUEUE = 8

ofp_bad_action_code_map = {
    0: 'OFPBAC_BAD_TYPE',
    1: 'OFPBAC_BAD_LEN',
    2: 'OFPBAC_BAD_EXPERIMENTER',
    3: 'OFPBAC_BAD_EXPERIMENTER_TYPE',
    4: 'OFPBAC_BAD_OUT_PORT',
    5: 'OFPBAC_BAD_ARGUMENT',
    6: 'OFPBAC_EPERM',
    7: 'OFPBAC_TOO_MANY',
    8: 'OFPBAC_BAD_QUEUE',
}

# Identifiers from group ofp_bad_request_code
OFPBRC_BAD_VERSION = 0
OFPBRC_BAD_TYPE = 1
OFPBRC_BAD_STAT = 2
OFPBRC_BAD_EXPERIMENTER = 3
OFPBRC_BAD_SUBTYPE = 4
OFPBRC_EPERM = 5
OFPBRC_BAD_LEN = 6
OFPBRC_BUFFER_EMPTY = 7
OFPBRC_BUFFER_UNKNOWN = 8

ofp_bad_request_code_map = {
    0: 'OFPBRC_BAD_VERSION',
    1: 'OFPBRC_BAD_TYPE',
    2: 'OFPBRC_BAD_STAT',
    3: 'OFPBRC_BAD_EXPERIMENTER',
    4: 'OFPBRC_BAD_SUBTYPE',
    5: 'OFPBRC_EPERM',
    6: 'OFPBRC_BAD_LEN',
    7: 'OFPBRC_BUFFER_EMPTY',
    8: 'OFPBRC_BUFFER_UNKNOWN',
}

# Identifiers from group ofp_bsn_vport_l2gre_flags
OF_BSN_VPORT_L2GRE_LOCAL_MAC_IS_VALID = 1
OF_BSN_VPORT_L2GRE_DSCP_ASSIGN = 2
OF_BSN_VPORT_L2GRE_DSCP_COPY = 4
OF_BSN_VPORT_L2GRE_LOOPBACK_IS_VALID = 8
OF_BSN_VPORT_L2GRE_RATE_LIMIT_IS_VALID = 16

ofp_bsn_vport_l2gre_flags_map = {
    1: 'OF_BSN_VPORT_L2GRE_LOCAL_MAC_IS_VALID',
    2: 'OF_BSN_VPORT_L2GRE_DSCP_ASSIGN',
    4: 'OF_BSN_VPORT_L2GRE_DSCP_COPY',
    8: 'OF_BSN_VPORT_L2GRE_LOOPBACK_IS_VALID',
    16: 'OF_BSN_VPORT_L2GRE_RATE_LIMIT_IS_VALID',
}

# Identifiers from group ofp_bsn_vport_q_in_q_untagged
OF_BSN_VPORT_Q_IN_Q_UNTAGGED = 65535

ofp_bsn_vport_q_in_q_untagged_map = {
    65535: 'OF_BSN_VPORT_Q_IN_Q_UNTAGGED',
}

# Identifiers from group ofp_bsn_vport_status
OF_BSN_VPORT_STATUS_OK = 0
OF_BSN_VPORT_STATUS_FAILED = 1

ofp_bsn_vport_status_map = {
    0: 'OF_BSN_VPORT_STATUS_OK',
    1: 'OF_BSN_VPORT_STATUS_FAILED',
}

# Identifiers from group ofp_capabilities
OFPC_FLOW_STATS = 1
OFPC_TABLE_STATS = 2
OFPC_PORT_STATS = 4
OFPC_STP = 8
OFPC_RESERVED = 16
OFPC_IP_REASM = 32
OFPC_QUEUE_STATS = 64
OFPC_ARP_MATCH_IP = 128

ofp_capabilities_map = {
    1: 'OFPC_FLOW_STATS',
    2: 'OFPC_TABLE_STATS',
    4: 'OFPC_PORT_STATS',
    8: 'OFPC_STP',
    16: 'OFPC_RESERVED',
    32: 'OFPC_IP_REASM',
    64: 'OFPC_QUEUE_STATS',
    128: 'OFPC_ARP_MATCH_IP',
}

# Identifiers from group ofp_config_flags
OFPC_FRAG_NORMAL = 0
OFPC_FRAG_DROP = 1
OFPC_FRAG_REASM = 2
OFPC_FRAG_MASK = 3

ofp_config_flags_map = {
    0: 'OFPC_FRAG_NORMAL',
    1: 'OFPC_FRAG_DROP',
    2: 'OFPC_FRAG_REASM',
    3: 'OFPC_FRAG_MASK',
}

# Identifiers from group ofp_error_type
OFPET_HELLO_FAILED = 0
OFPET_BAD_REQUEST = 1
OFPET_BAD_ACTION = 2
OFPET_FLOW_MOD_FAILED = 3
OFPET_PORT_MOD_FAILED = 4
OFPET_QUEUE_OP_FAILED = 5

ofp_error_type_map = {
    0: 'OFPET_HELLO_FAILED',
    1: 'OFPET_BAD_REQUEST',
    2: 'OFPET_BAD_ACTION',
    3: 'OFPET_FLOW_MOD_FAILED',
    4: 'OFPET_PORT_MOD_FAILED',
    5: 'OFPET_QUEUE_OP_FAILED',
}

# Identifiers from group ofp_flow_mod_command
OFPFC_ADD = 0
OFPFC_MODIFY = 1
OFPFC_MODIFY_STRICT = 2
OFPFC_DELETE = 3
OFPFC_DELETE_STRICT = 4

ofp_flow_mod_command_map = {
    0: 'OFPFC_ADD',
    1: 'OFPFC_MODIFY',
    2: 'OFPFC_MODIFY_STRICT',
    3: 'OFPFC_DELETE',
    4: 'OFPFC_DELETE_STRICT',
}

# Identifiers from group ofp_flow_mod_failed_code
OFPFMFC_ALL_TABLES_FULL = 0
OFPFMFC_OVERLAP = 1
OFPFMFC_EPERM = 2
OFPFMFC_BAD_EMERG_TIMEOUT = 3
OFPFMFC_BAD_COMMAND = 4
OFPFMFC_UNSUPPORTED = 5

ofp_flow_mod_failed_code_map = {
    0: 'OFPFMFC_ALL_TABLES_FULL',
    1: 'OFPFMFC_OVERLAP',
    2: 'OFPFMFC_EPERM',
    3: 'OFPFMFC_BAD_EMERG_TIMEOUT',
    4: 'OFPFMFC_BAD_COMMAND',
    5: 'OFPFMFC_UNSUPPORTED',
}

# Identifiers from group ofp_flow_mod_flags
OFPFF_SEND_FLOW_REM = 1
OFPFF_CHECK_OVERLAP = 2
OFPFF_EMERG = 4

ofp_flow_mod_flags_map = {
    1: 'OFPFF_SEND_FLOW_REM',
    2: 'OFPFF_CHECK_OVERLAP',
    4: 'OFPFF_EMERG',
}

# Identifiers from group ofp_flow_removed_reason
OFPRR_IDLE_TIMEOUT = 0
OFPRR_HARD_TIMEOUT = 1
OFPRR_DELETE = 2

ofp_flow_removed_reason_map = {
    0: 'OFPRR_IDLE_TIMEOUT',
    1: 'OFPRR_HARD_TIMEOUT',
    2: 'OFPRR_DELETE',
}

# Identifiers from group ofp_flow_wildcards
OFPFW_IN_PORT = 1
OFPFW_DL_VLAN = 2
OFPFW_DL_SRC = 4
OFPFW_NW_DST_BITS = 6
OFPFW_NW_SRC_BITS = 6
OFPFW_NW_SRC_SHIFT = 8
OFPFW_DL_DST = 8
OFPFW_NW_DST_SHIFT = 14
OFPFW_DL_TYPE = 16
OFPFW_NW_PROTO = 32
OFPFW_TP_SRC = 64
OFPFW_TP_DST = 128
OFPFW_NW_SRC_ALL = 8192
OFPFW_NW_SRC_MASK = 16128
OFPFW_NW_DST_ALL = 524288
OFPFW_NW_DST_MASK = 1032192
OFPFW_DL_VLAN_PCP = 1048576
OFPFW_NW_TOS = 2097152
OFPFW_ALL = 4194303

ofp_flow_wildcards_map = {
    1: 'OFPFW_IN_PORT',
    2: 'OFPFW_DL_VLAN',
    4: 'OFPFW_DL_SRC',
    8: 'OFPFW_DL_DST',
    16: 'OFPFW_DL_TYPE',
    32: 'OFPFW_NW_PROTO',
    64: 'OFPFW_TP_SRC',
    128: 'OFPFW_TP_DST',
    1048576: 'OFPFW_DL_VLAN_PCP',
    2097152: 'OFPFW_NW_TOS',
}

# Identifiers from group ofp_hello_failed_code
OFPHFC_INCOMPATIBLE = 0
OFPHFC_EPERM = 1

ofp_hello_failed_code_map = {
    0: 'OFPHFC_INCOMPATIBLE',
    1: 'OFPHFC_EPERM',
}

# Identifiers from group ofp_nicira_controller_role
NX_ROLE_OTHER = 0
NX_ROLE_MASTER = 1
NX_ROLE_SLAVE = 2

ofp_nicira_controller_role_map = {
    0: 'NX_ROLE_OTHER',
    1: 'NX_ROLE_MASTER',
    2: 'NX_ROLE_SLAVE',
}

# Identifiers from group ofp_packet_in_reason
OFPR_NO_MATCH = 0
OFPR_ACTION = 1

ofp_packet_in_reason_map = {
    0: 'OFPR_NO_MATCH',
    1: 'OFPR_ACTION',
}

# Identifiers from group ofp_port
OFPP_MAX = 0xff00
OFPP_IN_PORT = 0xfff8
OFPP_TABLE = 0xfff9
OFPP_NORMAL = 0xfffa
OFPP_FLOOD = 0xfffb
OFPP_ALL = 0xfffc
OFPP_CONTROLLER = 0xfffd
OFPP_LOCAL = 0xfffe
OFPP_NONE = 0xffff

ofp_port_map = {
    0xff00: 'OFPP_MAX',
    0xfff8: 'OFPP_IN_PORT',
    0xfff9: 'OFPP_TABLE',
    0xfffa: 'OFPP_NORMAL',
    0xfffb: 'OFPP_FLOOD',
    0xfffc: 'OFPP_ALL',
    0xfffd: 'OFPP_CONTROLLER',
    0xfffe: 'OFPP_LOCAL',
    0xffff: 'OFPP_NONE',
}

# Identifiers from group ofp_port_config
OFPPC_PORT_DOWN = 1
OFPPC_NO_STP = 2
OFPPC_NO_RECV = 4
OFPPC_NO_RECV_STP = 8
OFPPC_NO_FLOOD = 16
OFPPC_NO_FWD = 32
OFPPC_NO_PACKET_IN = 64
OFPPC_BSN_MIRROR_DEST = 2147483648

ofp_port_config_map = {
    1: 'OFPPC_PORT_DOWN',
    2: 'OFPPC_NO_STP',
    4: 'OFPPC_NO_RECV',
    8: 'OFPPC_NO_RECV_STP',
    16: 'OFPPC_NO_FLOOD',
    32: 'OFPPC_NO_FWD',
    64: 'OFPPC_NO_PACKET_IN',
    2147483648: 'OFPPC_BSN_MIRROR_DEST',
}

# Identifiers from group ofp_port_features
OFPPF_10MB_HD = 1
OFPPF_10MB_FD = 2
OFPPF_100MB_HD = 4
OFPPF_100MB_FD = 8
OFPPF_1GB_HD = 16
OFPPF_1GB_FD = 32
OFPPF_10GB_FD = 64
OFPPF_COPPER = 128
OFPPF_FIBER = 256
OFPPF_AUTONEG = 512
OFPPF_PAUSE = 1024
OFPPF_PAUSE_ASYM = 2048

ofp_port_features_map = {
    1: 'OFPPF_10MB_HD',
    2: 'OFPPF_10MB_FD',
    4: 'OFPPF_100MB_HD',
    8: 'OFPPF_100MB_FD',
    16: 'OFPPF_1GB_HD',
    32: 'OFPPF_1GB_FD',
    64: 'OFPPF_10GB_FD',
    128: 'OFPPF_COPPER',
    256: 'OFPPF_FIBER',
    512: 'OFPPF_AUTONEG',
    1024: 'OFPPF_PAUSE',
    2048: 'OFPPF_PAUSE_ASYM',
}

# Identifiers from group ofp_port_mod_failed_code
OFPPMFC_BAD_PORT = 0
OFPPMFC_BAD_HW_ADDR = 1

ofp_port_mod_failed_code_map = {
    0: 'OFPPMFC_BAD_PORT',
    1: 'OFPPMFC_BAD_HW_ADDR',
}

# Identifiers from group ofp_port_reason
OFPPR_ADD = 0
OFPPR_DELETE = 1
OFPPR_MODIFY = 2

ofp_port_reason_map = {
    0: 'OFPPR_ADD',
    1: 'OFPPR_DELETE',
    2: 'OFPPR_MODIFY',
}

# Identifiers from group ofp_port_state
OFPPS_LINK_DOWN = 1
OFPPS_STP_LISTEN = 0
OFPPS_STP_LEARN = 256
OFPPS_STP_FORWARD = 512
OFPPS_STP_BLOCK = 768
OFPPS_STP_MASK = 768

ofp_port_state_map = {
    1: 'OFPPS_LINK_DOWN',
    0: 'OFPPS_STP_LISTEN',
    256: 'OFPPS_STP_LEARN',
    512: 'OFPPS_STP_FORWARD',
    768: 'OFPPS_STP_BLOCK',
    768: 'OFPPS_STP_MASK',
}

# Identifiers from group ofp_queue_op_failed_code
OFPQOFC_BAD_PORT = 0
OFPQOFC_BAD_QUEUE = 1
OFPQOFC_EPERM = 2

ofp_queue_op_failed_code_map = {
    0: 'OFPQOFC_BAD_PORT',
    1: 'OFPQOFC_BAD_QUEUE',
    2: 'OFPQOFC_EPERM',
}

# Identifiers from group ofp_queue_properties
OFPQT_NONE = 0
OFPQT_MIN_RATE = 1

ofp_queue_properties_map = {
    0: 'OFPQT_NONE',
    1: 'OFPQT_MIN_RATE',
}

# Identifiers from group ofp_stats_reply_flags
OFPSF_REPLY_MORE = 1

ofp_stats_reply_flags_map = {
    1: 'OFPSF_REPLY_MORE',
}

# Identifiers from group ofp_stats_request_flags

ofp_stats_request_flags_map = {
}

# Identifiers from group ofp_stats_type
OFPST_DESC = 0
OFPST_FLOW = 1
OFPST_AGGREGATE = 2
OFPST_TABLE = 3
OFPST_PORT = 4
OFPST_QUEUE = 5
OFPST_EXPERIMENTER = 65535

ofp_stats_type_map = {
    0: 'OFPST_DESC',
    1: 'OFPST_FLOW',
    2: 'OFPST_AGGREGATE',
    3: 'OFPST_TABLE',
    4: 'OFPST_PORT',
    5: 'OFPST_QUEUE',
    65535: 'OFPST_EXPERIMENTER',
}

# Identifiers from group ofp_type
OFPT_HELLO = 0
OFPT_ERROR = 1
OFPT_ECHO_REQUEST = 2
OFPT_ECHO_REPLY = 3
OFPT_EXPERIMENTER = 4
OFPT_FEATURES_REQUEST = 5
OFPT_FEATURES_REPLY = 6
OFPT_GET_CONFIG_REQUEST = 7
OFPT_GET_CONFIG_REPLY = 8
OFPT_SET_CONFIG = 9
OFPT_PACKET_IN = 10
OFPT_FLOW_REMOVED = 11
OFPT_PORT_STATUS = 12
OFPT_PACKET_OUT = 13
OFPT_FLOW_MOD = 14
OFPT_PORT_MOD = 15
OFPT_STATS_REQUEST = 16
OFPT_STATS_REPLY = 17
OFPT_BARRIER_REQUEST = 18
OFPT_BARRIER_REPLY = 19
OFPT_QUEUE_GET_CONFIG_REQUEST = 20
OFPT_QUEUE_GET_CONFIG_REPLY = 21

ofp_type_map = {
    0: 'OFPT_HELLO',
    1: 'OFPT_ERROR',
    2: 'OFPT_ECHO_REQUEST',
    3: 'OFPT_ECHO_REPLY',
    4: 'OFPT_EXPERIMENTER',
    5: 'OFPT_FEATURES_REQUEST',
    6: 'OFPT_FEATURES_REPLY',
    7: 'OFPT_GET_CONFIG_REQUEST',
    8: 'OFPT_GET_CONFIG_REPLY',
    9: 'OFPT_SET_CONFIG',
    10: 'OFPT_PACKET_IN',
    11: 'OFPT_FLOW_REMOVED',
    12: 'OFPT_PORT_STATUS',
    13: 'OFPT_PACKET_OUT',
    14: 'OFPT_FLOW_MOD',
    15: 'OFPT_PORT_MOD',
    16: 'OFPT_STATS_REQUEST',
    17: 'OFPT_STATS_REPLY',
    18: 'OFPT_BARRIER_REQUEST',
    19: 'OFPT_BARRIER_REPLY',
    20: 'OFPT_QUEUE_GET_CONFIG_REQUEST',
    21: 'OFPT_QUEUE_GET_CONFIG_REPLY',
}

