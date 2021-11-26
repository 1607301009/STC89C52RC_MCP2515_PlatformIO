#ifndef __TYPE_H
#define __TYPE_H


/* Configuration Registers */
#define CANSTAT         0x0E
#define CANCTRL         0x0F
#define BFPCTRL         0x0C
#define TEC             0x1C
#define REC             0x1D
#define CNF3            0x28
#define CNF2            0x29
#define CNF1            0x2A
#define CANINTE         0x2B
#define CANINTF         0x2C
#define EFLG            0x2D
#define TXRTSCTRL       0x0D

/*  Recieve Filters */
#define RXF0SIDH        0x00
#define RXF0SIDL        0x01
#define RXF0EID8        0x02
#define RXF0EID0        0x03

#define RXF1SIDH        0x04
#define RXF1SIDL        0x05
#define RXF1EID8        0x06
#define RXF1EID0        0x07

#define RXF2SIDH        0x08
#define RXF2SIDL        0x09
#define RXF2EID8        0x0A
#define RXF2EID0        0x0B

#define RXF3SIDH        0x10
#define RXF3SIDL        0x11
#define RXF3EID8        0x12
#define RXF3EID0        0x13

#define RXF4SIDH        0x14
#define RXF4SIDL        0x15
#define RXF4EID8        0x16
#define RXF4EID0        0x17

#define RXF5SIDH        0x18
#define RXF5SIDL        0x19
#define RXF5EID8        0x1A
#define RXF5EID0        0x1B

/* Receive Masks */
#define RXM0SIDH        0x20
#define RXM0SIDL        0x21
#define RXM0EID8        0x22
#define RXM0EID0        0x23

#define RXM1SIDH        0x24
#define RXM1SIDL        0x25
#define RXM1EID8        0x26
#define RXM1EID0        0x27

/* Tx Buffer 0 */
#define TXB0CTRL        0x30
#define TXB0SIDH        0x31
#define TXB0SIDL        0x32
#define TXB0EID8        0x33
#define TXB0EID0        0x34
#define TXB0DLC         0x35
#define TXB0D0          0x36
#define TXB0D1          0x37
#define TXB0D2          0x38
#define TXB0D3          0x39
#define TXB0D4          0x3A
#define TXB0D5          0x3B
#define TXB0D6          0x3C
#define TXB0D7          0x3D

/* Tx Buffer 1 */
#define TXB1CTRL        0x40
#define TXB1SIDH        0x41
#define TXB1SIDL        0x42
#define TXB1EID8        0x43
#define TXB1EID0        0x44
#define TXB1DLC         0x45
#define TXB1D0          0x46
#define TXB1D1          0x47
#define TXB1D2          0x48
#define TXB1D3          0x49
#define TXB1D4          0x4A
#define TXB1D5          0x4B
#define TXB1D6          0x4C
#define TXB1D7          0x4D

/* Tx Buffer 2 */
#define TXB2CTRL        0x50
#define TXB2SIDH        0x51
#define TXB2SIDL        0x52
#define TXB2EID8        0x53
#define TXB2EID0        0x54
#define TXB2DLC         0x55
#define TXB2D0          0x56
#define TXB2D1          0x57
#define TXB2D2          0x58
#define TXB2D3          0x59
#define TXB2D4          0x5A
#define TXB2D5          0x5B
#define TXB2D6          0x5C
#define TXB2D7          0x5D

/* Rx Buffer 0 */
#define RXB0CTRL		0x60
#define RXB0SIDH        0x61
#define RXB0SIDL        0x62
#define RXB0EID8        0x63
#define RXB0EID0        0x64
#define RXB0DLC         0x65
#define RXB0D0          0x66
#define RXB0D1          0x67
#define RXB0D2          0x68
#define RXB0D3          0x69
#define RXB0D4          0x6A
#define RXB0D5          0x6B
#define RXB0D6          0x6C
#define RXB0D7          0x6D

/* Rx Buffer 1 */
#define RXB1CTRL        0x70
#define RXB1SIDH        0x71
#define RXB1SIDL        0x72
#define RXB1EID8        0x73
#define RXB1EID0        0x74
#define RXB1DLC         0x75
#define RXB1D0          0x76
#define RXB1D1          0x77
#define RXB1D2          0x78
#define RXB1D3          0x79
#define RXB1D4          0x7A
#define RXB1D5          0x7B
#define RXB1D6          0x7C
#define RXB1D7          0x7D


/*******************************************************************
 *               Bit register masks                                *
 *******************************************************************/

/* TXBnCTRL */
#define TXREQ           0x08
#define TXP             0x03

/* RXBnCTRL */
#define RXM             0x60
#define BUKT            0x04

/* CANCTRL */
#define REQOP           0xE0
#define ABAT            0x10
#define	OSM             0x08
#define CLKEN           0x04
#define CLKPRE          0x03

/* CANSTAT */
#define REQOP           0xE0
#define ICOD            0x0E

/* CANINTE */
#define RX0IE           0x01
#define RX1IE           0x02
#define TX0IE           0x04
#define TX1IE           0x80
#define TX2IE           0x10
#define ERRIE           0x20
#define WAKIE           0x40
#define MERRE           0x80

/* CANINTF */
#define RX0IF           0x01
#define RX1IF           0x02
#define TX0IF           0x04
#define TX1IF           0x80
#define TX2IF           0x10
#define ERRIF           0x20
#define WAKIF           0x40
#define MERRF           0x80

/* BFPCTRL */
#define B1BFS           0x20
#define B0BFS           0x10
#define B1BFE           0x08
#define B0BFE           0x04
#define B1BFM           0x02
#define B0BFM           0x01

/* CNF1 Masks */
#define SJW             0xC0
#define BRP             0x3F

/* CNF2 Masks */
#define BTLMODE         0x80
#define SAM             0x40
#define PHSEG1          0x38
#define PRSEG           0x07

/* CNF3 Masks */
#define WAKFIL          0x40
#define PHSEG2          0x07

/* TXRTSCTRL Masks */
#define TXB2RTS         0x04
#define TXB1RTS         0x02
#define TXB0RTS         0x01


/*******************************************************************
 *                    Bit Timing Configuration                     *
 *******************************************************************/

/* CNF1 */
#define SJW_1TQ         0x00
#define SJW_2TQ         0x40
#define SJW_3TQ         0x80
#define SJW_4TQ         0xC0

/* CNF2 */
#define BTLMODE_CNF3    0x80
#define BTLMODE_PH1_IPT 0x00

#define SMPL_3X         0x40
#define SMPL_1X         0x00

#define PHSEG1_8TQ      0x38
#define PHSEG1_7TQ      0x30
#define PHSEG1_6TQ      0x28
#define PHSEG1_5TQ      0x20
#define PHSEG1_4TQ      0x18
#define PHSEG1_3TQ      0x10
#define PHSEG1_2TQ      0x08
#define PHSEG1_1TQ      0x00

#define PRSEG_8TQ       0x07
#define PRSEG_7TQ       0x06
#define PRSEG_6TQ       0x05
#define PRSEG_5TQ       0x04
#define PRSEG_4TQ       0x03
#define PRSEG_3TQ       0x02
#define PRSEG_2TQ       0x01
#define PRSEG_1TQ       0x00

/* CNF3 */
#define PHSEG2_8TQ      0x07
#define PHSEG2_7TQ      0x06
#define PHSEG2_6TQ      0x05
#define PHSEG2_5TQ      0x04
#define PHSEG2_4TQ      0x03
#define PHSEG2_3TQ      0x02
#define PHSEG2_2TQ      0x01
#define PHSEG2_1TQ      0x00

#define SOF_ENABLED     0x80
#define WAKFIL_ENABLED  0x40
#define WAKFIL_DISABLED 0x00


/*******************************************************************
 *                  Control/Configuration Registers                *
 *******************************************************************/

/* CANINTE */
#define RX0IE_ENABLED   0x01
#define RX0IE_DISABLED  0x00
#define RX1IE_ENABLED   0x02
#define RX1IE_DISABLED  0x00
#define G_RXIE_ENABLED  0x03
#define G_RXIE_DISABLED 0x00

#define TX0IE_ENABLED   0x04
#define TX0IE_DISABLED  0x00
#define TX1IE_ENABLED   0x08
#define TX2IE_DISABLED  0x00
#define TX2IE_ENABLED   0x10
#define TX2IE_DISABLED  0x00
#define G_TXIE_ENABLED  0x1C
#define G_TXIE_DISABLED 0x00

#define ERRIE_ENABLED   0x20
#define ERRIE_DISABLED  0x00
#define WAKIE_ENABLED   0x40
#define WAKIE_DISABLED  0x00
#define IVRE_ENABLED    0x80
#define IVRE_DISABLED   0x00

/* CANINTF */
#define RX0IF_SET       0x01
#define RX0IF_RESET     0x00
#define RX1IF_SET       0x02
#define RX1IF_RESET     0x00
#define TX0IF_SET       0x04
#define TX0IF_RESET     0x00
#define TX1IF_SET       0x08
#define TX2IF_RESET     0x00
#define TX2IF_SET       0x10
#define TX2IF_RESET     0x00
#define ERRIF_SET       0x20
#define ERRIF_RESET     0x00
#define WAKIF_SET       0x40
#define WAKIF_RESET     0x00
#define IVRF_SET        0x80
#define IVRF_RESET      0x00

/* CANCTRL */
#define REQOP_CONFIG    0x80
#define REQOP_LISTEN    0x60
#define REQOP_LOOPBACK  0x40
#define REQOP_SLEEP     0x20
#define REQOP_NORMAL    0x00

#define ABORT           0x10

#define OSM_ENABLED     0x08

#define CLKOUT_ENABLED  0x04
#define CLKOUT_DISABLED 0x00
#define CLKOUT_PRE_8    0x03
#define CLKOUT_PRE_4    0x02
#define CLKOUT_PRE_2    0x01
#define CLKOUT_PRE_1    0x00

/* CANSTAT */
#define OPMODE_CONFIG   0x80
#define OPMODE_LISTEN   0x60
#define OPMODE_LOOPBACK 0x40
#define OPMODE_SLEEP    0x20
#define OPMODE_NORMAL   0x00


/* RXBnCTRL */
#define RXM_RCV_ALL     0x60
#define RXM_VALID_EXT   0x40
#define RXM_VALID_STD   0x20
#define RXM_VALID_ALL   0x00

#define RXRTR_REMOTE    0x08
#define RXRTR_NO_REMOTE 0x00

#define BUKT_ROLLOVER    0x04
#define BUKT_NO_ROLLOVER 0x00

#define FILHIT0_FLTR_1  0x01
#define FILHIT0_FLTR_0  0x00

#define FILHIT1_FLTR_5  0x05
#define FILHIT1_FLTR_4  0x04
#define FILHIT1_FLTR_3  0x03
#define FILHIT1_FLTR_2  0x02
#define FILHIT1_FLTR_1  0x01
#define FILHIT1_FLTR_0  0x00


/* TXBnCTRL */
#define TXREQ_SET       0x08
#define TXREQ_CLEAR     0x00

#define TXP_HIGHEST     0x03
#define TXP_INTER_HIGH  0x02
#define TXP_INTER_LOW   0x01
#define TXP_LOWEST      0x00


/*******************************************************************
 *                  Register Bit Masks                             *
 *******************************************************************/

 #define DLC_0          0x00
 #define DLC_1          0x01
 #define DLC_2          0x02
 #define DLC_3          0x03
 #define DLC_4          0x04
 #define DLC_5          0x05
 #define DLC_6          0x06
 #define DLC_7          0x07
 #define DLC_8          0x08


/*******************************************************************
 *                  CAN SPI commands                               *
 *******************************************************************/

#define CAN_RESET       0xC0
#define CAN_READ        0x03
#define CAN_WRITE       0x02
#define CAN_RTS         0x80
#define CAN_RTS_TXB0    0x81
#define CAN_RTS_TXB1    0x82
#define CAN_RTS_TXB2    0x84
#define CAN_RD_STATUS   0xA0
#define CAN_BIT_MODIFY  0x05
#define CAN_RX_STATUS   0xB0
#define CAN_RD_RX_BUFF  0x90
#define CAN_LOAD_TX     0X40


/*******************************************************************
 *                  Miscellaneous                                  *
 *******************************************************************/

#define DUMMY_BYTE      0x00
#define TXB0            0x31
#define TXB1            0x41
#define TXB2            0x51
#define RXB0            0x61
#define RXB1            0x71
#define EXIDE_SET       0x08
#define EXIDE_RESET     0x00


//MCP2515������Ԥ��Ƶ	Ҫ����FOSC=8M BRP=0..64 PHSEG1=3..16 PGSEG2=2..8 SJW=1..4
#define    CAN_5Kbps      0x31    //TQ=12500 sample-point=0.875 PRSEG_6TQ PHSEG1_7TQ PHSEG2_2TQ SJW_1TQ
#define    CAN_10Kbps     0x13    //TQ=6250 sample-point=0.875 PRSEG_6TQ PHSEG1_7TQ PHSEG2_2TQ SJW_1TQ
#define    CAN_25Kbps     0x09    //TQ=2500 sample-point=0.875 PRSEG_6TQ PHSEG1_7TQ PHSEG2_2TQ SJW_1TQ
#define    CAN_50Kbps     0x04    //TQ=1250 sample-point=0.875 PRSEG_6TQ PHSEG1_7TQ PHSEG2_2TQ SJW_1TQ
#define    CAN_100Kbps    0x01    //TQ=500 sample-point=0.850 PRSEG_8TQ PHSEG1_8TQ PHSEG2_3TQ SJW_1TQ
#define    CAN_125Kbps    0x01    //TQ=500 sample-point=0.875 PRSEG_6TQ PHSEG1_7TQ PHSEG2_2TQ SJW_1TQ
#define    CAN_250Kbps    0x00    //TQ=250 sample-point=0.875 PRSEG_6TQ PHSEG1_7TQ PHSEG2_2TQ SJW_1TQ
#define    CAN_500Kbps    0x00    //TQ=250 sample-point=0.750 PRSEG_2TQ PHSEG1_3TQ PHSEG2_2TQ SJW_1TQ



/* E2 Config ������Ϣ ��E2 page��С���� */
#define E2_CanCifg         0x00
#define E2_RXM01ID         0x08
#define E2_RXF01           0x10
#define E2_RXF23           0x18
#define E2_RXF45           0x20


/* Config address ������Ϣ */
// page 0: Kbps, CAN_MODE, CANINTE, CANINTF, BUKT, RXB0RXM, RXB1RXM
//E2Read(E2_read_data, E2_CanCifg, 8);  // �� EEPROM ��ȡһ������
//CanCfg->_5Kbps = E2_read_data[E2_5Kbps];
//Set_Bitrate_Array(CanCfg->_5Kbps, CanCfg->bitrate);
//CanCfg->CAN_MODE = E2_read_data[E2_CAN_MODE];      // 0:���� 1:���� 2:���� 3:���� 4:����
//CanCfg->CANINTE_enable = E2_read_data[E2_CANINTE_enable];
//CanCfg->CANINTF_enable = E2_read_data[E2_CANINTF_enable];
////  ���ù���ʹ��λ������ģʽ���ж�ʹ��λ���жϱ�־λ
//CanCfg->BUKT_enable = E2_read_data[E2_BUKT_enable];
//CanCfg->RXB0RXM = E2_read_data[E2_RXB0RXM];
//CanCfg->RXB1RXM = E2_read_data[E2_RXB1RXM];
#define E2_5Kbps            0x0 // �����ʱ�־λ
#define E2_CAN_MODE         0x1 // ����ģʽ�� 1. ����ģʽ��
//          2. ����ģʽ��
//          3. ����ģʽ��
//          4. ������ģʽ��
//          5. ����ģʽ��
#define E2_CANINTE_enable   0x2
#define E2_CANINTF_enable   0x3
#define E2_BUKT_enable      0x4 // ����ʹ��λ
#define E2_RXB0RXM          0x5 // ���ջ�����0����ģʽ
// ���ջ�����0����ģʽλ 11 = �ر����Σ��˲����ܣ��������б���
//                   10 = ֻ���շ����˲��������Ĵ�����չ��ʶ������Ч����
//                   01 = ֻ���շ����˲��������Ĵ��б�׼��ʶ������Ч����
//                   00 = ���շ����˲������������д���չ��ʶ�����׼��ʶ������Ч����
#define E2_RXB1RXM          0x6 // ���ջ�����1����ģʽ p28


#define E2_RXF0ID   0x7
#define E2_RXF1ID   0x8
#define E2_RXF2ID   0x9
#define E2_RXF3ID   0xA
#define E2_RXF4ID   0xB
#define E2_RXF5ID   0xC

#define E2_RXM0ID   0xD
#define E2_RXM1ID   0xE



/* rec����״̬���� */
#define action_send_can_cfg 0xfe // �ϵ㷴����־λ
#define action_status       0xf0 // ���û��ȡ״̬
#define action_E2           0x1 // ����ʹ��λ
#define action_MCP2515      0x1 // ����ʹ��λ
#define save_config_E2      0x1 // ����ʹ��λ
#define read_config_E2      0x1 // ����ʹ��λ

/* ������״̬���� */
#define main_power_on      0x1 // �ϵ����
#define main_set_can_cfg   0x2 // ����Can config
#define main_send_can_cfg   0x3 // ����Can config
#define main_save_cfg  0x4 // ʹ��Can config

/* ���ø����˲��ڶ�ȡ���� */
#define RXF0_init_config      0x0 // ���ù���λ
#define RXF0_set_config      0x0 // ���ù���λ

typedef __bit bool;             // λ����
typedef unsigned char uint8;    // �޷���8λ���ͱ���
typedef unsigned int  uint16;    // �޷���16λ���ͱ���
typedef unsigned long  uint32;   // �޷���32λ���ͱ���


// p21 RTR Զ�̷��ͱ�־λ
typedef struct      // reveive �ṹ��
{
    uint32 ID;      // ֡ID
    uint8 FILHIT:3;      // �����˲�������λ��
    uint8 RTR:1;      // Զ��֡��־λ p21
    uint8 LEVEL:2;      // �������ȼ� p18
    uint8 TYPE:2;   // ֡����: ����֡�� Զ��֡�� ����֡�� ����֡
    uint8 IsSend:1; // ֡����: ����֡�� Զ��֡�� ����֡�� ����֡
    uint8 EXIDE:1;  // ֡��ʽ: ��׼֡�� ��չ֡

    uint8  DLC:4;   // ���ݳ�����λ <3:0> �������յ��������ֽڸ���

    uint8  DATA[8]; // ���ջ����� n �����ֶ��ֽ� m, �� 8 ���ֽڰ������ձ��ĵ�������Ϣ
} __xdata MsgStruct;

// BFPCTRL����RXnBF ���ſ��ƼĴ�����״̬�Ĵ��� ����ַ��0Ch�� p29 δ���������ļ�
// EFLG���������־�Ĵ��� ����ַ��2Dh�� p47 δ���������ļ�
typedef struct        // reveive �ṹ��
{
    uint8 _5Kbps;           // ������������λ: 5Kbps
    uint8 bitrate[5];       // ����������

    uint32 RXM0ID;       // ������Ĭ����ȫ����
    uint32 RXF0ID;       // �˲���0H
    uint32 RXF1ID;       // �˲���1H

    uint32 RXM1ID;       // ������Ĭ����ȫ����
    uint32 RXF2ID;       // �˲���2H
    uint32 RXF3ID;       // �˲���3H
    uint32 RXF4ID;       // �˲���4H
    uint32 RXF5ID;       // �˲���5H

    uint8 CANINTE_enable;     // �ж�ʹ��λ��p50
    uint8 CANINTF_enable;     // �жϱ�־λ��p51

    uint8 RXB0RXM:2;        // ���ջ�����0����ģʽλ 11 = �ر����Σ��˲����ܣ��������б���
    //  p27              10 = ֻ���շ����˲��������Ĵ�����չ��ʶ������Ч����
    //                   01 = ֻ���շ����˲��������Ĵ��б�׼��ʶ������Ч����
    //                   00 = ���շ����˲������������д���չ��ʶ�����׼��ʶ������Ч����
    uint8 RXB1RXM:2;        // ���ջ�����1����ģʽλ

    uint8 CAN_MODE:3;       // ����ģʽp58�� 0.���� 1.���� 2.���� 3.���� 4.����ģʽ��

    uint8 BUKT_enable:1;    // ���ջ�����0����1 ʹ��λ

    uint8 RXF0IDE:1;     // �˲���RXF0��չ֡��־λ
    uint8 RXF1IDE:1;     // �˲���RXF1��չ֡��־λ
    uint8 RXF2IDE:1;     // �˲���RXF2��չ֡��־λ
    uint8 RXF3IDE:1;     // �˲���RXF3��չ֡��־λ
    uint8 RXF4IDE:1;     // �˲���RXF4��չ֡��־λ
    uint8 RXF5IDE:1;     // �˲���RXF5��չ֡��־λ
}__xdata CanCfgStruct;


#endif