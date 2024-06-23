/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 */

#ifndef HINIC_MGMT_INTERFACE_H
#define HINIC_MGMT_INTERFACE_H

#include "nic_cfg_comm.h"
#include "mgmt_msg_base.h"

#ifndef ETH_ALEN
#define ETH_ALEN 6
#endif

#define HINIC3_CMD_OP_SET	1
#define HINIC3_CMD_OP_GET	0

#define HINIC3_CMD_OP_ADD	1
#define HINIC3_CMD_OP_DEL	0

#ifndef BIT
#define BIT(n) (1UL << (n))
#endif

enum nic_feature_cap {
	NIC_F_CSUM = BIT(0),
	NIC_F_SCTP_CRC = BIT(1),
	NIC_F_TSO = BIT(2),
	NIC_F_LRO = BIT(3),
	NIC_F_UFO = BIT(4),
	NIC_F_RSS = BIT(5),
	NIC_F_RX_VLAN_FILTER = BIT(6),
	NIC_F_RX_VLAN_STRIP = BIT(7),
	NIC_F_TX_VLAN_INSERT = BIT(8),
	NIC_F_VXLAN_OFFLOAD = BIT(9),
	NIC_F_IPSEC_OFFLOAD = BIT(10),
	NIC_F_FDIR = BIT(11),
	NIC_F_PROMISC = BIT(12),
	NIC_F_ALLMULTI = BIT(13),
	NIC_F_XSFP_REPORT = BIT(14),
	NIC_F_VF_MAC = BIT(15),
	NIC_F_RATE_LIMIT = BIT(16),
	NIC_F_RXQ_RECOVERY = BIT(17),
};

#define NIC_F_ALL_MASK 0x3FFFF /* 使能所有属性 */

struct hinic3_mgmt_msg_head {
	u8 status;
	u8 version;
	u8 rsvd0[6];
};

#define NIC_MAX_FEATURE_QWORD	4
struct hinic3_cmd_feature_nego {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u8 opcode; /* 1: set, 0: get */
	u8 rsvd;
	u64 s_feature[NIC_MAX_FEATURE_QWORD];
};

struct hinic3_port_mac_set {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u16 vlan_id;
	u16 rsvd1;
	u8 mac[ETH_ALEN];
};

struct hinic3_port_mac_update {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u16 vlan_id;
	u16 rsvd1;
	u8 old_mac[ETH_ALEN];
	u16 rsvd2;
	u8 new_mac[ETH_ALEN];
};

struct hinic3_vport_state {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u16 rsvd1;
	u8 state; /* 0--disable, 1--enable */
	u8 rsvd2[3];
};

struct hinic3_port_state {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u16 rsvd1;
	u8 state; /* 0--disable, 1--enable */
	u8 rsvd2[3];
};

#define HINIC3_SET_PORT_CAR_PROFILE 0
#define HINIC3_SET_PORT_CAR_STATE 1

struct hinic3_port_car_info {
	u32 cir; /* unit: kbps, range:[1,400*1000*1000], i.e. 1Kbps~400Gbps(400M*kbps) */
	u32 xir; /* unit: kbps, range:[1,400*1000*1000], i.e. 1Kbps~400Gbps(400M*kbps) */
	u32 cbs; /* unit: Byte, range:[1,320*1000*1000], i.e. 1byte~2560Mbit */
	u32 xbs; /* unit: Byte, range:[1,320*1000*1000], i.e. 1byte~2560Mbit */
};

struct hinic3_cmd_set_port_car {
	struct hinic3_mgmt_msg_head msg_head;

	u8 port_id;
	u8 opcode; /* 0--set car profile, 1--set car state */
	u8 state; /* 0--disable, 1--enable */
	u8 rsvd;

	struct hinic3_port_car_info car;
};

struct hinic3_cmd_clear_qp_resource {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u16 rsvd1;
};

struct hinic3_cmd_cache_out_qp_resource {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u16 rsvd1;
};

struct hinic3_port_stats_info {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u16 rsvd1;
};

struct hinic3_vport_stats {
	u64 tx_unicast_pkts_vport;
	u64 tx_unicast_bytes_vport;
	u64 tx_multicast_pkts_vport;
	u64 tx_multicast_bytes_vport;
	u64 tx_broadcast_pkts_vport;
	u64 tx_broadcast_bytes_vport;

	u64 rx_unicast_pkts_vport;
	u64 rx_unicast_bytes_vport;
	u64 rx_multicast_pkts_vport;
	u64 rx_multicast_bytes_vport;
	u64 rx_broadcast_pkts_vport;
	u64 rx_broadcast_bytes_vport;

	u64 tx_discard_vport;
	u64 rx_discard_vport;
	u64 tx_err_vport;
	u64 rx_err_vport;
};

struct hinic3_phy_fpga_port_stats {
	u64 mac_rx_total_octs_port;
	u64 mac_tx_total_octs_port;
	u64 mac_rx_under_frame_pkts_port;
	u64 mac_rx_frag_pkts_port;
	u64 mac_rx_64_oct_pkts_port;
	u64 mac_rx_127_oct_pkts_port;
	u64 mac_rx_255_oct_pkts_port;
	u64 mac_rx_511_oct_pkts_port;
	u64 mac_rx_1023_oct_pkts_port;
	u64 mac_rx_max_oct_pkts_port;
	u64 mac_rx_over_oct_pkts_port;
	u64 mac_tx_64_oct_pkts_port;
	u64 mac_tx_127_oct_pkts_port;
	u64 mac_tx_255_oct_pkts_port;
	u64 mac_tx_511_oct_pkts_port;
	u64 mac_tx_1023_oct_pkts_port;
	u64 mac_tx_max_oct_pkts_port;
	u64 mac_tx_over_oct_pkts_port;
	u64 mac_rx_good_pkts_port;
	u64 mac_rx_crc_error_pkts_port;
	u64 mac_rx_broadcast_ok_port;
	u64 mac_rx_multicast_ok_port;
	u64 mac_rx_mac_frame_ok_port;
	u64 mac_rx_length_err_pkts_port;
	u64 mac_rx_vlan_pkts_port;
	u64 mac_rx_pause_pkts_port;
	u64 mac_rx_unknown_mac_frame_port;
	u64 mac_tx_good_pkts_port;
	u64 mac_tx_broadcast_ok_port;
	u64 mac_tx_multicast_ok_port;
	u64 mac_tx_underrun_pkts_port;
	u64 mac_tx_mac_frame_ok_port;
	u64 mac_tx_vlan_pkts_port;
	u64 mac_tx_pause_pkts_port;
};

struct hinic3_port_stats {
	struct hinic3_mgmt_msg_head msg_head;

	struct hinic3_phy_fpga_port_stats stats;
};

struct hinic3_cmd_vport_stats {
	struct hinic3_mgmt_msg_head msg_head;

	u32 stats_size;
	u32 rsvd1;
	struct hinic3_vport_stats stats;
	u64 rsvd2[6];
};

struct hinic3_cmd_qpn {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u16 base_qpn;
};

enum hinic3_func_tbl_cfg_bitmap {
	FUNC_CFG_INIT,
	FUNC_CFG_RX_BUF_SIZE,
	FUNC_CFG_MTU,
};

struct hinic3_func_tbl_cfg {
	u16 rx_wqe_buf_size;
	u16 mtu;
	u32 rsvd[9];
};

struct hinic3_cmd_set_func_tbl {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u16 rsvd;

	u32 cfg_bitmap;
	struct hinic3_func_tbl_cfg tbl_cfg;
};

struct hinic3_cmd_cons_idx_attr {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_idx;
	u8 dma_attr_off;
	u8 pending_limit;
	u8 coalescing_time;
	u8 intr_en;
	u16 intr_idx;
	u32 l2nic_sqn;
	u32 rsvd;
	u64 ci_addr;
};

struct hinic3_cmd_vlan_offload {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u8 vlan_offload;
	u8 rsvd1[5];
};

/* ucode capture cfg info */
struct nic_cmd_capture_info {
	struct hinic3_mgmt_msg_head msg_head;
	u32 op_type;
	u32 func_port;
	u32 is_en_trx;       /* 也作为tx_rx */
	u32 offset_cos;      /* 也作为cos */
	u32 data_vlan;       /* 也作为vlan */
};

struct hinic3_cmd_lro_config {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u8 opcode;
	u8 rsvd1;
	u8 lro_ipv4_en;
	u8 lro_ipv6_en;
	u8 lro_max_pkt_len; /* unit is 1K */
	u8 resv2[13];
};

struct hinic3_cmd_lro_timer {
	struct hinic3_mgmt_msg_head msg_head;

	u8 opcode; /* 1: set timer value, 0: get timer value */
	u8 rsvd1;
	u16 rsvd2;
	u32 timer;
};

struct hinic3_cmd_local_lro_state {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u8 opcode; /* 0: get state, 1: set state */
	u8 state; /* 0: disable, 1: enable */
};

struct hinic3_cmd_vf_vlan_config {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u8 opcode;
	u8 rsvd1;
	u16 vlan_id;
	u8 qos;
	u8 rsvd2[5];
};

struct hinic3_cmd_spoofchk_set {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u8 state;
	u8 rsvd1;
};

struct hinic3_cmd_tx_rate_cfg {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u16 rsvd1;
	u32 min_rate;
	u32 max_rate;
	u8 rsvd2[8];
};

struct hinic3_cmd_port_info {
	struct hinic3_mgmt_msg_head msg_head;

	u8 port_id;
	u8 rsvd1[3];
	u8 port_type;
	u8 autoneg_cap;
	u8 autoneg_state;
	u8 duplex;
	u8 speed;
	u8 fec;
	u16 rsvd2;
	u32 rsvd3[4];
};

struct hinic3_cmd_register_vf {
	struct hinic3_mgmt_msg_head msg_head;

	u8 op_register; /* 0 - unregister, 1 - register */
	u8 rsvd1[3];
	u32 support_extra_feature;
	u8 rsvd2[32];
};

struct hinic3_cmd_link_state {
	struct hinic3_mgmt_msg_head msg_head;

	u8 port_id;
	u8 state;
	u16 rsvd1;
};

struct hinic3_cmd_vlan_config {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u8 opcode;
	u8 rsvd1;
	u16 vlan_id;
	u16 rsvd2;
};

/* set vlan filter */
struct hinic3_cmd_set_vlan_filter {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u8 resvd[2];
	u32 vlan_filter_ctrl; /* bit0:vlan filter en; bit1:broadcast_filter_en */
};

struct hinic3_cmd_link_ksettings_info {
	struct hinic3_mgmt_msg_head msg_head;

	u8 port_id;
	u8 rsvd1[3];

	u32 valid_bitmap;
	u8 speed;          /* enum nic_speed_level */
	u8 autoneg;        /* 0 - off, 1 - on */
	u8 fec;            /* 0 - RSFEC, 1 - BASEFEC, 2 - NOFEC */
	u8 rsvd2[21];      /* reserved for duplex, port, etc. */
};

struct mpu_lt_info {
	u8 node;
	u8 inst;
	u8 entry_size;
	u8 rsvd;
	u32 lt_index;
	u32 offset;
	u32 len;
};

struct nic_mpu_lt_opera {
	struct hinic3_mgmt_msg_head msg_head;
	struct mpu_lt_info net_lt_cmd;
	u8 data[100];
};

struct hinic3_force_pkt_drop {
	struct hinic3_mgmt_msg_head msg_head;

	u8 port;
	u8 rsvd1[3];
};

struct hinic3_rx_mode_config {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u16 rsvd1;
	u32 rx_mode;
};

/* rss */
struct hinic3_rss_context_table {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u16 rsvd1;
	u32 context;
};

struct hinic3_cmd_rss_engine_type {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u8 opcode;
	u8 hash_engine;
	u8 rsvd1[4];
};

struct hinic3_cmd_rss_hash_key {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u8 opcode;
	u8 rsvd1;
	u8 key[NIC_RSS_KEY_SIZE];
};

struct hinic3_rss_indir_table {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u16 rsvd1;
	u8 indir[NIC_RSS_INDIR_SIZE];
};

#define NIC_RSS_CMD_TEMP_ALLOC 0x01
#define NIC_RSS_CMD_TEMP_FREE 0x02

struct hinic3_rss_template_mgmt {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u8 cmd;
	u8 template_id;
	u8 rsvd1[4];
};

struct hinic3_cmd_rss_config {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u8 rss_en;
	u8 rq_priority_number;
	u8 prio_tc[NIC_DCB_COS_MAX];
	u16 num_qps;
	u16 rsvd1;
};

struct hinic3_dcb_state {
	u8 dcb_on;
	u8 default_cos;
	u8 trust;
	u8 rsvd1;
	u8 pcp2cos[NIC_DCB_UP_MAX];
	u8 dscp2cos[64];
	u32 rsvd2[7];
};

struct hinic3_cmd_vf_dcb_state {
	struct hinic3_mgmt_msg_head msg_head;

	struct hinic3_dcb_state state;
};

struct hinic3_up_ets_cfg { /* delet */
	struct hinic3_mgmt_msg_head msg_head;

	u8 port_id;
	u8 rsvd1[3];

	u8 cos_tc[NIC_DCB_COS_MAX];
	u8 tc_bw[NIC_DCB_TC_MAX];
	u8 cos_prio[NIC_DCB_COS_MAX];
	u8 cos_bw[NIC_DCB_COS_MAX];
	u8 tc_prio[NIC_DCB_TC_MAX];
};

#define CMD_QOS_ETS_COS_TC     BIT(0)
#define CMD_QOS_ETS_TC_BW      BIT(1)
#define CMD_QOS_ETS_COS_PRIO   BIT(2)
#define CMD_QOS_ETS_COS_BW     BIT(3)
#define CMD_QOS_ETS_TC_PRIO    BIT(4)
struct hinic3_cmd_ets_cfg {
	struct hinic3_mgmt_msg_head head;

	u8 port_id;
	u8 op_code;        /* 1 - set, 0 - get */
	/* bit0 - cos_tc, bit1 - tc_bw, bit2 - cos_prio, bit3 - cos_bw, bit4 - tc_prio */
	u8 cfg_bitmap;
	u8 rsvd;

	u8 cos_tc[NIC_DCB_COS_MAX];
	u8 tc_bw[NIC_DCB_TC_MAX];
	u8 cos_prio[NIC_DCB_COS_MAX];      /* 0 - DWRR, 1 - STRICT */
	u8 cos_bw[NIC_DCB_COS_MAX];
	u8 tc_prio[NIC_DCB_TC_MAX];        /* 0 - DWRR, 1 - STRICT */
};

struct hinic3_cmd_set_dcb_state {
	struct hinic3_mgmt_msg_head head;

	u16 func_id;
	u8 op_code;      /* 0 - get dcb state, 1 - set dcb state */
	u8 state;        /* 0 - disable, 1 - enable dcb */
	u8 port_state;   /* 0 - disable, 1 - enable dcb */
	u8 rsvd[7];
};

#define PFC_BIT_MAP_NUM 8
struct hinic3_cmd_set_pfc {
	struct hinic3_mgmt_msg_head head;

	u8 port_id;
	u8 op_code;  /* 0：get 1: set pfc_en  2: set pfc_bitmap 3: set all */
	u8 pfc_en;   /* pfc_en 和 pfc_bitmap 必须同时设置 */
	u8 pfc_bitmap;
	u8 rsvd[4];
};

#define CMD_QOS_PORT_TRUST     BIT(0)
#define CMD_QOS_PORT_DFT_COS   BIT(1)
struct hinic3_cmd_qos_port_cfg {
	struct hinic3_mgmt_msg_head head;

	u8 port_id;
	u8 op_code;       /* 0 - get, 1 - set */
	u8 cfg_bitmap;    /* bit0 - trust, bit1 - dft_cos */
	u8 rsvd0;

	u8 trust;
	u8 dft_cos;
	u8 rsvd1[18];
};

#define MAP_COS_MAX_NUM 8
#define CMD_QOS_MAP_PCP2COS     BIT(0)
#define CMD_QOS_MAP_DSCP2COS    BIT(1)
struct hinic3_cmd_qos_map_cfg {
	struct hinic3_mgmt_msg_head head;

	u8 op_code;
	u8 cfg_bitmap; /* bit0 - pcp2cos, bit1 - dscp2cos */
	u16 rsvd0;

	u8 pcp2cos[8]; /* 必须8个一起配置 */
	/* 配置dscp2cos时，若cos值设置为0xFF，MPU则忽略此dscp优先级的配置,
	 * 允许一次性配置多个dscp跟cos的映射关系
	 */
	u8 dscp2cos[64];
	u32 rsvd1[4];
};

struct hinic3_cos_up_map {
	struct hinic3_mgmt_msg_head msg_head;

	u8 port_id;
	u8 cos_valid_mask; /* every bit indicate index of map is valid 1 or not 0 */
	u16 rsvd1;

	/* user priority in cos(index:cos, value: up pri) */
	u8 map[NIC_DCB_UP_MAX];
};

struct hinic3_cmd_pause_config {
	struct hinic3_mgmt_msg_head msg_head;

	u8 port_id;
	u8 opcode;
	u16 rsvd1;
	u8 auto_neg;
	u8 rx_pause;
	u8 tx_pause;
	u8 rsvd2[5];
};

/* pfc风暴检测配置 */
struct nic_cmd_pause_inquiry_cfg {
	struct hinic3_mgmt_msg_head head;

	u32 valid;

	u32 type; /* 1: set, 2: get */

	u32 rx_inquiry_pause_drop_pkts_en; /* rx 卸包使能 */
	u32 rx_inquiry_pause_period_ms;  /* rx pause 检测周期 默认 200ms */
	u32 rx_inquiry_pause_times;      /* rx pause 检测次数 默认1次 */
	/* rx pause 检测阈值 默认 PAUSE_FRAME_THD_10G/25G/40G/100 */
	u32 rx_inquiry_pause_frame_thd;
	u32 rx_inquiry_tx_total_pkts;    /* rx pause 检测tx收包总数 */

	u32 tx_inquiry_pause_en; /* tx pause 检测使能 */
	u32 tx_inquiry_pause_period_ms;  /* tx pause 检测周期 默认 200ms */
	u32 tx_inquiry_pause_times;      /* tx pause 检测次数 默认 5次 */
	u32 tx_inquiry_pause_frame_thd;  /* tx pause 检测阈值 */
	u32 tx_inquiry_rx_total_pkts;    /* tx pause 检测rx收包总数 */

	u32 rsvd[4];
};

/* pfc/pause风暴tx异常上报 */
struct nic_cmd_tx_pause_notice {
	struct hinic3_mgmt_msg_head head;

	u32 tx_pause_except; /* 1: 异常，0: 正常 */
	u32 except_level;
	u32 rsvd;
};

#define HINIC3_CMD_OP_FREE 0
#define HINIC3_CMD_OP_ALLOC 1

struct hinic3_cmd_cfg_qps {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u8 opcode; /* 1: alloc qp, 0: free qp */
	u8 rsvd1;
	u16 num_qps;
	u16 rsvd2;
};

struct hinic3_cmd_led_config {
	struct hinic3_mgmt_msg_head msg_head;

	u8 port;
	u8 type;
	u8 mode;
	u8 rsvd1;
};

struct hinic3_cmd_port_loopback {
	struct hinic3_mgmt_msg_head msg_head;

	u8 port_id;
	u8 opcode;
	u8 mode;
	u8 en;
	u32 rsvd1[2];
};

struct hinic3_cmd_get_light_module_abs {
	struct hinic3_mgmt_msg_head msg_head;

	u8 port_id;
	u8 abs_status; /* 0:present, 1:absent */
	u8 rsv[2];
};

#define STD_SFP_INFO_MAX_SIZE 640
struct hinic3_cmd_get_std_sfp_info {
	struct hinic3_mgmt_msg_head msg_head;

	u8 port_id;
	u8 wire_type;
	u16 eeprom_len;
	u32 rsvd;
	u8 sfp_info[STD_SFP_INFO_MAX_SIZE];
};

struct hinic3_cable_plug_event {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u8 plugged; /* 0: unplugged, 1: plugged */
	u8 port_id;
};

/* MAC模块接口 */
struct nic_cmd_mac_info {
	struct hinic3_mgmt_msg_head head;

	u32 valid_bitmap;
	u16 rsvd;

	u8 host_id[32];
	u8 port_id[32];
	u8 mac_addr[192];
};

struct nic_cmd_set_tcam_enable {
	struct hinic3_mgmt_msg_head head;

	u16 func_id;
	u8 tcam_enable;
	u8 rsvd1;
	u32 rsvd2;
};

struct nic_cmd_set_fdir_status {
	struct hinic3_mgmt_msg_head head;

	u16 func_id;
	u16 rsvd1;
	u8 pkt_type_en;
	u8 pkt_type;
	u8 qid;
	u8 rsvd2;
};

#define HINIC3_TCAM_BLOCK_ENABLE      1
#define HINIC3_TCAM_BLOCK_DISABLE     0
#define HINIC3_MAX_TCAM_RULES_NUM   4096

/* tcam block type, according to tcam block size */
enum {
	NIC_TCAM_BLOCK_TYPE_LARGE = 0, /* block_size: 16 */
	NIC_TCAM_BLOCK_TYPE_SMALL,     /* block_size: 0 */
	NIC_TCAM_BLOCK_TYPE_MAX
};

/* alloc tcam block input struct */
struct nic_cmd_ctrl_tcam_block_in {
	struct hinic3_mgmt_msg_head head;

	u16 func_id;  /* func_id */
	u8 alloc_en;  /* 0: 释放分配的tcam block, 1: 申请新的tcam block */
	/* 0: 分配16 size 的tcam block, 1: 分配0 size的tcam block, 其他预留 */
	u8 tcam_type;
	u16 tcam_block_index;
	/* 驱动发给uP表示驱动希望分配的block大小
	 * uP返回给驱动的接口，表示uP 支持的分配的tcam block大小
	 */
	u16 alloc_block_num;
};

/* alloc tcam block output struct */
struct nic_cmd_ctrl_tcam_block_out {
	struct hinic3_mgmt_msg_head head;

	u16 func_id;  /* func_id */
	u8 alloc_en;  /* 0: 释放分配的tcam block, 1: 申请新的tcam block */
	/* 0: 分配16 size 的tcam block, 1: 分配0 size的tcam block, 其他预留 */
	u8 tcam_type;
	u16 tcam_block_index;
	/* 驱动发给uP表示驱动希望分配的block大小
	 * uP返回给驱动的接口，表示uP 支持的分配的tcam block大小
	 */
	u16 mpu_alloc_block_size;
};

struct nic_cmd_flush_tcam_rules {
	struct hinic3_mgmt_msg_head head;

	u16 func_id; /* func_id */
	u16 rsvd;
};

struct nic_cmd_dfx_fdir_tcam_block_table {
	struct hinic3_mgmt_msg_head head;
	u8 tcam_type;
	u8 valid;
	u16 tcam_block_index;
	u16 use_function_id;
	u16 rsvd;
};

struct tcam_result {
	u32 qid;
	u32 rsvd;
};

#define TCAM_FLOW_KEY_SIZE (44)

struct tcam_key_x_y {
	u8 x[TCAM_FLOW_KEY_SIZE];
	u8 y[TCAM_FLOW_KEY_SIZE];
};

struct nic_tcam_cfg_rule {
	u32 index;
	struct tcam_result data;
	struct tcam_key_x_y key;
};

#define TCAM_RULE_FDIR_TYPE 0
#define TCAM_RULE_PPA_TYPE  1

struct nic_cmd_fdir_add_rule {
	struct hinic3_mgmt_msg_head head;

	u16 func_id;
	u8 type;
	u8 rsvd;
	struct nic_tcam_cfg_rule rule;
};

struct nic_cmd_fdir_del_rules {
	struct hinic3_mgmt_msg_head head;

	u16 func_id;
	u8 type;
	u8 rsvd;
	u32 index_start;
	u32 index_num;
};

struct nic_cmd_fdir_get_rule {
	struct hinic3_mgmt_msg_head head;

	u32 index;
	u8 valid;
	u8 type;
	u16 rsvd;
	struct tcam_key_x_y key;
	struct tcam_result data;
	u64 packet_count;
	u64 byte_count;
};

struct hinic3_tcam_key_ipv4_mem {
	u32 rsvd1 : 4;
	u32 tunnel_type : 4;
	u32 ip_proto : 8;
	u32 rsvd0 : 16;
	u32 sipv4_h : 16;
	u32 ip_type : 1;
	u32 function_id : 15;
	u32 dipv4_h : 16;
	u32 sipv4_l : 16;
	u32 rsvd2 : 16;
	u32 dipv4_l : 16;
	u32 rsvd3;
	u32 dport : 16;
	u32 rsvd4 : 16;
	u32 rsvd5 : 16;
	u32 sport : 16;
	u32 outer_sipv4_h : 16;
	u32 rsvd6 : 16;
	u32 outer_dipv4_h : 16;
	u32 outer_sipv4_l : 16;
	u32 vni_h : 16;
	u32 outer_dipv4_l : 16;
	u32 rsvd7 : 16;
	u32 vni_l : 16;
};

struct hinic3_tcam_key_ipv6_mem {
	u32 rsvd1 : 4;
	u32 tunnel_type : 4;
	u32 ip_proto : 8;
	u32 rsvd0 : 16;
	u32 sipv6_key0 : 16;
	u32 ip_type : 1;
	u32 function_id : 15;
	u32 sipv6_key2 : 16;
	u32 sipv6_key1 : 16;
	u32 sipv6_key4 : 16;
	u32 sipv6_key3 : 16;
	u32 sipv6_key6 : 16;
	u32 sipv6_key5 : 16;
	u32 dport : 16;
	u32 sipv6_key7 : 16;
	u32 dipv6_key0 : 16;
	u32 sport : 16;
	u32 dipv6_key2 : 16;
	u32 dipv6_key1 : 16;
	u32 dipv6_key4 : 16;
	u32 dipv6_key3 : 16;
	u32 dipv6_key6 : 16;
	u32 dipv6_key5 : 16;
	u32 rsvd2 : 16;
	u32 dipv6_key7 : 16;
};

struct hinic3_tcam_key_vxlan_ipv6_mem {
	u32 rsvd1 : 4;
	u32 tunnel_type : 4;
	u32 ip_proto : 8;
	u32 rsvd0 : 16;

	u32 dipv6_key0 : 16;
	u32 ip_type : 1;
	u32 function_id : 15;

	u32 dipv6_key2 : 16;
	u32 dipv6_key1 : 16;

	u32 dipv6_key4 : 16;
	u32 dipv6_key3 : 16;

	u32 dipv6_key6 : 16;
	u32 dipv6_key5 : 16;

	u32 dport : 16;
	u32 dipv6_key7 : 16;

	u32 rsvd2 : 16;
	u32 sport : 16;

	u32 outer_sipv4_h : 16;
	u32 rsvd3 : 16;

	u32 outer_dipv4_h : 16;
	u32 outer_sipv4_l : 16;

	u32 vni_h : 16;
	u32 outer_dipv4_l : 16;

	u32 rsvd4 : 16;
	u32 vni_l : 16;
};

struct tag_tcam_key {
	union {
		struct hinic3_tcam_key_ipv4_mem key_info;
		struct hinic3_tcam_key_ipv6_mem key_info_ipv6;
		struct hinic3_tcam_key_vxlan_ipv6_mem key_info_vxlan_ipv6;
	};

	union {
		struct hinic3_tcam_key_ipv4_mem key_mask;
		struct hinic3_tcam_key_ipv6_mem key_mask_ipv6;
		struct hinic3_tcam_key_vxlan_ipv6_mem key_mask_vxlan_ipv6;
	};
};

enum {
	PPA_TABLE_ID_CLEAN_CMD = 0,
	PPA_TABLE_ID_ADD_CMD,
	PPA_TABLE_ID_DEL_CMD,
	FDIR_TABLE_ID_ADD_CMD,
	FDIR_TABLE_ID_DEL_CMD,
	PPA_TABEL_ID_MAX
};

struct hinic3_ppa_cfg_table_id_cmd {
	struct hinic3_mgmt_msg_head msg_head;

	u16 rsvd0;
	u16 cmd;
	u16 table_id;
	u16 rsvd1;
};

struct hinic3_ppa_cfg_ppa_en_cmd {
	struct hinic3_mgmt_msg_head msg_head;

	u16 func_id;
	u8 ppa_en;
	u8 rsvd;
};

struct hinic3_ppa_cfg_mode_cmd {
	struct hinic3_mgmt_msg_head msg_head;

	u16 rsvd0;
	u8 ppa_mode;
	u8 qpc_func_nums;
	u16 base_qpc_func_id;
	u16 rsvd1;
};

struct hinic3_ppa_flush_en_cmd {
	struct hinic3_mgmt_msg_head msg_head;

	u16 rsvd0;
	u8 flush_en; /* 0 flush done, 1 in flush operation */
	u8 rsvd1;
};

struct hinic3_ppa_fdir_query_cmd {
	struct hinic3_mgmt_msg_head msg_head;

	u32 index;
	u32 rsvd;
	u64 pkt_nums;
	u64 pkt_bytes;
};

/* BIOS CONF */
enum {
	NIC_NVM_DATA_SET = BIT(0), /* 1-save, 0-read */
	NIC_NVM_DATA_PXE = BIT(1),
	NIC_NVM_DATA_VLAN = BIT(2),
	NIC_NVM_DATA_VLAN_PRI = BIT(3),
	NIC_NVM_DATA_VLAN_ID = BIT(4),
	NIC_NVM_DATA_WORK_MODE = BIT(5),
	NIC_NVM_DATA_PF_SPEED_LIMIT = BIT(6),
	NIC_NVM_DATA_GE_MODE = BIT(7),
	NIC_NVM_DATA_AUTO_NEG = BIT(8),
	NIC_NVM_DATA_LINK_FEC = BIT(9),
	NIC_NVM_DATA_PF_ADAPTIVE_LINK = BIT(10),
	NIC_NVM_DATA_SRIOV_CONTROL = BIT(11),
	NIC_NVM_DATA_EXTEND_MODE = BIT(12),
	NIC_NVM_DATA_RESET = BIT(31),
};

#define BIOS_CFG_SIGNATURE                  0x1923E518
#define BIOS_OP_CFG_ALL(op_code_val)        (((op_code_val) >> 1) & (0xFFFFFFFF))
#define BIOS_OP_CFG_WRITE(op_code_val)      ((op_code_val) & NIC_NVM_DATA_SET)
#define BIOS_OP_CFG_PXE_EN(op_code_val)     ((op_code_val) & NIC_NVM_DATA_PXE)
#define BIOS_OP_CFG_VLAN_EN(op_code_val)    ((op_code_val) & NIC_NVM_DATA_VLAN)
#define BIOS_OP_CFG_VLAN_PRI(op_code_val)   ((op_code_val) & NIC_NVM_DATA_VLAN_PRI)
#define BIOS_OP_CFG_VLAN_ID(op_code_val)    ((op_code_val) & NIC_NVM_DATA_VLAN_ID)
#define BIOS_OP_CFG_WORK_MODE(op_code_val)  ((op_code_val) & NIC_NVM_DATA_WORK_MODE)
#define BIOS_OP_CFG_PF_BW(op_code_val)      ((op_code_val) & NIC_NVM_DATA_PF_SPEED_LIMIT)
#define BIOS_OP_CFG_GE_SPEED(op_code_val)   ((op_code_val) & NIC_NVM_DATA_GE_MODE)
#define BIOS_OP_CFG_AUTO_NEG(op_code_val)   ((op_code_val) & NIC_NVM_DATA_AUTO_NEG)
#define BIOS_OP_CFG_LINK_FEC(op_code_val)   ((op_code_val) & NIC_NVM_DATA_LINK_FEC)
#define BIOS_OP_CFG_AUTO_ADPAT(op_code_val) ((op_code_val) & NIC_NVM_DATA_PF_ADAPTIVE_LINK)
#define BIOS_OP_CFG_SRIOV_ENABLE(op_code_val)   ((op_code_val) & NIC_NVM_DATA_SRIOV_CONTROL)
#define BIOS_OP_CFG_EXTEND_MODE(op_code_val)    ((op_code_val) & NIC_NVM_DATA_EXTEND_MODE)
#define BIOS_OP_CFG_RST_DEF_SET(op_code_val)    ((op_code_val) & (u32)NIC_NVM_DATA_RESET)

#define NIC_BIOS_CFG_MAX_PF_BW 100
/* 注意:此结构必须保证4字节对齐 */
struct nic_bios_cfg {
	u32 signature; /* 签名，用于判断FLASH的内容合法性 */
	u8 pxe_en;     /* PXE enable: 0 - disable 1 - enable */
	u8 extend_mode;
	u8 rsvd0[2];
	u8 pxe_vlan_en;     /* PXE VLAN enable: 0 - disable 1 - enable */
	u8 pxe_vlan_pri;    /* PXE VLAN priority: 0-7 */
	u16 pxe_vlan_id;    /* PXE VLAN ID 1-4094 */
	u32 service_mode;   /* 参考CHIPIF_SERVICE_MODE_x 宏 */
	u32 pf_bw;          /* PF速率，百分比 0-100 */
	u8 speed;           /* enum of port speed */
	u8 auto_neg;        /* 自协商开关 0 - 字段无效 1 - 开2 - 关 */
	u8 lanes;           /* lane num */
	u8 fec;             /* FEC模式, 参考 enum mag_cmd_port_fec */
	u8 auto_adapt;      /* 自适应模式配置0 - 无效配置 1 - 开启 2 - 关闭 */
	u8 func_valid;      /* 指示func_id是否有效; 0 - 无效，other - 有效 */
	u8 func_id;         /* 当func_valid不为0时，该成员才有意义 */
	u8 sriov_en;        /* SRIOV-EN: 0 - 无效配置， 1 - 开启， 2 - 关闭 */
};

struct nic_cmd_bios_cfg {
	struct hinic3_mgmt_msg_head head;
	u32 op_code; /* Operation Code: Bit0[0: read 1:write, BIT1-6: cfg_mask */
	struct nic_bios_cfg bios_cfg;
};

struct nic_cmd_vhd_config {
	struct hinic3_mgmt_msg_head head;

	u16 func_id;
	u8  vhd_type;
	u8  virtio_small_enable;    /* 0: mergeable mode, 1: small mode */
};

/* BOND */
struct hinic3_create_bond_info {
	u32 bond_id;              /* bond设备号,output时有效,mpu操作成功返回时回填 */
	u32 master_slave_port_id; /*  */
	u32 slave_bitmap;         /* bond port id bitmap */
	u32 poll_timeout;         /* bond设备链路检查时间 */
	u32 up_delay;             /* 暂时预留 */
	u32 down_delay;           /* 暂时预留 */
	u32 bond_mode;            /* 暂时预留 */
	u32 active_pf; /* bond使用的active pf id */
	u32 active_port_max_num; /* bond活动成员口个数上限 */
	u32 active_port_min_num; /* bond活动成员口个数下限 */
	u32 xmit_hash_policy; /* hash策略，用于微码选路逻辑 */
	u32 rsvd[2];
};

/* 创建bond的消息接口 */
struct hinic3_cmd_create_bond {
	struct hinic3_mgmt_msg_head head;
	struct hinic3_create_bond_info create_bond_info;
};

struct hinic3_cmd_delete_bond {
	struct hinic3_mgmt_msg_head head;
	u32 bond_id;
	u32 rsvd[2];
};

struct hinic3_open_close_bond_info {
	u32 bond_id;                 /* bond设备号 */
	u32 open_close_flag;         /* 开启/关闭bond标识:1为open, 0为close */
	u32 rsvd[2];
};

/* MPU bond的消息接口 */
struct hinic3_cmd_open_close_bond {
	struct hinic3_mgmt_msg_head head;
	struct hinic3_open_close_bond_info open_close_bond_info;
};

/* LACPDU的port相关字段 */
struct lacp_port_params {
	u16 port_number;
	u16 port_priority;
	u16 key;
	u16 system_priority;
	u8 system[ETH_ALEN];
	u8 port_state;
	u8 rsvd;
};

struct lacp_port_info {
	u32 selected;
	u32 aggregator_port_id;           /* 使用的 aggregator port ID */

	struct lacp_port_params actor;    /* actor port参数 */
	struct lacp_port_params partner;  /* partner port参数 */

	u64 tx_lacp_pkts;
	u64 rx_lacp_pkts;
	u64 rx_8023ad_drop;
	u64 tx_8023ad_drop;
	u64 unknown_pkt_drop;
	u64 rx_marker_pkts;
	u64 tx_marker_pkts;
};

/* lacp 状态信息 */
struct hinic3_bond_status_info {
	struct hinic3_mgmt_msg_head head;
	u32 bond_id;
	u32 bon_mmi_status; /* 该bond子设备的链路状态 */
	u32 active_bitmap;  /* 该bond子设备的slave port状态 */
	u32 port_count;     /* 该bond子设备个数 */

	struct lacp_port_info port_info[4];

	u64 success_report_cnt[4]; /* 每个host成功上报lacp协商结果次数 */
	u64 fail_report_cnt[4];    /* 每个host上报lacp协商结果失败次数 */

	u64 poll_timeout;
	u64 fast_periodic_timeout;
	u64 slow_periodic_timeout;
	u64 short_timeout;
	u64 long_timeout;
	u64 aggregate_wait_timeout;
	u64 tx_period_timeout;
	u64 rx_marker_timer;
};

/* lacp协商结果更新之后向主机侧发送异步消息通知结构体 */
struct hinic3_bond_active_report_info {
	struct hinic3_mgmt_msg_head head;
	u32 bond_id;
	u32 bon_mmi_status; /* 该bond子设备的链路状态 */
	u32 active_bitmap;  /* 该bond子设备的slave port状态 */

	u8 rsvd[16];
};

/* IP checksum error packets, enable rss quadruple hash. */
struct hinic3_ipcs_err_rss_enable_operation_s {
	struct hinic3_mgmt_msg_head head;

	u8 en_tag;
	u8 type; /* 1: set  0: get */
	u8 rsvd[2];
};

struct hinic3_smac_check_state {
	struct hinic3_mgmt_msg_head head;
	u8 smac_check_en; /* 1: enable 0: disable */
	u8 op_code; /* 1: set 0: get */
	u8 rsvd[2];
};

#endif /* HINIC_MGMT_INTERFACE_H */
