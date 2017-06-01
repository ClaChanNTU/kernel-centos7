/* QLogic qed NIC Driver
 * Copyright (c) 2015 QLogic Corporation
 *
 * This software is available under the terms of the GNU General Public License
 * (GPL) Version 2, available from the file COPYING in the main directory of
 * this source tree.
 */

#ifndef __ETH_COMMON__
#define __ETH_COMMON__

/********************/
/* ETH FW CONSTANTS */
/********************/
#define ETH_CACHE_LINE_SIZE                 64

#define ETH_MAX_RAMROD_PER_CON                          8
#define ETH_TX_BD_PAGE_SIZE_BYTES                       4096
#define ETH_RX_BD_PAGE_SIZE_BYTES                       4096
#define ETH_RX_CQE_PAGE_SIZE_BYTES                      4096
#define ETH_RX_NUM_NEXT_PAGE_BDS                        2

#define ETH_TX_MIN_BDS_PER_NON_LSO_PKT                          1
#define ETH_TX_MAX_BDS_PER_NON_LSO_PACKET                       18
#define ETH_TX_MAX_LSO_HDR_NBD                                          4
#define ETH_TX_MIN_BDS_PER_LSO_PKT                                      3
#define ETH_TX_MIN_BDS_PER_TUNN_IPV6_WITH_EXT_PKT       3
#define ETH_TX_MIN_BDS_PER_IPV6_WITH_EXT_PKT            2
#define ETH_TX_MIN_BDS_PER_PKT_W_LOOPBACK_MODE          2
#define ETH_TX_MAX_NON_LSO_PKT_LEN                  (9700 - (4 + 12 + 8))
#define ETH_TX_MAX_LSO_HDR_BYTES                    510

#define ETH_NUM_STATISTIC_COUNTERS                      MAX_NUM_VPORTS

/* Maximum number of buffers, used for RX packet placement */
#define ETH_RX_MAX_BUFF_PER_PKT             5

/* num of MAC/VLAN filters */
#define ETH_NUM_MAC_FILTERS                                     512
#define ETH_NUM_VLAN_FILTERS                            512

/* approx. multicast constants */
#define ETH_MULTICAST_BIN_FROM_MAC_SEED     0
#define ETH_MULTICAST_MAC_BINS                          256
#define ETH_MULTICAST_MAC_BINS_IN_REGS          (ETH_MULTICAST_MAC_BINS / 32)

/*  ethernet vport update constants */
#define ETH_FILTER_RULES_COUNT                          10
#define ETH_RSS_IND_TABLE_ENTRIES_NUM           128
#define ETH_RSS_KEY_SIZE_REGS                       10
#define ETH_RSS_ENGINE_NUM_K2               207
#define ETH_RSS_ENGINE_NUM_BB               127

/* TPA constants */
#define ETH_TPA_MAX_AGGS_NUM              64
#define ETH_TPA_CQE_START_LEN_LIST_SIZE   ETH_RX_MAX_BUFF_PER_PKT
#define ETH_TPA_CQE_CONT_LEN_LIST_SIZE    6
#define ETH_TPA_CQE_END_LEN_LIST_SIZE     4

/* Queue Zone sizes */
#define TSTORM_QZONE_SIZE    0
#define MSTORM_QZONE_SIZE    sizeof(struct mstorm_eth_queue_zone)
#define USTORM_QZONE_SIZE    sizeof(struct ustorm_eth_queue_zone)
#define XSTORM_QZONE_SIZE    0
#define YSTORM_QZONE_SIZE    sizeof(struct ystorm_eth_queue_zone)
#define PSTORM_QZONE_SIZE    0

/* Interrupt coalescing TimeSet */
struct coalescing_timeset {
	u8	timeset;
	u8	valid;
};

struct eth_tx_1st_bd_flags {
	u8 bitfields;
#define ETH_TX_1ST_BD_FLAGS_START_BD_MASK         0x1
#define ETH_TX_1ST_BD_FLAGS_START_BD_SHIFT        0
#define ETH_TX_1ST_BD_FLAGS_FORCE_VLAN_MODE_MASK  0x1
#define ETH_TX_1ST_BD_FLAGS_FORCE_VLAN_MODE_SHIFT 1
#define ETH_TX_1ST_BD_FLAGS_IP_CSUM_MASK          0x1
#define ETH_TX_1ST_BD_FLAGS_IP_CSUM_SHIFT         2
#define ETH_TX_1ST_BD_FLAGS_L4_CSUM_MASK          0x1
#define ETH_TX_1ST_BD_FLAGS_L4_CSUM_SHIFT         3
#define ETH_TX_1ST_BD_FLAGS_VLAN_INSERTION_MASK   0x1
#define ETH_TX_1ST_BD_FLAGS_VLAN_INSERTION_SHIFT  4
#define ETH_TX_1ST_BD_FLAGS_LSO_MASK              0x1
#define ETH_TX_1ST_BD_FLAGS_LSO_SHIFT             5
#define ETH_TX_1ST_BD_FLAGS_TUNN_IP_CSUM_MASK     0x1
#define ETH_TX_1ST_BD_FLAGS_TUNN_IP_CSUM_SHIFT    6
#define ETH_TX_1ST_BD_FLAGS_TUNN_L4_CSUM_MASK     0x1
#define ETH_TX_1ST_BD_FLAGS_TUNN_L4_CSUM_SHIFT    7
};

/* The parsing information data fo rthe first tx bd of a given packet. */
struct eth_tx_data_1st_bd {
	__le16				vlan;
	u8				nbds;
	struct eth_tx_1st_bd_flags	bd_flags;
	__le16				bitfields;
#define ETH_TX_DATA_1ST_BD_TUNN_CFG_OVERRIDE_MASK  0x1
#define ETH_TX_DATA_1ST_BD_TUNN_CFG_OVERRIDE_SHIFT 0
#define ETH_TX_DATA_1ST_BD_RESERVED0_MASK          0x1
#define ETH_TX_DATA_1ST_BD_RESERVED0_SHIFT         1
#define ETH_TX_DATA_1ST_BD_FW_USE_ONLY_MASK        0x3FFF
#define ETH_TX_DATA_1ST_BD_FW_USE_ONLY_SHIFT       2
};

/* The parsing information data for the second tx bd of a given packet. */
struct eth_tx_data_2nd_bd {
	__le16	tunn_ip_size;
	__le16	bitfields1;
#define ETH_TX_DATA_2ND_BD_TUNN_INNER_L2_HDR_SIZE_W_MASK  0xF
#define ETH_TX_DATA_2ND_BD_TUNN_INNER_L2_HDR_SIZE_W_SHIFT 0
#define ETH_TX_DATA_2ND_BD_TUNN_INNER_ETH_TYPE_MASK       0x3
#define ETH_TX_DATA_2ND_BD_TUNN_INNER_ETH_TYPE_SHIFT      4
#define ETH_TX_DATA_2ND_BD_DEST_PORT_MODE_MASK            0x3
#define ETH_TX_DATA_2ND_BD_DEST_PORT_MODE_SHIFT           6
#define ETH_TX_DATA_2ND_BD_START_BD_MASK                  0x1
#define ETH_TX_DATA_2ND_BD_START_BD_SHIFT                 8
#define ETH_TX_DATA_2ND_BD_TUNN_TYPE_MASK                 0x3
#define ETH_TX_DATA_2ND_BD_TUNN_TYPE_SHIFT                9
#define ETH_TX_DATA_2ND_BD_TUNN_INNER_IPV6_MASK           0x1
#define ETH_TX_DATA_2ND_BD_TUNN_INNER_IPV6_SHIFT          11
#define ETH_TX_DATA_2ND_BD_IPV6_EXT_MASK                  0x1
#define ETH_TX_DATA_2ND_BD_IPV6_EXT_SHIFT                 12
#define ETH_TX_DATA_2ND_BD_TUNN_IPV6_EXT_MASK             0x1
#define ETH_TX_DATA_2ND_BD_TUNN_IPV6_EXT_SHIFT            13
#define ETH_TX_DATA_2ND_BD_L4_UDP_MASK                    0x1
#define ETH_TX_DATA_2ND_BD_L4_UDP_SHIFT                   14
#define ETH_TX_DATA_2ND_BD_L4_PSEUDO_CSUM_MODE_MASK       0x1
#define ETH_TX_DATA_2ND_BD_L4_PSEUDO_CSUM_MODE_SHIFT      15
	__le16 bitfields2;
#define ETH_TX_DATA_2ND_BD_L4_HDR_START_OFFSET_W_MASK     0x1FFF
#define ETH_TX_DATA_2ND_BD_L4_HDR_START_OFFSET_W_SHIFT    0
#define ETH_TX_DATA_2ND_BD_RESERVED0_MASK                 0x7
#define ETH_TX_DATA_2ND_BD_RESERVED0_SHIFT                13
};

/* Regular ETH Rx FP CQE. */
struct eth_fast_path_rx_reg_cqe {
	u8	type;
	u8	bitfields;
#define ETH_FAST_PATH_RX_REG_CQE_RSS_HASH_TYPE_MASK  0x7
#define ETH_FAST_PATH_RX_REG_CQE_RSS_HASH_TYPE_SHIFT 0
#define ETH_FAST_PATH_RX_REG_CQE_TC_MASK             0xF
#define ETH_FAST_PATH_RX_REG_CQE_TC_SHIFT            3
#define ETH_FAST_PATH_RX_REG_CQE_RESERVED0_MASK      0x1
#define ETH_FAST_PATH_RX_REG_CQE_RESERVED0_SHIFT     7
	__le16				pkt_len;
	struct parsing_and_err_flags	pars_flags;
	__le16				vlan_tag;
	__le32				rss_hash;
	__le16				len_on_first_bd;
	u8				placement_offset;
	struct tunnel_parsing_flags	tunnel_pars_flags;
	u8				bd_num;
	u8				reserved[7];
	u32				fw_debug;
	u8				reserved1[3];
	u8				flags;
#define ETH_FAST_PATH_RX_REG_CQE_VALID_MASK          0x1
#define ETH_FAST_PATH_RX_REG_CQE_VALID_SHIFT         0
#define ETH_FAST_PATH_RX_REG_CQE_VALID_TOGGLE_MASK   0x1
#define ETH_FAST_PATH_RX_REG_CQE_VALID_TOGGLE_SHIFT  1
#define ETH_FAST_PATH_RX_REG_CQE_RESERVED2_MASK      0x3F
#define ETH_FAST_PATH_RX_REG_CQE_RESERVED2_SHIFT     2
};

/* TPA-continue ETH Rx FP CQE. */
struct eth_fast_path_rx_tpa_cont_cqe {
	u8	type;
	u8	tpa_agg_index;
	__le16	len_list[ETH_TPA_CQE_CONT_LEN_LIST_SIZE];
	u8	reserved[5];
	u8	reserved1;
	__le16	reserved2[ETH_TPA_CQE_CONT_LEN_LIST_SIZE];
};

/* TPA-end ETH Rx FP CQE. */
struct eth_fast_path_rx_tpa_end_cqe {
	u8	type;
	u8	tpa_agg_index;
	__le16	total_packet_len;
	u8	num_of_bds;
	u8	end_reason;
	__le16	num_of_coalesced_segs;
	__le32	ts_delta;
	__le16	len_list[ETH_TPA_CQE_END_LEN_LIST_SIZE];
	u8	reserved1[3];
	u8	reserved2;
	__le16	reserved3[ETH_TPA_CQE_END_LEN_LIST_SIZE];
};

/* TPA-start ETH Rx FP CQE. */
struct eth_fast_path_rx_tpa_start_cqe {
	u8	type;
	u8	bitfields;
#define ETH_FAST_PATH_RX_TPA_START_CQE_RSS_HASH_TYPE_MASK  0x7
#define ETH_FAST_PATH_RX_TPA_START_CQE_RSS_HASH_TYPE_SHIFT 0
#define ETH_FAST_PATH_RX_TPA_START_CQE_TC_MASK             0xF
#define ETH_FAST_PATH_RX_TPA_START_CQE_TC_SHIFT            3
#define ETH_FAST_PATH_RX_TPA_START_CQE_RESERVED0_MASK      0x1
#define ETH_FAST_PATH_RX_TPA_START_CQE_RESERVED0_SHIFT     7
	__le16	seg_len;
	struct parsing_and_err_flags pars_flags;
	__le16	vlan_tag;
	__le32	rss_hash;
	__le16	len_on_first_bd;
	u8	placement_offset;
	struct tunnel_parsing_flags tunnel_pars_flags;
	u8	tpa_agg_index;
	u8	header_len;
	__le16	ext_bd_len_list[ETH_TPA_CQE_START_LEN_LIST_SIZE];
	u32	fw_debug;
};

/* The L4 pseudo checksum mode for Ethernet */
enum eth_l4_pseudo_checksum_mode {
	ETH_L4_PSEUDO_CSUM_CORRECT_LENGTH,
	ETH_L4_PSEUDO_CSUM_ZERO_LENGTH,
	MAX_ETH_L4_PSEUDO_CHECKSUM_MODE
};

struct eth_rx_bd {
	struct regpair addr;
};

/* regular ETH Rx SP CQE */
struct eth_slow_path_rx_cqe {
	u8	type;
	u8	ramrod_cmd_id;
	u8	error_flag;
	u8	reserved[25];
	__le16	echo;
	u8	reserved1;
	u8	flags;
/* for PMD mode - valid indication */
#define ETH_SLOW_PATH_RX_CQE_VALID_MASK         0x1
#define ETH_SLOW_PATH_RX_CQE_VALID_SHIFT        0
/* for PMD mode - valid toggle indication */
#define ETH_SLOW_PATH_RX_CQE_VALID_TOGGLE_MASK  0x1
#define ETH_SLOW_PATH_RX_CQE_VALID_TOGGLE_SHIFT 1
#define ETH_SLOW_PATH_RX_CQE_RESERVED2_MASK     0x3F
#define ETH_SLOW_PATH_RX_CQE_RESERVED2_SHIFT    2
};

/* union for all ETH Rx CQE types */
union eth_rx_cqe {
	struct eth_fast_path_rx_reg_cqe		fast_path_regular;
	struct eth_fast_path_rx_tpa_start_cqe	fast_path_tpa_start;
	struct eth_fast_path_rx_tpa_cont_cqe	fast_path_tpa_cont;
	struct eth_fast_path_rx_tpa_end_cqe	fast_path_tpa_end;
	struct eth_slow_path_rx_cqe		slow_path;
};

/* ETH Rx CQE type */
enum eth_rx_cqe_type {
	ETH_RX_CQE_TYPE_UNUSED,
	ETH_RX_CQE_TYPE_REGULAR,
	ETH_RX_CQE_TYPE_SLOW_PATH,
	ETH_RX_CQE_TYPE_TPA_START,
	ETH_RX_CQE_TYPE_TPA_CONT,
	ETH_RX_CQE_TYPE_TPA_END,
	MAX_ETH_RX_CQE_TYPE
};

/* ETH Rx producers data */
struct eth_rx_prod_data {
	__le16	bd_prod;
	__le16	cqe_prod;
	__le16	reserved;
	__le16	reserved1;
};

/* The first tx bd of a given packet */
struct eth_tx_1st_bd {
	struct regpair			addr;
	__le16				nbytes;
	struct eth_tx_data_1st_bd	data;
};

/* The second tx bd of a given packet */
struct eth_tx_2nd_bd {
	struct regpair			addr;
	__le16				nbytes;
	struct eth_tx_data_2nd_bd	data;
};

/* The parsing information data for the third tx bd of a given packet. */
struct eth_tx_data_3rd_bd {
	__le16	lso_mss;
	__le16	bitfields;
#define ETH_TX_DATA_3RD_BD_TCP_HDR_LEN_DW_MASK  0xF
#define ETH_TX_DATA_3RD_BD_TCP_HDR_LEN_DW_SHIFT 0
#define ETH_TX_DATA_3RD_BD_HDR_NBD_MASK         0xF
#define ETH_TX_DATA_3RD_BD_HDR_NBD_SHIFT        4
#define ETH_TX_DATA_3RD_BD_START_BD_MASK        0x1
#define ETH_TX_DATA_3RD_BD_START_BD_SHIFT       8
#define ETH_TX_DATA_3RD_BD_RESERVED0_MASK       0x7F
#define ETH_TX_DATA_3RD_BD_RESERVED0_SHIFT      9
	u8	tunn_l4_hdr_start_offset_w;
	u8	tunn_hdr_size_w;
};

/* The third tx bd of a given packet */
struct eth_tx_3rd_bd {
	struct regpair			addr;
	__le16				nbytes;
	struct eth_tx_data_3rd_bd	data;
};

/* Complementary information for the regular tx bd of a given packet. */
struct eth_tx_data_bd {
	__le16	reserved0;
	__le16	bitfields;
#define ETH_TX_DATA_BD_RESERVED1_MASK  0xFF
#define ETH_TX_DATA_BD_RESERVED1_SHIFT 0
#define ETH_TX_DATA_BD_START_BD_MASK   0x1
#define ETH_TX_DATA_BD_START_BD_SHIFT  8
#define ETH_TX_DATA_BD_RESERVED2_MASK  0x7F
#define ETH_TX_DATA_BD_RESERVED2_SHIFT 9
	__le16 reserved3;
};

/* The common non-special TX BD ring element */
struct eth_tx_bd {
	struct regpair	addr;
	__le16		nbytes;
	struct eth_tx_data_bd	data;
};

union eth_tx_bd_types {
	struct eth_tx_1st_bd	first_bd;
	struct eth_tx_2nd_bd	second_bd;
	struct eth_tx_3rd_bd	third_bd;
	struct eth_tx_bd	reg_bd;
};

/* Mstorm Queue Zone */
struct mstorm_eth_queue_zone {
	struct eth_rx_prod_data rx_producers;
	__le32			reserved[2];
};

/* Ustorm Queue Zone */
struct ustorm_eth_queue_zone {
	struct coalescing_timeset	int_coalescing_timeset;
	__le16				reserved[3];
};

/* Ystorm Queue Zone */
struct ystorm_eth_queue_zone {
	struct coalescing_timeset	int_coalescing_timeset;
	__le16				reserved[3];
};

/* ETH doorbell data */
struct eth_db_data {
	u8 params;
#define ETH_DB_DATA_DEST_MASK         0x3
#define ETH_DB_DATA_DEST_SHIFT        0
#define ETH_DB_DATA_AGG_CMD_MASK      0x3
#define ETH_DB_DATA_AGG_CMD_SHIFT     2
#define ETH_DB_DATA_BYPASS_EN_MASK    0x1
#define ETH_DB_DATA_BYPASS_EN_SHIFT   4
#define ETH_DB_DATA_RESERVED_MASK     0x1
#define ETH_DB_DATA_RESERVED_SHIFT    5
#define ETH_DB_DATA_AGG_VAL_SEL_MASK  0x3
#define ETH_DB_DATA_AGG_VAL_SEL_SHIFT 6
	u8	agg_flags;
	__le16	bd_prod;
};

#endif /* __ETH_COMMON__ */
