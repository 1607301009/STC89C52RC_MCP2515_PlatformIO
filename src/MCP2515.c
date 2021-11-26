/**********************************************************************************
 * �ļ���  ��MCP2515.c
 * ����    ��MCP2515����������         
 * ʵ��ƽ̨��NiRen_STC/IAP15���İ�(���û�STC15��Ƭ��������) + NiRen_MCP2515 CANģ��    
**********************************************************************************/

#include "STC89xx.h"
#include "type.h"
#include "I2C_ROM.h"

//MCP2515���Ŷ���
#define MCP2515_INT   P16 //MCP2515�ж�����		������û���õ���

#define MCP2515_SCK   P15 //SPIʱ������
#define MCP2515_MOSI  P14 //SPI��������ӻ���������
#define MCP2515_MISO  P13 //SPI��������ӻ��������
#define MCP2515_CS    P12 //SPIƬѡ����

/*******************************************************************************
* ������  : Delay_Nms
* ����    : ͨ�������ʱԼnms(��׼ȷ)
* ����    : x
* ˵��    : �˷�ʽ��ʱʱ���ǲ�׼ȷ��,׼ȷ��ʱ�����ö�ʱ��
*******************************************************************************/
void Delay_Nms(uint16 x)
{
	uint16 y;

	for (;x>0;x--)
		for (y=0;y<100;y++);
}

/*******************************************************************************
* ������  : Exint_Init
* ����    : �ⲿ�ж�1��ʼ������
*******************************************************************************/
void Exint_Init(void) {
    PX1 = 1;    //�����ⲿ�ж�1���ж����ȼ�Ϊ�����ȼ�
    IT1 = 1;    //����INT1���ж����� (1:���½��� 0:�����غ��½���)
    EX1 = 1;    //ʹ��INT1�ж�
    EA = 1;     //ʹ�����ж�
}

/*******************************************************************************
* ������  : SPI_ReadByte
* ����    : ͨ��SPI��ȡһ���ֽ�����
* ����    : ��
* ���    : ��
* ����ֵ  : rByte(��ȡ����һ���ֽ�����)
* ˵��    : ��
*******************************************************************************/
uint8 SPI_ReadByte(void) {
    uint8 i, rByte = 0;

    MCP2515_SCK = 0;
    for (i = 0; i < 8; i++) {
        MCP2515_SCK = 1;
        rByte <<= 1;
        rByte |= MCP2515_MISO;
        MCP2515_SCK = 0;
    }
    return rByte;
}

/*******************************************************************************
* ������  : SPI_SendByte
* ����    : SPI����һ���ֽ�����
* ����    : dt:�����͵�����
* ���    : ��
* ����ֵ  : ��
* ˵��    : ��
*******************************************************************************/
void SPI_SendByte(uint8 dt) {
    uint8 i;
    for (i = 0; i < 8; i++) {
        MCP2515_SCK = 0;
        if ((dt << i) & 0x80)
            MCP2515_MOSI = 1;
        else
            MCP2515_MOSI = 0;
        MCP2515_SCK = 1;
    }
    MCP2515_SCK = 0;
}

/*******************************************************************************
* ������  : MCP2515_WriteByte
* ����    : ͨ��SPI��MCP2515ָ����ַ�Ĵ���д1���ֽ�����
* ����    : addr:MCP2515�Ĵ�����ַ,dat:��д�������
* ���    : ��
* ����ֵ  : ��
* ˵��    : ��
*******************************************************************************/
void MCP2515_WriteByte(uint8 addr, uint8 dat) {
    MCP2515_CS = 0;                //��MCP2515��CSΪ�͵�ƽ
    SPI_SendByte(CAN_WRITE);    //����д����
    SPI_SendByte(addr);            //���͵�ַ
    SPI_SendByte(dat);            //д������
    MCP2515_CS = 1;                //��MCP2515��CSΪ�ߵ�ƽ
}

/*******************************************************************************
* ������  : MCP2515_ReadByte
* ����    : ͨ��SPI��MCP2515ָ����ַ������1���ֽ�����
* ����    : addr:MCP2515�Ĵ�����ַ
* ���    : ��
* ����ֵ  : rByte:��ȡ���Ĵ�����1���ֽ�����
* ˵��    : ��
*******************************************************************************/
uint8 MCP2515_ReadByte(uint8 addr) {
    uint8 rByte;

    MCP2515_CS = 0;                //��MCP2515��CSΪ�͵�ƽ
    SPI_SendByte(CAN_READ);        //���Ͷ�����
    SPI_SendByte(addr);            //���͵�ַ
    rByte = SPI_ReadByte();        //��ȡ����
    MCP2515_CS = 1;                //��MCP2515��CSΪ�ߵ�ƽ
    return rByte;                //���ض�����һ���ֽ�����
}

/*******************************************************************************
* ������  : MCP2515_Reset
* ����    : ���͸�λָ�������λMCP2515
* ����    : ��
* ���    : ��
* ����ֵ  : ��
* ˵��    : ���ڲ��Ĵ�����λΪȱʡ״̬,���������趨Ϊ����ģʽ
*******************************************************************************/
void MCP2515_Reset(void) {
    MCP2515_CS = 0;                //��MCP2515��CSΪ�͵�ƽ
    SPI_SendByte(CAN_RESET);    //���ͼĴ�����λ����
    MCP2515_CS = 1;                //��MCP2515��CSΪ�ߵ�ƽ
}

/*******************************************************************************
* ����    : ��������ƴ�ӳ�ID��Ĭ�������λ�ĵ�һλΪ��չ��־λ��������
* ����    : array�����飬 offset��ID�������λ��
*******************************************************************************/
uint32 Get_ID_For_Array(uint8 *array, uint8 offset) {
    // 0bit RTRglag  1bit ERRORflag  2bit IDEflag
    return (((uint32) array[0 + offset] & 0x1F) << 24) |
           ((uint32) array[1 + offset] << 16) |
           ((uint32) array[2 + offset] << 8) |
           array[3 + offset];
}

/*******************************************************************************
* ����    : ��ID��֣�д�������У�Ĭ�������λ�ĵ�һλΪ��չ��־λ��
* ����    : array�����飬 offset��ID��λд�������λ�ã�
*******************************************************************************/
void Set_Array_For_ID(uint8 *array, uint8 offset, uint32 ID, uint8 flag) {
    // 0bit RTRglag  1bit ERRORflag  2bit IDEflag
    array[0 + offset] = (ID >> 24) & 0x1F| (flag << 5);
    array[1 + offset] = (ID >> 16) & 0xFF;
    array[2 + offset] = (ID >> 8) & 0xFF;
    array[3 + offset] = ID & 0xFF;
}

/*******************************************************************************
* ����    : ��mcp2515�Ĵ����ж�ȡ��ƴ�ӳ�ID����չ��־λ����ΪID��λ��
* ����    : buf_addr��mcp2515�Ĵ���SIDH�ĵ�ַ
*******************************************************************************/
uint32 Get_ID_For_Buf(uint8 buf_addr) {
    uint8 SIDL = MCP2515_ReadByte(buf_addr + 1);

    uint32 SID = ((uint32) MCP2515_ReadByte(buf_addr) << 3) | (SIDL >> 5);
    uint32 EID = (uint32) (SIDL & 3) << 16 |
                 ((uint32) MCP2515_ReadByte(buf_addr + 2) << 8) |
                 MCP2515_ReadByte(buf_addr + 3);
    // EID����ֵ������չ֡
    if (EID || (SIDL & 0x8)) {
        return SID << 18 | EID;
    } else {
        return SID;
    }
}

/*******************************************************************************
* ����    : ��ID���д�뵽mcp2515�Ĵ�����
* ����    : buf_addr��mcp2515�Ĵ���SIDH�ĵ�ַ�� ID�� �Լ���չ��־λ
*******************************************************************************/
void Set_Buf_For_ID(uint8 buf_addr, uint32 ID, uint8 EXIDE) {
    if ((ID > 0x7FF) || EXIDE) {
        MCP2515_WriteByte(buf_addr, ID >> 21);               //SIDH
        MCP2515_WriteByte(buf_addr + 1, (ID >> 18 & 0x07) << 5 | (ID >> 16 & 0x03) | 0x08);      //SIDL
        MCP2515_WriteByte(buf_addr + 2, ID >> 8 & 0xFF);     //EID8
        MCP2515_WriteByte(buf_addr + 3, ID & 0xFF);          //EID0
    } else {
        MCP2515_WriteByte(buf_addr, ID >> 3);                //SIDH
        MCP2515_WriteByte(buf_addr + 1, (ID & 0x07) << 5);   //SIDL
        MCP2515_WriteByte(buf_addr + 2, 0);                  //EID8
        MCP2515_WriteByte(buf_addr + 3, 0);                  //EID0
    }
}

/*******************************************************************************
* ����    : ���ñ���������
* ˵��    : MCP2515������	������ݮ���ص㣬Ҫ����FOSC=8M BRP=0..64 PRSEG=1..8 PHSEG1=3..16 PHSEG2=2..8 SJW=1..4
*******************************************************************************/
void Set_Bitrate_Array(uint8 _5Kbps, uint8 *bitrate) {
    uint8 kbps, prseg, phseg1, phseg2, sjw;
    switch (_5Kbps * 5) {
        case 5:
            kbps = CAN_5Kbps, prseg = PRSEG_6TQ, phseg1 = PHSEG1_7TQ, phseg2 = PHSEG2_2TQ, sjw = SJW_1TQ;
            break;
        case 10:
            kbps = CAN_10Kbps, prseg = PRSEG_6TQ, phseg1 = PHSEG1_7TQ, phseg2 = PHSEG2_2TQ, sjw = SJW_1TQ;
            break;
        case 25:
            kbps = CAN_25Kbps, prseg = PRSEG_6TQ, phseg1 = PHSEG1_7TQ, phseg2 = PHSEG2_2TQ, sjw = SJW_1TQ;
            break;
        case 50:
            kbps = CAN_50Kbps, prseg = PRSEG_6TQ, phseg1 = PHSEG1_7TQ, phseg2 = PHSEG2_2TQ, sjw = SJW_1TQ;
            break;
        case 100:
            kbps = CAN_100Kbps, prseg = PRSEG_8TQ, phseg1 = PHSEG1_8TQ, phseg2 = PHSEG2_3TQ, sjw = SJW_1TQ;
            break;
        case 125:
            kbps = CAN_125Kbps, prseg = PRSEG_6TQ, phseg1 = PHSEG1_7TQ, phseg2 = PHSEG2_2TQ, sjw = SJW_1TQ;
            break;
        case 250:
            kbps = CAN_250Kbps, prseg = PRSEG_6TQ, phseg1 = PHSEG1_7TQ, phseg2 = PHSEG2_2TQ, sjw = SJW_1TQ;
            break;
        default : /* Ĭ��ȡ500Kbps */
            kbps = CAN_500Kbps, prseg = PRSEG_2TQ, phseg1 = PHSEG1_3TQ, phseg2 = PHSEG2_2TQ, sjw = SJW_1TQ;
    }
    bitrate[0] = kbps, bitrate[1] = prseg, bitrate[2] = phseg1, bitrate[3] = phseg2, bitrate[4] = sjw;
}

void Can_Init(CanCfgStruct *CanCfg)
{
    MCP2515_Reset();    //���͸�λָ�������λMCP2515�� �Զ���������ģʽ
    Delay_Nms(1);        //ͨ�������ʱԼnms(��׼ȷ)

//    //����MCP2515����ģʽ
//    MCP2515_WriteByte(CANCTRL, REQOP_CONFIG | CLKOUT_ENABLED);
//    if ((MCP2515_ReadByte(CANSTAT) >> 5) != REQOP_CONFIG)//�ж�MCP2515�Ƿ��Ѿ����빤��ģʽ
//    {
//        MCP2515_WriteByte(CANCTRL, REQOP_CONFIG | CLKOUT_ENABLED);//�ٴ�����MCP2515��������ģʽ
//    }

    // ���ò�����
    // set CNF1, SJW=00,����Ϊ1TQ, BRP=49, TQ=[2*(BRP+1)]/Fsoc=2*50/8M=12.5us
    MCP2515_WriteByte(CNF1, CanCfg->bitrate[4] | CanCfg->bitrate[0]);
    // set CNF2, SAM=0,�ڲ���������߽���һ�β�����PHSEG1=(2+1)TQ=3TQ, PRSEG=(0+1)TQ=1TQ
    MCP2515_WriteByte(CNF2, BTLMODE_CNF3 | CanCfg->bitrate[2] | CanCfg->bitrate[1]);
    // set CNF3, PHSEG2=(2+1)TQ=3TQ,ͬʱ��CANCTRL.CLKEN=1ʱ�趨CLKOUT����Ϊʱ�����ʹ��λ
    MCP2515_WriteByte(CNF3, SOF_ENABLED | CanCfg->bitrate[3]);

    MCP2515_WriteByte(RXB0CTRL, CanCfg->BUKT_enable << 2);  // ���RXB0��,RXB0 ���յ��ı��Ľ���������RXB1

    MCP2515_WriteByte(RXB1CTRL, RXM);  // �������б���

    MCP2515_WriteByte(CANINTF, CanCfg->CANINTF_enable);  // ���CAN�жϱ�־�Ĵ���������λ(������MCU���)
    MCP2515_WriteByte(CANINTE, CanCfg->CANINTE_enable);  // ����CAN�ж�ʹ�ܼĴ����Ľ��ջ�����0���ж�ʹ��,����λ��ֹ�ж�

    // ���������˲���
    Set_Buf_For_ID(RXF0SIDH, CanCfg->RXF0ID, CanCfg->RXF0IDE);
    Set_Buf_For_ID(RXF1SIDH, CanCfg->RXF1ID, CanCfg->RXF1IDE);
    Set_Buf_For_ID(RXF2SIDH, CanCfg->RXF2ID, CanCfg->RXF2IDE);
    Set_Buf_For_ID(RXF3SIDH, CanCfg->RXF3ID, CanCfg->RXF3IDE);
    Set_Buf_For_ID(RXF4SIDH, CanCfg->RXF4ID, CanCfg->RXF4IDE);
    Set_Buf_For_ID(RXF5SIDH, CanCfg->RXF5ID, CanCfg->RXF5IDE);
    // ��������������
    Set_Buf_For_ID(RXM0SIDH, CanCfg->RXM0ID, 1);
    Set_Buf_For_ID(RXM1SIDH, CanCfg->RXM1ID, 1);

    //����MCP2515����ģʽ
//    MCP2515_WriteByte(CANCTRL, (CanCfg->CAN_MODE << 5) | CLKOUT_ENABLED);
//    if ((MCP2515_ReadByte(CANSTAT) >> 5) != CanCfg->CAN_MODE)//�ж�MCP2515�Ƿ��Ѿ����빤��ģʽ
//    {
//        MCP2515_WriteByte(CANCTRL, CanCfg->CAN_MODE | CLKOUT_ENABLED);//�ٴν�MCP2515����Ϊ����ģʽ,�˳�����ģʽ
//    }
    MCP2515_WriteByte(CANCTRL, REQOP_LOOPBACK | CLKOUT_ENABLED);//��MCP2515����Ϊ����ģʽ,�˳�����ģʽ
    if (OPMODE_NORMAL != (MCP2515_ReadByte(CANSTAT) && 0xE0))//�ж�MCP2515�Ƿ��Ѿ����뻷��ģʽ
    {
        MCP2515_WriteByte(CANCTRL, REQOP_LOOPBACK | CLKOUT_ENABLED);//�ٴν�MCP2515����Ϊ����ģʽ,�˳�����ģʽ
    }
}

/*******************************************************************************
* ������  : CAN_Send_Buffer
* ����    : CAN����ָ�����ȵ�����
* ����    : *CAN_TX_Buf(���������ݻ�����ָ��),len(���������ݳ���)
* ���    : ��
* ����ֵ  : ��
* ˵��    :
* �Ľ���   ���ڱ��ķ���֮ǰ�� MCU Ӧ��CANINTE.TXInE λ���г�ʼ�����Ա��ڱ��ķ���ʱʹ�ܻ��ֹ�жϵĲ���
 *          ��д�뷢�ͻ�����֮ǰ�����뽫TXBnCTRL.TXREQ λ���㣨�������ͻ������޵ȴ����͵ı��ģ���
*******************************************************************************/
void CAN_Send_Msg(MsgStruct *SendMsg) {
    uint8 TXBnCTRL;         // ѡ���ͻ�����
    uint8 i;
    //�Ĵ���״̬��ȡTXB0-2�Ƿ�æµ��1Ϊæµ��0Ϊ���У� ���ǰ�������Ĵ���ȫ��æµ�� Ĭ��ʹ�õ�3��
    for (i = 0; i < 3; i++) //�����ַ�����ֱ������0�Ž���
    {
        TXBnCTRL = TXB0CTRL + 0xF * i;
        if ((MCP2515_ReadByte(TXBnCTRL) & TXREQ) == 0) {
            break;
        }
    }

    Set_Buf_For_ID(TXBnCTRL + 1, SendMsg->ID, SendMsg->EXIDE);

    // ����DLC�� Ĭ��Ϊ����֡ RTR=0   ���ڿ���Զ��֡
    MCP2515_WriteByte(TXBnCTRL + 5, SendMsg->DLC | (SendMsg->RTR << 6));

    for(i = 0;(i <= SendMsg->DLC && i <= 8); i++)
    {
        MCP2515_WriteByte(TXBnCTRL + 6 + i, SendMsg->DATA[i]);						  //D0_8�������͵�����д�뷢�ͻ���Ĵ���
    }

    MCP2515_CS=0;
    MCP2515_WriteByte(TXBnCTRL, TXREQ | SendMsg->LEVEL);	//CTRL ��ʼ����
    MCP2515_CS=1;
    // ������ʽ���ã����η��ͣ�Զ��֡����չ֡������״̬����Ӧ��

    // �ȴ����ķ��ͳɹ�
//    for(i = 0; i < 14; i++)
//    {
//        if ((MCP2515_ReadByte(TXBnCTRL) & TXREQ) == 0)
//        {
//            return;
//        }
//        Delay_Nms(100);
//    }
}



/*******************************************************************************
* ����    : ͨ����ȡ�洢���ݣ�����Can����
* ����    : Can���ýṹ��
* ˵��    : ����GetInt32FormE2ƴ�ӳ�����ID�� ��λ����չ��־λ
*******************************************************************************/
void Set_Cfg_From_E2(CanCfgStruct *CanCfg) {
    __xdata uint8 E2_read_data[8];

    // page 0: Kbps, CAN_MODE, CANINTE, CANINTF, BUKT, RXB0RXM, RXB1RXM
    //  ���ò�����
    E2Read(E2_read_data, E2_CanCifg, 8);  // �� EEPROM ��ȡһ������
    CanCfg->_5Kbps = E2_read_data[E2_5Kbps];
    Set_Bitrate_Array(CanCfg->_5Kbps, CanCfg->bitrate);
    CanCfg->CAN_MODE = E2_read_data[E2_CAN_MODE];      // 0:���� 1:���� 2:���� 3:���� 4:����
    CanCfg->CANINTE_enable = E2_read_data[E2_CANINTE_enable];
    CanCfg->CANINTF_enable = E2_read_data[E2_CANINTF_enable];
    //  ���ù���ʹ��λ������ģʽ���ж�ʹ��λ���жϱ�־λ
    CanCfg->BUKT_enable = E2_read_data[E2_BUKT_enable];
    CanCfg->RXB0RXM = E2_read_data[E2_RXB0RXM];
    CanCfg->RXB1RXM = E2_read_data[E2_RXB1RXM];

    //  ����������0 1
    E2Read(E2_read_data, E2_RXM01ID, 8);  // �� EEPROM ��ȡһ������
    CanCfg->RXM0ID = Get_ID_For_Array(E2_read_data, 0);
    CanCfg->RXM1ID = Get_ID_For_Array(E2_read_data, 4);

    //  �˲���0��1
    E2Read(E2_read_data, E2_RXF01, 8);  // �� EEPROM ��ȡһ������
    CanCfg->RXF0IDE = E2_read_data[1] & 0x8 >> 3;
    CanCfg->RXF0ID = Get_ID_For_Array(E2_read_data, 0);
    CanCfg->RXF1IDE = E2_read_data[4] & 0x8 >> 3;
    CanCfg->RXF1ID = Get_ID_For_Array(E2_read_data, 4);
    //  �˲���2��3
    E2Read(E2_read_data, E2_RXF23, 8);  // �� EEPROM ��ȡһ������
    CanCfg->RXF2IDE = E2_read_data[0] & 0x8 >> 3;
    CanCfg->RXF2ID = Get_ID_For_Array(E2_read_data, 0);
    CanCfg->RXF3IDE = E2_read_data[4] & 0x8 >> 3;
    CanCfg->RXF3ID = Get_ID_For_Array(E2_read_data, 4);
    //  �˲���4��5
    E2Read(E2_read_data, E2_RXF45, 8);  // �� EEPROM ��ȡһ������
    CanCfg->RXF4IDE = E2_read_data[0] & 0x8 >> 3;
    CanCfg->RXF4ID = Get_ID_For_Array(E2_read_data, 0);
    CanCfg->RXF5IDE = E2_read_data[4] & 0x8 >> 3;
    CanCfg->RXF5ID = Get_ID_For_Array(E2_read_data, 4);
}

void Send_Cfg(void) {
    MsgStruct SendMsg;
    uint8 Tmp;

    SendMsg.ID = Get_ID_For_Buf(RXB0CTRL);

    SendMsg.RTR = 0x1;
    SendMsg.EXIDE = MCP2515_ReadByte(RXB0CTRL + 1) >> 3 & 0x1;
    SendMsg.DLC = 0;
    CAN_Send_Msg(&SendMsg);
}