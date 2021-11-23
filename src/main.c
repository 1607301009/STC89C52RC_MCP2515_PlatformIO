#include "STC89xx.h"     // Official header from STC-ISP for STC89xx / STC90xx
#include <stdio.h>
#include "UART.h"
#include "I2C_ROM.h"
#include "MCP2515.h"

//#define led15 P15
//#define led17 P17

volatile bool CAN_MERRF_Flag = 0;   // CAN报文错误中断标志位
volatile bool CAN_WAKIF_Flag = 0;   // CAN唤醒中断标志位
volatile bool CAN_ERRIF_Flag = 0;   // CAN错误中断标志位（EFLG 寄存器中有多个中断源）
volatile bool CAN_TX2IF_Flag = 0;   // MCP2515发送缓冲器2 空中断标志位
volatile bool CAN_TX1IF_Flag = 0;   // MCP2515发送缓冲器1 空中断标志位
volatile bool CAN_TX0IF_Flag = 0;   // MCP2515发送缓冲器0 空中断标志位
volatile bool CAN_RX1IF_Flag = 0;   // MCP2515接收缓冲器1 满中断标志位
volatile bool CAN_RX0IF_Flag = 0;   // MCP2515接收缓冲器0 满中断标志位


/*******************************************************************************
* 函数名  : Exint_ISR
* 描述    : 外部中断1中断服务函数 单片机引脚P3.3接MCP2515 INT引脚
* 说明    : 用于检测MCP2515中断引脚的中断信号
*******************************************************************************/
void Exint_ISR(void) __interrupt 2 __using 1
{
    // CAN接收到数据标志
    uint8 Flag = MCP2515_ReadByte(CANINTF);
    CAN_MERRF_Flag = Flag >> 7;          // CAN报文错误中断标志位
    CAN_WAKIF_Flag = Flag >> 6 & 0x1;    // CAN唤醒中断标志位
    CAN_ERRIF_Flag = Flag >> 5 & 0x1;    // CAN错误中断标志位（EFLG 寄存器中有多个中断源）
    CAN_TX2IF_Flag = Flag >> 4 & 0x1;    // MCP2515发送缓冲器2 空中断标志位
    CAN_TX1IF_Flag = Flag >> 3 & 0x1;    // MCP2515发送缓冲器1 空中断标志位
    CAN_TX0IF_Flag = Flag >> 2 & 0x1;    // MCP2515发送缓冲器0 空中断标志位
    CAN_RX1IF_Flag = Flag >> 1 & 0x1;    // MCP2515接收缓冲器1 满中断标志位
    CAN_RX0IF_Flag = Flag & 0x1;         // MCP2515接收缓冲器0 满中断标志位
}

void Print_array(uint8 *array, uint8 len) {
    uint8 i;
    printf("Len: %02X  Data:",  len);
    for (i = 0; i < len; i++) {
        printf(" %02X", array[i]);
    }
    printf("\r\n");
}




void Printf_Cfg(CanCfgStruct *CanCfg) {
//    uint8 __xdata E2_read_data[8];
//    uint8 isRead;
//    printf("page: ");
//    Printf_E2(E2_CanCifg);
//    Printf_E2(E2_RXF01);
//    Printf_E2(E2_RXF23);
//    Printf_E2(E2_RXF45);

//E2Read(E2_read_data, 0, 8);
//for (isRead = 0; isRead < 8; isRead++) {
//    if (isRead % 8 == 0) {
//        printf("\r\n");
//    }
//    if (isRead % 4 == 0) {
//        printf("  ");
//    }
//    printf(" %02X ", Send_data[isRead]);
//}

    printf("Kbps: %02d \r\n", CanCfg->_5Kbps * 5);
    printf("bitrate: %02d %02X %02X %02X %02X\r\n", CanCfg->bitrate[0],
           CanCfg->bitrate[1], CanCfg->bitrate[2], CanCfg->bitrate[3], CanCfg->bitrate[4]);
    printf("CAN_MODE: %02X \r\n", CanCfg->CAN_MODE);

    printf("CANINTE: %02X \r\n", CanCfg->CANINTE_enable);
    printf("CANINTF: %02X \r\n", CanCfg->CANINTF_enable);
    printf("BUKT_enable: %02X \r\n", CanCfg->BUKT_enable);
//
    printf("RXBnRXM0-1: %02X %02X\r\n", CanCfg->RXB0RXM, CanCfg->RXB1RXM);
//
    printf("RXMnID0-1: %08lX %08lX\r\n", CanCfg->RXM0ID, CanCfg->RXM1ID);
//    printf("RXFnID0-5: %07lX %07lX %07lX %07lX %07lX\r\n", CanCfg->RXF0ID, CanCfg->RXF1ID, CanCfg->RXF2ID,
//           CanCfg->RXF3ID, CanCfg->RXF4ID, CanCfg->RXF5ID);
//
//    printf("RXFnIDE0-5: %bX %bX %bX %bX %bX\r\n", CanCfg->RXF0IDE, CanCfg->RXF1IDE, CanCfg->RXF2IDE, CanCfg->RXF3IDE,
//           CanCfg->RXF4IDE, CanCfg->RXF5IDE);
}

/*******************************************************************************
* 描述    : 将数组中的数据，拼接完整ID，长度取4
* 输入    : uint8 数组
* 说明    : 无
*******************************************************************************/
//uint32 GetInt32FormE2(uint8 *buf, uint8 addr) {
//    if (buf[1 + addr] & 0x8 >> 3) {
//        uint32 SID = ((uint32) buf[0 + addr] << 3) | (buf[1 + addr] >> 5);
//        uint32 EID = (uint32) (buf[1 + addr] & 3) << 16 | ((uint32) buf[2 + addr] << 8) | buf[3 + addr];
//        return SID << 18 | EID;
//    } else {
//        uint32 SID = (uint32) (buf[0 + addr] << 3) | (buf[1 + addr] >> 5);
//        return SID;
//    }
//}

void unittest(){
    // pass
//    test_Get_ID_For_Array();
//    test_Set_Array_For_ID();

CanCfgStruct CanCfg;
Set_Cfg_From_E2(&CanCfg);
//printf("_5Kbps: %02X \r\n", CanCfg._5Kbps);
//printf("_5Kbps: %02X \r\n", CanCfg._5Kbps);
Printf_Cfg(&CanCfg);
    // not test
    // test_Get_ID_For_Buf()
    // test_Set_Buf_For_ID()
}



void E2_buf(uint8 isRead)
{
    uint8 __xdata Send_data[] = {
            // 波特率, 工作模式, CANINTE, CANINTF, BUKT, RXB0RXM, RXB1RXM
            0x14, 0x05, 0x03, 0x00, 0x01, 0x05, 0x03, 0x00,
            // RXF0ID, 1 2 3   4 5    ExIDE   id
            0x1F, 0xFF, 0xFF, 0xFF, 0x1F, 0xFF, 0xFF, 0xFF,
            0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01,
            0x00, 0x00, 0x07, 0xff, 0x10, 0x00, 0x17, 0xFF,
            // RXM0ID 0 1
            0x9F, 0xFF, 0xFF, 0xFF, 0x9F, 0xFF, 0xFF, 0xFE};
//    uint8 i;
//__xdata uint8 i;
//__xdata unsigned char i;
//__bdata bit k;
//    k =1;
    printf("E2_buf: %02X ", isRead);
//    if (isRead == 1) {
        printf("now read:\r\n");
        E2Read(Send_data, 0, 8);
        Print_array(Send_data, 8);
        E2Read(Send_data, 8, 8);
        Print_array(Send_data, 8);
        E2Read(Send_data, 16, 8);
        Print_array(Send_data, 8);
        E2Read(Send_data, 24, 8);
        Print_array(Send_data, 8);
        E2Read(Send_data, 32, 8);
        Print_array(Send_data, 8);
//        for (; isRead >= 4; isRead++) {
////            printf("isRead : %d\r\n", i);
////            if (i % 8 == 0) {
////                printf("\r\n");
////            }
////            if (i % 4 == 0) {
////                printf("  ");
////            }
//printf(" %02X ", Send_data[isRead]);
//        }

        
//    } else {
//        E2Write(Send_data, 0, 8);
//    }

    printf("\r\n E2 end\r\n");
}

void main()
{
//    uint8 i = 0xFF;
    volatile bool j = 0;
//    uint32 ID = 0x1FFFFFFF;

//    CanCfgStruct CanCfg;

    //    初始设置配置
    UART_init();    //UART1初始化配置
    Exint_Init();   //外部中断1初始化函数
    printf("bool: j = 0 x: %X\r\n", j);
//    printf("uint8: i = 0 x: %02X\r\n", i);
//    printf("uint32: ID = 0 x: %08X\r\n", ID);
//
    E2_buf(1);
//    printf("write \r\n");
//    E2_buf(0);

    unittest();



//    int n;
//    led15 = 0;  // LED on
//    led17 = 1;  // LED off
//    for (n = 0; n < 10000; n++); // waste some cycles
//    led15 = 1;  // LED off
//    led17 = 0;  // LED off
//    for (n = 0; n < 10000; n++); // waste some cycles
//    I2CDelay();
    while (1);
    return;
}