

/*
 * cpswregs.h - Header file for cpsw utilities
 *
 * Usage : none
 * Author: Alexander Zakharov, WAW Technologies Inc.
 * Date  : September, 2015
 */


#ifndef __CPSWREGS_H__
#define __CPSWREGS_H__


/* TI Common Platform Ethernet Switch */
#define CPSW_BASE_ADDR            0x4A100000
#define CPSW_BASE_SIZE            0x8000


/* Ethernet Switch Subsystem */
#define CPSW_SS_ADDR              0x4A100000
#define CPSW_SS_OFFSET            (CPSW_SS_ADDR - CPSW_BASE_ADDR)

#define SS_ID_VER                 (CPSW_SS_OFFSET + 0x0000)
#define SS_CONTROL                (CPSW_SS_OFFSET + 0x0004)
#define SS_SOFT_RESET             (CPSW_SS_OFFSET + 0x0008)
#define SS_STAT_PORT_EN           (CPSW_SS_OFFSET + 0x000C)
#define SS_PTYPE                  (CPSW_SS_OFFSET + 0x0010)
#define SS_SOFT_IDLE              (CPSW_SS_OFFSET + 0x0014)
#define SS_THRU_RATE              (CPSW_SS_OFFSET + 0x0018)
#define SS_GAP_THRESH             (CPSW_SS_OFFSET + 0x001C)
#define SS_TX_START_WDS           (CPSW_SS_OFFSET + 0x0020)
#define SS_FLOW_CONTROL           (CPSW_SS_OFFSET + 0x0024)
#define SS_VLAN_LTYPE             (CPSW_SS_OFFSET + 0x0028)
#define SS_TS_LTYPE               (CPSW_SS_OFFSET + 0x002C)
#define SS_DLR_LTYPE              (CPSW_SS_OFFSET + 0x0030)


/* Ethernet Switch Port Control */
#define CPSW_PORT_ADDR            0x4A100100
#define CPSW_PORT_OFFSET          (CPSW_PORT_ADDR - CPSW_BASE_ADDR)

#define PORT_P0_CONTROL           (CPSW_PORT_OFFSET + 0x0000)
#define PORT_P0_MAX_BLKS          (CPSW_PORT_OFFSET + 0x0008)
#define PORT_P0_BLK_CNT           (CPSW_PORT_OFFSET + 0x000C)
#define PORT_P0_TX_IN_CTL         (CPSW_PORT_OFFSET + 0x0010)
#define PORT_P0_PORT_VLAN         (CPSW_PORT_OFFSET + 0x0014)
#define PORT_P0_TX_PRI_MAP        (CPSW_PORT_OFFSET + 0x0018)
#define PORT_P0_CPDMA_TX_PRI_MAP  (CPSW_PORT_OFFSET + 0x001C)
#define PORT_P0_CPDMA_RX_CH_MAP   (CPSW_PORT_OFFSET + 0x0020)
#define PORT_P0_RX_DSCP_PRI_MAP0  (CPSW_PORT_OFFSET + 0x0030)
#define PORT_P0_RX_DSCP_PRI_MAP1  (CPSW_PORT_OFFSET + 0x0034)
#define PORT_P0_RX_DSCP_PRI_MAP2  (CPSW_PORT_OFFSET + 0x0038)
#define PORT_P0_RX_DSCP_PRI_MAP3  (CPSW_PORT_OFFSET + 0x003C)
#define PORT_P0_RX_DSCP_PRI_MAP4  (CPSW_PORT_OFFSET + 0x0040)
#define PORT_P0_RX_DSCP_PRI_MAP5  (CPSW_PORT_OFFSET + 0x0044)
#define PORT_P0_RX_DSCP_PRI_MAP6  (CPSW_PORT_OFFSET + 0x0048)
#define PORT_P0_RX_DSCP_PRI_MAP7  (CPSW_PORT_OFFSET + 0x004C)
#define PORT_P1_CONTROL           (CPSW_PORT_OFFSET + 0x0100)
#define PORT_P1_MAX_BLKS          (CPSW_PORT_OFFSET + 0x0108)
#define PORT_P1_BLK_CNT           (CPSW_PORT_OFFSET + 0x010C)
#define PORT_P1_TX_IN_CTL         (CPSW_PORT_OFFSET + 0x0110)
#define PORT_P1_PORT_VLAN         (CPSW_PORT_OFFSET + 0x0114)
#define PORT_P1_TX_PRI_MAP        (CPSW_PORT_OFFSET + 0x0118)
#define PORT_P1_TS_SEQ_MTYPE      (CPSW_PORT_OFFSET + 0x011C)
#define PORT_P1_SA_LO             (CPSW_PORT_OFFSET + 0x0120)
#define PORT_P1_SA_HI             (CPSW_PORT_OFFSET + 0x0124)
#define PORT_P1_SEND_PERCENT      (CPSW_PORT_OFFSET + 0x0128)
#define PORT_P1_RX_DSCP_PRI_MAP0  (CPSW_PORT_OFFSET + 0x0130)
#define PORT_P1_RX_DSCP_PRI_MAP1  (CPSW_PORT_OFFSET + 0x0134)
#define PORT_P1_RX_DSCP_PRI_MAP2  (CPSW_PORT_OFFSET + 0x0138)
#define PORT_P1_RX_DSCP_PRI_MAP3  (CPSW_PORT_OFFSET + 0x013C)
#define PORT_P1_RX_DSCP_PRI_MAP4  (CPSW_PORT_OFFSET + 0x0140)
#define PORT_P1_RX_DSCP_PRI_MAP5  (CPSW_PORT_OFFSET + 0x0144)
#define PORT_P1_RX_DSCP_PRI_MAP6  (CPSW_PORT_OFFSET + 0x0148)
#define PORT_P1_RX_DSCP_PRI_MAP7  (CPSW_PORT_OFFSET + 0x014C)
#define PORT_P2_CONTROL           (CPSW_PORT_OFFSET + 0x0200)
#define PORT_P2_MAX_BLKS          (CPSW_PORT_OFFSET + 0x0208)
#define PORT_P2_BLK_CNT           (CPSW_PORT_OFFSET + 0x020C)
#define PORT_P2_TX_IN_CTL         (CPSW_PORT_OFFSET + 0x0210)
#define PORT_P2_PORT_VLAN         (CPSW_PORT_OFFSET + 0x0214)
#define PORT_P2_TX_PRI_MAP        (CPSW_PORT_OFFSET + 0x0218)
#define PORT_P2_TS_SEQ_MTYPE      (CPSW_PORT_OFFSET + 0x021C)
#define PORT_P2_SA_LO             (CPSW_PORT_OFFSET + 0x0220)
#define PORT_P2_SA_HI             (CPSW_PORT_OFFSET + 0x0224)
#define PORT_P2_SEND_PERCENT      (CPSW_PORT_OFFSET + 0x0228)
#define PORT_P2_RX_DSCP_PRI_MAP0  (CPSW_PORT_OFFSET + 0x0230)
#define PORT_P2_RX_DSCP_PRI_MAP1  (CPSW_PORT_OFFSET + 0x0234)
#define PORT_P2_RX_DSCP_PRI_MAP2  (CPSW_PORT_OFFSET + 0x0238)
#define PORT_P2_RX_DSCP_PRI_MAP3  (CPSW_PORT_OFFSET + 0x023C)
#define PORT_P2_RX_DSCP_PRI_MAP4  (CPSW_PORT_OFFSET + 0x0240)
#define PORT_P2_RX_DSCP_PRI_MAP5  (CPSW_PORT_OFFSET + 0x0244)
#define PORT_P2_RX_DSCP_PRI_MAP6  (CPSW_PORT_OFFSET + 0x0248)
#define PORT_P2_RX_DSCP_PRI_MAP7  (CPSW_PORT_OFFSET + 0x024C)


/* CPPI DMA Controller Module */
#define CPSW_CPDMA_ADDR           0x4A100800
#define CPSW_CPDMA_OFFSET         (CPSW_CPDMA_ADDR - CPSW_BASE_ADDR)


/* Ethernet Statistics */
#define CPSW_STATS_ADDR           0x4A100900
#define CPSW_STATS_OFFSET         (CPSW_STATS_ADDR - CPSW_BASE_ADDR)


/* CPPI DMA State RAM */
#define CPSW_STATERAM_ADDR        0x4A100A00
#define CPSW_STATERAM_OFFSET      (CPSW_STATERAM_ADDR - CPSW_BASE_ADDR)


/* Ethernet Time Sync Module */
#define CPSW_CPTS_ADDR            0x4A100C00
#define CPSW_CPTS_OFFSET          (CPSW_CPTS_ADDR - CPSW_BASE_ADDR)

#define CPTS_IDVER                (CPSW_CPTS_OFFSET + 0x0000)
#define CPTS_CONTROL              (CPSW_CPTS_OFFSET + 0x0004)
#define CPTS_TS_PUSH              (CPSW_CPTS_OFFSET + 0x000C)
#define CPTS_TS_LOAD_VAL          (CPSW_CPTS_OFFSET + 0x0010)
#define CPTS_TS_LOAD_EN           (CPSW_CPTS_OFFSET + 0x0014)
#define CPTS_INTSTAT_RAW          (CPSW_CPTS_OFFSET + 0x0020)
#define CPTS_INTSTAT_MASKED       (CPSW_CPTS_OFFSET + 0x0024)
#define CPTS_INT_ENABLE           (CPSW_CPTS_OFFSET + 0x0028)
#define CPTS_EVENT_POP            (CPSW_CPTS_OFFSET + 0x0030)
#define CPTS_EVENT_LOW            (CPSW_CPTS_OFFSET + 0x0034)
#define CPTS_EVENT_HIGH           (CPSW_CPTS_OFFSET + 0x0038)


/* Ethernet Address Lookup Engine */
#define CPSW_ALE_ADDR             0x4A100D00
#define CPSW_ALE_OFFSET           (CPSW_ALE_ADDR - CPSW_BASE_ADDR)

#define ALE_IDVER                 (CPSW_ALE_OFFSET + 0x0000)
#define ALE_CONTROL               (CPSW_ALE_OFFSET + 0x0008)
#define ALE_PRESCALE              (CPSW_ALE_OFFSET + 0x0010)
#define ALE_UNKNOWN_VLAN          (CPSW_ALE_OFFSET + 0x0018)
#define ALE_TBLCTL                (CPSW_ALE_OFFSET + 0x0020)
#define ALE_TBLW2                 (CPSW_ALE_OFFSET + 0x0034)
#define ALE_TBLW1                 (CPSW_ALE_OFFSET + 0x0038)
#define ALE_TBLW0                 (CPSW_ALE_OFFSET + 0x003C)
#define ALE_PORTCTL0              (CPSW_ALE_OFFSET + 0x0040)
#define ALE_PORTCTL1              (CPSW_ALE_OFFSET + 0x0044)
#define ALE_PORTCTL2              (CPSW_ALE_OFFSET + 0x0048)
#define ALE_PORTCTL3              (CPSW_ALE_OFFSET + 0x004C)
#define ALE_PORTCTL4              (CPSW_ALE_OFFSET + 0x0050)
#define ALE_PORTCTL5              (CPSW_ALE_OFFSET + 0x0054)


/* Ethernet Sliver for Port #1 */
#define CPSW_SL1_ADDR             0x4A100D80
#define CPSW_SL1_OFFSET           (CPSW_SL1_ADDR - CPSW_BASE_ADDR)

#define SL1_IDVER                 (CPSW_SL1_OFFSET + 0x0000)
#define SL1_MACCONTROL            (CPSW_SL1_OFFSET + 0x0004)
#define SL1_MACSTATUS             (CPSW_SL1_OFFSET + 0x0008)
#define SL1_SOFT_RESET            (CPSW_SL1_OFFSET + 0x000C)
#define SL1_RX_MAXLEN             (CPSW_SL1_OFFSET + 0x0010)
#define SL1_BOFFTEST              (CPSW_SL1_OFFSET + 0x0014)
#define SL1_RX_PAUSE              (CPSW_SL1_OFFSET + 0x0018)
#define SL1_TX_PAUSE              (CPSW_SL1_OFFSET + 0x001C)
#define SL1_EMCONTROL             (CPSW_SL1_OFFSET + 0x0020)
#define SL1_RX_PRI_MAP            (CPSW_SL1_OFFSET + 0x0024)
#define SL1_TX_GAP                (CPSW_SL1_OFFSET + 0x0028)


/* Ethernet Sliver for Port #2 */
#define CPSW_SL2_ADDR             0x4A100DC0
#define CPSW_SL2_OFFSET           (CPSW_SL2_ADDR - CPSW_BASE_ADDR)

#define SL2_IDVER                 (CPSW_SL2_OFFSET + 0x0000)
#define SL2_MACCONTROL            (CPSW_SL2_OFFSET + 0x0004)
#define SL2_MACSTATUS             (CPSW_SL2_OFFSET + 0x0008)
#define SL2_SOFT_RESET            (CPSW_SL2_OFFSET + 0x000C)
#define SL2_RX_MAXLEN             (CPSW_SL2_OFFSET + 0x0010)
#define SL2_BOFFTEST              (CPSW_SL2_OFFSET + 0x0014)
#define SL2_RX_PAUSE              (CPSW_SL2_OFFSET + 0x0018)
#define SL2_TX_PAUSE              (CPSW_SL2_OFFSET + 0x001C)
#define SL2_EMCONTROL             (CPSW_SL2_OFFSET + 0x0020)
#define SL2_RX_PRI_MAP            (CPSW_SL2_OFFSET + 0x0024)
#define SL2_TX_GAP                (CPSW_SL2_OFFSET + 0x0028)


/* Ethernet MDIO Controller */
#define CPSW_MDIO_ADDR            0x4A101000
#define CPSW_MDIO_OFFSET          (CPSW_MDIO_ADDR - CPSW_BASE_ADDR)

#define MDIO_VER                  (CPSW_MDIO_OFFSET + 0x0000)
#define MDIO_CONTROL              (CPSW_MDIO_OFFSET + 0x0004)
#define MDIO_ALIVE                (CPSW_MDIO_OFFSET + 0x0008)
#define MDIO_LINK                 (CPSW_MDIO_OFFSET + 0x000C)
#define MDIO_LINKINTRAW           (CPSW_MDIO_OFFSET + 0x0010)
#define MDIO_LINKINTMASKED        (CPSW_MDIO_OFFSET + 0x0014)
#define MDIO_USERINTRAW           (CPSW_MDIO_OFFSET + 0x0020)
#define MDIO_USERINTMASKED        (CPSW_MDIO_OFFSET + 0x0024)
#define MDIO_USERINTMASKSET       (CPSW_MDIO_OFFSET + 0x0028)
#define MDIO_USERINTMASKCLR       (CPSW_MDIO_OFFSET + 0x002C)
#define MDIO_USERACCESS0          (CPSW_MDIO_OFFSET + 0x0080)
#define MDIO_USERPHYSEL0          (CPSW_MDIO_OFFSET + 0x0084)
#define MDIO_USERACCESS1          (CPSW_MDIO_OFFSET + 0x0088)
#define MDIO_USERPHYSEL1          (CPSW_MDIO_OFFSET + 0x008C)


/* Ethernet Subsystem Wrapper for RMII/RGMII */
#define CPSW_WR_ADDR              0x4A101200
#define CPSW_WR_OFFSET            (CPSW_WR_ADDR - CPSW_BASE_ADDR)


#endif /* #ifndef __CPSWREGS_H__ */
