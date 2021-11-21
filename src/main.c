#include "STC89xx.h"     // Official header from STC-ISP for STC89xx / STC90xx
#include <stdio.h>
#include "UART.h"
#include "I2C_ROM.h"

#define led15 P15
#define led17 P17


void E2_buf(uint8 isRead)
{
    uint8 Send_data[] = {
            // 波特率, 工作模式, CANINTE, CANINTF, BUKT, RXB0RXM, RXB1RXM
            0x14, 0x05, 0x03, 0x00, 0x01, 0x05, 0x03, 0x00,
            // RXF0ID, 1 2 3   4 5    ExIDE   id
            0x1F, 0xFF, 0xFF, 0xFF, 0x1F, 0xFF, 0xFF, 0xFF,
            0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01,
            0x00, 0x00, 0x07, 0xff, 0x10, 0x00, 0x17, 0xFF,
            // RXM0ID 0 1
            0x9F, 0xFF, 0xFF, 0xFF, 0x9F, 0xFF, 0xFF, 0xFE};
    printf("E2_buf: %02X ", isRead);
    if (isRead == 1) {
        E2Read(Send_data, 0, 40);
        for (isRead = 0; isRead < 40; isRead++) {
            if (isRead % 8 == 0) {
                printf("\r\n");
            }
            if (isRead % 4 == 0) {
                printf("  ");
            }
            printf(" %02X ", Send_data[isRead]);
        }
    } else {
        E2Write(Send_data, 0, 8);
    }

    printf("\r\n E2 end\r\n");
}


void main()
{
    uint8 i = 0xFF;
    volatile bool j = 0;
    uint32 ID = 0x1FFFFFFF;

    //    初始设置配置
    UART_init();    //UART1初始化配置
    printf("bool: j = 0 x: %X\r\n", j);
    printf("uint8: i = 0 x: %02X\r\n", i);
    printf("uint32: ID = 0 x: %08X\r\n", ID);

    E2_buf(1);
    printf("write \r\n");
    E2_buf(0);

    int n;
    led15 = 0;  // LED on
    led17 = 1;  // LED off
    for (n = 0; n < 10000; n++); // waste some cycles
    led15 = 1;  // LED off
    led17 = 0;  // LED off
    for (n = 0; n < 10000; n++); // waste some cycles
    I2CDelay();
    while (1);
    return;
}