#ifndef __UART_H
#define __UART_H

void UART_init(void);
void UART_send_str(uint8 d);
// 不在此处生命，中断异常
void uart(void) __interrupt 4;
int putchar(int c);

#endif