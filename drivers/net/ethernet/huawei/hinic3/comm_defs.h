/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2022. All rights reserved.
 * File Name     : comm_defs.h
 * Version       : Initial Draft
 * Description   : common definitions
 * Function List :
 * History       :
 * Modification: Created file
 */

#ifndef COMM_DEFS_H
#define COMM_DEFS_H

/* CMDQ MODULE_TYPE */
enum hinic3_mod_type {
	HINIC3_MOD_COMM = 0,  /* HW communication module */
	HINIC3_MOD_L2NIC = 1, /* L2NIC module */
	HINIC3_MOD_ROCE = 2,
	HINIC3_MOD_PLOG = 3,
	HINIC3_MOD_TOE = 4,
	HINIC3_MOD_FLR = 5,
	HINIC3_MOD_RSVD1 = 6,
	HINIC3_MOD_CFGM = 7, /* Configuration module */
	HINIC3_MOD_CQM = 8,
	HINIC3_MOD_RSVD2 = 9,
	COMM_MOD_FC = 10,
	HINIC3_MOD_OVS = 11,
	HINIC3_MOD_DSW = 12,
	HINIC3_MOD_MIGRATE = 13,
	HINIC3_MOD_HILINK = 14,
	HINIC3_MOD_CRYPT = 15, /* secure crypto module */
	HINIC3_MOD_VIO = 16,
	HINIC3_MOD_IMU = 17,
	HINIC3_MOD_DFT = 18, /* DFT */
	HINIC3_MOD_HW_MAX = 19, /* hardware max module id */
	/* Software module id, for PF/VF and multi-host */
	HINIC3_MOD_SW_FUNC = 20,
	HINIC3_MOD_MAX,
};

/* func reset的flag ,用于指示清理哪种资源 */
enum func_reset_flag {
	RES_TYPE_FLUSH_BIT = 0,
	RES_TYPE_MQM,
	RES_TYPE_SMF,
	RES_TYPE_PF_BW_CFG,

	RES_TYPE_COMM = 10,
	RES_TYPE_COMM_MGMT_CH,  /* clear mbox and aeq, The RES_TYPE_COMM bit must be set */
	RES_TYPE_COMM_CMD_CH,   /* clear cmdq and ceq, The RES_TYPE_COMM bit must be set */
	RES_TYPE_NIC,
	RES_TYPE_OVS,
	RES_TYPE_VBS,
	RES_TYPE_ROCE,
	RES_TYPE_FC,
	RES_TYPE_TOE,
	RES_TYPE_IPSEC,
	RES_TYPE_MAX,
};

#define HINIC3_COMM_RES                                     \
	((1 << RES_TYPE_COMM) | (1 << RES_TYPE_COMM_CMD_CH) |   \
	 (1 << RES_TYPE_FLUSH_BIT) | (1 << RES_TYPE_MQM) | \
	 (1 << RES_TYPE_SMF) | (1 << RES_TYPE_PF_BW_CFG))

#define HINIC3_NIC_RES      (1 << RES_TYPE_NIC)
#define HINIC3_OVS_RES      (1 << RES_TYPE_OVS)
#define HINIC3_VBS_RES      (1 << RES_TYPE_VBS)
#define HINIC3_ROCE_RES     (1 << RES_TYPE_ROCE)
#define HINIC3_FC_RES       (1 << RES_TYPE_FC)
#define HINIC3_TOE_RES      (1 << RES_TYPE_TOE)
#define HINIC3_IPSEC_RES    (1 << RES_TYPE_IPSEC)

/* MODE OVS、NIC、UNKNOWN */
#define HINIC3_WORK_MODE_OVS 0
#define HINIC3_WORK_MODE_UNKNOWN 1
#define HINIC3_WORK_MODE_NIC 2

#define DEVICE_TYPE_L2NIC                   0
#define DEVICE_TYPE_NVME                    1
#define DEVICE_TYPE_VIRTIO_NET              2
#define DEVICE_TYPE_VIRTIO_BLK              3
#define DEVICE_TYPE_VIRTIO_VSOCK            4
#define DEVICE_TYPE_VIRTIO_NET_TRANSITION   5
#define DEVICE_TYPE_VIRTIO_BLK_TRANSITION   6
#define DEVICE_TYPE_VIRTIO_SCSI_TRANSITION  7
#define DEVICE_TYPE_VIRTIO_HPC              8

#define IS_STORAGE_DEVICE_TYPE(dev_type)                                                        \
	((dev_type) == DEVICE_TYPE_VIRTIO_BLK || \
	 (dev_type) == DEVICE_TYPE_VIRTIO_BLK_TRANSITION || \
	 (dev_type) == DEVICE_TYPE_VIRTIO_SCSI_TRANSITION)

/* Common header control information of the COMM message
 * interaction command word between the driver and PF
 */
struct comm_info_head {
	u8 status;
	u8 version;
	u8 rep_aeq_num;
	u8 rsvd[5];
};

#endif
