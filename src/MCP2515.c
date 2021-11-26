/**********************************************************************************
 * 文件名  ：MCP2515.c
 * 描述    ：MCP2515驱动函数库         
 * 实验平台：NiRen_STC/IAP15核心板(或用户STC15单片机开发板) + NiRen_MCP2515 CAN模块    
**********************************************************************************/

#include "STC89xx.h"
#include "type.h"
#include "I2C_ROM.h"

//MCP2515引脚定义
#define MCP2515_INT   P16 //MCP2515中断引脚		（好像没有用到）

#define MCP2515_SCK   P15 //SPI时钟引脚
#define MCP2515_MOSI  P14 //SPI主机输出从机输入引脚
#define MCP2515_MISO  P13 //SPI主机输入从机输出引脚
#define MCP2515_CS    P12 //SPI片选引脚

/*******************************************************************************
* 函数名  : Delay_Nms
* 描述    : 通过软件延时约nms(不准确)
* 输入    : x
* 说明    : 此方式延时时间是不准确的,准确延时建议用定时器
*******************************************************************************/
void Delay_Nms(uint16 x)
{
	uint16 y;

	for (;x>0;x--)
		for (y=0;y<100;y++);
}

/*******************************************************************************
* 函数名  : Exint_Init
* 描述    : 外部中断1初始化函数
*******************************************************************************/
void Exint_Init(void) {
    PX1 = 1;    //设置外部中断1的中断优先级为高优先级
    IT1 = 1;    //设置INT1的中断类型 (1:仅下降沿 0:上升沿和下降沿)
    EX1 = 1;    //使能INT1中断
    EA = 1;     //使能总中断
}

/*******************************************************************************
* 函数名  : SPI_ReadByte
* 描述    : 通过SPI读取一个字节数据
* 输入    : 无
* 输出    : 无
* 返回值  : rByte(读取到的一个字节数据)
* 说明    : 无
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
* 函数名  : SPI_SendByte
* 描述    : SPI发送一个字节数据
* 输入    : dt:待发送的数据
* 输出    : 无
* 返回值  : 无
* 说明    : 无
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
* 函数名  : MCP2515_WriteByte
* 描述    : 通过SPI向MCP2515指定地址寄存器写1个字节数据
* 输入    : addr:MCP2515寄存器地址,dat:待写入的数据
* 输出    : 无
* 返回值  : 无
* 说明    : 无
*******************************************************************************/
void MCP2515_WriteByte(uint8 addr, uint8 dat) {
    MCP2515_CS = 0;                //置MCP2515的CS为低电平
    SPI_SendByte(CAN_WRITE);    //发送写命令
    SPI_SendByte(addr);            //发送地址
    SPI_SendByte(dat);            //写入数据
    MCP2515_CS = 1;                //置MCP2515的CS为高电平
}

/*******************************************************************************
* 函数名  : MCP2515_ReadByte
* 描述    : 通过SPI从MCP2515指定地址寄器读1个字节数据
* 输入    : addr:MCP2515寄存器地址
* 输出    : 无
* 返回值  : rByte:读取到寄存器的1个字节数据
* 说明    : 无
*******************************************************************************/
uint8 MCP2515_ReadByte(uint8 addr) {
    uint8 rByte;

    MCP2515_CS = 0;                //置MCP2515的CS为低电平
    SPI_SendByte(CAN_READ);        //发送读命令
    SPI_SendByte(addr);            //发送地址
    rByte = SPI_ReadByte();        //读取数据
    MCP2515_CS = 1;                //置MCP2515的CS为高电平
    return rByte;                //返回读到的一个字节数据
}

/*******************************************************************************
* 函数名  : MCP2515_Reset
* 描述    : 发送复位指令软件复位MCP2515
* 输入    : 无
* 输出    : 无
* 返回值  : 无
* 说明    : 将内部寄存器复位为缺省状态,并将器件设定为配置模式
*******************************************************************************/
void MCP2515_Reset(void) {
    MCP2515_CS = 0;                //置MCP2515的CS为低电平
    SPI_SendByte(CAN_RESET);    //发送寄存器复位命令
    MCP2515_CS = 1;                //置MCP2515的CS为高电平
}

/*******************************************************************************
* 描述    : 从数组中拼接出ID，默认数组高位的第一位为扩展标志位，舍弃。
* 输入    : array：数组， offset：ID在数组的位置
*******************************************************************************/
uint32 Get_ID_For_Array(uint8 *array, uint8 offset) {
    // 0bit RTRglag  1bit ERRORflag  2bit IDEflag
    return (((uint32) array[0 + offset] & 0x1F) << 24) |
           ((uint32) array[1 + offset] << 16) |
           ((uint32) array[2 + offset] << 8) |
           array[3 + offset];
}

/*******************************************************************************
* 描述    : 将ID拆分，写入数组中，默认数组高位的第一位为扩展标志位。
* 输入    : array：数组， offset：ID高位写入数组的位置，
*******************************************************************************/
void Set_Array_For_ID(uint8 *array, uint8 offset, uint32 ID, uint8 flag) {
    // 0bit RTRglag  1bit ERRORflag  2bit IDEflag
    array[0 + offset] = (ID >> 24) & 0x1F| (flag << 5);
    array[1 + offset] = (ID >> 16) & 0xFF;
    array[2 + offset] = (ID >> 8) & 0xFF;
    array[3 + offset] = ID & 0xFF;
}

/*******************************************************************************
* 描述    : 从mcp2515寄存器中读取并拼接出ID，扩展标志位设置为ID首位。
* 输入    : buf_addr：mcp2515寄存器SIDH的地址
*******************************************************************************/
uint32 Get_ID_For_Buf(uint8 buf_addr) {
    uint8 SIDL = MCP2515_ReadByte(buf_addr + 1);

    uint32 SID = ((uint32) MCP2515_ReadByte(buf_addr) << 3) | (SIDL >> 5);
    uint32 EID = (uint32) (SIDL & 3) << 16 |
                 ((uint32) MCP2515_ReadByte(buf_addr + 2) << 8) |
                 MCP2515_ReadByte(buf_addr + 3);
    // EID有数值或是扩展帧
    if (EID || (SIDL & 0x8)) {
        return SID << 18 | EID;
    } else {
        return SID;
    }
}

/*******************************************************************************
* 描述    : 将ID拆分写入到mcp2515寄存器中
* 输入    : buf_addr：mcp2515寄存器SIDH的地址， ID， 以及扩展标志位
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
* 描述    : 设置比特率数组
* 说明    : MCP2515波特率	根据树莓派特点，要考虑FOSC=8M BRP=0..64 PRSEG=1..8 PHSEG1=3..16 PHSEG2=2..8 SJW=1..4
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
        default : /* 默认取500Kbps */
            kbps = CAN_500Kbps, prseg = PRSEG_2TQ, phseg1 = PHSEG1_3TQ, phseg2 = PHSEG2_2TQ, sjw = SJW_1TQ;
    }
    bitrate[0] = kbps, bitrate[1] = prseg, bitrate[2] = phseg1, bitrate[3] = phseg2, bitrate[4] = sjw;
}

void Can_Init(CanCfgStruct *CanCfg)
{
    MCP2515_Reset();    //发送复位指令软件复位MCP2515， 自动进入配置模式
    Delay_Nms(1);        //通过软件延时约nms(不准确)

//    //设置MCP2515工作模式
//    MCP2515_WriteByte(CANCTRL, REQOP_CONFIG | CLKOUT_ENABLED);
//    if ((MCP2515_ReadByte(CANSTAT) >> 5) != REQOP_CONFIG)//判断MCP2515是否已经进入工作模式
//    {
//        MCP2515_WriteByte(CANCTRL, REQOP_CONFIG | CLKOUT_ENABLED);//再次设置MCP2515进入配置模式
//    }

    // 设置波特率
    // set CNF1, SJW=00,长度为1TQ, BRP=49, TQ=[2*(BRP+1)]/Fsoc=2*50/8M=12.5us
    MCP2515_WriteByte(CNF1, CanCfg->bitrate[4] | CanCfg->bitrate[0]);
    // set CNF2, SAM=0,在采样点对总线进行一次采样，PHSEG1=(2+1)TQ=3TQ, PRSEG=(0+1)TQ=1TQ
    MCP2515_WriteByte(CNF2, BTLMODE_CNF3 | CanCfg->bitrate[2] | CanCfg->bitrate[1]);
    // set CNF3, PHSEG2=(2+1)TQ=3TQ,同时当CANCTRL.CLKEN=1时设定CLKOUT引脚为时间输出使能位
    MCP2515_WriteByte(CNF3, SOF_ENABLED | CanCfg->bitrate[3]);

    MCP2515_WriteByte(RXB0CTRL, CanCfg->BUKT_enable << 2);  // 如果RXB0满,RXB0 接收到的报文将被滚存至RXB1

    MCP2515_WriteByte(RXB1CTRL, RXM);  // 接收所有报文

    MCP2515_WriteByte(CANINTF, CanCfg->CANINTF_enable);  // 清空CAN中断标志寄存器的所有位(必须由MCU清空)
    MCP2515_WriteByte(CANINTE, CanCfg->CANINTE_enable);  // 配置CAN中断使能寄存器的接收缓冲器0满中断使能,其它位禁止中断

    // 设置验收滤波器
    Set_Buf_For_ID(RXF0SIDH, CanCfg->RXF0ID, CanCfg->RXF0IDE);
    Set_Buf_For_ID(RXF1SIDH, CanCfg->RXF1ID, CanCfg->RXF1IDE);
    Set_Buf_For_ID(RXF2SIDH, CanCfg->RXF2ID, CanCfg->RXF2IDE);
    Set_Buf_For_ID(RXF3SIDH, CanCfg->RXF3ID, CanCfg->RXF3IDE);
    Set_Buf_For_ID(RXF4SIDH, CanCfg->RXF4ID, CanCfg->RXF4IDE);
    Set_Buf_For_ID(RXF5SIDH, CanCfg->RXF5ID, CanCfg->RXF5IDE);
    // 设置验收屏蔽器
    Set_Buf_For_ID(RXM0SIDH, CanCfg->RXM0ID, 1);
    Set_Buf_For_ID(RXM1SIDH, CanCfg->RXM1ID, 1);

    //设置MCP2515工作模式
//    MCP2515_WriteByte(CANCTRL, (CanCfg->CAN_MODE << 5) | CLKOUT_ENABLED);
//    if ((MCP2515_ReadByte(CANSTAT) >> 5) != CanCfg->CAN_MODE)//判断MCP2515是否已经进入工作模式
//    {
//        MCP2515_WriteByte(CANCTRL, CanCfg->CAN_MODE | CLKOUT_ENABLED);//再次将MCP2515设置为环回模式,退出配置模式
//    }
    MCP2515_WriteByte(CANCTRL, REQOP_LOOPBACK | CLKOUT_ENABLED);//将MCP2515设置为环回模式,退出配置模式
    if (OPMODE_NORMAL != (MCP2515_ReadByte(CANSTAT) && 0xE0))//判断MCP2515是否已经进入环回模式
    {
        MCP2515_WriteByte(CANCTRL, REQOP_LOOPBACK | CLKOUT_ENABLED);//再次将MCP2515设置为环回模式,退出配置模式
    }
}

/*******************************************************************************
* 函数名  : CAN_Send_Buffer
* 描述    : CAN发送指定长度的数据
* 输入    : *CAN_TX_Buf(待发送数据缓冲区指针),len(待发送数据长度)
* 输出    : 无
* 返回值  : 无
* 说明    :
* 改进点   ：在报文发送之前， MCU 应对CANINTE.TXInE 位进行初始化，以便在报文发送时使能或禁止中断的产生
 *          在写入发送缓冲器之前，必须将TXBnCTRL.TXREQ 位清零（表明发送缓冲器无等待发送的报文）。
*******************************************************************************/
void CAN_Send_Msg(MsgStruct *SendMsg) {
    uint8 TXBnCTRL;         // 选择发送缓冲器
    uint8 i;
    //寄存器状态获取TXB0-2是否忙碌，1为忙碌，0为空闲， 如果前面两个寄存器全部忙碌， 默认使用第3个
    for (i = 0; i < 3; i++) //发送字符串，直到遇到0才结束
    {
        TXBnCTRL = TXB0CTRL + 0xF * i;
        if ((MCP2515_ReadByte(TXBnCTRL) & TXREQ) == 0) {
            break;
        }
    }

    Set_Buf_For_ID(TXBnCTRL + 1, SendMsg->ID, SendMsg->EXIDE);

    // 设置DLC， 默认为数据帧 RTR=0   后期开发远程帧
    MCP2515_WriteByte(TXBnCTRL + 5, SendMsg->DLC | (SendMsg->RTR << 6));

    for(i = 0;(i <= SendMsg->DLC && i <= 8); i++)
    {
        MCP2515_WriteByte(TXBnCTRL + 6 + i, SendMsg->DATA[i]);						  //D0_8将待发送的数据写入发送缓冲寄存器
    }

    MCP2515_CS=0;
    MCP2515_WriteByte(TXBnCTRL, TXREQ | SendMsg->LEVEL);	//CTRL 开始发送
    MCP2515_CS=1;
    // 发送形式设置：单次发送，远程帧，拓展帧，调试状态，回应。

    // 等待报文发送成功
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
* 描述    : 通过读取存储数据，设置Can配置
* 输入    : Can配置结构体
* 说明    : 依赖GetInt32FormE2拼接出完整ID， 首位做扩展标志位
*******************************************************************************/
void Set_Cfg_From_E2(CanCfgStruct *CanCfg) {
    __xdata uint8 E2_read_data[8];

    // page 0: Kbps, CAN_MODE, CANINTE, CANINTF, BUKT, RXB0RXM, RXB1RXM
    //  设置波特率
    E2Read(E2_read_data, E2_CanCifg, 8);  // 从 EEPROM 读取一段数据
    CanCfg->_5Kbps = E2_read_data[E2_5Kbps];
    Set_Bitrate_Array(CanCfg->_5Kbps, CanCfg->bitrate);
    CanCfg->CAN_MODE = E2_read_data[E2_CAN_MODE];      // 0:正常 1:休眠 2:环回 3:监听 4:配置
    CanCfg->CANINTE_enable = E2_read_data[E2_CANINTE_enable];
    CanCfg->CANINTF_enable = E2_read_data[E2_CANINTF_enable];
    //  设置滚存使能位、工作模式、中断使能位、中断标志位
    CanCfg->BUKT_enable = E2_read_data[E2_BUKT_enable];
    CanCfg->RXB0RXM = E2_read_data[E2_RXB0RXM];
    CanCfg->RXB1RXM = E2_read_data[E2_RXB1RXM];

    //  设置屏蔽器0 1
    E2Read(E2_read_data, E2_RXM01ID, 8);  // 从 EEPROM 读取一段数据
    CanCfg->RXM0ID = Get_ID_For_Array(E2_read_data, 0);
    CanCfg->RXM1ID = Get_ID_For_Array(E2_read_data, 4);

    //  滤波器0、1
    E2Read(E2_read_data, E2_RXF01, 8);  // 从 EEPROM 读取一段数据
    CanCfg->RXF0IDE = E2_read_data[1] & 0x8 >> 3;
    CanCfg->RXF0ID = Get_ID_For_Array(E2_read_data, 0);
    CanCfg->RXF1IDE = E2_read_data[4] & 0x8 >> 3;
    CanCfg->RXF1ID = Get_ID_For_Array(E2_read_data, 4);
    //  滤波器2、3
    E2Read(E2_read_data, E2_RXF23, 8);  // 从 EEPROM 读取一段数据
    CanCfg->RXF2IDE = E2_read_data[0] & 0x8 >> 3;
    CanCfg->RXF2ID = Get_ID_For_Array(E2_read_data, 0);
    CanCfg->RXF3IDE = E2_read_data[4] & 0x8 >> 3;
    CanCfg->RXF3ID = Get_ID_For_Array(E2_read_data, 4);
    //  滤波器4、5
    E2Read(E2_read_data, E2_RXF45, 8);  // 从 EEPROM 读取一段数据
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